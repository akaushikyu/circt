/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* TypeDef Definitions                                                        *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

#ifdef GET_TYPEDEF_LIST
#undef GET_TYPEDEF_LIST

::circt::hw::IntType,
::circt::hw::ArrayType,
::circt::hw::UnpackedArrayType,
::circt::hw::InOutType,
::circt::hw::StructType,
::circt::hw::EnumType,
::circt::hw::UnionType,
::circt::hw::TypeAliasType,
::circt::hw::ModuleType,
::circt::hw::StringType

#endif // GET_TYPEDEF_LIST

#ifdef GET_TYPEDEF_CLASSES
#undef GET_TYPEDEF_CLASSES

static ::mlir::OptionalParseResult generatedTypeParser(::mlir::AsmParser &parser, ::llvm::StringRef *mnemonic, ::mlir::Type &value) {
  return ::mlir::AsmParser::KeywordSwitch<::mlir::OptionalParseResult>(parser)
    .Case(::circt::hw::IntType::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::hw::IntType::parse(parser);
      return ::mlir::success(!!value);
    })
    .Case(::circt::hw::ArrayType::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::hw::ArrayType::parse(parser);
      return ::mlir::success(!!value);
    })
    .Case(::circt::hw::UnpackedArrayType::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::hw::UnpackedArrayType::parse(parser);
      return ::mlir::success(!!value);
    })
    .Case(::circt::hw::InOutType::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::hw::InOutType::parse(parser);
      return ::mlir::success(!!value);
    })
    .Case(::circt::hw::StructType::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::hw::StructType::parse(parser);
      return ::mlir::success(!!value);
    })
    .Case(::circt::hw::EnumType::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::hw::EnumType::parse(parser);
      return ::mlir::success(!!value);
    })
    .Case(::circt::hw::UnionType::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::hw::UnionType::parse(parser);
      return ::mlir::success(!!value);
    })
    .Case(::circt::hw::TypeAliasType::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::hw::TypeAliasType::parse(parser);
      return ::mlir::success(!!value);
    })
    .Case(::circt::hw::ModuleType::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::hw::ModuleType::parse(parser);
      return ::mlir::success(!!value);
    })
    .Case(::circt::hw::StringType::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::hw::StringType::get(parser.getContext());
      return ::mlir::success(!!value);
    })
    .Default([&](llvm::StringRef keyword, llvm::SMLoc) {
      *mnemonic = keyword;
      return std::nullopt;
    });
}

static ::llvm::LogicalResult generatedTypePrinter(::mlir::Type def, ::mlir::AsmPrinter &printer) {
  return ::llvm::TypeSwitch<::mlir::Type, ::llvm::LogicalResult>(def)    .Case<::circt::hw::IntType>([&](auto t) {
      printer << ::circt::hw::IntType::getMnemonic();
t.print(printer);
      return ::mlir::success();
    })
    .Case<::circt::hw::ArrayType>([&](auto t) {
      printer << ::circt::hw::ArrayType::getMnemonic();
t.print(printer);
      return ::mlir::success();
    })
    .Case<::circt::hw::UnpackedArrayType>([&](auto t) {
      printer << ::circt::hw::UnpackedArrayType::getMnemonic();
t.print(printer);
      return ::mlir::success();
    })
    .Case<::circt::hw::InOutType>([&](auto t) {
      printer << ::circt::hw::InOutType::getMnemonic();
t.print(printer);
      return ::mlir::success();
    })
    .Case<::circt::hw::StructType>([&](auto t) {
      printer << ::circt::hw::StructType::getMnemonic();
t.print(printer);
      return ::mlir::success();
    })
    .Case<::circt::hw::EnumType>([&](auto t) {
      printer << ::circt::hw::EnumType::getMnemonic();
t.print(printer);
      return ::mlir::success();
    })
    .Case<::circt::hw::UnionType>([&](auto t) {
      printer << ::circt::hw::UnionType::getMnemonic();
t.print(printer);
      return ::mlir::success();
    })
    .Case<::circt::hw::TypeAliasType>([&](auto t) {
      printer << ::circt::hw::TypeAliasType::getMnemonic();
t.print(printer);
      return ::mlir::success();
    })
    .Case<::circt::hw::ModuleType>([&](auto t) {
      printer << ::circt::hw::ModuleType::getMnemonic();
t.print(printer);
      return ::mlir::success();
    })
    .Case<::circt::hw::StringType>([&](auto t) {
      printer << ::circt::hw::StringType::getMnemonic();
      return ::mlir::success();
    })
    .Default([](auto) { return ::mlir::failure(); });
}

