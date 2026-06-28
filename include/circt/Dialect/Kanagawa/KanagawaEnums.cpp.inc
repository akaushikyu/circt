/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Enum Utility Definitions                                                   *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: Kanagawa.td                                                          *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace circt::kanagawa {

::llvm::StringRef stringifyDirection(Direction val) {
  switch (val) {
    case Direction::Input: return "in";
    case Direction::Output: return "out";
  }
  return "";
}

::std::optional<Direction> symbolizeDirection(::llvm::StringRef str) {
  return ::llvm::StringSwitch<::std::optional<Direction>>(str)
      .Case("in", Direction::Input)
      .Case("out", Direction::Output)
      .Default(::std::nullopt);
}
::std::optional<Direction> symbolizeDirection(uint32_t value) {
  switch (value) {
  case 0: return Direction::Input;
  case 1: return Direction::Output;
  default: return ::std::nullopt;
  }
}

bool DirectionAttr::classof(::mlir::Attribute attr) {
  return (((::llvm::isa<::mlir::IntegerAttr>(attr))) && ((::llvm::cast<::mlir::IntegerAttr>(attr).getType().isSignlessInteger(32)))) && (((
    ::llvm::cast<::mlir::IntegerAttr>(attr).getValue().eq(::llvm::APInt(32, 0)))) || ((
    ::llvm::cast<::mlir::IntegerAttr>(attr).getValue().eq(::llvm::APInt(32, 1)))));
}
DirectionAttr DirectionAttr::get(::mlir::MLIRContext *context, Direction val) {
  ::mlir::IntegerType intType = ::mlir::IntegerType::get(context, 32);
  ::mlir::IntegerAttr baseAttr = ::mlir::IntegerAttr::get(intType, static_cast<uint32_t>(val));
  return ::llvm::cast<DirectionAttr>(baseAttr);
}
Direction DirectionAttr::getValue() const {
  return static_cast<Direction>(::mlir::IntegerAttr::getValue().getZExtValue());
}

} // namespace circt::kanagawa
namespace circt::kanagawa {

::llvm::StringRef stringifyPathDirection(PathDirection val) {
  switch (val) {
    case PathDirection::Parent: return "parent";
    case PathDirection::Child: return "child";
  }
  return "";
}

::std::optional<PathDirection> symbolizePathDirection(::llvm::StringRef str) {
  return ::llvm::StringSwitch<::std::optional<PathDirection>>(str)
      .Case("parent", PathDirection::Parent)
      .Case("child", PathDirection::Child)
      .Default(::std::nullopt);
}
::std::optional<PathDirection> symbolizePathDirection(uint32_t value) {
  switch (value) {
  case 0: return PathDirection::Parent;
  case 1: return PathDirection::Child;
  default: return ::std::nullopt;
  }
}

bool PathDirectionAttr::classof(::mlir::Attribute attr) {
  return (((::llvm::isa<::mlir::IntegerAttr>(attr))) && ((::llvm::cast<::mlir::IntegerAttr>(attr).getType().isSignlessInteger(32)))) && (((
    ::llvm::cast<::mlir::IntegerAttr>(attr).getValue().eq(::llvm::APInt(32, 0)))) || ((
    ::llvm::cast<::mlir::IntegerAttr>(attr).getValue().eq(::llvm::APInt(32, 1)))));
}
PathDirectionAttr PathDirectionAttr::get(::mlir::MLIRContext *context, PathDirection val) {
  ::mlir::IntegerType intType = ::mlir::IntegerType::get(context, 32);
  ::mlir::IntegerAttr baseAttr = ::mlir::IntegerAttr::get(intType, static_cast<uint32_t>(val));
  return ::llvm::cast<PathDirectionAttr>(baseAttr);
}
PathDirection PathDirectionAttr::getValue() const {
  return static_cast<PathDirection>(::mlir::IntegerAttr::getValue().getZExtValue());
}

} // namespace circt::kanagawa
