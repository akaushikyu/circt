//===- VitisFold.cpp - folds Vitis HLS performs that MLIR refuses ---------===//
//
// --vitis-fold
//
// MLIR leaves `arith.divsi %x, %c0` alone because the result is undefined
// behaviour, so a chain that Vitis HLS kills never folds. This pass applies
// what Vitis HLS 2025.1 does with an integer division / remainder by a
// constant zero, measured per operation (VITIS_NOTES.md N1a "Division by a
// constant 0" and N13), then the canonicalization folds.
//
// 1. The undefined value U (option `undef`, default on; N13).
//
//    Vitis' first backend transform (LLVM 3.1 based, `a.g.0` / `a.o.1`)
//    folds `sdiv / udiv / srem x, 0` to `undef` and then follows LLVM's undef
//    rules. Kernels: ~/hls-est-work/exp-src/t8/undef_cint.cpp (one output
//    slot per C int use of U = in[0] / 0, run t8_undef_cint), its follow-up
//    ~/hls-est-work/exp-src/t8review/rv_undef2.cpp (run t8review_undef2:
//    shifts right by U, remui by U, ops on two U values, selects decided by
//    a compare of U), the ap_fixed probes probe / probe2
//    (result_read_headers.md section 2) and dg_d_fold_divrem0{,b} (T4
//    review). Rules, integer types only (U2 is another U value):
//
//      source   divsi / divui / remsi %x, <constant 0>            -> U
//      U kept   trunci(U), addi / subi with a U operand, xori with
//               exactly one U operand, x / U, x % U (divsi / divui /
//               remsi / remui, U the divisor), x << U, x >> U (shrsi,
//               shrui), U * <odd constant>, U * U2, U & U2, U | U2 -> U
//      folds    extsi / extui / sitofp / uitofp (U)                 -> 0
//               U * y (y neither an odd constant nor U), U & y     -> 0
//               U ^ U2                                             -> 0
//               U | y                                              -> -1
//               U << c, U >> c (shrsi, shrui), U / y, U % y        -> 0
//               cmpi pred (U, y) or (y, U)        -> isTrueWhenEqual(pred)
//                 (eq / sle / sge / ule / uge true, the others false,
//                 whatever y is); also through a pair of the same
//                 extension from the same type, cmpi pred (ext U, ext y)
//                 (Vitis narrows such a compare first: probe2 out[16])
//               select c, U, y and select c, y, U                  -> y
//                 unless c is a constant, also one a compare rule above
//                 just produced: then the arm c picks, U or not
//                 (`(u >= x) ? u : x` is U and its store is deleted,
//                 rv_undef2 out[3], out[4])
//               a store of U into a function argument (an output)
//                 is deleted
//      anything else (an unmeasured use: a select / if condition, a yield,
//      a call operand, a cast, a min / max ...) sees U := 0, which is one
//      value U may take (a refinement, the T4 behaviour).
//
//    The compare has to be seen before MLIR merges `select (cmpi sge U, x),
//    U, x` into `maxsi U, x`: Vitis picks U for the sge form and x for the
//    sgt form (isTrueWhenEqual), and a max / min cannot tell the two apart.
//    So the rules run once before the first greedy rewrite, and with `undef`
//    the pass's own rewrite leaves out the arith select -> min / max
//    patterns (a later --canonicalize still forms them). A --canonicalize
//    run before this pass has already merged them; such a min / max of U is
//    an unmeasured use (VITIS_NOTES.md N13).
//
//    `remui %x, <constant 0>` is 0, not U: Vitis stores `a + b % 0u` as `a`
//    (dg_d_fold_divrem0 o_urem, undef_cint uout[1]).
//
//    Why add / sub keep U while an ap_fixed `in + scale` is `in`: the
//    integer-backed ap_fixed (the exactclass shim, as Vitis' own header)
//    sign-extends both operands to the result type first, and an extension
//    of U is 0. A C int `a + b / 0` has no extension: Vitis drops the store
//    and both arrays (dg_d_fold_divrem0: 6 BRAM, a_sdiv / b_sdiv gone).
//    Measured exceptions the rules do not reproduce: a C short sum
//    `(short)((short)u + (short)x)` is deleted by Vitis (it narrows the add
//    before it sees U; here the extension gives x), and `c ? U : x` is
//    stored only when !c (here: x always; same arrays live).
//
//    A store of U into a local or global memref is not deleted: hls-est has
//    no mem2reg here, so a later load would read the old contents instead of
//    U. Loads of the same element later in the same block, with no write in
//    between, are forwarded as U (what mem2reg gives Vitis for a local
//    scalar); then the stored value becomes 0.
//
//    Every rewrite is recorded in the module attribute `hls.vitis_fold`
//    (counts per rule, the same per function, and the first records with
//    their locations and function), which --bram-debug / --bram-debug-json
//    print (with --bram-analysis=top=, only the reachable functions' share).
//
// 2. Without `undef` (the T4 behaviour) and for index / vector types:
//
//      divsi / divui / remsi / remui %x, <constant 0>  -> constant 0
//
//    exact for ap_fixed and unsigned remainder, a refinement of U elsewhere
//    (OPEN_ISSUES.md O16: the other operands of `a + b / 0` stay live).
//    ceildivsi / ceildivui / floordivsi are not folded: no C expression
//    produces them with a zero divisor.
//
// 3. In the same greedy rewrite (option `canonicalize`, default on) every
//    loaded dialect's canonicalization patterns and the op folders, so a
//    folded zero propagates at once (muli %y, 0 -> 0, addi %y, 0 -> %y, ...).
//    The rules of 1 and the greedy rewrite alternate until neither changes
//    the IR (a folded U can expose a new zero divisor: `1.0 / scale`). Run
//    `--sccp` before for values that are only constant along the executed
//    paths (MEMOS.md M5 pipeline).
//
// 4. One-element tables (option `uniform-tables`, default on; only when the
//    pass runs on the module): a load from a never-written one-element
//    global (a scalar global) is its initial value (VITIS_NOTES.md N52;
//    foldUniformTableLoads below). Vitis folds such a scalar before its
//    automatic pipeline decision; a multi-element table, even a small
//    uniform one, folds only after it (once the pipeline pragma has
//    partitioned it into registers), so it is not folded here.
//
// 5. Counted loops (option `raise-counted-loops`, default on): an scf.for
//    whose bounds and step fold to constants becomes the normalised
//    affine.for over its trip count, in the same greedy rewrite, and its
//    memref.load / memref.store with affine indices become affine accesses
//    (RaiseCountedScfFor below). Under the same option an scf.while whose
//    exit test only reads values that start as constants and change by
//    constant arithmetic (`unsigned char i = 16; while (i--)`,
//    `for (i = 8; --i;)`, which cgeist emits as scf.while) becomes an
//    affine.for over its trip count (RaiseCountedScfWhile below): Vitis
//    computes that trip count and decides the loop as a counted one
//    (o72r_cdw: unrolled into the pipelined loop around it, 30;
//    o72r_cdw2: collapsed with its parent, 6).
//
// Not folded, on purpose: floating point (`mulf %y, 0.0` is not 0 for NaN /
// inf / -0.0; under the scalar / exact shims ap_fixed is a float, so nothing
// here applies, OPEN_ISSUES.md O6, O16), floating-point division by zero, and
// integer division by a non-constant value that is zero at run time.
//
//===----------------------------------------------------------------------===//

