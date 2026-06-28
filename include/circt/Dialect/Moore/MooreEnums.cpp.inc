/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Enum Utility Definitions                                                   *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: Moore.td                                                             *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace circt::moore {

::llvm::StringRef stringifyDPIArgDirection(DPIArgDirection val) {
  switch (val) {
    case DPIArgDirection::In: return "in";
    case DPIArgDirection::Out: return "out";
    case DPIArgDirection::InOut: return "inout";
    case DPIArgDirection::Return: return "return";
  }
  return "";
}

::std::optional<DPIArgDirection> symbolizeDPIArgDirection(::llvm::StringRef str) {
  return ::llvm::StringSwitch<::std::optional<DPIArgDirection>>(str)
      .Case("in", DPIArgDirection::In)
      .Case("out", DPIArgDirection::Out)
      .Case("inout", DPIArgDirection::InOut)
      .Case("return", DPIArgDirection::Return)
      .Default(::std::nullopt);
}
::std::optional<DPIArgDirection> symbolizeDPIArgDirection(uint32_t value) {
  switch (value) {
  case 0: return DPIArgDirection::In;
  case 1: return DPIArgDirection::Out;
  case 2: return DPIArgDirection::InOut;
  case 3: return DPIArgDirection::Return;
  default: return ::std::nullopt;
  }
}

bool DPIArgDirectionAttr::classof(::mlir::Attribute attr) {
  return (((::llvm::isa<::mlir::IntegerAttr>(attr))) && ((::llvm::cast<::mlir::IntegerAttr>(attr).getType().isSignlessInteger(32)))) && (((
    ::llvm::cast<::mlir::IntegerAttr>(attr).getValue().eq(::llvm::APInt(32, 0)))) || ((
    ::llvm::cast<::mlir::IntegerAttr>(attr).getValue().eq(::llvm::APInt(32, 1)))) || ((
    ::llvm::cast<::mlir::IntegerAttr>(attr).getValue().eq(::llvm::APInt(32, 2)))) || ((
    ::llvm::cast<::mlir::IntegerAttr>(attr).getValue().eq(::llvm::APInt(32, 3)))));
}
DPIArgDirectionAttr DPIArgDirectionAttr::get(::mlir::MLIRContext *context, DPIArgDirection val) {
  ::mlir::IntegerType intType = ::mlir::IntegerType::get(context, 32);
  ::mlir::IntegerAttr baseAttr = ::mlir::IntegerAttr::get(intType, static_cast<uint32_t>(val));
  return ::llvm::cast<DPIArgDirectionAttr>(baseAttr);
}
DPIArgDirection DPIArgDirectionAttr::getValue() const {
  return static_cast<DPIArgDirection>(::mlir::IntegerAttr::getValue().getZExtValue());
}

} // namespace circt::moore
namespace circt::moore {

::llvm::StringRef stringifyDeferAssert(DeferAssert val) {
  switch (val) {
    case DeferAssert::Immediate: return "immediate";
    case DeferAssert::Observed: return "observed";
    case DeferAssert::Final: return "final";
  }
  return "";
}

::std::optional<DeferAssert> symbolizeDeferAssert(::llvm::StringRef str) {
  return ::llvm::StringSwitch<::std::optional<DeferAssert>>(str)
      .Case("immediate", DeferAssert::Immediate)
      .Case("observed", DeferAssert::Observed)
      .Case("final", DeferAssert::Final)
      .Default(::std::nullopt);
}
::std::optional<DeferAssert> symbolizeDeferAssert(uint32_t value) {
  switch (value) {
  case 0: return DeferAssert::Immediate;
  case 1: return DeferAssert::Observed;
  case 2: return DeferAssert::Final;
  default: return ::std::nullopt;
  }
}

bool DeferAssertAttr::classof(::mlir::Attribute attr) {
  return (((::llvm::isa<::mlir::IntegerAttr>(attr))) && ((::llvm::cast<::mlir::IntegerAttr>(attr).getType().isSignlessInteger(32)))) && (((
    ::llvm::cast<::mlir::IntegerAttr>(attr).getValue().eq(::llvm::APInt(32, 0)))) || ((
    ::llvm::cast<::mlir::IntegerAttr>(attr).getValue().eq(::llvm::APInt(32, 1)))) || ((
    ::llvm::cast<::mlir::IntegerAttr>(attr).getValue().eq(::llvm::APInt(32, 2)))));
}
DeferAssertAttr DeferAssertAttr::get(::mlir::MLIRContext *context, DeferAssert val) {
  ::mlir::IntegerType intType = ::mlir::IntegerType::get(context, 32);
  ::mlir::IntegerAttr baseAttr = ::mlir::IntegerAttr::get(intType, static_cast<uint32_t>(val));
  return ::llvm::cast<DeferAssertAttr>(baseAttr);
}
DeferAssert DeferAssertAttr::getValue() const {
  return static_cast<DeferAssert>(::mlir::IntegerAttr::getValue().getZExtValue());
}

} // namespace circt::moore
namespace circt::moore {

::llvm::StringRef stringifyEdge(Edge val) {
  switch (val) {
    case Edge::AnyChange: return "any";
    case Edge::PosEdge: return "posedge";
    case Edge::NegEdge: return "negedge";
    case Edge::BothEdges: return "edge";
  }
  return "";
}

::std::optional<Edge> symbolizeEdge(::llvm::StringRef str) {
  return ::llvm::StringSwitch<::std::optional<Edge>>(str)
      .Case("any", Edge::AnyChange)
      .Case("posedge", Edge::PosEdge)
      .Case("negedge", Edge::NegEdge)
      .Case("edge", Edge::BothEdges)
      .Default(::std::nullopt);
}
::std::optional<Edge> symbolizeEdge(uint32_t value) {
  switch (value) {
  case 0: return Edge::AnyChange;
  case 1: return Edge::PosEdge;
  case 2: return Edge::NegEdge;
  case 3: return Edge::BothEdges;
  default: return ::std::nullopt;
  }
}

bool EdgeAttr::classof(::mlir::Attribute attr) {
  return (((::llvm::isa<::mlir::IntegerAttr>(attr))) && ((::llvm::cast<::mlir::IntegerAttr>(attr).getType().isSignlessInteger(32)))) && (((
    ::llvm::cast<::mlir::IntegerAttr>(attr).getValue().eq(::llvm::APInt(32, 0)))) || ((
    ::llvm::cast<::mlir::IntegerAttr>(attr).getValue().eq(::llvm::APInt(32, 1)))) || ((
    ::llvm::cast<::mlir::IntegerAttr>(attr).getValue().eq(::llvm::APInt(32, 2)))) || ((
    ::llvm::cast<::mlir::IntegerAttr>(attr).getValue().eq(::llvm::APInt(32, 3)))));
}
EdgeAttr EdgeAttr::get(::mlir::MLIRContext *context, Edge val) {
  ::mlir::IntegerType intType = ::mlir::IntegerType::get(context, 32);
  ::mlir::IntegerAttr baseAttr = ::mlir::IntegerAttr::get(intType, static_cast<uint32_t>(val));
  return ::llvm::cast<EdgeAttr>(baseAttr);
}
Edge EdgeAttr::getValue() const {
  return static_cast<Edge>(::mlir::IntegerAttr::getValue().getZExtValue());
}

} // namespace circt::moore
namespace circt::moore {

::llvm::StringRef stringifyFOpenMode(FOpenMode val) {
  switch (val) {
    case FOpenMode::Read: return "r";
    case FOpenMode::Write: return "w";
    case FOpenMode::Append: return "a";
    case FOpenMode::ReadUpdate: return "r_update";
    case FOpenMode::WriteUpdate: return "w_update";
    case FOpenMode::AppendUpdate: return "a_update";
  }
  return "";
}

::std::optional<FOpenMode> symbolizeFOpenMode(::llvm::StringRef str) {
  return ::llvm::StringSwitch<::std::optional<FOpenMode>>(str)
      .Case("r", FOpenMode::Read)
      .Case("w", FOpenMode::Write)
      .Case("a", FOpenMode::Append)
      .Case("r_update", FOpenMode::ReadUpdate)
      .Case("w_update", FOpenMode::WriteUpdate)
      .Case("a_update", FOpenMode::AppendUpdate)
      .Default(::std::nullopt);
}
::std::optional<FOpenMode> symbolizeFOpenMode(uint32_t value) {
  switch (value) {
  case 0: return FOpenMode::Read;
  case 1: return FOpenMode::Write;
  case 2: return FOpenMode::Append;
  case 3: return FOpenMode::ReadUpdate;
  case 4: return FOpenMode::WriteUpdate;
  case 5: return FOpenMode::AppendUpdate;
  default: return ::std::nullopt;
  }
}

bool FOpenModeAttr::classof(::mlir::Attribute attr) {
  return (((::llvm::isa<::mlir::IntegerAttr>(attr))) && ((::llvm::cast<::mlir::IntegerAttr>(attr).getType().isSignlessInteger(32)))) && (((
    ::llvm::cast<::mlir::IntegerAttr>(attr).getValue().eq(::llvm::APInt(32, 0)))) || ((
    ::llvm::cast<::mlir::IntegerAttr>(attr).getValue().eq(::llvm::APInt(32, 1)))) || ((
    ::llvm::cast<::mlir::IntegerAttr>(attr).getValue().eq(::llvm::APInt(32, 2)))) || ((
    ::llvm::cast<::mlir::IntegerAttr>(attr).getValue().eq(::llvm::APInt(32, 3)))) || ((
    ::llvm::cast<::mlir::IntegerAttr>(attr).getValue().eq(::llvm::APInt(32, 4)))) || ((
    ::llvm::cast<::mlir::IntegerAttr>(attr).getValue().eq(::llvm::APInt(32, 5)))));
}
FOpenModeAttr FOpenModeAttr::get(::mlir::MLIRContext *context, FOpenMode val) {
  ::mlir::IntegerType intType = ::mlir::IntegerType::get(context, 32);
  ::mlir::IntegerAttr baseAttr = ::mlir::IntegerAttr::get(intType, static_cast<uint32_t>(val));
  return ::llvm::cast<FOpenModeAttr>(baseAttr);
}
FOpenMode FOpenModeAttr::getValue() const {
  return static_cast<FOpenMode>(::mlir::IntegerAttr::getValue().getZExtValue());
}

} // namespace circt::moore
namespace circt::moore {

::llvm::StringRef stringifyIntAlign(IntAlign val) {
  switch (val) {
    case IntAlign::Right: return "right";
    case IntAlign::Left: return "left";
  }
  return "";
}

::std::optional<IntAlign> symbolizeIntAlign(::llvm::StringRef str) {
  return ::llvm::StringSwitch<::std::optional<IntAlign>>(str)
      .Case("right", IntAlign::Right)
      .Case("left", IntAlign::Left)
      .Default(::std::nullopt);
}
::std::optional<IntAlign> symbolizeIntAlign(uint32_t value) {
  switch (value) {
  case 0: return IntAlign::Right;
  case 1: return IntAlign::Left;
  default: return ::std::nullopt;
  }
}

bool IntAlignAttr::classof(::mlir::Attribute attr) {
  return (((::llvm::isa<::mlir::IntegerAttr>(attr))) && ((::llvm::cast<::mlir::IntegerAttr>(attr).getType().isSignlessInteger(32)))) && (((
    ::llvm::cast<::mlir::IntegerAttr>(attr).getValue().eq(::llvm::APInt(32, 0)))) || ((
    ::llvm::cast<::mlir::IntegerAttr>(attr).getValue().eq(::llvm::APInt(32, 1)))));
}
IntAlignAttr IntAlignAttr::get(::mlir::MLIRContext *context, IntAlign val) {
  ::mlir::IntegerType intType = ::mlir::IntegerType::get(context, 32);
  ::mlir::IntegerAttr baseAttr = ::mlir::IntegerAttr::get(intType, static_cast<uint32_t>(val));
  return ::llvm::cast<IntAlignAttr>(baseAttr);
}
IntAlign IntAlignAttr::getValue() const {
  return static_cast<IntAlign>(::mlir::IntegerAttr::getValue().getZExtValue());
}

} // namespace circt::moore
namespace circt::moore {

::llvm::StringRef stringifyIntFormat(IntFormat val) {
  switch (val) {
    case IntFormat::Decimal: return "decimal";
    case IntFormat::Binary: return "binary";
    case IntFormat::Octal: return "octal";
    case IntFormat::HexLower: return "hex_lower";
    case IntFormat::HexUpper: return "hex_upper";
  }
  return "";
}

::std::optional<IntFormat> symbolizeIntFormat(::llvm::StringRef str) {
  return ::llvm::StringSwitch<::std::optional<IntFormat>>(str)
      .Case("decimal", IntFormat::Decimal)
      .Case("binary", IntFormat::Binary)
      .Case("octal", IntFormat::Octal)
      .Case("hex_lower", IntFormat::HexLower)
      .Case("hex_upper", IntFormat::HexUpper)
      .Default(::std::nullopt);
}
::std::optional<IntFormat> symbolizeIntFormat(uint32_t value) {
  switch (value) {
  case 0: return IntFormat::Decimal;
  case 1: return IntFormat::Binary;
  case 2: return IntFormat::Octal;
  case 3: return IntFormat::HexLower;
  case 4: return IntFormat::HexUpper;
  default: return ::std::nullopt;
  }
}

bool IntFormatAttr::classof(::mlir::Attribute attr) {
  return (((::llvm::isa<::mlir::IntegerAttr>(attr))) && ((::llvm::cast<::mlir::IntegerAttr>(attr).getType().isSignlessInteger(32)))) && (((
    ::llvm::cast<::mlir::IntegerAttr>(attr).getValue().eq(::llvm::APInt(32, 0)))) || ((
    ::llvm::cast<::mlir::IntegerAttr>(attr).getValue().eq(::llvm::APInt(32, 1)))) || ((
    ::llvm::cast<::mlir::IntegerAttr>(attr).getValue().eq(::llvm::APInt(32, 2)))) || ((
    ::llvm::cast<::mlir::IntegerAttr>(attr).getValue().eq(::llvm::APInt(32, 3)))) || ((
    ::llvm::cast<::mlir::IntegerAttr>(attr).getValue().eq(::llvm::APInt(32, 4)))));
}
IntFormatAttr IntFormatAttr::get(::mlir::MLIRContext *context, IntFormat val) {
  ::mlir::IntegerType intType = ::mlir::IntegerType::get(context, 32);
  ::mlir::IntegerAttr baseAttr = ::mlir::IntegerAttr::get(intType, static_cast<uint32_t>(val));
  return ::llvm::cast<IntFormatAttr>(baseAttr);
}
IntFormat IntFormatAttr::getValue() const {
  return static_cast<IntFormat>(::mlir::IntegerAttr::getValue().getZExtValue());
}

} // namespace circt::moore
namespace circt::moore {

::llvm::StringRef stringifyIntPadding(IntPadding val) {
  switch (val) {
    case IntPadding::Space: return "space";
    case IntPadding::Zero: return "zero";
  }
  return "";
}

::std::optional<IntPadding> symbolizeIntPadding(::llvm::StringRef str) {
  return ::llvm::StringSwitch<::std::optional<IntPadding>>(str)
      .Case("space", IntPadding::Space)
      .Case("zero", IntPadding::Zero)
      .Default(::std::nullopt);
}
::std::optional<IntPadding> symbolizeIntPadding(uint32_t value) {
  switch (value) {
  case 0: return IntPadding::Space;
  case 1: return IntPadding::Zero;
  default: return ::std::nullopt;
  }
}

bool IntPaddingAttr::classof(::mlir::Attribute attr) {
  return (((::llvm::isa<::mlir::IntegerAttr>(attr))) && ((::llvm::cast<::mlir::IntegerAttr>(attr).getType().isSignlessInteger(32)))) && (((
    ::llvm::cast<::mlir::IntegerAttr>(attr).getValue().eq(::llvm::APInt(32, 0)))) || ((
    ::llvm::cast<::mlir::IntegerAttr>(attr).getValue().eq(::llvm::APInt(32, 1)))));
}
IntPaddingAttr IntPaddingAttr::get(::mlir::MLIRContext *context, IntPadding val) {
  ::mlir::IntegerType intType = ::mlir::IntegerType::get(context, 32);
  ::mlir::IntegerAttr baseAttr = ::mlir::IntegerAttr::get(intType, static_cast<uint32_t>(val));
  return ::llvm::cast<IntPaddingAttr>(baseAttr);
}
IntPadding IntPaddingAttr::getValue() const {
  return static_cast<IntPadding>(::mlir::IntegerAttr::getValue().getZExtValue());
}

} // namespace circt::moore
namespace circt::moore {

::llvm::StringRef stringifyJoinKind(JoinKind val) {
  switch (val) {
    case JoinKind::Join: return "join_all";
    case JoinKind::JoinAny: return "join_any";
    case JoinKind::JoinNone: return "join_none";
  }
  return "";
}

::std::optional<JoinKind> symbolizeJoinKind(::llvm::StringRef str) {
  return ::llvm::StringSwitch<::std::optional<JoinKind>>(str)
      .Case("join_all", JoinKind::Join)
      .Case("join_any", JoinKind::JoinAny)
      .Case("join_none", JoinKind::JoinNone)
      .Default(::std::nullopt);
}
::std::optional<JoinKind> symbolizeJoinKind(uint32_t value) {
  switch (value) {
  case 0: return JoinKind::Join;
  case 1: return JoinKind::JoinAny;
  case 2: return JoinKind::JoinNone;
  default: return ::std::nullopt;
  }
}

bool JoinKindAttr::classof(::mlir::Attribute attr) {
  return (((::llvm::isa<::mlir::IntegerAttr>(attr))) && ((::llvm::cast<::mlir::IntegerAttr>(attr).getType().isSignlessInteger(32)))) && (((
    ::llvm::cast<::mlir::IntegerAttr>(attr).getValue().eq(::llvm::APInt(32, 0)))) || ((
    ::llvm::cast<::mlir::IntegerAttr>(attr).getValue().eq(::llvm::APInt(32, 1)))) || ((
    ::llvm::cast<::mlir::IntegerAttr>(attr).getValue().eq(::llvm::APInt(32, 2)))));
}
JoinKindAttr JoinKindAttr::get(::mlir::MLIRContext *context, JoinKind val) {
  ::mlir::IntegerType intType = ::mlir::IntegerType::get(context, 32);
  ::mlir::IntegerAttr baseAttr = ::mlir::IntegerAttr::get(intType, static_cast<uint32_t>(val));
  return ::llvm::cast<JoinKindAttr>(baseAttr);
}
JoinKind JoinKindAttr::getValue() const {
  return static_cast<JoinKind>(::mlir::IntegerAttr::getValue().getZExtValue());
}

} // namespace circt::moore
namespace circt::moore {

::llvm::StringRef stringifyNetKind(NetKind val) {
  switch (val) {
    case NetKind::Supply0: return "supply0";
    case NetKind::Supply1: return "supply1";
    case NetKind::Tri: return "tri";
    case NetKind::TriAnd: return "triand";
    case NetKind::TriOr: return "trior";
    case NetKind::TriReg: return "trireg";
    case NetKind::Tri0: return "tri0";
    case NetKind::Tri1: return "tri1";
    case NetKind::UWire: return "uwire";
    case NetKind::Wire: return "wire";
    case NetKind::WAnd: return "wand";
    case NetKind::WOr: return "wor";
    case NetKind::Interconnect: return "interconnect";
    case NetKind::UserDefined: return "userdefined";
    case NetKind::Unknown: return "unknown";
  }
  return "";
}

::std::optional<NetKind> symbolizeNetKind(::llvm::StringRef str) {
  return ::llvm::StringSwitch<::std::optional<NetKind>>(str)
      .Case("supply0", NetKind::Supply0)
      .Case("supply1", NetKind::Supply1)
      .Case("tri", NetKind::Tri)
      .Case("triand", NetKind::TriAnd)
      .Case("trior", NetKind::TriOr)
      .Case("trireg", NetKind::TriReg)
      .Case("tri0", NetKind::Tri0)
      .Case("tri1", NetKind::Tri1)
      .Case("uwire", NetKind::UWire)
      .Case("wire", NetKind::Wire)
      .Case("wand", NetKind::WAnd)
      .Case("wor", NetKind::WOr)
      .Case("interconnect", NetKind::Interconnect)
      .Case("userdefined", NetKind::UserDefined)
      .Case("unknown", NetKind::Unknown)
      .Default(::std::nullopt);
}
::std::optional<NetKind> symbolizeNetKind(uint32_t value) {
  switch (value) {
  case 0: return NetKind::Supply0;
  case 1: return NetKind::Supply1;
  case 2: return NetKind::Tri;
  case 3: return NetKind::TriAnd;
  case 4: return NetKind::TriOr;
  case 5: return NetKind::TriReg;
  case 6: return NetKind::Tri0;
  case 7: return NetKind::Tri1;
  case 8: return NetKind::UWire;
  case 9: return NetKind::Wire;
  case 10: return NetKind::WAnd;
  case 11: return NetKind::WOr;
  case 12: return NetKind::Interconnect;
  case 13: return NetKind::UserDefined;
  case 14: return NetKind::Unknown;
  default: return ::std::nullopt;
  }
}

bool NetKindAttr::classof(::mlir::Attribute attr) {
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
    ::llvm::cast<::mlir::IntegerAttr>(attr).getValue().eq(::llvm::APInt(32, 13)))) || ((
    ::llvm::cast<::mlir::IntegerAttr>(attr).getValue().eq(::llvm::APInt(32, 14)))));
}
NetKindAttr NetKindAttr::get(::mlir::MLIRContext *context, NetKind val) {
  ::mlir::IntegerType intType = ::mlir::IntegerType::get(context, 32);
  ::mlir::IntegerAttr baseAttr = ::mlir::IntegerAttr::get(intType, static_cast<uint32_t>(val));
  return ::llvm::cast<NetKindAttr>(baseAttr);
}
NetKind NetKindAttr::getValue() const {
  return static_cast<NetKind>(::mlir::IntegerAttr::getValue().getZExtValue());
}

} // namespace circt::moore
namespace circt::moore {

::llvm::StringRef stringifyProcedureKind(ProcedureKind val) {
  switch (val) {
    case ProcedureKind::Initial: return "initial";
    case ProcedureKind::Final: return "final";
    case ProcedureKind::Always: return "always";
    case ProcedureKind::AlwaysComb: return "always_comb";
    case ProcedureKind::AlwaysLatch: return "always_latch";
    case ProcedureKind::AlwaysFF: return "always_ff";
  }
  return "";
}

::std::optional<ProcedureKind> symbolizeProcedureKind(::llvm::StringRef str) {
  return ::llvm::StringSwitch<::std::optional<ProcedureKind>>(str)
      .Case("initial", ProcedureKind::Initial)
      .Case("final", ProcedureKind::Final)
      .Case("always", ProcedureKind::Always)
      .Case("always_comb", ProcedureKind::AlwaysComb)
      .Case("always_latch", ProcedureKind::AlwaysLatch)
      .Case("always_ff", ProcedureKind::AlwaysFF)
      .Default(::std::nullopt);
}
::std::optional<ProcedureKind> symbolizeProcedureKind(uint32_t value) {
  switch (value) {
  case 0: return ProcedureKind::Initial;
  case 1: return ProcedureKind::Final;
  case 2: return ProcedureKind::Always;
  case 3: return ProcedureKind::AlwaysComb;
  case 4: return ProcedureKind::AlwaysLatch;
  case 5: return ProcedureKind::AlwaysFF;
  default: return ::std::nullopt;
  }
}

bool ProcedureKindAttr::classof(::mlir::Attribute attr) {
  return (((::llvm::isa<::mlir::IntegerAttr>(attr))) && ((::llvm::cast<::mlir::IntegerAttr>(attr).getType().isSignlessInteger(32)))) && (((
    ::llvm::cast<::mlir::IntegerAttr>(attr).getValue().eq(::llvm::APInt(32, 0)))) || ((
    ::llvm::cast<::mlir::IntegerAttr>(attr).getValue().eq(::llvm::APInt(32, 1)))) || ((
    ::llvm::cast<::mlir::IntegerAttr>(attr).getValue().eq(::llvm::APInt(32, 2)))) || ((
    ::llvm::cast<::mlir::IntegerAttr>(attr).getValue().eq(::llvm::APInt(32, 3)))) || ((
    ::llvm::cast<::mlir::IntegerAttr>(attr).getValue().eq(::llvm::APInt(32, 4)))) || ((
    ::llvm::cast<::mlir::IntegerAttr>(attr).getValue().eq(::llvm::APInt(32, 5)))));
}
ProcedureKindAttr ProcedureKindAttr::get(::mlir::MLIRContext *context, ProcedureKind val) {
  ::mlir::IntegerType intType = ::mlir::IntegerType::get(context, 32);
  ::mlir::IntegerAttr baseAttr = ::mlir::IntegerAttr::get(intType, static_cast<uint32_t>(val));
  return ::llvm::cast<ProcedureKindAttr>(baseAttr);
}
ProcedureKind ProcedureKindAttr::getValue() const {
  return static_cast<ProcedureKind>(::mlir::IntegerAttr::getValue().getZExtValue());
}

} // namespace circt::moore
namespace circt::moore {

::llvm::StringRef stringifyRealFormat(RealFormat val) {
  switch (val) {
    case RealFormat::Float: return "float";
    case RealFormat::Exponential: return "exponential";
    case RealFormat::General: return "general";
  }
  return "";
}

::std::optional<RealFormat> symbolizeRealFormat(::llvm::StringRef str) {
  return ::llvm::StringSwitch<::std::optional<RealFormat>>(str)
      .Case("float", RealFormat::Float)
      .Case("exponential", RealFormat::Exponential)
      .Case("general", RealFormat::General)
      .Default(::std::nullopt);
}
::std::optional<RealFormat> symbolizeRealFormat(uint32_t value) {
  switch (value) {
  case 0: return RealFormat::Float;
  case 1: return RealFormat::Exponential;
  case 2: return RealFormat::General;
  default: return ::std::nullopt;
  }
}

bool RealFormatAttr::classof(::mlir::Attribute attr) {
  return (((::llvm::isa<::mlir::IntegerAttr>(attr))) && ((::llvm::cast<::mlir::IntegerAttr>(attr).getType().isSignlessInteger(32)))) && (((
    ::llvm::cast<::mlir::IntegerAttr>(attr).getValue().eq(::llvm::APInt(32, 0)))) || ((
    ::llvm::cast<::mlir::IntegerAttr>(attr).getValue().eq(::llvm::APInt(32, 1)))) || ((
    ::llvm::cast<::mlir::IntegerAttr>(attr).getValue().eq(::llvm::APInt(32, 2)))));
}
RealFormatAttr RealFormatAttr::get(::mlir::MLIRContext *context, RealFormat val) {
  ::mlir::IntegerType intType = ::mlir::IntegerType::get(context, 32);
  ::mlir::IntegerAttr baseAttr = ::mlir::IntegerAttr::get(intType, static_cast<uint32_t>(val));
  return ::llvm::cast<RealFormatAttr>(baseAttr);
}
RealFormat RealFormatAttr::getValue() const {
  return static_cast<RealFormat>(::mlir::IntegerAttr::getValue().getZExtValue());
}

} // namespace circt::moore
namespace circt::moore {

::llvm::StringRef stringifySeverity(Severity val) {
  switch (val) {
    case Severity::Info: return "info";
    case Severity::Warning: return "warning";
    case Severity::Error: return "error";
    case Severity::Fatal: return "fatal";
  }
  return "";
}

::std::optional<Severity> symbolizeSeverity(::llvm::StringRef str) {
  return ::llvm::StringSwitch<::std::optional<Severity>>(str)
      .Case("info", Severity::Info)
      .Case("warning", Severity::Warning)
      .Case("error", Severity::Error)
      .Case("fatal", Severity::Fatal)
      .Default(::std::nullopt);
}
::std::optional<Severity> symbolizeSeverity(uint32_t value) {
  switch (value) {
  case 0: return Severity::Info;
  case 1: return Severity::Warning;
  case 2: return Severity::Error;
  case 3: return Severity::Fatal;
  default: return ::std::nullopt;
  }
}

bool SeverityAttr::classof(::mlir::Attribute attr) {
  return (((::llvm::isa<::mlir::IntegerAttr>(attr))) && ((::llvm::cast<::mlir::IntegerAttr>(attr).getType().isSignlessInteger(32)))) && (((
    ::llvm::cast<::mlir::IntegerAttr>(attr).getValue().eq(::llvm::APInt(32, 0)))) || ((
    ::llvm::cast<::mlir::IntegerAttr>(attr).getValue().eq(::llvm::APInt(32, 1)))) || ((
    ::llvm::cast<::mlir::IntegerAttr>(attr).getValue().eq(::llvm::APInt(32, 2)))) || ((
    ::llvm::cast<::mlir::IntegerAttr>(attr).getValue().eq(::llvm::APInt(32, 3)))));
}
SeverityAttr SeverityAttr::get(::mlir::MLIRContext *context, Severity val) {
  ::mlir::IntegerType intType = ::mlir::IntegerType::get(context, 32);
  ::mlir::IntegerAttr baseAttr = ::mlir::IntegerAttr::get(intType, static_cast<uint32_t>(val));
  return ::llvm::cast<SeverityAttr>(baseAttr);
}
Severity SeverityAttr::getValue() const {
  return static_cast<Severity>(::mlir::IntegerAttr::getValue().getZExtValue());
}

} // namespace circt::moore
namespace circt::moore {

::llvm::StringRef stringifyStringCmpPredicate(StringCmpPredicate val) {
  switch (val) {
    case StringCmpPredicate::eq: return "eq";
    case StringCmpPredicate::ne: return "ne";
    case StringCmpPredicate::lt: return "lt";
    case StringCmpPredicate::le: return "le";
    case StringCmpPredicate::gt: return "gt";
    case StringCmpPredicate::ge: return "ge";
  }
  return "";
}

::std::optional<StringCmpPredicate> symbolizeStringCmpPredicate(::llvm::StringRef str) {
  return ::llvm::StringSwitch<::std::optional<StringCmpPredicate>>(str)
      .Case("eq", StringCmpPredicate::eq)
      .Case("ne", StringCmpPredicate::ne)
      .Case("lt", StringCmpPredicate::lt)
      .Case("le", StringCmpPredicate::le)
      .Case("gt", StringCmpPredicate::gt)
      .Case("ge", StringCmpPredicate::ge)
      .Default(::std::nullopt);
}
::std::optional<StringCmpPredicate> symbolizeStringCmpPredicate(uint64_t value) {
  switch (value) {
  case 0: return StringCmpPredicate::eq;
  case 1: return StringCmpPredicate::ne;
  case 2: return StringCmpPredicate::lt;
  case 3: return StringCmpPredicate::le;
  case 4: return StringCmpPredicate::gt;
  case 5: return StringCmpPredicate::ge;
  default: return ::std::nullopt;
  }
}

bool StringCmpPredicateAttr::classof(::mlir::Attribute attr) {
  return (((::llvm::isa<::mlir::IntegerAttr>(attr))) && ((::llvm::cast<::mlir::IntegerAttr>(attr).getType().isSignlessInteger(64)))) && (((
    ::llvm::cast<::mlir::IntegerAttr>(attr).getValue().eq(::llvm::APInt(64, 0)))) || ((
    ::llvm::cast<::mlir::IntegerAttr>(attr).getValue().eq(::llvm::APInt(64, 1)))) || ((
    ::llvm::cast<::mlir::IntegerAttr>(attr).getValue().eq(::llvm::APInt(64, 2)))) || ((
    ::llvm::cast<::mlir::IntegerAttr>(attr).getValue().eq(::llvm::APInt(64, 3)))) || ((
    ::llvm::cast<::mlir::IntegerAttr>(attr).getValue().eq(::llvm::APInt(64, 4)))) || ((
    ::llvm::cast<::mlir::IntegerAttr>(attr).getValue().eq(::llvm::APInt(64, 5)))));
}
StringCmpPredicateAttr StringCmpPredicateAttr::get(::mlir::MLIRContext *context, StringCmpPredicate val) {
  ::mlir::IntegerType intType = ::mlir::IntegerType::get(context, 64);
  ::mlir::IntegerAttr baseAttr = ::mlir::IntegerAttr::get(intType, static_cast<uint64_t>(val));
  return ::llvm::cast<StringCmpPredicateAttr>(baseAttr);
}
StringCmpPredicate StringCmpPredicateAttr::getValue() const {
  return static_cast<StringCmpPredicate>(::mlir::IntegerAttr::getValue().getZExtValue());
}

} // namespace circt::moore
namespace circt::moore {

::llvm::StringRef stringifyUArrayCmpPredicate(UArrayCmpPredicate val) {
  switch (val) {
    case UArrayCmpPredicate::eq: return "eq";
    case UArrayCmpPredicate::ne: return "ne";
  }
  return "";
}

::std::optional<UArrayCmpPredicate> symbolizeUArrayCmpPredicate(::llvm::StringRef str) {
  return ::llvm::StringSwitch<::std::optional<UArrayCmpPredicate>>(str)
      .Case("eq", UArrayCmpPredicate::eq)
      .Case("ne", UArrayCmpPredicate::ne)
      .Default(::std::nullopt);
}
::std::optional<UArrayCmpPredicate> symbolizeUArrayCmpPredicate(uint64_t value) {
  switch (value) {
  case 0: return UArrayCmpPredicate::eq;
  case 1: return UArrayCmpPredicate::ne;
  default: return ::std::nullopt;
  }
}

bool UArrayCmpPredicateAttr::classof(::mlir::Attribute attr) {
  return (((::llvm::isa<::mlir::IntegerAttr>(attr))) && ((::llvm::cast<::mlir::IntegerAttr>(attr).getType().isSignlessInteger(64)))) && (((
    ::llvm::cast<::mlir::IntegerAttr>(attr).getValue().eq(::llvm::APInt(64, 0)))) || ((
    ::llvm::cast<::mlir::IntegerAttr>(attr).getValue().eq(::llvm::APInt(64, 1)))));
}
UArrayCmpPredicateAttr UArrayCmpPredicateAttr::get(::mlir::MLIRContext *context, UArrayCmpPredicate val) {
  ::mlir::IntegerType intType = ::mlir::IntegerType::get(context, 64);
  ::mlir::IntegerAttr baseAttr = ::mlir::IntegerAttr::get(intType, static_cast<uint64_t>(val));
  return ::llvm::cast<UArrayCmpPredicateAttr>(baseAttr);
}
UArrayCmpPredicate UArrayCmpPredicateAttr::getValue() const {
  return static_cast<UArrayCmpPredicate>(::mlir::IntegerAttr::getValue().getZExtValue());
}

} // namespace circt::moore
