

#include "circt/Dialect/Resource/Passes/BRAMAnalysis.h"
#include "circt/Dialect/LoopSchedule/LoopScheduleOps.h"
#include "circt/Dialect/Resource/Config/ConfigUtils.h"
#include "circt/Dialect/Resource/HLS/HLSOps.h"
#include "circt/Dialect/Resource/Interfaces/MemoryInterface.h"
#include "circt/Dialect/Resource/Model/AccessOrder.h"
#include "circt/Dialect/Resource/Passes/CallInstances.h"
#include "circt/Dialect/Resource/Passes/DataflowChannels.h"
#include "circt/Dialect/Resource/Passes/FoldUnrolledGuards.h"
#include "circt/Dialect/Resource/Passes/LoopPragmas.h"
#include "circt/Dialect/Resource/Passes/MathCores.h"
#include "circt/Dialect/Resource/Passes/MemoryRecurrences.h"
#include "circt/Dialect/Resource/Passes/MemrefBankClassification.h"
#include "circt/Dialect/Resource/Passes/PolygeistCompat.h"
#include "circt/Dialect/Resource/Passes/ReadOnlyMemory.h"
#include "circt/Dialect/Resource/Passes/StreamFifos.h"
#include "circt/Dialect/Resource/Plugins/MemoryInterfaces.h"
#include "circt/Dialect/Resource/Plugins/PassPolicies.h"
#include "circt/Dialect/Resource/Plugins/Registry.h"
#include "circt/Dialect/Resource/Plugins/Scheduling.h"
#include "mlir/Dialect/Affine/IR/AffineOps.h"
#include "mlir/Dialect/Arith/IR/Arith.h"
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
#include "llvm/Support/Format.h"
#include "llvm/Support/FormatVariadic.h"
#include "llvm/Support/JSON.h"
#include "llvm/Support/MathExtras.h"
#include "llvm/Support/raw_ostream.h"

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

using circt::hlsest::Config;

const Config &config() { return Config::get(); }

/// Bits of one block of the mapped primitive (18432 for a RAMB18E1).
int64_t bitsPerBlock() {
  const circt::hlsest::DeviceMemory *memoryOp = config().blockMemory();
  return memoryOp ? memoryOp->bits : 0;
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
  std::unique_ptr<circt::hlsest::MemoryMapper> mapper;       ///< user arrays
  std::unique_ptr<circt::hlsest::MemoryMapper> streamMapper; ///< stream FIFOs
  std::unique_ptr<circt::hlsest::MemoryMapper> fifoMapper; ///< m_axi read FIFO
  std::unique_ptr<circt::hlsest::ImplicitBufferModel> buffers; ///< m_axi
  std::unique_ptr<circt::hlsest::MemoryGrouping> grouping;
  const circt::hlsest::DeviceMemory *block =
      nullptr; ///< the mapper's primitive
  /// A bank could not be priced (an error was emitted); the pass fails after
  /// the report.
  mutable bool failed = false;
};

struct TopScope {
  std::string symbol;
  llvm::DenseSet<Operation *> funcs;
  llvm::DenseSet<StringRef> funcNames;
  llvm::DenseSet<StringRef> globals;
  unsigned skipped = 0;

  bool active() const { return !symbol.empty(); }

  bool covers(Operation *op) const {
    if (!active())
      return true;
    if (auto g = dyn_cast<memref::GlobalOp>(op))
      return globals.contains(g.getSymName());
    auto fn = op->getParentOfType<func::FuncOp>();
    return fn && funcs.contains(fn.getOperation());
  }
};

struct AccessRecord {
  std::string op;
  bool isWrite = false;
  std::string scopeKind;
  std::string scopeLoc;
  unsigned ii = 0;
  unsigned stageStart = 0;
  bool storeEnable = false;

  unsigned mergedLoads = 0;
  unsigned forwardedLoads = 0;
  unsigned removedStores = 0;

  unsigned registerPromoted = 0;

  unsigned mergedIfElseStores = 0;

  bool hoistedConditional = false;

  std::string portBank;
  Operation *scope = nullptr;

  std::string inFunc;
  std::optional<std::string> viaCall;

  bool portBound = false;
  std::string portBoundReason;
};

struct ScopeDemandRecord {
  std::string scopeKind;
  std::string scopeLoc;
  unsigned ii = 0;
  PortDemand demand;

  std::optional<std::string> sameState;
};

struct PartitionRecord {
  bool present = false;
  bool applied = false;
  std::string kind, source;

  int64_t factor = 0, dim = 0;
  std::optional<int64_t> bankIndex, bankCount;
  std::optional<std::string> reason;

  SmallVector<std::tuple<std::string, int64_t, int64_t>> dims;

  std::optional<std::string> from;

  SmallVector<int64_t> steeredGroups;
  std::optional<int64_t> forwardedReloads;
};

struct BankMathRecord {
  bool present = false;
  int64_t bitsPerBram = bitsPerBlock();
  bool wide = false;
  unsigned maxWidth = 0;
  unsigned configWidth = 0;
  int64_t widthTiles = 0;
  int64_t depthPerBlock = 0;
  int64_t addrDepth = 0;
  int64_t depthTiles = 0;
  int64_t blocksPerCopy = 0;
  int64_t replication = 1;
  int64_t blocks = 0;
  std::string formula;
  std::string band;
};

using AdapterRecord = circt::hlsest::ImplicitBuffer;

struct PipoRecord {
  bool channel = false;
  std::string notChannelReason;
  std::string region, regionKind;
  SmallVector<DataflowProcess> processes;
  int64_t blocks = 0;
  std::string blocksSource;
  std::string bindType, bindImpl;

  std::string secondPort;
  std::string mode, modeReason, rule;
};

struct MemrefRecord {
  std::string id;
  std::optional<std::string> name;
  std::optional<std::string> varname;
  std::optional<std::string> fromGlobal;

  std::optional<std::string> structMember;

  std::optional<std::string> aggregated;

  std::optional<std::string> keptReason;

  struct NarrowRecord {
    unsigned declaredBits = 0;
    unsigned bits = 0;
    std::string reason;
  };
  std::optional<NarrowRecord> narrow;
  std::string kind;
  std::optional<std::string> func;
  bool hasLoc = false;
  std::string locFile;
  unsigned locLine = 0, locCol = 0;
  std::string locText;

  SmallVector<int64_t> shape;
  std::string elemType;
  unsigned elemBits = 0;
  std::optional<int64_t> words;

  std::string status;
  std::optional<std::string> excludeReason;

  PartitionRecord partition;
  std::vector<AccessRecord> accesses;

  struct RegisterServed {
    std::string op, rw, loc, rule;
  };
  std::vector<RegisterServed> registerServed;
  bool accessesAttributed = false;
  bool rom = false;
  std::optional<AdapterRecord> adapter;
  std::optional<MathCoreRecord> math;
  std::optional<StreamHandleRecord> fifo;
  std::optional<PipoRecord> pipo;
  PortDemand demand;
  SmallVector<ScopeDemandRecord> perScope;

  std::string ramType;
  std::string ramReason;
  ReplicationRecord replication;
  BankMathRecord bankMath;
  unsigned bram = 0;

  std::string memoryId;
  std::string storageTier;
  circt::hlsest::ResourceVector resources;
  bool infeasible = false;

  unsigned instances = 1;
  unsigned bramPerInstance = 0;
  std::optional<std::string> ownerFunc;
};

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

    SmallVector<std::pair<std::string, unsigned>> sites;
  };
  SmallVector<Parent> parents;
};

/// The sequential-scope rule of the memory architecture policy and its
/// per-scope index (null when the policy counts one access per state).
struct SeqContext {
  SeqScopeIndex index;
  const circt::hlsest::MemoryArchitecturePolicy *policy = nullptr;
};

static std::optional<PortDemand>
perStateDemand(ArrayRef<const AccessSummary *> group) {
  std::map<int64_t, std::pair<unsigned, unsigned>> perState;
  for (const AccessSummary *a : group) {
    auto state = a->op->getAttrOfType<IntegerAttr>("hls.state");
    if (!state)
      return std::nullopt;
    auto &rw = perState[state.getInt()];
    (a->isWrite ? rw.second : rw.first)++;
  }
  PortDemand dimensionIndex;
  for (const auto &[state, rw] : perState) {
    dimensionIndex.reads = std::max(dimensionIndex.reads, rw.first);
    dimensionIndex.writes = std::max(dimensionIndex.writes, rw.second);
    dimensionIndex.total = std::max(dimensionIndex.total, rw.first + rw.second);
  }
  return dimensionIndex;
}

PortDemand scopeDemand(ArrayRef<const AccessSummary *> group,
                       SeqContext *seq = nullptr, std::string *note = nullptr) {
  PortDemand dimensionIndex;
  if (group.empty())
    return dimensionIndex;

  unsigned ii = group.front()->ii;
  assert(llvm::all_of(group, [&](auto *a) { return a->ii == ii; }) &&
         "scopeDemand requires a single-II group; bucket by scope first");

  if (ii == 0)
    if (std::optional<PortDemand> scheduled = perStateDemand(group))
      return *scheduled;
  if (ii == 0 && seq)
    return seq->policy->sequentialScopeDemand(group, seq->index, note);
  if (ii == 0) {
    bool anyR = false, anyW = false;
    for (const auto *a : group)
      (a->isWrite ? anyW : anyR) = true;
    dimensionIndex.reads = anyR ? 1u : 0u;
    dimensionIndex.writes = anyW ? 1u : 0u;
    dimensionIndex.total = (anyR || anyW) ? 1u : 0u;
    return dimensionIndex;
  }

  std::vector<std::pair<unsigned, unsigned>> slot(ii, {0u, 0u});
  for (const auto *a : group) {
    unsigned occ = std::max(a->latency, 1u);
    for (unsigned candidateValue = 0; candidateValue < occ; ++candidateValue) {
      unsigned phase = (a->stageStart + candidateValue) % ii;
      (a->isWrite ? slot[phase].second : slot[phase].first)++;
    }
  }

  for (const auto &cell : slot) {
    unsigned resultValue = cell.first, widthValue = cell.second;
    dimensionIndex.reads = std::max(dimensionIndex.reads, resultValue);
    dimensionIndex.writes = std::max(dimensionIndex.writes, widthValue);
    dimensionIndex.total =
        std::max(dimensionIndex.total, resultValue + widthValue);
  }

  return dimensionIndex;
}

static unsigned
sequentialRomReads(ArrayRef<AccessSummary> accesses, SeqContext *seq,
                   const circt::hlsest::MemoryArchitecturePolicy &policy) {
  if (!seq)
    return 0;
  std::map<Operation *, SmallVector<const AccessSummary *>> byScope;
  for (const AccessSummary &a : accesses)
    if (!a.isWrite && a.ii == 0 && !a.op->hasAttr("hls.state"))
      byScope[a.scope].push_back(&a);
  unsigned elementCount = 0;
  for (auto &[scope, group] : byScope)
    if (group.size() > 2)
      elementCount =
          std::max(elementCount, policy.sequentialRomReads(group, seq->index));
  return elementCount;
}

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

int64_t ceilDiv(int64_t a, int64_t buildPoint) {
  return (a + buildPoint - 1) / buildPoint;
}

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
    return 0;
  circt::hlsest::MemoryRequest request;
  request.words = words;
  request.writeWidth = bits;
  request.readWidths.push_back(bits);
  circt::hlsest::MappingTrace trace;
  circt::hlsest::Mapping memoryOp =
      mapper.map(request, memory, *priced, &trace);
  if (bm) {
    bm->present = true;
    bm->bitsPerBram = trace.bitsPerBlock;
    bm->wide = pricedConfig == config().tool.hls.memoryArchitecture.pricedWide;
    bm->maxWidth = trace.maxWidth;
    bm->formula = mapper.reportLabel().str();
    bm->band = memoryOp.band;
    if (words > 0 && bits > 0) {
      bm->configWidth = memoryOp.configWidth;
      bm->widthTiles = memoryOp.widthTiles;
      bm->depthPerBlock = memoryOp.depthPerBlock;
      bm->addrDepth = memoryOp.addrDepth;
      bm->depthTiles = memoryOp.depthTiles;
      bm->blocksPerCopy = memoryOp.blocks;
      bm->replication = 1;
      bm->blocks = memoryOp.blocks;
    }
  }
  return memoryOp.blocks;
}

/// `blocks` blocks of `memory` per resource class (cost + overhead).
circt::hlsest::ResourceVector
blockResources(const circt::hlsest::DeviceMemory *memory, int64_t blocks) {
  circt::hlsest::ResourceVector resultValue;
  if (!memory || blocks <= 0)
    return resultValue;
  resultValue.add(memory->cost);
  resultValue.add(memory->overhead);
  return resultValue.scaled(circt::hlsest::Rational(blocks));
}

/// The count of tool.report.primary_memory_class (the bram= number), whole
/// blocks.
unsigned primaryCount(const circt::hlsest::ResourceVector &resultValue) {
  return static_cast<unsigned>(
      resultValue.get(config().tool.report.primaryMemoryClass).ceil());
}

/// What a report line says the memory costs: "bram=<n>" (stdout_format
/// vitis-bram), or "<class>=<n>" per class (per-class).
std::string resourceText(unsigned bram,
                         const circt::hlsest::ResourceVector &resultValue) {
  if (config().tool.report.stdoutFormat != "per-class" || resultValue.empty())
    return "bram=" + std::to_string(bram);
  std::string out;
  for (const auto &[cls, elementCount] : resultValue.items()) {
    if (!out.empty())
      out += " ";
    out += cls + "=" + elementCount.str();
  }
  return out;
}

