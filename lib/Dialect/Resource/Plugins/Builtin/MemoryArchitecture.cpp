//===- MemoryArchitecture.cpp - The builtin memory architecture policy ----===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// vitis-auto: how Vitis HLS 2025.1 builds the memory of an automatic array
// (td=off), as a MemoryArchitecturePolicy:
//
//   capacity    the port slots the modulo scheduler may use per cycle: a bank
//               no loop body stores to more than max_stores_per_iteration
//               (1) times can be replicated, max_copies x (ports - 1) + 1 =
//               17 read-or-write slots (VITIS_NOTES N4); any other bank, and
//               an interface array, the two ports of one block RAM;
//   replication RAM_1WNR copies = max(1, ceil((R + W) / II) - 1), capped at
//               max_copies, max over the pipelined loops (N4);
//   sequential  two independent accesses of one straight-line stretch of a
//   scopes      non-pipelined scope share a state (N12; stretch-pair), or one
//               access per state (one-port);
//   plan        the storage kind from the per-cycle demand (ram_1p, ram_2p,
//               ram_t2p; never ram_s2p without a pragma), a ROM's kind from
//               its reads (rom.sdp_max_reads), and the port configuration
//               that prices the bank: the kinds whose port set is in
//               wide_port_sets (one port; a read and a write port; one or two
//               read-only ports) at priced_configs.wide (sdp: x36), the rest
//               and every replicated copy at priced_configs.narrow (tdp:
//               x18) (N6, N8).
//
// The storage kind names (RAM_1P, ...) are this policy's report labels; no
// interface carries them. (Moved from BRAMAnalysis.cpp, P2.)
//
//===----------------------------------------------------------------------===//

#include "Builtins.h"

#include "circt/Dialect/LoopSchedule/LoopScheduleOps.h"
#include "circt/Dialect/Resource/Model/AccessOrder.h"
#include "circt/Dialect/Resource/Passes/MemrefBankClassification.h"
#include "circt/Dialect/Resource/Plugins/MemoryInterfaces.h"
#include "circt/Dialect/Resource/Plugins/Registry.h"

#include "mlir/IR/BuiltinTypes.h"
#include "mlir/Interfaces/LoopLikeInterface.h"
#include "llvm/ADT/BitVector.h"
#include "llvm/ADT/DenseSet.h"
#include "llvm/Support/raw_ostream.h"

#include <map>

using namespace mlir;
using namespace circt::hls_analysis;
using circt::hlsest::Config;
using circt::loopschedule::LoopSchedulePipelineOp;

