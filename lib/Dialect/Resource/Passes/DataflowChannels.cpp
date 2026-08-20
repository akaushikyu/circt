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
//     an argument of the region (the processes touching it are merged), a
//     completely partitioned array (registers), an array declared as a
//     stream FIFO. Two readers are merged into one reader process.
//   - All processes that write one local array or stream are merged into one
//     process, together with every process on a dependence path from one of
//     them to another. An array whose writers are merged is still a channel
//     when a process outside the merged group reads it; an array whose every
//     accessor lies in one merged process is an ordinary memory of it.
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
#include "circt/Dialect/Resource/Passes/StreamFifos.h"
#include "circt/Dialect/Resource/Interfaces/MemoryDS.h"
#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/Dialect/MemRef/IR/MemRef.h"
#include "mlir/IR/BuiltinAttributes.h"
#include "mlir/IR/BuiltinOps.h"
#include "mlir/IR/SymbolTable.h"
#include "mlir/Interfaces/CallInterfaces.h"
#include "mlir/Interfaces/LoopLikeInterface.h"
#include "mlir/Interfaces/ViewLikeInterface.h"
#include "llvm/ADT/DenseSet.h"
#include "llvm/ADT/MapVector.h"
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

namespace {

// Positions of the ops of the region body, in program order.
llvm::DenseMap<Operation *, unsigned> bodyPositions(Operation *region) {
  llvm::DenseMap<Operation *, unsigned> position;
  unsigned i = 0;
  for (Region &r : region->getRegions())
    for (Block &b : r)
      for (Operation &op : b)
        position[&op] = i++;
  return position;
}

// The name the reports give a storage: its source variable when the front end
// recorded one.
std::string storageName(Operation *storage) {
  if (auto v = storage->getAttrOfType<StringAttr>("polygeist.varname"))
    return v.getValue().str();
  if (auto g = dyn_cast<memref::GlobalOp>(storage))
    return g.getSymName().str();
  return storage->getName().getStringRef().str() + " @ " +
         locText(storage->getLoc());
}

// Whether an hls::stream method reads or writes the stream; nullopt for the
// others (constructors, empty(), full(), size()).
std::optional<bool> streamMethodWrites(StringRef method) {
  if (method.starts_with("5write") || method.starts_with("8write_nb") ||
      method.starts_with("ls"))
    return true;
  if (method.starts_with("4read") || method.starts_with("7read_nb") ||
      method.starts_with("rs"))
    return false;
  return std::nullopt;
}

bool isHandleView(Operation *op, Value source) {
  StringRef name = op->getName().getStringRef();
  if (name == "polygeist.subindex" || name == "polygeist.memref2pointer" ||
      name == "polygeist.pointer2memref" || name == "llvm.bitcast" ||
      name == "llvm.addrspacecast" || name == "llvm.getelementptr" ||
      isa<memref::CastOp>(op))
    return true;
  if (auto v = dyn_cast<ViewLikeOpInterface>(op))
    return v.getViewSource() == source;
  return false;
}

// The hls::stream reads and writes reached from the handle values `roots`
// (directly, through views and pointer casts, or through the parameters of
// the callees they are passed to), each anchored at the outermost call
// through which it is reached.
SmallVector<ChannelAccess> streamAccesses(ArrayRef<Value> roots) {
  SmallVector<ChannelAccess> out;
  SmallVector<std::pair<Value, Operation *>> work; // (value, via)
  llvm::DenseSet<std::pair<void *, Operation *>> seen;
  auto push = [&](Value v, Operation *via) {
    if (seen.insert({v.getAsOpaquePointer(), via}).second)
      work.push_back({v, via});
  };
  for (Value r : roots)
    push(r, nullptr);
  while (!work.empty()) {
    auto [cur, via] = work.pop_back_val();
    for (OpOperand &use : cur.getUses()) {
      Operation *user = use.getOwner();
      if (auto call = dyn_cast<CallOpInterface>(user)) {
        auto args = call.getArgOperands();
        unsigned first = args.getBeginOperandIndex();
        unsigned n = use.getOperandNumber();
        if (n < first || n - first >= args.size())
          continue;
        unsigned argIndex = n - first;
        auto sym = dyn_cast_if_present<SymbolRefAttr>(
            call.getCallableForCallee());
        if (sym)
          if (auto t = parseStreamMethod(sym.getLeafReference().getValue())) {
            if (argIndex == 0)
              if (std::optional<bool> w = streamMethodWrites(t->method))
                out.push_back({via ? via : user, *w});
            continue;
          }
        auto callee = dyn_cast_or_null<func::FuncOp>(call.resolveCallable());
        if (callee && !callee.isExternal() &&
            argIndex < callee.getNumArguments())
          push(callee.getArgument(argIndex), via ? via : user);
        continue;
      }
      if (isHandleView(user, cur))
        for (Value r : user->getResults())
          push(r, via);
    }
  }
  return out;
}

// One region-local storage and the processes of the region that touch it.
struct StorageUse {
  std::string name;
  bool stream = false;
  struct Use {
    Operation *process;
    bool reads = false, writes = false;
  };
  SmallVector<Use> uses; // first-access order
};

} // namespace

