//===- ConstantIndex.h - constant memref indices shared by passes ---------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// One definition of "this index is a compile-time constant" for the passes
// that have to agree on it:
//   --infer-vitis-split-array   td=off rule (b) completely partitions a
//                               dimension that only constants index;
//   --memory-banking-bram       an access whose bank index is a constant
//                               reads one bank, any other reads every bank
//                               and muxes them (f loads + f-1 selects).
// If banking resolved fewer constants than the inference, a dimension split
// *because* its indices are constant would be read through every bank, and
// each bank would be charged a port for every such access.
//
//===----------------------------------------------------------------------===//

#ifndef CIRCT_DIALECT_RESOURCE_PASSES_CONSTANTINDEX_H
#define CIRCT_DIALECT_RESOURCE_PASSES_CONSTANTINDEX_H

#include "circt/Dialect/Resource/Config/Config.h"
#include "mlir/Dialect/Affine/Analysis/LoopAnalysis.h"
#include "mlir/Dialect/Affine/IR/AffineOps.h"
#include "mlir/Dialect/Arith/IR/Arith.h"
#include "mlir/Dialect/SCF/IR/SCF.h"
#include "mlir/Dialect/Utils/StaticValueUtils.h"
#include "mlir/IR/AffineExpr.h"
#include "mlir/IR/AffineMap.h"
#include "llvm/ADT/SmallVector.h"

#include <cstdint>
#include <optional>

