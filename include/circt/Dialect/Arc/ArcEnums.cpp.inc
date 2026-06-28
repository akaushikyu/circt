/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Enum Utility Definitions                                                   *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: Arc.td                                                               *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace circt::arc {

::llvm::StringRef stringifyZeroCountPredicate(ZeroCountPredicate val) {
  switch (val) {
    case ZeroCountPredicate::leading: return "leading";
    case ZeroCountPredicate::trailing: return "trailing";
  }
  return "";
}

::std::optional<ZeroCountPredicate> symbolizeZeroCountPredicate(::llvm::StringRef str) {
  return ::llvm::StringSwitch<::std::optional<ZeroCountPredicate>>(str)
      .Case("leading", ZeroCountPredicate::leading)
      .Case("trailing", ZeroCountPredicate::trailing)
      .Default(::std::nullopt);
}
::std::optional<ZeroCountPredicate> symbolizeZeroCountPredicate(uint32_t value) {
  switch (value) {
  case 0: return ZeroCountPredicate::leading;
  case 1: return ZeroCountPredicate::trailing;
  default: return ::std::nullopt;
  }
}

bool ZeroCountPredicateAttr::classof(::mlir::Attribute attr) {
  return (((::llvm::isa<::mlir::IntegerAttr>(attr))) && ((::llvm::cast<::mlir::IntegerAttr>(attr).getType().isSignlessInteger(32)))) && (((
    ::llvm::cast<::mlir::IntegerAttr>(attr).getValue().eq(::llvm::APInt(32, 0)))) || ((
    ::llvm::cast<::mlir::IntegerAttr>(attr).getValue().eq(::llvm::APInt(32, 1)))));
}
ZeroCountPredicateAttr ZeroCountPredicateAttr::get(::mlir::MLIRContext *context, ZeroCountPredicate val) {
  ::mlir::IntegerType intType = ::mlir::IntegerType::get(context, 32);
  ::mlir::IntegerAttr baseAttr = ::mlir::IntegerAttr::get(intType, static_cast<uint32_t>(val));
  return ::llvm::cast<ZeroCountPredicateAttr>(baseAttr);
}
ZeroCountPredicate ZeroCountPredicateAttr::getValue() const {
  return static_cast<ZeroCountPredicate>(::mlir::IntegerAttr::getValue().getZExtValue());
}

} // namespace circt::arc
