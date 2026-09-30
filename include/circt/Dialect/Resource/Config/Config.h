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
};

struct RomConfig {
  int64_t sdpMaxReads = 2;
  std::string copies; ///< ceil_half | n_minus_1
  /// A sequential scope reads a ROM in one state as often as it has
  /// independent reads at one dependence depth (W9r12, VITIS_NOTES N93).
  bool sequentialStateReads = true;
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
  int64_t writeBufferFreeMaxBurst = 16;
  int64_t writeBufferPortWidthBits = 18;
  int64_t writeBufferConfirmedMinBurst = 32;
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
  /// A local array of a dataflow region with `#pragma HLS stream depth=D`
  /// is one FIFO of depth D at the element width (VITIS_NOTES N67).
  bool streamPragmaArrays = true;
};

/// Dataflow ping-pong channels.
struct DataflowChannelConfig {
  bool enabled = true;
  int64_t defaultBlocks = 2;
  /// An array the processes of a dataflow region exchange stays a channel of
  /// that region when one process accesses it from inside its own nested
  /// dataflow region (VITIS_NOTES N84); off: such an array is no channel.
  bool throughNestedRegions = true;
};

struct PipelineDecisionConfig {
  std::string policy;
  bool floatLoadsPerfect = true;
  bool promotePipelined = true;
  bool flattenAcrossCalls = false;
  /// The straight-line code of flattened parents runs in the pipeline
  /// (VITIS_NOTES N65).
  bool sinkParentCode = true;
  /// After the unroll decisions, an affine.if whose set is empty (or
  /// universal) once an unrolled copy's constant index is substituted loses
  /// its dead arm (VITIS_NOTES N89).
  bool foldUnrolledGuards = true;
  /// A `pipeline off` innermost loop stays sequential in the scheduler
  /// instead of being scheduled as a pipeline (W9 round 12 review).
  bool pipelineOffSequential = true;
  /// A parent is not flattened into an automatically pipelined child whose
  /// sub-loop unroll makes the parent's next index a subscript of a
  /// multi-dimensional array (VITIS_NOTES N96).
  bool doWhileFlattenRefusal = true;
  /// ... only for a subscript made by a sub-loop of at least this trip count.
  int64_t doWhileMinSubLoopTrip = 3;
  /// A user `unroll factor=F` (1 < F) on an scf.for with a run-time trip count is applied as F guarded copies of the body in a loop of step F*step (copy u runs under iv + u*step < ub, Vitis keeps the exit test in the unrolled body); a copy's index into a cyclic partition is then not a constant bank, so e
  bool partialUnrollRuntimeLoops = true;
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
};

struct FoldingConfig {
  std::string ruleSet; ///< vitis-undef | zero | a plugin
  bool canonicalize = true;
  int64_t maxRounds = 16;
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
};

struct NarrowingConfig {
  bool storedRanges = true;
  bool loadDemand = true;
  std::vector<std::string> fullAddressInterfaceModes;
  bool completeReadSelector = true;
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
  StructConfig structs;
  NarrowingConfig narrowing;
  bool globalsAttributeAccesses = false;
  std::string groupingPlugin;
  std::string mathLibraryTable;
  /// A cos / sin table filled into a local struct array (std::complex) is
  /// computed at run time (a core); a plain local or a global is a ROM
  /// (VITIS_NOTES N60).
  bool localStructTablesAtRunTime = true;

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
  /// Cycles an operator class adds to such a recurrence chain
  /// (`<class>_f32` / `<class>_f64` before `<class>`); a class not listed
  /// adds its operator latency (VITIS_NOTES N83).
  std::map<std::string, int64_t> recurrenceLatencies;
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
