

// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#include "circt/Dialect/Resource/Passes/HlsInliner.h"
#include "circt/Dialect/Resource/Passes/CallInstances.h"
#include "mlir/Dialect/ControlFlow/IR/ControlFlowOps.h"
#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/IR/DialectRegistry.h"
#include "mlir/Transforms/InliningUtils.h"
#include "llvm/Support/CommandLine.h"

using namespace mlir;

static llvm::cl::opt<bool> allowInliningKeptCallees(
    "inline-ignore-inline-off",
    llvm::cl::desc("--inline: also inline calls to functions carrying "
                   "hls.inline_off (#pragma HLS inline off), as before W3"),
    llvm::cl::init(false));

namespace {
struct VitisInlinerInterface : public DialectInlinerInterface {
  using DialectInlinerInterface::DialectInlinerInterface;

  bool isLegalToInline(Operation *call, Operation *calledFunction,
                       bool cloneRequested) const final {
    if (allowInliningKeptCallees)
      return true;

    return !circt::hls_analysis::isKeptCallee(calledFunction) &&
           !call->hasAttr(circt::hls_analysis::kInlineAutoOffAttr);
  }
  bool isLegalToInline(Region *, Region *, bool, IRMapping &) const final {
    return true;
  }
  bool isLegalToInline(Operation *, Region *, bool, IRMapping &) const final {
    return true;
  }

  void handleTerminator(Operation *op, Block *continuationBlock) const final {
    auto returnOp = dyn_cast<func::ReturnOp>(op);
    if (!returnOp)
      return;
    OpBuilder passBuilder(op);
    cf::BranchOp::create(passBuilder, op->getLoc(), continuationBlock,
                         returnOp.getOperands());
    op->erase();
  }

  void handleTerminator(Operation *op,
                        ValueRange replacementValues) const final {
    auto returnOp = dyn_cast<func::ReturnOp>(op);
    if (!returnOp)
      return;
    for (auto [loopIndex, valueHandle] :
         llvm::enumerate(returnOp.getOperands()))
      replacementValues[loopIndex].replaceAllUsesWith(valueHandle);
  }
};
} // namespace

void circt::hls_analysis::registerHlsInlinerExtension(
    DialectRegistry &targetRegistry) {
  targetRegistry.addExtension(
      +[](MLIRContext *context, func::FuncDialect *targetDialect) {
        targetDialect->addInterfaces<VitisInlinerInterface>();
      });
}