#include "../Plugins/Builtin/Builtins.h"
#include "circt/Dialect/Resource/Passes/ConstantCallEval.h"
#include "circt/Dialect/Resource/Plugins/PassPolicies.h"
#include "circt/Dialect/Resource/Plugins/Registry.h"
#include "circt/Dialect/Resource/Config/ConfigUtils.h"
#include "circt/Dialect/Resource/Passes/PolygeistCompat.h"
#include "circt/Dialect/Resource/Passes/ReadOnlyMemory.h"
#include "circt/Dialect/Resource/Passes/VitisCleanup.h"

#include "mlir/Dialect/Affine/IR/AffineOps.h"
#include "mlir/Dialect/Arith/IR/Arith.h"
#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/Dialect/LLVMIR/LLVMDialect.h"
#include "mlir/Dialect/MemRef/IR/MemRef.h"
#include "mlir/Dialect/SCF/IR/SCF.h"
#include "mlir/IR/BuiltinOps.h"
#include "mlir/IR/IRMapping.h"
#include "mlir/IR/Matchers.h"
#include "mlir/IR/PatternMatch.h"
#include "mlir/Interfaces/FunctionInterfaces.h"
#include "mlir/Interfaces/SideEffectInterfaces.h"
#include "mlir/Pass/Pass.h"
#include "mlir/Transforms/GreedyPatternRewriteDriver.h"
#include "llvm/ADT/MapVector.h"
#include "llvm/ADT/SetVector.h"
#include "llvm/ADT/StringMap.h"

#include <algorithm>
#include <type_traits>

using namespace mlir;

namespace {

//===----------------------------------------------------------------------===//
// x / 0 -> 0 (the T4 rule) for what the undef rules do not model.
//===----------------------------------------------------------------------===//

template <typename OpTy>
struct FoldIntDivByZero : OpRewritePattern<OpTy> {
  FoldIntDivByZero(MLIRContext *ctx, bool undefRules)
      : OpRewritePattern<OpTy>(ctx), undefRules(undefRules) {}

  LogicalResult matchAndRewrite(OpTy op,
                                PatternRewriter &rewriter) const override {
    if (!matchPattern(op.getRhs(), m_Zero()))
      return failure();
    Type ty = op.getType();
    // With the undef rules an integer divsi / divui / remsi by 0 is U (see
    // UndefFolder); remui by 0 stays 0 (measured).
    if (undefRules && isa<IntegerType>(ty) &&
        !std::is_same_v<OpTy, arith::RemUIOp>)
      return failure();
    TypedAttr zero = rewriter.getZeroAttr(ty);
    if (!zero)
      return failure();
    rewriter.replaceOpWithNewOp<arith::ConstantOp>(op, ty, zero);
    return success();
  }

  bool undefRules;
};

//===----------------------------------------------------------------------===//
// The undefined value U.
//===----------------------------------------------------------------------===//

// One rewrite a rule made (circt::hlsest::FoldNote, the plugin interface's
// record): rule, loc, source, detail and the enclosing function's symbol.
using circt::hlsest::FoldNote;

/// divsi / divui / remsi of an integer by a constant 0.
static bool isUndefSource(Operation *op) {
  if (!isa<arith::DivSIOp, arith::DivUIOp, arith::RemSIOp>(op))
    return false;
  if (!isa<IntegerType>(op->getResult(0).getType()))
    return false;
  return matchPattern(op->getOperand(1), m_Zero());
}

static bool isOddConstant(Value v) {
  APInt c;
  return matchPattern(v, m_ConstantInt(&c)) && c[0];
}

static bool isTrueWhenEqual(arith::CmpIPredicate p) {
  switch (p) {
  case arith::CmpIPredicate::eq:
  case arith::CmpIPredicate::sle:
  case arith::CmpIPredicate::sge:
  case arith::CmpIPredicate::ule:
  case arith::CmpIPredicate::uge:
    return true;
  default:
    return false;
  }
}

/// The memref a view / cast chain starts from.
static Value memrefBase(Value m) {
  while (Operation *def = m.getDefiningOp()) {
    if (auto c = dyn_cast<memref::CastOp>(def))
      m = c.getSource();
    else if (auto s = dyn_cast<memref::SubViewOp>(def))
      m = s.getSource();
    else if (auto r = dyn_cast<memref::ReinterpretCastOp>(def))
      m = r.getSource();
    else if (auto e = dyn_cast<memref::ExpandShapeOp>(def))
      m = e.getSrc();
    else if (auto c2 = dyn_cast<memref::CollapseShapeOp>(def))
      m = c2.getSrc();
    else
      break;
  }
  return m;
}

/// A memref argument of a function (a port of the top, or of a callee that
/// was not inlined).
static bool isFunctionArgument(Value base) {
  auto arg = dyn_cast<BlockArgument>(base);
  if (!arg || !arg.getOwner()->isEntryBlock())
    return false;
  return isa<FunctionOpInterface>(arg.getOwner()->getParentOp());
}

/// Two memrefs whose bases are known, different storage: an allocation
/// (alloca / alloc) and any other known root (another allocation, a global,
/// a function argument), or two different globals. A base that is not such
/// a root (an if / loop result, a block argument of a region, an unknown op
/// such as polygeist.subindex) may be any of them, so it may alias.
static bool provablyDistinct(Value a, Value b) {
  Value ba = memrefBase(a), bb = memrefBase(b);
  if (ba == bb)
    return false;
  auto isAlloc = [](Value v) {
    Operation *d = v.getDefiningOp();
    return d && isa<memref::AllocaOp, memref::AllocOp>(d);
  };
  auto isGlobal = [](Value v) {
    return static_cast<bool>(v.getDefiningOp<memref::GetGlobalOp>());
  };
  auto isRoot = [&](Value v) {
    return isAlloc(v) || isGlobal(v) || isFunctionArgument(v);
  };
  if (!isRoot(ba) || !isRoot(bb))
    return false;
  if (isAlloc(ba) || isAlloc(bb))
    return true;
  if (isGlobal(ba) && isGlobal(bb))
    return ba.getDefiningOp<memref::GetGlobalOp>().getName() !=
           bb.getDefiningOp<memref::GetGlobalOp>().getName();
  return false; // two arguments, or an argument and a global
}

/// Store value operand / memref / "same access as" helpers for affine and
/// memref stores and loads.
static std::optional<std::pair<Value, Value>> storeValueAndMemref(Operation *op) {
  if (auto s = dyn_cast<affine::AffineStoreOp>(op))
    return std::make_pair(s.getValueToStore(), s.getMemRef());
  if (auto s = dyn_cast<memref::StoreOp>(op))
    return std::make_pair(s.getValueToStore(), s.getMemRef());
  return std::nullopt;
}

static bool sameAccess(Operation *store, Operation *load) {
  if (auto s = dyn_cast<affine::AffineStoreOp>(store)) {
    auto l = dyn_cast<affine::AffineLoadOp>(load);
    return l && l.getMemRef() == s.getMemRef() &&
           l.getAffineMap() == s.getAffineMap() &&
           llvm::equal(l.getMapOperands(), s.getMapOperands());
  }
  if (auto s = dyn_cast<memref::StoreOp>(store)) {
    auto l = dyn_cast<memref::LoadOp>(load);
    return l && l.getMemRef() == s.getMemRef() &&
           llvm::equal(l.getIndices(), s.getIndices());
  }
  return false;
}

static const char *const kNoteAttr = "hls.vitis_fold";
static constexpr unsigned kMaxRecords = 256;

class UndefFolder {
public:
  explicit UndefFolder(Operation *root) : root(root) {}

