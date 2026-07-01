//===- BRAMClassification.cpp ---------------------------------------------===//

#include "circt/Dialect/Resource/Passes/MemrefBankClassification.h"
#include "circt/Dialect/Resource/HLS/HLSOps.h"
#include "mlir/Dialect/Affine/IR/AffineOps.h"
#include "mlir/Dialect/MemRef/IR/MemRef.h"
#include "mlir/IR/BuiltinTypes.h"
#include "llvm/Support/Debug.h"

#include <llvm/ADT/TypeSwitch.h>

#define DEBUG_TYPE "bram-classification"

using namespace mlir;

namespace circt::hls_analysis {


//===----------------------------------------------------------------------===//
// Small helpers
//===----------------------------------------------------------------------===//
StringRef stringifyStorageMode(StorageMode mode) {
  switch (mode) {
  case StorageMode::OnePort:
    return "1p";
  case StorageMode::SDP:
    return "sdp";
  case StorageMode::TDP:
    return "tdp";
  case StorageMode::OneWriteNRead:
    return "1wnr";
  }
  return "?";
}

unsigned storageModeSlots(StorageMode mode) {
  switch (mode) {
  case StorageMode::OnePort:
    return 1;
  case StorageMode::SDP: // one read + one write; callers split the pools
  case StorageMode::TDP:
    return kDualPortSlots;
  case StorageMode::OneWriteNRead:
    return kReplicatedPortSlots;
  }
  return kDualPortSlots;
}

StringRef stringifyStorageKind(StorageKind mode) {
  switch (mode) {
  case StorageKind::RAM_1P:
    return "ram_1p";
  case StorageKind::RAM_2P:
    return "ram_2p";
  case StorageKind::RAM_1WNR:
    return "ram_1wnr";
  default:
    return "unsupported";
  }
}

StorageKind classifyStorageKind(unsigned reads, unsigned writes) {
  if (reads + writes <= 1) return StorageKind::RAM_1P;
  if (writes > 1) return StorageKind::RAM_2P;
  return StorageKind::RAM_1WNR;
}

// Vitis (VITIS_NOTES.md N4, replication.md R1-R3): a bank some loop body
// stores to more than once stays one true-dual-port RAM (the II is raised to
// ceil((R+W)/2)); otherwise extra reads are served by replicated copies, up to
// 16 copies + the shared write port = 17 accesses per cycle.
StorageMode classifyMode(unsigned /*maxReads*/, unsigned maxStoresPerLoop) {
  if (maxStoresPerLoop >= 2)
    return StorageMode::TDP;
  return StorageMode::OneWriteNRead;
}

/// Returns the memref operand of a load/store and flags which it was. Returns a
/// null Value for any other op.
static Value getAccessedMemRef(Operation *op, bool &isLoad, bool &isStore) {
  isLoad = isStore = false;
  return TypeSwitch<Operation *, Value>(op)
      .Case<affine::AffineLoadOp, memref::LoadOp>(
          [&](auto l) { isLoad = true; return l.getMemRef(); })
      .Case<affine::AffineStoreOp, memref::StoreOp>(
          [&](auto s) { isStore = true; return s.getMemRef(); })
      .Case<AffineStoreEnableOp, StoreEnableOp>(
          [&](auto s) { isStore = true; return s.getMemref(); })  // note: getMemref()
      .Default(Value{});
}

//===----------------------------------------------------------------------===//
// BRAMClassification
//===----------------------------------------------------------------------===//

BRAMClassification::BRAMClassification(Operation *op) {
  enumerateBanks(op);
  profileAccesses(op);
  LLVM_DEBUG(dump(llvm::dbgs()));
}

void BRAMClassification::enumerateBanks(Operation *root) {
  root->walk([&](memref::AllocaOp alloca) {
    Value bank = alloca.getResult();
    auto memTy = dyn_cast<MemRefType>(bank.getType());
    if (!memTy || !memTy.hasStaticShape())
      return; // Skip dynamic / non-memref allocas.

    BankProfile prof;
    prof.memref = bank;
    prof.width = memTy.getElementTypeBitWidth();
    prof.depth = static_cast<unsigned>(memTy.getNumElements());
    banks.try_emplace(bank, prof);
  });
}

void BRAMClassification::profileAccesses(Operation *root) {
  // Per bank, per enclosing innermost loop: (reads, writes) within one body.
  // Keyed loop = the innermost affine.for parent, or null for a straight-line
  // access outside every loop. The counts are per loop *body* (after
  // unrolling), which is what Vitis' replication rule looks at: a body with
  // two stores to the bank needs two write ports in one iteration, so the bank
  // cannot be a RAM_1WNR (one shared write port) and stays a 2-port RAM.
  using LoopCounts = llvm::DenseMap<Operation *, std::pair<unsigned, unsigned>>;
  llvm::DenseMap<Value, LoopCounts> perLoop;

  root->walk([&](Operation *op) {
    bool isLoad = false, isStore = false;
    Value bank = getAccessedMemRef(op, isLoad, isStore);
    if (!bank)
      return;
    auto it = banks.find(bank);
    if (it == banks.end())
      return; // Access to an argument/off-chip memref, not a tracked bank.

    Operation *loop = op->getParentOfType<affine::AffineForOp>();
    auto &counts = perLoop[bank][loop];
    if (isLoad)
      ++counts.first;
    if (isStore)
      ++counts.second;
  });

  // Fold to the worst-case profile across loops. Straight-line accesses
  // (null loop) run once and have no II, so they do not decide replicability
  // (Vitis' rule was only observed on loop bodies; replication.md "R3").
  for (auto &[bank, loopCounts] : perLoop) {
    BankProfile &prof = banks[bank];
    unsigned maxStoresPerLoop = 0;
    for (auto &[loop, rw] : loopCounts) {
      unsigned reads = rw.first, writes = rw.second;
      prof.maxReads = std::max(prof.maxReads, reads);
      prof.maxWrites = std::max(prof.maxWrites, writes);
      if (loop)
        maxStoresPerLoop = std::max(maxStoresPerLoop, writes);
    }
    prof.replicable = maxStoresPerLoop <= 1;
    prof.mode = classifyMode(prof.maxReads, maxStoresPerLoop);
    prof.type = classifyStorageKind(prof.maxReads, prof.maxWrites);
  }
}


StorageMode BRAMClassification::getMode(Value bank) const {
  auto it = banks.find(bank);
  return it == banks.end() ? StorageMode::TDP : it->second.mode;
}

const BankProfile *BRAMClassification::getProfile(Value bank) const {
  auto it = banks.find(bank);
  return it == banks.end() ? nullptr : &it->second;
}

void BRAMClassification::dump(llvm::raw_ostream &os) const {
  os << "=== (BRAMClassification) ===\n";
  for (auto &[bank, prof] : banks) {
    os << "  bank " << bank << ": " << prof.width << "x" << prof.depth
       << " modes=" << stringifyStorageMode(prof.mode) << " (R=" << prof.maxReads
       << " W=" << prof.maxWrites
       << (prof.replicable ? ", replicable" : ", not replicable") << ")"
       << " slots/cycle=" << storageModeSlots(prof.mode)
       << " storage kind= " << stringifyStorageKind(prof.type) << "\n";
  }
}

} // namespace bramopt
