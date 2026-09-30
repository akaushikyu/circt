

#include "circt/Dialect/Resource/Config/ConfigUtils.h"
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
  SmallVector<Operation *> readers;
  DenseSet<Operation *> functions;
  bool escaping = false;
  std::string escapeReason;
  bool live = false;
  bool scalarised = false;
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
  if (auto g = dyn_cast<memref::GlobalOp>(def))
    return g.getSymName();
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
    op->walk([&](Operation *o) {
      byValueDef.erase(o);
      byObject.erase(o);
      killedStores.erase(o);
      byDeadCall.erase(o);
    });
  }
};

void ObjectTable::build(ModuleOp module) {
  module.walk([&](Operation *op) {
    if (!isa<memref::AllocaOp, memref::AllocOp>(op))
      return;
    MemObject o;
    o.def = op;
    o.anchors.push_back(op);
    o.aliases.push_back(op->getResult(0));
    objs.push_back(std::move(o));
  });
  for (auto g : module.getOps<memref::GlobalOp>()) {
    MemObject o;
    o.def = g;
    std::optional<SymbolTable::UseRange> symbolUses =
        SymbolTable::getSymbolUses(g, module);
    if (!symbolUses) {
      o.escaping = true;
      o.escapeReason = "symbol uses unknown";
    } else {
      for (const SymbolTable::SymbolUse &use : *symbolUses) {
        auto globalUse = dyn_cast<memref::GetGlobalOp>(use.getUser());
        if (!globalUse) {
          o.escaping = true;
          o.escapeReason =
              ("symbol used by " + use.getUser()->getName().getStringRef())
                  .str();
          continue;
        }
        o.anchors.push_back(globalUse);
        o.aliases.push_back(globalUse.getResult());
      }
    }
    objs.push_back(std::move(o));
  }
  for (unsigned id = 0; id < objs.size(); ++id)
    close(id);
}

