//===- BRAMClassification.h - Per-bank storage-mode analysis --------------===//
//
// A cached AnalysisManager analysis. For each on-chip bank (a memref produced
// by an alloca, after array-partition decomposition has run) it computes the
// worst-case concurrent access profile across every loop that touches the bank
// and classifies the required port mode: OnePort, SDP, or TDP.
//
// It does NOT rewrite the IR. The scheduler reads getMode(bank) to build typed
// resource limits; the BRAM estimator reads the profile (width/depth/mode) to
// pick a primitive. Nothing here is serialized.
//
//===----------------------------------------------------------------------===//

#ifndef BRAMOPT_ANALYSIS_BRAMCLASSIFICATION_H
#define BRAMOPT_ANALYSIS_BRAMCLASSIFICATION_H

#include "circt/Dialect/Resource/Interfaces/MemoryDS.h"
#include "mlir/IR/Operation.h"
#include "mlir/IR/Value.h"
#include "llvm/ADT/DenseMap.h"
#include "llvm/Support/raw_ostream.h"

#include <circt/Dialect/Arc/ArcTypes.h.inc>

namespace circt::hls_analysis {

/// Port slots the scheduler may use per cycle on a bank (the Vitis storage
/// model, VITIS_NOTES.md N4):
///   OneWriteNRead  bank that Vitis may replicate (RAM_1WNR): no loop body
///                  stores to it more than once, so every read beyond the two
///                  ports of one block RAM is served by another copy. 16
///                  copies + the shared write port = 17 slots per cycle; the
///                  loop II becomes ceil((R + W) / 17).
///   TDP            bank that some loop body stores to twice or more: Vitis
///                  keeps one true-dual-port RAM and raises the II instead
///                  (ceil((R + W) / 2)). Also the fallback for interface
///                  memrefs (function arguments) and anything untracked.
///   OnePort / SDP  kept for completeness (one r/w port; dedicated R + W);
///                  no longer produced by classifyMode.
enum class StorageMode {
  OnePort,       // 1 R/W port. Reads and writes contend.
  SDP,           // 1 dedicated read + 1 dedicated write.
  TDP,           // 2 ports, each R or W.
  OneWriteNRead, // replicable: kReplicatedPortSlots read-or-write slots.
};

llvm::StringRef stringifyStorageMode(StorageMode mode);

/// Port slots per cycle the scheduler grants a bank in `mode`.
unsigned storageModeSlots(StorageMode mode);

/// Classification rule from the per-loop-body access profile.
///   maxStoresPerLoop >= 2 -> TDP            (no replication; 2 slots)
///   otherwise             -> OneWriteNRead  (replicable; 17 slots)
StorageMode classifyMode(unsigned maxReads, unsigned maxStoresPerLoop);

struct BankProfile {
  mlir::Value memref;          // The bank itself (alloca result).
  unsigned width = 0;          // Element bit width.
  unsigned depth = 0;          // Number of elements.
  unsigned maxReads = 0;       // Max loads in one loop body.
  unsigned maxWrites = 0;      // Max stores in one loop body.
  // Every loop body stores to the bank at most once, so Vitis may serve extra
  // reads from replicated copies (RAM_1WNR) instead of raising the II.
  bool replicable = true;
  StorageMode mode = StorageMode::OneWriteNRead;
  StorageKind type =  StorageKind::RAM_1P;
  unsigned copies  = 1;                       // replication factor
  unsigned loopII  = 1;                       // binding II for this bank
};

class BRAMClassification {
public:
  /// Constructed by getAnalysis<BRAMClassification>(). `op` is the func (or any
  /// region-holding op) whose banks should be classified.
  explicit BRAMClassification(mlir::Operation *op);

  /// Mode for `bank`. Returns TDP (two slots, the interface/untracked rule)
  /// if the value is not a tracked bank.
  StorageMode getMode(mlir::Value bank) const;

  /// Full profile for `bank`, or nullptr if untracked.
  const BankProfile *getProfile(mlir::Value bank) const;

  const llvm::DenseMap<mlir::Value, BankProfile> &getBanks() const {
    return banks;
  }

  void dump(llvm::raw_ostream &os) const;

private:
  void enumerateBanks(mlir::Operation *root);
  void profileAccesses(mlir::Operation *root);
  void classify();

  llvm::DenseMap<mlir::Value, BankProfile> banks;
};

} // namespace bramopt

#endif // BRAMOPT_ANALYSIS_BRAMCLASSIFICATION_H
