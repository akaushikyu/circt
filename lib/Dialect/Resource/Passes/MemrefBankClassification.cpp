

#include "circt/Dialect/Resource/Passes/MemrefBankClassification.h"
#include "circt/Dialect/Resource/Config/ConfigUtils.h"
#include "circt/Dialect/Resource/HLS/HLSOps.h"
#include "circt/Dialect/Resource/Passes/CallInstances.h"
#include "circt/Dialect/Resource/Passes/LoopPragmas.h"
#include "circt/Dialect/Resource/Passes/MemoryRecurrences.h"
#include "mlir/Dialect/Affine/IR/AffineOps.h"
#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/Dialect/MemRef/IR/MemRef.h"
#include "mlir/Dialect/SCF/IR/SCF.h"
#include "mlir/IR/Builders.h"
#include "mlir/IR/BuiltinOps.h"
#include "mlir/IR/BuiltinTypes.h"
#include "mlir/IR/SymbolTable.h"
#include "mlir/Interfaces/CallInterfaces.h"
#include "mlir/Interfaces/LoopLikeInterface.h"
#include "mlir/Interfaces/ViewLikeInterface.h"
#include "llvm/ADT/MapVector.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/Debug.h"

#include <llvm/ADT/TypeSwitch.h>

#include <limits>
#include <map>

#define DEBUG_TYPE "bram-classification"

using namespace mlir;

