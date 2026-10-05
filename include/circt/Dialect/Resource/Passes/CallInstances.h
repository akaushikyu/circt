//===- CallInstances.h - non-inlined callees as Vitis instantiates them ---===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// Shared model of the calls hls-est keeps (a callee with `hls.inline_off`, or
// one the inliner could not inline): the pragma attribute names, callee
// resolution, the storage root of a memref operand, and the instance count
// of every function as Vitis HLS 2025.1 instantiates a non-inlined callee
// (VITIS_NOTES.md N14, 60 kernels + 27 corpus designs):
//
//   R2  Inside one parent module, calls of one callee that can run
//       concurrently get one instance each; calls that are ordered share
//       one. Two calls are ordered when a value of one reaches an operand of
//       the other (a scalar data dependence, `g(g(x))`; through memory only
//       when the write can precede the read: later in program order or in
//       the next iteration of a common loop), when both access a common
//       array (any memref operand with the same storage root: an alloca, a
//       global, a function argument, through views), or when the parent
//       carries `#pragma HLS allocation function instances=<callee> limit=N`
//       (at most N instances). Calls in different branches of one
//       conditional never run together and are ordered too (w3r2_k5). The
//       instance count is the most calls that can run at once (the width of
//       the order, not the number of its connected groups: w3r2_k6, two
//       independent calls joined by a third keep 2 instances). A call site
//       inside a loop is one instance whatever the trip count. Calls whose
//       data operands are read from one memory run at most its read ports
//       (scheduling.call_depth.ports_per_memory, 2) at a time (N16 R4,
//       w11rv_r3 / r8: k unrolled copies of `y[i] = hls::exp(x[i])` get
//       min(k, 2) cores).
//   R3  Every parent module that calls the callee gets its own instances, so
//       a function's instance count is the sum over its parents of the
//       parent's count times the instances it holds (the product down the
//       instance tree). The top (a function nobody calls) counts 1.
//   R6  A caller's array is replicated for the pipelined loops of a callee
//       it is passed to only when every module it crosses is instantiated
//       at one place in the module hierarchy (one instance in one parent;
//       the parent's own multiplicity does not matter): w3rev_k3a / k3c /
//       w3fx_d2_nested replicate, w3rev_k3 / k3b / w3fx_d2_conc (two places)
//       do not, and the callee's loop II rises instead.
//   R9  A written `static` (global) array is one memory however many
//       instances its functions have (w3rev_k5, w3fx_d3_mix: in the top);
//       a read-only one (a ROM) is duplicated per instance (inl_c4).
//
// Not modelled (observed without a confirmed trigger, N14): the clones Vitis
// makes for different array argument forms (R4) and the outlined loops that
// give a call inside the loop an instance of its own (R5).
//
//===----------------------------------------------------------------------===//

#ifndef CIRCT_DIALECT_RESOURCE_PASSES_CALLINSTANCES_H
#define CIRCT_DIALECT_RESOURCE_PASSES_CALLINSTANCES_H

#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/IR/BuiltinOps.h"
#include "mlir/IR/SymbolTable.h"
#include "mlir/Interfaces/CallInterfaces.h"
#include "llvm/ADT/DenseMap.h"
#include "llvm/ADT/STLFunctionalExtras.h"
#include "llvm/ADT/SmallPtrSet.h"
#include "llvm/ADT/SmallVector.h"
#include "llvm/ADT/StringRef.h"

#include <optional>
#include <string>

