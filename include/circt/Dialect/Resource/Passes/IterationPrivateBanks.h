//===- IterationPrivateBanks.h - banks one loop iteration owns --*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef CIRCT_DIALECT_RESOURCE_PASSES_ITERATIONPRIVATEBANKS_H
#define CIRCT_DIALECT_RESOURCE_PASSES_ITERATIONPRIVATEBANKS_H

#include "mlir/IR/BuiltinOps.h"

namespace circt::hls_analysis {

/// Marks `hls.registers` on every bank of a partitioned local array whose
/// elements one iteration of one loop writes and reads (VITIS_NOTES N92):
/// every access lies in the body of one loop L at one address that is an
/// injective affine function of L's index (and of values that do not change
/// inside L), and the first access in L's body is an unconditional store.
/// Vitis' reflow promotes such an element to a scalar (LLVM LICM), forwards
/// the stores into the loads and deletes the dead alloca. Returns the number
/// of banks marked.
unsigned markIterationPrivateBanks(mlir::ModuleOp module);

} // namespace circt::hls_analysis

#endif // CIRCT_DIALECT_RESOURCE_PASSES_ITERATIONPRIVATEBANKS_H
