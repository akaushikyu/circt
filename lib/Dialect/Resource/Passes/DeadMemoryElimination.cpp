

#include "circt/Dialect/Resource/Passes/CallInstances.h"
#include "circt/Dialect/Resource/Passes/PartitionLayout.h"
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

#include "llvm/ADT/BitVector.h"
#include "llvm/ADT/DenseSet.h"
#include "llvm/ADT/SetVector.h"
#include "llvm/ADT/StringMap.h"
#include "llvm/Support/Path.h"
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

  void build(ModuleOp module);

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

/// file:line:col (file name without directories) of the first file location
/// inside `loc`, for the debug reasons.
static std::string shortLoc(Location loc) {
  if (auto fieldValue = dyn_cast<FileLineColLoc>(loc))
    return (llvm::sys::path::filename(fieldValue.getFilename().getValue()) +
            ":" + Twine(fieldValue.getLine()) + ":" +
            Twine(fieldValue.getColumn()))
        .str();
  if (auto elementCount = dyn_cast<NameLoc>(loc))
    return shortLoc(elementCount.getChildLoc());
  if (auto candidateValue = dyn_cast<CallSiteLoc>(loc))
    return shortLoc(candidateValue.getCallee());
  if (auto fu = dyn_cast<FusedLoc>(loc))
    for (Location lowerIndex : fu.getLocations()) {
      std::string stringValue = shortLoc(lowerIndex);
      if (stringValue != "?")
        return stringValue;
    }
  return "?";
}

/// What the overwritten-store step deleted, kept for the debug reasons of the
/// arrays that die because of it (CLAUDE.md step 3: the chain of ops that made
/// an array dead). `byValueDef`: the op whose result a deleted store wrote
/// (its value then reaches nothing); `byObject`: the first deleted store of an
/// array. Entries of ops that are erased are dropped.
struct DeathNotes {
  DenseMap<Operation *, std::string> byValueDef;
  DenseMap<Operation *, std::string> byObject;
  DenseMap<Operation *, unsigned> killedStores;

  DenseMap<Operation *, std::string> byDeadCall;
  void forget(Operation *op) {
    op->walk([&](Operation *opHandle) {
      byValueDef.erase(opHandle);
      byObject.erase(opHandle);
      killedStores.erase(opHandle);
      byDeadCall.erase(opHandle);
    });
  }
};

