//===- DataflowChannels.cpp - dataflow ping-pong channels -----------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// What Vitis 2025.1 does with the local arrays of a dataflow region, as
// measured on minimal kernels (one region, a producer and a consumer per
// channel, one property varied at a time) and on every dataflow design of the
// corpus:
//
//   - The processes are the region's calls and its loops (Vitis turns each
//     loop into a `Loop_*_proc`). A local or static array that one process
//     writes and a later process reads is a ping-pong channel. Not a channel:
//     an argument of the region (the processes touching it are merged), an
//     array the consumer also writes (merged into one process, an ordinary
//     memory), a completely partitioned array (registers), an array declared
//     as a stream FIFO. Two readers are merged into one reader process.
//   - Blocks: the depth of a `stream type=pipo` pragma, else 2, except 1 when
//     the region is a function that is not the top and none of whose direct
//     callers is a dataflow region (its invocations can never overlap; Vitis
//     warns "Consider increasing the depth of PIPO ... to 2").
//   - Separate memory per block exactly when some process drives a second
//     port of the channel (two accesses that can happen in one cycle) or the
//     channel is bound to ram_2p / ram_s2p; otherwise one memory of N x D
//     words. A single memory is a true-dual-port RAM, one port per side, so
//     it never uses the x36 mode; each separate block is x18 unless bound to
//     ram_2p / ram_s2p with one port per process (x36 up to 512 words).
//   - Below 1024 bits (N x D x W for a single memory, D x W per block
//     otherwise) the memory is distributed RAM; impl=lutram is always
//     distributed RAM. A channel is never replicated: more reads per cycle
//     raise the consumer's II.
//
//===----------------------------------------------------------------------===//

#include "circt/Dialect/Resource/Passes/DataflowChannels.h"
#include "circt/Dialect/Resource/Interfaces/MemoryDS.h"
#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/Dialect/MemRef/IR/MemRef.h"
#include "mlir/IR/BuiltinAttributes.h"
#include "mlir/IR/BuiltinOps.h"
#include "mlir/IR/SymbolTable.h"
#include "mlir/Interfaces/CallInterfaces.h"
#include "mlir/Interfaces/LoopLikeInterface.h"
#include "llvm/ADT/DenseMap.h"
#include "llvm/Support/raw_ostream.h"

using namespace mlir;