  /// One round: find U, rewrite its uses. True if the IR changed.
  bool run(SmallVectorImpl<FoldNote> &notes);

private:
  void addUndef(Value v, Location src) {
    if (!isa<IntegerType>(v.getType()))
      return;
    if (undef.insert({v, src}).second)
      work.push_back(v);
  }
  bool isU(Value v) const { return undef.count(v); }
  Location srcOf(Value v) const { return undef.find(v)->second; }
  /// The result of `op` is U given which of its operands are U.
  bool producesUndef(Operation *op) const;
  void forwardStore(Operation *store, Value u);

  Operation *root;
  llvm::MapVector<Value, Location> undef;
  SmallVector<Value> work;
};

bool UndefFolder::producesUndef(Operation *op) const {
  if (op->getNumResults() != 1 || !isa<IntegerType>(op->getResult(0).getType()))
    return false;
  if (isa<arith::TruncIOp>(op))
    return isU(op->getOperand(0));
  if (isa<arith::AddIOp, arith::SubIOp>(op))
    return isU(op->getOperand(0)) || isU(op->getOperand(1));
  // U ^ x is U, U ^ U2 is 0 (rv_undef2 out[7]).
  if (isa<arith::XOrIOp>(op))
    return isU(op->getOperand(0)) != isU(op->getOperand(1));
  // x / U, x % U, also unsigned (rv_undef2 uout[0]); x / 0 is a source and
  // remui x, 0 is 0.
  if (isa<arith::DivSIOp, arith::DivUIOp, arith::RemSIOp, arith::RemUIOp>(op))
    return isU(op->getOperand(1));
  // x << U, x >> U (rv_undef2 out[0], out[1]).
  if (isa<arith::ShLIOp, arith::ShRSIOp, arith::ShRUIOp>(op))
    return isU(op->getOperand(1));
  // U * U2, U & U2, U | U2 (rv_undef2 out[5], out[6], out[8]).
  if (isa<arith::MulIOp, arith::AndIOp, arith::OrIOp>(op) &&
      isU(op->getOperand(0)) && isU(op->getOperand(1)))
    return true;
  if (isa<arith::MulIOp>(op))
    return (isU(op->getOperand(0)) && isOddConstant(op->getOperand(1))) ||
           (isU(op->getOperand(1)) && isOddConstant(op->getOperand(0)));
  if (auto sel = dyn_cast<arith::SelectOp>(op)) {
    if (isU(sel.getTrueValue()) && isU(sel.getFalseValue()))
      return true;
    APInt c;
    if (matchPattern(sel.getCondition(), m_ConstantInt(&c)))
      return isU(c.isZero() ? sel.getFalseValue() : sel.getTrueValue());
    return false;
  }
  return false;
}

/// `op` or an op nested in it may write `mem` (or has an unknown effect).
static bool mayWrite(Operation *op, Value mem) {
  WalkResult r = op->walk([&](Operation *n) {
    if (isa<affine::AffineLoadOp, memref::LoadOp>(n))
      return WalkResult::advance();
    if (auto sv = storeValueAndMemref(n))
      return provablyDistinct(sv->second, mem) ? WalkResult::advance()
                                               : WalkResult::interrupt();
    // A loop / if has the effects of its body, which the walk visits.
    if (n->getNumRegions() && n->hasTrait<OpTrait::HasRecursiveMemoryEffects>())
      return WalkResult::advance();
    return isMemoryEffectFree(n) ? WalkResult::advance()
                                 : WalkResult::interrupt();
  });
  return r.wasInterrupted();
}

/// Loads of the element `store` writes that follow it in its block (also
/// inside a loop / if there), up to the first op that may write that memory,
/// read U: what mem2reg gives Vitis for a local scalar.
void UndefFolder::forwardStore(Operation *store, Value u) {
  Value mem = storeValueAndMemref(store)->second;
  for (Operation *op = store->getNextNode(); op; op = op->getNextNode()) {
    if (mayWrite(op, mem))
      break;
    op->walk([&](Operation *n) {
      if (isa<affine::AffineLoadOp, memref::LoadOp>(n) && sameAccess(store, n))
        addUndef(n->getResult(0), srcOf(u));
    });
  }
}

bool UndefFolder::run(SmallVectorImpl<FoldNote> &notes) {
  undef.clear();
  work.clear();
  root->walk([&](Operation *op) {
    if (isUndefSource(op))
      addUndef(op->getResult(0), op->getLoc());
  });
  if (undef.empty())
    return false;

  // Propagate through the U-preserving ops and through memory (same block).
  while (!work.empty()) {
    Value v = work.pop_back_val();
    for (OpOperand &use : v.getUses()) {
      Operation *user = use.getOwner();
      if (producesUndef(user)) {
        addUndef(user->getResult(0), srcOf(v));
        continue;
      }
      if (auto sv = storeValueAndMemref(user))
        if (sv->first == v && !isFunctionArgument(memrefBase(sv->second)))
          forwardStore(user, v);
    }
  }

  // Every op that uses a U value and does not itself produce U, in the order
  // the U values were found and then their use lists (not IR order), the
  // selects last: a compare rule below can decide a select's condition.
  llvm::SetVector<Operation *> userSet;
  for (auto &[v, src] : undef)
    for (Operation *u : v.getUsers())
      if (!producesUndef(u))
        userSet.insert(u);
  if (userSet.empty())
    return false;
  SmallVector<Operation *> users(userSet.begin(), userSet.end());
  std::stable_partition(users.begin(), users.end(), [](Operation *op) {
    return !isa<arith::SelectOp>(op);
  });

  OpBuilder b(root->getContext());
  auto note = [&](StringRef rule, Operation *op, Value u, std::string d = {}) {
    std::string fn;
    if (auto f = op->getParentOfType<FunctionOpInterface>())
      fn = f.getName().str();
    notes.push_back(
        {rule.str(), op->getLoc(), srcOf(u), std::move(d), std::move(fn)});
  };
  auto firstU = [&](Operation *op) -> Value {
    for (Value o : op->getOperands())
      if (isU(o))
        return o;
    return {};
  };
  auto replaceWithConstant = [&](Operation *op, TypedAttr attr) {
    b.setInsertionPoint(op);
    Value c = arith::ConstantOp::create(b, op->getLoc(), attr.getType(), attr);
    op->getResult(0).replaceAllUsesWith(c);
  };
  llvm::SmallPtrSet<Operation *, 16> done;
  SmallVector<Operation *> toErase;
  auto replaceAndErase = [&](Operation *op, TypedAttr attr) {
    replaceWithConstant(op, attr);
    toErase.push_back(op);
    done.insert(op);
  };
  auto zeroOperands = [&](Operation *op) {
    for (OpOperand &o : op->getOpOperands())
      if (isU(o.get())) {
        b.setInsertionPoint(op);
        Value z = arith::ConstantOp::create(b, op->getLoc(), o.get().getType(),
                                            b.getZeroAttr(o.get().getType()));
        o.set(z);
      }
  };

  for (Operation *op : users) {
    if (done.contains(op))
      continue;
    Value u = firstU(op);
    if (!u)
      continue; // its U operands were rewritten by an earlier action
    if (auto sv = storeValueAndMemref(op)) {
      if (sv->first == u && isFunctionArgument(memrefBase(sv->second))) {
        note("store-deleted", op, u);
        toErase.push_back(op);
        done.insert(op);
      } else {
        note("store-local-zero", op, u);
        zeroOperands(op);
      }
      continue;
    }
    if (isa<arith::ExtSIOp, arith::ExtUIOp>(op)) {
      // cmpi pred (ext U, ext y), the same extension from the same type:
      // Vitis compares the unextended values (probe2 out[16]).
      Type src = op->getOperand(0).getType();
      for (Operation *cmpUser : op->getResult(0).getUsers()) {
        auto cmp = dyn_cast<arith::CmpIOp>(cmpUser);
        if (!cmp || done.contains(cmp))
          continue;
        Value other = cmp.getLhs() == op->getResult(0) ? cmp.getRhs()
                                                       : cmp.getLhs();
        Operation *od = other.getDefiningOp();
        if (!od || od->getName() != op->getName() ||
            od->getOperand(0).getType() != src)
          continue;
        bool val = isTrueWhenEqual(cmp.getPredicate());
        note("cmp-through-ext", cmp, u, val ? "true" : "false");
        replaceAndErase(cmp, b.getBoolAttr(val));
      }
      note("ext-zero", op, u);
      replaceAndErase(op, b.getZeroAttr(op->getResult(0).getType()));
      continue;
    }
    if (isa<arith::SIToFPOp, arith::UIToFPOp>(op)) {
      note("itofp-zero", op, u);
      replaceAndErase(op, b.getZeroAttr(op->getResult(0).getType()));
      continue;
    }
    if (isa<arith::XOrIOp>(op)) { // both operands U (one keeps U)
      note("xor-undef-undef-zero", op, u);
      replaceAndErase(op, b.getZeroAttr(op->getResult(0).getType()));
      continue;
    }
    if (isa<arith::MulIOp, arith::AndIOp>(op)) {
      note(isa<arith::MulIOp>(op) ? "mul-zero" : "and-zero", op, u);
      replaceAndErase(op, b.getZeroAttr(op->getResult(0).getType()));
      continue;
    }
    if (isa<arith::OrIOp>(op)) {
      auto ty = cast<IntegerType>(op->getResult(0).getType());
      note("or-ones", op, u);
      replaceAndErase(op, b.getIntegerAttr(ty, APInt::getAllOnes(ty.getWidth())));
      continue;
    }
    if (isa<arith::ShLIOp, arith::ShRSIOp, arith::ShRUIOp, arith::DivSIOp,
            arith::DivUIOp, arith::RemSIOp, arith::RemUIOp>(op) &&
        isU(op->getOperand(0)) && !isU(op->getOperand(1))) {
      note(isa<arith::ShLIOp, arith::ShRSIOp, arith::ShRUIOp>(op)
               ? "shift-of-undef-zero"
               : "div-of-undef-zero",
           op, u);
      replaceAndErase(op, b.getZeroAttr(op->getResult(0).getType()));
      continue;
    }
    if (auto cmp = dyn_cast<arith::CmpIOp>(op)) {
      bool val = isTrueWhenEqual(cmp.getPredicate());
      note("cmp-true-when-equal", op, u, val ? "true" : "false");
      replaceAndErase(op, b.getBoolAttr(val));
      continue;
    }
    if (auto sel = dyn_cast<arith::SelectOp>(op)) {
      // A condition a compare rule above has just decided: the arm it picks.
      // When that arm is U its users see U in the next round.
      APInt c;
      if (matchPattern(sel.getCondition(), m_ConstantInt(&c))) {
        Value pick = c.isZero() ? sel.getFalseValue() : sel.getTrueValue();
        note("select-constant-condition", op, u,
             isU(pick) ? "undef arm" : "other arm");
        sel.getResult().replaceAllUsesWith(pick);
        toErase.push_back(op);
        done.insert(op);
        continue;
      }
      if (!isU(sel.getCondition())) {
        Value keep = isU(sel.getTrueValue()) ? sel.getFalseValue()
                                             : sel.getTrueValue();
        note("select-other-arm", op, u);
        sel.getResult().replaceAllUsesWith(keep);
        toErase.push_back(op);
        done.insert(op);
        continue;
      }
    }
    // Unmeasured use: U := 0.
    note("use-zero", op, u, op->getName().getStringRef().str());
    zeroOperands(op);
  }

  // The U producers (and forwarded loads) are dead once every use above is
  // rewritten; erase them so the result does not depend on `canonicalize`.
  // Collect them before anything is erased (their Values dangle afterwards).
  llvm::SetVector<Operation *> producers;
  for (auto &[v, src] : undef)
    if (Operation *def = v.getDefiningOp())
      producers.insert(def);
  for (Operation *op : toErase)
    op->erase();
  llvm::SmallPtrSet<Operation *, 16> erased;
  for (bool again = true; again;) {
    again = false;
    for (Operation *def : llvm::reverse(producers)) {
      if (erased.contains(def) || !def->use_empty() ||
          !wouldOpBeTriviallyDead(def))
        continue;
      erased.insert(def);
      def->erase();
      again = true;
    }
  }
  return true;
}

//===----------------------------------------------------------------------===//
// Pass.
//===----------------------------------------------------------------------===//

/// The arith `select (cmpi pred, a, b), a, b -> min / max (a, b)` patterns.
static bool isSelectToMinMax(const RewritePattern &p) {
  std::optional<OperationName> root = p.getRootKind();
  if (!root || root->getStringRef() != arith::SelectOp::getOperationName())
    return false;
  return llvm::any_of(p.getGeneratedOps(), [](OperationName n) {
    return llvm::is_contained({arith::MaxSIOp::getOperationName(),
                               arith::MinSIOp::getOperationName(),
                               arith::MaxUIOp::getOperationName(),
                               arith::MinUIOp::getOperationName()},
                              n.getStringRef());
  });
}

//===----------------------------------------------------------------------===//
// Uniform tables and counted loops (options uniform-tables and
// raise-counted-loops).
//===----------------------------------------------------------------------===//

/// The one value every element of `g`'s initial value holds, or null: a
/// dense integer or float initialiser that is a splat or whose elements are
/// all equal.
static TypedAttr uniformInitialValue(memref::GlobalOp g) {
  auto dense = dyn_cast_or_null<DenseElementsAttr>(g.getInitialValueAttr());
  if (!dense || dense.empty())
    return {};
  Type elt = dense.getElementType();
  if (!isa<IntegerType, FloatType>(elt))
    return {};
  if (dense.isSplat())
    return dense.getSplatValue<TypedAttr>();
  auto values = dense.getValues<Attribute>();
  Attribute first = *values.begin();
  for (Attribute v : values)
    if (v != first)
      return {};
  return cast<TypedAttr>(first);
}

/// A never-written one-element global (a scalar global) is its initial
/// value. Vitis folds it before the automatic pipeline decision (N52:
/// rvsf_g1 / rvsf_g2, `int ksz = 16` as an inner bound: the outer loop is
/// pipelined and k unrolled, 30 = hls-est). A multi-element table whose
/// elements all hold one value folds in Vitis only after the pipeline
/// decision, once the pipeline pragma has completely partitioned it
/// (`partition_inferred: cnt, 'pipeline pragma'`): rvsf_rc16 / rc4 / rc2nc
/// (`cnt[2|4]` all 16 as the inner bound) pipeline the inner loop (2), and
/// folding them here would pipeline the outer loop instead (30). So only one
/// element is folded. Only loads of the get_global result and of its views
/// are folded (a value passed on through a call or a loop may meet another
/// memory there); a global the user gave a storage or partition pragma is
/// left alone (the user decided, as for N7 (a)).
static unsigned foldUniformTableLoads(ModuleOp module,
                                      ArrayRef<std::string> userPragmas,
                                      SmallVectorImpl<FoldNote> &notes) {
  llvm::StringMap<SmallVector<Value>> sites;
  module.walk([&](memref::GetGlobalOp gg) {
    sites[gg.getName()].push_back(gg.getResult());
  });
  unsigned folded = 0;
  for (auto g : module.getOps<memref::GlobalOp>()) {
    if (g.isExternal() || g.isUninitialized() ||
        !g.getType().hasStaticShape() ||
        g.getType().getNumElements() != 1 ||
        llvm::any_of(userPragmas,
                     [&](const std::string &a) { return g->hasAttr(a); }))
      continue;
    TypedAttr value = uniformInitialValue(g);
    if (!value)
      continue;
    auto it = sites.find(g.getSymName());
    if (it == sites.end() ||
        !circt::hls_analysis::neverWritten(it->second))
      continue;
    SmallVector<Value> work(it->second.begin(), it->second.end());
    SmallVector<Operation *> loads;
    while (!work.empty()) {
      Value cur = work.pop_back_val();
      for (Operation *user : cur.getUsers()) {
        if (auto view = dyn_cast<ViewLikeOpInterface>(user)) {
          if (view.getViewSource() == cur)
            for (Value r : user->getResults())
              if (isa<BaseMemRefType>(r.getType()))
                work.push_back(r);
          continue;
        }
        if (isa<affine::AffineLoadOp, memref::LoadOp>(user) &&
            user->getOperand(0) == cur &&
            user->getResult(0).getType() == value.getType())
          loads.push_back(user);
      }
    }
    for (Operation *load : loads) {
      OpBuilder b(load);
      Value c = b.create<arith::ConstantOp>(load->getLoc(), value);
      std::string func;
      if (auto fn = load->getParentOfType<FunctionOpInterface>())
        func = fn.getName().str();
      notes.push_back({"uniform-table-load", load->getLoc(), g.getLoc(),
                       ("@" + g.getSymName() + " holds one value").str(),
                       func});
      load->getResult(0).replaceAllUsesWith(c);
      load->erase();
      ++folded;
    }
  }
  return folded;
}

/// The address of a local array or a global (or of a row / element view of
/// one, or of a parameter every call binds to one) compared with the null
/// pointer: never null, so `K[k] ? 1 : 0` is 1
/// and the comparison no longer keeps the array alive (VITIS_NOTES N118:
/// kernel w9r15p_pb_null, Vitis 0 BRAM; nikhil_p lab2 K_lcl). The top
/// function's arguments may be null and are left. Key
/// tool.hls.folding.storage_address_not_null.
/// A call of the C library's assertion failure handler (`__assert_fail`,
/// what `assert` expands to) builds no hardware in Vitis: a pipelined loop
/// with an assert is scheduled as without it (VITIS_NOTES N126: kernels
/// w9r16p_as / as_no identical, II 3; pp4fpgas huffman create_tree). The
/// call is erased; the canonicalization then removes the empty arm and the
/// condition (the loads that fed only the check). Key
/// tool.hls.folding.drop_asserts.
struct DropAssertFail : OpRewritePattern<func::CallOp> {
  using OpRewritePattern::OpRewritePattern;

