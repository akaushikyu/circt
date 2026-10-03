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
  {"tool.hls.memory_architecture.iteration_private_registers", KeyKind::Bool, "", "A local array, or a bank of a partitioned one, whose every access lies in the body of one loop L at one address that is an injective affine function of L's index and of values defined outside L (the same in every access, invariant in every loop nested in L), and whose first access in L's body is an unconditional store (every loop between L and it of constant trip count >= 1), holds only values one iteration of L writes and reads: it becomes registers, no memory (LLVM LICM promotion, store forwarding and dead-alloca removal in reflow; VITIS_NOTES N92, kernels w9r12p_rp_base, w9r12rv_n92_flat / n92_const2: Vitis no memory; rp_later / rp_nopart / w9r12rv_n92_varinit stay memories)", "", BANK, "", kNoLimit, kNoLimit, true},
  {"tool.hls.memory_architecture.one_loop_read_write_sdp", KeyKind::Bool, "", "A bank whose every access lies in one pipelined loop with one read and one write per cycle, or whose one read per iteration lies in one pipelined loop with at most II writes per iteration while every other loop only writes it, at most once per cycle, is bound to a read-only and a write-only port (RAM_S2P, simple dual port: x36 allowed); a measured Vitis rule (VITIS_NOTES N90 (c), kernels w9r11i_gd_f / gd_h, w9r11rev_sdp_w / gd_pre / gd_post: RAM_AUTO_1R1W 512x32 = 1; with another loop reading the array it stays x18: gd_a / gd_b / gd_g = 2; off: RAM_2P, x18)", "K-04, K-05", BA, "", kNoLimit, kNoLimit, true},
  {"tool.hls.memory_architecture.partitioned_argument_bank_ports", KeyKind::Bool, "", "A function argument with an array_partition pragma (its own, or that of a kept callee's parameter) has one port pool per bank in the scheduler: accesses whose bank is a constant never share a port with another bank's accesses, and an access whose bank is not a constant takes a port of every bank (VITIS_NOTES N88; kernels w9r11p_sa_r8 / sa_2d28 / sa_cpt, w9r11rev_pa_var3; off: one pool for the whole argument)", "K-03", A2L, "", kNoLimit, kNoLimit, true},
  {"tool.hls.memory_architecture.port_occupancy_cycles", KeyKind::UInt, "cycles", "Cycles one access holds its port", "K-11", BA, "", 1, kNoLimit, false},
  {"tool.hls.memory_architecture.replication", KeyKind::Section, "", "RAM_1WNR replication", "K-02, K-06, K-07", A2L ", " BA ", " BANK, "", kNoLimit, kNoLimit, false},
  {"tool.hls.memory_architecture.replication.max_copies", KeyKind::UInt, "copies", "At most this many copies of a replicated bank (1: no replication); the scheduler's pool is max_copies * (ports - 1) + 1 slots", "K-02", A2L ", " BA, "", 1, kNoLimit, false},
  {"tool.hls.memory_architecture.replication.max_stores_per_iteration", KeyKind::UInt, "stores", "A bank some loop body stores to more often than this is never replicated", "K-06", A2L ", " BA, "", 0, kNoLimit, false},
  {"tool.hls.memory_architecture.replication.shared_write_port_reads_when_idle", KeyKind::Bool, "", "The shared write port of the copies reads in a cycle without a write (the +1 slot)", "K-02", A2L, "", kNoLimit, kNoLimit, false},
  {"tool.hls.memory_architecture.replication.exclusive_arm_stores_once", KeyKind::Bool, "", "The stores the two arms of one if make count once per iteration, whatever their addresses (off: only a same-address pair)", "P-10", A2L ", " BA ", " BANK, "", kNoLimit, kNoLimit, false},
  {"tool.hls.memory_architecture.replication.port_bound_several_arrays", KeyKind::Bool, "", "A callee parameter whose call sites bind two or more different arrays is read through the module's own ports even with one instance: those arrays are never replicated for the callee's accesses (VITIS_NOTES N75; off: only a callee instantiated at more than one place)", "K-02", A2L ", " BA, "", kNoLimit, kNoLimit, true},
  {"tool.hls.memory_architecture.replication.port_bound_writable_globals", KeyKind::Bool, "", "A written global or function-static array is never replicated: its accesses, also those of a callee reading it through a parameter, go through its two ports and the loop II rises (VITIS_NOTES N85; off: such an array is replicated like a local)", "K-02", A2L ", " BA, "", kNoLimit, kNoLimit, true},
  {"tool.hls.memory_architecture.replication.rotating_reads_full_copies", KeyKind::Bool, "", "A replicable bank read in a pipelined loop that does not write it only by steered reads (unrolled copies of one read whose bank is chosen at run time) gets ceil(R / II) copies, one more than the shared-write-port rule (VITIS_NOTES N115: kernel w9r15p_rc_rot 16 copies against rc_fix 15; NeuroFPGA padded_A). Off by default: polybench_pragmas k3mm tmp2, 64 steered reads per bank at II 4, has 15 copies in Vitis (OPEN_ISSUES O153)", "K-02", A2L ", " BA, "", kNoLimit, kNoLimit, true},
  {"tool.hls.memory_architecture.replication.user_ram_1wnr_replicable", KeyKind::Bool, "", "A user bind_storage type=ram_1wnr makes the bank replicable even when a loop stores it more than once per iteration; that loop's II rises instead (VITIS_NOTES N113: kernels w9r15p_bw_1wnr 12 against bw_none 4; FocusedACO route). Off by default: on FocusedACO it needs N114 (exclusive predicated loads share a port slot, unconfirmed) to stay in band", "K-02", A2L ", " BA, "", kNoLimit, kNoLimit, true},
  {"tool.hls.memory_architecture.replication.callee_stores_per_loop", KeyKind::Bool, "", "A bank passed to a callee whose loop body stores it twice is not replicable in the caller either", "P-10", BANK, "", kNoLimit, kNoLimit, false},
  {"tool.hls.memory_architecture.replication.caller_stores_per_loop", KeyKind::Bool, "", "A callee's memref parameter is replicable for the callee's loops only when the arrays its call sites pass are: a caller loop (or another callee of that array) storing them more than once per iteration makes the parameter a 2-port memory for the scheduler too; a measured Vitis rule (VITIS_NOTES N99; kernels w9r13p_nr_call / nr_call1: 16 caller stores per iteration, the callee's reader II 8; off: a callee parameter's replicability comes from the callee alone)", "P-10", BANK, "", kNoLimit, kNoLimit, true},
  {"tool.hls.memory_architecture.rom", KeyKind::Section, "", "Read-only memories", "K-08", BA, "", kNoLimit, kNoLimit, false},
  {"tool.hls.memory_architecture.rom.sdp_max_reads", KeyKind::UInt, "reads/cycle", "A ROM read at most this often per cycle is one simple-dual-port memory", "K-08", BA, "", 1, kNoLimit, false},
  {"tool.hls.memory_architecture.rom.sequential_state_reads", KeyKind::Bool, "", "In a sequential (non-pipelined) scope a ROM's reads issue as soon as their addresses are ready: the reads of one straight-line stretch at one dependence depth (the longest chain of reads of the stretch their address is computed from) share a state, and the ROM needs that many read ports (rom.copies copies above sdp_max_reads); a measured Vitis rule (VITIS_NOTES N93, kernels w9r12p_rom_s2 / s3 / s4 / s8: 2 / 3 / 4 / 8 independent reads -> 1 / 2 / 2 / 4 ROM copies, rom_chain4: 1); off: two reads per state at most (N12)", "K-08", BA, "", kNoLimit, kNoLimit, true},
  {"tool.hls.memory_architecture.rom.copies", KeyKind::Enum, "", "Copies of a ROM read more often (ROM_NP): ceil(n/2), or n-1", "K-08", BA, "ceil_half|n_minus_1", kNoLimit, kNoLimit, false},
  {"tool.hls.memory_architecture.sequential_scope", KeyKind::Section, "", "Ports of a non-pipelined scope that no sequential scheduler scheduled", "K-12..K-14", BA, "", kNoLimit, kNoLimit, false},
  {"tool.hls.memory_architecture.sequential_scope.model", KeyKind::Enum, "", "stretch-pair: two independent accesses of one straight-line stretch share a state; one-port: one access per state", "K-12", BA, "stretch-pair|one-port", kNoLimit, kNoLimit, false},
  {"tool.hls.memory_architecture.sequential_scope.loads_before_consumer", KeyKind::Bool, "", "stretch-pair: two independent reads share a state only when their first consumers start in the same cycle of the stretch (multi-cycle operations: multiplies of two variables, divisions, floating point, math, calls, loads); a measured Vitis rule (VITIS_NOTES N101, kernels w9r13fix_sq_mul / sq_chain / sq_fadd: 1 port, sq_add / sq_mul2 / sq_store: 2); off: any two independent accesses (N12)", "K-12", BA, "", kNoLimit, kNoLimit, true},
  {"tool.hls.memory_architecture.port_set_rule", KeyKind::Enum, "", "Where a bank's port set comes from: the selected kind (by_kind), or the per-cycle demand (by_demand, a designer knob)", "K-04, K-05, P-15", BA, "by_kind|by_demand", kNoLimit, kNoLimit, false},
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
  {"tool.hls.implicit_buffers[].max_bus_bits", KeyKind::UInt, "bits", "Widest adapter data width (AXI4 allows up to 1024 bits; a wider element takes several beats, VITIS_NOTES N56)", "A-04", BA, "", 1, kNoLimit, true},
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
  {"tool.hls.implicit_buffers[].read_fifo.per_channel", KeyKind::Bool, "", "One read FIFO per distinct channel= of the bundle's reading ports, else one per bundle; a measured Vitis rule (VITIS_NOTES N56)", "A-06", BA, "", kNoLimit, kNoLimit, true},
  {"tool.hls.implicit_buffers[].read_fifo.cast_load_width", KeyKind::Bool, "", "The FIFO width counts loads through a pointer cast (reinterpret_cast<ap_uint<512>*>), else only the declared element; a measured Vitis rule (VITIS_NOTES N56)", "A-06", BA, "", kNoLimit, kNoLimit, true},
  {"tool.hls.implicit_buffers[].read_fifo.power_of_two_width", KeyKind::Bool, "", "The read FIFO width (widest read access, at least the bus minimum) is rounded up to a power of two before the FIFO is priced, max_bus_bits applying after the rounding; a measured Vitis rule (VITIS_NOTES N63)", "A-06", BA, "", kNoLimit, kNoLimit, true},
  {"tool.hls.implicit_buffers[].write_buffer", KeyKind::Section, "", "The write buffer", "A-07", BA, "", kNoLimit, kNoLimit, true},
  {"tool.hls.implicit_buffers[].write_buffer.free_max_burst", KeyKind::UInt, "beats", "A write burst at most this long needs no buffer RAM; a measured Vitis rule", "A-07", BA, "", 0, kNoLimit, false},
  {"tool.hls.implicit_buffers[].write_buffer.port_width_bits", KeyKind::UInt, "bits", "Longer bursts cost ceil(bus width / this)", "A-07", BA, "", 1, kNoLimit, false},
  {"tool.hls.implicit_buffers[].write_buffer.confirmed_min_burst", KeyKind::UInt, "beats", "Shorter priced bursts are marked unconfirmed (never changes a number)", "A-07", BA, "", 0, kNoLimit, false},
  {"tool.hls.implicit_buffers[].unresolved_call", KeyKind::Enum, "", "What a port passed to a call without a body is assumed to do", "A-08", BA, "rw|none", kNoLimit, kNoLimit, true},
  {"tool.hls.implicit_buffers[].bus_requests", KeyKind::Section, "", "The requests one bundle accepts per cycle from a pipelined loop (a modulo-scheduler resource per bundle and direction)", "", A2L, "", kNoLimit, kNoLimit, true},
  {"tool.hls.implicit_buffers[].bus_requests.read_per_cycle", KeyKind::UInt, "", "Read requests per cycle and bundle: a pipelined loop with n reads of the bundle's ports per iteration has II >= n / this; a measured Vitis rule (VITIS_NOTES N95; kernels w9r13p_mx_r8: 8 reads, II 8; 0: unlimited)", "", A2L, "", 0, kNoLimit, false},
  {"tool.hls.implicit_buffers[].bus_requests.through_calls", KeyKind::Bool, "", "The request limits also hold in a callee for a memref parameter that every call site binds to a port of one bundle (through the caller's own parameters); a measured Vitis rule (VITIS_NOTES N95, kernel w9r13rev_mx_callee: 8 reads per iteration in an inline-off load function, II 8; off: only the top function's ports)", "", A2L ", " BANK, "", kNoLimit, kNoLimit, true},
  {"tool.hls.implicit_buffers[].bus_requests.write_per_cycle", KeyKind::UInt, "", "Write requests per cycle and bundle (VITIS_NOTES N95; kernels w9r13p_mx_w8 / mx_w4x2: 8 writes to one bundle, II 8; 4 to each of two, II 4; 0: unlimited)", "", A2L, "", 0, kNoLimit, false},

  {"tool.hls.streams", KeyKind::Section, "", "hls::stream objects: one FIFO each (VITIS_NOTES N31)", "P-06", BA, "", kNoLimit, kNoLimit, false},
  {"tool.hls.streams.enabled", KeyKind::Bool, "", "Price the stream objects as FIFOs (--bram-stream-fifos overrides); off prices the handle storage as a RAM", "P-06", BA, "", kNoLimit, kNoLimit, false},
  {"tool.hls.streams.default_depth", KeyKind::UInt, "words", "Depth of a stream without a depth pragma or template argument", "P-06", BA, "", 1, kNoLimit, false},
  {"tool.hls.streams.srl_max_depth", KeyKind::UInt, "words", "FIFOs at most this deep are shift registers at any width", "P-06", BA, "", 0, kNoLimit, false},
  {"tool.hls.streams.srl_max_bits", KeyKind::UInt, "bits", "FIFOs of at most this many bits (depth x width) are shift registers", "P-06", BA, "", 0, kNoLimit, false},
  {"tool.hls.streams.mapper", KeyKind::PluginName, "", "The MemoryMapper that prices a block-RAM FIFO", "P-06", BA, "memory_mapper", kNoLimit, kNoLimit, false},
  {"tool.hls.streams.priced_config", KeyKind::String, "", "The port configuration a FIFO is priced at (never x36)", "P-06", BA, "", kNoLimit, kNoLimit, false},
  {"tool.hls.streams.dataflow_argument_fifos", KeyKind::Bool, "", "A dataflow function forwards each scalar / m_axi pointer argument a later process reads through a FIFO <arg>_c, depth = processes on the longest channel path to the reader (+1 when the first process does not read it); priced as a stream FIFO (VITIS_NOTES N54)", "P-06", BA, "", kNoLimit, kNoLimit, true},
  {"tool.hls.streams.distinct_element_instances", KeyKind::Bool, "", "Calls of a kept function on distinct constant elements of an array of streams are concurrent: one instance each (VITIS_NOTES N59)", "P-06", "--bram-analysis, --memory-banking-bram", "", kNoLimit, kNoLimit, true},
  {"tool.hls.streams.declared_element_bits", KeyKind::Bool, "", "A FIFO is as wide as the packed C++ element cgeist records (hls.stream_element_bits: a struct is the sum of its members, bool 1 bit), else the IR type's packed bits (VITIS_NOTES N58)", "P-06", BA, "", kNoLimit, kNoLimit, true},
  {"tool.hls.streams.stream_pragma_arrays", KeyKind::Bool, "", "A local array of a dataflow region with #pragma HLS stream (type fifo or none) and a depth is one FIFO of that depth at the element width, priced as a stream FIFO, instead of a memory; a measured Vitis rule (VITIS_NOTES N67)", "", BA, "", kNoLimit, kNoLimit, true},
  {"tool.hls.dataflow_channels", KeyKind::Section, "", "Ping-pong channels of a dataflow region", "P-08", BA, "", kNoLimit, kNoLimit, false},
  {"tool.hls.dataflow_channels.enabled", KeyKind::Bool, "", "Price an array one process writes and a later one reads as a PIPO (--bram-dataflow-channels overrides)", "P-08", BA, "", kNoLimit, kNoLimit, false},
  {"tool.hls.dataflow_channels.default_blocks", KeyKind::UInt, "blocks", "Blocks of a channel without a stream type=pipo depth", "P-08", BA, "", 1, kNoLimit, false},
  {"tool.hls.dataflow_channels.through_nested_regions", KeyKind::Bool, "", "An array exchanged by the processes of a dataflow region stays a channel of that region when a process accesses it from inside its own nested dataflow region (VITIS_NOTES N84; off: no channel)", "P-08", BA, "", kNoLimit, kNoLimit, true},
  {"tool.hls.dataflow_channels.promoted_invariant_accesses", KeyKind::Bool, "", "The accesses a pipelined loop makes to a channel bank at one address that does not change in the loop (a read-modify-write of a completely partitioned dimension whose other index is the enclosing row: X[i][col[a]] += v) are promoted to a register: loaded before the loop, stored after it, so they give no second port inside the loop; two such loops that follow each other in one block without a loop between them do give one (the store-back of the first and the preload of the second share a state); a measured Vitis rule (VITIS_NOTES N105; kernels w9r14p_pp_unr4 / pp_nomask separate, pp_mid single; class_ece8893 mizanur Lab3; off: any two accesses of one pipelined iteration)", "", BA, "", kNoLimit, kNoLimit, true},

  {"tool.hls.pipeline_decision", KeyKind::Section, "", "The automatic pipeline / unroll / flatten decision", "D-01..D-12", APU, "", kNoLimit, kNoLimit, false},
  {"tool.hls.pipeline_decision.policy", KeyKind::PluginName, "", "The PipelinePolicy", "D-02, D-07, D-08", APU, "pipeline_policy", kNoLimit, kNoLimit, false},
  {"tool.hls.pipeline_decision.float_loads_perfect", KeyKind::Bool, "", "A read-only inner-invariant floating-point load keeps a nest perfect (flattened, not unrolled)", "D-03", APU, "", kNoLimit, kNoLimit, false},
  {"tool.hls.pipeline_decision.promote_pipelined", KeyKind::Bool, "", "Promote the invariant accesses of the pipelined loop itself to registers after the unroll", "D-06", APU, "", kNoLimit, kNoLimit, false},
  {"tool.hls.pipeline_decision.flatten_across_calls", KeyKind::Bool, "", "Flatten a loop into a pipelined loop of a callee (documented assumption: never); reserved: only false is implemented, true is refused", "D-11", APU, "", kNoLimit, kNoLimit, false},
  {"tool.hls.pipeline_decision.sink_parent_code", KeyKind::Bool, "", "The straight-line code (with memory accesses, no loops) before the child loop in the body of a loop flattened into a pipeline runs in the pipeline under a first-iteration guard, so its accesses count in the pipeline's port demand and schedule; a measured Vitis rule (VITIS_NOTES N65)", "", A2L, "", kNoLimit, kNoLimit, true},
  {"tool.hls.pipeline_decision.sink_parent_trailing_code", KeyKind::Bool, "", "The straight-line code after the child loop in the body of a loop flattened into a pipeline (memory accesses, register code, calls of functions without a body such as a stream write; no loops) runs in the pipeline under a last-iteration guard, so its accesses count in the pipeline's port demand and schedule; a measured Vitis rule (VITIS_NOTES N97 (b); kernel w9r13p_st_row: the 64 packing reads of a struct written to a stream, t RAM_1WNR 32; class_ece8893 anuvab / ayush lab2 rOut; off: the code stays after the pipelined loop)", "", A2L, "", kNoLimit, kNoLimit, true},
  {"tool.hls.pipeline_decision.sink_parent_trailing_stores", KeyKind::Bool, "", "sink_parent_trailing_code also sinks trailing code that writes memory (an array or scalar store); a measured Vitis rule for the default off (W9r14 review kernel w9r14rv_st_arr: stores to an output array after the child loop, Vitis disables the flatten, [HLS 214-437], 2 BRAM; sunk: 8); only a stream write after the loop is measured to flatten (N97 (b)); on: the W9r14-impl behaviour", "", A2L, "", kNoLimit, kNoLimit, true},
  {"tool.hls.pipeline_decision.fold_unrolled_guards", KeyKind::Bool, "", "After the unroll decisions, an if whose condition is false (or true) for every value once an unrolled copy's constant index is substituted loses its dead arm, so the accesses of that arm take no port and no schedule slot: an affine.if, or an scf.if whose condition is an affine comparison of loop variables (arith add / sub / constant multiply / rem / div, C's normalised %, and / or); in the then arm of an affine.if left, an operand an equality of its set fixes is that constant (an address it computes becomes invariant); a measured Vitis rule (VITIS_NOTES N89; kernels w9r11p_sa_cnd2, w9r11rev_fg_mod / fg_unr; off: the copy's guarded accesses stay)", "", APU, "", kNoLimit, kNoLimit, true},
  {"tool.hls.pipeline_decision.fold_nested_constant_guards", KeyKind::Bool, "", "fold_unrolled_guards also substitutes guard operands computed from constants through nested affine.apply and index arithmetic (an unrolled copy's apply of apply of a constant), so a guard whose operands are all constants folds (OPEN_ISSUES O151: nikhil_p lab2 kernel_attention_V, V_lcl read 7 times on banks 0..3 and 6 times on 4..15 as in Vitis; off: only a constant or a one-level apply of constants)", "", APU, "", kNoLimit, kNoLimit, true},
  {"tool.hls.pipeline_decision.pipeline_off_sequential", KeyKind::Bool, "", "An innermost loop under `pipeline off` stays a sequential loop in --convert-affine-to-loopschedule (as a runtime-trip loop already did): its body is a state machine, so the sequential port model (VITIS_NOTES N12) and the ROM copies of one state (N93) apply, not a modulo schedule's replication; a measured Vitis rule (kernel w9r12rv_n93_loop: four independent ROM reads per iteration under pipeline off, Vitis 2 ROM copies; off: the loop is scheduled as a pipeline, 1)", "", A2L, "", kNoLimit, kNoLimit, true},
  {"tool.hls.pipeline_decision.do_while_flatten_refusal", KeyKind::Bool, "", "A parent loop p is not flattened into its automatically pipelined child (no user pipeline) when the pipeline's complete unroll of a sub-loop of the child makes p + step a subscript of a multi-dimensional array that every iteration computes (no guard on the child's index, none false for that copy): Vitis' front end hoists the address, p becomes a do-while loop and Vitis refuses the flatten (200-960); the loops around p stay sequential too; a measured Vitis rule (VITIS_NOTES N96; kernels w9r13p_dv_p1 / dv_p2 / dv_expl / dv_lin / dv_val, N76's n64_* kernels; off: flattened as any perfect parent)", "", APU, "", kNoLimit, kNoLimit, true},
  {"tool.hls.pipeline_decision.do_while_min_subloop_trip", KeyKind::UInt, "", "do_while_flatten_refusal applies only to a subscript made by a sub-loop of at least this many iterations; a measured Vitis rule (kernels w9r13i_yp_d: a 2 x 2 window, flattened, against w9r13i_yp_c: 3 x 3, refused; Yolo-v3-tiny max_pool_2D_stride1, kernels w9r13i_yp_a / yp_b / yp_e / yp_f, flattened; the mechanism is unconfirmed)", "", APU, "", 1, kNoLimit, true},
  {"tool.hls.pipeline_decision.partial_unroll_runtime_loops", KeyKind::Bool, "", "A user `unroll factor=F` (1 < F) on an scf.for with a run-time trip count is applied as F guarded copies of the body in a loop of step F*step (copy u runs under iv + u*step < ub, Vitis keeps the exit test in the unrolled body); a copy's index into a cyclic partition is then not a constant bank, so every bank it can reach gets one access per copy; a measured Vitis rule (VITIS_NOTES N103, [HLS 214-188], kernels w9r14p_uv_var / uv_shr 116 against uv_none 58; off: the loop stays rolled)", "", APU, "", kNoLimit, kNoLimit, true},
  {"tool.hls.pipeline_decision.call_occupancy_after_partition", KeyKind::Bool, "", "The occupancy of a kept call in a pipelined loop is recomputed once the automatic partitions are decided: accesses to arrays that became registers, and loads whose value is unused, take no port (OPEN_ISSUES O133 / O144, Dehazing calculate_median: its scalarised window; off: the occupancy --auto-pipeline-unroll estimated before the partitions)", "", APU, "", kNoLimit, kNoLimit, true},

  {"tool.hls.partitioning", KeyKind::Section, "", "Automatic and inferred array partitioning", "Q-03..Q-08, Q-15", SPLIT ", " BANK, "", kNoLimit, kNoLimit, false},
  {"tool.hls.partitioning.policy", KeyKind::PluginName, "", "The PartitionPolicy", "Q-03, Q-04, Q-08, Q-15", SPLIT, "partition_policy", kNoLimit, kNoLimit, false},
  {"tool.hls.partitioning.constant_index", KeyKind::Section, "", "Rule (b): a dimension every access indexes with a constant", "Q-03", SPLIT, "", kNoLimit, kNoLimit, false},
  {"tool.hls.partitioning.constant_index.min_extent", KeyKind::UInt, "elements", "Smallest extent of such a dimension that is partitioned", "Q-03", SPLIT, "", 1, kNoLimit, false},
  {"tool.hls.partitioning.constant_index.max_extent", KeyKind::UInt, "elements", "Largest extent of such a dimension that is partitioned; a larger one stays whole (VITIS_NOTES N61; 0 or absent: no limit)", "Q-03", SPLIT, "", 0, kNoLimit, true},
  {"tool.hls.partitioning.constant_index.after_user_partition", KeyKind::Bool, "", "Rule (b) also applies to an array with a user cyclic / block array_partition, on every part (VITIS_NOTES N57)", "Q-03", SPLIT, "", kNoLimit, kNoLimit, true},
  {"tool.hls.partitioning.constant_index.pipo_streams", KeyKind::Bool, "", "Rule (b) also applies to an array whose only storage pragma is stream type=pipo (VITIS_NOTES N77)", "Q-03", SPLIT, "", kNoLimit, kNoLimit, true},
  {"tool.hls.partitioning.constant_index.globals", KeyKind::Bool, "", "Rule (b) also applies to globals and function statics, over the accesses of every function (VITIS_NOTES N77)", "Q-03", SPLIT, "", kNoLimit, kNoLimit, true},
  {"tool.hls.partitioning.constant_index.through_calls", KeyKind::Bool, "", "Rule (b) follows an array through the calls it is passed to (inline off callees, dataflow processes, recursively): the callee's accesses of the parameter count as the array's, so an array every function indexes with a constant in a dimension is partitioned there, and banking splits the callee's parameter the same way; a measured Vitis rule (VITIS_NOTES N94; kernels w9r13p_ci_io / ci_wr / ci_df / ci_cyc, control ci_var; off: a call stops rule (b))", "Q-03", SPLIT, "", kNoLimit, kNoLimit, true},
  {"tool.hls.partitioning.constant_index.fold_division", KeyKind::Bool, "", "An index computed by division, remainder, shifts or bit operations on constants (an unrolled copy's `(k * 2) / 2`) is a constant for rules (b) / (c) and for memory banking, as LLVM's constant folding makes it before Vitis partitions; a measured Vitis rule (VITIS_NOTES N97 (a); kernel w9r13p_st_row, siddharth lab2 `softmax_row`: a struct taken whole from a stream and read at the unrolled indices has no memory; off: only add / sub / mul fold)", "Q-03", SPLIT, "", kNoLimit, kNoLimit, true},
  {"tool.hls.partitioning.constant_index.fold_conditionals", KeyKind::Bool, "", "An index chosen by an scf.if or select whose condition folds to a constant once the loop is unrolled (a counter advanced only on some iterations: `if (k != 3) w[n++] = ..`) is that constant for rules (b) / (c) and for memory banking, as LLVM folds it before Vitis partitions (VITIS_NOTES N110 corpus: Dehazing tile_median cross_window / diag_window scalarised by 214-449; off: such an index is unknown)", "Q-03", SPLIT, "", kNoLimit, kNoLimit, true},
  {"tool.hls.partitioning.constant_index.through_views", KeyKind::Bool, "", "Rule (c) (every access constant: registers) also counts the accesses made through an element or row view of the array (polygeist.subindex `f(a[i])` with a reference parameter, or a memref.cast to a dynamic shape) inside the callees it is passed to (VITIS_NOTES N94 through the view; Dehazing calculate_median vals_tmp / median_tmp, scalar in Vitis; off: such a view stops the analysis)", "Q-03", SPLIT, "", kNoLimit, kNoLimit, true},
  {"tool.hls.partitioning.constant_index.block_offset", KeyKind::Bool, "", "On a dimension with a user block partition (block size B = ceil(extent / factor)), rule (b) looks at the offset inside the block: an affine index whose value modulo B is a constant (every variable term a multiple of B, as j = 8 * jj + u with u unrolled and B = 4) counts as a constant index, so each block is partitioned completely; a cyclic partition still needs a constant index; a measured Vitis rule (VITIS_NOTES N104; kernels w9r14p_cb_blk 64 banks, cb_cyc 16; class_ece8893 adithi lab3; off: a constant index only)", "Q-03", SPLIT, "", kNoLimit, kNoLimit, true},
  {"tool.hls.partitioning.constant_index.non_affine_arrays", KeyKind::Bool, "", "Rule (b) also applies to an array none of whose accesses is affine (VITIS_NOTES N57)", "Q-03", SPLIT, "", kNoLimit, kNoLimit, true},
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
  {"tool.hls.partitioning.steer_window_groups", KeyKind::Bool, "", "Unrolled window reads (one runtime base plus constants on every partitioned dimension) read each bank once per member of a residue class: a steered group spans several partitioned dimensions, and copies that share a residue class form further groups (VITIS_NOTES N74; off: one dimension, distinct residues only)", "", BANK, "", kNoLimit, kNoLimit, true},
  {"tool.hls.partitioning.induction_residue_banks", KeyKind::Bool, "", "A memref index that is the induction variable of an scf.for plus a constant addresses one bank of a cyclic partition when the loop's lower bound and step are constants and the step is a multiple of the factor ((lb + c) mod factor; the offset stays a run-time value): the guarded copies of a run-time-trip partial user unroll from a constant start (N103); a measured Vitis rule (W9r14 review kernel w9r14rv_uv_lb0: lb 0, factor 2, cyclic 2, Vitis single PIPO 58; with a run-time start, N103 uv_var, 116; off: every such bank is unknown)", "", BANK, "", kNoLimit, kNoLimit, true},
  {"tool.hls.partitioning.compound_assign_two_stores", KeyKind::Bool, "", "An ap_fixed compound assignment (/=, *=, +=, -=; cgeist marks its store hls.ap_compound_assign) to a bank chosen at run time writes that bank twice: never RAM_1WNR, two writes per iteration (VITIS_NOTES N38 R-cmpd)", "", BANK, "", kNoLimit, kNoLimit, true},
  {"tool.hls.partitioning.block_bank_from_loop_range", KeyKind::Bool, "", "A block-partitioned dimension whose index stays inside one block over the constant iteration range of its enclosing loops (buf[i + 64], i < 64, block depth 64) is accessed in that one bank, not through a store per candidate bank (VITIS_NOTES N86)", "", BANK, "", kNoLimit, kNoLimit, true},
  {"tool.hls.partitioning.reachable_store_banks", KeyKind::Bool, "", "A store whose bank is chosen at run time writes only the banks its index can reach when only the known low bits of its operands are used (an affine.for counter is lb + step * t, any other operand unknown): copy u of Cl[i][jj + u] with jj stepping by 32 writes banks u and u + 32, not every bank of the partition (OPEN_ISSUES O150: ben_hall lab3, kernel w9r8p_fl_pre; a loop range does not prune: vishnu lab3 row_ptr_A_local; off: a store_enable on every bank)", "", BANK, "", kNoLimit, kNoLimit, true},
  {"tool.hls.partitioning.complete_partition_registers", KeyKind::Bool, "", "A one-element bank of a complete partition (memory banking's hls.partition alloca) is a register: no port pool in a pipelined loop, priced as registers (VITIS_NOTES N111: kernel w9r15p_rg_net, a compare-and-swap network on a completely partitioned int v[8] runs at II 1; off: two ports per element)", "", BANK, "", kNoLimit, kNoLimit, true},
  {"tool.hls.partitioning.known_residue_banks", KeyKind::Bool, "", "A memref index whose low bits are known modulo a power-of-two cyclic factor ((n & ~7) + k: residue k mod 8; through casts, add / sub, masks with all-zero or all-one low bits, multiplies and shifts by a multiple of the factor) addresses that one bank, its offset computed at run time, as LLVM's known bits give Vitis (VITIS_NOTES N115 control kernel w9r15p_rc_fix: 15 copies per bank; off: the bank is chosen at run time)", "", BANK, "", kNoLimit, kNoLimit, true},

  {"tool.hls.folding", KeyKind::Section, "", "The tool's constant folding", "F-01..F-03", FOLD, "", kNoLimit, kNoLimit, false},
  {"tool.hls.folding.rule_set", KeyKind::PluginName, "", "The FoldRuleSet: vitis-undef (Vitis' undefined value of x / 0) or zero (x / 0 -> 0)", "F-01, F-02", FOLD, "fold_rule_set", kNoLimit, kNoLimit, false},
  {"tool.hls.folding.canonicalize", KeyKind::Bool, "", "Also apply every dialect's canonicalization in the same rewrite, so a folded zero propagates", "F-03", FOLD, "", kNoLimit, kNoLimit, false},
  {"tool.hls.folding.storage_address_not_null", KeyKind::Bool, "", "The address of a local array or global (or of a view of one) compared with the null pointer folds to a constant (never null), so a comparison does not keep the array alive (VITIS_NOTES N118: kernel w9r15p_pb_null, Vitis 0 BRAM; nikhil_p lab2 K_lcl; off: the comparison keeps it)", "F-03", FOLD, "", kNoLimit, kNoLimit, true},
  {"tool.hls.folding.max_rounds", KeyKind::UInt, "", "Rounds of the fold rewrite at most", "F-03", FOLD, "", 1, kNoLimit, false},

  {"tool.hls.middle_end", KeyKind::Section, "", "The LLVM clean-ups of the tool that change ports and memories", "L-01..L-03, E-02..E-04", A2L ", " DME, "", kNoLimit, kNoLimit, false},
  {"tool.hls.middle_end.licm_hoist_invariant_loads", KeyKind::Bool, "", "LICM: invariant loads move out of the pipelined loop and use none of its ports", "L-01", A2L, "", kNoLimit, kNoLimit, false},
  {"tool.hls.middle_end.licm_hoist_past_calls", KeyKind::Bool, "", "A memref some call takes is still hoisted from a loop without calls", "P-11", A2L, "", kNoLimit, kNoLimit, false},
  {"tool.hls.middle_end.licm_hoist_conditional", KeyKind::Bool, "", "Invariant loads nested in an if of the body are hoisted too (speculated)", "P-11", A2L, "", kNoLimit, kNoLimit, false},
  {"tool.hls.middle_end.licm_hoist_while_conditions", KeyKind::Bool, "", "LICM: a loop-invariant load in the condition region of an scf.while (a bound re-read every iteration, for (i = rp[r]; i < rp[r + 1]; ++i)) moves in front of the loop, so it shares the enclosing scope's states (VITIS_NOTES N120: davendra lab3 row_ptr_A_local, kernels w9r15p_rp_*; off: it stays in the condition)", "P-11", A2L, "", kNoLimit, kNoLimit, true},
  {"tool.hls.middle_end.merge_if_else_accesses", KeyKind::Bool, "", "A load / store both arms of an if/else make of one address is one access (SimplifyCFG / InstCombine)", "P-11", A2L, "", kNoLimit, kNoLimit, false},
  {"tool.hls.middle_end.gvn_loads", KeyKind::Bool, "", "GVN: a repeated load of one address is one load", "L-02", A2L, "", kNoLimit, kNoLimit, false},
  {"tool.hls.middle_end.gvn_memref_loads", KeyKind::Bool, "", "GVN also on memref.load (an index computed outside the affine form): a load of the same index values as an earlier load of the block, nothing in between that may write it, is the same value (Dehazing debayer with its counters raised by cgeist: 27 reads of in_tile, 9 distinct; off: only affine.load)", "L-02", A2L, "", kNoLimit, kNoLimit, true},
  {"tool.hls.middle_end.gvn_conditional_loads", KeyKind::Bool, "", "GVN load PRE: loads of one address in one block and in the ifs nested in it, with no write of the memref between them, are one load per iteration; a measured Vitis rule (W9 round 8 review, kernels w9r8f_pr1 / pr2 / pr3)", "L-02", A2L, "", kNoLimit, kNoLimit, false},
  {"tool.hls.middle_end.globals", KeyKind::Bool, "", "The clean-ups of --convert-affine-to-loopschedule (invariant-load hoist, GVN of loads, store forwarding, DSE) treat a global array like a local one: its memref.get_global (one per function) is the root memref, and every call is a barrier for it; a measured Vitis rule (ECG_Classifier baseline conv1d_2b: the guarded read-modify-writes of a global accumulator merge to one per iteration, II 1; kernel ie_acc with the accumulator global; off: no access of a global is merged or forwarded)", "L-02", A2L, "", kNoLimit, kNoLimit, true},
  {"tool.hls.middle_end.dse_guarded_stores", KeyKind::Bool, "", "GVN load PRE + DSE across an if: a store under an if of a pipelined loop body that a later store of the same address at the body's top level overwrites in the same iteration, with only loads of that address between (they take the guarded value through a select), uses no port; a measured Vitis rule (W9r11: stream_hls MultiHeadSelfAttention1 opt2 node2, init store + load + store of v17 at loop II 1)", "L-02", A2L, "", kNoLimit, kNoLimit, true},
  {"tool.hls.middle_end.forward_to_guarded_loads", KeyKind::Bool, "", "GVN store-to-load forwarding into an if: a load under an if of a pipelined loop body that reads the address a store at the body's top level wrote earlier in the same iteration (only loads of that address between) takes the stored value and uses no port (W9r11: class_ece8893 barry_walker lab2 output_matrix_local, 1 BRAM per bank)", "L-02", A2L, "", kNoLimit, kNoLimit, true},
  {"tool.hls.middle_end.store_forwarding", KeyKind::Bool, "", "Store-to-load forwarding and dead-store elimination within a block", "L-03", A2L, "", kNoLimit, kNoLimit, false},
  {"tool.hls.middle_end.dead_memory", KeyKind::Section, "", "Dead-memory elimination", "E-02..E-04", DME, "", kNoLimit, kNoLimit, false},
  {"tool.hls.middle_end.dead_memory.overwritten_stores", KeyKind::Bool, "", "A store a later store of the same access overwrites before any read is deleted", "E-03", DME, "", kNoLimit, kNoLimit, false},
  {"tool.hls.middle_end.dead_memory.dead_calls", KeyKind::Bool, "", "A call of a kept callee whose written arrays are never read is deleted", "P-12", DME, "", kNoLimit, kNoLimit, false},
  {"tool.hls.middle_end.dead_memory.overwritten_call_outputs", KeyKind::Bool, "", "dead_calls also deletes a call whose written one-element locals (scalar reference outputs) are, after the call, stored again in the same block before any other access or never accessed again up to the function's return, even when the variable is read elsewhere; a measured Vitis rule (VITIS_NOTES N107; kernels w9r14p_dc_dead 0 against dc_live 16; whetstone mod7; off: such a call is live)", "P-12", DME, "", kNoLimit, kNoLimit, true},
  {"tool.hls.middle_end.dead_memory.overwritten_by_loops", KeyKind::Bool, "", "overwritten_call_outputs also accepts an overwrite that is the first access of the local inside a loop with a constant trip count of at least one (nested loops included) that comes next after the call; a measured Vitis rule (W9r14 review kernel w9r14rv_dc_loopw: the outputs are overwritten in a 4-trip loop, Vitis deletes the call, 0; off: only a plain store, 16)", "P-12", DME, "", kNoLimit, kNoLimit, true},
  {"tool.hls.middle_end.dead_memory.unread_register_elements", KeyKind::Bool, "", "A store into an element of a registers array (hls.registers) that no used load reads, in its function or in the kept callees it is passed to, is deleted with the values computed only for it, after the automatic partitions (VITIS_NOTES N110: Vitis passes a kept callee only the window elements it reads; Dehazing calculate_median, kernel w9r15p_dw_dead; off: every store stays)", "P-12", DME, "", kNoLimit, kNoLimit, true},
  {"tool.hls.middle_end.dead_memory.honour_preserve", KeyKind::Bool, "", "hls.preserve keeps a dead array (Vitis: no)", "E-04", DME, "", kNoLimit, kNoLimit, false},
  {"tool.hls.middle_end.dead_memory.global_shared_by_functions_escapes", KeyKind::Bool, "", "A global used by more than one function escapes", "E-02", DME, "", kNoLimit, kNoLimit, false},
  {"tool.hls.middle_end.dead_memory.load_store_cycles", KeyKind::Bool, "", "An array whose loads feed (as value, address or condition) stores into itself, directly or through other arrays, is kept: no cyclic dead-store elimination; a measured Vitis rule (VITIS_NOTES N66)", "", DME, "", kNoLimit, kNoLimit, true},
  {"tool.hls.inlining", KeyKind::Section, "", "Function inlining", "P-01", "--inline", "", kNoLimit, kNoLimit, false},
  {"tool.hls.inlining.honour_inline_off", KeyKind::Bool, "", "Calls to hls.inline_off callees stay calls (--inline-ignore-inline-off overrides)", "P-01", "--inline", "", kNoLimit, kNoLimit, false},
  {"tool.hls.structs", KeyKind::Section, "", "Disaggregation of struct-typed variables", "P-02", "--split-struct-memrefs", "", kNoLimit, kNoLimit, false},
  {"tool.hls.structs.aggregate", KeyKind::Bool, "", "A variable an AGGREGATE pragma reached is one memory of packed words", "P-02", "--split-struct-memrefs", "", kNoLimit, kNoLimit, false},
  {"tool.hls.structs.globals", KeyKind::Bool, "", "Struct-typed globals are split like locals", "P-02", "--split-struct-memrefs", "", kNoLimit, kNoLimit, false},
  {"tool.hls.structs.scalar_registers", KeyKind::Bool, "", "A member of a single struct variable accessed only at constant positions is registers", "P-02", "--split-struct-memrefs", "", kNoLimit, kNoLimit, false},
  {"tool.hls.structs.through_calls", KeyKind::Bool, "", "A variable passed whole to kept calls is split together with the callees' parameters", "P-02", "--split-struct-memrefs", "", kNoLimit, kNoLimit, false},
  {"tool.hls.structs.element_copy_loops", KeyKind::Bool, "", "A loop that copies one whole struct element byte by byte (an inlined copy constructor / assignment, e.g. of an hls::vector) is one element copy, as Vitis turns the memcpy into one aggregate copy (VITIS_NOTES N44 / N51)", "P-02", "--split-struct-memrefs", "", kNoLimit, kNoLimit, true},
  {"tool.hls.structs.temporary_registers", KeyKind::Bool, "", "A one-element struct temporary cgeist materializes (a by-value operand, a returned struct) is split into registers, never a memory (VITIS_NOTES N51)", "P-02", "--split-struct-memrefs", "", kNoLimit, kNoLimit, true},
  {"tool.hls.structs.member_partitions", KeyKind::Bool, "", "An array_partition on a member path (variable=row.data) applies to the member's memory of a struct with one array member, its dim after the variable's dimensions (OPEN_ISSUES O78)", "P-02", "--split-struct-memrefs", "", kNoLimit, kNoLimit, true},
  {"tool.hls.structs.specialize_split_casts", KeyKind::Bool, "", "After the split, a static array of scalars passed through a memref.cast to a dynamic-shape parameter of a kept callee (a split hls::vector / struct array: memref<512x8xi16> to memref<?x8xi16>) specialises the callee to the static type, as --lower-polygeist-subindex does before the split, so the array's partition pragma reaches the callee's accesses; Vitis applies such pragmas (class_ece8893 hyungseok_bae lab3 local_B / local_row_idx_B: [HLS 214-248] cyclic 8, VITIS_NOTES N47 / N51, OPEN_ISSUES O84 (c); off: the pragma is dropped, used by memref.cast)", "P-02", "--split-struct-memrefs", "", kNoLimit, kNoLimit, true},
  {"tool.hls.narrowing", KeyKind::Section, "", "Element width the tool stores per word", "P-03", "--narrow-ram-widths", "", kNoLimit, kNoLimit, false},
  {"tool.hls.narrowing.stored_ranges", KeyKind::Bool, "", "Narrow to the bits the stored values need", "P-03", "--narrow-ram-widths", "", kNoLimit, kNoLimit, false},
  {"tool.hls.narrowing.constant_set_reinterpretation", KeyKind::Bool, "", "A RAM whose every stored value is a compile-time constant is narrowed by the ROM rule of N26 on that set of values (with no negative value, each value cut to the unsigned width of the largest is read as signed): VITIS_NOTES N112, kernels w9r15p_wc_* ({0, 100} -> 6 bits, {0, 64} -> 7); off: the interval of the stored values", "P-03", "--narrow-ram-widths", "", kNoLimit, kNoLimit, true},
  {"tool.hls.narrowing.load_demand", KeyKind::Bool, "", "Narrow to the low bits the loads' users demand", "P-03", "--narrow-ram-widths", "", kNoLimit, kNoLimit, false},
  {"tool.hls.narrowing.complete_read_selector", KeyKind::Bool, "", "A read whose subscript of a completely partitioned dimension of S elements comes from an array's load demands ceil(log2 S) bits of it (the bank selector); a write's subscript demands every bit (VITIS_NOTES N91, kernels w9r12p_nw_*)", "P-03", "--narrow-ram-widths", "", kNoLimit, kNoLimit, true},
  {"tool.hls.narrowing.full_address_interface_modes", KeyKind::StringList, "", "Interface modes of a top-level array argument whose subscripts demand every bit (m_axi: 32 bits, VITIS_NOTES N41); an argument without a pragma or of another mode demands the bits of its own address like a local (ap_memory and s_axilite: confirmed, kernels w9p5_idx_mem256 and w9rv_n41_mc; the other modes unconfirmed)", "P-03", "--narrow-ram-widths", "", kNoLimit, kNoLimit, false},
  {"tool.hls.globals", KeyKind::Section, "", "File-scope arrays", "T-03", BA, "", kNoLimit, kNoLimit, false},
  {"tool.hls.globals.attribute_accesses", KeyKind::Bool, "", "A global's accesses are attributed through its get_global sites (--bram-attribute-globals overrides)", "T-03", BA, "", kNoLimit, kNoLimit, false},
  {"tool.hls.grouping", KeyKind::Section, "", "Several memrefs mapped to one memory", "N-11", BA, "", kNoLimit, kNoLimit, false},
  {"tool.hls.grouping.plugin", KeyKind::PluginName, "", "The MemoryGrouping (identity: one memref, one memory)", "N-11", BA, "memory_grouping", kNoLimit, kNoLimit, false},
  {"tool.hls.math_library", KeyKind::Section, "", "Cost table of the math cores", "N-15", BA, "", kNoLimit, kNoLimit, false},
  {"tool.hls.math_library.table", KeyKind::String, "", "Path of the math-core cost table (math_costs.json format; relative to the file that sets it); empty: math calls cost nothing (--bram-analysis=math-costs= overrides)", "S-04, N-15", BA, "", kNoLimit, kNoLimit, false},
  {"tool.hls.math_library.local_struct_tables_at_run_time", KeyKind::Bool, "", "A table filled from math calls of the loop index is evaluated at compile time when it is a plain local or a global (also through one-element register temporaries and per-bank stores), but computed at run time (a core) when it is a member memory of a local struct array (VITIS_NOTES N60); off: the stores are judged as before W9r7", "N-15", BA, "", kNoLimit, kNoLimit, true},
  {"tool.hls.math_library.fixed_exp_tables_when_unlisted", KeyKind::Bool, "", "An hls::exp of ap_fixed / ap_ufixed whose (function, type) the cost table does not list is priced as the ROM tables its body reads (recorded by --lower-polygeist-subindex as hls.core_tables: the branch the template parameters select in hls_exp_apfixed.h), each a one-read ROM at the band formula, below the block threshold 0; one set per instance (per_concurrent_call); a measured Vitis rule (VITIS_NOTES N106; kernels w9r14p_ex_21_9 / ex_24_12 5, ex_32_8 7; off: unknown cost, 0)", "N-15", BA, "", kNoLimit, kNoLimit, true},
  {"tool.hls.math_library.inlined_tables_in_pipelines", KeyKind::Bool, "", "In a pipelined loop, k = ceil(calls / II) > 1 concurrent calls of an ap_fixed library core whose ROM tables are known (the cost table's tables of a library_module entry, or N106's hls.core_tables) share one set of tables read k times per cycle, each priced as a k-read ROM (up to two reads one memory, more ceil(k / 2) copies, N8), instead of k instances; calls that are copies of a user `unroll` pragma (partial or complete) stay one module per copy; a measured Vitis rule (VITIS_NOTES N16 R6: exp_32_16 v3x2 5, v4 16; W9r14 review kernel w9r14rv_ex_21_9u2: two exp<21,9> calls at II 1, 5; corpus zijun_wang lab2: 25 calls from the pipeline's unroll of an inner loop, inlined, 169; anuvab / ayush / kaihong / ritik lab2 (unroll factor=F) and ben_hall lab2 (a complete unroll pragma) keep exp_*_s modules; the trigger is unconfirmed; off: k instances)", "N-15", BA, "", kNoLimit, kNoLimit, true},

  //===----------------------------------------------------------- backend
  {"tool.backend", KeyKind::Section, "", "What maps memories to primitives (the HLS tool itself for Vitis, logic synthesis for other flows)", "", BA, "", kNoLimit, kNoLimit, false},
  {"tool.backend.id", KeyKind::String, "", "Back-end id", "", "debug output", "", kNoLimit, kNoLimit, false},
  {"tool.backend.storage_selector", KeyKind::Section, "", "Which tier a bank goes to, before scheduling", "B-08, B-09", BA, "", kNoLimit, kNoLimit, false},
  {"tool.backend.storage_selector.plugin", KeyKind::PluginName, "", "The StorageSelector", "B-08", BA, "storage_selector", kNoLimit, kNoLimit, false},
  {"tool.backend.storage_selector.min_block_bits", KeyKind::UInt, "bits", "Words x exact element bits from which a bank is a block RAM", "B-08", BA, "", 0, kNoLimit, false},
  {"tool.backend.storage_selector.inclusive", KeyKind::Bool, "", "A bank of exactly min_block_bits is a block RAM", "B-08", BA, "", kNoLimit, kNoLimit, false},
  {"tool.backend.storage_selector.block", KeyKind::String, "", "Memory id of the block tier", "B-08", BA, "", kNoLimit, kNoLimit, false},
  {"tool.backend.storage_selector.below", KeyKind::Enum, "", "Tier of a bank below the threshold (priced at 0 of the primary class)", "B-08", BA, "registers|distributed|hard-small|block|large", kNoLimit, kNoLimit, false},
  {"tool.backend.storage_selector.forcing_impl", KeyKind::String, "", "The bind_storage impl (lower case) that puts a bank in the block tier whatever its size, below min_block_bits included (the legacy RESOURCE core=..._BRAM pragma is the same attribute); a measured Vitis rule (VITIS_NOTES N98; kernels w9r13p_rs_bind / rs_res: a 16 x 16-bit array is RAM_2P_BRAM_1R1W, 1 BRAM); empty: no impl forces it", "B-08", BA, "", kNoLimit, kNoLimit, true},
  {"tool.backend.memory_mapper", KeyKind::Section, "", "The rule that turns a bank into primitives", "B-04..B-07", BA, "", kNoLimit, kNoLimit, false},
  {"tool.backend.memory_mapper.plugin", KeyKind::PluginName, "", "The MemoryMapper: vitis-band7, vitis-aspect-min or geometry-min (bram-formula=band|n6 overrides)", "B-07", BA, "memory_mapper", kNoLimit, kNoLimit, false},
  {"tool.backend.memory_mapper.primitive", KeyKind::String, "", "Memory id it maps to", "B-01", BA, "", kNoLimit, kNoLimit, false},
  {"tool.backend.memory_mapper.depth_rounding", KeyKind::Enum, "", "pow2: the address space is priced (2500 words as 4096); exact: the words. Read by geometry-min; the vitis-band7 bands are already powers of two, so there it changes nothing", "B-04", BA, "pow2|exact", kNoLimit, kNoLimit, false},
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
  {"frontend.user_storage_pragmas", KeyKind::StringList, "", "Attributes by which the user decided an array's storage (no automatic partition)", "Q-05", SPLIT ", " FOLD, "", kNoLimit, kNoLimit, false},

  //===------------------------------------------------------- scheduling
  {"scheduling", KeyKind::Section, "", "Operator timing, dependences, schedulers and binding", "S-01..S-22", A2L ", " APU, "", kNoLimit, kNoLimit, false},
  {"scheduling.timing", KeyKind::Section, "", "The operator timing model", "S-01..S-05", A2L, "", kNoLimit, kNoLimit, false},
  {"scheduling.timing.model", KeyKind::PluginName, "", "The OperatorTimingModel", "S-02", A2L, "operator_timing_model", kNoLimit, kNoLimit, false},
  {"scheduling.timing.operator_latencies", KeyKind::IntMap, "cycles", "Latency per operator class of calyx-fixed (unconfirmed against Vitis); call / kept_call -1: the loop stays sequential; the optional fpdiv_f32 / fpdiv_f64 / fpsqrt_f32 / fpsqrt_f64 replace fpdiv / fpsqrt for that element type (VITIS_NOTES N78); the optional stream_read / stream_write time a blocking hls::stream access on its stream's one port (N82; absent: the loop stays sequential)", "S-01, S-03, S-04", A2L ", " APU, "", -1, kNoLimit, false},
  {"scheduling.dependences", KeyKind::Section, "", "Which dependences constrain the schedule", "S-11..S-13", A2L, "", kNoLimit, kNoLimit, false},
  {"scheduling.dependences.model", KeyKind::PluginName, "", "The DependenceModel (cached-o1 keeps OPEN_ISSUES O1)", "S-11", A2L, "dependence_model", kNoLimit, kNoLimit, false},
  {"scheduling.dependences.memory_recurrences", KeyKind::Bool, "", "A load and a store of one memory linked by a read-modify-write chain and a carried distance d bound the II of the pipelined loop: d = 1 (one element, or a[i-1]) or an address that cannot be computed: the chain's recurrence latency; d >= 2: ceil((2 + chain) / d) (VITIS_NOTES N87; off: no memory recurrence reaches the scheduler, OPEN_ISSUES O1)", "S-11", A2L, "", kNoLimit, kNoLimit, true},
  {"scheduling.dependences.unknown_address_min_ii", KeyKind::UInt, "cycles", "A read-modify-write of one array at the same address value computed inside the pipelined body from loaded or carried values (h[v]++: the address cannot be evaluated) bounds the II at least this much, also when the chain from the load to the store is combinational: the next iteration's read waits for this iteration's write (VITIS_NOTES N117: kernel w9r15p_hs_rmw II 2, Dehazing debayer, 3d-rendering ZCULLING; 0: only the chain's recurrence latency, R4)", "S-11", A2L, "", 0, kNoLimit, true},
  {"scheduling.dependences.recurrence_latencies", KeyKind::IntMap, "cycles", "Cycles an operator class adds to a memory recurrence chain (<class>_f32 / <class>_f64 are looked up before <class>); a class not listed adds its operator latency (VITIS_NOTES N83: fadd 4, dadd 5, fmul 3, dmul 6; integer add / multiply 0 measured, the II is at least 1)", "S-11", A2L, "", 0, kNoLimit, true},
  {"scheduling.modulo", KeyKind::Section, "", "The modulo scheduler of pipelined loops", "S-08, S-10", A2L, "", kNoLimit, kNoLimit, false},
  {"scheduling.modulo.model", KeyKind::PluginName, "", "The ModuloScheduler", "S-10", A2L, "modulo_scheduler", kNoLimit, kNoLimit, false},
  {"scheduling.modulo.fast_threshold", KeyKind::UInt, "ops", "greedy-simplex: more resource-limited operations than this go to the greedy scheduler (0: always)", "S-08", A2L, "", 0, kNoLimit, false},
  {"scheduling.modulo.fast_ops_threshold", KeyKind::UInt, "ops", "greedy-simplex: more operations than this go to the greedy scheduler (0: no rule)", "S-08", A2L, "", 0, kNoLimit, false},
  {"scheduling.modulo.max_ii_bumps", KeyKind::UInt, "", "II increments the greedy scheduler tries", "S-08, R-06", A2L, "", 0, kNoLimit, false},
  {"scheduling.modulo.callee_global_recurrence", KeyKind::Bool, "", "A call in a pipelined loop to a callee Vitis keeps that reads and writes one global array (directly or in its own callees) starts only when the previous iteration's call has finished: II >= the call's depth; a measured Vitis rule (VITIS_NOTES N102, kernels w9r13rev_gl_call: hist[k & 7] += 1 in an inline-off callee, II 2; gl_callw: a store only, II 1; off: no such recurrence)", "S-08", A2L ", " BANK, "", kNoLimit, kNoLimit, true},
  {"scheduling.modulo.lower_ii_of_both", KeyKind::Bool, "", "greedy-simplex: a loop the simplex scheduler scheduled is also scheduled by the greedy scheduler, and the schedule with the lower II is kept (the simplex heuristic fixes the last store of an unrolled reduction before its loads, so a port- or bus-bound loop gets bumped far above its resource bound); a measured Vitis rule (kernels w9r13p_mx_r8: 8 reads on one m_axi bundle, Vitis II 8, simplex 14; w9r13p_nr_w16 / nr_w2 / nr_call: 16 reads on 2 ports, Vitis II 8, simplex 14; siddharth lab2 A x V loop, Vitis II 6, simplex 9; off: the simplex schedule stays)", "S-08", A2L, "", kNoLimit, kNoLimit, true},
  {"scheduling.modulo.max_pipeline_body_ops", KeyKind::UInt, "ops", "A pipelined loop whose body has more operations is left sequential with a warning (a memory guard, designer knob; 0: none)", "S-08", A2L, "", 0, kNoLimit, true},
  {"scheduling.modulo.recurrence_repair_rounds", KeyKind::UInt, "", "greedy scheduler: times a loop-carried edge broken by resource delays may move its destination later before the II is bumped (0: bump at once; 64 since R-cmpd is modelled, W9r7, OPEN_ISSUES O56); VITIS_NOTES N39", "S-08", A2L, "", 0, kNoLimit, false},
  {"scheduling.modulo.user_ii_target", KeyKind::Bool, "", "A loop with a user pipeline II=N > 1 is scheduled at N when it could start more often", "P-14", A2L, "", kNoLimit, kNoLimit, false},
  {"scheduling.sequential", KeyKind::Section, "", "The scheduler of non-pipelined regions", "K-12..K-14, S-22", A2L, "", kNoLimit, kNoLimit, false},
  {"scheduling.sequential.model", KeyKind::PluginName, "", "The SequentialScheduler (none: the stretch-pair rule applies)", "S-22", A2L, "sequential_scheduler", kNoLimit, kNoLimit, false},
  {"scheduling.binding", KeyKind::Section, "", "Operator binding and sharing", "S-21", A2L, "", kNoLimit, kNoLimit, false},
  {"scheduling.binding.model", KeyKind::PluginName, "", "The Binder (none: nothing is bound)", "S-21", A2L, "binder", kNoLimit, kNoLimit, false},
  {"scheduling.emit_detail", KeyKind::Bool, "", "Write hls.op_timing on every scheduled operation (inspection only; never changes a number)", "S-21, C-02", A2L, "", kNoLimit, kNoLimit, false},
  {"scheduling.call_depth", KeyKind::Section, "", "The ASAP chaining model of the depth of one call of a loop-free callee in a pipelined loop (Vitis 2025.1 xc7z020-1 delays)", "P-13", APU, "", kNoLimit, kNoLimit, false},
  {"scheduling.call_depth.load_data_ns", KeyKind::Number, "ns", "A load's data arrives this far into the cycle after it issues", "P-13", APU, "", 0, kNoLimit, false},
  {"scheduling.call_depth.logic_ns", KeyKind::Number, "ns", "and / or / xor", "P-13", APU, "", 0, kNoLimit, false},
  {"scheduling.call_depth.select_ns", KeyKind::Number, "ns", "select", "P-13", APU, "", 0, kNoLimit, false},
  {"scheduling.call_depth.variable_shift_ns", KeyKind::Number, "ns", "A shift by a variable amount", "P-13", APU, "", 0, kNoLimit, false},
  {"scheduling.call_depth.constant_multiplier_ns", KeyKind::Number, "ns", "A multiply by a constant with three or more set bits (unconfirmed)", "P-13", APU, "", 0, kNoLimit, false},
  {"scheduling.call_depth.narrow_multiply_max_bits", KeyKind::UInt, "bits", "Multiplies of two variables up to this width take narrow_multiply_cycles; wider ones the multicycle latency", "P-13", APU, "", 1, kNoLimit, false},
  {"scheduling.call_depth.narrow_multiply_cycles", KeyKind::UInt, "cycles", "Latency of such a multiply", "P-13", APU, "", 0, kNoLimit, false},
  {"scheduling.call_depth.ports_per_memory", KeyKind::UInt, "ports", "Accesses of one memory per cycle", "P-13", APU, "", 1, kNoLimit, false},
  {"scheduling.call_depth.staggered_calls_share_instance", KeyKind::Bool, "", "Two calls of one kept function at the top level of their caller that no value or array orders still share one instance when their inputs become ready in different states of the caller's call schedule (a call starts after the calls whose arrays or values it uses, calls of one function sharing an array run one after the other): VITIS_NOTES N116, kernels w9r15p_al_lim / al_nolim 1 instance against al_same / al_two 2; forgebench attn_breakdown rope (off: such calls are concurrent, N14 R2)", "P-13", APU, "", kNoLimit, kNoLimit, true},
  {"scheduling.call_depth.index_bits", KeyKind::UInt, "bits", "Width an index value is timed at (Vitis narrows addresses)", "P-13", APU, "", 1, kNoLimit, false},
  {"scheduling.call_depth.carry_chain_ns", KeyKind::ObjectList, "", "Adder / subtractor / comparator delay by width (the last band has no max_bits)", "P-13", APU, "", kNoLimit, kNoLimit, false},
  {"scheduling.call_depth.carry_chain_ns[].max_bits", KeyKind::UInt, "bits", "Widest operand of the band", "P-13", APU, "", 1, kNoLimit, true},
  {"scheduling.call_depth.carry_chain_ns[].ns", KeyKind::Number, "ns", "Delay", "P-13", APU, "", 0, kNoLimit, false},
  {"scheduling.call_depth.ternary_adder_ns", KeyKind::ObjectList, "", "Three-input adder delay by width", "P-13", APU, "", kNoLimit, kNoLimit, false},
  {"scheduling.call_depth.ternary_adder_ns[].max_bits", KeyKind::UInt, "bits", "Widest result of the band", "P-13", APU, "", 1, kNoLimit, true},
  {"scheduling.call_depth.ternary_adder_ns[].ns", KeyKind::Number, "ns", "Delay", "P-13", APU, "", 0, kNoLimit, false},

  //===---------------------------------------------------------- plugins
  {"plugins", KeyKind::FreeObject, "", "plugins.<name>: a section owned by the plugin of that name, validated by it; a section whose plugin is not selected by any plugin key is refused", "", "plugins", "", kNoLimit, kNoLimit, false},
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
