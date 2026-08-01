

// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#include "circt/Dialect/Resource/HLS/HLSOps.h"
#include "circt/Dialect/Resource/Interfaces/MemoryDS.h"
#include "circt/Dialect/Resource/Passes/ConstantIndex.h"
#include "circt/Support/LLVM.h"
#include "circt/Transforms/Passes.h"
#include "mlir/Dialect/Affine/IR/AffineOps.h"
#include "mlir/Dialect/Arith/IR/Arith.h"
#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/Dialect/MemRef/IR/MemRef.h"
#include "mlir/Dialect/SCF/IR/SCF.h"
#include "mlir/Dialect/Utils/StaticValueUtils.h"
#include "mlir/IR/AffineExpr.h"
#include "mlir/IR/AffineMap.h"
#include "mlir/IR/OperationSupport.h"
#include "mlir/Pass/Pass.h"
#include "mlir/Support/LLVM.h"
#include "mlir/Transforms/WalkPatternRewriteDriver.h"
#include "llvm/ADT/TypeSwitch.h"
#include "llvm/Support/FormatVariadic.h"

#include <circt/Dialect/Resource/Interfaces/MemoryOpInterface.h.inc>
#include <mlir/IR/IntegerSet.h>
#include <numeric>
#include <optional>
#include <utility>

namespace circt::hls_analysis {
#define GEN_PASS_DEF_MEMORYBANKING
#include "circt/Dialect/Resource/Passes/Passes.h.inc"
} // namespace circt::hls_analysis

using namespace mlir;
using namespace circt;
using namespace circt::hls_analysis;

static unsigned effectiveFactor(const PartitionSpec &spec,
                                MemRefType memRefType) {
  if (spec.kind == PartitionSpec::Complete)
    return static_cast<unsigned>(memRefType.getShape()[spec.dim]);
  return spec.factor;
}

static std::pair<AffineExpr, AffineExpr>
computeBankAndOffset(AffineExpr idxExpr, const PartitionSpec &spec,
                     MemRefType originalType) {
  unsigned fieldValue = effectiveFactor(spec, originalType);
  if (spec.kind == PartitionSpec::Block) {

    int64_t extent = originalType.getShape()[spec.dim];
    int64_t blockSize = (extent + static_cast<int64_t>(fieldValue) - 1) /
                        static_cast<int64_t>(fieldValue);
    return {idxExpr.floorDiv(blockSize), idxExpr % blockSize};
  }

  return {idxExpr % static_cast<int64_t>(fieldValue),
          idxExpr.floorDiv(static_cast<int64_t>(fieldValue))};
}

namespace {

struct MemrefBankAccess {
  SmallVector<Value, 4> bankedIndices;
  Value bankIdx;
  std::optional<unsigned> constBank;
};

static MemrefBankAccess
computeMemrefBankAccess(OpBuilder &buildPoint, Location loc, ValueRange indices,
                        const PartitionSpec &spec, MemRefType origTy) {
  unsigned fieldValue = effectiveFactor(spec, origTy);
  Value indexValue = indices[spec.dim];

  bool bankIsDiv = spec.kind == PartitionSpec::Block;
  int64_t divisor;
  if (bankIsDiv) {
    int64_t extent = origTy.getShape()[spec.dim];
    divisor = (extent + (int64_t)fieldValue - 1) / (int64_t)fieldValue;
  } else {
    divisor = (int64_t)fieldValue;
  }

  MemrefBankAccess mba;
  mba.bankedIndices.assign(indices.begin(), indices.end());

  if (auto candidateValue = getConstantIndexValue(indexValue)) {
    int64_t valueHandle = *candidateValue;
    int64_t bank = bankIsDiv ? valueHandle / divisor : valueHandle % divisor;
    int64_t off = bankIsDiv ? valueHandle % divisor : valueHandle / divisor;
    mba.constBank = (unsigned)bank;
    mba.bankedIndices[spec.dim] =
        arith::ConstantIndexOp::create(buildPoint, loc, off);
    return mba;
  }

  Value dimensionIndex =
      arith::ConstantIndexOp::create(buildPoint, loc, divisor);
  Value bankV =
      bankIsDiv
          ? arith::DivUIOp::create(buildPoint, loc, indexValue, dimensionIndex)
                .getResult()
          : arith::RemUIOp::create(buildPoint, loc, indexValue, dimensionIndex)
                .getResult();
  Value offV =
      bankIsDiv
          ? arith::RemUIOp::create(buildPoint, loc, indexValue, dimensionIndex)
                .getResult()
          : arith::DivUIOp::create(buildPoint, loc, indexValue, dimensionIndex)
                .getResult();
  mba.bankIdx = bankV;
  mba.bankedIndices[spec.dim] = offV;
  return mba;
}

struct BankAccess {
  AffineMap bankMap;
  AffineMap bankedAccessMap;
  std::optional<unsigned> constBank;
};

BankAccess computeBankAccess(AffineMap accessMap, const PartitionSpec &spec,
                             MemRefType origTy, MLIRContext *context) {

  AffineExpr indexValue = accessMap.getResult(spec.dim);
  auto [bankExpr, offsetExpr] = computeBankAndOffset(indexValue, spec, origTy);

  unsigned nDims = accessMap.getNumDims();
  unsigned nSyms = accessMap.getNumSymbols();

  BankAccess ba;
  AffineExpr simp = simplifyAffineExpr(bankExpr, nDims, nSyms);
  ba.bankMap = AffineMap::get(nDims, nSyms, simp);

  SmallVector<AffineExpr, 4> results(accessMap.getResults().begin(),
                                     accessMap.getResults().end());
  results[spec.dim] = offsetExpr;
  ba.bankedAccessMap = AffineMap::get(nDims, nSyms, results, context);

  if (auto candidateValue = dyn_cast<AffineConstantExpr>(simp))
    ba.constBank = static_cast<unsigned>(candidateValue.getValue());
  return ba;
}

static std::optional<unsigned>
constantBankThroughInductionVars(AffineMap accessMap, ArrayRef<Value> operands,
                                 const PartitionSpec &spec, MemRefType origTy) {
  unsigned nDims = accessMap.getNumDims();
  unsigned nSyms = accessMap.getNumSymbols();
  MLIRContext *context = accessMap.getContext();
  SmallVector<AffineExpr, 4> dimRepl;
  bool any = false;
  for (unsigned loopIndex = 0; loopIndex < nDims; ++loopIndex) {
    AffineExpr dimensionIndex = getAffineDimExpr(loopIndex, context);
    Value valueHandle = operands[loopIndex];
    if (affine::isAffineForInductionVar(valueHandle)) {
      affine::AffineForOp owner = affine::getForInductionVarOwner(valueHandle);
      if (owner.hasConstantLowerBound() && owner.getStepAsInt() != 1) {
        dimensionIndex = dimensionIndex * owner.getStepAsInt() +
                         owner.getConstantLowerBound();
        any = true;
      }
    }
    dimRepl.push_back(dimensionIndex);
  }
  if (!any)
    return std::nullopt;
  AffineExpr indexValue = accessMap.getResult(spec.dim).replaceDims(dimRepl);
  AffineExpr bank = computeBankAndOffset(indexValue, spec, origTy).first;
  if (auto candidateValue =
          dyn_cast<AffineConstantExpr>(simplifyAffineExpr(bank, nDims, nSyms)))
    return static_cast<unsigned>(candidateValue.getValue());
  return std::nullopt;
}

struct MemoryBankingPass
    : public hls_analysis::impl::MemoryBankingBase<MemoryBankingPass> {
  MemoryBankingPass(const MemoryBankingPass &other) = default;
  explicit MemoryBankingPass() {}

  void runOnOperation() override;

  LogicalResult applyMemoryBanking(Operation *, MLIRContext *);

  SmallVector<Value, 4> createBanks(OpBuilder &passBuilder, Value originalMem);

private:
  DenseMap<Value, SmallVector<Value>> memoryToBanks;
  DenseSet<Operation *> opsToErase;

  DenseSet<Value> oldMemRefVals;
};
} // namespace

