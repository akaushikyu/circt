/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Rewriters                                                                  *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: HandshakeCanonicalization.td                                         *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

/* Generated from:
    HandshakeCanonicalization.td:25
*/
struct EliminateSimpleBranchesPattern : public ::mlir::RewritePattern {
  EliminateSimpleBranchesPattern(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("handshake.br", 1, context, {}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range a(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::circt::handshake::BranchOp>(op0); (void)castedOp0;
    a = castedOp0.getODSOperands(0);

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ a }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    HandshakeCanonicalization.td:27
*/
struct EliminateSimpleForksPattern : public ::mlir::RewritePattern {
  EliminateSimpleForksPattern(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("handshake.fork", 1, context, {}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range arg(op0->getOperands());
    ::circt::handshake::ForkOp op;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::circt::handshake::ForkOp>(op0); (void)castedOp0;
    op = castedOp0;
    arg = castedOp0.getODSOperands(0);
    if (!((op.getODSResults(0).size() == 1))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities '' failed to satisfy constraint: 'has one result'";
      });
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ arg }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    HandshakeCanonicalization.td:22
*/
struct EliminateSimpleMergesPattern : public ::mlir::RewritePattern {
  EliminateSimpleMergesPattern(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("handshake.merge", 1, context, {}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range arg(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::circt::handshake::MergeOp>(op0); (void)castedOp0;
    arg = castedOp0.getODSOperands(0);
    if (!((arg.size() == 1))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities '' failed to satisfy constraint: 'has one operand'";
      });
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ arg }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    HandshakeCanonicalization.td:35
*/
struct EliminateSunkBuffersPattern : public ::mlir::RewritePattern {
  EliminateSunkBuffersPattern(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("handshake.sink", 2, context, {"handshake.sink"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::ArrayAttr initValues;
    ::circt::handshake::BufferTypeEnumAttr bufferType;
    ::mlir::IntegerAttr size;
    ::mlir::Operation::operand_range operand(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::circt::handshake::SinkOp>(op0); (void)castedOp0;
    {
      auto *op1 = (*castedOp0.getODSOperands(0).begin()).getDefiningOp();
      if (!(op1)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "There's no operation that defines operand 0 of castedOp0";
        });
      }
      auto castedOp1 = ::llvm::dyn_cast<::circt::handshake::BufferOp>(op1); (void)castedOp1;
      if (!(castedOp1)){
        return rewriter.notifyMatchFailure(op1, [&](::mlir::Diagnostic &diag) {
          diag << "castedOp1 is not ::circt::handshake::BufferOp type";
        });
      }
      operand = castedOp1.getODSOperands(0);
      {
        [[maybe_unused]] auto tblgen_attr = castedOp1.getProperties().getSlots();
        if (!(tblgen_attr)){
          return rewriter.notifyMatchFailure(castedOp1, [&](::mlir::Diagnostic &diag) {
            diag << "expected op 'handshake.buffer' to have attribute 'slots' of type '::mlir::IntegerAttr'";
          });
        }
        size = tblgen_attr;
      }
      {
        [[maybe_unused]] auto tblgen_attr = castedOp1.getProperties().getBufferType();
        if (!(tblgen_attr)){
          return rewriter.notifyMatchFailure(castedOp1, [&](::mlir::Diagnostic &diag) {
            diag << "expected op 'handshake.buffer' to have attribute 'bufferType' of type '::circt::handshake::BufferTypeEnumAttr'";
          });
        }
        bufferType = tblgen_attr;
      }
      {
        [[maybe_unused]] auto tblgen_attr = castedOp1.getProperties().getInitValues();
        initValues = tblgen_attr;
      }
      tblgen_ops.push_back(op1);
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc(), tblgen_ops[1]->getLoc()}); (void)odsLoc;
    ::circt::handshake::SinkOp tblgen_SinkOp_0;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::circt::handshake::SinkOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*operand.begin()));
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      tblgen_SinkOp_0 = ::circt::handshake::SinkOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }
    rewriter.eraseOp(op0);
    return ::mlir::success();
  }
};

/* Generated from:
    HandshakeCanonicalization.td:31
*/
struct EliminateSunkConstantsPattern : public ::mlir::RewritePattern {
  EliminateSunkConstantsPattern(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("handshake.sink", 2, context, {}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range ctrl(op0->getOperands());
    ::mlir::TypedAttr value;
    ::circt::handshake::SinkOp sink;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::circt::handshake::SinkOp>(op0); (void)castedOp0;
    sink = castedOp0;
    {
      auto *op1 = (*castedOp0.getODSOperands(0).begin()).getDefiningOp();
      if (!(op1)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "There's no operation that defines operand 0 of castedOp0";
        });
      }
      auto castedOp1 = ::llvm::dyn_cast<::circt::handshake::ConstantOp>(op1); (void)castedOp1;
      if (!(castedOp1)){
        return rewriter.notifyMatchFailure(op1, [&](::mlir::Diagnostic &diag) {
          diag << "castedOp1 is not ::circt::handshake::ConstantOp type";
        });
      }
      {
        [[maybe_unused]] auto tblgen_attr = castedOp1.getProperties().getValue();
        if (!(tblgen_attr)){
          return rewriter.notifyMatchFailure(castedOp1, [&](::mlir::Diagnostic &diag) {
            diag << "expected op 'handshake.constant' to have attribute 'value' of type '::mlir::TypedAttr'";
          });
        }
        value = tblgen_attr;
      }
      ctrl = castedOp1.getODSOperands(0);
      tblgen_ops.push_back(op1);
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc(), tblgen_ops[1]->getLoc()}); (void)odsLoc;
    rewriter.eraseOp(op0);
    return ::mlir::success();
  }
};

[[maybe_unused]] void populateWithGenerated(::mlir::RewritePatternSet &patterns) {
  patterns.add<EliminateSimpleBranchesPattern>(patterns.getContext());
  patterns.add<EliminateSimpleForksPattern>(patterns.getContext());
  patterns.add<EliminateSimpleMergesPattern>(patterns.getContext());
  patterns.add<EliminateSunkBuffersPattern>(patterns.getContext());
  patterns.add<EliminateSunkConstantsPattern>(patterns.getContext());
}
