/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Rewriters                                                                  *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: FIRRTLCanonicalization.td                                            *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/


static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_FIRRTLCanonicalization1(
    ::mlir::PatternRewriter &rewriter, ::mlir::Operation *op, ::mlir::Attribute attr,
    ::llvm::StringRef failureStr) {
  if (!(((::llvm::isa<::mlir::IntegerAttr>(attr))) && ((::llvm::cast<::mlir::IntegerAttr>(attr).getType().isSignlessInteger(32))))) {
    return rewriter.notifyMatchFailure(op, [&](::mlir::Diagnostic &diag) {
      diag << failureStr << ": 32-bit signless integer attribute";
    });
  }
  return ::mlir::success();
}
static ::llvm::LogicalResult static_dag_matcher_0(::mlir::PatternRewriter &rewriter, ::mlir::Operation *op0, ::llvm::SmallVector<::mlir::Operation *, 4> &tblgen_ops, ::mlir::IntegerAttr &m, ::mlir::Operation::operand_range &a) {
  (void)tblgen_ops;
  auto castedOp1 = ::llvm::dyn_cast<::circt::firrtl::PadPrimOp>(op0); (void)castedOp1;
  if (!(castedOp1)){
    return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
      diag << "castedOp1 is not ::circt::firrtl::PadPrimOp type";
    });
  }
  a = castedOp1.getODSOperands(0);
  {
    [[maybe_unused]] auto tblgen_attr = castedOp1.getProperties().getAmount();
    if (!(tblgen_attr)){
      return rewriter.notifyMatchFailure(castedOp1, [&](::mlir::Diagnostic &diag) {
        diag << "expected op 'firrtl.pad' to have attribute 'amount' of type '::mlir::IntegerAttr'";
      });
    }
    m = tblgen_attr;
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult static_dag_matcher_1(::mlir::PatternRewriter &rewriter, ::mlir::Operation *op0, ::llvm::SmallVector<::mlir::Operation *, 4> &tblgen_ops, ::circt::firrtl::ConstantOp &zcst) {
  (void)tblgen_ops;
  auto castedOp1 = ::llvm::dyn_cast<::circt::firrtl::ConstantOp>(op0); (void)castedOp1;
  if (!(castedOp1)){
    return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
      diag << "castedOp1 is not ::circt::firrtl::ConstantOp type";
    });
  }
  zcst = castedOp1;
  {
    [[maybe_unused]] auto tblgen_attr = castedOp1.getProperties().getValue();
    if (!(tblgen_attr)){
      return rewriter.notifyMatchFailure(castedOp1, [&](::mlir::Diagnostic &diag) {
        diag << "expected op 'firrtl.constant' to have attribute 'value' of type '::mlir::IntegerAttr'";
      });
    }
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult static_dag_matcher_2(::mlir::PatternRewriter &rewriter, ::mlir::Operation *op0, ::llvm::SmallVector<::mlir::Operation *, 4> &tblgen_ops, ::mlir::IntegerAttr &cst, ::circt::firrtl::ConstantOp &ocst) {
  (void)tblgen_ops;
  auto castedOp1 = ::llvm::dyn_cast<::circt::firrtl::ConstantOp>(op0); (void)castedOp1;
  if (!(castedOp1)){
    return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
      diag << "castedOp1 is not ::circt::firrtl::ConstantOp type";
    });
  }
  ocst = castedOp1;
  {
    [[maybe_unused]] auto tblgen_attr = castedOp1.getProperties().getValue();
    if (!(tblgen_attr)){
      return rewriter.notifyMatchFailure(castedOp1, [&](::mlir::Diagnostic &diag) {
        diag << "expected op 'firrtl.constant' to have attribute 'value' of type '::mlir::IntegerAttr'";
      });
    }
    cst = tblgen_attr;
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult static_dag_matcher_3(::mlir::PatternRewriter &rewriter, ::mlir::Operation *op0, ::llvm::SmallVector<::mlir::Operation *, 4> &tblgen_ops, ::mlir::Operation::operand_range &x) {
  (void)tblgen_ops;
  auto castedOp1 = ::llvm::dyn_cast<::circt::firrtl::AsSIntPrimOp>(op0); (void)castedOp1;
  if (!(castedOp1)){
    return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
      diag << "castedOp1 is not ::circt::firrtl::AsSIntPrimOp type";
    });
  }
  x = castedOp1.getODSOperands(0);
  return ::mlir::success();
}

static ::llvm::LogicalResult static_dag_matcher_4(::mlir::PatternRewriter &rewriter, ::mlir::Operation *op0, ::llvm::SmallVector<::mlir::Operation *, 4> &tblgen_ops, ::mlir::IntegerAttr &n, ::mlir::Operation::operand_range &y, ::circt::firrtl::PadPrimOp &pad) {
  (void)tblgen_ops;
  auto castedOp1 = ::llvm::dyn_cast<::circt::firrtl::PadPrimOp>(op0); (void)castedOp1;
  if (!(castedOp1)){
    return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
      diag << "castedOp1 is not ::circt::firrtl::PadPrimOp type";
    });
  }
  pad = castedOp1;
  y = castedOp1.getODSOperands(0);
  {
    [[maybe_unused]] auto tblgen_attr = castedOp1.getProperties().getAmount();
    if (!(tblgen_attr)){
      return rewriter.notifyMatchFailure(castedOp1, [&](::mlir::Diagnostic &diag) {
        diag << "expected op 'firrtl.pad' to have attribute 'amount' of type '::mlir::IntegerAttr'";
      });
    }
    n = tblgen_attr;
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult static_dag_matcher_5(::mlir::PatternRewriter &rewriter, ::mlir::Operation *op0, ::llvm::SmallVector<::mlir::Operation *, 4> &tblgen_ops, ::mlir::IntegerAttr &cst, ::circt::firrtl::ConstantOp &zcst) {
  (void)tblgen_ops;
  auto castedOp1 = ::llvm::dyn_cast<::circt::firrtl::ConstantOp>(op0); (void)castedOp1;
  if (!(castedOp1)){
    return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
      diag << "castedOp1 is not ::circt::firrtl::ConstantOp type";
    });
  }
  zcst = castedOp1;
  {
    [[maybe_unused]] auto tblgen_attr = castedOp1.getProperties().getValue();
    if (!(tblgen_attr)){
      return rewriter.notifyMatchFailure(castedOp1, [&](::mlir::Diagnostic &diag) {
        diag << "expected op 'firrtl.constant' to have attribute 'value' of type '::mlir::IntegerAttr'";
      });
    }
    cst = tblgen_attr;
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult static_dag_matcher_6(::mlir::PatternRewriter &rewriter, ::mlir::Operation *op0, ::llvm::SmallVector<::mlir::Operation *, 4> &tblgen_ops, ::mlir::Operation::operand_range &z) {
  (void)tblgen_ops;
  auto castedOp1 = ::llvm::dyn_cast<::circt::firrtl::AndRPrimOp>(op0); (void)castedOp1;
  if (!(castedOp1)){
    return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
      diag << "castedOp1 is not ::circt::firrtl::AndRPrimOp type";
    });
  }
  z = castedOp1.getODSOperands(0);
  return ::mlir::success();
}

static ::llvm::LogicalResult static_dag_matcher_7(::mlir::PatternRewriter &rewriter, ::mlir::Operation *op0, ::llvm::SmallVector<::mlir::Operation *, 4> &tblgen_ops, ::mlir::IntegerAttr &n, ::mlir::Operation::operand_range &x, ::circt::firrtl::PadPrimOp &pad) {
  (void)tblgen_ops;
  auto castedOp1 = ::llvm::dyn_cast<::circt::firrtl::PadPrimOp>(op0); (void)castedOp1;
  if (!(castedOp1)){
    return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
      diag << "castedOp1 is not ::circt::firrtl::PadPrimOp type";
    });
  }
  pad = castedOp1;
  x = castedOp1.getODSOperands(0);
  {
    [[maybe_unused]] auto tblgen_attr = castedOp1.getProperties().getAmount();
    if (!(tblgen_attr)){
      return rewriter.notifyMatchFailure(castedOp1, [&](::mlir::Diagnostic &diag) {
        diag << "expected op 'firrtl.pad' to have attribute 'amount' of type '::mlir::IntegerAttr'";
      });
    }
    n = tblgen_attr;
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult static_dag_matcher_8(::mlir::PatternRewriter &rewriter, ::mlir::Operation *op0, ::llvm::SmallVector<::mlir::Operation *, 4> &tblgen_ops, ::mlir::IntegerAttr &n, ::mlir::Operation::operand_range &x, ::circt::firrtl::PadPrimOp &pad, ::circt::firrtl::AndRPrimOp &old) {
  (void)tblgen_ops;
  auto castedOp1 = ::llvm::dyn_cast<::circt::firrtl::AndRPrimOp>(op0); (void)castedOp1;
  if (!(castedOp1)){
    return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
      diag << "castedOp1 is not ::circt::firrtl::AndRPrimOp type";
    });
  }
  old = castedOp1;
  {
    auto *op2 = (*castedOp1.getODSOperands(0).begin()).getDefiningOp();
    if (!(op2)){
      return rewriter.notifyMatchFailure(castedOp1, [&](::mlir::Diagnostic &diag) {
        diag << "There's no operation that defines operand 0 of castedOp1";
      });
    }
    if(::mlir::failed(static_dag_matcher_7(rewriter, op2, tblgen_ops, n, x, pad))) {
      return ::mlir::failure();
    }
    tblgen_ops.push_back(op2);
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult static_dag_matcher_9(::mlir::PatternRewriter &rewriter, ::mlir::Operation *op0, ::llvm::SmallVector<::mlir::Operation *, 4> &tblgen_ops, ::mlir::Operation::operand_range &x) {
  (void)tblgen_ops;
  auto castedOp1 = ::llvm::dyn_cast<::circt::firrtl::AsUIntPrimOp>(op0); (void)castedOp1;
  if (!(castedOp1)){
    return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
      diag << "castedOp1 is not ::circt::firrtl::AsUIntPrimOp type";
    });
  }
  x = castedOp1.getODSOperands(0);
  return ::mlir::success();
}

static ::llvm::LogicalResult static_dag_matcher_10(::mlir::PatternRewriter &rewriter, ::mlir::Operation *op0, ::llvm::SmallVector<::mlir::Operation *, 4> &tblgen_ops, ::mlir::Operation::operand_range &src, ::mlir::Operation::operand_range &dst) {
  (void)tblgen_ops;
  auto castedOp1 = ::llvm::dyn_cast<::circt::firrtl::ConnectOp>(op0); (void)castedOp1;
  if (!(castedOp1)){
    return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
      diag << "castedOp1 is not ::circt::firrtl::ConnectOp type";
    });
  }
  dst = castedOp1.getODSOperands(0);
  src = castedOp1.getODSOperands(1);
  return ::mlir::success();
}

static ::llvm::LogicalResult static_dag_matcher_11(::mlir::PatternRewriter &rewriter, ::mlir::Operation *op0, ::llvm::SmallVector<::mlir::Operation *, 4> &tblgen_ops, ::mlir::IntegerAttr &cst) {
  (void)tblgen_ops;
  auto castedOp1 = ::llvm::dyn_cast<::circt::firrtl::ConstantOp>(op0); (void)castedOp1;
  if (!(castedOp1)){
    return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
      diag << "castedOp1 is not ::circt::firrtl::ConstantOp type";
    });
  }
  {
    [[maybe_unused]] auto tblgen_attr = castedOp1.getProperties().getValue();
    if (!(tblgen_attr)){
      return rewriter.notifyMatchFailure(castedOp1, [&](::mlir::Diagnostic &diag) {
        diag << "expected op 'firrtl.constant' to have attribute 'value' of type '::mlir::IntegerAttr'";
      });
    }
    cst = tblgen_attr;
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult static_dag_matcher_12(::mlir::PatternRewriter &rewriter, ::mlir::Operation *op0, ::llvm::SmallVector<::mlir::Operation *, 4> &tblgen_ops, ::mlir::Operation::operand_range &f, ::mlir::Operation::operand_range &t, ::mlir::Operation::operand_range &cond2) {
  (void)tblgen_ops;
  auto castedOp1 = ::llvm::dyn_cast<::circt::firrtl::MuxPrimOp>(op0); (void)castedOp1;
  if (!(castedOp1)){
    return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
      diag << "castedOp1 is not ::circt::firrtl::MuxPrimOp type";
    });
  }
  cond2 = castedOp1.getODSOperands(0);
  t = castedOp1.getODSOperands(1);
  f = castedOp1.getODSOperands(2);
  return ::mlir::success();
}

static ::llvm::LogicalResult static_dag_matcher_13(::mlir::PatternRewriter &rewriter, ::mlir::Operation *op0, ::llvm::SmallVector<::mlir::Operation *, 4> &tblgen_ops, ::mlir::Operation::operand_range &a, ::mlir::Operation::operand_range &b, ::circt::firrtl::CatPrimOp &lhs) {
  (void)tblgen_ops;
  auto castedOp1 = ::llvm::dyn_cast<::circt::firrtl::CatPrimOp>(op0); (void)castedOp1;
  if (!(castedOp1)){
    return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
      diag << "castedOp1 is not ::circt::firrtl::CatPrimOp type";
    });
  }
  lhs = castedOp1;
  {
    auto variadic_operand_range = castedOp1.getODSOperands(0);
    if (variadic_operand_range.size() != 2) return ::mlir::failure();
    a = variadic_operand_range.slice(0, 1);
    b = variadic_operand_range.slice(1, 1);
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult static_dag_matcher_14(::mlir::PatternRewriter &rewriter, ::mlir::Operation *op0, ::llvm::SmallVector<::mlir::Operation *, 4> &tblgen_ops, ::mlir::Operation::operand_range &z) {
  (void)tblgen_ops;
  auto castedOp1 = ::llvm::dyn_cast<::circt::firrtl::OrRPrimOp>(op0); (void)castedOp1;
  if (!(castedOp1)){
    return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
      diag << "castedOp1 is not ::circt::firrtl::OrRPrimOp type";
    });
  }
  z = castedOp1.getODSOperands(0);
  return ::mlir::success();
}

static ::llvm::LogicalResult static_dag_matcher_15(::mlir::PatternRewriter &rewriter, ::mlir::Operation *op0, ::llvm::SmallVector<::mlir::Operation *, 4> &tblgen_ops, ::mlir::Operation::operand_range &x, ::mlir::IntegerAttr &cst, ::circt::firrtl::ConstantOp &zcst, ::circt::firrtl::SubPrimOp &old) {
  (void)tblgen_ops;
  auto castedOp1 = ::llvm::dyn_cast<::circt::firrtl::SubPrimOp>(op0); (void)castedOp1;
  if (!(castedOp1)){
    return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
      diag << "castedOp1 is not ::circt::firrtl::SubPrimOp type";
    });
  }
  old = castedOp1;
  {
    auto *op2 = (*castedOp1.getODSOperands(0).begin()).getDefiningOp();
    if (!(op2)){
      return rewriter.notifyMatchFailure(castedOp1, [&](::mlir::Diagnostic &diag) {
        diag << "There's no operation that defines operand 0 of castedOp1";
      });
    }
    if(::mlir::failed(static_dag_matcher_5(rewriter, op2, tblgen_ops, cst, zcst))) {
      return ::mlir::failure();
    }
    tblgen_ops.push_back(op2);
  }
  x = castedOp1.getODSOperands(1);
  return ::mlir::success();
}

static ::llvm::LogicalResult static_dag_matcher_16(::mlir::PatternRewriter &rewriter, ::mlir::Operation *op0, ::llvm::SmallVector<::mlir::Operation *, 4> &tblgen_ops, ::mlir::Operation::operand_range &z) {
  (void)tblgen_ops;
  auto castedOp1 = ::llvm::dyn_cast<::circt::firrtl::XorRPrimOp>(op0); (void)castedOp1;
  if (!(castedOp1)){
    return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
      diag << "castedOp1 is not ::circt::firrtl::XorRPrimOp type";
    });
  }
  z = castedOp1.getODSOperands(0);
  return ::mlir::success();
}

