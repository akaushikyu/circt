

// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#include "circt/Dialect/Resource/Passes/InferVitisSplitArray.h"
#include "../Plugins/Builtin/Builtins.h"
#include "circt/Dialect/Resource/Config/ConfigUtils.h"
#include "circt/Dialect/Resource/Passes/CallInstances.h"
#include "circt/Dialect/Resource/Passes/ConstantIndex.h"
#include "circt/Dialect/Resource/Passes/LoopPragmas.h"
#include "circt/Dialect/Resource/Passes/PolygeistCompat.h"
#include "circt/Dialect/Resource/Plugins/PassPolicies.h"
#include "circt/Dialect/Resource/Plugins/Registry.h"
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
#include "mlir/Interfaces/SideEffectInterfaces.h"
#include "mlir/Pass/Pass.h"
#include "llvm/ADT/DenseSet.h"
#include "llvm/ADT/MapVector.h"
#include "llvm/ADT/SmallVector.h"
#include "llvm/ADT/StringSet.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/MathExtras.h"
#include "llvm/Support/raw_ostream.h"

#include "circt/Dialect/Resource/Interfaces/MemoryDS.h"
#include <algorithm>
#include <circt/Dialect/Resource/Interfaces/MemoryOpInterface.h.inc>
#include <optional>
#include <set>
#include <string>

#define DEBUG_TYPE "infer-vitis-split-array"

namespace circt {
namespace hls_analysis {}
} // namespace circt

using namespace mlir;
using namespace mlir::affine;
using namespace circt;
using namespace circt::hls_analysis;

namespace {

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

/// Names SSA values with small ids so linear forms built from different
/// accesses (each with its own map operand list) are directly comparable.
class TermTable {
public:
  unsigned idFor(Value valueHandle) {
    unsigned next = ids.size();
    return ids.try_emplace(valueHandle, next).first->second;
  }

private:
  DenseMap<Value, unsigned> ids;
};

/// The index of one access along one memref dimension:
///     sum_k coeff_k * term_k + constant
/// A term is a loop iteration counter, a symbol, or any other index value.
struct LinearIndex {

  SmallVector<std::pair<unsigned, int64_t>, 2> terms;
  int64_t constant = 0;
  bool opaque = false;
};

struct Access {
  Operation *op = nullptr;
  bool isWrite = false;
  SmallVector<LinearIndex, 3> index;
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
  if (!accumulateLinear(expr, 1, numDims, coeffs, li.constant)) {
    li = LinearIndex();
    li.opaque = true;
    return li;
  }

  for (auto [pos, rawCoeff] : llvm::enumerate(coeffs)) {
    int64_t coeff = rawCoeff;
    if (coeff == 0)
      continue;
    Value valueHandle = operands[pos];
    if (std::optional<int64_t> cst = getConstantIntValue(valueHandle)) {
      li.constant += coeff * *cst;
      continue;
    }

    if (isAffineForInductionVar(valueHandle)) {
      AffineForOp owner = getForInductionVarOwner(valueHandle);
      if (owner.hasConstantLowerBound()) {
        li.constant += coeff * owner.getConstantLowerBound();
        coeff *= owner.getStepAsInt();
      }
    }
    li.terms.emplace_back(terms.idFor(valueHandle), coeff);
  }

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

  fullyComposeAffineMapAndOperands(&map, &operands);
  canonicalizeMapAndOperands(&map, &operands);
  map = simplifyAffineMap(map);

