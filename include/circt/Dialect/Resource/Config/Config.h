//===- Config.h - hls-est configuration: device, tool profile, run -*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// The designer's configuration of hls-est (hls-doc/configuration.md, design
// memo hls-doc/design/configuration-and-plugins.md). One JSON document with
// these sections:
//
//   run         which device, which tool profile, which clock
//   device      what the silicon offers, as data with a data-sheet source:
//               resource classes, memory primitives (geometries, port
//               configurations), shift registers, arithmetic blocks
//   tool        the tool profile: what the modelled HLS tool decides
//               (tool.hls), what the memory mapping back end decides
//               (tool.backend), the report format and the default pipeline
//   scheduling  operator timing, dependences, the schedulers, binding
//   frontend    what the MLIR input is assumed to look like
//   plugins     free-form sections owned by external plugins
//
// The compiled-in defaults are the AMD xc7z020clg400-1 device and the Vitis
// HLS 2025.1 profile (td=off ground truth); they reproduce the estimates of
// hls-est before the configuration existed byte for byte. A file given with
// --hls-config overrides keys of the defaults, --config-set overrides single
// keys, and a pass option given explicitly on the command line overrides the
// configuration (Config::get() is the merged result).
//
// The structs below are plain data filled by the loader (Loader.cpp), so that
// passes and plugins read typed values and never touch JSON.
//
//===----------------------------------------------------------------------===//

#ifndef CIRCT_DIALECT_RESOURCE_CONFIG_CONFIG_H
#define CIRCT_DIALECT_RESOURCE_CONFIG_CONFIG_H

#include "llvm/ADT/ArrayRef.h"
#include "llvm/ADT/StringRef.h"
#include "llvm/Support/JSON.h"

#include <cstdint>
#include <map>
#include <optional>
#include <string>
#include <utility>
#include <vector>

namespace circt::hlsest {

//===----------------------------------------------------------------------===//
// Resource counts.
//===----------------------------------------------------------------------===//

/// A non-negative count that may be a fraction (some devices count half
/// blocks or half DSPs). Always kept reduced, with a positive denominator.
struct Rational {
  int64_t num = 0;
  int64_t den = 1;

  Rational() = default;
  Rational(int64_t n) : num(n), den(1) {} // NOLINT: an integer count
  Rational(int64_t n, int64_t d);

  bool isZero() const { return num == 0; }
  bool isInteger() const { return den == 1; }
  /// The count rounded up to whole units (what a report of whole blocks
  /// prints).
  int64_t ceil() const;
  Rational operator+(const Rational &o) const;
  Rational operator*(const Rational &o) const;
  bool operator==(const Rational &o) const {
    return num == o.num && den == o.den;
  }
  bool operator!=(const Rational &o) const { return !(*this == o); }
  /// "3" or "1/2".
  std::string str() const;
  /// Parses "3", "1/2" or a JSON integer.
  static std::optional<Rational> fromJson(const llvm::json::Value &v);
};

/// Resource class -> count. A cost in hls-est is always a ResourceVector
/// over the classes of the device (`device.resource_classes`); today's
/// "bram" number is its entry for `tool.report.primary_memory_class`.
class ResourceVector {
public:
  /// The count of `cls` (0 when absent).
  Rational get(llvm::StringRef cls) const;
  void add(llvm::StringRef cls, Rational n);
  void add(const ResourceVector &o);
  ResourceVector scaled(Rational factor) const;
  bool empty() const { return entries.empty(); }
  /// Entries sorted by class name.
  const std::vector<std::pair<std::string, Rational>> &items() const {
    return entries;
  }
  /// `{"BRAM_18K": 2, "LUT": "1/2"}`.
  llvm::json::Value toJson() const;
  /// "BRAM_18K 2, LUT 1/2".
  std::string str() const;

private:
  std::vector<std::pair<std::string, Rational>> entries;
};

//===----------------------------------------------------------------------===//
// device: the silicon, as data (no tool policy).
//===----------------------------------------------------------------------===//

struct ResourceClass {
  std::string name;
  std::optional<int64_t> capacity; ///< nullopt: not looked up
  std::string reportLabel;
  ResourceVector equivalent; ///< e.g. one MLAB = 10 ALM
};

/// One legal shape of a memory primitive.
struct Geometry {
  int64_t width = 0; ///< data bits per word, parity included
  int64_t depth = 0; ///< words
  std::optional<int64_t> byte; ///< byte-enable width of this shape
};

/// One port configuration of a memory primitive.
struct PortConfig {
  std::string name;               ///< "sp", "sdp", "tdp", ...
  std::vector<std::string> ports; ///< each "r", "w" or "rw"
  int64_t maxWidth = 0;           ///< widest geometry legal in this config
  bool mixedWidth = false;
};

struct ReadLatencyOption {
  int64_t cycles = 1;
  std::optional<double> maxFreqMhz;
};

/// A memory primitive of the device (a block RAM, a LUT RAM, a URAM, ...).
struct DeviceMemory {
  std::string id;
  std::string tier; ///< distributed | hard-small | block | large
  ResourceVector cost;     ///< per instance
  ResourceVector overhead; ///< extra logic per instance
  int64_t bits = 0;        ///< bits per instance, parity included
  std::vector<Geometry> geometries;
  std::vector<PortConfig> portConfigs;
  std::string init; ///< none | zero | any | no_undef
  std::vector<ReadLatencyOption> readLatencyOptions;
  std::optional<double> fmaxMhz;

  const PortConfig *portConfig(llvm::StringRef name) const;
  bool hasGeometry(int64_t width, int64_t depth) const;
};

struct ShiftRegister {
  std::string id;
  int64_t maxDepth = 0;
  int64_t width = 0;
  ResourceVector cost;
};

struct ArithMultiplier {
  int64_t a = 0, b = 0;
  std::string signedness; ///< signed | unsigned | both
  int64_t count = 1;
};

/// A DSP or math block. Recorded for the operator timing models and Phase 6
/// (DSP / FF / LUT); no BRAM rule reads it.
struct ArithBlock {
  std::string id;
  ResourceVector cost, overhead;
  std::vector<ArithMultiplier> mul;
  std::optional<int64_t> preAdd, acc;
  std::vector<std::string> hardFp;
  std::optional<double> fmaxMhz;
};

struct LogicCell {
  std::string cell;
  int64_t lutInputs = 0;
  std::optional<bool> fracturable;
  std::optional<int64_t> regsPerCell;
  ResourceVector cost;
};

struct Device {
  std::string id, part, speedGrade;
  std::string status; ///< validated | unvalidated (`_status`)
  /// Identity strings a tool's own model needs (`tool_ids.<tool>`), read only
  /// by that tool's plugins (the Vitis builtins read `vitis.library`).
  llvm::json::Object toolIds;
  std::vector<ResourceClass> resourceClasses;
  std::vector<DeviceMemory> memories;
  std::vector<ShiftRegister> shiftRegisters;
  std::vector<ArithBlock> arith;
  LogicCell logic;
  /// Chaining terms (reserved; null on every device file today).
  std::optional<llvm::json::Value> timing;
  /// A per-device operator characterisation table (op, widths, period, impl
  /// -> latency, delays, occupancy, cost) for timing models other than
  /// calyx-fixed (Phase 6); empty when none.
  std::string operatorTable;

