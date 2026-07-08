//===- VitisCleanup.h - Vitis front-end cleanups hls-est models -*- C++ -*-===//
//
// Passes that reproduce what the Vitis HLS front end (clang + the "reflow"
// LLVM passes, before the a.o.1 stage) removes or folds before it allocates
// memories (tools/hls-est-validate/VITIS_NOTES.md N1, N1a):
//
//   --promote-globals-to-allocas  a non-constant memref.global used by one
//                                 function becomes an alloca there, so every
//                                 later pass treats it like a local array
//   --vitis-fold                  folds Vitis folds and MLIR does not
//                                 (integer division by a constant zero -> 0),
//                                 plus the canonicalization folds
//   --dead-memory-elimination     removes arrays whose values never reach a
//                                 side effect that leaves the function
//
// They are meant to run early, before --auto-pipeline-unroll:
//   --promote-globals-to-allocas --vitis-fold --canonicalize --sccp
//   --dead-memory-elimination
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
void registerVitisCleanupPasses();
} // namespace circt::hls_analysis

#endif
