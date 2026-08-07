//===- VitisCleanup.h - Vitis front-end cleanups hls-est models -*- C++ -*-===//
//
// Passes that reproduce what the Vitis HLS front end (clang + the "reflow"
// LLVM passes, before the a.o.1 stage) removes or folds before it allocates
// memories (tools/hls-est-validate/VITIS_NOTES.md N1, N1a):
//
//   --promote-globals-to-allocas  a non-constant memref.global used by one
//                                 function becomes an alloca there, so every
//                                 later pass treats it like a local array
//   --vitis-fold                  folds Vitis folds and MLIR does not: the
//                                 undefined value of an integer division by
//                                 a constant zero, per use (N13; option
//                                 `undef=false`: x / 0 -> 0), plus the
//                                 canonicalization folds
//   --dead-memory-elimination     removes arrays whose values never reach a
//                                 side effect that leaves the function
//   --mark-constant-fills         marks arrays whose every write stores a
//                                 compile-time constant: Vitis ROMs (N26);
//                                 runs before the folds (after --inline)
//
// They are meant to run early, before --auto-pipeline-unroll:
//   --inline --canonicalize --sccp --vitis-fold --dead-memory-elimination
// (MEMOS.md M5; --promote-globals-to-allocas only after O10 / O17)
// None of them is part of the default pipeline (Peter decides; MEMOS.md M5).
//
//===----------------------------------------------------------------------===//

#ifndef HLS_PASSES_VITISCLEANUP_H
#define HLS_PASSES_VITISCLEANUP_H

#include "mlir/Pass/Pass.h"
#include <memory>

namespace circt::hls_analysis {
std::unique_ptr<mlir::Pass> createPromoteGlobalsToAllocasPass();
std::unique_ptr<mlir::Pass> createVitisFoldPass();
std::unique_ptr<mlir::Pass> createDeadMemoryEliminationPass();
std::unique_ptr<mlir::Pass> createMarkConstantFillsPass();
void registerVitisCleanupPasses();
} // namespace circt::hls_analysis

#endif
