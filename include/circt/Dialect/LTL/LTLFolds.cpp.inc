/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Rewriters                                                                  *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: LTL.td                                                               *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

static ::llvm::LogicalResult static_dag_matcher_0(::mlir::PatternRewriter &rewriter, ::mlir::Operation *op0, ::llvm::SmallVector<::mlir::Operation *, 4> &tblgen_ops, ::mlir::Operation::operand_range &inputs) {
  (void)tblgen_ops;
  auto castedOp1 = ::llvm::dyn_cast<circt::ltl::ConcatOp>(op0); (void)castedOp1;
  if (!(castedOp1)){
    return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
      diag << "castedOp1 is not circt::ltl::ConcatOp type";
    });
  }
  inputs = castedOp1.getODSOperands(0);
  return ::mlir::success();
}

/* Generated from:
    LTLFolds.td:86
*/
struct FlattenConcats : public ::mlir::RewritePattern {
  FlattenConcats(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("ltl.concat", 1, context, {"ltl.concat"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range inputs(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    if(::mlir::failed(static_dag_matcher_0(rewriter, op0, tblgen_ops, inputs))) {
      return ::mlir::failure();
    }
    auto castedOp0 = ::llvm::dyn_cast_or_null<circt::ltl::ConcatOp>(op0); (void)castedOp0;
    if (!((
        llvm::any_of(inputs, [](auto v){
          return !!v.template getDefiningOp<ConcatOp>();
        })
      ))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'inputs' failed to satisfy constraint: 'any value is defined by ConcatOp'";
      });
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    auto nativeVar_0 = flattenConcats(inputs); (void)nativeVar_0;
    circt::ltl::ConcatOp tblgen_ConcatOp_1;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      circt::ltl::ConcatOp::Properties tblgen_props; (void)tblgen_props;
      for (auto v: nativeVar_0) {
        tblgen_values.push_back(v);
      }
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      tblgen_ConcatOp_1 = circt::ltl::ConcatOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ tblgen_ConcatOp_1.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    LTLFolds.td:68
*/
struct MoveClockedDelayIntoConcat : public ::mlir::RewritePattern {
  MoveClockedDelayIntoConcat(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("ltl.clocked_delay", 2, context, {"ltl.clocked_delay", "ltl.concat"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::IntegerAttr length;
    ::mlir::IntegerAttr delay;
    ::mlir::Operation::operand_range clock(op0->getOperands());
    circt::ltl::ClockEdgeAttr edge;
    ::mlir::Operation::operand_range inputs(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<circt::ltl::ClockedDelayOp>(op0); (void)castedOp0;
    {
      auto *op1 = (*castedOp0.getODSOperands(0).begin()).getDefiningOp();
      if (!(op1)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "There's no operation that defines operand 0 of castedOp0";
        });
      }
      if(::mlir::failed(static_dag_matcher_0(rewriter, op1, tblgen_ops, inputs))) {
        return ::mlir::failure();
      }
      tblgen_ops.push_back(op1);
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getEdge();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'ltl.clocked_delay' to have attribute 'edge' of type 'circt::ltl::ClockEdgeAttr'";
        });
      }
      edge = tblgen_attr;
    }
    clock = castedOp0.getODSOperands(1);
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getDelay();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'ltl.clocked_delay' to have attribute 'delay' of type '::mlir::IntegerAttr'";
        });
      }
      delay = tblgen_attr;
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getLength();
      length = tblgen_attr;
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc(), tblgen_ops[1]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    auto nativeVar_0 = inputs[0]; (void)nativeVar_0;
    circt::ltl::ClockedDelayOp tblgen_ClockedDelayOp_1;
    {
      ::mlir::Value tblgen_value_0 = nativeVar_0;
      ::mlir::Value tblgen_value_1 = (*clock.begin());
      tblgen_ClockedDelayOp_1 = circt::ltl::ClockedDelayOp::create(rewriter, odsLoc,
        /*input=*/tblgen_value_0,
        /*edge=*/edge,
        /*clock=*/tblgen_value_1,
        /*delay=*/delay,
        /*length=*/length
      );
    }
    auto nativeVar_2 = inputs.drop_front(); (void)nativeVar_2;
    auto nativeVar_3 = concatValues(ValueRange{tblgen_ClockedDelayOp_1}, ValueRange{nativeVar_2}); (void)nativeVar_3;
    circt::ltl::ConcatOp tblgen_ConcatOp_4;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      circt::ltl::ConcatOp::Properties tblgen_props; (void)tblgen_props;
      for (auto v: nativeVar_3) {
        tblgen_values.push_back(v);
      }
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      tblgen_ConcatOp_4 = circt::ltl::ConcatOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ tblgen_ConcatOp_4.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    LTLFolds.td:48
*/
struct MoveDelayIntoConcat : public ::mlir::RewritePattern {
  MoveDelayIntoConcat(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("ltl.delay", 2, context, {"ltl.concat", "ltl.delay"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::IntegerAttr length;
    ::mlir::IntegerAttr delay;
    ::mlir::Operation::operand_range inputs(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<circt::ltl::DelayOp>(op0); (void)castedOp0;
    {
      auto *op1 = (*castedOp0.getODSOperands(0).begin()).getDefiningOp();
      if (!(op1)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "There's no operation that defines operand 0 of castedOp0";
        });
      }
      if(::mlir::failed(static_dag_matcher_0(rewriter, op1, tblgen_ops, inputs))) {
        return ::mlir::failure();
      }
      tblgen_ops.push_back(op1);
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getDelay();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'ltl.delay' to have attribute 'delay' of type '::mlir::IntegerAttr'";
        });
      }
      delay = tblgen_attr;
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getLength();
      length = tblgen_attr;
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc(), tblgen_ops[1]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    auto nativeVar_0 = inputs[0]; (void)nativeVar_0;
    circt::ltl::DelayOp tblgen_DelayOp_1;
    {
      ::mlir::Value tblgen_value_0 = nativeVar_0;
      tblgen_DelayOp_1 = circt::ltl::DelayOp::create(rewriter, odsLoc,
        /*input=*/tblgen_value_0,
        /*delay=*/delay,
        /*length=*/length
      );
    }
    auto nativeVar_2 = inputs.drop_front(); (void)nativeVar_2;
    auto nativeVar_3 = concatValues(ValueRange{tblgen_DelayOp_1}, ValueRange{nativeVar_2}); (void)nativeVar_3;
    circt::ltl::ConcatOp tblgen_ConcatOp_4;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      circt::ltl::ConcatOp::Properties tblgen_props; (void)tblgen_props;
      for (auto v: nativeVar_3) {
        tblgen_values.push_back(v);
      }
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      tblgen_ConcatOp_4 = circt::ltl::ConcatOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ tblgen_ConcatOp_4.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    LTLFolds.td:59
*/
struct NestedClockedDelays : public ::mlir::RewritePattern {
  NestedClockedDelays(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("ltl.clocked_delay", 2, context, {"ltl.clocked_delay"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::IntegerAttr length1;
    ::mlir::IntegerAttr delay1;
    ::mlir::Operation::operand_range clock1(op0->getOperands());
    ::mlir::IntegerAttr delay0;
    circt::ltl::ClockEdgeAttr edge1;
    ::mlir::Operation::operand_range clock0(op0->getOperands());
    ::mlir::IntegerAttr length0;
    circt::ltl::ClockEdgeAttr edge0;
    ::mlir::Operation::operand_range input(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<circt::ltl::ClockedDelayOp>(op0); (void)castedOp0;
    {
      auto *op1 = (*castedOp0.getODSOperands(0).begin()).getDefiningOp();
      if (!(op1)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "There's no operation that defines operand 0 of castedOp0";
        });
      }
      auto castedOp1 = ::llvm::dyn_cast<circt::ltl::ClockedDelayOp>(op1); (void)castedOp1;
      if (!(castedOp1)){
        return rewriter.notifyMatchFailure(op1, [&](::mlir::Diagnostic &diag) {
          diag << "castedOp1 is not circt::ltl::ClockedDelayOp type";
        });
      }
      input = castedOp1.getODSOperands(0);
      {
        [[maybe_unused]] auto tblgen_attr = castedOp1.getProperties().getEdge();
        if (!(tblgen_attr)){
          return rewriter.notifyMatchFailure(castedOp1, [&](::mlir::Diagnostic &diag) {
            diag << "expected op 'ltl.clocked_delay' to have attribute 'edge' of type 'circt::ltl::ClockEdgeAttr'";
          });
        }
        edge0 = tblgen_attr;
      }
      clock0 = castedOp1.getODSOperands(1);
      {
        [[maybe_unused]] auto tblgen_attr = castedOp1.getProperties().getDelay();
        if (!(tblgen_attr)){
          return rewriter.notifyMatchFailure(castedOp1, [&](::mlir::Diagnostic &diag) {
            diag << "expected op 'ltl.clocked_delay' to have attribute 'delay' of type '::mlir::IntegerAttr'";
          });
        }
        delay0 = tblgen_attr;
      }
      {
        [[maybe_unused]] auto tblgen_attr = castedOp1.getProperties().getLength();
        length0 = tblgen_attr;
      }
      tblgen_ops.push_back(op1);
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getEdge();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'ltl.clocked_delay' to have attribute 'edge' of type 'circt::ltl::ClockEdgeAttr'";
        });
      }
      edge1 = tblgen_attr;
    }
    clock1 = castedOp0.getODSOperands(1);
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getDelay();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'ltl.clocked_delay' to have attribute 'delay' of type '::mlir::IntegerAttr'";
        });
      }
      delay1 = tblgen_attr;
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getLength();
      length1 = tblgen_attr;
    }
    if (!(((*clock0.begin()) == (*clock1.begin()) && edge0 == edge1))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'clock0, clock1, edge0, edge1' failed to satisfy constraint: ''";
      });
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc(), tblgen_ops[1]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    auto nativeVar_0 = rewriter.getI64IntegerAttr(delay0.getInt() + delay1.getInt()); (void)nativeVar_0;
    auto nativeVar_1 = 
      length0 && length1 ? rewriter.getI64IntegerAttr(length0.getInt() + length1.getInt())
               : IntegerAttr{}
    ; (void)nativeVar_1;
    circt::ltl::ClockedDelayOp tblgen_ClockedDelayOp_2;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      circt::ltl::ClockedDelayOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*input.begin()));
      tblgen_props.edge = ::llvm::dyn_cast_if_present<decltype(tblgen_props.edge)>(edge0);
      tblgen_values.push_back((*clock0.begin()));
      tblgen_props.delay = ::llvm::dyn_cast_if_present<decltype(tblgen_props.delay)>(nativeVar_0);
      tblgen_props.length = ::llvm::dyn_cast_if_present<decltype(tblgen_props.length)>(nativeVar_1);
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      tblgen_ClockedDelayOp_2 = circt::ltl::ClockedDelayOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ tblgen_ClockedDelayOp_2.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    LTLFolds.td:42
*/
struct NestedDelays : public ::mlir::RewritePattern {
  NestedDelays(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("ltl.delay", 2, context, {"ltl.delay"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::IntegerAttr delay2;
    ::mlir::IntegerAttr length1;
    ::mlir::IntegerAttr delay1;
    ::mlir::IntegerAttr length2;
    ::mlir::Operation::operand_range input(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<circt::ltl::DelayOp>(op0); (void)castedOp0;
    {
      auto *op1 = (*castedOp0.getODSOperands(0).begin()).getDefiningOp();
      if (!(op1)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "There's no operation that defines operand 0 of castedOp0";
        });
      }
      auto castedOp1 = ::llvm::dyn_cast<circt::ltl::DelayOp>(op1); (void)castedOp1;
      if (!(castedOp1)){
        return rewriter.notifyMatchFailure(op1, [&](::mlir::Diagnostic &diag) {
          diag << "castedOp1 is not circt::ltl::DelayOp type";
        });
      }
      input = castedOp1.getODSOperands(0);
      {
        [[maybe_unused]] auto tblgen_attr = castedOp1.getProperties().getDelay();
        if (!(tblgen_attr)){
          return rewriter.notifyMatchFailure(castedOp1, [&](::mlir::Diagnostic &diag) {
            diag << "expected op 'ltl.delay' to have attribute 'delay' of type '::mlir::IntegerAttr'";
          });
        }
        delay1 = tblgen_attr;
      }
      {
        [[maybe_unused]] auto tblgen_attr = castedOp1.getProperties().getLength();
        length1 = tblgen_attr;
      }
      tblgen_ops.push_back(op1);
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getDelay();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'ltl.delay' to have attribute 'delay' of type '::mlir::IntegerAttr'";
        });
      }
      delay2 = tblgen_attr;
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getLength();
      length2 = tblgen_attr;
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc(), tblgen_ops[1]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    auto nativeVar_0 = rewriter.getI64IntegerAttr(delay1.getInt() + delay2.getInt()); (void)nativeVar_0;
    auto nativeVar_1 = 
      length1 && length2 ? rewriter.getI64IntegerAttr(length1.getInt() + length2.getInt())
               : IntegerAttr{}
    ; (void)nativeVar_1;
    circt::ltl::DelayOp tblgen_DelayOp_2;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      circt::ltl::DelayOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*input.begin()));
      tblgen_props.delay = ::llvm::dyn_cast_if_present<decltype(tblgen_props.delay)>(nativeVar_0);
      tblgen_props.length = ::llvm::dyn_cast_if_present<decltype(tblgen_props.length)>(nativeVar_1);
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      tblgen_DelayOp_2 = circt::ltl::DelayOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ tblgen_DelayOp_2.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

[[maybe_unused]] void populateWithGenerated(::mlir::RewritePatternSet &patterns) {
  patterns.add<FlattenConcats>(patterns.getContext());
  patterns.add<MoveClockedDelayIntoConcat>(patterns.getContext());
  patterns.add<MoveDelayIntoConcat>(patterns.getContext());
  patterns.add<NestedClockedDelays>(patterns.getContext());
  patterns.add<NestedDelays>(patterns.getContext());
}
