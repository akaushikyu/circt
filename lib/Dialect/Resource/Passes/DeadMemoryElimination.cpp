//===- DeadMemoryElimination.cpp - remove arrays Vitis HLS removes --------===//
//
// --dead-memory-elimination
//
// Vitis HLS deletes every array whose values cannot reach a side effect that
// leaves the design, together with all computation that only fed it, before
// it allocates memories (VITIS_NOTES.md N1, N1a; 35 kernels in
// ~/hls-est-work/exp-notes/dead_globals.md R1). The alloca / global is still
// present in db/a.g.ld.5.gdce.ll and gone in db/a.o.1.ll (the "Unroll/Inline"
// phase of csynth_design_size.rpt); no later stage removes an array, and an
// eliminated array has no memory row (0 BRAM). Observed cases: write-only
// arrays (dg_a_writeonly), arrays read only into another dead array
// (dg_b_unreached), arrays read into a scalar that is overwritten
// (dg_h_deadvalue), and arrays whose only consumer is multiplied by a folded
// constant 0 (dg_d_int0, dg_d_apfixed16: the forgebench attention Q and K).
// File-scope globals are removed exactly like locals (dg_e_globals_*).
//
// The pass is an aggressive dead-code elimination over the whole module whose
// unit of memory is an *object*: a memref.alloca / memref.alloc, or a
// memref.global together with all its memref.get_global sites (plus the views
// derived from them through ViewLikeOpInterface).
//
//   Live sinks (roots): the terminators of a function's blocks (func.return
//     and, in a multi-block body such as an inlined callee with an early
//     return, cf.br / cf.cond_br / cf.switch: the function's control flow is
//     kept, so branch conditions and successor operands are live); every call
//     (all operands);
//     every write to memory that is not a tracked object (function arguments,
//     unknown pointers); every op with unknown or untracked side effects; and
//     every object that escapes (passed to a call, stored as a value, yielded,
//     used by an op that is neither an access nor a view, or a global used by
//     several functions / by a non-get_global symbol user).
//   Propagation: a live op makes its operands live; a live value makes its
//     defining op live; a live load makes its object live; a live object makes
//     every op that writes to it live; a live op makes its enclosing loops /
//     ifs live (their bound / condition operands, not their iter_args). Loop
//     iter_args and if results are tracked per index, so a dead accumulator
//     chain inside a live loop dies (the attention QKV loop accumulates Q, K
//     and V in one loop; only V survives).
//   Load -> store cycles (option `load-store-cycles`, key
//     tool.hls.middle_end.dead_memory.load_store_cycles, default on): an
//     object whose loaded values reach a store into itself, directly or
//     through other objects (as the stored value, an address or the condition
//     of an enclosing if / loop), is a root as well: Vitis only deletes a
//     store once its array has no used load, so `cnt[k] = cnt[k] + 1` keeps
//     `cnt` although nothing it holds leaves the design (VITIS_NOTES.md N66).
//   Iterated to a fixpoint. After the stand-ins below are in place, every
//     value an op that stays (a live op, or a terminator of a live op / of a
//     function block) still uses is made live as well, with the same
//     propagation, so the erase step never leaves a null operand.
//   Then every op that is not live is erased (dead
//     objects with all their stores, the loops that only fed them, and the
//     loads / arithmetic whose results reach nothing). A dead iter_arg of a
//     live loop becomes a pass-through (yield its own block argument, init 0);
//     a dead result of a live if yields 0.
//
// Overwritten stores (option `overwritten-stores`, default on): before the
// liveness, a store S to a non-escaping object is deleted when a later store
// K to the same object with the same access (same memref value, equal affine
// access function, or the same index values for memref.store) and the same
// stored type is reached unconditionally after S in an enclosing block (S's
// own block, or the block containing the loop / if around S), with no op
// between them that may read the object - including every op inside the
// loops between S and K (their later iterations run after S), except loads of
// the same element whose value only feeds stores to that element (a
// read-modify-write accumulator `s[i][j] += q*k`, which LICM keeps in a
// register: no read of memory remains in the loop). This is what
// LLVM's LICM scalar promotion + DSE do to `for d: s[i][j] += q*k;
// s[i][j] *= scale` once `* scale` folded to `store 0`: the in-loop store
// of the accumulator is overwritten by the zero and Q, K die (dg_d_apfixed16,
// a.o.1.ll:1171 `store i16 0` with no Q/K loads). Because the accesses must be
// equal, a store indexed by an inner loop variable is never killed by a store
// outside that loop, so there is no cross-loop dead-store elimination
// (dead_globals.md R2, dg_c_overwrite: `buf[i] = x` loop, `buf[i] = 0` loop,
// read loop keeps all three loops and 1 BRAM).
//
// `hls.preserve` does not protect a dead array (Vitis removes it as well);
// a live one is never touched. The eliminated objects are recorded in the
// module attribute `hls.dead_memrefs` so that --bram-debug / --bram-debug-json
// list them with status "eliminated_dead" and the reason.
//
//===----------------------------------------------------------------------===//

#include "circt/Dialect/Resource/Config/ConfigUtils.h"
#include "circt/Dialect/Resource/Passes/VitisCleanup.h"
#include "circt/Dialect/Resource/Passes/CallInstances.h"
#include "circt/Dialect/Resource/Passes/PartitionLayout.h"

#include "mlir/Dialect/Affine/Analysis/AffineAnalysis.h"
#include "mlir/Dialect/Affine/Analysis/LoopAnalysis.h"
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
#include "llvm/ADT/StringMap.h"
#include "llvm/ADT/SetVector.h"
#include "llvm/Support/Path.h"
#include "llvm/Support/raw_ostream.h"

#include <functional>

#include <string>
#include <vector>

using namespace mlir;

namespace {

//===----------------------------------------------------------------------===//
// Objects and their aliases.
//===----------------------------------------------------------------------===//

struct MemObject {
  Operation *def = nullptr;            // alloca / alloc / memref.global
  SmallVector<Operation *> anchors;    // def (local) or its get_global ops
  SmallVector<Value> aliases;          // def result / get_global results / views
  SmallVector<Operation *> writers;    // ops with a Write or Free effect on it
  SmallVector<Operation *> readers;    // ops that only read it
  DenseSet<Operation *> functions;     // functions that hold an alias
  bool escaping = false;
  std::string escapeReason;
  bool live = false;
  bool scalarised = false; // only constant-index accesses (load-store cycles)
};

struct ObjectTable {
  std::vector<MemObject> objs;
  DenseMap<Value, unsigned> objOf;