static Operation *unbankableUser(Value mem) {
  for (Operation *user : mem.getUsers()) {
    if (isa<affine::AffineLoadOp, affine::AffineStoreOp, memref::LoadOp,
            memref::StoreOp, func::ReturnOp>(user))
      continue;
    return user;
  }
  return nullptr;
}

static DenseSet<Value> collectMemRefs(func::FuncOp funcOp) {
  DenseSet<Value> memrefVals;
  funcOp.walk([&](Operation *op) {
    Value memref;
    if (auto read = dyn_cast<affine::AffineReadOpInterface>(op))
      memref = read.getMemRef();
    else if (auto write = dyn_cast<affine::AffineWriteOpInterface>(op))
      memref = write.getMemRef();
    else
      return WalkResult::advance();
    memrefVals.insert(memref);
    return WalkResult::advance();
  });
  return memrefVals;
}

static void verifyBankingConfigurations(unsigned bankingFactor,
                                        unsigned bankingDimension,
                                        MemRefType originalType) {
  [[maybe_unused]] ArrayRef<int64_t> originalShape = originalType.getShape();
  assert(!originalShape.empty() && "memref shape should not be empty");
  assert(bankingDimension < originalType.getRank() &&
         "dimension must be within the memref rank");

  assert(bankingFactor >= 1 && "banking factor must be positive");
  assert(bankingFactor <= originalShape[bankingDimension] &&
         "banking factor must not exceed the dimension extent");
}

static MemRefType computeBankedMemRefType(MemRefType originalType,
                                          uint64_t bankingFactor,
                                          unsigned bankingDimension) {
  ArrayRef<int64_t> originalShape = originalType.getShape();
  SmallVector<int64_t, 4> newShape(originalShape.begin(), originalShape.end());

  int64_t extent = newShape[bankingDimension];
  newShape[bankingDimension] =
      (extent + static_cast<int64_t>(bankingFactor) - 1) /
      static_cast<int64_t>(bankingFactor);
  return MemRefType::get(newShape, originalType.getElementType(),
                         originalType.getLayout(),
                         originalType.getMemorySpace());
}

static SmallVector<int64_t> decodeIndex(int64_t linIndex,
                                        ArrayRef<int64_t> shape) {
  const unsigned rank = shape.size();
  SmallVector<int64_t> ndIndex(rank, 0);
  for (int64_t dimensionIndex = rank - 1; dimensionIndex >= 0;
       --dimensionIndex) {
    ndIndex[dimensionIndex] = linIndex % shape[dimensionIndex];
    linIndex /= shape[dimensionIndex];
  }
  return ndIndex;
}

static SmallVector<SmallVector<Attribute>>
sliceSubBlock(ArrayRef<Attribute> allAttrs, ArrayRef<int64_t> memShape,
              ArrayRef<int64_t> newShape, unsigned bankingDimension,
              unsigned bankingFactor, PartitionSpec::Kind kind,
              Attribute zeroAttr) {
  size_t numElements = std::reduce(memShape.begin(), memShape.end(), size_t{1},
                                   std::multiplies<size_t>());
  size_t perBank = std::reduce(newShape.begin(), newShape.end(), size_t{1},
                               std::multiplies<size_t>());
  int64_t blockSize =
      (memShape[bankingDimension] + static_cast<int64_t>(bankingFactor) - 1) /
      static_cast<int64_t>(bankingFactor);

  SmallVector<SmallVector<Attribute>> subBlocks(
      bankingFactor, SmallVector<Attribute>(perBank, zeroAttr));

  for (unsigned linIndex = 0; linIndex < numElements; ++linIndex) {
    SmallVector<int64_t> ndIndex = decodeIndex(linIndex, memShape);
    int64_t dimensionIndex = ndIndex[bankingDimension];
    unsigned bank;
    int64_t offset;
    if (kind == PartitionSpec::Block) {
      bank = static_cast<unsigned>(dimensionIndex / blockSize);
      offset = dimensionIndex % blockSize;
    } else {
      bank = static_cast<unsigned>(dimensionIndex % bankingFactor);
      offset = dimensionIndex / static_cast<int64_t>(bankingFactor);
    }
    ndIndex[bankingDimension] = offset;

    int64_t newLin = 0;
    for (unsigned keyValue = 0; keyValue < newShape.size(); ++keyValue)
      newLin = newLin * newShape[keyValue] + ndIndex[keyValue];
    subBlocks[bank][newLin] = allAttrs[linIndex];
  }
  return subBlocks;
}