/* Generated from:
    FIRRTLCanonicalization.td:302
*/
struct AddOfPad : public ::mlir::RewritePattern {
  AddOfPad(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("firrtl.add", 2, context, {"firrtl.add", "firrtl.pad"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::IntegerAttr m;
    ::mlir::Operation::operand_range a(op0->getOperands());
    ::mlir::Operation::operand_range b(op0->getOperands());
    ::circt::firrtl::AddPrimOp old;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::circt::firrtl::AddPrimOp>(op0); (void)castedOp0;
    old = castedOp0;
    auto eitherLambda0 = [&](::mlir::OperandRange v0, ::mlir::OperandRange v1) {
      auto local_op_0 = (*v0.begin()).getDefiningOp();
      {
        if (!(local_op_0)){
          return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
            diag << "There's no operation that defines operand 0 of castedOp0";
          });
        }
        if(::mlir::failed(static_dag_matcher_0(rewriter, local_op_0, tblgen_ops, m, a))) {
          return ::mlir::failure();
        }
      }
      b = v1;
      tblgen_ops.push_back(local_op_0);
      return ::mlir::success();
    };
    {
      auto eitherOperand0 = castedOp0.getODSOperands(0);
      auto eitherOperand1 = castedOp0.getODSOperands(1);
      if(::mlir::failed(eitherLambda0(eitherOperand0, eitherOperand1)) && ::mlir::failed(eitherLambda0(eitherOperand1, eitherOperand0)))
        return ::mlir::failure();
    }
    if (!((
      type_isa<FIRRTLBaseType>((*a.begin()).getType()) &&
        !type_cast<FIRRTLBaseType>((*a.begin()).getType()).getRecursiveTypeProperties().hasUninferredWidth
      ))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'a' failed to satisfy constraint: ''";
      });
    }
    if (!((
      type_isa<FIRRTLBaseType>((*b.begin()).getType()) &&
        !type_cast<FIRRTLBaseType>((*b.begin()).getType()).getRecursiveTypeProperties().hasUninferredWidth
      ))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'b' failed to satisfy constraint: ''";
      });
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc(), tblgen_ops[1]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    ::circt::firrtl::AddPrimOp tblgen_AddPrimOp_0;
    {
      ::mlir::Value tblgen_value_0 = (*a.begin());
      ::mlir::Value tblgen_value_1 = (*b.begin());
      tblgen_AddPrimOp_0 = ::circt::firrtl::AddPrimOp::create(rewriter, odsLoc,
        /*lhs=*/tblgen_value_0,
        /*rhs=*/tblgen_value_1
      );
    }
    auto nativeVar_1 = moveNameHint((*old.getODSResults(0).begin()), tblgen_AddPrimOp_0); (void)nativeVar_1;
    auto nativeVar_2 = rewriter.getI32IntegerAttr(type_cast<FIRRTLBaseType>((*old.getODSResults(0).begin()).getType()).getBitWidthOrSentinel()); (void)nativeVar_2;
    ::circt::firrtl::PadPrimOp tblgen_PadPrimOp_3;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::circt::firrtl::PadPrimOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back(nativeVar_1);
      tblgen_props.amount = ::llvm::dyn_cast_if_present<decltype(tblgen_props.amount)>(nativeVar_2);
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      tblgen_PadPrimOp_3 = ::circt::firrtl::PadPrimOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ tblgen_PadPrimOp_3.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    FIRRTLCanonicalization.td:296
*/
struct AddOfSelf : public ::mlir::RewritePattern {
  AddOfSelf(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("firrtl.add", 1, context, {"firrtl.shl"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range x(op0->getOperands());
    ::mlir::Operation::operand_range x0(op0->getOperands());
    ::circt::firrtl::AddPrimOp old;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::circt::firrtl::AddPrimOp>(op0); (void)castedOp0;
    old = castedOp0;
    x0 = castedOp0.getODSOperands(0);
    x = castedOp0.getODSOperands(1);
    if (!(*x.begin() == *x0.begin())){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "Operands 'x' and 'x0' must be equal";
      });
    }
    if (!((
      type_isa<FIRRTLBaseType>((*x.begin()).getType()) &&
        !type_cast<FIRRTLBaseType>((*x.begin()).getType()).getRecursiveTypeProperties().hasUninferredWidth
      ))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'x' failed to satisfy constraint: ''";
      });
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    auto nativeVar_0 = 1; (void)nativeVar_0;
    ::circt::firrtl::ShlPrimOp tblgen_ShlPrimOp_1;
    {
      ::mlir::Value tblgen_value_0 = (*x.begin());
      tblgen_ShlPrimOp_1 = ::circt::firrtl::ShlPrimOp::create(rewriter, odsLoc,
        /*input=*/tblgen_value_0,
        /*amount=*/nativeVar_0
      );
    }
    auto nativeVar_2 = moveNameHint((*old.getODSResults(0).begin()), tblgen_ShlPrimOp_1); (void)nativeVar_2;

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ {nativeVar_2} }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    FIRRTLCanonicalization.td:290
*/
struct AddOfZero : public ::mlir::RewritePattern {
  AddOfZero(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("firrtl.add", 2, context, {"firrtl.pad"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::circt::firrtl::ConstantOp zcst;
    ::mlir::Operation::operand_range x(op0->getOperands());
    ::circt::firrtl::AddPrimOp old;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::circt::firrtl::AddPrimOp>(op0); (void)castedOp0;
    old = castedOp0;
    x = castedOp0.getODSOperands(0);
    {
      auto *op1 = (*castedOp0.getODSOperands(1).begin()).getDefiningOp();
      if (!(op1)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "There's no operation that defines operand 1 of castedOp0";
        });
      }
      if(::mlir::failed(static_dag_matcher_1(rewriter, op1, tblgen_ops, zcst))) {
        return ::mlir::failure();
      }
      tblgen_ops.push_back(op1);
    }
    if (!((
      type_isa<FIRRTLBaseType>((*x.begin()).getType()) &&
        !type_cast<FIRRTLBaseType>((*x.begin()).getType()).getRecursiveTypeProperties().hasUninferredWidth
      ))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'x' failed to satisfy constraint: ''";
      });
    }
    if (!((((*zcst.getODSResults(0).begin()).getDefiningOp<ConstantOp>() &&(*zcst.getODSResults(0).begin()).getDefiningOp<ConstantOp>().getValue().isZero())) || (((*zcst.getODSResults(0).begin()).getDefiningOp<SpecialConstantOp>() &&(*zcst.getODSResults(0).begin()).getDefiningOp<SpecialConstantOp>().getValue() == false)))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'zcst' failed to satisfy constraint: ''";
      });
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc(), tblgen_ops[1]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    auto nativeVar_0 = rewriter.getI32IntegerAttr(type_cast<FIRRTLBaseType>((*old.getODSResults(0).begin()).getType()).getBitWidthOrSentinel()); (void)nativeVar_0;
    ::circt::firrtl::PadPrimOp tblgen_PadPrimOp_1;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::circt::firrtl::PadPrimOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*x.begin()));
      tblgen_props.amount = ::llvm::dyn_cast_if_present<decltype(tblgen_props.amount)>(nativeVar_0);
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      tblgen_PadPrimOp_1 = ::circt::firrtl::PadPrimOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ tblgen_PadPrimOp_1.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    FIRRTLCanonicalization.td:350
*/
struct AndOfAllOne : public ::mlir::RewritePattern {
  AndOfAllOne(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("firrtl.and", 2, context, {"firrtl.asUInt", "firrtl.pad"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::IntegerAttr cst;
    ::circt::firrtl::ConstantOp ocst;
    ::mlir::Operation::operand_range x(op0->getOperands());
    ::circt::firrtl::AndPrimOp old;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::circt::firrtl::AndPrimOp>(op0); (void)castedOp0;
    old = castedOp0;
    x = castedOp0.getODSOperands(0);
    {
      auto *op1 = (*castedOp0.getODSOperands(1).begin()).getDefiningOp();
      if (!(op1)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "There's no operation that defines operand 1 of castedOp0";
        });
      }
      if(::mlir::failed(static_dag_matcher_2(rewriter, op1, tblgen_ops, cst, ocst))) {
        return ::mlir::failure();
      }
      tblgen_ops.push_back(op1);
    }
    if (!((
      type_isa<FIRRTLBaseType>((*x.begin()).getType()) &&
        !type_cast<FIRRTLBaseType>((*x.begin()).getType()).getRecursiveTypeProperties().hasUninferredWidth
      ))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'x' failed to satisfy constraint: ''";
      });
    }
    if (!((areAnonymousTypesEquivalent((*x.begin()).getType(), (*ocst.getODSResults(0).begin()).getType())))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'x, ocst' failed to satisfy constraint: ''";
      });
    }
    if (!(((*ocst.getODSResults(0).begin()).getDefiningOp<ConstantOp>() && (*ocst.getODSResults(0).begin()).getDefiningOp<ConstantOp>().getValue().isAllOnes()))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'ocst' failed to satisfy constraint: ''";
      });
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc(), tblgen_ops[1]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    auto nativeVar_0 = rewriter.getI32IntegerAttr(type_cast<FIRRTLBaseType>((*old.getODSResults(0).begin()).getType()).getBitWidthOrSentinel()); (void)nativeVar_0;
    ::circt::firrtl::PadPrimOp tblgen_PadPrimOp_1;
    {
      ::mlir::Value tblgen_value_0 = (*x.begin());
      tblgen_PadPrimOp_1 = ::circt::firrtl::PadPrimOp::create(rewriter, odsLoc,
        /*input=*/tblgen_value_0,
        /*amount=*/nativeVar_0
      );
    }
    ::circt::firrtl::AsUIntPrimOp tblgen_AsUIntPrimOp_2;
    {
      ::mlir::Value tblgen_value_0 = (*tblgen_PadPrimOp_1.getODSResults(0).begin());
      tblgen_AsUIntPrimOp_2 = ::circt::firrtl::AsUIntPrimOp::create(rewriter, odsLoc,
        /*input=*/tblgen_value_0
      );
    }
    auto nativeVar_3 = moveNameHint((*old.getODSResults(0).begin()), tblgen_AsUIntPrimOp_2); (void)nativeVar_3;

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ {nativeVar_3} }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    FIRRTLCanonicalization.td:369
*/
struct AndOfAsSIntL : public ::mlir::RewritePattern {
  AndOfAsSIntL(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("firrtl.and", 2, context, {"firrtl.and", "firrtl.asUInt"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range y(op0->getOperands());
    ::mlir::Operation::operand_range x(op0->getOperands());
    ::circt::firrtl::AndPrimOp old;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::circt::firrtl::AndPrimOp>(op0); (void)castedOp0;
    old = castedOp0;
    {
      auto *op1 = (*castedOp0.getODSOperands(0).begin()).getDefiningOp();
      if (!(op1)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "There's no operation that defines operand 0 of castedOp0";
        });
      }
      if(::mlir::failed(static_dag_matcher_3(rewriter, op1, tblgen_ops, x))) {
        return ::mlir::failure();
      }
      tblgen_ops.push_back(op1);
    }
    y = castedOp0.getODSOperands(1);
    if (!((type_isa<IntType>((*x.begin()).getType())))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'x' failed to satisfy constraint: ''";
      });
    }
    if (!((
      type_isa<FIRRTLBaseType>((*x.begin()).getType()) &&
        !type_cast<FIRRTLBaseType>((*x.begin()).getType()).getRecursiveTypeProperties().hasUninferredWidth
      ))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'x' failed to satisfy constraint: ''";
      });
    }
    if (!((type_cast<IntType>((*x.begin()).getType()).getWidth() == type_cast<IntType>((*y.begin()).getType()).getWidth()))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'x, y' failed to satisfy constraint: ''";
      });
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc(), tblgen_ops[1]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    ::circt::firrtl::AsUIntPrimOp tblgen_AsUIntPrimOp_0;
    {
      ::mlir::Value tblgen_value_0 = (*y.begin());
      tblgen_AsUIntPrimOp_0 = ::circt::firrtl::AsUIntPrimOp::create(rewriter, odsLoc,
        /*input=*/tblgen_value_0
      );
    }
    ::circt::firrtl::AndPrimOp tblgen_AndPrimOp_1;
    {
      ::mlir::Value tblgen_value_0 = (*x.begin());
      ::mlir::Value tblgen_value_1 = (*tblgen_AsUIntPrimOp_0.getODSResults(0).begin());
      tblgen_AndPrimOp_1 = ::circt::firrtl::AndPrimOp::create(rewriter, odsLoc,
        /*lhs=*/tblgen_value_0,
        /*rhs=*/tblgen_value_1
      );
    }
    auto nativeVar_2 = moveNameHint((*old.getODSResults(0).begin()), tblgen_AndPrimOp_1); (void)nativeVar_2;

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ {nativeVar_2} }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    FIRRTLCanonicalization.td:374
*/
struct AndOfAsSIntR : public ::mlir::RewritePattern {
  AndOfAsSIntR(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("firrtl.and", 2, context, {"firrtl.and", "firrtl.asUInt"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range y(op0->getOperands());
    ::mlir::Operation::operand_range x(op0->getOperands());
    ::circt::firrtl::AndPrimOp old;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::circt::firrtl::AndPrimOp>(op0); (void)castedOp0;
    old = castedOp0;
    x = castedOp0.getODSOperands(0);
    {
      auto *op1 = (*castedOp0.getODSOperands(1).begin()).getDefiningOp();
      if (!(op1)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "There's no operation that defines operand 1 of castedOp0";
        });
      }
      auto castedOp1 = ::llvm::dyn_cast<::circt::firrtl::AsSIntPrimOp>(op1); (void)castedOp1;
      if (!(castedOp1)){
        return rewriter.notifyMatchFailure(op1, [&](::mlir::Diagnostic &diag) {
          diag << "castedOp1 is not ::circt::firrtl::AsSIntPrimOp type";
        });
      }
      y = castedOp1.getODSOperands(0);
      tblgen_ops.push_back(op1);
    }
    if (!((type_isa<IntType>((*y.begin()).getType())))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'y' failed to satisfy constraint: ''";
      });
    }
    if (!((
      type_isa<FIRRTLBaseType>((*x.begin()).getType()) &&
        !type_cast<FIRRTLBaseType>((*x.begin()).getType()).getRecursiveTypeProperties().hasUninferredWidth
      ))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'x' failed to satisfy constraint: ''";
      });
    }
    if (!((type_cast<IntType>((*x.begin()).getType()).getWidth() == type_cast<IntType>((*y.begin()).getType()).getWidth()))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'x, y' failed to satisfy constraint: ''";
      });
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc(), tblgen_ops[1]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    ::circt::firrtl::AsUIntPrimOp tblgen_AsUIntPrimOp_0;
    {
      ::mlir::Value tblgen_value_0 = (*x.begin());
      tblgen_AsUIntPrimOp_0 = ::circt::firrtl::AsUIntPrimOp::create(rewriter, odsLoc,
        /*input=*/tblgen_value_0
      );
    }
    ::circt::firrtl::AndPrimOp tblgen_AndPrimOp_1;
    {
      ::mlir::Value tblgen_value_0 = (*tblgen_AsUIntPrimOp_0.getODSResults(0).begin());
      ::mlir::Value tblgen_value_1 = (*y.begin());
      tblgen_AndPrimOp_1 = ::circt::firrtl::AndPrimOp::create(rewriter, odsLoc,
        /*lhs=*/tblgen_value_0,
        /*rhs=*/tblgen_value_1
      );
    }
    auto nativeVar_2 = moveNameHint((*old.getODSResults(0).begin()), tblgen_AndPrimOp_1); (void)nativeVar_2;

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ {nativeVar_2} }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    FIRRTLCanonicalization.td:362
*/
struct AndOfPad : public ::mlir::RewritePattern {
  AndOfPad(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("firrtl.and", 2, context, {"firrtl.and", "firrtl.pad", "firrtl.tail"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::IntegerAttr n;
    ::mlir::Operation::operand_range y(op0->getOperands());
    ::circt::firrtl::PadPrimOp pad;
    ::mlir::Operation::operand_range x(op0->getOperands());
    ::circt::firrtl::AndPrimOp old;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::circt::firrtl::AndPrimOp>(op0); (void)castedOp0;
    old = castedOp0;
    auto eitherLambda0 = [&](::mlir::OperandRange v0, ::mlir::OperandRange v1) {
      x = v0;
      auto local_op_1 = (*v1.begin()).getDefiningOp();
      {
        if (!(local_op_1)){
          return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
            diag << "There's no operation that defines operand 1 of castedOp0";
          });
        }
        if(::mlir::failed(static_dag_matcher_4(rewriter, local_op_1, tblgen_ops, n, y, pad))) {
          return ::mlir::failure();
        }
      }
      tblgen_ops.push_back(local_op_1);
      return ::mlir::success();
    };
    {
      auto eitherOperand0 = castedOp0.getODSOperands(0);
      auto eitherOperand1 = castedOp0.getODSOperands(1);
      if(::mlir::failed(eitherLambda0(eitherOperand0, eitherOperand1)) && ::mlir::failed(eitherLambda0(eitherOperand1, eitherOperand0)))
        return ::mlir::failure();
    }
    if (!((
      type_isa<FIRRTLBaseType>((*x.begin()).getType()) &&
        !type_cast<FIRRTLBaseType>((*x.begin()).getType()).getRecursiveTypeProperties().hasUninferredWidth
      ))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'x' failed to satisfy constraint: ''";
      });
    }
    if (!((type_isa<UIntType>(((*x.begin()).getType()))))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "value entity 'x' failed to satisfy constraint: 'uint type'";
      });
    }
    if (!((areAnonymousTypesEquivalent((*x.begin()).getType(), (*pad.getODSResults(0).begin()).getType())))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'x, pad' failed to satisfy constraint: ''";
      });
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc(), tblgen_ops[1]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    auto nativeVar_0 = rewriter.getI32IntegerAttr(type_cast<FIRRTLBaseType>((*x.begin()).getType()).getBitWidthOrSentinel() - type_cast<FIRRTLBaseType>((*y.begin()).getType()).getBitWidthOrSentinel()); (void)nativeVar_0;
    ::circt::firrtl::TailPrimOp tblgen_TailPrimOp_1;
    {
      ::mlir::Value tblgen_value_0 = (*x.begin());
      tblgen_TailPrimOp_1 = ::circt::firrtl::TailPrimOp::create(rewriter, odsLoc,
        /*input=*/tblgen_value_0,
        /*amount=*/nativeVar_0
      );
    }
    ::circt::firrtl::AndPrimOp tblgen_AndPrimOp_2;
    {
      ::mlir::Value tblgen_value_0 = (*tblgen_TailPrimOp_1.getODSResults(0).begin());
      ::mlir::Value tblgen_value_1 = (*y.begin());
      tblgen_AndPrimOp_2 = ::circt::firrtl::AndPrimOp::create(rewriter, odsLoc,
        /*lhs=*/tblgen_value_0,
        /*rhs=*/tblgen_value_1
      );
    }
    ::circt::firrtl::PadPrimOp tblgen_PadPrimOp_3;
    {
      ::mlir::Value tblgen_value_0 = (*tblgen_AndPrimOp_2.getODSResults(0).begin());
      tblgen_PadPrimOp_3 = ::circt::firrtl::PadPrimOp::create(rewriter, odsLoc,
        /*input=*/tblgen_value_0,
        /*amount=*/n
      );
    }
    auto nativeVar_4 = moveNameHint((*old.getODSResults(0).begin()), tblgen_PadPrimOp_3); (void)nativeVar_4;

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ {nativeVar_4} }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    FIRRTLCanonicalization.td:356
*/
struct AndOfSelf : public ::mlir::RewritePattern {
  AndOfSelf(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("firrtl.and", 1, context, {"firrtl.asUInt"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range x(op0->getOperands());
    ::mlir::Operation::operand_range x0(op0->getOperands());
    ::circt::firrtl::AndPrimOp old;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::circt::firrtl::AndPrimOp>(op0); (void)castedOp0;
    old = castedOp0;
    x0 = castedOp0.getODSOperands(0);
    x = castedOp0.getODSOperands(1);
    if (!(*x.begin() == *x0.begin())){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "Operands 'x' and 'x0' must be equal";
      });
    }
    if (!((
      type_isa<FIRRTLBaseType>((*x.begin()).getType()) &&
        !type_cast<FIRRTLBaseType>((*x.begin()).getType()).getRecursiveTypeProperties().hasUninferredWidth
      ))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'x' failed to satisfy constraint: ''";
      });
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    ::circt::firrtl::AsUIntPrimOp tblgen_AsUIntPrimOp_0;
    {
      ::mlir::Value tblgen_value_0 = (*x.begin());
      tblgen_AsUIntPrimOp_0 = ::circt::firrtl::AsUIntPrimOp::create(rewriter, odsLoc,
        /*input=*/tblgen_value_0
      );
    }
    auto nativeVar_1 = moveNameHint((*old.getODSResults(0).begin()), tblgen_AsUIntPrimOp_0); (void)nativeVar_1;

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ {nativeVar_1} }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    FIRRTLCanonicalization.td:344
*/
struct AndOfZero : public ::mlir::RewritePattern {
  AndOfZero(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("firrtl.and", 2, context, {}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::IntegerAttr cst;
    ::circt::firrtl::ConstantOp zcst;
    ::mlir::Operation::operand_range x(op0->getOperands());
    ::circt::firrtl::AndPrimOp old;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::circt::firrtl::AndPrimOp>(op0); (void)castedOp0;
    old = castedOp0;
    x = castedOp0.getODSOperands(0);
    {
      auto *op1 = (*castedOp0.getODSOperands(1).begin()).getDefiningOp();
      if (!(op1)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "There's no operation that defines operand 1 of castedOp0";
        });
      }
      if(::mlir::failed(static_dag_matcher_5(rewriter, op1, tblgen_ops, cst, zcst))) {
        return ::mlir::failure();
      }
      tblgen_ops.push_back(op1);
    }
    if (!((
      type_isa<FIRRTLBaseType>((*x.begin()).getType()) &&
        !type_cast<FIRRTLBaseType>((*x.begin()).getType()).getRecursiveTypeProperties().hasUninferredWidth
      ))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'x' failed to satisfy constraint: ''";
      });
    }
    if (!((((*zcst.getODSResults(0).begin()).getDefiningOp<ConstantOp>() &&(*zcst.getODSResults(0).begin()).getDefiningOp<ConstantOp>().getValue().isZero())) || (((*zcst.getODSResults(0).begin()).getDefiningOp<SpecialConstantOp>() &&(*zcst.getODSResults(0).begin()).getDefiningOp<SpecialConstantOp>().getValue() == false)))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'zcst' failed to satisfy constraint: ''";
      });
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc(), tblgen_ops[1]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    auto nativeVar_0 = ConstantOp::create(rewriter, (*old.getODSResults(0).begin()).getLoc(), type_cast<IntType>((*old.getODSResults(0).begin()).getType()), getIntZerosAttr((*old.getODSResults(0).begin()).getType())); (void)nativeVar_0;

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ {nativeVar_0} }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    FIRRTLCanonicalization.td:516
*/
struct AndRCatAndR_left : public ::mlir::RewritePattern {
  AndRCatAndR_left(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("firrtl.andr", 3, context, {"firrtl.andr", "firrtl.asUInt", "firrtl.cat"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range z(op0->getOperands());
    ::mlir::Operation::operand_range y(op0->getOperands());
    ::circt::firrtl::AndRPrimOp old;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::circt::firrtl::AndRPrimOp>(op0); (void)castedOp0;
    old = castedOp0;
    {
      auto *op1 = (*castedOp0.getODSOperands(0).begin()).getDefiningOp();
      if (!(op1)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "There's no operation that defines operand 0 of castedOp0";
        });
      }
      auto castedOp1 = ::llvm::dyn_cast<::circt::firrtl::CatPrimOp>(op1); (void)castedOp1;
      if (!(castedOp1)){
        return rewriter.notifyMatchFailure(op1, [&](::mlir::Diagnostic &diag) {
          diag << "castedOp1 is not ::circt::firrtl::CatPrimOp type";
        });
      }
      {
        auto variadic_operand_range = castedOp1.getODSOperands(0);
        if (variadic_operand_range.size() != 2) return ::mlir::failure();
        y = variadic_operand_range.slice(0, 1);
        {
          auto *local_op_1 = variadic_operand_range[1].getDefiningOp();
          if (!(local_op_1)){
            return rewriter.notifyMatchFailure(castedOp1, [&](::mlir::Diagnostic &diag) {
              diag << "There's no operation that defines variadic operand 0 (variadic sub-opearnd #1) of castedOp1";
            });
          }
          if(::mlir::failed(static_dag_matcher_6(rewriter, local_op_1, tblgen_ops, z))) {
            return ::mlir::failure();
          }
          tblgen_ops.push_back(local_op_1);
        }
      }
      tblgen_ops.push_back(op1);
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc(), tblgen_ops[1]->getLoc(), tblgen_ops[2]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    ::circt::firrtl::AsUIntPrimOp tblgen_AsUIntPrimOp_1;
    {
      ::mlir::Value tblgen_value_0 = (*z.begin());
      tblgen_AsUIntPrimOp_1 = ::circt::firrtl::AsUIntPrimOp::create(rewriter, odsLoc,
        /*input=*/tblgen_value_0
      );
    }
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_variadic_values_0;
    tblgen_variadic_values_0.push_back((*y.begin()));
    tblgen_variadic_values_0.push_back(tblgen_AsUIntPrimOp_1);
    ::circt::firrtl::CatPrimOp tblgen_CatPrimOp_2;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values_0;
      for (auto v: tblgen_variadic_values_0) {
        tblgen_values_0.push_back(v);
      }
      tblgen_CatPrimOp_2 = ::circt::firrtl::CatPrimOp::create(rewriter, odsLoc,
        /*inputs=*/tblgen_values_0
      );
    }
    ::circt::firrtl::AndRPrimOp tblgen_AndRPrimOp_3;
    {
      ::mlir::Value tblgen_value_0 = (*tblgen_CatPrimOp_2.getODSResults(0).begin());
      tblgen_AndRPrimOp_3 = ::circt::firrtl::AndRPrimOp::create(rewriter, odsLoc,
        /*input=*/tblgen_value_0
      );
    }
    auto nativeVar_4 = moveNameHint((*old.getODSResults(0).begin()), tblgen_AndRPrimOp_3); (void)nativeVar_4;

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ {nativeVar_4} }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    FIRRTLCanonicalization.td:522
*/
struct AndRCatAndR_right : public ::mlir::RewritePattern {
  AndRCatAndR_right(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("firrtl.andr", 3, context, {"firrtl.andr", "firrtl.asUInt", "firrtl.cat"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range y(op0->getOperands());
    ::mlir::Operation::operand_range z(op0->getOperands());
    ::circt::firrtl::AndRPrimOp old;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::circt::firrtl::AndRPrimOp>(op0); (void)castedOp0;
    old = castedOp0;
    {
      auto *op1 = (*castedOp0.getODSOperands(0).begin()).getDefiningOp();
      if (!(op1)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "There's no operation that defines operand 0 of castedOp0";
        });
      }
      auto castedOp1 = ::llvm::dyn_cast<::circt::firrtl::CatPrimOp>(op1); (void)castedOp1;
      if (!(castedOp1)){
        return rewriter.notifyMatchFailure(op1, [&](::mlir::Diagnostic &diag) {
          diag << "castedOp1 is not ::circt::firrtl::CatPrimOp type";
        });
      }
      {
        auto variadic_operand_range = castedOp1.getODSOperands(0);
        if (variadic_operand_range.size() != 2) return ::mlir::failure();
        {
          auto *local_op_0 = variadic_operand_range[0].getDefiningOp();
          if (!(local_op_0)){
            return rewriter.notifyMatchFailure(castedOp1, [&](::mlir::Diagnostic &diag) {
              diag << "There's no operation that defines variadic operand 0 (variadic sub-opearnd #0) of castedOp1";
            });
          }
          if(::mlir::failed(static_dag_matcher_6(rewriter, local_op_0, tblgen_ops, z))) {
            return ::mlir::failure();
          }
          tblgen_ops.push_back(local_op_0);
        }
        y = variadic_operand_range.slice(1, 1);
      }
      tblgen_ops.push_back(op1);
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc(), tblgen_ops[1]->getLoc(), tblgen_ops[2]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    ::circt::firrtl::AsUIntPrimOp tblgen_AsUIntPrimOp_1;
    {
      ::mlir::Value tblgen_value_0 = (*z.begin());
      tblgen_AsUIntPrimOp_1 = ::circt::firrtl::AsUIntPrimOp::create(rewriter, odsLoc,
        /*input=*/tblgen_value_0
      );
    }
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_variadic_values_0;
    tblgen_variadic_values_0.push_back(tblgen_AsUIntPrimOp_1);
    tblgen_variadic_values_0.push_back((*y.begin()));
    ::circt::firrtl::CatPrimOp tblgen_CatPrimOp_2;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values_0;
      for (auto v: tblgen_variadic_values_0) {
        tblgen_values_0.push_back(v);
      }
      tblgen_CatPrimOp_2 = ::circt::firrtl::CatPrimOp::create(rewriter, odsLoc,
        /*inputs=*/tblgen_values_0
      );
    }
    ::circt::firrtl::AndRPrimOp tblgen_AndRPrimOp_3;
    {
      ::mlir::Value tblgen_value_0 = (*tblgen_CatPrimOp_2.getODSResults(0).begin());
      tblgen_AndRPrimOp_3 = ::circt::firrtl::AndRPrimOp::create(rewriter, odsLoc,
        /*input=*/tblgen_value_0
      );
    }
    auto nativeVar_4 = moveNameHint((*old.getODSResults(0).begin()), tblgen_AndRPrimOp_3); (void)nativeVar_4;

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ {nativeVar_4} }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    FIRRTLCanonicalization.td:510
*/
struct AndRPadS : public ::mlir::RewritePattern {
  AndRPadS(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("firrtl.andr", 2, context, {"firrtl.andr"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::IntegerAttr n;
    ::mlir::Operation::operand_range x(op0->getOperands());
    ::circt::firrtl::PadPrimOp pad;
    ::circt::firrtl::AndRPrimOp old;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    if(::mlir::failed(static_dag_matcher_8(rewriter, op0, tblgen_ops, n, x, pad, old))) {
      return ::mlir::failure();
    }
    auto castedOp0 = ::llvm::dyn_cast_or_null<::circt::firrtl::AndRPrimOp>(op0); (void)castedOp0;
    if (!((
      type_isa<FIRRTLBaseType>((*x.begin()).getType()) &&
        !type_cast<FIRRTLBaseType>((*x.begin()).getType()).getRecursiveTypeProperties().hasUninferredWidth
      ))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'x' failed to satisfy constraint: ''";
      });
    }
    if (!((type_isa<SIntType>((*x.begin()).getType())))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'x' failed to satisfy constraint: ''";
      });
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc(), tblgen_ops[1]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    ::circt::firrtl::AndRPrimOp tblgen_AndRPrimOp_0;
    {
      ::mlir::Value tblgen_value_0 = (*x.begin());
      tblgen_AndRPrimOp_0 = ::circt::firrtl::AndRPrimOp::create(rewriter, odsLoc,
        /*input=*/tblgen_value_0
      );
    }
    auto nativeVar_1 = moveNameHint((*old.getODSResults(0).begin()), tblgen_AndRPrimOp_0); (void)nativeVar_1;

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ {nativeVar_1} }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    FIRRTLCanonicalization.td:504
*/
struct AndRPadU : public ::mlir::RewritePattern {
  AndRPadU(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("firrtl.andr", 2, context, {}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::IntegerAttr n;
    ::mlir::Operation::operand_range x(op0->getOperands());
    ::circt::firrtl::PadPrimOp pad;
    ::circt::firrtl::AndRPrimOp old;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    if(::mlir::failed(static_dag_matcher_8(rewriter, op0, tblgen_ops, n, x, pad, old))) {
      return ::mlir::failure();
    }
    auto castedOp0 = ::llvm::dyn_cast_or_null<::circt::firrtl::AndRPrimOp>(op0); (void)castedOp0;
    if (!((
      type_isa<FIRRTLBaseType>((*x.begin()).getType()) &&
        !type_cast<FIRRTLBaseType>((*x.begin()).getType()).getRecursiveTypeProperties().hasUninferredWidth
      ))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'x' failed to satisfy constraint: ''";
      });
    }
    if (!((type_isa<UIntType>((*x.begin()).getType())))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'x' failed to satisfy constraint: ''";
      });
    }
    if (!((type_cast<IntType>((*pad.getODSResults(0).begin()).getType()).getBitWidthOrSentinel() > type_cast<IntType>((*x.begin()).getType()).getBitWidthOrSentinel()))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'pad, x' failed to satisfy constraint: ''";
      });
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc(), tblgen_ops[1]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    auto nativeVar_0 = ConstantOp::create(rewriter, (*old.getODSResults(0).begin()).getLoc(), type_cast<IntType>((*old.getODSResults(0).begin()).getType()), getIntZerosAttr((*old.getODSResults(0).begin()).getType())); (void)nativeVar_0;

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ {nativeVar_0} }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    FIRRTLCanonicalization.td:492
*/
struct AndRasSInt : public ::mlir::RewritePattern {
  AndRasSInt(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("firrtl.andr", 2, context, {"firrtl.andr"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range x(op0->getOperands());
    ::circt::firrtl::AndRPrimOp old;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::circt::firrtl::AndRPrimOp>(op0); (void)castedOp0;
    old = castedOp0;
    {
      auto *op1 = (*castedOp0.getODSOperands(0).begin()).getDefiningOp();
      if (!(op1)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "There's no operation that defines operand 0 of castedOp0";
        });
      }
      if(::mlir::failed(static_dag_matcher_3(rewriter, op1, tblgen_ops, x))) {
        return ::mlir::failure();
      }
      tblgen_ops.push_back(op1);
    }
    if (!((
      type_isa<FIRRTLBaseType>((*x.begin()).getType()) &&
        !type_cast<FIRRTLBaseType>((*x.begin()).getType()).getRecursiveTypeProperties().hasUninferredWidth
      ))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'x' failed to satisfy constraint: ''";
      });
    }
    if (!((type_isa<IntType>((*x.begin()).getType())))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'x' failed to satisfy constraint: ''";
      });
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc(), tblgen_ops[1]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    ::circt::firrtl::AndRPrimOp tblgen_AndRPrimOp_0;
    {
      ::mlir::Value tblgen_value_0 = (*x.begin());
      tblgen_AndRPrimOp_0 = ::circt::firrtl::AndRPrimOp::create(rewriter, odsLoc,
        /*input=*/tblgen_value_0
      );
    }
    auto nativeVar_1 = moveNameHint((*old.getODSResults(0).begin()), tblgen_AndRPrimOp_0); (void)nativeVar_1;

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ {nativeVar_1} }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    FIRRTLCanonicalization.td:498
*/
struct AndRasUInt : public ::mlir::RewritePattern {
  AndRasUInt(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("firrtl.andr", 2, context, {"firrtl.andr"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range x(op0->getOperands());
    ::circt::firrtl::AndRPrimOp old;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::circt::firrtl::AndRPrimOp>(op0); (void)castedOp0;
    old = castedOp0;
    {
      auto *op1 = (*castedOp0.getODSOperands(0).begin()).getDefiningOp();
      if (!(op1)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "There's no operation that defines operand 0 of castedOp0";
        });
      }
      if(::mlir::failed(static_dag_matcher_9(rewriter, op1, tblgen_ops, x))) {
        return ::mlir::failure();
      }
      tblgen_ops.push_back(op1);
    }
    if (!((
      type_isa<FIRRTLBaseType>((*x.begin()).getType()) &&
        !type_cast<FIRRTLBaseType>((*x.begin()).getType()).getRecursiveTypeProperties().hasUninferredWidth
      ))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'x' failed to satisfy constraint: ''";
      });
    }
    if (!((type_isa<IntType>((*x.begin()).getType())))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'x' failed to satisfy constraint: ''";
      });
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc(), tblgen_ops[1]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    ::circt::firrtl::AndRPrimOp tblgen_AndRPrimOp_0;
    {
      ::mlir::Value tblgen_value_0 = (*x.begin());
      tblgen_AndRPrimOp_0 = ::circt::firrtl::AndRPrimOp::create(rewriter, odsLoc,
        /*input=*/tblgen_value_0
      );
    }
    auto nativeVar_1 = moveNameHint((*old.getODSResults(0).begin()), tblgen_AndRPrimOp_0); (void)nativeVar_1;

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ {nativeVar_1} }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    FIRRTLCanonicalization.td:699
*/
struct AssertXWhenX : public ::mlir::RewritePattern {
  AssertXWhenX(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("firrtl.assert", 1, context, {}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range x(op0->getOperands());
    ::mlir::Operation::operand_range x0(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::circt::firrtl::AssertOp>(op0); (void)castedOp0;
    x0 = castedOp0.getODSOperands(1);
    x = castedOp0.getODSOperands(2);
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getMessage();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'firrtl.assert' to have attribute 'message' of type '::mlir::StringAttr'";
        });
      }
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getName();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'firrtl.assert' to have attribute 'name' of type '::mlir::StringAttr'";
        });
      }
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getIsConcurrent();
      if (!tblgen_attr) tblgen_attr = rewriter.getBoolAttr(false);
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getEventControl();
      if (!tblgen_attr) tblgen_attr = ::circt::firrtl::EventControlAttr::get(rewriter.getContext(), EventControl::AtPosEdge);
    }
    if (!(*x.begin() == *x0.begin())){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "Operands 'x' and 'x0' must be equal";
      });
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    rewriter.eraseOp(op0);
    return ::mlir::success();
  }
};

/* Generated from:
    FIRRTLCanonicalization.td:701
*/
struct AssumeXWhenX : public ::mlir::RewritePattern {
  AssumeXWhenX(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("firrtl.assume", 1, context, {}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range x(op0->getOperands());
    ::mlir::Operation::operand_range x0(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::circt::firrtl::AssumeOp>(op0); (void)castedOp0;
    x0 = castedOp0.getODSOperands(1);
    x = castedOp0.getODSOperands(2);
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getMessage();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'firrtl.assume' to have attribute 'message' of type '::mlir::StringAttr'";
        });
      }
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getName();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'firrtl.assume' to have attribute 'name' of type '::mlir::StringAttr'";
        });
      }
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getIsConcurrent();
      if (!tblgen_attr) tblgen_attr = rewriter.getBoolAttr(false);
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getEventControl();
      if (!tblgen_attr) tblgen_attr = ::circt::firrtl::EventControlAttr::get(rewriter.getContext(), EventControl::AtPosEdge);
    }
    if (!(*x.begin() == *x0.begin())){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "Operands 'x' and 'x0' must be equal";
      });
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    rewriter.eraseOp(op0);
    return ::mlir::success();
  }
};