unsigned portOccupancy(bool) {

  return static_cast<unsigned>(
      config().tool.hls.memoryArchitecture.portOccupancyCycles);
}

Operation *sequentialScope(Operation *op) {
  for (Operation *cur = op->getParentOp(); cur; cur = cur->getParentOp())
    if (isa<LoopLikeOpInterface>(cur))
      return cur;
  if (auto fn = op->getParentOfType<func::FuncOp>())
    return fn.getOperation();
  return nullptr;
}

static void
collectAccessesFrom(Value mem, Operation *via, StringRef portBoundReason,
                    const InstanceModel *model,
                    DenseSet<std::pair<Operation *, unsigned>> &visitedArgs,
                    DenseSet<Operation *> &seen,
                    SmallVectorImpl<AccessSummary> &out) {
  for (OpOperand &use : mem.getUses()) {
    Operation *user = use.getOwner();
    if (auto call = dyn_cast<CallOpInterface>(user)) {
      func::FuncOp callee = resolveDefinedCallee(call);
      if (!callee)
        continue;
      std::optional<unsigned> indexValue = callArgIndex(call, use);
      if (!indexValue || *indexValue >= callee.getNumArguments())
        continue;
      if (!visitedArgs.insert({callee.getOperation(), *indexValue}).second)
        continue;
      StringRef reason = portBoundReason;
      if (reason.empty() && model)
        reason = model->calleeArgPortBoundReason(callee, *indexValue);
      collectAccessesFrom(callee.getArgument(*indexValue), via ? via : user,
                          reason, model, visitedArgs, seen, out);
      continue;
    }
    if (auto view = dyn_cast<ViewLikeOpInterface>(user))
      if (view.getViewSource() == mem) {
        for (Value resultValue : user->getResults())
          if (isa<BaseMemRefType>(resultValue.getType()))
            collectAccessesFrom(resultValue, via, portBoundReason, model,
                                visitedArgs, seen, out);
        continue;
      }
    bool isWrite = false;
    if (!classifyAccess(user, mem, isWrite))
      continue;

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
      a.stageStart = stage ? static_cast<unsigned>(stage.getStart()) : 0u;
    } else {

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
    collectAccessesFrom(mem, nullptr, "", model, visitedArgs, seen, out);
  return out;
}

using circt::hls_analysis::neverWritten;

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
  StringRef elementCount = op->getName().getStringRef();
  return elementCount == "hls.store_enable" ||
         elementCount == "hls.affine.store_enable";
}

static unsigned counterAttr(Operation *op, StringRef name) {
  if (auto a = op->getAttrOfType<IntegerAttr>(name))
    return a.getInt() > 0 ? static_cast<unsigned>(a.getInt()) : 0u;
  return 0;
}

static void describeMemref(Operation *op, unsigned index,
                           MemrefRecord &resultValue) {
  StringRef opName = op->getName().getStringRef();
  if (auto g = dyn_cast<memref::GlobalOp>(op)) {
    resultValue.kind = "global";
    resultValue.name = g.getSymName().str();
    resultValue.id = "global#" + std::to_string(index);
  } else {
    resultValue.kind = opName.starts_with("memref.")
                           ? opName.drop_front(7).str()
                           : opName.str();
    if (auto fn = op->getParentOfType<func::FuncOp>())
      resultValue.func = fn.getName().str();
    resultValue.id = (resultValue.func ? *resultValue.func : std::string("?")) +
                     "#" + std::to_string(index);
  }

  if (auto valueHandle = op->getAttrOfType<StringAttr>("polygeist.varname"))
    resultValue.varname = valueHandle.getValue().str();
  else if (auto buildPoint = op->getAttrOfType<StringAttr>("hls.bank_of"))
    resultValue.varname = buildPoint.getValue().str();
  if (auto g = op->getAttrOfType<StringAttr>("hls.from_global"))
    resultValue.fromGlobal = g.getValue().str();
  if (auto memoryOp = op->getAttrOfType<StringAttr>("hls.struct_member"))
    resultValue.structMember = memoryOp.getValue().str();
  if (auto memoryOp = op->getAttrOfType<StringAttr>("hls.aggregated"))
    resultValue.aggregated = memoryOp.getValue().str();
  if (auto keyValue = op->getAttrOfType<StringAttr>("hls.kept_reason"))
    resultValue.keptReason = keyValue.getValue().str();

  if (auto fieldValue = findFileLoc(op->getLoc())) {
    resultValue.hasLoc = true;
    resultValue.locFile = fieldValue.getFilename().str();
    resultValue.locLine = fieldValue.getLine();
    resultValue.locCol = fieldValue.getColumn();
  }
  resultValue.locText = locString(op->getLoc());

  PartitionRecord &portValue = resultValue.partition;
  auto readFields = [&](DictionaryAttr dimensionIndex) {
    if (auto keyValue = dimensionIndex.getAs<StringAttr>("kind"))
      portValue.kind = keyValue.getValue().str();
    if (auto fieldValue = dimensionIndex.getAs<IntegerAttr>("factor"))
      portValue.factor = fieldValue.getInt();
    if (auto dm = dimensionIndex.getAs<IntegerAttr>("dim"))
      portValue.dim = dm.getInt();
    if (auto stringValue = dimensionIndex.getAs<StringAttr>("source"))
      portValue.source = stringValue.getValue().str();
    else
      portValue.source = "pragma";
  };
  if (auto dimensionIndex =
          op->getAttrOfType<DictionaryAttr>("hls.partition")) {
    portValue.present = true;
    portValue.applied = true;
    readFields(dimensionIndex);
    if (auto bi = op->getAttrOfType<IntegerAttr>("hls.bank_index"))
      portValue.bankIndex = bi.getInt();
    if (auto bc = op->getAttrOfType<IntegerAttr>("hls.bank_count"))
      portValue.bankCount = bc.getInt();
    if (auto all = dimensionIndex.getAs<ArrayAttr>("dims"))
      for (Attribute a : all)
        if (auto dd = dyn_cast<DictionaryAttr>(a)) {
          auto keyValue = dd.getAs<StringAttr>("kind");
          auto fieldValue = dd.getAs<IntegerAttr>("factor");
          auto dm = dd.getAs<IntegerAttr>("dim");
          if (keyValue && fieldValue && dm)
            portValue.dims.push_back(
                {keyValue.getValue().str(), fieldValue.getInt(), dm.getInt()});
        }
    if (auto from = dimensionIndex.getAs<StringAttr>("from"))
      portValue.from = from.getValue().str();
  } else if (auto arr = op->getAttrOfType<ArrayAttr>("hls.array_partition")) {
    if (!arr.empty())
      if (auto dimensionIndex = dyn_cast<DictionaryAttr>(arr[0])) {
        portValue.present = true;
        portValue.applied = false;
        readFields(dimensionIndex);
      }
  }
  if (auto reason = op->getAttrOfType<StringAttr>("hls.partition_reason"))
    portValue.reason = reason.getValue().str();
  if (auto st = op->getAttrOfType<DictionaryAttr>("hls.steering")) {
    if (auto g = st.getAs<DenseI64ArrayAttr>("groups"))
      portValue.steeredGroups.assign(g.asArrayRef().begin(),
                                     g.asArrayRef().end());
    if (auto fieldValue = st.getAs<IntegerAttr>("forwarded_reloads"))
      portValue.forwardedReloads = fieldValue.getInt();
  }
}

static void recordAccesses(ArrayRef<AccessSummary> accesses,
                           MemrefRecord &resultValue, SeqContext *seq) {
  resultValue.accesses.clear();
  resultValue.perScope.clear();
  SmallVector<Operation *> scopeOrder;
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
    if (auto buildPoint = a.op->getAttrOfType<IntegerAttr>("hls.port_bank"))
      ar.portBank = std::to_string(buildPoint.getInt());
    else if (auto elementCount =
                 a.op->getAttrOfType<IntegerAttr>("hls.port_banks"))
      ar.portBank = "any of " + std::to_string(elementCount.getInt());
    if (auto fn = a.op->getParentOfType<func::FuncOp>())
      ar.inFunc = fn.getName().str();
    if (a.via) {
      std::string valueHandle = "call";

      if (auto call = dyn_cast<CallOpInterface>(a.via))
        if (auto symbolName = dyn_cast_or_null<SymbolRefAttr>(
                call.getCallableForCallee().dyn_cast<SymbolRefAttr>()))
          valueHandle += " @" + symbolName.getLeafReference().str();
      ar.viaCall = valueHandle + " @ " + locString(a.via->getLoc());
    }
    ar.portBound = a.portBound;
    ar.portBoundReason = a.portBoundReason.str();
    resultValue.accesses.push_back(std::move(ar));
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
    resultValue.perScope.push_back(std::move(sd));
  }
}

static unsigned narrowRomWidth(ArrayRef<APInt> vals) {
  bool anyNegative = llvm::any_of(
      vals, [](const APInt &valueHandle) { return valueHandle.isNegative(); });
  unsigned width = 0;
  if (anyNegative) {
    for (const APInt &valueHandle : vals)
      width = std::max(width, valueHandle.getSignificantBits());
    return width;
  }
  unsigned a = 0;
  for (const APInt &valueHandle : vals)
    a = std::max(a, valueHandle.getActiveBits());
  if (a == 0)
    return 0;
  for (const APInt &valueHandle : vals)
    width = std::max(width, valueHandle.trunc(a).getSignificantBits());
  return width;
}

static unsigned applyNarrowWidth(Operation *op, MemrefRecord &rec) {
  rec.narrow.reset();
  auto bits = op->getAttrOfType<IntegerAttr>(kNarrowBitsAttrName);
  if (!bits || bits.getInt() <= 0 ||
      static_cast<uint64_t>(bits.getInt()) >= rec.elemBits)
    return rec.elemBits;
  MemrefRecord::NarrowRecord elementCount;
  elementCount.declaredBits = rec.elemBits;
  elementCount.bits = static_cast<unsigned>(bits.getInt());
  if (auto why = op->getAttrOfType<StringAttr>(kNarrowReasonAttrName))
    elementCount.reason = why.getValue().str();
  rec.narrow = std::move(elementCount);
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
  for (int64_t dimensionIndex : rec.shape)
    if (!ShapedType::isDynamic(dimensionIndex))
      words *= dimensionIndex;
  rec.words = words;
  BRAMCost cost;
  cost.kind = StorageKind::RAM_1P;
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
  cost.note = "hls::stream storage, not a RAM: " + std::to_string(fifo.fifos) +
              " FIFO(s) = " + std::to_string(fifo.bram) + " BRAM [" + groups +
              "]";
  if (!fifo.note.empty())
    cost.note += " (" + fifo.note + ")";
  rec.status = "fifo";
  rec.ramType = "FIFO";
  rec.ramReason = "hls::stream FIFOs: " + groups;
  rec.bram = cost.bramCount;
  rec.fifo = std::move(fifo);
  return cost;
}

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

static bool onExclusivePaths(Operation *a, Operation *buildPoint,
                             Operation *scope) {
  SeqScopeIndex::OpInfo exprValue, rowValue;
  exprValue.arms = nestedArms(a, scope);
  rowValue.arms = nestedArms(buildPoint, scope);
  return inExclusiveArms(exprValue, hoistedArmsOf(a), rowValue,
                         hoistedArmsOf(buildPoint));
}

static std::string sameCycleAccesses(ArrayRef<AccessSummary> accesses,
                                     SeqContext *seq) {
  using ProcessScope = std::pair<Operation *, Operation *>;
  SmallVector<ProcessScope> scopes;
  for (const AccessSummary &a : accesses)
    if (!llvm::is_contained(scopes, ProcessScope{a.via, a.scope}))
      scopes.push_back({a.via, a.scope});
  for (auto [via, scope] : scopes) {
    SmallVector<const AccessSummary *> group;
    for (const AccessSummary &a : accesses)
      if (a.scope == scope && a.via == via)
        group.push_back(&a);
    if (group.size() < 2)
      continue;
    unsigned ii = group.front()->ii;
    if (ii == 0) {
      if (!seq)
        continue;
      std::string note;
      if (seq->policy->sequentialScopeDemand(group, seq->index, &note).total >=
          2)
        return "non-pipelined scope, " + note;
      continue;
    }
    for (size_t loopIndex = 0; loopIndex < group.size(); ++loopIndex)
      for (size_t innerIndex = loopIndex + 1; innerIndex < group.size();
           ++innerIndex) {
        const AccessSummary *a = group[loopIndex],
                            *buildPoint = group[innerIndex];
        if (onExclusivePaths(a->op, buildPoint->op, scope))
          continue;
        if (!a->isWrite && !buildPoint->isWrite &&
            compareAddresses(a->op, buildPoint->op) == AddrRelation::Same)
          continue;
        return "pipelined scope (II " + std::to_string(ii) +
               "), one control "
               "path of one iteration: " +
               accessText(a) + " + " + accessText(buildPoint);
      }
  }
  return {};
}