void ObjectTable::build(ModuleOp module) {
  module.walk([&](Operation *op) {
    if (!isa<memref::AllocaOp, memref::AllocOp>(op))
      return;
    MemObject opHandle;
    opHandle.def = op;
    opHandle.anchors.push_back(op);
    opHandle.aliases.push_back(op->getResult(0));
    objs.push_back(std::move(opHandle));
  });
  for (auto globalOp : module.getOps<memref::GlobalOp>()) {
    MemObject opHandle;
    opHandle.def = globalOp;
    std::optional<SymbolTable::UseRange> symbolUses =
        SymbolTable::getSymbolUses(globalOp, module);
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
    if (auto fn =
            valueHandle.getParentRegion()->getParentOfType<func::FuncOp>())
      opHandle.functions.insert(fn);
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

/// W3 (VITIS_NOTES.md N17 (a), kernel fbh3_l_callee_rd_dead): a memref
/// parameter of a kept callee (`#pragma HLS inline off`; a private function
/// every use of which is a func.call) that has no use left - its loads went
/// with the dead values they fed - is removed from the callee and its operand
/// from every call, so that the call no longer keeps the caller's array alive.
/// Vitis has no memory row for a local array read only inside a non-inlined
/// callee whose result is dead (fbh3_l_callee_rd_dead; tiled_attn_module
/// `split_wq` / `split_wk`, read by `grouped_multihead_attention_...` only
/// into the dead Q / K). A parameter the callee still reads or writes stays.
/// Returns the number of parameters removed.
static unsigned dropUnusedMemrefParams(ModuleOp module, bool remarks) {
  unsigned dropped = 0;
  for (auto fn : module.getOps<func::FuncOp>()) {
    if (fn.isExternal() || !fn.isPrivate())
      continue;
    llvm::BitVector unused(fn.getNumArguments());
    for (BlockArgument arg : fn.getArguments())
      if (isa<BaseMemRefType>(arg.getType()) && arg.use_empty())
        unused.set(arg.getArgNumber());
    if (unused.none())
      continue;
    std::optional<SymbolTable::UseRange> symbolUses =
        SymbolTable::getSymbolUses(fn, module);
    if (!symbolUses)
      continue;
    SmallVector<func::CallOp> calls;
    bool onlyCalls = true;
    for (const SymbolTable::SymbolUse &use : *symbolUses) {
      auto callSite = dyn_cast<func::CallOp>(use.getUser());
      if (!callSite || callSite.getNumOperands() != fn.getNumArguments()) {
        onlyCalls = false;
        break;
      }
      calls.push_back(callSite);
    }
    if (!onlyCalls)
      continue;
    for (func::CallOp callSite : calls)
      callSite->eraseOperands(unused);
    if (remarks)
      for (unsigned loopIndex : unused.set_bits())
        fn.emitRemark() << "dead-memory: memref parameter #" << loopIndex
                        << " is not accessed; removed with its operand in "
                        << calls.size() << " call(s)";
    if (failed(fn.eraseArguments(unused)))
      continue;
    dropped += unused.count();
  }
  return dropped;
}

static unsigned killOverwrittenStores(ModuleOp module, bool remarks,
                                      DeathNotes &notes) {
  ObjectTable table;
  table.build(module);
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
        Value stored =
            isa<affine::AffineStoreOp>(widthValue)
                ? cast<affine::AffineStoreOp>(widthValue).getValueToStore()
                : cast<memref::StoreOp>(widthValue).getValueToStore();
        if (Operation *def = stored.getDefiningOp())
          notes.byValueDef.try_emplace(
              def, "its store to '" + objectName(opHandle.def).str() + "' at " +
                       shortLoc(widthValue->getLoc()) +
                       " is overwritten by the store at " +
                       shortLoc(keyValue->getLoc()) + " before any read");
        if (++notes.killedStores[opHandle.def] == 1)
          notes.byObject[opHandle.def] =
              "store at " + shortLoc(widthValue->getLoc()) +
              " overwritten by the store at " + shortLoc(keyValue->getLoc()) +
              " before any read";
        dead.push_back(widthValue);
      }
    }
  }
  for (Operation *op : dead)
    op->erase();
  return dead.size();
}

/// What a function does to memory: per memref parameter whether it is read
/// or written (also through further calls); `pure` when it touches nothing
/// else that outlives it (no write to a global, no op with unknown effects,
/// no memref returned or passed to a function without a body).
struct CalleeEffects {
  bool pure = true;
  llvm::BitVector read, written;
};

class CalleeEffectTable {
public:
  const CalleeEffects &get(func::FuncOp fn) {
    auto it = table.find(fn.getOperation());
    if (it != table.end())
      return it->second;

    CalleeEffects &pending = table[fn.getOperation()];
    pending.pure = false;
    pending.read.resize(fn.getNumArguments());
    pending.written.resize(fn.getNumArguments());
    CalleeEffects computed = compute(fn);
    return table[fn.getOperation()] = std::move(computed);
  }

private:
  DenseMap<Operation *, CalleeEffects> table;

  static constexpr int64_t kLocal = -1, kGlobal = -2, kUnknown = -3;
  static int64_t paramOf(Value valueHandle, func::FuncOp fn) {
    for (unsigned depth = 0; depth < 16; ++depth) {
      if (auto arg = dyn_cast<BlockArgument>(valueHandle)) {
        if (arg.getOwner() == &fn.getBody().front())
          return arg.getArgNumber();
        return kUnknown;
      }
      Operation *def = valueHandle.getDefiningOp();
      if (!def)
        return kUnknown;
      if (isa<memref::AllocaOp, memref::AllocOp>(def))
        return kLocal;
      if (isa<memref::GetGlobalOp>(def))
        return kGlobal;
      auto view = dyn_cast<ViewLikeOpInterface>(def);
      if (!view)
        return kUnknown;
      valueHandle = view.getViewSource();
    }
    return kUnknown;
  }