  void build(ModuleOp module);

  std::optional<unsigned> lookup(Value v) const {
    auto it = objOf.find(v);
    if (it == objOf.end())
      return std::nullopt;
    return it->second;
  }

private:
  void close(unsigned id);
};

static StringRef objectName(Operation *def) {
  if (auto vn = def->getAttrOfType<StringAttr>("polygeist.varname"))
    return vn.getValue();
  if (auto g = dyn_cast<memref::GlobalOp>(def))
    return g.getSymName();
  return "<unnamed>";
}

/// file:line:col (file name without directories) of the first file location
/// inside `loc`, for the debug reasons.
static std::string shortLoc(Location loc) {
  if (auto f = dyn_cast<FileLineColLoc>(loc))
    return (llvm::sys::path::filename(f.getFilename().getValue()) + ":" +
            Twine(f.getLine()) + ":" + Twine(f.getColumn()))
        .str();
  if (auto n = dyn_cast<NameLoc>(loc))
    return shortLoc(n.getChildLoc());
  if (auto c = dyn_cast<CallSiteLoc>(loc))
    return shortLoc(c.getCallee());
  if (auto fu = dyn_cast<FusedLoc>(loc))
    for (Location l : fu.getLocations()) {
      std::string s = shortLoc(l);
      if (s != "?")
        return s;
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
  DenseMap<Operation *, unsigned> killedStores; // per object def
  // Per object def: the deleted call that wrote it (N17 (a) / (d), N25).
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
    std::optional<SymbolTable::UseRange> uses =
        SymbolTable::getSymbolUses(g, module);
    if (!uses) {
      o.escaping = true;
      o.escapeReason = "symbol uses unknown";
    } else {
      for (const SymbolTable::SymbolUse &use : *uses) {
        auto gg = dyn_cast<memref::GetGlobalOp>(use.getUser());
        if (!gg) {
          o.escaping = true;
          o.escapeReason = ("symbol used by " +
                            use.getUser()->getName().getStringRef())
                               .str();
          continue;
        }
        o.anchors.push_back(gg);
        o.aliases.push_back(gg.getResult());
      }
    }
    objs.push_back(std::move(o));
  }
  for (unsigned id = 0; id < objs.size(); ++id)
    close(id);
}

// Follow views, record writers, functions and escapes of object `id`.
void ObjectTable::close(unsigned id) {
  MemObject &o = objs[id];
  SmallVector<Value> work(o.aliases.begin(), o.aliases.end());
  for (Value v : work)
    objOf[v] = id;
  llvm::SetVector<Operation *> writers, readers;
  while (!work.empty()) {
    Value v = work.pop_back_val();
    if (auto fn = v.getParentRegion()->getParentOfType<func::FuncOp>())
      o.functions.insert(fn);
    for (OpOperand &use : v.getUses()) {
      Operation *user = use.getOwner();
      // A view: its memref results are further aliases of the object.
      if (auto view = dyn_cast<ViewLikeOpInterface>(user)) {
        if (view.getViewSource() == v) {
          for (Value r : user->getResults())
            if (isa<BaseMemRefType>(r.getType()) && !objOf.count(r)) {
              objOf[r] = id;
              o.aliases.push_back(r);
              work.push_back(r);
            }
          continue;
        }
      }
      if (isa<memref::DimOp>(user))
        continue; // reads the shape only
      // An access: an effect that names this very value.
      bool named = false, writes = false;
      if (auto eff = dyn_cast<MemoryEffectOpInterface>(user)) {
        SmallVector<MemoryEffects::EffectInstance> effects;
        eff.getEffects(effects);
        for (auto &e : effects) {
          if (e.getValue() != v)
            continue;
          named = true;
          if (isa<MemoryEffects::Write, MemoryEffects::Free>(e.getEffect()))
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
      // Anything else (call operand, stored as a value, yielded, returned,
      // an op without effect information): the object escapes.
      if (!o.escaping) {
        o.escaping = true;
        o.escapeReason =
            ("passed to " + user->getName().getStringRef()).str();
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
    o.escapeReason = "global used by " + std::to_string(o.functions.size()) +
                     " functions";
  }
  // tool.hls.middle_end.dead_memory.honour_preserve (Vitis: false): an array
  // the user marked to keep is a root of the liveness.
  if (dm.honourPreserve && o.def->hasAttr("hls.preserve") && !o.escaping) {
    o.escaping = true;
    o.escapeReason = "hls.preserve (honour_preserve)";
  }
}

//===----------------------------------------------------------------------===//
// Effects helpers.
//===----------------------------------------------------------------------===//

/// True if `op` (not its regions) may read memory of object `id`, or memory
/// it cannot name (unknown effects).
static bool mayReadObject(Operation *op, const ObjectTable &table,
                          unsigned id) {
  if (auto eff = dyn_cast<MemoryEffectOpInterface>(op)) {
    SmallVector<MemoryEffects::EffectInstance> effects;
    eff.getEffects(effects);
    for (auto &e : effects) {
      if (!isa<MemoryEffects::Read>(e.getEffect()))
        continue;
      if (!e.getValue())
        return true;
      std::optional<unsigned> o = table.lookup(e.getValue());
      if (!o || *o == id)
        return true; // untracked memref may alias? only args: cannot be id
    }
    return false;
  }
  if (op->hasTrait<OpTrait::HasRecursiveMemoryEffects>())
    return false; // the nested ops are checked by the caller's walk
  return true;    // unknown effects
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

//===----------------------------------------------------------------------===//
// Overwritten stores (LICM promotion + DSE in Vitis' LLVM pipeline).
//===----------------------------------------------------------------------===//

static Value storedMemref(Operation *op) {
  if (auto s = dyn_cast<affine::AffineStoreOp>(op))
    return s.getMemRef();
  if (auto s = dyn_cast<memref::StoreOp>(op))
    return s.getMemRef();
  return {};
}

static Type storedType(Operation *op) {
  if (auto s = dyn_cast<affine::AffineStoreOp>(op))
    return s.getValueToStore().getType();
  if (auto s = dyn_cast<memref::StoreOp>(op))
    return s.getValueToStore().getType();
  return {};
}

static Value accessedMemref(Operation *op) {
  if (Value m = storedMemref(op))
    return m;
  if (auto l = dyn_cast<affine::AffineLoadOp>(op))
    return l.getMemRef();
  if (auto l = dyn_cast<memref::LoadOp>(op))
    return l.getMemRef();
  return {};
}

/// Same memref value and the same element: equal affine access functions, or
/// the same index values for memref.load / memref.store.
static bool sameAddress(Operation *a, Operation *b) {
  Value ma = accessedMemref(a), mb = accessedMemref(b);
  if (!ma || ma != mb)
    return false;
  bool affA = isa<affine::AffineLoadOp, affine::AffineStoreOp>(a);
  bool affB = isa<affine::AffineLoadOp, affine::AffineStoreOp>(b);
  if (affA && affB)
    return affine::MemRefAccess(a) == affine::MemRefAccess(b);
  if (affA || affB)
    return false;
  auto indices = [](Operation *op) -> OperandRange {
    if (auto l = dyn_cast<memref::LoadOp>(op))
      return l.getIndices();
    return cast<memref::StoreOp>(op).getIndices();
  };
  return llvm::equal(indices(a), indices(b));
}

static bool sameAccess(Operation *a, Operation *b) {
  return storedMemref(a) && storedMemref(b) &&
         storedType(a) == storedType(b) && sameAddress(a, b);
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
    Value v = work.pop_back_val();
    if (!seen.insert(v).second)
      continue;
    for (OpOperand &use : v.getUses()) {
      Operation *user = use.getOwner();
      if (!anchor->isAncestor(user))
        return false;
      if (storedMemref(user)) {
        // Only as the stored value of a store to the same element.
        bool isValue = (isa<affine::AffineStoreOp>(user) &&
                        use.getOperandNumber() == 0) ||
                       (isa<memref::StoreOp>(user) &&
                        use.getOperandNumber() == 0);
        if (!isValue || !sameAccess(user, store))
          return false;
        continue;
      }
      // A terminator (a loop's yield) carries the value out of the chain.
      if (user->getNumRegions() != 0 || !isMemoryEffectFree(user) ||
          user->hasTrait<OpTrait::IsTerminator>())
        return false;
      for (Value r : user->getResults())
        work.push_back(r);
    }
  }
  return true;
}

/// The store that overwrites `store` before any read, or null.
static Operation *findKiller(Operation *store, const ObjectTable &table,
                             unsigned id) {
  Operation *anchor = store; // ancestor of `store` in the block being scanned
  while (true) {
    // Reads inside the anchor (other than the store itself) run after the
    // store in later iterations of the loops between them, unless they only
    // feed this element's accumulator chain (promotable to a register).
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
    std::optional<SymbolTable::UseRange> uses =
        SymbolTable::getSymbolUses(fn, module);
    if (!uses)
      continue;
    SmallVector<func::CallOp> calls;
    bool onlyCalls = true;
    for (const SymbolTable::SymbolUse &use : *uses) {
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
      for (unsigned i : unused.set_bits())
        fn.emitRemark() << "dead-memory: memref parameter #" << i
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
    for (Operation *w : o.writers) {
      if (!storedMemref(w))
        continue;
      if (Operation *k = findKiller(w, table, id)) {
        if (remarks)
          w->emitRemark() << "dead-memory-elimination: store to '"
                          << objectName(o.def)
                          << "' is overwritten before any read by the store "
                             "at "
                          << k->getLoc();
        Value stored = isa<affine::AffineStoreOp>(w)
                           ? cast<affine::AffineStoreOp>(w).getValueToStore()
                           : cast<memref::StoreOp>(w).getValueToStore();
        if (Operation *def = stored.getDefiningOp())
          notes.byValueDef.try_emplace(
              def, "its store to '" + objectName(o.def).str() + "' at " +
                       shortLoc(w->getLoc()) +
                       " is overwritten by the store at " +
                       shortLoc(k->getLoc()) + " before any read");
        if (++notes.killedStores[o.def] == 1)
          notes.byObject[o.def] = "store at " + shortLoc(w->getLoc()) +
                                  " overwritten by the store at " +
                                  shortLoc(k->getLoc()) + " before any read";
        dead.push_back(w);
      }
    }
  }
  for (Operation *op : dead)
    op->erase();
  return dead.size();
}

//===----------------------------------------------------------------------===//
// Calls whose outputs are never read (VITIS_NOTES.md N17 (a) / (d), N25).
//===----------------------------------------------------------------------===//
//
// A call to a non-inlined callee that only reads its inputs and writes its
// array parameters, whose results are unused and whose written arrays are
// never read by anything, is deleted by Vitis together with the arrays, when
// no other call of the same callee *form* is live (fbh3_g_callee_wr: a
// single-site filler is deleted with its global; fbrf_deadcall: the second
// call of `dotp` goes). When a call of the same form is live, the dead call
// stays and so does the array it writes, as RAM_AUTO_0R0W at its full cost,
// for a global and for a local alike (fbh3_g_callee_wr_shared,
// rvfb_h3_noalloc, w7_dl_global, w7_dl_local, w7_dl_toplocal; forgebench
// tiled_attn_module BRAM_A2 / A3 / B2 / B3). The form is the partition of
// the array arguments: Vitis clones a callee per argument partition (N14 R4),
// so the call that fills forgebench diff_orders_module's unpartitioned
// BRAM_C3 is its own single-site function, deleted with BRAM_C3, while the
// calls that fill the partitioned BRAM_A1 / BRAM_C1 stay.

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
    // Conservative while it is being computed (a recursive call).
    CalleeEffects &pending = table[fn.getOperation()];
    pending.pure = false;
    pending.read.resize(fn.getNumArguments());
    pending.written.resize(fn.getNumArguments());
    CalleeEffects computed = compute(fn);
    return table[fn.getOperation()] = std::move(computed);
  }

private:
  DenseMap<Operation *, CalleeEffects> table;

  // The parameter a memref value names (through views), or kLocal for memory
  // of the function's own allocas, kGlobal for a global, kUnknown otherwise.
  static constexpr int64_t kLocal = -1, kGlobal = -2, kUnknown = -3;
  static int64_t paramOf(Value v, func::FuncOp fn) {
    for (unsigned depth = 0; depth < 16; ++depth) {
      if (auto arg = dyn_cast<BlockArgument>(v)) {
        if (arg.getOwner() == &fn.getBody().front())
          return arg.getArgNumber();
        return kUnknown;
      }
      Operation *def = v.getDefiningOp();
      if (!def)
        return kUnknown;
      if (isa<memref::AllocaOp, memref::AllocOp>(def))
        return kLocal;
      if (isa<memref::GetGlobalOp>(def))
        return kGlobal;
      auto view = dyn_cast<ViewLikeOpInterface>(def);
      if (!view)
        return kUnknown;
      v = view.getViewSource();
    }
    return kUnknown;
  }

  CalleeEffects compute(func::FuncOp fn) {
    CalleeEffects e;
    e.read.resize(fn.getNumArguments());
    e.written.resize(fn.getNumArguments());
    auto note = [&](Value mem, bool isWrite) {
      int64_t p = paramOf(mem, fn);
      if (p >= 0)
        (isWrite ? e.written : e.read).set(static_cast<unsigned>(p));
      else if (p == kUnknown || (p == kGlobal && isWrite))
        e.pure = false;
    };
    fn.walk([&](Operation *op) {
      if (!e.pure)
        return;
      if (auto call = dyn_cast<func::CallOp>(op)) {
        func::FuncOp callee = circt::hls_analysis::resolveDefinedCallee(call);
        if (!callee) {
          // A function without a body (libm): pure only without memrefs.
          if (llvm::any_of(call.getOperands(), [](Value v) {
                return isa<BaseMemRefType>(v.getType());
              }))
            e.pure = false;
          return;
        }
        const CalleeEffects &ce = get(callee);
        if (!ce.pure) {
          e.pure = false;
          return;
        }
        for (auto [i, v] : llvm::enumerate(call.getArgOperands())) {
          if (!isa<BaseMemRefType>(v.getType()) || i >= ce.read.size())
            continue;
          if (ce.read.test(i))
            note(v, false);
          if (ce.written.test(i))
            note(v, true);
        }
        return;
      }
      if (isa<func::ReturnOp>(op)) {
        if (llvm::any_of(op->getOperands(), [](Value v) {
              return isa<BaseMemRefType>(v.getType());
            }))
          e.pure = false;
        return;
      }
      if (auto eff = dyn_cast<MemoryEffectOpInterface>(op)) {
        SmallVector<MemoryEffects::EffectInstance> effects;
        eff.getEffects(effects);
        for (auto &fx : effects) {
          if (isa<MemoryEffects::Allocate, MemoryEffects::Free>(fx.getEffect()))
            continue;
          if (!fx.getValue()) {
            e.pure = false;
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
      e.pure = false; // unknown effects
    });
    return e;
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
  MemRefType ty = alloca.getType();
  if (!ty.hasStaticShape() || ty.getNumElements() != 1)
    return false;
  DenseSet<Value> aliases(o.aliases.begin(), o.aliases.end());
  auto touches = [&](Operation *op) {
    WalkResult r = op->walk([&](Operation *inner) {
      for (Value v : inner->getOperands())
        if (aliases.contains(v))
          return WalkResult::interrupt();
      return WalkResult::advance();
    });
    return r.wasInterrupted();
  };
  // Whether `op` overwrites the local before it reads it (Overwrites),
  // touches it otherwise (Touches), or does not touch it (None).
  enum class Effect { None, Overwrites, Touches };
  const bool throughLoops = circt::hlsest::Config::get()
                                .tool.hls.middleEnd.deadMemory
                                .overwrittenByLoops;
  std::function<Effect(Operation *)> effectOf = [&](Operation *op) -> Effect {
    Value mem, stored;
    if (auto st = dyn_cast<affine::AffineStoreOp>(op)) {
      mem = st.getMemRef();
      stored = st.getValueToStore();
    } else if (auto st = dyn_cast<memref::StoreOp>(op)) {
      mem = st.getMemRef();
      stored = st.getValueToStore();
    }
    if (mem && aliases.contains(mem) && !aliases.contains(stored))
      return Effect::Overwrites;
    if (!touches(op))
      return Effect::None;
    // W9r14 review (kernel w9r14rv_dc_loopw: `f(n, x, y); for (k < 4) { x =
    // in[k]; y = 2 * in[k]; }`, Vitis 0): a loop that runs at least once and
    // whose body overwrites the local before any other access of it.
    if (auto loop = dyn_cast<affine::AffineForOp>(op);
        loop && throughLoops) {
      std::optional<uint64_t> trip = affine::getConstantTripCount(loop);
      if (trip && *trip >= 1)
        for (Operation &in : loop.getBody()->without_terminator()) {
          Effect e = effectOf(&in);
          if (e != Effect::None)
            return e;
        }
    }
    return Effect::Touches;
  };
  for (Operation *op = call->getNextNode(); op; op = op->getNextNode()) {
    Effect e = effectOf(op);
    if (e == Effect::Overwrites)
      return true;
    if (e == Effect::Touches)
      return false;
    if (op->hasTrait<OpTrait::IsTerminator>())
      return isa<func::ReturnOp>(op);
  }
  return false;
}

/// Deletes the dead calls; marks the arrays of dead calls that must stay.
static unsigned eraseDeadCalls(ModuleOp module, bool remarks,
                               DeathNotes &notes, bool overwrittenOutputs) {
  ObjectTable objects;
  objects.build(module);
  CalleeEffectTable effects;
  circt::hls_analysis::PartitionRoots partitions(module, /*warn=*/false);

  // Per object: is it read anywhere (a load, a call whose callee reads the
  // parameter, or a use this analysis does not understand)?
  std::vector<bool> objRead(objects.objs.size(), false);
  for (unsigned id = 0; id < objects.objs.size(); ++id) {
    const MemObject &o = objects.objs[id];
    if (!isa<memref::AllocaOp, memref::GlobalOp>(o.def)) {
      objRead[id] = true;
      continue;
    }
    for (Value v : o.aliases)
      for (OpOperand &use : v.getUses()) {
        Operation *user = use.getOwner();
        if (auto call = dyn_cast<func::CallOp>(user)) {
          func::FuncOp callee = circt::hls_analysis::resolveDefinedCallee(call);
          unsigned i = use.getOperandNumber();
          if (!callee) {
            objRead[id] = true;
            continue;
          }
          const CalleeEffects &ce = effects.get(callee);
          if (!ce.pure || i >= ce.read.size() || ce.read.test(i))
            objRead[id] = true;
          continue;
        }
        if (auto view = dyn_cast<ViewLikeOpInterface>(user))
          if (view.getViewSource() == v)
            continue; // its results are aliases of their own
        if (isa<memref::DimOp>(user))
          continue;
        if (storedMemref(user) && use.getOperandNumber() == 0) {
          objRead[id] = true; // the memref stored as a value
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
        for (auto &f : fx) {
          if (f.getValue() != v)
            continue;
          named = true;
          if (isa<MemoryEffects::Read>(f.getEffect()))
            objRead[id] = true;
        }
        if (!named)
          objRead[id] = true;
      }
  }

  // Calls, grouped by callee form; a call is dead when it is pure, its
  // results are unused and every array it writes is an unread object.
  struct Group {
    SmallVector<func::CallOp> calls;
    bool anyLive = false;
  };
  SmallVector<Group> groups;          // in program order of their first call
  llvm::StringMap<unsigned> groupIndex; // "callee|form" -> index
  DenseMap<Operation *, SmallVector<unsigned>> outputsOf; // dead call -> objs
  module.walk([&](func::CallOp call) {
    func::FuncOp callee = circt::hls_analysis::resolveDefinedCallee(call);
    if (!callee)
      return;
    const CalleeEffects &ce = effects.get(callee);
    SmallVector<std::optional<circt::hls_analysis::BankLayout>> layouts;
    std::string nonRoots;
    bool dead = ce.pure && call->use_empty();
    SmallVector<unsigned> outs;
    for (auto [i, v] : llvm::enumerate(call.getArgOperands())) {
      if (!isa<BaseMemRefType>(v.getType())) {
        layouts.push_back(std::nullopt);
        continue;
      }
      std::optional<unsigned> obj = objects.lookup(v);
      layouts.push_back(partitions.layoutOfRootValue(v));
      if (!obj)
        nonRoots += "P" + std::to_string(i); // a parameter: its own form
      if (i < ce.written.size() && ce.written.test(i)) {
        if (obj && objRead[*obj] && overwrittenOutputs &&
            overwrittenAfterCall(call, objects.objs[*obj]))
          continue; // the value it writes is never read (N107)
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
      // N17 (a): the arrays the dead calls write stay at their full cost.
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

//===----------------------------------------------------------------------===//
// Liveness.
//===----------------------------------------------------------------------===//

static bool isHandledLoop(Operation *op) {
  return isa<affine::AffineForOp, scf::ForOp>(op);
}
static bool isHandledIf(Operation *op) {
  return isa<affine::AffineIfOp, scf::IfOp>(op);
}
static bool canMaterializeZero(Type t) {
  return isa<IntegerType, IndexType, FloatType>(t);
}

class Liveness {
public:
  Liveness(ModuleOp module, ObjectTable &table, bool keepCycles)
      : module(module), t(table), keepCycles(keepCycles) {}

  void run();
  bool isLive(Operation *op) const { return liveOps.contains(op); }
  bool iterLive(Operation *op, unsigned i) const {
    return liveIdx.contains({op, i});
  }
  bool isConservative(Operation *op) const {
    return conservative.contains(op);
  }
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
  void markVal(Value v);
  void markIdx(Operation *op, unsigned i);
  void markObject(unsigned id);
  void processOp(Operation *op);
  void markLoadStoreCycles();

  ModuleOp module;
  ObjectTable &t;
  bool keepCycles;
  DenseSet<Operation *> liveOps;
  DenseSet<Value> liveVals;
  DenseSet<std::pair<Operation *, unsigned>> liveIdx;
  DenseSet<Operation *> conservative;
  SmallVector<Operation *> opWork;
};

void Liveness::markObject(unsigned id) {
  MemObject &o = t.objs[id];
  if (o.live)
    return;
  o.live = true;
  for (Operation *a : o.anchors)
    markOp(a);
  for (Operation *w : o.writers)
    markOp(w);
}

void Liveness::markVal(Value v) {
  if (!liveVals.insert(v).second)
    return;
  if (std::optional<unsigned> id = t.lookup(v))
    markObject(*id);
  if (auto r = dyn_cast<OpResult>(v)) {
    Operation *def = r.getOwner();
    if (!conservative.contains(def) &&
        (isHandledLoop(def) || isHandledIf(def)))
      markIdx(def, r.getResultNumber());
    markOp(def);
    return;
  }
  auto a = cast<BlockArgument>(v);
  Operation *owner = a.getOwner()->getParentOp();
  // A function block argument is a function argument (entry block) or is fed
  // by the successor operands of its predecessors' branches, which are roots
  // (every terminator of a function block is live), so nothing to follow.
  if (!owner || isa<func::FuncOp>(owner))
    return;
  if (isHandledLoop(owner) && !conservative.contains(owner)) {
    auto loop = cast<LoopLikeOpInterface>(owner);
    auto iterArgs = loop.getRegionIterArgs();
    for (unsigned i = 0; i < iterArgs.size(); ++i)
      if (iterArgs[i] == v)
        markIdx(owner, i);
  }
  markOp(owner); // induction variable, iter_arg or conservative block arg
}

void Liveness::markIdx(Operation *op, unsigned i) {
  if (!liveIdx.insert({op, i}).second)
    return;
  markOp(op);
  if (isHandledLoop(op)) {
    auto loop = cast<LoopLikeOpInterface>(op);
    markVal(loop.getInits()[i]);
    markVal(loop.getRegionIterArgs()[i]);
    if (auto yielded = loop.getYieldedValuesMutable())
      markVal((*yielded)[i].get());
    markVal(op->getResult(i));
    return;
  }
  // affine.if / scf.if: result i comes from operand i of each branch's yield.
  for (Region &r : op->getRegions())
    if (!r.empty())
      markVal(r.front().getTerminator()->getOperand(i));
  markVal(op->getResult(i));
}

void Liveness::processOp(Operation *op) {
  if (op->getNumRegions() > 0 && !conservative.contains(op) &&
      (isHandledLoop(op) || isHandledIf(op))) {
    // Control operands only (bounds, step, condition); not the inits.
    DenseSet<unsigned> inits;
    if (isHandledLoop(op))
      for (OpOperand &o : cast<LoopLikeOpInterface>(op).getInitsMutable())
        inits.insert(o.getOperandNumber());
    for (OpOperand &o : op->getOpOperands())
      if (!inits.contains(o.getOperandNumber()))
        markVal(o.get());
  } else if (op->getNumRegions() > 0) {
    // Unknown region semantics: everything it uses or yields is live.
    for (Value v : op->getOperands())
      markVal(v);
    for (Region &r : op->getRegions())
      for (Block &b : r)
        if (!b.empty() && b.back().hasTrait<OpTrait::IsTerminator>())
          markOp(&b.back());
  } else {
    for (Value v : op->getOperands())
      markVal(v);
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
  Type ty;
  if (auto g = dyn_cast<memref::GlobalOp>(o.def))
    ty = g.getType();
  else
    ty = o.def->getResult(0).getType();
  if (auto mt = dyn_cast<MemRefType>(ty))
    if (mt.hasStaticShape() &&
        mt.getNumElements() <= circt::hlsest::Config::get()
                                   .tool.hls.options.arrayPartition
                                   .completeThreshold)
      return true;
  auto constantAccess = [](Operation *op) {
    if (auto l = dyn_cast<affine::AffineLoadOp>(op))
      return l.getAffineMap().isConstant();
    if (auto st = dyn_cast<affine::AffineStoreOp>(op))
      return st.getAffineMap().isConstant();
    auto allConstant = [](ValueRange idx) {
      return llvm::all_of(idx, [](Value v) { return matchPattern(v, m_Constant()); });
    };
    if (auto l = dyn_cast<memref::LoadOp>(op))
      return allConstant(l.getIndices());
    if (auto st = dyn_cast<memref::StoreOp>(op))
      return allConstant(st.getIndices());
    return false;
  };
  if (o.aliases.size() != o.anchors.size())
    return false; // views
  return llvm::all_of(o.readers, constantAccess) &&
         llvm::all_of(o.writers, constantAccess);
}

/// The tracked objects an op (not its regions) writes.
static void writtenObjects(Operation *op, const ObjectTable &t,
                           llvm::SmallSetVector<unsigned, 4> &out) {
  auto eff = dyn_cast<MemoryEffectOpInterface>(op);
  if (!eff)
    return;
  SmallVector<MemoryEffects::EffectInstance> effects;
  eff.getEffects(effects);
  for (auto &e : effects)
    if (isa<MemoryEffects::Write>(e.getEffect()) && e.getValue())
      if (std::optional<unsigned> id = t.lookup(e.getValue()))
        if (!t.objs[*id].scalarised)
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
    for (Value v : load->getOperands()) {
      if (isa<BaseMemRefType>(v.getType()))
        continue;
      if (loop->getRegion(0).isAncestor(v.getParentRegion()))
        return false;
    }
    return true;
  };
  auto onlyThisElementIn = [&](Operation *loop) {
    for (Operation *a : accesses)
      if (loop->isAncestor(a) && !sameAddress(a, load))
        return false;
    return true;
  };
  // The nearest earlier op of `op`'s block that touches the object is a store
  // of the loaded element: GVN forwards its value, no load remains (the
  // `store 0; load; store` of a struct member's default initialisation and
  // copy, gnnbuilder `sum_incremental_data::finalized`, which Vitis
  // removes).
  auto forwardedBefore = [&](Operation *op) {
    for (Operation *prev = op->getPrevNode(); prev; prev = prev->getPrevNode()) {
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
    // The store that forwards the value before the loop: the nearest earlier
    // op of the loop's block that touches the object.
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
  const unsigned n = t.objs.size();
  for (MemObject &o : t.objs)
    o.scalarised = isScalarised(o);
  std::vector<llvm::SmallSetVector<unsigned, 4>> feeds(n);
  for (unsigned x = 0; x < n; ++x) {
    const MemObject &o = t.objs[x];
    if (o.live || o.readers.empty() || o.scalarised)
      continue;
    llvm::SmallSetVector<unsigned, 4> &out = feeds[x];
    DenseSet<Value> seen;
    SmallVector<Value> work;
    auto taint = [&](Value v) {
      if (!isa<BaseMemRefType>(v.getType()) && seen.insert(v).second)
        work.push_back(v);
    };
    // Every store nested in a region op whose control a loaded value decides.
    auto controlled = [&](Operation *region) {
      region->walk([&](Operation *in) {
        if (in != region)
          writtenObjects(in, t, out);
      });
      for (Value r : region->getResults())
        taint(r);
    };
    for (Operation *r : o.readers)
      if (!isForwardedAccumulatorLoad(r, o))
        for (Value v : r->getResults())
          taint(v);
    while (!work.empty()) {
      Value v = work.pop_back_val();
      for (OpOperand &use : v.getUses()) {
        Operation *user = use.getOwner();
        writtenObjects(user, t, out);
        if (isHandledLoop(user)) {
          auto loop = cast<LoopLikeOpInterface>(user);
          bool init = false;
          for (OpOperand &i : loop.getInitsMutable())
            if (&i == &use) {
              unsigned k = i.getOperandNumber() -
                           loop.getInitsMutable().begin()->getOperandNumber();
              taint(loop.getRegionIterArgs()[k]);
              taint(user->getResult(k));
              init = true;
            }
          if (!init)
            controlled(user);
          continue;
        }
        if (user->getNumRegions() > 0) {
          controlled(user); // an if condition, or unknown region semantics
          continue;
        }
        if (user->hasTrait<OpTrait::IsTerminator>()) {
          Operation *parent = user->getParentOp();
          if (parent && (isHandledLoop(parent) || isHandledIf(parent))) {
            unsigned k = use.getOperandNumber();
            if (k < parent->getNumResults())
              taint(parent->getResult(k));
            if (isHandledLoop(parent)) {
              auto iter = cast<LoopLikeOpInterface>(parent).getRegionIterArgs();
              if (k < iter.size())
                taint(iter[k]);
            }
          }
          continue;
        }
        for (Value r : user->getResults())
          taint(r);
      }
    }
  }
  // Objects on a cycle: those that reach themselves.
  for (unsigned x = 0; x < n; ++x) {
    if (feeds[x].empty())
      continue;
    llvm::BitVector reached(n);
    SmallVector<unsigned> stack(feeds[x].begin(), feeds[x].end());
    for (unsigned y : stack)
      reached.set(y);
    while (!stack.empty() && !reached.test(x)) {
      unsigned y = stack.pop_back_val();
      for (unsigned z : feeds[y])
        if (!reached.test(z)) {
          reached.set(z);
          stack.push_back(z);
        }
    }
    if (!reached.test(x))
      continue;
    MemObject &o = t.objs[x];
    if (!o.def->hasAttr("hls.kept_reason"))
      o.def->setAttr(
          "hls.kept_reason",
          StringAttr::get(module.getContext(),
                          "kept: its loads feed stores into itself"
                          + std::string(feeds[x].contains(x)
                                            ? ""
                                            : " through other arrays") +
                          " (Vitis has no cyclic dead-store elimination; "
                          "VITIS_NOTES.md N66)"));
    markObject(x);
  }
}

void Liveness::run() {
  // Region ops whose iter_args / results cannot be given a stand-in value
  // when dead are handled conservatively.
  module.walk([&](Operation *op) {
    if (isHandledLoop(op)) {
      for (Value a : cast<LoopLikeOpInterface>(op).getRegionIterArgs())
        if (!canMaterializeZero(a.getType()))
          conservative.insert(op);
    } else if (isHandledIf(op)) {
      for (Type ty : op->getResultTypes())
        if (!canMaterializeZero(ty))
          conservative.insert(op);
    }
  });

  for (unsigned id = 0; id < t.objs.size(); ++id)
    if (t.objs[id].escaping)
      markObject(id);

  module.walk([&](Operation *op) {
    if (isa<func::FuncOp, ModuleOp, memref::GlobalOp>(op))
      return;
    if (!op->getParentOfType<func::FuncOp>())
      return;
    // func.return, and the cf.br / cf.cond_br / cf.switch of a multi-block
    // function body (an inlined callee with an early return): the control
    // flow of the function stays, so its conditions and the successor
    // operands that feed the next blocks' arguments are live.
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
      for (auto &e : effects) {
        if (isa<MemoryEffects::Read, MemoryEffects::Allocate>(e.getEffect()))
          continue;
        if (isa<MemoryEffects::Write, MemoryEffects::Free>(e.getEffect()) &&
            e.getValue() && t.lookup(e.getValue()))
          continue; // live only if the object is
        markOp(op); // write to an argument / unknown memory, other effects
        return;
      }
      return;
    }
    if (op->hasTrait<OpTrait::HasRecursiveMemoryEffects>() ||
        op->hasTrait<OpTrait::IsTerminator>())
      return;
    markOp(op); // no effect information
  });

  while (!opWork.empty())
    processOp(opWork.pop_back_val());
  // Second phase: the cycles among the objects the first one left dead (a
  // cycle through a live object changes nothing), so that only the arrays the
  // rule keeps carry its hls.kept_reason.
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
      for (Value v : op->getOperands()) {
        auto r = dyn_cast<OpResult>(v);
        if (!r || liveOps.contains(r.getOwner()))
          continue;
        markVal(v);
        ++added;
        grew = true;
      }
    });
    while (!opWork.empty())
      processOp(opWork.pop_back_val());
  }
  return added;
}

//===----------------------------------------------------------------------===//
// The pass.
//===----------------------------------------------------------------------===//

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
  void getDependentDialects(DialectRegistry &registry) const override {
    registry.insert<arith::ArithDialect, memref::MemRefDialect>();
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
static std::string deadChain(Operation *load, const ObjectTable &t,
                             const DeathNotes &notes) {
  std::string out;
  llvm::raw_string_ostream os(out);
  os << load->getName().getStringRef() << " at " << shortLoc(load->getLoc());
  if (load->getNumResults() != 1)
    return out;
  Value cur = load->getResult(0);
  DenseSet<Value> seen{cur};
  auto objText = [&](Value m) {
    std::string s;
    if (std::optional<unsigned> id = t.lookup(m)) {
      const MemObject &o = t.objs[*id];
      s = "'" + objectName(o.def).str() + "'" + (o.live ? "" : " (dead)");
    } else {
      s = "an untracked memref";
    }
    return s;
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
    for (OpOperand &u : cur.getUses()) {
      Operation *user = u.getOwner();
      if (Value m = storedMemref(user)) {
        bool asValue = u.getOperandNumber() == 0;
        os << " -> "
           << (asValue ? "stored into " : "an index of a store into ")
           << objText(m) << " at " << shortLoc(user->getLoc());
        return out;
      }
      if (user->hasTrait<OpTrait::IsTerminator>()) {
        Operation *parent = user->getParentOp();
        unsigned i = u.getOperandNumber();
        if (parent && (isHandledLoop(parent) || isHandledIf(parent)) &&
            i < parent->getNumResults()) {
          if (!next && !seen.contains(parent->getResult(i))) {
            next = parent->getResult(i);
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
    // A store of this value that the overwritten-store step deleted.
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

static Attribute describeDead(Builder &b, const MemObject &o,
                              StringRef reason) {
  SmallVector<NamedAttribute> f;
  Operation *def = o.def;
  f.push_back(b.getNamedAttr("name", b.getStringAttr(objectName(def))));
  StringRef opName = def->getName().getStringRef();
  f.push_back(b.getNamedAttr(
      "kind", b.getStringAttr(isa<memref::GlobalOp>(def)
                                  ? StringRef("global")
                                  : opName.drop_front(strlen("memref.")))));
  if (auto g = dyn_cast<memref::GlobalOp>(def))
    f.push_back(b.getNamedAttr("symbol", b.getStringAttr(g.getSymName())));
  if (auto fn = def->getParentOfType<func::FuncOp>())
    f.push_back(b.getNamedAttr("func", b.getStringAttr(fn.getName())));
  else if (!o.anchors.empty())
    if (auto fn = o.anchors.front()->getParentOfType<func::FuncOp>())
      f.push_back(b.getNamedAttr("func", b.getStringAttr(fn.getName())));
  Type ty = isa<memref::GlobalOp>(def) ? Type(cast<memref::GlobalOp>(def).getType())
                                       : def->getResult(0).getType();
  f.push_back(b.getNamedAttr("type", TypeAttr::get(ty)));
  f.push_back(b.getNamedAttr("loc", LocationAttr(def->getLoc())));
  f.push_back(b.getNamedAttr("reason", b.getStringAttr(reason)));
  if (def->hasAttr("hls.preserve"))
    f.push_back(b.getNamedAttr("preserve", b.getUnitAttr()));
  if (auto fg = def->getAttrOfType<StringAttr>("hls.from_global"))
    f.push_back(b.getNamedAttr("from_global", fg));
  return b.getDictionaryAttr(f);
}

bool DeadMemoryEliminationPass::eliminateOnce(
    ModuleOp module, SmallVectorImpl<Attribute> &records) {
  ObjectTable table;
  table.build(module);
  Liveness live(module, table, keepCycles);
  live.run();

  bool changed = false;

  // Why each dead object is dead, on the IR the liveness saw (the stand-ins
  // below rewrite the yields the chains go through).
  std::vector<std::string> reasons(table.objs.size());
  for (unsigned id = 0; id < table.objs.size(); ++id) {
    const MemObject &o = table.objs[id];
    if (o.live)
      continue;
    SmallVector<Operation *> reads;
    unsigned nWrites = 0;
    for (Value v : o.aliases)
      for (Operation *u : v.getUsers()) {
        auto eff = dyn_cast<MemoryEffectOpInterface>(u);
        if (!eff)
          continue;
        if (eff.hasEffect<MemoryEffects::Read>())
          reads.push_back(u);
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

  // Dead iter_args / if results of live region ops: give them stand-ins so
  // the values that fed them can be erased.
  module.walk([&](Operation *op) {
    if (!live.isLive(op) || live.isConservative(op))
      return;
    if (isHandledLoop(op)) {
      auto loop = cast<LoopLikeOpInterface>(op);
      auto iterArgs = loop.getRegionIterArgs();
      auto yielded = loop.getYieldedValuesMutable();
      for (unsigned i = 0; i < iterArgs.size(); ++i) {
        if (live.iterLive(op, i))
          continue;
        bool alreadyPassThrough =
            yielded && (*yielded)[i].get() == iterArgs[i] &&
            matchPattern(loop.getInitsMutable()[i].get(), m_Constant());
        if (alreadyPassThrough)
          continue; // stand-in from an earlier round
        OpBuilder ob(op);
        Type ty = iterArgs[i].getType();
        Value zero = arith::ConstantOp::create(ob, op->getLoc(), ty,
                                               ob.getZeroAttr(ty));
        loop.getInitsMutable()[i].set(zero);
        if (yielded)
          (*yielded)[i].set(iterArgs[i]);
        changed = true;
      }
    } else if (isHandledIf(op)) {
      for (unsigned i = 0; i < op->getNumResults(); ++i) {
        if (live.iterLive(op, i))
          continue;
        bool allConstant = llvm::all_of(op->getRegions(), [&](Region &r) {
          return r.empty() ||
                 matchPattern(r.front().getTerminator()->getOperand(i),
                              m_Constant());
        });
        if (allConstant)
          continue; // stand-ins from an earlier round (or constants anyway)
        OpBuilder ob(op);
        Type ty = op->getResult(i).getType();
        Value zero = arith::ConstantOp::create(ob, op->getLoc(), ty,
                                               ob.getZeroAttr(ty));
        for (Region &r : op->getRegions())
          if (!r.empty()) {
            r.front().getTerminator()->setOperand(i, zero);
            changed = true;
          }
      }
    }
  });

  // Everything an op that stays still uses becomes live: the stand-in
  // constants and loop inits that are stand-ins from an earlier round. (This
  // replaces a rule that kept any side-effect-free op with a live user but
  // erased that op's own operands.)
  live.closeOverSurvivors();

  // Record and report the dead objects (after the closure, which only adds).
  Builder b(module.getContext());
  for (unsigned id = 0; id < table.objs.size(); ++id) {
    const MemObject &o = table.objs[id];
    if (o.live)
      continue;
    records.push_back(describeDead(b, o, reasons[id]));
    if (remarks)
      o.def->emitRemark() << "dead-memory-elimination: removed '"
                          << objectName(o.def) << "': " << reasons[id];
  }

  // Erase every op that does not survive (top-most only; the terminators of
  // ops that stay, and of function blocks, stay as well).
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
  // Dead globals, collected before anything is erased: the `def` of a dead
  // alloca dangles once the loop below has erased it.
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

  // Their get_global sites were erased above.
  for (Operation *g : deadGlobals) {
    notes.forget(g);
    g->erase();
    changed = true;
  }
  return changed;
}

void DeadMemoryEliminationPass::runOnOperation() {
  ModuleOp module = getOperation();
  // Vitis clones a kept callee per tuple of argument IR types (VITIS_NOTES
  // N165), before its dead-code removal (a.o.1); the clones are separate
  // functions from here on.
  if (circt::hlsest::Config::get().tool.hls.clonePerArgumentType)
    circt::hls_analysis::cloneKeptCalleesPerArgumentType(module);
  // An option given explicitly, else tool.hls.middle_end.dead_memory.
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
  // Erasing dead loads can expose more overwritten stores and vice versa.
  for (unsigned round = 0; round < 16; ++round) {
    bool changed = false;
    if (killOverwritten)
      changed |= killOverwrittenStores(module, remarks, notes) > 0;
    changed |= dropUnusedMemrefParams(module, remarks) > 0;
    if (eraseCalls)
      changed |= eraseDeadCalls(module, remarks, notes,
                                dm.overwrittenCallOutputs) > 0;
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
