/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Enum Utility Definitions                                                   *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: ESI.td                                                               *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace circt::esi {

::llvm::StringRef stringifyChannelDirection(ChannelDirection val) {
  switch (val) {
    case ChannelDirection::to: return "to";
    case ChannelDirection::from: return "from";
  }
  return "";
}

::std::optional<ChannelDirection> symbolizeChannelDirection(::llvm::StringRef str) {
  return ::llvm::StringSwitch<::std::optional<ChannelDirection>>(str)
      .Case("to", ChannelDirection::to)
      .Case("from", ChannelDirection::from)
      .Default(::std::nullopt);
}
::std::optional<ChannelDirection> symbolizeChannelDirection(uint32_t value) {
  switch (value) {
  case 1: return ChannelDirection::to;
  case 2: return ChannelDirection::from;
  default: return ::std::nullopt;
  }
}

bool ChannelDirectionAttr::classof(::mlir::Attribute attr) {
  return (((::llvm::isa<::mlir::IntegerAttr>(attr))) && ((::llvm::cast<::mlir::IntegerAttr>(attr).getType().isSignlessInteger(32)))) && (((
    ::llvm::cast<::mlir::IntegerAttr>(attr).getValue().eq(::llvm::APInt(32, 1)))) || ((
    ::llvm::cast<::mlir::IntegerAttr>(attr).getValue().eq(::llvm::APInt(32, 2)))));
}
ChannelDirectionAttr ChannelDirectionAttr::get(::mlir::MLIRContext *context, ChannelDirection val) {
  ::mlir::IntegerType intType = ::mlir::IntegerType::get(context, 32);
  ::mlir::IntegerAttr baseAttr = ::mlir::IntegerAttr::get(intType, static_cast<uint32_t>(val));
  return ::llvm::cast<ChannelDirectionAttr>(baseAttr);
}
ChannelDirection ChannelDirectionAttr::getValue() const {
  return static_cast<ChannelDirection>(::mlir::IntegerAttr::getValue().getZExtValue());
}

} // namespace circt::esi
namespace circt::esi {

::llvm::StringRef stringifyChannelSignaling(ChannelSignaling val) {
  switch (val) {
    case ChannelSignaling::ValidReady: return "ValidReady";
    case ChannelSignaling::FIFO: return "FIFO";
    case ChannelSignaling::ValidOnly: return "ValidOnly";
  }
  return "";
}

::std::optional<ChannelSignaling> symbolizeChannelSignaling(::llvm::StringRef str) {
  return ::llvm::StringSwitch<::std::optional<ChannelSignaling>>(str)
      .Case("ValidReady", ChannelSignaling::ValidReady)
      .Case("FIFO", ChannelSignaling::FIFO)
      .Case("ValidOnly", ChannelSignaling::ValidOnly)
      .Default(::std::nullopt);
}
::std::optional<ChannelSignaling> symbolizeChannelSignaling(uint32_t value) {
  switch (value) {
  case 0: return ChannelSignaling::ValidReady;
  case 1: return ChannelSignaling::FIFO;
  case 2: return ChannelSignaling::ValidOnly;
  default: return ::std::nullopt;
  }
}

bool ChannelSignalingAttr::classof(::mlir::Attribute attr) {
  return (((::llvm::isa<::mlir::IntegerAttr>(attr))) && ((::llvm::cast<::mlir::IntegerAttr>(attr).getType().isSignlessInteger(32)))) && (((
    ::llvm::cast<::mlir::IntegerAttr>(attr).getValue().eq(::llvm::APInt(32, 0)))) || ((
    ::llvm::cast<::mlir::IntegerAttr>(attr).getValue().eq(::llvm::APInt(32, 1)))) || ((
    ::llvm::cast<::mlir::IntegerAttr>(attr).getValue().eq(::llvm::APInt(32, 2)))));
}
ChannelSignalingAttr ChannelSignalingAttr::get(::mlir::MLIRContext *context, ChannelSignaling val) {
  ::mlir::IntegerType intType = ::mlir::IntegerType::get(context, 32);
  ::mlir::IntegerAttr baseAttr = ::mlir::IntegerAttr::get(intType, static_cast<uint32_t>(val));
  return ::llvm::cast<ChannelSignalingAttr>(baseAttr);
}
ChannelSignaling ChannelSignalingAttr::getValue() const {
  return static_cast<ChannelSignaling>(::mlir::IntegerAttr::getValue().getZExtValue());
}

} // namespace circt::esi