static SmallVector<Value, 4>
handleGetGlobalOp(memref::GetGlobalOp getGlobalOp, uint64_t bankingFactor,
                  unsigned bankingDimension, PartitionSpec::Kind kind,
                  MemRefType newMemRefType, OpBuilder &passBuilder,
                  llvm::function_ref<DictionaryAttr(unsigned)> bankAttrs) {
  SmallVector<Value, 4> banks;
  auto memTy = cast<MemRefType>(getGlobalOp.getType());
  ArrayRef<int64_t> originalShape = memTy.getShape();
  auto newShape =
      SmallVector<int64_t>(originalShape.begin(), originalShape.end());
  newShape[bankingDimension] = (originalShape[bankingDimension] +
                                static_cast<int64_t>(bankingFactor) - 1) /
                               static_cast<int64_t>(bankingFactor);

  auto *symbolTableOp = getGlobalOp->getParentWithTrait<OpTrait::SymbolTable>();
  auto globalOpNameAttr = getGlobalOp.getNameAttr();
  auto globalOp = dyn_cast_or_null<memref::GlobalOp>(
      SymbolTable::lookupSymbolIn(symbolTableOp, globalOpNameAttr));
  assert(globalOp && "The corresponding GlobalOp should exist in the module");
  MemRefType globalOpTy = globalOp.getType();

  auto cstAttr =
      dyn_cast_or_null<DenseElementsAttr>(globalOp.getConstantInitValue());
  auto attributes = cstAttr.getValues<Attribute>();
  SmallVector<Attribute, 8> allAttrs(attributes.begin(), attributes.end());

  Attribute zeroAttr = passBuilder.getZeroAttr(globalOpTy.getElementType());
  auto subBlocks =
      sliceSubBlock(allAttrs, originalShape, newShape, bankingDimension,
                    bankingFactor, kind, zeroAttr);

  passBuilder.setInsertionPointAfter(globalOp);
  OpBuilder::InsertPoint globalOpsInsertPt = passBuilder.saveInsertionPoint();
  passBuilder.setInsertionPointAfter(getGlobalOp);
  OpBuilder::InsertPoint getGlobalOpsInsertPt =
      passBuilder.saveInsertionPoint();

  for (size_t bankCnt = 0; bankCnt < bankingFactor; ++bankCnt) {
    auto newMemRefTy = MemRefType::get(newShape, globalOpTy.getElementType());
    auto newTypeAttr = TypeAttr::get(newMemRefTy);
    std::string newName = llvm::formatv(
        "{0}_{1}_{2}", globalOpNameAttr.getValue(), "bank", bankCnt);
    RankedTensorType tensorType =
        RankedTensorType::get({newShape}, globalOpTy.getElementType());
    auto newInitValue = DenseElementsAttr::get(tensorType, subBlocks[bankCnt]);

    passBuilder.restoreInsertionPoint(globalOpsInsertPt);
    auto newGlobalOp = memref::GlobalOp::create(
        passBuilder, globalOp.getLoc(), passBuilder.getStringAttr(newName),
        globalOp.getSymVisibilityAttr(), newTypeAttr, newInitValue,
        globalOp.getConstantAttr(), globalOp.getAlignmentAttr());

    DictionaryAttr provenance = bankAttrs(static_cast<unsigned>(bankCnt));
    for (NamedAttribute attr : provenance)
      newGlobalOp->setAttr(attr.getName(), attr.getValue());
    passBuilder.setInsertionPointAfter(newGlobalOp);
    globalOpsInsertPt = passBuilder.saveInsertionPoint();

    passBuilder.restoreInsertionPoint(getGlobalOpsInsertPt);
    auto newGetGlobalOp = memref::GetGlobalOp::create(
        passBuilder, getGlobalOp.getLoc(), newMemRefTy, newGlobalOp.getName());
    newGetGlobalOp->setAttrs(provenance);
    passBuilder.setInsertionPointAfter(newGetGlobalOp);
    getGlobalOpsInsertPt = passBuilder.saveInsertionPoint();

    banks.push_back(newGetGlobalOp);
  }

  globalOp.erase();
  return banks;
}

static void updateFuncOpArgumentTypes(func::FuncOp funcOp, unsigned argIndex,
                                      MemRefType newMemRefType,
                                      unsigned numInsertedArgs) {
  auto originalArgTypes = funcOp.getFunctionType().getInputs();
  SmallVector<Type, 4> updatedArgTypes;
  for (unsigned loopIndex = 0; loopIndex < originalArgTypes.size();
       ++loopIndex) {
    updatedArgTypes.push_back(originalArgTypes[loopIndex]);
    if (loopIndex == argIndex)
      for (unsigned innerIndex = 0; innerIndex < numInsertedArgs; ++innerIndex)
        updatedArgTypes.push_back(newMemRefType);
  }
  auto resultTypes = funcOp.getFunctionType().getResults();
  funcOp.setType(
      FunctionType::get(funcOp.getContext(), updatedArgTypes, resultTypes));
}