namespace circt::hls_analysis {

StringRef stringifyStorageMode(StorageMode mode) {
  switch (mode) {
  case StorageMode::OnePort:
    return "1p";
  case StorageMode::SDP:
    return "sdp";
  case StorageMode::TDP:
    return "tdp";
  case StorageMode::OneWriteNRead:
    return "1wnr";
  case StorageMode::Registers:
    return "registers";
  }
  return "?";
}

/// Ports of one block RAM in the configuration a non-replicable bank is
/// priced at (the device's `tdp`: 2).
static unsigned blockRamPorts() {
  const circt::hlsest::Config &cfg = circt::hlsest::Config::get();
  const circt::hlsest::MemoryArchitectureConfig &ma =
      cfg.tool.hls.memoryArchitecture;
  if (const circt::hlsest::DeviceMemory *memoryOp =
          cfg.device.memory(cfg.tool.backend.memoryMapper.primitive))
    if (const circt::hlsest::PortConfig *pc =
            memoryOp->portConfig(ma.pricedNarrow))
      return static_cast<unsigned>(pc->ports.size());
  return kDualPortSlots;
}

unsigned storageModeSlots(StorageMode mode) {
  switch (mode) {
  case StorageMode::OnePort:
    return 1;
  case StorageMode::SDP:
  case StorageMode::TDP:
    return blockRamPorts();
  case StorageMode::OneWriteNRead:

    return static_cast<unsigned>(
        circt::hlsest::Config::get()
            .tool.hls.memoryArchitecture.replicatedSlots());
  case StorageMode::Registers:
    return std::numeric_limits<unsigned>::max();
  }
  return blockRamPorts();
}

StringRef stringifyStorageKind(StorageKind mode) {
  switch (mode) {
  case StorageKind::RAM_1P:
    return "ram_1p";
  case StorageKind::RAM_2P:
    return "ram_2p";
  case StorageKind::RAM_1WNR:
    return "ram_1wnr";
  default:
    return "unsupported";
  }
}

StorageKind classifyStorageKind(unsigned reads, unsigned writes) {
  if (reads + writes <= 1)
    return StorageKind::RAM_1P;
  if (writes > 1)
    return StorageKind::RAM_2P;
  return StorageKind::RAM_1WNR;
}

StorageMode classifyMode(unsigned maxStoresPerLoop) {

  if (static_cast<int64_t>(maxStoresPerLoop) >
      circt::hlsest::Config::get()
          .tool.hls.memoryArchitecture.replication.maxStoresPerIteration)
    return StorageMode::TDP;
  return StorageMode::OneWriteNRead;
}

/// Returns the memref operand of a load/store and flags which it was. Returns a
/// null Value for any other op.
static Value getAccessedMemRef(Operation *op, bool &isLoad, bool &isStore) {
  isLoad = isStore = false;

  if (hls_analysis::isPromotedAccess(op))
    return Value{};
  return TypeSwitch<Operation *, Value>(op)
      .Case<affine::AffineLoadOp, memref::LoadOp>([&](auto lowerIndex) {
        isLoad = true;
        return lowerIndex.getMemRef();
      })
      .Case<affine::AffineStoreOp, memref::StoreOp>([&](auto stringValue) {
        isStore = true;
        return stringValue.getMemRef();
      })
      .Case<AffineStoreEnableOp, StoreEnableOp>([&](auto stringValue) {
        isStore = true;
        return stringValue.getMemref();
      })
      .Default(Value{});
}

/// The memref operands of an access op that writes, else null.
static Value storedMemRef(Operation *op) {
  bool isLoad = false, isStore = false;
  Value mem = getAccessedMemRef(op, isLoad, isStore);
  return isStore ? mem : Value();
}

/// A store in the else block of an if whose then block, at top level, stores
/// the same memref through the same map and operands: the two arms are one
/// store after convert-affine-to-loopschedule's if/else merge. (The rule with
/// --hls-exclusive-arm-stores=false.)
static bool pairedWithThenArmStore(Operation *store) {
  Operation *parent = store->getParentOp();
  if (!isa_and_present<scf::IfOp, affine::AffineIfOp>(parent))
    return false;
  if (parent->getNumRegions() < 2 ||
      store->getParentRegion() != &parent->getRegion(1) ||
      parent->getRegion(0).empty())
    return false;
  for (Operation &op : parent->getRegion(0).front()) {
    if (op.getName() != store->getName() ||
        !llvm::equal(op.getOperands().drop_front(),
                     store->getOperands().drop_front()) ||
        storedMemRef(&op) != storedMemRef(store))
      continue;

    if (auto arrayValue = dyn_cast<affine::AffineStoreOp>(op)) {
      auto buildPoint = cast<affine::AffineStoreOp>(store);
      if (arrayValue.getAffineMap() != buildPoint.getAffineMap())
        continue;
    }
    return true;
  }
  return false;
}

static llvm::cl::opt<bool> clExclusiveArmStores(
    "hls-exclusive-arm-stores",
    llvm::cl::desc("Count the stores the two arms of one if make to an array "
                   "once per loop iteration, whatever their addresses, for "
                   "RAM_1WNR replicability (--memory-banking-bram, "
                   "--convert-affine-to-loopschedule, --bram-analysis); off: "
                   "only a same-address pair in the then / else blocks "
                   "counts once"),
    llvm::cl::init(true));

namespace {
/// One arm of one if: the if (an op, or an `hls.if_arms` id) and the arm.
struct IfArm {
  const void *ifOp = nullptr;
  int64_t hoistedId = 0;
  int64_t arm = 0;
  bool sameIf(const IfArm &opHandle) const {
    return ifOp == opHandle.ifOp && hoistedId == opHandle.hoistedId;
  }
};
using ArmPath = SmallVector<IfArm, 4>;
} // namespace

/// The if arms `op` runs under inside `scope`, outermost first.
static ArmPath armPathOf(Operation *op, Operation *scope) {
  ArmPath nested;
  for (Operation *cur = op; cur && cur != scope;) {
    Region *region = cur->getParentRegion();
    Operation *parent = cur->getParentOp();
    if (!region || !parent)
      break;
    if (isa<scf::IfOp, affine::AffineIfOp>(parent))
      nested.push_back({parent, 0, region->getRegionNumber()});
    cur = parent;
  }
  ArmPath path(nested.rbegin(), nested.rend());

  if (auto arms = op->getAttrOfType<DenseI64ArrayAttr>(kIfArmsAttr)) {
    ArrayRef<int64_t> arrayValue = arms.asArrayRef();
    for (size_t loopIndex = arrayValue.size(); loopIndex >= 2; loopIndex -= 2)
      path.push_back(
          {nullptr, arrayValue[loopIndex - 2], arrayValue[loopIndex - 1]});
  }
  return path;
}

/// Stores under no if of level `depth` all run; each if of that level runs
/// one arm, so it adds the most any one of its arms runs. The paths are
/// bucketed by their if and arm in one pass (the former repeated scan was
/// quadratic in the number of ifs: hlsyn symm-opt-medium, 24 % of its run
/// time).
static unsigned maxConcurrent(ArrayRef<const ArmPath *> paths, unsigned depth) {
  unsigned total = 0;

  std::map<std::pair<const void *, int64_t>,
           std::map<int64_t, SmallVector<const ArmPath *>>>
      byIf;
  for (const ArmPath *portValue : paths) {
    if (portValue->size() <= depth) {
      ++total;
      continue;
    }
    const IfArm &arrayValue = (*portValue)[depth];
    byIf[{arrayValue.ifOp, arrayValue.hoistedId}][arrayValue.arm].push_back(
        portValue);
  }
  for (auto &[theIf, arms] : byIf) {
    unsigned best = 0;
    for (auto &[arm, inArm] : arms)
      best = std::max(best, maxConcurrent(inArm, depth + 1));
    total += best;
  }
  return total;
}

/// --hls-exclusive-arm-stores when given, else
/// tool.hls.memory_architecture.replication.exclusive_arm_stores_once.
static bool exclusiveArmStores() {
  return circt::hlsest::resolveGlobalOption(
      clExclusiveArmStores,
      circt::hlsest::Config::get()
          .tool.hls.memoryArchitecture.replication.exclusiveArmStoresOnce);
}

unsigned maxStoresInOneIteration(ArrayRef<Operation *> stores,
                                 Operation *scope) {
  if (!exclusiveArmStores())
    return stores.size();
  SmallVector<ArmPath> paths;
  paths.reserve(stores.size());
  for (Operation *store : stores)
    paths.push_back(armPathOf(store, scope));
  SmallVector<const ArmPath *> refs;
  for (const ArmPath &portValue : paths)
    refs.push_back(&portValue);
  return maxConcurrent(refs, 0);
}

/// Max stores of `mem` per body of one loop of its own function (a store
/// outside every loop does not count), not following calls.
static unsigned localStoresPerLoop(Value mem) {
  llvm::MapVector<Operation *, SmallVector<Operation *>> perLoop;
  for (Operation *user : mem.getUsers()) {
    if (storedMemRef(user) != mem ||
        (!exclusiveArmStores() && pairedWithThenArmStore(user)))
      continue;
    Operation *loop = user->getParentOfType<LoopLikeOpInterface>();
    if (!loop)
      continue;
    perLoop[loop].push_back(user);
  }
  unsigned best = 0;
  for (auto &[loop, stores] : perLoop)
    best = std::max(best, maxStoresInOneIteration(stores, loop));
  return best;
}

namespace {
class CalleeStores {
public:
  /// Max stores per loop body of the memref parameter `idx` of `fn`, in `fn`
  /// and, transitively, in the callees it is passed on to.
  unsigned ofParameter(func::FuncOp fn, unsigned indexValue) {
    auto key = std::make_pair(fn.getOperation(), indexValue);
    if (auto it = memo.find(key); it != memo.end())
      return it->second;
    memo[key] = 0;
    BlockArgument arg = fn.getArgument(indexValue);
    unsigned elementCount =
        std::max(localStoresPerLoop(arg), throughCalls(arg));
    memo[key] = elementCount;
    return elementCount;
  }

