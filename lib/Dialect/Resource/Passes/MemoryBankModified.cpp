

// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#include "circt/Dialect/Resource/HLS/HLSOps.h"
#include "circt/Dialect/Resource/Interfaces/MemoryDS.h"
#include "circt/Dialect/Resource/Passes/CallInstances.h"
#include "circt/Dialect/Resource/Passes/ConstantIndex.h"
#include "circt/Dialect/Resource/Passes/PartitionLayout.h"
#include "circt/Support/LLVM.h"
#include "circt/Transforms/Passes.h"
#include "mlir/Dialect/Affine/IR/AffineOps.h"
#include "mlir/Dialect/Arith/IR/Arith.h"
#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/Dialect/MemRef/IR/MemRef.h"
#include "mlir/Dialect/SCF/IR/SCF.h"
#include "mlir/IR/AffineExpr.h"
#include "mlir/IR/AffineMap.h"
#include "mlir/IR/BuiltinOps.h"
#include "mlir/IR/IRMapping.h"
#include "mlir/IR/IntegerSet.h"
#include "mlir/IR/SymbolTable.h"
#include "mlir/Pass/Pass.h"
#include "mlir/Support/LLVM.h"
#include "llvm/ADT/MapVector.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/Support/FormatVariadic.h"

#include <circt/Dialect/Resource/Interfaces/MemoryOpInterface.h.inc>

#include <numeric>
#include <optional>
#include <string>
#include <utility>

namespace circt::hls_analysis {
#define GEN_PASS_DEF_MEMORYBANKING
#include "circt/Dialect/Resource/Passes/Passes.h.inc"
} // namespace circt::hls_analysis

using namespace mlir;
using namespace circt;
using namespace circt::hls_analysis;

namespace {

static std::optional<int64_t>
constantBankThroughInductionVars(AffineMap accessMap, ArrayRef<Value> operands,
                                 const DimPartition &portValue) {
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
  AffineExpr indexValue =
      accessMap.getResult(portValue.dim).replaceDims(dimRepl);
  AffineExpr bank = bankAndOffset(indexValue, portValue).first;
  if (auto candidateValue =
          dyn_cast<AffineConstantExpr>(simplifyAffineExpr(bank, nDims, nSyms)))
    return candidateValue.getValue();
  return std::nullopt;
}

struct BankChoice {
  SmallVector<std::optional<int64_t>> constBank;
  SmallVector<unsigned> rotating;

  int64_t numCandidates(const BankLayout &lowerIndex) const {
    int64_t elementCount = 1;
    for (unsigned resultValue : rotating)
      elementCount *= lowerIndex.dims[resultValue].factor;
    return elementCount;
  }

  SmallVector<int64_t> digits(const BankLayout &lowerIndex,
                              int64_t keyValue) const {
    SmallVector<int64_t> out(rotating.size());
    for (int64_t loopIndex = static_cast<int64_t>(rotating.size()) - 1;
         loopIndex >= 0; --loopIndex) {
      int64_t fieldValue = lowerIndex.dims[rotating[loopIndex]].factor;
      out[loopIndex] = keyValue % fieldValue;
      keyValue /= fieldValue;
    }
    return out;
  }

