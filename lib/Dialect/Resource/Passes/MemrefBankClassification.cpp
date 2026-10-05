//===- BRAMClassification.cpp ---------------------------------------------===//

#include "circt/Dialect/Resource/Config/ConfigUtils.h"
#include "circt/Dialect/Resource/Passes/MemrefBankClassification.h"
#include "circt/Dialect/Resource/HLS/HLSOps.h"
#include "mlir/Dialect/Affine/IR/AffineOps.h"
#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/Dialect/MemRef/IR/MemRef.h"
#include "mlir/Dialect/SCF/IR/SCF.h"
#include "mlir/IR/Builders.h"
#include "mlir/IR/BuiltinOps.h"
#include "mlir/IR/SymbolTable.h"
#include "mlir/Interfaces/CallInterfaces.h"
#include "mlir/Interfaces/ViewLikeInterface.h"
#include "circt/Dialect/Resource/Passes/CallInstances.h"
#include "circt/Dialect/Resource/Passes/LoopPragmas.h"
#include "circt/Dialect/Resource/Passes/MemoryRecurrences.h"
#include "circt/Dialect/Resource/Passes/StoragePragmas.h"
#include "llvm/ADT/MapVector.h"
#include "mlir/IR/BuiltinTypes.h"
#include "mlir/Interfaces/LoopLikeInterface.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/Debug.h"

#include <llvm/ADT/TypeSwitch.h>

#include <limits>
#include <map>

#define DEBUG_TYPE "bram-classification"

using namespace mlir;

namespace circt::hls_analysis {


//===----------------------------------------------------------------------===//
// Small helpers
//===----------------------------------------------------------------------===//
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
  if (const circt::hlsest::DeviceMemory *m =
          cfg.device.memory(cfg.tool.backend.memoryMapper.primitive))
    if (const circt::hlsest::PortConfig *pc = m->portConfig(ma.pricedNarrow))
      return static_cast<unsigned>(pc->ports.size());
  return kDualPortSlots;
}

