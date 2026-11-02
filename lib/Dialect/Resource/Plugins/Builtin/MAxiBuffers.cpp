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
//     unconfirmed), except that burst x the widest element (not padded to
//     the bus minimum) below min_bram_bits (1024) is LUTRAM (N158), and W
//     is that element width, not the padded bus width (N158 (b),
//     write_buffer.element_width);
//   - the data width is max(min_bus_bits (32), the widest element of the
//     bundle), at most max_bus_bits (1024, the AXI4 limit); the read FIFO is also as wide as the widest load through a
//     pointer cast (read_fifo.cast_load_width), and there is one read FIFO
//     per distinct `channel=` of the reading ports (read_fifo.per_channel;
//     both VITIS_NOTES N56, kernels w9r7_mx_*); the read FIFO width is
//     rounded up to a power of two (read_fifo.power_of_two_width, N63,
//     kernels w9r8p_mx_*); the burst settings are the largest any port states, else the
//     interface pragma defaults (16 / 16 / 16 / 16);
//   - a load whose only use is a part-select read-modify-write stored back
//     to its element, every byte kept whole or overwritten, is no read
//     (read_fifo.strobed_part_writes, N152: Vitis writes with byte strobes);
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
#include "circt/Dialect/Resource/Passes/StreamFifos.h"
#include "circt/Dialect/Resource/Plugins/MemoryInterfaces.h"
#include "circt/Dialect/Resource/Plugins/Registry.h"

#include "circt/Dialect/LoopSchedule/LoopScheduleOps.h"

#include "mlir/Dialect/Affine/IR/AffineOps.h"
#include "mlir/Dialect/Arith/IR/Arith.h"
#include "mlir/Dialect/LLVMIR/LLVMDialect.h"
#include "mlir/Dialect/MemRef/IR/MemRef.h"
#include "mlir/IR/BuiltinAttributes.h"
#include "mlir/Interfaces/CallInterfaces.h"
#include "mlir/Interfaces/ViewLikeInterface.h"
#include "llvm/ADT/DenseSet.h"
#include "llvm/Support/MathExtras.h"

using namespace mlir;
using namespace circt::hlsest;
using circt::hls_analysis::classifyAccess;
using circt::hls_analysis::Memref2PointerOp;
using circt::hls_analysis::Pointer2MemrefOp;
using circt::hls_analysis::llvmStorageBits;

