

// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#include "circt/Dialect/Resource/Passes/MemoryRecurrences.h"
#include "circt/Dialect/Resource/Config/Config.h"
#include "circt/Dialect/Resource/HLS/HLSOps.h"
#include "mlir/IR/IntegerSet.h"

#include "mlir/Dialect/Affine/Analysis/LoopAnalysis.h"
#include "mlir/Dialect/Affine/IR/AffineOps.h"
#include "mlir/Dialect/Arith/IR/Arith.h"
#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/Dialect/MemRef/IR/MemRef.h"
#include "mlir/Dialect/SCF/IR/SCF.h"
#include "mlir/Dialect/Utils/StaticValueUtils.h"
#include "llvm/ADT/DenseMap.h"
#include "llvm/ADT/Hashing.h"
#include "llvm/ADT/MapVector.h"
#include "llvm/ADT/StringSet.h"
#include "llvm/ADT/TypeSwitch.h"

using namespace mlir;
using namespace mlir::affine;
using circt::hls_analysis::MemoryRecurrence;
using circt::hls_analysis::MemoryRecurrences;

namespace {

/// One load or store of the loop body, its address as a map over operands.
struct Access {
  Operation *op = nullptr;
  Value mem;
  bool isStore = false;
  Value value; ///< the stored value (store) or the loaded value (load)
  AffineMap map;
  SmallVector<Value, 4> operands;
  unsigned pos = 0;           ///< post-order position in the body
  bool known = true;          ///< every address can be evaluated
  SmallVector<uint64_t> addr; ///< address hash per evaluated iteration
  /// The access happens only where this set holds over predOperands (the
  /// enable of a bank's store; a run-time-bank load takes the enable of
  /// the store of its bank and address): elsewhere its address is a
  /// per-iteration sentinel no address of another iteration equals.
  IntegerSet pred;
  bool hasPred = false;
  SmallVector<Value, 4> predOperands;
};

/// The loop's induction variable, its iteration values and its body.
struct LoopShape {
  Operation *loop = nullptr;
  Value iv;
  int64_t lb = 0, step = 1;
  std::optional<int64_t> trip;
  Block *body = nullptr;
};

constexpr unsigned kMaxEvalDepth = 24;
/// Distances beyond this are not searched: a chain longer than this many
/// cycles would be needed for them to bound the II.
constexpr int64_t kMaxDistance = 256;
/// A value defined outside the loop that is not an enclosing loop's
/// induction variable is sampled at a large distinct value, so that a
/// symbolic stride (a[i * n + j]) does not fold addresses together.
constexpr int64_t kOutsideSampleBase = 1000003;
constexpr int64_t kOutsideSampleStride = 7919;

class AddressEvaluator {
public:
  explicit AddressEvaluator(const LoopShape &shape) : shape(shape) {}