  LoopLikeOpInterface root = getFlattenedRoot(loop);
  loopInvariant = llvm::all_of(operands, [&](Value valueHandle) {
    return root.isDefinedOutsideOfLoop(valueHandle);
  });
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
    for (auto &entryValue : effects)
      if (!isa<MemoryEffects::Read>(entryValue.getEffect())) {
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
  MLIRContext *context = loop.getContext();

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
          AffineMap::getMultiDimIdentityMap(load.getIndices().size(), context),
          load.getIndices(), loop, terms, ra.access, ra.loopInvariant);
    } else if (auto store = dyn_cast<memref::StoreOp>(op)) {
      mem = store.getMemRef();
      ra.access.isWrite = true;
      analyzeAddress(
          AffineMap::getMultiDimIdentityMap(store.getIndices().size(), context),
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

/// What one memory bank can do in one clock cycle.
struct PortModel {
  unsigned ports;
  unsigned readPorts;
  unsigned writePorts;
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
  static BankLoad max(const BankLoad &a, const BankLoad &buildPoint) {
    BankLoad memoryOp;
    memoryOp.reads = std::max(a.reads, buildPoint.reads);
    memoryOp.writes = std::max(a.writes, buildPoint.writes);
    memoryOp.total = std::max(a.total, buildPoint.total);
    return memoryOp;
  }
};

struct PartitionChoice {
  unsigned dim;
  int64_t factor;
};

static int64_t floorMod(int64_t value, int64_t modulus) {
  int64_t resultValue = value % modulus;
  return resultValue < 0 ? resultValue + modulus : resultValue;
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
    Signature signature;
    llvm::MapVector<int64_t, Bucket> classes;
  };
  llvm::MapVector<int64_t, Bucket> fixedBank;
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
  unsigned excess = 0;
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
  PortLimit before;
  PortLimit after;
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
      if (llvm::any_of(plan.parts, [&](const PartitionChoice &portValue) {
            return portValue.dim == dim;
          }))
        continue;

      int64_t limit = maxFactor > 0 ? std::min(extent, maxFactor) : extent;
      int64_t scanTo = std::min(
          {limit, stableFactorBound(regions, dim) + 1, maxScannedFactor});
      for (int64_t factor = 2; factor <= scanTo; ++factor) {
        SmallVector<PartitionChoice, 2> trial(plan.parts);
        trial.push_back({dim, factor});
        PortLimit trialLimit = portLimit(regions, trial, pm, rotatingAware);

        if (trialLimit.excess < bestLimit.excess ||
            (best && trialLimit.excess == bestLimit.excess &&
             factor < best->factor)) {
          best = PartitionChoice{dim, factor};
          bestLimit = trialLimit;
        }
        if (trialLimit.excess == 0)
          break;
      }
    }

    if (!best)
      break;
    plan.parts.push_back(*best);
    plan.after = bestLimit;
  }
  return plan;
}

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
static ArrayAttr buildPartitionAttr(Builder &buildPoint,
                                    ArrayRef<PartitionChoice> parts,
                                    ArrayRef<int64_t> shape, StringAttr varName,
                                    StringRef source = kSourcePressure) {
  SmallVector<Attribute, 2> entries;
  for (const PartitionChoice &part : parts) {
    SmallVector<NamedAttribute, 5> fields;

    fields.push_back(buildPoint.getNamedAttr(
        "dim", buildPoint.getI32IntegerAttr(part.dim + 1)));
    fields.push_back(buildPoint.getNamedAttr(
        "factor",
        buildPoint.getI32IntegerAttr(static_cast<int32_t>(part.factor))));
    fields.push_back(buildPoint.getNamedAttr(
        "kind", buildPoint.getStringAttr(kindName(part, shape))));
    fields.push_back(
        buildPoint.getNamedAttr("source", buildPoint.getStringAttr(source)));
    if (varName)
      fields.push_back(buildPoint.getNamedAttr("variable", varName));
    entries.push_back(buildPoint.getDictionaryAttr(fields));
  }
  return buildPoint.getArrayAttr(entries);
}

/// One line for `hls.partition_reason`: the loop whose port demand drove the
/// decision, its per-iteration access counts, the target II and the factor.
static std::string describePartitionReason(const PartitionPlan &plan,
                                           const PipelineRegion &region,
                                           ArrayRef<int64_t> shape) {
  std::string stringValue;
  llvm::raw_string_ostream os(stringValue);
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
  return stringValue;
}

static ArrayAttr buildPressureAttr(Builder &buildPoint,
                                   ArrayRef<PipelineRegion> regions) {
  SmallVector<Attribute, 2> entries;
  for (const PipelineRegion &region : regions)
    entries.push_back(buildPoint.getDictionaryAttr(
        {buildPoint.getNamedAttr("ii",
                                 buildPoint.getI32IntegerAttr(region.targetII)),
         buildPoint.getNamedAttr("reads",
                                 buildPoint.getI32IntegerAttr(region.reads)),
         buildPoint.getNamedAttr(
             "writes", buildPoint.getI32IntegerAttr(region.writes))}));
  return buildPoint.getArrayAttr(entries);
}

/// Per memref dimension: whether the access's index is a constant. On a
/// dimension d with blockSizes[d] = B > 1 (a user block partition), the
/// offset inside the block counts instead: the index modulo B is a constant
/// (VITIS_NOTES N104: `j = 8 * jj + u` with B = 4).
static SmallVector<bool>
constantDimsOfAffine(AffineMap map, ValueRange mapOperands,
                     ArrayRef<int64_t> blockSizes = {}) {
  SmallVector<Value, 8> operands(mapOperands.begin(), mapOperands.end());

  fullyComposeAffineMapAndOperands(&map, &operands);
  AffineMap folded = foldConstantIndexOperands(map, operands);
  SmallVector<bool> dims;

  SmallVector<AffineExpr> counters;
  for (unsigned loopIndex = 0; loopIndex < folded.getNumDims(); ++loopIndex) {
    AffineExpr dim = getAffineDimExpr(loopIndex, map.getContext());
    if (loopIndex < operands.size())
      if (AffineForOp loop = getForInductionVarOwner(operands[loopIndex]))
        if (loop.hasConstantLowerBound() && loop.getStepAsInt() > 1)
          dim = dim * loop.getStepAsInt() + loop.getConstantLowerBound();
    counters.push_back(dim);
  }
  for (auto [dimensionIndex, expr] : llvm::enumerate(folded.getResults())) {
    bool constant = isa<AffineConstantExpr>(expr);
    if (!constant && dimensionIndex < blockSizes.size() &&
        blockSizes[dimensionIndex] > 1)
      constant = isa<AffineConstantExpr>(simplifyAffineExpr(
          expr.replaceDims(counters) % blockSizes[dimensionIndex],
          folded.getNumDims(), folded.getNumSymbols()));
    dims.push_back(constant);
  }
  return dims;
}

