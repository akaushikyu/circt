/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Enum Utility Definitions                                                   *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: ArcPasses.td                                                         *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace circt::arc {

::llvm::StringRef stringifyLowerVectorizationsModeEnum(LowerVectorizationsModeEnum val) {
  switch (val) {
    case LowerVectorizationsModeEnum::Boundary: return "boundary";
    case LowerVectorizationsModeEnum::Body: return "body";
    case LowerVectorizationsModeEnum::InlineBody: return "inline-body";
    case LowerVectorizationsModeEnum::Full: return "Full";
  }
  return "";
}

::std::optional<LowerVectorizationsModeEnum> symbolizeLowerVectorizationsModeEnum(::llvm::StringRef str) {
  return ::llvm::StringSwitch<::std::optional<LowerVectorizationsModeEnum>>(str)
      .Case("boundary", LowerVectorizationsModeEnum::Boundary)
      .Case("body", LowerVectorizationsModeEnum::Body)
      .Case("inline-body", LowerVectorizationsModeEnum::InlineBody)
      .Case("Full", LowerVectorizationsModeEnum::Full)
      .Default(::std::nullopt);
}
::std::optional<LowerVectorizationsModeEnum> symbolizeLowerVectorizationsModeEnum(uint32_t value) {
  switch (value) {
  case 0: return LowerVectorizationsModeEnum::Boundary;
  case 1: return LowerVectorizationsModeEnum::Body;
  case 2: return LowerVectorizationsModeEnum::InlineBody;
  case 3: return LowerVectorizationsModeEnum::Full;
  default: return ::std::nullopt;
  }
}

bool LowerVectorizationsModeEnumAttr::classof(::mlir::Attribute attr) {
  return (((::llvm::isa<::mlir::IntegerAttr>(attr))) && ((::llvm::cast<::mlir::IntegerAttr>(attr).getType().isSignlessInteger(32)))) && (((
    ::llvm::cast<::mlir::IntegerAttr>(attr).getValue().eq(::llvm::APInt(32, 0)))) || ((
    ::llvm::cast<::mlir::IntegerAttr>(attr).getValue().eq(::llvm::APInt(32, 1)))) || ((
    ::llvm::cast<::mlir::IntegerAttr>(attr).getValue().eq(::llvm::APInt(32, 2)))) || ((
    ::llvm::cast<::mlir::IntegerAttr>(attr).getValue().eq(::llvm::APInt(32, 3)))));
}
LowerVectorizationsModeEnumAttr LowerVectorizationsModeEnumAttr::get(::mlir::MLIRContext *context, LowerVectorizationsModeEnum val) {
  ::mlir::IntegerType intType = ::mlir::IntegerType::get(context, 32);
  ::mlir::IntegerAttr baseAttr = ::mlir::IntegerAttr::get(intType, static_cast<uint32_t>(val));
  return ::llvm::cast<LowerVectorizationsModeEnumAttr>(baseAttr);
}
LowerVectorizationsModeEnum LowerVectorizationsModeEnumAttr::getValue() const {
  return static_cast<LowerVectorizationsModeEnum>(::mlir::IntegerAttr::getValue().getZExtValue());
}

} // namespace circt::arc