  static bool isAssertHandler(StringRef name) {
    return name == "__assert_fail" || name == "__assert_rtn" ||
           name == "_assert" || name == "_wassert" ||
           name == "__assert_perror_fail";
  }

  LogicalResult matchAndRewrite(func::CallOp call,
                                PatternRewriter &rewriter) const override {
    if (call.getNumResults() != 0 || !isAssertHandler(call.getCallee()))
      return failure();
    rewriter.eraseOp(call);
    return success();
  }
};

struct FoldStorageAddressNullCompare : OpRewritePattern<LLVM::ICmpOp> {
  using OpRewritePattern::OpRewritePattern;

  /// `mem` names a local array or a global through views; a parameter does
  /// when every call of its function passes one (kernel_compute_acc's K_lcl
  /// parameter in nikhil_p lab2, a dataflow process).
  static bool isStorage(Value mem, unsigned depth = 0) {
    while (Operation *def = mem.getDefiningOp()) {
      if (isa<memref::AllocaOp, memref::AllocOp, memref::GetGlobalOp>(def))
        return true;
      auto view = dyn_cast<ViewLikeOpInterface>(def);
      if (!view)
        return false;
      mem = view.getViewSource();
    }
    auto arg = dyn_cast<BlockArgument>(mem);
    auto fn = arg ? dyn_cast<func::FuncOp>(arg.getOwner()->getParentOp())
                  : func::FuncOp();
    if (!fn || depth > 4 || arg.getOwner() != &fn.getBody().front())
      return false;
    auto module = fn->getParentOfType<ModuleOp>();
    std::optional<SymbolTable::UseRange> uses =
        module ? SymbolTable::getSymbolUses(fn, module) : std::nullopt;
    if (!uses || uses->empty())
      return false; // the top function, or taken by address
    for (const SymbolTable::SymbolUse &u : *uses) {
      auto call = dyn_cast<func::CallOp>(u.getUser());
      if (!call || arg.getArgNumber() >= call.getNumOperands() ||
          !isStorage(call.getOperand(arg.getArgNumber()), depth + 1))
        return false;
    }
    return true;
  }

