//===- ConstantFills.cpp - arrays Vitis turns into ROMs -------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// --mark-constant-fills
//
// Vitis implements an array whose every write stores a compile-time constant
// as a ROM holding those constants: by db/a.o.1.ll the array is an `internal
// constant` global with the values as its initialiser and the fill loop is
// gone (VITIS_NOTES.md N26; kernels w7_rf*, forgebench activation_op1's
// `set_value(FM_buffer_3, 1)` through an `inline off` callee). It does so
// before its arithmetic folds: the forgebench attention `scores`, whose
// stores become `store i16 0` only once `acc * (x / 0)` folds (N1, N13), is
// still a RAM in a.o.1 and costs 1 BRAM (attention_op_p1, dg_d_apfixed16).
//
// So this pass runs early (after --inline, before --canonicalize / --sccp /
// --vitis-fold) and evaluates the stored values itself: a value counts when
// it is an integer constant, a side-effect-free op whose operands evaluate
// (folded with the op's own folder: what LLVM constant folding does to a
// constant expression, not an algebraic rewrite of a non-constant value), or
// the parameter of a private function every call of which passes such a
// value. An alloca or global written by exactly one store (direct, or inside
// a callee through a parameter it is passed to, reached by one call) that
// stores such a value gets
// `hls.const_fill = <width>`: the element width its values need (N26's rule;
// a dense initial value counts as values too; 0 when every value is 0).
// --memory-banking-bram copies the mark to the banks, and --bram-analysis
// prices a marked array that is read and written as a ROM of that width.
//
//===----------------------------------------------------------------------===//

#include "circt/Dialect/Resource/Passes/VitisCleanup.h"
#include "circt/Dialect/Resource/Passes/CallInstances.h"

#include "mlir/Dialect/Affine/IR/AffineOps.h"
#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/Dialect/MemRef/IR/MemRef.h"
#include "mlir/IR/BuiltinOps.h"
#include "mlir/IR/Matchers.h"
#include "mlir/IR/SymbolTable.h"
#include "mlir/Interfaces/SideEffectInterfaces.h"
#include "mlir/Pass/Pass.h"

using namespace mlir;