  /// Max over the defined callees `mem` is passed to directly.
  unsigned throughCalls(Value mem) {
    unsigned best = 0;
    for (OpOperand &use : mem.getUses()) {
      auto callSite = dyn_cast<CallOpInterface>(use.getOwner());
      if (!callSite)
        continue;
      func::FuncOp callee = resolveDefinedCallee(callSite);
      if (!callee || callee.isExternal())
        continue;
      std::optional<unsigned> indexValue = callArgIndex(callSite, use);
      if (!indexValue || *indexValue >= callee.getNumArguments())
        continue;
      best = std::max(best, ofParameter(callee, *indexValue));
    }
    return best;
  }

private:
  DenseMap<std::pair<Operation *, unsigned>, unsigned> memo;
};
} // namespace

void annotateCalleeStoresPerLoop(ModuleOp module) {
  CalleeStores stores;
  OpBuilder buildPoint(module.getContext());
  module.walk([&](memref::AllocaOp localAlloca) {
    unsigned elementCount = stores.throughCalls(localAlloca.getResult());
    if (elementCount > 1)
      localAlloca->setAttr(kCalleeStoresPerLoopAttr,
                           buildPoint.getI64IntegerAttr(elementCount));
  });
  module.walk([&](func::FuncOp fn) {
    if (fn.isExternal())
      return;
    for (BlockArgument arg : fn.getArguments()) {
      if (!isa<MemRefType>(arg.getType()))
        continue;
      unsigned elementCount = stores.throughCalls(arg);
      if (elementCount > 1)
        fn.setArgAttr(arg.getArgNumber(), kCalleeStoresPerLoopAttr,
                      buildPoint.getI64IntegerAttr(elementCount));
    }
  });
}

namespace {
/// The stores per loop body of the arrays a callee parameter is bound to
/// (N99): over every call site of the callee, the passed value's stores in
/// its own function's loops and in the loops of the callees it is passed to,
/// and, for a value that is itself a parameter, recursively those of its
/// call sites.
class CallerStores {
public:
  explicit CallerStores(ModuleOp module) {
    module.walk([&](CallOpInterface callSite) {
      if (func::FuncOp callee = resolveDefinedCallee(callSite))
        callers[callee.getOperation()].push_back(callSite);
    });
  }

