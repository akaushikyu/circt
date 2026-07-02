#include "circt/Dialect/Resource/Passes/BRAMAnalysis.h"
#include "circt/Dialect/Resource/Interfaces/MemoryInterface.h"
#include "circt/Dialect/LoopSchedule/LoopScheduleOps.h"
#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/Dialect/MemRef/IR/MemRef.h"
#include "mlir/IR/BuiltinOps.h"
#include "mlir/Interfaces/LoopLikeInterface.h"
#include "mlir/Interfaces/SideEffectInterfaces.h"
#include "mlir/Pass/Pass.h"

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

namespace {

//===----------------------------------------------------------------------===//
// Device model (Zynq-7020 / 7-series RAMB18E1), as Vitis HLS 2025.1 prices it
// (VITIS_NOTES.md N6, 147 + 3 kernels; ~/hls-est-work/exp-notes/aspect.md,
// aspect_chk.md).
//===----------------------------------------------------------------------===//
// A RAMB18E1 holds 18*1024 = 18432 bits *including the parity bits*, in one of
// the aspect-ratio modes below (data bits per word x words). Vitis cuts a bank
// of D words x W bits into ceil(W/m) columns that all use the same mode m, each
// column takes P/depth(m) blocks with P = 2^ceil(log2 D) (the address space of
// the core, not the word count: 2500x18 one-port = 4, not 3), and it takes the
// cheapest mode:
//
//     BRAM_18K(W, D, wide) = min over m of ceil(W / m) * max(1, P / depth(m))
//
//     mode m (bits)  1      2     4     9     18    36
//     depth(m)       16384  8192  4096  2048  1024  512
//
// The x36 mode (both ports of the block ganged into one 36-bit port) is only
// available when at most ONE port is live per cycle (`wide`: Vitis' ram_1p, or
// an explicit ram_s2p). When two ports are live in the same cycle (a read and
// a write, or two reads, in one iteration of a pipelined loop: ram_2p /
// ram_t2p) each port is at most x18. Every copy of a replicated RAM_1WNR is a
// true-dual-port RAM (port A writes/reads, port B reads), so copies are priced
// narrow. Parity bits count: 1024x18 = 1, 2048x9 = 1, 512x36 wide = 1.
//
// Data points (Vitis): 1024x32 one-port 2, 4096x32 8 (wide or narrow), 64x32
// one-port 1 / two-port 2, 1024x40 3, 1024x72 4, 2048x24 3, 3072x20 5 (five
// x4 columns; mixed-width columns are not used), 1024x1 1.
constexpr int64_t kBitsPerBRAM = 18 * 1024; // incl. parity

struct AspectMode {
  unsigned width;  // data bits per word in this mode (parity included)
  int64_t depth;   // words per RAMB18E1 in this mode
};
constexpr AspectMode kAspectModes[] = {{1, 16384}, {2, 8192}, {4, 4096},
                                       {9, 2048},  {18, 1024}, {36, 512}};
constexpr unsigned kMaxPortWidthWide = 36;   // one live port (x36)
constexpr unsigned kMaxPortWidthNarrow = 18; // two live ports (TDP, x18)

struct PortDemand {
  unsigned reads = 0;
  unsigned writes = 0;
  unsigned total = 0;
  // True iff reads and writes are partitioned across scopes -- no single scope
  // both reads and writes this bank, and at least one scope of each exists. This
  // is the structural precondition for simple-dual-port (one port read-only, the
  // other write-only); only meaningful on the combined demand.
  bool segregated = false;
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
  Operation *scope = nullptr;
};

struct ScopeDemandRecord {
  std::string scopeKind;
  std::string scopeLoc;
  unsigned ii = 0;
  PortDemand demand;
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
};

struct BankMathRecord {
  bool present = false;
  int64_t bitsPerBram = kBitsPerBRAM;
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
};

// Per pipelined loop, what Vitis' replication rule saw (replication.md R2).
struct ReplicationLoopRecord {
  std::string scopeLoc;
  unsigned ii = 0;
  unsigned reads = 0;  // loads per iteration of the loop
  unsigned writes = 0; // stores per iteration of the loop
  unsigned need = 0;   // ceil((reads + writes) / ii): ports the loop needs
  unsigned copies = 0; // max(1, need - 1), capped
};

struct ReplicationRecord {
  bool present = false;     // the bank's accesses were attributed
  bool replicable = false;  // no loop body stores to the bank twice
  unsigned maxStoresPerLoop = 0;
  unsigned copies = 1;      // chosen copy count (1: plain RAM)
  SmallVector<ReplicationLoopRecord> loops;
  std::optional<std::string> limitingLoop; // scope that set `copies`
};

struct MemrefRecord {
  std::string id;
  std::optional<std::string> name;    // memref.global symbol
  std::optional<std::string> varname; // polygeist.varname / hls.bank_of
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
  SmallVector<AccessRecord> accesses;
  bool accessesAttributed = false; // false for globals (no SSA result)
  PortDemand demand;
  SmallVector<ScopeDemandRecord> perScope;