void ObjectTable::close(unsigned id) {
  MemObject &o = objs[id];
  SmallVector<Value> work(o.aliases.begin(), o.aliases.end());
  for (Value valueHandle : work)
    objOf[valueHandle] = id;
  llvm::SetVector<Operation *> writers, readers;
  while (!work.empty()) {
    Value valueHandle = work.pop_back_val();
    if (auto fn =
            valueHandle.getParentRegion()->getParentOfType<func::FuncOp>())
      o.functions.insert(fn);
    for (OpOperand &use : valueHandle.getUses()) {
      Operation *user = use.getOwner();

      if (auto view = dyn_cast<ViewLikeOpInterface>(user)) {
        if (view.getViewSource() == valueHandle) {
          for (Value resultValue : user->getResults())
            if (isa<BaseMemRefType>(resultValue.getType()) &&
                !objOf.count(resultValue)) {
              objOf[resultValue] = id;
              o.aliases.push_back(resultValue);
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
        else
          readers.insert(user);
        continue;
      }

      if (!o.escaping) {
        o.escaping = true;
        o.escapeReason = ("passed to " + user->getName().getStringRef()).str();
      }
    }
  }
  o.writers.assign(writers.begin(), writers.end());
  o.readers.assign(readers.begin(), readers.end());
  const circt::hlsest::DeadMemoryConfig &dm =
      circt::hlsest::Config::get().tool.hls.middleEnd.deadMemory;
  if (dm.globalSharedByFunctionsEscapes && isa<memref::GlobalOp>(o.def) &&
      o.functions.size() > 1 && !o.escaping) {
    o.escaping = true;
    o.escapeReason =
        "global used by " + std::to_string(o.functions.size()) + " functions";
  }

  if (dm.honourPreserve && o.def->hasAttr("hls.preserve") && !o.escaping) {
    o.escaping = true;
    o.escapeReason = "hls.preserve (honour_preserve)";
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
      std::optional<unsigned> o = table.lookup(entryValue.getValue());
      if (!o || *o == id)
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
      auto call = dyn_cast<func::CallOp>(use.getUser());
      if (!call || call.getNumOperands() != fn.getNumArguments()) {
        onlyCalls = false;
        break;
      }
      calls.push_back(call);
    }
    if (!onlyCalls)
      continue;
    for (func::CallOp call : calls)
      call->eraseOperands(unused);
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
    const MemObject &o = table.objs[id];
    if (o.escaping)
      continue;
    for (Operation *widthValue : o.writers) {
      if (!storedMemref(widthValue))
        continue;
      if (Operation *keyValue = findKiller(widthValue, table, id)) {
        if (remarks)
          widthValue->emitRemark()
              << "dead-memory-elimination: store to '" << objectName(o.def)
              << "' is overwritten before any read by the store "
                 "at "
              << keyValue->getLoc();
        Value stored =
            isa<affine::AffineStoreOp>(widthValue)
                ? cast<affine::AffineStoreOp>(widthValue).getValueToStore()
                : cast<memref::StoreOp>(widthValue).getValueToStore();
        if (Operation *def = stored.getDefiningOp())
          notes.byValueDef.try_emplace(
              def, "its store to '" + objectName(o.def).str() + "' at " +
                       shortLoc(widthValue->getLoc()) +
                       " is overwritten by the store at " +
                       shortLoc(keyValue->getLoc()) + " before any read");
        if (++notes.killedStores[o.def] == 1)
          notes.byObject[o.def] = "store at " + shortLoc(widthValue->getLoc()) +
                                  " overwritten by the store at " +
                                  shortLoc(keyValue->getLoc()) +
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
      if (auto call = dyn_cast<func::CallOp>(op)) {
        func::FuncOp callee = circt::hls_analysis::resolveDefinedCallee(call);
        if (!callee) {

          if (llvm::any_of(call.getOperands(), [](Value valueHandle) {
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
             llvm::enumerate(call.getArgOperands())) {
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

/// VITIS_NOTES N107: the value a call leaves in a one-element local of its
/// own function (a scalar passed by reference) is never read when, after the
/// call, the next op of the call's block that touches the local is a store
/// that overwrites it, or no op touches it up to the function's return (the
/// call is in the function's body block, not in a loop or an if). Kernel
/// w9r14p_dc_dead (`f(n, x, y); x = y = 1.0;`): Vitis deletes the call and
/// its sin / cos cores; whetstone mod7.
static bool overwrittenAfterCall(func::CallOp call, const MemObject &o) {
  auto alloca = dyn_cast<memref::AllocaOp>(o.def);
  if (!alloca || alloca->getParentOfType<func::FuncOp>() !=
                     call->getParentOfType<func::FuncOp>())
    return false;
  MemRefType memRefType = alloca.getType();
  if (!memRefType.hasStaticShape() || memRefType.getNumElements() != 1)
    return false;
  DenseSet<Value> aliases(o.aliases.begin(), o.aliases.end());
  auto touches = [&](Operation *op) {
    WalkResult resultValue = op->walk([&](Operation *inner) {
      for (Value valueHandle : inner->getOperands())
        if (aliases.contains(valueHandle))
          return WalkResult::interrupt();
      return WalkResult::advance();
    });
    return resultValue.wasInterrupted();
  };
  for (Operation *op = call->getNextNode(); op; op = op->getNextNode()) {
    Value mem, stored;
    if (auto st = dyn_cast<affine::AffineStoreOp>(op)) {
      mem = st.getMemRef();
      stored = st.getValueToStore();
    } else if (auto st = dyn_cast<memref::StoreOp>(op)) {
      mem = st.getMemRef();
      stored = st.getValueToStore();
    }
    if (mem && aliases.contains(mem) && !aliases.contains(stored))
      return true;
    if (touches(op))
      return false;
    if (op->hasTrait<OpTrait::IsTerminator>())
      return isa<func::ReturnOp>(op);
  }
  return false;
}

/// Deletes the dead calls; marks the arrays of dead calls that must stay.
static unsigned eraseDeadCalls(ModuleOp module, bool remarks, DeathNotes &notes,
                               bool overwrittenOutputs) {
  ObjectTable objects;
  objects.build(module);
  CalleeEffectTable effects;
  circt::hls_analysis::PartitionRoots partitions(module, false);

  std::vector<bool> objRead(objects.objs.size(), false);
  for (unsigned id = 0; id < objects.objs.size(); ++id) {
    const MemObject &o = objects.objs[id];
    if (!isa<memref::AllocaOp, memref::GlobalOp>(o.def)) {
      objRead[id] = true;
      continue;
    }
    for (Value valueHandle : o.aliases)
      for (OpOperand &use : valueHandle.getUses()) {
        Operation *user = use.getOwner();
        if (auto call = dyn_cast<func::CallOp>(user)) {
          func::FuncOp callee = circt::hls_analysis::resolveDefinedCallee(call);
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
  module.walk([&](func::CallOp call) {
    func::FuncOp callee = circt::hls_analysis::resolveDefinedCallee(call);
    if (!callee)
      return;
    const CalleeEffects &ce = effects.get(callee);
    SmallVector<std::optional<circt::hls_analysis::BankLayout>> layouts;
    std::string nonRoots;
    bool dead = ce.pure && call->use_empty();
    SmallVector<unsigned> outs;
    for (auto [loopIndex, valueHandle] :
         llvm::enumerate(call.getArgOperands())) {
      if (!isa<BaseMemRefType>(valueHandle.getType())) {
        layouts.push_back(std::nullopt);
        continue;
      }
      std::optional<unsigned> obj = objects.lookup(valueHandle);
      layouts.push_back(partitions.layoutOfRootValue(valueHandle));
      if (!obj)
        nonRoots += "P" + std::to_string(loopIndex);
      if (loopIndex < ce.written.size() && ce.written.test(loopIndex)) {
        if (obj && objRead[*obj] && overwrittenOutputs &&
            overwrittenAfterCall(call, objects.objs[*obj]))
          continue;
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
    Group &g = groups[git->second];
    g.calls.push_back(call);
    if (dead)
      outputsOf[call.getOperation()] = std::move(outs);
    else
      g.anyLive = true;
  });

  unsigned erased = 0;
  for (Group &g : groups) {
    if (g.anyLive) {

      for (func::CallOp call : g.calls) {
        auto it = outputsOf.find(call.getOperation());
        if (it == outputsOf.end())
          continue;
        for (unsigned id : it->second)
          objects.objs[id].def->setAttr(
              "hls.kept_reason",
              StringAttr::get(
                  module.getContext(),
                  "kept: never read, written by a call of @" +
                      call.getCallee().str() +
                      ", which has another live call site of the same "
                      "form; Vitis keeps the array as RAM_AUTO_0R0W at its "
                      "full cost (VITIS_NOTES.md N17 (a), N25)"));
      }
      continue;
    }
    for (func::CallOp call : g.calls) {
      if (auto it = outputsOf.find(call.getOperation()); it != outputsOf.end())
        for (unsigned id : it->second)
          notes.byDeadCall.try_emplace(
              objects.objs[id].def,
              "its writer, the call of @" + call.getCallee().str() + " at " +
                  shortLoc(call.getLoc()) +
                  ", was deleted: no array it writes is read and no call of "
                  "the same form is live (VITIS_NOTES.md N17 (a) / (d), N25)");
      if (remarks)
        call->emitRemark() << "dead-memory-elimination: call of @"
                           << call.getCallee()
                           << " deleted: no array it writes is read and no "
                              "call of the same form is live (N17 (a) / (d))";
      call->erase();
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
  Liveness(ModuleOp module, ObjectTable &table, bool keepCycles)
      : module(module), typeValue(table), keepCycles(keepCycles) {}

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
  void markLoadStoreCycles();

  ModuleOp module;
  ObjectTable &typeValue;
  bool keepCycles;
  DenseSet<Operation *> liveOps;
  DenseSet<Value> liveVals;
  DenseSet<std::pair<Operation *, unsigned>> liveIdx;
  DenseSet<Operation *> conservative;
  SmallVector<Operation *> opWork;
};

void Liveness::markObject(unsigned id) {
  MemObject &o = typeValue.objs[id];
  if (o.live)
    return;
  o.live = true;
  for (Operation *arrayValue : o.anchors)
    markOp(arrayValue);
  for (Operation *widthValue : o.writers)
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
      for (OpOperand &o : cast<LoopLikeOpInterface>(op).getInitsMutable())
        inits.insert(o.getOperandNumber());
    for (OpOperand &o : op->getOpOperands())
      if (!inits.contains(o.getOperandNumber()))
        markVal(o.get());
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

/// True if Vitis has turned the array into registers before it removes dead
/// code, so that a cycle through it is a dead register cycle like any other:
/// an array of at most complete_threshold elements (kernel w9r8i_dm_sroa:
/// `int cnt[2] = {0, 0}; ... cnt[0] += hist[i]` with cnt unused, Vitis keeps
/// only `hist`'s own update), or one whose every access names its element by
/// constant indices directly on the object (LLVM's SROA; Dehazing-denoising
/// `pixel_cnt[0] += blue_hist[i]`).
static bool isScalarised(const MemObject &o) {
  Type memRefType;
  if (auto g = dyn_cast<memref::GlobalOp>(o.def))
    memRefType = g.getType();
  else
    memRefType = o.def->getResult(0).getType();
  if (auto mt = dyn_cast<MemRefType>(memRefType))
    if (mt.hasStaticShape() &&
        mt.getNumElements() <=
            circt::hlsest::Config::get()
                .tool.hls.options.arrayPartition.completeThreshold)
      return true;
  auto constantAccess = [](Operation *op) {
    if (auto lowerIndex = dyn_cast<affine::AffineLoadOp>(op))
      return lowerIndex.getAffineMap().isConstant();
    if (auto st = dyn_cast<affine::AffineStoreOp>(op))
      return st.getAffineMap().isConstant();
    auto allConstant = [](ValueRange indexValue) {
      return llvm::all_of(indexValue, [](Value valueHandle) {
        return matchPattern(valueHandle, m_Constant());
      });
    };
    if (auto lowerIndex = dyn_cast<memref::LoadOp>(op))
      return allConstant(lowerIndex.getIndices());
    if (auto st = dyn_cast<memref::StoreOp>(op))
      return allConstant(st.getIndices());
    return false;
  };
  if (o.aliases.size() != o.anchors.size())
    return false;
  return llvm::all_of(o.readers, constantAccess) &&
         llvm::all_of(o.writers, constantAccess);
}

/// The tracked objects an op (not its regions) writes.
static void writtenObjects(Operation *op, const ObjectTable &typeValue,
                           llvm::SmallSetVector<unsigned, 4> &out) {
  auto eff = dyn_cast<MemoryEffectOpInterface>(op);
  if (!eff)
    return;
  SmallVector<MemoryEffects::EffectInstance> effects;
  eff.getEffects(effects);
  for (auto &entryValue : effects)
    if (isa<MemoryEffects::Write>(entryValue.getEffect()) &&
        entryValue.getValue())
      if (std::optional<unsigned> id = typeValue.lookup(entryValue.getValue()))
        if (!typeValue.objs[*id].scalarised)
          out.insert(*id);
}

/// A load GVN replaces by a stored value: directly after a store of the same
/// element (nothing in between touches the object), or a read-modify-write
/// accumulator whose loop LICM promotes to a register and
/// whose value before the loop is forwarded from a store to the element just
/// before it: `q[s][o] = 0; for d: q[s][o] += x[d] * w[o][d];` reads nothing
/// of q in Vitis (kernel w9r8i_dm_acc0: q removed when nothing reads it;
/// forgebench attention_op_p1 Q / K, VITIS_NOTES N1), so it is no load of a
/// load -> store cycle. When the element was written by an earlier loop nest
/// instead, the load before the promoted loop stays (w9r8i_dm_accn: q kept).
/// The loop is the innermost one around `load`, extended outwards while the
/// address stays invariant; no other access of the object may lie in it.
static bool isForwardedAccumulatorLoad(Operation *load, const MemObject &o) {
  if (!isa<affine::AffineLoadOp, memref::LoadOp>(load))
    return false;
  DenseSet<Operation *> accesses(o.readers.begin(), o.readers.end());
  accesses.insert(o.writers.begin(), o.writers.end());
  auto invariantIn = [&](Operation *loop) {
    for (Value valueHandle : load->getOperands()) {
      if (isa<BaseMemRefType>(valueHandle.getType()))
        continue;
      if (loop->getRegion(0).isAncestor(valueHandle.getParentRegion()))
        return false;
    }
    return true;
  };
  auto onlyThisElementIn = [&](Operation *loop) {
    for (Operation *arrayValue : accesses)
      if (loop->isAncestor(arrayValue) && !sameAddress(arrayValue, load))
        return false;
    return true;
  };

  auto forwardedBefore = [&](Operation *op) {
    for (Operation *prev = op->getPrevNode(); prev;
         prev = prev->getPrevNode()) {
      bool touches = false;
      prev->walk([&](Operation *in) {
        if (accesses.contains(in))
          touches = true;
      });
      if (!touches)
        continue;
      return accesses.contains(prev) && storedMemref(prev) &&
             sameAddress(prev, load) &&
             storedType(prev) == load->getResult(0).getType();
    }
    return false;
  };
  if (forwardedBefore(load))
    return true;
  Operation *loop = load->getParentOp();
  while (loop && !isHandledLoop(loop))
    loop = loop->getParentOp();
  if (!loop || isa<func::FuncOp>(loop) || !invariantIn(loop) ||
      !onlyThisElementIn(loop))
    return false;
  bool chain = llvm::any_of(o.writers, [&](Operation *st) {
    return loop->isAncestor(st) && sameAddress(st, load) &&
           isPromotableChainLoad(load, st, loop);
  });
  if (!chain)
    return false;
  while (true) {

    if (forwardedBefore(loop))
      return true;
    for (Operation *op = loop->getPrevNode(); op; op = op->getPrevNode()) {
      bool touches = false;
      op->walk([&](Operation *in) {
        if (accesses.contains(in))
          touches = true;
      });
      if (touches)
        return false;
    }
    Operation *parent = loop->getParentOp();
    if (!parent || !isHandledLoop(parent) || !invariantIn(parent) ||
        !onlyThisElementIn(parent))
      return false;
    loop = parent;
  }
}

/// VITIS_NOTES N66 (kernels w9r8p_dm_self / dm_selfaff, w9r8i_dm_cyc2 /
/// dm_ctl / dm_feed): Vitis removes an array only once no load from it is
/// used (LLVM deletes unused loads and then a store-only alloca; a store is
/// never deleted while its array still has a load, so there is no cyclic
/// dead-store elimination). An array whose loaded values reach, as stored
/// value, address or controlling condition, a store into itself, or into
/// another array that feeds it back the same way, is therefore kept although
/// nothing it holds leaves the design. An array accessed only at constant
/// indices takes no part (isScalarised: it is registers by then). Finds the
/// objects on such cycles of the
/// "a load of X feeds a store into Y" graph among the objects that are not
/// live yet and makes them roots; everything that feeds them follows from the
/// ordinary propagation.
void Liveness::markLoadStoreCycles() {
  const unsigned elementCount = typeValue.objs.size();
  for (MemObject &o : typeValue.objs)
    o.scalarised = isScalarised(o);
  std::vector<llvm::SmallSetVector<unsigned, 4>> feeds(elementCount);
  for (unsigned exprValue = 0; exprValue < elementCount; ++exprValue) {
    const MemObject &o = typeValue.objs[exprValue];
    if (o.live || o.readers.empty() || o.scalarised)
      continue;
    llvm::SmallSetVector<unsigned, 4> &out = feeds[exprValue];
    DenseSet<Value> seen;
    SmallVector<Value> work;
    auto taint = [&](Value valueHandle) {
      if (!isa<BaseMemRefType>(valueHandle.getType()) &&
          seen.insert(valueHandle).second)
        work.push_back(valueHandle);
    };

    auto controlled = [&](Operation *region) {
      region->walk([&](Operation *in) {
        if (in != region)
          writtenObjects(in, typeValue, out);
      });
      for (Value resultValue : region->getResults())
        taint(resultValue);
    };
    for (Operation *resultValue : o.readers)
      if (!isForwardedAccumulatorLoad(resultValue, o))
        for (Value valueHandle : resultValue->getResults())
          taint(valueHandle);
    while (!work.empty()) {
      Value valueHandle = work.pop_back_val();
      for (OpOperand &use : valueHandle.getUses()) {
        Operation *user = use.getOwner();
        writtenObjects(user, typeValue, out);
        if (isHandledLoop(user)) {
          auto loop = cast<LoopLikeOpInterface>(user);
          bool initialValue = false;
          for (OpOperand &loopIndex : loop.getInitsMutable())
            if (&loopIndex == &use) {
              unsigned keyValue =
                  loopIndex.getOperandNumber() -
                  loop.getInitsMutable().begin()->getOperandNumber();
              taint(loop.getRegionIterArgs()[keyValue]);
              taint(user->getResult(keyValue));
              initialValue = true;
            }
          if (!initialValue)
            controlled(user);
          continue;
        }
        if (user->getNumRegions() > 0) {
          controlled(user);
          continue;
        }
        if (user->hasTrait<OpTrait::IsTerminator>()) {
          Operation *parent = user->getParentOp();
          if (parent && (isHandledLoop(parent) || isHandledIf(parent))) {
            unsigned keyValue = use.getOperandNumber();
            if (keyValue < parent->getNumResults())
              taint(parent->getResult(keyValue));
            if (isHandledLoop(parent)) {
              auto iter = cast<LoopLikeOpInterface>(parent).getRegionIterArgs();
              if (keyValue < iter.size())
                taint(iter[keyValue]);
            }
          }
          continue;
        }
        for (Value resultValue : user->getResults())
          taint(resultValue);
      }
    }
  }

  for (unsigned exprValue = 0; exprValue < elementCount; ++exprValue) {
    if (feeds[exprValue].empty())
      continue;
    llvm::BitVector reached(elementCount);
    SmallVector<unsigned> stack(feeds[exprValue].begin(),
                                feeds[exprValue].end());
    for (unsigned rowValue : stack)
      reached.set(rowValue);
    while (!stack.empty() && !reached.test(exprValue)) {
      unsigned rowValue = stack.pop_back_val();
      for (unsigned depthValue : feeds[rowValue])
        if (!reached.test(depthValue)) {
          reached.set(depthValue);
          stack.push_back(depthValue);
        }
    }
    if (!reached.test(exprValue))
      continue;
    MemObject &o = typeValue.objs[exprValue];
    if (!o.def->hasAttr("hls.kept_reason"))
      o.def->setAttr(
          "hls.kept_reason",
          StringAttr::get(module.getContext(),
                          "kept: its loads feed stores into itself" +
                              std::string(feeds[exprValue].contains(exprValue)
                                              ? ""
                                              : " through other arrays") +
                              " (Vitis has no cyclic dead-store elimination; "
                              "VITIS_NOTES.md N66)"));
    markObject(exprValue);
  }
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

  if (keepCycles) {
    markLoadStoreCycles();
    while (!opWork.empty())
      processOp(opWork.pop_back_val());
  }
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
  Option<bool> loadStoreCycles{
      *this, "load-store-cycles",
      llvm::cl::desc("Keep an array whose loads feed stores into itself "
                     "(directly or through other arrays): Vitis has no "
                     "cyclic dead-store elimination (VITIS_NOTES.md N66)"),
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
  bool keepCycles = true;
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
      const MemObject &o = typeValue.objs[*id];
      stringValue =
          "'" + objectName(o.def).str() + "'" + (o.live ? "" : " (dead)");
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

static Attribute describeDead(Builder &buildPoint, const MemObject &o,
                              StringRef reason) {
  SmallVector<NamedAttribute> fieldValue;
  Operation *def = o.def;
  fieldValue.push_back(buildPoint.getNamedAttr(
      "name", buildPoint.getStringAttr(objectName(def))));
  StringRef opName = def->getName().getStringRef();
  fieldValue.push_back(buildPoint.getNamedAttr(
      "kind",
      buildPoint.getStringAttr(isa<memref::GlobalOp>(def)
                                   ? StringRef("global")
                                   : opName.drop_front(strlen("memref.")))));
  if (auto g = dyn_cast<memref::GlobalOp>(def))
    fieldValue.push_back(buildPoint.getNamedAttr(
        "symbol", buildPoint.getStringAttr(g.getSymName())));
  if (auto fn = def->getParentOfType<func::FuncOp>())
    fieldValue.push_back(buildPoint.getNamedAttr(
        "func", buildPoint.getStringAttr(fn.getName())));
  else if (!o.anchors.empty())
    if (auto fn = o.anchors.front()->getParentOfType<func::FuncOp>())
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
  Liveness live(module, table, keepCycles);
  live.run();

  bool changed = false;

  std::vector<std::string> reasons(table.objs.size());
  for (unsigned id = 0; id < table.objs.size(); ++id) {
    const MemObject &o = table.objs[id];
    if (o.live)
      continue;
    SmallVector<Operation *> reads;
    unsigned nWrites = 0;
    for (Value valueHandle : o.aliases)
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
    if (o.writers.empty() && reads.empty() && isa<memref::GlobalOp>(o.def) &&
        o.aliases.empty()) {
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
    auto kn = notes.byObject.find(o.def);
    if (kn != notes.byObject.end())
      os << "; " << notes.killedStores.lookup(o.def)
         << " overwritten store(s) deleted, first: " << kn->second;
    auto dc = notes.byDeadCall.find(o.def);
    if (dc != notes.byDeadCall.end())
      os << "; " << dc->second;
    if (o.def->hasAttr("hls.preserve"))
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
    const MemObject &o = table.objs[id];
    if (o.live)
      continue;
    records.push_back(describeDead(buildPoint, o, reasons[id]));
    if (remarks)
      o.def->emitRemark() << "dead-memory-elimination: removed '"
                          << objectName(o.def) << "': " << reasons[id];
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
  for (const MemObject &o : table.objs)
    if (!o.live && isa<memref::GlobalOp>(o.def))
      deadGlobals.push_back(o.def);
  for (Operation *op : dead)
    notes.forget(op);
  for (Operation *op : dead)
    op->dropAllReferences();
  for (Operation *op : dead) {
    op->dropAllUses();
    op->erase();
  }
  changed |= !dead.empty();

  for (Operation *g : deadGlobals) {
    notes.forget(g);
    g->erase();
    changed = true;
  }
  return changed;
}

void DeadMemoryEliminationPass::runOnOperation() {
  ModuleOp module = getOperation();

  const circt::hlsest::DeadMemoryConfig &dm =
      circt::hlsest::Config::get().tool.hls.middleEnd.deadMemory;
  const bool killOverwritten =
      circt::hlsest::resolveOption(overwrittenStores, dm.overwrittenStores);
  const bool eraseCalls = circt::hlsest::resolveOption(deadCalls, dm.deadCalls);
  keepCycles =
      circt::hlsest::resolveOption(loadStoreCycles, dm.keepLoadStoreCycles);
  notes = DeathNotes();
  SmallVector<Attribute> records;
  if (auto prev = module->getAttrOfType<ArrayAttr>("hls.dead_memrefs"))
    records.append(prev.begin(), prev.end());

  for (unsigned round = 0; round < 16; ++round) {
    bool changed = false;
    if (killOverwritten)
      changed |= killOverwrittenStores(module, remarks, notes) > 0;
    changed |= dropUnusedMemrefParams(module, remarks) > 0;
    if (eraseCalls)
      changed |=
          eraseDeadCalls(module, remarks, notes, dm.overwrittenCallOutputs) > 0;
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
  registerPass([] { return createMarkConstantFillsPass(); });
  registerPass([] { return createNarrowRamWidthsPass(); });
}
} // namespace circt::hls_analysis