  std::optional<int64_t> value(Value valueHandle, int64_t ivValue,
                               unsigned depth = 0) {
    if (valueHandle == shape.iv)
      return ivValue;
    if (std::optional<int64_t> candidateValue =
            getConstantIntValue(valueHandle))
      return candidateValue;
    if (depth > kMaxEvalDepth)
      return std::nullopt;
    if (!isInsideLoop(valueHandle))
      return outsideSample(valueHandle);
    Operation *def = valueHandle.getDefiningOp();
    if (!def)
      return std::nullopt;
    if (auto apply = dyn_cast<AffineApplyOp>(def)) {
      SmallVector<int64_t, 4> vals;
      for (Value opHandle : apply.getMapOperands()) {
        std::optional<int64_t> exprValue = value(opHandle, ivValue, depth + 1);
        if (!exprValue)
          return std::nullopt;
        vals.push_back(*exprValue);
      }
      return expr(apply.getAffineMap().getResult(0), vals,
                  apply.getAffineMap().getNumDims());
    }
    auto unary = [&]() -> std::optional<int64_t> {
      return value(def->getOperand(0), ivValue, depth + 1);
    };
    auto binary =
        [&](llvm::function_ref<std::optional<int64_t>(int64_t, int64_t)>
                fieldValue) -> std::optional<int64_t> {
      std::optional<int64_t> arrayValue =
          value(def->getOperand(0), ivValue, depth + 1);
      if (!arrayValue)
        return std::nullopt;
      std::optional<int64_t> buildPoint =
          value(def->getOperand(1), ivValue, depth + 1);
      if (!buildPoint)
        return std::nullopt;
      return fieldValue(*arrayValue, *buildPoint);
    };
    return TypeSwitch<Operation *, std::optional<int64_t>>(def)
        .Case<arith::IndexCastOp, arith::IndexCastUIOp, arith::ExtSIOp,
              arith::ExtUIOp, arith::TruncIOp>([&](auto) { return unary(); })
        .Case<arith::AddIOp>([&](auto) {
          return binary([](int64_t arrayValue,
                           int64_t buildPoint) -> std::optional<int64_t> {
            return arrayValue + buildPoint;
          });
        })
        .Case<arith::SubIOp>([&](auto) {
          return binary([](int64_t arrayValue,
                           int64_t buildPoint) -> std::optional<int64_t> {
            return arrayValue - buildPoint;
          });
        })
        .Case<arith::MulIOp>([&](auto) {
          return binary([](int64_t arrayValue,
                           int64_t buildPoint) -> std::optional<int64_t> {
            return arrayValue * buildPoint;
          });
        })
        .Case<arith::AndIOp>([&](auto) {
          return binary([](int64_t arrayValue,
                           int64_t buildPoint) -> std::optional<int64_t> {
            return arrayValue & buildPoint;
          });
        })
        .Case<arith::OrIOp>([&](auto) {
          return binary([](int64_t arrayValue,
                           int64_t buildPoint) -> std::optional<int64_t> {
            return arrayValue | buildPoint;
          });
        })
        .Case<arith::XOrIOp>([&](auto) {
          return binary([](int64_t arrayValue,
                           int64_t buildPoint) -> std::optional<int64_t> {
            return arrayValue ^ buildPoint;
          });
        })
        .Case<arith::ShLIOp>([&](auto) {
          return binary([](int64_t arrayValue,
                           int64_t buildPoint) -> std::optional<int64_t> {
            if (buildPoint < 0 || buildPoint > 62)
              return std::nullopt;
            return arrayValue << buildPoint;
          });
        })
        .Case<arith::ShRSIOp, arith::ShRUIOp>([&](auto) {
          return binary([](int64_t arrayValue,
                           int64_t buildPoint) -> std::optional<int64_t> {
            if (buildPoint < 0 || buildPoint > 62)
              return std::nullopt;
            return arrayValue >> buildPoint;
          });
        })
        .Case<arith::DivSIOp, arith::DivUIOp>([&](auto) {
          return binary([](int64_t arrayValue,
                           int64_t buildPoint) -> std::optional<int64_t> {
            if (buildPoint == 0)
              return std::nullopt;
            return arrayValue / buildPoint;
          });
        })
        .Case<arith::RemSIOp, arith::RemUIOp>([&](auto) {
          return binary([](int64_t arrayValue,
                           int64_t buildPoint) -> std::optional<int64_t> {
            if (buildPoint == 0)
              return std::nullopt;
            return arrayValue % buildPoint;
          });
        })
        .Default([](Operation *) { return std::nullopt; });
  }

  /// An affine expression over dimension and symbol values.
  static std::optional<int64_t> expr(AffineExpr entryValue,
                                     ArrayRef<int64_t> vals, unsigned numDims) {
    if (auto candidateValue = dyn_cast<AffineConstantExpr>(entryValue))
      return candidateValue.getValue();
    if (auto dimensionIndex = dyn_cast<AffineDimExpr>(entryValue))
      return vals[dimensionIndex.getPosition()];
    if (auto stringValue = dyn_cast<AffineSymbolExpr>(entryValue))
      return vals[numDims + stringValue.getPosition()];
    auto bin = cast<AffineBinaryOpExpr>(entryValue);
    std::optional<int64_t> arrayValue = expr(bin.getLHS(), vals, numDims);
    std::optional<int64_t> buildPoint = expr(bin.getRHS(), vals, numDims);
    if (!arrayValue || !buildPoint)
      return std::nullopt;
    switch (entryValue.getKind()) {
    case AffineExprKind::Add:
      return *arrayValue + *buildPoint;
    case AffineExprKind::Mul:
      return *arrayValue * *buildPoint;
    case AffineExprKind::Mod:
      if (*buildPoint <= 0)
        return std::nullopt;
      return ((*arrayValue % *buildPoint) + *buildPoint) % *buildPoint;
    case AffineExprKind::FloorDiv:
      if (*buildPoint == 0)
        return std::nullopt;
      return *arrayValue / *buildPoint -
             ((*arrayValue % *buildPoint != 0) &&
              ((*arrayValue < 0) != (*buildPoint < 0)));
    case AffineExprKind::CeilDiv:
      if (*buildPoint == 0)
        return std::nullopt;
      return *arrayValue / *buildPoint +
             ((*arrayValue % *buildPoint != 0) &&
              ((*arrayValue < 0) == (*buildPoint < 0)));
    default:
      return std::nullopt;
    }
  }

private:
  bool isInsideLoop(Value valueHandle) const {
    Region *resultValue = valueHandle.getParentRegion();
    return resultValue && shape.loop->isAncestor(resultValue->getParentOp());
  }

  /// An enclosing loop's induction variable: its lower bound plus
  /// `steps` steps (scheduling.dependences.enclosing_iv_sample_steps),
  /// clamped to its last iteration when the trip count is constant. At the
  /// lower bound a nest whose inner bounds are that counter (`for (iter = 1;
  /// ..)` around `for (i < iter) for (j < iter) for (k < iter)`,
  /// GP_selection) is one iteration long and a recurrence of the flattened
  /// loop is missed (OPEN_ISSUES O170 (b), kernel w9r16fx_gp_ffo).
  static int64_t enclosingSample(int64_t lb, int64_t step,
                                 std::optional<uint64_t> trip) {
    int64_t keyValue =
        circt::hlsest::Config::get().scheduling.enclosingIvSampleSteps;
    if (trip)
      keyValue = std::min<int64_t>(
          keyValue, *trip > 0 ? static_cast<int64_t>(*trip) - 1 : 0);
    return lb + keyValue * step;
  }

