

// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#include "circt/Dialect/Resource/Config/ConfigUtils.h"
#include "circt/Dialect/Resource/HLS/HLSOps.h"
#include "circt/Dialect/Resource/Interfaces/MemoryDS.h"
#include "circt/Dialect/Resource/Passes/CallInstances.h"
#include "circt/Dialect/Resource/Passes/ConstantIndex.h"
#include "circt/Dialect/Resource/Passes/IterationPrivateBanks.h"
#include "circt/Dialect/Resource/Passes/MemrefBankClassification.h"
#include "circt/Dialect/Resource/Passes/PartitionLayout.h"
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
#include "mlir/IR/BuiltinOps.h"
#include "mlir/IR/IRMapping.h"
#include "mlir/IR/IntegerSet.h"
#include "mlir/IR/SymbolTable.h"
#include "mlir/Interfaces/SideEffectInterfaces.h"
#include "mlir/Pass/Pass.h"
#include "mlir/Support/LLVM.h"
#include "llvm/ADT/MapVector.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/ADT/SetVector.h"
#include "llvm/ADT/StringSet.h"
#include "llvm/Support/FormatVariadic.h"
#include "llvm/Support/MathExtras.h"

#include <circt/Dialect/Resource/Interfaces/MemoryOpInterface.h.inc>

#include <map>
#include <numeric>
#include <optional>
#include <set>
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

using IndexRange = std::pair<int64_t, int64_t>;
static std::optional<IndexRange>
rangeOf(AffineExpr entryValue, ArrayRef<Value> operands, unsigned nDims) {
  if (auto candidateValue = dyn_cast<AffineConstantExpr>(entryValue))
    return IndexRange{candidateValue.getValue(), candidateValue.getValue()};
  if (auto dimensionIndex = dyn_cast<AffineDimExpr>(entryValue)) {
    Value valueHandle = operands[dimensionIndex.getPosition()];
    if (!affine::isAffineForInductionVar(valueHandle))
      return std::nullopt;
    affine::AffineForOp owner = affine::getForInductionVarOwner(valueHandle);
    if (!owner.hasConstantBounds())
      return std::nullopt;
    int64_t lb = owner.getConstantLowerBound();
    int64_t ub = owner.getConstantUpperBound();
    int64_t step = owner.getStepAsInt();
    if (ub <= lb || step <= 0)
      return std::nullopt;
    return IndexRange{lb, lb + ((ub - 1 - lb) / step) * step};
  }
  auto bin = dyn_cast<AffineBinaryOpExpr>(entryValue);
  if (!bin)
    return std::nullopt;
  std::optional<IndexRange> lowerIndex = rangeOf(bin.getLHS(), operands, nDims);
  if (!lowerIndex)
    return std::nullopt;
  auto rc = dyn_cast<AffineConstantExpr>(bin.getRHS());
  switch (entryValue.getKind()) {
  case AffineExprKind::Add: {
    std::optional<IndexRange> resultValue =
        rangeOf(bin.getRHS(), operands, nDims);
    if (!resultValue)
      return std::nullopt;
    return IndexRange{lowerIndex->first + resultValue->first,
                      lowerIndex->second + resultValue->second};
  }
  case AffineExprKind::Mul: {
    if (!rc)
      return std::nullopt;
    int64_t arrayValue = lowerIndex->first * rc.getValue(),
            buildPoint = lowerIndex->second * rc.getValue();
    return IndexRange{std::min(arrayValue, buildPoint),
                      std::max(arrayValue, buildPoint)};
  }
  case AffineExprKind::FloorDiv: {
    if (!rc || rc.getValue() <= 0)
      return std::nullopt;
    return IndexRange{
        llvm::divideFloorSigned(lowerIndex->first, rc.getValue()),
        llvm::divideFloorSigned(lowerIndex->second, rc.getValue())};
  }
  case AffineExprKind::Mod: {
    if (!rc || rc.getValue() <= 0)
      return std::nullopt;
    int64_t memoryOp = rc.getValue();
    if (llvm::divideFloorSigned(lowerIndex->first, memoryOp) !=
        llvm::divideFloorSigned(lowerIndex->second, memoryOp))
      return IndexRange{0, memoryOp - 1};
    return IndexRange{llvm::mod(lowerIndex->first, memoryOp),
                      llvm::mod(lowerIndex->second, memoryOp)};
  }
  default:
    return std::nullopt;
  }
}

