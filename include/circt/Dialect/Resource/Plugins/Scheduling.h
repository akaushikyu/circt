//===- Scheduling.h - Plugin interfaces of the scheduler ------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// The five scheduling interfaces of --convert-affine-to-loopschedule (MEMOS
// decision #37, design memo section 8.7), in the order the pass calls them per
// pipelined region:
//
//   DependenceModel      the operations, memory dependences and iter_arg
//                        recurrences of the problem (builtin cached-o1)
//   OperatorTimingModel  operation -> operator class, latency, delays, impl
//                        (builtin calyx-fixed)
//   ModuloScheduler      the II and the start times (builtins greedy-simplex,
//                        greedy, simplex)
//   SequentialScheduler  a state schedule of a non-pipelined region (builtin
//                        none: the BRAM port model's stretch-pair rule
//                        applies)
//   Binder               operation -> functional unit (builtin none)
//
// The pass keeps the mechanics every scheduler relies on: region selection,
// the structural dependence edges, the memory port pools (from the
// MemoryArchitecturePolicy), problem.check()/verify(), schedule reuse and the
// IR it writes. The schedule result travels as IR (loopschedule.pipeline II
// and stage starts, hls.scheduler, hls.state, hls.op_timing, hls.unit); the
// BRAM port model reads the II and the stage starts, so a replacement
// scheduler is BRAM-equivalent only if its stage starts match.
//
//===----------------------------------------------------------------------===//

#ifndef CIRCT_DIALECT_RESOURCE_PLUGINS_SCHEDULING_H
#define CIRCT_DIALECT_RESOURCE_PLUGINS_SCHEDULING_H

#include "circt/Analysis/DependenceAnalysis.h"
#include "circt/Dialect/Resource/Passes/CyclicSchedulingAnalysisModified.h"
#include "circt/Dialect/Resource/Plugins/Plugin.h"
#include "circt/Scheduling/Problems.h"

#include "mlir/Dialect/Affine/IR/AffineOps.h"
#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "llvm/ADT/DenseMap.h"

#include <optional>
#include <string>

