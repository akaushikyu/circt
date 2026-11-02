//===- CallInstances.cpp - non-inlined callees as Vitis instantiates them -===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// See CallInstances.h. Evidence: VITIS_NOTES.md N14 (kernels
// ~/hls-est-work/exp-src/inline/inl_*.cpp, runs experiments/inl_*).
//
//===----------------------------------------------------------------------===//

#include "circt/Dialect/Resource/Passes/CallInstances.h"
#include <vector>
#include <tuple>
#include <set>
#include "circt/Dialect/Resource/Interfaces/MemoryDS.h"
#include "circt/Dialect/Resource/Passes/ReadOnlyMemory.h"
#include "circt/Dialect/Resource/Config/Config.h"
#include "circt/Dialect/Resource/Passes/PartitionLayout.h"
#include "circt/Dialect/LoopSchedule/LoopScheduleOps.h"
#include "circt/Dialect/Resource/Passes/LoopPragmas.h"
#include "circt/Dialect/Resource/Passes/ConstantIndex.h"
#include "circt/Dialect/Resource/Passes/FunctionPipelines.h"
#include "circt/Dialect/Resource/Passes/PolygeistCompat.h"
#include "circt/Dialect/Resource/Passes/StreamFifos.h"
#include "mlir/Dialect/Affine/IR/AffineOps.h"
#include "mlir/Dialect/MemRef/IR/MemRef.h"
#include "mlir/Dialect/SCF/IR/SCF.h"
#include "mlir/IR/SymbolTable.h"
#include "mlir/Interfaces/LoopLikeInterface.h"
#include "mlir/Interfaces/SideEffectInterfaces.h"
#include "mlir/Interfaces/ViewLikeInterface.h"
#include "llvm/ADT/BitVector.h"
#include "llvm/ADT/DenseSet.h"
#include "llvm/ADT/MapVector.h"
#include "llvm/ADT/SmallPtrSet.h"

#include <functional>

using namespace mlir;