namespace {

int64_t ceilDiv(int64_t a, int64_t b) { return (a + b - 1) / b; }

//===----------------------------------------------------------------------===//
// Strobed part-select writes (VITIS_NOTES N152).
//
// `out[i].range(hi, lo) = x` on an m_axi word is lowered by cgeist to
// `store(ori(andi(load out[i], ~mask), x << lo), out[i])`. Vitis writes such a
// word with byte strobes and reads nothing when every byte is either kept
// whole or overwritten (kernels w9r21p_c1 / c2 / c3: no read FIFO); a slice
// that splits a byte (c5) or any other use of the loaded word (c4, `|=`)
// reads. After --convert-affine-to-loopschedule the chain crosses pipeline
// stages through loopschedule.register, and the masks are hoisted constant
// expressions, so both are looked through here.
//===----------------------------------------------------------------------===//

using circt::loopschedule::LoopSchedulePipelineStageOp;
using circt::loopschedule::LoopScheduleRegisterOp;

constexpr unsigned kConstEvalDepth = 64;

/// Memo tables of the two evaluators below, cleared per analysed load (the
/// expressions of an unrolled part-select chain share most of their operands).
struct StrobeMemo {
  DenseMap<Value, std::optional<APInt>> constants;
  DenseMap<Value, APInt> possible;
};
static thread_local StrobeMemo *strobeMemo = nullptr;

static std::optional<APInt> evalConstIntImpl(Value v, unsigned depth);
static std::optional<APInt> evalConstInt(Value v, unsigned depth);
static APInt possibleOnes(Value v, unsigned depth = 0);
static Value throughStages(Value v);

/// Whether base + x and base + y wrap neither signed nor unsigned (the
/// base's largest value from its possible bits; x, y non-negative).
static bool noWrap(Value base, const APInt &x, const APInt &y,
                   unsigned depth) {
  if (x.getBitWidth() != y.getBitWidth() || x.isNegative() || y.isNegative())
    return false;
  APInt maxBase = possibleOnes(base, depth + 1);
  if (maxBase.getBitWidth() != x.getBitWidth())
    return false;
  bool overflow = false;
  APInt top = maxBase.uadd_ov(x.ugt(y) ? x : y, overflow);
  return !overflow && !top.isNegative();
}

/// `v` as base + offset (base null: a constant), looking through additions
/// of constants and selects with a known condition: the part-select
/// `range(8 * s + 7, 8 * s)` compares and subtracts its two bounds, which
/// share the base 8 * s (W9 round 21 review D7).
struct LinearForm {
  Value base;
  APInt offset;
};
static std::optional<LinearForm> linearForm(Value v, unsigned depth) {
  unsigned width = v.getType().isIndex() ? 64
                   : v.getType().isInteger()
                       ? v.getType().getIntOrFloatBitWidth()
                       : 0;
  if (!width || depth > kConstEvalDepth)
    return std::nullopt;
  if (std::optional<APInt> c = evalConstInt(v, depth + 1))
    return LinearForm{Value(), *c};
  v = throughStages(v);
  Operation *op = v.getDefiningOp();
  if (op && isa<arith::AddIOp, arith::SubIOp>(op)) {
    std::optional<APInt> c = evalConstInt(op->getOperand(1), depth + 1);
    if (c && c->getBitWidth() == width)
      if (std::optional<LinearForm> f =
              linearForm(op->getOperand(0), depth + 1))
        return LinearForm{f->base, isa<arith::AddIOp>(op) ? f->offset + *c
                                                          : f->offset - *c};
    if (isa<arith::AddIOp>(op))
      if (std::optional<APInt> c0 = evalConstInt(op->getOperand(0), depth + 1);
          c0 && c0->getBitWidth() == width)
        if (std::optional<LinearForm> f =
                linearForm(op->getOperand(1), depth + 1))
          return LinearForm{f->base, f->offset + *c0};
  }
  if (auto sel = dyn_cast_or_null<arith::SelectOp>(op))
    if (std::optional<APInt> c = evalConstInt(sel.getCondition(), depth + 1))
      return linearForm(c->isZero() ? sel.getFalseValue() : sel.getTrueValue(),
                        depth + 1);
  // min / max of two values with one base (canonicalised selects).
  if (op && isa<arith::MinUIOp, arith::MaxUIOp, arith::MinSIOp,
                arith::MaxSIOp>(op)) {
    std::optional<LinearForm> a = linearForm(op->getOperand(0), depth + 1);
    std::optional<LinearForm> b = linearForm(op->getOperand(1), depth + 1);
    if (a && b && a->base && a->base == b->base &&
        noWrap(a->base, a->offset, b->offset, depth)) {
      bool aSmaller = a->offset.ult(b->offset);
      bool min = isa<arith::MinUIOp, arith::MinSIOp>(op);
      return aSmaller == min ? *a : *b;
    }
  }
  return LinearForm{v, APInt(width, 0)};
}

/// The difference / comparison of two values with one base, when neither
/// base + offset wraps (the base's largest value from its possible bits).
static std::optional<APInt> evalSameBase(Operation *op, unsigned depth) {
  std::optional<LinearForm> a = linearForm(op->getOperand(0), depth + 1);
  std::optional<LinearForm> b = linearForm(op->getOperand(1), depth + 1);
  if (!a || !b || !a->base || a->base != b->base ||
      a->offset.getBitWidth() != b->offset.getBitWidth())
    return std::nullopt;
  if (isa<arith::SubIOp>(op))
    return a->offset - b->offset;
  auto cmp = dyn_cast<arith::CmpIOp>(op);
  if (!cmp || !noWrap(a->base, a->offset, b->offset, depth))
    return std::nullopt;
  const APInt &x = a->offset, &y = b->offset;
  bool r = false;
  switch (cmp.getPredicate()) {
  case arith::CmpIPredicate::eq: r = x == y; break;
  case arith::CmpIPredicate::ne: r = x != y; break;
  case arith::CmpIPredicate::ult:
  case arith::CmpIPredicate::slt: r = x.ult(y); break;
  case arith::CmpIPredicate::ule:
  case arith::CmpIPredicate::sle: r = x.ule(y); break;
  case arith::CmpIPredicate::ugt:
  case arith::CmpIPredicate::sgt: r = x.ugt(y); break;
  case arith::CmpIPredicate::uge:
  case arith::CmpIPredicate::sge: r = x.uge(y); break;
  }
  return APInt(1, r);
}

/// The value of an integer / index expression whose leaves are constants.
static std::optional<APInt> evalConstInt(Value v, unsigned depth = 0) {
  if (depth > kConstEvalDepth)
    return std::nullopt;
  if (strobeMemo) {
    auto it = strobeMemo->constants.find(v);
    if (it != strobeMemo->constants.end())
      return it->second;
  }
  std::optional<APInt> r = evalConstIntImpl(v, depth);
  if (strobeMemo)
    strobeMemo->constants[v] = r;
  return r;
}

static std::optional<APInt> evalConstIntImpl(Value v, unsigned depth) {
  Operation *op = v.getDefiningOp();
  if (!op)
    return std::nullopt;
  // A value defined in an earlier pipeline stage.
  if (auto stage = dyn_cast<LoopSchedulePipelineStageOp>(op)) {
    auto reg = dyn_cast<LoopScheduleRegisterOp>(
        stage.getBodyBlock().getTerminator());
    unsigned n = cast<OpResult>(v).getResultNumber();
    if (reg && n < reg->getNumOperands())
      return evalConstInt(reg->getOperand(n), depth + 1);
    return std::nullopt;
  }
  unsigned width = v.getType().isIndex() ? 64
                   : v.getType().isInteger()
                       ? v.getType().getIntOrFloatBitWidth()
                       : 0;
  if (!width)
    return std::nullopt;
  if (auto c = dyn_cast<arith::ConstantOp>(op)) {
    if (auto i = dyn_cast<IntegerAttr>(c.getValue()))
      return i.getValue().sextOrTrunc(width);
    return std::nullopt;
  }
  auto arg = [&](unsigned i) { return evalConstInt(op->getOperand(i), depth + 1); };
  if (isa<arith::ExtUIOp, arith::ExtSIOp, arith::TruncIOp, arith::IndexCastOp,
          arith::IndexCastUIOp>(op)) {
    auto a = arg(0);
    if (!a)
      return std::nullopt;
    if (isa<arith::ExtSIOp, arith::IndexCastOp>(op))
      return a->sextOrTrunc(width);
    return a->zextOrTrunc(width);
  }
  if (auto sel = dyn_cast<arith::SelectOp>(op)) {
    auto c = arg(0);
    if (!c)
      return std::nullopt;
    return evalConstInt(c->isZero() ? sel.getFalseValue() : sel.getTrueValue(),
                        depth + 1);
  }
  if (op->getNumOperands() != 2)
    return std::nullopt;
  auto a = arg(0), b = arg(1);
  if ((!a || !b) && isa<arith::CmpIOp, arith::SubIOp>(op))
    return evalSameBase(op, depth);
  if (!a || !b || a->getBitWidth() != b->getBitWidth())
    return std::nullopt;
  if (auto cmp = dyn_cast<arith::CmpIOp>(op)) {
    bool r = false;
    switch (cmp.getPredicate()) {
    case arith::CmpIPredicate::eq: r = *a == *b; break;
    case arith::CmpIPredicate::ne: r = *a != *b; break;
    case arith::CmpIPredicate::ult: r = a->ult(*b); break;
    case arith::CmpIPredicate::ule: r = a->ule(*b); break;
    case arith::CmpIPredicate::ugt: r = a->ugt(*b); break;
    case arith::CmpIPredicate::uge: r = a->uge(*b); break;
    case arith::CmpIPredicate::slt: r = a->slt(*b); break;
    case arith::CmpIPredicate::sle: r = a->sle(*b); break;
    case arith::CmpIPredicate::sgt: r = a->sgt(*b); break;
    case arith::CmpIPredicate::sge: r = a->sge(*b); break;
    }
    return APInt(1, r);
  }
  unsigned w = a->getBitWidth();
  auto shiftAmount = [&]() -> std::optional<unsigned> {
    if (b->uge(w))
      return std::nullopt;
    return static_cast<unsigned>(b->getZExtValue());
  };
  if (isa<arith::AddIOp>(op)) return *a + *b;
  if (isa<arith::SubIOp>(op)) return *a - *b;
  if (isa<arith::MulIOp>(op)) return *a * *b;
  if (isa<arith::AndIOp>(op)) return *a & *b;
  if (isa<arith::OrIOp>(op)) return *a | *b;
  if (isa<arith::XOrIOp>(op)) return *a ^ *b;
  if (isa<arith::MinUIOp>(op)) return a->ult(*b) ? *a : *b;
  if (isa<arith::MaxUIOp>(op)) return a->ugt(*b) ? *a : *b;
  if (isa<arith::MinSIOp>(op)) return a->slt(*b) ? *a : *b;
  if (isa<arith::MaxSIOp>(op)) return a->sgt(*b) ? *a : *b;
  if (isa<arith::ShLIOp, arith::ShRUIOp, arith::ShRSIOp>(op)) {
    auto s = shiftAmount();
    if (!s)
      return std::nullopt;
    if (isa<arith::ShLIOp>(op)) return a->shl(*s);
    if (isa<arith::ShRUIOp>(op)) return a->lshr(*s);
    return a->ashr(*s);
  }
  return std::nullopt;
}

static APInt possibleOnesImpl(Value v, unsigned depth);

/// The bits of `v` that may be one (all ones when unknown).
static APInt possibleOnes(Value v, unsigned depth) {
  if (strobeMemo) {
    auto it = strobeMemo->possible.find(v);
    if (it != strobeMemo->possible.end())
      return it->second;
  }
  APInt r = possibleOnesImpl(v, depth);
  if (strobeMemo)
    strobeMemo->possible[v] = r;
  return r;
}

static APInt possibleOnesImpl(Value v, unsigned depth) {
  unsigned w = v.getType().getIntOrFloatBitWidth();
  APInt all = APInt::getAllOnes(w);
  if (depth > kConstEvalDepth)
    return all;
  if (auto c = evalConstInt(v))
    return *c;
  Operation *op = v.getDefiningOp();
  if (!op)
    return all;
  auto p = [&](unsigned i) { return possibleOnes(op->getOperand(i), depth + 1); };
  if (isa<arith::AndIOp>(op))
    return p(0) & p(1);
  if (isa<arith::OrIOp, arith::XOrIOp>(op))
    return p(0) | p(1);
  if (auto sel = dyn_cast<arith::SelectOp>(op)) {
    if (std::optional<APInt> c = evalConstInt(sel.getCondition(), depth + 1))
      return possibleOnes(c->isZero() ? sel.getFalseValue()
                                      : sel.getTrueValue(),
                          depth + 1);
    return possibleOnes(sel.getTrueValue(), depth + 1) |
           possibleOnes(sel.getFalseValue(), depth + 1);
  }
  if (isa<arith::ExtUIOp>(op))
    return p(0).zext(w);
  // min / max: one of the operands (the one linearForm picks, when known).
  if (isa<arith::MinUIOp, arith::MaxUIOp, arith::MinSIOp, arith::MaxSIOp>(op)) {
    if (std::optional<LinearForm> f = linearForm(v, depth + 1))
      if (f->base && f->base != v && f->offset.isZero())
        return possibleOnes(f->base, depth + 1);
    return p(0) | p(1);
  }
  // A product with a power of two is a shift (`8 * s`).
  if (isa<arith::MulIOp>(op))
    for (unsigned i = 0; i < 2; ++i)
      if (std::optional<APInt> c = evalConstInt(op->getOperand(1 - i)))
        if (c->getBitWidth() == w && c->isPowerOf2())
          return possibleOnes(op->getOperand(i), depth + 1)
              .shl(c->logBase2());
  if (isa<arith::ShLIOp, arith::ShRUIOp>(op)) {
    APInt a = p(0);
    auto s = evalConstInt(op->getOperand(1));
    if (s && s->ult(w)) {
      unsigned n = static_cast<unsigned>(s->getZExtValue());
      return isa<arith::ShLIOp>(op) ? a.shl(n) : a.lshr(n);
    }
    // An unknown logical right shift never sets a bit above the highest one.
    if (isa<arith::ShRUIOp>(op))
      return APInt::getLowBitsSet(w, w - a.countLeadingZeros());
    return all;
  }
  // A value defined in an earlier pipeline stage.
  if (auto stage = dyn_cast<LoopSchedulePipelineStageOp>(op)) {
    auto reg = dyn_cast<LoopScheduleRegisterOp>(
        stage.getBodyBlock().getTerminator());
    unsigned n = cast<OpResult>(v).getResultNumber();
    if (reg && n < reg->getNumOperands())
      return possibleOnes(reg->getOperand(n), depth + 1);
  }
  return all;
}

/// The value a stage result carries (looked through its register), or `v`.
static Value throughStages(Value v) {
  for (unsigned i = 0; i < kConstEvalDepth; ++i) {
    auto stage = v.getDefiningOp<LoopSchedulePipelineStageOp>();
    if (!stage)
      return v;
    auto reg =
        dyn_cast<LoopScheduleRegisterOp>(stage.getBodyBlock().getTerminator());
    unsigned n = cast<OpResult>(v).getResultNumber();
    if (!reg || n >= reg->getNumOperands())
      return v;
    v = reg->getOperand(n);
  }
  return v;
}

/// The memref and the address of a plain load or store.
static bool accessAddress(Operation *op, Value &mem, AffineMap &map,
                          SmallVectorImpl<Value> &indices) {
  if (auto ld = dyn_cast<memref::LoadOp>(op)) {
    mem = ld.getMemRef();
    indices.assign(ld.getIndices().begin(), ld.getIndices().end());
    return true;
  }
  if (auto st = dyn_cast<memref::StoreOp>(op)) {
    mem = st.getMemRef();
    indices.assign(st.getIndices().begin(), st.getIndices().end());
    return true;
  }
  if (auto ld = dyn_cast<affine::AffineLoadOp>(op)) {
    mem = ld.getMemRef();
    map = ld.getAffineMap();
    indices.assign(ld.getMapOperands().begin(), ld.getMapOperands().end());
    return true;
  }
  if (auto st = dyn_cast<affine::AffineStoreOp>(op)) {
    mem = st.getMemRef();
    map = st.getAffineMap();
    indices.assign(st.getMapOperands().begin(), st.getMapOperands().end());
    return true;
  }
  return false;
}

static Value storedValue(Operation *op) {
  if (auto st = dyn_cast<memref::StoreOp>(op))
    return st.getValueToStore();
  if (auto st = dyn_cast<affine::AffineStoreOp>(op))
    return st.getValueToStore();
  return {};
}

/// Every byte of `kept` is all ones or all zeros.
static bool wholeBytes(const APInt &kept) {
  unsigned w = kept.getBitWidth();
  for (unsigned lo = 0; lo < w; lo += 8) {
    APInt byte = kept.extractBits(std::min(8u, w - lo), lo);
    if (!byte.isZero() && !byte.isAllOnes())
      return false;
  }
  return true;
}

/// The uses of `v`, looking through the registers that carry it to later
/// pipeline stages.
static void effectiveUses(Value v, SmallVectorImpl<OpOperand *> &out,
                          unsigned depth = 0) {
  for (OpOperand &use : v.getUses()) {
    if (auto reg = dyn_cast<LoopScheduleRegisterOp>(use.getOwner())) {
      auto stage = dyn_cast<LoopSchedulePipelineStageOp>(reg->getParentOp());
      if (stage && depth < kConstEvalDepth &&
          use.getOperandNumber() < stage->getNumResults()) {
        effectiveUses(stage->getResult(use.getOperandNumber()), out, depth + 1);
        continue;
      }
    }
    out.push_back(&use);
  }
}

/// Whether `load` only feeds strobed part-select writes back to its own
/// element (N152): see the section comment.
static bool isStrobedPartWriteLoadImpl(Operation *load);
static bool isStrobedPartWriteLoad(Operation *load) {
  StrobeMemo memo;
  strobeMemo = &memo;
  bool r = isStrobedPartWriteLoadImpl(load);
  strobeMemo = nullptr;
  return r;
}

static bool isStrobedPartWriteLoadImpl(Operation *load) {
  Value mem;
  AffineMap map;
  SmallVector<Value> indices;
  if (!accessAddress(load, mem, map, indices) || load->getNumResults() != 1)
    return false;
  Value word = load->getResult(0);
  if (!word.getType().isInteger())
    return false;
  unsigned w = word.getType().getIntOrFloatBitWidth();
  auto sameAddress = [&](Operation *store) {
    Value m;
    AffineMap mp;
    SmallVector<Value> idx;
    if (!accessAddress(store, m, mp, idx) || m != mem || mp != map ||
        idx.size() != indices.size())
      return false;
    for (auto [a, b] : llvm::zip(idx, indices))
      if (throughStages(a) != throughStages(b))
        return false;
    return true;
  };
  // Every value computed from the loaded word, so that an `ori` of two of
  // them (bits of the old word moved elsewhere) is recognised as a read.
  // Built at the first `ori` (speed only: most loads fail the walk below at
  // their first use, and the forward slice of each of them was most of the
  // time of class_ece8893_spring_2025 lab2_hanchen).
  DenseSet<Value> derived;
  auto isDerived = [&](Value v) {
    if (derived.empty()) {
      derived.insert(word);
      SmallVector<Value> slice{word};
      while (!slice.empty()) {
        Value cur = slice.pop_back_val();
        SmallVector<OpOperand *> uses;
        effectiveUses(cur, uses);
        for (OpOperand *use : uses)
          for (Value r : use->getOwner()->getResults())
            if (derived.insert(r).second)
              slice.push_back(r);
      }
    }
    return derived.contains(v);
  };
  // A field cleared at a position known only at run time: `word & ~(F <<
  // k)` with F a constant of whole bytes and k a multiple of 8 (a
  // part-select at a run-time byte lane, W9 round 21 review D7: kernel
  // w9r21rev_r3b_dynbyte `out[i].range(8 * s + 7, 8 * s) = x`, no read FIFO
  // in Vitis). The value or-ed in must be `y << k`, the same k, with y
  // within F.
  struct Hole {
    APInt field;
    Value shift;
  };
  auto matchHole = [&](Value mask) -> std::optional<Hole> {
    auto inv = throughStages(mask).getDefiningOp<arith::XOrIOp>();
    if (!inv)
      return std::nullopt;
    for (unsigned i = 0; i < 2; ++i) {
      std::optional<APInt> ones = evalConstInt(inv->getOperand(1 - i));
      if (!ones || !ones->isAllOnes() || ones->getBitWidth() != w)
        continue;
      auto shl =
          throughStages(inv->getOperand(i)).getDefiningOp<arith::ShLIOp>();
      if (!shl)
        return std::nullopt;
      std::optional<APInt> field = evalConstInt(shl.getLhs());
      APInt shiftBits = possibleOnes(shl.getRhs());
      if (!field || field->getBitWidth() != w || !wholeBytes(*field) ||
          shiftBits.getBitWidth() < 3 || !shiftBits.extractBits(3, 0).isZero())
        return std::nullopt;
      return Hole{*field, throughStages(shl.getRhs())};
    }
    return std::nullopt;
  };
  auto fillsHole = [&](Value v, const Hole &hole) {
    auto shl = throughStages(v).getDefiningOp<arith::ShLIOp>();
    if (!shl || throughStages(shl.getRhs()) != hole.shift)
      return false;
    APInt y = possibleOnes(shl.getLhs());
    return y.getBitWidth() == w && !y.intersects(~hole.field);
  };
  struct Item {
    Value value;
    APInt kept;
    std::optional<Hole> hole;
  };
  SmallVector<Item> work{{word, APInt::getAllOnes(w), std::nullopt}};
  bool stored = false;
  while (!work.empty()) {
    Item item = work.pop_back_val();
    Value cur = item.value;
    const APInt &kept = item.kept;
    SmallVector<OpOperand *> uses;
    effectiveUses(cur, uses);
    for (OpOperand *use : uses) {
      Operation *user = use->getOwner();
      Value other = user->getNumOperands() == 2
                        ? user->getOperand(1 - use->getOperandNumber())
                        : Value();
      if (isa<arith::AndIOp>(user)) {
        auto mask = evalConstInt(other);
        if (mask && mask->getBitWidth() == w) {
          work.push_back({user->getResult(0), kept & *mask, item.hole});
          continue;
        }
        std::optional<Hole> hole = item.hole ? std::nullopt : matchHole(other);
        if (!hole)
          return false;
        work.push_back({user->getResult(0), kept, hole});
        continue;
      }
      if (isa<arith::OrIOp>(user)) {
        if (isDerived(other))
          return false;
        if (item.hole) {
          if (!fillsHole(other, *item.hole))
            return false;
        } else if (possibleOnes(other).intersects(kept)) {
          return false;
        }
        work.push_back({user->getResult(0), kept, item.hole});
        continue;
      }
      if (storedValue(user) == cur && sameAddress(user)) {
        if (!wholeBytes(kept))
          return false;
        stored = true;
        continue;
      }
      return false;
    }
  }
  return stored;
}

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
        // The data argument of an hls::stream method: `s >> C[i]` /
        // `s.read(C[i])` writes the port's element, `s << C[i]` reads it
        // (class_ece8893 nikhil_p lab3 `mem3`, written only through
        // `C_local >> C[i]`: Vitis has no read FIFO; W9r7 review defect 8b).
        if (auto sym = dyn_cast_if_present<SymbolRefAttr>(
                call.getCallableForCallee()))
          if (auto stream = circt::hls_analysis::parseStreamMethod(
                  sym.getLeafReference().getValue()))
            if (n == first + 1)
              if (auto kind =
                      circt::hls_analysis::streamDataAccess(stream->method)) {
                (*kind == circt::hls_analysis::StreamData::WritesElement
                     ? a.hasWrite
                     : a.hasRead) = true;
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
      if (classifyAccess(user, cur, isWrite)) {
        // tool.hls.implicit_buffers[axi4-mm].read_fifo.strobed_part_writes.
        if (!isWrite && mc.readFifoStrobedPartWrites &&
            isStrobedPartWriteLoad(user))
          continue;
        (isWrite ? a.hasWrite : a.hasRead) = true;
      }
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
    // The `channel=` values of each bundle's reading ports. A port without
    // `channel=` is on channel 0: it shares the read FIFO of an explicit
    // `channel=0` (kernel w9r7rev_mx_chdef: a channel=0 port and two ports
    // without one, Vitis 39 = one FIFO, not two; W9r7 review defect 9).
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
        a->elementBits = std::max(a->elementBits, bits);
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
          // `#pragma HLS cache port=...` (hls.cache on the argument, N179).
          a->cachedRead |= static_cast<bool>(fn.getArgAttr(i, "hls.cache"));
          a->castLoadBits = std::max(a->castLoadBits, port.castLoadBits);
          readChannels[index].insert(intField(d, "channel", 0));
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
      // An AXI data bus is 2^n bytes wide: a 288-bit std::array<int, 9>
      // read is a 512-bit FIFO (N63: kernels w9r8p_mx_i9 29 = F(256 x 512),
      // mx_i3 96 -> 128 bits, mx_s5 80 -> 128; mx_i8 256 unchanged).
      unsigned unroundedReadBits = a.readBits;
      if (mc.readFifoPowerOfTwoWidth)
        a.readBits = std::min(
            static_cast<unsigned>(llvm::PowerOf2Ceil(a.readBits)), maxBits);
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
      } else if (a.cachedRead && mc.readCacheBram > 0) {
        // A cached read port: the adapter's read cache replaces the read
        // FIFO sizing (VITIS_NOTES N179: 29 whatever lines / depth / width /
        // outstanding reads, kernels w9r23p_x1 / x3 / x4 / x6).
        a.readBram = static_cast<unsigned>(mc.readCacheBram);
        a.readRule = "#pragma HLS cache on a reading port: read cache of " +
                     std::to_string(mc.readCacheBram) +
                     " blocks in place of the read FIFO (N179)";
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
        if (unroundedReadBits != a.busBits)
          a.readRule += "; " + std::to_string(unroundedReadBits) +
                        " bits wide: a load through a pointer cast (N56)";
        if (a.readBits != unroundedReadBits)
          a.readRule += "; " + std::to_string(unroundedReadBits) +
                        " bits rounded up to " + std::to_string(a.readBits) +
                        " (a power of two, N63)";
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
      } else if (mc.writeBufferMinBramBits > 0 &&
                 a.writeBurst * static_cast<int64_t>(std::min(
                                    a.elementBits, maxBits)) <
                     mc.writeBufferMinBramBits) {
        // write_buffer.min_bram_bits: burst x element bits below it is
        // LUTRAM (N158: 32 x 16-bit short 0 BRAM, 32 x 32-bit int 2).
        a.writeBram = 0;
        a.writeRule = std::to_string(a.writeBurst) + " x " +
                      std::to_string(std::min(a.elementBits, maxBits)) +
                      " bits < " + std::to_string(mc.writeBufferMinBramBits) +
                      ": LUTRAM write buffer, 0 BRAM (N158)";
      } else {
        // write_buffer.element_width (N158 (b)): W is the widest element,
        // not padded to the bus minimum (64 x short and 128 x char: 1 BRAM,
        // 32 x int: 2; kernels w9r21rev_r7a / r7b, w9r21p_i2).
        unsigned w = a.busBits;
        if (mc.writeBufferElementWidth && a.elementBits > 0)
          w = std::min(a.elementBits, maxBits);
        a.writeBram =
            static_cast<unsigned>(ceilDiv(w, mc.writeBufferPortWidthBits));
        a.writeRule = "max_write_burst_length > " +
                      std::to_string(mc.writeBufferFreeMaxBurst) +
                      ": ceil(" + std::to_string(w) + "/" +
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
