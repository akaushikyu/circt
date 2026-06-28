/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Enum Utility Definitions                                                   *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: SV.td                                                                *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

::llvm::StringRef stringifyCaseStmtType(CaseStmtType val) {
  switch (val) {
    case CaseStmtType::CaseStmt: return "case";
    case CaseStmtType::CaseXStmt: return "casex";
    case CaseStmtType::CaseZStmt: return "casez";
  }
  return "";
}

::std::optional<CaseStmtType> symbolizeCaseStmtType(::llvm::StringRef str) {
  return ::llvm::StringSwitch<::std::optional<CaseStmtType>>(str)
      .Case("case", CaseStmtType::CaseStmt)
      .Case("casex", CaseStmtType::CaseXStmt)
      .Case("casez", CaseStmtType::CaseZStmt)
      .Default(::std::nullopt);
}
::std::optional<CaseStmtType> symbolizeCaseStmtType(uint32_t value) {
  switch (value) {
  case 0: return CaseStmtType::CaseStmt;
  case 1: return CaseStmtType::CaseXStmt;
  case 2: return CaseStmtType::CaseZStmt;
  default: return ::std::nullopt;
  }
}

bool CaseStmtTypeAttr::classof(::mlir::Attribute attr) {
  return (((::llvm::isa<::mlir::IntegerAttr>(attr))) && ((::llvm::cast<::mlir::IntegerAttr>(attr).getType().isSignlessInteger(32)))) && (((
    ::llvm::cast<::mlir::IntegerAttr>(attr).getValue().eq(::llvm::APInt(32, 0)))) || ((
    ::llvm::cast<::mlir::IntegerAttr>(attr).getValue().eq(::llvm::APInt(32, 1)))) || ((
    ::llvm::cast<::mlir::IntegerAttr>(attr).getValue().eq(::llvm::APInt(32, 2)))));
}
CaseStmtTypeAttr CaseStmtTypeAttr::get(::mlir::MLIRContext *context, CaseStmtType val) {
  ::mlir::IntegerType intType = ::mlir::IntegerType::get(context, 32);
  ::mlir::IntegerAttr baseAttr = ::mlir::IntegerAttr::get(intType, static_cast<uint32_t>(val));
  return ::llvm::cast<CaseStmtTypeAttr>(baseAttr);
}
CaseStmtType CaseStmtTypeAttr::getValue() const {
  return static_cast<CaseStmtType>(::mlir::IntegerAttr::getValue().getZExtValue());
}
namespace circt::sv {

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

} // namespace circt::sv
namespace circt::sv {

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

} // namespace circt::sv
::llvm::StringRef stringifyIncludeStyle(IncludeStyle val) {
  switch (val) {
    case IncludeStyle::Local: return "local";
    case IncludeStyle::System: return "system";
  }
  return "";
}

::std::optional<IncludeStyle> symbolizeIncludeStyle(::llvm::StringRef str) {
  return ::llvm::StringSwitch<::std::optional<IncludeStyle>>(str)
      .Case("local", IncludeStyle::Local)
      .Case("system", IncludeStyle::System)
      .Default(::std::nullopt);
}
::std::optional<IncludeStyle> symbolizeIncludeStyle(uint32_t value) {
  switch (value) {
  case 0: return IncludeStyle::Local;
  case 1: return IncludeStyle::System;
  default: return ::std::nullopt;
  }
}

::llvm::StringRef stringifyMemBaseTypeAttr(MemBaseTypeAttr val) {
  switch (val) {
    case MemBaseTypeAttr::MemBaseBin: return "MemBaseBin";
    case MemBaseTypeAttr::MemBaseHex: return "MemBaseHex";
  }
  return "";
}

::std::optional<MemBaseTypeAttr> symbolizeMemBaseTypeAttr(::llvm::StringRef str) {
  return ::llvm::StringSwitch<::std::optional<MemBaseTypeAttr>>(str)
      .Case("MemBaseBin", MemBaseTypeAttr::MemBaseBin)
      .Case("MemBaseHex", MemBaseTypeAttr::MemBaseHex)
      .Default(::std::nullopt);
}
::std::optional<MemBaseTypeAttr> symbolizeMemBaseTypeAttr(uint32_t value) {
  switch (value) {
  case 0: return MemBaseTypeAttr::MemBaseBin;
  case 1: return MemBaseTypeAttr::MemBaseHex;
  default: return ::std::nullopt;
  }
}

