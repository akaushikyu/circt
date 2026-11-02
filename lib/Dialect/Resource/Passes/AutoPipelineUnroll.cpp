//===- AutoPipelineUnroll.cpp - Vitis automatic pipeline/unroll/flatten ---===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// Reproduces the automatic pipeline / unroll / flatten decision of Vitis HLS
// (`config_compile -pipeline_loops`, default 64). Evidence: VITIS_NOTES.md
// N3, exp-notes/pipeline_unroll.md and pipeline_unroll_chk.md (64 kernels).
//
// Per function:
//
//  0. User `hls.unroll` pragmas are applied first (complete, or by factor),
//     as Vitis does before its automatic decision. A loop that keeps
//     a partial user unroll (factor below the trip count, 1 included) is never
//     unrolled completely for an enclosing automatic pipeline: it blocks the
//     auto-pipelining of every loop around it and is pipelined
//     itself (Vitis ground truth of spector_hls/fir, forgebench/mult_op_p1,
//     diff_dims_p1, diff_orders_p1: the partially unrolled loops - and their
//     user-made copies - are the pipelined ones, their parents are not). Vitis
//     keeps the remainder iterations of a trip count the factor does not divide
//     in the unrolled body (exit checks), it has no epilogue loop:
//     the cleanup loop MLIR generates is unrolled completely into
//     straight-line code after the loop, and only the main
//     loop carries `hls.unroll_partial` (none does when the main
//     loop is left with a single iteration and MLIR replaces it by
//     its body).
//
//  1. Perfect-nest collapse. A loop whose body holds exactly one
//  nested loop
//     and no memory currentOperation outside it (register-only code is allowed)
//     forms a perfect nest with that loop; chains collapse into ONE
//     loop for the decision, with the product of the trip counts.
//     Perfectness is judged as Vitis sees it after LLVM LICM and scalar
//     promotion: a load whose address does not change with the inner
//     loop, from a memory the inner loop never writes, is
//     hoisted into the outer body, and the accesses of a memory touched at one
//     inner-invariant address only
//     (`acc[i] += ...`) are promoted to a register with the load before and
//     the store after the inner loop. Both make the nest imperfect;
//     pure arithmetic never does. The hoist rule is confirmed for integer
//     elements only: Vitis flattens the same nest when the invariant load
//     reads a floating-point element (see "Perfectness and floating point"
//     below; option float-loads-perfect, default on). Promotion makes the
//     nest imperfect whatever the element type. A loop marked
//     `hls.uncounted` (cgeist: a counter narrower than its runtime bound,
//     `for (uint8_t i = 0; i < n; i++)` with int n) is never the outer
//     loop of a collapsed pair: Vitis, which cannot compute its trip
//     count, treats it like the outer loop of an imperfect nest
//     (VITIS_NOTES.md N15: the loop is pipelined and a <= 64-trip
//     perfect inner loop unrolled into it, where an `int` counter
//     gets the inner loop pipelined and flattened). When its perfect
//     inner loop is pipelined instead, it is flattened into it in
//     step 3 despite its runtime bound, as the collapse would have done (N15:
//     nc_f_u8 like nc_f_int). A runtime-trip scf.for (a bound loaded inside an
//     enclosing loop) whose body is a perfect nest over a
//     constant-trip affine chain is collapsed the same way: the nest is
//     decided as that chain and the scf.for is flattened into its pipeline
//     (VITIS_NOTES.md N53 (b), isPerfectRuntimePair / decideRuntime).
//
//  2. Top-down decision. A (collapsed) loop P is pipelined iff every
//  loop
//     nested anywhere inside it - loops of called functions included - has a
//     constant trip count and the product of the trip counts along every
//     nesting path inside P is <= T. Every loop inside P is then
//     completely unrolled (all levels, callee loops included), after the
//     invariant loads have been hoisted and the register-promotable accesses
//     promoted out of the loops being unrolled - and, once they are unrolled,
//     out of the pipelined loop itself (option promote-pipelined,
//     default on) - so the pipelined body carries the accesses Vitis schedules
//     (one `acc[i]` load and store, not 64 of each; `acc[0..7] +=` of an
//     unrolled body becomes eight register recurrences and the loop
//     reads nothing of acc). A loop containing no loop is
//     pipelined as it is, whatever its trip count. If P fails, each child
//     loop is decided on its own. Functions are decided callers
//     first, so that the loops of a kept callee (`#pragma HLS inline off`) take
//     part in the caller's test as they are written (VITIS_NOTES.md N14 R7);
//     the callee's remaining loops are decided in the callee, and a caller
//     loop is never flattened into a callee's loop (step
//     3).
//
//  3. Flattening. A loop Q that was not pipelined, has exactly one
//  child
//     loop C (directly in its body, no call boundary), constant
//     bounds, and whose C (constant trip counts) ends up pipelined, is
//     converted and flattened by Vitis into C's pipeline. C is tagged with
//     `hls.flattened_parents = N` (counting Q and, recursively, Q's parents
//     and the perfect-chain members above C) so that later passes treat the
//     induction variables of those N ancestors as loop-variant for
//     C's pipeline: --convert-affine-to-loopschedule does not hoist such loads
//     and --infer-vitis-split-array / --bram-analysis count them.
//
// Tags: the pipelined loop gets `hls.pipeline = [{II = 0 : i32,
// source = "auto"}]` and, when it unrolled loops, `hls.auto_unrolled =
// [{factor, loc},
// ...]` (a record for --bram-debug). A user `hls.pipeline` is kept as written
// and always wins (the loop is pipelined whatever T, everything
// inside it is unrolled); a user `hls.pipeline_off` loop is never
// auto-pipelined. `pipeline-loops=0` disables the automatic decision; user
// pragmas are still applied.
//
// Perfectness and floating point (VITIS_NOTES.md N3, exp-src/
// pipeline_unroll_float): a load at an inner-invariant address makes the nest
// imperfect only when the loaded element is an integer. The same nest
// reading a float element (`lo[i][j] = la[i][j] * lb[i]`, float `lb`) is
// converted into a perfect nest and flattened by Vitis
// (rv_st_hoist_f_m64_n64, rv_rmw_hoist_f_m8_n64 / _m64_n64, pf_fmul_m8_n64,
// pf_fadd_m8_n64, pf_fmac_m8_n32, pf_srchoist_m8_n64 - the load written in
// the outer body in the source -, pm_floatarr_iop_m8_n64 - float arrays,
// integer arithmetic; polybench atax lp3/lp4, bicg lp1/lp2), while every
// integer twin is unrolled (rv_st_hoist_m64_n64, rv_rmw_hoist_m8_n64,
// pi_add_m8_n64, pi_mul3_m8_n64, pl_mul_m8_n64, pi_srchoist_m8_n64,
// pm_intarr_fop_m8_n64 - int arrays, float arithmetic), and so is a body
// with one float and one int invariant load (pf_twoload_m8_n64). It is the
// type of the load, not of the arithmetic. Register promotion of an
// accumulator makes the nest imperfect for float elements too
// (pf_memred_m8_n16; atax lp1/lp2, bicg lp3/lp4, gesummv, mvt). Vitis'
// mechanism is not visible in the IR dumps (the decision precedes a.o.1.ll,
// where the float load is hoisted all the same). Option float-loads-perfect
// applies this rule; it is on by default (MEMOS.md M8, decision #3 of
// 2026-10-10, together with the exactclass harness shim); =false gives the
// original T3 model, where every hoistable invariant load breaks
// perfectness. The rule keys on the MLIR element type, so it is right where
// that is the type Vitis sees: with the exactclass shim an ap_fixed is an
// integer, as in Vitis; the scalar shim (ap_fixed = float/double) and the
// exact shim (W <= 16: _Float16) make ap_fixed loads float, against N3.
//
//===----------------------------------------------------------------------===//

#include "circt/Dialect/Resource/Passes/AutoPipelineUnroll.h"
#include "../Plugins/Builtin/Builtins.h"
#include "circt/Dialect/Resource/Config/ConfigUtils.h"
#include "circt/Dialect/Resource/Passes/AffineUnroll.h"
#include "circt/Dialect/Resource/Passes/CallInstances.h"
#include "circt/Dialect/Resource/Passes/DoWhileFlatten.h"
#include "circt/Dialect/Resource/Passes/FloatOps.h"
#include "circt/Dialect/Resource/Passes/FoldUnrolledGuards.h"
#include "circt/Dialect/Resource/Passes/LoopPragmas.h"
#include "circt/Dialect/Resource/Passes/ReadOnlyMemory.h"
#include "circt/Dialect/Resource/Plugins/PassPolicies.h"
#include "circt/Dialect/Resource/Plugins/Registry.h"
#include "mlir/Dialect/Affine/Analysis/LoopAnalysis.h"
#include "mlir/Dialect/Affine/IR/AffineOps.h"
#include "mlir/Dialect/Affine/LoopUtils.h"
#include "mlir/Dialect/Arith/IR/Arith.h"
#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/Dialect/LLVMIR/LLVMTypes.h"
#include "mlir/Dialect/Math/IR/Math.h"
#include "mlir/Dialect/MemRef/IR/MemRef.h"
#include "mlir/Dialect/SCF/IR/SCF.h"
#include "mlir/IR/Builders.h"
#include "mlir/IR/BuiltinOps.h"
#include "mlir/IR/Diagnostics.h"
#include "mlir/IR/IRMapping.h"
#include "mlir/IR/PatternMatch.h"
#include "mlir/IR/SymbolTable.h"
#include "mlir/Interfaces/CallInterfaces.h"
#include "mlir/Interfaces/LoopLikeInterface.h"
#include "mlir/Interfaces/SideEffectInterfaces.h"
#include "mlir/Pass/Pass.h"
#include "llvm/ADT/DenseMap.h"
#include "llvm/ADT/DenseSet.h"
#include "llvm/ADT/MapVector.h"
#include "llvm/ADT/SmallPtrSet.h"
#include "llvm/ADT/SmallVector.h"
#include "llvm/ADT/StringSwitch.h"
#include "llvm/Support/Debug.h"

#include <functional>
#include <limits>
#include <map>
#include <optional>
#include <set>
#include <tuple>
#include <vector>

#define DEBUG_TYPE "auto-pipeline-unroll"

using namespace mlir;
using namespace mlir::affine;

/// The C library name `op` calls: an external func.call's symbol, or a
/// math dialect sin / cos (cgeist lowers `cos(double)` to math.cos):
/// "cos" for f64, "cosf" for f32.
static std::string libraryCallName(Operation *currentOperation,
                                   SymbolTableCollection &symbolTables) {
  if (auto callSite = dyn_cast<CallOpInterface>(currentOperation)) {
    auto calleeFunction = dyn_cast_or_null<func::FuncOp>(
        callSite.resolveCallableInTable(&symbolTables));
    return calleeFunction && calleeFunction.isExternal()
               ? calleeFunction.getSymName().str()
               : "";
  }
  llvm::StringRef base = llvm::StringSwitch<llvm::StringRef>(
                             currentOperation->getName().getStringRef())
                             .Case("math.sin", "sin")
                             .Case("math.cos", "cos")
                             .Default("");
  if (base.empty() || currentOperation->getNumResults() != 1)
    return "";
  Type typeValue = currentOperation->getResult(0).getType();
  if (typeValue.isF64())
    return base.str();
  if (typeValue.isF32())
    return (base + "f").str();
  return "";
}

static bool hasLoopingLibraryCall(Operation *currentOperation,
                                  SymbolTableCollection &symbolTables) {
  const std::vector<std::string> &names =
      circt::hlsest::Config::get()
          .tool.hls.pipelineDecision.libraryCallsWithLoops;
  if (names.empty())
    return false;
  std::string name = libraryCallName(currentOperation, symbolTables);
  return !name.empty() && llvm::is_contained(names, name);
}

using circt::hls_analysis::getFlattenedParents;
using circt::hls_analysis::kCallDepthAttr;
using circt::hls_analysis::kCallOccupancyAttr;
using circt::hls_analysis::kLoopAutoUnrolledAttr;
using circt::hls_analysis::kLoopCallBoundaryAttr;
using circt::hls_analysis::kLoopFlattenedParentsAttr;
using circt::hls_analysis::kLoopFlattenRefusedAttr;
using circt::hls_analysis::kLoopPipelineAttr;
using circt::hls_analysis::kLoopPipelineAutoSource;
using circt::hls_analysis::kLoopPipelineOffAttr;
using circt::hls_analysis::kLoopPromotedElementIterArgsAttr;
using circt::hls_analysis::kLoopUncountedAttr;
using circt::hls_analysis::kLoopUnrollAttr;
using circt::hls_analysis::kLoopUnrollOffAttr;
using circt::hls_analysis::kLoopUnrollPartialAttr;
using circt::hls_analysis::kLoopUnrollRuntimeGuardedAttr;