  std::string ramType;
  std::string ramReason;
  ReplicationRecord replication;
  BankMathRecord bankMath;
  unsigned bram = 0;
  bool infeasible = false;
};

//===----------------------------------------------------------------------===//
// Port demand: per temporal scope, then combined across scopes.
//===----------------------------------------------------------------------===//
// Peak demand within ONE loop. A pipelined scope (ii>=1) overlaps iterations, so
// accesses contend when they share a slot (stageStart % ii). A sequential scope
// (ii==0) issues at most one memory op per cycle, so reads and writes never
// collide regardless of how many there are.
PortDemand scopeDemand(ArrayRef<const AccessSummary *> group) {
  PortDemand d;
  if (group.empty())
    return d;

  unsigned ii = group.front()->ii;
  assert(llvm::all_of(group, [&](auto *a) { return a->ii == ii; }) &&
         "scopeDemand requires a single-II group; bucket by scope first");

  // Sequential scope: the body runs to completion before the next iteration, so
  // there is no cross-iteration overlap and at most one access is in flight
  // regardless of latency.
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

// Combine per-loop demand into a single requirement for the shared bank.
//   sequential loops  -> element-wise MAX (the array is time-shared)
static PortDemand computePortDemand(ArrayRef<AccessSummary> accesses) {
  std::map<Operation *, SmallVector<const AccessSummary *>> byScope;
  for (const auto &a : accesses)
    byScope[a.scope].push_back(&a);

  PortDemand combined;
  bool anyRead = false, anyWrite = false, anyReadModifyScope = false;
  for (const auto &kv : byScope) {
    PortDemand local = scopeDemand(kv.second);
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

//===----------------------------------------------------------------------===//
// Kind naming (declared early; used in notes).
//===----------------------------------------------------------------------===//
const char *kindName(StorageKind k) {
  switch (k) {
  case StorageKind::RAM_1P:   return "RAM_1P";
  case StorageKind::RAM_2P:   return "RAM_2P";
  case StorageKind::RAM_S2P:  return "RAM_S2P";
  case StorageKind::RAM_T2P:  return "RAM_T2P";
  case StorageKind::RAM_1WNR: return "RAM_1WNR";
  case StorageKind::LUTRAM:   return "LUTRAM";
  case StorageKind::URAM:     return "URAM";
  }
  return "?";
}

//===----------------------------------------------------------------------===//
// Storage-kind inference from port demand (replaces the old flat multiplier).
//===----------------------------------------------------------------------===//
struct KindResult {
  StorageKind kind = StorageKind::RAM_1P;
  bool infeasible = false; // demand exceeds the 2 physical ports of one block
  std::string note;
};

// A single BRAM primitive has at most two ports. Map the per-cycle access
// pattern to the narrowest mode that serves it; that mode then fixes whether
// the x36 aspect ratio is allowed (isWideKind). Note this is count-only and
// never returns RAM_S2P: from counts a read-modify array (narrow RAM_2P) and a
// segregated producer/consumer (wide RAM_S2P) both look like 1R+1W, and Vitis'
// automatic storage inference never picks ram_s2p either (aspect.md R2) - only
// an explicit bind_storage pragma does.
static KindResult selectStorageKind(const PortDemand &d) {
  KindResult r;
  unsigned total = d.total, w = d.writes, rd = d.reads;

  if (total <= 1) {
    r.kind = StorageKind::RAM_1P;          // one live port, wide x36
    return r;
  }
  if (total == 2) {
    r.kind = (rd == 1 && w == 1) ? StorageKind::RAM_2P
                                 : StorageKind::RAM_T2P;
    return r;
  }

  r.kind = StorageKind::RAM_T2P;
  r.infeasible = true;
  r.note = "port demand " + std::to_string(total) + "/cycle (" +
           std::to_string(rd) + "R+" + std::to_string(w) +
           "W, multi-writer) exceeds 2 ports; needs array_partition.";
  return r;
}

//===----------------------------------------------------------------------===//
// Width-aware block count.
//===----------------------------------------------------------------------===//
// Whether the kind leaves at most one port live per cycle, so the block may
// use the x36 aspect ratio (both ports ganged). Two live ports (true dual
// port) cap each port at x18.
bool isWideKind(StorageKind k) {
  switch (k) {
  case StorageKind::RAM_1P:   // one live port -> no TDP constraint -> wide
  case StorageKind::RAM_S2P:  // simple dual port: dedicated R + W -> wide
    return true;
  case StorageKind::RAM_2P:   // two live ports (read-modify) -> TDP x18
  case StorageKind::RAM_T2P:  // two live ports -> TDP x18
  case StorageKind::RAM_1WNR: // every copy is a TDP RAM -> x18
  case StorageKind::LUTRAM:
  case StorageKind::URAM:
    return false;
  }
  return false;
}

// Widest aspect-ratio mode (data bits per port) the kind allows.
unsigned blockDataWidth(StorageKind k) {
  if (k == StorageKind::LUTRAM || k == StorageKind::URAM)
    return 0; // not mapped to BRAM
  return isWideKind(k) ? kMaxPortWidthWide : kMaxPortWidthNarrow;
}

int64_t ceilDiv(int64_t a, int64_t b) { return (a + b - 1) / b; }

// BRAM_18K blocks for ONE copy of numElems x elemBits: the min over the
// aspect-ratio modes of ceil(elemBits / m) columns x max(1, P / depth(m))
// blocks per column, P = 2^ceil(log2 numElems) (N6). `wide` allows the x36
// mode. `bm`, when given, receives the intermediate values of the winning
// mode for the debug report; it is write-only here and never feeds back into
// the arithmetic.
int64_t estimateBlocks(int64_t numElems, unsigned elemBits, bool wide,
                       BankMathRecord *bm = nullptr) {
  if (bm) {
    bm->present = true;
    bm->wide = wide;
    bm->maxWidth = wide ? kMaxPortWidthWide : kMaxPortWidthNarrow;
  }
  if (numElems <= 0 || elemBits == 0)
    return 0;

  int64_t addrDepth = static_cast<int64_t>(llvm::PowerOf2Ceil(
      static_cast<uint64_t>(numElems)));
  int64_t best = -1;
  AspectMode bestMode{0, 0};
  int64_t bestCols = 0, bestPerCol = 0;
  // Widest mode first, so a tie is reported as the fewest-columns layout.
  for (const AspectMode &mode : llvm::reverse(kAspectModes)) {
    if (!wide && mode.width > kMaxPortWidthNarrow)
      continue;
    int64_t cols = ceilDiv(elemBits, mode.width);
    int64_t perCol = std::max<int64_t>(addrDepth / mode.depth, 1);
    int64_t blocks = cols * perCol;
    if (best < 0 || blocks < best) {
      best = blocks;
      bestMode = mode;
      bestCols = cols;
      bestPerCol = perCol;
    }
  }
  if (bm) {
    bm->configWidth = bestMode.width;
    bm->widthTiles = bestCols;
    bm->depthPerBlock = bestMode.depth;
    bm->addrDepth = addrDepth;
    bm->depthTiles = bestPerCol;
    bm->blocksPerCopy = best;
    bm->replication = 1;
    bm->blocks = best;
  }
  return best;
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
unsigned portOccupancy(bool /*isWrite*/) { return 1u; }

// Classify an op's effect on `mem`. Works for memref.load/store, affine
// load/store, or any op exposing memory effects; non-accessing aliasing ops
// (subview, cast, dealloc) report no read/write effect and are skipped.
bool classifyAccess(Operation *op, Value mem, bool &isWrite) {
  auto eff = dyn_cast<MemoryEffectOpInterface>(op);
  if (!eff)
    return false;
  SmallVector<MemoryEffects::EffectInstance> effects;
  eff.getEffects(effects);
  bool reads = false, writes = false;
  for (auto &e : effects) {
    if (e.getValue() && e.getValue() != mem)
      continue;
    if (isa<MemoryEffects::Read>(e.getEffect()))
      reads = true;
    else if (isa<MemoryEffects::Write>(e.getEffect()))
      writes = true;
  }
  if (!reads && !writes)
    return false;
  isWrite = writes; // a read-modify-write op needs a write port
  return true;
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


SmallVector<AccessSummary>
collectAccessSummaries(Operation *allocOp) {
  SmallVector<AccessSummary> out;
  if (allocOp->getNumResults() == 0)
    return out;
  Value mem = allocOp->getResult(0); // the bank's memref

  for (Operation *user : mem.getUsers()) {
    bool isWrite = false;
    if (!classifyAccess(user, mem, isWrite))
      continue;

    AccessSummary a;
    a.op = user;
    a.isWrite = isWrite;
    a.latency = portOccupancy(isWrite);

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
  return out;
}

//===----------------------------------------------------------------------===//
// Debug-record helpers (read-only views of the IR; no influence on the cost).
//===----------------------------------------------------------------------===//

// First file:line:col reachable through fused / named / call-site wrappers.
static FileLineColLoc findFileLoc(Location loc) {
  if (auto f = dyn_cast<FileLineColLoc>(loc))
    return f;
  if (auto n = dyn_cast<NameLoc>(loc))
    return findFileLoc(n.getChildLoc());
  if (auto c = dyn_cast<CallSiteLoc>(loc))
    return findFileLoc(c.getCallee());
  if (auto fu = dyn_cast<FusedLoc>(loc))
    for (Location l : fu.getLocations())
      if (auto f = findFileLoc(l))
        return f;
  if (auto o = dyn_cast<OpaqueLoc>(loc))
    return findFileLoc(o.getFallbackLocation());
  return {};
}

static std::string locString(Location loc) {
  if (auto f = findFileLoc(loc))
    return (f.getFilename().str() + ":" + std::to_string(f.getLine()) + ":" +
            std::to_string(f.getColumn()));
  if (isa<UnknownLoc>(loc))
    return "<unknown>";
  std::string s;
  llvm::raw_string_ostream os(s);
  loc.print(os);
  return s;
}

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
}

// Per-access and per-scope views of the same summaries the estimate used.
static void recordAccesses(ArrayRef<AccessSummary> accesses, MemrefRecord &r) {
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
    sd.demand = scopeDemand(group);
    r.perScope.push_back(std::move(sd));
  }
}

//===----------------------------------------------------------------------===//
// Replication (RAM_1WNR), VITIS_NOTES.md N4 / replication.md R1-R3.
//===----------------------------------------------------------------------===//
// Per pipelined loop L with R loads and W stores of the bank per iteration at
// II: Vitis needs ceil((R + W) / II) port-cycles per II; one true-dual-port
// RAM gives two, every further one comes from a copy whose port B serves
// reads while port A of all copies is the single shared write port (reading
// when idle). So copies = max(1, ceil((R + W) / II) - 1), capped at 16, max
// over the loops that access the bank. A bank that some loop body stores to
// more than once is never replicated (one shared write port cannot take two
// writes per iteration): it stays a plain 2-port RAM and the scheduler has
// raised that loop's II to ceil((R + W) / 2) instead (MemrefBankClassification).
// Straight-line code outside any loop does not take part (the rule was only
// observed on loop bodies).
static ReplicationRecord analyzeReplication(ArrayRef<AccessSummary> accesses,
                                            bool attributed) {
  ReplicationRecord r;
  r.present = attributed;
  if (!attributed)
    return r;

  struct ScopeStats {
    Operation *scope = nullptr;
    unsigned reads = 0, writes = 0, ii = 0;
  };
  SmallVector<ScopeStats> scopes; // first-appearance order (deterministic)
  for (const AccessSummary &a : accesses) {
    ScopeStats *st = nullptr;
    for (ScopeStats &s : scopes)
      if (s.scope == a.scope)
        st = &s;
    if (!st) {
      scopes.push_back({a.scope, 0, 0, a.ii});
      st = &scopes.back();
    }
    (a.isWrite ? st->writes : st->reads)++;
  }

  r.maxStoresPerLoop = 0;
  for (const ScopeStats &s : scopes) {
    bool isLoopBody = s.scope && (isa<LoopSchedulePipelineOp>(s.scope) ||
                                  isa<LoopLikeOpInterface>(s.scope));
    if (isLoopBody)
      r.maxStoresPerLoop = std::max(r.maxStoresPerLoop, s.writes);
  }
  r.replicable = r.maxStoresPerLoop <= 1;
  r.copies = 1;
  for (const ScopeStats &s : scopes) {
    if (!s.scope || !isa<LoopSchedulePipelineOp>(s.scope) || s.ii == 0)
      continue;
    ReplicationLoopRecord lr;
    lr.scopeLoc = locString(s.scope->getLoc());
    lr.ii = s.ii;
    lr.reads = s.reads;
    lr.writes = s.writes;
    lr.need = static_cast<unsigned>(ceilDiv(s.reads + s.writes, s.ii));
    unsigned c = lr.need > 1 ? lr.need - 1 : 1;
    lr.copies = std::min(c, kMaxReplicationCopies);
    if (r.replicable && lr.copies > r.copies) {
      r.copies = lr.copies;
      r.limitingLoop = lr.scopeLoc;
    }
    r.loops.push_back(std::move(lr));
  }
  if (!r.replicable)
    r.copies = 1;
  return r;
}

static std::string ramReasonFor(const PortDemand &d, const KindResult &kr,
                                const ReplicationRecord &rep, bool attributed,
                                bool anyStoreEnable, bool demandClamped) {
  std::string s;
  llvm::raw_string_ostream os(s);
  if (!attributed) {
    os << "global: accesses not attributed, default " << kindName(kr.kind);
    return s;
  }
  if (kr.kind == StorageKind::RAM_1WNR) {
    os << "replicable (no loop body stores to it more than once)";
    if (rep.limitingLoop) {
      for (const ReplicationLoopRecord &l : rep.loops)
        if (l.scopeLoc == *rep.limitingLoop) {
          os << "; pipeline @ " << l.scopeLoc << ": " << l.reads << "R+"
             << l.writes << "W per iteration at II " << l.ii
             << " needs ceil(" << (l.reads + l.writes) << "/" << l.ii
             << ")=" << l.need << " port-cycles";
          break;
        }
    }
    os << " -> RAM_1WNR with " << rep.copies
       << " copies (port B of every copy reads, port A of all copies is the "
          "shared write port and reads when idle";
    if (rep.copies >= kMaxReplicationCopies)
      os << "; capped at " << kMaxReplicationCopies;
    os << "); each copy is a true-dual-port RAM (x18/port)";
    return s;
  }
  os << "peak port demand " << d.total << "/cycle (" << d.reads << "R+"
     << d.writes << "W, max over scopes)";
  if (kr.infeasible) {
    os << ": " << kr.note;
    return s;
  }
  if (demandClamped)
    os << ", clamped to 2 ports (replicable bank, but no pipelined loop needs "
          "more than ceil((R+W)/II) <= 2 port-cycles, so Vitis spreads the "
          "accesses over the II)";
  if (d.total <= 1 && !demandClamped)
    os << ": at most one live port -> " << kindName(kr.kind) << " (x"
       << blockDataWidth(kr.kind) << " wide, no TDP constraint)";
  else
    os << ": two ports live in the same cycle -> " << kindName(kr.kind)
       << " (x" << blockDataWidth(kr.kind) << "/port, true dual port)";
  if (!rep.replicable)
    os << "; not replicable: a loop body stores to it " << rep.maxStoresPerLoop
       << " times (Vitis keeps one 2-port RAM and raises that loop's II)";
  else if (!rep.loops.empty())
    os << "; replicable, but every pipelined loop needs <= 2 port-cycles per "
          "II (no RAM_1WNR)";
  if (d.segregated)
    os << "; reads and writes live in different scopes (RAM_S2P-eligible) but "
          "count-only selection never picks RAM_S2P";
  if (anyStoreEnable)
    os << "; hls.store_enable counts as a write only (no phantom read port)";
  return s;
}

//===----------------------------------------------------------------------===//
// Top-level estimator.
//===----------------------------------------------------------------------===//
// Post-banking the memref IS one bank: no partition factor, no affine bank-id
// analysis. Geometry comes straight off the shape.
//
// `rec` is filled with the intermediate values of this very computation for the
// debug report; it is never read here, so the estimate does not depend on it.
static BRAMCost estimateBRAM(MemoryResourceOpInterface iface,
                             MemrefRecord &rec) {
  BRAMCost cost;
  cost.kind = StorageKind::RAM_1P;
  cost.bramCount = 0;

  // Geometry for the record (safe for any element type; the estimate below
  // reads the same values).
  {
    rec.shape = iface.getStaticShape();
    Type elt = iface.getElementType();
    llvm::raw_string_ostream os(rec.elemType);
    elt.print(os);
    rec.elemBits = elt.isIntOrFloat() ? elt.getIntOrFloatBitWidth()
                  : isa<IndexType>(elt) ? 64u
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
    rec.accessesAttributed = iface.getOperation()->getNumResults() > 0;
  }

  if (!iface.contributesToBRAMCost()) {
    cost.note = "excluded from BRAM accounting (LUTRAM / stream / zero-size)";
    // Explain which exclusion rule fired (mirrors contributesToBRAMCostImpl).
    int64_t bits = iface.getStaticSizeInBits();
    auto pragmaKind = iface.getPragmaStorageKind();
    if (pragmaKind && *pragmaKind == StorageKind::LUTRAM) {
      rec.status = "excluded_small";
      rec.excludeReason = "pragma storage kind LUTRAM; not BRAM-backed";
    } else if (bits == 0 && !rec.words) {
      // A dynamic extent makes the static size 0, which the cost interface
      // treats as "does not contribute"; report it as what it is.
      rec.status = "dynamic_shape";
      rec.excludeReason = "dynamic shape; static size unknown; not estimated";
    } else if (bits == 0) {
      rec.status = "zero_size";
      rec.excludeReason = "zero-size array (0 bits)";
    } else {
      rec.status = "excluded_small";
      rec.excludeReason = "size " + std::to_string(bits) + " bits < " +
                          std::to_string(kBRAMPromotionBits) +
                          "-bit BRAM promotion threshold (Words*Bits >= " +
                          std::to_string(kBRAMPromotionBits) +
                          " -> BRAM); distributed RAM, 0 BRAM";
    }
    // Still describe the accesses: useful when diagnosing a Vitis mismatch on
    // a small array, and it does not touch the estimate.
    SmallVector<AccessSummary> accesses =
        collectAccessSummaries(iface.getOperation());
    recordAccesses(accesses, rec);
    rec.demand = computePortDemand(accesses);
    rec.replication =
        analyzeReplication(accesses, rec.accessesAttributed);
    rec.ramType = kindName(cost.kind);
    rec.ramReason = "not selected: " + cost.note;
    rec.bram = cost.bramCount;
    return cost;
  }

  // --- Bank geometry ---
  auto shape = iface.getStaticShape();
  int64_t numElems = 1;
  for (int64_t dim : shape) {
    if (ShapedType::isDynamic(dim)) {
      cost.note = "dynamic shape; not estimated";
      rec.status = "dynamic_shape";
      rec.excludeReason = cost.note;
      rec.ramType = kindName(cost.kind);
      rec.ramReason = "not selected: " + cost.note;
      rec.bram = cost.bramCount;
      return cost;
    }
    numElems *= dim;
  }
  unsigned elemBits = iface.getElementType().getIntOrFloatBitWidth();
  if (numElems == 0 || elemBits == 0) {
    cost.note = "zero-size";
    rec.status = "zero_size";
    rec.excludeReason = cost.note;
    rec.ramType = kindName(cost.kind);
    rec.ramReason = "not selected: " + cost.note;
    rec.bram = cost.bramCount;
    return cost;
  }
  // --- Port contention -> storage kind ---
  SmallVector<AccessSummary> accesses =
      collectAccessSummaries(iface.getOperation());
  PortDemand demand = computePortDemand(accesses);
  ReplicationRecord rep =
      analyzeReplication(accesses, rec.accessesAttributed);
  KindResult kr;
  bool demandClamped = false;
  int64_t blocks;
  if (rep.copies > 1) {
    // RAM_1WNR: `copies` true-dual-port RAMs holding identical data.
    kr.kind = StorageKind::RAM_1WNR;
    int64_t perCopy =
        estimateBlocks(numElems, elemBits, /*wide=*/false, &rec.bankMath);
    blocks = perCopy * rep.copies;
    rec.bankMath.replication = rep.copies;
    rec.bankMath.blocks = blocks;
  } else {
    PortDemand d = demand;
    if (rep.replicable && d.total > 2) {
      // The scheduler grants a replicable bank 17 slots per cycle, so it may
      // pack more than two accesses into one cycle even when ceil((R+W)/II)
      // <= 2 (the II was raised by something else). Vitis then spreads them
      // over the II on the two ports of one plain RAM.
      demandClamped = true;
      d.total = 2;
      d.reads = std::min(d.reads, 2u);
      d.writes = std::min(d.writes, 2u);
      if (d.reads >= 1 && d.writes >= 1)
        d.reads = d.writes = 1;
    }
    kr = selectStorageKind(d);
    blocks = estimateBlocks(numElems, elemBits, isWideKind(kr.kind),
                            &rec.bankMath);
  }
  cost.kind = kr.kind;
  cost.infeasible = kr.infeasible;
  cost.bramCount = static_cast<unsigned>(blocks);
  if (!kr.note.empty())
    cost.note = kr.note + " => " + std::to_string(blocks) + " BRAM";
  else if (kr.kind == StorageKind::RAM_1WNR)
    cost.note = std::to_string(numElems) + "x" + std::to_string(elemBits) +
                "b -> RAM_1WNR, " + std::to_string(rep.copies) +
                " copies x " + std::to_string(rec.bankMath.blocksPerCopy) +
                " (x18/port) = " + std::to_string(blocks) + " BRAM_18K";
  else
    cost.note = std::to_string(numElems) + "x" + std::to_string(elemBits) +
                "b -> " + kindName(kr.kind) + " (x" +
                std::to_string(blockDataWidth(kr.kind)) + "/port) = " +
                std::to_string(blocks) + " BRAM_18K";

  // --- Record ---
  recordAccesses(accesses, rec);
  rec.demand = demand;
  rec.replication = rep;
  rec.status = kr.infeasible ? "infeasible" : "counted";
  rec.ramType = kindName(kr.kind);
  bool anyStoreEnable = llvm::any_of(
      rec.accesses, [](const AccessRecord &a) { return a.storeEnable; });
  rec.ramReason = ramReasonFor(demand, kr, rep, rec.accessesAttributed,
                               anyStoreEnable, demandClamped);
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

static void printDebugText(ArrayRef<MemrefRecord> records, int64_t total,
                           llvm::raw_ostream &os) {
  os << "=== bram-debug: how each BRAM number was derived ===\n";
  for (const MemrefRecord &r : records) {
    os << "[" << r.id << "] " << displayName(r) << " (" << r.kind;
    if (r.name && r.varname)
      os << " @" << *r.name;
    os << ") @ " << r.locText << "\n";
    os << "  shape " << shapeString(r.shape) << " x " << r.elemType << " ("
       << r.elemBits << " bits)";
    if (r.words)
      os << " = " << *r.words << " words";
    os << "\n";
    os << "  status: " << r.status;
    if (r.excludeReason)
      os << " -- " << *r.excludeReason;
    os << "\n";
    if (r.partition.present) {
      const PartitionRecord &p = r.partition;
      os << "  partition: " << p.kind << " factor=" << p.factor
         << " dim=" << p.dim << " source=" << p.source;
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
        os << "\n";
      }
      os << "  port demand: reads=" << r.demand.reads
         << " writes=" << r.demand.writes << " total=" << r.demand.total
         << " (max over scopes"
         << (r.demand.segregated ? "; segregated R/W" : "") << ")\n";
      for (const ScopeDemandRecord &s : r.perScope)
        os << "    scope " << s.scopeKind << " @ " << s.scopeLoc
           << " ii=" << s.ii << ": reads=" << s.demand.reads
           << " writes=" << s.demand.writes << " total=" << s.demand.total
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
           << " port-cycles -> copies " << l.copies << "\n";
    }
    os << "  ram type: " << r.ramType << " -- " << r.ramReason << "\n";
    if (r.bankMath.present) {
      const BankMathRecord &b = r.bankMath;
      os << "  bank math: " << b.bitsPerBram << " bits/BRAM_18K (incl. parity), "
         << (b.wide ? "one live port -> x36 allowed" : "two live ports -> x18 max")
         << " at " << r.ramType << ", element " << r.elemBits
         << "b -> mode x" << b.configWidth << ": columns ceil(" << r.elemBits
         << "/" << b.configWidth << ")=" << b.widthTiles << ", depth/block "
         << b.depthPerBlock << ", address depth 2^ceil(log2 "
         << (r.words ? *r.words : 0) << ")=" << b.addrDepth
         << ", blocks/column max(1," << b.addrDepth << "/" << b.depthPerBlock
         << ")=" << b.depthTiles << " -> " << b.blocksPerCopy
         << " per copy, replication " << b.replication << " -> " << b.blocks
         << " block(s)\n";
    }
    os << "  bram: " << r.bram << (r.infeasible ? "  [INFEASIBLE]" : "")
       << "\n";
  }
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
    accesses.push_back(std::move(ao));
  }
  o["accesses"] = std::move(accesses);

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
    o["bank_math"] = std::move(bm);
  } else {
    o["bank_math"] = nullptr;
  }
  o["bram"] = static_cast<int64_t>(r.bram);
  return o;
}

// Returns the error code of the failed open, or a default (success) code.
static std::error_code writeDebugJson(ArrayRef<MemrefRecord> records,
                                      int64_t total, StringRef path) {
  llvm::json::Object root;
  root["version"] = 2;
  root["total_bram"] = total;

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

  llvm::json::Array summary;
  for (const MemrefRecord *r : sortedByBram(records)) {
    llvm::json::Object s;
    s["id"] = r->id;
    s["varname"] = optStr(r->varname);
    s["bram"] = static_cast<int64_t>(r->bram);
    summary.push_back(std::move(s));
  }
  root["summary"] = std::move(summary);

  std::error_code ec;
  llvm::raw_fd_ostream os(path, ec, llvm::sys::fs::OF_Text);
  if (ec)
    return ec;
  os << llvm::formatv("{0:2}", llvm::json::Value(std::move(root))) << "\n";
  return std::error_code();
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

  void runOnOperation() override {
    int64_t total = 0;
    // One record per memref, in walk order, kept for the debug report.
    std::vector<MemrefRecord> records;
    unsigned index = 0;
    getOperation().walk([&](Operation *op) {
      auto iface = dyn_cast<MemoryResourceOpInterface>(op);
      if (!iface)
        return;
      MemrefRecord rec;
      describeMemref(op, index++, rec);
      BRAMCost cost = estimateBRAM(iface, rec);
      llvm::outs() << op->getName() << " @ " << op->getLoc() << "\n"
                   << "  kind=" << kindName(cost.kind)
                   << "  bram=" << cost.bramCount
                   << (cost.infeasible ? "  [INFEASIBLE]" : "") << "\n"
                   << "    " << cost.note << "\n";
      total += cost.bramCount;
      records.push_back(std::move(rec));
    });
    llvm::outs() << "Total BRAM: " << total << "\n";

    // Debug output only; nothing above depends on these flags. The estimate
    // and the stdout report are complete by now; a JSON path that cannot be
    // opened is still an error (non-zero exit), so a harness that asked for
    // the file never mistakes its absence for an empty result.
    if (bramDebugOpt)
      printDebugText(records, total, llvm::errs());
    if (!bramDebugJsonOpt.empty())
      if (std::error_code ec =
              writeDebugJson(records, total, bramDebugJsonOpt)) {
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
