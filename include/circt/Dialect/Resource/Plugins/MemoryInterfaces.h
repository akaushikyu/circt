//===- MemoryInterfaces.h - Plugin interfaces of the memory model -*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// The five interfaces --bram-analysis (and the scheduling pass, for the port
// pools) prices memories through (design memo sections 8.1, 8.2):
//
//   StorageSelector           which tier / device memory a bank goes to
//                             (Vitis: block RAM from 1024 bits, else
//                             distributed RAM; builtin vitis-bits-threshold)
//   MemoryArchitecturePolicy  the ports a bank offers the scheduler, the
//                             replication, the storage kind and the port
//                             configuration that prices it (builtin
//                             vitis-auto)
//   MemoryMapper              blocks of one bank in a device memory
//                             (builtins vitis-band7, vitis-aspect-min,
//                             geometry-min)
//   MemoryGrouping            several memrefs in one memory (builtin
//                             identity)
//   ImplicitBufferModel       memories no user array accounts for (builtin
//                             vitis-m_axi: the m_axi adapters)
//
// No signature names an AMD resource or a Vitis storage kind: those are the
// parameters and report labels of the Vitis builtins. Every cost is a
// ResourceVector over the device's resource classes.
//
//===----------------------------------------------------------------------===//

#ifndef CIRCT_DIALECT_RESOURCE_PLUGINS_MEMORYINTERFACES_H
#define CIRCT_DIALECT_RESOURCE_PLUGINS_MEMORYINTERFACES_H

#include "circt/Dialect/Resource/Model/MemoryModel.h"
#include "circt/Dialect/Resource/Plugins/Plugin.h"

#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "llvm/ADT/ArrayRef.h"
#include "llvm/ADT/SmallVector.h"

#include <optional>
#include <string>

namespace circt::hlsest {

using circt::hls_analysis::AccessSummary;
using circt::hls_analysis::PortDemand;
using circt::hls_analysis::ReplicationRecord;
using circt::hls_analysis::SeqScopeIndex;

/// What a bank needs, independent of any device.
struct MemoryRequest {
  int64_t words = 0;
  unsigned writeWidth = 0;                  ///< bits per word
  llvm::SmallVector<unsigned, 2> readWidths; ///< one entry (no mixed widths)
  bool readOnly = false;                    ///< a ROM
  bool needsInit = false;
  /// The width is the narrowed element width (for the reports).
  bool narrowed = false;
  std::optional<unsigned> byteEnableBits; ///< reserved
  std::optional<std::string> rdw;         ///< reserved
  bool needsEcc = false;                  ///< reserved
  std::optional<std::string> pragmaImpl;  ///< bind_storage impl, when parsed