  int64_t bank(const BankLayout &lowerIndex, int64_t keyValue) const {
    SmallVector<int64_t> dig = digits(lowerIndex, keyValue);
    int64_t buildPoint = 0;
    unsigned resultValue = 0;
    for (unsigned innerIndex = 0; innerIndex < lowerIndex.dims.size();
         ++innerIndex) {
      int64_t valueHandle =
          constBank[innerIndex] ? *constBank[innerIndex] : dig[resultValue++];
      buildPoint += valueHandle * lowerIndex.strides[innerIndex];
    }
    return buildPoint;
  }
};

static AffineMap canonicalAccess(AffineMap accessMap,
                                 SmallVectorImpl<Value> &operands) {
  affine::fullyComposeAffineMapAndOperands(&accessMap, &operands);
  affine::canonicalizeMapAndOperands(&accessMap, &operands);
  accessMap = foldConstantIndexOperands(accessMap, operands);
  affine::canonicalizeMapAndOperands(&accessMap, &operands);
  return simplifyAffineMap(accessMap);
}

struct AffineBanking {
  AffineMap bankedMap;
  BankChoice choice;
  SmallVector<AffineExpr> rotExprs;
};

static AffineBanking resolveAffine(AffineMap accessMap,
                                   ArrayRef<Value> operands,
                                   const BankLayout &lowerIndex) {
  unsigned nDims = accessMap.getNumDims();
  unsigned nSyms = accessMap.getNumSymbols();
  AffineBanking ab;
  SmallVector<AffineExpr, 4> results(accessMap.getResults().begin(),
                                     accessMap.getResults().end());
  for (unsigned innerIndex = 0; innerIndex < lowerIndex.dims.size();
       ++innerIndex) {
    const DimPartition &portValue = lowerIndex.dims[innerIndex];
    auto [bankExpr, offsetExpr] =
        bankAndOffset(accessMap.getResult(portValue.dim), portValue);
    AffineExpr simp = simplifyAffineExpr(bankExpr, nDims, nSyms);
    results[portValue.dim] = offsetExpr;
    std::optional<int64_t> candidateValue;
    if (auto ce = dyn_cast<AffineConstantExpr>(simp))
      candidateValue = ce.getValue();
    else
      candidateValue =
          constantBankThroughInductionVars(accessMap, operands, portValue);
    ab.choice.constBank.push_back(candidateValue);
    if (!candidateValue) {
      ab.choice.rotating.push_back(innerIndex);
      ab.rotExprs.push_back(simp);
    }
  }
  ab.bankedMap = AffineMap::get(nDims, nSyms, results, accessMap.getContext());
  return ab;
}

static AffineMap rotatingIndexMap(const AffineBanking &ab,
                                  const BankLayout &lowerIndex, unsigned nDims,
                                  unsigned nSyms) {
  AffineExpr entryValue = ab.rotExprs[0];
  for (unsigned loopIndex = 1; loopIndex < ab.rotExprs.size(); ++loopIndex)
    entryValue =
        entryValue * lowerIndex.dims[ab.choice.rotating[loopIndex]].factor +
        ab.rotExprs[loopIndex];
  if (ab.rotExprs.size() > 1)
    entryValue = simplifyAffineExpr(entryValue, nDims, nSyms);
  return AffineMap::get(nDims, nSyms, entryValue);
}

static void rewriteAffineLoad(affine::AffineLoadOp loadOp,
                              ArrayRef<Value> banks,
                              const BankLayout &lowerIndex) {
  OpBuilder buildPoint(loadOp);
  Location loc = loadOp.getLoc();
  SmallVector<Value, 4> operands(loadOp.getMapOperands().begin(),
                                 loadOp.getMapOperands().end());
  AffineMap accessMap = canonicalAccess(loadOp.getAffineMap(), operands);
  AffineBanking ab = resolveAffine(accessMap, operands, lowerIndex);
  if (ab.choice.rotating.empty()) {

    auto nl = affine::AffineLoadOp::create(buildPoint, loc,
                                           banks[ab.choice.bank(lowerIndex, 0)],
                                           ab.bankedMap, operands);
    loadOp.replaceAllUsesWith(nl.getResult());
    loadOp.erase();
    return;
  }

  Value bankIdx = affine::AffineApplyOp::create(
      buildPoint, loc,
      rotatingIndexMap(ab, lowerIndex, accessMap.getNumDims(),
                       accessMap.getNumSymbols()),
      operands);
  int64_t elementCount = ab.choice.numCandidates(lowerIndex);
  SmallVector<Value, 8> vals;
  for (int64_t keyValue = 0; keyValue < elementCount; ++keyValue)
    vals.push_back(affine::AffineLoadOp::create(
        buildPoint, loc, banks[ab.choice.bank(lowerIndex, keyValue)],
        ab.bankedMap, operands));
  Value result = vals[elementCount - 1];
  for (int64_t keyValue = elementCount - 1; keyValue-- > 0;) {
    Value kc = arith::ConstantIndexOp::create(buildPoint, loc, keyValue);
    Value eq = arith::CmpIOp::create(buildPoint, loc, arith::CmpIPredicate::eq,
                                     bankIdx, kc);
    result =
        arith::SelectOp::create(buildPoint, loc, eq, vals[keyValue], result);
  }
  loadOp.replaceAllUsesWith(result);
  loadOp.erase();
}

static void rewriteAffineStore(affine::AffineStoreOp storeOp,
                               ArrayRef<Value> banks,
                               const BankLayout &lowerIndex) {
  OpBuilder buildPoint(storeOp);
  Location loc = storeOp.getLoc();
  Value operandValue = storeOp.getValueToStore();
  SmallVector<Value, 4> operands(storeOp.getMapOperands().begin(),
                                 storeOp.getMapOperands().end());
  AffineMap accessMap = canonicalAccess(storeOp.getAffineMap(), operands);
  AffineBanking ab = resolveAffine(accessMap, operands, lowerIndex);
  if (ab.choice.rotating.empty()) {
    affine::AffineStoreOp::create(buildPoint, loc, operandValue,
                                  banks[ab.choice.bank(lowerIndex, 0)],
                                  ab.bankedMap, operands);
    storeOp.erase();
    return;
  }

  unsigned nDims = accessMap.getNumDims();
  unsigned nSyms = accessMap.getNumSymbols();
  int64_t elementCount = ab.choice.numCandidates(lowerIndex);
  for (int64_t keyValue = 0; keyValue < elementCount; ++keyValue) {
    SmallVector<int64_t> dig = ab.choice.digits(lowerIndex, keyValue);
    SmallVector<AffineExpr> constraints;
    SmallVector<bool> eqFlags;
    for (unsigned loopIndex = 0; loopIndex < dig.size(); ++loopIndex) {
      constraints.push_back(ab.rotExprs[loopIndex] - dig[loopIndex]);
      eqFlags.push_back(true);
    }
    IntegerSet cond = IntegerSet::get(nDims, nSyms, constraints, eqFlags);
    AffineStoreEnableOp::create(buildPoint, loc, operandValue,
                                banks[ab.choice.bank(lowerIndex, keyValue)],
                                operands, operands, ab.bankedMap, cond);
  }
  storeOp.erase();
}

struct MemrefBanking {
  SmallVector<Value, 4> bankedIndices;
  BankChoice choice;
  Value rotIdx;
};

static MemrefBanking resolveMemref(OpBuilder &buildPoint, Location loc,
                                   ValueRange indices,
                                   const BankLayout &lowerIndex) {
  MemrefBanking mb;
  mb.bankedIndices.assign(indices.begin(), indices.end());
  SmallVector<Value> rot;
  for (unsigned innerIndex = 0; innerIndex < lowerIndex.dims.size();
       ++innerIndex) {
    const DimPartition &portValue = lowerIndex.dims[innerIndex];
    Value indexValue = indices[portValue.dim];
    if (auto candidateValue = getConstantIndexValue(indexValue)) {
      auto [bank, off] = bankAndOffset(*candidateValue, portValue);
      mb.choice.constBank.push_back(bank);
      mb.bankedIndices[portValue.dim] =
          arith::ConstantIndexOp::create(buildPoint, loc, off);
      continue;
    }

    bool bankIsDiv = portValue.kind == PartitionSpec::Block;
    int64_t divisor = bankIsDiv ? portValue.depth : portValue.factor;
    Value dimensionIndex =
        arith::ConstantIndexOp::create(buildPoint, loc, divisor);
    Value bankV = bankIsDiv ? arith::DivUIOp::create(buildPoint, loc,
                                                     indexValue, dimensionIndex)
                                  .getResult()
                            : arith::RemUIOp::create(buildPoint, loc,
                                                     indexValue, dimensionIndex)
                                  .getResult();
    Value offV = bankIsDiv ? arith::RemUIOp::create(buildPoint, loc, indexValue,
                                                    dimensionIndex)
                                 .getResult()
                           : arith::DivUIOp::create(buildPoint, loc, indexValue,
                                                    dimensionIndex)
                                 .getResult();
    mb.bankedIndices[portValue.dim] = offV;
    mb.choice.constBank.push_back(std::nullopt);
    mb.choice.rotating.push_back(innerIndex);
    rot.push_back(bankV);
  }
  if (!rot.empty()) {
    mb.rotIdx = rot[0];
    for (unsigned loopIndex = 1; loopIndex < rot.size(); ++loopIndex) {
      Value fieldValue = arith::ConstantIndexOp::create(
          buildPoint, loc,
          lowerIndex.dims[mb.choice.rotating[loopIndex]].factor);
      Value mul = arith::MulIOp::create(buildPoint, loc, mb.rotIdx, fieldValue);
      mb.rotIdx = arith::AddIOp::create(buildPoint, loc, mul, rot[loopIndex]);
    }
  }
  return mb;
}

static void rewriteMemrefLoad(memref::LoadOp loadOp, ArrayRef<Value> banks,
                              const BankLayout &lowerIndex) {
  OpBuilder buildPoint(loadOp);
  Location loc = loadOp.getLoc();
  MemrefBanking mb =
      resolveMemref(buildPoint, loc, loadOp.getIndices(), lowerIndex);
  if (mb.choice.rotating.empty()) {
    auto nl = memref::LoadOp::create(buildPoint, loc,
                                     banks[mb.choice.bank(lowerIndex, 0)],
                                     mb.bankedIndices);
    loadOp.replaceAllUsesWith(nl.getResult());
    loadOp.erase();
    return;
  }
  int64_t elementCount = mb.choice.numCandidates(lowerIndex);
  SmallVector<Value, 8> vals;
  for (int64_t keyValue = 0; keyValue < elementCount; ++keyValue)
    vals.push_back(memref::LoadOp::create(
        buildPoint, loc, banks[mb.choice.bank(lowerIndex, keyValue)],
        mb.bankedIndices));
  Value result = vals[elementCount - 1];
  for (int64_t keyValue = elementCount - 1; keyValue-- > 0;) {
    Value kc = arith::ConstantIndexOp::create(buildPoint, loc, keyValue);
    Value eq = arith::CmpIOp::create(buildPoint, loc, arith::CmpIPredicate::eq,
                                     mb.rotIdx, kc);
    result =
        arith::SelectOp::create(buildPoint, loc, eq, vals[keyValue], result);
  }
  loadOp.replaceAllUsesWith(result);
  loadOp.erase();
}

static std::pair<Value, int64_t> residueBase(Value valueHandle,
                                             int64_t factor) {
  bool pow2 = llvm::isPowerOf2_64(static_cast<uint64_t>(factor));
  unsigned bits = llvm::Log2_64(static_cast<uint64_t>(factor));
  auto constOf = [](Value exprValue) -> std::optional<int64_t> {
    if (auto candidateValue = getConstantIndexValue(exprValue))
      return candidateValue;
    if (auto cast = exprValue.getDefiningOp<arith::IndexCastOp>())
      exprValue = cast.getIn();
    if (auto apply = exprValue.getDefiningOp<affine::AffineApplyOp>()) {
      SmallVector<Attribute> attrs;
      for (Value opHandle : apply.getMapOperands()) {
        std::optional<int64_t> candidateValue = getConstantIndexValue(opHandle);
        if (!candidateValue)
          return std::nullopt;
        attrs.push_back(IntegerAttr::get(opHandle.getType(), *candidateValue));
      }
      SmallVector<Attribute> passResult;
      if (succeeded(apply.getAffineMap().constantFold(attrs, passResult)) &&
          passResult.size() == 1)
        if (auto ia = dyn_cast<IntegerAttr>(passResult.front()))
          return ia.getInt();
    }
    return std::nullopt;
  };
  int64_t candidateValue = 0;
  for (unsigned guard = 0; guard < 32; ++guard) {
    Operation *def = valueHandle.getDefiningOp();
    if (!def)
      break;
    if (isa<arith::IndexCastOp, arith::IndexCastUIOp, arith::ExtSIOp,
            arith::ExtUIOp>(def)) {
      valueHandle = def->getOperand(0);
      continue;
    }
    if (auto tr = dyn_cast<arith::TruncIOp>(def)) {
      if (!pow2 || tr.getType().getIntOrFloatBitWidth() < bits)
        break;
      valueHandle = tr.getIn();
      continue;
    }
    if (isa<arith::AndIOp, arith::AddIOp>(def)) {
      Value lhs = def->getOperand(0), rhs = def->getOperand(1);
      std::optional<int64_t> keyValue = constOf(rhs);
      if (!keyValue) {
        keyValue = constOf(lhs);
        std::swap(lhs, rhs);
      }
      if (!keyValue)
        break;
      if (isa<arith::AndIOp>(def)) {
        uint64_t low = (uint64_t(1) << bits) - 1;
        if (!pow2 || (static_cast<uint64_t>(*keyValue) & low) != low)
          break;
      } else {
        candidateValue += *keyValue;
      }
      valueHandle = lhs;
      continue;
    }
    break;
  }
  return {valueHandle, candidateValue};
}

static bool hoistBefore(Value valueHandle, Operation *before, bool dryRun,
                        unsigned depth = 0) {
  Operation *def = valueHandle.getDefiningOp();
  if (!def || def->getBlock() != before->getBlock() ||
      def->isBeforeInBlock(before) || def == before)
    return def != before;
  if (depth > 64 || def->getNumRegions() || !isMemoryEffectFree(def))
    return false;
  for (Value opHandle : def->getOperands())
    if (!hoistBefore(opHandle, before, dryRun, depth + 1))
      return false;
  if (!dryRun)
    def->moveBefore(before);
  return true;
}

static void steerLoadGroups(Value site, ArrayRef<Value> banks,
                            const BankLayout &lowerIndex) {
  if (lowerIndex.dims.size() != 1 ||
      lowerIndex.dims.front().kind == PartitionSpec::Block)
    return;
  const DimPartition &portValue = lowerIndex.dims.front();
  int64_t fieldValue = portValue.factor;
  if (static_cast<int64_t>(banks.size()) != fieldValue || fieldValue < 2)
    return;

  llvm::MapVector<std::pair<Block *, Value>,
                  SmallVector<std::pair<memref::LoadOp, int64_t>>>
      groups;
  for (Operation *user : site.getUsers()) {
    auto ld = dyn_cast<memref::LoadOp>(user);
    if (!ld || ld.getMemRef() != site ||
        getConstantIndexValue(ld.getIndices()[portValue.dim]))
      continue;
    auto [base, candidateValue] =
        residueBase(ld.getIndices()[portValue.dim], fieldValue);
    groups[{ld->getBlock(), base}].push_back({ld, candidateValue});
  }
  for (auto &[key, members] : groups) {
    if (members.size() < 2)
      continue;
    llvm::SmallDenseSet<int64_t> residues;
    for (auto &memoryOp : members)
      residues.insert(((memoryOp.second % fieldValue) + fieldValue) %
                      fieldValue);
    if (residues.size() != members.size())
      continue;
    llvm::sort(members, [](auto &arrayValue, auto &buildPoint) {
      return arrayValue.first->isBeforeInBlock(buildPoint.first);
    });
    Operation *first = members.front().first;
    bool movable = llvm::all_of(members, [&](auto &memoryOp) {
      return llvm::all_of(memoryOp.first.getIndices(), [&](Value loopIndex) {
        return hoistBefore(loopIndex, first, true);
      });
    });
    if (!movable)
      continue;
    for (auto &memoryOp : members)
      for (Value loopIndex : memoryOp.first.getIndices())
        hoistBefore(loopIndex, first, false);
    OpBuilder buildPoint(first);
    Location loc = first->getLoc();

    SmallVector<MemrefBanking> mbs;
    for (auto &memoryOp : members)
      mbs.push_back(resolveMemref(buildPoint, loc, memoryOp.first.getIndices(),
                                  lowerIndex));

    SmallVector<SmallVector<Value>> hit(members.size());
    for (auto [innerIndex, mb] : llvm::enumerate(mbs))
      for (int64_t keyValue = 0; keyValue < fieldValue; ++keyValue)
        hit[innerIndex].push_back(arith::CmpIOp::create(
            buildPoint, loc, arith::CmpIPredicate::eq, mb.rotIdx,
            arith::ConstantIndexOp::create(buildPoint, loc, keyValue)));
    SmallVector<Value> bankVals;
    for (int64_t keyValue = 0; keyValue < fieldValue; ++keyValue) {
      SmallVector<Value> indexValue(mbs.back().bankedIndices.begin(),
                                    mbs.back().bankedIndices.end());
      for (unsigned dimensionIndex = 0; dimensionIndex < indexValue.size();
           ++dimensionIndex)
        for (size_t innerIndex = mbs.size() - 1; innerIndex-- > 0;)
          if (mbs[innerIndex].bankedIndices[dimensionIndex] !=
              indexValue[dimensionIndex])
            indexValue[dimensionIndex] = arith::SelectOp::create(
                buildPoint, loc, hit[innerIndex][keyValue],
                mbs[innerIndex].bankedIndices[dimensionIndex],
                indexValue[dimensionIndex]);
      bankVals.push_back(
          memref::LoadOp::create(buildPoint, loc, banks[keyValue], indexValue));
    }
    SmallVector<Value> results;
    for (size_t innerIndex = 0; innerIndex < members.size(); ++innerIndex) {
      Value resultValue = bankVals[fieldValue - 1];
      for (int64_t keyValue = fieldValue - 1; keyValue-- > 0;)
        resultValue =
            arith::SelectOp::create(buildPoint, loc, hit[innerIndex][keyValue],
                                    bankVals[keyValue], resultValue);
      results.push_back(resultValue);
    }
    for (auto [memoryOp, resultValue] : llvm::zip(members, results)) {
      memoryOp.first.replaceAllUsesWith(resultValue);
      memoryOp.first.erase();
    }
  }
}

static void rewriteMemrefStore(memref::StoreOp storeOp, ArrayRef<Value> banks,
                               const BankLayout &lowerIndex) {
  OpBuilder buildPoint(storeOp);
  Location loc = storeOp.getLoc();
  Value operandValue = storeOp.getValueToStore();
  MemrefBanking mb =
      resolveMemref(buildPoint, loc, storeOp.getIndices(), lowerIndex);
  if (mb.choice.rotating.empty()) {
    memref::StoreOp::create(buildPoint, loc, operandValue,
                            banks[mb.choice.bank(lowerIndex, 0)],
                            mb.bankedIndices);
  } else {
    int64_t elementCount = mb.choice.numCandidates(lowerIndex);
    for (int64_t keyValue = 0; keyValue < elementCount; ++keyValue) {
      Value kc = arith::ConstantIndexOp::create(buildPoint, loc, keyValue);
      Value en = arith::CmpIOp::create(buildPoint, loc,
                                       arith::CmpIPredicate::eq, mb.rotIdx, kc);

      StoreEnableOp::create(buildPoint, loc, operandValue, en,
                            banks[mb.choice.bank(lowerIndex, keyValue)],
                            mb.bankedIndices);
    }
  }
  storeOp.erase();
}

class BankingPlan {
public:
  explicit BankingPlan(ModuleOp module) : module(module), symbols(module) {}