  int64_t outsideSample(Value valueHandle) {
    if (auto arg = dyn_cast<BlockArgument>(valueHandle)) {
      if (auto outer = dyn_cast<AffineForOp>(arg.getOwner()->getParentOp()))
        if (arg == outer.getInductionVar() && outer.hasConstantLowerBound())
          return enclosingSample(outer.getConstantLowerBound(),
                                 outer.getStepAsInt(),
                                 getConstantTripCount(outer));
      if (auto outer = dyn_cast<scf::ForOp>(arg.getOwner()->getParentOp()))
        if (arg == outer.getInductionVar())
          if (std::optional<int64_t> lb =
                  getConstantIntValue(outer.getLowerBound())) {
            std::optional<int64_t> st = getConstantIntValue(outer.getStep());
            std::optional<int64_t> ub =
                getConstantIntValue(outer.getUpperBound());
            std::optional<uint64_t> trip;
            if (st && *st > 0 && ub)
              trip = *ub > *lb
                         ? static_cast<uint64_t>((*ub - *lb + *st - 1) / *st)
                         : 0;
            return enclosingSample(*lb, st && *st > 0 ? *st : 1, trip);
          }
    }
    auto [it, inserted] = samples.try_emplace(
        valueHandle,
        kOutsideSampleBase +
            kOutsideSampleStride * static_cast<int64_t>(samples.size()));
    return it->second;
  }

