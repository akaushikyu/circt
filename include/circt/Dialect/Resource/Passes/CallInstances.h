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
//       the other (a scalar data dependence, `g(g(x))`), when both access a
//       common array (any memref operand with the same storage root: an
//       alloca, a global, a function argument, through views), or when the
//       parent carries `#pragma HLS allocation function instances=<callee>
//       limit=N` (at most N instances). A call site inside a loop is one
//       instance whatever the trip count.
//   R3  Every parent module that calls the callee gets its own instances, so
//       a function's instance count is the sum over its parents of the
//       parent's count times the instances it holds (the product down the
//       instance tree). The top (a function nobody calls) counts 1.
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
#include "mlir/Interfaces/CallInterfaces.h"
#include "llvm/ADT/DenseMap.h"
#include "llvm/ADT/SmallVector.h"
#include "llvm/ADT/StringRef.h"

#include <optional>
#include <string>

namespace circt::hls_analysis {

/// `hls.inline_off` (unit, on a func.func): the function carries
/// `#pragma HLS inline off`; cgeist keeps its calls and so does hls-est's
/// `--inline` (HlsInliner.cpp).
constexpr llvm::StringLiteral kInlineOffAttr = "hls.inline_off";
/// `hls.allocation` (array of dictionaries, on a func.func): the function's
/// `#pragma HLS allocation` pragmas, `{instances = ["name", ...], limit = N,
/// type = "function"}` as cgeist --hls-annotate writes them.
constexpr llvm::StringLiteral kAllocationAttr = "hls.allocation";
/// `hls.orig_name` (string, on a func.func): the C/C++ name of a mangled
/// function, which the allocation pragma names.
constexpr llvm::StringLiteral kOrigNameAttr = "hls.orig_name";

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
/// parent) into instances by rule R2: union over "share a storage root" and
/// "a value of the earlier reaches an operand of the later", then capped by
/// `limit`. Returns the group of each site and the number of groups; `rule`
/// receives a one-line explanation.
unsigned groupConcurrentCalls(mlir::func::FuncOp parent,
                              llvm::ArrayRef<mlir::Operation *> sites,
                              std::optional<int64_t> limit,
                              llvm::SmallVectorImpl<unsigned> &group,
                              std::string *rule = nullptr);

} // namespace circt::hls_analysis

#endif // CIRCT_DIALECT_RESOURCE_PASSES_CALLINSTANCES_H