namespace circt::hls_analysis {
namespace {

bool isDataflowRegion(Operation *op) {
  return op->hasAttr(kDataflowAttr) &&
         (isa<func::FuncOp>(op) || isa<LoopLikeOpInterface>(op));
}

// The innermost dataflow region around `op`, or null.
Operation *enclosingRegion(Operation *op) {
  for (Operation *cur = op->getParentOp(); cur; cur = cur->getParentOp()) {
    if (isDataflowRegion(cur))
      return cur;
    if (isa<func::FuncOp>(cur))
      return nullptr;
  }
  return nullptr;
}

std::string locText(Location loc) {
  std::string s;
  llvm::raw_string_ostream os(s);
  loc.print(os);
  return s;
}

std::string processName(Operation *op) {
  std::string s;
  if (auto call = dyn_cast<CallOpInterface>(op)) {
    s = "call";
    if (auto sym = dyn_cast_if_present<SymbolRefAttr>(
            call.getCallableForCallee()))
      s += " @" + sym.getLeafReference().str();
  } else {
    s = op->getName().getStringRef().str();
  }
  return s + " @ " + locText(op->getLoc());
}

bool isProcessOp(Operation &op) {
  return isa<CallOpInterface>(op) || op.getNumRegions() > 0;
}

// The process of the region body `body` that `anchor` belongs to: its
// ancestor directly in the body. A straight-line op of the body (an access
// --convert-affine-to-loopschedule hoisted in front of the loop it was
// invariant in) belongs to the next call or loop, else the previous one.
Operation *processOf(Operation *anchor, Operation *region) {
  Operation *cur = anchor;
  while (cur && cur->getParentOp() != region)
    cur = cur->getParentOp();
  if (!cur || isProcessOp(*cur))
    return cur;
  for (Operation *n = cur->getNextNode(); n; n = n->getNextNode())
    if (isProcessOp(*n) && !n->hasTrait<OpTrait::IsTerminator>())
      return n;
  for (Operation *p = cur->getPrevNode(); p; p = p->getPrevNode())
    if (isProcessOp(*p))
      return p;
  return cur;
}

std::string lower(StringRef s) { return s.lower(); }

// The dictionary of an `[{...}]` pragma attribute (the first entry).
DictionaryAttr pragmaDict(Operation *op, StringRef name) {
  if (auto arr = op->getAttrOfType<ArrayAttr>(name))
    for (Attribute a : arr)
      if (auto d = dyn_cast<DictionaryAttr>(a))
        return d;
  return {};
}

// Blocks of a channel of `region` without a depth pragma, and why.
std::pair<int64_t, std::string> structuralBlocks(Operation *region) {
  if (!isa<func::FuncOp>(region))
    return {2, "2: dataflow-in-loop body (one corpus design, no kernel: "
               "unconfirmed)"};
  auto fn = cast<func::FuncOp>(region);
  auto module = fn->getParentOfType<ModuleOp>();
  std::optional<SymbolTable::UseRange> uses =
      module ? SymbolTable::getSymbolUses(fn, module) : std::nullopt;
  std::string caller;
  bool anyCall = false;
  if (uses)
    for (const SymbolTable::SymbolUse &u : *uses) {
      Operation *user = u.getUser();
      if (!isa<CallOpInterface>(user))
        continue;
      anyCall = true;
      if (Operation *r = enclosingRegion(user)) {
        caller = isa<func::FuncOp>(r)
                     ? "@" + cast<func::FuncOp>(r).getName().str()
                     : "a dataflow loop @ " + locText(r->getLoc());
        break;
      }
    }
  if (!anyCall)
    return {2, "2: the region of the top function"};
  if (!caller.empty())
    return {2, "2: the region function is called from the dataflow region " +
                   caller};
  return {1, "1: the region function is not the top and none of its direct "
             "callers is a dataflow region, so two invocations never overlap"};
}

// Whether `fn` is called from nowhere in its module: the top function.
bool isTopFunction(func::FuncOp fn) {
  auto module = fn->getParentOfType<ModuleOp>();
  if (!module)
    return true;
  std::optional<SymbolTable::UseRange> uses =
      SymbolTable::getSymbolUses(fn, module);
  return !uses || llvm::none_of(*uses, [](const SymbolTable::SymbolUse &u) {
    return isa<CallOpInterface>(u.getUser());
  });
}

func::FuncOp regionFunction(Operation *region) {
  return isa<func::FuncOp>(region) ? cast<func::FuncOp>(region)
                                   : region->getParentOfType<func::FuncOp>();
}

} // namespace

Operation *ProcessMerges::find(RegionMerges &m, Operation *p) {
  auto it = m.parent.find(p);
  if (it == m.parent.end() || it->second == p)
    return p;
  Operation *root = find(m, it->second);
  it->second = root;
  return root;
}

// Two processes of a region that access one array the region receives from
// its caller are merged into one process (gnnbuilder gcn / gin / pna / sage:
// in every dataflow-in-loop region of the non-top `*_conv` functions,
// "[HLS 214-475] Merging processes ... due to reads on" the parameters
// `in_degree_table` and the input embedding table, 24 regions; the local
// arrays between the merged processes are ordinary memories of the merged
// process there). A top-level argument is a port: two processes reading it
// stay separate and share it, one port each.
ProcessMerges::RegionMerges &ProcessMerges::compute(Operation *region) {
  std::unique_ptr<RegionMerges> &slot = regions[region];
  if (slot)
    return *slot;
  slot = std::make_unique<RegionMerges>();
  RegionMerges &m = *slot;
  func::FuncOp fn = regionFunction(region);
  if (!fn || isTopFunction(fn) || fn.isExternal())
    return m;
  for (BlockArgument arg : fn.getArguments()) {
    if (!isa<BaseMemRefType>(arg.getType()))
      continue;
    SmallVector<Operation *> procs;
    for (const ChannelAccess &a : accessesOf(arg)) {
      if (enclosingRegion(a.anchor) != region)
        continue;
      Operation *p = processOf(a.anchor, region);
      if (p && !llvm::is_contained(procs, p))
        procs.push_back(p);
    }
    for (size_t i = 1; i < procs.size(); ++i) {
      Operation *ra = find(m, procs.front()), *rb = find(m, procs[i]);
      m.parent.try_emplace(ra, ra);
      m.parent.try_emplace(rb, rb);
      if (ra == rb)
        continue;
      m.parent[rb] = ra;
      std::string why = "both access parameter " +
                        std::to_string(arg.getArgNumber()) + " of @" +
                        fn.getName().str() +
                        ", an array the region receives from its caller";
      m.reason[procs.front()] = why;
      m.reason[procs[i]] = why;
    }
  }
  return m;
}

std::pair<Operation *, std::string>
ProcessMerges::groupOf(Operation *region, Operation *process) {
  RegionMerges &m = compute(region);
  Operation *root = find(m, process);
  return {root, m.reason.lookup(process)};
}

ChannelVerdict analyzeDataflowChannel(Operation *storage,
                                      ArrayRef<ChannelAccess> accesses,
                                      int64_t words, ProcessMerges *merges) {
  ChannelVerdict v;
  if (accesses.empty())
    return v;
  Operation *region = nullptr;
  for (const ChannelAccess &a : accesses) {
    Operation *r = enclosingRegion(a.anchor);
    if (!r || (region && r != region))
      return v; // not every access lies in one dataflow region
    region = r;
  }
  // A local array belongs to the region of its own function (cgeist places
  // the allocas of a loop body at the function entry).
  if (!isa<memref::GlobalOp>(storage)) {
    auto own = storage->getParentOfType<func::FuncOp>();
    auto regionFn = isa<func::FuncOp>(region)
                        ? cast<func::FuncOp>(region)
                        : region->getParentOfType<func::FuncOp>();
    if (own != regionFn)
      return v;
  }
  v.inRegion = true;

  DictionaryAttr stream = pragmaDict(storage, "hls.stream");
  std::string streamType;
  if (stream)
    if (auto t = stream.getAs<StringAttr>("type"))
      streamType = lower(t.getValue());
  if (!streamType.empty() && streamType != "pipo") {
    v.notChannelReason = "stream type=" + streamType +
                         ": not a ping-pong channel (a FIFO, or a channel "
                         "kind no kernel has measured)";
    return v;
  }
  if (words <= 1) {
    v.notChannelReason = "one word: a scalar, not a ping-pong channel";
    return v;
  }

  DataflowChannel ch;
  ch.region = region;
  if (auto fn = dyn_cast<func::FuncOp>(region)) {
    ch.regionKind = "function";
    ch.regionName = "@" + fn.getName().str();
  } else {
    ch.regionKind = "loop";
    ch.regionName = region->getName().getStringRef().str() + " @ " +
                    locText(region->getLoc());
  }

  // Processes in program order of the region body.
  llvm::DenseMap<Operation *, unsigned> procIndex;
  for (const ChannelAccess &a : accesses) {
    Operation *p = processOf(a.anchor, region);
    if (!p)
      return v;
    auto [it, inserted] = procIndex.try_emplace(p, ch.processes.size());
    if (inserted) {
      DataflowProcess dp;
      dp.op = p;
      dp.name = processName(p);
      ch.processes.push_back(std::move(dp));
    }
    DataflowProcess &dp = ch.processes[it->second];
    (a.isWrite ? dp.writes : dp.reads) = true;
  }
  {
    llvm::DenseMap<Operation *, unsigned> position;
    unsigned i = 0;
    for (Region &r : region->getRegions())
      for (Block &b : r)
        for (Operation &op : b)
          position[&op] = i++;
    for (DataflowProcess &p : ch.processes)
      p.position = position.lookup(p.op);
    llvm::stable_sort(ch.processes,
                      [](const DataflowProcess &a, const DataflowProcess &b) {
                        return a.position < b.position;
                      });
  }

  // A producer merged with a consumer: the array lives inside one process.
  if (merges) {
    for (const DataflowProcess &w : ch.processes) {
      if (!w.writes)
        continue;
      auto [wg, why] = merges->groupOf(region, w.op);
      for (const DataflowProcess &r : ch.processes) {
        if (&r == &w || !r.reads)
          continue;
        auto [rg, rwhy] = merges->groupOf(region, r.op);
        if (rg == wg) {
          v.notChannelReason =
              "its producer and a consumer are merged into one process (" +
              (why.empty() ? rwhy : why) + "): an ordinary memory";
          return v;
        }
      }
    }
  }

  unsigned writers = 0, readers = 0;
  const DataflowProcess *writer = nullptr;
  for (const DataflowProcess &p : ch.processes) {
    if (p.writes) {
      ++writers;
      writer = &p;
    }
  }
  if (writers != 1) {
    v.notChannelReason =
        writers == 0 ? "no process of the region writes it"
                     : std::to_string(writers) +
                           " processes write it (Vitis merges a consumer "
                           "that writes the channel into one process: an "
                           "ordinary memory)";
    return v;
  }
  for (const DataflowProcess &p : ch.processes) {
    if (&p == writer || !p.reads)
      continue;
    if (p.position < writer->position) {
      v.notChannelReason = "read by a process ahead of its producer";
      return v;
    }
    ++readers;
  }
  if (readers == 0) {
    v.notChannelReason = "read by no process after its producer";
    return v;
  }

  if (stream && stream.getAs<IntegerAttr>("depth")) {
    ch.blocks = std::max<int64_t>(1, stream.getAs<IntegerAttr>("depth").getInt());
    ch.blocksSource =
        std::to_string(ch.blocks) + ": stream type=pipo depth pragma";
  } else {
    std::tie(ch.blocks, ch.blocksSource) = structuralBlocks(region);
  }
  if (DictionaryAttr bind = pragmaDict(storage, "hls.bind_storage")) {
    if (auto t = bind.getAs<StringAttr>("type"))
      ch.bindType = lower(t.getValue());
    if (auto i = bind.getAs<StringAttr>("impl"))
      ch.bindImpl = lower(i.getValue());
  }
  v.channel = std::move(ch);
  return v;
}

ChannelPrice
priceChannel(int64_t words, unsigned bits, int64_t blocks, bool twoPorts,
             bool bound2p, bool lutram,
             llvm::function_ref<int64_t(int64_t, unsigned, bool)> blocksOf) {
  ChannelPrice p;
  std::string geom = std::to_string(words) + "x" + std::to_string(bits);
  int64_t bankBits = words * static_cast<int64_t>(bits);
  if (lutram) {
    p.mode = "lutram";
    p.rule = "bind_storage impl=lutram: distributed RAM, 0 BRAM";
    return p;
  }
  if (blocks <= 1) {
    p.mode = "one block";
    if (bankBits < kBRAMPromotionBits) {
      p.rule = geom + " < 1024 bits: distributed RAM, 0 BRAM";
      return p;
    }
    bool sdp = !twoPorts;
    p.bram = static_cast<unsigned>(blocksOf(words, bits, sdp));
    p.rule = "one block, an ordinary memory: F(" + geom + ") at " +
             (sdp ? "x36 allowed (one port per process)"
                  : "x18 (a process drives two ports)") +
             " = " + std::to_string(p.bram);
    return p;
  }
  if (twoPorts || bound2p) {
    p.mode = "separate";
    if (bankBits < kBRAMPromotionBits) {
      p.rule = "separate, " + geom + " per block < 1024 bits: distributed "
               "RAM, 0 BRAM";
      return p;
    }
    bool sdp = bound2p && !twoPorts;
    int64_t each = blocksOf(words, bits, sdp);
    p.bram = static_cast<unsigned>(blocks * each);
    p.rule = "separate: " + std::to_string(blocks) + " x F(" + geom + ") at " +
             (sdp ? "x36 allowed (bound ram_2p / ram_s2p, one port per "
                    "process)"
                  : "x18") +
             " = " + std::to_string(blocks) + " x " + std::to_string(each) +
             " = " + std::to_string(p.bram);
    return p;
  }
  p.mode = "single";
  int64_t allWords = blocks * words;
  std::string all = std::to_string(allWords) + "x" + std::to_string(bits);
  if (allWords * static_cast<int64_t>(bits) < kBRAMPromotionBits) {
    p.rule = "single memory of " + all + " < 1024 bits: distributed RAM, 0 "
             "BRAM";
    return p;
  }
  p.bram = static_cast<unsigned>(blocksOf(allWords, bits, /*sdp=*/false));
  p.rule = "single memory of all " + std::to_string(blocks) + " blocks: F(" +
           all + ") at x18 (true dual port, one port per side) = " +
           std::to_string(p.bram);
  return p;
}

} // namespace circt::hls_analysis