  static bool isLocalOrGlobalStorage(Value ptr) {
    auto m2p = ptr.getDefiningOp<circt::hls_analysis::Memref2PointerOp>();
    return m2p && isStorage(m2p.getSource());
  }

  LogicalResult matchAndRewrite(LLVM::ICmpOp cmp,
                                PatternRewriter &rewriter) const override {
    LLVM::ICmpPredicate p = cmp.getPredicate();
    if (p != LLVM::ICmpPredicate::eq && p != LLVM::ICmpPredicate::ne)
      return failure();
    Value a = cmp.getLhs(), b = cmp.getRhs();
    if (b.getDefiningOp<LLVM::ZeroOp>())
      std::swap(a, b);
    if (!a.getDefiningOp<LLVM::ZeroOp>() || !isLocalOrGlobalStorage(b))
      return failure();
    rewriter.replaceOpWithNewOp<arith::ConstantOp>(
        cmp, rewriter.getBoolAttr(p == LLVM::ICmpPredicate::ne));
    return success();
  }
};

/// An scf.for whose bounds and step have become constants (cgeist leaves a
/// loop scf.for when its bound is not an affine symbol, e.g. loaded inside an
/// enclosing loop; a fold above may make it constant) becomes the normalised
/// affine.for over its trip count, with the original induction value
/// recomputed by an affine.apply: the automatic pipeline decision (VITIS_NOTES
/// N3) reads trip counts of affine loops only, and Vitis sees a counted loop.
struct RaiseCountedScfFor : OpRewritePattern<scf::ForOp> {
  using OpRewritePattern::OpRewritePattern;
  LogicalResult matchAndRewrite(scf::ForOp op,
                                PatternRewriter &rewriter) const override {
    if (!op.getInductionVar().getType().isIndex())
      return failure();
    APInt lbC, ubC, stepC;
    if (!matchPattern(op.getLowerBound(), m_ConstantInt(&lbC)) ||
        !matchPattern(op.getUpperBound(), m_ConstantInt(&ubC)) ||
        !matchPattern(op.getStep(), m_ConstantInt(&stepC)))
      return failure();
    int64_t lb = lbC.getSExtValue(), ub = ubC.getSExtValue(),
            step = stepC.getSExtValue();
    if (step <= 0 || ub <= lb)
      return failure(); // a zero-trip loop is the canonicalizer's
    // An unsigned comparison reads negative bounds as large values.
    if (op.getUnsignedCmp() && lb < 0)
      return failure();
    int64_t trip = llvm::divideCeil(static_cast<uint64_t>(ub - lb),
                                    static_cast<uint64_t>(step));
    Location loc = op.getLoc();
    auto loop = rewriter.create<affine::AffineForOp>(loc, 0, trip, 1,
                                                     op.getInitArgs());
    loop->setDiscardableAttrs(op->getDiscardableAttrDictionary());
    Block *body = loop.getBody();
    if (!body->empty() && body->back().hasTrait<OpTrait::IsTerminator>())
      rewriter.eraseOp(&body->back());
    rewriter.setInsertionPointToStart(body);
    AffineExpr d0 = rewriter.getAffineDimExpr(0);
    Value iv = rewriter.create<affine::AffineApplyOp>(
        loc, AffineMap::get(1, 0, d0 * step + lb), body->getArgument(0));
    SmallVector<Value> replacements{iv};
    for (BlockArgument a : body->getArguments().drop_front())
      replacements.push_back(a);
    rewriter.mergeBlocks(op.getBody(), body, replacements);
    auto yield = cast<scf::YieldOp>(body->getTerminator());
    rewriter.setInsertionPoint(yield);
    rewriter.replaceOpWithNewOp<affine::AffineYieldOp>(yield,
                                                       yield.getOperands());
    rewriter.replaceOp(op, loop.getResults());
    affinizeAccesses(loop, rewriter);
    return success();
  }

