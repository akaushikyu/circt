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
// Device model (Zynq-7020 / 7-series, UG473).
//===----------------------------------------------------------------------===//
// One BRAM_18K block holds 16*1024 = 16384 *data* bits (parity excluded; this is
// the S_bram value, NOT 18*1024). A RAMB36E1 is just two of these tiled, so we
// count everything in BRAM_18K units and let width/depth tiling synthesize the
// 36K cases.
//
// The per-block *data width* depends on how many ports must be live at once:
//
//     primitive / mode        gross width   data width   "# of 9b bytes"
//     RAMB18E1 TDP (2P/T2P)       18            16             2
//     RAMB18E1 1P / SDP (S2P)     36            32             4
//     RAMB36E1 TDP                36            32             4   (= 2x 18K)
//     RAMB36E1 SDP               72            64             8   (= 2x 18K)
//
// The x16-per-port limit is a *True-Dual-Port* effect: it applies only when the
// array needs two ports live in the SAME cycle (1R+1W read-modify, 2R, or 2W),
// which forces TDP where each port maxes at x18. With only one live port there
// is nothing to force TDP, so the block is used in its wide x36 config and a
// 512x32 array fits one 18K block -- this is why a time-shared single-port array
// (RAM_1P) is 1 BRAM, not 2. A simple-dual-port (RAM_S2P: one port read-only,
// one write-only) is likewise wide x36. So wide x32 == {RAM_1P, RAM_S2P};
// narrow x16 == {RAM_2P, RAM_T2P}. That x16 -> x32 difference is the whole
// story: at x16 a 32-bit element needs two width tiles (one RAMB36E1); at x32 it
// fits one 18K block. An 8/16-bit element fits x16, so contention never doubles
// it -- which is exactly the bug in the old flat "RAM_2P -> x2".
constexpr int64_t kBitsPerBRAM = 16 * 1024;

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
  int64_t factor = 0, dim = 0;
  std::optional<int64_t> bankIndex, bankCount;
  std::optional<std::string> reason; // hls.partition_reason
};

