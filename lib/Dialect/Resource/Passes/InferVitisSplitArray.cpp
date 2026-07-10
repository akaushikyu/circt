//===- InferVitisSplitArray.cpp - array partitions from port pressure -----===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// Models Vitis HLS' "Inferring pragma 'array_partition ...' due to pipeline
// pragma". For every pipelined loop it counts, per array, the distinct
// addresses one iteration reads and writes, compares that with what one memory
// can serve at the target II, and - when the memory's ports are the
// bottleneck - attaches the `hls.array_partition` spec that splits the array
// until they are not. MemoryBankingPassModified consumes the attribute; no
// memref type is rewritten here.
//
//   int a[64][64];
//   for (i = 0; i < 64; i++)            // pipelined, target II = 1
//     ... a[i][0] ... a[i][1] ... a[i][63] ...   // inner j loop was unrolled
//
//   64 reads per iteration against 1 read port per bank at II = 1
//     -> factor = max(reads, writes) / II = 64 on the dimension the unrolled
//        index walks -> `complete dim=2` (factor == extent), like Vitis.
//
// The factor is not just that ratio, though: a split only helps if it sends
// the contending accesses to *different* banks. Every access is reduced to a
// linear form per dimension, and a candidate (dim, factor) is scored by the
// worst number of accesses that can land in one bank during one iteration.
// The smallest factor that meets the target II wins; if none does, the one
// that gets closest.
//
// Position in the pipeline - the pass counts accesses as they stand in the
// loop body, so whatever Vitis would unroll must be unrolled already:
//   auto-pipeline-unroll
//   -> [cse / affine-scalrep / affine-loop-invariant-code-motion, optional]
//   -> infer-vitis-split-array
//   -> memory banking -> scheduling / BRAM estimation
// At that point every innermost loop left is a pipelined loop (see
// getPipelineII). A loop tagged `hls.flattened_parents = N` by
// auto-pipeline-unroll is flattened by Vitis with its N enclosing loops: their
// induction variables are loop-variant for the pipeline, so a load indexed by
// them is not hoisted and counts (LoopPragmas.h, getFlattenedRoot).
//
// Two modes, after Vitis' `syn.array_partition.throughput_driven` (option
// `td`):
//   td=auto (default)  the port-pressure inference above. With
//                      `auto-partitions` it also applies the three rules of
//                      td=off first (Vitis does them in either mode); off by
//                      default, so the default output is what it always was.
//   td=off             no port-pressure partitions at all - Vitis replicates
//                      instead (RAM_1WNR, priced by --bram-analysis) - only
//                      the automatic partitions Vitis still makes
//                      (VITIS_NOTES.md N7, exp-notes/partition.md R5):
//     (a) [HLS 214-421] an array of at most `complete-threshold` (4) elements
//         in total, any width or rank -> registers;
//     (b) [HLS 214-449] a dimension that EVERY access of the array indexes
//         with a constant (in every loop, pipelined or not, after the
//         unrolling auto-pipeline-unroll did) -> `complete` on that dimension,
//         one bank per index (source = "constant-index"); only for an array
//         with at least one affine access, the ones memory banking splits.
//         "Constant" is ConstantIndex.h, which banking shares, so every such
//         access then reads a single bank;
//     (c) an array that every access indexes with constants in every
//         dimension -> scalarised (registers).
//   "Registers" is the unit attribute `hls.registers` on the alloca:
//   --bram-analysis counts 0 BRAM (status "registers") and the scheduler puts
//   no port limit on it. Everything else stays one memory, and an array a
//   user pragma already describes is left alone.
//
//===----------------------------------------------------------------------===//
#include "circt/Dialect/Resource/Passes/InferVitisSplitArray.h"
#include "circt/Dialect/Resource/Passes/ConstantIndex.h"
#include "circt/Dialect/Resource/Passes/LoopPragmas.h"
#include "mlir/Dialect/Affine/Analysis/LoopAnalysis.h"
#include "mlir/Dialect/Affine/IR/AffineOps.h"
#include "mlir/Dialect/Arith/IR/Arith.h"
#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/Dialect/MemRef/IR/MemRef.h"
#include "mlir/Dialect/Utils/StaticValueUtils.h"
#include "mlir/IR/AffineExpr.h"
#include "mlir/IR/AffineMap.h"
#include "mlir/IR/Builders.h"
#include "mlir/Interfaces/LoopLikeInterface.h"
#include "mlir/Pass/Pass.h"
#include "llvm/ADT/MapVector.h"
#include "llvm/ADT/SmallVector.h"
#include "llvm/ADT/StringSet.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/MathExtras.h"
#include "llvm/Support/raw_ostream.h"

#include <algorithm>
#include <optional>
#include <string>
#include "circt/Dialect/Resource/Interfaces/MemoryDS.h"
#include <circt/Dialect/Resource/Interfaces/MemoryOpInterface.h.inc>

#define DEBUG_TYPE "infer-vitis-split-array"

namespace circt {
namespace hls_analysis {}
} // namespace circt

using namespace mlir;
using namespace mlir::affine;
using namespace circt;
using namespace circt::hls_analysis;

