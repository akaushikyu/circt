/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Enum Utility Definitions                                                   *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: LTL.td                                                               *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace circt::ltl {

::llvm::StringRef stringifyClockEdge(ClockEdge val) {
  switch (val) {
    case ClockEdge::Pos: return "posedge";
    case ClockEdge::Neg: return "negedge";
    case ClockEdge::Both: return "edge";
  }
  return "";
}

::std::optional<ClockEdge> symbolizeClockEdge(::llvm::StringRef str) {
  return ::llvm::StringSwitch<::std::optional<ClockEdge>>(str)
      .Case("posedge", ClockEdge::Pos)
      .Case("negedge", ClockEdge::Neg)
      .Case("edge", ClockEdge::Both)
      .Default(::std::nullopt);
}
::std::optional<ClockEdge> symbolizeClockEdge(uint32_t value) {
  switch (value) {
  case 0: return ClockEdge::Pos;
  case 1: return ClockEdge::Neg;
  case 2: return ClockEdge::Both;
  default: return ::std::nullopt;
  }
}

bool ClockEdgeAttr::classof(::mlir::Attribute attr) {
  return (((::llvm::isa<::mlir::IntegerAttr>(attr))) && ((::llvm::cast<::mlir::IntegerAttr>(attr).getType().isSignlessInteger(32)))) && (((
    ::llvm::cast<::mlir::IntegerAttr>(attr).getValue().eq(::llvm::APInt(32, 0)))) || ((
    ::llvm::cast<::mlir::IntegerAttr>(attr).getValue().eq(::llvm::APInt(32, 1)))) || ((
    ::llvm::cast<::mlir::IntegerAttr>(attr).getValue().eq(::llvm::APInt(32, 2)))));
}
ClockEdgeAttr ClockEdgeAttr::get(::mlir::MLIRContext *context, ClockEdge val) {
  ::mlir::IntegerType intType = ::mlir::IntegerType::get(context, 32);
  ::mlir::IntegerAttr baseAttr = ::mlir::IntegerAttr::get(intType, static_cast<uint32_t>(val));
  return ::llvm::cast<ClockEdgeAttr>(baseAttr);
}
ClockEdge ClockEdgeAttr::getValue() const {
  return static_cast<ClockEdge>(::mlir::IntegerAttr::getValue().getZExtValue());
}

} // namespace circt::ltl
