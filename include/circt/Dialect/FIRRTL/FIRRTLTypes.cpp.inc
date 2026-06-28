/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* TypeDef Definitions                                                        *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

#ifdef GET_TYPEDEF_LIST
#undef GET_TYPEDEF_LIST

::circt::firrtl::SIntType,
::circt::firrtl::UIntType,
::circt::firrtl::ClockType,
::circt::firrtl::ResetType,
::circt::firrtl::AsyncResetType,
::circt::firrtl::AnalogType,
::circt::firrtl::FVectorType,
::circt::firrtl::OpenVectorType,
::circt::firrtl::BundleType,
::circt::firrtl::OpenBundleType,
::circt::firrtl::FEnumType,
::circt::firrtl::RefType,
::circt::firrtl::LHSType,
::circt::firrtl::BaseTypeAliasType,
::circt::firrtl::ClassType,
::circt::firrtl::AnyRefType,
::circt::firrtl::StringType,
::circt::firrtl::FIntegerType,
::circt::firrtl::ListType,
::circt::firrtl::PathType,
::circt::firrtl::BoolType,
::circt::firrtl::DoubleType,
::circt::firrtl::FStringType,
::circt::firrtl::DomainType

#endif // GET_TYPEDEF_LIST

#ifdef GET_TYPEDEF_CLASSES
#undef GET_TYPEDEF_CLASSES

namespace circt::firrtl {

SIntType SIntType::get(::mlir::MLIRContext *context, int32_t widthOrSentinel, bool isConst) {
  return Base::get(context, std::move(widthOrSentinel), std::move(isConst));
}

SIntType SIntType::getChecked(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::mlir::MLIRContext *context, int32_t widthOrSentinel, bool isConst) {
  return Base::getChecked(emitError, context, std::move(widthOrSentinel), std::move(isConst));
}

::llvm::LogicalResult SIntType::verifyInvariants(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, int32_t widthOrSentinel, bool isConst) {
  if (::mlir::failed(verify(emitError, widthOrSentinel, isConst)))
    return ::mlir::failure();
  return ::mlir::success();
}


} // namespace circt::firrtl
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::firrtl::SIntType)
namespace circt::firrtl {

UIntType UIntType::get(::mlir::MLIRContext *context, int32_t widthOrSentinel, bool isConst) {
  return Base::get(context, std::move(widthOrSentinel), std::move(isConst));
}

UIntType UIntType::getChecked(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::mlir::MLIRContext *context, int32_t widthOrSentinel, bool isConst) {
  return Base::getChecked(emitError, context, std::move(widthOrSentinel), std::move(isConst));
}

::llvm::LogicalResult UIntType::verifyInvariants(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, int32_t widthOrSentinel, bool isConst) {
  if (::mlir::failed(verify(emitError, widthOrSentinel, isConst)))
    return ::mlir::failure();
  return ::mlir::success();
}


} // namespace circt::firrtl
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::firrtl::UIntType)
namespace circt::firrtl {

ClockType ClockType::get(::mlir::MLIRContext *context, bool isConst) {
  return Base::get(context, std::move(isConst));
}

ClockType ClockType::get(::mlir::MLIRContext *context) {
  return Base::get(context, false);
}


} // namespace circt::firrtl
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::firrtl::ClockType)
namespace circt::firrtl {

ResetType ResetType::get(::mlir::MLIRContext *context, bool isConst) {
  return Base::get(context, std::move(isConst));
}

ResetType ResetType::get(::mlir::MLIRContext *context) {
  return Base::get(context, false);
}


} // namespace circt::firrtl
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::firrtl::ResetType)
namespace circt::firrtl {

AsyncResetType AsyncResetType::get(::mlir::MLIRContext *context, bool isConst) {
  return Base::get(context, std::move(isConst));
}

AsyncResetType AsyncResetType::get(::mlir::MLIRContext *context) {
  return Base::get(context, false);
}


} // namespace circt::firrtl
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::firrtl::AsyncResetType)
namespace circt::firrtl {

AnalogType AnalogType::get(::mlir::MLIRContext *context, int32_t widthOrSentinel, bool isConst) {
  return Base::get(context, std::move(widthOrSentinel), std::move(isConst));
}

AnalogType AnalogType::getChecked(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::mlir::MLIRContext *context, int32_t widthOrSentinel, bool isConst) {
  return Base::getChecked(emitError, context, std::move(widthOrSentinel), std::move(isConst));
}

::llvm::LogicalResult AnalogType::verifyInvariants(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, int32_t widthOrSentinel, bool isConst) {
  if (::mlir::failed(verify(emitError, widthOrSentinel, isConst)))
    return ::mlir::failure();
  return ::mlir::success();
}


} // namespace circt::firrtl
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::firrtl::AnalogType)
namespace circt::firrtl {


} // namespace circt::firrtl
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::firrtl::FVectorType)
namespace circt::firrtl {

::llvm::LogicalResult OpenVectorType::verifyInvariants(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::circt::firrtl::FIRRTLType elementType, size_t numElements, bool isConst) {
  if (::mlir::failed(verify(emitError, elementType, numElements, isConst)))
    return ::mlir::failure();
  return ::mlir::success();
}


} // namespace circt::firrtl
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::firrtl::OpenVectorType)
namespace circt::firrtl {

::llvm::LogicalResult BundleType::verifyInvariants(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ArrayRef<BundleElement> elements, bool isConst) {
  if (::mlir::failed(verify(emitError, elements, isConst)))
    return ::mlir::failure();
  return ::mlir::success();
}


} // namespace circt::firrtl
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::firrtl::BundleType)
namespace circt::firrtl {

::llvm::LogicalResult OpenBundleType::verifyInvariants(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ArrayRef<BundleElement> elements, bool isConst) {
  if (::mlir::failed(verify(emitError, elements, isConst)))
    return ::mlir::failure();
  return ::mlir::success();
}


} // namespace circt::firrtl
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::firrtl::OpenBundleType)
namespace circt::firrtl {

::llvm::LogicalResult FEnumType::verifyInvariants(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ArrayRef<EnumElement> elements, bool isConst) {
  if (::mlir::failed(verify(emitError, elements, isConst)))
    return ::mlir::failure();
  return ::mlir::success();
}


} // namespace circt::firrtl
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::firrtl::FEnumType)
namespace circt::firrtl {

namespace detail {

struct RefTypeStorage : public ::mlir::TypeStorage {
  using KeyTy = std::tuple<::circt::firrtl::FIRRTLBaseType, bool, ::mlir::SymbolRefAttr>;
  RefTypeStorage(::circt::firrtl::FIRRTLBaseType type, bool forceable, ::mlir::SymbolRefAttr layer) : type(std::move(type)), forceable(std::move(forceable)), layer(std::move(layer)) {}