namespace circt::hls_analysis {

inline std::optional<int64_t> getConstantIndexValue(mlir::Value v);

/// Whether constant conditions fold (key
/// tool.hls.partitioning.constant_index.fold_conditionals).
inline bool foldConstantConditionals() {
  return circt::hlsest::Config::get()
      .tool.hls.partitioning.constantIndexFoldConditionals;
}

/// The value of an i1 condition computed from constants: a constant, or an
/// arith.cmpi of two operands getConstantIndexValue resolves.
inline std::optional<bool> getConstantCondition(mlir::Value c) {
  if (auto cst = c.getDefiningOp<mlir::arith::ConstantOp>())
    if (auto b = mlir::dyn_cast<mlir::BoolAttr>(cst.getValue()))
      return b.getValue();
  if (auto cst = c.getDefiningOp<mlir::arith::ConstantIntOp>())
    return cst.value() != 0;
  auto cmp = c.getDefiningOp<mlir::arith::CmpIOp>();
  if (!cmp)
    return std::nullopt;
  std::optional<int64_t> a = getConstantIndexValue(cmp.getLhs());
  std::optional<int64_t> b =
      a ? getConstantIndexValue(cmp.getRhs()) : std::nullopt;
  if (!a || !b)
    return std::nullopt;
  uint64_t ua = static_cast<uint64_t>(*a), ub = static_cast<uint64_t>(*b);
  unsigned width = 64;
  if (auto it = mlir::dyn_cast<mlir::IntegerType>(cmp.getLhs().getType()))
    width = it.getWidth();
  if (width == 0 || width > 64)
    return std::nullopt;
  if (width < 64) { // the unsigned predicates compare the bit patterns
    ua &= (uint64_t(1) << width) - 1;
    ub &= (uint64_t(1) << width) - 1;
  }
  using P = mlir::arith::CmpIPredicate;
  switch (cmp.getPredicate()) {
  case P::eq: return *a == *b;
  case P::ne: return *a != *b;
  case P::slt: return *a < *b;
  case P::sle: return *a <= *b;
  case P::sgt: return *a > *b;
  case P::sge: return *a >= *b;
  case P::ult: return ua < ub;
  case P::ule: return ua <= ub;
  case P::ugt: return ua > ub;
  case P::uge: return ua >= ub;
  }
  return std::nullopt;
}

/// The value of an index operand if it is a compile-time constant by the time
/// Vitis partitions and binds memories: an integer constant (also through
/// arith.index_cast / arith.index_castui), or the counter of an affine.for
/// with a constant lower bound that runs exactly once (the LLVM front end
/// folds such a loop away; cgeist usually does too).
inline std::optional<int64_t> getConstantIndexValue(mlir::Value v) {
  if (std::optional<int64_t> c = mlir::getConstantIntValue(v))
    return c;
  if (auto cast = v.getDefiningOp<mlir::arith::IndexCastOp>())
    return getConstantIndexValue(cast.getIn());
  if (auto cast = v.getDefiningOp<mlir::arith::IndexCastUIOp>()) {
    // Zero extension: only a non-negative source keeps its value.
    std::optional<int64_t> c = getConstantIndexValue(cast.getIn());
    if (c && *c >= 0)
      return c;
    return std::nullopt;
  }
  // Integer arithmetic on constants, which LLVM's constant folding removes
  // before Vitis looks at the indices: unrolling a loop over `worker(s[id],
  // s[id + 4])` leaves `index_cast(addi(index_cast %c, 4))` as the element
  // index of a stream array (W9r7 review defect 6). The result wraps to the
  // operation's width like the hardware value.
  if (mlir::Operation *def = v.getDefiningOp())
    if (mlir::isa<mlir::arith::AddIOp, mlir::arith::SubIOp,
                  mlir::arith::MulIOp>(def)) {
      std::optional<int64_t> a = getConstantIndexValue(def->getOperand(0));
      std::optional<int64_t> b =
          a ? getConstantIndexValue(def->getOperand(1)) : std::nullopt;
      if (!a || !b)
        return std::nullopt;
      uint64_t ua = static_cast<uint64_t>(*a), ub = static_cast<uint64_t>(*b);
      uint64_t r = mlir::isa<mlir::arith::AddIOp>(def)   ? ua + ub
                   : mlir::isa<mlir::arith::SubIOp>(def) ? ua - ub
                                                         : ua * ub;
      unsigned width = 64;
      if (auto it = mlir::dyn_cast<mlir::IntegerType>(v.getType()))
        width = it.getWidth();
      if (width == 0 || width > 64)
        return std::nullopt;
      if (width < 64) {
        uint64_t mask = (uint64_t(1) << width) - 1;
        r &= mask;
        if (r >> (width - 1)) // sign-extend
          r |= ~mask;
      }
      return static_cast<int64_t>(r);
    }
  // Division, remainder, shifts and bit operations on constants fold the
  // same way (an ap_fixed index scaled and unscaled, `(k * 2) / 2` with k an
  // unrolled loop's constant, siddharth lab2 `softmax_row`, VITIS_NOTES
  // N97): C's truncating signed division, the unsigned forms only for
  // non-negative values.
  if (mlir::Operation *def = v.getDefiningOp())
    if (circt::hlsest::Config::get()
            .tool.hls.partitioning.constantIndexFoldDivision &&
        mlir::isa<mlir::arith::DivSIOp, mlir::arith::RemSIOp,
                  mlir::arith::DivUIOp, mlir::arith::RemUIOp,
                  mlir::arith::ShLIOp, mlir::arith::ShRSIOp,
                  mlir::arith::ShRUIOp, mlir::arith::AndIOp, mlir::arith::OrIOp,
                  mlir::arith::XOrIOp>(def)) {
      std::optional<int64_t> a = getConstantIndexValue(def->getOperand(0));
      std::optional<int64_t> b =
          a ? getConstantIndexValue(def->getOperand(1)) : std::nullopt;
      if (!a || !b)
        return std::nullopt;
      bool isUnsigned = mlir::isa<mlir::arith::DivUIOp, mlir::arith::RemUIOp,
                                  mlir::arith::ShRUIOp>(def);
      if (isUnsigned && (*a < 0 || *b < 0))
        return std::nullopt;
      if (mlir::isa<mlir::arith::DivSIOp, mlir::arith::RemSIOp,
                    mlir::arith::DivUIOp, mlir::arith::RemUIOp>(def)) {
        if (*b == 0)
          return std::nullopt;
        return mlir::isa<mlir::arith::DivSIOp, mlir::arith::DivUIOp>(def)
                   ? *a / *b
                   : *a % *b;
      }
      if (mlir::isa<mlir::arith::AndIOp>(def))
        return *a & *b;
      if (mlir::isa<mlir::arith::OrIOp>(def))
        return *a | *b;
      if (mlir::isa<mlir::arith::XOrIOp>(def))
        return *a ^ *b;
      if (*b < 0 || *b >= 63 || *a < 0)
        return std::nullopt;
      return mlir::isa<mlir::arith::ShLIOp>(def) ? (*a << *b) : (*a >> *b);
    }
  // An affine.apply whose operands all fold to constants (unrolling leaves
  // `affine.apply (d0 + 1)(%c0)` as the index of a memref.load).
  if (auto apply = v.getDefiningOp<mlir::affine::AffineApplyOp>()) {
    mlir::AffineMap map = apply.getAffineMap();
    if (map.getNumResults() != 1)
      return std::nullopt;
    llvm::SmallVector<int64_t, 4> operands;
    for (mlir::Value o : apply.getMapOperands()) {
      std::optional<int64_t> c = getConstantIndexValue(o);
      if (!c)
        return std::nullopt;
      operands.push_back(*c);
    }
    llvm::SmallVector<mlir::AffineExpr, 4> repl;
    for (int64_t c : operands)
      repl.push_back(mlir::getAffineConstantExpr(c, map.getContext()));
    unsigned nd = map.getNumDims();
    mlir::AffineExpr e = map.getResult(0).replaceDimsAndSymbols(
        llvm::ArrayRef(repl).take_front(nd), llvm::ArrayRef(repl).drop_front(nd));
    e = mlir::simplifyAffineExpr(e, 0, 0);
    if (auto ce = llvm::dyn_cast<mlir::AffineConstantExpr>(e))
      return ce.getValue();
    return std::nullopt;
  }
  // A value chosen by a condition computed from constants: the counter an
  // unrolled loop advances only on some iterations (`if (k != 3) w[n++] =
  // ..`, Dehazing tile_median's cross / diag windows) is a chain of scf.if /
  // select results whose conditions fold once the loop is unrolled, as LLVM
  // folds them before Vitis partitions (VITIS_NOTES N110 corpus: the windows
  // are scalarised, 214-449).
  if (foldConstantConditionals()) {
    if (auto sel = v.getDefiningOp<mlir::arith::SelectOp>()) {
      std::optional<bool> c = getConstantCondition(sel.getCondition());
      if (!c)
        return std::nullopt;
      return getConstantIndexValue(*c ? sel.getTrueValue()
                                      : sel.getFalseValue());
    }
    if (auto ifOp = v.getDefiningOp<mlir::scf::IfOp>()) {
      std::optional<bool> c = getConstantCondition(ifOp.getCondition());
      if (!c || (!*c && ifOp.getElseRegion().empty()))
        return std::nullopt;
      mlir::Block &blk = *c ? ifOp.getThenRegion().front()
                            : ifOp.getElseRegion().front();
      auto yield = mlir::cast<mlir::scf::YieldOp>(blk.getTerminator());
      unsigned n = mlir::cast<mlir::OpResult>(v).getResultNumber();
      return getConstantIndexValue(yield.getOperand(n));
    }
  }
  if (mlir::affine::isAffineForInductionVar(v)) {
    mlir::affine::AffineForOp owner = mlir::affine::getForInductionVarOwner(v);
    if (owner.hasConstantLowerBound() &&
        mlir::affine::getConstantTripCount(owner) == uint64_t(1))
      return owner.getConstantLowerBound();
  }
  return std::nullopt;
}

/// `map` (taking `operands`, dimensions first) with every operand that
/// getConstantIndexValue resolves replaced by its value and every result
/// simplified. The map keeps its dimension and symbol counts, so it still
/// takes `operands`; it computes the same addresses at run time.
inline mlir::AffineMap foldConstantIndexOperands(mlir::AffineMap map,
                                                 mlir::ValueRange operands) {
  mlir::MLIRContext *ctx = map.getContext();
  unsigned numDims = map.getNumDims(), numSyms = map.getNumSymbols();
  llvm::SmallVector<mlir::AffineExpr, 8> dimRepl, symRepl;
  for (unsigned i = 0; i < numDims; ++i) {
    std::optional<int64_t> c = getConstantIndexValue(operands[i]);
    dimRepl.push_back(c ? mlir::getAffineConstantExpr(*c, ctx)
                        : mlir::getAffineDimExpr(i, ctx));
  }
  for (unsigned i = 0; i < numSyms; ++i) {
    std::optional<int64_t> c = getConstantIndexValue(operands[numDims + i]);
    symRepl.push_back(c ? mlir::getAffineConstantExpr(*c, ctx)
                        : mlir::getAffineSymbolExpr(i, ctx));
  }
  llvm::SmallVector<mlir::AffineExpr, 4> results;
  for (mlir::AffineExpr expr : map.getResults())
    results.push_back(mlir::simplifyAffineExpr(
        expr.replaceDimsAndSymbols(dimRepl, symRepl), numDims, numSyms));
  return mlir::AffineMap::get(numDims, numSyms, results, ctx);
}

} // namespace circt::hls_analysis

#endif // CIRCT_DIALECT_RESOURCE_PASSES_CONSTANTINDEX_H
