/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Enum Utility Definitions                                                   *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: Synth.td                                                             *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace circt::synth {

::llvm::StringRef stringifyPolarityKind(PolarityKind val) {
  switch (val) {
    case PolarityKind::Positive: return "positive";
    case PolarityKind::Negative: return "negative";
  }
  return "";
}

::std::optional<PolarityKind> symbolizePolarityKind(::llvm::StringRef str) {
  return ::llvm::StringSwitch<::std::optional<PolarityKind>>(str)
      .Case("positive", PolarityKind::Positive)
      .Case("negative", PolarityKind::Negative)
      .Default(::std::nullopt);
}
::std::optional<PolarityKind> symbolizePolarityKind(uint32_t value) {
  switch (value) {
  case 0: return PolarityKind::Positive;
  case 1: return PolarityKind::Negative;
  default: return ::std::nullopt;
  }
}

bool PolarityKindAttr::classof(::mlir::Attribute attr) {
  return (((::llvm::isa<::mlir::IntegerAttr>(attr))) && ((::llvm::cast<::mlir::IntegerAttr>(attr).getType().isSignlessInteger(32)))) && (((
    ::llvm::cast<::mlir::IntegerAttr>(attr).getValue().eq(::llvm::APInt(32, 0)))) || ((
    ::llvm::cast<::mlir::IntegerAttr>(attr).getValue().eq(::llvm::APInt(32, 1)))));
}
PolarityKindAttr PolarityKindAttr::get(::mlir::MLIRContext *context, PolarityKind val) {
  ::mlir::IntegerType intType = ::mlir::IntegerType::get(context, 32);
  ::mlir::IntegerAttr baseAttr = ::mlir::IntegerAttr::get(intType, static_cast<uint32_t>(val));
  return ::llvm::cast<PolarityKindAttr>(baseAttr);
}
PolarityKind PolarityKindAttr::getValue() const {
  return static_cast<PolarityKind>(::mlir::IntegerAttr::getValue().getZExtValue());
}

} // namespace circt::synth