namespace circt::hls_analysis {

func::FuncOp resolveDefinedCallee(CallOpInterface call) {
  auto callee = dyn_cast_or_null<func::FuncOp>(call.resolveCallable());
  if (!callee || callee.isExternal())
    return nullptr;
  return callee;
}

std::optional<unsigned> callArgIndex(CallOpInterface call, OpOperand &operand) {
  if (operand.getOwner() != call.getOperation())
    return std::nullopt;
  MutableOperandRange args = call.getArgOperandsMutable();
  unsigned first = args.getAsOperandRange().getBeginOperandIndex();
  unsigned n = operand.getOperandNumber();
  if (args.size() == 0 || n < first || n - first >= args.size())
    return std::nullopt;
  return n - first;
}

StorageRoot storageRoot(Value mem) {
  while (true) {
    Operation *def = mem.getDefiningOp();
    if (!def)
      return {mem, nullptr};
    if (auto gg = dyn_cast<memref::GetGlobalOp>(def)) {
      Operation *sym = SymbolTable::lookupNearestSymbolFrom(
          def, gg.getNameAttr());
      if (auto g = dyn_cast_or_null<memref::GlobalOp>(sym))
        return {Value(), g.getOperation()};
      return {mem, nullptr};
    }
    if (auto view = dyn_cast<ViewLikeOpInterface>(def)) {
      Value src = view.getViewSource();
      if (src && isa<BaseMemRefType>(src.getType())) {
        mem = src;
        continue;
      }
    }
    return {mem, nullptr};
  }
}

std::optional<int64_t> allocationLimit(func::FuncOp parent,
                                       func::FuncOp callee) {
  auto arr = parent->getAttrOfType<ArrayAttr>(kAllocationAttr);
  if (!arr)
    return std::nullopt;
  StringRef orig;
  if (auto o = callee->getAttrOfType<StringAttr>(kOrigNameAttr))
    orig = o.getValue();
  std::optional<int64_t> best;
  for (Attribute a : arr) {
    auto d = dyn_cast<DictionaryAttr>(a);
    if (!d)
      continue;
    if (auto t = d.getAs<StringAttr>("type"))
      if (t.getValue() != "function")
        continue;
    auto lim = d.getAs<IntegerAttr>("limit");
    if (!lim || lim.getInt() <= 0)
      continue;
    auto names = d.getAs<ArrayAttr>("instances");
    bool named = false;
    if (names) {
      for (Attribute n : names)
        if (auto s = dyn_cast<StringAttr>(n))
          if ((!orig.empty() && s.getValue() == orig) ||
              s.getValue() == callee.getName()) {
            named = true;
            break;
          }
    } else if (auto s = d.getAs<StringAttr>("instances")) {
      named = (!orig.empty() && s.getValue() == orig) ||
              s.getValue() == callee.getName();
    }
    if (!named)
      continue;
    if (!best || lim.getInt() < *best)
      best = lim.getInt();
  }
  return best;
}

namespace {
/// The region of `anc` that contains `op` (`anc` a proper ancestor of `op`).
static Region *regionUnder(Operation *op, Operation *anc) {
  for (Region *r = op->getParentRegion(); r; ) {
    Operation *owner = r->getParentOp();
    if (owner == anc)
      return r;
    if (!owner)
      return nullptr;
    r = owner->getParentRegion();
  }
  return nullptr;
}

/// Whether `a` and `b` can never run in one execution of their nearest
/// common ancestor: it is a conditional (scf.if, affine.if, scf.index_switch)
/// and they lie in different regions of it (W3 review 2 D1, w3r2_k5:
/// `if (sel) work(a, b); else work(c, d);`, Vitis 1 instance, 4 BRAM).
static bool mutuallyExclusive(Operation *a, Operation *b) {
  // Moved out of the arms by --convert-affine-to-loopschedule's if hoisting,
  // which records [if id, arm, ...] in hls.if_arms.
  auto armsOf = [](Operation *op) -> ArrayRef<int64_t> {
    if (auto at = op->getAttrOfType<DenseI64ArrayAttr>(kIfArmsAttr))
      return at.asArrayRef();
    return {};
  };
  ArrayRef<int64_t> ha = armsOf(a), hb = armsOf(b);
  for (size_t x = 0; x + 1 < ha.size(); x += 2)
    for (size_t y = 0; y + 1 < hb.size(); y += 2)
      if (ha[x] == hb[y] && ha[x + 1] != hb[y + 1])
        return true;
  for (Operation *p = a->getParentOp(); p; p = p->getParentOp()) {
    if (!p->isProperAncestor(b))
      continue;
    if (!isa<scf::IfOp, affine::AffineIfOp, scf::IndexSwitchOp>(p))
      return false;
    Region *ra = regionUnder(a, p), *rb = regionUnder(b, p);
    return ra && rb && ra != rb;
  }
  return false;
}

/// Minimum chain cover of the preorder `reach` (reach[i][j]: site i comes
/// before site j; transitively closed). Sites that reach each other (an
/// ordering around a loop) form one node; the width of the resulting partial
/// order is the number of chains (Dilworth: nodes - maximum matching of the
/// bipartite graph "a before b"). Returns the chain of each site, numbered in
/// order of the chains' first site.
static unsigned chainCover(ArrayRef<llvm::BitVector> reach,
                           SmallVectorImpl<unsigned> &chainOf) {
  unsigned n = reach.size();
  // Strongly connected classes: the first site of each class represents it.
  SmallVector<unsigned> rep(n);
  SmallVector<unsigned> nodes;
  for (unsigned i = 0; i < n; ++i) {
    rep[i] = i;
    for (unsigned r : nodes)
      if (reach[i].test(r) && reach[r].test(i)) {
        rep[i] = r;
        break;
      }
    if (rep[i] == i)
      nodes.push_back(i);
  }
  unsigned m = nodes.size();
  // Kuhn's augmenting paths: matchR[b] = the node matched before b.
  SmallVector<int> matchR(m, -1), next(m, -1);
  SmallVector<char> visited;
  std::function<bool(unsigned)> augment = [&](unsigned a) -> bool {
    for (unsigned b = 0; b < m; ++b) {
      if (b == a || visited[b] || !reach[nodes[a]].test(nodes[b]))
        continue;
      visited[b] = 1;
      if (matchR[b] < 0 || augment(static_cast<unsigned>(matchR[b]))) {
        matchR[b] = static_cast<int>(a);
        return true;
      }
    }
    return false;
  };
  for (unsigned a = 0; a < m; ++a) {
    visited.assign(m, 0);
    (void)augment(a);
  }
  for (unsigned b = 0; b < m; ++b)
    if (matchR[b] >= 0)
      next[matchR[b]] = static_cast<int>(b);
  // Chains start at the nodes nothing is matched before.
  SmallVector<int> chainOfNode(m, -1);
  unsigned chains = 0;
  for (unsigned b = 0; b < m; ++b) {
    if (matchR[b] >= 0)
      continue;
    for (int c = static_cast<int>(b); c >= 0; c = next[c])
      chainOfNode[c] = static_cast<int>(chains);
    ++chains;
  }
  // Number the chains in order of their first site.
  DenseMap<unsigned, unsigned> renumber;
  chainOf.assign(n, 0);
  for (unsigned i = 0; i < n; ++i) {
    unsigned node = llvm::find(nodes, rep[i]) - nodes.begin();
    unsigned c = static_cast<unsigned>(chainOfNode[node]);
    auto it = renumber.try_emplace(c, renumber.size()).first;
    chainOf[i] = it->second;
  }
  return chains;
}

// Memref operands of an op with their storage roots.
static void memrefRoots(Operation *op, SmallVectorImpl<StorageRoot> &out) {
  for (Value v : op->getOperands())
    if (isa<BaseMemRefType>(v.getType()))
      out.push_back(storageRoot(v));
}

// The element `mem` selects of its storage root: the constant indices of the
// polygeist.subindex views on the way, outermost first; nullopt when another
// view, or a subindex with a non-constant index, lies on the way (the
// operand may touch any element).
static std::optional<SmallVector<int64_t, 2>>
constantElementPath(Value mem) {
  SmallVector<int64_t, 2> path;
  while (Operation *def = mem.getDefiningOp()) {
    if (isa<memref::GetGlobalOp>(def))
      break;
    auto view = dyn_cast<ViewLikeOpInterface>(def);
    if (!view)
      break;
    // A cast changes the static shape only (a callee cloned with the
    // static type, specializeCastArguments): the same elements.
    if (isa<memref::CastOp>(def)) {
      mem = view.getViewSource();
      continue;
    }
    if (!isa<circt::hls_analysis::SubIndexOp>(def))
      return std::nullopt;
    std::optional<int64_t> k = getConstantIndexValue(def->getOperand(1));
    if (!k)
      return std::nullopt;
    path.insert(path.begin(), *k);
    mem = view.getViewSource();
  }
  return path;
}

// The element operand `index` of `call` selects: constantElementPath of the
// operand, then, when --lower-polygeist-subindex replaced a view by the whole
// array and its index (a callee clone whose next parameter carries
// hls.view_index), that constant index too (`worker(s[id], s[id + 4])`, an
// element by reference: W9r7 review defect 6).
static std::optional<SmallVector<int64_t, 2>>
constantElementPathAt(Operation *call, unsigned index) {
  std::optional<SmallVector<int64_t, 2>> path =
      constantElementPath(call->getOperand(index));
  if (!path)
    return path;
  auto ci = dyn_cast<CallOpInterface>(call);
  auto callee = ci ? dyn_cast_or_null<func::FuncOp>(ci.resolveCallable())
                   : func::FuncOp();
  if (!callee || index + 1 >= callee.getNumArguments() ||
      index + 1 >= call->getNumOperands() ||
      !callee.getArgAttr(index + 1, circt::hls_analysis::kViewIndexArgAttr))
    return path;
  std::optional<int64_t> k = getConstantIndexValue(call->getOperand(index + 1));
  if (!k)
    return std::nullopt;
  path->push_back(*k);
  return path;
}

// Whether the elements of the memref `root` are hls::stream objects (an
// array of streams: every element its own FIFO, VITIS_NOTES N31): a use
// reaches a stream member, directly, through views, or through the
// parameters of defined callees.
static bool isStreamArray(Value root) {
  SmallVector<Value> work{root};
  DenseSet<Value> seen{root};
  while (!work.empty() && seen.size() < 256) {
    Value v = work.pop_back_val();
    for (OpOperand &use : v.getUses()) {
      Operation *user = use.getOwner();
      if (auto call = dyn_cast<CallOpInterface>(user)) {
        if (auto sym = dyn_cast_if_present<SymbolRefAttr>(
                call.getCallableForCallee()))
          if (parseStreamMethod(sym.getLeafReference().getValue()))
            return true;
        auto args = call.getArgOperands();
        unsigned first = args.getBeginOperandIndex();
        unsigned k = use.getOperandNumber();
        auto callee = dyn_cast_or_null<func::FuncOp>(call.resolveCallable());
        if (callee && !callee.isExternal() && k >= first &&
            k - first < callee.getNumArguments() &&
            seen.insert(callee.getArgument(k - first)).second)
          work.push_back(callee.getArgument(k - first));
        continue;
      }
      if (isa<ViewLikeOpInterface>(user))
        for (Value r : user->getResults())
          if (isa<BaseMemRefType>(r.getType()) && seen.insert(r).second)
            work.push_back(r);
    }
  }
  return false;
}

// Whether two call sites touch a common object: a memref operand of each
// with one storage root, unless the root is an array of streams and the two
// operands are distinct constant elements of it (VITIS_NOTES N59, kernel
// w9r7_ci_s4: `for (id < 4) worker(in[id], out[id])` unrolled are four
// concurrent instances; they touch distinct FIFOs).
static bool sharesObject(Operation *a, Operation *b,
                         DenseMap<Value, bool> &streamArrays) {
  for (OpOperand &ox : a->getOpOperands()) {
    Value x = ox.get();
    if (!isa<BaseMemRefType>(x.getType()))
      continue;
    StorageRoot rx = storageRoot(x);
    for (OpOperand &oy : b->getOpOperands()) {
      Value y = oy.get();
      if (!isa<BaseMemRefType>(y.getType()) || storageRoot(y) != rx)
        continue;
      if (rx.value) {
        auto [it, fresh] = streamArrays.try_emplace(rx.value, false);
        if (fresh)
          it->second = isStreamArray(rx.value);
        if (it->second) {
          auto px = constantElementPathAt(a, ox.getOperandNumber()),
               py = constantElementPathAt(b, oy.getOperandNumber());
          if (px && py) {
            bool differ = false;
            for (size_t k = 0, e = std::min(px->size(), py->size()); k < e;
                 ++k)
              differ |= (*px)[k] != (*py)[k];
            if (differ)
              continue; // distinct FIFOs
          }
        }
      }
      return true;
    }
  }
  return false;
}

// Whether `a` and `b` touch only distinct constant elements of the array of
// streams `root` (so a value one writes there is not what the other reads).
static bool distinctStreamElements(Operation *a, Operation *b,
                                   const StorageRoot &root,
                                   DenseMap<Value, bool> &streamArrays) {
  if (!root.value)
    return false;
  auto [it, fresh] = streamArrays.try_emplace(root.value, false);
  if (fresh)
    it->second = isStreamArray(root.value);
  if (!it->second)
    return false;
  SmallVector<SmallVector<int64_t, 2>> pa, pb;
  for (auto [op, paths] : {std::make_pair(a, &pa), std::make_pair(b, &pb)})
    for (OpOperand &o : op->getOpOperands()) {
      Value v = o.get();
      if (!isa<BaseMemRefType>(v.getType()) || storageRoot(v) != root)
        continue;
      auto path = constantElementPathAt(op, o.getOperandNumber());
      if (!path)
        return false;
      paths->push_back(*path);
    }
  if (pa.empty() || pb.empty())
    return false;
  for (const auto &x : pa)
    for (const auto &y : pb) {
      bool differ = false;
      for (size_t k = 0, e = std::min(x.size(), y.size()); k < e; ++k)
        differ |= x[k] != y[k];
      if (!differ)
        return false;
    }
  return true;
}

static bool hasRootIn(ArrayRef<StorageRoot> roots,
                      const SmallVectorImpl<StorageRoot> &set) {
  for (const StorageRoot &r : roots)
    for (const StorageRoot &s : set)
      if (r == s)
        return true;
  return false;
}

using ArgWriteMemo = DenseMap<std::pair<Operation *, unsigned>, bool>;

static bool calleeMayWriteArg(func::FuncOp callee, unsigned idx,
                              ArgWriteMemo &memo);

// Whether the memory `mem` names may be written through it: a write effect
// on it or a view of it (or a write effect without a value), an op without
// effect information that takes it, or a call that may write the argument
// it is passed as.
static bool mayBeWritten(Value mem, ArgWriteMemo &memo) {
  bool writes = false;
  SmallVector<Value> work{mem};
  DenseSet<Value> seen;
  while (!work.empty() && !writes) {
    Value cur = work.pop_back_val();
    if (!seen.insert(cur).second)
      continue;
    for (OpOperand &use : cur.getUses()) {
      Operation *user = use.getOwner();
      if (auto view = dyn_cast<ViewLikeOpInterface>(user)) {
        if (view.getViewSource() == cur)
          for (Value r : user->getResults())
            if (isa<BaseMemRefType>(r.getType()))
              work.push_back(r);
        continue;
      }
      if (auto call = dyn_cast<CallOpInterface>(user)) {
        func::FuncOp inner = resolveDefinedCallee(call);
        std::optional<unsigned> j = callArgIndex(call, use);
        if (!inner || !j || *j >= inner.getNumArguments() ||
            calleeMayWriteArg(inner, *j, memo)) {
          writes = true;
          break;
        }
        continue;
      }
      if (isa<func::ReturnOp>(user))
        continue;
      auto eff = dyn_cast<MemoryEffectOpInterface>(user);
      if (!eff) {
        writes = true;
        break;
      }
      SmallVector<MemoryEffects::EffectInstance> effects;
      eff.getEffects(effects);
      for (auto &e : effects)
        if ((e.getValue() == cur && !isa<MemoryEffects::Read>(e.getEffect())) ||
            (!e.getValue() && isa<MemoryEffects::Write>(e.getEffect())))
          writes = true;
    }
  }
  return writes;
}

// Whether a defined callee may write the memory its argument `idx` names
// (mayBeWritten on the argument). Memoized; a call cycle counts as a write.
static bool calleeMayWriteArg(func::FuncOp callee, unsigned idx,
                              ArgWriteMemo &memo) {
  auto key = std::make_pair(callee.getOperation(), idx);
  auto it = memo.find(key);
  if (it != memo.end())
    return it->second;
  memo[key] = true; // a cycle back to this argument: assume a write
  bool writes = mayBeWritten(callee.getArgument(idx), memo);
  memo[key] = writes;
  return writes;
}

// Whether `fn`, or a function it calls, writes a global (a static array):
// a memref.get_global site that may be written through.
static bool calleeWritesGlobal(func::FuncOp fn, ArgWriteMemo &memo,
                               SmallPtrSetImpl<Operation *> &visited) {
  if (!visited.insert(fn.getOperation()).second)
    return false;
  bool writes = false;
  fn.walk([&](Operation *op) {
    if (auto gg = dyn_cast<memref::GetGlobalOp>(op)) {
      writes = mayBeWritten(gg.getResult(), memo);
    } else if (auto call = dyn_cast<CallOpInterface>(op)) {
      if (func::FuncOp inner = resolveDefinedCallee(call))
        writes = calleeWritesGlobal(inner, memo, visited);
    }
    return writes ? WalkResult::interrupt() : WalkResult::advance();
  });
  return writes;
}

// Whether `op` reads (Read effect) or writes (Write effect) one of its
// memref operands whose root is in `roots`. A call to a defined callee:
// reads every such operand, writes it when the callee may write the
// argument (calleeMayWriteArg); any other call or op without effect
// information: reads and writes every such operand. A view (memref.cast,
// subview, ...) neither reads nor writes: the accesses through it do.
static void readsWrites(Operation *op, const SmallVectorImpl<StorageRoot> &roots,
                        bool &reads, bool &writes,
                        DenseMap<std::pair<Operation *, unsigned>, bool>
                            &argWrites) {
  reads = writes = false;
  if (isa<ViewLikeOpInterface>(op))
    return;
  SmallVector<Value, 4> mems;
  for (Value v : op->getOperands())
    if (isa<BaseMemRefType>(v.getType()))
      mems.push_back(v);
  if (mems.empty())
    return;
  auto inRoots = [&](Value v) {
    StorageRoot r = storageRoot(v);
    for (const StorageRoot &s : roots)
      if (r == s)
        return true;
    return false;
  };
  if (auto call = dyn_cast<CallOpInterface>(op)) {
    func::FuncOp callee = resolveDefinedCallee(call);
    for (OpOperand &operand : op->getOpOperands()) {
      Value v = operand.get();
      if (!isa<BaseMemRefType>(v.getType()) || !inRoots(v))
        continue;
      reads = true;
      std::optional<unsigned> idx = callArgIndex(call, operand);
      if (!callee || !idx || *idx >= callee.getNumArguments() ||
          calleeMayWriteArg(callee, *idx, argWrites))
        writes = true;
    }
    return;
  }
  auto eff = dyn_cast<MemoryEffectOpInterface>(op);
  if (!eff) {
    for (Value v : mems)
      if (inRoots(v)) {
        reads = writes = true;
        return;
      }
    return;
  }
  SmallVector<MemoryEffects::EffectInstance> effects;
  eff.getEffects(effects);
  for (auto &e : effects) {
    Value v = e.getValue();
    if (!v || !isa<BaseMemRefType>(v.getType()) || !inRoots(v))
      continue;
    if (isa<MemoryEffects::Read>(e.getEffect()))
      reads = true;
    else if (isa<MemoryEffects::Write>(e.getEffect()))
      writes = true;
  }
}
} // namespace

// The reads the data operands of `site` (a call's arguments, a math op's
// operands; not memref operands, which rule (i) covers) come from: every op
// reading through a memref operand that a data operand is computed from
// through side-effect-free ops, with the storage root it reads. Block
// arguments and other ops end the walk.
static void dataOperandMemories(
    Operation *site, SmallVectorImpl<std::pair<StorageRoot, Operation *>> &out) {
  SmallVector<Value, 8> work;
  if (auto call = dyn_cast<CallOpInterface>(site))
    work.append(call.getArgOperands().begin(), call.getArgOperands().end());
  else
    work.append(site->getOperands().begin(), site->getOperands().end());
  llvm::SmallPtrSet<Operation *, 32> seen;
  constexpr unsigned kMaxOps = 256; // argument expressions are small
  for (unsigned steps = 0; !work.empty() && steps < 4 * kMaxOps; ++steps) {
    Value v = work.pop_back_val();
    if (isa<BaseMemRefType>(v.getType()))
      continue;
    Operation *def = v.getDefiningOp();
    if (!def)
      continue;
    // A result of a single-block region op whose terminator forwards one
    // operand per result (a `loopschedule.pipeline.stage` and its
    // `loopschedule.register`): the value the terminator forwards.
    if (def->getNumRegions() == 1 && def->getRegion(0).hasOneBlock()) {
      Operation *term = def->getRegion(0).front().getTerminator();
      if (term && term->getNumOperands() == def->getNumResults()) {
        work.push_back(term->getOperand(cast<OpResult>(v).getResultNumber()));
        continue;
      }
    }
    if (!seen.insert(def).second || seen.size() > kMaxOps)
      continue;
    auto effects = dyn_cast<MemoryEffectOpInterface>(def);
    if (effects && effects.hasEffect<MemoryEffects::Read>()) {
      for (Value operand : def->getOperands())
        if (isa<BaseMemRefType>(operand.getType()))
          out.push_back({storageRoot(operand), def});
      continue;
    }
    if (!isMemoryEffectFree(def))
      continue;
    work.append(def->getOperands().begin(), def->getOperands().end());
  }
}

// The read ports of the memory `root` names: `ports` per memory, times the
// banks of an `hls.array_partition` on a function argument (the
// --memory-banking-bram pass splits allocas and globals into one root per
// bank, but not arguments). The accesses are assumed spread over the banks
// (N16 v4n: 4 unrolled copies over `cyclic factor=4` ports keep 4 cores).
static unsigned memoryReadPorts(const StorageRoot &root, unsigned ports) {
  auto arg = dyn_cast_or_null<BlockArgument>(root.value);
  if (!arg)
    return ports;
  auto fn = dyn_cast_or_null<func::FuncOp>(arg.getOwner()->getParentOp());
  auto type = dyn_cast<MemRefType>(arg.getType());
  if (!fn || !type || arg.getOwner() != &fn.getBody().front())
    return ports;
  auto spec = fn.getArgAttrOfType<ArrayAttr>(arg.getArgNumber(),
                                            "hls.array_partition");
  if (!spec)
    return ports;
  SmallVector<PartitionEntry, 2> entries;
  parsePartitionEntries(spec, "", entries);
  std::optional<BankLayout> layout = buildBankLayout(entries, type);
  if (!layout || layout->numBanks <= 1)
    return ports;
  return static_cast<unsigned>(std::min<int64_t>(
      layout->numBanks * static_cast<int64_t>(ports), 1 << 20));
}

/// The sequential loop of `parent` each call site lies in when Vitis
/// outlines it into a module of its own (VITIS_NOTES N14 R5: a loop that
/// holds a call, in a function that also calls a function outside every
/// loop; kernels inl_c7 / inl_c8 / inl_c11 outlined, inl_c1 / inl_c6 /
/// inl_c9 with calls only inside loops not), or null: the outermost loop
/// around the site that is neither pipelined nor completely unrolled. A
/// dataflow region keeps its processes (no outlining).
static void outlinedLoopDomains(func::FuncOp parent,
                                ArrayRef<Operation *> sites,
                                SmallVectorImpl<Operation *> &domain) {
  if (parent->hasAttr("hls.dataflow"))
    return;
  auto isLoop = [](Operation *op) {
    // loopschedule.pipeline: a loop --convert-affine-to-loopschedule
    // pipelined.
    if (!isa<LoopLikeOpInterface>(op))
      return false;
    if (op->hasAttr(kLoopPipelineAttr) && !op->hasAttr(kLoopPipelineOffAttr))
      return false; // a pipelined loop is a pipeline module, not R5's
    if (op->hasAttr(kLoopUnrollAttr))
      return false;
    return true;
  };
  auto outerLoop = [&](Operation *op) -> Operation * {
    Operation *outer = nullptr;
    for (Operation *p = op->getParentOp(); p && p != parent.getOperation();
         p = p->getParentOp())
      if (isLoop(p))
        outer = p;
    return outer;
  };
  auto anyLoop = [&](Operation *op) {
    for (Operation *p = op->getParentOp(); p && p != parent.getOperation();
         p = p->getParentOp())
      if (isa<LoopLikeOpInterface>(p) ||
          p->getName().getStringRef().starts_with("loopschedule."))
        return true;
    return false;
  };
  bool directCall = false;
  parent.getBody().walk([&](CallOpInterface call) {
    if (resolveDefinedCallee(call) && !anyLoop(call.getOperation()))
      directCall = true;
  });
  if (!directCall)
    return;
  for (unsigned i = 0; i < sites.size(); ++i)
    domain[i] = outerLoop(sites[i]);
}

unsigned groupConcurrentCalls(
    func::FuncOp parent, ArrayRef<Operation *> sites,
    std::optional<int64_t> limit, SmallVectorImpl<unsigned> &group,
    std::string *rule,
    llvm::function_ref<bool(unsigned, unsigned)> alsoOrdered) {
  unsigned n = sites.size();
  group.assign(n, 0);
  if (n == 0)
    return 0;
  // A dataflow region: every call in its body is a process of its own, and
  // the processes overlap, so no ordering lets two call sites share one
  // instance (VITIS_NOTES N48: soda erosion, 68 + 4 call sites of two
  // process functions -> 72 copies of their delay buffer). A call the
  // region's completely unrolled loop held is a process too: cgeist keeps
  // it (HLSAutoInline) and --auto-pipeline-unroll has copied it into the
  // region's body before this runs (kernel w9r6rev n48a: four `stage`
  // processes, 4 BRAM). Calls nested in a loop that stays are not
  // processes; they keep the sequential rule among themselves, and the
  // processes stay instances of their own next to them (unconfirmed: no
  // kernel mixes the two kinds for one callee yet).
  SmallVector<bool> isProcess(n, false);
  unsigned processes = 0;
  if (parent->hasAttr("hls.dataflow"))
    for (unsigned i = 0; i < n; ++i)
      if (isa<CallOpInterface>(sites[i]) &&
          sites[i]->getParentOp() == parent.getOperation()) {
        isProcess[i] = true;
        ++processes;
      }
  if (processes == n) {
    for (unsigned i = 0; i < n; ++i)
      group[i] = i;
    if (rule)
      *rule = std::to_string(n) + " call site(s) -> " + std::to_string(n) +
              " instance(s) (dataflow region: every call site is a process "
              "of its own)";
    return n;
  }
  // before[i][j]: call i runs before call j (directly ordered; closed
  // transitively below). Calls that are not ordered either way can run at
  // the same time and need instances of their own: the instance count is the
  // most calls that can run at once, the width of the order (W3 review 2 D2,
  // w3r2_k6: `work(a, t1); work(b, t2); work(t1, t2);` - the third call is
  // ordered after both others, but those two run concurrently: Vitis 2
  // instances, 12 BRAM; a union of the ordered pairs gave 1).
  SmallVector<llvm::BitVector> before(n, llvm::BitVector(n));
  unsigned byArray = 0, byValue = 0, byBranch = 0, byCaller = 0;
  auto order = [&](unsigned i, unsigned j, unsigned &counter) {
    if (before[i].test(j) || before[j].test(i))
      return;
    before[i].set(j);
    ++counter;
  };

  // (i) a common array: a memref operand with the same storage root, or a
  // global the callee writes (every call of it writes the same static array:
  // w3fx_d3_samepar, `u2(a, b); u2(c, d)` with a written `static int t[]`
  // inside: 1 instance; a read-only table does not order the calls, each
  // instance has its own ROM: inl_c4).
  ArgWriteMemo argWrites;
  SmallVector<SmallVector<StorageRoot, 4>> roots(n);
  for (unsigned i = 0; i < n; ++i)
    memrefRoots(sites[i], roots[i]);
  bool writesGlobal = false;
  if (auto call = dyn_cast<CallOpInterface>(sites.front()))
    if (func::FuncOp callee = resolveDefinedCallee(call)) {
      SmallPtrSet<Operation *, 8> stack;
      writesGlobal = calleeWritesGlobal(callee, argWrites, stack);
    }
  DenseMap<Value, bool> streamArrays;
  bool distinctStreams =
      circt::hlsest::Config::get().tool.hls.streams.distinctElementInstances;
  for (unsigned i = 0; i < n; ++i)
    for (unsigned j = i + 1; j < n; ++j)
      if (writesGlobal ||
          (hasRootIn(roots[i], roots[j]) &&
           (!distinctStreams ||
            sharesObject(sites[i], sites[j], streamArrays))))
        order(i, j, byArray);

  // (ii) a value of site i reaches an operand of another site j, through SSA
  // uses, region results / iter_args, and memory (a value written to an
  // array is read back from it). An op can see what an earlier op produced
  // when it comes later in program order or when both lie in a loop of the
  // parent (the next iteration): a write that only follows a read in program
  // order is no dependence of that read (W3 review D1(a), w3rev_k6: `work(a,
  // ra); work(b, rb);` then a loop that reads ra and overwrites b keeps two
  // concurrent instances, Vitis 8 BRAM).
  SmallVector<Operation *> programOrder;
  DenseMap<Operation *, unsigned> ordinal;
  parent.getBody().walk<WalkOrder::PreOrder>([&](Operation *op) {
    ordinal[op] = programOrder.size();
    programOrder.push_back(op);
  });
  Operation *parentOp = parent.getOperation();
  auto isLoop = [](Operation *op) {
    return isa<LoopLikeOpInterface>(op) ||
           isa<loopschedule::LoopSchedulePipelineOp>(op);
  };
  // Whether b lies in a loop of the parent that also holds a. The loops
  // around a are nested, so that is b inside a's outermost loop below the
  // parent, i.e. b's ordinal in that loop's preorder range (memoized per op:
  // the walks below ask this for every op of the body per call site).
  DenseMap<Operation *, Operation *> outermostLoopOf;
  DenseMap<Operation *, unsigned> lastOrdinalOf;
  auto outermostLoop = [&](Operation *a) -> Operation * {
    auto [it, fresh] = outermostLoopOf.try_emplace(a, nullptr);
    if (fresh)
      for (Operation *p = a->getParentOp(); p && p != parentOp;
           p = p->getParentOp())
        if (isLoop(p))
          it->second = p;
    return it->second;
  };
  auto shareLoop = [&](Operation *a, Operation *b) {
    Operation *loop = outermostLoop(a);
    if (!loop)
      return false;
    auto [it, fresh] = lastOrdinalOf.try_emplace(loop, 0);
    if (fresh) {
      unsigned last = ordinal.lookup(loop);
      loop->walk([&](Operation *op) {
        last = std::max(last, ordinal.lookup(op));
      });
      it->second = last;
    }
    unsigned ob = ordinal.lookup(b);
    return ob > ordinal.lookup(loop) && ob <= it->second;
  };
  auto mayFollow = [&](Operation *earlier, Operation *later) {
    return ordinal.lookup(earlier) < ordinal.lookup(later) ||
           shareLoop(earlier, later);
  };

  // The storage roots each op touches and whether it reads / writes each
  // (memrefRoots + readsWrites), computed once per op for every site's walk
  // below: the walks visit the whole body per call site and round, and
  // recomputing these dominated large dataflow designs (SkyNet; speed only).
  struct RootAccess {
    StorageRoot root;
    bool reads, writes;
  };
  DenseMap<Operation *, SmallVector<RootAccess, 2>> rootAccessMemo;
  auto rootAccesses = [&](Operation *op) -> ArrayRef<RootAccess> {
    auto [it, fresh] = rootAccessMemo.try_emplace(op);
    if (fresh) {
      SmallVector<StorageRoot, 4> own;
      memrefRoots(op, own);
      for (const StorageRoot &r : own) {
        SmallVector<StorageRoot, 1> one{r};
        bool reads, writes;
        readsWrites(op, one, reads, writes, argWrites);
        it->second.push_back({r, reads, writes});
      }
    }
    return it->second;
  };

  for (unsigned i = 0; i < n; ++i) {
    // Nothing to learn when site i is already ordered against every other
    // site (order() never changes an ordered pair).
    bool allOrdered = true;
    for (unsigned j = 0; j < n && allOrdered; ++j)
      if (j != i && !before[i].test(j) && !before[j].test(i))
        allOrdered = false;
    if (allOrdered)
      continue;
    // Data values (not memref views: a view carries no data, the accesses
    // through it are tracked by their storage root).
    DenseSet<Value> tainted;
    auto taintValue = [&](Value v) {
      return !isa<BaseMemRefType>(v.getType()) && tainted.insert(v).second;
    };
    // (storage root, the op that wrote a tainted value to it)
    SmallVector<std::pair<StorageRoot, Operation *>, 4> taintedWrites;
    DenseSet<Operation *> taintedOps;
    auto taintOp = [&](Operation *op) {
      if (!taintedOps.insert(op).second)
        return;
      for (Value r : op->getResults())
        taintValue(r);
      for (Region &region : op->getRegions())
        for (Block &b : region)
          for (BlockArgument a : b.getArguments())
            taintValue(a);
      // Writes through this op taint the array: a later read of it is
      // dependent.
      for (const RootAccess &ra : rootAccesses(op))
        if (ra.writes)
          taintedWrites.push_back({ra.root, op});
    };
    // A tainted terminator taints what it forwards: result k of its region
    // op for operand k (a stage's `loopschedule.register`, an scf / affine
    // yield), the next iteration's iter_arg k of a loop, or every result
    // when the operands do not map one to one (W3 review D1(b): forwarding
    // call 1's result through a pipeline stage must not taint the other
    // values the stage registers, w3rev_k2 p2).
    auto taintForwarded = [&](Operation *term) {
      Operation *regionOp = term->getParentOp();
      if (!regionOp || regionOp == parentOp || isa<func::FuncOp>(regionOp))
        return false;
      bool changed = false;
      if (auto pt = dyn_cast<loopschedule::LoopScheduleTerminatorOp>(term)) {
        auto pipe = cast<loopschedule::LoopSchedulePipelineOp>(regionOp);
        for (auto [k, v] : llvm::enumerate(pt.getIterArgs()))
          if (tainted.contains(v)) {
            if (k < pipe.getCondBlock().getNumArguments())
              changed |= taintValue(pipe.getCondBlock().getArgument(k));
            if (k < pipe.getStagesBlock().getNumArguments())
              changed |= taintValue(pipe.getStagesBlock().getArgument(k));
          }
        for (auto [k, v] : llvm::enumerate(pt.getResults()))
          if (tainted.contains(v) && k < pipe->getNumResults())
            changed |= taintValue(pipe->getResult(k));
        return changed;
      }
      bool oneToOne = term->getNumOperands() == regionOp->getNumResults();
      SmallVector<BlockArgument> iterArgs;
      if (auto loop = dyn_cast<LoopLikeOpInterface>(regionOp))
        if (loop.getRegionIterArgs().size() == term->getNumOperands())
          iterArgs.assign(loop.getRegionIterArgs().begin(),
                          loop.getRegionIterArgs().end());
      for (auto [k, v] : llvm::enumerate(term->getOperands())) {
        if (!tainted.contains(v))
          continue;
        if (!iterArgs.empty())
          changed |= taintValue(iterArgs[k]);
        if (oneToOne) {
          changed |= taintValue(regionOp->getResult(k));
          continue;
        }
        for (Value r : regionOp->getResults())
          changed |= taintValue(r);
        break;
      }
      return changed;
    };
    // Whether `op` reads an array a tainted write reached before it.
    auto readsTaintedMemory = [&](Operation *op) {
      for (const RootAccess &ra : rootAccesses(op)) {
        if (!ra.reads)
          continue;
        bool written = llvm::any_of(taintedWrites, [&](const auto &w) {
          return w.first == ra.root && w.second != op &&
                 mayFollow(w.second, op) &&
                 !(distinctStreams &&
                   distinctStreamElements(w.second, op, ra.root,
                                          streamArrays));
        });
        if (written)
          return true;
      }
      return false;
    };
    Operation *site = sites[i];
    taintOp(site);
    // The walk only decides which unordered sites the value of site i
    // reaches; once every one is reached, more rounds change nothing.
    unsigned unresolved = 0;
    for (unsigned j = 0; j < n; ++j)
      if (j != i && !before[i].test(j) && !before[j].test(i))
        ++unresolved;
    auto allReached = [&] {
      unsigned reached = 0;
      for (unsigned j = 0; j < n; ++j)
        if (j != i && !before[i].test(j) && !before[j].test(i) &&
            taintedOps.contains(sites[j]))
          ++reached;
      return reached == unresolved;
    };
    bool changed = true;
    // The ops that may follow the site: those after it in program order and
    // those of its outermost loop (the next iteration). Both are one
    // contiguous tail of the preorder from the loop's first op (or the
    // op after the site), so the walk starts there instead of testing
    // mayFollow for every op of the body (speed only: cbc / ecb / xts
    // aes256dec spent half their time in those lookups).
    size_t firstFollower = ordinal.lookup(site) + 1;
    if (Operation *loop = outermostLoop(site))
      firstFollower = ordinal.lookup(loop) + 1;
    ArrayRef<Operation *> followers =
        ArrayRef<Operation *>(programOrder).drop_front(
            std::min(firstFollower, programOrder.size()));
    for (unsigned round = 0; changed && round < 8 && !allReached(); ++round) {
      changed = false;
      for (Operation *op : followers) {
        if (op == site)
          continue;
        // A terminator is visited again when more of its operands become
        // tainted: each operand forwards to its own result.
        bool isTerminator = op->hasTrait<OpTrait::IsTerminator>();
        if (!isTerminator && taintedOps.contains(op))
          continue;
        bool hit = llvm::any_of(op->getOperands(),
                                [&](Value v) { return tainted.contains(v); });
        if (!hit && !isTerminator && !taintedWrites.empty())
          hit = readsTaintedMemory(op);
        if (!hit)
          continue;
        if (!taintedOps.contains(op)) {
          taintOp(op);
          changed = true;
        }
        if (isTerminator && taintForwarded(op))
          changed = true;
      }
    }
    for (unsigned j = 0; j < n; ++j)
      if (j != i && taintedOps.contains(sites[j]))
        order(i, j, byValue);
  }

  // (vi) staggered inputs (VITIS_NOTES N116): two calls at the top level of
  // the caller that nothing above orders still run one after the other when
  // their inputs become ready in different states. Each top-level op starts
  // after the top-level ops whose values or arrays it uses (a write it
  // reads or overwrites, a read it overwrites); a call or an op with regions
  // takes a step, as does a call of a function after an earlier call of the
  // same function that shares an array with it (one instance, N14 R2) or
  // under an allocation limit of 1. Kernels w9r15p_al_lim / al_nolim
  // (`mm(e, 3, Q); mm(e, 5, K); work(Q, o1); work(K, o2)`): one `work`
  // instance; al_same (one producer writes Q and K) and al_two (two
  // independent producers) two; forgebench attn_breakdown `rope`.
  //
  // (vii) calls are issued in program order (VITIS_NOTES N156, scheduling.
  // call_depth.in_order_call_starts): two calls of f share an instance when
  // a call between them waits for the first one (it uses a value or an
  // array of it, directly or through another call), as the second one is
  // issued after that call (w9r21p_f2_straight `work(A, B, C); mid(P, A);
  // work(D, E, F)`: one `work` instance; f4 with an independent `mid`:
  // two). With the rule on, the staggered starts of (vi) and this rule also
  // apply to the calls in one nested block outside pipelined loops
  // (w9r21p_f1: the three calls in one arm of an if chain in a loop, one
  // instance; FLAT-acceleration computeAttention). The starts themselves
  // stay those of (vi): forcing every call to start no earlier than the
  // previous one makes forgebench attn_breakdown's two `rope` calls start
  // together (two instances, Vitis one).
  unsigned byStagger = 0;
  const circt::hlsest::CallDepthConfig &callDepthCfg =
      circt::hlsest::Config::get().scheduling.callDepth;
  auto inPipeline = [&](Operation *op) {
    for (Operation *p = op; p && p != parentOp; p = p->getParentOp())
      if (isa<loopschedule::LoopSchedulePipelineOp>(p) ||
          p->hasAttr("hls.pipeline"))
        return true;
    return false;
  };
  // topLevel: the caller's own body, where an allocation limit of 1 orders
  // two calls of the limited function; a nested block may be a loop Vitis
  // outlines, which the limit does not reach (N14 R5, lit
  // w9r17fx_n14r5_outlined_loop_pair).
  auto staggerBlock = [&](Block &body, ArrayRef<unsigned> blockSites,
                          bool topLevel) {
    Operation *blockOp = body.getParentOp();
    SmallVector<Operation *> top;
    DenseMap<Operation *, unsigned> topIndex;
    for (Operation &op : body.without_terminator()) {
      topIndex[&op] = top.size();
      top.push_back(&op);
    }
    if (top.size() > 512)
      return;
    auto topOf = [&](Operation *op) -> Operation * {
      while (op && op->getBlock() != &body) {
        op = op->getParentOp();
        if (op == blockOp)
          return nullptr;
      }
      return op;
    };
    struct TopAccess {
      SmallVector<StorageRoot, 4> reads, writes;
      SmallVector<unsigned, 4> ssaDeps;
    };
    SmallVector<TopAccess> acc(top.size());
    for (unsigned t = 0; t < top.size(); ++t) {
      top[t]->walk([&](Operation *op) {
        for (const RootAccess &ra : rootAccesses(op)) {
          if (ra.reads)
            acc[t].reads.push_back(ra.root);
          if (ra.writes)
            acc[t].writes.push_back(ra.root);
        }
        for (Value v : op->getOperands())
          if (Operation *d = topOf(v.getDefiningOp()); d && d != top[t])
            acc[t].ssaDeps.push_back(topIndex.lookup(d));
      });
    }
    auto meets = [](ArrayRef<StorageRoot> a, ArrayRef<StorageRoot> b) {
      return llvm::any_of(a, [&](const StorageRoot &x) {
        return llvm::is_contained(b, x);
      });
    };
    auto calleeOf = [](Operation *op) -> Operation * {
      if (auto call = dyn_cast<CallOpInterface>(op))
        if (func::FuncOp f = resolveDefinedCallee(call))
          return f.getOperation();
      return nullptr;
    };
    SmallVector<unsigned> finish(top.size(), 0), start(top.size(), 0);
    // waits[k]: the earlier ops op k waits for, directly (a value or an
    // array it uses) or through an op it waits for (N156).
    SmallVector<llvm::BitVector> waits(top.size(), llvm::BitVector(top.size()));
    auto waitFor = [&](unsigned k, unsigned d) {
      waits[k].set(d);
      waits[k] |= waits[d];
    };
    for (unsigned k = 0; k < top.size(); ++k) {
      unsigned st = 0;
      for (unsigned d : acc[k].ssaDeps)
        if (d < k) {
          st = std::max(st, finish[d]);
          waitFor(k, d);
        }
      Operation *ck = calleeOf(top[k]);
      for (unsigned l = 0; l < k; ++l) {
        bool dep = meets(acc[l].writes, acc[k].reads) ||
                   meets(acc[l].writes, acc[k].writes) ||
                   meets(acc[l].reads, acc[k].writes);
        // Two calls on distinct elements of a stream array touch distinct
        // FIFOs (neuro_monarchs init_mults_HLS: 8 org_mult calls, 8
        // instances in Vitis).
        bool bothCalls = isa<CallOpInterface>(top[l]) &&
                         isa<CallOpInterface>(top[k]);
        if (dep && bothCalls && distinctStreams &&
            !sharesObject(top[l], top[k], streamArrays))
          dep = false;
        if (!dep && ck && calleeOf(top[l]) == ck) {
          std::optional<int64_t> lim =
              allocationLimit(parent, cast<func::FuncOp>(ck));
          dep = (topLevel && lim && *lim == 1) ||
                sharesObject(top[l], top[k], streamArrays);
        }
        if (dep) {
          st = std::max(st, finish[l]);
          waitFor(k, l);
        }
      }
      start[k] = st;
      bool step = isa<CallOpInterface>(top[k]) || top[k]->getNumRegions();
      finish[k] = st + (step ? 1 : 0);
    }
    // N156: a call between the two sites that waits for the first one is
    // issued before the second one, which so cannot overlap the first. A
    // loop is issued in program order as well (W9 round 21 review D5:
    // kernel w9r21rev_r5a_loopbetween, `work(A, B, C); for (..) G[i] =
    // C[..] + 1; work(D, E, F)`: one `work` instance in Vitis).
    auto waitingCallBetween = [&](unsigned a, unsigned b) {
      for (unsigned c = a + 1; c < b; ++c)
        if ((isa<CallOpInterface>(top[c]) || top[c]->getNumRegions() > 0) &&
            waits[c].test(a))
          return true;
      return false;
    };
    for (unsigned x = 0; x < blockSites.size(); ++x)
      for (unsigned y = x + 1; y < blockSites.size(); ++y) {
        unsigned i = blockSites[x], j = blockSites[y];
        unsigned ti = topIndex.lookup(sites[i]), tj = topIndex.lookup(sites[j]);
        bool staggered = start[ti] != start[tj];
        bool waited = callDepthCfg.inOrderCallStarts &&
                      waitingCallBetween(std::min(ti, tj), std::max(ti, tj));
        if (staggered || waited)
          order(std::min(i, j), std::max(i, j), byStagger);
      }
  };
  if (callDepthCfg.staggeredCallsShareInstance && n > 1 && processes == 0) {
    bool allTop = llvm::all_of(sites, [&](Operation *s) {
      return s->getParentOp() == parentOp;
    });
    if (allTop) {
      SmallVector<unsigned> all;
      for (unsigned i = 0; i < n; ++i)
        all.push_back(i);
      staggerBlock(parent.getBody().front(), all, /*topLevel=*/true);
    } else if (callDepthCfg.inOrderCallStarts) {
      // Per block holding two or more of the sites, outside pipelines.
      llvm::MapVector<Block *, SmallVector<unsigned>> byBlock;
      for (unsigned i = 0; i < n; ++i)
        byBlock[sites[i]->getBlock()].push_back(i);
      for (auto &[block, blockSites] : byBlock)
        if (blockSites.size() > 1 && !inPipeline(sites[blockSites[0]]))
          staggerBlock(*block, blockSites, /*topLevel=*/false);
    }
  }

  // (v) the read ports of a memory the calls read their data operands from:
  // the k unrolled copies of `y[i] = hls::exp(x[i])` in a `pipeline off`
  // loop over an unpartitioned x (two read ports, x_address0 / x_address1)
  // get min(k, 2) instances (Vitis 2025.1: w11rv_r3 k 3 and w11rv_r8 k 8,
  // exp_32_16_s, function-pipelined; w11rf_sin4 k 4, generic_sincos_16_5_s,
  // not pipelined (II 46); w11rf_exp4 k 4: 2 each; w11rf_exp2a, the copies
  // of two calls on x and w: 2 + 2), while v4n's cyclic-partitioned ports
  // keep k (N16 R4; memoryReadPorts). The calls reading one memory form
  // `ports` chains, the n-th of them (program order) after the
  // (n - ports)-th, so at most `ports` run at once. Unconfirmed: calls whose operands come from several
  // memories, and calls in pipelined loops.
  unsigned ports = static_cast<unsigned>(std::max<int64_t>(
      0, circt::hlsest::Config::get().scheduling.callDepth.portsPerMemory));
  unsigned byPorts = 0;
  if (ports > 0 && n > ports) {
    // Per memory, its distinct reads in program order and the calls each
    // read feeds (one read can feed several calls: a scalar loaded once and
    // passed to three dataflow processes, DGNN_Booster_convLSTM's
    // CONV_GNN_sigmoid, is one port access, and Vitis keeps 3 instances).
    struct Read {
      Operation *op;
      SmallVector<unsigned, 2> calls;
    };
    SmallVector<std::pair<StorageRoot, SmallVector<Read, 8>>, 4> memories;
    for (unsigned i = 0; i < n; ++i) {
      SmallVector<std::pair<StorageRoot, Operation *>, 2> reads;
      dataOperandMemories(sites[i], reads);
      for (const auto &[root, op] : reads) {
        auto *mem = llvm::find_if(
            memories, [&](const auto &e) { return e.first == root; });
        if (mem == memories.end()) {
          memories.push_back({root, {}});
          mem = std::prev(memories.end());
        }
        auto *read = llvm::find_if(mem->second,
                                   [&](const Read &r) { return r.op == op; });
        if (read == mem->second.end()) {
          mem->second.push_back({op, {}});
          read = std::prev(mem->second.end());
        }
        if (!llvm::is_contained(read->calls, i))
          read->calls.push_back(i);
      }
    }
    for (auto &[root, reads] : memories) {
      llvm::stable_sort(reads, [&](const Read &x, const Read &y) {
        return ordinal.lookup(x.op) < ordinal.lookup(y.op);
      });
      unsigned p = memoryReadPorts(root, ports);
      for (unsigned a = 0; a + p < reads.size(); ++a)
        for (unsigned ci : reads[a].calls)
          for (unsigned cj : reads[a + p].calls)
            if (ci != cj)
              order(std::min(ci, cj), std::max(ci, cj), byPorts);
    }
  }

  // (iii) calls in different branches of one conditional never run at the
  // same time: they can share an instance (W3 review 2 D1, w3r2_k5). They
  // are ordered like the branches in program order. Unconfirmed: whether
  // Vitis also shares the instance when the conditional sits in a pipelined
  // loop (different iterations may overlap).
  for (unsigned i = 0; i < n; ++i)
    for (unsigned j = i + 1; j < n; ++j)
      if (mutuallyExclusive(sites[i], sites[j]))
        order(i, j, byBranch);

  // (iv) pairs the caller knows never run at the same time.
  if (alsoOrdered)
    for (unsigned i = 0; i < n; ++i)
      for (unsigned j = i + 1; j < n; ++j)
        if (alsoOrdered(i, j))
          order(i, j, byCaller);

  // The processes of a dataflow region are ordered against no other call
  // (see above); clearing them before the closure also keeps an order
  // through a process from reaching two nested calls.
  if (processes > 0)
    for (unsigned i = 0; i < n; ++i)
      for (unsigned j = 0; j < n; ++j)
        if (isProcess[i] || isProcess[j])
          before[i].reset(j);

  // Transitive closure (Warshall over bit rows).
  for (unsigned k = 0; k < n; ++k)
    for (unsigned i = 0; i < n; ++i)
      if (before[i].test(k))
        before[i] |= before[k];

  unsigned groups = chainCover(before, group);
  unsigned uncapped = groups;
  unsigned outlinedLoops = 0;
  if (limit && *limit > 0 && groups > static_cast<unsigned>(*limit)) {
    unsigned cap = static_cast<unsigned>(*limit);
    // Vitis outlines a sequential loop that holds a call into a module of
    // its own when the function also calls a function outside every loop
    // (VITIS_NOTES N14 R5); the calls in that loop belong to the outlined
    // module, which the function's allocation limit does not reach: the
    // limit caps only the calls left in the function's own body, and each
    // outlined loop keeps the instances its own order needs (kernels
    // inl_c8_loop_and_direct_limit1 and w9r17i_ol_lim: limit 1, one call in
    // the loop and one outside, 2 instances; w9r17rev_rv_olpair: limit 1, two
    // independent calls in the outlined loop, 2 instances there, 8 BRAM;
    // forgebench tiled_attn_module).
    SmallVector<Operation *> domain(n, nullptr);
    if (circt::hlsest::Config::get()
            .scheduling.callDepth.outlinedLoopsOwnAllocation)
      outlinedLoopDomains(parent, sites, domain);
    llvm::MapVector<Operation *, SmallVector<unsigned>> members;
    for (unsigned i = 0; i < n; ++i)
      members[domain[i]].push_back(i);
    if (members.size() > 1 || !members.count(nullptr)) {
      // Instances per domain: the width of the order among its own call
      // sites (a chain cover of the restricted order), capped by the limit
      // only in the function's own body (domain null).
      unsigned offset = 0;
      for (auto &[d, idx] : members) {
        SmallVector<llvm::BitVector> sub(idx.size(),
                                         llvm::BitVector(idx.size()));
        for (unsigned a = 0; a < idx.size(); ++a)
          for (unsigned b = 0; b < idx.size(); ++b)
            if (before[idx[a]].test(idx[b]))
              sub[a].set(b);
        SmallVector<unsigned> subGroup;
        unsigned width = chainCover(sub, subGroup);
        unsigned kept = d ? width : std::min(width, cap);
        for (unsigned a = 0; a < idx.size(); ++a)
          group[idx[a]] = offset + std::min(subGroup[a], kept - 1);
        offset += kept;
      }
      groups = offset;
      outlinedLoops = members.size() - (members.count(nullptr) ? 1 : 0);
    } else {
      for (unsigned i = 0; i < n; ++i)
        group[i] = std::min(group[i], cap - 1);
      groups = cap;
    }
  }
  if (rule) {
    std::string s = std::to_string(n) + " call site(s) -> " +
                    std::to_string(groups) + " instance(s)";
    if (n > 1) {
      s += " (ordered pairs: " + std::to_string(byArray) +
           " by a common array, " + std::to_string(byValue) +
           " by a value dependence";
      if (byBranch)
        s += ", " + std::to_string(byBranch) + " by exclusive branches";
      if (byCaller)
        s += ", " + std::to_string(byCaller) + " by sequential code";
      if (byPorts)
        s += ", " + std::to_string(byPorts) + " by the ports of a memory " +
             "their operands are read from";
      if (byStagger)
        s += ", " + std::to_string(byStagger) +
             " by inputs ready in different states";
      if (processes)
        s += "; " + std::to_string(processes) +
             " of them dataflow processes, an instance each";
      if (limit && outlinedLoops)
        s += "; allocation limit " + std::to_string(*limit) +
             " caps the function's own body only: " +
             std::to_string(outlinedLoops) +
             " loop(s) holding calls are outlined (N14 R5)";
      else if (limit)
        s += "; allocation limit " + std::to_string(*limit) +
             (uncapped > groups ? " applied" : " not binding");
      s += ")";
    }
    *rule = s;
  }
  return groups;
}

unsigned InstanceModel::instancesAt(Operation *op) const {
  if (auto fn = op->getParentOfType<func::FuncOp>())
    return instancesOf(fn);
  return 1;
}

func::FuncOp InstanceModel::owner(ArrayRef<func::FuncOp> users) const {
  if (users.empty())
    return nullptr;
  if (users.size() == 1)
    return users.front();
  // Ancestor sets (a function is its own ancestor).
  auto ancestors = [&](func::FuncOp f) {
    SmallPtrSet<Operation *, 8> seen;
    SmallVector<func::FuncOp> work{f};
    seen.insert(f.getOperation());
    while (!work.empty()) {
      func::FuncOp cur = work.pop_back_val();
      auto it = callers.find(cur.getOperation());
      if (it == callers.end())
        continue;
      for (func::FuncOp p : it->second)
        if (seen.insert(p.getOperation()).second)
          work.push_back(p);
    }
    return seen;
  };
  SmallPtrSet<Operation *, 8> common = ancestors(users.front());
  for (func::FuncOp u : users.drop_front()) {
    SmallPtrSet<Operation *, 8> a = ancestors(u);
    SmallVector<Operation *> drop;
    for (Operation *c : common)
      if (!a.contains(c))
        drop.push_back(c);
    for (Operation *c : drop)
      common.erase(c);
  }
  if (common.empty())
    return nullptr;
  // The deepest: a common ancestor that is not a proper ancestor of another
  // common ancestor; among several (a diamond), the most instantiated.
  func::FuncOp best;
  for (Operation *c : common) {
    auto fc = cast<func::FuncOp>(c);
    bool properAncestor = false;
    for (Operation *d : common) {
      if (d == c)
        continue;
      SmallPtrSet<Operation *, 8> ad = ancestors(cast<func::FuncOp>(d));
      if (ad.contains(c)) {
        properAncestor = true;
        break;
      }
    }
    if (properAncestor)
      continue;
    if (!best || instancesOf(fc) > instancesOf(best))
      best = fc;
  }
  return best;
}

unsigned InstanceModel::ownerInstances(ArrayRef<func::FuncOp> users) const {
  if (users.empty())
    return 1;
  func::FuncOp o = owner(users);
  return o ? instancesOf(o) : 1u;
}

unsigned InstanceModel::instanceSites(func::FuncOp fn) const {
  auto it = parents.find(fn.getOperation());
  if (it == parents.end())
    return 0;
  unsigned sites = 0;
  for (const ParentInstances &pi : it->second)
    sites += pi.instances;
  return sites;
}

func::FuncOp
InstanceModel::singleInstanceOwner(ArrayRef<func::FuncOp> users) const {
  // Walk up from the owner to the nearest function with one instance: with
  // one caller that caller, with several their deepest common ancestor (in
  // practice the top). A call cycle stops the walk.
  func::FuncOp o = owner(users);
  SmallPtrSet<Operation *, 8> visited;
  while (o && instancesOf(o) != 1) {
    if (!visited.insert(o.getOperation()).second)
      return nullptr;
    auto it = callers.find(o.getOperation());
    if (it == callers.end() || it->second.empty())
      return o;
    o = owner(it->second);
  }
  return o;
}

bool InstanceModel::argBindsSeveralArrays(func::FuncOp fn,
                                          unsigned argIndex) const {
  if (!circt::hlsest::Config::get()
           .tool.hls.memoryArchitecture.replication.portBoundSeveralArrays)
    return false;
  auto it = parents.find(fn.getOperation());
  if (it == parents.end())
    return false;
  std::optional<StorageRoot> first;
  for (const ParentInstances &pi : it->second)
    for (auto &[siteOp, grp] : pi.siteGroups) {
      (void)grp;
      auto args = cast<CallOpInterface>(siteOp).getArgOperands();
      if (argIndex >= args.size() ||
          !isa<BaseMemRefType>(args[argIndex].getType()))
        continue;
      StorageRoot root = storageRoot(args[argIndex]);
      if (!first)
        first = root;
      else if (*first != root)
        return true;
    }
  return false;
}

bool InstanceModel::calleeArgPortBound(func::FuncOp callee,
                                       unsigned argIndex) const {
  return !calleeArgPortBoundReason(callee, argIndex).empty();
}

StringRef InstanceModel::calleeArgPortBoundReason(func::FuncOp callee,
                                                  unsigned argIndex) const {
  if (instanceSites(callee) > 1)
    return "instances";
  if (argBindsSeveralArrays(callee, argIndex))
    return "several_arrays";
  if (argSharesPortBoundArray(callee, argIndex))
    return "array_shared_with_port_bound_parameter";
  if (argBindsWritableGlobal(callee, argIndex))
    return "writable_global";
  return "";
}

bool InstanceModel::isWrittenGlobal(Operation *global) const {
  auto g = dyn_cast<memref::GlobalOp>(global);
  if (!g || g.getConstant())
    return false;
  auto [it, inserted] = writtenGlobals.try_emplace(global, false);
  if (!inserted)
    return it->second;
  SmallVector<Value> sites;
  if (Operation *table = SymbolTable::getNearestSymbolTable(global)) {
    auto [tit, fresh] = globalSitesByTable.try_emplace(table);
    if (fresh)
      table->walk([&](memref::GetGlobalOp gg) {
        tit->second[gg.getNameAttr().getAttr()].push_back(gg.getResult());
      });
    auto sit = tit->second.find(g.getSymNameAttr());
    if (sit != tit->second.end())
      sites = sit->second;
  }
  bool written = !sites.empty() && !neverWritten(sites);
  writtenGlobals[global] = written;
  return written;
}

bool InstanceModel::argBindsWritableGlobal(func::FuncOp fn,
                                           unsigned argIndex) const {
  if (!circt::hlsest::Config::get()
           .tool.hls.memoryArchitecture.replication.portBoundWritableGlobals)
    return false;
  SmallVector<StorageRoot> roots;
  boundRoots(fn, argIndex, roots);
  return llvm::any_of(roots, [&](const StorageRoot &r) {
    return r.global && isWrittenGlobal(r.global);
  });
}

void InstanceModel::boundRoots(func::FuncOp fn, unsigned argIndex,
                               SmallVectorImpl<StorageRoot> &out) const {
  SmallPtrSet<Operation *, 8> stack;
  std::function<void(func::FuncOp, unsigned)> walk = [&](func::FuncOp f,
                                                         unsigned idx) {
    if (!stack.insert(f.getOperation()).second)
      return; // a call cycle
    auto it = parents.find(f.getOperation());
    if (it != parents.end())
      for (const ParentInstances &pi : it->second)
        for (auto &[siteOp, grp] : pi.siteGroups) {
          (void)grp;
          auto args = cast<CallOpInterface>(siteOp).getArgOperands();
          if (idx >= args.size() || !isa<BaseMemRefType>(args[idx].getType()))
            continue;
          StorageRoot root = storageRoot(args[idx]);
          auto barg = dyn_cast_or_null<BlockArgument>(root.value);
          Operation *parentOp = pi.parent;
          if (barg && barg.getOwner()->getParentOp() == parentOp &&
              parents.count(parentOp)) {
            walk(cast<func::FuncOp>(parentOp), barg.getArgNumber());
            continue;
          }
          if (!llvm::is_contained(out, root))
            out.push_back(root);
        }
    stack.erase(f.getOperation());
  };
  walk(fn, argIndex);
}

bool InstanceModel::argSharesPortBoundArray(func::FuncOp fn,
                                            unsigned argIndex) const {
  if (!circt::hlsest::Config::get()
           .tool.hls.memoryArchitecture.replication.portBoundSeveralArrays)
    return false;
  if (!severalArraysRoots) {
    severalArraysRoots.emplace();
    for (auto &[calleeOp, pis] : parents) {
      (void)pis;
      auto callee = cast<func::FuncOp>(calleeOp);
      for (BlockArgument arg : callee.getArguments())
        if (isa<BaseMemRefType>(arg.getType()) &&
            argBindsSeveralArrays(callee, arg.getArgNumber()))
          boundRoots(callee, arg.getArgNumber(), *severalArraysRoots);
    }
  }
  if (severalArraysRoots->empty())
    return false;
  SmallVector<StorageRoot> mine;
  boundRoots(fn, argIndex, mine);
  for (const StorageRoot &r : mine)
    if (llvm::is_contained(*severalArraysRoots, r))
      return true;
  return false;
}

bool InstanceModel::argReachesSharedModule(func::FuncOp fn,
                                           unsigned argIndex) const {
  SmallPtrSet<Operation *, 8> stack;
  std::function<bool(func::FuncOp, unsigned)> shared =
      [&](func::FuncOp f, unsigned idx) -> bool {
    if (calleeArgPortBound(f, idx))
      return true;
    if (!stack.insert(f.getOperation()).second)
      return false; // a call cycle: decided where it started
    bool result = false;
    auto it = parents.find(f.getOperation());
    if (it != parents.end())
      for (const ParentInstances &pi : it->second) {
        for (auto &[siteOp, grp] : pi.siteGroups) {
          (void)grp;
          auto call = cast<CallOpInterface>(siteOp);
          auto args = call.getArgOperands();
          if (idx >= args.size())
            continue;
          // The caller's array: its own (an alloca, a global) ends the walk;
          // an argument of the caller continues it one level up.
          StorageRoot root = storageRoot(args[idx]);
          auto barg = dyn_cast_or_null<BlockArgument>(root.value);
          if (!barg || barg.getOwner()->getParentOp() != pi.parent)
            continue;
          if (shared(pi.parent, barg.getArgNumber())) {
            result = true;
            break;
          }
        }
        if (result)
          break;
      }
    stack.erase(f.getOperation());
    return result;
  };
  return shared(fn, argIndex);
}

/// Whether the call sites `a` and `b` of one callee lie in two different
/// loops of `parent` that run one after the other (VITIS_NOTES N16 R10,
/// applied to kept callees, W9 round 19 review defect 3): their holders in
/// the innermost common block are two loops, and either that block is not
/// the parent's body (two loops nested in an outer loop run in turn,
/// w2fx_twonest), or the two loops access a common array (w2fx_twoshared /
/// w2fx_twodep; kernel w9r19r_rv_fps: g in a pipelined loop and in a
/// `pipeline off` loop, both reading `in`: one instance of g in the top,
/// Vitis 2 BRAM), or one of them is pipelined (kernel w9r19f_fx_fps_dis:
/// the same loops on disjoint arrays, `top_Pipeline_A` and `top_Outline_B`
/// share one g in the top, Vitis 2 BRAM). Two sequential loops of the body
/// on disjoint arrays are outlined and run concurrently, an instance each
/// (w2rv_twoloops), and a dataflow region's processes overlap: not ordered
/// here. Unconfirmed: two pipelined loops on disjoint arrays.
static bool orderedBySequentialLoops(func::FuncOp parent, Operation *a,
                                     Operation *b) {
  if (parent->hasAttr("hls.dataflow"))
    return false;
  auto isLoop = [](Operation *op) {
    return isa<LoopLikeOpInterface, loopschedule::LoopSchedulePipelineOp>(op);
  };
  llvm::DenseMap<Block *, Operation *> holderOfA;
  for (Operation *p = a; p && p != parent.getOperation(); p = p->getParentOp())
    holderOfA.try_emplace(p->getBlock(), p);
  for (Operation *q = b; q && q != parent.getOperation();
       q = q->getParentOp()) {
    auto it = holderOfA.find(q->getBlock());
    if (it == holderOfA.end())
      continue;
    Operation *x = it->second;
    if (x == q || !isLoop(x) || !isLoop(q))
      return false;
    if (q->getParentOp() != parent.getOperation())
      return true;
    auto pipelined = [](Operation *loop) {
      return isa<loopschedule::LoopSchedulePipelineOp>(loop) ||
             (loop->hasAttr(kLoopPipelineAttr) &&
              !loop->hasAttr(kLoopPipelineOffAttr));
    };
    if (pipelined(x) || pipelined(q))
      return true;
    SmallVector<StorageRoot, 8> rootsX;
    x->walk([&](Operation *op) { memrefRoots(op, rootsX); });
    bool common = false;
    q->walk([&](Operation *op) {
      SmallVector<StorageRoot, 4> own;
      memrefRoots(op, own);
      if (llvm::any_of(own, [&](const StorageRoot &r) {
            return llvm::is_contained(rootsX, r);
          })) {
        common = true;
        return WalkResult::interrupt();
      }
      return WalkResult::advance();
    });
    return common;
  }
  return false;
}

/// Whether `callee` takes an array (VITIS_NOTES N145): a memref parameter
/// that some call site binds to something other than a scalar - a
/// one-element variable (`&rcon`), registers or an aggregated struct
/// pointer (N147).
static bool takesArrayArgument(func::FuncOp callee,
                               ArrayRef<Operation *> sites,
                               const AggregatedScalars &scalars) {
  auto isScalar = [&](Value v) {
    if (scalars.contains(v))
      return true;
    StorageRoot root = storageRoot(v);
    Operation *def = root.global ? root.global
                     : root.value ? root.value.getDefiningOp()
                                  : nullptr;
    if (!def)
      return false;
    if (def->hasAttr(kRegistersAttrName))
      return true;
    if (root.global)
      return false;
    auto t = dyn_cast<MemRefType>(root.value.getType());
    return t && t.hasStaticShape() && t.getNumElements() == 1 &&
           isa<memref::AllocaOp, memref::AllocOp>(def);
  };
  for (BlockArgument arg : callee.getArguments()) {
    if (!isa<MemRefType>(arg.getType()))
      continue;
    unsigned n = arg.getArgNumber();
    for (Operation *site : sites) {
      auto call = cast<CallOpInterface>(site);
      if (n < call.getArgOperands().size() &&
          !isScalar(call.getArgOperands()[n]))
        return true;
    }
  }
  return false;
}

/// N145: the call sites of a callee with an array argument that lie in
/// different modules of `parent` (an outlined pipelined loop, N143, or the
/// parent's own body) never share an instance; each module groups its own
/// calls by R2 (the parent's allocation limit caps its body only). Returns
/// false (nothing done) when the sites lie in one module.
static bool groupByOutlinedPipelines(func::FuncOp parent,
                                     ArrayRef<Operation *> sites,
                                     const AggregatedScalars &scalars,
                                     ParentInstances &pi,
                                     SmallVectorImpl<unsigned> &group) {
  llvm::MapVector<Operation *, SmallVector<unsigned>> members;
  for (unsigned i = 0; i < sites.size(); ++i)
    members[outlinedPipelineAround(sites[i], parent)].push_back(i);
  if (members.size() < 2 || !takesArrayArgument(pi.callee, sites, scalars))
    return false;
  group.assign(sites.size(), 0);
  unsigned offset = 0, loops = 0;
  std::string rules;
  for (auto &[domain, idx] : members) {
    SmallVector<Operation *> sub;
    for (unsigned i : idx)
      sub.push_back(sites[i]);
    SmallVector<unsigned> subGroup;
    std::string subRule;
    unsigned width = groupConcurrentCalls(
        parent, sub, domain ? std::nullopt : pi.limit, subGroup, &subRule);
    for (unsigned a = 0; a < idx.size(); ++a)
      group[idx[a]] = offset + subGroup[a];
    offset += width;
    loops += domain ? 1 : 0;
    rules += (rules.empty() ? "" : "; ") +
             std::string(domain ? "outlined loop: " : "body: ") + subRule;
  }
  pi.instances = offset;
  pi.rule = std::to_string(sites.size()) + " call site(s) -> " +
            std::to_string(offset) + " instance(s) (an array argument; " +
            std::to_string(loops) +
            " outlined pipelined loop(s) hold calls, an instance per "
            "module, N145: " +
            rules + ")";
  return true;
}

InstanceModel computeInstances(ModuleOp module,
                               llvm::function_ref<bool(func::FuncOp)> inScope) {
  InstanceModel m;
  const bool outlinedArrayInstances =
      circt::hlsest::Config::get()
          .scheduling.callDepth.outlinedPipelineArrayInstances;
  const bool sequentialLoopsShare =
      circt::hlsest::Config::get()
          .scheduling.callDepth.sequentialLoopsShareInstance;
  AggregatedScalars scalars;
  if (outlinedArrayInstances)
    scalars = computeAggregatedScalars(module);
  SmallVector<func::FuncOp> funcs;
  for (auto fn : module.getOps<func::FuncOp>())
    if (!fn.isExternal() && (!inScope || inScope(fn)))
      funcs.push_back(fn);
  DenseSet<Operation *> scope;
  for (func::FuncOp f : funcs)
    scope.insert(f.getOperation());

  for (func::FuncOp parent : funcs) {
    // Call sites per callee, in program order.
    llvm::MapVector<Operation *, SmallVector<Operation *>> byCallee;
    parent.getBody().walk<WalkOrder::PreOrder>([&](CallOpInterface call) {
      func::FuncOp callee = resolveDefinedCallee(call);
      if (!callee || !scope.contains(callee.getOperation()))
        return;
      byCallee[callee.getOperation()].push_back(call.getOperation());
    });
    for (auto &[calleeOp, sites] : byCallee) {
      auto callee = cast<func::FuncOp>(calleeOp);
      ParentInstances pi;
      pi.parent = parent;
      pi.callee = callee;
      pi.callSites = sites.size();
      pi.limit = allocationLimit(parent, callee);
      SmallVector<unsigned> group;
      if (!outlinedArrayInstances ||
          !groupByOutlinedPipelines(parent, sites, scalars, pi, group)) {
        llvm::function_ref<bool(unsigned, unsigned)> loopsOrdered;
        auto sequentialLoops = [&](unsigned i, unsigned j) {
          return orderedBySequentialLoops(parent, sites[i], sites[j]);
        };
        if (sequentialLoopsShare)
          loopsOrdered = sequentialLoops;
        pi.instances = groupConcurrentCalls(parent, sites, pi.limit, group,
                                            &pi.rule, loopsOrdered);
      }
      for (unsigned i = 0; i < sites.size(); ++i) {
        pi.siteGroups.push_back({sites[i], group[i]});
        m.sites[sites[i]] = {parent, callee, group[i]};
      }
      m.parents[calleeOp].push_back(std::move(pi));
      auto &cs = m.callers[calleeOp];
      if (!llvm::is_contained(cs, parent))
        cs.push_back(parent);
    }
  }

  // Multiplicity: memoized over the call graph; a cycle counts as a root.
  DenseMap<Operation *, unsigned> memo;
  SmallPtrSet<Operation *, 8> onStack;
  std::function<unsigned(func::FuncOp)> mult = [&](func::FuncOp f) -> unsigned {
    auto it = memo.find(f.getOperation());
    if (it != memo.end())
      return it->second;
    if (!onStack.insert(f.getOperation()).second) {
      m.recursive = true;
      return 1;
    }
    unsigned total = 0;
    auto pit = m.parents.find(f.getOperation());
    if (pit != m.parents.end())
      for (const ParentInstances &pi : pit->second)
        total += mult(pi.parent) * pi.instances;
    onStack.erase(f.getOperation());
    if (pit == m.parents.end() || pit->second.empty())
      total = 1; // a root: the top, or a function nothing in scope calls
    memo[f.getOperation()] = total;
    return total;
  };
  for (func::FuncOp f : funcs)
    m.multiplicity[f.getOperation()] = mult(f);
  return m;
}

//===----------------------------------------------------------------------===//
// Clones of kept callees per argument IR type (VITIS_NOTES N165)
//===----------------------------------------------------------------------===//

namespace {
/// The kind of a floating-point array argument: a top-level port ('p', an
/// integer array in Vitis' IR) or a caller-local / global array ('l').
/// Other arguments have no kind ('-'): their IR type is the same either way.
char floatArrayKind(Value arg, const DenseMap<Value, char> &paramKinds) {
  auto type = dyn_cast<BaseMemRefType>(arg.getType());
  if (!type || !isa<FloatType>(type.getElementType()))
    return '-';
  StorageRoot root = storageRoot(arg);
  if (root.global || !root.value)
    return 'l';
  auto it = paramKinds.find(root.value);
  if (it != paramKinds.end())
    return it->second;
  return 'l'; // an alloca, or a value of unknown origin
}
} // namespace

bool inExclusiveArms(Operation *a, Operation *b) {
  return mutuallyExclusive(a, b);
}

unsigned cloneKeptCalleesPerArgumentType(ModuleOp module) {
  SymbolTable symbols(module);
  SmallVector<func::FuncOp> defined;
  DenseSet<Operation *> called;
  for (auto fn : module.getOps<func::FuncOp>()) {
    if (fn.isExternal())
      continue;
    defined.push_back(fn);
    fn.walk([&](func::CallOp call) {
      if (auto callee = symbols.lookup<func::FuncOp>(call.getCallee()))
        if (callee != fn)
          called.insert(callee.getOperation());
    });
  }
  DenseMap<Value, char> paramKinds;
  SmallVector<func::FuncOp> worklist;
  DenseSet<Operation *> queued;
  for (func::FuncOp fn : defined) {
    if (called.contains(fn.getOperation()))
      continue;
    for (BlockArgument arg : fn.getArguments())
      paramKinds[arg] = 'p';
    worklist.push_back(fn);
    queued.insert(fn.getOperation());
  }
  // Per kept callee: the clone made for each argument-kind key.
  DenseMap<Operation *, llvm::StringMap<func::FuncOp>> clonesByKey;
  unsigned made = 0;
  for (size_t next = 0; next < worklist.size(); ++next) {
    func::FuncOp fn = worklist[next];
    SmallVector<func::CallOp> calls;
    fn.walk([&](func::CallOp call) { calls.push_back(call); });
    for (func::CallOp call : calls) {
      auto callee = symbols.lookup<func::FuncOp>(call.getCallee());
      if (!callee || callee.isExternal() || callee == fn)
        continue;
      std::string key;
      for (Value arg : call.getArgOperands())
        key.push_back(floatArrayKind(arg, paramKinds));
      func::FuncOp target = callee;
      if (isKeptCallee(callee) && key.find_first_not_of('-') != std::string::npos) {
        llvm::StringMap<func::FuncOp> &byKey = clonesByKey[callee];
        auto it = byKey.find(key);
        if (it != byKey.end()) {
          target = it->second;
        } else if (byKey.empty()) {
          byKey[key] = callee; // the first key keeps the original
        } else {
          // SymbolTable::insert makes the clone's name unique.
          target = cast<func::FuncOp>(callee->clone());
          symbols.insert(target, Block::iterator(callee->getNextNode()));
          byKey[key] = target;
          ++made;
        }
      }
      if (target != callee)
        call.setCallee(target.getName());
      if (queued.insert(target.getOperation()).second) {
        for (auto [arg, kind] : llvm::zip(target.getArguments(), key))
          if (kind != '-')
            paramKinds[arg] = kind;
        worklist.push_back(target);
      }
    }
  }
  return made;
}

unsigned estimateCallOccupancy(
    func::FuncOp fn, SymbolTableCollection &symbolTable,
    SmallPtrSetImpl<Operation *> &stack,
    llvm::function_ref<bool(Operation *access, Value mem)> ignore) {
  if (!stack.insert(fn.getOperation()).second)
    return 1;
  unsigned cycles = 1;
  llvm::MapVector<std::pair<Value, Operation *>, unsigned> perMemory;
  // One access per distinct (memory, read/write, address) of the unrolled
  // body: the repeated loads of one element are one read after CSE, as in
  // Vitis (w3h_cb_nest64: q[i][d] read once per (i, d), not per j; II 8).
  std::set<std::tuple<const void *, bool, const void *,
                      std::vector<const void *>>>
      seen;
  fn.walk([&](Operation *op) {
    Value mem;
    bool isWrite = false;
    Attribute map;
    ValueRange indices;
    if (auto l = dyn_cast<affine::AffineLoadOp>(op)) {
      mem = l.getMemRef();
      map = l.getMapAttr();
      indices = l.getMapOperands();
    } else if (auto s = dyn_cast<affine::AffineStoreOp>(op)) {
      mem = s.getMemRef();
      isWrite = true;
      map = s.getMapAttr();
      indices = s.getMapOperands();
    } else if (auto l = dyn_cast<memref::LoadOp>(op)) {
      mem = l.getMemRef();
      indices = l.getIndices();
    } else if (auto s = dyn_cast<memref::StoreOp>(op)) {
      mem = s.getMemRef();
      isWrite = true;
      indices = s.getIndices();
    } else if (auto call = dyn_cast<CallOpInterface>(op)) {
      if (auto callee = dyn_cast_or_null<func::FuncOp>(
              call.resolveCallableInTable(&symbolTable)))
        if (!callee.isExternal())
          cycles = std::max(cycles, estimateCallOccupancy(callee, symbolTable,
                                                          stack, ignore));
      return;
    }
    if (!mem || (ignore && ignore(op, mem)))
      return;
    std::vector<const void *> address;
    for (Value v : indices)
      address.push_back(v.getAsOpaquePointer());
    const void *memKey = mem.getAsOpaquePointer();
    const void *mapKey = map ? map.getAsOpaquePointer() : nullptr;
    // A load of an element this body wrote before is served by the stored
    // value (store-to-load forwarding: the `s[i][j] +=` chain of
    // w3h_cb_nest64 writes s 16 times and reads it never).
    if (!isWrite && seen.count({memKey, true, mapKey, address}))
      return;
    if (!seen.insert({memKey, isWrite, mapKey, std::move(address)}).second)
      return;
    StorageRoot root = storageRoot(mem);
    ++perMemory[{root.value, root.global}];
  });
  for (auto &[key, n] : perMemory)
    cycles = std::max(cycles, (n + 1) / 2);
  stack.erase(fn.getOperation());
  return cycles;
}

unsigned refreshCallOccupancies(ModuleOp module) {
  SymbolTableCollection symbolTable;
  // The parameters every call site binds to registers, to a fixpoint (a
  // window passed down through two kept functions).
  llvm::DenseMap<Operation *, SmallVector<CallOpInterface>> callers;
  module.walk([&](CallOpInterface call) {
    if (auto callee = dyn_cast_or_null<func::FuncOp>(
            call.resolveCallableInTable(&symbolTable)))
      if (!callee.isExternal())
        callers[callee.getOperation()].push_back(call);
  });
  llvm::DenseSet<Value> registerParams;
  auto isRegisters = [&](Value mem) {
    StorageRoot root = storageRoot(mem);
    if (root.global)
      return root.global->hasAttr(kRegistersAttrName);
    if (Operation *def = root.value.getDefiningOp())
      return def->hasAttr(kRegistersAttrName);
    return registerParams.contains(root.value);
  };
  for (bool changed = true; changed;) {
    changed = false;
    for (auto &[fnOp, calls] : callers) {
      auto fn = cast<func::FuncOp>(fnOp);
      for (BlockArgument arg : fn.getArguments()) {
        if (!isa<MemRefType>(arg.getType()) || registerParams.contains(arg))
          continue;
        bool all = llvm::all_of(calls, [&](CallOpInterface call) {
          unsigned n = arg.getArgNumber();
          return n < call.getArgOperands().size() &&
                 isRegisters(call.getArgOperands()[n]);
        });
        if (all) {
          registerParams.insert(arg);
          changed = true;
        }
      }
    }
  }
  auto ignore = [&](Operation *access, Value mem) {
    if (isRegisters(mem))
      return true;
    return isa<affine::AffineLoadOp, memref::LoadOp>(access) &&
           access->use_empty();
  };
  unsigned changedCalls = 0;
  module.walk([&](CallOpInterface call) {
    auto occ = call->getAttrOfType<IntegerAttr>(kCallOccupancyAttr);
    auto callee = dyn_cast_or_null<func::FuncOp>(
        call.resolveCallableInTable(&symbolTable));
    if (!occ || !callee || callee.isExternal())
      return;
    SmallPtrSet<Operation *, 8> stack;
    unsigned now = estimateCallOccupancy(callee, symbolTable, stack, ignore);
    if (now == static_cast<unsigned>(occ.getInt()))
      return;
    Builder b(call.getContext());
    call->setAttr(kCallOccupancyAttr, b.getI64IntegerAttr(now));
    // hls.call_depth was max(model depth, occupancy); the model's depth is
    // recorded only when the occupancy decided it.
    if (auto est = call->getAttrOfType<IntegerAttr>(kCallDepthEstimateAttr))
      call->setAttr(kCallDepthAttr,
                    b.getI64IntegerAttr(std::max<int64_t>(est.getInt(), now)));
    else if (auto depth = call->getAttrOfType<IntegerAttr>(kCallDepthAttr);
             depth && depth.getInt() < now)
      call->setAttr(kCallDepthAttr, b.getI64IntegerAttr(now));
    ++changedCalls;
  });
  return changedCalls;
}

} // namespace circt::hls_analysis
