/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Enum Utility Definitions                                                   *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: SystemC.td                                                           *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

::llvm::StringRef stringifyMemberAccessKind(MemberAccessKind val) {
  switch (val) {
    case MemberAccessKind::Dot: return "dot";
    case MemberAccessKind::Arrow: return "arrow";
  }
  return "";
}

::std::optional<MemberAccessKind> symbolizeMemberAccessKind(::llvm::StringRef str) {
  return ::llvm::StringSwitch<::std::optional<MemberAccessKind>>(str)
      .Case("dot", MemberAccessKind::Dot)
      .Case("arrow", MemberAccessKind::Arrow)
      .Default(::std::nullopt);
}
::std::optional<MemberAccessKind> symbolizeMemberAccessKind(uint32_t value) {
  switch (value) {
  case 0: return MemberAccessKind::Dot;
  case 1: return MemberAccessKind::Arrow;
  default: return ::std::nullopt;
  }
}

bool MemberAccessKindAttr::classof(::mlir::Attribute attr) {
  return (((::llvm::isa<::mlir::IntegerAttr>(attr))) && ((::llvm::cast<::mlir::IntegerAttr>(attr).getType().isSignlessInteger(32)))) && (((
    ::llvm::cast<::mlir::IntegerAttr>(attr).getValue().eq(::llvm::APInt(32, 0)))) || ((
    ::llvm::cast<::mlir::IntegerAttr>(attr).getValue().eq(::llvm::APInt(32, 1)))));
}
MemberAccessKindAttr MemberAccessKindAttr::get(::mlir::MLIRContext *context, MemberAccessKind val) {
  ::mlir::IntegerType intType = ::mlir::IntegerType::get(context, 32);
  ::mlir::IntegerAttr baseAttr = ::mlir::IntegerAttr::get(intType, static_cast<uint32_t>(val));
  return ::llvm::cast<MemberAccessKindAttr>(baseAttr);
}
MemberAccessKind MemberAccessKindAttr::getValue() const {
  return static_cast<MemberAccessKind>(::mlir::IntegerAttr::getValue().getZExtValue());
}