namespace circt::hls_analysis {

/// `hls.inline_off` (unit, on a func.func): the function carries
/// `#pragma HLS inline off`; cgeist keeps its calls and so does hls-est's
/// `--inline` (HlsInliner.cpp).
constexpr llvm::StringLiteral kInlineOffAttr = "hls.inline_off";
/// `hls.inline_auto_off` (dictionary, on a func.func and on its func.call
/// ops): Vitis would not inline these calls automatically (callee size x
/// calls above its threshold, or a dataflow process; VITIS_NOTES N18), so
/// cgeist keeps them (--hls-auto-inline, W10). hls-est treats such a callee
/// exactly like an `inline off` one.
constexpr llvm::StringLiteral kInlineAutoOffAttr = "hls.inline_auto_off";

/// Whether `fn` is a callee whose calls Vitis keeps: `inline off`, or kept by
/// Vitis's automatic-inlining rule.
inline bool isKeptCallee(mlir::Operation *fn) {
  return fn->hasAttr(kInlineOffAttr) || fn->hasAttr(kInlineAutoOffAttr);
}
/// `hls.allocation` (array of dictionaries, on a func.func): the function's
/// `#pragma HLS allocation` pragmas, `{instances = ["name", ...], limit = N,
/// type = "function"}` as cgeist --hls-annotate writes them.
constexpr llvm::StringLiteral kAllocationAttr = "hls.allocation";
/// `hls.orig_name` (string, on a func.func): the C/C++ name of a mangled
/// function, which the allocation pragma names.
constexpr llvm::StringLiteral kOrigNameAttr = "hls.orig_name";
/// `hls.port_bound_args` (array of i64, on a func.func): the indices of the
/// memref arguments whose array reaches the function through a module that
/// is instantiated at more than one place (InstanceModel::
/// argReachesSharedModule, R6). Vitis does not replicate such an array for
/// the function's loops: the accesses go through the module's two ports and
/// the loop's II rises (w3rev_k3: rd3's loop II 2). Written by
/// --auto-pipeline-unroll (a module pass) for MemrefBankClassification,
/// which runs inside function passes and cannot look at the call sites.
constexpr llvm::StringLiteral kPortBoundArgsAttr = "hls.port_bound_args";

/// The func.func with a body that `call` resolves to in the enclosing module,
/// or null (an indirect call, an external declaration).
mlir::func::FuncOp resolveDefinedCallee(mlir::CallOpInterface call);

/// Index of `operand` among the call's argument operands, or nullopt when it
/// is not one (a callee pointer, for example).
std::optional<unsigned> callArgIndex(mlir::CallOpInterface call,
                                     mlir::OpOperand &operand);

/// The storage a memref value names: its root through views (memref.cast,
/// memref.subview, polygeist.subindex, any ViewLikeOpInterface op), with a
/// memref.get_global resolved to its memref.global so that two sites of one
/// global compare equal. Two values with the same key alias; distinct keys
/// are distinct arrays, except for function arguments, which name whatever
/// the caller passes (compare those through the call graph if needed).
struct StorageRoot {
  mlir::Value value;              // the root value (null for a global)
  mlir::Operation *global = nullptr; // memref.global when rooted in one
  bool operator==(const StorageRoot &o) const {
    return value == o.value && global == o.global;
  }
  bool operator!=(const StorageRoot &o) const { return !(*this == o); }
};
StorageRoot storageRoot(mlir::Value mem);

/// The `allocation function` limit the parent sets for `callee`
/// (kAllocationAttr, matched by hls.orig_name or symbol name), if any.
std::optional<int64_t> allocationLimit(mlir::func::FuncOp parent,
                                       mlir::func::FuncOp callee);

/// How many instances of `callee` one parent holds, and why.
struct ParentInstances {
  mlir::func::FuncOp parent;
  mlir::func::FuncOp callee;
  unsigned callSites = 0;  // calls of `callee` in `parent`
  unsigned instances = 0;  // concurrent groups, capped by the limit
  std::optional<int64_t> limit; // `allocation ... limit=N` on the parent
  std::string rule;        // one line for the debug report
  /// Group (instance index within the parent) of each call site, in walk
  /// order of the parent's body.
  llvm::SmallVector<std::pair<mlir::Operation *, unsigned>> siteGroups;
};

/// Instance counts of every function of a module (R2 + R3).
struct InstanceModel {
  /// Instances of each function: 1 for a root (the top, or any function no
  /// in-scope function calls), the sum over parents otherwise. Functions
  /// outside the scope are absent.
  llvm::DenseMap<mlir::Operation *, unsigned> multiplicity;
  /// Per callee, one entry per parent that calls it.
  llvm::DenseMap<mlir::Operation *, llvm::SmallVector<ParentInstances>>
      parents;
  /// Per call site: (parent, callee, group index within the parent).
  struct Site {
    mlir::func::FuncOp parent, callee;
    unsigned group = 0;
  };
  llvm::DenseMap<mlir::Operation *, Site> sites;
  /// A call cycle was found; the functions on it count as roots.
  bool recursive = false;