/// Whether a user array_partition of `def` is `complete` on every dimension
/// of `ty` (dim=0, or one complete entry per dimension).
static bool userCompleteEveryDim(Operation *def, MemRefType memRefType) {
  auto entries = def->getAttrOfType<ArrayAttr>(kPartitionAttr);
  if (!entries)
    return false;
  SmallVector<bool> complete(memRefType.getRank(), false);
  for (Attribute a : entries) {
    auto entry = dyn_cast<DictionaryAttr>(a);
    auto dim = entry ? entry.getAs<IntegerAttr>("dim") : IntegerAttr();
    auto kind = entry ? entry.getAs<StringAttr>("kind") : StringAttr();
    if (!dim || !kind || kind.getValue() != "complete")
      continue;
    for (int64_t dimensionIndex = 0; dimensionIndex < memRefType.getRank();
         ++dimensionIndex)
      if (dim.getInt() == dimensionIndex + 1 || dim.getInt() == 0)
        complete[dimensionIndex] = true;
  }
  return llvm::all_of(complete,
                      [](bool candidateValue) { return candidateValue; });
}

/// Per dimension of `def` (type `ty`): the block size of a user block
/// array_partition on it, 0 without one (N104).
static SmallVector<int64_t> userBlockSizes(Operation *def,
                                           MemRefType memRefType) {
  SmallVector<int64_t> sizes(memRefType.getRank(), 0);
  auto entries = def->getAttrOfType<ArrayAttr>(kPartitionAttr);
  if (!entries || !memRefType.hasStaticShape())
    return sizes;
  for (Attribute a : entries) {
    auto entry = dyn_cast<DictionaryAttr>(a);
    auto dim = entry ? entry.getAs<IntegerAttr>("dim") : IntegerAttr();
    auto kind = entry ? entry.getAs<StringAttr>("kind") : StringAttr();
    auto factor = entry ? entry.getAs<IntegerAttr>("factor") : IntegerAttr();
    if (!dim || !kind || !factor || factor.getInt() <= 1 ||
        kind.getValue() != "block")
      continue;
    for (int64_t dimensionIndex = 0; dimensionIndex < memRefType.getRank();
         ++dimensionIndex)
      if (dim.getInt() == dimensionIndex + 1 || dim.getInt() == 0) {
        int64_t extent = memRefType.getDimSize(dimensionIndex);
        sizes[dimensionIndex] =
            (extent + factor.getInt() - 1) / factor.getInt();
      }
  }
  return sizes;
}

