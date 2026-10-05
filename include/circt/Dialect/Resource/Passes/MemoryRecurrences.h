//===- MemoryRecurrences.h - loop-carried memory recurrences --------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// The II bound a loop-carried memory recurrence puts on a pipelined loop, as
// Vitis sets it (VITIS_NOTES N87, 23 kernels w9r11p_rr_*; OPEN_ISSUES O1).
// --convert-affine-to-loopschedule runs it on every innermost loop it
// schedules, a `pipeline off` loop included: there the bound changes no II,
// and the register-served accesses (R1 / R3, N90 (a) / (b)) take no port
// either (W9r11 review D9: kernel w9r11rev_gd_np, gd_f with `pipeline off`:
// Vitis 1 BRAM = hls-est; w9r11rev_rr_np: Vitis 1, hls-est 2, the extra
// port from the sequential port model N12, not from this rule):
//
//   A load L and a store S of one memory, with a data path from L's value to
//   the value S stores (the read-modify-write chain; a store and a later load
//   of the same address in one iteration forward the value, so k chained
//   read-modify-writes are one chain), and a smallest distance d >= 1 such
//   that S in iteration n writes the address L reads in iteration n + d:
//
//   (R1) d = 1, same address (an element invariant in the innermost loop of
//        the pipelined nest): Vitis promotes the element to a register; the
//        II is the chain's recurrence latency, at least 1 (fadd 4, dadd 5,
//        fmul 3, dmul 6, integer add / multiply 0 -> 1; N83).
//   (R3) d = 1, different addresses (a[i] = a[i-1] + x): the load is
//        replaced by the forwarded value; the same II as R1.
//   (R4) an address Vitis cannot compute (acc[idx[i]]), the same index
//        value for L and S: a reuse register, the same II as R1.
//   (N154) R1's shape on a lane chosen at run time of an aggregated word
//        (hls.dynamic_lane): no promotion; II >= 3 + chain (the R2 bound
//        with d = 1 plus the lane insert).
//   (R2) d >= 2: the load of iteration n + d issues at least one state after
//        the store of iteration n: II >= ceil((2 + chain) / d) (fadd 6,
//        fmul 5, integer add 2 states from load to store, inclusive).
//
// The recurrence of the register (R1, R3, R4) does not involve the memory's
// ports, so the bound is applied as a minimum II of the loop rather than as
// an edge between the load and the store.
//
//===----------------------------------------------------------------------===//

#ifndef CIRCT_DIALECT_RESOURCE_PASSES_MEMORYRECURRENCES_H
#define CIRCT_DIALECT_RESOURCE_PASSES_MEMORYRECURRENCES_H

#include "mlir/IR/Operation.h"
#include "llvm/ADT/DenseMap.h"
#include "llvm/ADT/STLFunctionalExtras.h"
#include "llvm/ADT/MapVector.h"
#include "llvm/ADT/SetVector.h"
#include "llvm/ADT/StringRef.h"

#include <optional>
#include <string>

namespace circt::hls_analysis {

/// The binding recurrence of a loop.
struct MemoryRecurrence {
  unsigned ii = 1;                   ///< the II bound it implies
  int64_t distance = 0;              ///< d; 1 for an unknown address (R4)
  int64_t chain = 0;                 ///< recurrence latency of the chain
  std::string rule;                  ///< R1, R2, R3 or R4
  mlir::Operation *load = nullptr;   ///< L
  mlir::Operation *store = nullptr;  ///< S
};

/// What the memory recurrences of one loop imply.
struct MemoryRecurrences {
  /// The binding recurrence (largest II bound), when one needs more than 1.
  std::optional<MemoryRecurrence> bound;
  /// The accesses served by a register instead of the memory: under R1 every
  /// access of the promoted element but the first load and the last store,
  /// under R3 the forwarded load, and the dead guarded stores
  /// (MemoryRecurrenceOptions::guardedStoreElimination). They use no port.
  llvm::SetVector<mlir::Operation *> promoted;
  /// The rule that serves each promoted access from a register: "R1", "R3"
  /// (N87), "N90a" (a guarded store a later store overwrites), "N90b" (a
  /// guarded load after a store of its address); a --bram-debug record.
  llvm::DenseMap<mlir::Operation *, llvm::StringRef> rule;
  /// The access that stands for promoted ones (the R1 element's first load,
  /// the R3 store) and how many: a --bram-debug record.
  llvm::MapVector<mlir::Operation *, unsigned> standsFor;
  /// The (store, load) pairs of N154's recurrences: the scheduler keeps the
  /// next iteration's load after the store (a carried dependence), since the
  /// word stays in memory.
  llvm::SmallVector<std::pair<mlir::Operation *, mlir::Operation *>>
      laneRecurrences;
};

/// Which of the analysis' results are wanted.
struct MemoryRecurrenceOptions {
  /// The II bound and the register promotion of R1 / R3
  /// (scheduling.dependences.memory_recurrences).
  bool recurrences = true;
  /// A guarded store a later unconditional store of the same address
  /// overwrites in the same iteration uses no port
  /// (tool.hls.middle_end.dse_guarded_stores).
  bool guardedStoreElimination = true;
  /// A load under an if that reads what a top-level store wrote earlier in
  /// the same iteration uses no port
  /// (tool.hls.middle_end.forward_to_guarded_loads).
  bool forwardToGuardedLoads = true;
  /// R4 (one unknown address value): the II is at least this (N117,
  /// scheduling.dependences.unknown_address_min_ii); 0 keeps the chain alone.
  int64_t unknownAddressMinII = 0;
  /// A `#pragma HLS dependence variable=<v> inter false` removes the
  /// loop-carried bounds of <v> (N122,
  /// scheduling.dependences.user_inter_independence).
  bool userInterIndependence = false;
  /// A read-modify-write of a run-time lane of an aggregated word is a
  /// recurrence through the memory, II 3 + chain, not a promoted element
  /// (N154, scheduling.dependences.dynamic_lane_rmw).
  bool dynamicLaneRmw = true;
};

/// The memory recurrences of `loop` (an affine.for or a pipelined scf.for).
/// `recurrenceLatency(op)` is the cycles `op` adds to a recurrence chain.
/// `window` iterations are evaluated to find dependence distances.
MemoryRecurrences findMemoryRecurrences(
    mlir::Operation *loop,
    llvm::function_ref<int64_t(mlir::Operation *)> recurrenceLatency,
    const MemoryRecurrenceOptions &options, unsigned window = 512);

/// The attribute on an access served by a register (MemoryRecurrences::
/// promoted), a string naming the rule (MemoryRecurrences::rule): no port
/// pool in the scheduler, no port demand in --bram-analysis.
constexpr llvm::StringLiteral kPromotedAccessAttr = "hls.register_promoted";

/// The counter on the access that stands for them (MemoryRecurrences::
/// standsFor).
constexpr llvm::StringLiteral kPromotedCountAttr =
    "hls.register_promoted_accesses";

inline bool isPromotedAccess(mlir::Operation *op) {
  return op->hasAttr(kPromotedAccessAttr);
}

} // namespace circt::hls_analysis

#endif // CIRCT_DIALECT_RESOURCE_PASSES_MEMORYRECURRENCES_H
