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
#include "mlir/IR/BuiltinOps.h"
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
///   Registers      an alloca marked `hls.registers` (completely partitioned
///                  or scalarised by Vitis, VITIS_NOTES.md N7): no memory,
///                  so no port limit at all.
enum class StorageMode {
  OnePort,       // 1 R/W port. Reads and writes contend.
  SDP,           // 1 dedicated read + 1 dedicated write.
  TDP,           // 2 ports, each R or W.
  OneWriteNRead, // replicable: kReplicatedPortSlots read-or-write slots.
  Registers,     // hls.registers: unlimited.
};

llvm::StringRef stringifyStorageMode(StorageMode mode);

/// Port slots per cycle the scheduler grants a bank in `mode`
/// (std::numeric_limits<unsigned>::max() for Registers: no limit; the
/// scheduler links no resource to such accesses).
unsigned storageModeSlots(StorageMode mode);

/// Classification rule from the per-loop-body access profile (the number
/// of reads plays no part):
///   maxStoresPerLoop >= 2 -> TDP            (no replication; 2 slots)
///   otherwise             -> OneWriteNRead  (replicable; 17 slots)
StorageMode classifyMode(unsigned maxStoresPerLoop);

/// Set on an alloca, or as an argument attribute on a memref parameter: the
/// most stores one loop body of a callee makes to the memref it is passed as
/// (transitively, only when > 1). Written by annotateCalleeStoresPerLoop,
/// read by BRAMClassification, which runs per function.
constexpr llvm::StringLiteral kCalleeStoresPerLoopAttr =
    "hls.callee_stores_per_loop";

/// Annotates every alloca and memref parameter passed to a defined callee
/// whose loops store it more than once per iteration.
void annotateCalleeStoresPerLoop(mlir::ModuleOp module);

/// The annotation of `bank` (0 when absent).
unsigned calleeStoresPerLoop(mlir::Value bank);

/// Set as an argument attribute on a memref parameter of a defined callee:
/// the most stores one loop body makes, in any function, to the arrays the
/// call sites pass as that parameter (only when > 1; VITIS_NOTES N99).
/// Written by annotateCallerStoresPerLoop, read by BRAMClassification.
constexpr llvm::StringLiteral kCallerStoresPerLoopAttr =
    "hls.caller_stores_per_loop";

/// Annotates every memref parameter whose call sites pass an array some loop
/// body stores more than once per iteration (in the caller, in another
/// callee of that array, or further up the call chain).
void annotateCallerStoresPerLoop(mlir::ModuleOp module);

/// The annotation of the parameter `bank` (0 when absent or not a
/// parameter).
unsigned callerStoresPerLoop(mlir::Value bank);

/// Set as an argument attribute on a memref parameter of a defined function
/// without an interface of its own: the m_axi bundle (string) every call
/// site binds it to, through the callers' parameters up to the top
/// function's `hls.interface` (W9r13 review finding 1; VITIS_NOTES N95).
/// Written by annotateMaxiBundlesThroughCalls, read by the scheduler's
/// bundle request limit.
constexpr llvm::StringLiteral kMaxiBundleAttr = "hls.maxi_bundle";

/// Annotates every such parameter. `mode` is the interface mode of the
/// implicit buffer (m_axi), `defaultBundle` the bundle of a port without a
/// `bundle=` (gmem).
void annotateMaxiBundlesThroughCalls(mlir::ModuleOp module,
                                     llvm::StringRef mode,
                                     llvm::StringRef defaultBundle);

/// Set (unit) on a call to a defined callee that reads and writes one
/// global array, in its own body or in its callees' (VITIS_NOTES N102):
/// in a pipelined loop the next iteration's call waits for this one.
/// Written by annotateCalleeGlobalRecurrences in a module pass, so that the
/// per-function scheduler need not look into the callee.
constexpr llvm::StringLiteral kCalleeGlobalRecurrenceAttr =
    "hls.callee_global_recurrence";

void annotateCalleeGlobalRecurrences(mlir::ModuleOp module);

/// The most of `stores` (accesses of one memref inside one loop body) that
/// can run in one iteration: the stores in the two arms of one if never run
/// together, so they count once, whatever their addresses (Vitis builds
/// `if (c) B[i] = v; else B[N-1-i] = w;` read 8 times at II 1 as a RAM_1WNR
/// with 7 copies, both stores sharing the one write port). The arms are the
/// if/else regions the stores are nested in below `scope`, and the arms
/// --convert-affine-to-loopschedule hoisted them out of (`hls.if_arms`).
unsigned maxStoresInOneIteration(llvm::ArrayRef<mlir::Operation *> stores,
                                 mlir::Operation *scope);

struct BankProfile {
  mlir::Value memref;          // The bank itself (alloca result).
  unsigned width = 0;          // Element bit width.
  unsigned depth = 0;          // Number of elements.
  unsigned maxReads = 0;       // Max loads in one loop body.
  unsigned maxWrites = 0;      // Max stores in one loop body.
  // Every loop body stores to the bank at most once, so Vitis may serve extra
  // reads from replicated copies (RAM_1WNR) instead of raising the II.
  bool replicable = true;
  // The alloca carries hls.registers: mode is Registers whatever the profile.
  bool registers = false;
  StorageMode mode = StorageMode::OneWriteNRead;
  StorageKind type = StorageKind::RAM_1P;
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