static std::optional<int64_t>
constantBankThroughRanges(AffineMap accessMap, ArrayRef<Value> operands,
                          const DimPartition &portValue) {
  if (portValue.kind != PartitionSpec::Block ||
      !circt::hlsest::Config::get()
           .tool.hls.partitioning.blockBankFromLoopRange)
    return std::nullopt;
  std::optional<IndexRange> resultValue = rangeOf(
      accessMap.getResult(portValue.dim), operands, accessMap.getNumDims());
  if (!resultValue || resultValue->first < 0 ||
      resultValue->second >= portValue.extent)
    return std::nullopt;
  int64_t lo = resultValue->first / portValue.depth,
          hi = resultValue->second / portValue.depth;
  if (lo != hi)
    return std::nullopt;
  return lo;
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
    if (!candidateValue)
      candidateValue =
          constantBankThroughRanges(accessMap, operands, portValue);
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

/// The candidate banks a rotating affine access can reach when nothing is
/// known about its operands but their integer structure, as LLVM's known
/// bits see an unrolled copy's index: ben_hall lab3's `Cl[i][jj + u] +=
/// t[jj + u]` (Cl complete on dim 2, jj stepping by 32 after a factor-32
/// unroll, `32 * d0 + u` once normalized) reaches only the indices congruent
/// to u modulo 32, banks u and u + 32, where every store became a
/// store_enable on all 64 banks (33 accesses per bank, ResMinII 17; Vitis
/// writes each bank once per iteration: OPEN_ISSUES O150, kernel
/// w9r8p_fl_pre). An affine.for counter is lb + step * t, every other
/// operand an unknown integer (a loop's upper bound is not used: a store at
/// `row[i][k]` with i in [1, 8) still reaches bank 0 in Vitis, vishnu lab3
/// row_ptr_A_local); the index is evaluated over one power-of-two period of
/// every operand and taken modulo that period (the known low bits), residues
/// outside the dimension are unreachable. nullopt (every candidate) when the
/// period space is large or no value is in range. Key
/// tool.hls.partitioning.reachable_store_banks.
static std::optional<SmallVector<int64_t>>
reachableCandidates(AffineMap accessMap, ArrayRef<Value> operands,
                    const AffineBanking &ab, const BankLayout &lowerIndex) {
  constexpr int64_t kMaxPoints = 1 << 14;
  unsigned nDims = accessMap.getNumDims();
  unsigned nSyms = accessMap.getNumSymbols();
  MLIRContext *context = accessMap.getContext();
  SmallVector<AffineExpr> idxExprs;
  int64_t extent = 1;
  for (unsigned resultValue : ab.choice.rotating) {
    const DimPartition &portValue = lowerIndex.dims[resultValue];
    idxExprs.push_back(accessMap.getResult(portValue.dim));
    extent = std::max(extent, portValue.extent);
  }

  SmallVector<unsigned> usedDims, usedSyms;
  {
    llvm::SmallSetVector<unsigned, 4> dimensionIndex, sy;
    for (AffineExpr entryValue : idxExprs)
      entryValue.walk([&](AffineExpr exprValue) {
        if (auto de = dyn_cast<AffineDimExpr>(exprValue))
          dimensionIndex.insert(de.getPosition());
        else if (auto se = dyn_cast<AffineSymbolExpr>(exprValue))
          sy.insert(se.getPosition());
      });
    usedDims.assign(dimensionIndex.begin(), dimensionIndex.end());
    usedSyms.assign(sy.begin(), sy.end());
  }
  SmallVector<int64_t> counterLb, counterStep;
  for (unsigned dimensionIndex : usedDims) {
    int64_t lb = 0, step = 1;
    if (affine::isAffineForInductionVar(operands[dimensionIndex])) {
      affine::AffineForOp owner =
          affine::getForInductionVarOwner(operands[dimensionIndex]);
      if (owner.hasConstantLowerBound()) {
        lb = owner.getConstantLowerBound();
        step = owner.getStepAsInt();
      }
    }
    counterLb.push_back(lb);
    counterStep.push_back(step);
  }
  unsigned nUsed = usedDims.size() + usedSyms.size();
  int64_t period = llvm::PowerOf2Ceil(static_cast<uint64_t>(extent));
  int64_t points = 1;
  for (unsigned loopIndex = 0; loopIndex < nUsed; ++loopIndex) {
    points *= period;
    if (points > kMaxPoints)
      return std::nullopt;
  }
  std::set<int64_t> hit;
  SmallVector<int64_t> typeValue(nUsed, 0);
  for (int64_t pt = 0; pt < points; ++pt) {
    SmallVector<AffineExpr> dimRepl, symRepl;
    for (unsigned loopIndex = 0; loopIndex < nDims; ++loopIndex)
      dimRepl.push_back(getAffineDimExpr(loopIndex, context));
    for (unsigned loopIndex = 0; loopIndex < nSyms; ++loopIndex)
      symRepl.push_back(getAffineSymbolExpr(loopIndex, context));

    for (unsigned useValue = 0; useValue < usedDims.size(); ++useValue)
      dimRepl[usedDims[useValue]] = getAffineConstantExpr(
          counterLb[useValue] + counterStep[useValue] * typeValue[useValue],
          context);
    for (unsigned useValue = 0; useValue < usedSyms.size(); ++useValue)
      symRepl[usedSyms[useValue]] =
          getAffineConstantExpr(typeValue[usedDims.size() + useValue], context);
    int64_t keyValue = 0;
    bool inRange = true;
    for (unsigned resultValue = 0; resultValue < idxExprs.size() && inRange;
         ++resultValue) {
      const DimPartition &portValue =
          lowerIndex.dims[ab.choice.rotating[resultValue]];
      auto candidateValue = dyn_cast<AffineConstantExpr>(simplifyAffineExpr(
          idxExprs[resultValue].replaceDimsAndSymbols(dimRepl, symRepl), nDims,
          nSyms));
      if (!candidateValue)
        return std::nullopt;

      int64_t indexValue = llvm::mod(candidateValue.getValue(), period);
      if (indexValue >= portValue.extent) {
        inRange = false;
        break;
      }
      int64_t bank = bankAndOffset(indexValue, portValue).first;
      if (bank < 0 || bank >= portValue.factor)
        return std::nullopt;
      keyValue = keyValue * portValue.factor + bank;
    }
    if (inRange)
      hit.insert(keyValue);
    for (unsigned useValue = 0; useValue < nUsed; ++useValue) {
      if (++typeValue[useValue] < period)
        break;
      typeValue[useValue] = 0;
    }
  }
  if (hit.empty())
    return std::nullopt;
  return SmallVector<int64_t>(hit.begin(), hit.end());
}

static bool reachableStoreBanks() {
  return circt::hlsest::Config::get().tool.hls.partitioning.reachableStoreBanks;
}

/// `hls.rotating_bank` on a load of a steered group (unrolled copies of one
/// read whose bank is chosen at run time, each bank read once per residue
/// member): such reads get one more replicated copy (VITIS_NOTES N115,
/// --bram-analysis). A lone rotating read (one load per candidate bank and
/// a mux) keeps N4's count: polybench_pragmas syrk, forgebench
/// mult_op_module_dot and the lab2 attention designs are Vitis' that way.
static void markRotatingRead(Operation *load) {
  load->setAttr("hls.rotating_bank", UnitAttr::get(load->getContext()));
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

/// An ap_fixed compound assignment (`A[b][i] /= c`, marked by cgeist) to a
/// bank chosen at run time: Vitis keeps two stores per bank, the
/// `if (!op) V = 0` at the head of the cross-format ap_fixed_base::operator=
/// and the final store; its DSE does not remove the first across the per-bank
/// switch (VITIS_NOTES N38 R-cmpd, kernels w9r_d1div / d2mul / d3add,
/// w9v_r_cyc; corpus nayan / sreenidhi / vishnu / kamya / pengzhao lab2).
/// So the array is never RAM_1WNR and the loop has two writes per bank.
/// cgeist's store forwarding leaves one store; the mark restores the other.
static bool compoundAssignTwoStores(Operation *store) {
  return store->hasAttr("hls.ap_compound_assign") &&
         circt::hlsest::Config::get()
             .tool.hls.partitioning.compoundAssignTwoStores;
}

/// Returns the store_enables left out because their bank is unreachable.
static unsigned rewriteAffineStore(affine::AffineStoreOp storeOp,
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
    return 0;
  }

  unsigned nDims = accessMap.getNumDims();
  unsigned nSyms = accessMap.getNumSymbols();
  int64_t elementCount = ab.choice.numCandidates(lowerIndex);
  SmallVector<int64_t> candidates;
  std::optional<SmallVector<int64_t>> reach;
  if (reachableStoreBanks())
    reach = reachableCandidates(accessMap, operands, ab, lowerIndex);
  if (reach)
    candidates = *reach;
  else
    for (int64_t keyValue = 0; keyValue < elementCount; ++keyValue)
      candidates.push_back(keyValue);
  for (int64_t keyValue : candidates) {
    SmallVector<int64_t> dig = ab.choice.digits(lowerIndex, keyValue);
    SmallVector<AffineExpr> constraints;
    SmallVector<bool> eqFlags;
    for (unsigned loopIndex = 0; loopIndex < dig.size(); ++loopIndex) {
      constraints.push_back(ab.rotExprs[loopIndex] - dig[loopIndex]);
      eqFlags.push_back(true);
    }
    IntegerSet cond = IntegerSet::get(nDims, nSyms, constraints, eqFlags);
    if (compoundAssignTwoStores(storeOp)) {
      auto extra = AffineStoreEnableOp::create(
          buildPoint, loc, operandValue,
          banks[ab.choice.bank(lowerIndex, keyValue)], operands, operands,
          ab.bankedMap, cond);
      extra->setAttr("hls.compound_assign_store", buildPoint.getUnitAttr());
    }
    AffineStoreEnableOp::create(buildPoint, loc, operandValue,
                                banks[ab.choice.bank(lowerIndex, keyValue)],
                                operands, operands, ab.bankedMap, cond);
  }
  storeOp.erase();
  return static_cast<unsigned>(elementCount -
                               static_cast<int64_t>(candidates.size()));
}

struct MemrefBanking {
  SmallVector<Value, 4> bankedIndices;
  BankChoice choice;
  Value rotIdx;
  SmallVector<Value> rotDigits;
};

/// The value of an integer or index `v` computed from constants only, through
/// side-effect-free single-result ops (their folders): the `affine.apply` of
/// a constant and the arithmetic on it a complete unroll leaves in the body
/// of a pipelined loop whose accesses are memref ops (a runtime-trip scf.for,
/// VITIS_NOTES.md N53, or a non-affine index in an affine loop). Vitis' bank
/// index of such an access is a constant: o72r_bank / o72r_banka, a
/// `res[i & 63][k]` store with k unrolled writes one bank of 16 (Vitis 16;
/// read as a rotating bank every store became a store_enable on every bank,
/// 32). The IR is not changed (folding it would also change the scheduler's
/// input). Depth-limited.
static std::optional<int64_t> evaluateConstantInt(Value valueHandle,
                                                  unsigned depth = 0) {
  if (std::optional<int64_t> candidateValue = getConstantIntValue(valueHandle))
    return candidateValue;
  Operation *def = valueHandle.getDefiningOp();
  if (!def || depth >= 16 || def->getNumResults() != 1 ||
      def->getNumRegions() != 0 || !isMemoryEffectFree(def) ||
      !valueHandle.getType().isIntOrIndex())
    return std::nullopt;
  SmallVector<Attribute, 4> operands;
  for (Value o : def->getOperands()) {
    if (!o.getType().isIntOrIndex())
      return std::nullopt;
    std::optional<int64_t> candidateValue = evaluateConstantInt(o, depth + 1);
    if (!candidateValue)
      return std::nullopt;
    operands.push_back(IntegerAttr::get(o.getType(), *candidateValue));
  }
  SmallVector<OpFoldResult, 1> results;
  if (failed(def->fold(operands, results)) || results.size() != 1)
    return std::nullopt;
  if (auto attr = dyn_cast<Attribute>(results.front()))
    if (auto ia = dyn_cast<IntegerAttr>(attr))
      return ia.getValue().getSExtValue();
  return std::nullopt;
}

/// A memref index that is a constant or computed from constants only
/// (evaluateConstantInt): such an access addresses one bank.
static std::optional<int64_t> constantIndexOf(Value indexValue) {
  if (std::optional<int64_t> candidateValue = getConstantIndexValue(indexValue))
    return candidateValue;
  return evaluateConstantInt(indexValue);
}

static std::pair<Value, int64_t> residueBase(Value valueHandle, int64_t factor,
                                             unsigned depth);

/// The bank of `idx` along a cyclic partition `p` when the index is the
/// induction variable of an scf.for plus a constant, the loop's lower bound
/// and step are constants and the step is a multiple of the factor: every
/// iteration then reaches the same bank, (lb + c) mod factor. This is the
/// form the guarded copies of a run-time-trip partial user unroll take
/// (--auto-pipeline-unroll, VITIS_NOTES N103): copy u of `for (i = 0; i < n;
/// i++) A[i]` unrolled by 2 reads A[2k + u], one bank of a cyclic-2
/// partition (W9r14 review kernel w9r14rv_uv_lb0: Vitis single PIPO, 58).
/// With a run-time lower bound (`for (i = ptr[k]; ...)`, N103's uv_var /
/// nikhil lab3) the bank stays unknown. Key
/// tool.hls.partitioning.induction_residue_banks.
static std::optional<int64_t>
inductionResidueBank(Value indexValue, const DimPartition &portValue) {
  if (!circt::hlsest::Config::get()
           .tool.hls.partitioning.inductionResidueBanks ||
      portValue.kind != PartitionSpec::Cyclic || portValue.factor <= 1)
    return std::nullopt;
  auto [base, candidateValue] = residueBase(indexValue, portValue.factor, 0);
  auto arg = dyn_cast<BlockArgument>(base);
  if (!arg)
    return std::nullopt;
  auto loop = dyn_cast_or_null<scf::ForOp>(arg.getOwner()->getParentOp());
  if (!loop || loop.getInductionVar() != arg)
    return std::nullopt;
  std::optional<int64_t> lb = getConstantIntValue(loop.getLowerBound());
  std::optional<int64_t> step = getConstantIntValue(loop.getStep());
  if (!lb || !step || *step <= 0 || *step % portValue.factor != 0)
    return std::nullopt;
  int64_t bank = (*lb + candidateValue) % portValue.factor;
  return bank < 0 ? bank + portValue.factor : bank;
}

/// The residue of a memref index modulo a power-of-two cyclic factor when
/// its low bits are known, as LLVM's known bits give Vitis: `(n & ~7) + k`
/// with k a constant has residue k mod 8 whatever n is (VITIS_NOTES N115
/// control kernel w9r15p_rc_fix: each read's bank is the constant k % 8,
/// 15 copies per bank). Through casts, add / sub, and with a mask whose low
/// bits are zero (residue 0) or all ones (the operand's residue), a multiply
/// or shift that makes a multiple of the factor. Key
/// tool.hls.partitioning.known_residue_banks.
static std::optional<int64_t> knownResidue(Value valueHandle, int64_t factor,
                                           unsigned depth = 0) {
  if (std::optional<int64_t> candidateValue = constantIndexOf(valueHandle))
    return llvm::mod(*candidateValue, factor);
  Operation *def = valueHandle.getDefiningOp();
  if (!def || depth > 16)
    return std::nullopt;
  unsigned bits = llvm::Log2_64(static_cast<uint64_t>(factor));
  uint64_t low = (uint64_t(1) << bits) - 1;
  if (isa<arith::IndexCastOp, arith::IndexCastUIOp, arith::ExtSIOp,
          arith::ExtUIOp>(def))
    return knownResidue(def->getOperand(0), factor, depth + 1);
  if (auto tr = dyn_cast<arith::TruncIOp>(def)) {
    if (tr.getType().getIntOrFloatBitWidth() < bits)
      return std::nullopt;
    return knownResidue(tr.getIn(), factor, depth + 1);
  }
  if (isa<arith::AddIOp, arith::SubIOp>(def)) {
    std::optional<int64_t> arrayValue =
        knownResidue(def->getOperand(0), factor, depth + 1);
    std::optional<int64_t> buildPoint =
        arrayValue ? knownResidue(def->getOperand(1), factor, depth + 1)
                   : std::nullopt;
    if (!arrayValue || !buildPoint)
      return std::nullopt;
    return llvm::mod(isa<arith::AddIOp>(def) ? *arrayValue + *buildPoint
                                             : *arrayValue - *buildPoint,
                     factor);
  }
  if (auto andOp = dyn_cast<arith::AndIOp>(def)) {
    for (unsigned loopIndex = 0; loopIndex < 2; ++loopIndex) {
      std::optional<int64_t> memoryOp =
          constantIndexOf(def->getOperand(loopIndex));
      if (!memoryOp)
        continue;
      uint64_t mask = static_cast<uint64_t>(*memoryOp) & low;
      if (mask == 0)
        return 0;
      if (mask == low)
        return knownResidue(def->getOperand(1 - loopIndex), factor, depth + 1);
    }
    return std::nullopt;
  }
  if (isa<arith::MulIOp>(def)) {
    for (unsigned loopIndex = 0; loopIndex < 2; ++loopIndex)
      if (std::optional<int64_t> memoryOp =
              constantIndexOf(def->getOperand(loopIndex));
          memoryOp && *memoryOp % factor == 0)
        return 0;
    return std::nullopt;
  }
  if (auto shl = dyn_cast<arith::ShLIOp>(def)) {
    std::optional<int64_t> keyValue = constantIndexOf(shl.getRhs());
    if (keyValue && *keyValue >= static_cast<int64_t>(bits) && *keyValue < 63)
      return 0;
    return std::nullopt;
  }
  return std::nullopt;
}

/// The bank of a non-constant memref index along `p` when it is known
/// anyway: an scf.for counter stepping by a multiple of the factor
/// (inductionResidueBank), or known low bits (knownResidue).
static std::optional<int64_t> knownBank(Value indexValue,
                                        const DimPartition &portValue) {
  if (std::optional<int64_t> bank = inductionResidueBank(indexValue, portValue))
    return bank;
  if (portValue.kind == PartitionSpec::Cyclic && portValue.factor > 1 &&
      llvm::isPowerOf2_64(static_cast<uint64_t>(portValue.factor)) &&
      circt::hlsest::Config::get().tool.hls.partitioning.knownResidueBanks)
    return knownResidue(indexValue, portValue.factor);
  return std::nullopt;
}

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
    std::optional<int64_t> constIdx = constantIndexOf(indexValue);

    if (constIdx) {
      auto [bank, off] = bankAndOffset(*constIdx, portValue);
      if (bank >= 0 && bank < portValue.factor) {
        mb.choice.constBank.push_back(bank);
        mb.bankedIndices[portValue.dim] =
            arith::ConstantIndexOp::create(buildPoint, loc, off);
        continue;
      }
    }

    if (std::optional<int64_t> bank = knownBank(indexValue, portValue)) {
      mb.choice.constBank.push_back(*bank);
      Value dimensionIndex =
          arith::ConstantIndexOp::create(buildPoint, loc, portValue.factor);
      mb.bankedIndices[portValue.dim] =
          arith::DivUIOp::create(buildPoint, loc, indexValue, dimensionIndex)
              .getResult();
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
  mb.rotDigits = rot;
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
  for (int64_t keyValue = 0; keyValue < elementCount; ++keyValue) {
    vals.push_back(memref::LoadOp::create(
        buildPoint, loc, banks[mb.choice.bank(lowerIndex, keyValue)],
        mb.bankedIndices));
  }
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

template <typename ConstOf>
static bool isMultipleOf(Value valueHandle, int64_t factor, ConstOf constOf,
                         unsigned depth = 0) {
  if (factor <= 1)
    return true;
  if (auto candidateValue = constOf(valueHandle))
    return *candidateValue % factor == 0;
  Operation *def = valueHandle.getDefiningOp();
  if (!def || depth > 4)
    return false;
  if (isa<arith::IndexCastOp, arith::IndexCastUIOp, arith::ExtSIOp,
          arith::ExtUIOp>(def))
    return isMultipleOf(def->getOperand(0), factor, constOf, depth + 1);
  if (isa<arith::MulIOp>(def))
    return isMultipleOf(def->getOperand(0), factor, constOf, depth + 1) ||
           isMultipleOf(def->getOperand(1), factor, constOf, depth + 1);
  if (auto shl = dyn_cast<arith::ShLIOp>(def)) {
    std::optional<int64_t> keyValue = constOf(shl.getRhs());
    if (keyValue && *keyValue >= 0 && *keyValue < 62 &&
        ((int64_t(1) << *keyValue) % factor) == 0)
      return true;
    return isMultipleOf(shl.getLhs(), factor, constOf, depth + 1);
  }
  if (isa<arith::AddIOp, arith::SubIOp>(def))
    return isMultipleOf(def->getOperand(0), factor, constOf, depth + 1) &&
           isMultipleOf(def->getOperand(1), factor, constOf, depth + 1);
  return false;
}

static std::pair<Value, int64_t> residueBase(Value valueHandle, int64_t factor,
                                             unsigned depth) {
  bool pow2 = llvm::isPowerOf2_64(static_cast<uint64_t>(factor));
  unsigned bits = llvm::Log2_64(static_cast<uint64_t>(factor));
  auto constOf = [](Value exprValue) -> std::optional<int64_t> {
    if (auto candidateValue = getConstantIndexValue(exprValue))
      return candidateValue;
    if (auto cast = exprValue.getDefiningOp<arith::IndexCastOp>())
      exprValue = cast.getIn();
    if (auto apply = exprValue.getDefiningOp<affine::AffineApplyOp>()) {
      SmallVector<Attribute> attrs;
      for (Value o : apply.getMapOperands()) {
        std::optional<int64_t> candidateValue = getConstantIndexValue(o);
        if (!candidateValue)
          return std::nullopt;
        attrs.push_back(IntegerAttr::get(o.getType(), *candidateValue));
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
    if (isa<arith::RemSIOp, arith::RemUIOp>(def)) {
      std::optional<int64_t> memoryOp = constOf(def->getOperand(1));
      if (!memoryOp || *memoryOp <= 0 || *memoryOp % factor != 0)
        break;
      valueHandle = def->getOperand(0);
      continue;
    }
    if (auto sel = dyn_cast<arith::SelectOp>(def)) {
      if (depth >= 4)
        break;
      auto [bt, ct] = residueBase(sel.getTrueValue(), factor, depth + 1);
      auto [bf, cf] = residueBase(sel.getFalseValue(), factor, depth + 1);
      if (bt != bf || ((ct - cf) % factor) != 0)
        break;
      return {bt, candidateValue + cf};
    }
    if (isa<arith::AddIOp, arith::SubIOp>(def) &&
        !constOf(def->getOperand(0)) && !constOf(def->getOperand(1))) {

      Value lhs = def->getOperand(0), rhs = def->getOperand(1);
      if (isMultipleOf(rhs, factor, constOf)) {
        valueHandle = lhs;
        continue;
      }
      if (isa<arith::AddIOp>(def) && isMultipleOf(lhs, factor, constOf)) {
        valueHandle = rhs;
        continue;
      }
      break;
    }
    if (auto sub = dyn_cast<arith::SubIOp>(def)) {
      std::optional<int64_t> keyValue = constOf(sub.getRhs());
      if (!keyValue)
        break;
      candidateValue -= *keyValue;
      valueHandle = sub.getLhs();
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
  for (Value o : def->getOperands())
    if (!hoistBefore(o, before, dryRun, depth + 1))
      return false;
  if (!dryRun)
    def->moveBefore(before);
  return true;
}

/// Whether steered groups follow N74: a group may span several partitioned
/// dimensions, and copies that share a residue class are split into further
/// groups (off: one partitioned dimension, pairwise distinct residues only).
static bool steerWindowGroups() {
  return circt::hlsest::Config::get().tool.hls.partitioning.steerWindowGroups;
}

/// One copy of a steered group: the load and, per rotating partitioned
/// dimension of the group (in layout order), the constant its index adds to
/// the group's runtime base.
struct SteerMember {
  mutable memref::LoadOp load;
  SmallVector<int64_t> offsets;
};

/// The bank of a constant index along `p`, nullopt when the index is not a
/// constant or names no bank (resolveMemref's rule).
static std::optional<int64_t> constantBankOf(Value indexValue,
                                             const DimPartition &portValue) {
  std::optional<int64_t> candidateValue = constantIndexOf(indexValue);
  if (!candidateValue)
    return knownBank(indexValue, portValue);
  int64_t bank = bankAndOffset(*candidateValue, portValue).first;
  if (bank < 0 || bank >= portValue.factor)
    return std::nullopt;
  return bank;
}

/// One group of loads whose indices on every rotating partitioned dimension
/// are one runtime base plus constants, no two copies with the same residues:
/// rewritten as one load per candidate bank, at the offset of the copy that
/// addresses it.
/// Returns whether the group was steered (debug provenance only).
static bool steerGroup(SmallVector<SteerMember> members, ArrayRef<Value> banks,
                       const BankLayout &lowerIndex) {
  llvm::sort(members,
             [](const SteerMember &arrayValue, const SteerMember &buildPoint) {
               return arrayValue.load->isBeforeInBlock(buildPoint.load);
             });

  SmallVector<std::optional<int64_t>> constBanks;
  for (const DimPartition &portValue : lowerIndex.dims)
    constBanks.push_back(constantBankOf(
        members.front().load.getIndices()[portValue.dim], portValue));
  unsigned numRotating = llvm::count(constBanks, std::nullopt);
  for (const SteerMember &memoryOp : members) {
    if (memoryOp.offsets.size() != numRotating)
      return false;
    for (auto [innerIndex, portValue] : llvm::enumerate(lowerIndex.dims))
      if (constantBankOf(memoryOp.load.getIndices()[portValue.dim],
                         portValue) != constBanks[innerIndex])
        return false;
  }
  Operation *first = members.front().load;
  bool movable = llvm::all_of(members, [&](const SteerMember &memoryOp) {
    return llvm::all_of(memoryOp.load.getIndices(), [&](Value loopIndex) {
      return hoistBefore(loopIndex, first, true);
    });
  });
  if (!movable)
    return false;
  for (const SteerMember &memoryOp : members)
    for (Value loopIndex : memoryOp.load.getIndices())
      hoistBefore(loopIndex, first, false);
  OpBuilder buildPoint(first);
  Location loc = first->getLoc();

  SmallVector<MemrefBanking> mbs;
  for (const SteerMember &memoryOp : members)
    mbs.push_back(
        resolveMemref(buildPoint, loc, memoryOp.load.getIndices(), lowerIndex));
  const BankChoice &choice = mbs.front().choice;

  for (unsigned resultValue : choice.rotating) {
    unsigned pdim = lowerIndex.dims[resultValue].dim;
    if (lowerIndex.bankType && lowerIndex.bankType.getShape()[pdim] == 1) {
      Value zero = arith::ConstantIndexOp::create(buildPoint, loc, 0);
      for (MemrefBanking &mb : mbs)
        mb.bankedIndices[pdim] = zero;
    }
  }

  SmallVector<SmallVector<Value>> eq0;
  for (auto [loopIndex, resultValue] : llvm::enumerate(choice.rotating)) {
    SmallVector<Value> row;
    for (int64_t valueHandle = 0;
         valueHandle < lowerIndex.dims[resultValue].factor; ++valueHandle)
      row.push_back(arith::CmpIOp::create(
          buildPoint, loc, arith::CmpIPredicate::eq,
          mbs.front().rotDigits[loopIndex],
          arith::ConstantIndexOp::create(buildPoint, loc, valueHandle)));
    eq0.push_back(std::move(row));
  }

  int64_t elementCount = choice.numCandidates(lowerIndex);
  llvm::DenseMap<int64_t, Value> conjunctions;
  auto copy0In = [&](ArrayRef<int64_t> digits) -> Value {
    if (digits.size() == 1)
      return eq0[0][digits[0]];
    int64_t key = 0;
    for (auto [loopIndex, dimensionIndex] : llvm::enumerate(digits))
      key = key * lowerIndex.dims[choice.rotating[loopIndex]].factor +
            dimensionIndex;
    Value &valueHandle = conjunctions[key];
    if (!valueHandle) {
      valueHandle = eq0[0][digits[0]];
      for (size_t loopIndex = 1; loopIndex < digits.size(); ++loopIndex)
        valueHandle = arith::AndIOp::create(buildPoint, loc, valueHandle,
                                            eq0[loopIndex][digits[loopIndex]]);
    }
    return valueHandle;
  };
  SmallVector<SmallVector<Value>> hit(members.size());
  for (size_t innerIndex = 0; innerIndex < members.size(); ++innerIndex)
    for (int64_t keyValue = 0; keyValue < elementCount; ++keyValue) {
      SmallVector<int64_t> dig = choice.digits(lowerIndex, keyValue);
      for (auto [loopIndex, resultValue] : llvm::enumerate(choice.rotating)) {
        int64_t fieldValue = lowerIndex.dims[resultValue].factor;
        dig[loopIndex] =
            ((dig[loopIndex] - members[innerIndex].offsets[loopIndex] +
              members.front().offsets[loopIndex]) %
                 fieldValue +
             fieldValue) %
            fieldValue;
      }
      hit[innerIndex].push_back(copy0In(dig));
    }
  SmallVector<Value> bankVals;
  for (int64_t keyValue = 0; keyValue < elementCount; ++keyValue) {
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
    bankVals.push_back(memref::LoadOp::create(
        buildPoint, loc, banks[choice.bank(lowerIndex, keyValue)], indexValue));
    if (!choice.rotating.empty())
      markRotatingRead(bankVals.back().getDefiningOp());
  }
  SmallVector<Value> results;
  for (size_t innerIndex = 0; innerIndex < members.size(); ++innerIndex) {
    Value resultValue = bankVals[elementCount - 1];
    for (int64_t keyValue = elementCount - 1; keyValue-- > 0;)
      resultValue =
          arith::SelectOp::create(buildPoint, loc, hit[innerIndex][keyValue],
                                  bankVals[keyValue], resultValue);
    results.push_back(resultValue);
  }
  for (auto [memoryOp, resultValue] : llvm::zip(members, results)) {
    memoryOp.load.replaceAllUsesWith(resultValue);
    memoryOp.load.erase();
  }
  return true;
}

/// The copies of one group split into groups whose residue tuples are
/// pairwise distinct (each reads every bank at most once), first fit in
/// program order. Copies that share a residue class meet in one bank in some
/// iteration, so the bank is read once per class member: Vitis' per-bank read
/// count is the largest class (VITIS_NOTES N74, kernels w9r9p_o92_f2_w3x3,
/// f3_w9x1, f3_w6x1). Without N74 the group stays whole and only distinct
/// residues on one dimension are steered (N27).
template <typename T>
static std::vector<SmallVector<T>>
residueClassGroups(ArrayRef<T> members,
                   function_ref<ArrayRef<int64_t>(const T &)> offsetsOf,
                   ArrayRef<int64_t> factors) {
  auto residues = [&](const T &memoryOp) {
    SmallVector<int64_t> resultValue;
    for (auto [candidateValue, fieldValue] :
         llvm::zip(offsetsOf(memoryOp), factors))
      resultValue.push_back(((candidateValue % fieldValue) + fieldValue) %
                            fieldValue);
    return resultValue;
  };
  std::vector<SmallVector<T>> groups;
  std::vector<std::set<SmallVector<int64_t>>> seen;
  if (!steerWindowGroups()) {
    std::set<SmallVector<int64_t>> all;
    for (const T &memoryOp : members)
      if (!all.insert(residues(memoryOp)).second)
        return {};
    groups.emplace_back(members.begin(), members.end());
    return groups;
  }
  for (const T &memoryOp : members) {
    SmallVector<int64_t> resultValue = residues(memoryOp);
    size_t globalOp = 0;
    while (globalOp < groups.size() && seen[globalOp].count(resultValue))
      ++globalOp;
    if (globalOp == groups.size()) {
      groups.emplace_back();
      seen.emplace_back();
    }
    groups[globalOp].push_back(memoryOp);
    seen[globalOp].insert(resultValue);
  }
  return groups;
}

/// `e` as `base + c` with a constant c (0 when there is none).
static std::pair<AffineExpr, int64_t> splitConstant(AffineExpr entryValue) {
  if (auto add = dyn_cast<AffineBinaryOpExpr>(entryValue);
      add && add.getKind() == AffineExprKind::Add) {
    if (auto candidateValue = dyn_cast<AffineConstantExpr>(add.getRHS()))
      return {add.getLHS(), candidateValue.getValue()};
    if (auto candidateValue = dyn_cast<AffineConstantExpr>(add.getLHS()))
      return {add.getRHS(), candidateValue.getValue()};
  }
  return {entryValue, 0};
}

/// An affine.load of `site` in a nested region (an scf.if arm) that repeats
/// the address of a load in an enclosing block, with no other use of `site`
/// than loads inside that block's parent op, is replaced by the outer load.
/// The load GVN of --convert-affine-to-loopschedule merges such a reload
/// anyway (`m = a[i]; if (m < b) m = a[i];`, Explainable-ML's pooling), but
/// only while both are the same affine.load: once the outer one is steered
/// (N74) the reload would read every bank again.
/// Returns how many reloads were forwarded.
static unsigned forwardNestedReloads(Value site) {
  SmallVector<affine::AffineLoadOp> loads;
  for (Operation *user : site.getUsers())
    if (auto ld = dyn_cast<affine::AffineLoadOp>(user);
        ld && ld.getMemRef() == site)
      loads.push_back(ld);
  if (loads.size() < 2)
    return 0;

  SmallVector<Value> handles{site};

  bool isGlobal = isa<BlockArgument>(site);
  if (auto globalUse = site.getDefiningOp<memref::GetGlobalOp>()) {
    isGlobal = true;
    if (auto fn = globalUse->getParentOfType<FunctionOpInterface>())
      fn->walk([&](memref::GetGlobalOp other) {
        if (other != globalUse &&
            other.getNameAttr() == globalUse.getNameAttr())
          handles.push_back(other.getResult());
      });
  }
  auto onlyLoadsIn = [&](Operation *scope) {
    if (isGlobal &&
        scope->walk([](CallOpInterface) { return WalkResult::interrupt(); })
            .wasInterrupted())
      return false;
    return llvm::all_of(handles, [&](Value h) {
      return llvm::all_of(h.getUsers(), [&](Operation *user) {
        return isa<affine::AffineLoadOp, memref::LoadOp>(user) ||
               !scope->isAncestor(user);
      });
    });
  };
  llvm::SmallPtrSet<Operation *, 8> erased;
  for (affine::AffineLoadOp inner : loads) {
    for (affine::AffineLoadOp outer : loads) {
      if (outer == inner || erased.count(outer) ||
          outer->getBlock() == inner->getBlock())
        continue;
      Operation *anc = outer->getBlock()->findAncestorOpInBlock(*inner);
      if (!anc || !outer->isBeforeInBlock(anc) ||
          outer.getAffineMap() != inner.getAffineMap() ||
          outer.getMapOperands() != inner.getMapOperands() ||
          !onlyLoadsIn(outer->getParentOp()))
        continue;
      inner.getResult().replaceAllUsesWith(outer.getResult());
      erased.insert(inner);
      break;
    }
  }
  for (Operation *op : erased)
    op->erase();
  return erased.size();
}

/// What steerLoadGroups did to one array (debug provenance, `hls.steering`
/// on its banks; W9r9 review D8).
struct SteerStats {
  SmallVector<int64_t> groupSizes;
  unsigned forwardedReloads = 0;
  unsigned prunedStoreEnables = 0;
};

static void steerLoadGroups(Value site, ArrayRef<Value> banks,
                            const BankLayout &lowerIndex, bool affineLoads,
                            SteerStats &stats) {
  if (lowerIndex.numBanks < 2 ||
      static_cast<int64_t>(banks.size()) != lowerIndex.numBanks ||
      llvm::any_of(lowerIndex.dims, [](const DimPartition &portValue) {
        return portValue.kind == PartitionSpec::Block;
      }))
    return;
  if (lowerIndex.dims.size() != 1 && !steerWindowGroups())
    return;
  if (affineLoads && steerWindowGroups())
    stats.forwardedReloads += forwardNestedReloads(site);

  auto rotatingFactors = [&](ArrayRef<std::optional<int64_t>> constBanks) {
    SmallVector<int64_t> fieldValue;
    for (auto [innerIndex, portValue] : llvm::enumerate(lowerIndex.dims))
      if (!constBanks[innerIndex])
        fieldValue.push_back(portValue.factor);
    return fieldValue;
  };

  if (affineLoads) {
    struct AffineCopy {
      affine::AffineLoadOp load;
      SmallVector<int64_t> offsets;
    };
    struct AffineGroup {
      Block *block;

      SmallVector<std::optional<int64_t>> constBanks;
      SmallVector<AffineMap> bases;
      SmallVector<SmallVector<Value>> operands;
      SmallVector<AffineCopy> members;
    };
    std::vector<AffineGroup> agroups;
    for (Operation *user : site.getUsers()) {
      auto ld = dyn_cast<affine::AffineLoadOp>(user);
      if (!ld || ld.getMemRef() != site)
        continue;
      AffineBanking ab;
      {

        SmallVector<Value, 4> operands(ld.getMapOperands());
        AffineMap accessMap = canonicalAccess(ld.getAffineMap(), operands);
        ab = resolveAffine(accessMap, operands, lowerIndex);
        if (ab.choice.rotating.empty())
          continue;
      }
      AffineGroup key{ld->getBlock(), {}, {}, {}, {}};
      SmallVector<int64_t> offsets;
      bool ok = true;
      for (auto [innerIndex, portValue] : llvm::enumerate(lowerIndex.dims)) {

        AffineMap map = ld.getAffineMap().getSubMap({portValue.dim});
        SmallVector<Value> ops(ld.getMapOperands());
        affine::fullyComposeAffineMapAndOperands(&map, &ops);
        affine::canonicalizeMapAndOperands(&map, &ops);
        AffineExpr entryValue = map.getResult(0);
        if (auto ce = dyn_cast<AffineConstantExpr>(entryValue)) {
          int64_t bank = bankAndOffset(ce.getValue(), portValue).first;
          if (lowerIndex.dims.size() == 1 || bank < 0 ||
              bank >= portValue.factor || !ab.choice.constBank[innerIndex]) {
            ok = false;
            break;
          }
          key.constBanks.push_back(bank);
          key.bases.push_back(AffineMap());
          key.operands.emplace_back();
          continue;
        }
        if (ab.choice.constBank[innerIndex]) {
          ok = false;
          break;
        }
        auto [baseExpr, candidateValue] = splitConstant(entryValue);
        key.constBanks.push_back(std::nullopt);
        key.bases.push_back(AffineMap::get(
            map.getNumDims(), map.getNumSymbols(), baseExpr, map.getContext()));
        key.operands.push_back(ops);
        offsets.push_back(candidateValue);
      }
      if (!ok)
        continue;
      auto it = llvm::find_if(agroups, [&](const AffineGroup &globalOp) {
        return globalOp.block == key.block &&
               globalOp.constBanks == key.constBanks &&
               globalOp.bases == key.bases && globalOp.operands == key.operands;
      });
      if (it == agroups.end()) {
        agroups.push_back(std::move(key));
        it = std::prev(agroups.end());
      }
      it->members.push_back({ld, std::move(offsets)});
    }
    for (AffineGroup &globalOp : agroups) {
      if (globalOp.members.size() < 2)
        continue;
      std::vector<SmallVector<AffineCopy>> classes =
          residueClassGroups<AffineCopy>(
              globalOp.members,
              [](const AffineCopy &candidateValue) -> ArrayRef<int64_t> {
                return candidateValue.offsets;
              },
              rotatingFactors(globalOp.constBanks));
      SmallVector<AffineCopy *> steered;
      for (SmallVector<AffineCopy> &cls : classes)
        if (cls.size() >= 2)
          for (AffineCopy &candidateValue : globalOp.members)
            if (llvm::any_of(cls, [&](const AffineCopy &exprValue) {
                  return exprValue.load == candidateValue.load;
                }))
              steered.push_back(&candidateValue);
      if (steered.empty())
        continue;

      SmallVector<std::tuple<AffineMap, SmallVector<Value>, Value>> applied;
      Operation *firstLoad = steered.front()->load;
      for (AffineCopy *candidateValue : steered)
        if (candidateValue->load->isBeforeInBlock(firstLoad))
          firstLoad = candidateValue->load;
      llvm::DenseMap<Operation *, memref::LoadOp> converted;
      for (AffineCopy *copy : steered) {
        affine::AffineLoadOp ld = copy->load;
        OpBuilder buildPoint(ld);
        SmallVector<Value> indexValue;
        AffineMap map = ld.getAffineMap();
        for (unsigned resultValue = 0; resultValue < map.getNumResults();
             ++resultValue) {
          AffineMap sub = map.getSubMap({resultValue});
          SmallVector<Value> ops(ld.getMapOperands());
          affine::fullyComposeAffineMapAndOperands(&sub, &ops);
          affine::canonicalizeMapAndOperands(&sub, &ops);
          auto it = llvm::find_if(applied, [&](auto &arrayValue) {
            return std::get<0>(arrayValue) == sub &&
                   std::get<1>(arrayValue) == ops;
          });
          if (it != applied.end()) {
            indexValue.push_back(std::get<2>(*it));
            continue;
          }

          bool early = llvm::all_of(ops, [&](Value valueHandle) {
            Operation *dimensionIndex = valueHandle.getDefiningOp();
            return !dimensionIndex ||
                   dimensionIndex->getBlock() != firstLoad->getBlock() ||
                   dimensionIndex->isBeforeInBlock(firstLoad);
          });
          OpBuilder ab(early ? firstLoad : ld.getOperation());
          Value valueHandle =
              affine::AffineApplyOp::create(ab, ld.getLoc(), sub, ops);
          applied.push_back({sub, ops, valueHandle});
          indexValue.push_back(valueHandle);
        }
        auto ml =
            memref::LoadOp::create(buildPoint, ld.getLoc(), site, indexValue);
        for (NamedAttribute arrayValue : ld->getDiscardableAttrs())
          if (arrayValue.getName() != "map")
            ml->setDiscardableAttr(arrayValue.getName(), arrayValue.getValue());
        ld.getResult().replaceAllUsesWith(ml.getResult());
        converted[ld.getOperation()] = ml;
        ld.erase();
      }
      for (SmallVector<AffineCopy> &cls : classes) {
        if (cls.size() < 2)
          continue;
        SmallVector<SteerMember> members;
        for (AffineCopy &candidateValue : cls)
          members.push_back(
              {converted.lookup(candidateValue.load.getOperation()),
               candidateValue.offsets});
        int64_t size = members.size();
        if (steerGroup(std::move(members), banks, lowerIndex))
          stats.groupSizes.push_back(size);
      }
    }
  }

  using GroupKey = std::pair<Block *, SmallVector<std::pair<int64_t, void *>>>;
  std::map<GroupKey, size_t> groupIndex;
  std::vector<SmallVector<SteerMember>> groups;
  SmallVector<SmallVector<std::optional<int64_t>>> groupConstBanks;
  for (Operation *user : site.getUsers()) {
    auto ld = dyn_cast<memref::LoadOp>(user);
    if (!ld || ld.getMemRef() != site)
      continue;
    GroupKey key{ld->getBlock(), {}};
    SmallVector<std::optional<int64_t>> constBanks;
    SteerMember memoryOp{ld, {}};
    for (const DimPartition &portValue : lowerIndex.dims) {
      Value indexValue = ld.getIndices()[portValue.dim];
      if (lowerIndex.dims.size() == 1
              ? constantIndexOf(indexValue).has_value() ||
                    inductionResidueBank(indexValue, portValue).has_value()
              : constantBankOf(indexValue, portValue).has_value()) {
        std::optional<int64_t> bank = constantBankOf(indexValue, portValue);
        key.second.push_back({bank ? *bank : -1, nullptr});
        constBanks.push_back(bank ? bank : std::optional<int64_t>(-1));
        continue;
      }
      auto [base, candidateValue] =
          residueBase(indexValue, portValue.factor, 0);
      key.second.push_back({0, base.getAsOpaquePointer()});
      constBanks.push_back(std::nullopt);
      memoryOp.offsets.push_back(candidateValue);
    }
    if (memoryOp.offsets.empty())
      continue;
    auto [it, inserted] = groupIndex.try_emplace(key, groups.size());
    if (inserted) {
      groups.emplace_back();
      groupConstBanks.push_back(constBanks);
    }
    groups[it->second].push_back(std::move(memoryOp));
  }
  for (auto [members, constBanks] : llvm::zip(groups, groupConstBanks)) {
    if (members.size() < 2)
      continue;

    for (SmallVector<SteerMember> &cls : residueClassGroups<SteerMember>(
             members,
             [](const SteerMember &memoryOp) -> ArrayRef<int64_t> {
               return memoryOp.offsets;
             },
             rotatingFactors(constBanks)))
      if (cls.size() >= 2) {
        int64_t size = cls.size();
        if (steerGroup(std::move(cls), banks, lowerIndex))
          stats.groupSizes.push_back(size);
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

      if (compoundAssignTwoStores(storeOp)) {
        auto extra = StoreEnableOp::create(
            buildPoint, loc, operandValue, en,
            banks[mb.choice.bank(lowerIndex, keyValue)], mb.bankedIndices);
        extra->setAttr("hls.compound_assign_store", buildPoint.getUnitAttr());
      }
      StoreEnableOp::create(buildPoint, loc, operandValue, en,
                            banks[mb.choice.bank(lowerIndex, keyValue)],
                            mb.bankedIndices);
    }
  }
  storeOp.erase();
}

/// `hls.steering` on the memory of each bank: the sizes of the load groups
/// steered across the banks and the forwarded if-arm reloads (N27 / N74),
/// accumulated over the sites of a global. Read by the debug report only.
static void recordSteering(ArrayRef<Value> banks, const SteerStats &stats) {
  if (stats.groupSizes.empty() && stats.forwardedReloads == 0 &&
      stats.prunedStoreEnables == 0)
    return;
  for (Value bank : banks) {
    Operation *mem = bank.getDefiningOp();
    if (auto globalUse = dyn_cast_or_null<memref::GetGlobalOp>(mem))
      mem = SymbolTable::lookupNearestSymbolFrom(globalUse,
                                                 globalUse.getNameAttr());
    if (!mem)
      continue;
    Builder buildPoint(mem->getContext());
    SmallVector<int64_t> sizes;
    int64_t forwarded = 0, pruned = 0;
    if (auto old = mem->getAttrOfType<DictionaryAttr>("hls.steering")) {
      if (auto globalOp = old.getAs<DenseI64ArrayAttr>("groups"))
        sizes.append(globalOp.asArrayRef().begin(),
                     globalOp.asArrayRef().end());
      if (auto fieldValue = old.getAs<IntegerAttr>("forwarded_reloads"))
        forwarded = fieldValue.getInt();
      if (auto portValue = old.getAs<IntegerAttr>("pruned_store_enables"))
        pruned = portValue.getInt();
    }
    sizes.append(stats.groupSizes.begin(), stats.groupSizes.end());
    forwarded += stats.forwardedReloads;
    pruned += stats.prunedStoreEnables;
    SmallVector<NamedAttribute> fields{
        buildPoint.getNamedAttr("groups",
                                buildPoint.getDenseI64ArrayAttr(sizes)),
        buildPoint.getNamedAttr("forwarded_reloads",
                                buildPoint.getI64IntegerAttr(forwarded))};

    if (pruned)
      fields.push_back(buildPoint.getNamedAttr(
          "pruned_store_enables", buildPoint.getI64IntegerAttr(pruned)));
    mem->setAttr("hls.steering", buildPoint.getDictionaryAttr(fields));
  }
}

class BankingPlan {
public:
  BankingPlan(ModuleOp module, bool steerAffineLoads)
      : module(module), symbols(module), steerAffineLoads(steerAffineLoads) {}

  void run() {
    partitions.emplace(module, true);
    assignCalleeForms();
    bank();
    if (clonesMade)
      refreshFormPortBound();
  }

private:
  ModuleOp module;
  SymbolTable symbols;
  bool steerAffineLoads = true;

  std::optional<PartitionRoots> partitions;

  DenseMap<Operation *, Operation *> originOf;

  DenseMap<Operation *, SmallVector<std::pair<std::string, func::FuncOp>>>
      formsOf;

  llvm::MapVector<Operation *, SmallVector<std::optional<BankLayout>>>
      paramLayouts;
  unsigned clonesMade = 0;

  llvm::StringSet<> multiFormCallees;

  DenseMap<Value, SmallVector<Value>> banksOf;

  std::optional<BankLayout> layoutOfValue(Value valueHandle, func::FuncOp fn);
  void assignCalleeForms();
  void bank();
  void refreshFormPortBound();

  DictionaryAttr partitionAttr(OpBuilder &buildPoint,
                               const BankLayout &lowerIndex);
  DictionaryAttr bankAttrs(OpBuilder &buildPoint, const BankLayout &lowerIndex,
                           unsigned bankIdx, Operation *from, StringRef bankOf);
  SmallVector<Value> createAllocaBanks(memref::AllocaOp alloca,
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
          multiFormCallees.insert(orig.getName());
          multiFormCallees.insert(inst.getName());
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

void BankingPlan::refreshFormPortBound() {
  InstanceModel model = computeInstances(module);
  OpBuilder buildPoint(module.getContext());
  for (const auto &entry : multiFormCallees) {
    auto fn = symbols.lookup<func::FuncOp>(entry.getKey());
    if (!fn || fn.isExternal())
      continue;
    SmallVector<int64_t> bound;
    for (BlockArgument arg : fn.getArguments())
      if (isa<BaseMemRefType>(arg.getType()) &&
          model.argReachesSharedModule(fn, arg.getArgNumber()))
        bound.push_back(arg.getArgNumber());
    if (bound.empty())
      fn->removeAttr(kPortBoundArgsAttr);
    else
      fn->setAttr(kPortBoundArgsAttr, buildPoint.getI64ArrayAttr(bound));
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
  if (auto o = dyn_cast<OpaqueLoc>(loc))
    return findFileLineColLoc(o.getFallbackLocation());
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
BankingPlan::createAllocaBanks(memref::AllocaOp alloca,
                               const BankLayout &lowerIndex) {
  OpBuilder buildPoint(alloca->getContext());
  buildPoint.setInsertionPointAfter(alloca);
  Attribute varName = alloca->getAttr("polygeist.varname");
  std::string bankOf = varName ? cast<StringAttr>(varName).getValue().str()
                               : unnamedBankOf(alloca.getResult());
  SmallVector<Value> banks;
  for (int64_t loopIndex = 0; loopIndex < lowerIndex.numBanks; ++loopIndex) {
    auto bank = memref::AllocaOp::create(buildPoint, alloca.getLoc(),
                                         lowerIndex.bankType);
    bank->setAttrs(bankAttrs(buildPoint, lowerIndex,
                             static_cast<unsigned>(loopIndex), alloca, bankOf));
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
  SteerStats stats;
  steerLoadGroups(site, banks, lowerIndex, steerAffineLoads, stats);
  recordSteering(banks, stats);
  SmallVector<Operation *> users(site.getUsers().begin(),
                                 site.getUsers().end());
  unsigned pruned = 0;
  for (Operation *user : users) {
    if (auto ld = dyn_cast<affine::AffineLoadOp>(user))
      rewriteAffineLoad(ld, banks, lowerIndex);
    else if (auto st = dyn_cast<affine::AffineStoreOp>(user))
      pruned += rewriteAffineStore(st, banks, lowerIndex);
    else if (auto ld = dyn_cast<memref::LoadOp>(user))
      rewriteMemrefLoad(ld, banks, lowerIndex);
    else if (auto st = dyn_cast<memref::StoreOp>(user))
      rewriteMemrefStore(st, banks, lowerIndex);
  }
  if (pruned) {
    SteerStats prunedStats;
    prunedStats.prunedStoreEnables = pruned;
    recordSteering(banks, prunedStats);
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
  MemoryBankingPass() = default;
  MemoryBankingPass(const MemoryBankingPass &other)
      : hls_analysis::impl::MemoryBankingBase<MemoryBankingPass>(other) {}

  Option<bool> annotateCalleeStores{
      *this, "callee-stores-per-loop",
      llvm::cl::desc("After banking, record on each bank (alloca or memref "
                     "parameter) the most stores one loop body of a callee "
                     "it is passed to makes (hls.callee_stores_per_loop), so "
                     "that the per-function scheduler does not give a bank "
                     "Vitis keeps a 2-port RAM the replicated read slots."),
      llvm::cl::init(true)};

  Option<bool> steerAffineLoads{
      *this, "steer-affine-loads",
      llvm::cl::desc("Unrolled affine.load copies of a cyclic / complete "
                     "partitioned array whose partitioned index is one "
                     "runtime expression plus constants distinct modulo the "
                     "factor read each bank once per iteration (as the "
                     "memref.load copies already did), instead of every "
                     "candidate bank per copy."),
      llvm::cl::init(true)};

  void runOnOperation() override {

    const circt::hlsest::HlsToolConfig &hc =
        circt::hlsest::Config::get().tool.hls;
    circt::hlsest::applyConfigured(steerAffineLoads,
                                   hc.partitioning.steerAffineLoads);
    circt::hlsest::applyConfigured(
        annotateCalleeStores,
        hc.memoryArchitecture.replication.calleeStoresPerLoop);
    BankingPlan(getOperation(), steerAffineLoads).run();

    if (hc.memoryArchitecture.iterationPrivateRegisters)
      hls_analysis::markIterationPrivateBanks(getOperation());

    if (annotateCalleeStores)
      hls_analysis::annotateCalleeStoresPerLoop(getOperation());

    if (hc.memoryArchitecture.replication.callerStoresPerLoop)
      hls_analysis::annotateCallerStoresPerLoop(getOperation());

    if (const circt::hlsest::ImplicitBufferConfig *mc =
            hc.implicitBuffer("axi4-mm"))
      if (mc->busRequestsThroughCalls)
        hls_analysis::annotateMaxiBundlesThroughCalls(getOperation(), mc->mode,
                                                      mc->defaultBundle);
    if (circt::hlsest::Config::get().scheduling.calleeGlobalRecurrence)
      hls_analysis::annotateCalleeGlobalRecurrences(getOperation());
  }
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
