/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Enum Utility Definitions                                                   *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: FIRRTLEnums.td                                                       *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace circt::firrtl {

::llvm::StringRef stringifyConvention(Convention val) {
  switch (val) {
    case Convention::Internal: return "internal";
    case Convention::Scalarized: return "scalarized";
  }
  return "";
}

::std::optional<Convention> symbolizeConvention(::llvm::StringRef str) {
  return ::llvm::StringSwitch<::std::optional<Convention>>(str)
      .Case("internal", Convention::Internal)
      .Case("scalarized", Convention::Scalarized)
      .Default(::std::nullopt);
}
::std::optional<Convention> symbolizeConvention(uint32_t value) {
  switch (value) {
  case 0: return Convention::Internal;
  case 1: return Convention::Scalarized;
  default: return ::std::nullopt;
  }
}


} // namespace circt::firrtl
namespace circt::firrtl {

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

} // namespace circt::firrtl
namespace circt::firrtl {

::llvm::StringRef stringifyLayerConvention(LayerConvention val) {
  switch (val) {
    case LayerConvention::Bind: return "bind";
    case LayerConvention::Inline: return "inline";
  }
  return "";
}

::std::optional<LayerConvention> symbolizeLayerConvention(::llvm::StringRef str) {
  return ::llvm::StringSwitch<::std::optional<LayerConvention>>(str)
      .Case("bind", LayerConvention::Bind)
      .Case("inline", LayerConvention::Inline)
      .Default(::std::nullopt);
}
::std::optional<LayerConvention> symbolizeLayerConvention(uint32_t value) {
  switch (value) {
  case 0: return LayerConvention::Bind;
  case 1: return LayerConvention::Inline;
  default: return ::std::nullopt;
  }
}


} // namespace circt::firrtl
namespace circt::firrtl {

::llvm::StringRef stringifyLayerSpecialization(LayerSpecialization val) {
  switch (val) {
    case LayerSpecialization::Enable: return "enable";
    case LayerSpecialization::Disable: return "disable";
  }
  return "";
}

::std::optional<LayerSpecialization> symbolizeLayerSpecialization(::llvm::StringRef str) {
  return ::llvm::StringSwitch<::std::optional<LayerSpecialization>>(str)
      .Case("enable", LayerSpecialization::Enable)
      .Case("disable", LayerSpecialization::Disable)
      .Default(::std::nullopt);
}
::std::optional<LayerSpecialization> symbolizeLayerSpecialization(uint32_t value) {
  switch (value) {
  case 0: return LayerSpecialization::Enable;
  case 1: return LayerSpecialization::Disable;
  default: return ::std::nullopt;
  }
}


} // namespace circt::firrtl
namespace circt::firrtl {

::llvm::StringRef stringifyMemDirAttr(MemDirAttr val) {
  switch (val) {
    case MemDirAttr::Infer: return "Infer";
    case MemDirAttr::Read: return "Read";
    case MemDirAttr::Write: return "Write";
    case MemDirAttr::ReadWrite: return "ReadWrite";
  }
  return "";
}

::std::optional<MemDirAttr> symbolizeMemDirAttr(::llvm::StringRef str) {
  return ::llvm::StringSwitch<::std::optional<MemDirAttr>>(str)
      .Case("Infer", MemDirAttr::Infer)
      .Case("Read", MemDirAttr::Read)
      .Case("Write", MemDirAttr::Write)
      .Case("ReadWrite", MemDirAttr::ReadWrite)
      .Default(::std::nullopt);
}
::std::optional<MemDirAttr> symbolizeMemDirAttr(uint32_t value) {
  switch (value) {
  case 0: return MemDirAttr::Infer;
  case 1: return MemDirAttr::Read;
  case 2: return MemDirAttr::Write;
  case 3: return MemDirAttr::ReadWrite;
  default: return ::std::nullopt;
  }
}

bool MemDirAttrAttr::classof(::mlir::Attribute attr) {
  return (((::llvm::isa<::mlir::IntegerAttr>(attr))) && ((::llvm::cast<::mlir::IntegerAttr>(attr).getType().isSignlessInteger(32)))) && (((
    ::llvm::cast<::mlir::IntegerAttr>(attr).getValue().eq(::llvm::APInt(32, 0)))) || ((
    ::llvm::cast<::mlir::IntegerAttr>(attr).getValue().eq(::llvm::APInt(32, 1)))) || ((
    ::llvm::cast<::mlir::IntegerAttr>(attr).getValue().eq(::llvm::APInt(32, 2)))) || ((
    ::llvm::cast<::mlir::IntegerAttr>(attr).getValue().eq(::llvm::APInt(32, 3)))));
}
MemDirAttrAttr MemDirAttrAttr::get(::mlir::MLIRContext *context, MemDirAttr val) {
  ::mlir::IntegerType intType = ::mlir::IntegerType::get(context, 32);
  ::mlir::IntegerAttr baseAttr = ::mlir::IntegerAttr::get(intType, static_cast<uint32_t>(val));
  return ::llvm::cast<MemDirAttrAttr>(baseAttr);
}
MemDirAttr MemDirAttrAttr::getValue() const {
  return static_cast<MemDirAttr>(::mlir::IntegerAttr::getValue().getZExtValue());
}

} // namespace circt::firrtl
namespace circt::firrtl {

::llvm::StringRef stringifyNameKindEnum(NameKindEnum val) {
  switch (val) {
    case NameKindEnum::DroppableName: return "droppable_name";
    case NameKindEnum::InterestingName: return "interesting_name";
  }
  return "";
}

::std::optional<NameKindEnum> symbolizeNameKindEnum(::llvm::StringRef str) {
  return ::llvm::StringSwitch<::std::optional<NameKindEnum>>(str)
      .Case("droppable_name", NameKindEnum::DroppableName)
      .Case("interesting_name", NameKindEnum::InterestingName)
      .Default(::std::nullopt);
}
::std::optional<NameKindEnum> symbolizeNameKindEnum(uint32_t value) {
  switch (value) {
  case 0: return NameKindEnum::DroppableName;
  case 1: return NameKindEnum::InterestingName;
  default: return ::std::nullopt;
  }
}


} // namespace circt::firrtl
namespace circt::firrtl {

::llvm::StringRef stringifyRUWBehavior(RUWBehavior val) {
  switch (val) {
    case RUWBehavior::Undefined: return "Undefined";
    case RUWBehavior::Old: return "Old";
    case RUWBehavior::New: return "New";
  }
  return "";
}

::std::optional<RUWBehavior> symbolizeRUWBehavior(::llvm::StringRef str) {
  return ::llvm::StringSwitch<::std::optional<RUWBehavior>>(str)
      .Case("Undefined", RUWBehavior::Undefined)
      .Case("Old", RUWBehavior::Old)
      .Case("New", RUWBehavior::New)
      .Default(::std::nullopt);
}
::std::optional<RUWBehavior> symbolizeRUWBehavior(uint32_t value) {
  switch (value) {
  case 0: return RUWBehavior::Undefined;
  case 1: return RUWBehavior::Old;
  case 2: return RUWBehavior::New;
  default: return ::std::nullopt;
  }
}


} // namespace circt::firrtl
namespace circt::firrtl {

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

} // namespace circt::firrtl
