//===- MAxiBuffers.cpp - The builtin m_axi adapter model ------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// vitis-m_axi (an ImplicitBufferModel): every m_axi bundle of a public
// function gets an adapter `<bundle>_m_axi_U` whose memories are the read data
// FIFO (depth max_read_burst_length x num_read_outstanding) and, with a write
// burst longer than free_max_burst, the write buffer (VITIS_NOTES N1a
// "Interfaces"; dead_globals.md R8 and the 14 mx_* kernels of
// ~/hls-est-work/exp-src/maxi):
//   - the read FIFO is shift registers up to srl_max_depth (32) words and a
//     two-port block RAM deeper (the x18 bands: depth 64 .. 1024 ceil(W/18),
//     2048 ceil(W/9), 4096 8 at W = 32; confirmed up to 4096);
//   - the write buffer costs nothing up to free_max_burst (16) and
//     ceil(W / port_width_bits (18)) from a burst of 32 (17 .. 31
//     unconfirmed);
//   - the data width is max(min_bus_bits (32), the widest element of the
//     bundle), at most max_bus_bits (1024, the AXI4 limit); the read FIFO is also as wide as the widest load through a
//     pointer cast (read_fifo.cast_load_width), and there is one read FIFO
//     per distinct `channel=` of the reading ports (read_fifo.per_channel;
//     both VITIS_NOTES N56, kernels w9r7_mx_*); the burst settings are the largest any port states, else the
//     interface pragma defaults (16 / 16 / 16 / 16);
//   - a port no access reads (writes) has no read FIFO (write buffer); an
//     argument passed to a defined callee is followed into it, and a port
//     passed to a call without a body is assumed to read and write
//     (unresolved_call: rw).
// The cut-offs are measured Vitis rules, parameters of this model, never
// derived from the device's shift registers or port widths (design memo gap
// G6). (Moved from BRAMAnalysis.cpp, P2.)
//
//===----------------------------------------------------------------------===//

#include "Builtins.h"

#include "circt/Dialect/Resource/Model/AccessOrder.h"
#include "circt/Dialect/Resource/Passes/PolygeistCompat.h"
#include "circt/Dialect/Resource/Plugins/MemoryInterfaces.h"
#include "circt/Dialect/Resource/Plugins/Registry.h"

#include "mlir/Dialect/LLVMIR/LLVMDialect.h"
#include "mlir/IR/BuiltinAttributes.h"
#include "mlir/Interfaces/CallInterfaces.h"
#include "mlir/Interfaces/ViewLikeInterface.h"
#include "llvm/ADT/DenseSet.h"

using namespace mlir;
using namespace circt::hlsest;
using circt::hls_analysis::classifyAccess;
using circt::hls_analysis::Memref2PointerOp;
using circt::hls_analysis::Pointer2MemrefOp;
using circt::hls_analysis::llvmStorageBits;