unsigned storageModeSlots(StorageMode mode) {
  switch (mode) {
  case StorageMode::OnePort:
    return 1;
  case StorageMode::SDP: // one read + one write; callers split the pools
  case StorageMode::TDP:
    return blockRamPorts();
  case StorageMode::OneWriteNRead:
    // max_copies x (ports - 1) + 1 = 17 (tool.hls.memory_architecture.
    // replication).
    return static_cast<unsigned>(circt::hlsest::Config::get()
                                     .tool.hls.memoryArchitecture
                                     .replicatedSlots());
  case StorageMode::Registers:
    return std::numeric_limits<unsigned>::max(); // no memory, no limit
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
  if (reads + writes <= 1) return StorageKind::RAM_1P;
  if (writes > 1) return StorageKind::RAM_2P;
  return StorageKind::RAM_1WNR;
}

// Vitis (VITIS_NOTES.md N4, replication.md R1-R3): a bank some loop body
// stores to more than once stays one true-dual-port RAM (the II is raised to
// ceil((R+W)/2)); otherwise extra reads are served by replicated copies, up to
// 16 copies + the shared write port = 17 accesses per cycle.
StorageMode classifyMode(unsigned maxStoresPerLoop) {
  // tool.hls.memory_architecture.replication.max_stores_per_iteration (1).
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
  // A register-promoted access (VITIS_NOTES N87) uses no port of the bank.
  if (hls_analysis::isPromotedAccess(op))
    return Value{};
  return TypeSwitch<Operation *, Value>(op)
      .Case<affine::AffineLoadOp, memref::LoadOp>(
          [&](auto l) { isLoad = true; return l.getMemRef(); })
      .Case<affine::AffineStoreOp, memref::StoreOp>(
          [&](auto s) { isStore = true; return s.getMemRef(); })
      .Case<AffineStoreEnableOp, StoreEnableOp>(
          [&](auto s) { isStore = true; return s.getMemref(); })  // note: getMemref()
      .Default(Value{});
}


//===----------------------------------------------------------------------===//
// Stores per loop body made by callees
//===----------------------------------------------------------------------===//
// Vitis decides whether an array can be a RAM_1WNR from every loop that
// accesses it, the loops of the functions it is passed to included: a callee
// loop that stores a bank twice per iteration keeps the caller's bank one
// 2-port RAM, and then the caller's own pipelined loops get two ports of it,
// not the replicated read slots (the price model, analyzeReplication in
// BRAMAnalysis, already follows calls; a caller loop scheduled with the
// replicated slots got an II and a copy count for its other arrays that
// Vitis never builds: a softmax callee storing 16 banks of `attention` per
// iteration, the caller reading them at II 1 and replicating `V_local` 15
// times where Vitis builds one copy). The convert-affine-to-loopschedule
// pass runs per function and may not read the callees, so this module-level
// step records the callees' worst loop body on the caller's bank.

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
    // Same memref, indices and (for affine.store) map.
    if (auto a = dyn_cast<affine::AffineStoreOp>(op)) {
      auto b = cast<affine::AffineStoreOp>(store);
      if (a.getAffineMap() != b.getAffineMap())
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
  const void *ifOp = nullptr; // set for an if the store is nested in
  int64_t hoistedId = 0;      // set for an if it was hoisted out of
  int64_t arm = 0;
  bool sameIf(const IfArm &o) const {
    return ifOp == o.ifOp && hoistedId == o.hoistedId;
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
  // hls.if_arms lists [if id, arm, ...] innermost first.
  if (auto arms = op->getAttrOfType<DenseI64ArrayAttr>(kIfArmsAttr)) {
    ArrayRef<int64_t> a = arms.asArrayRef();
    for (size_t i = a.size(); i >= 2; i -= 2)
      path.push_back({nullptr, a[i - 2], a[i - 1]});
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
  // if -> arm -> paths, in first-seen order (the sum and max do not depend
  // on it).
  std::map<std::pair<const void *, int64_t>,
           std::map<int64_t, SmallVector<const ArmPath *>>>
      byIf;
  for (const ArmPath *p : paths) {
    if (p->size() <= depth) {
      ++total;
      continue;
    }
    const IfArm &a = (*p)[depth];
    byIf[{a.ifOp, a.hoistedId}][a.arm].push_back(p);
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
      clExclusiveArmStores, circt::hlsest::Config::get()
                                .tool.hls.memoryArchitecture.replication
                                .exclusiveArmStoresOnce);
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
  for (const ArmPath &p : paths)
    refs.push_back(&p);
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
  unsigned ofParameter(func::FuncOp fn, unsigned idx) {
    auto key = std::make_pair(fn.getOperation(), idx);
    if (auto it = memo.find(key); it != memo.end())
      return it->second;
    memo[key] = 0; // a recursive call contributes nothing
    BlockArgument arg = fn.getArgument(idx);
    unsigned n = std::max(localStoresPerLoop(arg), throughCalls(arg));
    memo[key] = n;
    return n;
  }

  /// Max over the defined callees `mem` is passed to directly.
  unsigned throughCalls(Value mem) {
    unsigned best = 0;
    for (OpOperand &use : mem.getUses()) {
      auto call = dyn_cast<CallOpInterface>(use.getOwner());
      if (!call)
        continue;
      func::FuncOp callee = resolveDefinedCallee(call);
      if (!callee || callee.isExternal())
        continue;
      std::optional<unsigned> idx = callArgIndex(call, use);
      if (!idx || *idx >= callee.getNumArguments())
        continue;
      best = std::max(best, ofParameter(callee, *idx));
    }
    return best;
  }

private:
  DenseMap<std::pair<Operation *, unsigned>, unsigned> memo;
};
} // namespace

void annotateCalleeStoresPerLoop(ModuleOp module) {
  CalleeStores stores;
  OpBuilder b(module.getContext());
  module.walk([&](memref::AllocaOp alloca) {
    unsigned n = stores.throughCalls(alloca.getResult());
    if (n > 1)
      alloca->setAttr(kCalleeStoresPerLoopAttr, b.getI64IntegerAttr(n));
  });
  module.walk([&](func::FuncOp fn) {
    if (fn.isExternal())
      return;
    for (BlockArgument arg : fn.getArguments()) {
      if (!isa<MemRefType>(arg.getType()))
        continue;
      unsigned n = stores.throughCalls(arg);
      if (n > 1)
        fn.setArgAttr(arg.getArgNumber(), kCalleeStoresPerLoopAttr,
                      b.getI64IntegerAttr(n));
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
    module.walk([&](CallOpInterface call) {
      if (func::FuncOp callee = resolveDefinedCallee(call))
        callers[callee.getOperation()].push_back(call);
    });
  }

  unsigned ofParameter(func::FuncOp fn, unsigned idx) {
    auto key = std::make_pair(fn.getOperation(), idx);
    if (auto it = memo.find(key); it != memo.end())
      return it->second;
    memo[key] = 0; // a recursive call contributes nothing
    unsigned best = 0;
    for (CallOpInterface call : callers.lookup(fn.getOperation())) {
      if (idx >= call.getArgOperands().size())
        continue;
      best = std::max(best, ofValue(call.getArgOperands()[idx]));
    }
    memo[key] = best;
    return best;
  }

private:
  unsigned ofValue(Value v) {
    if (!isa<MemRefType>(v.getType()))
      return 0;
    unsigned n = std::max(localStoresPerLoop(v), callees.throughCalls(v));
    if (auto arg = dyn_cast<BlockArgument>(v))
      if (auto fn = dyn_cast<func::FuncOp>(arg.getOwner()->getParentOp()))
        n = std::max(n, ofParameter(fn, arg.getArgNumber()));
    return n;
  }

  CalleeStores callees;
  DenseMap<Operation *, SmallVector<CallOpInterface, 2>> callers;
  DenseMap<std::pair<Operation *, unsigned>, unsigned> memo;
};
} // namespace

void annotateCallerStoresPerLoop(ModuleOp module) {
  CallerStores stores(module);
  OpBuilder b(module.getContext());
  module.walk([&](func::FuncOp fn) {
    if (fn.isExternal())
      return;
    for (BlockArgument arg : fn.getArguments()) {
      if (!isa<MemRefType>(arg.getType()))
        continue;
      unsigned n = stores.ofParameter(fn, arg.getArgNumber());
      if (n > 1)
        fn.setArgAttr(arg.getArgNumber(), kCallerStoresPerLoopAttr,
                      b.getI64IntegerAttr(n));
    }
  });
}

//===----------------------------------------------------------------------===//
// m_axi bundles through calls, global recurrences of callees
//===----------------------------------------------------------------------===//

namespace {
/// The m_axi bundle a memref value is a port of: a parameter with an
/// `hls.interface` of the mode, or one every call site binds to such a port.
class MaxiBundles {
public:
  MaxiBundles(ModuleOp module, StringRef mode, StringRef defaultBundle)
      : mode(mode), defaultBundle(defaultBundle) {
    module.walk([&](CallOpInterface call) {
      if (func::FuncOp callee = resolveDefinedCallee(call))
        callers[callee.getOperation()].push_back(call);
    });
  }

  /// The bundle of parameter `idx` of `fn` from its own interface; nullopt
  /// when it has none of the mode.
  std::optional<std::string> declared(func::FuncOp fn, unsigned idx) const {
    auto ifaces = fn.getArgAttrOfType<ArrayAttr>(idx, "hls.interface");
    if (!ifaces)
      return std::nullopt;
    for (Attribute attr : ifaces) {
      auto d = dyn_cast<DictionaryAttr>(attr);
      auto m = d ? d.getAs<StringAttr>("mode") : StringAttr();
      if (!m || m.getValue() != mode)
        continue;
      if (auto b = d.getAs<StringAttr>("bundle"))
        return b.getValue().str();
      return defaultBundle;
    }
    return std::nullopt;
  }

  /// The bundle every call site of `fn` binds parameter `idx` to; nullopt
  /// when one binds something else, they disagree, or nothing calls it.
  std::optional<std::string> throughCalls(func::FuncOp fn, unsigned idx) {
    auto key = std::make_pair(fn.getOperation(), idx);
    if (auto it = memo.find(key); it != memo.end())
      return it->second;
    memo[key] = std::nullopt; // a recursive call binds nothing
    std::optional<std::string> bundle;
    bool any = false, agree = true;
    for (CallOpInterface call : callers.lookup(fn.getOperation())) {
      if (idx >= call.getArgOperands().size()) {
        agree = false;
        break;
      }
      std::optional<std::string> b = ofValue(call.getArgOperands()[idx]);
      if (!b || (any && *b != *bundle)) {
        agree = false;
        break;
      }
      bundle = b;
      any = true;
    }
    std::optional<std::string> result =
        any && agree ? bundle : std::optional<std::string>();
    memo[key] = result;
    return result;
  }

private:
  std::optional<std::string> ofValue(Value v) {
    while (auto view = v.getDefiningOp<ViewLikeOpInterface>())
      v = view.getViewSource();
    auto arg = dyn_cast<BlockArgument>(v);
    if (!arg)
      return std::nullopt;
    auto fn = dyn_cast<func::FuncOp>(arg.getOwner()->getParentOp());
    if (!fn || !isa<BaseMemRefType>(arg.getType()))
      return std::nullopt;
    if (std::optional<std::string> b = declared(fn, arg.getArgNumber()))
      return b;
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
  OpBuilder b(module.getContext());
  module.walk([&](func::FuncOp fn) {
    if (fn.isExternal())
      return;
    for (BlockArgument arg : fn.getArguments()) {
      unsigned idx = arg.getArgNumber();
      if (!isa<BaseMemRefType>(arg.getType()) || bundles.declared(fn, idx))
        continue;
      if (std::optional<std::string> bundle = bundles.throughCalls(fn, idx))
        fn.setArgAttr(idx, kMaxiBundleAttr, b.getStringAttr(*bundle));
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
      return it->second; // computed, or a recursive call in progress
    Sets sets;
    fn.walk([&](Operation *op) {
      if (auto call = dyn_cast<CallOpInterface>(op)) {
        if (func::FuncOp callee = resolveDefinedCallee(call)) {
          const Sets &inner = of(callee);
          sets.reads.insert(inner.reads.begin(), inner.reads.end());
          sets.writes.insert(inner.writes.begin(), inner.writes.end());
        }
        return;
      }
      Value mem;
      bool write = false;
      if (auto l = dyn_cast<affine::AffineReadOpInterface>(op))
        mem = l.getMemRef();
      else if (auto s = dyn_cast<affine::AffineWriteOpInterface>(op))
        mem = s.getMemRef(), write = true;
      else if (auto l = dyn_cast<memref::LoadOp>(op))
        mem = l.getMemRef();
      else if (auto s = dyn_cast<memref::StoreOp>(op))
        mem = s.getMemRef(), write = true;
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
  module.walk([&](CallOpInterface call) {
    func::FuncOp callee = resolveDefinedCallee(call);
    if (!callee || !isKeptCallee(callee))
      return;
    const GlobalEffects::Sets &sets = effects.of(callee);
    if (llvm::any_of(sets.writes,
                     [&](StringRef g) { return sets.reads.contains(g); }))
      call->setAttr(kCalleeGlobalRecurrenceAttr, unit);
  });
}

unsigned callerStoresPerLoop(Value bank) {
  auto arg = dyn_cast<BlockArgument>(bank);
  if (!arg)
    return 0;
  auto fn = dyn_cast<func::FuncOp>(arg.getOwner()->getParentOp());
  if (!fn)
    return 0;
  auto a = fn.getArgAttrOfType<IntegerAttr>(arg.getArgNumber(),
                                            kCallerStoresPerLoopAttr);
  return a ? static_cast<unsigned>(a.getInt()) : 0u;
}

unsigned calleeStoresPerLoop(Value bank) {
  IntegerAttr a;
  if (auto arg = dyn_cast<BlockArgument>(bank)) {
    if (auto fn = dyn_cast<func::FuncOp>(arg.getOwner()->getParentOp()))
      a = fn.getArgAttrOfType<IntegerAttr>(arg.getArgNumber(),
                                           kCalleeStoresPerLoopAttr);
  } else if (Operation *def = bank.getDefiningOp()) {
    a = def->getAttrOfType<IntegerAttr>(kCalleeStoresPerLoopAttr);
  }
  return a ? static_cast<unsigned>(a.getInt()) : 0u;
}

//===----------------------------------------------------------------------===//
// BRAMClassification
//===----------------------------------------------------------------------===//

BRAMClassification::BRAMClassification(Operation *op) {
  enumerateBanks(op);
  profileAccesses(op);
  LLVM_DEBUG(dump(llvm::dbgs()));
}


/// One bank of a complete partition (a memref.alloca memory banking made,
/// `hls.partition`, holding a single element) is a register: Vitis gives the
/// elements of a completely partitioned array no port limit in a pipelined
/// loop (VITIS_NOTES N111: kernel w9r15p_rg_net, a 19-step compare-and-swap
/// network on `int v[8]` complete runs at II 1; with a 2-port pool per
/// element hls-est had II 32). Key
/// tool.hls.partitioning.complete_partition_registers.
static bool isOneElementPartitionBank(Operation *alloca, MemRefType memTy) {
  return memTy.getNumElements() == 1 && alloca->hasAttr("hls.partition") &&
         circt::hlsest::Config::get()
             .tool.hls.partitioning.completePartitionRegisters;
}

void BRAMClassification::enumerateBanks(Operation *root) {
  // W3 (VITIS_NOTES.md N14 R6): the memref arguments of a non-inlined callee
  // name the caller's arrays, which Vitis replicates for the callee's own
  // pipelined loops like any local array (inl_e1: `buf` read 3x per cycle in
  // the callee, RAM_1WNR, 4 BRAM). The arguments of the top are its ports:
  // not tracked, two slots per cycle. A callee is a private function (the
  // harness prefix --symbol-privatize=exclude=<top> makes every function but
  // the top private; cgeist emits `static` functions private) or one that
  // carries hls.inline_off or hls.inline_auto_off. This analysis runs inside
  // a function pass, which may not look at the other functions of the module
  // (the pass manager runs function passes in parallel), so the call sites
  // are not searched.
  // An argument listed in `hls.port_bound_args` (--auto-pipeline-unroll: its
  // array crosses a module instantiated at more than one place) is not
  // replicated for the callee (N14 R6; w3rev_k3, w3fx_d2_conc: rd3's loop
  // II 2, the caller's array RAM_1R1W): it stays untracked, two ports.
  if (auto fn = dyn_cast<func::FuncOp>(root)) {
    bool isCallee = fn.isPrivate() || isKeptCallee(fn);
    SmallVector<int64_t> portBound;
    if (auto bound = fn->getAttrOfType<ArrayAttr>(kPortBoundArgsAttr))
      for (Attribute a : bound)
        if (auto i = dyn_cast<IntegerAttr>(a))
          portBound.push_back(i.getInt());
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
  root->walk([&](memref::AllocaOp alloca) {
    Value bank = alloca.getResult();
    auto memTy = dyn_cast<MemRefType>(bank.getType());
    if (!memTy || !memTy.hasStaticShape())
      return; // Skip dynamic / non-memref allocas.

    // Only arrays of integers / floats (and index) are storage the scheduler
    // models; a memref of memrefs or of an LLVM struct is a pointer variable
    // or an aggregate (cgeist output for forgebench conv_*), not a bank.
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
    prof.registers = alloca->hasAttr(kRegistersAttrName) ||
                     isOneElementPartitionBank(alloca, memTy);
    if (prof.registers)
      prof.mode = StorageMode::Registers;
    banks.try_emplace(bank, prof);
  });
  // A global (or function static) marked hls.registers has no memory ports
  // either (VITIS_NOTES N7 (a), kernel w9rv_r1_glob4); every other global
  // stays untracked (two ports).
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

/// A bank whose alloca carries a user `bind_storage type=ram_1wnr` and the
/// key tool.hls.memory_architecture.replication.user_ram_1wnr_replicable.
static bool userRam1wnr(Value bank) {
  if (!circt::hlsest::Config::get()
           .tool.hls.memoryArchitecture.replication.userRam1wnrReplicable)
    return false;
  Operation *def = bank.getDefiningOp();
  auto binds = def ? def->getAttrOfType<ArrayAttr>("hls.bind_storage")
                   : ArrayAttr();
  if (!binds)
    return false;
  for (Attribute b : binds)
    if (auto d = dyn_cast<DictionaryAttr>(b))
      if (auto t = d.getAs<StringAttr>("type"))
        if (t.getValue().equals_insensitive("ram_1wnr"))
          return true;
  return false;
}

/// A bank whose alloca carries a user `bind_storage` of a plain RAM type
/// (ram_1p / ram_2p / ram_t2p / ram_s2p) and the key
/// tool.hls.memory_architecture.replication.user_plain_ram_pins_kind: the
/// kind is final, so the bank is never replicated (VITIS_NOTES N173).
static bool userPinnedRam(Value bank) {
  if (!circt::hlsest::Config::get()
           .tool.hls.memoryArchitecture.replication.userPlainRamPinsKind)
    return false;
  std::optional<std::string> type =
      hls_analysis::bindStorageType(bank.getDefiningOp());
  return type && hls_analysis::isPinnedRamType(*type);
}

void BRAMClassification::profileAccesses(Operation *root) {
  // Per bank, per enclosing innermost loop: (reads, writes) within one body.
  // Keyed loop = the innermost enclosing LoopLikeOpInterface op (affine.for,
  // scf.for, ...: the same notion of scope as BRAMAnalysis' sequentialScope),
  // or null for a straight-line access outside every loop. The counts are per loop *body* (after
  // unrolling), which is what Vitis' replication rule looks at: a body with
  // two stores to the bank needs two write ports in one iteration, so the bank
  // cannot be a RAM_1WNR (one shared write port) and stays a 2-port RAM.
  using LoopCounts = llvm::DenseMap<Operation *, std::pair<unsigned, unsigned>>;
  llvm::DenseMap<Value, LoopCounts> perLoop;
  // The stores themselves, per bank and loop: two in the arms of one if
  // count once for replicability (maxStoresInOneIteration).
  llvm::DenseMap<Value, llvm::MapVector<Operation *, SmallVector<Operation *>>>
      storesPerLoop;

  root->walk([&](Operation *op) {
    bool isLoad = false, isStore = false;
    Value bank = getAccessedMemRef(op, isLoad, isStore);
    if (!bank)
      return;
    auto it = banks.find(bank);
    if (it == banks.end())
      return; // Access to an argument/off-chip memref, not a tracked bank.

    Operation *loop = op->getParentOfType<LoopLikeOpInterface>();
    auto &counts = perLoop[bank][loop];
    if (isLoad)
      ++counts.first;
    if (isStore) {
      ++counts.second;
      storesPerLoop[bank][loop].push_back(op);
    }
  });

  // Fold to the worst-case profile across loops. Straight-line accesses
  // (null loop) run once and have no II, so they do not decide replicability
  // (Vitis' rule was only observed on loop bodies; replication.md "R3").
  for (auto &[bank, loopCounts] : perLoop) {
    BankProfile &prof = banks[bank];
    unsigned maxStoresPerLoop = 0;
    for (auto &[loop, rw] : loopCounts) {
      unsigned reads = rw.first, writes = rw.second;
      prof.maxReads = std::max(prof.maxReads, reads);
      prof.maxWrites = std::max(prof.maxWrites, writes);
      if (loop && writes)
        maxStoresPerLoop = std::max(
            maxStoresPerLoop,
            hls_analysis::maxStoresInOneIteration(storesPerLoop[bank][loop],
                                                  loop));
    }
    // The loops of the callees this bank is passed to (annotated by
    // annotateCalleeStoresPerLoop, which can see the other functions).
    maxStoresPerLoop = std::max(maxStoresPerLoop, calleeStoresPerLoop(bank));
    // A parameter: the arrays its call sites pass, stored by the callers
    // (annotateCallerStoresPerLoop, VITIS_NOTES N99).
    maxStoresPerLoop = std::max(maxStoresPerLoop, callerStoresPerLoop(bank));
    prof.replicable = maxStoresPerLoop <= 1;
    // A user `bind_storage type=ram_1wnr` (N113): replicated anyway; the
    // loops storing it twice keep the shared write port and a higher II.
    if (!prof.replicable && userRam1wnr(bank)) {
      prof.replicable = true;
      maxStoresPerLoop = 1;
    }
    // A user binding of a plain RAM type (N173): never replicated; the
    // loops that read it more often than its ports allow raise their II.
    if (userPinnedRam(bank)) {
      prof.replicable = false;
      maxStoresPerLoop = std::numeric_limits<unsigned>::max();
    }
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
       << " modes=" << stringifyStorageMode(prof.mode) << " (R=" << prof.maxReads
       << " W=" << prof.maxWrites
       << (prof.replicable ? ", replicable" : ", not replicable") << ")"
       << " slots/cycle=" << storageModeSlots(prof.mode)
       << " storage kind= " << stringifyStorageKind(prof.type) << "\n";
  }
}

} // namespace bramopt
