/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Enum Utility Definitions                                                   *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: RTG.td                                                               *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace circt::rtg {

::llvm::StringRef stringifyLabelVisibility(LabelVisibility val) {
  switch (val) {
    case LabelVisibility::local: return "local";
    case LabelVisibility::global: return "global";
    case LabelVisibility::external: return "external";
  }
  return "";
}

::std::optional<LabelVisibility> symbolizeLabelVisibility(::llvm::StringRef str) {
  return ::llvm::StringSwitch<::std::optional<LabelVisibility>>(str)
      .Case("local", LabelVisibility::local)
      .Case("global", LabelVisibility::global)
      .Case("external", LabelVisibility::external)
      .Default(::std::nullopt);
}
::std::optional<LabelVisibility> symbolizeLabelVisibility(uint32_t value) {
  switch (value) {
  case 0: return LabelVisibility::local;
  case 1: return LabelVisibility::global;
  case 2: return LabelVisibility::external;
  default: return ::std::nullopt;
  }
}

bool LabelVisibilityAttr::classof(::mlir::Attribute attr) {
  return (((::llvm::isa<::mlir::IntegerAttr>(attr))) && ((::llvm::cast<::mlir::IntegerAttr>(attr).getType().isSignlessInteger(32)))) && (((
    ::llvm::cast<::mlir::IntegerAttr>(attr).getValue().eq(::llvm::APInt(32, 0)))) || ((
    ::llvm::cast<::mlir::IntegerAttr>(attr).getValue().eq(::llvm::APInt(32, 1)))) || ((
    ::llvm::cast<::mlir::IntegerAttr>(attr).getValue().eq(::llvm::APInt(32, 2)))));
}
LabelVisibilityAttr LabelVisibilityAttr::get(::mlir::MLIRContext *context, LabelVisibility val) {
  ::mlir::IntegerType intType = ::mlir::IntegerType::get(context, 32);
  ::mlir::IntegerAttr baseAttr = ::mlir::IntegerAttr::get(intType, static_cast<uint32_t>(val));
  return ::llvm::cast<LabelVisibilityAttr>(baseAttr);
}
LabelVisibility LabelVisibilityAttr::getValue() const {
  return static_cast<LabelVisibility>(::mlir::IntegerAttr::getValue().getZExtValue());
}

} // namespace circt::rtg
namespace circt::rtg {

::llvm::StringRef stringifySegmentKind(SegmentKind val) {
  switch (val) {
    case SegmentKind::Data: return "data";
    case SegmentKind::Text: return "text";
  }
  return "";
}

::std::optional<SegmentKind> symbolizeSegmentKind(::llvm::StringRef str) {
  return ::llvm::StringSwitch<::std::optional<SegmentKind>>(str)
      .Case("data", SegmentKind::Data)
      .Case("text", SegmentKind::Text)
      .Default(::std::nullopt);
}
::std::optional<SegmentKind> symbolizeSegmentKind(uint32_t value) {
  switch (value) {
  case 0: return SegmentKind::Data;
  case 1: return SegmentKind::Text;
  default: return ::std::nullopt;
  }
}

bool SegmentKindAttr::classof(::mlir::Attribute attr) {
  return (((::llvm::isa<::mlir::IntegerAttr>(attr))) && ((::llvm::cast<::mlir::IntegerAttr>(attr).getType().isSignlessInteger(32)))) && (((
    ::llvm::cast<::mlir::IntegerAttr>(attr).getValue().eq(::llvm::APInt(32, 0)))) || ((
    ::llvm::cast<::mlir::IntegerAttr>(attr).getValue().eq(::llvm::APInt(32, 1)))));
}
SegmentKindAttr SegmentKindAttr::get(::mlir::MLIRContext *context, SegmentKind val) {
  ::mlir::IntegerType intType = ::mlir::IntegerType::get(context, 32);
  ::mlir::IntegerAttr baseAttr = ::mlir::IntegerAttr::get(intType, static_cast<uint32_t>(val));
  return ::llvm::cast<SegmentKindAttr>(baseAttr);
}
SegmentKind SegmentKindAttr::getValue() const {
  return static_cast<SegmentKind>(::mlir::IntegerAttr::getValue().getZExtValue());
}

} // namespace circt::rtg