static void
updateFuncOpArgAttrs(func::FuncOp funcOp, unsigned argIndex,
                     unsigned numInsertedArgs,
                     llvm::function_ref<DictionaryAttr(unsigned)> bankAttrs) {
  ArrayAttr existingArgAttrs = funcOp->getAttrOfType<ArrayAttr>("arg_attrs");
  SmallVector<Attribute, 4> updatedArgAttrs;
  unsigned numArguments = funcOp.getNumArguments();
  unsigned newNumArguments = numArguments + numInsertedArgs;
  updatedArgAttrs.resize(newNumArguments);

  for (unsigned loopIndex = 0; loopIndex < numArguments; ++loopIndex) {
    unsigned newIndex =
        (loopIndex > argIndex) ? loopIndex + numInsertedArgs : loopIndex;
    updatedArgAttrs[newIndex] = existingArgAttrs
                                    ? existingArgAttrs[loopIndex]
                                    : DictionaryAttr::get(funcOp.getContext());
  }
  for (unsigned loopIndex = 0; loopIndex < numInsertedArgs; ++loopIndex)
    updatedArgAttrs[argIndex + 1 + loopIndex] = bankAttrs(loopIndex);

  funcOp->setAttr("arg_attrs",
                  ArrayAttr::get(funcOp.getContext(), updatedArgAttrs));
}

static FileLineColLoc findFileLineColLoc(Location loc) {
  if (auto fieldValue = dyn_cast<FileLineColLoc>(loc))
    return fieldValue;
  if (auto elementCount = dyn_cast<NameLoc>(loc))
    return findFileLineColLoc(elementCount.getChildLoc());
  if (auto candidateValue = dyn_cast<CallSiteLoc>(loc))
    return findFileLineColLoc(candidateValue.getCallee());
  if (auto fu = dyn_cast<FusedLoc>(loc))
    for (Location lowerIndex : fu.getLocations())
      if (auto fieldValue = findFileLineColLoc(lowerIndex))
        return fieldValue;
  if (auto opHandle = dyn_cast<OpaqueLoc>(loc))
    return findFileLineColLoc(opHandle.getFallbackLocation());
  return {};
}

static std::string unnamedBankOf(Value mem) {
  if (auto fieldValue = findFileLineColLoc(mem.getLoc()))
    return "<unnamed@" + fieldValue.getFilename().str() + ":" +
           std::to_string(fieldValue.getLine()) + ":" +
           std::to_string(fieldValue.getColumn()) + ">";
  unsigned ordinal = 0;
  if (Operation *def = mem.getDefiningOp())
    if (auto function = def->getParentOfType<func::FuncOp>())
      function.walk([&](Operation *op) {
        if (op == def)
          return WalkResult::interrupt();
        if (isa<MemoryResourceOpInterface>(op) && !op->hasAttr("hls.partition"))
          ++ordinal;
        return WalkResult::advance();
      });
  return "<unnamed#" + std::to_string(ordinal) + ">";
}

