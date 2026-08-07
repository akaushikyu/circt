

#include "circt/Dialect/Resource/Passes/BRAMAnalysis.h"
#include "circt/Dialect/LoopSchedule/LoopScheduleOps.h"
#include "circt/Dialect/Resource/Interfaces/MemoryInterface.h"
#include "circt/Dialect/Resource/Passes/CallInstances.h"
#include "circt/Dialect/Resource/Passes/LoopPragmas.h"
#include "mlir/Dialect/Affine/IR/AffineOps.h"
#include "mlir/Dialect/Arith/IR/Arith.h"
#include "mlir/Dialect/Func/IR/FuncOps.h"
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

constexpr int64_t kBitsPerBRAM = 18 * 1024;

struct AspectMode {
  unsigned width;
  int64_t depth;
};
constexpr AspectMode kAspectModes[] = {{1, 16384}, {2, 8192},  {4, 4096},
                                       {9, 2048},  {18, 1024}, {36, 512}};
constexpr unsigned kMaxPortWidthWide = 36;
constexpr unsigned kMaxPortWidthNarrow = 18;

struct PortDemand {
  unsigned reads = 0;
  unsigned writes = 0;
  unsigned total = 0;

  bool segregated = false;
};

enum class BramFormula { Band, N6 };

const char *formulaName(BramFormula fieldValue) {
  return fieldValue == BramFormula::Band ? "band" : "n6";
}

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
    if (auto globalOp = dyn_cast<memref::GlobalOp>(op))
      return globals.contains(globalOp.getSymName());
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
  Operation *scope = nullptr;

  std::string inFunc;
  std::optional<std::string> viaCall;

  bool portBound = false;
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
};

struct BankMathRecord {
  bool present = false;
  int64_t bitsPerBram = kBitsPerBRAM;
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

struct ReplicationLoopRecord {
  std::string scopeLoc;
  unsigned ii = 0;
  unsigned reads = 0;
  unsigned writes = 0;
  unsigned need = 0;
  unsigned copies = 0;

  bool portBound = false;
};

struct ReplicationRecord {
  bool present = false;
  bool replicable = false;
  unsigned maxStoresPerLoop = 0;
  unsigned copies = 1;
  SmallVector<ReplicationLoopRecord> loops;
  std::optional<std::string> limitingLoop;

  bool portBoundLimited = false;
};

struct AdapterRecord {
  std::string bundle;
  SmallVector<std::string> ports;
  unsigned busBits = 32;
  int64_t readBurst = 16, readOutstanding = 16;
  int64_t writeBurst = 16, writeOutstanding = 16;
  bool hasRead = false, hasWrite = false;
  bool passedToCall = false;
  bool unresolvedCall = false;
  int64_t readDepth = 0;
  unsigned readBram = 0, writeBram = 0;
  std::string readRule, writeRule;
};

struct MemrefRecord {
  std::string id;
  std::optional<std::string> name;
  std::optional<std::string> varname;
  std::optional<std::string> fromGlobal;

  std::optional<std::string> keptReason;
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
  SmallVector<AccessRecord> accesses;
  bool accessesAttributed = false;
  bool rom = false;
  std::optional<AdapterRecord> adapter;
  PortDemand demand;
  SmallVector<ScopeDemandRecord> perScope;

  std::string ramType;
  std::string ramReason;
  ReplicationRecord replication;
  BankMathRecord bankMath;
  unsigned bram = 0;
  bool infeasible = false;

  unsigned instances = 1;
  unsigned bramPerInstance = 0;
  std::optional<std::string> ownerFunc;
};

struct InstanceRecord {
  std::string func;
  unsigned instances = 1;
  bool inlineOff = false;
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

class SeqScopeIndex {
public:
  struct OpInfo {
    unsigned stretch = 0;
    unsigned ordinal = 0;

    SmallVector<std::pair<Operation *, unsigned>, 2> arms;
  };
  struct Scope {
    DenseMap<Operation *, OpInfo> info;
    std::vector<std::vector<Operation *>> stretches;
  };

  const Scope &get(Operation *scope) {
    std::unique_ptr<Scope> &slot = scopes[scope];
    if (!slot) {
      slot = std::make_unique<Scope>();
      unsigned cur = 0;
      SmallVector<std::pair<Operation *, unsigned>, 2> arms;
      for (Region &region : scope->getRegions())
        for (Block &block : region) {
          walkBlock(block, *slot, cur, arms);
          ++cur;
        }
    }
    return *slot;
  }

private:
  DenseMap<Operation *, std::unique_ptr<Scope>> scopes;

  static void add(Operation *op, Scope &stringValue, unsigned cur,
                  ArrayRef<std::pair<Operation *, unsigned>> arms) {
    if (stringValue.stretches.size() <= cur)
      stringValue.stretches.resize(cur + 1);
    OpInfo info;
    info.stretch = cur;
    info.ordinal = stringValue.stretches[cur].size();
    info.arms.assign(arms.begin(), arms.end());
    stringValue.stretches[cur].push_back(op);
    stringValue.info[op] = std::move(info);
  }

