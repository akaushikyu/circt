/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Rewriters                                                                  *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: HWArithCanonicalizations.td                                          *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

/* Generated from:
    HWArithCanonicalizations.td:22
*/
struct EliminateCast : public ::mlir::RewritePattern {
  EliminateCast(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("hwarith.cast", 1, context, {}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range in(op0->getOperands());
    ::circt::hwarith::CastOp out;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::circt::hwarith::CastOp>(op0); (void)castedOp0;
    out = castedOp0;
    in = castedOp0.getODSOperands(0);
    if (!(((*in.begin()).getType() == (*out.getODSResults(0).begin()).getType()))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'in, out' failed to satisfy constraint: ''";
      });
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ in }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

[[maybe_unused]] void populateWithGenerated(::mlir::RewritePatternSet &patterns) {
  patterns.add<EliminateCast>(patterns.getContext());
}