namespace {

const Config &config() { return Config::get(); }

int64_t ceilDiv(int64_t a, int64_t b) { return (a + b - 1) / b; }

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

//===----------------------------------------------------------------------===//
// Sequential scopes: accesses per state (--bram-seq-dual-port, on by default
// since MEMOS.md M6; VITIS_NOTES.md N12, OPEN_ISSUES.md O3).
//===----------------------------------------------------------------------===//
// Vitis schedules a non-pipelined region with the same 2-port RAM core it uses
// in a pipeline (`Core .. 'RAM' .. <Ports = 2>` in *.verbose.sched.rpt), puts
// up to two accesses of one array in one state, and the binder makes the array
// ram_2p (two reads, or a read and a write) / ram_t2p (two writes), x18
// columns, as soon as one state holds two (polybench atax: the 64 invariant
// buff_x loads hoisted into the parent issue two per state, buff_x_U ram_2p =
// 2). Kernels (~/hls-est-work/exp-src/seqports*, 33 runs; t6rev, 6 runs): two
// accesses share a state when they lie in one straight-line stretch of the
// scope and neither depends on the other:
//   - stretch: the scope's block up to the next loop / pipeline / other
//     region op. That boundary is confirmed only where the later access feeds
//     something ordered after the loop (sp_split_loop, rv_sib3: 1); Vitis
//     outlines a pipelined inner loop as a call and can start an independent
//     second loop beside it, loading for both in one state (rv_sib2: 2, this
//     model 1 - an under-estimate, OPEN_ISSUES.md O21).
//     The arms of an if belong to the stretch (Vitis predicates them: sp_if
//     2), but the two arms of one if never pair (sp_o_ifarms, sp_o_ifst 1),
//     also after --convert-affine-to-loopschedule hoisted them in front of the
//     if (the arm is kept in hls.if_arms).
//   - dependence: an SSA chain from one access to the other (sp_dd 1, a
//     read-modify-write 1), a store ordered against a may-alias access
//     (sp_stld_alias 1), or a memory order through another array (a value
//     stored to b and read back from b feeds the second address: rv_memdep,
//     rv_memdep2 1); provably disjoint addresses do not order
//     (sp_stld / sp_ldst 2). Two loads of one address are one load (GVN).
//   - the ASAP distance does not matter for two loads (sp_far: 38 cycles
//     apart, still one state), and a state never holds more than two
//     (sp_8ld: 8 loads -> four states of two, ram_2p, no RAM_1WNR).
// Over-estimates (Vitis spread the two over the slack of the stretch: 1 port
// where this says 2): sp_stfar, sp_o_2st, sp_o_far2, sp_o_2ld_rmw
// (OPEN_ISSUES.md O21).



// The accesses (indices into the access list of one stretch, in program
// order) an operation depends on: every index below `prefix`, plus the set
// bits of `tail` at or above it. Dependences in a stretch mostly form chains
// (each access ordered after all earlier ones), which this keeps at constant
// size; one k-bit vector per operation of the stretch was quadratic in time
// and memory (hlsyn gemm-blocked: 131k accesses of one bank in one stretch,
// over 600 s and 4.6 GB; OPEN_ISSUES O103 (2)). The sets it describes are
// exactly those of the bit vectors it replaced.
class DepSet {
public:
  bool test(unsigned i) const {
    return i < prefix || (i < tail.size() && tail.test(i));
  }
  bool any() const { return prefix > 0 || firstTailBit(0) >= 0; }
  /// Every index below this is in the set.
  unsigned prefixSize() const { return prefix; }
  void set(unsigned i) {
    if (i < prefix)
      return;
    if (i >= tail.size())
      tail.resize(i + 1);
    tail.set(i);
    normalize();
  }
  /// Adds every index below `n`.
  void setPrefix(unsigned n) {
    if (n <= prefix)
      return;
    prefix = n;
    normalize();
  }
  DepSet &operator|=(const DepSet &o) {
    prefix = std::max(prefix, o.prefix);
    if (o.firstTailBit(prefix) >= 0) {
      if (tail.size() < o.tail.size())
        tail.resize(o.tail.size());
      tail |= o.tail;
    }
    normalize();
    return *this;
  }
  /// Whether some index of this set is missing from `o` (BitVector::test).
  bool hasIndexNotIn(const DepSet &o) const {
    if (prefix > o.prefix)
      return true; // o.prefix itself is not in o (normalized)
    for (int b = firstTailBit(o.prefix); b >= 0;
         b = tail.find_next(static_cast<unsigned>(b)))
      if (!o.test(static_cast<unsigned>(b)))
        return true;
    return false;
  }
  /// The smallest index >= `from` that is not in the set.
  unsigned nextUnset(unsigned from) const {
    from = std::max(from, prefix);
    if (from >= tail.size())
      return from;
    int u = tail.find_first_unset_in(from, tail.size());
    return u < 0 ? static_cast<unsigned>(tail.size()) : static_cast<unsigned>(u);
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
      int u = tail.find_first_unset_in(prefix, tail.size());
      prefix = u < 0 ? static_cast<unsigned>(tail.size())
                     : static_cast<unsigned>(u);
    }
    if (!tail.empty() && firstTailBit(prefix) < 0)
      tail = llvm::BitVector();
  }
};