  const DeviceMemory *memory(llvm::StringRef id) const;
  const ResourceClass *resourceClass(llvm::StringRef name) const;
  /// `tool_ids.<tool>.<key>` as a string, if present.
  std::optional<std::string> toolId(llvm::StringRef tool,
                                    llvm::StringRef key) const;
};

//===----------------------------------------------------------------------===//
// tool: the profile of the modelled HLS tool.
//===----------------------------------------------------------------------===//

struct ArrayPartitionOptions {
  std::string throughputDriven; ///< auto | off
  int64_t completeThreshold = 4;
  bool includePorts = false;
};

struct HlsOptions {
  std::string flowTarget;
  int64_t pipelineLoops = 64;
  ArrayPartitionOptions arrayPartition;
};

struct TimingMargin {
  std::optional<double> fraction; ///< of the clock period
  std::optional<double> ns;
};

struct ReplicationConfig {
  int64_t maxCopies = 16;
  int64_t maxStoresPerIteration = 1;
  bool sharedWritePortReadsWhenIdle = true;
  bool exclusiveArmStoresOnce = true;
  bool calleeStoresPerLoop = true;
  /// A callee parameter is replicable only when the arrays its call sites
  /// pass are: their stores per loop body in the callers (and the callers'
  /// other callees) count (VITIS_NOTES N99).
  bool callerStoresPerLoop = true;
  /// A callee parameter that its call sites bind to two or more different
  /// arrays is port-bound even when the callee has one instance
  /// (VITIS_NOTES N75).
  bool portBoundSeveralArrays = true;
  /// A written global or function-static array is never replicated, also
  /// for a callee reading it through a parameter: its accesses go through
  /// its two ports (VITIS_NOTES N85).
  bool portBoundWritableGlobals = true;
  /// A replicable bank read in a pipelined loop that does not write it only by
  /// steered reads (unrolled copies of one read whose bank is chosen at run
  /// time) gets ceil(R / II) copies, one more than the shared-write-port rule
  /// (VITIS_NOTES N115: kernel w9r15p_rc_rot 16 copies against rc_fix 15;
  /// NeuroFPGA padded_A). Off by default: polybench_pragmas k3mm tmp2, 64
  /// steered reads per bank at II 4, has 15 copies in Vitis (OPEN_ISSUES O153)
  bool rotatingReadsFullCopies = false;
  /// A user bind_storage type=ram_1wnr makes the bank replicable even when a
  /// loop stores it more than once per iteration; that loop's II rises instead
  /// (VITIS_NOTES N113: kernels w9r15p_bw_1wnr 12 against bw_none 4; FocusedACO
  /// route). Off by default: on FocusedACO it needs N114 (exclusive predicated
  /// loads share a port slot, unconfirmed) to stay in band
  bool userRam1wnrReplicable = false;
  /// Steered reads (bank chosen at run time) in different arms of one if /
  /// else-if chain share a port slot (VITIS_NOTES N124).
  bool exclusiveSteeredReadsShareSlot = false;
  /// A select of two loaded values of one array whose arm values are also
  /// used elsewhere (a running maximum) loads the selected address once more:
  /// one more read per select in the RAM_1WNR copy count (VITIS_NOTES N163).
  bool selectOfLoadsReload = false;
  /// A RAM_1WNR bank's independent reads in one state of sequential code
  /// count toward its copies (VITIS_NOTES N164).
  bool sequentialStateReads = false;
  /// A user bind_storage of a plain RAM type (ram_1p, ram_2p, ram_t2p,
  /// ram_s2p) pins the kind: no RAM_1WNR copies, the bank keeps the type's
  /// ports in the scheduler (the II rises), and a ram_s2p bank is priced in
  /// simple-dual-port mode (VITIS_NOTES N173).
  bool userPlainRamPinsKind = false;
};

struct RomConfig {
  int64_t sdpMaxReads = 2;
  std::string copies; ///< ceil_half | n_minus_1
  /// A sequential scope reads a ROM in one state as often as it has
  /// independent reads at one dependence depth (W9r12, VITIS_NOTES N93).
  bool sequentialStateReads = true;
  /// A kept callee pipelined at its caller loop's II spreads its ROM reads
  /// over the II's slots (W9r19, VITIS_NOTES N144).
  bool functionPipelineReads = true;
  /// A ROM read by several kept functions is one copy per reading module
  /// (W9r19, VITIS_NOTES N136 (a), (c), (d)).
  bool moduleCopies = true;
  /// ... also when their common parent reads it itself (N136 (b)); off until
  /// the parent's own copy is priced as Vitis schedules it (OPEN_ISSUES
  /// O130: machsuite aes_table's top copy).
  bool moduleCopiesParentReads = false;
};

struct MemoryArchitectureConfig {
  std::string plugin;
  int64_t untrackedMemoryPorts = 2;
  /// A function argument with an array_partition pragma (its own, or a kept
  /// callee parameter's) has the ports of each bank: an access whose bank is
  /// a constant takes a slot of that bank's pool (VITIS_NOTES N88).
  bool partitionedArgumentBankPorts = true;
  /// A bank that only one pipelined loop accesses, one read and one write
  /// per cycle, gets a read-only and a write-only port: RAM_S2P, simple dual
  /// port (x36) (W9r11, VITIS_NOTES N90).
  bool oneLoopReadWriteSdp = true;
  /// A bank only one iteration of one loop writes and reads becomes
  /// registers (W9r12, VITIS_NOTES N92).
  bool iterationPrivateRegisters = true;
  int64_t portOccupancyCycles = 1;
  ReplicationConfig replication;
  RomConfig rom;
  std::string sequentialScopeModel; ///< stretch-pair | one-port
  /// stretch-pair: two independent reads share a state only when their
  /// first consumers start in the same cycle (Vitis issues a read in the
  /// state before its first consumer; VITIS_NOTES N101).
  bool sequentialLoadsBeforeConsumer = true;
  std::string portSetRule;          ///< by_kind | by_demand
  std::vector<std::vector<std::string>> widePortSets;
  std::string pricedWide, pricedNarrow; ///< port_configs names