namespace {

//===----------------------------------------------------------------------===//
// Pragma attributes
//===----------------------------------------------------------------------===//

/// Set on a loop only for the duration of its loopUnrollByFactor
/// call, so that the main loop and the cleanup clone can be found
/// afterwards.
constexpr llvm::StringLiteral kUnrollPendingAttr = "hls.unroll_partial_pending";
/// A pipelined loop whose register promotion waits for its parents'
/// flatten decisions (promoteNowOrLater).
constexpr llvm::StringLiteral kPendingPromotionAttr = "hls.promotion_pending";

/// First dictionary of a `[{...}]` (or bare `{...}`) pragma attribute.
static DictionaryAttr firstPragmaDictionary(Attribute attributeValue) {
  if (auto array = dyn_cast_or_null<ArrayAttr>(attributeValue))
    attributeValue = array.empty() ? Attribute() : array[0];
  return dyn_cast_or_null<DictionaryAttr>(attributeValue);
}

static bool marksAutoPipelineTag(Attribute attributeValue) {
  DictionaryAttr dict = firstPragmaDictionary(attributeValue);
  if (!dict)
    return false;
  auto source = dict.getAs<StringAttr>("source");
  return source && source.getValue() == kLoopPipelineAutoSource;
}

/// A `hls.pipeline` the user wrote (not this pass's own tag).
static bool hasUserPipelineTag(Operation *chosenLoopForPipeline) {
  Attribute attributeValue = chosenLoopForPipeline->getAttr(kLoopPipelineAttr);
  return attributeValue && !marksAutoPipelineTag(attributeValue) &&
         !chosenLoopForPipeline->hasAttr(kLoopPipelineOffAttr);
}

/// User unroll factor of `loop`; 0 = complete; nullopt = no pragma.
static std::optional<uint64_t>
unrollFactorFromPragma(Operation *chosenLoopForPipeline) {
  if (chosenLoopForPipeline->hasAttr(kLoopUnrollOffAttr))
    return std::nullopt;
  Attribute attributeValue = chosenLoopForPipeline->getAttr(kLoopUnrollAttr);
  if (!attributeValue)
    return std::nullopt;
  DictionaryAttr dict = firstPragmaDictionary(attributeValue);
  if (!dict)
    return 0;
  if (auto unrollFactor = dict.getAs<IntegerAttr>("factor"))
    return unrollFactor.getInt() > 0
               ? static_cast<uint64_t>(unrollFactor.getInt())
               : 0;
  return 0;
}

static void markAutoPipelineTag(Operation *chosenLoopForPipeline) {
  Builder passBuilder(chosenLoopForPipeline->getContext());
  chosenLoopForPipeline->setAttr(
      kLoopPipelineAttr,
      passBuilder.getArrayAttr({passBuilder.getDictionaryAttr(
          {passBuilder.getNamedAttr("II", passBuilder.getI32IntegerAttr(0)),
           passBuilder.getNamedAttr(
               "source",
               passBuilder.getStringAttr(kLoopPipelineAutoSource))})}));
}

/// A loop whose trip count is not known when the decision is made:
/// an `scf.for` whose bounds are no affine symbols (a bound loaded inside an
/// enclosing loop, `count = n[j]; while (count >= 16)`, which cgeist
/// cannot raise to an affine.for) or an `scf.while` (an exit that depends on
/// data). Vitis pipelines such a loop like any other when every
/// loop inside it has a constant trip count and the trip-count
/// products inside it are <= T (VITIS_NOTES.md N53: kernels o72_fa / o72_fe /
/// o72_wa / o72_xw / shafix_v4, trip `?` or `1 ~ 268435456`, inner and callee
/// loops unrolled). A constant-bound scf.for is raised to an affine.for by
/// --vitis-fold (raise-counted-loops) before this pass.
static bool isDynamicLoop(Operation *currentOperation) {
  return isa<scf::ForOp, scf::WhileOp>(currentOperation);
}

static void noteFlattenFailure(AffineForOp chosenLoopForPipeline) {
  chosenLoopForPipeline->setAttr(
      kLoopFlattenRefusedAttr,
      UnitAttr::get(chosenLoopForPipeline.getContext()));
}

static void recordFlattenedParents(AffineForOp chosenLoopForPipeline,
                                   unsigned elementTotal) {
  if (elementTotal == 0)
    return;
  Builder passBuilder(chosenLoopForPipeline.getContext());
  chosenLoopForPipeline->setAttr(
      kLoopFlattenedParentsAttr,
      passBuilder.getI64IntegerAttr(getFlattenedParents(chosenLoopForPipeline) +
                                    elementTotal));
}

//===----------------------------------------------------------------------===//
// Memory accesses and the LICM / promotion model
//===----------------------------------------------------------------------===//

/// One affine or memref load/store: its memory and composed address.
struct MemoryAccess {
  Operation *currentOperation = nullptr;
  Value memoryValue;
  bool isWrite = false;
  AffineMap affineMap;
  llvm::SmallVector<Value, 8> inputOperands;
};

/// The composed addresses of one promoteInvariantAccesses call (W9 round 23
/// review D9: its walks composed every access of a fully unrolled body once
/// per memory and again for the candidate memories, hlsyn fdtd-2d-large's
/// 1,190,000-op body). Keyed on the map and the operand values; it lives for
/// one call (ComposedAddressScope), which creates and erases no affine.apply,
/// so a key always names the same composition.
using ComposedAddressKey = std::vector<const void *>;
static thread_local std::map<ComposedAddressKey,
                             std::pair<AffineMap, llvm::SmallVector<Value, 4>>>
    *composedAddressCache = nullptr;
namespace {
struct ComposedAddressScope {
  std::map<ComposedAddressKey,
           std::pair<AffineMap, llvm::SmallVector<Value, 4>>>
      cache;
  decltype(composedAddressCache) enclosingLoop;
  ComposedAddressScope() : enclosingLoop(composedAddressCache) {
    composedAddressCache = &cache;
  }
  ~ComposedAddressScope() { composedAddressCache = enclosingLoop; }
};
} // namespace

static std::optional<MemoryAccess>
accessDescription(Operation *currentOperation) {
  MemoryAccess firstSide;
  firstSide.currentOperation = currentOperation;
  MLIRContext *ctx = currentOperation->getContext();
  if (auto memoryLoad = dyn_cast<AffineLoadOp>(currentOperation)) {
    firstSide.memoryValue = memoryLoad.getMemRef();
    firstSide.affineMap = memoryLoad.getAffineMap();
    firstSide.inputOperands.assign(memoryLoad.getMapOperands().begin(),
                                   memoryLoad.getMapOperands().end());
  } else if (auto storeOperation = dyn_cast<AffineStoreOp>(currentOperation)) {
    firstSide.memoryValue = storeOperation.getMemRef();
    firstSide.isWrite = true;
    firstSide.affineMap = storeOperation.getAffineMap();
    firstSide.inputOperands.assign(storeOperation.getMapOperands().begin(),
                                   storeOperation.getMapOperands().end());
  } else if (auto memoryLoad = dyn_cast<memref::LoadOp>(currentOperation)) {
    firstSide.memoryValue = memoryLoad.getMemRef();
    firstSide.affineMap =
        AffineMap::getMultiDimIdentityMap(memoryLoad.getIndices().size(), ctx);
    firstSide.inputOperands.assign(memoryLoad.getIndices().begin(),
                                   memoryLoad.getIndices().end());
  } else if (auto storeOperation =
                 dyn_cast<memref::StoreOp>(currentOperation)) {
    firstSide.memoryValue = storeOperation.getMemRef();
    firstSide.isWrite = true;
    firstSide.affineMap = AffineMap::getMultiDimIdentityMap(
        storeOperation.getIndices().size(), ctx);
    firstSide.inputOperands.assign(storeOperation.getIndices().begin(),
                                   storeOperation.getIndices().end());
  } else {
    return std::nullopt;
  }
  ComposedAddressKey mapKey;
  if (composedAddressCache) {
    mapKey.reserve(firstSide.inputOperands.size() + 1);
    mapKey.emplace_back(firstSide.affineMap.getAsOpaquePointer());
    for (Value operandValue : firstSide.inputOperands)
      mapKey.emplace_back(operandValue.getAsOpaquePointer());
    auto inductionValue = composedAddressCache->find(mapKey);
    if (inductionValue != composedAddressCache->end()) {
      firstSide.affineMap = inductionValue->second.first;
      firstSide.inputOperands.assign(inductionValue->second.second.begin(),
                                     inductionValue->second.second.end());
      return firstSide;
    }
  }
  fullyComposeAffineMapAndOperands(&firstSide.affineMap,
                                   &firstSide.inputOperands);
  canonicalizeMapAndOperands(&firstSide.affineMap, &firstSide.inputOperands);
  firstSide.affineMap = simplifyAffineMap(firstSide.affineMap);
  if (composedAddressCache)
    composedAddressCache->emplace(
        std::move(mapKey), std::make_pair(firstSide.affineMap,
                                          llvm::SmallVector<Value, 4>(
                                              firstSide.inputOperands.begin(),
                                              firstSide.inputOperands.end())));
  return firstSide;
}

static bool sameAddressAs(const MemoryAccess &firstValue,
                          const MemoryAccess &secondValue) {
  return firstValue.memoryValue == secondValue.memoryValue &&
         firstValue.affineMap == secondValue.affineMap &&
         firstValue.inputOperands == secondValue.inputOperands;
}

/// `nest`, when given, is the outermost loop flattened with
/// `loop`: the address must not change over the flattened nest
/// either.
static bool isInvariantWithin(const MemoryAccess &firstSide,
                              AffineForOp chosenLoopForPipeline,
                              Operation *nestStructure = nullptr) {
  auto outside = [&](Value operandValue) {
    if (!chosenLoopForPipeline.isDefinedOutsideOfLoop(operandValue))
      return false;
    return !nestStructure || !nestStructure->isAncestor(
                                 operandValue.getParentBlock()->getParentOp());
  };
  return outside(firstSide.memoryValue) &&
         llvm::all_of(firstSide.inputOperands, outside);
}

/// True if some op inside `loop` (an affine.for or a runtime
/// loop) may write `mem`, or uses it opaquely.
static bool isWrittenDuringLoop(Value memoryValue,
                                Operation *chosenLoopForPipeline) {
  bool written = false;
  chosenLoopForPipeline->walk([&](Operation *currentOperation) {
    if (currentOperation == chosenLoopForPipeline)
      return WalkResult::advance();
    if (!llvm::is_contained(currentOperation->getOperands(), memoryValue))
      return WalkResult::advance();
    auto eff = dyn_cast<MemoryEffectOpInterface>(currentOperation);
    if (!eff) {
      written = true; // a call, a cast: unknown effects
      return WalkResult::interrupt();
    }
    llvm::SmallVector<MemoryEffects::EffectInstance> effects;
    eff.getEffectsOnValue(memoryValue, effects);
    for (auto &exprValue : effects)
      if (!isa<MemoryEffects::Read>(exprValue.getEffect())) {
        written = true;
        return WalkResult::interrupt();
      }
    return WalkResult::advance();
  });
  return written;
}

/// `e` as (the expression without its constant term, the constant term):
/// `d0 * 2 + 5` is (d0 * 2, 5), `7` is (null, 7), `d0` is (d0, 0). Simplified
/// affine expressions keep the constant as the right operand of the outermost
/// addition.
static std::pair<AffineExpr, int64_t> splitConstantPart(AffineExpr exprValue) {
  if (auto constantTerm = dyn_cast<AffineConstantExpr>(exprValue))
    return {AffineExpr(), constantTerm.getValue()};
  if (auto add = dyn_cast<AffineBinaryOpExpr>(exprValue))
    if (add.getKind() == AffineExprKind::Add)
      if (auto constantTerm = dyn_cast<AffineConstantExpr>(add.getRHS()))
        return {add.getLHS(), constantTerm.getValue()};
  return {exprValue, 0};
}

/// Two loop-invariant addresses of one memory that provably never
/// meet: same operands, and the maps differ by a nonzero constant in some
/// dimension (`acc[0]` vs `acc[1]`, `buf[i][2]` vs `buf[i][5]`).
static bool certainlyDisjoint(const MemoryAccess &firstValue,
                              const MemoryAccess &secondValue) {
  if (firstValue.inputOperands != secondValue.inputOperands ||
      firstValue.affineMap.getNumResults() !=
          secondValue.affineMap.getNumResults())
    return false;
  // Fast path, without building new expressions: equal non-constant parts
  // and different constant terms in some dimension. A fully unrolled body
  // compares thousands of such addresses (`acc[3]`, `acc[i][5]`).
  for (auto [ex, ey] : llvm::zip(firstValue.affineMap.getResults(),
                                 secondValue.affineMap.getResults())) {
    auto [vx, cx] = splitConstantPart(ex);
    auto [vy, cy] = splitConstantPart(ey);
    if (vx == vy && cx != cy)
      return true;
  }
  for (auto [ex, ey] : llvm::zip(firstValue.affineMap.getResults(),
                                 secondValue.affineMap.getResults())) {
    AffineExpr depthValue =
        simplifyAffineExpr(ex - ey, firstValue.affineMap.getNumDims(),
                           firstValue.affineMap.getNumSymbols());
    if (auto constantTerm = dyn_cast<AffineConstantExpr>(depthValue))
      if (constantTerm.getValue() != 0)
        return true;
  }
  return false;
}

/// Whether `v` names (part of) `mem` through casts, views and pointer
/// conversions of it (a `memref.cast` passed to a callee that reads the
/// element: cgeist's `hls::stream::write(const T &)` argument), without being
/// `mem` itself.
static bool aliasesValue(Value operandValue, Value memoryValue) {
  for (unsigned recursionDepth = 0;
       recursionDepth < 8 && operandValue != memoryValue; ++recursionDepth) {
    if (!isa<BaseMemRefType, LLVM::LLVMPointerType>(operandValue.getType()))
      return false;
    Operation *def = operandValue.getDefiningOp();
    if (!def || def->getNumOperands() == 0 || accessDescription(def) ||
        isa<CallOpInterface>(def))
      return false;
    operandValue = def->getOperand(0);
    if (operandValue == memoryValue)
      return true;
  }
  return false;
}

/// Whether `op` sits in `loop`'s body inside if-arms only (affine.if
/// / scf.if, any depth), with tool.hls.pipeline_decision.
/// promote_conditional_accesses: the promotion carries the element through
/// those ifs as results (rewriteCarriedAccesses).
/// Set while sinkWriteOnlyInvariantStores promotes the element accesses of
/// a loop before the decision (N166 (a)): only that promotion
/// rewrites conditional accesses. The later promotions of pipelined loops keep
/// their conditional accesses in memory (their arrays are classified by N92's
/// iteration-private rule, which a promotion across the loop would
/// defeat: training stream_hls MultiHeadSelfAttention1 opt5, Vitis 2688).
static thread_local bool promotingBeforeDecision = false;

static bool appearsOnlyInBranches(Operation *currentOperation,
                                  AffineForOp chosenLoopForPipeline) {
  if (!promotingBeforeDecision ||
      !circt::hlsest::Config::get()
           .tool.hls.pipelineDecision.promoteConditionalAccesses)
    return false;
  for (Operation *parentNode = currentOperation->getParentOp(); parentNode;
       parentNode = parentNode->getParentOp()) {
    if (parentNode == chosenLoopForPipeline.getOperation())
      return true;
    if (!isa<AffineIfOp, scf::IfOp>(parentNode))
      return false;
  }
  return false;
}

/// Vitis (LLVM LICM scalar promotion) keeps a location of `mem` in a
/// register across `loop` when every use of `mem` inside the
/// loop is a load or store at an address that does not change with
/// the loop, and the distinct addresses are provably disjoint (LLVM
/// promotes each must-alias set on its own: `acc[0] += ..; acc[1] += ..` become
/// two registers). At least one access must be a store (a read-only location is
/// hoisted, not promoted). `groups`, if given, receives the accesses per
/// address in program order, or stays empty when some access is nested in a
/// region of the body (an `affine.if`), which the physical rewrite does not
/// handle.
static bool isPromotableIn(
    Value memoryValue, AffineForOp chosenLoopForPipeline,
    llvm::SmallVector<llvm::SmallVector<MemoryAccess, 4>, 2> *groups = nullptr,
    Operation *nestStructure = nullptr) {
  bool ok = true, anyStore = false, allDirect = true;
  llvm::SmallVector<llvm::SmallVector<MemoryAccess, 4>, 2> matchedGroups;
  // A fully unrolled body has thousands of addresses that differ only in
  // constant terms (`acc[i][0]`, `acc[i][1]`, ...). While every address seen
  // so far has the same operands and the same non-constant part in every
  // dimension (`shared`), an address with that part is either one already
  // seen (looked up by its map) or, having other constant terms, disjoint
  // from all of them (provablyDisjoint's fast path); only the first address
  // that breaks the pattern falls back to the pairwise comparison.
  std::optional<llvm::SmallVector<AffineExpr, 4>> shared;
  bool uniform = true;
  llvm::DenseMap<AffineMap, unsigned> groupOfMap;
  std::set<llvm::SmallVector<int64_t, 4>> seenConstants;
  auto nonConstantParts = [](const MemoryAccess &firstValue) {
    llvm::SmallVector<AffineExpr, 4> parts;
    for (AffineExpr exprValue : firstValue.affineMap.getResults())
      parts.emplace_back(splitConstantPart(exprValue).first);
    return parts;
  };
  chosenLoopForPipeline.getBody()->walk([&](Operation *currentOperation) {
    // An alias used in the loop (a cast passed to a call that reads
    // the element) is an access the rewrite cannot see: LLVM's promotion needs
    // every access of the must-alias set to be a load or store in the
    // loop.
    if (llvm::any_of(currentOperation->getOperands(), [&](Value operandValue) {
          return operandValue != memoryValue &&
                 aliasesValue(operandValue, memoryValue);
        })) {
      ok = false;
      return WalkResult::interrupt();
    }
    if (!llvm::is_contained(currentOperation->getOperands(), memoryValue))
      return WalkResult::advance();
    std::optional<MemoryAccess> firstSide = accessDescription(currentOperation);
    if (!firstSide || firstSide->memoryValue != memoryValue ||
        !isInvariantWithin(*firstSide, chosenLoopForPipeline, nestStructure)) {
      ok = false; // stored as a value, passed to a call, variant address
      return WalkResult::interrupt();
    }
    anyStore |= firstSide->isWrite;
    if (currentOperation->getBlock() != chosenLoopForPipeline.getBody() &&
        !appearsOnlyInBranches(currentOperation, chosenLoopForPipeline))
      allDirect = false;
    if (uniform) {
      llvm::SmallVector<AffineExpr, 4> parts = nonConstantParts(*firstSide);
      if (!shared)
        shared = parts;
      if (*shared == parts && (matchedGroups.empty() ||
                               matchedGroups.front().front().inputOperands ==
                                   firstSide->inputOperands)) {
        auto inductionValue = groupOfMap.find(firstSide->affineMap);
        if (inductionValue != groupOfMap.end()) {
          matchedGroups[inductionValue->second].emplace_back(*firstSide);
          return WalkResult::advance();
        }
        // A new address must differ in its constant terms, which makes it
        // disjoint from every address seen.
        llvm::SmallVector<int64_t, 4> constants;
        for (AffineExpr exprValue : firstSide->affineMap.getResults())
          constants.emplace_back(splitConstantPart(exprValue).second);
        if (seenConstants.insert(constants).second) {
          groupOfMap[firstSide->affineMap] = matchedGroups.size();
          matchedGroups.push_back({*firstSide});
          return WalkResult::advance();
        }
      }
      uniform = false;
    }
    auto *groupValue = llvm::find_if(matchedGroups, [&](auto &grp) {
      return sameAddressAs(grp.front(), *firstSide);
    });
    if (groupValue != matchedGroups.end()) {
      groupValue->push_back(*firstSide);
    } else {
      for (auto &grp : matchedGroups)
        if (!certainlyDisjoint(grp.front(), *firstSide)) {
          ok = false; // may alias another promoted location
          return WalkResult::interrupt();
        }
      matchedGroups.push_back({*firstSide});
    }
    return WalkResult::advance();
  });
  if (!ok || !anyStore)
    return false;
  if (groups) {
    if (allDirect)
      *groups = std::move(matchedGroups);
    else
      groups->clear();
  }
  return true;
}

static bool elementIsFloating(Value memoryValue) {
  return isa<FloatType>(
      cast<MemRefType>(memoryValue.getType()).getElementType());
}

/// Where Vitis' LICM / promotion leave a memory currentOperation AT DECISION
/// TIME: the innermost loop out of which it cannot move. Opaque
/// memory ops (calls, hls.store_enable, ...) stay where they are. With
/// `floatLoadsPerfect`, so does a read-only load of a floating-point element
/// (observed, see the file header; the physical hoist that Vitis' later LICM
/// applies to it is done by hoistInvariantOps when a loop is
/// actually unrolled).
class HoistModel {
public:
  explicit HoistModel(bool floatLoadsPerfect)
      : floatLoadsPerfect(floatLoadsPerfect) {}

  /// The loop whose body `op` effectively sits in (nullptr: outside
  /// every loop of the function).
  AffineForOp effectiveLoop(Operation *currentOperation) {
    AffineForOp activeNest = currentOperation->getParentOfType<AffineForOp>();
    std::optional<MemoryAccess> firstSide = accessDescription(currentOperation);
    if (!firstSide)
      return activeNest;
    while (activeNest && movableOutOf(*firstSide, activeNest))
      activeNest = activeNest->getParentOfType<AffineForOp>();
    return activeNest;
  }

  bool movableOutOf(const MemoryAccess &firstSide,
                    AffineForOp chosenLoopForPipeline) {
    if (!isInvariantWithin(firstSide, chosenLoopForPipeline))
      return false;
    if (!firstSide.isWrite &&
        !written(firstSide.memoryValue, chosenLoopForPipeline))
      // LICM hoist (confirmed for integer elements; a float load stays put
      // for the decision under float-loads-perfect).
      return !(floatLoadsPerfect && elementIsFloating(firstSide.memoryValue));
    return promotable(firstSide.memoryValue, chosenLoopForPipeline);
  }

  const bool floatLoadsPerfect;

private:
  using Key = std::pair<Value, Operation *>;
  bool written(Value memoryValue, AffineForOp chosenLoopForPipeline) {
    Key mapKey{memoryValue, chosenLoopForPipeline.getOperation()};
    auto inductionValue = writtenCache.find(mapKey);
    if (inductionValue != writtenCache.end())
      return inductionValue->second;
    bool widthValue = isWrittenDuringLoop(memoryValue, chosenLoopForPipeline);
    writtenCache[mapKey] = widthValue;
    return widthValue;
  }
  bool promotable(Value memoryValue, AffineForOp chosenLoopForPipeline) {
    Key mapKey{memoryValue, chosenLoopForPipeline.getOperation()};
    auto inductionValue = promotableCache.find(mapKey);
    if (inductionValue != promotableCache.end())
      return inductionValue->second;
    bool pointerValue = isPromotableIn(memoryValue, chosenLoopForPipeline);
    promotableCache[mapKey] = pointerValue;
    return pointerValue;
  }
  llvm::DenseMap<Key, bool> writtenCache, promotableCache;
};

//===----------------------------------------------------------------------===//
// Loop forest
//===----------------------------------------------------------------------===//

struct LoopNode {
  /// Perfect chain, outermost first. The decision treats it as one
  /// loop.
  llvm::SmallVector<AffineForOp, 3> nestedLoops;
  llvm::SmallVector<std::unique_ptr<LoopNode>, 4> childList;
  /// Reached through a call from the parent node: no flattening across it,
  /// decided when its own function is processed.
  bool throughCall = false;
  /// Some chain member has no constant trip count, carries `hls.unroll_off`,
  /// or the node stands for a loop that is not an affine.for at all.
  bool dynamic = false;
  /// The node is one runtime loop (isRuntimeLoop: scf.for /
  /// scf.while; the chain is empty): a pipeline candidate of its own, never
  /// collapsed or flattened with another loop, dynamic for every
  /// loop around it.
  Operation *runtimeLoop = nullptr;
  /// The runtime loop is an scf.for whose body is a perfect nest
  /// over its only child, an affine chain of constant trip counts
  /// (isPerfectRuntimePair): flattened into that chain's pipeline.
  bool perfectRuntime = false;
  /// Some chain member keeps a partial user unroll (`hls.unroll_partial`):
  /// never unrolled by an enclosing pipeline, pipelined on its own.
  bool userFixed = false;
  uint64_t tripCountValue =
      1;                    // product of the chain's trip counts (if !dynamic)
  int userPipelineIdx = -1; // outermost user-pipelined chain member
  bool pipelineOff = false; // chain.back() carries hls.pipeline_off
  /// The node is one `hls.uncounted` loop that would have collapsed
  /// with its only child (a perfect pair, constant inner trip count) had it
  /// been counted (step 1); it may still be flattened into that child (step 3).
  bool uncountedPerfect = false;
  // Derived over the subtree.
  bool constInside = true;
  uint64_t maxPath = 1; // trip * max over children of maxPath
  bool hasUserPipeline = false;
  bool hasUserFixed = false;
  /// The pipelined loop that absorbs this node: the node's own
  /// innermost loop when it is pipelined, or the child's when it is
  /// flattened into it.
  AffineForOp taggedLoop;
  /// The loops around `tagged` Vitis does not flatten into it (N96,
  /// doWhileParents): an automatic pipeline's unroll makes their next index
  /// a subscript.
  llvm::SmallPtrSet<Operation *, 4> doWhileParents;
  /// Some loop of the node was not flattened into `tagged` for that
  /// reason: no loop around the node is flattened into it either.
  bool flattenRefused = false;
};

/// A read-only load of a floating-point element directly in `outer`'s body
/// from a memory `inner` never writes. cgeist's own LICM moves inner-invariant
/// loads there (`lb[i]` of `lo[i][j] = la[i][j] * lb[i]` ends up before the j
/// loop in the MLIR), and a source may hold it there too (`float t =
/// lb[i];` before the j loop, pf_srchoist_m8_n64), but Vitis
/// converts such a nest into a perfect one and flattens it (see the file
/// header), so under float-loads-perfect the load is judged as if it were in
/// the inner loop.
static bool canSinkFloatLoad(Operation *currentOperation, Block *outerBody,
                             AffineForOp innerLoop) {
  if (currentOperation->getBlock() != outerBody)
    return false;
  std::optional<MemoryAccess> firstSide = accessDescription(currentOperation);
  if (!firstSide || firstSide->isWrite ||
      !elementIsFloating(firstSide->memoryValue))
    return false;
  return !isWrittenDuringLoop(firstSide->memoryValue, innerLoop);
}

/// A loop whose trip count is unknown but the same in every
/// iteration of `outer` (an enclosing loop): a constant lower bound
/// and an upper bound computed only from values defined outside `outer`. Vitis
/// flattens a perfect nest of such loops into the innermost pipeline like
/// constant-trip loops (W9r16 review kernel w9r16rv_gp_flat: three loops
/// to a top argument `iter`, `VITIS_LOOP_10_3_VITIS_LOOP_11_4_
/// VITIS_LOOP_12_5`, II 1; GP_selection loop 1180_20, whose bound is
/// the counter of a loop around the nest). Key
/// tool.hls.pipeline_decision.flatten_nest_invariant_bounds.
static bool boundIsInvariantWithin(AffineForOp chosenLoopForPipeline,
                                   Operation *enclosingLoop) {
  if (!circt::hlsest::Config::get()
           .tool.hls.pipelineDecision.flattenNestInvariantBounds)
    return false;
  if (chosenLoopForPipeline->hasAttr(kLoopUncountedAttr) ||
      chosenLoopForPipeline->hasAttr(kLoopUnrollOffAttr) ||
      !chosenLoopForPipeline.hasConstantLowerBound() ||
      chosenLoopForPipeline.getUpperBoundMap().getNumResults() != 1)
    return false;
  return llvm::all_of(chosenLoopForPipeline.getUpperBoundOperands(),
                      [&](Value operandValue) {
                        return !enclosingLoop->isAncestor(
                            operandValue.getParentBlock()->getParentOp());
                      });
}

/// Every member of `chain` (but the first when `skipFirst`) has a constant
/// trip count or one invariant in `outer` (boundInvariantIn).
static bool nestIsInvariantWithin(llvm::ArrayRef<AffineForOp> nestedLoops,
                                  Operation *enclosingLoop, bool skipFirst) {
  for (AffineForOp chosenLoopForPipeline :
       nestedLoops.drop_front(skipFirst ? 1 : 0))
    if ((!getConstantTripCount(chosenLoopForPipeline) ||
         chosenLoopForPipeline->hasAttr(kLoopUnrollOffAttr)) &&
        !boundIsInvariantWithin(chosenLoopForPipeline, enclosingLoop))
      return false;
  return true;
}

/// Does `outer` form a perfect nest with `inner` (the only loop
/// directly in its body), as Vitis judges it after LICM / promotion?
static bool formsPerfectNest(AffineForOp enclosingLoop, AffineForOp innerLoop,
                             HoistModel &licm) {
  if (innerLoop->getBlock() != enclosingLoop.getBody())
    return false;
  bool perfectNestFlag = true;
  enclosingLoop.getBody()->walk<WalkOrder::PreOrder>(
      [&](Operation *currentOperation) {
        if (currentOperation == innerLoop.getOperation())
          return WalkResult::skip();
        if (isa<LoopLikeOpInterface>(currentOperation) ||
            isa<CallOpInterface>(currentOperation)) {
          perfectNestFlag = false;
          return WalkResult::interrupt();
        }
        if (currentOperation->getNumRegions() > 0)
          return WalkResult::advance(); // look inside ifs
        if (isMemoryEffectFree(currentOperation))
          return WalkResult::advance();
        if (licm.effectiveLoop(currentOperation) != enclosingLoop)
          return WalkResult::advance(); // hoisted further out
        if (licm.floatLoadsPerfect &&
            canSinkFloatLoad(currentOperation, enclosingLoop.getBody(),
                             innerLoop))
          return WalkResult::advance(); // sunk back by Vitis' nest conversion
        perfectNestFlag = false;
        return WalkResult::interrupt();
      });
  if (!perfectNestFlag)
    return false;
  // Memory ops of the inner nest that LICM / promotion move into outer's
  // body.
  innerLoop.getBody()->walk([&](Operation *currentOperation) {
    if (!accessDescription(currentOperation))
      return WalkResult::advance();
    if (licm.effectiveLoop(currentOperation) == enclosingLoop) {
      perfectNestFlag = false;
      return WalkResult::interrupt();
    }
    return WalkResult::advance();
  });
  return perfectNestFlag;
}

/// Does the runtime-trip scf.for `outer` (isRuntimeLoop) form a perfect nest
/// with `inner`, the only loop directly in its body? Judged as
/// isPerfectPair judges an affine pair, with what LICM cannot see through an
/// scf.for treated conservatively: a memory currentOperation in outer's body
/// (other than a sinkable float load) makes the nest imperfect, and so does an
/// access of the inner nest that LICM / promotion move out of `inner` unless it
/// is a read of a memory outer never writes at an address that does not change
/// with outer (hoisted past outer as well). Vitis flattens such a nest into
/// `inner`'s pipeline (VITIS_NOTES.md N53 (b): o72r_pf / pf2 / pf3 / pf4 /
/// acc / s65, o72f_pf7: flatten `VITIS_LOOP_<outer>`, trip `?`); a distance-1
/// recurrence of the inner loop (`buf[i][k] = buf[i][k-1] ..`,
/// o72r_raw / o72f_rawm) is not flattened, as for an affine nest (o72f_rawc;
/// O8, not modelled for either).
static bool formsPerfectRuntimeNest(scf::ForOp enclosingLoop,
                                    AffineForOp innerLoop, HoistModel &licm) {
  if (innerLoop->getBlock() != enclosingLoop.getBody())
    return false;
  bool perfectNestFlag = true;
  enclosingLoop.getBody()->walk<WalkOrder::PreOrder>(
      [&](Operation *currentOperation) {
        if (currentOperation == innerLoop.getOperation())
          return WalkResult::skip();
        if (isa<LoopLikeOpInterface>(currentOperation) ||
            isa<CallOpInterface>(currentOperation)) {
          perfectNestFlag = false;
          return WalkResult::interrupt();
        }
        if (currentOperation->getNumRegions() > 0 ||
            isMemoryEffectFree(currentOperation))
          return WalkResult::advance();
        if (licm.floatLoadsPerfect &&
            canSinkFloatLoad(currentOperation, enclosingLoop.getBody(),
                             innerLoop))
          return WalkResult::advance();
        perfectNestFlag = false;
        return WalkResult::interrupt();
      });
  if (!perfectNestFlag)
    return false;
  auto definedOutside = [&](Value operandValue) {
    return !enclosingLoop->isAncestor(
        operandValue.getParentRegion()->getParentOp());
  };
  innerLoop->walk([&](Operation *currentOperation) {
    std::optional<MemoryAccess> firstSide = accessDescription(currentOperation);
    if (!firstSide)
      return WalkResult::advance();
    AffineForOp eff = licm.effectiveLoop(currentOperation);
    if (eff && innerLoop->isAncestor(eff))
      return WalkResult::advance(); // stays inside the inner nest
    bool pastOuter =
        !firstSide->isWrite && definedOutside(firstSide->memoryValue) &&
        llvm::all_of(firstSide->inputOperands, definedOutside) &&
        !isWrittenDuringLoop(firstSide->memoryValue, enclosingLoop);
    if (pastOuter)
      return WalkResult::advance();
    perfectNestFlag = false;
    return WalkResult::interrupt();
  });
  return perfectNestFlag;
}

static uint64_t clampedMultiply(uint64_t firstSide, uint64_t passBuilder) {
  uint64_t secondAccess;
  if (__builtin_mul_overflow(firstSide, passBuilder, &secondAccess))
    return std::numeric_limits<uint64_t>::max();
  return secondAccess;
}

class LoopForest {
public:
  LoopForest(HoistModel &licm) : licm(licm) {}