/* Generated from:
    FIRRTLCanonicalization.td:549
*/
struct BitsOfAnd : public ::mlir::RewritePattern {
  BitsOfAnd(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("firrtl.bits", 2, context, {"firrtl.and", "firrtl.bits"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::IntegerAttr oLow;
    ::mlir::IntegerAttr oHigh;
    ::mlir::Operation::operand_range y(op0->getOperands());
    ::mlir::Operation::operand_range x(op0->getOperands());
    ::circt::firrtl::BitsPrimOp old;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::circt::firrtl::BitsPrimOp>(op0); (void)castedOp0;
    old = castedOp0;
    {
      auto *op1 = (*castedOp0.getODSOperands(0).begin()).getDefiningOp();
      if (!(op1)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "There's no operation that defines operand 0 of castedOp0";
        });
      }
      auto castedOp1 = ::llvm::dyn_cast<::circt::firrtl::AndPrimOp>(op1); (void)castedOp1;
      if (!(castedOp1)){
        return rewriter.notifyMatchFailure(op1, [&](::mlir::Diagnostic &diag) {
          diag << "castedOp1 is not ::circt::firrtl::AndPrimOp type";
        });
      }
      x = castedOp1.getODSOperands(0);
      y = castedOp1.getODSOperands(1);
      tblgen_ops.push_back(op1);
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getHi();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'firrtl.bits' to have attribute 'hi' of type '::mlir::IntegerAttr'";
        });
      }
      if(::mlir::failed(__mlir_ods_local_attr_constraint_FIRRTLCanonicalization1(rewriter, castedOp0, tblgen_attr, "op 'firrtl.bits' attribute 'hi' failed to satisfy constraint: '32-bit signless integer attribute'"))) {
        return ::mlir::failure();
      }
      oHigh = tblgen_attr;
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getLo();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'firrtl.bits' to have attribute 'lo' of type '::mlir::IntegerAttr'";
        });
      }
      if(::mlir::failed(__mlir_ods_local_attr_constraint_FIRRTLCanonicalization1(rewriter, castedOp0, tblgen_attr, "op 'firrtl.bits' attribute 'lo' failed to satisfy constraint: '32-bit signless integer attribute'"))) {
        return ::mlir::failure();
      }
      oLow = tblgen_attr;
    }
    if (!((
      type_isa<FIRRTLBaseType>((*x.begin()).getType()) &&
        !type_cast<FIRRTLBaseType>((*x.begin()).getType()).getRecursiveTypeProperties().hasUninferredWidth
      ))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'x' failed to satisfy constraint: ''";
      });
    }
    if (!((areAnonymousTypesEquivalent((*x.begin()).getType(), (*y.begin()).getType())))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'x, y' failed to satisfy constraint: ''";
      });
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc(), tblgen_ops[1]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    ::circt::firrtl::BitsPrimOp tblgen_BitsPrimOp_0;
    {
      ::mlir::Value tblgen_value_0 = (*x.begin());
      tblgen_BitsPrimOp_0 = ::circt::firrtl::BitsPrimOp::create(rewriter, odsLoc,
        /*input=*/tblgen_value_0,
        /*hi=*/oHigh,
        /*lo=*/oLow
      );
    }
    ::circt::firrtl::BitsPrimOp tblgen_BitsPrimOp_1;
    {
      ::mlir::Value tblgen_value_0 = (*y.begin());
      tblgen_BitsPrimOp_1 = ::circt::firrtl::BitsPrimOp::create(rewriter, odsLoc,
        /*input=*/tblgen_value_0,
        /*hi=*/oHigh,
        /*lo=*/oLow
      );
    }
    ::circt::firrtl::AndPrimOp tblgen_AndPrimOp_2;
    {
      ::mlir::Value tblgen_value_0 = (*tblgen_BitsPrimOp_0.getODSResults(0).begin());
      ::mlir::Value tblgen_value_1 = (*tblgen_BitsPrimOp_1.getODSResults(0).begin());
      tblgen_AndPrimOp_2 = ::circt::firrtl::AndPrimOp::create(rewriter, odsLoc,
        /*lhs=*/tblgen_value_0,
        /*rhs=*/tblgen_value_1
      );
    }
    auto nativeVar_3 = moveNameHint((*old.getODSResults(0).begin()), tblgen_AndPrimOp_2); (void)nativeVar_3;

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ {nativeVar_3} }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    FIRRTLCanonicalization.td:543
*/
struct BitsOfAsUInt : public ::mlir::RewritePattern {
  BitsOfAsUInt(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("firrtl.bits", 2, context, {"firrtl.bits"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::IntegerAttr oLow;
    ::mlir::IntegerAttr oHigh;
    ::mlir::Operation::operand_range x(op0->getOperands());
    ::circt::firrtl::BitsPrimOp old;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::circt::firrtl::BitsPrimOp>(op0); (void)castedOp0;
    old = castedOp0;
    {
      auto *op1 = (*castedOp0.getODSOperands(0).begin()).getDefiningOp();
      if (!(op1)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "There's no operation that defines operand 0 of castedOp0";
        });
      }
      if(::mlir::failed(static_dag_matcher_9(rewriter, op1, tblgen_ops, x))) {
        return ::mlir::failure();
      }
      tblgen_ops.push_back(op1);
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getHi();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'firrtl.bits' to have attribute 'hi' of type '::mlir::IntegerAttr'";
        });
      }
      if(::mlir::failed(__mlir_ods_local_attr_constraint_FIRRTLCanonicalization1(rewriter, castedOp0, tblgen_attr, "op 'firrtl.bits' attribute 'hi' failed to satisfy constraint: '32-bit signless integer attribute'"))) {
        return ::mlir::failure();
      }
      oHigh = tblgen_attr;
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getLo();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'firrtl.bits' to have attribute 'lo' of type '::mlir::IntegerAttr'";
        });
      }
      if(::mlir::failed(__mlir_ods_local_attr_constraint_FIRRTLCanonicalization1(rewriter, castedOp0, tblgen_attr, "op 'firrtl.bits' attribute 'lo' failed to satisfy constraint: '32-bit signless integer attribute'"))) {
        return ::mlir::failure();
      }
      oLow = tblgen_attr;
    }
    if (!((
      type_isa<FIRRTLBaseType>((*x.begin()).getType()) &&
        !type_cast<FIRRTLBaseType>((*x.begin()).getType()).getRecursiveTypeProperties().hasUninferredWidth
      ))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'x' failed to satisfy constraint: ''";
      });
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc(), tblgen_ops[1]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    ::circt::firrtl::BitsPrimOp tblgen_BitsPrimOp_0;
    {
      ::mlir::Value tblgen_value_0 = (*x.begin());
      tblgen_BitsPrimOp_0 = ::circt::firrtl::BitsPrimOp::create(rewriter, odsLoc,
        /*input=*/tblgen_value_0,
        /*hi=*/oHigh,
        /*lo=*/oLow
      );
    }
    auto nativeVar_1 = moveNameHint((*old.getODSResults(0).begin()), tblgen_BitsPrimOp_0); (void)nativeVar_1;

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ {nativeVar_1} }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    FIRRTLCanonicalization.td:528
*/
struct BitsOfBits : public ::mlir::RewritePattern {
  BitsOfBits(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("firrtl.bits", 2, context, {"firrtl.bits"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::IntegerAttr oLow;
    ::mlir::IntegerAttr oHigh;
    ::mlir::IntegerAttr iLow;
    ::mlir::IntegerAttr iHigh;
    ::mlir::Operation::operand_range x(op0->getOperands());
    ::circt::firrtl::BitsPrimOp old;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::circt::firrtl::BitsPrimOp>(op0); (void)castedOp0;
    old = castedOp0;
    {
      auto *op1 = (*castedOp0.getODSOperands(0).begin()).getDefiningOp();
      if (!(op1)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "There's no operation that defines operand 0 of castedOp0";
        });
      }
      auto castedOp1 = ::llvm::dyn_cast<::circt::firrtl::BitsPrimOp>(op1); (void)castedOp1;
      if (!(castedOp1)){
        return rewriter.notifyMatchFailure(op1, [&](::mlir::Diagnostic &diag) {
          diag << "castedOp1 is not ::circt::firrtl::BitsPrimOp type";
        });
      }
      x = castedOp1.getODSOperands(0);
      {
        [[maybe_unused]] auto tblgen_attr = castedOp1.getProperties().getHi();
        if (!(tblgen_attr)){
          return rewriter.notifyMatchFailure(castedOp1, [&](::mlir::Diagnostic &diag) {
            diag << "expected op 'firrtl.bits' to have attribute 'hi' of type '::mlir::IntegerAttr'";
          });
        }
        if(::mlir::failed(__mlir_ods_local_attr_constraint_FIRRTLCanonicalization1(rewriter, castedOp1, tblgen_attr, "op 'firrtl.bits' attribute 'hi' failed to satisfy constraint: '32-bit signless integer attribute'"))) {
          return ::mlir::failure();
        }
        iHigh = tblgen_attr;
      }
      {
        [[maybe_unused]] auto tblgen_attr = castedOp1.getProperties().getLo();
        if (!(tblgen_attr)){
          return rewriter.notifyMatchFailure(castedOp1, [&](::mlir::Diagnostic &diag) {
            diag << "expected op 'firrtl.bits' to have attribute 'lo' of type '::mlir::IntegerAttr'";
          });
        }
        if(::mlir::failed(__mlir_ods_local_attr_constraint_FIRRTLCanonicalization1(rewriter, castedOp1, tblgen_attr, "op 'firrtl.bits' attribute 'lo' failed to satisfy constraint: '32-bit signless integer attribute'"))) {
          return ::mlir::failure();
        }
        iLow = tblgen_attr;
      }
      tblgen_ops.push_back(op1);
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getHi();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'firrtl.bits' to have attribute 'hi' of type '::mlir::IntegerAttr'";
        });
      }
      if(::mlir::failed(__mlir_ods_local_attr_constraint_FIRRTLCanonicalization1(rewriter, castedOp0, tblgen_attr, "op 'firrtl.bits' attribute 'hi' failed to satisfy constraint: '32-bit signless integer attribute'"))) {
        return ::mlir::failure();
      }
      oHigh = tblgen_attr;
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getLo();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'firrtl.bits' to have attribute 'lo' of type '::mlir::IntegerAttr'";
        });
      }
      if(::mlir::failed(__mlir_ods_local_attr_constraint_FIRRTLCanonicalization1(rewriter, castedOp0, tblgen_attr, "op 'firrtl.bits' attribute 'lo' failed to satisfy constraint: '32-bit signless integer attribute'"))) {
        return ::mlir::failure();
      }
      oLow = tblgen_attr;
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc(), tblgen_ops[1]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    auto nativeVar_0 = rewriter.getI32IntegerAttr(iLow.getValue().getZExtValue() + oHigh.getValue().getZExtValue()); (void)nativeVar_0;
    auto nativeVar_1 = rewriter.getI32IntegerAttr(oLow.getValue().getZExtValue() + iLow.getValue().getZExtValue()); (void)nativeVar_1;
    ::circt::firrtl::BitsPrimOp tblgen_BitsPrimOp_2;
    {
      ::mlir::Value tblgen_value_0 = (*x.begin());
      tblgen_BitsPrimOp_2 = ::circt::firrtl::BitsPrimOp::create(rewriter, odsLoc,
        /*input=*/tblgen_value_0,
        /*hi=*/nativeVar_0,
        /*lo=*/nativeVar_1
      );
    }
    auto nativeVar_3 = moveNameHint((*old.getODSResults(0).begin()), tblgen_BitsPrimOp_2); (void)nativeVar_3;

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ {nativeVar_3} }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    FIRRTLCanonicalization.td:537
*/
struct BitsOfMux : public ::mlir::RewritePattern {
  BitsOfMux(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("firrtl.bits", 2, context, {"firrtl.bits", "firrtl.mux"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::IntegerAttr oLow;
    ::mlir::Operation::operand_range y(op0->getOperands());
    ::mlir::Operation::operand_range x(op0->getOperands());
    ::mlir::IntegerAttr oHigh;
    ::mlir::Operation::operand_range c(op0->getOperands());
    ::circt::firrtl::BitsPrimOp old;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::circt::firrtl::BitsPrimOp>(op0); (void)castedOp0;
    old = castedOp0;
    {
      auto *op1 = (*castedOp0.getODSOperands(0).begin()).getDefiningOp();
      if (!(op1)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "There's no operation that defines operand 0 of castedOp0";
        });
      }
      auto castedOp1 = ::llvm::dyn_cast<::circt::firrtl::MuxPrimOp>(op1); (void)castedOp1;
      if (!(castedOp1)){
        return rewriter.notifyMatchFailure(op1, [&](::mlir::Diagnostic &diag) {
          diag << "castedOp1 is not ::circt::firrtl::MuxPrimOp type";
        });
      }
      c = castedOp1.getODSOperands(0);
      x = castedOp1.getODSOperands(1);
      y = castedOp1.getODSOperands(2);
      tblgen_ops.push_back(op1);
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getHi();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'firrtl.bits' to have attribute 'hi' of type '::mlir::IntegerAttr'";
        });
      }
      if(::mlir::failed(__mlir_ods_local_attr_constraint_FIRRTLCanonicalization1(rewriter, castedOp0, tblgen_attr, "op 'firrtl.bits' attribute 'hi' failed to satisfy constraint: '32-bit signless integer attribute'"))) {
        return ::mlir::failure();
      }
      oHigh = tblgen_attr;
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getLo();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'firrtl.bits' to have attribute 'lo' of type '::mlir::IntegerAttr'";
        });
      }
      if(::mlir::failed(__mlir_ods_local_attr_constraint_FIRRTLCanonicalization1(rewriter, castedOp0, tblgen_attr, "op 'firrtl.bits' attribute 'lo' failed to satisfy constraint: '32-bit signless integer attribute'"))) {
        return ::mlir::failure();
      }
      oLow = tblgen_attr;
    }
    if (!((
      isa_and_nonnull<ConstantOp, SpecialConstantOp, AggregateConstantOp>
        ((*x.begin()).getDefiningOp())
      ))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'x' failed to satisfy constraint: ''";
      });
    }
    if (!((
      isa_and_nonnull<ConstantOp, SpecialConstantOp, AggregateConstantOp>
        ((*y.begin()).getDefiningOp())
      ))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'y' failed to satisfy constraint: ''";
      });
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc(), tblgen_ops[1]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    ::circt::firrtl::BitsPrimOp tblgen_BitsPrimOp_0;
    {
      ::mlir::Value tblgen_value_0 = (*x.begin());
      tblgen_BitsPrimOp_0 = ::circt::firrtl::BitsPrimOp::create(rewriter, odsLoc,
        /*input=*/tblgen_value_0,
        /*hi=*/oHigh,
        /*lo=*/oLow
      );
    }
    ::circt::firrtl::BitsPrimOp tblgen_BitsPrimOp_1;
    {
      ::mlir::Value tblgen_value_0 = (*y.begin());
      tblgen_BitsPrimOp_1 = ::circt::firrtl::BitsPrimOp::create(rewriter, odsLoc,
        /*input=*/tblgen_value_0,
        /*hi=*/oHigh,
        /*lo=*/oLow
      );
    }
    ::circt::firrtl::MuxPrimOp tblgen_MuxPrimOp_2;
    {
      ::mlir::Value tblgen_value_0 = (*c.begin());
      ::mlir::Value tblgen_value_1 = (*tblgen_BitsPrimOp_0.getODSResults(0).begin());
      ::mlir::Value tblgen_value_2 = (*tblgen_BitsPrimOp_1.getODSResults(0).begin());
      tblgen_MuxPrimOp_2 = ::circt::firrtl::MuxPrimOp::create(rewriter, odsLoc,
        /*sel=*/tblgen_value_0,
        /*high=*/tblgen_value_1,
        /*low=*/tblgen_value_2
      );
    }
    auto nativeVar_3 = moveNameHint((*old.getODSResults(0).begin()), tblgen_MuxPrimOp_2); (void)nativeVar_3;

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ {nativeVar_3} }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    FIRRTLCanonicalization.td:556
*/
struct BitsOfPad : public ::mlir::RewritePattern {
  BitsOfPad(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("firrtl.bits", 2, context, {"firrtl.asUInt"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::IntegerAttr oLow;
    ::mlir::IntegerAttr oHigh;
    ::mlir::IntegerAttr n;
    ::mlir::Operation::operand_range x(op0->getOperands());
    ::circt::firrtl::BitsPrimOp old;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::circt::firrtl::BitsPrimOp>(op0); (void)castedOp0;
    old = castedOp0;
    {
      auto *op1 = (*castedOp0.getODSOperands(0).begin()).getDefiningOp();
      if (!(op1)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "There's no operation that defines operand 0 of castedOp0";
        });
      }
      auto castedOp1 = ::llvm::dyn_cast<::circt::firrtl::PadPrimOp>(op1); (void)castedOp1;
      if (!(castedOp1)){
        return rewriter.notifyMatchFailure(op1, [&](::mlir::Diagnostic &diag) {
          diag << "castedOp1 is not ::circt::firrtl::PadPrimOp type";
        });
      }
      x = castedOp1.getODSOperands(0);
      {
        [[maybe_unused]] auto tblgen_attr = castedOp1.getProperties().getAmount();
        if (!(tblgen_attr)){
          return rewriter.notifyMatchFailure(castedOp1, [&](::mlir::Diagnostic &diag) {
            diag << "expected op 'firrtl.pad' to have attribute 'amount' of type '::mlir::IntegerAttr'";
          });
        }
        if(::mlir::failed(__mlir_ods_local_attr_constraint_FIRRTLCanonicalization1(rewriter, castedOp1, tblgen_attr, "op 'firrtl.pad' attribute 'amount' failed to satisfy constraint: '32-bit signless integer attribute'"))) {
          return ::mlir::failure();
        }
        n = tblgen_attr;
      }
      tblgen_ops.push_back(op1);
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getHi();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'firrtl.bits' to have attribute 'hi' of type '::mlir::IntegerAttr'";
        });
      }
      if(::mlir::failed(__mlir_ods_local_attr_constraint_FIRRTLCanonicalization1(rewriter, castedOp0, tblgen_attr, "op 'firrtl.bits' attribute 'hi' failed to satisfy constraint: '32-bit signless integer attribute'"))) {
        return ::mlir::failure();
      }
      oHigh = tblgen_attr;
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getLo();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'firrtl.bits' to have attribute 'lo' of type '::mlir::IntegerAttr'";
        });
      }
      if(::mlir::failed(__mlir_ods_local_attr_constraint_FIRRTLCanonicalization1(rewriter, castedOp0, tblgen_attr, "op 'firrtl.bits' attribute 'lo' failed to satisfy constraint: '32-bit signless integer attribute'"))) {
        return ::mlir::failure();
      }
      oLow = tblgen_attr;
    }
    if (!((
      type_isa<FIRRTLBaseType>((*x.begin()).getType()) &&
        !type_cast<FIRRTLBaseType>((*x.begin()).getType()).getRecursiveTypeProperties().hasUninferredWidth
      ))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'x' failed to satisfy constraint: ''";
      });
    }
    if (!((type_cast<IntType>((*old.getODSResults(0).begin()).getType()).getWidth() == type_cast<IntType>((*x.begin()).getType()).getWidth()))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'old, x' failed to satisfy constraint: ''";
      });
    }
    if (!((oLow.getValue().isZero()))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'oLow' failed to satisfy constraint: ''";
      });
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc(), tblgen_ops[1]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    ::circt::firrtl::AsUIntPrimOp tblgen_AsUIntPrimOp_0;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::circt::firrtl::AsUIntPrimOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*x.begin()));
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      tblgen_AsUIntPrimOp_0 = ::circt::firrtl::AsUIntPrimOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ tblgen_AsUIntPrimOp_0.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    FIRRTLCanonicalization.td:686
*/
struct CVTSigned : public ::mlir::RewritePattern {
  CVTSigned(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("firrtl.cvt", 1, context, {}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range x(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::circt::firrtl::CvtPrimOp>(op0); (void)castedOp0;
    x = castedOp0.getODSOperands(0);
    if (!((type_isa<SIntType>(((*x.begin()).getType()))))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "value entity 'x' failed to satisfy constraint: 'sint type'";
      });
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ x }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    FIRRTLCanonicalization.td:691
*/
struct CVTUnSigned : public ::mlir::RewritePattern {
  CVTUnSigned(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("firrtl.cvt", 1, context, {"firrtl.asSInt", "firrtl.pad"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range x(op0->getOperands());
    ::circt::firrtl::CvtPrimOp old;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::circt::firrtl::CvtPrimOp>(op0); (void)castedOp0;
    old = castedOp0;
    x = castedOp0.getODSOperands(0);
    if (!((type_isa<UIntType>(((*x.begin()).getType()))))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "value entity 'x' failed to satisfy constraint: 'uint type'";
      });
    }
    if (!((
      type_isa<FIRRTLBaseType>((*old.getODSResults(0).begin()).getType()) &&
        !type_cast<FIRRTLBaseType>((*old.getODSResults(0).begin()).getType()).getRecursiveTypeProperties().hasUninferredWidth
      ))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'old' failed to satisfy constraint: ''";
      });
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    auto nativeVar_0 = rewriter.getI32IntegerAttr(type_cast<SIntType>((*old.getODSResults(0).begin()).getType()).getBitWidthOrSentinel()); (void)nativeVar_0;
    ::circt::firrtl::PadPrimOp tblgen_PadPrimOp_1;
    {
      ::mlir::Value tblgen_value_0 = (*x.begin());
      tblgen_PadPrimOp_1 = ::circt::firrtl::PadPrimOp::create(rewriter, odsLoc,
        /*input=*/tblgen_value_0,
        /*amount=*/nativeVar_0
      );
    }
    ::circt::firrtl::AsSIntPrimOp tblgen_AsSIntPrimOp_2;
    {
      ::mlir::Value tblgen_value_0 = (*tblgen_PadPrimOp_1.getODSResults(0).begin());
      tblgen_AsSIntPrimOp_2 = ::circt::firrtl::AsSIntPrimOp::create(rewriter, odsLoc,
        /*input=*/tblgen_value_0
      );
    }
    auto nativeVar_3 = moveNameHint((*old.getODSResults(0).begin()), tblgen_AsSIntPrimOp_2); (void)nativeVar_3;

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ {nativeVar_3} }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    FIRRTLCanonicalization.td:660
*/
struct CatBitsBits : public ::mlir::RewritePattern {
  CatBitsBits(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("firrtl.cat", 3, context, {"firrtl.bits"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::IntegerAttr low;
    ::mlir::IntegerAttr mid2;
    ::mlir::IntegerAttr mid;
    ::mlir::IntegerAttr hi;
    ::mlir::Operation::operand_range x(op0->getOperands());
    ::mlir::Operation::operand_range x0(op0->getOperands());
    ::circt::firrtl::CatPrimOp old;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::circt::firrtl::CatPrimOp>(op0); (void)castedOp0;
    old = castedOp0;
    {
      auto variadic_operand_range = castedOp0.getODSOperands(0);
      if (variadic_operand_range.size() != 2) return ::mlir::failure();
      {
        auto *local_op_0 = variadic_operand_range[0].getDefiningOp();
        if (!(local_op_0)){
          return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
            diag << "There's no operation that defines variadic operand 0 (variadic sub-opearnd #0) of castedOp0";
          });
        }
        auto castedOp1 = ::llvm::dyn_cast<::circt::firrtl::BitsPrimOp>(local_op_0); (void)castedOp1;
        if (!(castedOp1)){
          return rewriter.notifyMatchFailure(local_op_0, [&](::mlir::Diagnostic &diag) {
            diag << "castedOp1 is not ::circt::firrtl::BitsPrimOp type";
          });
        }
        x0 = castedOp1.getODSOperands(0);
        {
          [[maybe_unused]] auto tblgen_attr = castedOp1.getProperties().getHi();
          if (!(tblgen_attr)){
            return rewriter.notifyMatchFailure(castedOp1, [&](::mlir::Diagnostic &diag) {
              diag << "expected op 'firrtl.bits' to have attribute 'hi' of type '::mlir::IntegerAttr'";
            });
          }
          if(::mlir::failed(__mlir_ods_local_attr_constraint_FIRRTLCanonicalization1(rewriter, castedOp1, tblgen_attr, "op 'firrtl.bits' attribute 'hi' failed to satisfy constraint: '32-bit signless integer attribute'"))) {
            return ::mlir::failure();
          }
          hi = tblgen_attr;
        }
        {
          [[maybe_unused]] auto tblgen_attr = castedOp1.getProperties().getLo();
          if (!(tblgen_attr)){
            return rewriter.notifyMatchFailure(castedOp1, [&](::mlir::Diagnostic &diag) {
              diag << "expected op 'firrtl.bits' to have attribute 'lo' of type '::mlir::IntegerAttr'";
            });
          }
          if(::mlir::failed(__mlir_ods_local_attr_constraint_FIRRTLCanonicalization1(rewriter, castedOp1, tblgen_attr, "op 'firrtl.bits' attribute 'lo' failed to satisfy constraint: '32-bit signless integer attribute'"))) {
            return ::mlir::failure();
          }
          mid = tblgen_attr;
        }
        tblgen_ops.push_back(local_op_0);
      }
      {
        auto *local_op_1 = variadic_operand_range[1].getDefiningOp();
        if (!(local_op_1)){
          return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
            diag << "There's no operation that defines variadic operand 0 (variadic sub-opearnd #1) of castedOp0";
          });
        }
        auto castedOp1 = ::llvm::dyn_cast<::circt::firrtl::BitsPrimOp>(local_op_1); (void)castedOp1;
        if (!(castedOp1)){
          return rewriter.notifyMatchFailure(local_op_1, [&](::mlir::Diagnostic &diag) {
            diag << "castedOp1 is not ::circt::firrtl::BitsPrimOp type";
          });
        }
        x = castedOp1.getODSOperands(0);
        {
          [[maybe_unused]] auto tblgen_attr = castedOp1.getProperties().getHi();
          if (!(tblgen_attr)){
            return rewriter.notifyMatchFailure(castedOp1, [&](::mlir::Diagnostic &diag) {
              diag << "expected op 'firrtl.bits' to have attribute 'hi' of type '::mlir::IntegerAttr'";
            });
          }
          if(::mlir::failed(__mlir_ods_local_attr_constraint_FIRRTLCanonicalization1(rewriter, castedOp1, tblgen_attr, "op 'firrtl.bits' attribute 'hi' failed to satisfy constraint: '32-bit signless integer attribute'"))) {
            return ::mlir::failure();
          }
          mid2 = tblgen_attr;
        }
        {
          [[maybe_unused]] auto tblgen_attr = castedOp1.getProperties().getLo();
          if (!(tblgen_attr)){
            return rewriter.notifyMatchFailure(castedOp1, [&](::mlir::Diagnostic &diag) {
              diag << "expected op 'firrtl.bits' to have attribute 'lo' of type '::mlir::IntegerAttr'";
            });
          }
          if(::mlir::failed(__mlir_ods_local_attr_constraint_FIRRTLCanonicalization1(rewriter, castedOp1, tblgen_attr, "op 'firrtl.bits' attribute 'lo' failed to satisfy constraint: '32-bit signless integer attribute'"))) {
            return ::mlir::failure();
          }
          low = tblgen_attr;
        }
        tblgen_ops.push_back(local_op_1);
      }
    }
    if (!(*x.begin() == *x0.begin())){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "Operands 'x' and 'x0' must be equal";
      });
    }
    if (!((mid2.getValue() + 1 == mid.getValue()))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'mid2, mid' failed to satisfy constraint: ''";
      });
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc(), tblgen_ops[1]->getLoc(), tblgen_ops[2]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    ::circt::firrtl::BitsPrimOp tblgen_BitsPrimOp_0;
    {
      ::mlir::Value tblgen_value_0 = (*x.begin());
      tblgen_BitsPrimOp_0 = ::circt::firrtl::BitsPrimOp::create(rewriter, odsLoc,
        /*input=*/tblgen_value_0,
        /*hi=*/hi,
        /*lo=*/low
      );
    }
    auto nativeVar_1 = moveNameHint((*old.getODSResults(0).begin()), tblgen_BitsPrimOp_0); (void)nativeVar_1;

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ {nativeVar_1} }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    FIRRTLCanonicalization.td:654
*/
struct CatCast : public ::mlir::RewritePattern {
  CatCast(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("firrtl.cat", 3, context, {"firrtl.cat"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range y(op0->getOperands());
    ::mlir::Operation::operand_range x(op0->getOperands());
    ::circt::firrtl::CatPrimOp old;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::circt::firrtl::CatPrimOp>(op0); (void)castedOp0;
    old = castedOp0;
    {
      auto variadic_operand_range = castedOp0.getODSOperands(0);
      if (variadic_operand_range.size() != 2) return ::mlir::failure();
      {
        auto *local_op_0 = variadic_operand_range[0].getDefiningOp();
        if (!(local_op_0)){
          return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
            diag << "There's no operation that defines variadic operand 0 (variadic sub-opearnd #0) of castedOp0";
          });
        }
        if(::mlir::failed(static_dag_matcher_9(rewriter, local_op_0, tblgen_ops, x))) {
          return ::mlir::failure();
        }
        tblgen_ops.push_back(local_op_0);
      }
      {
        auto *local_op_1 = variadic_operand_range[1].getDefiningOp();
        if (!(local_op_1)){
          return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
            diag << "There's no operation that defines variadic operand 0 (variadic sub-opearnd #1) of castedOp0";
          });
        }
        auto castedOp1 = ::llvm::dyn_cast<::circt::firrtl::AsUIntPrimOp>(local_op_1); (void)castedOp1;
        if (!(castedOp1)){
          return rewriter.notifyMatchFailure(local_op_1, [&](::mlir::Diagnostic &diag) {
            diag << "castedOp1 is not ::circt::firrtl::AsUIntPrimOp type";
          });
        }
        y = castedOp1.getODSOperands(0);
        tblgen_ops.push_back(local_op_1);
      }
    }
    if (!((type_isa<IntType>((*x.begin()).getType())))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'x' failed to satisfy constraint: ''";
      });
    }
    if (!((type_isa<IntType>((*y.begin()).getType())))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'y' failed to satisfy constraint: ''";
      });
    }
    if (!((type_cast<IntType>((*x.begin()).getType()).isSigned() == type_cast<IntType>((*y.begin()).getType()).isSigned()))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'x, y' failed to satisfy constraint: ''";
      });
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc(), tblgen_ops[1]->getLoc(), tblgen_ops[2]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_variadic_values_0;
    tblgen_variadic_values_0.push_back((*x.begin()));
    tblgen_variadic_values_0.push_back((*y.begin()));
    ::circt::firrtl::CatPrimOp tblgen_CatPrimOp_1;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values_0;
      for (auto v: tblgen_variadic_values_0) {
        tblgen_values_0.push_back(v);
      }
      tblgen_CatPrimOp_1 = ::circt::firrtl::CatPrimOp::create(rewriter, odsLoc,
        /*inputs=*/tblgen_values_0
      );
    }
    auto nativeVar_2 = moveNameHint((*old.getODSResults(0).begin()), tblgen_CatPrimOp_1); (void)nativeVar_2;

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ {nativeVar_2} }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    FIRRTLCanonicalization.td:648
*/
struct CatDoubleConst : public ::mlir::RewritePattern {
  CatDoubleConst(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("firrtl.cat", 2, context, {"firrtl.asUInt", "firrtl.cat"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range v(op0->getOperands());
    ::mlir::Operation::operand_range cst2(op0->getOperands());
    ::mlir::Operation::operand_range cst1(op0->getOperands());
    ::circt::firrtl::CatPrimOp old;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::circt::firrtl::CatPrimOp>(op0); (void)castedOp0;
    old = castedOp0;
    {
      auto variadic_operand_range = castedOp0.getODSOperands(0);
      if (variadic_operand_range.size() != 2) return ::mlir::failure();
      cst1 = variadic_operand_range.slice(0, 1);
      {
        auto *local_op_1 = variadic_operand_range[1].getDefiningOp();
        if (!(local_op_1)){
          return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
            diag << "There's no operation that defines variadic operand 0 (variadic sub-opearnd #1) of castedOp0";
          });
        }
        auto castedOp1 = ::llvm::dyn_cast<::circt::firrtl::CatPrimOp>(local_op_1); (void)castedOp1;
        if (!(castedOp1)){
          return rewriter.notifyMatchFailure(local_op_1, [&](::mlir::Diagnostic &diag) {
            diag << "castedOp1 is not ::circt::firrtl::CatPrimOp type";
          });
        }
        {
          auto variadic_operand_range = castedOp1.getODSOperands(0);
          if (variadic_operand_range.size() != 2) return ::mlir::failure();
          cst2 = variadic_operand_range.slice(0, 1);
          v = variadic_operand_range.slice(1, 1);
        }
        tblgen_ops.push_back(local_op_1);
      }
    }
    if (!((
      type_isa<FIRRTLBaseType>((*v.begin()).getType()) &&
        !type_cast<FIRRTLBaseType>((*v.begin()).getType()).getRecursiveTypeProperties().hasUninferredWidth
      ))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'v' failed to satisfy constraint: ''";
      });
    }
    if (!((
      isa_and_nonnull<ConstantOp, SpecialConstantOp, AggregateConstantOp>
        ((*cst1.begin()).getDefiningOp())
      ))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'cst1' failed to satisfy constraint: ''";
      });
    }
    if (!((
      isa_and_nonnull<ConstantOp, SpecialConstantOp, AggregateConstantOp>
        ((*cst2.begin()).getDefiningOp())
      ))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'cst2' failed to satisfy constraint: ''";
      });
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc(), tblgen_ops[1]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    ::circt::firrtl::AsUIntPrimOp tblgen_AsUIntPrimOp_2;
    {
      ::mlir::Value tblgen_value_0 = (*cst2.begin());
      tblgen_AsUIntPrimOp_2 = ::circt::firrtl::AsUIntPrimOp::create(rewriter, odsLoc,
        /*input=*/tblgen_value_0
      );
    }
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_variadic_values_1;
    tblgen_variadic_values_1.push_back((*cst1.begin()));
    tblgen_variadic_values_1.push_back(tblgen_AsUIntPrimOp_2);
    ::circt::firrtl::CatPrimOp tblgen_CatPrimOp_3;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values_0;
      for (auto v: tblgen_variadic_values_1) {
        tblgen_values_0.push_back(v);
      }
      tblgen_CatPrimOp_3 = ::circt::firrtl::CatPrimOp::create(rewriter, odsLoc,
        /*inputs=*/tblgen_values_0
      );
    }
    ::circt::firrtl::AsUIntPrimOp tblgen_AsUIntPrimOp_4;
    {
      ::mlir::Value tblgen_value_0 = (*v.begin());
      tblgen_AsUIntPrimOp_4 = ::circt::firrtl::AsUIntPrimOp::create(rewriter, odsLoc,
        /*input=*/tblgen_value_0
      );
    }
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_variadic_values_0;
    tblgen_variadic_values_0.push_back(tblgen_CatPrimOp_3);
    tblgen_variadic_values_0.push_back(tblgen_AsUIntPrimOp_4);
    ::circt::firrtl::CatPrimOp tblgen_CatPrimOp_5;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values_0;
      for (auto v: tblgen_variadic_values_0) {
        tblgen_values_0.push_back(v);
      }
      tblgen_CatPrimOp_5 = ::circt::firrtl::CatPrimOp::create(rewriter, odsLoc,
        /*inputs=*/tblgen_values_0
      );
    }
    auto nativeVar_6 = moveNameHint((*old.getODSResults(0).begin()), tblgen_CatPrimOp_5); (void)nativeVar_6;

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ {nativeVar_6} }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    FIRRTLCanonicalization.td:215
*/
struct ConnectExtension : public ::mlir::RewritePattern {
  ConnectExtension(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("firrtl.connect", 1, context, {"firrtl.matchingconnect", "firrtl.pad"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range src(op0->getOperands());
    ::mlir::Operation::operand_range dst(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    if(::mlir::failed(static_dag_matcher_10(rewriter, op0, tblgen_ops, src, dst))) {
      return ::mlir::failure();
    }
    auto castedOp0 = ::llvm::dyn_cast_or_null<::circt::firrtl::ConnectOp>(op0); (void)castedOp0;
    if (!((type_isa<IntType>(((*dst.begin()).getType()))))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "value entity 'dst' failed to satisfy constraint: 'sint or uint type'";
      });
    }
    if (!((type_isa<IntType>(((*src.begin()).getType()))))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "value entity 'src' failed to satisfy constraint: 'sint or uint type'";
      });
    }
    if (!((
      type_isa<FIRRTLBaseType>((*dst.begin()).getType()) &&
        !type_cast<FIRRTLBaseType>((*dst.begin()).getType()).getRecursiveTypeProperties().hasUninferredWidth
      ))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'dst' failed to satisfy constraint: ''";
      });
    }
    if (!((
      type_isa<FIRRTLBaseType>((*src.begin()).getType()) &&
        !type_cast<FIRRTLBaseType>((*src.begin()).getType()).getRecursiveTypeProperties().hasUninferredWidth
      ))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'src' failed to satisfy constraint: ''";
      });
    }
    if (!((!areAnonymousTypesEquivalent((*src.begin()).getType(), (*dst.begin()).getType())))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'src, dst' failed to satisfy constraint: ''";
      });
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    auto nativeVar_0 = type_cast<FIRRTLBaseType>((*dst.begin()).getType()).getBitWidthOrSentinel(); (void)nativeVar_0;
    ::circt::firrtl::PadPrimOp tblgen_PadPrimOp_1;
    {
      ::mlir::Value tblgen_value_0 = (*src.begin());
      tblgen_PadPrimOp_1 = ::circt::firrtl::PadPrimOp::create(rewriter, odsLoc,
        /*input=*/tblgen_value_0,
        /*amount=*/nativeVar_0
      );
    }
    ::circt::firrtl::MatchingConnectOp tblgen_MatchingConnectOp_2;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::circt::firrtl::MatchingConnectOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*dst.begin()));
      tblgen_values.push_back((*tblgen_PadPrimOp_1.getODSResults(0).begin()));
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      tblgen_MatchingConnectOp_2 = ::circt::firrtl::MatchingConnectOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }
    rewriter.eraseOp(op0);
    return ::mlir::success();
  }
};

