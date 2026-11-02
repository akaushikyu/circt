//===- TestPlugin.cpp - hls-est test plugin: one per interface ------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// The plugin the lit tests of test/hls-est/Plugins load with --load-plugin:
// at least one implementation of every interface, each with a behaviour a
// test can recognise (hls-doc/plugins.md). Built by the CIRCT build as a
// MODULE that links nothing: every symbol resolves in hls-est.
//
//===----------------------------------------------------------------------===//

#include "circt/Dialect/Resource/Plugins/MemoryInterfaces.h"
#include "circt/Dialect/Resource/Plugins/PassPolicies.h"
#include "circt/Dialect/Resource/Plugins/Registry.h"
#include "circt/Dialect/Resource/Plugins/Scheduling.h"

#include "mlir/Dialect/MemRef/IR/MemRef.h"
#include "mlir/Tools/Plugins/PassPlugin.h"
#include "llvm/Config/llvm-config.h"

#include <cmath>
#include <map>
#include <cstdlib>

using namespace circt::hlsest;
using namespace mlir;
using llvm::StringRef;

namespace {

//===--------------------------------------------------- memory interfaces

/// Every bank in the block memory, however small.
struct TestAllBlock : StorageSelector {
  StringRef name() const override { return "test-all-block"; }
  TierChoice select(const MemoryRequest &, const Device &device,
                    const SelectionContext &) const override {
    for (const DeviceMemory &m : device.memories)
      if (m.tier == "block")
        return {m.id, m.tier, "test-all-block"};
    return {};
  }
};

/// One port per bank, no replication, every bank labelled test-sp and priced
/// at the narrow configuration.
struct TestSinglePort : MemoryArchitecturePolicy {
  StringRef name() const override { return "test-single-port"; }
  PortPools capacity(const BankStaticProfile *profile,
                     const DeviceMemory &) const override {
    PortPools p;
    if (profile && profile->registers)
      return p;
    p.pools.push_back({"_rsrc", 1u, PortPool::Any});
    return p;
  }
  ReplicationRecord replication(llvm::ArrayRef<AccessSummary>,
                                bool attributed) const override {
    ReplicationRecord r;
    r.present = attributed;
    return r;
  }
  bool pairsSequentialAccesses() const override { return false; }
  PortDemand sequentialScopeDemand(llvm::ArrayRef<const AccessSummary *>,
                                   SeqScopeIndex &,
                                   std::string *) const override {
    return {1, 0, 1, false};
  }
  MemoryPlan plan(const PortDemand &demand, ReplicationRecord &,
                  const MemoryRequest &, const PlanContext &) const override {
    MemoryPlan p;
    p.label = "test-sp";
    p.pricedConfig = Config::get().tool.hls.memoryArchitecture.pricedNarrow;
    p.reason = "test-single-port: peak " + std::to_string(demand.total) +
               " access(es) per cycle on one port";
    return p;
  }
  std::string unpricedLabel(bool) const override { return "test-none"; }
};

/// Every bank is one block.
struct TestOneBlock : MemoryMapper {
  StringRef name() const override { return "test-one-block"; }
  Mapping map(const MemoryRequest &, const DeviceMemory &memory,
              const PortConfig &priced, MappingTrace *trace) const override {
    if (trace) {
      trace->bitsPerBlock = memory.bits;
      trace->pricedConfig = priced.name;
      trace->maxWidth = static_cast<unsigned>(priced.maxWidth);
    }
    Mapping m;
    m.blocks = 1;
    m.cost = memory.cost;
    m.band = "test-one-block: one block per bank";
    return m;
  }
};

/// Candidates 0 and 1, 2 and 3, ... share one memory.
struct TestMergePairs : MemoryGrouping {
  StringRef name() const override { return "test-merge-pairs"; }
  void group(llvm::ArrayRef<GroupCandidate> candidates,
             llvm::SmallVectorImpl<MemoryGroup> &groups) const override {
    for (unsigned i = 0; i + 1 < candidates.size(); i += 2)
      groups.push_back({{i, i + 1}, "test-merge-pairs"});
  }
};

/// No implicit buffers.
struct TestZero : ImplicitBufferModel {
  StringRef name() const override { return "test-zero"; }
  void buffers(func::FuncOp, const ImplicitBufferConfig &,
               llvm::function_ref<int64_t(int64_t, unsigned)>,
               llvm::SmallVectorImpl<ImplicitBuffer> &) const override {}
};

//===----------------------------------------------------- pass policies

struct TestPipelineNothing : PipelinePolicy {
  StringRef name() const override { return "test-pipeline-nothing"; }
  LogicalResult decide(ModuleOp,
                       const PipelineDecisionOptions &) const override {
    return success();
  }
};

struct TestNoPartition : PartitionPolicy {
  StringRef name() const override { return "test-no-partition"; }
  LogicalResult run(func::FuncOp, const PartitionOptions &,
                    PartitionStatistics &) const override {
    return success();
  }
};

struct TestNoFold : FoldRuleSet {
  StringRef name() const override { return "test-no-fold"; }
  void populate(RewritePatternSet &, MLIRContext *) const override {}
};

//===-------------------------------------------------------- scheduling

/// Every operation latency 0 (memory accesses 1).
struct TestAllComb : OperatorTimingModel {
  StringRef name() const override { return "test-all-comb"; }
  std::optional<OperatorTiming>
  timing(Operation *op, const SchedulingContext &) const override {
    OperatorTiming t;
    bool memory = isa<affine::AffineLoadOp, affine::AffineStoreOp,
                      memref::LoadOp, memref::StoreOp>(op) ||
                  op->getName().getStringRef() == "hls.store_enable";
    t.cls = memory ? "mem" : "comb";
    t.latency = memory ? 1 : 0;
    return t;
  }
  void listClasses(llvm::SmallVectorImpl<std::string> &out) const override {
    out.push_back("comb");
  }
};

/// A floating-point multiply takes ceil(20 ns / clock) cycles (the clock of
/// run.clock_ns), every other operation what calyx-fixed would give it
/// (looked up through the registry's builtin).
struct TestClockedTiming : OperatorTimingModel {
  StringRef name() const override { return "test-clocked-timing"; }
  void configure(const Config &config, ConfigDiagnostics &diag) override {
    base = PluginRegistry<OperatorTimingModel>::instance().create(
        "calyx-fixed", config, diag);
    fpmul = static_cast<unsigned>(std::ceil(20.0 / config.run.clockNs));
  }
  void library(llvm::SmallVectorImpl<OperatorTiming> &out) const override {
    base->library(out);
    for (OperatorTiming &t : out)
      if (t.cls == "fpmul")
        t.latency = fpmul;
  }
  std::optional<OperatorTiming>
  timing(Operation *op, const SchedulingContext &ctx) const override {
    std::optional<OperatorTiming> t = base->timing(op, ctx);
    if (t && t->cls == "fpmul")
      t->latency = fpmul;
    return t;
  }
  void listClasses(llvm::SmallVectorImpl<std::string> &out) const override {
    base->listClasses(out);
  }
  std::unique_ptr<OperatorTimingModel> base;
  unsigned fpmul = 2;
};

/// The operations of the loop, no dependence (the pass adds the structural
/// ones): an iter_arg recurrence no longer bounds the II.
struct TestNoDeps : DependenceModel {
  StringRef name() const override { return "test-no-deps"; }
  circt::scheduling::ModuloProblem
  populate(affine::AffineForOp loop, DependenceInputs &) const override {
    circt::scheduling::ModuloProblem p(loop);
    loop.getBody()->walk([&](Operation *op) { p.insertOperation(op); });
    return p;
  }
};

/// ASAP at a fixed II (plugins.test-fixed-ii.ii, else 4), first free slot of
/// every resource; not a function of the problem alone (no reuse).
struct TestFixedII : ModuloScheduler {
  StringRef name() const override { return "test-fixed-ii"; }
  void configure(const Config &config, ConfigDiagnostics &) override {
    if (const llvm::json::Object *o = config.plugins.getObject(name()))
      if (std::optional<int64_t> v = o->getInteger("ii"))
        ii = static_cast<unsigned>(*v);
  }
  ScheduleOutcome schedule(circt::scheduling::ModuloProblem &p, Operation *,
                           const SchedulingContext &) const override {
    p.setInitiationInterval(ii);
    std::map<std::pair<std::string, unsigned>, unsigned> used;
    for (Operation *op : p.getOperations()) {
      unsigned start = 0;
      for (auto dep : p.getDependences(op)) {
        Operation *src = dep.getSource();
        if (src == op || p.getDistance(dep).value_or(0) != 0)
          continue;
        std::optional<unsigned> s = p.getStartTime(src);
        auto opr = p.getLinkedOperatorType(src);
        if (s && opr)
          start = std::max(start, *s + p.getLatency(*opr).value_or(0));
      }
      auto rsrcs = p.getLinkedResourceTypes(op);
      for (;; ++start) {
        bool free = true;
        if (rsrcs)
          for (auto r : *rsrcs)
            if (used[{r.str(), start % ii}] >= p.getLimit(r).value_or(~0u))
              free = false;
        if (free)
          break;
      }
      if (rsrcs)
        for (auto r : *rsrcs)
          ++used[{r.str(), start % ii}];
      p.setStartTime(op, start);
    }
    return {true, "test-fixed-ii", {}};
  }
  unsigned ii = 4;
};

/// Every operation of a function body in state 0 (loop bodies are left to
/// the stretch-pair rule).
struct TestSeqAsap : SequentialScheduler {
  StringRef name() const override { return "test-seq-asap"; }
  bool schedule(Block &region, const SchedulingContext &,
                SequentialSchedule &out) const override {
    if (!isa<func::FuncOp>(region.getParentOp()))
      return false;
    out.numStates = 1;
    for (Operation &op : region.without_terminator())
      out.stateOf[&op] = 0;
    return true;
  }
};

/// One unit per operator class (with scheduling.emit_detail, which records
/// the class).
struct TestShareAll : Binder {
  StringRef name() const override { return "test-share-all"; }
  void bind(const ScheduleView &view, const SchedulingContext &,
            BindingResult &out) const override {
    llvm::StringMap<int64_t> unitOf;
    for (const RegionSchedule &r : view.regions)
      for (const OpSchedule &o : r.ops)
        if (o.cls)
          out.opToUnit[o.op] =
              unitOf.try_emplace(*o.cls, unitOf.size()).first->second;
  }
};

} // namespace

