//===- AffineToLoopSchedule.cpp--------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// MODIFIED VERSION. Changes relative to the original conversion:
//
//   1. affine.apply support: AffineApplyOp is now marked illegal in
//      lowerAffineStructures(), so the AffineApplyLowering pattern from
//      AffineToStandard (already pulled in via
//      populateAffineToStdConversionPatterns) expands it into arith ops
//      before scheduling. The scheduler therefore never sees affine.apply.
//
//   2. Expanded arithmetic coverage in populateOperatorTypes():
//      - MulIOp / DivSIOp / DivUIOp / RemSIOp / RemUIOp -> "multicycle".
//        (div/rem appear when affine.apply maps containing floordiv/mod are
//        expanded, e.g. the delinearization introduced by loop coalescing.)
//      - SelectOp, SubIOp, AndI/OrI/XOrI, shifts, trunc/ext, etc. -> "comb".
//        These also appear in floordiv/mod expansion (cmpi + select fixups).
//      - The original dead `.Case<AddIOp, CmpIOp>` (unreachable because both
//        ops matched the first Case) has been removed.
//
//   3. Nested loop support, in two layers:
//      a) Perfectly nested bands are coalesced (flattened) into a single
//         loop with affine::coalesceLoops() before any analysis runs. The
//         delinearization it introduces (floordiv/mod affine.apply ops) is
//         handled by (1) and (2).
//      b) Any remaining nesting (imperfect nests, or bands whose inner
//         bounds depend on outer IVs so coalescing fails) falls back to
//         pipelining each *innermost* loop in place. Outer affine.for loops
//         are left intact as sequential control around the pipeline; the
//         pipeline op is not IsolatedFromAbove, so it may freely reference
//         outer induction variables and loop-invariant values.
//
//   4. Scalability for unrolled bodies (option `fast-threshold`, default 150):
//      a loop whose modulo problem holds more resource-limited (memory)
//      operations than the threshold is scheduled by a greedy resource-bound
//      modulo list scheduler (II = max(ResMinII, recurrence-feasible II),
//      ASAP placement in dependence order against a modulo reservation
//      table, II bumped when an op cannot be placed) instead of the
//      simplex-based ModuloSimplexScheduler, which re-solves an LP per
//      resource-limited op and is cubic in the body size. Small bodies keep
//      the simplex scheduler. `fast-threshold=0` uses the greedy scheduler for
//      every loop. A problem with more operations than `fast-ops-threshold`
//      (default 4096) goes to the greedy scheduler too, however few memory
//      operations it has: the simplex tableau is dense in the operations and
//      the dependences.
//
//   5. Pre-scheduling CSE (option `cse`, default on): duplicated
//      side-effect-free ops (the per-access index arithmetic left by affine
//      map expansion) are merged before the problem is built. Memory ops are
//      never merged, so the port demand seen by --bram-analysis is unchanged.
//
//===----------------------------------------------------------------------===//

#include "../Plugins/Builtin/Builtins.h"
#include "circt/Dialect/Resource/Plugins/MemoryInterfaces.h"
#include "circt/Dialect/Resource/Passes/StoragePragmas.h"
#include "circt/Dialect/Resource/Plugins/Registry.h"
#include "circt/Dialect/Resource/Plugins/Scheduling.h"
#include "circt/Dialect/Resource/Config/ConfigUtils.h"
#include "circt/Dialect/Resource/Passes/FoldUnrolledGuards.h"
#include "circt/Dialect/Resource/Passes/FloatOps.h"
#include "circt/Dialect/Resource/Passes/AffineToLoopScheduleModified.h"
#include "circt/Dialect/Resource/Passes/CallInstances.h"
#include "circt/Dialect/Resource/Passes/MemrefBankClassification.h"
#include "circt/Dialect/Resource/Passes/PartitionLayout.h"
#include "circt/Dialect/Resource/Passes/MemoryRecurrences.h"
#include "circt/Dialect/Resource/Passes/StreamFifos.h"
#include "circt/Dialect/Resource/Passes/LoopPragmas.h"
#include "circt/Dialect/Resource/Passes/CyclicSchedulingAnalysisModified.h"
#include "circt/Analysis/DependenceAnalysis.h"
#include "circt/Dialect/LoopSchedule/LoopScheduleOps.h"
#include "circt/Dialect/Resource/HLS/HLSDialect.h"
#include "circt/Scheduling/Algorithms.h"
#include "circt/Scheduling/Problems.h"
#include "circt/Dialect/Resource/HLS/HLSOps.h"
#include "mlir/Conversion/AffineToStandard/AffineToStandard.h"
#include "mlir/Dialect/Affine/Analysis/AffineAnalysis.h"
#include "mlir/Dialect/Affine/Analysis/LoopAnalysis.h"
#include "mlir/Dialect/Affine/IR/AffineMemoryOpInterfaces.h"
#include "mlir/Dialect/Affine/IR/AffineOps.h"
#include "mlir/Dialect/LLVMIR/LLVMDialect.h"
#include "mlir/Dialect/Affine/IR/AffineValueMap.h"
#include "mlir/Interfaces/CallInterfaces.h"
#include "mlir/Interfaces/ViewLikeInterface.h"
#include "mlir/Dialect/Affine/LoopUtils.h"
#include "circt/Dialect/Resource/Passes/AffineUnroll.h"
#include "mlir/Dialect/Affine/Utils.h"
#include "mlir/Dialect/Arith/IR/Arith.h"
#include "mlir/Dialect/ControlFlow/IR/ControlFlow.h"
#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/Dialect/MemRef/IR/MemRef.h"
#include "mlir/Dialect/LLVMIR/LLVMTypes.h"
#include "mlir/Dialect/SCF/IR/SCF.h"
#include "mlir/Dialect/Math/IR/Math.h"
#include "mlir/IR/BuiltinDialect.h"
#include "mlir/IR/Dominance.h"
#include "mlir/IR/IRMapping.h"
#include "mlir/IR/ImplicitLocOpBuilder.h"
#include "mlir/IR/OperationSupport.h"
#include "mlir/Interfaces/SideEffectInterfaces.h"
#include "mlir/Pass/Pass.h"
#include "llvm/ADT/StringSet.h"
#include "mlir/Transforms/DialectConversion.h"
#include "mlir/Transforms/RegionUtils.h"
#include "llvm/ADT/DenseSet.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/ADT/TypeSwitch.h"
#include "llvm/Support/Debug.h"
#include <cassert>
#include <limits>
#include <queue>
#include <map>
#include <set>
#include <unordered_map>
#include <thread>
#include <mlir/IR/IntegerSet.h>

#define DEBUG_TYPE "affine-to-loopschedule"

#include "llvm/Support/CommandLine.h"
#include "llvm/ADT/MapVector.h"

// MODIFIED (T4): a call inside a loop body (a math-library function the
// frontend left as func.call: tanh, nanf, ...) has no operator type, so its
// loop stays a sequential affine.for (T3). With this option >= 0 such a call
// gets an operator type of that latency instead, so the loop is pipelined
// like any other. Only calls without memref operands or results (their memory
// effects would be invisible to the dependence analysis). Off by default
// (-1): it changes the estimate of the designs that call a math function in a
// loop (forgebench Llama_GPT_module, gpt_transformer_p1, spector_hls normals),
// and the default pipeline's numbers are Peter's call (MEMOS.md M5).
static llvm::cl::opt<int> loopScheduleCallLatency(
    "loopschedule-call-latency",
    llvm::cl::desc("--convert-affine-to-loopschedule: operator latency for a "
                   "func.call without memref operands inside a loop body "
                   "(-1: leave that loop sequential)"),
    llvm::cl::init(-1));
// W3 (VITIS_NOTES.md N14 R2 / R6 / R7): a call to a function defined in the
// module (a callee kept because of `#pragma HLS inline off`, or one the
// inliner could not inline) inside a pipelined loop is an operation of the
// loop in Vitis: the loop is pipelined around it, the callee's accesses go
// through the instance's port (no replication of the caller's arrays for
// them), and calls of one iteration that share an instance (a common array
// argument, a value dependence, an allocation limit) are serialized, which
// raises the II (inl_e3: two `get2(buf, i)` calls, II 4; inl_c4: three
// independent `h(x)` calls, three instances, II 1). Such a call gets an
// operator type whose latency is the occupancy --auto-pipeline-unroll
// estimated for it (`hls.call_occupancy`: the callee's accesses to its
// busiest memory, two per cycle; inl_f2: II 8), or this option's latency
// when the call has no estimate, whatever its operands; -1 leaves loops with
// such calls sequential as before W3. A loop around a call whose callee
// still has loops is never pipelined (`hls.call_boundary`).
static llvm::cl::opt<int> loopScheduleKeptCallLatency(
    "loopschedule-kept-call-latency",
    llvm::cl::desc("--convert-affine-to-loopschedule: operator latency for a "
                   "func.call to a function defined in the module inside a "
                   "loop body (-1: leave that loop sequential)"),
    llvm::cl::init(1));
// https://circt.llvm.org/docs/Scheduling/
namespace circt {
// The generated base class takes an AffineToLoopScheduleOptions struct, which
// the DECL block defines; the public header declares it in circt::hls_analysis,
// so declare it here in circt as well for the DEF block.
#define GEN_PASS_DECL_AFFINETOLOOPSCHEDULE
#define GEN_PASS_DEF_AFFINETOLOOPSCHEDULE
#include "circt/Conversion/Passes.h.inc"
} // namespace circt

using namespace mlir;
using namespace mlir::arith;
using namespace mlir::memref;
using namespace mlir::scf;
using namespace mlir::func;
using namespace mlir::affine;
using namespace circt;
using namespace circt::analysis;
using namespace circt::scheduling;
using namespace circt::loopschedule;
using namespace circt::hls_analysis;

namespace {


struct AffineToLoopSchedule
    : public circt::impl::AffineToLoopScheduleBase<AffineToLoopSchedule> {
  // MODIFIED (T7): explicit copy constructor (clonePass), since Statistic
  // members are not copyable; the copy starts with fresh counters.
  AffineToLoopSchedule() = default;
  AffineToLoopSchedule(const AffineToLoopSchedule &other)
      : circt::impl::AffineToLoopScheduleBase<AffineToLoopSchedule>(other) {}

  void unrollInnerReductions();
  void runOnOperation() override;

private:
  /// tool.hls.middle_end.gvn_memref_loads (set in runOnOperation).
  bool gvnMemrefLoads = true;
  ModuloProblem getModuloProblem(CyclicProblem &prob);
  LogicalResult
  lowerAffineStructures(MemoryDependenceAnalysis &dependenceAnalysis);

  // MODIFIED: these now operate on a single (innermost) loop instead of a
  // perfectly nested band, since nests are either coalesced into one loop
  // up front, or only their innermost loops are pipelined in place.
  // MODIFIED (O72): `loop` is an innermost affine.for or a pipelined
  // runtime-trip scf.for (isScheduledRuntimeFor, VITIS_NOTES.md N53).
  LogicalResult populateOperatorTypes(Operation *loop, ModuloProblem &problem,
                                      const BRAMClassification &bramClass);
  
  LogicalResult solveSchedulingProblem(Operation *loop,
                                       ModuloProblem &problem);
  LogicalResult createLoopSchedulePipeline(Operation *loop,
                                           ModuloProblem &problem);
  /// Schedules one loop and replaces it by its pipeline; false leaves it
  /// sequential, failure fails the pass.
  FailureOr<bool> pipelineLoop(Operation *loop,
                               const BRAMClassification &bramClass,
                               InnermostLoopDependenceAnalysis &dependenceAnalysis);

  // MODIFIED: pre-analysis structural transform. Flattens perfectly nested
  // bands into single loops where legal.
  void coalescePerfectNests();
  // MODIFIED: one memref.get_global per global symbol in the function, at
  // its entry, so that the global is one root memref (isRootMemref).
  void uniqueGlobalRefs();
  void sinkFlattenedParentCode();
  void sinkTrailingParentCode(AffineForOp c, ArrayRef<AffineForOp> chain);

  // MODIFIED: pre-analysis LICM on the loops about to be pipelined (after
  // coalescing). Moves loop-invariant pure ops and loop-invariant affine
  // loads from a memref the loop never writes to just before the loop.
  void hoistInvariantLoads();
  void tagMemoryRecurrences();
  int64_t nextLaneRecurrenceId = 0;
  int64_t recurrenceLatency(Operation *op) const;
  struct PromotedElementRecurrence {
    int64_t chain = 0;      ///< latency from the iter_arg to its yield
    unsigned multiCycle = 0; ///< multi-cycle operations on that path
    unsigned iterArg = 0;
  };
  /// Which iter_args promotedElementRecurrence looks at, and which of their
  /// paths count.
  struct RegisterCycleRules {
    bool promotedChains = false; ///< N160: promoted, >= 2 multi-cycle ops
    bool f64Chains = false;      ///< N160 (b): any iter_arg, an f64 op
  };
  std::optional<PromotedElementRecurrence>
  promotedElementRecurrence(Operation *loop,
                            RegisterCycleRules rules) const;
  void cleanupRedundantAccesses();
  void mergeIfElseAccesses();
  void mergeConditionalLoads();

  CyclicSchedulingAnalysis *schedulingAnalysis;

  // The scheduling plugins of this run (scheduling.*, hls-doc/plugins.md),
  // and the memory models that give each bank its port pools
  // (tool.hls.memory_architecture, tool.backend.storage_selector).
  std::unique_ptr<circt::hlsest::OperatorTimingModel> timingModel;
  std::unique_ptr<circt::hlsest::DependenceModel> dependenceModel;
  std::unique_ptr<circt::hlsest::ModuloScheduler> moduloScheduler;
  std::unique_ptr<circt::hlsest::SequentialScheduler> sequentialScheduler;
  std::unique_ptr<circt::hlsest::Binder> binder;
  std::unique_ptr<circt::hlsest::MemoryArchitecturePolicy> memoryPolicy;
  std::unique_ptr<circt::hlsest::StorageSelector> storageSelector;
  circt::hlsest::SchedulingContext schedulingContext;
  bool emitDetail = false;
  LogicalResult createPlugins();

  // MODIFIED (T7): the work of the memory dependence analysis
  // (InnermostLoopDependenceAnalysis), for --mlir-pass-statistics.
  Statistic numDepPairs{this, "dependence-pairs",
                        "Same-memref access pairs the memory dependence "
                        "analysis enumerated"};
  Statistic numDepTests{this, "dependence-tests",
                        "Dependence tests it ran (memo misses)"};
  Statistic numDeps{this, "dependences", "Memory dependences it recorded"};

  // MODIFIED (T7): schedule reuse between loops with identical scheduling
  // problems (user-unrolled copies of a pipelined loop); see
  // scheduleSignature.
  Option<bool> reuseSchedules{
      *this, "reuse-schedules",
      llvm::cl::desc("Give a loop whose scheduling problem is identical to an "
                     "already scheduled loop's (same operations in the same "
                     "order, operator latencies, resource limits and sharing, "
                     "dependences and distances) that loop's II and start "
                     "times instead of solving it again. Both schedulers are "
                     "deterministic functions of these inputs, so the result "
                     "is the same."),
      llvm::cl::init(true)};
  Option<bool> userIITarget{
      *this, "user-ii-target",
      llvm::cl::desc("Schedule a loop with a user `pipeline II=N` (N > 1) at "
                     "N when it could start more often: N is Vitis' target "
                     "II, and the RAM_1WNR copies are sized at the final "
                     "II."),
      llvm::cl::init(true)};
  Option<bool> hoistPastCalls{
      *this, "hoist-past-calls",
      llvm::cl::desc("With hoist-invariant: a memref passed to some call is "
                     "still hoisted from when the loop contains no call (a "
                     "callee can write it only while a call runs); off: any "
                     "call taking it anywhere in the function pins its "
                     "loads."),
      llvm::cl::init(true)};
  Option<bool> hoistConditional{
      *this, "hoist-conditional-invariant",
      llvm::cl::desc("With hoist-invariant: also hoist a loop-invariant "
                     "affine.load nested in an if of the loop body (Vitis' "
                     "LICM speculates guarded invariant loads)."),
      llvm::cl::init(true)};
  Option<bool> sinkParentCode{
      *this, "sink-flattened-parent-code",
      llvm::cl::desc("Move the straight-line code of the loops a pipelined "
                     "loop is flattened with (hls.flattened_parents) into "
                     "the pipelined body under a first-iteration guard: "
                     "Vitis allocates its ports in the pipeline "
                     "(VITIS_NOTES N65)"),
      llvm::cl::init(true)};
  Option<bool> sinkParentTrailingCode{
      *this, "sink-flattened-parent-trailing-code",
      llvm::cl::desc("Move the straight-line code after the child loop of "
                     "a parent flattened into a pipelined loop into the "
                     "pipelined body under a last-iteration guard "
                     "(VITIS_NOTES N97 (b))"),
      llvm::cl::init(true)};
  Option<bool> mergeIfElse{
      *this, "merge-if-else-accesses",
      llvm::cl::desc("Before the redundant-access cleanup, hoist a load both "
                     "arms of an if/else make of one address above the if, "
                     "and sink a store both arms make to one address below "
                     "it as one store of the value the if yields (Vitis "
                     "SimplifyCFG / InstCombine): the pair counts as one "
                     "access per iteration for ports and replication."),
      llvm::cl::init(true)};
  Option<bool> trackGlobals{
      *this, "track-globals",
      llvm::cl::desc("The redundant-access cleanup, the invariant-load "
                     "hoist and the store forwarding treat a global array "
                     "like a local one (its one memref.get_global per "
                     "function is the root memref; every call is a barrier "
                     "for it): Vitis' LLVM GVN / LICM make no difference "
                     "between them (ECG_Classifier baseline conv1d_2b: the "
                     "read-modify-writes of a global accumulator merge, "
                     "II 1)."),
      llvm::cl::init(true)};
  Option<bool> gvnConditionalLoads{
      *this, "gvn-conditional-loads",
      llvm::cl::desc("Before the redundant-access cleanup, replace the loads "
                     "of one address made in one block and in the ifs nested "
                     "in it, with no write of the memref between them, by one "
                     "load before the first (Vitis GVN load PRE: one read per "
                     "path, so one per iteration; W9 round 8 review, kernels "
                     "w9r8f_pr1 / pr2 / pr3)."),
      llvm::cl::init(true)};
  Option<bool> verifyScheduleReuse{
      *this, "verify-schedule-reuse",
      llvm::cl::desc("With reuse-schedules: solve every reused loop anyway, "
                     "keep the solved schedule and warn if it differs from "
                     "the reused one."),
      llvm::cl::init(false)};
  Statistic numSchedulesSolved{this, "schedules-solved",
                               "Loops whose scheduling problem was solved"};
  Statistic numSchedulesReused{
      this, "schedules-reused",
      "Loops that reused the schedule of an identical scheduling problem"};
  Statistic numReuseMismatches{
      this, "schedule-reuse-mismatches",
      "verify-schedule-reuse: reused schedules that differ from a new solve"};

  struct CachedSchedule {
    SmallVector<int64_t> signature;
    unsigned ii = 0;
    SmallVector<unsigned> startTimes; // in problem order
    std::string scheduler;
    std::string loc;
    bool recurrenceLatencies = false; // the schedule uses them
  };
  // The floating-point adds / multiplies of the loop being scheduled that sit
  // on a register recurrence, each with the operator type of its recurrence
  // latency (VITIS_NOTES N83), set by populateOperatorTypes.
  SmallVector<std::pair<Operation *, Problem::OperatorType>>
      recurrenceAlternatives;
  // Per function; keyed by the hash of the signature.
  std::unordered_map<size_t, SmallVector<CachedSchedule, 1>> scheduleCache;
};

} // namespace

/// MODIFIED (T7): everything the modulo schedulers (ModuloSimplexScheduler,
/// FastModuloScheduler) read from a ModuloProblem, with operations numbered by
/// their position in the problem and operator / resource types by their first
/// use: per operation its name, linked operator type and latency, linked
/// resource types and limits, and its dependences (source position, kind,
/// operand indices, distance); plus the anchor's position. Both schedulers
/// only compare operator / resource types for identity, iterate operations and
/// dependences in problem order and break ties by that order, so two problems
/// with equal signatures get the same II and the same start time per
/// position. The typical case is a body that a user unroll of an outer loop
/// copied N times: the copies differ in the memrefs (of one type) they access
/// and in the constants of their outer-index arithmetic, so their problems
/// are identical (forgebench diff_orders_p1: 137 of 140 innermost loops
/// reuse a schedule) unless such a constant enters the body (diff_orders_module
/// with --infer-vitis-split-array: copy k reads a bank at `[(%iv + j) floordiv
/// 16, %outer + k]`, and its problem differs from copy k+1's; 278 of 417 loops
/// reuse).
static SmallVector<int64_t> scheduleSignature(ModuloProblem &prob,
                                              Operation *anchor) {
  SmallVector<int64_t> w;
  DenseMap<Operation *, int64_t> index;
  int64_t n = 0;
  for (Operation *op : prob.getOperations())
    index[op] = n++;
  DenseMap<const void *, int64_t> oprIds, rsrcIds;
  auto idOf = [](DenseMap<const void *, int64_t> &ids, const void *key) {
    auto [it, fresh] = ids.try_emplace(key, ids.size());
    (void)fresh;
    return it->second;
  };
  auto optToWord = [](auto opt) -> int64_t {
    return opt ? static_cast<int64_t>(*opt) : -1;
  };
  auto position = [&](Operation *op) -> int64_t {
    auto it = index.find(op);
    return it == index.end() ? -1 : it->second;
  };
  w.push_back(n);
  w.push_back(position(anchor));
  for (Operation *op : prob.getOperations()) {
    w.push_back(
        reinterpret_cast<intptr_t>(op->getName().getAsOpaquePointer()));
    if (auto opr = prob.getLinkedOperatorType(op)) {
      w.push_back(idOf(oprIds, opr->getAttr().getAsOpaquePointer()));
      w.push_back(optToWord(prob.getLatency(*opr)));
    } else {
      w.append({-1, -1});
    }
    if (auto rsrcs = prob.getLinkedResourceTypes(op)) {
      w.push_back(rsrcs->size());
      for (Problem::ResourceType r : *rsrcs) {
        w.push_back(idOf(rsrcIds, r.getAttr().getAsOpaquePointer()));
        w.push_back(optToWord(prob.getLimit(r)));
      }
    } else {
      w.push_back(-1);
    }
    int64_t numDeps = 0;
    for (auto &dep : prob.getDependences(op)) {
      w.push_back(position(dep.getSource()));
      w.push_back(dep.isAuxiliary());
      w.push_back(optToWord(dep.getSourceIndex()));
      w.push_back(optToWord(dep.getDestinationIndex()));
      w.push_back(optToWord(prob.getDistance(dep)));
      ++numDeps;
    }
    w.push_back(-2 - numDeps);
  }
  return w;
}

//===----------------------------------------------------------------------===//
// Invariant-load hoisting (Vitis LICM, VITIS_NOTES.md N4 / replication.md R4).
//
// Vitis hoists a load whose address does not depend on the pipelined loop's
// induction variable, from an array the loop does not store to, out of the
// loop (it enters the loop module as a scalar argument). Such a load then uses
// no port of the loop's schedule, so it neither limits the II nor counts
// toward the replication factor. The decision is made on the loop as it is
// pipelined: when a perfect nest has been flattened (coalesced) the outer
// index is part of the flattened loop and `A[i][k]` with k unrolled is NOT
// invariant - which is why this runs after coalescePerfectNests() and not as
// a pipeline-level --affine-loop-invariant-code-motion (that would hoist out
// of the inner loop before the flatten decision and make the nest imperfect).
//
// Only ops directly in the loop body are moved (nothing from inside an
// affine.if: that would be speculation), in program order, so an op is
// hoisted iff every operand is defined outside the loop or by an op hoisted
// before it. A memref counts as written in the loop if any op inside the
// loop has a write effect on it *or on any view of it* (memref.cast,
// subview, ...: the alias set below), or uses one of them without declaring
// its effects; a memref that escaped (call, region op, yield) is never
// hoisted from.
//===----------------------------------------------------------------------===//

static bool isInnermostAffineFor(AffineForOp forOp);
static void tagPartitionedArgumentBanks(func::FuncOp func);
/// `hls.memory_recurrence` on a pipelined loop: the bound of its memory
/// recurrences (tagMemoryRecurrences); read by the scheduler and, carried
/// onto the pipeline op, by --bram-debug.
constexpr llvm::StringLiteral kMemoryRecurrenceAttr = "hls.memory_recurrence";
/// `hls.lane_recurrence = array<i64: ...>` on the store (id) and the load
/// (-1 - id) of an N154 recurrence (tagMemoryRecurrences): the scheduler
/// adds the carried dependence from the store to the next iteration's load
/// (addLaneRecurrenceEdges).
constexpr llvm::StringLiteral kLaneRecurrenceAttr = "hls.lane_recurrence";
/// `hls.register_cycle` on the op whose value a loop yields for a promoted
/// array element on an N160 recurrence (tagMemoryRecurrences): it is
/// scheduled with one cycle more than its operator latency.
constexpr llvm::StringLiteral kRegisterCycleAttr = "hls.register_cycle";

namespace {
/// The memref itself plus every value derived from it through a view-like op
/// (memref.cast, subview, reinterpret_cast, expand/collapse_shape, ...),
/// transitively. `escaped`: some member has a use that is neither a plain
/// access nor a view - a call, an op with regions taking it (scf.for
/// iter_args), a terminator yielding it, or an op producing a memref we
/// cannot follow - so the set may be incomplete. `passedToCall`: some member
/// is an operand of a call that returns neither a memref nor a pointer. The
/// callee may read and write the memory while it runs, and may keep the
/// address for a later call to use, but cannot hand it back to this
/// function, so the set stays complete; whether that matters depends on
/// where the calls are.
struct MemrefAliasInfo {
  SmallPtrSet<Value, 4> members;
  bool escaped = false;
  bool passedToCall = false;
};
} // namespace

/// A use through which the memref cannot flow anywhere else: an affine access
/// or a region-free, non-call op with declared effects and no memref result.
static bool isPlainMemrefUse(Operation *user) {
  if (isa<AffineReadOpInterface, AffineWriteOpInterface>(user))
    return true;
  if (isa<CallOpInterface>(user) || user->getNumRegions() != 0 ||
      user->hasTrait<OpTrait::IsTerminator>() ||
      !isa<MemoryEffectOpInterface>(user))
    return false;
  return llvm::none_of(user->getResultTypes(),
                       [](Type t) { return isa<BaseMemRefType>(t); });
}

static MemrefAliasInfo collectMemrefAliases(Value mem) {
  MemrefAliasInfo info;
  // Any callee may read and write a global without receiving it: every call
  // is a barrier for it, as for a memref some call received.
  if (isa_and_present<memref::GetGlobalOp>(mem.getDefiningOp()))
    info.passedToCall = true;
  SmallVector<Value> worklist{mem};
  info.members.insert(mem);
  while (!worklist.empty()) {
    Value v = worklist.pop_back_val();
    for (Operation *user : v.getUsers()) {
      if (isa<ViewLikeOpInterface>(user)) {
        for (Value r : user->getResults())
          if (isa<BaseMemRefType>(r.getType()) && info.members.insert(r).second)
            worklist.push_back(r);
        continue;
      }
      // A call that returns a pointer may return the memref's address (a
      // pointer into it can be turned back into a memref): escaped.
      if (isa<CallOpInterface>(user) &&
          llvm::none_of(user->getResultTypes(), [](Type t) {
            return isa<BaseMemRefType, LLVM::LLVMPointerType>(t);
          })) {
        info.passedToCall = true;
        continue;
      }
      if (!isPlainMemrefUse(user))
        info.escaped = true;
    }
  }
  return info;
}

/// True if some op inside `forOp` may write the memref through any member of
/// its alias set (or uses one opaquely), or if the memref has escaped. A
/// memref passed to a call counts as written when `callsOnlyInLoop` is false
/// (the old conservative rule), else only when the loop contains a call
/// (hoist-past-calls: an array filled by a call before the loop, Analog-CIM
/// on-board `v_ref_buf`, is read through hoisted loads in Vitis: a plain
/// RAM of 4 BRAM, not 15 copies).
static bool isMemrefWrittenInLoop(const MemrefAliasInfo &alias,
                                  Operation *forOp,
                                  bool callsOnlyInLoop = false) {
  if (alias.escaped)
    return true;
  if (alias.passedToCall) {
    if (!callsOnlyInLoop)
      return true;
    // A callee that received the memref may write it only while it runs,
    // during that call or (keeping the address) during a later call: only a
    // call inside the loop can write it while the loop runs.
    bool hasCall = false;
    forOp->walk([&](CallOpInterface) {
      hasCall = true;
      return WalkResult::interrupt();
    });
    if (hasCall)
      return true;
  }
  bool written = false;
  forOp->walk([&](Operation *op) {
    if (isa<ViewLikeOpInterface>(op))
      return WalkResult::advance(); // pure; its result is a member itself
    for (Value opd : op->getOperands()) {
      if (!alias.members.contains(opd))
        continue;
      if (isa<AffineWriteOpInterface>(op)) {
        written = true;
        return WalkResult::interrupt();
      }
      if (isa<AffineReadOpInterface>(op))
        continue;
      auto eff = dyn_cast<MemoryEffectOpInterface>(op);
      if (!eff) {
        written = true; // unknown effects on the memref: assume a write
        return WalkResult::interrupt();
      }
      SmallVector<MemoryEffects::EffectInstance> effects;
      eff.getEffectsOnValue(opd, effects);
      for (auto &e : effects)
        if (!isa<MemoryEffects::Read>(e.getEffect())) {
          written = true; // Write, Allocate, Free
          return WalkResult::interrupt();
        }
    }
    return WalkResult::advance();
  });
  return written;
}

void AffineToLoopSchedule::hoistInvariantLoads() {
  SmallVector<AffineForOp> loops;
  getOperation().walk([&](AffineForOp forOp) {
    if (isInnermostAffineFor(forOp))
      loops.push_back(forOp);
  });

  // Alias sets are a property of the function (moving ops changes no uses).
  DenseMap<Value, MemrefAliasInfo> aliasCache;
  auto aliasInfo = [&](Value mem) -> const MemrefAliasInfo & {
    auto it = aliasCache.find(mem);
    if (it == aliasCache.end())
      it = aliasCache.try_emplace(mem, collectMemrefAliases(mem)).first;
    return it->second;
  };

  unsigned hoistedLoads = 0, hoistedPure = 0;
  for (AffineForOp forOp : loops) {
    // MODIFIED (T3): `hls.flattened_parents = N` (--auto-pipeline-unroll)
    // says Vitis flattens the N enclosing loops into this pipeline, so their
    // IVs - and everything defined in their bodies - are loop-variant for
    // it, and a write in their bodies is a write in the pipelined loop.
    LoopLikeOpInterface root = circt::hls_analysis::getFlattenedRoot(forOp);
    DenseSet<Value> invariant; // results of ops hoisted so far
    auto isInvariantValue = [&](Value v) {
      return root.isDefinedOutsideOfLoop(v) || invariant.contains(v);
    };
    DenseMap<Value, bool> writtenCache;
    auto writtenInLoop = [&](Value mem) {
      auto it = writtenCache.find(mem);
      if (it != writtenCache.end())
        return it->second;
      bool w = isMemrefWrittenInLoop(aliasInfo(mem), root, hoistPastCalls);
      writtenCache[mem] = w;
      return w;
    };

    SmallVector<Operation *> toHoist;
    for (Operation &op : forOp.getBody()->without_terminator()) {
      if (op.getNumRegions() != 0)
        continue;
      bool hoistable = false;
      if (auto load = dyn_cast<AffineLoadOp>(op)) {
        hoistable = llvm::all_of(load.getMapOperands(), isInvariantValue) &&
                    isInvariantValue(load.getMemRef()) &&
                    !writtenInLoop(load.getMemRef());
        if (hoistable)
          ++hoistedLoads;
      } else if (isMemoryEffectFree(&op) && isSpeculatable(&op) &&
                 op.getNumResults() > 0) {
        hoistable = llvm::all_of(op.getOperands(), isInvariantValue);
        if (hoistable)
          ++hoistedPure;
      }
      if (!hoistable)
        continue;
      toHoist.push_back(&op);
      for (Value r : op.getResults())
        invariant.insert(r);
    }
    // A load under an if of the body (unrolled compares with an early
    // `break`, a guarded read) is hoisted the same way when its address and
    // memref are loop-invariant: Vitis' LICM speculates it (a kernel reading
    // 32 `rb[l]` under a break-guarded compare at II 2 takes them as 32
    // scalar arguments of the pipeline, `rb` a plain 2-port RAM; an
    // if/else-guarded `X[l + k]` read in a loop over c is hoisted out of the
    // c loop). Its operands are defined above the loop or by a hoisted op.
    if (hoistConditional)
      forOp.getBody()->walk([&](AffineLoadOp load) {
        Operation *parent = load->getParentOp();
        if (parent == forOp.getOperation())
          return; // a top-level load: decided above
        for (Operation *p = parent; p != forOp.getOperation();
             p = p->getParentOp())
          if (!isa<scf::IfOp, AffineIfOp>(p))
            return; // only if-nesting, never another region kind
        if (!llvm::all_of(load.getMapOperands(), isInvariantValue) ||
            !isInvariantValue(load.getMemRef()) ||
            writtenInLoop(load.getMemRef()))
          return;
        load->setAttr("hls.hoisted_conditional", UnitAttr::get(load->getContext()));
        toHoist.push_back(load);
        invariant.insert(load.getResult());
        ++hoistedLoads;
      });
    // Program order is preserved, so every hoisted op's operands are already
    // above the loop when it is moved.
    for (Operation *op : toHoist)
      op->moveBefore(forOp);
  }
  // The condition of an scf.while (a loop whose bound is re-read every
  // iteration, `for (i = rp[r]; i < rp[r + 1]; ++i)`): an invariant load of
  // the before-region moves in front of the loop, as LLVM's LICM moves it out
  // of the loop header, so it shares the enclosing scope's states with the
  // other reads there (VITIS_NOTES N120: davendra lab3 read_csr_row,
  // row_ptr_A_local[row] and [row + 1] in one state, ram_2p 2; kernels
  // w9r15p_rp_*). Key tool.hls.middle_end.licm_hoist_while_conditions.
  if (circt::hlsest::Config::get().tool.hls.middleEnd.licmHoistWhileConditions)
    getOperation().walk([&](scf::WhileOp whileOp) {
      Block &before = whileOp.getBefore().front();
      SmallVector<Operation *> moves;
      DenseSet<Value> hoisted;
      auto invariant = [&](Value v) {
        return !whileOp->isAncestor(v.getParentRegion()->getParentOp()) ||
               hoisted.contains(v);
      };
      for (Operation &op : before.without_terminator()) {
        if (op.getNumRegions() != 0)
          continue;
        bool ok = false;
        if (auto load = dyn_cast<AffineLoadOp>(op))
          ok = llvm::all_of(load.getMapOperands(), invariant) &&
               invariant(load.getMemRef()) &&
               !isMemrefWrittenInLoop(aliasInfo(load.getMemRef()), whileOp,
                                      hoistPastCalls);
        else if (isMemoryEffectFree(&op) && isSpeculatable(&op) &&
                 op.getNumResults() > 0)
          ok = llvm::all_of(op.getOperands(), invariant);
        if (!ok)
          continue;
        moves.push_back(&op);
        for (Value r : op.getResults())
          hoisted.insert(r);
      }
      // Only worth it when a load moves; pure ops alone stay.
      if (llvm::none_of(moves, [](Operation *op) {
            return isa<AffineLoadOp>(op);
          }))
        return;
      for (Operation *op : moves) {
        if (isa<AffineLoadOp>(op))
          ++hoistedLoads;
        op->moveBefore(whileOp);
      }
    });
  LLVM_DEBUG(llvm::dbgs() << "hoisted " << hoistedLoads
                          << " loop-invariant affine.load and " << hoistedPure
                          << " pure ops out of innermost loops\n");
}