  KeyTy getAsKey() const {
    return KeyTy(type, forceable, layer);
  }

  bool operator==(const KeyTy &tblgenKey) const {
    return (type == std::get<0>(tblgenKey)) && (forceable == std::get<1>(tblgenKey)) && (layer == std::get<2>(tblgenKey));
  }

  static ::llvm::hash_code hashKey(const KeyTy &tblgenKey) {
    return ::llvm::hash_combine(std::get<0>(tblgenKey), std::get<1>(tblgenKey), std::get<2>(tblgenKey));
  }

  static RefTypeStorage *construct(::mlir::TypeStorageAllocator &allocator, KeyTy &&tblgenKey) {
    auto type = std::move(std::get<0>(tblgenKey));
    auto forceable = std::move(std::get<1>(tblgenKey));
    auto layer = std::move(std::get<2>(tblgenKey));
    return new (allocator.allocate<RefTypeStorage>()) RefTypeStorage(std::move(type), std::move(forceable), std::move(layer));
  }

  ::circt::firrtl::FIRRTLBaseType type;
  bool forceable;
  ::mlir::SymbolRefAttr layer;
};

} // namespace detail
::llvm::LogicalResult RefType::verifyInvariants(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::circt::firrtl::FIRRTLBaseType type, bool forceable, ::mlir::SymbolRefAttr layer) {
  if (::mlir::failed(verify(emitError, type, forceable, layer)))
    return ::mlir::failure();
  return ::mlir::success();
}

::circt::firrtl::FIRRTLBaseType RefType::getType() const {
  return getImpl()->type;
}

bool RefType::getForceable() const {
  return getImpl()->forceable;
}

::mlir::SymbolRefAttr RefType::getLayer() const {
  return getImpl()->layer;
}


} // namespace circt::firrtl
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::firrtl::RefType)
namespace circt::firrtl {

namespace detail {

struct LHSTypeStorage : public ::mlir::TypeStorage {
  using KeyTy = std::tuple<FIRRTLBaseType>;
  LHSTypeStorage(FIRRTLBaseType type) : type(std::move(type)) {}

  KeyTy getAsKey() const {
    return KeyTy(type);
  }

  bool operator==(const KeyTy &tblgenKey) const {
    return (type == std::get<0>(tblgenKey));
  }

  static ::llvm::hash_code hashKey(const KeyTy &tblgenKey) {
    return ::llvm::hash_combine(std::get<0>(tblgenKey));
  }

  static LHSTypeStorage *construct(::mlir::TypeStorageAllocator &allocator, KeyTy &&tblgenKey) {
    auto type = std::move(std::get<0>(tblgenKey));
    return new (allocator.allocate<LHSTypeStorage>()) LHSTypeStorage(std::move(type));
  }