bool MemBaseTypeAttrAttr::classof(::mlir::Attribute attr) {
  return (((::llvm::isa<::mlir::IntegerAttr>(attr))) && ((::llvm::cast<::mlir::IntegerAttr>(attr).getType().isSignlessInteger(32)))) && (((
    ::llvm::cast<::mlir::IntegerAttr>(attr).getValue().eq(::llvm::APInt(32, 0)))) || ((
    ::llvm::cast<::mlir::IntegerAttr>(attr).getValue().eq(::llvm::APInt(32, 1)))));
}
MemBaseTypeAttrAttr MemBaseTypeAttrAttr::get(::mlir::MLIRContext *context, MemBaseTypeAttr val) {
  ::mlir::IntegerType intType = ::mlir::IntegerType::get(context, 32);
  ::mlir::IntegerAttr baseAttr = ::mlir::IntegerAttr::get(intType, static_cast<uint32_t>(val));
  return ::llvm::cast<MemBaseTypeAttrAttr>(baseAttr);
}
MemBaseTypeAttr MemBaseTypeAttrAttr::getValue() const {
  return static_cast<MemBaseTypeAttr>(::mlir::IntegerAttr::getValue().getZExtValue());
}
namespace circt::sv {

::llvm::StringRef stringifyModportDirection(ModportDirection val) {
  switch (val) {
    case ModportDirection::input: return "input";
    case ModportDirection::output: return "output";
    case ModportDirection::inout: return "inout";
  }
  return "";
}

::std::optional<ModportDirection> symbolizeModportDirection(::llvm::StringRef str) {
  return ::llvm::StringSwitch<::std::optional<ModportDirection>>(str)
      .Case("input", ModportDirection::input)
      .Case("output", ModportDirection::output)
      .Case("inout", ModportDirection::inout)
      .Default(::std::nullopt);
}
::std::optional<ModportDirection> symbolizeModportDirection(uint32_t value) {
  switch (value) {
  case 0: return ModportDirection::input;
  case 1: return ModportDirection::output;
  case 2: return ModportDirection::inout;
  default: return ::std::nullopt;
  }
}


} // namespace circt::sv
namespace circt::sv {

::llvm::StringRef stringifyResetType(ResetType val) {
  switch (val) {
    case ResetType::NoReset: return "noreset";
    case ResetType::SyncReset: return "syncreset";
    case ResetType::AsyncReset: return "asyncreset";
  }
  return "";
}

::std::optional<ResetType> symbolizeResetType(::llvm::StringRef str) {
  return ::llvm::StringSwitch<::std::optional<ResetType>>(str)
      .Case("noreset", ResetType::NoReset)
      .Case("syncreset", ResetType::SyncReset)
      .Case("asyncreset", ResetType::AsyncReset)
      .Default(::std::nullopt);
}
::std::optional<ResetType> symbolizeResetType(uint32_t value) {
  switch (value) {
  case 0: return ResetType::NoReset;
  case 1: return ResetType::SyncReset;
  case 2: return ResetType::AsyncReset;
  default: return ::std::nullopt;
  }
}

bool ResetTypeAttr::classof(::mlir::Attribute attr) {
  return (((::llvm::isa<::mlir::IntegerAttr>(attr))) && ((::llvm::cast<::mlir::IntegerAttr>(attr).getType().isSignlessInteger(32)))) && (((
    ::llvm::cast<::mlir::IntegerAttr>(attr).getValue().eq(::llvm::APInt(32, 0)))) || ((
    ::llvm::cast<::mlir::IntegerAttr>(attr).getValue().eq(::llvm::APInt(32, 1)))) || ((
    ::llvm::cast<::mlir::IntegerAttr>(attr).getValue().eq(::llvm::APInt(32, 2)))));
}
ResetTypeAttr ResetTypeAttr::get(::mlir::MLIRContext *context, ResetType val) {
  ::mlir::IntegerType intType = ::mlir::IntegerType::get(context, 32);
  ::mlir::IntegerAttr baseAttr = ::mlir::IntegerAttr::get(intType, static_cast<uint32_t>(val));
  return ::llvm::cast<ResetTypeAttr>(baseAttr);
}
ResetType ResetTypeAttr::getValue() const {
  return static_cast<ResetType>(::mlir::IntegerAttr::getValue().getZExtValue());
}

} // namespace circt::sv
namespace circt::sv {

::llvm::StringRef stringifyValidationQualifierTypeEnum(ValidationQualifierTypeEnum val) {
  switch (val) {
    case ValidationQualifierTypeEnum::ValidationQualifierPlain: return "plain";
    case ValidationQualifierTypeEnum::ValidationQualifierUnique: return "unique";
    case ValidationQualifierTypeEnum::ValidationQualifierUnique0: return "unique0";
    case ValidationQualifierTypeEnum::ValidationQualifierPriority: return "priority";
  }
  return "";
}

::std::optional<ValidationQualifierTypeEnum> symbolizeValidationQualifierTypeEnum(::llvm::StringRef str) {
  return ::llvm::StringSwitch<::std::optional<ValidationQualifierTypeEnum>>(str)
      .Case("plain", ValidationQualifierTypeEnum::ValidationQualifierPlain)
      .Case("unique", ValidationQualifierTypeEnum::ValidationQualifierUnique)
      .Case("unique0", ValidationQualifierTypeEnum::ValidationQualifierUnique0)
      .Case("priority", ValidationQualifierTypeEnum::ValidationQualifierPriority)
      .Default(::std::nullopt);
}
::std::optional<ValidationQualifierTypeEnum> symbolizeValidationQualifierTypeEnum(uint32_t value) {
  switch (value) {
  case 0: return ValidationQualifierTypeEnum::ValidationQualifierPlain;
  case 1: return ValidationQualifierTypeEnum::ValidationQualifierUnique;
  case 2: return ValidationQualifierTypeEnum::ValidationQualifierUnique0;
  case 3: return ValidationQualifierTypeEnum::ValidationQualifierPriority;
  default: return ::std::nullopt;
  }
}


} // namespace circt::sv
