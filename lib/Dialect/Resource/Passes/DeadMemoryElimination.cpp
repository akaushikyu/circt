//===- DeadMemoryElimination.cpp - drop memory results nobody uses ------- ===//

#include "circt/Dialect/Resource/Passes/VitisCleanup.h"

#include "mlir/Dialect/Affine/Analysis/AffineAnalysis.h"
#include "mlir/Dialect/Affine/IR/AffineOps.h"
#include "mlir/Dialect/Arith/IR/Arith.h"
#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/Dialect/MemRef/IR/MemRef.h"
#include "mlir/Dialect/SCF/IR/SCF.h"
#include "mlir/IR/BuiltinOps.h"
#include "mlir/IR/SymbolTable.h"
#include "mlir/Interfaces/CallInterfaces.h"
#include "mlir/Interfaces/LoopLikeInterface.h"
#include "mlir/Interfaces/SideEffectInterfaces.h"
#include "mlir/Interfaces/ViewLikeInterface.h"
#include "mlir/Pass/Pass.h"

#include "llvm/ADT/DenseSet.h"
#include "llvm/ADT/SetVector.h"
#include "llvm/Support/raw_ostream.h"

#include <string>
#include <vector>

using namespace mlir;

namespace {

struct MemObject {
  Operation *def = nullptr;
  SmallVector<Operation *> anchors;
  SmallVector<Value> aliases;
  SmallVector<Operation *> writers;
  DenseSet<Operation *> functions;
  bool escaping = false;
  std::string escapeReason;
  bool live = false;
};

struct ObjectTable {
  std::vector<MemObject> objs;
  DenseMap<Value, unsigned> objOf;

  void build(ModuleOp rootModule);