  /// The read-or-write slots per cycle of a replicable bank:
  /// max_copies * (ports - 1) + 1 with the shared write port reading when
  /// idle (17 for Vitis), else max_copies * (ports - 1).
  int64_t replicatedSlots() const;
  /// Whether the port set `ports` (r / w / rw, any order) is priced wide.
  bool isWidePortSet(llvm::ArrayRef<std::string> ports) const;
};

struct AxiDefaults {
  int64_t maxReadBurstLength = 16, numReadOutstanding = 16;
  int64_t maxWriteBurstLength = 16, numWriteOutstanding = 16;
};

/// One source of RAM no user array accounts for (memo section 4.2).
struct ImplicitBufferConfig {
  std::string source, protocol, mode, plugin;
  bool enabled = true;
  std::string defaultBundle;
  int64_t minBusBits = 32;
  /// The widest AXI4 data bus (the protocol allows 8 .. 1024 bits); a wider
  /// element is moved in several beats (VITIS_NOTES N56).
  int64_t maxBusBits = 1024;
  AxiDefaults defaults;
  int64_t readFifoSrlMaxDepth = 32;
  std::string readFifoMapper, readFifoPricedConfig;
  int64_t readFifoConfirmedMaxDepth = 4096;
  /// One read FIFO per distinct `channel=` of the bundle's reading ports
  /// (VITIS_NOTES N56, kernels w9r7_mx_ch2 / mx_ch3); off: one per bundle.
  bool readFifoPerChannel = true;
  /// The read FIFO is as wide as the widest load through the port after a
  /// pointer cast (`*reinterpret_cast<ap_uint<512>*>(&a[i])`, N56, kernels
  /// w9r7_mx_cast512 / mx_cast256); off: the declared element widths only.
  bool readFifoCastLoadWidth = true;
  /// The read FIFO's width is rounded up to a power of two (an AXI data bus
  /// is 2^n bytes wide; N63, kernels w9r8p_mx_i9 / mx_i3 / mx_s5).
  bool readFifoPowerOfTwoWidth = true;
  /// A load of a port element whose only use is a part-select
  /// read-modify-write stored back to the same element, every byte of it
  /// either kept whole or overwritten, is no read: Vitis writes the word with
  /// byte strobes (VITIS_NOTES N152, kernels w9r21p_c1..c5).
  bool readFifoStrobedPartWrites = true;
  /// A bundle with a read port under `#pragma HLS cache` has this many
  /// blocks of read cache in its adapter, in place of the read FIFO
  /// (VITIS_NOTES N179); 0: the pragma is ignored.
  int64_t readCacheBram = 0;
  int64_t writeBufferFreeMaxBurst = 16;
  int64_t writeBufferPortWidthBits = 18;
  int64_t writeBufferConfirmedMinBurst = 32;
  /// A write buffer of max_write_burst_length x element bits below this many
  /// bits is LUTRAM, 0 BRAM (VITIS_NOTES N158, kernels w9r21p_i1 / i2); 0:
  /// no such test.
  int64_t writeBufferMinBramBits = 1024;
  /// The write buffer's BRAM is ceil(element bits / port_width_bits), the
  /// widest element not padded to the bus minimum (VITIS_NOTES N158 (b)).
  bool writeBufferElementWidth = true;
  std::string unresolvedCall; ///< rw | none
  /// Read / write requests one bundle accepts per cycle from a pipelined
  /// loop: a modulo-scheduler resource per bundle and direction (VITIS_NOTES
  /// N95); 0: unlimited.
  int64_t readRequestsPerCycle = 1;
  int64_t writeRequestsPerCycle = 1;
  /// The limits also hold for the parameter of a callee that every call
  /// site binds to a port of one bundle (W9r13 review: w9r13rev_mx_callee,
  /// 8 reads in an inline-off load function, II 8).
  bool busRequestsThroughCalls = true;
};

/// hls::stream FIFOs.
struct StreamConfig {
  bool enabled = true;
  int64_t defaultDepth = 2;
  int64_t srlMaxDepth = 2;
  int64_t srlMaxBits = 1024;
  std::string mapper, pricedConfig;
  /// The `<arg>_c` FIFOs a dataflow function forwards its scalar and m_axi
  /// pointer arguments through (VITIS_NOTES N54).
  bool dataflowArgumentFifos = true;
  /// Calls on distinct constant elements of an array of streams are not
  /// ordered by that array: each is its own instance (VITIS_NOTES N59).
  bool distinctElementInstances = true;
  /// A stream's width is cgeist's hls.stream_element_bits when present (the
  /// packed C++ element: bool 1 bit, VITIS_NOTES N58).
  bool declaredElementBits = true;
  /// A function-static stream of a struct is as wide as the struct's C
  /// storage, padding included (VITIS_NOTES N141).
  bool staticStructStorageBits = true;
  /// A local array of a dataflow region with `#pragma HLS stream depth=D`
  /// is one FIFO of depth D at the element width (VITIS_NOTES N67).
  bool streamPragmaArrays = true;
  /// A `stream depth` pragma naming one element of an array of streams
  /// (`variable = s[0]`) deepens that element only (VITIS_NOTES N177).
  bool elementDepthPragmas = false;
};

/// Dataflow ping-pong channels.
struct DataflowChannelConfig {
  bool enabled = true;
  int64_t defaultBlocks = 2;
  /// An array the processes of a dataflow region exchange stays a channel of
  /// that region when one process accesses it from inside its own nested
  /// dataflow region (VITIS_NOTES N84); off: such an array is no channel.
  bool throughNestedRegions = true;
  /// A pipelined loop's accesses of a channel bank at one loop-invariant
  /// address are registers (load before, store after the loop): they give
  /// no second port inside the loop, and two such loops that follow each
  /// other without a loop boundary do (VITIS_NOTES N105).
  bool promotedInvariantAccesses = true;
};

struct PipelineDecisionConfig {
  std::string policy;
  bool floatLoadsPerfect = true;
  bool promotePipelined = true;
  bool flattenAcrossCalls = false;
  /// The straight-line code of flattened parents runs in the pipeline
  /// (VITIS_NOTES N65).
  bool sinkParentCode = true;
  /// ... and the code after the child loop, in its last iteration
  /// (VITIS_NOTES N97 (b)).
  bool sinkParentTrailingCode = true;
  /// ... also when that code writes memory (W9r14 review: Vitis disables
  /// the flatten for such a nest, [HLS 214-437]; off by default).
  bool sinkParentTrailingStores = false;
  /// After the unroll decisions, an affine.if whose set is empty (or
  /// universal) once an unrolled copy's constant index is substituted loses
  /// its dead arm (VITIS_NOTES N89).
  bool foldUnrolledGuards = true;
  /// After the unroll decisions, a product with a constant-zero operand (an
  /// unrolled copy's counter 0) is the constant 0 (W9r23 review D12).
  bool foldUnrolledZeroProducts = true;
  /// A `pipeline off` innermost loop stays sequential in the scheduler
  /// instead of being scheduled as a pipeline (W9 round 12 review).
  bool pipelineOffSequential = true;
  /// A parent is not flattened into an automatically pipelined child whose
  /// sub-loop unroll makes the parent's next index a subscript of a
  /// multi-dimensional array (VITIS_NOTES N96).
  bool doWhileFlattenRefusal = true;
  /// External library functions whose core has loops of its own (Vitis'
  /// sin_or_cos_double / sin_or_cos_float): a loop calling one is neither
  /// pipelined nor unrolled, nor are the loops around it (VITIS_NOTES N169).
  std::vector<std::string> libraryCallsWithLoops;
  /// External library functions (C names) whose Vitis core has no loop of
  /// its own, so a loop calling one is pipelined like any other: timed with
  /// the libm_call operator class (VITIS_NOTES N169). A name not listed
  /// leaves the loop sequential (W9 round 22 review: fmod / atan2 cores have
  /// loops and their callers are not pipelined).
  std::vector<std::string> pipelinedLibraryCalls;
  /// ... only for a subscript made by a sub-loop of at least this trip count.
  int64_t doWhileMinSubLoopTrip = 3;
  /// A user `unroll factor=F` (1 < F) on an scf.for with a run-time trip count is applied as F guarded copies of the body in a loop of step F*step (copy u runs under iv + u*step < ub, Vitis keeps the exit test in the unrolled body); a copy's index into a cyclic partition is then not a constant bank, so e
  bool partialUnrollRuntimeLoops = true;
  /// The occupancy of a kept call in a pipelined loop is recomputed once the
  /// automatic partitions are decided: accesses to arrays that became
  /// registers, and loads whose value is unused, take no port (OPEN_ISSUES O133
  /// / O144, Dehazing calculate_median: its scalarised window; off: the
  /// occupancy --auto-pipeline-unroll estimated before the partitions)
  bool callOccupancyAfterPartition = true;
  /// fold_unrolled_guards also substitutes guard operands computed from
  /// constants through nested affine.apply and index arithmetic (an unrolled
  /// copy's apply of apply of a constant), so a guard whose operands are all
  /// constants folds (OPEN_ISSUES O151: nikhil_p lab2 kernel_attention_V, V_lcl
  /// read 7 times on banks 0..3 and 6 times on 4..15 as in Vitis; off: only a
  /// constant or a one-level apply of constants)
  bool foldNestedConstantGuards = true;
  /// An affine.if that holds on its loops' whole domain folds (N127).
  bool foldDomainTrueGuards = false;
  /// A load of one element in both arms of an if is read once before it
  /// (N127, W9r16 review).
  bool hoistCommonArmLoads = false;
  /// A pipelined loop promotes only locations invariant over the loops
  /// flattened into it (W9r16 review, gp_flat).
  bool promoteNestInvariantOnly = false;
  /// After LICM's store after a promoted loop: loads of that element that
  /// follow read the stored value, and the store before the loop and the
  /// promoted store itself are deleted when overwritten before any read
  /// (VITIS_NOTES N166 (a)).
  bool promotedStoreCleanup = false;
  /// The register promotion also rewrites accesses of the element nested in
  /// if-arms of the loop body: the value is carried through the if as a
  /// result (LLVM LICM promotes a conditional store to a non-escaping local;
  /// W9 round 22 review kernel w9r22rv_k09_condacc).
  bool promoteConditionalAccesses = false;
  /// A perfect inner loop with a nest-invariant variable bound flattens
  /// (W9r16 review, gp_flat).
  bool flattenNestInvariantBounds = false;
};

struct PartitionInferenceConfig {
  int64_t targetII = 1;
  int64_t portsAny = 2, portsRead = 1, portsWrite = 1;
  int64_t maxFactor = 0, maxDims = 1;
  bool rotatingBanks = false;
  int64_t maxScannedFactor = 65536;
};

struct PartitioningConfig {
  std::string policy;
  int64_t constantIndexMinExtent = 2;
  /// Largest extent of a dimension rule (b) partitions: Vitis leaves a
  /// constant-indexed dimension of more than 64 elements whole, whatever the
  /// element width or the number of rows (VITIS_NOTES N61; 0: no limit).
  int64_t constantIndexMaxExtent = 64;
  /// Rule (b) also after a user cyclic / block partition, on every part
  /// (VITIS_NOTES N57).
  bool constantIndexAfterUserPartition = true;
  /// Rule (b) also for an array without an affine access (every index a
  /// memref.load operand; N57: the other indices need not be affine).
  bool constantIndexNonAffineArrays = true;
  /// Rule (b) also for an array whose only storage pragma is `stream
  /// type=pipo` (VITIS_NOTES N77).
  bool constantIndexPipoStreams = true;
  /// Rule (b) also for memref.globals, over every function's accesses (N77).
  bool constantIndexGlobals = true;
  /// Rule (b) follows an array into the callees it is passed to: their
  /// accesses count as the array's (VITIS_NOTES N94).
  bool constantIndexThroughCalls = true;
  /// An index computed by division, remainder, shifts or bit operations on
  /// constants is a constant (VITIS_NOTES N97 (a)).
  bool constantIndexFoldDivision = true;
  /// (b) / banking: a value chosen by an scf.if / select whose condition
  /// folds to a constant is that constant (VITIS_NOTES N110 corpus).
  bool constantIndexFoldConditionals = true;
  /// (c) through element / row views (polygeist.subindex, memref.cast)
  /// passed to callees (N94 through the view, O133).
  bool constantIndexThroughViews = true;
  /// After a user block partition, rule (b) asks for a constant offset
  /// inside the block, not a constant index (VITIS_NOTES N104).
  bool constantIndexBlockOffset = true;
  /// An ap_fixed compound assignment (cgeist's hls.ap_compound_assign) to a
  /// bank chosen at run time writes that bank twice (VITIS_NOTES N38 R-cmpd).
  bool compoundAssignTwoStores = true;
  /// A block-partitioned dimension whose index stays in one block over the
  /// constant iteration range of its loops has a constant bank (W9r10
  /// review D2; VITIS_NOTES N86).
  bool blockBankFromLoopRange = true;
  PartitionInferenceConfig inference;
  bool steerAffineLoads = true;
  /// Steered load groups follow N74: a group spans every partitioned
  /// dimension (base + constant on each) and copies that share a residue
  /// class form further groups, so a bank is read once per class member.
  bool steerWindowGroups = true;
  /// The unrolled copies of a window read, each under its own guard (the one
  /// access of the array under it; not a run-time partial unroll's trip
  /// test; no call or store to the array in the block), still form one
  /// steered group (VITIS_NOTES N155, kernel w9r21p_g1_rot5).
  bool steerThroughGuards = true;
  /// A bank no access reads, after the steered reads are limited to the
  /// banks their counters reach, is removed with its stores, also when it is
  /// passed to callees that only write it (VITIS_NOTES N157, kernel
  /// w9r21p_k1_deadbank; YOLOv4-Tiny L5).
  bool dropUnreadBanks = true;
  /// An scf.for induction variable plus a constant, with a constant lower
  /// bound and a step that is a multiple of a cyclic factor, addresses one
  /// bank (W9r14 review, N103 copies, kernel w9r14rv_uv_lb0).
  bool inductionResidueBanks = true;
  /// A store whose bank is chosen at run time writes only the banks its index
  /// can reach when only the known low bits of its operands are used (an
  /// affine.for counter is lb + step * t, any other operand unknown): copy u of
  /// Cl[i][jj + u] with jj stepping by 32 writes banks u and u + 32, not every
  /// bank of the partition (OPEN_ISSUES O150: ben_hall lab3, kernel
  /// w9r8p_fl_pre; a loop range does not prune: vishnu lab3 row_ptr_A_local;
  /// off: a store_enable on every bank)
  bool reachableStoreBanks = true;
  /// A one-element bank of a complete partition (memory banking's hls.partition
  /// alloca) is a register: no port pool in a pipelined loop, priced as
  /// registers (VITIS_NOTES N111: kernel w9r15p_rg_net, a compare-and-swap
  /// network on a completely partitioned int v[8] runs at II 1; off: two ports
  /// per element)
  bool completePartitionRegisters = true;
  /// A memref index whose low bits are known modulo a power-of-two cyclic
  /// factor ((n & ~7) + k: residue k mod 8; through casts, add / sub, masks
  /// with all-zero or all-one low bits, multiplies and shifts by a multiple of
  /// the factor) addresses that one bank, its offset computed at run time, as
  /// LLVM's known bits give Vitis (VITIS_NOTES N115 control kernel
  /// w9r15p_rc_fix: 15 copies per bank; off: the bank is chosen at run time)
  bool knownResidueBanks = true;
  /// A block-partitioned memref index whose value range (types, masks,
  /// constants) stays inside fewer blocks reaches only those (VITIS_NOTES
  /// N175).
  bool banksFromValueRange = false;
  /// A partitioned local array passed to a kept callee whose parameter
  /// declares a smaller first dimension keeps its partition across the call
  /// (VITIS_NOTES N180).
  bool reshapedCalleeParameters = false;
  /// Reads of a completely partitioned dimension at a run-time bank index
  /// address every bank at the in-bank offset 0, so reads that share their
  /// other subscripts load each bank once (VITIS_NOTES N172).
  bool sharedAddressBankReads = false;
};

struct FoldingConfig {
  std::string ruleSet; ///< vitis-undef | zero | a plugin
  bool canonicalize = true;
  int64_t maxRounds = 16;
  /// The address of a local array or global (or of a view of one) compared with
  /// the null pointer folds to a constant (never null), so a comparison does
  /// not keep the array alive (VITIS_NOTES N118: kernel w9r15p_pb_null, Vitis 0
  /// BRAM; nikhil_p lab2 K_lcl; off: the comparison keeps it)
  bool storageAddressNotNull = true;
  /// Calls of the assertion failure handler build no hardware (N126).
  bool dropAsserts = false;
  /// A call whose arguments are all constants and whose callee computes
  /// without memory is evaluated and replaced by its result (N130).
  bool evaluateConstantCalls = true;
  /// Operations one such evaluation may execute before it gives up.
  int64_t constantCallMaxSteps = 1000000;
  /// After the unroll decision, a load of a never-written initialised global
  /// at constant subscripts is its initial value; a table every load of which
  /// folds disappears (VITIS_NOTES N168).
  bool constantGlobalLoadsAfterUnroll = false;
  /// Loops of a function's entry that fill local arrays from constants are
  /// evaluated; such an array becomes a constant table (VITIS_NOTES N174).
  bool evaluateConstantFills = false;
  /// The largest array (elements) such an evaluation keeps.
  int64_t constantFillMaxElements = 4096;
};

struct DeadMemoryConfig {
  bool overwrittenStores = true;
  bool deadCalls = true;
  bool honourPreserve = false;
  bool globalSharedByFunctionsEscapes = true;
  bool keepLoadStoreCycles = true;
  /// A kept call's one-element output that is overwritten (or never touched)
  /// after the call before any read does not keep the call (N107).
  bool overwrittenCallOutputs = true;
  /// ... also when the overwrite is the first access inside a loop that runs
  /// at least once (W9r14 review, kernel w9r14rv_dc_loopw).
  bool overwrittenByLoops = true;
  /// A store into an element of a registers array (hls.registers) that no used
  /// load reads, in its function or in the kept callees it is passed to, is
  /// deleted with the values computed only for it, after the automatic
  /// partitions (VITIS_NOTES N110: Vitis passes a kept callee only the window
  /// elements it reads; Dehazing calculate_median, kernel w9r15p_dw_dead; off:
  /// every store stays)
  bool unreadRegisterElements = true;
};

struct MiddleEndConfig {
  bool licmHoistInvariantLoads = true;
  bool licmHoistPastCalls = true;
  bool licmHoistConditional = true;
  bool mergeIfElseAccesses = true;
  bool gvnLoads = true;
  bool gvnConditionalLoads = true;
  /// The clean-ups treat a global array like a local one.
  bool trackGlobals = true;
  bool storeForwarding = true;
  /// A store under an if of a pipelined body that a later store of the same
  /// address at the body's top level overwrites in the same iteration (only
  /// loads of that address between) uses no port (GVN load PRE + DSE).
  bool dseGuardedStores = true;
  /// A load under an if of a pipelined body that reads what a store at the
  /// body's top level wrote earlier in the same iteration uses no port.
  bool forwardToGuardedLoads = true;
  DeadMemoryConfig deadMemory;
  /// LICM: a loop-invariant load in the condition region of an scf.while (a
  /// bound re-read every iteration, for (i = rp[r]; i < rp[r + 1]; ++i)) moves
  /// in front of the loop, so it shares the enclosing scope's states
  /// (VITIS_NOTES N120: davendra lab3 row_ptr_A_local, kernels w9r15p_rp_*;
  /// off: it stays in the condition)
  bool licmHoistWhileConditions = true;
  /// GVN also on memref.load (an index computed outside the affine form): a
  /// load of the same index values as an earlier load of the block, nothing in
  /// between that may write it, is the same value (Dehazing debayer with its
  /// counters raised by cgeist: 27 reads of in_tile, 9 distinct; off: only
  /// affine.load)
  bool gvnMemrefLoads = true;
  /// Store-to-load forwarding and dead-store elimination in pipelined loop
  /// bodies on partitioned local arrays before --memory-banking-bram splits
  /// them (VITIS_NOTES N138: k2mm's unrolled tmp1 copies keep one load and
  /// one store per iteration; off: only the cleanup after banking, which a
  /// run-time bank hides the address from)
  bool forwardBeforeBanking = false;
};

struct StructConfig {
  bool aggregate = true;
  bool globals = true;
  bool scalarRegisters = true;
  bool throughCalls = true;
  bool elementCopyLoops = true;
  bool temporaryRegisters = true;
  bool memberPartitions = true;
  /// After the split, a static array passed to a callee's dynamic-shape
  /// parameter specialises the callee to the static type (OPEN_ISSUES O84
  /// (c)).
  bool specializeSplitCasts = true;
  /// A pointer-to-struct argument of the top function without a memory
  /// interface is one wide scalar register (W9r19, VITIS_NOTES N147).
  bool topPointerScalar = true;
};

struct NarrowingConfig {
  bool storedRanges = true;
  bool loadDemand = true;
  std::vector<std::string> fullAddressInterfaceModes;
  bool completeReadSelector = true;
  /// A RAM whose every stored value is a constant is narrowed by N26's ROM
  /// reinterpretation of that set (N112).
  bool constantSetReinterpretation = true;
  /// An undefined value adds nothing to a select's or an if's range
  /// (N151 (b)).
  bool undefContributesNothing = true;
  /// A load from a register array or a struct field takes the range of the
  /// store that reaches it in its block (N151 (c)).
  bool reachingStoreRanges = true;
  /// An accumulation `s += x` over a loop of T trips ranges over init +
  /// T x the step's range, as an iter_arg or through memory (N159).
  bool accumulationRanges = true;
  /// An array whose element a called (kept) function writes through a
  /// scalar reference parameter is not narrowed (N162).
  bool calleeParamStoresFullRange = true;
  /// A stored value that is a plain copy of the array's own loaded elements
  /// (a swap) makes no cycle: the copy carries the array's range (VITIS_NOTES
  /// N167; a copy through another array still does).
  bool copiesCloseRanges = false;
};

struct HlsToolConfig {
  HlsOptions options;
  TimingMargin timingMargin;
  MemoryArchitectureConfig memoryArchitecture;
  std::vector<ImplicitBufferConfig> implicitBuffers;
  StreamConfig streams;
  DataflowChannelConfig dataflowChannels;
  PipelineDecisionConfig pipelineDecision;
  PartitioningConfig partitioning;
  FoldingConfig folding;
  MiddleEndConfig middleEnd;
  bool honourInlineOff = true;
  /// A kept callee is cloned per tuple of argument IR types of its call sites
  /// (float / double top-level ports vs caller-local arrays; VITIS_NOTES N165).
  bool clonePerArgumentType = false;
  StructConfig structs;
  NarrowingConfig narrowing;
  bool globalsAttributeAccesses = false;
  std::string groupingPlugin;
  std::string mathLibraryTable;
  /// A cos / sin table filled into a local struct array (std::complex) is
  /// computed at run time (a core); a plain local or a global is a ROM
  /// (VITIS_NOTES N60).
  bool localStructTablesAtRunTime = true;
  /// An ap_fixed hls::exp without a cost table entry is priced as the ROM
  /// tables of its body (VITIS_NOTES N106).
  bool fixedExpTablesWhenUnlisted = true;
  /// In a pipelined loop, the ap_fixed library cores whose tables are known
  /// share one set of tables read k times per cycle (N16 R6).
  bool inlinedTablesInPipelines = true;
  /// Calls of different functions whose cost-table entries name the same
  /// library module (sin and cos of double: sin_or_cos_double_s) share its
  /// instances (VITIS_NOTES N169).
  bool sharedLibraryModules = false;
  /// A library math core is shared by calls in exclusive arms of one
  /// pipelined iteration and by the pipelined loops of one function (they
  /// run one after another) (VITIS_NOTES N178).
  bool sequentialCoreSharing = false;
  /// An array argument of the top bound to s_axilite is a RAM inside the
  /// control adapter, priced like a two-port bank (VITIS_NOTES N176).
  bool axiLiteArrayMemories = false;

