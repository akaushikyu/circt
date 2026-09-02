

#include "../Plugins/Builtin/Builtins.h"
#include "circt/Dialect/Resource/Config/ConfigUtils.h"
#include "circt/Dialect/Resource/Passes/ReadOnlyMemory.h"
#include "circt/Dialect/Resource/Passes/VitisCleanup.h"
#include "circt/Dialect/Resource/Plugins/PassPolicies.h"
#include "circt/Dialect/Resource/Plugins/Registry.h"

#include "mlir/Dialect/Affine/IR/AffineOps.h"
#include "mlir/Dialect/Arith/IR/Arith.h"
#include "mlir/Dialect/MemRef/IR/MemRef.h"
#include "mlir/Dialect/SCF/IR/SCF.h"
#include "mlir/IR/BuiltinOps.h"
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

template <typename OpTy>
struct FoldIntDivByZero : OpRewritePattern<OpTy> {
  FoldIntDivByZero(MLIRContext *context, bool undefRules)
      : OpRewritePattern<OpTy>(context), undefRules(undefRules) {}

  LogicalResult matchAndRewrite(OpTy op,
                                PatternRewriter &rewriter) const override {
    if (!matchPattern(op.getRhs(), m_Zero()))
      return failure();
    Type memRefType = op.getType();

    if (undefRules && isa<IntegerType>(memRefType) &&
        !std::is_same_v<OpTy, arith::RemUIOp>)
      return failure();
    TypedAttr zero = rewriter.getZeroAttr(memRefType);
    if (!zero)
      return failure();
    rewriter.replaceOpWithNewOp<arith::ConstantOp>(op, memRefType, zero);
    return success();
  }

  bool undefRules;
};

using circt::hlsest::FoldNote;

/// divsi / divui / remsi of an integer by a constant 0.
static bool isUndefSource(Operation *op) {
  if (!isa<arith::DivSIOp, arith::DivUIOp, arith::RemSIOp>(op))
    return false;
  if (!isa<IntegerType>(op->getResult(0).getType()))
    return false;
  return matchPattern(op->getOperand(1), m_Zero());
}

static bool isOddConstant(Value valueHandle) {
  APInt candidateValue;
  return matchPattern(valueHandle, m_ConstantInt(&candidateValue)) &&
         candidateValue[0];
}