namespace circt::hw {

namespace detail {

struct IntTypeStorage : public ::mlir::TypeStorage {
  using KeyTy = std::tuple<::mlir::TypedAttr>;
  IntTypeStorage(::mlir::TypedAttr width) : width(std::move(width)) {}

  KeyTy getAsKey() const {
    return KeyTy(width);
  }

  bool operator==(const KeyTy &tblgenKey) const {
    return (width == std::get<0>(tblgenKey));
  }

  static ::llvm::hash_code hashKey(const KeyTy &tblgenKey) {
    return ::llvm::hash_combine(std::get<0>(tblgenKey));
  }

  static IntTypeStorage *construct(::mlir::TypeStorageAllocator &allocator, KeyTy &&tblgenKey) {
    auto width = std::move(std::get<0>(tblgenKey));
    return new (allocator.allocate<IntTypeStorage>()) IntTypeStorage(std::move(width));
  }

  ::mlir::TypedAttr width;
};

} // namespace detail
::mlir::TypedAttr IntType::getWidth() const {
  return getImpl()->width;
}


} // namespace circt::hw
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::hw::IntType)
namespace circt::hw {

namespace detail {

struct ArrayTypeStorage : public ::mlir::TypeStorage {
  using KeyTy = std::tuple<::mlir::Type, ::mlir::Attribute>;
  ArrayTypeStorage(::mlir::Type elementType, ::mlir::Attribute sizeAttr) : elementType(std::move(elementType)), sizeAttr(std::move(sizeAttr)) {}

  KeyTy getAsKey() const {
    return KeyTy(elementType, sizeAttr);
  }

  bool operator==(const KeyTy &tblgenKey) const {
    return (elementType == std::get<0>(tblgenKey)) && (sizeAttr == std::get<1>(tblgenKey));
  }

  static ::llvm::hash_code hashKey(const KeyTy &tblgenKey) {
    return ::llvm::hash_combine(std::get<0>(tblgenKey), std::get<1>(tblgenKey));
  }

  static ArrayTypeStorage *construct(::mlir::TypeStorageAllocator &allocator, KeyTy &&tblgenKey) {
    auto elementType = std::move(std::get<0>(tblgenKey));
    auto sizeAttr = std::move(std::get<1>(tblgenKey));
    return new (allocator.allocate<ArrayTypeStorage>()) ArrayTypeStorage(std::move(elementType), std::move(sizeAttr));
  }

