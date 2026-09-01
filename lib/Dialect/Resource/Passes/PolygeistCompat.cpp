

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
#include "mlir/IR/Builders.h"
#include "mlir/IR/BuiltinOps.h"
#include "mlir/IR/Diagnostics.h"
#include "mlir/IR/SymbolTable.h"
#include "mlir/Transforms/InliningUtils.h"
#include "llvm/ADT/MapVector.h"
#include "llvm/ADT/SmallVector.h"

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
/// whole array. Only integer / float elements of a rank-1 row; anything
/// else is left as it was.
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
    if (!src || !passResult || src.getRank() != 1 ||
        passResult.getRank() != 1 || !src.hasStaticShape() ||
        !ShapedType::isDynamic(passResult.getShape()[0]) ||
        !src.getLayout().isIdentity() || !passResult.getLayout().isIdentity() ||
        src.getElementType() != passResult.getElementType() ||
        !src.getElementType().isIntOrFloat())
      continue;
    auto fn = call->getParentOfType<func::FuncOp>();
    if (!fn)
      continue;
    Location loc = call.getLoc();
    OpBuilder entry(&fn.getBody().front(), fn.getBody().front().begin());
    auto tmp = memref::AllocaOp::create(
        entry, loc, MemRefType::get({1}, src.getElementType()));
    auto view = memref::CastOp::create(entry, loc, passResult, tmp);
    Value indexValue = si.getIndex();
    bool affineIdx =
        affine::isValidDim(indexValue) || affine::isValidSymbol(indexValue);
    OpBuilder buildPoint(call);
    Value zero = arith::ConstantIndexOp::create(buildPoint, loc, 0);
    auto load = [&](OpBuilder &bb, Value mem, Value loopIndex) -> Value {
      if (affineIdx || mem == tmp.getResult())
        return affine::AffineLoadOp::create(bb, loc, mem,
                                            ValueRange{loopIndex});
      return memref::LoadOp::create(bb, loc, mem, ValueRange{loopIndex});
    };
    auto store = [&](OpBuilder &bb, Value valueHandle, Value mem,
                     Value loopIndex) {
      if (affineIdx || mem == tmp.getResult())
        affine::AffineStoreOp::create(bb, loc, valueHandle, mem,
                                      ValueRange{loopIndex});
      else
        memref::StoreOp::create(bb, loc, valueHandle, mem,
                                ValueRange{loopIndex});
    };
    if (streamWrites)
      store(buildPoint, load(buildPoint, si.getSource(), indexValue), tmp,
            zero);
    call->setOperand(1, view);
    if (streamReads) {
      buildPoint.setInsertionPointAfter(call);
      store(buildPoint, load(buildPoint, tmp, zero), si.getSource(),
            indexValue);
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
        OpBuilder buildPoint(&entry, entry.begin());
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
            Value ptr =
                memref::CastOp::create(buildPoint, arg.getLoc(), ptrTy, arg);
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
      OpBuilder buildPoint(call);
      auto nc =
          func::CallOp::create(buildPoint, call.getLoc(), clone, operands);
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

  StringRef getArgument() const final { return "lower-polygeist-subindex"; }
  StringRef getDescription() const final {
    return "Replace polygeist.subindex (a row of an array passed by "
           "reference, or the elements from an offset on) by indexed "
           "accesses of the whole array, cloning a callee per array-argument "
           "form as Vitis does (N14 R4)";
  }
  void getDependentDialects(DialectRegistry &targetRegistry) const override {
    targetRegistry.insert<affine::AffineDialect, memref::MemRefDialect,
                          func::FuncDialect, arith::ArithDialect>();
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
      attrs.push_back(DictionaryAttr::get(context, {}));
    }
    Block &entry = clone.getBody().front();
    OpBuilder buildPoint(&entry, entry.begin());
    for (auto &[portValue, memRefType] : llvm::reverse(rows)) {
      BlockArgument old = entry.getArgument(portValue);
      Location loc = old.getLoc();
      BlockArgument full = entry.insertArgument(portValue + 1, memRefType, loc);
      BlockArgument row =
          entry.insertArgument(portValue + 2, buildPoint.getIndexType(), loc);
      auto si = SubIndexOp::create(buildPoint, loc, old.getType(), full, row);
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
    OpBuilder buildPoint(user);
    Location loc = user->getLoc();
    auto copyAttrs = [&](Operation *from, Operation *to) {
      for (NamedAttribute a : from->getDiscardableAttrs())
        if (a.getName() != "map")
          to->setDiscardableAttr(a.getName(), a.getValue());
    };
    auto shifted = [&](ValueRange indices) {
      SmallVector<Value> out(indices.begin(), indices.end());
      out[0] = arith::AddIOp::create(buildPoint, loc, out[0], off);
      return out;
    };
    if (auto load = dyn_cast<memref::LoadOp>(user)) {
      auto nl = memref::LoadOp::create(buildPoint, loc, src,
                                       shifted(load.getIndices()));
      copyAttrs(user, nl);
      load.replaceAllUsesWith(nl.getResult());
      load.erase();
      return true;
    }
    if (auto store = dyn_cast<memref::StoreOp>(user)) {
      auto ns = memref::StoreOp::create(buildPoint, loc, store.getValue(), src,
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
            buildPoint, loc, map.getSubMap({resultValue}), mapOperands));
      indices = shifted(indices);
      if (isLoad) {
        auto nl = memref::LoadOp::create(buildPoint, loc, src, indices);
        copyAttrs(user, nl);
        user->getResult(0).replaceAllUsesWith(nl.getResult());
      } else {
        auto ns2 = memref::StoreOp::create(
            buildPoint, loc, cast<affine::AffineStoreOp>(user).getValue(), src,
            indices);
        copyAttrs(user, ns2);
      }
      user->erase();
      return true;
    }
    if (isLoad) {
      auto nl =
          affine::AffineLoadOp::create(buildPoint, loc, src, map, operands);
      copyAttrs(user, nl);
      user->getResult(0).replaceAllUsesWith(nl.getResult());
    } else {
      auto ns2 = affine::AffineStoreOp::create(
          buildPoint, loc, cast<affine::AffineStoreOp>(user).getValue(), src,
          map, operands);
      copyAttrs(user, ns2);
    }
    user->erase();
    return true;
  }

  bool rewriteAccess(Operation *user, SubIndexOp si) {
    if (si.isOffsetView())
      return rewriteOffsetAccess(user, si);
    Value src = si.getSource();
    Value indexValue = si.getIndex();
    OpBuilder buildPoint(user);
    Location loc = user->getLoc();
    auto copyAttrs = [&](Operation *from, Operation *to) {
      for (NamedAttribute a : from->getDiscardableAttrs())
        if (a.getName() != "map")
          to->setDiscardableAttr(a.getName(), a.getValue());
    };
    if (auto load = dyn_cast<memref::LoadOp>(user)) {
      SmallVector<Value> indices{indexValue};
      indices.append(load.getIndices().begin(), load.getIndices().end());
      auto nl = memref::LoadOp::create(buildPoint, loc, src, indices);
      copyAttrs(user, nl);
      load.replaceAllUsesWith(nl.getResult());
      load.erase();
      return true;
    }
    if (auto store = dyn_cast<memref::StoreOp>(user)) {
      SmallVector<Value> indices{indexValue};
      indices.append(store.getIndices().begin(), store.getIndices().end());
      auto ns = memref::StoreOp::create(buildPoint, loc, store.getValue(), src,
                                        indices);
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
            buildPoint, loc, map.getSubMap({resultValue}), mapOperands));
      if (isLoad) {
        auto nl = memref::LoadOp::create(buildPoint, loc, src, indices);
        copyAttrs(user, nl);
        user->getResult(0).replaceAllUsesWith(nl.getResult());
      } else {
        auto ns2 = memref::StoreOp::create(
            buildPoint, loc, cast<affine::AffineStoreOp>(user).getValue(), src,
            indices);
        copyAttrs(user, ns2);
      }
      user->erase();
      return true;
    }
    if (isLoad) {
      auto nl =
          affine::AffineLoadOp::create(buildPoint, loc, src, map, operands);
      copyAttrs(user, nl);
      user->getResult(0).replaceAllUsesWith(nl.getResult());
    } else {
      auto ns2 = affine::AffineStoreOp::create(
          buildPoint, loc, cast<affine::AffineStoreOp>(user).getValue(), src,
          map, operands);
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
    OpBuilder buildPoint(call);
    auto nc = func::CallOp::create(buildPoint, call.getLoc(), clone, operands);
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
      if (!si.isRowSelect() && !si.isOffsetView())
        continue;
      SmallVector<Operation *> users(si->getUsers().begin(),
                                     si->getUsers().end());
      for (Operation *user : users) {
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