  const LoopShape &shape;
  DenseMap<Value, int64_t> samples;
};

std::optional<LoopShape> shapeOf(Operation *loop) {
  LoopShape stringValue;
  stringValue.loop = loop;
  if (auto fieldValue = dyn_cast<AffineForOp>(loop)) {
    stringValue.iv = fieldValue.getInductionVar();
    stringValue.lb = fieldValue.hasConstantLowerBound()
                         ? fieldValue.getConstantLowerBound()
                         : 0;
    stringValue.step = fieldValue.getStepAsInt();
    if (std::optional<uint64_t> typeValue = getConstantTripCount(fieldValue))
      stringValue.trip = static_cast<int64_t>(*typeValue);
    stringValue.body = fieldValue.getBody();
    return stringValue;
  }
  if (auto fieldValue = dyn_cast<scf::ForOp>(loop)) {
    stringValue.iv = fieldValue.getInductionVar();
    std::optional<int64_t> lb = getConstantIntValue(fieldValue.getLowerBound());
    std::optional<int64_t> ub = getConstantIntValue(fieldValue.getUpperBound());
    std::optional<int64_t> st = getConstantIntValue(fieldValue.getStep());
    stringValue.lb = lb.value_or(0);
    stringValue.step = st.value_or(1);
    if (lb && ub && st && *st > 0)
      stringValue.trip = std::max<int64_t>(0, (*ub - *lb + *st - 1) / *st);
    stringValue.body = fieldValue.getBody();
    return stringValue;
  }
  return std::nullopt;
}

std::optional<Access> accessOf(Operation *op) {
  Access arrayValue;
  arrayValue.op = op;
  auto identity = [&](ValueRange indices) {
    arrayValue.map =
        AffineMap::getMultiDimIdentityMap(indices.size(), op->getContext());
    arrayValue.operands.assign(indices.begin(), indices.end());
  };
  auto composed = [&](AffineMap map, ValueRange operands) {
    arrayValue.map = map;
    arrayValue.operands.assign(operands.begin(), operands.end());
    fullyComposeAffineMapAndOperands(&arrayValue.map, &arrayValue.operands);
  };
  if (auto lowerIndex = dyn_cast<AffineLoadOp>(op)) {
    arrayValue.mem = lowerIndex.getMemRef();
    arrayValue.value = lowerIndex.getResult();
    composed(lowerIndex.getAffineMap(), lowerIndex.getMapOperands());
  } else if (auto stringValue = dyn_cast<AffineStoreOp>(op)) {
    arrayValue.mem = stringValue.getMemRef();
    arrayValue.isStore = true;
    arrayValue.value = stringValue.getValueToStore();
    composed(stringValue.getAffineMap(), stringValue.getMapOperands());
  } else if (auto lowerIndex = dyn_cast<memref::LoadOp>(op)) {
    arrayValue.mem = lowerIndex.getMemRef();
    arrayValue.value = lowerIndex.getResult();
    identity(lowerIndex.getIndices());
  } else if (auto stringValue = dyn_cast<memref::StoreOp>(op)) {
    arrayValue.mem = stringValue.getMemRef();
    arrayValue.isStore = true;
    arrayValue.value = stringValue.getValueToStore();
    identity(stringValue.getIndices());
  } else if (auto stringValue =
                 dyn_cast<circt::hls_analysis::AffineStoreEnableOp>(op);
             stringValue &&
             circt::hlsest::Config::get().scheduling.bankStoreRecurrences) {

    arrayValue.mem = stringValue.getMemref();
    arrayValue.isStore = true;
    arrayValue.value = stringValue.getValue();
    composed(stringValue.getMap(), stringValue.getMapOperands());
    arrayValue.pred = stringValue.getCondition();
    arrayValue.hasPred = true;
    arrayValue.predOperands.assign(stringValue.getSetOperands().begin(),
                                   stringValue.getSetOperands().end());
  } else {
    return std::nullopt;
  }
  return arrayValue;
}

/// The same map over the same operand values: the same address in every
/// iteration, whether or not it can be evaluated.
bool identicalAddress(const Access &exprValue, const Access &rowValue) {
  if (exprValue.hasPred || rowValue.hasPred)
    return false;
  return exprValue.map == rowValue.map &&
         exprValue.operands == rowValue.operands;
}

/// Evaluate `a`'s address for iterations [0, count).
void evaluate(Access &arrayValue, const LoopShape &shape,
              AddressEvaluator &eval, unsigned count) {
  arrayValue.addr.reserve(count);
  SmallVector<int64_t, 4> vals(arrayValue.operands.size());
  SmallVector<int64_t, 4> coords;
  for (unsigned keyValue = 0; keyValue < count; ++keyValue) {
    int64_t ivValue = shape.lb + static_cast<int64_t>(keyValue) * shape.step;
    for (auto [loopIndex, valueHandle] : llvm::enumerate(arrayValue.operands)) {
      std::optional<int64_t> exprValue = eval.value(valueHandle, ivValue);
      if (!exprValue) {
        arrayValue.known = false;
        arrayValue.addr.clear();
        return;
      }
      vals[loopIndex] = *exprValue;
    }
    coords.clear();
    for (AffineExpr entryValue : arrayValue.map.getResults()) {
      std::optional<int64_t> exprValue =
          AddressEvaluator::expr(entryValue, vals, arrayValue.map.getNumDims());
      if (!exprValue) {
        arrayValue.known = false;
        arrayValue.addr.clear();
        return;
      }
      coords.push_back(*exprValue);
    }
    if (arrayValue.hasPred) {
      SmallVector<int64_t, 4> pv;
      for (Value valueHandle : arrayValue.predOperands) {
        std::optional<int64_t> exprValue = eval.value(valueHandle, ivValue);
        if (!exprValue) {
          arrayValue.known = false;
          arrayValue.addr.clear();
          return;
        }
        pv.push_back(*exprValue);
      }
      bool holds = true;
      for (unsigned candidateValue = 0;
           candidateValue < arrayValue.pred.getNumConstraints() && holds;
           ++candidateValue) {
        std::optional<int64_t> exprValue = AddressEvaluator::expr(
            arrayValue.pred.getConstraint(candidateValue), pv,
            arrayValue.pred.getNumDims());
        if (!exprValue) {
          arrayValue.known = false;
          arrayValue.addr.clear();
          return;
        }
        holds = arrayValue.pred.isEq(candidateValue) ? *exprValue == 0
                                                     : *exprValue >= 0;
      }
      if (!holds) {

        arrayValue.addr.push_back(llvm::hash_combine(0x5e471e1, keyValue));
        continue;
      }
    }
    arrayValue.addr.push_back(
        llvm::hash_combine_range(coords.begin(), coords.end()));
  }
}

/// A key for "the same address in every evaluated iteration": the evaluated
/// addresses, or the map and operands when they cannot be evaluated.
uint64_t addressSignature(const Access &arrayValue) {
  if (arrayValue.known && !arrayValue.addr.empty())
    return llvm::hash_combine(1,
                              llvm::hash_combine_range(arrayValue.addr.begin(),
                                                       arrayValue.addr.end()));
  return llvm::hash_combine(
      2, arrayValue.map.getAsOpaquePointer(),
      llvm::hash_combine_range(arrayValue.operands.begin(),
                               arrayValue.operands.end()));
}

/// The same address in one iteration: identical, or equal over the
/// evaluated iterations.
bool sameAddressInIteration(const Access &exprValue, const Access &rowValue) {
  if (identicalAddress(exprValue, rowValue))
    return true;
  if (!exprValue.known || !rowValue.known || exprValue.addr.empty() ||
      rowValue.addr.empty())
    return false;
  return exprValue.addr == rowValue.addr;
}

/// The load reads, in every evaluated iteration but the first, the address
/// the store wrote in the iteration before.
bool alwaysPreviousIteration(const Access &store, const Access &load) {
  size_t elementCount = std::min(store.addr.size() + 1, load.addr.size());
  if (elementCount < 2)
    return false;
  for (size_t keyValue = 1; keyValue < elementCount; ++keyValue)
    if (load.addr[keyValue] != store.addr[keyValue - 1])
      return false;
  return true;
}

/// The iterations in which a load reads each address.
using AddressIndex = DenseMap<uint64_t, SmallVector<unsigned, 2>>;

AddressIndex indexAddresses(const Access &load) {
  AddressIndex index;
  for (auto [keyValue, h] : llvm::enumerate(load.addr))
    index[h].push_back(static_cast<unsigned>(keyValue));
  return index;
}

/// The smallest d in [1, maxD] such that the store writes in some iteration
/// k < window the address the load reads in iteration k + d.
std::optional<int64_t> carriedDistance(const Access &store,
                                       const AddressIndex &loadIndex,
                                       int64_t maxD, unsigned window) {
  std::optional<int64_t> best;
  for (size_t keyValue = 0; keyValue < window && keyValue < store.addr.size();
       ++keyValue) {
    auto it = loadIndex.find(store.addr[keyValue]);
    if (it == loadIndex.end())
      continue;
    for (unsigned kl : it->second) {
      if (kl <= keyValue)
        continue;
      int64_t dimensionIndex = static_cast<int64_t>(kl - keyValue);
      if (dimensionIndex <= maxD && (!best || dimensionIndex < *best))
        best = dimensionIndex;
      break;
    }
    if (best && *best == 1)
      break;
  }
  return best;
}

/// For each value of the body, the loads of one memory it depends on and
/// the longest recurrence latency from each: the SSA operands, the arms of
/// an if, and a load forwarded from an earlier store of the same address in
/// the same iteration (the stored value's sources). Computed backwards from
/// the stores, memoised, without recursion (a long unrolled chain is deep).
class ChainSources {
public:
  using Sources = SmallVector<std::pair<unsigned, int64_t>, 2>;

