

// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#include "circt/Dialect/Resource/Passes/CallInstances.h"
#include "circt/Dialect/LoopSchedule/LoopScheduleOps.h"
#include "circt/Dialect/Resource/Passes/LoopPragmas.h"
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

func::FuncOp resolveDefinedCallee(CallOpInterface callSite) {
  auto callee = dyn_cast_or_null<func::FuncOp>(callSite.resolveCallable());
  if (!callee || callee.isExternal())
    return nullptr;
  return callee;
}

std::optional<unsigned> callArgIndex(CallOpInterface callSite,
                                     OpOperand &operand) {
  if (operand.getOwner() != callSite.getOperation())
    return std::nullopt;
  MutableOperandRange args = callSite.getArgOperandsMutable();
  unsigned first = args.getAsOperandRange().getBeginOperandIndex();
  unsigned elementCount = operand.getOperandNumber();
  if (args.size() == 0 || elementCount < first ||
      elementCount - first >= args.size())
    return std::nullopt;
  return elementCount - first;
}

StorageRoot storageRoot(Value mem) {
  while (true) {
    Operation *def = mem.getDefiningOp();
    if (!def)
      return {mem, nullptr};
    if (auto globalUse = dyn_cast<memref::GetGlobalOp>(def)) {
      Operation *symbolName =
          SymbolTable::lookupNearestSymbolFrom(def, globalUse.getNameAttr());
      if (auto globalOp = dyn_cast_or_null<memref::GlobalOp>(symbolName))
        return {Value(), globalOp.getOperation()};
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
  if (auto opHandle = callee->getAttrOfType<StringAttr>(kOrigNameAttr))
    orig = opHandle.getValue();
  std::optional<int64_t> best;
  for (Attribute arrayValue : arr) {
    auto dimensionIndex = dyn_cast<DictionaryAttr>(arrayValue);
    if (!dimensionIndex)
      continue;
    if (auto typeValue = dimensionIndex.getAs<StringAttr>("type"))
      if (typeValue.getValue() != "function")
        continue;
    auto lim = dimensionIndex.getAs<IntegerAttr>("limit");
    if (!lim || lim.getInt() <= 0)
      continue;
    auto names = dimensionIndex.getAs<ArrayAttr>("instances");
    bool named = false;
    if (names) {
      for (Attribute elementCount : names)
        if (auto stringValue = dyn_cast<StringAttr>(elementCount))
          if ((!orig.empty() && stringValue.getValue() == orig) ||
              stringValue.getValue() == callee.getName()) {
            named = true;
            break;
          }
    } else if (auto stringValue =
                   dimensionIndex.getAs<StringAttr>("instances")) {
      named = (!orig.empty() && stringValue.getValue() == orig) ||
              stringValue.getValue() == callee.getName();
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
  for (Region *resultValue = op->getParentRegion(); resultValue;) {
    Operation *owner = resultValue->getParentOp();
    if (owner == anc)
      return resultValue;
    if (!owner)
      return nullptr;
    resultValue = owner->getParentRegion();
  }
  return nullptr;
}

/// Whether `a` and `b` can never run in one execution of their nearest
/// common ancestor: it is a conditional (scf.if, affine.if, scf.index_switch)
/// and they lie in different regions of it (W3 review 2 D1, w3r2_k5:
/// `if (sel) work(a, b); else work(c, d);`, Vitis 1 instance, 4 BRAM).
static bool mutuallyExclusive(Operation *arrayValue, Operation *buildPoint) {

  auto armsOf = [](Operation *op) -> ArrayRef<int64_t> {
    if (auto at = op->getAttrOfType<DenseI64ArrayAttr>(kIfArmsAttr))
      return at.asArrayRef();
    return {};
  };
  ArrayRef<int64_t> ha = armsOf(arrayValue), hb = armsOf(buildPoint);
  for (size_t exprValue = 0; exprValue + 1 < ha.size(); exprValue += 2)
    for (size_t rowValue = 0; rowValue + 1 < hb.size(); rowValue += 2)
      if (ha[exprValue] == hb[rowValue] &&
          ha[exprValue + 1] != hb[rowValue + 1])
        return true;
  for (Operation *portValue = arrayValue->getParentOp(); portValue;
       portValue = portValue->getParentOp()) {
    if (!portValue->isProperAncestor(buildPoint))
      continue;
    if (!isa<scf::IfOp, affine::AffineIfOp, scf::IndexSwitchOp>(portValue))
      return false;
    Region *ra = regionUnder(arrayValue, portValue),
           *rb = regionUnder(buildPoint, portValue);
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
  unsigned elementCount = reach.size();

  SmallVector<unsigned> rep(elementCount);
  SmallVector<unsigned> nodes;
  for (unsigned loopIndex = 0; loopIndex < elementCount; ++loopIndex) {
    rep[loopIndex] = loopIndex;
    for (unsigned resultValue : nodes)
      if (reach[loopIndex].test(resultValue) &&
          reach[resultValue].test(loopIndex)) {
        rep[loopIndex] = resultValue;
        break;
      }
    if (rep[loopIndex] == loopIndex)
      nodes.push_back(loopIndex);
  }
  unsigned memoryOp = nodes.size();

  SmallVector<int> matchR(memoryOp, -1), next(memoryOp, -1);
  SmallVector<char> visited;
  std::function<bool(unsigned)> augment = [&](unsigned arrayValue) -> bool {
    for (unsigned buildPoint = 0; buildPoint < memoryOp; ++buildPoint) {
      if (buildPoint == arrayValue || visited[buildPoint] ||
          !reach[nodes[arrayValue]].test(nodes[buildPoint]))
        continue;
      visited[buildPoint] = 1;
      if (matchR[buildPoint] < 0 ||
          augment(static_cast<unsigned>(matchR[buildPoint]))) {
        matchR[buildPoint] = static_cast<int>(arrayValue);
        return true;
      }
    }
    return false;
  };
  for (unsigned arrayValue = 0; arrayValue < memoryOp; ++arrayValue) {
    visited.assign(memoryOp, 0);
    (void)augment(arrayValue);
  }
  for (unsigned buildPoint = 0; buildPoint < memoryOp; ++buildPoint)
    if (matchR[buildPoint] >= 0)
      next[matchR[buildPoint]] = static_cast<int>(buildPoint);

  SmallVector<int> chainOfNode(memoryOp, -1);
  unsigned chains = 0;
  for (unsigned buildPoint = 0; buildPoint < memoryOp; ++buildPoint) {
    if (matchR[buildPoint] >= 0)
      continue;
    for (int candidateValue = static_cast<int>(buildPoint); candidateValue >= 0;
         candidateValue = next[candidateValue])
      chainOfNode[candidateValue] = static_cast<int>(chains);
    ++chains;
  }

  DenseMap<unsigned, unsigned> renumber;
  chainOf.assign(elementCount, 0);
  for (unsigned loopIndex = 0; loopIndex < elementCount; ++loopIndex) {
    unsigned node = llvm::find(nodes, rep[loopIndex]) - nodes.begin();
    unsigned candidateValue = static_cast<unsigned>(chainOfNode[node]);
    auto it = renumber.try_emplace(candidateValue, renumber.size()).first;
    chainOf[loopIndex] = it->second;
  }
  return chains;
}

static void memrefRoots(Operation *op, SmallVectorImpl<StorageRoot> &out) {
  for (Value valueHandle : op->getOperands())
    if (isa<BaseMemRefType>(valueHandle.getType()))
      out.push_back(storageRoot(valueHandle));
}

static bool hasRootIn(ArrayRef<StorageRoot> roots,
                      const SmallVectorImpl<StorageRoot> &set) {
  for (const StorageRoot &resultValue : roots)
    for (const StorageRoot &stringValue : set)
      if (resultValue == stringValue)
        return true;
  return false;
}

using ArgWriteMemo = DenseMap<std::pair<Operation *, unsigned>, bool>;

static bool calleeMayWriteArg(func::FuncOp callee, unsigned indexValue,
                              ArgWriteMemo &memo);

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
          for (Value resultValue : user->getResults())
            if (isa<BaseMemRefType>(resultValue.getType()))
              work.push_back(resultValue);
        continue;
      }
      if (auto callSite = dyn_cast<CallOpInterface>(user)) {
        func::FuncOp inner = resolveDefinedCallee(callSite);
        std::optional<unsigned> innerIndex = callArgIndex(callSite, use);
        if (!inner || !innerIndex || *innerIndex >= inner.getNumArguments() ||
            calleeMayWriteArg(inner, *innerIndex, memo)) {
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
      for (auto &entryValue : effects)
        if ((entryValue.getValue() == cur &&
             !isa<MemoryEffects::Read>(entryValue.getEffect())) ||
            (!entryValue.getValue() &&
             isa<MemoryEffects::Write>(entryValue.getEffect())))
          writes = true;
    }
  }
  return writes;
}

static bool calleeMayWriteArg(func::FuncOp callee, unsigned indexValue,
                              ArgWriteMemo &memo) {
  auto key = std::make_pair(callee.getOperation(), indexValue);
  auto it = memo.find(key);
  if (it != memo.end())
    return it->second;
  memo[key] = true;
  bool writes = mayBeWritten(callee.getArgument(indexValue), memo);
  memo[key] = writes;
  return writes;
}

static bool calleeWritesGlobal(func::FuncOp fn, ArgWriteMemo &memo,
                               SmallPtrSetImpl<Operation *> &visited) {
  if (!visited.insert(fn.getOperation()).second)
    return false;
  bool writes = false;
  fn.walk([&](Operation *op) {
    if (auto globalUse = dyn_cast<memref::GetGlobalOp>(op)) {
      writes = mayBeWritten(globalUse.getResult(), memo);
    } else if (auto callSite = dyn_cast<CallOpInterface>(op)) {
      if (func::FuncOp inner = resolveDefinedCallee(callSite))
        writes = calleeWritesGlobal(inner, memo, visited);
    }
    return writes ? WalkResult::interrupt() : WalkResult::advance();
  });
  return writes;
}

static void
readsWrites(Operation *op, const SmallVectorImpl<StorageRoot> &roots,
            bool &reads, bool &writes,
            DenseMap<std::pair<Operation *, unsigned>, bool> &argWrites) {
  reads = writes = false;
  if (isa<ViewLikeOpInterface>(op))
    return;
  SmallVector<Value, 4> mems;
  for (Value valueHandle : op->getOperands())
    if (isa<BaseMemRefType>(valueHandle.getType()))
      mems.push_back(valueHandle);
  if (mems.empty())
    return;
  auto inRoots = [&](Value valueHandle) {
    StorageRoot resultValue = storageRoot(valueHandle);
    for (const StorageRoot &stringValue : roots)
      if (resultValue == stringValue)
        return true;
    return false;
  };
  if (auto callSite = dyn_cast<CallOpInterface>(op)) {
    func::FuncOp callee = resolveDefinedCallee(callSite);
    for (OpOperand &operand : op->getOpOperands()) {
      Value valueHandle = operand.get();
      if (!isa<BaseMemRefType>(valueHandle.getType()) || !inRoots(valueHandle))
        continue;
      reads = true;
      std::optional<unsigned> indexValue = callArgIndex(callSite, operand);
      if (!callee || !indexValue || *indexValue >= callee.getNumArguments() ||
          calleeMayWriteArg(callee, *indexValue, argWrites))
        writes = true;
    }
    return;
  }
  auto eff = dyn_cast<MemoryEffectOpInterface>(op);
  if (!eff) {
    for (Value valueHandle : mems)
      if (inRoots(valueHandle)) {
        reads = writes = true;
        return;
      }
    return;
  }
  SmallVector<MemoryEffects::EffectInstance> effects;
  eff.getEffects(effects);
  for (auto &entryValue : effects) {
    Value valueHandle = entryValue.getValue();
    if (!valueHandle || !isa<BaseMemRefType>(valueHandle.getType()) ||
        !inRoots(valueHandle))
      continue;
    if (isa<MemoryEffects::Read>(entryValue.getEffect()))
      reads = true;
    else if (isa<MemoryEffects::Write>(entryValue.getEffect()))
      writes = true;
  }
}
} // namespace

unsigned groupConcurrentCalls(func::FuncOp parent, ArrayRef<Operation *> sites,
                              std::optional<int64_t> limit,
                              SmallVectorImpl<unsigned> &group,
                              std::string *rule) {
  unsigned elementCount = sites.size();
  group.assign(elementCount, 0);
  if (elementCount == 0)
    return 0;

  SmallVector<llvm::BitVector> before(elementCount,
                                      llvm::BitVector(elementCount));
  unsigned byArray = 0, byValue = 0, byBranch = 0;
  auto order = [&](unsigned loopIndex, unsigned innerIndex, unsigned &counter) {
    if (before[loopIndex].test(innerIndex) ||
        before[innerIndex].test(loopIndex))
      return;
    before[loopIndex].set(innerIndex);
    ++counter;
  };

  ArgWriteMemo argWrites;
  SmallVector<SmallVector<StorageRoot, 4>> roots(elementCount);
  for (unsigned loopIndex = 0; loopIndex < elementCount; ++loopIndex)
    memrefRoots(sites[loopIndex], roots[loopIndex]);
  bool writesGlobal = false;
  if (auto callSite = dyn_cast<CallOpInterface>(sites.front()))
    if (func::FuncOp callee = resolveDefinedCallee(callSite)) {
      SmallPtrSet<Operation *, 8> stack;
      writesGlobal = calleeWritesGlobal(callee, argWrites, stack);
    }
  for (unsigned loopIndex = 0; loopIndex < elementCount; ++loopIndex)
    for (unsigned innerIndex = loopIndex + 1; innerIndex < elementCount;
         ++innerIndex)
      if (writesGlobal || hasRootIn(roots[loopIndex], roots[innerIndex]))
        order(loopIndex, innerIndex, byArray);

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
  auto shareLoop = [&](Operation *arrayValue, Operation *buildPoint) {
    for (Operation *portValue = arrayValue->getParentOp();
         portValue && portValue != parentOp;
         portValue = portValue->getParentOp())
      if (isLoop(portValue) && portValue->isProperAncestor(buildPoint))
        return true;
    return false;
  };
  auto mayFollow = [&](Operation *earlier, Operation *later) {
    return ordinal.lookup(earlier) < ordinal.lookup(later) ||
           shareLoop(earlier, later);
  };

  for (unsigned loopIndex = 0; loopIndex < elementCount; ++loopIndex) {

    DenseSet<Value> tainted;
    auto taintValue = [&](Value valueHandle) {
      return !isa<BaseMemRefType>(valueHandle.getType()) &&
             tainted.insert(valueHandle).second;
    };

    SmallVector<std::pair<StorageRoot, Operation *>, 4> taintedWrites;
    DenseSet<Operation *> taintedOps;
    auto taintOp = [&](Operation *op) {
      if (!taintedOps.insert(op).second)
        return;
      for (Value resultValue : op->getResults())
        taintValue(resultValue);
      for (Region &region : op->getRegions())
        for (Block &buildPoint : region)
          for (BlockArgument arrayValue : buildPoint.getArguments())
            taintValue(arrayValue);

      SmallVector<StorageRoot, 4> own;
      memrefRoots(op, own);
      if (own.empty())
        return;
      for (const StorageRoot &resultValue : own) {
        SmallVector<StorageRoot, 1> one{resultValue};
        bool reads, writes;
        readsWrites(op, one, reads, writes, argWrites);
        if (writes)
          taintedWrites.push_back({resultValue, op});
      }
    };

    auto taintForwarded = [&](Operation *term) {
      Operation *regionOp = term->getParentOp();
      if (!regionOp || regionOp == parentOp || isa<func::FuncOp>(regionOp))
        return false;
      bool changed = false;
      if (auto pt = dyn_cast<loopschedule::LoopScheduleTerminatorOp>(term)) {
        auto pipe = cast<loopschedule::LoopSchedulePipelineOp>(regionOp);
        for (auto [keyValue, valueHandle] : llvm::enumerate(pt.getIterArgs()))
          if (tainted.contains(valueHandle)) {
            if (keyValue < pipe.getCondBlock().getNumArguments())
              changed |= taintValue(pipe.getCondBlock().getArgument(keyValue));
            if (keyValue < pipe.getStagesBlock().getNumArguments())
              changed |=
                  taintValue(pipe.getStagesBlock().getArgument(keyValue));
          }
        for (auto [keyValue, valueHandle] : llvm::enumerate(pt.getResults()))
          if (tainted.contains(valueHandle) && keyValue < pipe->getNumResults())
            changed |= taintValue(pipe->getResult(keyValue));
        return changed;
      }
      bool oneToOne = term->getNumOperands() == regionOp->getNumResults();
      SmallVector<BlockArgument> iterArgs;
      if (auto loop = dyn_cast<LoopLikeOpInterface>(regionOp))
        if (loop.getRegionIterArgs().size() == term->getNumOperands())
          iterArgs.assign(loop.getRegionIterArgs().begin(),
                          loop.getRegionIterArgs().end());
      for (auto [keyValue, valueHandle] :
           llvm::enumerate(term->getOperands())) {
        if (!tainted.contains(valueHandle))
          continue;
        if (!iterArgs.empty())
          changed |= taintValue(iterArgs[keyValue]);
        if (oneToOne) {
          changed |= taintValue(regionOp->getResult(keyValue));
          continue;
        }
        for (Value resultValue : regionOp->getResults())
          changed |= taintValue(resultValue);
        break;
      }
      return changed;
    };

    auto readsTaintedMemory = [&](Operation *op) {
      SmallVector<StorageRoot, 4> own;
      memrefRoots(op, own);
      for (const StorageRoot &resultValue : own) {
        bool written = llvm::any_of(taintedWrites, [&](const auto &widthValue) {
          return widthValue.first == resultValue && widthValue.second != op &&
                 mayFollow(widthValue.second, op);
        });
        if (!written)
          continue;
        SmallVector<StorageRoot, 1> one{resultValue};
        bool reads, writes;
        readsWrites(op, one, reads, writes, argWrites);
        if (reads)
          return true;
      }
      return false;
    };
    Operation *site = sites[loopIndex];
    taintOp(site);
    bool changed = true;
    for (unsigned round = 0; changed && round < 8; ++round) {
      changed = false;
      for (Operation *op : programOrder) {
        if (op == site || !mayFollow(site, op))
          continue;

        bool isTerminator = op->hasTrait<OpTrait::IsTerminator>();
        if (!isTerminator && taintedOps.contains(op))
          continue;
        bool hit = llvm::any_of(op->getOperands(), [&](Value valueHandle) {
          return tainted.contains(valueHandle);
        });
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
    for (unsigned innerIndex = 0; innerIndex < elementCount; ++innerIndex)
      if (innerIndex != loopIndex && taintedOps.contains(sites[innerIndex]))
        order(loopIndex, innerIndex, byValue);
  }

  for (unsigned loopIndex = 0; loopIndex < elementCount; ++loopIndex)
    for (unsigned innerIndex = loopIndex + 1; innerIndex < elementCount;
         ++innerIndex)
      if (mutuallyExclusive(sites[loopIndex], sites[innerIndex]))
        order(loopIndex, innerIndex, byBranch);

  for (unsigned keyValue = 0; keyValue < elementCount; ++keyValue)
    for (unsigned loopIndex = 0; loopIndex < elementCount; ++loopIndex)
      if (before[loopIndex].test(keyValue))
        before[loopIndex] |= before[keyValue];

  unsigned groups = chainCover(before, group);
  unsigned uncapped = groups;
  if (limit && *limit > 0 && groups > static_cast<unsigned>(*limit)) {
    unsigned cap = static_cast<unsigned>(*limit);
    for (unsigned loopIndex = 0; loopIndex < elementCount; ++loopIndex)
      group[loopIndex] = std::min(group[loopIndex], cap - 1);
    groups = cap;
  }
  if (rule) {
    std::string stringValue = std::to_string(elementCount) +
                              " call site(s) -> " + std::to_string(groups) +
                              " instance(s)";
    if (elementCount > 1) {
      stringValue += " (ordered pairs: " + std::to_string(byArray) +
                     " by a common array, " + std::to_string(byValue) +
                     " by a value dependence";
      if (byBranch)
        stringValue +=
            ", " + std::to_string(byBranch) + " by exclusive branches";
      if (limit)
        stringValue += "; allocation limit " + std::to_string(*limit) +
                       (uncapped > groups ? " applied" : " not binding");
      stringValue += ")";
    }
    *rule = stringValue;
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

  auto ancestors = [&](func::FuncOp fieldValue) {
    SmallPtrSet<Operation *, 8> seen;
    SmallVector<func::FuncOp> work{fieldValue};
    seen.insert(fieldValue.getOperation());
    while (!work.empty()) {
      func::FuncOp cur = work.pop_back_val();
      auto it = callers.find(cur.getOperation());
      if (it == callers.end())
        continue;
      for (func::FuncOp portValue : it->second)
        if (seen.insert(portValue.getOperation()).second)
          work.push_back(portValue);
    }
    return seen;
  };
  SmallPtrSet<Operation *, 8> common = ancestors(users.front());
  for (func::FuncOp useValue : users.drop_front()) {
    SmallPtrSet<Operation *, 8> arrayValue = ancestors(useValue);
    SmallVector<Operation *> drop;
    for (Operation *candidateValue : common)
      if (!arrayValue.contains(candidateValue))
        drop.push_back(candidateValue);
    for (Operation *candidateValue : drop)
      common.erase(candidateValue);
  }
  if (common.empty())
    return nullptr;

  func::FuncOp best;
  for (Operation *candidateValue : common) {
    auto fc = cast<func::FuncOp>(candidateValue);
    bool properAncestor = false;
    for (Operation *dimensionIndex : common) {
      if (dimensionIndex == candidateValue)
        continue;
      SmallPtrSet<Operation *, 8> ad =
          ancestors(cast<func::FuncOp>(dimensionIndex));
      if (ad.contains(candidateValue)) {
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
  func::FuncOp opHandle = owner(users);
  return opHandle ? instancesOf(opHandle) : 1u;
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

  func::FuncOp opHandle = owner(users);
  SmallPtrSet<Operation *, 8> visited;
  while (opHandle && instancesOf(opHandle) != 1) {
    if (!visited.insert(opHandle.getOperation()).second)
      return nullptr;
    auto it = callers.find(opHandle.getOperation());
    if (it == callers.end() || it->second.empty())
      return opHandle;
    opHandle = owner(it->second);
  }
  return opHandle;
}

bool InstanceModel::argReachesSharedModule(func::FuncOp fn,
                                           unsigned argIndex) const {
  SmallPtrSet<Operation *, 8> stack;
  std::function<bool(func::FuncOp, unsigned)> shared =
      [&](func::FuncOp fieldValue, unsigned indexValue) -> bool {
    if (instanceSites(fieldValue) > 1)
      return true;
    if (!stack.insert(fieldValue.getOperation()).second)
      return false;
    bool result = false;
    auto it = parents.find(fieldValue.getOperation());
    if (it != parents.end())
      for (const ParentInstances &pi : it->second) {
        for (auto &[siteOp, grp] : pi.siteGroups) {
          (void)grp;
          auto callSite = cast<CallOpInterface>(siteOp);
          auto args = callSite.getArgOperands();
          if (indexValue >= args.size())
            continue;

          StorageRoot root = storageRoot(args[indexValue]);
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
    stack.erase(fieldValue.getOperation());
    return result;
  };
  return shared(fn, argIndex);
}

InstanceModel computeInstances(ModuleOp module,
                               llvm::function_ref<bool(func::FuncOp)> inScope) {
  InstanceModel memoryOp;
  SmallVector<func::FuncOp> funcs;
  for (auto fn : module.getOps<func::FuncOp>())
    if (!fn.isExternal() && (!inScope || inScope(fn)))
      funcs.push_back(fn);
  DenseSet<Operation *> scope;
  for (func::FuncOp fieldValue : funcs)
    scope.insert(fieldValue.getOperation());

  for (func::FuncOp parent : funcs) {

    llvm::MapVector<Operation *, SmallVector<Operation *>> byCallee;
    parent.getBody().walk<WalkOrder::PreOrder>([&](CallOpInterface callSite) {
      func::FuncOp callee = resolveDefinedCallee(callSite);
      if (!callee || !scope.contains(callee.getOperation()))
        return;
      byCallee[callee.getOperation()].push_back(callSite.getOperation());
    });
    for (auto &[calleeOp, sites] : byCallee) {
      auto callee = cast<func::FuncOp>(calleeOp);
      ParentInstances pi;
      pi.parent = parent;
      pi.callee = callee;
      pi.callSites = sites.size();
      pi.limit = allocationLimit(parent, callee);
      SmallVector<unsigned> group;
      pi.instances =
          groupConcurrentCalls(parent, sites, pi.limit, group, &pi.rule);
      for (unsigned loopIndex = 0; loopIndex < sites.size(); ++loopIndex) {
        pi.siteGroups.push_back({sites[loopIndex], group[loopIndex]});
        memoryOp.sites[sites[loopIndex]] = {parent, callee, group[loopIndex]};
      }
      memoryOp.parents[calleeOp].push_back(std::move(pi));
      auto &cs = memoryOp.callers[calleeOp];
      if (!llvm::is_contained(cs, parent))
        cs.push_back(parent);
    }
  }

  DenseMap<Operation *, unsigned> memo;
  SmallPtrSet<Operation *, 8> onStack;
  std::function<unsigned(func::FuncOp)> mult =
      [&](func::FuncOp fieldValue) -> unsigned {
    auto it = memo.find(fieldValue.getOperation());
    if (it != memo.end())
      return it->second;
    if (!onStack.insert(fieldValue.getOperation()).second) {
      memoryOp.recursive = true;
      return 1;
    }
    unsigned total = 0;
    auto pit = memoryOp.parents.find(fieldValue.getOperation());
    if (pit != memoryOp.parents.end())
      for (const ParentInstances &pi : pit->second)
        total += mult(pi.parent) * pi.instances;
    onStack.erase(fieldValue.getOperation());
    if (pit == memoryOp.parents.end() || pit->second.empty())
      total = 1;
    memo[fieldValue.getOperation()] = total;
    return total;
  };
  for (func::FuncOp fieldValue : funcs)
    memoryOp.multiplicity[fieldValue.getOperation()] = mult(fieldValue);
  return memoryOp;
}

} // namespace circt::hls_analysis