namespace {

int64_t ceilDiv(int64_t a, int64_t b) { return (a + b - 1) / b; }

static void scanArgUses(Value v, ImplicitBuffer &a,
                        const ImplicitBufferConfig &mc) {
  SmallVector<Value> work{v};
  DenseSet<Value> seen{v};
  while (!work.empty()) {
    Value cur = work.pop_back_val();
    for (OpOperand &use : cur.getUses()) {
      Operation *user = use.getOwner();
      // A struct element reached through cgeist's pointer casts and
      // getelementptr (an m_axi port of structs).
      if (isa<Memref2PointerOp, Pointer2MemrefOp, LLVM::GEPOp>(user)) {
        if (user->getOperand(0) == cur &&
            seen.insert(user->getResult(0)).second)
          work.push_back(user->getResult(0));
        continue;
      }
      if (auto ld = dyn_cast<LLVM::LoadOp>(user)) {
        a.hasRead = true;
        // A load of another type through cgeist's memref2pointer / GEP is
        // a pointer cast in the source (`*reinterpret_cast<ap_uint<512> *>
        // (&a[i])`); Vitis sizes the read FIFO by it (VITIS_NOTES N56).
        Type t = ld.getType();
        unsigned bits = t.isIntOrFloat() ? t.getIntOrFloatBitWidth() : 0;
        if (!bits)
          if (auto storage = llvmStorageBits(t))
            bits = static_cast<unsigned>(*storage);
        a.castLoadBits = std::max(a.castLoadBits, bits);
        continue;
      }
      if (auto st = dyn_cast<LLVM::StoreOp>(user)) {
        if (st.getAddr() == cur)
          a.hasWrite = true;
        continue;
      }
      if (auto view = dyn_cast<ViewLikeOpInterface>(user))
        if (view.getViewSource() == cur) {
          for (Value r : user->getResults())
            if (isa<BaseMemRefType>(r.getType()) && seen.insert(r).second)
              work.push_back(r);
          continue;
        }
      if (auto call = dyn_cast<CallOpInterface>(user)) {
        a.passedToCall = true;
        auto callee =
            dyn_cast_or_null<func::FuncOp>(call.resolveCallable());
        auto args = call.getArgOperands();
        unsigned first = args.getBeginOperandIndex();
        unsigned n = use.getOperandNumber();
        if (callee && !callee.isExternal() && n >= first &&
            n - first < callee.getNumArguments()) {
          Value inner = callee.getArgument(n - first);
          if (seen.insert(inner).second)
            work.push_back(inner);
          continue;
        }
        // tool.hls.implicit_buffers[axi4-mm].unresolved_call: what a port
        // passed to a call without a body is assumed to do (rw).
        a.unresolvedCall = true;
        if (mc.unresolvedCall == "rw")
          a.hasRead = a.hasWrite = true;
        continue;
      }
      bool isWrite = false;
      if (classifyAccess(user, cur, isWrite))
        (isWrite ? a.hasWrite : a.hasRead) = true;
    }
  }
}

static int64_t intField(DictionaryAttr d, StringRef name, int64_t dflt) {
  if (auto i = d.getAs<IntegerAttr>(name))
    return i.getInt();
  return dflt;
}

class VitisMAxiBuffers : public ImplicitBufferModel {
public:
  llvm::StringRef name() const override { return "vitis-m_axi"; }

  void configure(const Config &config, ConfigDiagnostics &) override {
    indexBits = static_cast<unsigned>(config.frontend.indexBits);
    if (const ImplicitBufferConfig *mc = config.tool.hls.implicitBuffer("axi4-mm"))
      if (const DeviceMemory *m = config.blockMemory())
        if (const PortConfig *pc = m->portConfig(mc->readFifoPricedConfig))
          fifoWidth = pc->maxWidth;
  }