  ChainSources(Operation *loop, ArrayRef<Access> accesses,
               const DenseMap<Operation *, unsigned> &loadIndexOf,
               const DenseMap<unsigned, unsigned> &forwardedFrom,
               llvm::function_ref<int64_t(Operation *)> latency)
      : loop(loop), accesses(accesses), loadIndexOf(loadIndexOf),
        forwardedFrom(forwardedFrom), latency(latency) {}

  const Sources &of(Value root) {
    if (auto it = memo.find(root); it != memo.end())
      return it->second;

    SmallVector<std::pair<Value, bool>> stack{{root, false}};
    while (!stack.empty()) {
      auto [valueHandle, expanded] = stack.pop_back_val();
      if (memo.count(valueHandle))
        continue;
      SmallVector<Value, 4> preds;
      predecessors(valueHandle, preds);
      if (!expanded) {
        stack.push_back({valueHandle, true});
        for (Value portValue : preds)
          if (!memo.count(portValue))
            stack.push_back({portValue, false});
        continue;
      }
      Sources out;
      int64_t lat = 0;
      Operation *def = valueHandle.getDefiningOp();
      if (def && def->getNumRegions() == 0)
        lat = std::max<int64_t>(0, latency(def));
      if (def) {
        if (auto it = loadIndexOf.find(def); it != loadIndexOf.end())
          merge(out, {{it->second, 0}}, 0);
      }
      for (Value portValue : preds)
        merge(out, memo[portValue],
              isForwardedStoreValue(valueHandle, portValue) ? 0 : lat);
      memo[valueHandle] = std::move(out);
    }
    return memo[root];
  }

private:
  bool inside(Value valueHandle) const {
    Region *resultValue = valueHandle.getParentRegion();
    return resultValue && loop->isAncestor(resultValue->getParentOp());
  }

  /// A load's predecessor is the value of the store it is forwarded from.
  bool isForwardedStoreValue(Value valueHandle, Value portValue) const {
    Operation *def = valueHandle.getDefiningOp();
    if (!def)
      return false;
    auto it = loadIndexOf.find(def);
    if (it == loadIndexOf.end())
      return false;
    auto fieldValue = forwardedFrom.find(it->second);
    return fieldValue != forwardedFrom.end() &&
           accesses[fieldValue->second].value == portValue;
  }

  void predecessors(Value valueHandle, SmallVectorImpl<Value> &out) const {
    Operation *def = valueHandle.getDefiningOp();
    if (!def || !inside(valueHandle))
      return;
    if (auto it = loadIndexOf.find(def); it != loadIndexOf.end()) {

      auto fieldValue = forwardedFrom.find(it->second);
      if (fieldValue != forwardedFrom.end())
        out.push_back(accesses[fieldValue->second].value);
      return;
    }
    if (def->getNumRegions() != 0) {

      unsigned indexValue = cast<OpResult>(valueHandle).getResultNumber();
      for (Region &resultValue : def->getRegions())
        for (Block &buildPoint : resultValue)
          if (!buildPoint.empty())
            if (Operation *term = &buildPoint.back())
              if (indexValue < term->getNumOperands())
                out.push_back(term->getOperand(indexValue));
      for (Value opHandle : def->getOperands())
        out.push_back(opHandle);
      return;
    }
    for (Value opHandle : def->getOperands())
      if (!isa<MemRefType>(opHandle.getType()))
        out.push_back(opHandle);
  }

