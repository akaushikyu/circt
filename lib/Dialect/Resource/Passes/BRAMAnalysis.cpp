#include "circt/Dialect/Resource/Config/ConfigUtils.h"
#include "circt/Dialect/Resource/Passes/BRAMAnalysis.h"
#include "circt/Dialect/Resource/Interfaces/MemoryInterface.h"
#include "circt/Dialect/Resource/Passes/LoopPragmas.h"
#include "circt/Dialect/Resource/Passes/MemrefBankClassification.h"
#include "circt/Dialect/Resource/HLS/HLSOps.h"
#include "circt/Dialect/Resource/Passes/FoldUnrolledGuards.h"
#include "circt/Dialect/Resource/Passes/MemoryRecurrences.h"
#include "circt/Dialect/Resource/Model/AccessOrder.h"
#include "circt/Dialect/Resource/Plugins/MemoryInterfaces.h"
#include "circt/Dialect/Resource/Passes/StoragePragmas.h"
#include "circt/Dialect/Resource/Plugins/PassPolicies.h"
#include "circt/Dialect/Resource/Plugins/Registry.h"
#include "circt/Dialect/Resource/Plugins/Scheduling.h"
#include "circt/Dialect/Resource/Passes/MathCores.h"
#include "circt/Dialect/Resource/Passes/StreamFifos.h"
#include "circt/Dialect/Resource/Passes/DataflowChannels.h"
#include "circt/Dialect/Resource/Passes/PolygeistCompat.h"
#include "circt/Dialect/Resource/Passes/ReadOnlyMemory.h"
#include "circt/Dialect/LoopSchedule/LoopScheduleOps.h"
#include "mlir/Dialect/Affine/IR/AffineOps.h"
#include "mlir/Dialect/Arith/IR/Arith.h"
#include "circt/Dialect/Resource/Passes/CallInstances.h"
#include "circt/Dialect/Resource/Passes/FunctionPipelines.h"
#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/Dialect/LLVMIR/LLVMDialect.h"
#include "mlir/Dialect/MemRef/IR/MemRef.h"
#include "mlir/Dialect/SCF/IR/SCF.h"
#include "mlir/Dialect/Utils/StaticValueUtils.h"
#include "mlir/IR/BuiltinOps.h"
#include "mlir/IR/Matchers.h"
#include "mlir/IR/SymbolTable.h"
#include "mlir/Interfaces/CallInterfaces.h"
#include "mlir/Interfaces/LoopLikeInterface.h"
#include "mlir/Interfaces/SideEffectInterfaces.h"
#include "mlir/Interfaces/ViewLikeInterface.h"
#include "mlir/Pass/Pass.h"

#include "llvm/ADT/BitVector.h"
#include "llvm/ADT/DenseSet.h"
#include "llvm/ADT/StringMap.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/FileSystem.h"
#include "llvm/Support/FormatVariadic.h"
#include "llvm/Support/JSON.h"
#include "llvm/Support/MathExtras.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Support/Format.h"

#include <algorithm>
#include <map>
#include <optional>
#include <string>
#include <vector>

#define DEBUG_TYPE "hls-analysis-loop-schedule"

using namespace mlir;
using circt::loopschedule::LoopSchedulePipelineOp;
using circt::loopschedule::LoopSchedulePipelineStageOp;
using namespace circt::hls_analysis;

//===----------------------------------------------------------------------===//
// Debug-mode options.
//===----------------------------------------------------------------------===//
// Plain llvm::cl options rather than pass options so they can be appended to
// any pipeline string (`... --bram-analysis --bram-debug`). They only add
// output: the estimate is computed exactly as without them, and the normal
// stdout report is byte-identical. The text form goes to stderr after the
// report; the JSON form is what tools/hls-est-validate/compare.py diffs
// against the Vitis per-memory table.
static llvm::cl::opt<bool> bramDebugOpt(
    "bram-debug",
    llvm::cl::desc("After the --bram-analysis report, explain on stderr how "
                   "every memref's BRAM number was derived (does not change "
                   "any estimate)"),
    llvm::cl::init(false));

static llvm::cl::opt<std::string> bramDebugJsonOpt(
    "bram-debug-json",
    llvm::cl::desc("Write the --bram-analysis derivation of every memref as "
                   "JSON to this path (does not change any estimate)"),
    llvm::cl::value_desc("path"), llvm::cl::init(""));

// Model extensions that change estimates. Off by default: Peter decides what
// the default pipeline computes (MEMOS.md M5 has the before/after tables).
// Plain llvm::cl options like the debug flags, so that a whitespace-split
// pipeline string (tools/hls-est-validate/run_hlsest.py) can carry them.
static llvm::cl::opt<bool> bramAttributeGlobalsOpt(
    "bram-attribute-globals",
    llvm::cl::desc("--bram-analysis: attribute the accesses of a "
                   "memref.global through its memref.get_global sites (port "
                   "demand, RAM type, replication like an alloca; a constant "
                   "global is priced as a ROM: read-only ports are simple "
                   "dual port, x36 allowed). Default: globals are RAM_1P "
                   "with unattributed accesses (OPEN_ISSUES.md O4)"),
    llvm::cl::init(false));

static llvm::cl::opt<bool> bramMaxiAdaptersOpt(
    "bram-maxi-adapters",
    llvm::cl::desc("--bram-analysis: add the BRAM of the m_axi adapter of "
                   "every bundle of a public function's hls.interface "
                   "arguments (read FIFO depth max_read_burst_length x "
                   "num_read_outstanding, write buffer when "
                   "max_write_burst_length > 16; VITIS_NOTES.md N1a). On by "
                   "default (MEMOS.md M5, decision #4 of 2026-10-10); =false "
                   "leaves the adapters out"),
    llvm::cl::init(true));

static llvm::cl::opt<bool> bramStreamFifosOpt(
    "bram-stream-fifos",
    llvm::cl::desc("--bram-analysis: price every hls::stream object as the "
                   "FIFO Vitis builds (one per stream, array element or "
                   "struct member; depth from the stream pragma, the "
                   "template argument, else 2; shift registers when depth <= "
                   "2 or depth x width <= 1024 bits, else the depth bands at "
                   "x18; VITIS_NOTES.md N31) instead of the stream handle "
                   "storage as a RAM. On by default (MEMOS.md decision #53); "
                   "=false gives the former model"),
    llvm::cl::init(true));

static llvm::cl::opt<bool> bramDataflowChannelsOpt(
    "bram-dataflow-channels",
    llvm::cl::desc("--bram-analysis: price every local array that one "
                   "process of a dataflow region writes and a later one "
                   "reads as the ping-pong channel Vitis builds (N blocks: "
                   "the stream type=pipo depth, else 2, else 1 for a non-top "
                   "region function no dataflow region calls; one memory of "
                   "N x D words at x18, or N separate memories when a process "
                   "accesses the bank twice in one cycle or it is bound to "
                   "ram_2p / ram_s2p; never replicated) instead of as an "
                   "ordinary memory. On by default; =false gives the former "
                   "model"),
    llvm::cl::init(true));

static llvm::cl::opt<bool> bramSeqDualPortOpt(
    "bram-seq-dual-port",
    llvm::cl::desc("--bram-analysis: in a sequential (non-pipelined) scope, "
                   "two accesses of a bank that lie in one straight-line "
                   "stretch (no loop or pipeline between them) and do not "
                   "depend on each other (SSA or memory order through any "
                   "array) share a state and keep both ports live (RAM_2P, "
                   "or RAM_T2P for two writes; x18 columns; VITIS_NOTES.md "
                   "N12). On by default (MEMOS.md M6, decision #2 of "
                   "2026-10-10); =false gives the former model, where a "
                   "sequential scope has one live port (OPEN_ISSUES.md O3)"),
    llvm::cl::init(true));

namespace {

//===----------------------------------------------------------------------===//
// The memory model (hls-doc/plugins.md): the configuration's plugins.
//===----------------------------------------------------------------------===//
// --bram-analysis decides what an array is (a RAM, a ROM, a FIFO, a dataflow
// channel, registers) and what its accesses demand per cycle; the models of
// the configuration decide the rest:
//   StorageSelector           which device memory (tier) the bank goes to
//                             (tool.backend.storage_selector; Vitis: block
//                             RAM from 1024 bits);
//   MemoryArchitecturePolicy  replication, the storage kind and the port
//                             configuration that prices it
//                             (tool.hls.memory_architecture; Vitis: ram_1p /
//                             ram_2p / ram_t2p, RAM_1WNR, ROM_nP);
//   MemoryMapper              the blocks of the bank in that memory
//                             (tool.backend.memory_mapper; Vitis: the
//                             7-series depth bands, VITIS_NOTES N8);
//   ImplicitBufferModel       the m_axi adapters (tool.hls.implicit_buffers);
//   MemoryGrouping            memrefs that share one memory (identity).
// The numbers they use are configuration data: the device's memories, port
// configurations and resource classes, and the profile's parameters.
using circt::hlsest::Config;

const Config &config() { return Config::get(); }

/// Bits of one block of the mapped primitive (18432 for a RAMB18E1).
int64_t bitsPerBlock() {
  const circt::hlsest::DeviceMemory *m = config().blockMemory();
  return m ? m->bits : 0;
}

/// The widest port of a bank priced wide (36) or narrow (18).
unsigned maxPortWidth(bool wide) {
  return static_cast<unsigned>(config().pricedPortWidth(wide));
}

/// frontend.index_bits (64): the width of an index element.
unsigned indexElementBits() {
  return static_cast<unsigned>(config().frontend.indexBits);
}

/// --bram-analysis=bram-formula=band | n6: the mapper vitis-band7 |
/// vitis-aspect-min (an override of tool.backend.memory_mapper.plugin).
enum class BramFormula { Band, N6 };

/// The plugins of one run, created from the registries by name.
struct Models {
  std::unique_ptr<circt::hlsest::StorageSelector> selector;
  std::unique_ptr<circt::hlsest::MemoryArchitecturePolicy> policy;
  std::unique_ptr<circt::hlsest::MemoryMapper> mapper; ///< user arrays
  std::unique_ptr<circt::hlsest::MemoryMapper> streamMapper; ///< stream FIFOs
  std::unique_ptr<circt::hlsest::MemoryMapper> fifoMapper; ///< m_axi read FIFO
  std::unique_ptr<circt::hlsest::ImplicitBufferModel> buffers; ///< m_axi
  std::unique_ptr<circt::hlsest::MemoryGrouping> grouping;
  const circt::hlsest::DeviceMemory *block = nullptr; ///< the mapper's primitive
  /// A bank could not be priced (an error was emitted); the pass fails after
  /// the report.
  mutable bool failed = false;
};

// What top= selects (MEMOS.md M7; computeTopScope fills it).
struct TopScope {
  std::string symbol;                     // empty: no top=, everything costed
  llvm::DenseSet<Operation *> funcs;      // reachable func.func ops
  llvm::DenseSet<StringRef> funcNames;    // their symbol names
  llvm::DenseSet<StringRef> globals;      // memref.global symbols they use
  unsigned skipped = 0;                   // memref ops outside the scope

  bool active() const { return !symbol.empty(); }
  // Whether `op` is synthesized under top=: a memref.global the reachable
  // functions use, or an op inside a reachable func.func (an alloca, a
  // get_global site, a pipeline).
  bool covers(Operation *op) const {
    if (!active())
      return true;
    if (auto g = dyn_cast<memref::GlobalOp>(op))
      return globals.contains(g.getSymName());
    auto fn = op->getParentOfType<func::FuncOp>();
    return fn && funcs.contains(fn.getOperation());
  }
};

//===----------------------------------------------------------------------===//
// Debug records.
//===----------------------------------------------------------------------===//
// Everything the debug report says about one memref. Filled while the estimate
// is computed (from the same intermediate values the estimate uses), and only
// ever *read* by the text/JSON printers, so collecting it cannot change a
// number. Optional strings are JSON null when unset.

struct AccessRecord {
  std::string op;        // e.g. "memref.load", "hls.store_enable"
  bool isWrite = false;
  std::string scopeKind; // "pipeline" | "loop" | "func" | "none"
  std::string scopeLoc;
  unsigned ii = 0;
  unsigned stageStart = 0;
  bool storeEnable = false; // hls.store_enable: write-only, no phantom read
  // Counters the scheduler's redundant-access cleanup left on the op
  // (AffineToLoopScheduleModified.cpp cleanupRedundantAccesses): accesses
  // that no longer exist because this one stands for them.
  unsigned mergedLoads = 0;    // hls.merged_loads: same-address loads (CSE)
  unsigned forwardedLoads = 0; // hls.forwarded_loads: loads served by the value
  unsigned removedStores = 0;  // hls.removed_stores: stores it overwrote
  // hls.register_promoted_accesses: accesses of a register-promoted element
  // (or a forwarded load) this one stands for (VITIS_NOTES N87).
  unsigned registerPromoted = 0;
  // hls.merged_if_else_stores: a store both arms of an if/else made to this
  // address, sunk below the if as this one (mergeIfElseAccesses).
  unsigned mergedIfElseStores = 0;
  // hls.hoisted_conditional: a loop-invariant load hoisted out of an if of
  // the loop it was in (hoistInvariantLoads, hoist-conditional-invariant).
  bool hoistedConditional = false;
  // hls.port_bank / hls.port_banks (VITIS_NOTES N88): the bank of a
  // partitioned function argument whose ports this access uses ("" when it
  // is not such an access).
  std::string portBank;
  Operation *scope = nullptr;
  // An access inside a non-inlined callee that received the memref as an
  // argument (VITIS_NOTES.md N14 R6): the function it lies in and the call
  // in the owner's function through which it was reached.
  std::string inFunc;
  std::optional<std::string> viaCall;
  // ... through a module instantiated at more than one place (N14 R6): no
  // replication for it.
  bool portBound = false;
  std::string portBoundReason;
};

struct ScopeDemandRecord {
  std::string scopeKind;
  std::string scopeLoc;
  unsigned ii = 0;
  PortDemand demand;
  // --bram-seq-dual-port: the two accesses of a sequential scope that share
  // a state.
  std::optional<std::string> sameState;
};

struct PartitionRecord {
  bool present = false;
  bool applied = false; // banks exist (hls.partition) vs. spec still unbanked
  std::string kind, source;
  // On a bank (`applied`): the factor and 1-based dimension banking actually
  // used. On an unbanked memref: the pragma entry's fields as written.
  int64_t factor = 0, dim = 0;
  std::optional<int64_t> bankIndex, bankCount;
  std::optional<std::string> reason; // hls.partition_reason
  // Every split dimension when banking split more than one (`dims` of
  // hls.partition): (kind, factor, 1-based dim).
  SmallVector<std::tuple<std::string, int64_t, int64_t>> dims;
  // The array member whose pragma the split comes from when it is not the
  // array's own (a callee parameter, VITIS_NOTES.md N17 (b)).
  std::optional<std::string> from;
  // `hls.steering` (W9r9 review D8): copies per load group steered across
  // the banks (N27 / N74) and the if-arm reloads forwarded to an outer load.
  SmallVector<int64_t> steeredGroups;
  std::optional<int64_t> forwardedReloads;
  // Store_enables left out for banks the index cannot reach (O150).
  std::optional<int64_t> prunedStoreEnables;
};

struct BankMathRecord {
  bool present = false;
  int64_t bitsPerBram = bitsPerBlock();
  bool wide = false;         // x36 mode allowed (one live port / RAM_S2P)
  unsigned maxWidth = 0;     // widest mode allowed: 36 (wide) or 18 (narrow)
  unsigned configWidth = 0;  // chosen aspect-ratio mode m (bits per word)
  int64_t widthTiles = 0;    // columns = ceil(elemBits / m)
  int64_t depthPerBlock = 0; // words per RAMB18 in mode m
  int64_t addrDepth = 0;     // P = 2^ceil(log2 words): the priced depth
  int64_t depthTiles = 0;    // blocks per column = max(1, P / depthPerBlock)
  int64_t blocksPerCopy = 0; // widthTiles * depthTiles
  int64_t replication = 1;   // RAM_1WNR copies (1: not replicated)
  int64_t blocks = 0;        // blocksPerCopy * replication
  std::string formula;       // "band" | "n6" (bram-formula=)
  std::string band;          // the depth band / rule that priced the bank
};

// One m_axi bundle of a public function (VITIS_NOTES.md N1a "Interfaces"):
// Vitis adds an adapter instance `<bundle>_m_axi_U` whose BRAM comes from the
// read data FIFO and the write buffer (the implicit-buffer model's record).
using AdapterRecord = circt::hlsest::ImplicitBuffer;

// An array of a dataflow region (--bram-dataflow-channels): whether it is a
// ping-pong channel, and if so how Vitis builds and prices it.
struct PipoRecord {
  bool channel = false;
  std::string notChannelReason;
  std::string region, regionKind;
  SmallVector<DataflowProcess> processes;
  int64_t blocks = 0;
  std::string blocksSource;
  std::string bindType, bindImpl;
  // The two accesses of one process that can happen in the same cycle (the
  // process drives a second port), or empty.
  std::string secondPort;
  std::string mode, modeReason, rule;
};

struct MemrefRecord {
  std::string id;
  std::optional<std::string> name;    // memref.global symbol
  std::optional<std::string> varname; // polygeist.varname / hls.bank_of
  std::optional<std::string> fromGlobal; // hls.from_global (promoted global)
  // hls.struct_member (--split-struct-memrefs): the member of a local array
  // of structs this memref holds (VITIS_NOTES.md N29).
  std::optional<std::string> structMember;
  // hls.aggregated (--split-struct-memrefs): a struct variable an AGGREGATE
  // pragma reached, packed into one word per element.
  std::optional<std::string> aggregated;
  // hls.kept_reason (--dead-memory-elimination): why an array nothing reads
  // is still priced (VITIS_NOTES.md N17 (a), N25).
  std::optional<std::string> keptReason;
  // The element width Vitis stores per word when it is narrower than the
  // declared type (hls.narrow_bits from --narrow-ram-widths): the width the
  // array is priced with, and why.
  struct NarrowRecord {
    unsigned declaredBits = 0;
    unsigned bits = 0;
    std::string reason;
  };
  std::optional<NarrowRecord> narrow;
  std::string kind;                   // "alloca" | "global" | ...
  std::optional<std::string> func;
  bool hasLoc = false;
  std::string locFile;
  unsigned locLine = 0, locCol = 0;
  std::string locText; // printed location when no file:line:col is available

  SmallVector<int64_t> shape;
  std::string elemType;
  unsigned elemBits = 0;
  std::optional<int64_t> words;

  std::string status;                        // counted | excluded_small | ...
  std::optional<std::string> excludeReason;

  PartitionRecord partition;
  std::vector<AccessRecord> accesses;
  // Accesses served by a register instead of the memory (hls.register_promoted,
  // VITIS_NOTES N87 R1 / R3, N90 (a) / (b)): no port, not in `accesses`.
  struct RegisterServed {
    std::string op, rw, loc, rule;
  };
  std::vector<RegisterServed> registerServed;
  bool accessesAttributed = false; // false for globals unless attributed
  bool rom = false;                // constant global priced as a ROM
  std::optional<AdapterRecord> adapter; // kind == "m_axi_adapter"
  std::optional<MathCoreRecord> math;   // kind == "math_core"
  std::optional<StreamHandleRecord> fifo; // hls::stream handle storage
  std::optional<PipoRecord> pipo; // array of a dataflow region
  PortDemand demand;
  SmallVector<ScopeDemandRecord> perScope;

