#ifndef HLS_INTERFACES_MEMORYDS_H
#define HLS_INTERFACES_MEMORYDS_H

#include "mlir/IR/AffineMap.h"
#include "mlir/IR/Operation.h"

#include <cstdint>

namespace circt::hls_analysis {

    /// Size above which an array is assumed to be mapped to block RAM rather
    /// than kept in registers/LUTRAM: 32 words x 32 bits. The cost interface
    /// (contributesToBRAMCost) applies it and the --bram-debug explanation
    /// quotes it, so the two cannot drift apart.
    /// TODO: most tools expose this as a configurable threshold; make it a
    ///       target/device parameter instead of a constant.
    inline constexpr int64_t kBRAMPromotionBits = 32 * 32;

    enum class StorageKind {
      RAM_1P,
      RAM_2P,
      RAM_S2P,
      RAM_T2P,
      LUTRAM,
      URAM,
      RAM_1WNR
    };

    struct PartitionSpec {
        enum Kind { Complete, Block, Cyclic } kind;
        unsigned factor;       // ignored for Complete
        unsigned dim;          // which dimension (0-indexed)
    };

    struct AccessSummary {
      mlir::Operation *op;
      bool isWrite;
      unsigned stageStart;
      unsigned latency;
      // Temporal grouping. Accesses with different `scope`s run in different
      // loops and do not contend for ports (unless in a dataflow region).
      mlir::Operation *scope = nullptr;
      // II of `scope` when it is a pipeline; 0 means sequential scope
      // (no cross-iteration overlap -> at most one access per cycle).
      unsigned ii = 0;
    };

    struct BRAMCost {
        StorageKind kind;
        unsigned bramCount;
        bool infeasible = false;   // true if port demand exceeds chosen kind
        std::string note;          // human-readable explanation
    };

    llvm::DenseMap<llvm::StringRef, PartitionSpec>
    getPartitionSpecs(mlir::Operation* op);

} // namespace circt::hls_analysis

#endif