/* Generated from:
    FIRRTLCanonicalization.td:209
*/
struct ConnectSameType : public ::mlir::RewritePattern {
  ConnectSameType(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("firrtl.connect", 1, context, {"firrtl.matchingconnect"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range src(op0->getOperands());
    ::mlir::Operation::operand_range dst(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    if(::mlir::failed(static_dag_matcher_10(rewriter, op0, tblgen_ops, src, dst))) {
      return ::mlir::failure();
    }
    auto castedOp0 = ::llvm::dyn_cast_or_null<::circt::firrtl::ConnectOp>(op0); (void)castedOp0;
    if (!((areAnonymousTypesEquivalent((*dst.begin()).getType(), (*src.begin()).getType())))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'dst, src' failed to satisfy constraint: ''";
      });
    }
    if (!((
      type_isa<FIRRTLBaseType>((*dst.begin()).getType()) &&
        !type_cast<FIRRTLBaseType>((*dst.begin()).getType()).getRecursiveTypeProperties().hasUninferredWidth
      ))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'dst' failed to satisfy constraint: ''";
      });
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::circt::firrtl::MatchingConnectOp tblgen_MatchingConnectOp_0;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::circt::firrtl::MatchingConnectOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*dst.begin()));
      tblgen_values.push_back((*src.begin()));
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      tblgen_MatchingConnectOp_0 = ::circt::firrtl::MatchingConnectOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }
    rewriter.eraseOp(op0);
    return ::mlir::success();
  }
};