Operation *ProcessMerges::find(RegionMerges &m, Operation *p) {
  auto it = m.parent.find(p);
  if (it == m.parent.end() || it->second == p)
    return p;
  Operation *root = find(m, it->second);
  m.parent[p] = root;
  return root;
}

bool ProcessMerges::unite(RegionMerges &m, Operation *a, Operation *b) {
  Operation *ra = find(m, a), *rb = find(m, b);
  if (ra == rb)
    return false;
  m.parent.try_emplace(ra, ra);
  m.parent[rb] = ra;
  return true;
}

static void addReason(llvm::DenseMap<Operation *, std::string> &reasons,
                      Operation *p, const std::string &why) {
  std::string &r = reasons[p];
  if (r.find(why) != std::string::npos)
    return;
  if (!r.empty())
    r += "; ";
  r += why;
}

// Two processes of a region that access one array the region receives from
// its caller are merged into one process (gnnbuilder gcn / gin / pna / sage:
// in every dataflow-in-loop region of the non-top `*_conv` functions,
// "[HLS 214-475] Merging processes ... due to reads on" the parameters
// `in_degree_table` and the input embedding table, 24 regions; the local
// arrays between the merged processes are ordinary memories of the merged
// process there). A top-level argument is a port: two processes reading it
// stay separate and share it, one port each.
void ProcessMerges::mergeOnParameters(Operation *region, RegionMerges &m) {
  func::FuncOp fn = regionFunction(region);
  if (!fn || isTopFunction(fn) || fn.isExternal())
    return;
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
    std::string why = "both access parameter " +
                      std::to_string(arg.getArgNumber()) + " of @" +
                      fn.getName().str() +
                      ", an array the region receives from its caller";
    for (size_t i = 1; i < procs.size(); ++i)
      if (unite(m, procs.front(), procs[i])) {
        addReason(m.reason, procs.front(), why);
        addReason(m.reason, procs[i], why);
      }
  }
}