  std::string ramType;
  std::string ramReason;
  ReplicationRecord replication;
  BankMathRecord bankMath;
  unsigned bram = 0;
  // The device memory that priced it ("" when none), the storage selector's
  // tier, and what it costs per resource class (additive debug keys).
  std::string memoryId;
  std::string storageTier;
  circt::hlsest::ResourceVector resources;
  bool infeasible = false;
  // Non-inlined callees (VITIS_NOTES.md N14 R1-R3): the memory is charged
  // once per instance of the module that owns it. `bram` is the charged
  // total, `bramPerInstance` what one instance costs.
  unsigned instances = 1;
  unsigned bramPerInstance = 0;
  std::optional<std::string> ownerFunc; // the owning function (a global:
                                        // the deepest common caller)
  // A ROM priced per reading module (VITIS_NOTES N136): one entry per copy
  // (group of readers, where it lives, how many, what one costs). Written
  // under the top-level debug key "rom_module_copies", not in the record.
  struct RomModuleCopy {
    std::string funcs, where, rule;
    unsigned copies = 1;
    unsigned bramPerCopy = 0;
  };
  std::vector<RomModuleCopy> romModuleCopies;
};

// One non-inlined callee of the debug report: its instances and why.
struct InstanceRecord {
  std::string func;
  unsigned instances = 1;
  bool inlineOff = false;
  bool inlineAutoOff = false; ///< kept by Vitis's automatic-inlining rule
  struct Parent {
    std::string parent;
    unsigned parentInstances = 1;
    unsigned callSites = 0;
    unsigned instances = 0;
    std::optional<int64_t> limit;
    std::string rule;
    // Each call site (its location) and the instance it is bound to, in
    // program order (0-based within the parent).
    SmallVector<std::pair<std::string, unsigned>> sites;
  };
  SmallVector<Parent> parents;
};

/// The sequential-scope rule of the memory architecture policy and its
/// per-scope index (null when the policy counts one access per state).
struct SeqContext {
  SeqScopeIndex index;
  const circt::hlsest::MemoryArchitecturePolicy *policy = nullptr;
  /// The kept callees Vitis pipelines at their caller's II (N144), or null.
  const circt::hls_analysis::FunctionPipelineModel *functionPipelines =
      nullptr;
  /// The policy's sequentialScopeDemand per group of accesses (their ops, in
  /// order): the port demand and the reason both ask for it on the same
  /// groups, and it walks the whole straight-line stretch (W9r23 review D9:
  /// half the time of held-out bilateralfilter FILTER_SIZE 7).
  std::map<std::vector<Operation *>, std::pair<PortDemand, std::string>>
      demandMemo;
  PortDemand sequentialDemand(ArrayRef<const AccessSummary *> group,
                              std::string *note) {
    std::vector<Operation *> key;
    key.reserve(group.size());
    for (const AccessSummary *a : group)
      key.push_back(a->op);
    auto it = demandMemo.find(key);
    if (it == demandMemo.end()) {
      std::string n;
      PortDemand d = policy->sequentialScopeDemand(group, index, &n);
      it = demandMemo.emplace(std::move(key), std::make_pair(d, n)).first;
    }
    if (note && !it->second.second.empty())
      *note = it->second.second;
    return it->second.first;
  }
};

//===----------------------------------------------------------------------===//
// Port demand: per temporal scope, then combined across scopes.
//===----------------------------------------------------------------------===//
// Peak demand within ONE loop. A pipelined scope (ii>=1) overlaps iterations, so
// accesses contend when they share a slot (stageStart % ii). A sequential scope
// (ii==0) issues at most one memory op per cycle, so reads and writes never
// collide regardless of how many there are - unless `seq` is given
// (--bram-seq-dual-port): then two independent accesses of one straight-line
// stretch share a state (sequentialScopeDemand). `note` receives that pair.
// A sequential scope that a SequentialScheduler scheduled carries hls.state on
// its operations; it is counted state by state (the accesses of one bank in
// one state), and the MemoryArchitecturePolicy's sequential rule (the
// stretch-pair approximation of Vitis' state schedule) is not applied.
static std::optional<PortDemand>
perStateDemand(ArrayRef<const AccessSummary *> group) {
  std::map<int64_t, std::pair<unsigned, unsigned>> perState; // {reads, writes}
  for (const AccessSummary *a : group) {
    auto state = a->op->getAttrOfType<IntegerAttr>("hls.state");
    if (!state)
      return std::nullopt;
    auto &rw = perState[state.getInt()];
    (a->isWrite ? rw.second : rw.first)++;
  }
  PortDemand d;
  for (const auto &[state, rw] : perState) {
    d.reads = std::max(d.reads, rw.first);
    d.writes = std::max(d.writes, rw.second);
    d.total = std::max(d.total, rw.first + rw.second);
  }
  return d;
}

PortDemand scopeDemand(ArrayRef<const AccessSummary *> group,
                       SeqContext *seq = nullptr,
                       std::string *note = nullptr) {
  PortDemand d;
  if (group.empty())
    return d;

  unsigned ii = group.front()->ii;
  assert(llvm::all_of(group, [&](auto *a) { return a->ii == ii; }) &&
         "scopeDemand requires a single-II group; bucket by scope first");

  // Sequential scope: the body runs to completion before the next iteration, so
  // there is no cross-iteration overlap and at most one access is in flight
  // regardless of latency.
  if (ii == 0)
    if (std::optional<PortDemand> scheduled = perStateDemand(group))
      return *scheduled;
  if (ii == 0 && seq)
    return seq->sequentialDemand(group, note);
  if (ii == 0) {
    bool anyR = false, anyW = false;
    for (const auto *a : group)
      (a->isWrite ? anyW : anyR) = true;
    d.reads = anyR ? 1u : 0u;
    d.writes = anyW ? 1u : 0u;
    d.total = (anyR || anyW) ? 1u : 0u;
    return d;
  }

  // Pipelined scope: an access starting at `stageStart` and holding its port for
  // `latency` cycles reserves phases stageStart .. stageStart+latency-1, each
  // taken mod II. Looping the cycles handles wraparound, including self-overlap
  // when latency >= II.
  std::vector<std::pair<unsigned, unsigned>> slot(ii, {0u, 0u}); // {reads,writes}
  for (const auto *a : group) {
    unsigned occ = std::max(a->latency, 1u); // 0-latency access still uses a port
    for (unsigned c = 0; c < occ; ++c) {
      unsigned phase = (a->stageStart + c) % ii;
      (a->isWrite ? slot[phase].second : slot[phase].first)++;
    }
  }

  for (const auto &cell : slot) {
    unsigned r = cell.first, w = cell.second;
    d.reads = std::max(d.reads, r);
    d.writes = std::max(d.writes, w);
    d.total = std::max(d.total, r + w);
  }

  return d;
}

// The most reads of a ROM that one state of one of its sequential scopes
// holds, by the policy's rule (0: not modelled, or no such scope). Scopes a
// SequentialScheduler scheduled (hls.state) are counted state by state by
// scopeDemand already.
static unsigned
sequentialRomReads(ArrayRef<AccessSummary> accesses, SeqContext *seq,
                   const circt::hlsest::MemoryArchitecturePolicy &policy) {
  if (!seq)
    return 0;
  std::map<Operation *, SmallVector<const AccessSummary *>> byScope;
  for (const AccessSummary &a : accesses)
    if (!a.isWrite && a.ii == 0 && !a.op->hasAttr("hls.state"))
      byScope[a.scope].push_back(&a);
  unsigned n = 0;
  for (auto &[scope, group] : byScope)
    if (group.size() > 2)
      n = std::max(n, policy.sequentialRomReads(group, seq->index));
  return n;
}

// One copy of a ROM in the module structure (VITIS_NOTES N136): the
// readers whose accesses price it, where it lives and how many there are.
struct RomCopyPlan {
  SmallVector<func::FuncOp> readers;
  std::string where, rule;
  unsigned copies = 1;
};

// The copies of a ROM read by several kept functions (N136), per instance of
// their common parent, or nullopt when the rule does not apply (one reader,
// a reader not reached from the owner through functions with one caller
// each (a reader below a direct child of the owner is placed by that
// child, with the instances the chain gives it), the owner reading it
// itself without rom.module_copies_parent_reads, or nothing that differs
// from one shared copy). (a) An instance of a reader inside a pipelined loop
// Vitis outlines (N143; its call sites all in that loop) keeps its own copy;
// (b) a parent that reads the ROM keeps one for its own reads and every
// child its own; (c) otherwise the readers instanced in the parent's body
// share one copy, unless two of them are called in one pipelined loop of
// the parent (rom_pl; hlsyn aes: aes_subBytes_1 and aes_expandEncKey_1 in
// L5), then each keeps its own, one per instance.
static std::optional<SmallVector<RomCopyPlan>>
planRomModuleCopies(ArrayRef<func::FuncOp> users, const InstanceModel &model) {
  const circt::hlsest::RomConfig &romCfg =
      config().tool.hls.memoryArchitecture.rom;
  if (!romCfg.moduleCopies || users.size() < 2)
    return std::nullopt;
  func::FuncOp parent = model.owner(users);
  if (!parent)
    return std::nullopt;
  bool parentReads = llvm::is_contained(users, parent);
  if (parentReads && !romCfg.moduleCopiesParentReads)
    return std::nullopt;
  SmallVector<func::FuncOp> readers;
  for (func::FuncOp f : users)
    if (f != parent)
      readers.push_back(f);
  // Each reader's instances in the parent: in an outlined loop or the body.
  struct ReaderInstances {
    func::FuncOp fn;
    unsigned loopInstances = 0, bodyInstances = 0;
    llvm::SmallPtrSet<Operation *, 4> pipelines; // pipelined loops calling it
  };
  SmallVector<ReaderInstances> per;
  // The ParentInstances of `fn` in its only caller `caller`, or null.
  auto instancesIn = [&](func::FuncOp fn,
                         func::FuncOp caller) -> const ParentInstances * {
    auto pit = model.parents.find(fn.getOperation());
    if (pit == model.parents.end())
      return nullptr;
    for (const ParentInstances &p : pit->second)
      if (p.parent == caller)
        return &p;
    return nullptr;
  };
  for (func::FuncOp r : readers) {
    // A reader reached through kept functions of its own (each with one
    // caller) is placed by the direct child of the parent on that chain,
    // and has the chain's instances per instance of that child (W9 round
    // 19 review defect 4, kernel w9r19r_rv_rm_gc: g1 called through a kept
    // f and g2 directly, both in one pipelined loop of the top: one ROM in
    // g1 and one in g2, Vitis 2).
    func::FuncOp child = r;
    unsigned below = 1;
    for (unsigned depth = 0;; ++depth) {
      auto callers = model.callers.find(child.getOperation());
      if (depth > 16 || callers == model.callers.end() ||
          callers->second.size() != 1)
        return std::nullopt;
      func::FuncOp caller = callers->second.front();
      if (caller == parent)
        break;
      const ParentInstances *up = instancesIn(child, caller);
      if (!up)
        return std::nullopt;
      below *= std::max(up->instances, 1u);
      child = caller;
    }
    const ParentInstances *pi = instancesIn(child, parent);
    if (!pi)
      return std::nullopt;
    ReaderInstances ri;
    ri.fn = r;
    std::map<unsigned, llvm::SmallPtrSet<Operation *, 2>> modulesOfGroup;
    for (const auto &[site, group] : pi->siteGroups) {
      modulesOfGroup[group].insert(
          circt::hls_analysis::outlinedPipelineAround(site, parent));
      if (auto pl = site->getParentOfType<LoopSchedulePipelineOp>())
        ri.pipelines.insert(pl.getOperation());
    }
    for (auto &[group, modules] : modulesOfGroup)
      (modules.size() == 1 && *modules.begin() ? ri.loopInstances
                                               : ri.bodyInstances) += below;
    per.push_back(std::move(ri));
  }
  bool conflict = false;
  for (unsigned i = 0; i < per.size() && !conflict; ++i)
    for (unsigned j = i + 1; j < per.size() && !conflict; ++j)
      for (Operation *pl : per[i].pipelines)
        if (per[j].pipelines.contains(pl) && per[i].bodyInstances &&
            per[j].bodyInstances) {
          conflict = true;
          break;
        }
  SmallVector<RomCopyPlan> plan;
  bool differs = parentReads || conflict;
  if (parentReads)
    plan.push_back({{parent}, "@" + parent.getName().str(),
                    "the parent reads it itself (N136 (b))", 1});
  RomCopyPlan shared;
  shared.where = "@" + parent.getName().str();
  shared.rule = "readers instanced in the parent's body share one copy "
                "(N136 (c))";
  for (ReaderInstances &ri : per) {
    std::string name = "@" + ri.fn.getName().str();
    if (ri.loopInstances) {
      differs = true;
      plan.push_back({{ri.fn}, name + " in an outlined pipelined loop of @" +
                                   parent.getName().str(),
                      "instance inside an outlined loop module (N136 (a), "
                      "N143)",
                      ri.loopInstances});
    }
    if (!ri.bodyInstances)
      continue;
    if (parentReads || conflict)
      plan.push_back({{ri.fn}, name,
                      parentReads ? "child of a reading parent (N136 (b))"
                                  : "called in one pipelined iteration with "
                                    "another reader (N136 (c))",
                      ri.bodyInstances});
    else
      shared.readers.push_back(ri.fn);
  }
  if (!differs)
    return std::nullopt;
  if (!shared.readers.empty())
    plan.push_back(std::move(shared));
  return plan;
}

// The most reads per cycle of a ROM in one of the function pipelines that
// read it (VITIS_NOTES N144): ceil(reads / II) for a callee pipelined at II
// (its reads issue in its own modulo schedule, one body per II cycles); 0
// when no function pipeline reads it. `others` receives the accesses of
// every other scope.
static unsigned
functionPipelineRomReads(ArrayRef<AccessSummary> accesses, SeqContext *seq,
                         SmallVectorImpl<AccessSummary> &others) {
  if (!seq || !seq->functionPipelines || seq->functionPipelines->ii.empty())
    return 0;
  std::map<Operation *, unsigned> readsPerPipeline;
  for (const AccessSummary &a : accesses) {
    if (!a.isWrite && a.ii == 0 && a.scope && isa<func::FuncOp>(a.scope) &&
        seq->functionPipelines->iiOf(a.scope)) {
      ++readsPerPipeline[a.scope];
      continue;
    }
    others.push_back(a);
  }
  unsigned n = 0;
  for (const auto &[fn, reads] : readsPerPipeline) {
    unsigned ii = *seq->functionPipelines->iiOf(fn);
    n = std::max(n, (reads + ii - 1) / ii);
  }
  return n;
}

// Combine per-loop demand into a single requirement for the shared bank.
//   sequential loops  -> element-wise MAX (the array is time-shared)
static PortDemand computePortDemand(ArrayRef<AccessSummary> accesses,
                                    SeqContext *seq) {
  std::map<Operation *, SmallVector<const AccessSummary *>> byScope;
  for (const auto &a : accesses)
    byScope[a.scope].push_back(&a);

  PortDemand combined;
  bool anyRead = false, anyWrite = false, anyReadModifyScope = false;
  for (const auto &kv : byScope) {
    PortDemand local = scopeDemand(kv.second, seq);
    anyRead |= local.reads > 0;
    anyWrite |= local.writes > 0;
    anyReadModifyScope |= (local.reads > 0 && local.writes > 0);
    combined.reads = std::max(combined.reads, local.reads);
    combined.writes = std::max(combined.writes, local.writes);
    combined.total = std::max(combined.total, local.total);

  }
  combined.segregated = anyRead && anyWrite && !anyReadModifyScope;
  return combined;
}

int64_t ceilDiv(int64_t a, int64_t b) { return (a + b - 1) / b; }

// Data bits per port of the geometry the mapper picked for the bank (for the
// stdout note): x36 only for an SDP bank at most 512 words deep; deeper banks
// use 1Kx18 ... 16Kx1 whatever the kind allows. The widest geometry the
// priced configuration allows when the mapper recorded none (an empty bank).
unsigned usedPortWidth(const BankMathRecord &bm) {
  return bm.configWidth ? bm.configWidth : bm.maxWidth;
}

/// What one memory of a bank costs: its blocks, priced by `mapper` in
/// `memory` at the port configuration `pricedConfig`. `bm`, when given,
/// receives the intermediate values (the debug report); it never feeds back
/// into the arithmetic.
int64_t mapBlocks(const circt::hlsest::MemoryMapper &mapper,
                  const circt::hlsest::DeviceMemory &memory,
                  llvm::StringRef pricedConfig, int64_t words, unsigned bits,
                  BankMathRecord *bm = nullptr) {
  const circt::hlsest::PortConfig *priced = memory.portConfig(pricedConfig);
  if (!priced)
    return 0; // the policy's checkDevice refused such a configuration
  circt::hlsest::MemoryRequest request;
  request.words = words;
  request.writeWidth = bits;
  request.readWidths.push_back(bits);
  circt::hlsest::MappingTrace trace;
  circt::hlsest::Mapping m = mapper.map(request, memory, *priced, &trace);
  if (bm) {
    bm->present = true;
    bm->bitsPerBram = trace.bitsPerBlock;
    bm->wide = pricedConfig ==
               config().tool.hls.memoryArchitecture.pricedWide;
    bm->maxWidth = trace.maxWidth;
    bm->formula = mapper.reportLabel().str();
    bm->band = m.band;
    if (words > 0 && bits > 0) {
      bm->configWidth = m.configWidth;
      bm->widthTiles = m.widthTiles;
      bm->depthPerBlock = m.depthPerBlock;
      bm->addrDepth = m.addrDepth;
      bm->depthTiles = m.depthTiles;
      bm->blocksPerCopy = m.blocks;
      bm->replication = 1;
      bm->blocks = m.blocks;
    }
  }
  return m.blocks;
}

/// `blocks` blocks of `memory` per resource class (cost + overhead).
circt::hlsest::ResourceVector
blockResources(const circt::hlsest::DeviceMemory *memory, int64_t blocks) {
  circt::hlsest::ResourceVector r;
  if (!memory || blocks <= 0)
    return r;
  r.add(memory->cost);
  r.add(memory->overhead);
  return r.scaled(circt::hlsest::Rational(blocks));
}

/// The count of tool.report.primary_memory_class (the bram= number), whole
/// blocks.
unsigned primaryCount(const circt::hlsest::ResourceVector &r) {
  return static_cast<unsigned>(
      r.get(config().tool.report.primaryMemoryClass).ceil());
}

/// What a report line says the memory costs: "bram=<n>" (stdout_format
/// vitis-bram), or "<class>=<n>" per class (per-class).
std::string resourceText(unsigned bram,
                         const circt::hlsest::ResourceVector &r) {
  if (config().tool.report.stdoutFormat != "per-class" || r.empty())
    return "bram=" + std::to_string(bram);
  std::string out;
  for (const auto &[cls, n] : r.items()) {
    if (!out.empty())
      out += " ";
    out += cls + "=" + n.str();
  }
  return out;
}

//===----------------------------------------------------------------------===//
// Access-summary collection (replaces the removed getAccessSummary interface
// method). The memref interface stays dialect-neutral; this loopschedule-aware
// analysis lives in the pass, where reaching into pipeline/stage timing is fair
// game. It reconstructs, per access to this bank:
//   isWrite     - from the op's memory effect on the bank value (dialect-neutral)
//   scope       - the enclosing pipeline (pipelined) or loop (sequential); only
//                 accesses sharing a scope contend for ports
//   ii          - the pipeline II, or 0 for a sequential scope
//   stageStart  - the enclosing stage's `start` cycle (the port-issue phase)
//   latency     - port *occupancy* in cycles; a BRAM address port is held for
//                 one cycle per access regardless of read latency
//===----------------------------------------------------------------------===//

// BRAM address-port occupancy. A synchronous read presents its address for a
// single cycle (data returns later without re-using the port), so one cycle is
// the right contention footprint. Exposed as a hook for multi-cycle/wide ops.
unsigned portOccupancy(bool /*isWrite*/) {
  // tool.hls.memory_architecture.port_occupancy_cycles (1).
  return static_cast<unsigned>(
      config().tool.hls.memoryArchitecture.portOccupancyCycles);
}

// Nearest enclosing loop for a sequential (non-pipelined) access. Uses the
// generic LoopLikeOpInterface so scf.for / affine.for / custom loops all work
// without hard-coding a dialect; falls back to the enclosing function so that
// straight-line accesses still share one scope.
Operation *sequentialScope(Operation *op) {
  for (Operation *cur = op->getParentOp(); cur; cur = cur->getParentOp())
    if (isa<LoopLikeOpInterface>(cur))
      return cur;
  if (auto fn = op->getParentOfType<func::FuncOp>())
    return fn.getOperation();
  return nullptr;
}


// `banks`: the SSA values that name the bank - the alloca's result, or every
// memref.get_global result of a global (--bram-attribute-globals). The
// accesses are collected through views (memref.cast, a subview) and through
// calls to functions defined in the module: a bank passed to a non-inlined
// callee is priced from the callee's accesses too (VITIS_NOTES.md N14 R6:
// the caller's array is replicated for the callee's own pipelined loops; a
// callee called from a pipelined caller loop reads through its port in its
// own sequential scope). An access is counted once however many call sites
// reach it (one instance serves ordered calls; concurrent instances of one
// callee never share an argument array, N14 R2). An access reached through a
// callee instantiated at more than one place (`model`, N14 R6: w3rev_k3,
// w3fx_d2_conc) is port-bound: it never makes the bank replicated.
static void collectAccessesFrom(
    Value mem, Operation *via, StringRef portBoundReason,
    const InstanceModel *model,
    DenseSet<std::pair<Operation *, unsigned>> &visitedArgs,
    DenseSet<Operation *> &seen, SmallVectorImpl<AccessSummary> &out) {
  for (OpOperand &use : mem.getUses()) {
    Operation *user = use.getOwner();
    if (auto call = dyn_cast<CallOpInterface>(user)) {
      func::FuncOp callee = resolveDefinedCallee(call);
      if (!callee)
        continue;
      std::optional<unsigned> idx = callArgIndex(call, use);
      if (!idx || *idx >= callee.getNumArguments())
        continue;
      if (!visitedArgs.insert({callee.getOperation(), *idx}).second)
        continue;
      StringRef reason = portBoundReason;
      if (reason.empty() && model)
        reason = model->calleeArgPortBoundReason(callee, *idx);
      collectAccessesFrom(callee.getArgument(*idx), via ? via : user, reason,
                          model, visitedArgs, seen, out);
      continue;
    }
    if (auto view = dyn_cast<ViewLikeOpInterface>(user))
      if (view.getViewSource() == mem) {
        for (Value r : user->getResults())
          if (isa<BaseMemRefType>(r.getType()))
            collectAccessesFrom(r, via, portBoundReason, model, visitedArgs,
                                seen, out);
        continue;
      }
    bool isWrite = false;
    if (!classifyAccess(user, mem, isWrite))
      continue;
    // Served by a register (VITIS_NOTES N87 R1 / R3): no port; the access
    // that stands for it carries hls.register_promoted_accesses.
    if (circt::hls_analysis::isPromotedAccess(user))
      continue;
    if (!seen.insert(user).second)
      continue;

    AccessSummary a;
    a.op = user;
    a.isWrite = isWrite;
    a.latency = portOccupancy(isWrite);
    a.via = via;
    a.portBound = !portBoundReason.empty();
    a.portBoundReason = portBoundReason;

    if (auto pipeline = user->getParentOfType<LoopSchedulePipelineOp>()) {
      auto stage = user->getParentOfType<LoopSchedulePipelineStageOp>();
      a.scope = pipeline.getOperation();
      a.ii = static_cast<unsigned>(pipeline.getII());
      a.stageStart =
          stage ? static_cast<unsigned>(stage.getStart()) : 0u;
    } else {
      // Sequential: one iteration in flight, so ii=0 collapses the scope to at
      // most one access per cycle in scopeDemand().
      a.scope = sequentialScope(user);
      a.ii = 0;
      a.stageStart = 0;
    }
    out.push_back(a);
  }
}

SmallVector<AccessSummary>
collectAccessSummaries(ArrayRef<Value> banks,
                       const InstanceModel *model = nullptr) {
  SmallVector<AccessSummary> out;
  DenseSet<std::pair<Operation *, unsigned>> visitedArgs;
  DenseSet<Operation *> seen;
  for (Value mem : banks)
    collectAccessesFrom(mem, /*via=*/nullptr, /*portBoundReason=*/"", model,
                        visitedArgs, seen, out);
  return out;
}

// neverWritten (ReadOnlyMemory.h): no op writes or frees the memory named by
// `sites` (the get_global results of a global) or a value derived from them -
// a view, a loop iter_arg / result of a pointer walk - and none escapes.
using circt::hls_analysis::neverWritten;

//===----------------------------------------------------------------------===//
// Debug-record helpers (read-only views of the IR; no influence on the cost).
//===----------------------------------------------------------------------===//

static std::string scopeKindName(Operation *scope) {
  if (!scope)
    return "none";
  if (isa<LoopSchedulePipelineOp>(scope))
    return "pipeline";
  if (isa<LoopLikeOpInterface>(scope))
    return "loop";
  if (isa<func::FuncOp>(scope))
    return "func";
  return scope->getName().getStringRef().str();
}

static bool isStoreEnableOp(Operation *op) {
  StringRef n = op->getName().getStringRef();
  return n == "hls.store_enable" || n == "hls.affine.store_enable";
}

static unsigned counterAttr(Operation *op, StringRef name) {
  if (auto a = op->getAttrOfType<IntegerAttr>(name))
    return a.getInt() > 0 ? static_cast<unsigned>(a.getInt()) : 0u;
  return 0;
}

// Identity: id, name, varname, kind, enclosing function, location, partition
// provenance. All of it comes from attributes the front end / banking left on
// the op; nothing here is derived from the estimate.
static void describeMemref(Operation *op, unsigned index, MemrefRecord &r) {
  StringRef opName = op->getName().getStringRef();
  if (auto g = dyn_cast<memref::GlobalOp>(op)) {
    r.kind = "global";
    r.name = g.getSymName().str();
    r.id = "global#" + std::to_string(index);
  } else {
    r.kind = opName.starts_with("memref.") ? opName.drop_front(7).str()
                                            : opName.str();
    if (auto fn = op->getParentOfType<func::FuncOp>())
      r.func = fn.getName().str();
    r.id = (r.func ? *r.func : std::string("?")) + "#" + std::to_string(index);
  }

  if (auto v = op->getAttrOfType<StringAttr>("polygeist.varname"))
    r.varname = v.getValue().str();
  else if (auto b = op->getAttrOfType<StringAttr>("hls.bank_of"))
    r.varname = b.getValue().str();
  if (auto g = op->getAttrOfType<StringAttr>("hls.from_global"))
    r.fromGlobal = g.getValue().str();
  if (auto m = op->getAttrOfType<StringAttr>("hls.struct_member"))
    r.structMember = m.getValue().str();
  if (auto m = op->getAttrOfType<StringAttr>("hls.aggregated"))
    r.aggregated = m.getValue().str();
  if (auto k = op->getAttrOfType<StringAttr>("hls.kept_reason"))
    r.keptReason = k.getValue().str();

  if (auto f = findFileLoc(op->getLoc())) {
    r.hasLoc = true;
    r.locFile = f.getFilename().str();
    r.locLine = f.getLine();
    r.locCol = f.getColumn();
  }
  r.locText = locString(op->getLoc());

  // Partition provenance. Banks carry `hls.partition` (set by memory banking
  // from the original `hls.array_partition` entry); an unbanked memref may
  // still carry the pragma itself.
  PartitionRecord &p = r.partition;
  auto readFields = [&](DictionaryAttr d) {
    if (auto k = d.getAs<StringAttr>("kind"))
      p.kind = k.getValue().str();
    if (auto f = d.getAs<IntegerAttr>("factor"))
      p.factor = f.getInt();
    if (auto dm = d.getAs<IntegerAttr>("dim"))
      p.dim = dm.getInt();
    if (auto s = d.getAs<StringAttr>("source"))
      p.source = s.getValue().str();
    else
      p.source = "pragma";
  };
  if (auto d = op->getAttrOfType<DictionaryAttr>("hls.partition")) {
    p.present = true;
    p.applied = true;
    readFields(d);
    if (auto bi = op->getAttrOfType<IntegerAttr>("hls.bank_index"))
      p.bankIndex = bi.getInt();
    if (auto bc = op->getAttrOfType<IntegerAttr>("hls.bank_count"))
      p.bankCount = bc.getInt();
    if (auto all = d.getAs<ArrayAttr>("dims"))
      for (Attribute a : all)
        if (auto dd = dyn_cast<DictionaryAttr>(a)) {
          auto k = dd.getAs<StringAttr>("kind");
          auto f = dd.getAs<IntegerAttr>("factor");
          auto dm = dd.getAs<IntegerAttr>("dim");
          if (k && f && dm)
            p.dims.push_back({k.getValue().str(), f.getInt(), dm.getInt()});
        }
    if (auto from = d.getAs<StringAttr>("from"))
      p.from = from.getValue().str();
  } else if (auto arr = op->getAttrOfType<ArrayAttr>("hls.array_partition")) {
    if (!arr.empty())
      if (auto d = dyn_cast<DictionaryAttr>(arr[0])) {
        p.present = true;
        p.applied = false;
        readFields(d);
      }
  }
  if (auto reason = op->getAttrOfType<StringAttr>("hls.partition_reason"))
    p.reason = reason.getValue().str();
  if (auto st = op->getAttrOfType<DictionaryAttr>("hls.steering")) {
    if (auto g = st.getAs<DenseI64ArrayAttr>("groups"))
      p.steeredGroups.assign(g.asArrayRef().begin(), g.asArrayRef().end());
    if (auto f = st.getAs<IntegerAttr>("forwarded_reloads"))
      p.forwardedReloads = f.getInt();
    if (auto f = st.getAs<IntegerAttr>("pruned_store_enables"))
      p.prunedStoreEnables = f.getInt();
  }
}

// Per-access and per-scope views of the same summaries the estimate used.
static void recordAccesses(ArrayRef<AccessSummary> accesses, MemrefRecord &r,
                           SeqContext *seq) {
  r.accesses.clear();
  r.perScope.clear();
  SmallVector<Operation *> scopeOrder; // first-appearance order (deterministic)
  for (const AccessSummary &a : accesses) {
    AccessRecord ar;
    ar.op = a.op->getName().getStringRef().str();
    ar.isWrite = a.isWrite;
    ar.scope = a.scope;
    ar.scopeKind = scopeKindName(a.scope);
    ar.scopeLoc = a.scope ? locString(a.scope->getLoc()) : "<none>";
    ar.ii = a.ii;
    ar.stageStart = a.stageStart;
    ar.storeEnable = isStoreEnableOp(a.op);
    ar.mergedLoads = counterAttr(a.op, "hls.merged_loads");
    ar.forwardedLoads = counterAttr(a.op, "hls.forwarded_loads");
    ar.removedStores = counterAttr(a.op, "hls.removed_stores");
    ar.registerPromoted =
        counterAttr(a.op, circt::hls_analysis::kPromotedCountAttr);
    ar.mergedIfElseStores = counterAttr(a.op, "hls.merged_if_else_stores");
    ar.hoistedConditional = a.op->hasAttr("hls.hoisted_conditional");
    if (auto b = a.op->getAttrOfType<IntegerAttr>("hls.port_bank"))
      ar.portBank = std::to_string(b.getInt());
    else if (auto n = a.op->getAttrOfType<IntegerAttr>("hls.port_banks"))
      ar.portBank = "any of " + std::to_string(n.getInt());
    if (auto fn = a.op->getParentOfType<func::FuncOp>())
      ar.inFunc = fn.getName().str();
    if (a.via) {
      std::string v = "call";
      // The callee's name from the call itself: a.via is a call to a
      // defined function (collectAccessesFrom follows no other), and a
      // symbol lookup per access was a linear scan of the module (hp_fft
      // n1024 UF32, OPEN_ISSUES O103).
      if (auto call = dyn_cast<CallOpInterface>(a.via))
        if (auto sym = dyn_cast_or_null<SymbolRefAttr>(
                call.getCallableForCallee().dyn_cast<SymbolRefAttr>()))
          v += " @" + sym.getLeafReference().str();
      ar.viaCall = v + " @ " + locString(a.via->getLoc());
    }
    ar.portBound = a.portBound;
    ar.portBoundReason = a.portBoundReason.str();
    r.accesses.push_back(std::move(ar));
    if (!llvm::is_contained(scopeOrder, a.scope))
      scopeOrder.push_back(a.scope);
  }
  for (Operation *scope : scopeOrder) {
    SmallVector<const AccessSummary *> group;
    for (const AccessSummary &a : accesses)
      if (a.scope == scope)
        group.push_back(&a);
    ScopeDemandRecord sd;
    sd.scopeKind = scopeKindName(scope);
    sd.scopeLoc = scope ? locString(scope->getLoc()) : "<none>";
    sd.ii = group.front()->ii;
    std::string note;
    sd.demand = scopeDemand(group, seq, &note);
    if (!note.empty())
      sd.sameState = note;
    r.perScope.push_back(std::move(sd));
  }
}

//===----------------------------------------------------------------------===//
// Top-level estimator.
//===----------------------------------------------------------------------===//
// ROMs: element width from the stored values (VITIS_NOTES.md N26).
//===----------------------------------------------------------------------===//
// Vitis implements an array whose every write stores a constant as a ROM
// holding those constants (forgebench activation_op1: `set_value(FM_buffer_3,
// 1)` -> `FM_buffer_3_U 50176x12 ROM_AUTO_1R`; --mark-constant-fills marks
// such arrays early, with the width, as `hls.const_fill`), and gives a ROM,
// filled or constant-initialised, the element width its values need (kernels
// w7_rf6 / rf7 / rf9u / rf12u / rf17u / rf_apf / rfneg / rfneg1 / rf_iota /
// rf_part / rf_stride and the tables w7_rtbl9 / rtblneg / rtbl_16 /
// rtbl_gap / rtbl_hi):
//   - no negative value: A = the unsigned width of the largest value; each
//     value cut to A bits is read as signed, and the width is the most signed
//     bits any of them needs (300 -> 9, 2048 -> 12, 100000 -> 16, 6 -> 2,
//     7 -> 1, {1, 6} -> 2, {0..100, 384..511} -> 8, [98304, 131071] -> 16);
//   - some negative value: the most signed bits any value needs (-300 -> 10,
//     -1 -> 1, -300..300 -> 10); mixed signs beyond rtblneg are unconfirmed;
//   - all values 0: no memory (N1a, dg_c_const0).
// A partial or strided fill is a ROM as well (w7_rf_part, w7_rf_stride: the
// unwritten words are undefined).

// The ROM element width of `vals` (N26); 0 when every value is 0.
static unsigned narrowRomWidth(ArrayRef<APInt> vals) {
  bool anyNegative =
      llvm::any_of(vals, [](const APInt &v) { return v.isNegative(); });
  unsigned width = 0;
  if (anyNegative) {
    for (const APInt &v : vals)
      width = std::max(width, v.getSignificantBits());
    return width;
  }
  unsigned a = 0;
  for (const APInt &v : vals)
    a = std::max(a, v.getActiveBits());
  if (a == 0)
    return 0;
  for (const APInt &v : vals)
    width = std::max(width, v.trunc(a).getSignificantBits());
  return width;
}

//===----------------------------------------------------------------------===//
// hls::stream handle storage (--bram-stream-fifos, StreamFifos.h): the storage
// is not a RAM; it stands for one FIFO per stream object, priced by Vitis's
// FIFO rule. `rec` gets the geometry of the handle storage and the FIFOs.
//===----------------------------------------------------------------------===//
// Take the narrowed element width of `op` (hls.narrow_bits) into `rec` when
// it is below the declared width; the width the array is priced with.
static unsigned applyNarrowWidth(Operation *op, MemrefRecord &rec) {
  rec.narrow.reset();
  auto bits = op->getAttrOfType<IntegerAttr>(kNarrowBitsAttrName);
  if (!bits || bits.getInt() <= 0 ||
      static_cast<uint64_t>(bits.getInt()) >= rec.elemBits)
    return rec.elemBits;
  MemrefRecord::NarrowRecord n;
  n.declaredBits = rec.elemBits;
  n.bits = static_cast<unsigned>(bits.getInt());
  if (auto why = op->getAttrOfType<StringAttr>(kNarrowReasonAttrName))
    n.reason = why.getValue().str();
  rec.narrow = std::move(n);
  return rec.narrow->bits;
}

static BRAMCost estimateStreamFifos(MemoryResourceOpInterface iface,
                                    MemrefRecord &rec,
                                    StreamHandleRecord fifo) {
  rec.shape = iface.getStaticShape();
  Type elt = iface.getElementType();
  {
    llvm::raw_string_ostream os(rec.elemType);
    elt.print(os);
  }
  rec.elemBits = elt.isIntOrFloat() ? elt.getIntOrFloatBitWidth() : 0u;
  int64_t words = 1;
  for (int64_t d : rec.shape)
    if (!ShapedType::isDynamic(d))
      words *= d;
  rec.words = words;
  BRAMCost cost;
  cost.kind = StorageKind::RAM_1P; // not used: the line says FIFO
  cost.label = "FIFO";
  cost.bramCount = fifo.bram;
  std::string groups;
  for (const FifoGroup &g : fifo.groups) {
    if (!groups.empty())
      groups += "; ";
    groups += std::to_string(g.count) + " x ";
    if (g.member)
      groups += "member " + std::to_string(*g.member) + " ";
    groups += std::to_string(g.depth) + "x" + std::to_string(g.bits) +
              " (depth " + g.depthSource + ", width " + g.bitsSource +
              "): " + g.reason;
  }
  cost.note = "hls::stream storage, not a RAM: " +
              std::to_string(fifo.fifos) + " FIFO(s) = " +
              std::to_string(fifo.bram) + " BRAM [" + groups + "]";
  if (!fifo.note.empty())
    cost.note += " (" + fifo.note + ")";
  rec.status = "fifo";
  rec.ramType = "FIFO";
  rec.ramReason = "hls::stream FIFOs: " + groups;
  rec.bram = cost.bramCount;
  rec.fifo = std::move(fifo);
  return cost;
}

//===----------------------------------------------------------------------===//
// Dataflow ping-pong channels (--bram-dataflow-channels, DataflowChannels.h).
//===----------------------------------------------------------------------===//
// The arms of every scf.if / affine.if between `op` and its scope.
static SmallVector<std::pair<Operation *, unsigned>, 2>
nestedArms(Operation *op, Operation *scope) {
  SmallVector<std::pair<Operation *, unsigned>, 2> arms;
  for (Operation *cur = op; cur && cur != scope;) {
    Operation *parent = cur->getParentOp();
    if (!parent)
      break;
    if (isa<scf::IfOp, affine::AffineIfOp>(parent))
      arms.push_back({parent, cur->getParentRegion()->getRegionNumber()});
    cur = parent;
  }
  return arms;
}

// Whether two accesses of one scope lie in different arms of one if, where
// they still are or where --convert-affine-to-loopschedule hoisted them from.
static bool onExclusivePaths(Operation *a, Operation *b, Operation *scope) {
  SeqScopeIndex::OpInfo x, y;
  x.arms = nestedArms(a, scope);
  y.arms = nestedArms(b, scope);
  return inExclusiveArms(x, hoistedArmsOf(a), y, hoistedArmsOf(b));
}

// Two accesses of the bank that one process can make in the same cycle, so
// that the process drives the bank's second port; empty when there are none.
// Vitis gives a process a second port of a channel exactly then (kernels:
// two reads, two writes or a read-modify-write in one iteration of a
// pipelined loop at any II; two independent accesses a non-pipelined loop
// schedules in one state). Accesses on mutually exclusive arms of an if share
// one port: the count is the most on any one control path, not the sum over
// the arms. Two loads of one address are one load. One function body can
// serve two processes (a helper called as the producer and again as the
// consumer): its accesses then belong to two processes, told apart by the
// call through which each was reached, and the producer's write and the
// consumer's read never make one process drive two ports (kernel: one copy
// helper called twice around a 512-word channel, Vitis single memory, 2).
// The memref and the indices of a plain bank access (memref.load,
// memref.store, hls.store_enable); false for anything else.
static bool bankAccessIndices(Operation *op, Value &mem,
                              SmallVectorImpl<Value> &indices) {
  if (auto ld = dyn_cast<memref::LoadOp>(op)) {
    mem = ld.getMemRef();
    indices.assign(ld.getIndices().begin(), ld.getIndices().end());
    return true;
  }
  if (auto st = dyn_cast<memref::StoreOp>(op)) {
    mem = st.getMemRef();
    indices.assign(st.getIndices().begin(), st.getIndices().end());
    return true;
  }
  if (auto se = dyn_cast<circt::hls_analysis::StoreEnableOp>(op)) {
    mem = se.getMemref();
    indices.assign(se.getIndices().begin(), se.getIndices().end());
    return true;
  }
  return false;
}

// VITIS_NOTES N105: every access `group` makes to the bank inside the
// pipelined `scope` is at one address that does not change in the loop
// (the operands of every dimension wider than one word are defined outside
// the loop and are the same values in every access; a one-word dimension is
// a completely partitioned one, whose in-bank index is always 0). Vitis
// promotes such an element to a register: one load before the loop, one
// store after it.
static bool invariantInPipeline(ArrayRef<const AccessSummary *> group,
                                Operation *scope) {
  SmallVector<Value> first;
  bool haveFirst = false;
  for (const AccessSummary *a : group) {
    Value mem;
    SmallVector<Value> idx;
    if (a->via || !bankAccessIndices(a->op, mem, idx))
      return false;
    auto ty = dyn_cast<MemRefType>(mem.getType());
    if (!ty || !ty.hasStaticShape() ||
        idx.size() != static_cast<size_t>(ty.getRank()))
      return false;
    for (auto [d, v] : llvm::enumerate(idx)) {
      if (ty.getDimSize(d) == 1)
        continue;
      Region *r = v.getParentRegion();
      if (r && scope->isAncestor(r->getParentOp()))
        return false; // computed in the loop
      if (haveFirst && first[d] != v)
        return false;
    }
    if (!haveFirst) {
      first = idx;
      haveFirst = true;
    }
  }
  return haveFirst;
}

// Whether a loop lies between `a` and `b` (a before b in one block), or
// inside an op between them: the store-back after `a` and the preload before
// `b` are then in different states (N105, kernel w9r14p_pp_mid).
static bool loopBetween(Operation *a, Operation *b) {
  for (Operation *op = a->getNextNode(); op && op != b;
       op = op->getNextNode()) {
    WalkResult r = op->walk([](Operation *inner) {
      return isa<LoopLikeOpInterface, LoopSchedulePipelineOp>(inner)
                 ? WalkResult::interrupt()
                 : WalkResult::advance();
    });
    if (r.wasInterrupted())
      return true;
  }
  return false;
}

static std::string sameCycleAccesses(ArrayRef<AccessSummary> accesses,
                                     SeqContext *seq,
                                     std::string *promotedNote = nullptr) {
  using ProcessScope = std::pair<Operation *, Operation *>; // (via, scope)
  SmallVector<ProcessScope> scopes; // first-appearance order (deterministic)
  for (const AccessSummary &a : accesses)
    if (!llvm::is_contained(scopes, ProcessScope{a.via, a.scope}))
      scopes.push_back({a.via, a.scope});
  const bool promote =
      config().tool.hls.dataflowChannels.promotedInvariantAccesses;
  SmallVector<Operation *> promoted; // pipelines whose accesses are registers
  for (auto [via, scope] : scopes) {
    SmallVector<const AccessSummary *> group;
    for (const AccessSummary &a : accesses)
      if (a.scope == scope && a.via == via)
        group.push_back(&a);
    if (promote && !via && group.front()->ii != 0 && scope &&
        invariantInPipeline(group, scope)) {
      promoted.push_back(scope);
      if (promotedNote) {
        std::string at = locString(scope->getLoc());
        if (promotedNote->find(at) == std::string::npos)
          *promotedNote += (promotedNote->empty() ? "" : ", ") + at;
      }
      continue;
    }
    if (group.size() < 2)
      continue;
    unsigned ii = group.front()->ii;
    if (ii == 0) {
      if (!seq)
        continue;
      std::string note;
      if (seq->sequentialDemand(group, &note).total >= 2)
        return "non-pipelined scope, " + note;
      continue;
    }
    for (size_t i = 0; i < group.size(); ++i)
      for (size_t j = i + 1; j < group.size(); ++j) {
        const AccessSummary *a = group[i], *b = group[j];
        if (onExclusivePaths(a->op, b->op, scope))
          continue;
        if (!a->isWrite && !b->isWrite &&
            compareAddresses(a->op, b->op) == AddrRelation::Same)
          continue;
        return "pipelined scope (II " + std::to_string(ii) + "), one control "
               "path of one iteration: " + accessText(a) + " + " +
               accessText(b);
      }
  }
  // Two promoted pipelines one after the other in one block, no loop
  // between them: the store-back of the first and the preload of the second
  // share a state (N105, kernels w9r14p_pp_unr4 / pp_nomask: the unrolled
  // row copies of one RMW pipeline, separate).
  for (Operation *p1 : promoted)
    for (Operation *p2 : promoted)
      if (p1 != p2 && p1->getBlock() == p2->getBlock() &&
          p1->isBeforeInBlock(p2) && !loopBetween(p1, p2))
        return "the register store-back after the pipelined loop at " +
               locString(p1->getLoc()) + " and the preload before the one at " +
               locString(p2->getLoc()) +
               " share a state (VITIS_NOTES N105: loop-invariant accesses "
               "promoted to registers)";
  return {};
}

// Prices `iface` as the ping-pong channel `ch` (one bank of it). `rec` gets
// the geometry, the accesses and the decisions.
static BRAMCost estimateChannel(MemoryResourceOpInterface iface,
                                MemrefRecord &rec, const DataflowChannel &ch,
                                ArrayRef<AccessSummary> accesses,
                                SeqContext *seq, const Models &models,
                                const std::string &secondPort,
                                const std::string &promotedLoops = {}) {
  rec.shape = iface.getStaticShape();
  Type elt = iface.getElementType();
  {
    llvm::raw_string_ostream os(rec.elemType);
    elt.print(os);
  }
  rec.elemBits = elt.getIntOrFloatBitWidth();
  unsigned pricedBits = applyNarrowWidth(iface.getOperation(), rec);
  int64_t words = 1;
  for (int64_t d : rec.shape)
    words *= d;
  rec.words = words;
  rec.accessesAttributed = true;

  PipoRecord p;
  p.channel = true;
  p.region = ch.regionName;
  p.regionKind = ch.regionKind;
  p.processes = ch.processes;
  p.blocks = ch.blocks;
  p.blocksSource = ch.blocksSource;
  p.bindType = ch.bindType;
  p.bindImpl = ch.bindImpl;
  p.secondPort = secondPort;
  bool twoPorts = !p.secondPort.empty();
  bool bound2p = ch.bindType == "ram_2p" || ch.bindType == "ram_s2p";
  // A ram_1p / ram_s2p binding gives each process one port of the bank (a
  // read port and a write port at most): a second access in the same cycle
  // waits, Vitis raises the II instead (pipo_c_bindt2p: two reads per
  // iteration of a ram_s2p channel, 256x32 = 2 x 1, x36).
  bool onePortPerSide = ch.bindType == "ram_1p" || ch.bindType == "ram_s2p";
  std::string clamped;
  if (twoPorts && onePortPerSide) {
    clamped = "; bind_storage type=" + ch.bindType +
              " has one port per side, so the second access waits (" +
              p.secondPort + ")";
    twoPorts = false;
  }
  bool lutram = ch.bindImpl == "lutram";
  // Each memory of the channel goes where the storage selector puts it
  // (tool.backend.storage_selector), like any other bank, and is priced in
  // the memory the selector chose.
  const circt::hlsest::Device &device = config().device;
  const circt::hlsest::DeviceMemory *chosen = models.block;
  auto belowBlock = [&](int64_t w,
                        unsigned bits) -> std::optional<std::string> {
    circt::hlsest::MemoryRequest request;
    request.words = w;
    request.writeWidth = bits;
    request.readWidths.push_back(bits);
    request.narrowed = bits != rec.elemBits;
    circt::hlsest::TierChoice choice =
        models.selector->select(request, device, {});
    if (!choice.memory.empty()) {
      if (const circt::hlsest::DeviceMemory *m = device.memory(choice.memory))
        chosen = m;
      return std::nullopt;
    }
    const circt::hlsest::StorageSelectorConfig &sel =
        config().tool.backend.storageSelector;
    // The builtin threshold's words, when it is the reason (Vitis default).
    if (sel.belowBlock(w * static_cast<int64_t>(bits)))
      return std::string(sel.belowSymbol()) + " " +
             std::to_string(sel.minBlockBits) + " bits";
    return "kept in tier " + choice.tier + " by storage selector '" +
           models.selector->name().str() + "'";
  };
  ChannelPrice price = priceChannel(
      words, pricedBits, ch.blocks, twoPorts, bound2p, lutram, belowBlock,
      [&](int64_t w, unsigned bits, bool sdp) -> int64_t {
        const circt::hlsest::MemoryArchitectureConfig &m =
            config().tool.hls.memoryArchitecture;
        llvm::StringRef priced = sdp ? m.pricedWide : m.pricedNarrow;
        if (!chosen->portConfig(priced)) {
          // As for an ordinary bank: a memory without the configuration the
          // channel is priced at fails the run, naming the bank.
          iface->emitError("--bram-analysis: dataflow channel priced at port "
                           "configuration '")
              << priced << "', which memory '" << chosen->id << "' (tier "
              << chosen->tier << ") does not have";
          models.failed = true;
          return 0;
        }
        return mapBlocks(*models.mapper, *chosen, priced, w, bits,
                         &rec.bankMath);
      });
  // The memory that priced it, when the selector chose another memory than
  // the mapper's default block (the resource classes follow it).
  if (price.bram && chosen != models.block)
    rec.memoryId = chosen->id;
  if (rec.bankMath.present)
    rec.bankMath.blocks = price.bram;
  p.mode = price.mode;
  p.rule = price.rule;
  if (lutram)
    p.modeReason = "bind_storage impl=lutram";
  else if (twoPorts)
    p.modeReason = "a process drives a second port: " + p.secondPort;
  else if (bound2p)
    p.modeReason = "bind_storage type=" + ch.bindType +
                   " (separate memories even with one port per process)";
  else
    p.modeReason = "every process uses one port of the bank";
  if (!twoPorts && !promotedLoops.empty())
    p.modeReason += " (the loop-invariant accesses of the pipelined loop(s) "
                    "at " +
                    promotedLoops +
                    " are registers: one load before, one store after the "
                    "loop, VITIS_NOTES N105)";
  p.modeReason += clamped;

  BRAMCost cost;
  cost.kind = twoPorts || ch.blocks > 1 ? StorageKind::RAM_2P
                                        : StorageKind::RAM_1P;
  cost.label = "PIPO";
  cost.bramCount = price.bram;
  std::string procs;
  for (const DataflowProcess &dp : ch.processes) {
    if (!procs.empty())
      procs += ", ";
    procs += std::string(dp.writes && dp.reads ? "writes+reads "
                         : dp.writes           ? "writes "
                                               : "reads ") +
             dp.name;
  }
  cost.note = "dataflow ping-pong channel of " + ch.regionKind + " " +
              ch.regionName + " [" + procs + "]; blocks " + ch.blocksSource +
              "; " + price.mode + " (" + p.modeReason + "): " + price.rule +
              " (never replicated)";
  recordAccesses(accesses, rec, seq);
  rec.demand = computePortDemand(accesses, seq);
  rec.status = "pipo";
  rec.ramType = "PIPO";
  rec.ramReason = price.mode + ": " + p.modeReason + "; " + price.rule;
  rec.bram = price.bram;
  rec.pipo = std::move(p);
  return cost;
}

// Which arrays of a dataflow region have a process that drives a second port
// of a bank. Vitis builds every bank of one partitioned channel from one RAM
// module, and the module has one mode: when a process drives a second port of
// one bank, every bank is a separate memory per block (corpus:
// class_ece8893_spring_2025 vishnu_varma_venkata lab3, row_ptr_A_local
// complete dim 1: only bank 0 is read twice per iteration, one "separate"
// log line for the module, all 8 banks 65x32 = 4).
class ChannelPorts {
public:
  using SitesFn = llvm::function_ref<SmallVector<Value>(Operation *)>;
  ChannelPorts(SeqContext *seq, const InstanceModel *instances,
               SitesFn sitesOf)
      : seq(seq), instances(instances), sitesOf(sitesOf) {}