  ::mlir::Type elementType;
  ::mlir::Attribute sizeAttr;
};

} // namespace detail
ArrayType ArrayType::get(::mlir::MLIRContext *context, ::mlir::Type elementType, ::mlir::Attribute sizeAttr) {
  return Base::get(context, std::move(elementType), std::move(sizeAttr));
}

ArrayType ArrayType::getChecked(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::mlir::MLIRContext *context, ::mlir::Type elementType, ::mlir::Attribute sizeAttr) {
  return Base::getChecked(emitError, context, std::move(elementType), std::move(sizeAttr));
}

ArrayType ArrayType::get(Type elementType, size_t size) {
  auto *ctx = elementType.getContext();
  auto intType = mlir::IntegerType::get(ctx, 64);
  auto sizeAttr = mlir::IntegerAttr::get(intType, size);
  return Base::get(ctx, elementType, sizeAttr);
}

ArrayType ArrayType::getChecked(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, Type elementType, size_t size) {
  auto *ctx = elementType.getContext();
  auto intType = mlir::IntegerType::get(ctx, 64);
  auto sizeAttr = mlir::IntegerAttr::get(intType, size);
  return Base::getChecked(emitError, ctx, elementType, sizeAttr);
}

::llvm::LogicalResult ArrayType::verifyInvariants(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::mlir::Type elementType, ::mlir::Attribute sizeAttr) {
  if (::mlir::failed(verify(emitError, elementType, sizeAttr)))
    return ::mlir::failure();
  return ::mlir::success();
}

::mlir::Type ArrayType::parse(::mlir::AsmParser &odsParser) {
  ::mlir::Builder odsBuilder(odsParser.getContext());
  ::llvm::SMLoc odsLoc = odsParser.getCurrentLocation();
  (void) odsLoc;
  ::mlir::FailureOr<::mlir::Type> _result_elementType;
  ::mlir::FailureOr<::mlir::Attribute> _result_sizeAttr;
  // Parse literal '<'
  if (odsParser.parseLess()) return {};
  {
    auto odsCustomLoc = odsParser.getCurrentLocation();
    (void)odsCustomLoc;
    auto odsCustomResult = parseHWArray(odsParser,
      ::mlir::detail::unwrapForCustomParse(_result_sizeAttr),
      ::mlir::detail::unwrapForCustomParse(_result_elementType));
    if (::mlir::failed(odsCustomResult)) return {};
    if (::mlir::failed(_result_sizeAttr)) {
      odsParser.emitError(odsCustomLoc, "custom parser failed to parse parameter 'sizeAttr'");
      return {};
    }
    if (::mlir::failed(_result_elementType)) {
      odsParser.emitError(odsCustomLoc, "custom parser failed to parse parameter 'elementType'");
      return {};
    }
  }
  // Parse literal '>'
  if (odsParser.parseGreater()) return {};
  assert(::mlir::succeeded(_result_elementType));
  assert(::mlir::succeeded(_result_sizeAttr));
  return odsParser.getChecked<ArrayType>(odsLoc, odsParser.getContext(),
      ::mlir::Type((*_result_elementType)),
      ::mlir::Attribute((*_result_sizeAttr)));
}

void ArrayType::print(::mlir::AsmPrinter &odsPrinter) const {
  ::mlir::Builder odsBuilder(getContext());
  odsPrinter << "<";
  printHWArray(odsPrinter,
    getSizeAttr(),
    getElementType());
  odsPrinter << ">";
}

::mlir::Type ArrayType::getElementType() const {
  return getImpl()->elementType;
}

::mlir::Attribute ArrayType::getSizeAttr() const {
  return getImpl()->sizeAttr;
}


} // namespace circt::hw
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::hw::ArrayType)
namespace circt::hw {

namespace detail {

struct UnpackedArrayTypeStorage : public ::mlir::TypeStorage {
  using KeyTy = std::tuple<::mlir::Type, ::mlir::Attribute>;
  UnpackedArrayTypeStorage(::mlir::Type elementType, ::mlir::Attribute sizeAttr) : elementType(std::move(elementType)), sizeAttr(std::move(sizeAttr)) {}

  KeyTy getAsKey() const {
    return KeyTy(elementType, sizeAttr);
  }

  bool operator==(const KeyTy &tblgenKey) const {
    return (elementType == std::get<0>(tblgenKey)) && (sizeAttr == std::get<1>(tblgenKey));
  }

  static ::llvm::hash_code hashKey(const KeyTy &tblgenKey) {
    return ::llvm::hash_combine(std::get<0>(tblgenKey), std::get<1>(tblgenKey));
  }

  static UnpackedArrayTypeStorage *construct(::mlir::TypeStorageAllocator &allocator, KeyTy &&tblgenKey) {
    auto elementType = std::move(std::get<0>(tblgenKey));
    auto sizeAttr = std::move(std::get<1>(tblgenKey));
    return new (allocator.allocate<UnpackedArrayTypeStorage>()) UnpackedArrayTypeStorage(std::move(elementType), std::move(sizeAttr));
  }