//===----------------------------------------------------------------------===//
// Redundant-access cleanup (Vitis GVN / DSE on the unrolled body;
// VITIS_NOTES.md N4: R and W per iteration are counted "after unrolling, CSE,
// LICM").
//
// Within one block, in program order, Vitis' LLVM pipeline removes
//   - a load of an address loaded before with no intervening write that may
//     alias it: the same value (CSE / GVN)                         [cse-loads]
//   - a load of an address stored before with no intervening may-alias write
//     (store-to-load forwarding), and a store overwritten by a later store to
//     the same address with no intervening may-alias read (dead-store
//     elimination)                                            [forward-stores]
// so an unrolled accumulator `acc[i] += ...` (load, add, store, N times)
// becomes one load and one store per iteration, and only those use ports.
//
// Two affine accesses to one memref are compared with
// AffineValueMap::difference after full composition: every result a constant
// 0 -> same address; some result a nonzero constant -> disjoint (`A[i][k]`
// vs `A[i][k+1]` after unrolling); anything else may alias. Distinct memref
// values never alias (the affine dialect's and the dependence analysis'
// assumption), so only memrefs whose SSA value identifies the storage take
// part: allocas, allocs and function arguments (not views, iter_args or
// get_global results, see isRootMemref), and only when they have not escaped
// (collectMemrefAliases). A memref passed to a call has not escaped: the
// callee may read and write it, but only while the call runs, so the call is
// a barrier at its own position like any other opaque use below (the known
// values of that memref are forgotten there), and accesses that do not span
// the call are still merged and forwarded. The callee may also keep the
// address and write through it during a later call that does not take the
// memref, so every call is a barrier for a memref passed to some call. Vitis does the same: a kept callee
// taking an array after a loop does not stop the forwarding of an
// accumulator inside that loop. Only affine.load / affine.store are tracked; a
// non-affine or predicated access, an access through a view, an op with
// regions touching the memref, and any other use of the memref or of a view
// of it are opaque: they forget everything known about that memref. Nothing
// is forwarded across a block boundary or a loop back edge.
//
// The surviving op records what it absorbed (`hls.merged_loads` on a load,
// `hls.forwarded_loads` / `hls.removed_stores` on a store); the affine
// lowering carries the attributes along (copyHlsAttrs) so --bram-debug can
// show why R and W are what they are. Erases ops, so it runs before every
// analysis (runOnOperation).
//===----------------------------------------------------------------------===//

namespace {
enum class AddrRelation { Same, Disjoint, MayAlias };

struct AccessAddr;
/// The composed addresses of one clean-up phase of runOnOperation (W9 round
/// 23 review D9: each phase built the AccessAddr of the same access several
/// times, and a fully unrolled body has hundreds of thousands: hlsyn
/// symm-opt-medium). Keyed on the map and the operand values; it lives for one
/// phase (AccessAddrCacheScope), in which no affine.apply is created or
/// erased, so a key always names the same composition.
using AccessAddrKey = std::vector<const void *>;
static thread_local std::map<AccessAddrKey,
                             std::pair<AffineMap, SmallVector<Value, 4>>>
    *accessAddrCache = nullptr;
struct AccessAddrCacheScope {
  std::map<AccessAddrKey, std::pair<AffineMap, SmallVector<Value, 4>>> cache;
  AccessAddrCacheScope() { accessAddrCache = &cache; }
  ~AccessAddrCacheScope() { accessAddrCache = nullptr; }
};

struct AccessAddr {
  AffineMap map;
  SmallVector<Value, 4> operands;
  AccessAddr(AffineMap m, ValueRange opds)
      : map(m), operands(opds.begin(), opds.end()) {
    AccessAddrKey key;
    if (accessAddrCache) {
      key.reserve(operands.size() + 1);
      key.push_back(map.getAsOpaquePointer());
      for (Value v : operands)
        key.push_back(v.getAsOpaquePointer());
      auto it = accessAddrCache->find(key);
      if (it != accessAddrCache->end()) {
        map = it->second.first;
        operands = it->second.second;
        return;
      }
    }
    fullyComposeAffineMapAndOperands(&map, &operands);
    canonicalizeMapAndOperands(&map, &operands);
    if (accessAddrCache)
      accessAddrCache->emplace(std::move(key), std::make_pair(map, operands));
  }
};

/// What is known about one address of a memref at the current point of a
/// block.
struct KnownValue {
  AccessAddr addr;
  Value value;      // the value held at `addr`
  Operation *store; // the affine.store that put it there; null: a load read it
  bool readSince;   // a read that may alias `addr` happened after `store`
};
} // namespace

/// `e` as (the expression without its constant term, the constant term):
/// `d0 + 5` is (d0, 5), `7` is (null, 7), `d0` is (d0, 0). Simplified affine
/// expressions keep the constant as the right operand of the outermost
/// addition.
static std::pair<AffineExpr, int64_t> splitConstantTerm(AffineExpr e) {
  if (auto c = dyn_cast<AffineConstantExpr>(e))
    return {AffineExpr(), c.getValue()};
  if (auto add = dyn_cast<AffineBinaryOpExpr>(e))
    if (add.getKind() == AffineExprKind::Add)
      if (auto c = dyn_cast<AffineConstantExpr>(add.getRHS()))
        return {add.getLHS(), c.getValue()};
  return {e, 0};
}

static AddrRelation compareAddresses(const AccessAddr &a,
                                     const AccessAddr &b) {
  if (a.map.getNumResults() != b.map.getNumResults())
    return AddrRelation::MayAlias;
  // Fast path for the common case of an unrolled body (the same operands,
  // results that differ in constant terms only): the difference of two
  // results whose non-constant parts are equal is the difference of their
  // constants. A nonzero one in any result makes them disjoint, as below.
  if (a.operands == b.operands &&
      a.map.getNumDims() == b.map.getNumDims() &&
      a.map.getNumSymbols() == b.map.getNumSymbols()) {
    bool allEqualParts = true;
    for (auto [ea, eb] : llvm::zip(a.map.getResults(), b.map.getResults())) {
      auto [va, ca] = splitConstantTerm(ea);
      auto [vb, cb] = splitConstantTerm(eb);
      if (va != vb) {
        allEqualParts = false;
        continue;
      }
      if (ca != cb)
        return AddrRelation::Disjoint;
    }
    if (allEqualParts)
      return AddrRelation::Same;
  }
  AffineValueMap va(a.map, a.operands), vb(b.map, b.operands), diff;
  AffineValueMap::difference(va, vb, &diff);
  bool allZero = true;
  for (unsigned d = 0, n = diff.getNumResults(); d < n; ++d) {
    auto c = dyn_cast<AffineConstantExpr>(diff.getResult(d));
    if (!c)
      allZero = false;
    else if (c.getValue() != 0)
      return AddrRelation::Disjoint;
  }
  return allZero ? AddrRelation::Same : AddrRelation::MayAlias;
}

static int64_t counterAttr(Operation *op, StringRef name) {
  if (auto a = op->getAttrOfType<IntegerAttr>(name))
    return a.getInt();
  return 0;
}

static void addCounterAttr(Operation *op, StringRef name, int64_t by) {
  if (by <= 0)
    return;
  op->setAttr(name, IntegerAttr::get(IntegerType::get(op->getContext(), 64),
                                     counterAttr(op, name) + by));
}

/// The pass's track-globals option for the function being processed (set by
/// runOnOperation on the thread that processes it).
static thread_local bool tlsTrackGlobals = true;

/// Memrefs whose SSA value identifies the storage: a local array, a
/// function argument, or (track-globals) a global, whose one
/// memref.get_global per function uniqueGlobalRefs leaves. A view or an
/// iter_arg aliases its source: not tracked.
static bool isRootMemref(Value mem) {
  if (auto arg = dyn_cast<BlockArgument>(mem))
    return isa<func::FuncOp>(arg.getOwner()->getParentOp());
  if (tlsTrackGlobals &&
      isa_and_present<memref::GetGlobalOp>(mem.getDefiningOp()))
    return true;
  return isa_and_present<memref::AllocaOp, memref::AllocOp>(
      mem.getDefiningOp());
}

namespace {
/// An index over the known values of one block that gives, for an address,
/// exactly the relation compareAddresses gives against every known value,
/// without comparing it with each of them (the pairwise scan was quadratic in
/// the accesses of an unrolled body: 78-95 % of the run time of fdtd-2d-large,
/// lab2_hanchen and gemm-p-large; OPEN_ISSUES O91).
///
/// An address is split into its shape (the operands, the dimension and symbol
/// counts, and every result without its constant term, splitConstantTerm) and
/// the constant terms. Two addresses of one shape are the same address when
/// their constants are equal and disjoint otherwise (compareAddresses' fast
/// path). For two shapes, the difference of their constant-free results is
/// computed once (the AffineValueMap::difference of compareAddresses' slow
/// path); the difference of two addresses is that plus the difference of the
/// constants, so a result whose shape difference is a constant k is the
/// constant k + ca - cb, and any other is not a constant.
class KnownAddressIndex {
public:
  struct Split {
    unsigned shape = 0;
    std::vector<int64_t> consts;
  };
  /// Per pair of shapes: no relation can be computed (different result
  /// counts: compareAddresses says MayAlias), or the constant difference of
  /// each result's constant-free parts (nullopt: not a constant).
  struct PairInfo {
    bool mayAliasAll = false;
    SmallVector<std::optional<int64_t>, 4> k;
  };

  Split split(const AccessAddr &a) {
    Split out;
    std::vector<uintptr_t> key;
    key.push_back(a.map.getNumResults());
    key.push_back(a.map.getNumDims());
    key.push_back(a.map.getNumSymbols());
    for (Value v : a.operands)
      key.push_back(reinterpret_cast<uintptr_t>(v.getAsOpaquePointer()));
    SmallVector<AffineExpr, 4> parts;
    for (AffineExpr e : a.map.getResults()) {
      auto [part, c] = splitConstantTerm(e);
      parts.push_back(part);
      out.consts.push_back(c);
      key.push_back(
          reinterpret_cast<uintptr_t>(part ? part.getAsOpaquePointer() : nullptr));
    }
    auto [it, inserted] = shapeIds.try_emplace(key, shapes.size());
    if (inserted) {
      Shape sh;
      sh.ctx = a.map.getContext();
      sh.numDims = a.map.getNumDims();
      sh.numSymbols = a.map.getNumSymbols();
      sh.operands.assign(a.operands.begin(), a.operands.end());
      sh.parts = std::move(parts);
      shapes.push_back(std::move(sh));
    }
    out.shape = it->second;
    return out;
  }

  const PairInfo &pair(unsigned sa, unsigned sb) {
    auto [it, inserted] = pairs.try_emplace({sa, sb});
    if (!inserted)
      return it->second;
    PairInfo &info = it->second;
    const Shape &a = shapes[sa], &b = shapes[sb];
    if (a.parts.size() != b.parts.size()) {
      info.mayAliasAll = true;
      return info;
    }
    bool sameOperands = a.operands == b.operands &&
                        a.numDims == b.numDims && a.numSymbols == b.numSymbols;
    bool needDifference = false;
    for (auto [pa, pb] : llvm::zip(a.parts, b.parts)) {
      if (sameOperands && pa == pb)
        info.k.push_back(0);
      else {
        info.k.push_back(std::nullopt);
        needDifference = true;
      }
    }
    if (!needDifference)
      return info;
    AffineValueMap va(partsMap(a), a.operands), vb(partsMap(b), b.operands),
        diff;
    AffineValueMap::difference(va, vb, &diff);
    for (unsigned r = 0, n = diff.getNumResults(); r < n; ++r) {
      if (sameOperands && a.parts[r] == b.parts[r])
        continue;
      if (auto c = dyn_cast<AffineConstantExpr>(diff.getResult(r)))
        info.k[r] = c.getValue();
    }
    return info;
  }

  /// compareAddresses of an address (shape sa, constants ca) and a known one
  /// (shape sb, constants cb).
  static AddrRelation relation(const PairInfo &p, ArrayRef<int64_t> ca,
                               ArrayRef<int64_t> cb) {
    if (p.mayAliasAll)
      return AddrRelation::MayAlias;
    bool allZero = true;
    for (unsigned r = 0, n = p.k.size(); r < n; ++r) {
      if (!p.k[r]) {
        allZero = false;
        continue;
      }
      if (*p.k[r] + ca[r] - cb[r] != 0)
        return AddrRelation::Disjoint;
    }
    return allZero ? AddrRelation::Same : AddrRelation::MayAlias;
  }

private:
  struct Shape {
    MLIRContext *ctx = nullptr;
    unsigned numDims = 0, numSymbols = 0;
    SmallVector<Value, 4> operands;
    SmallVector<AffineExpr, 4> parts;
  };
  AffineMap partsMap(const Shape &sh) {
    SmallVector<AffineExpr, 4> results;
    MLIRContext *ctx = sh.ctx;
    for (AffineExpr p : sh.parts)
      results.push_back(p ? p : getAffineConstantExpr(0, ctx));
    return AffineMap::get(sh.numDims, sh.numSymbols, results, ctx);
  }

  std::vector<Shape> shapes;
  std::map<std::vector<uintptr_t>, unsigned> shapeIds;
  DenseMap<std::pair<unsigned, unsigned>, PairInfo> pairs;
};

/// The known values of one memref, in program order, indexed by address.
struct KnownValues {
  struct Entry {
    KnownValue kv;
    KnownAddressIndex::Split split;
    bool alive = true;
  };
  struct Bucket {
    unsigned shape;
    SmallVector<unsigned, 4> all;
    std::map<std::vector<int64_t>, SmallVector<unsigned, 2>> exact;
    /// Per mask of results: the entries by their constants on those results.
    std::map<uint64_t, std::map<std::vector<int64_t>, SmallVector<unsigned, 2>>>
        projected;
  };
  std::vector<Entry> entries;
  std::vector<Bucket> buckets;
  DenseMap<unsigned, unsigned> bucketOf;

  static std::vector<int64_t> project(ArrayRef<int64_t> c, uint64_t mask) {
    std::vector<int64_t> out;
    for (unsigned r = 0, n = c.size(); r < n; ++r)
      if (mask & (uint64_t(1) << r))
        out.push_back(c[r]);
    return out;
  }

  void add(KnownValue kv, KnownAddressIndex::Split split) {
    unsigned id = entries.size();
    auto [it, inserted] = bucketOf.try_emplace(split.shape, buckets.size());
    if (inserted)
      buckets.push_back(Bucket{split.shape, {}, {}, {}});
    Bucket &b = buckets[it->second];
    b.all.push_back(id);
    b.exact[split.consts].push_back(id);
    for (auto &[mask, index] : b.projected)
      index[project(split.consts, mask)].push_back(id);
    entries.push_back({std::move(kv), std::move(split), true});
  }

  /// The live entries that are not disjoint from the address, with their
  /// relation (Same or MayAlias), in program order.
  SmallVector<std::pair<unsigned, AddrRelation>>
  overlapping(KnownAddressIndex &index, const KnownAddressIndex::Split &q) {
    SmallVector<std::pair<unsigned, AddrRelation>> out;
    for (Bucket &b : buckets) {
      const KnownAddressIndex::PairInfo &p = index.pair(q.shape, b.shape);
      auto addAll = [&](ArrayRef<unsigned> ids) {
        for (unsigned id : ids)
          if (entries[id].alive) {
            AddrRelation rel = KnownAddressIndex::relation(
                p, q.consts, entries[id].split.consts);
            if (rel != AddrRelation::Disjoint)
              out.push_back({id, rel});
          }
      };
      unsigned n = q.consts.size();
      if (p.mayAliasAll || n > 63) {
        addAll(b.all);
        continue;
      }
      uint64_t mask = 0;
      for (unsigned r = 0; r < n; ++r)
        if (p.k[r])
          mask |= uint64_t(1) << r;
      std::vector<int64_t> target;
      for (unsigned r = 0; r < n; ++r)
        if (p.k[r])
          target.push_back(q.consts[r] + *p.k[r]);
      uint64_t full = n == 64 ? ~uint64_t(0) : (uint64_t(1) << n) - 1;
      if (mask == 0) {
        addAll(b.all);
      } else if (mask == full) {
        auto it = b.exact.find(target);
        if (it != b.exact.end())
          addAll(it->second);
      } else {
        auto [pit, built] = b.projected.try_emplace(mask);
        if (built)
          for (unsigned id : b.all)
            pit->second[project(entries[id].split.consts, mask)].push_back(id);
        auto it = pit->second.find(target);
        if (it != pit->second.end())
          addAll(it->second);
      }
    }
    llvm::sort(out, [](const auto &x, const auto &y) { return x.first < y.first; });
    return out;
  }
};
} // namespace

void AffineToLoopSchedule::cleanupRedundantAccesses() {
  SmallVector<Block *> blocks;
  getOperation().walk([&](Block *b) { blocks.push_back(b); });

  DenseMap<Value, MemrefAliasInfo> aliasCache;
  auto aliasInfo = [&](Value mem) -> const MemrefAliasInfo & {
    auto it = aliasCache.find(mem);
    if (it == aliasCache.end())
      it = aliasCache.try_emplace(mem, collectMemrefAliases(mem)).first;
    return it->second;
  };

  unsigned merged = 0, forwarded = 0, removed = 0;
  for (Block *block : blocks) {
    // No op is created while a block is processed (only erased), so the
    // operand values the index keys on stay valid within the block.
    KnownAddressIndex index;
    DenseMap<Value, KnownValues> known; // root -> values
    DenseMap<Value, Value> memberToRoot; // alias member -> root
    // gvn_memref_loads: per tracked root, the memref.loads seen by index
    // operands.
    DenseMap<Value, std::map<std::vector<const void *>, Value>> memrefLoads;
    auto forget = [&](Value mem) {
      auto it = memberToRoot.find(mem);
      if (it != memberToRoot.end()) {
        known.erase(it->second);
        memrefLoads.erase(it->second);
      }
      known.erase(mem);
      memrefLoads.erase(mem);
    };
    auto forgetOperands = [&](Operation *op) {
      for (Value v : op->getOperands())
        if (isa<BaseMemRefType>(v.getType()))
          forget(v);
    };
    // Tracked iff a root that has not escaped. Registers the alias set so
    // that an access through a view forgets the root's state.
    auto trackable = [&](Value mem) -> bool {
      if (!isRootMemref(mem))
        return false;
      const MemrefAliasInfo &ai = aliasInfo(mem);
      if (ai.escaped)
        return false;
      if (!memberToRoot.count(mem))
        for (Value m : ai.members)
          memberToRoot[m] = mem;
      return true;
    };

    for (Operation &op : llvm::make_early_inc_range(*block)) {
      // A memref.load (an index computed outside the affine form) of the
      // same index values as an earlier load, nothing in between that may
      // write the memref: the same value, as Vitis' GVN merges it (Dehazing
      // debayer with its counters raised: 27 reads of in_tile, 9 distinct;
      // key tool.hls.middle_end.gvn_memref_loads). Exact operand matches
      // only, kept apart from the affine state (a lookup per load: hlsyn
      // gemm-blocked has thousands of such loads in one block); any write
      // or opaque use of the memref forgets them.
      if (auto mload = dyn_cast<memref::LoadOp>(op);
          mload && cseLoads && gvnMemrefLoads) {
        Value mem = mload.getMemRef();
        if (!trackable(mem)) {
          forget(mem);
          continue;
        }
        std::vector<const void *> key;
        for (Value v : mload.getIndices())
          key.push_back(v.getAsOpaquePointer());
        auto &seen = memrefLoads[mem];
        auto it = seen.find(key);
        if (it != seen.end()) {
          addCounterAttr(it->second.getDefiningOp(), "hls.merged_loads", 1);
          ++merged;
          mload.getResult().replaceAllUsesWith(it->second);
          mload.erase();
          continue;
        }
        seen.emplace(std::move(key), mload.getResult());
        continue;
      }
      if (auto load = dyn_cast<AffineLoadOp>(op)) {
        Value mem = load.getMemRef();
        if (!trackable(mem)) {
          forget(mem);
          continue;
        }
        AccessAddr addr(load.getAffineMap(), load.getMapOperands());
        KnownAddressIndex::Split split = index.split(addr);
        KnownValues &vals = known[mem];
        KnownValue *same = nullptr;
        for (auto [id, rel] : vals.overlapping(index, split)) {
          KnownValue &kv = vals.entries[id].kv;
          if (rel == AddrRelation::Same) {
            same = &kv;
            break;
          }
          if (kv.store) // MayAlias
            kv.readSince = true;
        }
        if (same && (same->store ? forwardStores : cseLoads)) {
          // The memory is not read: the known value is used instead.
          if (same->store) {
            addCounterAttr(same->store, "hls.forwarded_loads", 1);
            ++forwarded;
          } else {
            addCounterAttr(same->value.getDefiningOp(), "hls.merged_loads", 1);
            ++merged;
          }
          load.getResult().replaceAllUsesWith(same->value);
          load.erase();
          continue;
        }
        if (same) { // option off: a real read of a known address
          if (same->store)
            same->readSince = true;
          continue;
        }
        vals.add({addr, load.getResult(), nullptr, false}, std::move(split));
        continue;
      }
      if (auto store = dyn_cast<AffineStoreOp>(op)) {
        Value mem = store.getMemRef();
        if (!trackable(mem)) {
          forget(mem);
          continue;
        }
        memrefLoads.erase(mem); // may write what a memref.load read
        AccessAddr addr(store.getAffineMap(), store.getMapOperands());
        KnownAddressIndex::Split split = index.split(addr);
        KnownValues &vals = known[mem];
        for (auto [id, rel] : vals.overlapping(index, split)) {
          KnownValues::Entry &e = vals.entries[id];
          KnownValue &kv = e.kv;
          if (rel == AddrRelation::Same && kv.store && !kv.readSince &&
              forwardStores) {
            // Overwritten before anything could read it: dead. This store
            // stands for it (and for the loads it served) in the report.
            addCounterAttr(&op, "hls.removed_stores",
                           1 + counterAttr(kv.store, "hls.removed_stores"));
            addCounterAttr(&op, "hls.forwarded_loads",
                           counterAttr(kv.store, "hls.forwarded_loads"));
            kv.store->erase();
            ++removed;
          }
          // Same (still needed) or may-alias: the old value is unknown now.
          e.alive = false;
        }
        vals.add({addr, store.getValueToStore(), store.getOperation(), false},
                 std::move(split));
        continue;
      }
      // Any call, directly or inside the op's regions, may write a memref
      // whose address some call received earlier (and kept).
      bool hasCall = false;
      op.walk([&](CallOpInterface) {
        hasCall = true;
        return WalkResult::interrupt();
      });
      if (hasCall) {
        SmallVector<Value> passed;
        for (auto &entry : known)
          if (aliasInfo(entry.first).passedToCall)
            passed.push_back(entry.first);
        for (auto &entry : memrefLoads)
          if (aliasInfo(entry.first).passedToCall)
            passed.push_back(entry.first);
        for (Value root : passed) {
          known.erase(root);
          memrefLoads.erase(root);
        }
      }
      // Anything else that touches a memref, or a view of one, directly or
      // inside its regions, is opaque for that memref.
      forgetOperands(&op);
      for (Region &region : op.getRegions())
        region.walk([&](Operation *inner) { forgetOperands(inner); });
    }
  }
  LLVM_DEBUG(llvm::dbgs() << "redundant-access cleanup: merged " << merged
                          << " loads, forwarded " << forwarded
                          << " loads from stores, removed " << removed
                          << " dead stores\n");
}

//===----------------------------------------------------------------------===//
// Same-address accesses in the two arms of an if/else (Vitis SimplifyCFG /
// InstCombine: a load both arms make of one address is hoisted above the
// branch, a store both arms make to one address is sunk below it as one store
// of a select).
//
// Vitis counts `if (c) A[i] = x; else A[i] = 0;` as one store per iteration:
// the array stays replicable (RAM_1WNR with 7 copies for 8 reads at II 1). A
// read-modify-write repeated in both arms (`if (c) Y[i] += 0; else Y[i] +=
// x * w;`) becomes one load and one store, so an unrolled accumulation of it
// is one load and one store per iteration after store forwarding (Vitis
// 2025.1, td=off: kernels with these two patterns, an int and a float one).
//
// For each scf.if / affine.if with an else block, innermost first:
//   - an affine.load in one arm with an affine.load of the same address of the
//     same memref in the other arm, neither preceded in its arm by anything
//     that may write that address, becomes one load just before the if;
//   - an affine.store in one arm with an affine.store to the same address of
//     the same memref in the other arm, neither followed in its arm by
//     anything that may touch that address, becomes one store just after the
//     if of a value the if yields.
// The address operands must be defined outside the if, and only memrefs the
// redundant-access cleanup tracks take part (a local array or a function
// argument that has not escaped). Accesses of the memref at a disjoint
// constant offset (`A[i]` vs `A[i + 1]`) do not block the move; any other use
// of the memref or of a view of it does. Runs before the redundant-access
// cleanup, which then forwards the merged accesses across iterations of an
// unrolled body.
//===----------------------------------------------------------------------===//

namespace {
/// One arm of an if/else: its block, and the region that holds it.
struct IfArm {
  Block *block;
  Region *region;
};
} // namespace

static Value accessMemref(Operation *op) {
  if (auto l = dyn_cast<AffineLoadOp>(op))
    return l.getMemRef();
  if (auto s = dyn_cast<AffineStoreOp>(op))
    return s.getMemRef();
  return {};
}

static AccessAddr accessAddr(Operation *op) {
  if (auto l = dyn_cast<AffineLoadOp>(op))
    return AccessAddr(l.getAffineMap(), l.getMapOperands());
  auto s = cast<AffineStoreOp>(op);
  return AccessAddr(s.getAffineMap(), s.getMapOperands());
}

namespace {
/// What mayConflict needs of an op and everything nested in it, collected
/// once: whether it holds a call, and the ops that take a memref operand with
/// those operands and, for an affine access, its address (the walk with an
/// operand scan per op and an AccessAddr per access made mayConflict, called
/// for every pair of accesses of an if arm, 41-56 % of symm-opt and syr2k;
/// OPEN_ISSUES O91). Entries are invalidated when the IR under them changes.
struct ConflictSummary {
  struct Toucher {
    Operation *op;
    SmallVector<Value, 1> memrefs;
    std::optional<AccessAddr> addr; // affine.load / affine.store only
  };
  bool hasCall = false;
  SmallVector<Toucher, 2> touchers;
};

class ConflictSummaries {
public:
  const ConflictSummary &get(Operation *op) {
    auto it = cache.find(op);
    if (it != cache.end())
      return *it->second;
    auto summary = std::make_unique<ConflictSummary>();
    op->walk([&](Operation *y) {
      if (isa<CallOpInterface>(y))
        summary->hasCall = true;
      ConflictSummary::Toucher t;
      t.op = y;
      for (Value v : y->getOperands())
        if (isa<BaseMemRefType>(v.getType()))
          t.memrefs.push_back(v);
      if (t.memrefs.empty())
        return;
      if (isa<AffineLoadOp, AffineStoreOp>(y))
        t.addr.emplace(accessAddr(y));
      summary->touchers.push_back(std::move(t));
    });
    return *cache.try_emplace(op, std::move(summary)).first->second;
  }
  /// `op` changes or goes away: forget it and every op that encloses it.
  void invalidate(Operation *op) {
    for (Operation *cur = op; cur; cur = cur->getParentOp())
      cache.erase(cur);
  }
  void clear() { cache.clear(); }

private:
  DenseMap<Operation *, std::unique_ptr<ConflictSummary>> cache;
};
} // namespace

/// True when `other` (an op of an arm, or nested in one) may conflict with an
/// access to `addr` of the memref whose alias set is `alias`: a write that
/// may alias the address (or, with `readsConflict`, any access that may alias
/// it), or any other use of a member of the alias set. A call conflicts when
/// the memref was passed to some call.
static bool mayConflict(Operation *other, Value mem,
                        const MemrefAliasInfo &alias, const AccessAddr &addr,
                        bool readsConflict, ConflictSummaries &summaries) {
  const ConflictSummary &s = summaries.get(other);
  if (alias.passedToCall && s.hasCall)
    return true;
  for (const ConflictSummary::Toucher &t : s.touchers) {
    Operation *op = t.op;
    bool touches = llvm::any_of(t.memrefs, [&](Value v) {
      return alias.members.contains(v);
    });
    if (!touches)
      continue;
    if (isa<ViewLikeOpInterface>(op))
      continue; // its uses are visited themselves
    bool isLoad = isa<AffineLoadOp>(op), isStore = isa<AffineStoreOp>(op);
    if ((isLoad || isStore) && accessMemref(op) == mem) {
      if (isLoad && !readsConflict)
        continue;
      if (compareAddresses(*t.addr, addr) == AddrRelation::Disjoint)
        continue;
    }
    return true;
  }
  return false;
}

static bool definedOutside(ValueRange values, Operation *ifOp) {
  return llvm::all_of(values, [&](Value v) {
    return !ifOp->isAncestor(v.getParentRegion()->getParentOp());
  });
}

/// The memory touchers of an if arm by the memref they touch, with the
/// position of the arm's op they are nested in: mayConflict over every
/// earlier (later) op of the arm is the same question asked of the touchers
/// of the alias set's members at smaller (larger) positions, which is what
/// keeps movableAccesses from scanning the whole arm per access (hlsyn
/// symm-opt-medium over 600 s; OPEN_ISSUES O103 (3)).
struct ArmTouchers {
  using Entry = std::pair<unsigned, const ConflictSummary::Toucher *>;
  DenseMap<Value, SmallVector<Entry>> byMemref;
  SmallVector<unsigned> callPositions; ///< arm ops that hold a call
  DenseMap<Operation *, unsigned> position;

  ArmTouchers(Block *block, ConflictSummaries &summaries) {
    unsigned pos = 0;
    for (Operation &op : *block) {
      position[&op] = pos;
      const ConflictSummary &s = summaries.get(&op);
      if (s.hasCall)
        callPositions.push_back(pos);
      for (const ConflictSummary::Toucher &t : s.touchers)
        for (Value v : t.memrefs) {
          SmallVector<Entry> &list = byMemref[v];
          if (list.empty() || list.back().second != &t)
            list.push_back({pos, &t});
        }
      ++pos;
    }
  }

  /// mayConflict(op, ...) for some op of the arm before (`before`) or after
  /// the op at `pos`.
  bool anyConflict(unsigned pos, bool before, Value mem,
                   const MemrefAliasInfo &alias, const AccessAddr &addr,
                   bool readsConflict) const {
    auto inRange = [&](unsigned q) { return before ? q < pos : q > pos; };
    if (alias.passedToCall && llvm::any_of(callPositions, inRange))
      return true;
    for (Value member : alias.members) {
      auto it = byMemref.find(member);
      if (it == byMemref.end())
        continue;
      for (const Entry &e : it->second) {
        if (!inRange(e.first))
          continue;
        const ConflictSummary::Toucher &t = *e.second;
        Operation *op = t.op;
        if (isa<ViewLikeOpInterface>(op))
          continue; // its uses are visited themselves
        bool isLoad = isa<AffineLoadOp>(op), isStore = isa<AffineStoreOp>(op);
        if ((isLoad || isStore) && accessMemref(op) == mem) {
          if (isLoad && !readsConflict)
            continue;
          if (compareAddresses(*t.addr, addr) == AddrRelation::Disjoint)
            continue;
        }
        return true;
      }
    }
    return false;
  }
};

/// The loads of `arm` that no earlier op of the arm may overwrite, and the
/// stores of `arm` that no later op of the arm may read or overwrite, whose
/// memref is tracked and whose address operands are defined outside `ifOp`.
static void movableAccesses(
    IfArm arm, Operation *ifOp,
    function_ref<const MemrefAliasInfo *(Value)> tracked,
    SmallVectorImpl<AffineLoadOp> &loads,
    SmallVectorImpl<AffineStoreOp> &stores, ConflictSummaries &summaries) {
  ArmTouchers touchers(arm.block, summaries);
  for (Operation &op : arm.block->without_terminator()) {
    auto load = dyn_cast<AffineLoadOp>(op);
    if (!load || !definedOutside(load.getMapOperands(), ifOp))
      continue;
    const MemrefAliasInfo *alias = tracked(load.getMemRef());
    if (!alias)
      continue;
    if (!touchers.anyConflict(touchers.position.lookup(&op), /*before=*/true,
                              load.getMemRef(), *alias, accessAddr(load),
                              /*readsConflict=*/false))
      loads.push_back(load);
  }
  for (Operation &op : arm.block->without_terminator()) {
    auto store = dyn_cast<AffineStoreOp>(op);
    if (!store || !definedOutside(store.getMapOperands(), ifOp))
      continue;
    const MemrefAliasInfo *alias = tracked(store.getMemRef());
    if (!alias)
      continue;
    if (!touchers.anyConflict(touchers.position.lookup(&op), /*before=*/false,
                              store.getMemRef(), *alias, accessAddr(store),
                              /*readsConflict=*/true))
      stores.push_back(store);
  }
}

template <typename AccessOp>
static SmallVector<std::pair<AccessOp, AccessOp>>
pairSameAddress(ArrayRef<AccessOp> thenOps, ArrayRef<AccessOp> elseOps) {
  SmallVector<std::pair<AccessOp, AccessOp>> pairs;
  DenseSet<Operation *> used;
  // Each address once (W9 round 23 review D9: the pairs made the composed
  // address of every else access once per then access).
  SmallVector<std::optional<AccessAddr>> elseAddrs(elseOps.size());
  for (AccessOp t : thenOps) {
    std::optional<AccessAddr> tAddr;
    for (unsigned ei = 0; ei < elseOps.size(); ++ei) {
      AccessOp e = elseOps[ei];
      if (used.contains(e) || t.getMemRef() != e.getMemRef())
        continue;
      if (!tAddr)
        tAddr.emplace(accessAddr(t));
      if (!elseAddrs[ei])
        elseAddrs[ei].emplace(accessAddr(e));
      if (compareAddresses(*tAddr, *elseAddrs[ei]) != AddrRelation::Same)
        continue;
      used.insert(e);
      pairs.push_back({t, e});
      break;
    }
  }
  return pairs;
}

/// Rebuilds `ifOp` with one more result per stored value pair and returns the
/// new op; the old one is erased.
static Operation *addIfResults(Operation *ifOp,
                               ArrayRef<std::pair<Value, Value>> yielded) {
  OpBuilder b(ifOp);
  SmallVector<Type> types(ifOp->getResultTypes());
  for (auto [t, e] : yielded)
    types.push_back(t.getType());
  Operation *newIf;
  if (auto sIf = dyn_cast<scf::IfOp>(ifOp)) {
    auto n = scf::IfOp::create(b, sIf.getLoc(), types, sIf.getCondition());
    n.getThenRegion().takeBody(sIf.getThenRegion());
    n.getElseRegion().takeBody(sIf.getElseRegion());
    newIf = n;
  } else {
    auto aIf = cast<AffineIfOp>(ifOp);
    auto n = AffineIfOp::create(b, aIf.getLoc(), types, aIf.getIntegerSet(),
                                aIf.getOperands(), /*withElseRegion=*/true);
    n.getThenRegion().takeBody(aIf.getThenRegion());
    n.getElseRegion().takeBody(aIf.getElseRegion());
    newIf = n;
  }
  for (unsigned armIdx = 0; armIdx < 2; ++armIdx) {
    Operation *term = newIf->getRegion(armIdx).front().getTerminator();
    SmallVector<Value> operands(term->getOperands());
    for (auto [t, e] : yielded)
      operands.push_back(armIdx == 0 ? t : e);
    term->setOperands(operands);
  }
  for (auto [oldRes, newRes] :
       llvm::zip(ifOp->getResults(), newIf->getResults()))
    oldRes.replaceAllUsesWith(newRes);
  ifOp->erase();
  return newIf;
}