SmallVector<Value, 4> MemoryBankingPass::createBanks(OpBuilder &passBuilder,
                                                     Value originalMem) {

  SmallVector<Value, 4> banks;
  MemRefType originalMemRefType = cast<MemRefType>(originalMem.getType());

  PartitionSpec spec;
  auto iface =
      dyn_cast_or_null<MemoryResourceOpInterface>(originalMem.getDefiningOp());
  if (!iface)
    return banks;
  auto specOpt = iface.getPartitionSpec();
  if (!specOpt.has_value())
    return banks;
  spec = *specOpt;

  unsigned currFactor = effectiveFactor(spec, originalMemRefType);
  unsigned currDimension = spec.dim;
  verifyBankingConfigurations(currFactor, currDimension, originalMemRefType);

  Operation *origDef = originalMem.getDefiningOp();
  func::FuncOp argFunc;
  unsigned argNo = 0;
  if (auto blockArg = dyn_cast<BlockArgument>(originalMem)) {
    argFunc = dyn_cast<func::FuncOp>(blockArg.getOwner()->getParentOp());
    argNo = blockArg.getArgNumber();
  }
  auto origAttr = [&](StringRef name) -> Attribute {
    if (origDef)
      return origDef->getAttr(name);
    if (argFunc)
      return argFunc.getArgAttr(argNo, name);
    return Attribute();
  };
  DictionaryAttr origEntry;
  if (auto arr = dyn_cast_or_null<ArrayAttr>(origAttr("hls.array_partition")))
    if (!arr.empty())
      origEntry = dyn_cast<DictionaryAttr>(arr[0]);
  auto varName = dyn_cast_or_null<StringAttr>(origAttr("polygeist.varname"));
  std::string bankOf;
  if (varName)
    bankOf = varName.getValue().str();
  else if (auto getGlobal = dyn_cast_or_null<memref::GetGlobalOp>(origDef))
    bankOf = getGlobal.getName().str();
  else if (argFunc)
    bankOf = "arg" + std::to_string(argNo);
  else
    bankOf = unnamedBankOf(originalMem);

  const char *specKind = spec.kind == PartitionSpec::Complete ? "complete"
                         : spec.kind == PartitionSpec::Block  ? "block"
                                                              : "cyclic";

  Attribute sourceAttr;
  if (origEntry)
    sourceAttr = origEntry.get("source");
  if (!sourceAttr)
    sourceAttr = passBuilder.getStringAttr("pragma");
  DictionaryAttr partitionAttr = passBuilder.getDictionaryAttr({
      passBuilder.getNamedAttr("kind", passBuilder.getStringAttr(specKind)),
      passBuilder.getNamedAttr("factor", passBuilder.getI32IntegerAttr(
                                             static_cast<int32_t>(currFactor))),
      passBuilder.getNamedAttr("dim",
                               passBuilder.getI32IntegerAttr(
                                   static_cast<int32_t>(currDimension + 1))),
      passBuilder.getNamedAttr("source", sourceAttr),
  });
  auto bankAttrs = [&](unsigned bankIdx) -> DictionaryAttr {
    SmallVector<NamedAttribute, 8> attrs;
    if (varName)
      attrs.push_back(passBuilder.getNamedAttr("polygeist.varname", varName));
    if (Attribute preserve = origAttr("hls.preserve"))
      attrs.push_back(passBuilder.getNamedAttr("hls.preserve", preserve));
    if (!bankOf.empty())
      attrs.push_back(passBuilder.getNamedAttr(
          "hls.bank_of", passBuilder.getStringAttr(bankOf)));
    attrs.push_back(passBuilder.getNamedAttr(
        "hls.bank_index",
        passBuilder.getI32IntegerAttr(static_cast<int32_t>(bankIdx))));
    attrs.push_back(passBuilder.getNamedAttr(
        "hls.bank_count",
        passBuilder.getI32IntegerAttr(static_cast<int32_t>(currFactor))));
    attrs.push_back(passBuilder.getNamedAttr("hls.partition", partitionAttr));
    if (auto reason =
            dyn_cast_or_null<StringAttr>(origAttr("hls.partition_reason")))
      attrs.push_back(passBuilder.getNamedAttr("hls.partition_reason", reason));
    return passBuilder.getDictionaryAttr(attrs);
  };

  MemRefType newMemRefType =
      computeBankedMemRefType(originalMemRefType, currFactor, currDimension);

  if (auto blockArgMem = dyn_cast<BlockArgument>(originalMem)) {
    Block *block = blockArgMem.getOwner();
    unsigned blockArgNum = blockArgMem.getArgNumber();

    for (unsigned loopIndex = 0; loopIndex < currFactor; ++loopIndex)
      block->insertArgument(blockArgNum + 1 + loopIndex, newMemRefType,
                            blockArgMem.getLoc());

    auto blockArgs = block->getArguments().slice(blockArgNum + 1, currFactor);
    banks.append(blockArgs.begin(), blockArgs.end());

    auto funcOp = dyn_cast<func::FuncOp>(block->getParentOp());
    assert(funcOp && "BlockArgument is not part of a FuncOp");
    updateFuncOpArgumentTypes(funcOp, blockArgNum, newMemRefType, currFactor);
    updateFuncOpArgAttrs(funcOp, blockArgNum, currFactor, bankAttrs);
  } else {
    Operation *originalDef = originalMem.getDefiningOp();
    Location loc = originalDef->getLoc();
    passBuilder.setInsertionPointAfter(originalDef);
    TypeSwitch<Operation *>(originalDef)
        .Case<memref::AllocOp>([&](memref::AllocOp) {
          for (uint64_t buildPoint = 0; buildPoint < currFactor; ++buildPoint) {
            auto bankAllocOp =
                memref::AllocOp::create(passBuilder, loc, newMemRefType);
            bankAllocOp->setAttrs(bankAttrs(static_cast<unsigned>(buildPoint)));
            banks.push_back(bankAllocOp);
          }
        })
        .Case<memref::AllocaOp>([&](memref::AllocaOp) {
          for (uint64_t buildPoint = 0; buildPoint < currFactor; ++buildPoint) {
            auto bankAllocaOp =
                memref::AllocaOp::create(passBuilder, loc, newMemRefType);
            bankAllocaOp->setAttrs(
                bankAttrs(static_cast<unsigned>(buildPoint)));
            banks.push_back(bankAllocaOp);
          }
        })
        .Case<memref::GetGlobalOp>([&](memref::GetGlobalOp getGlobalOp) {
          auto newBanks = handleGetGlobalOp(
              getGlobalOp, currFactor, currDimension, spec.kind, newMemRefType,
              passBuilder, bankAttrs);
          banks.append(newBanks.begin(), newBanks.end());
        })
        .Default([](Operation *) {
          llvm_unreachable("Unhandled memory operation type");
        });
  }
  return banks;
}

struct BankMemRefLoadPattern : OpRewritePattern<memref::LoadOp> {
  BankMemRefLoadPattern(MLIRContext *context,
                        DenseMap<Value, SmallVector<Value>> &memoryToBanks,
                        DenseSet<Value> &oldMemRefVals)
      : OpRewritePattern<memref::LoadOp>(context), memoryToBanks(memoryToBanks),
        oldMemRefVals(oldMemRefVals) {}

  LogicalResult matchAndRewrite(memref::LoadOp loadOp,
                                PatternRewriter &rewriter) const override {
    Value mem = loadOp.getMemRef();
    auto iface =
        dyn_cast_or_null<MemoryResourceOpInterface>(mem.getDefiningOp());
    if (!iface)
      return failure();
    auto specOpt = iface.getPartitionSpec();
    if (!specOpt)
      return failure();
    PartitionSpec spec = *specOpt;
    auto banksIt = memoryToBanks.find(mem);
    if (banksIt == memoryToBanks.end())
      return failure();
    ArrayRef<Value> banks = banksIt->second;
    MemRefType origTy = loadOp.getMemRefType();
    unsigned factor = effectiveFactor(spec, origTy);
    verifyBankingConfigurations(factor, spec.dim, origTy);

    Location loc = loadOp.getLoc();
    rewriter.setInsertionPoint(loadOp);
    MemrefBankAccess ba = computeMemrefBankAccess(
        rewriter, loc, loadOp.getIndices(), spec, origTy);

    if (ba.constBank) {
      rewriter.replaceOpWithNewOp<memref::LoadOp>(loadOp, banks[*ba.constBank],
                                                  ba.bankedIndices);
      if (isa<BlockArgument>(mem))
        oldMemRefVals.insert(mem);
      return success();
    }

    SmallVector<Value, 4> bankVals;
    for (unsigned keyValue = 0; keyValue < factor; ++keyValue)
      bankVals.push_back(memref::LoadOp::create(rewriter, loc, banks[keyValue],
                                                ba.bankedIndices));

    Value result = bankVals[factor - 1];
    for (unsigned keyValue = factor - 1; keyValue-- > 0;) {
      Value kc = arith::ConstantIndexOp::create(rewriter, loc, keyValue);
      Value eq = arith::CmpIOp::create(rewriter, loc, arith::CmpIPredicate::eq,
                                       ba.bankIdx, kc);
      result = arith::SelectOp::create(rewriter, loc, eq, bankVals[keyValue],
                                       result);
    }
    if (isa<BlockArgument>(mem))
      oldMemRefVals.insert(mem);
    rewriter.replaceOp(loadOp, result);
    return success();
  }

private:
  DenseMap<Value, SmallVector<Value>> &memoryToBanks;
  DenseSet<Value> &oldMemRefVals;
};

