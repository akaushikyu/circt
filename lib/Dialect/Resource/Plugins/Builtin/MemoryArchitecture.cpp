

// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#include "Builtins.h"

#include "circt/Dialect/LoopSchedule/LoopScheduleOps.h"
#include "circt/Dialect/Resource/Model/AccessOrder.h"
#include "circt/Dialect/Resource/Passes/MemrefBankClassification.h"
#include "circt/Dialect/Resource/Passes/StoragePragmas.h"
#include "circt/Dialect/Resource/Plugins/MemoryInterfaces.h"
#include "circt/Dialect/Resource/Plugins/Registry.h"

#include "mlir/Dialect/Affine/IR/AffineOps.h"
#include "mlir/Dialect/Arith/IR/Arith.h"
#include "mlir/Dialect/MemRef/IR/MemRef.h"
#include "mlir/IR/BuiltinTypes.h"
#include "mlir/IR/Matchers.h"
#include "mlir/Interfaces/CallInterfaces.h"
#include "mlir/Interfaces/LoopLikeInterface.h"
#include "llvm/ADT/BitVector.h"
#include "llvm/ADT/DenseSet.h"
#include "llvm/Support/raw_ostream.h"

#include <array>
#include <functional>
#include <limits>
#include <map>

using namespace mlir;
using namespace circt::hls_analysis;
using circt::hlsest::Config;
using circt::loopschedule::LoopSchedulePipelineOp;

namespace {

const Config &config() { return Config::get(); }

int64_t ceilDiv(int64_t arrayValue, int64_t buildPoint) {
  return (arrayValue + buildPoint - 1) / buildPoint;
}

/// The widest port of a bank priced wide (36) or narrow (18).
unsigned maxPortWidth(bool wide) {
  return static_cast<unsigned>(config().pricedPortWidth(wide));
}

/// Ports of one block in its true-dual-port configuration (2).
unsigned blockPorts() { return static_cast<unsigned>(config().blockPorts()); }

/// tool.hls.memory_architecture.replication.max_copies (16).
unsigned maxReplicationCopies() {
  return static_cast<unsigned>(
      config().tool.hls.memoryArchitecture.replication.maxCopies);
}

class DepSet {
public:
  bool test(unsigned loopIndex) const {
    return loopIndex < prefix ||
           (loopIndex < tail.size() && tail.test(loopIndex));
  }
  bool any() const { return prefix > 0 || firstTailBit(0) >= 0; }
  /// Every index below this is in the set.
  unsigned prefixSize() const { return prefix; }
  void set(unsigned loopIndex) {
    if (loopIndex < prefix)
      return;
    if (loopIndex >= tail.size())
      tail.resize(loopIndex + 1);
    tail.set(loopIndex);
    normalize();
  }
  /// Adds every index below `n`.
  void setPrefix(unsigned n) {
    if (n <= prefix)
      return;
    prefix = n;
    normalize();
  }
  DepSet &operator|=(const DepSet &opHandle) {
    prefix = std::max(prefix, opHandle.prefix);
    if (opHandle.firstTailBit(prefix) >= 0) {
      if (tail.size() < opHandle.tail.size())
        tail.resize(opHandle.tail.size());
      tail |= opHandle.tail;
    }
    normalize();
    return *this;
  }
  /// Whether some index of this set is missing from `o` (BitVector::test).
  bool hasIndexNotIn(const DepSet &opHandle) const {
    if (prefix > opHandle.prefix)
      return true;

    unsigned from = opHandle.prefix;
    if (from >= tail.size())
      return false;
    ArrayRef<uintptr_t> mine = tail.getData();
    ArrayRef<uintptr_t> theirs = opHandle.tail.getData();
    constexpr unsigned kWordBits = sizeof(uintptr_t) * 8;
    unsigned first = from / kWordBits;
    for (unsigned widthValue = first; widthValue < mine.size(); ++widthValue) {
      uintptr_t missing =
          mine[widthValue] &
          ~(widthValue < theirs.size() ? theirs[widthValue] : uintptr_t(0));
      if (widthValue == first)
        missing &= ~uintptr_t(0) << (from % kWordBits);
      if (missing)
        return true;
    }
    return false;
  }
  /// The smallest index >= `from` that is not in the set.
  unsigned nextUnset(unsigned from) const {
    from = std::max(from, prefix);
    if (from >= tail.size())
      return from;
    int useValue = tail.find_first_unset_in(from, tail.size());
    return useValue < 0 ? static_cast<unsigned>(tail.size())
                        : static_cast<unsigned>(useValue);
  }

private:
  unsigned prefix = 0;
  llvm::BitVector tail; ///< absolute indices; bits below prefix are ignored