/* Generated from:
    FIRRTLCanonicalization.td:228
*/
struct DShlOfConstant : public ::mlir::RewritePattern {
  DShlOfConstant(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("firrtl.dshl", 2, context, {"firrtl.pad", "firrtl.shl"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::IntegerAttr cst;
    ::mlir::Operation::operand_range x(op0->getOperands());
    ::circt::firrtl::DShlPrimOp old;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::circt::firrtl::DShlPrimOp>(op0); (void)castedOp0;
    old = castedOp0;
    x = castedOp0.getODSOperands(0);
    {
      auto *op1 = (*castedOp0.getODSOperands(1).begin()).getDefiningOp();
      if (!(op1)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "There's no operation that defines operand 1 of castedOp0";
        });
      }
      if(::mlir::failed(static_dag_matcher_11(rewriter, op1, tblgen_ops, cst))) {
        return ::mlir::failure();
      }
      tblgen_ops.push_back(op1);
    }
    if (!((
      type_isa<FIRRTLBaseType>((*x.begin()).getType()) &&
        !type_cast<FIRRTLBaseType>((*x.begin()).getType()).getRecursiveTypeProperties().hasUninferredWidth
      ))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'x' failed to satisfy constraint: ''";
      });
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc(), tblgen_ops[1]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    auto nativeVar_0 = rewriter.getI32IntegerAttr(cst.getValue().getLimitedValue(1ULL << 31)); (void)nativeVar_0;
    ::circt::firrtl::ShlPrimOp tblgen_ShlPrimOp_1;
    {
      ::mlir::Value tblgen_value_0 = (*x.begin());
      tblgen_ShlPrimOp_1 = ::circt::firrtl::ShlPrimOp::create(rewriter, odsLoc,
        /*input=*/tblgen_value_0,
        /*amount=*/nativeVar_0
      );
    }
    auto nativeVar_2 = moveNameHint((*old.getODSResults(0).begin()), tblgen_ShlPrimOp_1); (void)nativeVar_2;
    auto nativeVar_3 = rewriter.getI32IntegerAttr(type_cast<FIRRTLBaseType>((*old.getODSResults(0).begin()).getType()).getBitWidthOrSentinel()); (void)nativeVar_3;
    ::circt::firrtl::PadPrimOp tblgen_PadPrimOp_4;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::circt::firrtl::PadPrimOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back(nativeVar_2);
      tblgen_props.amount = ::llvm::dyn_cast_if_present<decltype(tblgen_props.amount)>(nativeVar_3);
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      tblgen_PadPrimOp_4 = ::circt::firrtl::PadPrimOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ tblgen_PadPrimOp_4.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    FIRRTLCanonicalization.td:234
*/
struct DShrOfConstant : public ::mlir::RewritePattern {
  DShrOfConstant(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("firrtl.dshr", 2, context, {"firrtl.pad", "firrtl.shr"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::IntegerAttr cst;
    ::mlir::Operation::operand_range x(op0->getOperands());
    ::circt::firrtl::DShrPrimOp old;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::circt::firrtl::DShrPrimOp>(op0); (void)castedOp0;
    old = castedOp0;
    x = castedOp0.getODSOperands(0);
    {
      auto *op1 = (*castedOp0.getODSOperands(1).begin()).getDefiningOp();
      if (!(op1)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "There's no operation that defines operand 1 of castedOp0";
        });
      }
      if(::mlir::failed(static_dag_matcher_11(rewriter, op1, tblgen_ops, cst))) {
        return ::mlir::failure();
      }
      tblgen_ops.push_back(op1);
    }
    if (!((
      type_isa<FIRRTLBaseType>((*x.begin()).getType()) &&
        !type_cast<FIRRTLBaseType>((*x.begin()).getType()).getRecursiveTypeProperties().hasUninferredWidth
      ))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'x' failed to satisfy constraint: ''";
      });
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc(), tblgen_ops[1]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    auto nativeVar_0 = rewriter.getI32IntegerAttr(cst.getValue().getLimitedValue(1ULL << 31)); (void)nativeVar_0;
    ::circt::firrtl::ShrPrimOp tblgen_ShrPrimOp_1;
    {
      ::mlir::Value tblgen_value_0 = (*x.begin());
      tblgen_ShrPrimOp_1 = ::circt::firrtl::ShrPrimOp::create(rewriter, odsLoc,
        /*input=*/tblgen_value_0,
        /*amount=*/nativeVar_0
      );
    }
    auto nativeVar_2 = moveNameHint((*old.getODSResults(0).begin()), tblgen_ShrPrimOp_1); (void)nativeVar_2;
    auto nativeVar_3 = rewriter.getI32IntegerAttr(type_cast<FIRRTLBaseType>((*old.getODSResults(0).begin()).getType()).getBitWidthOrSentinel()); (void)nativeVar_3;
    ::circt::firrtl::PadPrimOp tblgen_PadPrimOp_4;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::circt::firrtl::PadPrimOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back(nativeVar_2);
      tblgen_props.amount = ::llvm::dyn_cast_if_present<decltype(tblgen_props.amount)>(nativeVar_3);
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      tblgen_PadPrimOp_4 = ::circt::firrtl::PadPrimOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ tblgen_PadPrimOp_4.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    FIRRTLCanonicalization.td:155
*/
struct GEQWithConstLHS : public ::mlir::RewritePattern {
  GEQWithConstLHS(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("firrtl.geq", 1, context, {"firrtl.leq"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range rhs(op0->getOperands());
    ::mlir::Operation::operand_range lhs(op0->getOperands());
    ::circt::firrtl::GEQPrimOp old;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::circt::firrtl::GEQPrimOp>(op0); (void)castedOp0;
    old = castedOp0;
    lhs = castedOp0.getODSOperands(0);
    rhs = castedOp0.getODSOperands(1);
    if (!((
      isa_and_nonnull<ConstantOp, SpecialConstantOp, AggregateConstantOp>
        ((*lhs.begin()).getDefiningOp())
      ))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'lhs' failed to satisfy constraint: ''";
      });
    }
    if (!((
      !isa_and_nonnull<ConstantOp, SpecialConstantOp, AggregateConstantOp>
        ((*rhs.begin()).getDefiningOp())
      ))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'rhs' failed to satisfy constraint: ''";
      });
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    ::circt::firrtl::LEQPrimOp tblgen_LEQPrimOp_0;
    {
      ::mlir::Value tblgen_value_0 = (*rhs.begin());
      ::mlir::Value tblgen_value_1 = (*lhs.begin());
      tblgen_LEQPrimOp_0 = ::circt::firrtl::LEQPrimOp::create(rewriter, odsLoc,
        /*lhs=*/tblgen_value_0,
        /*rhs=*/tblgen_value_1
      );
    }
    auto nativeVar_1 = moveNameHint((*old.getODSResults(0).begin()), tblgen_LEQPrimOp_0); (void)nativeVar_1;

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ {nativeVar_1} }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    FIRRTLCanonicalization.td:161
*/
struct GTWithConstLHS : public ::mlir::RewritePattern {
  GTWithConstLHS(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("firrtl.gt", 1, context, {"firrtl.lt"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range rhs(op0->getOperands());
    ::mlir::Operation::operand_range lhs(op0->getOperands());
    ::circt::firrtl::GTPrimOp old;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::circt::firrtl::GTPrimOp>(op0); (void)castedOp0;
    old = castedOp0;
    lhs = castedOp0.getODSOperands(0);
    rhs = castedOp0.getODSOperands(1);
    if (!((
      isa_and_nonnull<ConstantOp, SpecialConstantOp, AggregateConstantOp>
        ((*lhs.begin()).getDefiningOp())
      ))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'lhs' failed to satisfy constraint: ''";
      });
    }
    if (!((
      !isa_and_nonnull<ConstantOp, SpecialConstantOp, AggregateConstantOp>
        ((*rhs.begin()).getDefiningOp())
      ))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'rhs' failed to satisfy constraint: ''";
      });
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    ::circt::firrtl::LTPrimOp tblgen_LTPrimOp_0;
    {
      ::mlir::Value tblgen_value_0 = (*rhs.begin());
      ::mlir::Value tblgen_value_1 = (*lhs.begin());
      tblgen_LTPrimOp_0 = ::circt::firrtl::LTPrimOp::create(rewriter, odsLoc,
        /*lhs=*/tblgen_value_0,
        /*rhs=*/tblgen_value_1
      );
    }
    auto nativeVar_1 = moveNameHint((*old.getODSResults(0).begin()), tblgen_LTPrimOp_0); (void)nativeVar_1;

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ {nativeVar_1} }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    FIRRTLCanonicalization.td:143
*/
struct LEQWithConstLHS : public ::mlir::RewritePattern {
  LEQWithConstLHS(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("firrtl.leq", 1, context, {"firrtl.geq"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range rhs(op0->getOperands());
    ::mlir::Operation::operand_range lhs(op0->getOperands());
    ::circt::firrtl::LEQPrimOp old;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::circt::firrtl::LEQPrimOp>(op0); (void)castedOp0;
    old = castedOp0;
    lhs = castedOp0.getODSOperands(0);
    rhs = castedOp0.getODSOperands(1);
    if (!((
      isa_and_nonnull<ConstantOp, SpecialConstantOp, AggregateConstantOp>
        ((*lhs.begin()).getDefiningOp())
      ))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'lhs' failed to satisfy constraint: ''";
      });
    }
    if (!((
      !isa_and_nonnull<ConstantOp, SpecialConstantOp, AggregateConstantOp>
        ((*rhs.begin()).getDefiningOp())
      ))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'rhs' failed to satisfy constraint: ''";
      });
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    ::circt::firrtl::GEQPrimOp tblgen_GEQPrimOp_0;
    {
      ::mlir::Value tblgen_value_0 = (*rhs.begin());
      ::mlir::Value tblgen_value_1 = (*lhs.begin());
      tblgen_GEQPrimOp_0 = ::circt::firrtl::GEQPrimOp::create(rewriter, odsLoc,
        /*lhs=*/tblgen_value_0,
        /*rhs=*/tblgen_value_1
      );
    }
    auto nativeVar_1 = moveNameHint((*old.getODSResults(0).begin()), tblgen_GEQPrimOp_0); (void)nativeVar_1;

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ {nativeVar_1} }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    FIRRTLCanonicalization.td:149
*/
struct LTWithConstLHS : public ::mlir::RewritePattern {
  LTWithConstLHS(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("firrtl.lt", 1, context, {"firrtl.gt"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range rhs(op0->getOperands());
    ::mlir::Operation::operand_range lhs(op0->getOperands());
    ::circt::firrtl::LTPrimOp old;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::circt::firrtl::LTPrimOp>(op0); (void)castedOp0;
    old = castedOp0;
    lhs = castedOp0.getODSOperands(0);
    rhs = castedOp0.getODSOperands(1);
    if (!((
      isa_and_nonnull<ConstantOp, SpecialConstantOp, AggregateConstantOp>
        ((*lhs.begin()).getDefiningOp())
      ))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'lhs' failed to satisfy constraint: ''";
      });
    }
    if (!((
      !isa_and_nonnull<ConstantOp, SpecialConstantOp, AggregateConstantOp>
        ((*rhs.begin()).getDefiningOp())
      ))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'rhs' failed to satisfy constraint: ''";
      });
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    ::circt::firrtl::GTPrimOp tblgen_GTPrimOp_0;
    {
      ::mlir::Value tblgen_value_0 = (*rhs.begin());
      ::mlir::Value tblgen_value_1 = (*lhs.begin());
      tblgen_GTPrimOp_0 = ::circt::firrtl::GTPrimOp::create(rewriter, odsLoc,
        /*lhs=*/tblgen_value_0,
        /*rhs=*/tblgen_value_1
      );
    }
    auto nativeVar_1 = moveNameHint((*old.getODSResults(0).begin()), tblgen_GTPrimOp_0); (void)nativeVar_1;

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ {nativeVar_1} }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    FIRRTLCanonicalization.td:630
*/
struct Mux2PadSel : public ::mlir::RewritePattern {
  Mux2PadSel(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("firrtl.int.mux2cell", 1, context, {"firrtl.constant", "firrtl.int.mux2cell"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range a(op0->getOperands());
    ::mlir::Operation::operand_range cond(op0->getOperands());
    ::mlir::Operation::operand_range b(op0->getOperands());
    ::circt::firrtl::Mux2CellIntrinsicOp old;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::circt::firrtl::Mux2CellIntrinsicOp>(op0); (void)castedOp0;
    old = castedOp0;
    cond = castedOp0.getODSOperands(0);
    a = castedOp0.getODSOperands(1);
    b = castedOp0.getODSOperands(2);
    if (!((type_cast<IntType>((*cond.begin()).getType()).getBitWidthOrSentinel() >= 0 &&type_cast<IntType>((*cond.begin()).getType()).getBitWidthOrSentinel()< 1))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'cond' failed to satisfy constraint: ''";
      });
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    auto nativeVar_0 = getIntZerosAttr(rewriter.getType<UIntType>(1)); (void)nativeVar_0;
    ::circt::firrtl::ConstantOp tblgen_ConstantOp_1;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::circt::firrtl::ConstantOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_props.value = ::llvm::dyn_cast_if_present<decltype(tblgen_props.value)>(nativeVar_0);
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      tblgen_types.push_back(rewriter.getType<UIntType>(1));
      tblgen_ConstantOp_1 = ::circt::firrtl::ConstantOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }
    ::circt::firrtl::Mux2CellIntrinsicOp tblgen_Mux2CellIntrinsicOp_2;
    {
      ::mlir::Value tblgen_value_0 = (*tblgen_ConstantOp_1.getODSResults(0).begin());
      ::mlir::Value tblgen_value_1 = (*a.begin());
      ::mlir::Value tblgen_value_2 = (*b.begin());
      tblgen_Mux2CellIntrinsicOp_2 = ::circt::firrtl::Mux2CellIntrinsicOp::create(rewriter, odsLoc,
        /*sel=*/tblgen_value_0,
        /*high=*/tblgen_value_1,
        /*low=*/tblgen_value_2
      );
    }
    auto nativeVar_3 = moveNameHint((*old.getODSResults(0).begin()), tblgen_Mux2CellIntrinsicOp_2); (void)nativeVar_3;

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ {nativeVar_3} }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    FIRRTLCanonicalization.td:640
*/
struct Mux4PadSel : public ::mlir::RewritePattern {
  Mux4PadSel(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("firrtl.int.mux4cell", 1, context, {"firrtl.int.mux4cell", "firrtl.pad"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range c(op0->getOperands());
    ::mlir::Operation::operand_range d(op0->getOperands());
    ::mlir::Operation::operand_range a(op0->getOperands());
    ::mlir::Operation::operand_range cond(op0->getOperands());
    ::mlir::Operation::operand_range b(op0->getOperands());
    ::circt::firrtl::Mux4CellIntrinsicOp old;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::circt::firrtl::Mux4CellIntrinsicOp>(op0); (void)castedOp0;
    old = castedOp0;
    cond = castedOp0.getODSOperands(0);
    a = castedOp0.getODSOperands(1);
    b = castedOp0.getODSOperands(2);
    c = castedOp0.getODSOperands(3);
    d = castedOp0.getODSOperands(4);
    if (!((type_cast<IntType>((*cond.begin()).getType()).getBitWidthOrSentinel() >= 0 &&type_cast<IntType>((*cond.begin()).getType()).getBitWidthOrSentinel()< 2))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'cond' failed to satisfy constraint: ''";
      });
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    auto nativeVar_0 = rewriter.getI32IntegerAttr(2); (void)nativeVar_0;
    ::circt::firrtl::PadPrimOp tblgen_PadPrimOp_1;
    {
      ::mlir::Value tblgen_value_0 = (*cond.begin());
      tblgen_PadPrimOp_1 = ::circt::firrtl::PadPrimOp::create(rewriter, odsLoc,
        /*input=*/tblgen_value_0,
        /*amount=*/nativeVar_0
      );
    }
    ::circt::firrtl::Mux4CellIntrinsicOp tblgen_Mux4CellIntrinsicOp_2;
    {
      ::mlir::Value tblgen_value_0 = (*tblgen_PadPrimOp_1.getODSResults(0).begin());
      ::mlir::Value tblgen_value_1 = (*a.begin());
      ::mlir::Value tblgen_value_2 = (*b.begin());
      ::mlir::Value tblgen_value_3 = (*c.begin());
      ::mlir::Value tblgen_value_4 = (*d.begin());
      tblgen_Mux4CellIntrinsicOp_2 = ::circt::firrtl::Mux4CellIntrinsicOp::create(rewriter, odsLoc,
        /*sel=*/tblgen_value_0,
        /*v3=*/tblgen_value_1,
        /*v2=*/tblgen_value_2,
        /*v1=*/tblgen_value_3,
        /*v0=*/tblgen_value_4
      );
    }
    auto nativeVar_3 = moveNameHint((*old.getODSResults(0).begin()), tblgen_Mux4CellIntrinsicOp_2); (void)nativeVar_3;

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ {nativeVar_3} }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    FIRRTLCanonicalization.td:602
*/
struct MuxEQOperands : public ::mlir::RewritePattern {
  MuxEQOperands(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("firrtl.mux", 2, context, {}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range b(op0->getOperands());
    ::mlir::Operation::operand_range b0(op0->getOperands());
    ::mlir::Operation::operand_range a(op0->getOperands());
    ::mlir::Operation::operand_range a0(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::circt::firrtl::MuxPrimOp>(op0); (void)castedOp0;
    {
      auto *op1 = (*castedOp0.getODSOperands(0).begin()).getDefiningOp();
      if (!(op1)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "There's no operation that defines operand 0 of castedOp0";
        });
      }
      auto castedOp1 = ::llvm::dyn_cast<::circt::firrtl::EQPrimOp>(op1); (void)castedOp1;
      if (!(castedOp1)){
        return rewriter.notifyMatchFailure(op1, [&](::mlir::Diagnostic &diag) {
          diag << "castedOp1 is not ::circt::firrtl::EQPrimOp type";
        });
      }
      a0 = castedOp1.getODSOperands(0);
      b0 = castedOp1.getODSOperands(1);
      tblgen_ops.push_back(op1);
    }
    a = castedOp0.getODSOperands(1);
    b = castedOp0.getODSOperands(2);
    if (!(*b.begin() == *b0.begin())){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "Operands 'b' and 'b0' must be equal";
      });
    }
    if (!(*a.begin() == *a0.begin())){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "Operands 'a' and 'a0' must be equal";
      });
    }
    if (!((areAnonymousTypesEquivalent((*a.begin()).getType(), (*b.begin()).getType())))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'a, b' failed to satisfy constraint: ''";
      });
    }
    if (!((
      type_isa<FIRRTLBaseType>((*a.begin()).getType()) &&
        !type_cast<FIRRTLBaseType>((*a.begin()).getType()).getRecursiveTypeProperties().hasUninferredWidth
      ))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'a' failed to satisfy constraint: ''";
      });
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc(), tblgen_ops[1]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ b }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    FIRRTLCanonicalization.td:608
*/
struct MuxEQOperandsSwapped : public ::mlir::RewritePattern {
  MuxEQOperandsSwapped(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("firrtl.mux", 2, context, {}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range a(op0->getOperands());
    ::mlir::Operation::operand_range a0(op0->getOperands());
    ::mlir::Operation::operand_range b(op0->getOperands());
    ::mlir::Operation::operand_range b0(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::circt::firrtl::MuxPrimOp>(op0); (void)castedOp0;
    {
      auto *op1 = (*castedOp0.getODSOperands(0).begin()).getDefiningOp();
      if (!(op1)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "There's no operation that defines operand 0 of castedOp0";
        });
      }
      auto castedOp1 = ::llvm::dyn_cast<::circt::firrtl::EQPrimOp>(op1); (void)castedOp1;
      if (!(castedOp1)){
        return rewriter.notifyMatchFailure(op1, [&](::mlir::Diagnostic &diag) {
          diag << "castedOp1 is not ::circt::firrtl::EQPrimOp type";
        });
      }
      b0 = castedOp1.getODSOperands(0);
      a0 = castedOp1.getODSOperands(1);
      tblgen_ops.push_back(op1);
    }
    a = castedOp0.getODSOperands(1);
    b = castedOp0.getODSOperands(2);
    if (!(*a.begin() == *a0.begin())){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "Operands 'a' and 'a0' must be equal";
      });
    }
    if (!(*b.begin() == *b0.begin())){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "Operands 'b' and 'b0' must be equal";
      });
    }
    if (!((areAnonymousTypesEquivalent((*a.begin()).getType(), (*b.begin()).getType())))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'a, b' failed to satisfy constraint: ''";
      });
    }
    if (!((
      type_isa<FIRRTLBaseType>((*a.begin()).getType()) &&
        !type_cast<FIRRTLBaseType>((*a.begin()).getType()).getRecursiveTypeProperties().hasUninferredWidth
      ))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'a' failed to satisfy constraint: ''";
      });
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc(), tblgen_ops[1]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ b }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    FIRRTLCanonicalization.td:614
*/
struct MuxNEQ : public ::mlir::RewritePattern {
  MuxNEQ(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("firrtl.mux", 2, context, {"firrtl.eq", "firrtl.mux"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range y(op0->getOperands());
    ::mlir::Operation::operand_range x(op0->getOperands());
    ::mlir::Operation::operand_range a(op0->getOperands());
    ::mlir::Operation::operand_range b(op0->getOperands());
    ::circt::firrtl::MuxPrimOp old;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::circt::firrtl::MuxPrimOp>(op0); (void)castedOp0;
    old = castedOp0;
    {
      auto *op1 = (*castedOp0.getODSOperands(0).begin()).getDefiningOp();
      if (!(op1)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "There's no operation that defines operand 0 of castedOp0";
        });
      }
      auto castedOp1 = ::llvm::dyn_cast<::circt::firrtl::NEQPrimOp>(op1); (void)castedOp1;
      if (!(castedOp1)){
        return rewriter.notifyMatchFailure(op1, [&](::mlir::Diagnostic &diag) {
          diag << "castedOp1 is not ::circt::firrtl::NEQPrimOp type";
        });
      }
      a = castedOp1.getODSOperands(0);
      b = castedOp1.getODSOperands(1);
      tblgen_ops.push_back(op1);
    }
    x = castedOp0.getODSOperands(1);
    y = castedOp0.getODSOperands(2);
    if (!((areAnonymousTypesEquivalent((*x.begin()).getType(), (*y.begin()).getType())))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'x, y' failed to satisfy constraint: ''";
      });
    }
    if (!((
      type_isa<FIRRTLBaseType>((*x.begin()).getType()) &&
        !type_cast<FIRRTLBaseType>((*x.begin()).getType()).getRecursiveTypeProperties().hasUninferredWidth
      ))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'x' failed to satisfy constraint: ''";
      });
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc(), tblgen_ops[1]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    ::circt::firrtl::EQPrimOp tblgen_EQPrimOp_0;
    {
      ::mlir::Value tblgen_value_0 = (*a.begin());
      ::mlir::Value tblgen_value_1 = (*b.begin());
      tblgen_EQPrimOp_0 = ::circt::firrtl::EQPrimOp::create(rewriter, odsLoc,
        /*lhs=*/tblgen_value_0,
        /*rhs=*/tblgen_value_1
      );
    }
    ::circt::firrtl::MuxPrimOp tblgen_MuxPrimOp_1;
    {
      ::mlir::Value tblgen_value_0 = (*tblgen_EQPrimOp_0.getODSResults(0).begin());
      ::mlir::Value tblgen_value_1 = (*y.begin());
      ::mlir::Value tblgen_value_2 = (*x.begin());
      tblgen_MuxPrimOp_1 = ::circt::firrtl::MuxPrimOp::create(rewriter, odsLoc,
        /*sel=*/tblgen_value_0,
        /*high=*/tblgen_value_1,
        /*low=*/tblgen_value_2
      );
    }
    auto nativeVar_2 = moveNameHint((*old.getODSResults(0).begin()), tblgen_MuxPrimOp_1); (void)nativeVar_2;

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ {nativeVar_2} }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    FIRRTLCanonicalization.td:570
*/
struct MuxNot : public ::mlir::RewritePattern {
  MuxNot(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("firrtl.mux", 3, context, {"firrtl.not"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::circt::firrtl::ConstantOp ocst;
    ::circt::firrtl::ConstantOp zcst;
    ::mlir::Operation::operand_range cond(op0->getOperands());
    ::circt::firrtl::MuxPrimOp old;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::circt::firrtl::MuxPrimOp>(op0); (void)castedOp0;
    old = castedOp0;
    cond = castedOp0.getODSOperands(0);
    {
      auto *op1 = (*castedOp0.getODSOperands(1).begin()).getDefiningOp();
      if (!(op1)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "There's no operation that defines operand 1 of castedOp0";
        });
      }
      if(::mlir::failed(static_dag_matcher_1(rewriter, op1, tblgen_ops, zcst))) {
        return ::mlir::failure();
      }
      tblgen_ops.push_back(op1);
    }
    {
      auto *op1 = (*castedOp0.getODSOperands(2).begin()).getDefiningOp();
      if (!(op1)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "There's no operation that defines operand 2 of castedOp0";
        });
      }
      auto castedOp1 = ::llvm::dyn_cast<::circt::firrtl::ConstantOp>(op1); (void)castedOp1;
      if (!(castedOp1)){
        return rewriter.notifyMatchFailure(op1, [&](::mlir::Diagnostic &diag) {
          diag << "castedOp1 is not ::circt::firrtl::ConstantOp type";
        });
      }
      ocst = castedOp1;
      {
        [[maybe_unused]] auto tblgen_attr = castedOp1.getProperties().getValue();
        if (!(tblgen_attr)){
          return rewriter.notifyMatchFailure(castedOp1, [&](::mlir::Diagnostic &diag) {
            diag << "expected op 'firrtl.constant' to have attribute 'value' of type '::mlir::IntegerAttr'";
          });
        }
      }
      tblgen_ops.push_back(op1);
    }
    if (!((areAnonymousTypesEquivalent((*cond.begin()).getType(), (*zcst.getODSResults(0).begin()).getType())))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'cond, zcst' failed to satisfy constraint: ''";
      });
    }
    if (!((areAnonymousTypesEquivalent((*cond.begin()).getType(), (*ocst.getODSResults(0).begin()).getType())))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'cond, ocst' failed to satisfy constraint: ''";
      });
    }
    if (!((((*zcst.getODSResults(0).begin()).getDefiningOp<ConstantOp>() &&(*zcst.getODSResults(0).begin()).getDefiningOp<ConstantOp>().getValue().isZero())) || (((*zcst.getODSResults(0).begin()).getDefiningOp<SpecialConstantOp>() &&(*zcst.getODSResults(0).begin()).getDefiningOp<SpecialConstantOp>().getValue() == false)))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'zcst' failed to satisfy constraint: ''";
      });
    }
    if (!((((*ocst.getODSResults(0).begin()).getDefiningOp<ConstantOp>() &&(*ocst.getODSResults(0).begin()).getDefiningOp<ConstantOp>().getValue().isOne())) || (((*ocst.getODSResults(0).begin()).getDefiningOp<SpecialConstantOp>() &&(*ocst.getODSResults(0).begin()).getDefiningOp<SpecialConstantOp>().getValue() == true)))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'ocst' failed to satisfy constraint: ''";
      });
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc(), tblgen_ops[1]->getLoc(), tblgen_ops[2]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    ::circt::firrtl::NotPrimOp tblgen_NotPrimOp_0;
    {
      ::mlir::Value tblgen_value_0 = (*cond.begin());
      tblgen_NotPrimOp_0 = ::circt::firrtl::NotPrimOp::create(rewriter, odsLoc,
        /*input=*/tblgen_value_0
      );
    }
    auto nativeVar_1 = moveNameHint((*old.getODSResults(0).begin()), tblgen_NotPrimOp_0); (void)nativeVar_1;

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ {nativeVar_1} }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    FIRRTLCanonicalization.td:620
*/
struct MuxPadSel : public ::mlir::RewritePattern {
  MuxPadSel(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("firrtl.mux", 1, context, {"firrtl.constant", "firrtl.mux"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range a(op0->getOperands());
    ::mlir::Operation::operand_range cond(op0->getOperands());
    ::mlir::Operation::operand_range b(op0->getOperands());
    ::circt::firrtl::MuxPrimOp old;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::circt::firrtl::MuxPrimOp>(op0); (void)castedOp0;
    old = castedOp0;
    cond = castedOp0.getODSOperands(0);
    a = castedOp0.getODSOperands(1);
    b = castedOp0.getODSOperands(2);
    if (!((type_cast<IntType>((*cond.begin()).getType()).getBitWidthOrSentinel() >= 0 &&type_cast<IntType>((*cond.begin()).getType()).getBitWidthOrSentinel()< 1))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'cond' failed to satisfy constraint: ''";
      });
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    auto nativeVar_0 = getIntZerosAttr(rewriter.getType<UIntType>(1)); (void)nativeVar_0;
    ::circt::firrtl::ConstantOp tblgen_ConstantOp_1;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::circt::firrtl::ConstantOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_props.value = ::llvm::dyn_cast_if_present<decltype(tblgen_props.value)>(nativeVar_0);
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      tblgen_types.push_back(rewriter.getType<UIntType>(1));
      tblgen_ConstantOp_1 = ::circt::firrtl::ConstantOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }
    ::circt::firrtl::MuxPrimOp tblgen_MuxPrimOp_2;
    {
      ::mlir::Value tblgen_value_0 = (*tblgen_ConstantOp_1.getODSResults(0).begin());
      ::mlir::Value tblgen_value_1 = (*a.begin());
      ::mlir::Value tblgen_value_2 = (*b.begin());
      tblgen_MuxPrimOp_2 = ::circt::firrtl::MuxPrimOp::create(rewriter, odsLoc,
        /*sel=*/tblgen_value_0,
        /*high=*/tblgen_value_1,
        /*low=*/tblgen_value_2
      );
    }
    auto nativeVar_3 = moveNameHint((*old.getODSResults(0).begin()), tblgen_MuxPrimOp_2); (void)nativeVar_3;

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ {nativeVar_3} }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    FIRRTLCanonicalization.td:584
*/
struct MuxSameFalse : public ::mlir::RewritePattern {
  MuxSameFalse(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("firrtl.mux", 2, context, {"firrtl.and", "firrtl.mux"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range f(op0->getOperands());
    ::mlir::Operation::operand_range f0(op0->getOperands());
    ::mlir::Operation::operand_range cond2(op0->getOperands());
    ::mlir::Operation::operand_range cond1(op0->getOperands());
    ::mlir::Operation::operand_range t(op0->getOperands());
    ::circt::firrtl::MuxPrimOp old;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::circt::firrtl::MuxPrimOp>(op0); (void)castedOp0;
    old = castedOp0;
    cond1 = castedOp0.getODSOperands(0);
    {
      auto *op1 = (*castedOp0.getODSOperands(1).begin()).getDefiningOp();
      if (!(op1)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "There's no operation that defines operand 1 of castedOp0";
        });
      }
      if(::mlir::failed(static_dag_matcher_12(rewriter, op1, tblgen_ops, f0, t, cond2))) {
        return ::mlir::failure();
      }
      tblgen_ops.push_back(op1);
    }
    f = castedOp0.getODSOperands(2);
    if (!(*f.begin() == *f0.begin())){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "Operands 'f' and 'f0' must be equal";
      });
    }
    if (!((areAnonymousTypesEquivalent((*t.begin()).getType(), (*f.begin()).getType())))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 't, f' failed to satisfy constraint: ''";
      });
    }
    if (!((
      type_isa<FIRRTLBaseType>((*f.begin()).getType()) &&
        !type_cast<FIRRTLBaseType>((*f.begin()).getType()).getRecursiveTypeProperties().hasUninferredWidth
      ))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'f' failed to satisfy constraint: ''";
      });
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc(), tblgen_ops[1]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    ::circt::firrtl::AndPrimOp tblgen_AndPrimOp_0;
    {
      ::mlir::Value tblgen_value_0 = (*cond1.begin());
      ::mlir::Value tblgen_value_1 = (*cond2.begin());
      tblgen_AndPrimOp_0 = ::circt::firrtl::AndPrimOp::create(rewriter, odsLoc,
        /*lhs=*/tblgen_value_0,
        /*rhs=*/tblgen_value_1
      );
    }
    ::circt::firrtl::MuxPrimOp tblgen_MuxPrimOp_1;
    {
      ::mlir::Value tblgen_value_0 = (*tblgen_AndPrimOp_0.getODSResults(0).begin());
      ::mlir::Value tblgen_value_1 = (*t.begin());
      ::mlir::Value tblgen_value_2 = (*f.begin());
      tblgen_MuxPrimOp_1 = ::circt::firrtl::MuxPrimOp::create(rewriter, odsLoc,
        /*sel=*/tblgen_value_0,
        /*high=*/tblgen_value_1,
        /*low=*/tblgen_value_2
      );
    }
    auto nativeVar_2 = moveNameHint((*old.getODSResults(0).begin()), tblgen_MuxPrimOp_1); (void)nativeVar_2;

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ {nativeVar_2} }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    FIRRTLCanonicalization.td:578
*/
struct MuxSameTrue : public ::mlir::RewritePattern {
  MuxSameTrue(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("firrtl.mux", 2, context, {"firrtl.mux", "firrtl.or"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range f(op0->getOperands());
    ::mlir::Operation::operand_range cond2(op0->getOperands());
    ::mlir::Operation::operand_range cond1(op0->getOperands());
    ::mlir::Operation::operand_range t(op0->getOperands());
    ::mlir::Operation::operand_range t0(op0->getOperands());
    ::circt::firrtl::MuxPrimOp old;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::circt::firrtl::MuxPrimOp>(op0); (void)castedOp0;
    old = castedOp0;
    cond1 = castedOp0.getODSOperands(0);
    t0 = castedOp0.getODSOperands(1);
    {
      auto *op1 = (*castedOp0.getODSOperands(2).begin()).getDefiningOp();
      if (!(op1)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "There's no operation that defines operand 2 of castedOp0";
        });
      }
      if(::mlir::failed(static_dag_matcher_12(rewriter, op1, tblgen_ops, f, t, cond2))) {
        return ::mlir::failure();
      }
      tblgen_ops.push_back(op1);
    }
    if (!(*t.begin() == *t0.begin())){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "Operands 't' and 't0' must be equal";
      });
    }
    if (!((areAnonymousTypesEquivalent((*t.begin()).getType(), (*f.begin()).getType())))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 't, f' failed to satisfy constraint: ''";
      });
    }
    if (!((
      type_isa<FIRRTLBaseType>((*t.begin()).getType()) &&
        !type_cast<FIRRTLBaseType>((*t.begin()).getType()).getRecursiveTypeProperties().hasUninferredWidth
      ))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 't' failed to satisfy constraint: ''";
      });
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc(), tblgen_ops[1]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    ::circt::firrtl::OrPrimOp tblgen_OrPrimOp_0;
    {
      ::mlir::Value tblgen_value_0 = (*cond1.begin());
      ::mlir::Value tblgen_value_1 = (*cond2.begin());
      tblgen_OrPrimOp_0 = ::circt::firrtl::OrPrimOp::create(rewriter, odsLoc,
        /*lhs=*/tblgen_value_0,
        /*rhs=*/tblgen_value_1
      );
    }
    ::circt::firrtl::MuxPrimOp tblgen_MuxPrimOp_1;
    {
      ::mlir::Value tblgen_value_0 = (*tblgen_OrPrimOp_0.getODSResults(0).begin());
      ::mlir::Value tblgen_value_1 = (*t.begin());
      ::mlir::Value tblgen_value_2 = (*f.begin());
      tblgen_MuxPrimOp_1 = ::circt::firrtl::MuxPrimOp::create(rewriter, odsLoc,
        /*sel=*/tblgen_value_0,
        /*high=*/tblgen_value_1,
        /*low=*/tblgen_value_2
      );
    }
    auto nativeVar_2 = moveNameHint((*old.getODSResults(0).begin()), tblgen_MuxPrimOp_1); (void)nativeVar_2;

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ {nativeVar_2} }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    FIRRTLCanonicalization.td:590
*/
struct NarrowMuxLHS : public ::mlir::RewritePattern {
  NarrowMuxLHS(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("firrtl.mux", 3, context, {"firrtl.cat", "firrtl.mux"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range c(op0->getOperands());
    ::circt::firrtl::CatPrimOp rhs;
    ::mlir::Operation::operand_range a(op0->getOperands());
    ::mlir::Operation::operand_range a0(op0->getOperands());
    ::mlir::Operation::operand_range cond(op0->getOperands());
    ::mlir::Operation::operand_range b(op0->getOperands());
    ::circt::firrtl::CatPrimOp lhs;
    ::circt::firrtl::MuxPrimOp old;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::circt::firrtl::MuxPrimOp>(op0); (void)castedOp0;
    old = castedOp0;
    cond = castedOp0.getODSOperands(0);
    {
      auto *op1 = (*castedOp0.getODSOperands(1).begin()).getDefiningOp();
      if (!(op1)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "There's no operation that defines operand 1 of castedOp0";
        });
      }
      if(::mlir::failed(static_dag_matcher_13(rewriter, op1, tblgen_ops, a0, b, lhs))) {
        return ::mlir::failure();
      }
      tblgen_ops.push_back(op1);
    }
    {
      auto *op1 = (*castedOp0.getODSOperands(2).begin()).getDefiningOp();
      if (!(op1)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "There's no operation that defines operand 2 of castedOp0";
        });
      }
      auto castedOp1 = ::llvm::dyn_cast<::circt::firrtl::CatPrimOp>(op1); (void)castedOp1;
      if (!(castedOp1)){
        return rewriter.notifyMatchFailure(op1, [&](::mlir::Diagnostic &diag) {
          diag << "castedOp1 is not ::circt::firrtl::CatPrimOp type";
        });
      }
      rhs = castedOp1;
      {
        auto variadic_operand_range = castedOp1.getODSOperands(0);
        if (variadic_operand_range.size() != 2) return ::mlir::failure();
        a = variadic_operand_range.slice(0, 1);
        c = variadic_operand_range.slice(1, 1);
      }
      tblgen_ops.push_back(op1);
    }
    if (!(*a.begin() == *a0.begin())){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "Operands 'a' and 'a0' must be equal";
      });
    }
    if (!((areAnonymousTypesEquivalent((*lhs.getODSResults(0).begin()).getType(), (*rhs.getODSResults(0).begin()).getType())))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'lhs, rhs' failed to satisfy constraint: ''";
      });
    }
    if (!((
      type_isa<FIRRTLBaseType>((*lhs.getODSResults(0).begin()).getType()) &&
        !type_cast<FIRRTLBaseType>((*lhs.getODSResults(0).begin()).getType()).getRecursiveTypeProperties().hasUninferredWidth
      ))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'lhs' failed to satisfy constraint: ''";
      });
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc(), tblgen_ops[1]->getLoc(), tblgen_ops[2]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    ::circt::firrtl::MuxPrimOp tblgen_MuxPrimOp_1;
    {
      ::mlir::Value tblgen_value_0 = (*cond.begin());
      ::mlir::Value tblgen_value_1 = (*b.begin());
      ::mlir::Value tblgen_value_2 = (*c.begin());
      tblgen_MuxPrimOp_1 = ::circt::firrtl::MuxPrimOp::create(rewriter, odsLoc,
        /*sel=*/tblgen_value_0,
        /*high=*/tblgen_value_1,
        /*low=*/tblgen_value_2
      );
    }
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_variadic_values_0;
    tblgen_variadic_values_0.push_back((*a.begin()));
    tblgen_variadic_values_0.push_back(tblgen_MuxPrimOp_1);
    ::circt::firrtl::CatPrimOp tblgen_CatPrimOp_2;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values_0;
      for (auto v: tblgen_variadic_values_0) {
        tblgen_values_0.push_back(v);
      }
      tblgen_CatPrimOp_2 = ::circt::firrtl::CatPrimOp::create(rewriter, odsLoc,
        /*inputs=*/tblgen_values_0
      );
    }
    auto nativeVar_3 = moveNameHint((*old.getODSResults(0).begin()), tblgen_CatPrimOp_2); (void)nativeVar_3;

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ {nativeVar_3} }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    FIRRTLCanonicalization.td:596
*/
struct NarrowMuxRHS : public ::mlir::RewritePattern {
  NarrowMuxRHS(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("firrtl.mux", 3, context, {"firrtl.cat", "firrtl.mux"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range c(op0->getOperands());
    ::circt::firrtl::CatPrimOp rhs;
    ::mlir::Operation::operand_range a(op0->getOperands());
    ::mlir::Operation::operand_range cond(op0->getOperands());
    ::mlir::Operation::operand_range b(op0->getOperands());
    ::mlir::Operation::operand_range b0(op0->getOperands());
    ::circt::firrtl::CatPrimOp lhs;
    ::circt::firrtl::MuxPrimOp old;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::circt::firrtl::MuxPrimOp>(op0); (void)castedOp0;
    old = castedOp0;
    cond = castedOp0.getODSOperands(0);
    {
      auto *op1 = (*castedOp0.getODSOperands(1).begin()).getDefiningOp();
      if (!(op1)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "There's no operation that defines operand 1 of castedOp0";
        });
      }
      if(::mlir::failed(static_dag_matcher_13(rewriter, op1, tblgen_ops, a, b0, lhs))) {
        return ::mlir::failure();
      }
      tblgen_ops.push_back(op1);
    }
    {
      auto *op1 = (*castedOp0.getODSOperands(2).begin()).getDefiningOp();
      if (!(op1)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "There's no operation that defines operand 2 of castedOp0";
        });
      }
      auto castedOp1 = ::llvm::dyn_cast<::circt::firrtl::CatPrimOp>(op1); (void)castedOp1;
      if (!(castedOp1)){
        return rewriter.notifyMatchFailure(op1, [&](::mlir::Diagnostic &diag) {
          diag << "castedOp1 is not ::circt::firrtl::CatPrimOp type";
        });
      }
      rhs = castedOp1;
      {
        auto variadic_operand_range = castedOp1.getODSOperands(0);
        if (variadic_operand_range.size() != 2) return ::mlir::failure();
        c = variadic_operand_range.slice(0, 1);
        b = variadic_operand_range.slice(1, 1);
      }
      tblgen_ops.push_back(op1);
    }
    if (!(*b.begin() == *b0.begin())){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "Operands 'b' and 'b0' must be equal";
      });
    }
    if (!((areAnonymousTypesEquivalent((*lhs.getODSResults(0).begin()).getType(), (*rhs.getODSResults(0).begin()).getType())))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'lhs, rhs' failed to satisfy constraint: ''";
      });
    }
    if (!((
      type_isa<FIRRTLBaseType>((*lhs.getODSResults(0).begin()).getType()) &&
        !type_cast<FIRRTLBaseType>((*lhs.getODSResults(0).begin()).getType()).getRecursiveTypeProperties().hasUninferredWidth
      ))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'lhs' failed to satisfy constraint: ''";
      });
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc(), tblgen_ops[1]->getLoc(), tblgen_ops[2]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    ::circt::firrtl::MuxPrimOp tblgen_MuxPrimOp_1;
    {
      ::mlir::Value tblgen_value_0 = (*cond.begin());
      ::mlir::Value tblgen_value_1 = (*a.begin());
      ::mlir::Value tblgen_value_2 = (*c.begin());
      tblgen_MuxPrimOp_1 = ::circt::firrtl::MuxPrimOp::create(rewriter, odsLoc,
        /*sel=*/tblgen_value_0,
        /*high=*/tblgen_value_1,
        /*low=*/tblgen_value_2
      );
    }
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_variadic_values_0;
    tblgen_variadic_values_0.push_back(tblgen_MuxPrimOp_1);
    tblgen_variadic_values_0.push_back((*b.begin()));
    ::circt::firrtl::CatPrimOp tblgen_CatPrimOp_2;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values_0;
      for (auto v: tblgen_variadic_values_0) {
        tblgen_values_0.push_back(v);
      }
      tblgen_CatPrimOp_2 = ::circt::firrtl::CatPrimOp::create(rewriter, odsLoc,
        /*inputs=*/tblgen_values_0
      );
    }
    auto nativeVar_3 = moveNameHint((*old.getODSResults(0).begin()), tblgen_CatPrimOp_2); (void)nativeVar_3;

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ {nativeVar_3} }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    FIRRTLCanonicalization.td:173
*/
struct NotEq : public ::mlir::RewritePattern {
  NotEq(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("firrtl.not", 2, context, {"firrtl.neq"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range y(op0->getOperands());
    ::mlir::Operation::operand_range x(op0->getOperands());
    ::circt::firrtl::NotPrimOp old;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::circt::firrtl::NotPrimOp>(op0); (void)castedOp0;
    old = castedOp0;
    {
      auto *op1 = (*castedOp0.getODSOperands(0).begin()).getDefiningOp();
      if (!(op1)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "There's no operation that defines operand 0 of castedOp0";
        });
      }
      auto castedOp1 = ::llvm::dyn_cast<::circt::firrtl::EQPrimOp>(op1); (void)castedOp1;
      if (!(castedOp1)){
        return rewriter.notifyMatchFailure(op1, [&](::mlir::Diagnostic &diag) {
          diag << "castedOp1 is not ::circt::firrtl::EQPrimOp type";
        });
      }
      x = castedOp1.getODSOperands(0);
      y = castedOp1.getODSOperands(1);
      tblgen_ops.push_back(op1);
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc(), tblgen_ops[1]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    ::circt::firrtl::NEQPrimOp tblgen_NEQPrimOp_0;
    {
      ::mlir::Value tblgen_value_0 = (*x.begin());
      ::mlir::Value tblgen_value_1 = (*y.begin());
      tblgen_NEQPrimOp_0 = ::circt::firrtl::NEQPrimOp::create(rewriter, odsLoc,
        /*lhs=*/tblgen_value_0,
        /*rhs=*/tblgen_value_1
      );
    }
    auto nativeVar_1 = moveNameHint((*old.getODSResults(0).begin()), tblgen_NEQPrimOp_0); (void)nativeVar_1;

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ {nativeVar_1} }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    FIRRTLCanonicalization.td:197
*/
struct NotGeq : public ::mlir::RewritePattern {
  NotGeq(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("firrtl.not", 2, context, {"firrtl.lt"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range y(op0->getOperands());
    ::mlir::Operation::operand_range x(op0->getOperands());
    ::circt::firrtl::NotPrimOp old;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::circt::firrtl::NotPrimOp>(op0); (void)castedOp0;
    old = castedOp0;
    {
      auto *op1 = (*castedOp0.getODSOperands(0).begin()).getDefiningOp();
      if (!(op1)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "There's no operation that defines operand 0 of castedOp0";
        });
      }
      auto castedOp1 = ::llvm::dyn_cast<::circt::firrtl::GEQPrimOp>(op1); (void)castedOp1;
      if (!(castedOp1)){
        return rewriter.notifyMatchFailure(op1, [&](::mlir::Diagnostic &diag) {
          diag << "castedOp1 is not ::circt::firrtl::GEQPrimOp type";
        });
      }
      x = castedOp1.getODSOperands(0);
      y = castedOp1.getODSOperands(1);
      tblgen_ops.push_back(op1);
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc(), tblgen_ops[1]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    ::circt::firrtl::LTPrimOp tblgen_LTPrimOp_0;
    {
      ::mlir::Value tblgen_value_0 = (*x.begin());
      ::mlir::Value tblgen_value_1 = (*y.begin());
      tblgen_LTPrimOp_0 = ::circt::firrtl::LTPrimOp::create(rewriter, odsLoc,
        /*lhs=*/tblgen_value_0,
        /*rhs=*/tblgen_value_1
      );
    }
    auto nativeVar_1 = moveNameHint((*old.getODSResults(0).begin()), tblgen_LTPrimOp_0); (void)nativeVar_1;

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ {nativeVar_1} }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    FIRRTLCanonicalization.td:203
*/
struct NotGt : public ::mlir::RewritePattern {
  NotGt(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("firrtl.not", 2, context, {"firrtl.leq"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range y(op0->getOperands());
    ::mlir::Operation::operand_range x(op0->getOperands());
    ::circt::firrtl::NotPrimOp old;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::circt::firrtl::NotPrimOp>(op0); (void)castedOp0;
    old = castedOp0;
    {
      auto *op1 = (*castedOp0.getODSOperands(0).begin()).getDefiningOp();
      if (!(op1)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "There's no operation that defines operand 0 of castedOp0";
        });
      }
      auto castedOp1 = ::llvm::dyn_cast<::circt::firrtl::GTPrimOp>(op1); (void)castedOp1;
      if (!(castedOp1)){
        return rewriter.notifyMatchFailure(op1, [&](::mlir::Diagnostic &diag) {
          diag << "castedOp1 is not ::circt::firrtl::GTPrimOp type";
        });
      }
      x = castedOp1.getODSOperands(0);
      y = castedOp1.getODSOperands(1);
      tblgen_ops.push_back(op1);
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc(), tblgen_ops[1]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    ::circt::firrtl::LEQPrimOp tblgen_LEQPrimOp_0;
    {
      ::mlir::Value tblgen_value_0 = (*x.begin());
      ::mlir::Value tblgen_value_1 = (*y.begin());
      tblgen_LEQPrimOp_0 = ::circt::firrtl::LEQPrimOp::create(rewriter, odsLoc,
        /*lhs=*/tblgen_value_0,
        /*rhs=*/tblgen_value_1
      );
    }
    auto nativeVar_1 = moveNameHint((*old.getODSResults(0).begin()), tblgen_LEQPrimOp_0); (void)nativeVar_1;

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ {nativeVar_1} }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    FIRRTLCanonicalization.td:185
*/
struct NotLeq : public ::mlir::RewritePattern {
  NotLeq(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("firrtl.not", 2, context, {"firrtl.gt"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range y(op0->getOperands());
    ::mlir::Operation::operand_range x(op0->getOperands());
    ::circt::firrtl::NotPrimOp old;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::circt::firrtl::NotPrimOp>(op0); (void)castedOp0;
    old = castedOp0;
    {
      auto *op1 = (*castedOp0.getODSOperands(0).begin()).getDefiningOp();
      if (!(op1)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "There's no operation that defines operand 0 of castedOp0";
        });
      }
      auto castedOp1 = ::llvm::dyn_cast<::circt::firrtl::LEQPrimOp>(op1); (void)castedOp1;
      if (!(castedOp1)){
        return rewriter.notifyMatchFailure(op1, [&](::mlir::Diagnostic &diag) {
          diag << "castedOp1 is not ::circt::firrtl::LEQPrimOp type";
        });
      }
      x = castedOp1.getODSOperands(0);
      y = castedOp1.getODSOperands(1);
      tblgen_ops.push_back(op1);
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc(), tblgen_ops[1]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    ::circt::firrtl::GTPrimOp tblgen_GTPrimOp_0;
    {
      ::mlir::Value tblgen_value_0 = (*x.begin());
      ::mlir::Value tblgen_value_1 = (*y.begin());
      tblgen_GTPrimOp_0 = ::circt::firrtl::GTPrimOp::create(rewriter, odsLoc,
        /*lhs=*/tblgen_value_0,
        /*rhs=*/tblgen_value_1
      );
    }
    auto nativeVar_1 = moveNameHint((*old.getODSResults(0).begin()), tblgen_GTPrimOp_0); (void)nativeVar_1;

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ {nativeVar_1} }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    FIRRTLCanonicalization.td:191
*/
struct NotLt : public ::mlir::RewritePattern {
  NotLt(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("firrtl.not", 2, context, {"firrtl.geq"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range y(op0->getOperands());
    ::mlir::Operation::operand_range x(op0->getOperands());
    ::circt::firrtl::NotPrimOp old;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::circt::firrtl::NotPrimOp>(op0); (void)castedOp0;
    old = castedOp0;
    {
      auto *op1 = (*castedOp0.getODSOperands(0).begin()).getDefiningOp();
      if (!(op1)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "There's no operation that defines operand 0 of castedOp0";
        });
      }
      auto castedOp1 = ::llvm::dyn_cast<::circt::firrtl::LTPrimOp>(op1); (void)castedOp1;
      if (!(castedOp1)){
        return rewriter.notifyMatchFailure(op1, [&](::mlir::Diagnostic &diag) {
          diag << "castedOp1 is not ::circt::firrtl::LTPrimOp type";
        });
      }
      x = castedOp1.getODSOperands(0);
      y = castedOp1.getODSOperands(1);
      tblgen_ops.push_back(op1);
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc(), tblgen_ops[1]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    ::circt::firrtl::GEQPrimOp tblgen_GEQPrimOp_0;
    {
      ::mlir::Value tblgen_value_0 = (*x.begin());
      ::mlir::Value tblgen_value_1 = (*y.begin());
      tblgen_GEQPrimOp_0 = ::circt::firrtl::GEQPrimOp::create(rewriter, odsLoc,
        /*lhs=*/tblgen_value_0,
        /*rhs=*/tblgen_value_1
      );
    }
    auto nativeVar_1 = moveNameHint((*old.getODSResults(0).begin()), tblgen_GEQPrimOp_0); (void)nativeVar_1;

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ {nativeVar_1} }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    FIRRTLCanonicalization.td:179
*/
struct NotNeq : public ::mlir::RewritePattern {
  NotNeq(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("firrtl.not", 2, context, {"firrtl.eq"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range y(op0->getOperands());
    ::mlir::Operation::operand_range x(op0->getOperands());
    ::circt::firrtl::NotPrimOp old;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::circt::firrtl::NotPrimOp>(op0); (void)castedOp0;
    old = castedOp0;
    {
      auto *op1 = (*castedOp0.getODSOperands(0).begin()).getDefiningOp();
      if (!(op1)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "There's no operation that defines operand 0 of castedOp0";
        });
      }
      auto castedOp1 = ::llvm::dyn_cast<::circt::firrtl::NEQPrimOp>(op1); (void)castedOp1;
      if (!(castedOp1)){
        return rewriter.notifyMatchFailure(op1, [&](::mlir::Diagnostic &diag) {
          diag << "castedOp1 is not ::circt::firrtl::NEQPrimOp type";
        });
      }
      x = castedOp1.getODSOperands(0);
      y = castedOp1.getODSOperands(1);
      tblgen_ops.push_back(op1);
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc(), tblgen_ops[1]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    ::circt::firrtl::EQPrimOp tblgen_EQPrimOp_0;
    {
      ::mlir::Value tblgen_value_0 = (*x.begin());
      ::mlir::Value tblgen_value_1 = (*y.begin());
      tblgen_EQPrimOp_0 = ::circt::firrtl::EQPrimOp::create(rewriter, odsLoc,
        /*lhs=*/tblgen_value_0,
        /*rhs=*/tblgen_value_1
      );
    }
    auto nativeVar_1 = moveNameHint((*old.getODSResults(0).begin()), tblgen_EQPrimOp_0); (void)nativeVar_1;

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ {nativeVar_1} }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    FIRRTLCanonicalization.td:167
*/
struct NotNot : public ::mlir::RewritePattern {
  NotNot(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("firrtl.not", 2, context, {"firrtl.asUInt"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range x(op0->getOperands());
    ::circt::firrtl::NotPrimOp old;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::circt::firrtl::NotPrimOp>(op0); (void)castedOp0;
    old = castedOp0;
    {
      auto *op1 = (*castedOp0.getODSOperands(0).begin()).getDefiningOp();
      if (!(op1)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "There's no operation that defines operand 0 of castedOp0";
        });
      }
      auto castedOp1 = ::llvm::dyn_cast<::circt::firrtl::NotPrimOp>(op1); (void)castedOp1;
      if (!(castedOp1)){
        return rewriter.notifyMatchFailure(op1, [&](::mlir::Diagnostic &diag) {
          diag << "castedOp1 is not ::circt::firrtl::NotPrimOp type";
        });
      }
      x = castedOp1.getODSOperands(0);
      tblgen_ops.push_back(op1);
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc(), tblgen_ops[1]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    ::circt::firrtl::AsUIntPrimOp tblgen_AsUIntPrimOp_0;
    {
      ::mlir::Value tblgen_value_0 = (*x.begin());
      tblgen_AsUIntPrimOp_0 = ::circt::firrtl::AsUIntPrimOp::create(rewriter, odsLoc,
        /*input=*/tblgen_value_0
      );
    }
    auto nativeVar_1 = moveNameHint((*old.getODSResults(0).begin()), tblgen_AsUIntPrimOp_0); (void)nativeVar_1;

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ {nativeVar_1} }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    FIRRTLCanonicalization.td:386
*/
struct OrOfAllOne : public ::mlir::RewritePattern {
  OrOfAllOne(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("firrtl.or", 2, context, {}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::IntegerAttr cst;
    ::circt::firrtl::ConstantOp ocst;
    ::mlir::Operation::operand_range x(op0->getOperands());
    ::circt::firrtl::OrPrimOp old;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::circt::firrtl::OrPrimOp>(op0); (void)castedOp0;
    old = castedOp0;
    x = castedOp0.getODSOperands(0);
    {
      auto *op1 = (*castedOp0.getODSOperands(1).begin()).getDefiningOp();
      if (!(op1)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "There's no operation that defines operand 1 of castedOp0";
        });
      }
      if(::mlir::failed(static_dag_matcher_2(rewriter, op1, tblgen_ops, cst, ocst))) {
        return ::mlir::failure();
      }
      tblgen_ops.push_back(op1);
    }
    if (!((
      type_isa<FIRRTLBaseType>((*x.begin()).getType()) &&
        !type_cast<FIRRTLBaseType>((*x.begin()).getType()).getRecursiveTypeProperties().hasUninferredWidth
      ))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'x' failed to satisfy constraint: ''";
      });
    }
    if (!((areAnonymousTypesEquivalent((*x.begin()).getType(), (*ocst.getODSResults(0).begin()).getType())))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'x, ocst' failed to satisfy constraint: ''";
      });
    }
    if (!(((*ocst.getODSResults(0).begin()).getDefiningOp<ConstantOp>() && (*ocst.getODSResults(0).begin()).getDefiningOp<ConstantOp>().getValue().isAllOnes()))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'ocst' failed to satisfy constraint: ''";
      });
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc(), tblgen_ops[1]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    auto nativeVar_0 = ConstantOp::create(rewriter, (*old.getODSResults(0).begin()).getLoc(), type_cast<IntType>((*old.getODSResults(0).begin()).getType()), getIntOnesAttr((*old.getODSResults(0).begin()).getType())); (void)nativeVar_0;

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ {nativeVar_0} }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    FIRRTLCanonicalization.td:398
*/
struct OrOfPad : public ::mlir::RewritePattern {
  OrOfPad(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("firrtl.or", 2, context, {"firrtl.cat", "firrtl.head", "firrtl.or", "firrtl.tail"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::IntegerAttr n;
    ::mlir::Operation::operand_range y(op0->getOperands());
    ::circt::firrtl::PadPrimOp pad;
    ::mlir::Operation::operand_range x(op0->getOperands());
    ::circt::firrtl::OrPrimOp old;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::circt::firrtl::OrPrimOp>(op0); (void)castedOp0;
    old = castedOp0;
    x = castedOp0.getODSOperands(0);
    {
      auto *op1 = (*castedOp0.getODSOperands(1).begin()).getDefiningOp();
      if (!(op1)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "There's no operation that defines operand 1 of castedOp0";
        });
      }
      if(::mlir::failed(static_dag_matcher_4(rewriter, op1, tblgen_ops, n, y, pad))) {
        return ::mlir::failure();
      }
      tblgen_ops.push_back(op1);
    }
    if (!((
      type_isa<FIRRTLBaseType>((*x.begin()).getType()) &&
        !type_cast<FIRRTLBaseType>((*x.begin()).getType()).getRecursiveTypeProperties().hasUninferredWidth
      ))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'x' failed to satisfy constraint: ''";
      });
    }
    if (!((type_isa<UIntType>(((*x.begin()).getType()))))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "value entity 'x' failed to satisfy constraint: 'uint type'";
      });
    }
    if (!((areAnonymousTypesEquivalent((*x.begin()).getType(), (*pad.getODSResults(0).begin()).getType())))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'x, pad' failed to satisfy constraint: ''";
      });
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc(), tblgen_ops[1]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    auto nativeVar_1 = rewriter.getI32IntegerAttr(type_cast<FIRRTLBaseType>((*x.begin()).getType()).getBitWidthOrSentinel() - type_cast<FIRRTLBaseType>((*y.begin()).getType()).getBitWidthOrSentinel()); (void)nativeVar_1;
    ::circt::firrtl::HeadPrimOp tblgen_HeadPrimOp_2;
    {
      ::mlir::Value tblgen_value_0 = (*x.begin());
      tblgen_HeadPrimOp_2 = ::circt::firrtl::HeadPrimOp::create(rewriter, odsLoc,
        /*input=*/tblgen_value_0,
        /*amount=*/nativeVar_1
      );
    }
    auto nativeVar_3 = rewriter.getI32IntegerAttr(type_cast<FIRRTLBaseType>((*x.begin()).getType()).getBitWidthOrSentinel() - type_cast<FIRRTLBaseType>((*y.begin()).getType()).getBitWidthOrSentinel()); (void)nativeVar_3;
    ::circt::firrtl::TailPrimOp tblgen_TailPrimOp_4;
    {
      ::mlir::Value tblgen_value_0 = (*x.begin());
      tblgen_TailPrimOp_4 = ::circt::firrtl::TailPrimOp::create(rewriter, odsLoc,
        /*input=*/tblgen_value_0,
        /*amount=*/nativeVar_3
      );
    }
    ::circt::firrtl::OrPrimOp tblgen_OrPrimOp_5;
    {
      ::mlir::Value tblgen_value_0 = (*tblgen_TailPrimOp_4.getODSResults(0).begin());
      ::mlir::Value tblgen_value_1 = (*y.begin());
      tblgen_OrPrimOp_5 = ::circt::firrtl::OrPrimOp::create(rewriter, odsLoc,
        /*lhs=*/tblgen_value_0,
        /*rhs=*/tblgen_value_1
      );
    }
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_variadic_values_0;
    tblgen_variadic_values_0.push_back(tblgen_HeadPrimOp_2);
    tblgen_variadic_values_0.push_back(tblgen_OrPrimOp_5);
    ::circt::firrtl::CatPrimOp tblgen_CatPrimOp_6;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values_0;
      for (auto v: tblgen_variadic_values_0) {
        tblgen_values_0.push_back(v);
      }
      tblgen_CatPrimOp_6 = ::circt::firrtl::CatPrimOp::create(rewriter, odsLoc,
        /*inputs=*/tblgen_values_0
      );
    }
    auto nativeVar_7 = moveNameHint((*old.getODSResults(0).begin()), tblgen_CatPrimOp_6); (void)nativeVar_7;

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ {nativeVar_7} }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    FIRRTLCanonicalization.td:392
*/
struct OrOfSelf : public ::mlir::RewritePattern {
  OrOfSelf(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("firrtl.or", 1, context, {"firrtl.asUInt"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range x(op0->getOperands());
    ::mlir::Operation::operand_range x0(op0->getOperands());
    ::circt::firrtl::OrPrimOp old;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::circt::firrtl::OrPrimOp>(op0); (void)castedOp0;
    old = castedOp0;
    x0 = castedOp0.getODSOperands(0);
    x = castedOp0.getODSOperands(1);
    if (!(*x.begin() == *x0.begin())){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "Operands 'x' and 'x0' must be equal";
      });
    }
    if (!((
      type_isa<FIRRTLBaseType>((*x.begin()).getType()) &&
        !type_cast<FIRRTLBaseType>((*x.begin()).getType()).getRecursiveTypeProperties().hasUninferredWidth
      ))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'x' failed to satisfy constraint: ''";
      });
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    ::circt::firrtl::AsUIntPrimOp tblgen_AsUIntPrimOp_0;
    {
      ::mlir::Value tblgen_value_0 = (*x.begin());
      tblgen_AsUIntPrimOp_0 = ::circt::firrtl::AsUIntPrimOp::create(rewriter, odsLoc,
        /*input=*/tblgen_value_0
      );
    }
    auto nativeVar_1 = moveNameHint((*old.getODSResults(0).begin()), tblgen_AsUIntPrimOp_0); (void)nativeVar_1;

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ {nativeVar_1} }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    FIRRTLCanonicalization.td:380
*/
struct OrOfZero : public ::mlir::RewritePattern {
  OrOfZero(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("firrtl.or", 2, context, {"firrtl.asUInt", "firrtl.pad"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::IntegerAttr cst;
    ::circt::firrtl::ConstantOp zcst;
    ::mlir::Operation::operand_range x(op0->getOperands());
    ::circt::firrtl::OrPrimOp old;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::circt::firrtl::OrPrimOp>(op0); (void)castedOp0;
    old = castedOp0;
    x = castedOp0.getODSOperands(0);
    {
      auto *op1 = (*castedOp0.getODSOperands(1).begin()).getDefiningOp();
      if (!(op1)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "There's no operation that defines operand 1 of castedOp0";
        });
      }
      if(::mlir::failed(static_dag_matcher_5(rewriter, op1, tblgen_ops, cst, zcst))) {
        return ::mlir::failure();
      }
      tblgen_ops.push_back(op1);
    }
    if (!((
      type_isa<FIRRTLBaseType>((*x.begin()).getType()) &&
        !type_cast<FIRRTLBaseType>((*x.begin()).getType()).getRecursiveTypeProperties().hasUninferredWidth
      ))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'x' failed to satisfy constraint: ''";
      });
    }
    if (!((((*zcst.getODSResults(0).begin()).getDefiningOp<ConstantOp>() &&(*zcst.getODSResults(0).begin()).getDefiningOp<ConstantOp>().getValue().isZero())) || (((*zcst.getODSResults(0).begin()).getDefiningOp<SpecialConstantOp>() &&(*zcst.getODSResults(0).begin()).getDefiningOp<SpecialConstantOp>().getValue() == false)))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'zcst' failed to satisfy constraint: ''";
      });
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc(), tblgen_ops[1]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    auto nativeVar_0 = rewriter.getI32IntegerAttr(type_cast<FIRRTLBaseType>((*old.getODSResults(0).begin()).getType()).getBitWidthOrSentinel()); (void)nativeVar_0;
    ::circt::firrtl::PadPrimOp tblgen_PadPrimOp_1;
    {
      ::mlir::Value tblgen_value_0 = (*x.begin());
      tblgen_PadPrimOp_1 = ::circt::firrtl::PadPrimOp::create(rewriter, odsLoc,
        /*input=*/tblgen_value_0,
        /*amount=*/nativeVar_0
      );
    }
    ::circt::firrtl::AsUIntPrimOp tblgen_AsUIntPrimOp_2;
    {
      ::mlir::Value tblgen_value_0 = (*tblgen_PadPrimOp_1.getODSResults(0).begin());
      tblgen_AsUIntPrimOp_2 = ::circt::firrtl::AsUIntPrimOp::create(rewriter, odsLoc,
        /*input=*/tblgen_value_0
      );
    }
    auto nativeVar_3 = moveNameHint((*old.getODSResults(0).begin()), tblgen_AsUIntPrimOp_2); (void)nativeVar_3;

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ {nativeVar_3} }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    FIRRTLCanonicalization.td:405
*/
struct OrOrr : public ::mlir::RewritePattern {
  OrOrr(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("firrtl.or", 2, context, {"firrtl.asUInt", "firrtl.cat", "firrtl.orr"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range x(op0->getOperands());
    ::mlir::Operation::operand_range a(op0->getOperands());
    ::circt::firrtl::OrPrimOp old;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::circt::firrtl::OrPrimOp>(op0); (void)castedOp0;
    old = castedOp0;
    a = castedOp0.getODSOperands(0);
    {
      auto *op1 = (*castedOp0.getODSOperands(1).begin()).getDefiningOp();
      if (!(op1)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "There's no operation that defines operand 1 of castedOp0";
        });
      }
      auto castedOp1 = ::llvm::dyn_cast<::circt::firrtl::OrRPrimOp>(op1); (void)castedOp1;
      if (!(castedOp1)){
        return rewriter.notifyMatchFailure(op1, [&](::mlir::Diagnostic &diag) {
          diag << "castedOp1 is not ::circt::firrtl::OrRPrimOp type";
        });
      }
      x = castedOp1.getODSOperands(0);
      tblgen_ops.push_back(op1);
    }
    if (!((type_cast<IntType>((*a.begin()).getType()).getBitWidthOrSentinel() >= 0 &&type_cast<IntType>((*a.begin()).getType()).getBitWidthOrSentinel()< 2))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'a' failed to satisfy constraint: ''";
      });
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc(), tblgen_ops[1]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    ::circt::firrtl::AsUIntPrimOp tblgen_AsUIntPrimOp_1;
    {
      ::mlir::Value tblgen_value_0 = (*a.begin());
      tblgen_AsUIntPrimOp_1 = ::circt::firrtl::AsUIntPrimOp::create(rewriter, odsLoc,
        /*input=*/tblgen_value_0
      );
    }
    ::circt::firrtl::AsUIntPrimOp tblgen_AsUIntPrimOp_2;
    {
      ::mlir::Value tblgen_value_0 = (*x.begin());
      tblgen_AsUIntPrimOp_2 = ::circt::firrtl::AsUIntPrimOp::create(rewriter, odsLoc,
        /*input=*/tblgen_value_0
      );
    }
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_variadic_values_0;
    tblgen_variadic_values_0.push_back(tblgen_AsUIntPrimOp_1);
    tblgen_variadic_values_0.push_back(tblgen_AsUIntPrimOp_2);
    ::circt::firrtl::CatPrimOp tblgen_CatPrimOp_3;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values_0;
      for (auto v: tblgen_variadic_values_0) {
        tblgen_values_0.push_back(v);
      }
      tblgen_CatPrimOp_3 = ::circt::firrtl::CatPrimOp::create(rewriter, odsLoc,
        /*inputs=*/tblgen_values_0
      );
    }
    ::circt::firrtl::OrRPrimOp tblgen_OrRPrimOp_4;
    {
      ::mlir::Value tblgen_value_0 = (*tblgen_CatPrimOp_3.getODSResults(0).begin());
      tblgen_OrRPrimOp_4 = ::circt::firrtl::OrRPrimOp::create(rewriter, odsLoc,
        /*input=*/tblgen_value_0
      );
    }
    auto nativeVar_5 = moveNameHint((*old.getODSResults(0).begin()), tblgen_OrRPrimOp_4); (void)nativeVar_5;

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ {nativeVar_5} }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    FIRRTLCanonicalization.td:449
*/
struct OrRCatOrR_left : public ::mlir::RewritePattern {
  OrRCatOrR_left(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("firrtl.orr", 3, context, {"firrtl.asUInt", "firrtl.cat", "firrtl.orr"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range z(op0->getOperands());
    ::mlir::Operation::operand_range y(op0->getOperands());
    ::circt::firrtl::OrRPrimOp old;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::circt::firrtl::OrRPrimOp>(op0); (void)castedOp0;
    old = castedOp0;
    {
      auto *op1 = (*castedOp0.getODSOperands(0).begin()).getDefiningOp();
      if (!(op1)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "There's no operation that defines operand 0 of castedOp0";
        });
      }
      auto castedOp1 = ::llvm::dyn_cast<::circt::firrtl::CatPrimOp>(op1); (void)castedOp1;
      if (!(castedOp1)){
        return rewriter.notifyMatchFailure(op1, [&](::mlir::Diagnostic &diag) {
          diag << "castedOp1 is not ::circt::firrtl::CatPrimOp type";
        });
      }
      {
        auto variadic_operand_range = castedOp1.getODSOperands(0);
        if (variadic_operand_range.size() != 2) return ::mlir::failure();
        y = variadic_operand_range.slice(0, 1);
        {
          auto *local_op_1 = variadic_operand_range[1].getDefiningOp();
          if (!(local_op_1)){
            return rewriter.notifyMatchFailure(castedOp1, [&](::mlir::Diagnostic &diag) {
              diag << "There's no operation that defines variadic operand 0 (variadic sub-opearnd #1) of castedOp1";
            });
          }
          if(::mlir::failed(static_dag_matcher_14(rewriter, local_op_1, tblgen_ops, z))) {
            return ::mlir::failure();
          }
          tblgen_ops.push_back(local_op_1);
        }
      }
      tblgen_ops.push_back(op1);
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc(), tblgen_ops[1]->getLoc(), tblgen_ops[2]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    ::circt::firrtl::AsUIntPrimOp tblgen_AsUIntPrimOp_1;
    {
      ::mlir::Value tblgen_value_0 = (*z.begin());
      tblgen_AsUIntPrimOp_1 = ::circt::firrtl::AsUIntPrimOp::create(rewriter, odsLoc,
        /*input=*/tblgen_value_0
      );
    }
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_variadic_values_0;
    tblgen_variadic_values_0.push_back((*y.begin()));
    tblgen_variadic_values_0.push_back(tblgen_AsUIntPrimOp_1);
    ::circt::firrtl::CatPrimOp tblgen_CatPrimOp_2;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values_0;
      for (auto v: tblgen_variadic_values_0) {
        tblgen_values_0.push_back(v);
      }
      tblgen_CatPrimOp_2 = ::circt::firrtl::CatPrimOp::create(rewriter, odsLoc,
        /*inputs=*/tblgen_values_0
      );
    }
    ::circt::firrtl::OrRPrimOp tblgen_OrRPrimOp_3;
    {
      ::mlir::Value tblgen_value_0 = (*tblgen_CatPrimOp_2.getODSResults(0).begin());
      tblgen_OrRPrimOp_3 = ::circt::firrtl::OrRPrimOp::create(rewriter, odsLoc,
        /*input=*/tblgen_value_0
      );
    }
    auto nativeVar_4 = moveNameHint((*old.getODSResults(0).begin()), tblgen_OrRPrimOp_3); (void)nativeVar_4;

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ {nativeVar_4} }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    FIRRTLCanonicalization.td:455
*/
struct OrRCatOrR_right : public ::mlir::RewritePattern {
  OrRCatOrR_right(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("firrtl.orr", 3, context, {"firrtl.asUInt", "firrtl.cat", "firrtl.orr"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range y(op0->getOperands());
    ::mlir::Operation::operand_range z(op0->getOperands());
    ::circt::firrtl::OrRPrimOp old;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::circt::firrtl::OrRPrimOp>(op0); (void)castedOp0;
    old = castedOp0;
    {
      auto *op1 = (*castedOp0.getODSOperands(0).begin()).getDefiningOp();
      if (!(op1)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "There's no operation that defines operand 0 of castedOp0";
        });
      }
      auto castedOp1 = ::llvm::dyn_cast<::circt::firrtl::CatPrimOp>(op1); (void)castedOp1;
      if (!(castedOp1)){
        return rewriter.notifyMatchFailure(op1, [&](::mlir::Diagnostic &diag) {
          diag << "castedOp1 is not ::circt::firrtl::CatPrimOp type";
        });
      }
      {
        auto variadic_operand_range = castedOp1.getODSOperands(0);
        if (variadic_operand_range.size() != 2) return ::mlir::failure();
        {
          auto *local_op_0 = variadic_operand_range[0].getDefiningOp();
          if (!(local_op_0)){
            return rewriter.notifyMatchFailure(castedOp1, [&](::mlir::Diagnostic &diag) {
              diag << "There's no operation that defines variadic operand 0 (variadic sub-opearnd #0) of castedOp1";
            });
          }
          if(::mlir::failed(static_dag_matcher_14(rewriter, local_op_0, tblgen_ops, z))) {
            return ::mlir::failure();
          }
          tblgen_ops.push_back(local_op_0);
        }
        y = variadic_operand_range.slice(1, 1);
      }
      tblgen_ops.push_back(op1);
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc(), tblgen_ops[1]->getLoc(), tblgen_ops[2]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    ::circt::firrtl::AsUIntPrimOp tblgen_AsUIntPrimOp_1;
    {
      ::mlir::Value tblgen_value_0 = (*z.begin());
      tblgen_AsUIntPrimOp_1 = ::circt::firrtl::AsUIntPrimOp::create(rewriter, odsLoc,
        /*input=*/tblgen_value_0
      );
    }
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_variadic_values_0;
    tblgen_variadic_values_0.push_back(tblgen_AsUIntPrimOp_1);
    tblgen_variadic_values_0.push_back((*y.begin()));
    ::circt::firrtl::CatPrimOp tblgen_CatPrimOp_2;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values_0;
      for (auto v: tblgen_variadic_values_0) {
        tblgen_values_0.push_back(v);
      }
      tblgen_CatPrimOp_2 = ::circt::firrtl::CatPrimOp::create(rewriter, odsLoc,
        /*inputs=*/tblgen_values_0
      );
    }
    ::circt::firrtl::OrRPrimOp tblgen_OrRPrimOp_3;
    {
      ::mlir::Value tblgen_value_0 = (*tblgen_CatPrimOp_2.getODSResults(0).begin());
      tblgen_OrRPrimOp_3 = ::circt::firrtl::OrRPrimOp::create(rewriter, odsLoc,
        /*input=*/tblgen_value_0
      );
    }
    auto nativeVar_4 = moveNameHint((*old.getODSResults(0).begin()), tblgen_OrRPrimOp_3); (void)nativeVar_4;

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ {nativeVar_4} }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    FIRRTLCanonicalization.td:443
*/
struct OrRPadU : public ::mlir::RewritePattern {
  OrRPadU(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("firrtl.orr", 2, context, {"firrtl.orr"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::IntegerAttr n;
    ::mlir::Operation::operand_range x(op0->getOperands());
    ::circt::firrtl::PadPrimOp pad;
    ::circt::firrtl::OrRPrimOp old;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::circt::firrtl::OrRPrimOp>(op0); (void)castedOp0;
    old = castedOp0;
    {
      auto *op1 = (*castedOp0.getODSOperands(0).begin()).getDefiningOp();
      if (!(op1)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "There's no operation that defines operand 0 of castedOp0";
        });
      }
      if(::mlir::failed(static_dag_matcher_7(rewriter, op1, tblgen_ops, n, x, pad))) {
        return ::mlir::failure();
      }
      tblgen_ops.push_back(op1);
    }
    if (!((
      type_isa<FIRRTLBaseType>((*x.begin()).getType()) &&
        !type_cast<FIRRTLBaseType>((*x.begin()).getType()).getRecursiveTypeProperties().hasUninferredWidth
      ))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'x' failed to satisfy constraint: ''";
      });
    }
    if (!((type_isa<UIntType>((*x.begin()).getType())))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'x' failed to satisfy constraint: ''";
      });
    }
    if (!((type_cast<IntType>((*pad.getODSResults(0).begin()).getType()).getBitWidthOrSentinel() >= type_cast<IntType>((*x.begin()).getType()).getBitWidthOrSentinel()))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'pad, x' failed to satisfy constraint: ''";
      });
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc(), tblgen_ops[1]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    ::circt::firrtl::OrRPrimOp tblgen_OrRPrimOp_0;
    {
      ::mlir::Value tblgen_value_0 = (*x.begin());
      tblgen_OrRPrimOp_0 = ::circt::firrtl::OrRPrimOp::create(rewriter, odsLoc,
        /*input=*/tblgen_value_0
      );
    }
    auto nativeVar_1 = moveNameHint((*old.getODSResults(0).begin()), tblgen_OrRPrimOp_0); (void)nativeVar_1;

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ {nativeVar_1} }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    FIRRTLCanonicalization.td:431
*/
struct OrRasSInt : public ::mlir::RewritePattern {
  OrRasSInt(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("firrtl.orr", 2, context, {"firrtl.orr"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range x(op0->getOperands());
    ::circt::firrtl::OrRPrimOp old;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::circt::firrtl::OrRPrimOp>(op0); (void)castedOp0;
    old = castedOp0;
    {
      auto *op1 = (*castedOp0.getODSOperands(0).begin()).getDefiningOp();
      if (!(op1)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "There's no operation that defines operand 0 of castedOp0";
        });
      }
      if(::mlir::failed(static_dag_matcher_3(rewriter, op1, tblgen_ops, x))) {
        return ::mlir::failure();
      }
      tblgen_ops.push_back(op1);
    }
    if (!((
      type_isa<FIRRTLBaseType>((*x.begin()).getType()) &&
        !type_cast<FIRRTLBaseType>((*x.begin()).getType()).getRecursiveTypeProperties().hasUninferredWidth
      ))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'x' failed to satisfy constraint: ''";
      });
    }
    if (!((type_isa<IntType>((*x.begin()).getType())))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'x' failed to satisfy constraint: ''";
      });
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc(), tblgen_ops[1]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    ::circt::firrtl::OrRPrimOp tblgen_OrRPrimOp_0;
    {
      ::mlir::Value tblgen_value_0 = (*x.begin());
      tblgen_OrRPrimOp_0 = ::circt::firrtl::OrRPrimOp::create(rewriter, odsLoc,
        /*input=*/tblgen_value_0
      );
    }
    auto nativeVar_1 = moveNameHint((*old.getODSResults(0).begin()), tblgen_OrRPrimOp_0); (void)nativeVar_1;

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ {nativeVar_1} }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    FIRRTLCanonicalization.td:437
*/
struct OrRasUInt : public ::mlir::RewritePattern {
  OrRasUInt(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("firrtl.orr", 2, context, {"firrtl.orr"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range x(op0->getOperands());
    ::circt::firrtl::OrRPrimOp old;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::circt::firrtl::OrRPrimOp>(op0); (void)castedOp0;
    old = castedOp0;
    {
      auto *op1 = (*castedOp0.getODSOperands(0).begin()).getDefiningOp();
      if (!(op1)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "There's no operation that defines operand 0 of castedOp0";
        });
      }
      if(::mlir::failed(static_dag_matcher_9(rewriter, op1, tblgen_ops, x))) {
        return ::mlir::failure();
      }
      tblgen_ops.push_back(op1);
    }
    if (!((
      type_isa<FIRRTLBaseType>((*x.begin()).getType()) &&
        !type_cast<FIRRTLBaseType>((*x.begin()).getType()).getRecursiveTypeProperties().hasUninferredWidth
      ))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'x' failed to satisfy constraint: ''";
      });
    }
    if (!((type_isa<IntType>((*x.begin()).getType())))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'x' failed to satisfy constraint: ''";
      });
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc(), tblgen_ops[1]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    ::circt::firrtl::OrRPrimOp tblgen_OrRPrimOp_0;
    {
      ::mlir::Value tblgen_value_0 = (*x.begin());
      tblgen_OrRPrimOp_0 = ::circt::firrtl::OrRPrimOp::create(rewriter, odsLoc,
        /*input=*/tblgen_value_0
      );
    }
    auto nativeVar_1 = moveNameHint((*old.getODSResults(0).begin()), tblgen_OrRPrimOp_0); (void)nativeVar_1;

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ {nativeVar_1} }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    FIRRTLCanonicalization.td:671
*/
struct RefResolveOfRefSend : public ::mlir::RewritePattern {
  RefResolveOfRefSend(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("firrtl.ref.resolve", 2, context, {}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range base(op0->getOperands());
    ::circt::firrtl::RefResolveOp resolve;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::circt::firrtl::RefResolveOp>(op0); (void)castedOp0;
    resolve = castedOp0;
    {
      auto *op1 = (*castedOp0.getODSOperands(0).begin()).getDefiningOp();
      if (!(op1)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "There's no operation that defines operand 0 of castedOp0";
        });
      }
      auto castedOp1 = ::llvm::dyn_cast<::circt::firrtl::RefSendOp>(op1); (void)castedOp1;
      if (!(castedOp1)){
        return rewriter.notifyMatchFailure(op1, [&](::mlir::Diagnostic &diag) {
          diag << "castedOp1 is not ::circt::firrtl::RefSendOp type";
        });
      }
      base = castedOp1.getODSOperands(0);
      tblgen_ops.push_back(op1);
    }
    if (!((areAnonymousTypesEquivalent((*base.begin()).getType(), (*resolve.getODSResults(0).begin()).getType())))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'base, resolve' failed to satisfy constraint: ''";
      });
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc(), tblgen_ops[1]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ base }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    FIRRTLCanonicalization.td:666
*/
struct RegResetWithZeroReset : public ::mlir::RewritePattern {
  RegResetWithZeroReset(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("firrtl.regreset", 1, context, {"firrtl.reg"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::UnitAttr forceable;
    ::circt::hw::InnerSymAttr inner_sym;
    ::circt::firrtl::NameKindEnumAttr nameKind;
    ::mlir::ArrayAttr annotations;
    ::mlir::StringAttr name;
    ::mlir::Operation::operand_range reset(op0->getOperands());
    ::mlir::Operation::operand_range clock(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::circt::firrtl::RegResetOp>(op0); (void)castedOp0;
    clock = castedOp0.getODSOperands(0);
    reset = castedOp0.getODSOperands(1);
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getName();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'firrtl.regreset' to have attribute 'name' of type '::mlir::StringAttr'";
        });
      }
      name = tblgen_attr;
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getNameKind();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'firrtl.regreset' to have attribute 'nameKind' of type '::circt::firrtl::NameKindEnumAttr'";
        });
      }
      nameKind = tblgen_attr;
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getAnnotations();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'firrtl.regreset' to have attribute 'annotations' of type '::mlir::ArrayAttr'";
        });
      }
      annotations = tblgen_attr;
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getInnerSym();
      inner_sym = tblgen_attr;
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getForceable();
      if (!tblgen_attr) tblgen_attr = ((false) ? rewriter.getUnitAttr() : nullptr);
      forceable = tblgen_attr;
    }
    if (!((((*reset.begin()).getDefiningOp<ConstantOp>() &&(*reset.begin()).getDefiningOp<ConstantOp>().getValue().isZero())) || (((*reset.begin()).getDefiningOp<SpecialConstantOp>() &&(*reset.begin()).getDefiningOp<SpecialConstantOp>().getValue() == false)))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'reset' failed to satisfy constraint: ''";
      });
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    ::circt::firrtl::RegOp tblgen_RegOp_0;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::circt::firrtl::RegOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*clock.begin()));
      tblgen_props.name = ::llvm::dyn_cast_if_present<decltype(tblgen_props.name)>(name);
      tblgen_props.nameKind = ::llvm::dyn_cast_if_present<decltype(tblgen_props.nameKind)>(nameKind);
      tblgen_props.annotations = ::llvm::dyn_cast_if_present<decltype(tblgen_props.annotations)>(annotations);
      tblgen_props.inner_sym = ::llvm::dyn_cast_if_present<decltype(tblgen_props.inner_sym)>(inner_sym);
      tblgen_props.forceable = ::llvm::dyn_cast_if_present<decltype(tblgen_props.forceable)>(forceable);
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      for (auto v: castedOp0.getODSResults(1)) {
        tblgen_types.push_back(v.getType());
      }
      tblgen_RegOp_0 = ::circt::firrtl::RegOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ tblgen_RegOp_0.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ tblgen_RegOp_0.getODSResults(1) }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    FIRRTLCanonicalization.td:681
