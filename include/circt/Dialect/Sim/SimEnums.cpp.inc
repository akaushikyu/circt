/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Enum Utility Definitions                                                   *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: Sim.td                                                               *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace circt::sim {

::llvm::StringRef stringifyDPIDirection(DPIDirection val) {
  switch (val) {
    case DPIDirection::Input: return "in";
    case DPIDirection::Output: return "out";
    case DPIDirection::InOut: return "inout";
    case DPIDirection::Return: return "return";
    case DPIDirection::Ref: return "ref";
  }
  return "";
}

::std::optional<DPIDirection> symbolizeDPIDirection(::llvm::StringRef str) {
  return ::llvm::StringSwitch<::std::optional<DPIDirection>>(str)
      .Case("in", DPIDirection::Input)
      .Case("out", DPIDirection::Output)
      .Case("inout", DPIDirection::InOut)
      .Case("return", DPIDirection::Return)
      .Case("ref", DPIDirection::Ref)
      .Default(::std::nullopt);
}
::std::optional<DPIDirection> symbolizeDPIDirection(uint32_t value) {
  switch (value) {
  case 0: return DPIDirection::Input;
  case 1: return DPIDirection::Output;
  case 2: return DPIDirection::InOut;
  case 3: return DPIDirection::Return;
  case 4: return DPIDirection::Ref;
  default: return ::std::nullopt;
  }
}

bool DPIDirectionAttr::classof(::mlir::Attribute attr) {
  return (((::llvm::isa<::mlir::IntegerAttr>(attr))) && ((::llvm::cast<::mlir::IntegerAttr>(attr).getType().isSignlessInteger(32)))) && (((
    ::llvm::cast<::mlir::IntegerAttr>(attr).getValue().eq(::llvm::APInt(32, 0)))) || ((
    ::llvm::cast<::mlir::IntegerAttr>(attr).getValue().eq(::llvm::APInt(32, 1)))) || ((
    ::llvm::cast<::mlir::IntegerAttr>(attr).getValue().eq(::llvm::APInt(32, 2)))) || ((
    ::llvm::cast<::mlir::IntegerAttr>(attr).getValue().eq(::llvm::APInt(32, 3)))) || ((
    ::llvm::cast<::mlir::IntegerAttr>(attr).getValue().eq(::llvm::APInt(32, 4)))));
}
DPIDirectionAttr DPIDirectionAttr::get(::mlir::MLIRContext *context, DPIDirection val) {
  ::mlir::IntegerType intType = ::mlir::IntegerType::get(context, 32);
  ::mlir::IntegerAttr baseAttr = ::mlir::IntegerAttr::get(intType, static_cast<uint32_t>(val));
  return ::llvm::cast<DPIDirectionAttr>(baseAttr);
}
DPIDirection DPIDirectionAttr::getValue() const {
  return static_cast<DPIDirection>(::mlir::IntegerAttr::getValue().getZExtValue());
}

} // namespace circt::sim
namespace circt::sim {

::llvm::StringRef stringifyQueueCmpPredicate(QueueCmpPredicate val) {
  switch (val) {
    case QueueCmpPredicate::eq: return "eq";
    case QueueCmpPredicate::ne: return "ne";
  }
  return "";
}

::std::optional<QueueCmpPredicate> symbolizeQueueCmpPredicate(::llvm::StringRef str) {
  return ::llvm::StringSwitch<::std::optional<QueueCmpPredicate>>(str)
      .Case("eq", QueueCmpPredicate::eq)
      .Case("ne", QueueCmpPredicate::ne)
      .Default(::std::nullopt);
}
::std::optional<QueueCmpPredicate> symbolizeQueueCmpPredicate(uint64_t value) {
  switch (value) {
  case 0: return QueueCmpPredicate::eq;
  case 1: return QueueCmpPredicate::ne;
  default: return ::std::nullopt;
  }
}

bool QueueCmpPredicateAttr::classof(::mlir::Attribute attr) {
  return (((::llvm::isa<::mlir::IntegerAttr>(attr))) && ((::llvm::cast<::mlir::IntegerAttr>(attr).getType().isSignlessInteger(64)))) && (((
    ::llvm::cast<::mlir::IntegerAttr>(attr).getValue().eq(::llvm::APInt(64, 0)))) || ((
    ::llvm::cast<::mlir::IntegerAttr>(attr).getValue().eq(::llvm::APInt(64, 1)))));
}
QueueCmpPredicateAttr QueueCmpPredicateAttr::get(::mlir::MLIRContext *context, QueueCmpPredicate val) {
  ::mlir::IntegerType intType = ::mlir::IntegerType::get(context, 64);
  ::mlir::IntegerAttr baseAttr = ::mlir::IntegerAttr::get(intType, static_cast<uint64_t>(val));
  return ::llvm::cast<QueueCmpPredicateAttr>(baseAttr);
}
QueueCmpPredicate QueueCmpPredicateAttr::getValue() const {
  return static_cast<QueueCmpPredicate>(::mlir::IntegerAttr::getValue().getZExtValue());
}

} // namespace circt::sim
namespace circt::sim {

::llvm::StringRef stringifySVFOpenMode(SVFOpenMode val) {
  switch (val) {
    case SVFOpenMode::Read: return "r";
    case SVFOpenMode::Write: return "w";
    case SVFOpenMode::Append: return "a";
    case SVFOpenMode::ReadUpdate: return "r_update";
    case SVFOpenMode::WriteUpdate: return "w_update";
    case SVFOpenMode::AppendUpdate: return "a_update";
  }
  return "";
}

::std::optional<SVFOpenMode> symbolizeSVFOpenMode(::llvm::StringRef str) {
  return ::llvm::StringSwitch<::std::optional<SVFOpenMode>>(str)
      .Case("r", SVFOpenMode::Read)
      .Case("w", SVFOpenMode::Write)
      .Case("a", SVFOpenMode::Append)
      .Case("r_update", SVFOpenMode::ReadUpdate)
      .Case("w_update", SVFOpenMode::WriteUpdate)
      .Case("a_update", SVFOpenMode::AppendUpdate)
      .Default(::std::nullopt);
}
::std::optional<SVFOpenMode> symbolizeSVFOpenMode(uint32_t value) {
  switch (value) {
  case 0: return SVFOpenMode::Read;
  case 1: return SVFOpenMode::Write;
  case 2: return SVFOpenMode::Append;
  case 3: return SVFOpenMode::ReadUpdate;
  case 4: return SVFOpenMode::WriteUpdate;
  case 5: return SVFOpenMode::AppendUpdate;
  default: return ::std::nullopt;
  }
}

bool SVFOpenModeAttr::classof(::mlir::Attribute attr) {
  return (((::llvm::isa<::mlir::IntegerAttr>(attr))) && ((::llvm::cast<::mlir::IntegerAttr>(attr).getType().isSignlessInteger(32)))) && (((
    ::llvm::cast<::mlir::IntegerAttr>(attr).getValue().eq(::llvm::APInt(32, 0)))) || ((
    ::llvm::cast<::mlir::IntegerAttr>(attr).getValue().eq(::llvm::APInt(32, 1)))) || ((
    ::llvm::cast<::mlir::IntegerAttr>(attr).getValue().eq(::llvm::APInt(32, 2)))) || ((
    ::llvm::cast<::mlir::IntegerAttr>(attr).getValue().eq(::llvm::APInt(32, 3)))) || ((
    ::llvm::cast<::mlir::IntegerAttr>(attr).getValue().eq(::llvm::APInt(32, 4)))) || ((
    ::llvm::cast<::mlir::IntegerAttr>(attr).getValue().eq(::llvm::APInt(32, 5)))));
}
SVFOpenModeAttr SVFOpenModeAttr::get(::mlir::MLIRContext *context, SVFOpenMode val) {
  ::mlir::IntegerType intType = ::mlir::IntegerType::get(context, 32);
  ::mlir::IntegerAttr baseAttr = ::mlir::IntegerAttr::get(intType, static_cast<uint32_t>(val));
  return ::llvm::cast<SVFOpenModeAttr>(baseAttr);
}
SVFOpenMode SVFOpenModeAttr::getValue() const {
  return static_cast<SVFOpenMode>(::mlir::IntegerAttr::getValue().getZExtValue());
}

} // namespace circt::sim