  unsigned instancesOf(mlir::func::FuncOp fn) const {
    auto it = multiplicity.find(fn.getOperation());
    return it == multiplicity.end() ? 1u : it->second;
  }
  /// Instances of the function `op` lives in (1 outside any function).
  unsigned instancesAt(mlir::Operation *op) const;
  /// Instances of the module that owns a global used from `users`: the
  /// deepest common ancestor in the call graph of the functions that use it
  /// (one user: that function; none: 1).
  unsigned ownerInstances(llvm::ArrayRef<mlir::func::FuncOp> users) const;
  /// The owner itself (null when none / several roots).
  mlir::func::FuncOp owner(llvm::ArrayRef<mlir::func::FuncOp> users) const;
  /// Where a written global used from `users` lives (R9): the nearest
  /// function at or above the owner that has one instance (the top in
  /// w3rev_k5); null when none is found.
  mlir::func::FuncOp
  singleInstanceOwner(llvm::ArrayRef<mlir::func::FuncOp> users) const;
  /// Places in the module hierarchy where `fn` is instantiated: the sum over
  /// its parents of the instances each parent holds, without the parents'
  /// own multiplicity (the rows of the csynth instance tables); 0 for a root.
  unsigned instanceSites(mlir::func::FuncOp fn) const;
  /// Whether the array passed as memref argument `argIndex` of `fn` crosses
  /// a module instantiated at more than one place on its way from its owner
  /// (`fn` itself, or a caller up the chain of arguments) (R6).
  bool argReachesSharedModule(mlir::func::FuncOp fn, unsigned argIndex) const;
  /// Whether the call sites of `fn` bind two or more different arrays
  /// (storage roots) to its memref argument `argIndex`. One module instance
  /// then reads them through its own ports (VITIS_NOTES N75: rs_two_common,
  /// rs_pingpong; tool.hls.memory_architecture.replication.
  /// port_bound_several_arrays).
  bool argBindsSeveralArrays(mlir::func::FuncOp fn, unsigned argIndex) const;
  /// The callee side of R6 / N75: whether accesses inside `callee` to the
  /// array passed as its argument `argIndex` go through a module port
  /// (several instances, or several arrays bound to the parameter).
  bool calleeArgPortBound(mlir::func::FuncOp callee, unsigned argIndex) const;
  /// Why calleeArgPortBound holds: "instances" (several instance sites, R6),
  /// "several_arrays" (N75), "array_shared_with_port_bound_parameter" (N75
  /// per array, W9r9 review D1), "writable_global" (N85); empty when it does
  /// not.
  llvm::StringRef calleeArgPortBoundReason(mlir::func::FuncOp callee,
                                           unsigned argIndex) const;
  /// The arrays bound to memref argument `argIndex` of `fn` at its call
  /// sites, followed up through the callers' own arguments to their roots
  /// (an alloca, a global, or an argument of a root function).
  void boundRoots(mlir::func::FuncOp fn, unsigned argIndex,
                  llvm::SmallVectorImpl<StorageRoot> &out) const;
  /// N75 is a per-array decision (W9r9 review D1, kernel w9r9rev_e75_mixed):
  /// an array bound to a parameter that binds several arrays is port-bound
  /// in every callee it reaches, also through parameters that bind it alone.
  bool argSharesPortBoundArray(mlir::func::FuncOp fn, unsigned argIndex) const;

  /// Whether a written global (or function static) reaches memref argument
  /// `argIndex` of `fn` (VITIS_NOTES N85: Vitis never replicates such an
  /// array, a callee reads it through its two ports; tool.hls.
  /// memory_architecture.replication.port_bound_writable_globals).
  bool argBindsWritableGlobal(mlir::func::FuncOp fn, unsigned argIndex) const;
  /// Whether some op writes the global `global` (not a constant table).
  bool isWrittenGlobal(mlir::Operation *global) const;
  /// Cache of isWrittenGlobal.
  mutable llvm::DenseMap<mlir::Operation *, bool> writtenGlobals;
  /// The get_global sites of every global of a symbol table, collected in one
  /// walk per table (isWrittenGlobal walked the table once per global:
  /// hp_fft n1024 UF32, OPEN_ISSUES O103).
  mutable llvm::DenseMap<mlir::Operation *,
                         llvm::DenseMap<mlir::StringAttr,
                                        llvm::SmallVector<mlir::Value>>>
      globalSitesByTable;

  /// Cache of the roots bound to a parameter that binds several arrays.
  mutable std::optional<llvm::SmallVector<StorageRoot>> severalArraysRoots;