// Two accesses of `accs` (one bank, one stretch of a sequential scope, in
// program order) that Vitis issues in the same state, or none.
static std::optional<std::pair<const AccessSummary *, const AccessSummary *>>
findSameStatePair(ArrayRef<const AccessSummary *> accs,
                  const SeqScopeIndex::Scope &s, unsigned stretch,
                  const DenseSet<Value> &bankValues) {
  unsigned k = accs.size();
  const std::vector<Operation *> &ops = s.stretches[stretch];
  SmallVector<unsigned> ord(k);
  SmallVector<const SeqScopeIndex::OpInfo *> info(k);
  DenseMap<Operation *, unsigned> accIdx;
  for (unsigned j = 0; j < k; ++j) {
    info[j] = &s.info.find(accs[j]->op)->second;
    ord[j] = info[j]->ordinal;
    accIdx[accs[j]->op] = j;
  }
  unsigned lo = ord.front(), hi = ord.back();
  // deps[p - lo]: the accesses (indices into accs) the op at ordinal p
  // depends on, through SSA values or memory order. Invariant: an access in
  // a set brings its own dependences along (i in d implies deps[i] in d), so
  // an access already in d never needs to be looked at again.
  std::vector<DepSet> deps(hi - lo + 1);
  // Every access before the last other use of the bank (a prefix: accs is
  // in program order).
  unsigned barrier = 0;
  // The arms an access was hoisted out of by --convert-affine-to-loopschedule
  // (hls.if_arms: [if id, arm, ...]).
  SmallVector<ArrayRef<int64_t>> hoistedArms(k);
  for (unsigned j = 0; j < k; ++j)
    hoistedArms[j] = hoistedArmsOf(accs[j]->op);
  auto exclusive = [&](unsigned i, unsigned j) {
    return inExclusiveArms(*info[i], hoistedArms[i], *info[j], hoistedArms[j]);
  };
  // The ops of [lo, p) with memory effects whose order can carry an access of
  // `accs`: the accesses themselves and the ops that depend on one. A later op
  // whose effects may conflict with one of them inherits its dependences, so
  // the memory order through any storage counts (x = a[i]; b[j] = x;
  // y = b[k]; a[y]: rv_memdep, VITIS_NOTES.md N12). An op that depends on no
  // access never carries one and is left out.
  struct MemEvent {
    Operation *op;
    unsigned pos;
    int acc; // index into accs, -1 for another op
    SmallVector<MemTouch, 2> touches;
  };
  std::vector<MemEvent> events;
  SmallVector<MemTouch, 2> touches;
  // Events per storage key, and those touching any storage (a null key); an
  // access of `accs` inherits nothing from another access of `accs` (they
  // are ordered by their addresses below), so the events that are not
  // accesses are also indexed on their own.
  struct EventIndex {
    DenseMap<const void *, SmallVector<unsigned>> byKey;
    SmallVector<unsigned> anyStorage, all;
    void add(unsigned ei, ArrayRef<MemTouch> touches) {
      all.push_back(ei);
      if (llvm::any_of(touches,
                       [](const MemTouch &t) { return t.key == nullptr; }))
        anyStorage.push_back(ei);
      for (const MemTouch &t : touches)
        if (t.key) {
          SmallVector<unsigned> &ids = byKey[t.key];
          if (ids.empty() || ids.back() != ei)
            ids.push_back(ei);
        }
    }
  };
  EventIndex allEvents, otherEvents;
  SmallVector<unsigned> candidates;
  SmallVector<unsigned> seenStamp; // per event: the op that listed it last
  unsigned stamp = 0;
  for (unsigned p = lo; p <= hi; ++p) {
    Operation *op = ops[p];
    DepSet &d = deps[p - lo];
    auto addValue = [&](Value v) {
      Operation *def = v.getDefiningOp();
      if (!def)
        return;
      auto it = s.info.find(def);
      if (it == s.info.end() || it->second.stretch != stretch ||
          it->second.ordinal < lo || it->second.ordinal >= p)
        return; // defined before the first access or elsewhere
      d |= deps[it->second.ordinal - lo];
      auto ai = accIdx.find(def);
      if (ai != accIdx.end())
        d.set(ai->second);
    };
    for (Value v : op->getOperands())
      addValue(v);
    for (Region &region : op->getRegions()) // an if: results from its arms
      for (Block &block : region)
        if (!block.empty())
          for (Value v : block.back().getOperands())
            addValue(v);
    auto self = accIdx.find(op);
    int selfAcc = self == accIdx.end() ? -1 : static_cast<int>(self->second);
    // Memory order against the earlier ops of the stretch (two accesses of the
    // bank are ordered below, by their addresses).
    touches.clear();
    memTouches(op, touches);
    const EventIndex &index = selfAcc >= 0 ? otherEvents : allEvents;
    if (!touches.empty() && !index.all.empty()) {
      const SeqScopeIndex::OpInfo &opInfo = s.info.find(op)->second;
      ArrayRef<int64_t> opHoisted = hoistedArmsOf(op);
      // Only events that can conflict with a touch of op: the same storage,
      // or any storage (a null key) on either side (mayConflict). What d
      // inherits is a union, so the order of the events does not matter.
      // (Speed only: the scan over every earlier event was quadratic in the
      // stretch, barry_walker lab_2.)
      candidates.clear();
      bool anyStorage = llvm::any_of(
          touches, [](const MemTouch &t) { return t.key == nullptr; });
      if (anyStorage) {
        candidates.append(index.all.begin(), index.all.end());
      } else {
        ++stamp;
        auto add = [&](ArrayRef<unsigned> ids) {
          for (unsigned ei : ids)
            if (seenStamp[ei] != stamp) {
              seenStamp[ei] = stamp;
              candidates.push_back(ei);
            }
        };
        add(index.anyStorage);
        for (const MemTouch &t : touches) {
          auto it = index.byKey.find(t.key);
          if (it != index.byKey.end())
            add(it->second);
        }
      }
      for (unsigned ei : candidates) {
        const MemEvent &e = events[ei];
        const DepSet &ed = deps[e.pos - lo];
        if (!ed.hasIndexNotIn(d) && !(e.acc >= 0 && !d.test(e.acc)))
          continue; // nothing to inherit
        if (inExclusiveArms(s.info.find(e.op)->second, hoistedArmsOf(e.op),
                            opInfo, opHoisted))
          continue;
        bool conflict = llvm::any_of(e.touches, [&](const MemTouch &a) {
          return llvm::any_of(touches, [&](const MemTouch &b) {
            return mayConflict(e.op, a, op, b);
          });
        });
        if (!conflict)
          continue;
        d |= ed;
        if (e.acc >= 0)
          d.set(e.acc);
      }
    }
    if (!touches.empty() && (selfAcc >= 0 || d.any())) {
      unsigned ei = events.size();
      events.push_back({op, p, selfAcc, touches});
      seenStamp.push_back(0);
      allEvents.add(ei, touches);
      if (selfAcc < 0)
        otherEvents.add(ei, touches);
    }
    if (selfAcc < 0) {
      // Another use of the bank (a call, a view): every access after it is
      // ordered after every access before it.
      if (llvm::any_of(op->getOperands(),
                       [&](Value v) { return bankValues.contains(v); }))
        barrier = std::max<unsigned>(
            barrier, static_cast<unsigned>(llvm::lower_bound(ord, p) -
                                           ord.begin()));
      continue;
    }
    unsigned j = self->second;
    d.setPrefix(barrier);
    // The earlier accesses this one is ordered after by address. Latest
    // first: the set is a union, and an access already in it (with its own
    // dependences) adds nothing, so a chain is settled by its last link.
    for (unsigned i = j; i-- > d.prefixSize();) {
      if (d.test(i) || exclusive(i, j) ||
          !(accs[i]->isWrite || accs[j]->isWrite))
        continue;
      if (compareAddresses(accs[i]->op, op) != AddrRelation::Disjoint) {
        d.set(i);
        d |= deps[ord[i] - lo];
      }
    }
    for (unsigned i = d.nextUnset(0); i < j; i = d.nextUnset(i + 1)) {
      if (exclusive(i, j))
        continue;
      if (!accs[i]->isWrite && !accs[j]->isWrite &&
          compareAddresses(accs[i]->op, op) == AddrRelation::Same)
        continue; // one load after GVN
      return std::make_pair(accs[i], accs[j]);
    }
  }
  return std::nullopt;
}