  unsigned ofParameter(func::FuncOp fn, unsigned indexValue) {
    auto key = std::make_pair(fn.getOperation(), indexValue);
    if (auto it = memo.find(key); it != memo.end())
      return it->second;
    memo[key] = 0;
    unsigned best = 0;
    for (CallOpInterface callSite : callers.lookup(fn.getOperation())) {
      if (indexValue >= callSite.getArgOperands().size())
        continue;
      best = std::max(best, ofValue(callSite.getArgOperands()[indexValue]));
    }
    memo[key] = best;
    return best;
  }

private:
  unsigned ofValue(Value valueHandle) {
    if (!isa<MemRefType>(valueHandle.getType()))
      return 0;
    unsigned elementCount = std::max(localStoresPerLoop(valueHandle),
                                     callees.throughCalls(valueHandle));
    if (auto arg = dyn_cast<BlockArgument>(valueHandle))
      if (auto fn = dyn_cast<func::FuncOp>(arg.getOwner()->getParentOp()))
        elementCount =
            std::max(elementCount, ofParameter(fn, arg.getArgNumber()));
    return elementCount;
  }

  CalleeStores callees;
  DenseMap<Operation *, SmallVector<CallOpInterface, 2>> callers;
  DenseMap<std::pair<Operation *, unsigned>, unsigned> memo;
};
} // namespace

void annotateCallerStoresPerLoop(ModuleOp module) {
  CallerStores stores(module);
  OpBuilder buildPoint(module.getContext());
  module.walk([&](func::FuncOp fn) {
    if (fn.isExternal())
      return;
    for (BlockArgument arg : fn.getArguments()) {
      if (!isa<MemRefType>(arg.getType()))
        continue;
      unsigned elementCount = stores.ofParameter(fn, arg.getArgNumber());
      if (elementCount > 1)
        fn.setArgAttr(arg.getArgNumber(), kCallerStoresPerLoopAttr,
                      buildPoint.getI64IntegerAttr(elementCount));
    }
  });
}

namespace {
/// The m_axi bundle a memref value is a port of: a parameter with an
/// `hls.interface` of the mode, or one every call site binds to such a port.
class MaxiBundles {
public:
  MaxiBundles(ModuleOp module, StringRef mode, StringRef defaultBundle)
      : mode(mode), defaultBundle(defaultBundle) {
    module.walk([&](CallOpInterface callSite) {
      if (func::FuncOp callee = resolveDefinedCallee(callSite))
        callers[callee.getOperation()].push_back(callSite);
    });
  }

  /// The bundle of parameter `idx` of `fn` from its own interface; nullopt
  /// when it has none of the mode.
  std::optional<std::string> declared(func::FuncOp fn,
                                      unsigned indexValue) const {
    auto ifaces = fn.getArgAttrOfType<ArrayAttr>(indexValue, "hls.interface");
    if (!ifaces)
      return std::nullopt;
    for (Attribute attr : ifaces) {
      auto dimensionIndex = dyn_cast<DictionaryAttr>(attr);
      auto memoryOp = dimensionIndex ? dimensionIndex.getAs<StringAttr>("mode")
                                     : StringAttr();
      if (!memoryOp || memoryOp.getValue() != mode)
        continue;
      if (auto buildPoint = dimensionIndex.getAs<StringAttr>("bundle"))
        return buildPoint.getValue().str();
      return defaultBundle;
    }
    return std::nullopt;
  }