  /// The implicit buffer of `protocol` (e.g. "axi4-mm"), or null.
  const ImplicitBufferConfig *implicitBuffer(llvm::StringRef protocol) const;
};

struct StorageSelectorConfig {
  std::string plugin;
  int64_t minBlockBits = 1024;
  bool inclusive = true;
  std::string block; ///< memory id of the block tier
  std::string below; ///< tier name for what stays below the threshold
  /// The bind_storage impl that puts a bank in the block tier at any size
  /// (Vitis: bram, VITIS_NOTES N98); empty: none.
  std::string forcingImpl = "bram";
  /// The bind_storage impl that puts a bank in the tier below the block tier
  /// at any size (Vitis: lutram, VITIS_NOTES N171); empty: none.
  std::string distributedImpl;

  /// Whether `bits` (words x exact element bits) stays below the block tier.
  bool belowBlock(int64_t bits) const {
    return inclusive ? bits < minBlockBits : bits <= minBlockBits;
  }
  /// "<" or "<=" for the reports.
  const char *belowSymbol() const { return inclusive ? "<" : "<="; }
};

/// One depth band of the vitis-band7 mapper.
struct DepthBand {
  std::optional<int64_t> maxDepth; ///< nullopt for the `beyond` band
  bool beyond = false;
  std::optional<int64_t> width;    ///< the column width of the band
  std::optional<int64_t> sdpWidth; ///< column width when the bank is wide
  std::optional<int64_t> tdpWidth; ///< ... when it is narrow
  std::optional<int64_t> altWidth; ///< the alternative column (2Kx9 x 2)
  std::optional<int64_t> altStack;
  std::optional<int64_t> wordsPerBlock; ///< `beyond`: words of one block
};

struct MemoryMapperConfig {
  std::string plugin;
  std::string primitive;     ///< memory id
  std::string depthRounding; ///< pow2 | exact
  std::vector<std::string> acceptedLibraries;
  std::vector<DepthBand> depthBands;
  bool mixedColumns = false; ///< geometry-min: mix column widths
  bool depthStack = false;   ///< geometry-min: stack shallower blocks
};

struct BackendConfig {
  std::string id;
  StorageSelectorConfig storageSelector;
  MemoryMapperConfig memoryMapper;
};

struct ReportConfig {
  std::string primaryMemoryClass;
  std::string stdoutFormat; ///< vitis-bram | per-class
  std::string referenceStage;
  std::vector<std::string> classes;
};

struct ToolProfile {
  std::string id, name, version;
  HlsToolConfig hls;
  BackendConfig backend;
  ReportConfig report;
  std::string pipeline;
};

//===----------------------------------------------------------------------===//
// scheduling, frontend, run.
//===----------------------------------------------------------------------===//

/// Delay of one operator class up to a width (the last band has no bound).
struct DelayBand {
  std::optional<int64_t> maxBits;
  double ns = 0;
};

/// The ASAP chaining model of the depth of a call of a loop-free callee
/// (--auto-pipeline-unroll; the delays Vitis 2025.1 reports for xc7z020-1).
struct CallDepthConfig {
  double loadDataNs = 3.25;
  double logicNs = 0.99;
  double selectNs = 0.69;
  double variableShiftNs = 4.42;
  double constantMultiplierNs = 5.58;
  int64_t narrowMultiplyMaxBits = 32;
  int64_t narrowMultiplyCycles = 2;
  int64_t portsPerMemory = 2;
  /// Two calls of one function at the top level of their caller that no
  /// value or array orders still share an instance when their inputs become
  /// ready in different states of the caller's call schedule (N116).
  bool staggeredCallsShareInstance = true;
  /// Calls are issued in program order: two calls of a function share an
  /// instance when a call between them waits for the first (VITIS_NOTES
  /// N156, kernels w9r21p_f1 .. f4); with staggeredCallsShareInstance, both
  /// rules also apply in one nested block outside pipelines.
  bool inOrderCallStarts = true;
  /// A function's allocation limit caps the calls of each loop Vitis
  /// outlines into a module of its own separately (N14 R5).
  bool outlinedLoopsOwnAllocation = true;
  /// A kept callee with an array parameter called inside a pipelined loop
  /// Vitis outlines and outside it has an instance in each module (W9r19,
  /// VITIS_NOTES N145).
  bool outlinedPipelineArrayInstances = true;
  /// Calls of a kept callee in two loops of its caller that run one after
  /// the other share an instance (N16 R10 for kept callees; W9 round 19
  /// review defect 3).
  bool sequentialLoopsShareInstance = true;
  int64_t indexBits = 32;
  std::vector<DelayBand> carryChainNs, ternaryAdderNs;