  /// Loops directly inside `region` (not nested in another loop),
  /// following calls into their callees: the affine.for loops in `loops`, the
  /// runtime loops (isRuntimeLoop) in `runtimeLoops`. `opaqueLoop` is set when
  /// any other loop is met.
  void gatherChildLoops(
      Region &blockRegion, bool throughCall,
      llvm::SmallVector<std::pair<AffineForOp, bool>, 4> &loopList,
      llvm::SmallVector<std::pair<Operation *, bool>, 2> &runtimeLoops,
      bool &opaqueLoop, SmallPtrSetImpl<Operation *> &callStackSet) {
    blockRegion.walk<WalkOrder::PreOrder>([&](Operation *currentOperation) {
      if (auto affineLoop = dyn_cast<AffineForOp>(currentOperation)) {
        loopList.emplace_back(affineLoop, throughCall);
        return WalkResult::skip();
      }
      if (isDynamicLoop(currentOperation)) {
        runtimeLoops.emplace_back(currentOperation, throughCall);
        return WalkResult::skip();
      }
      if (isa<LoopLikeOpInterface>(currentOperation)) {
        opaqueLoop = true;
        return WalkResult::skip();
      }
      // A library core with loops of its own (sin_or_cos_double; VITIS_NOTES
      // N169): a dynamic loop inside the caller's loop.
      if (hasLoopingLibraryCall(currentOperation, symbolTables)) {
        opaqueLoop = true;
        return WalkResult::advance();
      }
      if (auto callSite = dyn_cast<CallOpInterface>(currentOperation)) {
        auto calleeFunction = dyn_cast_or_null<func::FuncOp>(
            callSite.resolveCallableInTable(&symbolTables));
        if (!calleeFunction || calleeFunction.isExternal() ||
            !callStackSet.insert(calleeFunction.getOperation()).second)
          return WalkResult::advance();
        gatherChildLoops(calleeFunction.getBody(), /*viaCall=*/true, loopList,
                         runtimeLoops, opaqueLoop, callStackSet);
        callStackSet.erase(calleeFunction.getOperation());
      }
      return WalkResult::advance();
    });
  }

  std::unique_ptr<LoopNode> build(AffineForOp root, bool throughCall,
                                  SmallPtrSetImpl<Operation *> &callStackSet) {
    auto nodeState = std::make_unique<LoopNode>();
    nodeState->throughCall = throughCall;
    nodeState->nestedLoops.emplace_back(root);
    AffineForOp activeNest = root;
    llvm::SmallVector<std::pair<AffineForOp, bool>, 4> childLoopList;
    llvm::SmallVector<std::pair<Operation *, bool>, 2> runtimeChildNodes;
    bool opaqueLoop = false;
    while (true) {
      childLoopList.clear();
      runtimeChildNodes.clear();
      opaqueLoop = false;
      gatherChildLoops(activeNest.getRegion(), /*viaCall=*/false, childLoopList,
                       runtimeChildNodes, opaqueLoop, callStackSet);
      if (childLoopList.size() != 1 || opaqueLoop ||
          !runtimeChildNodes.empty() || childLoopList[0].second)
        break;
      AffineForOp child = childLoopList[0].first;
      // A dynamic inner loop is not flattened (Vitis' semi-perfect
      // rule allows a variable bound on the outermost loop only),
      // unless its bound does not change over the nest (nestInvariantBound).
      if (child->hasAttr(kLoopUnrollOffAttr) ||
          (!getConstantTripCount(child) &&
           !boundIsInvariantWithin(child, root)))
        break;
      if (!formsPerfectNest(activeNest, child, licm))
        break;
      // An uncounted loop (only ever the first chain member: its
      // trip count is not constant) does not collapse with its child (step 1,
      // N15).
      if (activeNest->hasAttr(kLoopUncountedAttr)) {
        nodeState->uncountedPerfect = true;
        break;
      }
      nodeState->nestedLoops.emplace_back(child);
      activeNest = child;
    }
    for (AffineForOp chosenLoopForPipeline : nodeState->nestedLoops) {
      std::optional<uint64_t> tripCountValue =
          getConstantTripCount(chosenLoopForPipeline);
      if (!tripCountValue || chosenLoopForPipeline->hasAttr(kLoopUnrollOffAttr))
        nodeState->dynamic = true;
      else
        nodeState->tripCountValue =
            clampedMultiply(nodeState->tripCountValue, *tripCountValue);
    }
    for (auto [idx, chosenLoopForPipeline] :
         llvm::enumerate(nodeState->nestedLoops)) {
      if (nodeState->userPipelineIdx < 0 &&
          hasUserPipelineTag(chosenLoopForPipeline))
        nodeState->userPipelineIdx = static_cast<int>(idx);
      if (chosenLoopForPipeline->hasAttr(kLoopUnrollPartialAttr))
        nodeState->userFixed = true;
    }
    nodeState->pipelineOff =
        nodeState->nestedLoops.back()->hasAttr(kLoopPipelineOffAttr);
    constructChildNodes(*nodeState, childLoopList, runtimeChildNodes,
                        callStackSet);
    if (opaqueLoop) {
      // A loop that is not an affine.for: a dynamic child.
      auto opaque = std::make_unique<LoopNode>();
      opaque->dynamic = true;
      opaque->constInside = false;
      nodeState->childList.emplace_back(std::move(opaque));
    }
    nodeState->hasUserPipeline = nodeState->userPipelineIdx >= 0;
    summarize(*nodeState);
    return nodeState;
  }

  /// A runtime loop (isRuntimeLoop) and the loops inside it: it is
  /// decided like a one-loop chain whose trip count is unknown
  /// (N53), so it is dynamic for every loop around it, and the loops
  /// of all its regions (an scf.while's condition region included) are its
  /// children.
  std::unique_ptr<LoopNode>
  buildRuntime(Operation *chosenLoopForPipeline, bool throughCall,
               SmallPtrSetImpl<Operation *> &callStackSet) {
    auto nodeState = std::make_unique<LoopNode>();
    nodeState->throughCall = throughCall;
    nodeState->runtimeLoop = chosenLoopForPipeline;
    nodeState->dynamic = true;
    nodeState->pipelineOff =
        chosenLoopForPipeline->hasAttr(kLoopPipelineOffAttr);
    nodeState->hasUserPipeline = hasUserPipelineTag(chosenLoopForPipeline);
    llvm::SmallVector<std::pair<AffineForOp, bool>, 4> childLoopList;
    llvm::SmallVector<std::pair<Operation *, bool>, 2> runtimeChildNodes;
    bool opaqueLoop = false;
    for (Region &blockRegion : chosenLoopForPipeline->getRegions())
      gatherChildLoops(blockRegion, /*viaCall=*/false, childLoopList,
                       runtimeChildNodes, opaqueLoop, callStackSet);
    if (auto affineLoop = dyn_cast<scf::ForOp>(chosenLoopForPipeline))
      nodeState->perfectRuntime =
          !nodeState->pipelineOff && !opaqueLoop && runtimeChildNodes.empty() &&
          childLoopList.size() == 1 && !childLoopList[0].second &&
          getConstantTripCount(childLoopList[0].first) &&
          !childLoopList[0].first->hasAttr(kLoopUnrollOffAttr) &&
          formsPerfectRuntimeNest(affineLoop, childLoopList[0].first, licm);
    constructChildNodes(*nodeState, childLoopList, runtimeChildNodes,
                        callStackSet);
    if (opaqueLoop) {
      auto opaque = std::make_unique<LoopNode>();
      opaque->dynamic = true;
      opaque->constInside = false;
      nodeState->childList.emplace_back(std::move(opaque));
    }
    summarize(*nodeState);
    return nodeState;
  }

  /// The subtrees of the loops gatherChildLoops found, affine loops first.
  void constructChildNodes(
      LoopNode &nodeState,
      llvm::ArrayRef<std::pair<AffineForOp, bool>> childLoopList,
      llvm::ArrayRef<std::pair<Operation *, bool>> runtimeChildNodes,
      SmallPtrSetImpl<Operation *> &callStackSet) {
    // A child reached through a call: keep its function on the call stack
    // while its subtree is built, so that a call back into that function
    // (direct or mutual recursion) is cut there too, not only during
    // gatherChildLoops. Children of this function are already covered by
    // the entry runOnOperation pushed.
    auto withOwner = [&](Operation *chosenLoopForPipeline, auto buildFn) {
      Operation *owner = nullptr;
      if (auto fn = chosenLoopForPipeline->getParentOfType<func::FuncOp>())
        owner = fn.getOperation();
      bool pushed = owner && callStackSet.insert(owner).second;
      nodeState.childList.emplace_back(buildFn());
      if (pushed)
        callStackSet.erase(owner);
    };
    for (auto [chosenLoopForPipeline, childViaCall] : childLoopList)
      withOwner(chosenLoopForPipeline, [&] {
        return build(chosenLoopForPipeline, childViaCall, callStackSet);
      });
    for (auto [chosenLoopForPipeline, childViaCall] : runtimeChildNodes)
      withOwner(chosenLoopForPipeline, [&] {
        return buildRuntime(chosenLoopForPipeline, childViaCall, callStackSet);
      });
  }

  /// The properties derived over the subtree (hasUserPipeline holds the
  /// node's own on entry).
  static void summarize(LoopNode &nodeState) {
    nodeState.constInside = !nodeState.dynamic;
    nodeState.hasUserFixed = nodeState.userFixed;
    uint64_t maxChild = 1;
    for (auto &constantTerm : nodeState.childList) {
      nodeState.constInside &= constantTerm->constInside;
      nodeState.hasUserPipeline |= constantTerm->hasUserPipeline;
      nodeState.hasUserFixed |= constantTerm->hasUserFixed;
      maxChild = std::max(maxChild, constantTerm->maxPath);
    }
    nodeState.maxPath = clampedMultiply(nodeState.tripCountValue, maxChild);
  }