  /// The memref.load / memref.store in the raised loop whose indices are all
  /// valid affine dimensions or symbols become affine.load / affine.store:
  /// constant-index partitioning (VITIS_NOTES N7 (b)), banking and the
  /// scheduler's dependence analysis read affine accesses only, as for a loop
  /// cgeist raised itself (kernels rvsf_g3 / rvsf_g3c: the same body under a
  /// one-element-global bound and under a #define bound, both Vitis 16).
  /// Accesses indexed by a value of an enclosing non-affine loop stay.
  static void affinizeAccesses(affine::AffineForOp loop,
                               PatternRewriter &rewriter) {
    auto allAffine = [](ValueRange indices) {
      return llvm::all_of(indices, [](Value v) {
        return affine::isValidDim(v) || affine::isValidSymbol(v);
      });
    };
    SmallVector<Operation *> accesses;
    loop.walk([&](Operation *op) {
      if (isa<memref::LoadOp, memref::StoreOp>(op))
        accesses.push_back(op);
    });
    for (Operation *op : accesses) {
      rewriter.setInsertionPoint(op);
      DictionaryAttr attrs = op->getDiscardableAttrDictionary();
      Operation *repl = nullptr;
      if (auto load = dyn_cast<memref::LoadOp>(op)) {
        if (allAffine(load.getIndices()))
          repl = rewriter.replaceOpWithNewOp<affine::AffineLoadOp>(
              load, load.getMemRef(), load.getIndices());
      } else if (auto store = dyn_cast<memref::StoreOp>(op)) {
        if (allAffine(store.getIndices()))
          repl = rewriter.replaceOpWithNewOp<affine::AffineStoreOp>(
              store, store.getValueToStore(), store.getMemRef(),
              store.getIndices());
      }
      if (repl)
        repl->setDiscardableAttrs(attrs);
    }
  }
};

/// The trip count of an scf.while whose exit test can be computed at
/// compile time: the loop is executed symbolically, the iteration values
/// that start as constants (its init operands) are carried through the
/// arith operations of both regions by their folders, and the count is
/// returned once the condition folds to false. Anything else (a load, a
/// call, a nested loop, a value never constant) is unknown; a condition that
/// reads an unknown value makes the trip count unknown. Bounded by
/// kMaxTrips iterations and kMaxSteps evaluated operations.
static std::optional<uint64_t> constantWhileTripCount(scf::WhileOp op) {
  constexpr uint64_t kMaxTrips = uint64_t(1) << 16;
  constexpr uint64_t kMaxSteps = uint64_t(1) << 22;
  if (!op.getBefore().hasOneBlock() || !op.getAfter().hasOneBlock())
    return std::nullopt;
  Block &before = op.getBefore().front();
  Block &after = op.getAfter().front();
  auto cond = cast<scf::ConditionOp>(before.getTerminator());
  auto yield = cast<scf::YieldOp>(after.getTerminator());
  DenseMap<Value, Attribute> env;
  auto valueOf = [&](Value v) -> Attribute {
    auto it = env.find(v);
    if (it != env.end())
      return it->second;
    if (op->isAncestor(v.getParentRegion()->getParentOp()))
      return {};
    Attribute c;
    if (matchPattern(v, m_Constant(&c)))
      return c;
    return {};
  };
  auto evaluate = [&](Block &block) {
    for (Operation &o : block.without_terminator()) {
      SmallVector<Attribute, 4> operands;
      bool known = isa<arith::ArithDialect>(o.getDialect()) &&
                   o.getNumRegions() == 0;
      for (Value v : o.getOperands()) {
        if (!known)
          break;
        operands.push_back(valueOf(v));
        known = static_cast<bool>(operands.back());
      }
      SmallVector<OpFoldResult, 2> results;
      if (known && (failed(o.fold(operands, results)) ||
                    results.size() != o.getNumResults()))
        known = false;
      for (auto [i, r] : llvm::enumerate(o.getResults())) {
        Attribute a;
        if (known) {
          if (auto v = dyn_cast<Value>(results[i]))
            a = v == r ? Attribute() : valueOf(v);
          else
            a = cast<Attribute>(results[i]);
        }
        env[r] = a;
      }
    }
  };
  SmallVector<Attribute, 4> state;
  for (Value v : op.getInits())
    state.push_back(valueOf(v));
  const uint64_t stepsPerTrip =
      before.getOperations().size() + after.getOperations().size();
  uint64_t steps = 0;
  for (uint64_t trip = 0;; ++trip) {
    for (auto [arg, a] : llvm::zip(before.getArguments(), state))
      env[arg] = a;
    evaluate(before);
    auto c = dyn_cast_or_null<IntegerAttr>(valueOf(cond.getCondition()));
    if (!c)
      return std::nullopt;
    if (c.getValue().isZero())
      return trip;
    steps += stepsPerTrip;
    if (trip >= kMaxTrips || steps > kMaxSteps)
      return std::nullopt;
    SmallVector<Attribute, 4> forwarded;
    for (Value v : cond.getArgs())
      forwarded.push_back(valueOf(v));
    for (auto [arg, a] : llvm::zip(after.getArguments(), forwarded))
      env[arg] = a;
    evaluate(after);
    state.clear();
    for (Value v : yield.getOperands())
      state.push_back(valueOf(v));
  }
}

/// An scf.while with a constant trip count N >= 1 (constantWhileTripCount)
/// becomes `affine.for 0 to N` carrying the while's values: its body is the
/// before region (the exit test, now dead) followed by the after region, and
/// the before region is cloned once more after the loop for the values the
/// while forwarded at its exit. The loop keeps the while's attributes (user
/// pragmas). Iteration-dependent indices stay as they are (computed from the
/// carried values); once the loop is unrolled they fold to constants.
struct RaiseCountedScfWhile : OpRewritePattern<scf::WhileOp> {
  using OpRewritePattern::OpRewritePattern;
  LogicalResult matchAndRewrite(scf::WhileOp op,
                                PatternRewriter &rewriter) const override {
    std::optional<uint64_t> trip = constantWhileTripCount(op);
    if (!trip || *trip == 0)
      return failure();
    Block &before = op.getBefore().front();
    Block &after = op.getAfter().front();
    auto cond = cast<scf::ConditionOp>(before.getTerminator());
    auto yield = cast<scf::YieldOp>(after.getTerminator());
    Location loc = op.getLoc();
    auto loop = rewriter.create<affine::AffineForOp>(
        loc, 0, static_cast<int64_t>(*trip), 1, op.getInits());
    loop->setDiscardableAttrs(op->getDiscardableAttrDictionary());
    Block *body = loop.getBody();
    if (!body->empty() && body->back().hasTrait<OpTrait::IsTerminator>())
      rewriter.eraseOp(&body->back());
    rewriter.setInsertionPointToEnd(body);
    IRMapping inLoop;
    for (auto [arg, carried] :
         llvm::zip(before.getArguments(), body->getArguments().drop_front()))
      inLoop.map(arg, carried);
    for (Operation &o : before.without_terminator())
      rewriter.clone(o, inLoop);
    for (auto [arg, v] : llvm::zip(after.getArguments(), cond.getArgs()))
      inLoop.map(arg, inLoop.lookupOrDefault(v));
    for (Operation &o : after.without_terminator())
      rewriter.clone(o, inLoop);
    SmallVector<Value> next;
    for (Value v : yield.getOperands())
      next.push_back(inLoop.lookupOrDefault(v));
    rewriter.create<affine::AffineYieldOp>(loc, next);
    rewriter.setInsertionPointAfter(loop);
    IRMapping atExit;
    for (auto [arg, r] : llvm::zip(before.getArguments(), loop.getResults()))
      atExit.map(arg, r);
    for (Operation &o : before.without_terminator())
      rewriter.clone(o, atExit);
    SmallVector<Value> results;
    for (Value v : cond.getArgs())
      results.push_back(atExit.lookupOrDefault(v));
    rewriter.replaceOp(op, results);
    return success();
  }
};

struct VitisFoldPass : PassWrapper<VitisFoldPass, OperationPass<>> {
  MLIR_DEFINE_EXPLICIT_INTERNAL_INLINE_TYPE_ID(VitisFoldPass)