/// The affine.loads (and, with `memrefLoads`, the memref.loads) of `op` and
/// of the ifs nested in it, through ifs only (a loop or any other region op
/// ends the search), in program order.
static void collectLoadsThroughIfs(Operation *op, bool memrefLoads,
                                   SmallVectorImpl<Operation *> &out) {
  if (isa<AffineLoadOp>(op) || (memrefLoads && isa<memref::LoadOp>(op))) {
    out.push_back(op);
    return;
  }
  if (!isa<AffineIfOp, scf::IfOp>(op))
    return;
  for (Region &r : op->getRegions())
    for (Block &b : r)
      for (Operation &in : b)
        collectLoadsThroughIfs(&in, memrefLoads, out);
}

/// The memref and the address operands of an affine.load or a memref.load.
static Value loadMemref(Operation *load) {
  if (auto l = dyn_cast<AffineLoadOp>(load))
    return l.getMemRef();
  return cast<memref::LoadOp>(load).getMemRef();
}
static ValueRange loadAddressOperands(Operation *load) {
  if (auto l = dyn_cast<AffineLoadOp>(load))
    return l.getMapOperands();
  return cast<memref::LoadOp>(load).getIndices();
}

/// True when `v` is available before `point` (an op of `block`): defined
/// before it in `block`, or outside `block`'s region.
static bool availableBefore(Value v, Block *block, Operation *point) {
  Block *vb = v.getParentBlock();
  if (vb == block) {
    Operation *def = v.getDefiningOp();
    return !def || def->isBeforeInBlock(point);
  }
  return vb->getParent()->isProperAncestor(block->getParent());
}

/// Vitis GVN load PRE (W9 round 8 review defect 6: class_ece8893 Dehazing
/// update_vmin_vmax reads `blue_hist[i]` in two non-exclusive ifs of one
/// pipelined iteration; kernels w9r8f_pr1 Vitis 1 BRAM, RAM_AUTO_1R1W: one
/// read per iteration; control pr2, another address in the second if, 2
/// BRAM; pr3, a store of the array between the two ifs, keeps both). The
/// loads of one address of one memref made directly in a block and in the
/// ifs nested in its ops, with no op between the first and the last that may
/// write the memref, read one value: GVN makes it available on every path
/// with one load each. They become one load before the first op that holds
/// one of them (`hls.merged_loads` counts the others). The cleanup within a
/// block (cleanupRedundantAccesses) handles the loads of one block; this
/// handles the ones under ifs, which it never reaches.
/// With gvn_memref_loads, memref.loads of the same index values merge the
/// same way: the per-bank loads of a run-time bank read of a complete
/// partition at the shared in-bank offset (VITIS_NOTES N172), when the reads
/// sit in separate ifs (W9r23 review D3: kernel w9r23rev_d1_dyn_same_pred,
/// seven predicated reads of buf[ri[k]][c], Vitis 7 BRAM, before 49; the
/// control d2_dyn_addr_bank, a different address per bank, stays 49).
void AffineToLoopSchedule::mergeConditionalLoads() {
  DenseMap<Value, MemrefAliasInfo> aliasCache;
  auto aliasInfo = [&](Value mem) -> const MemrefAliasInfo & {
    auto it = aliasCache.find(mem);
    if (it == aliasCache.end())
      it = aliasCache.try_emplace(mem, collectMemrefAliases(mem)).first;
    return it->second;
  };
  SmallVector<Block *> blocks;
  getOperation().walk([&](Block *b) { blocks.push_back(b); });
  unsigned merged = 0;
  for (Block *block : blocks) {
    struct Cand {
      Operation *load; // an affine.load or a memref.load
      Operation *top;  // the op of `block` that holds it
    };
    SmallVector<Cand> cands;
    bool nested = false;
    bool memrefLoads = cseLoads && gvnMemrefLoads;
    for (Operation &top : *block) {
      SmallVector<Operation *> loads;
      collectLoadsThroughIfs(&top, memrefLoads, loads);
      for (Operation *l : loads) {
        cands.push_back({l, &top});
        nested |= l != &top;
      }
    }
    if (!nested || cands.size() < 2)
      continue;
    // Bucket the loads by memref and canonical address (an unrolled body
    // has thousands: a pairwise comparison made lab2_hanchen run for over
    // 40 min). Equal canonical maps and operands are the same address.
    std::map<std::vector<const void *>, SmallVector<unsigned, 2>> buckets;
    for (unsigned i = 0; i < cands.size(); ++i) {
      Operation *l = cands[i].load;
      Value mem = loadMemref(l);
      if (!isRootMemref(mem))
        continue;
      std::vector<const void *> key{mem.getAsOpaquePointer()};
      if (auto al = dyn_cast<AffineLoadOp>(l)) {
        AccessAddr addr(al.getAffineMap(), al.getMapOperands());
        key.push_back(addr.map.getAsOpaquePointer());
        for (Value v : addr.operands)
          key.push_back(v.getAsOpaquePointer());
      } else {
        key.push_back(nullptr); // a memref.load: its index values
        for (Value v : loadAddressOperands(l))
          key.push_back(v.getAsOpaquePointer());
      }
      buckets[key].push_back(i);
    }
    // The index of each op of the block, and per memref the number of ops
    // up to each index that may write it (computed when first needed).
    DenseMap<Operation *, unsigned> position;
    SmallVector<Operation *> tops;
    for (Operation &op : *block) {
      position[&op] = tops.size();
      tops.push_back(&op);
    }
    DenseMap<Value, std::vector<unsigned>> writesBefore;
    // The ops of `tops` a merge below erased (loads directly in the block):
    // never walked again (they wrote nothing). Walking them read freed
    // memory: a nondeterministic crash, about 1 run in 10 of held-out
    // Vitis_Libraries writeToDataFrame (W9r22-impl), as the buckets' order
    // follows pointer values.
    DenseSet<Operation *> erasedTops;
    auto writersPrefix = [&](Value mem) -> const std::vector<unsigned> & {
      auto it = writesBefore.find(mem);
      if (it != writesBefore.end())
        return it->second;
      const MemrefAliasInfo &alias = aliasInfo(mem);
      std::vector<unsigned> prefix(tops.size() + 1, 0);
      for (unsigned k = 0; k < tops.size(); ++k)
        prefix[k + 1] =
            prefix[k] +
            (!erasedTops.contains(tops[k]) &&
                     isMemrefWrittenInLoop(alias, tops[k],
                                           /*callsOnlyInLoop=*/true)
                 ? 1
                 : 0);
      return writesBefore.try_emplace(mem, std::move(prefix)).first->second;
    };
    for (auto &[key, group] : buckets) {
      if (group.size() < 2 || llvm::all_of(group, [&](unsigned k) {
            return cands[k].load == cands[k].top;
          }))
        continue; // nothing under an if: the block cleanup's case
      Value mem = loadMemref(cands[group.front()].load);
      if (aliasInfo(mem).escaped)
        continue;
      // No op from the first holder to the last may write the memref.
      Operation *first = cands[group.front()].top;
      Operation *last = cands[group.back()].top;
      const std::vector<unsigned> &prefix = writersPrefix(mem);
      if (prefix[position[last] + 1] != prefix[position[first]])
        continue;
      // A load of the group whose address operands exist before `first`.
      std::optional<unsigned> pick;
      for (unsigned k : group)
        if (llvm::all_of(loadAddressOperands(cands[k].load), [&](Value v) {
              return availableBefore(v, block, first);
            })) {
          pick = k;
          break;
        }
      if (!pick)
        continue;
      OpBuilder b(first);
      Operation *one = b.clone(*cands[*pick].load);
      for (unsigned k : group) {
        cands[k].load->getResult(0).replaceAllUsesWith(one->getResult(0));
        if (cands[k].load == cands[k].top)
          erasedTops.insert(cands[k].top);
        cands[k].load->erase();
      }
      addCounterAttr(one, "hls.merged_loads", group.size() - 1);
      merged += group.size() - 1;
    }
  }
  LLVM_DEBUG(llvm::dbgs() << "merged " << merged
                          << " loads under ifs (GVN load PRE)\n");
}

namespace {
/// The affine accesses of the ops of one block, by memref and address, for
/// the backward search of mergeIfElseAccesses' load forwarding: the nearest
/// earlier op of the block that is a load of the same address or may write
/// it. The scan op by op was quadratic in a fully unrolled body (hlsyn
/// symm-opt-medium: 48,000 arm loads, each scanning up to the start of the
/// pipelined body; over 600 s, OPEN_ISSUES O103 (3)).
///
/// compareAddresses decides two addresses by the difference of their maps:
/// a nonzero constant in some result is Disjoint, zero in all is Same. An
/// address is (shape, constants): the operands and the non-constant part of
/// every result, and the constant term of every result. For two shapes the
/// difference of the non-constant parts is, per result, a constant k or not
/// constant; the difference of two addresses is then k + c_a - c_b in the
/// results where k is constant. So the accesses of one shape that are Same
/// as (or not Disjoint from) a query are those whose constants equal
/// c_a + k in those results, found by a lookup per shape. Any other use of
/// the memref (a non-affine access, a call) leaves the answer Unknown and
/// the caller scans as before.
class BlockAccessIndex {
public:
  enum class Answer { Unknown, None, Earlier, Blocked };
  DenseMap<Operation *, unsigned> position;

  BlockAccessIndex(Block *block, ConflictSummaries &summaries) {
    unsigned pos = 0;
    for (Operation &op : *block) {
      position[&op] = pos;
      const ConflictSummary &s = summaries.get(&op);
      if (s.hasCall)
        callPositions.push_back(pos);
      for (const ConflictSummary::Toucher &t : s.touchers)
        add(t, &op, pos);
      ++pos;
    }
  }

  /// What the backward scan from the op at `pos` finds for a load of `mem`
  /// at `addr` (alias set `alias`); `earlier` receives the load on Earlier.
  Answer query(unsigned pos, Value mem, const MemrefAliasInfo &alias,
               const AccessAddr &addr, Operation *&earlier) {
    if (alias.members.size() != 1 || !alias.members.contains(mem))
      return Answer::Unknown;
    if (alias.passedToCall && !callPositions.empty() &&
        callPositions.front() < pos)
      return Answer::Unknown;
    auto mit = perMemref.find(mem);
    if (mit == perMemref.end())
      return Answer::None;
    MemrefEntries &m = mit->second;
    if (!m.irregular.empty() && m.irregular.front() < pos)
      return Answer::Unknown;
    Constants ca = constantsOf(addr);
    const Entry *best = nullptr;
    bool bestSame = false;
    for (auto &[shape, sh] : m.shapes) {
      if (sh.entries.empty() || sh.entries.front().pos >= pos)
        continue;
      // Per result: the constant difference of the non-constant parts.
      SmallVector<std::optional<int64_t>, 4> k =
          partDifference(addr, sh.entries.front().addr);
      bool full = k.size() == ca.size() &&
                  llvm::all_of(k, [](auto x) { return x.has_value(); });
      uint64_t mask = 0;
      Constants target;
      for (unsigned r = 0; r < k.size() && r < 64; ++r)
        if (k[r]) {
          mask |= uint64_t(1) << r;
          target.push_back(ca[r] + *k[r]);
        }
      const std::vector<unsigned> *bucket =
          sh.bucket(mask, k.size() == ca.size() ? k.size() : 0, full, target);
      if (!bucket)
        continue;
      // The last live entry before pos.
      auto it = llvm::lower_bound(*bucket, pos, [&](unsigned i, unsigned p) {
        return sh.entries[i].pos < p;
      });
      while (it != bucket->begin()) {
        --it;
        const Entry &e = sh.entries[*it];
        if (!e.alive)
          continue;
        if (!best || e.pos > best->pos) {
          best = &e;
          bestSame = full;
        }
        break;
      }
    }
    if (!best)
      return Answer::None;
    if (bestSame && best->topLoad) {
      earlier = best->op;
      return Answer::Earlier;
    }
    return Answer::Blocked;
  }

  /// `op` (an access nested in an op of the block) goes away.
  void erase(Operation *op) {
    auto it = entryOfOp.find(op);
    if (it == entryOfOp.end())
      return;
    it->second.first->entries[it->second.second].alive = false;
    entryOfOp.erase(it);
  }

private:
  using ShapeKey = std::vector<const void *>;
  using Constants = std::vector<int64_t>;
  struct Entry {
    unsigned pos;
    Operation *op;
    bool topLoad; ///< an affine.load that is itself an op of the block
    bool isStore;
    AccessAddr addr;
    bool alive = true;
  };
  struct Shape {
    std::vector<Entry> entries; ///< in position order
    /// Per (mask of the results compared, full): entry indices by the
    /// constants of those results. Full (every result compared): stores and
    /// the block's own loads (Same); otherwise stores only (may alias).
    std::map<std::pair<uint64_t, bool>,
             std::map<Constants, std::vector<unsigned>>>
        buckets;
    const std::vector<unsigned> *bucket(uint64_t mask, unsigned numResults,
                                        bool full, const Constants &target) {
      auto [it, inserted] = buckets.try_emplace({mask, full});
      if (inserted)
        for (unsigned i = 0; i < entries.size(); ++i) {
          const Entry &e = entries[i];
          if (!e.isStore && !(full && e.topLoad))
            continue;
          Constants c = constantsOf(e.addr), proj;
          for (unsigned r = 0; r < c.size() && r < 64; ++r)
            if (mask & (uint64_t(1) << r))
              proj.push_back(c[r]);
          it->second[proj].push_back(i);
        }
      (void)numResults;
      auto b = it->second.find(target);
      return b == it->second.end() ? nullptr : &b->second;
    }
  };
  struct MemrefEntries {
    std::vector<unsigned> irregular; ///< positions of any other use
    std::map<ShapeKey, Shape> shapes;
  };
  DenseMap<Value, MemrefEntries> perMemref;
  DenseMap<Operation *, std::pair<Shape *, unsigned>> entryOfOp;
  SmallVector<unsigned> callPositions;

  static ShapeKey shapeOf(const AccessAddr &a) {
    ShapeKey k;
    for (Value v : a.operands)
      k.push_back(v.getAsOpaquePointer());
    k.push_back(reinterpret_cast<const void *>(
        static_cast<uintptr_t>(a.map.getNumDims())));
    k.push_back(reinterpret_cast<const void *>(
        static_cast<uintptr_t>(a.map.getNumSymbols())));
    k.push_back(reinterpret_cast<const void *>(
        static_cast<uintptr_t>(a.map.getNumResults())));
    for (AffineExpr e : a.map.getResults())
      k.push_back(splitConstantTerm(e).first.getAsOpaquePointer());
    return k;
  }
  static Constants constantsOf(const AccessAddr &a) {
    Constants c;
    for (AffineExpr e : a.map.getResults())
      c.push_back(splitConstantTerm(e).second);
    return c;
  }
  /// `a` without the constant terms of its results.
  static AffineMap partsOf(const AccessAddr &a) {
    SmallVector<AffineExpr, 4> parts;
    for (AffineExpr e : a.map.getResults()) {
      AffineExpr p = splitConstantTerm(e).first;
      parts.push_back(p ? p : getAffineConstantExpr(0, a.map.getContext()));
    }
    return AffineMap::get(a.map.getNumDims(), a.map.getNumSymbols(), parts,
                          a.map.getContext());
  }
  /// Per result, the difference of the non-constant parts of `a` and `b`
  /// when it is a constant (empty when the result counts differ). Memoized
  /// per pair of shapes: it depends on nothing else.
  SmallVector<std::optional<int64_t>, 4>
  partDifference(const AccessAddr &a, const AccessAddr &b) {
    SmallVector<std::optional<int64_t>, 4> k;
    if (a.map.getNumResults() != b.map.getNumResults())
      return k;
    std::pair<ShapeKey, ShapeKey> key{shapeOf(a), shapeOf(b)};
    auto it = differenceCache.find(key);
    if (it != differenceCache.end())
      return it->second;
    AffineValueMap va(partsOf(a), a.operands), vb(partsOf(b), b.operands),
        diff;
    AffineValueMap::difference(va, vb, &diff);
    for (unsigned r = 0, n = diff.getNumResults(); r < n; ++r) {
      if (auto c = dyn_cast<AffineConstantExpr>(diff.getResult(r)))
        k.push_back(c.getValue());
      else
        k.push_back(std::nullopt);
    }
    differenceCache[key] = k;
    return k;
  }
  std::map<std::pair<ShapeKey, ShapeKey>,
           SmallVector<std::optional<int64_t>, 4>>
      differenceCache;

  void add(const ConflictSummary::Toucher &t, Operation *top, unsigned pos) {
    Operation *op = t.op;
    if (isa<ViewLikeOpInterface>(op))
      return; // mayConflict skips it: its uses are visited themselves
    bool isLoad = isa<AffineLoadOp>(op), isStore = isa<AffineStoreOp>(op);
    for (Value v : t.memrefs) {
      MemrefEntries &m = perMemref[v];
      if (!(isLoad || isStore) || accessMemref(op) != v) {
        if (m.irregular.empty() || m.irregular.back() != pos)
          m.irregular.push_back(pos);
        continue;
      }
      Shape &sh = m.shapes[shapeOf(*t.addr)];
      sh.buckets.clear(); // built lazily from the complete entry list
      entryOfOp[op] = {&sh, static_cast<unsigned>(sh.entries.size())};
      sh.entries.push_back({pos, op, /*topLoad=*/isLoad && op == top, isStore,
                            *t.addr});
    }
  }
};
} // namespace

/// Whether replacing `v` in `user` changes the address an affine access
/// records (a map operand of the access, or an affine.apply its maps compose).
static bool changesAnAddress(Operation *user, Value v) {
  if (isa<AffineApplyOp>(user))
    return true;
  if (auto l = dyn_cast<AffineLoadOp>(user))
    return llvm::is_contained(l.getMapOperands(), v);
  if (auto st = dyn_cast<AffineStoreOp>(user))
    return llvm::is_contained(st.getMapOperands(), v);
  return false;
}

void AffineToLoopSchedule::mergeIfElseAccesses() {
  SmallVector<Operation *> ifs; // post-order: inner ifs first
  getOperation().walk([&](Operation *op) {
    if (auto sIf = dyn_cast<scf::IfOp>(op)) {
      if (!sIf.getElseRegion().empty())
        ifs.push_back(op);
    } else if (auto aIf = dyn_cast<AffineIfOp>(op)) {
      if (aIf.hasElse())
        ifs.push_back(op);
    }
  });

  DenseMap<Value, MemrefAliasInfo> aliasCache;
  auto tracked = [&](Value mem) -> const MemrefAliasInfo * {
    if (!isRootMemref(mem))
      return nullptr;
    auto it = aliasCache.find(mem);
    if (it == aliasCache.end())
      it = aliasCache.try_emplace(mem, collectMemrefAliases(mem)).first;
    return it->second.escaped ? nullptr : &it->second;
  };

  unsigned hoisted = 0, sunk = 0, forwarded = 0;
  // A load inside an arm whose address an earlier load before the if already
  // read, with nothing in between that may write it, reads that value (Vitis
  // GVN: `if (y[i] < 0) y[i] = 0; else if (y[i] > 6) y[i] = 6;` reads y[i]
  // once; with the second read the array looked read twice per iteration).
  ConflictSummaries summaries;
  DenseMap<Operation *, std::unique_ptr<AccessAddr>> loadAddrs;
  auto loadAddr = [&](AffineLoadOp l) -> const AccessAddr & {
    auto it = loadAddrs.find(l.getOperation());
    if (it == loadAddrs.end())
      it = loadAddrs
               .try_emplace(l.getOperation(),
                            std::make_unique<AccessAddr>(accessAddr(l)))
               .first;
    return *it->second;
  };
  SmallVector<AffineLoadOp> armLoads;
  getOperation().walk([&](AffineLoadOp load) {
    if (isa_and_present<scf::IfOp, AffineIfOp>(load->getParentOp()))
      armLoads.push_back(load);
  });
  // Per block, built when first searched; dropped when an address in it
  // changes (a forwarded load fed an index).
  DenseMap<Block *, std::unique_ptr<BlockAccessIndex>> blockIndex;
  auto indexOf = [&](Block *block) -> BlockAccessIndex & {
    std::unique_ptr<BlockAccessIndex> &slot = blockIndex[block];
    if (!slot)
      slot = std::make_unique<BlockAccessIndex>(block, summaries);
    return *slot;
  };
  for (AffineLoadOp load : armLoads) {
    const MemrefAliasInfo *alias = tracked(load.getMemRef());
    if (!alias)
      continue;
    AccessAddr addr = accessAddr(load);
    auto conflicts = [&](Operation *op) {
      return mayConflict(op, load.getMemRef(), *alias, addr,
                         /*readsConflict=*/false, summaries);
    };
    AffineLoadOp earlier;
    bool blocked = false;
    for (Operation *cur = load; cur && !earlier && !blocked;) {
      BlockAccessIndex &index = indexOf(cur->getBlock());
      Operation *found = nullptr;
      BlockAccessIndex::Answer answer =
          index.query(index.position.lookup(cur), load.getMemRef(), *alias,
                      addr, found);
      if (answer == BlockAccessIndex::Answer::Earlier) {
        earlier = cast<AffineLoadOp>(found);
        break;
      }
      if (answer == BlockAccessIndex::Answer::Blocked) {
        blocked = true;
        break;
      }
      if (answer == BlockAccessIndex::Answer::Unknown)
      for (Operation *op = cur->getPrevNode(); op; op = op->getPrevNode()) {
        if (auto l = dyn_cast<AffineLoadOp>(op);
            l && l != load && l.getMemRef() == load.getMemRef() &&
            compareAddresses(loadAddr(l), addr) == AddrRelation::Same) {
          earlier = l;
          break;
        }
        if (conflicts(op)) {
          blocked = true;
          break;
        }
      }
      Operation *parent = cur->getParentOp();
      if (!isa_and_present<scf::IfOp, AffineIfOp>(parent))
        break; // only through if arms, never out of a loop body
      cur = parent;
    }
    if (!earlier || blocked)
      continue;
    addCounterAttr(earlier, "hls.merged_loads",
                   1 + counterAttr(load, "hls.merged_loads"));
    // The users' addresses (a loaded index) change with the replacement.
    Value loaded = load.getResult();
    for (Operation *user : loaded.getUsers()) {
      summaries.invalidate(user);
      loadAddrs.erase(user);
      // A summary rebuilt above it records another address (the access
      // composes affine.apply chains): the indexes of the blocks around it
      // are rebuilt from the new summaries.
      if (changesAnAddress(user, loaded))
        for (Operation *a = user; a; a = a->getParentOp())
          blockIndex.erase(a->getBlock());
    }
    load.getResult().replaceAllUsesWith(earlier.getResult());
    for (Operation *a = load; a && !isa<func::FuncOp>(a); a = a->getParentOp()) {
      auto it = blockIndex.find(a->getBlock());
      if (it != blockIndex.end())
        it->second->erase(load);
    }
    summaries.invalidate(load);
    loadAddrs.erase(load.getOperation());
    load.erase();
    ++forwarded;
  }

  for (Operation *ifOp : ifs) {
    IfArm thenArm{&ifOp->getRegion(0).front(), &ifOp->getRegion(0)};
    IfArm elseArm{&ifOp->getRegion(1).front(), &ifOp->getRegion(1)};

    SmallVector<AffineLoadOp> thenLoads, elseLoads;
    SmallVector<AffineStoreOp> thenStores, elseStores;
    // The arms change below (moves, erases, a rebuilt if): summaries are per
    // if.
    summaries.clear();
    movableAccesses(thenArm, ifOp, tracked, thenLoads, thenStores, summaries);
    movableAccesses(elseArm, ifOp, tracked, elseLoads, elseStores, summaries);

    for (auto [t, e] : pairSameAddress<AffineLoadOp>(thenLoads, elseLoads)) {
      t->moveBefore(ifOp);
      addCounterAttr(t, "hls.merged_loads",
                     1 + counterAttr(e, "hls.merged_loads"));
      e.getResult().replaceAllUsesWith(t.getResult());
      e.erase();
      ++hoisted;
    }

    auto storePairs = pairSameAddress<AffineStoreOp>(thenStores, elseStores);
    if (storePairs.empty())
      continue;
    SmallVector<std::pair<Value, Value>> yielded;
    for (auto [t, e] : storePairs)
      yielded.push_back({t.getValueToStore(), e.getValueToStore()});
    unsigned firstNew = ifOp->getNumResults();
    // The stores are rebuilt after the if from the then-arm store, which
    // keeps its map, operands and attributes.
    SmallVector<AffineStoreOp> kept;
    for (auto [t, e] : storePairs) {
      addCounterAttr(t, "hls.merged_if_else_stores",
                     1 + counterAttr(e, "hls.merged_if_else_stores"));
      addCounterAttr(t, "hls.removed_stores",
                     counterAttr(e, "hls.removed_stores"));
      addCounterAttr(t, "hls.forwarded_loads",
                     counterAttr(e, "hls.forwarded_loads"));
      kept.push_back(t);
      e.erase();
    }
    Operation *newIf = addIfResults(ifOp, yielded);
    for (auto [i, store] : llvm::enumerate(kept)) {
      store->moveAfter(newIf);
      store.getValueMutable().assign(newIf->getResult(firstNew + i));
      ++sunk;
    }
    // Keep program order of the sunk stores (moveAfter reverses them).
    for (unsigned i = 1; i < kept.size(); ++i)
      kept[i]->moveAfter(kept[i - 1]);
  }
  LLVM_DEBUG(llvm::dbgs() << "if/else merge: forwarded " << forwarded
                          << " arm loads, hoisted " << hoisted
                          << " loads, sank " << sunk << " stores\n");
}

/// The body of a loop the pass schedules: an affine.for or a pipelined
/// runtime-trip scf.for (isScheduledRuntimeFor).
static Block *loopBody(Operation *loop) {
  if (auto forOp = dyn_cast<AffineForOp>(loop))
    return forOp.getBody();
  return cast<scf::ForOp>(loop).getBody();
}

/// Returns true if `forOp` contains no loop of any kind anywhere in its body
/// (including inside ifs). MODIFIED (T3): an scf.for / scf.while inside an
/// affine.for used to make that affine.for "innermost" and sent it to the
/// scheduler, which has no operator type for the inner loop; such a loop is
/// sequential control around the inner loop, like an affine.for nest whose
/// inner loop is the pipelined one.
static bool isInnermostAffineFor(AffineForOp forOp) {
  bool hasNested = false;
  forOp.getBody()->walk([&](Operation *op) {
    if (!isa<LoopLikeOpInterface>(op))
      return WalkResult::advance();
    hasNested = true;
    return WalkResult::interrupt();
  });
  return !hasNested;
}

/// MODIFIED (T3): the pipeline terminator requires every yielded value to be
/// produced by a pipeline stage, and the stage plumbing only finds a value
/// yielded straight from a multicycle op (an fadd accumulator) when the
/// terminator happens to be scheduled when that op completes. Every yielded
/// value therefore goes through an identity `arith.select %true, %v, %v`
/// (a comb op, zero latency, scheduled once the value is ready): a loop that
/// yields one of its own iter_args or a value defined outside it (a shift
/// register: `affine.yield %new, %prev`) and the promoted `acc[k] +=`
/// accumulators of an unrolled body are both handled by that.
static void materializeYieldedValues(Operation *loop) {
  Operation *yield = loopBody(loop)->getTerminator();
  Value trueVal;
  OpBuilder b(yield);
  for (OpOperand &opd : yield->getOpOperands()) {
    Value v = opd.get();
    if (!trueVal) {
      OpBuilder ob(loop);
      trueVal = arith::ConstantOp::create(ob, loop->getLoc(),
                                          ob.getBoolAttr(true));
    }
    opd.set(arith::SelectOp::create(b, yield->getLoc(), trueVal, v, v));
  }
}

/// MODIFIED: Returns true if the perfect band has a rectangular iteration
/// space, i.e. every non-outermost loop's bounds are invariant with respect
/// to all enclosing IVs in the band. Flattening via coalesceLoops is only
/// valid in that case (trip count = product of per-loop trip counts);
/// affine::coalesceLoops does NOT reject non-rectangular nests gracefully -
/// it hoists the upper-bound product above the outermost loop, where an
/// outer-IV-dependent bound operand is undefined, and corrupts the IR
/// (null operands) instead of returning failure. So we must check here.
static bool isRectangularBand(ArrayRef<AffineForOp> band) {
  // Op handles are value-like wrappers around Operation*, but their
  // generated accessors are not const-qualified, so copy out of the
  // ArrayRef before calling getRegion().
  AffineForOp outermost = band.front();
  Region &outerRegion = outermost.getRegion();
  for (AffineForOp loop : band.drop_front()) {
    if (!areValuesDefinedAbove(loop.getLowerBoundOperands(), outerRegion) ||
        !areValuesDefinedAbove(loop.getUpperBoundOperands(), outerRegion))
      return false;
  }
  return true;
}

/// A ModuloProblem with the operations, operator types, resources and
/// dependences of a CyclicProblem (the dependence model cached-o1).
static ModuloProblem copyToModuloProblem(CyclicProblem &prob) {
  ModuloProblem modProb(prob.getContainingOp());
  for (auto *op : prob.getOperations()) {
    auto opr = prob.getLinkedOperatorType(op);
    if (opr.has_value()) {
      modProb.setLinkedOperatorType(op, opr.value());
      auto latency = prob.getLatency(opr.value());
      if (latency.has_value())
        modProb.setLatency(opr.value(), latency.value());
    }
    auto rsrc = prob.getLinkedResourceTypes(op);
    if (rsrc.has_value())
      modProb.setLinkedResourceTypes(op, rsrc.value());
    modProb.insertOperation(op);
  }

  for (auto *op : prob.getOperations()) {
    for (auto dep : prob.getDependences(op)) {
      if (dep.isAuxiliary()) {
        auto depInserted = modProb.insertDependence(dep);
        assert(succeeded(depInserted));
        (void)depInserted;
      }
      auto distance = prob.getDistance(dep);
      if (distance.has_value())
        modProb.setDistance(dep, distance.value());
    }
  }

  return modProb;
}

ModuloProblem AffineToLoopSchedule::getModuloProblem(CyclicProblem &prob) {
  return copyToModuloProblem(prob);
}

/// MODIFIED: Flatten perfectly nested loop bands into single loops using
/// affine::coalesceLoops. This runs *before* dependence analysis so all
/// later analyses see the flattened IR.
///
/// coalesceLoops introduces delinearization of the flat IV via affine.apply
/// ops containing floordiv/mod; those are expanded to arith ops in
/// lowerAffineStructures and scheduled as multicycle/comb ops.
///
/// Bands that cannot be coalesced (e.g. inner bounds depending on outer
/// IVs) are simply left alone; their innermost loops are pipelined in place
/// later, with the outer loops remaining as sequential affine.for control.
/// VITIS_NOTES N65 (kernels w9r8p_fl_pre / fl_pre2; class_ece8893 ben_hall
/// lab3): when --auto-pipeline-unroll flattens the loops above a pipelined
/// loop C into it (hls.flattened_parents, N3 (3)), Vitis sinks the
/// straight-line code of those loops' bodies into the flattened pipeline,
/// guarded by the predicate of the first iteration of the loops below it,
/// and allocates its ports there: `for i, for k { t[j] = A[i][k] * B[k][j]
/// (j unrolled); for jj (pipelined, flattened) ... }` reads B 64 times per
/// pipeline iteration (Vitis II 2, B RAM_1WNR 60). Does the same in the IR:
/// the code before the child loop in a flattened parent's body moves to the
/// start of C's body under `affine.if` (every loop from the parent's child
/// down to C at its lower bound), so that the scheduler and --bram-analysis
/// see it in the pipeline. Only code without loops, whose values nothing
/// outside it uses, in parents without iter_args, and only when it accesses
/// memory (register code costs no port); the code after the child loop
/// stays where it is (not measured).
void AffineToLoopSchedule::sinkFlattenedParentCode() {
  SmallVector<AffineForOp> pipelined;
  getOperation().walk([&](AffineForOp loop) {
    if (circt::hls_analysis::getFlattenedParents(loop) > 0 &&
        loop->hasAttr(circt::hls_analysis::kLoopPipelineAttr))
      pipelined.push_back(loop);
  });
  for (AffineForOp c : pipelined) {
    unsigned n = circt::hls_analysis::getFlattenedParents(c);
    // The loops from C up to its n-th ancestor, each directly in the body
    // of the next.
    SmallVector<AffineForOp> chain{c};
    for (unsigned l = 0; l < n; ++l) {
      auto p = dyn_cast<AffineForOp>(chain.back()->getParentOp());
      if (!p)
        break;
      chain.push_back(p);
    }
    for (unsigned l = 1; sinkParentCode && l < chain.size(); ++l) {
      AffineForOp parent = chain[l];
      Operation *below = chain[l - 1];
      if (parent.getNumIterOperands() != 0)
        break;
      SmallVector<Operation *> pre;
      bool ok = true, accessesMemory = false;
      for (Operation &op : *parent.getBody()) {
        if (&op == below)
          break;
        bool hasLoop = isa<AffineForOp, scf::ForOp, scf::WhileOp>(op);
        op.walk([&](Operation *in) {
          if (in != &op && isa<AffineForOp, scf::ForOp, scf::WhileOp>(in))
            hasLoop = true;
          if (isa<AffineReadOpInterface, AffineWriteOpInterface,
                  memref::LoadOp, memref::StoreOp>(in))
            accessesMemory = true;
          if (isa<CallOpInterface>(in))
            hasLoop = true; // a call: not straight-line code we model
        });
        if (hasLoop) {
          ok = false;
          break;
        }
        pre.push_back(&op);
      }
      if (!ok || pre.empty() || !accessesMemory)
        continue;
      llvm::SmallPtrSet<Operation *, 16> moved(pre.begin(), pre.end());
      for (Operation *op : pre)
        for (Value r : op->getResults())
          for (Operation *u : r.getUsers()) {
            Operation *top = u;
            while (top && top->getBlock() != parent.getBody())
              top = top->getParentOp();
            if (!top || !moved.contains(top))
              ok = false;
          }
      // The guard: every loop from `below` down to C at its lower bound.
      SmallVector<AffineExpr> exprs;
      SmallVector<bool> eqs;
      SmallVector<Value> dims;
      for (unsigned k = 0; k < l && ok; ++k) {
        AffineForOp inner = chain[k];
        std::optional<uint64_t> trip = getConstantTripCount(inner);
        if (!inner.hasConstantLowerBound() || !trip || *trip == 0) {
          ok = false;
          break;
        }
        exprs.push_back(getAffineDimExpr(dims.size(), c.getContext()) -
                        inner.getConstantLowerBound());
        eqs.push_back(true);
        dims.push_back(inner.getInductionVar());
      }
      if (!ok)
        continue;
      IntegerSet set = IntegerSet::get(dims.size(), 0, exprs, eqs);
      OpBuilder b(c.getBody(), c.getBody()->begin());
      auto guard = AffineIfOp::create(b, parent.getLoc(), set, dims,
                                      /*withElseRegion=*/false);
      Block *then = guard.getThenBlock();
      for (Operation *op : pre)
        op->moveBefore(then->getTerminator());
      guard->setAttr("hls.flattened_parent_code",
                     b.getI64IntegerAttr(static_cast<int64_t>(l)));
    }
    if (sinkParentTrailingCode)
      sinkTrailingParentCode(c, chain);
  }
}