*/
struct StoUtoS : public ::mlir::RewritePattern {
  StoUtoS(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("firrtl.asUInt", 2, context, {}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range x(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::circt::firrtl::AsUIntPrimOp>(op0); (void)castedOp0;
    {
      auto *op1 = (*castedOp0.getODSOperands(0).begin()).getDefiningOp();
      if (!(op1)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "There's no operation that defines operand 0 of castedOp0";
        });
      }
      if(::mlir::failed(static_dag_matcher_3(rewriter, op1, tblgen_ops, x))) {
        return ::mlir::failure();
      }
      tblgen_ops.push_back(op1);
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc(), tblgen_ops[1]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ x }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    FIRRTLCanonicalization.td:314
*/
struct SubFromZeroSigned : public ::mlir::RewritePattern {
  SubFromZeroSigned(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("firrtl.sub", 2, context, {"firrtl.neg", "firrtl.pad"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range x(op0->getOperands());
    ::mlir::IntegerAttr cst;
    ::circt::firrtl::ConstantOp zcst;
    ::circt::firrtl::SubPrimOp old;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    if(::mlir::failed(static_dag_matcher_15(rewriter, op0, tblgen_ops, x, cst, zcst, old))) {
      return ::mlir::failure();
    }
    auto castedOp0 = ::llvm::dyn_cast_or_null<::circt::firrtl::SubPrimOp>(op0); (void)castedOp0;
    if (!((
      type_isa<FIRRTLBaseType>((*x.begin()).getType()) &&
        !type_cast<FIRRTLBaseType>((*x.begin()).getType()).getRecursiveTypeProperties().hasUninferredWidth
      ))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'x' failed to satisfy constraint: ''";
      });
    }
    if (!((((*zcst.getODSResults(0).begin()).getDefiningOp<ConstantOp>() &&(*zcst.getODSResults(0).begin()).getDefiningOp<ConstantOp>().getValue().isZero())) || (((*zcst.getODSResults(0).begin()).getDefiningOp<SpecialConstantOp>() &&(*zcst.getODSResults(0).begin()).getDefiningOp<SpecialConstantOp>().getValue() == false)))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'zcst' failed to satisfy constraint: ''";
      });
    }
    if (!((type_isa<SIntType>(((*x.begin()).getType()))))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "value entity 'x' failed to satisfy constraint: 'sint type'";
      });
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc(), tblgen_ops[1]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    ::circt::firrtl::NegPrimOp tblgen_NegPrimOp_0;
    {
      ::mlir::Value tblgen_value_0 = (*x.begin());
      tblgen_NegPrimOp_0 = ::circt::firrtl::NegPrimOp::create(rewriter, odsLoc,
        /*input=*/tblgen_value_0
      );
    }
    auto nativeVar_1 = moveNameHint((*old.getODSResults(0).begin()), tblgen_NegPrimOp_0); (void)nativeVar_1;
    auto nativeVar_2 = rewriter.getI32IntegerAttr(type_cast<FIRRTLBaseType>((*old.getODSResults(0).begin()).getType()).getBitWidthOrSentinel()); (void)nativeVar_2;
    ::circt::firrtl::PadPrimOp tblgen_PadPrimOp_3;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::circt::firrtl::PadPrimOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back(nativeVar_1);
      tblgen_props.amount = ::llvm::dyn_cast_if_present<decltype(tblgen_props.amount)>(nativeVar_2);
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      tblgen_PadPrimOp_3 = ::circt::firrtl::PadPrimOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ tblgen_PadPrimOp_3.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    FIRRTLCanonicalization.td:320
*/
struct SubFromZeroUnsigned : public ::mlir::RewritePattern {
  SubFromZeroUnsigned(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("firrtl.sub", 2, context, {"firrtl.asUInt", "firrtl.neg", "firrtl.pad"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range x(op0->getOperands());
    ::mlir::IntegerAttr cst;
    ::circt::firrtl::ConstantOp zcst;
    ::circt::firrtl::SubPrimOp old;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    if(::mlir::failed(static_dag_matcher_15(rewriter, op0, tblgen_ops, x, cst, zcst, old))) {
      return ::mlir::failure();
    }
    auto castedOp0 = ::llvm::dyn_cast_or_null<::circt::firrtl::SubPrimOp>(op0); (void)castedOp0;
    if (!((
      type_isa<FIRRTLBaseType>((*x.begin()).getType()) &&
        !type_cast<FIRRTLBaseType>((*x.begin()).getType()).getRecursiveTypeProperties().hasUninferredWidth
      ))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'x' failed to satisfy constraint: ''";
      });
    }
    if (!((((*zcst.getODSResults(0).begin()).getDefiningOp<ConstantOp>() &&(*zcst.getODSResults(0).begin()).getDefiningOp<ConstantOp>().getValue().isZero())) || (((*zcst.getODSResults(0).begin()).getDefiningOp<SpecialConstantOp>() &&(*zcst.getODSResults(0).begin()).getDefiningOp<SpecialConstantOp>().getValue() == false)))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'zcst' failed to satisfy constraint: ''";
      });
    }
    if (!((type_isa<UIntType>(((*x.begin()).getType()))))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "value entity 'x' failed to satisfy constraint: 'uint type'";
      });
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc(), tblgen_ops[1]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    ::circt::firrtl::NegPrimOp tblgen_NegPrimOp_0;
    {
      ::mlir::Value tblgen_value_0 = (*x.begin());
      tblgen_NegPrimOp_0 = ::circt::firrtl::NegPrimOp::create(rewriter, odsLoc,
        /*input=*/tblgen_value_0
      );
    }
    auto nativeVar_1 = moveNameHint((*old.getODSResults(0).begin()), tblgen_NegPrimOp_0); (void)nativeVar_1;
    auto nativeVar_2 = rewriter.getI32IntegerAttr(type_cast<FIRRTLBaseType>((*old.getODSResults(0).begin()).getType()).getBitWidthOrSentinel()); (void)nativeVar_2;
    ::circt::firrtl::PadPrimOp tblgen_PadPrimOp_3;
    {
      ::mlir::Value tblgen_value_0 = nativeVar_1;
      tblgen_PadPrimOp_3 = ::circt::firrtl::PadPrimOp::create(rewriter, odsLoc,
        /*input=*/tblgen_value_0,
        /*amount=*/nativeVar_2
      );
    }
    ::circt::firrtl::AsUIntPrimOp tblgen_AsUIntPrimOp_4;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values; (void)tblgen_values;
      ::circt::firrtl::AsUIntPrimOp::Properties tblgen_props; (void)tblgen_props;
      tblgen_values.push_back((*tblgen_PadPrimOp_3.getODSResults(0).begin()));
      ::llvm::SmallVector<::mlir::Type, 4> tblgen_types; (void)tblgen_types;
      for (auto v: castedOp0.getODSResults(0)) {
        tblgen_types.push_back(v.getType());
      }
      tblgen_AsUIntPrimOp_4 = ::circt::firrtl::AsUIntPrimOp::create(rewriter, odsLoc, tblgen_types, tblgen_values, tblgen_props);
    }

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ tblgen_AsUIntPrimOp_4.getODSResults(0) }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    FIRRTLCanonicalization.td:332
*/
struct SubOfPadL : public ::mlir::RewritePattern {
  SubOfPadL(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("firrtl.sub", 2, context, {"firrtl.pad", "firrtl.sub"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::IntegerAttr m;
    ::mlir::Operation::operand_range a(op0->getOperands());
    ::mlir::Operation::operand_range b(op0->getOperands());
    ::circt::firrtl::SubPrimOp old;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::circt::firrtl::SubPrimOp>(op0); (void)castedOp0;
    old = castedOp0;
    {
      auto *op1 = (*castedOp0.getODSOperands(0).begin()).getDefiningOp();
      if (!(op1)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "There's no operation that defines operand 0 of castedOp0";
        });
      }
      if(::mlir::failed(static_dag_matcher_0(rewriter, op1, tblgen_ops, m, a))) {
        return ::mlir::failure();
      }
      tblgen_ops.push_back(op1);
    }
    b = castedOp0.getODSOperands(1);
    if (!((
      type_isa<FIRRTLBaseType>((*a.begin()).getType()) &&
        !type_cast<FIRRTLBaseType>((*a.begin()).getType()).getRecursiveTypeProperties().hasUninferredWidth
      ))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'a' failed to satisfy constraint: ''";
      });
    }
    if (!((
      type_isa<FIRRTLBaseType>((*b.begin()).getType()) &&
        !type_cast<FIRRTLBaseType>((*b.begin()).getType()).getRecursiveTypeProperties().hasUninferredWidth
      ))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'b' failed to satisfy constraint: ''";
      });
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc(), tblgen_ops[1]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    ::circt::firrtl::SubPrimOp tblgen_SubPrimOp_0;
    {
      ::mlir::Value tblgen_value_0 = (*a.begin());
      ::mlir::Value tblgen_value_1 = (*b.begin());
      tblgen_SubPrimOp_0 = ::circt::firrtl::SubPrimOp::create(rewriter, odsLoc,
        /*lhs=*/tblgen_value_0,
        /*rhs=*/tblgen_value_1
      );
    }
    auto nativeVar_1 = rewriter.getI32IntegerAttr(type_cast<FIRRTLBaseType>((*old.getODSResults(0).begin()).getType()).getBitWidthOrSentinel()); (void)nativeVar_1;
    ::circt::firrtl::PadPrimOp tblgen_PadPrimOp_2;
    {
      ::mlir::Value tblgen_value_0 = (*tblgen_SubPrimOp_0.getODSResults(0).begin());
      tblgen_PadPrimOp_2 = ::circt::firrtl::PadPrimOp::create(rewriter, odsLoc,
        /*input=*/tblgen_value_0,
        /*amount=*/nativeVar_1
      );
    }
    auto nativeVar_3 = moveNameHint((*old.getODSResults(0).begin()), tblgen_PadPrimOp_2); (void)nativeVar_3;

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ {nativeVar_3} }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    FIRRTLCanonicalization.td:338
*/
struct SubOfPadR : public ::mlir::RewritePattern {
  SubOfPadR(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("firrtl.sub", 2, context, {"firrtl.pad", "firrtl.sub"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::IntegerAttr m;
    ::mlir::Operation::operand_range a(op0->getOperands());
    ::mlir::Operation::operand_range b(op0->getOperands());
    ::circt::firrtl::SubPrimOp old;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::circt::firrtl::SubPrimOp>(op0); (void)castedOp0;
    old = castedOp0;
    b = castedOp0.getODSOperands(0);
    {
      auto *op1 = (*castedOp0.getODSOperands(1).begin()).getDefiningOp();
      if (!(op1)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "There's no operation that defines operand 1 of castedOp0";
        });
      }
      if(::mlir::failed(static_dag_matcher_0(rewriter, op1, tblgen_ops, m, a))) {
        return ::mlir::failure();
      }
      tblgen_ops.push_back(op1);
    }
    if (!((
      type_isa<FIRRTLBaseType>((*a.begin()).getType()) &&
        !type_cast<FIRRTLBaseType>((*a.begin()).getType()).getRecursiveTypeProperties().hasUninferredWidth
      ))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'a' failed to satisfy constraint: ''";
      });
    }
    if (!((
      type_isa<FIRRTLBaseType>((*b.begin()).getType()) &&
        !type_cast<FIRRTLBaseType>((*b.begin()).getType()).getRecursiveTypeProperties().hasUninferredWidth
      ))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'b' failed to satisfy constraint: ''";
      });
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc(), tblgen_ops[1]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    ::circt::firrtl::SubPrimOp tblgen_SubPrimOp_0;
    {
      ::mlir::Value tblgen_value_0 = (*b.begin());
      ::mlir::Value tblgen_value_1 = (*a.begin());
      tblgen_SubPrimOp_0 = ::circt::firrtl::SubPrimOp::create(rewriter, odsLoc,
        /*lhs=*/tblgen_value_0,
        /*rhs=*/tblgen_value_1
      );
    }
    auto nativeVar_1 = rewriter.getI32IntegerAttr(type_cast<FIRRTLBaseType>((*old.getODSResults(0).begin()).getType()).getBitWidthOrSentinel()); (void)nativeVar_1;
    ::circt::firrtl::PadPrimOp tblgen_PadPrimOp_2;
    {
      ::mlir::Value tblgen_value_0 = (*tblgen_SubPrimOp_0.getODSResults(0).begin());
      tblgen_PadPrimOp_2 = ::circt::firrtl::PadPrimOp::create(rewriter, odsLoc,
        /*input=*/tblgen_value_0,
        /*amount=*/nativeVar_1
      );
    }
    auto nativeVar_3 = moveNameHint((*old.getODSResults(0).begin()), tblgen_PadPrimOp_2); (void)nativeVar_3;

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ {nativeVar_3} }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    FIRRTLCanonicalization.td:326
*/
struct SubOfSelf : public ::mlir::RewritePattern {
  SubOfSelf(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("firrtl.sub", 1, context, {}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range x(op0->getOperands());
    ::mlir::Operation::operand_range x0(op0->getOperands());
    ::circt::firrtl::SubPrimOp old;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::circt::firrtl::SubPrimOp>(op0); (void)castedOp0;
    old = castedOp0;
    x0 = castedOp0.getODSOperands(0);
    x = castedOp0.getODSOperands(1);
    if (!(*x.begin() == *x0.begin())){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "Operands 'x' and 'x0' must be equal";
      });
    }
    if (!((
      type_isa<FIRRTLBaseType>((*x.begin()).getType()) &&
        !type_cast<FIRRTLBaseType>((*x.begin()).getType()).getRecursiveTypeProperties().hasUninferredWidth
      ))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'x' failed to satisfy constraint: ''";
      });
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    auto nativeVar_0 = ConstantOp::create(rewriter, (*old.getODSResults(0).begin()).getLoc(), type_cast<IntType>((*old.getODSResults(0).begin()).getType()), getIntZerosAttr((*old.getODSResults(0).begin()).getType())); (void)nativeVar_0;

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ {nativeVar_0} }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    FIRRTLCanonicalization.td:308
*/
struct SubOfZero : public ::mlir::RewritePattern {
  SubOfZero(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("firrtl.sub", 2, context, {"firrtl.pad"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::IntegerAttr cst;
    ::circt::firrtl::ConstantOp zcst;
    ::mlir::Operation::operand_range x(op0->getOperands());
    ::circt::firrtl::SubPrimOp old;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::circt::firrtl::SubPrimOp>(op0); (void)castedOp0;
    old = castedOp0;
    x = castedOp0.getODSOperands(0);
    {
      auto *op1 = (*castedOp0.getODSOperands(1).begin()).getDefiningOp();
      if (!(op1)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "There's no operation that defines operand 1 of castedOp0";
        });
      }
      if(::mlir::failed(static_dag_matcher_5(rewriter, op1, tblgen_ops, cst, zcst))) {
        return ::mlir::failure();
      }
      tblgen_ops.push_back(op1);
    }
    if (!((
      type_isa<FIRRTLBaseType>((*x.begin()).getType()) &&
        !type_cast<FIRRTLBaseType>((*x.begin()).getType()).getRecursiveTypeProperties().hasUninferredWidth
      ))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'x' failed to satisfy constraint: ''";
      });
    }
    if (!((((*zcst.getODSResults(0).begin()).getDefiningOp<ConstantOp>() &&(*zcst.getODSResults(0).begin()).getDefiningOp<ConstantOp>().getValue().isZero())) || (((*zcst.getODSResults(0).begin()).getDefiningOp<SpecialConstantOp>() &&(*zcst.getODSResults(0).begin()).getDefiningOp<SpecialConstantOp>().getValue() == false)))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'zcst' failed to satisfy constraint: ''";
      });
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc(), tblgen_ops[1]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    auto nativeVar_0 = rewriter.getI32IntegerAttr(type_cast<FIRRTLBaseType>((*old.getODSResults(0).begin()).getType()).getBitWidthOrSentinel()); (void)nativeVar_0;
    ::circt::firrtl::PadPrimOp tblgen_PadPrimOp_1;
    {
      ::mlir::Value tblgen_value_0 = (*x.begin());
      tblgen_PadPrimOp_1 = ::circt::firrtl::PadPrimOp::create(rewriter, odsLoc,
        /*input=*/tblgen_value_0,
        /*amount=*/nativeVar_0
      );
    }
    auto nativeVar_2 = moveNameHint((*old.getODSResults(0).begin()), tblgen_PadPrimOp_1); (void)nativeVar_2;

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ {nativeVar_2} }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    FIRRTLCanonicalization.td:564
*/
struct SubaccessOfConstant : public ::mlir::RewritePattern {
  SubaccessOfConstant(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("firrtl.subaccess", 2, context, {"firrtl.subindex"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::IntegerAttr cst;
    ::mlir::Operation::operand_range array(op0->getOperands());
    ::circt::firrtl::SubaccessOp old;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::circt::firrtl::SubaccessOp>(op0); (void)castedOp0;
    old = castedOp0;
    array = castedOp0.getODSOperands(0);
    {
      auto *op1 = (*castedOp0.getODSOperands(1).begin()).getDefiningOp();
      if (!(op1)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "There's no operation that defines operand 1 of castedOp0";
        });
      }
      if(::mlir::failed(static_dag_matcher_11(rewriter, op1, tblgen_ops, cst))) {
        return ::mlir::failure();
      }
      tblgen_ops.push_back(op1);
    }
    if (!((cast<IntegerAttr>(cst).getAPSInt().getExtValue() < static_cast<int64_t>(type_cast<FVectorType>((*array.begin()).getType()).getNumElements())))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'cst, array' failed to satisfy constraint: ''";
      });
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc(), tblgen_ops[1]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    auto nativeVar_0 = rewriter.getI32IntegerAttr(cast<IntegerAttr>(cst).getAPSInt().getExtValue()); (void)nativeVar_0;
    ::circt::firrtl::SubindexOp tblgen_SubindexOp_1;
    {
      ::mlir::Value tblgen_value_0 = (*array.begin());
      tblgen_SubindexOp_1 = ::circt::firrtl::SubindexOp::create(rewriter, odsLoc,
        /*input=*/tblgen_value_0,
        /*index=*/nativeVar_0
      );
    }
    auto nativeVar_2 = moveNameHint((*old.getODSResults(0).begin()), tblgen_SubindexOp_1); (void)nativeVar_2;

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ {nativeVar_2} }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    FIRRTLCanonicalization.td:703
*/
struct UnclockedAssumeIntrinsicXWhenX : public ::mlir::RewritePattern {
  UnclockedAssumeIntrinsicXWhenX(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("firrtl.int.unclocked_assume", 1, context, {}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range x(op0->getOperands());
    ::mlir::Operation::operand_range x0(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::circt::firrtl::UnclockedAssumeIntrinsicOp>(op0); (void)castedOp0;
    x0 = castedOp0.getODSOperands(0);
    x = castedOp0.getODSOperands(1);
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getMessage();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'firrtl.int.unclocked_assume' to have attribute 'message' of type '::mlir::StringAttr'";
        });
      }
    }
    {
      [[maybe_unused]] auto tblgen_attr = castedOp0.getProperties().getName();
      if (!(tblgen_attr)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "expected op 'firrtl.int.unclocked_assume' to have attribute 'name' of type '::mlir::StringAttr'";
        });
      }
    }
    if (!(*x.begin() == *x0.begin())){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "Operands 'x' and 'x0' must be equal";
      });
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    rewriter.eraseOp(op0);
    return ::mlir::success();
  }
};