  FIRRTLBaseType type;
};

} // namespace detail
LHSType LHSType::get(::mlir::MLIRContext *context, FIRRTLBaseType type) {
  return Base::get(context, std::move(type));
}

LHSType LHSType::getChecked(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::mlir::MLIRContext *context, FIRRTLBaseType type) {
  return Base::getChecked(emitError, context, std::move(type));
}

::llvm::LogicalResult LHSType::verifyInvariants(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, FIRRTLBaseType type) {
  if (::mlir::failed(verify(emitError, type)))
    return ::mlir::failure();
  return ::mlir::success();
}

FIRRTLBaseType LHSType::getType() const {
  return getImpl()->type;
}


} // namespace circt::firrtl
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::firrtl::LHSType)
namespace circt::firrtl {


} // namespace circt::firrtl
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::firrtl::BaseTypeAliasType)
namespace circt::firrtl {

ClassType ClassType::get(::mlir::MLIRContext *context, FlatSymbolRefAttr name, ::llvm::ArrayRef<ClassElement> elements) {
  return Base::get(context, std::move(name), std::move(elements));
}


} // namespace circt::firrtl
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::firrtl::ClassType)
namespace circt::firrtl {


} // namespace circt::firrtl
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::firrtl::AnyRefType)
namespace circt::firrtl {


} // namespace circt::firrtl
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::firrtl::StringType)
namespace circt::firrtl {


} // namespace circt::firrtl
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::firrtl::FIntegerType)
namespace circt::firrtl {

namespace detail {

struct ListTypeStorage : public ::mlir::TypeStorage {
  using KeyTy = std::tuple<circt::firrtl::PropertyType>;
  ListTypeStorage(circt::firrtl::PropertyType elementType) : elementType(std::move(elementType)) {}

  KeyTy getAsKey() const {
    return KeyTy(elementType);
  }

  bool operator==(const KeyTy &tblgenKey) const {
    return (elementType == std::get<0>(tblgenKey));
  }

  static ::llvm::hash_code hashKey(const KeyTy &tblgenKey) {
    return ::llvm::hash_combine(std::get<0>(tblgenKey));
  }

  static ListTypeStorage *construct(::mlir::TypeStorageAllocator &allocator, KeyTy &&tblgenKey) {
    auto elementType = std::move(std::get<0>(tblgenKey));
    return new (allocator.allocate<ListTypeStorage>()) ListTypeStorage(std::move(elementType));
  }

  circt::firrtl::PropertyType elementType;
};

} // namespace detail
ListType ListType::get(::mlir::MLIRContext *context, circt::firrtl::PropertyType elementType) {
  return Base::get(context, std::move(elementType));
}

circt::firrtl::PropertyType ListType::getElementType() const {
  return getImpl()->elementType;
}


} // namespace circt::firrtl
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::firrtl::ListType)
namespace circt::firrtl {


} // namespace circt::firrtl
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::firrtl::PathType)
namespace circt::firrtl {


} // namespace circt::firrtl
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::firrtl::BoolType)
namespace circt::firrtl {


} // namespace circt::firrtl
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::firrtl::DoubleType)
namespace circt::firrtl {


} // namespace circt::firrtl
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::firrtl::FStringType)
namespace circt::firrtl {

namespace detail {

struct DomainTypeStorage : public ::mlir::TypeStorage {
  using KeyTy = std::tuple<FlatSymbolRefAttr, ArrayAttr>;
  DomainTypeStorage(FlatSymbolRefAttr name, ArrayAttr fields) : name(std::move(name)), fields(std::move(fields)) {}

  KeyTy getAsKey() const {
    return KeyTy(name, fields);
  }

  bool operator==(const KeyTy &tblgenKey) const {
    return (name == std::get<0>(tblgenKey)) && (fields == std::get<1>(tblgenKey));
  }

  static ::llvm::hash_code hashKey(const KeyTy &tblgenKey) {
    return ::llvm::hash_combine(std::get<0>(tblgenKey), std::get<1>(tblgenKey));
  }

  static DomainTypeStorage *construct(::mlir::TypeStorageAllocator &allocator, KeyTy &&tblgenKey) {
    auto name = std::move(std::get<0>(tblgenKey));
    auto fields = std::move(std::get<1>(tblgenKey));
    return new (allocator.allocate<DomainTypeStorage>()) DomainTypeStorage(std::move(name), std::move(fields));
  }

  FlatSymbolRefAttr name;
  ArrayAttr fields;
};

} // namespace detail
DomainType DomainType::get(::mlir::MLIRContext *context, FlatSymbolRefAttr name, ArrayAttr fields) {
  return Base::get(context, std::move(name), std::move(fields));
}

FlatSymbolRefAttr DomainType::getName() const {
  return getImpl()->name;
}

ArrayAttr DomainType::getFields() const {
  return getImpl()->fields;
}


} // namespace circt::firrtl
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::firrtl::DomainType)

#endif // GET_TYPEDEF_CLASSES