namespace {

// Attribute spellings. `hls.array_partition` is the one the Polygeist fork
// emits and MemoryResourceOpInterface::getPartitionSpec() parses:
//   [{dim = 1 : i32, factor = 2 : i32, kind = "cyclic", variable = "buf"}]
constexpr StringLiteral kPartitionAttr = "hls.array_partition";
constexpr StringLiteral kPressureAttr = "hls.port_pressure";
/// Why a partition was inferred, for the --bram-debug report (string; memory
/// banking copies it onto every bank). Informational only.
constexpr StringLiteral kReasonAttr = "hls.partition_reason";
constexpr StringLiteral kPipelineAttr = "hls.pipeline";
constexpr StringLiteral kPipelineOffAttr = "hls.pipeline_off";
constexpr StringLiteral kVarNameAttr = "polygeist.varname";
/// `source` of an inferred spec entry: port pressure (td=auto) or the
/// constant-index rule (b).
constexpr StringLiteral kSourcePressure = "infer-from-design";
constexpr StringLiteral kSourceConstantIndex = "constant-index";
/// Pragmas that already decide how an array is stored; such an array is left
/// to them by the automatic partitions (a)-(c).
constexpr StringLiteral kUserStoragePragmas[] = {
    "hls.array_partition", "hls.array_reshape", "hls.bind_storage",
    "hls.stream"};

// Factors above this are never scanned one by one. Purely a guard against
// degenerate inputs (a[i] next to a[i + 2^40]); real factors are tiny.
constexpr int64_t kMaxScannedFactor = 1 << 16;

//===----------------------------------------------------------------------===//
// Access model
//===----------------------------------------------------------------------===//

/// Names SSA values with small ids so linear forms built from different
/// accesses (each with its own map operand list) are directly comparable.
class TermTable {
public:
  unsigned idFor(Value v) {
    unsigned next = ids.size();
    return ids.try_emplace(v, next).first->second;
  }

private:
  DenseMap<Value, unsigned> ids;
};

/// The index of one access along one memref dimension:
///     sum_k coeff_k * term_k + constant
/// A term is a loop iteration counter, a symbol, or any other index value.
struct LinearIndex {
  // (term id, coefficient), sorted by id, no zero coefficients.
  SmallVector<std::pair<unsigned, int64_t>, 2> terms;
  int64_t constant = 0;
  bool opaque = false; // mod / floordiv / ...: nothing is known
};

struct Access {
  Operation *op = nullptr;
  bool isWrite = false;
  SmallVector<LinearIndex, 3> index; // one entry per memref dimension
};

/// What one pipelined loop asks of one memory in a single iteration: distinct
/// read addresses and distinct write addresses, hoistable reads excluded.
struct PipelineRegion {
  AffineForOp loop;
  unsigned targetII = 1;
  SmallVector<Access, 8> accesses;
  unsigned reads = 0;
  unsigned writes = 0;
};

/// Accumulate `scale * expr` into one coefficient per map input plus a
/// constant. Fails on mod / floordiv / ceildiv and non-constant products.
static bool accumulateLinear(AffineExpr expr, int64_t scale, unsigned numDims,
                             MutableArrayRef<int64_t> coeffs,
                             int64_t &constant) {
  switch (expr.getKind()) {
  case AffineExprKind::Constant:
    constant += scale * cast<AffineConstantExpr>(expr).getValue();
    return true;
  case AffineExprKind::DimId:
    coeffs[cast<AffineDimExpr>(expr).getPosition()] += scale;
    return true;
  case AffineExprKind::SymbolId:
    coeffs[numDims + cast<AffineSymbolExpr>(expr).getPosition()] += scale;
    return true;
  case AffineExprKind::Add: {
    auto bin = cast<AffineBinaryOpExpr>(expr);
    return accumulateLinear(bin.getLHS(), scale, numDims, coeffs, constant) &&
           accumulateLinear(bin.getRHS(), scale, numDims, coeffs, constant);
  }
  case AffineExprKind::Mul: {
    auto bin = cast<AffineBinaryOpExpr>(expr);
    if (auto rhs = dyn_cast<AffineConstantExpr>(bin.getRHS()))
      return accumulateLinear(bin.getLHS(), scale * rhs.getValue(), numDims,
                              coeffs, constant);
    if (auto lhs = dyn_cast<AffineConstantExpr>(bin.getLHS()))
      return accumulateLinear(bin.getRHS(), scale * lhs.getValue(), numDims,
                              coeffs, constant);
    return false;
  }
  default:
    return false;
  }
}

static LinearIndex makeLinearIndex(AffineExpr expr, unsigned numDims,
                                   ValueRange operands, TermTable &terms) {
  LinearIndex li;
  SmallVector<int64_t, 8> coeffs(operands.size(), 0);
  if (!accumulateLinear(expr, /*scale=*/1, numDims, coeffs, li.constant)) {
    li = LinearIndex();
    li.opaque = true;
    return li;
  }

  for (auto [pos, rawCoeff] : llvm::enumerate(coeffs)) {
    int64_t coeff = rawCoeff;
    if (coeff == 0)
      continue;
    Value v = operands[pos];
    if (std::optional<int64_t> cst = getConstantIntValue(v)) {
      li.constant += coeff * *cst;
      continue;
    }
    // iv = lb + step * t. Express the index in the iteration counter t so that
    // `for i = 0 to N step 4 { a[i], a[i+1], ... }` is seen to pin a[i + c] to
    // bank (c mod 4) rather than rotating through the banks.
    if (isAffineForInductionVar(v)) {
      AffineForOp owner = getForInductionVarOwner(v);
      if (owner.hasConstantLowerBound()) {
        li.constant += coeff * owner.getConstantLowerBound();
        coeff *= owner.getStepAsInt();
      }
    }
    li.terms.emplace_back(terms.idFor(v), coeff);
  }

  // Canonical form: sorted by term, duplicates merged, zeros dropped.
  llvm::sort(li.terms);
  SmallVector<std::pair<unsigned, int64_t>, 2> merged;
  for (auto [id, coeff] : li.terms) {
    if (!merged.empty() && merged.back().first == id)
      merged.back().second += coeff;
    else
      merged.emplace_back(id, coeff);
  }
  llvm::erase_if(merged, [](const auto &term) { return term.second == 0; });
  li.terms = std::move(merged);
  return li;
}

/// Build the per-dimension linear forms of one access and decide whether its
/// address is invariant in `loop`.
static void analyzeAddress(AffineMap map, ValueRange mapOperands,
                           AffineForOp loop, TermTable &terms, Access &access,
                           bool &loopInvariant) {
  SmallVector<Value, 8> operands(mapOperands.begin(), mapOperands.end());
  // Look through affine.apply producers (e.g. the 2*j left by loop
  // normalization) so coefficients are those of the real loop counters.
  fullyComposeAffineMapAndOperands(&map, &operands);
  canonicalizeMapAndOperands(&map, &operands);
  map = simplifyAffineMap(map);

  AffineForOp root = getFlattenedRoot(loop);
  loopInvariant = llvm::all_of(
      operands, [&](Value v) { return root.isDefinedOutsideOfLoop(v); });
  for (AffineExpr expr : map.getResults())
    access.index.push_back(
        makeLinearIndex(expr, map.getNumDims(), operands, terms));
}

/// Two accesses with the same key touch the same element. Opaque indices get
/// a key of their own, so they are never merged with anything.
static std::string addressKey(const Access &access) {
  std::string key;
  llvm::raw_string_ostream os(key);
  os << (access.isWrite ? 'W' : 'R');
  for (const LinearIndex &li : access.index) {
    if (li.opaque) {
      os << "|?" << static_cast<const void *>(access.op);
      continue;
    }
    os << '|' << li.constant;
    for (auto [id, coeff] : li.terms)
      os << '+' << coeff << "*t" << id;
  }
  return key;
}

/// True if some op in the loops flattened into `loop`'s pipeline (its
/// `hls.flattened_parents` ancestors), outside `loop` itself, may write `mem`
/// or uses it opaquely: Vitis sinks that code into the pipelined loop, so a
/// read of `mem` there cannot be hoisted.
static bool isWrittenInFlattenedParents(Value mem, AffineForOp loop) {
  AffineForOp root = getFlattenedRoot(loop);
  if (root == loop)
    return false;
  bool written = false;
  root.getBody()->walk([&](Operation *op) {
    if (loop->isAncestor(op) || !llvm::is_contained(op->getOperands(), mem))
      return WalkResult::advance();
    auto eff = dyn_cast<MemoryEffectOpInterface>(op);
    if (!eff) {
      written = true;
      return WalkResult::interrupt();
    }
    SmallVector<MemoryEffects::EffectInstance> effects;
    eff.getEffectsOnValue(mem, effects);
    for (auto &e : effects)
      if (!isa<MemoryEffects::Read>(e.getEffect())) {
        written = true;
        return WalkResult::interrupt();
      }
    return WalkResult::advance();
  });
  return written;
}

/// Record, for every memory touched inside `loop`, the accesses that still
/// occupy a port once per iteration after the clean-ups every HLS front end
/// performs:
///  - reads whose address does not change with the loop, from a memory the
///    loop never writes, are hoisted to the preheader (LICM);
///  - repeated accesses to one address collapse to a single read and a single
///    write (GVN / store forwarding) - the `acc[i] += ...` chain left behind
///    by an unrolled reduction is one read and one write, not 64 of each.
/// Accesses under mutually exclusive branches all count: a pipelined body is
/// if-converted.
static void
collectRegions(AffineForOp loop, unsigned targetII, TermTable &terms,
               llvm::MapVector<Value, SmallVector<PipelineRegion, 2>> &out) {
  struct RawAccess {
    Access access;
    bool loopInvariant = false;
  };
  llvm::MapVector<Value, SmallVector<RawAccess, 8>> raw;
  MLIRContext *ctx = loop.getContext();

  loop.getBody()->walk([&](Operation *op) {
    RawAccess ra;
    ra.access.op = op;
    Value mem;
    if (auto read = dyn_cast<AffineReadOpInterface>(op)) {
      mem = read.getMemRef();
      analyzeAddress(read.getAffineMap(), read.getMapOperands(), loop, terms,
                     ra.access, ra.loopInvariant);
    } else if (auto write = dyn_cast<AffineWriteOpInterface>(op)) {
      mem = write.getMemRef();
      ra.access.isWrite = true;
      analyzeAddress(write.getAffineMap(), write.getMapOperands(), loop, terms,
                     ra.access, ra.loopInvariant);
    } else if (auto load = dyn_cast<memref::LoadOp>(op)) {
      mem = load.getMemRef();
      analyzeAddress(
          AffineMap::getMultiDimIdentityMap(load.getIndices().size(), ctx),
          load.getIndices(), loop, terms, ra.access, ra.loopInvariant);
    } else if (auto store = dyn_cast<memref::StoreOp>(op)) {
      mem = store.getMemRef();
      ra.access.isWrite = true;
      analyzeAddress(
          AffineMap::getMultiDimIdentityMap(store.getIndices().size(), ctx),
          store.getIndices(), loop, terms, ra.access, ra.loopInvariant);
    } else {
      return;
    }
    raw[mem].push_back(std::move(ra));
  });

  for (auto &entry : raw) {
    SmallVector<RawAccess, 8> &accesses = entry.second;
    bool writtenInLoop =
        llvm::any_of(accesses,
                     [](const RawAccess &ra) { return ra.access.isWrite; }) ||
        isWrittenInFlattenedParents(entry.first, loop);

    PipelineRegion region;
    region.loop = loop;
    region.targetII = targetII;
    llvm::StringSet<> seen;
    for (RawAccess &ra : accesses) {
      if (!ra.access.isWrite && ra.loopInvariant && !writtenInLoop)
        continue;
      if (!seen.insert(addressKey(ra.access)).second)
        continue;
      (ra.access.isWrite ? region.writes : region.reads)++;
      region.accesses.push_back(std::move(ra.access));
    }
    if (!region.accesses.empty())
      out[entry.first].push_back(std::move(region));
  }
}

//===----------------------------------------------------------------------===//
// Contention model
//===----------------------------------------------------------------------===//

/// What one memory bank can do in one clock cycle.
struct PortModel {
  unsigned ports;      // accesses of any kind
  unsigned readPorts;  // reads
  unsigned writePorts; // writes
};

/// Worst-case accesses landing in a single bank during one iteration. Each
/// field is its own maximum; they need not be reached by the same bank.
struct BankLoad {
  unsigned reads = 0;
  unsigned writes = 0;
  unsigned total = 0;