static SmallVector<bool> constantDimsOfIndices(ValueRange indices) {
  SmallVector<bool> dims;
  for (Value indexValue : indices)
    dims.push_back(getConstantIndexValue(indexValue).has_value());
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
    if (auto globalUse = flag ? flag.getDefiningOp<memref::GetGlobalOp>()
                              : memref::GetGlobalOp())
      if (globalUse.getName().ends_with("@init"))
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
                                     bool throughCalls, ConstantIndexInfo &info,
                                     SmallPtrSetImpl<Value> &visited,
                                     ArrayRef<int64_t> blockSizes) {
  if (!visited.insert(mem).second)
    return;
  for (OpOperand &use : mem.getUses()) {
    Operation *user = use.getOwner();
    SmallVector<bool> dims;

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
        analyzeConstantIndexUses(sub.getResult(), viewRank, throughCalls, view,
                                 visited, {});
        if (!view.complete) {
          info.complete = false;
          return;
        }
        info.throughViews = true;
        info.accesses += view.accesses;
        info.affineAccesses += view.affineAccesses;
        bool indexConst = getConstantIndexValue(sub.getIndex()).has_value();

        bool rowSelect = sub.isRowSelect();
        if (view.accesses) {
          for (unsigned dimensionIndex = 0; dimensionIndex < rank;
               ++dimensionIndex) {
            bool candidateValue;
            if (dimensionIndex == 0)
              candidateValue = indexConst && (rowSelect || view.constantDim[0]);
            else
              candidateValue = view.constantDim[rowSelect ? dimensionIndex - 1
                                                          : dimensionIndex];
            info.constantDim[dimensionIndex] =
                info.constantDim[dimensionIndex] && candidateValue;
          }
        }
        continue;
      }
    }
    if (auto callSite = dyn_cast<func::CallOp>(user);
        callSite && throughCalls) {
      auto callee = dyn_cast_or_null<func::FuncOp>(callSite.resolveCallable());
      unsigned index = use.getOperandNumber();
      if (!callee || callee.isExternal() || index >= callee.getNumArguments() ||
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
      dims = constantDimsOfAffine(store.getAffineMap(), store.getMapOperands(),
                                  blockSizes);
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
    for (unsigned dimensionIndex = 0; dimensionIndex < rank; ++dimensionIndex)
      info.constantDim[dimensionIndex] =
          info.constantDim[dimensionIndex] && dims[dimensionIndex];
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
  SmallVector<PartitionChoice, 2> parts;
  std::string reason;
  /// None although rule (b) applies: memory banking could not split the
  /// array (no affine access), so no spec is written. `reason` says why.
  bool unbankable = false;
};

/// The inputs of the automatic rules (a)-(c).
struct AutomaticRules {
  int64_t completeThreshold = 4;            ///< (a), elements
  int64_t constantIndexMinExtent = 2;       ///< (b), elements
  int64_t constantIndexMaxExtent = 64;      ///< (b), elements; 0: no limit
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
static bool hasOnlyUserPartition(Operation *def, const AutomaticRules &rules) {
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
static int64_t partExtent(Operation *def, MemRefType memRefType,
                          unsigned dimensionIndex) {
  int64_t extent = memRefType.getDimSize(dimensionIndex);
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
    if (dim.getInt() != static_cast<int64_t>(dimensionIndex) + 1 &&
        dim.getInt() != 0)
      continue;
    if (kind.getValue() == "cyclic" || kind.getValue() == "block")
      extent = (extent + factor.getInt() - 1) / factor.getInt();
  }
  return extent;
}

/// Whether rules (a)-(c) may look at an array `def` of type `ty` at all: a
/// static array of words the user has not given a storage pragma.
static bool isAutomaticCandidate(Operation *def, MemRefType memRefType,
                                 const AutomaticRules &rules) {
  if (!memRefType.hasStaticShape())
    return false;
  Type elt = memRefType.getElementType();
  if (!elt.isIntOrFloat() && !isa<IndexType>(elt))
    return false;
  for (StringRef pragma : rules.userStoragePragmas)
    if (def->hasAttr(pragma))
      return false;
  return true;
}

/// Rule (a), small arrays, whatever their accesses (also those passed on to a
/// call): complete_threshold counts elements, not bits (int[4] fires, char[5]
/// does not; partition_chk.md R5). It holds for globals and function
/// statics as for locals (VITIS_NOTES N7 (a), kernel w9rv_r1_glob4).
static AutomaticPartition decideSmallArray(MemRefType memRefType,
                                           const AutomaticRules &rules) {
  AutomaticPartition decision;
  int64_t completeThreshold = rules.completeThreshold;
  int64_t elements = memRefType.getNumElements();
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
static AutomaticPartition decideFromConstantIndices(
    Operation *def, MemRefType memRefType, const ConstantIndexInfo &info,
    const AutomaticRules &rules, bool afterUser, bool onlyB) {
  AutomaticPartition decision;
  unsigned rank = memRefType.getRank();
  if (!info.complete || info.accesses == 0)
    return decision;
  if (onlyB && llvm::all_of(info.constantDim,
                            [](bool candidateValue) { return candidateValue; }))
    return decision;
  bool allConstant = llvm::all_of(
      info.constantDim, [](bool candidateValue) { return candidateValue; });

  bool userComplete = afterUser && userCompleteEveryDim(def, memRefType);
  if (info.throughViews && (!allConstant || (afterUser && !userComplete)))
    return decision;

  if ((!afterUser || (userComplete && info.throughViews)) && allConstant) {
    decision.kind = AutomaticPartition::Registers;
    decision.reason = "every one of the " + std::to_string(info.accesses) +
                      " access(es) uses a constant index in every dimension: "
                      "scalarised into registers (Vitis front end, alloca "
                      "gone in a.o.1; partition.md R5)";
    return decision;
  }

  SmallVector<unsigned, 2> tooLarge;
  for (unsigned dimensionIndex = 0; dimensionIndex < rank; ++dimensionIndex) {
    if (!info.constantDim[dimensionIndex] ||
        memRefType.getDimSize(dimensionIndex) < rules.constantIndexMinExtent)
      continue;
    if (rules.constantIndexMaxExtent > 0 &&
        partExtent(def, memRefType, dimensionIndex) >
            rules.constantIndexMaxExtent) {
      tooLarge.push_back(dimensionIndex);
      continue;
    }
    decision.parts.push_back(
        {dimensionIndex, memRefType.getDimSize(dimensionIndex)});
  }
  if (decision.parts.empty()) {
    if (!tooLarge.empty())
      decision.reason =
          "dimension " + std::to_string(tooLarge.front() + 1) +
          " is indexed only by constants, but its extent (per part of a "
          "user partition) " +
          std::to_string(partExtent(def, memRefType, tooLarge.front())) +
          " exceeds constant_index.max_extent " +
          std::to_string(rules.constantIndexMaxExtent) +
          ": left whole (Vitis does not partition it; VITIS_NOTES N61)";
    return decision;
  }
  std::string dims;
  llvm::raw_string_ostream os(dims);
  llvm::interleave(
      decision.parts, os,
      [&](const PartitionChoice &portValue) { os << (portValue.dim + 1); },
      ", ");
  if (info.affineAccesses == 0 && !rules.nonAffineArrays) {

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

static AutomaticPartition decideAutomaticPartition(memref::AllocaOp localAlloca,
                                                   const AutomaticRules &rules,
                                                   bool &afterUser) {
  AutomaticPartition decision;
  MemRefType memRefType = localAlloca.getType();
  Operation *def = localAlloca.getOperation();

  afterUser = rules.afterUserPartition &&
              hasOnlyUserPartition(localAlloca.getOperation(), rules) &&
              memRefType.hasStaticShape() &&
              (memRefType.getElementType().isIntOrFloat() ||
               isa<IndexType>(memRefType.getElementType()));
  bool pipo = !afterUser && hasOnlyPipoStream(def, rules) &&
              memRefType.hasStaticShape() &&
              (memRefType.getElementType().isIntOrFloat() ||
               isa<IndexType>(memRefType.getElementType()));
  if (!afterUser && !pipo && !isAutomaticCandidate(def, memRefType, rules))
    return decision;

  if (!afterUser && !pipo) {
    decision = decideSmallArray(memRefType, rules);
    if (decision.kind != AutomaticPartition::None)
      return decision;
  }

  SmallVector<int64_t> blockSizes;
  if (afterUser && rules.blockOffset)
    blockSizes = userBlockSizes(def, memRefType);
  ConstantIndexInfo info =
      analyzeConstantIndices(localAlloca.getResult(), memRefType.getRank(),
                             rules.throughCalls, blockSizes);
  return decideFromConstantIndices(def, memRefType, info, rules, afterUser,
                                   pipo);
}

/// The constant element index of a load / store of `mem`, if every index
/// folds (getConstantIndexValue through the composed affine map).
static std::optional<SmallVector<int64_t>> constantElement(Operation *op) {
  SmallVector<int64_t> out;
  auto fromAffine = [&](AffineMap map, ValueRange mapOperands) -> bool {
    SmallVector<Value, 8> operands(mapOperands.begin(), mapOperands.end());
    fullyComposeAffineMapAndOperands(&map, &operands);
    AffineMap folded = foldConstantIndexOperands(map, operands);
    for (AffineExpr entryValue : folded.getResults()) {
      auto candidateValue = dyn_cast<AffineConstantExpr>(entryValue);
      if (!candidateValue)
        return false;
      out.push_back(candidateValue.getValue());
    }
    return true;
  };
  auto fromIndices = [&](ValueRange indices) -> bool {
    for (Value valueHandle : indices) {
      std::optional<int64_t> candidateValue =
          getConstantIndexValue(valueHandle);
      if (!candidateValue)
        return false;
      out.push_back(*candidateValue);
    }
    return true;
  };
  bool ok = false;
  if (auto lowerIndex = dyn_cast<AffineLoadOp>(op))
    ok = fromAffine(lowerIndex.getAffineMap(), lowerIndex.getMapOperands());
  else if (auto stringValue = dyn_cast<AffineStoreOp>(op))
    ok = fromAffine(stringValue.getAffineMap(), stringValue.getMapOperands());
  else if (auto lowerIndex = dyn_cast<memref::LoadOp>(op))
    ok = fromIndices(lowerIndex.getIndices());
  else if (auto stringValue = dyn_cast<memref::StoreOp>(op))
    ok = fromIndices(stringValue.getIndices());
  if (!ok)
    return std::nullopt;
  return out;
}

/// The elements of `mem` (an array, or a callee parameter it is bound to)
/// some used load reads, into `read`; `ownStores` collects the stores of the
/// array's own function. False when an access or use cannot be resolved to
/// constant elements (then every element counts as read).
static bool collectReadElements(Value mem, bool own,
                                std::set<SmallVector<int64_t>> &read,
                                SmallVectorImpl<Operation *> &ownStores,
                                SmallPtrSetImpl<Value> &visited) {
  if (!visited.insert(mem).second)
    return true;
  for (OpOperand &use : mem.getUses()) {
    Operation *user = use.getOwner();
    if (isa<AffineLoadOp, memref::LoadOp>(user)) {
      if (user->use_empty())
        continue;
      std::optional<SmallVector<int64_t>> entryValue = constantElement(user);
      if (!entryValue)
        return false;
      read.insert(*entryValue);
      continue;
    }
    if (auto stringValue = dyn_cast<AffineStoreOp>(user);
        stringValue && stringValue.getMemRef() == mem) {
      if (own)
        ownStores.push_back(user);
      continue;
    }
    if (auto stringValue = dyn_cast<memref::StoreOp>(user);
        stringValue && stringValue.getMemRef() == mem) {
      if (own)
        ownStores.push_back(user);
      continue;
    }
    if (auto callSite = dyn_cast<func::CallOp>(user)) {
      auto callee = dyn_cast_or_null<func::FuncOp>(callSite.resolveCallable());
      unsigned elementCount = use.getOperandNumber();
      if (!callee || callee.isExternal() ||
          elementCount >= callee.getNumArguments() ||
          callee.getArgument(elementCount).getType() != mem.getType())
        return false;
      if (!collectReadElements(callee.getArgument(elementCount), false, read,
                               ownStores, visited))
        return false;
      continue;
    }
    return false;
  }
  return true;
}

/// Stores into an element of a registers array (hls.registers: scalarised,
/// each element its own register) that no used load reads, in the array's
/// function or in the kept callees it is passed to, are deleted, and then
/// the values computed only for them (their loads of other arrays): Vitis
/// passes a kept callee only the elements it reads and drops the rest
/// (VITIS_NOTES N110: kernel w9r15p_dw_dead, 7 of 49 window elements live,
/// `tile` 6 copies; Dehazing calculate_median 29 parameters, Min_RGB_Tile
/// 29 reads per iteration). Returns the number of stores deleted.
static unsigned removeUnreadRegisterElements(ModuleOp module) {
  SmallVector<memref::AllocaOp> arrays;
  module.walk([&](memref::AllocaOp a) {
    if (a->hasAttr(kRegistersAttrName) && a.getType().hasStaticShape())
      arrays.push_back(a);
  });
  unsigned erased = 0;
  for (memref::AllocaOp a : arrays) {
    std::set<SmallVector<int64_t>> read;
    SmallVector<Operation *> stores;
    SmallPtrSet<Value, 4> visited;

    if (!collectReadElements(a.getResult(), true, read, stores, visited) ||
        read.empty())
      continue;
    SmallVector<Operation *> worklist;
    unsigned erasedHere = 0;
    for (Operation *st : stores) {
      std::optional<SmallVector<int64_t>> entryValue = constantElement(st);
      if (!entryValue || read.count(*entryValue))
        continue;
      ++erasedHere;
      for (Value valueHandle : st->getOperands())
        if (Operation *def = valueHandle.getDefiningOp();
            def && valueHandle != a.getResult())
          worklist.push_back(def);
      st->erase();
      ++erased;
    }

    llvm::DenseSet<Operation *> gone;
    while (!worklist.empty()) {
      Operation *op = worklist.pop_back_val();
      if (gone.contains(op) || !isOpTriviallyDead(op))
        continue;
      for (Value valueHandle : op->getOperands())
        if (Operation *def = valueHandle.getDefiningOp())
          worklist.push_back(def);
      gone.insert(op);
      op->erase();
    }

    if (erasedHere) {
      std::string why;
      if (auto resultValue =
              a->getAttrOfType<StringAttr>(kRegistersReasonAttrName))
        why = resultValue.getValue().str();
      why += "; " + std::to_string(erasedHere) +
             " store(s) into element(s) no used load reads deleted, with "
             "the values computed only for them (VITIS_NOTES N110)";
      a->setAttr(kRegistersReasonAttrName,
                 StringAttr::get(a.getContext(), why));
    }
  }
  return erased;
}

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
    rules.afterUserPartition = cfgPartitioning->constantIndexAfterUserPartition;
    rules.nonAffineArrays = cfgPartitioning->constantIndexNonAffineArrays;
    rules.pipoStreams = cfgPartitioning->constantIndexPipoStreams;
    rules.globals = cfgPartitioning->constantIndexGlobals;
    rules.throughCalls = cfgPartitioning->constantIndexThroughCalls;
    rules.blockOffset = cfgPartitioning->constantIndexBlockOffset;
    DenseSet<Value> decided;
    Builder passBuilder(func.getContext());
    func.walk([&](memref::AllocaOp localAlloca) {
      Operation *def = localAlloca.getOperation();
      if (def->hasAttr(kRegistersAttrName)) {
        decided.insert(localAlloca.getResult());
        return;
      }
      bool afterUser = false;
      AutomaticPartition decision =
          decideAutomaticPartition(localAlloca, rules, afterUser);
      auto varName = def->getAttrOfType<StringAttr>(kVarNameAttr);
      std::string name =
          varName ? varName.getValue().str() : std::string("<unnamed>");
      if (decision.unbankable) {
        ++runStats.unbankable;
        LLVM_DEBUG(llvm::dbgs()
                   << "array '" << name << "': " << decision.reason << "\n");
        if (emitRemarks)
          mlir::emitRemark(localAlloca.getLoc())
              << "array '" << name << "' left whole: " << decision.reason;
      }
      if (decision.kind == AutomaticPartition::None) {

        if (!decision.unbankable && !decision.reason.empty() && emitRemarks)
          mlir::emitRemark(localAlloca.getLoc())
              << "array '" << name << "' left whole: " << decision.reason;
        return;
      }
      decided.insert(localAlloca.getResult());
      if (decision.kind == AutomaticPartition::Registers) {
        def->setAttr(kRegistersAttrName, passBuilder.getUnitAttr());
        def->setAttr(kRegistersReasonAttrName,
                     passBuilder.getStringAttr(decision.reason));
        ++runStats.registers;
        LLVM_DEBUG(llvm::dbgs() << "array '" << name << "': registers ("
                                << decision.reason << ")\n");
        if (emitRemarks)
          mlir::emitRemark(localAlloca.getLoc())
              << "array '" << name << "' -> registers: " << decision.reason;
        return;
      }
      ArrayRef<int64_t> shape = localAlloca.getType().getShape();
      ArrayAttr automatic = buildPartitionAttr(
          passBuilder, decision.parts, shape, varName, kSourceConstantIndex);
      if (afterUser) {

        SmallVector<Attribute> merged;
        if (auto user = def->getAttrOfType<ArrayAttr>(kPartitionAttr))
          llvm::append_range(merged, user.getValue());
        llvm::append_range(merged, automatic.getValue());
        automatic = passBuilder.getArrayAttr(merged);
      }
      def->setAttr(kPartitionAttr, automatic);
      def->setAttr(kReasonAttr, passBuilder.getStringAttr(decision.reason));
      ++runStats.constantDims;
      if (decision.parts.size() > 1)
        ++runStats.multiConstantDims;
      LLVM_DEBUG(llvm::dbgs()
                 << "array '" << name << "': " << decision.reason << "\n");
      if (emitRemarks)
        for (const PartitionChoice &part : decision.parts)
          mlir::emitRemark(localAlloca.getLoc())
              << "Automatically partitioning array '" << name << "' dimension "
              << part.dim + 1 << " completely based on constant index";
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
  void applyConstantIndexGlobals(func::FuncOp func, const AutomaticRules &rules,
                                 DenseSet<Value> &decided) {
    if (!rules.globals)
      return;
    auto module = func->getParentOfType<ModuleOp>();
    Builder passBuilder(func.getContext());
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
      MemRefType memRefType = global.getType();
      bool wordArray = memRefType.hasStaticShape() &&
                       (memRefType.getElementType().isIntOrFloat() ||
                        isa<IndexType>(memRefType.getElementType()));
      bool afterUser = rules.afterUserPartition && wordArray &&
                       hasOnlyUserPartition(def, rules);
      bool pipo = !afterUser && wordArray && hasOnlyPipoStream(def, rules);
      if (!afterUser && !pipo && !isAutomaticCandidate(def, memRefType, rules))
        return;
      unsigned rank = memRefType.getRank();
      ConstantIndexInfo info;
      info.constantDim.assign(rank, true);
      std::optional<SymbolTable::UseRange> symbolUses =
          SymbolTable::getSymbolUses(def, module);
      if (!symbolUses)
        return;
      for (const SymbolTable::SymbolUse &use : *symbolUses) {
        auto globalUse = dyn_cast<memref::GetGlobalOp>(use.getUser());
        if (!globalUse)
          return;
        ConstantIndexInfo gi = analyzeConstantIndices(
            globalUse.getResult(), rank, rules.throughCalls,
            afterUser && rules.blockOffset ? userBlockSizes(def, memRefType)
                                           : SmallVector<int64_t>());
        if (!gi.complete)
          return;
        info.accesses += gi.accesses;
        info.affineAccesses += gi.affineAccesses;
        for (unsigned dimensionIndex = 0; dimensionIndex < rank;
             ++dimensionIndex)
          info.constantDim[dimensionIndex] = info.constantDim[dimensionIndex] &&
                                             gi.constantDim[dimensionIndex];
      }
      AutomaticPartition decision = decideFromConstantIndices(
          def, memRefType, info, rules, afterUser, true);
      if (decision.kind != AutomaticPartition::ConstantDims)
        return;
      ArrayAttr automatic = buildPartitionAttr(
          passBuilder, decision.parts, memRefType.getShape(),
          def->getAttrOfType<StringAttr>(kVarNameAttr), kSourceConstantIndex);
      if (afterUser) {
        SmallVector<Attribute> merged;
        if (auto user = def->getAttrOfType<ArrayAttr>(kPartitionAttr))
          llvm::append_range(merged, user.getValue());
        llvm::append_range(merged, automatic.getValue());
        automatic = passBuilder.getArrayAttr(merged);
      }
      def->setAttr(kPartitionAttr, automatic);
      def->setAttr(kReasonAttr, passBuilder.getStringAttr(decision.reason));
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
    Builder passBuilder(func.getContext());
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
      def->setAttr(kRegistersAttrName, passBuilder.getUnitAttr());
      def->setAttr(kRegistersReasonAttrName,
                   passBuilder.getStringAttr(decision.reason));
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

      if (userPipelined)
        mlir::emitWarning(loop.getLoc())
            << "hls.pipeline on a loop that still contains loops: unroll them "
               "before infer-vitis-split-array; nothing is inferred from it";
      return std::nullopt;
    }
    return getUserTargetII(loop).value_or(targetIIValue);
  }

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
    maxFactorValue =
        maxFactor.hasValue() ? static_cast<int64_t>(maxFactor) : inf.maxFactor;
    rotatingBanksValue = resolveOption(rotatingBanks, inf.rotatingBanks);
    const circt::hlsest::ArrayPartitionOptions &ap =
        cfg.tool.hls.options.arrayPartition;
    includePortsValue = resolveOption(includePorts, ap.includePorts);
    completeThresholdValue = completeThreshold.hasValue()
                                 ? static_cast<int64_t>(completeThreshold)
                                 : ap.completeThreshold;
    throughputDrivenValue = throughputDriven.hasValue()
                                ? std::string(throughputDriven)
                                : ap.throughputDriven;
    userStoragePragmas = cfg.frontend.userStoragePragmas;
  }

  /// The counters of the current run (the pass adds them to its
  /// statistics).
  circt::hlsest::PartitionStatistics runStats;

  void runOnOperation() override {
    for (func::FuncOp func : getOperation().getOps<func::FuncOp>()) {
      if (func.isExternal())
        continue;
      if (failed(runOnFunction(func)))
        return signalPassFailure();
    }
    if (circt::hlsest::Config::get()
            .tool.hls.middleEnd.deadMemory.unreadRegisterElements)
      removeUnreadRegisterElements(getOperation());

    if (circt::hlsest::Config::get()
            .tool.hls.pipelineDecision.callOccupancyAfterPartition)
      circt::hls_analysis::refreshCallOccupancies(getOperation());
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

    const circt::hlsest::Config &cfg = circt::hlsest::Config::get();
    circt::hlsest::ConfigDiagnostics diag;
    std::unique_ptr<circt::hlsest::PartitionPolicy> policy =
        circt::hlsest::PluginRegistry<
            circt::hlsest::PartitionPolicy>::instance()
            .create(cfg.tool.hls.partitioning.policy, cfg, diag);
    if (!policy) {
      InFlightDiagnostic dimensionIndex =
          func.emitError("infer-vitis-split-array: ");
      llvm::interleave(diag.errors, dimensionIndex, "; ");
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

    DenseSet<Value> decided;
    if (tdOff || autoPartitions)
      decided = applyAutomaticPartitions(func);

    TermTable terms;
    llvm::MapVector<Value, SmallVector<PipelineRegion, 2>> pressure;
    func.walk([&](AffineForOp loop) {
      if (std::optional<unsigned> ii = getPipelineII(loop)) {
        ++runStats.regions;
        collectRegions(loop, *ii, terms, pressure);
      }
    });

    Builder passBuilder(func.getContext());
    for (auto &entry : pressure) {
      Value mem = entry.first;
      ArrayRef<PipelineRegion> regions = entry.second;
      Operation *def = mem.getDefiningOp();
      auto arg = dyn_cast<BlockArgument>(mem);
      bool isFuncArg = arg && arg.getOwner() == &func.getBody().front();

      if (annotatePressure) {
        ArrayAttr attr = buildPressureAttr(passBuilder, regions);
        if (def)
          def->setAttr(kPressureAttr, attr);
        else if (isFuncArg)
          func.setArgAttr(arg.getArgNumber(), kPressureAttr, attr);
      }

      if (tdOff || decided.contains(mem))
        continue;

      auto memTy = dyn_cast<MemRefType>(mem.getType());
      if (!memTy || memTy.getRank() == 0)
        continue;
      ArrayRef<int64_t> shape = memTy.getShape();
      if (portLimit(regions, {}, pm, rotatingBanksValue).excess == 0)
        continue;

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
        continue;
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

      PartitionPlan plan = inferPartition(
          regions, shape, pm, rotatingBanksValue, maxFactorValue, maxDimsValue,
          cfgPartitioning->inference.maxScannedFactor);

      if (!plan.parts.empty()) {
        ArrayAttr spec =
            buildPartitionAttr(passBuilder, plan.parts, shape, varName);
        if (def)
          def->setAttr(kPartitionAttr, spec);
        else
          func.setArgAttr(arg.getArgNumber(), kPartitionAttr, spec);
        ++runStats.partitioned;

        if (plan.before.region) {
          StringAttr reason = passBuilder.getStringAttr(
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
          AffineForOp worstLoop = worst.loop;
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
  circt::hlsest::PluginRegistry<circt::hlsest::PartitionPolicy>::instance().add(
      "vitis-td",
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
