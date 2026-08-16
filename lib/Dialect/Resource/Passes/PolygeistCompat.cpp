

// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#include "circt/Dialect/Resource/Passes/PolygeistCompat.h"
#include "circt/Dialect/Resource/Passes/CallInstances.h"
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
  for (Attribute arrayValue : arr) {
    auto dimensionIndex = dyn_cast<DictionaryAttr>(arrayValue);
    if (!dimensionIndex) {
      entries.push_back(arrayValue);
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
           "reference) by indexed accesses of the whole array, cloning a "
           "callee per array-argument form as Vitis does (N14 R4)";
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
    std::string name = callee.getName().str() + "_row";
    for (auto &[portValue, memRefType] : rows)
      name += "_" + std::to_string(portValue);
    clone.setName(name);
    clone.setPrivate();

    SmallVector<Type> types;
    SmallVector<DictionaryAttr> attrs;
    unsigned elementCount = callee.getNumArguments();
    for (unsigned loopIndex = 0; loopIndex < elementCount; ++loopIndex) {
      DictionaryAttr arrayValue = callee.getArgAttrDict(loopIndex);
      auto it = llvm::find_if(rows, [&](auto &resultValue) {
        return resultValue.first == loopIndex;
      });
      if (it == rows.end()) {
        types.push_back(callee.getArgument(loopIndex).getType());
        attrs.push_back(arrayValue ? arrayValue
                                   : DictionaryAttr::get(context, {}));
        continue;
      }
      types.push_back(it->second);
      attrs.push_back(shiftPartitionDims(arrayValue, context,
                                         dyn_cast<MemRefType>(it->second)));
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

  bool rewriteAccess(Operation *user, SubIndexOp si) {
    Value src = si.getSource();
    Value indexValue = si.getIndex();
    OpBuilder buildPoint(user);
    Location loc = user->getLoc();
    auto copyAttrs = [&](Operation *from, Operation *to) {
      for (NamedAttribute arrayValue : from->getDiscardableAttrs())
        if (arrayValue.getName() != "map")
          to->setDiscardableAttr(arrayValue.getName(), arrayValue.getValue());
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
      for (AffineExpr entryValue : map.getResults())
        results.push_back(entryValue.shiftSymbols(ns, 1));
      map = AffineMap::get(nd, ns + 1, results, context);
      operands.append(mapOperands.begin(), mapOperands.begin() + nd);
      operands.push_back(indexValue);
      operands.append(mapOperands.begin() + nd, mapOperands.end());
    } else if (affine::isValidDim(indexValue)) {
      results.push_back(getAffineDimExpr(0, context));
      for (AffineExpr entryValue : map.getResults())
        results.push_back(entryValue.shiftDims(nd, 1));
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

  bool redirectCall(func::CallOp callSite, SymbolTable &symbols,
                    SmallVectorImpl<SubIndexOp> &worklist) {
    func::FuncOp callee = resolveDefinedCallee(callSite);
    if (!callee)
      return false;
    SmallVector<std::pair<unsigned, Type>> rows;
    for (auto [loopIndex, valueHandle] :
         llvm::enumerate(callSite.getArgOperands())) {
      auto si = valueHandle.getDefiningOp<SubIndexOp>();
      if (!si || !si.isRowSelect())
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
         llvm::enumerate(callSite.getArgOperands())) {
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
    OpBuilder buildPoint(callSite);
    auto nc =
        func::CallOp::create(buildPoint, callSite.getLoc(), clone, operands);
    for (NamedAttribute arrayValue : callSite->getDiscardableAttrs())
      nc->setDiscardableAttr(arrayValue.getName(), arrayValue.getValue());
    callSite.replaceAllUsesWith(nc.getResults());
    callSite.erase();
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
    SymbolTable symbols(module);
    SmallVector<SubIndexOp> worklist;
    module.walk([&](SubIndexOp si) { worklist.push_back(si); });

    for (unsigned elementCount = 0;
         elementCount < worklist.size() && elementCount < 100000;
         ++elementCount) {
      SubIndexOp si = worklist[elementCount];
      if (!si)
        continue;
      if (!si.isRowSelect())
        continue;
      SmallVector<Operation *> users(si->getUsers().begin(),
                                     si->getUsers().end());
      for (Operation *user : users) {
        if (auto callSite = dyn_cast<func::CallOp>(user)) {
          redirectCall(callSite, symbols, worklist);
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
          << (si.isRowSelect() ? "a use that is neither a load/store nor a "
                                 "call to a function of the module"
                               : "not a row of a static-shape array");
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