/// VITIS_NOTES N97 (b) (kernel w9r13p_st_row; class_ece8893 anuvab / ayush
/// lab2 `rOut`): the code after the child loop in a flattened parent's body
/// runs in the flattened pipeline too, in the last iteration of the loops
/// below the parent: `for i { for j (pipelined, flattened) t.d[j] = ..;
/// s.write(t); }` packs t into the stream word inside the i x j pipeline
/// (Vitis t RAM_1WNR 16 copies). Moves it to the end of C's body under
/// `affine.if` (every loop from the parent's child down to C at its last
/// iteration). Only code without loops (a call is allowed when its callee
/// has no body: a stream method), whose values nothing before it uses, in
/// parents without iter_args, and only when it accesses memory.
/// Whether the store `op` writes a local that only stores fill and only
/// calls of functions without a body read (through casts): the temporary
/// cgeist makes for a struct passed by reference to `hls::stream::write`,
/// part of the stream write N97 (b) sinks, not an array the design reads.
static bool stagesExternalCallArgument(Operation *op) {
  Value mem;
  if (auto st = dyn_cast<memref::StoreOp>(op))
    mem = st.getMemRef();
  else if (auto st = dyn_cast<AffineWriteOpInterface>(op))
    mem = st.getMemRef();
  while (auto cast = mem ? mem.getDefiningOp<memref::CastOp>() : nullptr)
    mem = cast.getSource();
  if (!mem || !mem.getDefiningOp<memref::AllocaOp>())
    return false;
  bool externalCall = false;
  SmallVector<Value> work{mem};
  while (!work.empty()) {
    Value v = work.pop_back_val();
    for (Operation *user : v.getUsers()) {
      if (auto cast = dyn_cast<memref::CastOp>(user)) {
        work.push_back(cast.getResult());
        continue;
      }
      if (auto st = dyn_cast<memref::StoreOp>(user)) {
        if (st.getMemRef() != v)
          return false;
        continue;
      }
      if (auto st = dyn_cast<AffineWriteOpInterface>(user)) {
        if (st.getMemRef() != v)
          return false;
        continue;
      }
      auto call = dyn_cast<func::CallOp>(user);
      if (!call)
        return false;
      auto callee = SymbolTable::lookupNearestSymbolFrom<func::FuncOp>(
          call, call.getCalleeAttr());
      if (!callee || !callee.isExternal())
        return false;
      externalCall = true;
    }
  }
  return externalCall;
}

void AffineToLoopSchedule::sinkTrailingParentCode(
    AffineForOp c, ArrayRef<AffineForOp> chain) {
  for (unsigned l = 1; l < chain.size(); ++l) {
    AffineForOp parent = chain[l];
    Operation *below = chain[l - 1];
    if (parent.getNumIterOperands() != 0)
      break;
    SmallVector<Operation *> post;
    bool ok = true, accessesMemory = false;
    // W9r14 review (kernel w9r14rv_st_arr): trailing stores to an output
    // array make Vitis disable the flatten ([HLS 214-437]) and pipeline the
    // child alone; only a stream write after the child is measured to
    // flatten (st_row, rOut). Code that writes memory stays where it is.
    const bool sinkStores = circt::hlsest::Config::get()
                                .tool.hls.pipelineDecision
                                .sinkParentTrailingStores;
    for (Operation *op = below->getNextNode();
         op && op != parent.getBody()->getTerminator();
         op = op->getNextNode()) {
      bool bad = false;
      op->walk([&](Operation *in) {
        if (isa<AffineForOp, scf::ForOp, scf::WhileOp>(in))
          bad = true;
        if (isa<AffineReadOpInterface, AffineWriteOpInterface,
                memref::LoadOp, memref::StoreOp>(in))
          accessesMemory = true;
        if (!sinkStores && isa<AffineWriteOpInterface, memref::StoreOp>(in) &&
            !stagesExternalCallArgument(in))
          bad = true;
        // A result of the child loop (its iter_args' final value) exists
        // only after the loop.
        for (Value v : in->getOperands())
          if (v.getDefiningOp() == below)
            bad = true;
        if (auto call = dyn_cast<func::CallOp>(in)) {
          auto callee = SymbolTable::lookupNearestSymbolFrom<func::FuncOp>(
              call, call.getCalleeAttr());
          if (!callee || !callee.isExternal())
            bad = true; // a kept function: not straight-line code we model
        } else if (isa<CallOpInterface>(in)) {
          bad = true;
        }
      });
      if (bad) {
        ok = false;
        break;
      }
      post.push_back(op);
    }
    if (!ok || post.empty() || !accessesMemory)
      continue;
    // The guard: every loop from `below` down to C at its last iteration.
    SmallVector<AffineExpr> exprs;
    SmallVector<bool> eqs;
    SmallVector<Value> dims;
    for (unsigned k = 0; k < l && ok; ++k) {
      AffineForOp inner = chain[k];
      std::optional<uint64_t> trip = getConstantTripCount(inner);
      if (!inner.hasConstantLowerBound() || !trip || *trip == 0) {
        ok = false;
        break;
      }
      int64_t last = inner.getConstantLowerBound() +
                     static_cast<int64_t>(*trip - 1) * inner.getStepAsInt();
      exprs.push_back(getAffineDimExpr(dims.size(), c.getContext()) - last);
      eqs.push_back(true);
      dims.push_back(inner.getInductionVar());
    }
    if (!ok)
      continue;
    IntegerSet set = IntegerSet::get(dims.size(), 0, exprs, eqs);
    OpBuilder b(c.getBody()->getTerminator());
    auto guard = AffineIfOp::create(b, parent.getLoc(), set, dims,
                                    /*withElseRegion=*/false);
    Block *then = guard.getThenBlock();
    for (Operation *op : post) {
      op->moveBefore(then->getTerminator());
      // Debug provenance: the moved accesses and calls keep the mark through
      // the lowering (hls.* attributes of accesses survive it), so
      // --bram-debug can count them per pipeline.
      op->walk([&](Operation *in) {
        if (isa<AffineReadOpInterface, AffineWriteOpInterface, memref::LoadOp,
                memref::StoreOp, CallOpInterface>(in))
          in->setAttr(circt::hls_analysis::kSunkTrailingCodeAttr, b.getI64IntegerAttr(
                                                 static_cast<int64_t>(l)));
      });
    }
    guard->setAttr("hls.flattened_parent_trailing_code",
                   b.getI64IntegerAttr(static_cast<int64_t>(l)));
  }
}

void AffineToLoopSchedule::uniqueGlobalRefs() {
  func::FuncOp func = getOperation();
  if (func.isExternal())
    return;
  llvm::MapVector<Attribute, SmallVector<memref::GetGlobalOp, 2>> refs;
  func.walk(
      [&](memref::GetGlobalOp g) { refs[g.getNameAttr()].push_back(g); });
  Block &entry = func.front();
  for (auto &[name, ops] : llvm::reverse(refs)) {
    memref::GetGlobalOp first = ops.front();
    first->moveBefore(&entry, entry.begin());
    for (memref::GetGlobalOp other : ArrayRef(ops).drop_front()) {
      if (other.getType() != first.getType())
        continue;
      for (NamedAttribute attr : other->getAttrs())
        if (!first->hasAttr(attr.getName()))
          first->setAttr(attr.getName(), attr.getValue());
      other.replaceAllUsesWith(first.getResult());
      other.erase();
    }
  }
}

void AffineToLoopSchedule::coalescePerfectNests() {
  // Collect maximal perfect bands first (pre-order so outer bands are found
  // before any inner siblings), then mutate after the walk completes.
  SmallVector<SmallVector<AffineForOp>> bands;
  DenseSet<Operation *> visited;
  getOperation().walk<WalkOrder::PreOrder>([&](AffineForOp root) {
    if (visited.contains(root))
      return;
    SmallVector<AffineForOp> band;
    getPerfectlyNestedLoops(band, root);
    for (AffineForOp loop : band)
      visited.insert(loop);
    // A loop Vitis does not flatten into the pipeline inside it
    // (hls.flatten_refused, --auto-pipeline-unroll, VITIS_NOTES N96) stays
    // a loop of its own: only the members inside the innermost such loop
    // are coalesced.
    for (unsigned i = band.size(); i-- > 0;)
      if (band[i]->hasAttr(circt::hls_analysis::kLoopFlattenRefusedAttr)) {
        band.erase(band.begin(), band.begin() + i + 1);
        break;
      }
    if (band.size() < 2)
      return;
    // Only worth coalescing if the band actually ends in an innermost loop;
    // otherwise the flattened loop still would not be pipelineable.
    // MODIFIED: additionally require a rectangular iteration space, since
    // coalesceLoops silently miscompiles triangular/trapezoidal nests
    // instead of failing (see isRectangularBand). Non-rectangular nests
    // fall back to innermost-loop pipelining.
    // MODIFIED (T3): affine::coalesceLoops erases every loop but the
    // outermost and cannot carry an inner loop's results (iter_args chained
    // through two levels: "operation destroyed but still has uses"); such a
    // band is left as a nest whose innermost loop is pipelined in place.
    bool innerResults = llvm::any_of(
        ArrayRef<AffineForOp>(band).drop_front(),
        [](AffineForOp loop) { return loop.getNumResults() != 0; });
    if (band.size() > 1 && isInnermostAffineFor(band.back()) &&
        isRectangularBand(band) && !innerResults)
      bands.push_back(std::move(band));
  });

  for (auto &band : bands) {
    // MODIFIED (T3): the pipeline tags of --auto-pipeline-unroll sit on the
    // innermost loop, which coalesceLoops erases. Carry them to the loop
    // that survives and discount the band's own levels from
    // hls.flattened_parents: they are part of the coalesced loop now.
    AffineForOp innermost = band.back();
    Attribute pipelineTag =
        innermost->getAttr(circt::hls_analysis::kLoopPipelineAttr);
    Attribute pipelineOff =
        innermost->getAttr(circt::hls_analysis::kLoopPipelineOffAttr);
    Attribute autoUnrolled =
        innermost->getAttr(circt::hls_analysis::kLoopAutoUnrolledAttr);
    Attribute unrollPartial =
        innermost->getAttr(circt::hls_analysis::kLoopUnrollPartialAttr);
    Attribute foldedGuards =
        innermost->getAttr(circt::hls_analysis::kFoldedGuardsAttr);
    Attribute pinnedOperands =
        innermost->getAttr(circt::hls_analysis::kPinnedGuardOperandsAttr);
    unsigned flattened = circt::hls_analysis::getFlattenedParents(innermost);
    unsigned levels = band.size() - 1;
    if (failed(coalesceLoops(MutableArrayRef<AffineForOp>(band)))) {
      LLVM_DEBUG(llvm::dbgs()
                 << "Could not coalesce perfect nest rooted at "
                 << *band.front()
                 << "; falling back to innermost-loop pipelining\n");
      continue;
    }
    AffineForOp outer = band.front();
    if (pipelineTag)
      outer->setAttr(circt::hls_analysis::kLoopPipelineAttr, pipelineTag);
    if (pipelineOff)
      outer->setAttr(circt::hls_analysis::kLoopPipelineOffAttr, pipelineOff);
    if (autoUnrolled)
      outer->setAttr(circt::hls_analysis::kLoopAutoUnrolledAttr, autoUnrolled);
    if (unrollPartial)
      outer->setAttr(circt::hls_analysis::kLoopUnrollPartialAttr,
                     unrollPartial);
    if (foldedGuards)
      outer->setAttr(circt::hls_analysis::kFoldedGuardsAttr, foldedGuards);
    if (pinnedOperands)
      outer->setAttr(circt::hls_analysis::kPinnedGuardOperandsAttr,
                     pinnedOperands);
    if (flattened > levels)
      outer->setAttr(circt::hls_analysis::kLoopFlattenedParentsAttr,
                     IntegerAttr::get(IntegerType::get(outer.getContext(), 64),
                                      flattened - levels));
    else
      outer->removeAttr(circt::hls_analysis::kLoopFlattenedParentsAttr);
  }
}

// Anchor memref-level write-effecting ops (e.g. hls.store_enable) that
// MemoryDependenceAnalysis can't see. Without an outgoing edge the scheduler
// treats them as sinks; give each an auxiliary dependence to the loop
// terminator so the dependence DAG has a single sink.
static void anchorUntrackedSideEffects(Operation *loop,
                                       ModuloProblem &problem) {
  Operation *anchor = loopBody(loop)->getTerminator();

  SmallVector<Operation *> ops(problem.getOperations().begin(),
                               problem.getOperations().end());

  // Every op that is already the source of some intra-iteration dependence
  // has an outgoing edge; everything else is a sink. A loop-carried edge
  // (distance > 0) does not count: the simplex scheduler's single-sink check
  // ignores it too (a call bound to its own instance, chainSharedCallee-
  // Instances, reported "multiple sinks detected" and fell back to the greedy
  // scheduler on 9 catalogue designs before the W9r13 review fixes).
  DenseSet<Operation *> hasSuccessor;
  for (Operation *op : ops)
    for (auto dep : problem.getDependences(op))
      if (Operation *src = dep.getSource())
        if (problem.getDistance(dep).value_or(0) == 0)
          hasSuccessor.insert(src);

  for (Operation *op : ops) {
    if (op == anchor || hasSuccessor.contains(op))
      continue;
    Problem::Dependence dep(op, anchor);
    auto inserted = problem.insertDependence(dep);
    (void)inserted;
    assert(succeeded(inserted) && "failed to anchor sink");
  }
}

// VITIS_NOTES N154: the read-modify-write of a run-time lane of an
// aggregated word stays in memory, so the next iteration's load of the word
// comes after this iteration's store (tagMemoryRecurrences tags the pairs).
static void addLaneRecurrenceEdges(Operation *loop, ModuloProblem &problem) {
  DenseMap<int64_t, Operation *> stores;
  SmallVector<std::pair<int64_t, Operation *>> loads;
  loopBody(loop)->walk([&](Operation *op) {
    auto ids = op->getAttrOfType<DenseI64ArrayAttr>(kLaneRecurrenceAttr);
    if (!ids || !problem.hasOperation(op))
      return;
    for (int64_t id : ids.asArrayRef()) {
      if (id >= 0)
        stores[id] = op;
      else
        loads.push_back({-1 - id, op});
    }
  });
  for (auto [id, load] : loads) {
    Operation *store = stores.lookup(id);
    if (!store || store == load)
      continue;
    Problem::Dependence dep(store, load);
    if (succeeded(problem.insertDependence(dep)))
      problem.setDistance(dep, 1);
  }
}

// W3 (VITIS_NOTES.md N14 R2 in a pipelined loop): calls of one iteration to
// the same defined callee that share an instance - they access a common
// array, a value of one reaches the other, or the function limits the
// callee's instances (`allocation function ... limit=N`) - run one after the
// other on that instance, each for its whole depth (latency + 1 states), in
// Vitis a carried dependence between the call operations (`[HLS 200-880]`).
// Chain them in program order with the depth as the latency of each call
// and close the chain across iterations (distance 1), so the II is at least
// the sum of the depths: inl_e3 / w3rev_k4 2 x 2 = II 4, w3rev_k2 2 x 3 = 6,
// w3fx_d4_three 3 x 2 = 6, w3fx_d4_rd4 2 x 4 = 8 (W3 review D4). The depth
// is hls.call_depth from --auto-pipeline-unroll, or the call's latency + 1
// without it. Independent calls keep their own instances and overlap
// (inl_c4: II 1).
static void chainSharedCalleeInstances(Operation *loop,
                                       ModuloProblem &problem) {
  auto parent = loop->getParentOfType<func::FuncOp>();
  if (!parent)
    return;
  llvm::MapVector<Operation *, SmallVector<Operation *>> byCallee;
  loopBody(loop)->walk([&](CallOpInterface call) {
    if (!problem.hasOperation(call.getOperation()))
      return;
    if (func::FuncOp callee = resolveDefinedCallee(call))
      byCallee[callee.getOperation()].push_back(call.getOperation());
  });
  // One call alone on its instance: the next iteration's call waits until
  // this one has released the instance, so the II is at least the call's
  // occupancy (hls.call_occupancy from --auto-pipeline-unroll; N14 R7,
  // inl_f2_unroll_off: 16 accesses of each row per call, II 8).
  auto boundBySelf = [&](Operation *call) {
    auto occ = call->getAttrOfType<IntegerAttr>(
        circt::hls_analysis::kCallOccupancyAttr);
    if (!occ || occ.getInt() <= 1)
      return;
    Problem::Dependence self(call, call);
    if (succeeded(problem.insertDependence(self)))
      problem.setDistance(self, 1);
  };
  // A call that shares its instance with another call of the iteration
  // holds it for its whole depth: hls.call_depth, else its latency + 1.
  auto holdForDepth = [&](Operation *call) {
    unsigned depth = 0;
    if (auto d = call->getAttrOfType<IntegerAttr>(
            circt::hls_analysis::kCallDepthAttr))
      depth = static_cast<unsigned>(std::max<int64_t>(1, d.getInt()));
    else if (auto opr = problem.getLinkedOperatorType(call))
      depth = problem.getLatency(*opr).value_or(0) + 1;
    if (depth == 0)
      return;
    Problem::OperatorType held = problem.getOrInsertOperatorType(
        "call_kept_held_" + std::to_string(depth));
    problem.setLatency(held, depth);
    problem.setLinkedOperatorType(call, held);
  };
  // A call whose callee reads and writes one global array (hls.callee_
  // global_recurrence, VITIS_NOTES N102): the next iteration's call reads
  // what this one writes, so it waits for this call's whole depth
  // (w9r13rev_gl_call: `hist[k & 7] += 1` in an inline-off callee, II 2;
  // gl_callw, a store only, II 1).
  auto recurrentAlone = [&](Operation *call) {
    if (!call->hasAttr(circt::hls_analysis::kCalleeGlobalRecurrenceAttr))
      return false;
    holdForDepth(call);
    Problem::Dependence self(call, call);
    if (succeeded(problem.insertDependence(self)))
      problem.setDistance(self, 1);
    return true;
  };
  for (auto &[calleeOp, sites] : byCallee) {
    if (sites.size() < 2) {
      if (!recurrentAlone(sites.front()))
        boundBySelf(sites.front());
      continue;
    }
    auto callee = cast<func::FuncOp>(calleeOp);
    SmallVector<unsigned> group;
    groupConcurrentCalls(parent, sites, allocationLimit(parent, callee),
                         group);
    llvm::MapVector<unsigned, SmallVector<Operation *>> chains;
    for (unsigned i = 0; i < sites.size(); ++i)
      chains[group[i]].push_back(sites[i]);
    for (auto &[g, chain] : chains) {
      if (chain.size() < 2) {
        if (!recurrentAlone(chain.front()))
          boundBySelf(chain.front());
        continue;
      }
      for (Operation *call : chain)
        holdForDepth(call);
      for (unsigned k = 1; k < chain.size(); ++k)
        (void)problem.insertDependence(
            Problem::Dependence(chain[k - 1], chain[k]));
      Problem::Dependence back(chain.back(), chain.front());
      if (succeeded(problem.insertDependence(back)))
        problem.setDistance(back, 1);
    }
  }
}

// MODIFIED (T4): a region op of the body (an scf.if left by the if hoisting,
// whose branches only yield values computed in front of it) uses values
// through its nested terminators, which are not operands of the op itself,
// so the problem had no edge from their producers to the op. The scheduler
// could then start the scf.if before (or in another stage than) a value its
// yield returns; the clone of the if kept the original value, which the loop
// erasure nulled ("null operand found" on spector_hls sobel_filter_x/y).
// Add an auxiliary dependence from the producer of every value captured by a
// nested op to the region op.
static void anchorRegionCaptures(Operation *loop, ModuloProblem &problem) {
  Block *body = loopBody(loop);
  for (Operation &regionOp : body->without_terminator()) {
    if (regionOp.getNumRegions() == 0 || !problem.hasOperation(&regionOp))
      continue;
    regionOp.walk([&](Operation *nested) {
      if (nested == &regionOp)
        return;
      for (Value v : nested->getOperands()) {
        Operation *def = v.getDefiningOp();
        if (!def || def == &regionOp || def->getBlock() != body ||
            !problem.hasOperation(def))
          continue;
        auto inserted =
            problem.insertDependence(Problem::Dependence(def, &regionOp));
        (void)inserted;
      }
    });
  }
}

/// MODIFIED: Fully unroll constant-trip innermost reduction loops so the
/// loop *above* them becomes the pipelineable innermost loop, matching
/// Vitis HLS behavior ("pipeline 2nd-level loop, unroll lower loop"). The
/// unrolled inner body exposes one memref.load per (bank, iteration) so the
/// partitioned arrays are actually read in parallel; otherwise the inner
/// reduction would serialize and the array_partition would be wasted.
///
/// Targets only innermost affine.for loops with a small constant trip count
/// that carry a reduction (iter_args)
void AffineToLoopSchedule::unrollInnerReductions() {
  SmallVector<AffineForOp> targets;
  // TODO: automatically unroll loop count with trips < 64
  //       paramterize later (Vitis specific behavior)
  
  unsigned kMaxUnrollTrip = 64;
  
  getOperation().walk([&](AffineForOp forOp) {
    if (!isInnermostAffineFor(forOp))
      return;
    // Reduction: carries iter_args (the accumulator).
    if (forOp.getNumIterOperands() == 0)
      return;
    auto tc = getConstantTripCount(forOp);
    if (!tc || *tc == 0)
      return;
    // Guard against unrolling something huge; the HLS inner dim is small.
    if (*tc > kMaxUnrollTrip)   // e.g. 64
      return;
    targets.push_back(forOp);
  });

  for (AffineForOp forOp : targets) {
    if (failed(circt::hls_analysis::hlsLoopUnrollFull(forOp))) {
      LLVM_DEBUG(llvm::dbgs()
                 << "could not fully unroll inner reduction: " << *forOp << "\n");
    }
  }
}


//===----------------------------------------------------------------------===//
// Pre-scheduling CSE of side-effect-free ops
//===----------------------------------------------------------------------===//
namespace {
// DenseMapInfo keyed on structural op equivalence (same op, attributes, operand
// values and result types; locations ignored), as mlir::CSE does.
struct PureOpInfo : public llvm::DenseMapInfo<Operation *> {
  static unsigned getHashValue(const Operation *opC) {
    return OperationEquivalence::computeHash(
        const_cast<Operation *>(opC),
        /*hashOperands=*/OperationEquivalence::directHashValue,
        /*hashResults=*/OperationEquivalence::ignoreHashValue,
        OperationEquivalence::IgnoreLocations);
  }
  static bool isEqual(const Operation *lhsC, const Operation *rhsC) {
    auto *lhs = const_cast<Operation *>(lhsC);
    auto *rhs = const_cast<Operation *>(rhsC);
    if (lhs == rhs)
      return true;
    // Entries are never erased, so no tombstone can be compared (as in
    // mlir/lib/Transforms/Utils/CSE.cpp).
    if (lhs == getEmptyKey() || rhs == getEmptyKey())
      return false;
    return OperationEquivalence::isEquivalentTo(
        lhs, rhs, OperationEquivalence::IgnoreLocations);
  }
};
} // namespace

/// Merge every later duplicate of a side-effect-free, region-free,
/// non-terminator op into the first occurrence within the same block. Nested
/// blocks are processed with their own scope. Ops with memory effects (loads,
/// stores, store_enables) are never candidates, so the number and order of
/// memory accesses is preserved exactly. Returns the number of ops erased.
static unsigned cseBlockPureOps(Block &block) {
  unsigned merged = 0;
  DenseSet<Operation *, PureOpInfo> seen;
  for (Operation &op : llvm::make_early_inc_range(block)) {
    for (Region &region : op.getRegions())
      for (Block &nested : region)
        merged += cseBlockPureOps(nested);
    if (op.getNumRegions() != 0 || op.getNumResults() == 0 ||
        op.hasTrait<OpTrait::IsTerminator>() || !isMemoryEffectFree(&op))
      continue;
    auto [it, inserted] = seen.insert(&op);
    if (inserted)
      continue;
    op.replaceAllUsesWith(*it);
    op.erase();
    ++merged;
  }
  return merged;
}

//===----------------------------------------------------------------------===//
// Greedy resource-bound modulo scheduler (fast path for large loop bodies)
//===----------------------------------------------------------------------===//
// The ModuloSimplexScheduler fixes one resource-limited op at a time and
// re-solves the LP after each, which is cubic in the body size; a 64-way
// unrolled body with ~700 memory ops takes minutes. This scheduler produces a
// valid ModuloProblem solution in O(II * (V + E)) per II candidate:
//
//   1. II starts at ResMinII = max over resources of ceil(uses / limit).
//   2. Resource-free ASAP times are the longest paths in the constraint graph
//      (edge weight latency - distance * II). A positive cycle means a
//      recurrence cannot close within II (what makes the simplex raise its
//      parameter T). Feasibility is monotone in II (a cycle's slack is
//      distance_sum * II - latency_sum, and every cycle has distance >= 1),
//      so the recurrence-feasible II is found by galloping plus bisection:
//      O(log II) positive-cycle tests instead of one per candidate II.
//   3. Ops are placed in a topological order of the intra-iteration (distance
//      0) edges, ties broken by problem insertion order (= program order).
//      Each op starts ASAP w.r.t. every already placed predecessor; a
//      resource-limited op takes the first of the II congruence classes from
//      that time whose modulo reservation table has a free instance (one
//      always exists while II >= ResMinII).
//   4. Every dependence, including back edges whose source was placed after
//      its destination, is re-checked; a violation bumps II and restarts.
//
// Steps 3/4 are classic iterative modulo scheduling without backtracking. The
// structure --bram-analysis reads (II and each access's stage mod II) comes
// out the same as from the simplex for the saturated resources that decide
// the port demand: both place accesses at the first free slot from their
// ASAP time.
namespace {
class FastModuloScheduler {
public:
  explicit FastModuloScheduler(ModuloProblem &prob,
                               unsigned recurrenceRepairRounds = 0,
                               bool heightPriority = false,
                               bool fpUnitLimits = false)
      : prob(prob), recurrenceRepairRounds(recurrenceRepairRounds),
        heightPriority(heightPriority), fpUnitLimits(fpUnitLimits) {}

  /// Returns the number of operations linked to a resource with a limit.
  static unsigned countLimitedOps(ModuloProblem &prob);


  /// The first II from max(ResMinII, minII, RecMinII) up that places every
  /// op, at most `maxIIBumps` steps up and below `belowII` (0: no bound).
  LogicalResult schedule(unsigned maxIIBumps, unsigned minII = 1,
                         unsigned belowII = 0);

private:
  struct Edge {
    unsigned src;
    unsigned latency;
    unsigned distance;
  };

  ModuloProblem &prob;
  unsigned recurrenceRepairRounds;
  // Among ready ops, the one with the longest latency path to the end of
  // the iteration goes first (else program order); see build().
  bool heightPriority;
  // At II > 1, each floating-point operator class gets ceil(ops / II) units
  // (VITIS_NOTES N135); see scheduleWithFPUnits().
  bool fpUnitLimits;
  SmallVector<Operation *> ops;                             // insertion order
  SmallVector<unsigned> latency;                            // per op
  SmallVector<SmallVector<Edge, 4>> preds;                  // incoming edges
  SmallVector<SmallVector<Problem::ResourceType, 1>> rsrcs; // limited rsrcs
  SmallVector<unsigned> topo;
  // Edges with a nonzero distance (loop-carried); they bound the relaxation
  // rounds of asapTimes.
  unsigned numCarriedEdges = 0;
  // The floating-point unit class of each op (index into fpClassNames), -1
  // for an op outside every class, and the number of ops per class.
  SmallVector<int> fpClass;
  SmallVector<StringRef> fpClassNames;
  SmallVector<unsigned> fpClassOps;

  LogicalResult build();
  unsigned resMinII() const;
  /// Longest-path ASAP times at `ii`; false on a positive cycle.
  bool asapTimes(unsigned ii, SmallVectorImpl<int64_t> &asap) const;
  /// Smallest II >= lo without a positive cycle, or 0 if there is none.
  unsigned recMinII(unsigned lo) const;
  /// List-schedules every op at or after `asap` against a modulo
  /// reservation table; false when a resource-limited op finds no slot.
  /// `fpUnits` (empty: no limit) caps the issues per modulo slot of each
  /// floating-point class.
  bool placeAll(unsigned ii, ArrayRef<int64_t> asap,
                SmallVectorImpl<int64_t> &st, ArrayRef<unsigned> fpUnits = {});
  /// (2)-(4) at `ii`: placement, then the check of every edge, with the
  /// recurrence repair rounds in between. With `fpUnits`, a violated carried
  /// edge whose late source waited for a full floating-point slot sets
  /// `raiseClass` to that class and fails without repair.
  /// `asapAtII` (optional) holds asapTimes(ii) already computed.
  bool tryII(unsigned ii, SmallVectorImpl<unsigned> &start,
             ArrayRef<unsigned> fpUnits = {}, int *raiseClass = nullptr,
             ArrayRef<int64_t> asapAtII = {});
  /// The floating-point class of an op on the critical path of `src` that
  /// started later than its operands allowed (it waited for a unit), or -1.
  int stalledFPClassBehind(unsigned src, unsigned ii,
                           ArrayRef<int64_t> earliest,
                           ArrayRef<int64_t> st) const;
  /// N135: the schedule at `ii` with ceil(ops / ii) units per floating-point
  /// class, one unit more for each class that breaks a carried edge; false
  /// (and `start` untouched) when no unit count up to one per op places it.
  bool scheduleWithFPUnits(unsigned ii, SmallVectorImpl<unsigned> &start);
};

/// The floating-point operator class whose units Vitis allocates per
/// pipelined loop (VITIS_NOTES N135: fadd / fsub share `fadd`, fmul, dadd /
/// dsub share `dadd`, dmul; N140: ddiv and fdiv, a divide by a power of two
/// being a multiply (FloatOps.h); dsqrt / fsqrt, see N140 for their
/// evidence; the half-precision classes by analogy, unconfirmed), or none
/// for any other op.
static std::optional<StringRef> fpUnitClass(Operation *op) {
  if (!isa<AddFOp, SubFOp, MulFOp, DivFOp, math::SqrtOp>(op) ||
      op->getNumResults() != 1)
    return std::nullopt;
  Type t = op->getResult(0).getType();
  if (!t.isF16() && !t.isF32() && !t.isF64())
    return std::nullopt;
  const char *prefix = t.isF64() ? "d" : t.isF32() ? "f" : "h";
  const char *kind = "add";
  if (isa<MulFOp>(op) ||
      (isa<DivFOp>(op) && circt::hls_analysis::isExactReciprocalDivide(op)))
    kind = "mul";
  else if (isa<DivFOp>(op))
    kind = "div";
  else if (isa<math::SqrtOp>(op))
    kind = "sqrt";
  // Interned so that the class names outlive this call.
  return StringAttr::get(op->getContext(), Twine(prefix) + kind).getValue();
}
} // namespace

unsigned FastModuloScheduler::countLimitedOps(ModuloProblem &prob) {
  unsigned n = 0;
  for (Operation *op : prob.getOperations()) {
    auto lr = prob.getLinkedResourceTypes(op);
    if (!lr)
      continue;
    if (llvm::any_of(*lr, [&](Problem::ResourceType r) {
          return prob.getLimit(r).value_or(0) > 0;
        }))
      ++n;
  }
  return n;
}

LogicalResult FastModuloScheduler::build() {
  DenseMap<Operation *, unsigned> index;
  for (Operation *op : prob.getOperations()) {
    index[op] = ops.size();
    ops.push_back(op);
  }
  unsigned n = ops.size();
  latency.assign(n, 0);
  preds.assign(n, {});
  rsrcs.assign(n, {});
  for (unsigned i = 0; i < n; ++i) {
    auto opr = prob.getLinkedOperatorType(ops[i]);
    if (!opr)
      return failure();
    auto lat = prob.getLatency(*opr);
    if (!lat)
      return failure();
    latency[i] = *lat;
    if (auto lr = prob.getLinkedResourceTypes(ops[i]))
      for (Problem::ResourceType r : *lr)
        if (prob.getLimit(r).value_or(0) > 0)
          rsrcs[i].push_back(r);
  }
  fpClass.assign(n, -1);
  if (fpUnitLimits) {
    for (unsigned i = 0; i < n; ++i) {
      std::optional<StringRef> cls = fpUnitClass(ops[i]);
      if (!cls || !rsrcs[i].empty())
        continue;
      auto *it = llvm::find(fpClassNames, *cls);
      fpClass[i] = it - fpClassNames.begin();
      if (it == fpClassNames.end()) {
        fpClassNames.push_back(*cls);
        fpClassOps.push_back(0);
      }
      ++fpClassOps[fpClass[i]];
    }
  }

  SmallVector<unsigned> indeg(n, 0);
  SmallVector<SmallVector<unsigned, 4>> succ0(n);
  for (unsigned j = 0; j < n; ++j) {
    for (auto &dep : prob.getDependences(ops[j])) {
      auto it = index.find(dep.getSource());
      if (it == index.end())
        continue;
      unsigned i = it->second;
      unsigned dist = prob.getDistance(dep).value_or(0);
      preds[j].push_back({i, latency[i], dist});
      if (dist == 0) {
        succ0[i].push_back(j);
        ++indeg[j];
      } else {
        ++numCarriedEdges;
      }
    }
  }

  // Kahn's algorithm; among ready ops the earliest inserted goes first.
  auto kahn = [&](auto before) {
    SmallVector<unsigned> deg(indeg);
    std::priority_queue<unsigned, std::vector<unsigned>, decltype(before)>
        ready(before);
    for (unsigned i = 0; i < n; ++i)
      if (deg[i] == 0)
        ready.push(i);
    topo.clear();
    while (!ready.empty()) {
      unsigned i = ready.top();
      ready.pop();
      topo.push_back(i);
      for (unsigned j : succ0[i])
        if (--deg[j] == 0)
          ready.push(j);
    }
  };
  kahn(std::greater<unsigned>());
  if (heightPriority && topo.size() == n) {
    // Height priority (VITIS_NOTES N133, W9 round 17 review): the ready op
    // with the longest latency path to the end of the iteration (distance-0
    // edges) goes first, ties in program order. A port-limited load that
    // starts a long chain then gets an early slot before loads with slack:
    // in hlsyn atax the 248 A_buf loads of the two `unroll factor=2` copies
    // fill 17 slots per cycle; in program order copy 2's first load came
    // 7 cycles after copy 1's, so its chain and its tmp_buf store ended a
    // dadd later, where Vitis runs both chains in the same states and
    // stores both in ST_878.
    // A store ends its path: nothing waits for the write, so its cycle
    // does not count (VITIS_NOTES N135: with it, the last add of an unrolled
    // reduction chain, which feeds the store, outranked the second copy's
    // other adds of equal height in hlsyn bicg-medium and never waited
    // for a slot, where Vitis' does).
    SmallVector<int64_t> height(n, 0);
    for (unsigned k = n; k-- > 0;) {
      unsigned i = topo[k];
      int64_t h = 0;
      for (unsigned j : succ0[i])
        h = std::max(h, height[j]);
      bool store = isa<AffineStoreOp, memref::StoreOp, StoreEnableOp>(ops[i]);
      height[i] = h + (store ? 0 : latency[i]);
    }
    kahn([&height](unsigned a, unsigned b) {
      // priority_queue pops the largest: a < b when b goes first.
      if (height[a] != height[b])
        return height[a] < height[b];
      return a > b;
    });
  }
  DEBUG_WITH_TYPE("fast-modulo-size", {
    size_t edges = 0;
    for (auto &p : preds)
      edges += p.size();
    llvm::dbgs() << "fast modulo scheduler: " << n << " ops, " << edges
                 << " edges, " << numCarriedEdges << " carried\n";
  });
  // A cycle of distance-0 edges has no schedule at any II.
  return success(topo.size() == n);
}