  // Call-graph helpers (parents of a function, as func.funcs).
  llvm::DenseMap<mlir::Operation *, llvm::SmallVector<mlir::func::FuncOp>>
      callers;
};

/// Build the model for the functions of `module` that `inScope` accepts (all
/// of them when `inScope` is null). Calls to functions outside the scope or
/// without a body are ignored.
InstanceModel
computeInstances(mlir::ModuleOp module,
                 llvm::function_ref<bool(mlir::func::FuncOp)> inScope = nullptr);

/// Group the calls `sites` (all to one callee, in program order within one
/// parent) into instances by rule R2: two calls are ordered when they share
/// a storage root, when a value of one reaches an operand of the other
/// (forward in program order, or around a common loop; a terminator forwards
/// each operand to its own result / iter_arg), or when they lie in different
/// branches of one conditional, or when they are the n-th and (n + ports)-th
/// call reading their data operands from one memory (its read ports, from
/// the configuration); the groups are a minimum cover of the
/// transitively closed order by chains (each chain one instance, its calls
/// run one after the other), then capped by `limit`. Returns the group of
/// each site and the number of groups; `rule` receives a one-line
/// explanation. Works on the affine form (--convert-affine-to-loopschedule)
/// and on the loopschedule form (--bram-analysis) alike. `alsoOrdered`
/// (optional) orders further pairs (i < j) the caller knows never overlap.
unsigned groupConcurrentCalls(
    mlir::func::FuncOp parent, llvm::ArrayRef<mlir::Operation *> sites,
    std::optional<int64_t> limit, llvm::SmallVectorImpl<unsigned> &group,
    std::string *rule = nullptr,
    llvm::function_ref<bool(unsigned, unsigned)> alsoOrdered = nullptr);

/// The cycles one call of the loop-free `fn` holds its instance (its own
/// II): its distinct accesses per memory at two per cycle (a memory's two
/// ports), the busiest memory deciding, a nested call with its own
/// occupancy; at least 1 (VITIS_NOTES N14 R7). `ignore`, when given, drops
/// an access (the memory is registers, or the loaded value is unused).
unsigned estimateCallOccupancy(
    mlir::func::FuncOp fn, mlir::SymbolTableCollection &symbolTable,
    llvm::SmallPtrSetImpl<mlir::Operation *> &stack,
    llvm::function_ref<bool(mlir::Operation *access, mlir::Value mem)> ignore =
        nullptr);

/// `hls.call_depth_estimate = N : i64` on a call whose hls.call_depth the
/// occupancy decided: the depth --auto-pipeline-unroll's delay model gave the
/// callee (smaller than the occupancy), so that refreshCallOccupancies can take
/// the maximum again with a new occupancy.
constexpr llvm::StringLiteral kCallDepthEstimateAttr =
    "hls.call_depth_estimate";

/// Recomputes hls.call_occupancy (and hls.call_depth) of every call that has
/// one once --infer-vitis-split-array has decided the automatic partitions:
/// an access to an array that became registers (an alloca or global marked
/// hls.registers, or a parameter every call site of its function binds to
/// one) takes no port, and a load whose value nothing uses takes none either
/// (Vitis removes it). OPEN_ISSUES O133 / O144: Dehazing's calculate_median
/// read its square_window 49 times at two per cycle (occupancy 25) although
/// the window is scalarised (214-449). Returns the number of calls changed.
unsigned refreshCallOccupancies(mlir::ModuleOp module);

/// Clones every kept callee (inline off, or kept by cgeist's automatic
/// inlining) once per tuple of argument IR types its call sites give it, as
/// Vitis does: a float / double array that is a port of the top function is
/// an integer array in Vitis' IR (`[N x i32]*`), a caller-local or global one
/// stays floating point, so call sites mixing them call different functions
/// (`f`, `f.1`, ...), each a module with its own local arrays (VITIS_NOTES
/// N165: kernels w9r22p_b1_mix 3 modules, b4_swap 2; controls b2 (locals
/// only), b3 (ports only), b5 (int arrays) 1). The kind of a parameter of a
/// non-root function is the kind its clone was made for; roots (functions
/// no other function calls: the top) have port parameters. Calls are
/// redirected to the clones. Returns the number of clones made.
unsigned cloneKeptCalleesPerArgumentType(mlir::ModuleOp module);

/// Whether `a` and `b` lie in different arms of one if (directly, or as
/// recorded in `hls.if_arms` after --convert-affine-to-loopschedule hoisted
/// them): they never run in one execution of the if.
bool inExclusiveArms(mlir::Operation *a, mlir::Operation *b);

} // namespace circt::hls_analysis

#endif // CIRCT_DIALECT_RESOURCE_PASSES_CALLINSTANCES_H
