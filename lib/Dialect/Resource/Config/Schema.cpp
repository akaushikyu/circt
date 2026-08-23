//===- Schema.cpp - The keys of the hls-est configuration -----------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// The rows of the "rows" column are those of
// hls-doc/design/assumptions-inventory.md; a key without a row was added
// after the inventory was written (the passes of the W9 rounds: stream
// FIFOs, dataflow channels, width narrowing, struct splitting, the
// call-depth model of the pipeline decision, ...), and its doc says what it
// models. "unconfirmed" in a doc marks a value no Vitis kernel has proven.
//
//===----------------------------------------------------------------------===//

#include "circt/Dialect/Resource/Config/Schema.h"

#include "llvm/ADT/StringMap.h"

#include <cmath>
#include <limits>

using namespace circt::hlsest;
using llvm::StringRef;

namespace {

constexpr double kNoLimit = std::numeric_limits<double>::quiet_NaN();

// Readers, abbreviated so that the table stays readable.
#define BA "--bram-analysis"
#define A2L "--convert-affine-to-loopschedule"
#define APU "--auto-pipeline-unroll"
#define SPLIT "--infer-vitis-split-array"
#define BANK "--memory-banking-bram"
#define FOLD "--vitis-fold"
#define DME "--dead-memory-elimination"
#define LOADER "loader (validation only)"

// clang-format off
const KeySpec kSchema[] = {
  {"version", KeyKind::UInt, "", "Format version of the document; this hls-est reads 1", "", LOADER, "", 1, 1, false},

  //===--------------------------------------------------------------- run
  {"run", KeyKind::Section, "", "Which device, which tool profile, which clock", "S-17", "driver", "", kNoLimit, kNoLimit, false},
  {"run.device", KeyKind::String, "", "Id of a compiled-in device description, or the path of a device file; setting it replaces the device section", "", "loader", "", kNoLimit, kNoLimit, false},
  {"run.tool", KeyKind::String, "", "Id of a compiled-in tool profile, or the path of a profile file; setting it replaces the tool and scheduling sections", "", "loader", "", kNoLimit, kNoLimit, false},
  {"run.clock_ns", KeyKind::Number, "ns", "Target clock period (Vitis create_clock); the call-depth model of the pipeline decision chains operators within it", "S-17", APU ", operator timing models", "", 0.001, kNoLimit, false},

  //===------------------------------------------------------------ device
  {"device", KeyKind::Section, "", "The silicon as data with a data-sheet source: resource classes, memory primitives, shift registers, arithmetic blocks, the logic cell; no tool policy", "", BA ", " A2L ", builtins' checkDevice", "", kNoLimit, kNoLimit, false},
  {"device.id", KeyKind::String, "", "Identity of the description", "", "debug output", "", kNoLimit, kNoLimit, false},
  {"device.part", KeyKind::String, "", "Part number", "", "debug output, math-table check", "", kNoLimit, kNoLimit, false},
  {"device.speed_grade", KeyKind::String, "", "Speed grade", "", "debug output", "", kNoLimit, kNoLimit, true},
  {"device.tool_ids", KeyKind::FreeObject, "", "Identity strings one tool's model needs, per tool (vitis.library); read only by that tool's plugins", "N-09", "vitis-band7 checkDevice", "", kNoLimit, kNoLimit, true},
  {"device.resource_classes", KeyKind::ObjectList, "", "The countable resources; every cost is a vector over these names", "N-01", BA ", validation", "", kNoLimit, kNoLimit, false},
  {"device.resource_classes[].name", KeyKind::String, "", "Class name (BRAM_18K, LUT, M20K, ...)", "N-01", BA, "", kNoLimit, kNoLimit, false},
  {"device.resource_classes[].capacity", KeyKind::NullableUInt, "units", "Units on the part (null: not looked up); recorded, read only by validation", "N-01", LOADER, "", 0, kNoLimit, true},
  {"device.resource_classes[].report_label", KeyKind::String, "", "Column label in the vendor's report", "N-01", "debug output", "", kNoLimit, kNoLimit, true},
  {"device.resource_classes[].equivalent", KeyKind::ResourceVector, "", "What one unit counts in other classes (one MLAB = 10 ALM)", "N-01", "recorded", "", kNoLimit, kNoLimit, true},
  {"device.memories", KeyKind::ObjectList, "", "The memory primitives", "B-01, B-02, B-03, N-02", BA ", " A2L, "", kNoLimit, kNoLimit, false},
  {"device.memories[].id", KeyKind::String, "", "Primitive id (ramb18, lut64x1, usram, ...)", "", BA, "", kNoLimit, kNoLimit, false},
  {"device.memories[].tier", KeyKind::Enum, "", "The tier a storage selector chooses among", "N-02", "storage selectors", "distributed|hard-small|block|large", kNoLimit, kNoLimit, false},
  {"device.memories[].cost", KeyKind::ResourceVector, "", "Cost of one instance", "N-01", "memory mappers", "", kNoLimit, kNoLimit, false},
  {"device.memories[].overhead", KeyKind::ResourceVector, "", "Extra logic per instance (Libero: 36 4LUT + 36 DFF per LSRAM)", "N-06", "memory mappers", "", kNoLimit, kNoLimit, true},
  {"device.memories[].bits", KeyKind::UInt, "bits", "Bits of one instance, parity included", "B-01", "memory mappers, debug (bits_per_bram)", "", 1, kNoLimit, false},
  {"device.memories[].geometries", KeyKind::ObjectList, "", "The legal (width, depth) shapes", "B-02", "memory mappers", "", kNoLimit, kNoLimit, false},
  {"device.memories[].geometries[].width", KeyKind::UInt, "bits", "Data bits per word in this shape, parity included", "B-02", "memory mappers", "", 1, kNoLimit, false},
  {"device.memories[].geometries[].depth", KeyKind::UInt, "words", "Words in this shape", "B-02", "memory mappers", "", 1, kNoLimit, false},
  {"device.memories[].geometries[].byte", KeyKind::UInt, "bits", "Byte-enable width of this shape", "N-13", "reserved", "", 1, kNoLimit, true},
  {"device.memories[].port_configs", KeyKind::ObjectList, "", "The port configurations; a geometry is legal in a configuration when its width <= max_width", "B-03", "memory architecture policies, memory mappers", "", kNoLimit, kNoLimit, false},
  {"device.memories[].port_configs[].name", KeyKind::String, "", "Configuration name (sp, sdp, tdp, sqp, ...)", "B-03", "memory architecture policies", "", kNoLimit, kNoLimit, false},
  {"device.memories[].port_configs[].ports", KeyKind::StringList, "", "The ports, each r, w or rw", "B-03", "memory architecture policies", "r|w|rw", kNoLimit, kNoLimit, false},
  {"device.memories[].port_configs[].max_width", KeyKind::UInt, "bits", "The widest geometry this configuration allows", "B-03", "memory mappers", "", 1, kNoLimit, false},
  {"device.memories[].port_configs[].mixed_width", KeyKind::Bool, "", "Ports of different widths allowed", "", "reserved", "", kNoLimit, kNoLimit, true},
  {"device.memories[].init", KeyKind::Enum, "", "Initial contents the primitive supports (a ROM needs any or no_undef)", "", "storage selectors", "none|zero|any|no_undef", kNoLimit, kNoLimit, false},
  {"device.memories[].read_latency_options", KeyKind::ObjectList, "", "Read latencies the primitive offers", "S-03", "memory architecture policies", "", kNoLimit, kNoLimit, false},
  {"device.memories[].read_latency_options[].cycles", KeyKind::UInt, "cycles", "Read latency (0: asynchronous read)", "S-03", "memory architecture policies", "", 0, kNoLimit, false},
  {"device.memories[].read_latency_options[].max_freq_mhz", KeyKind::Number, "MHz", "Highest clock with this latency", "", "reserved", "", 0, kNoLimit, true},
  {"device.memories[].fmax_mhz", KeyKind::Number, "MHz", "Memory clock limit (double pumping)", "N-03", "reserved", "", 0, kNoLimit, true},
  {"device.memories[].cascade", KeyKind::FreeObject, "", "Hardware cascade {depth, width, max_depth} (UltraScale)", "", "reserved", "", kNoLimit, kNoLimit, true},
  {"device.memories[].ecc", KeyKind::FreeObject, "", "ECC {width, excludes_byte_enable}", "N-13", "reserved", "", kNoLimit, kNoLimit, true},
  {"device.memories[].rdw", KeyKind::StringList, "", "Read-during-write modes", "N-13", "reserved", "", kNoLimit, kNoLimit, true},
  {"device.shift_registers", KeyKind::ObjectList, "", "Shift-register primitives (never derived into the Vitis FIFO cut-offs)", "", "reserved", "", kNoLimit, kNoLimit, true},
  {"device.shift_registers[].id", KeyKind::String, "", "Primitive id", "", "reserved", "", kNoLimit, kNoLimit, false},
  {"device.shift_registers[].max_depth", KeyKind::UInt, "words", "Deepest shift register of one primitive", "", "reserved", "", 1, kNoLimit, false},
  {"device.shift_registers[].width", KeyKind::UInt, "bits", "Width of one primitive", "", "reserved", "", 1, kNoLimit, false},
  {"device.shift_registers[].cost", KeyKind::ResourceVector, "", "Cost of one primitive", "", "reserved", "", kNoLimit, kNoLimit, false},
  {"device.fifos", KeyKind::FreeArray, "", "Hard FIFOs", "N-12", "reserved", "", kNoLimit, kNoLimit, true},
  {"device.arith", KeyKind::ObjectList, "", "DSP and math blocks (Phase 6 timing models and binders)", "", "reserved (Phase 6)", "", kNoLimit, kNoLimit, true},
  {"device.arith[].id", KeyKind::String, "", "Block id", "", "reserved", "", kNoLimit, kNoLimit, false},
  {"device.arith[].cost", KeyKind::ResourceVector, "", "Cost of one block", "", "reserved", "", kNoLimit, kNoLimit, false},
  {"device.arith[].overhead", KeyKind::ResourceVector, "", "Extra logic per block", "N-06", "reserved", "", kNoLimit, kNoLimit, true},
  {"device.arith[].mul", KeyKind::ObjectList, "", "Multiplier fracture modes, widest first", "", "reserved", "", kNoLimit, kNoLimit, true},
  {"device.arith[].mul[].a", KeyKind::UInt, "bits", "Width of operand a", "", "reserved", "", 1, kNoLimit, false},
  {"device.arith[].mul[].b", KeyKind::UInt, "bits", "Width of operand b", "", "reserved", "", 1, kNoLimit, false},
  {"device.arith[].mul[].signed", KeyKind::Enum, "", "Signedness of the mode", "", "reserved", "signed|unsigned|both", kNoLimit, kNoLimit, false},
  {"device.arith[].mul[].count", KeyKind::UInt, "", "Multipliers of this mode per block", "", "reserved", "", 1, kNoLimit, true},
  {"device.arith[].pre_add", KeyKind::UInt, "bits", "Pre-adder width", "", "reserved", "", 1, kNoLimit, true},
  {"device.arith[].acc", KeyKind::UInt, "bits", "Accumulator width", "", "reserved", "", 1, kNoLimit, true},
  {"device.arith[].cascade", KeyKind::FreeObject, "", "Cascade paths", "", "reserved", "", kNoLimit, kNoLimit, true},
  {"device.arith[].hard_fp", KeyKind::StringList, "", "Hard floating-point formats (fp32, fp16, bf16, ...)", "", "reserved", "", kNoLimit, kNoLimit, true},
  {"device.arith[].dot", KeyKind::FreeArray, "", "Dot-product modes", "", "reserved", "", kNoLimit, kNoLimit, true},
  {"device.arith[].fmax_mhz", KeyKind::Number, "MHz", "Block clock limit", "N-03", "reserved", "", 0, kNoLimit, true},
  {"device.logic", KeyKind::Section, "", "The logic cell", "", "reserved (Phase 6)", "", kNoLimit, kNoLimit, true},
  {"device.logic.cell", KeyKind::String, "", "Cell name (LUT6, 4LUT, ALM)", "", "reserved", "", kNoLimit, kNoLimit, false},
  {"device.logic.lut_inputs", KeyKind::UInt, "", "Inputs of one LUT", "", "reserved", "", 1, kNoLimit, false},
  {"device.logic.fracturable", KeyKind::Bool, "", "The LUT splits into two smaller ones", "", "reserved", "", kNoLimit, kNoLimit, true},
  {"device.logic.regs_per_cell", KeyKind::UInt, "", "Registers per cell", "", "reserved", "", 0, kNoLimit, true},
  {"device.logic.cost", KeyKind::ResourceVector, "", "Cost of one cell", "", "reserved", "", kNoLimit, kNoLimit, true},
  {"device.timing", KeyKind::NullableObject, "", "Chaining terms {ff_setup_ns, clk_to_q_ns, connection_ns, mux_ns_per_input} (null: none)", "N-14", "reserved", "", kNoLimit, kNoLimit, true},
  {"device.operator_table", KeyKind::NullablePath, "", "Operator characterisation table (op, widths, period, impl -> latency, delays, occupancy, cost) for timing models other than calyx-fixed; null: none", "N-08", "operator timing models (Phase 6)", "", kNoLimit, kNoLimit, true},

  //===-------------------------------------------------------------- tool
  {"tool", KeyKind::Section, "", "The tool profile: what the HLS tool decides (hls), what the memory mapping back end decides (backend), the report and the default pipeline", "", "every pass", "", kNoLimit, kNoLimit, false},
  {"tool.id", KeyKind::String, "", "Profile id", "", "debug output", "", kNoLimit, kNoLimit, false},
  {"tool.name", KeyKind::String, "", "The modelled tool", "", "debug output", "", kNoLimit, kNoLimit, false},
  {"tool.version", KeyKind::String, "", "Its version", "", "math-table check", "", kNoLimit, kNoLimit, false},
  {"tool.hls", KeyKind::Section, "", "Decisions of the HLS tool", "", "every pass", "", kNoLimit, kNoLimit, false},
  {"tool.hls.options", KeyKind::Section, "", "The run configuration of the modelled tool (the ground-truth settings)", "", APU ", " SPLIT, "", kNoLimit, kNoLimit, false},
  {"tool.hls.options.flow_target", KeyKind::String, "", "Vitis flow_target (recorded)", "", "recorded", "", kNoLimit, kNoLimit, false},
  {"tool.hls.options.pipeline_loops", KeyKind::UInt, "iterations", "config_compile -pipeline_loops: a loop whose nested trip-count products are all <= this is pipelined and everything inside it unrolled; 0 disables the automatic decision", "D-01", APU, "", 0, kNoLimit, false},
  {"tool.hls.options.array_partition", KeyKind::Section, "", "syn.array_partition settings", "Q-01, Q-02, Q-09", SPLIT, "", kNoLimit, kNoLimit, false},
  {"tool.hls.options.array_partition.throughput_driven", KeyKind::Enum, "", "auto: port-pressure partitioning; off: only the automatic partitions (the ground truth); a bare --infer-vitis-split-array takes this value", "Q-01", SPLIT, "auto|off", kNoLimit, kNoLimit, false},
  {"tool.hls.options.array_partition.complete_threshold", KeyKind::UInt, "elements", "Arrays of at most this many elements are completely partitioned (registers)", "Q-02", SPLIT, "", 0, kNoLimit, false},
  {"tool.hls.options.array_partition.include_ports", KeyKind::Bool, "", "Interface arrays are partitioned too", "Q-09", SPLIT, "", kNoLimit, kNoLimit, false},
  {"tool.hls.timing_margin", KeyKind::Section, "", "Clock uncertainty subtracted from the period (one of fraction or ns)", "S-20", APU ", operator timing models", "", kNoLimit, kNoLimit, false},
  {"tool.hls.timing_margin.fraction", KeyKind::Number, "", "Fraction of the period (Vitis default 27%)", "S-20", APU, "", 0, 0.999, true},
  {"tool.hls.timing_margin.ns", KeyKind::Number, "ns", "Absolute margin", "S-20", APU, "", 0, kNoLimit, true},

  {"tool.hls.memory_architecture", KeyKind::Section, "", "Port pools before scheduling, then kind, replication, ROM handling and pricing configuration after it", "K-02..K-14, S-06", A2L ", " BA, "", kNoLimit, kNoLimit, false},
  {"tool.hls.memory_architecture.plugin", KeyKind::PluginName, "", "The MemoryArchitecturePolicy", "K-04", A2L ", " BA, "memory_architecture_policy", kNoLimit, kNoLimit, false},
  {"tool.hls.memory_architecture.untracked_memory_ports", KeyKind::UInt, "ports", "Ports of a memref the scheduler does not track (a function argument, a memref.alloc, a global)", "K-03, K-20", A2L, "", 1, kNoLimit, false},
  {"tool.hls.memory_architecture.port_occupancy_cycles", KeyKind::UInt, "cycles", "Cycles one access holds its port", "K-11", BA, "", 1, kNoLimit, false},
  {"tool.hls.memory_architecture.replication", KeyKind::Section, "", "RAM_1WNR replication", "K-02, K-06, K-07", A2L ", " BA ", " BANK, "", kNoLimit, kNoLimit, false},
  {"tool.hls.memory_architecture.replication.max_copies", KeyKind::UInt, "copies", "At most this many copies of a replicated bank (1: no replication); the scheduler's pool is max_copies * (ports - 1) + 1 slots", "K-02", A2L ", " BA, "", 1, kNoLimit, false},
  {"tool.hls.memory_architecture.replication.max_stores_per_iteration", KeyKind::UInt, "stores", "A bank some loop body stores to more often than this is never replicated", "K-06", A2L ", " BA, "", 0, kNoLimit, false},
  {"tool.hls.memory_architecture.replication.shared_write_port_reads_when_idle", KeyKind::Bool, "", "The shared write port of the copies reads in a cycle without a write (the +1 slot)", "K-02", A2L, "", kNoLimit, kNoLimit, false},
  {"tool.hls.memory_architecture.replication.exclusive_arm_stores_once", KeyKind::Bool, "", "The stores the two arms of one if make count once per iteration, whatever their addresses (off: only a same-address pair)", "", A2L ", " BA ", " BANK, "", kNoLimit, kNoLimit, false},
  {"tool.hls.memory_architecture.replication.callee_stores_per_loop", KeyKind::Bool, "", "A bank passed to a callee whose loop body stores it twice is not replicable in the caller either", "", BANK, "", kNoLimit, kNoLimit, false},
  {"tool.hls.memory_architecture.rom", KeyKind::Section, "", "Read-only memories", "K-08", BA, "", kNoLimit, kNoLimit, false},
  {"tool.hls.memory_architecture.rom.sdp_max_reads", KeyKind::UInt, "reads/cycle", "A ROM read at most this often per cycle is one simple-dual-port memory", "K-08", BA, "", 1, kNoLimit, false},
  {"tool.hls.memory_architecture.rom.copies", KeyKind::Enum, "", "Copies of a ROM read more often (ROM_NP): ceil(n/2), or n-1", "K-08", BA, "ceil_half|n_minus_1", kNoLimit, kNoLimit, false},
  {"tool.hls.memory_architecture.sequential_scope", KeyKind::Section, "", "Ports of a non-pipelined scope that no sequential scheduler scheduled", "K-12..K-14", BA, "", kNoLimit, kNoLimit, false},
  {"tool.hls.memory_architecture.sequential_scope.model", KeyKind::Enum, "", "stretch-pair: two independent accesses of one straight-line stretch share a state; one-port: one access per state", "K-12", BA, "stretch-pair|one-port", kNoLimit, kNoLimit, false},
  {"tool.hls.memory_architecture.port_set_rule", KeyKind::Enum, "", "Where a bank's port set comes from: the selected kind (by_kind), or the per-cycle demand (by_demand, a designer knob)", "K-04, K-05", BA, "by_kind|by_demand", kNoLimit, kNoLimit, false},
  {"tool.hls.memory_architecture.wide_port_sets", KeyKind::PortSetList, "", "Port sets priced at priced_configs.wide (Vitis' SDP test: one port, a read and a write port, two read ports)", "K-05, N-10", BA, "", kNoLimit, kNoLimit, false},
  {"tool.hls.memory_architecture.priced_configs", KeyKind::Section, "", "The port configurations whose max_width prices a bank", "B-03, K-05", BA, "", kNoLimit, kNoLimit, false},
  {"tool.hls.memory_architecture.priced_configs.wide", KeyKind::String, "", "Configuration of a bank whose port set is wide", "B-03", BA, "", kNoLimit, kNoLimit, false},
  {"tool.hls.memory_architecture.priced_configs.narrow", KeyKind::String, "", "Configuration of any other bank and of every replicated copy", "B-03", BA, "", kNoLimit, kNoLimit, false},

  {"tool.hls.implicit_buffers", KeyKind::ObjectList, "", "Sources of RAM no user array accounts for (one entry per source)", "A-01..A-08, B-13, N-12", BA, "", kNoLimit, kNoLimit, false},
  {"tool.hls.implicit_buffers[].source", KeyKind::Enum, "", "What creates the buffer", "N-12", BA, "interface|cluster_fifo|lsu_cache|dataflow_pipo", kNoLimit, kNoLimit, false},
  {"tool.hls.implicit_buffers[].protocol", KeyKind::String, "", "Interface protocol (axi4-mm)", "A-03", BA, "", kNoLimit, kNoLimit, false},
  {"tool.hls.implicit_buffers[].mode", KeyKind::String, "", "The hls.interface mode that selects the entry (m_axi)", "A-03", BA, "", kNoLimit, kNoLimit, false},
  {"tool.hls.implicit_buffers[].plugin", KeyKind::PluginName, "", "The ImplicitBufferModel", "A-06, A-07", BA, "implicit_buffer_model", kNoLimit, kNoLimit, false},
  {"tool.hls.implicit_buffers[].enabled", KeyKind::Bool, "", "Price these buffers (--bram-maxi-adapters overrides)", "A-01", BA, "", kNoLimit, kNoLimit, false},
  {"tool.hls.implicit_buffers[].default_bundle", KeyKind::String, "", "Bundle of a port without bundle=", "A-03", BA, "", kNoLimit, kNoLimit, true},
  {"tool.hls.implicit_buffers[].min_bus_bits", KeyKind::UInt, "bits", "Narrowest adapter data width", "A-04", BA, "", 1, kNoLimit, true},
  {"tool.hls.implicit_buffers[].defaults", KeyKind::Section, "", "Interface pragma defaults", "A-05", BA, "", kNoLimit, kNoLimit, true},
  {"tool.hls.implicit_buffers[].defaults.max_read_burst_length", KeyKind::UInt, "beats", "Default max_read_burst_length", "A-05", BA, "", 1, kNoLimit, false},
  {"tool.hls.implicit_buffers[].defaults.num_read_outstanding", KeyKind::UInt, "", "Default num_read_outstanding", "A-05", BA, "", 1, kNoLimit, false},
  {"tool.hls.implicit_buffers[].defaults.max_write_burst_length", KeyKind::UInt, "beats", "Default max_write_burst_length", "A-05", BA, "", 1, kNoLimit, false},
  {"tool.hls.implicit_buffers[].defaults.num_write_outstanding", KeyKind::UInt, "", "Default num_write_outstanding", "A-05", BA, "", 1, kNoLimit, false},
  {"tool.hls.implicit_buffers[].read_fifo", KeyKind::Section, "", "The read data FIFO (depth = burst x outstanding)", "A-06, B-13", BA, "", kNoLimit, kNoLimit, true},
  {"tool.hls.implicit_buffers[].read_fifo.srl_max_depth", KeyKind::UInt, "words", "A read FIFO at most this deep is shift registers (0 BRAM); a measured Vitis rule", "A-06", BA, "", 0, kNoLimit, false},
  {"tool.hls.implicit_buffers[].read_fifo.mapper", KeyKind::PluginName, "", "The MemoryMapper that prices the FIFO, whatever the main mapper is", "B-13", BA, "memory_mapper", kNoLimit, kNoLimit, false},
  {"tool.hls.implicit_buffers[].read_fifo.priced_config", KeyKind::String, "", "The port configuration it is priced at", "B-13", BA, "", kNoLimit, kNoLimit, false},
  {"tool.hls.implicit_buffers[].read_fifo.confirmed_max_depth", KeyKind::UInt, "words", "Deeper FIFOs are marked unconfirmed in the debug output (never changes a number)", "A-06", BA, "", 0, kNoLimit, false},
  {"tool.hls.implicit_buffers[].write_buffer", KeyKind::Section, "", "The write buffer", "A-07", BA, "", kNoLimit, kNoLimit, true},
  {"tool.hls.implicit_buffers[].write_buffer.free_max_burst", KeyKind::UInt, "beats", "A write burst at most this long needs no buffer RAM; a measured Vitis rule", "A-07", BA, "", 0, kNoLimit, false},
  {"tool.hls.implicit_buffers[].write_buffer.port_width_bits", KeyKind::UInt, "bits", "Longer bursts cost ceil(bus width / this)", "A-07", BA, "", 1, kNoLimit, false},
  {"tool.hls.implicit_buffers[].write_buffer.confirmed_min_burst", KeyKind::UInt, "beats", "Shorter priced bursts are marked unconfirmed (never changes a number)", "A-07", BA, "", 0, kNoLimit, false},
  {"tool.hls.implicit_buffers[].unresolved_call", KeyKind::Enum, "", "What a port passed to a call without a body is assumed to do", "A-08", BA, "rw|none", kNoLimit, kNoLimit, true},

  {"tool.hls.streams", KeyKind::Section, "", "hls::stream objects: one FIFO each (VITIS_NOTES N31)", "", BA, "", kNoLimit, kNoLimit, false},
  {"tool.hls.streams.enabled", KeyKind::Bool, "", "Price the stream objects as FIFOs (--bram-stream-fifos overrides); off prices the handle storage as a RAM", "", BA, "", kNoLimit, kNoLimit, false},
  {"tool.hls.streams.default_depth", KeyKind::UInt, "words", "Depth of a stream without a depth pragma or template argument", "", BA, "", 1, kNoLimit, false},
  {"tool.hls.streams.srl_max_depth", KeyKind::UInt, "words", "FIFOs at most this deep are shift registers at any width", "", BA, "", 0, kNoLimit, false},
  {"tool.hls.streams.srl_max_bits", KeyKind::UInt, "bits", "FIFOs of at most this many bits (depth x width) are shift registers", "", BA, "", 0, kNoLimit, false},
  {"tool.hls.streams.mapper", KeyKind::PluginName, "", "The MemoryMapper that prices a block-RAM FIFO", "", BA, "memory_mapper", kNoLimit, kNoLimit, false},
  {"tool.hls.streams.priced_config", KeyKind::String, "", "The port configuration a FIFO is priced at (never x36)", "", BA, "", kNoLimit, kNoLimit, false},
  {"tool.hls.dataflow_channels", KeyKind::Section, "", "Ping-pong channels of a dataflow region", "", BA, "", kNoLimit, kNoLimit, false},
  {"tool.hls.dataflow_channels.enabled", KeyKind::Bool, "", "Price an array one process writes and a later one reads as a PIPO (--bram-dataflow-channels overrides)", "", BA, "", kNoLimit, kNoLimit, false},
  {"tool.hls.dataflow_channels.default_blocks", KeyKind::UInt, "blocks", "Blocks of a channel without a stream type=pipo depth", "", BA, "", 1, kNoLimit, false},

  {"tool.hls.pipeline_decision", KeyKind::Section, "", "The automatic pipeline / unroll / flatten decision", "D-01..D-12", APU, "", kNoLimit, kNoLimit, false},
  {"tool.hls.pipeline_decision.policy", KeyKind::PluginName, "", "The PipelinePolicy", "D-02, D-07, D-08", APU, "pipeline_policy", kNoLimit, kNoLimit, false},
  {"tool.hls.pipeline_decision.float_loads_perfect", KeyKind::Bool, "", "A read-only inner-invariant floating-point load keeps a nest perfect (flattened, not unrolled)", "D-03", APU, "", kNoLimit, kNoLimit, false},
  {"tool.hls.pipeline_decision.promote_pipelined", KeyKind::Bool, "", "Promote the invariant accesses of the pipelined loop itself to registers after the unroll", "D-06", APU, "", kNoLimit, kNoLimit, false},
  {"tool.hls.pipeline_decision.flatten_across_calls", KeyKind::Bool, "", "Flatten a loop into a pipelined loop of a callee (documented assumption: never)", "D-11", APU, "", kNoLimit, kNoLimit, false},

  {"tool.hls.partitioning", KeyKind::Section, "", "Automatic and inferred array partitioning", "Q-03..Q-08, Q-15", SPLIT ", " BANK, "", kNoLimit, kNoLimit, false},
  {"tool.hls.partitioning.policy", KeyKind::PluginName, "", "The PartitionPolicy", "Q-03, Q-04, Q-08, Q-15", SPLIT, "partition_policy", kNoLimit, kNoLimit, false},
  {"tool.hls.partitioning.constant_index", KeyKind::Section, "", "Rule (b): a dimension every access indexes with a constant", "Q-03", SPLIT, "", kNoLimit, kNoLimit, false},
  {"tool.hls.partitioning.constant_index.min_extent", KeyKind::UInt, "elements", "Smallest extent of such a dimension that is partitioned", "Q-03", SPLIT, "", 1, kNoLimit, false},
  {"tool.hls.partitioning.inference", KeyKind::Section, "", "The td=auto port-pressure search", "Q-06..Q-08", SPLIT, "", kNoLimit, kNoLimit, false},
  {"tool.hls.partitioning.inference.target_ii", KeyKind::UInt, "cycles", "II of a loop without its own", "Q-07", SPLIT, "", 1, kNoLimit, false},
  {"tool.hls.partitioning.inference.ports", KeyKind::Section, "", "Port model of the search, per bank and cycle", "Q-06", SPLIT, "", kNoLimit, kNoLimit, false},
  {"tool.hls.partitioning.inference.ports.any", KeyKind::UInt, "ports", "Accesses of any kind", "Q-06", SPLIT, "", 1, kNoLimit, false},
  {"tool.hls.partitioning.inference.ports.read", KeyKind::UInt, "ports", "Reads", "Q-06", SPLIT, "", 1, kNoLimit, false},
  {"tool.hls.partitioning.inference.ports.write", KeyKind::UInt, "ports", "Writes", "Q-06", SPLIT, "", 1, kNoLimit, false},
  {"tool.hls.partitioning.inference.max_factor", KeyKind::UInt, "", "Largest factor (0: the extent)", "Q-08", SPLIT, "", 0, kNoLimit, false},
  {"tool.hls.partitioning.inference.max_dims", KeyKind::UInt, "", "Dimensions partitioned per array", "Q-08", SPLIT, "", 1, kNoLimit, false},
  {"tool.hls.partitioning.inference.rotating_banks", KeyKind::Bool, "", "A rotating access is charged to one bank (off: to every bank)", "Q-08", SPLIT, "", kNoLimit, kNoLimit, false},
  {"tool.hls.partitioning.inference.max_scanned_factor", KeyKind::UInt, "", "Factors above this are not scanned one by one (a guard)", "Q-08", SPLIT, "", 1, kNoLimit, false},
  {"tool.hls.partitioning.steer_affine_loads", KeyKind::Bool, "", "Unrolled copies of a partitioned load with distinct constant offsets read each bank once", "", BANK, "", kNoLimit, kNoLimit, false},

  {"tool.hls.folding", KeyKind::Section, "", "The tool's constant folding", "F-01..F-03", FOLD, "", kNoLimit, kNoLimit, false},
  {"tool.hls.folding.rule_set", KeyKind::PluginName, "", "The FoldRuleSet: vitis-undef (Vitis' undefined value of x / 0) or zero (x / 0 -> 0)", "F-01, F-02", FOLD, "fold_rule_set", kNoLimit, kNoLimit, false},
  {"tool.hls.folding.canonicalize", KeyKind::Bool, "", "Also apply every dialect's canonicalization in the same rewrite, so a folded zero propagates", "F-03", FOLD, "", kNoLimit, kNoLimit, false},
  {"tool.hls.folding.max_rounds", KeyKind::UInt, "", "Rounds of the fold rewrite at most", "F-03", FOLD, "", 1, kNoLimit, false},

  {"tool.hls.middle_end", KeyKind::Section, "", "The LLVM clean-ups of the tool that change ports and memories", "L-01..L-03, E-02..E-04", A2L ", " DME, "", kNoLimit, kNoLimit, false},
  {"tool.hls.middle_end.licm_hoist_invariant_loads", KeyKind::Bool, "", "LICM: invariant loads move out of the pipelined loop and use none of its ports", "L-01", A2L, "", kNoLimit, kNoLimit, false},
  {"tool.hls.middle_end.licm_hoist_past_calls", KeyKind::Bool, "", "A memref some call takes is still hoisted from a loop without calls", "", A2L, "", kNoLimit, kNoLimit, false},
  {"tool.hls.middle_end.licm_hoist_conditional", KeyKind::Bool, "", "Invariant loads nested in an if of the body are hoisted too (speculated)", "", A2L, "", kNoLimit, kNoLimit, false},
  {"tool.hls.middle_end.merge_if_else_accesses", KeyKind::Bool, "", "A load / store both arms of an if/else make of one address is one access (SimplifyCFG / InstCombine)", "", A2L, "", kNoLimit, kNoLimit, false},
  {"tool.hls.middle_end.gvn_loads", KeyKind::Bool, "", "GVN: a repeated load of one address is one load", "L-02", A2L, "", kNoLimit, kNoLimit, false},
  {"tool.hls.middle_end.store_forwarding", KeyKind::Bool, "", "Store-to-load forwarding and dead-store elimination within a block", "L-03", A2L, "", kNoLimit, kNoLimit, false},
  {"tool.hls.middle_end.dead_memory", KeyKind::Section, "", "Dead-memory elimination", "E-02..E-04", DME, "", kNoLimit, kNoLimit, false},
  {"tool.hls.middle_end.dead_memory.overwritten_stores", KeyKind::Bool, "", "A store a later store of the same access overwrites before any read is deleted", "E-03", DME, "", kNoLimit, kNoLimit, false},
  {"tool.hls.middle_end.dead_memory.dead_calls", KeyKind::Bool, "", "A call of a kept callee whose written arrays are never read is deleted", "", DME, "", kNoLimit, kNoLimit, false},
  {"tool.hls.middle_end.dead_memory.honour_preserve", KeyKind::Bool, "", "hls.preserve keeps a dead array (Vitis: no)", "E-04", DME, "", kNoLimit, kNoLimit, false},
  {"tool.hls.middle_end.dead_memory.global_shared_by_functions_escapes", KeyKind::Bool, "", "A global used by more than one function escapes", "E-02", DME, "", kNoLimit, kNoLimit, false},
  {"tool.hls.inlining", KeyKind::Section, "", "Function inlining", "", "--inline", "", kNoLimit, kNoLimit, false},
  {"tool.hls.inlining.honour_inline_off", KeyKind::Bool, "", "Calls to hls.inline_off callees stay calls (--inline-ignore-inline-off overrides)", "", "--inline", "", kNoLimit, kNoLimit, false},
  {"tool.hls.structs", KeyKind::Section, "", "Disaggregation of struct-typed variables", "", "--split-struct-memrefs", "", kNoLimit, kNoLimit, false},
  {"tool.hls.structs.aggregate", KeyKind::Bool, "", "A variable an AGGREGATE pragma reached is one memory of packed words", "", "--split-struct-memrefs", "", kNoLimit, kNoLimit, false},
  {"tool.hls.structs.globals", KeyKind::Bool, "", "Struct-typed globals are split like locals", "", "--split-struct-memrefs", "", kNoLimit, kNoLimit, false},
  {"tool.hls.structs.scalar_registers", KeyKind::Bool, "", "A member of a single struct variable accessed only at constant positions is registers", "", "--split-struct-memrefs", "", kNoLimit, kNoLimit, false},
  {"tool.hls.structs.through_calls", KeyKind::Bool, "", "A variable passed whole to kept calls is split together with the callees' parameters", "", "--split-struct-memrefs", "", kNoLimit, kNoLimit, false},
  {"tool.hls.narrowing", KeyKind::Section, "", "Element width the tool stores per word", "", "--narrow-ram-widths", "", kNoLimit, kNoLimit, false},
  {"tool.hls.narrowing.stored_ranges", KeyKind::Bool, "", "Narrow to the bits the stored values need", "", "--narrow-ram-widths", "", kNoLimit, kNoLimit, false},
  {"tool.hls.narrowing.load_demand", KeyKind::Bool, "", "Narrow to the low bits the loads' users demand", "", "--narrow-ram-widths", "", kNoLimit, kNoLimit, false},
  {"tool.hls.globals", KeyKind::Section, "", "File-scope arrays", "T-03", BA, "", kNoLimit, kNoLimit, false},
  {"tool.hls.globals.attribute_accesses", KeyKind::Bool, "", "A global's accesses are attributed through its get_global sites (--bram-attribute-globals overrides)", "T-03", BA, "", kNoLimit, kNoLimit, false},
  {"tool.hls.grouping", KeyKind::Section, "", "Several memrefs mapped to one memory", "N-11", BA, "", kNoLimit, kNoLimit, false},
  {"tool.hls.grouping.plugin", KeyKind::PluginName, "", "The MemoryGrouping (identity: one memref, one memory)", "N-11", BA, "memory_grouping", kNoLimit, kNoLimit, false},
  {"tool.hls.math_library", KeyKind::Section, "", "Cost table of the math cores", "N-15", BA, "", kNoLimit, kNoLimit, false},
  {"tool.hls.math_library.table", KeyKind::String, "", "Path of the math-core cost table (math_costs.json format; relative to the file that sets it); empty: math calls cost nothing (--bram-analysis=math-costs= overrides)", "S-04, N-15", BA, "", kNoLimit, kNoLimit, false},

  //===----------------------------------------------------------- backend
  {"tool.backend", KeyKind::Section, "", "What maps memories to primitives (the HLS tool itself for Vitis, logic synthesis for other flows)", "", BA, "", kNoLimit, kNoLimit, false},
  {"tool.backend.id", KeyKind::String, "", "Back-end id", "", "debug output", "", kNoLimit, kNoLimit, false},
  {"tool.backend.storage_selector", KeyKind::Section, "", "Which tier a bank goes to, before scheduling", "B-08, B-09", BA, "", kNoLimit, kNoLimit, false},
  {"tool.backend.storage_selector.plugin", KeyKind::PluginName, "", "The StorageSelector", "B-08", BA, "storage_selector", kNoLimit, kNoLimit, false},
  {"tool.backend.storage_selector.min_block_bits", KeyKind::UInt, "bits", "Words x exact element bits from which a bank is a block RAM", "B-08", BA, "", 0, kNoLimit, false},
  {"tool.backend.storage_selector.inclusive", KeyKind::Bool, "", "A bank of exactly min_block_bits is a block RAM", "B-08", BA, "", kNoLimit, kNoLimit, false},
  {"tool.backend.storage_selector.block", KeyKind::String, "", "Memory id of the block tier", "B-08", BA, "", kNoLimit, kNoLimit, false},
  {"tool.backend.storage_selector.below", KeyKind::String, "", "Tier of a bank below the threshold (priced at 0 of the primary class)", "B-08", BA, "", kNoLimit, kNoLimit, false},
  {"tool.backend.memory_mapper", KeyKind::Section, "", "The rule that turns a bank into primitives", "B-04..B-07", BA, "", kNoLimit, kNoLimit, false},
  {"tool.backend.memory_mapper.plugin", KeyKind::PluginName, "", "The MemoryMapper: vitis-band7, vitis-aspect-min or geometry-min (bram-formula=band|n6 overrides)", "B-07", BA, "memory_mapper", kNoLimit, kNoLimit, false},
  {"tool.backend.memory_mapper.primitive", KeyKind::String, "", "Memory id it maps to", "B-01", BA, "", kNoLimit, kNoLimit, false},
  {"tool.backend.memory_mapper.depth_rounding", KeyKind::Enum, "", "pow2: the address space is priced (2500 words as 4096); exact: the words", "B-04", BA, "pow2|exact", kNoLimit, kNoLimit, false},
  {"tool.backend.memory_mapper.accepted_libraries", KeyKind::StringList, "", "vitis-band7: the Vitis part libraries whose pricing was measured", "B-05", "vitis-band7 checkDevice", "", kNoLimit, kNoLimit, false},
  {"tool.backend.memory_mapper.depth_bands", KeyKind::ObjectList, "", "vitis-band7: the depth bands (max_depth increasing, one beyond band last)", "B-05", BA, "", kNoLimit, kNoLimit, false},
  {"tool.backend.memory_mapper.depth_bands[].max_depth", KeyKind::UInt, "words", "Deepest address space of the band", "B-05", BA, "", 1, kNoLimit, true},
  {"tool.backend.memory_mapper.depth_bands[].beyond", KeyKind::Bool, "", "The band for every deeper address space", "B-05", BA, "", kNoLimit, kNoLimit, true},
  {"tool.backend.memory_mapper.depth_bands[].width", KeyKind::UInt, "bits", "Column width", "B-05", BA, "", 1, kNoLimit, true},
  {"tool.backend.memory_mapper.depth_bands[].sdp_width", KeyKind::UInt, "bits", "Column width of a wide bank", "B-05", BA, "", 1, kNoLimit, true},
  {"tool.backend.memory_mapper.depth_bands[].tdp_width", KeyKind::UInt, "bits", "Column width of a narrow bank", "B-05", BA, "", 1, kNoLimit, true},
  {"tool.backend.memory_mapper.depth_bands[].alternative", KeyKind::Section, "", "A second column shape; the cheaper one is taken", "B-05", BA, "", kNoLimit, kNoLimit, true},
  {"tool.backend.memory_mapper.depth_bands[].alternative.width", KeyKind::UInt, "bits", "Its width", "B-05", BA, "", 1, kNoLimit, false},
  {"tool.backend.memory_mapper.depth_bands[].alternative.stack", KeyKind::UInt, "blocks", "Its blocks per column", "B-05", BA, "", 1, kNoLimit, false},
  {"tool.backend.memory_mapper.depth_bands[].words_per_block", KeyKind::UInt, "words", "beyond: words of one block (columns of address space / this blocks)", "B-05", BA, "", 1, kNoLimit, true},
  {"tool.backend.memory_mapper.mixed_columns", KeyKind::Bool, "", "geometry-min: mix column widths (off, like Vitis)", "", BA, "", kNoLimit, kNoLimit, true},
  {"tool.backend.memory_mapper.depth_stack", KeyKind::Bool, "", "geometry-min: stack shallower blocks (off, like Vitis)", "", BA, "", kNoLimit, kNoLimit, true},

  //===------------------------------------------------------------ report
  {"tool.report", KeyKind::Section, "", "What the report prints and which ground truth it compares with", "N-07", BA, "", kNoLimit, kNoLimit, false},
  {"tool.report.primary_memory_class", KeyKind::String, "", "The class whose count is the bram= number", "N-07", BA, "", kNoLimit, kNoLimit, false},
  {"tool.report.stdout_format", KeyKind::Enum, "", "vitis-bram: kind= / bram= lines and Total BRAM; per-class: also Total <class> for every class", "N-07", BA, "vitis-bram|per-class", kNoLimit, kNoLimit, false},
  {"tool.report.reference_stage", KeyKind::Enum, "", "Which ground-truth number the profile may be compared with", "N-07", "harness", "hls_estimate|post_synthesis|post_fit", kNoLimit, kNoLimit, false},
  {"tool.report.classes", KeyKind::StringList, "", "The classes printed and compared", "N-07", BA, "", kNoLimit, kNoLimit, false},
  {"tool.pipeline", KeyKind::String, "", "The default pass pipeline (hls-est --default-pipeline; the harness's DEFAULT_PIPELINE)", "R-01", "driver, harness", "", kNoLimit, kNoLimit, false},

  //===--------------------------------------------------------- frontend
  {"frontend", KeyKind::Section, "", "What the MLIR input is assumed to look like", "", "every pass", "", kNoLimit, kNoLimit, false},
  {"frontend.index_bits", KeyKind::UInt, "bits", "Width of an index element (cgeist lowers C indices to index)", "B-10", BA, "", 1, 1024, false},
  {"frontend.element_types", KeyKind::StringList, "", "Element types that make an array of words (informational)", "B-11, C-03", "recorded", "int|float|index", kNoLimit, kNoLimit, false},
  {"frontend.user_storage_pragmas", KeyKind::StringList, "", "Attributes by which the user decided an array's storage (no automatic partition)", "Q-05", SPLIT, "", kNoLimit, kNoLimit, false},

  //===------------------------------------------------------- scheduling
  {"scheduling", KeyKind::Section, "", "Operator timing, dependences, schedulers and binding", "S-01..S-22", A2L ", " APU, "", kNoLimit, kNoLimit, false},
  {"scheduling.timing", KeyKind::Section, "", "The operator timing model", "S-01..S-05", A2L, "", kNoLimit, kNoLimit, false},
  {"scheduling.timing.model", KeyKind::PluginName, "", "The OperatorTimingModel", "S-02", A2L, "operator_timing_model", kNoLimit, kNoLimit, false},
  {"scheduling.timing.operator_latencies", KeyKind::IntMap, "cycles", "Latency per operator class of calyx-fixed (unconfirmed against Vitis); call / kept_call -1: the loop stays sequential", "S-01, S-03, S-04", A2L ", " APU, "", -1, kNoLimit, false},
  {"scheduling.dependences", KeyKind::Section, "", "Which dependences constrain the schedule", "S-11..S-13", A2L, "", kNoLimit, kNoLimit, false},
  {"scheduling.dependences.model", KeyKind::PluginName, "", "The DependenceModel (cached-o1 keeps OPEN_ISSUES O1)", "S-11", A2L, "dependence_model", kNoLimit, kNoLimit, false},
  {"scheduling.modulo", KeyKind::Section, "", "The modulo scheduler of pipelined loops", "S-08, S-10", A2L, "", kNoLimit, kNoLimit, false},
  {"scheduling.modulo.model", KeyKind::PluginName, "", "The ModuloScheduler", "S-10", A2L, "modulo_scheduler", kNoLimit, kNoLimit, false},
  {"scheduling.modulo.fast_threshold", KeyKind::UInt, "ops", "greedy-simplex: more resource-limited operations than this go to the greedy scheduler (0: always)", "S-08", A2L, "", 0, kNoLimit, false},
  {"scheduling.modulo.fast_ops_threshold", KeyKind::UInt, "ops", "greedy-simplex: more operations than this go to the greedy scheduler (0: no rule)", "S-08", A2L, "", 0, kNoLimit, false},
  {"scheduling.modulo.max_ii_bumps", KeyKind::UInt, "", "II increments the greedy scheduler tries", "S-08, R-06", A2L, "", 0, kNoLimit, false},
  {"scheduling.modulo.user_ii_target", KeyKind::Bool, "", "A loop with a user pipeline II=N > 1 is scheduled at N when it could start more often", "", A2L, "", kNoLimit, kNoLimit, false},
  {"scheduling.sequential", KeyKind::Section, "", "The scheduler of non-pipelined regions", "K-12..K-14, S-22", A2L, "", kNoLimit, kNoLimit, false},
  {"scheduling.sequential.model", KeyKind::PluginName, "", "The SequentialScheduler (none: the stretch-pair rule applies)", "S-22", A2L, "sequential_scheduler", kNoLimit, kNoLimit, false},
  {"scheduling.binding", KeyKind::Section, "", "Operator binding and sharing", "S-21", A2L, "", kNoLimit, kNoLimit, false},
  {"scheduling.binding.model", KeyKind::PluginName, "", "The Binder (none: nothing is bound)", "S-21", A2L, "binder", kNoLimit, kNoLimit, false},
  {"scheduling.emit_detail", KeyKind::Bool, "", "Write hls.op_timing on every scheduled operation (inspection only; never changes a number)", "S-21, C-02", A2L, "", kNoLimit, kNoLimit, false},
  {"scheduling.call_depth", KeyKind::Section, "", "The ASAP chaining model of the depth of one call of a loop-free callee in a pipelined loop (Vitis 2025.1 xc7z020-1 delays)", "", APU, "", kNoLimit, kNoLimit, false},
  {"scheduling.call_depth.load_data_ns", KeyKind::Number, "ns", "A load's data arrives this far into the cycle after it issues", "", APU, "", 0, kNoLimit, false},
  {"scheduling.call_depth.logic_ns", KeyKind::Number, "ns", "and / or / xor", "", APU, "", 0, kNoLimit, false},
  {"scheduling.call_depth.select_ns", KeyKind::Number, "ns", "select", "", APU, "", 0, kNoLimit, false},
  {"scheduling.call_depth.variable_shift_ns", KeyKind::Number, "ns", "A shift by a variable amount", "", APU, "", 0, kNoLimit, false},
  {"scheduling.call_depth.constant_multiplier_ns", KeyKind::Number, "ns", "A multiply by a constant with three or more set bits (unconfirmed)", "", APU, "", 0, kNoLimit, false},
  {"scheduling.call_depth.narrow_multiply_max_bits", KeyKind::UInt, "bits", "Multiplies of two variables up to this width take narrow_multiply_cycles; wider ones the multicycle latency", "", APU, "", 1, kNoLimit, false},
  {"scheduling.call_depth.narrow_multiply_cycles", KeyKind::UInt, "cycles", "Latency of such a multiply", "", APU, "", 0, kNoLimit, false},
  {"scheduling.call_depth.ports_per_memory", KeyKind::UInt, "ports", "Accesses of one memory per cycle", "", APU, "", 1, kNoLimit, false},
  {"scheduling.call_depth.index_bits", KeyKind::UInt, "bits", "Width an index value is timed at (Vitis narrows addresses)", "", APU, "", 1, kNoLimit, false},
  {"scheduling.call_depth.carry_chain_ns", KeyKind::ObjectList, "", "Adder / subtractor / comparator delay by width (the last band has no max_bits)", "", APU, "", kNoLimit, kNoLimit, false},
  {"scheduling.call_depth.carry_chain_ns[].max_bits", KeyKind::UInt, "bits", "Widest operand of the band", "", APU, "", 1, kNoLimit, true},
  {"scheduling.call_depth.carry_chain_ns[].ns", KeyKind::Number, "ns", "Delay", "", APU, "", 0, kNoLimit, false},
  {"scheduling.call_depth.ternary_adder_ns", KeyKind::ObjectList, "", "Three-input adder delay by width", "", APU, "", kNoLimit, kNoLimit, false},
  {"scheduling.call_depth.ternary_adder_ns[].max_bits", KeyKind::UInt, "bits", "Widest result of the band", "", APU, "", 1, kNoLimit, true},
  {"scheduling.call_depth.ternary_adder_ns[].ns", KeyKind::Number, "ns", "Delay", "", APU, "", 0, kNoLimit, false},

  //===---------------------------------------------------------- plugins
  {"plugins", KeyKind::FreeObject, "", "plugins.<name>: a section owned by the external plugin of that name, validated by it", "", "plugins", "", kNoLimit, kNoLimit, false},
};
// clang-format on

#undef BA
#undef A2L
#undef APU
#undef SPLIT
#undef BANK
#undef FOLD
#undef DME
#undef LOADER

const char *const kInterfaceKeys[] = {
    "storage_selector",       "memory_architecture_policy",
    "memory_mapper",          "memory_grouping",
    "implicit_buffer_model",  "pipeline_policy",
    "partition_policy",       "fold_rule_set",
    "operator_timing_model",  "dependence_model",
    "modulo_scheduler",       "sequential_scheduler",
    "binder"};

PluginNameCheck &pluginNameCheck() {
  static PluginNameCheck check;
  return check;
}

PluginConfigCheck &pluginConfigCheck() {
  static PluginConfigCheck check;
  return check;
}

} // namespace

