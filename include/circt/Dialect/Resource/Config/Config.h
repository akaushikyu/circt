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
};

struct RomConfig {
  int64_t sdpMaxReads = 2;
  std::string copies; ///< ceil_half | n_minus_1
};

struct MemoryArchitectureConfig {
  std::string plugin;
  int64_t untrackedMemoryPorts = 2;
  int64_t portOccupancyCycles = 1;
  ReplicationConfig replication;
  RomConfig rom;
  std::string sequentialScopeModel; ///< stretch-pair | one-port
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
  int64_t writeBufferFreeMaxBurst = 16;
  int64_t writeBufferPortWidthBits = 18;
  int64_t writeBufferConfirmedMinBurst = 32;
  std::string unresolvedCall; ///< rw | none
};

/// hls::stream FIFOs.
struct StreamConfig {
  bool enabled = true;
  int64_t defaultDepth = 2;
  int64_t srlMaxDepth = 2;
  int64_t srlMaxBits = 1024;
  std::string mapper, pricedConfig;
};

/// Dataflow ping-pong channels.
struct DataflowChannelConfig {
  bool enabled = true;
  int64_t defaultBlocks = 2;
};

struct PipelineDecisionConfig {
  std::string policy;
  bool floatLoadsPerfect = true;
  bool promotePipelined = true;
  bool flattenAcrossCalls = false;
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
  /// An ap_fixed compound assignment (cgeist's hls.ap_compound_assign) to a
  /// bank chosen at run time writes that bank twice (VITIS_NOTES N38 R-cmpd).
  bool compoundAssignTwoStores = true;
  PartitionInferenceConfig inference;
  bool steerAffineLoads = true;
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
};

struct MiddleEndConfig {
  bool licmHoistInvariantLoads = true;
  bool licmHoistPastCalls = true;
  bool licmHoistConditional = true;
  bool mergeIfElseAccesses = true;
  bool gvnLoads = true;
  bool storeForwarding = true;
  DeadMemoryConfig deadMemory;
};

struct StructConfig {
  bool aggregate = true;
  bool globals = true;
  bool scalarRegisters = true;
  bool throughCalls = true;
  bool elementCopyLoops = true;
  bool temporaryRegisters = true;
};

struct NarrowingConfig {
  bool storedRanges = true;
  bool loadDemand = true;
  std::vector<std::string> fullAddressInterfaceModes;
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
  std::string moduloModel;
  int64_t fastThreshold = 150;
  int64_t fastOpsThreshold = 16384;
  int64_t maxIIBumps = 4096;
  int64_t recurrenceRepairRounds = 64;
  bool userIITarget = true;
  std::string sequentialModel;
  std::string bindingModel;
  bool emitDetail = false;
  CallDepthConfig callDepth;

  /// `operator_latencies.<cls>`; 0 when the class is not listed.
  int64_t latency(llvm::StringRef cls) const;
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
