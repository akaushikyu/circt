//===- RamWidthNarrowing.cpp - the element width Vitis gives a RAM --------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// --narrow-ram-widths
//
// Vitis stores fewer bits per word than the declared element type when it can
// prove the other bits are never needed. The narrowing happens in reflow
// after the arrays are partitioned (every bank of an array gets the same
// width) and before the storage is chosen, so the LUTRAM threshold and the
// BRAM formula see the narrow width (td=off kernels w9n_*: `int a[1024]`
// becomes `[1024 x i6]` between a.o.1.ll and a.o.2.ll; `int a[64]` used as an
// index of a 64-word table is 64x6 = LUTRAM, 0 BRAM). The width is
//
//   min(Wr, Wd), capped by the declared width, where
//
//   Wr  the bits every value stored into the array needs: the union of their
//       integer ranges, unsigned width when no value is negative, else signed
//       width (ReLU outputs 31 of 32 bits; `& 0x7F` 7; a clamp to [0, 255] 8,
//       to [-128, 127] 8; a loop counter below 1024 10; an 8-term sum of
//       4-bit values 7). Elements never written do not count; a load from
//       another array has that array's range (a copy of a ReLU output is 31
//       bits too); a scalar parameter of a callee has the union of what its
//       call sites pass; a top-level scalar argument is full range.
//
//   Wd  1 + the highest bit any user of a load needs, walking the uses
//       backwards: a subscript needs the low bits of the flattened address of
//       the array it indexes (a 64 / 65 / 100 / 4096-word table: 6 / 7 / 7 /
//       12; `t[64][64]`: 12 on the last dimension, 6 on the first; a
//       cyclic or block partitioned dimension counts; a subscript of a
//       completely partitioned dimension of S elements selects a bank and
//       needs ceil(log2 S) bits in a read, every bit in a write, N91);
//       add / sub / mul / and / or / xor pass the low-bit
//       demand through; `& c` keeps up to the highest set bit of c (`& 0xF0`
//       is 8 bits: the low bits stay); a right shift by c adds c; a
//       truncation or extension caps it; a store into another array needs
//       that array's Wd; comparisons, divisions, interface stores, returns
//       and unknown calls need every bit (`a[i] < 5` and `tbl[a[i]] ^ a[i]`
//       keep 32).
//
// Arrays that reach one callee memref parameter share one width (the larger:
// a corpus design passes a 7-bit and a 12-bit index array through one
// parameter, both are 12 bits). Interfaces (memref parameters of the top
// function), arrays that escape to something this pass cannot follow, and
// ROMs (initialised globals never written, arrays marked by
// --mark-constant-fills, which have their own width rule) are not narrowed.
//
// The pass only annotates: every narrowed alloca / global gets
// `hls.narrow_bits` (the width) and `hls.narrow_reason` (Wr, Wd and the use
// that decided). --memory-banking-bram copies both to the banks and
// --bram-analysis prices the array with that width. It runs after
// --auto-pipeline-unroll (an unrolled accumulation is an expression tree,
// not a recurrence) and before --memory-banking-bram.
//
// Vitis computes each array's range once, from the arrays its values are
// loaded from: an array whose stored values depend on its own loads
// (directly or around a cycle of arrays) sees those loads at full range
// (`a[i] = a[i + 1] ^ (a[i] >> 1)` keeps 64 bits, kernel w9i_self), though a
// mask after the load still bounds the value (w9i_selfadd).
//
// An undefined value (llvm.mlir.undef, an arm cgeist builds for a path that
// returns nothing, e.g. hls::recip's `if (x == 0) return 0;`) contributes
// nothing to a select or an if's result (VITIS_NOTES N151 (b), kernel
// w9r21p_a1_lutdiv). A load from a register array (completely partitioned)
// or from a field of a local struct (an llvm.load through cgeist's pointer)
// takes the range of the store that reaches it in the same block, when one
// does, rather than the union of every store into it (N151 (c), kernel
// w9r21p_a5_overwrite; barry_walker lab2's attention_row_local.data).
//
// Not modelled (unconfirmed in Vitis): ranges through loop-carried scalars
// (an iter_arg is full range here; two corpus designs narrow accumulations),
// call results. The address width of interface arrays (VITIS_NOTES N41): a
// subscript of an ap_memory array argument (no pragma under
// flow_target=vivado) demands the bits of its address like a local; one of
// an m_axi argument (tool.hls.narrowing.full_address_interface_modes)
// demands every bit. A memcpy into a local array (cgeist's byte-copy loop
// through polygeist.memref2pointer) is a store of unknown values, not an
// escape.
//
//===----------------------------------------------------------------------===//

#include "circt/Dialect/Resource/Config/ConfigUtils.h"
#include "circt/Dialect/Resource/HLS/HLSOps.h"
#include "circt/Dialect/Resource/Passes/PartitionLayout.h"
#include "circt/Dialect/Resource/Passes/PolygeistCompat.h"
#include "circt/Dialect/Resource/Passes/VitisCleanup.h"

#include "mlir/Dialect/Affine/IR/AffineMemoryOpInterfaces.h"
#include "mlir/Dialect/Affine/Analysis/LoopAnalysis.h"
#include "mlir/Dialect/Affine/IR/AffineOps.h"
#include "mlir/Dialect/Arith/IR/Arith.h"
#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/Dialect/LLVMIR/LLVMDialect.h"
#include "mlir/Dialect/MemRef/IR/MemRef.h"
#include "mlir/Dialect/SCF/IR/SCF.h"
#include "mlir/IR/BuiltinOps.h"
#include "mlir/IR/Matchers.h"
#include "mlir/IR/SymbolTable.h"
#include "mlir/Interfaces/InferIntRangeInterface.h"
#include "mlir/Interfaces/ViewLikeInterface.h"
#include "mlir/Pass/Pass.h"

#include "llvm/ADT/EquivalenceClasses.h"
#include "llvm/ADT/TypeSwitch.h"
#include "llvm/Support/MathExtras.h"
#include "llvm/Support/Path.h"
#include "llvm/Support/raw_ostream.h"

#include <optional>
#include <string>

using namespace mlir;
using namespace circt::hls_analysis;