  int firstTailBit(unsigned from) const {
    from = std::max(from, prefix);
    return from < tail.size() ? tail.find_first_in(from, tail.size()) : -1;
  }
  /// Moves the run of set bits at `prefix` into the prefix and drops a tail
  /// that holds nothing above it.
  void normalize() {
    if (prefix < tail.size() && tail.test(prefix)) {
      int useValue = tail.find_first_unset_in(prefix, tail.size());
      prefix = useValue < 0 ? static_cast<unsigned>(tail.size())
                            : static_cast<unsigned>(useValue);
    }
    if (!tail.empty() && firstTailBit(prefix) < 0)
      tail = llvm::BitVector();
  }
};

static bool isMultiCycleOp(Operation *op) {
  if (isa<CallOpInterface>(op) || isa<memref::LoadOp, affine::AffineLoadOp>(op))
    return true;
  if (op->getNumResults() != 1 || op->getNumRegions() != 0)
    return false;
  if (isa<arith::ConstantOp, arith::SelectOp, arith::BitcastOp>(op))
    return false;
  StringRef targetDialect = op->getName().getDialectNamespace();
  if (targetDialect == "math")
    return true;
  if (targetDialect != "arith")
    return false;

  if (llvm::any_of(op->getOperandTypes(),
                   [](Type typeValue) { return isa<FloatType>(typeValue); }))
    return true;

  if (isa<arith::MulIOp>(op))
    return !matchPattern(op->getOperand(0), m_Constant()) &&
           !matchPattern(op->getOperand(1), m_Constant());
  return isa<arith::DivSIOp, arith::DivUIOp, arith::RemSIOp, arith::RemUIOp,
             arith::CeilDivSIOp, arith::CeilDivUIOp, arith::FloorDivSIOp>(op);
}

static const std::vector<int64_t> &
stretchStartCycles(const SeqScopeIndex::Scope &stringValue, unsigned stretch) {
  if (stringValue.startCycles.size() <= stretch)
    stringValue.startCycles.resize(stringValue.stretches.size());
  std::vector<int64_t> &start = stringValue.startCycles[stretch];
  const std::vector<Operation *> &ops = stringValue.stretches[stretch];
  if (start.size() == ops.size())
    return start;
  start.assign(ops.size(), 0);
  for (unsigned portValue = 0; portValue < ops.size(); ++portValue) {
    int64_t typeValue = 0;
    auto addValue = [&](Value valueHandle) {
      Operation *def = valueHandle.getDefiningOp();
      if (!def)
        return;
      auto it = stringValue.info.find(def);
      if (it == stringValue.info.end() || it->second.stretch != stretch ||
          it->second.ordinal >= portValue)
        return;
      typeValue = std::max(typeValue, start[it->second.ordinal] +
                                          (isMultiCycleOp(def) ? 1 : 0));
    };
    for (Value valueHandle : ops[portValue]->getOperands())
      addValue(valueHandle);
    for (Region &region : ops[portValue]->getRegions())
      for (Block &block : region)
        if (!block.empty())
          for (Value valueHandle : block.back().getOperands())
            addValue(valueHandle);
    start[portValue] = typeValue;
  }
  return start;
}

/// The cycle the first consumer of the read `op` starts in (the latest cycle
/// of the stretch when nothing in the stretch consumes it: the reads that
/// feed a later loop all wait for it, polybench atax's hoisted buff_x).
static int64_t firstConsumerCycle(const SeqScopeIndex::Scope &stringValue,
                                  unsigned stretch, Operation *op) {
  const std::vector<int64_t> &start = stretchStartCycles(stringValue, stretch);
  int64_t first = std::numeric_limits<int64_t>::max();
  for (Operation *user : op->getUsers()) {
    auto it = stringValue.info.find(user);
    if (it != stringValue.info.end() && it->second.stretch == stretch)
      first = std::min(first, start[it->second.ordinal]);
  }
  return first;
}

static const SeqScopeIndex::Scope::StretchOperands &
stretchOperands(const SeqScopeIndex::Scope &stringValue, unsigned stretch) {
  if (stringValue.operands.size() <= stretch)
    stringValue.operands.resize(stringValue.stretches.size());
  SeqScopeIndex::Scope::StretchOperands &cache = stringValue.operands[stretch];
  const std::vector<Operation *> &ops = stringValue.stretches[stretch];
  if (!cache.infos.empty() || ops.empty())
    return cache;
  cache.infos.resize(ops.size());
  cache.defs.resize(ops.size());
  cache.touches.resize(ops.size());
  for (auto [portValue, op] : llvm::enumerate(ops)) {
    cache.infos[portValue] = &stringValue.info.find(op)->second;
    memTouches(op, cache.touches[portValue]);
    auto addValue = [&](Value valueHandle) {
      Operation *def = valueHandle.getDefiningOp();
      if (!def)
        return;
      auto it = stringValue.info.find(def);
      if (it != stringValue.info.end() && it->second.stretch == stretch)
        cache.defs[portValue].push_back(it->second.ordinal);
    };
    for (Value valueHandle : op->getOperands())
      addValue(valueHandle);
    for (Region &region : op->getRegions())
      for (Block &block : region)
        if (!block.empty())
          for (Value valueHandle : block.back().getOperands())
            addValue(valueHandle);
  }
  return cache;
}

static std::optional<std::pair<const AccessSummary *, const AccessSummary *>>
findSameStatePair(ArrayRef<const AccessSummary *> accs,
                  const SeqScopeIndex::Scope &stringValue, unsigned stretch,
                  const DenseSet<Value> &bankValues) {
  unsigned keyValue = accs.size();
  const std::vector<Operation *> &ops = stringValue.stretches[stretch];
  SmallVector<unsigned> ord(keyValue);
  SmallVector<const SeqScopeIndex::OpInfo *> info(keyValue);
  for (unsigned innerIndex = 0; innerIndex < keyValue; ++innerIndex) {
    info[innerIndex] = &stringValue.info.find(accs[innerIndex]->op)->second;
    ord[innerIndex] = info[innerIndex]->ordinal;
  }
  unsigned lo = ord.front(), hi = ord.back();

  std::vector<DepSet> deps(hi - lo + 1);

  unsigned barrier = 0;

  SmallVector<ArrayRef<int64_t>> hoistedArms(keyValue);
  for (unsigned innerIndex = 0; innerIndex < keyValue; ++innerIndex)
    hoistedArms[innerIndex] = hoistedArmsOf(accs[innerIndex]->op);
  auto exclusive = [&](unsigned loopIndex, unsigned innerIndex) {
    return inExclusiveArms(*info[loopIndex], hoistedArms[loopIndex],
                           *info[innerIndex], hoistedArms[innerIndex]);
  };
  const bool readsBeforeConsumer =
      config().tool.hls.memoryArchitecture.sequentialLoadsBeforeConsumer;
  SmallVector<std::optional<int64_t>> consumerCycles(keyValue);
  auto consumerCycle = [&](unsigned loopIndex) {
    if (!consumerCycles[loopIndex])
      consumerCycles[loopIndex] =
          firstConsumerCycle(stringValue, stretch, accs[loopIndex]->op);
    return *consumerCycles[loopIndex];
  };

  struct MemEvent {
    Operation *op;
    unsigned pos;
    int acc;
    ArrayRef<MemTouch> touches;
  };
  std::vector<MemEvent> events;

  static constexpr unsigned kBlockFanout = 8, kBlockLevels = 4;
  struct EventList {
    SmallVector<unsigned> ids;
    std::array<std::vector<DepSet>, kBlockLevels> unions;
    void push(unsigned ei) {
      if (ids.empty() || ids.back() != ei)
        ids.push_back(ei);
    }
  };

  struct EventIndex {
    DenseMap<const void *, EventList> byKey, byKeyW;
    EventList anyStorage, all, anyStorageW, allW;
    void add(unsigned ei, ArrayRef<MemTouch> touches) {
      all.push(ei);
      for (const MemTouch &typeValue : touches) {
        if (typeValue.write)
          allW.push(ei);
        if (!typeValue.key) {
          anyStorage.push(ei);
          if (typeValue.write)
            anyStorageW.push(ei);
          continue;
        }
        byKey[typeValue.key].push(ei);
        if (typeValue.write)
          byKeyW[typeValue.key].push(ei);
      }
    }
  };
  EventIndex allEvents, otherEvents;
  SmallVector<unsigned> seenStamp;
  unsigned stamp = 0;
  const SeqScopeIndex::Scope::StretchOperands &operands =
      stretchOperands(stringValue, stretch);

  std::vector<int> accAt(hi - lo + 1, -1);
  for (unsigned innerIndex = 0; innerIndex < keyValue; ++innerIndex)
    accAt[ord[innerIndex] - lo] = static_cast<int>(innerIndex);
  for (unsigned portValue = lo; portValue <= hi; ++portValue) {
    Operation *op = ops[portValue];
    DepSet &dimensionIndex = deps[portValue - lo];
    for (unsigned def : operands.defs[portValue]) {
      if (def < lo || def >= portValue)
        continue;
      dimensionIndex |= deps[def - lo];
      if (accAt[def - lo] >= 0)
        dimensionIndex.set(static_cast<unsigned>(accAt[def - lo]));
    }
    int selfAcc = accAt[portValue - lo];

    ArrayRef<MemTouch> touches = operands.touches[portValue];
    EventIndex &index = selfAcc >= 0 ? otherEvents : allEvents;
    if (!touches.empty() && !index.all.ids.empty()) {
      const SeqScopeIndex::OpInfo &opInfo = *operands.infos[portValue];
      ArrayRef<int64_t> opHoisted = hoistedArmsOf(op);

      ++stamp;

      auto consider = [&](unsigned ei) {
        if (seenStamp[ei] == stamp)
          return;
        seenStamp[ei] = stamp;
        const MemEvent &entryValue = events[ei];
        const DepSet &ed = deps[entryValue.pos - lo];
        if (!ed.hasIndexNotIn(dimensionIndex) &&
            !(entryValue.acc >= 0 && !dimensionIndex.test(entryValue.acc)))
          return;
        if (inExclusiveArms(*operands.infos[entryValue.pos],
                            hoistedArmsOf(entryValue.op), opInfo, opHoisted))
          return;
        bool conflict =
            llvm::any_of(entryValue.touches, [&](const MemTouch &arrayValue) {
              return llvm::any_of(touches, [&](const MemTouch &buildPoint) {
                return mayConflict(entryValue.op, arrayValue, op, buildPoint);
              });
            });
        if (!conflict)
          return;
        dimensionIndex |= ed;
        if (entryValue.acc >= 0)
          dimensionIndex.set(entryValue.acc);
      };
      auto blockSize = [](unsigned level) {
        unsigned size = kBlockFanout;
        for (unsigned lowerIndex = 0; lowerIndex < level; ++lowerIndex)
          size *= kBlockFanout;
        return size;
      };

      auto blockUnion = [&](auto &self, EventList &list, unsigned level,
                            unsigned buildPoint) -> const DepSet & {
        std::vector<DepSet> &unions = list.unions[level];
        while (unions.size() <= buildPoint) {
          unsigned candidateValue = unions.size();
          DepSet useValue;
          for (unsigned innerIndex = 0; innerIndex < kBlockFanout;
               ++innerIndex) {
            unsigned child = candidateValue * kBlockFanout + innerIndex;
            if (level > 0) {
              useValue |= self(self, list, level - 1, child);
              continue;
            }
            const MemEvent &entryValue = events[list.ids[child]];
            useValue |= deps[entryValue.pos - lo];
            if (entryValue.acc >= 0)
              useValue.set(static_cast<unsigned>(entryValue.acc));
          }
          unions.push_back(std::move(useValue));
        }
        return unions[buildPoint];
      };

      auto visit = [&](auto &self, EventList &list, unsigned level,
                       unsigned buildPoint) -> void {
        unsigned n = list.ids.size(), size = blockSize(level);
        unsigned first = buildPoint * size;
        if (first >= n)
          return;
        if (n - first >= size &&
            !blockUnion(blockUnion, list, level, buildPoint)
                 .hasIndexNotIn(dimensionIndex))
          return;
        if (level > 0) {
          for (unsigned innerIndex = kBlockFanout; innerIndex-- > 0;)
            self(self, list, level - 1, buildPoint * kBlockFanout + innerIndex);
          return;
        }
        for (unsigned loopIndex = std::min(n, first + size);
             loopIndex-- > first;)
          consider(list.ids[loopIndex]);
      };
      auto add = [&](EventList &list) {
        unsigned top = kBlockLevels - 1, size = blockSize(top);
        for (unsigned buildPoint = (list.ids.size() + size - 1) / size;
             buildPoint-- > 0;)
          visit(visit, list, top, buildPoint);
      };
      bool anyStorageWrite =
          llvm::any_of(touches, [](const MemTouch &typeValue) {
            return typeValue.key == nullptr && typeValue.write;
          });
      if (anyStorageWrite) {
        add(index.all);
      } else {
        bool anyWrite = false;
        for (const MemTouch &typeValue : touches) {
          if (!typeValue.key) {
            add(index.allW);
            continue;
          }
          anyWrite |= typeValue.write;
          auto &byKey = typeValue.write ? index.byKey : index.byKeyW;
          auto it = byKey.find(typeValue.key);
          if (it != byKey.end())
            add(it->second);
        }
        add(anyWrite ? index.anyStorage : index.anyStorageW);
      }
    }
    if (!touches.empty() && (selfAcc >= 0 || dimensionIndex.any())) {
      unsigned ei = events.size();
      events.push_back({op, portValue, selfAcc, touches});
      seenStamp.push_back(0);
      allEvents.add(ei, touches);
      if (selfAcc < 0)
        otherEvents.add(ei, touches);
    }
    if (selfAcc < 0) {

      if (llvm::any_of(op->getOperands(), [&](Value valueHandle) {
            return bankValues.contains(valueHandle);
          }))
        barrier = std::max<unsigned>(
            barrier, static_cast<unsigned>(llvm::lower_bound(ord, portValue) -
                                           ord.begin()));
      continue;
    }
    unsigned innerIndex = static_cast<unsigned>(selfAcc);
    dimensionIndex.setPrefix(barrier);

    for (unsigned loopIndex = innerIndex;
         loopIndex-- > dimensionIndex.prefixSize();) {
      if (dimensionIndex.test(loopIndex) || exclusive(loopIndex, innerIndex) ||
          !(accs[loopIndex]->isWrite || accs[innerIndex]->isWrite))
        continue;
      if (compareAddresses(accs[loopIndex]->op, op) != AddrRelation::Disjoint) {
        dimensionIndex.set(loopIndex);
        dimensionIndex |= deps[ord[loopIndex] - lo];
      }
    }
    for (unsigned loopIndex = dimensionIndex.nextUnset(0);
         loopIndex < innerIndex;
         loopIndex = dimensionIndex.nextUnset(loopIndex + 1)) {
      if (exclusive(loopIndex, innerIndex))
        continue;
      if (!accs[loopIndex]->isWrite && !accs[innerIndex]->isWrite &&
          compareAddresses(accs[loopIndex]->op, op) == AddrRelation::Same)
        continue;
      if (readsBeforeConsumer && !accs[loopIndex]->isWrite &&
          !accs[innerIndex]->isWrite &&
          consumerCycle(loopIndex) != consumerCycle(innerIndex))
        continue;
      return std::make_pair(accs[loopIndex], accs[innerIndex]);
    }
  }
  return std::nullopt;
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

static unsigned sequentialRomReadsImpl(ArrayRef<const AccessSummary *> group,
                                       SeqScopeIndex &index) {
  Operation *scope = group.front()->scope;
  if (!scope)
    return 0;
  const SeqScopeIndex::Scope &stringValue = index.get(scope);
  std::map<unsigned, SmallVector<Operation *>> byStretch;
  for (const AccessSummary *arrayValue : group) {
    if (arrayValue->isWrite)
      return 0;
    auto it = stringValue.info.find(arrayValue->op);
    if (it != stringValue.info.end())
      byStretch[it->second.stretch].push_back(arrayValue->op);
  }
  unsigned best = 0;
  for (auto &[stretch, reads] : byStretch) {
    DenseSet<Operation *> isRead(reads.begin(), reads.end());

    DenseMap<Operation *, unsigned> memo;
    auto inStretch = [&](Operation *op) {
      auto it = stringValue.info.find(op);
      return it != stringValue.info.end() && it->second.stretch == stretch;
    };
    auto operandDefs = [&](Operation *op) {
      SmallVector<Operation *> defs;
      auto from = [&](Value valueHandle) {
        if (Operation *def = valueHandle.getDefiningOp())
          defs.push_back(def);
      };
      for (Value valueHandle : op->getOperands())
        from(valueHandle);
      for (Region &region : op->getRegions())
        for (Block &block : region)
          if (!block.empty())
            for (Value valueHandle : block.back().getOperands())
              from(valueHandle);
      return defs;
    };
    auto valueDepth = [&](Operation *root) -> unsigned {
      DenseSet<Operation *> open;
      SmallVector<std::pair<Operation *, bool>> stack{{root, false}};
      while (!stack.empty()) {
        auto [op, expanded] = stack.pop_back_val();
        if (memo.contains(op))
          continue;
        if (!inStretch(op)) {
          memo[op] = 0;
          continue;
        }
        SmallVector<Operation *> defs = operandDefs(op);
        if (!expanded) {
          if (!open.insert(op).second)
            continue;
          stack.push_back({op, true});
          for (Operation *def : defs)
            if (!memo.contains(def) && !open.contains(def))
              stack.push_back({def, false});
          continue;
        }
        unsigned dimensionIndex = 0;
        for (Operation *def : defs)
          dimensionIndex = std::max(dimensionIndex, memo.lookup(def));
        if (isRead.contains(op))
          ++dimensionIndex;
        memo[op] = dimensionIndex;
      }
      return memo.lookup(root);
    };
    std::map<unsigned, unsigned> perDepth;
    for (Operation *resultValue : reads) {
      unsigned issue = 0;
      for (Value valueHandle : resultValue->getOperands())
        if (Operation *def = valueHandle.getDefiningOp())
          issue = std::max(issue, valueDepth(def));
      best = std::max(best, ++perDepth[issue]);
    }
  }
  return best;
}

static const char *kindName(StorageKind keyValue) {
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
  const unsigned ports = blockPorts();

  if (total <= 1) {
    resultValue.kind = StorageKind::RAM_1P;
    return resultValue;
  }
  if (total <= ports) {
    resultValue.kind =
        widthValue >= 2 ? StorageKind::RAM_T2P : StorageKind::RAM_2P;
    return resultValue;
  }

  resultValue.kind = StorageKind::RAM_T2P;
  resultValue.infeasible = true;
  resultValue.note = "port demand " + std::to_string(total) + "/cycle (" +
                     std::to_string(rd) + "R+" + std::to_string(widthValue) +
                     "W, multi-writer) exceeds " + std::to_string(ports) +
                     " ports; needs array_partition.";
  return resultValue;
}

/// The port set each kind stands for (tool.hls.memory_architecture.
/// port_set_rule = by_kind); empty for a kind with more than two ports
/// (RAM_1WNR, ROM_NP: every copy is priced narrow) or no block RAM at all.
static std::vector<std::string> kindPortSet(StorageKind keyValue) {
  switch (keyValue) {
  case StorageKind::RAM_1P:
    return {"rw"};
  case StorageKind::RAM_2P:
    return {"rw", "r"};
  case StorageKind::RAM_T2P:
    return {"rw", "rw"};
  case StorageKind::RAM_S2P:
    return {"r", "w"};
  case StorageKind::ROM_1P:
    return {"r"};
  case StorageKind::ROM_2P:
    return {"r", "r"};
  case StorageKind::RAM_1WNR:
  case StorageKind::ROM_NP:
  case StorageKind::LUTRAM:
  case StorageKind::URAM:
    return {};
  }
  return {};
}

static bool isWideKind(StorageKind keyValue) {

  std::vector<std::string> ports = kindPortSet(keyValue);
  return !ports.empty() &&
         config().tool.hls.memoryArchitecture.isWidePortSet(ports);
}

static unsigned blockDataWidth(StorageKind keyValue) {
  if (keyValue == StorageKind::LUTRAM || keyValue == StorageKind::URAM)
    return 0;
  return maxPortWidth(isWideKind(keyValue));
}

/// Copies of a replicated bank that give `need` port-cycles per cycle: every
/// copy adds its ports but the shared write port (port B of a true-dual-port
/// block reads), and the shared write port reads when idle
/// (tool.hls.memory_architecture.replication.shared_write_port_reads_when_idle):
/// need - 1 for Vitis. At least 1.
static unsigned copiesForPortCycles(unsigned need) {
  const bool idleReads =
      config()
          .tool.hls.memoryArchitecture.replication.sharedWritePortReadsWhenIdle;
  const unsigned perCopy = std::max(1u, blockPorts() - 1);
  unsigned shared = idleReads ? 1u : 0u;
  if (need <= shared)
    return 1;
  return std::max<unsigned>(
      1, static_cast<unsigned>(ceilDiv(need - shared, perCopy)));
}

/// Whether the memory `access` reads or writes carries a user
/// `bind_storage type=ram_1wnr` (hls.bind_storage on its alloca / bank).
static bool boundRam1wnr(Operation *access) {
  Value mem;
  for (Value valueHandle : access->getOperands())
    if (isa<BaseMemRefType>(valueHandle.getType())) {
      mem = valueHandle;
      break;
    }
  Operation *def = mem ? mem.getDefiningOp() : nullptr;
  auto binds =
      def ? def->getAttrOfType<ArrayAttr>("hls.bind_storage") : ArrayAttr();
  if (!binds)
    return false;
  for (Attribute buildPoint : binds)
    if (auto dimensionIndex = dyn_cast<DictionaryAttr>(buildPoint))
      if (auto typeValue = dimensionIndex.getAs<StringAttr>("type"))
        if (typeValue.getValue().equals_insensitive("ram_1wnr"))
          return true;
  return false;
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

    unsigned rotatingReads = 0;
    bool portBound = false;
    SmallVector<Operation *> stores;

    SmallVector<Operation *> steeredReads;
    bool allReadsVarying = false;
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

    if (!arrayValue.isWrite && arrayValue.op)
      if (auto reloads =
              arrayValue.op->getAttrOfType<IntegerAttr>("hls.select_reloads"))
        st->reads = static_cast<unsigned>(std::max<int64_t>(
            0, static_cast<int64_t>(st->reads) + reloads.getInt()));
    if (!arrayValue.isWrite && arrayValue.op &&
        arrayValue.op->hasAttr("hls.rotating_bank") &&
        arrayValue.op->hasAttr("hls.bank_address_varies"))
      ++st->rotatingReads;
    if (arrayValue.isWrite && arrayValue.op)
      st->stores.push_back(arrayValue.op);
    if (!arrayValue.isWrite && arrayValue.op &&
        arrayValue.op->hasAttr("hls.runtime_bank"))
      st->steeredReads.push_back(arrayValue.op);
    st->portBound |= arrayValue.portBound;
  }

  for (ScopeStats &stringValue : scopes)
    if (stringValue.scope && stringValue.stores.size() == stringValue.writes &&
        stringValue.writes > 1)
      stringValue.writes = circt::hls_analysis::maxStoresInOneIteration(
          stringValue.stores, stringValue.scope);
  const circt::hlsest::ReplicationConfig &repCfg =
      config().tool.hls.memoryArchitecture.replication;

  for (ScopeStats &stringValue : scopes) {
    stringValue.allReadsVarying =
        stringValue.reads > 0 && stringValue.rotatingReads == stringValue.reads;
    if (repCfg.exclusiveSteeredReadsShareSlot && stringValue.scope &&
        stringValue.steeredReads.size() > 1) {
      unsigned shared = circt::hls_analysis::maxStoresInOneIteration(
          stringValue.steeredReads, stringValue.scope);
      stringValue.reads -=
          static_cast<unsigned>(stringValue.steeredReads.size()) - shared;
    }
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
  resultValue.replicable = static_cast<int64_t>(resultValue.maxStoresPerLoop) <=
                           repCfg.maxStoresPerIteration;

  if (!resultValue.replicable && repCfg.userRam1wnrReplicable &&
      llvm::any_of(accesses, [](const AccessSummary &arrayValue) {
        return arrayValue.op && boundRam1wnr(arrayValue.op);
      }))
    resultValue.replicable = true;
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
    lr.copies = std::min(copiesForPortCycles(lr.need), maxReplicationCopies());

    if (stringValue.allReadsVarying && stringValue.writes == 0 &&
        stringValue.ii > 1 && repCfg.rotatingReadsFullCopies) {
      lr.copies =
          std::min<unsigned>(std::max(1u, lr.need), maxReplicationCopies());
      lr.fullCopies = true;
    }

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
    if (rep.copies >= maxReplicationCopies())
      os << "; capped at " << maxReplicationCopies();
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
  else if (kr.kind == StorageKind::RAM_S2P)
    os << ": every read in one pipelined loop, at most one read and one "
          "write per cycle, other loops only write -> "
          "RAM_S2P (a read-only and a write-only port, x"
       << blockDataWidth(kr.kind) << ", simple dual port; N90)";
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

class VitisAutoArchitecture : public circt::hlsest::MemoryArchitecturePolicy {
public:
  StringRef name() const override { return "vitis-auto"; }

  void configure(const Config &cfg,
                 circt::hlsest::ConfigDiagnostics &) override {
    byDemand = cfg.tool.hls.memoryArchitecture.portSetRule == "by_demand";
  }

  /// The configuration that prices a bank of `kind` with peak `demand`:
  /// port_set_rule by_kind takes the port set the kind stands for (Vitis:
  /// ram_2p is narrow whether it serves two reads or a read and a write);
  /// by_demand (a designer knob for other targets) builds it from the demand,
  /// one r per read and one w per write, [rw] for at most one access.
  std::string pricedConfigOf(StorageKind kind, const PortDemand &demand) const {
    const circt::hlsest::MemoryArchitectureConfig &memoryOp =
        config().tool.hls.memoryArchitecture;
    if (!byDemand || kind == StorageKind::RAM_1WNR ||
        kind == StorageKind::ROM_NP)
      return isWideKind(kind) ? memoryOp.pricedWide : memoryOp.pricedNarrow;
    std::vector<std::string> ports;
    if (demand.total <= 1) {
      ports.push_back("rw");
    } else {
      ports.assign(demand.reads, "r");
      ports.insert(ports.end(), demand.writes, "w");
    }
    return memoryOp.isWidePortSet(ports) ? memoryOp.pricedWide
                                         : memoryOp.pricedNarrow;
  }

  void checkDevice(const circt::hlsest::Device &device,
                   circt::hlsest::ConfigDiagnostics &diag) const override {
    const Config &cfg = config();
    const circt::hlsest::DeviceMemory *block =
        device.memory(cfg.tool.backend.memoryMapper.primitive);
    if (!block)
      return;
    const circt::hlsest::MemoryArchitectureConfig &memoryOp =
        cfg.tool.hls.memoryArchitecture;
    for (const std::string *pc : {&memoryOp.pricedWide, &memoryOp.pricedNarrow})
      if (!block->portConfig(*pc))
        diag.errors.push_back("tool.hls.memory_architecture.priced_configs: "
                              "the block memory '" +
                              block->id + "' of device '" + device.id +
                              "' has no port configuration '" + *pc + "'");
  }

  circt::hlsest::PortPools
  capacity(const circt::hlsest::BankStaticProfile *profile,
           const circt::hlsest::DeviceMemory &) const override {
    circt::hlsest::PortPools pools;
    circt::hlsest::PortPool pool;
    pool.suffix = "_rsrc";
    pool.consumes = circt::hlsest::PortPool::Any;
    if (!profile)
      pool.limit = static_cast<unsigned>(
          config().tool.hls.memoryArchitecture.untrackedMemoryPorts);
    else if (profile->registers)
      return pools;
    else if (!profile->pinnedType.empty())
      return pinnedTypePools(profile->pinnedType);
    else if (profile->replicable)
      pool.limit = static_cast<unsigned>(
          config().tool.hls.memoryArchitecture.replicatedSlots());
    else
      pool.limit = blockPorts();
    pools.pools.push_back(pool);
    return pools;
  }

  ReplicationRecord replication(ArrayRef<AccessSummary> accesses,
                                bool attributed) const override {
    return analyzeReplication(accesses, attributed);
  }

  bool pairsSequentialAccesses() const override {
    return config().tool.hls.memoryArchitecture.sequentialScopeModel ==
           "stretch-pair";
  }

  PortDemand sequentialScopeDemand(ArrayRef<const AccessSummary *> group,
                                   SeqScopeIndex &index,
                                   std::string *note) const override {
    return ::sequentialScopeDemand(group, index, note);
  }

  unsigned sequentialRomReads(ArrayRef<const AccessSummary *> group,
                              SeqScopeIndex &index) const override {
    if (!config().tool.hls.memoryArchitecture.rom.sequentialStateReads)
      return 0;
    return ::sequentialRomReadsImpl(group, index);
  }

  circt::hlsest::MemoryPlan
  plan(const PortDemand &demand, ReplicationRecord &rep,
       const circt::hlsest::MemoryRequest &request,
       const circt::hlsest::PlanContext &context) const override {
    const circt::hlsest::MemoryArchitectureConfig &memoryOp =
        config().tool.hls.memoryArchitecture;
    circt::hlsest::MemoryPlan portValue;
    if (request.readOnly)
      return romPlan(demand, rep, memoryOp);

    const bool pinned =
        memoryOp.replication.userPlainRamPinsKind && request.pragmaType &&
        circt::hls_analysis::isPinnedRamType(*request.pragmaType);
    if (pinned &&
        (*request.pragmaType == "ram_s2p" || *request.pragmaType == "ram_1p"))
      return pinnedPlan(demand, rep, *request.pragmaType);
    if (pinned) {
      rep.copies = 1;
      rep.limitingLoop.reset();
      for (ReplicationLoopRecord &lowerIndex : rep.loops)
        lowerIndex.copies = 1;
    }
    KindResult kr;
    bool demandClamped = false;
    if (rep.copies > 1) {

      kr.kind = StorageKind::RAM_1WNR;
      portValue.copies = rep.copies;
      portValue.pricedConfig = memoryOp.pricedNarrow;
    } else {
      PortDemand dimensionIndex = demand;
      const unsigned ports = blockPorts();
      if ((rep.replicable || pinned) && dimensionIndex.total > ports) {

        demandClamped = true;
        dimensionIndex.total = ports;
        dimensionIndex.reads = std::min(dimensionIndex.reads, ports);
        dimensionIndex.writes = std::min(dimensionIndex.writes, ports);
        if (dimensionIndex.reads >= 1 && dimensionIndex.writes >= 1)
          dimensionIndex.reads = dimensionIndex.writes = 1;
      }
      kr = selectStorageKind(dimensionIndex);

      bool oneLoop = context.onePipelinedScope &&
                     kr.kind == StorageKind::RAM_2P &&
                     dimensionIndex.reads == 1 && dimensionIndex.writes == 1;
      bool split =
          context.readWriteSplit &&
          (kr.kind == StorageKind::RAM_2P || kr.kind == StorageKind::RAM_T2P) &&
          dimensionIndex.total <= blockPorts();
      if (memoryOp.oneLoopReadWriteSdp && !demandClamped &&
          (oneLoop || split)) {
        kr.kind = StorageKind::RAM_S2P;
        dimensionIndex.reads = dimensionIndex.writes = 1;
      }

      if (pinned && *request.pragmaType == "ram_2p" &&
          dimensionIndex.reads <= 1 && dimensionIndex.writes <= 1 &&
          !kr.infeasible) {
        kr.kind = StorageKind::RAM_S2P;
        dimensionIndex.reads = dimensionIndex.writes = 1;
      }
      portValue.pricedConfig = pricedConfigOf(kr.kind, dimensionIndex);
    }
    portValue.label = kindName(kr.kind);
    if (pinned && *request.pragmaType == "ram_2p")
      portValue.label = "RAM_2P";
    portValue.infeasible = kr.infeasible;
    portValue.note = kr.note;
    portValue.reason = ramReasonFor(demand, kr, rep, context.attributed,
                                    context.anyStoreEnable, demandClamped);
    if (pinned) {
      rep.replicable = false;
      portValue.reason =
          "bind_storage type=" + *request.pragmaType +
          " pins the kind (N173): no RAM_1WNR copies, the scheduler "
          "keeps two ports and raises the II; " +
          portValue.reason;
    }
    return portValue;
  }

  std::string unpricedLabel(bool readOnly) const override {
    return kindName(readOnly ? StorageKind::ROM_1P : StorageKind::RAM_1P);
  }

private:
  bool byDemand = false;

  /// A bank under a user binding of a plain RAM type (VITIS_NOTES N173):
  /// one memory of that type, no RAM_1WNR copies. ram_s2p has a read-only
  /// and a write-only port, simple dual port (x36 up to 512 words) whatever
  /// the demand (kernels w9r23p_b6 / b8, 512 x 128 read twice: 4); ram_1p is
  /// one port. (ram_2p / ram_t2p take plan's automatic path without copies:
  /// b5, ram_2p read once per cycle, is x36: 4.)
  circt::hlsest::MemoryPlan pinnedPlan(const PortDemand &demand,
                                       ReplicationRecord &rep,
                                       StringRef type) const {
    rep.copies = 1;
    rep.replicable = false;
    rep.limitingLoop.reset();
    for (ReplicationLoopRecord &lowerIndex : rep.loops)
      lowerIndex.copies = 1;
    PortDemand dimensionIndex = demand;
    StorageKind kind;
    if (type == "ram_s2p") {
      kind = StorageKind::RAM_S2P;
      dimensionIndex.reads = dimensionIndex.writes = 1;
      dimensionIndex.total = 2;
    } else {
      kind = StorageKind::RAM_1P;
      dimensionIndex.total = 1;
      dimensionIndex.reads = std::min(dimensionIndex.reads, 1u);
      dimensionIndex.writes = std::min(dimensionIndex.writes, 1u);
    }
    circt::hlsest::MemoryPlan portValue;
    portValue.label = kindName(kind);
    portValue.pricedConfig = pricedConfigOf(kind, dimensionIndex);
    std::string stringValue;
    llvm::raw_string_ostream os(stringValue);
    os << "bind_storage type=" << type
       << " pins the kind (N173): no RAM_1WNR copies, the scheduler keeps "
          "the type's ports and raises the II; peak port demand "
       << demand.total << "/cycle (" << demand.reads << "R+" << demand.writes
       << "W) -> " << kindName(kind) << " (x" << blockDataWidth(kind)
       << (isWideKind(kind) ? ", simple dual port)" : "/port)");
    portValue.reason = stringValue;
    return portValue;
  }

  /// The ports of a user-bound plain RAM type (VITIS_NOTES N173: the
  /// scheduler serialises what the type's ports cannot serve, kernels
  /// w9r23p_b1 ram_s2p II 7, b9 / b10 ram_t2p / ram_2p II 4, b11 ram_1p II 8
  /// for 7 reads and a write per iteration): ram_1p one port, ram_s2p one
  /// read-only and one write-only port, ram_2p / ram_t2p two ports.
  static circt::hlsest::PortPools pinnedTypePools(StringRef type) {
    circt::hlsest::PortPools pools;
    circt::hlsest::PortPool pool;
    if (type == "ram_s2p") {
      pool.suffix = "_rd";
      pool.consumes = circt::hlsest::PortPool::Read;
      pool.limit = 1;
      pools.pools.push_back(pool);
      pool.suffix = "_wr";
      pool.consumes = circt::hlsest::PortPool::Write;
      pools.pools.push_back(pool);
      return pools;
    }
    pool.suffix = "_rsrc";
    pool.consumes = circt::hlsest::PortPool::Any;
    pool.limit = type == "ram_1p" ? 1u : blockPorts();
    pools.pools.push_back(pool);

    if (type == "ram_2p") {
      pool.suffix = "_wr";
      pool.consumes = circt::hlsest::PortPool::Write;
      pool.limit = 1;
      pools.pools.push_back(pool);
    }
    return pools;
  }

  /// A ROM read at most rom.sdp_max_reads (2) times per cycle is one memory
  /// (ROM_1P / ROM_2P, read-only ports are simple dual port: x36); more
  /// reads need rom.copies copies (ceil(n/2), ROM_NP, x18), capped at
  /// max_copies (N8 (b)/(c)). n = the peak reads per cycle of the schedule,
  /// at least ceil(R / II) of every pipelined loop.
  circt::hlsest::MemoryPlan
  romPlan(const PortDemand &demand, ReplicationRecord &rep,
          const circt::hlsest::MemoryArchitectureConfig &memoryOp) const {
    const circt::hlsest::RomConfig &romCfg = memoryOp.rom;
    const unsigned sdpMaxReads = static_cast<unsigned>(romCfg.sdpMaxReads);
    auto romCopies = [&](unsigned reads) {
      unsigned candidateValue = romCfg.copies == "n_minus_1"
                                    ? reads - 1
                                    : static_cast<unsigned>(ceilDiv(reads, 2));
      return std::min<unsigned>(std::max(candidateValue, 1u),
                                maxReplicationCopies());
    };
    unsigned n = std::max(demand.total, 1u);
    for (ReplicationLoopRecord &lowerIndex : rep.loops) {
      n = std::max(n, lowerIndex.need);

      lowerIndex.copies =
          lowerIndex.need <= sdpMaxReads ? 1u : romCopies(lowerIndex.need);
    }
    rep.replicable = true;
    rep.copies = 1;
    rep.limitingLoop.reset();
    circt::hlsest::MemoryPlan portValue;
    StorageKind kind;
    if (n <= sdpMaxReads) {
      kind = n <= 1 ? StorageKind::ROM_1P : StorageKind::ROM_2P;
      PortDemand reads;
      reads.reads = reads.total = n;
      portValue.pricedConfig = pricedConfigOf(kind, reads);
    } else {
      kind = StorageKind::ROM_NP;
      rep.copies = romCopies(n);
      portValue.copies = rep.copies;
      portValue.pricedConfig = memoryOp.pricedNarrow;
    }
    portValue.label = kindName(kind);
    portValue.rom = true;
    portValue.romReads = n;
    portValue.reason =
        ": peak " + std::to_string(n) + " read(s) per cycle -> " +
        kindName(kind) +
        (n <= sdpMaxReads
             ? ": read-only ports are simple dual port, x" +
                   std::to_string(maxPortWidth(true)) + " allowed (N8)"
             : ", " + std::to_string(rep.copies) + " copies = " +
                   (romCfg.copies == "n_minus_1" ? "n-1" : "ceil(n/2)") +
                   " at x" + std::to_string(maxPortWidth(false)) +
                   " (N8 (c) ROM_nP: fr_rom3r / fr_rom4r, aes sbox, gsm "
                   "bitoff)");
    return portValue;
  }
};

} // namespace

void circt::hlsest::builtin::registerMemoryArchitecturePolicies() {
  PluginRegistry<MemoryArchitecturePolicy>::instance().add(
      "vitis-auto",
      "Vitis HLS automatic storage: 2-port RAM, RAM_1WNR replication, ROMs, "
      "same-state pairs in sequential scopes (VITIS_NOTES N4, N6, N8, N12)",
      [] { return std::make_unique<VitisAutoArchitecture>(); }, "builtin");
}