  std::optional<unsigned> lookup(Value valueHandle) const {
    auto it = objOf.find(valueHandle);
    if (it == objOf.end())
      return std::nullopt;
    return it->second;
  }

private:
  void close(unsigned id);
};

static StringRef objectName(Operation *def) {
  if (auto variableName = def->getAttrOfType<StringAttr>("polygeist.varname"))
    return variableName.getValue();
  if (auto globalOp = dyn_cast<memref::GlobalOp>(def))
    return globalOp.getSymName();
  return "<unnamed>";
}

void ObjectTable::build(ModuleOp rootModule) {
  rootModule.walk([&](Operation *op) {
    if (!isa<memref::AllocaOp, memref::AllocOp>(op))
      return;
    MemObject opHandle;
    opHandle.def = op;
    opHandle.anchors.push_back(op);
    opHandle.aliases.push_back(op->getResult(0));
    objs.push_back(std::move(opHandle));
  });
  for (auto globalOp : rootModule.getOps<memref::GlobalOp>()) {
    MemObject opHandle;
    opHandle.def = globalOp;
    std::optional<SymbolTable::UseRange> symbolUses =
        SymbolTable::getSymbolUses(globalOp, rootModule);
    if (!symbolUses) {
      opHandle.escaping = true;
      opHandle.escapeReason = "symbol uses unknown";
    } else {
      for (const SymbolTable::SymbolUse &use : *symbolUses) {
        auto globalUse = dyn_cast<memref::GetGlobalOp>(use.getUser());
        if (!globalUse) {
          opHandle.escaping = true;
          opHandle.escapeReason =
              ("symbol used by " + use.getUser()->getName().getStringRef())
                  .str();
          continue;
        }
        opHandle.anchors.push_back(globalUse);
        opHandle.aliases.push_back(globalUse.getResult());
      }
    }
    objs.push_back(std::move(opHandle));
  }
  for (unsigned id = 0; id < objs.size(); ++id)
    close(id);
}

void ObjectTable::close(unsigned id) {
  MemObject &opHandle = objs[id];
  SmallVector<Value> work(opHandle.aliases.begin(), opHandle.aliases.end());
  for (Value valueHandle : work)
    objOf[valueHandle] = id;
  llvm::SetVector<Operation *> writers;
  while (!work.empty()) {
    Value valueHandle = work.pop_back_val();
    if (auto function =
            valueHandle.getParentRegion()->getParentOfType<func::FuncOp>())
      opHandle.functions.insert(function);
    for (OpOperand &use : valueHandle.getUses()) {
      Operation *user = use.getOwner();

      if (auto view = dyn_cast<ViewLikeOpInterface>(user)) {
        if (view.getViewSource() == valueHandle) {
          for (Value resultValue : user->getResults())
            if (isa<BaseMemRefType>(resultValue.getType()) &&
                !objOf.count(resultValue)) {
              objOf[resultValue] = id;
              opHandle.aliases.push_back(resultValue);
              work.push_back(resultValue);
            }
          continue;
        }
      }
      if (isa<memref::DimOp>(user))
        continue;

      bool named = false, writes = false;
      if (auto eff = dyn_cast<MemoryEffectOpInterface>(user)) {
        SmallVector<MemoryEffects::EffectInstance> effects;
        eff.getEffects(effects);
        for (auto &entryValue : effects) {
          if (entryValue.getValue() != valueHandle)
            continue;
          named = true;
          if (isa<MemoryEffects::Write, MemoryEffects::Free>(
                  entryValue.getEffect()))
            writes = true;
        }
      }
      if (named) {
        if (writes)
          writers.insert(user);
        continue;
      }

      if (!opHandle.escaping) {
        opHandle.escaping = true;
        opHandle.escapeReason =
            ("passed to " + user->getName().getStringRef()).str();
      }
    }
  }
  opHandle.writers.assign(writers.begin(), writers.end());
  if (isa<memref::GlobalOp>(opHandle.def) && opHandle.functions.size() > 1 &&
      !opHandle.escaping) {
    opHandle.escaping = true;
    opHandle.escapeReason = "global used by " +
                            std::to_string(opHandle.functions.size()) +
                            " functions";
  }
}

/// True if `op` (not its regions) may read memory of object `id`, or memory
/// it cannot name (unknown effects).
static bool mayReadObject(Operation *op, const ObjectTable &table,
                          unsigned id) {
  if (auto eff = dyn_cast<MemoryEffectOpInterface>(op)) {
    SmallVector<MemoryEffects::EffectInstance> effects;
    eff.getEffects(effects);
    for (auto &entryValue : effects) {
      if (!isa<MemoryEffects::Read>(entryValue.getEffect()))
        continue;
      if (!entryValue.getValue())
        return true;
      std::optional<unsigned> opHandle = table.lookup(entryValue.getValue());
      if (!opHandle || *opHandle == id)
        return true;
    }
    return false;
  }
  if (op->hasTrait<OpTrait::HasRecursiveMemoryEffects>())
    return false;
  return true;
}

static bool subtreeMayReadObject(Operation *root, const ObjectTable &table,
                                 unsigned id, Operation *except = nullptr) {
  bool found = false;
  root->walk([&](Operation *op) {
    if (found || op == except)
      return;
    if (mayReadObject(op, table, id))
      found = true;
  });
  return found;
}

static Value storedMemref(Operation *op) {
  if (auto stringValue = dyn_cast<affine::AffineStoreOp>(op))
    return stringValue.getMemRef();
  if (auto stringValue = dyn_cast<memref::StoreOp>(op))
    return stringValue.getMemRef();
  return {};
}

static Type storedType(Operation *op) {
  if (auto stringValue = dyn_cast<affine::AffineStoreOp>(op))
    return stringValue.getValueToStore().getType();
  if (auto stringValue = dyn_cast<memref::StoreOp>(op))
    return stringValue.getValueToStore().getType();
  return {};
}

static Value accessedMemref(Operation *op) {
  if (Value memoryOp = storedMemref(op))
    return memoryOp;
  if (auto lowerIndex = dyn_cast<affine::AffineLoadOp>(op))
    return lowerIndex.getMemRef();
  if (auto lowerIndex = dyn_cast<memref::LoadOp>(op))
    return lowerIndex.getMemRef();
  return {};
}

/// Same memref value and the same element: equal affine access functions, or
/// the same index values for memref.load / memref.store.
static bool sameAddress(Operation *arrayValue, Operation *buildPoint) {
  Value ma = accessedMemref(arrayValue), mb = accessedMemref(buildPoint);
  if (!ma || ma != mb)
    return false;
  bool affA = isa<affine::AffineLoadOp, affine::AffineStoreOp>(arrayValue);
  bool affB = isa<affine::AffineLoadOp, affine::AffineStoreOp>(buildPoint);
  if (affA && affB)
    return affine::MemRefAccess(arrayValue) == affine::MemRefAccess(buildPoint);
  if (affA || affB)
    return false;
  auto indices = [](Operation *op) -> OperandRange {
    if (auto lowerIndex = dyn_cast<memref::LoadOp>(op))
      return lowerIndex.getIndices();
    return cast<memref::StoreOp>(op).getIndices();
  };
  return llvm::equal(indices(arrayValue), indices(buildPoint));
}

static bool sameAccess(Operation *arrayValue, Operation *buildPoint) {
  return storedMemref(arrayValue) && storedMemref(buildPoint) &&
         storedType(arrayValue) == storedType(buildPoint) &&
         sameAddress(arrayValue, buildPoint);
}

/// Structured ops whose regions run to completion in program order before the
/// next op of the parent block (no early exit), so a store directly after
/// them post-dominates everything inside.
static bool isStructuredParent(Operation *op) {
  return isa<affine::AffineForOp, scf::ForOp, affine::AffineIfOp, scf::IfOp>(
      op);
}

/// `load` reads the element `store` writes, and its value only flows (through
/// side-effect-free ops inside `anchor`) into the stored value of stores to
/// that element: a read-modify-write accumulator. LLVM's LICM keeps such a
/// loop-invariant element in a register (one load before the loop, one store
/// after it), so these reads do not observe anything outside the chain.
static bool isPromotableChainLoad(Operation *load, Operation *store,
                                  Operation *anchor) {
  if (!isa<affine::AffineLoadOp, memref::LoadOp>(load) ||
      !sameAddress(load, store) || load->getNumResults() != 1)
    return false;
  SmallVector<Value> work{load->getResult(0)};
  DenseSet<Value> seen;
  while (!work.empty()) {
    Value valueHandle = work.pop_back_val();
    if (!seen.insert(valueHandle).second)
      continue;
    for (OpOperand &use : valueHandle.getUses()) {
      Operation *user = use.getOwner();
      if (!anchor->isAncestor(user))
        return false;
      if (storedMemref(user)) {

        bool isValue =
            (isa<affine::AffineStoreOp>(user) && use.getOperandNumber() == 0) ||
            (isa<memref::StoreOp>(user) && use.getOperandNumber() == 0);
        if (!isValue || !sameAccess(user, store))
          return false;
        continue;
      }

      if (user->getNumRegions() != 0 || !isMemoryEffectFree(user) ||
          user->hasTrait<OpTrait::IsTerminator>())
        return false;
      for (Value resultValue : user->getResults())
        work.push_back(resultValue);
    }
  }
  return true;
}

/// The store that overwrites `store` before any read, or null.
static Operation *findKiller(Operation *store, const ObjectTable &table,
                             unsigned id) {
  Operation *anchor = store;
  while (true) {

    if (anchor != store) {
      bool blocked = false;
      anchor->walk([&](Operation *op) {
        if (blocked || op == store || !mayReadObject(op, table, id))
          return;
        if (!isPromotableChainLoad(op, store, anchor))
          blocked = true;
      });
      if (blocked)
        return nullptr;
    }
    for (Operation *it = anchor->getNextNode(); it; it = it->getNextNode()) {
      if (it != store && storedMemref(it) && sameAccess(store, it))
        return it;
      if (subtreeMayReadObject(it, table, id))
        return nullptr;
    }
    Operation *parent = anchor->getParentOp();
    if (!parent || !isStructuredParent(parent))
      return nullptr;
    anchor = parent;
  }
}

static unsigned killOverwrittenStores(ModuleOp rootModule, bool remarks) {
  ObjectTable table;
  table.build(rootModule);
  SmallVector<Operation *> dead;
  for (unsigned id = 0; id < table.objs.size(); ++id) {
    const MemObject &opHandle = table.objs[id];
    if (opHandle.escaping)
      continue;
    for (Operation *widthValue : opHandle.writers) {
      if (!storedMemref(widthValue))
        continue;
      if (Operation *keyValue = findKiller(widthValue, table, id)) {
        if (remarks)
          widthValue->emitRemark()
              << "dead-memory-elimination: store to '"
              << objectName(opHandle.def)
              << "' is overwritten before any read by the store "
                 "at "
              << keyValue->getLoc();
        dead.push_back(widthValue);
      }
    }
  }
  for (Operation *op : dead)
    op->erase();
  return dead.size();
}

static bool isHandledLoop(Operation *op) {
  return isa<affine::AffineForOp, scf::ForOp>(op);
}
static bool isHandledIf(Operation *op) {
  return isa<affine::AffineIfOp, scf::IfOp>(op);
}
static bool canMaterializeZero(Type typeValue) {
  return isa<IntegerType, IndexType, FloatType>(typeValue);
}

class Liveness {
public:
  Liveness(ModuleOp rootModule, ObjectTable &table)
      : rootModule(rootModule), typeValue(table) {}

