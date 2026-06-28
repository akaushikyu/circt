/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Enum Utility Definitions                                                   *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: Seq.td                                                               *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace circt::seq {

::llvm::StringRef stringifyClockConst(ClockConst val) {
  switch (val) {
    case ClockConst::Low: return "low";
    case ClockConst::High: return "high";
  }
  return "";
}

::std::optional<ClockConst> symbolizeClockConst(::llvm::StringRef str) {
  return ::llvm::StringSwitch<::std::optional<ClockConst>>(str)
      .Case("low", ClockConst::Low)
      .Case("high", ClockConst::High)
      .Default(::std::nullopt);
}
::std::optional<ClockConst> symbolizeClockConst(uint32_t value) {
  switch (value) {
  case 0: return ClockConst::Low;
  case 1: return ClockConst::High;
  default: return ::std::nullopt;
  }
}


} // namespace circt::seq
namespace circt::seq {

::llvm::StringRef stringifyRUW(RUW val) {
  switch (val) {
    case RUW::Undefined: return "undefined";
    case RUW::Old: return "old";
    case RUW::New: return "new";
  }
  return "";
}

::std::optional<RUW> symbolizeRUW(::llvm::StringRef str) {
  return ::llvm::StringSwitch<::std::optional<RUW>>(str)
      .Case("undefined", RUW::Undefined)
      .Case("old", RUW::Old)
      .Case("new", RUW::New)
      .Default(::std::nullopt);
}
::std::optional<RUW> symbolizeRUW(uint32_t value) {
  switch (value) {
  case 0: return RUW::Undefined;
  case 1: return RUW::Old;
  case 2: return RUW::New;
  default: return ::std::nullopt;
  }
}

bool RUWAttr::classof(::mlir::Attribute attr) {
  return (((::llvm::isa<::mlir::IntegerAttr>(attr))) && ((::llvm::cast<::mlir::IntegerAttr>(attr).getType().isSignlessInteger(32)))) && (((
    ::llvm::cast<::mlir::IntegerAttr>(attr).getValue().eq(::llvm::APInt(32, 0)))) || ((
    ::llvm::cast<::mlir::IntegerAttr>(attr).getValue().eq(::llvm::APInt(32, 1)))) || ((
    ::llvm::cast<::mlir::IntegerAttr>(attr).getValue().eq(::llvm::APInt(32, 2)))));
}
RUWAttr RUWAttr::get(::mlir::MLIRContext *context, RUW val) {
  ::mlir::IntegerType intType = ::mlir::IntegerType::get(context, 32);
  ::mlir::IntegerAttr baseAttr = ::mlir::IntegerAttr::get(intType, static_cast<uint32_t>(val));
  return ::llvm::cast<RUWAttr>(baseAttr);
}
RUW RUWAttr::getValue() const {
  return static_cast<RUW>(::mlir::IntegerAttr::getValue().getZExtValue());
}

} // namespace circt::seq
namespace circt::seq {

::llvm::StringRef stringifyWUW(WUW val) {
  switch (val) {
    case WUW::Undefined: return "undefined";
    case WUW::PortOrder: return "port_order";
  }
  return "";
}

::std::optional<WUW> symbolizeWUW(::llvm::StringRef str) {
  return ::llvm::StringSwitch<::std::optional<WUW>>(str)
      .Case("undefined", WUW::Undefined)
      .Case("port_order", WUW::PortOrder)
      .Default(::std::nullopt);
}
::std::optional<WUW> symbolizeWUW(uint32_t value) {
  switch (value) {
  case 0: return WUW::Undefined;
  case 1: return WUW::PortOrder;
  default: return ::std::nullopt;
  }
}

bool WUWAttr::classof(::mlir::Attribute attr) {
  return (((::llvm::isa<::mlir::IntegerAttr>(attr))) && ((::llvm::cast<::mlir::IntegerAttr>(attr).getType().isSignlessInteger(32)))) && (((
    ::llvm::cast<::mlir::IntegerAttr>(attr).getValue().eq(::llvm::APInt(32, 0)))) || ((
    ::llvm::cast<::mlir::IntegerAttr>(attr).getValue().eq(::llvm::APInt(32, 1)))));
}
WUWAttr WUWAttr::get(::mlir::MLIRContext *context, WUW val) {
  ::mlir::IntegerType intType = ::mlir::IntegerType::get(context, 32);
  ::mlir::IntegerAttr baseAttr = ::mlir::IntegerAttr::get(intType, static_cast<uint32_t>(val));
  return ::llvm::cast<WUWAttr>(baseAttr);
}
WUW WUWAttr::getValue() const {
  return static_cast<WUW>(::mlir::IntegerAttr::getValue().getZExtValue());
}

} // namespace circt::seq