static bool isTrueWhenEqual(arith::CmpIPredicate portValue) {
  switch (portValue) {
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
static Value memrefBase(Value memoryOp) {
  while (Operation *def = memoryOp.getDefiningOp()) {
    if (auto candidateValue = dyn_cast<memref::CastOp>(def))
      memoryOp = candidateValue.getSource();
    else if (auto stringValue = dyn_cast<memref::SubViewOp>(def))
      memoryOp = stringValue.getSource();
    else if (auto resultValue = dyn_cast<memref::ReinterpretCastOp>(def))
      memoryOp = resultValue.getSource();
    else if (auto entryValue = dyn_cast<memref::ExpandShapeOp>(def))
      memoryOp = entryValue.getSrc();
    else if (auto c2 = dyn_cast<memref::CollapseShapeOp>(def))
      memoryOp = c2.getSrc();
    else
      break;
  }
  return memoryOp;
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
static bool provablyDistinct(Value arrayValue, Value buildPoint) {
  Value ba = memrefBase(arrayValue), bb = memrefBase(buildPoint);
  if (ba == bb)
    return false;
  auto isAlloc = [](Value valueHandle) {
    Operation *dimensionIndex = valueHandle.getDefiningOp();
    return dimensionIndex &&
           isa<memref::AllocaOp, memref::AllocOp>(dimensionIndex);
  };
  auto isGlobal = [](Value valueHandle) {
    return static_cast<bool>(valueHandle.getDefiningOp<memref::GetGlobalOp>());
  };
  auto isRoot = [&](Value valueHandle) {
    return isAlloc(valueHandle) || isGlobal(valueHandle) ||
           isFunctionArgument(valueHandle);
  };
  if (!isRoot(ba) || !isRoot(bb))
    return false;
  if (isAlloc(ba) || isAlloc(bb))
    return true;
  if (isGlobal(ba) && isGlobal(bb))
    return ba.getDefiningOp<memref::GetGlobalOp>().getName() !=
           bb.getDefiningOp<memref::GetGlobalOp>().getName();
  return false;
}

/// Store value operand / memref / "same access as" helpers for affine and
/// memref stores and loads.
static std::optional<std::pair<Value, Value>>
storeValueAndMemref(Operation *op) {
  if (auto stringValue = dyn_cast<affine::AffineStoreOp>(op))
    return std::make_pair(stringValue.getValueToStore(),
                          stringValue.getMemRef());
  if (auto stringValue = dyn_cast<memref::StoreOp>(op))
    return std::make_pair(stringValue.getValueToStore(),
                          stringValue.getMemRef());
  return std::nullopt;
}

static bool sameAccess(Operation *store, Operation *load) {
  if (auto stringValue = dyn_cast<affine::AffineStoreOp>(store)) {
    auto lowerIndex = dyn_cast<affine::AffineLoadOp>(load);
    return lowerIndex && lowerIndex.getMemRef() == stringValue.getMemRef() &&
           lowerIndex.getAffineMap() == stringValue.getAffineMap() &&
           llvm::equal(lowerIndex.getMapOperands(),
                       stringValue.getMapOperands());
  }
  if (auto stringValue = dyn_cast<memref::StoreOp>(store)) {
    auto lowerIndex = dyn_cast<memref::LoadOp>(load);
    return lowerIndex && lowerIndex.getMemRef() == stringValue.getMemRef() &&
           llvm::equal(lowerIndex.getIndices(), stringValue.getIndices());
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
  void addUndef(Value valueHandle, Location src) {
    if (!isa<IntegerType>(valueHandle.getType()))
      return;
    if (undef.insert({valueHandle, src}).second)
      work.push_back(valueHandle);
  }
  bool isU(Value valueHandle) const { return undef.count(valueHandle); }
  Location srcOf(Value valueHandle) const {
    return undef.find(valueHandle)->second;
  }
  /// The result of `op` is U given which of its operands are U.
  bool producesUndef(Operation *op) const;
  void forwardStore(Operation *store, Value useValue);

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

  if (isa<arith::XOrIOp>(op))
    return isU(op->getOperand(0)) != isU(op->getOperand(1));

  if (isa<arith::DivSIOp, arith::DivUIOp, arith::RemSIOp, arith::RemUIOp>(op))
    return isU(op->getOperand(1));

  if (isa<arith::ShLIOp, arith::ShRSIOp, arith::ShRUIOp>(op))
    return isU(op->getOperand(1));

  if (isa<arith::MulIOp, arith::AndIOp, arith::OrIOp>(op) &&
      isU(op->getOperand(0)) && isU(op->getOperand(1)))
    return true;
  if (isa<arith::MulIOp>(op))
    return (isU(op->getOperand(0)) && isOddConstant(op->getOperand(1))) ||
           (isU(op->getOperand(1)) && isOddConstant(op->getOperand(0)));
  if (auto sel = dyn_cast<arith::SelectOp>(op)) {
    if (isU(sel.getTrueValue()) && isU(sel.getFalseValue()))
      return true;
    APInt candidateValue;
    if (matchPattern(sel.getCondition(), m_ConstantInt(&candidateValue)))
      return isU(candidateValue.isZero() ? sel.getFalseValue()
                                         : sel.getTrueValue());
    return false;
  }
  return false;
}

/// `op` or an op nested in it may write `mem` (or has an unknown effect).
static bool mayWrite(Operation *op, Value mem) {
  WalkResult resultValue = op->walk([&](Operation *elementCount) {
    if (isa<affine::AffineLoadOp, memref::LoadOp>(elementCount))
      return WalkResult::advance();
    if (auto sv = storeValueAndMemref(elementCount))
      return provablyDistinct(sv->second, mem) ? WalkResult::advance()
                                               : WalkResult::interrupt();

    if (elementCount->getNumRegions() &&
        elementCount->hasTrait<OpTrait::HasRecursiveMemoryEffects>())
      return WalkResult::advance();
    return isMemoryEffectFree(elementCount) ? WalkResult::advance()
                                            : WalkResult::interrupt();
  });
  return resultValue.wasInterrupted();
}

/// Loads of the element `store` writes that follow it in its block (also
/// inside a loop / if there), up to the first op that may write that memory,
/// read U: what mem2reg gives Vitis for a local scalar.
void UndefFolder::forwardStore(Operation *store, Value useValue) {
  Value mem = storeValueAndMemref(store)->second;
  for (Operation *op = store->getNextNode(); op; op = op->getNextNode()) {
    if (mayWrite(op, mem))
      break;
    op->walk([&](Operation *elementCount) {
      if (isa<affine::AffineLoadOp, memref::LoadOp>(elementCount) &&
          sameAccess(store, elementCount))
        addUndef(elementCount->getResult(0), srcOf(useValue));
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

  while (!work.empty()) {
    Value valueHandle = work.pop_back_val();
    for (OpOperand &use : valueHandle.getUses()) {
      Operation *user = use.getOwner();
      if (producesUndef(user)) {
        addUndef(user->getResult(0), srcOf(valueHandle));
        continue;
      }
      if (auto sv = storeValueAndMemref(user))
        if (sv->first == valueHandle &&
            !isFunctionArgument(memrefBase(sv->second)))
          forwardStore(user, valueHandle);
    }
  }

  llvm::SetVector<Operation *> userSet;
  for (auto &[valueHandle, src] : undef)
    for (Operation *useValue : valueHandle.getUsers())
      if (!producesUndef(useValue))
        userSet.insert(useValue);
  if (userSet.empty())
    return false;
  SmallVector<Operation *> users(userSet.begin(), userSet.end());
  std::stable_partition(users.begin(), users.end(), [](Operation *op) {
    return !isa<arith::SelectOp>(op);
  });

  OpBuilder buildPoint(root->getContext());
  auto note = [&](StringRef rule, Operation *op, Value useValue,
                  std::string dimensionIndex = {}) {
    std::string fn;
    if (auto fieldValue = op->getParentOfType<FunctionOpInterface>())
      fn = fieldValue.getName().str();
    notes.push_back({rule.str(), op->getLoc(), srcOf(useValue),
                     std::move(dimensionIndex), std::move(fn)});
  };
  auto firstU = [&](Operation *op) -> Value {
    for (Value o : op->getOperands())
      if (isU(o))
        return o;
    return {};
  };
  auto replaceWithConstant = [&](Operation *op, TypedAttr attr) {
    buildPoint.setInsertionPoint(op);
    Value candidateValue = arith::ConstantOp::create(buildPoint, op->getLoc(),
                                                     attr.getType(), attr);
    op->getResult(0).replaceAllUsesWith(candidateValue);
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
        buildPoint.setInsertionPoint(op);
        Value depthValue = arith::ConstantOp::create(
            buildPoint, op->getLoc(), o.get().getType(),
            buildPoint.getZeroAttr(o.get().getType()));
        o.set(depthValue);
      }
  };

  for (Operation *op : users) {
    if (done.contains(op))
      continue;
    Value useValue = firstU(op);
    if (!useValue)
      continue;
    if (auto sv = storeValueAndMemref(op)) {
      if (sv->first == useValue && isFunctionArgument(memrefBase(sv->second))) {
        note("store-deleted", op, useValue);
        toErase.push_back(op);
        done.insert(op);
      } else {
        note("store-local-zero", op, useValue);
        zeroOperands(op);
      }
      continue;
    }
    if (isa<arith::ExtSIOp, arith::ExtUIOp>(op)) {

      Type src = op->getOperand(0).getType();
      for (Operation *cmpUser : op->getResult(0).getUsers()) {
        auto cmp = dyn_cast<arith::CmpIOp>(cmpUser);
        if (!cmp || done.contains(cmp))
          continue;
        Value other =
            cmp.getLhs() == op->getResult(0) ? cmp.getRhs() : cmp.getLhs();
        Operation *od = other.getDefiningOp();
        if (!od || od->getName() != op->getName() ||
            od->getOperand(0).getType() != src)
          continue;
        bool operandValue = isTrueWhenEqual(cmp.getPredicate());
        note("cmp-through-ext", cmp, useValue, operandValue ? "true" : "false");
        replaceAndErase(cmp, buildPoint.getBoolAttr(operandValue));
      }
      note("ext-zero", op, useValue);
      replaceAndErase(op, buildPoint.getZeroAttr(op->getResult(0).getType()));
      continue;
    }
    if (isa<arith::SIToFPOp, arith::UIToFPOp>(op)) {
      note("itofp-zero", op, useValue);
      replaceAndErase(op, buildPoint.getZeroAttr(op->getResult(0).getType()));
      continue;
    }
    if (isa<arith::XOrIOp>(op)) {
      note("xor-undef-undef-zero", op, useValue);
      replaceAndErase(op, buildPoint.getZeroAttr(op->getResult(0).getType()));
      continue;
    }
    if (isa<arith::MulIOp, arith::AndIOp>(op)) {
      note(isa<arith::MulIOp>(op) ? "mul-zero" : "and-zero", op, useValue);
      replaceAndErase(op, buildPoint.getZeroAttr(op->getResult(0).getType()));
      continue;
    }
    if (isa<arith::OrIOp>(op)) {
      auto memRefType = cast<IntegerType>(op->getResult(0).getType());
      note("or-ones", op, useValue);
      replaceAndErase(
          op, buildPoint.getIntegerAttr(
                  memRefType, APInt::getAllOnes(memRefType.getWidth())));
      continue;
    }
    if (isa<arith::ShLIOp, arith::ShRSIOp, arith::ShRUIOp, arith::DivSIOp,
            arith::DivUIOp, arith::RemSIOp, arith::RemUIOp>(op) &&
        isU(op->getOperand(0)) && !isU(op->getOperand(1))) {
      note(isa<arith::ShLIOp, arith::ShRSIOp, arith::ShRUIOp>(op)
               ? "shift-of-undef-zero"
               : "div-of-undef-zero",
           op, useValue);
      replaceAndErase(op, buildPoint.getZeroAttr(op->getResult(0).getType()));
      continue;
    }
    if (auto cmp = dyn_cast<arith::CmpIOp>(op)) {
      bool operandValue = isTrueWhenEqual(cmp.getPredicate());
      note("cmp-true-when-equal", op, useValue,
           operandValue ? "true" : "false");
      replaceAndErase(op, buildPoint.getBoolAttr(operandValue));
      continue;
    }
    if (auto sel = dyn_cast<arith::SelectOp>(op)) {

      APInt candidateValue;
      if (matchPattern(sel.getCondition(), m_ConstantInt(&candidateValue))) {
        Value pick =
            candidateValue.isZero() ? sel.getFalseValue() : sel.getTrueValue();
        note("select-constant-condition", op, useValue,
             isU(pick) ? "undef arm" : "other arm");
        sel.getResult().replaceAllUsesWith(pick);
        toErase.push_back(op);
        done.insert(op);
        continue;
      }
      if (!isU(sel.getCondition())) {
        Value keep =
            isU(sel.getTrueValue()) ? sel.getFalseValue() : sel.getTrueValue();
        note("select-other-arm", op, useValue);
        sel.getResult().replaceAllUsesWith(keep);
        toErase.push_back(op);
        done.insert(op);
        continue;
      }
    }

    note("use-zero", op, useValue, op->getName().getStringRef().str());
    zeroOperands(op);
  }

  llvm::SetVector<Operation *> producers;
  for (auto &[valueHandle, src] : undef)
    if (Operation *def = valueHandle.getDefiningOp())
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

/// The arith `select (cmpi pred, a, b), a, b -> min / max (a, b)` patterns.
static bool isSelectToMinMax(const RewritePattern &portValue) {
  std::optional<OperationName> root = portValue.getRootKind();
  if (!root || root->getStringRef() != arith::SelectOp::getOperationName())
    return false;
  return llvm::any_of(
      portValue.getGeneratedOps(), [](OperationName elementCount) {
        return llvm::is_contained({arith::MaxSIOp::getOperationName(),
                                   arith::MinSIOp::getOperationName(),
                                   arith::MaxUIOp::getOperationName(),
                                   arith::MinUIOp::getOperationName()},
                                  elementCount.getStringRef());
      });
}

/// The one value every element of `g`'s initial value holds, or null: a
/// dense integer or float initialiser that is a splat or whose elements are
/// all equal.
static TypedAttr uniformInitialValue(memref::GlobalOp g) {
  auto denseValue =
      dyn_cast_or_null<DenseElementsAttr>(g.getInitialValueAttr());
  if (!denseValue || denseValue.empty())
    return {};
  Type elt = denseValue.getElementType();
  if (!isa<IntegerType, FloatType>(elt))
    return {};
  if (denseValue.isSplat())
    return denseValue.getSplatValue<TypedAttr>();
  auto values = denseValue.getValues<Attribute>();
  Attribute first = *values.begin();
  for (Attribute valueHandle : values)
    if (valueHandle != first)
      return {};
  return cast<TypedAttr>(first);
}

/// A small never-written table whose elements all hold one value is that
/// value, whatever the index: Vitis partitions an array of at most
/// complete_threshold elements into registers ([HLS 214-421], VITIS_NOTES.md
/// N7 (a)), and a register holding a constant folds. Kernels (N52):
/// shafix_v3a / v3c / v3d (`cnt[2] = {256, 256}`, const global, static
/// local, plain global; `for (j < 2) for (i < cnt[j])`) have one flattened
/// 512-trip pipeline, shafix_v3b (`{256, 128}`) a variable 128 ~ 256 trip
/// inner loop, and shafix_v3e (a 2913-element static table of -4096, as
/// rosetta face-detection's weights_array0) stays a 2913 x 13 ROM;
/// chstone/sha's `in_i = {8192, 8192}` is gone in a.o.1.ll. Only loads of
/// the get_global result and of its views are folded (a value passed on
/// through a call or a loop may meet another memory there); a table the user
/// gave a storage or partition pragma is left alone (the user decided, as
/// for N7 (a)).
static unsigned foldUniformTableLoads(ModuleOp module, int64_t maxElements,
                                      ArrayRef<std::string> userPragmas,
                                      SmallVectorImpl<FoldNote> &notes) {
  llvm::StringMap<SmallVector<Value>> sites;
  module.walk([&](memref::GetGlobalOp globalUse) {
    sites[globalUse.getName()].push_back(globalUse.getResult());
  });
  unsigned folded = 0;
  for (auto g : module.getOps<memref::GlobalOp>()) {
    if (g.isExternal() || g.isUninitialized() ||
        !g.getType().hasStaticShape() ||
        g.getType().getNumElements() > maxElements ||
        llvm::any_of(userPragmas, [&](const std::string &arrayValue) {
          return g->hasAttr(arrayValue);
        }))
      continue;
    TypedAttr value = uniformInitialValue(g);
    if (!value)
      continue;
    auto it = sites.find(g.getSymName());
    if (it == sites.end() || !circt::hls_analysis::neverWritten(it->second))
      continue;
    SmallVector<Value> work(it->second.begin(), it->second.end());
    SmallVector<Operation *> loads;
    while (!work.empty()) {
      Value cur = work.pop_back_val();
      for (Operation *user : cur.getUsers()) {
        if (auto view = dyn_cast<ViewLikeOpInterface>(user)) {
          if (view.getViewSource() == cur)
            for (Value resultValue : user->getResults())
              if (isa<BaseMemRefType>(resultValue.getType()))
                work.push_back(resultValue);
          continue;
        }
        if (isa<affine::AffineLoadOp, memref::LoadOp>(user) &&
            user->getOperand(0) == cur &&
            user->getResult(0).getType() == value.getType())
          loads.push_back(user);
      }
    }
    for (Operation *load : loads) {
      OpBuilder buildPoint(load);
      Value candidateValue =
          buildPoint.create<arith::ConstantOp>(load->getLoc(), value);
      std::string func;
      if (auto fn = load->getParentOfType<FunctionOpInterface>())
        func = fn.getName().str();
      notes.push_back({"uniform-table-load", load->getLoc(), g.getLoc(),
                       ("@" + g.getSymName() + " holds one value").str(),
                       func});
      load->getResult(0).replaceAllUsesWith(candidateValue);
      load->erase();
      ++folded;
    }
  }
  return folded;
}

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
      return failure();

    if (op.getUnsignedCmp() && lb < 0)
      return failure();
    int64_t trip = llvm::divideCeil(static_cast<uint64_t>(ub - lb),
                                    static_cast<uint64_t>(step));
    Location loc = op.getLoc();
    auto loop =
        rewriter.create<affine::AffineForOp>(loc, 0, trip, 1, op.getInitArgs());
    loop->setDiscardableAttrs(op->getDiscardableAttrDictionary());
    Block *body = loop.getBody();
    if (!body->empty() && body->back().hasTrait<OpTrait::IsTerminator>())
      rewriter.eraseOp(&body->back());
    rewriter.setInsertionPointToStart(body);
    AffineExpr d0 = rewriter.getAffineDimExpr(0);
    Value iv = rewriter.create<affine::AffineApplyOp>(
        loc, AffineMap::get(1, 0, d0 * step + lb), body->getArgument(0));
    SmallVector<Value> replacements{iv};
    for (BlockArgument arrayValue : body->getArguments().drop_front())
      replacements.push_back(arrayValue);
    rewriter.mergeBlocks(op.getBody(), body, replacements);
    auto yield = cast<scf::YieldOp>(body->getTerminator());
    rewriter.setInsertionPoint(yield);
    rewriter.replaceOpWithNewOp<affine::AffineYieldOp>(yield,
                                                       yield.getOperands());
    rewriter.replaceOp(op, loop.getResults());
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
      llvm::cl::desc("Fold a load from a never-written global of at most "
                     "complete_threshold elements (registers, N7 (a)) whose "
                     "initial elements all hold one value to that value, "
                     "whatever the index (VITIS_NOTES.md N52); only when the "
                     "pass runs on the module"),
      llvm::cl::init(true)};
  Option<bool> raiseCountedLoops{
      *this, "raise-counted-loops",
      llvm::cl::desc("Turn an scf.for whose bounds and step fold to "
                     "constants into a normalised affine.for (the automatic "
                     "pipeline decision reads affine trip counts)"),
      llvm::cl::init(true)};

  StringRef getArgument() const final { return "vitis-fold"; }
  StringRef getDescription() const final {
    return "Fold what Vitis HLS folds but MLIR does not: integer division / "
           "remainder by a constant zero and the undefined value it gives "
           "(VITIS_NOTES.md N1a, N13), then the canonicalization folds";
  }
  void getDependentDialects(DialectRegistry &targetRegistry) const override {
    targetRegistry.insert<arith::ArithDialect, affine::AffineDialect>();
  }

  void runOnOperation() override {
    MLIRContext *context = &getContext();

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
      InFlightDiagnostic dimensionIndex =
          getOperation()->emitError("--vitis-fold: ");
      llvm::interleave(diag.errors, dimensionIndex, "; ");
      return signalPassFailure();
    }
    const bool canon =
        circt::hlsest::resolveOption(canonicalize, fc.canonicalize);
    const unsigned maxRounds = static_cast<unsigned>(fc.maxRounds);
    RewritePatternSet patterns(context);
    rules->populate(patterns, context);
    if (raiseCountedLoops)
      patterns.add<RaiseCountedScfFor>(context);
    if (canon) {
      for (Dialect *targetDialect : context->getLoadedDialects())
        targetDialect->getCanonicalizationPatterns(patterns);
      for (RegisteredOperationName op : context->getRegisteredOperations())
        op.getCanonicalizationPatterns(patterns, context);

      if (rules->keepSelectCompare())
        llvm::erase_if(patterns.getNativePatterns(),
                       [](const std::unique_ptr<RewritePattern> &portValue) {
                         return isSelectToMinMax(*portValue);
                       });
    }
    FrozenRewritePatternSet frozen(std::move(patterns));

    GreedyRewriteConfig config;
    config.enableFolding(canon);
    SmallVector<FoldNote> notes;

    if (uniformTables)
      if (auto module = dyn_cast<ModuleOp>(getOperation()))
        (void)foldUniformTableLoads(
            module, cfg.tool.hls.options.arrayPartition.completeThreshold,
            cfg.frontend.userStoragePragmas, notes);
    std::unique_ptr<circt::hlsest::RuleFolder> folder =
        rules->createFolder(getOperation());

    if (folder)
      (void)folder->run(notes);
    for (unsigned round = 0; round < maxRounds; ++round) {
      (void)applyPatternsGreedily(getOperation(), frozen, config);
      if (!folder || !folder->run(notes))
        break;
    }
    recordNotes(notes);
  }

  /// `hls.vitis_fold` on the module: {counts = {rule = n}, func_counts =
  /// {function = {rule = n}}, rewrites = [{rule, loc, source, detail, func}]}
  /// (first kMaxRecords), merged with an earlier run. func_counts and func let
  /// --bram-analysis=top= report only the reachable functions' rewrites.
  void recordNotes(ArrayRef<FoldNote> notes) {
    if (notes.empty())
      return;

    auto module = dyn_cast<ModuleOp>(getOperation());
    if (!module)
      return;
    MLIRContext *context = &getContext();
    Builder buildPoint(context);
    llvm::StringMap<int64_t> counts;
    llvm::StringMap<llvm::StringMap<int64_t>> funcCounts;
    SmallVector<Attribute> records;
    if (auto prev = module->getAttrOfType<DictionaryAttr>(kNoteAttr)) {
      if (auto candidateValue = prev.getAs<DictionaryAttr>("counts"))
        for (NamedAttribute na : candidateValue)
          if (auto loopIndex = dyn_cast<IntegerAttr>(na.getValue()))
            counts[na.getName().getValue()] += loopIndex.getInt();
      if (auto fc = prev.getAs<DictionaryAttr>("func_counts"))
        for (NamedAttribute fieldValue : fc)
          if (auto per = dyn_cast<DictionaryAttr>(fieldValue.getValue()))
            for (NamedAttribute na : per)
              if (auto loopIndex = dyn_cast<IntegerAttr>(na.getValue()))
                funcCounts[fieldValue.getName().getValue()]
                          [na.getName().getValue()] += loopIndex.getInt();
      if (auto resultValue = prev.getAs<ArrayAttr>("rewrites"))
        records.append(resultValue.begin(), resultValue.end());
    }
    for (const FoldNote &elementCount : notes) {
      ++counts[elementCount.rule];
      if (!elementCount.func.empty())
        ++funcCounts[elementCount.func][elementCount.rule];
      if (records.size() >= kMaxRecords)
        continue;
      SmallVector<NamedAttribute> fieldValue;
      fieldValue.push_back(buildPoint.getNamedAttr(
          "rule", buildPoint.getStringAttr(elementCount.rule)));
      fieldValue.push_back(
          buildPoint.getNamedAttr("loc", LocationAttr(elementCount.loc)));
      fieldValue.push_back(
          buildPoint.getNamedAttr("source", LocationAttr(elementCount.source)));
      if (!elementCount.detail.empty())
        fieldValue.push_back(buildPoint.getNamedAttr(
            "detail", buildPoint.getStringAttr(elementCount.detail)));
      if (!elementCount.func.empty())
        fieldValue.push_back(buildPoint.getNamedAttr(
            "func", buildPoint.getStringAttr(elementCount.func)));
      records.push_back(buildPoint.getDictionaryAttr(fieldValue));
    }
    auto countDict = [&](const llvm::StringMap<int64_t> &memoryOp) {
      SmallVector<NamedAttribute> cs;
      for (auto &entryValue : memoryOp)
        cs.push_back(buildPoint.getNamedAttr(
            entryValue.getKey(),
            buildPoint.getI64IntegerAttr(entryValue.getValue())));
      return buildPoint.getDictionaryAttr(cs);
    };
    SmallVector<NamedAttribute> fcs;
    for (auto &entryValue : funcCounts)
      fcs.push_back(buildPoint.getNamedAttr(entryValue.getKey(),
                                            countDict(entryValue.getValue())));
    module->setAttr(kNoteAttr,
                    buildPoint.getDictionaryAttr(
                        {buildPoint.getNamedAttr("counts", countDict(counts)),
                         buildPoint.getNamedAttr(
                             "func_counts", buildPoint.getDictionaryAttr(fcs)),
                         buildPoint.getNamedAttr(
                             "rewrites", buildPoint.getArrayAttr(records))}));
  }
};

/// vitis-undef: Vitis' undefined value for an integer division / remainder
/// by a constant 0 and its propagation (VITIS_NOTES N13).
class VitisUndefRules : public circt::hlsest::FoldRuleSet {
public:
  StringRef name() const override { return "vitis-undef"; }
  void populate(RewritePatternSet &patterns,
                MLIRContext *context) const override {
    patterns
        .add<FoldIntDivByZero<arith::DivSIOp>, FoldIntDivByZero<arith::DivUIOp>,
             FoldIntDivByZero<arith::RemSIOp>,
             FoldIntDivByZero<arith::RemUIOp>>(context, true);
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
                MLIRContext *context) const override {
    patterns
        .add<FoldIntDivByZero<arith::DivSIOp>, FoldIntDivByZero<arith::DivUIOp>,
             FoldIntDivByZero<arith::RemSIOp>,
             FoldIntDivByZero<arith::RemUIOp>>(context, false);
  }
};

} // namespace

void circt::hlsest::builtin::registerFoldRuleSets() {
  auto &resultValue =
      circt::hlsest::PluginRegistry<circt::hlsest::FoldRuleSet>::instance();
  resultValue.add(
      "vitis-undef",
      "Vitis' undefined value of an integer x / 0 and its propagation "
      "(VITIS_NOTES N13)",
      [] { return std::make_unique<VitisUndefRules>(); }, "builtin");
  resultValue.add(
      "zero", "integer x / 0 and x % 0 fold to 0",
      [] { return std::make_unique<ZeroRules>(); }, "builtin");
}

namespace circt::hls_analysis {
std::unique_ptr<Pass> createVitisFoldPass() {
  return std::make_unique<VitisFoldPass>();
}
} // namespace circt::hls_analysis