// Vitis merges all processes of a dataflow region that write one local array
// into one process ("[HLS 214-475] Merging processes 'P2' and 'P1' ... due to
// writes on 'buf'"), loops and calls alike and whatever the writes are (zero
// fill and partial copy, conditional, read-modify-write; kernels w9m_ll2,
// ff2, cond, rmw), and with them every process on a dependence path from one
// of the merged processes to another: a reader of the array between two
// writers (w9m_rwr), a process linked through another array (w9m_cyc) or
// through streams (w9m_strm). A process between the writers in program order
// with no such path stays apart (w9m_betw), and so does one that depends on
// only one writer (w9v_m_half): the closure follows dependences, not program
// order. Merges chain across arrays (w9m_trans). Streams merge like arrays.
// Not modelled, because no kernel decides them: a scalar passed between
// processes (cgeist's one-word memref) as a merge or path carrier, and the
// region's own arguments as path carriers.
void ProcessMerges::mergeWritersAndPaths(Operation *region, RegionMerges &m) {
  func::FuncOp fn = regionFunction(region);
  if (!fn || fn.isExternal())
    return;
  auto module = fn->getParentOfType<ModuleOp>();

  // The region-local storages: allocas of the region function and globals
  // only it uses (a static local), whose every access lies in the region.
  SmallVector<std::pair<Operation *, SmallVector<Value>>> storages;
  fn.walk([&](Operation *op) {
    if (isa<memref::AllocaOp, memref::AllocOp>(op))
      storages.push_back({op, {op->getResult(0)}});
  });
  if (module) {
    llvm::MapVector<StringRef, SmallVector<Value>> globals;
    fn.walk([&](memref::GetGlobalOp g) {
      globals[g.getName()].push_back(g.getResult());
    });
    for (auto &[sym, sites] : globals) {
      auto g = SymbolTable::lookupNearestSymbolFrom<memref::GlobalOp>(
          module, StringAttr::get(module.getContext(), sym));
      if (!g || g.getConstant())
        continue;
      std::optional<SymbolTable::UseRange> uses =
          SymbolTable::getSymbolUses(g, module);
      if (!uses || llvm::any_of(*uses, [&](const SymbolTable::SymbolUse &u) {
            return u.getUser()->getParentOfType<func::FuncOp>() != fn;
          }))
        continue;
      storages.push_back({g.getOperation(), sites});
    }
  }

  SmallVector<StorageUse> used;
  for (auto &[storage, sites] : storages) {
    StorageUse su;
    su.name = storageName(storage);
    SmallVector<ChannelAccess> accesses = streamAccesses(sites);
    su.stream = !accesses.empty();
    if (!su.stream) {
      auto type = dyn_cast<MemRefType>(sites.front().getType());
      if (!type || !type.hasStaticShape() || type.getNumElements() <= 1)
        continue; // a scalar, or an array of unknown size
      for (Value v : sites)
        llvm::append_range(accesses, accessesOf(v));
    }
    bool local = true;
    for (const ChannelAccess &a : accesses) {
      if (enclosingRegion(a.anchor) != region) {
        local = false;
        break;
      }
      Operation *p = processOf(a.anchor, region);
      if (!p) {
        local = false;
        break;
      }
      auto it = llvm::find_if(
          su.uses, [&](const StorageUse::Use &u) { return u.process == p; });
      if (it == su.uses.end()) {
        su.uses.push_back({p});
        it = std::prev(su.uses.end());
      }
      (a.isWrite ? it->writes : it->reads) = true;
    }
    if (local && su.uses.size() >= 2)
      used.push_back(std::move(su));
  }

  // The writers of one storage become one process.
  for (const StorageUse &su : used) {
    Operation *first = nullptr;
    for (const StorageUse::Use &u : su.uses) {
      if (!u.writes)
        continue;
      if (!first) {
        first = u.process;
        continue;
      }
      std::string why = "writes on '" + su.name + "'";
      if (unite(m, first, u.process) ||
          !m.reason.count(u.process)) {
        addReason(m.reason, first, why);
        addReason(m.reason, u.process, why);
      }
    }
  }

  // The dependences between processes: P -> Q for P before Q in program order
  // touching one array that one of them writes; for a stream, from each
  // writer to each reader.
  SmallVector<std::pair<Operation *, Operation *>> edges;
  for (const StorageUse &su : used)
    for (const StorageUse::Use &a : su.uses)
      for (const StorageUse::Use &b : su.uses) {
        if (a.process == b.process)
          continue;
        bool dep = su.stream ? a.writes && b.reads
                             : m.position.lookup(a.process) <
                                       m.position.lookup(b.process) &&
                                   (a.writes || b.writes);
        if (dep)
          edges.push_back({a.process, b.process});
      }

  // Contract the merged groups and pull in every process that lies on a
  // path from a group back to itself, until no group changes.
  for (bool changed = true; changed;) {
    changed = false;
    llvm::MapVector<Operation *, SmallVector<Operation *>> succ;
    for (auto [a, b] : edges) {
      Operation *ra = find(m, a), *rb = find(m, b);
      if (ra != rb && !llvm::is_contained(succ[ra], rb))
        succ[ra].push_back(rb);
      succ.insert({rb, {}});
    }
    auto reach = [&](Operation *from) {
      llvm::DenseSet<Operation *> seen;
      SmallVector<Operation *> work{from};
      while (!work.empty()) {
        Operation *cur = work.pop_back_val();
        auto it = succ.find(cur);
        if (it == succ.end())
          continue;
        for (Operation *n : it->second)
          if (seen.insert(n).second)
            work.push_back(n);
      }
      return seen;
    };
    llvm::DenseMap<Operation *, llvm::DenseSet<Operation *>> reachable;
    for (auto &entry : succ)
      reachable[entry.first] = reach(entry.first);
    for (auto &entry : succ) {
      Operation *g = entry.first;
      for (Operation *x : reachable.find(g)->second) {
        if (x == g || !reachable.find(x)->second.contains(g))
          continue;
        changed = unite(m, g, x) || changed;
      }
      if (changed)
        break; // the contracted graph changed: rebuild it
    }
  }
  // A process the closure pulled in has no reason of its own yet.
  SmallVector<Operation *> members;
  for (auto &entry : m.parent)
    members.push_back(entry.first);
  for (Operation *p : members)
    if (!m.reason.count(p))
      m.reason[p] = "on a dependence path from one process of the merged "
                    "group to another";
}

