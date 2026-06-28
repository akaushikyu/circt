/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Enum Utility Definitions                                                   *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: HWArith.td                                                           *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace circt::hwarith {

::llvm::StringRef stringifyICmpPredicate(ICmpPredicate val) {
  switch (val) {
    case ICmpPredicate::eq: return "eq";
    case ICmpPredicate::ne: return "ne";
    case ICmpPredicate::lt: return "lt";
    case ICmpPredicate::ge: return "ge";
    case ICmpPredicate::le: return "le";
    case ICmpPredicate::gt: return "gt";
  }
  return "";
}

::std::optional<ICmpPredicate> symbolizeICmpPredicate(::llvm::StringRef str) {
  return ::llvm::StringSwitch<::std::optional<ICmpPredicate>>(str)
      .Case("eq", ICmpPredicate::eq)
      .Case("ne", ICmpPredicate::ne)
      .Case("lt", ICmpPredicate::lt)
      .Case("ge", ICmpPredicate::ge)
      .Case("le", ICmpPredicate::le)
      .Case("gt", ICmpPredicate::gt)
      .Default(::std::nullopt);
}
::std::optional<ICmpPredicate> symbolizeICmpPredicate(uint64_t value) {
  switch (value) {
  case 0: return ICmpPredicate::eq;
  case 1: return ICmpPredicate::ne;
  case 2: return ICmpPredicate::lt;
  case 3: return ICmpPredicate::ge;
  case 4: return ICmpPredicate::le;
  case 5: return ICmpPredicate::gt;
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
    ::llvm::cast<::mlir::IntegerAttr>(attr).getValue().eq(::llvm::APInt(64, 5)))));
}
ICmpPredicateAttr ICmpPredicateAttr::get(::mlir::MLIRContext *context, ICmpPredicate val) {
  ::mlir::IntegerType intType = ::mlir::IntegerType::get(context, 64);
  ::mlir::IntegerAttr baseAttr = ::mlir::IntegerAttr::get(intType, static_cast<uint64_t>(val));
  return ::llvm::cast<ICmpPredicateAttr>(baseAttr);
}
ICmpPredicate ICmpPredicateAttr::getValue() const {
  return static_cast<ICmpPredicate>(::mlir::IntegerAttr::getValue().getZExtValue());
}

} // namespace circt::hwarith