  ::mlir::Type elementType;
  ::mlir::Attribute sizeAttr;
};

} // namespace detail
UnpackedArrayType UnpackedArrayType::get(::mlir::MLIRContext *context, ::mlir::Type elementType, ::mlir::Attribute sizeAttr) {
  return Base::get(context, std::move(elementType), std::move(sizeAttr));
}

UnpackedArrayType UnpackedArrayType::getChecked(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::mlir::MLIRContext *context, ::mlir::Type elementType, ::mlir::Attribute sizeAttr) {
  return Base::getChecked(emitError, context, std::move(elementType), std::move(sizeAttr));
}

UnpackedArrayType UnpackedArrayType::get(Type elementType, size_t size) {
  auto *ctx = elementType.getContext();
  auto intType = mlir::IntegerType::get(ctx, 64);
  auto sizeAttr = mlir::IntegerAttr::get(intType, size);
  return Base::get(ctx, elementType, sizeAttr);
}

UnpackedArrayType UnpackedArrayType::getChecked(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, Type elementType, size_t size) {
  auto *ctx = elementType.getContext();
  auto intType = mlir::IntegerType::get(ctx, 64);
  auto sizeAttr = mlir::IntegerAttr::get(intType, size);
  return Base::getChecked(emitError, ctx, elementType, sizeAttr);
}

::llvm::LogicalResult UnpackedArrayType::verifyInvariants(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::mlir::Type elementType, ::mlir::Attribute sizeAttr) {
  if (::mlir::failed(verify(emitError, elementType, sizeAttr)))
    return ::mlir::failure();
  return ::mlir::success();
}

::mlir::Type UnpackedArrayType::parse(::mlir::AsmParser &odsParser) {
  ::mlir::Builder odsBuilder(odsParser.getContext());
  ::llvm::SMLoc odsLoc = odsParser.getCurrentLocation();
  (void) odsLoc;
  ::mlir::FailureOr<::mlir::Type> _result_elementType;
  ::mlir::FailureOr<::mlir::Attribute> _result_sizeAttr;
  // Parse literal '<'
  if (odsParser.parseLess()) return {};
  {
    auto odsCustomLoc = odsParser.getCurrentLocation();
    (void)odsCustomLoc;
    auto odsCustomResult = parseHWArray(odsParser,
      ::mlir::detail::unwrapForCustomParse(_result_sizeAttr),
      ::mlir::detail::unwrapForCustomParse(_result_elementType));
    if (::mlir::failed(odsCustomResult)) return {};
    if (::mlir::failed(_result_sizeAttr)) {
      odsParser.emitError(odsCustomLoc, "custom parser failed to parse parameter 'sizeAttr'");
      return {};
    }
    if (::mlir::failed(_result_elementType)) {
      odsParser.emitError(odsCustomLoc, "custom parser failed to parse parameter 'elementType'");
      return {};
    }
  }
  // Parse literal '>'
  if (odsParser.parseGreater()) return {};
  assert(::mlir::succeeded(_result_elementType));
  assert(::mlir::succeeded(_result_sizeAttr));
  return odsParser.getChecked<UnpackedArrayType>(odsLoc, odsParser.getContext(),
      ::mlir::Type((*_result_elementType)),
      ::mlir::Attribute((*_result_sizeAttr)));
}

void UnpackedArrayType::print(::mlir::AsmPrinter &odsPrinter) const {
  ::mlir::Builder odsBuilder(getContext());
  odsPrinter << "<";
  printHWArray(odsPrinter,
    getSizeAttr(),
    getElementType());
  odsPrinter << ">";
}

::mlir::Type UnpackedArrayType::getElementType() const {
  return getImpl()->elementType;
}

::mlir::Attribute UnpackedArrayType::getSizeAttr() const {
  return getImpl()->sizeAttr;
}


} // namespace circt::hw
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::hw::UnpackedArrayType)
namespace circt::hw {

namespace detail {

struct InOutTypeStorage : public ::mlir::TypeStorage {
  using KeyTy = std::tuple<::mlir::Type>;
  InOutTypeStorage(::mlir::Type elementType) : elementType(std::move(elementType)) {}

  KeyTy getAsKey() const {
    return KeyTy(elementType);
  }

  bool operator==(const KeyTy &tblgenKey) const {
    return (elementType == std::get<0>(tblgenKey));
  }

  static ::llvm::hash_code hashKey(const KeyTy &tblgenKey) {
    return ::llvm::hash_combine(std::get<0>(tblgenKey));
  }

