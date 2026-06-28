/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Enum Utility Definitions                                                   *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: HWEnums.td                                                           *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace circt::hw {

::llvm::StringRef stringifyEventControl(EventControl val) {
  switch (val) {
    case EventControl::AtPosEdge: return "posedge";
    case EventControl::AtNegEdge: return "negedge";
    case EventControl::AtEdge: return "edge";
  }
  return "";
}

::std::optional<EventControl> symbolizeEventControl(::llvm::StringRef str) {
  return ::llvm::StringSwitch<::std::optional<EventControl>>(str)
      .Case("posedge", EventControl::AtPosEdge)
      .Case("negedge", EventControl::AtNegEdge)
      .Case("edge", EventControl::AtEdge)
      .Default(::std::nullopt);
}
::std::optional<EventControl> symbolizeEventControl(uint32_t value) {
  switch (value) {
  case 0: return EventControl::AtPosEdge;
  case 1: return EventControl::AtNegEdge;
  case 2: return EventControl::AtEdge;
  default: return ::std::nullopt;
  }
}

bool EventControlAttr::classof(::mlir::Attribute attr) {
  return (((::llvm::isa<::mlir::IntegerAttr>(attr))) && ((::llvm::cast<::mlir::IntegerAttr>(attr).getType().isSignlessInteger(32)))) && (((
    ::llvm::cast<::mlir::IntegerAttr>(attr).getValue().eq(::llvm::APInt(32, 0)))) || ((
    ::llvm::cast<::mlir::IntegerAttr>(attr).getValue().eq(::llvm::APInt(32, 1)))) || ((
    ::llvm::cast<::mlir::IntegerAttr>(attr).getValue().eq(::llvm::APInt(32, 2)))));
}
EventControlAttr EventControlAttr::get(::mlir::MLIRContext *context, EventControl val) {
  ::mlir::IntegerType intType = ::mlir::IntegerType::get(context, 32);
  ::mlir::IntegerAttr baseAttr = ::mlir::IntegerAttr::get(intType, static_cast<uint32_t>(val));
  return ::llvm::cast<EventControlAttr>(baseAttr);
}
EventControl EventControlAttr::getValue() const {
  return static_cast<EventControl>(::mlir::IntegerAttr::getValue().getZExtValue());
}

} // namespace circt::hw
namespace circt::hw {

::llvm::StringRef stringifyPEO(PEO val) {
  switch (val) {
    case PEO::Add: return "add";
    case PEO::Mul: return "mul";
    case PEO::And: return "and";
    case PEO::Or: return "or";
    case PEO::Xor: return "xor";
    case PEO::Shl: return "shl";
    case PEO::ShrU: return "shru";
    case PEO::ShrS: return "shrs";
    case PEO::DivU: return "divu";
    case PEO::DivS: return "divs";
    case PEO::ModU: return "modu";
    case PEO::ModS: return "mods";
    case PEO::CLog2: return "clog2";
    case PEO::StrConcat: return "str.concat";
  }
  return "";
}

::std::optional<PEO> symbolizePEO(::llvm::StringRef str) {
  return ::llvm::StringSwitch<::std::optional<PEO>>(str)
      .Case("add", PEO::Add)
      .Case("mul", PEO::Mul)
      .Case("and", PEO::And)
      .Case("or", PEO::Or)
      .Case("xor", PEO::Xor)
      .Case("shl", PEO::Shl)
      .Case("shru", PEO::ShrU)
      .Case("shrs", PEO::ShrS)
      .Case("divu", PEO::DivU)
      .Case("divs", PEO::DivS)
      .Case("modu", PEO::ModU)
      .Case("mods", PEO::ModS)
      .Case("clog2", PEO::CLog2)
      .Case("str.concat", PEO::StrConcat)
      .Default(::std::nullopt);
}
::std::optional<PEO> symbolizePEO(uint32_t value) {
  switch (value) {
  case 0: return PEO::Add;
  case 1: return PEO::Mul;
  case 2: return PEO::And;
  case 3: return PEO::Or;
  case 4: return PEO::Xor;
  case 5: return PEO::Shl;
  case 6: return PEO::ShrU;
  case 7: return PEO::ShrS;
  case 8: return PEO::DivU;
  case 9: return PEO::DivS;
  case 10: return PEO::ModU;
  case 11: return PEO::ModS;
  case 12: return PEO::CLog2;
  case 13: return PEO::StrConcat;
  default: return ::std::nullopt;
  }
}

bool PEOAttr::classof(::mlir::Attribute attr) {
  return (((::llvm::isa<::mlir::IntegerAttr>(attr))) && ((::llvm::cast<::mlir::IntegerAttr>(attr).getType().isSignlessInteger(32)))) && (((
    ::llvm::cast<::mlir::IntegerAttr>(attr).getValue().eq(::llvm::APInt(32, 0)))) || ((
    ::llvm::cast<::mlir::IntegerAttr>(attr).getValue().eq(::llvm::APInt(32, 1)))) || ((
    ::llvm::cast<::mlir::IntegerAttr>(attr).getValue().eq(::llvm::APInt(32, 2)))) || ((
    ::llvm::cast<::mlir::IntegerAttr>(attr).getValue().eq(::llvm::APInt(32, 3)))) || ((
    ::llvm::cast<::mlir::IntegerAttr>(attr).getValue().eq(::llvm::APInt(32, 4)))) || ((
    ::llvm::cast<::mlir::IntegerAttr>(attr).getValue().eq(::llvm::APInt(32, 5)))) || ((
    ::llvm::cast<::mlir::IntegerAttr>(attr).getValue().eq(::llvm::APInt(32, 6)))) || ((
    ::llvm::cast<::mlir::IntegerAttr>(attr).getValue().eq(::llvm::APInt(32, 7)))) || ((
    ::llvm::cast<::mlir::IntegerAttr>(attr).getValue().eq(::llvm::APInt(32, 8)))) || ((
    ::llvm::cast<::mlir::IntegerAttr>(attr).getValue().eq(::llvm::APInt(32, 9)))) || ((
    ::llvm::cast<::mlir::IntegerAttr>(attr).getValue().eq(::llvm::APInt(32, 10)))) || ((
    ::llvm::cast<::mlir::IntegerAttr>(attr).getValue().eq(::llvm::APInt(32, 11)))) || ((
    ::llvm::cast<::mlir::IntegerAttr>(attr).getValue().eq(::llvm::APInt(32, 12)))) || ((
    ::llvm::cast<::mlir::IntegerAttr>(attr).getValue().eq(::llvm::APInt(32, 13)))));
}
PEOAttr PEOAttr::get(::mlir::MLIRContext *context, PEO val) {
  ::mlir::IntegerType intType = ::mlir::IntegerType::get(context, 32);
  ::mlir::IntegerAttr baseAttr = ::mlir::IntegerAttr::get(intType, static_cast<uint32_t>(val));
  return ::llvm::cast<PEOAttr>(baseAttr);
}
PEO PEOAttr::getValue() const {
  return static_cast<PEO>(::mlir::IntegerAttr::getValue().getZExtValue());
}

} // namespace circt::hw