static BRAMCost estimateChannel(MemoryResourceOpInterface iface,
                                MemrefRecord &rec, const DataflowChannel &ch,
                                ArrayRef<AccessSummary> accesses,
                                SeqContext *seq, const Models &models,
                                const std::string &secondPort) {
  rec.shape = iface.getStaticShape();
  Type elt = iface.getElementType();
  {
    llvm::raw_string_ostream os(rec.elemType);
    elt.print(os);
  }
  rec.elemBits = elt.getIntOrFloatBitWidth();
  unsigned pricedBits = applyNarrowWidth(iface.getOperation(), rec);
  int64_t words = 1;
  for (int64_t dimensionIndex : rec.shape)
    words *= dimensionIndex;
  rec.words = words;
  rec.accessesAttributed = true;

  PipoRecord portValue;
  portValue.channel = true;
  portValue.region = ch.regionName;
  portValue.regionKind = ch.regionKind;
  portValue.processes = ch.processes;
  portValue.blocks = ch.blocks;
  portValue.blocksSource = ch.blocksSource;
  portValue.bindType = ch.bindType;
  portValue.bindImpl = ch.bindImpl;
  portValue.secondPort = secondPort;
  bool twoPorts = !portValue.secondPort.empty();
  bool bound2p = ch.bindType == "ram_2p" || ch.bindType == "ram_s2p";

  bool onePortPerSide = ch.bindType == "ram_1p" || ch.bindType == "ram_s2p";
  std::string clamped;
  if (twoPorts && onePortPerSide) {
    clamped = "; bind_storage type=" + ch.bindType +
              " has one port per side, so the second access waits (" +
              portValue.secondPort + ")";
    twoPorts = false;
  }
  bool lutram = ch.bindImpl == "lutram";

  const circt::hlsest::Device &device = config().device;
  const circt::hlsest::DeviceMemory *chosen = models.block;
  auto belowBlock = [&](int64_t widthValue,
                        unsigned bits) -> std::optional<std::string> {
    circt::hlsest::MemoryRequest request;
    request.words = widthValue;
    request.writeWidth = bits;
    request.readWidths.push_back(bits);
    request.narrowed = bits != rec.elemBits;
    circt::hlsest::TierChoice choice =
        models.selector->select(request, device, {});
    if (!choice.memory.empty()) {
      if (const circt::hlsest::DeviceMemory *memoryOp =
              device.memory(choice.memory))
        chosen = memoryOp;
      return std::nullopt;
    }
    const circt::hlsest::StorageSelectorConfig &sel =
        config().tool.backend.storageSelector;

    if (sel.belowBlock(widthValue * static_cast<int64_t>(bits)))
      return std::string(sel.belowSymbol()) + " " +
             std::to_string(sel.minBlockBits) + " bits";
    return "kept in tier " + choice.tier + " by storage selector '" +
           models.selector->name().str() + "'";
  };
  ChannelPrice price = priceChannel(
      words, pricedBits, ch.blocks, twoPorts, bound2p, lutram, belowBlock,
      [&](int64_t widthValue, unsigned bits, bool sdp) -> int64_t {
        const circt::hlsest::MemoryArchitectureConfig &memoryOp =
            config().tool.hls.memoryArchitecture;
        llvm::StringRef priced =
            sdp ? memoryOp.pricedWide : memoryOp.pricedNarrow;
        if (!chosen->portConfig(priced)) {

          iface->emitError("--bram-analysis: dataflow channel priced at port "
                           "configuration '")
              << priced << "', which memory '" << chosen->id << "' (tier "
              << chosen->tier << ") does not have";
          models.failed = true;
          return 0;
        }
        return mapBlocks(*models.mapper, *chosen, priced, widthValue, bits,
                         &rec.bankMath);
      });

  if (price.bram && chosen != models.block)
    rec.memoryId = chosen->id;
  if (rec.bankMath.present)
    rec.bankMath.blocks = price.bram;
  portValue.mode = price.mode;
  portValue.rule = price.rule;
  if (lutram)
    portValue.modeReason = "bind_storage impl=lutram";
  else if (twoPorts)
    portValue.modeReason =
        "a process drives a second port: " + portValue.secondPort;
  else if (bound2p)
    portValue.modeReason =
        "bind_storage type=" + ch.bindType +
        " (separate memories even with one port per process)";
  else
    portValue.modeReason = "every process uses one port of the bank";
  portValue.modeReason += clamped;

  BRAMCost cost;
  cost.kind =
      twoPorts || ch.blocks > 1 ? StorageKind::RAM_2P : StorageKind::RAM_1P;
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
              "; " + price.mode + " (" + portValue.modeReason +
              "): " + price.rule + " (never replicated)";
  recordAccesses(accesses, rec, seq);
  rec.demand = computePortDemand(accesses, seq);
  rec.status = "pipo";
  rec.ramType = "PIPO";
  rec.ramReason = price.mode + ": " + portValue.modeReason + "; " + price.rule;
  rec.bram = price.bram;
  rec.pipo = std::move(portValue);
  return cost;
}

class ChannelPorts {
public:
  using SitesFn = llvm::function_ref<SmallVector<Value>(Operation *)>;
  ChannelPorts(SeqContext *seq, const InstanceModel *instances, SitesFn sitesOf)
      : seq(seq), instances(instances), sitesOf(sitesOf) {}

  const std::string &ofBank(Operation *op) {
    auto it = cache.find(op);
    if (it != cache.end())
      return it->second;
    SmallVector<AccessSummary> accesses =
        collectAccessSummaries(sitesOf(op), instances);
    return cache[op] = sameCycleAccesses(accesses, seq);
  }

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
  auto dimensionIndex = dyn_cast<DictionaryAttr>(arr[0]);
  if (!dimensionIndex)
    return std::nullopt;
  if (auto typeValue = dimensionIndex.getAs<StringAttr>("type"))
    if (!typeValue.getValue().equals_insensitive("fifo"))
      return std::nullopt;
  auto depthAttr = dimensionIndex.getAs<IntegerAttr>("depth");
  if (!depthAttr || depthAttr.getInt() <= 0)
    return std::nullopt;
  int64_t fifoDepth = depthAttr.getInt();
  std::string depthSource = "pragma";

  if (dimensionIndex.get("depth_defaulted")) {
    std::optional<int64_t> words = staticElementCount(op);
    if (!words || *words <= 0)
      return std::nullopt;
    fifoDepth = *words;
    depthSource = "the array's size (#pragma HLS stream without a depth)";
  }
  unsigned bits = packedTypeBits(elt);
  std::string bitsSource = "ir element";

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
  FifoPrice portValue =
      priceFifo(g.depth, g.bits, "", [&](int64_t depth, unsigned buildPoint) {
        return mapBlocks(*models.streamMapper, *models.block,
                         config().tool.hls.streams.pricedConfig, depth,
                         buildPoint);
      });
  g.bramEach = portValue.bram;
  g.reason = portValue.reason;
  StreamHandleRecord resultValue;
  resultValue.groups.push_back(std::move(g));
  resultValue.bram = portValue.bram;
  resultValue.fifos = 1;
  resultValue.note =
      "an array with #pragma HLS stream in a dataflow region: one FIFO "
      "of the pragma's depth (VITIS_NOTES N67)";
  return resultValue;
}

static std::optional<BRAMCost>
tryDataflowChannel(MemoryResourceOpInterface iface, MemrefRecord &rec,
                   ArrayRef<Value> sites, SeqContext *seq, const Models &models,
                   const InstanceModel *instances, ChannelPorts &ports,
                   ProcessMerges &merges) {
  Operation *op = iface.getOperation();
  Type elt = iface.getElementType();
  if (!elt.isIntOrFloat() || op->hasAttr(kRegistersAttrName))
    return std::nullopt;

  if (op->hasAttr("hls.const_fill"))
    return std::nullopt;
  if (auto g = dyn_cast<memref::GlobalOp>(op))
    if (g.getConstant())
      return std::nullopt;
  int64_t words = 1;
  for (int64_t dimensionIndex : iface.getStaticShape()) {
    if (ShapedType::isDynamic(dimensionIndex))
      return std::nullopt;
    words *= dimensionIndex;
  }
  if (sites.empty())
    return std::nullopt;
  SmallVector<AccessSummary> accesses =
      collectAccessSummaries(sites, instances);
  SmallVector<ChannelAccess> anchors;
  for (const AccessSummary &a : accesses)
    anchors.push_back({a.via ? a.via : a.op, a.isWrite});
  ChannelVerdict valueHandle =
      analyzeDataflowChannel(op, anchors, words, &merges);
  if (valueHandle.channel)
    return estimateChannel(iface, rec, *valueHandle.channel, accesses, seq,
                           models, ports.ofArray(op));
  if (valueHandle.inRegion && config().tool.hls.streams.streamPragmaArrays)
    if (std::optional<StreamHandleRecord> fifo =
            streamPragmaArrayFifo(op, elt, models))
      return estimateStreamFifos(iface, rec, std::move(*fifo));
  if (valueHandle.inRegion) {
    PipoRecord portValue;
    portValue.notChannelReason = valueHandle.notChannelReason;
    rec.pipo = std::move(portValue);
  }
  return std::nullopt;
}

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
staticProfile(ArrayRef<AccessSummary> accesses, unsigned width, int64_t words) {
  circt::hlsest::BankStaticProfile portValue;
  portValue.width = width;
  portValue.depth = static_cast<unsigned>(std::max<int64_t>(words, 0));
  std::map<Operation *, std::pair<unsigned, unsigned>> perScope;
  for (const AccessSummary &a : accesses) {
    auto &rw = perScope[a.scope];
    (a.isWrite ? rw.second : rw.first)++;
  }
  for (const auto &[scope, rw] : perScope) {
    portValue.maxReads = std::max(portValue.maxReads, rw.first);
    portValue.maxWrites = std::max(portValue.maxWrites, rw.second);
  }
  return portValue;
}

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