  // The two same-cycle accesses of one process on bank `op`, or empty.
  const std::string &ofBank(Operation *op) {
    auto it = cache.find(op);
    if (it != cache.end())
      return it->second;
    SmallVector<AccessSummary> accesses =
        collectAccessSummaries(sitesOf(op), instances);
    std::string promoted;
    std::string &pair = cache[op] =
        sameCycleAccesses(accesses, seq, &promoted);
    promotedCache[op] = std::move(promoted);
    return pair;
  }

  // The pipelined loops whose loop-invariant accesses of bank `op` were
  // promoted to registers (VITIS_NOTES N105), for the debug reason.
  const std::string &promotedOf(Operation *op) {
    ofBank(op);
    return promotedCache[op];
  }

  // The same for the array `op` is a bank of: its own finding, else the first
  // one of another bank of the same array (prefixed with that bank).
  std::string ofArray(Operation *op) {
    std::string own = ofBank(op);
    if (!own.empty())
      return own;
    auto bankOf = op->getAttrOfType<StringAttr>("hls.bank_of");
    if (!bankOf)
      return own;
    Operation *scope = isa<memref::GlobalOp>(op)
                           ? op->getParentOp()
                           : op->getParentOfType<func::FuncOp>().getOperation();
    if (!scope)
      return own;
    std::string found;
    // The banks of the scope in walk order, indexed once per scope (a walk
    // of the scope per bank was quadratic: hp_fft n1024 UF32, OPEN_ISSUES
    // O103).
    for (Operation *other : banksOf(scope)[bankKey(op)]) {
      if (other == op)
        continue;
      const std::string &pair = ofBank(other);
      if (pair.empty())
        continue;
      found = "another bank of the array";
      if (auto bi = other->getAttrOfType<IntegerAttr>("hls.bank_index"))
        found += " (bank " + std::to_string(bi.getInt()) + ")";
      found += " shares its RAM module: " + pair;
      break;
    }
    return found;
  }

private:
  /// The ops of one array's banks: same op name, hls.bank_of, hls.bank_count.
  using BankKey = std::tuple<const void *, const void *, const void *>;
  static BankKey bankKey(Operation *op) {
    return {op->getName().getAsOpaquePointer(),
            op->getAttr("hls.bank_of").getAsOpaquePointer(),
            op->getAttr("hls.bank_count").getAsOpaquePointer()};
  }
  std::map<Operation *, std::string> promotedCache;
  std::map<BankKey, SmallVector<Operation *>> &banksOf(Operation *scope) {
    auto [it, fresh] = bankIndex.try_emplace(scope);
    if (fresh)
      scope->walk([&](Operation *other) {
        if (other->getAttrOfType<StringAttr>("hls.bank_of"))
          it->second[bankKey(other)].push_back(other);
      });
    return it->second;
  }