ProcessMerges::RegionMerges &ProcessMerges::compute(Operation *region) {
  std::unique_ptr<RegionMerges> &slot = regions[region];
  if (slot)
    return *slot;
  slot = std::make_unique<RegionMerges>();
  RegionMerges &m = *slot;
  m.position = bodyPositions(region);
  mergeOnParameters(region, m);
  mergeWritersAndPaths(region, m);
  return m;
}

std::pair<Operation *, std::string>
ProcessMerges::groupOf(Operation *region, Operation *process) {
  RegionMerges &m = compute(region);
  Operation *root = find(m, process);
  return {root, m.reason.lookup(process)};
}

Operation *ProcessMerges::groupLeader(Operation *region, Operation *process) {
  RegionMerges &m = compute(region);
  Operation *root = find(m, process);
  Operation *leader = process;
  for (auto &entry : m.parent)
    if (find(m, entry.first) == root &&
        m.position.lookup(entry.first) < m.position.lookup(leader))
      leader = entry.first;
  return leader;
}

bool ProcessMerges::isMerged(Operation *region, Operation *process) {
  RegionMerges &m = compute(region);
  Operation *root = find(m, process);
  if (root != process)
    return true;
  for (auto &entry : m.parent)
    if (entry.first != process && find(m, entry.first) == root)
      return true;
  return false;
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

  // Merged processes act as one: the writers of a region-local array are
  // always one process, and the array is a channel exactly when a process
  // outside that group reads it; when the group takes in every accessor it is
  // an ordinary memory of the merged process (pipo_m_crw, w9m_inner).
  auto groupKey = [&](const DataflowProcess &p) -> Operation * {
    return merges ? merges->groupOf(region, p.op).first : p.op;
  };
  if (merges)
    for (DataflowProcess &p : ch.processes)
      if (merges->isMerged(region, p.op)) {
        p.group = processName(merges->groupLeader(region, p.op));
        p.mergeReason = merges->groupOf(region, p.op).second;
      }
  SmallVector<Operation *> writerGroups;
  const DataflowProcess *firstWriter = nullptr;
  for (const DataflowProcess &p : ch.processes)
    if (p.writes) {
      if (!firstWriter)
        firstWriter = &p;
      if (!llvm::is_contained(writerGroups, groupKey(p)))
        writerGroups.push_back(groupKey(p));
    }
  if (writerGroups.size() != 1) {
    v.notChannelReason =
        writerGroups.empty()
            ? "no process of the region writes it"
            : std::to_string(writerGroups.size()) +
                  " processes write it (Vitis merges a consumer "
                  "that writes the channel into one process: an "
                  "ordinary memory)";
    return v;
  }
  Operation *writerGroup = writerGroups.front();
  unsigned readers = 0;
  bool readInsideGroup = false;
  for (const DataflowProcess &p : ch.processes) {
    if (!p.reads)
      continue;
    if (groupKey(p) == writerGroup) {
      readInsideGroup = true;
      continue;
    }
    if (p.position < firstWriter->position) {
      v.notChannelReason = "read by a process ahead of its producer";
      return v;
    }
    ++readers;
  }
  if (readers == 0) {
    const DataflowProcess &w = *firstWriter;
    if (!w.group.empty() && readInsideGroup)
      v.notChannelReason = "every process that accesses it is merged into "
                           "one process (" + w.group + ": " +
                           w.mergeReason + "): an ordinary memory";
    else
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
