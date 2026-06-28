/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Enum Utility Definitions                                                   *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: MSFT.td                                                              *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

::llvm::StringRef stringifyPrimitiveType(PrimitiveType val) {
  switch (val) {
    case PrimitiveType::M20K: return "M20K";
    case PrimitiveType::DSP: return "DSP";
    case PrimitiveType::FF: return "FF";
  }
  return "";
}

::std::optional<PrimitiveType> symbolizePrimitiveType(::llvm::StringRef str) {
  return ::llvm::StringSwitch<::std::optional<PrimitiveType>>(str)
      .Case("M20K", PrimitiveType::M20K)
      .Case("DSP", PrimitiveType::DSP)
      .Case("FF", PrimitiveType::FF)
      .Default(::std::nullopt);
}
::std::optional<PrimitiveType> symbolizePrimitiveType(uint32_t value) {
  switch (value) {
  case 1: return PrimitiveType::M20K;
  case 2: return PrimitiveType::DSP;
  case 3: return PrimitiveType::FF;
  default: return ::std::nullopt;
  }
}

bool PrimitiveTypeAttr::classof(::mlir::Attribute attr) {
  return (((::llvm::isa<::mlir::IntegerAttr>(attr))) && ((::llvm::cast<::mlir::IntegerAttr>(attr).getType().isSignlessInteger(32)))) && (((
    ::llvm::cast<::mlir::IntegerAttr>(attr).getValue().eq(::llvm::APInt(32, 1)))) || ((
    ::llvm::cast<::mlir::IntegerAttr>(attr).getValue().eq(::llvm::APInt(32, 2)))) || ((
    ::llvm::cast<::mlir::IntegerAttr>(attr).getValue().eq(::llvm::APInt(32, 3)))));
}
PrimitiveTypeAttr PrimitiveTypeAttr::get(::mlir::MLIRContext *context, PrimitiveType val) {
  ::mlir::IntegerType intType = ::mlir::IntegerType::get(context, 32);
  ::mlir::IntegerAttr baseAttr = ::mlir::IntegerAttr::get(intType, static_cast<uint32_t>(val));
  return ::llvm::cast<PrimitiveTypeAttr>(baseAttr);
}
PrimitiveType PrimitiveTypeAttr::getValue() const {
  return static_cast<PrimitiveType>(::mlir::IntegerAttr::getValue().getZExtValue());
}