  SeqContext *seq;
  const InstanceModel *instances;
  SitesFn sitesOf;
  DenseMap<Operation *, std::string> cache;
  DenseMap<Operation *, std::map<BankKey, SmallVector<Operation *>>> bankIndex;
};

// When `op` is an array of a dataflow region: its channel price, or nullopt
// to price it as an ordinary memory (then `rec.pipo` says why it is not a
// channel). Arrays without a static integer / float shape and completely
// partitioned arrays are never channels.
/// The number of elements of a statically shaped alloca / alloc / global.
static std::optional<int64_t> staticElementCount(Operation *op) {
  MemRefType type;
  if (auto g = dyn_cast<memref::GlobalOp>(op))
    type = g.getType();
  else if (op->getNumResults() == 1)
    type = dyn_cast<MemRefType>(op->getResult(0).getType());
  if (!type || !type.hasStaticShape())
    return std::nullopt;
  return type.getNumElements();
}

/// VITIS_NOTES N67 (kernels w9r8p_st_d256 / st_d4, control st_pipo;
/// class_ece8893 gabriel_lopez_lugo lab2): a local array of a dataflow region
/// with `#pragma HLS stream` (type fifo, or no type) and a depth is one FIFO
/// of that depth at the element width (`buf_r_U | fifo channel | 160, 256,
/// 1`), priced with the stream FIFO bands (a FIFO of at most srl_max_bits is
/// shift registers), whatever the array's shape. A pragma without a depth
/// gives a FIFO as deep as the array (review kernel s1_nodepth).
static std::optional<StreamHandleRecord>
streamPragmaArrayFifo(Operation *op, Type elt, const Models &models) {
  auto arr = op->getAttrOfType<ArrayAttr>("hls.stream");
  if (!arr || arr.empty())
    return std::nullopt;
  auto d = dyn_cast<DictionaryAttr>(arr[0]);
  if (!d)
    return std::nullopt;
  if (auto t = d.getAs<StringAttr>("type"))
    if (!t.getValue().equals_insensitive("fifo"))
      return std::nullopt;
  auto depthAttr = d.getAs<IntegerAttr>("depth");
  if (!depthAttr || depthAttr.getInt() <= 0)
    return std::nullopt;
  int64_t fifoDepth = depthAttr.getInt();
  std::string depthSource = "pragma";
  // A pragma without a depth (cgeist marks the default 2 depth_defaulted):
  // the FIFO is as deep as the array (W9 round 8 review defect 4, kernel
  // w9r8rev s1_nodepth.cpp: int buf[1024] -> fifo_w32_d1024, 2 BRAM).
  if (d.get("depth_defaulted")) {
    std::optional<int64_t> words = staticElementCount(op);
    if (!words || *words <= 0)
      return std::nullopt;
    fifoDepth = *words;
    depthSource = "the array's size (#pragma HLS stream without a depth)";
  }
  unsigned bits = packedTypeBits(elt);
  std::string bitsSource = "ir element";
  // The packed width of a struct element --split-struct-memrefs split off.
  if (auto a = op->getAttrOfType<IntegerAttr>("hls.stream_array_element_bits"))
    if (a.getInt() > 0) {
      bits = static_cast<unsigned>(a.getInt());
      bitsSource = "packed struct element (hls.stream_array_element_bits)";
    }
  if (bits == 0)
    return std::nullopt;
  FifoGroup g;
  g.count = 1;
  g.countSource = "the whole array (#pragma HLS stream, N67)";
  g.depth = fifoDepth;
  g.depthSource = depthSource;
  g.bits = bits;
  g.bitsSource = bitsSource;
  FifoPrice p = priceFifo(g.depth, g.bits, "", [&](int64_t depth,
                                                   unsigned b) {
    return mapBlocks(*models.streamMapper, *models.block,
                     config().tool.hls.streams.pricedConfig, depth, b);
  });
  g.bramEach = p.bram;
  g.reason = p.reason;
  StreamHandleRecord r;
  r.groups.push_back(std::move(g));
  r.bram = p.bram;
  r.fifos = 1;
  r.note = "an array with #pragma HLS stream in a dataflow region: one FIFO "
           "of the pragma's depth (VITIS_NOTES N67)";
  return r;
}

static std::optional<BRAMCost>
tryDataflowChannel(MemoryResourceOpInterface iface, MemrefRecord &rec,
                   ArrayRef<Value> sites, SeqContext *seq,
                   const Models &models, const InstanceModel *instances,
                   ChannelPorts &ports, ProcessMerges &merges) {
  Operation *op = iface.getOperation();
  Type elt = iface.getElementType();
  if (!elt.isIntOrFloat() || op->hasAttr(kRegistersAttrName))
    return std::nullopt;
  // An array every write of which stores a constant is a ROM of those
  // constants (no memory at all when they are all 0), whatever processes
  // write it; a constant global is a ROM too.
  if (op->hasAttr("hls.const_fill"))
    return std::nullopt;
  if (auto g = dyn_cast<memref::GlobalOp>(op))
    if (g.getConstant())
      return std::nullopt;
  int64_t words = 1;
  for (int64_t d : iface.getStaticShape()) {
    if (ShapedType::isDynamic(d))
      return std::nullopt;
    words *= d;
  }
  if (sites.empty())
    return std::nullopt;
  SmallVector<AccessSummary> accesses =
      collectAccessSummaries(sites, instances);
  SmallVector<ChannelAccess> anchors;
  for (const AccessSummary &a : accesses)
    anchors.push_back({a.via ? a.via : a.op, a.isWrite});
  ChannelVerdict v = analyzeDataflowChannel(op, anchors, words, &merges);
  if (v.channel)
    return estimateChannel(iface, rec, *v.channel, accesses, seq, models,
                           ports.ofArray(op), ports.promotedOf(op));
  if (v.inRegion && config().tool.hls.streams.streamPragmaArrays)
    if (std::optional<StreamHandleRecord> fifo =
            streamPragmaArrayFifo(op, elt, models))
      return estimateStreamFifos(iface, rec, std::move(*fifo));
  if (v.inRegion) {
    PipoRecord p;
    p.notChannelReason = v.notChannelReason;
    rec.pipo = std::move(p);
  }
  return std::nullopt;
}

//===----------------------------------------------------------------------===//
// Post-banking the memref IS one bank: no partition factor, no affine bank-id
// analysis. Geometry comes straight off the shape.
//
// `rec` is filled with the intermediate values of this very computation for the
// debug report; it is never read here, so the estimate does not depend on it.
//
// `banks` are the SSA values that name the storage (the alloca result, or the
// get_global results of an attributed global); `attributed` says whether they
// are all of its accesses (false: a global without --bram-attribute-globals).
/// The resource class one block of `memory` is counted in, for the stdout
/// notes ("BRAM_18K" for a RAMB18).
static std::string unitName(const circt::hlsest::DeviceMemory *memory) {
  if (memory && !memory->cost.items().empty())
    return memory->cost.items().front().first;
  return config().tool.report.primaryMemoryClass;
}

/// The static access profile of a bank from its access summaries: the most
/// loads / stores of one scope.
static circt::hlsest::BankStaticProfile
staticProfile(ArrayRef<AccessSummary> accesses, unsigned width,
              int64_t words) {
  circt::hlsest::BankStaticProfile p;
  p.width = width;
  p.depth = static_cast<unsigned>(std::max<int64_t>(words, 0));
  std::map<Operation *, std::pair<unsigned, unsigned>> perScope;
  for (const AccessSummary &a : accesses) {
    auto &rw = perScope[a.scope];
    (a.isWrite ? rw.second : rw.first)++;
  }
  for (const auto &[scope, rw] : perScope) {
    p.maxReads = std::max(p.maxReads, rw.first);
    p.maxWrites = std::max(p.maxWrites, rw.second);
  }
  return p;
}

// VITIS_NOTES N90 (c), W9r11 review D1: a read-only and a write-only port
// can serve the bank when its one read per iteration lies in one pipelined
// loop with at most II writes per iteration (one write per cycle once spread
// over the II), and every other loop only writes it, at most once per cycle.
// Kernels w9r11rev_sdp_w (1R + 1W at II 1 plus a loop that initialises it)
// and w9r11rev_gd_pre / gd_post (1R + 2W at II 2, plus a loop that writes it
// before / after): 1 BRAM; gd_a / gd_b / gd_e / gd_g (a later loop reads
// it): x18 = 2. Two reads per iteration keep the scheduled per-cycle test
// (onePipelinedScope): fir_filter `fir1` (2R + 2W in hls-est's II 2, Vitis
// II 1) and gemver-medium `u1_buf` (2 reads in a loop, a memcpy loop writes
// it) are x18 in Vitis.
static bool readWriteSplitFits(ArrayRef<AccessSummary> accesses,
                               SeqContext *seq) {
  Operation *readScope = nullptr;
  for (const AccessSummary &a : accesses) {
    if (a.isWrite)
      continue;
    if (readScope && a.scope != readScope)
      return false;
    readScope = a.scope;
  }
  if (!isa_and_present<LoopSchedulePipelineOp>(readScope))
    return false;
  SmallVector<Operation *> scopes;
  for (const AccessSummary &a : accesses)
    if (!llvm::is_contained(scopes, a.scope))
      scopes.push_back(a.scope);
  for (Operation *scope : scopes) {
    SmallVector<const AccessSummary *> group;
    for (const AccessSummary &a : accesses)
      if (a.scope == scope)
        group.push_back(&a);
    if (scope == readScope) {
      unsigned ii = group.front()->ii;
      unsigned reads = llvm::count_if(
          group, [](const AccessSummary *a) { return !a->isWrite; });
      if (ii == 0 || reads != 1 || group.size() - reads > ii)
        return false;
    } else if (scopeDemand(group, seq).writes > 1) {
      return false;
    }
  }
  return true;
}

static BRAMCost estimateBRAM(MemoryResourceOpInterface iface,
                             MemrefRecord &rec, ArrayRef<Value> banks,
                             bool attributed, SeqContext *seq,
                             const Models &models,
                             const InstanceModel *instances,
                             ArrayRef<Value> allSites) {
  const circt::hlsest::MemoryArchitecturePolicy &policy = *models.policy;
  BRAMCost cost;
  cost.kind = StorageKind::RAM_1P;
  cost.label = policy.unpricedLabel(/*readOnly=*/false);
  cost.bramCount = 0;

  // Geometry for the record (safe for any element type; the estimate below
  // reads the same values).
  {
    rec.shape = iface.getStaticShape();
    Type elt = iface.getElementType();
    llvm::raw_string_ostream os(rec.elemType);
    elt.print(os);
    rec.elemBits = elt.isIntOrFloat() ? elt.getIntOrFloatBitWidth()
                  : isa<IndexType>(elt) ? indexElementBits()
                                        : 0u;
    int64_t n = 1;
    bool dynamic = false;
    for (int64_t d : rec.shape) {
      if (ShapedType::isDynamic(d))
        dynamic = true;
      else
        n *= d;
    }
    if (!dynamic)
      rec.words = n;
    rec.accessesAttributed = attributed;
    rec.registerServed.clear();
    for (Value bank : banks)
      for (Operation *user : bank.getUsers()) {
        auto rule = user->getAttrOfType<StringAttr>(
            circt::hls_analysis::kPromotedAccessAttr);
        if (!rule)
          continue;
        bool isWrite = false;
        if (!classifyAccess(user, bank, isWrite))
          continue;
        rec.registerServed.push_back({user->getName().getStringRef().str(),
                                      isWrite ? "write" : "read",
                                      locString(user->getLoc()),
                                      rule.getValue().str()});
      }
  }

  // Pointer variables (memref<memref<...>>), LLVM structs, ...: not an array
  // of words Vitis maps to a RAM, and no element width to price.
  {
    Type elt = iface.getElementType();
    if (!elt.isIntOrFloat() && !isa<IndexType>(elt)) {
      cost.note = "element type " + rec.elemType +
                  " is not an integer / float; not estimated";
      rec.status = "excluded_type";
      rec.excludeReason = cost.note;
      SmallVector<AccessSummary> accesses = collectAccessSummaries(banks, instances);
      recordAccesses(accesses, rec, seq);
      rec.demand = computePortDemand(accesses, seq);
      rec.ramType = cost.label;
      rec.ramReason = "not selected: " + cost.note;
      rec.bram = cost.bramCount;
      return cost;
    }
  }

  // Completely partitioned / scalarised by Vitis (hls.registers, set by
  // --infer-vitis-split-array's automatic partitions, VITIS_NOTES.md N7): no
  // memory at all, whatever its size.
  if (iface.getOperation()->hasAttr(kRegistersAttrName)) {
    std::string why = "automatic complete partition";
    if (auto r = iface.getOperation()->getAttrOfType<StringAttr>(
            kRegistersReasonAttrName))
      why = r.getValue().str();
    cost.note = "hls.registers: " + why + " -> registers, 0 BRAM";
    rec.status = "registers";
    rec.excludeReason = "registers (hls.registers): " + why;
    rec.storageTier = "registers";
    SmallVector<AccessSummary> accesses = collectAccessSummaries(banks, instances);
    recordAccesses(accesses, rec, seq);
    rec.demand = computePortDemand(accesses, seq);
    rec.ramType = "none";
    rec.ramReason = "not selected: registers, no memory (no port limit in "
                    "the schedule)";
    rec.bram = cost.bramCount;
    return cost;
  }

  // The storage the bank goes to (tool.backend.storage_selector). Vitis
  // narrows the element width before it chooses the storage: the selector
  // sees the narrowed width too (an int[64] used only as an index of a
  // 64-word table is 64x6 bits: distributed RAM). A bank whose declared size
  // is already below the block tier is excluded with its declared size.
  unsigned pricedBits = applyNarrowWidth(iface.getOperation(), rec);
  const circt::hlsest::Device &device = config().device;
  SmallVector<AccessSummary> selectionAccesses =
      collectAccessSummaries(banks, instances);
  circt::hlsest::BankStaticProfile profile =
      staticProfile(selectionAccesses, pricedBits, rec.words.value_or(0));
  circt::hlsest::SelectionContext selection;
  selection.profile = attributed ? &profile : nullptr;
  int64_t declaredBits = iface.getStaticSizeInBits();
  auto pragmaKind = iface.getPragmaStorageKind();
  bool pragmaLutram = pragmaKind && *pragmaKind == StorageKind::LUTRAM;
  circt::hlsest::TierChoice choice;
  if (!pragmaLutram && declaredBits != 0) {
    circt::hlsest::MemoryRequest declared;
    declared.words = rec.words.value_or(0);
    declared.writeWidth = rec.elemBits;
    declared.readWidths.push_back(rec.elemBits);
    declared.pragmaImpl =
        circt::hls_analysis::bindStorageImpl(iface.getOperation());
    choice = models.selector->select(declared, device, selection);
    if (!choice.memory.empty() && rec.narrow && rec.words) {
      circt::hlsest::MemoryRequest narrowed = declared;
      narrowed.writeWidth = pricedBits;
      narrowed.readWidths = {pricedBits};
      narrowed.narrowed = true;
      choice = models.selector->select(narrowed, device, selection);
    }
  }
  // The tier the scheduling pass chose before it scheduled the bank
  // (hls.storage_tier, --convert-affine-to-loopschedule) wins, so that the
  // bank is priced in the memory it was scheduled for.
  if (auto recorded =
          iface.getOperation()->getAttrOfType<StringAttr>("hls.storage_tier"))
    if (recorded.getValue() != choice.tier && !pragmaLutram &&
        declaredBits != 0) {
      choice.tier = recorded.getValue().str();
      choice.memory.clear();
      if (choice.tier != config().tool.backend.storageSelector.below)
        for (const circt::hlsest::DeviceMemory &m : device.memories)
          if (m.tier == choice.tier) {
            choice.memory = m.id;
            break;
          }
      if (choice.memory.empty())
        choice.note = "storage tier " + choice.tier +
                      " chosen before scheduling (hls.storage_tier): not "
                      "priced";
    }
  rec.storageTier = choice.tier;
  if (pragmaLutram || declaredBits == 0 || choice.memory.empty()) {
    cost.note = "excluded from BRAM accounting (LUTRAM / stream / zero-size)";
    // Explain which exclusion rule fired.
    if (pragmaLutram) {
      rec.status = "excluded_small";
      rec.excludeReason = "pragma storage kind LUTRAM; not BRAM-backed";
    } else if (declaredBits == 0 && !rec.words) {
      // A dynamic extent makes the static size 0; report it as what it is.
      rec.status = "dynamic_shape";
      rec.excludeReason = "dynamic shape; static size unknown; not estimated";
    } else if (declaredBits == 0) {
      rec.status = "zero_size";
      rec.excludeReason = "zero-size array (0 bits)";
    } else {
      rec.status = "excluded_small";
      rec.excludeReason = choice.note;
    }
    // Still describe the accesses: useful when diagnosing a Vitis mismatch on
    // a small array, and it does not touch the estimate.
    SmallVector<AccessSummary> accesses = std::move(selectionAccesses);
    recordAccesses(accesses, rec, seq);
    rec.demand = computePortDemand(accesses, seq);
    rec.replication = policy.replication(accesses, rec.accessesAttributed);
    rec.ramType = cost.label;
    rec.ramReason = "not selected: " + cost.note;
    rec.bram = cost.bramCount;
    return cost;
  }
  const circt::hlsest::DeviceMemory *memory = device.memory(choice.memory);
  rec.memoryId = choice.memory;

  // --- Bank geometry ---
  auto shape = iface.getStaticShape();
  int64_t numElems = 1;
  for (int64_t dim : shape) {
    if (ShapedType::isDynamic(dim)) {
      cost.note = "dynamic shape; not estimated";
      rec.status = "dynamic_shape";
      rec.excludeReason = cost.note;
      rec.ramType = cost.label;
      rec.ramReason = "not selected: " + cost.note;
      rec.bram = cost.bramCount;
      return cost;
    }
    numElems *= dim;
  }
  unsigned elemBits = pricedBits; // int/float width (narrowed); index: index_bits
  if (numElems == 0 || elemBits == 0 || !memory) {
    cost.note = "zero-size";
    rec.status = "zero_size";
    rec.excludeReason = cost.note;
    rec.ramType = cost.label;
    rec.ramReason = "not selected: " + cost.note;
    rec.bram = cost.bramCount;
    return cost;
  }
  // --- Port contention -> plan ---
  SmallVector<AccessSummary> accesses = std::move(selectionAccesses);
  PortDemand demand = computePortDemand(accesses, seq);
  ReplicationRecord rep = policy.replication(accesses, rec.accessesAttributed);
  // Once a pipelined loop makes the bank a RAM_1WNR, the owner's sequential
  // code binds its loads to the copies and starts the independent ones of a
  // straight-line stretch in one state: copies = max(the loops' count, reads
  // in one state - 1) (VITIS_NOTES N164: kernels w9r22p_a2_r3_tail /
  // a2_r3_head 3 copies; a2_r3_tail1, one sequential read, and a2_r2_tail, a
  // plain 2-port RAM, unchanged; the state count is N93's rule for ROMs).
  if (rep.copies > 1 && config()
                            .tool.hls.memoryArchitecture.replication
                            .sequentialStateReads)
    if (unsigned n = sequentialRomReads(accesses, seq, policy); n > 2) {
      unsigned cap = static_cast<unsigned>(std::max<int64_t>(
          1, config().tool.hls.memoryArchitecture.replication.maxCopies));
      unsigned copies = std::min(n - 1, cap);
      if (copies > rep.copies) {
        ReplicationLoopRecord lr;
        lr.scopeLoc = "sequential state";
        lr.reads = n;
        lr.need = n;
        lr.copies = copies;
        rep.loops.push_back(lr);
        rep.copies = copies;
        rep.limitingLoop = lr.scopeLoc;
      }
    }
  int64_t blocks;
  // An initialised global that is attributed and never written is a ROM:
  // `constant`, or (what cgeist emits for `static const T t[] = {...}`: a
  // private global with a dense initial value and no `constant`) no get_global
  // site or view of one is written or escapes (Vitis 2025.1 rom2r_int: a
  // 512x32 table read twice per cycle is `tbl_ROM_AUTO_1R`, 1 BRAM). How a
  // ROM is built from its reads per cycle is the policy's (vitis-auto: one
  // simple-dual-port memory up to two reads, ceil(n / 2) copies beyond).
  auto global = dyn_cast<memref::GlobalOp>(iface.getOperation());
  // Not only with --bram-attribute-globals: a constant table is a ROM
  // whatever reads it, and its reads are its ports (N26 tables).
  bool initRom = global && !global.isExternal() &&
                 !global.isUninitialized() &&
                 (global.getConstant() || neverWritten(allSites));
  // N26: the element width of the ROM - from the dense initial value of an
  // initialised global, or from the constants every write stores (a filled
  // ROM: an array --mark-constant-fills marked, read somewhere; also a global
  // whose accesses are not attributed).
  std::optional<unsigned> romBits;
  bool fillRom = false;
  Type eltTy = iface.getElementType();
  SmallVector<AccessSummary> romAccesses =
      attributed ? accesses : collectAccessSummaries(allSites, instances);
  if (!initRom)
    if (auto mark = iface->getAttrOfType<IntegerAttr>("hls.const_fill")) {
      bool anyRead = llvm::any_of(
          romAccesses, [](const AccessSummary &a) { return !a.isWrite; });
      bool anyWrite = llvm::any_of(
          romAccesses, [](const AccessSummary &a) { return a.isWrite; });
      fillRom = anyRead && anyWrite;
      if (fillRom)
        romBits = static_cast<unsigned>(mark.getInt());
    }
  if (initRom && eltTy.isInteger())
    if (auto d = dyn_cast_or_null<DenseIntElementsAttr>(
            global.getInitialValueAttr())) {
      SmallVector<APInt> vals(d.getValues<APInt>().begin(),
                              d.getValues<APInt>().end());
      romBits = narrowRomWidth(vals);
    }
  rec.rom = initRom || fillRom;
  circt::hlsest::MemoryRequest request;
  request.words = numElems;
  request.writeWidth = elemBits;
  request.readWidths.push_back(elemBits);
  request.narrowed = rec.narrow.has_value();
  request.pragmaType =
      circt::hls_analysis::bindStorageType(iface.getOperation());
  if (rec.rom) {
    // A filled ROM is read only: its writes become the initial value.
    if (fillRom || !attributed) {
      SmallVector<AccessSummary> reads;
      for (const AccessSummary &a : romAccesses)
        if (!a.isWrite)
          reads.push_back(a);
      accesses = std::move(reads);
      rec.accessesAttributed = true;
      demand = computePortDemand(accesses, seq);
      rep = policy.replication(accesses, true);
    }
    // A ROM has its own width rule (the values it holds).
    rec.narrow.reset();
    elemBits = rec.elemBits;
    unsigned declaredBits = elemBits;
    std::string widthNote;
    if (romBits) {
      unsigned w = *romBits;
      widthNote = "; element width " + std::to_string(w) + " of " +
                  std::to_string(declaredBits) +
                  " bits from its values (N26)";
      if (w == 0) {
        cost.kind = StorageKind::ROM_1P;
        cost.label = policy.unpricedLabel(/*readOnly=*/true);
        cost.bramCount = 0;
        cost.note = std::to_string(numElems) + "x" +
                    std::to_string(declaredBits) +
                    "b ROM whose values are all 0: no memory (N1a, N26)";
        recordAccesses(accesses, rec, seq);
        rec.demand = demand;
        rec.status = "zero_rom";
        rec.excludeReason = cost.note;
        rec.memoryId.clear();
        rec.ramType = "none";
        rec.ramReason = "not selected: " + cost.note;
        rec.bram = 0;
        return cost;
      }
      elemBits = w;
      circt::hlsest::MemoryRequest romRequest;
      romRequest.words = numElems;
      romRequest.writeWidth = w;
      romRequest.readWidths.push_back(w);
      romRequest.readOnly = true;
      romRequest.needsInit = true;
      romRequest.pragmaImpl =
          circt::hls_analysis::bindStorageImpl(iface.getOperation());
      circt::hlsest::TierChoice romChoice =
          models.selector->select(romRequest, device, selection);
      if (romChoice.memory.empty()) {
        const circt::hlsest::StorageSelectorConfig &sel =
            config().tool.backend.storageSelector;
        cost.kind = StorageKind::ROM_1P;
        cost.label = policy.unpricedLabel(/*readOnly=*/true);
        cost.bramCount = 0;
        // The builtin threshold's words when it is the reason; otherwise
        // the selector that kept the ROM out of the priced memories.
        std::string why =
            sel.belowBlock(numElems * static_cast<int64_t>(w))
                ? std::string(sel.belowSymbol()) + " " +
                      std::to_string(sel.minBlockBits) + " bits"
                : "kept in tier " + romChoice.tier + " by storage selector '" +
                      models.selector->name().str() + "'";
        cost.note = std::to_string(numElems) + "x" + std::to_string(w) +
                    "b ROM (narrowed from " + std::to_string(declaredBits) +
                    " bits, N26) " + why + ": distributed ROM, 0 BRAM";
        recordAccesses(accesses, rec, seq);
        rec.demand = demand;
        rec.status = "excluded_small";
        rec.excludeReason = cost.note;
        rec.storageTier = romChoice.tier;
        rec.memoryId.clear();
        rec.ramType = cost.label;
        rec.ramReason = "not selected: " + cost.note;
        rec.bram = 0;
        return cost;
      }
    }
    request.words = numElems;
    request.writeWidth = elemBits;
    request.readWidths = {elemBits};
    request.readOnly = true;
    request.needsInit = true;
    request.narrowed = false;
    // The reads of a function pipeline (N144) are spread over its II's
    // slots; the sequential state rule below covers the other scopes.
    ArrayRef<AccessSummary> stateRuleAccesses = accesses;
    SmallVector<AccessSummary> otherScopes;
    if (unsigned n = functionPipelineRomReads(accesses, seq, otherScopes)) {
      demand = computePortDemand(otherScopes, seq);
      demand.reads = std::max(demand.reads, n);
      demand.total = std::max(demand.total, n);
      stateRuleAccesses = otherScopes;
    }
    // Independent reads of one state of a sequential scope (N93).
    if (unsigned n = sequentialRomReads(stateRuleAccesses, seq, policy);
        n > demand.total) {
      demand.reads = demand.total = n;
    }
    circt::hlsest::PlanContext ctx;
    ctx.attributed = true;
    circt::hlsest::MemoryPlan plan = policy.plan(demand, rep, request, ctx);
    if (plan.copies > 1) {
      int64_t perCopy = mapBlocks(*models.mapper, *memory, plan.pricedConfig,
                                  numElems, elemBits, &rec.bankMath);
      blocks = perCopy * plan.copies;
      rec.bankMath.replication = plan.copies;
      rec.bankMath.blocks = blocks;
    } else {
      blocks = mapBlocks(*models.mapper, *memory, plan.pricedConfig, numElems,
                         elemBits, &rec.bankMath);
    }
    cost.label = plan.label;
    cost.bramCount = static_cast<unsigned>(blocks);
    const char *what = fillRom ? "b array written only with constants -> "
                       : global.getConstant()
                           ? "b constant global -> "
                           : "b initialised global, never written -> ";
    cost.note = std::to_string(numElems) + "x" + std::to_string(elemBits) +
                what + plan.label + " (" + std::to_string(plan.romReads) +
                " read port(s)/cycle) = " + std::to_string(blocks) + " " +
                unitName(memory);
    recordAccesses(accesses, rec, seq);
    rec.demand = demand;
    rec.replication = rep;
    rec.status = "counted";
    rec.ramType = plan.label;
    rec.ramReason =
        std::string(fillRom
                        ? "every write stores a constant (ROM of those "
                          "values, N26)"
                    : global.getConstant()
                        ? "constant-initialised global (ROM, never written)"
                        : "initialised global that no get_global site writes "
                          "(ROM)") +
        widthNote + plan.reason;
    rec.bram = cost.bramCount;
    return cost;
  }
  // The kind, the copies and the priced configuration
  // (tool.hls.memory_architecture: vitis-auto).
  recordAccesses(accesses, rec, seq);
  circt::hlsest::PlanContext ctx;
  ctx.attributed = rec.accessesAttributed;
  ctx.anyStoreEnable = llvm::any_of(
      rec.accesses, [](const AccessRecord &a) { return a.storeEnable; });
  // One pipelined loop holds every access (VITIS_NOTES N90 (c), w9r11i_gd_f
  // / gd_h), or the reads only (readWriteSplitFits).
  ctx.onePipelinedScope =
      !accesses.empty() && isa_and_present<LoopSchedulePipelineOp>(
                               accesses.front().scope) &&
      llvm::all_of(accesses, [&](const AccessSummary &a) {
        return a.scope == accesses.front().scope;
      });
  ctx.readWriteSplit = readWriteSplitFits(accesses, seq);
  // The banks have no other user (a pointer cast for an unrolled memcpy, a
  // view, a call) that may access them elsewhere.
  if (ctx.onePipelinedScope || ctx.readWriteSplit) {
    DenseSet<Operation *> accessOps;
    for (const AccessSummary &a : accesses)
      accessOps.insert(a.op);
    for (Value bank : banks)
      for (Operation *user : bank.getUsers())
        if (!accessOps.contains(user) && !isa<memref::DeallocOp>(user) &&
            !circt::hls_analysis::isPromotedAccess(user))
          ctx.onePipelinedScope = ctx.readWriteSplit = false;
  }
  circt::hlsest::MemoryPlan plan = policy.plan(demand, rep, request, ctx);
  if (!memory->portConfig(plan.pricedConfig)) {
    // A policy that prices the bank at a configuration the chosen memory
    // lacks (a two-port bank in a one-port memory): the run fails, naming the
    // bank, rather than pricing it with another memory's numbers.
    iface->emitError("--bram-analysis: the memory architecture policy prices "
                     "this bank at port configuration '")
        << plan.pricedConfig << "', which memory '" << memory->id
        << "' (tier " << memory->tier << ") does not have";
    plan.infeasible = true;
    models.failed = true;
  }
  if (plan.copies > 1) {
    int64_t perCopy = mapBlocks(*models.mapper, *memory, plan.pricedConfig,
                                numElems, elemBits, &rec.bankMath);
    blocks = perCopy * plan.copies;
    rec.bankMath.replication = plan.copies;
    rec.bankMath.blocks = blocks;
  } else {
    blocks = mapBlocks(*models.mapper, *memory, plan.pricedConfig, numElems,
                       elemBits, &rec.bankMath);
  }
  cost.label = plan.label;
  cost.infeasible = plan.infeasible;
  cost.bramCount = static_cast<unsigned>(blocks);
  if (!plan.note.empty())
    cost.note = plan.note + " => " + std::to_string(blocks) + " BRAM";
  else if (plan.copies > 1)
    cost.note = std::to_string(numElems) + "x" + std::to_string(elemBits) +
                "b -> " + plan.label + ", " + std::to_string(plan.copies) +
                " copies x " + std::to_string(rec.bankMath.blocksPerCopy) +
                " (x" + std::to_string(usedPortWidth(rec.bankMath)) +
                "/port) = " + std::to_string(blocks) + " " + unitName(memory);
  else
    cost.note = std::to_string(numElems) + "x" + std::to_string(elemBits) +
                "b -> " + plan.label + " (x" +
                std::to_string(usedPortWidth(rec.bankMath)) + "/port) = " +
                std::to_string(blocks) + " " + unitName(memory);

  // --- Record ---
  rec.demand = demand;
  rec.replication = rep;
  rec.status = plan.infeasible ? "infeasible" : "counted";
  rec.ramType = plan.label;
  rec.ramReason = plan.reason;
  rec.bram = cost.bramCount;
  rec.infeasible = cost.infeasible;
  return cost;
}

//===----------------------------------------------------------------------===//
// Debug printers.
//===----------------------------------------------------------------------===//

static std::string shapeString(ArrayRef<int64_t> shape) {
  std::string s = "[";
  for (size_t i = 0; i < shape.size(); ++i) {
    if (i)
      s += "x";
    s += ShapedType::isDynamic(shape[i]) ? "?" : std::to_string(shape[i]);
  }
  return s + "]";
}

static std::string displayName(const MemrefRecord &r) {
  std::string n = r.varname ? *r.varname
                  : r.name  ? *r.name
                            : std::string("<unnamed>");
  if (r.partition.applied && r.partition.bankIndex && r.partition.bankCount)
    n += "[bank " + std::to_string(*r.partition.bankIndex) + "/" +
         std::to_string(*r.partition.bankCount) + "]";
  return n;
}

static SmallVector<const MemrefRecord *>
sortedByBram(ArrayRef<MemrefRecord> records) {
  SmallVector<const MemrefRecord *> order;
  for (const MemrefRecord &r : records)
    order.push_back(&r);
  llvm::stable_sort(order, [](const MemrefRecord *a, const MemrefRecord *b) {
    if (a->bram != b->bram)
      return a->bram > b->bram;
    return a->id < b->id;
  });
  return order;
}

// The pipeline / unroll / flatten decisions --auto-pipeline-unroll recorded
// on each pipelined loop (carried onto the loopschedule.pipeline op by
// --convert-affine-to-loopschedule). Read-only: the estimate never looks at
// them. `loc` is the same string as the per-scope `scope_loc` of the memref
// records, so the two can be joined.
struct PipelineRecord {
  std::string loc;
  std::string func;
  unsigned ii = 0;
  std::optional<int64_t> tripCount;
  // "auto" (tagged by --auto-pipeline-unroll), "user" (a source pragma) or
  // "innermost" (no tag: the conversion's default of pipelining every
  // innermost loop).
  std::string source = "innermost";
  unsigned flattenedParents = 0;      // hls.flattened_parents
  std::optional<int64_t> unrollPartial; // hls.unroll_partial (user factor)
  // hls.unroll_runtime_guarded: the partial user unroll of a run-time-trip
  // loop, as guarded copies (VITIS_NOTES N103).
  bool unrollRuntimeGuarded = false;
  // Accesses and calls moved in from after a flattened parent's child loop
  // (hls.sunk_trailing_code, VITIS_NOTES N97 (b)).
  int64_t sunkTrailingOps = 0;
  // hls.scheduler: the modulo scheduler that produced the schedule ("simplex",
  // "greedy", or either with the other's failure noted; OPEN_ISSUES O9).
  std::string scheduler;
  struct Unrolled {
    std::string loc;
    int64_t factor = 0;
  };
  SmallVector<Unrolled> unrolled; // hls.auto_unrolled, in unroll order
  // hls.memory_recurrence: the memory recurrence that bounds the II
  // (VITIS_NOTES N87): ii, distance, chain, rule, load, store.
  DictionaryAttr memoryRecurrence;
  // hls.folded_guards / hls.pinned_guard_operands (VITIS_NOTES N89): ifs of
  // the loop's unrolled copies that were decided, operands an equality fixed.
  int64_t foldedGuards = 0;
  int64_t pinnedGuardOperands = 0;
  // hls.port_bank / hls.port_banks (VITIS_NOTES N88): accesses of a
  // partitioned function argument per bank pool, "arg<N> bank <b>" or
  // "arg<N> any of <n>" -> count.
  std::map<std::string, int64_t> argumentBankPorts;
};

// The memref an access op reads or writes (null for any other op).
static Value accessedMemrefOf(Operation *op, bool &isLoad) {
  isLoad = isa<memref::LoadOp, affine::AffineLoadOp>(op);
  if (auto l = dyn_cast<memref::LoadOp>(op))
    return l.getMemRef();
  if (auto l = dyn_cast<affine::AffineLoadOp>(op))
    return l.getMemRef();
  if (auto s = dyn_cast<memref::StoreOp>(op))
    return s.getMemRef();
  if (auto s = dyn_cast<affine::AffineStoreOp>(op))
    return s.getMemRef();
  if (auto s = dyn_cast<circt::hls_analysis::StoreEnableOp>(op))
    return s.getMemref();
  return Value();
}

// With top= only the pipelines of the reachable functions (TopScope::covers),
// as the --symbol-privatize / --symbol-dce prefix leaves them.
static std::vector<PipelineRecord>
collectPipelineRecords(ModuleOp module, const TopScope &scope) {
  std::vector<PipelineRecord> out;
  module.walk([&](LoopSchedulePipelineOp p) {
    if (!scope.covers(p))
      return;
    PipelineRecord r;
    r.loc = locString(p.getLoc());
    if (auto fn = p->getParentOfType<func::FuncOp>())
      r.func = fn.getName().str();
    r.ii = static_cast<unsigned>(p.getII());
    if (auto tc = p.getTripCount())
      r.tripCount = static_cast<int64_t>(*tc);
    if (Attribute tag = p->getAttr(kLoopPipelineAttr)) {
      r.source = "user";
      if (auto arr = dyn_cast<ArrayAttr>(tag))
        tag = arr.empty() ? Attribute() : arr[0];
      if (auto dict = dyn_cast_or_null<DictionaryAttr>(tag))
        if (auto s = dict.getAs<StringAttr>("source"))
          r.source = s.getValue().str();
    }
    if (auto fp = p->getAttrOfType<IntegerAttr>(kLoopFlattenedParentsAttr))
      if (fp.getInt() > 0)
        r.flattenedParents = static_cast<unsigned>(fp.getInt());
    if (auto up = p->getAttrOfType<IntegerAttr>(kLoopUnrollPartialAttr))
      r.unrollPartial = up.getInt();
    r.unrollRuntimeGuarded =
        p->hasAttr(circt::hls_analysis::kLoopUnrollRuntimeGuardedAttr);
    p->walk([&](Operation *op) {
      if (op->hasAttr(circt::hls_analysis::kSunkTrailingCodeAttr))
        ++r.sunkTrailingOps;
    });
    if (auto s = p->getAttrOfType<StringAttr>(kLoopSchedulerAttr))
      r.scheduler = s.getValue().str();
    r.memoryRecurrence =
        p->getAttrOfType<DictionaryAttr>("hls.memory_recurrence");
    if (auto f = p->getAttrOfType<IntegerAttr>(
            circt::hls_analysis::kFoldedGuardsAttr))
      r.foldedGuards = f.getInt();
    if (auto f = p->getAttrOfType<IntegerAttr>(
            circt::hls_analysis::kPinnedGuardOperandsAttr))
      r.pinnedGuardOperands = f.getInt();
    p->walk([&](Operation *op) {
      auto bank = op->getAttrOfType<IntegerAttr>("hls.port_bank");
      auto banks = op->getAttrOfType<IntegerAttr>("hls.port_banks");
      if (!bank && !banks)
        return;
      bool isLoad = false;
      Value mem = accessedMemrefOf(op, isLoad);
      auto arg = dyn_cast_or_null<BlockArgument>(mem);
      std::string key = arg ? "arg" + std::to_string(arg.getArgNumber())
                            : std::string("?");
      key += bank ? " bank " + std::to_string(bank.getInt())
                  : " any of " + std::to_string(banks.getInt());
      ++r.argumentBankPorts[key];
    });
    if (auto arr = p->getAttrOfType<ArrayAttr>(kLoopAutoUnrolledAttr))
      for (Attribute a : arr) {
        auto dict = dyn_cast<DictionaryAttr>(a);
        if (!dict)
          continue;
        PipelineRecord::Unrolled u;
        if (auto f = dict.getAs<IntegerAttr>("factor"))
          u.factor = f.getInt();
        if (auto l = dict.getAs<LocationAttr>("loc"))
          u.loc = locString(l);
        r.unrolled.push_back(std::move(u));
      }
    out.push_back(std::move(r));
  });
  return out;
}

// What --vitis-fold rewrote (module attribute `hls.vitis_fold`, written by
// VitisFold.cpp): counts per rule and the first records. Debug output only.
struct FoldSummary {
  struct Rewrite {
    std::string rule, loc, source, detail, func;
  };
  SmallVector<std::pair<std::string, int64_t>> counts;
  SmallVector<Rewrite> rewrites;
  bool present = false;
  // top= is given but the attribute has no per-function counts (written by an
  // --vitis-fold older than the W1a review fixes): the summary is the whole
  // module's.
  bool wholeModule = false;
};

// With top= only the rewrites inside the reachable functions: the counts are
// summed from `func_counts` over them and a record is kept when its `func` is
// one of them, as the --symbol-privatize / --symbol-dce prefix would leave it.
static FoldSummary collectFoldSummary(ModuleOp module, const TopScope &scope) {
  FoldSummary s;
  auto d = module->getAttrOfType<DictionaryAttr>("hls.vitis_fold");
  if (!d)
    return s;
  s.present = true;
  auto funcCounts = d.getAs<DictionaryAttr>("func_counts");
  bool scoped = scope.active() && funcCounts;
  s.wholeModule = scope.active() && !funcCounts;
  if (scoped) {
    std::map<std::string, int64_t> sums; // by rule name, like `counts`
    for (NamedAttribute f : funcCounts) {
      auto per = dyn_cast<DictionaryAttr>(f.getValue());
      if (!per || !scope.funcNames.contains(f.getName().getValue()))
        continue;
      for (NamedAttribute na : per)
        if (auto i = dyn_cast<IntegerAttr>(na.getValue()))
          sums[na.getName().str()] += i.getInt();
    }
    s.counts.assign(sums.begin(), sums.end());
  } else if (auto c = d.getAs<DictionaryAttr>("counts")) {
    for (NamedAttribute na : c)
      if (auto i = dyn_cast<IntegerAttr>(na.getValue()))
        s.counts.push_back({na.getName().str(), i.getInt()});
  }
  if (auto r = d.getAs<ArrayAttr>("rewrites"))
    for (Attribute a : r) {
      auto rd = dyn_cast<DictionaryAttr>(a);
      if (!rd)
        continue;
      if (scoped) {
        auto fn = rd.getAs<StringAttr>("func");
        if (!fn || !scope.funcNames.contains(fn.getValue()))
          continue;
      }
      FoldSummary::Rewrite w;
      if (auto x = rd.getAs<StringAttr>("rule"))
        w.rule = x.str();
      if (auto x = rd.getAs<LocationAttr>("loc"))
        w.loc = locString(Location(x));
      if (auto x = rd.getAs<LocationAttr>("source"))
        w.source = locString(Location(x));
      if (auto x = rd.getAs<StringAttr>("detail"))
        w.detail = x.str();
      if (auto x = rd.getAs<StringAttr>("func"))
        w.func = x.str();
      s.rewrites.push_back(std::move(w));
    }
  return s;
}

static void printFoldSummary(const FoldSummary &f, llvm::raw_ostream &os) {
  if (!f.present)
    return;
  int64_t n = 0;
  for (auto &c : f.counts)
    n += c.second;
  os << "--- vitis-fold: " << n
     << " rewrites of the undefined value of an integer x / 0 "
        "(VITIS_NOTES.md N13) ---\n";
  if (f.wholeModule)
    os << "  (whole module: this hls.vitis_fold has no per-function counts, "
          "so top= does not narrow it)\n";
  os << "  counts:";
  for (auto &c : f.counts)
    os << " " << c.first << "=" << c.second;
  os << "\n";
  for (const FoldSummary::Rewrite &w : f.rewrites) {
    os << "  " << w.rule << " @ " << w.loc;
    if (!w.detail.empty())
      os << " (" << w.detail << ")";
    // The uniform-table fold (N52) names the table it read, the undef rules
    // the division that produced U (N13).
    os << (w.rule == "uniform-table-load" ? "; table @ "
                                          : "; undefined value from @ ")
       << w.source << "\n";
  }
  if (static_cast<int64_t>(f.rewrites.size()) < n)
    os << "  ... " << (n - static_cast<int64_t>(f.rewrites.size()))
       << " more not recorded\n";
}

static void printDebugText(ArrayRef<MemrefRecord> records,
                           ArrayRef<PipelineRecord> pipelines,
                           ArrayRef<InstanceRecord> instances, int64_t total,
                           const FoldSummary &fold,
                           const circt::hlsest::MemoryMapper &mapper,
                           const TopScope &scope, llvm::raw_ostream &os) {
  os << "=== bram-debug: how each BRAM number was derived ===\n";
  os << "bram formula: " << mapper.reportLabel() << " ("
     << mapper.reportDescription() << ")\n";
  // Only a configuration other than the compiled-in defaults is named, so
  // that the default report stays as it was.
  if (!config().isDefault()) {
    const Config &cfg = config();
    os << "configuration: " << cfg.hash << " (device " << cfg.device.id
       << ", tool " << cfg.tool.id << "; " << cfg.overrides.size()
       << " key(s) differ from the defaults:";
    for (const circt::hlsest::ConfigOverride &o : cfg.overrides) {
      std::string v;
      llvm::raw_string_ostream vs(v);
      vs << o.value;
      os << " " << o.path << "=" << v;
    }
    os << ")\n";
  }
  if (scope.active())
    os << "top: @" << scope.symbol << " (" << scope.funcs.size()
       << " function(s) reachable through calls; " << scope.skipped
       << " memref(s) outside them not costed)\n";
  else
    os << "top: none (every function is costed)\n";
  for (const MemrefRecord &r : records) {
    if (r.math) {
      os << "[" << r.id << "] math core '" << r.math->coreName << "' ("
         << r.kind << ") in @" << (r.func ? *r.func : "?") << " @ "
         << r.locText << "\n";
      printMathCoreText(*r.math, os);
      os << "  bram: " << r.bram << "\n";
      continue;
    }
    if (r.adapter) {
      const AdapterRecord &a = *r.adapter;
      os << "[" << r.id << "] m_axi bundle '" << a.bundle << "' ("
         << r.kind << ") in @" << (r.func ? *r.func : "?") << " @ "
         << r.locText << "\n";
      os << "  ports:";
      for (const std::string &p : a.ports)
        os << " " << p;
      os << "; bus width max(32, element bits) = " << a.busBits << "\n";
      os << "  read FIFO: " << (a.hasRead ? "used" : "no load from the bundle")
         << ", max_read_burst_length " << a.readBurst
         << " x num_read_outstanding " << a.readOutstanding << " = depth "
         << a.readDepth << " -> " << a.readBram << " BRAM (" << a.readRule
         << ")\n";
      os << "  write buffer: " << (a.hasWrite ? "used" : "no store to the bundle")
         << ", max_write_burst_length " << a.writeBurst
         << " (num_write_outstanding " << a.writeOutstanding
         << " has no effect) -> " << a.writeBram << " BRAM (" << a.writeRule
         << ")\n";
      if (a.unresolvedCall)
        os << "  note: an argument of the bundle is passed to a call without "
              "a body in the module; assumed read and written\n";
      else if (a.passedToCall)
        os << "  note: an argument of the bundle is passed to a call; its "
              "accesses in the callee are counted\n";
      os << "  bram: " << r.bram << "\n";
      continue;
    }
    os << "[" << r.id << "] " << displayName(r) << " (" << r.kind;
    if (r.name && r.varname)
      os << " @" << *r.name;
    os << ") @ " << r.locText << "\n";
    if (r.fromGlobal)
      os << "  promoted from memref.global @" << *r.fromGlobal
         << " (--promote-globals-to-allocas)\n";
    if (r.structMember)
      os << "  struct array split: " << *r.structMember
         << " (--split-struct-memrefs)\n";
    if (r.aggregated)
      os << "  struct variable " << *r.aggregated
         << " (--split-struct-memrefs)\n";
    os << "  shape " << shapeString(r.shape) << " x " << r.elemType << " ("
       << r.elemBits << " bits)";
    if (r.words)
      os << " = " << *r.words << " words";
    os << "\n";
    if (r.narrow)
      os << "  narrowed width: " << r.narrow->bits << " of "
         << r.narrow->declaredBits << " bits (" << r.narrow->reason << ")\n";
    os << "  status: " << r.status;
    if (r.excludeReason)
      os << " -- " << *r.excludeReason;
    os << "\n";
    if (r.status == "eliminated_dead") {
      os << "  bram: 0\n";
      continue;
    }
    if (r.fifo) {
      const StreamHandleRecord &f = *r.fifo;
      os << "  hls::stream storage (not a RAM): " << f.fifos
         << " FIFO(s); methods:";
      for (const std::string &m : f.methods)
        os << " " << m;
      os << "\n";
      for (const FifoGroup &g : f.groups) {
        os << "  fifo: " << g.count << " x ";
        if (g.member)
          os << "member " << *g.member << " ";
        os << "depth " << g.depth << " (" << g.depthSource << ") x "
           << g.bits << " bits (" << g.bitsSource << ") -> " << g.bramEach
           << " each: " << g.reason << " (count: " << g.countSource
           << ")\n";
      }
      if (!f.note.empty())
        os << "  note: " << f.note << "\n";
      if (r.instances != 1)
        os << "  instances: " << r.instances << " x " << r.bramPerInstance
           << "\n";
      os << "  bram: " << r.bram << "\n";
      continue;
    }
    if (r.pipo) {
      const PipoRecord &pp = *r.pipo;
      if (!pp.channel) {
        os << "  dataflow region array, not a ping-pong channel: "
           << pp.notChannelReason << "\n";
      } else {
        os << "  dataflow ping-pong channel of " << pp.regionKind << " "
           << pp.region << "\n";
        for (const DataflowProcess &dp : pp.processes) {
          os << "    process " << dp.position << " ("
             << (dp.writes && dp.reads ? "writes, reads"
                 : dp.writes           ? "writes"
                                       : "reads")
             << "): " << dp.name << "\n";
          if (!dp.group.empty())
            os << "      merged into the process of " << dp.group << " ("
               << dp.mergeReason << ")\n";
        }
        os << "  blocks: " << pp.blocksSource << "\n";
        if (!pp.bindType.empty() || !pp.bindImpl.empty())
          os << "  bind_storage: type=" << pp.bindType
             << " impl=" << pp.bindImpl << "\n";
        os << "  mode: " << pp.mode << " (" << pp.modeReason << ")\n"
           << "  pipo price: " << pp.rule << "\n";
      }
    }
    if (r.keptReason)
      os << "  " << *r.keptReason << "\n";
    if (r.partition.present) {
      const PartitionRecord &p = r.partition;
      os << "  partition: " << p.kind << " factor=" << p.factor
         << " dim=" << p.dim << " source=" << p.source;
      if (!p.dims.empty()) {
        os << " dims=[";
        llvm::interleaveComma(p.dims, os, [&](const auto &t) {
          os << std::get<0>(t) << " " << std::get<1>(t) << " on dim "
             << std::get<2>(t);
        });
        os << "]";
      }
      if (p.from)
        os << " from " << *p.from;
      if (p.applied) {
        os << " (bank";
        if (p.bankIndex)
          os << " " << *p.bankIndex;
        if (p.bankCount)
          os << " of " << *p.bankCount;
        os << ")";
      } else {
        os << " (spec present, not banked)";
      }
      if (p.reason)
        os << "\n    reason: " << *p.reason;
      os << "\n";
    } else {
      os << "  partition: none\n";
    }
    if (!r.accessesAttributed) {
      os << "  accesses: not attributed (memref.global has no SSA result)\n";
    } else {
      os << "  accesses (" << r.accesses.size() << "):\n";
      for (const AccessRecord &a : r.accesses) {
        os << "    - " << a.op << " " << (a.isWrite ? "write" : "read ")
           << " in " << a.scopeKind << " @ " << a.scopeLoc;
        if (a.scopeKind == "pipeline")
          os << " ii=" << a.ii << " stage=" << a.stageStart;
        if (a.viaCall)
          os << " (in @" << a.inFunc << " via " << *a.viaCall
             << (a.portBound ? ", port-bound" : "") << ")";
        if (a.storeEnable)
          os << " (store_enable: write-only, no read port)";
        if (a.mergedLoads)
          os << " (+" << a.mergedLoads
             << " same-address load(s) merged into it: CSE)";
        if (a.forwardedLoads || a.removedStores) {
          os << " (absorbed";
          if (a.forwardedLoads)
            os << " " << a.forwardedLoads << " forwarded load(s)";
          if (a.removedStores)
            os << (a.forwardedLoads ? "," : "") << " " << a.removedStores
               << " dead store(s)";
          os << ")";
        }
        if (a.mergedIfElseStores)
          os << " (stands for the same-address stores of both arms of an "
                "if/else: one store)";
        if (a.hoistedConditional)
          os << " (loop-invariant load hoisted out of an if of the loop "
                "body)";
        if (!a.portBank.empty())
          os << " (ports of argument bank " << a.portBank << ", N88)";
        os << "\n";
      }
      for (const MemrefRecord::RegisterServed &x : r.registerServed)
        os << "    served by a register (" << x.rule << "): " << x.op << " ("
           << x.rw << ") @ " << x.loc << "\n";
      os << "  port demand: reads=" << r.demand.reads
         << " writes=" << r.demand.writes << " total=" << r.demand.total
         << " (max over scopes"
         << (r.demand.segregated ? "; segregated R/W" : "") << ")\n";
      for (const ScopeDemandRecord &s : r.perScope)
        os << "    scope " << s.scopeKind << " @ " << s.scopeLoc
           << " ii=" << s.ii << ": reads=" << s.demand.reads
           << " writes=" << s.demand.writes << " total=" << s.demand.total
           << (s.sameState ? " [" + *s.sameState + "]" : std::string())
           << "\n";
    }
    if (r.replication.present) {
      const ReplicationRecord &p = r.replication;
      os << "  replication: " << (p.replicable ? "replicable" : "not replicable")
         << " (max " << p.maxStoresPerLoop
         << " store(s) per loop body), copies " << p.copies;
      if (p.limitingLoop)
        os << " set by pipeline @ " << *p.limitingLoop;
      os << "\n";
      for (const ReplicationLoopRecord &l : p.loops)
        os << "    pipeline @ " << l.scopeLoc << " ii=" << l.ii << ": "
           << l.reads << "R+" << l.writes << "W per iteration -> ceil("
           << (l.reads + l.writes) << "/" << l.ii << ")=" << l.need
           << " port-cycles -> copies " << l.copies
           << (l.portBound ? " (port-bound: a callee instantiated at more "
                             "than one place, N14 R6)"
                           : "")
           << "\n";
    }
    os << "  ram type: " << r.ramType << " -- " << r.ramReason << "\n";
    if (r.bankMath.present) {
      const BankMathRecord &b = r.bankMath;
      // x36 iff the bank is simple dual port (isWideKind): one used port, or
      // two read-only ports (ROM_2P), or write-only + read-only (RAM_S2P).
      bool onePort = r.ramType == "RAM_1P" || r.ramType == "ROM_1P";
      os << "  bank math: " << b.bitsPerBram << " bits/BRAM_18K (incl. parity), "
         << (!b.wide    ? "two live ports -> x18 max"
             : onePort  ? "one live port -> x36 allowed"
                        : "simple dual port -> x36 allowed")
         << " at " << r.ramType << ", element " << r.elemBits
         << "b -> mode x" << b.configWidth << ": columns ceil(" << r.elemBits
         << "/" << b.configWidth << ")=" << b.widthTiles << ", depth/block "
         << b.depthPerBlock << ", address depth 2^ceil(log2 "
         << (r.words ? *r.words : 0) << ")=" << b.addrDepth
         << ", blocks/column max(1," << b.addrDepth << "/" << b.depthPerBlock
         << ")=" << b.depthTiles << " -> " << b.blocksPerCopy
         << " per copy, replication " << b.replication << " -> " << b.blocks
         << " block(s); formula " << b.formula << ": " << b.band << "\n";
    }
    for (const MemrefRecord::RomModuleCopy &c : r.romModuleCopies)
      os << "  rom module copy: " << c.copies << " x " << c.bramPerCopy
         << " in " << c.where << " (readers " << c.funcs << "; " << c.rule
         << ")\n";
    if (r.instances != 1)
      os << "  instances: " << r.instances << " of @"
         << (r.ownerFunc ? *r.ownerFunc : (r.func ? *r.func : "?"))
         << " (N14: charged once per instance; " << r.bramPerInstance
         << " per instance)\n";
    os << "  bram: " << r.bram << (r.infeasible ? "  [INFEASIBLE]" : "")
       << "\n";
  }
  if (!instances.empty()) {
    os << "--- instances (non-inlined callees, VITIS_NOTES.md N14 R2/R3) "
          "---\n";
    for (const InstanceRecord &f : instances) {
      os << "  @" << f.func << ": " << f.instances << " instance(s)"
         << (f.inlineOff ? " (inline off)" : "")
         << (f.inlineAutoOff ? " (not inlined automatically)" : "") << "\n";
      for (const InstanceRecord::Parent &p : f.parents) {
        os << "    in @" << p.parent << " (x" << p.parentInstances << "): "
           << p.rule << "\n";
        for (const auto &[loc, inst] : p.sites)
          os << "      call @ " << loc << " -> instance " << inst << "\n";
      }
    }
  }
  os << "--- pipelines (decisions of --auto-pipeline-unroll) ---\n";
  for (const PipelineRecord &p : pipelines) {
    os << "  pipeline @ " << p.loc << " in @" << p.func << ": ii=" << p.ii;
    if (p.tripCount)
      os << " trip=" << *p.tripCount;
    os << " source=" << p.source
       << " flattened_parents=" << p.flattenedParents;
    if (p.unrollPartial)
      os << " unroll_partial=" << *p.unrollPartial;
    if (p.unrollRuntimeGuarded)
      os << " (run-time trip: guarded copies, N103)";
    if (p.sunkTrailingOps)
      os << " sunk_trailing_ops=" << p.sunkTrailingOps << " (N97 (b))";
    if (!p.scheduler.empty())
      os << " scheduler=" << p.scheduler;
    if (DictionaryAttr m = p.memoryRecurrence) {
      auto num = [&](StringRef k) {
        auto a = m.getAs<IntegerAttr>(k);
        return a ? a.getInt() : int64_t(0);
      };
      auto str = [&](StringRef k) {
        auto a = m.getAs<StringAttr>(k);
        return a ? a.getValue() : StringRef();
      };
      os << " memory_recurrence=" << str("rule") << " ii>=" << num("ii")
         << " (distance " << num("distance") << ", chain " << num("chain")
         << ", load @ " << str("load") << ", store @ " << str("store") << ")";
    }
    if (p.foldedGuards || p.pinnedGuardOperands)
      os << " folded_guards=" << p.foldedGuards
         << " pinned_guard_operands=" << p.pinnedGuardOperands << " (N89)";
    if (!p.argumentBankPorts.empty()) {
      os << " argument_bank_ports=[";
      bool first = true;
      for (const auto &[k, n] : p.argumentBankPorts) {
        os << (first ? "" : ", ") << k << ": " << n;
        first = false;
      }
      os << "] (N88)";
    }
    os << "\n";
    for (const PipelineRecord::Unrolled &u : p.unrolled)
      os << "    unrolled x" << u.factor << " @ " << u.loc << "\n";
  }
  printFoldSummary(fold, os);
  os << "--- summary (sorted by BRAM) ---\n";
  for (const MemrefRecord *r : sortedByBram(records))
    os << "  " << llvm::format("%6u", r->bram) << "  " << r->id << "  "
       << displayName(*r) << "\n";
  os << "Total BRAM: " << total << "\n";
}

static llvm::json::Value optStr(const std::optional<std::string> &s) {
  if (s)
    return llvm::json::Value(*s);
  return llvm::json::Value(nullptr);
}

static llvm::json::Value optInt(const std::optional<int64_t> &v) {
  if (v)
    return llvm::json::Value(*v);
  return llvm::json::Value(nullptr);
}

static llvm::json::Object toJson(const MemrefRecord &r) {
  llvm::json::Object o;
  o["id"] = r.id;
  o["name"] = optStr(r.name);
  o["varname"] = optStr(r.varname);
  o["kind"] = r.kind;
  o["func"] = optStr(r.func);
  // Additive (version stays 2): provenance of a promoted global, ROM pricing
  // and the m_axi adapter pseudo-memrefs (kind "m_axi_adapter").
  if (r.fromGlobal)
    o["from_global"] = *r.fromGlobal;
  if (r.structMember) // additive (W8b)
    o["struct_member"] = *r.structMember;
  if (r.aggregated) // additive
    o["aggregated"] = *r.aggregated;
  if (r.rom)
    o["rom"] = true;
  if (r.math)
    o["math"] = mathCoreJson(*r.math);
  if (r.pipo) { // additive (W9): array of a dataflow region
    const PipoRecord &pp = *r.pipo;
    llvm::json::Object po;
    po["channel"] = pp.channel;
    if (!pp.channel) {
      po["not_channel_reason"] = pp.notChannelReason;
    } else {
      po["region"] = pp.region;
      po["region_kind"] = pp.regionKind;
      llvm::json::Array procs;
      for (const DataflowProcess &dp : pp.processes) {
        llvm::json::Object pr;
        pr["process"] = dp.name;
        pr["position"] = static_cast<int64_t>(dp.position);
        pr["reads"] = dp.reads;
        pr["writes"] = dp.writes;
        if (!dp.group.empty()) { // additive: the process Vitis merges it into
          pr["merge_group"] = dp.group;
          pr["merge_reason"] = dp.mergeReason;
        }
        procs.push_back(std::move(pr));
      }
      po["processes"] = std::move(procs);
      po["blocks"] = pp.blocks;
      po["blocks_source"] = pp.blocksSource;
      if (!pp.bindType.empty())
        po["bind_type"] = pp.bindType;
      if (!pp.bindImpl.empty())
        po["bind_impl"] = pp.bindImpl;
      if (!pp.secondPort.empty())
        po["second_port"] = pp.secondPort;
      po["mode"] = pp.mode;
      po["mode_reason"] = pp.modeReason;
      po["rule"] = pp.rule;
    }
    o["pipo"] = std::move(po);
  }
  if (r.fifo) { // additive (W9): hls::stream handle storage
    const StreamHandleRecord &f = *r.fifo;
    llvm::json::Object fo;
    fo["fifos"] = f.fifos;
    fo["bram"] = static_cast<int64_t>(f.bram);
    llvm::json::Array methods;
    for (const std::string &m : f.methods)
      methods.push_back(m);
    fo["methods"] = std::move(methods);
    llvm::json::Array groups;
    for (const FifoGroup &g : f.groups) {
      llvm::json::Object go;
      go["count"] = g.count;
      go["count_source"] = g.countSource;
      if (g.member)
        go["member"] = static_cast<int64_t>(*g.member);
      go["depth"] = g.depth;
      go["depth_source"] = g.depthSource;
      go["bits"] = static_cast<int64_t>(g.bits);
      go["bits_source"] = g.bitsSource;
      go["bram_each"] = static_cast<int64_t>(g.bramEach);
      go["reason"] = g.reason;
      groups.push_back(std::move(go));
    }
    fo["groups"] = std::move(groups);
    if (!f.note.empty())
      fo["note"] = f.note;
    o["fifo"] = std::move(fo);
  }
  if (r.adapter) {
    const AdapterRecord &a = *r.adapter;
    llvm::json::Object ad;
    ad["bundle"] = a.bundle;
    llvm::json::Array ports;
    for (const std::string &p : a.ports)
      ports.push_back(p);
    ad["ports"] = std::move(ports);
    ad["bus_bits"] = static_cast<int64_t>(a.busBits);
    ad["has_read"] = a.hasRead;
    ad["has_write"] = a.hasWrite;
    ad["passed_to_call"] = a.passedToCall;
    ad["unresolved_call"] = a.unresolvedCall;
    ad["max_read_burst_length"] = a.readBurst;
    ad["num_read_outstanding"] = a.readOutstanding;
    ad["read_depth"] = a.readDepth;
    ad["read_bram"] = static_cast<int64_t>(a.readBram);
    ad["read_bits"] = static_cast<int64_t>(a.readBits);
    ad["read_channels"] = static_cast<int64_t>(a.readChannels);
    ad["read_rule"] = a.readRule;
    ad["max_write_burst_length"] = a.writeBurst;
    ad["num_write_outstanding"] = a.writeOutstanding;
    ad["write_bram"] = static_cast<int64_t>(a.writeBram);
    ad["write_rule"] = a.writeRule;
    o["adapter"] = std::move(ad);
  }
  if (r.hasLoc) {
    llvm::json::Object loc;
    loc["file"] = r.locFile;
    loc["line"] = static_cast<int64_t>(r.locLine);
    loc["col"] = static_cast<int64_t>(r.locCol);
    o["loc"] = std::move(loc);
  } else {
    o["loc"] = nullptr;
  }
  llvm::json::Array shape;
  for (int64_t d : r.shape)
    shape.push_back(ShapedType::isDynamic(d) ? llvm::json::Value(nullptr)
                                             : llvm::json::Value(d));
  o["shape"] = std::move(shape);
  o["elem_type"] = r.elemType;
  o["elem_bits"] = static_cast<int64_t>(r.elemBits);
  o["words"] = optInt(r.words);
  o["status"] = r.status;
  o["exclude_reason"] = optStr(r.excludeReason);
  if (r.keptReason) // additive: only on arrays kept although never read
    o["kept_reason"] = *r.keptReason;
  if (r.narrow) { // additive: only on arrays priced with a narrowed width
    llvm::json::Object n;
    n["declared_bits"] = static_cast<int64_t>(r.narrow->declaredBits);
    n["bits"] = static_cast<int64_t>(r.narrow->bits);
    n["reason"] = r.narrow->reason;
    o["narrow"] = std::move(n);
  }

  if (r.partition.present) {
    const PartitionRecord &p = r.partition;
    llvm::json::Object part;
    part["kind"] = p.kind;
    part["factor"] = p.factor;
    part["dim"] = p.dim;
    part["source"] = p.source;
    part["reason"] = optStr(p.reason);
    part["bank_index"] = optInt(p.bankIndex);
    part["bank_count"] = optInt(p.bankCount);
    // Additive keys: only on banks split along several dimensions, or split
    // by a pragma that is not the array's own.
    if (!p.dims.empty()) {
      llvm::json::Array dims;
      for (const auto &[k, f, dm] : p.dims)
        dims.push_back(llvm::json::Object{{"kind", k}, {"factor", f}, {"dim", dm}});
      part["dims"] = std::move(dims);
    }
    if (p.from)
      part["from"] = *p.from;
    // Additive (W9r9 review D8): load groups steered across the banks.
    if (p.forwardedReloads) {
      llvm::json::Array g;
      for (int64_t n : p.steeredGroups)
        g.push_back(n);
      part["steered_groups"] = std::move(g);
      part["forwarded_reloads"] = *p.forwardedReloads;
    }
    // Additive (W9r15, OPEN_ISSUES O150).
    if (p.prunedStoreEnables)
      part["pruned_store_enables"] = *p.prunedStoreEnables;
    o["partition"] = std::move(part);
  } else {
    o["partition"] = nullptr;
  }

  llvm::json::Array accesses;
  for (const AccessRecord &a : r.accesses) {
    llvm::json::Object ao;
    ao["op"] = a.op;
    ao["rw"] = a.isWrite ? "write" : "read";
    ao["scope"] = a.scopeKind;
    ao["scope_loc"] = a.scopeLoc;
    ao["ii"] = static_cast<int64_t>(a.ii);
    ao["stage_start"] = static_cast<int64_t>(a.stageStart);
    ao["store_enable"] = a.storeEnable;
    ao["merged_loads"] = static_cast<int64_t>(a.mergedLoads);
    ao["forwarded_loads"] = static_cast<int64_t>(a.forwardedLoads);
    ao["removed_stores"] = static_cast<int64_t>(a.removedStores);
    ao["register_promoted_accesses"] =
        static_cast<int64_t>(a.registerPromoted);
    // Additive (N38-impl): stores of both if/else arms merged into this one.
    ao["merged_if_else_stores"] = static_cast<int64_t>(a.mergedIfElseStores);
    ao["hoisted_conditional"] = a.hoistedConditional;
    // Additive (W3, N14 R6): the function the access lies in and the call
    // through which a callee's access of an argument array was reached.
    ao["in_func"] = a.inFunc.empty() ? llvm::json::Value(nullptr)
                                     : llvm::json::Value(a.inFunc);
    ao["via_call"] = optStr(a.viaCall);
    // Additive (W3 review D2, N14 R6).
    ao["port_bound"] = a.portBound;
    // Additive (W9r9 review D8): R6 instances / N75 several arrays / N75 per
    // array.
    ao["port_bound_reason"] = a.portBoundReason.empty()
                                  ? llvm::json::Value(nullptr)
                                  : llvm::json::Value(a.portBoundReason);
    // Additive (W9r11 review D8): the bank of a partitioned argument whose
    // ports the access uses (N88).
    ao["port_bank"] = a.portBank.empty() ? llvm::json::Value(nullptr)
                                         : llvm::json::Value(a.portBank);
    accesses.push_back(std::move(ao));
  }
  o["accesses"] = std::move(accesses);
  // Additive (W9r11 review D8): accesses a register serves, with the rule.
  llvm::json::Array served;
  for (const MemrefRecord::RegisterServed &x : r.registerServed)
    served.push_back(llvm::json::Object{
        {"op", x.op}, {"rw", x.rw}, {"loc", x.loc}, {"rule", x.rule}});
  o["register_served_accesses"] = std::move(served);

  llvm::json::Object pd;
  pd["reads"] = static_cast<int64_t>(r.demand.reads);
  pd["writes"] = static_cast<int64_t>(r.demand.writes);
  pd["total"] = static_cast<int64_t>(r.demand.total);
  llvm::json::Array perScope;
  for (const ScopeDemandRecord &s : r.perScope) {
    llvm::json::Object so;
    so["scope"] = s.scopeKind;
    so["scope_loc"] = s.scopeLoc;
    so["ii"] = static_cast<int64_t>(s.ii);
    so["reads"] = static_cast<int64_t>(s.demand.reads);
    so["writes"] = static_cast<int64_t>(s.demand.writes);
    so["total"] = static_cast<int64_t>(s.demand.total);
    if (s.sameState)
      so["same_state"] = *s.sameState;
    perScope.push_back(std::move(so));
  }
  pd["per_scope"] = std::move(perScope);
  o["port_demand"] = std::move(pd);

  o["ram_type"] = r.ramType;
  o["ram_reason"] = r.ramReason;

  if (r.replication.present) {
    const ReplicationRecord &p = r.replication;
    llvm::json::Object rp;
    rp["replicable"] = p.replicable;
    rp["max_stores_per_loop"] = static_cast<int64_t>(p.maxStoresPerLoop);
    rp["copies"] = static_cast<int64_t>(p.copies);
    rp["limiting_loop"] = optStr(p.limitingLoop);
    llvm::json::Array loops;
    for (const ReplicationLoopRecord &l : p.loops) {
      llvm::json::Object lo;
      lo["scope_loc"] = l.scopeLoc;
      lo["ii"] = static_cast<int64_t>(l.ii);
      lo["reads"] = static_cast<int64_t>(l.reads);
      lo["writes"] = static_cast<int64_t>(l.writes);
      lo["need"] = static_cast<int64_t>(l.need);
      lo["copies"] = static_cast<int64_t>(l.copies);
      // Additive (W3 review D2, N14 R6).
      lo["port_bound"] = l.portBound;
      if (l.fullCopies)
        lo["full_copies"] = true;
      loops.push_back(std::move(lo));
    }
    rp["loops"] = std::move(loops);
    o["replication"] = std::move(rp);
  } else {
    o["replication"] = nullptr;
  }

  if (r.bankMath.present) {
    const BankMathRecord &b = r.bankMath;
    llvm::json::Object bm;
    bm["bits_per_bram"] = b.bitsPerBram;
    bm["wide"] = b.wide;
    bm["max_width"] = static_cast<int64_t>(b.maxWidth);
    bm["config_width"] = static_cast<int64_t>(b.configWidth); // mode m
    bm["width_tiles"] = b.widthTiles;         // columns = ceil(bits / m)
    bm["depth_per_block"] = b.depthPerBlock;  // words per RAMB18 in mode m
    bm["addr_depth"] = b.addrDepth;           // 2^ceil(log2 words)
    bm["depth_tiles"] = b.depthTiles;         // blocks per column
    bm["blocks_per_copy"] = b.blocksPerCopy;
    bm["replication"] = b.replication;
    bm["blocks"] = b.blocks;
    // Additive (version 2 readers ignore them): bram-formula= and its band.
    bm["formula"] = b.formula;
    bm["band"] = b.band;
    o["bank_math"] = std::move(bm);
  } else {
    o["bank_math"] = nullptr;
  }
  o["bram"] = static_cast<int64_t>(r.bram);
  // Additive (W3, N14 R1-R3): the memory is charged once per instance of
  // its owning module; `bram` is the charged total.
  o["instances"] = static_cast<int64_t>(r.instances);
  o["bram_per_instance"] = static_cast<int64_t>(r.bramPerInstance);
  o["owner_func"] = optStr(r.ownerFunc);
  return o;
}

/// Additive (P2), one entry per record id under the top-level key
/// "memory_model" (not in the record itself, whose sorted keys hand-written
/// tests check line by line): the device memory that priced it, the storage
/// selector's tier and what it costs per resource class.
static llvm::json::Value memoryModelJson(ArrayRef<MemrefRecord> records) {
  llvm::json::Object out;
  for (const MemrefRecord &r : records) {
    llvm::json::Object o;
    o["memory"] = r.memoryId.empty() ? llvm::json::Value(nullptr)
                                     : llvm::json::Value(r.memoryId);
    o["storage_tier"] = r.storageTier.empty()
                            ? llvm::json::Value(nullptr)
                            : llvm::json::Value(r.storageTier);
    o["resources"] = r.resources.toJson();
    out[r.id] = std::move(o);
  }
  return out;
}

// Returns the error code of the failed open, or a default (success) code.
/// The configuration this run used (additive debug key "config"): its hash,
/// device and profile, the files and --config-set assignments, and every key
/// that differs from the compiled-in defaults with its value and origin.
static llvm::json::Value configRecord() {
  const Config &cfg = config();
  llvm::json::Object c;
  c["hash"] = cfg.hash;
  c["device"] = cfg.device.id;
  c["tool"] = cfg.tool.id;
  llvm::json::Array files, sets;
  for (const std::string &f : cfg.files)
    files.push_back(f);
  for (const std::string &st : cfg.sets)
    sets.push_back(st);
  c["files"] = std::move(files);
  c["sets"] = std::move(sets);
  llvm::json::Object changed;
  for (const circt::hlsest::ConfigOverride &o : cfg.overrides)
    changed[o.path] = llvm::json::Object{{"value", o.value},
                                         {"source", o.source}};
  c["non_default"] = std::move(changed);
  return c;
}

static std::error_code writeDebugJson(ArrayRef<MemrefRecord> records,
                                      ArrayRef<PipelineRecord> pipelineRecords,
                                      ArrayRef<InstanceRecord> instanceRecords,
                                      int64_t total, const FoldSummary &fold,
                                      const circt::hlsest::MemoryMapper &mapper,
                                      const llvm::json::Value &plugins,
                                      const llvm::json::Value &resources,
                                      const llvm::json::Value &functionPipelines,
                                      const TopScope &scope, StringRef path) {
  llvm::json::Object root;
  root["version"] = 2;
  root["total_bram"] = total;
  root["bram_formula"] = mapper.reportLabel(); // additive
  root["config"] = configRecord(); // additive (P2)
  root["plugins"] = plugins;       // additive (P2)
  root["resources"] = resources;   // additive (P2)
  root["memory_model"] = memoryModelJson(records); // additive (P2)
  // Additive (W9r19): ROMs priced per reading module (N136), and the kept
  // callees pipelined at their caller's II (N144).
  {
    llvm::json::Object copies;
    for (const MemrefRecord &r : records) {
      if (r.romModuleCopies.empty())
        continue;
      llvm::json::Array a;
      for (const MemrefRecord::RomModuleCopy &c : r.romModuleCopies)
        a.push_back(llvm::json::Object{{"readers", c.funcs},
                                       {"where", c.where},
                                       {"rule", c.rule},
                                       {"copies", (int64_t)c.copies},
                                       {"bram_per_copy",
                                        (int64_t)c.bramPerCopy}});
      copies[r.id] = std::move(a);
    }
    root["rom_module_copies"] = std::move(copies);
  }
  root["function_pipelines"] = functionPipelines;
  // Additive: top= (null without it) and what it left out.
  if (scope.active()) {
    llvm::json::Object to;
    to["symbol"] = scope.symbol;
    SmallVector<StringRef> names(scope.funcNames.begin(),
                                 scope.funcNames.end());
    llvm::sort(names);
    llvm::json::Array fa;
    for (StringRef n : names)
      fa.push_back(n.str());
    to["functions"] = std::move(fa);
    to["skipped_memrefs"] = static_cast<int64_t>(scope.skipped);
    root["top"] = std::move(to);
  } else {
    root["top"] = nullptr;
  }

  llvm::json::Array functions;
  SmallVector<std::string> seen;
  for (const MemrefRecord &r : records)
    if (r.func && !llvm::is_contained(seen, *r.func)) {
      seen.push_back(*r.func);
      functions.push_back(*r.func);
    }
  root["functions"] = std::move(functions);

  llvm::json::Array memrefs;
  for (const MemrefRecord &r : records)
    memrefs.push_back(toJson(r));
  root["memrefs"] = std::move(memrefs);

  llvm::json::Array pipelines;
  for (const PipelineRecord &p : pipelineRecords) {
    llvm::json::Object po;
    po["scope_loc"] = p.loc;
    po["func"] = p.func;
    po["ii"] = static_cast<int64_t>(p.ii);
    po["trip_count"] = optInt(p.tripCount);
    po["source"] = p.source;
    po["flattened_parents"] = static_cast<int64_t>(p.flattenedParents);
    po["unroll_partial"] = optInt(p.unrollPartial);
    po["unroll_runtime_guarded"] = p.unrollRuntimeGuarded;
    po["sunk_trailing_ops"] = p.sunkTrailingOps;
    po["scheduler"] = p.scheduler.empty() ? llvm::json::Value(nullptr)
                                          : llvm::json::Value(p.scheduler);
    if (DictionaryAttr m = p.memoryRecurrence) {
      llvm::json::Object mo;
      for (NamedAttribute a : m) {
        if (auto i = dyn_cast<IntegerAttr>(a.getValue()))
          mo[a.getName().strref()] = i.getInt();
        else if (auto s = dyn_cast<StringAttr>(a.getValue()))
          mo[a.getName().strref()] = s.getValue().str();
      }
      po["memory_recurrence"] = std::move(mo);
    } else {
      po["memory_recurrence"] = nullptr;
    }
    // Additive (W9r11 review D8): N89's folded guards and pinned operands.
    po["folded_guards"] = p.foldedGuards;
    po["pinned_guard_operands"] = p.pinnedGuardOperands;
    llvm::json::Object abp;
    for (const auto &[k, n] : p.argumentBankPorts)
      abp[k] = n;
    po["argument_bank_ports"] = std::move(abp);
    llvm::json::Array unrolled;
    for (const PipelineRecord::Unrolled &u : p.unrolled) {
      llvm::json::Object uo;
      uo["loc"] = u.loc;
      uo["factor"] = u.factor;
      unrolled.push_back(std::move(uo));
    }
    po["unrolled"] = std::move(unrolled);
    pipelines.push_back(std::move(po));
  }
  root["pipelines"] = std::move(pipelines);

  // Additive (W3): the non-inlined callees and their instances (N14).
  llvm::json::Array instances;
  for (const InstanceRecord &f : instanceRecords) {
    llvm::json::Object fo;
    fo["func"] = f.func;
    fo["instances"] = static_cast<int64_t>(f.instances);
    fo["inline_off"] = f.inlineOff;
    fo["inline_auto_off"] = f.inlineAutoOff;
    llvm::json::Array parents;
    for (const InstanceRecord::Parent &p : f.parents) {
      llvm::json::Object po;
      po["parent"] = p.parent;
      po["parent_instances"] = static_cast<int64_t>(p.parentInstances);
      po["call_sites"] = static_cast<int64_t>(p.callSites);
      po["instances"] = static_cast<int64_t>(p.instances);
      po["allocation_limit"] = optInt(p.limit);
      po["rule"] = p.rule;
      llvm::json::Array sites;
      for (const auto &[loc, inst] : p.sites)
        sites.push_back(llvm::json::Object{
            {"loc", loc}, {"instance", static_cast<int64_t>(inst)}});
      po["sites"] = std::move(sites);
      parents.push_back(std::move(po));
    }
    fo["parents"] = std::move(parents);
    instances.push_back(std::move(fo));
  }
  root["instances"] = std::move(instances);

  llvm::json::Array summary;
  for (const MemrefRecord *r : sortedByBram(records)) {
    llvm::json::Object s;
    s["id"] = r->id;
    s["varname"] = optStr(r->varname);
    s["bram"] = static_cast<int64_t>(r->bram);
    summary.push_back(std::move(s));
  }
  root["summary"] = std::move(summary);

  // Additive (version 2 readers ignore it): null without --vitis-fold.
  if (fold.present) {
    llvm::json::Object fo, counts;
    for (auto &c : fold.counts)
      counts[c.first] = c.second;
    fo["counts"] = std::move(counts);
    llvm::json::Array rewrites;
    for (const FoldSummary::Rewrite &w : fold.rewrites) {
      llvm::json::Object wo;
      wo["rule"] = w.rule;
      wo["loc"] = w.loc;
      wo["source"] = w.source;
      wo["detail"] = w.detail.empty() ? llvm::json::Value(nullptr)
                                      : llvm::json::Value(w.detail);
      wo["func"] = w.func.empty() ? llvm::json::Value(nullptr)
                                  : llvm::json::Value(w.func); // additive
      rewrites.push_back(std::move(wo));
    }
    fo["rewrites"] = std::move(rewrites);
    // Additive: "top" when top= narrowed the summary to the reachable
    // functions, else "module".
    fo["scope"] = scope.active() && !fold.wholeModule ? "top" : "module";
    root["vitis_fold"] = std::move(fo);
  } else {
    root["vitis_fold"] = nullptr;
  }

  std::error_code ec;
  llvm::raw_fd_ostream os(path, ec, llvm::sys::fs::OF_Text);
  if (ec)
    return ec;
  os << llvm::formatv("{0:2}", llvm::json::Value(std::move(root))) << "\n";
  return std::error_code();
}

//===----------------------------------------------------------------------===//
// m_axi adapters (VITIS_NOTES.md N1a "Interfaces"; dead_globals.md R8 and the
// 14 mx_* kernels of ~/hls-est-work/exp-src/maxi).
//===----------------------------------------------------------------------===//

// One record per (public function, bundle) of m_axi arguments, from the
// configuration's implicit-buffer model (tool.hls.implicit_buffers[axi4-mm]:
// vitis-m_axi); only public functions with a body have an interface.
static SmallVector<std::pair<func::FuncOp, AdapterRecord>>
collectAdapters(ModuleOp module, const Models &models) {
  SmallVector<std::pair<func::FuncOp, AdapterRecord>> out;
  const circt::hlsest::ImplicitBufferConfig *mc =
      config().tool.hls.implicitBuffer("axi4-mm");
  if (!mc || !models.buffers || !models.fifoMapper)
    return out;
  // The read FIFO is priced by the mapper and at the port configuration the
  // entry names (vitis-band7, tdp: the x18 bands), whatever the main mapper.
  auto mapFifo = [&](int64_t depth, unsigned bits) -> int64_t {
    return mapBlocks(*models.fifoMapper, *models.block,
                     mc->readFifoPricedConfig, depth, bits);
  };
  for (auto fn : module.getOps<func::FuncOp>()) {
    if (fn.isPrivate() || fn.isExternal())
      continue;
    SmallVector<circt::hlsest::ImplicitBuffer> buffers;
    models.buffers->buffers(fn, *mc, mapFifo, buffers);
    for (circt::hlsest::ImplicitBuffer &b : buffers)
      out.push_back({fn, std::move(b)});
  }
  return out;
}

// Records for the memrefs --dead-memory-elimination removed (module attribute
// `hls.dead_memrefs`): debug output only, 0 BRAM, never on stdout.
static void appendDeadRecords(ModuleOp module, unsigned &index,
                              std::vector<MemrefRecord> &records) {
  auto arr = module->getAttrOfType<ArrayAttr>("hls.dead_memrefs");
  if (!arr)
    return;
  for (Attribute attr : arr) {
    auto d = dyn_cast<DictionaryAttr>(attr);
    if (!d)
      continue;
    MemrefRecord r;
    auto str = [&](StringRef k) -> std::optional<std::string> {
      if (auto s = d.getAs<StringAttr>(k))
        return s.getValue().str();
      return std::nullopt;
    };
    r.kind = str("kind").value_or("alloca");
    r.func = str("func");
    if (r.kind == "global")
      r.name = str("symbol");
    r.varname = str("name");
    r.fromGlobal = str("from_global");
    r.id = (r.func ? *r.func : std::string("?")) + "#dead" +
           std::to_string(index++);
    if (auto l = d.getAs<LocationAttr>("loc")) {
      if (auto f = findFileLoc(Location(l))) {
        r.hasLoc = true;
        r.locFile = f.getFilename().str();
        r.locLine = f.getLine();
        r.locCol = f.getColumn();
      }
      r.locText = locString(Location(l));
    }
    if (auto t = d.getAs<TypeAttr>("type"))
      if (auto mt = dyn_cast<MemRefType>(t.getValue())) {
        r.shape = llvm::to_vector(mt.getShape());
        Type elt = mt.getElementType();
        llvm::raw_string_ostream os(r.elemType);
        elt.print(os);
        r.elemBits = elt.isIntOrFloat() ? elt.getIntOrFloatBitWidth()
                     : isa<IndexType>(elt) ? indexElementBits()
                                           : 0u;
        if (mt.hasStaticShape())
          r.words = mt.getNumElements();
      }
    r.status = "eliminated_dead";
    r.excludeReason = "removed by " +
                      str("by").value_or("--dead-memory-elimination") + ": " +
                      str("reason").value_or("dead");
    r.ramType = "none";
    r.ramReason = "eliminated";
    r.bram = 0;
    records.push_back(std::move(r));
  }
}

//===----------------------------------------------------------------------===//
// Top function (top=, MEMOS.md M7, OPEN_ISSUES.md O12).
//===----------------------------------------------------------------------===//
// Vitis synthesizes the top function and what it calls; cgeist also emits
// uncalled alternative tops and standalone copies of callees it inlined (O10),
// whose memrefs Vitis never sees. With top=<symbol> --bram-analysis costs only
// the memrefs of the func.funcs reachable from the top, the memref.globals
// those functions use, and the m_axi adapters of the top's own interface.
// Reachable = what --symbol-privatize=exclude=<top> --symbol-dce keeps: every
// symbol a reachable function references, transitively (the callee of a
// func.call, the function of a func.constant for an indirect call, the global
// of a memref.get_global, a symbol in any other attribute). A global's
// get_global sites in other functions are not attributed either
// (runOnOperation), so the ports, copies and ROM test of a global shared with
// an unreachable function see only the reachable accesses.

// Fills `scope` with what `top` reaches; false (after an error) when there is
// no func.func of that name with a body.
static bool computeTopScope(ModuleOp module, StringRef top, TopScope &scope) {
  scope.symbol = top.str();
  auto topFn = module.lookupSymbol<func::FuncOp>(top);
  if (!topFn || topFn.isExternal()) {
    mlir::emitError(module.getLoc(), "--bram-analysis: top=")
        << top << ": no func.func with a body of that name in the module";
    return false;
  }
  SmallVector<func::FuncOp> work{topFn};
  scope.funcs.insert(topFn.getOperation());
  while (!work.empty()) {
    func::FuncOp fn = work.pop_back_val();
    scope.funcNames.insert(fn.getName());
    fn.walk([&](Operation *op) {
      // As SymbolTable's use walk: every SymbolRefAttr in the op's
      // attributes, a nested reference as one symbol.
      op->getAttrDictionary().walk<WalkOrder::PreOrder>(
          [&](SymbolRefAttr ref) {
            Operation *sym = SymbolTable::lookupNearestSymbolFrom(op, ref);
            if (auto g = dyn_cast_or_null<memref::GlobalOp>(sym))
              scope.globals.insert(g.getSymName());
            else if (auto callee = dyn_cast_or_null<func::FuncOp>(sym))
              if (!callee.isExternal() &&
                  scope.funcs.insert(callee.getOperation()).second)
                work.push_back(callee);
            return WalkResult::skip();
          });
    });
  }
  return true;
}

// The public func.funcs with a body that hold a memref (an alloca or a
// get_global), for the warning when no top= is given.
static SmallVector<StringRef> publicFuncsWithMemrefs(ModuleOp module) {
  SmallVector<StringRef> out;
  for (auto fn : module.getOps<func::FuncOp>()) {
    if (fn.isPrivate() || fn.isExternal())
      continue;
    bool holds = false;
    fn.walk([&](Operation *op) {
      if (isa<memref::AllocaOp, memref::AllocOp, memref::GetGlobalOp>(op)) {
        holds = true;
        return WalkResult::interrupt();
      }
      return WalkResult::advance();
    });
    if (holds)
      out.push_back(fn.getName());
  }
  return out;
}

// The non-inlined callees of the model (functions some in-scope function
// calls), by name, for the debug report.
static SmallVector<InstanceRecord>
collectInstanceRecords(const InstanceModel &model) {
  SmallVector<InstanceRecord> out;
  for (auto &[calleeOp, parents] : model.parents) {
    auto callee = cast<func::FuncOp>(calleeOp);
    InstanceRecord r;
    r.func = callee.getName().str();
    r.instances = model.instancesOf(callee);
    r.inlineOff = callee->hasAttr(kInlineOffAttr);
    r.inlineAutoOff = callee->hasAttr(kInlineAutoOffAttr);
    for (const ParentInstances &pi : parents) {
      InstanceRecord::Parent p;
      func::FuncOp parentFn = pi.parent;
      p.parent = parentFn.getName().str();
      p.parentInstances = model.instancesOf(parentFn);
      p.callSites = pi.callSites;
      p.instances = pi.instances;
      p.limit = pi.limit;
      p.rule = pi.rule;
      for (const auto &[site, group] : pi.siteGroups)
        p.sites.push_back({locString(site->getLoc()), group});
      r.parents.push_back(std::move(p));
    }
    llvm::sort(r.parents, [](const InstanceRecord::Parent &a,
                             const InstanceRecord::Parent &b) {
      return a.parent < b.parent;
    });
    out.push_back(std::move(r));
  }
  llvm::sort(out, [](const InstanceRecord &a, const InstanceRecord &b) {
    return a.func < b.func;
  });
  return out;
}

// The debug record of one math core (kind "math_core"): a pseudo-memref, as
// the m_axi adapters are, so that the debug report and compare.py list it
// next to the arrays.
static MemrefRecord mathCoreDebugRecord(MathCoreRecord m) {
  MemrefRecord rec;
  rec.id = m.func + "#math:" + m.function + ":" + m.type + ":" + m.arguments;
  rec.kind = "math_core";
  rec.name = m.coreName;
  rec.varname = "math_core:" + m.coreName;
  rec.func = m.func;
  rec.locText = m.loc;
  rec.elemType = m.type;
  rec.status = m.status;
  rec.ramType = "MATH_CORE";
  rec.ramReason = m.reason;
  rec.bram = static_cast<unsigned>(m.bram);
  // As for a memref: the instances of the owning function and what one of
  // them costs.
  rec.instances = m.functionInstances;
  rec.bramPerInstance = static_cast<unsigned>(m.bram / m.functionInstances);
  rec.math = std::move(m);
  return rec;
}

//===----------------------------------------------------------------------===//
// Pass.
//===----------------------------------------------------------------------===//
struct BRAMAnalysisLoopSchedule
    : PassWrapper<BRAMAnalysisLoopSchedule, OperationPass<ModuleOp>> {

  MLIR_DEFINE_EXPLICIT_INTERNAL_INLINE_TYPE_ID(BRAMAnalysisLoopSchedule)

  StringRef getArgument() const final { return "bram-analysis"; }
  StringRef getDescription() const final {
    return "Estimate BRAM resources for HLS allocations (post-banking).";
  }

  BRAMAnalysisLoopSchedule() = default;
  BRAMAnalysisLoopSchedule(const BRAMAnalysisLoopSchedule &other)
      : PassWrapper(other) {}

  Option<BramFormula> formulaOpt{
      *this, "bram-formula",
      llvm::cl::desc("Blocks per bank: band = the 7-series depth bands "
                     "(VITIS_NOTES.md N8, the default since MEMOS.md M4); "
                     "n6 = the minimum over the aspect-ratio modes (N6, the "
                     "former default; differs only deeper than 4096 words)"),
      llvm::cl::init(BramFormula::Band),
      llvm::cl::values(
          clEnumValN(BramFormula::Band, "band", "7-series depth bands (N8)"),
          clEnumValN(BramFormula::N6, "n6",
                     "minimum over aspect-ratio modes (N6)"))};

  Option<std::string> topOpt{
      *this, "top",
      llvm::cl::desc("Cost only the memrefs of the func.funcs reachable from "
                     "this one through calls (any symbol reference, as "
                     "--symbol-dce keeps them), the memref.globals they use and "
                     "its own m_axi adapters, as Vitis synthesizes the top and "
                     "what it calls (MEMOS.md M7). Without it every function "
                     "is costed, with a warning when more than one public "
                     "function holds memrefs"),
      llvm::cl::init("")};

  Option<std::string> mathCostsOpt{
      *this, "math-costs",
      llvm::cl::desc("Cost table of the hls:: math cores (JSON, "
                     "tools/hls-est-validate/math_costs.json): every math op, "
                     "libm call and exactclass-shim marker call gets the BRAM "
                     "of its (function, type, argument form) entry per core "
                     "instance, instances by the call structure; a pair the "
                     "table does not list is reported with a warning and "
                     "costs 0. Without it math calls cost nothing"),
      llvm::cl::value_desc("path"), llvm::cl::init("")};

  // The values this run uses: an option given explicitly, else the
  // configuration (hls-doc/configuration.md).
  Models models;
  std::string mathCostsPath;
  bool attributeGlobals = false, maxiAdapters = true, streamFifos = true,
       dataflowChannels = true, seqDualPort = true;
  /// The plugin chosen for each interface (the debug report's "plugins").
  llvm::json::Object pluginRecord;

  template <class Interface>
  std::unique_ptr<Interface> createPlugin(llvm::StringRef key,
                                          llvm::StringRef name,
                                          circt::hlsest::ConfigDiagnostics &diag) {
    auto &registry = circt::hlsest::PluginRegistry<Interface>::instance();
    std::unique_ptr<Interface> p = registry.create(name, config(), diag);
    if (p) {
      const circt::hlsest::PluginEntry *e = registry.find(name);
      pluginRecord[key] = llvm::json::Object{
          {"name", name.str()}, {"origin", e ? e->origin : "?"}};
    }
    return p;
  }

  template <class Interface>
  void recordConfiguredPlugin(llvm::StringRef key, llvm::StringRef name) {
    const circt::hlsest::PluginEntry *e =
        circt::hlsest::PluginRegistry<Interface>::instance().find(name);
    pluginRecord[key] = llvm::json::Object{
        {"name", name.str()}, {"origin", e ? e->origin : "?"}};
  }

  LogicalResult resolveConfiguration() {
    using circt::hlsest::resolveGlobalOption;
    const Config &cfg = config();
    const circt::hlsest::HlsToolConfig &hls = cfg.tool.hls;
    circt::hlsest::ConfigDiagnostics diag;
    // bram-formula=band | n6 is the mapper vitis-band7 | vitis-aspect-min.
    std::string mapperName = cfg.tool.backend.memoryMapper.plugin;
    if (formulaOpt.hasValue())
      mapperName = formulaOpt == BramFormula::Band ? "vitis-band7"
                                                   : "vitis-aspect-min";
    models.block = cfg.blockMemory();
    if (!models.block)
      diag.errors.push_back("tool.backend.memory_mapper.primitive: device '" +
                            cfg.device.id + "' has no memory '" +
                            cfg.tool.backend.memoryMapper.primitive + "'");
    models.mapper = createPlugin<circt::hlsest::MemoryMapper>(
        "memory_mapper", mapperName, diag);
    models.selector = createPlugin<circt::hlsest::StorageSelector>(
        "storage_selector", cfg.tool.backend.storageSelector.plugin, diag);
    models.policy = createPlugin<circt::hlsest::MemoryArchitecturePolicy>(
        "memory_architecture_policy", hls.memoryArchitecture.plugin, diag);
    models.grouping = createPlugin<circt::hlsest::MemoryGrouping>(
        "memory_grouping", hls.groupingPlugin, diag);
    models.streamMapper = createPlugin<circt::hlsest::MemoryMapper>(
        "stream_fifo_mapper", hls.streams.mapper, diag);
    const circt::hlsest::ImplicitBufferConfig *maxi =
        hls.implicitBuffer("axi4-mm");
    if (maxi) {
      models.buffers = createPlugin<circt::hlsest::ImplicitBufferModel>(
          "implicit_buffer_model", maxi->plugin, diag);
      models.fifoMapper = createPlugin<circt::hlsest::MemoryMapper>(
          "read_fifo_mapper", maxi->readFifoMapper, diag);
    }
    if (!diag.ok()) {
      InFlightDiagnostic d = getOperation().emitError("--bram-analysis: ");
      llvm::interleave(diag.errors, d, "; ");
      return failure();
    }
    // The implementations the other passes of the configuration select, so
    // that the report says which code produced every number.
    recordConfiguredPlugin<circt::hlsest::PipelinePolicy>(
        "pipeline_policy", hls.pipelineDecision.policy);
    recordConfiguredPlugin<circt::hlsest::PartitionPolicy>(
        "partition_policy", hls.partitioning.policy);
    recordConfiguredPlugin<circt::hlsest::FoldRuleSet>("fold_rule_set",
                                                       hls.folding.ruleSet);
    const circt::hlsest::SchedulingConfig &sc = cfg.scheduling;
    recordConfiguredPlugin<circt::hlsest::OperatorTimingModel>(
        "operator_timing_model", sc.timingModel);
    recordConfiguredPlugin<circt::hlsest::DependenceModel>("dependence_model",
                                                           sc.dependenceModel);
    recordConfiguredPlugin<circt::hlsest::ModuloScheduler>("modulo_scheduler",
                                                           sc.moduloModel);
    recordConfiguredPlugin<circt::hlsest::SequentialScheduler>(
        "sequential_scheduler", sc.sequentialModel);
    recordConfiguredPlugin<circt::hlsest::Binder>("binder", sc.bindingModel);
    mathCostsPath = mathCostsOpt.hasValue() ? std::string(mathCostsOpt)
                                            : hls.mathLibraryTable;
    attributeGlobals = resolveGlobalOption(bramAttributeGlobalsOpt,
                                           hls.globalsAttributeAccesses);
    maxiAdapters =
        resolveGlobalOption(bramMaxiAdaptersOpt, maxi && maxi->enabled) &&
        maxi;
    streamFifos = resolveGlobalOption(bramStreamFifosOpt, hls.streams.enabled);
    dataflowChannels = resolveGlobalOption(bramDataflowChannelsOpt,
                                           hls.dataflowChannels.enabled);
    seqDualPort = resolveGlobalOption(bramSeqDualPortOpt,
                                      models.policy->pairsSequentialAccesses());
    return success();
  }

  /// The memory groups of tool.hls.grouping: member op -> (group, position).
  llvm::DenseMap<Operation *, std::pair<unsigned, unsigned>> groupOf;
  SmallVector<circt::hlsest::MemoryGroup> groups;
  SmallVector<circt::hlsest::GroupCandidate> groupCandidates;

  /// Asks the grouping which memrefs share one memory (none for identity).
  void computeGroups(ModuleOp module, const TopScope &scope) {
    module.walk([&](MemoryResourceOpInterface iface) {
      Operation *op = iface.getOperation();
      Type elt = iface.getElementType();
      if (!scope.covers(op) || !elt.isIntOrFloat())
        return;
      int64_t words = 1;
      for (int64_t d : iface.getStaticShape()) {
        if (ShapedType::isDynamic(d))
          return;
        words *= d;
      }
      circt::hlsest::GroupCandidate c;
      c.op = op;
      if (auto v = op->getAttrOfType<StringAttr>("polygeist.varname"))
        c.name = v.getValue().str();
      else if (auto g = dyn_cast<memref::GlobalOp>(op))
        c.name = g.getSymName().str();
      c.request.words = words;
      c.request.writeWidth = elt.getIntOrFloatBitWidth();
      c.request.readWidths.push_back(c.request.writeWidth);
      groupCandidates.push_back(std::move(c));
    });
    models.grouping->group(groupCandidates, groups);
    for (auto [gi, g] : llvm::enumerate(groups))
      for (auto [pos, member] : llvm::enumerate(g.members))
        if (member < groupCandidates.size())
          groupOf[groupCandidates[member].op] = {
              static_cast<unsigned>(gi), static_cast<unsigned>(pos)};
  }

  /// A member of a group of two or more memrefs: the first member is priced
  /// as one memory holding all of them (their words one after the other, the
  /// widest element), at the narrow configuration; the others cost nothing.
  void applyGrouping(Operation *op, MemrefRecord &rec, BRAMCost &cost) {
    auto it = groupOf.find(op);
    if (it == groupOf.end())
      return;
    const circt::hlsest::MemoryGroup &g = groups[it->second.first];
    if (g.members.size() < 2)
      return;
    std::string names;
    int64_t words = 0;
    unsigned width = 0;
    for (unsigned m : g.members) {
      const circt::hlsest::GroupCandidate &c = groupCandidates[m];
      names += (names.empty() ? "" : ", ") +
               (c.name.empty() ? std::string("?") : c.name);
      words += c.request.words;
      width = std::max(width, c.request.writeWidth);
    }
    if (it->second.second == 0) {
      int64_t blocks = mapBlocks(
          *models.mapper, *models.block,
          config().tool.hls.memoryArchitecture.pricedNarrow, words, width,
          &rec.bankMath);
      cost.bramCount = static_cast<unsigned>(blocks);
      cost.note = "one memory for the group [" + names + "] (" + g.note +
                  "): " + std::to_string(words) + "x" +
                  std::to_string(width) + "b = " + std::to_string(blocks) +
                  " " + unitName(models.block);
      rec.memoryId = models.block ? models.block->id : "";
    } else {
      cost.bramCount = 0;
      cost.note = "in the memory of the group [" + names + "] (" + g.note +
                  "), priced with its first member";
      rec.memoryId.clear();
    }
    rec.bram = cost.bramCount;
    rec.ramReason = cost.note;
  }

  void runOnOperation() override {
    ModuleOp module = getOperation();
    if (failed(resolveConfiguration()))
      return signalPassFailure();
    // The math-core cost table first, so that a bad file fails before any
    // report line.
    MathCostConfig mathCosts;
    if (!mathCostsPath.empty()) {
      std::string err;
      if (!mathCosts.load(mathCostsPath, err)) {
        mlir::emitError(module.getLoc(), "--bram-analysis: math-costs: ")
            << err;
        return signalPassFailure();
      }
    }
    TopScope scope;
    if (!topOpt.empty()) {
      if (!computeTopScope(module, topOpt, scope))
        return signalPassFailure();
    } else {
      SmallVector<StringRef> tops = publicFuncsWithMemrefs(module);
      if (tops.size() > 1) {
        InFlightDiagnostic w = mlir::emitWarning(module.getLoc())
                               << "--bram-analysis: " << tops.size()
                               << " public functions hold memrefs (";
        llvm::interleaveComma(tops, w, [&](StringRef n) { w << "@" << n; });
        w << "); all of them are costed. Give the top function with "
             "--bram-analysis=top=<symbol> (or --symbol-privatize=exclude="
             "<top> --symbol-dce first) to cost only what it reaches";
      }
    }
    computeGroups(module, scope);
    int64_t total = 0;
    circt::hlsest::ResourceVector totalResources;
    // One record per memref, in walk order, kept for the debug report.
    std::vector<MemrefRecord> records;
    unsigned index = 0;
    // Built lazily per sequential scope; not with --bram-seq-dual-port=false.
    SeqContext seqContext;
    seqContext.policy = models.policy.get();
    SeqContext *seq = seqDualPort ? &seqContext : nullptr;
    // get_global sites per symbol (--bram-attribute-globals). With top= only
    // the sites in reachable functions: an access from a function the top
    // never reaches is not synthesized (the prefix deletes the function).
    llvm::StringMap<SmallVector<Value>> globalSites;
    if (attributeGlobals)
      module.walk([&](memref::GetGlobalOp gg) {
        if (scope.covers(gg))
          globalSites[gg.getName()].push_back(gg.getResult());
      });
    // Non-inlined callees (VITIS_NOTES.md N14): instances of every function
    // in scope (R2 concurrency groups per parent, R3 product down the call
    // tree). A function's own memories are charged once per instance; a
    // global is charged once per instance of the deepest function that
    // reaches all its get_global sites (its owner, where Vitis places a
    // static array shared by several callees).
    InstanceModel instanceModel = computeInstances(module, [&](func::FuncOp fn) {
      return !scope.active() || scope.funcs.contains(fn.getOperation());
    });
    llvm::StringMap<SmallVector<func::FuncOp>> globalUsers;
    // Every get_global site in scope, whatever --bram-attribute-globals says:
    // whether a global is written decides how often it is charged (R9).
    llvm::StringMap<SmallVector<Value>> globalUseSites;
    module.walk([&](memref::GetGlobalOp gg) {
      auto fn = gg->getParentOfType<func::FuncOp>();
      if (!fn || !scope.covers(gg))
        return;
      globalUseSites[gg.getName()].push_back(gg.getResult());
      auto &users = globalUsers[gg.getName()];
      if (!llvm::is_contained(users, fn))
        users.push_back(fn);
    });
    // Kept callees pipelined at their caller's II (VITIS_NOTES N144) and the
    // aggregated struct pointers that never limit their II (N147).
    circt::hls_analysis::AggregatedScalars aggregatedScalars =
        circt::hls_analysis::computeAggregatedScalars(module);
    auto isReadOnlyGlobal = [&](Operation *op) {
      auto g = dyn_cast<memref::GlobalOp>(op);
      if (!g || g.isExternal() || g.isUninitialized())
        return false;
      if (g.getConstant())
        return true;
      auto it = globalUseSites.find(g.getSymName());
      return it != globalUseSites.end() && neverWritten(it->second);
    };
    circt::hls_analysis::FunctionPipelineModel functionPipelines =
        circt::hls_analysis::computeFunctionPipelines(
            module, aggregatedScalars,
            [&](func::FuncOp fn) {
              return !scope.active() || scope.funcs.contains(fn.getOperation());
            },
            isReadOnlyGlobal);
    seqContext.functionPipelines = &functionPipelines;
    llvm::json::Array functionPipelinesArray;
    {
      SmallVector<std::pair<std::string, unsigned>> fps;
      for (const auto &[fn, ii] : functionPipelines.ii)
        fps.push_back({cast<func::FuncOp>(fn).getName().str(), ii});
      llvm::sort(fps);
      for (const auto &[name, ii] : fps)
        functionPipelinesArray.push_back(llvm::json::Object{
            {"func", name}, {"ii", (int64_t)ii}, {"rule", "N144"}});
    }
    llvm::json::Value functionPipelinesJson(std::move(functionPipelinesArray));
    // Second ports of the arrays of dataflow regions, per bank and per array
    // (--bram-dataflow-channels).
    auto sitesOf = [&](Operation *op) -> SmallVector<Value> {
      if (auto g = dyn_cast<memref::GlobalOp>(op)) {
        auto it = globalUseSites.find(g.getSymName());
        return it == globalUseSites.end() ? SmallVector<Value>()
                                          : it->second;
      }
      return op->getNumResults() ? SmallVector<Value>{op->getResult(0)}
                                 : SmallVector<Value>();
    };
    ChannelPorts channelPorts(seq, &instanceModel, sitesOf);
    ProcessMerges processMerges([&](Value v) {
      SmallVector<ChannelAccess> out;
      for (const AccessSummary &a : collectAccessSummaries({v}, &instanceModel))
        out.push_back({a.via ? a.via : a.op, a.isWrite});
      return out;
    });
    // The functions that hold a dataflow region (the function itself or one
    // of its loops): only their arrays, and globals, can be channels.
    llvm::DenseSet<Operation *> dataflowFuncs;
    module.walk([&](Operation *op) {
      if (op->hasAttr(kDataflowAttr))
        if (auto fn = isa<func::FuncOp>(op) ? cast<func::FuncOp>(op)
                                            : op->getParentOfType<func::FuncOp>())
          dataflowFuncs.insert(fn.getOperation());
    });
    auto mayBeChannel = [&](Operation *op) {
      if (dataflowFuncs.empty())
        return false;
      if (isa<memref::GlobalOp>(op))
        return true;
      auto fn = op->getParentOfType<func::FuncOp>();
      return fn && dataflowFuncs.contains(fn.getOperation());
    };
    module.walk([&](Operation *op) {
      auto iface = dyn_cast<MemoryResourceOpInterface>(op);
      if (!iface)
        return;
      if (!scope.covers(op)) {
        ++scope.skipped; // not reached from top=: no output, no cost
        return;
      }
      SmallVector<Value> banks;
      bool attributed;
      if (auto g = dyn_cast<memref::GlobalOp>(op)) {
        attributed = attributeGlobals;
        if (attributed) {
          auto it = globalSites.find(g.getSymName());
          if (it != globalSites.end())
            banks = it->second;
        }
      } else {
        attributed = op->getNumResults() > 0;
        if (attributed)
          banks.push_back(op->getResult(0));
      }
      MemrefRecord rec;
      describeMemref(op, index++, rec);
      SmallVector<Value> allSites;
      if (auto g = dyn_cast<memref::GlobalOp>(op)) {
        auto it = globalUseSites.find(g.getSymName());
        if (it != globalUseSites.end())
          allSites = it->second;
      } else {
        allSites = banks;
      }
      // An hls::stream object's storage is priced as the FIFOs it stands
      // for, never as a RAM.
      std::optional<StreamHandleRecord> fifo;
      if (streamFifos)
        fifo = analyzeStreamHandle(op, allSites, [&](int64_t depth,
                                                     unsigned bits) {
          // The mapper and port configuration of tool.hls.streams
          // (vitis-band7 at tdp: x18, never x36).
          return mapBlocks(*models.streamMapper, *models.block,
                           config().tool.hls.streams.pricedConfig, depth,
                           bits);
        });
      // A local array that one process of a dataflow region writes and a
      // later one reads is a ping-pong channel, never an ordinary memory.
      std::optional<BRAMCost> channel;
      if (!fifo && dataflowChannels && mayBeChannel(op))
        channel = tryDataflowChannel(iface, rec, allSites, seq, models,
                                     &instanceModel, channelPorts,
                                     processMerges);
      BRAMCost cost =
          fifo      ? estimateStreamFifos(iface, rec, std::move(*fifo))
          : channel ? *channel
                    : estimateBRAM(iface, rec, banks, attributed, seq,
                                   models, &instanceModel, allSites);
      // A ROM read by several kept functions: one copy per reading module
      // (VITIS_NOTES N136), each priced by its own readers' accesses.
      if (auto g = dyn_cast<memref::GlobalOp>(op);
          g && !fifo && !channel && attributed && rec.rom &&
          cost.bramCount > 0) {
        auto users = globalUsers.find(g.getSymName());
        if (users != globalUsers.end())
          if (auto plan = planRomModuleCopies(users->second, instanceModel)) {
            unsigned total = 0;
            std::string parts;
            for (const RomCopyPlan &copy : *plan) {
              SmallVector<Value> sites;
              for (Value site : banks)
                if (llvm::is_contained(
                        copy.readers,
                        site.getParentRegion()
                            ->getParentOfType<func::FuncOp>()))
                  sites.push_back(site);
              MemrefRecord tmp = rec;
              BRAMCost c = estimateBRAM(iface, tmp, sites, attributed, seq,
                                        models, &instanceModel, allSites);
              total += c.bramCount * copy.copies;
              std::string names;
              for (func::FuncOp f : copy.readers)
                names += (names.empty() ? "@" : ", @") + f.getName().str();
              rec.romModuleCopies.push_back(
                  {names, copy.where, copy.rule, copy.copies, c.bramCount});
              parts += (parts.empty() ? "" : " + ") +
                       std::to_string(copy.copies) + " x " +
                       std::to_string(c.bramCount) + " (" + copy.where + ")";
            }
            cost.note += "; one copy per reading module (N136): " + parts +
                         " = " + std::to_string(total);
            cost.bramCount = total;
            rec.bram = total;
          }
      }
      // Memories several memrefs share (tool.hls.grouping; identity: none).
      applyGrouping(op, rec, cost);
      // Charge once per instance of the owning module (N14 R1-R3). A
      // global that is written somewhere is one memory however many
      // instances its functions have: Vitis places it in a module with one
      // instance (N14 R9; W3 review D3: w3rev_k5, w3fx_d3_mix: `static int
      // t[1024]` of a callee with 2 instances, one RAM in the top). A
      // read-only one (a ROM) is duplicated per instance (inl_c4, w3rev_k2).
      unsigned instances = 1;
      bool sharedGlobal = false;
      if (auto g = dyn_cast<memref::GlobalOp>(op)) {
        auto it = globalUsers.find(g.getSymName());
        if (it != globalUsers.end()) {
          auto sites = globalUseSites.find(g.getSymName());
          bool written = !g.getConstant() && sites != globalUseSites.end() &&
                         !neverWritten(sites->second);
          if (written && instanceModel.ownerInstances(it->second) > 1) {
            sharedGlobal = true;
            if (func::FuncOp home =
                    instanceModel.singleInstanceOwner(it->second))
              rec.ownerFunc = home.getName().str();
          } else {
            instances = instanceModel.ownerInstances(it->second);
            if (func::FuncOp owner = instanceModel.owner(it->second))
              rec.ownerFunc = owner.getName().str();
          }
        }
      } else {
        instances = instanceModel.instancesAt(op);
      }
      rec.instances = instances;
      rec.bramPerInstance = cost.bramCount;
      if (instances != 1) {
        cost.bramCount *= instances;
        cost.note += " x " + std::to_string(instances) + " instance(s) of @" +
                     (rec.ownerFunc ? *rec.ownerFunc
                                    : (rec.func ? *rec.func : "?")) +
                     " = " + std::to_string(cost.bramCount) +
                     " (non-inlined callee, N14)";
        rec.bram = cost.bramCount;
      }
      if (sharedGlobal)
        cost.note += " (written static shared by every instance of its "
                     "functions: one memory in @" +
                     (rec.ownerFunc ? *rec.ownerFunc : std::string("?")) +
                     ", N14 R9)";
      // What it costs in the device's resource classes: the blocks of the
      // memory that priced it (a RAMB18 counts one BRAM_18K). The bram=
      // number is the primary class's count.
      const circt::hlsest::DeviceMemory *pricedBy =
          !rec.memoryId.empty() ? config().device.memory(rec.memoryId)
          : cost.bramCount     ? models.block
                               : nullptr;
      rec.resources = blockResources(pricedBy, cost.bramCount);
      unsigned primary = primaryCount(rec.resources);
      if (primary != cost.bramCount) {
        cost.bramCount = primary;
        rec.bram = primary;
      }
      llvm::outs() << op->getName() << " @ " << op->getLoc() << "\n"
                   << "  kind="
                   << (rec.fifo                      ? "FIFO"
                       : rec.pipo && rec.pipo->channel ? "PIPO"
                                                       : cost.label)
                   << "  " << resourceText(cost.bramCount, rec.resources)
                   << (cost.infeasible ? "  [INFEASIBLE]" : "") << "\n"
                   << "    " << cost.note << "\n";
      total += cost.bramCount;
      totalResources.add(rec.resources);
      records.push_back(std::move(rec));
    });
    // s_axilite array arguments of the top: a RAM in the control adapter
    // (VITIS_NOTES N176), one line each on stdout (no "kind=" token, as the
    // m_axi adapters), counted in the total.
    if (config().tool.hls.axiLiteArrayMemories)
      module.walk([&](func::FuncOp fn) {
        if (scope.active() ? fn.getName() != scope.symbol
                           : (fn.isPrivate() || fn.isExternal()))
          return;
        for (unsigned i = 0, e = fn.getNumArguments(); i < e; ++i) {
          auto ty = dyn_cast<MemRefType>(fn.getArgument(i).getType());
          auto ifaces = fn.getArgAttrOfType<ArrayAttr>(i, "hls.interface");
          if (!ty || !ty.hasStaticShape() ||
              !ty.getElementType().isIntOrFloat() || !ifaces)
            continue;
          std::string port;
          bool axiLite = false, otherMemory = false;
          for (Attribute a : ifaces)
            if (auto d = dyn_cast<DictionaryAttr>(a))
              if (auto mode = d.getAs<StringAttr>("mode")) {
                if (mode.getValue().equals_insensitive("s_axilite")) {
                  axiLite = true;
                  if (auto p = d.getAs<StringAttr>("port"))
                    port = p.getValue().str();
                } else {
                  otherMemory = true;
                }
              }
          // An array that is also an m_axi (or another memory) port: the
          // s_axilite entry is its address register in the control
          // adapter, not a memory (held-out utils stream_to_axi `wbuf`,
          // database scan_col `buf0` / `buf1`: no control_s_axi BRAM).
          if (!axiLite || otherMemory)
            continue;
          int64_t words = ty.getNumElements();
          unsigned bits = ty.getElementType().getIntOrFloatBitWidth();
          circt::hlsest::MemoryRequest request;
          request.words = words;
          request.writeWidth = bits;
          request.readWidths.push_back(bits);
          circt::hlsest::TierChoice choice =
              models.selector->select(request, config().device, {});
          MemrefRecord rec;
          int64_t bram = 0;
          if (!choice.memory.empty()) {
            const circt::hlsest::DeviceMemory *mem =
                config().device.memory(choice.memory);
            if (!mem)
              mem = models.block;
            bram = mapBlocks(*models.mapper, *mem,
                             config().tool.hls.memoryArchitecture.pricedNarrow,
                             words, bits, &rec.bankMath);
            rec.ramReason = "s_axilite array argument: a two-port RAM in the "
                            "control adapter (N176), " +
                            std::to_string(words) + "x" +
                            std::to_string(bits) + " at x18 bands";
          } else {
            rec.ramReason = "s_axilite array argument (N176): " +
                            std::to_string(words * bits) +
                            " bits, below the block tier: distributed RAM";
          }
          circt::hlsest::ResourceVector res =
              blockResources(models.block, static_cast<unsigned>(bram));
          totalResources.add(res);
          if (port.empty())
            port = "arg" + std::to_string(i);
          llvm::outs() << "s_axilite.array port=" << port << " func=@"
                       << fn.getName() << " bram=" << bram << " (" << words
                       << "x" << bits << "b)\n";
          total += static_cast<unsigned>(bram);
          rec.id = fn.getName().str() + "#s_axilite:" + port;
          rec.kind = "s_axilite_memory";
          rec.name = port;
          rec.varname = port;
          rec.func = fn.getName().str();
          rec.locText = locString(fn.getLoc());
          rec.shape = llvm::to_vector(ty.getShape());
          rec.elemType = "i" + std::to_string(bits);
          rec.elemBits = bits;
          rec.words = words;
          rec.status = bram ? "counted" : "excluded_small";
          rec.ramType = "S_AXILITE_RAM";
          rec.bram = static_cast<unsigned>(bram);
          rec.resources = res;
          records.push_back(std::move(rec));
        }
      });
    // m_axi adapters: one line each on stdout (no "kind=" token, so report
    // parsers do not mistake it for a memref), counted in the total.
    if (maxiAdapters)
      for (auto &[fn, a] : collectAdapters(module, models)) {
        if (scope.active() && fn.getName() != scope.symbol)
          continue; // only the top's interface is synthesized as m_axi
        unsigned bram = a.readBram + a.writeBram;
        circt::hlsest::ResourceVector adapterResources =
            blockResources(models.block, bram);
        totalResources.add(adapterResources);
        llvm::outs() << "m_axi.adapter bundle=" << a.bundle << " func=@"
                     << fn.getName() << " bram=" << bram << " (read FIFO ";
        if (a.readChannels > 1)
          llvm::outs() << a.readChannels << "x";
        llvm::outs() << a.readDepth << "x" << a.readBits << "b -> "
                     << a.readBram << ", write burst " << a.writeBurst
                     << " -> " << a.writeBram << ")\n";
        total += bram;
        MemrefRecord rec;
        rec.id = fn.getName().str() + "#m_axi:" + a.bundle;
        rec.kind = "m_axi_adapter";
        rec.name = a.bundle;
        rec.varname = a.bundle + "_m_axi";
        rec.func = fn.getName().str();
        rec.locText = locString(fn.getLoc());
        if (auto f = findFileLoc(fn.getLoc())) {
          rec.hasLoc = true;
          rec.locFile = f.getFilename().str();
          rec.locLine = f.getLine();
          rec.locCol = f.getColumn();
        }
        rec.shape = {a.readDepth};
        rec.elemType = "i" + std::to_string(a.busBits);
        rec.elemBits = a.busBits;
        rec.words = a.readDepth;
        rec.status = "counted";
        rec.ramType = "M_AXI_ADAPTER";
        rec.ramReason = "read FIFO: " + a.readRule + "; write buffer: " +
                        a.writeRule;
        rec.bram = bram;
        rec.resources = adapterResources;
        rec.adapter = std::move(a);
        records.push_back(std::move(rec));
      }
    // The `<arg>_c` FIFOs of a dataflow top (VITIS_NOTES N54): one line each
    // on stdout (no "kind=" token, as the adapters), counted in the total.
    if (streamFifos && config().tool.hls.streams.dataflowArgumentFifos)
      module.walk([&](func::FuncOp fn) {
        if (scope.active() && fn.getName() != scope.symbol)
          return; // the top's arguments only (kernels w9r7_sc_*)
        for (DataflowArgumentFifo &f : processMerges.argumentFifos(fn)) {
          FifoPrice p = priceFifo(f.depth, f.bits, "", [&](int64_t depth,
                                                           unsigned bits) {
            return mapBlocks(*models.streamMapper, *models.block,
                             config().tool.hls.streams.pricedConfig, depth,
                             bits);
          });
          circt::hlsest::ResourceVector res =
              blockResources(models.block, p.bram);
          totalResources.add(res);
          llvm::outs() << "dataflow.arg_fifo name=" << f.name << " func=@"
                       << fn.getName() << " bram=" << p.bram << " (depth "
                       << f.depth << " x " << f.bits << "b)\n";
          total += p.bram;
          MemrefRecord rec;
          rec.id = fn.getName().str() + "#arg_fifo:" + f.name;
          rec.kind = "dataflow_arg_fifo";
          rec.name = f.name;
          rec.varname = f.name;
          rec.func = fn.getName().str();
          rec.locText = locString(fn.getLoc());
          rec.shape = {f.depth};
          rec.elemType = "i" + std::to_string(f.bits);
          rec.elemBits = f.bits;
          rec.words = f.depth;
          rec.status = "counted";
          rec.ramType = "FIFO";
          rec.ramReason = "dataflow argument FIFO (N54): " + f.reason + "; " +
                          p.reason;
          rec.bram = p.bram;
          rec.resources = res;
          records.push_back(std::move(rec));
        }
      });
    // hls:: math cores (math-costs=; MathCores.h): one line each on stdout (no
    // "kind=" token, as the adapters), counted in the total. Only the
    // functions top= reaches.
    if (!mathCostsPath.empty())
      for (MathCoreRecord &m : analyzeMathCores(
               module, mathCosts,
               [&](Operation *op) { return scope.covers(op); },
               [&](Operation *fn) {
                 return instanceModel.instancesOf(cast<func::FuncOp>(fn));
               },
               [&](Location loc, const std::string &msg) {
                 mlir::emitWarning(loc) << "--bram-analysis: math-costs: "
                                        << msg;
               },
               // A core's ROM table (VITIS_NOTES N106), read `reads` times
               // per cycle (N16 R6: the concurrent calls of an inlined core
               // share it), priced like a ROM of the design: the storage
               // selector's tier, the memory policy's ROM plan (one read: the
               // wide port configuration; more than two: copies, N8).
               [&](int64_t words, unsigned bits, unsigned reads) -> int64_t {
                 circt::hlsest::MemoryRequest rom;
                 rom.words = words;
                 rom.writeWidth = bits;
                 rom.readWidths.push_back(bits);
                 rom.readOnly = true;
                 rom.needsInit = true;
                 circt::hlsest::TierChoice c =
                     models.selector->select(rom, config().device, {});
                 const circt::hlsest::DeviceMemory *mem =
                     c.memory.empty() ? nullptr
                                     : config().device.memory(c.memory);
                 if (!mem)
                   return 0;
                 if (reads <= 1)
                   return mapBlocks(
                       *models.mapper, *mem,
                       config().tool.hls.memoryArchitecture.pricedWide, words,
                       bits);
                 PortDemand demand;
                 demand.reads = demand.total = reads;
                 ReplicationRecord rep;
                 circt::hlsest::PlanContext ctx;
                 circt::hlsest::MemoryPlan plan =
                     models.policy->plan(demand, rep, rom, ctx);
                 return mapBlocks(*models.mapper, *mem, plan.pricedConfig,
                                  words, bits) *
                        std::max<int64_t>(1, plan.copies);
               })) {
        printMathCoreLine(m, llvm::outs());
        total += m.bram;
        MemrefRecord mr = mathCoreDebugRecord(std::move(m));
        mr.resources.add(config().tool.report.primaryMemoryClass,
                         circt::hlsest::Rational(mr.bram));
        totalResources.add(mr.resources);
        records.push_back(std::move(mr));
      }
    // tool.report.stdout_format: vitis-bram prints the primary class's total
    // as "Total BRAM", per-class one total per reported class.
    if (config().tool.report.stdoutFormat != "per-class")
      llvm::outs() << "Total BRAM: " << total << "\n";
    else
      for (const std::string &cls : config().tool.report.classes)
        llvm::outs() << "Total " << cls << ": "
                     << totalResources.get(cls).str() << "\n";
    if (bramDebugOpt || !bramDebugJsonOpt.empty()) {
      size_t first = records.size();
      appendDeadRecords(module, index, records);
      if (scope.active())
        records.erase(
            std::remove_if(records.begin() + first, records.end(),
                           [&](const MemrefRecord &r) {
                             return r.func &&
                                    !scope.funcNames.contains(*r.func);
                           }),
            records.end());
    }

    // Debug output only; nothing above depends on these flags. The estimate
    // and the stdout report are complete by now; a JSON path that cannot be
    // opened is still an error (non-zero exit), so a harness that asked for
    // the file never mistakes its absence for an empty result.
    std::vector<PipelineRecord> pipelines;
    if (bramDebugOpt || !bramDebugJsonOpt.empty())
      pipelines = collectPipelineRecords(getOperation(), scope);
    SmallVector<InstanceRecord> instanceRecords;
    if (bramDebugOpt || !bramDebugJsonOpt.empty())
      instanceRecords = collectInstanceRecords(instanceModel);
    FoldSummary fold;
    if (bramDebugOpt || !bramDebugJsonOpt.empty())
      fold = collectFoldSummary(module, scope);
    if (bramDebugOpt)
      printDebugText(records, pipelines, instanceRecords, total, fold,
                     *models.mapper, scope, llvm::errs());
    if (models.failed)
      signalPassFailure();
    if (!bramDebugJsonOpt.empty())
      if (std::error_code ec = writeDebugJson(
              records, pipelines, instanceRecords, total, fold,
              *models.mapper, llvm::json::Value(llvm::json::Object(pluginRecord)),
              totalResources.toJson(), functionPipelinesJson, scope,
              bramDebugJsonOpt)) {
        // Location-based emitError: no "see current operation" module dump.
        mlir::emitError(getOperation().getLoc(),
                        "bram-debug-json: cannot write '")
            << bramDebugJsonOpt << "': " << ec.message();
        signalPassFailure();
      }
  }
};

} // namespace

namespace circt::hls_analysis {

std::unique_ptr<Pass> createBRAMAnalysisPass() {
  return std::make_unique<BRAMAnalysisLoopSchedule>();
}

void registerBRAMLoopscheduleAnalysisPass() {
  PassRegistration<BRAMAnalysisLoopSchedule>();
}
}
