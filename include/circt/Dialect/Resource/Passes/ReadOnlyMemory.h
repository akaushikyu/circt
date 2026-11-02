//===- ReadOnlyMemory.h - is a memory ever written? -------------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// `neverWritten(sites)`: no op writes or frees the memory named by `sites`
// (the get_global results of a global, an alloca) or by a value derived from
// them, and none of them escapes. Used by --vitis-fold (a never-written
// table with one value everywhere folds to that value) and --bram-analysis
// (a never-written initialised global is a ROM): Vitis' front end sees such
// a global as `constant` (LLVM GlobalOpt) whatever the source says.
//
// A memref value is followed through
//   - a view of it (ViewLikeOpInterface, polygeist.subindex included);
//   - a counted loop's (scf.for, affine.for) init operand: into the loop's region iter_arg and the loop's
//     result (cgeist's pointer walks, `p = &tab[j][0]; ... *p++`, carry the
//     current position as a memref iter_arg of the loop);
//   - a yield operand: into the iter_arg and result of the enclosing loop,
//     or the result of the enclosing scf.if / affine.if;
//   - a pure op without regions whose results are all memrefs
//     (arith.select, memref.cast): into its results;
//   - a call operand of a function defined in the module: into the
//     callee's parameter (`walk(&tab[j][0], n)`).
// Any other use must be an op with memory effects on that value that reads
// it; anything else (a call of an external function, a store of the
// memref, a return, an op without effect information) makes the memory
// possibly written.
//
//===----------------------------------------------------------------------===//

#ifndef CIRCT_DIALECT_RESOURCE_PASSES_READONLYMEMORY_H
#define CIRCT_DIALECT_RESOURCE_PASSES_READONLYMEMORY_H

#include "mlir/Dialect/Affine/IR/AffineOps.h"
#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/Dialect/MemRef/IR/MemRef.h"
#include "mlir/Dialect/SCF/IR/SCF.h"
#include "mlir/IR/BuiltinTypes.h"
#include "mlir/Interfaces/CallInterfaces.h"
#include "mlir/Interfaces/LoopLikeInterface.h"
#include "mlir/Interfaces/SideEffectInterfaces.h"
#include "mlir/Interfaces/ViewLikeInterface.h"
#include "llvm/ADT/DenseSet.h"

namespace circt::hls_analysis {

/// The values a memref operand `use` flows into without being accessed: the
/// result of a view, the iter_arg and result a counted loop's init or yield
/// feeds, the result an if yield feeds, the results of a pure all-memref op,
/// the parameter of a defined callee. False when `use` is not such a flow.
inline bool memrefFlowTargets(mlir::OpOperand &use,
                              llvm::SmallVectorImpl<mlir::Value> &targets) {
  mlir::Operation *user = use.getOwner();
  if (auto view = llvm::dyn_cast<mlir::ViewLikeOpInterface>(user)) {
    if (view.getViewSource() != use.get())
      return false;
    for (mlir::Value r : user->getResults())
      if (llvm::isa<mlir::BaseMemRefType>(r.getType()))
        targets.push_back(r);
    return true;
  }
  // Counted loops only: their inits, iter_args, yields and results pair up
  // one to one (an scf.while's results follow its condition, not its inits).
  if (llvm::isa<mlir::scf::ForOp, mlir::affine::AffineForOp>(user)) {
    auto loop = llvm::cast<mlir::LoopLikeOpInterface>(user);
    auto inits = loop.getInitsMutable();
    for (auto [i, init] : llvm::enumerate(inits)) {
      if (&init != &use)
        continue;
      targets.push_back(loop.getRegionIterArgs()[i]);
      if (auto results = loop.getLoopResults())
        targets.push_back((*results)[i]);
      return true;
    }
    return false;
  }
  // A pure op without regions whose results are all memrefs (arith.select,
  // memref.cast) writes nothing; its results may alias the operand. One with
  // a result of another type (polygeist.memref2pointer: an !llvm.ptr) lets
  // the address escape.
  if (user->getNumRegions() == 0 && user->getNumResults() > 0 &&
      mlir::isMemoryEffectFree(user) &&
      !llvm::isa<mlir::CallOpInterface>(user) &&
      llvm::all_of(user->getResultTypes(), [](mlir::Type t) {
        return llvm::isa<mlir::BaseMemRefType>(t);
      })) {
    for (mlir::Value r : user->getResults())
      targets.push_back(r);
    return true;
  }
  if (auto call = llvm::dyn_cast<mlir::CallOpInterface>(user)) {
    auto callee =
        llvm::dyn_cast_or_null<mlir::func::FuncOp>(call.resolveCallable());
    if (!callee || callee.isExternal())
      return false;
    unsigned first = call.getArgOperands().getBeginOperandIndex();
    unsigned idx = use.getOperandNumber();
    if (idx < first || idx - first >= callee.getNumArguments())
      return false;
    targets.push_back(callee.getArgument(idx - first));
    return true;
  }
  if (user->hasTrait<mlir::OpTrait::IsTerminator>() &&
      llvm::isa<mlir::scf::YieldOp, mlir::affine::AffineYieldOp>(user)) {
    mlir::Operation *parent = user->getParentOp();
    unsigned idx = use.getOperandNumber();
    if (llvm::isa<mlir::scf::ForOp, mlir::affine::AffineForOp>(parent)) {
      auto loop = llvm::cast<mlir::LoopLikeOpInterface>(parent);
      auto iterArgs = loop.getRegionIterArgs();
      if (idx >= iterArgs.size())
        return false;
      targets.push_back(iterArgs[idx]);
      if (auto results = loop.getLoopResults())
        targets.push_back((*results)[idx]);
      return true;
    }
    if (llvm::isa<mlir::scf::IfOp, mlir::affine::AffineIfOp>(parent)) {
      if (idx >= parent->getNumResults())
        return false;
      targets.push_back(parent->getResult(idx));
      return true;
    }
  }
  return false;
}

/// True if no op writes or frees the memory named by `sites` or by a value
/// derived from them (memrefFlowTargets), and none of them escapes.
inline bool neverWritten(llvm::ArrayRef<mlir::Value> sites) {
  llvm::SmallVector<mlir::Value> work(sites.begin(), sites.end());
  llvm::DenseSet<mlir::Value> seen(sites.begin(), sites.end());
  llvm::SmallVector<mlir::Value, 4> targets;
  while (!work.empty()) {
    mlir::Value cur = work.pop_back_val();
    for (mlir::OpOperand &use : cur.getUses()) {
      mlir::Operation *user = use.getOwner();
      targets.clear();
      if (memrefFlowTargets(use, targets)) {
        for (mlir::Value t : targets)
          if (seen.insert(t).second)
            work.push_back(t);
        continue;
      }
      if (llvm::isa<mlir::memref::DimOp>(user))
        continue;
      auto eff = llvm::dyn_cast<mlir::MemoryEffectOpInterface>(user);
      if (!eff)
        return false;
      llvm::SmallVector<mlir::MemoryEffects::EffectInstance> effects;
      eff.getEffects(effects);
      bool named = false;
      for (auto &e : effects) {
        if (e.getValue() != cur)
          continue;
        named = true;
        if (llvm::isa<mlir::MemoryEffects::Write, mlir::MemoryEffects::Free>(
                e.getEffect()))
          return false;
      }
      if (!named)
        return false;
    }
  }
  return true;
}

} // namespace circt::hls_analysis

#endif // CIRCT_DIALECT_RESOURCE_PASSES_READONLYMEMORY_H
