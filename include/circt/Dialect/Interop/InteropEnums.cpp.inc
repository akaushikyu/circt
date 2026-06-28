/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Enum Utility Definitions                                                   *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: Interop.td                                                           *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

::llvm::StringRef stringifyInteropMechanism(InteropMechanism val) {
  switch (val) {
    case InteropMechanism::CFFI: return "cffi";
    case InteropMechanism::CPP: return "cpp";
  }
  return "";
}

::std::optional<InteropMechanism> symbolizeInteropMechanism(::llvm::StringRef str) {
  return ::llvm::StringSwitch<::std::optional<InteropMechanism>>(str)
      .Case("cffi", InteropMechanism::CFFI)
      .Case("cpp", InteropMechanism::CPP)
      .Default(::std::nullopt);
}
::std::optional<InteropMechanism> symbolizeInteropMechanism(uint32_t value) {
  switch (value) {
  case 0: return InteropMechanism::CFFI;
  case 1: return InteropMechanism::CPP;
  default: return ::std::nullopt;
  }
}

bool InteropMechanismAttr::classof(::mlir::Attribute attr) {
  return (((::llvm::isa<::mlir::IntegerAttr>(attr))) && ((::llvm::cast<::mlir::IntegerAttr>(attr).getType().isSignlessInteger(32)))) && (((
    ::llvm::cast<::mlir::IntegerAttr>(attr).getValue().eq(::llvm::APInt(32, 0)))) || ((
    ::llvm::cast<::mlir::IntegerAttr>(attr).getValue().eq(::llvm::APInt(32, 1)))));
}
InteropMechanismAttr InteropMechanismAttr::get(::mlir::MLIRContext *context, InteropMechanism val) {
  ::mlir::IntegerType intType = ::mlir::IntegerType::get(context, 32);
  ::mlir::IntegerAttr baseAttr = ::mlir::IntegerAttr::get(intType, static_cast<uint32_t>(val));
  return ::llvm::cast<InteropMechanismAttr>(baseAttr);
}
InteropMechanism InteropMechanismAttr::getValue() const {
  return static_cast<InteropMechanism>(::mlir::IntegerAttr::getValue().getZExtValue());
}
