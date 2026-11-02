//===- DoWhileFlatten.h - Vitis' do-while flatten refusal -------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// Vitis refuses to flatten a parent loop p into its automatically pipelined
// child (`[HLS 200-960] Cannot flatten loop ... either the parent loop or sub
// loop is do-while loop`) when the pipeline's complete unroll of a sub-loop
// of the child creates a subscript `p + 1` of a multi-dimensional array that
// every iteration of the child computes: the front end's LICM hoists that
// address out of the child, it merges with p's increment and leaves p in
// do-while form (VITIS_NOTES N96, kernels w9r13p_dv_p1 / dv_p2 / dv_expl /
// dv_lin / dv_val; N64 / N76's kernels; ECG_Classifier baseline conv1d_2c /
// 3c / 4c, Dehazing tile_median).
//
// What triggers it, and what does not:
//  - `T[i + k][j + l]` with k, l unrolled by j's pipeline (dv_p1): k = 1
//    gives `T[i + 1][..]`: i is not flattened into j.
//  - `T[(i + 2k) & 63][..]` (dv_p2), a linearised `T[(i + k) * 64 + ..]`
//    (dv_lin), `i + 1` written out without a sub-loop (dv_expl) and `i + k`
//    used as a value, not a subscript (dv_val): flattened.
//  - A sub-loop of trip count 2 does not trigger it (kernels w9r13i_yp_d,
//    a 2 x 2 window, flattened, against w9r13i_yp_c, 3 x 3, refused;
//    Yolo-v3-tiny's stride-1 max pool, w9r13i_yp_a / yp_b / yp_e / yp_f:
//    flattened whatever the element type, nest depth or reduction): the
//    subscript must come from a sub-loop of at least `minSubLoopTrip`
//    iterations (unconfirmed why; LLVM may unroll a 2-trip loop before its
//    LICM, as if written out).
//  - A guard of the access on the child's index (`if (c & 1)`, n64_ifconly)
//    keeps the address in the child: flattened. A guard that is false for
//    the copy that makes `p + 1` (`if (k & 1)`, n64_ifkonly) removes it:
//    flattened. A guard on p and the sub-loop only (`if ((l + k) & 1)`,
//    n64_iflonly; ECG's `if (l + k < 2 || l + k > 93)`) is invariant in the
//    child and does not stop the hoist: refused.
//
//===----------------------------------------------------------------------===//

#ifndef CIRCT_DIALECT_RESOURCE_PASSES_DOWHILEFLATTEN_H
#define CIRCT_DIALECT_RESOURCE_PASSES_DOWHILEFLATTEN_H

#include "mlir/Dialect/Affine/IR/AffineOps.h"
#include "llvm/ADT/SmallPtrSet.h"

namespace circt::hls_analysis {

/// The loops around `pipelined` (affine.for ancestors in its function) whose
/// next index `p + step` some access inside `pipelined` takes as a subscript
/// of a multi-dimensional memref once the loops inside `pipelined` are
/// unrolled (N96). Call it before the unroll: the subscript must come from
/// a sub-loop's index, of a sub-loop of at least `minSubLoopTrip`
/// iterations. `maxCombinations` bounds the sub-loop index values tried per
/// access.
llvm::SmallPtrSet<mlir::Operation *, 4>
doWhileParents(mlir::affine::AffineForOp pipelined, uint64_t minSubLoopTrip,
               uint64_t maxCombinations = 4096);

} // namespace circt::hls_analysis

#endif // CIRCT_DIALECT_RESOURCE_PASSES_DOWHILEFLATTEN_H
