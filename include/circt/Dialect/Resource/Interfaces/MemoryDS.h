#ifndef HLS_INTERFACES_MEMORYDS_H
#define HLS_INTERFACES_MEMORYDS_H

#include "mlir/IR/AffineMap.h"
#include "mlir/IR/Operation.h"

#include <cstdint>

namespace circt::hls_analysis {

    /// Smallest array (Words * exact element Bits) that Vitis HLS implements
    /// in block RAM; anything smaller becomes distributed RAM (0 BRAM). The
    /// threshold is inclusive: 64x16 = 1024 bits -> 1 BRAM, 93x11 = 1023 ->
    /// LUTRAM, 64x15 = 960 -> LUTRAM (VITIS_NOTES.md N5, 23 kernels). The cost
    /// interface (contributesToBRAMCost) applies it and the --bram-debug
    /// explanation quotes it, so the two cannot drift apart.
    inline constexpr int64_t kBRAMPromotionBits = 1024;

    /// RAM_1WNR replication (VITIS_NOTES.md N4): at most 16 identical copies
    /// of a bank, i.e. 16 dedicated read ports (port B of every copy) plus the
    /// shared port A, which writes or - in a cycle without a write - reads.
    /// The scheduler therefore offers 17 read-or-write slots per cycle to a
    /// bank that can be replicated (no loop body stores to it more than once).
    inline constexpr unsigned kMaxReplicationCopies = 16;
    inline constexpr unsigned kReplicatedPortSlots = kMaxReplicationCopies + 1;
    /// Ports of one physical block RAM (true dual port). A bank that cannot be
    /// replicated, and an interface memref, offers this many slots per cycle.
    inline constexpr unsigned kDualPortSlots = 2;

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