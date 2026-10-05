//===- HlsInliner.cpp - func-dialect inliner that honours inline off ------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// hls-est's default pipeline starts with MLIR's `--inline`, which inlines
// every func.call it legally can. Vitis keeps a callee marked
// `#pragma HLS inline off` as a module of its own, charged once per instance
// (VITIS_NOTES.md N14 R1-R3), and cgeist now keeps those calls (Polygeist
// 62c40544, `hls.inline_off` on the callee). This interface makes `--inline`
// keep them too: a call whose callee carries `hls.inline_off` is never
// inlined, and neither is one cgeist kept because Vitis would not inline it
// automatically (`hls.inline_auto_off`, N18, Polygeist W10). Everything else
// behaves as the stock func-dialect interface:
// any call into any region may be inlined (the destination dialect still
// has its say: the affine dialect refuses multi-block or side-effecting
// bodies inside its loops), a func.return becomes a branch to the
// continuation block or replaces the call's results.
//
//===----------------------------------------------------------------------===//

#include "circt/Dialect/Resource/Config/ConfigUtils.h"
#include "circt/Dialect/Resource/Passes/HlsInliner.h"
#include "circt/Dialect/Resource/Passes/CallInstances.h"
#include "mlir/Dialect/ControlFlow/IR/ControlFlowOps.h"
#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/IR/DialectRegistry.h"
#include "mlir/Transforms/InliningUtils.h"
#include "llvm/Support/CommandLine.h"

using namespace mlir;

static llvm::cl::opt<bool> inlineIgnoreInlineOff(
    "inline-ignore-inline-off",
    llvm::cl::desc("--inline: also inline calls to functions carrying "
                   "hls.inline_off (#pragma HLS inline off), as before W3"),
    llvm::cl::init(false));

namespace {
struct HlsFuncInlinerInterface : public DialectInlinerInterface {
  using DialectInlinerInterface::DialectInlinerInterface;

  bool isLegalToInline(Operation *call, Operation *callable,
                       bool wouldBeCloned) const final {
    // --inline-ignore-inline-off when given, else
    // tool.hls.inlining.honour_inline_off (true).
    if (circt::hlsest::resolveGlobalOption(
            inlineIgnoreInlineOff,
            !circt::hlsest::Config::get().tool.hls.honourInlineOff))
      return true;
    // `inline off`, or a call cgeist kept because Vitis would not inline it
    // automatically (hls.inline_auto_off, VITIS_NOTES N18).
    return !circt::hls_analysis::isKeptCallee(callable) &&
           !call->hasAttr(circt::hls_analysis::kInlineAutoOffAttr);
  }
  bool isLegalToInline(Region *, Region *, bool, IRMapping &) const final {
    return true;
  }
  bool isLegalToInline(Operation *, Region *, bool, IRMapping &) const final {
    return true;
  }

  // A func.return at the end of an inlined body: branch to the block that
  // continues after the call, passing the returned values.
  void handleTerminator(Operation *op, Block *newDest) const final {
    auto ret = dyn_cast<func::ReturnOp>(op);
    if (!ret)
      return;
    OpBuilder builder(op);
    cf::BranchOp::create(builder, op->getLoc(), newDest, ret.getOperands());
    op->erase();
  }
  // A single-block body: the returned values replace the call's results.
  void handleTerminator(Operation *op, ValueRange valuesToRepl) const final {
    auto ret = dyn_cast<func::ReturnOp>(op);
    if (!ret)
      return;
    for (auto [i, v] : llvm::enumerate(ret.getOperands()))
      valuesToRepl[i].replaceAllUsesWith(v);
  }
};
} // namespace

void circt::hls_analysis::registerHlsInlinerExtension(
    DialectRegistry &registry) {
  registry.addExtension(+[](MLIRContext *ctx, func::FuncDialect *dialect) {
    dialect->addInterfaces<HlsFuncInlinerInterface>();
  });
}