  static InOutTypeStorage *construct(::mlir::TypeStorageAllocator &allocator, KeyTy &&tblgenKey) {
    auto elementType = std::move(std::get<0>(tblgenKey));
    return new (allocator.allocate<InOutTypeStorage>()) InOutTypeStorage(std::move(elementType));
  }

  ::mlir::Type elementType;
};

} // namespace detail
InOutType InOutType::get(::mlir::MLIRContext *context, ::mlir::Type elementType) {
  return Base::get(context, std::move(elementType));
}

InOutType InOutType::getChecked(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::mlir::MLIRContext *context, ::mlir::Type elementType) {
  return Base::getChecked(emitError, context, std::move(elementType));
}

InOutType InOutType::get(Type elementType) {
  return Base::get(elementType.getContext(), elementType);
}

InOutType InOutType::getChecked(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, Type elementType) {
  return Base::getChecked(emitError, elementType.getContext(), elementType);
}

::llvm::LogicalResult InOutType::verifyInvariants(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::mlir::Type elementType) {
  if (::mlir::failed(verify(emitError, elementType)))
    return ::mlir::failure();
  return ::mlir::success();
}

::mlir::Type InOutType::parse(::mlir::AsmParser &odsParser) {
  ::mlir::Builder odsBuilder(odsParser.getContext());
  ::llvm::SMLoc odsLoc = odsParser.getCurrentLocation();
  (void) odsLoc;
  ::mlir::FailureOr<::mlir::Type> _result_elementType;
  // Parse literal '<'
  if (odsParser.parseLess()) return {};
  {
    auto odsCustomLoc = odsParser.getCurrentLocation();
    (void)odsCustomLoc;
    auto odsCustomResult = parseHWElementType(odsParser,
      ::mlir::detail::unwrapForCustomParse(_result_elementType));
    if (::mlir::failed(odsCustomResult)) return {};
    if (::mlir::failed(_result_elementType)) {
      odsParser.emitError(odsCustomLoc, "custom parser failed to parse parameter 'elementType'");
      return {};
    }
  }
  // Parse literal '>'
  if (odsParser.parseGreater()) return {};
  assert(::mlir::succeeded(_result_elementType));
  return odsParser.getChecked<InOutType>(odsLoc, odsParser.getContext(),
      ::mlir::Type((*_result_elementType)));
}

void InOutType::print(::mlir::AsmPrinter &odsPrinter) const {
  ::mlir::Builder odsBuilder(getContext());
  odsPrinter << "<";
  printHWElementType(odsPrinter,
    getElementType());
  odsPrinter << ">";
}

::mlir::Type InOutType::getElementType() const {
  return getImpl()->elementType;
}


} // namespace circt::hw
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::hw::InOutType)
namespace circt::hw {

namespace detail {

struct StructTypeStorage : public ::mlir::TypeStorage {
  using KeyTy = std::tuple<::llvm::ArrayRef<::circt::hw::StructType::FieldInfo>>;
  StructTypeStorage(::llvm::ArrayRef<::circt::hw::StructType::FieldInfo> elements) : elements(std::move(elements)) {}

  KeyTy getAsKey() const {
    return KeyTy(elements);
  }

  bool operator==(const KeyTy &tblgenKey) const {
    return (elements == std::get<0>(tblgenKey));
  }

  static ::llvm::hash_code hashKey(const KeyTy &tblgenKey) {
    return ::llvm::hash_combine(std::get<0>(tblgenKey));
  }

  static StructTypeStorage *construct(::mlir::TypeStorageAllocator &allocator, KeyTy &&tblgenKey) {
    auto elements = std::move(std::get<0>(tblgenKey));
    elements = allocator.copyInto(elements);
    return new (allocator.allocate<StructTypeStorage>()) StructTypeStorage(std::move(elements));
  }

