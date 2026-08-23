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

    /// Unit attribute on a memref.alloca whose array Vitis implements as
    /// registers (completely partitioned / scalarised, no memory): set by
    /// --infer-vitis-split-array's automatic partitions (td=off, or td=auto
    /// with auto-partitions; VITIS_NOTES.md N7). --bram-analysis counts 0
    /// BRAM (status "registers") and the scheduler gives it no port limit.
    /// `kRegistersReasonAttrName` (string) says which rule fired.
    inline constexpr llvm::StringLiteral kRegistersAttrName = "hls.registers";
    inline constexpr llvm::StringLiteral kRegistersReasonAttrName =
        "hls.registers_reason";
    /// The element width an array is priced with when Vitis stores fewer bits
    /// than its declared type (--narrow-ram-widths), and why.
    inline constexpr llvm::StringLiteral kNarrowBitsAttrName =
        "hls.narrow_bits";
    inline constexpr llvm::StringLiteral kNarrowReasonAttrName =
        "hls.narrow_reason";

    enum class StorageKind {
      RAM_1P,
      RAM_2P,
      RAM_S2P,
      RAM_T2P,
      LUTRAM,
      URAM,
      RAM_1WNR,
      // Read-only storage (a constant-initialised memref.global): Vitis
      // ROM_1P / ROM_2P are simple-dual-port (x36 allowed); ROM_NP is
      // replicated, ceil(ports / 2) copies at x18 (VITIS_NOTES.md N8).
      ROM_1P,
      ROM_2P,
      ROM_NP
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
      // The call through which the access was reached when it lies in a
      // callee that received the memref as an argument (the outermost call
      // in the owner's function); null for a direct access.
      mlir::Operation *via = nullptr;
      // The access reaches the array through a module instantiated at more
      // than one place (VITIS_NOTES.md N14 R6): it goes through the module's
      // two ports and never makes the array replicated.
      bool portBound = false;
    };

    struct BRAMCost {
        StorageKind kind;
        unsigned bramCount;
        std::string label;         // the storage kind as the report names it
        bool infeasible = false;   // true if port demand exceeds chosen kind
        std::string note;          // human-readable explanation
    };

    llvm::DenseMap<llvm::StringRef, PartitionSpec>
    getPartitionSpecs(mlir::Operation* op);

} // namespace circt::hls_analysis

#endif