HLS_EST_REGISTER_PLUGIN(StorageSelector, "test-all-block",
                        "test: every bank in the block memory", TestAllBlock);
HLS_EST_REGISTER_PLUGIN(MemoryArchitecturePolicy, "test-single-port",
                        "test: one port, no replication", TestSinglePort);
HLS_EST_REGISTER_PLUGIN(MemoryMapper, "test-one-block",
                        "test: one block per bank", TestOneBlock);
HLS_EST_REGISTER_PLUGIN(MemoryGrouping, "test-merge-pairs",
                        "test: memrefs pairwise in one memory", TestMergePairs);
HLS_EST_REGISTER_PLUGIN(ImplicitBufferModel, "test-zero",
                        "test: no implicit buffers", TestZero);
HLS_EST_REGISTER_PLUGIN(PipelinePolicy, "test-pipeline-nothing",
                        "test: pipelines nothing", TestPipelineNothing);
HLS_EST_REGISTER_PLUGIN(PartitionPolicy, "test-no-partition",
                        "test: partitions nothing", TestNoPartition);
HLS_EST_REGISTER_PLUGIN(FoldRuleSet, "test-no-fold", "test: folds nothing",
                        TestNoFold);
HLS_EST_REGISTER_PLUGIN(OperatorTimingModel, "test-all-comb",
                        "test: every operation combinational", TestAllComb);