  ::llvm::ArrayRef<::circt::hw::StructType::FieldInfo> elements;
};

} // namespace detail
StructType StructType::get(::mlir::MLIRContext *context, ::llvm::ArrayRef<::circt::hw::StructType::FieldInfo> elements) {
  return Base::get(context, std::move(elements));
}

StructType StructType::getChecked(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::mlir::MLIRContext *context, ::llvm::ArrayRef<::circt::hw::StructType::FieldInfo> elements) {
  return Base::getChecked(emitError, context, std::move(elements));
}

::llvm::LogicalResult StructType::verifyInvariants(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::llvm::ArrayRef<::circt::hw::StructType::FieldInfo> elements) {
  if (::mlir::failed(verify(emitError, elements)))
    return ::mlir::failure();
  return ::mlir::success();
}

::llvm::ArrayRef<::circt::hw::StructType::FieldInfo> StructType::getElements() const {
  return getImpl()->elements;
}


} // namespace circt::hw
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::hw::StructType)
namespace circt::hw {

namespace detail {

struct EnumTypeStorage : public ::mlir::TypeStorage {
  using KeyTy = std::tuple<mlir::ArrayAttr>;
  EnumTypeStorage(mlir::ArrayAttr fields) : fields(std::move(fields)) {}

  KeyTy getAsKey() const {
    return KeyTy(fields);
  }

  bool operator==(const KeyTy &tblgenKey) const {
    return (fields == std::get<0>(tblgenKey));
  }

  static ::llvm::hash_code hashKey(const KeyTy &tblgenKey) {
    return ::llvm::hash_combine(std::get<0>(tblgenKey));
  }

  static EnumTypeStorage *construct(::mlir::TypeStorageAllocator &allocator, KeyTy &&tblgenKey) {
    auto fields = std::move(std::get<0>(tblgenKey));
    return new (allocator.allocate<EnumTypeStorage>()) EnumTypeStorage(std::move(fields));
  }

  mlir::ArrayAttr fields;
};

} // namespace detail
EnumType EnumType::get(::mlir::MLIRContext *context, mlir::ArrayAttr fields) {
  return Base::get(context, std::move(fields));
}

mlir::ArrayAttr EnumType::getFields() const {
  return getImpl()->fields;
}


} // namespace circt::hw
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::hw::EnumType)
namespace circt::hw {

namespace detail {

struct UnionTypeStorage : public ::mlir::TypeStorage {
  using KeyTy = std::tuple<::llvm::ArrayRef<::circt::hw::UnionType::FieldInfo>>;
  UnionTypeStorage(::llvm::ArrayRef<::circt::hw::UnionType::FieldInfo> elements) : elements(std::move(elements)) {}

  KeyTy getAsKey() const {
    return KeyTy(elements);
  }

  bool operator==(const KeyTy &tblgenKey) const {
    return (elements == std::get<0>(tblgenKey));
  }

  static ::llvm::hash_code hashKey(const KeyTy &tblgenKey) {
    return ::llvm::hash_combine(std::get<0>(tblgenKey));
  }

  static UnionTypeStorage *construct(::mlir::TypeStorageAllocator &allocator, KeyTy &&tblgenKey) {
    auto elements = std::move(std::get<0>(tblgenKey));
    elements = allocator.copyInto(elements);
    return new (allocator.allocate<UnionTypeStorage>()) UnionTypeStorage(std::move(elements));
  }

  ::llvm::ArrayRef<::circt::hw::UnionType::FieldInfo> elements;
};

} // namespace detail
UnionType UnionType::get(::mlir::MLIRContext *context, ::llvm::ArrayRef<::circt::hw::UnionType::FieldInfo> elements) {
  return Base::get(context, std::move(elements));
}

UnionType UnionType::getChecked(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::mlir::MLIRContext *context, ::llvm::ArrayRef<::circt::hw::UnionType::FieldInfo> elements) {
  return Base::getChecked(emitError, context, std::move(elements));
}

::llvm::LogicalResult UnionType::verifyInvariants(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::llvm::ArrayRef<::circt::hw::UnionType::FieldInfo> elements) {
  if (::mlir::failed(verify(emitError, elements)))
    return ::mlir::failure();
  return ::mlir::success();
}

::llvm::ArrayRef<::circt::hw::UnionType::FieldInfo> UnionType::getElements() const {
  return getImpl()->elements;
}


} // namespace circt::hw
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::hw::UnionType)
namespace circt::hw {

namespace detail {

struct TypeAliasTypeStorage : public ::mlir::TypeStorage {
  using KeyTy = std::tuple<mlir::SymbolRefAttr, mlir::Type, mlir::Type>;
  TypeAliasTypeStorage(mlir::SymbolRefAttr ref, mlir::Type innerType, mlir::Type canonicalType) : ref(std::move(ref)), innerType(std::move(innerType)), canonicalType(std::move(canonicalType)) {}