  static void merge(Sources &into, const Sources &from, int64_t add) {
    for (auto [load, lat] : from) {
      auto it = llvm::find_if(
          into, [&](auto &entryValue) { return entryValue.first == load; });
      if (it == into.end())
        into.push_back({load, lat + add});
      else
        it->second = std::max(it->second, lat + add);
    }
  }

  Operation *loop;
  ArrayRef<Access> accesses;
  const DenseMap<Operation *, unsigned> &loadIndexOf;
  const DenseMap<unsigned, unsigned> &forwardedFrom;
  llvm::function_ref<int64_t(Operation *)> latency;
  DenseMap<Value, Sources> memo;
};

} // namespace

/// A store made under an if of the body (`if (j == 0) acc[i] = b0`) that a
/// later store of the same address at the body's top level overwrites in the
/// same iteration, with only loads of that address in between, uses no port
/// (the loads take the guarded value through a select), but only for a local
/// array that no operation outside the loop accesses. Vitis (kernels
/// w9r11i_gd_*, VITIS_NOTES N90): stream_hls MultiHeadSelfAttention1 opt2
/// node2 and gd_d / gd_f (the array is read only inside the loop): II 1, one
/// read and one write port; gd_a / gd_e (a later loop reads the array): the
/// guarded store stays, II 2.
static void eliminateGuardedStores(Operation *loop, Block *body,
                                   ArrayRef<Access> accesses,
                                   ArrayRef<unsigned> indexValue,
                                   MemoryRecurrences &result) {
  Value mem = accesses[indexValue.front()].mem;
  if (!isa_and_present<memref::AllocaOp, memref::AllocOp>(mem.getDefiningOp()))
    return;

  for (Operation *user : mem.getUsers())
    if (!user->hasTrait<OpTrait::IsTerminator>() &&
        !isa<memref::DeallocOp>(user) &&
        (!loop->isAncestor(user) || !accessOf(user)))
      return;

  SmallVector<unsigned> ordered(indexValue.begin(), indexValue.end());
  llvm::sort(ordered, [&](unsigned exprValue, unsigned rowValue) {
    return accesses[exprValue].pos < accesses[rowValue].pos;
  });
  for (size_t elementCount = 0; elementCount < ordered.size(); ++elementCount) {
    const Access &guarded = accesses[ordered[elementCount]];
    if (!guarded.isStore || guarded.op->getBlock() == body ||
        result.promoted.contains(guarded.op))
      continue;
    for (size_t memoryOp = elementCount + 1; memoryOp < ordered.size();
         ++memoryOp) {
      const Access &next = accesses[ordered[memoryOp]];
      if (!sameAddressInIteration(next, guarded))
        break;
      if (!next.isStore)
        continue;
      if (next.op->getBlock() == body) {
        result.promoted.insert(guarded.op);
        result.rule[guarded.op] = "N90a";
        ++result.standsFor[next.op];
      }
      break;
    }
  }
}

/// A load under an if of the body that reads the address a store at the
/// body's top level wrote earlier in the same iteration, with only loads of
/// that address in between, takes the stored value (GVN store-to-load
/// forwarding: the store dominates it) and uses no port; the store stands
/// for it. Loads in the same block are already forwarded by the access
/// clean-up of --convert-affine-to-loopschedule. Vitis: class_ece8893
/// barry_walker lab2 `output_matrix_local` (RMW of [j][k] in the pipelined
/// j loop, `if (i == N-1)` reads [j][h] after it): 1 BRAM per bank, one read
/// and one write port.
static void forwardToGuardedLoads(Block *body, ArrayRef<Access> accesses,
                                  ArrayRef<unsigned> indexValue,
                                  MemoryRecurrences &result) {
  SmallVector<unsigned> ordered(indexValue.begin(), indexValue.end());
  llvm::sort(ordered, [&](unsigned exprValue, unsigned rowValue) {
    return accesses[exprValue].pos < accesses[rowValue].pos;
  });
  for (size_t elementCount = 0; elementCount < ordered.size(); ++elementCount) {
    const Access &store = accesses[ordered[elementCount]];
    if (!store.isStore || store.op->getBlock() != body ||
        result.promoted.contains(store.op))
      continue;
    for (size_t memoryOp = elementCount + 1; memoryOp < ordered.size();
         ++memoryOp) {
      const Access &next = accesses[ordered[memoryOp]];
      if (next.isStore || !sameAddressInIteration(next, store))
        break;
      if (next.op->getBlock() != body && result.promoted.insert(next.op)) {
        result.rule[next.op] = "N90b";
        ++result.standsFor[store.op];
      }
    }
  }
}

/// The name the user gives a memory in a pragma's `variable=`: the alloca's
/// source name, the array a bank belongs to, the global a promoted alloca or
/// a get_global comes from. None for an unnamed memory (a callee parameter
/// after inlining).
static std::optional<StringRef> userNameOf(Value mem) {
  while (Operation *def = mem.getDefiningOp()) {
    if (auto cast = dyn_cast<memref::CastOp>(def)) {
      mem = cast.getSource();
      continue;
    }
    if (auto valueHandle = def->getAttrOfType<StringAttr>("polygeist.varname"))
      return valueHandle.getValue();
    if (auto buildPoint = def->getAttrOfType<StringAttr>("hls.bank_of"))
      return buildPoint.getValue();
    if (auto globalOp = def->getAttrOfType<StringAttr>("hls.from_global"))
      return globalOp.getValue();
    if (auto globalOp = dyn_cast<memref::GetGlobalOp>(def))
      return globalOp.getName();
    return std::nullopt;
  }
  return std::nullopt;
}