  double carryChain(unsigned bits) const;
  double ternaryAdder(unsigned bits) const;
};

struct SchedulingConfig {
  std::string timingModel;
  std::map<std::string, int64_t> operatorLatencies;
  std::string dependenceModel;
  /// Loop-carried memory recurrences bound the II of a pipelined loop
  /// (VITIS_NOTES N87, MemoryRecurrences.h).
  bool memoryRecurrences = true;
  /// A read-modify-write of one array at an address computed inside the
  /// loop body (h[v]++) bounds the II at least this much (N117; 0: off).
  int64_t unknownAddressMinII = 2;
  /// `#pragma HLS dependence variable=<v> inter false` removes <v>'s
  /// loop-carried memory recurrences (N122).
  bool userInterIndependence = true;
  /// The memory-recurrence analysis evaluates an enclosing loop's induction
  /// variable this many steps past its lower bound (O170 (b); 0: the lower
  /// bound).
  int64_t enclosingIvSampleSteps = 0;
  /// The predicated stores of a run-time-chosen bank count as stores of the
  /// array for its loop-carried memory recurrences (O170 (a)).
  bool bankStoreRecurrences = false;
  /// Cycles an operator class adds to such a recurrence chain
  /// (`<class>_f32` / `<class>_f64` before `<class>`); a class not listed
  /// adds its operator latency (VITIS_NOTES N83).
  std::map<std::string, int64_t> recurrenceLatencies;
  /// A floating-point add / multiply on a register (iter_arg) recurrence
  /// takes its recurrenceLatencies value instead of its operator latency
  /// (VITIS_NOTES N83: `s = s op a[i]` reaches the recurrence values).
  bool registerRecurrenceLatencies = false;
  /// An iter_arg that carries an array element promoted to a register,
  /// through two or more multi-cycle operations, bounds the II by its chain
  /// latency + 1 (VITIS_NOTES N160, kernels w9r21p_b1 / b2).
  bool promotedElementRegisterCycle = true;
  /// Any iter_arg (a scalar accumulator too) carried through a multi-cycle
  /// double-precision operation fed by another multi-cycle floating-point
  /// operation bounds the II by its chain latency + 1
  /// (VITIS_NOTES N160 (b), kernels w9r21rev_r2c / r2d / r2e).
  bool f64RegisterCycle = true;
  /// The accesses of an aggregated word whose lane is read and written back
  /// in one block share one port (VITIS_NOTES N154 (b)).
  bool laneRmwOnePort = true;
  /// Ops the N160 search may visit per loop before it gives up (designer
  /// knob; 0: unlimited).
  int64_t promotedElementSearchBudget = 1000000;
  /// A read-modify-write of a lane chosen at run time in an aggregated word
  /// (hls::vector) at a word address the loop keeps is a recurrence through
  /// the memory, II >= 3 + chain, not a promoted element (VITIS_NOTES N154,
  /// kernel w9r21p_e1_vecrmw).
  bool dynamicLaneRmw = true;
  std::string moduloModel;
  int64_t fastThreshold = 150;
  int64_t fastOpsThreshold = 4096;
  int64_t maxIIBumps = 4096;
  /// greedy-simplex: a loop the simplex scheduled is also scheduled by the
  /// greedy scheduler, and the lower II wins (W9r13-impl: the simplex fixes
  /// the store of an unrolled reduction before its loads and then bumps
  /// the II; Vitis reaches the resource bound).
  bool lowerIIOfBoth = true;
  /// A call in a pipelined loop to a kept callee that reads and writes one
  /// global array is a loop-carried recurrence of the call: the II is at
  /// least the call's depth (W9r13 review: w9r13rev_gl_call, II 2;
  /// gl_callw, stores only, II 1).
  bool calleeGlobalRecurrence = true;
  /// A pipelined loop whose body (after the implied unroll) has more ops
  /// than this is left sequential with a warning: a guard against bodies the
  /// pipeline construction cannot hold in memory (OPEN_ISSUES O76:
  /// hlsyn-vitis seidel-2d, 40 x 118 x 118 unrolled; 0: no guard).
  int64_t maxPipelineBodyOps = 250000;
  int64_t recurrenceRepairRounds = 64;
  /// Greedy scheduler: ready ops in order of their latency path to the end
  /// of the iteration, not program order (VITIS_NOTES N133).
  bool heightPriority = false;
  /// Greedy scheduler: at II > 1 each floating-point operator class (fadd,
  /// fmul, dadd, dmul) has ceil(ops / II) units, one more per carried edge
  /// they would break (VITIS_NOTES N135).
  bool fpUnitLimits = false;
  bool userIITarget = true;
  std::string sequentialModel;
  std::string bindingModel;
  bool emitDetail = false;
  CallDepthConfig callDepth;