unsigned FastModuloScheduler::resMinII() const {
  DenseMap<Problem::ResourceType, unsigned> uses;
  for (auto &rs : rsrcs)
    for (Problem::ResourceType r : rs)
      ++uses[r];
  unsigned ii = 1;
  for (auto &[r, count] : uses) {
    unsigned limit = *prob.getLimit(r);
    ii = std::max(ii, (count + limit - 1) / limit);
  }
  return ii;
}

/// Whether the predecessor graph `parent` (each op's last relaxing
/// predecessor, -1 for none) has a cycle.
static bool hasParentCycle(ArrayRef<int64_t> parent) {
  unsigned n = parent.size();
  // 0: not visited; k + 1: visited by the walk that started at op k.
  SmallVector<unsigned> walk(n, 0);
  for (unsigned start = 0; start < n; ++start) {
    int64_t v = start;
    while (v >= 0 && walk[v] == 0) {
      walk[v] = start + 1;
      v = parent[v];
    }
    if (v >= 0 && walk[v] == start + 1)
      return true;
  }
  return false;
}

bool FastModuloScheduler::asapTimes(unsigned ii,
                                    SmallVectorImpl<int64_t> &asap) const {
  unsigned n = ops.size();
  asap.assign(n, 0);
  SmallVector<int64_t> parent(n, -1);
  bool changed = true;
  // One round in topological order of the distance-0 edges settles every
  // path that takes no carried edge, and each further round one more
  // carried edge. Without a positive cycle a longest path is simple, so it
  // takes each carried edge at most once (and has at most n - 1 edges):
  // min(n, carried edges + 1) rounds settle it, and a change in the round
  // after that is a positive cycle. The bound matters for a large unrolled
  // body with few carried edges, where n rounds per infeasible II were
  // quadratic.
  unsigned rounds = std::min<unsigned>(n, numCarriedEdges + 1);
  for (unsigned round = 0; changed && round <= rounds; ++round) {
    changed = false;
    for (unsigned j : topo)
      for (const Edge &e : preds[j]) {
        int64_t cand = asap[e.src] + static_cast<int64_t>(e.latency) -
                       static_cast<int64_t>(e.distance) * ii;
        if (cand > asap[j]) {
          asap[j] = cand;
          parent[j] = e.src;
          changed = true;
        }
      }
    // A cycle among the relaxing predecessors has a positive weight (the
    // predecessor-subgraph lemma of Bellman-Ford), so the II is infeasible;
    // it shows long before the round bound when the body has many carried
    // edges (a large unrolled stencil: thousands). Without a positive cycle
    // the predecessors stay acyclic and the rounds run as before, so the
    // times and the verdict are unchanged.
    if (changed && hasParentCycle(parent))
      return false;
  }
  return !changed;
}

unsigned FastModuloScheduler::recMinII(unsigned lo) const {
  SmallVector<int64_t> asap;
  if (asapTimes(lo, asap))
    return lo;
  // Every cycle has distance >= 1 (build() rejected distance-0 cycles) and a
  // simple cycle's latency sum is at most the sum of all op latencies, so
  // that sum is a feasible II and bounds the search.
  uint64_t bound = 0;
  for (unsigned lat : latency)
    bound += lat;
  bound = std::max<uint64_t>(bound, static_cast<uint64_t>(lo) + 1);
  // Gallop to the first feasible lo + 2^k ...
  uint64_t infeasible = lo, hi = lo;
  for (uint64_t step = 1;; step *= 2) {
    hi = std::min(static_cast<uint64_t>(lo) + step, bound);
    if (asapTimes(static_cast<unsigned>(hi), asap))
      break;
    if (hi >= bound)
      return 0;
    infeasible = hi;
  }
  // ... then bisect (infeasible, hi]; feasibility is monotone in II.
  while (hi - infeasible > 1) {
    uint64_t mid = infeasible + (hi - infeasible) / 2;
    if (asapTimes(static_cast<unsigned>(mid), asap))
      hi = mid;
    else
      infeasible = mid;
  }
  return static_cast<unsigned>(hi);
}

bool FastModuloScheduler::tryII(unsigned ii, SmallVectorImpl<unsigned> &start,
                                ArrayRef<unsigned> fpUnits, int *raiseClass,
                                ArrayRef<int64_t> asapAtII) {
  // (2) resource-free ASAP times (ii >= recMinII, so no positive cycle).
  SmallVector<int64_t> earliest(asapAtII.begin(), asapAtII.end());
  if (asapAtII.empty() && !asapTimes(ii, earliest))
    return false;
  // (3) + (4), repaired: a loop-carried edge that the list schedule violates
  // because resource conflicts delayed its source (the reads feeding an
  // accumulation chain) raises the earliest time of its destination (the
  // accumulator read) to what the edge demands, and the body is placed
  // again. The destination of such an edge has no distance-0 predecessor
  // on the delayed path, so moving it later shortens the recurrence instead
  // of failing the II. Bounded by `recurrenceRepairRounds`; 0 keeps the
  // plain list schedule.
  for (unsigned round = 0;; ++round) {
    SmallVector<int64_t> st;
    if (!placeAll(ii, earliest, st, fpUnits))
      return false;
    // N135: Vitis gives a class another unit where a recurrence would break
    // (hlsyn atax: dadd 38 for ceil(248 / 15) = 34 ... see
    // scheduleWithFPUnits), rather than delaying the recurrence's read.
    if (!fpUnits.empty() && raiseClass)
      for (unsigned j = 0, n = ops.size(); j < n; ++j)
        for (const Edge &e : preds[j]) {
          if (e.distance == 0 ||
              st[e.src] + static_cast<int64_t>(e.latency) -
                      static_cast<int64_t>(e.distance) * ii <=
                  st[j])
            continue;
          int cls = stalledFPClassBehind(e.src, ii, earliest, st);
          if (cls >= 0) {
            *raiseClass = cls;
            return false;
          }
        }
    bool raised = false, violated = false;
    for (unsigned j = 0, n = ops.size(); j < n; ++j)
      for (const Edge &e : preds[j]) {
        int64_t need = st[e.src] + static_cast<int64_t>(e.latency) -
                       static_cast<int64_t>(e.distance) * ii;
        if (need <= st[j])
          continue;
        violated = true;
        if (e.distance > 0 && need > earliest[j]) {
          earliest[j] = need;
          raised = true;
        }
      }
    if (!violated) {
      start.clear();
      for (int64_t t : st)
        start.push_back(static_cast<unsigned>(t));
      return true;
    }
    if (!raised || round >= recurrenceRepairRounds)
      return false;
  }
}

bool FastModuloScheduler::placeAll(unsigned ii, ArrayRef<int64_t> asap,
                                   SmallVectorImpl<int64_t> &st,
                                   ArrayRef<unsigned> fpUnits) {
  unsigned n = ops.size();
  // (3) list scheduling against a modulo reservation table.
  st.assign(n, -1);
  DenseMap<Problem::ResourceType, SmallVector<unsigned>> mrt;
  // Issues per modulo slot of each floating-point class (with fpUnits).
  SmallVector<SmallVector<unsigned>> fpTable;
  if (!fpUnits.empty())
    fpTable.assign(fpUnits.size(), SmallVector<unsigned>(ii, 0));
  for (unsigned j : topo) {
    int64_t est = asap[j];
    for (const Edge &e : preds[j])
      if (st[e.src] >= 0)
        est = std::max(est, st[e.src] + static_cast<int64_t>(e.latency) -
                                static_cast<int64_t>(e.distance) * ii);
    if (!fpTable.empty() && fpClass[j] >= 0) {
      // The first slot from est with a free unit; units * ii >= the class's
      // ops, so one is free within ii cycles.
      SmallVector<unsigned> &tab = fpTable[fpClass[j]];
      int64_t t = est;
      while (tab[static_cast<unsigned>(t % ii)] >= fpUnits[fpClass[j]])
        ++t;
      ++tab[static_cast<unsigned>(t % ii)];
      st[j] = t;
      continue;
    }
    if (rsrcs[j].empty()) {
      st[j] = est;
      continue;
    }
    bool placed = false;
    for (unsigned k = 0; k < ii && !placed; ++k) {
      int64_t t = est + k;
      unsigned slot = static_cast<unsigned>(t % ii);
      bool free = true;
      for (Problem::ResourceType r : rsrcs[j]) {
        auto &tab = mrt[r];
        if (tab.empty())
          tab.assign(ii, 0);
        if (tab[slot] >= *prob.getLimit(r)) {
          free = false;
          break;
        }
      }
      if (!free)
        continue;
      for (Problem::ResourceType r : rsrcs[j])
        ++mrt[r][slot];
      st[j] = t;
      placed = true;
    }
    if (!placed)
      return false;
  }
  return true;
}

int FastModuloScheduler::stalledFPClassBehind(unsigned src, unsigned ii,
                                              ArrayRef<int64_t> earliest,
                                              ArrayRef<int64_t> st) const {
  // Walk the tight intra-iteration edges back from `src` (each op starts
  // exactly when that operand is ready) to an op that started later than
  // all its operands allowed.
  SmallVector<unsigned> work{src};
  DenseSet<unsigned> seen{src};
  while (!work.empty()) {
    unsigned u = work.pop_back_val();
    int64_t ready = earliest[u];
    for (const Edge &e : preds[u])
      ready = std::max(ready, st[e.src] + static_cast<int64_t>(e.latency) -
                                  static_cast<int64_t>(e.distance) * ii);
    if (fpClass[u] >= 0 && st[u] > ready)
      return fpClass[u];
    for (const Edge &e : preds[u])
      if (e.distance == 0 &&
          st[e.src] + static_cast<int64_t>(e.latency) == st[u] &&
          seen.insert(e.src).second)
        work.push_back(e.src);
  }
  return -1;
}

bool FastModuloScheduler::scheduleWithFPUnits(
    unsigned ii, SmallVectorImpl<unsigned> &start) {
  // N135 (kernels w9r18p_o181_*, hlsyn atax / bicg / gesummv): at II > 1
  // Vitis instantiates ceil(ops / II) units of each floating-point class
  // and places the body on that modulo table, so a chain waits whenever the
  // slot of its next add is full; whether two unrolled copies' stores share
  // a state (and their memory needs a second write port) follows from those
  // waits. A class gets one more unit while a carried edge breaks behind one
  // of its waits (atax dadd 38 for ceil(248 / 15) = 34, bicg 39 for 31).
  SmallVector<unsigned> units;
  unsigned raisable = 0;
  for (unsigned c = 0, e = fpClassOps.size(); c < e; ++c) {
    units.push_back((fpClassOps[c] + ii - 1) / ii);
    raisable += fpClassOps[c] - units.back();
  }
  // The resource-free times do not depend on the units: computed once.
  SmallVector<int64_t> asap;
  if (!asapTimes(ii, asap))
    return false;
  // Each raise adds a unit to a class below one unit per op, so the loop
  // ends; at one unit per op a class never waits and cannot be raised.
  for (unsigned round = 0; round <= raisable; ++round) {
    int raiseClass = -1;
    SmallVector<unsigned> placed;
    if (tryII(ii, placed, units, &raiseClass, asap)) {
      start.assign(placed.begin(), placed.end());
      DEBUG_WITH_TYPE("fast-modulo-fp-units", {
        llvm::dbgs() << "fast modulo scheduler: II " << ii << " after " << round
                     << " raises, units";
        for (unsigned c = 0, e = units.size(); c < e; ++c)
          llvm::dbgs() << " " << fpClassNames[c] << "=" << units[c] << "/"
                       << fpClassOps[c];
        llvm::dbgs() << "\n";
      });
      return true;
    }
    if (raiseClass < 0 || units[raiseClass] >= fpClassOps[raiseClass]) {
      DEBUG_WITH_TYPE("fast-modulo-fp-units",
                      llvm::dbgs() << "fast modulo scheduler: II " << ii
                                   << " no unit schedule after " << round
                                   << " raises\n");
      return false;
    }
    ++units[raiseClass];
  }
  return false;
}

LogicalResult FastModuloScheduler::schedule(unsigned maxIIBumps,
                                            unsigned minII, unsigned belowII) {
  if (failed(build()))
    return failure();
  unsigned resII = std::max(resMinII(), minII);
  unsigned ii = recMinII(resII);
  if (ii == 0)
    return failure();
  LLVM_DEBUG(llvm::dbgs() << "fast modulo scheduler: ResMinII = " << resII
                          << ", recurrence-feasible II = " << ii << "\n");
  SmallVector<unsigned> start;
  // From here every bump is a placement conflict, not a recurrence.
  for (unsigned bumps = 0; bumps <= maxIIBumps; ++bumps, ++ii) {
    if (belowII && ii >= belowII)
      return failure();
    if (!tryII(ii, start))
      continue;
    // The units follow the II (N135), so the limits never raise it; a body
    // they cannot place keeps the schedule without them.
    if (ii > 1 && !fpClassOps.empty())
      (void)scheduleWithFPUnits(ii, start);
    prob.setInitiationInterval(ii);
    for (unsigned i = 0, n = ops.size(); i < n; ++i)
      prob.setStartTime(ops[i], start[i]);
    LLVM_DEBUG(llvm::dbgs() << "fast modulo schedule: " << ops.size()
                            << " ops, II = " << ii << "\n");
    return success();
  }
  return failure();
}

/// Creates the scheduling plugins and the memory models of the configuration
/// once per pass instance (a clone creates its own). The plugins see the
/// configuration with this pass's explicit options in it (fast-threshold,
/// fast-ops-threshold, --loopschedule-call-latency,
/// --loopschedule-kept-call-latency), so that an option beats the file.
LogicalResult AffineToLoopSchedule::createPlugins() {
  circt::hlsest::Config cfg = circt::hlsest::Config::get();
  cfg.scheduling.fastThreshold = fastThreshold;
  cfg.scheduling.fastOpsThreshold = fastOpsThreshold;
  cfg.scheduling.userIITarget = userIITarget;
  cfg.scheduling.operatorLatencies["call"] = circt::hlsest::resolveGlobalOption(
      loopScheduleCallLatency,
      static_cast<int>(cfg.scheduling.latency("call")));
  cfg.scheduling.operatorLatencies["kept_call"] =
      circt::hlsest::resolveGlobalOption(
          loopScheduleKeptCallLatency,
          static_cast<int>(cfg.scheduling.latency("kept_call")));
  circt::hlsest::ConfigDiagnostics diag;
  using circt::hlsest::PluginRegistry;
  timingModel = PluginRegistry<circt::hlsest::OperatorTimingModel>::instance()
                    .create(cfg.scheduling.timingModel, cfg, diag);
  dependenceModel = PluginRegistry<circt::hlsest::DependenceModel>::instance()
                        .create(cfg.scheduling.dependenceModel, cfg, diag);
  moduloScheduler = PluginRegistry<circt::hlsest::ModuloScheduler>::instance()
                        .create(cfg.scheduling.moduloModel, cfg, diag);
  sequentialScheduler =
      PluginRegistry<circt::hlsest::SequentialScheduler>::instance().create(
          cfg.scheduling.sequentialModel, cfg, diag);
  binder = PluginRegistry<circt::hlsest::Binder>::instance().create(
      cfg.scheduling.bindingModel, cfg, diag);
  memoryPolicy =
      PluginRegistry<circt::hlsest::MemoryArchitecturePolicy>::instance()
          .create(cfg.tool.hls.memoryArchitecture.plugin, cfg, diag);
  storageSelector = PluginRegistry<circt::hlsest::StorageSelector>::instance()
                        .create(cfg.tool.backend.storageSelector.plugin, cfg,
                                diag);
  if (!circt::hlsest::Config::get().blockMemory())
    diag.errors.push_back("tool.backend.memory_mapper.primitive: no such "
                          "device memory");
  if (!diag.ok()) {
    InFlightDiagnostic d =
        getOperation().emitError("--convert-affine-to-loopschedule: ");
    llvm::interleave(diag.errors, d, "; ");
    return failure();
  }
  const circt::hlsest::Config &installed = circt::hlsest::Config::get();
  schedulingContext.periodNs = installed.periodNs();
  schedulingContext.clockNs = installed.run.clockNs;
  schedulingContext.device = &installed.device;
  schedulingContext.timingModel = timingModel.get();
  emitDetail = installed.scheduling.emitDetail;
  return success();
}

/// The dependences every problem needs whatever the dependence model
/// delivers: the implicit value flow from an if's yields to its results, and
/// every store before the loop's terminator (the anchor of the schedule).
/// Re-inserting an edge the problem already holds changes nothing.
static void addStructuralDependences(Operation *loop, ModuloProblem &problem) {
  loopBody(loop)->walk([&](Operation *op) {
    Block *thenBlock = nullptr, *elseBlock = nullptr;
    if (auto ifOp = dyn_cast<scf::IfOp>(op)) {
      thenBlock = ifOp.thenBlock();
      elseBlock = ifOp.elseBlock();
    } else if (auto ifOp = dyn_cast<AffineIfOp>(op)) {
      thenBlock = ifOp.getThenBlock();
      if (ifOp.hasElse())
        elseBlock = ifOp.getElseBlock();
    } else {
      return WalkResult::advance();
    }
    if (op->getNumResults() == 0)
      return WalkResult::skip();
    (void)problem.insertDependence(
        Problem::Dependence(thenBlock->getTerminator(), op));
    if (elseBlock)
      (void)problem.insertDependence(
          Problem::Dependence(elseBlock->getTerminator(), op));
    return WalkResult::advance();
  });
  Operation *anchor = loopBody(loop)->getTerminator();
  loopBody(loop)->walk([&](Operation *op) {
    if (isa<AffineStoreOp, memref::StoreOp>(op))
      (void)problem.insertDependence(Problem::Dependence(op, anchor));
  });
}

//===----------------------------------------------------------------------===//
// Selects of loaded values (VITIS_NOTES N163)
//===----------------------------------------------------------------------===//
// Vitis' front end turns `c ? load(p) : load(q)` of floating-point loads into
// `load(c ? p : q)` and keeps the two arm loads when something else (the
// compare of a maximum) also uses them, so each such select is one more read
// of the array; a
// running maximum whose previous value is itself such a select repeats it at
// every step (kernels w9r22p_a1_max4 / a1_tern4: 4 element reads, 7 read
// slots, 6 RAM_1WNR copies; a1_max2: 3 reads, 5 slots). The extra reads are
// recorded as `hls.select_reloads` on the select's first base load, where the
// RAM_1WNR copy count reads them (MemoryArchitecture analyzeReplication).
// When neither arm value is used elsewhere, the two loads are that one load
// of the selected address: `hls.select_reloads` -1 (one read fewer).

/// The memref a load reads, or null.
static Value loadedMemref(Operation *op) {
  if (auto load = dyn_cast<AffineLoadOp>(op))
    return load.getMemRef();
  if (auto load = dyn_cast<memref::LoadOp>(op))
    return load.getMemRef();
  return {};
}

/// Marks the then-arm load of every if / else result that both arms
/// produce by loading one array, with nothing else using the loaded
/// values: LLVM SimplifyCFG sinks the two loads into one load of the
/// selected address, one read fewer (`c ? t[i][j] : t[i+1][j]` that cgeist
/// emits as an if; W9 round 22 review kernels w9r22rv_k02_condsel and
/// w9r22fx_f5_condsel_int: 3 read slots, 2 copies, 64 BRAM, hls-est 96).
static void markIfArmLoadMerges(func::FuncOp func, Builder &builder) {
  auto armLoad = [](Block &arm, unsigned i) -> Operation * {
    Value v = arm.getTerminator()->getOperand(i);
    Operation *def = v.getDefiningOp();
    if (!def || def->getBlock() != &arm || !loadedMemref(def) ||
        !v.hasOneUse())
      return nullptr;
    return def;
  };
  func.walk([&](Operation *op) {
    Block *thenBlock = nullptr, *elseBlock = nullptr;
    if (auto ifOp = dyn_cast<scf::IfOp>(op)) {
      if (ifOp.getElseRegion().empty())
        return;
      thenBlock = ifOp.thenBlock();
      elseBlock = ifOp.elseBlock();
    } else if (auto ifOp = dyn_cast<AffineIfOp>(op)) {
      if (!ifOp.hasElse())
        return;
      thenBlock = ifOp.getThenBlock();
      elseBlock = ifOp.getElseBlock();
    } else {
      return;
    }
    for (unsigned i = 0; i < op->getNumResults(); ++i) {
      Operation *thenLoad = armLoad(*thenBlock, i);
      Operation *elseLoad = armLoad(*elseBlock, i);
      if (!thenLoad || !elseLoad ||
          loadedMemref(thenLoad) != loadedMemref(elseLoad))
        continue;
      int64_t reloads = -1;
      if (auto old = thenLoad->getAttrOfType<IntegerAttr>("hls.select_reloads"))
        reloads += old.getInt();
      thenLoad->setAttr("hls.select_reloads",
                        builder.getI64IntegerAttr(reloads));
    }
  });
}

static void markSelectOfLoadReloads(func::FuncOp func) {
  // A select that loads its selected address: (memref, its first base load).
  DenseMap<Operation *, std::pair<Value, Operation *>> reloadingSelects;
  auto baseOf = [&](Value v) -> std::pair<Value, Operation *> {
    Operation *def = v.getDefiningOp();
    if (!def)
      return {};
    if (Value mem = loadedMemref(def))
      return {mem, def};
    auto it = reloadingSelects.find(def);
    return it == reloadingSelects.end() ? std::pair<Value, Operation *>{}
                                        : it->second;
  };
  Builder builder(func.getContext());
  markIfArmLoadMerges(func, builder);
  func.walk([&](arith::SelectOp select) {
    auto [trueMem, trueLoad] = baseOf(select.getTrueValue());
    auto [falseMem, falseLoad] = baseOf(select.getFalseValue());
    if (!trueMem || trueMem != falseMem)
      return;
    // Only within one loop body: the extra read belongs to the select's scope.
    if (trueLoad->getParentOfType<AffineForOp>() !=
            select->getParentOfType<AffineForOp>() ||
        falseLoad->getParentOfType<AffineForOp>() !=
            select->getParentOfType<AffineForOp>())
      return;
    auto usedElsewhere = [&](Value v) {
      return llvm::any_of(v.getUsers(), [&](Operation *user) {
        return user != select.getOperation();
      });
    };
    bool trueElsewhere = usedElsewhere(select.getTrueValue());
    bool falseElsewhere = usedElsewhere(select.getFalseValue());
    // Neither arm value is used elsewhere: the two loads become the one
    // load of the selected address, one read fewer (W9 round 22 review
    // kernel w9r22rv_k02_condsel, `c[k] > 0 ? t[i][j] : t[i+1][j]` plus two
    // reads: 3 read slots, 2 copies, 64 BRAM; the int control
    // w9r22fx_f5_condsel_int the same, 64). Both arms must be plain loads (a
    // nested select already counts its own reload).
    if (!trueElsewhere && !falseElsewhere) {
      if (!loadedMemref(select.getTrueValue().getDefiningOp()) ||
          !loadedMemref(select.getFalseValue().getDefiningOp()) ||
          trueLoad == falseLoad)
        return;
      int64_t reloads = -1;
      if (auto old = trueLoad->getAttrOfType<IntegerAttr>("hls.select_reloads"))
        reloads += old.getInt();
      trueLoad->setAttr("hls.select_reloads",
                        builder.getI64IntegerAttr(reloads));
      return;
    }
    // Both arm values must stay live elsewhere (the compare) for the
    // reload; with one of them only, the loads are kept and nothing is
    // added (kernel w9r22fx_f6_condsel_used: 4 reads, 3 copies, 96).
    if (!trueElsewhere || !falseElsewhere)
      return;
    // The reload: floating-point values only; an integer maximum of loads
    // keeps its loads (training class_ece8893_2023_spring YOLOv4-Tiny
    // Maxpool_Layer: hls::max of ap_fixed<16,6> loads, 4 reads, Vitis
    // maxpool_in_buf 12 = 2 copies, no reload; W9r22-impl).
    if (!isa<FloatType>(select.getType()))
      return;
    reloadingSelects[select] = {trueMem, trueLoad};
    int64_t reloads = 1;
    if (auto old = trueLoad->getAttrOfType<IntegerAttr>("hls.select_reloads"))
      reloads += old.getInt();
    trueLoad->setAttr("hls.select_reloads",
                      builder.getI64IntegerAttr(reloads));
  });
}

void AffineToLoopSchedule::runOnOperation() {
  // The options given explicitly, else the configuration: the middle-end
  // clean-ups (tool.hls.middle_end.*) and the modulo scheduler's parameters
  // (scheduling.modulo.*). Each clone of this function pass applies them to
  // its own copy of the options.
  {
    using circt::hlsest::applyConfigured;
    const circt::hlsest::Config &cfg = circt::hlsest::Config::get();
    const circt::hlsest::MiddleEndConfig &me = cfg.tool.hls.middleEnd;
    applyConfigured(hoistInvariant, me.licmHoistInvariantLoads);
    applyConfigured(cseLoads, me.gvnLoads);
    gvnMemrefLoads = me.gvnMemrefLoads;
    applyConfigured(forwardStores, me.storeForwarding);
    applyConfigured(hoistPastCalls, me.licmHoistPastCalls);
    applyConfigured(hoistConditional, me.licmHoistConditional);
    applyConfigured(mergeIfElse, me.mergeIfElseAccesses);
    applyConfigured(gvnConditionalLoads, me.gvnConditionalLoads);
    applyConfigured(trackGlobals, me.trackGlobals);
    applyConfigured(sinkParentCode,
                    cfg.tool.hls.pipelineDecision.sinkParentCode);
    applyConfigured(sinkParentTrailingCode,
                    cfg.tool.hls.pipelineDecision.sinkParentTrailingCode);
    const circt::hlsest::SchedulingConfig &sc = cfg.scheduling;
    applyConfigured(fastThreshold, static_cast<unsigned>(sc.fastThreshold));
    applyConfigured(fastOpsThreshold,
                    static_cast<unsigned>(sc.fastOpsThreshold));
    applyConfigured(userIITarget, sc.userIITarget);
  }
  if (!timingModel && failed(createPlugins()))
    return signalPassFailure();
  // Phase 0 — structural transforms. Both mutate the loop nest and MUST run
  // before any analysis is constructed.
  tlsTrackGlobals = trackGlobals;
  if (trackGlobals)
    uniqueGlobalRefs(); // a global is one root memref
  if (sinkParentCode || sinkParentTrailingCode)
    sinkFlattenedParentCode(); // N65 / N97 (b): before the bands are found
  coalescePerfectNests();      // flatten perfect rectangular bands
  // unrollInnerReductions();     // unroll innermost reduction loops; the loop
  // above becomes the new innermost/pipelined loop

  // MODIFIED: Vitis-style LICM on the loops that will be pipelined, after the
  // flatten decision (see hoistInvariantLoads). Moves ops only, so it must
  // precede the analyses below like the coalescing does.
  // MODIFIED: Vitis GVN / DSE on the unrolled bodies (see
  // cleanupRedundantAccesses), before the LICM so that a dead store no longer
  // pins its memref in the loop. Erases ops, so it precedes every analysis.
  // `forward-stores` is on by default (Passes.td, MEMOS.md M6 decision #5): it
  // reproduces Vitis per array where the array is live (an unrolled `acc[i] +=`
  // becomes 1 BRAM, not a 2-port RAM; attention Q/K become replicable, 3
  // copies = Vitis). It would also make arrays Vitis deletes replicable, which
  // is why it waited for --dead-memory-elimination in the default pipeline
  // (OPEN_ISSUES.md O7).
  if (mergeIfElse) {
    AccessAddrCacheScope addrCache;
    mergeIfElseAccesses();
  }
  if (gvnConditionalLoads) {
    AccessAddrCacheScope addrCache;
    mergeConditionalLoads();
  }
  if (cseLoads || forwardStores) {
    AccessAddrCacheScope addrCache;
    cleanupRedundantAccesses();
  }
  if (hoistInvariant)
    hoistInvariantLoads();
  if (circt::hlsest::Config::get()
          .tool.hls.memoryArchitecture.replication.selectOfLoadsReload)
    markSelectOfLoadReloads(getOperation());
  // MODIFIED (T3): see materializeYieldedValues.
  getOperation().walk([&](AffineForOp forOp) {
    if (isInnermostAffineFor(forOp))
      materializeYieldedValues(forOp);
  });
  // MODIFIED (O72): the pipelined runtime-trip scf.for loops too.
  getOperation().walk([&](scf::ForOp forOp) {
    if (isScheduledRuntimeFor(forOp))
      materializeYieldedValues(forOp);
  });

  // MODIFIED: drop trivially dead ops up front. A dead op has no outgoing
  // dependence edge, so it is a sink in the scheduling DAG; anchoring it
  // would burn a slot and a pipeline register for a value nothing reads.
  // This must precede getAnalysis<MemoryDependenceAnalysis>(), since
  // erasing ops later invalidates the analysis's cached Operation* keys —
  // and must never run after a ModuloProblem has been built from them.
  // A dead region op (an scf.if with no results used and no side effects)
  // takes its body with it, so the ops inside it are not collected a second
  // time (they were erased twice: a double free once an unrolled copy's
  // guards were folded, class_ece8893_2023_spring Eyeriss).
  {
    SmallVector<Operation *> dead;
    getOperation().walk<WalkOrder::PreOrder>([&](Operation *op) {
      if (op == getOperation().getOperation() || !isOpTriviallyDead(op))
        return WalkResult::advance();
      dead.push_back(op);
      return WalkResult::skip();
    });
    for (Operation *op : llvm::reverse(dead))
      op->erase();
  }
  
  // Get dependence analysis for the whole function.
  // MODIFIED (T7): restricted to the accesses inside innermost loops (the
  // loops pipelined below), at their own depth; the function-wide pairs cost
  // up to 99% of the run time on user-unrolled bodies. This is still a copy
  // of the cached analysis, as upstream: lowerAffineStructures re-keys the
  // copy, and CyclicSchedulingAnalysis reads the cached instance, whose keys
  // are the erased affine ops (OPEN_ISSUES O1: memory dependences never reach
  // the schedulers). Kept as is so that no schedule changes.
  // W9r11 (OPEN_ISSUES O103 (1)): cached-o1 reads none of it, so it is not
  // computed for that model (ResidualBlock opt4: 104 of 110 s); the cyclic
  // analysis then builds its own on the lowered body, which has no affine
  // access left.
  auto dependenceAnalysis =
      dependenceModel->name() == "cached-o1"
          ? InnermostLoopDependenceAnalysis(
                getOperation(),
                InnermostLoopDependenceAnalysis::ComputeNothing{})
          : getAnalysis<InnermostLoopDependenceAnalysis>();
  numDepPairs += dependenceAnalysis.getCounters().pairs;
  numDepTests += dependenceAnalysis.getCounters().tests;
  numDeps += dependenceAnalysis.getCounters().dependences;

  if (circt::hlsest::Config::get()
          .tool.hls.memoryArchitecture.partitionedArgumentBankPorts)
    tagPartitionedArgumentBanks(getOperation());
  if (circt::hlsest::Config::get().scheduling.memoryRecurrences ||
      circt::hlsest::Config::get().tool.hls.middleEnd.dseGuardedStores ||
      circt::hlsest::Config::get().tool.hls.middleEnd.forwardToGuardedLoads)
    tagMemoryRecurrences();

  // After dependence analysis, materialize affine structures.
  if (failed(lowerAffineStructures(dependenceAnalysis)))
    return signalPassFailure();


  // MODIFIED: collapse the redundant index arithmetic introduced by
  // per-access affine-map expansion. Each affine.load/store expands its own
  // copy of the floordiv/mod delinearization, so a banked access used N
  // times yields N identical divsi/select chains. Merging them here — before
  // the scheduling problem is constructed — means the scheduler sees one
  // shared computation, so its result occupies a single pipeline register
  // slot instead of one per access. Only side-effect-free ops are merged
  // (never loads/stores), so the memory dependence analysis computed above
  // stays valid and the per-bank port demand is untouched. (An earlier
  // version built an OpPassManager with CSE here but never ran it.)
  if (cseBeforeSchedule) {
    unsigned merged = 0;
    for (Block &block : getOperation().getBody())
      merged += cseBlockPureOps(block);
    LLVM_DEBUG(llvm::dbgs() << "pre-schedule CSE merged " << merged
                            << " side-effect-free ops\n");
  }

  // Get scheduling analysis for the whole function.
  schedulingAnalysis = &getAnalysis<CyclicSchedulingAnalysis>();

  auto &bramClass = getAnalysis<BRAMClassification>();
  
  // MODIFIED: Instead of bailing on nests, collect every *innermost* loop
  // (post-coalescing) and pipeline each one in place. Outer loops of
  // non-coalescable nests remain as affine.for wrapping the pipeline.
  SmallVector<AffineForOp> innermostLoops;
  getOperation().walk([&](AffineForOp forOp) {
    // W3: a loop that calls a kept function with loops of its own stays a
    // sequential affine.for (hls.call_boundary, --auto-pipeline-unroll;
    // VITIS_NOTES.md N14 R7): Vitis pipelines the callee's loops in the
    // callee, not the caller loop around the call.
    if (forOp->hasAttr(circt::hls_analysis::kLoopCallBoundaryAttr))
      return;
    // A `pipeline off` loop stays a sequential affine.for, as the
    // runtime-trip loops already did (isScheduledRuntimeFor): Vitis
    // schedules its body as a state machine, and the sequential port model
    // (N12) and the ROM copies of one state (N93) apply to it (W9 round 12
    // review, kernel w9r12rv_n93_loop: four independent ROM reads per
    // iteration under `#pragma HLS pipeline off`, Vitis 2 ROM copies).
    if (forOp->hasAttr(circt::hls_analysis::kLoopPipelineOffAttr) &&
        circt::hlsest::Config::get()
            .tool.hls.pipelineDecision.pipelineOffSequential)
      return;
    if (isInnermostAffineFor(forOp))
      innermostLoops.push_back(forOp);
  });

  // MODIFIED (O72): the runtime-trip scf.for loops --auto-pipeline-unroll
  // pipelined (VITIS_NOTES.md N53: Vitis pipelines them like any other loop;
  // o72_fa / o72_fe: 16 reads of `buf` per iteration, RAM_1WNR 15 copies),
  // after the affine loops.
  SmallVector<Operation *> runtimeLoops;
  getOperation().walk([&](scf::ForOp forOp) {
    if (isScheduledRuntimeFor(forOp))
      runtimeLoops.push_back(forOp);
  });

  scheduleCache.clear();
  for (AffineForOp loop : innermostLoops)
    if (failed(pipelineLoop(loop, bramClass, dependenceAnalysis)))
      return signalPassFailure();
  for (Operation *loop : runtimeLoops)
    if (failed(pipelineLoop(loop, bramClass, dependenceAnalysis)))
      return signalPassFailure();

  // The state schedules of the non-pipelined regions (the function body and
  // every loop left sequential), when the configuration has a sequential
  // scheduler (scheduling.sequential.model; builtin none: the BRAM port
  // model's stretch-pair rule applies).
  SmallVector<Block *> sequentialRegions;
  if (!getOperation().getBody().empty())
    sequentialRegions.push_back(&getOperation().getBody().front());
  getOperation().walk([&](AffineForOp loop) {
    sequentialRegions.push_back(loop.getBody());
  });
  for (Block *region : sequentialRegions) {
    circt::hlsest::SequentialSchedule sched;
    sched.region = region;
    if (!sequentialScheduler->schedule(*region, schedulingContext, sched))
      continue;
    Builder b(&getContext());
    for (auto &[op, state] : sched.stateOf)
      op->setAttr("hls.state", b.getI64IntegerAttr(state));
  }

  // Operator binding of this function (scheduling.binding.model; builtin
  // none binds nothing).
  circt::hlsest::BindingResult binding;
  binder->bind(circt::hlsest::ScheduleView::fromIR(getOperation()),
               schedulingContext, binding);
  if (!binding.opToUnit.empty()) {
    Builder b(&getContext());
    for (auto &[op, unit] : binding.opToUnit)
      op->setAttr("hls.unit", b.getI64IntegerAttr(unit));
  }
}

