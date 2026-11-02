//===- PassPolicies.h - Plugin interfaces of the decision passes -*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// Three passes are a decision procedure of the modelled tool over the whole
// IR; each delegates the decision to a plugin (design memo section 8.1):
//
//   PipelinePolicy   --auto-pipeline-unroll: which loops are pipelined,
//                    unrolled and flattened (builtin vitis-pipeline-loops:
//                    config_compile -pipeline_loops with the LICM model)
//   PartitionPolicy  --infer-vitis-split-array: the automatic partitions and
//                    the port-pressure inference (builtin vitis-td)
//   FoldRuleSet      --vitis-fold: what folds (builtins vitis-undef, zero)
//
// A policy writes the pass's IR contract: PipelinePolicy the hls.pipeline /
// hls.flattened_parents / hls.auto_unrolled / hls.unroll_partial tags and the
// unrolled loops, PartitionPolicy hls.array_partition / hls.registers, so
// that the passes after them work whatever policy ran.
//
//===----------------------------------------------------------------------===//

#ifndef CIRCT_DIALECT_RESOURCE_PLUGINS_PASSPOLICIES_H
#define CIRCT_DIALECT_RESOURCE_PLUGINS_PASSPOLICIES_H

#include "circt/Dialect/Resource/Plugins/Plugin.h"

#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/IR/BuiltinOps.h"
#include "mlir/IR/PatternMatch.h"
#include "mlir/Support/LogicalResult.h"

#include <functional>
#include <memory>
#include <string>

namespace circt::hlsest {

/// The resolved options of --auto-pipeline-unroll (an option given
/// explicitly, else the configuration).
struct PipelineDecisionOptions {
  unsigned pipelineLoops = 64;
  bool promotePipelined = true;
  bool floatLoadsPerfect = true;
  double callDepthBudgetNs = 7.3;
  /// Prints one remark per decision when set.
  std::function<void(mlir::Location, const llvm::Twine &)> remark;
};

class PipelinePolicy : public PluginBase {
public:
  virtual mlir::LogicalResult
  decide(mlir::ModuleOp module, const PipelineDecisionOptions &options) const = 0;
};

/// The resolved options of --infer-vitis-split-array.
struct PartitionOptions {
  unsigned targetII = 1, ports = 2, readPorts = 1, writePorts = 1;
  unsigned maxDims = 1;
  int64_t maxFactor = 0, completeThreshold = 4;
  bool rotatingBanks = false, includePorts = false;
  bool throughputDrivenOff = true; ///< td=off
  bool autoPartitions = false;     ///< td=auto with the rules of td=off
  bool annotatePressure = true, emitRemarks = false, autoPipeline = true;
};

/// Counters the policy reports back as the pass statistics.
struct PartitionStatistics {
  unsigned regions = 0, partitioned = 0, unresolved = 0, registers = 0,
           constantDims = 0, multiConstantDims = 0, unbankable = 0;
};

class PartitionPolicy : public PluginBase {
public:
  virtual mlir::LogicalResult run(mlir::func::FuncOp func,
                                  const PartitionOptions &options,
                                  PartitionStatistics &stats) const = 0;
};

/// One rewrite a fold rule made, for the hls.vitis_fold report.
struct FoldNote {
  std::string rule;
  mlir::Location loc;
  mlir::Location source;
  std::string detail;
  std::string func; ///< the enclosing function's symbol, empty outside one
};

/// The rules of a rule set that are not rewrite patterns, over one root op
/// (it may keep what it learnt between rounds).
class RuleFolder {
public:
  virtual ~RuleFolder();
  /// One round; true when the IR changed.
  virtual bool run(llvm::SmallVectorImpl<FoldNote> &notes) = 0;
};

class FoldRuleSet : public PluginBase {
public:
  /// The rewrite patterns of the rule set (added to the canonicalization
  /// patterns when canonicalize is on).
  virtual void populate(mlir::RewritePatternSet &patterns,
                        mlir::MLIRContext *context) const = 0;
  /// The rules that are not patterns (the undefined-value propagation),
  /// run before the rewrite and after each round of it; null when there are
  /// none.
  virtual std::unique_ptr<RuleFolder> createFolder(mlir::Operation *root) const {
    return nullptr;
  }
  /// Whether the canonicalization's select-to-min/max patterns must be left
  /// out (they lose the compare an undefined value depends on).
  virtual bool keepSelectCompare() const { return false; }
};

} // namespace circt::hlsest

#endif // CIRCT_DIALECT_RESOURCE_PLUGINS_PASSPOLICIES_H
