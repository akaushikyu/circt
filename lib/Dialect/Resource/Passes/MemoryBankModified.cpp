//===- MemoryBankModified.cpp - bank the memories of an HLS kernel --------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// `--memory-banking-bram`: split every array that Vitis HLS partitions into
// one memref per bank and rewrite its accesses (td=off ground truth).
//
// Which arrays, and how (PartitionLayout.h, VITIS_NOTES.md N17, N21, N24): a
// storage root (a memref.alloca, or a memref.global with every
// memref.get_global of it) is partitioned by the merge of its own
// `hls.array_partition` pragma and the pragmas of every callee parameter it
// is passed to, transitively (N17 (b): `[HLS 214-248] Applying
// array_partition to '<caller array>'`). Entries on different dimensions
// combine, `dim = 0` is every dimension, the larger factor wins on one
// dimension, a factor beyond the extent is a complete partition.
//
// Callees. A parameter receives the partition of the arrays passed to it, so
// it becomes one parameter per bank and every call passes the banks. A callee
// whose calls pass arrays of different partitions is cloned per argument
// partition (`<callee>_form<N>`), as Vitis clones per argument form (N14 R4,
// N24 (g)); the walk goes top-down from the functions no call reaches, whose
// parameters (the interface ports) are never split.
//
// An array that reaches an op the banking cannot rewrite (a view, a cast, a
// function without a body, a memref stored as a value or returned) or a
// parameter of another shape stays one memory, with a warning.
//
//===----------------------------------------------------------------------===//

#include "circt/Dialect/Resource/Config/ConfigUtils.h"
#include "circt/Support/LLVM.h"
#include "circt/Transforms/Passes.h"
#include "circt/Dialect/Resource/Interfaces/MemoryDS.h"
#include "circt/Dialect/Resource/HLS/HLSOps.h"
#include "circt/Dialect/Resource/Passes/CallInstances.h"
#include "llvm/ADT/StringSet.h"
#include "circt/Dialect/Resource/Passes/IterationPrivateBanks.h"
#include "circt/Dialect/Resource/Passes/PreBankForwarding.h"
#include "circt/Dialect/Resource/Passes/MemrefBankClassification.h"
#include "circt/Dialect/Resource/Passes/ConstantIndex.h"
#include "circt/Dialect/Resource/Passes/PartitionLayout.h"
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
#include "llvm/ADT/SetVector.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/Support/FormatVariadic.h"
#include "llvm/Support/MathExtras.h"

#include <circt/Dialect/Resource/Interfaces/MemoryOpInterface.h.inc>

#include <map>
#include <numeric>
#include <set>
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

//===----------------------------------------------------------------------===//
// Which banks an access can touch
//===----------------------------------------------------------------------===//

// Bank-index constness through a stepped loop counter. An operand that is the
// induction variable of `affine.for %i = lb to ub step s` only ever takes the
// values lb + s*t, so `(d0 + c) mod f` is a constant whenever s is a multiple
// of f, even though the expression is not constant in d0. The access maps keep
// the IV as their operand (the offset `idx floordiv f` must see the real
// value); only the *decision* "constant bank or rotating" is made on the
// substituted form. This is the same rewrite `infer-vitis-split-array`
// applies in makeLinearIndex(), so both passes agree on which accesses rotate
// once loop normalization is not in the pipeline. Loops with step 1 are left
// alone: substituting lb + t cannot make a residue constant.
static std::optional<int64_t>
constantBankThroughInductionVars(AffineMap accessMap, ArrayRef<Value> operands,
                                 const DimPartition &p) {
  unsigned nDims = accessMap.getNumDims();
  unsigned nSyms = accessMap.getNumSymbols();
  MLIRContext *ctx = accessMap.getContext();
  SmallVector<AffineExpr, 4> dimRepl;
  bool any = false;
  for (unsigned i = 0; i < nDims; ++i) {
    AffineExpr d = getAffineDimExpr(i, ctx);
    Value v = operands[i];
    if (affine::isAffineForInductionVar(v)) {
      affine::AffineForOp owner = affine::getForInductionVarOwner(v);
      if (owner.hasConstantLowerBound() && owner.getStepAsInt() != 1) {
        d = d * owner.getStepAsInt() + owner.getConstantLowerBound();
        any = true;
      }
    }
    dimRepl.push_back(d);
  }
  if (!any)
    return std::nullopt;
  AffineExpr idx = accessMap.getResult(p.dim).replaceDims(dimRepl);
  AffineExpr bank = bankAndOffset(idx, p).first;
  if (auto c = dyn_cast<AffineConstantExpr>(
          simplifyAffineExpr(bank, nDims, nSyms)))
    return c.getValue();
  return std::nullopt;
}

// The value range [lo, hi] of an affine index expression whose dimensions
// are affine.for induction variables with constant bounds; nullopt when a
// term is not bounded that way (a symbol, another value, a non-constant
// divisor).
using IndexRange = std::pair<int64_t, int64_t>;
static std::optional<IndexRange> rangeOf(AffineExpr e,
                                         ArrayRef<Value> operands,
                                         unsigned nDims) {
  if (auto c = dyn_cast<AffineConstantExpr>(e))
    return IndexRange{c.getValue(), c.getValue()};
  if (auto d = dyn_cast<AffineDimExpr>(e)) {
    Value v = operands[d.getPosition()];
    if (!affine::isAffineForInductionVar(v))
      return std::nullopt;
    affine::AffineForOp owner = affine::getForInductionVarOwner(v);
    if (!owner.hasConstantBounds())
      return std::nullopt;
    int64_t lb = owner.getConstantLowerBound();
    int64_t ub = owner.getConstantUpperBound();
    int64_t step = owner.getStepAsInt();
    if (ub <= lb || step <= 0)
      return std::nullopt; // no iteration: leave the access alone
    return IndexRange{lb, lb + ((ub - 1 - lb) / step) * step};
  }
  auto bin = dyn_cast<AffineBinaryOpExpr>(e);
  if (!bin)
    return std::nullopt; // a symbol
  std::optional<IndexRange> l = rangeOf(bin.getLHS(), operands, nDims);
  if (!l)
    return std::nullopt;
  auto rc = dyn_cast<AffineConstantExpr>(bin.getRHS());
  switch (e.getKind()) {
  case AffineExprKind::Add: {
    std::optional<IndexRange> r = rangeOf(bin.getRHS(), operands, nDims);
    if (!r)
      return std::nullopt;
    return IndexRange{l->first + r->first, l->second + r->second};
  }
  case AffineExprKind::Mul: {
    if (!rc)
      return std::nullopt;
    int64_t a = l->first * rc.getValue(), b = l->second * rc.getValue();
    return IndexRange{std::min(a, b), std::max(a, b)};
  }
  case AffineExprKind::FloorDiv: {
    if (!rc || rc.getValue() <= 0)
      return std::nullopt;
    return IndexRange{llvm::divideFloorSigned(l->first, rc.getValue()),
                      llvm::divideFloorSigned(l->second, rc.getValue())};
  }
  case AffineExprKind::Mod: {
    if (!rc || rc.getValue() <= 0)
      return std::nullopt;
    int64_t m = rc.getValue();
    if (llvm::divideFloorSigned(l->first, m) !=
        llvm::divideFloorSigned(l->second, m))
      return IndexRange{0, m - 1};
    return IndexRange{llvm::mod(l->first, m), llvm::mod(l->second, m)};
  }
  default:
    return std::nullopt; // ceildiv: not produced by the access maps here
  }
}

// Bank-index constness through the iteration range: a block-partitioned
// dimension whose index stays inside one block over every iteration of the
// enclosing loops (`buf[i + 64]`, i < 64, block depth 64) touches one bank,
// though its bank expression `(i + 64) floordiv 64` is not constant in i.
// Vitis resolves such a store to its one bank (gnnbuilder gcn/gin/pna/sage
// qm9 `global_pooling_buffer`, 1 BRAM_18K per bank; kernels w9r10fx_fx_blk /
// fx_blkl; the W9r10 review's D2). Cyclic dimensions are unaffected: a
// rotating index covers several residues unless it is constant.
static std::optional<int64_t>
constantBankThroughRanges(AffineMap accessMap, ArrayRef<Value> operands,
                          const DimPartition &p) {
  if (p.kind != PartitionSpec::Block ||
      !circt::hlsest::Config::get()
           .tool.hls.partitioning.blockBankFromLoopRange)
    return std::nullopt;
  std::optional<IndexRange> r = rangeOf(accessMap.getResult(p.dim), operands,
                                        accessMap.getNumDims());
  if (!r || r->first < 0 || r->second >= p.extent)
    return std::nullopt; // out of the array: leave it to the general path
  int64_t lo = r->first / p.depth, hi = r->second / p.depth;
  if (lo != hi)
    return std::nullopt;
  return lo;
}

// Which banks one access can touch: per split dimension either a constant
// bank or a rotating one; the candidates are every combination of the
// rotating dimensions, in row-major order.
struct BankChoice {
  SmallVector<std::optional<int64_t>> constBank; // per layout dim
  SmallVector<unsigned> rotating;                // layout dim indices
  // Per rotating dimension, the banks the index can reach (first, count):
  // empty means every bank of the dimension. A block-partitioned index
  // whose value range covers fewer blocks (VITIS_NOTES N175).
  SmallVector<std::pair<int64_t, int64_t>, 2> reach;

  int64_t firstBank(const BankLayout &l, unsigned i) const {
    return reach.empty() ? 0 : reach[i].first;
  }
  int64_t bankCount(const BankLayout &l, unsigned i) const {
    return reach.empty() ? l.dims[rotating[i]].factor : reach[i].second;
  }
  int64_t numCandidates(const BankLayout &l) const {
    int64_t n = 1;
    for (unsigned i = 0; i < rotating.size(); ++i)
      n *= bankCount(l, i);
    return n;
  }
  // The rotating dimensions' bank digits of candidate `k`.
  SmallVector<int64_t> digits(const BankLayout &l, int64_t k) const {
    SmallVector<int64_t> out(rotating.size());
    for (int64_t i = static_cast<int64_t>(rotating.size()) - 1; i >= 0; --i) {
      int64_t f = bankCount(l, i);
      out[i] = firstBank(l, i) + k % f;
      k /= f;
    }
    return out;
  }
  // The value of the linear run-time bank index (the rotating digits in
  // row-major order over the full factors) of candidate `k`.
  int64_t rotValue(const BankLayout &l, int64_t k) const {
    SmallVector<int64_t> dig = digits(l, k);
    int64_t v = 0;
    for (unsigned i = 0; i < rotating.size(); ++i)
      v = v * l.dims[rotating[i]].factor + dig[i];
    return v;
  }
  // The bank (linear index) of candidate `k`.
  int64_t bank(const BankLayout &l, int64_t k) const {
    SmallVector<int64_t> dig = digits(l, k);
    int64_t b = 0;
    unsigned r = 0;
    for (unsigned j = 0; j < l.dims.size(); ++j) {
      int64_t v = constBank[j] ? *constBank[j] : dig[r++];
      b += v * l.strides[j];
    }
    return b;
  }
};

//===----------------------------------------------------------------------===//
// Access rewriting
//===----------------------------------------------------------------------===//

// Canonical (map, operands) of an affine access: composed, constants folded
// (after --auto-pipeline-unroll the first unrolled iteration indexes with an
// SSA constant; also an index cast of one and the counter of a single-trip
// loop, ConstantIndex.h), simplified.
static AffineMap canonicalAccess(AffineMap accessMap,
                                 SmallVectorImpl<Value> &operands) {
  affine::fullyComposeAffineMapAndOperands(&accessMap, &operands);
  affine::canonicalizeMapAndOperands(&accessMap, &operands);
  accessMap = foldConstantIndexOperands(accessMap, operands);
  affine::canonicalizeMapAndOperands(&accessMap, &operands);
  return simplifyAffineMap(accessMap);
}

struct AffineBanking {
  AffineMap bankedMap;               // split dims -> intra-bank offset
  BankChoice choice;
  SmallVector<AffineExpr> rotExprs;  // bank expression per rotating dim
};

static std::optional<std::pair<int64_t, int64_t>>
banksFromRange(Value idx, const DimPartition &p);
static std::optional<std::pair<int64_t, int64_t>>
affineBanksFromRange(AffineExpr e, ArrayRef<Value> operands, unsigned nDims,
                     const DimPartition &p);

static AffineBanking resolveAffine(AffineMap accessMap,
                                   ArrayRef<Value> operands,
                                   const BankLayout &l) {
  unsigned nDims = accessMap.getNumDims();
  unsigned nSyms = accessMap.getNumSymbols();
  AffineBanking ab;
  SmallVector<AffineExpr, 4> results(accessMap.getResults().begin(),
                                     accessMap.getResults().end());
  for (unsigned j = 0; j < l.dims.size(); ++j) {
    const DimPartition &p = l.dims[j];
    auto [bankExpr, offsetExpr] = bankAndOffset(accessMap.getResult(p.dim), p);
    AffineExpr simp = simplifyAffineExpr(bankExpr, nDims, nSyms);
    results[p.dim] = offsetExpr;
    std::optional<int64_t> c;
    if (auto ce = dyn_cast<AffineConstantExpr>(simp))
      c = ce.getValue();
    else
      c = constantBankThroughInductionVars(accessMap, operands, p);
    if (!c)
      c = constantBankThroughRanges(accessMap, operands, p);
    // The value range of the index's operands (VITIS_NOTES N175).
    std::optional<std::pair<int64_t, int64_t>> reach;
    if (!c) {
      reach = affineBanksFromRange(accessMap.getResult(p.dim), operands,
                                   nDims, p);
      if (reach && reach->second == 1)
        c = reach->first;
    }
    ab.choice.constBank.push_back(c);
    if (!c) {
      ab.choice.rotating.push_back(j);
      ab.rotExprs.push_back(simp);
      ab.choice.reach.push_back(reach ? *reach
                                      : std::make_pair(int64_t(0), p.factor));
    }
  }
  // Every rotating dimension reaches all its banks: no reach record.
  if (llvm::all_of(llvm::zip(ab.choice.rotating, ab.choice.reach),
                   [&](auto rr) {
                     auto [r, range] = rr;
                     return range.first == 0 && range.second == l.dims[r].factor;
                   }))
    ab.choice.reach.clear();
  ab.bankedMap =
      AffineMap::get(nDims, nSyms, results, accessMap.getContext());
  return ab;
}