  /// `operator_latencies.<cls>`; 0 when the class is not listed.
  int64_t latency(llvm::StringRef cls) const;
  /// The operator class of a floating-point `base` operation (fpdiv,
  /// fpsqrt) on floats of `width` bits: `<base>_f<width>` when the table has
  /// that key, else `base` (VITIS_NOTES N78: the divide and the square root
  /// take 15 / 58 and 15 / 56 cycles for float / double).
  std::string floatClass(llvm::StringRef base, unsigned width) const;
};

struct FrontendConfig {
  int64_t indexBits = 64;
  std::vector<std::string> elementTypes;
  std::vector<std::string> userStoragePragmas;
};

struct RunConfig {
  std::string device; ///< id of a compiled-in device file, or a path
  std::string tool;   ///< id of a compiled-in profile, or a path
  double clockNs = 10;
};

/// One leaf of the configuration whose value differs from the compiled-in
/// default, and where it came from (a file or --config-set).
struct ConfigOverride {
  std::string path;
  llvm::json::Value value;
  std::string source;
};

class Config {
public:
  int64_t version = 1;
  RunConfig run;
  Device device;
  ToolProfile tool;
  FrontendConfig frontend;
  SchedulingConfig scheduling;
  /// `plugins.<name>` sections, passed to the plugin that owns the name.
  llvm::json::Object plugins;