llvm::ArrayRef<KeySpec> circt::hlsest::configSchema() { return kSchema; }

const KeySpec *circt::hlsest::findKeySpec(StringRef path) {
  static const llvm::StringMap<const KeySpec *> index = [] {
    llvm::StringMap<const KeySpec *> m;
    for (const KeySpec &k : kSchema)
      m[k.path] = &k;
    return m;
  }();
  auto it = index.find(path);
  return it == index.end() ? nullptr : it->second;
}

StringRef circt::hlsest::keyKindName(KeyKind kind) {
  switch (kind) {
  case KeyKind::Section:
    return "object";
  case KeyKind::ObjectList:
    return "array of objects";
  case KeyKind::FreeObject:
    return "object (free-form)";
  case KeyKind::FreeArray:
    return "array (free-form)";
  case KeyKind::Bool:
    return "bool";
  case KeyKind::Int:
    return "int";
  case KeyKind::UInt:
    return "uint";
  case KeyKind::Number:
    return "number";
  case KeyKind::String:
    return "string";
  case KeyKind::Enum:
    return "enum";
  case KeyKind::PluginName:
    return "plugin name";
  case KeyKind::StringList:
    return "array of strings";
  case KeyKind::PortSetList:
    return "array of port sets";
  case KeyKind::ResourceVector:
    return "resource vector";
  case KeyKind::IntMap:
    return "map of int";
  case KeyKind::NullableUInt:
    return "uint or null";
  case KeyKind::NullablePath:
    return "path or null";
  case KeyKind::NullableObject:
    return "object or null";
  }
  return "?";
}

llvm::ArrayRef<const char *> circt::hlsest::pluginInterfaceKeys() {
  return kInterfaceKeys;
}

void circt::hlsest::setPluginNameCheck(PluginNameCheck check) {
  pluginNameCheck() = std::move(check);
}

const PluginNameCheck &circt::hlsest::getPluginNameCheck() {
  return pluginNameCheck();
}

void circt::hlsest::setPluginConfigCheck(PluginConfigCheck check) {
  pluginConfigCheck() = std::move(check);
}

const PluginConfigCheck &circt::hlsest::getPluginConfigCheck() {
  return pluginConfigCheck();
}
