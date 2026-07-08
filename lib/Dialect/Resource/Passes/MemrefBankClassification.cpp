//===- MemrefBankClassification.cpp - estimate Vitis resources ----------- ===//

#include "circt/Dialect/Resource/Passes/MemrefBankClassification.h"
#include "circt/Dialect/Resource/HLS/HLSOps.h"
#include "mlir/Dialect/Affine/IR/AffineOps.h"
#include "mlir/Dialect/MemRef/IR/MemRef.h"
#include "mlir/IR/BuiltinTypes.h"
#include "mlir/Interfaces/LoopLikeInterface.h"
#include "llvm/Support/Debug.h"

#include <llvm/ADT/TypeSwitch.h>

#define DEBUG_TYPE "bram-classification"

using namespace mlir;

namespace circt::hls_analysis {

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
  case StorageMode::SDP:
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
  if (reads + writes <= 1)
    return StorageKind::RAM_1P;
  if (writes > 1)
    return StorageKind::RAM_2P;
  return StorageKind::RAM_1WNR;
}

StorageMode classifyMode(unsigned maxStoresPerLoop) {
  if (maxStoresPerLoop >= 2)
    return StorageMode::TDP;
  return StorageMode::OneWriteNRead;
}

/// Returns the memref operand of a load/store and flags which it was. Returns a
/// null Value for any other op.
static Value getAccessedMemRef(Operation *op, bool &isLoad, bool &isStore) {
  isLoad = isStore = false;
  return TypeSwitch<Operation *, Value>(op)
      .Case<affine::AffineLoadOp, memref::LoadOp>([&](auto lowerIndex) {
        isLoad = true;
        return lowerIndex.getMemRef();
      })
      .Case<affine::AffineStoreOp, memref::StoreOp>([&](auto stringValue) {
        isStore = true;
        return stringValue.getMemRef();
      })
      .Case<AffineStoreEnableOp, StoreEnableOp>([&](auto stringValue) {
        isStore = true;
        return stringValue.getMemref();
      })
      .Default(Value{});
}

BRAMClassification::BRAMClassification(Operation *op) {
  enumerateBanks(op);
  profileAccesses(op);
  LLVM_DEBUG(dump(llvm::dbgs()));
}

void BRAMClassification::enumerateBanks(Operation *root) {
  root->walk([&](memref::AllocaOp localAlloca) {
    Value bank = localAlloca.getResult();
    auto memTy = dyn_cast<MemRefType>(bank.getType());
    if (!memTy || !memTy.hasStaticShape())
      return;

    Type elt = memTy.getElementType();
    if (!elt.isIntOrFloat() && !isa<IndexType>(elt))
      return;

    BankProfile prof;
    prof.memref = bank;
    prof.width = elt.isIntOrFloat() ? elt.getIntOrFloatBitWidth() : 64u;
    prof.depth = static_cast<unsigned>(memTy.getNumElements());
    banks.try_emplace(bank, prof);
  });
}

void BRAMClassification::profileAccesses(Operation *root) {

  using LoopCounts = llvm::DenseMap<Operation *, std::pair<unsigned, unsigned>>;
  llvm::DenseMap<Value, LoopCounts> perLoop;

  root->walk([&](Operation *op) {
    bool isLoad = false, isStore = false;
    Value bank = getAccessedMemRef(op, isLoad, isStore);
    if (!bank)
      return;
    auto it = banks.find(bank);
    if (it == banks.end())
      return;

    Operation *loop = op->getParentOfType<LoopLikeOpInterface>();
    auto &counts = perLoop[bank][loop];
    if (isLoad)
      ++counts.first;
    if (isStore)
      ++counts.second;
  });

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
    prof.mode = classifyMode(maxStoresPerLoop);
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
       << " modes=" << stringifyStorageMode(prof.mode)
       << " (R=" << prof.maxReads << " W=" << prof.maxWrites
       << (prof.replicable ? ", replicable" : ", not replicable") << ")"
       << " slots/cycle=" << storageModeSlots(prof.mode)
       << " storage kind= " << stringifyStorageKind(prof.type) << "\n";
  }
}

} // namespace circt::hls_analysis