HLS_EST_REGISTER_PLUGIN(OperatorTimingModel, "test-clocked-timing",
                        "test: fpmul latency ceil(20 ns / clock)",
                        TestClockedTiming);
HLS_EST_REGISTER_PLUGIN(DependenceModel, "test-no-deps",
                        "test: no memory or iter_arg dependence", TestNoDeps);
HLS_EST_REGISTER_PLUGIN(ModuloScheduler, "test-fixed-ii",
                        "test: ASAP at a fixed II", TestFixedII);
HLS_EST_REGISTER_PLUGIN(SequentialScheduler, "test-seq-asap",
                        "test: function bodies in one state", TestSeqAsap);
HLS_EST_REGISTER_PLUGIN(Binder, "test-share-all",
                        "test: one unit per operator class", TestShareAll);

namespace {
/// With HLS_EST_TEST_DUPLICATE set, a second registration of a builtin name
/// (the registry refuses it and hls-est stops).
struct TestDuplicate : TestOneBlock {
  StringRef name() const override { return "vitis-band7"; }
};
const bool duplicateRegistered = [] {
  if (std::getenv("HLS_EST_TEST_DUPLICATE"))
    PluginRegistry<MemoryMapper>::instance().add(
        "vitis-band7", "test: a duplicate",
        [] { return std::make_unique<TestDuplicate>(); }, HLS_EST_PLUGIN_ORIGIN);
  return true;
}();
} // namespace

extern "C" LLVM_ATTRIBUTE_WEAK mlir::PassPluginLibraryInfo
mlirGetPassPluginInfo() {
  return {MLIR_PLUGIN_API_VERSION, "HlsEstTestPlugin", LLVM_VERSION_STRING,
          []() {}};
}

extern "C" LLVM_ATTRIBUTE_WEAK circt::hlsest::HlsEstPluginInfo
hlsEstGetPluginInfo() {
  return {HLS_EST_PLUGIN_API_VERSION, "HlsEstTestPlugin"};
}
