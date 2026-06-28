/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Rewriters                                                                  *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: HWCanonicalization.td                                                *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

/* Generated from:
    HWCanonicalization.td:21
*/
struct ArrayInjectToSameIndex : public ::mlir::RewritePattern {
  ArrayInjectToSameIndex(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("hw.array_inject", 2, context, {"hw.array_inject"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range element(op0->getOperands());
    ::mlir::Operation::operand_range index(op0->getOperands());
    ::mlir::Operation::operand_range index0(op0->getOperands());
    ::mlir::Operation::operand_range array(op0->getOperands());
    ::circt::hw::ArrayInjectOp op;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::circt::hw::ArrayInjectOp>(op0); (void)castedOp0;
    op = castedOp0;
    {
      auto *op1 = (*castedOp0.getODSOperands(0).begin()).getDefiningOp();
      if (!(op1)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "There's no operation that defines operand 0 of castedOp0";
        });
      }
      auto castedOp1 = ::llvm::dyn_cast<::circt::hw::ArrayInjectOp>(op1); (void)castedOp1;
      if (!(castedOp1)){
        return rewriter.notifyMatchFailure(op1, [&](::mlir::Diagnostic &diag) {
          diag << "castedOp1 is not ::circt::hw::ArrayInjectOp type";
        });
      }
      array = castedOp1.getODSOperands(0);
      index0 = castedOp1.getODSOperands(1);
      tblgen_ops.push_back(op1);
    }
    index = castedOp0.getODSOperands(1);
    element = castedOp0.getODSOperands(2);
    if (!(*index.begin() == *index0.begin())){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "Operands 'index' and 'index0' must be equal";
      });
    }
    if (!(((*op.getODSResults(0).begin()) != (*array.begin())))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'op, array' failed to satisfy constraint: ''";
      });
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc(), tblgen_ops[1]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    ::circt::hw::ArrayInjectOp tblgen_ArrayInjectOp_0;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::circt::hw::ArrayInjectOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*array.begin()));
      tblgen_values.push_back((*index.begin()));
      tblgen_values.push_back((*element.begin()));
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      tblgen_ArrayInjectOp_0 = ::circt::hw::ArrayInjectOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ tblgen_ArrayInjectOp_0.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

[[maybe_unused]] void populateWithGenerated(::mlir::RewritePatternSet &patterns) {
  patterns.add<ArrayInjectToSameIndex>(patterns.getContext());
}
