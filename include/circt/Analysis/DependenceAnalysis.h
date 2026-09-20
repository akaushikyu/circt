//===- DependenceAnalysis.h - memory dependence analyses ------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This header file defines prototypes for methods that perform analysis
// involving memory access dependences.
//
//===----------------------------------------------------------------------===//

#ifndef CIRCT_ANALYSIS_DEPENDENCE_ANALYSIS_H
#define CIRCT_ANALYSIS_DEPENDENCE_ANALYSIS_H

#include "circt/Support/LLVM.h"
#include "mlir/Dialect/Affine/Analysis/AffineAnalysis.h"
#include <utility>
#include <vector>

namespace mlir {
namespace affine {
struct DependenceComponent;
} // namespace affine
namespace func {
class FuncOp;
} // namespace func
} // namespace mlir

namespace circt {
namespace analysis {

/// MemoryDependence captures a dependence from one memory operation to another.
/// It represents the destination of the dependence edge, the type of the
/// dependence, and the components associated with each enclosing loop.
struct MemoryDependence {
  MemoryDependence(
      Operation *source,
      mlir::affine::DependenceResult::ResultEnum dependenceType,
      ArrayRef<mlir::affine::DependenceComponent> dependenceComponents)
      : source(source), dependenceType(dependenceType),
        dependenceComponents(dependenceComponents.begin(),
                             dependenceComponents.end()) {}

  // The source Operation where this dependence originates.
  Operation *source;

  // The dependence type denotes whether or not there is a dependence.
  mlir::affine::DependenceResult::ResultEnum dependenceType;

  // The dependence components include lower and upper bounds for each loop.
  SmallVector<mlir::affine::DependenceComponent> dependenceComponents;
};

/// MemoryDependenceResult captures a set of memory dependences. The map key is
/// the operation to which the dependences exist, and the map value is zero or
/// more MemoryDependences for that operation.
using MemoryDependenceResult =
    DenseMap<Operation *, SmallVector<MemoryDependence>>;

/// MemoryDependenceAnalysis traverses any AffineForOps in the FuncOp body and
/// checks for affine memory access dependences. Non-affine memory dependences
/// are currently not supported. Results are captured in a
/// MemoryDependenceResult, and an API is exposed to query dependences of a
/// given Operation.
/// TODO(mikeurbach): consider upstreaming this to MLIR's AffineAnalysis.
struct MemoryDependenceAnalysis {
  // Construct the analysis from a FuncOp.
  MemoryDependenceAnalysis(Operation *funcOp);

  // Returns the dependences, if any, that the given Operation depends on.
  ArrayRef<MemoryDependence> getDependences(Operation *);

  // Replaces the dependences, if any, from the oldOp to the newOp.
  void replaceOp(Operation *oldOp, Operation *newOp);

  // MODIFIED for hls-est: what the construction did, for pass statistics.
  struct Counters {
    uint64_t pairs = 0;        // same-memref access pairs enumerated
    uint64_t tests = 0;        // dependence tests run (memo misses)
    uint64_t dependences = 0;  // dependences recorded
  };
  const Counters &getCounters() const { return counters; }

protected:
  // MODIFIED for hls-est: which pairs of accesses the analysis examines.
  enum class Scope {
    // Every pair of accesses to one memref in the function, at every loop
    // depth the two have in common (the upstream analysis).
    Function,
    // Only pairs of accesses inside one innermost affine.for (a loop with no
    // loop in its body), at that loop's depth; see
    // InnermostLoopDependenceAnalysis.
    InnermostLoops,
    // MODIFIED for hls-est: nothing is examined (an empty analysis, for a
    // dependence model that does not read it).
    None,
  };
  MemoryDependenceAnalysis(Operation *funcOp, Scope scope);

private:
  // Dependences are stored per destination in stable slots, so replaceOp()
  // re-keys an operation without copying its list; `bySource` is the inverted
  // index that lets replaceOp() retarget the dependences leaving an operation
  // without rescanning every list.
  std::vector<SmallVector<MemoryDependence>> slots;
  Counters counters;
  DenseMap<Operation *, unsigned> slotOf;
  DenseMap<Operation *, SmallVector<unsigned>> bySource;

  unsigned slotFor(Operation *op);
  void record(Operation *source, Operation *destination,
              mlir::affine::DependenceResult::ResultEnum type,
              ArrayRef<mlir::affine::DependenceComponent> components);
  void checkMemrefDependence(SmallVectorImpl<Operation *> &memoryOps,
                             unsigned depth);
};

/// MODIFIED for hls-est: the dependences a modulo schedule of an innermost
/// affine.for can use. For every access inside an innermost loop L (an
/// affine.for whose body holds no loop) at depth D, it records exactly the
/// depth-D entries of MemoryDependenceAnalysis: the dependences carried by L
/// and those within one iteration of L, all of whose sources are inside L.
/// The dependences carried by loops enclosing L, and those of accesses outside
/// innermost loops, are not computed: a modulo schedule of L (where enclosing
/// loops run sequentially) has no use for them, and on bodies unrolled by a
/// user pragma they are almost all of the work (forgebench conv_B: 1.45M
/// access pairs per depth, 637 of 641 s; OPEN_ISSUES O1 notes that the
/// scheduler does not receive them yet).
struct InnermostLoopDependenceAnalysis : public MemoryDependenceAnalysis {
  explicit InnermostLoopDependenceAnalysis(Operation *funcOp)
      : MemoryDependenceAnalysis(funcOp, Scope::InnermostLoops) {}
  /// An analysis that records no dependence (computeNothing tag): what
  /// --convert-affine-to-loopschedule passes on when the configured dependence
  /// model does not read it (cached-o1; OPEN_ISSUES O103 (1)).
  struct ComputeNothing {};
  InnermostLoopDependenceAnalysis(Operation *funcOp, ComputeNothing)
      : MemoryDependenceAnalysis(funcOp, Scope::None) {}
};

} // namespace analysis
} // namespace circt

#endif // CIRCT_ANALYSIS_DEPENDENCE_ANALYSIS_H