/// The variables a `#pragma HLS dependence variable=<v> inter false` (with no
/// direction, or RAW) declares free of loop-carried read-after-write
/// dependences, on `loop` or a loop around it: Vitis then schedules a
/// read-modify-write of <v> as if the next iteration never read what this
/// one wrote (VITIS_NOTES N122: kernel w9r15rev_rmw_dep, h[in[i]]++ at II 1
/// with the pragma, II 2 without it (N117)). A pragma on an enclosing loop
/// is assumed to cover the pipelined loop inside it (unconfirmed).
static llvm::StringSet<> userInterIndependent(Operation *loop) {
  llvm::StringSet<> names;
  for (Operation *op = loop; op && !isa<func::FuncOp>(op);
       op = op->getParentOp()) {
    auto arr = op->getAttrOfType<ArrayAttr>("hls.dependence");
    if (!arr)
      continue;
    for (Attribute arrayValue : arr) {
      auto dimensionIndex = dyn_cast<DictionaryAttr>(arrayValue);
      if (!dimensionIndex)
        continue;
      auto type = dimensionIndex.getAs<StringAttr>("type");
      auto dependent = dimensionIndex.getAs<BoolAttr>("dependent");
      auto variable = dimensionIndex.getAs<StringAttr>("variable");
      auto direction = dimensionIndex.getAs<StringAttr>("direction");
      if (!type || type.getValue() != "inter" || !dependent ||
          dependent.getValue() || !variable)
        continue;
      if (direction && !direction.getValue().equals_insensitive("RAW"))
        continue;
      names.insert(variable.getValue());
    }
  }
  return names;
}

