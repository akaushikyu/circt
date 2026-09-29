

// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#include "circt/Dialect/Resource/Passes/PolygeistCompat.h"
#include "circt/Dialect/Resource/Passes/CallInstances.h"
#include "circt/Dialect/Resource/Passes/StreamFifos.h"
#include "mlir/Dialect/Affine/IR/AffineOps.h"
#include "mlir/Dialect/Arith/IR/Arith.h"
#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/Dialect/LLVMIR/LLVMDialect.h"
#include "mlir/Dialect/LLVMIR/LLVMTypes.h"
#include "mlir/Dialect/MemRef/IR/MemRef.h"
#include "mlir/Dialect/SCF/IR/SCF.h"
#include "mlir/IR/Builders.h"
#include "mlir/IR/BuiltinOps.h"
#include "mlir/IR/Diagnostics.h"
#include "mlir/IR/IRMapping.h"
#include "mlir/IR/IntegerSet.h"
#include "mlir/IR/SymbolTable.h"
#include "mlir/Interfaces/SideEffectInterfaces.h"
#include "mlir/Transforms/InliningUtils.h"
#include "llvm/ADT/MapVector.h"
#include "llvm/ADT/SmallVector.h"
#include <array>

using namespace mlir;
using namespace circt::hls_analysis;