/* Generated from:
    FIRRTLCanonicalization.td:676
*/
struct UtoStoU : public ::mlir::RewritePattern {
  UtoStoU(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("firrtl.asSInt", 2, context, {}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range x(op0->getOperands());
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::circt::firrtl::AsSIntPrimOp>(op0); (void)castedOp0;
    {
      auto *op1 = (*castedOp0.getODSOperands(0).begin()).getDefiningOp();
      if (!(op1)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "There's no operation that defines operand 0 of castedOp0";
        });
      }
      if(::mlir::failed(static_dag_matcher_9(rewriter, op1, tblgen_ops, x))) {
        return ::mlir::failure();
      }
      tblgen_ops.push_back(op1);
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc(), tblgen_ops[1]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ x }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    FIRRTLCanonicalization.td:424
*/
struct XorOfPad : public ::mlir::RewritePattern {
  XorOfPad(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("firrtl.xor", 2, context, {"firrtl.cat", "firrtl.head", "firrtl.tail", "firrtl.xor"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::IntegerAttr n;
    ::mlir::Operation::operand_range y(op0->getOperands());
    ::circt::firrtl::PadPrimOp pad;
    ::mlir::Operation::operand_range x(op0->getOperands());
    ::circt::firrtl::XorPrimOp old;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::circt::firrtl::XorPrimOp>(op0); (void)castedOp0;
    old = castedOp0;
    x = castedOp0.getODSOperands(0);
    {
      auto *op1 = (*castedOp0.getODSOperands(1).begin()).getDefiningOp();
      if (!(op1)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "There's no operation that defines operand 1 of castedOp0";
        });
      }
      if(::mlir::failed(static_dag_matcher_4(rewriter, op1, tblgen_ops, n, y, pad))) {
        return ::mlir::failure();
      }
      tblgen_ops.push_back(op1);
    }
    if (!((
      type_isa<FIRRTLBaseType>((*x.begin()).getType()) &&
        !type_cast<FIRRTLBaseType>((*x.begin()).getType()).getRecursiveTypeProperties().hasUninferredWidth
      ))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'x' failed to satisfy constraint: ''";
      });
    }
    if (!((type_isa<UIntType>(((*x.begin()).getType()))))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "value entity 'x' failed to satisfy constraint: 'uint type'";
      });
    }
    if (!((areAnonymousTypesEquivalent((*x.begin()).getType(), (*pad.getODSResults(0).begin()).getType())))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'x, pad' failed to satisfy constraint: ''";
      });
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc(), tblgen_ops[1]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    auto nativeVar_1 = rewriter.getI32IntegerAttr(type_cast<FIRRTLBaseType>((*x.begin()).getType()).getBitWidthOrSentinel() - type_cast<FIRRTLBaseType>((*y.begin()).getType()).getBitWidthOrSentinel()); (void)nativeVar_1;
    ::circt::firrtl::HeadPrimOp tblgen_HeadPrimOp_2;
    {
      ::mlir::Value tblgen_value_0 = (*x.begin());
      tblgen_HeadPrimOp_2 = ::circt::firrtl::HeadPrimOp::create(rewriter, odsLoc,
        /*input=*/tblgen_value_0,
        /*amount=*/nativeVar_1
      );
    }
    auto nativeVar_3 = rewriter.getI32IntegerAttr(type_cast<FIRRTLBaseType>((*x.begin()).getType()).getBitWidthOrSentinel() - type_cast<FIRRTLBaseType>((*y.begin()).getType()).getBitWidthOrSentinel()); (void)nativeVar_3;
    ::circt::firrtl::TailPrimOp tblgen_TailPrimOp_4;
    {
      ::mlir::Value tblgen_value_0 = (*x.begin());
      tblgen_TailPrimOp_4 = ::circt::firrtl::TailPrimOp::create(rewriter, odsLoc,
        /*input=*/tblgen_value_0,
        /*amount=*/nativeVar_3
      );
    }
    ::circt::firrtl::XorPrimOp tblgen_XorPrimOp_5;
    {
      ::mlir::Value tblgen_value_0 = (*tblgen_TailPrimOp_4.getODSResults(0).begin());
      ::mlir::Value tblgen_value_1 = (*y.begin());
      tblgen_XorPrimOp_5 = ::circt::firrtl::XorPrimOp::create(rewriter, odsLoc,
        /*lhs=*/tblgen_value_0,
        /*rhs=*/tblgen_value_1
      );
    }
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_variadic_values_0;
    tblgen_variadic_values_0.push_back(tblgen_HeadPrimOp_2);
    tblgen_variadic_values_0.push_back(tblgen_XorPrimOp_5);
    ::circt::firrtl::CatPrimOp tblgen_CatPrimOp_6;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values_0;
      for (auto v: tblgen_variadic_values_0) {
        tblgen_values_0.push_back(v);
      }
      tblgen_CatPrimOp_6 = ::circt::firrtl::CatPrimOp::create(rewriter, odsLoc,
        /*inputs=*/tblgen_values_0
      );
    }
    auto nativeVar_7 = moveNameHint((*old.getODSResults(0).begin()), tblgen_CatPrimOp_6); (void)nativeVar_7;

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ {nativeVar_7} }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    FIRRTLCanonicalization.td:418
*/
struct XorOfSelf : public ::mlir::RewritePattern {
  XorOfSelf(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("firrtl.xor", 1, context, {}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range x(op0->getOperands());
    ::mlir::Operation::operand_range x0(op0->getOperands());
    ::circt::firrtl::XorPrimOp old;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::circt::firrtl::XorPrimOp>(op0); (void)castedOp0;
    old = castedOp0;
    x0 = castedOp0.getODSOperands(0);
    x = castedOp0.getODSOperands(1);
    if (!(*x.begin() == *x0.begin())){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "Operands 'x' and 'x0' must be equal";
      });
    }
    if (!((
      type_isa<FIRRTLBaseType>((*x.begin()).getType()) &&
        !type_cast<FIRRTLBaseType>((*x.begin()).getType()).getRecursiveTypeProperties().hasUninferredWidth
      ))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'x' failed to satisfy constraint: ''";
      });
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    auto nativeVar_0 = ConstantOp::create(rewriter, (*old.getODSResults(0).begin()).getLoc(), type_cast<IntType>((*old.getODSResults(0).begin()).getType()), getIntZerosAttr((*old.getODSResults(0).begin()).getType())); (void)nativeVar_0;

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ {nativeVar_0} }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    FIRRTLCanonicalization.td:412
*/
struct XorOfZero : public ::mlir::RewritePattern {
  XorOfZero(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("firrtl.xor", 2, context, {"firrtl.asUInt", "firrtl.pad"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::circt::firrtl::ConstantOp zcst;
    ::mlir::Operation::operand_range x(op0->getOperands());
    ::circt::firrtl::XorPrimOp old;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::circt::firrtl::XorPrimOp>(op0); (void)castedOp0;
    old = castedOp0;
    x = castedOp0.getODSOperands(0);
    {
      auto *op1 = (*castedOp0.getODSOperands(1).begin()).getDefiningOp();
      if (!(op1)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "There's no operation that defines operand 1 of castedOp0";
        });
      }
      if(::mlir::failed(static_dag_matcher_1(rewriter, op1, tblgen_ops, zcst))) {
        return ::mlir::failure();
      }
      tblgen_ops.push_back(op1);
    }
    if (!((
      type_isa<FIRRTLBaseType>((*x.begin()).getType()) &&
        !type_cast<FIRRTLBaseType>((*x.begin()).getType()).getRecursiveTypeProperties().hasUninferredWidth
      ))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'x' failed to satisfy constraint: ''";
      });
    }
    if (!((((*zcst.getODSResults(0).begin()).getDefiningOp<ConstantOp>() &&(*zcst.getODSResults(0).begin()).getDefiningOp<ConstantOp>().getValue().isZero())) || (((*zcst.getODSResults(0).begin()).getDefiningOp<SpecialConstantOp>() &&(*zcst.getODSResults(0).begin()).getDefiningOp<SpecialConstantOp>().getValue() == false)))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'zcst' failed to satisfy constraint: ''";
      });
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc(), tblgen_ops[1]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    auto nativeVar_0 = rewriter.getI32IntegerAttr(type_cast<FIRRTLBaseType>((*old.getODSResults(0).begin()).getType()).getBitWidthOrSentinel()); (void)nativeVar_0;
    ::circt::firrtl::PadPrimOp tblgen_PadPrimOp_1;
    {
      ::mlir::Value tblgen_value_0 = (*x.begin());
      tblgen_PadPrimOp_1 = ::circt::firrtl::PadPrimOp::create(rewriter, odsLoc,
        /*input=*/tblgen_value_0,
        /*amount=*/nativeVar_0
      );
    }
    ::circt::firrtl::AsUIntPrimOp tblgen_AsUIntPrimOp_2;
    {
      ::mlir::Value tblgen_value_0 = (*tblgen_PadPrimOp_1.getODSResults(0).begin());
      tblgen_AsUIntPrimOp_2 = ::circt::firrtl::AsUIntPrimOp::create(rewriter, odsLoc,
        /*input=*/tblgen_value_0
      );
    }
    auto nativeVar_3 = moveNameHint((*old.getODSResults(0).begin()), tblgen_AsUIntPrimOp_2); (void)nativeVar_3;

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ {nativeVar_3} }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    FIRRTLCanonicalization.td:479
*/
struct XorRCatXorR_left : public ::mlir::RewritePattern {
  XorRCatXorR_left(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("firrtl.xorr", 3, context, {"firrtl.asUInt", "firrtl.cat", "firrtl.xorr"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range z(op0->getOperands());
    ::mlir::Operation::operand_range y(op0->getOperands());
    ::circt::firrtl::XorRPrimOp old;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::circt::firrtl::XorRPrimOp>(op0); (void)castedOp0;
    old = castedOp0;
    {
      auto *op1 = (*castedOp0.getODSOperands(0).begin()).getDefiningOp();
      if (!(op1)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "There's no operation that defines operand 0 of castedOp0";
        });
      }
      auto castedOp1 = ::llvm::dyn_cast<::circt::firrtl::CatPrimOp>(op1); (void)castedOp1;
      if (!(castedOp1)){
        return rewriter.notifyMatchFailure(op1, [&](::mlir::Diagnostic &diag) {
          diag << "castedOp1 is not ::circt::firrtl::CatPrimOp type";
        });
      }
      {
        auto variadic_operand_range = castedOp1.getODSOperands(0);
        if (variadic_operand_range.size() != 2) return ::mlir::failure();
        y = variadic_operand_range.slice(0, 1);
        {
          auto *local_op_1 = variadic_operand_range[1].getDefiningOp();
          if (!(local_op_1)){
            return rewriter.notifyMatchFailure(castedOp1, [&](::mlir::Diagnostic &diag) {
              diag << "There's no operation that defines variadic operand 0 (variadic sub-opearnd #1) of castedOp1";
            });
          }
          if(::mlir::failed(static_dag_matcher_16(rewriter, local_op_1, tblgen_ops, z))) {
            return ::mlir::failure();
          }
          tblgen_ops.push_back(local_op_1);
        }
      }
      tblgen_ops.push_back(op1);
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc(), tblgen_ops[1]->getLoc(), tblgen_ops[2]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    ::circt::firrtl::AsUIntPrimOp tblgen_AsUIntPrimOp_1;
    {
      ::mlir::Value tblgen_value_0 = (*z.begin());
      tblgen_AsUIntPrimOp_1 = ::circt::firrtl::AsUIntPrimOp::create(rewriter, odsLoc,
        /*input=*/tblgen_value_0
      );
    }
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_variadic_values_0;
    tblgen_variadic_values_0.push_back((*y.begin()));
    tblgen_variadic_values_0.push_back(tblgen_AsUIntPrimOp_1);
    ::circt::firrtl::CatPrimOp tblgen_CatPrimOp_2;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values_0;
      for (auto v: tblgen_variadic_values_0) {
        tblgen_values_0.push_back(v);
      }
      tblgen_CatPrimOp_2 = ::circt::firrtl::CatPrimOp::create(rewriter, odsLoc,
        /*inputs=*/tblgen_values_0
      );
    }
    ::circt::firrtl::XorRPrimOp tblgen_XorRPrimOp_3;
    {
      ::mlir::Value tblgen_value_0 = (*tblgen_CatPrimOp_2.getODSResults(0).begin());
      tblgen_XorRPrimOp_3 = ::circt::firrtl::XorRPrimOp::create(rewriter, odsLoc,
        /*input=*/tblgen_value_0
      );
    }
    auto nativeVar_4 = moveNameHint((*old.getODSResults(0).begin()), tblgen_XorRPrimOp_3); (void)nativeVar_4;

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ {nativeVar_4} }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    FIRRTLCanonicalization.td:485
*/
struct XorRCatXorR_right : public ::mlir::RewritePattern {
  XorRCatXorR_right(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("firrtl.xorr", 3, context, {"firrtl.asUInt", "firrtl.cat", "firrtl.xorr"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range y(op0->getOperands());
    ::mlir::Operation::operand_range z(op0->getOperands());
    ::circt::firrtl::XorRPrimOp old;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::circt::firrtl::XorRPrimOp>(op0); (void)castedOp0;
    old = castedOp0;
    {
      auto *op1 = (*castedOp0.getODSOperands(0).begin()).getDefiningOp();
      if (!(op1)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "There's no operation that defines operand 0 of castedOp0";
        });
      }
      auto castedOp1 = ::llvm::dyn_cast<::circt::firrtl::CatPrimOp>(op1); (void)castedOp1;
      if (!(castedOp1)){
        return rewriter.notifyMatchFailure(op1, [&](::mlir::Diagnostic &diag) {
          diag << "castedOp1 is not ::circt::firrtl::CatPrimOp type";
        });
      }
      {
        auto variadic_operand_range = castedOp1.getODSOperands(0);
        if (variadic_operand_range.size() != 2) return ::mlir::failure();
        {
          auto *local_op_0 = variadic_operand_range[0].getDefiningOp();
          if (!(local_op_0)){
            return rewriter.notifyMatchFailure(castedOp1, [&](::mlir::Diagnostic &diag) {
              diag << "There's no operation that defines variadic operand 0 (variadic sub-opearnd #0) of castedOp1";
            });
          }
          if(::mlir::failed(static_dag_matcher_16(rewriter, local_op_0, tblgen_ops, z))) {
            return ::mlir::failure();
          }
          tblgen_ops.push_back(local_op_0);
        }
        y = variadic_operand_range.slice(1, 1);
      }
      tblgen_ops.push_back(op1);
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc(), tblgen_ops[1]->getLoc(), tblgen_ops[2]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    ::circt::firrtl::AsUIntPrimOp tblgen_AsUIntPrimOp_1;
    {
      ::mlir::Value tblgen_value_0 = (*z.begin());
      tblgen_AsUIntPrimOp_1 = ::circt::firrtl::AsUIntPrimOp::create(rewriter, odsLoc,
        /*input=*/tblgen_value_0
      );
    }
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_variadic_values_0;
    tblgen_variadic_values_0.push_back(tblgen_AsUIntPrimOp_1);
    tblgen_variadic_values_0.push_back((*y.begin()));
    ::circt::firrtl::CatPrimOp tblgen_CatPrimOp_2;
    {
      ::llvm::SmallVector<::mlir::Value, 4> tblgen_values_0;
      for (auto v: tblgen_variadic_values_0) {
        tblgen_values_0.push_back(v);
      }
      tblgen_CatPrimOp_2 = ::circt::firrtl::CatPrimOp::create(rewriter, odsLoc,
        /*inputs=*/tblgen_values_0
      );
    }
    ::circt::firrtl::XorRPrimOp tblgen_XorRPrimOp_3;
    {
      ::mlir::Value tblgen_value_0 = (*tblgen_CatPrimOp_2.getODSResults(0).begin());
      tblgen_XorRPrimOp_3 = ::circt::firrtl::XorRPrimOp::create(rewriter, odsLoc,
        /*input=*/tblgen_value_0
      );
    }
    auto nativeVar_4 = moveNameHint((*old.getODSResults(0).begin()), tblgen_XorRPrimOp_3); (void)nativeVar_4;

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ {nativeVar_4} }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    FIRRTLCanonicalization.td:473
*/
struct XorRPadU : public ::mlir::RewritePattern {
  XorRPadU(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("firrtl.xorr", 2, context, {"firrtl.xorr"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::IntegerAttr n;
    ::mlir::Operation::operand_range x(op0->getOperands());
    ::circt::firrtl::PadPrimOp pad;
    ::circt::firrtl::XorRPrimOp old;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::circt::firrtl::XorRPrimOp>(op0); (void)castedOp0;
    old = castedOp0;
    {
      auto *op1 = (*castedOp0.getODSOperands(0).begin()).getDefiningOp();
      if (!(op1)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "There's no operation that defines operand 0 of castedOp0";
        });
      }
      if(::mlir::failed(static_dag_matcher_7(rewriter, op1, tblgen_ops, n, x, pad))) {
        return ::mlir::failure();
      }
      tblgen_ops.push_back(op1);
    }
    if (!((
      type_isa<FIRRTLBaseType>((*x.begin()).getType()) &&
        !type_cast<FIRRTLBaseType>((*x.begin()).getType()).getRecursiveTypeProperties().hasUninferredWidth
      ))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'x' failed to satisfy constraint: ''";
      });
    }
    if (!((type_isa<UIntType>((*x.begin()).getType())))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'x' failed to satisfy constraint: ''";
      });
    }
    if (!((type_cast<IntType>((*pad.getODSResults(0).begin()).getType()).getBitWidthOrSentinel() >= type_cast<IntType>((*x.begin()).getType()).getBitWidthOrSentinel()))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'pad, x' failed to satisfy constraint: ''";
      });
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc(), tblgen_ops[1]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    ::circt::firrtl::XorRPrimOp tblgen_XorRPrimOp_0;
    {
      ::mlir::Value tblgen_value_0 = (*x.begin());
      tblgen_XorRPrimOp_0 = ::circt::firrtl::XorRPrimOp::create(rewriter, odsLoc,
        /*input=*/tblgen_value_0
      );
    }
    auto nativeVar_1 = moveNameHint((*old.getODSResults(0).begin()), tblgen_XorRPrimOp_0); (void)nativeVar_1;

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ {nativeVar_1} }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    FIRRTLCanonicalization.td:461
*/
struct XorRasSInt : public ::mlir::RewritePattern {
  XorRasSInt(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("firrtl.xorr", 2, context, {"firrtl.xorr"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range x(op0->getOperands());
    ::circt::firrtl::XorRPrimOp old;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::circt::firrtl::XorRPrimOp>(op0); (void)castedOp0;
    old = castedOp0;
    {
      auto *op1 = (*castedOp0.getODSOperands(0).begin()).getDefiningOp();
      if (!(op1)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "There's no operation that defines operand 0 of castedOp0";
        });
      }
      if(::mlir::failed(static_dag_matcher_3(rewriter, op1, tblgen_ops, x))) {
        return ::mlir::failure();
      }
      tblgen_ops.push_back(op1);
    }
    if (!((
      type_isa<FIRRTLBaseType>((*x.begin()).getType()) &&
        !type_cast<FIRRTLBaseType>((*x.begin()).getType()).getRecursiveTypeProperties().hasUninferredWidth
      ))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'x' failed to satisfy constraint: ''";
      });
    }
    if (!((type_isa<IntType>((*x.begin()).getType())))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'x' failed to satisfy constraint: ''";
      });
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc(), tblgen_ops[1]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    ::circt::firrtl::XorRPrimOp tblgen_XorRPrimOp_0;
    {
      ::mlir::Value tblgen_value_0 = (*x.begin());
      tblgen_XorRPrimOp_0 = ::circt::firrtl::XorRPrimOp::create(rewriter, odsLoc,
        /*input=*/tblgen_value_0
      );
    }
    auto nativeVar_1 = moveNameHint((*old.getODSResults(0).begin()), tblgen_XorRPrimOp_0); (void)nativeVar_1;

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ {nativeVar_1} }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    FIRRTLCanonicalization.td:467
*/
struct XorRasUInt : public ::mlir::RewritePattern {
  XorRasUInt(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("firrtl.xorr", 2, context, {"firrtl.xorr"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range x(op0->getOperands());
    ::circt::firrtl::XorRPrimOp old;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::circt::firrtl::XorRPrimOp>(op0); (void)castedOp0;
    old = castedOp0;
    {
      auto *op1 = (*castedOp0.getODSOperands(0).begin()).getDefiningOp();
      if (!(op1)){
        return rewriter.notifyMatchFailure(castedOp0, [&](::mlir::Diagnostic &diag) {
          diag << "There's no operation that defines operand 0 of castedOp0";
        });
      }
      if(::mlir::failed(static_dag_matcher_9(rewriter, op1, tblgen_ops, x))) {
        return ::mlir::failure();
      }
      tblgen_ops.push_back(op1);
    }
    if (!((
      type_isa<FIRRTLBaseType>((*x.begin()).getType()) &&
        !type_cast<FIRRTLBaseType>((*x.begin()).getType()).getRecursiveTypeProperties().hasUninferredWidth
      ))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'x' failed to satisfy constraint: ''";
      });
    }
    if (!((type_isa<IntType>((*x.begin()).getType())))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'x' failed to satisfy constraint: ''";
      });
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc(), tblgen_ops[1]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    ::circt::firrtl::XorRPrimOp tblgen_XorRPrimOp_0;
    {
      ::mlir::Value tblgen_value_0 = (*x.begin());
      tblgen_XorRPrimOp_0 = ::circt::firrtl::XorRPrimOp::create(rewriter, odsLoc,
        /*input=*/tblgen_value_0
      );
    }
    auto nativeVar_1 = moveNameHint((*old.getODSResults(0).begin()), tblgen_XorRPrimOp_0); (void)nativeVar_1;

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ {nativeVar_1} }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    FIRRTLCanonicalization.td:243
*/
struct extendAnd : public ::mlir::RewritePattern {
  extendAnd(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("firrtl.and", 1, context, {"firrtl.and", "firrtl.pad"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range rhs(op0->getOperands());
    ::mlir::Operation::operand_range lhs(op0->getOperands());
    ::circt::firrtl::AndPrimOp old;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::circt::firrtl::AndPrimOp>(op0); (void)castedOp0;
    old = castedOp0;
    lhs = castedOp0.getODSOperands(0);
    rhs = castedOp0.getODSOperands(1);
    if (!((
      type_isa<FIRRTLBaseType>((*lhs.begin()).getType()) &&
        !type_cast<FIRRTLBaseType>((*lhs.begin()).getType()).getRecursiveTypeProperties().hasUninferredWidth
      ))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'lhs' failed to satisfy constraint: ''";
      });
    }
    if (!((
      type_isa<FIRRTLBaseType>((*rhs.begin()).getType()) &&
        !type_cast<FIRRTLBaseType>((*rhs.begin()).getType()).getRecursiveTypeProperties().hasUninferredWidth
      ))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'rhs' failed to satisfy constraint: ''";
      });
    }
    if (!((
      !areAnonymousTypesEquivalent(
        type_cast<FIRRTLBaseType>((*lhs.begin()).getType()).getAllConstDroppedType(),
        type_cast<FIRRTLBaseType>((*rhs.begin()).getType()).getAllConstDroppedType())
      ))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'lhs, rhs' failed to satisfy constraint: ''";
      });
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    auto nativeVar_0 = rewriter.getI32IntegerAttr(type_cast<FIRRTLBaseType>((*old.getODSResults(0).begin()).getType()).getBitWidthOrSentinel()); (void)nativeVar_0;
    ::circt::firrtl::PadPrimOp tblgen_PadPrimOp_1;
    {
      ::mlir::Value tblgen_value_0 = (*lhs.begin());
      tblgen_PadPrimOp_1 = ::circt::firrtl::PadPrimOp::create(rewriter, odsLoc,
        /*input=*/tblgen_value_0,
        /*amount=*/nativeVar_0
      );
    }
    auto nativeVar_2 = rewriter.getI32IntegerAttr(type_cast<FIRRTLBaseType>((*old.getODSResults(0).begin()).getType()).getBitWidthOrSentinel()); (void)nativeVar_2;
    ::circt::firrtl::PadPrimOp tblgen_PadPrimOp_3;
    {
      ::mlir::Value tblgen_value_0 = (*rhs.begin());
      tblgen_PadPrimOp_3 = ::circt::firrtl::PadPrimOp::create(rewriter, odsLoc,
        /*input=*/tblgen_value_0,
        /*amount=*/nativeVar_2
      );
    }
    ::circt::firrtl::AndPrimOp tblgen_AndPrimOp_4;
    {
      ::mlir::Value tblgen_value_0 = (*tblgen_PadPrimOp_1.getODSResults(0).begin());
      ::mlir::Value tblgen_value_1 = (*tblgen_PadPrimOp_3.getODSResults(0).begin());
      tblgen_AndPrimOp_4 = ::circt::firrtl::AndPrimOp::create(rewriter, odsLoc,
        /*lhs=*/tblgen_value_0,
        /*rhs=*/tblgen_value_1
      );
    }
    auto nativeVar_5 = moveNameHint((*old.getODSResults(0).begin()), tblgen_AndPrimOp_4); (void)nativeVar_5;

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ {nativeVar_5} }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    FIRRTLCanonicalization.td:249
*/
struct extendOr : public ::mlir::RewritePattern {
  extendOr(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("firrtl.or", 1, context, {"firrtl.or", "firrtl.pad"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range rhs(op0->getOperands());
    ::mlir::Operation::operand_range lhs(op0->getOperands());
    ::circt::firrtl::OrPrimOp old;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::circt::firrtl::OrPrimOp>(op0); (void)castedOp0;
    old = castedOp0;
    lhs = castedOp0.getODSOperands(0);
    rhs = castedOp0.getODSOperands(1);
    if (!((
      type_isa<FIRRTLBaseType>((*lhs.begin()).getType()) &&
        !type_cast<FIRRTLBaseType>((*lhs.begin()).getType()).getRecursiveTypeProperties().hasUninferredWidth
      ))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'lhs' failed to satisfy constraint: ''";
      });
    }
    if (!((
      type_isa<FIRRTLBaseType>((*rhs.begin()).getType()) &&
        !type_cast<FIRRTLBaseType>((*rhs.begin()).getType()).getRecursiveTypeProperties().hasUninferredWidth
      ))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'rhs' failed to satisfy constraint: ''";
      });
    }
    if (!((
      !areAnonymousTypesEquivalent(
        type_cast<FIRRTLBaseType>((*lhs.begin()).getType()).getAllConstDroppedType(),
        type_cast<FIRRTLBaseType>((*rhs.begin()).getType()).getAllConstDroppedType())
      ))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'lhs, rhs' failed to satisfy constraint: ''";
      });
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    auto nativeVar_0 = rewriter.getI32IntegerAttr(type_cast<FIRRTLBaseType>((*old.getODSResults(0).begin()).getType()).getBitWidthOrSentinel()); (void)nativeVar_0;
    ::circt::firrtl::PadPrimOp tblgen_PadPrimOp_1;
    {
      ::mlir::Value tblgen_value_0 = (*lhs.begin());
      tblgen_PadPrimOp_1 = ::circt::firrtl::PadPrimOp::create(rewriter, odsLoc,
        /*input=*/tblgen_value_0,
        /*amount=*/nativeVar_0
      );
    }
    auto nativeVar_2 = rewriter.getI32IntegerAttr(type_cast<FIRRTLBaseType>((*old.getODSResults(0).begin()).getType()).getBitWidthOrSentinel()); (void)nativeVar_2;
    ::circt::firrtl::PadPrimOp tblgen_PadPrimOp_3;
    {
      ::mlir::Value tblgen_value_0 = (*rhs.begin());
      tblgen_PadPrimOp_3 = ::circt::firrtl::PadPrimOp::create(rewriter, odsLoc,
        /*input=*/tblgen_value_0,
        /*amount=*/nativeVar_2
      );
    }
    ::circt::firrtl::OrPrimOp tblgen_OrPrimOp_4;
    {
      ::mlir::Value tblgen_value_0 = (*tblgen_PadPrimOp_1.getODSResults(0).begin());
      ::mlir::Value tblgen_value_1 = (*tblgen_PadPrimOp_3.getODSResults(0).begin());
      tblgen_OrPrimOp_4 = ::circt::firrtl::OrPrimOp::create(rewriter, odsLoc,
        /*lhs=*/tblgen_value_0,
        /*rhs=*/tblgen_value_1
      );
    }
    auto nativeVar_5 = moveNameHint((*old.getODSResults(0).begin()), tblgen_OrPrimOp_4); (void)nativeVar_5;

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ {nativeVar_5} }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    FIRRTLCanonicalization.td:255
*/
struct extendXor : public ::mlir::RewritePattern {
  extendXor(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("firrtl.xor", 1, context, {"firrtl.pad", "firrtl.xor"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range rhs(op0->getOperands());
    ::mlir::Operation::operand_range lhs(op0->getOperands());
    ::circt::firrtl::XorPrimOp old;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::circt::firrtl::XorPrimOp>(op0); (void)castedOp0;
    old = castedOp0;
    lhs = castedOp0.getODSOperands(0);
    rhs = castedOp0.getODSOperands(1);
    if (!((
      type_isa<FIRRTLBaseType>((*lhs.begin()).getType()) &&
        !type_cast<FIRRTLBaseType>((*lhs.begin()).getType()).getRecursiveTypeProperties().hasUninferredWidth
      ))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'lhs' failed to satisfy constraint: ''";
      });
    }
    if (!((
      type_isa<FIRRTLBaseType>((*rhs.begin()).getType()) &&
        !type_cast<FIRRTLBaseType>((*rhs.begin()).getType()).getRecursiveTypeProperties().hasUninferredWidth
      ))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'rhs' failed to satisfy constraint: ''";
      });
    }
    if (!((
      !areAnonymousTypesEquivalent(
        type_cast<FIRRTLBaseType>((*lhs.begin()).getType()).getAllConstDroppedType(),
        type_cast<FIRRTLBaseType>((*rhs.begin()).getType()).getAllConstDroppedType())
      ))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'lhs, rhs' failed to satisfy constraint: ''";
      });
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    auto nativeVar_0 = rewriter.getI32IntegerAttr(type_cast<FIRRTLBaseType>((*old.getODSResults(0).begin()).getType()).getBitWidthOrSentinel()); (void)nativeVar_0;
    ::circt::firrtl::PadPrimOp tblgen_PadPrimOp_1;
    {
      ::mlir::Value tblgen_value_0 = (*lhs.begin());
      tblgen_PadPrimOp_1 = ::circt::firrtl::PadPrimOp::create(rewriter, odsLoc,
        /*input=*/tblgen_value_0,
        /*amount=*/nativeVar_0
      );
    }
    auto nativeVar_2 = rewriter.getI32IntegerAttr(type_cast<FIRRTLBaseType>((*old.getODSResults(0).begin()).getType()).getBitWidthOrSentinel()); (void)nativeVar_2;
    ::circt::firrtl::PadPrimOp tblgen_PadPrimOp_3;
    {
      ::mlir::Value tblgen_value_0 = (*rhs.begin());
      tblgen_PadPrimOp_3 = ::circt::firrtl::PadPrimOp::create(rewriter, odsLoc,
        /*input=*/tblgen_value_0,
        /*amount=*/nativeVar_2
      );
    }
    ::circt::firrtl::XorPrimOp tblgen_XorPrimOp_4;
    {
      ::mlir::Value tblgen_value_0 = (*tblgen_PadPrimOp_1.getODSResults(0).begin());
      ::mlir::Value tblgen_value_1 = (*tblgen_PadPrimOp_3.getODSResults(0).begin());
      tblgen_XorPrimOp_4 = ::circt::firrtl::XorPrimOp::create(rewriter, odsLoc,
        /*lhs=*/tblgen_value_0,
        /*rhs=*/tblgen_value_1
      );
    }
    auto nativeVar_5 = moveNameHint((*old.getODSResults(0).begin()), tblgen_XorPrimOp_4); (void)nativeVar_5;

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ {nativeVar_5} }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    FIRRTLCanonicalization.td:265
*/
struct moveConstAdd : public ::mlir::RewritePattern {
  moveConstAdd(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("firrtl.add", 1, context, {"firrtl.add"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range y(op0->getOperands());
    ::mlir::Operation::operand_range x(op0->getOperands());
    ::circt::firrtl::AddPrimOp old;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::circt::firrtl::AddPrimOp>(op0); (void)castedOp0;
    old = castedOp0;
    x = castedOp0.getODSOperands(0);
    y = castedOp0.getODSOperands(1);
    if (!((
      isa_and_nonnull<ConstantOp, SpecialConstantOp, AggregateConstantOp>
        ((*x.begin()).getDefiningOp())
      ))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'x' failed to satisfy constraint: ''";
      });
    }
    if (!((
      !isa_and_nonnull<ConstantOp, SpecialConstantOp, AggregateConstantOp>
        ((*y.begin()).getDefiningOp())
      ))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'y' failed to satisfy constraint: ''";
      });
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    ::circt::firrtl::AddPrimOp tblgen_AddPrimOp_0;
    {
      ::mlir::Value tblgen_value_0 = (*y.begin());
      ::mlir::Value tblgen_value_1 = (*x.begin());
      tblgen_AddPrimOp_0 = ::circt::firrtl::AddPrimOp::create(rewriter, odsLoc,
        /*lhs=*/tblgen_value_0,
        /*rhs=*/tblgen_value_1
      );
    }
    auto nativeVar_1 = moveNameHint((*old.getODSResults(0).begin()), tblgen_AddPrimOp_0); (void)nativeVar_1;

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ {nativeVar_1} }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    FIRRTLCanonicalization.td:270
*/
struct moveConstAnd : public ::mlir::RewritePattern {
  moveConstAnd(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("firrtl.and", 1, context, {"firrtl.and"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range y(op0->getOperands());
    ::mlir::Operation::operand_range x(op0->getOperands());
    ::circt::firrtl::AndPrimOp old;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::circt::firrtl::AndPrimOp>(op0); (void)castedOp0;
    old = castedOp0;
    x = castedOp0.getODSOperands(0);
    y = castedOp0.getODSOperands(1);
    if (!((
      isa_and_nonnull<ConstantOp, SpecialConstantOp, AggregateConstantOp>
        ((*x.begin()).getDefiningOp())
      ))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'x' failed to satisfy constraint: ''";
      });
    }
    if (!((
      !isa_and_nonnull<ConstantOp, SpecialConstantOp, AggregateConstantOp>
        ((*y.begin()).getDefiningOp())
      ))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'y' failed to satisfy constraint: ''";
      });
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    ::circt::firrtl::AndPrimOp tblgen_AndPrimOp_0;
    {
      ::mlir::Value tblgen_value_0 = (*y.begin());
      ::mlir::Value tblgen_value_1 = (*x.begin());
      tblgen_AndPrimOp_0 = ::circt::firrtl::AndPrimOp::create(rewriter, odsLoc,
        /*lhs=*/tblgen_value_0,
        /*rhs=*/tblgen_value_1
      );
    }
    auto nativeVar_1 = moveNameHint((*old.getODSResults(0).begin()), tblgen_AndPrimOp_0); (void)nativeVar_1;

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ {nativeVar_1} }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    FIRRTLCanonicalization.td:275
*/
struct moveConstOr : public ::mlir::RewritePattern {
  moveConstOr(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("firrtl.or", 1, context, {"firrtl.or"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range y(op0->getOperands());
    ::mlir::Operation::operand_range x(op0->getOperands());
    ::circt::firrtl::OrPrimOp old;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::circt::firrtl::OrPrimOp>(op0); (void)castedOp0;
    old = castedOp0;
    x = castedOp0.getODSOperands(0);
    y = castedOp0.getODSOperands(1);
    if (!((
      isa_and_nonnull<ConstantOp, SpecialConstantOp, AggregateConstantOp>
        ((*x.begin()).getDefiningOp())
      ))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'x' failed to satisfy constraint: ''";
      });
    }
    if (!((
      !isa_and_nonnull<ConstantOp, SpecialConstantOp, AggregateConstantOp>
        ((*y.begin()).getDefiningOp())
      ))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'y' failed to satisfy constraint: ''";
      });
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    ::circt::firrtl::OrPrimOp tblgen_OrPrimOp_0;
    {
      ::mlir::Value tblgen_value_0 = (*y.begin());
      ::mlir::Value tblgen_value_1 = (*x.begin());
      tblgen_OrPrimOp_0 = ::circt::firrtl::OrPrimOp::create(rewriter, odsLoc,
        /*lhs=*/tblgen_value_0,
        /*rhs=*/tblgen_value_1
      );
    }
    auto nativeVar_1 = moveNameHint((*old.getODSResults(0).begin()), tblgen_OrPrimOp_0); (void)nativeVar_1;

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ {nativeVar_1} }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

