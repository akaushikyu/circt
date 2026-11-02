//===- PreBankForwarding.cpp - forwarding before partitioning -------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// VITIS_NOTES N138 (polybench_pragmas k2mm, `k2mm_Pipeline_lp1_lp2_lp3`):
// the two `unroll factor=2` copies of `tmp1[i][j] += alpha * A[i][k] *
// B[k][j]` leave one read and one write of tmp1 per iteration in Vitis'
// schedule: the first copy's sum is forwarded to the second copy's load and
// its store, overwritten by the second copy's, is deleted (LLVM GVN / DSE on
// the unrolled body). tmp1 is cyclic-partitioned on j, and after the flatten
// j is a run-time value, so --memory-banking-bram turns each access into one
// access per bank (loads and a select on j mod 4, stores guarded by
// j mod 4 == bank). --convert-affine-to-loopschedule's cleanup compares
// affine addresses of one memref and does not see through that form, so the
// two guarded stores stayed and made the banks non-replicable (O170 (c)).
// This runs the same forwarding before the banks exist, on the whole array.
//
// Within the top-level block of each pipelined affine.for, in program order,
// per array (a local alloca / alloc with a partition attribute whose every
// user is a plain load or store, so no view can alias it):
//   - a load whose map and operands equal an earlier store's, with no other
//     access to the array in between, is replaced by the stored value;
//   - a store whose address equals an earlier store's, with no read of the
//     array in between (the forwarded load is no read), deletes the earlier
//     store;
//   - any other access to the array, or any op with regions or a call that
//     uses it, forgets what is known about it.
// Equal addresses are equal maps on identical operands: conservative, and
// exactly the unrolled copies' form (`tmp1[%i, %j]` twice).
//
//===----------------------------------------------------------------------===//

#include "circt/Dialect/Resource/Passes/PreBankForwarding.h"
#include "mlir/Dialect/Affine/IR/AffineOps.h"
#include "mlir/Dialect/MemRef/IR/MemRef.h"
#include "mlir/IR/Builders.h"
#include "llvm/ADT/DenseMap.h"

using namespace mlir;

namespace circt::hls_analysis {
namespace {

/// Partition attributes: the pragma's (cgeist) and the inferred one.
bool isPartitioned(Operation *def) {
  return def->hasAttr("hls.array_partition") || def->hasAttr("hls.partition");
}

/// A local partitioned array whose every user is a plain load or store (no
/// view, cast or call can make another value alias it).
bool isTrackableArray(Value mem) {
  Operation *def = mem.getDefiningOp();
  if (!def || !isa<memref::AllocaOp, memref::AllocOp>(def) ||
      !isPartitioned(def))
    return false;
  for (Operation *user : mem.getUsers())
    if (!isa<affine::AffineLoadOp, affine::AffineStoreOp, memref::LoadOp,
             memref::StoreOp, memref::DeallocOp>(user))
      return false;
  return true;
}

void addCounter(Operation *op, StringRef name, int64_t n) {
  if (n == 0)
    return;
  int64_t old = 0;
  if (auto a = op->getAttrOfType<IntegerAttr>(name))
    old = a.getInt();
  op->setAttr(name, Builder(op->getContext()).getI64IntegerAttr(old + n));
}

int64_t counter(Operation *op, StringRef name) {
  if (auto a = op->getAttrOfType<IntegerAttr>(name))
    return a.getInt();
  return 0;
}

bool sameAddress(affine::AffineStoreOp store, AffineMap map,
                 Operation::operand_range operands) {
  return store.getAffineMap() == map &&
         llvm::equal(store.getMapOperands(), operands);
}

/// The last store of each tracked array in the block, and whether the array
/// was read since.
struct LastStore {
  affine::AffineStoreOp store;
  bool readSince = false;
};

void forwardInBlock(Block &block, DenseMap<Value, bool> &trackable,
                    PreBankForwardingStats &stats) {
  DenseMap<Value, LastStore> last;
  auto tracked = [&](Value mem) {
    auto [it, inserted] = trackable.try_emplace(mem, false);
    if (inserted)
      it->second = isTrackableArray(mem);
    return it->second;
  };
  for (Operation &op : llvm::make_early_inc_range(block)) {
    if (auto load = dyn_cast<affine::AffineLoadOp>(op)) {
      Value mem = load.getMemRef();
      if (!tracked(mem))
        continue;
      auto it = last.find(mem);
      if (it == last.end())
        continue;
      if (sameAddress(it->second.store, load.getAffineMap(),
                      load.getMapOperands())) {
        addCounter(it->second.store, "hls.forwarded_loads", 1);
        ++stats.forwardedLoads;
        load.getResult().replaceAllUsesWith(
            it->second.store.getValueToStore());
        load.erase();
        continue;
      }
      it->second.readSince = true;
      continue;
    }
    if (auto store = dyn_cast<affine::AffineStoreOp>(op)) {
      Value mem = store.getMemRef();
      if (!tracked(mem))
        continue;
      auto it = last.find(mem);
      if (it != last.end() && !it->second.readSince &&
          sameAddress(it->second.store, store.getAffineMap(),
                      store.getMapOperands())) {
        affine::AffineStoreOp dead = it->second.store;
        addCounter(store, "hls.removed_stores",
                   1 + counter(dead, "hls.removed_stores"));
        addCounter(store, "hls.forwarded_loads",
                   counter(dead, "hls.forwarded_loads"));
        dead.erase();
        ++stats.removedStores;
      }
      last[mem] = {store, false};
      continue;
    }
    // Anything else that touches a tracked array, directly or inside its
    // regions (a memref.load, a nested loop, a call), forgets it.
    auto forget = [&](Operation *inner) {
      for (Value v : inner->getOperands())
        last.erase(v);
    };
    forget(&op);
    for (Region &region : op.getRegions())
      region.walk([&](Operation *inner) { forget(inner); });
  }
}

} // namespace

PreBankForwardingStats forwardPartitionedStores(ModuleOp module) {
  PreBankForwardingStats stats;
  DenseMap<Value, bool> trackable;
  module.walk([&](affine::AffineForOp loop) {
    if (loop->hasAttr("hls.pipeline"))
      forwardInBlock(*loop.getBody(), trackable, stats);
  });
  return stats;
}

} // namespace circt::hls_analysis