  /// The bundle every call site of `fn` binds parameter `idx` to; nullopt
  /// when one binds something else, they disagree, or nothing calls it.
  std::optional<std::string> throughCalls(func::FuncOp fn,
                                          unsigned indexValue) {
    auto key = std::make_pair(fn.getOperation(), indexValue);
    if (auto it = memo.find(key); it != memo.end())
      return it->second;
    memo[key] = std::nullopt;
    std::optional<std::string> bundle;
    bool any = false, agree = true;
    for (CallOpInterface callSite : callers.lookup(fn.getOperation())) {
      if (indexValue >= callSite.getArgOperands().size()) {
        agree = false;
        break;
      }
      std::optional<std::string> buildPoint =
          ofValue(callSite.getArgOperands()[indexValue]);
      if (!buildPoint || (any && *buildPoint != *bundle)) {
        agree = false;
        break;
      }
      bundle = buildPoint;
      any = true;
    }
    std::optional<std::string> result =
        any && agree ? bundle : std::optional<std::string>();
    memo[key] = result;
    return result;
  }

private:
  std::optional<std::string> ofValue(Value valueHandle) {
    while (auto view = valueHandle.getDefiningOp<ViewLikeOpInterface>())
      valueHandle = view.getViewSource();
    auto arg = dyn_cast<BlockArgument>(valueHandle);
    if (!arg)
      return std::nullopt;
    auto fn = dyn_cast<func::FuncOp>(arg.getOwner()->getParentOp());
    if (!fn || !isa<BaseMemRefType>(arg.getType()))
      return std::nullopt;
    if (std::optional<std::string> buildPoint =
            declared(fn, arg.getArgNumber()))
      return buildPoint;
    return throughCalls(fn, arg.getArgNumber());
  }

  std::string mode, defaultBundle;
  DenseMap<Operation *, SmallVector<CallOpInterface, 2>> callers;
  DenseMap<std::pair<Operation *, unsigned>, std::optional<std::string>> memo;
};
} // namespace

void annotateMaxiBundlesThroughCalls(ModuleOp module, StringRef mode,
                                     StringRef defaultBundle) {
  MaxiBundles bundles(module, mode, defaultBundle);
  OpBuilder buildPoint(module.getContext());
  module.walk([&](func::FuncOp fn) {
    if (fn.isExternal())
      return;
    for (BlockArgument arg : fn.getArguments()) {
      unsigned indexValue = arg.getArgNumber();
      if (!isa<BaseMemRefType>(arg.getType()) ||
          bundles.declared(fn, indexValue))
        continue;
      if (std::optional<std::string> bundle =
              bundles.throughCalls(fn, indexValue))
        fn.setArgAttr(indexValue, kMaxiBundleAttr,
                      buildPoint.getStringAttr(*bundle));
    }
  });
}

namespace {
/// The globals a function reads and writes, its callees' included.
class GlobalEffects {
public:
  struct Sets {
    llvm::SmallDenseSet<StringRef, 4> reads, writes;
  };

