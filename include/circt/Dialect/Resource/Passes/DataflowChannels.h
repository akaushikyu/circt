//===- DataflowChannels.h - dataflow ping-pong channels ----------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// Inside a `#pragma HLS dataflow` region (a function, or the body of a loop),
// Vitis turns every call and every loop of the region into a process and every
// local array that one process writes and a later one reads into a ping-pong
// channel (PIPO): N blocks of the array, so that the producer fills one block
// while the consumer reads another. The channel is either one memory holding
// all N blocks (block index in the low address bits, one port per side) or a
// separate memory per block; it is never replicated (more reads per cycle
// raise the consumer's II instead).
//
// This file recognises the channels (which region, which processes, how many
// blocks, which binding) and prices one bank of a channel; whether a process
// drives a second port is decided by --bram-analysis, which knows the
// schedule (BRAMAnalysis.cpp).
//
//===----------------------------------------------------------------------===//

#ifndef CIRCT_DIALECT_RESOURCE_PASSES_DATAFLOWCHANNELS_H
#define CIRCT_DIALECT_RESOURCE_PASSES_DATAFLOWCHANNELS_H

#include "mlir/IR/Operation.h"
#include "mlir/IR/Value.h"
#include "llvm/ADT/ArrayRef.h"
#include "llvm/ADT/STLFunctionalExtras.h"
#include "llvm/ADT/DenseMap.h"
#include "llvm/ADT/SmallVector.h"

#include <cstdint>
#include <functional>
#include <memory>
#include <optional>
#include <string>

namespace circt::hls_analysis {

/// `hls.dataflow` on a func.func or a loop: a `#pragma HLS dataflow` region.
constexpr llvm::StringLiteral kDataflowAttr = "hls.dataflow";

/// One access of the storage, seen from the function that owns the storage:
/// `anchor` is the access itself, or the call through which it is reached
/// when it lies in a callee.
struct ChannelAccess {
  mlir::Operation *anchor = nullptr;
  bool isWrite = false;
};

/// One process of a dataflow region that touches the channel.
struct DataflowProcess {
  mlir::Operation *op = nullptr; ///< the call or loop of the region body
  std::string name;              ///< "call @f" / the loop kind, and its loc
  unsigned position = 0;         ///< its position in the region body
  bool reads = false, writes = false;
  /// The process Vitis merges it into (named by the group's first process
  /// in program order), and why; empty when it stays a process of its own.
  std::string group, mergeReason;
};

/// A ping-pong channel and the facts its price depends on.
struct DataflowChannel {
  mlir::Operation *region = nullptr; ///< the dataflow func.func or loop
  std::string regionKind;            ///< "function" | "loop"
  std::string regionName;
  llvm::SmallVector<DataflowProcess> processes; ///< program order
  int64_t blocks = 2;
  std::string blocksSource; ///< why `blocks`
  std::string bindType, bindImpl; ///< hls.bind_storage (lower case)
};

/// What the channel analysis says about one storage.
struct ChannelVerdict {
  /// The storage lies in a dataflow region (its accesses are all in one).
  bool inRegion = false;
  /// Set when it is a ping-pong channel.
  std::optional<DataflowChannel> channel;
  /// Why an array of a dataflow region is not a channel.
  std::string notChannelReason;
};

/// The processes of each dataflow region that Vitis merges into one process:
///   - every process that writes one region-local array or stream (a local
///     of the region, not a scalar), together with every process on a
///     dependence path from one process of the merged group to another
///     (through region-local arrays and streams), until nothing changes;
///   - the processes that access one array a non-top region function
///     receives from its caller (a top-level argument is a port, which two
///     processes share).
class ProcessMerges {
public:
  /// Every access of a memref value, seen from its function.
  using AccessesFn =
      std::function<llvm::SmallVector<ChannelAccess>(mlir::Value)>;
  explicit ProcessMerges(AccessesFn accessesOf)
      : accessesOf(std::move(accessesOf)) {}

  /// The process `process` of `region` is merged with: a representative of
  /// its group (itself when it is alone) and why.
  std::pair<mlir::Operation *, std::string>
  groupOf(mlir::Operation *region, mlir::Operation *process);

  /// The first process in program order of the group of `process`.
  mlir::Operation *groupLeader(mlir::Operation *region,
                               mlir::Operation *process);

  /// Whether `process` shares its group with another process.
  bool isMerged(mlir::Operation *region, mlir::Operation *process);

private:
  struct RegionMerges {
    llvm::DenseMap<mlir::Operation *, mlir::Operation *> parent;
    llvm::DenseMap<mlir::Operation *, std::string> reason;
    llvm::DenseMap<mlir::Operation *, unsigned> position;
  };
  RegionMerges &compute(mlir::Operation *region);
  mlir::Operation *find(RegionMerges &m, mlir::Operation *p);
  bool unite(RegionMerges &m, mlir::Operation *a, mlir::Operation *b);
  void mergeOnParameters(mlir::Operation *region, RegionMerges &m);
  void mergeWritersAndPaths(mlir::Operation *region, RegionMerges &m);

  AccessesFn accessesOf;
  llvm::DenseMap<mlir::Operation *, std::unique_ptr<RegionMerges>> regions;
};

/// Whether `storage` (a memref.alloca, or a memref.global that a function
/// holding a dataflow region uses) is a ping-pong channel, given every access
/// of it (`accesses`) and the number of words of one bank (`words`).
/// `merges`, when given, tells which processes Vitis merges.
ChannelVerdict analyzeDataflowChannel(mlir::Operation *storage,
                                      llvm::ArrayRef<ChannelAccess> accesses,
                                      int64_t words,
                                      ProcessMerges *merges = nullptr);

/// How the channel is built and what one bank of it costs.
struct ChannelPrice {
  unsigned bram = 0;
  std::string mode; ///< "single" | "separate" | "one block" | "lutram"
  std::string rule; ///< the arithmetic, in words
};

/// One bank of `words` x `bits` of a channel of `blocks` blocks.
/// `twoPorts`: some process can access the bank twice in one cycle;
/// `bound2p`: a bind_storage type=ram_2p / ram_s2p; `lutram`: impl=lutram.
/// `blocksOf(words, bits, sdp)` is the BRAM_18K of one memory by the depth
/// bands (`sdp`: the x36 mode is allowed).
ChannelPrice
priceChannel(int64_t words, unsigned bits, int64_t blocks, bool twoPorts,
             bool bound2p, bool lutram,
             llvm::function_ref<int64_t(int64_t, unsigned, bool)> blocksOf);

} // namespace circt::hls_analysis

#endif // CIRCT_DIALECT_RESOURCE_PASSES_DATAFLOWCHANNELS_H
