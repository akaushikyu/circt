/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Enum Utility Definitions                                                   *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: Comb.td                                                              *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace circt::comb {

::llvm::StringRef stringifyICmpPredicate(ICmpPredicate val) {
  switch (val) {
    case ICmpPredicate::eq: return "eq";
    case ICmpPredicate::ne: return "ne";
    case ICmpPredicate::slt: return "slt";
    case ICmpPredicate::sle: return "sle";
    case ICmpPredicate::sgt: return "sgt";
    case ICmpPredicate::sge: return "sge";
    case ICmpPredicate::ult: return "ult";
    case ICmpPredicate::ule: return "ule";
    case ICmpPredicate::ugt: return "ugt";
    case ICmpPredicate::uge: return "uge";
    case ICmpPredicate::ceq: return "ceq";
    case ICmpPredicate::cne: return "cne";
    case ICmpPredicate::weq: return "weq";
    case ICmpPredicate::wne: return "wne";
  }
  return "";
}

::std::optional<ICmpPredicate> symbolizeICmpPredicate(::llvm::StringRef str) {
  return ::llvm::StringSwitch<::std::optional<ICmpPredicate>>(str)
      .Case("eq", ICmpPredicate::eq)
      .Case("ne", ICmpPredicate::ne)
      .Case("slt", ICmpPredicate::slt)
      .Case("sle", ICmpPredicate::sle)
      .Case("sgt", ICmpPredicate::sgt)
      .Case("sge", ICmpPredicate::sge)
      .Case("ult", ICmpPredicate::ult)
      .Case("ule", ICmpPredicate::ule)
      .Case("ugt", ICmpPredicate::ugt)
      .Case("uge", ICmpPredicate::uge)
      .Case("ceq", ICmpPredicate::ceq)
      .Case("cne", ICmpPredicate::cne)
      .Case("weq", ICmpPredicate::weq)
      .Case("wne", ICmpPredicate::wne)
      .Default(::std::nullopt);
}
::std::optional<ICmpPredicate> symbolizeICmpPredicate(uint64_t value) {
  switch (value) {
  case 0: return ICmpPredicate::eq;
  case 1: return ICmpPredicate::ne;
  case 2: return ICmpPredicate::slt;
  case 3: return ICmpPredicate::sle;
  case 4: return ICmpPredicate::sgt;
  case 5: return ICmpPredicate::sge;
  case 6: return ICmpPredicate::ult;
  case 7: return ICmpPredicate::ule;
  case 8: return ICmpPredicate::ugt;
  case 9: return ICmpPredicate::uge;
  case 10: return ICmpPredicate::ceq;
  case 11: return ICmpPredicate::cne;
  case 12: return ICmpPredicate::weq;
  case 13: return ICmpPredicate::wne;
  default: return ::std::nullopt;
  }
}

bool ICmpPredicateAttr::classof(::mlir::Attribute attr) {
  return (((::llvm::isa<::mlir::IntegerAttr>(attr))) && ((::llvm::cast<::mlir::IntegerAttr>(attr).getType().isSignlessInteger(64)))) && (((
    ::llvm::cast<::mlir::IntegerAttr>(attr).getValue().eq(::llvm::APInt(64, 0)))) || ((
    ::llvm::cast<::mlir::IntegerAttr>(attr).getValue().eq(::llvm::APInt(64, 1)))) || ((
    ::llvm::cast<::mlir::IntegerAttr>(attr).getValue().eq(::llvm::APInt(64, 2)))) || ((
    ::llvm::cast<::mlir::IntegerAttr>(attr).getValue().eq(::llvm::APInt(64, 3)))) || ((
    ::llvm::cast<::mlir::IntegerAttr>(attr).getValue().eq(::llvm::APInt(64, 4)))) || ((
    ::llvm::cast<::mlir::IntegerAttr>(attr).getValue().eq(::llvm::APInt(64, 5)))) || ((
    ::llvm::cast<::mlir::IntegerAttr>(attr).getValue().eq(::llvm::APInt(64, 6)))) || ((
    ::llvm::cast<::mlir::IntegerAttr>(attr).getValue().eq(::llvm::APInt(64, 7)))) || ((
    ::llvm::cast<::mlir::IntegerAttr>(attr).getValue().eq(::llvm::APInt(64, 8)))) || ((
    ::llvm::cast<::mlir::IntegerAttr>(attr).getValue().eq(::llvm::APInt(64, 9)))) || ((
    ::llvm::cast<::mlir::IntegerAttr>(attr).getValue().eq(::llvm::APInt(64, 10)))) || ((
    ::llvm::cast<::mlir::IntegerAttr>(attr).getValue().eq(::llvm::APInt(64, 11)))) || ((
    ::llvm::cast<::mlir::IntegerAttr>(attr).getValue().eq(::llvm::APInt(64, 12)))) || ((
    ::llvm::cast<::mlir::IntegerAttr>(attr).getValue().eq(::llvm::APInt(64, 13)))));
}
ICmpPredicateAttr ICmpPredicateAttr::get(::mlir::MLIRContext *context, ICmpPredicate val) {
  ::mlir::IntegerType intType = ::mlir::IntegerType::get(context, 64);
  ::mlir::IntegerAttr baseAttr = ::mlir::IntegerAttr::get(intType, static_cast<uint64_t>(val));
  return ::llvm::cast<ICmpPredicateAttr>(baseAttr);
}
ICmpPredicate ICmpPredicateAttr::getValue() const {
  return static_cast<ICmpPredicate>(::mlir::IntegerAttr::getValue().getZExtValue());
}

} // namespace circt::comb