  VitisFoldPass() = default;
  VitisFoldPass(const VitisFoldPass &other) : PassWrapper(other) {}

  Option<bool> canonicalize{
      *this, "canonicalize",
      llvm::cl::desc("Also apply every loaded dialect's canonicalization "
                     "patterns and the op folders in the same greedy rewrite, "
                     "so a folded zero propagates (x*0 -> 0 for integers); "
                     "false: only the division rules"),
      llvm::cl::init(true)};
  Option<bool> undefRules{
      *this, "undef",
      llvm::cl::desc("Vitis' undefined value for an integer divsi / divui / "
                     "remsi by a constant 0 (VITIS_NOTES.md N13: stores of it "
                     "into outputs deleted, add / sub / trunc keep it, "
                     "extensions / mul / and fold to 0, compares to "
                     "isTrueWhenEqual, ...); false: x/0 -> 0 (the T4 rule)"),
      llvm::cl::init(true)};
  Option<bool> uniformTables{
      *this, "uniform-tables",
      llvm::cl::desc("Fold a load from a never-written one-element global "
                     "(a scalar global) to its initial value, as Vitis does "
                     "before its pipeline decision (VITIS_NOTES.md N52); "
                     "only when the pass runs on the module"),
      llvm::cl::init(true)};
  Option<bool> raiseCountedLoops{
      *this, "raise-counted-loops",
      llvm::cl::desc("Turn an scf.for whose bounds and step fold to "
                     "constants into a normalised affine.for with affine "
                     "accesses (the automatic pipeline decision reads affine "
                     "trip counts, partitioning and banking affine indices), "
                     "and an scf.while whose exit test folds to a constant "
                     "trip count into an affine.for over it"),
      llvm::cl::init(true)};

  StringRef getArgument() const final { return "vitis-fold"; }
  StringRef getDescription() const final {
    return "Fold what Vitis HLS folds but MLIR does not: integer division / "
           "remainder by a constant zero and the undefined value it gives "
           "(VITIS_NOTES.md N1a, N13), then the canonicalization folds";
  }
  void getDependentDialects(DialectRegistry &registry) const override {
    registry.insert<arith::ArithDialect, affine::AffineDialect>();
  }

  void runOnOperation() override {
    MLIRContext *ctx = &getContext();
    // An option given explicitly, else the configuration (tool.hls.folding:
    // the FoldRuleSet rule_set, canonicalize, max_rounds). undef=true is the
    // rule set vitis-undef, undef=false the rule set zero.
    const circt::hlsest::Config &cfg = circt::hlsest::Config::get();
    const circt::hlsest::FoldingConfig &fc = cfg.tool.hls.folding;
    std::string ruleSetName = fc.ruleSet;
    if (undefRules.hasValue())
      ruleSetName = undefRules ? "vitis-undef" : "zero";
    circt::hlsest::ConfigDiagnostics diag;
    std::unique_ptr<circt::hlsest::FoldRuleSet> rules =
        circt::hlsest::PluginRegistry<circt::hlsest::FoldRuleSet>::instance()
            .create(ruleSetName, cfg, diag);
    if (!rules) {
      InFlightDiagnostic d = getOperation()->emitError("--vitis-fold: ");
      llvm::interleave(diag.errors, d, "; ");
      return signalPassFailure();
    }
    const bool canon = circt::hlsest::resolveOption(canonicalize,
                                                    fc.canonicalize);
    const unsigned maxRounds = static_cast<unsigned>(fc.maxRounds);
    RewritePatternSet patterns(ctx);
    rules->populate(patterns, ctx);
    if (raiseCountedLoops)
      patterns.add<RaiseCountedScfFor, RaiseCountedScfWhile>(ctx);
    if (cfg.tool.hls.folding.storageAddressNotNull)
      patterns.add<FoldStorageAddressNullCompare>(ctx);
    if (cfg.tool.hls.folding.dropAsserts)
      patterns.add<DropAssertFail>(ctx);
    if (canon) {
      for (Dialect *dialect : ctx->getLoadedDialects())
        dialect->getCanonicalizationPatterns(patterns);
      for (RegisteredOperationName op : ctx->getRegisteredOperations())
        op.getCanonicalizationPatterns(patterns, ctx);
      // `select (cmpi a, b), a, b` stays a select: as a min / max it loses
      // the predicate that decides a compare of U (see the file comment).
      if (rules->keepSelectCompare())
        llvm::erase_if(patterns.getNativePatterns(),
                       [](const std::unique_ptr<RewritePattern> &p) {
                         return isSelectToMinMax(*p);
                       });
    }
    FrozenRewritePatternSet frozen(std::move(patterns));
    // A failure to converge is not an error (the IR is still valid). Without
    // `canonicalize` the op folders are off too.
    GreedyRewriteConfig config;
    config.enableFolding(canon);
    SmallVector<FoldNote> notes;
    // Only on the module itself: the test reads every function's uses.
    if (uniformTables)
      if (auto module = dyn_cast<ModuleOp>(getOperation()))
        (void)foldUniformTableLoads(module, cfg.frontend.userStoragePragmas,
                                    notes);
    // Calls of constants evaluated (N130): only on the module (the callee
    // may be any function).
    auto module = dyn_cast<ModuleOp>(getOperation());
    const bool evalCalls = module && fc.evaluateConstantCalls;
    if (evalCalls)
      (void)circt::hls_analysis::foldConstantCalls(
          module, fc.constantCallMaxSteps, notes);
    std::unique_ptr<circt::hlsest::RuleFolder> folder =
        rules->createFolder(getOperation());
    // The rules first, before the rewrite merges anything they need.
    if (folder)
      (void)folder->run(notes);
    for (unsigned round = 0; round < maxRounds; ++round) {
      (void)applyPatternsGreedily(getOperation(), frozen, config);
      bool more = folder && folder->run(notes);
      if (evalCalls && circt::hls_analysis::foldConstantCalls(
                           module, fc.constantCallMaxSteps, notes) > 0)
        more = true;
      if (!more)
        break;
    }
    // Fill loops of constants evaluated (N174): only on the module; the
    // folded loads and loop results are cleaned up by one more round.
    if (module && fc.evaluateConstantFills &&
        circt::hls_analysis::foldConstantFillPrefixes(
            module, fc.constantCallMaxSteps, fc.constantFillMaxElements,
            notes) > 0)
      (void)applyPatternsGreedily(getOperation(), frozen, config);
    recordNotes(notes);
  }

