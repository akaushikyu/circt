/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Enum Utility Definitions                                                   *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: OMEnums.td                                                           *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace circt::om {

::llvm::StringRef stringifyTargetKind(TargetKind val) {
  switch (val) {
    case TargetKind::DontTouch: return "dont_touch";
    case TargetKind::Instance: return "instance";
    case TargetKind::MemberInstance: return "member_instance";
    case TargetKind::MemberReference: return "member_reference";
    case TargetKind::Reference: return "reference";
  }
  return "";
}

::std::optional<TargetKind> symbolizeTargetKind(::llvm::StringRef str) {
  return ::llvm::StringSwitch<::std::optional<TargetKind>>(str)
      .Case("dont_touch", TargetKind::DontTouch)
      .Case("instance", TargetKind::Instance)
      .Case("member_instance", TargetKind::MemberInstance)
      .Case("member_reference", TargetKind::MemberReference)
      .Case("reference", TargetKind::Reference)
      .Default(::std::nullopt);
}
::std::optional<TargetKind> symbolizeTargetKind(uint32_t value) {
  switch (value) {
  case 0: return TargetKind::DontTouch;
  case 1: return TargetKind::Instance;
  case 2: return TargetKind::MemberInstance;
  case 3: return TargetKind::MemberReference;
  case 4: return TargetKind::Reference;
  default: return ::std::nullopt;
  }
}

bool TargetKindAttr::classof(::mlir::Attribute attr) {
  return (((::llvm::isa<::mlir::IntegerAttr>(attr))) && ((::llvm::cast<::mlir::IntegerAttr>(attr).getType().isSignlessInteger(32)))) && (((
    ::llvm::cast<::mlir::IntegerAttr>(attr).getValue().eq(::llvm::APInt(32, 0)))) || ((
    ::llvm::cast<::mlir::IntegerAttr>(attr).getValue().eq(::llvm::APInt(32, 1)))) || ((
    ::llvm::cast<::mlir::IntegerAttr>(attr).getValue().eq(::llvm::APInt(32, 2)))) || ((
    ::llvm::cast<::mlir::IntegerAttr>(attr).getValue().eq(::llvm::APInt(32, 3)))) || ((
    ::llvm::cast<::mlir::IntegerAttr>(attr).getValue().eq(::llvm::APInt(32, 4)))));
}
TargetKindAttr TargetKindAttr::get(::mlir::MLIRContext *context, TargetKind val) {
  ::mlir::IntegerType intType = ::mlir::IntegerType::get(context, 32);
  ::mlir::IntegerAttr baseAttr = ::mlir::IntegerAttr::get(intType, static_cast<uint32_t>(val));
  return ::llvm::cast<TargetKindAttr>(baseAttr);
}
TargetKind TargetKindAttr::getValue() const {
  return static_cast<TargetKind>(::mlir::IntegerAttr::getValue().getZExtValue());
}

} // namespace circt::om