// Per-state demand of a sequential scope: one access per state unless two of
// them share one (findSameStatePair); never more than two.
static PortDemand sequentialScopeDemand(ArrayRef<const AccessSummary *> group,
                                        SeqScopeIndex &index,
                                        std::string *note) {
  PortDemand d;
  bool anyR = false, anyW = false;
  for (const auto *a : group)
    (a->isWrite ? anyW : anyR) = true;
  d.reads = anyR ? 1u : 0u;
  d.writes = anyW ? 1u : 0u;
  d.total = (anyR || anyW) ? 1u : 0u;
  Operation *scope = group.front()->scope;
  if (!scope || group.size() < 2)
    return d;
  const SeqScopeIndex::Scope &s = index.get(scope);
  std::map<unsigned, SmallVector<const AccessSummary *>> byStretch;
  for (const auto *a : group) {
    auto it = s.info.find(a->op);
    if (it != s.info.end()) // else under a region op that is not an if: alone
      byStretch[it->second.stretch].push_back(a);
  }
  DenseSet<Value> bankValues;
  for (const auto *a : group)
    for (Value v : a->op->getOperands())
      if (isa<BaseMemRefType>(v.getType()))
        bankValues.insert(v);
  for (auto &[stretch, accs] : byStretch) {
    if (accs.size() < 2)
      continue;
    llvm::sort(accs, [&](const AccessSummary *x, const AccessSummary *y) {
      return s.info.find(x->op)->second.ordinal <
             s.info.find(y->op)->second.ordinal;
    });
    auto pair = findSameStatePair(accs, s, stretch, bankValues);
    if (!pair)
      continue;
    bool w1 = pair->first->isWrite, w2 = pair->second->isWrite;
    d.total = 2;
    if (!w1 && !w2)
      d.reads = 2;
    else if (w1 && w2)
      d.writes = 2;
    if (note)
      *note = "same state (independent, one straight-line stretch): " +
              accessText(pair->first) + " + " + accessText(pair->second);
    return d;
  }
  return d;
}