struct BankAffineLoadPattern
    : public OpRewritePattern<mlir::affine::AffineLoadOp> {
  BankAffineLoadPattern(MLIRContext *context,
                        DenseMap<Value, SmallVector<Value>> &memoryToBanks,
                        DenseSet<Value> &oldMemRefVals)
      : OpRewritePattern<mlir::affine::AffineLoadOp>(context),
        memoryToBanks(memoryToBanks), oldMemRefVals(oldMemRefVals) {}

  LogicalResult matchAndRewrite(mlir::affine::AffineLoadOp loadOp,
                                PatternRewriter &rewriter) const override {
    Value mem = loadOp.getMemref();
    auto iface =
        dyn_cast_or_null<MemoryResourceOpInterface>(mem.getDefiningOp());
    if (!iface)
      return failure();
    auto specOpt = iface.getPartitionSpec();
    if (!specOpt.has_value())
      return failure();
    PartitionSpec spec = *specOpt;

    auto banksIt = memoryToBanks.find(mem);
    if (banksIt == memoryToBanks.end())
      return failure();
    ArrayRef<Value> banks = banksIt->second;
    MemRefType origTy = loadOp.getMemRefType();
    unsigned fieldValue = effectiveFactor(spec, origTy);
    verifyBankingConfigurations(fieldValue, spec.dim, origTy);

    Location loc = loadOp.getLoc();
    AffineMap accessMap = loadOp.getAffineMap();
    SmallVector<Value, 4> operands(loadOp.getMapOperands().begin(),
                                   loadOp.getMapOperands().end());
    affine::fullyComposeAffineMapAndOperands(&accessMap, &operands);

    affine::canonicalizeMapAndOperands(&accessMap, &operands);

    accessMap = foldConstantIndexOperands(accessMap, operands);
    affine::canonicalizeMapAndOperands(&accessMap, &operands);
    accessMap = simplifyAffineMap(accessMap);
    BankAccess ba =
        computeBankAccess(accessMap, spec, origTy, rewriter.getContext());
    if (!ba.constBank)
      ba.constBank =
          constantBankThroughInductionVars(accessMap, operands, spec, origTy);

    if (ba.constBank) {
      auto newLoad = rewriter.replaceOpWithNewOp<mlir::affine::AffineLoadOp>(
          loadOp, banks[*ba.constBank], ba.bankedAccessMap, operands);
      (void)newLoad;
      if (isa<BlockArgument>(mem))
        oldMemRefVals.insert(mem);
      return success();
    }

    Value bankIdx =
        affine::AffineApplyOp::create(rewriter, loc, ba.bankMap, operands);

    SmallVector<Value, 4> bankVals;
    for (unsigned keyValue = 0; keyValue < fieldValue; ++keyValue)
      bankVals.push_back(mlir::affine::AffineLoadOp::create(
          rewriter, loc, banks[keyValue], ba.bankedAccessMap, operands));

    Value result = bankVals[fieldValue - 1];
    for (unsigned keyValue = fieldValue - 1; keyValue-- > 0;) {
      Value kc = arith::ConstantIndexOp::create(rewriter, loc, keyValue);
      Value eq = arith::CmpIOp::create(rewriter, loc, arith::CmpIPredicate::eq,
                                       bankIdx, kc);
      result = arith::SelectOp::create(rewriter, loc, eq, bankVals[keyValue],
                                       result);
    }

    if (isa<BlockArgument>(mem))
      oldMemRefVals.insert(mem);
    rewriter.replaceOp(loadOp, result);
    return success();
  }

private:
  DenseMap<Value, SmallVector<Value>> &memoryToBanks;
  DenseSet<Value> &oldMemRefVals;
};

struct BankMemRefStorePattern : public OpRewritePattern<memref::StoreOp> {
  BankMemRefStorePattern(MLIRContext *context,
                         DenseMap<Value, SmallVector<Value>> &memoryToBanks,
                         DenseSet<Operation *> &opsToErase,
                         DenseSet<Operation *> &processedOps,
                         DenseSet<Value> &oldMemRefVals)
      : OpRewritePattern<memref::StoreOp>(context),
        memoryToBanks(memoryToBanks), opsToErase(opsToErase),
        processedOps(processedOps), oldMemRefVals(oldMemRefVals) {}

  LogicalResult matchAndRewrite(memref::StoreOp storeOp,
                                PatternRewriter &rewriter) const override {
    if (processedOps.contains(storeOp))
      return failure();
    Value mem = storeOp.getMemRef();
    auto iface =
        dyn_cast_or_null<MemoryResourceOpInterface>(mem.getDefiningOp());
    if (!iface)
      return failure();
    auto specOpt = iface.getPartitionSpec();
    if (!specOpt)
      return failure();
    PartitionSpec spec = *specOpt;
    auto banksIt = memoryToBanks.find(mem);
    if (banksIt == memoryToBanks.end())
      return failure();
    ArrayRef<Value> banks = banksIt->second;
    MemRefType origTy = storeOp.getMemRefType();
    unsigned fieldValue = effectiveFactor(spec, origTy);
    verifyBankingConfigurations(fieldValue, spec.dim, origTy);

    Location loc = storeOp.getLoc();
    Value operandValue = storeOp.getValueToStore();
    rewriter.setInsertionPoint(storeOp);
    MemrefBankAccess ba = computeMemrefBankAccess(
        rewriter, loc, storeOp.getIndices(), spec, origTy);

    if (ba.constBank) {
      memref::StoreOp::create(rewriter, loc, operandValue, banks[*ba.constBank],
                              ba.bankedIndices);
    } else {
      for (unsigned keyValue = 0; keyValue < fieldValue; ++keyValue) {
        Value kc = arith::ConstantIndexOp::create(rewriter, loc, keyValue);
        Value en = arith::CmpIOp::create(
            rewriter, loc, arith::CmpIPredicate::eq, ba.bankIdx, kc);

        StoreEnableOp::create(rewriter, loc, operandValue, en, banks[keyValue],
                              ba.bankedIndices);
      }
    }
    processedOps.insert(storeOp);
    opsToErase.insert(storeOp);
    oldMemRefVals.insert(mem);
    return success();
  }

private:
  DenseMap<Value, SmallVector<Value>> &memoryToBanks;
  DenseSet<Operation *> &opsToErase;
  DenseSet<Operation *> &processedOps;
  DenseSet<Value> &oldMemRefVals;
};

