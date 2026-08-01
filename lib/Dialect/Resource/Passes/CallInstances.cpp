

// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#include "circt/Dialect/Resource/Passes/CallInstances.h"
#include "mlir/Dialect/MemRef/IR/MemRef.h"
#include "mlir/IR/SymbolTable.h"
#include "mlir/Interfaces/SideEffectInterfaces.h"
#include "mlir/Interfaces/ViewLikeInterface.h"
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
struct UnionFind {
  SmallVector<unsigned> portValue;
  explicit UnionFind(unsigned elementCount) : portValue(elementCount) {
    for (unsigned loopIndex = 0; loopIndex < elementCount; ++loopIndex)
      portValue[loopIndex] = loopIndex;
  }
  unsigned find(unsigned exprValue) {
    while (portValue[exprValue] != exprValue) {
      portValue[exprValue] = portValue[portValue[exprValue]];
      exprValue = portValue[exprValue];
    }
    return exprValue;
  }
  void join(unsigned arrayValue, unsigned buildPoint) {
    arrayValue = find(arrayValue);
    buildPoint = find(buildPoint);
    if (arrayValue != buildPoint)
      portValue[std::max(arrayValue, buildPoint)] =
          std::min(arrayValue, buildPoint);
  }
};

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

static void readsWrites(Operation *op,
                        const SmallVectorImpl<StorageRoot> &roots, bool &reads,
                        bool &writes) {
  reads = writes = false;
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
  auto eff = dyn_cast<MemoryEffectOpInterface>(op);
  if (!eff || isa<CallOpInterface>(op)) {
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
  UnionFind uf(elementCount);
  unsigned byArray = 0, byValue = 0;

  SmallVector<SmallVector<StorageRoot, 4>> roots(elementCount);
  for (unsigned loopIndex = 0; loopIndex < elementCount; ++loopIndex)
    memrefRoots(sites[loopIndex], roots[loopIndex]);
  for (unsigned loopIndex = 0; loopIndex < elementCount; ++loopIndex)
    for (unsigned innerIndex = loopIndex + 1; innerIndex < elementCount;
         ++innerIndex)
      if (uf.find(loopIndex) != uf.find(innerIndex) &&
          hasRootIn(roots[loopIndex], roots[innerIndex])) {
        uf.join(loopIndex, innerIndex);
        ++byArray;
      }

  SmallVector<Operation *> order;
  DenseMap<Operation *, unsigned> ordinal;
  parent.getBody().walk<WalkOrder::PreOrder>([&](Operation *op) {
    ordinal[op] = order.size();
    order.push_back(op);
  });
  DenseMap<Operation *, unsigned> siteIdx;
  for (unsigned loopIndex = 0; loopIndex < elementCount; ++loopIndex)
    siteIdx[sites[loopIndex]] = loopIndex;

  for (unsigned loopIndex = 0; loopIndex + 1 < elementCount; ++loopIndex) {
    DenseSet<Value> tainted;
    SmallVector<StorageRoot, 4> taintedRoots;
    DenseSet<Operation *> taintedOps;
    auto taintOp = [&](Operation *op) {
      if (!taintedOps.insert(op).second)
        return;
      for (Value resultValue : op->getResults())
        tainted.insert(resultValue);
      for (Region &region : op->getRegions())
        for (Block &buildPoint : region)
          for (BlockArgument arrayValue : buildPoint.getArguments())
            tainted.insert(arrayValue);
      bool reads, writes;

      SmallVector<StorageRoot, 4> own;
      memrefRoots(op, own);
      if (!own.empty()) {
        readsWrites(op, own, reads, writes);
        if (writes)
          for (const StorageRoot &resultValue : own)
            taintedRoots.push_back(resultValue);
      }
    };
    taintOp(sites[loopIndex]);
    unsigned start = ordinal[sites[loopIndex]];
    bool changed = true;
    for (unsigned round = 0; changed && round < 8; ++round) {
      changed = false;
      for (unsigned portValue = start + 1; portValue < order.size();
           ++portValue) {
        Operation *op = order[portValue];
        if (taintedOps.contains(op))
          continue;
        bool hit = llvm::any_of(op->getOperands(), [&](Value valueHandle) {
          return tainted.contains(valueHandle);
        });
        if (!hit && !taintedRoots.empty()) {
          bool reads, writes;
          readsWrites(op, taintedRoots, reads, writes);
          hit = reads;
        }
        if (!hit)
          continue;
        size_t before = taintedOps.size();
        taintOp(op);

        if (op->hasTrait<OpTrait::IsTerminator>())
          if (Operation *regionOp = op->getParentOp())
            if (regionOp != parent.getOperation() &&
                !isa<func::FuncOp>(regionOp)) {
              for (Value resultValue : regionOp->getResults())
                if (tainted.insert(resultValue).second)
                  changed = true;
            }
        if (taintedOps.size() != before)
          changed = true;
      }
    }
    for (unsigned innerIndex = loopIndex + 1; innerIndex < elementCount;
         ++innerIndex) {
      if (uf.find(loopIndex) == uf.find(innerIndex))
        continue;
      if (taintedOps.contains(sites[innerIndex])) {
        uf.join(loopIndex, innerIndex);
        ++byValue;
      }
    }
  }

  DenseMap<unsigned, unsigned> comp;
  unsigned groups = 0;
  for (unsigned loopIndex = 0; loopIndex < elementCount; ++loopIndex) {
    unsigned resultValue = uf.find(loopIndex);
    auto it = comp.find(resultValue);
    if (it == comp.end())
      it = comp.insert({resultValue, groups++}).first;
    group[loopIndex] = it->second;
  }
  unsigned before = groups;
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
      if (limit)
        stringValue += "; allocation limit " + std::to_string(*limit) +
                       (before > groups ? " applied" : " not binding");
      stringValue += ")";
    }
    *rule = stringValue;
  }
  return groups;
}

unsigned InstanceModel::instancesAt(Operation *op) const {
  if (auto function = op->getParentOfType<func::FuncOp>())
    return instancesOf(function);
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

InstanceModel computeInstances(ModuleOp rootModule,
                               llvm::function_ref<bool(func::FuncOp)> inScope) {
  InstanceModel memoryOp;
  SmallVector<func::FuncOp> funcs;
  for (auto function : rootModule.getOps<func::FuncOp>())
    if (!function.isExternal() && (!inScope || inScope(function)))
      funcs.push_back(function);
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