  int64_t bits() const { return words * static_cast<int64_t>(writeWidth); }
};

/// The static access profile of a bank the scheduler limits (no schedule
/// yet): the most loads / stores one loop body makes.
struct BankStaticProfile {
  unsigned width = 0, depth = 0;
  unsigned maxReads = 0, maxWrites = 0;
  /// No loop body stores to the bank too often for replication.
  bool replicable = true;
  /// Completely partitioned: no memory.
  bool registers = false;
};

/// What a selector knows besides the request (it runs before scheduling, so
/// there is no per-cycle demand).
struct SelectionContext {
  /// Null for a memref the scheduler does not track.
  const BankStaticProfile *profile = nullptr;
};

/// The storage a bank goes to.
struct TierChoice {
  /// A device memory id, priced by the memory mapper; empty when the bank
  /// stays below every priced tier (registers or distributed RAM that costs
  /// nothing of the counted classes).
  std::string memory;
  std::string tier; ///< the device memory's tier, or the profile's `below`
  std::string note; ///< why (the report's exclusion text when `memory` is "")
};

class StorageSelector : public PluginBase {
public:
  /// Depends only on its arguments: --bram-analysis may call it more than
  /// once for a bank.
  virtual TierChoice select(const MemoryRequest &request, const Device &device,
                            const SelectionContext &context) const = 0;
};

/// One pool of port slots the scheduler limits per cycle.
struct PortPool {
  std::string suffix;           ///< resource name suffix ("_rsrc")
  std::optional<unsigned> limit; ///< nullopt: unlimited (no resource)
  enum Consumes { Read, Write, Any } consumes = Any;
};

struct PortPools {
  llvm::SmallVector<PortPool, 2> pools; ///< empty: no port limit
  unsigned readLatency = 1;
};

/// How a bank is built, after scheduling.
struct MemoryPlan {
  std::string label;        ///< report label ("RAM_2P", "RAM_1WNR", ...)
  std::string pricedConfig; ///< port configuration whose width prices it
  unsigned copies = 1;      ///< replication
  bool infeasible = false;  ///< the demand exceeds what the plan serves
  std::string note;         ///< the infeasibility, for the stdout line
  std::string reason;       ///< why this plan (the report's ram_reason)
  bool rom = false;         ///< priced as a read-only memory
  unsigned romReads = 0;    ///< a ROM: peak reads per cycle
};

/// What the plan sees of the bank besides its demand and replication.
struct PlanContext {
  bool attributed = true;      ///< the bank's accesses were all attributed
  bool anyStoreEnable = false; ///< some write is a predicated store
};

class MemoryArchitecturePolicy : public PluginBase {
public:
  /// Before scheduling: the scheduler's port pools for a bank (null
  /// `profile`: a memref the scheduler does not track). Read by the
  /// scheduling pass only.
  virtual PortPools capacity(const BankStaticProfile *profile,
                             const DeviceMemory &memory) const = 0;
  /// The replication rule over the bank's accesses.
  virtual ReplicationRecord replication(llvm::ArrayRef<AccessSummary> accesses,
                                        bool attributed) const = 0;
  /// Whether sequential scopes are counted state by state (true: the pass
  /// hands each scope to sequentialScopeDemand) or one access per cycle.
  virtual bool pairsSequentialAccesses() const = 0;
  /// The per-cycle demand of one sequential scope (a group of accesses of one
  /// bank in one non-pipelined scope that no SequentialScheduler scheduled);
  /// `note` receives the two accesses that share a state, if any.
  virtual PortDemand
  sequentialScopeDemand(llvm::ArrayRef<const AccessSummary *> group,
                        SeqScopeIndex &index, std::string *note) const = 0;
  /// After scheduling: the kind, the copies and the priced configuration of
  /// a bank from its demand and replication. May rewrite the per-loop
  /// copies of `replication` for the debug report (a ROM's rule).
  virtual MemoryPlan plan(const PortDemand &demand,
                          ReplicationRecord &replication,
                          const MemoryRequest &request,
                          const PlanContext &context) const = 0;
  /// The report label of a bank that is not priced (below every counted
  /// tier, an all-zero ROM).
  virtual std::string unpricedLabel(bool readOnly) const {
    return readOnly ? "ROM" : "RAM";
  }
};

/// The blocks of one bank in one device memory.
struct Mapping {
  int64_t blocks = 0; ///< primitive instances of one copy
  ResourceVector cost; ///< blocks x (cost + overhead) of the memory
  unsigned configWidth = 0; ///< width of the geometry used
  int64_t widthTiles = 0, depthTiles = 0;
  int64_t addrDepth = 0;     ///< the depth priced
  int64_t depthPerBlock = 0; ///< words of one block in that geometry
  std::string band;          ///< the rule that priced it, in words
};

/// Debug values in neutral names.
struct MappingTrace {
  int64_t bitsPerBlock = 0;
  std::string pricedConfig;
  unsigned maxWidth = 0;
};

class MemoryMapper : public PluginBase {
public:
  virtual Mapping map(const MemoryRequest &request, const DeviceMemory &memory,
                      const PortConfig &priced, MappingTrace *trace) const = 0;
  /// The label of the reports ("band" for vitis-band7, "n6" for
  /// vitis-aspect-min); the name by default.
  virtual llvm::StringRef reportLabel() const { return name(); }
  /// A one-line description of the rule for the --bram-debug header.
  virtual std::string reportDescription() const { return name().str(); }
};

/// One memref the grouping may merge.
struct GroupCandidate {
  mlir::Operation *op = nullptr; ///< its memref.alloca / memref.global
  std::string name;
  MemoryRequest request;
};

/// Memories several memrefs share (indices into the candidate list).
struct MemoryGroup {
  llvm::SmallVector<unsigned, 2> members;
  std::string note;
};

class MemoryGrouping : public PluginBase {
public:
  /// Groups of two or more candidates that are one memory; a candidate in no
  /// group is a memory of its own.
  virtual void group(llvm::ArrayRef<GroupCandidate> candidates,
                     llvm::SmallVectorImpl<MemoryGroup> &groups) const = 0;
};

/// One implicit buffer (for the m_axi model: one bundle's adapter).
struct ImplicitBuffer {
  std::string bundle;
  llvm::SmallVector<std::string> ports;
  unsigned busBits = 32;
  int64_t readBurst = 16, readOutstanding = 16;
  int64_t writeBurst = 16, writeOutstanding = 16;
  bool hasRead = false, hasWrite = false;
  bool passedToCall = false;   ///< an argument reaches a call
  bool unresolvedCall = false; ///< ... whose body is unknown
  int64_t readDepth = 0;
  unsigned readBram = 0, writeBram = 0; ///< blocks of the block memory
  std::string readRule, writeRule;
};

class ImplicitBufferModel : public PluginBase {
public:
  /// The buffers of one public function's interface for the configuration's
  /// entry `spec`. `mapFifo(depth, bits)` prices a FIFO with the mapper and
  /// configuration `spec` names.
  virtual void buffers(mlir::func::FuncOp fn, const ImplicitBufferConfig &spec,
                       llvm::function_ref<int64_t(int64_t, unsigned)> mapFifo,
                       llvm::SmallVectorImpl<ImplicitBuffer> &out) const = 0;
};

} // namespace circt::hlsest

#endif // CIRCT_DIALECT_RESOURCE_PLUGINS_MEMORYINTERFACES_H
