//===- LoopPragmas.h - loop-level HLS attributes shared by passes ---------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// Names of the loop attributes the cgeist front end emits for HLS pragmas and
// the ones --auto-pipeline-unroll adds, plus the one helper every consumer of
// `hls.flattened_parents` needs.
//
//===----------------------------------------------------------------------===//

#ifndef CIRCT_DIALECT_RESOURCE_PASSES_LOOPPRAGMAS_H
#define CIRCT_DIALECT_RESOURCE_PASSES_LOOPPRAGMAS_H

#include "mlir/Dialect/Affine/IR/AffineOps.h"
#include "mlir/IR/BuiltinAttributes.h"
#include "llvm/ADT/StringRef.h"

namespace circt::hls_analysis {

/// `hls.pipeline = [{II = N : i32, ...}]`: a user `#pragma HLS pipeline`, or
/// `[{II = 0 : i32, source = "auto"}]` written by --auto-pipeline-unroll.
constexpr llvm::StringLiteral kLoopPipelineAttr = "hls.pipeline";
/// `hls.pipeline_off` (unit): `#pragma HLS pipeline off`.
constexpr llvm::StringLiteral kLoopPipelineOffAttr = "hls.pipeline_off";
/// `hls.if_arms` (DenseI64ArrayAttr, pairs [if id, arm number, ...]) on a
/// memory access that --convert-affine-to-loopschedule hoisted out of the arms
/// of an scf.if (hoistIfBodies), innermost if first. Ids are unique within the
/// function. Two accesses that carry the same if id with different arm numbers
/// never execute together (--bram-seq-dual-port, VITIS_NOTES.md N12).
constexpr llvm::StringLiteral kIfArmsAttr = "hls.if_arms";
/// `hls.unroll = [{factor = F : i32, ...}]`, F = 0 for a complete unroll.
constexpr llvm::StringLiteral kLoopUnrollAttr = "hls.unroll";
/// `hls.unroll_off` (unit): `#pragma HLS unroll off`.
constexpr llvm::StringLiteral kLoopUnrollOffAttr = "hls.unroll_off";
/// `hls.unroll_partial = F : i64` (written by --auto-pipeline-unroll in place
/// of a consumed `hls.unroll`): the loop keeps a partial user unroll (factor
/// F below its trip count, 1 included). Vitis never unrolls such a loop
/// completely for an enclosing automatic pipeline, so no loop around it is
/// auto-pipelined; the loop itself still is.
constexpr llvm::StringLiteral kLoopUnrollPartialAttr = "hls.unroll_partial";
/// `hls.flattened_parents = N : i64` on a pipelined loop: Vitis flattens its N
/// directly enclosing affine.for ancestors into the pipeline, so their
/// induction variables are loop-variant for that pipeline.
constexpr llvm::StringLiteral kLoopFlattenedParentsAttr = "hls.flattened_parents";
/// `hls.auto_unrolled = [{factor = F : i64, loc = loc(...)}, ...]` on a
/// pipelined loop (written by --auto-pipeline-unroll): the loops it unrolled
/// completely for that pipeline, in unroll order (innermost first), with
/// their trip counts. A decision record for --bram-debug; no estimate reads
/// it.
constexpr llvm::StringLiteral kLoopAutoUnrolledAttr = "hls.auto_unrolled";
/// `hls.scheduler = "<name>"` on a pipelined loop (written by
/// --convert-affine-to-loopschedule, carried onto the loopschedule.pipeline
/// op): the modulo scheduler that produced its schedule, "simplex" or
/// "greedy", with " (simplex failed)" / " (greedy failed)" when the other one
/// was tried first and failed (OPEN_ISSUES O9). A record for --bram-debug; no
/// estimate reads it.
constexpr llvm::StringLiteral kLoopSchedulerAttr = "hls.scheduler";
/// Value of the `source` key of an automatic `hls.pipeline` tag.
constexpr llvm::StringLiteral kLoopPipelineAutoSource = "auto";
/// `hls.call_boundary = "<callee>"` on a loop (written by
/// --auto-pipeline-unroll): the loop is not pipelined because it calls a kept
/// function (`#pragma HLS inline off`) that still has loops of its own; Vitis
/// pipelines those in the callee and leaves the caller loop sequential
/// (VITIS_NOTES.md N14 R7, kernel w3h_cb_nest256). --convert-affine-to-
/// loopschedule leaves such a loop an affine.for instead of pipelining it as
/// an innermost loop.
constexpr llvm::StringLiteral kLoopCallBoundaryAttr = "hls.call_boundary";
/// `hls.call_occupancy = N : i64` on a func.call inside a pipelined loop
/// (written by --auto-pipeline-unroll): the cycles one call holds its callee
/// instance, estimated from the callee's memory accesses, at most two per
/// memory per cycle (VITIS_NOTES.md N14 R7: `inl_f2_unroll_off`, 16 accesses
/// of each row per call, II 8). --convert-affine-to-loopschedule uses it as
/// the call's latency and as the II bound of the calls an instance serves.
constexpr llvm::StringLiteral kCallOccupancyAttr = "hls.call_occupancy";
/// `hls.uncounted` (unit, from cgeist): a loop whose exit test compares a
/// counter with a runtime bound of a wider type that the counter is not known
/// to reach (`for (uint8_t i = 0; i < n; i++)`, int n), raised by assuming
/// that the loop terminates. Vitis cannot compute its trip count and does not
/// collapse it with its perfect inner nest before the pipeline decision
/// (VITIS_NOTES.md N15).
constexpr llvm::StringLiteral kLoopUncountedAttr = "hls.uncounted";

/// Number of enclosing loops flattened into `loop`'s pipeline (0 if none).
inline unsigned getFlattenedParents(mlir::affine::AffineForOp loop) {
  auto attr = loop->getAttrOfType<mlir::IntegerAttr>(kLoopFlattenedParentsAttr);
  return attr && attr.getInt() > 0 ? static_cast<unsigned>(attr.getInt()) : 0;
}

/// The outermost affine.for whose iteration space belongs to `loop`'s
/// pipeline: `loop` itself, or its N-th enclosing affine.for when `loop`
/// carries `hls.flattened_parents = N`. A value is invariant for the pipeline
/// iff it is defined outside this loop.
inline mlir::affine::AffineForOp
getFlattenedRoot(mlir::affine::AffineForOp loop) {
  mlir::affine::AffineForOp root = loop;
  for (unsigned n = getFlattenedParents(loop); n > 0; --n) {
    auto parent = root->getParentOfType<mlir::affine::AffineForOp>();
    if (!parent)
      break;
    root = parent;
  }
  return root;
}

} // namespace circt::hls_analysis

#endif // CIRCT_DIALECT_RESOURCE_PASSES_LOOPPRAGMAS_H
