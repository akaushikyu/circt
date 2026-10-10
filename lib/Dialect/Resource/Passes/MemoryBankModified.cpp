

// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#include "circt/Dialect/Resource/Config/ConfigUtils.h"
#include "circt/Dialect/Resource/HLS/HLSOps.h"
#include "circt/Dialect/Resource/Interfaces/MemoryDS.h"
#include "circt/Dialect/Resource/Passes/CallInstances.h"
#include "circt/Dialect/Resource/Passes/ConstantIndex.h"
#include "circt/Dialect/Resource/Passes/IterationPrivateBanks.h"
#include "circt/Dialect/Resource/Passes/MemrefBankClassification.h"
#include "circt/Dialect/Resource/Passes/PartitionLayout.h"
#include "circt/Dialect/Resource/Passes/PreBankForwarding.h"
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
#include "llvm/ADT/BitVector.h"
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

  SmallVector<std::pair<int64_t, int64_t>, 2> reach;

  int64_t firstBank(const BankLayout &lowerIndex, unsigned loopIndex) const {
    return reach.empty() ? 0 : reach[loopIndex].first;
  }
  int64_t bankCount(const BankLayout &lowerIndex, unsigned loopIndex) const {
    return reach.empty() ? lowerIndex.dims[rotating[loopIndex]].factor
                         : reach[loopIndex].second;
  }
  int64_t numCandidates(const BankLayout &lowerIndex) const {
    int64_t elementCount = 1;
    for (unsigned loopIndex = 0; loopIndex < rotating.size(); ++loopIndex)
      elementCount *= bankCount(lowerIndex, loopIndex);
    return elementCount;
  }

  SmallVector<int64_t> digits(const BankLayout &lowerIndex,
                              int64_t keyValue) const {
    SmallVector<int64_t> out(rotating.size());
    for (int64_t loopIndex = static_cast<int64_t>(rotating.size()) - 1;
         loopIndex >= 0; --loopIndex) {
      int64_t fieldValue = bankCount(lowerIndex, loopIndex);
      out[loopIndex] = firstBank(lowerIndex, loopIndex) + keyValue % fieldValue;
      keyValue /= fieldValue;
    }
    return out;
  }

  int64_t rotValue(const BankLayout &lowerIndex, int64_t keyValue) const {
    SmallVector<int64_t> dig = digits(lowerIndex, keyValue);
    int64_t valueHandle = 0;
    for (unsigned loopIndex = 0; loopIndex < rotating.size(); ++loopIndex)
      valueHandle = valueHandle * lowerIndex.dims[rotating[loopIndex]].factor +
                    dig[loopIndex];
    return valueHandle;
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

static std::optional<std::pair<int64_t, int64_t>>
banksFromRange(Value indexValue, const DimPartition &portValue);
static std::optional<std::pair<int64_t, int64_t>>
affineBanksFromRange(AffineExpr entryValue, ArrayRef<Value> operands,
                     unsigned nDims, const DimPartition &portValue);

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

    std::optional<std::pair<int64_t, int64_t>> reach;
    if (!candidateValue) {
      reach = affineBanksFromRange(accessMap.getResult(portValue.dim), operands,
                                   nDims, portValue);
      if (reach && reach->second == 1)
        candidateValue = reach->first;
    }
    ab.choice.constBank.push_back(candidateValue);
    if (!candidateValue) {
      ab.choice.rotating.push_back(innerIndex);
      ab.rotExprs.push_back(simp);
      ab.choice.reach.push_back(
          reach ? *reach : std::make_pair(int64_t(0), portValue.factor));
    }
  }

  if (llvm::all_of(llvm::zip(ab.choice.rotating, ab.choice.reach),
                   [&](auto rr) {
                     auto [resultValue, range] = rr;
                     return range.first == 0 &&
                            range.second == lowerIndex.dims[resultValue].factor;
                   }))
    ab.choice.reach.clear();
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

  bool lowBitsKnown = true;
  for (AffineExpr entryValue : idxExprs)
    entryValue.walk([&](AffineExpr exprValue) {
      auto bin = dyn_cast<AffineBinaryOpExpr>(exprValue);
      if (!bin)
        return;
      if (exprValue.getKind() == AffineExprKind::FloorDiv ||
          exprValue.getKind() == AffineExprKind::CeilDiv)
        lowBitsKnown = false;
      if (exprValue.getKind() == AffineExprKind::Mod) {
        auto candidateValue = dyn_cast<AffineConstantExpr>(bin.getRHS());
        if (!candidateValue || candidateValue.getValue() <= 0 ||
            !llvm::isPowerOf2_64(candidateValue.getValue()))
          lowBitsKnown = false;
      }
    });
  if (!lowBitsKnown)
    return std::nullopt;

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
/// `hls.bank_address_varies` when the in-bank address depends on which copy
/// addresses the bank (VITIS_NOTES N125): only then are the reads predicated
/// per bank in Vitis and get the extra copy.
/// `hls.runtime_bank` on the per-bank loads of a read whose bank is chosen at
/// run time (a lone read's one load per candidate bank and a mux, or a
/// steered group's loads): Vitis keeps such a load predicated on its bank
/// select, so loads in
/// exclusive if / else-if arms share a port slot (VITIS_NOTES N124,
/// --bram-analysis).
/// Only cyclic partitions carry the mark: under a block partition Vitis
/// speculates the arm loads and counts every read (W9r16 review kernel
/// w9r16rv_ie_blk, ie_part with `block factor=2`: Vitis 40, 5 copies).
static void markRuntimeBankRead(Operation *load, const BankChoice &choice,
                                const BankLayout &lowerIndex) {
  bool allCyclic = llvm::all_of(choice.rotating, [&](unsigned resultValue) {
    return lowerIndex.dims[resultValue].kind == PartitionSpec::Cyclic &&
           lowerIndex.dims[resultValue].factor > 1;
  });
  if (!choice.rotating.empty() && allCyclic)
    load->setAttr("hls.runtime_bank", UnitAttr::get(load->getContext()));
}