namespace circt::hlsest {

class OperatorTimingModel;

/// What the timing model says about one operation.
struct OperatorTiming {
  /// The operator-type name; operations of one class share one operator type
  /// of the problem, so they must agree on latency.
  std::string cls;
  unsigned latency = 0; ///< cycles
  std::optional<unsigned> recurrenceLatency; ///< nullopt: latency
  float inDelayNs = 0, outDelayNs = 0;       ///< 0: unbounded chaining
  std::string impl; ///< a device arith[] id or "logic"; "" when not chosen
  ResourceVector cost; ///< per unit (empty today; Phase 6)
  unsigned occupancy = 1; ///< cycles a unit is held (recorded, ignored)
  std::optional<unsigned> unitLimit; ///< allocation limit; nullopt: unlimited
  /// With unitLimit: the units are per object rather than per class (one
  /// resource per distinct instance key, e.g. one port per hls::stream object,
  /// VITIS_NOTES N82); empty: one resource for the class.
  std::string unitInstance;
};

using OperatorTimingMap = llvm::DenseMap<mlir::Operation *, OperatorTiming>;

/// What a scheduling call knows about the run.
struct SchedulingContext {
  double periodNs = 0;  ///< run.clock_ns minus the timing margin
  double clockNs = 0;   ///< run.clock_ns
  const Device *device = nullptr;
  /// The II the user asked for (pipeline II=N > 1), when the profile honours
  /// it (scheduling.modulo.user_ii_target).
  std::optional<unsigned> requestedII;
  /// Every operation of the problem with its timing (modulo problems only).
  const OperatorTimingMap *timing = nullptr;
  const OperatorTimingModel *timingModel = nullptr;
};

class OperatorTimingModel : public PluginBase {
public:
  /// nullopt: the operation is not supported (its loop stays sequential).
  /// Called for every operation of a pipelined loop body; for a memory
  /// access (load, store, store_enable) only the latency is used (the pass
  /// gives every access of one memref one operator type with the memory's
  /// port pools).
  virtual std::optional<OperatorTiming>
  timing(mlir::Operation *op, const SchedulingContext &context) const = 0;
  /// The operator types the pass inserts first, in this order.
  virtual void library(llvm::SmallVectorImpl<OperatorTiming> &out) const {}
  /// The latency keys it reads (scheduling.timing.operator_latencies).
  virtual void listClasses(llvm::SmallVectorImpl<std::string> &out) const = 0;
};

/// What the pass has already computed, for a dependence model to read (never
/// to change).
struct DependenceInputs {
  circt::hls_analysis::CyclicSchedulingAnalysis &cached;
  circt::analysis::InnermostLoopDependenceAnalysis &rekeyed;
};

class DependenceModel : public PluginBase {
public:
  /// The operations of the loop body, the memory dependences and the iter_arg
  /// recurrences, in a deterministic order. The pass adds the structural
  /// edges (an if's yields to the if, every store to the terminator)
  /// afterwards.
  virtual circt::scheduling::ModuloProblem
  populate(mlir::affine::AffineForOp loop, DependenceInputs &inputs) const = 0;
};

struct ScheduleOutcome {
  bool success = false;
  std::string label; ///< written as hls.scheduler
  /// The offset of an operation within its start cycle (chaining); empty: 0.
  llvm::DenseMap<mlir::Operation *, float> startInCycleNs;
};

class ModuloScheduler : public PluginBase {
public:
  /// Sets the II and every start time; must not add or remove operations,
  /// operator types, limits or dependences.
  virtual ScheduleOutcome schedule(circt::scheduling::ModuloProblem &problem,
                                   mlir::Operation *anchor,
                                   const SchedulingContext &context) const = 0;
  /// True only if the result depends on nothing but the problem and the
  /// requested II (then the pass reuses the schedule of an identical
  /// problem); false turns reuse off.
  virtual bool isFunctionOfProblem() const { return false; }
};

/// A state schedule of one non-pipelined region.
struct SequentialSchedule {
  mlir::Block *region = nullptr;
  unsigned numStates = 0;
  llvm::DenseMap<mlir::Operation *, unsigned> stateOf;
};

class SequentialScheduler : public PluginBase {
public:
  /// false: not scheduled, the stretch-pair rule applies to the region. On
  /// true the pass writes hls.state on every operation of `out.stateOf`.
  virtual bool schedule(mlir::Block &region, const SchedulingContext &context,
                        SequentialSchedule &out) const = 0;
};

/// One operation of a schedule, as the IR carries it.
struct OpSchedule {
  mlir::Operation *op = nullptr;
  unsigned start = 0; ///< stage start (pipelined) or hls.state (sequential)
  std::optional<std::string> cls;
  std::optional<unsigned> latency;
  std::optional<int64_t> unit;
};

/// One scheduled region.
struct RegionSchedule {
  mlir::Operation *region = nullptr; ///< the pipeline op, or the block's parent
  bool pipelined = false;
  unsigned ii = 0; ///< 0: sequential
  std::optional<int64_t> tripCount;
  std::string scheduler;
  llvm::SmallVector<OpSchedule> ops;
};

/// The schedule result of one function, read back from the IR.
struct ScheduleView {
  llvm::SmallVector<RegionSchedule> regions;
  /// Builds the view of one function (pipelines with their stages; scopes
  /// whose operations carry hls.state).
  static ScheduleView fromIR(mlir::func::FuncOp func);
};

/// What a binder decides: operation -> unit id, and the multiplexer inputs.
struct BindingResult {
  llvm::DenseMap<mlir::Operation *, int64_t> opToUnit;
  struct Mux {
    int64_t unit = 0;
    unsigned pin = 0, inputs = 0, bits = 0;
  };
  llvm::SmallVector<Mux> muxes;
};

class Binder : public PluginBase {
public:
  /// Binds the operations of one function (`view`); the built-in "none"
  /// leaves `out` empty. The pass writes hls.unit on the bound operations.
  virtual void bind(const ScheduleView &view, const SchedulingContext &context,
                    BindingResult &out) const = 0;
};

} // namespace circt::hlsest

#endif // CIRCT_DIALECT_RESOURCE_PLUGINS_SCHEDULING_H