  static void
  walkBlock(Block &block, Scope &stringValue, unsigned &cur,
            SmallVectorImpl<std::pair<Operation *, unsigned>> &arms) {
    for (Operation &op : block) {
      if (isa<scf::IfOp, affine::AffineIfOp>(op)) {
        for (auto [loopIndex, region] : llvm::enumerate(op.getRegions())) {
          arms.push_back({&op, static_cast<unsigned>(loopIndex)});
          for (Block &buildPoint : region)
            walkBlock(buildPoint, stringValue, cur, arms);
          arms.pop_back();
        }
        add(&op, stringValue, cur, arms);
        continue;
      }
      if (op.getNumRegions() > 0) {
        ++cur;
        continue;
      }
      add(&op, stringValue, cur, arms);
    }
  }
};

static std::pair<Value, int64_t> splitConstantOffset(Value valueHandle) {
  int64_t off = 0;
  for (unsigned guard = 0; guard < 64; ++guard) {
    if (std::optional<int64_t> candidateValue =
            getConstantIntValue(valueHandle))
      return {Value(), off + *candidateValue};
    if (auto add = valueHandle.getDefiningOp<arith::AddIOp>()) {
      if (std::optional<int64_t> candidateValue =
              getConstantIntValue(add.getRhs())) {
        off += *candidateValue;
        valueHandle = add.getLhs();
        continue;
      }
      if (std::optional<int64_t> candidateValue =
              getConstantIntValue(add.getLhs())) {
        off += *candidateValue;
        valueHandle = add.getRhs();
        continue;
      }
    }
    if (auto sub = valueHandle.getDefiningOp<arith::SubIOp>())
      if (std::optional<int64_t> candidateValue =
              getConstantIntValue(sub.getRhs())) {
        off -= *candidateValue;
        valueHandle = sub.getLhs();
        continue;
      }
    break;
  }
  return {valueHandle, off};
}

enum class AddrRelation { Same, Disjoint, Unknown };

static AddrRelation compareAddresses(Operation *arrayValue,
                                     Operation *buildPoint) {
  auto indices = [](Operation *op) -> std::optional<SmallVector<Value, 4>> {
    if (auto lowerIndex = dyn_cast<memref::LoadOp>(op))
      return SmallVector<Value, 4>(lowerIndex.getIndices());
    if (auto st = dyn_cast<memref::StoreOp>(op))
      return SmallVector<Value, 4>(st.getIndices());
    return std::nullopt;
  };
  auto ia = indices(arrayValue), ib = indices(buildPoint);
  if (!ia || !ib || ia->size() != ib->size())
    return AddrRelation::Unknown;
  bool same = true;
  for (auto [exprValue, rowValue] : llvm::zip(*ia, *ib)) {
    if (exprValue == rowValue)
      continue;
    auto [bx, ox] = splitConstantOffset(exprValue);
    auto [by, oy] = splitConstantOffset(rowValue);
    if (bx == by) {
      if (ox != oy)
        return AddrRelation::Disjoint;
      continue;
    }
    same = false;
  }
  return same ? AddrRelation::Same : AddrRelation::Unknown;
}

static const void *storageKey(Value valueHandle) {
  for (unsigned guard = 0; guard < 64; ++guard) {
    auto view = valueHandle.getDefiningOp<ViewLikeOpInterface>();
    if (!view)
      break;
    valueHandle = view.getViewSource();
  }
  if (auto globalOp = valueHandle.getDefiningOp<memref::GetGlobalOp>())
    return globalOp.getNameAttr().getAttr().getAsOpaquePointer();
  if (valueHandle.getDefiningOp<memref::AllocaOp>() ||
      valueHandle.getDefiningOp<memref::AllocOp>())
    return valueHandle.getAsOpaquePointer();
  if (auto arg = dyn_cast<BlockArgument>(valueHandle))
    if (arg.getOwner()->isEntryBlock() &&
        isa<FunctionOpInterface>(arg.getOwner()->getParentOp()))
      return valueHandle.getAsOpaquePointer();
  return nullptr;
}

struct MemTouch {
  const void *key = nullptr;
  Value memref;
  bool write = false;
};

static void memTouches(Operation *op, SmallVectorImpl<MemTouch> &out) {
  if (op->hasTrait<OpTrait::HasRecursiveMemoryEffects>())
    return;
  auto iface = dyn_cast<MemoryEffectOpInterface>(op);
  if (!iface || isa<CallOpInterface>(op)) {
    out.push_back({nullptr, Value(), true});
    return;
  }
  SmallVector<MemoryEffects::EffectInstance, 2> effects;
  iface.getEffects(effects);
  for (const MemoryEffects::EffectInstance &entryValue : effects) {
    if (isa<MemoryEffects::Allocate>(entryValue.getEffect()))
      continue;
    bool write = !isa<MemoryEffects::Read>(entryValue.getEffect());
    Value valueHandle = entryValue.getValue();
    if (!valueHandle || !isa<BaseMemRefType>(valueHandle.getType()))
      out.push_back({nullptr, Value(), write});
    else
      out.push_back({storageKey(valueHandle), valueHandle, write});
  }
}

static bool mayConflict(Operation *arrayValue, const MemTouch &ta,
                        Operation *buildPoint, const MemTouch &tb) {
  if (!ta.write && !tb.write)
    return false;
  if (ta.key && tb.key && ta.key != tb.key)
    return false;
  if (ta.memref && ta.memref == tb.memref &&
      compareAddresses(arrayValue, buildPoint) == AddrRelation::Disjoint)
    return false;
  return true;
}

static bool inExclusiveArms(const SeqScopeIndex::OpInfo &exprValue,
                            ArrayRef<int64_t> hoistedX,
                            const SeqScopeIndex::OpInfo &rowValue,
                            ArrayRef<int64_t> hoistedY) {
  for (const auto &ax : exprValue.arms)
    for (const auto &ay : rowValue.arms)
      if (ax.first == ay.first && ax.second != ay.second)
        return true;
  for (size_t arrayValue = 0; arrayValue + 1 < hoistedX.size(); arrayValue += 2)
    for (size_t buildPoint = 0; buildPoint + 1 < hoistedY.size();
         buildPoint += 2)
      if (hoistedX[arrayValue] == hoistedY[buildPoint] &&
          hoistedX[arrayValue + 1] != hoistedY[buildPoint + 1])
        return true;
  return false;
}

static ArrayRef<int64_t> hoistedArmsOf(Operation *op) {
  if (auto arrayValue = op->getAttrOfType<DenseI64ArrayAttr>(kIfArmsAttr))
    return arrayValue.asArrayRef();
  return {};
}

static std::optional<std::pair<const AccessSummary *, const AccessSummary *>>
findSameStatePair(ArrayRef<const AccessSummary *> accs,
                  const SeqScopeIndex::Scope &stringValue, unsigned stretch,
                  const DenseSet<Value> &bankValues) {
  unsigned keyValue = accs.size();
  const std::vector<Operation *> &ops = stringValue.stretches[stretch];
  SmallVector<unsigned> ord(keyValue);
  SmallVector<const SeqScopeIndex::OpInfo *> info(keyValue);
  DenseMap<Operation *, unsigned> accIdx;
  for (unsigned innerIndex = 0; innerIndex < keyValue; ++innerIndex) {
    info[innerIndex] = &stringValue.info.find(accs[innerIndex]->op)->second;
    ord[innerIndex] = info[innerIndex]->ordinal;
    accIdx[accs[innerIndex]->op] = innerIndex;
  }
  unsigned lo = ord.front(), hi = ord.back();

  std::vector<llvm::BitVector> deps(hi - lo + 1, llvm::BitVector(keyValue));
  llvm::BitVector barrier(keyValue);

  SmallVector<ArrayRef<int64_t>> hoistedArms(keyValue);
  for (unsigned innerIndex = 0; innerIndex < keyValue; ++innerIndex)
    hoistedArms[innerIndex] = hoistedArmsOf(accs[innerIndex]->op);
  auto exclusive = [&](unsigned loopIndex, unsigned innerIndex) {
    return inExclusiveArms(*info[loopIndex], hoistedArms[loopIndex],
                           *info[innerIndex], hoistedArms[innerIndex]);
  };

  struct MemEvent {
    Operation *op;
    unsigned pos;
    int acc;
    SmallVector<MemTouch, 2> touches;
  };
  std::vector<MemEvent> events;
  SmallVector<MemTouch, 2> touches;
  for (unsigned portValue = lo; portValue <= hi; ++portValue) {
    Operation *op = ops[portValue];
    llvm::BitVector &dimensionIndex = deps[portValue - lo];
    auto addValue = [&](Value valueHandle) {
      Operation *def = valueHandle.getDefiningOp();
      if (!def)
        return;
      auto it = stringValue.info.find(def);
      if (it == stringValue.info.end() || it->second.stretch != stretch ||
          it->second.ordinal < lo || it->second.ordinal >= portValue)
        return;
      dimensionIndex |= deps[it->second.ordinal - lo];
      auto ai = accIdx.find(def);
      if (ai != accIdx.end())
        dimensionIndex.set(ai->second);
    };
    for (Value valueHandle : op->getOperands())
      addValue(valueHandle);
    for (Region &region : op->getRegions())
      for (Block &block : region)
        if (!block.empty())
          for (Value valueHandle : block.back().getOperands())
            addValue(valueHandle);
    auto self = accIdx.find(op);
    int selfAcc = self == accIdx.end() ? -1 : static_cast<int>(self->second);

    touches.clear();
    memTouches(op, touches);
    if (!touches.empty() && !events.empty()) {
      const SeqScopeIndex::OpInfo &opInfo = stringValue.info.find(op)->second;
      ArrayRef<int64_t> opHoisted = hoistedArmsOf(op);
      for (const MemEvent &entryValue : events) {
        if (selfAcc >= 0 && entryValue.acc >= 0)
          continue;
        const llvm::BitVector &ed = deps[entryValue.pos - lo];
        if (!ed.test(dimensionIndex) &&
            !(entryValue.acc >= 0 && !dimensionIndex.test(entryValue.acc)))
          continue;
        if (inExclusiveArms(stringValue.info.find(entryValue.op)->second,
                            hoistedArmsOf(entryValue.op), opInfo, opHoisted))
          continue;
        bool conflict =
            llvm::any_of(entryValue.touches, [&](const MemTouch &arrayValue) {
              return llvm::any_of(touches, [&](const MemTouch &buildPoint) {
                return mayConflict(entryValue.op, arrayValue, op, buildPoint);
              });
            });
        if (!conflict)
          continue;
        dimensionIndex |= ed;
        if (entryValue.acc >= 0)
          dimensionIndex.set(entryValue.acc);
      }
    }
    if (!touches.empty() && (selfAcc >= 0 || dimensionIndex.any()))
      events.push_back({op, portValue, selfAcc, touches});
    if (selfAcc < 0) {

      if (llvm::any_of(op->getOperands(), [&](Value valueHandle) {
            return bankValues.contains(valueHandle);
          }))
        for (unsigned loopIndex = 0;
             loopIndex < keyValue && ord[loopIndex] < portValue; ++loopIndex)
          barrier.set(loopIndex);
      continue;
    }
    unsigned innerIndex = self->second;
    dimensionIndex |= barrier;
    for (unsigned loopIndex = 0; loopIndex < innerIndex; ++loopIndex) {
      if (exclusive(loopIndex, innerIndex) ||
          !(accs[loopIndex]->isWrite || accs[innerIndex]->isWrite))
        continue;
      if (compareAddresses(accs[loopIndex]->op, op) != AddrRelation::Disjoint) {
        dimensionIndex.set(loopIndex);
        dimensionIndex |= deps[ord[loopIndex] - lo];
      }
    }
    for (unsigned loopIndex = 0; loopIndex < innerIndex; ++loopIndex) {
      if (dimensionIndex.test(loopIndex) || exclusive(loopIndex, innerIndex))
        continue;
      if (!accs[loopIndex]->isWrite && !accs[innerIndex]->isWrite &&
          compareAddresses(accs[loopIndex]->op, op) == AddrRelation::Same)
        continue;
      return std::make_pair(accs[loopIndex], accs[innerIndex]);
    }
  }
  return std::nullopt;
}

static std::string accessText(const AccessSummary *arrayValue) {
  std::string stringValue;
  llvm::raw_string_ostream os(stringValue);
  os << arrayValue->op->getName() << " @ ";
  arrayValue->op->getLoc().print(os);
  return stringValue;
}

static PortDemand sequentialScopeDemand(ArrayRef<const AccessSummary *> group,
                                        SeqScopeIndex &index,
                                        std::string *note) {
  PortDemand dimensionIndex;
  bool anyR = false, anyW = false;
  for (const auto *arrayValue : group)
    (arrayValue->isWrite ? anyW : anyR) = true;
  dimensionIndex.reads = anyR ? 1u : 0u;
  dimensionIndex.writes = anyW ? 1u : 0u;
  dimensionIndex.total = (anyR || anyW) ? 1u : 0u;
  Operation *scope = group.front()->scope;
  if (!scope || group.size() < 2)
    return dimensionIndex;
  const SeqScopeIndex::Scope &stringValue = index.get(scope);
  std::map<unsigned, SmallVector<const AccessSummary *>> byStretch;
  for (const auto *arrayValue : group) {
    auto it = stringValue.info.find(arrayValue->op);
    if (it != stringValue.info.end())
      byStretch[it->second.stretch].push_back(arrayValue);
  }
  DenseSet<Value> bankValues;
  for (const auto *arrayValue : group)
    for (Value valueHandle : arrayValue->op->getOperands())
      if (isa<BaseMemRefType>(valueHandle.getType()))
        bankValues.insert(valueHandle);
  for (auto &[stretch, accs] : byStretch) {
    if (accs.size() < 2)
      continue;
    llvm::sort(accs, [&](const AccessSummary *exprValue,
                         const AccessSummary *rowValue) {
      return stringValue.info.find(exprValue->op)->second.ordinal <
             stringValue.info.find(rowValue->op)->second.ordinal;
    });
    auto pair = findSameStatePair(accs, stringValue, stretch, bankValues);
    if (!pair)
      continue;
    bool w1 = pair->first->isWrite, w2 = pair->second->isWrite;
    dimensionIndex.total = 2;
    if (!w1 && !w2)
      dimensionIndex.reads = 2;
    else if (w1 && w2)
      dimensionIndex.writes = 2;
    if (note)
      *note = "same state (independent, one straight-line stretch): " +
              accessText(pair->first) + " + " + accessText(pair->second);
    return dimensionIndex;
  }
  return dimensionIndex;
}

PortDemand scopeDemand(ArrayRef<const AccessSummary *> group,
                       SeqScopeIndex *seq = nullptr,
                       std::string *note = nullptr) {
  PortDemand dimensionIndex;
  if (group.empty())
    return dimensionIndex;

  unsigned ii = group.front()->ii;
  assert(llvm::all_of(group,
                      [&](auto *arrayValue) { return arrayValue->ii == ii; }) &&
         "scopeDemand requires a single-II group; bucket by scope first");

  if (ii == 0 && seq)
    return sequentialScopeDemand(group, *seq, note);
  if (ii == 0) {
    bool anyR = false, anyW = false;
    for (const auto *arrayValue : group)
      (arrayValue->isWrite ? anyW : anyR) = true;
    dimensionIndex.reads = anyR ? 1u : 0u;
    dimensionIndex.writes = anyW ? 1u : 0u;
    dimensionIndex.total = (anyR || anyW) ? 1u : 0u;
    return dimensionIndex;
  }

  std::vector<std::pair<unsigned, unsigned>> slot(ii, {0u, 0u});
  for (const auto *arrayValue : group) {
    unsigned occ = std::max(arrayValue->latency, 1u);
    for (unsigned candidateValue = 0; candidateValue < occ; ++candidateValue) {
      unsigned phase = (arrayValue->stageStart + candidateValue) % ii;
      (arrayValue->isWrite ? slot[phase].second : slot[phase].first)++;
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

static PortDemand computePortDemand(ArrayRef<AccessSummary> accesses,
                                    SeqScopeIndex *seq) {
  std::map<Operation *, SmallVector<const AccessSummary *>> byScope;
  for (const auto &arrayValue : accesses)
    byScope[arrayValue.scope].push_back(&arrayValue);

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

const char *kindName(StorageKind keyValue) {
  switch (keyValue) {
  case StorageKind::RAM_1P:
    return "RAM_1P";
  case StorageKind::RAM_2P:
    return "RAM_2P";
  case StorageKind::RAM_S2P:
    return "RAM_S2P";
  case StorageKind::RAM_T2P:
    return "RAM_T2P";
  case StorageKind::RAM_1WNR:
    return "RAM_1WNR";
  case StorageKind::LUTRAM:
    return "LUTRAM";
  case StorageKind::URAM:
    return "URAM";
  case StorageKind::ROM_1P:
    return "ROM_1P";
  case StorageKind::ROM_2P:
    return "ROM_2P";
  case StorageKind::ROM_NP:
    return "ROM_NP";
  }
  return "?";
}

struct KindResult {
  StorageKind kind = StorageKind::RAM_1P;
  bool infeasible = false;
  std::string note;
};

static KindResult selectStorageKind(const PortDemand &dimensionIndex) {
  KindResult resultValue;
  unsigned total = dimensionIndex.total, widthValue = dimensionIndex.writes,
           rd = dimensionIndex.reads;

  if (total <= 1) {
    resultValue.kind = StorageKind::RAM_1P;
    return resultValue;
  }
  if (total == 2) {
    resultValue.kind =
        widthValue >= 2 ? StorageKind::RAM_T2P : StorageKind::RAM_2P;
    return resultValue;
  }

  resultValue.kind = StorageKind::RAM_T2P;
  resultValue.infeasible = true;
  resultValue.note = "port demand " + std::to_string(total) + "/cycle (" +
                     std::to_string(rd) + "R+" + std::to_string(widthValue) +
                     "W, multi-writer) exceeds 2 ports; needs array_partition.";
  return resultValue;
}

bool isWideKind(StorageKind keyValue) {
  switch (keyValue) {
  case StorageKind::RAM_1P:
  case StorageKind::RAM_S2P:
  case StorageKind::ROM_1P:
  case StorageKind::ROM_2P:
    return true;
  case StorageKind::RAM_2P:
  case StorageKind::RAM_T2P:
  case StorageKind::RAM_1WNR:
  case StorageKind::ROM_NP:
  case StorageKind::LUTRAM:
  case StorageKind::URAM:
    return false;
  }
  return false;
}

unsigned blockDataWidth(StorageKind keyValue) {
  if (keyValue == StorageKind::LUTRAM || keyValue == StorageKind::URAM)
    return 0;
  return isWideKind(keyValue) ? kMaxPortWidthWide : kMaxPortWidthNarrow;
}

int64_t ceilDiv(int64_t arrayValue, int64_t buildPoint) {
  return (arrayValue + buildPoint - 1) / buildPoint;
}

unsigned usedPortWidth(const BankMathRecord &bm, StorageKind keyValue) {
  return bm.configWidth ? bm.configWidth : blockDataWidth(keyValue);
}

int64_t estimateBlocksN6(int64_t numElems, unsigned elemBits, bool wide,
                         BankMathRecord *bm = nullptr) {
  if (bm) {
    bm->present = true;
    bm->wide = wide;
    bm->maxWidth = wide ? kMaxPortWidthWide : kMaxPortWidthNarrow;
    bm->formula = formulaName(BramFormula::N6);
    bm->band = "min over the aspect-ratio modes (N6)";
  }
  if (numElems <= 0 || elemBits == 0)
    return 0;

  int64_t addrDepth =
      static_cast<int64_t>(llvm::PowerOf2Ceil(static_cast<uint64_t>(numElems)));
  int64_t best = -1;
  AspectMode bestMode{0, 0};
  int64_t bestCols = 0, bestPerCol = 0;

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

int64_t estimateBlocksBand(int64_t numElems, unsigned elemBits, bool sdp,
                           BankMathRecord *bm = nullptr) {
  if (bm) {
    bm->present = true;
    bm->wide = sdp;
    bm->maxWidth = sdp ? kMaxPortWidthWide : kMaxPortWidthNarrow;
    bm->formula = formulaName(BramFormula::Band);
  }
  if (numElems <= 0 || elemBits == 0)
    return 0;
  int64_t addrDepth =
      static_cast<int64_t>(llvm::PowerOf2Ceil(static_cast<uint64_t>(numElems)));
  int64_t widthValue = elemBits;
  unsigned mode;
  int64_t depthPerBlock;
  int64_t cols, perCol;
  const char *band;
  if (addrDepth <= 512) {
    mode = sdp ? 36 : 18;
    depthPerBlock = sdp ? 512 : 1024;
    cols = ceilDiv(widthValue, mode);
    perCol = 1;
    band = sdp ? "depth <= 512, SDP: ceil(W/36)"
               : "depth <= 512, not SDP: ceil(W/18)";
  } else if (addrDepth <= 1024) {
    mode = 18, depthPerBlock = 1024, cols = ceilDiv(widthValue, 18), perCol = 1;
    band = "depth 513-1024: ceil(W/18)";
  } else if (addrDepth <= 2048) {
    mode = 9, depthPerBlock = 2048, cols = ceilDiv(widthValue, 9), perCol = 1;
    band = "depth 1025-2048: ceil(W/9)";
  } else if (addrDepth <= 4096) {
    band = "depth 2049-4096: min(ceil(W/4), 2*ceil(W/9))";
    if (ceilDiv(widthValue, 4) <= 2 * ceilDiv(widthValue, 9))
      mode = 4, depthPerBlock = 4096, cols = ceilDiv(widthValue, 4), perCol = 1;
    else
      mode = 9, depthPerBlock = 2048, cols = ceilDiv(widthValue, 9), perCol = 2;
  } else if (addrDepth <= 8192) {
    mode = 2, depthPerBlock = 8192, cols = ceilDiv(widthValue, 2), perCol = 1;
    band = "depth 4097-8192: ceil(W/2)";
  } else {
    mode = 1, depthPerBlock = 16384, cols = widthValue,
    perCol = addrDepth / 16384;
    band = "depth > 8192: 2^ceil(log2 ceil(D/16384)) * W";
  }
  int64_t blocks = cols * perCol;
  if (bm) {
    bm->band = band;
    bm->configWidth = mode;
    bm->widthTiles = cols;
    bm->depthPerBlock = depthPerBlock;
    bm->addrDepth = addrDepth;
    bm->depthTiles = perCol;
    bm->blocksPerCopy = blocks;
    bm->replication = 1;
    bm->blocks = blocks;
  }
  return blocks;
}

int64_t estimateBlocks(int64_t numElems, unsigned elemBits, bool sdp,
                       BramFormula formula, BankMathRecord *bm = nullptr) {
  return formula == BramFormula::Band
             ? estimateBlocksBand(numElems, elemBits, sdp, bm)
             : estimateBlocksN6(numElems, elemBits, sdp, bm);
}

unsigned portOccupancy(bool) { return 1u; }

bool classifyAccess(Operation *op, Value mem, bool &isWrite) {
  auto eff = dyn_cast<MemoryEffectOpInterface>(op);
  if (!eff)
    return false;
  SmallVector<MemoryEffects::EffectInstance> effects;
  eff.getEffects(effects);
  bool reads = false, writes = false;
  for (auto &entryValue : effects) {
    if (entryValue.getValue() && entryValue.getValue() != mem)
      continue;
    if (isa<MemoryEffects::Read>(entryValue.getEffect()))
      reads = true;
    else if (isa<MemoryEffects::Write>(entryValue.getEffect()))
      writes = true;
  }
  if (!reads && !writes)
    return false;
  isWrite = writes;
  return true;
}

Operation *sequentialScope(Operation *op) {
  for (Operation *cur = op->getParentOp(); cur; cur = cur->getParentOp())
    if (isa<LoopLikeOpInterface>(cur))
      return cur;
  if (auto fn = op->getParentOfType<func::FuncOp>())
    return fn.getOperation();
  return nullptr;
}

static void collectAccessesFrom(
    Value mem, Operation *via, bool portBound, const InstanceModel *model,
    DenseSet<std::pair<Operation *, unsigned>> &visitedArgs,
    DenseSet<Operation *> &seen, SmallVectorImpl<AccessSummary> &out) {
  for (OpOperand &use : mem.getUses()) {
    Operation *user = use.getOwner();
    if (auto callSite = dyn_cast<CallOpInterface>(user)) {
      func::FuncOp callee = resolveDefinedCallee(callSite);
      if (!callee)
        continue;
      std::optional<unsigned> indexValue = callArgIndex(callSite, use);
      if (!indexValue || *indexValue >= callee.getNumArguments())
        continue;
      if (!visitedArgs.insert({callee.getOperation(), *indexValue}).second)
        continue;
      bool shared = portBound || (model && model->instanceSites(callee) > 1);
      collectAccessesFrom(callee.getArgument(*indexValue), via ? via : user,
                          shared, model, visitedArgs, seen, out);
      continue;
    }
    if (auto view = dyn_cast<ViewLikeOpInterface>(user))
      if (view.getViewSource() == mem) {
        for (Value resultValue : user->getResults())
          if (isa<BaseMemRefType>(resultValue.getType()))
            collectAccessesFrom(resultValue, via, portBound, model, visitedArgs,
                                seen, out);
        continue;
      }
    bool isWrite = false;
    if (!classifyAccess(user, mem, isWrite))
      continue;
    if (!seen.insert(user).second)
      continue;

    AccessSummary arrayValue;
    arrayValue.op = user;
    arrayValue.isWrite = isWrite;
    arrayValue.latency = portOccupancy(isWrite);
    arrayValue.via = via;
    arrayValue.portBound = portBound;

    if (auto pipeline = user->getParentOfType<LoopSchedulePipelineOp>()) {
      auto stage = user->getParentOfType<LoopSchedulePipelineStageOp>();
      arrayValue.scope = pipeline.getOperation();
      arrayValue.ii = static_cast<unsigned>(pipeline.getII());
      arrayValue.stageStart =
          stage ? static_cast<unsigned>(stage.getStart()) : 0u;
    } else {

      arrayValue.scope = sequentialScope(user);
      arrayValue.ii = 0;
      arrayValue.stageStart = 0;
    }
    out.push_back(arrayValue);
  }
}

SmallVector<AccessSummary>
collectAccessSummaries(ArrayRef<Value> banks,
                       const InstanceModel *model = nullptr) {
  SmallVector<AccessSummary> out;
  DenseSet<std::pair<Operation *, unsigned>> visitedArgs;
  DenseSet<Operation *> seen;
  for (Value mem : banks)
    collectAccessesFrom(mem, nullptr, false, model, visitedArgs, seen, out);
  return out;
}

static bool neverWritten(ArrayRef<Value> sites) {
  SmallVector<Value> work(sites.begin(), sites.end());
  DenseSet<Value> seen(sites.begin(), sites.end());
  while (!work.empty()) {
    Value cur = work.pop_back_val();
    for (OpOperand &use : cur.getUses()) {
      Operation *user = use.getOwner();
      if (auto view = dyn_cast<ViewLikeOpInterface>(user))
        if (view.getViewSource() == cur) {
          for (Value resultValue : user->getResults())
            if (isa<BaseMemRefType>(resultValue.getType()) &&
                seen.insert(resultValue).second)
              work.push_back(resultValue);
          continue;
        }
      if (isa<memref::DimOp>(user))
        continue;
      auto eff = dyn_cast<MemoryEffectOpInterface>(user);
      if (!eff)
        return false;
      SmallVector<MemoryEffects::EffectInstance> effects;
      eff.getEffects(effects);
      bool named = false;
      for (auto &entryValue : effects) {
        if (entryValue.getValue() != cur)
          continue;
        named = true;
        if (isa<MemoryEffects::Write, MemoryEffects::Free>(
                entryValue.getEffect()))
          return false;
      }
      if (!named)
        return false;
    }
  }
  return true;
}

static FileLineColLoc findFileLoc(Location loc) {
  if (auto fieldValue = dyn_cast<FileLineColLoc>(loc))
    return fieldValue;
  if (auto elementCount = dyn_cast<NameLoc>(loc))
    return findFileLoc(elementCount.getChildLoc());
  if (auto candidateValue = dyn_cast<CallSiteLoc>(loc))
    return findFileLoc(candidateValue.getCallee());
  if (auto fu = dyn_cast<FusedLoc>(loc))
    for (Location lowerIndex : fu.getLocations())
      if (auto fieldValue = findFileLoc(lowerIndex))
        return fieldValue;
  if (auto opHandle = dyn_cast<OpaqueLoc>(loc))
    return findFileLoc(opHandle.getFallbackLocation());
  return {};
}

static std::string locString(Location loc) {
  if (auto fieldValue = findFileLoc(loc))
    return (fieldValue.getFilename().str() + ":" +
            std::to_string(fieldValue.getLine()) + ":" +
            std::to_string(fieldValue.getColumn()));
  if (isa<UnknownLoc>(loc))
    return "<unknown>";
  std::string stringValue;
  llvm::raw_string_ostream os(stringValue);
  loc.print(os);
  return stringValue;
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
  StringRef elementCount = op->getName().getStringRef();
  return elementCount == "hls.store_enable" ||
         elementCount == "hls.affine.store_enable";
}

static unsigned counterAttr(Operation *op, StringRef name) {
  if (auto arrayValue = op->getAttrOfType<IntegerAttr>(name))
    return arrayValue.getInt() > 0 ? static_cast<unsigned>(arrayValue.getInt())
                                   : 0u;
  return 0;
}

static void describeMemref(Operation *op, unsigned index,
                           MemrefRecord &resultValue) {
  StringRef opName = op->getName().getStringRef();
  if (auto globalOp = dyn_cast<memref::GlobalOp>(op)) {
    resultValue.kind = "global";
    resultValue.name = globalOp.getSymName().str();
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
  if (auto globalOp = op->getAttrOfType<StringAttr>("hls.from_global"))
    resultValue.fromGlobal = globalOp.getValue().str();
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
      for (Attribute arrayValue : all)
        if (auto dd = dyn_cast<DictionaryAttr>(arrayValue)) {
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
}

static void recordAccesses(ArrayRef<AccessSummary> accesses,
                           MemrefRecord &resultValue, SeqScopeIndex *seq) {
  resultValue.accesses.clear();
  resultValue.perScope.clear();
  SmallVector<Operation *> scopeOrder;
  for (const AccessSummary &arrayValue : accesses) {
    AccessRecord ar;
    ar.op = arrayValue.op->getName().getStringRef().str();
    ar.isWrite = arrayValue.isWrite;
    ar.scope = arrayValue.scope;
    ar.scopeKind = scopeKindName(arrayValue.scope);
    ar.scopeLoc =
        arrayValue.scope ? locString(arrayValue.scope->getLoc()) : "<none>";
    ar.ii = arrayValue.ii;
    ar.stageStart = arrayValue.stageStart;
    ar.storeEnable = isStoreEnableOp(arrayValue.op);
    ar.mergedLoads = counterAttr(arrayValue.op, "hls.merged_loads");
    ar.forwardedLoads = counterAttr(arrayValue.op, "hls.forwarded_loads");
    ar.removedStores = counterAttr(arrayValue.op, "hls.removed_stores");
    if (auto fn = arrayValue.op->getParentOfType<func::FuncOp>())
      ar.inFunc = fn.getName().str();
    if (arrayValue.via) {
      std::string valueHandle = "call";
      if (auto callSite = dyn_cast<CallOpInterface>(arrayValue.via))
        if (auto callee = resolveDefinedCallee(callSite))
          valueHandle += " @" + callee.getName().str();
      ar.viaCall = valueHandle + " @ " + locString(arrayValue.via->getLoc());
    }
    ar.portBound = arrayValue.portBound;
    resultValue.accesses.push_back(std::move(ar));
    if (!llvm::is_contained(scopeOrder, arrayValue.scope))
      scopeOrder.push_back(arrayValue.scope);
  }
  for (Operation *scope : scopeOrder) {
    SmallVector<const AccessSummary *> group;
    for (const AccessSummary &arrayValue : accesses)
      if (arrayValue.scope == scope)
        group.push_back(&arrayValue);
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

static ReplicationRecord analyzeReplication(ArrayRef<AccessSummary> accesses,
                                            bool attributed) {
  ReplicationRecord resultValue;
  resultValue.present = attributed;
  if (!attributed)
    return resultValue;

  struct ScopeStats {
    Operation *scope = nullptr;
    unsigned reads = 0, writes = 0, ii = 0;
    bool portBound = false;
  };
  SmallVector<ScopeStats> scopes;
  for (const AccessSummary &arrayValue : accesses) {
    ScopeStats *st = nullptr;
    for (ScopeStats &stringValue : scopes)
      if (stringValue.scope == arrayValue.scope)
        st = &stringValue;
    if (!st) {
      scopes.push_back({arrayValue.scope, 0, 0, arrayValue.ii, false});
      st = &scopes.back();
    }
    (arrayValue.isWrite ? st->writes : st->reads)++;
    st->portBound |= arrayValue.portBound;
  }

  resultValue.maxStoresPerLoop = 0;
  for (const ScopeStats &stringValue : scopes) {
    bool isLoopBody =
        stringValue.scope && (isa<LoopSchedulePipelineOp>(stringValue.scope) ||
                              isa<LoopLikeOpInterface>(stringValue.scope));
    if (isLoopBody)
      resultValue.maxStoresPerLoop =
          std::max(resultValue.maxStoresPerLoop, stringValue.writes);
  }
  resultValue.replicable = resultValue.maxStoresPerLoop <= 1;
  resultValue.copies = 1;
  for (const ScopeStats &stringValue : scopes) {
    if (!stringValue.scope || !isa<LoopSchedulePipelineOp>(stringValue.scope) ||
        stringValue.ii == 0)
      continue;
    ReplicationLoopRecord lr;
    lr.scopeLoc = locString(stringValue.scope->getLoc());
    lr.ii = stringValue.ii;
    lr.reads = stringValue.reads;
    lr.writes = stringValue.writes;
    lr.need = static_cast<unsigned>(
        ceilDiv(stringValue.reads + stringValue.writes, stringValue.ii));
    unsigned candidateValue = lr.need > 1 ? lr.need - 1 : 1;
    lr.copies = std::min(candidateValue, kMaxReplicationCopies);

    if (stringValue.portBound) {
      lr.portBound = true;
      lr.copies = 1;
      resultValue.portBoundLimited |= lr.need > 2;
    }
    if (resultValue.replicable && lr.copies > resultValue.copies) {
      resultValue.copies = lr.copies;
      resultValue.limitingLoop = lr.scopeLoc;
    }
    resultValue.loops.push_back(std::move(lr));
  }
  if (!resultValue.replicable)
    resultValue.copies = 1;
  return resultValue;
}

static std::string ramReasonFor(const PortDemand &dimensionIndex,
                                const KindResult &kr,
                                const ReplicationRecord &rep, bool attributed,
                                bool anyStoreEnable, bool demandClamped) {
  std::string stringValue;
  llvm::raw_string_ostream os(stringValue);
  if (!attributed) {
    os << "global: accesses not attributed, default " << kindName(kr.kind);
    return stringValue;
  }
  if (kr.kind == StorageKind::RAM_1WNR) {
    os << "replicable (no loop body stores to it more than once)";
    if (rep.limitingLoop) {
      for (const ReplicationLoopRecord &lowerIndex : rep.loops)
        if (lowerIndex.scopeLoc == *rep.limitingLoop) {
          os << "; pipeline @ " << lowerIndex.scopeLoc << ": "
             << lowerIndex.reads << "R+" << lowerIndex.writes
             << "W per iteration at II " << lowerIndex.ii << " needs ceil("
             << (lowerIndex.reads + lowerIndex.writes) << "/" << lowerIndex.ii
             << ")=" << lowerIndex.need << " port-cycles";
          break;
        }
    }
    os << " -> RAM_1WNR with " << rep.copies
       << " copies (port B of every copy reads, port A of all copies is the "
          "shared write port and reads when idle";
    if (rep.copies >= kMaxReplicationCopies)
      os << "; capped at " << kMaxReplicationCopies;
    os << "); each copy is a true-dual-port RAM (x18/port)";
    return stringValue;
  }
  os << "peak port demand " << dimensionIndex.total << "/cycle ("
     << dimensionIndex.reads << "R+" << dimensionIndex.writes
     << "W, max over scopes)";
  if (kr.infeasible) {
    os << ": " << kr.note;
    return stringValue;
  }
  if (demandClamped && rep.portBoundLimited)
    os << ", clamped to 2 ports (a callee instantiated at more than one "
          "place reads it through the module's ports: no replication across "
          "the call, Vitis raises that loop's II instead; N14 R6)";
  else if (demandClamped)
    os << ", clamped to 2 ports (replicable bank, but no pipelined loop needs "
          "more than ceil((R+W)/II) <= 2 port-cycles, so Vitis spreads the "
          "accesses over the II)";
  if (dimensionIndex.total <= 1 && !demandClamped)
    os << ": at most one live port -> " << kindName(kr.kind) << " (x"
       << blockDataWidth(kr.kind) << " wide, no TDP constraint)";
  else
    os << ": two ports live in the same cycle -> " << kindName(kr.kind) << " (x"
       << blockDataWidth(kr.kind) << "/port, true dual port)";
  if (!rep.replicable)
    os << "; not replicable: a loop body stores to it " << rep.maxStoresPerLoop
       << " times (Vitis keeps one 2-port RAM and raises that loop's II)";
  else if (!rep.loops.empty())
    os << "; replicable, but every pipelined loop needs <= 2 port-cycles per "
          "II (no RAM_1WNR)";
  if (dimensionIndex.segregated)
    os << "; reads and writes live in different scopes (RAM_S2P-eligible) but "
          "count-only selection never picks RAM_S2P";
  if (anyStoreEnable)
    os << "; hls.store_enable counts as a write only (no phantom read port)";
  return stringValue;
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
  unsigned arrayValue = 0;
  for (const APInt &valueHandle : vals)
    arrayValue = std::max(arrayValue, valueHandle.getActiveBits());
  if (arrayValue == 0)
    return 0;
  for (const APInt &valueHandle : vals)
    width = std::max(width, valueHandle.trunc(arrayValue).getSignificantBits());
  return width;
}

static BRAMCost estimateBRAM(MemoryResourceOpInterface iface, MemrefRecord &rec,
                             ArrayRef<Value> banks, bool attributed,
                             SeqScopeIndex *seq, BramFormula formula,
                             const InstanceModel *instances,
                             ArrayRef<Value> allSites) {
  BRAMCost cost;
  cost.kind = StorageKind::RAM_1P;
  cost.bramCount = 0;

  {
    rec.shape = iface.getStaticShape();
    Type elt = iface.getElementType();
    llvm::raw_string_ostream os(rec.elemType);
    elt.print(os);
    rec.elemBits = elt.isIntOrFloat()    ? elt.getIntOrFloatBitWidth()
                   : isa<IndexType>(elt) ? 64u
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
      rec.ramType = kindName(cost.kind);
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

  if (!iface.contributesToBRAMCost()) {
    cost.note = "excluded from BRAM accounting (LUTRAM / stream / zero-size)";

    int64_t bits = iface.getStaticSizeInBits();
    auto pragmaKind = iface.getPragmaStorageKind();
    if (pragmaKind && *pragmaKind == StorageKind::LUTRAM) {
      rec.status = "excluded_small";
      rec.excludeReason = "pragma storage kind LUTRAM; not BRAM-backed";
    } else if (bits == 0 && !rec.words) {

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

    SmallVector<AccessSummary> accesses =
        collectAccessSummaries(banks, instances);
    recordAccesses(accesses, rec, seq);
    rec.demand = computePortDemand(accesses, seq);
    rec.replication = analyzeReplication(accesses, rec.accessesAttributed);
    rec.ramType = kindName(cost.kind);
    rec.ramReason = "not selected: " + cost.note;
    rec.bram = cost.bramCount;
    return cost;
  }

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
  unsigned elemBits = rec.elemBits;
  if (numElems == 0 || elemBits == 0) {
    cost.note = "zero-size";
    rec.status = "zero_size";
    rec.excludeReason = cost.note;
    rec.ramType = kindName(cost.kind);
    rec.ramReason = "not selected: " + cost.note;
    rec.bram = cost.bramCount;
    return cost;
  }

  SmallVector<AccessSummary> accesses =
      collectAccessSummaries(banks, instances);
  PortDemand demand = computePortDemand(accesses, seq);
  ReplicationRecord rep = analyzeReplication(accesses, rec.accessesAttributed);
  KindResult kr;
  bool demandClamped = false;
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
      bool anyRead =
          llvm::any_of(romAccesses, [](const AccessSummary &arrayValue) {
            return !arrayValue.isWrite;
          });
      bool anyWrite =
          llvm::any_of(romAccesses, [](const AccessSummary &arrayValue) {
            return arrayValue.isWrite;
          });
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
  if (rec.rom) {

    if (fillRom || !attributed) {
      SmallVector<AccessSummary> reads;
      for (const AccessSummary &arrayValue : romAccesses)
        if (!arrayValue.isWrite)
          reads.push_back(arrayValue);
      accesses = std::move(reads);
      rec.accessesAttributed = true;
      demand = computePortDemand(accesses, seq);
      rep = analyzeReplication(accesses, true);
    }
    unsigned declaredBits = elemBits;
    std::string widthNote;
    if (romBits) {
      unsigned widthValue = *romBits;
      widthNote = "; element width " + std::to_string(widthValue) + " of " +
                  std::to_string(declaredBits) + " bits from its values (N26)";
      if (widthValue == 0) {
        cost.kind = StorageKind::ROM_1P;
        cost.bramCount = 0;
        cost.note = std::to_string(numElems) + "x" +
                    std::to_string(declaredBits) +
                    "b ROM whose values are all 0: no memory (N1a, N26)";
        recordAccesses(accesses, rec, seq);
        rec.demand = demand;
        rec.status = "zero_rom";
        rec.excludeReason = cost.note;
        rec.ramType = "none";
        rec.ramReason = "not selected: " + cost.note;
        rec.bram = 0;
        return cost;
      }
      elemBits = widthValue;
      if (numElems * static_cast<int64_t>(widthValue) < kBRAMPromotionBits) {
        cost.kind = StorageKind::ROM_1P;
        cost.bramCount = 0;
        cost.note = std::to_string(numElems) + "x" +
                    std::to_string(widthValue) + "b ROM (narrowed from " +
                    std::to_string(declaredBits) + " bits, N26) < " +
                    std::to_string(kBRAMPromotionBits) +
                    " bits: distributed ROM, 0 BRAM";
        recordAccesses(accesses, rec, seq);
        rec.demand = demand;
        rec.status = "excluded_small";
        rec.excludeReason = cost.note;
        rec.ramType = kindName(cost.kind);
        rec.ramReason = "not selected: " + cost.note;
        rec.bram = 0;
        return cost;
      }
    }
    unsigned elementCount = std::max(demand.total, 1u);
    for (ReplicationLoopRecord &lowerIndex : rep.loops) {
      elementCount = std::max(elementCount, lowerIndex.need);

      lowerIndex.copies =
          lowerIndex.need <= 2
              ? 1u
              : std::min<unsigned>(
                    static_cast<unsigned>(ceilDiv(lowerIndex.need, 2)),
                    kMaxReplicationCopies);
    }
    rep.replicable = true;
    rep.copies = 1;
    rep.limitingLoop.reset();
    if (elementCount <= 2) {
      kr.kind = elementCount <= 1 ? StorageKind::ROM_1P : StorageKind::ROM_2P;
      blocks = estimateBlocks(numElems, elemBits, true, formula, &rec.bankMath);
    } else {
      kr.kind = StorageKind::ROM_NP;
      rep.copies =
          std::min<unsigned>(static_cast<unsigned>(ceilDiv(elementCount, 2)),
                             kMaxReplicationCopies);
      int64_t perCopy =
          estimateBlocks(numElems, elemBits, false, formula, &rec.bankMath);
      blocks = perCopy * rep.copies;
      rec.bankMath.replication = rep.copies;
      rec.bankMath.blocks = blocks;
    }
    cost.kind = kr.kind;
    cost.bramCount = static_cast<unsigned>(blocks);
    const char *what = fillRom ? "b array written only with constants -> "
                       : global.getConstant()
                           ? "b constant global -> "
                           : "b initialised global, never written -> ";
    cost.note = std::to_string(numElems) + "x" + std::to_string(elemBits) +
                what + kindName(kr.kind) + " (" + std::to_string(elementCount) +
                " read port(s)/cycle) = " + std::to_string(blocks) +
                " BRAM_18K";
    recordAccesses(accesses, rec, seq);
    rec.demand = demand;
    rec.replication = rep;
    rec.status = "counted";
    rec.ramType = kindName(kr.kind);
    rec.ramReason =
        std::string(fillRom ? "every write stores a constant (ROM of those "
                              "values, N26)"
                    : global.getConstant()
                        ? "constant-initialised global (ROM, never written)"
                        : "initialised global that no get_global site writes "
                          "(ROM)") +
        widthNote + ": peak " + std::to_string(elementCount) +
        " read(s) per cycle -> " + kindName(kr.kind) +
        (elementCount <= 2
             ? std::string(": read-only ports are simple dual port, x36 "
                           "allowed (N8)")
             : ", " + std::to_string(rep.copies) +
                   " copies = ceil(n/2) at x18 (N8 (c) ROM_nP: "
                   "fr_rom3r / fr_rom4r, aes sbox, gsm bitoff)");
    rec.bram = cost.bramCount;
    return cost;
  }
  if (rep.copies > 1) {

    kr.kind = StorageKind::RAM_1WNR;
    int64_t perCopy =
        estimateBlocks(numElems, elemBits, false, formula, &rec.bankMath);
    blocks = perCopy * rep.copies;
    rec.bankMath.replication = rep.copies;
    rec.bankMath.blocks = blocks;
  } else {
    PortDemand dimensionIndex = demand;
    if (rep.replicable && dimensionIndex.total > 2) {

      demandClamped = true;
      dimensionIndex.total = 2;
      dimensionIndex.reads = std::min(dimensionIndex.reads, 2u);
      dimensionIndex.writes = std::min(dimensionIndex.writes, 2u);
      if (dimensionIndex.reads >= 1 && dimensionIndex.writes >= 1)
        dimensionIndex.reads = dimensionIndex.writes = 1;
    }
    kr = selectStorageKind(dimensionIndex);
    blocks = estimateBlocks(numElems, elemBits, isWideKind(kr.kind), formula,
                            &rec.bankMath);
  }
  cost.kind = kr.kind;
  cost.infeasible = kr.infeasible;
  cost.bramCount = static_cast<unsigned>(blocks);
  if (!kr.note.empty())
    cost.note = kr.note + " => " + std::to_string(blocks) + " BRAM";
  else if (kr.kind == StorageKind::RAM_1WNR)
    cost.note = std::to_string(numElems) + "x" + std::to_string(elemBits) +
                "b -> RAM_1WNR, " + std::to_string(rep.copies) + " copies x " +
                std::to_string(rec.bankMath.blocksPerCopy) + " (x" +
                std::to_string(usedPortWidth(rec.bankMath, kr.kind)) +
                "/port) = " + std::to_string(blocks) + " BRAM_18K";
  else
    cost.note = std::to_string(numElems) + "x" + std::to_string(elemBits) +
                "b -> " + kindName(kr.kind) + " (x" +
                std::to_string(usedPortWidth(rec.bankMath, kr.kind)) +
                "/port) = " + std::to_string(blocks) + " BRAM_18K";

  recordAccesses(accesses, rec, seq);
  rec.demand = demand;
  rec.replication = rep;
  rec.status = kr.infeasible ? "infeasible" : "counted";
  rec.ramType = kindName(kr.kind);
  bool anyStoreEnable =
      llvm::any_of(rec.accesses, [](const AccessRecord &arrayValue) {
        return arrayValue.storeEnable;
      });
  rec.ramReason = ramReasonFor(demand, kr, rep, rec.accessesAttributed,
                               anyStoreEnable, demandClamped);
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
  llvm::stable_sort(order, [](const MemrefRecord *arrayValue,
                              const MemrefRecord *buildPoint) {
    if (arrayValue->bram != buildPoint->bram)
      return arrayValue->bram > buildPoint->bram;
    return arrayValue->id < buildPoint->id;
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
};

static SmallVector<PipelineRecord>
collectPipelineRecords(ModuleOp module, const TopScope &scope) {
  SmallVector<PipelineRecord> out;
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
    if (auto arr = portValue->getAttrOfType<ArrayAttr>(kLoopAutoUnrolledAttr))
      for (Attribute arrayValue : arr) {
        auto dict = dyn_cast<DictionaryAttr>(arrayValue);
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
    for (Attribute arrayValue : resultValue) {
      auto rd = dyn_cast<DictionaryAttr>(arrayValue);
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
    os << "; undefined value from @ " << widthValue.source << "\n";
  }
  if (static_cast<int64_t>(fieldValue.rewrites.size()) < elementCount)
    os << "  ... "
       << (elementCount - static_cast<int64_t>(fieldValue.rewrites.size()))
       << " more not recorded\n";
}

static void printDebugText(ArrayRef<MemrefRecord> records,
                           ArrayRef<PipelineRecord> pipelines,
                           ArrayRef<InstanceRecord> instances, int64_t total,
                           const FoldSummary &fold, BramFormula formula,
                           const TopScope &scope, llvm::raw_ostream &os) {
  os << "=== bram-debug: how each BRAM number was derived ===\n";
  os << "bram formula: " << formulaName(formula)
     << (formula == BramFormula::Band
             ? " (7-series depth bands, VITIS_NOTES.md N8)"
             : " (min over aspect-ratio modes, VITIS_NOTES.md N6)")
     << "\n";
  if (scope.active())
    os << "top: @" << scope.symbol << " (" << scope.funcs.size()
       << " function(s) reachable through calls; " << scope.skipped
       << " memref(s) outside them not costed)\n";
  else
    os << "top: none (every function is costed)\n";
  for (const MemrefRecord &resultValue : records) {
    if (resultValue.adapter) {
      const AdapterRecord &arrayValue = *resultValue.adapter;
      os << "[" << resultValue.id << "] m_axi bundle '" << arrayValue.bundle
         << "' (" << resultValue.kind << ") in @"
         << (resultValue.func ? *resultValue.func : "?") << " @ "
         << resultValue.locText << "\n";
      os << "  ports:";
      for (const std::string &portValue : arrayValue.ports)
        os << " " << portValue;
      os << "; bus width max(32, element bits) = " << arrayValue.busBits
         << "\n";
      os << "  read FIFO: "
         << (arrayValue.hasRead ? "used" : "no load from the bundle")
         << ", max_read_burst_length " << arrayValue.readBurst
         << " x num_read_outstanding " << arrayValue.readOutstanding
         << " = depth " << arrayValue.readDepth << " -> " << arrayValue.readBram
         << " BRAM (" << arrayValue.readRule << ")\n";
      os << "  write buffer: "
         << (arrayValue.hasWrite ? "used" : "no store to the bundle")
         << ", max_write_burst_length " << arrayValue.writeBurst
         << " (num_write_outstanding " << arrayValue.writeOutstanding
         << " has no effect) -> " << arrayValue.writeBram << " BRAM ("
         << arrayValue.writeRule << ")\n";
      if (arrayValue.unresolvedCall)
        os << "  note: an argument of the bundle is passed to a call without "
              "a body in the module; assumed read and written\n";
      else if (arrayValue.passedToCall)
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
    os << "  shape " << shapeString(resultValue.shape) << " x "
       << resultValue.elemType << " (" << resultValue.elemBits << " bits)";
    if (resultValue.words)
      os << " = " << *resultValue.words << " words";
    os << "\n";
    os << "  status: " << resultValue.status;
    if (resultValue.excludeReason)
      os << " -- " << *resultValue.excludeReason;
    os << "\n";
    if (resultValue.status == "eliminated_dead") {
      os << "  bram: 0\n";
      continue;
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
      for (const AccessRecord &arrayValue : resultValue.accesses) {
        os << "    - " << arrayValue.op << " "
           << (arrayValue.isWrite ? "write" : "read ") << " in "
           << arrayValue.scopeKind << " @ " << arrayValue.scopeLoc;
        if (arrayValue.scopeKind == "pipeline")
          os << " ii=" << arrayValue.ii << " stage=" << arrayValue.stageStart;
        if (arrayValue.viaCall)
          os << " (in @" << arrayValue.inFunc << " via " << *arrayValue.viaCall
             << (arrayValue.portBound ? ", port-bound" : "") << ")";
        if (arrayValue.storeEnable)
          os << " (store_enable: write-only, no read port)";
        if (arrayValue.mergedLoads)
          os << " (+" << arrayValue.mergedLoads
             << " same-address load(s) merged into it: CSE)";
        if (arrayValue.forwardedLoads || arrayValue.removedStores) {
          os << " (absorbed";
          if (arrayValue.forwardedLoads)
            os << " " << arrayValue.forwardedLoads << " forwarded load(s)";
          if (arrayValue.removedStores)
            os << (arrayValue.forwardedLoads ? "," : "") << " "
               << arrayValue.removedStores << " dead store(s)";
          os << ")";
        }
        os << "\n";
      }
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
  llvm::json::Object opHandle;
  opHandle["id"] = resultValue.id;
  opHandle["name"] = optStr(resultValue.name);
  opHandle["varname"] = optStr(resultValue.varname);
  opHandle["kind"] = resultValue.kind;
  opHandle["func"] = optStr(resultValue.func);

  if (resultValue.fromGlobal)
    opHandle["from_global"] = *resultValue.fromGlobal;
  if (resultValue.rom)
    opHandle["rom"] = true;
  if (resultValue.adapter) {
    const AdapterRecord &arrayValue = *resultValue.adapter;
    llvm::json::Object ad;
    ad["bundle"] = arrayValue.bundle;
    llvm::json::Array ports;
    for (const std::string &portValue : arrayValue.ports)
      ports.push_back(portValue);
    ad["ports"] = std::move(ports);
    ad["bus_bits"] = static_cast<int64_t>(arrayValue.busBits);
    ad["has_read"] = arrayValue.hasRead;
    ad["has_write"] = arrayValue.hasWrite;
    ad["passed_to_call"] = arrayValue.passedToCall;
    ad["unresolved_call"] = arrayValue.unresolvedCall;
    ad["max_read_burst_length"] = arrayValue.readBurst;
    ad["num_read_outstanding"] = arrayValue.readOutstanding;
    ad["read_depth"] = arrayValue.readDepth;
    ad["read_bram"] = static_cast<int64_t>(arrayValue.readBram);
    ad["read_rule"] = arrayValue.readRule;
    ad["max_write_burst_length"] = arrayValue.writeBurst;
    ad["num_write_outstanding"] = arrayValue.writeOutstanding;
    ad["write_bram"] = static_cast<int64_t>(arrayValue.writeBram);
    ad["write_rule"] = arrayValue.writeRule;
    opHandle["adapter"] = std::move(ad);
  }
  if (resultValue.hasLoc) {
    llvm::json::Object loc;
    loc["file"] = resultValue.locFile;
    loc["line"] = static_cast<int64_t>(resultValue.locLine);
    loc["col"] = static_cast<int64_t>(resultValue.locCol);
    opHandle["loc"] = std::move(loc);
  } else {
    opHandle["loc"] = nullptr;
  }
  llvm::json::Array shape;
  for (int64_t dimensionIndex : resultValue.shape)
    shape.push_back(ShapedType::isDynamic(dimensionIndex)
                        ? llvm::json::Value(nullptr)
                        : llvm::json::Value(dimensionIndex));
  opHandle["shape"] = std::move(shape);
  opHandle["elem_type"] = resultValue.elemType;
  opHandle["elem_bits"] = static_cast<int64_t>(resultValue.elemBits);
  opHandle["words"] = optInt(resultValue.words);
  opHandle["status"] = resultValue.status;
  opHandle["exclude_reason"] = optStr(resultValue.excludeReason);
  if (resultValue.keptReason)
    opHandle["kept_reason"] = *resultValue.keptReason;

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
    opHandle["partition"] = std::move(part);
  } else {
    opHandle["partition"] = nullptr;
  }

  llvm::json::Array accesses;
  for (const AccessRecord &arrayValue : resultValue.accesses) {
    llvm::json::Object ao;
    ao["op"] = arrayValue.op;
    ao["rw"] = arrayValue.isWrite ? "write" : "read";
    ao["scope"] = arrayValue.scopeKind;
    ao["scope_loc"] = arrayValue.scopeLoc;
    ao["ii"] = static_cast<int64_t>(arrayValue.ii);
    ao["stage_start"] = static_cast<int64_t>(arrayValue.stageStart);
    ao["store_enable"] = arrayValue.storeEnable;
    ao["merged_loads"] = static_cast<int64_t>(arrayValue.mergedLoads);
    ao["forwarded_loads"] = static_cast<int64_t>(arrayValue.forwardedLoads);
    ao["removed_stores"] = static_cast<int64_t>(arrayValue.removedStores);

    ao["in_func"] = arrayValue.inFunc.empty()
                        ? llvm::json::Value(nullptr)
                        : llvm::json::Value(arrayValue.inFunc);
    ao["via_call"] = optStr(arrayValue.viaCall);

    ao["port_bound"] = arrayValue.portBound;
    accesses.push_back(std::move(ao));
  }
  opHandle["accesses"] = std::move(accesses);

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
  opHandle["port_demand"] = std::move(pd);

  opHandle["ram_type"] = resultValue.ramType;
  opHandle["ram_reason"] = resultValue.ramReason;

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
    opHandle["replication"] = std::move(rp);
  } else {
    opHandle["replication"] = nullptr;
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
    opHandle["bank_math"] = std::move(bm);
  } else {
    opHandle["bank_math"] = nullptr;
  }
  opHandle["bram"] = static_cast<int64_t>(resultValue.bram);

  opHandle["instances"] = static_cast<int64_t>(resultValue.instances);
  opHandle["bram_per_instance"] =
      static_cast<int64_t>(resultValue.bramPerInstance);
  opHandle["owner_func"] = optStr(resultValue.ownerFunc);
  return opHandle;
}

static std::error_code writeDebugJson(ArrayRef<MemrefRecord> records,
                                      ArrayRef<PipelineRecord> pipelineRecords,
                                      ArrayRef<InstanceRecord> instanceRecords,
                                      int64_t total, const FoldSummary &fold,
                                      BramFormula formula,
                                      const TopScope &scope, StringRef path) {
  llvm::json::Object root;
  root["version"] = 2;
  root["total_bram"] = total;
  root["bram_formula"] = formulaName(formula);

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

static unsigned fifoBlocksNarrow(unsigned bits, int64_t depth) {
  return static_cast<unsigned>(estimateBlocksBand(depth, bits, false));
}

static void scanArgUses(Value valueHandle, AdapterRecord &arrayValue) {
  SmallVector<Value> work{valueHandle};
  DenseSet<Value> seen{valueHandle};
  while (!work.empty()) {
    Value cur = work.pop_back_val();
    for (OpOperand &use : cur.getUses()) {
      Operation *user = use.getOwner();
      if (auto view = dyn_cast<ViewLikeOpInterface>(user))
        if (view.getViewSource() == cur) {
          for (Value resultValue : user->getResults())
            if (isa<BaseMemRefType>(resultValue.getType()) &&
                seen.insert(resultValue).second)
              work.push_back(resultValue);
          continue;
        }
      if (auto callSite = dyn_cast<CallOpInterface>(user)) {
        arrayValue.passedToCall = true;
        auto callee =
            dyn_cast_or_null<func::FuncOp>(callSite.resolveCallable());
        auto args = callSite.getArgOperands();
        unsigned first = args.getBeginOperandIndex();
        unsigned elementCount = use.getOperandNumber();
        if (callee && !callee.isExternal() && elementCount >= first &&
            elementCount - first < callee.getNumArguments()) {
          Value inner = callee.getArgument(elementCount - first);
          if (seen.insert(inner).second)
            work.push_back(inner);
          continue;
        }
        arrayValue.unresolvedCall = arrayValue.hasRead = arrayValue.hasWrite =
            true;
        continue;
      }
      bool isWrite = false;
      if (classifyAccess(user, cur, isWrite))
        (isWrite ? arrayValue.hasWrite : arrayValue.hasRead) = true;
    }
  }
}

static int64_t intField(DictionaryAttr dimensionIndex, StringRef name,
                        int64_t dflt) {
  if (auto loopIndex = dimensionIndex.getAs<IntegerAttr>(name))
    return loopIndex.getInt();
  return dflt;
}

static SmallVector<std::pair<func::FuncOp, AdapterRecord>>
collectAdapters(ModuleOp module) {
  SmallVector<std::pair<func::FuncOp, AdapterRecord>> out;
  for (auto fn : module.getOps<func::FuncOp>()) {
    if (fn.isPrivate() || fn.isExternal())
      continue;
    SmallVector<AdapterRecord> bundles;
    for (unsigned loopIndex = 0, entryValue = fn.getNumArguments();
         loopIndex < entryValue; ++loopIndex) {
      auto ifaces = fn.getArgAttrOfType<ArrayAttr>(loopIndex, "hls.interface");
      if (!ifaces)
        continue;
      for (Attribute attr : ifaces) {
        auto dimensionIndex = dyn_cast<DictionaryAttr>(attr);
        auto mode = dimensionIndex ? dimensionIndex.getAs<StringAttr>("mode")
                                   : StringAttr();
        if (!mode || mode.getValue() != "m_axi")
          continue;
        std::string bundle = "gmem";
        if (auto buildPoint = dimensionIndex.getAs<StringAttr>("bundle"))
          bundle = buildPoint.getValue().str();
        AdapterRecord *arrayValue = nullptr;
        for (AdapterRecord &exprValue : bundles)
          if (exprValue.bundle == bundle)
            arrayValue = &exprValue;
        if (!arrayValue) {
          bundles.emplace_back();
          arrayValue = &bundles.back();
          arrayValue->bundle = bundle;
          arrayValue->readBurst = arrayValue->readOutstanding = 0;
          arrayValue->writeBurst = arrayValue->writeOutstanding = 0;
        }
        if (auto portValue = dimensionIndex.getAs<StringAttr>("port"))
          arrayValue->ports.push_back(portValue.getValue().str());
        Value arg = fn.getArgument(loopIndex);
        unsigned bits = 32;
        if (auto mt = dyn_cast<BaseMemRefType>(arg.getType())) {
          Type elt = mt.getElementType();
          bits = elt.isIntOrFloat()    ? elt.getIntOrFloatBitWidth()
                 : isa<IndexType>(elt) ? 64u
                                       : 32u;
        } else if (arg.getType().isIntOrFloat()) {
          bits = arg.getType().getIntOrFloatBitWidth();
        }
        arrayValue->busBits =
            std::max(arrayValue->busBits, std::max(32u, bits));

        arrayValue->readBurst =
            std::max(arrayValue->readBurst,
                     intField(dimensionIndex, "max_read_burst_length", 0));
        arrayValue->readOutstanding =
            std::max(arrayValue->readOutstanding,
                     intField(dimensionIndex, "num_read_outstanding", 0));
        arrayValue->writeBurst =
            std::max(arrayValue->writeBurst,
                     intField(dimensionIndex, "max_write_burst_length", 0));
        arrayValue->writeOutstanding =
            std::max(arrayValue->writeOutstanding,
                     intField(dimensionIndex, "num_write_outstanding", 0));
        scanArgUses(arg, *arrayValue);
      }
    }
    for (AdapterRecord &arrayValue : bundles) {
      if (!arrayValue.readBurst)
        arrayValue.readBurst = 16;
      if (!arrayValue.readOutstanding)
        arrayValue.readOutstanding = 16;
      if (!arrayValue.writeBurst)
        arrayValue.writeBurst = 16;
      if (!arrayValue.writeOutstanding)
        arrayValue.writeOutstanding = 16;
      arrayValue.readDepth = arrayValue.readBurst * arrayValue.readOutstanding;

      if (!arrayValue.hasRead) {
        arrayValue.readBram = 0;
        arrayValue.readRule = "no load: no read FIFO cost";
      } else if (arrayValue.readDepth <= 32) {
        arrayValue.readBram = 0;
        arrayValue.readRule = "depth <= 32: shift-register FIFO, 0 BRAM";
      } else {
        arrayValue.readBram =
            fifoBlocksNarrow(arrayValue.busBits, arrayValue.readDepth);
        arrayValue.readRule =
            "depth > 32: BRAM FIFO, two ports (x18 bands of N8)";
        if (arrayValue.readDepth > 4096)
          arrayValue.readRule += "; depth > 4096 unconfirmed";
      }

      if (!arrayValue.hasWrite) {
        arrayValue.writeBram = 0;
        arrayValue.writeRule = "no store: no write buffer cost";
      } else if (arrayValue.writeBurst <= 16) {
        arrayValue.writeBram = 0;
        arrayValue.writeRule = "max_write_burst_length <= 16: 0 BRAM";
      } else {
        arrayValue.writeBram =
            static_cast<unsigned>(ceilDiv(arrayValue.busBits, 18));
        arrayValue.writeRule = "max_write_burst_length > 16: ceil(W/18)";
        if (arrayValue.writeBurst < 32)
          arrayValue.writeRule += " (bursts 17..31 unconfirmed)";
      }
      out.push_back({fn, std::move(arrayValue)});
    }
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
                               : isa<IndexType>(elt) ? 64u
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
        if (auto globalOp = dyn_cast_or_null<memref::GlobalOp>(symbolName))
          scope.globals.insert(globalOp.getSymName());
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
               [](const InstanceRecord::Parent &arrayValue,
                  const InstanceRecord::Parent &buildPoint) {
                 return arrayValue.parent < buildPoint.parent;
               });
    out.push_back(std::move(resultValue));
  }
  llvm::sort(out, [](const InstanceRecord &arrayValue,
                     const InstanceRecord &buildPoint) {
    return arrayValue.func < buildPoint.func;
  });
  return out;
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

  void runOnOperation() override {
    ModuleOp module = getOperation();
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
    int64_t total = 0;

    std::vector<MemrefRecord> records;
    unsigned index = 0;

    SeqScopeIndex seqIndex;
    SeqScopeIndex *seq = bramSeqDualPortOpt ? &seqIndex : nullptr;

    llvm::StringMap<SmallVector<Value>> globalSites;
    if (bramAttributeGlobalsOpt)
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
      if (auto globalOp = dyn_cast<memref::GlobalOp>(op)) {
        attributed = bramAttributeGlobalsOpt;
        if (attributed) {
          auto it = globalSites.find(globalOp.getSymName());
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
      if (auto globalOp = dyn_cast<memref::GlobalOp>(op)) {
        auto it = globalUseSites.find(globalOp.getSymName());
        if (it != globalUseSites.end())
          allSites = it->second;
      } else {
        allSites = banks;
      }
      BRAMCost cost = estimateBRAM(iface, rec, banks, attributed, seq,
                                   formulaOpt, &instanceModel, allSites);

      unsigned instances = 1;
      bool sharedGlobal = false;
      if (auto globalOp = dyn_cast<memref::GlobalOp>(op)) {
        auto it = globalUsers.find(globalOp.getSymName());
        if (it != globalUsers.end()) {
          auto sites = globalUseSites.find(globalOp.getSymName());
          bool written = !globalOp.getConstant() &&
                         sites != globalUseSites.end() &&
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
      llvm::outs() << op->getName() << " @ " << op->getLoc() << "\n"
                   << "  kind=" << kindName(cost.kind)
                   << "  bram=" << cost.bramCount
                   << (cost.infeasible ? "  [INFEASIBLE]" : "") << "\n"
                   << "    " << cost.note << "\n";
      total += cost.bramCount;
      records.push_back(std::move(rec));
    });

    if (bramMaxiAdaptersOpt)
      for (auto &[fn, arrayValue] : collectAdapters(module)) {
        if (scope.active() && fn.getName() != scope.symbol)
          continue;
        unsigned bram = arrayValue.readBram + arrayValue.writeBram;
        llvm::outs() << "m_axi.adapter bundle=" << arrayValue.bundle
                     << " func=@" << fn.getName() << " bram=" << bram
                     << " (read FIFO " << arrayValue.readDepth << "x"
                     << arrayValue.busBits << "b -> " << arrayValue.readBram
                     << ", write burst " << arrayValue.writeBurst << " -> "
                     << arrayValue.writeBram << ")\n";
        total += bram;
        MemrefRecord rec;
        rec.id = fn.getName().str() + "#m_axi:" + arrayValue.bundle;
        rec.kind = "m_axi_adapter";
        rec.name = arrayValue.bundle;
        rec.varname = arrayValue.bundle + "_m_axi";
        rec.func = fn.getName().str();
        rec.locText = locString(fn.getLoc());
        if (auto fieldValue = findFileLoc(fn.getLoc())) {
          rec.hasLoc = true;
          rec.locFile = fieldValue.getFilename().str();
          rec.locLine = fieldValue.getLine();
          rec.locCol = fieldValue.getColumn();
        }
        rec.shape = {arrayValue.readDepth};
        rec.elemType = "i" + std::to_string(arrayValue.busBits);
        rec.elemBits = arrayValue.busBits;
        rec.words = arrayValue.readDepth;
        rec.status = "counted";
        rec.ramType = "M_AXI_ADAPTER";
        rec.ramReason = "read FIFO: " + arrayValue.readRule +
                        "; write buffer: " + arrayValue.writeRule;
        rec.bram = bram;
        rec.adapter = std::move(arrayValue);
        records.push_back(std::move(rec));
      }
    llvm::outs() << "Total BRAM: " << total << "\n";
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

    SmallVector<PipelineRecord> pipelines;
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
                     formulaOpt, scope, llvm::errs());
    if (!bramDebugJsonOpt.empty())
      if (std::error_code ec =
              writeDebugJson(records, pipelines, instanceRecords, total, fold,
                             formulaOpt, scope, bramDebugJsonOpt)) {

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