  /// Provenance: the SHA-256 (hex) of the merged configuration without its
  /// documentation keys, the --hls-config files and the --config-set
  /// assignments in the order they were applied, and every leaf that
  /// differs from the compiled-in defaults.
  std::string hash;
  std::vector<std::string> files;
  std::vector<std::string> sets;
  std::vector<ConfigOverride> overrides;
  /// The merged document (documentation keys removed).
  llvm::json::Value merged = nullptr;

  bool isDefault() const { return overrides.empty(); }

  /// The clock period minus the timing margin (ns).
  double periodNs() const;

  /// The block-RAM primitive the memory mapper prices with
  /// (tool.backend.memory_mapper.primitive), or null.
  const DeviceMemory *blockMemory() const;
  /// The widest port of a bank priced wide (priced_configs.wide: 36) or
  /// narrow (priced_configs.narrow: 18), from the device's port configs.
  int64_t pricedPortWidth(bool wide) const;
  /// Ports of the narrow (true-dual-port) configuration of one block (2).
  int64_t blockPorts() const;

  /// The configuration of this process: what the driver installed, else the
  /// compiled-in defaults. Immutable once a pass has read it.
  static const Config &get();
  /// The compiled-in defaults (built once).
  static const Config &defaults();
  /// Installs the merged configuration (the hls-est driver does this once,
  /// after the command line has been parsed and before any pass runs).
  static void install(Config config);
};

//===----------------------------------------------------------------------===//
// Building, dumping, validating.
//===----------------------------------------------------------------------===//

struct ConfigDiagnostics {
  std::vector<std::string> errors;
  std::vector<std::string> warnings;
  bool ok() const { return errors.empty(); }
};

/// Builds the configuration: the compiled-in defaults, then each file of
/// `files` in order, then each `path=value` assignment of `sets`. A file or
/// assignment that sets `run.device` (`run.tool`) first replaces the
/// `device` section (the `tool` and `scheduling` sections) with the named
/// compiled-in file or the file at that path. Every error is collected in
/// `diag`; the result is valid only when `diag.ok()`.
Config buildConfig(llvm::ArrayRef<std::string> files,
                   llvm::ArrayRef<std::string> sets, ConfigDiagnostics &diag);

/// The compiled-in defaults as JSON, sorted, with a `_doc` string per
/// section and an `_<key>` description next to every key.
std::string dumpDefaultConfig();
/// The merged configuration as JSON, sorted; every object that holds a key
/// differing from the defaults gets `_source: {key: origin}`.
std::string dumpEffectiveConfig(const Config &config);
/// The schema: every key with its type, unit, default, range, doc,
/// inventory rows and readers, as JSON (make_config_doc.py reads it).
std::string dumpConfigSchema();

/// The compiled-in device and profile files by id (for --list-targets and
/// the loader).
std::vector<std::string> compiledInDevices();
std::vector<std::string> compiledInProfiles();

/// Writes `v` as JSON with sorted keys and two-space indentation.
std::string printSortedJson(const llvm::json::Value &v);

} // namespace circt::hlsest

#endif // CIRCT_DIALECT_RESOURCE_CONFIG_CONFIG_H