  HoistModel &licm;
  SymbolTableCollection symbolTables;
};

//===----------------------------------------------------------------------===//
// Physical transforms: hoist, promote, unroll
//===----------------------------------------------------------------------===//

/// Vitis LICM on a loop about to be unrolled: ops directly in
/// `loop`'s body whose operands are all defined outside it (or by
/// ops hoisted before them) move before the loop - pure speculatable
/// ops, and loads from a memory the loop never writes. After the
/// unroll, the pipelined parent then holds one such load instead of trip-count
/// copies of it.
static unsigned hoistLoopInvariantOps(AffineForOp chosenLoopForPipeline) {
  DenseSet<Value> invariant;
  auto isInvariantValue = [&](Value operandValue) {
    return chosenLoopForPipeline.isDefinedOutsideOfLoop(operandValue) ||
           invariant.contains(operandValue);
  };
  llvm::DenseMap<Value, bool> writtenCache;
  auto writtenInLoop = [&](Value memoryValue) {
    auto inductionValue = writtenCache.find(memoryValue);
    if (inductionValue != writtenCache.end())
      return inductionValue->second;
    bool widthValue = isWrittenDuringLoop(memoryValue, chosenLoopForPipeline);
    writtenCache[memoryValue] = widthValue;
    return widthValue;
  };
  llvm::SmallVector<Operation *> toHoist;
  for (Operation &currentOperation :
       chosenLoopForPipeline.getBody()->without_terminator()) {
    if (currentOperation.getNumRegions() != 0)
      continue;
    bool hoistable = false;
    if (auto memoryLoad = dyn_cast<AffineLoadOp>(currentOperation)) {
      hoistable = llvm::all_of(memoryLoad.getMapOperands(), isInvariantValue) &&
                  isInvariantValue(memoryLoad.getMemRef()) &&
                  !writtenInLoop(memoryLoad.getMemRef());
    } else if (auto memoryLoad = dyn_cast<memref::LoadOp>(currentOperation)) {
      hoistable = llvm::all_of(memoryLoad.getIndices(), isInvariantValue) &&
                  isInvariantValue(memoryLoad.getMemRef()) &&
                  !writtenInLoop(memoryLoad.getMemRef());
    } else if (isMemoryEffectFree(&currentOperation) &&
               isSpeculatable(&currentOperation) &&
               currentOperation.getNumResults() > 0) {
      hoistable =
          llvm::all_of(currentOperation.getOperands(), isInvariantValue);
    }
    if (!hoistable)
      continue;
    toHoist.emplace_back(&currentOperation);
    for (Value secondAccess : currentOperation.getResults())
      invariant.insert(secondAccess);
  }
  for (Operation *currentOperation : toHoist)
    currentOperation->moveBefore(chosenLoopForPipeline);
  return toHoist.size();
}

/// VITIS_NOTES N166 (a): after LICM's store `st` of the promoted value
/// after `loop`, LLVM forwards it to the loads of that element that
/// follow in the block before any other access of the memory, deletes it when a
/// store of the element follows before any read, and deletes the store of
/// the element just before the loop that nothing reads in between
/// (the loop no longer touches the memory). `s[i][j] = 0; for (d)
/// s[i][j] += x; s[i][j] /= D;` keeps the one store of the quotient (kernels
/// w9r22p_c1 / c4: Vitis 7 / 12 bits). The memories cleanupAroundPromotedStore
/// forwarded loads of; afterwards a local array left with stores only is dead
/// (removeWriteOnlyArrays).
static thread_local llvm::SmallVector<Value> *forwardedMemories = nullptr;

static void cleanPromotedStore(AffineStoreOp storeOp,
                               AffineForOp chosenLoopForPipeline) {
  Value memoryValue = storeOp.getMemRef();
  if (forwardedMemories && !llvm::is_contained(*forwardedMemories, memoryValue))
    forwardedMemories->push_back(memoryValue);
  auto sameElement = [&](Operation *currentOperation) {
    if (auto firstAccess = dyn_cast<AffineLoadOp>(currentOperation))
      return firstAccess.getMemRef() == memoryValue &&
             firstAccess.getAffineMap() == storeOp.getAffineMap() &&
             llvm::equal(firstAccess.getMapOperands(),
                         storeOp.getMapOperands());
    if (auto stringValue = dyn_cast<AffineStoreOp>(currentOperation))
      return stringValue.getMemRef() == memoryValue &&
             stringValue.getAffineMap() == storeOp.getAffineMap() &&
             llvm::equal(stringValue.getMapOperands(),
                         storeOp.getMapOperands());
    return false;
  };
  // Whether `op` (or an op inside it) may access the memory otherwise.
  auto touches = [&](Operation *currentOperation) {
    bool matchedGroups = false;
    currentOperation->walk([&](Operation *innerLoop) {
      if (isa<CallOpInterface>(innerLoop) ||
          llvm::is_contained(innerLoop->getOperands(), memoryValue)) {
        matchedGroups = true;
        return WalkResult::interrupt();
      }
      return WalkResult::advance();
    });
    return matchedGroups;
  };
  Value stored = storeOp.getValueToStore();
  bool overwritten = false;
  for (Operation *nextNode = storeOp->getNextNode(); nextNode;) {
    Operation *following = nextNode->getNextNode();
    if (sameElement(nextNode) && isa<AffineLoadOp>(nextNode)) {
      nextNode->getResult(0).replaceAllUsesWith(stored);
      nextNode->erase();
      nextNode = following;
      continue;
    }
    if (sameElement(nextNode) && isa<AffineStoreOp>(nextNode)) {
      overwritten = true;
      break;
    }
    if (touches(nextNode))
      break;
    nextNode = following;
  }
  // The store just before the loop: the loads of the element between
  // it and the loop (the promotion's initial load) read its value,
  // and it is dead once they do (the loop no longer accesses the
  // element).
  llvm::SmallVector<Operation *> loadsBefore;
  for (Operation *priorOperation = chosenLoopForPipeline->getPrevNode();
       priorOperation; priorOperation = priorOperation->getPrevNode()) {
    if (sameElement(priorOperation) && isa<AffineLoadOp>(priorOperation)) {
      loadsBefore.emplace_back(priorOperation);
      continue;
    }
    if (sameElement(priorOperation) && isa<AffineStoreOp>(priorOperation)) {
      if (touches(chosenLoopForPipeline))
        break;
      Value earlier = cast<AffineStoreOp>(priorOperation).getValueToStore();
      for (Operation *memoryLoad : loadsBefore) {
        memoryLoad->getResult(0).replaceAllUsesWith(earlier);
        memoryLoad->erase();
      }
      priorOperation->erase();
      break;
    }
    if (touches(priorOperation))
      break;
  }
  if (overwritten)
    storeOp->erase();
}

/// The stores of `loop` that are its only accesses to one memory,
/// all at one loop-invariant element, directly in its body, the last
/// one storing a value the loop yields (or one defined outside it):
/// LICM sinks them to one store after the loop, which then forwards
/// and dies like a promoted store (cleanupAroundPromotedStore). Loops with a
/// constant trip count of at least one only (the store must run). Returns the
/// number of memories sunk.
static unsigned sinkDeadStores(AffineForOp chosenLoopForPipeline) {
  std::optional<uint64_t> tripCountValue =
      getConstantTripCount(chosenLoopForPipeline);
  if (!tripCountValue || *tripCountValue == 0)
    return 0;
  Block *body = chosenLoopForPipeline.getBody();
  llvm::MapVector<Value, llvm::SmallVector<AffineStoreOp, 2>> storesOf;
  DenseSet<Value> disqualified;
  chosenLoopForPipeline.getBody()->walk([&](Operation *currentOperation) {
    for (Value operandValue : currentOperation->getOperands()) {
      if (!isa<BaseMemRefType>(operandValue.getType()))
        continue;
      auto storeOp = dyn_cast<AffineStoreOp>(currentOperation);
      if (!storeOp || storeOp.getMemRef() != operandValue ||
          currentOperation->getBlock() != body)
        disqualified.insert(operandValue);
      else
        storesOf[operandValue].emplace_back(storeOp);
    }
    if (isa<CallOpInterface>(currentOperation))
      for (auto &[memoryValue, list] : storesOf)
        disqualified.insert(memoryValue);
  });
  unsigned sunk = 0;
  Operation *yield = body->getTerminator();
  for (auto &[memoryValue, stores] : storesOf) {
    if (disqualified.contains(memoryValue) ||
        !chosenLoopForPipeline.isDefinedOutsideOfLoop(memoryValue))
      continue;
    AffineStoreOp last = stores.back();
    bool sameElement = llvm::all_of(stores, [&](AffineStoreOp storeOp) {
      return storeOp.getAffineMap() == last.getAffineMap() &&
             llvm::equal(storeOp.getMapOperands(), last.getMapOperands());
    });
    if (!sameElement ||
        !llvm::all_of(last.getMapOperands(), [&](Value operandValue) {
          return chosenLoopForPipeline.isDefinedOutsideOfLoop(operandValue);
        }))
      continue;
    // The value the last iteration stores, seen after the loop.
    Value after;
    Value stored = last.getValueToStore();
    if (chosenLoopForPipeline.isDefinedOutsideOfLoop(stored)) {
      after = stored;
    } else {
      for (OpOperand &secondValue : yield->getOpOperands())
        if (secondValue.get() == stored) {
          after =
              chosenLoopForPipeline.getResult(secondValue.getOperandNumber());
          break;
        }
    }
    if (!after)
      continue;
    OpBuilder passBuilder(chosenLoopForPipeline.getContext());
    passBuilder.setInsertionPointAfter(chosenLoopForPipeline);
    AffineStoreOp storeOp =
        AffineStoreOp::create(passBuilder, last.getLoc(), after, memoryValue,
                              last.getAffineMap(), last.getMapOperands());
    for (AffineStoreOp old : stores)
      old->erase();
    cleanPromotedStore(storeOp, chosenLoopForPipeline);
    ++sunk;
  }
  return sunk;
}

static AffineForOp
promoteLoopInvariantAccesses(AffineForOp chosenLoopForPipeline,
                             unsigned &promotedAccess, Operation *nestStructure,
                             llvm::ArrayRef<Value> only);

/// The promotion's rewrite of `block`: a load of carried element k reads
/// `cur[k]`, a store sets it, and both are erased. An if-op (affine.if /
/// scf.if) holding carried accesses is rebuilt with one more result per
/// element they touch: each arm yields its value of the element (an arm
/// that does not touch it, or a missing else, yields the value from before
/// the if), and the if's result is the element's value after it (LLVM's
/// SSA update of a promoted conditional store, onlyInIfArms).
static void rewriteCarriedAccesses(
    Block *block, const llvm::DenseMap<Operation *, unsigned> &carriedIndexOf,
    llvm::SmallVector<Value> &activeNest) {
  for (Operation &currentOperation : llvm::make_early_inc_range(*block)) {
    if (currentOperation.hasTrait<OpTrait::IsTerminator>())
      continue;
    auto inductionValue = carriedIndexOf.find(&currentOperation);
    if (inductionValue != carriedIndexOf.end()) {
      if (auto storeOperation = dyn_cast<AffineStoreOp>(currentOperation))
        activeNest[inductionValue->second] = storeOperation.getValueToStore();
      else
        currentOperation.getResult(0).replaceAllUsesWith(
            activeNest[inductionValue->second]);
      currentOperation.erase();
      continue;
    }
    if (!isa<AffineIfOp, scf::IfOp>(currentOperation))
      continue;
    llvm::SmallVector<unsigned> touched;
    currentOperation.walk([&](Operation *innerLoop) {
      auto matchedGroups = carriedIndexOf.find(innerLoop);
      if (matchedGroups != carriedIndexOf.end() &&
          !llvm::is_contained(touched, matchedGroups->second))
        touched.emplace_back(matchedGroups->second);
    });
    if (touched.empty())
      continue;
    llvm::sort(touched);
    bool isAffine = isa<AffineIfOp>(currentOperation);
    llvm::SmallVector<Type> types(currentOperation.getResultTypes());
    for (unsigned keyValue : touched)
      types.emplace_back(activeNest[keyValue].getType());
    OperationState state(currentOperation.getLoc(), currentOperation.getName());
    state.addOperands(currentOperation.getOperands());
    state.addAttributes(currentOperation.getAttrs());
    state.addTypes(types);
    for (unsigned secondAccess = 0;
         secondAccess < currentOperation.getNumRegions(); ++secondAccess)
      (void)state.addRegion();
    OpBuilder passBuilder(&currentOperation);
    Operation *rebuilt = passBuilder.create(state);
    for (unsigned secondAccess = 0;
         secondAccess < currentOperation.getNumRegions(); ++secondAccess) {
      Region &blockRegion = rebuilt->getRegion(secondAccess);
      blockRegion.takeBody(currentOperation.getRegion(secondAccess));
      llvm::SmallVector<Value> armCur = activeNest;
      if (blockRegion.empty()) {
        // A missing else: the element keeps its value.
        Block *armBlock = passBuilder.createBlock(&blockRegion);
        passBuilder.setInsertionPointToEnd(armBlock);
        llvm::SmallVector<Value> vals;
        for (unsigned keyValue : touched)
          vals.emplace_back(activeNest[keyValue]);
        if (isAffine)
          AffineYieldOp::create(passBuilder, currentOperation.getLoc(), vals);
        else
          scf::YieldOp::create(passBuilder, currentOperation.getLoc(), vals);
        continue;
      }
      Block &armBlock = blockRegion.front();
      rewriteCarriedAccesses(&armBlock, carriedIndexOf, armCur);
      Operation *yield = armBlock.getTerminator();
      llvm::SmallVector<Value> vals;
      for (unsigned keyValue : touched)
        vals.emplace_back(armCur[keyValue]);
      yield->insertOperands(yield->getNumOperands(), vals);
    }
    unsigned old = currentOperation.getNumResults();
    for (unsigned indexValue = 0; indexValue < old; ++indexValue)
      currentOperation.getResult(indexValue)
          .replaceAllUsesWith(rebuilt->getResult(indexValue));
    for (auto [indexValue, keyValue] : llvm::enumerate(touched))
      activeNest[keyValue] = rebuilt->getResult(old + indexValue);
    currentOperation.erase();
  }
}

/// The memories `loop` reads and writes at one invariant element
/// that its own block also accesses at that element outside the
/// loop: the loop's parent is imperfect with respect to
/// them, so LLVM's LICM promotes them before any flattening (`s[i][j] = 0; for
/// (d) s[i][j] += x; s[i][j] /= D;`: Vitis 7 bits, kernel w9r22p_c1_accdiv; a
/// perfect nest keeps its accumulator in memory, N129).
static llvm::SmallVector<Value>
elementsNearLoop(AffineForOp chosenLoopForPipeline) {
  llvm::SmallVector<Value> outputList;
  for (Operation &currentOperation : *chosenLoopForPipeline->getBlock()) {
    if (&currentOperation == chosenLoopForPipeline.getOperation())
      continue;
    Value memoryValue;
    if (auto firstAccess = dyn_cast<AffineLoadOp>(currentOperation))
      memoryValue = firstAccess.getMemRef();
    else if (auto storeOp = dyn_cast<AffineStoreOp>(currentOperation))
      memoryValue = storeOp.getMemRef();
    if (!memoryValue || llvm::is_contained(outputList, memoryValue))
      continue;
    bool inLoop = false;
    chosenLoopForPipeline.getBody()->walk([&](Operation *innerLoop) {
      if (llvm::is_contained(innerLoop->getOperands(), memoryValue)) {
        inLoop = true;
        return WalkResult::interrupt();
      }
      return WalkResult::advance();
    });
    if (inLoop)
      outputList.emplace_back(memoryValue);
  }
  return outputList;
}

/// A local array the forwarding left without a read (its stores only) is
/// dead, as Vitis deletes it (held-out self_supervised_contrastive_learning
/// `norm1[i] = 0; for (j) norm1[i] += x; norm1[i] = sqrt(norm1[i]); ...
/// / norm1[i]`: no memory). Recorded in `hls.dead_memrefs`.
static void eraseUnusedArrays(ModuleOp moduleOp, llvm::ArrayRef<Value> mems) {
  Builder passBuilder(moduleOp.getContext());
  llvm::SmallVector<Attribute> dead;
  if (auto priorOperation =
          moduleOp->getAttrOfType<ArrayAttr>("hls.dead_memrefs"))
    dead.assign(priorOperation.begin(), priorOperation.end());
  bool changed = false;
  for (Value memoryValue : mems) {
    auto alloca = memoryValue.getDefiningOp<memref::AllocaOp>();
    if (!alloca)
      continue;
    bool storesOnly =
        llvm::all_of(memoryValue.getUsers(), [&](Operation *userPragma) {
          if (auto storeOp = dyn_cast<AffineStoreOp>(userPragma))
            return storeOp.getMemRef() == memoryValue &&
                   storeOp.getValueToStore() != memoryValue;
          if (auto storeOp = dyn_cast<memref::StoreOp>(userPragma))
            return storeOp.getMemRef() == memoryValue &&
                   storeOp.getValueToStore() != memoryValue;
          return false;
        });
    if (!storesOnly)
      continue;
    for (Operation *userPragma :
         llvm::make_early_inc_range(memoryValue.getUsers()))
      userPragma->erase();
    auto fn = alloca->getParentOfType<func::FuncOp>();
    std::string name;
    if (auto operandValue =
            alloca->getAttrOfType<StringAttr>("polygeist.varname"))
      name = operandValue.getValue().str();
    dead.emplace_back(passBuilder.getDictionaryAttr(
        {passBuilder.getNamedAttr("kind", passBuilder.getStringAttr("alloca")),
         passBuilder.getNamedAttr(
             "func", passBuilder.getStringAttr(fn ? fn.getName() : "")),
         passBuilder.getNamedAttr("name", passBuilder.getStringAttr(name)),
         passBuilder.getNamedAttr("loc", alloca.getLoc()),
         passBuilder.getNamedAttr("type", TypeAttr::get(alloca.getType())),
         passBuilder.getNamedAttr(
             "by", passBuilder.getStringAttr("--auto-pipeline-unroll")),
         passBuilder.getNamedAttr(
             "reason", passBuilder.getStringAttr(
                           "no read left after the register promotion of "
                           "its element accesses forwarded them "
                           "(VITIS_NOTES N166 (a))"))}));
    alloca->erase();
    changed = true;
  }
  if (changed)
    moduleOp->setAttr("hls.dead_memrefs", passBuilder.getArrayAttr(dead));
}

static void sinkFunctionDeadStores(func::FuncOp containingFunction) {
  llvm::SmallVector<AffineForOp> loopList;
  containingFunction.walk([&](AffineForOp chosenLoopForPipeline) {
    loopList.emplace_back(chosenLoopForPipeline);
  });
  for (AffineForOp chosenLoopForPipeline : loopList) {
    (void)sinkDeadStores(chosenLoopForPipeline);
    // Read-modify-write accesses of such an element (an ap_fixed `+=` that
    // cgeist keeps in memory): promoted like LICM does.
    llvm::SmallVector<Value> around = elementsNearLoop(chosenLoopForPipeline);
    if (around.empty())
      continue;
    std::optional<uint64_t> tripCountValue =
        getConstantTripCount(chosenLoopForPipeline);
    if (!tripCountValue || *tripCountValue == 0) {
      // A loop that may not run: only an element with a conditional
      // access is promoted here (the later promotion of the pipelined
      // loop does not rewrite if-arms), without the clean-up around
      // it, so the initial store and the full width stay (kernel
      // w9r22fx_f7_condacc_vartrip: Vitis 16 bits, 60).
      if (!circt::hlsest::Config::get()
               .tool.hls.pipelineDecision.promoteConditionalAccesses)
        continue;
      llvm::erase_if(around, [&](Value memoryValue) {
        bool conditional = false;
        chosenLoopForPipeline.getBody()->walk([&](Operation *currentOperation) {
          std::optional<MemoryAccess> firstSide =
              accessDescription(currentOperation);
          if (firstSide && firstSide->memoryValue == memoryValue &&
              currentOperation->getBlock() != chosenLoopForPipeline.getBody())
            conditional = true;
        });
        return !conditional;
      });
      if (around.empty())
        continue;
    }
    unsigned promotedAccess = 0;
    promotingBeforeDecision = true;
    (void)promoteLoopInvariantAccesses(chosenLoopForPipeline, promotedAccess,
                                       nullptr, around);
    promotingBeforeDecision = false;
  }
}

/// Register promotion of every memory `loop` touches at
/// loop-invariant, pairwise disjoint addresses only (Vitis / LLVM
/// LICM scalar promotion): per address, one load before the loop,
/// the value carried as an iter_arg, one store after (a read-only address is
/// just loaded before the loop). Only affine accesses directly in
/// the body are rewritten. Returns the loop (a new op, with the same
/// attributes, when something was promoted). `nest`: the outermost
/// loop flattened with `loop` (isInvariantIn).
static AffineForOp promoteLoopInvariantAccesses(
    AffineForOp chosenLoopForPipeline, unsigned &promotedAccess,
    Operation *nestStructure = nullptr, llvm::ArrayRef<Value> only = {}) {
  ComposedAddressScope composedAddresses;
  std::optional<uint64_t> trips = getConstantTripCount(chosenLoopForPipeline);
  bool runsAtLeastOnce = trips && *trips >= 1;
  // Memories accessed directly in the body (or in its if-arms, see
  // onlyInIfArms), in first-access order.
  llvm::SmallVector<Value, 4> mems;
  auto addMem = [&](Operation *currentOperation) {
    std::optional<MemoryAccess> firstSide = accessDescription(currentOperation);
    if (firstSide && !llvm::is_contained(mems, firstSide->memoryValue))
      mems.emplace_back(firstSide->memoryValue);
  };
  if (promotingBeforeDecision) {
    chosenLoopForPipeline.getBody()->walk([&](Operation *currentOperation) {
      if (currentOperation->getBlock() == chosenLoopForPipeline.getBody() ||
          appearsOnlyInBranches(currentOperation, chosenLoopForPipeline))
        addMem(currentOperation);
    });
  } else {
    for (Operation &currentOperation :
         chosenLoopForPipeline.getBody()->without_terminator())
      addMem(&currentOperation);
  }
  unsigned promotedBefore = promotedAccess;
  for (Value memoryValue : mems) {
    if (!only.empty() && !llvm::is_contained(only, memoryValue))
      continue;
    // A promotion rewrote the loop (new induction variable, erased
    // accesses): the cached addresses may name values that are gone.
    if (promotedAccess != promotedBefore) {
      composedAddresses.cache.clear();
      promotedBefore = promotedAccess;
    }
    llvm::SmallVector<llvm::SmallVector<MemoryAccess, 4>, 2> groups;
    if (!isPromotableIn(memoryValue, chosenLoopForPipeline, &groups,
                        nestStructure) ||
        groups.empty())
      continue;
    bool allAffine = llvm::all_of(groups, [](auto &grp) {
      return llvm::all_of(grp, [](const MemoryAccess &firstSide) {
        return isa<AffineLoadOp, AffineStoreOp>(firstSide.currentOperation);
      });
    });
    Type elemType = cast<MemRefType>(memoryValue.getType()).getElementType();
    if (!allAffine || !elemType.isIntOrIndexOrFloat())
      continue;
    // One load before the loop per address, in address order. A
    // read-only location is just that load (LICM hoists it). The others are
    // carried as iter_args, added to the loop in one rewrite: one
    // per address made the rewrite quadratic in a fully unrolled body.
    llvm::SmallVector<const llvm::SmallVector<MemoryAccess, 4> *> carriedValue;
    llvm::SmallVector<Value> inits;
    for (auto &accesses : groups) {
      const MemoryAccess &firstAccess = accesses.front();
      bool anyStore = llvm::any_of(accesses, [](const MemoryAccess &firstSide) {
        return firstSide.isWrite;
      });
      OpBuilder passBuilder(chosenLoopForPipeline);
      Value init;
      if (!firstAccess.isWrite || !runsAtLeastOnce ||
          firstAccess.currentOperation->getBlock() !=
              chosenLoopForPipeline.getBody()) {
        // A store first in a loop that may run zero times leaves the
        // old value when it does not run, so LLVM LICM loads it in the
        // preheader (promoteLoopAccessesToScalars: a preheader load unless
        // the store is guaranteed to execute; W9 round 12 review, kernel
        // w9r12rv_n92_varinit, an init loop `for (t = 0; t < n;
        // t++)`: Vitis keeps the memory).
        init = AffineLoadOp::create(
            passBuilder, firstAccess.currentOperation->getLoc(), memoryValue,
            firstAccess.affineMap, firstAccess.inputOperands);
      } else {
        // The first access is a store the loop always runs: no value
        // flows in.
        init = arith::ConstantOp::create(
            passBuilder, chosenLoopForPipeline.getLoc(), elemType,
            passBuilder.getZeroAttr(elemType));
      }
      if (!anyStore) {
        // A read-only location: LICM hoists it (one load before the
        // loop).
        for (const MemoryAccess &firstSide : accesses) {
          firstSide.currentOperation->getResult(0).replaceAllUsesWith(init);
          firstSide.currentOperation->erase();
        }
        ++promotedAccess;
        continue;
      }
      carriedValue.emplace_back(&accesses);
      inits.emplace_back(init);
    }
    if (carriedValue.empty())
      continue;
    IRRewriter rewriter(chosenLoopForPipeline.getContext());
    llvm::DenseMap<Operation *, unsigned> carriedIndexOf;
    for (auto [indexValue, accesses] : llvm::enumerate(carriedValue))
      for (const MemoryAccess &firstSide : *accesses)
        carriedIndexOf[firstSide.currentOperation] = indexValue;
    Block *body = chosenLoopForPipeline.getBody();
    DictionaryAttr attrs =
        chosenLoopForPipeline->getDiscardableAttrDictionary();
    FailureOr<LoopLikeOpInterface> replaced =
        chosenLoopForPipeline.replaceWithAdditionalYields(
            rewriter, inits, /*replaceInitOperandUsesInLoop=*/false,
            [&](OpBuilder &, Location, llvm::ArrayRef<BlockArgument> newArgs) {
              llvm::SmallVector<Value> activeNest(newArgs.begin(),
                                                  newArgs.end());
              rewriteCarriedAccesses(body, carriedIndexOf, activeNest);
              return activeNest;
            });
    if (failed(replaced))
      continue;
    chosenLoopForPipeline = cast<AffineForOp>(replaced->getOperation());
    chosenLoopForPipeline->setDiscardableAttrs(attrs);
    // One store after the loop per carried address; each is inserted
    // right after the loop, so they end up in reverse address order
    // (the order the former one-address-at-a-time rewrite produced).
    unsigned firstResult =
        chosenLoopForPipeline.getNumResults() - carriedValue.size();
    // Record which iter_args carry a promoted element (N160).
    llvm::SmallVector<int64_t> promotedArgs;
    if (auto priorOperation =
            chosenLoopForPipeline->getAttrOfType<DenseI64ArrayAttr>(
                kLoopPromotedElementIterArgsAttr))
      promotedArgs.assign(priorOperation.asArrayRef().begin(),
                          priorOperation.asArrayRef().end());
    for (unsigned indexValue = firstResult;
         indexValue < chosenLoopForPipeline.getNumResults(); ++indexValue)
      promotedArgs.emplace_back(indexValue);
    chosenLoopForPipeline->setAttr(
        kLoopPromotedElementIterArgsAttr,
        DenseI64ArrayAttr::get(chosenLoopForPipeline.getContext(),
                               promotedArgs));
    for (auto [indexValue, accesses] : llvm::enumerate(carriedValue)) {
      const MemoryAccess &firstAccess = accesses->front();
      OpBuilder after(chosenLoopForPipeline.getContext());
      after.setInsertionPointAfter(chosenLoopForPipeline);
      AffineStoreOp storeOp = AffineStoreOp::create(
          after, chosenLoopForPipeline.getLoc(),
          chosenLoopForPipeline.getResult(firstResult + indexValue),
          memoryValue, firstAccess.affineMap, firstAccess.inputOperands);
      // Only around a loop that runs at least once: with a run-time
      // trip count Vitis keeps the initial store and the element's full width
      // (W9 round 22 review kernel w9r22rv_k07_vartrip: 16 bits, 60 BRAM;
      // the constant-trip control k08_consttrip is narrowed, 30).
      if (runsAtLeastOnce &&
          circt::hlsest::Config::get()
              .tool.hls.pipelineDecision.promotedStoreCleanup)
        cleanPromotedStore(storeOp, chosenLoopForPipeline);
      ++promotedAccess;
    }
  }
  return chosenLoopForPipeline;
}

static std::string formatLocation(Location sourceLoc) {
  std::string stringValue;
  llvm::raw_string_ostream os(stringValue);
  sourceLoc.print(os);
  return stringValue;
}

//===----------------------------------------------------------------------===//
// Depth of one call of a loop-free callee (VITIS_NOTES.md N14 R2 in
// a pipelined loop; W3 review D4)
//===----------------------------------------------------------------------===//
// Vitis runs the calls of one iteration that share an instance one after the
// other, each for its whole depth (latency + 1 states), so the
// loop's II is the sum of their depths (`[HLS 200-880]` carried
// dependence between the `call` operations): inl_e3 / w3rev_k4 2 x 2 = II 4,
// w3rev_k2 2 x 3 = 6, w3fx_d4_three 3 x 2 = 6, w3fx_d4_add3 2 x 3 = 6,
// w3fx_d4_rd4 2 x 4 = 8 (not 2 x its own II 2), w3fx_d4_mul 2 x 4 = 8. The
// callee's latency is an ASAP schedule of its body as the Vitis
// `*.verbose.sched.rpt` shows it:
//  - a load or store issues in the cycle its index operands are ready (Vitis
//    narrows the address arithmetic and fits it in front of the RAM), at
//    most two accesses per memory per cycle (its two ports); the data of a
//    load arrives load_data_ns (3.25 ns) into the next cycle;
//  - a combinational op starts when its last operand is ready and adds its
//    delay; when that passes the cycle budget (the clock period less the
//    default 27 % clock uncertainty of Vitis: 7.3 ns at 10 ns) it moves to
//    the next cycle (w3rev_k2 `a[i] + a[1023 - i] + tbl[...]`: the second
//    add does not fit after the load, latency 2);
//  - a multi-cycle op takes its latency in whole cycles.
// Delays: the mode per currentOperation and width over the 12 6xx verbose
// schedule reports of the Vitis 2025.1 xc7z020-1 ground-truth cache: `add` /
// `sub` / `icmp` i6-i10 1.73-1.91, i16 2.07, i32 2.55, i64 3.52 ns; `and` /
// `or` / `xor` 0.97-0.99; `select` 0.69; a variable `shl` / `lshr` /
// `ashr` 4.42; a BRAM or ROM `load` 3.25 into the cycle after it issues.
// Latencies: a 32-bit multiply of two variables 2 cycles (w3fx_d4_mul,
// `mul_32s_32s_32_2_1`); a multiply by a constant with at most two set bits
// is a shift and an add (w3rev_k2 `i * 5`: `shl` + `add`), by another
// constant a combinational multiplier (5.58 ns, the mode of `mul` i26 / i32;
// unconfirmed); wider multiplies, divisions, remainders and floating-point
// operators take the latencies of the --convert-affine-to-loopschedule
// operator table (3, 4, 5, 12, 16, 20; unconfirmed for calls).
namespace call_depth {

// The delays and latencies are the configuration's scheduling.call_depth and
// scheduling.timing.operator_latencies (the defaults are the values above).
using circt::hlsest::CallDepthConfig;
using circt::hlsest::SchedulingConfig;

/// When a value is ready: the cycle and the nanoseconds used in it.
struct ReadyTime {
  unsigned schedulingCycle = 0;
  double ns = 0.0;
  bool operator<(const ReadyTime &outputValue) const {
    return schedulingCycle != outputValue.schedulingCycle
               ? schedulingCycle < outputValue.schedulingCycle
               : ns < outputValue.ns;
  }
};

class PipelineModel {
public:
  PipelineModel(double budgetNs, const SchedulingConfig &sched)
      : budgetNs(budgetNs), delayList(sched.callDepth), sched(sched) {}