FailureOr<bool> AffineToLoopSchedule::pipelineLoop(
    Operation *loop, const BRAMClassification &bramClass,
    InnermostLoopDependenceAnalysis &dependenceAnalysis) {
  // A body too large for the pipeline construction (a pipeline pragma over
  // a whole stencil: hlsyn-vitis seidel-2d unrolls 118 x 118 iterations
  // into one body and ran out of memory building it) stays sequential.
  if (int64_t cap = circt::hlsest::Config::get().scheduling.maxPipelineBodyOps) {
    int64_t ops = 0;
    loop->walk([&](Operation *) { ++ops; });
    if (ops > cap) {
      mlir::emitWarning(loop->getLoc(),
                        "not pipelined (left as a sequential loop): the body "
                        "has ")
          << ops << " operations, more than "
          << "scheduling.modulo.max_pipeline_body_ops = " << cap;
      return false;
    }
  }
  // The problem of the configuration's dependence model (cached-o1), with
  // the structural edges every scheduler needs. The DependenceModel plugin
  // interface takes an affine.for; a runtime-trip scf.for gets the cached
  // problem cached-o1 would return, and stays sequential under another
  // model.
  std::optional<ModuloProblem> populated;
  if (auto forOp = dyn_cast<AffineForOp>(loop)) {
    circt::hlsest::DependenceInputs inputs{*schedulingAnalysis,
                                           dependenceAnalysis};
    populated.emplace(dependenceModel->populate(forOp, inputs));
  } else {
    if (dependenceModel->name() != "cached-o1") {
      mlir::emitWarning(loop->getLoc(),
                        "not pipelined (left as a sequential loop): the "
                        "dependence model ")
          << dependenceModel->name() << " takes affine.for loops only";
      return false;
    }
    populated.emplace(copyToModuloProblem(schedulingAnalysis->getProblem(loop)));
  }
  ModuloProblem &moduloProblem = *populated;
  addStructuralDependences(loop, moduloProblem);

  // Populate the target operator types.
  // MODIFIED (T3): a loop whose body holds an op the scheduler has no
  // operator type for (a call to a math function, ...) stays a sequential
  // affine.for instead of failing the pass; populateOperatorTypes warned.
  if (failed(populateOperatorTypes(loop, moduloProblem, bramClass)))
    return false;

  anchorRegionCaptures(loop, moduloProblem);
  addLaneRecurrenceEdges(loop, moduloProblem);
  chainSharedCalleeInstances(loop, moduloProblem);
  anchorUntrackedSideEffects(loop, moduloProblem);

  // Solve the scheduling problem computed by the analysis.
  if (failed(solveSchedulingProblem(loop, moduloProblem)))
    return failure();

  // Convert the IR.
  if (failed(createLoopSchedulePipeline(loop, moduloProblem)))
    return failure();
  return true;
}

/// Apply the affine map from an 'affine.load' operation to its operands, and
/// feed the results to a newly created 'memref.load' operation (which replaces
/// the original 'affine.load').
/// The `hls.*` discardable attributes of an affine access (the counters the
/// redundant-access cleanup left on it) that its lowered form keeps, so that
/// --bram-debug can still report them.
static SmallVector<NamedAttribute> hlsAttrsOf(Operation *op) {
  SmallVector<NamedAttribute> out;
  for (NamedAttribute a : op->getDiscardableAttrs())
    if (a.getName().strref().starts_with("hls."))
      out.push_back(a);
  return out;
}

static void setAttrs(Operation *op, ArrayRef<NamedAttribute> attrs) {
  for (const NamedAttribute &a : attrs)
    op->setAttr(a.getName(), a.getValue());
}

/// Also replaces the affine load with the memref load in dependenceAnalysis.
/// TODO(mikeurbach): this is copied from AffineToStandard, see if we can reuse.
class AffineLoadLowering : public OpConversionPattern<AffineLoadOp> {
public:
  AffineLoadLowering(MLIRContext *context,
                     MemoryDependenceAnalysis &dependenceAnalysis)
      : OpConversionPattern(context), dependenceAnalysis(dependenceAnalysis) {}

  LogicalResult
  matchAndRewrite(AffineLoadOp op, OpAdaptor adaptor,
                  ConversionPatternRewriter &rewriter) const override {
    // Expand affine map from 'affineLoadOp'.
    SmallVector<Value, 8> indices(op.getMapOperands());
    auto resultOperands =
        expandAffineMap(rewriter, op.getLoc(), op.getAffineMap(), indices);
    if (!resultOperands)
      return failure();

    // Build memref.load memref[expandedMap.results].
    SmallVector<NamedAttribute> hlsAttrs = hlsAttrsOf(op);
    auto memrefLoad = rewriter.replaceOpWithNewOp<memref::LoadOp>(
        op, op.getMemRef(), *resultOperands);
    setAttrs(memrefLoad, hlsAttrs);

    dependenceAnalysis.replaceOp(op, memrefLoad);

    return success();
  }

private:
  MemoryDependenceAnalysis &dependenceAnalysis;
};

/// Apply the affine map from an 'affine.store' operation to its operands, and
/// feed the results to a newly created 'memref.store' operation (which
/// replaces the original 'affine.store').
/// Also replaces the affine store with the memref store in dependenceAnalysis.
/// TODO(mikeurbach): this is copied from AffineToStandard, see if we can reuse.
class AffineStoreLowering : public OpConversionPattern<AffineStoreOp> {
public:
  AffineStoreLowering(MLIRContext *context,
                      MemoryDependenceAnalysis &dependenceAnalysis)
      : OpConversionPattern(context), dependenceAnalysis(dependenceAnalysis) {}

  LogicalResult
  matchAndRewrite(AffineStoreOp op, OpAdaptor adaptor,
                  ConversionPatternRewriter &rewriter) const override {
    // Expand affine map from 'affineStoreOp'.
    SmallVector<Value, 8> indices(op.getMapOperands());
    auto maybeExpandedMap =
        expandAffineMap(rewriter, op.getLoc(), op.getAffineMap(), indices);
    if (!maybeExpandedMap)
      return failure();

    // Build memref.store valueToStore, memref[expandedMap.results].
    SmallVector<NamedAttribute> hlsAttrs = hlsAttrsOf(op);
    auto memrefStore = rewriter.replaceOpWithNewOp<memref::StoreOp>(
        op, op.getValueToStore(), op.getMemRef(), *maybeExpandedMap);
    setAttrs(memrefStore, hlsAttrs);

    dependenceAnalysis.replaceOp(op, memrefStore);

    return success();
  }

private:
  MemoryDependenceAnalysis &dependenceAnalysis;
};

// Lower an IntegerSet predicate to one i1: AND of one comparison per
// constraint. Equality (expr == 0) -> cmpi eq; inequality (expr >= 0) -> sge.
// Empty set is vacuously true.
static Value materializeIntegerSet(OpBuilder &b, Location loc, IntegerSet set,
                                   ValueRange setOperands) {
  if (set.getNumConstraints() == 0)
    return arith::ConstantIntOp::create(b, loc, /*value=*/1, /*width=*/1);

  Value zero = arith::ConstantIndexOp::create(b, loc, 0);
  Value acc;
  for (unsigned i = 0, e = set.getNumConstraints(); i < e; ++i) {
    AffineExpr c = set.getConstraint(i);
    bool isEq = set.isEq(i);
    auto cMap = AffineMap::get(set.getNumDims(), set.getNumSymbols(), c);
    Value lhs = affine::AffineApplyOp::create(b, loc, cMap,
                                              llvm::to_vector(setOperands));
    Value cmp = arith::CmpIOp::create(
        b, loc, isEq ? arith::CmpIPredicate::eq : arith::CmpIPredicate::sge,
        lhs, zero);
    acc = acc ? arith::AndIOp::create(b, loc, acc, cmp).getResult() : cmp;
  }
  return acc;
}

struct AffineStoreEnableLowering
    : public OpConversionPattern<hls_analysis::AffineStoreEnableOp> {
  AffineStoreEnableLowering(MLIRContext *ctx,
                            MemoryDependenceAnalysis &da)
      : OpConversionPattern(ctx), dependenceAnalysis(da) {}

  LogicalResult
  matchAndRewrite(AffineStoreEnableOp op, OpAdaptor adaptor,
                  ConversionPatternRewriter &rewriter) const override {
    Location loc = op.getLoc();

    // (a) predicate set -> i1
    Value en = materializeIntegerSet(rewriter, loc, op.getCondition(),
                                     adaptor.getSetOperands());
    if (!en)
      return rewriter.notifyMatchFailure(op, "could not materialize predicate");

    // (b) affine map -> index SSA values
    auto idx = expandAffineMap(rewriter, loc, op.getMap(),
                               llvm::to_vector(adaptor.getMapOperands()));
    if (!idx)
      return rewriter.notifyMatchFailure(op, "could not expand access map");

    // (c) flat predicated store; it keeps the hls.* attributes (a register-
    // promoted store, N87, W9r11 review D10)
    SmallVector<NamedAttribute> hlsAttrs = hlsAttrsOf(op);
    auto lowered = rewriter.replaceOpWithNewOp<hls_analysis::StoreEnableOp>(
        op, adaptor.getValue(), en, adaptor.getMemref(), *idx);
    setAttrs(lowered, hlsAttrs);

    // (d) hand the scheduler the dependence edges the affine op carried
    dependenceAnalysis.replaceOp(op, lowered);
    return success();
  }

private:
  MemoryDependenceAnalysis &dependenceAnalysis;
};

/// Hoists computation out of scf::IfOp branches, turning the if into a
/// mux-like operation and exposing concurrent execution of its branches (was
/// the IfOpHoisting conversion pattern). Runs on the whole function after the
/// conversion: innermost ifs first (post-order), each branch's ops moved in
/// front of the if in order (then-branch, then else-branch), leaving the
/// yields.
/// MODIFIED (T6): a memory access moved out of an arm records it in
/// `hls.if_arms` (LoopPragmas.h), so that --bram-analysis still knows that the
/// two arms of one if never run together (Vitis predicates them and binds the
/// two to one port: sp_o_ifarms / sp_o_ifst, VITIS_NOTES.md N12). Read only by
/// the opt-in --bram-seq-dual-port; no estimate depends on it otherwise.
static void hoistIfBodies(Operation *root) {
  SmallVector<IfOp> ifs;
  root->walk<WalkOrder::PostOrder>([&](IfOp op) { ifs.push_back(op); });
  int64_t ifId = 0;
  for (IfOp op : ifs) {
    ++ifId;
    int64_t arm = -1;
    for (Block *blk : {op.thenBlock(), op.elseBlock()}) {
      ++arm;
      if (!blk)
        continue;
      for (Operation &inner :
           llvm::make_early_inc_range(blk->without_terminator())) {
        // A call is recorded too: calls in different arms never run together
        // and share an instance (W3 review 2 D1, w3r2_k5; groupConcurrentCalls).
        // So is a math dialect op (a library core: MathCores groups its
        // sites like calls; VITIS_NOTES N169, w9r22p_d3_sincos_branch: pow
        // in both arms is one pow_generic_double_s).
        if (isa<memref::LoadOp, memref::StoreOp, hls_analysis::StoreEnableOp,
                CallOpInterface>(inner) ||
            inner.getDialect() == inner.getContext()->getLoadedDialect("math")) {
          SmallVector<int64_t> arms;
          if (auto prev = inner.getAttrOfType<DenseI64ArrayAttr>(
                  circt::hls_analysis::kIfArmsAttr))
            arms.append(prev.asArrayRef().begin(), prev.asArrayRef().end());
          arms.push_back(ifId);
          arms.push_back(arm);
          inner.setAttr(circt::hls_analysis::kIfArmsAttr,
                        DenseI64ArrayAttr::get(inner.getContext(), arms));
        }
        inner.moveBefore(op);
      }
    }
  }
}

/// Helper to mark AffineYieldOp legal, unless it is the terminator of a
/// partially converted scf::IfOp (an affine.if lowered to scf.if). MODIFIED
/// (T4): the immediate parent only - the yield of an affine.for nested in an
/// scf.if stays an affine.yield (it used to be converted to an scf.yield when
/// the if was not hoisted away first, which broke the loop).
static bool yieldOpLegalityCallback(AffineYieldOp op) {
  return !isa<IfOp>(op->getParentOp());
}

/// After analyzing memory dependences, and before creating the schedule, we
/// want to materialize affine operations with arithmetic, scf, and memref
/// operations, which make the condition computation of addresses, etc.
/// explicit. This is important so the schedule can consider potentially
/// complex computations in the condition of ifs, or the addresses of loads
/// and stores. The dependence analysis will be updated so the dependences
/// from the affine loads and stores are now on the memref loads and stores.
/// Folds the affine.apply ops that feed a bound of `forOp` into the bound map.
/// lowerAffineStructures expands every affine.apply into arith ops, and an
/// arith value computed inside a loop is no valid affine dimension or symbol,
/// so an affine.for left in place (a sequential loop) whose bound read such an
/// apply would no longer verify: polybench nussinov's `for (k = i + 1; k < j;
/// k++)`, whose `j` is an apply of the enclosing loops' counters ("operand
/// cannot be used as a dimension id", W8b). Loops whose bounds read no apply
/// are left untouched.
static void composeBoundApplies(AffineForOp forOp) {
  auto readsApply = [](ValueRange operands) {
    return llvm::any_of(operands, [](Value v) {
      return v.getDefiningOp<AffineApplyOp>() != nullptr;
    });
  };
  if (readsApply(forOp.getLowerBoundOperands())) {
    AffineMap map = forOp.getLowerBoundMap();
    SmallVector<Value> operands(forOp.getLowerBoundOperands());
    affine::fullyComposeAffineMapAndOperands(&map, &operands);
    affine::canonicalizeMapAndOperands(&map, &operands);
    forOp.setLowerBound(operands, map);
  }
  if (readsApply(forOp.getUpperBoundOperands())) {
    AffineMap map = forOp.getUpperBoundMap();
    SmallVector<Value> operands(forOp.getUpperBoundOperands());
    affine::fullyComposeAffineMapAndOperands(&map, &operands);
    affine::canonicalizeMapAndOperands(&map, &operands);
    forOp.setUpperBound(operands, map);
  }
}

/// The index expressions of an affine access with its map fully composed and
/// every constant operand substituted (simplified; a dimension or symbol that
/// is not a constant stays one).
static SmallVector<AffineExpr> constantFoldedIndices(Operation *op) {
  AffineMap map;
  SmallVector<Value> operands;
  if (auto l = dyn_cast<AffineLoadOp>(op)) {
    map = l.getAffineMap();
    operands.assign(l.getMapOperands().begin(), l.getMapOperands().end());
  } else if (auto s = dyn_cast<AffineStoreOp>(op)) {
    map = s.getAffineMap();
    operands.assign(s.getMapOperands().begin(), s.getMapOperands().end());
  } else {
    return {};
  }
  fullyComposeAffineMapAndOperands(&map, &operands);
  MLIRContext *ctx = op->getContext();
  SmallVector<AffineExpr> dims, syms;
  for (auto [i, v] : llvm::enumerate(operands)) {
    std::optional<int64_t> c = getConstantIntValue(v);
    bool isDim = i < map.getNumDims();
    AffineExpr e = c       ? getAffineConstantExpr(*c, ctx)
                   : isDim ? getAffineDimExpr(i, ctx)
                           : getAffineSymbolExpr(i - map.getNumDims(), ctx);
    (isDim ? dims : syms).push_back(e);
  }
  SmallVector<AffineExpr> out;
  for (AffineExpr e : map.getResults())
    out.push_back(simplifyAffineExpr(e.replaceDimsAndSymbols(dims, syms),
                                     map.getNumDims(), map.getNumSymbols()));
  return out;
}

/// The bank of `layout` an access with these index expressions reaches, when
/// every partitioned dimension's bank is a constant.
static std::optional<int64_t>
constantBankOf(ArrayRef<AffineExpr> indices,
               const hls_analysis::BankLayout &layout) {
  int64_t bank = 0;
  for (auto [d, p] : llvm::enumerate(layout.dims)) {
    if (p.dim >= indices.size())
      return std::nullopt;
    auto c = dyn_cast<AffineConstantExpr>(
        hls_analysis::bankAndOffset(indices[p.dim], p).first);
    if (!c || c.getValue() < 0 || c.getValue() >= p.factor)
      return std::nullopt;
    bank += c.getValue() * layout.strides[d];
  }
  return bank;
}

/// VITIS_NOTES N88: an array_partition pragma on a function argument (the
/// top's own, or a kept callee's parameter, which Vitis applies to the top
/// port the parameter is bound to: `[HLS 214-248] Applying array_partition
/// to 'out'`) gives each bank its own ports. Every access of such an
/// argument whose bank is a constant is tagged hls.port_bank; the scheduler
/// keys the argument's port pools by that bank (linkMemoryResource). An
/// access whose bank is not a constant may reach any bank: it is tagged
/// hls.port_banks = the number of banks and takes a port of every bank's
/// pool (kernel w9r11rev_pa_var3: a[16][8] cyclic 4 on dim 2, two
/// constant-bank reads per bank plus `a[i][idx[i] & 7]`: Vitis II 2).
static void tagPartitionedArgumentBanks(func::FuncOp func) {
  if (func.isExternal())
    return;
  for (BlockArgument arg : func.getArguments()) {
    auto ty = dyn_cast<MemRefType>(arg.getType());
    auto spec = func.getArgAttrOfType<ArrayAttr>(arg.getArgNumber(),
                                                 "hls.array_partition");
    if (!ty || !ty.hasStaticShape() || !spec)
      continue;
    SmallVector<hls_analysis::PartitionEntry> entries;
    hls_analysis::parsePartitionEntries(spec, "", entries);
    std::optional<hls_analysis::BankLayout> layout =
        hls_analysis::buildBankLayout(entries, ty);
    if (!layout || layout->numBanks < 2)
      continue;
    Builder b(func.getContext());
    for (Operation *user : arg.getUsers()) {
      SmallVector<AffineExpr> indices = constantFoldedIndices(user);
      if (indices.empty() && isa<memref::LoadOp, memref::StoreOp>(user)) {
        ValueRange idx = isa<memref::LoadOp>(user)
                             ? cast<memref::LoadOp>(user).getIndices()
                             : cast<memref::StoreOp>(user).getIndices();
        for (Value v : idx) {
          std::optional<int64_t> c = getConstantIntValue(v);
          indices.push_back(c ? getAffineConstantExpr(*c, func.getContext())
                              : getAffineDimExpr(0, func.getContext()));
        }
      }
      if (indices.empty())
        continue;
      if (std::optional<int64_t> bank = constantBankOf(indices, *layout))
        user->setAttr("hls.port_bank", b.getI64IntegerAttr(*bank));
      else
        user->setAttr("hls.port_banks", b.getI64IntegerAttr(layout->numBanks));
    }
  }
}

/// The cycles `op` adds to a memory recurrence chain:
/// scheduling.dependences.recurrence_latencies of its class (typed first),
/// else its operator latency; an operation the timing model does not time
/// adds nothing.
int64_t AffineToLoopSchedule::recurrenceLatency(Operation *op) const {
  std::optional<circt::hlsest::OperatorTiming> t =
      timingModel->timing(op, schedulingContext);
  if (!t)
    return 0;
  const auto &table = circt::hlsest::Config::get().scheduling.recurrenceLatencies;
  if (op->getNumResults() == 1)
    if (auto ft = dyn_cast<FloatType>(op->getResult(0).getType())) {
      auto it = table.find(t->cls + "_f" + std::to_string(ft.getWidth()));
      if (it != table.end())
        return it->second;
    }
  // A typed class (fpdiv_f32) falls back to its base class (fpdiv).
  StringRef cls = t->cls;
  auto it = table.find(cls.str());
  if (it == table.end())
    it = table.find(cls.split('_').first.str());
  if (it != table.end())
    return it->second;
  return t->latency;
}

/// VITIS_NOTES N160: the longest register recurrence of an iter_arg that
/// carries a promoted array element (hls.promoted_element_iter_args, written
/// by --auto-pipeline-unroll's register promotion): the operator latencies
/// on the longest path from the iter_arg to the value the loop yields for it,
/// and how many multi-cycle operations that path holds. Values flowing
/// through the arms of a nested if are followed.
///
/// N160 (b) (scheduling.dependences.f64_register_cycle): with
/// `rules.f64Chains`, every iter_arg (a scalar accumulator too) whose path
/// holds a multi-cycle double-precision operation fed by another multi-cycle
/// floating-point operation of the iteration counts, whatever the number of
/// such operations (a bare `s = s + a[i]` keeps its latency: w9r10p_rc_dadd,
/// II 5, N83): kernels w9r21rev_r2d_scalar1 (`s += a[i] *
/// b[i]`, double, one dadd per iteration: Vitis II 8, the dadd's 7 + 1),
/// r2e_elem1 (a promoted element, one dadd: II 8), r2c_scalar (two chained
/// dadds on a scalar: II 15), r2b_dbl3 (three: II 22). Single-precision
/// chains do not take the extra cycle (w9r11p rr_fi: one fadd, II 4;
/// rr_u4f: four chained fadds, II 16, N83), so without an f64 operation
/// only `rules.promotedChains` (N160: a promoted element through two or
/// more multi-cycle operations) applies.
std::optional<AffineToLoopSchedule::PromotedElementRecurrence>
AffineToLoopSchedule::promotedElementRecurrence(
    Operation *loop, RegisterCycleRules rules) const {
  auto marked = loop->getAttrOfType<DenseI64ArrayAttr>(
      circt::hls_analysis::kLoopPromotedElementIterArgsAttr);
  if (!marked && !rules.f64Chains)
    return std::nullopt;
  Block *body = loopBody(loop);
  Operation *yield = body->getTerminator();
  unsigned numIter = yield->getNumOperands();
  if (numIter == 0 || body->getNumArguments() < numIter)
    return std::nullopt;
  unsigned firstIter = body->getNumArguments() - numIter;
  DenseSet<int64_t> promoted;
  if (marked)
    promoted.insert(marked.asArrayRef().begin(), marked.asArrayRef().end());
  SmallVector<int64_t> candidates;
  for (unsigned i = 0; i < numIter; ++i)
    if (rules.f64Chains || (rules.promotedChains && promoted.count(i)))
      candidates.push_back(i);
  struct Path {
    int64_t latency = -1; ///< -1: does not depend on the iter_arg
    unsigned multiCycle = 0;
    bool f64 = false; ///< a multi-cycle double-precision op on the path
    bool operator<(const Path &o) const {
      return std::tie(latency, multiCycle, f64) <
             std::tie(o.latency, o.multiCycle, o.f64);
    }
  };
  auto isF64Op = [](Operation *op) {
    auto isF64 = [](Type t) { return t.isF64(); };
    return llvm::any_of(op->getResultTypes(), isF64) ||
           llvm::any_of(op->getOperandTypes(), isF64);
  };
  // N160 (b) needs the f64 operation's other operand to come from a
  // multi-cycle floating-point operation of the iteration (`s += a[i] *
  // b[i]`): a bare `s = s + a[i]` keeps the recurrence latency (N83,
  // w9r10p_rc_dadd: II 5 on a no_dsp dadd).
  std::function<int64_t(Operation *)> latencyFn;
  auto fedByMultiCycleFloat = [&](Operation *op,
                                  const DenseSet<Value> &onPath) {
    for (Value o : op->getOperands()) {
      if (onPath.contains(o))
        continue;
      Operation *def = o.getDefiningOp();
      if (def && def->getBlock() == op->getBlock() &&
          isa<FloatType>(o.getType()) && def->getNumRegions() == 0 &&
          !isa<affine::AffineReadOpInterface, memref::LoadOp>(def) &&
          latencyFn(def) > 0)
        return true;
    }
    return false;
  };
  std::optional<PromotedElementRecurrence> best;
  // Post-order positions (nested ops before their parent, definitions
  // before uses) and the operator latencies, shared by every iter_arg; each
  // iter_arg then visits only the ops computed from it.
  DenseMap<Operation *, unsigned> position;
  body->walk<WalkOrder::PostOrder>(
      [&](Operation *op) { position[op] = position.size(); });
  DenseMap<Operation *, int64_t> latencyOf;
  auto latency = [&](Operation *op) -> int64_t {
    auto [it, fresh] = latencyOf.try_emplace(op, 0);
    if (fresh && op->getNumRegions() == 0)
      if (std::optional<circt::hlsest::OperatorTiming> t =
              timingModel->timing(op, schedulingContext))
        it->second = t->latency;
    return it->second;
  };
  latencyFn = latency;
  // scheduling.dependences.promoted_element_search_budget (a designer
  // knob, not a Vitis rule): the slices of all iter_args together may hold
  // this many ops; a larger search (hlsyn adi / seidel-2d: thousands of
  // promoted elements in one unrolled body) is abandoned and the loop keeps
  // the chain bound.
  int64_t budget = circt::hlsest::Config::get()
                       .scheduling.promotedElementSearchBudget;
  int64_t visited = 0;
  for (int64_t idx : candidates) {
    BlockArgument arg = body->getArgument(firstIter + idx);
    // The ops computed from the iter_arg; a nested terminator brings in the
    // region op it yields from.
    SmallVector<Operation *> slice;
    DenseSet<Operation *> inSlice;
    SmallVector<Value> work{arg};
    while (!work.empty()) {
      Value v = work.pop_back_val();
      for (Operation *user : v.getUsers()) {
        Operation *op = user;
        while (op && op != yield && op->hasTrait<OpTrait::IsTerminator>() &&
               op->getParentOp() != loop)
          op = op->getParentOp();
        if (!op || op == yield || !position.count(op) ||
            !inSlice.insert(op).second)
          continue;
        if (budget > 0 && ++visited > budget)
          return std::nullopt;
        slice.push_back(op);
        for (Value r : op->getResults())
          work.push_back(r);
      }
    }
    llvm::sort(slice, [&](Operation *x, Operation *y) {
      return position.lookup(x) < position.lookup(y);
    });
    DenseMap<Value, Path> dist;
    dist[arg] = Path{0, 0};
    DenseSet<Value> onPath{arg};
    for (Operation *op : slice)
      for (Value r : op->getResults())
        onPath.insert(r);
    auto pathOf = [&](Value v) {
      auto it = dist.find(v);
      return it == dist.end() ? Path{} : it->second;
    };
    for (Operation *op : slice) {
      Path in;
      for (Value o : op->getOperands())
        in = std::max(in, pathOf(o));
      for (Region &r : op->getRegions())
        for (Block &b : r)
          for (Value o : b.getTerminator()->getOperands())
            in = std::max(in, pathOf(o));
      if (in.latency < 0)
        continue;
      int64_t lat = latency(op);
      Path out{in.latency + lat, in.multiCycle + (lat > 0 ? 1u : 0u),
               in.f64 || (lat > 0 && isF64Op(op) &&
                          fedByMultiCycleFloat(op, onPath))};
      for (Value r : op->getResults())
        dist[r] = out;
    }
    Path p = pathOf(yield->getOperand(idx));
    if (p.latency < 0)
      continue;
    bool counts = (rules.promotedChains && promoted.count(idx) &&
                   p.multiCycle >= 2) ||
                  (rules.f64Chains && p.f64 && p.multiCycle >= 1);
    if (!counts)
      continue;
    PromotedElementRecurrence rec{p.latency, p.multiCycle,
                                  static_cast<unsigned>(idx)};
    if (!best || std::tie(rec.chain, rec.multiCycle) >
                     std::tie(best->chain, best->multiCycle))
      best = rec;
  }
  return best;
}

/// VITIS_NOTES N87 (OPEN_ISSUES O1): the II bound of the memory recurrences
/// of each innermost loop to be scheduled (a `pipeline off` loop included:
/// its register-served accesses take no port; W9r11 review D9)
/// (findMemoryRecurrences), recorded on the loop as hls.memory_recurrence =
/// {ii, distance, chain, rule, load, store} for the scheduler
/// (solveSchedulingProblem) and --bram-debug.
void AffineToLoopSchedule::tagMemoryRecurrences() {
  SmallVector<Operation *> loops;
  getOperation().walk([&](Operation *op) {
    if (auto forOp = dyn_cast<AffineForOp>(op)) {
      if (!forOp->hasAttr(circt::hls_analysis::kLoopCallBoundaryAttr) &&
          isInnermostAffineFor(forOp))
        loops.push_back(op);
    } else if (auto forOp = dyn_cast<scf::ForOp>(op)) {
      if (isScheduledRuntimeFor(forOp))
        loops.push_back(op);
    }
  });
  const circt::hlsest::Config &cfg = circt::hlsest::Config::get();
  circt::hls_analysis::MemoryRecurrenceOptions options;
  options.recurrences = cfg.scheduling.memoryRecurrences;
  options.guardedStoreElimination = cfg.tool.hls.middleEnd.dseGuardedStores;
  options.forwardToGuardedLoads = cfg.tool.hls.middleEnd.forwardToGuardedLoads;
  options.unknownAddressMinII = cfg.scheduling.unknownAddressMinII;
  options.userInterIndependence = cfg.scheduling.userInterIndependence;
  options.dynamicLaneRmw = cfg.scheduling.dynamicLaneRmw;
  Builder b(&getContext());
  auto locText = [](Operation *op) {
    std::string s;
    llvm::raw_string_ostream os(s);
    if (auto fl = dyn_cast<FileLineColLoc>(op->getLoc()))
      os << fl.getFilename().getValue() << ":" << fl.getLine() << ":"
         << fl.getColumn();
    else
      op->getLoc().print(os);
    return s;
  };
  for (Operation *loop : loops) {
    loop->removeAttr(kMemoryRecurrenceAttr);
    circt::hls_analysis::MemoryRecurrences found =
        circt::hls_analysis::findMemoryRecurrences(
            loop, [&](Operation *op) { return recurrenceLatency(op); },
            options);
    for (Operation *op : found.promoted)
      op->setAttr(circt::hls_analysis::kPromotedAccessAttr,
                  b.getStringAttr(found.rule.lookup(op)));
    for (auto [op, n] : found.standsFor)
      op->setAttr(circt::hls_analysis::kPromotedCountAttr,
                  b.getI64IntegerAttr(n));
    // N154: the store and load of each lane recurrence share an id.
    for (auto [store, load] : found.laneRecurrences) {
      int64_t id = nextLaneRecurrenceId++;
      for (Operation *op : {store, load}) {
        SmallVector<int64_t> ids;
        if (auto prev = op->getAttrOfType<DenseI64ArrayAttr>(
                kLaneRecurrenceAttr))
          ids.assign(prev.asArrayRef().begin(), prev.asArrayRef().end());
        ids.push_back(op == store ? id : -1 - id);
        op->setAttr(kLaneRecurrenceAttr,
                    DenseI64ArrayAttr::get(op->getContext(), ids));
      }
    }
    std::optional<circt::hls_analysis::MemoryRecurrence> &rec = found.bound;
    // N160 (scheduling.dependences.promoted_element_register_cycle): a
    // promoted array element carried through two or more multi-cycle
    // operations needs one state more than the chain (hlsyn bicg's s_buf[j]:
    // two chained 7-state dadds, Vitis II 15; kernels w9r21p_b1 / b2).
    // N160 (b) (scheduling.dependences.f64_register_cycle): any iter_arg
    // carried through a multi-cycle double-precision operation does too.
    RegisterCycleRules cycleRules{cfg.scheduling.promotedElementRegisterCycle,
                                  cfg.scheduling.f64RegisterCycle};
    if (cycleRules.promotedChains || cycleRules.f64Chains)
      if (std::optional<PromotedElementRecurrence> p =
              promotedElementRecurrence(loop, cycleRules))
        if (!rec || static_cast<int64_t>(rec->ii) < p->chain + 1) {
          // The bound comes from the scheduling problem itself: the
          // yielded value's definition takes the register's cycle
          // (populateOperatorTypes); the attribute records it.
          Block *body = loopBody(loop);
          Operation *yieldOp = body->getTerminator();
          unsigned firstIter =
              body->getNumArguments() - yieldOp->getNumOperands();
          (void)firstIter;
          if (Operation *def =
                  yieldOp->getOperand(p->iterArg).getDefiningOp())
            if (def->getBlock() == body && def->getNumRegions() == 0)
              def->setAttr(kRegisterCycleAttr, b.getUnitAttr());
          circt::hls_analysis::MemoryRecurrence r;
          r.ii = static_cast<unsigned>(p->chain + 1);
          r.distance = 1;
          r.chain = p->chain;
          r.rule = "N160";
          r.load = r.store = loop;
          rec = r;
        }
    if (!rec)
      continue;
    loop->setAttr(
        kMemoryRecurrenceAttr,
        b.getDictionaryAttr(
            {b.getNamedAttr("ii", b.getI64IntegerAttr(rec->ii)),
             b.getNamedAttr("distance", b.getI64IntegerAttr(rec->distance)),
             b.getNamedAttr("chain", b.getI64IntegerAttr(rec->chain)),
             b.getNamedAttr("rule", b.getStringAttr(rec->rule)),
             b.getNamedAttr("load", b.getStringAttr(locText(rec->load))),
             b.getNamedAttr("store", b.getStringAttr(locText(rec->store)))}));
  }
}

LogicalResult AffineToLoopSchedule::lowerAffineStructures(
    MemoryDependenceAnalysis &dependenceAnalysis) {
  auto *context = &getContext();
  auto op = getOperation();
  op.walk([](AffineForOp forOp) { composeBoundApplies(forOp); });

  ConversionTarget target(*context);
  target.addLegalDialect<AffineDialect, ArithDialect, MemRefDialect,
                         SCFDialect, HLSDialect>();
  // MODIFIED: AffineApplyOp is now illegal too. The AffineApplyLowering
  // pattern registered by populateAffineToStdConversionPatterns expands it
  // into explicit arith ops (muli/addi/divsi/remsi/cmpi/select for
  // floordiv/mod semantics), which the scheduler can then handle. 
  target.addIllegalOp<AffineApplyOp, AffineStoreEnableOp,
                      AffineIfOp, AffineLoadOp, AffineStoreOp>();
  target.addDynamicallyLegalOp<AffineYieldOp>(yieldOpLegalityCallback);

  RewritePatternSet patterns(context);
  populateAffineToStdConversionPatterns(patterns);
  patterns.add<AffineLoadLowering>(context, dependenceAnalysis);
  patterns.add<AffineStoreLowering>(context, dependenceAnalysis);
  patterns.add<AffineStoreEnableLowering>(context, dependenceAnalysis);

  if (failed(applyPartialConversion(op, target, std::move(patterns))))
    return failure();

  // MODIFIED (T4): the scf.if hoisting (IfOpHoisting) used to run as a
  // pattern inside the conversion above. It is a plain move of every
  // non-terminator op of both branches in front of the if, innermost if
  // first, so it is done here on the converted IR (same IR on all 42
  // Estimation inputs and the harness subset), without interplay with the
  // driver's pending replacements; the yield legality above now only looks
  // at the immediate parent. (The "null operand found" of spector_hls
  // sobel_filter_x/y was a scheduling gap, see anchorRegionCaptures.)
  hoistIfBodies(op);
  return success();
}