struct BankAffineStorePattern
    : public OpRewritePattern<mlir::affine::AffineStoreOp> {
  BankAffineStorePattern(MLIRContext *context,
                         DenseMap<Value, SmallVector<Value>> &memoryToBanks,
                         DenseSet<Operation *> &opsToErase,
                         DenseSet<Operation *> &processedOps,
                         DenseSet<Value> &oldMemRefVals)
      : OpRewritePattern<mlir::affine::AffineStoreOp>(context),
        memoryToBanks(memoryToBanks), opsToErase(opsToErase),
        processedOps(processedOps), oldMemRefVals(oldMemRefVals) {}

  LogicalResult matchAndRewrite(mlir::affine::AffineStoreOp storeOp,
                                PatternRewriter &rewriter) const override {
    if (processedOps.contains(storeOp))
      return failure();

    Value mem = storeOp.getMemref();
    auto iface =
        dyn_cast_or_null<MemoryResourceOpInterface>(mem.getDefiningOp());
    if (!iface)
      return failure();
    auto specOpt = iface.getPartitionSpec();
    if (!specOpt.has_value())
      return failure();

    PartitionSpec spec = *specOpt;

    auto banksIt = memoryToBanks.find(mem);
    if (banksIt == memoryToBanks.end())
      return failure();

    ArrayRef<Value> banks = banksIt->second;
    MemRefType origTy = storeOp.getMemRefType();
    unsigned factor = effectiveFactor(spec, origTy);
    verifyBankingConfigurations(factor, spec.dim, origTy);

    Location loc = storeOp.getLoc();
    Value operandValue = storeOp.getValueToStore();
    AffineMap accessMap = storeOp.getAffineMap();
    SmallVector<Value, 4> operands(storeOp.getMapOperands().begin(),
                                   storeOp.getMapOperands().end());
    affine::fullyComposeAffineMapAndOperands(&accessMap, &operands);

    affine::canonicalizeMapAndOperands(&accessMap, &operands);

    accessMap = foldConstantIndexOperands(accessMap, operands);
    affine::canonicalizeMapAndOperands(&accessMap, &operands);
    accessMap = simplifyAffineMap(accessMap);
    BankAccess ba =
        computeBankAccess(accessMap, spec, origTy, rewriter.getContext());
    if (!ba.constBank)
      ba.constBank =
          constantBankThroughInductionVars(accessMap, operands, spec, origTy);

    rewriter.setInsertionPoint(storeOp);

    if (ba.constBank) {
      affine::AffineStoreOp::create(rewriter, loc, operandValue,
                                    banks[*ba.constBank], ba.bankedAccessMap,
                                    operands);
    } else {

      AffineExpr be = ba.bankMap.getResult(0);
      unsigned nDims = ba.bankMap.getNumDims();
      unsigned nSyms = ba.bankMap.getNumSymbols();
      assert(operandValue && "null stored value");
      for (Value valueHandle : operands)
        assert(valueHandle && "null map operand");
      assert(banks.size() == factor && "bank count != factor");
      for (unsigned keyValue = 0; keyValue < factor; ++keyValue) {

        IntegerSet cond =
            IntegerSet::get(nDims, nSyms, {be - keyValue}, {true});
        AffineStoreEnableOp::create(rewriter, loc, operandValue,
                                    banks[keyValue], operands, operands,
                                    ba.bankedAccessMap, cond);
      }
    }

    processedOps.insert(storeOp);
    opsToErase.insert(storeOp);
    oldMemRefVals.insert(mem);
    return success();
  }

private:
  DenseMap<Value, SmallVector<Value>> &memoryToBanks;
  DenseSet<Operation *> &opsToErase;
  DenseSet<Operation *> &processedOps;
  DenseSet<Value> &oldMemRefVals;
};

struct BankReturnPattern : public OpRewritePattern<func::ReturnOp> {
  BankReturnPattern(MLIRContext *context,
                    DenseMap<Value, SmallVector<Value>> &memoryToBanks)
      : OpRewritePattern<func::ReturnOp>(context),
        memoryToBanks(memoryToBanks) {}

  LogicalResult matchAndRewrite(func::ReturnOp returnOp,
                                PatternRewriter &rewriter) const override {
    Location loc = returnOp.getLoc();
    SmallVector<Value, 4> newReturnOperands;
    bool allOrigMemsUsedByReturn = true;
    for (auto operand : returnOp.getOperands()) {
      if (!memoryToBanks.contains(operand)) {
        newReturnOperands.push_back(operand);
        continue;
      }
      if (operand.hasOneUse())
        allOrigMemsUsedByReturn = false;
      auto banks = memoryToBanks[operand];
      newReturnOperands.append(banks.begin(), banks.end());
    }

    func::FuncOp funcOp = returnOp->getParentOfType<func::FuncOp>();
    rewriter.setInsertionPointToEnd(&funcOp.getBlocks().front());
    auto newReturnOp =
        func::ReturnOp::create(rewriter, loc, ValueRange(newReturnOperands));
    TypeRange newReturnType = TypeRange(newReturnOperands);
    FunctionType newFuncType =
        FunctionType::get(funcOp.getContext(),
                          funcOp.getFunctionType().getInputs(), newReturnType);
    funcOp.setType(newFuncType);

    if (allOrigMemsUsedByReturn)
      rewriter.replaceOp(returnOp, newReturnOp);
    return success();
  }

private:
  DenseMap<Value, SmallVector<Value>> &memoryToBanks;
};