  KeyTy getAsKey() const {
    return KeyTy(ref, innerType, canonicalType);
  }

  bool operator==(const KeyTy &tblgenKey) const {
    return (ref == std::get<0>(tblgenKey)) && (innerType == std::get<1>(tblgenKey)) && (canonicalType == std::get<2>(tblgenKey));
  }

  static ::llvm::hash_code hashKey(const KeyTy &tblgenKey) {
    return ::llvm::hash_combine(std::get<0>(tblgenKey), std::get<1>(tblgenKey), std::get<2>(tblgenKey));
  }

  static TypeAliasTypeStorage *construct(::mlir::TypeStorageAllocator &allocator, KeyTy &&tblgenKey) {
    auto ref = std::move(std::get<0>(tblgenKey));
    auto innerType = std::move(std::get<1>(tblgenKey));
    auto canonicalType = std::move(std::get<2>(tblgenKey));
    return new (allocator.allocate<TypeAliasTypeStorage>()) TypeAliasTypeStorage(std::move(ref), std::move(innerType), std::move(canonicalType));
  }

  mlir::SymbolRefAttr ref;
  mlir::Type innerType;
  mlir::Type canonicalType;
};

} // namespace detail
TypeAliasType TypeAliasType::get(::mlir::MLIRContext *context, mlir::SymbolRefAttr ref, mlir::Type innerType, mlir::Type canonicalType) {
  return Base::get(context, std::move(ref), std::move(innerType), std::move(canonicalType));
}

mlir::SymbolRefAttr TypeAliasType::getRef() const {
  return getImpl()->ref;
}

mlir::Type TypeAliasType::getInnerType() const {
  return getImpl()->innerType;
}

mlir::Type TypeAliasType::getCanonicalType() const {
  return getImpl()->canonicalType;
}


} // namespace circt::hw
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::hw::TypeAliasType)
namespace circt::hw {

ModuleType ModuleType::get(::mlir::MLIRContext *context, ::llvm::ArrayRef<::circt::hw::ModulePort> ports) {
  return Base::get(context, std::move(ports));
}

ModuleType ModuleType::getChecked(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::mlir::MLIRContext *context, ::llvm::ArrayRef<::circt::hw::ModulePort> ports) {
  return Base::getChecked(emitError, context, std::move(ports));
}

::llvm::LogicalResult ModuleType::verifyInvariants(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::llvm::ArrayRef<::circt::hw::ModulePort> ports) {
  if (::mlir::failed(verify(emitError, ports)))
    return ::mlir::failure();
  return ::mlir::success();
}


} // namespace circt::hw
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::hw::ModuleType)
namespace circt::hw {


} // namespace circt::hw
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::hw::StringType)
namespace circt::hw {


/// Parse a type registered to this dialect.
::mlir::Type HWDialect::parseType(::mlir::DialectAsmParser &parser) const {
  ::llvm::SMLoc typeLoc = parser.getCurrentLocation();
  ::llvm::StringRef mnemonic;
  ::mlir::Type genType;
  auto parseResult = generatedTypeParser(parser, &mnemonic, genType);
  if (parseResult.has_value())
    return genType;
  
  parser.emitError(typeLoc) << "unknown  type `"
      << mnemonic << "` in dialect `" << getNamespace() << "`";
  return {};
}
/// Print a type registered to this dialect.
void HWDialect::printType(::mlir::Type type,
                    ::mlir::DialectAsmPrinter &printer) const {
  if (::mlir::succeeded(generatedTypePrinter(type, printer)))
    return;
  
}

} // namespace circt::hw

#endif // GET_TYPEDEF_CLASSES