  void buffers(func::FuncOp fn, const ImplicitBufferConfig &mc,
               llvm::function_ref<int64_t(int64_t, unsigned)> mapFifo,
               SmallVectorImpl<ImplicitBuffer> &out) const override {
    SmallVector<ImplicitBuffer> bundles;
    // The `channel=` values of each bundle's reading ports (-1: none given).
    SmallVector<llvm::SmallDenseSet<int64_t, 4>> readChannels;
    for (unsigned i = 0, e = fn.getNumArguments(); i < e; ++i) {
      auto ifaces = fn.getArgAttrOfType<ArrayAttr>(i, "hls.interface");
      if (!ifaces)
        continue;
      for (Attribute attr : ifaces) {
        auto d = dyn_cast<DictionaryAttr>(attr);
        auto mode = d ? d.getAs<StringAttr>("mode") : StringAttr();
        if (!mode || mode.getValue() != mc.mode)
          continue;
        std::string bundle = mc.defaultBundle;
        if (auto b = d.getAs<StringAttr>("bundle"))
          bundle = b.getValue().str();
        ImplicitBuffer *a = nullptr;
        unsigned index = 0;
        for (unsigned k = 0; k < bundles.size(); ++k)
          if (bundles[k].bundle == bundle) {
            a = &bundles[k];
            index = k;
          }
        if (!a) {
          index = bundles.size();
          readChannels.emplace_back();
          bundles.emplace_back();
          a = &bundles.back();
          a->bundle = bundle;
          a->busBits = static_cast<unsigned>(mc.minBusBits);
          a->readBurst = a->readOutstanding = 0;
          a->writeBurst = a->writeOutstanding = 0;
        }
        if (auto p = d.getAs<StringAttr>("port"))
          a->ports.push_back(p.getValue().str());
        Value arg = fn.getArgument(i);
        unsigned bits = static_cast<unsigned>(mc.minBusBits);
        if (auto mt = dyn_cast<BaseMemRefType>(arg.getType())) {
          Type elt = mt.getElementType();
          bits = elt.isIntOrFloat() ? elt.getIntOrFloatBitWidth()
                 : isa<IndexType>(elt)
                     ? indexBits
                     : static_cast<unsigned>(mc.minBusBits);
          // A struct element: Vitis always aggregates an m_axi struct port,
          // at the struct's C storage size, padding included
          // (compact=none; kernel w9s_b: {int; short; ap_int<5>[2]} is a
          // 64-bit port, hls::vector<ap_fixed<14>, 8> a 128-bit one).
          if (isa<LLVM::LLVMStructType>(elt))
            if (auto storage = llvmStorageBits(elt))
              bits = static_cast<unsigned>(*storage);
        } else if (arg.getType().isIntOrFloat()) {
          bits = arg.getType().getIntOrFloatBitWidth();
        }
        a->busBits = std::max(
            a->busBits,
            std::max(static_cast<unsigned>(mc.minBusBits), bits));
        // Vitis requires consistent settings within a bundle; take the
        // largest value any port states (defaults 16 / 16 / 16 / 16).
        a->readBurst = std::max(a->readBurst,
                                intField(d, "max_read_burst_length", 0));
        a->readOutstanding = std::max(
            a->readOutstanding, intField(d, "num_read_outstanding", 0));
        a->writeBurst = std::max(a->writeBurst,
                                 intField(d, "max_write_burst_length", 0));
        a->writeOutstanding = std::max(
            a->writeOutstanding, intField(d, "num_write_outstanding", 0));
        // Scan the port on its own first: its channel has a read FIFO only
        // when the port itself reads.
        ImplicitBuffer port;
        scanArgUses(arg, port, mc);
        a->hasRead |= port.hasRead;
        a->hasWrite |= port.hasWrite;
        a->passedToCall |= port.passedToCall;
        a->unresolvedCall |= port.unresolvedCall;
        if (port.hasRead) {
          a->castLoadBits = std::max(a->castLoadBits, port.castLoadBits);
          readChannels[index].insert(intField(d, "channel", -1));
        }
      }
    }
    for (ImplicitBuffer &a : bundles) {
      if (!a.readBurst)
        a.readBurst = mc.defaults.maxReadBurstLength;
      if (!a.readOutstanding)
        a.readOutstanding = mc.defaults.numReadOutstanding;
      if (!a.writeBurst)
        a.writeBurst = mc.defaults.maxWriteBurstLength;
      if (!a.writeOutstanding)
        a.writeOutstanding = mc.defaults.numWriteOutstanding;
      a.readDepth = a.readBurst * a.readOutstanding;
      // AXI4 moves at most max_bus_bits (1024) per beat: a wider element
      // takes several beats through a 1024-bit adapter (connor_talley lab2:
      // 2048-bit hls::vector ports, 3 channels x 57 = 3 x ceil(1024 / 18);
      // kernel w9r7i_mx_w2048).
      unsigned maxBits = static_cast<unsigned>(mc.maxBusBits);
      a.busBits = std::min(a.busBits, maxBits);
      a.readBits = a.busBits;
      if (mc.readFifoCastLoadWidth)
        a.readBits = std::max(a.readBits, std::min(a.castLoadBits, maxBits));
      size_t index = &a - bundles.data();
      a.readChannels =
          mc.readFifoPerChannel
              ? std::max<unsigned>(1, readChannels[index].size())
              : 1;
      // Read data FIFO: confirmed at depth 2 .. 32 -> 0 (SRL) and 40, 48,
      // 64, 256, 1024 -> ceil(W/18), 2048 -> ceil(W/9), 4096 -> 8 (W = 32),
      // for W = 32 (int, and ap_int<16> widened) and W = 64.
      if (!a.hasRead) {
        a.readBram = 0;
        a.readRule = "no load: no read FIFO cost";
      } else if (a.readDepth <= mc.readFifoSrlMaxDepth) {
        a.readBram = 0;
        a.readRule = "depth <= " + std::to_string(mc.readFifoSrlMaxDepth) +
                     ": shift-register FIFO, 0 BRAM";
      } else {
        a.readBram = a.readChannels *
                     static_cast<unsigned>(mapFifo(a.readDepth, a.readBits));
        a.readRule = "depth > " + std::to_string(mc.readFifoSrlMaxDepth) +
                     ": BRAM FIFO, two ports (x" +
                     std::to_string(fifoWidth) + " bands of N8)";
        if (a.readBits != a.busBits)
          a.readRule += "; " + std::to_string(a.readBits) +
                        " bits wide: a load through a pointer cast (N56)";
        if (a.readChannels > 1)
          a.readRule += "; " + std::to_string(a.readChannels) +
                        " FIFOs, one per channel (N56)";
        if (a.readDepth > mc.readFifoConfirmedMaxDepth)
          a.readRule += "; depth > " +
                        std::to_string(mc.readFifoConfirmedMaxDepth) +
                        " unconfirmed";
      }
      // Write buffer: 0 at max_write_burst_length 16 (any outstanding,
      // 1 .. 32), ceil(W/18) at 32, 64, 128, 256 (W = 32: 2; W = 64 at 64:
      // 4). Bursts 17 .. 31 are unconfirmed.
      if (!a.hasWrite) {
        a.writeBram = 0;
        a.writeRule = "no store: no write buffer cost";
      } else if (a.writeBurst <= mc.writeBufferFreeMaxBurst) {
        a.writeBram = 0;
        a.writeRule = "max_write_burst_length <= " +
                      std::to_string(mc.writeBufferFreeMaxBurst) + ": 0 BRAM";
      } else {
        a.writeBram = static_cast<unsigned>(
            ceilDiv(a.busBits, mc.writeBufferPortWidthBits));
        a.writeRule = "max_write_burst_length > " +
                      std::to_string(mc.writeBufferFreeMaxBurst) +
                      ": ceil(W/" +
                      std::to_string(mc.writeBufferPortWidthBits) + ")";
        if (a.writeBurst < mc.writeBufferConfirmedMinBurst)
          a.writeRule += " (bursts " +
                         std::to_string(mc.writeBufferFreeMaxBurst + 1) +
                         ".." +
                         std::to_string(mc.writeBufferConfirmedMinBurst - 1) +
                         " unconfirmed)";
      }
      out.push_back(std::move(a));
    }
  }

private:
  unsigned indexBits = 64;
  int64_t fifoWidth = 18;
};

} // namespace

void circt::hlsest::builtin::registerImplicitBufferModels() {
  PluginRegistry<ImplicitBufferModel>::instance().add(
      "vitis-m_axi",
      "the read FIFO and write buffer of every m_axi bundle's adapter "
      "(VITIS_NOTES N1a)",
      [] { return std::make_unique<VitisMAxiBuffers>(); }, "builtin");
}