namespace {

constexpr unsigned kMaxDepth = 24;

// The integer value(s) `v` always has, or false.
static bool evaluate(Value v, SmallVectorImpl<APInt> &out, unsigned depth) {
  if (!v || depth > kMaxDepth || !v.getType().isIntOrIndex())
    return false;
  APInt c;
  if (matchPattern(v, m_ConstantInt(&c))) {
    out.push_back(c);
    return true;
  }
  if (auto res = dyn_cast<OpResult>(v)) {
    Operation *op = res.getOwner();
    if (op->getNumResults() != 1 || op->getNumRegions() != 0 ||
        !isMemoryEffectFree(op))
      return false;
    SmallVector<Attribute> operands;
    for (Value o : op->getOperands()) {
      SmallVector<APInt> vals;
      if (!evaluate(o, vals, depth + 1) || vals.size() != 1)
        return false;
      operands.push_back(IntegerAttr::get(o.getType(), vals.front()));
    }
    SmallVector<OpFoldResult> folded;
    if (failed(op->fold(operands, folded)) || folded.size() != 1)
      return false;
    auto attr = dyn_cast_or_null<IntegerAttr>(
        dyn_cast_if_present<Attribute>(folded.front()));
    if (!attr)
      return false;
    out.push_back(attr.getValue());
    return true;
  }
  auto arg = cast<BlockArgument>(v);
  auto fn = dyn_cast_or_null<func::FuncOp>(arg.getOwner()->getParentOp());
  if (!fn || arg.getOwner() != &fn.getBody().front() || !fn.isPrivate())
    return false;
  auto module = fn->getParentOfType<ModuleOp>();
  std::optional<SymbolTable::UseRange> uses =
      module ? SymbolTable::getSymbolUses(fn, module) : std::nullopt;
  if (!uses)
    return false;
  bool any = false;
  for (const SymbolTable::SymbolUse &u : *uses) {
    auto call = dyn_cast<func::CallOp>(u.getUser());
    if (!call || arg.getArgNumber() >= call.getNumOperands())
      return false;
    if (!evaluate(call.getOperand(arg.getArgNumber()), out, depth + 1))
      return false;
    any = true;
  }
  return any;
}

// The ROM element width of `vals` (VITIS_NOTES.md N26); 0 when every value
// is 0. Same rule as --bram-analysis applies to constant tables.
static unsigned romWidth(ArrayRef<APInt> vals) {
  bool anyNegative =
      llvm::any_of(vals, [](const APInt &v) { return v.isNegative(); });
  unsigned width = 0;
  if (anyNegative) {
    for (const APInt &v : vals)
      width = std::max(width, v.getSignificantBits());
    return width;
  }
  unsigned a = 0;
  for (const APInt &v : vals)
    a = std::max(a, v.getActiveBits());
  if (a == 0)
    return 0;
  for (const APInt &v : vals)
    width = std::max(width, v.trunc(a).getSignificantBits());
  return width;
}

// Collect the values stored into the memory `mem` names, following calls
// into private callees; `writes` counts the stores, a store in a callee once
// per call that reaches it. False when some write cannot be evaluated or the
// memory escapes (a view, an unknown use, a callee without a body).
static bool collectFill(Value mem, SmallVectorImpl<APInt> &vals,
                        unsigned &writes, unsigned depth) {
  if (depth > kMaxDepth)
    return false;
  for (OpOperand &use : mem.getUses()) {
    Operation *user = use.getOwner();
    if (isa<affine::AffineLoadOp, memref::LoadOp, memref::DimOp>(user))
      continue;
    if (auto st = dyn_cast<affine::AffineStoreOp>(user)) {
      if (st.getValueToStore() == mem)
        return false;
      ++writes;
      if (!evaluate(st.getValueToStore(), vals, 0))
        return false;
      continue;
    }
    if (auto st = dyn_cast<memref::StoreOp>(user)) {
      if (st.getValueToStore() == mem)
        return false;
      ++writes;
      if (!evaluate(st.getValueToStore(), vals, 0))
        return false;
      continue;
    }
    if (auto call = dyn_cast<func::CallOp>(user)) {
      func::FuncOp callee = circt::hls_analysis::resolveDefinedCallee(call);
      unsigned i = use.getOperandNumber();
      if (!callee || i >= callee.getNumArguments())
        return false;
      if (!collectFill(callee.getArgument(i), vals, writes, depth + 1))
        return false;
      continue;
    }
    return false; // a view, a return, an op with unknown effects
  }
  return true;
}

struct MarkConstantFillsPass
    : PassWrapper<MarkConstantFillsPass, OperationPass<ModuleOp>> {
  MLIR_DEFINE_EXPLICIT_INTERNAL_INLINE_TYPE_ID(MarkConstantFillsPass)
  StringRef getArgument() const final { return "mark-constant-fills"; }
  StringRef getDescription() const final {
    return "Mark arrays whose every write stores a compile-time constant "
           "(hls.const_fill = element width of those values): Vitis "
           "implements them as ROMs (VITIS_NOTES.md N26)";
  }

  void runOnOperation() override {
    ModuleOp module = getOperation();
    Builder b(module.getContext());
    auto mark = [&](Operation *op, ArrayRef<Value> sites,
                    ArrayRef<APInt> initVals) {
      auto ty = cast<MemRefType>(op->getNumResults()
                                     ? op->getResult(0).getType()
                                     : cast<memref::GlobalOp>(op).getType());
      if (!ty.getElementType().isInteger())
        return;
      SmallVector<APInt> vals(initVals.begin(), initVals.end());
      unsigned writes = 0;
      for (Value s : sites)
        if (!collectFill(s, vals, writes, 0))
          return;
      // One store, once: a fill loop (w7_rf*, w7_rf_part, w7_rf_stride) or
      // a filler called once (activation_op1). Two fill loops, two calls or
      // a conditional pair of stores leave a RAM (dead_globals dg_c_const01,
      // dg_c_const0_x2: `buf 512x1 RAM`, narrowed but not a ROM; that
      // narrowing is not modelled, OPEN_ISSUES O18).
      if (writes != 1)
        return;
      unsigned width = ty.getElementType().getIntOrFloatBitWidth();
      for (APInt &v : vals)
        v = v.sextOrTrunc(width);
      op->setAttr("hls.const_fill", b.getI32IntegerAttr(
                                        static_cast<int32_t>(romWidth(vals))));
    };
    module.walk([&](memref::AllocaOp a) {
      if (a.getType().hasStaticShape())
        mark(a, {a.getResult()}, {});
    });
    llvm::StringMap<SmallVector<Value>> sites;
    module.walk([&](memref::GetGlobalOp gg) {
      sites[gg.getName()].push_back(gg.getResult());
    });
    for (auto g : module.getOps<memref::GlobalOp>()) {
      if (g.isExternal() || g.getConstant() || !g.getType().hasStaticShape())
        continue;
      SmallVector<APInt> init;
      if (!g.isUninitialized()) {
        auto d = dyn_cast_or_null<DenseIntElementsAttr>(
            g.getInitialValueAttr());
        if (!d)
          continue;
        for (const APInt &v : d.getValues<APInt>())
          init.push_back(v);
      }
      auto it = sites.find(g.getSymName());
      if (it == sites.end())
        continue;
      mark(g, it->second, init);
    }
  }
};

} // namespace

std::unique_ptr<Pass> circt::hls_analysis::createMarkConstantFillsPass() {
  return std::make_unique<MarkConstantFillsPass>();
}