// The linear index over the rotating dimensions (candidate number).
static AffineMap rotatingIndexMap(const AffineBanking &ab, const BankLayout &l,
                                  unsigned nDims, unsigned nSyms) {
  AffineExpr e = ab.rotExprs[0];
  for (unsigned i = 1; i < ab.rotExprs.size(); ++i)
    e = e * l.dims[ab.choice.rotating[i]].factor + ab.rotExprs[i];
  if (ab.rotExprs.size() > 1)
    e = simplifyAffineExpr(e, nDims, nSyms);
  return AffineMap::get(nDims, nSyms, e);
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
/// operand an unknown integer (a loop's upper bound is not used: a store at `row[i][k]` with i in [1, 8) still reaches bank 0 in
/// Vitis, vishnu lab3 row_ptr_A_local); the index is evaluated over one
/// power-of-two period of every operand and taken modulo that period (the
/// known low bits), residues outside the dimension are unreachable. nullopt (every candidate) when the period space is large or
/// no value is in range. Key tool.hls.partitioning.reachable_store_banks.
static std::optional<SmallVector<int64_t>>
reachableCandidates(AffineMap accessMap, ArrayRef<Value> operands,
                    const AffineBanking &ab, const BankLayout &l) {
  constexpr int64_t kMaxPoints = 1 << 14;
  unsigned nDims = accessMap.getNumDims();
  unsigned nSyms = accessMap.getNumSymbols();
  MLIRContext *ctx = accessMap.getContext();
  SmallVector<AffineExpr> idxExprs;
  int64_t extent = 1;
  for (unsigned r : ab.choice.rotating) {
    const DimPartition &p = l.dims[r];
    idxExprs.push_back(accessMap.getResult(p.dim));
    extent = std::max(extent, p.extent);
  }
  // Known low bits survive only +, * and a power-of-two mod: a division
  // shifts higher, unenumerated bits into the index (`j floordiv 2` with j in
  // [0, 128) reaches every bank of a 64-bank dimension, but one period of j
  // reaches only half of them), so such an index may reach every candidate
  // (W9 round 15 review, kernel ob_fdiv_aff).
  bool lowBitsKnown = true;
  for (AffineExpr e : idxExprs)
    e.walk([&](AffineExpr x) {
      auto bin = dyn_cast<AffineBinaryOpExpr>(x);
      if (!bin)
        return;
      if (x.getKind() == AffineExprKind::FloorDiv ||
          x.getKind() == AffineExprKind::CeilDiv)
        lowBitsKnown = false;
      if (x.getKind() == AffineExprKind::Mod) {
        auto c = dyn_cast<AffineConstantExpr>(bin.getRHS());
        if (!c || c.getValue() <= 0 || !llvm::isPowerOf2_64(c.getValue()))
          lowBitsKnown = false;
      }
    });
  if (!lowBitsKnown)
    return std::nullopt;
  // Operands the rotating indices use (dims, then symbols).
  SmallVector<unsigned> usedDims, usedSyms;
  {
    llvm::SmallSetVector<unsigned, 4> d, sy;
    for (AffineExpr e : idxExprs)
      e.walk([&](AffineExpr x) {
        if (auto de = dyn_cast<AffineDimExpr>(x))
          d.insert(de.getPosition());
        else if (auto se = dyn_cast<AffineSymbolExpr>(x))
          sy.insert(se.getPosition());
      });
    usedDims.assign(d.begin(), d.end());
    usedSyms.assign(sy.begin(), sy.end());
  }
  SmallVector<int64_t> counterLb, counterStep;
  for (unsigned d : usedDims) {
    int64_t lb = 0, step = 1;
    if (affine::isAffineForInductionVar(operands[d])) {
      affine::AffineForOp owner = affine::getForInductionVarOwner(operands[d]);
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
  for (unsigned i = 0; i < nUsed; ++i) {
    points *= period;
    if (points > kMaxPoints)
      return std::nullopt;
  }
  std::set<int64_t> hit;
  SmallVector<int64_t> t(nUsed, 0);
  for (int64_t pt = 0; pt < points; ++pt) {
    SmallVector<AffineExpr> dimRepl, symRepl;
    for (unsigned i = 0; i < nDims; ++i)
      dimRepl.push_back(getAffineDimExpr(i, ctx));
    for (unsigned i = 0; i < nSyms; ++i)
      symRepl.push_back(getAffineSymbolExpr(i, ctx));
    // An affine.for counter is lb + step * t (its trailing zero bits are
    // known); any other operand is an unknown integer t.
    for (unsigned u = 0; u < usedDims.size(); ++u)
      dimRepl[usedDims[u]] =
          getAffineConstantExpr(counterLb[u] + counterStep[u] * t[u], ctx);
    for (unsigned u = 0; u < usedSyms.size(); ++u)
      symRepl[usedSyms[u]] =
          getAffineConstantExpr(t[usedDims.size() + u], ctx);
    int64_t k = 0;
    bool inRange = true;
    for (unsigned r = 0; r < idxExprs.size() && inRange; ++r) {
      const DimPartition &p = l.dims[ab.choice.rotating[r]];
      auto c = dyn_cast<AffineConstantExpr>(simplifyAffineExpr(
          idxExprs[r].replaceDimsAndSymbols(dimRepl, symRepl), nDims, nSyms));
      if (!c)
        return std::nullopt;
      // Known low bits only: the index modulo the period (at least the
      // extent); a residue past the extent is out of the array.
      int64_t idx = llvm::mod(c.getValue(), period);
      if (idx >= p.extent) {
        inRange = false;
        break;
      }
      int64_t bank = bankAndOffset(idx, p).first;
      if (bank < 0 || bank >= p.factor)
        return std::nullopt;
      k = k * p.factor + bank;
    }
    if (inRange)
      hit.insert(k);
    for (unsigned u = 0; u < nUsed; ++u) {
      if (++t[u] < period)
        break;
      t[u] = 0;
    }
  }
  if (hit.empty())
    return std::nullopt;
  return SmallVector<int64_t>(hit.begin(), hit.end());
}

static bool reachableStoreBanks() {
  return circt::hlsest::Config::get()
      .tool.hls.partitioning.reachableStoreBanks;
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
                                const BankLayout &l) {
  bool allCyclic = llvm::all_of(choice.rotating, [&](unsigned r) {
    return l.dims[r].kind == PartitionSpec::Cyclic && l.dims[r].factor > 1;
  });
  if (!choice.rotating.empty() && allCyclic)
    load->setAttr("hls.runtime_bank", UnitAttr::get(load->getContext()));
}

static void markRotatingRead(Operation *load, bool addressVaries) {
  load->setAttr("hls.rotating_bank", UnitAttr::get(load->getContext()));
  if (addressVaries)
    load->setAttr("hls.bank_address_varies",
                  UnitAttr::get(load->getContext()));
}

static void rewriteAffineLoad(affine::AffineLoadOp loadOp,
                              ArrayRef<Value> banks, const BankLayout &l) {
  OpBuilder b(loadOp);
  Location loc = loadOp.getLoc();
  SmallVector<Value, 4> operands(loadOp.getMapOperands().begin(),
                                 loadOp.getMapOperands().end());
  AffineMap accessMap = canonicalAccess(loadOp.getAffineMap(), operands);
  AffineBanking ab = resolveAffine(accessMap, operands, l);
  if (ab.choice.rotating.empty()) {
    // Constant bank: one direct load.
    auto nl = affine::AffineLoadOp::create(
        b, loc, banks[ab.choice.bank(l, 0)], ab.bankedMap, operands);
    loadOp.replaceAllUsesWith(nl.getResult());
    loadOp.erase();
    return;
  }
  // Rotating bank: read every candidate bank at the shared offset and select
  // on the (runtime) bank index.
  Value bankIdx = affine::AffineApplyOp::create(
      b, loc,
      rotatingIndexMap(ab, l, accessMap.getNumDims(),
                       accessMap.getNumSymbols()),
      operands);
  int64_t n = ab.choice.numCandidates(l);
  SmallVector<Value, 8> vals;
  for (int64_t k = 0; k < n; ++k) {
    vals.push_back(affine::AffineLoadOp::create(
        b, loc, banks[ab.choice.bank(l, k)], ab.bankedMap, operands));
    markRuntimeBankRead(vals.back().getDefiningOp(), ab.choice, l);
  }
  Value result = vals[n - 1];
  for (int64_t k = n - 1; k-- > 0;) {
    Value kc =
        arith::ConstantIndexOp::create(b, loc, ab.choice.rotValue(l, k));
    Value eq = arith::CmpIOp::create(b, loc, arith::CmpIPredicate::eq,
                                     bankIdx, kc);
    result = arith::SelectOp::create(b, loc, eq, vals[k], result);
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
    if (Attribute a = from->getAttr(name))
      to->setAttr(name, a);
}

/// Returns the store_enables left out because their bank is unreachable.
static unsigned rewriteAffineStore(affine::AffineStoreOp storeOp,
                                   ArrayRef<Value> banks,
                                   const BankLayout &l) {
  OpBuilder b(storeOp);
  Location loc = storeOp.getLoc();
  Value val = storeOp.getValueToStore();
  SmallVector<Value, 4> operands(storeOp.getMapOperands().begin(),
                                 storeOp.getMapOperands().end());
  AffineMap accessMap = canonicalAccess(storeOp.getAffineMap(), operands);
  AffineBanking ab = resolveAffine(accessMap, operands, l);
  if (ab.choice.rotating.empty()) {
    auto ns = affine::AffineStoreOp::create(
        b, loc, val, banks[ab.choice.bank(l, 0)], ab.bankedMap, operands);
    copyForwardingCounters(storeOp, ns);
    storeOp.erase();
    return 0;
  }
  // Rotating bank: one affine.store_enable per candidate bank, guarded by
  // "bank expression == its digit" on every rotating dimension. Staying affine
  // keeps the write visible to MemoryDependenceAnalysis (loop-carried deps for
  // accumulation); it lowers to the flat store_enable later.
  unsigned nDims = accessMap.getNumDims();
  unsigned nSyms = accessMap.getNumSymbols();
  int64_t n = ab.choice.numCandidates(l);
  SmallVector<int64_t> candidates;
  std::optional<SmallVector<int64_t>> reach;
  if (reachableStoreBanks())
    reach = reachableCandidates(accessMap, operands, ab, l);
  // reachableCandidates numbers a candidate by its linear bank digits over
  // the full factors (rotValue); keep the candidates of this access's
  // (possibly range-narrowed) set that it reaches.
  for (int64_t k = 0; k < n; ++k)
    if (!reach || llvm::is_contained(*reach, ab.choice.rotValue(l, k)))
      candidates.push_back(k);
  for (int64_t k : candidates) {
    SmallVector<int64_t> dig = ab.choice.digits(l, k);
    SmallVector<AffineExpr> constraints;
    SmallVector<bool> eqFlags;
    for (unsigned i = 0; i < dig.size(); ++i) {
      constraints.push_back(ab.rotExprs[i] - dig[i]);
      eqFlags.push_back(true);
    }
    IntegerSet cond = IntegerSet::get(nDims, nSyms, constraints, eqFlags);
    if (compoundAssignTwoStores(storeOp)) {
      auto extra = AffineStoreEnableOp::create(
          b, loc, val, banks[ab.choice.bank(l, k)], /*mapOperands=*/operands,
          /*setOperands=*/operands, ab.bankedMap, cond);
      extra->setAttr("hls.compound_assign_store", b.getUnitAttr());
    }
    auto se = AffineStoreEnableOp::create(
        b, loc, val, banks[ab.choice.bank(l, k)], /*mapOperands=*/operands,
        /*setOperands=*/operands, ab.bankedMap, cond);
    copyForwardingCounters(storeOp, se);
  }
  storeOp.erase();
  return static_cast<unsigned>(n - static_cast<int64_t>(candidates.size()));
}

// A non-affine (memref.load / memref.store) access: the bank of every split
// dimension, constant when its index folds, else computed at run time.
struct MemrefBanking {
  SmallVector<Value, 4> bankedIndices; // split dims -> offset
  BankChoice choice;
  Value rotIdx; // linear index over the rotating dims (null if none)
  SmallVector<Value> rotDigits; // the bank along each rotating dim
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
static std::optional<int64_t> evaluateConstantInt(Value v,
                                                  unsigned depth = 0) {
  if (std::optional<int64_t> c = getConstantIntValue(v))
    return c;
  Operation *def = v.getDefiningOp();
  if (!def || depth >= 16 || def->getNumResults() != 1 ||
      def->getNumRegions() != 0 || !isMemoryEffectFree(def) ||
      !v.getType().isIntOrIndex())
    return std::nullopt;
  SmallVector<Attribute, 4> operands;
  for (Value o : def->getOperands()) {
    if (!o.getType().isIntOrIndex())
      return std::nullopt;
    std::optional<int64_t> c = evaluateConstantInt(o, depth + 1);
    if (!c)
      return std::nullopt;
    operands.push_back(IntegerAttr::get(o.getType(), *c));
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
static std::optional<int64_t> constantIndexOf(Value idx) {
  if (std::optional<int64_t> c = getConstantIndexValue(idx))
    return c;
  return evaluateConstantInt(idx);
}

static std::pair<Value, int64_t> residueBase(Value v, int64_t factor,
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
static std::optional<int64_t> inductionResidueBank(Value idx,
                                                   const DimPartition &p) {
  if (!circt::hlsest::Config::get()
           .tool.hls.partitioning.inductionResidueBanks ||
      p.kind != PartitionSpec::Cyclic || p.factor <= 1)
    return std::nullopt;
  auto [base, c] = residueBase(idx, p.factor, 0);
  auto arg = dyn_cast<BlockArgument>(base);
  if (!arg)
    return std::nullopt;
  auto loop = dyn_cast_or_null<scf::ForOp>(arg.getOwner()->getParentOp());
  if (!loop || loop.getInductionVar() != arg)
    return std::nullopt;
  std::optional<int64_t> lb = getConstantIntValue(loop.getLowerBound());
  std::optional<int64_t> step = getConstantIntValue(loop.getStep());
  if (!lb || !step || *step <= 0 || *step % p.factor != 0)
    return std::nullopt;
  int64_t bank = (*lb + c) % p.factor;
  return bank < 0 ? bank + p.factor : bank;
}

/// The residue of a memref index modulo a power-of-two cyclic factor when
/// its low bits are known, as LLVM's known bits give Vitis: `(n & ~7) + k`
/// with k a constant has residue k mod 8 whatever n is (VITIS_NOTES N115
/// control kernel w9r15p_rc_fix: each read's bank is the constant k % 8,
/// 15 copies per bank). Through casts, add / sub, and with a mask whose low
/// bits are zero (residue 0) or all ones (the operand's residue), a multiply
/// or shift that makes a multiple of the factor. Key
/// tool.hls.partitioning.known_residue_banks.
static std::optional<int64_t> knownResidue(Value v, int64_t factor,
                                           unsigned depth = 0) {
  if (std::optional<int64_t> c = constantIndexOf(v))
    return llvm::mod(*c, factor);
  Operation *def = v.getDefiningOp();
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
    std::optional<int64_t> a = knownResidue(def->getOperand(0), factor,
                                            depth + 1);
    std::optional<int64_t> b =
        a ? knownResidue(def->getOperand(1), factor, depth + 1)
          : std::nullopt;
    if (!a || !b)
      return std::nullopt;
    return llvm::mod(isa<arith::AddIOp>(def) ? *a + *b : *a - *b, factor);
  }
  if (auto andOp = dyn_cast<arith::AndIOp>(def)) {
    for (unsigned i = 0; i < 2; ++i) {
      std::optional<int64_t> m = constantIndexOf(def->getOperand(i));
      if (!m)
        continue;
      uint64_t mask = static_cast<uint64_t>(*m) & low;
      if (mask == 0)
        return 0;
      if (mask == low)
        return knownResidue(def->getOperand(1 - i), factor, depth + 1);
    }
    return std::nullopt;
  }
  if (isa<arith::MulIOp>(def)) {
    for (unsigned i = 0; i < 2; ++i)
      if (std::optional<int64_t> m = constantIndexOf(def->getOperand(i));
          m && *m % factor == 0)
        return 0;
    return std::nullopt;
  }
  if (auto shl = dyn_cast<arith::ShLIOp>(def)) {
    std::optional<int64_t> k = constantIndexOf(shl.getRhs());
    if (k && *k >= static_cast<int64_t>(bits) && *k < 63)
      return 0;
    return std::nullopt;
  }
  return std::nullopt;
}

/// The bank of a non-constant memref index along `p` when it is known
/// anyway: an scf.for counter stepping by a multiple of the factor
/// (inductionResidueBank), or known low bits (knownResidue).
static std::optional<int64_t> knownBank(Value idx, const DimPartition &p) {
  if (std::optional<int64_t> bank = inductionResidueBank(idx, p))
    return bank;
  if (p.kind == PartitionSpec::Cyclic && p.factor > 1 &&
      llvm::isPowerOf2_64(static_cast<uint64_t>(p.factor)) &&
      circt::hlsest::Config::get().tool.hls.partitioning.knownResidueBanks)
    return knownResidue(idx, p.factor);
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
memrefIndexRangeImpl(Value v, unsigned depth, RangeMemo &memo);

/// memrefIndexRange of `v`, memoized in `memo` (one query walks a DAG of
/// operations that share operands: without it the walk is exponential in
/// its depth; hlsyn fdtd-2d-large / symm-opt-medium timed out).
///
/// Ranges are kept in the signed reading of the value's integer type, as
/// MLIR's constants are: an N-bit result whose computed range leaves
/// [-2^(N-1), 2^(N-1) - 1] wraps, so its range becomes that whole interval
/// (review W9r23 D1: `u8 t = in & 15; t += 250` is `addi i8 %t, -6`, values
/// 250..255 and 0..9 once read unsigned).
static unsigned rangeBitWidth(Value x) {
  return x.getType().isIndex() ? 64u : x.getType().getIntOrFloatBitWidth();
}
static std::optional<ValueRange64> signedTypeRange(unsigned n) {
  if (n == 0 || n >= 40)
    return std::nullopt;
  return ValueRange64{-(int64_t(1) << (n - 1)), (int64_t(1) << (n - 1)) - 1};
}
/// The values of an N-bit integer with signed range `r` (nullopt: unknown)
/// read as unsigned (index_castui, extui): a range below zero moves up by
/// 2^N; one that straddles zero covers [0, 2^N - 1] (the interval hull of
/// the two wrapped pieces); an unknown one is [0, 2^N - 1] (review W9r23
/// D2: index_castui of a loaded i8 reaches 0..255 only).
static std::optional<ValueRange64>
unsignedReading(std::optional<ValueRange64> r, unsigned n) {
  if (n >= 40)
    return r && r->first >= 0 ? r : std::nullopt;
  int64_t span = int64_t(1) << n;
  if (!r || (r->first < 0 && r->second >= 0))
    return ValueRange64{0, span - 1};
  if (r->second < 0)
    return ValueRange64{r->first + span, r->second + span};
  return r;
}
static std::optional<ValueRange64> memrefIndexRange(Value v, unsigned depth,
                                                    RangeMemo &memo) {
  auto it = memo.find(v);
  if (it != memo.end())
    return it->second;
  std::optional<ValueRange64> r = memrefIndexRangeImpl(v, depth, memo);
  if (r && v.getType().isSignlessInteger())
    if (std::optional<ValueRange64> t = signedTypeRange(rangeBitWidth(v));
        t && (r->first < t->first || r->second > t->second))
      r = t;
  memo[v] = r;
  return r;
}
static std::optional<ValueRange64> memrefIndexRange(Value v) {
  RangeMemo memo;
  return memrefIndexRange(v, 0, memo);
}

static std::optional<ValueRange64>
memrefIndexRangeImpl(Value v, unsigned depth, RangeMemo &memo) {
  constexpr int64_t kLimit = int64_t(1) << 40;
  auto bounded = [&](ValueRange64 r) -> std::optional<ValueRange64> {
    if (r.first < -kLimit || r.second > kLimit || r.first > r.second)
      return std::nullopt;
    return r;
  };
  if (std::optional<int64_t> c = getConstantIntValue(v))
    return bounded({*c, *c});
  if (depth > 16)
    return std::nullopt;
  // Loop counters are not bounded by their trip counts: Vitis' bank
  // reach does not use them (a store at `row[i][k]` with i in [1, 8) still
  // reaches bank 0 of a complete partition: vishnu lab3 row_ptr_A_local /
  // col_ptr_B_local, W9r23-impl); the block-partition case of N86 is
  // tool.hls.partitioning.block_bank_from_loop_range's.
  Operation *def = v.getDefiningOp();
  if (!def)
    return std::nullopt;
  auto widthOf = rangeBitWidth;
  if (isa<arith::ExtUIOp, arith::IndexCastUIOp>(def)) {
    Value in = def->getOperand(0);
    unsigned n = widthOf(in);
    if (n >= 40 && isa<arith::ExtUIOp>(def))
      return memrefIndexRange(in, depth + 1, memo);
    return unsignedReading(memrefIndexRange(in, depth + 1, memo), n);
  }
  if (isa<arith::ExtSIOp, arith::IndexCastOp>(def)) {
    if (auto r = memrefIndexRange(def->getOperand(0), depth + 1, memo))
      return r;
    return signedTypeRange(widthOf(def->getOperand(0)));
  }
  // An affine.apply of constants (an unrolled copy's counter): its value.
  if (auto apply = dyn_cast<affine::AffineApplyOp>(def)) {
    SmallVector<Attribute> operands;
    for (Value o : apply.getMapOperands()) {
      auto r = memrefIndexRange(o, depth + 1, memo);
      if (!r || r->first != r->second)
        return std::nullopt;
      operands.push_back(IntegerAttr::get(o.getType(), r->first));
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
    auto r = memrefIndexRange(tr.getIn(), depth + 1, memo);
    unsigned n = widthOf(tr.getResult());
    if (r && n < 40 && r->first >= -(int64_t(1) << (n - 1)) &&
        r->second < (int64_t(1) << (n - 1)))
      return r;
    return signedTypeRange(n);
  }
  if (isa<arith::AndIOp>(def)) {
    for (unsigned i = 0; i < 2; ++i)
      if (std::optional<int64_t> m = constantIndexOf(def->getOperand(i));
          m && *m >= 0) {
        auto r = memrefIndexRange(def->getOperand(1 - i), depth + 1, memo);
        if (r && r->first >= 0)
          return bounded({0, std::min(r->second, *m)});
        return bounded({0, *m});
      }
    return std::nullopt;
  }
  // A signed remainder of a value that may be negative may be negative: no
  // bound (Vitis keeps every row of xf_remap's buf_bram[WIN_ROW + 1], read
  // at `(y + m - 3) % WIN_ROW`: 9 banks, held-out remap BILINEAR).
  if (isa<arith::RemSIOp>(def)) {
    std::optional<int64_t> c = constantIndexOf(def->getOperand(1));
    if (!c || *c <= 0)
      return std::nullopt;
    auto r = memrefIndexRange(def->getOperand(0), depth + 1, memo);
    if (r && r->first >= 0)
      return bounded({0, std::min(r->second, *c - 1)});
    return std::nullopt;
  }
  if (isa<arith::RemUIOp>(def)) {
    std::optional<int64_t> c = constantIndexOf(def->getOperand(1));
    if (!c || *c <= 0)
      return std::nullopt;
    auto r = memrefIndexRange(def->getOperand(0), depth + 1, memo);
    if (r && r->first >= 0 && r->second < *c)
      return r;
    return bounded({0, *c - 1});
  }
  if (isa<arith::ShRUIOp, arith::ShRSIOp>(def)) {
    std::optional<int64_t> k = constantIndexOf(def->getOperand(1));
    auto r = memrefIndexRange(def->getOperand(0), depth + 1, memo);
    if (!k || *k < 0 || *k >= 62 || !r || r->first < 0)
      return std::nullopt;
    return bounded({r->first >> *k, r->second >> *k});
  }
  if (isa<arith::AddIOp, arith::SubIOp, arith::MulIOp>(def)) {
    auto a = memrefIndexRange(def->getOperand(0), depth + 1, memo);
    if (!a)
      return std::nullopt;
    auto c = memrefIndexRange(def->getOperand(1), depth + 1, memo);
    if (!c)
      return std::nullopt;
    if (isa<arith::AddIOp>(def))
      return bounded({a->first + c->first, a->second + c->second});
    if (isa<arith::SubIOp>(def))
      return bounded({a->first - c->second, a->second - c->first});
    int64_t p[4] = {a->first * c->first, a->first * c->second,
                    a->second * c->first, a->second * c->second};
    return bounded(
        {*std::min_element(p, p + 4), *std::max_element(p, p + 4)});
  }
  return std::nullopt;
}

/// The banks a memref index of a block or complete partition can reach,
/// from its value range (memrefIndexRange) clipped to the dimension (an
/// index outside it is undefined behaviour; VITIS_NOTES N175): (first bank,
/// number of banks); nullopt when the range is unknown or reaches every
/// bank. Key tool.hls.partitioning.banks_from_value_range.
static std::optional<std::pair<int64_t, int64_t>>
banksFromRange(Value idx, const DimPartition &p) {
  bool complete = p.kind == PartitionSpec::Complete ||
                  (p.kind == PartitionSpec::Cyclic && p.factor == p.extent);
  if ((p.kind != PartitionSpec::Block && !complete) || p.factor <= 1 ||
      p.depth <= 0 ||
      !circt::hlsest::Config::get().tool.hls.partitioning.banksFromValueRange)
    return std::nullopt;
  std::optional<ValueRange64> r = memrefIndexRange(idx);
  if (!r)
    return std::nullopt;
  int64_t first = std::max<int64_t>(r->first, 0);
  int64_t last = std::min<int64_t>(r->second, p.extent - 1);
  if (first > last)
    return std::nullopt;
  int64_t lo = first / p.depth, hi = last / p.depth;
  if (lo == 0 && hi >= p.factor - 1)
    return std::nullopt;
  return std::make_pair(lo, std::min(hi, p.factor - 1) - lo + 1);
}

/// banksFromRange for an affine index expression: its dimensions and
/// symbols take the value ranges of their operands (memrefIndexRange).
static std::optional<std::pair<int64_t, int64_t>>
affineBanksFromRange(AffineExpr e, ArrayRef<Value> operands, unsigned nDims,
                     const DimPartition &p) {
  bool complete = p.kind == PartitionSpec::Complete ||
                  (p.kind == PartitionSpec::Cyclic && p.factor == p.extent);
  if ((p.kind != PartitionSpec::Block && !complete) || p.factor <= 1 ||
      !circt::hlsest::Config::get().tool.hls.partitioning.banksFromValueRange)
    return std::nullopt;
  RangeMemo memo;
  std::function<std::optional<ValueRange64>(AffineExpr)> eval =
      [&](AffineExpr x) -> std::optional<ValueRange64> {
    if (auto c = dyn_cast<AffineConstantExpr>(x))
      return ValueRange64{c.getValue(), c.getValue()};
    if (auto d = dyn_cast<AffineDimExpr>(x))
      return memrefIndexRange(operands[d.getPosition()], 0, memo);
    if (auto sy = dyn_cast<AffineSymbolExpr>(x))
      return memrefIndexRange(operands[nDims + sy.getPosition()], 0, memo);
    auto bin = dyn_cast<AffineBinaryOpExpr>(x);
    if (!bin)
      return std::nullopt;
    auto rc = dyn_cast<AffineConstantExpr>(bin.getRHS());
    // An affine mod by a constant is in [0, m - 1] whatever its operand.
    if (x.getKind() == AffineExprKind::Mod && rc && rc.getValue() > 0 &&
        !eval(bin.getLHS()))
      return ValueRange64{0, rc.getValue() - 1};
    auto l = eval(bin.getLHS());
    if (!l)
      return std::nullopt;
    switch (x.getKind()) {
    case AffineExprKind::Add: {
      auto r = eval(bin.getRHS());
      if (!r)
        return std::nullopt;
      return ValueRange64{l->first + r->first, l->second + r->second};
    }
    case AffineExprKind::Mul: {
      if (!rc)
        return std::nullopt;
      int64_t a = l->first * rc.getValue(), b = l->second * rc.getValue();
      return ValueRange64{std::min(a, b), std::max(a, b)};
    }
    case AffineExprKind::FloorDiv:
      if (!rc || rc.getValue() <= 0)
        return std::nullopt;
      return ValueRange64{llvm::divideFloorSigned(l->first, rc.getValue()),
                          llvm::divideFloorSigned(l->second, rc.getValue())};
    case AffineExprKind::Mod: {
      if (!rc || rc.getValue() <= 0)
        return std::nullopt;
      int64_t m = rc.getValue();
      if (llvm::divideFloorSigned(l->first, m) !=
          llvm::divideFloorSigned(l->second, m))
        return ValueRange64{0, m - 1};
      return ValueRange64{llvm::mod(l->first, m), llvm::mod(l->second, m)};
    }
    default:
      return std::nullopt;
    }
  };
  std::optional<ValueRange64> r = eval(e);
  constexpr int64_t kLimit = int64_t(1) << 40;
  if (!r || r->first < -kLimit || r->second > kLimit)
    return std::nullopt;
  int64_t first = std::max<int64_t>(r->first, 0);
  int64_t last = std::min<int64_t>(r->second, p.extent - 1);
  if (first > last)
    return std::nullopt;
  int64_t lo = first / p.depth, hi = last / p.depth;
  if (lo == 0 && hi >= p.factor - 1)
    return std::nullopt;
  return std::make_pair(lo, std::min(hi, p.factor - 1) - lo + 1);
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
  OpBuilder b(&entry, entry.begin());
  auto c = arith::ConstantIndexOp::create(b, fn.getLoc(), 0);
  c->setAttr("hls.bank_offset_zero", b.getUnitAttr());
  return c.getResult();
}

/// `useRanges`: narrow block / complete dimensions by the index's value
/// range (off for the members of a steered group, whose candidate set is
/// the group's).
static MemrefBanking resolveMemref(OpBuilder &b, Location loc,
                                   ValueRange indices, const BankLayout &l,
                                   bool useRanges = true) {
  MemrefBanking mb;
  mb.bankedIndices.assign(indices.begin(), indices.end());
  SmallVector<Value> rot;
  SmallVector<std::pair<int64_t, int64_t>, 2> rangeReach;
  bool anyNarrowReach = false;
  for (unsigned j = 0; j < l.dims.size(); ++j) {
    const DimPartition &p = l.dims[j];
    Value idx = indices[p.dim];
    std::optional<int64_t> constIdx = constantIndexOf(idx);
    // A constant index outside the dimension (`loc[t][h - 1]` in the arm of
    // `h == 0 ? ... : ...` that never runs for the unrolled h = 0 copy) names
    // no bank: it is resolved at run time like any other index (before, the
    // bank -1 indexed out of the bank list).
    if (constIdx) {
      auto [bank, off] = bankAndOffset(*constIdx, p);
      if (bank >= 0 && bank < p.factor) {
        mb.choice.constBank.push_back(bank);
        mb.bankedIndices[p.dim] = arith::ConstantIndexOp::create(b, loc, off);
        continue;
      }
    }
    // A known bank whose offset is computed at run time (N103 copies; known
    // low bits, N115's control).
    if (std::optional<int64_t> bank = knownBank(idx, p)) {
      mb.choice.constBank.push_back(*bank);
      Value d = arith::ConstantIndexOp::create(b, loc, p.factor);
      mb.bankedIndices[p.dim] =
          arith::DivUIOp::create(b, loc, idx, d).getResult();
      continue;
    }
    // A block-partitioned index whose value range stays inside one block
    // addresses that bank; one that spans fewer blocks than the factor
    // reaches only those (VITIS_NOTES N175: kernels w9r23p_h1 / h2 4 banks
    // read, h4 two blocks per lane; control h3, an unbounded index, every
    // bank).
    std::optional<std::pair<int64_t, int64_t>> reach =
        useRanges ? banksFromRange(idx, p) : std::nullopt;
    if (reach && reach->second == 1) {
      mb.choice.constBank.push_back(reach->first);
      Value d = arith::ConstantIndexOp::create(b, loc, p.depth);
      mb.bankedIndices[p.dim] =
          arith::RemUIOp::create(b, loc, idx, d).getResult();
      continue;
    }
    // memref indices are non-negative index values: unsigned div / rem.
    bool bankIsDiv = p.kind == PartitionSpec::Block;
    int64_t divisor = bankIsDiv ? p.depth : p.factor;
    Value d = arith::ConstantIndexOp::create(b, loc, divisor);
    Value bankV = bankIsDiv ? arith::DivUIOp::create(b, loc, idx, d).getResult()
                            : arith::RemUIOp::create(b, loc, idx, d).getResult();
    // A completely partitioned dimension: every bank is read at offset 0,
    // whatever the access (VITIS_NOTES N172: per-bank reads of different
    // accesses then match).
    bool completeDim = p.kind == PartitionSpec::Complete ||
                       (!bankIsDiv && p.factor == p.extent);
    Value offV =
        completeDim && circt::hlsest::Config::get()
                           .tool.hls.partitioning.sharedAddressBankReads
            ? sharedZeroIndex(b.getInsertionBlock()->getParentOp())
        : bankIsDiv ? arith::RemUIOp::create(b, loc, idx, d).getResult()
                    : arith::DivUIOp::create(b, loc, idx, d).getResult();
    mb.bankedIndices[p.dim] = offV;
    mb.choice.constBank.push_back(std::nullopt);
    mb.choice.rotating.push_back(j);
    rangeReach.push_back(reach ? *reach : std::make_pair(int64_t(0), p.factor));
    anyNarrowReach |= reach.has_value();
    rot.push_back(bankV);
  }
  if (anyNarrowReach)
    mb.choice.reach = std::move(rangeReach);
  mb.rotDigits = rot;
  if (!rot.empty()) {
    mb.rotIdx = rot[0];
    for (unsigned i = 1; i < rot.size(); ++i) {
      Value f = arith::ConstantIndexOp::create(
          b, loc, l.dims[mb.choice.rotating[i]].factor);
      Value mul = arith::MulIOp::create(b, loc, mb.rotIdx, f);
      mb.rotIdx = arith::AddIOp::create(b, loc, mul, rot[i]);
    }
  }
  return mb;
}

static void rewriteMemrefLoad(memref::LoadOp loadOp, ArrayRef<Value> banks,
                              const BankLayout &l) {
  OpBuilder b(loadOp);
  Location loc = loadOp.getLoc();
  MemrefBanking mb = resolveMemref(b, loc, loadOp.getIndices(), l);
  if (mb.choice.rotating.empty()) {
    auto nl = memref::LoadOp::create(b, loc, banks[mb.choice.bank(l, 0)],
                                     mb.bankedIndices);
    loadOp.replaceAllUsesWith(nl.getResult());
    loadOp.erase();
    return;
  }
  int64_t n = mb.choice.numCandidates(l);
  SmallVector<Value, 8> vals;
  for (int64_t k = 0; k < n; ++k) {
    vals.push_back(memref::LoadOp::create(b, loc, banks[mb.choice.bank(l, k)],
                                          mb.bankedIndices));
    markRuntimeBankRead(vals.back().getDefiningOp(), mb.choice, l);
  }
  Value result = vals[n - 1];
  for (int64_t k = n - 1; k-- > 0;) {
    Value kc = arith::ConstantIndexOp::create(b, loc,
                                              mb.choice.rotValue(l, k));
    Value eq = arith::CmpIOp::create(b, loc, arith::CmpIPredicate::eq,
                                     mb.rotIdx, kc);
    result = arith::SelectOp::create(b, loc, eq, vals[k], result);
  }
  loadOp.replaceAllUsesWith(result);
  loadOp.erase();
}

//===----------------------------------------------------------------------===//
// Loads that together read each bank once (steered loads)
//===----------------------------------------------------------------------===//
//
// Unrolled copies of one runtime-indexed read, `A[(base + 4*i + u) & 4095]`
// for u = 0..3 with A cyclic-partitioned by 4, address a different bank each
// whatever `base` is: their indices differ by constants that are distinct
// modulo the factor. Vitis proves that and reads every bank once per
// iteration, steering the addresses and results through sparse muxes
// (VITIS_NOTES N27; kernel w7rv_rt4: 4 banks `ram_1p`, II 1, four
// sparsemux_9_2_32; w7rv_rt2, two copies: 8 BRAM too). Rewriting each
// copy on its own reads every candidate bank per copy, which makes each bank
// look read four times per cycle (3 RAM_1WNR copies per bank, 24 BRAM against
// Vitis' 8). So such a group is rewritten as one load per bank, at the offset
// of the copy that addresses it, and each copy selects its bank's value.

// `v` as `base + c (mod factor)`: peels constant additions, index casts,
// truncations that keep log2(factor) bits and `and` masks whose low
// log2(factor) bits are ones (the last two only for a power-of-two factor),
// remainders by a multiple of the factor (`x rem M` differs from x by a
// multiple of M, signed or not), and the sign fix of a signed remainder
// that C's `%` / affine `mod` lower to, `select(r < 0, r + M, r)`: both arms
// have one base and offsets congruent modulo the factor (MultiHeadSelfAttention1
// opt3 / opt4 `v341`, `(v50 + 2 v48) % 16` with a cyclic factor 2: the bank is
// the unrolled v50, one read per bank as in Vitis' memory table; OPEN_ISSUES
// O121).
// Whether `v` is a multiple of `factor` whatever its operands: a constant
// multiple, a product with a constant multiple, or a left shift by a
// constant whose power of two is a multiple.
template <typename ConstOf>
static bool isMultipleOf(Value v, int64_t factor, ConstOf constOf,
                         unsigned depth = 0) {
  if (factor <= 1)
    return true;
  if (auto c = constOf(v))
    return *c % factor == 0;
  Operation *def = v.getDefiningOp();
  if (!def || depth > 4)
    return false;
  if (isa<arith::IndexCastOp, arith::IndexCastUIOp, arith::ExtSIOp,
          arith::ExtUIOp>(def))
    return isMultipleOf(def->getOperand(0), factor, constOf, depth + 1);
  if (isa<arith::MulIOp>(def))
    return isMultipleOf(def->getOperand(0), factor, constOf, depth + 1) ||
           isMultipleOf(def->getOperand(1), factor, constOf, depth + 1);
  if (auto shl = dyn_cast<arith::ShLIOp>(def)) {
    std::optional<int64_t> k = constOf(shl.getRhs());
    if (k && *k >= 0 && *k < 62 && ((int64_t(1) << *k) % factor) == 0)
      return true;
    return isMultipleOf(shl.getLhs(), factor, constOf, depth + 1);
  }
  if (isa<arith::AddIOp, arith::SubIOp>(def))
    return isMultipleOf(def->getOperand(0), factor, constOf, depth + 1) &&
           isMultipleOf(def->getOperand(1), factor, constOf, depth + 1);
  return false;
}

static std::pair<Value, int64_t> residueBase(Value v, int64_t factor,
                                             unsigned depth) {
  bool pow2 = llvm::isPowerOf2_64(static_cast<uint64_t>(factor));
  unsigned bits = llvm::Log2_64(static_cast<uint64_t>(factor));
  auto constOf = [](Value x) -> std::optional<int64_t> {
    if (auto c = getConstantIndexValue(x))
      return c;
    if (auto cast = x.getDefiningOp<arith::IndexCastOp>())
      x = cast.getIn();
    if (auto apply = x.getDefiningOp<affine::AffineApplyOp>()) {
      SmallVector<Attribute> attrs;
      for (Value o : apply.getMapOperands()) {
        std::optional<int64_t> c = getConstantIndexValue(o);
        if (!c)
          return std::nullopt;
        attrs.push_back(IntegerAttr::get(o.getType(), *c));
      }
      SmallVector<Attribute> res;
      if (succeeded(apply.getAffineMap().constantFold(attrs, res)) &&
          res.size() == 1)
        if (auto ia = dyn_cast<IntegerAttr>(res.front()))
          return ia.getInt();
    }
    return std::nullopt;
  };
  int64_t c = 0;
  for (unsigned guard = 0; guard < 32; ++guard) {
    Operation *def = v.getDefiningOp();
    if (!def)
      break;
    if (isa<arith::IndexCastOp, arith::IndexCastUIOp, arith::ExtSIOp,
            arith::ExtUIOp>(def)) {
      v = def->getOperand(0);
      continue;
    }
    if (auto tr = dyn_cast<arith::TruncIOp>(def)) {
      if (!pow2 || tr.getType().getIntOrFloatBitWidth() < bits)
        break;
      v = tr.getIn();
      continue;
    }
    if (isa<arith::RemSIOp, arith::RemUIOp>(def)) {
      std::optional<int64_t> m = constOf(def->getOperand(1));
      if (!m || *m <= 0 || *m % factor != 0)
        break;
      v = def->getOperand(0);
      continue;
    }
    if (auto sel = dyn_cast<arith::SelectOp>(def)) {
      if (depth >= 4)
        break;
      auto [bt, ct] = residueBase(sel.getTrueValue(), factor, depth + 1);
      auto [bf, cf] = residueBase(sel.getFalseValue(), factor, depth + 1);
      if (bt != bf || ((ct - cf) % factor) != 0)
        break;
      return {bt, c + cf};
    }
    if (isa<arith::AddIOp, arith::SubIOp>(def) &&
        !constOf(def->getOperand(0)) && !constOf(def->getOperand(1))) {
      // `x + q*M` / `x - q*M` with M a multiple of the factor: the floored
      // form of C's `%` that cgeist emits for an affine-raised index,
      // `x + (-M) * floordiv(x, M)` (W9 round 12 review, kernels
      // w9r12rv_o121_cyc4 / cyc3: `A[(j + 4*i + 2) % 2048]`, cyclic 4 / 3).
      // A constant operand is peeled below instead, so that the copies of
      // one unrolled read keep one runtime base.
      Value lhs = def->getOperand(0), rhs = def->getOperand(1);
      if (isMultipleOf(rhs, factor, constOf)) {
        v = lhs;
        continue;
      }
      if (isa<arith::AddIOp>(def) && isMultipleOf(lhs, factor, constOf)) {
        v = rhs;
        continue;
      }
      break;
    }
    if (auto sub = dyn_cast<arith::SubIOp>(def)) {
      std::optional<int64_t> k = constOf(sub.getRhs());
      if (!k)
        break;
      c -= *k;
      v = sub.getLhs();
      continue;
    }
    if (isa<arith::AndIOp, arith::AddIOp>(def)) {
      Value lhs = def->getOperand(0), rhs = def->getOperand(1);
      std::optional<int64_t> k = constOf(rhs);
      if (!k) {
        k = constOf(lhs);
        std::swap(lhs, rhs);
      }
      if (!k)
        break;
      if (isa<arith::AndIOp>(def)) {
        uint64_t low = (uint64_t(1) << bits) - 1;
        if (!pow2 || (static_cast<uint64_t>(*k) & low) != low)
          break;
      } else {
        c += *k;
      }
      v = lhs;
      continue;
    }
    break;
  }
  return {v, c};
}

// Move the side-effect-free ops `v` depends on, in this block after
// `before`, to just before it. False (nothing moved) when one has effects or
// regions.
static bool hoistBefore(Value v, Operation *before, bool dryRun,
                        unsigned depth = 0) {
  Operation *def = v.getDefiningOp();
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

/// tool.hls.partitioning.steer_through_guards (VITIS_NOTES N155): the
/// unrolled copies of a window read each under its own guard (`if (l + k in
/// range) s += X[l + k - 2]`) still form one steered group, as Vitis reads
/// every bank once per load state whatever the guards (kernel w9r21p_g1).
static bool steerThroughGuards() {
  return circt::hlsest::Config::get()
      .tool.hls.partitioning.steerThroughGuards;
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
  // Only a guard around this one access of its array: the unrolled copies of
  // a guarded tap (N155). Several accesses under one if (the arms of an
  // if / else-if, VITIS_NOTES N124, kernel w9r16p_ie_part) keep their own
  // groups, one per block.
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
  // The group's loads are issued together before its first member: never
  // across a call or a store to the array in the block (W9r9 review D3,
  // lit w9r9fix_n74_reload_after_call: a reload after a call that writes the
  // array stays in its arm).
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
static bool steerBefore(Operation *a, Operation *b) {
  Operation *aa = guardAnchor(a), *ab = guardAnchor(b);
  if (aa != ab)
    return aa->isBeforeInBlock(ab);
  if (a->getBlock() == b->getBlock())
    return a->isBeforeInBlock(b);
  // Different arms or nesting levels under one anchor: pre-order position.
  bool seenA = false, aFirst = false;
  aa->walk<WalkOrder::PreOrder>([&](Operation *op) {
    if (op == a && !seenA) {
      seenA = true;
      aFirst = true;
      return WalkResult::interrupt();
    }
    if (op == b)
      return WalkResult::interrupt();
    return WalkResult::advance();
  });
  return aFirst;
}

/// hoistBefore that also moves side-effect-free ops nested in the if arms
/// of `before`'s block (the index of a guarded copy, steerThroughGuards).
static bool hoistBeforeThroughGuards(Value v, Operation *before, bool dryRun,
                                     unsigned depth = 0) {
  Operation *def = v.getDefiningOp();
  if (!def)
    return true; // a block argument: defined above
  if (def == before)
    return false;
  Block *block = before->getBlock();
  if (def->getBlock() == block)
    return hoistBefore(v, before, dryRun, depth);
  // The op of `block` that holds def, through if arms only.
  Operation *anchor = def->getParentOp();
  bool throughIfs = true;
  while (anchor && anchor->getBlock() != block) {
    throughIfs &= isSteerableGuard(anchor);
    anchor = anchor->getParentOp();
  }
  if (!anchor)
    return true; // defined outside the block: it dominates it
  if (!steerThroughGuards() || !throughIfs || !isSteerableGuard(anchor))
    return false;
  if (depth > 64 || def->getNumRegions() || !isMemoryEffectFree(def))
    return false;
  for (Value o : def->getOperands())
    if (!hoistBeforeThroughGuards(o, before, dryRun, depth + 1))
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
static std::optional<std::pair<int64_t, int64_t>> indexRange(Value v,
                                                             unsigned depth =
                                                                 0) {
  if (depth > 16)
    return std::nullopt;
  if (std::optional<int64_t> c = getConstantIntValue(v))
    return std::make_pair(*c, *c);
  if (affine::isAffineForInductionVar(v)) {
    affine::AffineForOp f = affine::getForInductionVarOwner(v);
    if (!f.hasConstantBounds() || f.getStepAsInt() <= 0)
      return std::nullopt;
    int64_t lb = f.getConstantLowerBound(), ub = f.getConstantUpperBound();
    if (ub <= lb)
      return std::nullopt;
    int64_t step = f.getStepAsInt();
    return std::make_pair(lb, lb + (ub - 1 - lb) / step * step);
  }
  Operation *def = v.getDefiningOp();
  if (!def)
    return std::nullopt;
  if (isa<arith::IndexCastOp, arith::IndexCastUIOp, arith::ExtSIOp,
          arith::ExtUIOp>(def))
    return indexRange(def->getOperand(0), depth + 1);
  auto combine = [](std::pair<int64_t, int64_t> a,
                    std::pair<int64_t, int64_t> b, char op)
      -> std::optional<std::pair<int64_t, int64_t>> {
    if (op == '+')
      return std::make_pair(a.first + b.first, a.second + b.second);
    if (op == '-')
      return std::make_pair(a.first - b.second, a.second - b.first);
    int64_t c[4] = {a.first * b.first, a.first * b.second,
                    a.second * b.first, a.second * b.second};
    return std::make_pair(*std::min_element(c, c + 4),
                          *std::max_element(c, c + 4));
  };
  if (isa<arith::AddIOp, arith::SubIOp, arith::MulIOp>(def)) {
    auto a = indexRange(def->getOperand(0), depth + 1);
    auto b = indexRange(def->getOperand(1), depth + 1);
    if (!a || !b)
      return std::nullopt;
    return combine(*a, *b,
                   isa<arith::AddIOp>(def)   ? '+'
                   : isa<arith::SubIOp>(def) ? '-'
                                             : '*');
  }
  if (auto apply = dyn_cast<affine::AffineApplyOp>(def)) {
    AffineMap map = apply.getAffineMap();
    SmallVector<std::optional<std::pair<int64_t, int64_t>>> ops;
    for (Value o : apply.getMapOperands())
      ops.push_back(indexRange(o, depth + 1));
    std::function<std::optional<std::pair<int64_t, int64_t>>(AffineExpr)>
        eval = [&](AffineExpr e)
        -> std::optional<std::pair<int64_t, int64_t>> {
      if (auto c = dyn_cast<AffineConstantExpr>(e))
        return std::make_pair(c.getValue(), c.getValue());
      if (auto d = dyn_cast<AffineDimExpr>(e))
        return ops[d.getPosition()];
      if (auto s = dyn_cast<AffineSymbolExpr>(e))
        return ops[map.getNumDims() + s.getPosition()];
      auto bin = dyn_cast<AffineBinaryOpExpr>(e);
      if (!bin)
        return std::nullopt;
      auto l = eval(bin.getLHS()), r = eval(bin.getRHS());
      if (!l || !r)
        return std::nullopt;
      if (e.getKind() == AffineExprKind::Add)
        return combine(*l, *r, '+');
      if (e.getKind() == AffineExprKind::Mul)
        return combine(*l, *r, '*');
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
  return circt::hlsest::Config::get()
      .tool.hls.partitioning.steerWindowGroups;
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
static std::optional<int64_t> constantBankOf(Value idx, const DimPartition &p) {
  std::optional<int64_t> c = constantIndexOf(idx);
  if (!c)
    return knownBank(idx, p);
  int64_t bank = bankAndOffset(*c, p).first;
  if (bank < 0 || bank >= p.factor)
    return std::nullopt;
  return bank;
}

/// Residue sets modulo a partition factor (possibleResidues).
using ResidueSet = std::set<int64_t>;

static ResidueSet allResidues(int64_t f) {
  ResidueSet out;
  for (int64_t v = 0; v < f; ++v)
    out.insert(v);
  return out;
}

/// {a + b} / {a * b} over two residue sets, modulo f.
static ResidueSet combineResidues(const ResidueSet &x, const ResidueSet &y,
                                  int64_t f, bool multiply) {
  ResidueSet out;
  for (int64_t a : x)
    for (int64_t b : y)
      out.insert(llvm::mod(multiply ? a * b : a + b, f));
  return out;
}

static ResidueSet mapResidues(const ResidueSet &x, int64_t f,
                              llvm::function_ref<int64_t(int64_t)> fn) {
  ResidueSet out;
  for (int64_t a : x)
    out.insert(llvm::mod(fn(a), f));
  return out;
}

using ResidueMemo = llvm::DenseMap<Value, ResidueSet>;
static ResidueSet residuesOf(Value v, int64_t f, unsigned depth,
                             ResidueMemo &memo);

/// The residues of an affine expression whose dims / symbols take the given
/// residue sets: + and * combine the sets; a modulo by a multiple of f keeps
/// its operand's residues; a division, or a modulo by anything else, is an
/// unknown integer (every residue).
static ResidueSet affineExprResidues(AffineExpr e, ArrayRef<ResidueSet> dims,
                                     ArrayRef<ResidueSet> syms, int64_t f) {
  if (auto c = dyn_cast<AffineConstantExpr>(e))
    return {llvm::mod(c.getValue(), f)};
  if (auto d = dyn_cast<AffineDimExpr>(e))
    return dims[d.getPosition()];
  if (auto sy = dyn_cast<AffineSymbolExpr>(e))
    return syms[sy.getPosition()];
  auto bin = cast<AffineBinaryOpExpr>(e);
  switch (e.getKind()) {
  case AffineExprKind::Add:
  case AffineExprKind::Mul:
    return combineResidues(affineExprResidues(bin.getLHS(), dims, syms, f),
                           affineExprResidues(bin.getRHS(), dims, syms, f), f,
                           e.getKind() == AffineExprKind::Mul);
  case AffineExprKind::Mod:
    if (auto m = dyn_cast<AffineConstantExpr>(bin.getRHS()))
      if (m.getValue() > 0 && m.getValue() % f == 0)
        return affineExprResidues(bin.getLHS(), dims, syms, f);
    return allResidues(f);
  default:
    return allResidues(f);
  }
}

/// The residues modulo f an index value can take, by known bits: constants;
/// loop counters lb + step * t (affine.for / scf.for with constant lower
/// bound and step); casts; + - * and shifts left by a constant; and / or
/// with a constant mask (f a power of two); a remainder by a multiple of f;
/// select (either value); affine.apply. Anything else (a division, a load,
/// a function argument) is an unknown integer: every residue. Correlations
/// between operands are not tracked, so the set can only grow.
static ResidueSet computeResidues(Value v, int64_t f, unsigned depth,
                                  ResidueMemo &memo);

static ResidueSet residuesOf(Value v, int64_t f, unsigned depth,
                             ResidueMemo &memo) {
  auto it = memo.find(v);
  if (it != memo.end())
    return it->second;
  ResidueSet out = computeResidues(v, f, depth, memo);
  memo[v] = out;
  return out;
}

static ResidueSet computeResidues(Value v, int64_t f, unsigned depth,
                                  ResidueMemo &memo) {
  constexpr unsigned kMaxDepth = 24;
  if (std::optional<int64_t> c = constantIndexOf(v))
    return {llvm::mod(*c, f)};
  if (depth > kMaxDepth)
    return allResidues(f);
  // A counter: lb + step * t.
  auto counter = [&](int64_t lb, int64_t step) {
    ResidueSet out;
    for (int64_t t = 0; t < f; ++t)
      out.insert(llvm::mod(lb + step * t, f));
    return out;
  };
  if (affine::isAffineForInductionVar(v)) {
    affine::AffineForOp owner = affine::getForInductionVarOwner(v);
    if (owner.hasConstantLowerBound())
      return counter(owner.getConstantLowerBound(), owner.getStepAsInt());
    return allResidues(f);
  }
  if (auto arg = dyn_cast<BlockArgument>(v)) {
    if (auto loop = dyn_cast_or_null<scf::ForOp>(arg.getOwner()->getParentOp()))
      if (loop.getInductionVar() == arg) {
        std::optional<int64_t> lb = getConstantIntValue(loop.getLowerBound());
        std::optional<int64_t> st = getConstantIntValue(loop.getStep());
        if (lb && st)
          return counter(*lb, *st);
      }
    return allResidues(f);
  }
  Operation *def = v.getDefiningOp();
  if (!def)
    return allResidues(f);
  const bool pow2 = llvm::isPowerOf2_64(static_cast<uint64_t>(f));
  const unsigned bits = llvm::Log2_64(static_cast<uint64_t>(f));
  auto operand = [&](unsigned i) {
    return residuesOf(def->getOperand(i), f, depth + 1, memo);
  };
  if (isa<arith::IndexCastOp, arith::IndexCastUIOp, arith::ExtSIOp,
          arith::ExtUIOp>(def))
    return operand(0);
  if (auto tr = dyn_cast<arith::TruncIOp>(def)) {
    if (pow2 && tr.getType().getIntOrFloatBitWidth() >= bits)
      return operand(0);
    return allResidues(f);
  }
  if (isa<arith::AddIOp>(def))
    return combineResidues(operand(0), operand(1), f, /*multiply=*/false);
  if (isa<arith::SubIOp>(def))
    return combineResidues(operand(0),
                           mapResidues(operand(1), f,
                                       [](int64_t x) { return -x; }),
                           f, /*multiply=*/false);
  if (isa<arith::MulIOp>(def))
    return combineResidues(operand(0), operand(1), f, /*multiply=*/true);
  if (auto shl = dyn_cast<arith::ShLIOp>(def)) {
    std::optional<int64_t> k = constantIndexOf(shl.getRhs());
    if (!k || *k < 0 || *k > 62)
      return allResidues(f);
    int64_t scale = llvm::mod(int64_t(1) << *k, f);
    return mapResidues(operand(0), f, [&](int64_t x) { return x * scale; });
  }
  if (isa<arith::AndIOp, arith::OrIOp>(def) && pow2) {
    // (x op m) mod 2^b = (x mod 2^b) op (m mod 2^b) in two's complement.
    for (unsigned i = 0; i < 2; ++i)
      if (std::optional<int64_t> m = constantIndexOf(def->getOperand(i))) {
        int64_t low = llvm::mod(*m, f);
        bool isAnd = isa<arith::AndIOp>(def);
        return mapResidues(operand(1 - i), f, [&](int64_t x) {
          return isAnd ? (x & low) : (x | low);
        });
      }
    return allResidues(f);
  }
  if (isa<arith::RemSIOp, arith::RemUIOp>(def)) {
    std::optional<int64_t> m = constantIndexOf(def->getOperand(1));
    if (m && *m > 0 && *m % f == 0)
      return operand(0);
    return allResidues(f);
  }
  if (auto sel = dyn_cast<arith::SelectOp>(def)) {
    ResidueSet out = residuesOf(sel.getTrueValue(), f, depth + 1, memo);
    ResidueSet other = residuesOf(sel.getFalseValue(), f, depth + 1, memo);
    out.insert(other.begin(), other.end());
    return out;
  }
  if (auto apply = dyn_cast<affine::AffineApplyOp>(def)) {
    AffineMap map = apply.getAffineMap();
    if (map.getNumResults() != 1)
      return allResidues(f);
    SmallVector<ResidueSet> dims, syms;
    for (auto [i, o] : llvm::enumerate(apply.getMapOperands()))
      (i < map.getNumDims() ? dims : syms)
          .push_back(residuesOf(o, f, depth + 1, memo));
    return affineExprResidues(map.getResult(0), dims, syms, f);
  }
  return allResidues(f);
}

/// The residues modulo the factor a memref index can take (residuesOf;
/// nullopt for a factor too large to enumerate). W9r16 review: an index
/// through a division (`4 * (n / 2)`, kernel w9r16rv_rs_fd) or a mask
/// (`4 * (n & 1)`, w9r16p_rs_same) keeps the residues of the multiply.
static std::optional<ResidueSet> possibleResidues(Value idx,
                                                  const DimPartition &p) {
  constexpr int64_t kMaxFactor = 256;
  const int64_t f = p.factor;
  if (f <= 1)
    return ResidueSet{0};
  if (f > kMaxFactor)
    return std::nullopt;
  if (std::optional<int64_t> bank = knownBank(idx, p))
    return ResidueSet{*bank};
  ResidueMemo memo;
  return residuesOf(idx, f, 0, memo);
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
                                 const BankLayout &l,
                                 ArrayRef<unsigned> rotating) {
  for (auto [i, r] : llvm::enumerate(rotating)) {
    const DimPartition &p = l.dims[r];
    if (l.bankType && l.bankType.getShape()[p.dim] == 1)
      continue; // a complete partition: offset 0 on every bank
    std::optional<ResidueSet> res =
        possibleResidues(members.front().load.getIndices()[p.dim], p);
    // Unknown residues: assume one in-bank address (N4's count, the common
    // form) rather than the extra copy (W9r16 review: an unknown base
    // over-counted w9r16rv_rs_fd by 16).
    if (!res)
      return false;
    const int64_t off0 = members.front().offsets[i];
    for (int64_t r0 : *res) {
      int64_t rb = llvm::mod(r0 - off0, p.factor);
      std::optional<int64_t> q;
      for (const SteerMember &m : members) {
        int64_t qj = llvm::divideFloorSigned(rb + m.offsets[i], p.factor);
        if (q && *q != qj)
          return true;
        q = qj;
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
                       const BankLayout &l) {
  llvm::sort(members, [](const SteerMember &a, const SteerMember &b) {
    return steerBefore(a.load, b.load);
  });
  // Every copy must see the same constant banks and rotating dimensions as
  // resolveMemref will (the grouping saw the same, this is a guard).
  SmallVector<std::optional<int64_t>> constBanks;
  for (const DimPartition &p : l.dims)
    constBanks.push_back(
        constantBankOf(members.front().load.getIndices()[p.dim], p));
  unsigned numRotating = llvm::count(constBanks, std::nullopt);
  for (const SteerMember &m : members) {
    if (m.offsets.size() != numRotating)
      return false;
    for (auto [j, p] : llvm::enumerate(l.dims))
      if (constantBankOf(m.load.getIndices()[p.dim], p) != constBanks[j])
        return false;
  }
  Operation *first = guardAnchor(members.front().load);
  bool movable = llvm::all_of(members, [&](const SteerMember &m) {
    return llvm::all_of(m.load.getIndices(), [&](Value i) {
      return hoistBeforeThroughGuards(i, first, /*dryRun=*/true);
    });
  });
  if (!movable)
    return false;
  for (const SteerMember &m : members)
    for (Value i : m.load.getIndices())
      hoistBeforeThroughGuards(i, first, /*dryRun=*/false);
  OpBuilder b(first);
  Location loc = first->getLoc();
  // Per copy: its offsets and its (runtime) bank.
  SmallVector<MemrefBanking, 4> mbs;
  for (const SteerMember &m : members)
    mbs.push_back(
        resolveMemref(b, loc, m.load.getIndices(), l, /*useRanges=*/false));
  const BankChoice &choice = mbs.front().choice;
  // A partitioned dimension of extent 1 in the bank (a complete partition)
  // has offset 0 in every copy.
  for (unsigned r : choice.rotating) {
    unsigned pdim = l.dims[r].dim;
    if (l.bankType && l.bankType.getShape()[pdim] == 1) {
      Value zero = arith::ConstantIndexOp::create(b, loc, 0);
      for (MemrefBanking &mb : mbs)
        mb.bankedIndices[pdim] = zero;
    }
  }
  // eq0[i][v]: copy 0's bank digit on rotating dimension i is v.
  SmallVector<SmallVector<Value>> eq0;
  for (auto [i, r] : llvm::enumerate(choice.rotating)) {
    SmallVector<Value> row;
    for (int64_t v = 0; v < l.dims[r].factor; ++v)
      row.push_back(arith::CmpIOp::create(
          b, loc, arith::CmpIPredicate::eq, mbs.front().rotDigits[i],
          arith::ConstantIndexOp::create(b, loc, v)));
    eq0.push_back(std::move(row));
  }
  // hit[j][k]: copy j addresses candidate k. The copies' banks are one
  // runtime bank rotated by their constants: copy j is in the bank with
  // digits d exactly when copy 0 is in the bank with digits d - c_j + c_0
  // (mod f per dimension), so one set of comparisons serves all.
  int64_t n = choice.numCandidates(l);
  llvm::DenseMap<int64_t, Value> conjunctions; // copy 0's candidate -> hit
  auto copy0In = [&](ArrayRef<int64_t> digits) -> Value {
    if (digits.size() == 1)
      return eq0[0][digits[0]];
    int64_t key = 0;
    for (auto [i, d] : llvm::enumerate(digits))
      key = key * l.dims[choice.rotating[i]].factor + d;
    Value &v = conjunctions[key];
    if (!v) {
      v = eq0[0][digits[0]];
      for (size_t i = 1; i < digits.size(); ++i)
        v = arith::AndIOp::create(b, loc, v, eq0[i][digits[i]]);
    }
    return v;
  };
  SmallVector<SmallVector<Value>> hit(members.size());
  for (size_t j = 0; j < members.size(); ++j)
    for (int64_t k = 0; k < n; ++k) {
      SmallVector<int64_t> dig = choice.digits(l, k);
      for (auto [i, r] : llvm::enumerate(choice.rotating)) {
        int64_t f = l.dims[r].factor;
        dig[i] = ((dig[i] - members[j].offsets[i] +
                   members.front().offsets[i]) % f + f) % f;
      }
      hit[j].push_back(copy0In(dig));
    }
  const bool addressVaries =
      !choice.rotating.empty() &&
      steeredAddressVaries(members, l, choice.rotating);
  // N157 (drop_unread_banks): the candidates some copy's index can reach
  // with the values its counters take; the others get no read (a 3 x 3
  // window over rows 0..9 of a 12-row complete dimension reads 10 banks).
  SmallVector<bool> reachable(n, true);
  if (dropUnreadBanks()) {
    constexpr int64_t kMaxEnumerated = 4096;
    std::vector<SmallVector<std::set<int64_t>>> digitSets;
    bool known = true;
    for (const SteerMember &m : members) {
      SmallVector<std::set<int64_t>> perDim;
      for (unsigned r : choice.rotating) {
        const DimPartition &p = l.dims[r];
        auto range = indexRange(m.load.getIndices()[p.dim]);
        if (!range || range->second - range->first >= kMaxEnumerated) {
          known = false;
          break;
        }
        std::set<int64_t> banksHit;
        for (int64_t v = range->first; v <= range->second; ++v)
          if (v >= 0 && v < p.extent)
            banksHit.insert(bankAndOffset(v, p).first);
        perDim.push_back(std::move(banksHit));
      }
      if (!known)
        break;
      digitSets.push_back(std::move(perDim));
    }
    if (known)
      for (int64_t k = 0; k < n; ++k) {
        SmallVector<int64_t> dig = choice.digits(l, k);
        reachable[k] = llvm::any_of(digitSets, [&](const auto &sets) {
          for (auto [i, d] : llvm::enumerate(dig))
            if (!sets[i].count(d))
              return false;
          return true;
        });
      }
    if (llvm::none_of(reachable, [](bool b) { return b; }))
      reachable.assign(n, true);
  }
  SmallVector<Value> bankVals(n);
  for (int64_t k = 0; k < n; ++k) {
    if (!reachable[k])
      continue;
    SmallVector<Value> idx(mbs.back().bankedIndices.begin(),
                           mbs.back().bankedIndices.end());
    for (unsigned d = 0; d < idx.size(); ++d)
      for (size_t j = mbs.size() - 1; j-- > 0;)
        if (mbs[j].bankedIndices[d] != idx[d])
          idx[d] = arith::SelectOp::create(b, loc, hit[j][k],
                                           mbs[j].bankedIndices[d], idx[d]);
    bankVals[k] =
        memref::LoadOp::create(b, loc, banks[choice.bank(l, k)], idx);
    if (!choice.rotating.empty()) {
      markRotatingRead(bankVals[k].getDefiningOp(), addressVaries);
      markRuntimeBankRead(bankVals[k].getDefiningOp(), choice, l);
    }
  }
  SmallVector<Value> results;
  int64_t last = n - 1;
  while (last > 0 && !reachable[last])
    --last;
  for (size_t j = 0; j < members.size(); ++j) {
    Value r = bankVals[last];
    for (int64_t k = last; k-- > 0;)
      if (reachable[k])
        r = arith::SelectOp::create(b, loc, hit[j][k], bankVals[k], r);
    results.push_back(r);
  }
  for (auto [m, r] : llvm::zip(members, results)) {
    m.load.replaceAllUsesWith(r);
    m.load.erase();
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
  auto residues = [&](const T &m) {
    SmallVector<int64_t> r;
    for (auto [c, f] : llvm::zip(offsetsOf(m), factors))
      r.push_back(((c % f) + f) % f);
    return r;
  };
  std::vector<SmallVector<T>> groups;
  std::vector<std::set<SmallVector<int64_t>>> seen;
  if (!steerWindowGroups()) {
    std::set<SmallVector<int64_t>> all;
    for (const T &m : members)
      if (!all.insert(residues(m)).second)
        return {};
    groups.emplace_back(members.begin(), members.end());
    return groups;
  }
  for (const T &m : members) {
    SmallVector<int64_t> r = residues(m);
    size_t g = 0;
    while (g < groups.size() && seen[g].count(r))
      ++g;
    if (g == groups.size()) {
      groups.emplace_back();
      seen.emplace_back();
    }
    groups[g].push_back(m);
    seen[g].insert(r);
  }
  return groups;
}

/// `e` as `base + c` with a constant c (0 when there is none).
static std::pair<AffineExpr, int64_t> splitConstant(AffineExpr e) {
  if (auto add = dyn_cast<AffineBinaryOpExpr>(e);
      add && add.getKind() == AffineExprKind::Add) {
    if (auto c = dyn_cast<AffineConstantExpr>(add.getRHS()))
      return {add.getLHS(), c.getValue()};
    if (auto c = dyn_cast<AffineConstantExpr>(add.getLHS()))
      return {add.getRHS(), c.getValue()};
  }
  return {e, 0};
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
  // A global is also reachable through another get_global of it and through
  // a callee's own get_global (W9r9 review D3, w9r9rev fwd_call.cpp): inside
  // the scope of a global (or of an argument, which may be bound to one), no
  // call may run and no other handle of the global may be used except by
  // loads.
  SmallVector<Value> handles{site};
  // An argument may alias a global a callee writes: also no calls.
  bool isGlobal = isa<BlockArgument>(site);
  if (auto gg = site.getDefiningOp<memref::GetGlobalOp>()) {
    isGlobal = true;
    if (auto fn = gg->getParentOfType<FunctionOpInterface>())
      fn->walk([&](memref::GetGlobalOp other) {
        if (other != gg && other.getNameAttr() == gg.getNameAttr())
          handles.push_back(other.getResult());
      });
  }
  auto onlyLoadsIn = [&](Operation *scope) {
    if (isGlobal && scope
                        ->walk([](CallOpInterface) {
                          return WalkResult::interrupt();
                        })
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
  SmallVector<int64_t> groupSizes; // copies per steered group (N27 / N74)
  unsigned forwardedReloads = 0;   // if-arm reloads forwarded (N74)
  unsigned prunedStoreEnables = 0; // unreachable store banks (O150)
};

static void steerLoadGroups(Value site, ArrayRef<Value> banks,
                            const BankLayout &l, bool affineLoads,
                            SteerStats &stats) {
  if (l.numBanks < 2 || static_cast<int64_t>(banks.size()) != l.numBanks ||
      llvm::any_of(l.dims, [](const DimPartition &p) {
        return p.kind == PartitionSpec::Block;
      }))
    return;
  if (l.dims.size() != 1 && !steerWindowGroups())
    return;
  if (affineLoads && steerWindowGroups())
    stats.forwardedReloads += forwardNestedReloads(site);
  // The factors of the rotating dimensions of a group with these constant
  // banks.
  auto rotatingFactors = [&](ArrayRef<std::optional<int64_t>> constBanks) {
    SmallVector<int64_t> f;
    for (auto [j, p] : llvm::enumerate(l.dims))
      if (!constBanks[j])
        f.push_back(p.factor);
    return f;
  };
  // Unrolled affine.load copies whose partitioned indices are one affine
  // expression of the same operands plus constants (`X[c][ki][j*s + kw]`, j
  // unrolled): read each bank once per residue class, as their memref.load
  // form below.
  if (affineLoads) {
    struct AffineCopy {
      affine::AffineLoadOp load;
      SmallVector<int64_t> offsets;
    };
    struct AffineGroup {
      Block *block;
      // Per partitioned dimension: its constant bank, or the index without
      // its constant (map and operands).
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
        // A load whose bank is known statically is banked directly below.
        SmallVector<Value, 4> operands(ld.getMapOperands());
        AffineMap accessMap = canonicalAccess(ld.getAffineMap(), operands);
        ab = resolveAffine(accessMap, operands, l);
        if (ab.choice.rotating.empty())
          continue;
      }
      AffineGroup key{guardAnchor(ld)->getBlock(), {}, {}, {}, {}};
      SmallVector<int64_t> offsets;
      bool ok = true;
      for (auto [j, p] : llvm::enumerate(l.dims)) {
        // The partitioned index alone, with constant operands and
        // affine.apply chains folded in (an unrolled copy's constant often
        // reaches the map as an operand).
        AffineMap map = ld.getAffineMap().getSubMap({p.dim});
        SmallVector<Value> ops(ld.getMapOperands());
        affine::fullyComposeAffineMapAndOperands(&map, &ops);
        affine::canonicalizeMapAndOperands(&map, &ops);
        AffineExpr e = map.getResult(0);
        if (auto ce = dyn_cast<AffineConstantExpr>(e)) {
          int64_t bank = bankAndOffset(ce.getValue(), p).first;
          if (l.dims.size() == 1 || bank < 0 || bank >= p.factor ||
              !ab.choice.constBank[j]) {
            ok = false; // a constant bank (one dimension: banked below)
            break;
          }
          key.constBanks.push_back(bank);
          key.bases.push_back(AffineMap());
          key.operands.emplace_back();
          continue;
        }
        if (ab.choice.constBank[j]) {
          ok = false; // a constant bank through a stepped counter
          break;
        }
        auto [baseExpr, c] = splitConstant(e);
        key.constBanks.push_back(std::nullopt);
        key.bases.push_back(AffineMap::get(map.getNumDims(),
                                           map.getNumSymbols(), baseExpr,
                                           map.getContext()));
        key.operands.push_back(ops);
        offsets.push_back(c);
      }
      if (!ok)
        continue;
      auto it = llvm::find_if(agroups, [&](const AffineGroup &g) {
        return g.block == key.block && g.constBanks == key.constBanks &&
               g.bases == key.bases && g.operands == key.operands;
      });
      if (it == agroups.end()) {
        agroups.push_back(std::move(key));
        it = std::prev(agroups.end());
      }
      it->members.push_back({ld, std::move(offsets)});
    }
    for (AffineGroup &g : agroups) {
      if (g.members.size() < 2)
        continue;
      std::vector<SmallVector<AffineCopy>> classes =
          residueClassGroups<AffineCopy>(
              g.members,
              [](const AffineCopy &c) -> ArrayRef<int64_t> {
                return c.offsets;
              },
              rotatingFactors(g.constBanks));
      SmallVector<AffineCopy *> steered;
      for (SmallVector<AffineCopy> &cls : classes)
        if (cls.size() >= 2)
          for (AffineCopy &c : g.members)
            if (llvm::any_of(cls, [&](const AffineCopy &x) {
                  return x.load == c.load;
                }))
              steered.push_back(&c);
      if (steered.empty())
        continue;
      // One index computation per distinct (folded) index expression, so
      // that the copies' equal indices are one value and need no mux.
      SmallVector<std::tuple<AffineMap, SmallVector<Value>, Value>> applied;
      Operation *firstLoad = steered.front()->load;
      for (AffineCopy *c : steered)
        if (steerBefore(c->load, firstLoad))
          firstLoad = c->load;
      firstLoad = guardAnchor(firstLoad);
      llvm::DenseMap<Operation *, memref::LoadOp> converted;
      for (AffineCopy *copy : steered) {
        affine::AffineLoadOp ld = copy->load;
        OpBuilder b(ld);
        SmallVector<Value> idx;
        AffineMap map = ld.getAffineMap();
        for (unsigned r = 0; r < map.getNumResults(); ++r) {
          AffineMap sub = map.getSubMap({r});
          SmallVector<Value> ops(ld.getMapOperands());
          affine::fullyComposeAffineMapAndOperands(&sub, &ops);
          affine::canonicalizeMapAndOperands(&sub, &ops);
          auto it = llvm::find_if(applied, [&](auto &a) {
            return std::get<0>(a) == sub && std::get<1>(a) == ops;
          });
          if (it != applied.end()) {
            idx.push_back(std::get<2>(*it));
            continue;
          }
          // Shared values go before the first copy when their operands
          // allow it (they are function values or induction variables).
          bool early = llvm::all_of(ops, [&](Value v) {
            Operation *d = v.getDefiningOp();
            return !d || d->getBlock() != firstLoad->getBlock() ||
                   d->isBeforeInBlock(firstLoad);
          });
          OpBuilder ab(early ? firstLoad : ld.getOperation());
          Value v = affine::AffineApplyOp::create(ab, ld.getLoc(), sub, ops);
          applied.push_back({sub, ops, v});
          idx.push_back(v);
        }
        auto ml = memref::LoadOp::create(b, ld.getLoc(), site, idx);
        for (NamedAttribute a : ld->getDiscardableAttrs())
          if (a.getName() != "map")
            ml->setDiscardableAttr(a.getName(), a.getValue());
        ld.getResult().replaceAllUsesWith(ml.getResult());
        converted[ld.getOperation()] = ml;
        ld.erase();
      }
      for (SmallVector<AffineCopy> &cls : classes) {
        if (cls.size() < 2)
          continue;
        SmallVector<SteerMember> members;
        for (AffineCopy &c : cls)
          members.push_back({converted.lookup(c.load.getOperation()),
                             c.offsets});
        int64_t size = members.size();
        if (steerGroup(std::move(members), banks, l))
          stats.groupSizes.push_back(size);
      }
    }
  }
  // Group the runtime-indexed loads of one block by the base of their index
  // on every partitioned dimension (or its constant bank).
  using GroupKey =
      std::pair<Block *, SmallVector<std::pair<int64_t, void *>>>;
  std::map<GroupKey, size_t> groupIndex;
  std::vector<SmallVector<SteerMember>> groups;
  SmallVector<SmallVector<std::optional<int64_t>>> groupConstBanks;
  for (Operation *user : site.getUsers()) {
    auto ld = dyn_cast<memref::LoadOp>(user);
    if (!ld || ld.getMemRef() != site)
      continue;
    GroupKey key{guardAnchor(ld)->getBlock(), {}};
    SmallVector<std::optional<int64_t>> constBanks;
    SteerMember m{ld, {}};
    for (const DimPartition &p : l.dims) {
      Value idx = ld.getIndices()[p.dim];
      if (l.dims.size() == 1 ? constantIndexOf(idx).has_value() ||
                                   inductionResidueBank(idx, p).has_value()
                             : constantBankOf(idx, p).has_value()) {
        std::optional<int64_t> bank = constantBankOf(idx, p);
        key.second.push_back({bank ? *bank : -1, nullptr});
        constBanks.push_back(bank ? bank : std::optional<int64_t>(-1));
        continue;
      }
      auto [base, c] = residueBase(idx, p.factor, 0);
      key.second.push_back({0, base.getAsOpaquePointer()});
      constBanks.push_back(std::nullopt);
      m.offsets.push_back(c);
    }
    if (m.offsets.empty())
      continue; // every bank constant
    auto [it, inserted] = groupIndex.try_emplace(key, groups.size());
    if (inserted) {
      groups.emplace_back();
      groupConstBanks.push_back(constBanks);
    }
    groups[it->second].push_back(std::move(m));
  }
  for (auto [members, constBanks] : llvm::zip(groups, groupConstBanks)) {
    if (members.size() < 2)
      continue;
    // two copies may meet in one bank: without N74 they are rewritten one
    // by one; with it, each residue class forms its own steered groups
    for (SmallVector<SteerMember> &cls : residueClassGroups<SteerMember>(
             members,
             [](const SteerMember &m) -> ArrayRef<int64_t> {
               return m.offsets;
             },
             rotatingFactors(constBanks)))
      if (cls.size() >= 2) {
        int64_t size = cls.size();
        if (steerGroup(std::move(cls), banks, l))
          stats.groupSizes.push_back(size);
      }
  }
}

static void rewriteMemrefStore(memref::StoreOp storeOp, ArrayRef<Value> banks,
                               const BankLayout &l) {
  OpBuilder b(storeOp);
  Location loc = storeOp.getLoc();
  Value val = storeOp.getValueToStore();
  MemrefBanking mb = resolveMemref(b, loc, storeOp.getIndices(), l);
  if (mb.choice.rotating.empty()) {
    auto ns = memref::StoreOp::create(b, loc, val,
                                      banks[mb.choice.bank(l, 0)],
                                      mb.bankedIndices);
    copyForwardingCounters(storeOp, ns);
  } else {
    int64_t n = mb.choice.numCandidates(l);
    for (int64_t k = 0; k < n; ++k) {
      Value kc = arith::ConstantIndexOp::create(b, loc,
                                                mb.choice.rotValue(l, k));
      Value en = arith::CmpIOp::create(b, loc, arith::CmpIPredicate::eq,
                                       mb.rotIdx, kc);
      // StoreEnableOp operand order: (value, enable_i1, memref, indices...)
      if (compoundAssignTwoStores(storeOp)) {
        auto extra = StoreEnableOp::create(
            b, loc, val, en, banks[mb.choice.bank(l, k)], mb.bankedIndices);
        extra->setAttr("hls.compound_assign_store", b.getUnitAttr());
      }
      auto se = StoreEnableOp::create(b, loc, val, en,
                                      banks[mb.choice.bank(l, k)],
                                      mb.bankedIndices);
      copyForwardingCounters(storeOp, se);
    }
  }
  storeOp.erase();
}

//===----------------------------------------------------------------------===//
// Arrays: storage roots, the callee parameters they reach, callee forms
//===----------------------------------------------------------------------===//
//
// A storage root is a memref.alloca or a memref.global. Its partition is the
// merge of its own pragma and the pragmas of every callee parameter it is
// passed to, directly or through further calls (N17 (b)). Pragmas flow from a
// parameter to the arrays that reach it, not sideways: an array that only
// shares an unpartitioned callee with a partitioned one stays unpartitioned
// (forgebench diff_orders_module: BRAM_C3, filled by the same load_64_128 as
// the partitioned BRAM_A1 / BRAM_C1, has no partition banks in Vitis). A
// callee whose call sites pass arrays of different partitions is cloned per
// form, as Vitis does (N14 R4; diff_orders_module a.o.1: the call that fills
// BRAM_C3 is a separate, single-site function that dead-code removal
// deletes).

/// `hls.steering` on the memory of each bank: the sizes of the load groups
/// steered across the banks and the forwarded if-arm reloads (N27 / N74),
/// accumulated over the sites of a global. Read by the debug report only.
static void recordSteering(ArrayRef<Value> banks, const SteerStats &stats) {
  if (stats.groupSizes.empty() && stats.forwardedReloads == 0 &&
      stats.prunedStoreEnables == 0)
    return;
  for (Value bank : banks) {
    Operation *mem = bank.getDefiningOp();
    if (auto gg = dyn_cast_or_null<memref::GetGlobalOp>(mem))
      mem = SymbolTable::lookupNearestSymbolFrom(gg, gg.getNameAttr());
    if (!mem)
      continue;
    Builder b(mem->getContext());
    SmallVector<int64_t> sizes;
    int64_t forwarded = 0, pruned = 0;
    if (auto old = mem->getAttrOfType<DictionaryAttr>("hls.steering")) {
      if (auto g = old.getAs<DenseI64ArrayAttr>("groups"))
        sizes.append(g.asArrayRef().begin(), g.asArrayRef().end());
      if (auto f = old.getAs<IntegerAttr>("forwarded_reloads"))
        forwarded = f.getInt();
      if (auto p = old.getAs<IntegerAttr>("pruned_store_enables"))
        pruned = p.getInt();
    }
    sizes.append(stats.groupSizes.begin(), stats.groupSizes.end());
    forwarded += stats.forwardedReloads;
    pruned += stats.prunedStoreEnables;
    SmallVector<NamedAttribute> fields{
        b.getNamedAttr("groups", b.getDenseI64ArrayAttr(sizes)),
        b.getNamedAttr("forwarded_reloads", b.getI64IntegerAttr(forwarded))};
    // The store_enables reachable_store_banks left out (O150), on the
    // array's banks; absent when none.
    if (pruned)
      fields.push_back(b.getNamedAttr("pruned_store_enables",
                                      b.getI64IntegerAttr(pruned)));
    mem->setAttr("hls.steering", b.getDictionaryAttr(fields));
  }
}

class BankingPlan {
public:
  BankingPlan(ModuleOp module, bool steerAffineLoads)
      : module(module), symbols(module), steerAffineLoads(steerAffineLoads) {}

  void run() {
    partitions.emplace(module, /*warn=*/true);
    assignCalleeForms();
    bank();
    if (clonesMade)
      refreshFormPortBound();
  }

private:
  ModuleOp module;
  SymbolTable symbols;
  bool steerAffineLoads = true;

  // The partition of every storage root of the incoming module.
  std::optional<PartitionRoots> partitions;

  // --- Callee forms ---
  // A cloned function or alloca -> the one it was cloned from.
  DenseMap<Operation *, Operation *> originOf;
  // Original function -> its forms (layout key, function instance).
  DenseMap<Operation *, SmallVector<std::pair<std::string, func::FuncOp>>>
      formsOf;
  // Function instance -> the partition of each parameter.
  llvm::MapVector<Operation *, SmallVector<std::optional<BankLayout>>>
      paramLayouts;
  unsigned clonesMade = 0;
  // The names of every form of a callee that has more than one (the
  // original and its clones).
  llvm::StringSet<> multiFormCallees;

  // --- Rewriting ---
  DenseMap<Value, SmallVector<Value>> banksOf;

  std::optional<BankLayout> layoutOfValue(Value v, func::FuncOp fn);
  void assignCalleeForms();
  void bank();
  void refreshFormPortBound();

  DictionaryAttr partitionAttr(OpBuilder &b, const BankLayout &l);
  DictionaryAttr bankAttrs(OpBuilder &b, const BankLayout &l,
                           unsigned bankIdx, Operation *from,
                           StringRef bankOf);
  SmallVector<Value> createAllocaBanks(memref::AllocaOp alloca,
                                       const BankLayout &l);
  void createGlobalBanks(memref::GlobalOp g, ArrayRef<Value> sites,
                         const BankLayout &l);
  void rewriteAccesses(Value site, const BankLayout &l);
  void rewriteCalls();
};

std::optional<BankLayout> BankingPlan::layoutOfValue(Value v,
                                                     func::FuncOp fn) {
  if (auto arg = dyn_cast<BlockArgument>(v)) {
    if (arg.getOwner() != &fn.getBody().front())
      return std::nullopt;
    auto it = paramLayouts.find(fn.getOperation());
    if (it == paramLayouts.end() || arg.getArgNumber() >= it->second.size())
      return std::nullopt;
    return it->second[arg.getArgNumber()];
  }
  Operation *def = v.getDefiningOp();
  if (!def)
    return std::nullopt;
  if (auto gg = dyn_cast<memref::GetGlobalOp>(def))
    def = symbols.lookup(gg.getName());
  else if (!isa<memref::AllocaOp>(def))
    return std::nullopt;
  if (Operation *orig = originOf.lookup(def))
    def = orig;
  return partitions->layoutOf(def);
}

void BankingPlan::assignCalleeForms() {
  // Top-down from the functions no call reaches: each call gets the form of
  // its callee whose parameter partitions equal its arguments' partitions.
  SmallVector<func::FuncOp> work;
  for (auto fn : module.getOps<func::FuncOp>())
    if (!fn.isExternal() && !partitions->called().contains(fn.getOperation())) {
      paramLayouts[fn.getOperation()].assign(fn.getNumArguments(),
                                             std::nullopt);
      work.push_back(fn);
    }
  for (unsigned w = 0; w < work.size() && w < 100000; ++w) {
    func::FuncOp fn = work[w];
    SmallVector<func::CallOp> calls;
    fn.walk([&](func::CallOp c) { calls.push_back(c); });
    for (func::CallOp call : calls) {
      func::FuncOp now = resolveDefinedCallee(call);
      if (!now)
        continue;
      Operation *origOp = originOf.lookup(now.getOperation());
      auto orig = origOp ? cast<func::FuncOp>(origOp) : now;
      SmallVector<std::optional<BankLayout>> layouts(orig.getNumArguments(),
                                                     std::nullopt);
      for (auto [i, v] : llvm::enumerate(call.getArgOperands()))
        if (i < layouts.size() && isa<MemRefType>(v.getType()))
          layouts[i] = layoutOfValue(v, fn);
      std::string key = partitionFormKey(layouts);
      auto &forms = formsOf[orig.getOperation()];
      func::FuncOp inst;
      for (auto &[k, f] : forms)
        if (k == key)
          inst = f;
      if (!inst) {
        if (forms.empty()) {
          inst = orig;
        } else {
          // Another form: a clone of the callee (N14 R4), its locals mapped
          // back to the originals so they keep their partitions.
          IRMapping map;
          inst = cast<func::FuncOp>(orig->clone(map));
          orig.walk([&](memref::AllocaOp a) {
            if (Value c = map.lookupOrNull(a.getResult()))
              originOf[c.getDefiningOp()] = a.getOperation();
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
        call.setCalleeAttr(FlatSymbolRefAttr::get(inst.getSymNameAttr()));
    }
  }
  // An original function whose every call now reaches a clone is dead.
  for (auto &[origOp, forms] : formsOf) {
    auto orig = cast<func::FuncOp>(origOp);
    if (orig.isPrivate() && symbols.symbolKnownUseEmpty(orig, module))
      paramLayouts.erase(origOp), symbols.erase(orig);
  }
}

// Each form of a callee is its own module in Vitis (N14 R4), so whether its
// parameters reach a module instantiated at more than one place (N14 R6,
// hls.port_bound_args, decided by --auto-pipeline-unroll on the callee
// before it was split into forms) is decided again on the forms' own call
// sites. w9r13rev_ci_two: cons(A) with A partitioned by constant indices
// (N94) and cons(B) are cons and cons_1 in Vitis, both II 1, B RAM_1WNR
// (60); the shared callee had made B port-bound (II 8, 4).
void BankingPlan::refreshFormPortBound() {
  InstanceModel model = computeInstances(module);
  OpBuilder b(module.getContext());
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
      fn->setAttr(kPortBoundArgsAttr, b.getI64ArrayAttr(bound));
  }
}

DictionaryAttr BankingPlan::partitionAttr(OpBuilder &b, const BankLayout &l) {
  auto kindName = [](PartitionSpec::Kind k) {
    return k == PartitionSpec::Complete ? "complete"
           : k == PartitionSpec::Block  ? "block"
                                        : "cyclic";
  };
  auto dimDict = [&](const DimPartition &p, bool withSource) {
    SmallVector<NamedAttribute> f{
        b.getNamedAttr("kind", b.getStringAttr(kindName(p.kind))),
        b.getNamedAttr("factor",
                       b.getI32IntegerAttr(static_cast<int32_t>(p.factor))),
        b.getNamedAttr("dim",
                       b.getI32IntegerAttr(static_cast<int32_t>(p.dim + 1)))};
    if (withSource)
      f.push_back(b.getNamedAttr(
          "source", p.source ? p.source : b.getStringAttr("pragma")));
    return f;
  };
  // `kind`, `factor` and `dim` are what banking applied along the first split
  // dimension; `dims` lists every split dimension when there are several;
  // `from` names the callee parameter whose pragma the first split comes from
  // when it is not the array's own (N17 (b)).
  SmallVector<NamedAttribute> fields = dimDict(l.dims.front(), true);
  if (l.dims.size() > 1) {
    SmallVector<Attribute> all;
    for (const DimPartition &p : l.dims)
      all.push_back(b.getDictionaryAttr(dimDict(p, false)));
    fields.push_back(b.getNamedAttr("dims", b.getArrayAttr(all)));
  }
  if (!l.dims.front().from.empty())
    fields.push_back(
        b.getNamedAttr("from", b.getStringAttr(l.dims.front().from)));
  return b.getDictionaryAttr(fields);
}

DictionaryAttr BankingPlan::bankAttrs(OpBuilder &b, const BankLayout &l,
                                      unsigned bankIdx, Operation *from,
                                      StringRef bankOf) {
  // Provenance for the debug report (--bram-debug): which array each bank
  // came from (`hls.bank_of`), its index and count, and the split that
  // produced it (`hls.partition`). The marks of the array (its name, why it
  // is kept, its ROM width, its stream / bind_storage pragmas, the width
  // Vitis narrows it to) carry over:
  // every bank holds part of it.
  SmallVector<NamedAttribute, 8> attrs;
  if (from)
    for (StringRef name :
         {"polygeist.varname", "hls.preserve", "hls.partition_reason",
          "hls.kept_reason", "hls.const_fill", "hls.stream",
          "hls.bind_storage", "hls.narrow_bits", "hls.narrow_reason"})
      if (Attribute a = from->getAttr(name))
        attrs.push_back(b.getNamedAttr(name, a));
  if (!bankOf.empty())
    attrs.push_back(b.getNamedAttr("hls.bank_of", b.getStringAttr(bankOf)));
  attrs.push_back(b.getNamedAttr(
      "hls.bank_index", b.getI32IntegerAttr(static_cast<int32_t>(bankIdx))));
  attrs.push_back(b.getNamedAttr(
      "hls.bank_count",
      b.getI32IntegerAttr(static_cast<int32_t>(l.numBanks))));
  attrs.push_back(b.getNamedAttr("hls.partition", partitionAttr(b, l)));
  return b.getDictionaryAttr(attrs);
}

static FileLineColLoc findFileLineColLoc(Location loc) {
  if (auto f = dyn_cast<FileLineColLoc>(loc))
    return f;
  if (auto n = dyn_cast<NameLoc>(loc))
    return findFileLineColLoc(n.getChildLoc());
  if (auto c = dyn_cast<CallSiteLoc>(loc))
    return findFileLineColLoc(c.getCallee());
  if (auto fu = dyn_cast<FusedLoc>(loc))
    for (Location l : fu.getLocations())
      if (auto f = findFileLineColLoc(l))
        return f;
  if (auto o = dyn_cast<OpaqueLoc>(loc))
    return findFileLineColLoc(o.getFallbackLocation());
  return {};
}

// `hls.bank_of` for a partitioned array that has no `polygeist.varname`
// (hand-written IR, or a temporary the front end did not name). The banks of
// one array must still share a name so the debug report can add them up:
// use the source location when there is one, otherwise the array's
// program-order position among the function's storage declarations (banks
// inserted earlier in this pass are skipped; they carry `hls.partition`).
static std::string unnamedBankOf(Value mem) {
  if (auto f = findFileLineColLoc(mem.getLoc()))
    return "<unnamed@" + f.getFilename().str() + ":" +
           std::to_string(f.getLine()) + ":" + std::to_string(f.getColumn()) +
           ">";
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

SmallVector<Value> BankingPlan::createAllocaBanks(memref::AllocaOp alloca,
                                                  const BankLayout &l) {
  OpBuilder b(alloca->getContext());
  b.setInsertionPointAfter(alloca);
  Attribute varName = alloca->getAttr("polygeist.varname");
  std::string bankOf = varName ? cast<StringAttr>(varName).getValue().str()
                               : unnamedBankOf(alloca.getResult());
  SmallVector<Value> banks;
  for (int64_t i = 0; i < l.numBanks; ++i) {
    auto bank = memref::AllocaOp::create(b, alloca.getLoc(), l.bankType);
    bank->setAttrs(bankAttrs(b, l, static_cast<unsigned>(i), alloca, bankOf));
    banks.push_back(bank.getResult());
  }
  return banks;
}

// The initial value of every bank of a dense-initialised global.
static SmallVector<SmallVector<Attribute>>
sliceInitialValue(DenseElementsAttr init, MemRefType ty, const BankLayout &l) {
  ArrayRef<int64_t> shape = ty.getShape();
  ArrayRef<int64_t> bankShape = l.bankType.getShape();
  int64_t perBank = 1;
  for (int64_t d : bankShape)
    perBank *= d;
  Attribute zero = OpBuilder(ty.getContext()).getZeroAttr(ty.getElementType());
  SmallVector<SmallVector<Attribute>> out(
      l.numBanks, SmallVector<Attribute>(perBank, zero));
  SmallVector<Attribute> all(init.getValues<Attribute>().begin(),
                             init.getValues<Attribute>().end());
  int64_t rank = shape.size();
  SmallVector<int64_t> nd(rank);
  for (int64_t lin = 0; lin < static_cast<int64_t>(all.size()); ++lin) {
    int64_t rest = lin;
    for (int64_t d = rank - 1; d >= 0; --d) {
      nd[d] = rest % shape[d];
      rest /= shape[d];
    }
    int64_t bank = 0;
    for (unsigned j = 0; j < l.dims.size(); ++j) {
      auto [bk, off] = bankAndOffset(nd[l.dims[j].dim], l.dims[j]);
      bank += bk * l.strides[j];
      nd[l.dims[j].dim] = off;
    }
    int64_t pos = 0;
    for (int64_t d = 0; d < rank; ++d)
      pos = pos * bankShape[d] + nd[d];
    out[bank][pos] = all[lin];
  }
  return out;
}

void BankingPlan::createGlobalBanks(memref::GlobalOp g, ArrayRef<Value> sites,
                                    const BankLayout &l) {
  OpBuilder b(g->getContext());
  MemRefType ty = g.getType();
  SmallVector<SmallVector<Attribute>> init;
  std::optional<Attribute> initial = g.getInitialValue();
  auto dense = initial ? dyn_cast<DenseElementsAttr>(*initial)
                       : DenseElementsAttr();
  if (dense)
    init = sliceInitialValue(dense, ty, l);
  std::string bankOf = g.getSymName().str();
  b.setInsertionPointAfter(g);
  SmallVector<memref::GlobalOp> bankGlobals;
  for (int64_t i = 0; i < l.numBanks; ++i) {
    std::string name = llvm::formatv("{0}_bank_{1}", g.getSymName(), i);
    Attribute initAttr;
    if (dense)
      initAttr = DenseElementsAttr::get(
          RankedTensorType::get(l.bankType.getShape(), ty.getElementType()),
          init[i]);
    else if (initial)
      initAttr = *initial; // `uninitialized`
    auto bg = memref::GlobalOp::create(
        b, g.getLoc(), b.getStringAttr(name), g.getSymVisibilityAttr(),
        TypeAttr::get(l.bankType), initAttr, g.getConstantAttr(),
        g.getAlignmentAttr());
    for (NamedAttribute a :
         bankAttrs(b, l, static_cast<unsigned>(i), g, bankOf))
      bg->setAttr(a.getName(), a.getValue());
    symbols.insert(bg); // renames the bank on a clash with another symbol
    b.setInsertionPointAfter(bg);
    bankGlobals.push_back(bg);
  }
  for (Value site : sites) {
    auto gg = site.getDefiningOp<memref::GetGlobalOp>();
    OpBuilder sb(gg);
    sb.setInsertionPointAfter(gg);
    SmallVector<Value> banks;
    for (int64_t i = 0; i < l.numBanks; ++i)
      banks.push_back(memref::GetGlobalOp::create(sb, gg.getLoc(), l.bankType,
                                                  bankGlobals[i].getSymName())
                          .getResult());
    banksOf[site] = std::move(banks);
  }
}

void BankingPlan::rewriteAccesses(Value site, const BankLayout &l) {
  SmallVector<Value> banks = banksOf[site];
  SteerStats stats;
  steerLoadGroups(site, banks, l, steerAffineLoads, stats);
  recordSteering(banks, stats);
  SmallVector<Operation *> users(site.getUsers().begin(),
                                 site.getUsers().end());
  unsigned pruned = 0;
  for (Operation *user : users) {
    if (auto ld = dyn_cast<affine::AffineLoadOp>(user))
      rewriteAffineLoad(ld, banks, l);
    else if (auto st = dyn_cast<affine::AffineStoreOp>(user))
      pruned += rewriteAffineStore(st, banks, l);
    else if (auto ld = dyn_cast<memref::LoadOp>(user))
      rewriteMemrefLoad(ld, banks, l);
    else if (auto st = dyn_cast<memref::StoreOp>(user))
      rewriteMemrefStore(st, banks, l);
    // Calls are rewritten once every bank exists (rewriteCalls).
  }
  if (pruned) {
    SteerStats prunedStats;
    prunedStats.prunedStoreEnables = pruned;
    recordSteering(banks, prunedStats);
  }
}

void BankingPlan::rewriteCalls() {
  SmallVector<func::CallOp> calls;
  module.walk([&](func::CallOp call) {
    if (llvm::any_of(call.getArgOperands(),
                     [&](Value v) { return banksOf.count(v); }))
      calls.push_back(call);
  });
  for (func::CallOp call : calls) {
    SmallVector<Value> operands;
    for (Value v : call.getArgOperands()) {
      auto it = banksOf.find(v);
      if (it == banksOf.end())
        operands.push_back(v);
      else
        operands.append(it->second.begin(), it->second.end());
    }
    OpBuilder b(call);
    auto nc = func::CallOp::create(b, call.getLoc(), call.getCalleeAttr(),
                                   call.getResultTypes(), operands);
    for (NamedAttribute a : call->getDiscardableAttrs())
      nc->setDiscardableAttr(a.getName(), a.getValue());
    call.replaceAllUsesWith(nc.getResults());
    call.erase();
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
  OpBuilder b(module.getContext());
  SetVector<Value> candidates;
  for (const LocalBank &lb : localBanks)
    candidates.insert(*lb.bank);
  DenseMap<Operation *, SmallVector<func::CallOp>> callSitesOf;
  module.walk([&](func::CallOp call) {
    if (auto f = symbols.lookup<func::FuncOp>(call.getCallee()))
      callSitesOf[f].push_back(call);
  });
  for (func::FuncOp f : module.getOps<func::FuncOp>()) {
    if (f.isExternal() || f.isPublic() || callSitesOf.lookup(f).empty() ||
        f.getFunctionType().getNumInputs() !=
            f.getBody().front().getNumArguments())
      continue;
    for (unsigned i = 0; i < f.getNumArguments(); ++i)
      if (f.getArgAttr(i, "hls.bank_of") &&
          isa<MemRefType>(f.getArgument(i).getType()))
        candidates.insert(f.getArgument(i));
  }
  if (candidates.empty())
    return;
  auto isStore = [](Operation *u) {
    return isa<memref::StoreOp, affine::AffineStoreOp, StoreEnableOp,
               AffineStoreEnableOp>(u);
  };
  // The greatest set closed under the rule: start from every candidate.
  DenseSet<Value> unread(candidates.begin(), candidates.end());
  for (bool changed = true; changed;) {
    changed = false;
    for (Value v : candidates) {
      if (!unread.contains(v))
        continue;
      bool ok = llvm::all_of(v.getUses(), [&](OpOperand &use) {
        Operation *u = use.getOwner();
        if (isStore(u))
          return true;
        auto call = dyn_cast<func::CallOp>(u);
        if (!call)
          return false;
        auto callee = symbols.lookup<func::FuncOp>(call.getCallee());
        return callee && !callee.isExternal() &&
               use.getOperandNumber() < callee.getNumArguments() &&
               unread.contains(callee.getArgument(use.getOperandNumber()));
      });
      if (auto arg = dyn_cast<BlockArgument>(v)) {
        auto f = cast<func::FuncOp>(arg.getOwner()->getParentOp());
        ok = ok && llvm::all_of(callSitesOf.lookup(f), [&](func::CallOp c) {
               return c.getNumOperands() == f.getNumArguments() &&
                      unread.contains(c.getOperand(arg.getArgNumber()));
             });
      }
      if (!ok) {
        unread.erase(v);
        changed = true;
      }
    }
  }
  if (unread.empty())
    return;
  // The stores, then the parameters with their call operands.
  for (Value v : candidates)
    if (unread.contains(v))
      for (Operation *u : llvm::make_early_inc_range(v.getUsers()))
        if (isStore(u))
          u->erase();
  for (func::FuncOp f : module.getOps<func::FuncOp>()) {
    if (f.isExternal())
      continue;
    llvm::BitVector drop(f.getNumArguments());
    // Only a parameter nothing uses any more: one still used (a view, a call
    // the removal did not follow) is kept (OPEN_ISSUES O208 H2:
    // quantitative_finance SVD, "Cannot destroy a value that still has
    // uses").
    for (unsigned i = 0; i < f.getNumArguments(); ++i)
      if (unread.contains(f.getArgument(i)) && f.getArgument(i).use_empty())
        drop.set(i);
    if (drop.none())
      continue;
    for (func::CallOp call : callSitesOf.lookup(f))
      for (int i = static_cast<int>(drop.size()) - 1; i >= 0; --i)
        if (drop.test(i))
          call->eraseOperand(i);
    // The port-bound parameter indices follow the remaining parameters.
    if (auto pb = f->getAttrOfType<ArrayAttr>(kPortBoundArgsAttr)) {
      SmallVector<int64_t> idx;
      for (Attribute a : pb) {
        int64_t i = cast<IntegerAttr>(a).getInt();
        if (i < 0 || i >= static_cast<int64_t>(drop.size()) || drop.test(i))
          continue;
        int64_t droppedBefore = 0;
        for (int64_t j = 0; j < i; ++j)
          droppedBefore += drop.test(j);
        idx.push_back(i - droppedBefore);
      }
      f->setAttr(kPortBoundArgsAttr, b.getI64ArrayAttr(idx));
    }
    (void)f.eraseArguments(drop);
  }
  SmallVector<Attribute> dead;
  if (auto prev = module->getAttrOfType<ArrayAttr>("hls.dead_memrefs"))
    dead.assign(prev.begin(), prev.end());
  for (const LocalBank &lb : localBanks) {
        Value &bank = *lb.bank;
        unsigned i = lb.index;
        if (!bank || !unread.contains(bank))
          continue;
        auto alloca = bank.getDefiningOp<memref::AllocaOp>();
        if (!alloca || !alloca->use_empty())
          continue;
        auto fn = alloca->getParentOfType<func::FuncOp>();
        const std::string &name = lb.name;
        dead.push_back(b.getDictionaryAttr(
            {b.getNamedAttr("kind", b.getStringAttr("alloca")),
             b.getNamedAttr("func", b.getStringAttr(fn ? fn.getName() : "")),
             b.getNamedAttr("name", b.getStringAttr(name)),
             b.getNamedAttr("loc", alloca.getLoc()),
             b.getNamedAttr("type", TypeAttr::get(alloca.getType())),
             b.getNamedAttr("by", b.getStringAttr("--memory-banking-bram")),
             b.getNamedAttr(
                 "reason",
                 b.getStringAttr("bank " + std::to_string(i) +
                                 " of a partitioned array that no access "
                                 "reads (VITIS_NOTES N157)"))}));
        alloca->erase();
        bank = Value();
  }
  module->setAttr("hls.dead_memrefs", b.getArrayAttr(dead));
}

void BankingPlan::bank() {
  guardBlockWrites.clear();
  MLIRContext *ctx = module.getContext();
  OpBuilder b(ctx);

  // Storage roots of the module as it now is (clones included).
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
  for (auto g : module.getOps<memref::GlobalOp>())
    if (auto l = layoutOfRoot(g.getOperation()))
      roots.push_back({g.getOperation(), {}, *l});
  module.walk([&](memref::AllocaOp a) {
    if (auto l = layoutOfRoot(a.getOperation()))
      roots.push_back({a.getOperation(), {a.getResult()}, *l});
  });
  module.walk([&](memref::GetGlobalOp gg) {
    for (RootWork &r : roots)
      if (auto g = dyn_cast<memref::GlobalOp>(r.op))
        if (g.getSymName() == gg.getName())
          r.sites.push_back(gg.getResult());
  });

  // Parameters with a partition, per function instance.
  struct ParamWork {
    func::FuncOp fn;
    BlockArgument arg;
    BankLayout layout;
  };
  SmallVector<ParamWork> params;
  for (auto &[fnOp, layouts] : paramLayouts) {
    auto fn = cast<func::FuncOp>(fnOp);
    for (auto [i, l] : llvm::enumerate(layouts))
      if (l && i < fn.getNumArguments())
        params.push_back({fn, fn.getArgument(static_cast<unsigned>(i)), *l});
  }
  if (roots.empty() && params.empty())
    return;

  // Remember every original parameter's attributes (insertion renumbers).
  llvm::MapVector<Operation *, DenseMap<Value, DictionaryAttr>> origAttrs;
  DenseMap<Operation *, SmallVector<Value>> portBound;
  DenseMap<Value, DictionaryAttr> newArgAttrs;
  for (ParamWork &p : params) {
    auto [it, inserted] = origAttrs.insert({p.fn.getOperation(), {}});
    if (!inserted)
      continue;
    for (BlockArgument a : p.fn.getArguments())
      it->second[a] = p.fn.getArgAttrDict(a.getArgNumber());
    if (auto pb = p.fn->getAttrOfType<ArrayAttr>(kPortBoundArgsAttr))
      for (Attribute a : pb)
        if (auto i = dyn_cast<IntegerAttr>(a))
          if (i.getInt() >= 0 &&
              i.getInt() < static_cast<int64_t>(p.fn.getNumArguments()))
            portBound[p.fn.getOperation()].push_back(
                p.fn.getArgument(static_cast<unsigned>(i.getInt())));
  }

  // 1. Banks.
  for (RootWork &r : roots) {
    if (auto a = dyn_cast<memref::AllocaOp>(r.op))
      banksOf[a.getResult()] = createAllocaBanks(a, r.layout);
    else
      createGlobalBanks(cast<memref::GlobalOp>(r.op), r.sites, r.layout);
  }
  for (ParamWork &p : params) {
    Block &entry = p.fn.getBody().front();
    SmallVector<Value> banks;
    std::string bankOf = "arg" + std::to_string(p.arg.getArgNumber());
    for (int64_t i = 0; i < p.layout.numBanks; ++i) {
      BlockArgument ba = entry.insertArgument(
          p.arg.getArgNumber() + 1 + static_cast<unsigned>(i),
          p.layout.bankType, p.arg.getLoc());
      newArgAttrs[ba] =
          bankAttrs(b, p.layout, static_cast<unsigned>(i), nullptr, bankOf);
      banks.push_back(ba);
    }
    banksOf[p.arg] = std::move(banks);
  }

  // 2. Accesses.
  for (RootWork &r : roots)
    for (Value site : r.sites)
      rewriteAccesses(site, r.layout);
  for (ParamWork &p : params)
    rewriteAccesses(p.arg, p.layout);

  // 3. Calls pass the banks.
  rewriteCalls();

  // The bank allocas of local arrays, for step 6 (before step 4 erases
  // the originals, whose names the records keep).
  SmallVector<LocalBank> localBanks;
  for (RootWork &r : roots) {
    if (!isa<memref::AllocaOp>(r.op))
      continue;
    std::string name;
    if (auto v = r.op->getAttrOfType<StringAttr>("polygeist.varname"))
      name = v.getValue().str();
    for (Value site : r.sites)
      for (auto [i, bank] : llvm::enumerate(banksOf[site]))
        if (bank && bank.getDefiningOp<memref::AllocaOp>())
          localBanks.push_back({&bank, name, static_cast<unsigned>(i)});
  }

  // 4. The originals.
  for (RootWork &r : roots) {
    if (isa<memref::AllocaOp>(r.op)) {
      r.op->erase();
      continue;
    }
    for (Value site : r.sites)
      site.getDefiningOp()->erase();
    symbols.erase(r.op);
  }
  for (ParamWork &p : params)
    p.fn.getBody().front().eraseArgument(p.arg.getArgNumber());

  // 5. Signatures, parameter attributes and port-bound parameter indices.
  for (auto &[fnOp, orig] : origAttrs) {
    auto fn = cast<func::FuncOp>(fnOp);
    SmallVector<Type> types;
    SmallVector<DictionaryAttr> attrs;
    DenseMap<Value, int64_t> newIndex;
    for (BlockArgument a : fn.getArguments()) {
      types.push_back(a.getType());
      newIndex[a] = a.getArgNumber();
      DictionaryAttr d;
      if (auto it = newArgAttrs.find(a); it != newArgAttrs.end())
        d = it->second;
      else if (auto it2 = orig.find(a); it2 != orig.end())
        d = it2->second;
      attrs.push_back(d ? d : DictionaryAttr::get(ctx, {}));
    }
    fn.setFunctionType(
        FunctionType::get(ctx, types, fn.getFunctionType().getResults()));
    fn.setAllArgAttrs(attrs);
    auto pb = portBound.find(fnOp);
    if (pb != portBound.end()) {
      SmallVector<int64_t> idx;
      for (Value v : pb->second) {
        if (auto it = banksOf.find(v); it != banksOf.end()) {
          for (Value bv : it->second)
            idx.push_back(newIndex.lookup(bv));
        } else {
          idx.push_back(newIndex.lookup(v));
        }
      }
      llvm::sort(idx);
      fn->setAttr(kPortBoundArgsAttr, b.getI64ArrayAttr(idx));
    }
  }

  // 6. N157 (drop_unread_banks): a bank of a local array that no access
  // reads is removed with its stores (Vitis: w9r21p_k1_deadbank, 10 of 12
  // banks; YOLOv4-Tiny L5 conv_in_buf, whose banks are written in one callee
  // and read in another), recorded for --bram-debug. After step 5, so that
  // the parameters, their attributes and the call operands agree.
  if (dropUnreadBanks())
    dropUnreadBankValues(module, symbols, localBanks);

  // Composition leaves operand-defining affine.apply ops dead. Sweep until
  // nothing changes, because an apply that fed only another dead apply
  // becomes dead one round later.
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
  for (int64_t d = to.getRank() - 1; d >= 0; --d) {
    strides[d] = stride;
    stride *= to.getShape()[d];
  }
  return cast.getStaticStrides() == ArrayRef<int64_t>(strides);
}

static void shrinkReshapedArrays(ModuleOp module) {
  SmallVector<memref::AllocaOp> allocas;
  module.walk([&](memref::AllocaOp a) {
    if (a->hasAttr("hls.array_partition"))
      allocas.push_back(a);
  });
  for (memref::AllocaOp a : allocas) {
    MemRefType shape;
    bool ok = !a->use_empty();
    for (Operation *u : a->getUsers()) {
      auto cast = dyn_cast<memref::ReinterpretCastOp>(u);
      if (!cast || !isRowReshape(cast, a.getType()) ||
          (shape && cast.getType() != shape)) {
        ok = false;
        break;
      }
      shape = cast.getType();
    }
    if (!ok || !shape)
      continue;
    OpBuilder b(a);
    auto smaller = b.create<memref::AllocaOp>(a.getLoc(), shape);
    smaller->setAttrs(a->getAttrs());
    for (Operation *u : llvm::make_early_inc_range(a->getUsers())) {
      u->getResult(0).replaceAllUsesWith(smaller.getResult());
      u->erase();
    }
    a.erase();
  }
}

static void widenReshapedCalleeParameters(ModuleOp module) {
  if (!circt::hlsest::Config::get()
           .tool.hls.partitioning.reshapedCalleeParameters)
    return;
  shrinkReshapedArrays(module);
  SymbolTable symbols(module);
  // The array a call operand reshapes, or null.
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
    std::optional<SymbolTable::UseRange> uses = callee.getSymbolUses(module);
    if (!uses)
      continue;
    SmallVector<func::CallOp> calls;
    bool onlyCalls = true;
    for (const SymbolTable::SymbolUse &u : *uses) {
      auto call = dyn_cast<func::CallOp>(u.getUser());
      if (!call) {
        onlyCalls = false;
        break;
      }
      calls.push_back(call);
    }
    if (!onlyCalls || calls.empty())
      continue;
    for (unsigned i = 0; i < callee.getNumArguments(); ++i) {
      BlockArgument arg = callee.getArgument(i);
      MemRefType wide;
      bool ok = true;
      for (func::CallOp call : calls) {
        memref::AllocaOp root = reshapedRoot(call.getOperand(i));
        if (!root || (wide && root.getType() != wide)) {
          ok = false;
          break;
        }
        wide = root.getType();
      }
      if (!ok || !wide)
        continue;
      if (!llvm::all_of(arg.getUsers(), [&](Operation *u) {
            if (auto ld = dyn_cast<affine::AffineLoadOp>(u))
              return ld.getMemRef() == arg;
            if (auto st = dyn_cast<affine::AffineStoreOp>(u))
              return st.getMemRef() == arg;
            if (auto ld = dyn_cast<memref::LoadOp>(u))
              return ld.getMemRef() == arg;
            if (auto st = dyn_cast<memref::StoreOp>(u))
              return st.getMemRef() == arg;
            return false;
          }))
        continue;
      arg.setType(wide);
      SmallVector<Type> inputs(callee.getArgumentTypes());
      inputs[i] = wide;
      callee.setType(FunctionType::get(module.getContext(), inputs,
                                       callee.getResultTypes()));
      for (func::CallOp call : calls) {
        auto cast =
            call.getOperand(i).getDefiningOp<memref::ReinterpretCastOp>();
        call->setOperand(i, cast.getSource());
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
    // An option given explicitly, else the configuration
    // (tool.hls.partitioning.steer_affine_loads,
    // tool.hls.memory_architecture.replication.callee_stores_per_loop).
    const circt::hlsest::HlsToolConfig &hc =
        circt::hlsest::Config::get().tool.hls;
    circt::hlsest::applyConfigured(steerAffineLoads,
                                   hc.partitioning.steerAffineLoads);
    circt::hlsest::applyConfigured(
        annotateCalleeStores,
        hc.memoryArchitecture.replication.calleeStoresPerLoop);
    // Vitis forwards an unrolled copy's store to the next copy's load and
    // deletes the overwritten store before the partition (VITIS_NOTES N138,
    // tool.hls.middle_end.forward_before_banking).
    if (hc.middleEnd.forwardBeforeBanking)
      (void)hls_analysis::forwardPartitionedStores(getOperation());
    widenReshapedCalleeParameters(getOperation());
    BankingPlan(getOperation(), steerAffineLoads).run();
    // Banks one iteration of one loop owns are registers in Vitis
    // (VITIS_NOTES N92, tool.hls.memory_architecture.
    // iteration_private_registers).
    if (hc.memoryArchitecture.iterationPrivateRegisters)
      hls_analysis::markIterationPrivateBanks(getOperation());
    // The banks exist now; record the callees' stores per loop body on them
    // for the per-function scheduler (BRAMClassification).
    if (annotateCalleeStores)
      hls_analysis::annotateCalleeStoresPerLoop(getOperation());
    // And on the callees' parameters the stores of the arrays their call
    // sites pass (VITIS_NOTES N99, tool.hls.memory_architecture.replication.
    // caller_stores_per_loop).
    if (hc.memoryArchitecture.replication.callerStoresPerLoop)
      hls_analysis::annotateCallerStoresPerLoop(getOperation());
    // The m_axi bundle of a callee parameter bound to a port (the request
    // limit of VITIS_NOTES N95 in callees), and the calls of callees with a
    // read-modify-write of a global (N102), for the per-function scheduler.
    if (const circt::hlsest::ImplicitBufferConfig *mc =
            hc.implicitBuffer("axi4-mm"))
      if (mc->busRequestsThroughCalls)
        hls_analysis::annotateMaxiBundlesThroughCalls(
            getOperation(), mc->mode, mc->defaultBundle);
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