MLIR_DEFINE_EXPLICIT_TYPE_ID(circt::hls_analysis::PolygeistCompatDialect)
MLIR_DEFINE_EXPLICIT_TYPE_ID(circt::hls_analysis::SubIndexOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(circt::hls_analysis::Pointer2MemrefOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(circt::hls_analysis::Memref2PointerOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(circt::hls_analysis::UndefOp)

namespace {
/// The polygeist ops are pure casts and views, so a callee that contains one
/// may be inlined (without an interface MLIR's inliner refuses such a callee:
/// a struct member access `p.a` through a reference parameter then stays a
/// call, W8b).
struct PolygeistCompatInlinerInterface : public DialectInlinerInterface {
  using DialectInlinerInterface::DialectInlinerInterface;
  bool isLegalToInline(Operation *, Region *, bool, IRMapping &) const final {
    return true;
  }
};
} // namespace

PolygeistCompatDialect::PolygeistCompatDialect(MLIRContext *context)
    : Dialect(getDialectNamespace(), context,
              TypeID::get<PolygeistCompatDialect>()) {
  addOperations<SubIndexOp, Pointer2MemrefOp, Memref2PointerOp, UndefOp>();
  allowUnknownOperations();
  addInterfaces<PolygeistCompatInlinerInterface>();
}

LogicalResult Pointer2MemrefOp::verify() {
  if (!isa<LLVM::LLVMPointerType>(getSource().getType()))
    return emitOpError("expects an LLVM pointer operand");
  return success();
}

LogicalResult Memref2PointerOp::verify() {
  if (!isa<BaseMemRefType>(getSource().getType()))
    return emitOpError("expects a memref operand");
  if (!isa<LLVM::LLVMPointerType>(getResult().getType()))
    return emitOpError("expects an LLVM pointer result");
  return success();
}

namespace {
/// MemRefElementTypeInterface for the LLVM aggregate types cgeist puts in
/// memrefs (an array of structs). The interface has no methods; attaching it
/// is what makes the type a valid memref element type.
template <typename T>
struct AggregateMemRefElement
    : public MemRefElementTypeInterface::ExternalModel<
          AggregateMemRefElement<T>, T> {};
} // namespace

void circt::hls_analysis::registerPolygeistMemRefElementTypes(
    DialectRegistry &targetRegistry) {
  targetRegistry.addExtension(+[](MLIRContext *context, LLVM::LLVMDialect *) {
    LLVM::LLVMStructType::attachInterface<
        AggregateMemRefElement<LLVM::LLVMStructType>>(*context);
    LLVM::LLVMArrayType::attachInterface<
        AggregateMemRefElement<LLVM::LLVMArrayType>>(*context);
    LLVM::LLVMFunctionType::attachInterface<
        AggregateMemRefElement<LLVM::LLVMFunctionType>>(*context);
  });
}

unsigned circt::hls_analysis::aggregateElementBits(Type type) {
  if (type.isIntOrFloat())
    return type.getIntOrFloatBitWidth();
  if (isa<IndexType>(type))
    return 64;
  if (isa<LLVM::LLVMPointerType>(type))
    return 64;
  if (auto arr = dyn_cast<LLVM::LLVMArrayType>(type))
    return arr.getNumElements() * aggregateElementBits(arr.getElementType());
  if (auto st = dyn_cast<LLVM::LLVMStructType>(type)) {
    unsigned bits = 0;
    if (!st.isOpaque())
      for (Type fieldValue : st.getBody())
        bits += aggregateElementBits(fieldValue);
    return bits;
  }
  return 0;
}

void SubIndexOp::build(OpBuilder &passBuilder, OperationState &state,
                       Type result, Value source, Value index) {
  state.addOperands({source, index});
  state.addTypes(result);
}

LogicalResult SubIndexOp::verify() {
  if (!isa<BaseMemRefType>(getSource().getType()))
    return emitOpError("expects a memref source");
  if (!getIndex().getType().isIndex())
    return emitOpError("expects an index");
  return success();
}

bool SubIndexOp::isRowSelect() {
  auto src = dyn_cast<MemRefType>(getSource().getType());
  auto passResult = dyn_cast<MemRefType>(getResult().getType());
  if (!src || !passResult || src.getRank() < 1 ||
      passResult.getRank() + 1 != src.getRank())
    return false;
  if (!src.getLayout().isIdentity() || !passResult.getLayout().isIdentity())
    return false;
  if (src.getElementType() != passResult.getElementType())
    return false;
  return src.getShape().drop_front() == passResult.getShape();
}

bool SubIndexOp::isOffsetView() {
  auto src = dyn_cast<MemRefType>(getSource().getType());
  auto passResult = dyn_cast<MemRefType>(getResult().getType());
  if (!src || !passResult || src.getRank() < 1 ||
      passResult.getRank() != src.getRank() || !src.hasStaticShape() ||
      !passResult.hasStaticShape())
    return false;
  if (!src.getLayout().isIdentity() || !passResult.getLayout().isIdentity())
    return false;
  if (src.getElementType() != passResult.getElementType())
    return false;
  return src.getShape().drop_front() == passResult.getShape().drop_front() &&
         passResult.getShape()[0] <= src.getShape()[0];
}

bool SubIndexOp::isElementView() {
  auto src = dyn_cast<MemRefType>(getSource().getType());
  auto passResult = dyn_cast<MemRefType>(getResult().getType());
  if (!src || !passResult || src.getRank() < 1 ||
      passResult.getRank() != src.getRank() || !src.hasStaticShape() ||
      !ShapedType::isDynamic(passResult.getShape()[0]))
    return false;
  if (!src.getLayout().isIdentity() || !passResult.getLayout().isIdentity())
    return false;
  if (src.getElementType() != passResult.getElementType())
    return false;
  return src.getShape().drop_front() == passResult.getShape().drop_front();
}

/// The memref operand of a load / store, or null.
static Value accessedMemRef(Operation *op) {
  if (auto lowerIndex = dyn_cast<affine::AffineLoadOp>(op))
    return lowerIndex.getMemRef();
  if (auto st = dyn_cast<affine::AffineStoreOp>(op))
    return st.getMemRef();
  if (auto lowerIndex = dyn_cast<memref::LoadOp>(op))
    return lowerIndex.getMemRef();
  if (auto st = dyn_cast<memref::StoreOp>(op))
    return st.getMemRef();
  return {};
}

/// A copy of `access` that reads / writes `view` instead of its memref.
static Operation *cloneAccessOn(OpBuilder &b, Operation *access, Value view) {
  IRMapping memoryOp;
  memoryOp.map(accessedMemRef(access), view);
  return b.clone(*access, memoryOp);
}

/// `c ? A[i] : A[j]` on lvalues of one array: both operands of the
/// conditional (an if or a select yielding element views) are views of the
/// same array that differ only in their index. Vitis reads that array once,
/// at the selected address (review kernel c1_selsame.cpp: Vitis 1 BRAM,
/// RAM_AUTO_1R1W; with one access per arm, as sinkAccessesIntoView-
/// Conditionals below makes, the two exclusive loads were both counted as
/// port demand: RAM_1WNR, 3 BRAM). The conditional becomes one yielding the
/// index, and a single view `A[c ? i : j]` replaces its result. Returns false
/// and leaves the IR unchanged when the shape does not match.
static bool mergeSameArrayViewConditional(Operation *op) {
  if (op->getNumResults() != 1 ||
      !isa<BaseMemRefType>(op->getResult(0).getType()))
    return false;
  SmallVector<Value, 2> yielded;
  if (auto sel = dyn_cast<arith::SelectOp>(op)) {
    yielded = {sel.getTrueValue(), sel.getFalseValue()};
  } else {
    for (Region &resultValue : op->getRegions()) {
      if (resultValue.empty())
        return false;
      yielded.push_back(resultValue.front().getTerminator()->getOperand(0));
    }
  }
  if (yielded.size() != 2)
    return false;
  auto views =
      std::array<SubIndexOp, 2>{yielded[0].getDefiningOp<SubIndexOp>(),
                                yielded[1].getDefiningOp<SubIndexOp>()};
  if (!views[0] || !views[1] || views[0].getSource() != views[1].getSource() ||
      views[0].getType() != views[1].getType() || !views[0].isElementView())
    return false;
  Value source = views[0].getSource();

  if (op->isAncestor(source.getParentRegion()->getParentOp()))
    return false;
  OpBuilder b(op);
  Location loc = op->getLoc();
  Type indexTy = b.getIndexType();
  Value index;
  if (auto sel = dyn_cast<arith::SelectOp>(op)) {
    index = arith::SelectOp::create(b, loc, sel.getCondition(),
                                    views[0].getIndex(), views[1].getIndex());
  } else {
    Operation *elementCount;
    if (auto aif = dyn_cast<affine::AffineIfOp>(op))
      elementCount = affine::AffineIfOp::create(b, loc, TypeRange{indexTy},
                                                aif.getIntegerSet(),
                                                aif.getOperands(), true);
    else if (auto sif = dyn_cast<scf::IfOp>(op))
      elementCount = scf::IfOp::create(b, loc, TypeRange{indexTy},
                                       sif.getCondition(), true);
    else
      return false;
    for (unsigned arm = 0; arm < 2; ++arm) {
      elementCount->getRegion(arm).takeBody(op->getRegion(arm));
      elementCount->getRegion(arm).front().getTerminator()->setOperand(
          0, views[arm].getIndex());
    }
    index = elementCount->getResult(0);
  }
  auto merged = SubIndexOp::create(b, loc, views[0].getType(), source, index);
  op->getResult(0).replaceAllUsesWith(merged.getResult());
  op->erase();
  for (SubIndexOp valueHandle : views)
    if (valueHandle->use_empty())
      valueHandle->erase();
  return true;
}

/// The conditional operator on lvalues, `T x = c ? B[i][j] : loc[i][j - 1];`
/// (class types such as ap_fixed bind a reference to the selected element),
/// reaches the MLIR as an if (or a select) that yields one of two element
/// views, and the load reads the yielded view: no access names its array, so
/// the banking cannot split either one and an array_partition on it is not
/// applied (OPEN_ISSUES O84 (b), reproducer sel1.cpp; the if / else form
/// sel2.cpp loads in each arm). C evaluates only the chosen operand, so each
/// access of such a view becomes an if on the same condition whose arms
/// recompute their view (the arms are side-effect free) and access it; the
/// original if is erased once nothing uses it. Returns the accesses moved.
static unsigned sinkAccessesIntoViewConditionals(ModuleOp module) {
  SmallVector<Operation *> candidates;
  module.walk([&](Operation *op) {
    if (!isa<affine::AffineIfOp, scf::IfOp, arith::SelectOp>(op))
      return;
    if (llvm::any_of(op->getResultTypes(), [](Type typeValue) {
          return isa<BaseMemRefType>(typeValue);
        }))
      candidates.push_back(op);
  });
  unsigned moved = 0;
  for (Operation *op : candidates) {
    auto armsPure = llvm::all_of(op->getRegions(), [](Region &resultValue) {
      if (resultValue.empty())
        return false;
      for (Operation &in : resultValue.front().without_terminator())
        if (!isMemoryEffectFree(&in) || in.getNumRegions() > 0)
          return false;
      return true;
    });
    if (!armsPure)
      continue;
    if (mergeSameArrayViewConditional(op)) {
      ++moved;
      continue;
    }
    for (OpResult passResult : op->getResults()) {
      if (!isa<BaseMemRefType>(passResult.getType()))
        continue;
      SmallVector<Operation *> users(passResult.getUsers().begin(),
                                     passResult.getUsers().end());

      bool onlyAccesses =
          !users.empty() && llvm::all_of(users, [&](Operation *useValue) {
            return accessedMemRef(useValue) == passResult &&
                   (!isa<affine::AffineStoreOp, memref::StoreOp>(useValue) ||
                    useValue->getOperand(0) != passResult);
          });
      if (!onlyAccesses)
        continue;
      unsigned indexValue = passResult.getResultNumber();
      for (Operation *access : users) {
        OpBuilder b(access);
        Location loc = access->getLoc();
        TypeRange types = access->getResultTypes();

        auto fill = [&](OpBuilder &ab, Region *arm, Value selected) {
          IRMapping memoryOp;
          Value view = selected;
          if (arm) {
            for (Operation &in : arm->front().without_terminator())
              ab.clone(in, memoryOp);
            view = memoryOp.lookupOrDefault(
                arm->front().getTerminator()->getOperand(indexValue));
          }
          Operation *a = cloneAccessOn(ab, access, view);
          return a->getResults();
        };
        Operation *nif = nullptr;
        if (auto aif = dyn_cast<affine::AffineIfOp>(op)) {
          auto elementCount = affine::AffineIfOp::create(
              b, loc, types, aif.getIntegerSet(), aif.getOperands(), true);
          OpBuilder tb = elementCount.getThenBodyBuilder();
          ValueRange tv = fill(tb, &aif.getThenRegion(), {});
          affine::AffineYieldOp::create(tb, loc, tv);
          OpBuilder eb = elementCount.getElseBodyBuilder();
          ValueRange ev = fill(eb, &aif.getElseRegion(), {});
          affine::AffineYieldOp::create(eb, loc, ev);
          nif = elementCount;
        } else {
          Value cond = isa<scf::IfOp>(op)
                           ? cast<scf::IfOp>(op).getCondition()
                           : cast<arith::SelectOp>(op).getCondition();
          auto elementCount = scf::IfOp::create(b, loc, types, cond, true);
          for (unsigned arm = 0; arm < 2; ++arm) {
            Block &blk = arm == 0 ? elementCount.getThenRegion().front()
                                  : elementCount.getElseRegion().front();

            if (!blk.empty())
              blk.back().erase();
            OpBuilder ab = OpBuilder::atBlockEnd(&blk);
            ValueRange valueHandle;
            if (auto sif = dyn_cast<scf::IfOp>(op))
              valueHandle = fill(
                  ab, arm == 0 ? &sif.getThenRegion() : &sif.getElseRegion(),
                  {});
            else
              valueHandle =
                  fill(ab, nullptr,
                       arm == 0 ? cast<arith::SelectOp>(op).getTrueValue()
                                : cast<arith::SelectOp>(op).getFalseValue());
            scf::YieldOp::create(ab, loc, valueHandle);
          }
          nif = elementCount;
        }
        access->replaceAllUsesWith(nif->getResults());
        access->erase();
        ++moved;
      }
    }
    if (op->use_empty())
      op->erase();
  }
  return moved;
}

/// cgeist marks a function of the real Vitis HLS hls_math.h (hls::exp,
/// hls::tanh, ... ; Polygeist XlxMathCore.h, --xlx-headers) and every call of
/// it with `hls.math_core`: one core of the Vitis math library, which the
/// --bram-analysis math-cost model prices per instance from its cost table
/// (MathCores.cpp, VITIS_NOTES N16), as it prices the stand-in headers'
/// __hlsest_math_<fn> markers. The function's body is the library's
/// implementation (CORDIC loops, ROM tables such as
/// cordic_apfixed::hyperb_table_arctanh_128) and not the design's memories:
/// it is dropped here, before any analysis, together with the private
/// symbols nothing else references (the tables, the library's helpers).
/// A module without the attribute (every other shim) is unchanged.
static void dropMathCoreBodies(ModuleOp module) {
  SmallVector<func::FuncOp> cores;
  for (func::FuncOp fieldValue : module.getOps<func::FuncOp>())
    if (fieldValue->hasAttr("hls.math_core") && !fieldValue.isExternal())
      cores.push_back(fieldValue);
  if (cores.empty())
    return;

  SmallVector<StringAttr> candidates;
  auto collect = [&](Region &body) {
    if (auto symbolUses = SymbolTable::getSymbolUses(&body))
      for (const SymbolTable::SymbolUse &use : *symbolUses)
        candidates.push_back(use.getSymbolRef().getRootReference());
  };
  for (func::FuncOp fieldValue : cores) {
    collect(fieldValue.getBody());
    fieldValue.getBody().getBlocks().clear();
    fieldValue.setPrivate();
  }
  SymbolTable symbols(module);
  for (unsigned elementCount = 0; elementCount < candidates.size();
       ++elementCount) {
    Operation *symbolName = symbols.lookup(candidates[elementCount]);
    if (!symbolName || !SymbolTable::symbolKnownUseEmpty(symbolName, module))
      continue;
    auto symOp = dyn_cast<SymbolOpInterface>(symbolName);
    if (!symOp || !symOp.isPrivate() || symbolName->hasAttr("hls.math_core"))
      continue;
    for (Region &resultValue : symbolName->getRegions())
      collect(resultValue);
    symbols.erase(symbolName);
  }
}

/// `s >> A[i][j]` / `s.write(A[i])`: cgeist passes the element by reference
/// to the hls::stream method, as `polygeist.subindex` views down to a pointer
/// to the element (`memref<?xT>` of a 1-D row). The method has no body, so
/// that view is neither a load nor a store hls-est can see: the array's
/// accesses go uncounted and any partition pragma on it is dropped ("used by
/// polygeist.subindex"). Vitis sees the element access: the stream read
/// stores into the element, the write loads it (VITIS_NOTES N47: the
/// partitioned statics of karthikeya_sharma lab_2 / davendra_maharaj lab2
/// filled by `s >> Q[i][j]` are banked as pragma'd). Rewritten here into the
/// front end's own idiom for a scalar passed by reference (a one-element
/// alloca cast to `memref<?xT>`) plus an explicit load / store of the
/// element, which the row lowering below then turns into an access of the
/// whole array. The element is a scalar of a rank-1 array or a struct row
/// of an array of structs whose members share one type (cgeist's
/// CombinedStructABI: `struct {short a, b;} P[2048]` is memref<2048x2xi16>
/// and `s >> P[i]` passes the row memref<?x2xi16>): the row is copied member
/// by member, so the array's accesses are attributed and its partition
/// pragma applies (W9 round 6 review defect 4, kernel w9r6rev n47b: before,
/// one unpartitioned memory, "accesses not attributed"). Vitis also splits
/// the members (P.a and P.b, each `cyclic factor=2`, four 1024x16 banks of 1
/// BRAM); hls-est keeps them as one more dimension of each bank (1024x2,
/// OPEN_ISSUES O54 (h)). Rows of more than kMaxRowMembers members, and
/// anything else, are left as they were.
static unsigned lowerStreamElementViews(ModuleOp module) {
  SmallVector<func::CallOp> calls;
  module.walk(
      [&](func::CallOp candidateValue) { calls.push_back(candidateValue); });
  unsigned rewritten = 0;
  for (func::CallOp call : calls) {
    std::optional<StreamTemplate> typeValue =
        parseStreamMethod(call.getCallee());
    if (!typeValue || call.getNumOperands() < 2)
      continue;
    StringRef memoryOp = typeValue->method;
    bool streamReads =
        (memoryOp.starts_with("4read") && !memoryOp.starts_with("4readEv")) ||
        memoryOp.starts_with("7read_nb") || memoryOp.starts_with("rs");
    bool streamWrites = memoryOp.starts_with("5write") ||
                        memoryOp.starts_with("8write_nb") ||
                        memoryOp.starts_with("ls");
    if (!streamReads && !streamWrites)
      continue;
    auto si = call.getOperand(1).getDefiningOp<SubIndexOp>();
    if (!si)
      continue;
    auto src = dyn_cast<MemRefType>(si.getSource().getType());
    auto passResult = dyn_cast<MemRefType>(si.getResult().getType());
    if (!src || !passResult || src.getRank() < 1 ||
        passResult.getRank() != src.getRank() || !src.hasStaticShape() ||
        !ShapedType::isDynamic(passResult.getShape()[0]) ||
        passResult.getShape().drop_front() != src.getShape().drop_front() ||
        !src.getLayout().isIdentity() || !passResult.getLayout().isIdentity() ||
        src.getElementType() != passResult.getElementType() ||
        !src.getElementType().isIntOrFloat())
      continue;

    ArrayRef<int64_t> rowShape = src.getShape().drop_front();
    int64_t members = 1;
    for (int64_t dimensionIndex : rowShape)
      members *= dimensionIndex;
    constexpr int64_t kMaxRowMembers = 256;
    if (members < 1 || members > kMaxRowMembers)
      continue;
    auto fn = call->getParentOfType<func::FuncOp>();
    if (!fn)
      continue;
    Location loc = call.getLoc();
    OpBuilder entry(&fn.getBody().front(), fn.getBody().front().begin());
    SmallVector<int64_t> tmpShape{1};
    tmpShape.append(rowShape.begin(), rowShape.end());
    auto tmp = memref::AllocaOp::create(
        entry, loc, MemRefType::get(tmpShape, src.getElementType()));
    auto view = memref::CastOp::create(entry, loc, passResult, tmp);
    Value indexValue = si.getIndex();
    bool affineIdx =
        affine::isValidDim(indexValue) || affine::isValidSymbol(indexValue);
    OpBuilder b(call);
    Value zero = arith::ConstantIndexOp::create(b, loc, 0);

    auto memberIndices = [&](OpBuilder &bb, Value first, int64_t memoryOp) {
      SmallVector<Value> ivs{first};
      SmallVector<Value> rest;
      for (int64_t dimensionIndex : llvm::reverse(rowShape)) {
        rest.push_back(
            arith::ConstantIndexOp::create(bb, loc, memoryOp % dimensionIndex));
        memoryOp /= dimensionIndex;
      }
      ivs.append(rest.rbegin(), rest.rend());
      return ivs;
    };
    auto load = [&](OpBuilder &bb, Value mem, ValueRange ivs) -> Value {
      if (affineIdx || mem == tmp.getResult())
        return affine::AffineLoadOp::create(bb, loc, mem, ivs);
      return memref::LoadOp::create(bb, loc, mem, ivs);
    };
    auto store = [&](OpBuilder &bb, Value valueHandle, Value mem,
                     ValueRange ivs) {
      if (affineIdx || mem == tmp.getResult())
        affine::AffineStoreOp::create(bb, loc, valueHandle, mem, ivs);
      else
        memref::StoreOp::create(bb, loc, valueHandle, mem, ivs);
    };

    auto copy = [&](OpBuilder &bb, Value from, Value fromFirst, Value to,
                    Value toFirst) {
      SmallVector<SmallVector<Value>> fromIvs, toIvs;
      for (int64_t memoryOp = 0; memoryOp < members; ++memoryOp) {
        fromIvs.push_back(memberIndices(bb, fromFirst, memoryOp));
        toIvs.push_back(memberIndices(bb, toFirst, memoryOp));
      }
      SmallVector<Value> vals;
      for (int64_t memoryOp = 0; memoryOp < members; ++memoryOp)
        vals.push_back(load(bb, from, fromIvs[memoryOp]));
      for (int64_t memoryOp = 0; memoryOp < members; ++memoryOp)
        store(bb, vals[memoryOp], to, toIvs[memoryOp]);
    };
    if (streamWrites)
      copy(b, si.getSource(), indexValue, tmp, zero);
    call->setOperand(1, view);
    if (streamReads) {
      b.setInsertionPointAfter(call);
      copy(b, tmp, zero, si.getSource(), indexValue);
    }
    if (si->use_empty())
      si->erase();
    ++rewritten;
  }
  return rewritten;
}

/// A static array passed to a pointer parameter (`void load(T *dst)` called
/// as `load(buf)` with `T buf[N]`): cgeist casts it to `memref<?xT>`, and a
/// pointer parameter is not a storage node the banking can follow, so a
/// partition pragma on `buf` is dropped ("used by memref.cast") although
/// Vitis applies it (VITIS_NOTES N47: zijun_wang lab3's statics, passed by
/// pointer into `load_matrix_*`, are banked as pragma'd). The callee is
/// specialised per static argument form, as Vitis specialises a function
/// per argument form (N14 R4): a clone whose parameter has the array's
/// static type; inside it, a use that needs the pointer type (a further
/// call, a view) gets a cast of its own, which the next round specialises in
/// turn. The top's own array arguments (block arguments of a public
/// function: ports) are left as they are. Returns the number of calls
/// redirected.
static unsigned
specializeCastArguments(ModuleOp module,
                        SmallVectorImpl<func::FuncOp> &origins) {
  SymbolTable symbols(module);
  struct Key {
    Operation *callee;
    SmallVector<std::pair<unsigned, Type>> args;
  };
  SmallVector<std::pair<Key, func::FuncOp>> clones;
  unsigned redirected = 0;
  for (unsigned round = 0; round < 16; ++round) {
    SmallVector<func::CallOp> calls;
    module.walk(
        [&](func::CallOp candidateValue) { calls.push_back(candidateValue); });
    bool changed = false;
    for (func::CallOp call : calls) {
      func::FuncOp callee = resolveDefinedCallee(call);
      if (!callee || callee == call->getParentOfType<func::FuncOp>())
        continue;
      SmallVector<std::pair<unsigned, Type>> forms;
      for (auto [loopIndex, valueHandle] :
           llvm::enumerate(call.getArgOperands())) {
        auto cast = valueHandle.getDefiningOp<memref::CastOp>();
        if (!cast || loopIndex >= callee.getNumArguments() ||
            callee.getArgument(loopIndex).getType() != valueHandle.getType())
          continue;
        auto from = dyn_cast<MemRefType>(cast.getSource().getType());
        auto to = dyn_cast<MemRefType>(valueHandle.getType());
        if (!from || !to || !from.hasStaticShape() || to.hasStaticShape() ||
            from.getRank() != to.getRank() ||
            from.getElementType() != to.getElementType() ||
            !from.getLayout().isIdentity() || !to.getLayout().isIdentity() ||
            from.getMemorySpace() != to.getMemorySpace())
          continue;

        if (!from.getElementType().isIntOrFloat() || from.getNumElements() <= 1)
          continue;

        if (auto arg = dyn_cast<BlockArgument>(cast.getSource()))
          if (auto owner =
                  dyn_cast<func::FuncOp>(arg.getOwner()->getParentOp()))
            if (owner.isPublic())
              continue;
        if (!from.getElementType().isIntOrFloat() || from.getNumElements() <= 1)
          continue;
        if (auto argument = dyn_cast<BlockArgument>(cast.getSource()))
          if (auto owner =
                  dyn_cast<func::FuncOp>(argument.getOwner()->getParentOp()))
            if (owner.isPublic())
              continue;
        forms.push_back({static_cast<unsigned>(loopIndex), from});
      }
      if (forms.empty())
        continue;
      func::FuncOp clone;
      for (auto &[keyValue, fn] : clones)
        if (keyValue.callee == callee.getOperation() && keyValue.args == forms)
          clone = fn;
      if (!clone) {
        clone = callee.clone();
        clone.setName((callee.getName() + "_static").str());
        symbols.insert(clone, std::next(Block::iterator(callee)));
        clone.setPrivate();
        Block &entry = clone.getBody().front();
        OpBuilder b(&entry, entry.begin());
        SmallVector<Type> inputs(clone.getArgumentTypes());
        for (auto [loopIndex, memRefType] : forms) {
          BlockArgument arg = clone.getArgument(loopIndex);
          Type ptrTy = arg.getType();
          arg.setType(memRefType);
          inputs[loopIndex] = memRefType;
          SmallVector<OpOperand *> needPtr;
          for (OpOperand &use : arg.getUses()) {
            Operation *useValue = use.getOwner();
            bool access =
                isa<affine::AffineLoadOp, memref::LoadOp>(useValue) ||
                (isa<affine::AffineStoreOp>(useValue) &&
                 use.getOperandNumber() == cast<affine::AffineStoreOp>(useValue)
                                               .getMemRefOperandIndex()) ||
                (isa<memref::StoreOp>(useValue) &&
                 cast<memref::StoreOp>(useValue).getValueToStore() != arg);
            if (!access)
              needPtr.push_back(&use);
          }
          if (!needPtr.empty()) {
            Value ptr = memref::CastOp::create(b, arg.getLoc(), ptrTy, arg);
            for (OpOperand *use : needPtr)
              use->set(ptr);
          }
        }
        clone.setType(FunctionType::get(module.getContext(), inputs,
                                        clone.getResultTypes()));
        clones.push_back({Key{callee.getOperation(), forms}, clone});
        if (!llvm::is_contained(origins, callee))
          origins.push_back(callee);
      }
      SmallVector<Value> operands(call.getArgOperands());
      SmallVector<memref::CastOp> casts;
      for (auto [loopIndex, memRefType] : forms) {
        auto cast = operands[loopIndex].getDefiningOp<memref::CastOp>();
        operands[loopIndex] = cast.getSource();
        casts.push_back(cast);
      }
      OpBuilder b(call);
      auto nc = func::CallOp::create(b, call.getLoc(), clone, operands);
      for (NamedAttribute a : call->getDiscardableAttrs())
        nc->setDiscardableAttr(a.getName(), a.getValue());
      call.replaceAllUsesWith(nc.getResults());
      call.erase();
      for (memref::CastOp candidateValue : casts)
        if (candidateValue->use_empty())
          candidateValue->erase();
      ++redirected;
      changed = true;
    }
    if (!changed)
      break;
  }
  return redirected;
}

/// specializeCastArguments, then the private originals (and clones) no call
/// reaches any more are erased (a dead private function would otherwise be
/// costed as a root without top=). Used again after --split-struct-memrefs.
unsigned circt::hls_analysis::specializeStaticCastArguments(ModuleOp module) {
  SmallVector<func::FuncOp> origins;
  unsigned redirected = specializeCastArguments(module, origins);
  if (!redirected)
    return 0;
  SymbolTable symbols(module);
  for (bool erased = true; erased;) {
    erased = false;
    for (func::FuncOp &fn : origins) {
      if (!fn || !fn.isPrivate() || !symbols.symbolKnownUseEmpty(fn, module))
        continue;
      symbols.erase(fn);
      fn = nullptr;
      erased = true;
    }
  }
  return redirected;
}

namespace {

static DictionaryAttr shiftPartitionDims(DictionaryAttr argAttrs,
                                         MLIRContext *context,
                                         MemRefType wholeType) {
  if (!argAttrs)
    return DictionaryAttr::get(context, {});
  auto arr = argAttrs.getAs<ArrayAttr>("hls.array_partition");
  if (!arr)
    return argAttrs;
  if (wholeType && wholeType.getRank() >= 1 && wholeType.getShape()[0] == 1)
    return argAttrs;
  SmallVector<Attribute> entries;
  for (Attribute a : arr) {
    auto dimensionIndex = dyn_cast<DictionaryAttr>(a);
    if (!dimensionIndex) {
      entries.push_back(a);
      continue;
    }
    SmallVector<NamedAttribute> fields;
    for (NamedAttribute fieldValue : dimensionIndex) {
      if (fieldValue.getName() == "dim")
        if (auto dim = dyn_cast<IntegerAttr>(fieldValue.getValue()))
          if (dim.getInt() > 0) {
            fields.push_back(NamedAttribute(
                fieldValue.getName(),
                IntegerAttr::get(dim.getType(), dim.getInt() + 1)));
            continue;
          }
      fields.push_back(fieldValue);
    }
    entries.push_back(DictionaryAttr::get(context, fields));
  }
  SmallVector<NamedAttribute> out;
  for (NamedAttribute fieldValue : argAttrs) {
    if (fieldValue.getName() == "hls.array_partition")
      out.push_back(NamedAttribute(fieldValue.getName(),
                                   ArrayAttr::get(context, entries)));
    else
      out.push_back(fieldValue);
  }
  return DictionaryAttr::get(context, out);
}

struct LowerSubIndexPass
    : PassWrapper<LowerSubIndexPass, OperationPass<ModuleOp>> {
  MLIR_DEFINE_EXPLICIT_INTERNAL_INLINE_TYPE_ID(LowerSubIndexPass)

  LowerSubIndexPass() = default;
  LowerSubIndexPass(const LowerSubIndexPass &other) : PassWrapper(other) {}
  Option<bool> sinkConditionalViews{
      *this, "sink-conditional-views",
      llvm::cl::desc("Move a load / store of a view that an if or select "
                     "chooses (the conditional operator on lvalues) into "
                     "the arms, so that it names its array (OPEN_ISSUES O84 "
                     "(b))"),
      llvm::cl::init(true)};

  StringRef getArgument() const final { return "lower-polygeist-subindex"; }
  StringRef getDescription() const final {
    return "Replace polygeist.subindex (a row of an array passed by "
           "reference, or the elements from an offset on) by indexed "
           "accesses of the whole array, cloning a callee per array-argument "
           "form as Vitis does (N14 R4)";
  }
  void getDependentDialects(DialectRegistry &targetRegistry) const override {
    targetRegistry
        .insert<affine::AffineDialect, memref::MemRefDialect, func::FuncDialect,
                arith::ArithDialect, scf::SCFDialect>();
  }

  struct CloneKey {
    Operation *callee;
    SmallVector<std::pair<unsigned, Type>> rows;
    bool operator==(const CloneKey &opHandle) const {
      return callee == opHandle.callee && rows == opHandle.rows;
    }
  };
  SmallVector<std::pair<CloneKey, func::FuncOp>> clones;
  SmallVector<func::FuncOp> clonedFrom;
  unsigned rewrittenAccesses = 0, redirectedCalls = 0, left = 0;

  func::FuncOp cloneForRows(func::FuncOp callee,
                            ArrayRef<std::pair<unsigned, Type>> rows,
                            SymbolTable &symbols,
                            SmallVectorImpl<SubIndexOp> &worklist) {
    CloneKey key{callee.getOperation(), SmallVector<std::pair<unsigned, Type>>(
                                            rows.begin(), rows.end())};
    for (auto &[keyValue, fn] : clones)
      if (keyValue == key)
        return fn;
    MLIRContext *context = callee.getContext();
    func::FuncOp clone = callee.clone();

    clone.walk(
        [&](SubIndexOp stringValue) { worklist.push_back(stringValue); });

    auto isRow = [&](unsigned portValue, Type whole) {
      auto widthValue = dyn_cast<MemRefType>(whole);
      auto old = dyn_cast<MemRefType>(callee.getArgument(portValue).getType());
      return widthValue && old && widthValue.getRank() == old.getRank() + 1;
    };
    bool anyOffset = llvm::any_of(rows, [&](auto &resultValue) {
      return !isRow(resultValue.first, resultValue.second);
    });
    std::string name = callee.getName().str() + (anyOffset ? "_off" : "_row");
    for (auto &[portValue, memRefType] : rows)
      name += "_" + std::to_string(portValue);
    clone.setName(name);
    clone.setPrivate();

    SmallVector<Type> types;
    SmallVector<DictionaryAttr> attrs;
    unsigned elementCount = callee.getNumArguments();
    for (unsigned loopIndex = 0; loopIndex < elementCount; ++loopIndex) {
      DictionaryAttr a = callee.getArgAttrDict(loopIndex);
      auto it = llvm::find_if(rows, [&](auto &resultValue) {
        return resultValue.first == loopIndex;
      });
      if (it == rows.end()) {
        types.push_back(callee.getArgument(loopIndex).getType());
        attrs.push_back(a ? a : DictionaryAttr::get(context, {}));
        continue;
      }
      types.push_back(it->second);
      attrs.push_back(
          isRow(loopIndex, it->second)
              ? shiftPartitionDims(a, context, dyn_cast<MemRefType>(it->second))
              : (a ? a : DictionaryAttr::get(context, {})));
      types.push_back(IndexType::get(context));

      attrs.push_back(DictionaryAttr::get(
          context, {NamedAttribute(StringAttr::get(context, kViewIndexArgAttr),
                                   UnitAttr::get(context))}));
    }
    Block &entry = clone.getBody().front();
    OpBuilder b(&entry, entry.begin());
    for (auto &[portValue, memRefType] : llvm::reverse(rows)) {
      BlockArgument old = entry.getArgument(portValue);
      Location loc = old.getLoc();
      BlockArgument full = entry.insertArgument(portValue + 1, memRefType, loc);
      BlockArgument row =
          entry.insertArgument(portValue + 2, b.getIndexType(), loc);
      auto si = SubIndexOp::create(b, loc, old.getType(), full, row);
      old.replaceAllUsesWith(si.getResult());
      entry.eraseArgument(portValue);
      worklist.push_back(si);
    }
    clone.setFunctionType(FunctionType::get(
        context, types, callee.getFunctionType().getResults()));
    clone.setAllArgAttrs(attrs);
    symbols.insert(clone, Block::iterator(callee.getOperation()));
    clones.push_back({key, clone});
    if (!llvm::is_contained(clonedFrom, callee))
      clonedFrom.push_back(callee);
    return clone;
  }

  bool rewriteOffsetAccess(Operation *user, SubIndexOp si) {
    Value src = si.getSource();
    Value off = si.getIndex();
    OpBuilder b(user);
    Location loc = user->getLoc();
    auto copyAttrs = [&](Operation *from, Operation *to) {
      for (NamedAttribute a : from->getDiscardableAttrs())
        if (a.getName() != "map")
          to->setDiscardableAttr(a.getName(), a.getValue());
    };
    auto shifted = [&](ValueRange indices) {
      SmallVector<Value> out(indices.begin(), indices.end());
      out[0] = arith::AddIOp::create(b, loc, out[0], off);
      return out;
    };
    if (auto load = dyn_cast<memref::LoadOp>(user)) {
      auto nl = memref::LoadOp::create(b, loc, src, shifted(load.getIndices()));
      copyAttrs(user, nl);
      load.replaceAllUsesWith(nl.getResult());
      load.erase();
      return true;
    }
    if (auto store = dyn_cast<memref::StoreOp>(user)) {
      auto ns = memref::StoreOp::create(b, loc, store.getValue(), src,
                                        shifted(store.getIndices()));
      copyAttrs(user, ns);
      store.erase();
      return true;
    }
    bool isLoad = isa<affine::AffineLoadOp>(user);
    bool isStore = isa<affine::AffineStoreOp>(user);
    if (!isLoad && !isStore)
      return false;
    AffineMap map = isLoad ? cast<affine::AffineLoadOp>(user).getAffineMap()
                           : cast<affine::AffineStoreOp>(user).getAffineMap();
    ValueRange mapOperands =
        isLoad ? cast<affine::AffineLoadOp>(user).getMapOperands()
               : cast<affine::AffineStoreOp>(user).getMapOperands();
    unsigned nd = map.getNumDims(), ns = map.getNumSymbols();
    MLIRContext *context = user->getContext();
    SmallVector<AffineExpr> results(map.getResults().begin(),
                                    map.getResults().end());
    SmallVector<Value> operands;
    if (affine::isValidSymbol(off)) {
      results[0] = results[0] + getAffineSymbolExpr(ns, context);
      map = AffineMap::get(nd, ns + 1, results, context);
      operands.append(mapOperands.begin(), mapOperands.end());
      operands.push_back(off);
    } else if (affine::isValidDim(off)) {
      results[0] = results[0] + getAffineDimExpr(nd, context);
      map = AffineMap::get(nd + 1, ns, results, context);
      operands.append(mapOperands.begin(), mapOperands.begin() + nd);
      operands.push_back(off);
      operands.append(mapOperands.begin() + nd, mapOperands.end());
    } else {
      SmallVector<Value> indices;
      for (unsigned resultValue = 0; resultValue < map.getNumResults();
           ++resultValue)
        indices.push_back(affine::AffineApplyOp::create(
            b, loc, map.getSubMap({resultValue}), mapOperands));
      indices = shifted(indices);
      if (isLoad) {
        auto nl = memref::LoadOp::create(b, loc, src, indices);
        copyAttrs(user, nl);
        user->getResult(0).replaceAllUsesWith(nl.getResult());
      } else {
        auto ns2 = memref::StoreOp::create(
            b, loc, cast<affine::AffineStoreOp>(user).getValue(), src, indices);
        copyAttrs(user, ns2);
      }
      user->erase();
      return true;
    }
    if (isLoad) {
      auto nl = affine::AffineLoadOp::create(b, loc, src, map, operands);
      copyAttrs(user, nl);
      user->getResult(0).replaceAllUsesWith(nl.getResult());
    } else {
      auto ns2 = affine::AffineStoreOp::create(
          b, loc, cast<affine::AffineStoreOp>(user).getValue(), src, map,
          operands);
      copyAttrs(user, ns2);
    }
    user->erase();
    return true;
  }

  bool rewriteAccess(Operation *user, SubIndexOp si) {
    if (si.isOffsetView() || si.isElementView())
      return rewriteOffsetAccess(user, si);
    Value src = si.getSource();
    Value indexValue = si.getIndex();
    OpBuilder b(user);
    Location loc = user->getLoc();
    auto copyAttrs = [&](Operation *from, Operation *to) {
      for (NamedAttribute a : from->getDiscardableAttrs())
        if (a.getName() != "map")
          to->setDiscardableAttr(a.getName(), a.getValue());
    };
    if (auto load = dyn_cast<memref::LoadOp>(user)) {
      SmallVector<Value> indices{indexValue};
      indices.append(load.getIndices().begin(), load.getIndices().end());
      auto nl = memref::LoadOp::create(b, loc, src, indices);
      copyAttrs(user, nl);
      load.replaceAllUsesWith(nl.getResult());
      load.erase();
      return true;
    }
    if (auto store = dyn_cast<memref::StoreOp>(user)) {
      SmallVector<Value> indices{indexValue};
      indices.append(store.getIndices().begin(), store.getIndices().end());
      auto ns = memref::StoreOp::create(b, loc, store.getValue(), src, indices);
      copyAttrs(user, ns);
      store.erase();
      return true;
    }
    bool isLoad = isa<affine::AffineLoadOp>(user);
    bool isStore = isa<affine::AffineStoreOp>(user);
    if (!isLoad && !isStore)
      return false;
    AffineMap map = isLoad ? cast<affine::AffineLoadOp>(user).getAffineMap()
                           : cast<affine::AffineStoreOp>(user).getAffineMap();
    ValueRange mapOperands =
        isLoad ? cast<affine::AffineLoadOp>(user).getMapOperands()
               : cast<affine::AffineStoreOp>(user).getMapOperands();
    unsigned nd = map.getNumDims(), ns = map.getNumSymbols();
    MLIRContext *context = user->getContext();
    SmallVector<AffineExpr> results;
    SmallVector<Value> operands;
    if (affine::isValidSymbol(indexValue)) {
      results.push_back(getAffineSymbolExpr(0, context));
      for (AffineExpr e : map.getResults())
        results.push_back(e.shiftSymbols(ns, 1));
      map = AffineMap::get(nd, ns + 1, results, context);
      operands.append(mapOperands.begin(), mapOperands.begin() + nd);
      operands.push_back(indexValue);
      operands.append(mapOperands.begin() + nd, mapOperands.end());
    } else if (affine::isValidDim(indexValue)) {
      results.push_back(getAffineDimExpr(0, context));
      for (AffineExpr e : map.getResults())
        results.push_back(e.shiftDims(nd, 1));
      map = AffineMap::get(nd + 1, ns, results, context);
      operands.push_back(indexValue);
      operands.append(mapOperands.begin(), mapOperands.end());
    } else {

      SmallVector<Value> indices{indexValue};
      for (unsigned resultValue = 0; resultValue < map.getNumResults();
           ++resultValue)
        indices.push_back(affine::AffineApplyOp::create(
            b, loc, map.getSubMap({resultValue}), mapOperands));
      if (isLoad) {
        auto nl = memref::LoadOp::create(b, loc, src, indices);
        copyAttrs(user, nl);
        user->getResult(0).replaceAllUsesWith(nl.getResult());
      } else {
        auto ns2 = memref::StoreOp::create(
            b, loc, cast<affine::AffineStoreOp>(user).getValue(), src, indices);
        copyAttrs(user, ns2);
      }
      user->erase();
      return true;
    }
    if (isLoad) {
      auto nl = affine::AffineLoadOp::create(b, loc, src, map, operands);
      copyAttrs(user, nl);
      user->getResult(0).replaceAllUsesWith(nl.getResult());
    } else {
      auto ns2 = affine::AffineStoreOp::create(
          b, loc, cast<affine::AffineStoreOp>(user).getValue(), src, map,
          operands);
      copyAttrs(user, ns2);
    }
    user->erase();
    return true;
  }

  bool redirectCall(func::CallOp call, SymbolTable &symbols,
                    SmallVectorImpl<SubIndexOp> &worklist) {
    func::FuncOp callee = resolveDefinedCallee(call);
    if (!callee)
      return false;
    SmallVector<std::pair<unsigned, Type>> rows;
    for (auto [loopIndex, valueHandle] :
         llvm::enumerate(call.getArgOperands())) {
      auto si = valueHandle.getDefiningOp<SubIndexOp>();
      if (!si || !(si.isRowSelect() || si.isOffsetView()))
        continue;
      if (loopIndex >= callee.getNumArguments() ||
          callee.getArgument(loopIndex).getType() != valueHandle.getType())
        continue;
      rows.push_back(
          {static_cast<unsigned>(loopIndex), si.getSource().getType()});
    }
    if (rows.empty())
      return false;
    func::FuncOp clone = cloneForRows(callee, rows, symbols, worklist);
    SmallVector<Value> operands;
    for (auto [loopIndex, valueHandle] :
         llvm::enumerate(call.getArgOperands())) {
      auto it = llvm::find_if(rows, [&](auto &resultValue) {
        return resultValue.first == loopIndex;
      });
      if (it == rows.end()) {
        operands.push_back(valueHandle);
        continue;
      }
      auto si = valueHandle.getDefiningOp<SubIndexOp>();
      operands.push_back(si.getSource());
      operands.push_back(si.getIndex());
    }
    OpBuilder b(call);
    auto nc = func::CallOp::create(b, call.getLoc(), clone, operands);
    for (NamedAttribute a : call->getDiscardableAttrs())
      nc->setDiscardableAttr(a.getName(), a.getValue());
    call.replaceAllUsesWith(nc.getResults());
    call.erase();
    ++redirectedCalls;
    return true;
  }

  /// A Polygeist op hls-est does not model parses as an unregistered op of
  /// the polygeist dialect (PolygeistCompatDialect). That is safe only while
  /// it owns and touches no memory, as `polygeist.get_func` (a function's
  /// address) does: the memory analyses see memrefs through the ops they
  /// know, so an unknown op that reads, writes or views a memref would go
  /// uncounted. Such an op is an error rather than a silent miss (W8b
  /// review). True when the module has none.
  static bool checkUnmodelledOps(ModuleOp module) {
    bool ok = true;
    module.walk([&](Operation *op) {
      if (op->isRegistered() ||
          op->getName().getDialectNamespace() !=
              PolygeistCompatDialect::getDialectNamespace())
        return;
      auto isMemRef = [](Type typeValue) {
        return isa<BaseMemRefType>(typeValue);
      };
      if (llvm::any_of(op->getOperandTypes(), isMemRef) ||
          llvm::any_of(op->getResultTypes(), isMemRef)) {
        op->emitError("polygeist op not modelled by hls-est takes or "
                      "returns a memref: the memory it touches would not be "
                      "counted");
        ok = false;
      }
    });
    return ok;
  }

  void runOnOperation() override {
    ModuleOp module = getOperation();
    if (!checkUnmodelledOps(module))
      return signalPassFailure();
    dropMathCoreBodies(module);
    lowerStreamElementViews(module);
    if (sinkConditionalViews)
      sinkAccessesIntoViewConditionals(module);
    SmallVector<func::FuncOp> specialised;
    specializeCastArguments(module, specialised);
    SymbolTable symbols(module);
    clonedFrom.append(specialised.begin(), specialised.end());
    SmallVector<SubIndexOp> worklist;
    module.walk([&](SubIndexOp si) { worklist.push_back(si); });

    for (unsigned elementCount = 0;
         elementCount < worklist.size() && elementCount < 100000;
         ++elementCount) {
      SubIndexOp si = worklist[elementCount];
      if (!si)
        continue;
      bool element = si.isElementView();
      if (!si.isRowSelect() && !si.isOffsetView() && !element)
        continue;
      SmallVector<Operation *> users(si->getUsers().begin(),
                                     si->getUsers().end());
      for (Operation *user : users) {
        if (element && !accessedMemRef(user))
          continue;
        if (auto call = dyn_cast<func::CallOp>(user)) {
          redirectCall(call, symbols, worklist);
          continue;
        }
        if (rewriteAccess(user, si))
          ++rewrittenAccesses;
      }
      if (si->use_empty())
        si->erase();
      worklist[elementCount] = nullptr;
    }

    for (bool again = true; again;) {
      again = false;
      SmallVector<SubIndexOp> left;
      module.walk([&](SubIndexOp si) { left.push_back(si); });
      for (SubIndexOp si : left) {
        if (!si.isRowSelect() && !si.isOffsetView() && !si.isElementView())
          continue;
        if (!llvm::all_of(si->getUsers(), [](Operation *useValue) {
              return accessedMemRef(useValue) != Value();
            }))
          continue;
        SmallVector<Operation *> users(si->getUsers().begin(),
                                       si->getUsers().end());
        for (Operation *user : users)
          if (rewriteAccess(user, si)) {
            ++rewrittenAccesses;
            again = true;
          }
        if (si->use_empty())
          si->erase();
      }
    }

    module.walk([&](SubIndexOp si) {
      if (si->use_empty()) {
        si->erase();
        return;
      }
      ++left;
      si->emitWarning("polygeist.subindex not lowered: ")
          << (si.isRowSelect() || si.isOffsetView()
                  ? "a use that is neither a load/store nor a call to a "
                    "function of the module"
                  : "not a row of a static-shape array (nor an offset view of "
                    "one)");
    });

    SmallVector<func::FuncOp> candidates(clonedFrom.begin(), clonedFrom.end());
    for (auto &[key, fn] : clones)
      if (!llvm::is_contained(candidates, fn))
        candidates.push_back(fn);
    for (bool erased = true; erased;) {
      erased = false;
      for (func::FuncOp &fn : candidates) {
        if (!fn || !fn.isPrivate() || !symbols.symbolKnownUseEmpty(fn, module))
          continue;
        symbols.erase(fn);
        fn = nullptr;
        erased = true;
      }
    }
  }
};

} // namespace

std::unique_ptr<Pass> circt::hls_analysis::createLowerSubIndexPass() {
  return std::make_unique<LowerSubIndexPass>();
}

void circt::hls_analysis::registerLowerSubIndexPass() {
  PassRegistration<LowerSubIndexPass>();
}