  const Sets &of(func::FuncOp fn) {
    auto [it, inserted] = memo.try_emplace(fn.getOperation());
    if (!inserted)
      return it->second;
    Sets sets;
    fn.walk([&](Operation *op) {
      if (auto callSite = dyn_cast<CallOpInterface>(op)) {
        if (func::FuncOp callee = resolveDefinedCallee(callSite)) {
          const Sets &inner = of(callee);
          sets.reads.insert(inner.reads.begin(), inner.reads.end());
          sets.writes.insert(inner.writes.begin(), inner.writes.end());
        }
        return;
      }
      Value mem;
      bool write = false;
      if (auto lowerIndex = dyn_cast<affine::AffineReadOpInterface>(op))
        mem = lowerIndex.getMemRef();
      else if (auto stringValue = dyn_cast<affine::AffineWriteOpInterface>(op))
        mem = stringValue.getMemRef(), write = true;
      else if (auto lowerIndex = dyn_cast<memref::LoadOp>(op))
        mem = lowerIndex.getMemRef();
      else if (auto stringValue = dyn_cast<memref::StoreOp>(op))
        mem = stringValue.getMemRef(), write = true;
      if (!mem)
        return;
      while (auto view = mem.getDefiningOp<ViewLikeOpInterface>())
        mem = view.getViewSource();
      if (auto get = mem.getDefiningOp<memref::GetGlobalOp>())
        (write ? sets.writes : sets.reads).insert(get.getName());
    });
    Sets &slot = memo[fn.getOperation()];
    slot = std::move(sets);
    return slot;
  }

private:
  DenseMap<Operation *, Sets> memo;
};
} // namespace

void annotateCalleeGlobalRecurrences(ModuleOp module) {
  GlobalEffects effects;
  UnitAttr unit = UnitAttr::get(module.getContext());
  module.walk([&](CallOpInterface callSite) {
    func::FuncOp callee = resolveDefinedCallee(callSite);
    if (!callee || !isKeptCallee(callee))
      return;
    const GlobalEffects::Sets &sets = effects.of(callee);
    if (llvm::any_of(sets.writes, [&](StringRef globalOp) {
          return sets.reads.contains(globalOp);
        }))
      callSite->setAttr(kCalleeGlobalRecurrenceAttr, unit);
  });
}

unsigned callerStoresPerLoop(Value bank) {
  auto arg = dyn_cast<BlockArgument>(bank);
  if (!arg)
    return 0;
  auto fn = dyn_cast<func::FuncOp>(arg.getOwner()->getParentOp());
  if (!fn)
    return 0;
  auto arrayValue = fn.getArgAttrOfType<IntegerAttr>(arg.getArgNumber(),
                                                     kCallerStoresPerLoopAttr);
  return arrayValue ? static_cast<unsigned>(arrayValue.getInt()) : 0u;
}

unsigned calleeStoresPerLoop(Value bank) {
  IntegerAttr arrayValue;
  if (auto arg = dyn_cast<BlockArgument>(bank)) {
    if (auto fn = dyn_cast<func::FuncOp>(arg.getOwner()->getParentOp()))
      arrayValue = fn.getArgAttrOfType<IntegerAttr>(arg.getArgNumber(),
                                                    kCalleeStoresPerLoopAttr);
  } else if (Operation *def = bank.getDefiningOp()) {
    arrayValue = def->getAttrOfType<IntegerAttr>(kCalleeStoresPerLoopAttr);
  }
  return arrayValue ? static_cast<unsigned>(arrayValue.getInt()) : 0u;
}

BRAMClassification::BRAMClassification(Operation *op) {
  enumerateBanks(op);
  profileAccesses(op);
  LLVM_DEBUG(dump(llvm::dbgs()));
}

void BRAMClassification::enumerateBanks(Operation *root) {

  if (auto fn = dyn_cast<func::FuncOp>(root)) {
    bool isCallee = fn.isPrivate() || isKeptCallee(fn);
    SmallVector<int64_t> portBound;
    if (auto bound = fn->getAttrOfType<ArrayAttr>(kPortBoundArgsAttr))
      for (Attribute arrayValue : bound)
        if (auto loopIndex = dyn_cast<IntegerAttr>(arrayValue))
          portBound.push_back(loopIndex.getInt());
    if (isCallee)
      for (BlockArgument arg : fn.getArguments()) {
        auto memTy = dyn_cast<MemRefType>(arg.getType());
        if (!memTy || !memTy.hasStaticShape())
          continue;
        if (llvm::is_contained(portBound,
                               static_cast<int64_t>(arg.getArgNumber())))
          continue;
        Type elt = memTy.getElementType();
        if (!elt.isIntOrFloat() && !isa<IndexType>(elt))
          continue;
        BankProfile prof;
        prof.memref = arg;
        prof.width = elt.isIntOrFloat()
                         ? elt.getIntOrFloatBitWidth()
                         : static_cast<unsigned>(
                               circt::hlsest::Config::get().frontend.indexBits);
        prof.depth = static_cast<unsigned>(memTy.getNumElements());
        banks.try_emplace(arg, prof);
      }
  }
  root->walk([&](memref::AllocaOp localAlloca) {
    Value bank = localAlloca.getResult();
    auto memTy = dyn_cast<MemRefType>(bank.getType());
    if (!memTy || !memTy.hasStaticShape())
      return;

    Type elt = memTy.getElementType();
    if (!elt.isIntOrFloat() && !isa<IndexType>(elt))
      return;

    BankProfile prof;
    prof.memref = bank;
    prof.width = elt.isIntOrFloat()
                     ? elt.getIntOrFloatBitWidth()
                     : static_cast<unsigned>(
                           circt::hlsest::Config::get().frontend.indexBits);
    prof.depth = static_cast<unsigned>(memTy.getNumElements());
    prof.registers = localAlloca->hasAttr(kRegistersAttrName);
    if (prof.registers)
      prof.mode = StorageMode::Registers;
    banks.try_emplace(bank, prof);
  });

  root->walk([&](memref::GetGlobalOp get) {
    auto global = SymbolTable::lookupNearestSymbolFrom<memref::GlobalOp>(
        get, get.getNameAttr());
    if (!global || !global->hasAttr(kRegistersAttrName))
      return;
    MemRefType memTy = get.getType();
    Type elt = memTy.getElementType();
    if (!memTy.hasStaticShape() || !elt.isIntOrFloat())
      return;
    BankProfile prof;
    prof.memref = get.getResult();
    prof.width = elt.getIntOrFloatBitWidth();
    prof.depth = static_cast<unsigned>(memTy.getNumElements());
    prof.registers = true;
    prof.mode = StorageMode::Registers;
    banks.try_emplace(get.getResult(), prof);
  });
}

void BRAMClassification::profileAccesses(Operation *root) {

  using LoopCounts = llvm::DenseMap<Operation *, std::pair<unsigned, unsigned>>;
  llvm::DenseMap<Value, LoopCounts> perLoop;

  llvm::DenseMap<Value, llvm::MapVector<Operation *, SmallVector<Operation *>>>
      storesPerLoop;

  root->walk([&](Operation *op) {
    bool isLoad = false, isStore = false;
    Value bank = getAccessedMemRef(op, isLoad, isStore);
    if (!bank)
      return;
    auto it = banks.find(bank);
    if (it == banks.end())
      return;

    Operation *loop = op->getParentOfType<LoopLikeOpInterface>();
    auto &counts = perLoop[bank][loop];
    if (isLoad)
      ++counts.first;
    if (isStore) {
      ++counts.second;
      storesPerLoop[bank][loop].push_back(op);
    }
  });

  for (auto &[bank, loopCounts] : perLoop) {
    BankProfile &prof = banks[bank];
    unsigned maxStoresPerLoop = 0;
    for (auto &[loop, rw] : loopCounts) {
      unsigned reads = rw.first, writes = rw.second;
      prof.maxReads = std::max(prof.maxReads, reads);
      prof.maxWrites = std::max(prof.maxWrites, writes);
      if (loop && writes)
        maxStoresPerLoop =
            std::max(maxStoresPerLoop, hls_analysis::maxStoresInOneIteration(
                                           storesPerLoop[bank][loop], loop));
    }

    maxStoresPerLoop = std::max(maxStoresPerLoop, calleeStoresPerLoop(bank));

    maxStoresPerLoop = std::max(maxStoresPerLoop, callerStoresPerLoop(bank));
    prof.replicable = maxStoresPerLoop <= 1;
    prof.mode = prof.registers ? StorageMode::Registers
                               : classifyMode(maxStoresPerLoop);
    prof.type = classifyStorageKind(prof.maxReads, prof.maxWrites);
  }
}

StorageMode BRAMClassification::getMode(Value bank) const {
  auto it = banks.find(bank);
  return it == banks.end() ? StorageMode::TDP : it->second.mode;
}

const BankProfile *BRAMClassification::getProfile(Value bank) const {
  auto it = banks.find(bank);
  return it == banks.end() ? nullptr : &it->second;
}

void BRAMClassification::dump(llvm::raw_ostream &os) const {
  os << "=== (BRAMClassification) ===\n";
  for (auto &[bank, prof] : banks) {
    os << "  bank " << bank << ": " << prof.width << "x" << prof.depth
       << " modes=" << stringifyStorageMode(prof.mode)
       << " (R=" << prof.maxReads << " W=" << prof.maxWrites
       << (prof.replicable ? ", replicable" : ", not replicable") << ")"
       << " slots/cycle=" << storageModeSlots(prof.mode)
       << " storage kind= " << stringifyStorageKind(prof.type) << "\n";
  }
}

} // namespace circt::hls_analysis