static BRAMCost estimateBRAM(MemoryResourceOpInterface iface, MemrefRecord &rec,
                             ArrayRef<Value> banks, bool attributed,
                             SeqContext *seq, const Models &models,
                             const InstanceModel *instances,
                             ArrayRef<Value> allSites) {
  const circt::hlsest::MemoryArchitecturePolicy &policy = *models.policy;
  BRAMCost cost;
  cost.kind = StorageKind::RAM_1P;
  cost.label = policy.unpricedLabel(false);
  cost.bramCount = 0;

  {
    rec.shape = iface.getStaticShape();
    Type elt = iface.getElementType();
    llvm::raw_string_ostream os(rec.elemType);
    elt.print(os);
    rec.elemBits = elt.isIntOrFloat()    ? elt.getIntOrFloatBitWidth()
                   : isa<IndexType>(elt) ? indexElementBits()
                                         : 0u;
    int64_t elementCount = 1;
    bool dynamic = false;
    for (int64_t dimensionIndex : rec.shape) {
      if (ShapedType::isDynamic(dimensionIndex))
        dynamic = true;
      else
        elementCount *= dimensionIndex;
    }
    if (!dynamic)
      rec.words = elementCount;
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
        rec.registerServed.push_back(
            {user->getName().getStringRef().str(), isWrite ? "write" : "read",
             locString(user->getLoc()), rule.getValue().str()});
      }
  }

  {
    Type elt = iface.getElementType();
    if (!elt.isIntOrFloat() && !isa<IndexType>(elt)) {
      cost.note = "element type " + rec.elemType +
                  " is not an integer / float; not estimated";
      rec.status = "excluded_type";
      rec.excludeReason = cost.note;
      SmallVector<AccessSummary> accesses =
          collectAccessSummaries(banks, instances);
      recordAccesses(accesses, rec, seq);
      rec.demand = computePortDemand(accesses, seq);
      rec.ramType = cost.label;
      rec.ramReason = "not selected: " + cost.note;
      rec.bram = cost.bramCount;
      return cost;
    }
  }

  if (iface.getOperation()->hasAttr(kRegistersAttrName)) {
    std::string why = "automatic complete partition";
    if (auto resultValue = iface.getOperation()->getAttrOfType<StringAttr>(
            kRegistersReasonAttrName))
      why = resultValue.getValue().str();
    cost.note = "hls.registers: " + why + " -> registers, 0 BRAM";
    rec.status = "registers";
    rec.excludeReason = "registers (hls.registers): " + why;
    rec.storageTier = "registers";
    SmallVector<AccessSummary> accesses =
        collectAccessSummaries(banks, instances);
    recordAccesses(accesses, rec, seq);
    rec.demand = computePortDemand(accesses, seq);
    rec.ramType = "none";
    rec.ramReason = "not selected: registers, no memory (no port limit in "
                    "the schedule)";
    rec.bram = cost.bramCount;
    return cost;
  }

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
    choice = models.selector->select(declared, device, selection);
    if (!choice.memory.empty() && rec.narrow && rec.words) {
      circt::hlsest::MemoryRequest narrowed = declared;
      narrowed.writeWidth = pricedBits;
      narrowed.readWidths = {pricedBits};
      narrowed.narrowed = true;
      choice = models.selector->select(narrowed, device, selection);
    }
  }

  if (auto recorded =
          iface.getOperation()->getAttrOfType<StringAttr>("hls.storage_tier"))
    if (recorded.getValue() != choice.tier && !pragmaLutram &&
        declaredBits != 0) {
      choice.tier = recorded.getValue().str();
      choice.memory.clear();
      if (choice.tier != config().tool.backend.storageSelector.below)
        for (const circt::hlsest::DeviceMemory &memoryOp : device.memories)
          if (memoryOp.tier == choice.tier) {
            choice.memory = memoryOp.id;
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

    if (pragmaLutram) {
      rec.status = "excluded_small";
      rec.excludeReason = "pragma storage kind LUTRAM; not BRAM-backed";
    } else if (declaredBits == 0 && !rec.words) {

      rec.status = "dynamic_shape";
      rec.excludeReason = "dynamic shape; static size unknown; not estimated";
    } else if (declaredBits == 0) {
      rec.status = "zero_size";
      rec.excludeReason = "zero-size array (0 bits)";
    } else {
      rec.status = "excluded_small";
      rec.excludeReason = choice.note;
    }

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
  unsigned elemBits = pricedBits;
  if (numElems == 0 || elemBits == 0 || !memory) {
    cost.note = "zero-size";
    rec.status = "zero_size";
    rec.excludeReason = cost.note;
    rec.ramType = cost.label;
    rec.ramReason = "not selected: " + cost.note;
    rec.bram = cost.bramCount;
    return cost;
  }

  SmallVector<AccessSummary> accesses = std::move(selectionAccesses);
  PortDemand demand = computePortDemand(accesses, seq);
  ReplicationRecord rep = policy.replication(accesses, rec.accessesAttributed);
  int64_t blocks;

  auto global = dyn_cast<memref::GlobalOp>(iface.getOperation());

  bool initRom = global && !global.isExternal() && !global.isUninitialized() &&
                 (global.getConstant() || neverWritten(allSites));

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
    if (auto dimensionIndex = dyn_cast_or_null<DenseIntElementsAttr>(
            global.getInitialValueAttr())) {
      SmallVector<APInt> vals(dimensionIndex.getValues<APInt>().begin(),
                              dimensionIndex.getValues<APInt>().end());
      romBits = narrowRomWidth(vals);
    }
  rec.rom = initRom || fillRom;
  circt::hlsest::MemoryRequest request;
  request.words = numElems;
  request.writeWidth = elemBits;
  request.readWidths.push_back(elemBits);
  request.narrowed = rec.narrow.has_value();
  if (rec.rom) {

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

    rec.narrow.reset();
    elemBits = rec.elemBits;
    unsigned declaredBits = elemBits;
    std::string widthNote;
    if (romBits) {
      unsigned widthValue = *romBits;
      widthNote = "; element width " + std::to_string(widthValue) + " of " +
                  std::to_string(declaredBits) + " bits from its values (N26)";
      if (widthValue == 0) {
        cost.kind = StorageKind::ROM_1P;
        cost.label = policy.unpricedLabel(true);
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
      elemBits = widthValue;
      circt::hlsest::MemoryRequest romRequest;
      romRequest.words = numElems;
      romRequest.writeWidth = widthValue;
      romRequest.readWidths.push_back(widthValue);
      romRequest.readOnly = true;
      romRequest.needsInit = true;
      circt::hlsest::TierChoice romChoice =
          models.selector->select(romRequest, device, selection);
      if (romChoice.memory.empty()) {
        const circt::hlsest::StorageSelectorConfig &sel =
            config().tool.backend.storageSelector;
        cost.kind = StorageKind::ROM_1P;
        cost.label = policy.unpricedLabel(true);
        cost.bramCount = 0;

        std::string why =
            sel.belowBlock(numElems * static_cast<int64_t>(widthValue))
                ? std::string(sel.belowSymbol()) + " " +
                      std::to_string(sel.minBlockBits) + " bits"
                : "kept in tier " + romChoice.tier + " by storage selector '" +
                      models.selector->name().str() + "'";
        cost.note = std::to_string(numElems) + "x" +
                    std::to_string(widthValue) + "b ROM (narrowed from " +
                    std::to_string(declaredBits) + " bits, N26) " + why +
                    ": distributed ROM, 0 BRAM";
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

    if (unsigned elementCount = sequentialRomReads(accesses, seq, policy);
        elementCount > demand.total) {
      demand.reads = demand.total = elementCount;
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
        std::string(fillRom ? "every write stores a constant (ROM of those "
                              "values, N26)"
                    : global.getConstant()
                        ? "constant-initialised global (ROM, never written)"
                        : "initialised global that no get_global site writes "
                          "(ROM)") +
        widthNote + plan.reason;
    rec.bram = cost.bramCount;
    return cost;
  }

  recordAccesses(accesses, rec, seq);
  circt::hlsest::PlanContext ctx;
  ctx.attributed = rec.accessesAttributed;
  ctx.anyStoreEnable = llvm::any_of(
      rec.accesses, [](const AccessRecord &a) { return a.storeEnable; });

  ctx.onePipelinedScope =
      !accesses.empty() &&
      isa_and_present<LoopSchedulePipelineOp>(accesses.front().scope) &&
      llvm::all_of(accesses, [&](const AccessSummary &a) {
        return a.scope == accesses.front().scope;
      });
  ctx.readWriteSplit = readWriteSplitFits(accesses, seq);

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

    iface->emitError("--bram-analysis: the memory architecture policy prices "
                     "this bank at port configuration '")
        << plan.pricedConfig << "', which memory '" << memory->id << "' (tier "
        << memory->tier << ") does not have";
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
                std::to_string(usedPortWidth(rec.bankMath)) +
                "/port) = " + std::to_string(blocks) + " " + unitName(memory);

  rec.demand = demand;
  rec.replication = rep;
  rec.status = plan.infeasible ? "infeasible" : "counted";
  rec.ramType = plan.label;
  rec.ramReason = plan.reason;
  rec.bram = cost.bramCount;
  rec.infeasible = cost.infeasible;
  return cost;
}

static std::string shapeString(ArrayRef<int64_t> shape) {
  std::string stringValue = "[";
  for (size_t loopIndex = 0; loopIndex < shape.size(); ++loopIndex) {
    if (loopIndex)
      stringValue += "x";
    stringValue += ShapedType::isDynamic(shape[loopIndex])
                       ? "?"
                       : std::to_string(shape[loopIndex]);
  }
  return stringValue + "]";
}

static std::string displayName(const MemrefRecord &resultValue) {
  std::string elementCount = resultValue.varname ? *resultValue.varname
                             : resultValue.name  ? *resultValue.name
                                                 : std::string("<unnamed>");
  if (resultValue.partition.applied && resultValue.partition.bankIndex &&
      resultValue.partition.bankCount)
    elementCount += "[bank " +
                    std::to_string(*resultValue.partition.bankIndex) + "/" +
                    std::to_string(*resultValue.partition.bankCount) + "]";
  return elementCount;
}

static SmallVector<const MemrefRecord *>
sortedByBram(ArrayRef<MemrefRecord> records) {
  SmallVector<const MemrefRecord *> order;
  for (const MemrefRecord &resultValue : records)
    order.push_back(&resultValue);
  llvm::stable_sort(order,
                    [](const MemrefRecord *a, const MemrefRecord *buildPoint) {
                      if (a->bram != buildPoint->bram)
                        return a->bram > buildPoint->bram;
                      return a->id < buildPoint->id;
                    });
  return order;
}

struct PipelineRecord {
  std::string loc;
  std::string func;
  unsigned ii = 0;
  std::optional<int64_t> tripCount;

  std::string source = "innermost";
  unsigned flattenedParents = 0;
  std::optional<int64_t> unrollPartial;

  std::string scheduler;
  struct Unrolled {
    std::string loc;
    int64_t factor = 0;
  };
  SmallVector<Unrolled> unrolled;

  DictionaryAttr memoryRecurrence;

  int64_t foldedGuards = 0;
  int64_t pinnedGuardOperands = 0;

  std::map<std::string, int64_t> argumentBankPorts;
};

static Value accessedMemrefOf(Operation *op, bool &isLoad) {
  isLoad = isa<memref::LoadOp, affine::AffineLoadOp>(op);
  if (auto lowerIndex = dyn_cast<memref::LoadOp>(op))
    return lowerIndex.getMemRef();
  if (auto lowerIndex = dyn_cast<affine::AffineLoadOp>(op))
    return lowerIndex.getMemRef();
  if (auto stringValue = dyn_cast<memref::StoreOp>(op))
    return stringValue.getMemRef();
  if (auto stringValue = dyn_cast<affine::AffineStoreOp>(op))
    return stringValue.getMemRef();
  if (auto stringValue = dyn_cast<circt::hls_analysis::StoreEnableOp>(op))
    return stringValue.getMemref();
  return Value();
}

static std::vector<PipelineRecord>
collectPipelineRecords(ModuleOp module, const TopScope &scope) {
  std::vector<PipelineRecord> out;
  module.walk([&](LoopSchedulePipelineOp portValue) {
    if (!scope.covers(portValue))
      return;
    PipelineRecord resultValue;
    resultValue.loc = locString(portValue.getLoc());
    if (auto fn = portValue->getParentOfType<func::FuncOp>())
      resultValue.func = fn.getName().str();
    resultValue.ii = static_cast<unsigned>(portValue.getII());
    if (auto tc = portValue.getTripCount())
      resultValue.tripCount = static_cast<int64_t>(*tc);
    if (Attribute tag = portValue->getAttr(kLoopPipelineAttr)) {
      resultValue.source = "user";
      if (auto arr = dyn_cast<ArrayAttr>(tag))
        tag = arr.empty() ? Attribute() : arr[0];
      if (auto dict = dyn_cast_or_null<DictionaryAttr>(tag))
        if (auto stringValue = dict.getAs<StringAttr>("source"))
          resultValue.source = stringValue.getValue().str();
    }
    if (auto fp =
            portValue->getAttrOfType<IntegerAttr>(kLoopFlattenedParentsAttr))
      if (fp.getInt() > 0)
        resultValue.flattenedParents = static_cast<unsigned>(fp.getInt());
    if (auto up = portValue->getAttrOfType<IntegerAttr>(kLoopUnrollPartialAttr))
      resultValue.unrollPartial = up.getInt();
    if (auto stringValue =
            portValue->getAttrOfType<StringAttr>(kLoopSchedulerAttr))
      resultValue.scheduler = stringValue.getValue().str();
    resultValue.memoryRecurrence =
        portValue->getAttrOfType<DictionaryAttr>("hls.memory_recurrence");
    if (auto fieldValue = portValue->getAttrOfType<IntegerAttr>(
            circt::hls_analysis::kFoldedGuardsAttr))
      resultValue.foldedGuards = fieldValue.getInt();
    if (auto fieldValue = portValue->getAttrOfType<IntegerAttr>(
            circt::hls_analysis::kPinnedGuardOperandsAttr))
      resultValue.pinnedGuardOperands = fieldValue.getInt();
    portValue->walk([&](Operation *op) {
      auto bank = op->getAttrOfType<IntegerAttr>("hls.port_bank");
      auto banks = op->getAttrOfType<IntegerAttr>("hls.port_banks");
      if (!bank && !banks)
        return;
      bool isLoad = false;
      Value mem = accessedMemrefOf(op, isLoad);
      auto arg = dyn_cast_or_null<BlockArgument>(mem);
      std::string key =
          arg ? "arg" + std::to_string(arg.getArgNumber()) : std::string("?");
      key += bank ? " bank " + std::to_string(bank.getInt())
                  : " any of " + std::to_string(banks.getInt());
      ++resultValue.argumentBankPorts[key];
    });
    if (auto arr = portValue->getAttrOfType<ArrayAttr>(kLoopAutoUnrolledAttr))
      for (Attribute a : arr) {
        auto dict = dyn_cast<DictionaryAttr>(a);
        if (!dict)
          continue;
        PipelineRecord::Unrolled useValue;
        if (auto fieldValue = dict.getAs<IntegerAttr>("factor"))
          useValue.factor = fieldValue.getInt();
        if (auto lowerIndex = dict.getAs<LocationAttr>("loc"))
          useValue.loc = locString(lowerIndex);
        resultValue.unrolled.push_back(std::move(useValue));
      }
    out.push_back(std::move(resultValue));
  });
  return out;
}

struct FoldSummary {
  struct Rewrite {
    std::string rule, loc, source, detail, func;
  };
  SmallVector<std::pair<std::string, int64_t>> counts;
  SmallVector<Rewrite> rewrites;
  bool present = false;

  bool wholeModule = false;
};

static FoldSummary collectFoldSummary(ModuleOp module, const TopScope &scope) {
  FoldSummary stringValue;
  auto dimensionIndex = module->getAttrOfType<DictionaryAttr>("hls.vitis_fold");
  if (!dimensionIndex)
    return stringValue;
  stringValue.present = true;
  auto funcCounts = dimensionIndex.getAs<DictionaryAttr>("func_counts");
  bool scoped = scope.active() && funcCounts;
  stringValue.wholeModule = scope.active() && !funcCounts;
  if (scoped) {
    std::map<std::string, int64_t> sums;
    for (NamedAttribute fieldValue : funcCounts) {
      auto per = dyn_cast<DictionaryAttr>(fieldValue.getValue());
      if (!per || !scope.funcNames.contains(fieldValue.getName().getValue()))
        continue;
      for (NamedAttribute na : per)
        if (auto loopIndex = dyn_cast<IntegerAttr>(na.getValue()))
          sums[na.getName().str()] += loopIndex.getInt();
    }
    stringValue.counts.assign(sums.begin(), sums.end());
  } else if (auto candidateValue =
                 dimensionIndex.getAs<DictionaryAttr>("counts")) {
    for (NamedAttribute na : candidateValue)
      if (auto loopIndex = dyn_cast<IntegerAttr>(na.getValue()))
        stringValue.counts.push_back({na.getName().str(), loopIndex.getInt()});
  }
  if (auto resultValue = dimensionIndex.getAs<ArrayAttr>("rewrites"))
    for (Attribute a : resultValue) {
      auto rd = dyn_cast<DictionaryAttr>(a);
      if (!rd)
        continue;
      if (scoped) {
        auto fn = rd.getAs<StringAttr>("func");
        if (!fn || !scope.funcNames.contains(fn.getValue()))
          continue;
      }
      FoldSummary::Rewrite widthValue;
      if (auto exprValue = rd.getAs<StringAttr>("rule"))
        widthValue.rule = exprValue.str();
      if (auto exprValue = rd.getAs<LocationAttr>("loc"))
        widthValue.loc = locString(Location(exprValue));
      if (auto exprValue = rd.getAs<LocationAttr>("source"))
        widthValue.source = locString(Location(exprValue));
      if (auto exprValue = rd.getAs<StringAttr>("detail"))
        widthValue.detail = exprValue.str();
      if (auto exprValue = rd.getAs<StringAttr>("func"))
        widthValue.func = exprValue.str();
      stringValue.rewrites.push_back(std::move(widthValue));
    }
  return stringValue;
}

static void printFoldSummary(const FoldSummary &fieldValue,
                             llvm::raw_ostream &os) {
  if (!fieldValue.present)
    return;
  int64_t elementCount = 0;
  for (auto &candidateValue : fieldValue.counts)
    elementCount += candidateValue.second;
  os << "--- vitis-fold: " << elementCount
     << " rewrites of the undefined value of an integer x / 0 "
        "(VITIS_NOTES.md N13) ---\n";
  if (fieldValue.wholeModule)
    os << "  (whole module: this hls.vitis_fold has no per-function counts, "
          "so top= does not narrow it)\n";
  os << "  counts:";
  for (auto &candidateValue : fieldValue.counts)
    os << " " << candidateValue.first << "=" << candidateValue.second;
  os << "\n";
  for (const FoldSummary::Rewrite &widthValue : fieldValue.rewrites) {
    os << "  " << widthValue.rule << " @ " << widthValue.loc;
    if (!widthValue.detail.empty())
      os << " (" << widthValue.detail << ")";

    os << (widthValue.rule == "uniform-table-load"
               ? "; table @ "
               : "; undefined value from @ ")
       << widthValue.source << "\n";
  }
  if (static_cast<int64_t>(fieldValue.rewrites.size()) < elementCount)
    os << "  ... "
       << (elementCount - static_cast<int64_t>(fieldValue.rewrites.size()))
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

  if (!config().isDefault()) {
    const Config &cfg = config();
    os << "configuration: " << cfg.hash << " (device " << cfg.device.id
       << ", tool " << cfg.tool.id << "; " << cfg.overrides.size()
       << " key(s) differ from the defaults:";
    for (const circt::hlsest::ConfigOverride &o : cfg.overrides) {
      std::string valueHandle;
      llvm::raw_string_ostream vs(valueHandle);
      vs << o.value;
      os << " " << o.path << "=" << valueHandle;
    }
    os << ")\n";
  }
  if (scope.active())
    os << "top: @" << scope.symbol << " (" << scope.funcs.size()
       << " function(s) reachable through calls; " << scope.skipped
       << " memref(s) outside them not costed)\n";
  else
    os << "top: none (every function is costed)\n";
  for (const MemrefRecord &resultValue : records) {
    if (resultValue.math) {
      os << "[" << resultValue.id << "] math core '"
         << resultValue.math->coreName << "' (" << resultValue.kind << ") in @"
         << (resultValue.func ? *resultValue.func : "?") << " @ "
         << resultValue.locText << "\n";
      printMathCoreText(*resultValue.math, os);
      os << "  bram: " << resultValue.bram << "\n";
      continue;
    }
    if (resultValue.adapter) {
      const AdapterRecord &a = *resultValue.adapter;
      os << "[" << resultValue.id << "] m_axi bundle '" << a.bundle << "' ("
         << resultValue.kind << ") in @"
         << (resultValue.func ? *resultValue.func : "?") << " @ "
         << resultValue.locText << "\n";
      os << "  ports:";
      for (const std::string &portValue : a.ports)
        os << " " << portValue;
      os << "; bus width max(32, element bits) = " << a.busBits << "\n";
      os << "  read FIFO: " << (a.hasRead ? "used" : "no load from the bundle")
         << ", max_read_burst_length " << a.readBurst
         << " x num_read_outstanding " << a.readOutstanding << " = depth "
         << a.readDepth << " -> " << a.readBram << " BRAM (" << a.readRule
         << ")\n";
      os << "  write buffer: "
         << (a.hasWrite ? "used" : "no store to the bundle")
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
      os << "  bram: " << resultValue.bram << "\n";
      continue;
    }
    os << "[" << resultValue.id << "] " << displayName(resultValue) << " ("
       << resultValue.kind;
    if (resultValue.name && resultValue.varname)
      os << " @" << *resultValue.name;
    os << ") @ " << resultValue.locText << "\n";
    if (resultValue.fromGlobal)
      os << "  promoted from memref.global @" << *resultValue.fromGlobal
         << " (--promote-globals-to-allocas)\n";
    if (resultValue.structMember)
      os << "  struct array split: " << *resultValue.structMember
         << " (--split-struct-memrefs)\n";
    if (resultValue.aggregated)
      os << "  struct variable " << *resultValue.aggregated
         << " (--split-struct-memrefs)\n";
    os << "  shape " << shapeString(resultValue.shape) << " x "
       << resultValue.elemType << " (" << resultValue.elemBits << " bits)";
    if (resultValue.words)
      os << " = " << *resultValue.words << " words";
    os << "\n";
    if (resultValue.narrow)
      os << "  narrowed width: " << resultValue.narrow->bits << " of "
         << resultValue.narrow->declaredBits << " bits ("
         << resultValue.narrow->reason << ")\n";
    os << "  status: " << resultValue.status;
    if (resultValue.excludeReason)
      os << " -- " << *resultValue.excludeReason;
    os << "\n";
    if (resultValue.status == "eliminated_dead") {
      os << "  bram: 0\n";
      continue;
    }
    if (resultValue.fifo) {
      const StreamHandleRecord &fieldValue = *resultValue.fifo;
      os << "  hls::stream storage (not a RAM): " << fieldValue.fifos
         << " FIFO(s); methods:";
      for (const std::string &memoryOp : fieldValue.methods)
        os << " " << memoryOp;
      os << "\n";
      for (const FifoGroup &g : fieldValue.groups) {
        os << "  fifo: " << g.count << " x ";
        if (g.member)
          os << "member " << *g.member << " ";
        os << "depth " << g.depth << " (" << g.depthSource << ") x " << g.bits
           << " bits (" << g.bitsSource << ") -> " << g.bramEach
           << " each: " << g.reason << " (count: " << g.countSource << ")\n";
      }
      if (!fieldValue.note.empty())
        os << "  note: " << fieldValue.note << "\n";
      if (resultValue.instances != 1)
        os << "  instances: " << resultValue.instances << " x "
           << resultValue.bramPerInstance << "\n";
      os << "  bram: " << resultValue.bram << "\n";
      continue;
    }
    if (resultValue.pipo) {
      const PipoRecord &pp = *resultValue.pipo;
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
    if (resultValue.keptReason)
      os << "  " << *resultValue.keptReason << "\n";
    if (resultValue.partition.present) {
      const PartitionRecord &portValue = resultValue.partition;
      os << "  partition: " << portValue.kind << " factor=" << portValue.factor
         << " dim=" << portValue.dim << " source=" << portValue.source;
      if (!portValue.dims.empty()) {
        os << " dims=[";
        llvm::interleaveComma(portValue.dims, os, [&](const auto &typeValue) {
          os << std::get<0>(typeValue) << " " << std::get<1>(typeValue)
             << " on dim " << std::get<2>(typeValue);
        });
        os << "]";
      }
      if (portValue.from)
        os << " from " << *portValue.from;
      if (portValue.applied) {
        os << " (bank";
        if (portValue.bankIndex)
          os << " " << *portValue.bankIndex;
        if (portValue.bankCount)
          os << " of " << *portValue.bankCount;
        os << ")";
      } else {
        os << " (spec present, not banked)";
      }
      if (portValue.reason)
        os << "\n    reason: " << *portValue.reason;
      os << "\n";
    } else {
      os << "  partition: none\n";
    }
    if (!resultValue.accessesAttributed) {
      os << "  accesses: not attributed (memref.global has no SSA result)\n";
    } else {
      os << "  accesses (" << resultValue.accesses.size() << "):\n";
      for (const AccessRecord &a : resultValue.accesses) {
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
      for (const MemrefRecord::RegisterServed &exprValue :
           resultValue.registerServed)
        os << "    served by a register (" << exprValue.rule
           << "): " << exprValue.op << " (" << exprValue.rw << ") @ "
           << exprValue.loc << "\n";
      os << "  port demand: reads=" << resultValue.demand.reads
         << " writes=" << resultValue.demand.writes
         << " total=" << resultValue.demand.total << " (max over scopes"
         << (resultValue.demand.segregated ? "; segregated R/W" : "") << ")\n";
      for (const ScopeDemandRecord &stringValue : resultValue.perScope)
        os << "    scope " << stringValue.scopeKind << " @ "
           << stringValue.scopeLoc << " ii=" << stringValue.ii
           << ": reads=" << stringValue.demand.reads
           << " writes=" << stringValue.demand.writes
           << " total=" << stringValue.demand.total
           << (stringValue.sameState ? " [" + *stringValue.sameState + "]"
                                     : std::string())
           << "\n";
    }
    if (resultValue.replication.present) {
      const ReplicationRecord &portValue = resultValue.replication;
      os << "  replication: "
         << (portValue.replicable ? "replicable" : "not replicable") << " (max "
         << portValue.maxStoresPerLoop << " store(s) per loop body), copies "
         << portValue.copies;
      if (portValue.limitingLoop)
        os << " set by pipeline @ " << *portValue.limitingLoop;
      os << "\n";
      for (const ReplicationLoopRecord &lowerIndex : portValue.loops)
        os << "    pipeline @ " << lowerIndex.scopeLoc
           << " ii=" << lowerIndex.ii << ": " << lowerIndex.reads << "R+"
           << lowerIndex.writes << "W per iteration -> ceil("
           << (lowerIndex.reads + lowerIndex.writes) << "/" << lowerIndex.ii
           << ")=" << lowerIndex.need << " port-cycles -> copies "
           << lowerIndex.copies
           << (lowerIndex.portBound
                   ? " (port-bound: a callee instantiated at more "
                     "than one place, N14 R6)"
                   : "")
           << "\n";
    }
    os << "  ram type: " << resultValue.ramType << " -- "
       << resultValue.ramReason << "\n";
    if (resultValue.bankMath.present) {
      const BankMathRecord &buildPoint = resultValue.bankMath;

      bool onePort =
          resultValue.ramType == "RAM_1P" || resultValue.ramType == "ROM_1P";
      os << "  bank math: " << buildPoint.bitsPerBram
         << " bits/BRAM_18K (incl. parity), "
         << (!buildPoint.wide ? "two live ports -> x18 max"
             : onePort        ? "one live port -> x36 allowed"
                              : "simple dual port -> x36 allowed")
         << " at " << resultValue.ramType << ", element "
         << resultValue.elemBits << "b -> mode x" << buildPoint.configWidth
         << ": columns ceil(" << resultValue.elemBits << "/"
         << buildPoint.configWidth << ")=" << buildPoint.widthTiles
         << ", depth/block " << buildPoint.depthPerBlock
         << ", address depth 2^ceil(log2 "
         << (resultValue.words ? *resultValue.words : 0)
         << ")=" << buildPoint.addrDepth << ", blocks/column max(1,"
         << buildPoint.addrDepth << "/" << buildPoint.depthPerBlock
         << ")=" << buildPoint.depthTiles << " -> " << buildPoint.blocksPerCopy
         << " per copy, replication " << buildPoint.replication << " -> "
         << buildPoint.blocks << " block(s); formula " << buildPoint.formula
         << ": " << buildPoint.band << "\n";
    }
    if (resultValue.instances != 1)
      os << "  instances: " << resultValue.instances << " of @"
         << (resultValue.ownerFunc
                 ? *resultValue.ownerFunc
                 : (resultValue.func ? *resultValue.func : "?"))
         << " (N14: charged once per instance; " << resultValue.bramPerInstance
         << " per instance)\n";
    os << "  bram: " << resultValue.bram
       << (resultValue.infeasible ? "  [INFEASIBLE]" : "") << "\n";
  }
  if (!instances.empty()) {
    os << "--- instances (non-inlined callees, VITIS_NOTES.md N14 R2/R3) "
          "---\n";
    for (const InstanceRecord &fieldValue : instances) {
      os << "  @" << fieldValue.func << ": " << fieldValue.instances
         << " instance(s)" << (fieldValue.inlineOff ? " (inline off)" : "")
         << (fieldValue.inlineAutoOff ? " (not inlined automatically)" : "")
         << "\n";
      for (const InstanceRecord::Parent &portValue : fieldValue.parents) {
        os << "    in @" << portValue.parent << " (x"
           << portValue.parentInstances << "): " << portValue.rule << "\n";
        for (const auto &[loc, inst] : portValue.sites)
          os << "      call @ " << loc << " -> instance " << inst << "\n";
      }
    }
  }
  os << "--- pipelines (decisions of --auto-pipeline-unroll) ---\n";
  for (const PipelineRecord &portValue : pipelines) {
    os << "  pipeline @ " << portValue.loc << " in @" << portValue.func
       << ": ii=" << portValue.ii;
    if (portValue.tripCount)
      os << " trip=" << *portValue.tripCount;
    os << " source=" << portValue.source
       << " flattened_parents=" << portValue.flattenedParents;
    if (portValue.unrollPartial)
      os << " unroll_partial=" << *portValue.unrollPartial;
    if (!portValue.scheduler.empty())
      os << " scheduler=" << portValue.scheduler;
    if (DictionaryAttr memoryOp = portValue.memoryRecurrence) {
      auto num = [&](StringRef keyValue) {
        auto a = memoryOp.getAs<IntegerAttr>(keyValue);
        return a ? a.getInt() : int64_t(0);
      };
      auto str = [&](StringRef keyValue) {
        auto a = memoryOp.getAs<StringAttr>(keyValue);
        return a ? a.getValue() : StringRef();
      };
      os << " memory_recurrence=" << str("rule") << " ii>=" << num("ii")
         << " (distance " << num("distance") << ", chain " << num("chain")
         << ", load @ " << str("load") << ", store @ " << str("store") << ")";
    }
    if (portValue.foldedGuards || portValue.pinnedGuardOperands)
      os << " folded_guards=" << portValue.foldedGuards
         << " pinned_guard_operands=" << portValue.pinnedGuardOperands
         << " (N89)";
    if (!portValue.argumentBankPorts.empty()) {
      os << " argument_bank_ports=[";
      bool first = true;
      for (const auto &[keyValue, elementCount] : portValue.argumentBankPorts) {
        os << (first ? "" : ", ") << keyValue << ": " << elementCount;
        first = false;
      }
      os << "] (N88)";
    }
    os << "\n";
    for (const PipelineRecord::Unrolled &useValue : portValue.unrolled)
      os << "    unrolled x" << useValue.factor << " @ " << useValue.loc
         << "\n";
  }
  printFoldSummary(fold, os);
  os << "--- summary (sorted by BRAM) ---\n";
  for (const MemrefRecord *resultValue : sortedByBram(records))
    os << "  " << llvm::format("%6u", resultValue->bram) << "  "
       << resultValue->id << "  " << displayName(*resultValue) << "\n";
  os << "Total BRAM: " << total << "\n";
}

static llvm::json::Value optStr(const std::optional<std::string> &stringValue) {
  if (stringValue)
    return llvm::json::Value(*stringValue);
  return llvm::json::Value(nullptr);
}

static llvm::json::Value optInt(const std::optional<int64_t> &valueHandle) {
  if (valueHandle)
    return llvm::json::Value(*valueHandle);
  return llvm::json::Value(nullptr);
}

static llvm::json::Object toJson(const MemrefRecord &resultValue) {
  llvm::json::Object o;
  o["id"] = resultValue.id;
  o["name"] = optStr(resultValue.name);
  o["varname"] = optStr(resultValue.varname);
  o["kind"] = resultValue.kind;
  o["func"] = optStr(resultValue.func);

  if (resultValue.fromGlobal)
    o["from_global"] = *resultValue.fromGlobal;
  if (resultValue.structMember)
    o["struct_member"] = *resultValue.structMember;
  if (resultValue.aggregated)
    o["aggregated"] = *resultValue.aggregated;
  if (resultValue.rom)
    o["rom"] = true;
  if (resultValue.math)
    o["math"] = mathCoreJson(*resultValue.math);
  if (resultValue.pipo) {
    const PipoRecord &pp = *resultValue.pipo;
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
        if (!dp.group.empty()) {
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
  if (resultValue.fifo) {
    const StreamHandleRecord &fieldValue = *resultValue.fifo;
    llvm::json::Object fo;
    fo["fifos"] = fieldValue.fifos;
    fo["bram"] = static_cast<int64_t>(fieldValue.bram);
    llvm::json::Array methods;
    for (const std::string &memoryOp : fieldValue.methods)
      methods.push_back(memoryOp);
    fo["methods"] = std::move(methods);
    llvm::json::Array groups;
    for (const FifoGroup &g : fieldValue.groups) {
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
    if (!fieldValue.note.empty())
      fo["note"] = fieldValue.note;
    o["fifo"] = std::move(fo);
  }
  if (resultValue.adapter) {
    const AdapterRecord &a = *resultValue.adapter;
    llvm::json::Object ad;
    ad["bundle"] = a.bundle;
    llvm::json::Array ports;
    for (const std::string &portValue : a.ports)
      ports.push_back(portValue);
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
  if (resultValue.hasLoc) {
    llvm::json::Object loc;
    loc["file"] = resultValue.locFile;
    loc["line"] = static_cast<int64_t>(resultValue.locLine);
    loc["col"] = static_cast<int64_t>(resultValue.locCol);
    o["loc"] = std::move(loc);
  } else {
    o["loc"] = nullptr;
  }
  llvm::json::Array shape;
  for (int64_t dimensionIndex : resultValue.shape)
    shape.push_back(ShapedType::isDynamic(dimensionIndex)
                        ? llvm::json::Value(nullptr)
                        : llvm::json::Value(dimensionIndex));
  o["shape"] = std::move(shape);
  o["elem_type"] = resultValue.elemType;
  o["elem_bits"] = static_cast<int64_t>(resultValue.elemBits);
  o["words"] = optInt(resultValue.words);
  o["status"] = resultValue.status;
  o["exclude_reason"] = optStr(resultValue.excludeReason);
  if (resultValue.keptReason)
    o["kept_reason"] = *resultValue.keptReason;
  if (resultValue.narrow) {
    llvm::json::Object elementCount;
    elementCount["declared_bits"] =
        static_cast<int64_t>(resultValue.narrow->declaredBits);
    elementCount["bits"] = static_cast<int64_t>(resultValue.narrow->bits);
    elementCount["reason"] = resultValue.narrow->reason;
    o["narrow"] = std::move(elementCount);
  }

  if (resultValue.partition.present) {
    const PartitionRecord &portValue = resultValue.partition;
    llvm::json::Object part;
    part["kind"] = portValue.kind;
    part["factor"] = portValue.factor;
    part["dim"] = portValue.dim;
    part["source"] = portValue.source;
    part["reason"] = optStr(portValue.reason);
    part["bank_index"] = optInt(portValue.bankIndex);
    part["bank_count"] = optInt(portValue.bankCount);

    if (!portValue.dims.empty()) {
      llvm::json::Array dims;
      for (const auto &[keyValue, fieldValue, dm] : portValue.dims)
        dims.push_back(llvm::json::Object{
            {"kind", keyValue}, {"factor", fieldValue}, {"dim", dm}});
      part["dims"] = std::move(dims);
    }
    if (portValue.from)
      part["from"] = *portValue.from;

    if (portValue.forwardedReloads) {
      llvm::json::Array g;
      for (int64_t elementCount : portValue.steeredGroups)
        g.push_back(elementCount);
      part["steered_groups"] = std::move(g);
      part["forwarded_reloads"] = *portValue.forwardedReloads;
    }
    o["partition"] = std::move(part);
  } else {
    o["partition"] = nullptr;
  }

  llvm::json::Array accesses;
  for (const AccessRecord &a : resultValue.accesses) {
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
    ao["register_promoted_accesses"] = static_cast<int64_t>(a.registerPromoted);

    ao["merged_if_else_stores"] = static_cast<int64_t>(a.mergedIfElseStores);
    ao["hoisted_conditional"] = a.hoistedConditional;

    ao["in_func"] = a.inFunc.empty() ? llvm::json::Value(nullptr)
                                     : llvm::json::Value(a.inFunc);
    ao["via_call"] = optStr(a.viaCall);

    ao["port_bound"] = a.portBound;

    ao["port_bound_reason"] = a.portBoundReason.empty()
                                  ? llvm::json::Value(nullptr)
                                  : llvm::json::Value(a.portBoundReason);

    ao["port_bank"] = a.portBank.empty() ? llvm::json::Value(nullptr)
                                         : llvm::json::Value(a.portBank);
    accesses.push_back(std::move(ao));
  }
  o["accesses"] = std::move(accesses);

  llvm::json::Array served;
  for (const MemrefRecord::RegisterServed &exprValue :
       resultValue.registerServed)
    served.push_back(llvm::json::Object{{"op", exprValue.op},
                                        {"rw", exprValue.rw},
                                        {"loc", exprValue.loc},
                                        {"rule", exprValue.rule}});
  o["register_served_accesses"] = std::move(served);

  llvm::json::Object pd;
  pd["reads"] = static_cast<int64_t>(resultValue.demand.reads);
  pd["writes"] = static_cast<int64_t>(resultValue.demand.writes);
  pd["total"] = static_cast<int64_t>(resultValue.demand.total);
  llvm::json::Array perScope;
  for (const ScopeDemandRecord &stringValue : resultValue.perScope) {
    llvm::json::Object so;
    so["scope"] = stringValue.scopeKind;
    so["scope_loc"] = stringValue.scopeLoc;
    so["ii"] = static_cast<int64_t>(stringValue.ii);
    so["reads"] = static_cast<int64_t>(stringValue.demand.reads);
    so["writes"] = static_cast<int64_t>(stringValue.demand.writes);
    so["total"] = static_cast<int64_t>(stringValue.demand.total);
    if (stringValue.sameState)
      so["same_state"] = *stringValue.sameState;
    perScope.push_back(std::move(so));
  }
  pd["per_scope"] = std::move(perScope);
  o["port_demand"] = std::move(pd);

  o["ram_type"] = resultValue.ramType;
  o["ram_reason"] = resultValue.ramReason;

  if (resultValue.replication.present) {
    const ReplicationRecord &portValue = resultValue.replication;
    llvm::json::Object rp;
    rp["replicable"] = portValue.replicable;
    rp["max_stores_per_loop"] =
        static_cast<int64_t>(portValue.maxStoresPerLoop);
    rp["copies"] = static_cast<int64_t>(portValue.copies);
    rp["limiting_loop"] = optStr(portValue.limitingLoop);
    llvm::json::Array loops;
    for (const ReplicationLoopRecord &lowerIndex : portValue.loops) {
      llvm::json::Object lo;
      lo["scope_loc"] = lowerIndex.scopeLoc;
      lo["ii"] = static_cast<int64_t>(lowerIndex.ii);
      lo["reads"] = static_cast<int64_t>(lowerIndex.reads);
      lo["writes"] = static_cast<int64_t>(lowerIndex.writes);
      lo["need"] = static_cast<int64_t>(lowerIndex.need);
      lo["copies"] = static_cast<int64_t>(lowerIndex.copies);

      lo["port_bound"] = lowerIndex.portBound;
      loops.push_back(std::move(lo));
    }
    rp["loops"] = std::move(loops);
    o["replication"] = std::move(rp);
  } else {
    o["replication"] = nullptr;
  }

  if (resultValue.bankMath.present) {
    const BankMathRecord &buildPoint = resultValue.bankMath;
    llvm::json::Object bm;
    bm["bits_per_bram"] = buildPoint.bitsPerBram;
    bm["wide"] = buildPoint.wide;
    bm["max_width"] = static_cast<int64_t>(buildPoint.maxWidth);
    bm["config_width"] = static_cast<int64_t>(buildPoint.configWidth);
    bm["width_tiles"] = buildPoint.widthTiles;
    bm["depth_per_block"] = buildPoint.depthPerBlock;
    bm["addr_depth"] = buildPoint.addrDepth;
    bm["depth_tiles"] = buildPoint.depthTiles;
    bm["blocks_per_copy"] = buildPoint.blocksPerCopy;
    bm["replication"] = buildPoint.replication;
    bm["blocks"] = buildPoint.blocks;

    bm["formula"] = buildPoint.formula;
    bm["band"] = buildPoint.band;
    o["bank_math"] = std::move(bm);
  } else {
    o["bank_math"] = nullptr;
  }
  o["bram"] = static_cast<int64_t>(resultValue.bram);

  o["instances"] = static_cast<int64_t>(resultValue.instances);
  o["bram_per_instance"] = static_cast<int64_t>(resultValue.bramPerInstance);
  o["owner_func"] = optStr(resultValue.ownerFunc);
  return o;
}

/// Additive (P2), one entry per record id under the top-level key
/// "memory_model" (not in the record itself, whose sorted keys hand-written
/// tests check line by line): the device memory that priced it, the storage
/// selector's tier and what it costs per resource class.
static llvm::json::Value memoryModelJson(ArrayRef<MemrefRecord> records) {
  llvm::json::Object out;
  for (const MemrefRecord &resultValue : records) {
    llvm::json::Object o;
    o["memory"] = resultValue.memoryId.empty()
                      ? llvm::json::Value(nullptr)
                      : llvm::json::Value(resultValue.memoryId);
    o["storage_tier"] = resultValue.storageTier.empty()
                            ? llvm::json::Value(nullptr)
                            : llvm::json::Value(resultValue.storageTier);
    o["resources"] = resultValue.resources.toJson();
    out[resultValue.id] = std::move(o);
  }
  return out;
}

/// The configuration this run used (additive debug key "config"): its hash,
/// device and profile, the files and --config-set assignments, and every key
/// that differs from the compiled-in defaults with its value and origin.
static llvm::json::Value configRecord() {
  const Config &cfg = config();
  llvm::json::Object candidateValue;
  candidateValue["hash"] = cfg.hash;
  candidateValue["device"] = cfg.device.id;
  candidateValue["tool"] = cfg.tool.id;
  llvm::json::Array files, sets;
  for (const std::string &fieldValue : cfg.files)
    files.push_back(fieldValue);
  for (const std::string &st : cfg.sets)
    sets.push_back(st);
  candidateValue["files"] = std::move(files);
  candidateValue["sets"] = std::move(sets);
  llvm::json::Object changed;
  for (const circt::hlsest::ConfigOverride &o : cfg.overrides)
    changed[o.path] =
        llvm::json::Object{{"value", o.value}, {"source", o.source}};
  candidateValue["non_default"] = std::move(changed);
  return candidateValue;
}

static std::error_code writeDebugJson(ArrayRef<MemrefRecord> records,
                                      ArrayRef<PipelineRecord> pipelineRecords,
                                      ArrayRef<InstanceRecord> instanceRecords,
                                      int64_t total, const FoldSummary &fold,
                                      const circt::hlsest::MemoryMapper &mapper,
                                      const llvm::json::Value &plugins,
                                      const llvm::json::Value &resources,
                                      const TopScope &scope, StringRef path) {
  llvm::json::Object root;
  root["version"] = 2;
  root["total_bram"] = total;
  root["bram_formula"] = mapper.reportLabel();
  root["config"] = configRecord();
  root["plugins"] = plugins;
  root["resources"] = resources;
  root["memory_model"] = memoryModelJson(records);

  if (scope.active()) {
    llvm::json::Object to;
    to["symbol"] = scope.symbol;
    SmallVector<StringRef> names(scope.funcNames.begin(),
                                 scope.funcNames.end());
    llvm::sort(names);
    llvm::json::Array fa;
    for (StringRef elementCount : names)
      fa.push_back(elementCount.str());
    to["functions"] = std::move(fa);
    to["skipped_memrefs"] = static_cast<int64_t>(scope.skipped);
    root["top"] = std::move(to);
  } else {
    root["top"] = nullptr;
  }

  llvm::json::Array functions;
  SmallVector<std::string> seen;
  for (const MemrefRecord &resultValue : records)
    if (resultValue.func && !llvm::is_contained(seen, *resultValue.func)) {
      seen.push_back(*resultValue.func);
      functions.push_back(*resultValue.func);
    }
  root["functions"] = std::move(functions);

  llvm::json::Array memrefs;
  for (const MemrefRecord &resultValue : records)
    memrefs.push_back(toJson(resultValue));
  root["memrefs"] = std::move(memrefs);

  llvm::json::Array pipelines;
  for (const PipelineRecord &portValue : pipelineRecords) {
    llvm::json::Object po;
    po["scope_loc"] = portValue.loc;
    po["func"] = portValue.func;
    po["ii"] = static_cast<int64_t>(portValue.ii);
    po["trip_count"] = optInt(portValue.tripCount);
    po["source"] = portValue.source;
    po["flattened_parents"] = static_cast<int64_t>(portValue.flattenedParents);
    po["unroll_partial"] = optInt(portValue.unrollPartial);
    po["scheduler"] = portValue.scheduler.empty()
                          ? llvm::json::Value(nullptr)
                          : llvm::json::Value(portValue.scheduler);
    if (DictionaryAttr memoryOp = portValue.memoryRecurrence) {
      llvm::json::Object mo;
      for (NamedAttribute a : memoryOp) {
        if (auto loopIndex = dyn_cast<IntegerAttr>(a.getValue()))
          mo[a.getName().strref()] = loopIndex.getInt();
        else if (auto stringValue = dyn_cast<StringAttr>(a.getValue()))
          mo[a.getName().strref()] = stringValue.getValue().str();
      }
      po["memory_recurrence"] = std::move(mo);
    } else {
      po["memory_recurrence"] = nullptr;
    }

    po["folded_guards"] = portValue.foldedGuards;
    po["pinned_guard_operands"] = portValue.pinnedGuardOperands;
    llvm::json::Object abp;
    for (const auto &[keyValue, elementCount] : portValue.argumentBankPorts)
      abp[keyValue] = elementCount;
    po["argument_bank_ports"] = std::move(abp);
    llvm::json::Array unrolled;
    for (const PipelineRecord::Unrolled &useValue : portValue.unrolled) {
      llvm::json::Object uo;
      uo["loc"] = useValue.loc;
      uo["factor"] = useValue.factor;
      unrolled.push_back(std::move(uo));
    }
    po["unrolled"] = std::move(unrolled);
    pipelines.push_back(std::move(po));
  }
  root["pipelines"] = std::move(pipelines);

  llvm::json::Array instances;
  for (const InstanceRecord &fieldValue : instanceRecords) {
    llvm::json::Object fo;
    fo["func"] = fieldValue.func;
    fo["instances"] = static_cast<int64_t>(fieldValue.instances);
    fo["inline_off"] = fieldValue.inlineOff;
    fo["inline_auto_off"] = fieldValue.inlineAutoOff;
    llvm::json::Array parents;
    for (const InstanceRecord::Parent &portValue : fieldValue.parents) {
      llvm::json::Object po;
      po["parent"] = portValue.parent;
      po["parent_instances"] = static_cast<int64_t>(portValue.parentInstances);
      po["call_sites"] = static_cast<int64_t>(portValue.callSites);
      po["instances"] = static_cast<int64_t>(portValue.instances);
      po["allocation_limit"] = optInt(portValue.limit);
      po["rule"] = portValue.rule;
      llvm::json::Array sites;
      for (const auto &[loc, inst] : portValue.sites)
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
  for (const MemrefRecord *resultValue : sortedByBram(records)) {
    llvm::json::Object stringValue;
    stringValue["id"] = resultValue->id;
    stringValue["varname"] = optStr(resultValue->varname);
    stringValue["bram"] = static_cast<int64_t>(resultValue->bram);
    summary.push_back(std::move(stringValue));
  }
  root["summary"] = std::move(summary);

  if (fold.present) {
    llvm::json::Object fo, counts;
    for (auto &candidateValue : fold.counts)
      counts[candidateValue.first] = candidateValue.second;
    fo["counts"] = std::move(counts);
    llvm::json::Array rewrites;
    for (const FoldSummary::Rewrite &widthValue : fold.rewrites) {
      llvm::json::Object wo;
      wo["rule"] = widthValue.rule;
      wo["loc"] = widthValue.loc;
      wo["source"] = widthValue.source;
      wo["detail"] = widthValue.detail.empty()
                         ? llvm::json::Value(nullptr)
                         : llvm::json::Value(widthValue.detail);
      wo["func"] = widthValue.func.empty() ? llvm::json::Value(nullptr)
                                           : llvm::json::Value(widthValue.func);
      rewrites.push_back(std::move(wo));
    }
    fo["rewrites"] = std::move(rewrites);

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

static SmallVector<std::pair<func::FuncOp, AdapterRecord>>
collectAdapters(ModuleOp module, const Models &models) {
  SmallVector<std::pair<func::FuncOp, AdapterRecord>> out;
  const circt::hlsest::ImplicitBufferConfig *mc =
      config().tool.hls.implicitBuffer("axi4-mm");
  if (!mc || !models.buffers || !models.fifoMapper)
    return out;

  auto mapFifo = [&](int64_t depth, unsigned bits) -> int64_t {
    return mapBlocks(*models.fifoMapper, *models.block,
                     mc->readFifoPricedConfig, depth, bits);
  };
  for (auto fn : module.getOps<func::FuncOp>()) {
    if (fn.isPrivate() || fn.isExternal())
      continue;
    SmallVector<circt::hlsest::ImplicitBuffer> buffers;
    models.buffers->buffers(fn, *mc, mapFifo, buffers);
    for (circt::hlsest::ImplicitBuffer &buildPoint : buffers)
      out.push_back({fn, std::move(buildPoint)});
  }
  return out;
}

static void appendDeadRecords(ModuleOp module, unsigned &index,
                              std::vector<MemrefRecord> &records) {
  auto arr = module->getAttrOfType<ArrayAttr>("hls.dead_memrefs");
  if (!arr)
    return;
  for (Attribute attr : arr) {
    auto dimensionIndex = dyn_cast<DictionaryAttr>(attr);
    if (!dimensionIndex)
      continue;
    MemrefRecord resultValue;
    auto str = [&](StringRef keyValue) -> std::optional<std::string> {
      if (auto stringValue = dimensionIndex.getAs<StringAttr>(keyValue))
        return stringValue.getValue().str();
      return std::nullopt;
    };
    resultValue.kind = str("kind").value_or("alloca");
    resultValue.func = str("func");
    if (resultValue.kind == "global")
      resultValue.name = str("symbol");
    resultValue.varname = str("name");
    resultValue.fromGlobal = str("from_global");
    resultValue.id = (resultValue.func ? *resultValue.func : std::string("?")) +
                     "#dead" + std::to_string(index++);
    if (auto lowerIndex = dimensionIndex.getAs<LocationAttr>("loc")) {
      if (auto fieldValue = findFileLoc(Location(lowerIndex))) {
        resultValue.hasLoc = true;
        resultValue.locFile = fieldValue.getFilename().str();
        resultValue.locLine = fieldValue.getLine();
        resultValue.locCol = fieldValue.getColumn();
      }
      resultValue.locText = locString(Location(lowerIndex));
    }
    if (auto typeValue = dimensionIndex.getAs<TypeAttr>("type"))
      if (auto mt = dyn_cast<MemRefType>(typeValue.getValue())) {
        resultValue.shape = llvm::to_vector(mt.getShape());
        Type elt = mt.getElementType();
        llvm::raw_string_ostream os(resultValue.elemType);
        elt.print(os);
        resultValue.elemBits = elt.isIntOrFloat() ? elt.getIntOrFloatBitWidth()
                               : isa<IndexType>(elt) ? indexElementBits()
                                                     : 0u;
        if (mt.hasStaticShape())
          resultValue.words = mt.getNumElements();
      }
    resultValue.status = "eliminated_dead";
    resultValue.excludeReason = "removed by --dead-memory-elimination: " +
                                str("reason").value_or("dead");
    resultValue.ramType = "none";
    resultValue.ramReason = "eliminated";
    resultValue.bram = 0;
    records.push_back(std::move(resultValue));
  }
}

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
      op->getAttrDictionary().walk<WalkOrder::PreOrder>([&](SymbolRefAttr ref) {
        Operation *symbolName = SymbolTable::lookupNearestSymbolFrom(op, ref);
        if (auto g = dyn_cast_or_null<memref::GlobalOp>(symbolName))
          scope.globals.insert(g.getSymName());
        else if (auto callee = dyn_cast_or_null<func::FuncOp>(symbolName))
          if (!callee.isExternal() &&
              scope.funcs.insert(callee.getOperation()).second)
            work.push_back(callee);
        return WalkResult::skip();
      });
    });
  }
  return true;
}

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

static SmallVector<InstanceRecord>
collectInstanceRecords(const InstanceModel &model) {
  SmallVector<InstanceRecord> out;
  for (auto &[calleeOp, parents] : model.parents) {
    auto callee = cast<func::FuncOp>(calleeOp);
    InstanceRecord resultValue;
    resultValue.func = callee.getName().str();
    resultValue.instances = model.instancesOf(callee);
    resultValue.inlineOff = callee->hasAttr(kInlineOffAttr);
    resultValue.inlineAutoOff = callee->hasAttr(kInlineAutoOffAttr);
    for (const ParentInstances &pi : parents) {
      InstanceRecord::Parent portValue;
      func::FuncOp parentFn = pi.parent;
      portValue.parent = parentFn.getName().str();
      portValue.parentInstances = model.instancesOf(parentFn);
      portValue.callSites = pi.callSites;
      portValue.instances = pi.instances;
      portValue.limit = pi.limit;
      portValue.rule = pi.rule;
      for (const auto &[site, group] : pi.siteGroups)
        portValue.sites.push_back({locString(site->getLoc()), group});
      resultValue.parents.push_back(std::move(portValue));
    }
    llvm::sort(resultValue.parents,
               [](const InstanceRecord::Parent &a,
                  const InstanceRecord::Parent &buildPoint) {
                 return a.parent < buildPoint.parent;
               });
    out.push_back(std::move(resultValue));
  }
  llvm::sort(out,
             [](const InstanceRecord &a, const InstanceRecord &buildPoint) {
               return a.func < buildPoint.func;
             });
  return out;
}

static MemrefRecord mathCoreDebugRecord(MathCoreRecord memoryOp) {
  MemrefRecord rec;
  rec.id = memoryOp.func + "#math:" + memoryOp.function + ":" + memoryOp.type +
           ":" + memoryOp.arguments;
  rec.kind = "math_core";
  rec.name = memoryOp.coreName;
  rec.varname = "math_core:" + memoryOp.coreName;
  rec.func = memoryOp.func;
  rec.locText = memoryOp.loc;
  rec.elemType = memoryOp.type;
  rec.status = memoryOp.status;
  rec.ramType = "MATH_CORE";
  rec.ramReason = memoryOp.reason;
  rec.bram = static_cast<unsigned>(memoryOp.bram);

  rec.instances = memoryOp.functionInstances;
  rec.bramPerInstance =
      static_cast<unsigned>(memoryOp.bram / memoryOp.functionInstances);
  rec.math = std::move(memoryOp);
  return rec;
}

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
      llvm::cl::desc(
          "Cost only the memrefs of the func.funcs reachable from "
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

  Models models;
  std::string mathCostsPath;
  bool attributeGlobals = false, maxiAdapters = true, streamFifos = true,
       dataflowChannels = true, seqDualPort = true;
  /// The plugin chosen for each interface (the debug report's "plugins").
  llvm::json::Object pluginRecord;

  template <class Interface>
  std::unique_ptr<Interface>
  createPlugin(llvm::StringRef key, llvm::StringRef name,
               circt::hlsest::ConfigDiagnostics &diag) {
    auto &targetRegistry = circt::hlsest::PluginRegistry<Interface>::instance();
    std::unique_ptr<Interface> portValue =
        targetRegistry.create(name, config(), diag);
    if (portValue) {
      const circt::hlsest::PluginEntry *entryValue = targetRegistry.find(name);
      pluginRecord[key] =
          llvm::json::Object{{"name", name.str()},
                             {"origin", entryValue ? entryValue->origin : "?"}};
    }
    return portValue;
  }

  template <class Interface>
  void recordConfiguredPlugin(llvm::StringRef key, llvm::StringRef name) {
    const circt::hlsest::PluginEntry *entryValue =
        circt::hlsest::PluginRegistry<Interface>::instance().find(name);
    pluginRecord[key] =
        llvm::json::Object{{"name", name.str()},
                           {"origin", entryValue ? entryValue->origin : "?"}};
  }

  LogicalResult resolveConfiguration() {
    using circt::hlsest::resolveGlobalOption;
    const Config &cfg = config();
    const circt::hlsest::HlsToolConfig &hls = cfg.tool.hls;
    circt::hlsest::ConfigDiagnostics diag;

    std::string mapperName = cfg.tool.backend.memoryMapper.plugin;
    if (formulaOpt.hasValue())
      mapperName =
          formulaOpt == BramFormula::Band ? "vitis-band7" : "vitis-aspect-min";
    models.block = cfg.blockMemory();
    if (!models.block)
      diag.errors.push_back("tool.backend.memory_mapper.primitive: device '" +
                            cfg.device.id + "' has no memory '" +
                            cfg.tool.backend.memoryMapper.primitive + "'");
    models.mapper = createPlugin<circt::hlsest::MemoryMapper>("memory_mapper",
                                                              mapperName, diag);
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
      InFlightDiagnostic dimensionIndex =
          getOperation().emitError("--bram-analysis: ");
      llvm::interleave(diag.errors, dimensionIndex, "; ");
      return failure();
    }

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
        resolveGlobalOption(bramMaxiAdaptersOpt, maxi && maxi->enabled) && maxi;
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
      for (int64_t dimensionIndex : iface.getStaticShape()) {
        if (ShapedType::isDynamic(dimensionIndex))
          return;
        words *= dimensionIndex;
      }
      circt::hlsest::GroupCandidate candidateValue;
      candidateValue.op = op;
      if (auto valueHandle = op->getAttrOfType<StringAttr>("polygeist.varname"))
        candidateValue.name = valueHandle.getValue().str();
      else if (auto g = dyn_cast<memref::GlobalOp>(op))
        candidateValue.name = g.getSymName().str();
      candidateValue.request.words = words;
      candidateValue.request.writeWidth = elt.getIntOrFloatBitWidth();
      candidateValue.request.readWidths.push_back(
          candidateValue.request.writeWidth);
      groupCandidates.push_back(std::move(candidateValue));
    });
    models.grouping->group(groupCandidates, groups);
    for (auto [gi, g] : llvm::enumerate(groups))
      for (auto [pos, member] : llvm::enumerate(g.members))
        if (member < groupCandidates.size())
          groupOf[groupCandidates[member].op] = {static_cast<unsigned>(gi),
                                                 static_cast<unsigned>(pos)};
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
    for (unsigned memoryOp : g.members) {
      const circt::hlsest::GroupCandidate &candidateValue =
          groupCandidates[memoryOp];
      names += (names.empty() ? "" : ", ") + (candidateValue.name.empty()
                                                  ? std::string("?")
                                                  : candidateValue.name);
      words += candidateValue.request.words;
      width = std::max(width, candidateValue.request.writeWidth);
    }
    if (it->second.second == 0) {
      int64_t blocks =
          mapBlocks(*models.mapper, *models.block,
                    config().tool.hls.memoryArchitecture.pricedNarrow, words,
                    width, &rec.bankMath);
      cost.bramCount = static_cast<unsigned>(blocks);
      cost.note = "one memory for the group [" + names + "] (" + g.note +
                  "): " + std::to_string(words) + "x" + std::to_string(width) +
                  "b = " + std::to_string(blocks) + " " +
                  unitName(models.block);
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
        InFlightDiagnostic widthValue = mlir::emitWarning(module.getLoc())
                                        << "--bram-analysis: " << tops.size()
                                        << " public functions hold memrefs (";
        llvm::interleaveComma(tops, widthValue, [&](StringRef elementCount) {
          widthValue << "@" << elementCount;
        });
        widthValue
            << "); all of them are costed. Give the top function with "
               "--bram-analysis=top=<symbol> (or --symbol-privatize=exclude="
               "<top> --symbol-dce first) to cost only what it reaches";
      }
    }
    computeGroups(module, scope);
    int64_t total = 0;
    circt::hlsest::ResourceVector totalResources;

    std::vector<MemrefRecord> records;
    unsigned index = 0;

    SeqContext seqContext;
    seqContext.policy = models.policy.get();
    SeqContext *seq = seqDualPort ? &seqContext : nullptr;

    llvm::StringMap<SmallVector<Value>> globalSites;
    if (attributeGlobals)
      module.walk([&](memref::GetGlobalOp globalUse) {
        if (scope.covers(globalUse))
          globalSites[globalUse.getName()].push_back(globalUse.getResult());
      });

    InstanceModel instanceModel =
        computeInstances(module, [&](func::FuncOp fn) {
          return !scope.active() || scope.funcs.contains(fn.getOperation());
        });
    llvm::StringMap<SmallVector<func::FuncOp>> globalUsers;

    llvm::StringMap<SmallVector<Value>> globalUseSites;
    module.walk([&](memref::GetGlobalOp globalUse) {
      auto fn = globalUse->getParentOfType<func::FuncOp>();
      if (!fn || !scope.covers(globalUse))
        return;
      globalUseSites[globalUse.getName()].push_back(globalUse.getResult());
      auto &users = globalUsers[globalUse.getName()];
      if (!llvm::is_contained(users, fn))
        users.push_back(fn);
    });

    auto sitesOf = [&](Operation *op) -> SmallVector<Value> {
      if (auto g = dyn_cast<memref::GlobalOp>(op)) {
        auto it = globalUseSites.find(g.getSymName());
        return it == globalUseSites.end() ? SmallVector<Value>() : it->second;
      }
      return op->getNumResults() ? SmallVector<Value>{op->getResult(0)}
                                 : SmallVector<Value>();
    };
    ChannelPorts channelPorts(seq, &instanceModel, sitesOf);
    ProcessMerges processMerges([&](Value valueHandle) {
      SmallVector<ChannelAccess> out;
      for (const AccessSummary &a :
           collectAccessSummaries({valueHandle}, &instanceModel))
        out.push_back({a.via ? a.via : a.op, a.isWrite});
      return out;
    });

    llvm::DenseSet<Operation *> dataflowFuncs;
    module.walk([&](Operation *op) {
      if (op->hasAttr(kDataflowAttr))
        if (auto fn = isa<func::FuncOp>(op)
                          ? cast<func::FuncOp>(op)
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
        ++scope.skipped;
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

      std::optional<StreamHandleRecord> fifo;
      if (streamFifos)
        fifo = analyzeStreamHandle(
            op, allSites, [&](int64_t depth, unsigned bits) {
              return mapBlocks(*models.streamMapper, *models.block,
                               config().tool.hls.streams.pricedConfig, depth,
                               bits);
            });

      std::optional<BRAMCost> channel;
      if (!fifo && dataflowChannels && mayBeChannel(op))
        channel =
            tryDataflowChannel(iface, rec, allSites, seq, models,
                               &instanceModel, channelPorts, processMerges);
      BRAMCost cost = fifo ? estimateStreamFifos(iface, rec, std::move(*fifo))
                      : channel
                          ? *channel
                          : estimateBRAM(iface, rec, banks, attributed, seq,
                                         models, &instanceModel, allSites);

      applyGrouping(op, rec, cost);

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
        cost.note +=
            " x " + std::to_string(instances) + " instance(s) of @" +
            (rec.ownerFunc ? *rec.ownerFunc : (rec.func ? *rec.func : "?")) +
            " = " + std::to_string(cost.bramCount) +
            " (non-inlined callee, N14)";
        rec.bram = cost.bramCount;
      }
      if (sharedGlobal)
        cost.note += " (written static shared by every instance of its "
                     "functions: one memory in @" +
                     (rec.ownerFunc ? *rec.ownerFunc : std::string("?")) +
                     ", N14 R9)";

      const circt::hlsest::DeviceMemory *pricedBy =
          !rec.memoryId.empty() ? config().device.memory(rec.memoryId)
          : cost.bramCount      ? models.block
                                : nullptr;
      rec.resources = blockResources(pricedBy, cost.bramCount);
      unsigned primary = primaryCount(rec.resources);
      if (primary != cost.bramCount) {
        cost.bramCount = primary;
        rec.bram = primary;
      }
      llvm::outs() << op->getName() << " @ " << op->getLoc() << "\n"
                   << "  kind="
                   << (rec.fifo                        ? "FIFO"
                       : rec.pipo && rec.pipo->channel ? "PIPO"
                                                       : cost.label)
                   << "  " << resourceText(cost.bramCount, rec.resources)
                   << (cost.infeasible ? "  [INFEASIBLE]" : "") << "\n"
                   << "    " << cost.note << "\n";
      total += cost.bramCount;
      totalResources.add(rec.resources);
      records.push_back(std::move(rec));
    });

    if (maxiAdapters)
      for (auto &[fn, a] : collectAdapters(module, models)) {
        if (scope.active() && fn.getName() != scope.symbol)
          continue;
        unsigned bram = a.readBram + a.writeBram;
        circt::hlsest::ResourceVector adapterResources =
            blockResources(models.block, bram);
        totalResources.add(adapterResources);
        llvm::outs() << "m_axi.adapter bundle=" << a.bundle << " func=@"
                     << fn.getName() << " bram=" << bram << " (read FIFO ";
        if (a.readChannels > 1)
          llvm::outs() << a.readChannels << "x";
        llvm::outs() << a.readDepth << "x" << a.readBits << "b -> "
                     << a.readBram << ", write burst " << a.writeBurst << " -> "
                     << a.writeBram << ")\n";
        total += bram;
        MemrefRecord rec;
        rec.id = fn.getName().str() + "#m_axi:" + a.bundle;
        rec.kind = "m_axi_adapter";
        rec.name = a.bundle;
        rec.varname = a.bundle + "_m_axi";
        rec.func = fn.getName().str();
        rec.locText = locString(fn.getLoc());
        if (auto fieldValue = findFileLoc(fn.getLoc())) {
          rec.hasLoc = true;
          rec.locFile = fieldValue.getFilename().str();
          rec.locLine = fieldValue.getLine();
          rec.locCol = fieldValue.getColumn();
        }
        rec.shape = {a.readDepth};
        rec.elemType = "i" + std::to_string(a.busBits);
        rec.elemBits = a.busBits;
        rec.words = a.readDepth;
        rec.status = "counted";
        rec.ramType = "M_AXI_ADAPTER";
        rec.ramReason =
            "read FIFO: " + a.readRule + "; write buffer: " + a.writeRule;
        rec.bram = bram;
        rec.resources = adapterResources;
        rec.adapter = std::move(a);
        records.push_back(std::move(rec));
      }

    if (streamFifos && config().tool.hls.streams.dataflowArgumentFifos)
      module.walk([&](func::FuncOp fn) {
        if (scope.active() && fn.getName() != scope.symbol)
          return;
        for (DataflowArgumentFifo &fieldValue :
             processMerges.argumentFifos(fn)) {
          FifoPrice portValue = priceFifo(
              fieldValue.depth, fieldValue.bits, "",
              [&](int64_t depth, unsigned bits) {
                return mapBlocks(*models.streamMapper, *models.block,
                                 config().tool.hls.streams.pricedConfig, depth,
                                 bits);
              });
          circt::hlsest::ResourceVector passResult =
              blockResources(models.block, portValue.bram);
          totalResources.add(passResult);
          llvm::outs() << "dataflow.arg_fifo name=" << fieldValue.name
                       << " func=@" << fn.getName()
                       << " bram=" << portValue.bram << " (depth "
                       << fieldValue.depth << " x " << fieldValue.bits
                       << "b)\n";
          total += portValue.bram;
          MemrefRecord rec;
          rec.id = fn.getName().str() + "#arg_fifo:" + fieldValue.name;
          rec.kind = "dataflow_arg_fifo";
          rec.name = fieldValue.name;
          rec.varname = fieldValue.name;
          rec.func = fn.getName().str();
          rec.locText = locString(fn.getLoc());
          rec.shape = {fieldValue.depth};
          rec.elemType = "i" + std::to_string(fieldValue.bits);
          rec.elemBits = fieldValue.bits;
          rec.words = fieldValue.depth;
          rec.status = "counted";
          rec.ramType = "FIFO";
          rec.ramReason = "dataflow argument FIFO (N54): " + fieldValue.reason +
                          "; " + portValue.reason;
          rec.bram = portValue.bram;
          rec.resources = passResult;
          records.push_back(std::move(rec));
        }
      });

    if (!mathCostsPath.empty())
      for (MathCoreRecord &memoryOp : analyzeMathCores(
               module, mathCosts,
               [&](Operation *op) { return scope.covers(op); },
               [&](Operation *fn) {
                 return instanceModel.instancesOf(cast<func::FuncOp>(fn));
               },
               [&](Location loc, const std::string &msg) {
                 mlir::emitWarning(loc)
                     << "--bram-analysis: math-costs: " << msg;
               })) {
        printMathCoreLine(memoryOp, llvm::outs());
        total += memoryOp.bram;
        MemrefRecord mr = mathCoreDebugRecord(std::move(memoryOp));
        mr.resources.add(config().tool.report.primaryMemoryClass,
                         circt::hlsest::Rational(mr.bram));
        totalResources.add(mr.resources);
        records.push_back(std::move(mr));
      }

    if (config().tool.report.stdoutFormat != "per-class")
      llvm::outs() << "Total BRAM: " << total << "\n";
    else
      for (const std::string &cls : config().tool.report.classes)
        llvm::outs() << "Total " << cls << ": " << totalResources.get(cls).str()
                     << "\n";
    if (bramDebugOpt || !bramDebugJsonOpt.empty()) {
      size_t first = records.size();
      appendDeadRecords(module, index, records);
      if (scope.active())
        records.erase(std::remove_if(records.begin() + first, records.end(),
                                     [&](const MemrefRecord &resultValue) {
                                       return resultValue.func &&
                                              !scope.funcNames.contains(
                                                  *resultValue.func);
                                     }),
                      records.end());
    }

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
              records, pipelines, instanceRecords, total, fold, *models.mapper,
              llvm::json::Value(llvm::json::Object(pluginRecord)),
              totalResources.toJson(), scope, bramDebugJsonOpt)) {

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
} // namespace circt::hls_analysis
