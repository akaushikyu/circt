//===- PreBankForwarding.h - forwarding before partitioning -----*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef CIRCT_DIALECT_RESOURCE_PASSES_PREBANKFORWARDING_H
#define CIRCT_DIALECT_RESOURCE_PASSES_PREBANKFORWARDING_H

#include "mlir/IR/BuiltinOps.h"

namespace circt::hls_analysis {

/// Counts of forwardPartitionedStores.
struct PreBankForwardingStats {
  unsigned forwardedLoads = 0;
  unsigned removedStores = 0;
};

/// Store-to-load forwarding and dead-store elimination, within the body of
/// each pipelined loop, for the local arrays an `array_partition` pragma
/// splits (VITIS_NOTES N138): a load of the address the body stored before,
/// with no other access to the array in between, takes the stored value; a
/// store overwritten later in the body at the same address, with no read of
/// the array in between, is removed. Vitis' LLVM does this on the unrolled
/// body before the partition; --convert-affine-to-loopschedule does the same
/// for whole arrays and constant banks, but a run-time-bank access (one
/// load per bank and a select, one guarded store per bank) hides the address
/// from it. Annotates the surviving store with `hls.removed_stores` /
/// `hls.forwarded_loads`.
PreBankForwardingStats forwardPartitionedStores(mlir::ModuleOp module);

} // namespace circt::hls_analysis

#endif // CIRCT_DIALECT_RESOURCE_PASSES_PREBANKFORWARDING_H