  /// Depth (latency + 1) of one call of `fn`, or nullopt when `fn` (or a
  /// function it calls) still has loops, calls itself or calls a function
  /// without a body.
  std::optional<unsigned> recursionDepth(func::FuncOp fn,
                                         SymbolTableCollection &symbolTables) {
    auto inductionValue = memo.find(fn.getOperation());
    if (inductionValue != memo.end())
      return inductionValue->second;
    if (!onStack.insert(fn.getOperation()).second)
      return std::nullopt;
    std::optional<unsigned> depthValue = schedule(fn, symbolTables);
    onStack.erase(fn.getOperation());
    memo[fn.getOperation()] = depthValue;
    return depthValue;
  }

private:
  double budgetNs;
  const CallDepthConfig &delayList;
  const SchedulingConfig &sched;
  llvm::DenseMap<Operation *, std::optional<unsigned>> memo;
  SmallPtrSet<Operation *, 4> onStack;

  /// `start` plus a combinational delay, moved to the next cycle when it
  /// does not fit the budget.
  ReadyTime nestedLoops(ReadyTime beginTime, double delayNs) const {
    if (delayNs <= 0.0)
      return beginTime;
    if (beginTime.ns + delayNs <= budgetNs)
      return {beginTime.schedulingCycle, beginTime.ns + delayNs};
    return {beginTime.schedulingCycle + 1, delayNs};
  }

  static std::optional<int64_t> constantInt(Value operandValue) {
    if (auto constantTerm = operandValue.getDefiningOp<arith::ConstantOp>())
      if (auto indexValue = dyn_cast<IntegerAttr>(constantTerm.getValue()))
        return indexValue.getValue().getSExtValue();
    return std::nullopt;
  }

  /// Data width of a value for the delay table: an index is an address, which
  /// Vitis narrows (w3rev_k2: `i10`); it is timed at `index_bits` (32).
  unsigned bitsOf(Type typeValue) const {
    if (typeValue.isIntOrFloat())
      return typeValue.getIntOrFloatBitWidth();
    return static_cast<unsigned>(delayList.indexBits);
  }

  /// Ready time of a multiply: a constant factor is shifts and adds, two
  /// variables a pipelined multiplier.
  ReadyTime multiply(arith::MulIOp mul, ReadyTime beginTime) const {
    unsigned bits = bitsOf(mul.getType());
    std::optional<int64_t> constantTerm = constantInt(mul.getLhs());
    if (!constantTerm)
      constantTerm = constantInt(mul.getRhs());
    if (constantTerm) {
      uint64_t mag = *constantTerm < 0
                         ? 0 - static_cast<uint64_t>(*constantTerm)
                         : static_cast<uint64_t>(*constantTerm);
      unsigned setBits = llvm::popcount(mag);
      if (setBits <= 1)
        return beginTime; // a shift: wiring
      if (setBits == 2)
        return nestedLoops(beginTime, delayList.carryChain(bits));
      return nestedLoops(beginTime, delayList.constantMultiplierNs);
    }
    unsigned cycles =
        static_cast<int64_t>(bits) <= delayList.narrowMultiplyMaxBits
            ? static_cast<unsigned>(delayList.narrowMultiplyCycles)
            : static_cast<unsigned>(sched.latency("multicycle"));
    return {beginTime.schedulingCycle + cycles, 0.0};
  }

  /// Latency in whole cycles of a floating-point or math op (the operator
  /// table of --convert-affine-to-loopschedule), 0 for a combinational one.
  unsigned floatCycles(Operation *currentOperation) const {
    auto lat = [&](llvm::StringRef cls) {
      return static_cast<unsigned>(sched.latency(cls));
    };
    if (isa<arith::MulFOp>(currentOperation) ||
        circt::hls_analysis::isExactReciprocalDivide(currentOperation))
      return lat("fpmul");
    if (isa<arith::AddFOp, arith::SubFOp, arith::MaximumFOp, arith::MinimumFOp,
            arith::MaxNumFOp, arith::MinNumFOp, math::FmaOp, math::FloorOp,
            math::CeilOp, math::RoundOp, math::RoundEvenOp, math::TruncOp>(
            currentOperation))
      return lat("fpaddsub");
    auto width = [&] {
      Type elt = getElementTypeOrSelf(currentOperation->getResult(0).getType());
      return elt.isIntOrFloat() ? elt.getIntOrFloatBitWidth() : 0u;
    };
    if (isa<arith::DivFOp, arith::RemFOp>(currentOperation))
      return lat(sched.floatClass("fpdiv", width()));
    if (isa<math::SqrtOp, math::RsqrtOp>(currentOperation))
      return lat(sched.floatClass("fpsqrt", width()));
    if (isa<math::AbsFOp, math::AbsIOp, math::CopySignOp>(currentOperation))
      return 0;
    if (isa_and_nonnull<math::MathDialect>(currentOperation->getDialect()))
      return lat("fptrans"); // exp, log, pow, sin, ...
    return 0;
  }

  /// For an integer add / sub `op`, the add / sub of the same type that is
  /// only used by `op` and is not itself the root of a three-input adder:
  /// the two form one TernaryAdder (scheduling.call_depth.ternary_adder_ns).
  /// Null otherwise; index arithmetic (addresses) is never grouped.
  static Operation *ternaryInner(Operation *currentOperation,
                                 const SmallPtrSetImpl<Operation *> &roots) {
    if (!isa<arith::AddIOp, arith::SubIOp>(currentOperation) ||
        !isa<IntegerType>(currentOperation->getResult(0).getType()))
      return nullptr;
    for (Value operandValue : currentOperation->getOperands()) {
      Operation *depthValue = operandValue.getDefiningOp();
      if (depthValue && isa<arith::AddIOp, arith::SubIOp>(depthValue) &&
          operandValue.hasOneUse() &&
          operandValue.getType() == currentOperation->getResult(0).getType() &&
          !roots.contains(depthValue))
        return depthValue;
    }
    return nullptr;
  }