/* Generated from:
    FIRRTLCanonicalization.td:280
*/
struct moveConstXor : public ::mlir::RewritePattern {
  moveConstXor(::mlir::MLIRContext *context)
      : ::mlir::RewritePattern("firrtl.xor", 1, context, {"firrtl.xor"}) {}
  ::llvm::LogicalResult matchAndRewrite(::mlir::Operation *op0,
      ::mlir::PatternRewriter &rewriter) const override {
    // Variables for capturing values and attributes used while creating ops
    ::mlir::Operation::operand_range y(op0->getOperands());
    ::mlir::Operation::operand_range x(op0->getOperands());
    ::circt::firrtl::XorPrimOp old;
    ::llvm::SmallVector<::mlir::Operation *, 4> tblgen_ops;

    // Match
    tblgen_ops.push_back(op0);
    auto castedOp0 = ::llvm::dyn_cast<::circt::firrtl::XorPrimOp>(op0); (void)castedOp0;
    old = castedOp0;
    x = castedOp0.getODSOperands(0);
    y = castedOp0.getODSOperands(1);
    if (!((
      isa_and_nonnull<ConstantOp, SpecialConstantOp, AggregateConstantOp>
        ((*x.begin()).getDefiningOp())
      ))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'x' failed to satisfy constraint: ''";
      });
    }
    if (!((
      !isa_and_nonnull<ConstantOp, SpecialConstantOp, AggregateConstantOp>
        ((*y.begin()).getDefiningOp())
      ))){
      return rewriter.notifyMatchFailure(op0, [&](::mlir::Diagnostic &diag) {
        diag << "entities 'y' failed to satisfy constraint: ''";
      });
    }

    // Rewrite
    auto odsLoc = rewriter.getFusedLoc({tblgen_ops[0]->getLoc()}); (void)odsLoc;
    ::llvm::SmallVector<::mlir::Value, 4> tblgen_repl_values;
    ::circt::firrtl::XorPrimOp tblgen_XorPrimOp_0;
    {
      ::mlir::Value tblgen_value_0 = (*y.begin());
      ::mlir::Value tblgen_value_1 = (*x.begin());
      tblgen_XorPrimOp_0 = ::circt::firrtl::XorPrimOp::create(rewriter, odsLoc,
        /*lhs=*/tblgen_value_0,
        /*rhs=*/tblgen_value_1
      );
    }
    auto nativeVar_1 = moveNameHint((*old.getODSResults(0).begin()), tblgen_XorPrimOp_0); (void)nativeVar_1;

    for (auto v: ::llvm::SmallVector<::mlir::Value, 4>{ {nativeVar_1} }) {
      tblgen_repl_values.push_back(v);
    }

    rewriter.replaceOp(op0, tblgen_repl_values);
    return ::mlir::success();
  }
};

[[maybe_unused]] void populateWithGenerated(::mlir::RewritePatternSet &patterns) {
  patterns.add<AddOfPad>(patterns.getContext());
  patterns.add<AddOfSelf>(patterns.getContext());
  patterns.add<AddOfZero>(patterns.getContext());
  patterns.add<AndOfAllOne>(patterns.getContext());
  patterns.add<AndOfAsSIntL>(patterns.getContext());
  patterns.add<AndOfAsSIntR>(patterns.getContext());
  patterns.add<AndOfPad>(patterns.getContext());
  patterns.add<AndOfSelf>(patterns.getContext());
  patterns.add<AndOfZero>(patterns.getContext());
  patterns.add<AndRCatAndR_left>(patterns.getContext());
  patterns.add<AndRCatAndR_right>(patterns.getContext());
  patterns.add<AndRPadS>(patterns.getContext());
  patterns.add<AndRPadU>(patterns.getContext());
  patterns.add<AndRasSInt>(patterns.getContext());
  patterns.add<AndRasUInt>(patterns.getContext());
  patterns.add<AssertXWhenX>(patterns.getContext());
  patterns.add<AssumeXWhenX>(patterns.getContext());
  patterns.add<BitsOfAnd>(patterns.getContext());
  patterns.add<BitsOfAsUInt>(patterns.getContext());
  patterns.add<BitsOfBits>(patterns.getContext());
  patterns.add<BitsOfMux>(patterns.getContext());
  patterns.add<BitsOfPad>(patterns.getContext());
  patterns.add<CVTSigned>(patterns.getContext());
  patterns.add<CVTUnSigned>(patterns.getContext());
  patterns.add<CatBitsBits>(patterns.getContext());
  patterns.add<CatCast>(patterns.getContext());
  patterns.add<CatDoubleConst>(patterns.getContext());
  patterns.add<ConnectExtension>(patterns.getContext());
  patterns.add<ConnectSameType>(patterns.getContext());
  patterns.add<DShlOfConstant>(patterns.getContext());
  patterns.add<DShrOfConstant>(patterns.getContext());
  patterns.add<GEQWithConstLHS>(patterns.getContext());
  patterns.add<GTWithConstLHS>(patterns.getContext());
  patterns.add<LEQWithConstLHS>(patterns.getContext());
  patterns.add<LTWithConstLHS>(patterns.getContext());
  patterns.add<Mux2PadSel>(patterns.getContext());
  patterns.add<Mux4PadSel>(patterns.getContext());
  patterns.add<MuxEQOperands>(patterns.getContext());
  patterns.add<MuxEQOperandsSwapped>(patterns.getContext());
  patterns.add<MuxNEQ>(patterns.getContext());
  patterns.add<MuxNot>(patterns.getContext());
  patterns.add<MuxPadSel>(patterns.getContext());
  patterns.add<MuxSameFalse>(patterns.getContext());
  patterns.add<MuxSameTrue>(patterns.getContext());
  patterns.add<NarrowMuxLHS>(patterns.getContext());
  patterns.add<NarrowMuxRHS>(patterns.getContext());
  patterns.add<NotEq>(patterns.getContext());
  patterns.add<NotGeq>(patterns.getContext());
  patterns.add<NotGt>(patterns.getContext());
  patterns.add<NotLeq>(patterns.getContext());
  patterns.add<NotLt>(patterns.getContext());
  patterns.add<NotNeq>(patterns.getContext());
  patterns.add<NotNot>(patterns.getContext());
  patterns.add<OrOfAllOne>(patterns.getContext());
  patterns.add<OrOfPad>(patterns.getContext());
  patterns.add<OrOfSelf>(patterns.getContext());
  patterns.add<OrOfZero>(patterns.getContext());
  patterns.add<OrOrr>(patterns.getContext());
  patterns.add<OrRCatOrR_left>(patterns.getContext());
  patterns.add<OrRCatOrR_right>(patterns.getContext());
  patterns.add<OrRPadU>(patterns.getContext());
  patterns.add<OrRasSInt>(patterns.getContext());
  patterns.add<OrRasUInt>(patterns.getContext());
  patterns.add<RefResolveOfRefSend>(patterns.getContext());
  patterns.add<RegResetWithZeroReset>(patterns.getContext());
  patterns.add<StoUtoS>(patterns.getContext());
  patterns.add<SubFromZeroSigned>(patterns.getContext());
  patterns.add<SubFromZeroUnsigned>(patterns.getContext());
  patterns.add<SubOfPadL>(patterns.getContext());
  patterns.add<SubOfPadR>(patterns.getContext());
  patterns.add<SubOfSelf>(patterns.getContext());
  patterns.add<SubOfZero>(patterns.getContext());
  patterns.add<SubaccessOfConstant>(patterns.getContext());
  patterns.add<UnclockedAssumeIntrinsicXWhenX>(patterns.getContext());
  patterns.add<UtoStoU>(patterns.getContext());
  patterns.add<XorOfPad>(patterns.getContext());
  patterns.add<XorOfSelf>(patterns.getContext());
  patterns.add<XorOfZero>(patterns.getContext());
  patterns.add<XorRCatXorR_left>(patterns.getContext());
  patterns.add<XorRCatXorR_right>(patterns.getContext());
  patterns.add<XorRPadU>(patterns.getContext());
  patterns.add<XorRasSInt>(patterns.getContext());
  patterns.add<XorRasUInt>(patterns.getContext());
  patterns.add<extendAnd>(patterns.getContext());
  patterns.add<extendOr>(patterns.getContext());
  patterns.add<extendXor>(patterns.getContext());
  patterns.add<moveConstAdd>(patterns.getContext());
  patterns.add<moveConstAnd>(patterns.getContext());
  patterns.add<moveConstOr>(patterns.getContext());
  patterns.add<moveConstXor>(patterns.getContext());
}
