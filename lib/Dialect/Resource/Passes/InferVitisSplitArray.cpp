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
#include "../Plugins/Builtin/Builtins.h"
#include "circt/Dialect/Resource/Plugins/PassPolicies.h"
#include "circt/Dialect/Resource/Plugins/Registry.h"
#include "circt/Dialect/Resource/Passes/InferVitisSplitArray.h"
#include "circt/Dialect/Resource/Config/ConfigUtils.h"
#include "circt/Dialect/Resource/Passes/ConstantIndex.h"
#include "circt/Dialect/Resource/Passes/LoopPragmas.h"
#include "circt/Dialect/Resource/Passes/PolygeistCompat.h"
#include "mlir/Dialect/Affine/Analysis/LoopAnalysis.h"
#include "mlir/Dialect/Affine/IR/AffineOps.h"
#include "mlir/Dialect/Arith/IR/Arith.h"
#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/Dialect/MemRef/IR/MemRef.h"
#include "mlir/Dialect/SCF/IR/SCF.h"
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
// The attributes by which the user decided an array's storage
// (frontend.user_storage_pragmas: hls.array_partition, hls.array_reshape,
// hls.bind_storage, hls.stream).

// Factors above tool.hls.partitioning.inference.max_scanned_factor (65536)
// are never scanned one by one. Purely a guard against degenerate inputs
// (a[i] next to a[i + 2^40]); real factors are tiny.

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

  LoopLikeOpInterface root = getFlattenedRoot(loop);
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
  LoopLikeOpInterface root = getFlattenedRoot(loop);
  if (root.getOperation() == loop.getOperation())
    return false;
  bool written = false;
  root->walk([&](Operation *op) {
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
                                    int64_t maxFactor, unsigned maxDims,
                                    int64_t maxScannedFactor) {
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
          {limit, stableFactorBound(regions, dim) + 1, maxScannedFactor});
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

/// Per memref dimension: whether the access's index is a constant. On a
/// dimension d with blockSizes[d] = B > 1 (a user block partition), the
/// offset inside the block counts instead: the index modulo B is a constant
/// (VITIS_NOTES N104: `j = 8 * jj + u` with B = 4).
static SmallVector<bool>
constantDimsOfAffine(AffineMap map, ValueRange mapOperands,
                     ArrayRef<int64_t> blockSizes = {}) {
  SmallVector<Value, 8> operands(mapOperands.begin(), mapOperands.end());
  // Through affine.apply producers (unrolling leaves `apply (d0 + 1)(%c0)`).
  fullyComposeAffineMapAndOperands(&map, &operands);
  AffineMap folded = foldConstantIndexOperands(map, operands);
  SmallVector<bool> dims;
  // A partially unrolled loop keeps its step (`for j = 0 to 64 step 8`,
  // copies at j + u): its counter is lb + step * k, which the modulo below
  // must see.
  SmallVector<AffineExpr> counters;
  for (unsigned i = 0; i < folded.getNumDims(); ++i) {
    AffineExpr dim = getAffineDimExpr(i, map.getContext());
    if (i < operands.size())
      if (AffineForOp loop = getForInductionVarOwner(operands[i]))
        if (loop.hasConstantLowerBound() && loop.getStepAsInt() > 1)
          dim = dim * loop.getStepAsInt() + loop.getConstantLowerBound();
    counters.push_back(dim);
  }
  for (auto [d, expr] : llvm::enumerate(folded.getResults())) {
    bool constant = isa<AffineConstantExpr>(expr);
    if (!constant && d < blockSizes.size() && blockSizes[d] > 1)
      constant = isa<AffineConstantExpr>(simplifyAffineExpr(
          expr.replaceDims(counters) % blockSizes[d], folded.getNumDims(),
          folded.getNumSymbols()));
    dims.push_back(constant);
  }
  return dims;
}

/// Whether a user array_partition of `def` is `complete` on every dimension
/// of `ty` (dim=0, or one complete entry per dimension).
static bool userCompleteEveryDim(Operation *def, MemRefType ty) {
  auto entries = def->getAttrOfType<ArrayAttr>(kPartitionAttr);
  if (!entries)
    return false;
  SmallVector<bool> complete(ty.getRank(), false);
  for (Attribute a : entries) {
    auto entry = dyn_cast<DictionaryAttr>(a);
    auto dim = entry ? entry.getAs<IntegerAttr>("dim") : IntegerAttr();
    auto kind = entry ? entry.getAs<StringAttr>("kind") : StringAttr();
    if (!dim || !kind || kind.getValue() != "complete")
      continue;
    for (int64_t d = 0; d < ty.getRank(); ++d)
      if (dim.getInt() == d + 1 || dim.getInt() == 0)
        complete[d] = true;
  }
  return llvm::all_of(complete, [](bool c) { return c; });
}

/// Per dimension of `def` (type `ty`): the block size of a user block
/// array_partition on it, 0 without one (N104).
static SmallVector<int64_t> userBlockSizes(Operation *def, MemRefType ty) {
  SmallVector<int64_t> sizes(ty.getRank(), 0);
  auto entries = def->getAttrOfType<ArrayAttr>(kPartitionAttr);
  if (!entries || !ty.hasStaticShape())
    return sizes;
  for (Attribute a : entries) {
    auto entry = dyn_cast<DictionaryAttr>(a);
    auto dim = entry ? entry.getAs<IntegerAttr>("dim") : IntegerAttr();
    auto kind = entry ? entry.getAs<StringAttr>("kind") : StringAttr();
    auto factor = entry ? entry.getAs<IntegerAttr>("factor") : IntegerAttr();
    if (!dim || !kind || !factor || factor.getInt() <= 1 ||
        kind.getValue() != "block")
      continue;
    for (int64_t d = 0; d < ty.getRank(); ++d)
      if (dim.getInt() == d + 1 || dim.getInt() == 0) {
        int64_t extent = ty.getDimSize(d);
        sizes[d] = (extent + factor.getInt() - 1) / factor.getInt();
      }
  }
  return sizes;
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
  /// Some accesses were reached through an element / row view
  /// (polygeist.subindex, memref.cast) passed to a callee: memory banking
  /// does not split through such views, so only rule (c) may follow.
  bool throughViews = false;
};

/// Whether `store` writes a constant under the first-call guard of a static
/// (an scf.if on the `<static>@init` flag global cgeist emits): the static's
/// constant initialiser, not an access. A C++ static whose constructor is a
/// constant expression (`static complex<float> buf[..]`) is constant-
/// initialised by Vitis' clang (the initial value of the global, no code),
/// so these stores do not stop rule (b) (VITIS_NOTES N77: hp_fft_hls
/// `data_rev_stream`, 214-449 in the Vitis log).
static bool isStaticInitStore(Operation *store, Value stored) {
  if (!stored.getDefiningOp<arith::ConstantOp>())
    return false;
  for (auto ifOp = store->getParentOfType<scf::IfOp>(); ifOp;
       ifOp = ifOp->getParentOfType<scf::IfOp>()) {
    Operation *def = ifOp.getCondition().getDefiningOp();
    Value flag;
    if (auto ld = dyn_cast_or_null<AffineLoadOp>(def))
      flag = ld.getMemRef();
    else if (auto ld = dyn_cast_or_null<memref::LoadOp>(def))
      flag = ld.getMemRef();
    if (auto gg = flag ? flag.getDefiningOp<memref::GetGlobalOp>()
                       : memref::GetGlobalOp())
      if (gg.getName().ends_with("@init"))
        return true;
  }
  return false;
}

/// Whether rule (b) / (c) follows element and row views passed to callees
/// (key tool.hls.partitioning.constant_index.through_views).
static bool viewsFollowed() {
  return circt::hlsest::Config::get()
      .tool.hls.partitioning.constantIndexThroughViews;
}

/// The uses of `mem` (an array, or a callee parameter it reaches) into
/// `info`. With `throughCalls`, a call passing the array is followed into
/// the callee's parameter, whose accesses count as the array's (VITIS_NOTES
/// N94: Vitis decides rule (b) over the accesses in the inline-off callees
/// and dataflow processes the array is passed to); otherwise, or for a
/// callee without a body, the call stops the analysis.
static void analyzeConstantIndexUses(Value mem, unsigned rank,
                                     bool throughCalls,
                                     ConstantIndexInfo &info,
                                     SmallPtrSetImpl<Value> &visited,
                                     ArrayRef<int64_t> blockSizes) {
  if (!visited.insert(mem).second)
    return;
  for (OpOperand &use : mem.getUses()) {
    Operation *user = use.getOwner();
    SmallVector<bool> dims;
    // A view of the array taken for a reference / pointer parameter (`f(a[i])`
    // with `T &`, or a cast to a dynamic shape): its accesses are the
    // array's (VITIS_NOTES N94 through the view; Dehazing's vals_tmp elements
    // passed to compare_and_swap_unit are scalars in Vitis, 214-449).
    if (throughCalls && viewsFollowed()) {
      if (auto cast = dyn_cast<memref::CastOp>(user)) {
        auto to = dyn_cast<MemRefType>(cast.getType());
        if (!to || static_cast<unsigned>(to.getRank()) != rank) {
          info.complete = false;
          return;
        }
        info.throughViews = true;
        analyzeConstantIndexUses(cast.getResult(), rank, throughCalls, info,
                                 visited, blockSizes);
        if (!info.complete)
          return;
        continue;
      }
      if (auto sub = dyn_cast<circt::hls_analysis::SubIndexOp>(user);
          sub && sub.getSource() == mem &&
          (sub.isElementView() || sub.isRowSelect())) {
        auto to = cast<MemRefType>(sub.getType());
        unsigned viewRank = static_cast<unsigned>(to.getRank());
        ConstantIndexInfo view;
        view.constantDim.assign(viewRank, true);
        analyzeConstantIndexUses(sub.getResult(), viewRank, throughCalls,
                                 view, visited, {});
        if (!view.complete) {
          info.complete = false;
          return;
        }
        info.throughViews = true;
        info.accesses += view.accesses;
        info.affineAccesses += view.affineAccesses;
        bool indexConst = getConstantIndexValue(sub.getIndex()).has_value();
        // Row select: dimension 0 is the view's index, the rest the view's
        // dimensions. Element view: dimension 0 is index + the view's first
        // index, the rest agree.
        bool rowSelect = sub.isRowSelect();
        if (view.accesses) {
          for (unsigned d = 0; d < rank; ++d) {
            bool c;
            if (d == 0)
              c = indexConst && (rowSelect || view.constantDim[0]);
            else
              c = view.constantDim[rowSelect ? d - 1 : d];
            info.constantDim[d] = info.constantDim[d] && c;
          }
        }
        continue;
      }
    }
    if (auto call = dyn_cast<func::CallOp>(user); call && throughCalls) {
      auto callee = dyn_cast_or_null<func::FuncOp>(call.resolveCallable());
      unsigned index = use.getOperandNumber();
      if (!callee || callee.isExternal() ||
          index >= callee.getNumArguments() ||
          callee.getArgument(index).getType() != mem.getType()) {
        info.complete = false;
        return;
      }
      analyzeConstantIndexUses(callee.getArgument(index), rank, throughCalls,
                               info, visited, blockSizes);
      if (!info.complete)
        return;
      continue;
    }
    if (auto store = dyn_cast<AffineStoreOp>(user);
        store && store.getMemRef() == mem &&
        isStaticInitStore(store, store.getValueToStore()))
      continue;
    if (auto store = dyn_cast<memref::StoreOp>(user);
        store && store.getMemRef() == mem &&
        isStaticInitStore(store, store.getValueToStore()))
      continue;
    if (auto load = dyn_cast<AffineLoadOp>(user)) {
      dims = constantDimsOfAffine(load.getAffineMap(), load.getMapOperands(),
                                  blockSizes);
      ++info.affineAccesses;
    } else if (auto store = dyn_cast<AffineStoreOp>(user);
               store && store.getMemRef() == mem &&
               store.getValueToStore() != mem) {
      dims = constantDimsOfAffine(store.getAffineMap(),
                                  store.getMapOperands(), blockSizes);
      ++info.affineAccesses;
    } else if (auto load = dyn_cast<memref::LoadOp>(user)) {
      dims = constantDimsOfIndices(load.getIndices());
    } else if (auto store = dyn_cast<memref::StoreOp>(user);
               store && store.getMemRef() == mem &&
               store.getValueToStore() != mem) {
      dims = constantDimsOfIndices(store.getIndices());
    } else {
      info.complete = false;
      return;
    }
    if (dims.size() != rank) {
      info.complete = false;
      return;
    }
    ++info.accesses;
    for (unsigned d = 0; d < rank; ++d)
      info.constantDim[d] = info.constantDim[d] && dims[d];
  }
}

static ConstantIndexInfo
analyzeConstantIndices(Value mem, unsigned rank, bool throughCalls,
                       ArrayRef<int64_t> blockSizes = {}) {
  ConstantIndexInfo info;
  info.constantDim.assign(rank, true);
  SmallPtrSet<Value, 4> visited;
  analyzeConstantIndexUses(mem, rank, throughCalls, info, visited, blockSizes);
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

/// The inputs of the automatic rules (a)-(c).
struct AutomaticRules {
  int64_t completeThreshold = 4;           ///< (a), elements
  int64_t constantIndexMinExtent = 2;      ///< (b), elements
  int64_t constantIndexMaxExtent = 64;     ///< (b), elements; 0: no limit
  ArrayRef<std::string> userStoragePragmas; ///< arrays the user decided
  /// (b) also on an array with a user cyclic / block array_partition
  /// (VITIS_NOTES N57: 214-270 completes each part).
  bool afterUserPartition = true;
  /// (b) also on an array without an affine access (N57).
  bool nonAffineArrays = true;
  /// (b) also on an array whose only storage pragma is `stream type=pipo`
  /// (VITIS_NOTES N77, kernels w9r9p_o79_loc_pipo / static_pipo).
  bool pipoStreams = true;
  /// (b) also on memref.globals (function statics, file-scope arrays),
  /// over the accesses of every function (N77, w9r9p_o79_static*).
  bool globals = true;
  /// (b) over the accesses in the callees the array is passed to (N94).
  bool throughCalls = true;
  /// (b) after a user block partition: a constant offset in the block (N104).
  bool blockOffset = true;
};

/// Whether the only user storage pragma on `def` is `stream type=pipo`: Vitis
/// still applies the constant-index partition (b) to it (N77: o79_loc_pipo,
/// o79_static_pipo, hp_fft_hls `data_rev_stream`).
static bool hasOnlyPipoStream(Operation *def, const AutomaticRules &rules) {
  if (!rules.pipoStreams)
    return false;
  constexpr StringRef kStream = "hls.stream";
  auto streams = def->getAttrOfType<ArrayAttr>(kStream);
  if (!streams || streams.empty())
    return false;
  for (Attribute a : streams) {
    auto entry = dyn_cast<DictionaryAttr>(a);
    auto type = entry ? entry.getAs<StringAttr>("type") : StringAttr();
    if (!type || type.getValue() != "pipo")
      return false;
  }
  for (StringRef pragma : rules.userStoragePragmas)
    if (pragma != kStream && def->hasAttr(pragma))
      return false;
  return true;
}

/// Whether the only user storage pragma on `def` is an array_partition (rule
/// (b) may still add complete entries to it).
static bool hasOnlyUserPartition(Operation *def,
                                 const AutomaticRules &rules) {
  if (!def->hasAttr(kPartitionAttr))
    return false;
  for (StringRef pragma : rules.userStoragePragmas)
    if (pragma != kPartitionAttr && def->hasAttr(pragma))
      return false;
  return true;
}

/// The extent of each part of dimension `d` of `def` after the user's cyclic
/// / block array_partition on that dimension (dim = d + 1, or 0 for every
/// dimension); the whole extent without one. Rule (b)'s max_extent compares
/// this: zijun_wang lab2 `K_l[N][128]` with `cyclic factor=32 dim=2` gets
/// 128 banks in Vitis (parts of 4), while A[64][256] with a user cyclic 2 on
/// dim 1 keeps dim 2 whole (kernel w9r7rev_ap_big; VITIS_NOTES N61).
static int64_t partExtent(Operation *def, MemRefType ty, unsigned d) {
  int64_t extent = ty.getDimSize(d);
  auto entries = def->getAttrOfType<ArrayAttr>(kPartitionAttr);
  if (!entries)
    return extent;
  for (Attribute a : entries) {
    auto entry = dyn_cast<DictionaryAttr>(a);
    auto dim = entry ? entry.getAs<IntegerAttr>("dim") : IntegerAttr();
    auto kind = entry ? entry.getAs<StringAttr>("kind") : StringAttr();
    auto factor = entry ? entry.getAs<IntegerAttr>("factor") : IntegerAttr();
    if (!dim || !kind || !factor || factor.getInt() <= 1)
      continue;
    if (dim.getInt() != static_cast<int64_t>(d) + 1 && dim.getInt() != 0)
      continue;
    if (kind.getValue() == "cyclic" || kind.getValue() == "block")
      extent = (extent + factor.getInt() - 1) / factor.getInt();
  }
  return extent;
}

/// Whether rules (a)-(c) may look at an array `def` of type `ty` at all: a
/// static array of words the user has not given a storage pragma.
static bool isAutomaticCandidate(Operation *def, MemRefType ty,
                                 const AutomaticRules &rules) {
  if (!ty.hasStaticShape())
    return false;
  Type elt = ty.getElementType();
  if (!elt.isIntOrFloat() && !isa<IndexType>(elt))
    return false; // pointer variables, structs: not an array of words
  for (StringRef pragma : rules.userStoragePragmas)
    if (def->hasAttr(pragma))
      return false; // the user decided
  return true;
}

/// Rule (a), small arrays, whatever their accesses (also those passed on to a
/// call): complete_threshold counts elements, not bits (int[4] fires, char[5]
/// does not; partition_chk.md R5). It holds for globals and function
/// statics as for locals (VITIS_NOTES N7 (a), kernel w9rv_r1_glob4).
static AutomaticPartition decideSmallArray(MemRefType ty,
                                           const AutomaticRules &rules) {
  AutomaticPartition decision;
  int64_t completeThreshold = rules.completeThreshold;
  int64_t elements = ty.getNumElements();
  if (elements > 0 && elements <= completeThreshold) {
    decision.kind = AutomaticPartition::Registers;
    decision.reason = std::to_string(elements) +
                      " element(s) <= complete-threshold " +
                      std::to_string(completeThreshold) +
                      ": completely partitioned into registers (Vitis [HLS "
                      "214-421] 'Automatically partitioning small array ... "
                      "completely based on array size')";
  }
  return decision;
}

/// Rules (b) and (c) from what the accesses of `def` (an alloca or a
/// global) say. `onlyB`: rule (c) is not applied, and an array indexed by
/// constants in every dimension is left alone (unconfirmed for a PIPO stream
/// and for globals).
static AutomaticPartition
decideFromConstantIndices(Operation *def, MemRefType ty,
                          const ConstantIndexInfo &info,
                          const AutomaticRules &rules, bool afterUser,
                          bool onlyB) {
  AutomaticPartition decision;
  unsigned rank = ty.getRank();
  if (!info.complete || info.accesses == 0)
    return decision; // escapes, or nothing to look at (dead: not ours)
  if (onlyB && llvm::all_of(info.constantDim, [](bool c) { return c; }))
    return decision;
  bool allConstant = llvm::all_of(info.constantDim, [](bool c) { return c; });
  // Accesses through element views: memory banking cannot split the array,
  // so only registers can follow; a user complete partition of every
  // dimension is registers as well (VITIS_NOTES N111, kernel w9r15p_rg_net:
  // `int v[8]` complete, its elements passed by reference).
  bool userComplete = afterUser && userCompleteEveryDim(def, ty);
  if (info.throughViews && (!allConstant || (afterUser && !userComplete)))
    return decision; // banking does not split through the views

  // (c) Every access constant in every dimension: scalarised.
  if ((!afterUser || (userComplete && info.throughViews)) && allConstant) {
    decision.kind = AutomaticPartition::Registers;
    decision.reason = "every one of the " + std::to_string(info.accesses) +
                      " access(es) uses a constant index in every dimension: "
                      "scalarised into registers (Vitis front end, alloca "
                      "gone in a.o.1; partition.md R5)";
    return decision;
  }

  // (b) Dimensions that only ever see constants, min_extent (2) <= extent <=
  // max_extent (64): Vitis leaves a larger one whole (kernels w9r7fix_ap_e65
  // .. e128, e65w8, e128k64 against e64r256 / e64w32; VITIS_NOTES N61).
  SmallVector<unsigned, 2> tooLarge;
  for (unsigned d = 0; d < rank; ++d) {
    if (!info.constantDim[d] || ty.getDimSize(d) < rules.constantIndexMinExtent)
      continue;
    if (rules.constantIndexMaxExtent > 0 &&
        partExtent(def, ty, d) >
            rules.constantIndexMaxExtent) {
      tooLarge.push_back(d);
      continue;
    }
    decision.parts.push_back({d, ty.getDimSize(d)});
  }
  if (decision.parts.empty()) {
    if (!tooLarge.empty())
      decision.reason =
          "dimension " + std::to_string(tooLarge.front() + 1) +
          " is indexed only by constants, but its extent (per part of a "
          "user partition) " +
          std::to_string(partExtent(def, ty,
                                    tooLarge.front())) +
          " exceeds constant_index.max_extent " +
          std::to_string(rules.constantIndexMaxExtent) +
          ": left whole (Vitis does not partition it; VITIS_NOTES N61)";
    return decision;
  }
  std::string dims;
  llvm::raw_string_ostream os(dims);
  llvm::interleave(
      decision.parts, os,
      [&](const PartitionChoice &p) { os << (p.dim + 1); }, ", ");
  if (info.affineAccesses == 0 && !rules.nonAffineArrays) {
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
  if (afterUser)
    decision.reason += ", on every part of the user's array_partition (Vitis "
                       "[HLS 214-270] after the user pragma, VITIS_NOTES N57)";
  if (decision.parts.size() > 1)
    decision.reason += "; memory banking applies only the first entry";
  return decision;
}

static AutomaticPartition decideAutomaticPartition(memref::AllocaOp alloca,
                                                   const AutomaticRules &rules,
                                                   bool &afterUser) {
  AutomaticPartition decision;
  MemRefType ty = alloca.getType();
  Operation *def = alloca.getOperation();
  // A user cyclic / block partition: Vitis still completes each part along
  // a dimension every access indexes with a constant after the implied
  // unroll (N57, kernels w9r7_ap_cyc / ap_blk: 4 user banks -> 32). Only
  // rule (b) is applied on top of the user's pragma.
  afterUser = rules.afterUserPartition &&
              hasOnlyUserPartition(alloca.getOperation(), rules) &&
              ty.hasStaticShape() &&
              (ty.getElementType().isIntOrFloat() ||
               isa<IndexType>(ty.getElementType()));
  bool pipo = !afterUser && hasOnlyPipoStream(def, rules) &&
              ty.hasStaticShape() &&
              (ty.getElementType().isIntOrFloat() ||
               isa<IndexType>(ty.getElementType()));
  if (!afterUser && !pipo && !isAutomaticCandidate(def, ty, rules))
    return decision;

  // (a) Small arrays.
  if (!afterUser && !pipo) {
    decision = decideSmallArray(ty, rules);
    if (decision.kind != AutomaticPartition::None)
      return decision;
  }

  SmallVector<int64_t> blockSizes;
  if (afterUser && rules.blockOffset)
    blockSizes = userBlockSizes(def, ty);
  ConstantIndexInfo info = analyzeConstantIndices(
      alloca.getResult(), ty.getRank(), rules.throughCalls, blockSizes);
  return decideFromConstantIndices(def, ty, info, rules, afterUser, pipo);
}

//===----------------------------------------------------------------------===//
// Pass
//===----------------------------------------------------------------------===//

struct InferVitisSplitArray
    : public PassWrapper<InferVitisSplitArray, OperationPass<ModuleOp>> {
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
      llvm::cl::desc("Vitis syn.array_partition.throughput_driven. 'auto': "
                     "partitions from port pressure. 'off' (the default of "
                     "the configuration, tool.hls.options.array_partition."
                     "throughput_driven, the ground truth): only "
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
    AutomaticRules rules;
    rules.completeThreshold = completeThresholdValue;
    rules.constantIndexMinExtent = cfgPartitioning->constantIndexMinExtent;
    rules.constantIndexMaxExtent = cfgPartitioning->constantIndexMaxExtent;
    rules.userStoragePragmas = userStoragePragmas;
    rules.afterUserPartition =
        cfgPartitioning->constantIndexAfterUserPartition;
    rules.nonAffineArrays = cfgPartitioning->constantIndexNonAffineArrays;
    rules.pipoStreams = cfgPartitioning->constantIndexPipoStreams;
    rules.globals = cfgPartitioning->constantIndexGlobals;
    rules.throughCalls = cfgPartitioning->constantIndexThroughCalls;
    rules.blockOffset = cfgPartitioning->constantIndexBlockOffset;
    DenseSet<Value> decided;
    Builder builder(func.getContext());
    func.walk([&](memref::AllocaOp alloca) {
      Operation *def = alloca.getOperation();
      if (def->hasAttr(kRegistersAttrName)) {
        decided.insert(alloca.getResult());
        return;
      }
      bool afterUser = false;
      AutomaticPartition decision =
          decideAutomaticPartition(alloca, rules, afterUser);
      auto varName = def->getAttrOfType<StringAttr>(kVarNameAttr);
      std::string name =
          varName ? varName.getValue().str() : std::string("<unnamed>");
      if (decision.unbankable) {
        ++runStats.unbankable;
        LLVM_DEBUG(llvm::dbgs() << "array '" << name << "': "
                                << decision.reason << "\n");
        if (emitRemarks)
          mlir::emitRemark(alloca.getLoc())
              << "array '" << name << "' left whole: " << decision.reason;
      }
      if (decision.kind == AutomaticPartition::None) {
        // A rule that matched and declined (rule (b)'s max_extent).
        if (!decision.unbankable && !decision.reason.empty() && emitRemarks)
          mlir::emitRemark(alloca.getLoc())
              << "array '" << name << "' left whole: " << decision.reason;
        return;
      }
      decided.insert(alloca.getResult());
      if (decision.kind == AutomaticPartition::Registers) {
        def->setAttr(kRegistersAttrName, builder.getUnitAttr());
        def->setAttr(kRegistersReasonAttrName,
                     builder.getStringAttr(decision.reason));
        ++runStats.registers;
        LLVM_DEBUG(llvm::dbgs() << "array '" << name
                                << "': registers (" << decision.reason
                                << ")\n");
        if (emitRemarks)
          mlir::emitRemark(alloca.getLoc())
              << "array '" << name << "' -> registers: " << decision.reason;
        return;
      }
      ArrayRef<int64_t> shape = alloca.getType().getShape();
      ArrayAttr automatic = buildPartitionAttr(builder, decision.parts, shape,
                                               varName, kSourceConstantIndex);
      if (afterUser) {
        // Appended to the user's entries; memory banking merges entries on
        // one dimension by the larger factor (N17 (c)), so a complete entry
        // on the user's own dimension makes it complete.
        SmallVector<Attribute> merged;
        if (auto user = def->getAttrOfType<ArrayAttr>(kPartitionAttr))
          llvm::append_range(merged, user.getValue());
        llvm::append_range(merged, automatic.getValue());
        automatic = builder.getArrayAttr(merged);
      }
      def->setAttr(kPartitionAttr, automatic);
      def->setAttr(kReasonAttr, builder.getStringAttr(decision.reason));
      ++runStats.constantDims;
      if (decision.parts.size() > 1)
        ++runStats.multiConstantDims;
      LLVM_DEBUG(llvm::dbgs() << "array '" << name << "': "
                              << decision.reason << "\n");
      if (emitRemarks)
        for (const PartitionChoice &part : decision.parts)
          mlir::emitRemark(alloca.getLoc())
              << "Automatically partitioning array '" << name
              << "' dimension " << part.dim + 1
              << " completely based on constant index";
    });
    applySmallGlobals(func, rules, decided);
    applyConstantIndexGlobals(func, rules, decided);
    return decided;
  }

  /// Rule (b) on the globals and function statics `func` uses, over the
  /// accesses of every function of the module (VITIS_NOTES N77: Vitis logs
  /// [HLS 214-449] for a static array as for a local one, kernels
  /// w9r9p_o79_static / static_pipo, hp_fft_hls `data_rev_stream`). Rule
  /// (c) and an array indexed by constants in every dimension stay
  /// unconfirmed for globals and are left alone. A global decided once
  /// carries hls.partition_reason; later functions only note it.
  void applyConstantIndexGlobals(func::FuncOp func,
                                 const AutomaticRules &rules,
                                 DenseSet<Value> &decided) {
    if (!rules.globals)
      return;
    auto module = func->getParentOfType<ModuleOp>();
    Builder builder(func.getContext());
    func.walk([&](memref::GetGlobalOp get) {
      auto global = SymbolTable::lookupNearestSymbolFrom<memref::GlobalOp>(
          get, get.getNameAttr());
      if (!global)
        return;
      Operation *def = global.getOperation();
      if (def->hasAttr(kRegistersAttrName))
        return;
      if (def->hasAttr(kReasonAttr)) {
        decided.insert(get.getResult());
        return;
      }
      MemRefType ty = global.getType();
      bool wordArray = ty.hasStaticShape() &&
                       (ty.getElementType().isIntOrFloat() ||
                        isa<IndexType>(ty.getElementType()));
      bool afterUser = rules.afterUserPartition && wordArray &&
                       hasOnlyUserPartition(def, rules);
      bool pipo = !afterUser && wordArray && hasOnlyPipoStream(def, rules);
      if (!afterUser && !pipo && !isAutomaticCandidate(def, ty, rules))
        return;
      unsigned rank = ty.getRank();
      ConstantIndexInfo info;
      info.constantDim.assign(rank, true);
      std::optional<SymbolTable::UseRange> uses =
          SymbolTable::getSymbolUses(def, module);
      if (!uses)
        return;
      for (const SymbolTable::SymbolUse &use : *uses) {
        auto gg = dyn_cast<memref::GetGlobalOp>(use.getUser());
        if (!gg)
          return; // another kind of use: nothing is concluded
        ConstantIndexInfo gi = analyzeConstantIndices(
            gg.getResult(), rank, rules.throughCalls,
            afterUser && rules.blockOffset ? userBlockSizes(def, ty)
                                           : SmallVector<int64_t>());
        if (!gi.complete)
          return;
        info.accesses += gi.accesses;
        info.affineAccesses += gi.affineAccesses;
        for (unsigned d = 0; d < rank; ++d)
          info.constantDim[d] = info.constantDim[d] && gi.constantDim[d];
      }
      AutomaticPartition decision = decideFromConstantIndices(
          def, ty, info, rules, afterUser, /*onlyB=*/true);
      if (decision.kind != AutomaticPartition::ConstantDims)
        return;
      ArrayAttr automatic =
          buildPartitionAttr(builder, decision.parts, ty.getShape(),
                             def->getAttrOfType<StringAttr>(kVarNameAttr),
                             kSourceConstantIndex);
      if (afterUser) {
        SmallVector<Attribute> merged;
        if (auto user = def->getAttrOfType<ArrayAttr>(kPartitionAttr))
          llvm::append_range(merged, user.getValue());
        llvm::append_range(merged, automatic.getValue());
        automatic = builder.getArrayAttr(merged);
      }
      def->setAttr(kPartitionAttr, automatic);
      def->setAttr(kReasonAttr, builder.getStringAttr(decision.reason));
      decided.insert(get.getResult());
      ++runStats.constantDims;
      if (decision.parts.size() > 1)
        ++runStats.multiConstantDims;
      if (emitRemarks)
        for (const PartitionChoice &part : decision.parts)
          mlir::emitRemark(global.getLoc())
              << "Automatically partitioning global '" << global.getSymName()
              << "' dimension " << part.dim + 1
              << " completely based on constant index";
    });
  }

  /// Rule (a) on the globals and function statics `func` reads or writes
  /// (VITIS_NOTES N7 (a): Vitis logs [HLS 214-421] for them as for locals,
  /// kernel w9rv_r1_glob4). Rules (b) and (c) look at every access of an
  /// array, which for a global spans functions: not applied (unconfirmed).
  /// The pass is a module pass, so writing the global from here is safe.
  void applySmallGlobals(func::FuncOp func, const AutomaticRules &rules,
                         DenseSet<Value> &decided) {
    Builder builder(func.getContext());
    func.walk([&](memref::GetGlobalOp get) {
      auto global = SymbolTable::lookupNearestSymbolFrom<memref::GlobalOp>(
          get, get.getNameAttr());
      if (!global)
        return;
      Operation *def = global.getOperation();
      if (def->hasAttr(kRegistersAttrName)) {
        decided.insert(get.getResult());
        return;
      }
      if (!isAutomaticCandidate(def, global.getType(), rules))
        return;
      AutomaticPartition decision = decideSmallArray(global.getType(), rules);
      if (decision.kind != AutomaticPartition::Registers)
        return;
      decided.insert(get.getResult());
      def->setAttr(kRegistersAttrName, builder.getUnitAttr());
      def->setAttr(kRegistersReasonAttrName,
                   builder.getStringAttr(decision.reason));
      ++runStats.registers;
      LLVM_DEBUG(llvm::dbgs() << "global '" << global.getSymName()
                              << "': registers (" << decision.reason << ")\n");
      if (emitRemarks)
        mlir::emitRemark(global.getLoc())
            << "global '" << global.getSymName()
            << "' -> registers: " << decision.reason;
    });
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
    return getUserTargetII(loop).value_or(targetIIValue);
  }

  // The values the run uses: an option given explicitly, else the
  // configuration (tool.hls.options.array_partition.*,
  // tool.hls.partitioning.*, frontend.user_storage_pragmas). With the
  // configuration a bare --infer-vitis-split-array is td=off (the ground
  // truth, design memo decision 5); td=auto must be asked for.
  unsigned targetIIValue = 1, portsValue = 2, readPortsValue = 1,
           writePortsValue = 1, maxDimsValue = 1;
  int64_t maxFactorValue = 0, completeThresholdValue = 4;
  bool rotatingBanksValue = false, includePortsValue = false;
  std::string throughputDrivenValue = "off";
  std::vector<std::string> userStoragePragmas;
  const circt::hlsest::PartitioningConfig *cfgPartitioning = nullptr;

  void resolveConfiguration() {
    using circt::hlsest::resolveOption;
    const circt::hlsest::Config &cfg = circt::hlsest::Config::get();
    const circt::hlsest::PartitioningConfig &pc = cfg.tool.hls.partitioning;
    const circt::hlsest::PartitionInferenceConfig &inf = pc.inference;
    cfgPartitioning = &pc;
    targetIIValue =
        resolveOption<unsigned>(targetII, static_cast<unsigned>(inf.targetII));
    portsValue =
        resolveOption<unsigned>(ports, static_cast<unsigned>(inf.portsAny));
    readPortsValue = resolveOption<unsigned>(
        readPorts, static_cast<unsigned>(inf.portsRead));
    writePortsValue = resolveOption<unsigned>(
        writePorts, static_cast<unsigned>(inf.portsWrite));
    maxDimsValue =
        resolveOption<unsigned>(maxDims, static_cast<unsigned>(inf.maxDims));
    maxFactorValue = maxFactor.hasValue() ? static_cast<int64_t>(maxFactor)
                                          : inf.maxFactor;
    rotatingBanksValue = resolveOption(rotatingBanks, inf.rotatingBanks);
    const circt::hlsest::ArrayPartitionOptions &ap =
        cfg.tool.hls.options.arrayPartition;
    includePortsValue = resolveOption(includePorts, ap.includePorts);
    completeThresholdValue = completeThreshold.hasValue()
                                 ? static_cast<int64_t>(completeThreshold)
                                 : ap.completeThreshold;
    throughputDrivenValue =
        throughputDriven.hasValue() ? std::string(throughputDriven)
                                    : ap.throughputDriven;
    userStoragePragmas = cfg.frontend.userStoragePragmas;
  }

  /// The counters of the current run (the pass adds them to its
  /// statistics).
  circt::hlsest::PartitionStatistics runStats;

  // A module pass: the policy runs on one function at a time, and rule (a)
  // marks the globals a function uses (applySmallGlobals), which a function
  // pass may not write.
  void runOnOperation() override {
    for (func::FuncOp func : getOperation().getOps<func::FuncOp>()) {
      if (func.isExternal())
        continue;
      if (failed(runOnFunction(func)))
        return signalPassFailure();
    }
  }

  LogicalResult runOnFunction(func::FuncOp func) {
    resolveConfiguration();
    circt::hlsest::PartitionOptions o;
    o.targetII = targetIIValue;
    o.ports = portsValue;
    o.readPorts = readPortsValue;
    o.writePorts = writePortsValue;
    o.maxDims = maxDimsValue;
    o.maxFactor = maxFactorValue;
    o.completeThreshold = completeThresholdValue;
    o.rotatingBanks = rotatingBanksValue;
    o.includePorts = includePortsValue;
    o.throughputDrivenOff = throughputDrivenValue == "off";
    o.autoPartitions = autoPartitions;
    o.annotatePressure = annotatePressure;
    o.emitRemarks = emitRemarks;
    o.autoPipeline = autoPipeline;
    if (throughputDrivenValue != "auto" && throughputDrivenValue != "off") {
      func.emitError("infer-vitis-split-array: td must be 'auto' or 'off', "
                     "got '")
          << throughputDrivenValue << "'";
      return failure();
    }
    // The decision is the configuration's PartitionPolicy (builtin vitis-td:
    // runInference below).
    const circt::hlsest::Config &cfg = circt::hlsest::Config::get();
    circt::hlsest::ConfigDiagnostics diag;
    std::unique_ptr<circt::hlsest::PartitionPolicy> policy =
        circt::hlsest::PluginRegistry<circt::hlsest::PartitionPolicy>::instance()
            .create(cfg.tool.hls.partitioning.policy, cfg, diag);
    if (!policy) {
      InFlightDiagnostic d = func.emitError("infer-vitis-split-array: ");
      llvm::interleave(diag.errors, d, "; ");
      return failure();
    }
    circt::hlsest::PartitionStatistics stats;
    if (failed(policy->run(func, o, stats)))
      return failure();
    numRegions += stats.regions;
    numPartitioned += stats.partitioned;
    numUnresolved += stats.unresolved;
    numRegisters += stats.registers;
    numConstantDims += stats.constantDims;
    numMultiConstantDims += stats.multiConstantDims;
    numUnbankable += stats.unbankable;
    return success();
  }

  /// Vitis' automatic partitions and, with td=auto, the port-pressure
  /// inference (the builtin PartitionPolicy vitis-td).
  LogicalResult runInference(func::FuncOp func,
                             const circt::hlsest::PartitionOptions &o,
                             circt::hlsest::PartitionStatistics &stats) {
    const circt::hlsest::Config &cfg = circt::hlsest::Config::get();
    targetIIValue = o.targetII;
    portsValue = o.ports;
    readPortsValue = o.readPorts;
    writePortsValue = o.writePorts;
    maxDimsValue = o.maxDims;
    maxFactorValue = o.maxFactor;
    completeThresholdValue = o.completeThreshold;
    rotatingBanksValue = o.rotatingBanks;
    includePortsValue = o.includePorts;
    throughputDrivenValue = o.throughputDrivenOff ? "off" : "auto";
    userStoragePragmas = cfg.frontend.userStoragePragmas;
    cfgPartitioning = &cfg.tool.hls.partitioning;
    autoPartitions = o.autoPartitions;
    annotatePressure = o.annotatePressure;
    emitRemarks = o.emitRemarks;
    autoPipeline = o.autoPipeline;
    runStats = circt::hlsest::PartitionStatistics();
    if (targetIIValue == 0 || portsValue == 0 || readPortsValue == 0 ||
        writePortsValue == 0 || maxDimsValue == 0) {
      func.emitError("infer-vitis-split-array: target-ii, ports, read-ports, "
                     "write-ports and max-dims must be positive");
      return failure();
    }
    if (throughputDrivenValue != "auto" && throughputDrivenValue != "off") {
      func.emitError("infer-vitis-split-array: td must be 'auto' or 'off', "
                     "got '")
          << throughputDrivenValue << "'";
      return failure();
    }
    bool tdOff = throughputDrivenValue == "off";
    PortModel pm{portsValue, readPortsValue, writePortsValue};

    // 0. Vitis' automatic partitions that do not depend on throughput.
    DenseSet<Value> decided;
    if (tdOff || autoPartitions)
      decided = applyAutomaticPartitions(func);

    // 1. Port pressure per (memory, pipelined loop).
    TermTable terms;
    llvm::MapVector<Value, SmallVector<PipelineRegion, 2>> pressure;
    func.walk([&](AffineForOp loop) {
      if (std::optional<unsigned> ii = getPipelineII(loop)) {
        ++runStats.regions;
        collectRegions(loop, *ii, terms, pressure);
      }
    });

    // 2. One decision per memory, over all the loops that touch it.
    Builder builder(func.getContext());
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
      if (portLimit(regions, {}, pm, rotatingBanksValue).excess == 0)
        continue; // the ports keep up with every loop as it is

      // Where the spec lives, and whether a user already wrote one.
      auto iface = dyn_cast_or_null<MemoryResourceOpInterface>(def);
      bool canAnnotate = iface || (isFuncArg && includePortsValue);
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
        ++runStats.unresolved;
        if (emitRemarks)
          mlir::emitRemark(loc)
              << "array '" << name
              << "' limits a pipelined loop but is left alone: " << obstacle;
        continue;
      }

      PartitionPlan plan =
          inferPartition(regions, shape, pm, rotatingBanksValue,
                         maxFactorValue, maxDimsValue,
                         cfgPartitioning->inference.maxScannedFactor);

      if (!plan.parts.empty()) {
        ArrayAttr spec =
            buildPartitionAttr(builder, plan.parts, shape, varName);
        if (def)
          def->setAttr(kPartitionAttr, spec);
        else
          func.setArgAttr(arg.getArgNumber(), kPartitionAttr, spec);
        ++runStats.partitioned;

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
        ++runStats.unresolved;
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
    stats = runStats;
    return success();
  }
};

/// vitis-td: the automatic partitions Vitis makes whatever
/// syn.array_partition.throughput_driven says (small arrays, constant
/// indices; VITIS_NOTES N7) and, with td=auto, the port-pressure inference
/// (N2): the code of this pass.
class VitisTdPartitions : public circt::hlsest::PartitionPolicy {
public:
  StringRef name() const override { return "vitis-td"; }
  LogicalResult run(func::FuncOp func, const circt::hlsest::PartitionOptions &o,
                    circt::hlsest::PartitionStatistics &stats) const override {
    InferVitisSplitArray impl;
    return impl.runInference(func, o, stats);
  }
};

} // namespace

void circt::hlsest::builtin::registerPartitionPolicies() {
  circt::hlsest::PluginRegistry<circt::hlsest::PartitionPolicy>::instance()
      .add("vitis-td",
           "Vitis automatic partitions (td=off) and the port-pressure "
           "inference (td=auto)",
           [] { return std::make_unique<VitisTdPartitions>(); }, "builtin");
}

namespace circt::hls_analysis {

std::unique_ptr<mlir::Pass> createInferVitisSplitArray() {
  return std::make_unique<InferVitisSplitArray>();
}

void registerInferVitisSplitArray() {
  ::mlir::PassRegistration<InferVitisSplitArray>();
}

} // namespace circt::hls_analysis