  std::optional<unsigned> schedule(func::FuncOp fn,
                                   SymbolTableCollection &symbolTables) {
    llvm::DenseMap<Value, ReadyTime> ready;
    // Accesses per (memory, cycle): at most `ports_per_memory`.
    std::map<std::tuple<const void *, const void *, unsigned>, unsigned> ports;
    unsigned latency = 0;
    bool unsupported = false;
    // Roots of three-input adders: such a root is not grouped again.
    SmallPtrSet<Operation *, 8> ternaryRoots;

    auto readyOf = [&](Value operandValue) {
      auto inductionValue = ready.find(operandValue);
      return inductionValue == ready.end() ? ReadyTime{}
                                           : inductionValue->second;
    };
    auto latest = [&](ValueRange vs) {
      ReadyTime secondAccess;
      for (Value operandValue : vs)
        secondAccess = std::max(secondAccess, readyOf(operandValue));
      return secondAccess;
    };
    auto latestCycle = [&](ValueRange vs) {
      unsigned constantTerm = 0;
      for (Value operandValue : vs)
        constantTerm =
            std::max(constantTerm, readyOf(operandValue).schedulingCycle);
      return constantTerm;
    };
    // The first cycle >= `cycle` with a free port of `mem`.
    auto issue = [&](Value memoryValue, unsigned schedulingCycle) {
      circt::hls_analysis::StorageRoot root =
          circt::hls_analysis::storageRoot(memoryValue);
      const void *valueKey =
          root.value ? root.value.getAsOpaquePointer() : nullptr;
      const void *globalKey = root.global;
      while (ports[{valueKey, globalKey, schedulingCycle}] >=
             static_cast<unsigned>(delayList.portsPerMemory))
        ++schedulingCycle;
      ++ports[{valueKey, globalKey, schedulingCycle}];
      return schedulingCycle;
    };

    fn.getBody().walk<WalkOrder::PreOrder>([&](Operation *currentOperation) {
      if (isa<LoopLikeOpInterface>(currentOperation)) {
        unsupported = true;
        return WalkResult::interrupt();
      }
      ReadyTime beginTime = latest(currentOperation->getOperands());
      ReadyTime doneFlag = beginTime;
      Value memoryValue;
      ValueRange indices;
      bool isLoad = false, isStore = false;
      if (auto firstAccess = dyn_cast<AffineLoadOp>(currentOperation)) {
        memoryValue = firstAccess.getMemRef();
        indices = firstAccess.getMapOperands();
        isLoad = true;
      } else if (auto firstAccess =
                     dyn_cast<memref::LoadOp>(currentOperation)) {
        memoryValue = firstAccess.getMemRef();
        indices = firstAccess.getIndices();
        isLoad = true;
      } else if (auto stringValue = dyn_cast<AffineStoreOp>(currentOperation)) {
        memoryValue = stringValue.getMemRef();
        indices = stringValue.getMapOperands();
        isStore = true;
      } else if (auto stringValue =
                     dyn_cast<memref::StoreOp>(currentOperation)) {
        memoryValue = stringValue.getMemRef();
        indices = stringValue.getIndices();
        isStore = true;
      }
      if (isLoad) {
        unsigned constantTerm = issue(memoryValue, latestCycle(indices));
        doneFlag = {constantTerm + 1, delayList.loadDataNs};
      } else if (isStore) {
        unsigned constantTerm = issue(
            memoryValue,
            std::max(latestCycle(indices),
                     readyOf(currentOperation->getOperand(0)).schedulingCycle));
        latency = std::max(latency, constantTerm);
      } else if (auto callSite = dyn_cast<CallOpInterface>(currentOperation)) {
        auto calleeFunction = dyn_cast_or_null<func::FuncOp>(
            callSite.resolveCallableInTable(&symbolTables));
        std::optional<unsigned> innerLoop;
        if (calleeFunction && !calleeFunction.isExternal())
          innerLoop = recursionDepth(calleeFunction, symbolTables);
        if (!innerLoop) {
          unsupported = true;
          return WalkResult::interrupt();
        }
        doneFlag = {beginTime.schedulingCycle + *innerLoop, 0.0};
        latency = std::max(latency, doneFlag.schedulingCycle);
      } else if (auto mul = dyn_cast<arith::MulIOp>(currentOperation)) {
        doneFlag = multiply(mul, beginTime);
      } else if (isa<arith::DivSIOp, arith::DivUIOp, arith::RemSIOp,
                     arith::RemUIOp, arith::CeilDivSIOp, arith::CeilDivUIOp,
                     arith::FloorDivSIOp>(currentOperation)) {
        doneFlag = {beginTime.schedulingCycle +
                        static_cast<unsigned>(sched.latency("multicycle")),
                    0.0};
      } else if (Operation *innerLoop =
                     ternaryInner(currentOperation, ternaryRoots)) {
        // add(add(x, y), z): one three-input adder over x, y and z.
        llvm::SmallVector<Value, 3> leaves(innerLoop->getOperands());
        for (Value operandValue : currentOperation->getOperands())
          if (operandValue.getDefiningOp() != innerLoop)
            leaves.emplace_back(operandValue);
        doneFlag = nestedLoops(latest(leaves),
                               delayList.ternaryAdder(bitsOf(
                                   currentOperation->getResult(0).getType())));
        ternaryRoots.insert(currentOperation);
      } else if (isa<arith::AddIOp, arith::SubIOp, arith::CmpIOp>(
                     currentOperation)) {
        doneFlag = nestedLoops(
            beginTime, delayList.carryChain(
                           bitsOf(currentOperation->getOperand(0).getType())));
      } else if (isa<arith::AndIOp, arith::OrIOp, arith::XOrIOp>(
                     currentOperation)) {
        doneFlag = nestedLoops(beginTime, delayList.logicNs);
      } else if (isa<arith::SelectOp>(currentOperation)) {
        doneFlag = nestedLoops(beginTime, delayList.selectNs);
      } else if (isa<arith::ShLIOp, arith::ShRSIOp, arith::ShRUIOp>(
                     currentOperation)) {
        if (!constantInt(currentOperation->getOperand(1)))
          doneFlag = nestedLoops(beginTime, delayList.variableShiftNs);
      } else if (unsigned constantTerm = floatCycles(currentOperation)) {
        doneFlag = {beginTime.schedulingCycle + constantTerm, 0.0};
      } else if (isa<func::ReturnOp>(currentOperation)) {
        latency = std::max(latency, beginTime.schedulingCycle);
      } else if (currentOperation->hasTrait<OpTrait::IsTerminator>()) {
        // A yield: its region op's results are ready when its operands are.
        if (Operation *parentNode = currentOperation->getParentOp())
          if (parentNode->getNumResults() == currentOperation->getNumOperands())
            for (auto [secondAccess, operandValue] : llvm::zip(
                     parentNode->getResults(), currentOperation->getOperands()))
              ready[secondAccess] =
                  std::max(readyOf(secondAccess), readyOf(operandValue));
      }
      // Everything else (constants, casts, extensions, views, region ops
      // whose results their yields set) is wiring.
      for (Value secondAccess : currentOperation->getResults())
        if (!ready.count(secondAccess))
          ready[secondAccess] = doneFlag;
      return WalkResult::advance();
    });
    if (unsupported)
      return std::nullopt;
    return latency + 1;
  }
};

} // namespace call_depth

/// The constant an index value holds: a constant, or an affine.apply (the
/// unroll's copies of an induction variable) of constants.
static std::optional<int64_t>
indexOfConstantValue(Value operandValue, unsigned recursionDepth = 0) {
  APInt constantTerm;
  if (matchPattern(operandValue, m_ConstantInt(&constantTerm)))
    return constantTerm.getSExtValue();
  if (recursionDepth > 8)
    return std::nullopt;
  // Integer arithmetic of constants (an unrolled copy's `c + (c > 2)`, cast
  // to an index), folded by the ops' own folders as LLVM's constant folding
  // does (VITIS_NOTES N174: the subscripts of a table evaluated from fill
  // loops, kernel w9r23p_c5_revmap_fold).
  if (Operation *def = operandValue.getDefiningOp();
      def && !isa<AffineApplyOp>(def) && def->getNumResults() == 1 &&
      def->getNumRegions() == 0 && isMemoryEffectFree(def) &&
      operandValue.getType().isIntOrIndex()) {
    llvm::SmallVector<Attribute> inputOperands;
    for (Value outputValue : def->getOperands()) {
      if (!outputValue.getType().isIntOrIndex())
        return std::nullopt;
      std::optional<int64_t> keyValue =
          indexOfConstantValue(outputValue, recursionDepth + 1);
      if (!keyValue)
        return std::nullopt;
      inputOperands.emplace_back(
          IntegerAttr::get(outputValue.getType(), *keyValue));
    }
    llvm::SmallVector<OpFoldResult, 1> folded;
    if (failed(def->fold(inputOperands, folded)) || folded.size() != 1)
      return std::nullopt;
    if (auto attributeValue = dyn_cast<Attribute>(folded.front())) {
      if (auto ia = dyn_cast<IntegerAttr>(attributeValue))
        return ia.getValue().getSExtValue();
      return std::nullopt;
    }
    // A fold to an operand (`x + 0` is x).
    return indexOfConstantValue(cast<Value>(folded.front()),
                                recursionDepth + 1);
  }
  auto apply = operandValue.getDefiningOp<AffineApplyOp>();
  if (!apply)
    return std::nullopt;
  llvm::SmallVector<Attribute> inputOperands;
  for (Value outputValue : apply.getMapOperands()) {
    std::optional<int64_t> keyValue =
        indexOfConstantValue(outputValue, recursionDepth + 1);
    if (!keyValue)
      return std::nullopt;
    inputOperands.emplace_back(
        IntegerAttr::get(IndexType::get(operandValue.getContext()), *keyValue));
  }
  llvm::SmallVector<Attribute> outputResults;
  if (failed(apply.getAffineMap().constantFold(inputOperands, outputResults)) ||
      outputResults.size() != 1)
    return std::nullopt;
  auto indexValue = dyn_cast_or_null<IntegerAttr>(outputResults[0]);
  if (!indexValue)
    return std::nullopt;
  return indexValue.getInt();
}

/// The constant subscripts of a load, or nullopt.
static std::optional<llvm::SmallVector<uint64_t>>
constantSubscripts(Operation *memoryLoad) {
  llvm::SmallVector<uint64_t> outputList;
  if (auto firstAccess = dyn_cast<AffineLoadOp>(memoryLoad)) {
    llvm::SmallVector<Attribute> inputOperands;
    for (Value operandValue : firstAccess.getMapOperands()) {
      std::optional<int64_t> constantTerm = indexOfConstantValue(operandValue);
      if (!constantTerm)
        return std::nullopt;
      inputOperands.emplace_back(IntegerAttr::get(
          IndexType::get(memoryLoad->getContext()), *constantTerm));
    }
    llvm::SmallVector<Attribute> outputResults;
    if (failed(firstAccess.getAffineMap().constantFold(inputOperands,
                                                       outputResults)))
      return std::nullopt;
    for (Attribute secondAccess : outputResults) {
      auto indexValue = dyn_cast_or_null<IntegerAttr>(secondAccess);
      if (!indexValue || indexValue.getValue().isNegative())
        return std::nullopt;
      outputList.emplace_back(indexValue.getValue().getZExtValue());
    }
    return outputList;
  }
  if (auto firstAccess = dyn_cast<memref::LoadOp>(memoryLoad)) {
    for (Value operandValue : firstAccess.getIndices()) {
      std::optional<int64_t> constantTerm = indexOfConstantValue(operandValue);
      if (!constantTerm || *constantTerm < 0)
        return std::nullopt;
      outputList.emplace_back(static_cast<uint64_t>(*constantTerm));
    }
    return outputList;
  }
  return std::nullopt;
}

/// VITIS_NOTES N168: after the unroll every subscript of a table read in a
/// completely unrolled loop is a constant, and Vitis loads the
/// initialiser's element (kernels w9r22p_e1_rom_unroll / e4_rom_unroll_int: the
/// table is deleted at a.o.1, 0 BRAM; e2 / e3 / e5 with variable subscripts
/// keep it). Only loads of the get_global result itself are folded; a user
/// storage or partition pragma on the table does not stop the fold (W9 round
/// 22 review kernels w9r22rv_k11_rom_bound, bind_storage rom_2p impl=bram,
/// and w9r22fx_f1_rom_part, a cyclic partition: 0 BRAM). A global whose
/// every use is gone is erased.
static void foldConstantLoad(ModuleOp moduleOp) {
  llvm::StringMap<llvm::SmallVector<Value>> sites;
  moduleOp.walk([&](memref::GetGlobalOp gg) {
    sites[gg.getName()].emplace_back(gg.getResult());
  });
  llvm::SmallVector<memref::GlobalOp> globals(
      moduleOp.getOps<memref::GlobalOp>());
  for (memref::GlobalOp groupValue : globals) {
    auto dense =
        dyn_cast_or_null<DenseElementsAttr>(groupValue.getInitialValueAttr());
    if (groupValue.isExternal() || !dense ||
        !groupValue.getType().hasStaticShape() ||
        !isa<IntegerType, FloatType>(dense.getElementType()) ||
        dense.getElementType() != groupValue.getType().getElementType())
      continue;
    auto inductionValue = sites.find(groupValue.getSymName());
    if (inductionValue == sites.end() ||
        !circt::hls_analysis::neverWritten(inductionValue->second))
      continue;
    llvm::ArrayRef<int64_t> shape = groupValue.getType().getShape();
    bool anyFolded = false;
    for (Value site : inductionValue->second) {
      llvm::SmallVector<Operation *> loads;
      for (Operation *userPragma : site.getUsers())
        if (isa<AffineLoadOp, memref::LoadOp>(userPragma) &&
            userPragma->getOperand(0) == site)
          loads.emplace_back(userPragma);
      for (Operation *memoryLoad : loads) {
        std::optional<llvm::SmallVector<uint64_t>> idx =
            constantSubscripts(memoryLoad);
        if (!idx || idx->size() != shape.size())
          continue;
        bool inBounds = true;
        for (auto [indexValue, extent] : llvm::zip(*idx, shape))
          inBounds &= static_cast<int64_t>(indexValue) < extent;
        if (!inBounds)
          continue;
        uint64_t flat = 0;
        for (auto [indexValue, extent] : llvm::zip(*idx, shape))
          flat = flat * static_cast<uint64_t>(extent) + indexValue;
        Attribute element = *std::next(dense.getValues<Attribute>().begin(),
                                       static_cast<int64_t>(flat));
        auto value = cast<TypedAttr>(element);
        OpBuilder passBuilder(memoryLoad);
        Value constantTerm =
            arith::ConstantOp::create(passBuilder, memoryLoad->getLoc(), value);
        memoryLoad->getResult(0).replaceAllUsesWith(constantTerm);
        memoryLoad->erase();
        anyFolded = true;
      }
    }
    if (!anyFolded)
      continue;
    bool allUnused = true;
    for (Value site : inductionValue->second) {
      if (site.use_empty())
        site.getDefiningOp()->erase();
      else
        allUnused = false;
    }
    if (allUnused && SymbolTable::symbolKnownUseEmpty(groupValue, moduleOp))
      groupValue.erase();
  }
}

struct PipelineDecisionPass
    : public PassWrapper<PipelineDecisionPass, OperationPass<ModuleOp>> {
  MLIR_DEFINE_EXPLICIT_INTERNAL_INLINE_TYPE_ID(PipelineDecisionPass)

  PipelineDecisionPass() = default;
  PipelineDecisionPass(const PipelineDecisionPass &other)
      : PassWrapper(other) {}

  Option<unsigned> pipelineLoops{
      *this, "pipeline-loops",
      llvm::cl::desc("Vitis config_compile -pipeline_loops: a loop whose "
                     "nested trip-count products are all <= this is "
                     "pipelined and everything inside it unrolled; 0 "
                     "disables the automatic decision (default 64)"),
      llvm::cl::init(64)};
  Option<bool> promotePipelined{
      *this, "promote-pipelined",
      llvm::cl::desc("Also promote the loop-invariant accesses of the "
                     "pipelined loop itself to registers once its inner "
                     "loops are unrolled (Vitis LICM; off keeps them as "
                     "memory accesses of the pipeline)"),
      llvm::cl::init(true)};
  Option<bool> floatLoadsPerfect{
      *this, "float-loads-perfect",
      llvm::cl::desc("A read-only inner-invariant load of a floating-point "
                     "element does not make a loop nest imperfect, so the "
                     "nest is flattened rather than its inner loop unrolled "
                     "(Vitis 2025.1 observation, VITIS_NOTES.md N3). On by "
                     "default (MEMOS.md M8, decision #3); =false: every "
                     "hoistable invariant load breaks perfectness, the "
                     "original T3 rule"),
      llvm::cl::init(true)};
  Option<bool> emitRemarks{
      *this, "emit-remarks",
      llvm::cl::desc("Print one remark per decision (pipeline, unroll, "
                     "flatten, user unroll)"),
      llvm::cl::init(false)};
  // The cycle budget of the call-depth estimate (hls.call_depth): the clock
  // period less the clock uncertainty, which Vitis defaults to 27 % of the
  // period (7.3 ns of the ground-truth 10 ns, `<State 2>: 5.806ns` in
  // w3rev_k4 get2 fits, 8.35 ns in w3rev_k2 get2 does not).
  Option<double> clockPeriodNs{
      *this, "clock-period-ns",
      llvm::cl::desc("Target clock period in ns for the depth of a call in "
                     "a pipelined loop (Vitis create_clock; default 10, the "
                     "ground-truth configuration)"),
      llvm::cl::init(10.0)};
  Option<double> clockUncertaintyPct{
      *this, "clock-uncertainty-pct",
      llvm::cl::desc("Clock uncertainty in percent of the period (Vitis "
                     "default 27)"),
      llvm::cl::init(27.0)};

  llvm::StringRef getArgument() const final { return "auto-pipeline-unroll"; }
  llvm::StringRef getDescription() const final {
    return "Vitis automatic pipeline / unroll / flatten decision "
           "(config_compile -pipeline_loops)";
  }

  void getDependentDialects(DialectRegistry &registry) const override {
    registry.insert<arith::ArithDialect, memref::MemRefDialect>();
  }

  // The values the run uses: an option given explicitly, else the
  // configuration (tool.hls.options.pipeline_loops,
  // tool.hls.pipeline_decision.*, run.clock_ns, tool.hls.timing_margin);
  // resolved at the start of runOnOperation.
  unsigned pipelineLoopsValue = 64;
  bool promotePipelinedValue = true;
  bool floatLoadsPerfectValue = true;
  /// tool.hls.pipeline_decision.do_while_flatten_refusal (N96).
  bool doWhileRefusalValue = true;
  /// tool.hls.pipeline_decision.do_while_min_subloop_trip (N96).
  uint64_t doWhileMinSubLoopTrip = 3;
  /// tool.hls.pipeline_decision.partial_unroll_runtime_loops (N103).
  bool partialUnrollRuntimeValue = true;

  /// How many of `loops` (outermost first, the innermost directly around
  /// the pipeline's absorbed loops) flatten into the pipeline: those inside
  /// the innermost loop of `refused` (N96).
  static unsigned
  flattenableParents(llvm::ArrayRef<AffineForOp> loopList,
                     const llvm::SmallPtrSetImpl<Operation *> &refused) {
    unsigned elementTotal = 0;
    for (AffineForOp chosenLoopForPipeline : llvm::reverse(loopList)) {
      if (refused.contains(chosenLoopForPipeline.getOperation()))
        break;
      ++elementTotal;
    }
    return elementTotal;
  }

  /// The cycle budget of the call-depth model: the clock period less the
  /// clock uncertainty.
  double callDepthBudgetNs(const circt::hlsest::Config &cfg) const {
    double period =
        circt::hlsest::resolveOption(clockPeriodNs, cfg.run.clockNs);
    if (clockUncertaintyPct.hasValue())
      return period * (1.0 - clockUncertaintyPct / 100.0);
    const circt::hlsest::TimingMargin &middleValue = cfg.tool.hls.timingMargin;
    if (middleValue.fraction)
      return period * (1.0 - *middleValue.fraction);
    if (middleValue.ns)
      return period - *middleValue.ns;
    return period;
  }

  std::function<void(Location, const llvm::Twine &)> remarkFn;

  void emitRemark(Location sourceLoc, const llvm::Twine &msg) {
    if (remarkFn)
      remarkFn(sourceLoc, msg);
    LLVM_DEBUG(llvm::dbgs() << msg << " @ " << sourceLoc << "\n");
  }

  /// Step 0: user `hls.unroll` pragmas, innermost loops first.
  void applyUserUnrolls(func::FuncOp containingFunction) {
    llvm::SmallVector<AffineForOp> loopList;
    containingFunction.walk<WalkOrder::PostOrder>(
        [&](AffineForOp chosenLoopForPipeline) {
          if (unrollFactorFromPragma(chosenLoopForPipeline))
            loopList.emplace_back(chosenLoopForPipeline);
        });
    for (AffineForOp chosenLoopForPipeline : loopList) {
      uint64_t unrollFactor = *unrollFactorFromPragma(chosenLoopForPipeline);
      std::optional<uint64_t> tripCountValue =
          getConstantTripCount(chosenLoopForPipeline);
      Location loopLoc = chosenLoopForPipeline.getLoc();
      chosenLoopForPipeline->removeAttr(kLoopUnrollAttr);
      Builder passBuilder(chosenLoopForPipeline.getContext());
      if (unrollFactor != 1)
        markUserUnrollCopies(chosenLoopForPipeline);
      if (unrollFactor == 1) {
        chosenLoopForPipeline->setAttr(kLoopUnrollPartialAttr,
                                       passBuilder.getI64IntegerAttr(1));
        emitRemark(loopLoc, "user unroll: factor 1, the loop is never "
                            "auto-unrolled into a parent pipeline");
        continue;
      }
      if (unrollFactor == 0 ||
          (tripCountValue && unrollFactor >= *tripCountValue)) {
        if (!tripCountValue) {
          emitRemark(loopLoc, "user unroll: dynamic trip count, left rolled");
          continue;
        }
        emitRemark(loopLoc, "user unroll: completely (trip " +
                                llvm::Twine(*tripCountValue) + ")");
        if (failed(
                circt::hls_analysis::hlsLoopUnrollFull(chosenLoopForPipeline)))
          LLVM_DEBUG(llvm::dbgs() << "  loopUnrollFull failed\n");
        continue;
      }
      emitRemark(loopLoc, "user unroll: by factor " +
                              llvm::Twine(unrollFactor) +
                              " (the loop is never auto-unrolled into a "
                              "parent pipeline)");
      applyPartialUnroll(chosenLoopForPipeline, unrollFactor);
    }
    if (!partialUnrollRuntimeValue)
      return;
    llvm::SmallVector<scf::ForOp> runtimeLoops;
    containingFunction.walk<WalkOrder::PostOrder>(
        [&](scf::ForOp chosenLoopForPipeline) {
          std::optional<uint64_t> flagValue =
              unrollFactorFromPragma(chosenLoopForPipeline);
          if (!flagValue || *flagValue <= 1)
            return;
          // Inside a user-pipelined loop the pipeline's complete
          // unroll wins and fails on the run-time trip count ([HLS 214-187]
          // "Cannot unroll loop
          // ... as it has a variable trip count": class_ece8893 Shengxi_Liang
          // LAB3 B_loop, shibao_su lab3): the loop stays rolled.
          for (Operation *pointerValue = chosenLoopForPipeline->getParentOp();
               pointerValue && !isa<func::FuncOp>(pointerValue);
               pointerValue = pointerValue->getParentOp())
            if ((isa<AffineForOp>(pointerValue) ||
                 isDynamicLoop(pointerValue)) &&
                hasUserPipelineTag(pointerValue)) {
              emitRemark(chosenLoopForPipeline.getLoc(),
                         "user unroll: run-time trip count inside a "
                         "pipelined loop, left rolled");
              return;
            }
          runtimeLoops.emplace_back(chosenLoopForPipeline);
        });
    for (scf::ForOp chosenLoopForPipeline : runtimeLoops) {
      uint64_t unrollFactor = *unrollFactorFromPragma(chosenLoopForPipeline);
      markUserUnrollCopies(chosenLoopForPipeline);
      emitRemark(chosenLoopForPipeline.getLoc(),
                 "user unroll: run-time trip count, by factor " +
                     llvm::Twine(unrollFactor) +
                     " with guarded copies (VITIS_NOTES N103)");
      applyRuntimePartialUnroll(chosenLoopForPipeline, unrollFactor);
    }
  }

  /// Marks the calls and math ops of a loop a user `unroll` pragma
  /// unrolls (hls.user_unroll_copy; the copies inherit the mark): debug
  /// provenance and the N16 R6 test in --bram-analysis (a library core called
  /// from such copies stays one module per copy).
  static void markUserUnrollCopies(Operation *chosenLoopForPipeline) {
    Builder passBuilder(chosenLoopForPipeline->getContext());
    chosenLoopForPipeline->walk([&](Operation *currentOperation) {
      if (isa<CallOpInterface>(currentOperation) ||
          currentOperation->getName().getDialectNamespace() == "math")
        currentOperation->setAttr(circt::hls_analysis::kUserUnrollCopyAttr,
                                  passBuilder.getUnitAttr());
    });
  }

  /// `#pragma HLS unroll factor=F` on an scf.for whose trip count is only
  /// known at run time (VITIS_NOTES N103: Vitis applies it, [HLS 214-188],
  /// and keeps the loop's II). The loop becomes one of
  /// step F * step whose body holds F copies; copy u > 0 runs under `iv + u *
  /// step < ub` (Vitis keeps the exit test in the unrolled body, there is no
  /// epilogue loop). Loop-carried values flow through the copies (an
  /// skipped copy passes them on unchanged). The new loop carries
  /// `hls.unroll_partial`.
  void applyRuntimePartialUnroll(scf::ForOp chosenLoopForPipeline,
                                 uint64_t unrollFactor) {
    OpBuilder passBuilder(chosenLoopForPipeline);
    Location runtimeUnrollBuildLoc = chosenLoopForPipeline.getLoc();
    Value step = chosenLoopForPipeline.getStep();
    Type ivType = step.getType();
    auto constant = [&](OpBuilder &runtimeBodyBuilder,
                        int64_t runtimeConstantValue) -> Value {
      if (ivType.isIndex())
        return runtimeBodyBuilder.create<arith::ConstantIndexOp>(
            runtimeUnrollBuildLoc, runtimeConstantValue);
      return runtimeBodyBuilder.create<arith::ConstantOp>(
          runtimeUnrollBuildLoc,
          runtimeBodyBuilder.getIntegerAttr(ivType, runtimeConstantValue));
    };
    Value runtimeWidenedStep = passBuilder.createOrFold<arith::MulIOp>(
        runtimeUnrollBuildLoc, step,
        constant(passBuilder, static_cast<int64_t>(unrollFactor)));
    Block *runtimeSourceBody = chosenLoopForPipeline.getBody();
    auto cloneBody = [&](OpBuilder &runtimeBodyBuilder, Value iv,
                         ValueRange runtimeCarriedArgs) {
      IRMapping map;
      map.map(chosenLoopForPipeline.getInductionVar(), iv);
      map.map(chosenLoopForPipeline.getRegionIterArgs(), runtimeCarriedArgs);
      for (Operation &currentOperation :
           runtimeSourceBody->without_terminator())
        runtimeBodyBuilder.clone(currentOperation, map);
      auto yield = cast<scf::YieldOp>(runtimeSourceBody->getTerminator());
      llvm::SmallVector<Value> runtimeYielded;
      for (Value operandValue : yield.getOperands())
        runtimeYielded.emplace_back(map.lookupOrDefault(operandValue));
      return runtimeYielded;
    };
    auto newLoop = passBuilder.create<scf::ForOp>(
        runtimeUnrollBuildLoc, chosenLoopForPipeline.getLowerBound(),
        chosenLoopForPipeline.getUpperBound(), runtimeWidenedStep,
        chosenLoopForPipeline.getInitArgs(),
        [&](OpBuilder &runtimeBodyBuilder, Location runtimeCopyLoc, Value iv,
            ValueRange args) {
          llvm::SmallVector<Value> runtimeCarriedArgs =
              cloneBody(runtimeBodyBuilder, iv, args);
          for (uint64_t runtimeCopyIndex = 1; runtimeCopyIndex < unrollFactor;
               ++runtimeCopyIndex) {
            Value offset = runtimeBodyBuilder.createOrFold<arith::MulIOp>(
                runtimeCopyLoc, step,
                constant(runtimeBodyBuilder,
                         static_cast<int64_t>(runtimeCopyIndex)));
            Value runtimeCopyIv = runtimeBodyBuilder.create<arith::AddIOp>(
                runtimeCopyLoc, iv, offset);
            // scf.for compares its bounds signed.
            Value runtimeBelowUpper = runtimeBodyBuilder.create<arith::CmpIOp>(
                runtimeCopyLoc, arith::CmpIPredicate::slt, runtimeCopyIv,
                chosenLoopForPipeline.getUpperBound());
            auto runtimeGuardedCopy = runtimeBodyBuilder.create<scf::IfOp>(
                runtimeCopyLoc, runtimeBelowUpper,
                [&](OpBuilder &tb, Location) {
                  tb.create<scf::YieldOp>(
                      runtimeCopyLoc,
                      cloneBody(tb, runtimeCopyIv, runtimeCarriedArgs));
                },
                [&](OpBuilder &eb, Location) {
                  eb.create<scf::YieldOp>(runtimeCopyLoc, runtimeCarriedArgs);
                });
            runtimeCarriedArgs.assign(runtimeGuardedCopy.getResults().begin(),
                                      runtimeGuardedCopy.getResults().end());
          }
          runtimeBodyBuilder.create<scf::YieldOp>(runtimeCopyLoc,
                                                  runtimeCarriedArgs);
        });
    for (NamedAttribute attributeValue :
         chosenLoopForPipeline->getDiscardableAttrs())
      if (attributeValue.getName() != kLoopUnrollAttr)
        newLoop->setAttr(attributeValue.getName(), attributeValue.getValue());
    newLoop->setAttr(
        kLoopUnrollPartialAttr,
        passBuilder.getI64IntegerAttr(static_cast<int64_t>(unrollFactor)));
    newLoop->setAttr(kLoopUnrollRuntimeGuardedAttr, passBuilder.getUnitAttr());
    chosenLoopForPipeline.replaceAllUsesWith(newLoop.getResults());
    chosenLoopForPipeline.erase();
  }

  /// `#pragma HLS unroll factor=F` with 1 < F < trip count (or a dynamic
  /// trip count). loopUnrollByFactor keeps `loop` as the main
  /// loop (step scaled by F) and, when F does not divide the trip
  /// count, clones it - attributes included - into a cleanup loop
  /// with the original step right after it; either loop is replaced
  /// by its body when it is left with a single iteration (`loop` is
  /// then erased). Vitis has no epilogue loop (the exit checks stay
  /// in the unrolled body): the cleanup loop is unrolled completely
  /// into straight-line code, and only the main loop - if it is
  /// still a loop - gets `hls.unroll_partial`, so no second
  /// partially-unrolled pipeline appears.
  void applyPartialUnroll(AffineForOp chosenLoopForPipeline,
                          uint64_t unrollFactor) {
    Builder passBuilder(chosenLoopForPipeline.getContext());
    auto markMain = [&](AffineForOp main) {
      main->setAttr(
          kLoopUnrollPartialAttr,
          passBuilder.getI64IntegerAttr(static_cast<int64_t>(unrollFactor)));
    };
    // An empty body: loopUnrollByFactor leaves the loop as it is.
    if (llvm::hasSingleElement(
            chosenLoopForPipeline.getBody()->getOperations())) {
      markMain(chosenLoopForPipeline);
      return;
    }
    // Where the results of the call will sit: between `prev` and `next`
    // (both survive it; a loop always has a terminator after it).
    Block *partialUnrollContainingBlock = chosenLoopForPipeline->getBlock();
    Operation *partialUnrollPrecedingOp = chosenLoopForPipeline->getPrevNode();
    Operation *partialUnrollFollowingOp = chosenLoopForPipeline->getNextNode();
    int64_t partialUnrollSourceStep = chosenLoopForPipeline.getStepAsInt();
    // The calls and math ops of one iteration; their copies for the
    // remainder iterations are marked below.
    auto isCoreOp = [](Operation *currentOperation) {
      return isa<CallOpInterface>(currentOperation) ||
             currentOperation->getName().getDialectNamespace() == "math";
    };
    unsigned partialUnrollCoresPerIteration = 0;
    chosenLoopForPipeline.getBody()->walk([&](Operation *currentOperation) {
      if (isCoreOp(currentOperation)) {
        currentOperation->setAttr(kUnrollPendingAttr,
                                  passBuilder.getUnitAttr());
        ++partialUnrollCoresPerIteration;
      }
    });
    std::optional<uint64_t> partialUnrollKnownTrips =
        affine::getConstantTripCount(chosenLoopForPipeline);
    // A temporary marker the cleanup clone inherits, to find both loops.
    chosenLoopForPipeline->setAttr(kUnrollPendingAttr,
                                   passBuilder.getUnitAttr());
    auto clearPending = [&] {
      for (Operation *currentOperation =
               partialUnrollPrecedingOp
                   ? partialUnrollPrecedingOp->getNextNode()
                   : &partialUnrollContainingBlock->front();
           currentOperation && currentOperation != partialUnrollFollowingOp;
           currentOperation = currentOperation->getNextNode())
        currentOperation->walk([&](Operation *innerLoop) {
          if (isCoreOp(innerLoop))
            innerLoop->removeAttr(kUnrollPendingAttr);
        });
    };
    if (failed(circt::hls_analysis::hlsLoopUnrollByFactor(chosenLoopForPipeline,
                                                          unrollFactor))) {
      // Fails before touching the IR (bounds with several results).
      LLVM_DEBUG(llvm::dbgs() << "  loopUnrollByFactor failed\n");
      chosenLoopForPipeline->removeAttr(kUnrollPendingAttr);
      clearPending();
      markMain(chosenLoopForPipeline);
      return;
    }
    llvm::SmallVector<AffineForOp, 2> partialUnrollUnrolledLoops;
    for (Operation *currentOperation =
             partialUnrollPrecedingOp ? partialUnrollPrecedingOp->getNextNode()
                                      : &partialUnrollContainingBlock->front();
         currentOperation && currentOperation != partialUnrollFollowingOp;
         currentOperation = currentOperation->getNextNode())
      if (auto affineLoop = dyn_cast<AffineForOp>(currentOperation))
        if (affineLoop->hasAttr(kUnrollPendingAttr))
          partialUnrollUnrolledLoops.emplace_back(affineLoop);
    // The remainder's calls and math ops are copies of the unrolled body's
    // (kUnrollRemainderAttr), whether the main loop is still a
    // loop or was promoted to straight-line code (one iteration
    // left: w11rv_r8, trip count 10, factor 8, keeps no loop): the
    // ops of the cleanup loop, or, when the cleanup was promoted too
    // (one remainder iteration), the last iteration's worth of them in program
    // order.
    bool partialUnrollHasCleanupLoop = llvm::any_of(
        partialUnrollUnrolledLoops, [&](AffineForOp loopCandidate) {
          return loopCandidate.getStepAsInt() == partialUnrollSourceStep;
        });
    auto markRemainder = [&](Operation *currentOperation) {
      currentOperation->setAttr(circt::hls_analysis::kUnrollRemainderAttr,
                                passBuilder.getUnitAttr());
    };
    if (!partialUnrollHasCleanupLoop && partialUnrollKnownTrips &&
        *partialUnrollKnownTrips % unrollFactor == 1) {
      llvm::SmallVector<Operation *> partialUnrollRemainderOps;
      for (Operation *currentOperation =
               partialUnrollPrecedingOp
                   ? partialUnrollPrecedingOp->getNextNode()
                   : &partialUnrollContainingBlock->front();
           currentOperation && currentOperation != partialUnrollFollowingOp;
           currentOperation = currentOperation->getNextNode()) {
        if (auto affineLoop = dyn_cast<AffineForOp>(currentOperation);
            affineLoop && affineLoop->hasAttr(kUnrollPendingAttr))
          continue; // the main loop
        currentOperation->walk<WalkOrder::PreOrder>([&](Operation *innerLoop) {
          if (isCoreOp(innerLoop) && innerLoop->hasAttr(kUnrollPendingAttr))
            partialUnrollRemainderOps.emplace_back(innerLoop);
        });
      }
      if (partialUnrollCoresPerIteration <= partialUnrollRemainderOps.size())
        for (Operation *currentOperation :
             llvm::ArrayRef(partialUnrollRemainderOps)
                 .take_back(partialUnrollCoresPerIteration))
          markRemainder(currentOperation);
    }
    clearPending();
    for (AffineForOp affineLoop : partialUnrollUnrolledLoops) {
      affineLoop->removeAttr(kUnrollPendingAttr);
      if (affineLoop.getStepAsInt() != partialUnrollSourceStep) {
        markMain(affineLoop); // the main loop, step * factor
        continue;
      }
      affineLoop.getBody()->walk([&](Operation *currentOperation) {
        if (isCoreOp(currentOperation))
          markRemainder(currentOperation);
      });
      emitRemark(affineLoop.getLoc(),
                 "user unroll: remainder iterations unrolled completely (Vitis "
                 "keeps them in the unrolled body, there is no epilogue "
                 "loop)");
      if (failed(circt::hls_analysis::hlsLoopUnrollFull(affineLoop)))
        emitRemark(affineLoop.getLoc(), "user unroll: the remainder loop has a "
                                        "dynamic trip count, left rolled");
    }
  }

  /// Every loop inside `region`, innermost first, callee loops
  /// included.
  void collectInner(Region &region,
                    llvm::SmallVector<AffineForOp> &collectInnerLoops,
                    SmallPtrSetImpl<Operation *> &collectSeenCallees,
                    SymbolTableCollection &collectTables) {
    region.walk<WalkOrder::PostOrder>([&](Operation *op) {
      if (auto affineLoop = dyn_cast<AffineForOp>(op)) {
        collectInnerLoops.emplace_back(affineLoop);
      } else if (auto caller = dyn_cast<CallOpInterface>(op)) {
        auto callee = dyn_cast_or_null<func::FuncOp>(
            caller.resolveCallableInTable(&collectTables));
        if (callee && !callee.isExternal() &&
            collectSeenCallees.insert(callee.getOperation()).second)
          collectInner(callee.getBody(), collectInnerLoops, collectSeenCallees,
                       collectTables);
      }
    });
  }

  /// Everything inside the pipelined loop (an affine.for or a
  /// runtime loop) is unrolled completely. Each unrolled
  /// loop is recorded on `pipelined` in `hls.auto_unrolled`. Returns
  /// the number of loops unrolled.
  unsigned unrollInside(Operation *unrollInsidePipelineRoot,
                        SymbolTableCollection &collectTables) {
    llvm::SmallVector<AffineForOp> collectInnerLoops;
    SmallPtrSet<Operation *, 4> collectSeenCallees;
    // The function that owns `pipelined` is never re-entered through a call
    // (direct or mutual recursion): that would collect `pipelined` itself,
    // or an ancestor of it, and erase it under our feet.
    if (auto owner = unrollInsidePipelineRoot->getParentOfType<func::FuncOp>())
      collectSeenCallees.insert(owner.getOperation());
    for (Region &region : unrollInsidePipelineRoot->getRegions())
      collectInner(region, collectInnerLoops, collectSeenCallees,
                   collectTables);
    Builder passBuilder(unrollInsidePipelineRoot->getContext());
    llvm::SmallVector<Attribute> unrollInsideHistory;
    if (auto unrollInsideOldHistory =
            unrollInsidePipelineRoot->getAttrOfType<ArrayAttr>(
                kLoopAutoUnrolledAttr))
      unrollInsideHistory.append(unrollInsideOldHistory.begin(),
                                 unrollInsideOldHistory.end());
    unsigned unrollInsideTotalLoops = 0;
    for (AffineForOp loop : collectInnerLoops) {
      if (loop.getOperation() == unrollInsidePipelineRoot ||
          loop->isProperAncestor(unrollInsidePipelineRoot))
        continue;
      std::optional<uint64_t> trips = getConstantTripCount(loop);
      if (!trips) {
        emitRemark(loop.getLoc(), "cannot unroll: dynamic trip count");
        continue;
      }
      unsigned hoisted = hoistLoopInvariantOps(loop);
      unsigned promotedAccess = 0;
      loop = promoteLoopInvariantAccesses(loop, promotedAccess);
      emitRemark(
          loop.getLoc(),
          "unrolling loop completely with a factor of " + llvm::Twine(*trips) +
              " (implied by the pipeline of the loop at " +
              formatLocation(unrollInsidePipelineRoot->getLoc()) +
              "; hoisted " + llvm::Twine(hoisted) +
              " invariant op(s), promoted " + llvm::Twine(promotedAccess) +
              " memory(ies) to registers)");
      loop->removeAttr(kLoopPipelineAttr);
      loop->removeAttr(kLoopFlattenedParentsAttr);
      loop->removeAttr(kLoopAutoUnrolledAttr);
      LocationAttr loopLoc = loop.getLoc();
      if (failed(circt::hls_analysis::hlsLoopUnrollFull(loop))) {
        LLVM_DEBUG(llvm::dbgs() << "  loopUnrollFull failed\n");
        continue;
      }
      unrollInsideHistory.emplace_back(passBuilder.getDictionaryAttr(
          {passBuilder.getNamedAttr(
               "factor",
               passBuilder.getI64IntegerAttr(static_cast<int64_t>(*trips))),
           passBuilder.getNamedAttr("loc", loopLoc)}));
      ++unrollInsideTotalLoops;
    }
    if (!unrollInsideHistory.empty())
      unrollInsidePipelineRoot->setAttr(
          kLoopAutoUnrolledAttr, passBuilder.getArrayAttr(unrollInsideHistory));
    return unrollInsideTotalLoops;
  }

  /// LLVM LICM also promotes the accesses that became loop-invariant
  /// in the pipelined loop itself once its inner loops were unrolled
  /// (`acc[0..7] += ..` in a loop over k): the recurrence then runs
  /// through registers and the scheduler sees it as an iter_args recurrence.
  AffineForOp promoteOutOfPipeline(AffineForOp chosenLoopForPipeline,
                                   Operation *nestStructure = nullptr) {
    unsigned promotedAccess = 0;
    AffineForOp result = promoteLoopInvariantAccesses(
        chosenLoopForPipeline, promotedAccess, nestStructure);
    if (promotedAccess)
      emitRemark(result.getLoc(), "promoted " + llvm::Twine(promotedAccess) +
                                      " invariant location(s) of the pipelined "
                                      "loop to registers");
    return result;
  }

  /// With tool.hls.pipeline_decision.promote_nest_invariant_only, the
  /// promotion waits until the parents' flatten decisions are made
  /// (promotePending): a location that changes with a loop flattened
  /// into the pipeline is not invariant in the flattened loop, and
  /// Vitis reads and writes it in every iteration (W9r16 review kernels
  /// w9r16rv_gp_flat / gp_flatc, `M[i][j] += ..` in a pipelined k
  /// loop flattened with i and j: M 1R1W, 2 BRAM; GP_selection
  /// loop 1180_20).
  AffineForOp promoteNowOrLater(AffineForOp chosenLoopForPipeline) {
    if (!circt::hlsest::Config::get()
             .tool.hls.pipelineDecision.promoteNestInvariantOnly)
      return promoteOutOfPipeline(chosenLoopForPipeline);
    chosenLoopForPipeline->setAttr(
        kPendingPromotionAttr,
        UnitAttr::get(chosenLoopForPipeline.getContext()));
    return chosenLoopForPipeline;
  }

  /// The deferred promotions of `func`'s pipelined loops, each against its
  /// flattened nest (hls.flattened_parents enclosing loops).
  void promotePending(func::FuncOp containingFunction) {
    llvm::SmallVector<AffineForOp> pending;
    containingFunction.walk([&](AffineForOp chosenLoopForPipeline) {
      if (chosenLoopForPipeline->hasAttr(kPendingPromotionAttr))
        pending.emplace_back(chosenLoopForPipeline);
    });
    for (AffineForOp chosenLoopForPipeline : pending) {
      chosenLoopForPipeline->removeAttr(kPendingPromotionAttr);
      Operation *nestStructure = nullptr;
      unsigned parentNodes =
          static_cast<unsigned>(getFlattenedParents(chosenLoopForPipeline));
      for (Operation *currentOperation = chosenLoopForPipeline->getParentOp();
           currentOperation && parentNodes > 0;
           currentOperation = currentOperation->getParentOp())
        if (isa<AffineForOp>(currentOperation) ||
            isDynamicLoop(currentOperation)) {
          nestStructure = currentOperation;
          --parentNodes;
        }
      promoteOutOfPipeline(chosenLoopForPipeline, nestStructure);
    }
  }

  void decide(LoopNode &candidate, SymbolTableCollection &symbolTables) {
    if (candidate.runtimeLoop)
      return decideRuntime(candidate, symbolTables);
    if (candidate.nestedLoops.empty())
      return; // placeholder for a loop of another kind
    unsigned decisionMaxDepth = pipelineLoopsValue;
    if (candidate.userPipelineIdx >= 0) {
      AffineForOp decisionUserLoop =
          candidate.nestedLoops[candidate.userPipelineIdx];
      candidate.taggedLoop = decisionUserLoop;
      recordFlattenedParents(decisionUserLoop, candidate.userPipelineIdx);
      emitRemark(decisionUserLoop.getLoc(),
                 "user pipeline: unrolling everything inside, " +
                     llvm::Twine(candidate.userPipelineIdx) +
                     " perfect parent(s) flattened into it");
      unrollInside(decisionUserLoop, symbolTables);
      // Promotion replaces the loop op; keep the node's handles
      // current (the parent's flatten step reads chain.front()).
      candidate.taggedLoop = promotePipelinedValue
                                 ? promoteNowOrLater(decisionUserLoop)
                                 : decisionUserLoop;
      candidate.nestedLoops[candidate.userPipelineIdx] = candidate.taggedLoop;
      return;
    }
    bool feasible = decisionMaxDepth > 0 && !candidate.pipelineOff;
    for (auto &decisionChildNode : candidate.childList)
      feasible &= decisionChildNode->constInside &&
                  decisionChildNode->maxPath <= decisionMaxDepth &&
                  !decisionChildNode->hasUserPipeline &&
                  !decisionChildNode->hasUserFixed;
    if (feasible) {
      AffineForOp decisionPipelineLoop = candidate.nestedLoops.back();
      candidate.taggedLoop = decisionPipelineLoop;
      markAutoPipelineTag(decisionPipelineLoop);
      // The do-while refusal (N96) is decided on the sub-loops before the
      // unroll below removes them.
      if (doWhileRefusalValue)
        candidate.doWhileParents = circt::hls_analysis::doWhileParents(
            decisionPipelineLoop, doWhileMinSubLoopTrip);
      unsigned decisionFlatParents =
          flattenableParents(llvm::ArrayRef(candidate.nestedLoops).drop_back(),
                             candidate.doWhileParents);
      if (decisionFlatParents + 1 < candidate.nestedLoops.size()) {
        candidate.flattenRefused = true;
        noteFlattenFailure(candidate.nestedLoops[candidate.nestedLoops.size() -
                                                 2 - decisionFlatParents]);
        emitRemark(candidate
                       .nestedLoops[candidate.nestedLoops.size() - 2 -
                                    decisionFlatParents]
                       .getLoc(),
                   "not flattened into the pipelined loop at " +
                       formatLocation(decisionPipelineLoop.getLoc()) +
                       ": its unrolled sub-loop subscripts the next "
                       "index of "
                       "this loop (Vitis 200-960, do-while "
                       "loop)");
      }
      recordFlattenedParents(decisionPipelineLoop, decisionFlatParents);
      // The pipeline's trip count: the chain members flattened into it.
      uint64_t decisionTripProduct = 1;
      for (AffineForOp member : llvm::ArrayRef(candidate.nestedLoops)
                                    .take_back(decisionFlatParents + 1))
        decisionTripProduct = clampedMultiply(
            decisionTripProduct, getConstantTripCount(member).value_or(1));
      emitRemark(decisionPipelineLoop.getLoc(),
                 "automatically set the pipeline for the loop (trip " +
                     (candidate.dynamic ? llvm::Twine("?")
                                        : llvm::Twine(decisionTripProduct)) +
                     ", " + llvm::Twine(decisionFlatParents) +
                     " perfect parent(s) flattened, " +
                     llvm::Twine(candidate.childList.size()) +
                     " inner loop(s) to unroll)");
      unrollInside(decisionPipelineLoop, symbolTables);
      candidate.taggedLoop = promotePipelinedValue
                                 ? promoteNowOrLater(decisionPipelineLoop)
                                 : decisionPipelineLoop;
      candidate.nestedLoops.back() = candidate.taggedLoop;
      return;
    }
    for (auto &constantTerm : candidate.childList)
      if (!constantTerm->throughCall)
        decide(*constantTerm, symbolTables);
    // Flattening of this (imperfect) loop into its single pipelined
    // child.
    if (candidate.childList.size() != 1)
      return;
    LoopNode &constantTerm = *candidate.childList.front();
    // An uncounted loop that is a perfect parent (not collapsed in
    // step 1) is flattened into its pipelined child as the counted
    // loop is through the collapse: its runtime bound is the
    // variable outermost bound the semi-perfect rule allows (N15: nc_f_u8 is
    // flattened like nc_f_int). A loop around it is not (c.dynamic).
    // Variable bounds that do not change over this loop's chain
    // flatten like constant ones; the outermost loop may have any
    // bound (the semi-perfect rule; boundInvariantIn). Only into a
    // syntactically perfect parent: an imperfect parent of a variable-trip
    // child is not flattened ([HLS 200-960]; auto_pipeline_siblings.mlir
    // dynamic_inner).
    Operation *outermost =
        candidate.nestedLoops.empty() ? nullptr : candidate.nestedLoops.front();
    bool perfectParent =
        outermost && !constantTerm.nestedLoops.empty() &&
        llvm::all_of(
            candidate.nestedLoops.back().getBody()->without_terminator(),
            [&](Operation &currentOperation) {
              return &currentOperation ==
                         constantTerm.nestedLoops.front().getOperation() ||
                     isMemoryEffectFree(&currentOperation);
            });
    bool nCounted = !candidate.dynamic || candidate.uncountedPerfect ||
                    (perfectParent &&
                     nestIsInvariantWithin(candidate.nestedLoops, outermost,
                                           /*skipFirst=*/true));
    bool cCounted = !constantTerm.dynamic ||
                    (perfectParent &&
                     nestIsInvariantWithin(constantTerm.nestedLoops, outermost,
                                           /*skipFirst=*/false));
    if (constantTerm.throughCall || constantTerm.nestedLoops.empty() ||
        !constantTerm.taggedLoop || !nCounted || !cCounted)
      return;
    if (constantTerm.nestedLoops.front()->getBlock() !=
        candidate.nestedLoops.back().getBody())
      return; // the child loop is conditional
    if (constantTerm.flattenRefused)
      return; // a loop between this one and the pipeline stays (N96)
    unsigned parentNodes =
        flattenableParents(candidate.nestedLoops, constantTerm.doWhileParents);
    if (parentNodes < candidate.nestedLoops.size()) {
      noteFlattenFailure(candidate.nestedLoops[candidate.nestedLoops.size() -
                                               1 - parentNodes]);
      emitRemark(
          candidate.nestedLoops[candidate.nestedLoops.size() - 1 - parentNodes]
              .getLoc(),
          "not flattened into the pipelined loop at " +
              formatLocation(constantTerm.taggedLoop.getLoc()) +
              ": its unrolled sub-loop subscripts the next index of "
              "this "
              "loop (Vitis 200-960, do-while loop)");
      // The perfect inner members below the refused loop still
      // collapse.
      recordFlattenedParents(constantTerm.taggedLoop, parentNodes);
      candidate.flattenRefused = true;
      return;
    }
    recordFlattenedParents(constantTerm.taggedLoop,
                           candidate.nestedLoops.size());
    candidate.taggedLoop = constantTerm.taggedLoop;
    candidate.doWhileParents = constantTerm.doWhileParents;
    emitRemark(candidate.nestedLoops.front().getLoc(),
               "flattening the loop (and " +
                   llvm::Twine(candidate.nestedLoops.size() - 1) +
                   " perfect inner loop(s)) into the pipelined "
                   "loop at " +
                   formatLocation(constantTerm.taggedLoop.getLoc()));
  }

  /// A runtime loop (N53) is pipelined under the test of an affine
  /// one: its own trip count does not matter, every loop inside it
  /// (callee loops included) must have a constant trip count with products <=
  /// T. An scf.for whose body is a perfect nest (isPerfectRuntimePair) is
  /// instead collapsed with it as a perfect affine parent is (step 1; a
  /// variable bound is allowed on the outermost loop of a flattened
  /// nest): the nest is decided as its inner chain and the runtime
  /// loop is flattened into that chain's pipeline (N53 (b)).
  /// Otherwise it is never flattened with another loop (its parent's
  /// trip count is unknown to it), and promoteOutOfPipeline, an affine
  /// transform, is not applied to it.
  void decideRuntime(LoopNode &candidate, SymbolTableCollection &symbolTables) {
    Operation *chosenLoopForPipeline = candidate.runtimeLoop;
    unsigned T = pipelineLoopsValue;
    if (hasUserPipelineTag(chosenLoopForPipeline)) {
      emitRemark(chosenLoopForPipeline->getLoc(),
                 "user pipeline of a runtime-trip loop: "
                 "unrolling everything inside");
      unrollInside(chosenLoopForPipeline, symbolTables);
      return;
    }
    if (candidate.perfectRuntime && T > 0) {
      LoopNode &constantTerm = *candidate.childList.front();
      decide(constantTerm, symbolTables);
      if (constantTerm.taggedLoop &&
          llvm::is_contained(constantTerm.nestedLoops,
                             constantTerm.taggedLoop)) {
        recordFlattenedParents(constantTerm.taggedLoop, 1);
        candidate.taggedLoop = constantTerm.taggedLoop;
        emitRemark(chosenLoopForPipeline->getLoc(),
                   "flattening the runtime-trip loop (perfect nest) "
                   "into the "
                   "pipelined loop at " +
                       formatLocation(constantTerm.taggedLoop.getLoc()));
      }
      return;
    }
    bool feasible = T > 0 && !candidate.pipelineOff;
    for (auto &constantTerm : candidate.childList)
      feasible &= constantTerm->constInside && constantTerm->maxPath <= T &&
                  !constantTerm->hasUserPipeline && !constantTerm->hasUserFixed;
    if (feasible) {
      markAutoPipelineTag(chosenLoopForPipeline);
      unsigned unrolledRegion =
          unrollInside(chosenLoopForPipeline, symbolTables);
      emitRemark(chosenLoopForPipeline->getLoc(),
                 "automatically set the pipeline for the runtime-trip loop "
                 "(unrolled " +
                     llvm::Twine(unrolledRegion) + " inner loop(s))");
      return;
    }
    for (auto &constantTerm : candidate.childList)
      if (!constantTerm->throughCall)
        decide(*constantTerm, symbolTables);
  }

  /// The functions with a body, every caller before its callees (reverse
  /// post-order of the call graph; a call cycle is cut where the walk meets
  /// it). With calls kept (`#pragma HLS inline off`, W3), Vitis decides a
  /// caller loop against the callee's loops as they are written,
  /// before the callee's own decision changes them (VITIS_NOTES.md N14 R7:
  /// `inl_f2` a 16-trip callee loop is unrolled into the pipelined
  /// caller loop; corpus attn_breakdown_op1 and kernel
  /// w3h_cb_nest256: a callee nest of 8 x 8 x 4 trips keeps the 8-trip caller
  /// loop sequential, the callee pipelines its own flattened
  /// loop). Deciding the callee first would unroll its inner loops
  /// and let the caller pass the trip-count test on what is left.
  static llvm::SmallVector<func::FuncOp>
  callersFirst(ModuleOp moduleOp, SymbolTableCollection &symbolTables) {
    llvm::SmallVector<func::FuncOp> postOrder;
    DenseSet<Operation *> visited;
    std::function<void(func::FuncOp)> visit = [&](func::FuncOp fn) {
      if (!visited.insert(fn.getOperation()).second)
        return;
      fn.walk([&](CallOpInterface callSite) {
        auto calleeFunction = dyn_cast_or_null<func::FuncOp>(
            callSite.resolveCallableInTable(&symbolTables));
        if (calleeFunction && !calleeFunction.isExternal())
          visit(calleeFunction);
      });
      postOrder.emplace_back(fn);
    };
    for (auto fn : moduleOp.getOps<func::FuncOp>())
      if (!fn.isExternal())
        visit(fn);
    return llvm::SmallVector<func::FuncOp>(llvm::reverse(postOrder));
  }

  /// Whether `fn`, or a function it calls, still holds a loop.
  static bool hasLoops(func::FuncOp fn, SymbolTableCollection &symbolTables,
                       SmallPtrSetImpl<Operation *> &stack) {
    if (!stack.insert(fn.getOperation()).second)
      return false; // a call cycle: counted where it started
    bool matchedGroups = false;
    fn.walk([&](Operation *currentOperation) {
      if (isa<LoopLikeOpInterface>(currentOperation)) {
        matchedGroups = true;
        return WalkResult::interrupt();
      }
      if (auto callSite = dyn_cast<CallOpInterface>(currentOperation))
        if (auto calleeFunction = dyn_cast_or_null<func::FuncOp>(
                callSite.resolveCallableInTable(&symbolTables)))
          if (!calleeFunction.isExternal() &&
              hasLoops(calleeFunction, symbolTables, stack)) {
            matchedGroups = true;
            return WalkResult::interrupt();
          }
      return WalkResult::advance();
    });
    stack.erase(fn.getOperation());
    return matchedGroups;
  }

  /// Cycles one call of the loop-free `fn` holds its instance: its
  /// accesses to each memory (an argument, a local array, a global), two per
  /// cycle (a memory's two ports), the busiest memory deciding; at least 1. A
  /// nested call counts with its own occupancy.
  static unsigned occupancy(func::FuncOp fn,
                            SymbolTableCollection &symbolTables,
                            SmallPtrSetImpl<Operation *> &stack) {
    return circt::hls_analysis::estimateCallOccupancy(fn, symbolTables, stack);
  }

  /// The call boundary after the decisions (VITIS_NOTES.md N14 R7): a
  /// loop that is not pipelined and calls a kept function that still
  /// has loops gets `hls.call_boundary` (Vitis pipelines the callee's loops in
  /// the callee and leaves the caller loop sequential:
  /// w3h_cb_nest256, attn_breakdown_op1 `VITIS_LOOP_232_1`); a call inside a
  /// pipelined loop gets `hls.call_occupancy` (its callee is
  /// loop-free by then, R7) and `hls.call_depth` (the states of one
  /// call, for calls that share an instance; N14 R2 in a pipelined
  /// loop).
  static void markCallBoundaries(ModuleOp moduleOp,
                                 SymbolTableCollection &symbolTables,
                                 call_depth::PipelineModel &depthModel) {
    // A library core with loops of its own (VITIS_NOTES N169): the
    // loop around the call stays sequential like one around a kept
    // callee with loops (--convert-affine-to-loopschedule does not pipeline
    // it).
    moduleOp.walk([&](Operation *currentOperation) {
      if (!hasLoopingLibraryCall(currentOperation, symbolTables))
        return;
      auto chosenLoopForPipeline =
          currentOperation->getParentOfType<AffineForOp>();
      if (!chosenLoopForPipeline ||
          chosenLoopForPipeline->hasAttr(kLoopPipelineAttr) ||
          chosenLoopForPipeline->hasAttr(kLoopCallBoundaryAttr))
        return;
      chosenLoopForPipeline->setAttr(
          kLoopCallBoundaryAttr,
          StringAttr::get(currentOperation->getContext(),
                          libraryCallName(currentOperation, symbolTables)));
    });
    moduleOp.walk([&](CallOpInterface callSite) {
      auto calleeFunction = dyn_cast_or_null<func::FuncOp>(
          callSite.resolveCallableInTable(&symbolTables));
      if (!calleeFunction || calleeFunction.isExternal())
        return;
      // A call in a pipelined runtime loop (N53) is a call in a
      // pipelined loop; any other runtime loop is left as
      // it was (the affine.for around it, if any, is the one marked).
      Operation *chosenLoopForPipeline =
          callSite->getParentOfType<AffineForOp>();
      if (auto innerLoop = callSite->getParentOfType<LoopLikeOpInterface>();
          innerLoop && isDynamicLoop(innerLoop) &&
          innerLoop->hasAttr(kLoopPipelineAttr))
        chosenLoopForPipeline = innerLoop;
      if (!chosenLoopForPipeline)
        return;
      OpBuilder passBuilder(callSite.getContext());
      SmallPtrSet<Operation *, 8> stack;
      if (chosenLoopForPipeline->hasAttr(kLoopPipelineAttr)) {
        unsigned occ = occupancy(calleeFunction, symbolTables, stack);
        callSite->setAttr(kCallOccupancyAttr,
                          passBuilder.getI64IntegerAttr(occ));
        if (std::optional<unsigned> depthValue =
                depthModel.recursionDepth(calleeFunction, symbolTables)) {
          callSite->setAttr(kCallDepthAttr, passBuilder.getI64IntegerAttr(
                                                std::max(*depthValue, occ)));
          // The model's own depth, when the occupancy raised it (only then
          // can a smaller occupancy after the partitions lower it again).
          if (*depthValue < occ)
            callSite->setAttr(circt::hls_analysis::kCallDepthEstimateAttr,
                              passBuilder.getI64IntegerAttr(*depthValue));
        }
        return;
      }
      if (!chosenLoopForPipeline->hasAttr(kLoopCallBoundaryAttr) &&
          hasLoops(calleeFunction, symbolTables, stack))
        chosenLoopForPipeline->setAttr(
            kLoopCallBoundaryAttr,
            passBuilder.getStringAttr(calleeFunction.getSymName()));
    });
  }

  void runOnOperation() override {
    ModuleOp moduleOp = getOperation();
    const circt::hlsest::Config &cfg = circt::hlsest::Config::get();
    const circt::hlsest::PipelineDecisionConfig &pd =
        cfg.tool.hls.pipelineDecision;
    if (pd.flattenAcrossCalls) {
      // A documented assumption of the Vitis policy (a loop is never
      // flattened into a pipelined loop of a callee); no alternative
      // exists.
      moduleOp.emitError(
          "--auto-pipeline-unroll: "
          "tool.hls.pipeline_decision.flatten_across_calls = true "
          "is not implemented");
      return signalPassFailure();
    }
    // An option given explicitly, else the configuration
    // (tool.hls.options.pipeline_loops, tool.hls.pipeline_decision.*,
    // run.clock_ns, tool.hls.timing_margin).
    circt::hlsest::PipelineDecisionOptions pipelineOptions;
    pipelineOptions.pipelineLoops = circt::hlsest::resolveOption<unsigned>(
        pipelineLoops,
        static_cast<unsigned>(cfg.tool.hls.options.pipelineLoops));
    pipelineOptions.promotePipelined =
        circt::hlsest::resolveOption(promotePipelined, pd.promotePipelined);
    pipelineOptions.floatLoadsPerfect =
        circt::hlsest::resolveOption(floatLoadsPerfect, pd.floatLoadsPerfect);
    pipelineOptions.callDepthBudgetNs = callDepthBudgetNs(cfg);
    if (emitRemarks)
      pipelineOptions.remark = [](Location sourceLoc, const llvm::Twine &msg) {
        mlir::emitRemark(sourceLoc) << msg;
      };
    // The decision is the configuration's PipelinePolicy (builtin
    // vitis-pipeline-loops: runDecision below).
    circt::hlsest::ConfigDiagnostics diag;
    std::unique_ptr<circt::hlsest::PipelinePolicy> policy =
        circt::hlsest::PluginRegistry<circt::hlsest::PipelinePolicy>::instance()
            .create(pd.policy, cfg, diag);
    if (!policy) {
      InFlightDiagnostic depthValue =
          moduleOp.emitError("--auto-pipeline-unroll: ");
      llvm::interleave(diag.errors, depthValue, "; ");
      return signalPassFailure();
    }
    if (failed(policy->decide(moduleOp, pipelineOptions)))
      return signalPassFailure();
    if (cfg.tool.hls.folding.constantGlobalLoadsAfterUnroll)
      foldConstantLoad(moduleOp);
    // The guards of the unrolled copies that can never (or always) hold
    // (VITIS_NOTES N89): only copy 0 of `if (k + j * N == 0)` can run.
    if (pd.foldUnrolledGuards) {
      circt::hls_analysis::FoldedGuards flagValue =
          circt::hls_analysis::foldConstantAffineIfs(moduleOp);
      LLVM_DEBUG(llvm::dbgs() << "folded " << flagValue.folded << " guard(s) ("
                              << flagValue.scfIfs << " scf.if), pinned "
                              << flagValue.pinnedOperands << " operand(s)\n");
    }
    // An unrolled copy's product by its counter 0 is 0 (W9r23 review D12).
    if (pd.foldUnrolledZeroProducts) {
      unsigned candidate =
          circt::hls_analysis::foldUnrolledZeroProducts(moduleOp);
      (void)candidate;
      LLVM_DEBUG(llvm::dbgs()
                 << "folded " << candidate << " zero product(s)\n");
    }
  }

  /// The Vitis decision procedure (the builtin PipelinePolicy
  /// vitis-pipeline-loops): user unrolls, then per function the pipelined
  /// loops, the unrolled and the flattened ones, then the call boundaries
  /// and the port-bound arguments.
  LogicalResult
  runDecision(ModuleOp moduleOp,
              const circt::hlsest::PipelineDecisionOptions &outputValue) {
    SymbolTableCollection symbolTables;
    pipelineLoopsValue = outputValue.pipelineLoops;
    promotePipelinedValue = outputValue.promotePipelined;
    floatLoadsPerfectValue = outputValue.floatLoadsPerfect;
    doWhileRefusalValue = circt::hlsest::Config::get()
                              .tool.hls.pipelineDecision.doWhileFlattenRefusal;
    doWhileMinSubLoopTrip = static_cast<uint64_t>(
        circt::hlsest::Config::get()
            .tool.hls.pipelineDecision.doWhileMinSubLoopTrip);
    partialUnrollRuntimeValue =
        circt::hlsest::Config::get()
            .tool.hls.pipelineDecision.partialUnrollRuntimeLoops;
    remarkFn = outputValue.remark;

    // Idempotency: drop the tags of a previous run.
    moduleOp.walk([&](Operation *currentOperation) {
      if (isDynamicLoop(currentOperation)) {
        if (marksAutoPipelineTag(currentOperation->getAttr(kLoopPipelineAttr)))
          currentOperation->removeAttr(kLoopPipelineAttr);
        currentOperation->removeAttr(kLoopAutoUnrolledAttr);
      }
    });
    moduleOp.walk([&](AffineForOp chosenLoopForPipeline) {
      if (marksAutoPipelineTag(
              chosenLoopForPipeline->getAttr(kLoopPipelineAttr)))
        chosenLoopForPipeline->removeAttr(kLoopPipelineAttr);
      chosenLoopForPipeline->removeAttr(kLoopFlattenedParentsAttr);
      chosenLoopForPipeline->removeAttr(kLoopFlattenRefusedAttr);
      chosenLoopForPipeline->removeAttr(kLoopAutoUnrolledAttr);
      chosenLoopForPipeline->removeAttr(kLoopCallBoundaryAttr);
    });
    moduleOp.walk([&](CallOpInterface callSite) {
      callSite->removeAttr(kCallOccupancyAttr);
      callSite->removeAttr(kCallDepthAttr);
      callSite->removeAttr(circt::hls_analysis::kCallDepthEstimateAttr);
    });
    for (auto containingFunction : moduleOp.getOps<func::FuncOp>())
      containingFunction->removeAttr(circt::hls_analysis::kPortBoundArgsAttr);

    for (auto containingFunction : moduleOp.getOps<func::FuncOp>())
      if (!containingFunction.isExternal())
        applyUserUnrolls(containingFunction);

    // LLVM LICM before the decision (VITIS_NOTES N166 (a)): a loop
    // that only stores one invariant element (cgeist carries the accumulator in
    // an iter_arg) stores it once after the loop, and that store
    // forwards to the loads after it and dies under the next store.
    if (circt::hlsest::Config::get()
            .tool.hls.pipelineDecision.promotedStoreCleanup) {
      llvm::SmallVector<Value> forwarded;
      forwardedMemories = &forwarded;
      for (auto containingFunction : moduleOp.getOps<func::FuncOp>())
        if (!containingFunction.isExternal())
          sinkFunctionDeadStores(containingFunction);
      forwardedMemories = nullptr;
      eraseUnusedArrays(moduleOp, forwarded);
    }

    for (func::FuncOp containingFunction :
         callersFirst(moduleOp, symbolTables)) {
      HoistModel licm(floatLoadsPerfectValue);
      LoopForest forest(licm);
      // Top-level loops of this function (affine.for and runtime loops, in
      // program order); callee loops are decided with their own function
      // and only take part in the feasibility test.
      llvm::SmallVector<Operation *, 8> roots;
      containingFunction.getBody().walk<WalkOrder::PreOrder>(
          [&](Operation *currentOperation) {
            if (!isa<AffineForOp>(currentOperation) &&
                !isDynamicLoop(currentOperation))
              return WalkResult::advance();
            roots.emplace_back(currentOperation);
            return WalkResult::skip();
          });
      llvm::SmallVector<std::unique_ptr<LoopNode>> nodes;
      SmallPtrSet<Operation *, 4> callStackSet;
      callStackSet.insert(containingFunction.getOperation());
      for (Operation *chosenLoopForPipeline : roots) {
        if (auto affineLoop = dyn_cast<AffineForOp>(chosenLoopForPipeline))
          nodes.emplace_back(
              forest.build(affineLoop, /*viaCall=*/false, callStackSet));
        else
          nodes.emplace_back(forest.buildRuntime(
              chosenLoopForPipeline, /*viaCall=*/false, callStackSet));
      }
      for (auto &nodeState : nodes)
        decide(*nodeState, symbolTables);
      promotePending(containingFunction);
    }
    call_depth::PipelineModel depthModel(
        outputValue.callDepthBudgetNs, circt::hlsest::Config::get().scheduling);
    markCallBoundaries(moduleOp, symbolTables, depthModel);
    markPortBoundArgs(moduleOp);
    return success();
  }

  /// `hls.port_bound_args` on every function whose memref arguments name an
  /// array that crosses a module instantiated at more than one place
  /// (VITIS_NOTES.md N14 R6; W3 review D2: w3rev_k3 / k3b / w3fx_d2_conc).
  /// MemrefBankClassification gives such an argument two ports instead of
  /// the replicable pool, so the callee's loop II rises as in Vitis
  /// (rd3 II 2). The instances are counted after the unroll decisions, on the
  /// final call sites.
  static void markPortBoundArgs(ModuleOp moduleOp) {
    using namespace circt::hls_analysis;
    InstanceModel model = computeInstances(moduleOp);
    OpBuilder passBuilder(moduleOp.getContext());
    for (auto fn : moduleOp.getOps<func::FuncOp>()) {
      if (fn.isExternal())
        continue;
      llvm::SmallVector<int64_t> bound;
      for (BlockArgument arg : fn.getArguments())
        if (isa<BaseMemRefType>(arg.getType()) &&
            model.argReachesSharedModule(fn, arg.getArgNumber()))
          bound.emplace_back(arg.getArgNumber());
      if (!bound.empty())
        fn->setAttr(kPortBoundArgsAttr, passBuilder.getI64ArrayAttr(bound));
    }
  }
};

/// vitis-pipeline-loops: Vitis' config_compile -pipeline_loops decision
/// (VITIS_NOTES N3), the code of this pass.
class VitisPipelinePolicy : public circt::hlsest::PipelinePolicy {
public:
  llvm::StringRef name() const override { return "vitis-pipeline-loops"; }
  LogicalResult decide(ModuleOp moduleOp,
                       const circt::hlsest::PipelineDecisionOptions
                           &pipelineOptions) const override {
    PipelineDecisionPass impl;
    return impl.runDecision(moduleOp, pipelineOptions);
  }
};

} // namespace

void circt::hlsest::builtin::registerPipelinePolicies() {
  circt::hlsest::PluginRegistry<circt::hlsest::PipelinePolicy>::instance().add(
      "vitis-pipeline-loops",
      "Vitis config_compile -pipeline_loops: pipeline a loop whose "
      "nested "
      "trip-count products are all <= pipeline_loops, unroll inside, flatten "
      "perfect parents (VITIS_NOTES N3)",
      [] { return std::make_unique<VitisPipelinePolicy>(); }, "builtin");
}

namespace circt::hls_analysis {

std::unique_ptr<mlir::Pass> createAutoPipelineUnrollPass() {
  return std::make_unique<PipelineDecisionPass>();
}

void registerAutoPipelineUnrollPass() {
  ::mlir::PassRegistration<PipelineDecisionPass>();
}

} // namespace circt::hls_analysis