  void run() {
    partitions.emplace(module, true);
    assignCalleeForms();
    bank();
  }

private:
  ModuleOp module;
  SymbolTable symbols;

  std::optional<PartitionRoots> partitions;

  DenseMap<Operation *, Operation *> originOf;

  DenseMap<Operation *, SmallVector<std::pair<std::string, func::FuncOp>>>
      formsOf;

  llvm::MapVector<Operation *, SmallVector<std::optional<BankLayout>>>
      paramLayouts;
  unsigned clonesMade = 0;

  DenseMap<Value, SmallVector<Value>> banksOf;

  std::optional<BankLayout> layoutOfValue(Value valueHandle, func::FuncOp fn);
  void assignCalleeForms();
  void bank();

  DictionaryAttr partitionAttr(OpBuilder &buildPoint,
                               const BankLayout &lowerIndex);
  DictionaryAttr bankAttrs(OpBuilder &buildPoint, const BankLayout &lowerIndex,
                           unsigned bankIdx, Operation *from, StringRef bankOf);
  SmallVector<Value> createAllocaBanks(memref::AllocaOp localAlloca,
                                       const BankLayout &lowerIndex);
  void createGlobalBanks(memref::GlobalOp globalOp, ArrayRef<Value> sites,
                         const BankLayout &lowerIndex);
  void rewriteAccesses(Value site, const BankLayout &lowerIndex);
  void rewriteCalls();
};

std::optional<BankLayout> BankingPlan::layoutOfValue(Value valueHandle,
                                                     func::FuncOp fn) {
  if (auto arg = dyn_cast<BlockArgument>(valueHandle)) {
    if (arg.getOwner() != &fn.getBody().front())
      return std::nullopt;
    auto it = paramLayouts.find(fn.getOperation());
    if (it == paramLayouts.end() || arg.getArgNumber() >= it->second.size())
      return std::nullopt;
    return it->second[arg.getArgNumber()];
  }
  Operation *def = valueHandle.getDefiningOp();
  if (!def)
    return std::nullopt;
  if (auto globalUse = dyn_cast<memref::GetGlobalOp>(def))
    def = symbols.lookup(globalUse.getName());
  else if (!isa<memref::AllocaOp>(def))
    return std::nullopt;
  if (Operation *orig = originOf.lookup(def))
    def = orig;
  return partitions->layoutOf(def);
}

void BankingPlan::assignCalleeForms() {

  SmallVector<func::FuncOp> work;
  for (auto fn : module.getOps<func::FuncOp>())
    if (!fn.isExternal() && !partitions->called().contains(fn.getOperation())) {
      paramLayouts[fn.getOperation()].assign(fn.getNumArguments(),
                                             std::nullopt);
      work.push_back(fn);
    }
  for (unsigned widthValue = 0; widthValue < work.size() && widthValue < 100000;
       ++widthValue) {
    func::FuncOp fn = work[widthValue];
    SmallVector<func::CallOp> calls;
    fn.walk(
        [&](func::CallOp candidateValue) { calls.push_back(candidateValue); });
    for (func::CallOp callSite : calls) {
      func::FuncOp now = resolveDefinedCallee(callSite);
      if (!now)
        continue;
      Operation *origOp = originOf.lookup(now.getOperation());
      auto orig = origOp ? cast<func::FuncOp>(origOp) : now;
      SmallVector<std::optional<BankLayout>> layouts(orig.getNumArguments(),
                                                     std::nullopt);
      for (auto [loopIndex, valueHandle] :
           llvm::enumerate(callSite.getArgOperands()))
        if (loopIndex < layouts.size() &&
            isa<MemRefType>(valueHandle.getType()))
          layouts[loopIndex] = layoutOfValue(valueHandle, fn);
      std::string key = partitionFormKey(layouts);
      auto &forms = formsOf[orig.getOperation()];
      func::FuncOp inst;
      for (auto &[keyValue, fieldValue] : forms)
        if (keyValue == key)
          inst = fieldValue;
      if (!inst) {
        if (forms.empty()) {
          inst = orig;
        } else {

          IRMapping map;
          inst = cast<func::FuncOp>(orig->clone(map));
          orig.walk([&](memref::AllocaOp arrayValue) {
            if (Value candidateValue = map.lookupOrNull(arrayValue.getResult()))
              originOf[candidateValue.getDefiningOp()] =
                  arrayValue.getOperation();
          });
          inst.setName((orig.getName() + "_form" + Twine(++clonesMade)).str());
          inst.setPrivate();
          symbols.insert(inst, std::next(Block::iterator(orig.getOperation())));
          originOf[inst.getOperation()] = orig.getOperation();
        }
        forms.push_back({key, inst});
        paramLayouts[inst.getOperation()] = layouts;
        work.push_back(inst);
      }
      if (inst != now)
        callSite.setCalleeAttr(FlatSymbolRefAttr::get(inst.getSymNameAttr()));
    }
  }

  for (auto &[origOp, forms] : formsOf) {
    auto orig = cast<func::FuncOp>(origOp);
    if (orig.isPrivate() && symbols.symbolKnownUseEmpty(orig, module))
      paramLayouts.erase(origOp), symbols.erase(orig);
  }
}

DictionaryAttr BankingPlan::partitionAttr(OpBuilder &buildPoint,
                                          const BankLayout &lowerIndex) {
  auto kindName = [](PartitionSpec::Kind keyValue) {
    return keyValue == PartitionSpec::Complete ? "complete"
           : keyValue == PartitionSpec::Block  ? "block"
                                               : "cyclic";
  };
  auto dimDict = [&](const DimPartition &portValue, bool withSource) {
    SmallVector<NamedAttribute> fieldValue{
        buildPoint.getNamedAttr(
            "kind", buildPoint.getStringAttr(kindName(portValue.kind))),
        buildPoint.getNamedAttr("factor",
                                buildPoint.getI32IntegerAttr(
                                    static_cast<int32_t>(portValue.factor))),
        buildPoint.getNamedAttr("dim",
                                buildPoint.getI32IntegerAttr(
                                    static_cast<int32_t>(portValue.dim + 1)))};
    if (withSource)
      fieldValue.push_back(buildPoint.getNamedAttr(
          "source", portValue.source ? portValue.source
                                     : buildPoint.getStringAttr("pragma")));
    return fieldValue;
  };

  SmallVector<NamedAttribute> fields = dimDict(lowerIndex.dims.front(), true);
  if (lowerIndex.dims.size() > 1) {
    SmallVector<Attribute> all;
    for (const DimPartition &portValue : lowerIndex.dims)
      all.push_back(buildPoint.getDictionaryAttr(dimDict(portValue, false)));
    fields.push_back(
        buildPoint.getNamedAttr("dims", buildPoint.getArrayAttr(all)));
  }
  if (!lowerIndex.dims.front().from.empty())
    fields.push_back(buildPoint.getNamedAttr(
        "from", buildPoint.getStringAttr(lowerIndex.dims.front().from)));
  return buildPoint.getDictionaryAttr(fields);
}

DictionaryAttr BankingPlan::bankAttrs(OpBuilder &buildPoint,
                                      const BankLayout &lowerIndex,
                                      unsigned bankIdx, Operation *from,
                                      StringRef bankOf) {

  SmallVector<NamedAttribute, 8> attrs;
  if (from)
    for (StringRef name :
         {"polygeist.varname", "hls.preserve", "hls.partition_reason",
          "hls.kept_reason", "hls.const_fill", "hls.stream", "hls.bind_storage",
          "hls.narrow_bits", "hls.narrow_reason"})
      if (Attribute arrayValue = from->getAttr(name))
        attrs.push_back(buildPoint.getNamedAttr(name, arrayValue));
  if (!bankOf.empty())
    attrs.push_back(buildPoint.getNamedAttr("hls.bank_of",
                                            buildPoint.getStringAttr(bankOf)));
  attrs.push_back(buildPoint.getNamedAttr(
      "hls.bank_index",
      buildPoint.getI32IntegerAttr(static_cast<int32_t>(bankIdx))));
  attrs.push_back(buildPoint.getNamedAttr(
      "hls.bank_count",
      buildPoint.getI32IntegerAttr(static_cast<int32_t>(lowerIndex.numBanks))));
  attrs.push_back(buildPoint.getNamedAttr(
      "hls.partition", partitionAttr(buildPoint, lowerIndex)));
  return buildPoint.getDictionaryAttr(attrs);
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
    if (auto fn = def->getParentOfType<func::FuncOp>())
      fn.walk([&](Operation *op) {
        if (op == def)
          return WalkResult::interrupt();
        if (isa<MemoryResourceOpInterface>(op) && !op->hasAttr("hls.partition"))
          ++ordinal;
        return WalkResult::advance();
      });
  return "<unnamed#" + std::to_string(ordinal) + ">";
}

SmallVector<Value>
BankingPlan::createAllocaBanks(memref::AllocaOp localAlloca,
                               const BankLayout &lowerIndex) {
  OpBuilder buildPoint(localAlloca->getContext());
  buildPoint.setInsertionPointAfter(localAlloca);
  Attribute varName = localAlloca->getAttr("polygeist.varname");
  std::string bankOf = varName ? cast<StringAttr>(varName).getValue().str()
                               : unnamedBankOf(localAlloca.getResult());
  SmallVector<Value> banks;
  for (int64_t loopIndex = 0; loopIndex < lowerIndex.numBanks; ++loopIndex) {
    auto bank = memref::AllocaOp::create(buildPoint, localAlloca.getLoc(),
                                         lowerIndex.bankType);
    bank->setAttrs(bankAttrs(buildPoint, lowerIndex,
                             static_cast<unsigned>(loopIndex), localAlloca,
                             bankOf));
    banks.push_back(bank.getResult());
  }
  return banks;
}

static SmallVector<SmallVector<Attribute>>
sliceInitialValue(DenseElementsAttr initialValue, MemRefType memRefType,
                  const BankLayout &lowerIndex) {
  ArrayRef<int64_t> shape = memRefType.getShape();
  ArrayRef<int64_t> bankShape = lowerIndex.bankType.getShape();
  int64_t perBank = 1;
  for (int64_t dimensionIndex : bankShape)
    perBank *= dimensionIndex;
  Attribute zero = OpBuilder(memRefType.getContext())
                       .getZeroAttr(memRefType.getElementType());
  SmallVector<SmallVector<Attribute>> out(
      lowerIndex.numBanks, SmallVector<Attribute>(perBank, zero));
  SmallVector<Attribute> all(initialValue.getValues<Attribute>().begin(),
                             initialValue.getValues<Attribute>().end());
  int64_t rank = shape.size();
  SmallVector<int64_t> nd(rank);
  for (int64_t lin = 0; lin < static_cast<int64_t>(all.size()); ++lin) {
    int64_t rest = lin;
    for (int64_t dimensionIndex = rank - 1; dimensionIndex >= 0;
         --dimensionIndex) {
      nd[dimensionIndex] = rest % shape[dimensionIndex];
      rest /= shape[dimensionIndex];
    }
    int64_t bank = 0;
    for (unsigned innerIndex = 0; innerIndex < lowerIndex.dims.size();
         ++innerIndex) {
      auto [bk, off] = bankAndOffset(nd[lowerIndex.dims[innerIndex].dim],
                                     lowerIndex.dims[innerIndex]);
      bank += bk * lowerIndex.strides[innerIndex];
      nd[lowerIndex.dims[innerIndex].dim] = off;
    }
    int64_t pos = 0;
    for (int64_t dimensionIndex = 0; dimensionIndex < rank; ++dimensionIndex)
      pos = pos * bankShape[dimensionIndex] + nd[dimensionIndex];
    out[bank][pos] = all[lin];
  }
  return out;
}

void BankingPlan::createGlobalBanks(memref::GlobalOp globalOp,
                                    ArrayRef<Value> sites,
                                    const BankLayout &lowerIndex) {
  OpBuilder buildPoint(globalOp->getContext());
  MemRefType memRefType = globalOp.getType();
  SmallVector<SmallVector<Attribute>> initialValue;
  std::optional<Attribute> initial = globalOp.getInitialValue();
  auto denseValue =
      initial ? dyn_cast<DenseElementsAttr>(*initial) : DenseElementsAttr();
  if (denseValue)
    initialValue = sliceInitialValue(denseValue, memRefType, lowerIndex);
  std::string bankOf = globalOp.getSymName().str();
  buildPoint.setInsertionPointAfter(globalOp);
  SmallVector<memref::GlobalOp> bankGlobals;
  for (int64_t loopIndex = 0; loopIndex < lowerIndex.numBanks; ++loopIndex) {
    std::string name =
        llvm::formatv("{0}_bank_{1}", globalOp.getSymName(), loopIndex);
    Attribute initAttr;
    if (denseValue)
      initAttr = DenseElementsAttr::get(
          RankedTensorType::get(lowerIndex.bankType.getShape(),
                                memRefType.getElementType()),
          initialValue[loopIndex]);
    else if (initial)
      initAttr = *initial;
    auto bg = memref::GlobalOp::create(
        buildPoint, globalOp.getLoc(), buildPoint.getStringAttr(name),
        globalOp.getSymVisibilityAttr(), TypeAttr::get(lowerIndex.bankType),
        initAttr, globalOp.getConstantAttr(), globalOp.getAlignmentAttr());
    for (NamedAttribute arrayValue :
         bankAttrs(buildPoint, lowerIndex, static_cast<unsigned>(loopIndex),
                   globalOp, bankOf))
      bg->setAttr(arrayValue.getName(), arrayValue.getValue());
    symbols.insert(bg);
    buildPoint.setInsertionPointAfter(bg);
    bankGlobals.push_back(bg);
  }
  for (Value site : sites) {
    auto globalUse = site.getDefiningOp<memref::GetGlobalOp>();
    OpBuilder sb(globalUse);
    sb.setInsertionPointAfter(globalUse);
    SmallVector<Value> banks;
    for (int64_t loopIndex = 0; loopIndex < lowerIndex.numBanks; ++loopIndex)
      banks.push_back(memref::GetGlobalOp::create(
                          sb, globalUse.getLoc(), lowerIndex.bankType,
                          bankGlobals[loopIndex].getSymName())
                          .getResult());
    banksOf[site] = std::move(banks);
  }
}

void BankingPlan::rewriteAccesses(Value site, const BankLayout &lowerIndex) {
  SmallVector<Value> banks = banksOf[site];
  steerLoadGroups(site, banks, lowerIndex);
  SmallVector<Operation *> users(site.getUsers().begin(),
                                 site.getUsers().end());
  for (Operation *user : users) {
    if (auto ld = dyn_cast<affine::AffineLoadOp>(user))
      rewriteAffineLoad(ld, banks, lowerIndex);
    else if (auto st = dyn_cast<affine::AffineStoreOp>(user))
      rewriteAffineStore(st, banks, lowerIndex);
    else if (auto ld = dyn_cast<memref::LoadOp>(user))
      rewriteMemrefLoad(ld, banks, lowerIndex);
    else if (auto st = dyn_cast<memref::StoreOp>(user))
      rewriteMemrefStore(st, banks, lowerIndex);
  }
}

void BankingPlan::rewriteCalls() {
  SmallVector<func::CallOp> calls;
  module.walk([&](func::CallOp callSite) {
    if (llvm::any_of(callSite.getArgOperands(), [&](Value valueHandle) {
          return banksOf.count(valueHandle);
        }))
      calls.push_back(callSite);
  });
  for (func::CallOp callSite : calls) {
    SmallVector<Value> operands;
    for (Value valueHandle : callSite.getArgOperands()) {
      auto it = banksOf.find(valueHandle);
      if (it == banksOf.end())
        operands.push_back(valueHandle);
      else
        operands.append(it->second.begin(), it->second.end());
    }
    OpBuilder buildPoint(callSite);
    auto nc = func::CallOp::create(buildPoint, callSite.getLoc(),
                                   callSite.getCalleeAttr(),
                                   callSite.getResultTypes(), operands);
    for (NamedAttribute arrayValue : callSite->getDiscardableAttrs())
      nc->setDiscardableAttr(arrayValue.getName(), arrayValue.getValue());
    callSite.replaceAllUsesWith(nc.getResults());
    callSite.erase();
  }
}

void BankingPlan::bank() {
  MLIRContext *context = module.getContext();
  OpBuilder buildPoint(context);

  struct RootWork {
    Operation *op;
    SmallVector<Value> sites;
    BankLayout layout;
  };
  SmallVector<RootWork> roots;
  auto layoutOfRoot = [&](Operation *op) -> std::optional<BankLayout> {
    Operation *key = originOf.lookup(op);
    return partitions->layoutOf(key ? key : op);
  };
  for (auto globalOp : module.getOps<memref::GlobalOp>())
    if (auto lowerIndex = layoutOfRoot(globalOp.getOperation()))
      roots.push_back({globalOp.getOperation(), {}, *lowerIndex});
  module.walk([&](memref::AllocaOp arrayValue) {
    if (auto lowerIndex = layoutOfRoot(arrayValue.getOperation()))
      roots.push_back(
          {arrayValue.getOperation(), {arrayValue.getResult()}, *lowerIndex});
  });
  module.walk([&](memref::GetGlobalOp globalUse) {
    for (RootWork &resultValue : roots)
      if (auto globalOp = dyn_cast<memref::GlobalOp>(resultValue.op))
        if (globalOp.getSymName() == globalUse.getName())
          resultValue.sites.push_back(globalUse.getResult());
  });

  struct ParamWork {
    func::FuncOp fn;
    BlockArgument arg;
    BankLayout layout;
  };
  SmallVector<ParamWork> params;
  for (auto &[fnOp, layouts] : paramLayouts) {
    auto fn = cast<func::FuncOp>(fnOp);
    for (auto [loopIndex, lowerIndex] : llvm::enumerate(layouts))
      if (lowerIndex && loopIndex < fn.getNumArguments())
        params.push_back({fn, fn.getArgument(static_cast<unsigned>(loopIndex)),
                          *lowerIndex});
  }
  if (roots.empty() && params.empty())
    return;

  llvm::MapVector<Operation *, DenseMap<Value, DictionaryAttr>> origAttrs;
  DenseMap<Operation *, SmallVector<Value>> portBound;
  DenseMap<Value, DictionaryAttr> newArgAttrs;
  for (ParamWork &portValue : params) {
    auto [it, inserted] = origAttrs.insert({portValue.fn.getOperation(), {}});
    if (!inserted)
      continue;
    for (BlockArgument arrayValue : portValue.fn.getArguments())
      it->second[arrayValue] =
          portValue.fn.getArgAttrDict(arrayValue.getArgNumber());
    if (auto pb = portValue.fn->getAttrOfType<ArrayAttr>(kPortBoundArgsAttr))
      for (Attribute arrayValue : pb)
        if (auto loopIndex = dyn_cast<IntegerAttr>(arrayValue))
          if (loopIndex.getInt() >= 0 &&
              loopIndex.getInt() <
                  static_cast<int64_t>(portValue.fn.getNumArguments()))
            portBound[portValue.fn.getOperation()].push_back(
                portValue.fn.getArgument(
                    static_cast<unsigned>(loopIndex.getInt())));
  }

  for (RootWork &resultValue : roots) {
    if (auto arrayValue = dyn_cast<memref::AllocaOp>(resultValue.op))
      banksOf[arrayValue.getResult()] =
          createAllocaBanks(arrayValue, resultValue.layout);
    else
      createGlobalBanks(cast<memref::GlobalOp>(resultValue.op),
                        resultValue.sites, resultValue.layout);
  }
  for (ParamWork &portValue : params) {
    Block &entry = portValue.fn.getBody().front();
    SmallVector<Value> banks;
    std::string bankOf = "arg" + std::to_string(portValue.arg.getArgNumber());
    for (int64_t loopIndex = 0; loopIndex < portValue.layout.numBanks;
         ++loopIndex) {
      BlockArgument ba = entry.insertArgument(
          portValue.arg.getArgNumber() + 1 + static_cast<unsigned>(loopIndex),
          portValue.layout.bankType, portValue.arg.getLoc());
      newArgAttrs[ba] =
          bankAttrs(buildPoint, portValue.layout,
                    static_cast<unsigned>(loopIndex), nullptr, bankOf);
      banks.push_back(ba);
    }
    banksOf[portValue.arg] = std::move(banks);
  }

  for (RootWork &resultValue : roots)
    for (Value site : resultValue.sites)
      rewriteAccesses(site, resultValue.layout);
  for (ParamWork &portValue : params)
    rewriteAccesses(portValue.arg, portValue.layout);

  rewriteCalls();

  for (RootWork &resultValue : roots) {
    if (isa<memref::AllocaOp>(resultValue.op)) {
      resultValue.op->erase();
      continue;
    }
    for (Value site : resultValue.sites)
      site.getDefiningOp()->erase();
    symbols.erase(resultValue.op);
  }
  for (ParamWork &portValue : params)
    portValue.fn.getBody().front().eraseArgument(portValue.arg.getArgNumber());

  for (auto &[fnOp, orig] : origAttrs) {
    auto fn = cast<func::FuncOp>(fnOp);
    SmallVector<Type> types;
    SmallVector<DictionaryAttr> attrs;
    DenseMap<Value, int64_t> newIndex;
    for (BlockArgument arrayValue : fn.getArguments()) {
      types.push_back(arrayValue.getType());
      newIndex[arrayValue] = arrayValue.getArgNumber();
      DictionaryAttr dimensionIndex;
      if (auto it = newArgAttrs.find(arrayValue); it != newArgAttrs.end())
        dimensionIndex = it->second;
      else if (auto it2 = orig.find(arrayValue); it2 != orig.end())
        dimensionIndex = it2->second;
      attrs.push_back(dimensionIndex ? dimensionIndex
                                     : DictionaryAttr::get(context, {}));
    }
    fn.setFunctionType(
        FunctionType::get(context, types, fn.getFunctionType().getResults()));
    fn.setAllArgAttrs(attrs);
    auto pb = portBound.find(fnOp);
    if (pb != portBound.end()) {
      SmallVector<int64_t> indexValue;
      for (Value valueHandle : pb->second) {
        if (auto it = banksOf.find(valueHandle); it != banksOf.end()) {
          for (Value bv : it->second)
            indexValue.push_back(newIndex.lookup(bv));
        } else {
          indexValue.push_back(newIndex.lookup(valueHandle));
        }
      }
      llvm::sort(indexValue);
      fn->setAttr(kPortBoundArgsAttr, buildPoint.getI64ArrayAttr(indexValue));
    }
  }

  for (bool erased = true; erased;) {
    erased = false;
    SmallVector<Operation *> dead;
    module.walk([&](affine::AffineApplyOp ap) {
      if (isOpTriviallyDead(ap))
        dead.push_back(ap);
    });
    for (Operation *op : dead) {
      op->erase();
      erased = true;
    }
  }
}

struct MemoryBankingPass
    : public hls_analysis::impl::MemoryBankingBase<MemoryBankingPass> {
  void runOnOperation() override { BankingPlan(getOperation()).run(); }
};

} // namespace

namespace circt::hls_analysis {

static std::unique_ptr<mlir::Pass> createMemoryBankingPassModified() {
  return std::make_unique<MemoryBankingPass>();
}

void registerMemoryBankingPassModified() {
  mlir::PassRegistration<MemoryBankingPass>();
}

} // namespace circt::hls_analysis