//===----------------------------------------------------------------------===//
// Kind naming (declared early; used in notes).
//===----------------------------------------------------------------------===//
static const char *kindName(StorageKind k) {
  switch (k) {
  case StorageKind::RAM_1P:   return "RAM_1P";
  case StorageKind::RAM_2P:   return "RAM_2P";
  case StorageKind::RAM_S2P:  return "RAM_S2P";
  case StorageKind::RAM_T2P:  return "RAM_T2P";
  case StorageKind::RAM_1WNR: return "RAM_1WNR";
  case StorageKind::LUTRAM:   return "LUTRAM";
  case StorageKind::URAM:     return "URAM";
  case StorageKind::ROM_1P:   return "ROM_1P";
  case StorageKind::ROM_2P:   return "ROM_2P";
  case StorageKind::ROM_NP:   return "ROM_NP";
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
// an explicit bind_storage pragma does. Two live ports are ram_2p (port A
// read / write, port B read) unless two writes share a cycle, which needs
// ram_t2p: Vitis binds ram_2p for two reads per state (N12 sp_far / sp_8ld;
// td=off corpus: polybench atax buff_x, mvt buff_y1, polybench_pragmas mvt
// buff_A, k2mm buff_B) and ram_t2p for two stores (sp_2st). Both are x18 per
// port, so the BRAM count does not depend on which of the two it is.
static KindResult selectStorageKind(const PortDemand &d) {
  KindResult r;
  unsigned total = d.total, w = d.writes, rd = d.reads;
  const unsigned ports = blockPorts(); // 2: one block RAM

  if (total <= 1) {
    r.kind = StorageKind::RAM_1P;          // one live port, wide x36
    return r;
  }
  if (total <= ports) {
    r.kind = w >= 2 ? StorageKind::RAM_T2P : StorageKind::RAM_2P;
    return r;
  }

  r.kind = StorageKind::RAM_T2P;
  r.infeasible = true;
  r.note = "port demand " + std::to_string(total) + "/cycle (" +
           std::to_string(rd) + "R+" + std::to_string(w) +
           "W, multi-writer) exceeds " + std::to_string(ports) +
           " ports; needs array_partition.";
  return r;
}

//===----------------------------------------------------------------------===//
// Width-aware block count.
//===----------------------------------------------------------------------===//
// Whether the bank is simple dual port (SDP), so a block may use the x36
// aspect ratio (both ports ganged). Vitis decides it on the ports the binder
// used (VITIS_NOTES.md N8 (b)/(d)): SDP = one used port, or one write-only +
// one read-only port, or two read-only ports; anything else (a read-write
// port next to a read port, two read-write ports, more than two ports) caps
// each port at x18. The kinds stand for these port sets: RAM_1P one port;
// RAM_S2P write-only + read-only; ROM_1P / ROM_2P one / two read-only ports;
// RAM_2P read-write + read (what Vitis binds for two accesses per cycle of an
// automatic RAM: the N6 corpus, 13379 of 13421 rows with a port vector);
// RAM_T2P two read-write ports; RAM_1WNR / ROM_NP more than two.
/// The port set each kind stands for (tool.hls.memory_architecture.
/// port_set_rule = by_kind); empty for a kind with more than two ports
/// (RAM_1WNR, ROM_NP: every copy is priced narrow) or no block RAM at all.
static std::vector<std::string> kindPortSet(StorageKind k) {
  switch (k) {
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

static bool isWideKind(StorageKind k) {
  // A kind is wide when its port set is one of the profile's wide port sets
  // (Vitis: one port, a read-only and a write-only port, one or two
  // read-only ports; tool.hls.memory_architecture.wide_port_sets).
  std::vector<std::string> ports = kindPortSet(k);
  return !ports.empty() &&
         config().tool.hls.memoryArchitecture.isWidePortSet(ports);
}

// Widest aspect-ratio mode (data bits per port) the kind allows.
static unsigned blockDataWidth(StorageKind k) {
  if (k == StorageKind::LUTRAM || k == StorageKind::URAM)
    return 0; // not mapped to BRAM
  return maxPortWidth(isWideKind(k));
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
/// Copies of a replicated bank that give `need` port-cycles per cycle: every
/// copy adds its ports but the shared write port (port B of a true-dual-port
/// block reads), and the shared write port reads when idle
/// (tool.hls.memory_architecture.replication.shared_write_port_reads_when_idle):
/// need - 1 for Vitis. At least 1.
static unsigned copiesForPortCycles(unsigned need) {
  const bool idleReads = config()
                             .tool.hls.memoryArchitecture.replication
                             .sharedWritePortReadsWhenIdle;
  const unsigned perCopy = std::max(1u, blockPorts() - 1);
  unsigned shared = idleReads ? 1u : 0u;
  if (need <= shared)
    return 1;
  return std::max<unsigned>(
      1, static_cast<unsigned>(ceilDiv(need - shared, perCopy)));
}

static ReplicationRecord analyzeReplication(ArrayRef<AccessSummary> accesses,
                                            bool attributed) {
  ReplicationRecord r;
  r.present = attributed;
  if (!attributed)
    return r;

  struct ScopeStats {
    Operation *scope = nullptr;
    unsigned reads = 0, writes = 0, ii = 0;
    bool portBound = false; // reached through a shared module (N14 R6)
    SmallVector<Operation *> stores;
  };
  SmallVector<ScopeStats> scopes; // first-appearance order (deterministic)
  for (const AccessSummary &a : accesses) {
    ScopeStats *st = nullptr;
    for (ScopeStats &s : scopes)
      if (s.scope == a.scope)
        st = &s;
    if (!st) {
      scopes.push_back({a.scope, 0, 0, a.ii, false});
      st = &scopes.back();
    }
    (a.isWrite ? st->writes : st->reads)++;
    if (a.isWrite && a.op)
      st->stores.push_back(a.op);
    st->portBound |= a.portBound;
  }
  // Stores in the two arms of one if share the write port: they count once
  // (both for replicability and for the port-cycles of the loop).
  for (ScopeStats &s : scopes)
    if (s.scope && s.stores.size() == s.writes && s.writes > 1)
      s.writes = circt::hls_analysis::maxStoresInOneIteration(s.stores, s.scope);

  r.maxStoresPerLoop = 0;
  for (const ScopeStats &s : scopes) {
    bool isLoopBody = s.scope && (isa<LoopSchedulePipelineOp>(s.scope) ||
                                  isa<LoopLikeOpInterface>(s.scope));
    if (isLoopBody)
      r.maxStoresPerLoop = std::max(r.maxStoresPerLoop, s.writes);
  }
  const circt::hlsest::ReplicationConfig &repCfg =
      config().tool.hls.memoryArchitecture.replication;
  r.replicable =
      static_cast<int64_t>(r.maxStoresPerLoop) <= repCfg.maxStoresPerIteration;
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
    lr.copies = std::min(copiesForPortCycles(lr.need), maxReplicationCopies());
    // A loop of a callee instantiated at more than one place reads the
    // caller's bank through the module's two ports (N14 R6, W3 review D2:
    // w3rev_k3 / k3b, w3fx_d2_conc: no replication, the loop's II rises).
    if (s.portBound) {
      lr.portBound = true;
      lr.copies = 1;
      r.portBoundLimited |= lr.need > 2;
    }
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
    if (rep.copies >= maxReplicationCopies())
      os << "; capped at " << maxReplicationCopies();
    os << "); each copy is a true-dual-port RAM (x18/port)";
    return s;
  }
  os << "peak port demand " << d.total << "/cycle (" << d.reads << "R+"
     << d.writes << "W, max over scopes)";
  if (kr.infeasible) {
    os << ": " << kr.note;
    return s;
  }
  if (demandClamped && rep.portBoundLimited)
    os << ", clamped to 2 ports (a callee instantiated at more than one "
          "place reads it through the module's ports: no replication across "
          "the call, Vitis raises that loop's II instead; N14 R6)";
  else if (demandClamped)
    os << ", clamped to 2 ports (replicable bank, but no pipelined loop needs "
          "more than ceil((R+W)/II) <= 2 port-cycles, so Vitis spreads the "
          "accesses over the II)";
  if (d.total <= 1 && !demandClamped)
    os << ": at most one live port -> " << kindName(kr.kind) << " (x"
       << blockDataWidth(kr.kind) << " wide, no TDP constraint)";
  else if (kr.kind == StorageKind::RAM_S2P)
    os << ": every read in one pipelined loop, at most one read and one "
          "write per cycle, other loops only write -> "
          "RAM_S2P (a read-only and a write-only port, x"
       << blockDataWidth(kr.kind) << ", simple dual port; N90)";
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
    const circt::hlsest::MemoryArchitectureConfig &m =
        config().tool.hls.memoryArchitecture;
    if (!byDemand || kind == StorageKind::RAM_1WNR ||
        kind == StorageKind::ROM_NP)
      return isWideKind(kind) ? m.pricedWide : m.pricedNarrow;
    std::vector<std::string> ports;
    if (demand.total <= 1) {
      ports.push_back("rw");
    } else {
      ports.assign(demand.reads, "r");
      ports.insert(ports.end(), demand.writes, "w");
    }
    return m.isWidePortSet(ports) ? m.pricedWide : m.pricedNarrow;
  }

  void checkDevice(const circt::hlsest::Device &device,
                   circt::hlsest::ConfigDiagnostics &diag) const override {
    const Config &cfg = config();
    const circt::hlsest::DeviceMemory *block =
        device.memory(cfg.tool.backend.memoryMapper.primitive);
    if (!block)
      return; // the mapper check names the missing primitive
    const circt::hlsest::MemoryArchitectureConfig &m =
        cfg.tool.hls.memoryArchitecture;
    for (const std::string *pc : {&m.pricedWide, &m.pricedNarrow})
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
      return pools; // no memory: no port limit
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

  circt::hlsest::MemoryPlan
  plan(const PortDemand &demand, ReplicationRecord &rep,
       const circt::hlsest::MemoryRequest &request,
       const circt::hlsest::PlanContext &ctx) const override {
    const circt::hlsest::MemoryArchitectureConfig &m =
        config().tool.hls.memoryArchitecture;
    circt::hlsest::MemoryPlan p;
    if (request.readOnly)
      return romPlan(demand, rep, m);
    KindResult kr;
    bool demandClamped = false;
    if (rep.copies > 1) {
      // RAM_1WNR: `copies` true-dual-port RAMs holding identical data.
      kr.kind = StorageKind::RAM_1WNR;
      p.copies = rep.copies;
      p.pricedConfig = m.pricedNarrow;
    } else {
      PortDemand d = demand;
      const unsigned ports = blockPorts();
      if (rep.replicable && d.total > ports) {
        // The scheduler grants a replicable bank 17 slots per cycle, so it
        // may pack more than two accesses into one cycle even when
        // ceil((R+W)/II) <= 2 (the II was raised by something else). Vitis
        // then spreads them over the II on the two ports of one plain RAM.
        demandClamped = true;
        d.total = ports;
        d.reads = std::min(d.reads, ports);
        d.writes = std::min(d.writes, ports);
        if (d.reads >= 1 && d.writes >= 1)
          d.reads = d.writes = 1;
      }
      kr = selectStorageKind(d);
      // VITIS_NOTES N90 (c): one pipelined loop with one read and one
      // write per cycle and no other access, or one read per iteration of
      // one pipelined loop, at most one write per cycle once spread over its
      // II, and loops that only write: a read-only and a write-only port.
      bool oneLoop = ctx.onePipelinedScope && kr.kind == StorageKind::RAM_2P &&
                     d.reads == 1 && d.writes == 1;
      bool split = ctx.readWriteSplit &&
                   (kr.kind == StorageKind::RAM_2P ||
                    kr.kind == StorageKind::RAM_T2P) &&
                   d.total <= blockPorts();
      if (m.oneLoopReadWriteSdp && !demandClamped && (oneLoop || split)) {
        kr.kind = StorageKind::RAM_S2P;
        d.reads = d.writes = 1;
      }
      p.pricedConfig = pricedConfigOf(kr.kind, d);
    }
    p.label = kindName(kr.kind);
    p.infeasible = kr.infeasible;
    p.note = kr.note;
    p.reason = ramReasonFor(demand, kr, rep, ctx.attributed,
                            ctx.anyStoreEnable, demandClamped);
    return p;
  }

  std::string unpricedLabel(bool readOnly) const override {
    return kindName(readOnly ? StorageKind::ROM_1P : StorageKind::RAM_1P);
  }

private:
  bool byDemand = false;

  /// A ROM read at most rom.sdp_max_reads (2) times per cycle is one memory
  /// (ROM_1P / ROM_2P, read-only ports are simple dual port: x36); more
  /// reads need rom.copies copies (ceil(n/2), ROM_NP, x18), capped at
  /// max_copies (N8 (b)/(c)). n = the peak reads per cycle of the schedule,
  /// at least ceil(R / II) of every pipelined loop.
  circt::hlsest::MemoryPlan
  romPlan(const PortDemand &demand, ReplicationRecord &rep,
          const circt::hlsest::MemoryArchitectureConfig &m) const {
    const circt::hlsest::RomConfig &romCfg = m.rom;
    const unsigned sdpMaxReads = static_cast<unsigned>(romCfg.sdpMaxReads);
    auto romCopies = [&](unsigned reads) {
      unsigned c = romCfg.copies == "n_minus_1"
                       ? reads - 1
                       : static_cast<unsigned>(ceilDiv(reads, 2));
      return std::min<unsigned>(std::max(c, 1u), maxReplicationCopies());
    };
    unsigned n = std::max(demand.total, 1u);
    for (ReplicationLoopRecord &l : rep.loops) {
      n = std::max(n, l.need);
      // What the loop alone would need of a ROM (debug record only): one
      // ROM up to two reads per cycle, else ceil(need / 2) (ROM_NP).
      l.copies = l.need <= sdpMaxReads ? 1u : romCopies(l.need);
    }
    rep.replicable = true;
    rep.copies = 1;
    rep.limitingLoop.reset();
    circt::hlsest::MemoryPlan p;
    StorageKind kind;
    if (n <= sdpMaxReads) {
      kind = n <= 1 ? StorageKind::ROM_1P : StorageKind::ROM_2P;
      PortDemand reads;
      reads.reads = reads.total = n;
      p.pricedConfig = pricedConfigOf(kind, reads);
    } else {
      kind = StorageKind::ROM_NP;
      rep.copies = romCopies(n);
      p.copies = rep.copies;
      p.pricedConfig = m.pricedNarrow;
    }
    p.label = kindName(kind);
    p.rom = true;
    p.romReads = n;
    p.reason =
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
    return p;
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