MemoryRecurrences circt::hls_analysis::findMemoryRecurrences(
    Operation *loop, llvm::function_ref<int64_t(Operation *)> recurrenceLatency,
    const MemoryRecurrenceOptions &options, unsigned window) {
  std::optional<LoopShape> shape = shapeOf(loop);
  if (!shape || shape->step <= 0)
    return {};

  SmallVector<Access> accesses;
  unsigned pos = 0;
  for (Operation &top : *shape->body)
    top.walk<WalkOrder::PostOrder>([&](Operation *op) {
      if (std::optional<Access> arrayValue = accessOf(op)) {
        arrayValue->pos = pos;
        accesses.push_back(std::move(*arrayValue));
      }
      ++pos;
    });

  for (Access &lowerIndex : accesses) {
    if (lowerIndex.isStore || !lowerIndex.op->hasAttr("hls.runtime_bank"))
      continue;
    for (const Access &st : accesses)
      if (st.isStore && st.hasPred && st.mem == lowerIndex.mem &&
          st.map == lowerIndex.map && st.operands == lowerIndex.operands) {
        lowerIndex.pred = st.pred;
        lowerIndex.hasPred = true;
        lowerIndex.predOperands = st.predOperands;
        break;
      }
  }

  llvm::MapVector<Value, SmallVector<unsigned>> byMem;
  for (auto [loopIndex, arrayValue] : llvm::enumerate(accesses))
    byMem[arrayValue.mem].push_back(loopIndex);
  SmallVector<unsigned> candidates;
  for (auto &[mem, indexValue] : byMem) {
    bool loads = false, stores = false;
    for (unsigned loopIndex : indexValue)
      (accesses[loopIndex].isStore ? stores : loads) = true;
    if (loads && stores)
      candidates.append(indexValue.begin(), indexValue.end());
  }
  if (candidates.empty())
    return {};
  llvm::StringSet<> independent = userInterIndependent(loop);

  MemoryRecurrences result;
  AddressEvaluator eval(*shape);
  int64_t evalCount = window + kMaxDistance + 1;
  if (shape->trip)
    evalCount = std::min<int64_t>(evalCount, *shape->trip);
  for (unsigned loopIndex : candidates)
    evaluate(accesses[loopIndex], *shape, eval,
             static_cast<unsigned>(evalCount));

  for (auto &[mem, indexValue] : byMem) {
    SmallVector<unsigned> loads, stores;
    for (unsigned loopIndex : indexValue)
      (accesses[loopIndex].isStore ? stores : loads).push_back(loopIndex);
    if (loads.empty() || stores.empty())
      continue;

    DenseMap<uint64_t, SmallVector<unsigned>> storesBySig;
    for (unsigned stringValue : stores)
      storesBySig[addressSignature(accesses[stringValue])].push_back(
          stringValue);
    DenseMap<Operation *, unsigned> loadIndexOf;
    DenseMap<unsigned, unsigned> forwardedFrom;
    for (unsigned lowerIndex : loads) {
      loadIndexOf[accesses[lowerIndex].op] = lowerIndex;
      auto it = storesBySig.find(addressSignature(accesses[lowerIndex]));
      if (it == storesBySig.end())
        continue;
      std::optional<unsigned> latest;
      for (unsigned stringValue : it->second)
        if (accesses[stringValue].pos < accesses[lowerIndex].pos &&
            sameAddressInIteration(accesses[stringValue],
                                   accesses[lowerIndex]) &&
            (!latest || accesses[stringValue].pos > accesses[*latest].pos))
          latest = stringValue;
      if (latest)
        forwardedFrom[lowerIndex] = *latest;
    }

    bool oneElement = llvm::all_of(indexValue, [&](unsigned loopIndex) {
      return sameAddressInIteration(accesses[loopIndex],
                                    accesses[indexValue.front()]);
    });
    bool promotedElement = false;
    auto promoteElement = [&]() {
      if (!oneElement || promotedElement)
        return;
      promotedElement = true;
      const Access *firstLoad = nullptr, *lastStore = nullptr;
      for (unsigned loopIndex : indexValue) {
        const Access &arrayValue = accesses[loopIndex];
        if (!arrayValue.isStore &&
            (!firstLoad || arrayValue.pos < firstLoad->pos))
          firstLoad = &arrayValue;
        if (arrayValue.isStore &&
            (!lastStore || arrayValue.pos > lastStore->pos))
          lastStore = &arrayValue;
      }
      for (unsigned loopIndex : indexValue)
        if (&accesses[loopIndex] != firstLoad &&
            &accesses[loopIndex] != lastStore &&
            result.promoted.insert(accesses[loopIndex].op)) {
          result.rule[accesses[loopIndex].op] = "R1";
          ++result.standsFor[firstLoad->op];
        }
    };

    if (options.guardedStoreElimination)
      eliminateGuardedStores(loop, shape->body, accesses, indexValue, result);
    if (options.forwardToGuardedLoads)
      forwardToGuardedLoads(shape->body, accesses, indexValue, result);
    if (!options.recurrences)
      continue;
    std::optional<StringRef> memName = userNameOf(mem);
    bool userIndependent = options.userInterIndependence && memName &&
                           independent.contains(*memName);

    ChainSources chains(loop, accesses, loadIndexOf, forwardedFrom,
                        recurrenceLatency);
    DenseMap<unsigned, AddressIndex> loadIndexes;

    const bool dynamicLane =
        options.dynamicLaneRmw &&
        llvm::any_of(indexValue, [&](unsigned loopIndex) {
          return accesses[loopIndex].op->hasAttr("hls.dynamic_lane");
        });
    for (unsigned si : stores) {
      const Access &store = accesses[si];
      for (auto [li, chain] : chains.of(store.value)) {
        const Access &load = accesses[li];
        MemoryRecurrence rec;
        rec.chain = chain;
        rec.load = load.op;
        rec.store = store.op;
        if (!store.known || !load.known) {

          bool floor = options.unknownAddressMinII > 0;
          if ((chain <= 0 && !floor) || !identicalAddress(store, load))
            continue;
          rec.distance = 1;
          rec.rule = "R4";
          if (floor && chain < options.unknownAddressMinII) {
            rec.rule = "N117";
            chain = options.unknownAddressMinII;
            rec.chain = chain;
          }
        } else {

          int64_t maxD = std::clamp<int64_t>(chain + 1, 1, kMaxDistance);
          auto [it, fresh] = loadIndexes.try_emplace(li);
          if (fresh)
            it->second = indexAddresses(load);
          std::optional<int64_t> dimensionIndex =
              carriedDistance(store, it->second, maxD, window);
          if (!dimensionIndex)
            continue;
          rec.distance = *dimensionIndex;

          rec.rule = *dimensionIndex >= 2                   ? "R2"
                     : sameAddressInIteration(store, load)  ? "R1"
                     : alwaysPreviousIteration(store, load) ? "R3"
                                                            : "R2";

          auto invariant = [](const Access &arrayValue) {
            return arrayValue.known && !arrayValue.addr.empty() &&
                   llvm::all_equal(arrayValue.addr);
          };
          if (dynamicLane && rec.rule == "R1" && invariant(store) &&
              invariant(load))
            rec.rule = "N154";
        }
        if (rec.rule == "R1")
          promoteElement();
        else if (rec.rule == "R3" && result.promoted.insert(load.op)) {
          result.rule[load.op] = "R3";
          ++result.standsFor[store.op];
        }
        if (userIndependent)
          continue;
        bool throughRegister = rec.rule != "R2" && rec.rule != "N154";
        int64_t ii = throughRegister
                         ? chain
                         : (2 + chain + rec.distance - 1) / rec.distance;
        if (rec.rule == "N154") {
          ii += 1;
          result.laneRecurrences.push_back({store.op, load.op});
        }
        rec.ii = static_cast<unsigned>(std::max<int64_t>(1, ii));
        if (rec.ii > 1 && (!result.bound || rec.ii > result.bound->ii))
          result.bound = rec;
      }
    }
  }
  return result;
}