  void run();
  bool isLive(Operation *op) const { return liveOps.contains(op); }
  bool iterLive(Operation *op, unsigned loopIndex) const {
    return liveIdx.contains({op, loopIndex});
  }
  bool isConservative(Operation *op) const { return conservative.contains(op); }

private:
  void markOp(Operation *op) {
    if (liveOps.insert(op).second)
      opWork.push_back(op);
  }
  void markVal(Value valueHandle);
  void markIdx(Operation *op, unsigned loopIndex);
  void markObject(unsigned id);
  void processOp(Operation *op);

  ModuleOp rootModule;
  ObjectTable &typeValue;
  DenseSet<Operation *> liveOps;
  DenseSet<Value> liveVals;
  DenseSet<std::pair<Operation *, unsigned>> liveIdx;
  DenseSet<Operation *> conservative;
  SmallVector<Operation *> opWork;
};

void Liveness::markObject(unsigned id) {
  MemObject &opHandle = typeValue.objs[id];
  if (opHandle.live)
    return;
  opHandle.live = true;
  for (Operation *arrayValue : opHandle.anchors)
    markOp(arrayValue);
  for (Operation *widthValue : opHandle.writers)
    markOp(widthValue);
}

void Liveness::markVal(Value valueHandle) {
  if (!liveVals.insert(valueHandle).second)
    return;
  if (std::optional<unsigned> id = typeValue.lookup(valueHandle))
    markObject(*id);
  if (auto resultValue = dyn_cast<OpResult>(valueHandle)) {
    Operation *def = resultValue.getOwner();
    if (!conservative.contains(def) && (isHandledLoop(def) || isHandledIf(def)))
      markIdx(def, resultValue.getResultNumber());
    markOp(def);
    return;
  }
  auto arrayValue = cast<BlockArgument>(valueHandle);
  Operation *owningFunction = arrayValue.getOwner()->getParentOp();
  if (!owningFunction || isa<func::FuncOp>(owningFunction))
    return;
  if (isHandledLoop(owningFunction) && !conservative.contains(owningFunction)) {
    auto loop = cast<LoopLikeOpInterface>(owningFunction);
    auto iterArgs = loop.getRegionIterArgs();
    for (unsigned loopIndex = 0; loopIndex < iterArgs.size(); ++loopIndex)
      if (iterArgs[loopIndex] == valueHandle)
        markIdx(owningFunction, loopIndex);
  }
  markOp(owningFunction);
}

void Liveness::markIdx(Operation *op, unsigned loopIndex) {
  if (!liveIdx.insert({op, loopIndex}).second)
    return;
  markOp(op);
  if (isHandledLoop(op)) {
    auto loop = cast<LoopLikeOpInterface>(op);
    markVal(loop.getInits()[loopIndex]);
    markVal(loop.getRegionIterArgs()[loopIndex]);
    if (auto yielded = loop.getYieldedValuesMutable())
      markVal((*yielded)[loopIndex].get());
    markVal(op->getResult(loopIndex));
    return;
  }

  for (Region &resultValue : op->getRegions())
    if (!resultValue.empty())
      markVal(resultValue.front().getTerminator()->getOperand(loopIndex));
  markVal(op->getResult(loopIndex));
}

void Liveness::processOp(Operation *op) {
  if (op->getNumRegions() > 0 && !conservative.contains(op) &&
      (isHandledLoop(op) || isHandledIf(op))) {

    DenseSet<unsigned> inits;
    if (isHandledLoop(op))
      for (OpOperand &opHandle :
           cast<LoopLikeOpInterface>(op).getInitsMutable())
        inits.insert(opHandle.getOperandNumber());
    for (OpOperand &opHandle : op->getOpOperands())
      if (!inits.contains(opHandle.getOperandNumber()))
        markVal(opHandle.get());
  } else if (op->getNumRegions() > 0) {

    for (Value valueHandle : op->getOperands())
      markVal(valueHandle);
    for (Region &resultValue : op->getRegions())
      for (Block &buildPoint : resultValue)
        if (!buildPoint.empty() &&
            buildPoint.back().hasTrait<OpTrait::IsTerminator>())
          markOp(&buildPoint.back());
  } else {
    for (Value valueHandle : op->getOperands())
      markVal(valueHandle);
  }
  Operation *parent = op->getParentOp();
  if (parent && !isa<func::FuncOp, ModuleOp>(parent))
    markOp(parent);
}

void Liveness::run() {

  rootModule.walk([&](Operation *op) {
    if (isHandledLoop(op)) {
      for (Value arrayValue : cast<LoopLikeOpInterface>(op).getRegionIterArgs())
        if (!canMaterializeZero(arrayValue.getType()))
          conservative.insert(op);
    } else if (isHandledIf(op)) {
      for (Type memRefType : op->getResultTypes())
        if (!canMaterializeZero(memRefType))
          conservative.insert(op);
    }
  });

  for (unsigned id = 0; id < typeValue.objs.size(); ++id)
    if (typeValue.objs[id].escaping)
      markObject(id);

  rootModule.walk([&](Operation *op) {
    if (isa<func::FuncOp, ModuleOp, memref::GlobalOp>(op))
      return;
    if (!op->getParentOfType<func::FuncOp>())
      return;
    if (op->hasTrait<OpTrait::ReturnLike>() &&
        isa_and_present<func::FuncOp>(op->getParentOp())) {
      markOp(op);
      return;
    }
    if (isa<CallOpInterface>(op)) {
      markOp(op);
      return;
    }
    if (auto eff = dyn_cast<MemoryEffectOpInterface>(op)) {
      SmallVector<MemoryEffects::EffectInstance> effects;
      eff.getEffects(effects);
      for (auto &entryValue : effects) {
        if (isa<MemoryEffects::Read, MemoryEffects::Allocate>(
                entryValue.getEffect()))
          continue;
        if (isa<MemoryEffects::Write, MemoryEffects::Free>(
                entryValue.getEffect()) &&
            entryValue.getValue() && typeValue.lookup(entryValue.getValue()))
          continue;
        markOp(op);
        return;
      }
      return;
    }
    if (op->hasTrait<OpTrait::HasRecursiveMemoryEffects>() ||
        op->hasTrait<OpTrait::IsTerminator>())
      return;
    markOp(op);
  });

  while (!opWork.empty())
    processOp(opWork.pop_back_val());
}

struct DeadMemoryEliminationPass
    : PassWrapper<DeadMemoryEliminationPass, OperationPass<ModuleOp>> {
  MLIR_DEFINE_EXPLICIT_INTERNAL_INLINE_TYPE_ID(DeadMemoryEliminationPass)

  DeadMemoryEliminationPass() = default;
  DeadMemoryEliminationPass(const DeadMemoryEliminationPass &other)
      : PassWrapper(other) {}

  Option<bool> overwrittenStores{
      *this, "overwritten-stores",
      llvm::cl::desc("Delete a store to a local array that a later store "
                     "with the same access overwrites before any read "
                     "(LICM scalar promotion + DSE in Vitis)"),
      llvm::cl::init(true)};
  Option<bool> remarks{
      *this, "remarks",
      llvm::cl::desc("Emit one remark per eliminated array / store"),
      llvm::cl::init(false)};

  StringRef getArgument() const final { return "dead-memory-elimination"; }
  StringRef getDescription() const final {
    return "Remove arrays (allocas, allocs, globals) whose values never reach "
           "a side effect that leaves the function, and the computation that "
           "only fed them (Vitis HLS a.o.1, VITIS_NOTES.md N1a)";
  }
  void getDependentDialects(DialectRegistry &targetRegistry) const override {
    targetRegistry.insert<arith::ArithDialect, memref::MemRefDialect>();
  }

  void runOnOperation() override;

private:
  bool eliminateOnce(ModuleOp rootModule, SmallVectorImpl<Attribute> &records);
};

static Attribute describeDead(Builder &buildPoint, const MemObject &opHandle,
                              StringRef reason) {
  SmallVector<NamedAttribute> fieldValue;
  Operation *def = opHandle.def;
  fieldValue.push_back(buildPoint.getNamedAttr(
      "name", buildPoint.getStringAttr(objectName(def))));
  StringRef opName = def->getName().getStringRef();
  fieldValue.push_back(buildPoint.getNamedAttr(
      "kind",
      buildPoint.getStringAttr(isa<memref::GlobalOp>(def)
                                   ? StringRef("global")
                                   : opName.drop_front(strlen("memref.")))));
  if (auto globalOp = dyn_cast<memref::GlobalOp>(def))
    fieldValue.push_back(buildPoint.getNamedAttr(
        "symbol", buildPoint.getStringAttr(globalOp.getSymName())));
  if (auto function = def->getParentOfType<func::FuncOp>())
    fieldValue.push_back(buildPoint.getNamedAttr(
        "func", buildPoint.getStringAttr(function.getName())));
  else if (!opHandle.anchors.empty())
    if (auto function =
            opHandle.anchors.front()->getParentOfType<func::FuncOp>())
      fieldValue.push_back(buildPoint.getNamedAttr(
          "func", buildPoint.getStringAttr(function.getName())));
  Type memRefType = isa<memref::GlobalOp>(def)
                        ? Type(cast<memref::GlobalOp>(def).getType())
                        : def->getResult(0).getType();
  fieldValue.push_back(
      buildPoint.getNamedAttr("type", TypeAttr::get(memRefType)));
  fieldValue.push_back(
      buildPoint.getNamedAttr("loc", LocationAttr(def->getLoc())));
  fieldValue.push_back(
      buildPoint.getNamedAttr("reason", buildPoint.getStringAttr(reason)));
  if (def->hasAttr("hls.preserve"))
    fieldValue.push_back(
        buildPoint.getNamedAttr("preserve", buildPoint.getUnitAttr()));
  if (auto fg = def->getAttrOfType<StringAttr>("hls.from_global"))
    fieldValue.push_back(buildPoint.getNamedAttr("from_global", fg));
  return buildPoint.getDictionaryAttr(fieldValue);
}

bool DeadMemoryEliminationPass::eliminateOnce(
    ModuleOp rootModule, SmallVectorImpl<Attribute> &records) {
  ObjectTable table;
  table.build(rootModule);
  Liveness live(rootModule, table);
  live.run();

  Builder buildPoint(rootModule.getContext());
  bool changed = false;

  for (const MemObject &opHandle : table.objs) {
    if (opHandle.live)
      continue;
    std::string reason;
    if (opHandle.writers.empty() && opHandle.anchors.size() <= 1 &&
        isa<memref::GlobalOp>(opHandle.def) && opHandle.aliases.empty())
      reason = "never accessed";
    else if (llvm::none_of(opHandle.aliases, [](Value valueHandle) {
               return llvm::any_of(
                   valueHandle.getUsers(), [](Operation *useValue) {
                     auto eff = dyn_cast<MemoryEffectOpInterface>(useValue);
                     return eff && eff.hasEffect<MemoryEffects::Read>();
                   });
             }))
      reason = "write-only: never read";
    else
      reason = "no load from it reaches a side effect that leaves the "
               "function (store to an argument, call, return)";
    if (opHandle.def->hasAttr("hls.preserve"))
      reason += "; hls.preserve does not keep a dead array (Vitis removes it)";
    records.push_back(describeDead(buildPoint, opHandle, reason));
    if (remarks)
      opHandle.def->emitRemark() << "dead-memory-elimination: removed '"
                                 << objectName(opHandle.def) << "': " << reason;
  }

  rootModule.walk([&](Operation *op) {
    if (!live.isLive(op) || live.isConservative(op))
      return;
    if (isHandledLoop(op)) {
      auto loop = cast<LoopLikeOpInterface>(op);
      auto iterArgs = loop.getRegionIterArgs();
      auto yielded = loop.getYieldedValuesMutable();
      for (unsigned loopIndex = 0; loopIndex < iterArgs.size(); ++loopIndex) {
        if (live.iterLive(op, loopIndex))
          continue;
        bool alreadyPassThrough =
            yielded && (*yielded)[loopIndex].get() == iterArgs[loopIndex] &&
            matchPattern(loop.getInitsMutable()[loopIndex].get(), m_Constant());
        if (alreadyPassThrough)
          continue;
        OpBuilder ob(op);
        Type memRefType = iterArgs[loopIndex].getType();
        Value zero = arith::ConstantOp::create(ob, op->getLoc(), memRefType,
                                               ob.getZeroAttr(memRefType));
        loop.getInitsMutable()[loopIndex].set(zero);
        if (yielded)
          (*yielded)[loopIndex].set(iterArgs[loopIndex]);
        changed = true;
      }
    } else if (isHandledIf(op)) {
      for (unsigned loopIndex = 0; loopIndex < op->getNumResults();
           ++loopIndex) {
        if (live.iterLive(op, loopIndex))
          continue;
        bool allConstant =
            llvm::all_of(op->getRegions(), [&](Region &resultValue) {
              return resultValue.empty() ||
                     matchPattern(
                         resultValue.front().getTerminator()->getOperand(
                             loopIndex),
                         m_Constant());
            });
        if (allConstant)
          continue;
        OpBuilder ob(op);
        Type memRefType = op->getResult(loopIndex).getType();
        Value zero = arith::ConstantOp::create(ob, op->getLoc(), memRefType,
                                               ob.getZeroAttr(memRefType));
        for (Region &resultValue : op->getRegions())
          if (!resultValue.empty()) {
            resultValue.front().getTerminator()->setOperand(loopIndex, zero);
            changed = true;
          }
      }
    }
  });

  SmallVector<Operation *> dead;
  for (auto function : rootModule.getOps<func::FuncOp>()) {
    if (function.isExternal())
      continue;
    function.getBody().walk<WalkOrder::PreOrder>([&](Operation *op) {
      if (live.isLive(op))
        return WalkResult::advance();
      if (op->hasTrait<OpTrait::IsTerminator>())
        return WalkResult::advance();

      if (op->getNumRegions() == 0 && isMemoryEffectFree(op) &&
          llvm::any_of(op->getUsers(), [&](Operation *useValue) {
            return live.isLive(useValue) ||
                   useValue->hasTrait<OpTrait::IsTerminator>();
          }))
        return WalkResult::skip();
      dead.push_back(op);
      return WalkResult::skip();
    });
  }
  for (Operation *op : dead)
    op->dropAllReferences();
  for (Operation *op : dead) {
    op->dropAllUses();
    op->erase();
  }
  changed |= !dead.empty();

  for (const MemObject &opHandle : table.objs)
    if (!opHandle.live && isa<memref::GlobalOp>(opHandle.def)) {
      opHandle.def->erase();
      changed = true;
    }
  return changed;
}

void DeadMemoryEliminationPass::runOnOperation() {
  ModuleOp rootModule = getOperation();
  SmallVector<Attribute> records;
  if (auto prev = rootModule->getAttrOfType<ArrayAttr>("hls.dead_memrefs"))
    records.append(prev.begin(), prev.end());

  for (unsigned round = 0; round < 16; ++round) {
    bool changed = false;
    if (overwrittenStores)
      changed |= killOverwrittenStores(rootModule, remarks) > 0;
    changed |= eliminateOnce(rootModule, records);
    if (!changed)
      break;
  }
  if (!records.empty())
    rootModule->setAttr("hls.dead_memrefs",
                        ArrayAttr::get(rootModule.getContext(), records));
}

} // namespace

namespace circt::hls_analysis {
std::unique_ptr<Pass> createDeadMemoryEliminationPass() {
  return std::make_unique<DeadMemoryEliminationPass>();
}

void registerVitisCleanupPasses() {
  PassRegistration<DeadMemoryEliminationPass>();
  registerPass([] { return createVitisFoldPass(); });
  registerPass([] { return createPromoteGlobalsToAllocasPass(); });
}
} // namespace circt::hls_analysis