  BankLoad &operator+=(const BankLoad &other) {
    reads += other.reads;
    writes += other.writes;
    total += other.total;
    return *this;
  }
  static BankLoad max(const BankLoad &a, const BankLoad &b) {
    BankLoad m;
    m.reads = std::max(a.reads, b.reads);
    m.writes = std::max(a.writes, b.writes);
    m.total = std::max(a.total, b.total);
    return m;
  }
};

struct PartitionChoice {
  unsigned dim;   // 0-based
  int64_t factor; // number of banks along `dim`; == extent means complete
};

static int64_t floorMod(int64_t value, int64_t modulus) {
  int64_t r = value % modulus;
  return r < 0 ? r + modulus : r;
}

/// Upper bound on how many of `accesses` can hit one bank in one iteration
/// once the array is cyclically banked by every entry of `parts`.
///
/// Along a banked dimension the bank of an access is (index mod factor):
///  - every coefficient a multiple of the factor: the bank is a compile-time
///    constant, (constant mod factor);
///  - otherwise the bank rotates with the loop. Accesses whose indices differ
///    by a constant (equal coefficients mod factor) keep a fixed distance, so
///    they share a bank exactly when their constants agree mod factor. With
///    `rotatingAware` only such a residue class is charged to a bank, which
///    assumes a binder that shares a port between mutually exclusive
///    accesses. Without it a rotating access is charged to every bank - that
///    is what MemoryBanking's read-every-bank-and-mux lowering costs, and it
///    matches Vitis answering a plain stencil with an II violation instead of
///    an inferred partition (an assumption worth re-checking per version);
///  - opaque indices may hit any bank.
static BankLoad worstBankLoad(ArrayRef<const Access *> accesses,
                              ArrayRef<PartitionChoice> parts,
                              bool rotatingAware) {
  BankLoad load;
  if (accesses.empty())
    return load;
  if (parts.empty()) {
    for (const Access *access : accesses)
      (access->isWrite ? load.writes : load.reads)++;
    load.total = load.reads + load.writes;
    return load;
  }

  const PartitionChoice &part = parts.front();
  ArrayRef<PartitionChoice> rest = parts.drop_front();

  using Bucket = SmallVector<const Access *, 8>;
  using Signature = SmallVector<std::pair<unsigned, int64_t>, 2>;
  struct RotatingGroup {
    Signature signature;                      // coefficients mod factor
    llvm::MapVector<int64_t, Bucket> classes; // constant mod factor -> accesses
  };
  llvm::MapVector<int64_t, Bucket> fixedBank; // known bank -> accesses
  Bucket anyBank;
  SmallVector<RotatingGroup, 2> groups;

  for (const Access *access : accesses) {
    const LinearIndex &li = access->index[part.dim];
    if (li.opaque) {
      anyBank.push_back(access);
      continue;
    }
    Signature signature;
    for (auto [id, coeff] : li.terms)
      if (int64_t residue = floorMod(coeff, part.factor))
        signature.emplace_back(id, residue);
    int64_t bank = floorMod(li.constant, part.factor);

    if (signature.empty()) {
      fixedBank[bank].push_back(access);
    } else if (!rotatingAware) {
      anyBank.push_back(access);
    } else {
      auto *group = llvm::find_if(groups, [&](const RotatingGroup &g) {
        return g.signature == signature;
      });
      if (group == groups.end()) {
        groups.emplace_back();
        group = &groups.back();
        group->signature = signature;
      }
      group->classes[bank].push_back(access);
    }
  }

  if (fixedBank.empty())
    load = worstBankLoad(anyBank, rest, rotatingAware);
  for (auto &entry : fixedBank) {
    Bucket &bucket = entry.second;
    bucket.append(anyBank.begin(), anyBank.end());
    load = BankLoad::max(load, worstBankLoad(bucket, rest, rotatingAware));
  }
  // Different rotating groups cannot be told apart statically: assume the
  // worst class of each meets in the same bank.
  for (RotatingGroup &group : groups) {
    BankLoad worstClass;
    for (auto &entry : group.classes)
      worstClass = BankLoad::max(
          worstClass, worstBankLoad(entry.second, rest, rotatingAware));
    load += worstClass;
  }
  return load;
}

/// Resource-constrained minimum II: `ports` units serve ports * II operations
/// per iteration of a modulo schedule.
static unsigned resourceMII(const BankLoad &load, const PortModel &pm) {
  uint64_t mii = 1;
  mii =
      std::max(mii, llvm::divideCeil(uint64_t(load.total), uint64_t(pm.ports)));
  mii = std::max(
      mii, llvm::divideCeil(uint64_t(load.reads), uint64_t(pm.readPorts)));
  mii = std::max(
      mii, llvm::divideCeil(uint64_t(load.writes), uint64_t(pm.writePorts)));
  return static_cast<unsigned>(mii);
}

/// The loop a memory's ports hold back the most.
struct PortLimit {
  unsigned excess = 0; // resource MII - target II; 0: the ports keep up
  unsigned mii = 1;
  const PipelineRegion *region = nullptr;
};

/// How far the memory's ports push its worst loop past the target II once it
/// is banked by `parts`.
static PortLimit portLimit(ArrayRef<PipelineRegion> regions,
                           ArrayRef<PartitionChoice> parts, const PortModel &pm,
                           bool rotatingAware) {
  PortLimit limit;
  for (const PipelineRegion &region : regions) {
    SmallVector<const Access *, 16> accesses;
    for (const Access &access : region.accesses)
      accesses.push_back(&access);
    unsigned mii =
        resourceMII(worstBankLoad(accesses, parts, rotatingAware), pm);
    if (mii > region.targetII && mii - region.targetII > limit.excess)
      limit = {mii - region.targetII, mii, &region};
  }
  return limit;
}

/// Beyond this factor nothing changes any more: coefficients and constants
/// are congruent only when equal, so larger factors split nothing further.
static int64_t stableFactorBound(ArrayRef<PipelineRegion> regions,
                                 unsigned dim) {
  int64_t minConst = 0, maxConst = 0, minCoeff = 0, maxCoeff = 0;
  bool first = true;
  for (const PipelineRegion &region : regions) {
    for (const Access &access : region.accesses) {
      const LinearIndex &li = access.index[dim];
      if (li.opaque)
        continue;
      minConst = first ? li.constant : std::min(minConst, li.constant);
      maxConst = first ? li.constant : std::max(maxConst, li.constant);
      first = false;
      for (auto [id, coeff] : li.terms) {
        minCoeff = std::min(minCoeff, coeff);
        maxCoeff = std::max(maxCoeff, coeff);
      }
    }
  }
  return std::max(maxConst - minConst, maxCoeff - minCoeff);
}

struct PartitionPlan {
  SmallVector<PartitionChoice, 2> parts;
  PortLimit before; // with the array in one piece
  PortLimit after;  // with `parts` applied
};

/// Greedy search, one dimension per round: take the (dim, factor) that brings
/// the ports closest to the target II, smallest factor first, until the
/// target is met, `maxDims` dimensions are used, or nothing improves.
static PartitionPlan inferPartition(ArrayRef<PipelineRegion> regions,
                                    ArrayRef<int64_t> shape,
                                    const PortModel &pm, bool rotatingAware,
                                    int64_t maxFactor, unsigned maxDims) {
  PartitionPlan plan;
  plan.before = plan.after = portLimit(regions, {}, pm, rotatingAware);

  while (plan.after.excess > 0 && plan.parts.size() < maxDims) {
    std::optional<PartitionChoice> best;
    PortLimit bestLimit = plan.after;

    for (unsigned dim = 0, rank = shape.size(); dim < rank; ++dim) {
      int64_t extent = shape[dim];
      if (ShapedType::isDynamic(extent) || extent < 2)
        continue;
      if (llvm::any_of(plan.parts,
                       [&](const PartitionChoice &p) { return p.dim == dim; }))
        continue;

      int64_t limit = maxFactor > 0 ? std::min(extent, maxFactor) : extent;
      int64_t scanTo = std::min(
          {limit, stableFactorBound(regions, dim) + 1, kMaxScannedFactor});
      for (int64_t factor = 2; factor <= scanTo; ++factor) {
        SmallVector<PartitionChoice, 2> trial(plan.parts);
        trial.push_back({dim, factor});
        PortLimit trialLimit = portLimit(regions, trial, pm, rotatingAware);
        // On ties the smallest factor wins, then the lowest dimension.
        if (trialLimit.excess < bestLimit.excess ||
            (best && trialLimit.excess == bestLimit.excess &&
             factor < best->factor)) {
          best = PartitionChoice{dim, factor};
          bestLimit = trialLimit;
        }
        if (trialLimit.excess == 0)
          break; // larger factors only cost more banks
      }
    }

    if (!best)
      break;
    plan.parts.push_back(*best);
    plan.after = bestLimit;
  }
  return plan;
}

//===----------------------------------------------------------------------===//
// IR plumbing
//===----------------------------------------------------------------------===//

/// Target II a user asked for on this loop, if any. Accepts
/// `hls.pipeline = {ii = N}` or `[{ii = N}]`.
static std::optional<unsigned> getUserTargetII(AffineForOp loop) {
  Attribute attr = loop->getAttr(kPipelineAttr);
  if (auto array = dyn_cast_or_null<ArrayAttr>(attr))
    attr = array.empty() ? Attribute() : array[0];
  auto dict = dyn_cast_or_null<DictionaryAttr>(attr);
  if (!dict)
    return std::nullopt;
  for (StringRef key : {"ii", "II"})
    if (auto ii = dict.getAs<IntegerAttr>(key))
      if (ii.getInt() > 0)
        return static_cast<unsigned>(ii.getInt());
  return std::nullopt;
}

/// MemoryBanking can only rewrite loads and stores (and returns); anything
/// else holding the memref - a call, a cast, a copy - would be left dangling.
static bool hasOnlyBankableUses(Value mem) {
  for (OpOperand &use : mem.getUses()) {
    Operation *user = use.getOwner();
    if (auto read = dyn_cast<AffineReadOpInterface>(user)) {
      if (read.getMemRef() == mem)
        continue;
    } else if (auto write = dyn_cast<AffineWriteOpInterface>(user)) {
      if (write.getMemRef() == mem && write.getValueToStore() != mem)
        continue;
    } else if (isa<memref::LoadOp>(user)) {
      continue;
    } else if (auto store = dyn_cast<memref::StoreOp>(user)) {
      if (store.getMemRef() == mem && store.getValueToStore() != mem)
        continue;
    } else if (isa<func::ReturnOp>(user)) {
      continue;
    }
    return false;
  }
  return true;
}

static StringRef kindName(const PartitionChoice &part,
                          ArrayRef<int64_t> shape) {
  return part.factor == shape[part.dim] ? "complete" : "cyclic";
}

/// Same encoding as a user pragma, tagged with a provenance string (`source`)
/// so user and inferred partitions stay distinguishable.
static ArrayAttr buildPartitionAttr(Builder &b, ArrayRef<PartitionChoice> parts,
                                    ArrayRef<int64_t> shape,
                                    StringAttr varName,
                                    StringRef source = kSourcePressure) {
  SmallVector<Attribute, 2> entries;
  for (const PartitionChoice &part : parts) {
    SmallVector<NamedAttribute, 5> fields;
    // Vitis numbers dimensions from 1; getPartitionSpec() subtracts it again.
    fields.push_back(b.getNamedAttr("dim", b.getI32IntegerAttr(part.dim + 1)));
    fields.push_back(b.getNamedAttr(
        "factor", b.getI32IntegerAttr(static_cast<int32_t>(part.factor))));
    fields.push_back(
        b.getNamedAttr("kind", b.getStringAttr(kindName(part, shape))));
    fields.push_back(b.getNamedAttr("source", b.getStringAttr(source)));
    if (varName)
      fields.push_back(b.getNamedAttr("variable", varName));
    entries.push_back(b.getDictionaryAttr(fields));
  }
  return b.getArrayAttr(entries);
}

/// One line for `hls.partition_reason`: the loop whose port demand drove the
/// decision, its per-iteration access counts, the target II and the factor.
static std::string describePartitionReason(const PartitionPlan &plan,
                                           const PipelineRegion &region,
                                           ArrayRef<int64_t> shape) {
  std::string s;
  llvm::raw_string_ostream os(s);
  AffineForOp loop = region.loop;
  os << "pipelined loop";
  if (loop.hasConstantBounds())
    os << " [" << loop.getConstantLowerBound() << ".."
       << loop.getConstantUpperBound() << " step " << loop.getStepAsInt()
       << ")";
  os << " @ ";
  if (auto fileLoc = dyn_cast<FileLineColLoc>(loop.getLoc()))
    os << fileLoc.getFilename().getValue() << ":" << fileLoc.getLine() << ":"
       << fileLoc.getColumn();
  else
    loop.getLoc().print(os);
  os << ": " << region.reads << " reads/" << region.writes
     << " writes per iteration, target II " << region.targetII << ", factor ";
  llvm::interleave(
      plan.parts, os,
      [&](const PartitionChoice &part) {
        os << part.factor << " (" << kindName(part, shape) << ", dim "
           << part.dim + 1 << ")";
      },
      " x ");
  os << " (port-limited II " << plan.before.mii << " -> " << plan.after.mii
     << ")";
  return s;
}

static ArrayAttr buildPressureAttr(Builder &b,
                                   ArrayRef<PipelineRegion> regions) {
  SmallVector<Attribute, 2> entries;
  for (const PipelineRegion &region : regions)
    entries.push_back(b.getDictionaryAttr(
        {b.getNamedAttr("ii", b.getI32IntegerAttr(region.targetII)),
         b.getNamedAttr("reads", b.getI32IntegerAttr(region.reads)),
         b.getNamedAttr("writes", b.getI32IntegerAttr(region.writes))}));
  return b.getArrayAttr(entries);
}

//===----------------------------------------------------------------------===//
// Automatic partitions independent of throughput (td=off rules (a)-(c))
//===----------------------------------------------------------------------===//

// What counts as a constant index (an integer constant, also through an index
// cast, or the counter of a loop that runs exactly once) is defined once, in
// ConstantIndex.h, and memory banking resolves exactly the same indices to a
// constant bank: a dimension split here because only constants index it is
// then read one bank at a time.

/// Per memref dimension: whether the access's index is a constant.
static SmallVector<bool> constantDimsOfAffine(AffineMap map,
                                              ValueRange mapOperands) {
  SmallVector<Value, 8> operands(mapOperands.begin(), mapOperands.end());
  // Through affine.apply producers (unrolling leaves `apply (d0 + 1)(%c0)`).
  fullyComposeAffineMapAndOperands(&map, &operands);
  AffineMap folded = foldConstantIndexOperands(map, operands);
  SmallVector<bool> dims;
  for (AffineExpr expr : folded.getResults())
    dims.push_back(isa<AffineConstantExpr>(expr));
  return dims;
}

static SmallVector<bool> constantDimsOfIndices(ValueRange indices) {
  SmallVector<bool> dims;
  for (Value idx : indices)
    dims.push_back(getConstantIndexValue(idx).has_value());
  return dims;
}

/// What the accesses of one array say about constant indices.
struct ConstantIndexInfo {
  /// Every use is a plain load or store whose indices could be read; false
  /// when the array escapes (call, cast, view, return) or is accessed by an
  /// op this analysis does not know: then nothing is concluded.
  bool complete = true;
  unsigned accesses = 0;
  /// Of those, affine.load / affine.store. Memory banking only splits an
  /// array that has at least one (collectMemRefs in MemoryBankModified.cpp);
  /// it then rewrites its memref.load / memref.store as well.
  unsigned affineAccesses = 0;
  /// Per dimension: every access indexes it with a constant.
  SmallVector<bool> constantDim;
};

static ConstantIndexInfo analyzeConstantIndices(Value mem, unsigned rank) {
  ConstantIndexInfo info;
  info.constantDim.assign(rank, true);
  for (OpOperand &use : mem.getUses()) {
    Operation *user = use.getOwner();
    SmallVector<bool> dims;
    if (auto load = dyn_cast<AffineLoadOp>(user)) {
      dims = constantDimsOfAffine(load.getAffineMap(), load.getMapOperands());
      ++info.affineAccesses;
    } else if (auto store = dyn_cast<AffineStoreOp>(user);
               store && store.getMemRef() == mem &&
               store.getValueToStore() != mem) {
      dims = constantDimsOfAffine(store.getAffineMap(),
                                  store.getMapOperands());
      ++info.affineAccesses;
    } else if (auto load = dyn_cast<memref::LoadOp>(user)) {
      dims = constantDimsOfIndices(load.getIndices());
    } else if (auto store = dyn_cast<memref::StoreOp>(user);
               store && store.getMemRef() == mem &&
               store.getValueToStore() != mem) {
      dims = constantDimsOfIndices(store.getIndices());
    } else {
      info.complete = false;
      return info;
    }
    if (dims.size() != rank) {
      info.complete = false;
      return info;
    }
    ++info.accesses;
    for (unsigned d = 0; d < rank; ++d)
      info.constantDim[d] = info.constantDim[d] && dims[d];
  }
  return info;
}

/// The decision for one array under rules (a)-(c).
struct AutomaticPartition {
  enum Kind { None, Registers, ConstantDims } kind = None;
  SmallVector<PartitionChoice, 2> parts; // ConstantDims: complete, per dim
  std::string reason;
  /// None although rule (b) applies: memory banking could not split the
  /// array (no affine access), so no spec is written. `reason` says why.
  bool unbankable = false;
};

static AutomaticPartition decideAutomaticPartition(memref::AllocaOp alloca,
                                                   int64_t completeThreshold) {
  AutomaticPartition decision;
  MemRefType ty = alloca.getType();
  if (!ty.hasStaticShape())
    return decision;
  Type elt = ty.getElementType();
  if (!elt.isIntOrFloat() && !isa<IndexType>(elt))
    return decision; // pointer variables, structs: not an array of words
  Operation *def = alloca.getOperation();
  for (StringRef pragma : kUserStoragePragmas)
    if (def->hasAttr(pragma))
      return decision; // the user decided

  // (a) Small arrays, whatever their accesses (also those passed on to a
  // call): complete_threshold counts elements, not bits (int[4] fires,
  // char[5] does not; partition_chk.md R5).
  int64_t elements = ty.getNumElements();
  if (elements > 0 && elements <= completeThreshold) {
    decision.kind = AutomaticPartition::Registers;
    decision.reason = std::to_string(elements) +
                      " element(s) <= complete-threshold " +
                      std::to_string(completeThreshold) +
                      ": completely partitioned into registers (Vitis [HLS "
                      "214-421] 'Automatically partitioning small array ... "
                      "completely based on array size')";
    return decision;
  }

  unsigned rank = ty.getRank();
  ConstantIndexInfo info = analyzeConstantIndices(alloca.getResult(), rank);
  if (!info.complete || info.accesses == 0)
    return decision; // escapes, or nothing to look at (dead: not ours)

  // (c) Every access constant in every dimension: scalarised.
  if (llvm::all_of(info.constantDim, [](bool c) { return c; })) {
    decision.kind = AutomaticPartition::Registers;
    decision.reason = "every one of the " + std::to_string(info.accesses) +
                      " access(es) uses a constant index in every dimension: "
                      "scalarised into registers (Vitis front end, alloca "
                      "gone in a.o.1; partition.md R5)";
    return decision;
  }

  // (b) Dimensions that only ever see constants, extent >= 2.
  for (unsigned d = 0; d < rank; ++d)
    if (info.constantDim[d] && ty.getDimSize(d) >= 2)
      decision.parts.push_back({d, ty.getDimSize(d)});
  if (decision.parts.empty())
    return decision;
  std::string dims;
  llvm::raw_string_ostream os(dims);
  llvm::interleave(
      decision.parts, os,
      [&](const PartitionChoice &p) { os << (p.dim + 1); }, ", ");
  if (info.affineAccesses == 0) {
    // Vitis would split it, but memory banking never rewrites an array
    // without an affine access: a spec would only be priced as one memory
    // carrying a partition nobody applied. Leave it whole, and say so.
    decision.parts.clear();
    decision.unbankable = true;
    decision.reason = "every one of the " + std::to_string(info.accesses) +
                      " access(es) indexes dimension(s) " + os.str() +
                      " with a constant, but none is an affine access, so "
                      "memory banking cannot split the array: left whole";
    return decision;
  }
  decision.kind = AutomaticPartition::ConstantDims;
  decision.reason = "every one of the " + std::to_string(info.accesses) +
                    " access(es) indexes dimension(s) " + os.str() +
                    " with a constant: complete partition (Vitis [HLS "
                    "214-449] 'Automatically partitioning array ... dimension "
                    "d completely based on constant index')";
  if (decision.parts.size() > 1)
    decision.reason += "; memory banking applies only the first entry";
  return decision;
}

//===----------------------------------------------------------------------===//
// Pass
//===----------------------------------------------------------------------===//

struct InferVitisSplitArray
    : public PassWrapper<InferVitisSplitArray, OperationPass<func::FuncOp>> {
  MLIR_DEFINE_EXPLICIT_INTERNAL_INLINE_TYPE_ID(InferVitisSplitArray)

  InferVitisSplitArray() = default;
  InferVitisSplitArray(const InferVitisSplitArray &other)
      : PassWrapper(other) {}

  Option<unsigned> targetII{
      *this, "target-ii",
      llvm::cl::desc("Target initiation interval of pipelined loops that do "
                     "not carry their own hls.pipeline II"),
      llvm::cl::init(1)};
  Option<bool> autoPipeline{
      *this, "auto-pipeline",
      llvm::cl::desc("Treat every innermost loop as pipelined: what Vitis' "
                     "config_compile -pipeline_loops amounts to once "
                     "auto-pipeline-unroll has dissolved the small inner "
                     "loops. Off: only loops carrying hls.pipeline"),
      llvm::cl::init(true)};
  // Defaults are one read port and one write port per bank, which gives
  // factor = max(reads, writes) / II and the partitions Vitis was seen to
  // infer. read-ports=2 models both ports of a RAM_2P/RAM_T2P serving reads
  // (half the factor); write-ports=2 a RAM_T2P.
  Option<unsigned> readPorts{*this, "read-ports",
                             llvm::cl::desc("Reads one bank serves per cycle"),
                             llvm::cl::init(1)};
  Option<unsigned> writePorts{
      *this, "write-ports", llvm::cl::desc("Writes one bank serves per cycle"),
      llvm::cl::init(1)};
  Option<unsigned> ports{
      *this, "ports",
      llvm::cl::desc("Accesses of any kind one bank serves per cycle"),
      llvm::cl::init(2)};
  Option<unsigned> maxFactor{
      *this, "max-factor",
      llvm::cl::desc("Largest factor to infer (0: the dimension extent)"),
      llvm::cl::init(0)};
  Option<unsigned> maxDims{
      *this, "max-dims",
      llvm::cl::desc("Dimensions that may be partitioned per array. Memory "
                     "banking consumes one spec per array, so keep 1 unless "
                     "the consumer handles several entries"),
      llvm::cl::init(1)};
  Option<bool> rotatingBanks{
      *this, "rotating-banks",
      llvm::cl::desc("Also split arrays whose contending accesses only "
                     "separate dynamically (a[i], a[i+1] with i the pipelined "
                     "counter). Assumes ports are shared between mutually "
                     "exclusive bank accesses"),
      llvm::cl::init(false)};
  Option<bool> includePorts{
      *this, "include-ports",
      llvm::cl::desc("Also annotate array function arguments (as argument "
                     "attributes). Off, like Vitis' -include_ports"),
      llvm::cl::init(false)};
  Option<bool> annotatePressure{
      *this, "annotate-pressure",
      llvm::cl::desc("Record hls.port_pressure = [{ii, reads, writes}] (one "
                     "entry per pipelined loop) on every analysed array"),
      llvm::cl::init(true)};
  Option<bool> emitRemarks{
      *this, "emit-remarks",
      llvm::cl::desc("Print a Vitis-style 'Inferring pragma' remark per "
                     "decision, and one for every loop left port-limited"),
      llvm::cl::init(false)};
  Option<std::string> throughputDriven{
      *this, "td",
      llvm::cl::desc("Vitis syn.array_partition.throughput_driven. 'auto' "
                     "(default): partitions from port pressure. 'off': only "
                     "the automatic partitions Vitis still makes with "
                     "throughput_driven=off - arrays of at most "
                     "complete-threshold elements and arrays indexed only by "
                     "constants become registers (hls.registers), a "
                     "dimension indexed only by constants is completely "
                     "partitioned (VITIS_NOTES.md N7)"),
      llvm::cl::init("auto")};
  Option<bool> autoPartitions{
      *this, "auto-partitions",
      llvm::cl::desc("With td=auto, also apply the automatic partitions of "
                     "td=off (small arrays, constant indices) before the "
                     "port-pressure inference, as Vitis does in both modes. "
                     "Off by default so that td=auto keeps its earlier "
                     "output; always on with td=off"),
      llvm::cl::init(false)};
  Option<unsigned> completeThreshold{
      *this, "complete-threshold",
      llvm::cl::desc("Vitis syn.array_partition.complete_threshold: arrays "
                     "with at most this many elements become registers under "
                     "the automatic partitions (Vitis default 4)"),
      llvm::cl::init(4)};

  Statistic numRegions{this, "pipelined-loops", "Pipelined loops analysed"};
  Statistic numPartitioned{this, "arrays-partitioned",
                           "Arrays given an inferred partition"};
  Statistic numUnresolved{this, "arrays-still-limited",
                          "Arrays whose ports still limit a loop's II"};
  Statistic numRegisters{this, "arrays-registers",
                         "Arrays turned into registers (small or all "
                         "constant indices)"};
  Statistic numConstantDims{this, "arrays-constant-index",
                            "Arrays completely partitioned on a dimension "
                            "indexed only by constants"};
  Statistic numMultiConstantDims{
      this, "arrays-constant-index-multi",
      "Arrays with more than one constant-indexed dimension (banking applies "
      "the first)"};
  Statistic numUnbankable{
      this, "arrays-constant-index-unbanked",
      "Arrays with a constant-indexed dimension left whole because they have "
      "no affine access for memory banking to split"};

  StringRef getArgument() const final { return "infer-vitis-split-array"; }
  StringRef getDescription() const final {
    return "Infer hls.array_partition for arrays whose memory ports limit the "
           "II of a pipelined loop (td=auto), or only Vitis' automatic "
           "small-array / constant-index partitions (td=off)";
  }

  /// Rules (a)-(c) on every local array of `func`. Returns the arrays they
  /// decided, which the port-pressure inference then leaves alone.
  DenseSet<Value> applyAutomaticPartitions(func::FuncOp func) {
    DenseSet<Value> decided;
    Builder builder(&getContext());
    func.walk([&](memref::AllocaOp alloca) {
      Operation *def = alloca.getOperation();
      if (def->hasAttr(kRegistersAttrName)) {
        decided.insert(alloca.getResult());
        return;
      }
      AutomaticPartition decision =
          decideAutomaticPartition(alloca, completeThreshold);
      auto varName = def->getAttrOfType<StringAttr>(kVarNameAttr);
      std::string name =
          varName ? varName.getValue().str() : std::string("<unnamed>");
      if (decision.unbankable) {
        ++numUnbankable;
        LLVM_DEBUG(llvm::dbgs() << "array '" << name << "': "
                                << decision.reason << "\n");
        if (emitRemarks)
          mlir::emitRemark(alloca.getLoc())
              << "array '" << name << "' left whole: " << decision.reason;
      }
      if (decision.kind == AutomaticPartition::None)
        return;
      decided.insert(alloca.getResult());
      if (decision.kind == AutomaticPartition::Registers) {
        def->setAttr(kRegistersAttrName, builder.getUnitAttr());
        def->setAttr(kRegistersReasonAttrName,
                     builder.getStringAttr(decision.reason));
        ++numRegisters;
        LLVM_DEBUG(llvm::dbgs() << "array '" << name
                                << "': registers (" << decision.reason
                                << ")\n");
        if (emitRemarks)
          mlir::emitRemark(alloca.getLoc())
              << "array '" << name << "' -> registers: " << decision.reason;
        return;
      }
      ArrayRef<int64_t> shape = alloca.getType().getShape();
      def->setAttr(kPartitionAttr,
                   buildPartitionAttr(builder, decision.parts, shape, varName,
                                      kSourceConstantIndex));
      def->setAttr(kReasonAttr, builder.getStringAttr(decision.reason));
      ++numConstantDims;
      if (decision.parts.size() > 1)
        ++numMultiConstantDims;
      LLVM_DEBUG(llvm::dbgs() << "array '" << name << "': "
                              << decision.reason << "\n");
      if (emitRemarks)
        for (const PartitionChoice &part : decision.parts)
          mlir::emitRemark(alloca.getLoc())
              << "Automatically partitioning array '" << name
              << "' dimension " << part.dim + 1
              << " completely based on constant index";
    });
    return decided;
  }

  /// Target II of `loop` if it is a pipelined region.
  ///
  /// The pass runs after auto-pipeline-unroll, and by then Vitis' rule ("the
  /// innermost loop is pipelined if its trip count exceeds the threshold,
  /// otherwise its parent is, with the inner loop unrolled") has a simple
  /// shape: every innermost loop still standing is pipelined. There is no way
  /// to tell a small loop that was never unrolled from a loop that has just
  /// swallowed its unrolled children, so no trip count is consulted here.
  std::optional<unsigned> getPipelineII(AffineForOp loop) {
    bool userPipelined = loop->hasAttr(kPipelineAttr);
    if (loop->hasAttr(kPipelineOffAttr) || (!userPipelined && !autoPipeline))
      return std::nullopt;
    if (getConstantTripCount(loop) == uint64_t(0))
      return std::nullopt;

    // Pipelining a loop unrolls everything inside it, so a loop below a user
    // pipeline is part of that region, not one of its own.
    for (auto parent = loop->getParentOfType<AffineForOp>(); parent;
         parent = parent->getParentOfType<AffineForOp>())
      if (parent->hasAttr(kPipelineAttr) && !parent->hasAttr(kPipelineOffAttr))
        return std::nullopt;

    bool hasNestedLoop = false;
    loop.getBody()->walk([&](LoopLikeOpInterface) {
      hasNestedLoop = true;
      return WalkResult::interrupt();
    });
    if (hasNestedLoop) {
      // Accesses are counted as they stand in the body; counting through a
      // loop that is still there would under-report them.
      if (userPipelined)
        mlir::emitWarning(loop.getLoc())
            << "hls.pipeline on a loop that still contains loops: unroll them "
               "before infer-vitis-split-array; nothing is inferred from it";
      return std::nullopt;
    }
    return getUserTargetII(loop).value_or(targetII);
  }

  void runOnOperation() override {
    func::FuncOp func = getOperation();
    if (func.isExternal())
      return;
    if (targetII == 0 || ports == 0 || readPorts == 0 || writePorts == 0 ||
        maxDims == 0) {
      func.emitError("infer-vitis-split-array: target-ii, ports, read-ports, "
                     "write-ports and max-dims must be positive");
      return signalPassFailure();
    }
    if (throughputDriven != "auto" && throughputDriven != "off") {
      func.emitError("infer-vitis-split-array: td must be 'auto' or 'off', "
                     "got '")
          << throughputDriven << "'";
      return signalPassFailure();
    }
    bool tdOff = throughputDriven == "off";
    PortModel pm{ports, readPorts, writePorts};

    // 0. Vitis' automatic partitions that do not depend on throughput.
    DenseSet<Value> decided;
    if (tdOff || autoPartitions)
      decided = applyAutomaticPartitions(func);

    // 1. Port pressure per (memory, pipelined loop).
    TermTable terms;
    llvm::MapVector<Value, SmallVector<PipelineRegion, 2>> pressure;
    func.walk([&](AffineForOp loop) {
      if (std::optional<unsigned> ii = getPipelineII(loop)) {
        ++numRegions;
        collectRegions(loop, *ii, terms, pressure);
      }
    });

    // 2. One decision per memory, over all the loops that touch it.
    Builder builder(&getContext());
    for (auto &entry : pressure) {
      Value mem = entry.first;
      ArrayRef<PipelineRegion> regions = entry.second;
      Operation *def = mem.getDefiningOp();
      auto arg = dyn_cast<BlockArgument>(mem);
      bool isFuncArg = arg && arg.getOwner() == &func.getBody().front();

      if (annotatePressure) {
        ArrayAttr attr = buildPressureAttr(builder, regions);
        if (def)
          def->setAttr(kPressureAttr, attr);
        else if (isFuncArg)
          func.setArgAttr(arg.getArgNumber(), kPressureAttr, attr);
      }

      // td=off: Vitis replicates instead of partitioning (RAM_1WNR), which
      // --bram-analysis prices; an array (a)-(c) decided is settled.
      if (tdOff || decided.contains(mem))
        continue;

      auto memTy = dyn_cast<MemRefType>(mem.getType());
      if (!memTy || memTy.getRank() == 0)
        continue;
      ArrayRef<int64_t> shape = memTy.getShape();
      if (portLimit(regions, {}, pm, rotatingBanks).excess == 0)
        continue; // the ports keep up with every loop as it is

      // Where the spec lives, and whether a user already wrote one.
      auto iface = dyn_cast_or_null<MemoryResourceOpInterface>(def);
      bool canAnnotate = iface || (isFuncArg && includePorts);
      bool hasUserSpec =
          iface ? (iface.getPartitionSpec().has_value() ||
                   def->hasAttr(kPartitionAttr))
                : (isFuncArg && func.getArgAttr(arg.getArgNumber(),
                                                kPartitionAttr) != nullptr);
      auto varName =
          def ? def->getAttrOfType<StringAttr>(kVarNameAttr) : StringAttr();
      std::string name = varName ? varName.getValue().str()
                         : isFuncArg
                             ? "arg" + std::to_string(arg.getArgNumber())
                             : std::string("<unnamed>");
      Location loc = def ? def->getLoc() : mem.getLoc();

      if (hasUserSpec)
        continue; // the user's pragma stands, whatever it achieves
      StringRef obstacle;
      if (!canAnnotate)
        obstacle = isFuncArg ? "interface array (see include-ports)"
                             : "not defined by a partitionable op";
      else if (!hasOnlyBankableUses(mem))
        obstacle = "it has users other than loads and stores";
      else if (llvm::none_of(shape, [](int64_t extent) {
                 return !ShapedType::isDynamic(extent) && extent > 1;
               }))
        obstacle = "no dimension of known extent to split";
      if (!obstacle.empty()) {
        ++numUnresolved;
        if (emitRemarks)
          mlir::emitRemark(loc)
              << "array '" << name
              << "' limits a pipelined loop but is left alone: " << obstacle;
        continue;
      }

      PartitionPlan plan =
          inferPartition(regions, shape, pm, rotatingBanks, maxFactor, maxDims);

      if (!plan.parts.empty()) {
        ArrayAttr spec =
            buildPartitionAttr(builder, plan.parts, shape, varName);
        if (def)
          def->setAttr(kPartitionAttr, spec);
        else
          func.setArgAttr(arg.getArgNumber(), kPartitionAttr, spec);
        ++numPartitioned;

        // Record why, for the debug report: the loop the ports held back the
        // most before partitioning is the one that drove the factor.
        if (plan.before.region) {
          StringAttr reason = builder.getStringAttr(
              describePartitionReason(plan, *plan.before.region, shape));
          if (def)
            def->setAttr(kReasonAttr, reason);
          else
            func.setArgAttr(arg.getArgNumber(), kReasonAttr, reason);
        }

        for (const PartitionChoice &part : plan.parts) {
          LLVM_DEBUG(llvm::dbgs()
                     << "array '" << name << "': " << kindName(part, shape)
                     << " factor=" << part.factor << " dim=" << part.dim + 1
                     << " (port-limited II " << plan.before.mii << " -> "
                     << plan.after.mii << ")\n");
          if (emitRemarks)
            mlir::emitRemark(loc)
                << "Inferring pragma 'array_partition type="
                << kindName(part, shape) << " factor=" << part.factor
                << " dim=" << part.dim + 1 << "' for array '" << name
                << "' due to pipeline pragma";
        }
      }

      if (plan.after.excess > 0) {
        ++numUnresolved;
        if (emitRemarks) {
          const PipelineRegion &worst = *plan.after.region;
          AffineForOp worstLoop = worst.loop; // getLoc() is non-const
          InFlightDiagnostic diag =
              mlir::emitRemark(loc)
              << "array '" << name
              << "' limits a pipelined loop to II = " << plan.after.mii
              << " (target " << worst.targetII << ")"
              << (plan.parts.empty() ? ": no partition separates its accesses"
                                     : " even with the inferred partition");
          diag.attachNote(worstLoop.getLoc())
              << worst.reads << " read(s) and " << worst.writes
              << " write(s) per iteration of this loop";
        }
      }
    }
  }
};

} // namespace

namespace circt::hls_analysis {

std::unique_ptr<mlir::Pass> createInferVitisSplitArray() {
  return std::make_unique<InferVitisSplitArray>();
}

void registerInferVitisSplitArray() {
  ::mlir::PassRegistration<InferVitisSplitArray>();
}

} // namespace circt::hls_analysis