//===----------------------------------------------------------------------===//
// Operator type (latency-1 "mem_<hash>") is unchanged and shared per memref —
// it governs latency, not port count. Only the *resource* construction varies
// by mode (the Vitis storage model, VITIS_NOTES.md N4):
//   1WNR -> one pool, limit 17: a bank no loop body stores to twice can be
//           replicated (16 copies + the shared write port), so the loop II is
//           ceil((R + W) / 17) and --bram-analysis prices the copies
//   TDP  -> one pool, limit 2: a bank some loop body stores to twice or more
//           stays one true-dual-port RAM and the II is ceil((R + W) / 2); also
//           every interface memref (function argument) and untracked memref
//   1P   -> one pool, limit 1
//   SDP  -> two pools, limit 1 each: loads -> _rd, stores -> _wr (dedicated)
//   Registers -> no resource at all: an alloca marked hls.registers (Vitis
//           partitions it completely / scalarises it, VITIS_NOTES.md N7) has
//           no memory ports, so its accesses never limit the II
// The greedy scheduler (FastModuloScheduler) reads the same limits through
// prob.getLimit(), so both paths see one port model.
//===----------------------------------------------------------------------===//

/// Records on the bank's defining op (its memref.alloca, or the
/// memref.get_global that names a global) the tier the storage selector
/// chose before scheduling (hls.storage_tier) and the read latency of the
/// bank's ports (hls.read_latency), so that --bram-analysis prices the bank
/// in the memory it was scheduled for (design memo 8.7 step 3).
static void recordStorageTier(Value memRef,
                              const circt::hlsest::StorageSelector &selector,
                              const circt::hlsest::BankStaticProfile *profile,
                              const circt::hlsest::PortPools &pools) {
  Operation *def = memRef.getDefiningOp();
  if (!def ||
      !isa<memref::AllocaOp, memref::GetGlobalOp>(def) ||
      def->hasAttr("hls.storage_tier"))
    return;
  auto ty = dyn_cast<MemRefType>(memRef.getType());
  if (!ty || !ty.hasStaticShape() || !ty.getElementType().isIntOrFloat())
    return;
  circt::hlsest::MemoryRequest request;
  request.words = ty.getNumElements();
  request.writeWidth = ty.getElementType().getIntOrFloatBitWidth();
  if (auto narrow = def->getAttrOfType<IntegerAttr>(
          hls_analysis::kNarrowBitsAttrName))
    if (narrow.getInt() > 0 &&
        static_cast<uint64_t>(narrow.getInt()) < request.writeWidth) {
      request.writeWidth = static_cast<unsigned>(narrow.getInt());
      request.narrowed = true;
    }
  request.readWidths.push_back(request.writeWidth);
  request.pragmaImpl = circt::hls_analysis::bindStorageImpl(def);
  circt::hlsest::SelectionContext ctx;
  ctx.profile = profile;
  circt::hlsest::TierChoice choice = selector.select(
      request, circt::hlsest::Config::get().device, ctx);
  Builder b(def->getContext());
  def->setAttr("hls.storage_tier", b.getStringAttr(choice.tier));
  def->setAttr("hls.read_latency", b.getI64IntegerAttr(pools.readLatency));
}

/// The m_axi bundle whose port `mem` is (a function argument with an
/// `hls.interface` entry of the m_axi buffer's mode, seen through views),
/// with the request limit of its direction; nullopt for any other memref or
/// an unlimited direction.
static std::optional<std::pair<std::string, int64_t>>
maxiBundleRequests(Value mem, bool isLoad) {
  while (auto view = mem.getDefiningOp<ViewLikeOpInterface>())
    mem = view.getViewSource();
  auto arg = dyn_cast<BlockArgument>(mem);
  if (!arg)
    return std::nullopt;
  auto fn = dyn_cast<func::FuncOp>(arg.getOwner()->getParentOp());
  if (!fn)
    return std::nullopt;
  const circt::hlsest::ImplicitBufferConfig *mc =
      circt::hlsest::Config::get().tool.hls.implicitBuffer("axi4-mm");
  if (!mc)
    return std::nullopt;
  int64_t limit =
      isLoad ? mc->readRequestsPerCycle : mc->writeRequestsPerCycle;
  if (limit <= 0)
    return std::nullopt;
  // A callee's parameter that every call site binds to a port of one bundle
  // (--memory-banking-bram, annotateMaxiBundlesThroughCalls; W9r13 review:
  // w9r13rev_mx_callee, 8 reads in an inline-off load function, II 8).
  if (auto bundle = fn.getArgAttrOfType<StringAttr>(
          arg.getArgNumber(), circt::hls_analysis::kMaxiBundleAttr))
    return std::make_pair(bundle.getValue().str(), limit);
  auto ifaces =
      fn.getArgAttrOfType<ArrayAttr>(arg.getArgNumber(), "hls.interface");
  if (!ifaces)
    return std::nullopt;
  for (Attribute attr : ifaces) {
    auto d = dyn_cast<DictionaryAttr>(attr);
    auto mode = d ? d.getAs<StringAttr>("mode") : StringAttr();
    if (!mode || mode.getValue() != mc->mode)
      continue;
    std::string bundle = mc->defaultBundle;
    if (auto b = d.getAs<StringAttr>("bundle"))
      bundle = b.getValue().str();
    return std::make_pair(bundle, limit);
  }
  return std::nullopt;
}

static void linkMemoryResource(Operation *memOp, Value memRef, bool isLoad,
                               unsigned latency, ModuloProblem &problem,
                               const BRAMClassification &bramClass,
                               const circt::hlsest::MemoryArchitecturePolicy &policy,
                               const circt::hlsest::StorageSelector &selector,
                               const circt::hlsest::DeviceMemory &memory) {
  auto key = std::to_string(hash_value(memRef));
  // Operator type: the timing model's memory latency (1), shared per memref.
  // The port pools of a partitioned argument are per bank (N88,
  // tagPartitionedArgumentBanks); the operator type stays per memref.
  // An access whose bank is not a constant (hls.port_banks) takes a port of
  // every bank's pools.
  SmallVector<std::string, 4> poolKeys;
  if (auto bank = memOp->getAttrOfType<IntegerAttr>("hls.port_bank"))
    poolKeys.push_back(key + "_bank" + std::to_string(bank.getInt()));
  else if (auto n = memOp->getAttrOfType<IntegerAttr>("hls.port_banks"))
    for (int64_t b = 0; b < n.getInt(); ++b)
      poolKeys.push_back(key + "_bank" + std::to_string(b));
  else
    poolKeys.push_back(key);
  Problem::OperatorType memOpr =
      problem.getOrInsertOperatorType("mem_" + key);
  problem.setLatency(memOpr, latency);
  problem.setLinkedOperatorType(memOp, memOpr);

  // The port pools of the bank (MemoryArchitecturePolicy::capacity; an
  // untracked memref - interface argument, get_global - has no profile).
  using hls_analysis::StorageMode;
  const BankProfile *prof = bramClass.getProfile(memRef);
  circt::hlsest::BankStaticProfile staticProfile;
  if (prof) {
    staticProfile.width = prof->width;
    staticProfile.depth = prof->depth;
    staticProfile.maxReads = prof->maxReads;
    staticProfile.maxWrites = prof->maxWrites;
    staticProfile.replicable = prof->mode == StorageMode::OneWriteNRead;
    staticProfile.registers = prof->mode == StorageMode::Registers;
    if (circt::hlsest::Config::get()
            .tool.hls.memoryArchitecture.replication.userPlainRamPinsKind)
      if (std::optional<std::string> type =
              hls_analysis::bindStorageType(memRef.getDefiningOp()))
        if (hls_analysis::isPinnedRamType(*type))
          staticProfile.pinnedType = *type;
  }
  circt::hlsest::PortPools pools =
      policy.capacity(prof ? &staticProfile : nullptr, memory);
  // VITIS_NOTES N154 (b) (scheduling.dependences.lane_rmw_one_port): the
  // accesses of an aggregated word whose lane is read and written back
  // (hls.lane_rmw, SplitStructMemrefs) share one port, whatever the
  // addresses: kernels w9r21p_e1_vecrmw (invariant word, run-time lane: II
  // 3), w9r21rev_r4a_lanecnt (lane = an unrolled counter: II 32) and
  // r4b_dynword (run-time word and lane: II 7) are all ram_1p 29 in Vitis.
  // A lane written without being read (`p[i >> 3][i & 7] = v`, lit
  // struct_through_calls, Vitis RAM_2P) is not marked.
  // Registers (a temporary vector Vitis scalarises: no pools) keep no port.
  if (Operation *var = memRef.getDefiningOp())
    if (var->hasAttr("hls.lane_rmw") && !pools.pools.empty() &&
        llvm::all_of(pools.pools,
                     [](const circt::hlsest::PortPool &p) {
                       return p.limit.has_value();
                     }) &&
        circt::hlsest::Config::get().scheduling.laneRmwOnePort) {
      circt::hlsest::PortPool one;
      one.suffix = "_lane_rmw";
      one.limit = 1;
      one.consumes = circt::hlsest::PortPool::Any;
      pools.pools.assign(1, one);
    }
  recordStorageTier(memRef, selector, prof ? &staticProfile : nullptr, pools);

  SmallVector<Problem::ResourceType> rsrcs;
  for (const circt::hlsest::PortPool &pool : pools.pools) {
    if (!pool.limit)
      continue; // unlimited: no resource
    if ((pool.consumes == circt::hlsest::PortPool::Read && !isLoad) ||
        (pool.consumes == circt::hlsest::PortPool::Write && isLoad))
      continue;
    for (const std::string &poolKey : poolKeys) {
      Problem::ResourceType r =
          problem.getOrInsertResourceType("mem_" + poolKey + pool.suffix);
      problem.setLimit(r, *pool.limit);
      rsrcs.push_back(r);
    }
  }
  // An access of an m_axi port also takes a request slot of its bundle:
  // one read and one write request per cycle and bundle (VITIS_NOTES N95,
  // kernels w9r13p_mx_r8 / mx_w8 / mx_w4x2; akshaya lab2: 8 writes to
  // bundle mem2 per iteration, II 8).
  if (auto bus = maxiBundleRequests(memRef, isLoad)) {
    Problem::ResourceType r = problem.getOrInsertResourceType(
        "maxi_" + bus->first + (isLoad ? "_rd" : "_wr"));
    problem.setLimit(r, static_cast<unsigned>(bus->second));
    rsrcs.push_back(r);
  }
  // A register-promoted access (VITIS_NOTES N87 R1 / R3) uses no port.
  if (!rsrcs.empty() && !hls_analysis::isPromotedAccess(memOp))
    problem.setLinkedResourceTypes(memOp, rsrcs);

  LLVM_DEBUG(llvm::dbgs() << "linked " << (isLoad ? "load" : "store")
                          << " to " << pools.pools.size() << " pool(s) for "
                          << *memOp << "\n");
}

/// The memref an access op reads or writes, and whether it reads (null for
/// any other op).
static Value accessedMemref(Operation *op, bool &isLoad) {
  isLoad = false;
  if (auto s = dyn_cast<AffineStoreOp>(op))
    return s.getMemRef();
  if (auto s = dyn_cast<memref::StoreOp>(op))
    return s.getMemRef();
  if (auto s = dyn_cast<StoreEnableOp>(op))
    return s.getMemref();
  isLoad = true;
  if (auto l = dyn_cast<AffineLoadOp>(op))
    return l.getMemRef();
  if (auto l = dyn_cast<memref::LoadOp>(op))
    return l.getMemRef();
  isLoad = false;
  return Value();
}

namespace {
/// An operation that holds one unit of an allocation-limited resource.
struct UnitUser {
  Operation *op;
  std::string unit;
  unsigned limit;
};
} // namespace

/// The (if, arm) pairs of `op`'s `hls.if_arms` (hoistIfBodies).
static SmallVector<std::pair<int64_t, int64_t>> ifArmsOf(Operation *op) {
  SmallVector<std::pair<int64_t, int64_t>> arms;
  if (auto at = op->getAttrOfType<DenseI64ArrayAttr>(
          circt::hls_analysis::kIfArmsAttr))
    for (size_t i = 0; i + 1 < at.size(); i += 2)
      arms.push_back({at[i], at[i + 1]});
  return arms;
}

/// True when `op` is shadowed on `unit` by the other arm of an if it was
/// hoisted out of (`hls.if_arms`): only one arm executes per iteration, so
/// the if's demand is the larger arm's count, not the sum. The arm with more
/// users of the unit (the then arm on a tie) keeps its links; the other
/// arm's users are dropped. Vitis evidence: two reads of one hls::stream in
/// the exclusive arms of an if pipeline at II 1 (w9r10rv rv_sc_cond,
/// VITIS_NOTES N82; the W9r10 review's D1).
static bool shadowedByOtherArm(
    Operation *op, StringRef unit,
    ArrayRef<std::pair<Operation *, StringRef>> unitOf) {
  for (auto [ifId, arm] : ifArmsOf(op)) {
    unsigned own = 0, other = 0;
    for (auto [o, u] : unitOf) {
      if (u != unit)
        continue;
      for (auto [id, a] : ifArmsOf(o))
        if (id == ifId)
          ++(a == arm ? own : other);
    }
    if (other > own || (other == own && arm != 0))
      return true;
  }
  return false;
}

/// Links every unit user to its resource, except users shadowed by the other
/// arm of an enclosing if (shadowedByOtherArm).
static void linkUnitResources(ArrayRef<UnitUser> users,
                              ModuloProblem &problem) {
  SmallVector<std::pair<Operation *, StringRef>> unitOf;
  for (const UnitUser &u : users)
    unitOf.push_back({u.op, u.unit});
  for (const UnitUser &u : users) {
    if (shadowedByOtherArm(u.op, u.unit, unitOf))
      continue;
    Problem::ResourceType r = problem.getOrInsertResourceType(u.unit);
    problem.setLimit(r, u.limit);
    problem.setLinkedResourceTypes(u.op, {r});
  }
}

/// The operations of `loop`'s body on a register recurrence: on a cycle of
/// def-use edges closed by the loop-carried edges from each yielded value to
/// the users of its iter_arg (values flowing through the arms of an if
/// included). Tarjan's strongly connected components over the body's
/// operations: linear in the body.
static DenseSet<Operation *> registerRecurrenceOps(Operation *loop) {
  DenseSet<Operation *> onCycle;
  Block *body = loopBody(loop);
  Operation *yield = body->getTerminator();
  unsigned numIter = yield->getNumOperands();
  if (numIter == 0 || body->getNumArguments() < numIter)
    return onCycle;
  unsigned firstIter = body->getNumArguments() - numIter;
  // Nodes: every operation inside the body except its terminator.
  DenseMap<Operation *, unsigned> index;
  SmallVector<Operation *> nodes;
  body->walk([&](Operation *op) {
    if (op != yield) {
      index[op] = nodes.size();
      nodes.push_back(op);
    }
  });
  unsigned n = nodes.size();
  SmallVector<SmallVector<unsigned, 2>> succ(n);
  auto addUsers = [&](unsigned from, Value v) {
    for (Operation *user : v.getUsers()) {
      auto it = index.find(user);
      if (it != index.end())
        succ[from].push_back(it->second);
    }
  };
  for (unsigned k = 0; k < n; ++k) {
    Operation *op = nodes[k];
    for (Value r : op->getResults())
      addUsers(k, r);
    // A nested terminator (an if's yield) passes its operands to the
    // parent's results.
    if (op->hasTrait<OpTrait::IsTerminator>())
      if (Operation *parent = op->getParentOp(); index.count(parent))
        for (Value r : parent->getResults())
          addUsers(k, r);
  }
  // The loop-carried edges: the yielded value's definition to the users of
  // its iter_arg.
  for (unsigned i = 0; i < numIter; ++i) {
    Operation *def = yield->getOperand(i).getDefiningOp();
    auto it = def ? index.find(def) : index.end();
    if (it != index.end())
      addUsers(it->second, body->getArgument(firstIter + i));
  }
  // Iterative Tarjan.
  const unsigned unvisited = ~0u;
  SmallVector<unsigned> order(n, unvisited), low(n, 0), stack;
  SmallVector<bool> onStack(n, false);
  unsigned counter = 0;
  SmallVector<std::pair<unsigned, unsigned>> frames; // node, next successor
  for (unsigned root = 0; root < n; ++root) {
    if (order[root] != unvisited)
      continue;
    frames.push_back({root, 0});
    order[root] = low[root] = counter++;
    stack.push_back(root);
    onStack[root] = true;
    while (!frames.empty()) {
      auto &[v, next] = frames.back();
      if (next < succ[v].size()) {
        unsigned w = succ[v][next++];
        if (order[w] == unvisited) {
          order[w] = low[w] = counter++;
          stack.push_back(w);
          onStack[w] = true;
          frames.push_back({w, 0});
        } else if (onStack[w]) {
          low[v] = std::min(low[v], order[w]);
        }
        continue;
      }
      unsigned done = v;
      frames.pop_back();
      if (!frames.empty())
        low[frames.back().first] =
            std::min(low[frames.back().first], low[done]);
      if (low[done] != order[done])
        continue;
      // `done` roots a component: pop it.
      SmallVector<unsigned> comp;
      unsigned w;
      do {
        w = stack.pop_back_val();
        onStack[w] = false;
        comp.push_back(w);
      } while (w != done);
      bool cyclic = comp.size() > 1 || llvm::is_contained(succ[done], done);
      if (cyclic)
        for (unsigned c : comp)
          onCycle.insert(nodes[c]);
    }
  }
  return onCycle;
}

/// Populate the scheduling problem's operator types: the timing model's
/// library first (calyx-fixed: comb, seq, multicycle, fpmul, fpaddsub,
/// fpdiv, fpsqrt, fptrans, in that order), then every operation of the loop
/// body with the class and latency the model gives it; a memory access gets
/// the one operator type of its memref and the port pools of its bank. An
/// operation the model does not support leaves the loop sequential.
LogicalResult AffineToLoopSchedule::populateOperatorTypes(
    Operation *loop, ModuloProblem &problem,
    const BRAMClassification &bramClass) {
  SmallVector<circt::hlsest::OperatorTiming> library;
  timingModel->library(library);
  for (const circt::hlsest::OperatorTiming &t : library) {
    Problem::OperatorType opr = problem.getOrInsertOperatorType(t.cls);
    problem.setLatency(opr, t.latency);
  }
  const circt::hlsest::Config &cfg = circt::hlsest::Config::get();
  const circt::hlsest::DeviceMemory *blockMemory = cfg.blockMemory();
  llvm::StringMap<unsigned> latencyOfClass;
  Operation *unsupported = nullptr;
  Operation *inconsistent = nullptr;
  SmallVector<UnitUser> unitUsers;
  // A floating-point add or multiply on a register recurrence can take its
  // recurrence latency (VITIS_NOTES N83: `s = s op a[i]` reaches II 4 / 3 /
  // 5 / 6 for fadd / fmul / dadd / dmul, below the chained 5 / 4 / 7 / 7);
  // solveSchedulingProblem uses it where it lowers the II.
  DenseSet<Operation *> onRecurrence;
  recurrenceAlternatives.clear();
  if (cfg.scheduling.registerRecurrenceLatencies)
    onRecurrence = registerRecurrenceOps(loop);
  WalkResult result = loopBody(loop)->walk([&](Operation *op) {
    std::optional<circt::hlsest::OperatorTiming> t =
        timingModel->timing(op, schedulingContext);
    if (!t) {
      unsupported = op;
      return WalkResult::interrupt();
    }
    if (onRecurrence.contains(op) &&
        (StringRef(t->cls).starts_with("fpaddsub") ||
         StringRef(t->cls).starts_with("fpmul")) &&
        isa<AddFOp, SubFOp, MulFOp>(op)) {
      unsigned recLatency = static_cast<unsigned>(recurrenceLatency(op));
      if (recLatency < t->latency) {
        Problem::OperatorType alt =
            problem.getOrInsertOperatorType(t->cls + "_recurrence");
        problem.setLatency(alt, recLatency);
        recurrenceAlternatives.push_back({op, alt});
      }
    }
    bool isLoad = false;
    if (Value memRef = accessedMemref(op, isLoad)) {
      linkMemoryResource(op, memRef, isLoad, t->latency, problem, bramClass,
                         *memoryPolicy, *storageSelector, *blockMemory);
      return WalkResult::advance();
    }
    // One operator type per class: its operations agree on the latency.
    auto [it, inserted] = latencyOfClass.try_emplace(t->cls, t->latency);
    if (!inserted && it->second != t->latency) {
      inconsistent = op;
      return WalkResult::interrupt();
    }
    Problem::OperatorType opr = problem.getOrInsertOperatorType(t->cls);
    problem.setLatency(opr, t->latency);
    problem.setLinkedOperatorType(op, opr);
    // N160: the op that yields a promoted element's value takes one cycle
    // more (the register's state), so the recurrence closes at chain + 1.
    if (op->hasAttr(kRegisterCycleAttr)) {
      Problem::OperatorType held =
          problem.getOrInsertOperatorType(t->cls + "_register_cycle");
      problem.setLatency(held, t->latency + 1);
      problem.setLinkedOperatorType(op, held);
    }
    if (t->unitLimit) {
      std::string unit = "unit_" + t->cls;
      if (!t->unitInstance.empty())
        unit += "@" + t->unitInstance;
      unitUsers.push_back({op, unit, *t->unitLimit});
    }
    if (emitDetail) {
      Builder b(op->getContext());
      op->setAttr("hls.op_timing",
                  b.getDictionaryAttr(
                      {b.getNamedAttr("cls", b.getStringAttr(t->cls)),
                       b.getNamedAttr("latency",
                                      b.getI64IntegerAttr(t->latency))}));
    }
    return WalkResult::advance();
  });

  if (inconsistent) {
    loop->emitError("--convert-affine-to-loopschedule: the timing model gives "
                    "operations of one class different latencies: ")
        << *inconsistent;
    return failure();
  }
  if (result.wasInterrupted()) {
    mlir::emitWarning(loop->getLoc(),
                      "not pipelined (left as a sequential loop): "
                      "unsupported operation ")
        << *unsupported;
    return failure();
  }
  linkUnitResources(unitUsers, problem);
  return success();
}

/// The II a user `#pragma HLS pipeline II=N` asks for on `forOp` (N > 1),
/// else 0. --auto-pipeline-unroll's own tag (source "auto") asks for none.
static unsigned userTargetII(Operation *loop) {
  auto arr = loop->getAttrOfType<ArrayAttr>(
      circt::hls_analysis::kLoopPipelineAttr);
  if (!arr || arr.empty())
    return 0;
  auto dict = dyn_cast<DictionaryAttr>(arr[0]);
  if (!dict || dict.get("source"))
    return 0;
  auto ii = dict.getAs<IntegerAttr>("II");
  return ii && ii.getInt() > 1 ? static_cast<unsigned>(ii.getInt()) : 0u;
}

/// Solve the pre-computed scheduling problem.
LogicalResult
AffineToLoopSchedule::solveSchedulingProblem(Operation *loop,
                                             ModuloProblem &problem) {
  // Optionally debug problem inputs.
  LLVM_DEBUG(loopBody(loop)->walk<WalkOrder::PreOrder>([&](Operation *op) {
    llvm::dbgs() << "Scheduling inputs for " << *op;
    auto opr = problem.getLinkedOperatorType(op);
    llvm::dbgs() << "\n  opr = " << opr->getAttr();
    llvm::dbgs() << "\n  latency = " << problem.getLatency(*opr);
    for (auto dep : problem.getDependences(op))
      if (dep.isAuxiliary())
        llvm::dbgs() << "\n  dep = { distance = " << problem.getDistance(dep)
                     << ", source = " << *dep.getSource() << " }";
    llvm::dbgs() << "\n\n";
  }));

  // Verify and solve the problem.
  if (failed(problem.check()))
    return failure();

  auto *anchor = loopBody(loop)->getTerminator();
  // Reuse an identical problem's schedule only when the scheduler's result
  // depends on nothing but the problem (and the requested II).
  const bool reuse = reuseSchedules && moduloScheduler->isFunctionOfProblem();
  unsigned targetII = userIITarget ? userTargetII(loop) : 0u;
  // A memory recurrence's bound (VITIS_NOTES N87, tagMemoryRecurrences):
  // the loop is scheduled at that II at least.
  // (N160's bound is in the problem: the register cycle's latency.)
  if (auto rec = loop->getAttrOfType<DictionaryAttr>(kMemoryRecurrenceAttr))
    if (auto ii = rec.getAs<IntegerAttr>("ii"))
      if (rec.getAs<StringAttr>("rule") != "N160")
        targetII = std::max<unsigned>(targetII, ii.getInt());

  // MODIFIED (T7): reuse the schedule of an identical problem (see
  // scheduleSignature).
  SmallVector<int64_t> signature;
  size_t signatureHash = 0;
  const CachedSchedule *reused = nullptr;
  if (reuse) {
    signature = scheduleSignature(problem, anchor);
    signature.push_back(targetII); // a different target, a different problem
    signatureHash =
        llvm::hash_combine_range(signature.begin(), signature.end());
    auto it = scheduleCache.find(signatureHash);
    if (it != scheduleCache.end())
      for (const CachedSchedule &c : it->second)
        if (c.signature == signature)
          reused = &c;
    DEBUG_WITH_TYPE("schedule-reuse", {
      llvm::dbgs() << "schedule signature " << loop->getLoc() << " ops "
                   << problem.getOperations().size() << " hash "
                   << signatureHash << (reused ? " reused" : " new") << ":";
      for (int64_t x : signature)
        llvm::dbgs() << " " << (x > 1000000 ? 999 : x);
      llvm::dbgs() << "\n";
    });
  }
  auto applyReused = [&]() {
    problem.setInitiationInterval(reused->ii);
    for (auto [op, t] : llvm::zip(problem.getOperations(), reused->startTimes))
      problem.setStartTime(op, t);
  };
  // The operator types of the recurrence alternatives, or back to the
  // chained ones.
  SmallVector<Problem::OperatorType> chainedTypes;
  for (auto [op, alt] : recurrenceAlternatives)
    chainedTypes.push_back(*problem.getLinkedOperatorType(op));
  auto linkRecurrenceLatencies = [&](bool on) {
    for (auto [i, entry] : llvm::enumerate(recurrenceAlternatives))
      problem.setLinkedOperatorType(entry.first,
                                    on ? entry.second : chainedTypes[i]);
  };
  if (reused && !verifyScheduleReuse) {
    linkRecurrenceLatencies(reused->recurrenceLatencies);
    applyReused();
    if (succeeded(problem.verify())) {
      ++numSchedulesReused;
      loop->setAttr(circt::hls_analysis::kLoopSchedulerAttr,
                     StringAttr::get(loop->getContext(),
                                     reused->scheduler + " (reused from " +
                                         reused->loc + ")"));
      return success();
    }
    // Cannot happen for an identical problem; solve it instead.
    linkRecurrenceLatencies(false);
    reused = nullptr;
  }

  // The modulo scheduler of the configuration (scheduling.modulo.model;
  // builtin greedy-simplex) sets the II and the start times.
  circt::hlsest::SchedulingContext ctx = schedulingContext;
  if (targetII)
    ctx.requestedII = targetII;
  circt::hlsest::ScheduleOutcome outcome =
      moduloScheduler->schedule(problem, anchor, ctx);
  bool scheduled = outcome.success;
  // MODIFIED (T7): which scheduler produced the schedule, for --bram-debug
  // (kLoopSchedulerAttr).
  std::string scheduler = outcome.label;
  if (!scheduled)
    return failure();
  // VITIS_NOTES N83 / N135: Vitis uses the faster recurrence latency of an
  // add / multiply on a register recurrence only where the recurrence would
  // otherwise set a higher II (kernels w9r10p_rc_*: II 4 / 3 / 5 / 6); a
  // loop whose II its resources set keeps the chained latencies (hlsyn
  // bicg-medium: the s_buf chain's dadds take 7 cycles at II 46).
  bool usedRecurrenceLatencies = false;
  if (!recurrenceAlternatives.empty() && *problem.getInitiationInterval() > 1) {
    unsigned chainedII = *problem.getInitiationInterval();
    SmallVector<unsigned> chainedStart;
    for (Operation *op : problem.getOperations())
      chainedStart.push_back(*problem.getStartTime(op));
    linkRecurrenceLatencies(true);
    circt::hlsest::ScheduleOutcome faster =
        moduloScheduler->schedule(problem, anchor, ctx);
    if (faster.success && *problem.getInitiationInterval() < chainedII &&
        succeeded(problem.verify())) {
      usedRecurrenceLatencies = true;
      scheduler = faster.label + " (recurrence latencies)";
    } else {
      linkRecurrenceLatencies(false);
      problem.setInitiationInterval(chainedII);
      for (auto [op, t] : llvm::zip(problem.getOperations(), chainedStart))
        problem.setStartTime(op, t);
    }
  }

  // Verify the solution.
  if (failed(problem.verify()))
    return failure();
  ++numSchedulesSolved;
  loop->setAttr(circt::hls_analysis::kLoopSchedulerAttr,
                 StringAttr::get(loop->getContext(), scheduler));

  // MODIFIED (T7): record the schedule for identical loops; with
  // verify-schedule-reuse, compare it with the one a reuse would have given.
  if (reuse) {
    SmallVector<unsigned> startTimes;
    for (Operation *op : problem.getOperations())
      startTimes.push_back(*problem.getStartTime(op));
    if (reused) {
      ++numSchedulesReused;
      if (reused->ii != *problem.getInitiationInterval() ||
          reused->startTimes != startTimes) {
        ++numReuseMismatches;
        mlir::emitWarning(loop->getLoc())
            << "schedule reuse mismatch: the identical loop at " << reused->loc
            << " has II " << reused->ii << ", this one solves to II "
            << *problem.getInitiationInterval();
      }
    } else {
      std::string loc;
      llvm::raw_string_ostream os(loc);
      if (auto fl = dyn_cast<FileLineColLoc>(loop->getLoc()))
        os << fl.getFilename().getValue() << ":" << fl.getLine() << ":"
           << fl.getColumn();
      else
        loop->getLoc().print(os);
      scheduleCache[signatureHash].push_back(
          {std::move(signature), *problem.getInitiationInterval(),
           std::move(startTimes), scheduler, std::move(loc),
           usedRecurrenceLatencies});
    }
  }

  // Optionally debug problem outputs.
  LLVM_DEBUG({
    llvm::dbgs() << "Scheduled initiation interval = "
                 << problem.getInitiationInterval() << "\n\n";
    loopBody(loop)->walk<WalkOrder::PreOrder>([&](Operation *op) {
      llvm::dbgs() << "Scheduling outputs for " << *op;
      llvm::dbgs() << "\n  start = " << problem.getStartTime(op);
      llvm::dbgs() << "\n\n";
    });
  });

  return success();
}

