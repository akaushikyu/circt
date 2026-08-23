//===- MemoryModel.h - Port demand and replication records ----*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// The values --bram-analysis computes per bank before it prices it, as the
// memory plugin interfaces (Plugins/MemoryInterfaces.h) receive them:
//
//   PortDemand          the peak accesses per cycle (reads, writes, total);
//   ReplicationRecord   what the replication rule saw per pipelined loop;
//   SeqScopeIndex       the straight-line stretches of a sequential scope,
//                       for a policy that pairs two accesses in one state.
//
// (Moved from BRAMAnalysis.cpp so that a plugin can read them; the record
// fields are also the keys of the --bram-debug-json report.)
//
//===----------------------------------------------------------------------===//

#ifndef CIRCT_DIALECT_RESOURCE_MODEL_MEMORYMODEL_H
#define CIRCT_DIALECT_RESOURCE_MODEL_MEMORYMODEL_H

#include "circt/Dialect/Resource/Interfaces/MemoryDS.h"

#include "mlir/Dialect/Affine/IR/AffineOps.h"
#include "mlir/Dialect/SCF/IR/SCF.h"
#include "mlir/IR/Operation.h"
#include "llvm/ADT/DenseMap.h"
#include "llvm/ADT/SmallVector.h"

#include <memory>
#include <optional>
#include <string>
#include <utility>
#include <vector>

namespace circt::hls_analysis {

/// Peak accesses of one bank per cycle.
struct PortDemand {
  unsigned reads = 0;
  unsigned writes = 0;
  unsigned total = 0;
  /// True iff reads and writes are partitioned across scopes: no single
  /// scope both reads and writes the bank, and at least one scope of each
  /// exists (the structural precondition of simple dual port; only
  /// meaningful on the combined demand).
  bool segregated = false;
};

/// Per pipelined loop, what the replication rule saw.
struct ReplicationLoopRecord {
  std::string scopeLoc;
  unsigned ii = 0;
  unsigned reads = 0;  ///< loads per iteration of the loop
  unsigned writes = 0; ///< stores per iteration of the loop
  unsigned need = 0;   ///< ceil((reads + writes) / ii): ports the loop needs
  unsigned copies = 0; ///< copies the loop alone needs
  /// The loop lies in a callee instantiated at more than one place and
  /// reaches the bank through its argument: its accesses go through the
  /// module's ports, copies 1 whatever `need` (the II rises instead).
  bool portBound = false;
};

struct ReplicationRecord {
  bool present = false;    ///< the bank's accesses were attributed
  bool replicable = false; ///< no loop body stores to the bank too often
  unsigned maxStoresPerLoop = 0;
  unsigned copies = 1; ///< chosen copy count (1: plain RAM)
  llvm::SmallVector<ReplicationLoopRecord> loops;
  std::optional<std::string> limitingLoop; ///< scope that set `copies`
  /// A port-bound loop needs more than two port-cycles per II.
  bool portBoundLimited = false;
};

/// Straight-line stretches of one sequential scope, built once per scope:
/// a stretch is the scope's block up to the next loop / pipeline / other
/// region op; the arms of an if belong to the stretch.
class SeqScopeIndex {
public:
  struct OpInfo {
    unsigned stretch = 0;
    unsigned ordinal = 0; ///< position in the stretch (an if after its arms)
    /// (if op, region number) of every if between the op and the scope.
    llvm::SmallVector<std::pair<mlir::Operation *, unsigned>, 2> arms;
  };
  struct Scope {
    llvm::DenseMap<mlir::Operation *, OpInfo> info;
    std::vector<std::vector<mlir::Operation *>> stretches;
  };

  const Scope &get(mlir::Operation *scope) {
    std::unique_ptr<Scope> &slot = scopes[scope];
    if (!slot) {
      slot = std::make_unique<Scope>();
      unsigned cur = 0;
      llvm::SmallVector<std::pair<mlir::Operation *, unsigned>, 2> arms;
      for (mlir::Region &region : scope->getRegions())
        for (mlir::Block &block : region) {
          walkBlock(block, *slot, cur, arms);
          ++cur; // another block: another stretch
        }
    }
    return *slot;
  }

private:
  llvm::DenseMap<mlir::Operation *, std::unique_ptr<Scope>> scopes;

  static void add(mlir::Operation *op, Scope &s, unsigned cur,
                  llvm::ArrayRef<std::pair<mlir::Operation *, unsigned>> arms) {
    if (s.stretches.size() <= cur)
      s.stretches.resize(cur + 1);
    OpInfo info;
    info.stretch = cur;
    info.ordinal = s.stretches[cur].size();
    info.arms.assign(arms.begin(), arms.end());
    s.stretches[cur].push_back(op);
    s.info[op] = std::move(info);
  }

  static void walkBlock(
      mlir::Block &block, Scope &s, unsigned &cur,
      llvm::SmallVectorImpl<std::pair<mlir::Operation *, unsigned>> &arms) {
    for (mlir::Operation &op : block) {
      if (llvm::isa<mlir::scf::IfOp, mlir::affine::AffineIfOp>(op)) {
        for (auto [i, region] : llvm::enumerate(op.getRegions())) {
          arms.push_back({&op, static_cast<unsigned>(i)});
          for (mlir::Block &b : region)
            walkBlock(b, s, cur, arms);
          arms.pop_back();
        }
        add(&op, s, cur, arms); // its results depend on its arms
        continue;
      }
      if (op.getNumRegions() > 0) {
        ++cur; // a loop / pipeline / other region op ends the stretch
        continue;
      }
      add(&op, s, cur, arms);
    }
  }
};

} // namespace circt::hls_analysis

#endif // CIRCT_DIALECT_RESOURCE_MODEL_MEMORYMODEL_H