struct BankMathRecord {
  bool present = false;
  int64_t bitsPerBram = kBitsPerBRAM;
  unsigned maxWidth = 0;     // blockDataWidth(kind): 32 or 16
  unsigned configWidth = 0;  // width the block is configured at
  int64_t widthTiles = 0;
  int64_t depthPerBlock = 0;
  int64_t depthTiles = 0;
  int64_t replication = 1;
  int64_t blocks = 0;
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
// pattern to the narrowest mode that serves it; that mode then fixes the
// per-block data width in blockDataWidth(). Note this is count-only and never
// returns RAM_S2P: from counts a read-modify array (narrow RAM_2P) and a
// segregated producer/consumer (wide RAM_S2P) both look like 1R+1W. The wide
// case is decided structurally by the caller (concurrent + segregated) or via
// an explicit bind_storage pragma.
static KindResult selectStorageKind(const PortDemand &d) {
  KindResult r;
  unsigned total = d.total, w = d.writes, rd = d.reads;

  if (total <= 1) {
    r.kind = StorageKind::RAM_1P;          // one live port, wide x32
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
// Data bits one BRAM_18K block can present per cycle for the given kind.
unsigned blockDataWidth(StorageKind k) {
  switch (k) {
  case StorageKind::RAM_1P:   // one live port -> no TDP constraint -> wide
  case StorageKind::RAM_S2P:  // simple dual port: dedicated R + W -> wide
    return 32;
  case StorageKind::RAM_2P:   // two live ports (read-modify) -> TDP x18
  case StorageKind::RAM_T2P:  // two live ports -> TDP x18
  case StorageKind::RAM_1WNR:
    return 16;
  case StorageKind::LUTRAM:
  case StorageKind::URAM:
    return 0; // not mapped to BRAM
  }
  return 16;
}

int64_t ceilDiv(int64_t a, int64_t b) { return (a + b - 1) / b; }

// Round a data width up to a width the block can be configured at (1,2,4,8,16,
// 32...). A 24-bit element occupies an x32 slice and a 12-bit element an x16
// slice; that rounding is what wastes BRAM depth for non-power-of-two widths.
unsigned configWidth(unsigned w) {
  return w <= 1 ? 1u : static_cast<unsigned>(llvm::PowerOf2Ceil(w));
}

// BRAM_18K blocks needed for numElems x elemBits in the chosen kind.
// Width tiling handles elements wider than the per-block bus (the x16 -> x32
// promotion); depth tiling handles arrays deeper than one block at that width.
// `bm`, when given, receives the intermediate values for the debug report; it
// is write-only here and never feeds back into the arithmetic.
int64_t estimateBlocks(int64_t numElems, unsigned elemBits, StorageKind kind,
                       BankMathRecord *bm = nullptr) {
  unsigned wmax = blockDataWidth(kind);
  if (bm) {
    bm->present = true;
    bm->maxWidth = wmax;
  }
  if (wmax == 0 || numElems == 0 || elemBits == 0)
    return 0;

  int64_t widthTiles;
  unsigned cfgW;
  if (elemBits <= wmax) {
    widthTiles = 1;
    cfgW = std::min(configWidth(elemBits), wmax); // narrower elements pack deeper
  } else {
    widthTiles = ceilDiv(elemBits, wmax); // promote: each tile is a full x-wmax block
    cfgW = wmax;
  }
  int64_t depthPerBlock = std::max<int64_t>(kBitsPerBRAM / cfgW, 1);
  int64_t depthTiles = ceilDiv(numElems, depthPerBlock);
  int64_t blocks = widthTiles * depthTiles;
  if (bm) {
    bm->configWidth = cfgW;
    bm->widthTiles = widthTiles;
    bm->depthPerBlock = depthPerBlock;
    bm->depthTiles = depthTiles;
    bm->replication = 1;
    bm->blocks = blocks;
  }
  return blocks;
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

static std::string ramReasonFor(const PortDemand &d, const KindResult &kr,
                                bool attributed, bool anyStoreEnable) {
  std::string s;
  llvm::raw_string_ostream os(s);
  if (!attributed) {
    os << "global: accesses not attributed, default " << kindName(kr.kind);
    return s;
  }
  os << "peak port demand " << d.total << "/cycle (" << d.reads << "R+"
     << d.writes << "W, max over scopes)";
  if (kr.infeasible) {
    os << ": " << kr.note;
    return s;
  }
  if (d.total <= 1)
    os << ": at most one live port -> " << kindName(kr.kind) << " (x"
       << blockDataWidth(kr.kind) << " wide, no TDP constraint)";
  else
    os << ": " << d.reads << "R+" << d.writes << "W in the same cycle -> "
       << kindName(kr.kind) << " (x" << blockDataWidth(kr.kind)
       << "/port, true dual port)";
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
    } else if (bits == 0) {
      rec.status = "zero_size";
      rec.excludeReason = rec.words ? "zero-size array (0 bits)"
                                    : "dynamic shape; static size unknown (0 bits)";
    } else {
      rec.status = "excluded_small";
      rec.excludeReason = "size " + std::to_string(bits) +
                          " bits <= 1024-bit BRAM promotion threshold (32 words"
                          " x 32 bits); kept in LUTRAM/FFs";
    }
    // Still describe the accesses: useful when diagnosing a Vitis mismatch on
    // a small array, and it does not touch the estimate.
    SmallVector<AccessSummary> accesses =
        collectAccessSummaries(iface.getOperation());
    recordAccesses(accesses, rec);
    rec.demand = computePortDemand(accesses);
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
  KindResult kr = selectStorageKind(demand);
  // --- Width-aware block count ---
  int64_t blocks = estimateBlocks(numElems, elemBits, kr.kind, &rec.bankMath);
  cost.kind = kr.kind;
  cost.infeasible = kr.infeasible;
  cost.bramCount = static_cast<unsigned>(blocks);
  cost.note =
      !kr.note.empty()
          ? kr.note + " => " + std::to_string(blocks) + " BRAM"
          : (std::to_string(numElems) + "x" + std::to_string(elemBits) +
             "b -> " + kindName(kr.kind) + " (x" +
             std::to_string(blockDataWidth(kr.kind)) + "/block) = " +
             std::to_string(blocks) + " BRAM_18K");

  // --- Record ---
  recordAccesses(accesses, rec);
  rec.demand = demand;
  rec.status = kr.infeasible ? "infeasible" : "counted";
  rec.ramType = kindName(kr.kind);
  bool anyStoreEnable = llvm::any_of(
      rec.accesses, [](const AccessRecord &a) { return a.storeEnable; });
  rec.ramReason =
      ramReasonFor(demand, kr, rec.accessesAttributed, anyStoreEnable);
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
    os << "  ram type: " << r.ramType << " -- " << r.ramReason << "\n";
    if (r.bankMath.present) {
      const BankMathRecord &b = r.bankMath;
      os << "  bank math: " << b.bitsPerBram << " bits/BRAM_18K, max width "
         << b.maxWidth << " at " << r.ramType << ", element " << r.elemBits
         << "b -> config width " << b.configWidth << ", width tiles "
         << b.widthTiles << ", depth/block " << b.depthPerBlock
         << ", depth tiles ceil(" << (r.words ? *r.words : 0) << "/"
         << b.depthPerBlock << ")=" << b.depthTiles << ", replication "
         << b.replication << " -> " << b.blocks << " block(s)\n";
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

  if (r.bankMath.present) {
    const BankMathRecord &b = r.bankMath;
    llvm::json::Object bm;
    bm["bits_per_bram"] = b.bitsPerBram;
    bm["max_width"] = static_cast<int64_t>(b.maxWidth);
    bm["config_width"] = static_cast<int64_t>(b.configWidth);
    bm["width_tiles"] = b.widthTiles;
    bm["depth_per_block"] = b.depthPerBlock;
    bm["depth_tiles"] = b.depthTiles;
    bm["replication"] = b.replication;
    bm["blocks"] = b.blocks;
    o["bank_math"] = std::move(bm);
  } else {
    o["bank_math"] = nullptr;
  }
  o["bram"] = static_cast<int64_t>(r.bram);
  return o;
}

static void writeDebugJson(ArrayRef<MemrefRecord> records, int64_t total,
                           StringRef path) {
  llvm::json::Object root;
  root["version"] = 1;
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
  if (ec) {
    llvm::errs() << "bram-debug-json: cannot write '" << path
                 << "': " << ec.message() << "\n";
    return;
  }
  os << llvm::formatv("{0:2}", llvm::json::Value(std::move(root))) << "\n";
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

    // Debug output only; nothing above depends on these flags.
    if (bramDebugOpt)
      printDebugText(records, total, llvm::errs());
    if (!bramDebugJsonOpt.empty())
      writeDebugJson(records, total, bramDebugJsonOpt);
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
