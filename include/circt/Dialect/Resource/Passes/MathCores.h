//===- MathCores.h - hls:: math-function cores for --bram-analysis -*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// The BRAM of the math-library cores Vitis instantiates for hls:: math calls:
// every (function, element type, argument form) is one core with a fixed
// BRAM_18K per instance, read from the programmer's cost table
// (tools/hls-est-validate/math_costs.json, option
// --bram-analysis=math-costs=<path>); the number of instances follows the call
// structure (MathCores.cpp).
//
//===----------------------------------------------------------------------===//

#ifndef CIRCT_DIALECT_RESOURCE_PASSES_MATHCORES_H
#define CIRCT_DIALECT_RESOURCE_PASSES_MATHCORES_H

#include "mlir/IR/BuiltinOps.h"
#include "llvm/ADT/STLFunctionalExtras.h"
#include "llvm/ADT/StringRef.h"
#include "llvm/Support/JSON.h"
#include "llvm/Support/raw_ostream.h"

#include <optional>
#include <string>
#include <vector>

namespace circt::hls_analysis {

/// One entry of the cost table: one core per (function, type, argument form).
struct MathCostEntry {
  unsigned index = 0;            // position in "entries"
  std::string function;          // "exp", "pow", "sin", ...
  std::string type;              // "float" | "double" | "half" | "ap_fixed<W,I>"
  std::string arguments = "any"; // "any" | "constant base" | "constant exponent"
  std::vector<std::string> cores; // Vitis module(s) of one instance; empty: inlined
  std::string coreKind;          // fp_operator | library_module | inline_cordic | inline | logic_only
  int64_t bram = 0;              // BRAM_18K of one instance
  std::string instancing;        // per_concurrent_call | operator | logic_only | cordic_loop | inline_tables
  std::optional<int64_t> cordicTrips;    // cordic_loop_trip_count
  std::optional<int64_t> bramIfUnrolled; // bram_18k_if_cordic_loop_unrolled
  /// cordic_loop_unrolled_in: which pipelined loops unroll the CORDIC loop
  /// (and fold its table): "any_pipeline" (default) or "user_pipeline" (only
  /// a loop with a pipeline pragma: sin / cos, whose CORDIC loop Vitis keeps
  /// under automatic pipelining).
  std::string cordicUnrolledIn = "any_pipeline";
  /// Functions whose call on the same argument (same type) shares this
  /// entry's instance (ap_fixed sin + cos of one argument: one CORDIC).
  std::vector<std::string> sharesInstanceWith;
  /// blocks_automatic_pipelining: the core keeps Vitis from pipelining the
  /// loops around a call automatically (the double sin / cos core, whose
  /// internal loops have a variable trip count): only a pipeline pragma
  /// pipelines them.
  bool blocksAutoPipelining = false;
  std::string tableName;         // first ROM table, names an inlined core
  /// The ROM tables of one instance, (words, bits) each: the cost table's
  /// "tables" of the entry, or the hls.core_tables of an N106 entry.
  std::vector<std::pair<int64_t, unsigned>> tableShapes;
};

/// The parsed cost table. Only the keys hls-est uses are read; the rest
/// (evidence, variants, dsp / ff / lut, ...) is documentation.
struct MathCostConfig {
  std::string path;
  std::vector<MathCostEntry> entries;

  /// Reads and validates `file`. On failure returns false with `error` set.
  bool load(llvm::StringRef file, std::string &error);
  /// The entry of (function, type, arguments); an argument form without its
  /// own entry falls back to "any". Null when the pair is not listed.
  const MathCostEntry *lookup(llvm::StringRef function, llvm::StringRef type,
                              llvm::StringRef arguments) const;
};

/// One region the calls of a core run in.
struct MathRegionRecord {
  std::string kind;      // "pipeline" | "sequential"
  std::string loc;       // the pipelined loop / the sequential scope
  unsigned ii = 0;       // pipeline: achieved (or requested) II
  bool iiAssumed = false; // pipeline left unscheduled: requested II, else 1
  std::string source;     // pipeline: "user" (a pragma) | "auto" (automatic)
  bool cordicKept = false; // cordic_loop: the CORDIC loop stays a loop here
  unsigned calls = 0;    // live, non-constant calls (shared pairs count once)
  unsigned unrollCopies = 1; // sequential (not pipelined by Vitis): copies of
                             // one call site hls-est's auto-unroll made
  unsigned instances = 0;
  int64_t bramPerInstance = 0;
  /// pipeline: the `instances` concurrent calls share one set of tables,
  /// each read that many times per cycle (VITIS_NOTES N16 R6); the region
  /// then costs `sharedTablesBram`, not instances x bramPerInstance.
  bool sharedTables = false;
  int64_t sharedTablesBram = 0;
};

/// One call site.
struct MathSiteRecord {
  std::string op;     // "math.exp", "func.call @__hlsest_math_exp", ...
  std::string loc;
  std::string status; // counted | folded | dead | shared
  std::string detail; // region, or what it shares with / why it is free
};

/// All calls of one core (one cost-table entry, or one unlisted pair) in one
/// function.
struct MathCoreRecord {
  std::string func;
  std::string function, type, arguments;
  std::string typeSource; // "marker" (shim marker call) | "mlir" (element type)
  std::optional<unsigned> entry; // index in the cost table
  std::optional<MathCostEntry> entryInfo; // a copy of that entry
  std::string configPath;
  std::string status;     // counted | unknown_cost | folded | dead
  std::string reason;
  std::string coreName;   // Vitis core module or ROM table (display, compare.py)
  std::string coreKind, instancing;
  int64_t bramPerInstance = 0;
  unsigned instances = 0;
  /// Instances of the function the calls are in (a callee Vitis keeps as a
  /// module, instantiated more than once); `instances` and `bram` include it.
  unsigned functionInstances = 1;
  int64_t bram = 0;
  std::string loc;        // first site
  std::vector<MathRegionRecord> regions;
  std::vector<MathSiteRecord> sites;
};

/// Finds the math calls of the functions `covers` accepts and prices them
/// with `config`; the cores of a function are built once per instance of it
/// (`instancesOf`). Unlisted (function, type) pairs get a record with status
/// "unknown_cost" and BRAM 0; `warn` is called once per such pair that has a
/// live, non-constant call. `romBlocks` prices a ROM of (words, bits) read
/// n times per cycle; with it, an unlisted ap_fixed exp whose function
/// records its tables (hls.core_tables) is priced as those tables
/// (VITIS_NOTES N106), and the concurrent calls of an ap_fixed library core
/// in a pipelined loop share one set of tables (N16 R6).
std::vector<MathCoreRecord>
analyzeMathCores(mlir::ModuleOp module, const MathCostConfig &config,
                 llvm::function_ref<bool(mlir::Operation *)> covers,
                 llvm::function_ref<unsigned(mlir::Operation *)> instancesOf,
                 llvm::function_ref<void(mlir::Location, const std::string &)>
                     warn,
                 llvm::function_ref<int64_t(int64_t, unsigned, unsigned)>
                     romBlocks = nullptr);

/// The "math" object of a math_core debug record (JSON v2, additive).
llvm::json::Object mathCoreJson(const MathCoreRecord &r);
/// The --bram-debug text lines of a math_core record (after its header).
void printMathCoreText(const MathCoreRecord &r, llvm::raw_ostream &os);
/// The stdout report line of a math_core record ("math.core function=...").
void printMathCoreLine(const MathCoreRecord &r, llvm::raw_ostream &os);

} // namespace circt::hls_analysis

#endif // CIRCT_DIALECT_RESOURCE_PASSES_MATHCORES_H
