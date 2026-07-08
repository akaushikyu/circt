//===- VitisFold.cpp - fold the forms Vitis optimizes -------------------- ===//

#include "circt/Dialect/Resource/Passes/VitisCleanup.h"

#include "mlir/Dialect/Arith/IR/Arith.h"
#include "mlir/IR/Matchers.h"
#include "mlir/IR/PatternMatch.h"
#include "mlir/Pass/Pass.h"
#include "mlir/Transforms/GreedyPatternRewriteDriver.h"

using namespace mlir;

namespace {

/// x / 0 and x % 0 (integer or index, scalar or splat) -> 0.
template <typename OpTy>
struct FoldIntDivByZero : OpRewritePattern<OpTy> {
  using OpRewritePattern<OpTy>::OpRewritePattern;

  LogicalResult matchAndRewrite(OpTy op,
                                PatternRewriter &rewriter) const override {
    if (!matchPattern(op.getRhs(), m_Zero()))
      return failure();
    Type memRefType = op.getType();
    TypedAttr zero = rewriter.getZeroAttr(memRefType);
    if (!zero)
      return failure();
    rewriter.replaceOpWithNewOp<arith::ConstantOp>(op, memRefType, zero);
    return success();
  }
};

struct VitisFoldPass : PassWrapper<VitisFoldPass, OperationPass<>> {
  MLIR_DEFINE_EXPLICIT_INTERNAL_INLINE_TYPE_ID(VitisFoldPass)

  VitisFoldPass() = default;
  VitisFoldPass(const VitisFoldPass &other) : PassWrapper(other) {}

  Option<bool> canonicalize{
      *this, "canonicalize",
      llvm::cl::desc("Also apply every loaded dialect's canonicalization "
                     "patterns and the op folders in the same greedy rewrite, "
                     "so a folded zero propagates (x*0 -> 0 for integers); "
                     "false: only x/0 -> 0"),
      llvm::cl::init(true)};

  StringRef getArgument() const final { return "vitis-fold"; }
  StringRef getDescription() const final {
    return "Fold what Vitis HLS folds but MLIR does not: integer division / "
           "remainder by a constant zero -> 0 (VITIS_NOTES.md N1a), then the "
           "canonicalization folds";
  }
  void getDependentDialects(DialectRegistry &targetRegistry) const override {
    targetRegistry.insert<arith::ArithDialect>();
  }

  void runOnOperation() override {
    MLIRContext *context = &getContext();
    RewritePatternSet patterns(context);
    patterns
        .add<FoldIntDivByZero<arith::DivSIOp>, FoldIntDivByZero<arith::DivUIOp>,
             FoldIntDivByZero<arith::RemSIOp>, FoldIntDivByZero<arith::RemUIOp>,
             FoldIntDivByZero<arith::CeilDivSIOp>,
             FoldIntDivByZero<arith::CeilDivUIOp>,
             FoldIntDivByZero<arith::FloorDivSIOp>>(context);
    if (canonicalize) {
      for (Dialect *targetDialect : context->getLoadedDialects())
        targetDialect->getCanonicalizationPatterns(patterns);
      for (RegisteredOperationName op : context->getRegisteredOperations())
        op.getCanonicalizationPatterns(patterns, context);
    }

    GreedyRewriteConfig config;
    config.enableFolding(canonicalize);
    (void)applyPatternsGreedily(getOperation(), std::move(patterns), config);
  }
};

} // namespace

namespace circt::hls_analysis {
std::unique_ptr<Pass> createVitisFoldPass() {
  return std::make_unique<VitisFoldPass>();
}
} // namespace circt::hls_analysis