  /// `hls.vitis_fold` on the module: {counts = {rule = n}, func_counts =
  /// {function = {rule = n}}, rewrites = [{rule, loc, source, detail, func}]}
  /// (first kMaxRecords), merged with an earlier run. func_counts and func let
  /// --bram-analysis=top= report only the reachable functions' rewrites.
  void recordNotes(ArrayRef<FoldNote> notes) {
    if (notes.empty())
      return;
    // Only when the pass runs on the module itself (as on the hls-est
    // command line): nested under a function it may run in parallel with
    // its siblings and must not touch the parent. The notes are debug only.
    auto module = dyn_cast<ModuleOp>(getOperation());
    if (!module)
      return;
    MLIRContext *ctx = &getContext();
    Builder b(ctx);
    llvm::StringMap<int64_t> counts;
    llvm::StringMap<llvm::StringMap<int64_t>> funcCounts;
    SmallVector<Attribute> records;
    if (auto prev = module->getAttrOfType<DictionaryAttr>(kNoteAttr)) {
      if (auto c = prev.getAs<DictionaryAttr>("counts"))
        for (NamedAttribute na : c)
          if (auto i = dyn_cast<IntegerAttr>(na.getValue()))
            counts[na.getName().getValue()] += i.getInt();
      if (auto fc = prev.getAs<DictionaryAttr>("func_counts"))
        for (NamedAttribute f : fc)
          if (auto per = dyn_cast<DictionaryAttr>(f.getValue()))
            for (NamedAttribute na : per)
              if (auto i = dyn_cast<IntegerAttr>(na.getValue()))
                funcCounts[f.getName().getValue()][na.getName().getValue()] +=
                    i.getInt();
      if (auto r = prev.getAs<ArrayAttr>("rewrites"))
        records.append(r.begin(), r.end());
    }
    for (const FoldNote &n : notes) {
      ++counts[n.rule];
      if (!n.func.empty())
        ++funcCounts[n.func][n.rule];
      if (records.size() >= kMaxRecords)
        continue;
      SmallVector<NamedAttribute> f;
      f.push_back(b.getNamedAttr("rule", b.getStringAttr(n.rule)));
      f.push_back(b.getNamedAttr("loc", LocationAttr(n.loc)));
      f.push_back(b.getNamedAttr("source", LocationAttr(n.source)));
      if (!n.detail.empty())
        f.push_back(b.getNamedAttr("detail", b.getStringAttr(n.detail)));
      if (!n.func.empty())
        f.push_back(b.getNamedAttr("func", b.getStringAttr(n.func)));
      records.push_back(b.getDictionaryAttr(f));
    }
    auto countDict = [&](const llvm::StringMap<int64_t> &m) {
      SmallVector<NamedAttribute> cs;
      for (auto &e : m)
        cs.push_back(
            b.getNamedAttr(e.getKey(), b.getI64IntegerAttr(e.getValue())));
      return b.getDictionaryAttr(cs); // sorts by name
    };
    SmallVector<NamedAttribute> fcs;
    for (auto &e : funcCounts)
      fcs.push_back(b.getNamedAttr(e.getKey(), countDict(e.getValue())));
    module->setAttr(
        kNoteAttr,
        b.getDictionaryAttr(
            {b.getNamedAttr("counts", countDict(counts)),
             b.getNamedAttr("func_counts", b.getDictionaryAttr(fcs)),
             b.getNamedAttr("rewrites", b.getArrayAttr(records))}));
  }
};

//===----------------------------------------------------------------------===//
// The builtin fold rule sets (FoldRuleSet plugins).
//===----------------------------------------------------------------------===//

/// vitis-undef: Vitis' undefined value for an integer division / remainder
/// by a constant 0 and its propagation (VITIS_NOTES N13).
class VitisUndefRules : public circt::hlsest::FoldRuleSet {
public:
  StringRef name() const override { return "vitis-undef"; }
  void populate(RewritePatternSet &patterns,
                MLIRContext *ctx) const override {
    patterns.add<FoldIntDivByZero<arith::DivSIOp>,
                 FoldIntDivByZero<arith::DivUIOp>,
                 FoldIntDivByZero<arith::RemSIOp>,
                 FoldIntDivByZero<arith::RemUIOp>>(ctx, /*undefRules=*/true);
  }
  bool keepSelectCompare() const override { return true; }
  std::unique_ptr<circt::hlsest::RuleFolder>
  createFolder(Operation *root) const override {
    return std::make_unique<UndefRuleFolder>(root);
  }

private:
  struct UndefRuleFolder : circt::hlsest::RuleFolder {
    explicit UndefRuleFolder(Operation *root) : folder(root) {}
    bool run(SmallVectorImpl<FoldNote> &notes) override {
      return folder.run(notes);
    }
    UndefFolder folder;
  };
};

/// zero: an integer x / 0 and x % 0 fold to 0 (exact for ap_fixed and for
/// an unsigned remainder; the T4 rule).
class ZeroRules : public circt::hlsest::FoldRuleSet {
public:
  StringRef name() const override { return "zero"; }
  void populate(RewritePatternSet &patterns,
                MLIRContext *ctx) const override {
    patterns.add<FoldIntDivByZero<arith::DivSIOp>,
                 FoldIntDivByZero<arith::DivUIOp>,
                 FoldIntDivByZero<arith::RemSIOp>,
                 FoldIntDivByZero<arith::RemUIOp>>(ctx, /*undefRules=*/false);
  }
};

} // namespace

void circt::hlsest::builtin::registerFoldRuleSets() {
  auto &r = circt::hlsest::PluginRegistry<circt::hlsest::FoldRuleSet>::instance();
  r.add("vitis-undef",
        "Vitis' undefined value of an integer x / 0 and its propagation "
        "(VITIS_NOTES N13)",
        [] { return std::make_unique<VitisUndefRules>(); }, "builtin");
  r.add("zero", "integer x / 0 and x % 0 fold to 0",
        [] { return std::make_unique<ZeroRules>(); }, "builtin");
}

namespace circt::hls_analysis {
std::unique_ptr<Pass> createVitisFoldPass() {
  return std::make_unique<VitisFoldPass>();
}
} // namespace circt::hls_analysis