namespace {

/// Fixpoint rounds in which the stored range of an array (or the range of a
/// callee parameter) may still grow before it is set to the full range. It
/// counts rounds, not stores: any number of stores in one pass over
/// straight-line code (an unrolled loop) is one change. A recurrence through
/// memory never reaches this, its loads are full range (`cyclic`); the cap
/// only bounds the work.
constexpr unsigned kWidenAfterRounds = 8;
/// Nesting of `&&` / `||` conditions a bound is read through.
constexpr unsigned kMaxConditionDepth = 8;
/// Rounds of the demanded-bits fixpoint (it grows at most to the widths, so
/// it ends; the cap only bounds the work).
constexpr unsigned kMaxDemandRounds = 128;
/// Steps of the def-use chain the reason prints.
constexpr unsigned kMaxChainSteps = 6;

/// Bits of an integer or index value (index: 64), 0 for anything else.
unsigned bitWidthOf(Type t) {
  if (auto it = dyn_cast<IntegerType>(t))
    return it.getWidth();
  if (isa<IndexType>(t))
    return IndexType::kInternalStorageBitWidth;
  return 0;
}

/// file:line:col (file name only) of the first file location in `loc`.
std::string shortLoc(Location loc) {
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

/// The bits a range needs: unsigned width when no value is negative, else
/// the signed width. At least 1.
unsigned bitsForRange(const ConstantIntRanges &r) {
  if (!r.smin().isNegative())
    return std::max(1u, r.smax().getActiveBits());
  return std::max(r.smin().getSignificantBits(),
                  r.smax().getSignificantBits());
}

std::string rangeText(const ConstantIntRanges &r) {
  bool isSigned = r.smin().isNegative();
  const APInt &lo = isSigned ? r.smin() : r.umin();
  const APInt &hi = isSigned ? r.smax() : r.umax();
  return "[" + llvm::toString(lo, 10, isSigned) + ", " +
         llvm::toString(hi, 10, isSigned) + "]";
}

//===----------------------------------------------------------------------===//
// Memory accesses.
//===----------------------------------------------------------------------===//

/// A read or write of one memref element.
struct Access {
  Value memref;
  Value stored; // the value a write stores; null for a read
};

std::optional<Access> asAccess(Operation *op) {
  if (auto ld = dyn_cast<memref::LoadOp>(op))
    return Access{ld.getMemRef(), {}};
  if (auto st = dyn_cast<memref::StoreOp>(op))
    return Access{st.getMemRef(), st.getValueToStore()};
  if (auto st = dyn_cast<StoreEnableOp>(op))
    return Access{st.getMemref(), st.getValue()};
  if (auto rd = dyn_cast<affine::AffineReadOpInterface>(op))
    return Access{rd.getMemRef(), {}};
  if (auto wr = dyn_cast<affine::AffineWriteOpInterface>(op))
    return Access{wr.getMemRef(), wr.getValueToStore()};
  return std::nullopt;
}

/// The subscript position of operand `operandNo` of a non-affine access, or
/// nullopt when the operand is not a subscript.
std::optional<unsigned> plainSubscriptPosition(Operation *op,
                                               unsigned operandNo) {
  unsigned first = 0;
  if (isa<memref::LoadOp>(op))
    first = 1;
  else if (isa<memref::StoreOp>(op))
    first = 2;
  else if (isa<StoreEnableOp>(op))
    first = 3;
  else
    return std::nullopt;
  if (operandNo < first)
    return std::nullopt;
  return operandNo - first;
}

bool hasDivOrMod(AffineExpr e) {
  bool found = false;
  e.walk([&](AffineExpr s) {
    if (s.getKind() == AffineExprKind::Mod ||
        s.getKind() == AffineExprKind::FloorDiv ||
        s.getKind() == AffineExprKind::CeilDiv)
      found = true;
  });
  return found;
}

/// Whether map operand `j` (dims first, then symbols) occurs in `e`.
bool usesOperand(AffineExpr e, AffineMap map, unsigned j) {
  if (j < map.getNumDims())
    return e.isFunctionOfDim(j);
  return e.isFunctionOfSymbol(j - map.getNumDims());
}

//===----------------------------------------------------------------------===//
// Memory classes: an array with its banks-to-be, views and the callee
// parameters it reaches. One class gets one width.
//===----------------------------------------------------------------------===//

/// Whether every use of `ptr` is either the address of an `llvm.store` or
/// the base of an `llvm.getelementptr` whose result satisfies the same
/// condition; `any` is set when at least one store is reached.
static bool onlyStoredThrough(Value ptr, bool &any) {
  for (OpOperand &use : ptr.getUses()) {
    Operation *user = use.getOwner();
    StringRef name = user->getName().getStringRef();
    if (name == "llvm.getelementptr") {
      if (use.getOperandNumber() != 0 || user->getNumResults() != 1 ||
          !onlyStoredThrough(user->getResult(0), any))
        return false;
      continue;
    }
    // llvm.store's operands are (value, address).
    if (name != "llvm.store" || use.getOperandNumber() != 1)
      return false;
    any = true;
  }
  return true;
}

/// Whether `op` is the destination side of cgeist's lowering of `memcpy`
/// into an array: `polygeist.memref2pointer` whose pointer is only offset by
/// (chains of) `llvm.getelementptr` and stored through with `llvm.store`
/// (the byte-copy loop; `memcpy(&a[k], ...)` adds a constant-offset GEP in
/// front of the loop's GEP). Vitis treats such a copy-in as ordinary stores
/// of values it knows nothing about (VITIS_NOTES N41, kernels
/// w9p5_idx_loc256 and w9rv_n41_mc): the array keeps its own address, and
/// its width is what its loads demand.
static bool isMemcpyDestination(Operation *op) {
  if (op->getName().getStringRef() != "polygeist.memref2pointer" ||
      op->getNumResults() != 1)
    return false;
  bool any = false;
  for (OpOperand &use : op->getResult(0).getUses())
    if (use.getOwner()->getName().getStringRef() != "llvm.getelementptr")
      return false;
  return onlyStoredThrough(op->getResult(0), any) && any;
}

struct MemClass {
  SmallVector<Operation *> roots; // alloca / alloc / memref.global
  SmallVector<Operation *> loads;
  SmallVector<Operation *> stores;
  // Never narrowed. `opaque`: its address and its values are unknown too (an
  // interface, an escape); a ROM keeps its known address and values.
  bool fixed = false;
  bool opaque = false;
  // Its subscripts index an address space this pass cannot see (an m_axi
  // interface, an escape): a subscript demands every bit. An ap_memory
  // interface is opaque but its address is the array's own (VITIS_NOTES N41).
  bool addressOpaque = false;
  // Filled by a memcpy (cgeist's byte-copy loop through
  // polygeist.memref2pointer): stores of unknown values (VITIS_NOTES N41).
  bool copiedIn = false;
  std::string fixedReason;
  Type elemType;
  unsigned declaredBits = 0;
  // Values present before any store (an initial value), if any.
  std::optional<ConstantIntRanges> initRange;
  // Fixpoint state.
  IntegerValueRange stored;
  unsigned rangeChanges = 0; // rounds in which `stored` grew
  bool grewThisRound = false;
  bool rangePinned = false;
  std::string pinReason;
  // Its stored values depend on its own loads (directly or through other
  // arrays): Vitis does not iterate, its loads are full range.
  bool cyclic = false;
  int scc = -1; // the strongly connected component of a cyclic class
  // A store whose value has no range at the fixpoint (it comes from
  // something never reached): its range is unknown.
  bool unknownStore = false;
  unsigned demand = 0;
  bool demandPinned = false;
  // Explanation.
  Operation *widestStore = nullptr;
  unsigned widestBits = 0;
  Operation *decidingLoad = nullptr;
};

class Narrowing {
public:
  Narrowing(ModuleOp module, bool useRanges, bool useDemand, bool remarks,
            ArrayRef<std::string> fullAddressModes, bool completeReadSelector,
            bool undefContributesNothing, bool reachingStoreRanges,
            bool accumulationRanges, bool calleeParamStoresFullRange)
      : module(module), symbols(module), partitions(module, /*warn=*/false),
        rangesOn(useRanges), demandOn(useDemand), remarksOn(remarks),
        completeReadSelector(completeReadSelector),
        undefContributesNothing(undefContributesNothing),
        reachingStoreRanges(reachingStoreRanges),
        accumulationRanges(accumulationRanges),
        calleeParamStoresFullRange(calleeParamStoresFullRange),
        fullAddressModes(fullAddressModes.begin(), fullAddressModes.end()) {}

  void run();

private:
  // --- Classes ---
  void buildClasses();
  unsigned nodeOf(const void *key);
  void trackValue(Value v, unsigned node,
                  SmallVectorImpl<std::pair<Value, unsigned>> &work);
  MemClass *classOf(Value memref) const;
  func::FuncOp internalCallee(func::CallOp call) const;
  bool isInternalFunction(func::FuncOp f) const;
  bool computeInternal(func::FuncOp f) const;
  bool hasFullAddressInterface(func::FuncOp f, unsigned arg) const;

  // --- Stored ranges (forward) ---
  void solveRanges();
  void markCyclicClasses();
  const SmallVector<unsigned, 2> &loadClassesOf(Value v);
  IntegerValueRange rangeOf(Value v);
  IntegerValueRange operandRange(OpOperand &use);
  bool isUndefined(Value v) const;
  const SmallVector<Operation *, 2> &reachingStore(Operation *load);
  SmallVector<Operation *, 2> findReachingStore(Operation *load,
                                                bool exactOnly = false,
                                                Operation *from = nullptr);
  // --- Accumulations (N159) ---
  struct Accumulation {
    Value init;                  ///< the loop's init operand
    SmallVector<Value, 4> steps; ///< the addends of the yielded chain
    int64_t trips = 0;
  };
  const std::optional<Accumulation> &accumulationOf(BlockArgument arg);
  void updateAccumulations(Operation *yield);
  DenseMap<Value, std::optional<Accumulation>> accumulations;
  /// Per accumulation iter_arg: its range at the start of an iteration
  /// (init + (T - 1) x step) and the loop result's (init + T x step).
  DenseMap<Value, IntegerValueRange> accumulationRange;
  DenseMap<Value, IntegerValueRange> accumulationResult;
  DenseMap<Value, unsigned> accumulationChanges;
  // The same accumulation through memory: `a[x] = init` before a loop of T
  // trips whose body adds to a[x] (`a[x] = a[x] + s`, x invariant; N159).
  struct MemAccumulation {
    SmallVector<Operation *, 2> inits; ///< the stores of init before the loop
    Operation *store = nullptr;        ///< the read-modify-write store
    SmallVector<Value, 4> steps;       ///< its addends
    int64_t trips = 0;
  };
  const std::optional<MemAccumulation> &memAccumulationOf(Operation *load);
  DenseMap<Operation *, std::optional<MemAccumulation>> memAccumulations;
  /// Per accumulating load: the range of one iteration's step (persists
  /// across rounds, as the steps follow the load in program order).
  DenseMap<Operation *, IntegerValueRange> memAccumulationStep;
  DenseMap<Operation *, unsigned> memAccumulationStepChanges;
  /// The read-modify-write store of each accumulating load -> the load.
  DenseMap<Operation *, Operation *> memAccumulationLoadOf;
  std::optional<std::pair<Value, int64_t>> pointerLocation(Value ptr);
  Value rootOf(Value v) const;
  bool writesCalleeParameter(Operation *store) const;
  bool calleeMayWrite(func::FuncOp callee, unsigned arg, unsigned depth = 0);
  DenseMap<std::pair<Operation *, unsigned>, bool> calleeWrites;
  std::optional<ConstantIntRanges> conditionBound(Value v, Value cond,
                                                  bool holds,
                                                  unsigned depth = 0);
  std::optional<ConstantIntRanges> compareBound(Value v, arith::CmpIOp cmp,
                                                bool holds);
  std::optional<APInt> constantOf(Value v);
  std::optional<std::pair<uint64_t, uint64_t>> smallUnsignedRange(Value v);
  IntegerValueRange blockArgRange(BlockArgument arg);
  void forwardOp(Operation *op);
  void endRound();
  std::optional<std::pair<int64_t, int64_t>>
  affineRange(AffineExpr e, ValueRange dims, ValueRange syms);

  // --- Demanded bits (backward) ---
  void solveDemand();
  std::pair<unsigned, Operation *> valueDemand(Value v);
  unsigned useDemand(OpOperand &use);
  unsigned resultDemand(Value r) const { return demand.lookup(r); }
  std::optional<unsigned> subscriptBits(Value memref, unsigned dim,
                                        bool isRead) const;
  std::optional<SmallVector<bool>> completeDims(Value memref) const;
  std::optional<std::pair<int64_t, int64_t>> subscriptRange(Operation *access,
                                                            unsigned dim);
  bool differentBanks(Operation *a, Operation *b);
  bool feedsBackIntoSameBank(Value v, unsigned cls, Operation *store);
  unsigned affineAccessDemand(Operation *op, OpOperand &use, unsigned w);

  // --- Result ---
  std::optional<unsigned> constantSetBits(const MemClass &c);
  void annotate();
  std::string demandChain(Operation *load) const;
  std::string nameOf(Value memref) const;

  ModuleOp module;
  SymbolTable symbols;
  PartitionRoots partitions;
  bool rangesOn, demandOn, remarksOn;
  // A read's subscript of a completely partitioned dimension of S elements
  // demands ceil(log2 S) bits (the bank selector, VITIS_NOTES N91)
  // (tool.hls.narrowing.complete_read_selector).
  bool completeReadSelector;
  bool undefContributesNothing;
  bool reachingStoreRanges;
  bool accumulationRanges;
  bool calleeParamStoresFullRange;
  /// The reaching stores of a load (empty: none), computed once.
  DenseMap<Operation *, SmallVector<Operation *, 2>> reachingStores;
  /// The same with exactOnly (the store of the load's own address).
  DenseMap<Operation *, SmallVector<Operation *, 2>> reachingStoresExact;
  const SmallVector<Operation *, 2> &reachingStoreExact(Operation *load);
  /// Per block, the ops that may write each root (in block order), and the
  /// ops that may write without saying what.
  struct BlockWriters {
    DenseMap<Value, SmallVector<Operation *>> byRoot;
    SmallVector<Operation *> unknown;
  };
  const BlockWriters &blockWriters(Block *block);
  DenseMap<Block *, std::unique_ptr<BlockWriters>> blockWriterCache;
  /// The memories a region op may write (their roots), or `unknown`.
  struct RegionWrites {
    DenseSet<Value> roots;
    bool unknown = false;
  };
  const RegionWrites &regionWrites(Operation *op);
  DenseMap<Operation *, std::unique_ptr<RegionWrites>> regionWriteCache;
  // Interface modes whose array subscripts demand every bit
  // (tool.hls.narrowing.full_address_interface_modes).
  SmallVector<std::string> fullAddressModes;

  // Union-find over roots and callee parameters (keys: root ops, block
  // arguments as opaque pointers).
  llvm::EquivalenceClasses<unsigned> unionFind;
  DenseMap<const void *, unsigned> nodeIds;
  DenseMap<Value, unsigned> nodeOfValue;
  DenseMap<unsigned, std::string> opaqueNodes; // node -> why
  DenseSet<unsigned> addressKnownNodes; // opaque, but own address (N41)
  DenseSet<unsigned> copiedInNodes;     // a memcpy destination
  SmallVector<Operation *> nodeRoot;           // node -> root op or null
  std::vector<MemClass> classes;
  DenseMap<unsigned, unsigned> classOfLeader;

  // Ops in program order (post-order: a region op after its body).
  SmallVector<Operation *> ops;

  // Forward state.
  DenseMap<Value, IntegerValueRange> ranges;
  DenseMap<Value, IntegerValueRange> paramRange; // callee scalar params
  DenseMap<Value, unsigned> paramRangeChanges; // rounds in which it grew
  DenseSet<Value> paramGrewThisRound;
  DenseSet<Value> paramRangePinned;
  bool rangesChanged = false;
  DenseMap<Value, SmallVector<unsigned, 2>> loadClasses;
  DenseMap<Operation *, SmallVector<func::CallOp>> callSites;
  mutable DenseMap<Operation *, bool> internalFunctions;

  // Backward state.
  DenseMap<Value, unsigned> demand;
  DenseMap<Value, Operation *> demandUser;
  DenseMap<Value, unsigned> paramDemand;
  DenseSet<Value> paramDemandPinned;
};

unsigned Narrowing::nodeOf(const void *key) {
  auto [it, inserted] = nodeIds.try_emplace(key, nodeIds.size());
  if (inserted) {
    unionFind.insert(it->second);
    nodeRoot.push_back(nullptr);
  }
  return it->second;
}

func::FuncOp Narrowing::internalCallee(func::CallOp call) const {
  auto f = symbols.lookup<func::FuncOp>(call.getCallee());
  if (!f || f.isExternal() || !isInternalFunction(f))
    return {};
  return f;
}

/// A private function whose every symbol use is a direct call: its parameters
/// are what the call sites pass.
bool Narrowing::isInternalFunction(func::FuncOp f) const {
  auto cached = internalFunctions.find(f);
  if (cached != internalFunctions.end())
    return cached->second;
  bool internal = computeInternal(f);
  internalFunctions[f] = internal;
  return internal;
}

/// Whether memref parameter `arg` of the public function `f` has an
/// interface pragma of a mode whose subscripts demand every bit (m_axi: the
/// subscript is part of a bus address). An array parameter without a pragma
/// is an ap_memory port under flow_target=vivado: its subscript demands the
/// bits of its own address, as for a local (VITIS_NOTES N41).
bool Narrowing::hasFullAddressInterface(func::FuncOp f, unsigned arg) const {
  auto ifaces = f.getArgAttrOfType<ArrayAttr>(arg, "hls.interface");
  if (!ifaces)
    return false;
  for (Attribute a : ifaces) {
    auto d = dyn_cast<DictionaryAttr>(a);
    auto mode = d ? d.getAs<StringAttr>("mode") : StringAttr();
    if (mode && llvm::is_contained(fullAddressModes, mode.getValue().str()))
      return true;
  }
  return false;
}

bool Narrowing::computeInternal(func::FuncOp f) const {
  if (!f.isPrivate() || f.isExternal())
    return false;
  std::optional<SymbolTable::UseRange> uses =
      SymbolTable::getSymbolUses(f, module);
  if (!uses)
    return false;
  bool any = false;
  for (const SymbolTable::SymbolUse &u : *uses) {
    if (!isa<func::CallOp>(u.getUser()))
      return false;
    any = true;
  }
  return any;
}

void Narrowing::trackValue(Value v, unsigned node,
                           SmallVectorImpl<std::pair<Value, unsigned>> &work) {
  if (nodeOfValue.try_emplace(v, node).second)
    work.push_back({v, node});
}

void Narrowing::buildClasses() {
  module.walk([&](func::CallOp call) {
    if (auto f = symbols.lookup<func::FuncOp>(call.getCallee()))
      callSites[f].push_back(call);
  });
  SmallVector<std::pair<Value, unsigned>> work;
  module.walk([&](Operation *op) {
    if (isa<memref::AllocaOp, memref::AllocOp>(op)) {
      unsigned n = nodeOf(op);
      nodeRoot[n] = op;
      trackValue(op->getResult(0), n, work);
    }
  });
  for (auto g : module.getOps<memref::GlobalOp>()) {
    unsigned n = nodeOf(g.getOperation());
    nodeRoot[n] = g;
    if (g.isExternal())
      opaqueNodes[n] = "external global";
    std::optional<SymbolTable::UseRange> uses =
        SymbolTable::getSymbolUses(g, module);
    if (!uses) {
      opaqueNodes[n] = "symbol uses unknown";
      continue;
    }
    for (const SymbolTable::SymbolUse &u : *uses) {
      if (auto gg = dyn_cast<memref::GetGlobalOp>(u.getUser()))
        trackValue(gg.getResult(), n, work);
      else
        opaqueNodes[n] = ("symbol used by " +
                          u.getUser()->getName().getStringRef())
                             .str();
    }
  }
  for (auto f : module.getOps<func::FuncOp>()) {
    if (f.isExternal())
      continue;
    bool internal = isInternalFunction(f);
    for (BlockArgument a : f.getArguments()) {
      if (!isa<BaseMemRefType>(a.getType()))
        continue;
      unsigned n = nodeOf(a.getAsOpaquePointer());
      if (!internal) {
        opaqueNodes[n] = "interface (memref parameter of " +
                         f.getSymName().str() + ")";
        if (!hasFullAddressInterface(f, a.getArgNumber()))
          addressKnownNodes.insert(n);
      }
      trackValue(a, n, work);
    }
  }

  while (!work.empty()) {
    auto [v, n] = work.pop_back_val();
    for (OpOperand &use : v.getUses()) {
      Operation *user = use.getOwner();
      if (std::optional<Access> acc = asAccess(user))
        if (acc->memref == v && acc->stored != v)
          continue; // the access is collected per class below
      if (auto view = dyn_cast<ViewLikeOpInterface>(user))
        if (view.getViewSource() == v) {
          for (Value r : user->getResults())
            if (isa<BaseMemRefType>(r.getType()))
              trackValue(r, n, work);
          continue;
        }
      if (isa<memref::DimOp, memref::DeallocOp>(user))
        continue;
      if (isMemcpyDestination(user)) {
        copiedInNodes.insert(n);
        continue;
      }
      if (auto call = dyn_cast<func::CallOp>(user))
        if (func::FuncOp callee = internalCallee(call)) {
          BlockArgument p = callee.getArgument(use.getOperandNumber());
          unionFind.unionSets(n, nodeOf(p.getAsOpaquePointer()));
          continue;
        }
      opaqueNodes[n] =
          ("escapes to " + user->getName().getStringRef()).str();
    }
  }

  // One class per union-find set.
  for (const auto *ec : unionFind) {
    if (!ec->isLeader())
      continue;
    unsigned leader = ec->getData();
    classOfLeader[leader] = classes.size();
    classes.emplace_back();
    MemClass &c = classes.back();
    for (auto m = unionFind.member_begin(*ec); m != unionFind.member_end();
         ++m) {
      if (Operation *root = nodeRoot[*m])
        c.roots.push_back(root);
      c.copiedIn |= copiedInNodes.contains(*m);
      auto o = opaqueNodes.find(*m);
      if (o == opaqueNodes.end())
        continue;
      c.addressOpaque |= !addressKnownNodes.contains(*m);
      if (!c.opaque) {
        c.opaque = c.fixed = true;
        c.fixedReason = o->second;
      }
    }
  }

  // Accesses, element types, ROMs, initial values.
  module.walk([&](Operation *op) {
    std::optional<Access> acc = asAccess(op);
    if (!acc)
      return;
    MemClass *c = classOf(acc->memref);
    if (!c)
      return;
    (acc->stored ? c->stores : c->loads).push_back(op);
  });
  for (MemClass &c : classes) {
    auto setFixed = [&](const std::string &why) {
      if (!c.fixed) {
        c.fixed = true;
        c.fixedReason = why;
      }
    };
    for (Operation *root : c.roots) {
      Type elt = isa<memref::GlobalOp>(root)
                     ? cast<memref::GlobalOp>(root).getType().getElementType()
                     : cast<MemRefType>(root->getResult(0).getType())
                           .getElementType();
      if (!c.elemType)
        c.elemType = elt;
      else if (c.elemType != elt)
        setFixed("element types differ");
      if (root->hasAttr("hls.const_fill"))
        setFixed("array written only with constants (ROM width rule)");
      auto g = dyn_cast<memref::GlobalOp>(root);
      if (!g || g.isExternal())
        continue;
      unsigned w = bitWidthOf(elt);
      ConstantIntRanges init = ConstantIntRanges::constant(APInt(w ? w : 1, 0));
      if (auto d = dyn_cast_or_null<DenseIntElementsAttr>(
              g.getInitialValueAttr())) {
        bool first = true;
        for (const APInt &v : d.getValues<APInt>()) {
          ConstantIntRanges r = ConstantIntRanges::constant(v);
          init = first ? r : init.rangeUnion(r);
          first = false;
        }
      }
      if (w)
        c.initRange = c.initRange ? c.initRange->rangeUnion(init) : init;
      if (!g.isUninitialized() && c.stores.empty())
        setFixed("initialised global never written: a ROM (ROM width rule)");
    }
    if (!c.elemType && c.roots.empty())
      continue; // only parameters: an interface, never priced here
    c.declaredBits = c.elemType ? bitWidthOf(c.elemType) : 0;
    if (!isa_and_nonnull<IntegerType>(c.elemType))
      setFixed("element type is not an integer");
    // Every access moves one element (no vector loads / stores).
    for (Operation *ld : c.loads)
      if (ld->getNumResults() != 1 ||
          ld->getResult(0).getType() != c.elemType)
        setFixed("an access moves more than one element");
    for (Operation *st : c.stores)
      if (asAccess(st)->stored.getType() != c.elemType)
        setFixed("an access moves more than one element");
  }
}

MemClass *Narrowing::classOf(Value memref) const {
  auto n = nodeOfValue.find(memref);
  if (n == nodeOfValue.end())
    return nullptr;
  unsigned leader = unionFind.getLeaderValue(n->second);
  auto c = classOfLeader.find(leader);
  if (c == classOfLeader.end())
    return nullptr;
  return const_cast<MemClass *>(&classes[c->second]);
}

std::string Narrowing::nameOf(Value memref) const {
  MemClass *c = classOf(memref);
  if (c)
    for (Operation *root : c->roots) {
      if (auto vn = root->getAttrOfType<StringAttr>("polygeist.varname"))
        return vn.getValue().str();
      if (auto g = dyn_cast<memref::GlobalOp>(root))
        return g.getSymName().str();
    }
  if (auto arg = dyn_cast<BlockArgument>(memref))
    if (auto f = dyn_cast<func::FuncOp>(arg.getOwner()->getParentOp()))
      return "argument " + std::to_string(arg.getArgNumber()) + " of @" +
             f.getSymName().str();
  return "<memref>";
}

//===----------------------------------------------------------------------===//
// Stored ranges.
//===----------------------------------------------------------------------===//

std::optional<std::pair<int64_t, int64_t>>
Narrowing::affineRange(AffineExpr e, ValueRange dims, ValueRange syms) {
  using Range = std::pair<int64_t, int64_t>;
  auto ofValue = [&](Value v) -> std::optional<Range> {
    IntegerValueRange r = rangeOf(v);
    if (r.isUninitialized())
      return std::nullopt;
    const ConstantIntRanges &c = r.getValue();
    if (c.smin().getSignificantBits() > 62 || c.smax().getSignificantBits() > 62)
      return std::nullopt;
    return Range{c.smin().getSExtValue(), c.smax().getSExtValue()};
  };
  if (auto c = dyn_cast<AffineConstantExpr>(e))
    return Range{c.getValue(), c.getValue()};
  if (auto d = dyn_cast<AffineDimExpr>(e))
    return ofValue(dims[d.getPosition()]);
  if (auto s = dyn_cast<AffineSymbolExpr>(e))
    return ofValue(syms[s.getPosition()]);
  auto bin = dyn_cast<AffineBinaryOpExpr>(e);
  if (!bin)
    return std::nullopt;
  std::optional<Range> l = affineRange(bin.getLHS(), dims, syms);
  std::optional<Range> r = affineRange(bin.getRHS(), dims, syms);
  if (!l || !r)
    return std::nullopt;
  constexpr int64_t kLimit = int64_t(1) << 60;
  auto bounded = [&](Range x) -> std::optional<Range> {
    if (x.first < -kLimit || x.second > kLimit)
      return std::nullopt;
    return x;
  };
  switch (e.getKind()) {
  case AffineExprKind::Add:
    return bounded({l->first + r->first, l->second + r->second});
  case AffineExprKind::Mul: {
    if (std::abs(l->first) > (1 << 30) || std::abs(l->second) > (1 << 30) ||
        std::abs(r->first) > (1 << 30) || std::abs(r->second) > (1 << 30))
      return std::nullopt;
    int64_t p[] = {l->first * r->first, l->first * r->second,
                   l->second * r->first, l->second * r->second};
    return Range{*std::min_element(p, p + 4), *std::max_element(p, p + 4)};
  }
  case AffineExprKind::FloorDiv:
  case AffineExprKind::CeilDiv: {
    if (r->first != r->second || r->first <= 0)
      return std::nullopt;
    int64_t c = r->first;
    bool ceil = e.getKind() == AffineExprKind::CeilDiv;
    auto div = [&](int64_t x) {
      return ceil ? llvm::divideCeilSigned(x, c) : llvm::divideFloorSigned(x, c);
    };
    return Range{div(l->first), div(l->second)};
  }
  case AffineExprKind::Mod: {
    if (r->first != r->second || r->first <= 0)
      return std::nullopt;
    if (l->first >= 0 && l->second < r->first)
      return *l;
    return Range{0, r->first - 1};
  }
  default:
    return std::nullopt;
  }
}

IntegerValueRange Narrowing::blockArgRange(BlockArgument arg) {
  Operation *owner = arg.getOwner()->getParentOp();
  auto fromBounds = [&](std::optional<int64_t> lo,
                        std::optional<int64_t> hiExclusive, int64_t step) {
    if (!lo || !hiExclusive || step <= 0)
      return IntegerValueRange::getMaxRange(arg);
    if (*hiExclusive <= *lo)
      return IntegerValueRange(); // the loop never runs
    int64_t last = *lo + ((*hiExclusive - 1 - *lo) / step) * step;
    unsigned w = bitWidthOf(arg.getType());
    return IntegerValueRange(ConstantIntRanges::fromSigned(
        APInt(w, *lo, /*isSigned=*/true), APInt(w, last, /*isSigned=*/true)));
  };
  // N159: an accumulation's iter_arg has the range updateAccumulations
  // found in the previous round (uninitialised until then).
  if (isa<affine::AffineForOp, scf::ForOp>(owner) &&
      arg.getArgNumber() > 0 && accumulationOf(arg)) {
    auto it = accumulationRange.find(arg);
    return it == accumulationRange.end() ? IntegerValueRange() : it->second;
  }
  if (auto f = dyn_cast<affine::AffineForOp>(owner)) {
    if (arg != f.getInductionVar())
      return IntegerValueRange::getMaxRange(arg); // an iter_arg: recurrence
    std::optional<int64_t> lo, hi;
    AffineMap lbMap = f.getLowerBoundMap(), ubMap = f.getUpperBoundMap();
    auto lbOps = f.getLowerBoundOperands(), ubOps = f.getUpperBoundOperands();
    // A max of several lower bounds: at least the largest minimum; a min of
    // upper bounds: at most the smallest maximum.
    for (AffineExpr e : lbMap.getResults()) {
      auto r = affineRange(e, ValueRange(lbOps).take_front(lbMap.getNumDims()),
                           ValueRange(lbOps).drop_front(lbMap.getNumDims()));
      if (!r)
        continue;
      lo = lo ? std::max(*lo, r->first) : r->first;
    }
    for (AffineExpr e : ubMap.getResults()) {
      auto r = affineRange(e, ValueRange(ubOps).take_front(ubMap.getNumDims()),
                           ValueRange(ubOps).drop_front(ubMap.getNumDims()));
      if (!r) {
        hi.reset();
        break;
      }
      hi = hi ? std::min(*hi, r->second) : r->second;
    }
    if (lbMap.getNumResults() == 0)
      lo.reset();
    // The IV is at most the largest upper bound value minus one; step >= 1
    // keeps it at most that.
    if (!lo || !hi)
      return IntegerValueRange::getMaxRange(arg);
    if (*hi <= *lo)
      return IntegerValueRange();
    unsigned w = bitWidthOf(arg.getType());
    return IntegerValueRange(ConstantIntRanges::fromSigned(
        APInt(w, *lo, true), APInt(w, *hi - 1, true)));
  }
  if (auto f = dyn_cast<scf::ForOp>(owner)) {
    if (arg != f.getInductionVar())
      return IntegerValueRange::getMaxRange(arg);
    std::optional<int64_t> step = getConstantIntValue(f.getStep());
    IntegerValueRange lb = rangeOf(f.getLowerBound());
    IntegerValueRange ub = rangeOf(f.getUpperBound());
    if (lb.isUninitialized() || ub.isUninitialized() || !step || *step <= 0)
      return IntegerValueRange::getMaxRange(arg);
    const ConstantIntRanges &l = lb.getValue(), &u = ub.getValue();
    if (l.smin().getSignificantBits() > 62 || u.smax().getSignificantBits() > 62)
      return IntegerValueRange::getMaxRange(arg);
    return fromBounds(l.smin().getSExtValue(), u.smax().getSExtValue(), 1);
  }
  if (auto f = dyn_cast<func::FuncOp>(owner)) {
    if (!isInternalFunction(f) || paramRangePinned.count(arg))
      return IntegerValueRange::getMaxRange(arg);
    auto it = paramRange.find(arg);
    return it == paramRange.end() ? IntegerValueRange() : it->second;
  }
  return IntegerValueRange::getMaxRange(arg);
}

IntegerValueRange Narrowing::rangeOf(Value v) {
  if (!bitWidthOf(v.getType()))
    return IntegerValueRange::getMaxRange(v);
  auto it = ranges.find(v);
  if (it != ranges.end())
    return it->second;
  if (auto arg = dyn_cast<BlockArgument>(v)) {
    IntegerValueRange r = blockArgRange(arg);
    ranges[v] = r;
    return r;
  }
  return IntegerValueRange::getMaxRange(v);
}

/// The range of `use`'s value at the user: its range, narrowed by the
/// condition of every scf.if the user sits in (the else arm of
/// `x < -128 ? -128 : min(x, 127)` sees x >= -128).
IntegerValueRange Narrowing::operandRange(OpOperand &use) {
  Value v = use.get();
  IntegerValueRange r = rangeOf(v);
  if (r.isUninitialized())
    return r;
  ConstantIntRanges cur = r.getValue();
  for (Operation *at = use.getOwner(); at && !isa<func::FuncOp>(at);
       at = at->getParentOp()) {
    auto ifOp = dyn_cast_or_null<scf::IfOp>(at->getParentOp());
    if (!ifOp)
      continue;
    bool inThen = at->getParentRegion() == &ifOp.getThenRegion();
    if (std::optional<ConstantIntRanges> b =
            conditionBound(v, ifOp.getCondition(), inThen)) {
      ConstantIntRanges x = cur.intersection(*b);
      if (x.smin().sle(x.smax()) && x.umin().ule(x.umax()))
        cur = x;
    }
  }
  return IntegerValueRange(cur);
}

/// A compile-time value of `v`: a constant op, or a range of one value.
std::optional<APInt> Narrowing::constantOf(Value v) {
  APInt c;
  if (matchPattern(v, m_ConstantInt(&c)))
    return c;
  auto it = ranges.find(v);
  if (it != ranges.end() && !it->second.isUninitialized() &&
      it->second.getValue().smin() == it->second.getValue().smax())
    return it->second.getValue().smin();
  return std::nullopt;
}

/// [umin, umax] of a value known to be non-negative and below 2^32.
std::optional<std::pair<uint64_t, uint64_t>>
Narrowing::smallUnsignedRange(Value v) {
  std::optional<ConstantIntRanges> r;
  APInt c;
  if (matchPattern(v, m_ConstantInt(&c)))
    r = ConstantIntRanges::constant(c);
  else if (auto it = ranges.find(v);
           it != ranges.end() && !it->second.isUninitialized())
    r = it->second.getValue();
  if (!r || r->smin().isNegative() || r->umax().getActiveBits() > 32)
    return std::nullopt;
  return std::make_pair(r->umin().getZExtValue(), r->umax().getZExtValue());
}

/// Both bounds at once; nullopt when they contradict (no value satisfies
/// both, so the code is dead and the bound is not used).
static std::optional<ConstantIntRanges>
meetBounds(std::optional<ConstantIntRanges> a,
           std::optional<ConstantIntRanges> b) {
  if (!a)
    return b;
  if (!b)
    return a;
  ConstantIntRanges x = a->intersection(*b);
  if (x.smin().sgt(x.smax()) || x.umin().ugt(x.umax()))
    return std::nullopt;
  // The two views describe one set: `x >= 0` (signed) and `x < 300`
  // (signed) leave signed [0, 299], so the unsigned view is [0, 299] too.
  APInt smin = x.smin(), smax = x.smax(), umin = x.umin(), umax = x.umax();
  if (!smin.isNegative()) {
    umin = llvm::APIntOps::umax(umin, smin);
    umax = llvm::APIntOps::umin(umax, smax);
  }
  if (!umax.isNegative()) {
    smin = llvm::APIntOps::smax(smin, umin);
    smax = llvm::APIntOps::smin(smax, umax);
  }
  if (smin.sgt(smax) || umin.ugt(umax))
    return std::nullopt;
  return ConstantIntRanges(umin, umax, smin, smax);
}

/// Either bound: a bound only when both sides give one.
static std::optional<ConstantIntRanges>
joinBounds(std::optional<ConstantIntRanges> a,
           std::optional<ConstantIntRanges> b) {
  if (!a || !b)
    return std::nullopt;
  return a->rangeUnion(*b);
}

/// What `cond` being `holds` says about `v`: a bound when cond compares v (or
/// v sign / zero extended) with a constant, or combines such comparisons with
/// `&&` / `||`. The front end lowers `p && q` to `scf.if p { yield q } else
/// { yield false }` and `p || q` to `scf.if p { yield true } else { yield q }`;
/// an `arith.andi` / `arith.ori` of i1s is the same. When the conjunction
/// holds, both bounds hold (Vitis narrows `x >= 0 && x < 300` to 9 bits);
/// when a disjunction holds, one of them does. nullopt: it says nothing.
std::optional<ConstantIntRanges>
Narrowing::conditionBound(Value v, Value cond, bool holds, unsigned depth) {
  if (depth > kMaxConditionDepth)
    return std::nullopt;
  if (auto cmp = cond.getDefiningOp<arith::CmpIOp>())
    return compareBound(v, cmp, holds);
  auto bound = [&](Value c, bool h) {
    return conditionBound(v, c, h, depth + 1);
  };
  // The bound of `lhs AND rhs` (isAnd) or `lhs OR rhs` being `holds`.
  auto combine = [&](Value lhs, Value rhs, bool isAnd) {
    // a && b holds, or a || b fails: both sides (negated for ||) hold.
    if (isAnd == holds)
      return meetBounds(bound(lhs, holds), bound(rhs, holds));
    return joinBounds(bound(lhs, holds), bound(rhs, holds));
  };
  if (auto a = cond.getDefiningOp<arith::AndIOp>(); a && a.getType().isInteger(1))
    return combine(a.getLhs(), a.getRhs(), /*isAnd=*/true);
  if (auto o = cond.getDefiningOp<arith::OrIOp>(); o && o.getType().isInteger(1))
    return combine(o.getLhs(), o.getRhs(), /*isAnd=*/false);
  auto ifOp = cond.getDefiningOp<scf::IfOp>();
  if (!ifOp || ifOp.getNumResults() != 1 || ifOp.getElseRegion().empty() ||
      !cond.getType().isInteger(1))
    return std::nullopt;
  Value yThen = ifOp.thenYield().getOperand(0);
  Value yElse = ifOp.elseYield().getOperand(0);
  APInt k;
  if (matchPattern(yElse, m_ConstantInt(&k)) && k.isZero())
    return combine(ifOp.getCondition(), yThen, /*isAnd=*/true);
  if (matchPattern(yThen, m_ConstantInt(&k)) && k.isOne())
    return combine(ifOp.getCondition(), yElse, /*isAnd=*/false);
  return std::nullopt;
}

/// What the comparison `cmp` being `holds` says about `v` (see
/// conditionBound).
std::optional<ConstantIntRanges>
Narrowing::compareBound(Value v, arith::CmpIOp cmp, bool holds) {
  using P = arith::CmpIPredicate;
  P pred = cmp.getPredicate();
  Value side = cmp.getLhs();
  std::optional<APInt> c = constantOf(cmp.getRhs());
  if (!c) {
    // constant <pred> side  ==  side <swapped pred> constant
    c = constantOf(cmp.getLhs());
    side = cmp.getRhs();
    if (!c)
      return std::nullopt;
    switch (pred) {
    case P::slt: pred = P::sgt; break;
    case P::sle: pred = P::sge; break;
    case P::sgt: pred = P::slt; break;
    case P::sge: pred = P::sle; break;
    case P::ult: pred = P::ugt; break;
    case P::ule: pred = P::uge; break;
    case P::ugt: pred = P::ult; break;
    case P::uge: pred = P::ule; break;
    default: break;
    }
  }
  if (!holds)
    pred = arith::invertPredicate(pred);
  bool sext = false, zext = false;
  if (side != v) {
    if (auto e = side.getDefiningOp<arith::ExtSIOp>(); e && e.getIn() == v)
      sext = true;
    else if (auto e = side.getDefiningOp<arith::ExtUIOp>(); e && e.getIn() == v)
      zext = true;
    else
      return std::nullopt;
  }
  unsigned wide = c->getBitWidth();
  bool isSigned = pred == P::slt || pred == P::sle || pred == P::sgt ||
                  pred == P::sge;
  APInt lo = isSigned ? APInt::getSignedMinValue(wide) : APInt::getZero(wide);
  APInt hi = isSigned ? APInt::getSignedMaxValue(wide)
                      : APInt::getMaxValue(wide);
  switch (pred) {
  case P::eq: lo = hi = *c; break;
  case P::slt: if (c->isMinSignedValue()) return std::nullopt; hi = *c - 1; break;
  case P::sle: hi = *c; break;
  case P::sgt: if (c->isMaxSignedValue()) return std::nullopt; lo = *c + 1; break;
  case P::sge: lo = *c; break;
  case P::ult: if (c->isZero()) return std::nullopt; hi = *c - 1; break;
  case P::ule: hi = *c; break;
  case P::ugt: if (c->isMaxValue()) return std::nullopt; lo = *c + 1; break;
  case P::uge: lo = *c; break;
  default: return std::nullopt;
  }
  unsigned w = bitWidthOf(v.getType());
  if (!sext && !zext)
    return isSigned || pred == P::eq ? ConstantIntRanges::fromSigned(lo, hi)
                                     : ConstantIntRanges::fromUnsigned(lo, hi);
  // Bring the bound to v's width: clamp to the image of the extension, then
  // truncate.
  if (pred == P::eq)
    isSigned = sext;
  if (sext && isSigned) {
    APInt mn = APInt::getSignedMinValue(w).sext(wide);
    APInt mx = APInt::getSignedMaxValue(w).sext(wide);
    if (lo.slt(mn)) lo = mn;
    if (hi.sgt(mx)) hi = mx;
    if (lo.sgt(hi))
      return std::nullopt;
    return ConstantIntRanges::fromSigned(lo.trunc(w), hi.trunc(w));
  }
  if (zext && !isSigned) {
    APInt mx = APInt::getMaxValue(w).zext(wide);
    if (hi.ugt(mx)) hi = mx;
    if (lo.ugt(hi))
      return std::nullopt;
    return ConstantIntRanges::fromUnsigned(lo.trunc(w), hi.trunc(w));
  }
  // A signed comparison of a zero-extended value (`(int)x > 100 ? 100 : x`
  // with x an unsigned char, the clamp of W9 round 21 review D8, kernel
  // w9r21rev_r1c_iterinit: Vitis 11 bits): the value lies in [0, 2^w - 1],
  // non-negative in the wider type.
  if (zext && isSigned && w < wide) {
    APInt mx = APInt::getMaxValue(w).zext(wide);
    APInt zero = APInt::getZero(wide);
    if (lo.slt(zero)) lo = zero;
    if (hi.sgt(mx)) hi = mx;
    if (lo.sgt(hi))
      return std::nullopt;
    return ConstantIntRanges::fromUnsigned(lo.trunc(w), hi.trunc(w));
  }
  return std::nullopt;
}

/// Whether `v` is an undefined value (tool.hls.narrowing.
/// undef_contributes_nothing): it adds nothing to a select's or an if's range.
bool Narrowing::isUndefined(Value v) const {
  if (!undefContributesNothing)
    return false;
  Operation *def = v.getDefiningOp();
  return def && isa<LLVM::UndefOp, LLVM::PoisonOp>(def);
}

/// Whether every subscript of the access `op` is the constant 0.
static bool accessesElementZero(Operation *op) {
  if (auto ld = dyn_cast<memref::LoadOp>(op))
    return llvm::all_of(ld.getIndices(),
                        [](Value i) { return matchPattern(i, m_Zero()); });
  if (auto st = dyn_cast<memref::StoreOp>(op))
    return llvm::all_of(st.getIndices(),
                        [](Value i) { return matchPattern(i, m_Zero()); });
  AffineMap map;
  ValueRange operands;
  if (auto rd = dyn_cast<affine::AffineReadOpInterface>(op)) {
    map = rd.getAffineMap();
    operands = rd.getMapOperands();
  } else if (auto wr = dyn_cast<affine::AffineWriteOpInterface>(op)) {
    map = wr.getAffineMap();
    operands = wr.getMapOperands();
  } else {
    return false;
  }
  for (AffineExpr e : map.getResults()) {
    auto c = dyn_cast<AffineConstantExpr>(e);
    if (!c || c.getValue() != 0)
      return false;
  }
  return true;
}

/// Whether `store` writes through a scalar reference parameter of a function
/// that is called (a kept callee; the top function has no call site): a
/// memref parameter whose every use in the callee is a load or store of
/// element 0 (`int &seen`, a struct member by reference). A parameter that
/// is a whole array (`int seen[128]`, indexed) does not count (kernel
/// w9r21fx_x2_plainarr: narrowed to 1 bit in Vitis).
bool Narrowing::writesCalleeParameter(Operation *store) const {
  std::optional<Access> acc = asAccess(store);
  if (!acc || !acc->stored || acc->memref.getDefiningOp())
    return false;
  auto arg = dyn_cast<BlockArgument>(acc->memref);
  if (!arg || !arg.getOwner()->isEntryBlock())
    return false;
  auto f = dyn_cast<func::FuncOp>(arg.getOwner()->getParentOp());
  if (!f || !callSites.count(f) || callSites.lookup(f).empty())
    return false;
  return llvm::all_of(arg.getUsers(), [&](Operation *user) {
    std::optional<Access> a = asAccess(user);
    return a && a->memref == arg && accessesElementZero(user);
  });
}

/// The memory a memref or pointer value is a view of: through casts, views,
/// cgeist's memref2pointer / pointer2memref and getelementptr.
Value Narrowing::rootOf(Value v) const {
  for (unsigned i = 0; i < 64; ++i) {
    Operation *def = v.getDefiningOp();
    if (!def)
      return v;
    if (isa<Memref2PointerOp, Pointer2MemrefOp, LLVM::GEPOp>(def)) {
      v = def->getOperand(0);
      continue;
    }
    if (auto view = dyn_cast<ViewLikeOpInterface>(def)) {
      v = view.getViewSource();
      continue;
    }
    return v;
  }
  return v;
}

/// Whether `callee` may write through its memref / pointer parameter `arg`:
/// a store through it or anything derived from it, or a call it is passed to
/// that may (an external callee may).
bool Narrowing::calleeMayWrite(func::FuncOp callee, unsigned arg,
                               unsigned depth) {
  if (!callee || callee.isExternal() || arg >= callee.getNumArguments() ||
      depth > 8)
    return true;
  auto key = std::make_pair(callee.getOperation(), arg);
  if (auto it = calleeWrites.find(key); it != calleeWrites.end())
    return it->second;
  calleeWrites[key] = true; // a recursive cycle: assume it writes
  bool writes = false;
  SmallVector<Value> work{callee.getArgument(arg)};
  DenseSet<Value> seen{callee.getArgument(arg)};
  while (!work.empty() && !writes) {
    Value v = work.pop_back_val();
    for (OpOperand &use : v.getUses()) {
      Operation *user = use.getOwner();
      if (isa<Memref2PointerOp, Pointer2MemrefOp, LLVM::GEPOp,
              ViewLikeOpInterface>(user)) {
        for (Value r : user->getResults())
          if (seen.insert(r).second)
            work.push_back(r);
        continue;
      }
      if (auto call = dyn_cast<func::CallOp>(user)) {
        func::FuncOp inner = symbols.lookup<func::FuncOp>(call.getCallee());
        if (calleeMayWrite(inner, use.getOperandNumber(), depth + 1))
          writes = true;
        continue;
      }
      if (isa<LLVM::LoadOp, memref::LoadOp, affine::AffineLoadOp>(user))
        continue;
      if (auto eff = dyn_cast<MemoryEffectOpInterface>(user)) {
        SmallVector<MemoryEffects::EffectInstance> effects;
        eff.getEffects(effects);
        for (auto &e : effects)
          if (isa<MemoryEffects::Write>(e.getEffect()))
            writes = true;
        continue;
      }
      if (!isMemoryEffectFree(user))
        writes = true;
    }
  }
  calleeWrites[key] = writes;
  return writes;
}

/// The (root, byte offset) a pointer addresses when every getelementptr on
/// the way has compile-time indices over a scalar element type.
std::optional<std::pair<Value, int64_t>>
Narrowing::pointerLocation(Value ptr) {
  int64_t offset = 0;
  for (unsigned i = 0; i < 64; ++i) {
    Operation *def = ptr.getDefiningOp();
    if (auto gep = dyn_cast_or_null<LLVM::GEPOp>(def)) {
      Type elt = gep.getElemType();
      std::optional<int64_t> bits = llvmStorageBits(elt);
      if (!bits || *bits % 8 || gep.getIndices().size() != 1 ||
          !elt.isIntOrFloat())
        return std::nullopt;
      auto idx = gep.getIndices()[0];
      int64_t k = 0;
      if (auto attr = llvm::dyn_cast_if_present<IntegerAttr>(idx)) {
        k = attr.getInt();
      } else if (Value dyn = llvm::dyn_cast_if_present<Value>(idx)) {
        std::optional<APInt> c = constantOf(dyn);
        if (!c || c->getSignificantBits() > 32)
          return std::nullopt;
        k = c->getSExtValue();
      } else {
        return std::nullopt;
      }
      offset += k * (*bits / 8);
      ptr = gep.getBase();
      continue;
    }
    if (isa_and_nonnull<Memref2PointerOp>(def))
      return std::make_pair(rootOf(ptr), offset);
    return std::nullopt;
  }
  return std::nullopt;
}

const SmallVector<Operation *, 2> &
Narrowing::reachingStoreExact(Operation *load) {
  auto it = reachingStoresExact.find(load);
  if (it == reachingStoresExact.end())
    it = reachingStoresExact
             .try_emplace(load, findReachingStore(load, /*exactOnly=*/true))
             .first;
  return it->second;
}

/// The roots of every memory `op` (a region op) may write, through stores,
/// calls it passes them to and declared write effects; `unknown` when an op
/// inside may write without saying what.
const Narrowing::RegionWrites &Narrowing::regionWrites(Operation *op) {
  std::unique_ptr<RegionWrites> &slot = regionWriteCache[op];
  if (slot)
    return *slot;
  auto rw = std::make_unique<RegionWrites>();
  op->walk([&](Operation *inner) {
    if (inner == op || rw->unknown)
      return;
    if (auto st = dyn_cast<LLVM::StoreOp>(inner)) {
      rw->roots.insert(rootOf(st.getAddr()));
      return;
    }
    if (std::optional<Access> acc = asAccess(inner)) {
      if (acc->stored)
        rw->roots.insert(rootOf(acc->memref));
      return;
    }
    if (isa<CallOpInterface>(inner)) {
      for (Value o : inner->getOperands())
        if (isa<BaseMemRefType, LLVM::LLVMPointerType>(o.getType()))
          rw->roots.insert(rootOf(o));
      return;
    }
    if (inner->getNumRegions())
      return; // its ops are visited by the walk
    if (auto eff = dyn_cast<MemoryEffectOpInterface>(inner)) {
      SmallVector<MemoryEffects::EffectInstance> effects;
      eff.getEffects(effects);
      for (auto &e : effects)
        if (isa<MemoryEffects::Write>(e.getEffect())) {
          if (e.getValue())
            rw->roots.insert(rootOf(e.getValue()));
          else
            rw->unknown = true;
        }
      return;
    }
    if (!inner->hasTrait<OpTrait::HasRecursiveMemoryEffects>() &&
        !isMemoryEffectFree(inner))
      rw->unknown = true;
  });
  slot = std::move(rw);
  return *slot;
}

/// The writers of each root among the ops of `block` (an op is listed under
/// every root it may write; region ops through regionWrites).
const Narrowing::BlockWriters &Narrowing::blockWriters(Block *block) {
  std::unique_ptr<BlockWriters> &slot = blockWriterCache[block];
  if (slot)
    return *slot;
  auto bw = std::make_unique<BlockWriters>();
  for (Operation &op : *block) {
    DenseSet<Value> roots;
    bool unknown = false;
    if (auto st = dyn_cast<LLVM::StoreOp>(op)) {
      roots.insert(rootOf(st.getAddr()));
    } else if (std::optional<Access> acc = asAccess(&op)) {
      if (acc->stored)
        roots.insert(rootOf(acc->memref));
    } else if (isa<CallOpInterface>(op)) {
      for (Value o : op.getOperands())
        if (isa<BaseMemRefType, LLVM::LLVMPointerType>(o.getType()))
          roots.insert(rootOf(o));
    } else if (op.getNumRegions()) {
      const RegionWrites &rw = regionWrites(&op);
      roots.insert(rw.roots.begin(), rw.roots.end());
      unknown = rw.unknown;
    } else if (auto eff = dyn_cast<MemoryEffectOpInterface>(op)) {
      SmallVector<MemoryEffects::EffectInstance> effects;
      eff.getEffects(effects);
      for (auto &e : effects)
        if (isa<MemoryEffects::Write>(e.getEffect())) {
          if (e.getValue())
            roots.insert(rootOf(e.getValue()));
          else
            unknown = true;
        }
    } else if (!op.hasTrait<OpTrait::HasRecursiveMemoryEffects>() &&
               !isMemoryEffectFree(&op)) {
      unknown = true;
    }
    if (unknown)
      bw->unknown.push_back(&op);
    else
      for (Value r : roots)
        bw->byRoot[r].push_back(&op);
  }
  slot = std::move(bw);
  return *slot;
}

const SmallVector<Operation *, 2> &Narrowing::reachingStore(Operation *load) {
  auto it = reachingStores.find(load);
  if (it == reachingStores.end())
    it = reachingStores.try_emplace(load, findReachingStore(load)).first;
  return it->second;
}

/// tool.hls.narrowing.reaching_store_ranges (VITIS_NOTES N151 (c)): the store
/// earlier in `load`'s block that writes exactly the element it reads, with
/// nothing in between that may write it, or the stores of both arms of an if
/// in between (one per arm; an arm without one takes the store before the
/// if); empty when there is none (the load then has its array's range). Only
/// for loads of a struct field through cgeist's pointer (constant
/// getelementptr offsets) and of a completely partitioned memref at constant
/// subscripts.
SmallVector<Operation *, 2> Narrowing::findReachingStore(Operation *load,
                                                         bool exactOnly,
                                                         Operation *from) {
  Value root;
  // The exact address of a memref access: a store with the same memref and
  // the same subscript operands (and map) writes the same element whatever
  // the array's partitioning (plain store-to-load forwarding;
  // tool.hls.narrowing.accumulation_ranges, N159: `acc[i] = 0` then the
  // accumulation loop's first load of acc[i]).
  Value loadMem;
  AffineMap loadMap;
  SmallVector<Value> loadOperands;
  auto addressOf = [](Operation *op, Value &mem, AffineMap &map,
                      SmallVectorImpl<Value> &operands) {
    if (auto ld = dyn_cast<memref::LoadOp>(op)) {
      mem = ld.getMemRef();
      operands.assign(ld.getIndices().begin(), ld.getIndices().end());
    } else if (auto st = dyn_cast<memref::StoreOp>(op)) {
      mem = st.getMemRef();
      operands.assign(st.getIndices().begin(), st.getIndices().end());
    } else if (auto ld = dyn_cast<affine::AffineLoadOp>(op)) {
      mem = ld.getMemRef();
      map = ld.getAffineMap();
      operands.assign(ld.getMapOperands().begin(), ld.getMapOperands().end());
    } else if (auto st = dyn_cast<affine::AffineStoreOp>(op)) {
      mem = st.getMemRef();
      map = st.getAffineMap();
      operands.assign(st.getMapOperands().begin(), st.getMapOperands().end());
    } else {
      return false;
    }
    return true;
  };
  bool exactAddress = accumulationRanges &&
                      addressOf(load, loadMem, loadMap, loadOperands);
  std::optional<int64_t> offset;
  SmallVector<int64_t> subscripts;
  unsigned loadBits = bitWidthOf(load->getResult(0).getType());
  auto constantSubscripts = [&](Operation *op,
                                SmallVectorImpl<int64_t> &out) -> bool {
    SmallVector<Value> idx;
    if (auto ld = dyn_cast<memref::LoadOp>(op))
      idx.assign(ld.getIndices().begin(), ld.getIndices().end());
    else if (auto st = dyn_cast<memref::StoreOp>(op))
      idx.assign(st.getIndices().begin(), st.getIndices().end());
    else if (isa<affine::AffineLoadOp, affine::AffineStoreOp>(op)) {
      AffineMap map;
      SmallVector<Value> operands;
      if (auto ld = dyn_cast<affine::AffineLoadOp>(op)) {
        map = ld.getAffineMap();
        operands.assign(ld.getMapOperands().begin(),
                        ld.getMapOperands().end());
      } else {
        auto st = cast<affine::AffineStoreOp>(op);
        map = st.getAffineMap();
        operands.assign(st.getMapOperands().begin(),
                        st.getMapOperands().end());
      }
      ValueRange all(operands);
      for (AffineExpr e : map.getResults()) {
        auto r = affineRange(e, all.take_front(map.getNumDims()),
                             all.drop_front(map.getNumDims()));
        if (!r || r->first != r->second)
          return false;
        out.push_back(r->first);
      }
      return true;
    } else
      return false;
    for (Value v : idx) {
      std::optional<APInt> c = constantOf(v);
      if (!c || c->getSignificantBits() > 62)
        return false;
      out.push_back(c->getSExtValue());
    }
    return true;
  };
  if (auto ld = dyn_cast<LLVM::LoadOp>(load)) {
    auto loc = pointerLocation(ld.getAddr());
    if (!loc)
      return {};
    root = loc->first;
    offset = loc->second;
  } else if (std::optional<Access> acc = asAccess(load)) {
    root = rootOf(acc->memref);
    std::optional<SmallVector<bool>> complete =
        exactOnly ? std::nullopt : completeDims(acc->memref);
    // Every dimension is split into registers: completely partitioned, or
    // of extent 1 (the leading dimension cgeist gives a struct member).
    auto type = dyn_cast<MemRefType>(acc->memref.getType());
    bool registers =
        complete && type &&
        llvm::all_of(llvm::enumerate(*complete), [&](auto dim) {
          return dim.value() || type.getDimSize(dim.index()) == 1;
        });
    bool constantElement = registers && constantSubscripts(load, subscripts);
    if (!constantElement) {
      subscripts.clear();
      if (!exactAddress)
        return {};
    }
  } else {
    return {};
  }
  // What `op` does to the element.
  enum class Effect { None, Clobber, Reaches };
  std::function<Effect(Operation *)> effectOf = [&](Operation *op) -> Effect {
    if (auto st = dyn_cast<LLVM::StoreOp>(op)) {
      if (rootOf(st.getAddr()) != root)
        return Effect::None;
      auto loc = pointerLocation(st.getAddr());
      std::optional<int64_t> bits = llvmStorageBits(st.getValue().getType());
      if (!offset || !loc || !bits || *bits % 8)
        return Effect::Clobber;
      int64_t lo = loc->second, hi = lo + *bits / 8;
      int64_t mlo = *offset, mhi = mlo + loadBits / 8;
      if (hi <= mlo || mhi <= lo)
        return Effect::None;
      if (lo == mlo && hi == mhi && st.getValue().getType().isInteger() &&
          bitWidthOf(st.getValue().getType()) == loadBits)
        return Effect::Reaches;
      return Effect::Clobber;
    }
    if (std::optional<Access> acc = asAccess(op)) {
      if (!acc->stored || rootOf(acc->memref) != root)
        return Effect::None;
      if (exactAddress && !offset && !isa<StoreEnableOp>(op)) {
        Value mem;
        AffineMap map;
        SmallVector<Value> operands;
        if (addressOf(op, mem, map, operands) && mem == loadMem &&
            map == loadMap && operands == loadOperands)
          return bitWidthOf(acc->stored.getType()) == loadBits
                     ? Effect::Reaches
                     : Effect::Clobber;
      }
      SmallVector<int64_t> sub;
      if (offset || subscripts.empty() || !constantSubscripts(op, sub) ||
          isa<StoreEnableOp>(op))
        return Effect::Clobber;
      if (sub != subscripts)
        return Effect::None;
      return bitWidthOf(acc->stored.getType()) == loadBits ? Effect::Reaches
                                                           : Effect::Clobber;
    }
    if (isa<CallOpInterface>(op)) {
      auto call = dyn_cast<func::CallOp>(op);
      func::FuncOp callee =
          call ? symbols.lookup<func::FuncOp>(call.getCallee()) : nullptr;
      for (OpOperand &o : op->getOpOperands())
        if (isa<BaseMemRefType, LLVM::LLVMPointerType>(o.get().getType()) &&
            rootOf(o.get()) == root &&
            calleeMayWrite(callee, o.getOperandNumber()))
          return Effect::Clobber;
      return Effect::None;
    }
    if (op->getNumRegions()) {
      // Most region ops (unrolled loops, ifs) write other arrays: a cached
      // summary answers them without a walk.
      const RegionWrites &rw = regionWrites(op);
      if (!rw.unknown && !rw.roots.contains(root))
        return Effect::None;
      bool clobber = false;
      op->walk([&](Operation *inner) {
        if (inner != op && effectOf(inner) != Effect::None)
          clobber = true;
      });
      return clobber ? Effect::Clobber : Effect::None;
    }
    if (auto eff = dyn_cast<MemoryEffectOpInterface>(op)) {
      SmallVector<MemoryEffects::EffectInstance> effects;
      eff.getEffects(effects);
      for (auto &e : effects)
        if (isa<MemoryEffects::Write>(e.getEffect()) &&
            (!e.getValue() || rootOf(e.getValue()) == root))
          return Effect::Clobber;
      return Effect::None;
    }
    return op->hasTrait<OpTrait::HasRecursiveMemoryEffects>() ||
                   isMemoryEffectFree(op)
               ? Effect::None
               : Effect::Clobber;
  };
  // Search backwards from `from` (exclusive) in its block: the stores that
  // reach (Found), nothing that writes the element (NotFound), or something
  // that may write it otherwise (Clobber).
  enum class Search { Found, NotFound, Clobber };
  SmallVector<Operation *, 2> found;
  std::function<Search(Operation *, Block *)> search =
      [&](Operation *from, Block *block) -> Search {
    // Only the ops of the block that may write the root (blockWriters)
    // can be anything but Effect::None: visit those, latest first.
    const BlockWriters &bw = blockWriters(block);
    ArrayRef<Operation *> byRoot, unknown = bw.unknown;
    if (auto it = bw.byRoot.find(root); it != bw.byRoot.end())
      byRoot = it->second;
    auto beforeFrom = [&](ArrayRef<Operation *> ops) {
      if (!from)
        return ops;
      return ops.take_front(llvm::partition_point(
                                ops, [&](Operation *o) {
                                  return o->isBeforeInBlock(from);
                                }) -
                            ops.begin());
    };
    byRoot = beforeFrom(byRoot);
    unknown = beforeFrom(unknown);
    while (!byRoot.empty() || !unknown.empty()) {
      Operation *op;
      if (unknown.empty() ||
          (!byRoot.empty() && unknown.back()->isBeforeInBlock(byRoot.back()))) {
        op = byRoot.back();
        byRoot = byRoot.drop_back();
      } else {
        op = unknown.back();
        unknown = unknown.drop_back();
      }
      bool isIf = isa<scf::IfOp, affine::AffineIfOp>(op) &&
                  op->getNumRegions() == 2 && !op->getRegion(1).empty();
      if (isIf) {
        Search arms[2];
        for (unsigned r = 0; r < 2; ++r) {
          Block &armBlock = op->getRegion(r).front();
          arms[r] = search(armBlock.getTerminator(), &armBlock);
          if (arms[r] == Search::Clobber)
            return Search::Clobber;
        }
        if (arms[0] == Search::Found && arms[1] == Search::Found)
          return Search::Found;
        if (arms[0] == Search::NotFound && arms[1] == Search::NotFound)
          continue;
        // One arm writes the element: the other one keeps the value from
        // before the if.
        return search(op, block) == Search::Found ? Search::Found
                                                  : Search::Clobber;
      }
      switch (effectOf(op)) {
      case Effect::None:
        continue;
      case Effect::Reaches:
        found.push_back(op);
        return Search::Found;
      case Effect::Clobber:
        return Search::Clobber;
      }
    }
    return Search::NotFound;
  };
  // `from`: search before that op (an enclosing loop) instead of the load.
  Operation *start = from ? from : load;
  if (search(start, start->getBlock()) != Search::Found)
    return {};
  return found;
}

/// The trip count of an affine.for / scf.for with constant bounds (1 ..
/// 2^30), else nullopt.
static std::optional<int64_t> constantTripCount(Operation *loop) {
  std::optional<int64_t> trips;
  if (auto f = dyn_cast<affine::AffineForOp>(loop)) {
    if (std::optional<uint64_t> t = affine::getConstantTripCount(f))
      trips = static_cast<int64_t>(*t);
  } else if (auto f = dyn_cast<scf::ForOp>(loop)) {
    std::optional<int64_t> lb = getConstantIntValue(f.getLowerBound());
    std::optional<int64_t> ub = getConstantIntValue(f.getUpperBound());
    std::optional<int64_t> st = getConstantIntValue(f.getStep());
    if (lb && ub && st && *st > 0)
      trips = *ub > *lb ? (*ub - *lb + *st - 1) / *st : 0;
  }
  if (!trips || *trips <= 0 || *trips > (int64_t(1) << 30))
    return std::nullopt;
  return trips;
}

/// [init.min + n * min(step.min, 0), init.max + n * max(step.max, 0)] in the
/// type of `like`; its full range when that does not fit.
static IntegerValueRange accumulatedRange(const ConstantIntRanges &init,
                                          const APInt &stepLo,
                                          const APInt &stepHi, int64_t n,
                                          Value like) {
  unsigned w = bitWidthOf(like.getType());
  APInt t(128, n), l = init.smin().sext(128), h = init.smax().sext(128);
  if (stepLo.isNegative())
    l += t * stepLo;
  if (stepHi.isStrictlyPositive())
    h += t * stepHi;
  if (l.getSignificantBits() > w || h.getSignificantBits() > w)
    return IntegerValueRange::getMaxRange(like);
  return IntegerValueRange(
      ConstantIntRanges::fromSigned(l.trunc(w), h.trunc(w)));
}

/// The memory form of N159 (tool.hls.narrowing.accumulation_ranges): `load`
/// reads a[x] in the body of a loop of T trips whose only write to a is
/// `a[x] = load + s1 + ...` later in the same block (x the same subscripts,
/// defined outside the loop; the addends not computed from the load), and
/// `a[x] = init` reaches the loop: the load ranges over init + (T - 1) x
/// the step, the store over init + T x the step (kernels w9r21p_j1_accT8 /
/// j2_accT64; Analog-CIM optimized output_buf).
const std::optional<Narrowing::MemAccumulation> &
Narrowing::memAccumulationOf(Operation *load) {
  auto it = memAccumulations.find(load);
  if (it != memAccumulations.end())
    return it->second;
  std::optional<MemAccumulation> out;
  auto record = [&]() -> const std::optional<MemAccumulation> & {
    if (out)
      memAccumulationLoadOf[out->store] = load;
    return memAccumulations[load] = out;
  };
  if (!accumulationRanges || load->getNumResults() != 1 ||
      !bitWidthOf(load->getResult(0).getType()) ||
      !isa<affine::AffineLoadOp, memref::LoadOp>(load))
    return record();
  Operation *loop = load->getParentOp();
  if (!loop || !isa<affine::AffineForOp, scf::ForOp>(loop))
    return record();
  std::optional<int64_t> trips = constantTripCount(loop);
  if (!trips)
    return record();
  auto addressOf = [](Operation *op, Value &mem, AffineMap &map,
                      SmallVectorImpl<Value> &operands) {
    if (auto ld = dyn_cast<memref::LoadOp>(op)) {
      mem = ld.getMemRef();
      operands.assign(ld.getIndices().begin(), ld.getIndices().end());
    } else if (auto st = dyn_cast<memref::StoreOp>(op)) {
      mem = st.getMemRef();
      operands.assign(st.getIndices().begin(), st.getIndices().end());
    } else if (auto ld = dyn_cast<affine::AffineLoadOp>(op)) {
      mem = ld.getMemRef();
      map = ld.getAffineMap();
      operands.assign(ld.getMapOperands().begin(), ld.getMapOperands().end());
    } else if (auto st = dyn_cast<affine::AffineStoreOp>(op)) {
      mem = st.getMemRef();
      map = st.getAffineMap();
      operands.assign(st.getMapOperands().begin(), st.getMapOperands().end());
    } else {
      return false;
    }
    return true;
  };
  Value mem;
  AffineMap map;
  SmallVector<Value> operands;
  addressOf(load, mem, map, operands);
  Region &body = loop->getRegion(0);
  if (llvm::any_of(operands, [&](Value v) {
        return body.isAncestor(v.getParentRegion());
      }))
    return record();
  // The loop's writes to the array: one store of the same address.
  Value root = rootOf(mem);
  Operation *store = nullptr;
  bool other = false;
  loop->walk([&](Operation *op) {
    if (std::optional<Access> acc = asAccess(op)) {
      if (acc->stored && rootOf(acc->memref) == root) {
        Value m;
        AffineMap mp;
        SmallVector<Value> ops;
        if (store || isa<StoreEnableOp>(op) || !addressOf(op, m, mp, ops) ||
            m != mem || mp != map || ops != operands)
          other = true;
        else
          store = op;
      }
      return;
    }
    if (isa<CallOpInterface>(op))
      for (Value o : op->getOperands())
        if (isa<BaseMemRefType, LLVM::LLVMPointerType>(o.getType()) &&
            rootOf(o) == root)
          other = true;
  });
  if (other || !store || store->getBlock() != load->getBlock() ||
      !load->isBeforeInBlock(store))
    return record();
  // The stored value as the load plus addends not computed from it.
  Value word = load->getResult(0);
  DenseSet<Value> derived{word};
  for (Operation *op = load->getNextNode(); op && op != store;
       op = op->getNextNode()) {
    bool uses = false;
    op->walk([&](Operation *inner) {
      for (Value v : inner->getOperands())
        uses |= derived.contains(v);
    });
    if (uses)
      for (Value r : op->getResults())
        derived.insert(r);
  }
  MemAccumulation acc;
  Value cur = store->getOperand(0);
  for (unsigned steps = 0; cur != word; ++steps) {
    auto add = cur.getDefiningOp<arith::AddIOp>();
    if (!add || add->getBlock() != load->getBlock() || steps > 4096)
      return record();
    Value a = add.getLhs(), b = add.getRhs();
    if (derived.contains(b)) {
      if (derived.contains(a))
        return record();
      std::swap(a, b);
    }
    if (derived.contains(b))
      return record();
    acc.steps.push_back(b);
    cur = a;
  }
  if (acc.steps.empty())
    return record();
  acc.inits = findReachingStore(load, /*exactOnly=*/true, /*from=*/loop);
  if (acc.inits.empty() ||
      llvm::any_of(acc.inits, [](Operation *st) {
        return !isa<affine::AffineStoreOp, memref::StoreOp>(st);
      }))
    return record();
  acc.store = store;
  acc.trips = *trips;
  out = std::move(acc);
  return record();
}

/// tool.hls.narrowing.accumulation_ranges (VITIS_NOTES N159): an iter_arg
/// of a loop with a constant trip count T whose yielded value is the iter_arg
/// plus addends that do not depend on it (`s += x` after register
/// promotion, a chain of unrolled `+=` included) ranges over
/// [init.min + (T - 1) * min(step.min, 0), init.max + (T - 1) *
/// max(step.max, 0)] at the start of an iteration, and the loop's result
/// with T for T - 1; nullopt for any other iter_arg (full range, as
/// before).
const std::optional<Narrowing::Accumulation> &
Narrowing::accumulationOf(BlockArgument arg) {
  auto it = accumulations.find(arg);
  if (it != accumulations.end())
    return it->second;
  std::optional<Accumulation> out;
  auto record = [&]() -> const std::optional<Accumulation> & {
    return accumulations[arg] = out;
  };
  if (!accumulationRanges || !bitWidthOf(arg.getType()))
    return record();
  auto loop = dyn_cast<LoopLikeOpInterface>(arg.getOwner()->getParentOp());
  if (!loop || !isa<affine::AffineForOp, scf::ForOp>(loop.getOperation()))
    return record();
  auto iterArgs = loop.getRegionIterArgs();
  auto found = llvm::find(iterArgs, arg);
  if (found == iterArgs.end())
    return record();
  unsigned k = found - iterArgs.begin();
  std::optional<int64_t> trips = constantTripCount(loop.getOperation());
  if (!trips)
    return record();
  Block *body = arg.getOwner();
  Operation *yield = body->getTerminator();
  if (k >= yield->getNumOperands())
    return record();
  // Everything in the body computed from the iter_arg.
  DenseSet<Value> derived{arg};
  for (Operation &op : body->without_terminator()) {
    bool uses = false;
    op.walk([&](Operation *inner) {
      for (Value v : inner->getOperands())
        uses |= derived.contains(v);
    });
    if (uses)
      for (Value r : op.getResults())
        derived.insert(r);
  }
  // The yielded value as the iter_arg plus independent addends.
  Accumulation acc;
  Value cur = yield->getOperand(k);
  for (unsigned steps = 0; cur != arg; ++steps) {
    auto add = cur.getDefiningOp<arith::AddIOp>();
    if (!add || add->getBlock() != body || steps > 4096)
      return record();
    Value a = add.getLhs(), b = add.getRhs();
    if (derived.contains(b)) {
      if (derived.contains(a))
        return record();
      std::swap(a, b);
    }
    if (derived.contains(b))
      return record();
    acc.steps.push_back(b);
    cur = a;
  }
  if (acc.steps.empty())
    return record();
  acc.init = loop.getInits()[k];
  acc.trips = *trips;
  out = std::move(acc);
  return record();
}

/// Recomputes the ranges of the accumulations a loop's yield closes; the
/// next round's iter_args (and the loop's results) read them.
void Narrowing::updateAccumulations(Operation *yield) {
  auto loop = dyn_cast<LoopLikeOpInterface>(yield->getParentOp());
  if (!loop)
    return;
  for (auto [k, a] : llvm::enumerate(loop.getRegionIterArgs())) {
    const std::optional<Accumulation> &acc = accumulationOf(a);
    if (!acc)
      continue;
    IntegerValueRange init = rangeOf(acc->init);
    if (init.isUninitialized())
      continue;
    APInt stepLo(128, 0), stepHi(128, 0);
    bool known = true;
    for (Value s : acc->steps) {
      IntegerValueRange r = rangeOf(s);
      if (r.isUninitialized()) {
        known = false;
        break;
      }
      stepLo += r.getValue().smin().sext(128);
      stepHi += r.getValue().smax().sext(128);
    }
    if (!known)
      continue;
    auto rangeAfter = [&](int64_t n) {
      return accumulatedRange(init.getValue(), stepLo, stepHi, n, a);
    };
    IntegerValueRange &cur = accumulationRange[a];
    IntegerValueRange joined =
        IntegerValueRange::join(cur, rangeAfter(acc->trips - 1));
    IntegerValueRange &res = accumulationResult[a];
    IntegerValueRange joinedRes =
        IntegerValueRange::join(res, rangeAfter(acc->trips));
    if (joined == cur && joinedRes == res)
      continue;
    if (++accumulationChanges[a] > kWidenAfterRounds) {
      joined = IntegerValueRange::getMaxRange(a);
      joinedRes = IntegerValueRange::getMaxRange(a);
    }
    cur = joined;
    res = joinedRes;
    rangesChanged = true;
  }
}

void Narrowing::forwardOp(Operation *op) {
  auto setMax = [&]() {
    for (Value r : op->getResults())
      if (bitWidthOf(r.getType()))
        ranges[r] = IntegerValueRange::getMaxRange(r);
  };
  // N159: a loop's accumulations (their iter_args read accumulationRange
  // through blockArgRange; the results take the same range).
  if (accumulationRanges && rangesOn) {
    if (isa<affine::AffineYieldOp, scf::YieldOp>(op)) {
      updateAccumulations(op);
      return;
    }
    if (auto loop = dyn_cast<LoopLikeOpInterface>(op);
        loop && isa<affine::AffineForOp, scf::ForOp>(op)) {
      setMax();
      for (auto [k, a] : llvm::enumerate(loop.getRegionIterArgs()))
        if (accumulationOf(a) && k < op->getNumResults()) {
          auto it = accumulationResult.find(a);
          ranges[op->getResult(k)] = it == accumulationResult.end()
                                          ? IntegerValueRange()
                                          : it->second;
        }
      return;
    }
  }
  // N159, memory form: an accumulating load ranges over init + (T - 1) x
  // the step its read-modify-write store recorded (memAccumulationStep).
  if (accumulationRanges && rangesOn &&
      isa<affine::AffineLoadOp, memref::LoadOp>(op))
    if (std::optional<MemAccumulation> ma = memAccumulationOf(op)) {
      MemClass *c = classOf(asAccess(op)->memref);
      if (c && !c->opaque && !c->fixed && !c->rangePinned) {
        Value res = op->getResult(0);
        IntegerValueRange init;
        bool known = true;
        for (Operation *st : ma->inits) {
          IntegerValueRange r = operandRange(st->getOpOperand(0));
          if (r.isUninitialized()) {
            known = false;
            break;
          }
          init = IntegerValueRange::join(init, r);
        }
        auto step = memAccumulationStep.find(op);
        if (!known || step == memAccumulationStep.end() ||
            step->second.isUninitialized()) {
          ranges[res] = IntegerValueRange();
          return;
        }
        ranges[res] = accumulatedRange(
            init.getValue(), step->second.getValue().smin(),
            step->second.getValue().smax(), ma->trips - 1, res);
        return;
      }
    }
  // Its store records the step's range for the next round.
  if (accumulationRanges && rangesOn)
    if (Operation *ld = memAccumulationLoadOf.lookup(op)) {
      SmallVector<Value, 4> steps = (*memAccumulations[ld]).steps;
      APInt lo(128, 0), hi(128, 0);
      bool known = true;
      for (Value st : steps) {
        IntegerValueRange r = rangeOf(st);
        if (r.isUninitialized()) {
          known = false;
          break;
        }
        lo += r.getValue().smin().sext(128);
        hi += r.getValue().smax().sext(128);
      }
      if (known) {
        IntegerValueRange &cur = memAccumulationStep[ld];
        IntegerValueRange joined = IntegerValueRange::join(
            cur, IntegerValueRange(ConstantIntRanges::fromSigned(lo, hi)));
        if (!(joined == cur)) {
          if (++memAccumulationStepChanges[ld] > kWidenAfterRounds)
            joined = IntegerValueRange(
                ConstantIntRanges::maxRange(/*bitwidth=*/128));
          cur = joined;
          rangesChanged = true;
        }
      }
    }
  // Accesses: a load has the range of what its class stores; a store adds to
  // it.
  // N151 (c): a load reached by a store of the same element in its block
  // has that store's range.
  if (reachingStoreRanges && rangesOn && op->getNumResults() == 1 &&
      bitWidthOf(op->getResult(0).getType()) &&
      (isa<LLVM::LoadOp>(op) || (asAccess(op) && !asAccess(op)->stored))) {
    MemClass *c = isa<LLVM::LoadOp>(op) ? nullptr
                                         : classOf(asAccess(op)->memref);
    if (!c || (!c->opaque && !c->fixed))
      if (const SmallVector<Operation *, 2> &sts = reachingStore(op);
          !sts.empty()) {
        IntegerValueRange joined;
        for (Operation *st : sts) {
          OpOperand &value = isa<LLVM::StoreOp>(st)
                                 ? cast<LLVM::StoreOp>(st).getValueMutable()
                                 : st->getOpOperand(0);
          IntegerValueRange r = operandRange(value);
          if (r.isUninitialized()) {
            joined = r;
            break;
          }
          joined = IntegerValueRange::join(joined, r);
        }
        ranges[op->getResult(0)] = joined;
        return;
      }
  }
  if (std::optional<Access> acc = asAccess(op)) {
    MemClass *c = classOf(acc->memref);
    if (acc->stored) {
      if (c && !c->fixed && !c->rangePinned &&
          bitWidthOf(acc->stored.getType())) {
        IntegerValueRange r = operandRange(op->getOpOperand(0));
        c->unknownStore |= r.isUninitialized();
        if (!r.isUninitialized()) {
          IntegerValueRange joined = IntegerValueRange::join(c->stored, r);
          if (!(joined == c->stored)) {
            rangesChanged = true;
            c->grewThisRound = true;
            c->stored = joined;
          }
          unsigned bits = bitsForRange(r.getValue());
          if (!c->widestStore || bits > c->widestBits) {
            c->widestStore = op;
            c->widestBits = bits;
          }
        }
      }
      return;
    }
    if (op->getNumResults() != 1)
      return setMax();
    Value res = op->getResult(0);
    if (!bitWidthOf(res.getType()))
      return;
    if (!rangesOn || !c || c->opaque || c->rangePinned || c->cyclic) {
      ranges[res] = IntegerValueRange::getMaxRange(res);
      return;
    }
    if (c->fixed) { // a ROM: its values are its initial values
      ranges[res] = c->initRange ? IntegerValueRange(*c->initRange)
                                 : IntegerValueRange::getMaxRange(res);
      return;
    }
    ranges[res] = c->stored;
    return;
  }
  if (auto call = dyn_cast<func::CallOp>(op)) {
    if (func::FuncOp callee = internalCallee(call))
      for (OpOperand &operand : call->getOpOperands())
        if (bitWidthOf(operand.get().getType())) {
          Value p = callee.getArgument(operand.getOperandNumber());
          if (paramRangePinned.count(p))
            continue;
          IntegerValueRange &cur = paramRange[p];
          IntegerValueRange joined =
              IntegerValueRange::join(cur, operandRange(operand));
          if (joined == cur)
            continue;
          rangesChanged = true;
          paramGrewThisRound.insert(p);
          cur = joined;
        }
    return setMax();
  }
  if (auto apply = dyn_cast<affine::AffineApplyOp>(op)) {
    AffineMap map = apply.getAffineMap();
    auto ops = apply.getMapOperands();
    auto r = affineRange(map.getResult(0),
                         ValueRange(ops).take_front(map.getNumDims()),
                         ValueRange(ops).drop_front(map.getNumDims()));
    if (!r)
      return setMax();
    unsigned w = bitWidthOf(apply.getType());
    ranges[apply.getResult()] = IntegerValueRange(ConstantIntRanges::fromSigned(
        APInt(w, r->first, true), APInt(w, r->second, true)));
    return;
  }
  if (isa<scf::IfOp, affine::AffineIfOp>(op) && op->getNumResults()) {
    SmallVector<IntegerValueRange> joined(op->getNumResults());
    for (Region &region : op->getRegions())
      for (Block &b : region)
        if (Operation *term = b.getTerminator())
          for (OpOperand &v : term->getOpOperands())
            if (v.getOperandNumber() < joined.size() &&
                bitWidthOf(v.get().getType()) && !isUndefined(v.get()))
              joined[v.getOperandNumber()] = IntegerValueRange::join(
                  joined[v.getOperandNumber()], operandRange(v));
    for (auto [i, r] : llvm::enumerate(op->getResults()))
      if (bitWidthOf(r.getType()))
        ranges[r] = joined[i];
    return;
  }
  if (auto sel = dyn_cast<arith::SelectOp>(op);
      sel && bitWidthOf(sel.getType())) {
    // Each arm under its side of the condition (`x > 0 ? x : 0` is
    // non-negative).
    IntegerValueRange t = operandRange(op->getOpOperand(1));
    IntegerValueRange f = operandRange(op->getOpOperand(2));
    auto refine = [&](IntegerValueRange r, Value arm, bool holds) {
      if (r.isUninitialized())
        return r;
      if (std::optional<ConstantIntRanges> b =
              conditionBound(arm, sel.getCondition(), holds)) {
        ConstantIntRanges x = r.getValue().intersection(*b);
        if (x.smin().sle(x.smax()) && x.umin().ule(x.umax()))
          return IntegerValueRange(x);
      }
      return r;
    };
    t = refine(t, sel.getTrueValue(), true);
    f = refine(f, sel.getFalseValue(), false);
    // N151 (b): an undefined arm contributes nothing.
    if (isUndefined(sel.getTrueValue()) && !isUndefined(sel.getFalseValue()))
      t = f;
    else if (isUndefined(sel.getFalseValue()) &&
             !isUndefined(sel.getTrueValue()))
      f = t;
    ranges[sel.getResult()] =
        t.isUninitialized() || f.isUninitialized()
            ? IntegerValueRange()
            : IntegerValueRange::join(t, f);
    return;
  }
  auto infer = dyn_cast<InferIntRangeInterface>(op);
  if (!infer || op->getNumRegions()) {
    setMax();
    return;
  }
  SmallVector<IntegerValueRange> args;
  bool bottom = false;
  for (OpOperand &operand : op->getOpOperands()) {
    if (!bitWidthOf(operand.get().getType()))
      return setMax();
    IntegerValueRange r = operandRange(operand);
    bottom |= r.isUninitialized();
    args.push_back(r);
  }
  if (bottom) {
    for (Value r : op->getResults())
      ranges[r] = IntegerValueRange();
    return;
  }
  setMax();
  infer.inferResultRangesFromOptional(
      args, [&](Value v, const IntegerValueRange &r) {
        if (!r.isUninitialized())
          ranges[v] = r;
      });
}

/// The classes whose loads `v` is computed from (through ops, scf.if arms
/// and the call sites of an internal function's parameter; not through loop
/// iter_args, which are full range anyway).
const SmallVector<unsigned, 2> &Narrowing::loadClassesOf(Value root) {
  // Iterative post-order: an unrolled expression can be thousands deep.
  SmallVector<std::pair<Value, bool>> stack{{root, false}};
  DenseSet<Value> onStack;
  while (!stack.empty()) {
    auto [v, expanded] = stack.pop_back_val();
    if (loadClasses.count(v))
      continue;
    SmallVector<Value> inputs;
    std::optional<unsigned> own;
    if (auto arg = dyn_cast<BlockArgument>(v)) {
      if (auto f = dyn_cast<func::FuncOp>(arg.getOwner()->getParentOp()))
        if (isInternalFunction(f))
          for (func::CallOp call : callSites.lookup(f))
            inputs.push_back(call.getOperand(arg.getArgNumber()));
      // N159: an accumulation's value comes from its init and its addends.
      if (isa<affine::AffineForOp, scf::ForOp>(arg.getOwner()->getParentOp()) &&
          arg.getArgNumber() > 0)
        if (const std::optional<Accumulation> &acc = accumulationOf(arg)) {
          inputs.push_back(acc->init);
          inputs.append(acc->steps.begin(), acc->steps.end());
        }
    } else if (Operation *def = v.getDefiningOp()) {
      std::optional<Access> acc = asAccess(def);
      SmallVector<Operation *, 2> forwarded;
      if (acc && !acc->stored && accumulationRanges)
        forwarded = reachingStoreExact(def);
      std::optional<MemAccumulation> memAcc;
      if (acc && !acc->stored && accumulationRanges)
        memAcc = memAccumulationOf(def);
      if (memAcc) {
        // An accumulating load: its init values and its addends.
        for (Operation *st : memAcc->inits)
          inputs.push_back(st->getOperand(0));
        inputs.append(memAcc->steps.begin(), memAcc->steps.end());
      } else if (!forwarded.empty()) {
        // A load forwarded from a store of the same address: the stored
        // values, not the array.
        for (Operation *st : forwarded)
          inputs.push_back(st->getOperand(0));
      } else if (acc) {
        if (MemClass *c = classOf(acc->memref))
          own = static_cast<unsigned>(c - classes.data());
      } else {
        inputs.append(def->operand_begin(), def->operand_end());
        if (isa<scf::IfOp, affine::AffineIfOp>(def))
          for (Region &region : def->getRegions())
            for (Block &b : region)
              if (Operation *term = b.getTerminator())
                inputs.append(term->operand_begin(), term->operand_end());
      }
    }
    if (!expanded) {
      if (!onStack.insert(v).second) {
        loadClasses[v]; // a cycle in the IR: cut it here
        continue;
      }
      stack.push_back({v, true});
      for (Value in : inputs)
        if (!loadClasses.count(in))
          stack.push_back({in, false});
      continue;
    }
    SmallVector<unsigned, 2> set;
    if (own)
      set.push_back(*own);
    for (Value in : inputs) {
      auto it = loadClasses.find(in);
      if (it != loadClasses.end())
        set.append(it->second.begin(), it->second.end());
    }
    llvm::sort(set);
    set.erase(std::unique(set.begin(), set.end()), set.end());
    loadClasses[v] = std::move(set);
  }
  return loadClasses[root];
}

/// Whether `v` is a plain copy of a loaded element: a load (VITIS_NOTES N167:
/// std::swap of two elements). A select of loads is not: a compare-exchange
/// written with selects keeps the full width in Vitis (W9 round 22 review
/// kernels w9r22rv_k21_minmax_swap / k22_minmax_swap_iota: 32 bits, 2 BRAM;
/// the std::swap control k23_swap_mask: 10 bits, 1).
static bool isPlainLoadedCopy(Value v) {
  Operation *def = v.getDefiningOp();
  return def && isa<affine::AffineLoadOp, memref::LoadOp, LLVM::LoadOp>(def);
}

/// Vitis computes an array's stored range once, from the ranges of the
/// arrays its stored values are loaded from; it does not iterate around a
/// cycle (`a[i] = a[i + 1] ^ (a[i] >> 1)` keeps 64 bits although 32 would
/// do: w9i_self; the same expression into another array is narrowed:
/// w9i_noself). Loads of an array on a cycle of this dependence are full
/// range; masks after them still bound what is stored (w9i_selfadd: 8).
void Narrowing::markCyclicClasses() {
  unsigned n = classes.size();
  std::vector<SmallVector<unsigned, 4>> succ(n); // D -> C: C stores from D
  // A plain copy of the array's own loaded elements makes no cycle: Vitis
  // closes the range over swaps (N167).
  const bool copiesClose =
      circt::hlsest::Config::get().tool.hls.narrowing.copiesCloseRanges;
  for (auto [ci, c] : llvm::enumerate(classes))
    if (!c.fixed)
      for (Operation *st : c.stores)
        if (bitWidthOf(asAccess(st)->stored.getType())) {
          // A copy of the array's own elements (a swap) closes; a copy
          // through another array does not (held-out beam_search `paths` /
          // `temp_paths`: Vitis keeps 32 bits).
          bool selfCopy = copiesClose && isPlainLoadedCopy(asAccess(st)->stored);
          for (unsigned d : loadClassesOf(asAccess(st)->stored)) {
            if (selfCopy && d == ci)
              continue;
            if (d != ci ||
                feedsBackIntoSameBank(asAccess(st)->stored, d, st))
              succ[d].push_back(static_cast<unsigned>(ci));
          }
        }
  // Tarjan's strongly connected components, iteratively.
  std::vector<int> index(n, -1), low(n, 0);
  std::vector<bool> onStack(n, false);
  SmallVector<unsigned> sccStack;
  int counter = 0;
  for (unsigned start = 0; start < n; ++start) {
    if (index[start] >= 0)
      continue;
    SmallVector<std::pair<unsigned, unsigned>> work{{start, 0}};
    index[start] = low[start] = counter++;
    sccStack.push_back(start);
    onStack[start] = true;
    while (!work.empty()) {
      auto &[v, next] = work.back();
      if (next < succ[v].size()) {
        unsigned w = succ[v][next++];
        if (index[w] < 0) {
          index[w] = low[w] = counter++;
          sccStack.push_back(w);
          onStack[w] = true;
          work.push_back({w, 0});
        } else if (onStack[w]) {
          low[v] = std::min(low[v], index[w]);
        }
        continue;
      }
      unsigned done = v;
      work.pop_back();
      if (!work.empty())
        low[work.back().first] = std::min(low[work.back().first], low[done]);
      if (low[done] != index[done])
        continue;
      SmallVector<unsigned> scc;
      unsigned w;
      do {
        w = sccStack.pop_back_val();
        onStack[w] = false;
        scc.push_back(w);
      } while (w != done);
      bool selfLoop = llvm::is_contained(succ[done], done);
      if (scc.size() > 1 || selfLoop)
        for (unsigned m : scc) {
          classes[m].cyclic = true;
          classes[m].scc = static_cast<int>(done);
        }
    }
  }
}

/// Counts the rounds in which each range grew, and sets a range that grew in
/// more than kWidenAfterRounds rounds to the full range (pinning changes the
/// loads' ranges, so it asks for one more round).
void Narrowing::endRound() {
  for (MemClass &c : classes) {
    if (!c.grewThisRound)
      continue;
    c.grewThisRound = false;
    if (++c.rangeChanges > kWidenAfterRounds && !c.rangePinned) {
      c.rangePinned = true;
      c.pinReason = "still growing after " +
                    std::to_string(kWidenAfterRounds) + " rounds";
      rangesChanged = true;
    }
  }
  for (Value p : paramGrewThisRound)
    if (++paramRangeChanges[p] > kWidenAfterRounds &&
        paramRangePinned.insert(p).second)
      rangesChanged = true;
  paramGrewThisRound.clear();
}

void Narrowing::solveRanges() {
  markCyclicClasses();
  for (MemClass &c : classes) {
    if (c.fixed)
      continue;
    if (c.copiedIn) {
      c.rangePinned = true; // the copied values are unknown
      c.pinReason = "filled by a memcpy copy-in";
    } else if (c.initRange)
      c.stored = IntegerValueRange(*c.initRange);
    else if (c.stores.empty()) {
      c.rangePinned = true; // read, never written: nothing is known
      c.pinReason = "never written";
    }
    // VITIS_NOTES N162: Vitis does not narrow an array whose element a
    // function it keeps as a call writes through a scalar reference
    // parameter (gnnbuilder pna_qm9
    // `min_incremental_data::one_sample_processed`, set to 0 in the caller
    // and to 1 only in the `INLINE off` min_incremental_update through its
    // `min_incremental_data &` parameter: 32 bits in all five 128-deep rows;
    // inlined, the same field of the max aggregation is 1 bit; kernels
    // w9r21rev_r10a_flagcall (struct member) and w9r21fx_x1_plainref (`int
    // &seen`): 128 x 32; r10b_flaginl (inlined): 128 x 1). An array passed
    // whole and indexed by the callee is narrowed (w9r21fx_x2_plainarr: 128
    // x 1; barry_walker lab2 `attention`, written in the dataflow process
    // softmax_HLS: 8 bits).
    if (calleeParamStoresFullRange && !c.rangePinned &&
        llvm::any_of(c.stores, [&](Operation *st) {
          return writesCalleeParameter(st);
        })) {
      c.rangePinned = true;
      c.pinReason =
          "written through a scalar reference parameter of a called function";
    }
  }
  // Stores join into their array's range in place, so a copy later in
  // program order sees it in the same round. An array that still has a
  // store without a range at the fixpoint is set to the full range, and the
  // arrays that copy from it are recomputed.
  for (bool again = true; again;) {
    do {
      rangesChanged = false;
      ranges.clear();
      for (MemClass &c : classes)
        c.unknownStore = false;
      for (Operation *op : ops)
        forwardOp(op);
      endRound();
    } while (rangesChanged);
    again = false;
    for (MemClass &c : classes)
      if (c.unknownStore && !c.rangePinned) {
        c.rangePinned = true;
        c.pinReason = "a stored value has no known range";
        again = true;
      }
  }
}

//===----------------------------------------------------------------------===//
// Demanded bits.
//===----------------------------------------------------------------------===//

/// The low bits of a subscript at `dim` of `memref` that reach the address:
/// the bits of the flattened address of the array (without the dimensions a
/// complete partition removes), less the bits a power-of-two stride shifts
/// out. nullopt: every bit (an interface, an unknown memref, a dimension
/// split into registers, a dynamic shape).
/// Which dimensions of `memref` a complete partition splits into separate
/// memories (from the partition of the arrays of its class); nullopt when
/// the class's arrays have another shape.
std::optional<SmallVector<bool>>
Narrowing::completeDims(Value memref) const {
  MemClass *c = classOf(memref);
  auto type = dyn_cast<MemRefType>(memref.getType());
  if (!c || !type)
    return std::nullopt;
  SmallVector<bool> complete(type.getRank(), false);
  for (Operation *root : c->roots)
    if (std::optional<BankLayout> l = partitions.layoutOf(root)) {
      MemRefType rootType =
          isa<memref::GlobalOp>(root)
              ? cast<memref::GlobalOp>(root).getType()
              : cast<MemRefType>(root->getResult(0).getType());
      if (rootType.getShape() != type.getShape())
        return std::nullopt;
      for (const DimPartition &p : l->dims)
        if (p.kind == PartitionSpec::Complete && p.dim < complete.size())
          complete[p.dim] = true;
    }
  return complete;
}

/// The values the subscript at `dim` of an access can take.
std::optional<std::pair<int64_t, int64_t>>
Narrowing::subscriptRange(Operation *access, unsigned dim) {
  auto ofValue = [&](Value v) -> std::optional<std::pair<int64_t, int64_t>> {
    IntegerValueRange r = rangeOf(v);
    if (r.isUninitialized() || r.getValue().smin().getSignificantBits() > 62 ||
        r.getValue().smax().getSignificantBits() > 62)
      return std::nullopt;
    return std::make_pair(r.getValue().smin().getSExtValue(),
                          r.getValue().smax().getSExtValue());
  };
  for (unsigned no = 0; no < access->getNumOperands(); ++no)
    if (plainSubscriptPosition(access, no) == dim)
      return ofValue(access->getOperand(no));
  AffineMap map;
  SmallVector<Value> operands;
  if (auto rd = dyn_cast<affine::AffineReadOpInterface>(access)) {
    map = rd.getAffineMap();
    operands = llvm::to_vector(rd.getMapOperands());
  } else if (auto wr = dyn_cast<affine::AffineWriteOpInterface>(access)) {
    map = wr.getAffineMap();
    operands = llvm::to_vector(wr.getMapOperands());
  } else {
    return std::nullopt;
  }
  if (dim >= map.getNumResults())
    return std::nullopt;
  return affineRange(map.getResult(dim),
                     ValueRange(operands).take_front(map.getNumDims()),
                     ValueRange(operands).drop_front(map.getNumDims()));
}

/// Whether two accesses of one array reach different memories of a complete
/// partition (`t[0][k]` and `t[i][k]` with i in [1, 7]): after the split,
/// which comes before the narrowing in Vitis, they are two arrays.
bool Narrowing::differentBanks(Operation *a, Operation *b) {
  Value memref = asAccess(a)->memref;
  std::optional<SmallVector<bool>> complete = completeDims(memref);
  if (!complete || asAccess(b)->memref.getType() != memref.getType())
    return false;
  for (auto [d, split] : llvm::enumerate(*complete)) {
    if (!split)
      continue;
    auto ra = subscriptRange(a, d), rb = subscriptRange(b, d);
    if (ra && rb && (ra->second < rb->first || rb->second < ra->first))
      return true;
  }
  return false;
}

/// Whether some load of class `cls` that `v` is computed from may read the
/// memory `store` writes (see differentBanks).
bool Narrowing::feedsBackIntoSameBank(Value v, unsigned cls,
                                      Operation *store) {
  SmallVector<Value> work{v};
  DenseSet<Value> seen;
  while (!work.empty()) {
    Value x = work.pop_back_val();
    if (!seen.insert(x).second)
      continue;
    auto it = loadClasses.find(x);
    if (it != loadClasses.end() && !llvm::is_contained(it->second, cls))
      continue;
    if (auto arg = dyn_cast<BlockArgument>(x)) {
      if (auto f = dyn_cast<func::FuncOp>(arg.getOwner()->getParentOp()))
        for (func::CallOp call : callSites.lookup(f))
          work.push_back(call.getOperand(arg.getArgNumber()));
      continue;
    }
    Operation *def = x.getDefiningOp();
    if (!def)
      continue;
    if (std::optional<Access> acc = asAccess(def)) {
      MemClass *c = classOf(acc->memref);
      if (c && static_cast<unsigned>(c - classes.data()) == cls &&
          !differentBanks(def, store))
        return true;
      continue;
    }
    work.append(def->operand_begin(), def->operand_end());
    if (isa<scf::IfOp, affine::AffineIfOp>(def))
      for (Region &region : def->getRegions())
        for (Block &b : region)
          if (Operation *term = b.getTerminator())
            work.append(term->operand_begin(), term->operand_end());
  }
  return false;
}

std::optional<unsigned> Narrowing::subscriptBits(Value memref, unsigned dim,
                                                 bool isRead) const {
  MemClass *c = classOf(memref);
  auto type = dyn_cast<MemRefType>(memref.getType());
  if (!c || c->addressOpaque || !type || !type.hasStaticShape() ||
      dim >= type.getRank())
    return std::nullopt;
  std::optional<SmallVector<bool>> completeOpt = completeDims(memref);
  if (!completeOpt)
    return std::nullopt;
  SmallVector<bool> &complete = *completeOpt;
  // A subscript of a completely partitioned dimension selects one of its S
  // banks. For a read Vitis keeps ceil(log2 S) bits of it (the selector of
  // `_ssdm_op_SparseMux`, whose out-of-range default is undef: kernels
  // w9r12p_nw_p16r1 / p64r1 / p65r1 give 4 / 6 / 7 bits, VITIS_NOTES N91); a
  // write is a compare chain whose out-of-range case writes nothing, so all
  // bits stay demanded (w9r12p_nw_wr64 / nw_wrst: 32 bits).
  if (complete[dim])
    return isRead && completeReadSelector
               ? std::optional<unsigned>(llvm::Log2_64_Ceil(
                     static_cast<uint64_t>(type.getDimSize(dim))))
               : std::nullopt;
  uint64_t words = 1, stride = 1;
  for (unsigned d = 0; d < type.getRank(); ++d) {
    if (complete[d])
      continue;
    words *= static_cast<uint64_t>(type.getDimSize(d));
    if (d > dim)
      stride *= static_cast<uint64_t>(type.getDimSize(d));
  }
  unsigned addrBits = llvm::Log2_64_Ceil(words);
  // The outermost dimension that is still addressed needs only its own
  // bits, whatever the stride below it: Vitis gives the row index of an
  // A[100][10] array 7 bits, not the 10 of the linear address (VITIS_NOTES
  // N41, kernels w9rv_n41_2d and w9rv_n41_2dloc). For an inner dimension
  // with a stride that is not a power of two the whole address is kept
  // (unconfirmed).
  bool outermost = true;
  for (unsigned d = 0; d < dim; ++d)
    if (!complete[d])
      outermost = false;
  if (outermost)
    return llvm::Log2_64_Ceil(static_cast<uint64_t>(type.getDimSize(dim)));
  if (llvm::isPowerOf2_64(stride))
    return addrBits - std::min(addrBits, llvm::Log2_64(stride));
  return addrBits;
}

unsigned Narrowing::affineAccessDemand(Operation *op, OpOperand &use,
                                       unsigned w) {
  AffineMap map;
  OperandRange mapOps = op->getOperands().take_front(0);
  Value memref;
  if (auto rd = dyn_cast<affine::AffineReadOpInterface>(op)) {
    map = rd.getAffineMap();
    mapOps = rd.getMapOperands();
    memref = rd.getMemRef();
  } else if (auto wr = dyn_cast<affine::AffineWriteOpInterface>(op)) {
    map = wr.getAffineMap();
    mapOps = wr.getMapOperands();
    memref = wr.getMemRef();
  } else {
    return w;
  }
  unsigned no = use.getOperandNumber();
  unsigned begin = mapOps.getBeginOperandIndex();
  if (no < begin || no >= begin + mapOps.size())
    return w; // e.g. the condition operands of hls.affine.store_enable
  unsigned j = no - begin;
  bool isRead = isa<affine::AffineReadOpInterface>(op);
  unsigned need = 0;
  for (auto [d, e] : llvm::enumerate(map.getResults())) {
    if (!usesOperand(e, map, j))
      continue;
    if (hasDivOrMod(e))
      return w;
    std::optional<unsigned> bits = subscriptBits(memref, d, isRead);
    if (!bits)
      return w;
    need = std::max(need, *bits);
  }
  return std::min(need, w);
}

unsigned Narrowing::useDemand(OpOperand &use) {
  Value v = use.get();
  unsigned w = bitWidthOf(v.getType());
  if (!w)
    return 0;
  Operation *user = use.getOwner();
  unsigned no = use.getOperandNumber();
  auto capped = [&](uint64_t x) {
    return static_cast<unsigned>(std::min<uint64_t>(x, w));
  };
  auto operandRangeAt = [&](unsigned i) {
    return i < user->getNumOperands()
               ? smallUnsignedRange(user->getOperand(i))
               : std::nullopt;
  };
  auto constOperand = [&](unsigned i) -> std::optional<APInt> {
    return i < user->getNumOperands() ? constantOf(user->getOperand(i))
                                      : std::nullopt;
  };

  if (std::optional<Access> acc = asAccess(user)) {
    if (acc->stored && no == 0 && acc->stored == v) {
      MemClass *c = classOf(acc->memref);
      if (!c || c->fixed || c->demandPinned)
        return w;
      // Around a cycle of arrays Vitis does not iterate: a value stored back
      // into its own array (or one of its cycle) keeps every bit (a
      // histogram `t[x] = t[x] + 1` stays 32 bits although t[x] also
      // indexes a 600-word table: corpus gnnbuilder
      // neightbor_table_offsets_temp).
      if (c->cyclic) {
        unsigned own = static_cast<unsigned>(c - classes.data());
        for (unsigned d : loadClassesOf(v))
          if (classes[d].scc == c->scc &&
              (d != own || feedsBackIntoSameBank(v, d, user)))
            return w;
      }
      return capped(c->demand);
    }
    if (std::optional<unsigned> pos = plainSubscriptPosition(user, no)) {
      std::optional<unsigned> bits =
          subscriptBits(acc->memref, *pos, /*isRead=*/!acc->stored);
      return bits ? capped(*bits) : w;
    }
    return affineAccessDemand(user, use, w);
  }
  if (auto apply = dyn_cast<affine::AffineApplyOp>(user)) {
    AffineMap map = apply.getAffineMap();
    if (hasDivOrMod(map.getResult(0)))
      return w;
    return capped(resultDemand(apply.getResult()));
  }
  if (auto call = dyn_cast<func::CallOp>(user)) {
    func::FuncOp callee = internalCallee(call);
    if (!callee)
      return w;
    Value p = callee.getArgument(no);
    if (paramDemandPinned.count(p))
      return w;
    return capped(paramDemand.lookup(p));
  }
  if (isa<scf::YieldOp, affine::AffineYieldOp>(user)) {
    Operation *parent = user->getParentOp();
    if (isa<scf::IfOp, affine::AffineIfOp>(parent) &&
        no < parent->getNumResults())
      return capped(resultDemand(parent->getResult(no)));
    return w; // a loop-carried value
  }
  if (user->getNumResults() != 1)
    return w;
  unsigned rd = resultDemand(user->getResult(0));
  return llvm::TypeSwitch<Operation *, unsigned>(user)
      .Case<arith::AddIOp, arith::SubIOp, arith::MulIOp, arith::OrIOp,
            arith::XOrIOp>([&](auto) { return capped(rd); })
      .Case<arith::AndIOp>([&](auto) {
        // The other operand's highest possible bit bounds what passes.
        if (auto m = operandRangeAt(1 - no))
          return capped(std::min<unsigned>(
              rd, 64 - llvm::countl_zero(m->second)));
        return capped(rd);
      })
      .Case<arith::ShLIOp>([&](auto) {
        auto s = operandRangeAt(1);
        if (no != 0 || !s)
          return w;
        return capped(rd > s->first ? rd - s->first : 0);
      })
      .Case<arith::ShRUIOp, arith::ShRSIOp>([&](auto) {
        auto s = operandRangeAt(1);
        if (no != 0 || !s)
          return w;
        return rd ? capped(uint64_t(rd) + s->second) : 0u;
      })
      .Case<arith::RemUIOp>([&](auto) {
        std::optional<APInt> c = constOperand(1);
        if (no != 0 || !c || !c->isPowerOf2())
          return w;
        return capped(std::min<unsigned>(rd, c->logBase2()));
      })
      .Case<arith::DivUIOp>([&](auto) {
        std::optional<APInt> c = constOperand(1);
        if (no != 0 || !c || !c->isPowerOf2())
          return w;
        return rd ? capped(uint64_t(rd) + c->logBase2()) : 0u;
      })
      .Case<arith::TruncIOp, arith::ExtUIOp, arith::ExtSIOp,
            arith::IndexCastOp, arith::IndexCastUIOp>(
          [&](auto) { return capped(rd); })
      .Case<arith::SelectOp>([&](auto) { return no == 0 ? w : capped(rd); })
      .Default([&](Operation *) { return w; });
}

std::pair<unsigned, Operation *> Narrowing::valueDemand(Value v) {
  unsigned best = 0;
  Operation *by = nullptr;
  for (OpOperand &use : v.getUses()) {
    unsigned d = useDemand(use);
    if (d > best || !by) {
      best = std::max(best, d);
      by = use.getOwner();
    }
  }
  return {best, by};
}

void Narrowing::solveDemand() {
  for (unsigned round = 0;; ++round) {
    demand.clear();
    demandUser.clear();
    std::vector<unsigned> newDemand(classes.size(), 0);
    std::vector<Operation *> newDeciding(classes.size(), nullptr);
    for (Operation *op : llvm::reverse(ops)) {
      for (Value r : op->getResults()) {
        if (!bitWidthOf(r.getType()))
          continue;
        auto [d, by] = valueDemand(r);
        demand[r] = d;
        demandUser[r] = by;
      }
      std::optional<Access> acc = asAccess(op);
      if (!acc || acc->stored || op->getNumResults() != 1)
        continue;
      MemClass *c = classOf(acc->memref);
      if (!c || c->fixed)
        continue;
      unsigned idx = static_cast<unsigned>(c - classes.data());
      unsigned d = demand.lookup(op->getResult(0));
      if (!newDeciding[idx] || d > newDemand[idx]) {
        newDemand[idx] = std::max(newDemand[idx], d);
        newDeciding[idx] = op;
      }
    }
    DenseMap<Value, unsigned> newParam;
    for (auto f : module.getOps<func::FuncOp>())
      if (isInternalFunction(f))
        for (BlockArgument a : f.getArguments())
          if (bitWidthOf(a.getType()))
            newParam[a] = valueDemand(a).first;
    bool changed = false;
    for (auto [i, c] : llvm::enumerate(classes)) {
      if (c.fixed || c.demandPinned)
        continue;
      c.decidingLoad = newDeciding[i];
      if (newDemand[i] == c.demand)
        continue;
      changed = true;
      if (round >= kMaxDemandRounds)
        c.demandPinned = true;
      else
        c.demand = newDemand[i];
    }
    for (auto &[p, d] : newParam) {
      if (paramDemandPinned.count(p) || paramDemand.lookup(p) == d)
        continue;
      changed = true;
      if (round >= kMaxDemandRounds)
        paramDemandPinned.insert(p);
      else
        paramDemand[p] = d;
    }
    if (!changed)
      break;
  }
}

//===----------------------------------------------------------------------===//
// Result.
//===----------------------------------------------------------------------===//

/// "load (k.cpp:9:40) -> arith.index_cast -> subscript of 'tbl' (64 words)".
std::string Narrowing::demandChain(Operation *load) const {
  std::string s;
  llvm::raw_string_ostream os(s);
  os << load->getName().getStringRef() << " (" << shortLoc(load->getLoc())
     << ")";
  Value v = load->getResult(0);
  for (unsigned step = 0; step < kMaxChainSteps; ++step) {
    Operation *user = demandUser.lookup(v);
    if (!user)
      return os.str() + " (unused)";
    os << " -> ";
    if (std::optional<Access> acc = asAccess(user)) {
      if (acc->stored == v)
        os << "store to '" << nameOf(acc->memref) << "' ("
           << shortLoc(user->getLoc()) << ")";
      else
        os << "subscript of '" << nameOf(acc->memref) << "' ("
           << shortLoc(user->getLoc()) << ")";
      return os.str();
    }
    os << user->getName().getStringRef();
    if (auto call = dyn_cast<func::CallOp>(user)) {
      os << " @" << call.getCallee();
      return os.str();
    }
    if (user->getNumResults() != 1 ||
        isa<scf::YieldOp, affine::AffineYieldOp>(user))
      return os.str();
    v = user->getResult(0);
  }
  return os.str() + " -> ...";
}

/// The width of a RAM whose every stored value is a compile-time constant
/// (a set of constants, not an interval), by N26's ROM rule: with no
/// negative value, each value cut to the unsigned width of the largest is
/// read as signed and the most signed bits any needs is kept (VITIS_NOTES
/// N112: kernels w9r15p_wc_100 / 101 / 96 store {0, c} -> 6 bits, wc_64 -> 7;
/// rosetta 3d-rendering frame_buffer {0, 100} -> 6). nullopt when a store's
/// value is not a constant, the array has an initial value or the rule is
/// off (tool.hls.narrowing.constant_set_reinterpretation).
std::optional<unsigned> Narrowing::constantSetBits(const MemClass &c) {
  if (!circt::hlsest::Config::get()
           .tool.hls.narrowing.constantSetReinterpretation ||
      c.initRange || c.stores.empty() || !c.declaredBits ||
      c.declaredBits > 64)
    return std::nullopt;
  SmallVector<APInt> vals;
  for (Operation *st : c.stores) {
    std::optional<Access> a = asAccess(st);
    std::optional<APInt> k =
        a && a->stored ? constantOf(a->stored) : std::nullopt;
    if (!k)
      return std::nullopt;
    vals.push_back(k->sextOrTrunc(c.declaredBits));
  }
  bool anyNegative =
      llvm::any_of(vals, [](const APInt &v) { return v.isNegative(); });
  unsigned width = 0;
  if (anyNegative) {
    for (const APInt &v : vals)
      width = std::max(width, v.getSignificantBits());
    return width;
  }
  unsigned a = 0;
  for (const APInt &v : vals)
    a = std::max(a, v.getActiveBits());
  if (a == 0)
    return std::nullopt; // all zero: dead-memory elimination's
  for (const APInt &v : vals)
    width = std::max(width, v.trunc(a).getSignificantBits());
  return width;
}

void Narrowing::annotate() {
  for (MemClass &c : classes) {
    if (remarksOn && c.fixed)
      for (Operation *root : c.roots)
        root->emitRemark() << "narrow-ram-widths: not narrowed: "
                           << c.fixedReason;
    if (c.fixed || c.roots.empty() || !c.declaredBits)
      continue;
    unsigned width = c.declaredBits;
    std::string wr = "stored values: none reach it";
    if (rangesOn) {
      if (c.rangePinned) {
        wr = "stored values: full range (" + c.pinReason + ")";
      } else if (!c.stored.isUninitialized()) {
        unsigned bits = bitsForRange(c.stored.getValue());
        wr = "stored values " + rangeText(c.stored.getValue()) + " need " +
             std::to_string(bits) + " bits";
        if (c.widestStore)
          wr += " (widest store at " + shortLoc(c.widestStore->getLoc()) + ")";
        if (std::optional<unsigned> setBits = constantSetBits(c);
            setBits && *setBits < bits) {
          bits = std::max(1u, *setBits);
          wr += "; every stored value a constant: " + std::to_string(bits) +
                " bits by the ROM reinterpretation (VITIS_NOTES N112)";
        }
        width = std::min(width, bits);
      }
    } else {
      wr = "stored ranges off";
    }
    std::string wd = "loads: none used";
    if (demandOn) {
      if (c.demandPinned) {
        wd = "loads demand every bit (no fixpoint after " +
             std::to_string(kMaxDemandRounds) + " rounds)";
      } else if (c.decidingLoad && c.demand > 0) {
        wd = "loads demand " + std::to_string(c.demand) + " bits: " +
             demandChain(c.decidingLoad);
        width = std::min(width, c.demand);
      }
    } else {
      wd = "load demand off";
    }
    if (remarksOn)
      for (Operation *root : c.roots)
        root->emitRemark() << "narrow-ram-widths: " << width << " of "
                           << c.declaredBits << " bits; " << wr << "; " << wd
                           << (c.cyclic ? "; on a cycle of arrays" : "")
                           << "; " << c.stores.size() << " store(s), "
                           << c.loads.size() << " load(s)";
    if (width >= c.declaredBits)
      continue;
    std::string reason = std::to_string(width) + " of " +
                         std::to_string(c.declaredBits) + " bits: " + wr +
                         "; " + wd;
    Builder b(module.getContext());
    for (Operation *root : c.roots) {
      root->setAttr(kNarrowBitsAttrName,
                    b.getI32IntegerAttr(static_cast<int32_t>(width)));
      root->setAttr(kNarrowReasonAttrName, b.getStringAttr(reason));
    }
  }
}

void Narrowing::run() {
  buildClasses();
  module.walk([&](Operation *op) {
    if (!isa<ModuleOp, func::FuncOp>(op))
      ops.push_back(op);
  });
  if (rangesOn)
    solveRanges();
  if (demandOn)
    solveDemand();
  annotate();
}

struct NarrowRamWidthsPass
    : PassWrapper<NarrowRamWidthsPass, OperationPass<ModuleOp>> {
  MLIR_DEFINE_EXPLICIT_INTERNAL_INLINE_TYPE_ID(NarrowRamWidthsPass)

  NarrowRamWidthsPass() = default;
  NarrowRamWidthsPass(const NarrowRamWidthsPass &other) : PassWrapper(other) {}

  Option<bool> storedRanges{
      *this, "stored-ranges",
      llvm::cl::desc("Narrow to the bits the stored values need"),
      llvm::cl::init(true)};
  Option<bool> loadDemand{
      *this, "load-demand",
      llvm::cl::desc("Narrow to the low bits the loads' users demand"),
      llvm::cl::init(true)};
  Option<bool> completeReadSelector{
      *this, "complete-read-selector",
      llvm::cl::desc("A read's subscript of a completely partitioned "
                     "dimension of S elements demands ceil(log2 S) bits "
                     "(VITIS_NOTES N91)"),
      llvm::cl::init(true)};
  Option<bool> remarks{
      *this, "remarks",
      llvm::cl::desc("Emit one remark per array with its widths and why"),
      llvm::cl::init(false)};

  StringRef getArgument() const final { return "narrow-ram-widths"; }
  StringRef getDescription() const final {
    return "Mark the element width Vitis gives each local / global array: "
           "min(bits the stored values need, low bits the loads' users "
           "demand) as hls.narrow_bits (run before --memory-banking-bram)";
  }
  void getDependentDialects(DialectRegistry &registry) const override {
    registry.insert<arith::ArithDialect, memref::MemRefDialect>();
  }
  void runOnOperation() override {
    // An option given explicitly, else tool.hls.narrowing.*.
    const circt::hlsest::NarrowingConfig &nc =
        circt::hlsest::Config::get().tool.hls.narrowing;
    circt::hlsest::applyConfigured(storedRanges, nc.storedRanges);
    circt::hlsest::applyConfigured(loadDemand, nc.loadDemand);
    circt::hlsest::applyConfigured(completeReadSelector,
                                   nc.completeReadSelector);
    Narrowing(getOperation(), storedRanges, loadDemand, remarks,
              nc.fullAddressInterfaceModes, completeReadSelector,
              nc.undefContributesNothing, nc.reachingStoreRanges,
              nc.accumulationRanges, nc.calleeParamStoresFullRange)
        .run();
  }
};

} // namespace

std::unique_ptr<Pass> circt::hls_analysis::createNarrowRamWidthsPass() {
  return std::make_unique<NarrowRamWidthsPass>();
}