static void markRotatingRead(Operation *load, bool addressVaries) {
  load->setAttr("hls.rotating_bank", UnitAttr::get(load->getContext()));
  if (addressVaries)
    load->setAttr("hls.bank_address_varies", UnitAttr::get(load->getContext()));
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
  for (int64_t keyValue = 0; keyValue < elementCount; ++keyValue) {
    vals.push_back(affine::AffineLoadOp::create(
        buildPoint, loc, banks[ab.choice.bank(lowerIndex, keyValue)],
        ab.bankedMap, operands));
    markRuntimeBankRead(vals.back().getDefiningOp(), ab.choice, lowerIndex);
  }
  Value result = vals[elementCount - 1];
  for (int64_t keyValue = elementCount - 1; keyValue-- > 0;) {
    Value kc = arith::ConstantIndexOp::create(
        buildPoint, loc, ab.choice.rotValue(lowerIndex, keyValue));
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

/// Carries the store-forwarding counters of `from` (hls.forwarded_loads /
/// hls.removed_stores, set by --pre-bank-forwarding, VITIS_NOTES N138) onto
/// a bank access that replaces it, so that --bram-debug still reports, per
/// bank, the loads and stores forwarding removed (W9 round 18 review
/// defect 6: banking rebuilt the accesses without them).
static void copyForwardingCounters(Operation *from, Operation *to) {
  for (StringRef name : {"hls.forwarded_loads", "hls.removed_stores"})
    if (Attribute arrayValue = from->getAttr(name))
      to->setAttr(name, arrayValue);
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
    auto ns = affine::AffineStoreOp::create(
        buildPoint, loc, operandValue, banks[ab.choice.bank(lowerIndex, 0)],
        ab.bankedMap, operands);
    copyForwardingCounters(storeOp, ns);
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

  for (int64_t keyValue = 0; keyValue < elementCount; ++keyValue)
    if (!reach ||
        llvm::is_contained(*reach, ab.choice.rotValue(lowerIndex, keyValue)))
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
    auto se =
        AffineStoreEnableOp::create(buildPoint, loc, operandValue,
                                    banks[ab.choice.bank(lowerIndex, keyValue)],
                                    operands, operands, ab.bankedMap, cond);
    copyForwardingCounters(storeOp, se);
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
  for (Value opHandle : def->getOperands()) {
    if (!opHandle.getType().isIntOrIndex())
      return std::nullopt;
    std::optional<int64_t> candidateValue =
        evaluateConstantInt(opHandle, depth + 1);
    if (!candidateValue)
      return std::nullopt;
    operands.push_back(IntegerAttr::get(opHandle.getType(), *candidateValue));
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

/// The values a memref index can take, from its operations' types and
/// constants, as LLVM's value-range analysis gives Vitis (VITIS_NOTES N175):
/// a zero extension of an N-bit value is in [0, 2^N - 1], a sign extension
/// in [-2^(N-1), 2^(N-1) - 1], an `and` with a non-negative constant in
/// [0, mask], a remainder by a constant c in [-(c - 1), c - 1] (unsigned:
/// [0, c - 1]), an unsigned shift right of a non-negative range by a
/// constant shrinks it; add / sub / mul combine ranges. Loop counters are
/// unknown. nullopt when unknown or too wide for int64 arithmetic.
using ValueRange64 = std::pair<int64_t, int64_t>;
using RangeMemo = DenseMap<Value, std::optional<ValueRange64>>;
static std::optional<ValueRange64>
memrefIndexRangeImpl(Value valueHandle, unsigned depth, RangeMemo &memo);

/// memrefIndexRange of `v`, memoized in `memo` (one query walks a DAG of
/// operations that share operands: without it the walk is exponential in
/// its depth; hlsyn fdtd-2d-large / symm-opt-medium timed out).
///
/// Ranges are kept in the signed reading of the value's integer type, as
/// MLIR's constants are: an N-bit result whose computed range leaves
/// [-2^(N-1), 2^(N-1) - 1] wraps, so its range becomes that whole interval
/// (review W9r23 D1: `u8 t = in & 15; t += 250` is `addi i8 %t, -6`, values
/// 250..255 and 0..9 once read unsigned).
static unsigned rangeBitWidth(Value exprValue) {
  return exprValue.getType().isIndex()
             ? 64u
             : exprValue.getType().getIntOrFloatBitWidth();
}
static std::optional<ValueRange64> signedTypeRange(unsigned elementCount) {
  if (elementCount == 0 || elementCount >= 40)
    return std::nullopt;
  return ValueRange64{-(int64_t(1) << (elementCount - 1)),
                      (int64_t(1) << (elementCount - 1)) - 1};
}
/// The values of an N-bit integer with signed range `r` (nullopt: unknown)
/// read as unsigned (index_castui, extui): a range below zero moves up by
/// 2^N; one that straddles zero covers [0, 2^N - 1] (the interval hull of
/// the two wrapped pieces); an unknown one is [0, 2^N - 1] (review W9r23
/// D2: index_castui of a loaded i8 reaches 0..255 only).
static std::optional<ValueRange64>
unsignedReading(std::optional<ValueRange64> resultValue,
                unsigned elementCount) {
  if (elementCount >= 40)
    return resultValue && resultValue->first >= 0 ? resultValue : std::nullopt;
  int64_t span = int64_t(1) << elementCount;
  if (!resultValue || (resultValue->first < 0 && resultValue->second >= 0))
    return ValueRange64{0, span - 1};
  if (resultValue->second < 0)
    return ValueRange64{resultValue->first + span, resultValue->second + span};
  return resultValue;
}
static std::optional<ValueRange64>
memrefIndexRange(Value valueHandle, unsigned depth, RangeMemo &memo) {
  auto it = memo.find(valueHandle);
  if (it != memo.end())
    return it->second;
  std::optional<ValueRange64> resultValue =
      memrefIndexRangeImpl(valueHandle, depth, memo);
  if (resultValue && valueHandle.getType().isSignlessInteger())
    if (std::optional<ValueRange64> typeValue =
            signedTypeRange(rangeBitWidth(valueHandle));
        typeValue && (resultValue->first < typeValue->first ||
                      resultValue->second > typeValue->second))
      resultValue = typeValue;
  memo[valueHandle] = resultValue;
  return resultValue;
}
static std::optional<ValueRange64> memrefIndexRange(Value valueHandle) {
  RangeMemo memo;
  return memrefIndexRange(valueHandle, 0, memo);
}

static std::optional<ValueRange64>
memrefIndexRangeImpl(Value valueHandle, unsigned depth, RangeMemo &memo) {
  constexpr int64_t kLimit = int64_t(1) << 40;
  auto bounded = [&](ValueRange64 resultValue) -> std::optional<ValueRange64> {
    if (resultValue.first < -kLimit || resultValue.second > kLimit ||
        resultValue.first > resultValue.second)
      return std::nullopt;
    return resultValue;
  };
  if (std::optional<int64_t> candidateValue = getConstantIntValue(valueHandle))
    return bounded({*candidateValue, *candidateValue});
  if (depth > 16)
    return std::nullopt;

  Operation *def = valueHandle.getDefiningOp();
  if (!def)
    return std::nullopt;
  auto widthOf = rangeBitWidth;
  if (isa<arith::ExtUIOp, arith::IndexCastUIOp>(def)) {
    Value in = def->getOperand(0);
    unsigned elementCount = widthOf(in);
    if (elementCount >= 40 && isa<arith::ExtUIOp>(def))
      return memrefIndexRange(in, depth + 1, memo);
    return unsignedReading(memrefIndexRange(in, depth + 1, memo), elementCount);
  }
  if (isa<arith::ExtSIOp, arith::IndexCastOp>(def)) {
    if (auto resultValue =
            memrefIndexRange(def->getOperand(0), depth + 1, memo))
      return resultValue;
    return signedTypeRange(widthOf(def->getOperand(0)));
  }

  if (auto apply = dyn_cast<affine::AffineApplyOp>(def)) {
    SmallVector<Attribute> operands;
    for (Value opHandle : apply.getMapOperands()) {
      auto resultValue = memrefIndexRange(opHandle, depth + 1, memo);
      if (!resultValue || resultValue->first != resultValue->second)
        return std::nullopt;
      operands.push_back(
          IntegerAttr::get(opHandle.getType(), resultValue->first));
    }
    SmallVector<Attribute> results;
    if (failed(apply.getAffineMap().constantFold(operands, results)) ||
        results.size() != 1)
      return std::nullopt;
    if (auto ia = dyn_cast_or_null<IntegerAttr>(results[0]))
      return bounded({ia.getInt(), ia.getInt()});
    return std::nullopt;
  }
  if (auto tr = dyn_cast<arith::TruncIOp>(def)) {
    auto resultValue = memrefIndexRange(tr.getIn(), depth + 1, memo);
    unsigned elementCount = widthOf(tr.getResult());
    if (resultValue && elementCount < 40 &&
        resultValue->first >= -(int64_t(1) << (elementCount - 1)) &&
        resultValue->second < (int64_t(1) << (elementCount - 1)))
      return resultValue;
    return signedTypeRange(elementCount);
  }
  if (isa<arith::AndIOp>(def)) {
    for (unsigned loopIndex = 0; loopIndex < 2; ++loopIndex)
      if (std::optional<int64_t> memoryOp =
              constantIndexOf(def->getOperand(loopIndex));
          memoryOp && *memoryOp >= 0) {
        auto resultValue =
            memrefIndexRange(def->getOperand(1 - loopIndex), depth + 1, memo);
        if (resultValue && resultValue->first >= 0)
          return bounded({0, std::min(resultValue->second, *memoryOp)});
        return bounded({0, *memoryOp});
      }
    return std::nullopt;
  }

  if (isa<arith::RemSIOp>(def)) {
    std::optional<int64_t> candidateValue = constantIndexOf(def->getOperand(1));
    if (!candidateValue || *candidateValue <= 0)
      return std::nullopt;
    auto resultValue = memrefIndexRange(def->getOperand(0), depth + 1, memo);
    if (resultValue && resultValue->first >= 0)
      return bounded({0, std::min(resultValue->second, *candidateValue - 1)});
    return std::nullopt;
  }
  if (isa<arith::RemUIOp>(def)) {
    std::optional<int64_t> candidateValue = constantIndexOf(def->getOperand(1));
    if (!candidateValue || *candidateValue <= 0)
      return std::nullopt;
    auto resultValue = memrefIndexRange(def->getOperand(0), depth + 1, memo);
    if (resultValue && resultValue->first >= 0 &&
        resultValue->second < *candidateValue)
      return resultValue;
    return bounded({0, *candidateValue - 1});
  }
  if (isa<arith::ShRUIOp, arith::ShRSIOp>(def)) {
    std::optional<int64_t> keyValue = constantIndexOf(def->getOperand(1));
    auto resultValue = memrefIndexRange(def->getOperand(0), depth + 1, memo);
    if (!keyValue || *keyValue < 0 || *keyValue >= 62 || !resultValue ||
        resultValue->first < 0)
      return std::nullopt;
    return bounded(
        {resultValue->first >> *keyValue, resultValue->second >> *keyValue});
  }
  if (isa<arith::AddIOp, arith::SubIOp, arith::MulIOp>(def)) {
    auto arrayValue = memrefIndexRange(def->getOperand(0), depth + 1, memo);
    if (!arrayValue)
      return std::nullopt;
    auto candidateValue = memrefIndexRange(def->getOperand(1), depth + 1, memo);
    if (!candidateValue)
      return std::nullopt;
    if (isa<arith::AddIOp>(def))
      return bounded({arrayValue->first + candidateValue->first,
                      arrayValue->second + candidateValue->second});
    if (isa<arith::SubIOp>(def))
      return bounded({arrayValue->first - candidateValue->second,
                      arrayValue->second - candidateValue->first});
    int64_t portValue[4] = {arrayValue->first * candidateValue->first,
                            arrayValue->first * candidateValue->second,
                            arrayValue->second * candidateValue->first,
                            arrayValue->second * candidateValue->second};
    return bounded({*std::min_element(portValue, portValue + 4),
                    *std::max_element(portValue, portValue + 4)});
  }
  return std::nullopt;
}

/// The banks a memref index of a block or complete partition can reach,
/// from its value range (memrefIndexRange) clipped to the dimension (an
/// index outside it is undefined behaviour; VITIS_NOTES N175): (first bank,
/// number of banks); nullopt when the range is unknown or reaches every
/// bank. Key tool.hls.partitioning.banks_from_value_range.
static std::optional<std::pair<int64_t, int64_t>>
banksFromRange(Value indexValue, const DimPartition &portValue) {
  bool complete = portValue.kind == PartitionSpec::Complete ||
                  (portValue.kind == PartitionSpec::Cyclic &&
                   portValue.factor == portValue.extent);
  if ((portValue.kind != PartitionSpec::Block && !complete) ||
      portValue.factor <= 1 || portValue.depth <= 0 ||
      !circt::hlsest::Config::get().tool.hls.partitioning.banksFromValueRange)
    return std::nullopt;
  std::optional<ValueRange64> resultValue = memrefIndexRange(indexValue);
  if (!resultValue)
    return std::nullopt;
  int64_t first = std::max<int64_t>(resultValue->first, 0);
  int64_t last = std::min<int64_t>(resultValue->second, portValue.extent - 1);
  if (first > last)
    return std::nullopt;
  int64_t lo = first / portValue.depth, hi = last / portValue.depth;
  if (lo == 0 && hi >= portValue.factor - 1)
    return std::nullopt;
  return std::make_pair(lo, std::min(hi, portValue.factor - 1) - lo + 1);
}

/// banksFromRange for an affine index expression: its dimensions and
/// symbols take the value ranges of their operands (memrefIndexRange).
static std::optional<std::pair<int64_t, int64_t>>
affineBanksFromRange(AffineExpr entryValue, ArrayRef<Value> operands,
                     unsigned nDims, const DimPartition &portValue) {
  bool complete = portValue.kind == PartitionSpec::Complete ||
                  (portValue.kind == PartitionSpec::Cyclic &&
                   portValue.factor == portValue.extent);
  if ((portValue.kind != PartitionSpec::Block && !complete) ||
      portValue.factor <= 1 ||
      !circt::hlsest::Config::get().tool.hls.partitioning.banksFromValueRange)
    return std::nullopt;
  RangeMemo memo;
  std::function<std::optional<ValueRange64>(AffineExpr)> eval =
      [&](AffineExpr exprValue) -> std::optional<ValueRange64> {
    if (auto candidateValue = dyn_cast<AffineConstantExpr>(exprValue))
      return ValueRange64{candidateValue.getValue(), candidateValue.getValue()};
    if (auto dimensionIndex = dyn_cast<AffineDimExpr>(exprValue))
      return memrefIndexRange(operands[dimensionIndex.getPosition()], 0, memo);
    if (auto sy = dyn_cast<AffineSymbolExpr>(exprValue))
      return memrefIndexRange(operands[nDims + sy.getPosition()], 0, memo);
    auto bin = dyn_cast<AffineBinaryOpExpr>(exprValue);
    if (!bin)
      return std::nullopt;
    auto rc = dyn_cast<AffineConstantExpr>(bin.getRHS());

    if (exprValue.getKind() == AffineExprKind::Mod && rc && rc.getValue() > 0 &&
        !eval(bin.getLHS()))
      return ValueRange64{0, rc.getValue() - 1};
    auto lowerIndex = eval(bin.getLHS());
    if (!lowerIndex)
      return std::nullopt;
    switch (exprValue.getKind()) {
    case AffineExprKind::Add: {
      auto resultValue = eval(bin.getRHS());
      if (!resultValue)
        return std::nullopt;
      return ValueRange64{lowerIndex->first + resultValue->first,
                          lowerIndex->second + resultValue->second};
    }
    case AffineExprKind::Mul: {
      if (!rc)
        return std::nullopt;
      int64_t arrayValue = lowerIndex->first * rc.getValue(),
              buildPoint = lowerIndex->second * rc.getValue();
      return ValueRange64{std::min(arrayValue, buildPoint),
                          std::max(arrayValue, buildPoint)};
    }
    case AffineExprKind::FloorDiv:
      if (!rc || rc.getValue() <= 0)
        return std::nullopt;
      return ValueRange64{
          llvm::divideFloorSigned(lowerIndex->first, rc.getValue()),
          llvm::divideFloorSigned(lowerIndex->second, rc.getValue())};
    case AffineExprKind::Mod: {
      if (!rc || rc.getValue() <= 0)
        return std::nullopt;
      int64_t memoryOp = rc.getValue();
      if (llvm::divideFloorSigned(lowerIndex->first, memoryOp) !=
          llvm::divideFloorSigned(lowerIndex->second, memoryOp))
        return ValueRange64{0, memoryOp - 1};
      return ValueRange64{llvm::mod(lowerIndex->first, memoryOp),
                          llvm::mod(lowerIndex->second, memoryOp)};
    }
    default:
      return std::nullopt;
    }
  };
  std::optional<ValueRange64> resultValue = eval(entryValue);
  constexpr int64_t kLimit = int64_t(1) << 40;
  if (!resultValue || resultValue->first < -kLimit ||
      resultValue->second > kLimit)
    return std::nullopt;
  int64_t first = std::max<int64_t>(resultValue->first, 0);
  int64_t last = std::min<int64_t>(resultValue->second, portValue.extent - 1);
  if (first > last)
    return std::nullopt;
  int64_t lo = first / portValue.depth, hi = last / portValue.depth;
  if (lo == 0 && hi >= portValue.factor - 1)
    return std::nullopt;
  return std::make_pair(lo, std::min(hi, portValue.factor - 1) - lo + 1);
}

/// One `arith.constant 0 : index` at the start of the function holding `at`
/// (made once, marked `hls.bank_offset_zero`): the in-bank offset of every
/// read of a completely partitioned dimension at a run-time bank, so that
/// the per-bank loads of reads that share their other subscripts are one
/// load for --convert-affine-to-loopschedule's load merging (VITIS_NOTES
/// N172).
static Value sharedZeroIndex(Operation *at) {
  auto fn = at->getParentOfType<func::FuncOp>();
  if (!fn && isa<func::FuncOp>(at))
    fn = cast<func::FuncOp>(at);
  Block &entry = fn.getBody().front();
  for (Operation &op : entry) {
    if (!op.hasAttr("hls.bank_offset_zero"))
      continue;
    return op.getResult(0);
  }
  OpBuilder buildPoint(&entry, entry.begin());
  auto candidateValue =
      arith::ConstantIndexOp::create(buildPoint, fn.getLoc(), 0);
  candidateValue->setAttr("hls.bank_offset_zero", buildPoint.getUnitAttr());
  return candidateValue.getResult();
}

/// `useRanges`: narrow block / complete dimensions by the index's value
/// range (off for the members of a steered group, whose candidate set is
/// the group's).
static MemrefBanking resolveMemref(OpBuilder &buildPoint, Location loc,
                                   ValueRange indices,
                                   const BankLayout &lowerIndex,
                                   bool useRanges = true) {
  MemrefBanking mb;
  mb.bankedIndices.assign(indices.begin(), indices.end());
  SmallVector<Value> rot;
  SmallVector<std::pair<int64_t, int64_t>, 2> rangeReach;
  bool anyNarrowReach = false;
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

    std::optional<std::pair<int64_t, int64_t>> reach =
        useRanges ? banksFromRange(indexValue, portValue) : std::nullopt;
    if (reach && reach->second == 1) {
      mb.choice.constBank.push_back(reach->first);
      Value dimensionIndex =
          arith::ConstantIndexOp::create(buildPoint, loc, portValue.depth);
      mb.bankedIndices[portValue.dim] =
          arith::RemUIOp::create(buildPoint, loc, indexValue, dimensionIndex)
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

    bool completeDim = portValue.kind == PartitionSpec::Complete ||
                       (!bankIsDiv && portValue.factor == portValue.extent);
    Value offV =
        completeDim && circt::hlsest::Config::get()
                           .tool.hls.partitioning.sharedAddressBankReads
            ? sharedZeroIndex(buildPoint.getInsertionBlock()->getParentOp())
        : bankIsDiv ? arith::RemUIOp::create(buildPoint, loc, indexValue,
                                             dimensionIndex)
                          .getResult()
                    : arith::DivUIOp::create(buildPoint, loc, indexValue,
                                             dimensionIndex)
                          .getResult();
    mb.bankedIndices[portValue.dim] = offV;
    mb.choice.constBank.push_back(std::nullopt);
    mb.choice.rotating.push_back(innerIndex);
    rangeReach.push_back(reach ? *reach
                               : std::make_pair(int64_t(0), portValue.factor));
    anyNarrowReach |= reach.has_value();
    rot.push_back(bankV);
  }
  if (anyNarrowReach)
    mb.choice.reach = std::move(rangeReach);
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
    markRuntimeBankRead(vals.back().getDefiningOp(), mb.choice, lowerIndex);
  }
  Value result = vals[elementCount - 1];
  for (int64_t keyValue = elementCount - 1; keyValue-- > 0;) {
    Value kc = arith::ConstantIndexOp::create(
        buildPoint, loc, mb.choice.rotValue(lowerIndex, keyValue));
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
  for (Value opHandle : def->getOperands())
    if (!hoistBefore(opHandle, before, dryRun, depth + 1))
      return false;
  if (!dryRun)
    def->moveBefore(before);
  return true;
}

/// tool.hls.partitioning.steer_through_guards (VITIS_NOTES N155): the
/// unrolled copies of a window read each under its own guard (`if (l + k in
/// range) s += X[l + k - 2]`) still form one steered group, as Vitis reads
/// every bank once per load state whatever the guards (kernel w9r21p_g1).
static bool steerThroughGuards() {
  return circt::hlsest::Config::get().tool.hls.partitioning.steerThroughGuards;
}

/// Per (block, array): whether the block holds a call or a store to the
/// array (guardAnchor); cleared by each banking run.
static DenseMap<std::pair<Block *, Value>, bool> guardBlockWrites;

/// An scf.if / affine.if steered groups look through: any guard but the
/// trip test of a copy of a run-time-trip partial unroll (a loop marked
/// hls.unroll_runtime_guarded), whose copies Vitis lets reach every bank
/// (VITIS_NOTES N103, kernel w9r14p_uv_var: a separate PIPO, 116).
static bool isSteerableGuard(Operation *op) {
  if (!isa_and_nonnull<scf::IfOp, affine::AffineIfOp>(op))
    return false;
  Operation *parent = op->getParentOp();
  return !parent || !parent->hasAttr("hls.unroll_runtime_guarded");
}

/// The op that stands for `op` in its group's block: `op` itself, or (with
/// steerThroughGuards) the outermost scf.if / affine.if it is nested in
/// without a loop or another region op between.
static Operation *guardAnchor(Operation *op) {
  if (!steerThroughGuards())
    return op;
  Operation *anchor = op;
  while (isSteerableGuard(anchor->getParentOp()))
    anchor = anchor->getParentOp();
  if (anchor == op)
    return op;

  Value mem;
  if (auto ld = dyn_cast<memref::LoadOp>(op))
    mem = ld.getMemRef();
  else if (auto ld = dyn_cast<affine::AffineLoadOp>(op))
    mem = ld.getMemRef();
  else
    return op;
  unsigned accesses = 0;
  anchor->walk([&](Operation *inner) {
    if (llvm::is_contained(inner->getOperands(), mem))
      ++accesses;
  });
  if (accesses != 1)
    return op;

  auto key = std::make_pair(anchor->getBlock(), mem);
  auto it = guardBlockWrites.find(key);
  if (it == guardBlockWrites.end()) {
    bool writes = false;
    for (Operation &top : *anchor->getBlock())
      top.walk([&](Operation *inner) {
        if (isa<CallOpInterface>(inner) ||
            (isa<memref::StoreOp, affine::AffineStoreOp, StoreEnableOp,
                 AffineStoreEnableOp>(inner) &&
             llvm::is_contained(inner->getOperands(), mem)))
          writes = true;
      });
    it = guardBlockWrites.try_emplace(key, writes).first;
  }
  return it->second ? op : anchor;
}

/// Program order of two ops of one group: by their anchors, then (same
/// anchor) by position in the anchor's regions.
static bool steerBefore(Operation *arrayValue, Operation *buildPoint) {
  Operation *aa = guardAnchor(arrayValue), *ab = guardAnchor(buildPoint);
  if (aa != ab)
    return aa->isBeforeInBlock(ab);
  if (arrayValue->getBlock() == buildPoint->getBlock())
    return arrayValue->isBeforeInBlock(buildPoint);

  bool seenA = false, aFirst = false;
  aa->walk<WalkOrder::PreOrder>([&](Operation *op) {
    if (op == arrayValue && !seenA) {
      seenA = true;
      aFirst = true;
      return WalkResult::interrupt();
    }
    if (op == buildPoint)
      return WalkResult::interrupt();
    return WalkResult::advance();
  });
  return aFirst;
}

/// hoistBefore that also moves side-effect-free ops nested in the if arms
/// of `before`'s block (the index of a guarded copy, steerThroughGuards).
static bool hoistBeforeThroughGuards(Value valueHandle, Operation *before,
                                     bool dryRun, unsigned depth = 0) {
  Operation *def = valueHandle.getDefiningOp();
  if (!def)
    return true;
  if (def == before)
    return false;
  Block *block = before->getBlock();
  if (def->getBlock() == block)
    return hoistBefore(valueHandle, before, dryRun, depth);

  Operation *anchor = def->getParentOp();
  bool throughIfs = true;
  while (anchor && anchor->getBlock() != block) {
    throughIfs &= isSteerableGuard(anchor);
    anchor = anchor->getParentOp();
  }
  if (!anchor)
    return true;
  if (!steerThroughGuards() || !throughIfs || !isSteerableGuard(anchor))
    return false;
  if (depth > 64 || def->getNumRegions() || !isMemoryEffectFree(def))
    return false;
  for (Value opHandle : def->getOperands())
    if (!hoistBeforeThroughGuards(opHandle, before, dryRun, depth + 1))
      return false;
  if (!dryRun)
    def->moveBefore(before);
  return true;
}

/// tool.hls.partitioning.drop_unread_banks (VITIS_NOTES N157).
static bool dropUnreadBanks() {
  return circt::hlsest::Config::get().tool.hls.partitioning.dropUnreadBanks;
}

/// The values an index can take, from the constant bounds of the affine.for
/// counters and the constants it is built of (+, - and * by a constant,
/// affine.apply of such expressions, index casts); nullopt when unknown.
static std::optional<std::pair<int64_t, int64_t>>
indexRange(Value valueHandle, unsigned depth = 0) {
  if (depth > 16)
    return std::nullopt;
  if (std::optional<int64_t> candidateValue = getConstantIntValue(valueHandle))
    return std::make_pair(*candidateValue, *candidateValue);
  if (affine::isAffineForInductionVar(valueHandle)) {
    affine::AffineForOp fieldValue =
        affine::getForInductionVarOwner(valueHandle);
    if (!fieldValue.hasConstantBounds() || fieldValue.getStepAsInt() <= 0)
      return std::nullopt;
    int64_t lb = fieldValue.getConstantLowerBound(),
            ub = fieldValue.getConstantUpperBound();
    if (ub <= lb)
      return std::nullopt;
    int64_t step = fieldValue.getStepAsInt();
    return std::make_pair(lb, lb + (ub - 1 - lb) / step * step);
  }
  Operation *def = valueHandle.getDefiningOp();
  if (!def)
    return std::nullopt;
  if (isa<arith::IndexCastOp, arith::IndexCastUIOp, arith::ExtSIOp,
          arith::ExtUIOp>(def))
    return indexRange(def->getOperand(0), depth + 1);
  auto combine = [](std::pair<int64_t, int64_t> arrayValue,
                    std::pair<int64_t, int64_t> buildPoint,
                    char op) -> std::optional<std::pair<int64_t, int64_t>> {
    if (op == '+')
      return std::make_pair(arrayValue.first + buildPoint.first,
                            arrayValue.second + buildPoint.second);
    if (op == '-')
      return std::make_pair(arrayValue.first - buildPoint.second,
                            arrayValue.second - buildPoint.first);
    int64_t candidateValue[4] = {arrayValue.first * buildPoint.first,
                                 arrayValue.first * buildPoint.second,
                                 arrayValue.second * buildPoint.first,
                                 arrayValue.second * buildPoint.second};
    return std::make_pair(
        *std::min_element(candidateValue, candidateValue + 4),
        *std::max_element(candidateValue, candidateValue + 4));
  };
  if (isa<arith::AddIOp, arith::SubIOp, arith::MulIOp>(def)) {
    auto arrayValue = indexRange(def->getOperand(0), depth + 1);
    auto buildPoint = indexRange(def->getOperand(1), depth + 1);
    if (!arrayValue || !buildPoint)
      return std::nullopt;
    return combine(*arrayValue, *buildPoint,
                   isa<arith::AddIOp>(def)   ? '+'
                   : isa<arith::SubIOp>(def) ? '-'
                                             : '*');
  }
  if (auto apply = dyn_cast<affine::AffineApplyOp>(def)) {
    AffineMap map = apply.getAffineMap();
    SmallVector<std::optional<std::pair<int64_t, int64_t>>> ops;
    for (Value opHandle : apply.getMapOperands())
      ops.push_back(indexRange(opHandle, depth + 1));
    std::function<std::optional<std::pair<int64_t, int64_t>>(AffineExpr)> eval =
        [&](AffineExpr entryValue)
        -> std::optional<std::pair<int64_t, int64_t>> {
      if (auto candidateValue = dyn_cast<AffineConstantExpr>(entryValue))
        return std::make_pair(candidateValue.getValue(),
                              candidateValue.getValue());
      if (auto dimensionIndex = dyn_cast<AffineDimExpr>(entryValue))
        return ops[dimensionIndex.getPosition()];
      if (auto stringValue = dyn_cast<AffineSymbolExpr>(entryValue))
        return ops[map.getNumDims() + stringValue.getPosition()];
      auto bin = dyn_cast<AffineBinaryOpExpr>(entryValue);
      if (!bin)
        return std::nullopt;
      auto lowerIndex = eval(bin.getLHS()), resultValue = eval(bin.getRHS());
      if (!lowerIndex || !resultValue)
        return std::nullopt;
      if (entryValue.getKind() == AffineExprKind::Add)
        return combine(*lowerIndex, *resultValue, '+');
      if (entryValue.getKind() == AffineExprKind::Mul)
        return combine(*lowerIndex, *resultValue, '*');
      return std::nullopt;
    };
    if (map.getNumResults() != 1)
      return std::nullopt;
    return eval(map.getResult(0));
  }
  return std::nullopt;
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

/// Residue sets modulo a partition factor (possibleResidues).
using ResidueSet = std::set<int64_t>;

static ResidueSet allResidues(int64_t fieldValue) {
  ResidueSet out;
  for (int64_t valueHandle = 0; valueHandle < fieldValue; ++valueHandle)
    out.insert(valueHandle);
  return out;
}

/// {a + b} / {a * b} over two residue sets, modulo f.
static ResidueSet combineResidues(const ResidueSet &exprValue,
                                  const ResidueSet &rowValue,
                                  int64_t fieldValue, bool multiply) {
  ResidueSet out;
  for (int64_t arrayValue : exprValue)
    for (int64_t buildPoint : rowValue)
      out.insert(llvm::mod(multiply ? arrayValue * buildPoint
                                    : arrayValue + buildPoint,
                           fieldValue));
  return out;
}

static ResidueSet mapResidues(const ResidueSet &exprValue, int64_t fieldValue,
                              llvm::function_ref<int64_t(int64_t)> fn) {
  ResidueSet out;
  for (int64_t arrayValue : exprValue)
    out.insert(llvm::mod(fn(arrayValue), fieldValue));
  return out;
}

using ResidueMemo = llvm::DenseMap<Value, ResidueSet>;
static ResidueSet residuesOf(Value valueHandle, int64_t fieldValue,
                             unsigned depth, ResidueMemo &memo);

/// The residues of an affine expression whose dims / symbols take the given
/// residue sets: + and * combine the sets; a modulo by a multiple of f keeps
/// its operand's residues; a division, or a modulo by anything else, is an
/// unknown integer (every residue).
static ResidueSet affineExprResidues(AffineExpr entryValue,
                                     ArrayRef<ResidueSet> dims,
                                     ArrayRef<ResidueSet> syms,
                                     int64_t fieldValue) {
  if (auto candidateValue = dyn_cast<AffineConstantExpr>(entryValue))
    return {llvm::mod(candidateValue.getValue(), fieldValue)};
  if (auto dimensionIndex = dyn_cast<AffineDimExpr>(entryValue))
    return dims[dimensionIndex.getPosition()];
  if (auto sy = dyn_cast<AffineSymbolExpr>(entryValue))
    return syms[sy.getPosition()];
  auto bin = cast<AffineBinaryOpExpr>(entryValue);
  switch (entryValue.getKind()) {
  case AffineExprKind::Add:
  case AffineExprKind::Mul:
    return combineResidues(
        affineExprResidues(bin.getLHS(), dims, syms, fieldValue),
        affineExprResidues(bin.getRHS(), dims, syms, fieldValue), fieldValue,
        entryValue.getKind() == AffineExprKind::Mul);
  case AffineExprKind::Mod:
    if (auto memoryOp = dyn_cast<AffineConstantExpr>(bin.getRHS()))
      if (memoryOp.getValue() > 0 && memoryOp.getValue() % fieldValue == 0)
        return affineExprResidues(bin.getLHS(), dims, syms, fieldValue);
    return allResidues(fieldValue);
  default:
    return allResidues(fieldValue);
  }
}

/// The residues modulo f an index value can take, by known bits: constants;
/// loop counters lb + step * t (affine.for / scf.for with constant lower
/// bound and step); casts; + - * and shifts left by a constant; and / or
/// with a constant mask (f a power of two); a remainder by a multiple of f;
/// select (either value); affine.apply. Anything else (a division, a load,
/// a function argument) is an unknown integer: every residue. Correlations
/// between operands are not tracked, so the set can only grow.
static ResidueSet computeResidues(Value valueHandle, int64_t fieldValue,
                                  unsigned depth, ResidueMemo &memo);

static ResidueSet residuesOf(Value valueHandle, int64_t fieldValue,
                             unsigned depth, ResidueMemo &memo) {
  auto it = memo.find(valueHandle);
  if (it != memo.end())
    return it->second;
  ResidueSet out = computeResidues(valueHandle, fieldValue, depth, memo);
  memo[valueHandle] = out;
  return out;
}

static ResidueSet computeResidues(Value valueHandle, int64_t fieldValue,
                                  unsigned depth, ResidueMemo &memo) {
  constexpr unsigned kMaxDepth = 24;
  if (std::optional<int64_t> candidateValue = constantIndexOf(valueHandle))
    return {llvm::mod(*candidateValue, fieldValue)};
  if (depth > kMaxDepth)
    return allResidues(fieldValue);

  auto counter = [&](int64_t lb, int64_t step) {
    ResidueSet out;
    for (int64_t typeValue = 0; typeValue < fieldValue; ++typeValue)
      out.insert(llvm::mod(lb + step * typeValue, fieldValue));
    return out;
  };
  if (affine::isAffineForInductionVar(valueHandle)) {
    affine::AffineForOp owner = affine::getForInductionVarOwner(valueHandle);
    if (owner.hasConstantLowerBound())
      return counter(owner.getConstantLowerBound(), owner.getStepAsInt());
    return allResidues(fieldValue);
  }
  if (auto arg = dyn_cast<BlockArgument>(valueHandle)) {
    if (auto loop = dyn_cast_or_null<scf::ForOp>(arg.getOwner()->getParentOp()))
      if (loop.getInductionVar() == arg) {
        std::optional<int64_t> lb = getConstantIntValue(loop.getLowerBound());
        std::optional<int64_t> st = getConstantIntValue(loop.getStep());
        if (lb && st)
          return counter(*lb, *st);
      }
    return allResidues(fieldValue);
  }
  Operation *def = valueHandle.getDefiningOp();
  if (!def)
    return allResidues(fieldValue);
  const bool pow2 = llvm::isPowerOf2_64(static_cast<uint64_t>(fieldValue));
  const unsigned bits = llvm::Log2_64(static_cast<uint64_t>(fieldValue));
  auto operand = [&](unsigned loopIndex) {
    return residuesOf(def->getOperand(loopIndex), fieldValue, depth + 1, memo);
  };
  if (isa<arith::IndexCastOp, arith::IndexCastUIOp, arith::ExtSIOp,
          arith::ExtUIOp>(def))
    return operand(0);
  if (auto tr = dyn_cast<arith::TruncIOp>(def)) {
    if (pow2 && tr.getType().getIntOrFloatBitWidth() >= bits)
      return operand(0);
    return allResidues(fieldValue);
  }
  if (isa<arith::AddIOp>(def))
    return combineResidues(operand(0), operand(1), fieldValue, false);
  if (isa<arith::SubIOp>(def))
    return combineResidues(
        operand(0),
        mapResidues(operand(1), fieldValue,
                    [](int64_t exprValue) { return -exprValue; }),
        fieldValue, false);
  if (isa<arith::MulIOp>(def))
    return combineResidues(operand(0), operand(1), fieldValue, true);
  if (auto shl = dyn_cast<arith::ShLIOp>(def)) {
    std::optional<int64_t> keyValue = constantIndexOf(shl.getRhs());
    if (!keyValue || *keyValue < 0 || *keyValue > 62)
      return allResidues(fieldValue);
    int64_t scale = llvm::mod(int64_t(1) << *keyValue, fieldValue);
    return mapResidues(operand(0), fieldValue,
                       [&](int64_t exprValue) { return exprValue * scale; });
  }
  if (isa<arith::AndIOp, arith::OrIOp>(def) && pow2) {

    for (unsigned loopIndex = 0; loopIndex < 2; ++loopIndex)
      if (std::optional<int64_t> memoryOp =
              constantIndexOf(def->getOperand(loopIndex))) {
        int64_t low = llvm::mod(*memoryOp, fieldValue);
        bool isAnd = isa<arith::AndIOp>(def);
        return mapResidues(
            operand(1 - loopIndex), fieldValue, [&](int64_t exprValue) {
              return isAnd ? (exprValue & low) : (exprValue | low);
            });
      }
    return allResidues(fieldValue);
  }
  if (isa<arith::RemSIOp, arith::RemUIOp>(def)) {
    std::optional<int64_t> memoryOp = constantIndexOf(def->getOperand(1));
    if (memoryOp && *memoryOp > 0 && *memoryOp % fieldValue == 0)
      return operand(0);
    return allResidues(fieldValue);
  }
  if (auto sel = dyn_cast<arith::SelectOp>(def)) {
    ResidueSet out =
        residuesOf(sel.getTrueValue(), fieldValue, depth + 1, memo);
    ResidueSet other =
        residuesOf(sel.getFalseValue(), fieldValue, depth + 1, memo);
    out.insert(other.begin(), other.end());
    return out;
  }
  if (auto apply = dyn_cast<affine::AffineApplyOp>(def)) {
    AffineMap map = apply.getAffineMap();
    if (map.getNumResults() != 1)
      return allResidues(fieldValue);
    SmallVector<ResidueSet> dims, syms;
    for (auto [loopIndex, opHandle] : llvm::enumerate(apply.getMapOperands()))
      (loopIndex < map.getNumDims() ? dims : syms)
          .push_back(residuesOf(opHandle, fieldValue, depth + 1, memo));
    return affineExprResidues(map.getResult(0), dims, syms, fieldValue);
  }
  return allResidues(fieldValue);
}

/// The residues modulo the factor a memref index can take (residuesOf;
/// nullopt for a factor too large to enumerate). W9r16 review: an index
/// through a division (`4 * (n / 2)`, kernel w9r16rv_rs_fd) or a mask
/// (`4 * (n & 1)`, w9r16p_rs_same) keeps the residues of the multiply.
static std::optional<ResidueSet>
possibleResidues(Value indexValue, const DimPartition &portValue) {
  constexpr int64_t kMaxFactor = 256;
  const int64_t fieldValue = portValue.factor;
  if (fieldValue <= 1)
    return ResidueSet{0};
  if (fieldValue > kMaxFactor)
    return std::nullopt;
  if (std::optional<int64_t> bank = knownBank(indexValue, portValue))
    return ResidueSet{*bank};
  ResidueMemo memo;
  return residuesOf(indexValue, fieldValue, 0, memo);
}

/// Whether the in-bank address of a steered group depends on which copy
/// addresses the bank (VITIS_NOTES N125): copy j reads offset
/// floor((base + c_j) / f) on its bank, so the address is one value on every
/// candidate bank exactly when no copy's constant carries the base's residue
/// past the factor while another's does not (`4n + r`, r < 4, cyclic 8:
/// banks r or r + 4, address n / 2 on both; `n + k`, k < 8: carries). Vitis
/// reads the first form unpredicated at the one address and muxes the data
/// (kernel w9r16p_rs_nc, polybench_pragmas k3mm tmp2), the second with one
/// predicated load per bank (rs_s1 / s2 / s4, NeuroFPGA padded_A).
static bool steeredAddressVaries(ArrayRef<SteerMember> members,
                                 const BankLayout &lowerIndex,
                                 ArrayRef<unsigned> rotating) {
  for (auto [loopIndex, resultValue] : llvm::enumerate(rotating)) {
    const DimPartition &portValue = lowerIndex.dims[resultValue];
    if (lowerIndex.bankType &&
        lowerIndex.bankType.getShape()[portValue.dim] == 1)
      continue;
    std::optional<ResidueSet> passResult = possibleResidues(
        members.front().load.getIndices()[portValue.dim], portValue);

    if (!passResult)
      return false;
    const int64_t off0 = members.front().offsets[loopIndex];
    for (int64_t r0 : *passResult) {
      int64_t rb = llvm::mod(r0 - off0, portValue.factor);
      std::optional<int64_t> queueValue;
      for (const SteerMember &memoryOp : members) {
        int64_t qj = llvm::divideFloorSigned(rb + memoryOp.offsets[loopIndex],
                                             portValue.factor);
        if (queueValue && *queueValue != qj)
          return true;
        queueValue = qj;
      }
    }
  }
  return false;
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
               return steerBefore(arrayValue.load, buildPoint.load);
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
  Operation *first = guardAnchor(members.front().load);
  bool movable = llvm::all_of(members, [&](const SteerMember &memoryOp) {
    return llvm::all_of(memoryOp.load.getIndices(), [&](Value loopIndex) {
      return hoistBeforeThroughGuards(loopIndex, first, true);
    });
  });
  if (!movable)
    return false;
  for (const SteerMember &memoryOp : members)
    for (Value loopIndex : memoryOp.load.getIndices())
      hoistBeforeThroughGuards(loopIndex, first, false);
  OpBuilder buildPoint(first);
  Location loc = first->getLoc();

  SmallVector<MemrefBanking, 4> mbs;
  for (const SteerMember &memoryOp : members)
    mbs.push_back(resolveMemref(buildPoint, loc, memoryOp.load.getIndices(),
                                lowerIndex, false));
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
  const bool addressVaries =
      !choice.rotating.empty() &&
      steeredAddressVaries(members, lowerIndex, choice.rotating);

  SmallVector<bool> reachable(elementCount, true);
  if (dropUnreadBanks()) {
    constexpr int64_t kMaxEnumerated = 4096;
    std::vector<SmallVector<std::set<int64_t>>> digitSets;
    bool known = true;
    for (const SteerMember &memoryOp : members) {
      SmallVector<std::set<int64_t>> perDim;
      for (unsigned resultValue : choice.rotating) {
        const DimPartition &portValue = lowerIndex.dims[resultValue];
        auto range = indexRange(memoryOp.load.getIndices()[portValue.dim]);
        if (!range || range->second - range->first >= kMaxEnumerated) {
          known = false;
          break;
        }
        std::set<int64_t> banksHit;
        for (int64_t valueHandle = range->first; valueHandle <= range->second;
             ++valueHandle)
          if (valueHandle >= 0 && valueHandle < portValue.extent)
            banksHit.insert(bankAndOffset(valueHandle, portValue).first);
        perDim.push_back(std::move(banksHit));
      }
      if (!known)
        break;
      digitSets.push_back(std::move(perDim));
    }
    if (known)
      for (int64_t keyValue = 0; keyValue < elementCount; ++keyValue) {
        SmallVector<int64_t> dig = choice.digits(lowerIndex, keyValue);
        reachable[keyValue] = llvm::any_of(digitSets, [&](const auto &sets) {
          for (auto [loopIndex, dimensionIndex] : llvm::enumerate(dig))
            if (!sets[loopIndex].count(dimensionIndex))
              return false;
          return true;
        });
      }
    if (llvm::none_of(reachable, [](bool buildPoint) { return buildPoint; }))
      reachable.assign(elementCount, true);
  }
  SmallVector<Value> bankVals(elementCount);
  for (int64_t keyValue = 0; keyValue < elementCount; ++keyValue) {
    if (!reachable[keyValue])
      continue;
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
    bankVals[keyValue] = memref::LoadOp::create(
        buildPoint, loc, banks[choice.bank(lowerIndex, keyValue)], indexValue);
    if (!choice.rotating.empty()) {
      markRotatingRead(bankVals[keyValue].getDefiningOp(), addressVaries);
      markRuntimeBankRead(bankVals[keyValue].getDefiningOp(), choice,
                          lowerIndex);
    }
  }
  SmallVector<Value> results;
  int64_t last = elementCount - 1;
  while (last > 0 && !reachable[last])
    --last;
  for (size_t innerIndex = 0; innerIndex < members.size(); ++innerIndex) {
    Value resultValue = bankVals[last];
    for (int64_t keyValue = last; keyValue-- > 0;)
      if (reachable[keyValue])
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
      AffineGroup key{guardAnchor(ld)->getBlock(), {}, {}, {}, {}};
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
        if (steerBefore(candidateValue->load, firstLoad))
          firstLoad = candidateValue->load;
      firstLoad = guardAnchor(firstLoad);
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
    GroupKey key{guardAnchor(ld)->getBlock(), {}};
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
    auto ns = memref::StoreOp::create(buildPoint, loc, operandValue,
                                      banks[mb.choice.bank(lowerIndex, 0)],
                                      mb.bankedIndices);
    copyForwardingCounters(storeOp, ns);
  } else {
    int64_t elementCount = mb.choice.numCandidates(lowerIndex);
    for (int64_t keyValue = 0; keyValue < elementCount; ++keyValue) {
      Value kc = arith::ConstantIndexOp::create(
          buildPoint, loc, mb.choice.rotValue(lowerIndex, keyValue));
      Value en = arith::CmpIOp::create(buildPoint, loc,
                                       arith::CmpIPredicate::eq, mb.rotIdx, kc);

      if (compoundAssignTwoStores(storeOp)) {
        auto extra = StoreEnableOp::create(
            buildPoint, loc, operandValue, en,
            banks[mb.choice.bank(lowerIndex, keyValue)], mb.bankedIndices);
        extra->setAttr("hls.compound_assign_store", buildPoint.getUnitAttr());
      }
      auto se = StoreEnableOp::create(
          buildPoint, loc, operandValue, en,
          banks[mb.choice.bank(lowerIndex, keyValue)], mb.bankedIndices);
      copyForwardingCounters(storeOp, se);
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

/// A bank alloca of a partitioned local array: its slot in the banking
/// plan, the original array and the bank's index.
struct LocalBank {
  Value *bank;
  std::string name; ///< the original array's polygeist.varname
  unsigned index;
};

/// N157: the banks (local allocas made by the banking, and bank parameters
/// of functions, hls.bank_of) that nothing reads: every use is a store, or
/// passes the bank to a bank parameter of a callee that nothing reads either,
/// and a parameter's every call site passes such a bank. They are removed:
/// the stores, the parameters with their call operands, then the allocas.
static void dropUnreadBankValues(ModuleOp module, SymbolTable &symbols,
                                 ArrayRef<LocalBank> localBanks) {
  OpBuilder buildPoint(module.getContext());
  SetVector<Value> candidates;
  for (const LocalBank &lb : localBanks)
    candidates.insert(*lb.bank);
  DenseMap<Operation *, SmallVector<func::CallOp>> callSitesOf;
  module.walk([&](func::CallOp callSite) {
    if (auto fieldValue = symbols.lookup<func::FuncOp>(callSite.getCallee()))
      callSitesOf[fieldValue].push_back(callSite);
  });
  for (func::FuncOp fieldValue : module.getOps<func::FuncOp>()) {
    if (fieldValue.isExternal() || fieldValue.isPublic() ||
        callSitesOf.lookup(fieldValue).empty() ||
        fieldValue.getFunctionType().getNumInputs() !=
            fieldValue.getBody().front().getNumArguments())
      continue;
    for (unsigned loopIndex = 0; loopIndex < fieldValue.getNumArguments();
         ++loopIndex)
      if (fieldValue.getArgAttr(loopIndex, "hls.bank_of") &&
          isa<MemRefType>(fieldValue.getArgument(loopIndex).getType()))
        candidates.insert(fieldValue.getArgument(loopIndex));
  }
  if (candidates.empty())
    return;
  auto isStore = [](Operation *useValue) {
    return isa<memref::StoreOp, affine::AffineStoreOp, StoreEnableOp,
               AffineStoreEnableOp>(useValue);
  };

  DenseSet<Value> unread(candidates.begin(), candidates.end());
  for (bool changed = true; changed;) {
    changed = false;
    for (Value valueHandle : candidates) {
      if (!unread.contains(valueHandle))
        continue;
      bool ok = llvm::all_of(valueHandle.getUses(), [&](OpOperand &use) {
        Operation *useValue = use.getOwner();
        if (isStore(useValue))
          return true;
        auto callSite = dyn_cast<func::CallOp>(useValue);
        if (!callSite)
          return false;
        auto callee = symbols.lookup<func::FuncOp>(callSite.getCallee());
        return callee && !callee.isExternal() &&
               use.getOperandNumber() < callee.getNumArguments() &&
               unread.contains(callee.getArgument(use.getOperandNumber()));
      });
      if (auto arg = dyn_cast<BlockArgument>(valueHandle)) {
        auto fieldValue = cast<func::FuncOp>(arg.getOwner()->getParentOp());
        ok = ok &&
             llvm::all_of(callSitesOf.lookup(fieldValue),
                          [&](func::CallOp candidateValue) {
                            return candidateValue.getNumOperands() ==
                                       fieldValue.getNumArguments() &&
                                   unread.contains(candidateValue.getOperand(
                                       arg.getArgNumber()));
                          });
      }
      if (!ok) {
        unread.erase(valueHandle);
        changed = true;
      }
    }
  }
  if (unread.empty())
    return;

  for (Value valueHandle : candidates)
    if (unread.contains(valueHandle))
      for (Operation *useValue :
           llvm::make_early_inc_range(valueHandle.getUsers()))
        if (isStore(useValue))
          useValue->erase();
  for (func::FuncOp fieldValue : module.getOps<func::FuncOp>()) {
    if (fieldValue.isExternal())
      continue;
    llvm::BitVector drop(fieldValue.getNumArguments());

    for (unsigned loopIndex = 0; loopIndex < fieldValue.getNumArguments();
         ++loopIndex)
      if (unread.contains(fieldValue.getArgument(loopIndex)) &&
          fieldValue.getArgument(loopIndex).use_empty())
        drop.set(loopIndex);
    if (drop.none())
      continue;
    for (func::CallOp callSite : callSitesOf.lookup(fieldValue))
      for (int loopIndex = static_cast<int>(drop.size()) - 1; loopIndex >= 0;
           --loopIndex)
        if (drop.test(loopIndex))
          callSite->eraseOperand(loopIndex);

    if (auto pb = fieldValue->getAttrOfType<ArrayAttr>(kPortBoundArgsAttr)) {
      SmallVector<int64_t> indexValue;
      for (Attribute arrayValue : pb) {
        int64_t loopIndex = cast<IntegerAttr>(arrayValue).getInt();
        if (loopIndex < 0 || loopIndex >= static_cast<int64_t>(drop.size()) ||
            drop.test(loopIndex))
          continue;
        int64_t droppedBefore = 0;
        for (int64_t innerIndex = 0; innerIndex < loopIndex; ++innerIndex)
          droppedBefore += drop.test(innerIndex);
        indexValue.push_back(loopIndex - droppedBefore);
      }
      fieldValue->setAttr(kPortBoundArgsAttr,
                          buildPoint.getI64ArrayAttr(indexValue));
    }
    (void)fieldValue.eraseArguments(drop);
  }
  SmallVector<Attribute> dead;
  if (auto prev = module->getAttrOfType<ArrayAttr>("hls.dead_memrefs"))
    dead.assign(prev.begin(), prev.end());
  for (const LocalBank &lb : localBanks) {
    Value &bank = *lb.bank;
    unsigned loopIndex = lb.index;
    if (!bank || !unread.contains(bank))
      continue;
    auto localAlloca = bank.getDefiningOp<memref::AllocaOp>();
    if (!localAlloca || !localAlloca->use_empty())
      continue;
    auto fn = localAlloca->getParentOfType<func::FuncOp>();
    const std::string &name = lb.name;
    dead.push_back(buildPoint.getDictionaryAttr(
        {buildPoint.getNamedAttr("kind", buildPoint.getStringAttr("alloca")),
         buildPoint.getNamedAttr(
             "func", buildPoint.getStringAttr(fn ? fn.getName() : "")),
         buildPoint.getNamedAttr("name", buildPoint.getStringAttr(name)),
         buildPoint.getNamedAttr("loc", localAlloca.getLoc()),
         buildPoint.getNamedAttr("type", TypeAttr::get(localAlloca.getType())),
         buildPoint.getNamedAttr(
             "by", buildPoint.getStringAttr("--memory-banking-bram")),
         buildPoint.getNamedAttr(
             "reason",
             buildPoint.getStringAttr("bank " + std::to_string(loopIndex) +
                                      " of a partitioned array that no access "
                                      "reads (VITIS_NOTES N157)"))}));
    localAlloca->erase();
    bank = Value();
  }
  module->setAttr("hls.dead_memrefs", buildPoint.getArrayAttr(dead));
}

void BankingPlan::bank() {
  guardBlockWrites.clear();
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

  SmallVector<LocalBank> localBanks;
  for (RootWork &resultValue : roots) {
    if (!isa<memref::AllocaOp>(resultValue.op))
      continue;
    std::string name;
    if (auto valueHandle =
            resultValue.op->getAttrOfType<StringAttr>("polygeist.varname"))
      name = valueHandle.getValue().str();
    for (Value site : resultValue.sites)
      for (auto [loopIndex, bank] : llvm::enumerate(banksOf[site]))
        if (bank && bank.getDefiningOp<memref::AllocaOp>())
          localBanks.push_back({&bank, name, static_cast<unsigned>(loopIndex)});
  }

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

  if (dropUnreadBanks())
    dropUnreadBankValues(module, symbols, localBanks);

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

/// VITIS_NOTES N180: a partitioned local array passed to a kept callee whose
/// parameter declares a smaller first dimension (cgeist: a
/// memref.reinterpret_cast of the alloca to the parameter's shape, offset 0,
/// the same trailing dimensions) keeps its partition across the call. An
/// array used only through such casts of one shape becomes an array of that
/// shape (the rows past it are unreachable: kernel w9r23p_w1, 24 of 25
/// rows). Otherwise the callee's parameter takes the array's shape and the
/// call passes the array itself, when every call site of that parameter
/// passes such a cast of an array of one type and the callee only loads and
/// stores through the parameter (the linear layout of the shared rows is the
/// same, so every access keeps its address). Key
/// tool.hls.partitioning.reshaped_callee_parameters (off: one kernel, no
/// corpus design; OPEN_ISSUES).
static bool isRowReshape(memref::ReinterpretCastOp cast, MemRefType from) {
  MemRefType to = cast.getType();
  if (!from.hasStaticShape() || !to.hasStaticShape() ||
      !from.getLayout().isIdentity() || from.getRank() != to.getRank() ||
      from.getRank() < 2 || to.getShape()[0] >= from.getShape()[0] ||
      from.getShape().drop_front() != to.getShape().drop_front() ||
      from.getElementType() != to.getElementType())
    return false;
  if (cast.getStaticOffsets().size() != 1 || cast.getStaticOffsets()[0] != 0)
    return false;
  int64_t stride = 1;
  SmallVector<int64_t> strides(to.getRank());
  for (int64_t dimensionIndex = to.getRank() - 1; dimensionIndex >= 0;
       --dimensionIndex) {
    strides[dimensionIndex] = stride;
    stride *= to.getShape()[dimensionIndex];
  }
  return cast.getStaticStrides() == ArrayRef<int64_t>(strides);
}

static void shrinkReshapedArrays(ModuleOp module) {
  SmallVector<memref::AllocaOp> allocas;
  module.walk([&](memref::AllocaOp arrayValue) {
    if (arrayValue->hasAttr("hls.array_partition"))
      allocas.push_back(arrayValue);
  });
  for (memref::AllocaOp arrayValue : allocas) {
    MemRefType shape;
    bool ok = !arrayValue->use_empty();
    for (Operation *useValue : arrayValue->getUsers()) {
      auto cast = dyn_cast<memref::ReinterpretCastOp>(useValue);
      if (!cast || !isRowReshape(cast, arrayValue.getType()) ||
          (shape && cast.getType() != shape)) {
        ok = false;
        break;
      }
      shape = cast.getType();
    }
    if (!ok || !shape)
      continue;
    OpBuilder buildPoint(arrayValue);
    auto smaller =
        buildPoint.create<memref::AllocaOp>(arrayValue.getLoc(), shape);
    smaller->setAttrs(arrayValue->getAttrs());
    for (Operation *useValue :
         llvm::make_early_inc_range(arrayValue->getUsers())) {
      useValue->getResult(0).replaceAllUsesWith(smaller.getResult());
      useValue->erase();
    }
    arrayValue.erase();
  }
}

static void widenReshapedCalleeParameters(ModuleOp module) {
  if (!circt::hlsest::Config::get()
           .tool.hls.partitioning.reshapedCalleeParameters)
    return;
  shrinkReshapedArrays(module);
  SymbolTable symbols(module);

  auto reshapedRoot = [](Value operand) -> memref::AllocaOp {
    auto cast = operand.getDefiningOp<memref::ReinterpretCastOp>();
    if (!cast)
      return {};
    auto root = cast.getSource().getDefiningOp<memref::AllocaOp>();
    if (!root || !root->hasAttr("hls.array_partition") ||
        !isRowReshape(cast, root.getType()))
      return {};
    return root;
  };
  for (func::FuncOp callee : module.getOps<func::FuncOp>()) {
    if (callee.isExternal() || callee.isPublic())
      continue;
    std::optional<SymbolTable::UseRange> symbolUses =
        callee.getSymbolUses(module);
    if (!symbolUses)
      continue;
    SmallVector<func::CallOp> calls;
    bool onlyCalls = true;
    for (const SymbolTable::SymbolUse &useValue : *symbolUses) {
      auto callSite = dyn_cast<func::CallOp>(useValue.getUser());
      if (!callSite) {
        onlyCalls = false;
        break;
      }
      calls.push_back(callSite);
    }
    if (!onlyCalls || calls.empty())
      continue;
    for (unsigned loopIndex = 0; loopIndex < callee.getNumArguments();
         ++loopIndex) {
      BlockArgument arg = callee.getArgument(loopIndex);
      MemRefType wide;
      bool ok = true;
      for (func::CallOp callSite : calls) {
        memref::AllocaOp root = reshapedRoot(callSite.getOperand(loopIndex));
        if (!root || (wide && root.getType() != wide)) {
          ok = false;
          break;
        }
        wide = root.getType();
      }
      if (!ok || !wide)
        continue;
      if (!llvm::all_of(arg.getUsers(), [&](Operation *useValue) {
            if (auto ld = dyn_cast<affine::AffineLoadOp>(useValue))
              return ld.getMemRef() == arg;
            if (auto st = dyn_cast<affine::AffineStoreOp>(useValue))
              return st.getMemRef() == arg;
            if (auto ld = dyn_cast<memref::LoadOp>(useValue))
              return ld.getMemRef() == arg;
            if (auto st = dyn_cast<memref::StoreOp>(useValue))
              return st.getMemRef() == arg;
            return false;
          }))
        continue;
      arg.setType(wide);
      SmallVector<Type> inputs(callee.getArgumentTypes());
      inputs[loopIndex] = wide;
      callee.setType(FunctionType::get(module.getContext(), inputs,
                                       callee.getResultTypes()));
      for (func::CallOp callSite : calls) {
        auto cast = callSite.getOperand(loopIndex)
                        .getDefiningOp<memref::ReinterpretCastOp>();
        callSite->setOperand(loopIndex, cast.getSource());
        if (cast->use_empty())
          cast->erase();
      }
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

    if (hc.middleEnd.forwardBeforeBanking)
      (void)hls_analysis::forwardPartitionedStores(getOperation());
    widenReshapedCalleeParameters(getOperation());
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