static LogicalResult cleanUpOldMemRefs(DenseSet<Value> &oldMemRefVals,
                                       DenseSet<Operation *> &opsToErase) {
  DenseSet<func::FuncOp> funcsToModify;
  SmallVector<Value, 4> valuesToErase;
  DenseMap<func::FuncOp, SmallVector<unsigned, 4>> erasedArgIndices;
  for (auto &memrefVal : oldMemRefVals) {
    valuesToErase.push_back(memrefVal);
    if (auto blockArg = dyn_cast<BlockArgument>(memrefVal)) {
      if (auto funcOp =
              dyn_cast<func::FuncOp>(blockArg.getOwner()->getParentOp())) {
        funcsToModify.insert(funcOp);
        erasedArgIndices[funcOp].push_back(blockArg.getArgNumber());
      }
    }
  }

  for (auto *op : opsToErase)
    op->erase();

  for (auto &memrefVal : valuesToErase) {
    assert(memrefVal.use_empty() && "use must be empty");
    if (auto blockArg = dyn_cast<BlockArgument>(memrefVal))
      blockArg.getOwner()->eraseArgument(blockArg.getArgNumber());
    else if (auto *op = memrefVal.getDefiningOp())
      op->erase();
  }

  for (auto funcOp : funcsToModify) {
    ArrayAttr existingArgAttrs = funcOp->getAttrOfType<ArrayAttr>("arg_attrs");
    if (existingArgAttrs) {
      SmallVector<Attribute, 4> updatedArgAttrs;
      auto erasedIndices = erasedArgIndices[funcOp];
      DenseSet<unsigned> indicesToErase(erasedIndices.begin(),
                                        erasedIndices.end());
      for (unsigned loopIndex = 0; loopIndex < existingArgAttrs.size();
           ++loopIndex)
        if (!indicesToErase.contains(loopIndex))
          updatedArgAttrs.push_back(existingArgAttrs[loopIndex]);
      funcOp->setAttr("arg_attrs",
                      ArrayAttr::get(funcOp.getContext(), updatedArgAttrs));
    }

    SmallVector<Type, 4> newArgTypes;
    for (BlockArgument arg : funcOp.getArguments())
      newArgTypes.push_back(arg.getType());
    funcOp.setType(FunctionType::get(funcOp.getContext(), newArgTypes,
                                     funcOp.getFunctionType().getResults()));
  }

  return success();
}

void MemoryBankingPass::runOnOperation() {
  func::FuncOp funcOp = getOperation();
  if (funcOp.isExternal())
    return;

  memoryToBanks.clear();
  oldMemRefVals.clear();
  opsToErase.clear();

  OpBuilder passBuilder(funcOp);

  DenseSet<Value> memrefs = collectMemRefs(funcOp);
  for (Value memrefVal : memrefs) {
    auto iface =
        dyn_cast_or_null<MemoryResourceOpInterface>(memrefVal.getDefiningOp());
    if (!iface)
      continue;
    auto spec = iface.getPartitionSpec();
    if (!spec || (spec->factor == 1 && spec->kind != PartitionSpec::Complete))
      continue;

    if (Operation *user = unbankableUser(memrefVal)) {
      memrefVal.getDefiningOp()->emitWarning(
          "array_partition not applied: the array is used by an op the "
          "banking does not rewrite (")
          << user->getName()
          << "); a partition across a call to a "
             "non-inlined function is not modelled (O33)";
      continue;
    }
    auto [it, inserted] =
        memoryToBanks.insert(std::make_pair(memrefVal, SmallVector<Value>{}));
    if (inserted)
      it->second = createBanks(passBuilder, memrefVal);
  }

  if (failed(applyMemoryBanking(funcOp, &getContext())))
    signalPassFailure();
}

LogicalResult MemoryBankingPass::applyMemoryBanking(Operation *operation,
                                                    MLIRContext *context) {
  RewritePatternSet patterns(context);
  DenseSet<Operation *> processedOps;
  patterns.add<BankAffineLoadPattern>(context, memoryToBanks, oldMemRefVals);
  patterns.add<BankAffineStorePattern>(context, memoryToBanks, opsToErase,
                                       processedOps, oldMemRefVals);
  patterns.add<BankReturnPattern>(context, memoryToBanks);
  patterns.add<BankMemRefLoadPattern>(context, memoryToBanks, oldMemRefVals);
  patterns.add<BankMemRefStorePattern>(context, memoryToBanks, opsToErase,
                                       processedOps, oldMemRefVals);

  walkAndApplyPatterns(operation, std::move(patterns));

  if (failed(cleanUpOldMemRefs(oldMemRefVals, opsToErase)))
    return failure();

  bool erased = true;
  while (erased) {
    erased = false;
    SmallVector<Operation *> dead;
    operation->walk([&](affine::AffineApplyOp ap) {
      if (isOpTriviallyDead(ap))
        dead.push_back(ap);
    });
    for (Operation *op : dead) {
      op->erase();
      erased = true;
    }
  }
  return success();
}

namespace circt::hls_analysis {

static std::unique_ptr<mlir::Pass> createMemoryBankingPassModified() {
  return std::make_unique<MemoryBankingPass>();
}

void registerMemoryBankingPassModified() {
  mlir::PassRegistration<MemoryBankingPass>();
}

} // namespace circt::hls_analysis