/// Create the loopschedule pipeline op for a single innermost loop.
///
/// MODIFIED: the pipeline is created *in place of* `forOp` rather than at
/// the root of a loop nest, and only `forOp` itself is erased. Any
/// enclosing affine.for loops survive and act as sequential control around
/// the pipeline. Because LoopSchedulePipelineOp is not IsolatedFromAbove,
/// cloned ops may keep references to outer induction variables and other
/// dominating values without extra plumbing.
LogicalResult
AffineToLoopSchedule::createLoopSchedulePipeline(Operation *loop,
                                                 ModuloProblem &problem) {
  ImplicitLocOpBuilder builder(loop->getLoc(), loop);
  Block *body = loopBody(loop);

  // Create Values for the loop's lower and upper bounds. If the bounds
  // depend on outer induction variables (non-coalesced nests), the expanded
  // bound computation is inserted right before the pipeline, inside the
  // enclosing loop, so dominance is preserved. MODIFIED (O72): a runtime-trip
  // scf.for has its bounds and step as values already; its comparison is
  // signed unless it says otherwise (scf.for semantics).
  Value lowerBound, upperBound, step;
  ValueRange inits;
  std::optional<uint64_t> constantTrip;
  arith::CmpIPredicate continuePredicate = arith::CmpIPredicate::ult;
  if (auto forOp = dyn_cast<AffineForOp>(loop)) {
    lowerBound = lowerAffineLowerBound(forOp, builder);
    upperBound = lowerAffineUpperBound(forOp, builder);
    int64_t stepValue = forOp.getStep().getSExtValue();
    step = arith::ConstantOp::create(
        builder, IntegerAttr::get(builder.getIndexType(), stepValue));
    inits = forOp.getInits();
    constantTrip = getConstantTripCount(forOp);
  } else {
    auto scfFor = cast<scf::ForOp>(loop);
    lowerBound = scfFor.getLowerBound();
    upperBound = scfFor.getUpperBound();
    step = scfFor.getStep();
    inits = scfFor.getInitArgs();
    if (!scfFor.getUnsignedCmp())
      continuePredicate = arith::CmpIPredicate::slt;
  }

  // Create the pipeline op, with the same result types as the loop. An
  // iter arg is created for the induction variable.
  TypeRange resultTypes = loop->getResultTypes();

  auto ii = builder.getI64IntegerAttr(problem.getInitiationInterval().value());

  SmallVector<Value> iterArgs;
  iterArgs.push_back(lowerBound);
  iterArgs.append(inits.begin(), inits.end());

  // If possible, attach a constant trip count attribute. This could be
  // generalized to support non-constant trip counts by supporting an
  // AffineMap. For loops whose bounds depend on outer IVs this is simply
  // omitted.
  std::optional<IntegerAttr> tripCountAttr;
  if (constantTrip)
    tripCountAttr = builder.getI64IntegerAttr(*constantTrip);

  auto pipeline = LoopSchedulePipelineOp::create(builder, resultTypes, ii,
                                                 tripCountAttr, iterArgs);

  // MODIFIED (T3 review fixes): carry the decision record of
  // --auto-pipeline-unroll (hls.pipeline tag, hls.flattened_parents,
  // hls.auto_unrolled, hls.unroll_partial) onto the pipeline op so that
  // --bram-debug can print which loops were flattened into and unrolled for
  // this pipeline. In-process only (the pipeline op's printer does not print
  // discardable attributes); nothing in the estimate reads them.
  for (StringRef name :
       {circt::hls_analysis::kLoopPipelineAttr,
        circt::hls_analysis::kLoopFlattenedParentsAttr,
        circt::hls_analysis::kLoopAutoUnrolledAttr,
        circt::hls_analysis::kLoopUnrollPartialAttr,
        circt::hls_analysis::kLoopUnrollRuntimeGuardedAttr,
        circt::hls_analysis::kLoopSchedulerAttr, kMemoryRecurrenceAttr,
        circt::hls_analysis::kFoldedGuardsAttr,
        circt::hls_analysis::kPinnedGuardOperandsAttr})
    if (Attribute a = loop->getAttr(name))
      pipeline->setAttr(name, a);

  // Create the condition, which currently just compares the induction
  // variable to the upper bound.
  Block &condBlock = pipeline.getCondBlock();
  builder.setInsertionPointToStart(&condBlock);
  auto cmpResult = arith::CmpIOp::create(builder, builder.getI1Type(),
                                         continuePredicate,
                                         condBlock.getArgument(0), upperBound);
  condBlock.getTerminator()->insertOperands(0, {cmpResult});

  // Add the non-yield operations to their start time groups.
  DenseMap<unsigned, SmallVector<Operation *>> startGroups;
  for (auto *op : problem.getOperations()) {
    if (isa<AffineYieldOp, YieldOp>(op))
      continue;
    auto startTime = problem.getStartTime(op);
    startGroups[*startTime].push_back(op);
  }

  // MODIFIED: ensure a stage exists for *every* time slot up to the last
  // scheduled operation, even if no op starts there. With multi-cycle
  // operators (e.g. latency-3 remsi/divsi from floordiv/mod expansion, or
  // latency-4/5 FP ops), the schedule can have gaps: a value produced at
  // time t and consumed at time t+k must be registered through every
  // intermediate stage, and that pass-through chain breaks if intermediate
  // stages are missing. When a chain breaks, builder.clone() silently falls
  // back to the original (soon-to-be-erased) value, producing null operands
  // after loop erasure. Empty groups become pure register-forwarding stages;
  // any stage with nothing to execute and nothing to forward is skipped at
  // creation time below.
  unsigned maxStartTime = 0;
  for (auto *op : problem.getOperations()) {
    if (isa<AffineYieldOp, YieldOp>(op))
      continue;
    maxStartTime = std::max(maxStartTime, *problem.getStartTime(op));
  }
  // MODIFIED (T7): the values the loop terminator yields are registered up to
  // the terminator's start time (`pipeEndTime` below), and the terminator can
  // start more than one cycle after the last op starts: a multi-cycle op whose
  // result nothing uses (an fmul of a dropped accumulation) still holds the
  // terminator back until it finishes. The forwarding stages up to the
  // terminator must exist too, or the register chain of a yielded value ends
  // early and the terminator lookup below finds no mapping (forgebench
  // mult_op_p3: select at 10, terminator at 12, last start 10).
  if (auto termStart =
          problem.getStartTime(body->getTerminator());
      termStart && *termStart > 0)
    maxStartTime = std::max(maxStartTime, *termStart - 1);
  for (unsigned t = 0; t <= maxStartTime; ++t)
    if (!startGroups.count(t))
      startGroups.try_emplace(t, SmallVector<Operation *>());

  // Maintain mappings of values in the loop body and results of stages,
  // initially populated with the iter args. Values defined *outside* the
  // loop (outer IVs, loop-invariant values) are intentionally not mapped:
  // clones keep referencing them directly.
  IRMapping valueMap;
  assert(iterArgs.size() == body->getNumArguments());
  for (size_t i = 0; i < iterArgs.size(); ++i)
    valueMap.map(body->getArgument(i),
                 pipeline.getStagesBlock().getArgument(i));

  // Create the stages.
  Block &stagesBlock = pipeline.getStagesBlock();
  builder.setInsertionPointToStart(&stagesBlock);

  // Iterate in order of the start times.
  SmallVector<unsigned> startTimes;
  for (const auto &group : startGroups)
    startTimes.push_back(group.first);
  llvm::sort(startTimes);

  DominanceInfo dom(getOperation());

  // MODIFIED (W9r9-impl, OPEN_ISSUES O103): a value is registered once, by
  // the stage that computes it, and every later stage and the terminator use
  // that stage result directly (the stages block is one region, so it
  // dominates them). The original lowering forwarded it through a register
  // of every intermediate stage: stages x live values operands and value
  // maps, 15 GB for hlsyn-vitis adi once a 58-cycle double divide (N78) made
  // its pipeline thousands of stages deep. The memory accesses keep their
  // stages, which is all --bram-analysis reads.
  auto isLoopTerminator = [loop](Operation *op) {
    return isa<AffineYieldOp, scf::YieldOp>(op) && op->getParentOp() == loop;
  };
  IRMapping current = valueMap;

  for (auto startTime : startTimes) {
    auto group = startGroups[startTime];
    llvm::sort(group, [&](Operation *a, Operation *b) {
      return dom.properlyDominates(a, b);
    });

    // The results a later stage or the loop terminator uses.
    SmallVector<Value> registered;
    for (auto *op : group) {
      bool usedLater = llvm::any_of(op->getUsers(), [&](Operation *rawUser) {
        // MODIFIED (T4): a use inside a region op (the yield of a hoisted
        // scf.if) is served when the region op is cloned, i.e. at the region
        // op's start time.
        Operation *user = body->findAncestorOpInBlock(*rawUser);
        if (!user)
          user = rawUser;
        return *problem.getStartTime(user) > startTime ||
               isLoopTerminator(user);
      });
      if (usedLater)
        llvm::append_range(registered, op->getResults());
    }
    SmallVector<Type> stageTypes;
    for (Value v : registered)
      stageTypes.push_back(v.getType());

    // MODIFIED: a gap-filling stage that has no ops to run and no values to
    // register is pointless; skip it. (Stage 0 is always created since it
    // carries the induction variable increment.)
    if (group.empty() && stageTypes.empty() && startTime != 0)
      continue;
    // Add the induction variable increment in the first stage.
    if (startTime == 0)
      stageTypes.push_back(lowerBound.getType());

    // Create the stage itself.
    builder.setInsertionPoint(stagesBlock.getTerminator());
    auto startTimeAttr = builder.getIntegerAttr(
        builder.getIntegerType(64, /*isSigned=*/true), startTime);
    auto stage =
        LoopSchedulePipelineStageOp::create(builder, stageTypes, startTimeAttr);
    auto &stageBlock = stage.getBodyBlock();
    auto *stageTerminator = stageBlock.getTerminator();
    builder.setInsertionPointToStart(&stageBlock);

    for (auto *op : group) {
      auto *newOp = builder.clone(*op, current);
      // Further uses in this stage use the clone.
      for (auto result : op->getResults())
        current.map(result, newOp->getResult(result.getResultNumber()));
    }

    // Register the values later stages use; from now on they read the
    // stage's results.
    SmallVector<Value> stageOperands;
    for (Value res : registered)
      stageOperands.push_back(current.lookup(res));
    for (auto [k, res] : llvm::enumerate(registered))
      current.map(res, stage.getResult(k));
    stageTerminator->insertOperands(stageTerminator->getNumOperands(),
                                    stageOperands);

    // Add the induction variable increment to the first stage.
    if (startTime == 0) {
      auto incResult =
          arith::AddIOp::create(builder, stagesBlock.getArgument(0), step);
      stageTerminator->insertOperands(stageTerminator->getNumOperands(),
                                      incResult->getResults());
    }
  }

  // Add the iter args and results to the terminator.
  auto stagesTerminator =
      cast<LoopScheduleTerminatorOp>(stagesBlock.getTerminator());

  // Collect iter args and results from the induction variable increment and
  // any mapped values that were originally yielded.
  SmallVector<Value> termIterArgs;
  SmallVector<Value> termResults;
  termIterArgs.push_back(
      stagesBlock.front().getResult(stagesBlock.front().getNumResults() - 1));

  for (auto value : body->getTerminator()->getOperands()) {
    termIterArgs.push_back(current.lookupOrDefault(value));
    termResults.push_back(current.lookupOrDefault(value));
  }

  stagesTerminator.getIterArgsMutable().append(termIterArgs);
  stagesTerminator.getResultsMutable().append(termResults);

  // Replace loop results with pipeline results.
  for (size_t i = 0; i < loop->getNumResults(); ++i)
    loop->getResult(i).replaceAllUsesWith(pipeline.getResult(i));

  // MODIFIED: remove only this loop from the IR; enclosing loops (if any)
  // are kept as sequential control around the new pipeline.
  loop->walk([](Operation *op) {
    op->dropAllUses();
    op->dropAllDefinedValueUses();
    op->dropAllReferences();
    op->erase();
  });

  return success();
}
//===----------------------------------------------------------------------===//
// The builtin scheduling plugins (hls-doc/plugins.md, design memo 8.7).
//===----------------------------------------------------------------------===//
namespace {

using circt::hlsest::OperatorTiming;

/// calyx-fixed: a fixed operator library "assuming Calyx" (no clock period
/// enters): comb 0, seq 1, multicycle 3 (integer mul / div / rem), fpmul 4,
/// fpaddsub 5, fpdiv 12, fpsqrt 16, fptrans 20, mem 1 cycles
/// (scheduling.timing.operator_latencies; unconfirmed against Vitis); a call
/// to a defined function holds its instance for hls.call_occupancy cycles
/// (else kept_call, 1), another call without memref operands takes `call`
/// (-1: the loop stays sequential).
class CalyxFixedTiming : public circt::hlsest::OperatorTimingModel {
public:
  StringRef name() const override { return "calyx-fixed"; }

  void configure(const circt::hlsest::Config &cfg,
                 circt::hlsest::ConfigDiagnostics &diag) override {
    latencies = cfg.scheduling.operatorLatencies;
    SmallVector<std::string> classes;
    listClasses(classes);
    for (const std::string &c : classes)
      if (!latencies.count(c))
        diag.errors.push_back("scheduling.timing.operator_latencies: "
                              "calyx-fixed needs a latency for '" +
                              c + "'");
    // A class calyx-fixed does not read is a typo (fp_mul for fpmul) that
    // would otherwise be ignored silently.
    for (const auto &kv : latencies) {
      if (llvm::is_contained(classes, kv.first) ||
          llvm::is_contained(kTypedClasses, StringRef(kv.first)))
        continue;
      std::string msg = "scheduling.timing.operator_latencies." + kv.first +
                        ": calyx-fixed has no operator class '" + kv.first +
                        "'";
      unsigned best = ~0u;
      StringRef bestName;
      for (const std::string &c : classes) {
        unsigned d = StringRef(kv.first).edit_distance(c);
        if (d < best) {
          best = d;
          bestName = c;
        }
      }
      if (best <= std::max<size_t>(2, kv.first.size() / 3))
        msg += " (did you mean " + bestName.str() + "?)";
      else
        msg += " (classes: " + llvm::join(classes, ", ") + ")";
      diag.errors.push_back(msg);
    }
  }

  void listClasses(SmallVectorImpl<std::string> &out) const override {
    for (const char *c : {"comb", "seq", "multicycle", "fpmul", "fpaddsub",
                          "fpdiv", "fpsqrt", "fptrans", "mem", "call",
                          "kept_call"})
      out.push_back(c);
  }

  static constexpr const char *kStreamRead = "stream_read";
  static constexpr const char *kStreamWrite = "stream_write";
  /// A call of an external C math library function (VITIS_NOTES N169).
  static constexpr const char *kLibmCall = "libm_call";

  /// Whether `name` is a C math library function whose Vitis core has no
  /// loop of its own (tool.hls.pipeline_decision.pipelined_library_calls:
  /// tanhf, expf, log2, log2f measured, VITIS_NOTES N169). Not sin / cos,
  /// fmod or atan2: their cores have loops and the loop around them stays
  /// sequential (tool.hls.pipeline_decision.library_calls_with_loops). An
  /// unmeasured function is not listed and keeps the loop sequential (W9
  /// round 22 review: fmod / atan2 had been pipelined by a name list).
  static bool isLibmMathFunction(StringRef name) {
    return llvm::is_contained(circt::hlsest::Config::get()
                                  .tool.hls.pipelineDecision
                                  .pipelinedLibraryCalls,
                              name.str());
  }

  /// Optional classes: per-type classes (VITIS_NOTES N78, N135 for the
  /// add / sub and multiply of a double; an absent one falls back to its
  /// base class) and the hls::stream accesses (N82; absent: a loop with a
  /// stream access stays sequential, the behaviour before W9r10).
  static constexpr const char *kTypedClasses[] = {
      "fpdiv_f32",    "fpdiv_f64",    "fpsqrt_f32", "fpsqrt_f64",
      "fpaddsub_f32", "fpaddsub_f64", "fpmul_f32",  "fpmul_f64",
      kStreamRead,    kStreamWrite, kLibmCall};

  void library(SmallVectorImpl<OperatorTiming> &out) const override {
    for (const char *c : {"comb", "seq", "multicycle", "fpmul", "fpaddsub",
                          "fpdiv", "fpsqrt", "fptrans"})
      out.push_back(make(c));
    for (const char *c : kTypedClasses)
      if (latencies.count(c))
        out.push_back(make(c));
  }

  std::optional<OperatorTiming>
  timing(Operation *op, const circt::hlsest::SchedulingContext &) const override {
    return TypeSwitch<Operation *, std::optional<OperatorTiming>>(op)
        // index_castui (cgeist's cast of an unsigned C index) is the same
        // wire as index_cast.
        .Case<IfOp, AffineYieldOp, arith::ConstantOp, CmpIOp, IndexCastOp,
              IndexCastUIOp, AllocaOp, AllocOp, YieldOp, AddIOp, SubIOp,
              SelectOp, AndIOp, OrIOp, XOrIOp, ShLIOp, ShRSIOp, ShRUIOp,
              TruncIOp, ExtSIOp, ExtUIOp, NegFOp, CmpFOp, ExtFOp, TruncFOp,
              SIToFPOp, UIToFPOp, FPToSIOp, FPToUIOp, BitcastOp>(
            [&](Operation *) { return make("comb"); })
        // An integer max / min is a compare and a select (both comb above);
        // a member of an SSA struct value is a wire (OPEN_ISSUES O111 (b)).
        .Case<MaxSIOp, MinSIOp, MaxUIOp, MinUIOp, LLVM::InsertValueOp,
              LLVM::ExtractValueOp>([&](Operation *) { return make("comb"); })
        .Case<AffineStoreOp, memref::StoreOp, AffineLoadOp, memref::LoadOp,
              StoreEnableOp>([&](Operation *) { return make("mem"); })
        .Case<MulIOp, DivSIOp, DivUIOp, RemSIOp, RemUIOp>(
            [&](Operation *) { return make("multicycle"); })
        .Case<MulFOp>(
            [&](Operation *o) { return make(typedClass("fpmul", o)); })
        .Case<AddFOp, SubFOp>(
            [&](Operation *o) { return make(typedClass("fpaddsub", o)); })
        .Case<MaximumFOp, MinimumFOp, MaxNumFOp, MinNumFOp>(
            [&](Operation *) { return make("fpaddsub"); })
        .Case<DivFOp, RemFOp>([&](Operation *o) {
          // A divide by a power of two is a multiply (FloatOps.h, D7).
          if (circt::hls_analysis::isExactReciprocalDivide(o))
            return make(typedClass("fpmul", o));
          return make(typedClass("fpdiv", o));
        })
        .Case<math::SqrtOp, math::RsqrtOp>(
            [&](Operation *o) { return make(typedClass("fpsqrt", o)); })
        .Case<math::ExpOp, math::Exp2Op, math::ExpM1Op, math::LogOp,
              math::Log2Op, math::Log10Op, math::Log1pOp, math::PowFOp,
              math::SinOp, math::CosOp, math::TanOp, math::TanhOp,
              math::ErfOp, math::AtanOp, math::Atan2Op>(
            [&](Operation *) { return make("fptrans"); })
        .Case<math::FmaOp>([&](Operation *) { return make("fpaddsub"); })
        .Case<math::AbsFOp, math::CopySignOp, math::AbsIOp>(
            [&](Operation *) { return make("comb"); })
        .Case<math::FloorOp, math::CeilOp, math::RoundOp, math::RoundEvenOp,
              math::TruncOp>([&](Operation *) { return make("fpaddsub"); })
        .Default([&](Operation *badOp) -> std::optional<OperatorTiming> {
          if (std::optional<OperatorTiming> t = streamTiming(badOp))
            return t;
          auto call = dyn_cast<CallOpInterface>(badOp);
          if (!call)
            return std::nullopt;
          // A call to a function defined in the module (W3, N14): an
          // operation of the pipelined loop holding its instance for the
          // cycles --auto-pipeline-unroll estimated (hls.call_occupancy,
          // N14 R7), else kept_call.
          int64_t kept = latency("kept_call");
          if (kept >= 0 && resolveDefinedCallee(call)) {
            unsigned lat = static_cast<unsigned>(kept);
            if (auto occ = badOp->getAttrOfType<IntegerAttr>(
                    circt::hls_analysis::kCallOccupancyAttr))
              lat = static_cast<unsigned>(std::max<int64_t>(1, occ.getInt()));
            OperatorTiming t;
            t.cls = "call_kept_" + std::to_string(lat);
            t.latency = lat;
            return t;
          }
          // An external C math library call (tanhf, expf, log2): its core
          // is an operator of the pipeline (N169: Vitis pipelines the loop).
          if (auto fc = dyn_cast<func::CallOp>(badOp))
            if (latencies.count(kLibmCall) && latency(kLibmCall) >= 0 &&
                isLibmMathFunction(fc.getCallee()) &&
                !resolveDefinedCallee(call))
              return make(kLibmCall);
          int64_t other = latency("call");
          if (other >= 0 &&
              llvm::none_of(badOp->getOperandTypes(),
                            llvm::IsaPred<BaseMemRefType>) &&
              llvm::none_of(badOp->getResultTypes(),
                            llvm::IsaPred<BaseMemRefType>)) {
            OperatorTiming t;
            t.cls = "call";
            t.latency = static_cast<unsigned>(other);
            return t;
          }
          return std::nullopt;
        });
  }

private:
  std::map<std::string, int64_t> latencies;

  /// A blocking access occupies its stream object's one port for a cycle
  /// (N82: two reads, or two writes, of one stream per iteration give II 2;
  /// accesses to two different streams give II 1).
  static constexpr unsigned kStreamAccessesPerCycle = 1;

  /// The blocking hls::stream access `op` makes (read / operator>>, write /
  /// operator<<), or nullopt. The non-blocking forms and empty / full are
  /// not covered (no kernel yet).
  static std::optional<StringRef> streamAccessClass(Operation *op) {
    auto call = dyn_cast<func::CallOp>(op);
    if (!call)
      return std::nullopt;
    std::optional<circt::hls_analysis::StreamTemplate> t =
        circt::hls_analysis::parseStreamMethod(call.getCallee());
    if (!t)
      return std::nullopt;
    StringRef m = t->method;
    if ((m.starts_with("4read") && !m.starts_with("4read_nb")) ||
        m.starts_with("rs"))
      return StringRef(kStreamRead);
    if (m.starts_with("5write") || m.starts_with("ls"))
      return StringRef(kStreamWrite);
    return std::nullopt;
  }

  /// A view of a stream handle (polygeist.subindex, memref.cast).
  static bool isHandleView(Operation *op) {
    return op->getName().getStringRef() == "polygeist.subindex" ||
           isa<memref::CastOp>(op);
  }

  /// True when every use of `op`'s results is, through further views, an
  /// operand of a blocking stream access.
  static bool reachesOnlyStreamAccesses(Operation *op) {
    for (Value r : op->getResults())
      for (Operation *user : r.getUsers()) {
        if (isHandleView(user) ? !reachesOnlyStreamAccesses(user)
                               : !streamAccessClass(user))
          return false;
      }
    return true;
  }

  /// How deep structuralKey looks through an index expression.
  static constexpr unsigned kIndexKeyDepth = 8;

  /// A hash of how `v` is computed: two side-effect-free, region-free
  /// computations of one expression from the same operands (copies CSE did
  /// not merge) get one key; a block argument, an op with effects or regions,
  /// or depth 0 is keyed by its SSA value (the W9r10 review's D1 note).
  static llvm::hash_code structuralKey(Value v, unsigned depth) {
    Operation *def = v.getDefiningOp();
    if (!def || depth == 0 || def->getNumRegions() != 0 ||
        !isMemoryEffectFree(def))
      return hash_value(v);
    llvm::hash_code h = llvm::hash_combine(
        def->getName().getStringRef(), def->getAttrDictionary(),
        cast<OpResult>(v).getResultNumber());
    for (Value operand : def->getOperands())
      h = llvm::hash_combine(h, structuralKey(operand, depth - 1));
    return h;
  }

  /// The stream object a handle names: the root value and the indices of
  /// the views taken from it (a constant index by value, another by how it
  /// is computed, structuralKey), as a resource key.
  static std::string streamObjectKey(Value handle) {
    std::string key;
    llvm::raw_string_ostream os(key);
    SmallVector<std::string> indices;
    while (Operation *def = handle.getDefiningOp()) {
      if (!isHandleView(def))
        break;
      if (def->getNumOperands() == 2) {
        APInt v;
        if (matchPattern(def->getOperand(1), m_ConstantInt(&v)))
          indices.push_back(std::to_string(v.getSExtValue()));
        else
          indices.push_back("v" + std::to_string(structuralKey(
                                      def->getOperand(1), kIndexKeyDepth)));
      }
      handle = def->getOperand(0);
    }
    os << hash_value(handle);
    for (const std::string &i : llvm::reverse(indices))
      os << "[" << i << "]";
    return key;
  }

  /// The timing of a stream access, or of a view feeding only stream
  /// accesses (a wire), when the stream classes are configured.
  std::optional<OperatorTiming> streamTiming(Operation *op) const {
    if (!latencies.count(kStreamRead) || !latencies.count(kStreamWrite))
      return std::nullopt;
    if (isHandleView(op))
      return reachesOnlyStreamAccesses(op) ? std::optional(make("comb"))
                                           : std::nullopt;
    std::optional<StringRef> cls = streamAccessClass(op);
    if (!cls || op->getNumOperands() == 0)
      return std::nullopt;
    OperatorTiming t = make(*cls);
    t.unitLimit = kStreamAccessesPerCycle;
    t.unitInstance = streamObjectKey(op->getOperand(0));
    return t;
  }

  int64_t latency(StringRef cls) const {
    auto it = latencies.find(cls.str());
    return it == latencies.end() ? 0 : it->second;
  }
  /// `base`, or its per-type class for the element width of `op`'s result.
  std::string typedClass(StringRef base, Operation *op) const {
    Type elt = getElementTypeOrSelf(op->getResult(0).getType());
    std::string typed =
        (base + "_f" + Twine(elt.isIntOrFloat() ? elt.getIntOrFloatBitWidth()
                                                : 0u))
            .str();
    return latencies.count(typed) ? typed : base.str();
  }
  OperatorTiming make(StringRef cls) const {
    OperatorTiming t;
    t.cls = cls.str();
    t.latency = static_cast<unsigned>(latency(cls));
    return t;
  }
};

/// cached-o1: the dependences of the function's cyclic scheduling analysis,
/// keyed on the affine operations before the lowering, so that loop-carried
/// memory dependences never reach the schedulers (OPEN_ISSUES O1; turning
/// them on broke 16 of the 42 Estimation inputs).
class CachedO1Dependences : public circt::hlsest::DependenceModel {
public:
  StringRef name() const override { return "cached-o1"; }
  ModuloProblem populate(AffineForOp loop,
                         circt::hlsest::DependenceInputs &in) const override {
    return copyToModuloProblem(in.cached.getProblem(loop));
  }
};

/// greedy-simplex: the greedy resource-bound modulo scheduler above
/// fast_threshold resource-limited operations (or fast_ops_threshold
/// operations), else the simplex scheduler; each falls back to the other; a
/// loop with a user II target that could start more often is rescheduled
/// greedily at the target. greedy / simplex: one algorithm, no fallback.
class ModuloSchedulers : public circt::hlsest::ModuloScheduler {
public:
  enum Kind { GreedySimplex, Greedy, Simplex };
  explicit ModuloSchedulers(Kind kind) : kind(kind) {}

  StringRef name() const override {
    return kind == GreedySimplex ? "greedy-simplex"
           : kind == Greedy      ? "greedy"
                                 : "simplex";
  }
  bool isFunctionOfProblem() const override { return true; }

  void configure(const circt::hlsest::Config &cfg,
                 circt::hlsest::ConfigDiagnostics &) override {
    fastThreshold = static_cast<unsigned>(cfg.scheduling.fastThreshold);
    fastOpsThreshold = static_cast<unsigned>(cfg.scheduling.fastOpsThreshold);
    maxIIBumps = static_cast<unsigned>(cfg.scheduling.maxIIBumps);
    recurrenceRepairRounds =
        static_cast<unsigned>(cfg.scheduling.recurrenceRepairRounds);
    heightPriority = cfg.scheduling.heightPriority;
    fpUnitLimits = cfg.scheduling.fpUnitLimits;
    lowerIIOfBoth = cfg.scheduling.lowerIIOfBoth;
  }

  circt::hlsest::ScheduleOutcome
  schedule(ModuloProblem &problem, Operation *anchor,
           const circt::hlsest::SchedulingContext &ctx) const override {
    circt::hlsest::ScheduleOutcome out;
    unsigned targetII = ctx.requestedII.value_or(0);
    if (kind == Greedy) {
      FastModuloScheduler fast(problem, recurrenceRepairRounds, heightPriority,
                                 fpUnitLimits);
      out.success = succeeded(fast.schedule(maxIIBumps));
      out.label = "greedy";
    } else if (kind == Simplex) {
      out.success = succeeded(scheduleSimplex(problem, anchor));
      out.label = "simplex";
    } else {
      // MODIFIED: large bodies (more resource-limited ops than
      // `fast-threshold`, more operations than `fast-ops-threshold` (a fully
      // unrolled body of arithmetic, whose dense simplex tableau would not
      // fit in memory), or any body when `fast-threshold` is 0) go to the
      // greedy resource-bound scheduler; if it cannot find a schedule it
      // falls back to the simplex.
      unsigned limited = FastModuloScheduler::countLimitedOps(problem);
      bool scheduled = false, triedFast = false;
      StringRef label;
      bool hugeProblem = fastOpsThreshold != 0 &&
                         problem.getOperations().size() > fastOpsThreshold;
      if (fastThreshold == 0 || limited > fastThreshold || hugeProblem) {
        triedFast = true;
        FastModuloScheduler fast(problem, recurrenceRepairRounds, heightPriority,
                                 fpUnitLimits);
        scheduled = succeeded(fast.schedule(maxIIBumps));
        if (scheduled)
          label = "greedy";
        LLVM_DEBUG(if (!scheduled) llvm::dbgs()
                   << "fast modulo scheduler failed; falling back to simplex\n");
      }
      if (!scheduled) {
        scheduled = succeeded(scheduleSimplex(problem, anchor));
        if (scheduled)
          label = triedFast ? "simplex (greedy failed)" : "simplex";
      }
      // MODIFIED (T4, OPEN_ISSUES O9): the simplex scheduler now reports a
      // failed II bump instead of asserting; fall back to the greedy
      // scheduler then (the reverse of the fallback above).
      if (!scheduled && !triedFast) {
        LLVM_DEBUG(llvm::dbgs()
                   << "simplex modulo scheduler failed; falling back to fast\n");
        FastModuloScheduler fast(problem, recurrenceRepairRounds, heightPriority,
                                 fpUnitLimits);
        scheduled = succeeded(fast.schedule(maxIIBumps));
        if (scheduled)
          label = "greedy (simplex failed)";
      }
      // The simplex heuristic can fix a late operation (the last store of
      // an unrolled reduction) before the ops that share a port with each
      // other, and then bumps the II one step per conflict: keep the greedy
      // schedule when its II is lower (scheduling.modulo.lower_ii_of_both;
      // w9r13p_mx_r8 II 14 -> 8 = Vitis).
      if (scheduled && lowerIIOfBoth && label.starts_with("simplex"))
        if (keepLowerGreedySchedule(problem))
          label = "greedy (lower II than simplex)";
      // The floating-point unit limits (N135) are a property of the
      // placement, which only the greedy scheduler models: a loop the
      // simplex scheduled at II > 1 is placed again at that II.
      if (scheduled && fpUnitLimits && label.starts_with("simplex"))
        if (placeWithFPUnitsAtSameII(problem))
          label = "greedy (floating-point units at the simplex II)";
      out.success = scheduled;
      out.label = label.str();
    }
    // A user `pipeline II=N` is the II Vitis schedules for: a loop that could
    // start more often is still scheduled at N (with the ports and copies
    // that fit N: 8 reads at II=2 -> a RAM_1WNR of 3 copies, not the 7 of II
    // 1), and a loop whose resources or recurrences need more keeps its
    // larger II. Vitis sometimes finishes below the target (corpus loops with
    // target 8 ending at 3 and 4, unexplained); that is not modelled.
    if (kind == GreedySimplex && out.success &&
        targetII > *problem.getInitiationInterval()) {
      FastModuloScheduler fast(problem, recurrenceRepairRounds, heightPriority,
                                 fpUnitLimits);
      if (succeeded(fast.schedule(maxIIBumps, targetII)))
        out.label = "greedy (user II target)";
    }
    return out;
  }

private:
  /// Problem::verify() without its error diagnostics: a failed check here
  /// only means the other schedule is kept. Diagnostics of other threads
  /// (function passes run in parallel) pass through.
  static bool verifiesQuietly(ModuloProblem &problem) {
    MLIRContext *ctx = problem.getContainingOp()->getContext();
    std::thread::id self = std::this_thread::get_id();
    ScopedDiagnosticHandler quiet(ctx, [self](Diagnostic &) {
      return success(std::this_thread::get_id() == self);
    });
    return succeeded(problem.verify());
  }

  /// Schedules `problem` (already scheduled) with the greedy scheduler too;
  /// keeps that schedule when its II is lower, else restores the first one.
  bool keepLowerGreedySchedule(ModuloProblem &problem) const {
    std::optional<unsigned> firstII = problem.getInitiationInterval();
    if (!firstII || *firstII <= 1)
      return false;
    SmallVector<std::pair<Operation *, unsigned>> firstStart;
    for (Operation *op : problem.getOperations())
      if (std::optional<unsigned> t = problem.getStartTime(op))
        firstStart.push_back({op, *t});
    // Only a lower II is kept, so the greedy search stops below the
    // simplex's II (no schedule changes; a bounded search).
    // The greedy schedule must also pass the problem's own check (the
    // caller verifies the kept schedule, and a failed check fails the
    // pass); otherwise the valid simplex schedule stays (W9r13 review
    // finding 7).
    FastModuloScheduler fast(problem, recurrenceRepairRounds, heightPriority,
                                 fpUnitLimits);
    if (succeeded(fast.schedule(maxIIBumps, /*minII=*/1, *firstII)) &&
        *problem.getInitiationInterval() < *firstII &&
        verifiesQuietly(problem))
      return true;
    problem.setInitiationInterval(*firstII);
    for (auto [op, t] : firstStart)
      problem.setStartTime(op, t);
    return false;
  }

  /// Schedules `problem` (already scheduled at II > 1, with a floating-point
  /// op of a unit class) with the greedy scheduler at the same II and its
  /// floating-point unit limits; keeps that schedule when it passes the
  /// problem's check, else restores the first one.
  bool placeWithFPUnitsAtSameII(ModuloProblem &problem) const {
    std::optional<unsigned> firstII = problem.getInitiationInterval();
    if (!firstII || *firstII <= 1 ||
        llvm::none_of(problem.getOperations(), [](Operation *op) {
          return fpUnitClass(op).has_value();
        }))
      return false;
    SmallVector<std::pair<Operation *, unsigned>> firstStart;
    for (Operation *op : problem.getOperations())
      if (std::optional<unsigned> t = problem.getStartTime(op))
        firstStart.push_back({op, *t});
    FastModuloScheduler fast(problem, recurrenceRepairRounds, heightPriority,
                             fpUnitLimits);
    if (succeeded(fast.schedule(maxIIBumps, /*minII=*/*firstII,
                                /*belowII=*/*firstII + 1)) &&
        verifiesQuietly(problem))
      return true;
    problem.setInitiationInterval(*firstII);
    for (auto [op, t] : firstStart)
      problem.setStartTime(op, t);
    return false;
  }

  Kind kind;
  unsigned fastThreshold = 150, fastOpsThreshold = 4096, maxIIBumps = 4096;
  unsigned recurrenceRepairRounds = 0;
  bool heightPriority = false;
  bool fpUnitLimits = false;
  bool lowerIIOfBoth = true;
};

/// none: no state schedule; the BRAM port model applies its stretch-pair rule
/// to every sequential scope.
class NoSequentialScheduler : public circt::hlsest::SequentialScheduler {
public:
  StringRef name() const override { return "none"; }
  bool schedule(Block &, const circt::hlsest::SchedulingContext &,
                circt::hlsest::SequentialSchedule &) const override {
    return false;
  }
};

/// none: binds nothing (Phase 6 will add a binder).
class NoBinder : public circt::hlsest::Binder {
public:
  StringRef name() const override { return "none"; }
  void bind(const circt::hlsest::ScheduleView &,
            const circt::hlsest::SchedulingContext &,
            circt::hlsest::BindingResult &) const override {}
};

} // namespace

void circt::hlsest::builtin::registerOperatorTimingModels() {
  PluginRegistry<OperatorTimingModel>::instance().add(
      "calyx-fixed",
      "fixed operator latencies per class (scheduling.timing."
      "operator_latencies), no clock",
      [] { return std::make_unique<CalyxFixedTiming>(); }, "builtin");
}

void circt::hlsest::builtin::registerDependenceModels() {
  PluginRegistry<DependenceModel>::instance().add(
      "cached-o1",
      "intra-iteration memory dependences and iter_arg recurrences of the "
      "cached analysis (loop-carried memory dependences never reach the "
      "scheduler, OPEN_ISSUES O1)",
      [] { return std::make_unique<CachedO1Dependences>(); }, "builtin");
}

void circt::hlsest::builtin::registerModuloSchedulers() {
  auto &r = PluginRegistry<ModuloScheduler>::instance();
  r.add("greedy-simplex",
        "greedy resource-bound modulo scheduler above fast_threshold, else "
        "the simplex; each falls back to the other",
        [] {
          return std::make_unique<ModuloSchedulers>(
              ModuloSchedulers::GreedySimplex);
        },
        "builtin");
  r.add("greedy", "the greedy resource-bound modulo scheduler only",
        [] { return std::make_unique<ModuloSchedulers>(ModuloSchedulers::Greedy); },
        "builtin");
  r.add("simplex", "the simplex modulo scheduler only",
        [] {
          return std::make_unique<ModuloSchedulers>(ModuloSchedulers::Simplex);
        },
        "builtin");
}

void circt::hlsest::builtin::registerSequentialSchedulers() {
  PluginRegistry<SequentialScheduler>::instance().add(
      "none", "no state schedule (the stretch-pair rule applies)",
      [] { return std::make_unique<NoSequentialScheduler>(); }, "builtin");
}

void circt::hlsest::builtin::registerBinders() {
  PluginRegistry<Binder>::instance().add(
      "none", "binds nothing",
      [] { return std::make_unique<NoBinder>(); }, "builtin");
}

//===----------------------------------------------------------------------===//
// The schedule result as the IR carries it.
//===----------------------------------------------------------------------===//

circt::hlsest::ScheduleView
circt::hlsest::ScheduleView::fromIR(func::FuncOp func) {
  ScheduleView view;
  auto opSchedule = [](Operation *op, unsigned start) {
    OpSchedule s;
    s.op = op;
    s.start = start;
    if (auto d = op->getAttrOfType<DictionaryAttr>("hls.op_timing")) {
      if (auto c = d.getAs<StringAttr>("cls"))
        s.cls = c.getValue().str();
      if (auto l = d.getAs<IntegerAttr>("latency"))
        s.latency = static_cast<unsigned>(l.getInt());
    }
    if (auto u = op->getAttrOfType<IntegerAttr>("hls.unit"))
      s.unit = u.getInt();
    return s;
  };
  func.walk([&](circt::loopschedule::LoopSchedulePipelineOp pipe) {
    RegionSchedule r;
    r.region = pipe.getOperation();
    r.pipelined = true;
    r.ii = static_cast<unsigned>(pipe.getII());
    if (auto tc = pipe.getTripCount())
      r.tripCount = static_cast<int64_t>(*tc);
    if (auto label = pipe->getAttrOfType<StringAttr>(
            circt::hls_analysis::kLoopSchedulerAttr))
      r.scheduler = label.getValue().str();
    pipe.walk([&](circt::loopschedule::LoopSchedulePipelineStageOp stage) {
      for (Operation &op : stage.getBodyBlock())
        r.ops.push_back(opSchedule(&op, static_cast<unsigned>(stage.getStart())));
    });
    view.regions.push_back(std::move(r));
  });
  // Sequential regions a SequentialScheduler scheduled (hls.state).
  llvm::MapVector<Operation *, RegionSchedule> sequential;
  func.walk([&](Operation *op) {
    auto state = op->getAttrOfType<IntegerAttr>("hls.state");
    if (!state)
      return;
    Operation *parent = op->getParentOp();
    RegionSchedule &r = sequential[parent];
    r.region = parent;
    r.ops.push_back(opSchedule(op, static_cast<unsigned>(state.getInt())));
  });
  for (auto &kv : sequential)
    view.regions.push_back(std::move(kv.second));
  return view;
}

namespace circt::hls_analysis {

std::unique_ptr<mlir::Pass> createAffineToLoopSchedule() {
  return std::make_unique<AffineToLoopSchedule>();
}

void registerAffineToLoopScheduleAnalysisPass() {
  PassRegistration<AffineToLoopSchedule>();
}

}
