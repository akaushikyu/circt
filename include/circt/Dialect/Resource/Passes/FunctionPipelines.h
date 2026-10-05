//===- FunctionPipelines.h - kept callees of pipelined loops ----*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// Three pieces of Vitis HLS 2025.1's module structure that the memory
// pricing of --bram-analysis needs (VITIS_NOTES N143 - N145, W9r19):
//
//   - Aggregated struct pointers (VITIS_NOTES N147): a pointer-to-struct
//     argument of the top function without a memory interface is one wide
//     scalar (hlsyn aes `ctx`: `ctx_i` / `ctx_o` 768 bits, ap_ovld; kernel
//     w9r19p_ri_s): its accesses, and those of every kept callee parameter
//     bound to it, are register reads and writes, never memory ports.
//   - Outlined pipelined loops (N143): a pipelined loop becomes a module of
//     its own (`<func>_Pipeline_<loop>`) exactly when its function also
//     accesses memory or runs another loop outside it (an aggregated struct
//     pointer's members count as memory here); calls, scalar arithmetic and
//     a returned scalar do not count.
//   - Function pipelines (N144): a kept, loop-free callee with a call site in
//     a pipelined loop (or in another function pipeline) is pipelined at the
//     caller loop's target II (its pragma II, 1 when it names none), raised
//     by its own port limits (its busiest memory, two accesses per cycle;
//     ROMs, registers and aggregated scalars excluded: a ROM is replicated
//     instead).
//
//===----------------------------------------------------------------------===//

#ifndef CIRCT_DIALECT_RESOURCE_PASSES_FUNCTIONPIPELINES_H
#define CIRCT_DIALECT_RESOURCE_PASSES_FUNCTIONPIPELINES_H

#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/IR/BuiltinOps.h"
#include "llvm/ADT/DenseMap.h"
#include "llvm/ADT/DenseSet.h"
#include "llvm/ADT/STLFunctionalExtras.h"

#include <optional>

namespace circt::hls_analysis {

/// The memref values that stand for an aggregated struct pointer (N147):
/// qualifying top-function arguments and, to a fixpoint, the memref
/// parameters of defined callees that every call site binds to one of them.
struct AggregatedScalars {
  llvm::DenseSet<mlir::Value> roots;

  /// Whether `mem` (an access's memref, through views, polygeist pointer
  /// round trips and llvm.getelementptr) names an aggregated struct pointer.
  bool contains(mlir::Value mem) const;
};

/// Computes AggregatedScalars for `module` (empty when the configuration key
/// tool.hls.structs.top_pointer_scalar is off). A root function (one no
/// in-module call reaches) contributes every pointer-to-one-struct argument
/// (`memref<?x!llvm.struct<...>>` not of a library class, or `memref<?xNxT>`
/// that its mangled name declares a class pointer) without a memory or
/// stream interface, every access of which selects element 0 and whose
/// derived pointers are never carried around a loop (a pointer walk such as
/// spector matrix_multiplication's `*A++` is an array).
AggregatedScalars computeAggregatedScalars(mlir::ModuleOp module);

/// N143: whether the pipelined loop `pipeline` (a loopschedule.pipeline)
/// becomes a module of its own: its function also has, outside it, another
/// loop or an access of a memory (a load or store of a memref that is not a
/// one-element variable or registers; an aggregated struct pointer counts,
/// W9 round 19 review defect 1). Calls do not count.
bool isOutlinedPipeline(mlir::Operation *pipeline);

/// The outermost outlined pipelined loop of `parent` around `op`, or null
/// (`op` is in the parent module's own body).
mlir::Operation *outlinedPipelineAround(mlir::Operation *op,
                                        mlir::func::FuncOp parent);

/// N144: the function pipelines of a module and their II.
struct FunctionPipelineModel {
  llvm::DenseMap<mlir::Operation *, unsigned> ii;

  /// The II of `fn` as a function pipeline, nullopt when it is not one.
  std::optional<unsigned> iiOf(mlir::Operation *fn) const {
    auto it = ii.find(fn);
    if (it == ii.end())
      return std::nullopt;
    return it->second;
  }
};

/// Computes the function pipelines among the functions `inScope` accepts
/// (all when null). `isReadOnlyGlobal(global)` says whether a memref.global
/// is a ROM (never written): its accesses do not limit the II.
FunctionPipelineModel computeFunctionPipelines(
    mlir::ModuleOp module, const AggregatedScalars &scalars,
    llvm::function_ref<bool(mlir::func::FuncOp)> inScope,
    llvm::function_ref<bool(mlir::Operation *)> isReadOnlyGlobal);

} // namespace circt::hls_analysis

#endif // CIRCT_DIALECT_RESOURCE_PASSES_FUNCTIONPIPELINES_H
