

// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#include "circt/Dialect/Resource/Passes/CallInstances.h"
#include "circt/Dialect/LoopSchedule/LoopScheduleOps.h"
#include "circt/Dialect/Resource/Config/Config.h"
#include "circt/Dialect/Resource/Passes/ConstantIndex.h"
#include "circt/Dialect/Resource/Passes/LoopPragmas.h"
#include "circt/Dialect/Resource/Passes/PartitionLayout.h"
#include "circt/Dialect/Resource/Passes/PolygeistCompat.h"
#include "circt/Dialect/Resource/Passes/ReadOnlyMemory.h"
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
static bool mutuallyExclusive(Operation *arrayValue, Operation *b) {

  auto armsOf = [](Operation *op) -> ArrayRef<int64_t> {
    if (auto at = op->getAttrOfType<DenseI64ArrayAttr>(kIfArmsAttr))
      return at.asArrayRef();
    return {};
  };
  ArrayRef<int64_t> ha = armsOf(arrayValue), hb = armsOf(b);
  for (size_t exprValue = 0; exprValue + 1 < ha.size(); exprValue += 2)
    for (size_t rowValue = 0; rowValue + 1 < hb.size(); rowValue += 2)
      if (ha[exprValue] == hb[rowValue] &&
          ha[exprValue + 1] != hb[rowValue + 1])
        return true;
  for (Operation *portValue = arrayValue->getParentOp(); portValue;
       portValue = portValue->getParentOp()) {
    if (!portValue->isProperAncestor(b))
      continue;
    if (!isa<scf::IfOp, affine::AffineIfOp, scf::IndexSwitchOp>(portValue))
      return false;
    Region *ra = regionUnder(arrayValue, portValue),
           *rb = regionUnder(b, portValue);
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
    for (unsigned b = 0; b < memoryOp; ++b) {
      if (b == arrayValue || visited[b] ||
          !reach[nodes[arrayValue]].test(nodes[b]))
        continue;
      visited[b] = 1;
      if (matchR[b] < 0 || augment(static_cast<unsigned>(matchR[b]))) {
        matchR[b] = static_cast<int>(arrayValue);
        return true;
      }
    }
    return false;
  };
  for (unsigned arrayValue = 0; arrayValue < memoryOp; ++arrayValue) {
    visited.assign(memoryOp, 0);
    (void)augment(arrayValue);
  }
  for (unsigned b = 0; b < memoryOp; ++b)
    if (matchR[b] >= 0)
      next[matchR[b]] = static_cast<int>(b);

  SmallVector<int> chainOfNode(memoryOp, -1);
  unsigned chains = 0;
  for (unsigned b = 0; b < memoryOp; ++b) {
    if (matchR[b] >= 0)
      continue;
    for (int candidateValue = static_cast<int>(b); candidateValue >= 0;
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

static std::optional<SmallVector<int64_t, 2>> constantElementPath(Value mem) {
  SmallVector<int64_t, 2> path;
  while (Operation *def = mem.getDefiningOp()) {
    if (isa<memref::GetGlobalOp>(def))
      break;
    auto view = dyn_cast<ViewLikeOpInterface>(def);
    if (!view)
      break;

    if (isa<memref::CastOp>(def)) {
      mem = view.getViewSource();
      continue;
    }
    if (!isa<circt::hls_analysis::SubIndexOp>(def))
      return std::nullopt;
    std::optional<int64_t> keyValue = getConstantIndexValue(def->getOperand(1));
    if (!keyValue)
      return std::nullopt;
    path.insert(path.begin(), *keyValue);
    mem = view.getViewSource();
  }
  return path;
}

static std::optional<SmallVector<int64_t, 2>>
constantElementPathAt(Operation *callSite, unsigned index) {
  std::optional<SmallVector<int64_t, 2>> path =
      constantElementPath(callSite->getOperand(index));
  if (!path)
    return path;
  auto ci = dyn_cast<CallOpInterface>(callSite);
  auto callee = ci ? dyn_cast_or_null<func::FuncOp>(ci.resolveCallable())
                   : func::FuncOp();
  if (!callee || index + 1 >= callee.getNumArguments() ||
      index + 1 >= callSite->getNumOperands() ||
      !callee.getArgAttr(index + 1, circt::hls_analysis::kViewIndexArgAttr))
    return path;
  std::optional<int64_t> keyValue =
      getConstantIndexValue(callSite->getOperand(index + 1));
  if (!keyValue)
    return std::nullopt;
  path->push_back(*keyValue);
  return path;
}

static bool isStreamArray(Value root) {
  SmallVector<Value> work{root};
  DenseSet<Value> seen{root};
  while (!work.empty() && seen.size() < 256) {
    Value valueHandle = work.pop_back_val();
    for (OpOperand &use : valueHandle.getUses()) {
      Operation *user = use.getOwner();
      if (auto callSite = dyn_cast<CallOpInterface>(user)) {
        if (auto symbolName = dyn_cast_if_present<SymbolRefAttr>(
                callSite.getCallableForCallee()))
          if (parseStreamMethod(symbolName.getLeafReference().getValue()))
            return true;
        auto args = callSite.getArgOperands();
        unsigned first = args.getBeginOperandIndex();
        unsigned keyValue = use.getOperandNumber();
        auto callee =
            dyn_cast_or_null<func::FuncOp>(callSite.resolveCallable());
        if (callee && !callee.isExternal() && keyValue >= first &&
            keyValue - first < callee.getNumArguments() &&
            seen.insert(callee.getArgument(keyValue - first)).second)
          work.push_back(callee.getArgument(keyValue - first));
        continue;
      }
      if (isa<ViewLikeOpInterface>(user))
        for (Value resultValue : user->getResults())
          if (isa<BaseMemRefType>(resultValue.getType()) &&
              seen.insert(resultValue).second)
            work.push_back(resultValue);
    }
  }
  return false;
}

static bool sharesObject(Operation *arrayValue, Operation *b,
                         DenseMap<Value, bool> &streamArrays) {
  for (OpOperand &ox : arrayValue->getOpOperands()) {
    Value exprValue = ox.get();
    if (!isa<BaseMemRefType>(exprValue.getType()))
      continue;
    StorageRoot rx = storageRoot(exprValue);
    for (OpOperand &oy : b->getOpOperands()) {
      Value rowValue = oy.get();
      if (!isa<BaseMemRefType>(rowValue.getType()) ||
          storageRoot(rowValue) != rx)
        continue;
      if (rx.value) {
        auto [it, fresh] = streamArrays.try_emplace(rx.value, false);
        if (fresh)
          it->second = isStreamArray(rx.value);
        if (it->second) {
          auto px = constantElementPathAt(arrayValue, ox.getOperandNumber()),
               py = constantElementPathAt(b, oy.getOperandNumber());
          if (px && py) {
            bool differ = false;
            for (size_t keyValue = 0, e = std::min(px->size(), py->size());
                 keyValue < e; ++keyValue)
              differ |= (*px)[keyValue] != (*py)[keyValue];
            if (differ)
              continue;
          }
        }
      }
      return true;
    }
  }
  return false;
}

static bool distinctStreamElements(Operation *arrayValue, Operation *b,
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
  for (auto [op, paths] :
       {std::make_pair(arrayValue, &pa), std::make_pair(b, &pb)})
    for (OpOperand &opHandle : op->getOpOperands()) {
      Value valueHandle = opHandle.get();
      if (!isa<BaseMemRefType>(valueHandle.getType()) ||
          storageRoot(valueHandle) != root)
        continue;
      auto path = constantElementPathAt(op, opHandle.getOperandNumber());
      if (!path)
        return false;
      paths->push_back(*path);
    }
  if (pa.empty() || pb.empty())
    return false;
  for (const auto &exprValue : pa)
    for (const auto &rowValue : pb) {
      bool differ = false;
      for (size_t keyValue = 0, e = std::min(exprValue.size(), rowValue.size());
           keyValue < e; ++keyValue)
        differ |= exprValue[keyValue] != rowValue[keyValue];
      if (!differ)
        return false;
    }
  return true;
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
      for (auto &e : effects)
        if ((e.getValue() == cur && !isa<MemoryEffects::Read>(e.getEffect())) ||
            (!e.getValue() && isa<MemoryEffects::Write>(e.getEffect())))
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
  for (auto &e : effects) {
    Value valueHandle = e.getValue();
    if (!valueHandle || !isa<BaseMemRefType>(valueHandle.getType()) ||
        !inRoots(valueHandle))
      continue;
    if (isa<MemoryEffects::Read>(e.getEffect()))
      reads = true;
    else if (isa<MemoryEffects::Write>(e.getEffect()))
      writes = true;
  }
}
} // namespace

static void
dataOperandMemories(Operation *site,
                    SmallVectorImpl<std::pair<StorageRoot, Operation *>> &out) {
  SmallVector<Value, 8> work;
  if (auto callSite = dyn_cast<CallOpInterface>(site))
    work.append(callSite.getArgOperands().begin(),
                callSite.getArgOperands().end());
  else
    work.append(site->getOperands().begin(), site->getOperands().end());
  llvm::SmallPtrSet<Operation *, 32> seen;
  constexpr unsigned kMaxOps = 256;
  for (unsigned steps = 0; !work.empty() && steps < 4 * kMaxOps; ++steps) {
    Value valueHandle = work.pop_back_val();
    if (isa<BaseMemRefType>(valueHandle.getType()))
      continue;
    Operation *def = valueHandle.getDefiningOp();
    if (!def)
      continue;

    if (def->getNumRegions() == 1 && def->getRegion(0).hasOneBlock()) {
      Operation *term = def->getRegion(0).front().getTerminator();
      if (term && term->getNumOperands() == def->getNumResults()) {
        work.push_back(
            term->getOperand(cast<OpResult>(valueHandle).getResultNumber()));
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

static unsigned memoryReadPorts(const StorageRoot &root, unsigned ports) {
  auto arg = dyn_cast_or_null<BlockArgument>(root.value);
  if (!arg)
    return ports;
  auto fn = dyn_cast_or_null<func::FuncOp>(arg.getOwner()->getParentOp());
  auto type = dyn_cast<MemRefType>(arg.getType());
  if (!fn || !type || arg.getOwner() != &fn.getBody().front())
    return ports;
  auto spec =
      fn.getArgAttrOfType<ArrayAttr>(arg.getArgNumber(), "hls.array_partition");
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

unsigned
groupConcurrentCalls(func::FuncOp parent, ArrayRef<Operation *> sites,
                     std::optional<int64_t> limit,
                     SmallVectorImpl<unsigned> &group, std::string *rule,
                     llvm::function_ref<bool(unsigned, unsigned)> alsoOrdered) {
  unsigned elementCount = sites.size();
  group.assign(elementCount, 0);
  if (elementCount == 0)
    return 0;

  SmallVector<bool> isProcess(elementCount, false);
  unsigned processes = 0;
  if (parent->hasAttr("hls.dataflow"))
    for (unsigned loopIndex = 0; loopIndex < elementCount; ++loopIndex)
      if (isa<CallOpInterface>(sites[loopIndex]) &&
          sites[loopIndex]->getParentOp() == parent.getOperation()) {
        isProcess[loopIndex] = true;
        ++processes;
      }
  if (processes == elementCount) {
    for (unsigned loopIndex = 0; loopIndex < elementCount; ++loopIndex)
      group[loopIndex] = loopIndex;
    if (rule)
      *rule = std::to_string(elementCount) + " call site(s) -> " +
              std::to_string(elementCount) +
              " instance(s) (dataflow region: every call site is a process "
              "of its own)";
    return elementCount;
  }

  SmallVector<llvm::BitVector> before(elementCount,
                                      llvm::BitVector(elementCount));
  unsigned byArray = 0, byValue = 0, byBranch = 0, byCaller = 0;
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
  DenseMap<Value, bool> streamArrays;
  bool distinctStreams =
      circt::hlsest::Config::get().tool.hls.streams.distinctElementInstances;
  for (unsigned loopIndex = 0; loopIndex < elementCount; ++loopIndex)
    for (unsigned innerIndex = loopIndex + 1; innerIndex < elementCount;
         ++innerIndex)
      if (writesGlobal ||
          (hasRootIn(roots[loopIndex], roots[innerIndex]) &&
           (!distinctStreams ||
            sharesObject(sites[loopIndex], sites[innerIndex], streamArrays))))
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

  DenseMap<Operation *, Operation *> outermostLoopOf;
  DenseMap<Operation *, unsigned> lastOrdinalOf;
  auto outermostLoop = [&](Operation *arrayValue) -> Operation * {
    auto [it, fresh] = outermostLoopOf.try_emplace(arrayValue, nullptr);
    if (fresh)
      for (Operation *portValue = arrayValue->getParentOp();
           portValue && portValue != parentOp;
           portValue = portValue->getParentOp())
        if (isLoop(portValue))
          it->second = portValue;
    return it->second;
  };
  auto shareLoop = [&](Operation *arrayValue, Operation *b) {
    Operation *loop = outermostLoop(arrayValue);
    if (!loop)
      return false;
    auto [it, fresh] = lastOrdinalOf.try_emplace(loop, 0);
    if (fresh) {
      unsigned last = ordinal.lookup(loop);
      loop->walk(
          [&](Operation *op) { last = std::max(last, ordinal.lookup(op)); });
      it->second = last;
    }
    unsigned ob = ordinal.lookup(b);
    return ob > ordinal.lookup(loop) && ob <= it->second;
  };
  auto mayFollow = [&](Operation *earlier, Operation *later) {
    return ordinal.lookup(earlier) < ordinal.lookup(later) ||
           shareLoop(earlier, later);
  };

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
      for (const StorageRoot &resultValue : own) {
        SmallVector<StorageRoot, 1> one{resultValue};
        bool reads, writes;
        readsWrites(op, one, reads, writes, argWrites);
        it->second.push_back({resultValue, reads, writes});
      }
    }
    return it->second;
  };

  for (unsigned loopIndex = 0; loopIndex < elementCount; ++loopIndex) {

    bool allOrdered = true;
    for (unsigned innerIndex = 0; innerIndex < elementCount && allOrdered;
         ++innerIndex)
      if (innerIndex != loopIndex && !before[loopIndex].test(innerIndex) &&
          !before[innerIndex].test(loopIndex))
        allOrdered = false;
    if (allOrdered)
      continue;

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
        for (Block &b : region)
          for (BlockArgument arrayValue : b.getArguments())
            taintValue(arrayValue);

      for (const RootAccess &ra : rootAccesses(op))
        if (ra.writes)
          taintedWrites.push_back({ra.root, op});
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
      for (const RootAccess &ra : rootAccesses(op)) {
        if (!ra.reads)
          continue;
        bool written = llvm::any_of(taintedWrites, [&](const auto &widthValue) {
          return widthValue.first == ra.root && widthValue.second != op &&
                 mayFollow(widthValue.second, op) &&
                 !(distinctStreams &&
                   distinctStreamElements(widthValue.second, op, ra.root,
                                          streamArrays));
        });
        if (written)
          return true;
      }
      return false;
    };
    Operation *site = sites[loopIndex];
    taintOp(site);

    unsigned unresolved = 0;
    for (unsigned innerIndex = 0; innerIndex < elementCount; ++innerIndex)
      if (innerIndex != loopIndex && !before[loopIndex].test(innerIndex) &&
          !before[innerIndex].test(loopIndex))
        ++unresolved;
    auto allReached = [&] {
      unsigned reached = 0;
      for (unsigned innerIndex = 0; innerIndex < elementCount; ++innerIndex)
        if (innerIndex != loopIndex && !before[loopIndex].test(innerIndex) &&
            !before[innerIndex].test(loopIndex) &&
            taintedOps.contains(sites[innerIndex]))
          ++reached;
      return reached == unresolved;
    };
    bool changed = true;
    for (unsigned round = 0; changed && round < 8 && !allReached(); ++round) {
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

  unsigned ports = static_cast<unsigned>(std::max<int64_t>(
      0, circt::hlsest::Config::get().scheduling.callDepth.portsPerMemory));
  unsigned byPorts = 0;
  if (ports > 0 && elementCount > ports) {

    struct Read {
      Operation *op;
      SmallVector<unsigned, 2> calls;
    };
    SmallVector<std::pair<StorageRoot, SmallVector<Read, 8>>, 4> memories;
    for (unsigned loopIndex = 0; loopIndex < elementCount; ++loopIndex) {
      SmallVector<std::pair<StorageRoot, Operation *>, 2> reads;
      dataOperandMemories(sites[loopIndex], reads);
      for (const auto &[root, op] : reads) {
        auto *mem = llvm::find_if(
            memories, [&](const auto &e) { return e.first == root; });
        if (mem == memories.end()) {
          memories.push_back({root, {}});
          mem = std::prev(memories.end());
        }
        auto *read = llvm::find_if(mem->second, [&](const Read &resultValue) {
          return resultValue.op == op;
        });
        if (read == mem->second.end()) {
          mem->second.push_back({op, {}});
          read = std::prev(mem->second.end());
        }
        if (!llvm::is_contained(read->calls, loopIndex))
          read->calls.push_back(loopIndex);
      }
    }
    for (auto &[root, reads] : memories) {
      llvm::stable_sort(
          reads, [&](const Read &exprValue, const Read &rowValue) {
            return ordinal.lookup(exprValue.op) < ordinal.lookup(rowValue.op);
          });
      unsigned portValue = memoryReadPorts(root, ports);
      for (unsigned arrayValue = 0; arrayValue + portValue < reads.size();
           ++arrayValue)
        for (unsigned ci : reads[arrayValue].calls)
          for (unsigned cj : reads[arrayValue + portValue].calls)
            if (ci != cj)
              order(std::min(ci, cj), std::max(ci, cj), byPorts);
    }
  }

  for (unsigned loopIndex = 0; loopIndex < elementCount; ++loopIndex)
    for (unsigned innerIndex = loopIndex + 1; innerIndex < elementCount;
         ++innerIndex)
      if (mutuallyExclusive(sites[loopIndex], sites[innerIndex]))
        order(loopIndex, innerIndex, byBranch);

  if (alsoOrdered)
    for (unsigned loopIndex = 0; loopIndex < elementCount; ++loopIndex)
      for (unsigned innerIndex = loopIndex + 1; innerIndex < elementCount;
           ++innerIndex)
        if (alsoOrdered(loopIndex, innerIndex))
          order(loopIndex, innerIndex, byCaller);

  if (processes > 0)
    for (unsigned loopIndex = 0; loopIndex < elementCount; ++loopIndex)
      for (unsigned innerIndex = 0; innerIndex < elementCount; ++innerIndex)
        if (isProcess[loopIndex] || isProcess[innerIndex])
          before[loopIndex].reset(innerIndex);

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
      if (byCaller)
        stringValue += ", " + std::to_string(byCaller) + " by sequential code";
      if (byPorts)
        stringValue += ", " + std::to_string(byPorts) +
                       " by the ports of a memory " +
                       "their operands are read from";
      if (processes)
        stringValue += "; " + std::to_string(processes) +
                       " of them dataflow processes, an instance each";
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
  auto globalOp = dyn_cast<memref::GlobalOp>(global);
  if (!globalOp || globalOp.getConstant())
    return false;
  auto [it, inserted] = writtenGlobals.try_emplace(global, false);
  if (!inserted)
    return it->second;
  SmallVector<Value> sites;
  if (Operation *table = SymbolTable::getNearestSymbolTable(global)) {
    auto [tit, fresh] = globalSitesByTable.try_emplace(table);
    if (fresh)
      table->walk([&](memref::GetGlobalOp globalUse) {
        tit->second[globalUse.getNameAttr().getAttr()].push_back(
            globalUse.getResult());
      });
    auto sit = tit->second.find(globalOp.getSymNameAttr());
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
  return llvm::any_of(roots, [&](const StorageRoot &resultValue) {
    return resultValue.global && isWrittenGlobal(resultValue.global);
  });
}

void InstanceModel::boundRoots(func::FuncOp fn, unsigned argIndex,
                               SmallVectorImpl<StorageRoot> &out) const {
  SmallPtrSet<Operation *, 8> stack;
  std::function<void(func::FuncOp, unsigned)> walk =
      [&](func::FuncOp fieldValue, unsigned indexValue) {
        if (!stack.insert(fieldValue.getOperation()).second)
          return;
        auto it = parents.find(fieldValue.getOperation());
        if (it != parents.end())
          for (const ParentInstances &pi : it->second)
            for (auto &[siteOp, grp] : pi.siteGroups) {
              (void)grp;
              auto args = cast<CallOpInterface>(siteOp).getArgOperands();
              if (indexValue >= args.size() ||
                  !isa<BaseMemRefType>(args[indexValue].getType()))
                continue;
              StorageRoot root = storageRoot(args[indexValue]);
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
        stack.erase(fieldValue.getOperation());
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
  for (const StorageRoot &resultValue : mine)
    if (llvm::is_contained(*severalArraysRoots, resultValue))
      return true;
  return false;
}

bool InstanceModel::argReachesSharedModule(func::FuncOp fn,
                                           unsigned argIndex) const {
  SmallPtrSet<Operation *, 8> stack;
  std::function<bool(func::FuncOp, unsigned)> shared =
      [&](func::FuncOp fieldValue, unsigned indexValue) -> bool {
    if (calleeArgPortBound(fieldValue, indexValue))
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