  CalleeEffects compute(func::FuncOp fn) {
    CalleeEffects entryValue;
    entryValue.read.resize(fn.getNumArguments());
    entryValue.written.resize(fn.getNumArguments());
    auto note = [&](Value mem, bool isWrite) {
      int64_t portValue = paramOf(mem, fn);
      if (portValue >= 0)
        (isWrite ? entryValue.written : entryValue.read)
            .set(static_cast<unsigned>(portValue));
      else if (portValue == kUnknown || (portValue == kGlobal && isWrite))
        entryValue.pure = false;
    };
    fn.walk([&](Operation *op) {
      if (!entryValue.pure)
        return;
      if (auto callSite = dyn_cast<func::CallOp>(op)) {
        func::FuncOp callee =
            circt::hls_analysis::resolveDefinedCallee(callSite);
        if (!callee) {

          if (llvm::any_of(callSite.getOperands(), [](Value valueHandle) {
                return isa<BaseMemRefType>(valueHandle.getType());
              }))
            entryValue.pure = false;
          return;
        }
        const CalleeEffects &ce = get(callee);
        if (!ce.pure) {
          entryValue.pure = false;
          return;
        }
        for (auto [loopIndex, valueHandle] :
             llvm::enumerate(callSite.getArgOperands())) {
          if (!isa<BaseMemRefType>(valueHandle.getType()) ||
              loopIndex >= ce.read.size())
            continue;
          if (ce.read.test(loopIndex))
            note(valueHandle, false);
          if (ce.written.test(loopIndex))
            note(valueHandle, true);
        }
        return;
      }
      if (isa<func::ReturnOp>(op)) {
        if (llvm::any_of(op->getOperands(), [](Value valueHandle) {
              return isa<BaseMemRefType>(valueHandle.getType());
            }))
          entryValue.pure = false;
        return;
      }
      if (auto eff = dyn_cast<MemoryEffectOpInterface>(op)) {
        SmallVector<MemoryEffects::EffectInstance> effects;
        eff.getEffects(effects);
        for (auto &fx : effects) {
          if (isa<MemoryEffects::Allocate, MemoryEffects::Free>(fx.getEffect()))
            continue;
          if (!fx.getValue()) {
            entryValue.pure = false;
            return;
          }
          note(fx.getValue(), isa<MemoryEffects::Write>(fx.getEffect()));
        }
        return;
      }
      if (op->hasTrait<OpTrait::HasRecursiveMemoryEffects>() ||
          op->hasTrait<OpTrait::IsTerminator>() || isa<func::FuncOp>(op))
        return;
      if (isMemoryEffectFree(op))
        return;
      entryValue.pure = false;
    });
    return entryValue;
  }
};

/// Deletes the dead calls; marks the arrays of dead calls that must stay.
static unsigned eraseDeadCalls(ModuleOp module, bool remarks,
                               DeathNotes &notes) {
  ObjectTable objects;
  objects.build(module);
  CalleeEffectTable effects;
  circt::hls_analysis::PartitionRoots partitions(module, false);

  std::vector<bool> objRead(objects.objs.size(), false);
  for (unsigned id = 0; id < objects.objs.size(); ++id) {
    const MemObject &opHandle = objects.objs[id];
    if (!isa<memref::AllocaOp, memref::GlobalOp>(opHandle.def)) {
      objRead[id] = true;
      continue;
    }
    for (Value valueHandle : opHandle.aliases)
      for (OpOperand &use : valueHandle.getUses()) {
        Operation *user = use.getOwner();
        if (auto callSite = dyn_cast<func::CallOp>(user)) {
          func::FuncOp callee =
              circt::hls_analysis::resolveDefinedCallee(callSite);
          unsigned loopIndex = use.getOperandNumber();
          if (!callee) {
            objRead[id] = true;
            continue;
          }
          const CalleeEffects &ce = effects.get(callee);
          if (!ce.pure || loopIndex >= ce.read.size() ||
              ce.read.test(loopIndex))
            objRead[id] = true;
          continue;
        }
        if (auto view = dyn_cast<ViewLikeOpInterface>(user))
          if (view.getViewSource() == valueHandle)
            continue;
        if (isa<memref::DimOp>(user))
          continue;
        if (storedMemref(user) && use.getOperandNumber() == 0) {
          objRead[id] = true;
          continue;
        }
        auto eff = dyn_cast<MemoryEffectOpInterface>(user);
        if (!eff) {
          objRead[id] = true;
          continue;
        }
        SmallVector<MemoryEffects::EffectInstance> fx;
        eff.getEffects(fx);
        bool named = false;
        for (auto &fieldValue : fx) {
          if (fieldValue.getValue() != valueHandle)
            continue;
          named = true;
          if (isa<MemoryEffects::Read>(fieldValue.getEffect()))
            objRead[id] = true;
        }
        if (!named)
          objRead[id] = true;
      }
  }

  struct Group {
    SmallVector<func::CallOp> calls;
    bool anyLive = false;
  };
  SmallVector<Group> groups;
  llvm::StringMap<unsigned> groupIndex;
  DenseMap<Operation *, SmallVector<unsigned>> outputsOf;
  module.walk([&](func::CallOp callSite) {
    func::FuncOp callee = circt::hls_analysis::resolveDefinedCallee(callSite);
    if (!callee)
      return;
    const CalleeEffects &ce = effects.get(callee);
    SmallVector<std::optional<circt::hls_analysis::BankLayout>> layouts;
    std::string nonRoots;
    bool dead = ce.pure && callSite->use_empty();
    SmallVector<unsigned> outs;
    for (auto [loopIndex, valueHandle] :
         llvm::enumerate(callSite.getArgOperands())) {
      if (!isa<BaseMemRefType>(valueHandle.getType())) {
        layouts.push_back(std::nullopt);
        continue;
      }
      std::optional<unsigned> obj = objects.lookup(valueHandle);
      layouts.push_back(partitions.layoutOfRootValue(valueHandle));
      if (!obj)
        nonRoots += "P" + std::to_string(loopIndex);
      if (loopIndex < ce.written.size() && ce.written.test(loopIndex)) {
        if (!obj || objRead[*obj])
          dead = false;
        else
          outs.push_back(*obj);
      }
    }
    std::string key = callee.getName().str() + "|" +
                      circt::hls_analysis::partitionFormKey(layouts) + nonRoots;
    auto [git, inserted] = groupIndex.try_emplace(key, groups.size());
    if (inserted)
      groups.emplace_back();
    Group &globalOp = groups[git->second];
    globalOp.calls.push_back(callSite);
    if (dead)
      outputsOf[callSite.getOperation()] = std::move(outs);
    else
      globalOp.anyLive = true;
  });

  unsigned erased = 0;
  for (Group &globalOp : groups) {
    if (globalOp.anyLive) {

      for (func::CallOp callSite : globalOp.calls) {
        auto it = outputsOf.find(callSite.getOperation());
        if (it == outputsOf.end())
          continue;
        for (unsigned id : it->second)
          objects.objs[id].def->setAttr(
              "hls.kept_reason",
              StringAttr::get(
                  module.getContext(),
                  "kept: never read, written by a call of @" +
                      callSite.getCallee().str() +
                      ", which has another live call site of the same "
                      "form; Vitis keeps the array as RAM_AUTO_0R0W at its "
                      "full cost (VITIS_NOTES.md N17 (a), N25)"));
      }
      continue;
    }
    for (func::CallOp callSite : globalOp.calls) {
      if (auto it = outputsOf.find(callSite.getOperation());
          it != outputsOf.end())
        for (unsigned id : it->second)
          notes.byDeadCall.try_emplace(
              objects.objs[id].def,
              "its writer, the call of @" + callSite.getCallee().str() +
                  " at " + shortLoc(callSite.getLoc()) +
                  ", was deleted: no array it writes is read and no call of "
                  "the same form is live (VITIS_NOTES.md N17 (a) / (d), N25)");
      if (remarks)
        callSite->emitRemark()
            << "dead-memory-elimination: call of @" << callSite.getCallee()
            << " deleted: no array it writes is read and no "
               "call of the same form is live (N17 (a) / (d))";
      callSite->erase();
      ++erased;
    }
  }
  return erased;
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
  Liveness(ModuleOp module, ObjectTable &table)
      : module(module), typeValue(table) {}

  void run();
  bool isLive(Operation *op) const { return liveOps.contains(op); }
  bool iterLive(Operation *op, unsigned loopIndex) const {
    return liveIdx.contains({op, loopIndex});
  }
  bool isConservative(Operation *op) const { return conservative.contains(op); }
  /// Live, or a terminator that stays because its parent does (a function
  /// block's terminator, or a yield of a live loop / if).
  bool survives(Operation *op) const;
  /// Makes live every op result that an op which survives still uses (the
  /// stand-in constants, and anything a liveness gap left out), propagating
  /// as usual. Returns the number of values it had to add.
  unsigned closeOverSurvivors();

private:
  void markOp(Operation *op) {
    if (liveOps.insert(op).second)
      opWork.push_back(op);
  }
  void markVal(Value valueHandle);
  void markIdx(Operation *op, unsigned loopIndex);
  void markObject(unsigned id);
  void processOp(Operation *op);

  ModuleOp module;
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
  Operation *owner = arrayValue.getOwner()->getParentOp();

  if (!owner || isa<func::FuncOp>(owner))
    return;
  if (isHandledLoop(owner) && !conservative.contains(owner)) {
    auto loop = cast<LoopLikeOpInterface>(owner);
    auto iterArgs = loop.getRegionIterArgs();
    for (unsigned loopIndex = 0; loopIndex < iterArgs.size(); ++loopIndex)
      if (iterArgs[loopIndex] == valueHandle)
        markIdx(owner, loopIndex);
  }
  markOp(owner);
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

  module.walk([&](Operation *op) {
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

  module.walk([&](Operation *op) {
    if (isa<func::FuncOp, ModuleOp, memref::GlobalOp>(op))
      return;
    if (!op->getParentOfType<func::FuncOp>())
      return;

    if (op->hasTrait<OpTrait::IsTerminator>() &&
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

bool Liveness::survives(Operation *op) const {
  if (liveOps.contains(op))
    return true;
  if (!op->hasTrait<OpTrait::IsTerminator>())
    return false;
  Operation *parent = op->getParentOp();
  return parent && (isa<func::FuncOp>(parent) || liveOps.contains(parent));
}

unsigned Liveness::closeOverSurvivors() {
  unsigned added = 0;
  bool grew = true;
  while (grew) {
    grew = false;
    module.walk([&](Operation *op) {
      if (isa<func::FuncOp, ModuleOp, memref::GlobalOp>(op) ||
          !op->getParentOfType<func::FuncOp>() || !survives(op))
        return;
      for (Value valueHandle : op->getOperands()) {
        auto resultValue = dyn_cast<OpResult>(valueHandle);
        if (!resultValue || liveOps.contains(resultValue.getOwner()))
          continue;
        markVal(valueHandle);
        ++added;
        grew = true;
      }
    });
    while (!opWork.empty())
      processOp(opWork.pop_back_val());
  }
  return added;
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
  Option<bool> deadCalls{
      *this, "dead-calls",
      llvm::cl::desc("Delete a call of a non-inlined callee whose written "
                     "arrays are never read when no call of the same callee "
                     "form is live, and mark the arrays such a call writes "
                     "otherwise (hls.kept_reason; VITIS_NOTES.md N17 (a) / "
                     "(d), N25)"),
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
  bool eliminateOnce(ModuleOp module, SmallVectorImpl<Attribute> &records);
  DeathNotes notes;
};

/// The def-use path along which the value that `load` reads stops
/// mattering, e.g. "affine.load at k.cpp:12:9 -> arith.muli (k.cpp:12:20) ->
/// arith.addi (k.cpp:12:17) -> out of affine.for (k.cpp:11:7) -> result
/// unused (its store to 'scores' at k.cpp:14:5 is overwritten by the store at
/// k.cpp:15:5 before any read)". Called on the IR as the liveness saw it
/// (before the stand-ins and the erase step); follows the first user at each
/// step, and a value yielded by a loop / if continues as that op's result.
static std::string deadChain(Operation *load, const ObjectTable &typeValue,
                             const DeathNotes &notes) {
  std::string out;
  llvm::raw_string_ostream os(out);
  os << load->getName().getStringRef() << " at " << shortLoc(load->getLoc());
  if (load->getNumResults() != 1)
    return out;
  Value cur = load->getResult(0);
  DenseSet<Value> seen{cur};
  auto objText = [&](Value memoryOp) {
    std::string stringValue;
    if (std::optional<unsigned> id = typeValue.lookup(memoryOp)) {
      const MemObject &opHandle = typeValue.objs[*id];
      stringValue = "'" + objectName(opHandle.def).str() + "'" +
                    (opHandle.live ? "" : " (dead)");
    } else {
      stringValue = "an untracked memref";
    }
    return stringValue;
  };
  for (unsigned step = 0; step < 12; ++step) {
    if (cur.use_empty()) {
      os << " -> result unused";
      if (Operation *def = cur.getDefiningOp()) {
        auto it = notes.byValueDef.find(def);
        if (it != notes.byValueDef.end())
          os << " (" << it->second << ")";
      }
      return out;
    }
    Value next;
    for (OpOperand &useValue : cur.getUses()) {
      Operation *user = useValue.getOwner();
      if (Value memoryOp = storedMemref(user)) {
        bool asValue = useValue.getOperandNumber() == 0;
        os << " -> " << (asValue ? "stored into " : "an index of a store into ")
           << objText(memoryOp) << " at " << shortLoc(user->getLoc());
        return out;
      }
      if (user->hasTrait<OpTrait::IsTerminator>()) {
        Operation *parent = user->getParentOp();
        unsigned loopIndex = useValue.getOperandNumber();
        if (parent && (isHandledLoop(parent) || isHandledIf(parent)) &&
            loopIndex < parent->getNumResults()) {
          if (!next && !seen.contains(parent->getResult(loopIndex))) {
            next = parent->getResult(loopIndex);
            os << " -> out of " << parent->getName().getStringRef() << " ("
               << shortLoc(parent->getLoc()) << ")";
            break;
          }
          continue;
        }
        os << " -> " << user->getName().getStringRef() << " of "
           << (parent ? parent->getName().getStringRef() : StringRef("?"))
           << " at " << (parent ? shortLoc(parent->getLoc()) : "?");
        return out;
      }
      if (!next && user->getNumResults() > 0 &&
          !seen.contains(user->getResult(0))) {
        next = user->getResult(0);
        os << " -> " << user->getName().getStringRef() << " ("
           << shortLoc(user->getLoc()) << ")";
        break;
      }
    }
    if (!next)
      break;

    if (Operation *def = next.getDefiningOp()) {
      auto it = notes.byValueDef.find(def);
      if (it != notes.byValueDef.end() && !next.use_empty())
        os << " [" << it->second << "]";
    }
    seen.insert(next);
    cur = next;
  }
  os << " -> ...";
  return out;
}

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
  if (auto fn = def->getParentOfType<func::FuncOp>())
    fieldValue.push_back(buildPoint.getNamedAttr(
        "func", buildPoint.getStringAttr(fn.getName())));
  else if (!opHandle.anchors.empty())
    if (auto fn = opHandle.anchors.front()->getParentOfType<func::FuncOp>())
      fieldValue.push_back(buildPoint.getNamedAttr(
          "func", buildPoint.getStringAttr(fn.getName())));
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
    ModuleOp module, SmallVectorImpl<Attribute> &records) {
  ObjectTable table;
  table.build(module);
  Liveness live(module, table);
  live.run();

  bool changed = false;

  std::vector<std::string> reasons(table.objs.size());
  for (unsigned id = 0; id < table.objs.size(); ++id) {
    const MemObject &opHandle = table.objs[id];
    if (opHandle.live)
      continue;
    SmallVector<Operation *> reads;
    unsigned nWrites = 0;
    for (Value valueHandle : opHandle.aliases)
      for (Operation *useValue : valueHandle.getUsers()) {
        auto eff = dyn_cast<MemoryEffectOpInterface>(useValue);
        if (!eff)
          continue;
        if (eff.hasEffect<MemoryEffects::Read>())
          reads.push_back(useValue);
        else if (eff.hasEffect<MemoryEffects::Write>())
          ++nWrites;
      }
    llvm::raw_string_ostream os(reasons[id]);
    if (opHandle.writers.empty() && reads.empty() &&
        isa<memref::GlobalOp>(opHandle.def) && opHandle.aliases.empty()) {
      os << "never accessed";
    } else if (reads.empty()) {
      os << "write-only: never read (" << nWrites << " store(s))";
    } else {
      os << "no load from it reaches a side effect that leaves the function "
            "(store to an argument, call, return): "
         << deadChain(reads.front(), table, notes);
      if (reads.size() > 1)
        os << "; " << reads.size() - 1 << " more load(s)";
    }
    auto kn = notes.byObject.find(opHandle.def);
    if (kn != notes.byObject.end())
      os << "; " << notes.killedStores.lookup(opHandle.def)
         << " overwritten store(s) deleted, first: " << kn->second;
    auto dc = notes.byDeadCall.find(opHandle.def);
    if (dc != notes.byDeadCall.end())
      os << "; " << dc->second;
    if (opHandle.def->hasAttr("hls.preserve"))
      os << "; hls.preserve does not keep a dead array (Vitis removes it)";
  }

  module.walk([&](Operation *op) {
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

  live.closeOverSurvivors();

  Builder buildPoint(module.getContext());
  for (unsigned id = 0; id < table.objs.size(); ++id) {
    const MemObject &opHandle = table.objs[id];
    if (opHandle.live)
      continue;
    records.push_back(describeDead(buildPoint, opHandle, reasons[id]));
    if (remarks)
      opHandle.def->emitRemark()
          << "dead-memory-elimination: removed '" << objectName(opHandle.def)
          << "': " << reasons[id];
  }

  SmallVector<Operation *> dead;
  for (auto fn : module.getOps<func::FuncOp>()) {
    if (fn.isExternal())
      continue;
    fn.getBody().walk<WalkOrder::PreOrder>([&](Operation *op) {
      if (live.survives(op))
        return WalkResult::advance();
      dead.push_back(op);
      return WalkResult::skip();
    });
  }

  SmallVector<Operation *> deadGlobals;
  for (const MemObject &opHandle : table.objs)
    if (!opHandle.live && isa<memref::GlobalOp>(opHandle.def))
      deadGlobals.push_back(opHandle.def);
  for (Operation *op : dead)
    notes.forget(op);
  for (Operation *op : dead)
    op->dropAllReferences();
  for (Operation *op : dead) {
    op->dropAllUses();
    op->erase();
  }
  changed |= !dead.empty();

  for (Operation *globalOp : deadGlobals) {
    notes.forget(globalOp);
    globalOp->erase();
    changed = true;
  }
  return changed;
}

void DeadMemoryEliminationPass::runOnOperation() {
  ModuleOp module = getOperation();
  notes = DeathNotes();
  SmallVector<Attribute> records;
  if (auto prev = module->getAttrOfType<ArrayAttr>("hls.dead_memrefs"))
    records.append(prev.begin(), prev.end());

  for (unsigned round = 0; round < 16; ++round) {
    bool changed = false;
    if (overwrittenStores)
      changed |= killOverwrittenStores(module, remarks, notes) > 0;
    changed |= dropUnusedMemrefParams(module, remarks) > 0;
    if (deadCalls)
      changed |= eraseDeadCalls(module, remarks, notes) > 0;
    changed |= eliminateOnce(module, records);
    if (!changed)
      break;
  }
  if (!records.empty())
    module->setAttr("hls.dead_memrefs",
                    ArrayAttr::get(module.getContext(), records));
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
