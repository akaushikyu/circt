/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* TypeDef Definitions                                                        *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

#ifdef GET_TYPEDEF_LIST
#undef GET_TYPEDEF_LIST

::circt::moore::VoidType,
::circt::moore::StringType,
::circt::moore::ChandleType,
::circt::moore::EventType,
::circt::moore::NullType,
::circt::moore::ClassHandleType,
::circt::moore::TimeType,
::circt::moore::IntType,
::circt::moore::RealType,
::circt::moore::ArrayType,
::circt::moore::UnpackedArrayType,
::circt::moore::OpenArrayType,
::circt::moore::OpenUnpackedArrayType,
::circt::moore::AssocArrayType,
::circt::moore::QueueType,
::circt::moore::StructType,
::circt::moore::UnpackedStructType,
::circt::moore::UnionType,
::circt::moore::UnpackedUnionType,
::circt::moore::RefType,
::circt::moore::FormatStringType

#endif // GET_TYPEDEF_LIST

#ifdef GET_TYPEDEF_CLASSES
#undef GET_TYPEDEF_CLASSES

static ::mlir::OptionalParseResult generatedTypeParser(::mlir::AsmParser &parser, ::llvm::StringRef *mnemonic, ::mlir::Type &value) {
  return ::mlir::AsmParser::KeywordSwitch<::mlir::OptionalParseResult>(parser)
    .Case(::circt::moore::VoidType::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::moore::VoidType::get(parser.getContext());
      return ::mlir::success(!!value);
    })
    .Case(::circt::moore::StringType::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::moore::StringType::get(parser.getContext());
      return ::mlir::success(!!value);
    })
    .Case(::circt::moore::ChandleType::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::moore::ChandleType::get(parser.getContext());
      return ::mlir::success(!!value);
    })
    .Case(::circt::moore::EventType::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::moore::EventType::get(parser.getContext());
      return ::mlir::success(!!value);
    })
    .Case(::circt::moore::NullType::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::moore::NullType::get(parser.getContext());
      return ::mlir::success(!!value);
    })
    .Case(::circt::moore::ClassHandleType::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::moore::ClassHandleType::parse(parser);
      return ::mlir::success(!!value);
    })
    .Case(::circt::moore::TimeType::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::moore::TimeType::get(parser.getContext());
      return ::mlir::success(!!value);
    })
    .Case(::circt::moore::ArrayType::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::moore::ArrayType::parse(parser);
      return ::mlir::success(!!value);
    })
    .Case(::circt::moore::UnpackedArrayType::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::moore::UnpackedArrayType::parse(parser);
      return ::mlir::success(!!value);
    })
    .Case(::circt::moore::OpenArrayType::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::moore::OpenArrayType::parse(parser);
      return ::mlir::success(!!value);
    })
    .Case(::circt::moore::OpenUnpackedArrayType::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::moore::OpenUnpackedArrayType::parse(parser);
      return ::mlir::success(!!value);
    })
    .Case(::circt::moore::AssocArrayType::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::moore::AssocArrayType::parse(parser);
      return ::mlir::success(!!value);
    })
    .Case(::circt::moore::QueueType::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::moore::QueueType::parse(parser);
      return ::mlir::success(!!value);
    })
    .Case(::circt::moore::StructType::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::moore::StructType::parse(parser);
      return ::mlir::success(!!value);
    })
    .Case(::circt::moore::UnpackedStructType::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::moore::UnpackedStructType::parse(parser);
      return ::mlir::success(!!value);
    })
    .Case(::circt::moore::UnionType::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::moore::UnionType::parse(parser);
      return ::mlir::success(!!value);
    })
    .Case(::circt::moore::UnpackedUnionType::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::moore::UnpackedUnionType::parse(parser);
      return ::mlir::success(!!value);
    })
    .Case(::circt::moore::RefType::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::moore::RefType::parse(parser);
      return ::mlir::success(!!value);
    })
    .Case(::circt::moore::FormatStringType::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::moore::FormatStringType::get(parser.getContext());
      return ::mlir::success(!!value);
    })
    .Default([&](llvm::StringRef keyword, llvm::SMLoc) {
      *mnemonic = keyword;
      return std::nullopt;
    });
}

static ::llvm::LogicalResult generatedTypePrinter(::mlir::Type def, ::mlir::AsmPrinter &printer) {
  return ::llvm::TypeSwitch<::mlir::Type, ::llvm::LogicalResult>(def)    .Case<::circt::moore::VoidType>([&](auto t) {
      printer << ::circt::moore::VoidType::getMnemonic();
      return ::mlir::success();
    })
    .Case<::circt::moore::StringType>([&](auto t) {
      printer << ::circt::moore::StringType::getMnemonic();
      return ::mlir::success();
    })
    .Case<::circt::moore::ChandleType>([&](auto t) {
      printer << ::circt::moore::ChandleType::getMnemonic();
      return ::mlir::success();
    })
    .Case<::circt::moore::EventType>([&](auto t) {
      printer << ::circt::moore::EventType::getMnemonic();
      return ::mlir::success();
    })
    .Case<::circt::moore::NullType>([&](auto t) {
      printer << ::circt::moore::NullType::getMnemonic();
      return ::mlir::success();
    })
    .Case<::circt::moore::ClassHandleType>([&](auto t) {
      printer << ::circt::moore::ClassHandleType::getMnemonic();
t.print(printer);
      return ::mlir::success();
    })
    .Case<::circt::moore::TimeType>([&](auto t) {
      printer << ::circt::moore::TimeType::getMnemonic();
      return ::mlir::success();
    })
    .Case<::circt::moore::ArrayType>([&](auto t) {
      printer << ::circt::moore::ArrayType::getMnemonic();
t.print(printer);
      return ::mlir::success();
    })
    .Case<::circt::moore::UnpackedArrayType>([&](auto t) {
      printer << ::circt::moore::UnpackedArrayType::getMnemonic();
t.print(printer);
      return ::mlir::success();
    })
    .Case<::circt::moore::OpenArrayType>([&](auto t) {
      printer << ::circt::moore::OpenArrayType::getMnemonic();
t.print(printer);
      return ::mlir::success();
    })
    .Case<::circt::moore::OpenUnpackedArrayType>([&](auto t) {
      printer << ::circt::moore::OpenUnpackedArrayType::getMnemonic();
t.print(printer);
      return ::mlir::success();
    })
    .Case<::circt::moore::AssocArrayType>([&](auto t) {
      printer << ::circt::moore::AssocArrayType::getMnemonic();
t.print(printer);
      return ::mlir::success();
    })
    .Case<::circt::moore::QueueType>([&](auto t) {
      printer << ::circt::moore::QueueType::getMnemonic();
t.print(printer);
      return ::mlir::success();
    })
    .Case<::circt::moore::StructType>([&](auto t) {
      printer << ::circt::moore::StructType::getMnemonic();
t.print(printer);
      return ::mlir::success();
    })
    .Case<::circt::moore::UnpackedStructType>([&](auto t) {
      printer << ::circt::moore::UnpackedStructType::getMnemonic();
t.print(printer);
      return ::mlir::success();
    })
    .Case<::circt::moore::UnionType>([&](auto t) {
      printer << ::circt::moore::UnionType::getMnemonic();
t.print(printer);
      return ::mlir::success();
    })
    .Case<::circt::moore::UnpackedUnionType>([&](auto t) {
      printer << ::circt::moore::UnpackedUnionType::getMnemonic();
t.print(printer);
      return ::mlir::success();
    })
    .Case<::circt::moore::RefType>([&](auto t) {
      printer << ::circt::moore::RefType::getMnemonic();
t.print(printer);
      return ::mlir::success();
    })
    .Case<::circt::moore::FormatStringType>([&](auto t) {
      printer << ::circt::moore::FormatStringType::getMnemonic();
      return ::mlir::success();
    })
    .Default([](auto) { return ::mlir::failure(); });
}

namespace circt::moore {


} // namespace circt::moore
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::moore::VoidType)
namespace circt::moore {


} // namespace circt::moore
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::moore::StringType)
namespace circt::moore {


} // namespace circt::moore
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::moore::ChandleType)
namespace circt::moore {


} // namespace circt::moore
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::moore::EventType)
namespace circt::moore {


} // namespace circt::moore
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::moore::NullType)
namespace circt::moore {

namespace detail {

struct ClassHandleTypeStorage : public ::mlir::TypeStorage {
  using KeyTy = std::tuple<::mlir::SymbolRefAttr>;
  ClassHandleTypeStorage(::mlir::SymbolRefAttr classSym) : classSym(std::move(classSym)) {}

  KeyTy getAsKey() const {
    return KeyTy(classSym);
  }

  bool operator==(const KeyTy &tblgenKey) const {
    return (classSym == std::get<0>(tblgenKey));
  }

  static ::llvm::hash_code hashKey(const KeyTy &tblgenKey) {
    return ::llvm::hash_combine(std::get<0>(tblgenKey));
  }

  static ClassHandleTypeStorage *construct(::mlir::TypeStorageAllocator &allocator, KeyTy &&tblgenKey) {
    auto classSym = std::move(std::get<0>(tblgenKey));
    return new (allocator.allocate<ClassHandleTypeStorage>()) ClassHandleTypeStorage(std::move(classSym));
  }

  ::mlir::SymbolRefAttr classSym;
};

} // namespace detail
ClassHandleType ClassHandleType::get(::mlir::MLIRContext *context, ::mlir::SymbolRefAttr classSym) {
  return Base::get(context, std::move(classSym));
}

::mlir::Type ClassHandleType::parse(::mlir::AsmParser &odsParser) {
  ::mlir::Builder odsBuilder(odsParser.getContext());
  ::llvm::SMLoc odsLoc = odsParser.getCurrentLocation();
  (void) odsLoc;
  ::mlir::FailureOr<::mlir::SymbolRefAttr> _result_classSym;
  // Parse literal '<'
  if (odsParser.parseLess()) return {};

  // Parse variable 'classSym'
  _result_classSym = ::mlir::FieldParser<::mlir::SymbolRefAttr>::parse(odsParser);
  if (::mlir::failed(_result_classSym)) {
    odsParser.emitError(odsParser.getCurrentLocation(), "failed to parse ClassHandleType parameter 'classSym' which is to be a `::mlir::SymbolRefAttr`");
    return {};
  }
  // Parse literal '>'
  if (odsParser.parseGreater()) return {};
  assert(::mlir::succeeded(_result_classSym));
  return ClassHandleType::get(odsParser.getContext(),
      ::mlir::SymbolRefAttr((*_result_classSym)));
}

void ClassHandleType::print(::mlir::AsmPrinter &odsPrinter) const {
  ::mlir::Builder odsBuilder(getContext());
  odsPrinter << "<";
  odsPrinter.printStrippedAttrOrType(getClassSym());
  odsPrinter << ">";
}

::mlir::SymbolRefAttr ClassHandleType::getClassSym() const {
  return getImpl()->classSym;
}


} // namespace circt::moore
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::moore::ClassHandleType)
namespace circt::moore {


} // namespace circt::moore
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::moore::TimeType)
namespace circt::moore {

namespace detail {

struct IntTypeStorage : public ::mlir::TypeStorage {
  using KeyTy = std::tuple<unsigned, Domain>;
  IntTypeStorage(unsigned width, Domain domain) : width(std::move(width)), domain(std::move(domain)) {}

  KeyTy getAsKey() const {
    return KeyTy(width, domain);
  }

  bool operator==(const KeyTy &tblgenKey) const {
    return (width == std::get<0>(tblgenKey)) && (domain == std::get<1>(tblgenKey));
  }

  static ::llvm::hash_code hashKey(const KeyTy &tblgenKey) {
    return ::llvm::hash_combine(std::get<0>(tblgenKey), std::get<1>(tblgenKey));
  }

  static IntTypeStorage *construct(::mlir::TypeStorageAllocator &allocator, KeyTy &&tblgenKey) {
    auto width = std::move(std::get<0>(tblgenKey));
    auto domain = std::move(std::get<1>(tblgenKey));
    return new (allocator.allocate<IntTypeStorage>()) IntTypeStorage(std::move(width), std::move(domain));
  }

  unsigned width;
  Domain domain;
};

} // namespace detail
IntType IntType::get(::mlir::MLIRContext *context, unsigned width, Domain domain) {
  return Base::get(context, std::move(width), std::move(domain));
}

unsigned IntType::getWidth() const {
  return getImpl()->width;
}

Domain IntType::getDomain() const {
  return getImpl()->domain;
}


} // namespace circt::moore
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::moore::IntType)
namespace circt::moore {

namespace detail {

struct RealTypeStorage : public ::mlir::TypeStorage {
  using KeyTy = std::tuple<RealWidth>;
  RealTypeStorage(RealWidth width) : width(std::move(width)) {}

  KeyTy getAsKey() const {
    return KeyTy(width);
  }

  bool operator==(const KeyTy &tblgenKey) const {
    return (width == std::get<0>(tblgenKey));
  }

  static ::llvm::hash_code hashKey(const KeyTy &tblgenKey) {
    return ::llvm::hash_combine(std::get<0>(tblgenKey));
  }

  static RealTypeStorage *construct(::mlir::TypeStorageAllocator &allocator, KeyTy &&tblgenKey) {
    auto width = std::move(std::get<0>(tblgenKey));
    return new (allocator.allocate<RealTypeStorage>()) RealTypeStorage(std::move(width));
  }

  RealWidth width;
};

} // namespace detail
RealType RealType::get(::mlir::MLIRContext *context, RealWidth width) {
  return Base::get(context, std::move(width));
}

RealWidth RealType::getWidth() const {
  return getImpl()->width;
}


} // namespace circt::moore
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::moore::RealType)
namespace circt::moore {

namespace detail {

struct ArrayTypeStorage : public ::mlir::TypeStorage {
  using KeyTy = std::tuple<unsigned, PackedType>;
  ArrayTypeStorage(unsigned size, PackedType elementType) : size(std::move(size)), elementType(std::move(elementType)) {}

  KeyTy getAsKey() const {
    return KeyTy(size, elementType);
  }

  bool operator==(const KeyTy &tblgenKey) const {
    return (size == std::get<0>(tblgenKey)) && (elementType == std::get<1>(tblgenKey));
  }

  static ::llvm::hash_code hashKey(const KeyTy &tblgenKey) {
    return ::llvm::hash_combine(std::get<0>(tblgenKey), std::get<1>(tblgenKey));
  }

  static ArrayTypeStorage *construct(::mlir::TypeStorageAllocator &allocator, KeyTy &&tblgenKey) {
    auto size = std::move(std::get<0>(tblgenKey));
    auto elementType = std::move(std::get<1>(tblgenKey));
    return new (allocator.allocate<ArrayTypeStorage>()) ArrayTypeStorage(std::move(size), std::move(elementType));
  }

  unsigned size;
  PackedType elementType;
};

} // namespace detail
ArrayType ArrayType::get(::mlir::MLIRContext *context, unsigned size, PackedType elementType) {
  return Base::get(context, std::move(size), std::move(elementType));
}

ArrayType ArrayType::get(unsigned size, PackedType elementType) {
  return Base::get(elementType.getContext(), size, elementType);
}

::mlir::Type ArrayType::parse(::mlir::AsmParser &odsParser) {
  ::mlir::Builder odsBuilder(odsParser.getContext());
  ::llvm::SMLoc odsLoc = odsParser.getCurrentLocation();
  (void) odsLoc;
  ::mlir::FailureOr<unsigned> _result_size;
  ::mlir::FailureOr<PackedType> _result_elementType;
  // Parse literal '<'
  if (odsParser.parseLess()) return {};

  // Parse variable 'size'
  _result_size = ::mlir::FieldParser<unsigned>::parse(odsParser);
  if (::mlir::failed(_result_size)) {
    odsParser.emitError(odsParser.getCurrentLocation(), "failed to parse ArrayType parameter 'size' which is to be a `unsigned`");
    return {};
  }
  // Parse literal 'x'
  if (odsParser.parseKeyword("x")) return {};

  // Parse variable 'elementType'
  _result_elementType = ::mlir::FieldParser<PackedType>::parse(odsParser);
  if (::mlir::failed(_result_elementType)) {
    odsParser.emitError(odsParser.getCurrentLocation(), "failed to parse ArrayType parameter 'elementType' which is to be a `PackedType`");
    return {};
  }
  // Parse literal '>'
  if (odsParser.parseGreater()) return {};
  assert(::mlir::succeeded(_result_size));
  assert(::mlir::succeeded(_result_elementType));
  return ArrayType::get(odsParser.getContext(),
      unsigned((*_result_size)),
      PackedType((*_result_elementType)));
}

void ArrayType::print(::mlir::AsmPrinter &odsPrinter) const {
  ::mlir::Builder odsBuilder(getContext());
  odsPrinter << "<";
  odsPrinter.printStrippedAttrOrType(getSize());
  odsPrinter << ' ' << "x";
  odsPrinter << ' ';
  odsPrinter.printStrippedAttrOrType(getElementType());
  odsPrinter << ">";
}

unsigned ArrayType::getSize() const {
  return getImpl()->size;
}

PackedType ArrayType::getElementType() const {
  return getImpl()->elementType;
}


} // namespace circt::moore
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::moore::ArrayType)
namespace circt::moore {

namespace detail {

struct UnpackedArrayTypeStorage : public ::mlir::TypeStorage {
  using KeyTy = std::tuple<unsigned, UnpackedType>;
  UnpackedArrayTypeStorage(unsigned size, UnpackedType elementType) : size(std::move(size)), elementType(std::move(elementType)) {}

  KeyTy getAsKey() const {
    return KeyTy(size, elementType);
  }

  bool operator==(const KeyTy &tblgenKey) const {
    return (size == std::get<0>(tblgenKey)) && (elementType == std::get<1>(tblgenKey));
  }

  static ::llvm::hash_code hashKey(const KeyTy &tblgenKey) {
    return ::llvm::hash_combine(std::get<0>(tblgenKey), std::get<1>(tblgenKey));
  }

  static UnpackedArrayTypeStorage *construct(::mlir::TypeStorageAllocator &allocator, KeyTy &&tblgenKey) {
    auto size = std::move(std::get<0>(tblgenKey));
    auto elementType = std::move(std::get<1>(tblgenKey));
    return new (allocator.allocate<UnpackedArrayTypeStorage>()) UnpackedArrayTypeStorage(std::move(size), std::move(elementType));
  }

  unsigned size;
  UnpackedType elementType;
};

} // namespace detail
UnpackedArrayType UnpackedArrayType::get(::mlir::MLIRContext *context, unsigned size, UnpackedType elementType) {
  return Base::get(context, std::move(size), std::move(elementType));
}

UnpackedArrayType UnpackedArrayType::get(unsigned size, UnpackedType elementType) {
  return Base::get(elementType.getContext(), size, elementType);
}

::mlir::Type UnpackedArrayType::parse(::mlir::AsmParser &odsParser) {
  ::mlir::Builder odsBuilder(odsParser.getContext());
  ::llvm::SMLoc odsLoc = odsParser.getCurrentLocation();
  (void) odsLoc;
  ::mlir::FailureOr<unsigned> _result_size;
  ::mlir::FailureOr<UnpackedType> _result_elementType;
  // Parse literal '<'
  if (odsParser.parseLess()) return {};

  // Parse variable 'size'
  _result_size = ::mlir::FieldParser<unsigned>::parse(odsParser);
  if (::mlir::failed(_result_size)) {
    odsParser.emitError(odsParser.getCurrentLocation(), "failed to parse UnpackedArrayType parameter 'size' which is to be a `unsigned`");
    return {};
  }
  // Parse literal 'x'
  if (odsParser.parseKeyword("x")) return {};

  // Parse variable 'elementType'
  _result_elementType = ::mlir::FieldParser<UnpackedType>::parse(odsParser);
  if (::mlir::failed(_result_elementType)) {
    odsParser.emitError(odsParser.getCurrentLocation(), "failed to parse UnpackedArrayType parameter 'elementType' which is to be a `UnpackedType`");
    return {};
  }
  // Parse literal '>'
  if (odsParser.parseGreater()) return {};
  assert(::mlir::succeeded(_result_size));
  assert(::mlir::succeeded(_result_elementType));
  return UnpackedArrayType::get(odsParser.getContext(),
      unsigned((*_result_size)),
      UnpackedType((*_result_elementType)));
}

void UnpackedArrayType::print(::mlir::AsmPrinter &odsPrinter) const {
  ::mlir::Builder odsBuilder(getContext());
  odsPrinter << "<";
  odsPrinter.printStrippedAttrOrType(getSize());
  odsPrinter << ' ' << "x";
  odsPrinter << ' ';
  odsPrinter.printStrippedAttrOrType(getElementType());
  odsPrinter << ">";
}

unsigned UnpackedArrayType::getSize() const {
  return getImpl()->size;
}

UnpackedType UnpackedArrayType::getElementType() const {
  return getImpl()->elementType;
}


} // namespace circt::moore
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::moore::UnpackedArrayType)
namespace circt::moore {

namespace detail {

struct OpenArrayTypeStorage : public ::mlir::TypeStorage {
  using KeyTy = std::tuple<PackedType>;
  OpenArrayTypeStorage(PackedType elementType) : elementType(std::move(elementType)) {}

  KeyTy getAsKey() const {
    return KeyTy(elementType);
  }

  bool operator==(const KeyTy &tblgenKey) const {
    return (elementType == std::get<0>(tblgenKey));
  }

  static ::llvm::hash_code hashKey(const KeyTy &tblgenKey) {
    return ::llvm::hash_combine(std::get<0>(tblgenKey));
  }

  static OpenArrayTypeStorage *construct(::mlir::TypeStorageAllocator &allocator, KeyTy &&tblgenKey) {
    auto elementType = std::move(std::get<0>(tblgenKey));
    return new (allocator.allocate<OpenArrayTypeStorage>()) OpenArrayTypeStorage(std::move(elementType));
  }

  PackedType elementType;
};

} // namespace detail
OpenArrayType OpenArrayType::get(::mlir::MLIRContext *context, PackedType elementType) {
  return Base::get(context, std::move(elementType));
}

OpenArrayType OpenArrayType::get(PackedType elementType) {
  return Base::get(elementType.getContext(), elementType);
}

::mlir::Type OpenArrayType::parse(::mlir::AsmParser &odsParser) {
  ::mlir::Builder odsBuilder(odsParser.getContext());
  ::llvm::SMLoc odsLoc = odsParser.getCurrentLocation();
  (void) odsLoc;
  ::mlir::FailureOr<PackedType> _result_elementType;
  // Parse literal '<'
  if (odsParser.parseLess()) return {};

  // Parse variable 'elementType'
  _result_elementType = ::mlir::FieldParser<PackedType>::parse(odsParser);
  if (::mlir::failed(_result_elementType)) {
    odsParser.emitError(odsParser.getCurrentLocation(), "failed to parse OpenArrayType parameter 'elementType' which is to be a `PackedType`");
    return {};
  }
  // Parse literal '>'
  if (odsParser.parseGreater()) return {};
  assert(::mlir::succeeded(_result_elementType));
  return OpenArrayType::get(odsParser.getContext(),
      PackedType((*_result_elementType)));
}

void OpenArrayType::print(::mlir::AsmPrinter &odsPrinter) const {
  ::mlir::Builder odsBuilder(getContext());
  odsPrinter << "<";
  odsPrinter.printStrippedAttrOrType(getElementType());
  odsPrinter << ">";
}

PackedType OpenArrayType::getElementType() const {
  return getImpl()->elementType;
}


} // namespace circt::moore
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::moore::OpenArrayType)
namespace circt::moore {

namespace detail {

struct OpenUnpackedArrayTypeStorage : public ::mlir::TypeStorage {
  using KeyTy = std::tuple<UnpackedType>;
  OpenUnpackedArrayTypeStorage(UnpackedType elementType) : elementType(std::move(elementType)) {}

  KeyTy getAsKey() const {
    return KeyTy(elementType);
  }

  bool operator==(const KeyTy &tblgenKey) const {
    return (elementType == std::get<0>(tblgenKey));
  }

  static ::llvm::hash_code hashKey(const KeyTy &tblgenKey) {
    return ::llvm::hash_combine(std::get<0>(tblgenKey));
  }

  static OpenUnpackedArrayTypeStorage *construct(::mlir::TypeStorageAllocator &allocator, KeyTy &&tblgenKey) {
    auto elementType = std::move(std::get<0>(tblgenKey));
    return new (allocator.allocate<OpenUnpackedArrayTypeStorage>()) OpenUnpackedArrayTypeStorage(std::move(elementType));
  }

  UnpackedType elementType;
};

} // namespace detail
OpenUnpackedArrayType OpenUnpackedArrayType::get(::mlir::MLIRContext *context, UnpackedType elementType) {
  return Base::get(context, std::move(elementType));
}

OpenUnpackedArrayType OpenUnpackedArrayType::get(UnpackedType elementType) {
  return Base::get(elementType.getContext(), elementType);
}

::mlir::Type OpenUnpackedArrayType::parse(::mlir::AsmParser &odsParser) {
  ::mlir::Builder odsBuilder(odsParser.getContext());
  ::llvm::SMLoc odsLoc = odsParser.getCurrentLocation();
  (void) odsLoc;
  ::mlir::FailureOr<UnpackedType> _result_elementType;
  // Parse literal '<'
  if (odsParser.parseLess()) return {};

  // Parse variable 'elementType'
  _result_elementType = ::mlir::FieldParser<UnpackedType>::parse(odsParser);
  if (::mlir::failed(_result_elementType)) {
    odsParser.emitError(odsParser.getCurrentLocation(), "failed to parse OpenUnpackedArrayType parameter 'elementType' which is to be a `UnpackedType`");
    return {};
  }
  // Parse literal '>'
  if (odsParser.parseGreater()) return {};
  assert(::mlir::succeeded(_result_elementType));
  return OpenUnpackedArrayType::get(odsParser.getContext(),
      UnpackedType((*_result_elementType)));
}

void OpenUnpackedArrayType::print(::mlir::AsmPrinter &odsPrinter) const {
  ::mlir::Builder odsBuilder(getContext());
  odsPrinter << "<";
  odsPrinter.printStrippedAttrOrType(getElementType());
  odsPrinter << ">";
}

UnpackedType OpenUnpackedArrayType::getElementType() const {
  return getImpl()->elementType;
}


} // namespace circt::moore
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::moore::OpenUnpackedArrayType)
namespace circt::moore {

namespace detail {

struct AssocArrayTypeStorage : public ::mlir::TypeStorage {
  using KeyTy = std::tuple<UnpackedType, UnpackedType>;
  AssocArrayTypeStorage(UnpackedType elementType, UnpackedType indexType) : elementType(std::move(elementType)), indexType(std::move(indexType)) {}

  KeyTy getAsKey() const {
    return KeyTy(elementType, indexType);
  }

  bool operator==(const KeyTy &tblgenKey) const {
    return (elementType == std::get<0>(tblgenKey)) && (indexType == std::get<1>(tblgenKey));
  }

  static ::llvm::hash_code hashKey(const KeyTy &tblgenKey) {
    return ::llvm::hash_combine(std::get<0>(tblgenKey), std::get<1>(tblgenKey));
  }

  static AssocArrayTypeStorage *construct(::mlir::TypeStorageAllocator &allocator, KeyTy &&tblgenKey) {
    auto elementType = std::move(std::get<0>(tblgenKey));
    auto indexType = std::move(std::get<1>(tblgenKey));
    return new (allocator.allocate<AssocArrayTypeStorage>()) AssocArrayTypeStorage(std::move(elementType), std::move(indexType));
  }

  UnpackedType elementType;
  UnpackedType indexType;
};

} // namespace detail
AssocArrayType AssocArrayType::get(::mlir::MLIRContext *context, UnpackedType elementType, UnpackedType indexType) {
  return Base::get(context, std::move(elementType), std::move(indexType));
}

AssocArrayType AssocArrayType::get(UnpackedType elementType, UnpackedType indexType) {
  return Base::get(elementType.getContext(), elementType, indexType);
}

::mlir::Type AssocArrayType::parse(::mlir::AsmParser &odsParser) {
  ::mlir::Builder odsBuilder(odsParser.getContext());
  ::llvm::SMLoc odsLoc = odsParser.getCurrentLocation();
  (void) odsLoc;
  ::mlir::FailureOr<UnpackedType> _result_elementType;
  ::mlir::FailureOr<UnpackedType> _result_indexType;
  // Parse literal '<'
  if (odsParser.parseLess()) return {};

  // Parse variable 'elementType'
  _result_elementType = ::mlir::FieldParser<UnpackedType>::parse(odsParser);
  if (::mlir::failed(_result_elementType)) {
    odsParser.emitError(odsParser.getCurrentLocation(), "failed to parse AssocArrayType parameter 'elementType' which is to be a `UnpackedType`");
    return {};
  }
  // Parse literal ','
  if (odsParser.parseComma()) return {};

  // Parse variable 'indexType'
  _result_indexType = ::mlir::FieldParser<UnpackedType>::parse(odsParser);
  if (::mlir::failed(_result_indexType)) {
    odsParser.emitError(odsParser.getCurrentLocation(), "failed to parse AssocArrayType parameter 'indexType' which is to be a `UnpackedType`");
    return {};
  }
  // Parse literal '>'
  if (odsParser.parseGreater()) return {};
  assert(::mlir::succeeded(_result_elementType));
  assert(::mlir::succeeded(_result_indexType));
  return AssocArrayType::get(odsParser.getContext(),
      UnpackedType((*_result_elementType)),
      UnpackedType((*_result_indexType)));
}

void AssocArrayType::print(::mlir::AsmPrinter &odsPrinter) const {
  ::mlir::Builder odsBuilder(getContext());
  odsPrinter << "<";
  odsPrinter.printStrippedAttrOrType(getElementType());
  odsPrinter << ",";
  odsPrinter << ' ';
  odsPrinter.printStrippedAttrOrType(getIndexType());
  odsPrinter << ">";
}

UnpackedType AssocArrayType::getElementType() const {
  return getImpl()->elementType;
}

UnpackedType AssocArrayType::getIndexType() const {
  return getImpl()->indexType;
}


} // namespace circt::moore
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::moore::AssocArrayType)
namespace circt::moore {

namespace detail {

struct QueueTypeStorage : public ::mlir::TypeStorage {
  using KeyTy = std::tuple<UnpackedType, unsigned>;
  QueueTypeStorage(UnpackedType elementType, unsigned bound) : elementType(std::move(elementType)), bound(std::move(bound)) {}

  KeyTy getAsKey() const {
    return KeyTy(elementType, bound);
  }

  bool operator==(const KeyTy &tblgenKey) const {
    return (elementType == std::get<0>(tblgenKey)) && (bound == std::get<1>(tblgenKey));
  }

  static ::llvm::hash_code hashKey(const KeyTy &tblgenKey) {
    return ::llvm::hash_combine(std::get<0>(tblgenKey), std::get<1>(tblgenKey));
  }

  static QueueTypeStorage *construct(::mlir::TypeStorageAllocator &allocator, KeyTy &&tblgenKey) {
    auto elementType = std::move(std::get<0>(tblgenKey));
    auto bound = std::move(std::get<1>(tblgenKey));
    return new (allocator.allocate<QueueTypeStorage>()) QueueTypeStorage(std::move(elementType), std::move(bound));
  }

  UnpackedType elementType;
  unsigned bound;
};

} // namespace detail
QueueType QueueType::get(::mlir::MLIRContext *context, UnpackedType elementType, unsigned bound) {
  return Base::get(context, std::move(elementType), std::move(bound));
}

QueueType QueueType::get(UnpackedType elementType, unsigned bound) {
  return Base::get(elementType.getContext(), elementType, bound);
}

::mlir::Type QueueType::parse(::mlir::AsmParser &odsParser) {
  ::mlir::Builder odsBuilder(odsParser.getContext());
  ::llvm::SMLoc odsLoc = odsParser.getCurrentLocation();
  (void) odsLoc;
  ::mlir::FailureOr<UnpackedType> _result_elementType;
  ::mlir::FailureOr<unsigned> _result_bound;
  // Parse literal '<'
  if (odsParser.parseLess()) return {};

  // Parse variable 'elementType'
  _result_elementType = ::mlir::FieldParser<UnpackedType>::parse(odsParser);
  if (::mlir::failed(_result_elementType)) {
    odsParser.emitError(odsParser.getCurrentLocation(), "failed to parse QueueType parameter 'elementType' which is to be a `UnpackedType`");
    return {};
  }
  // Parse literal ','
  if (odsParser.parseComma()) return {};

  // Parse variable 'bound'
  _result_bound = ::mlir::FieldParser<unsigned>::parse(odsParser);
  if (::mlir::failed(_result_bound)) {
    odsParser.emitError(odsParser.getCurrentLocation(), "failed to parse QueueType parameter 'bound' which is to be a `unsigned`");
    return {};
  }
  // Parse literal '>'
  if (odsParser.parseGreater()) return {};
  assert(::mlir::succeeded(_result_elementType));
  assert(::mlir::succeeded(_result_bound));
  return QueueType::get(odsParser.getContext(),
      UnpackedType((*_result_elementType)),
      unsigned((*_result_bound)));
}

void QueueType::print(::mlir::AsmPrinter &odsPrinter) const {
  ::mlir::Builder odsBuilder(getContext());
  odsPrinter << "<";
  odsPrinter.printStrippedAttrOrType(getElementType());
  odsPrinter << ",";
  odsPrinter << ' ';
  odsPrinter.printStrippedAttrOrType(getBound());
  odsPrinter << ">";
}

UnpackedType QueueType::getElementType() const {
  return getImpl()->elementType;
}

unsigned QueueType::getBound() const {
  return getImpl()->bound;
}


} // namespace circt::moore
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::moore::QueueType)
namespace circt::moore {

namespace detail {

struct StructTypeStorage : public ::mlir::TypeStorage {
  using KeyTy = std::tuple<::llvm::ArrayRef<StructLikeMember>>;
  StructTypeStorage(::llvm::ArrayRef<StructLikeMember> members) : members(std::move(members)) {}

  KeyTy getAsKey() const {
    return KeyTy(members);
  }

  bool operator==(const KeyTy &tblgenKey) const {
    return (members == std::get<0>(tblgenKey));
  }

  static ::llvm::hash_code hashKey(const KeyTy &tblgenKey) {
    return ::llvm::hash_combine(std::get<0>(tblgenKey));
  }

  static StructTypeStorage *construct(::mlir::TypeStorageAllocator &allocator, KeyTy &&tblgenKey) {
    auto members = std::move(std::get<0>(tblgenKey));
    members = allocator.copyInto(members);
    return new (allocator.allocate<StructTypeStorage>()) StructTypeStorage(std::move(members));
  }

  ::llvm::ArrayRef<StructLikeMember> members;
};

} // namespace detail
StructType StructType::get(::mlir::MLIRContext *context, ::llvm::ArrayRef<StructLikeMember> members) {
  return Base::get(context, std::move(members));
}

StructType StructType::getChecked(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::mlir::MLIRContext *context, ::llvm::ArrayRef<StructLikeMember> members) {
  return Base::getChecked(emitError, context, std::move(members));
}

::llvm::LogicalResult StructType::verifyInvariants(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::llvm::ArrayRef<StructLikeMember> members) {
  if (::mlir::failed(verify(emitError, members)))
    return ::mlir::failure();
  return ::mlir::success();
}

::mlir::Type StructType::parse(::mlir::AsmParser &odsParser) {
  ::mlir::Builder odsBuilder(odsParser.getContext());
  ::llvm::SMLoc odsLoc = odsParser.getCurrentLocation();
  (void) odsLoc;
  ::mlir::FailureOr<::llvm::SmallVector<StructLikeMember>> _result_members;
  // Parse literal '<'
  if (odsParser.parseLess()) return {};
  {
    auto odsCustomLoc = odsParser.getCurrentLocation();
    (void)odsCustomLoc;
    auto odsCustomResult = parseMembers(odsParser,
      ::mlir::detail::unwrapForCustomParse(_result_members));
    if (::mlir::failed(odsCustomResult)) return {};
    if (::mlir::failed(_result_members)) {
      odsParser.emitError(odsCustomLoc, "custom parser failed to parse parameter 'members'");
      return {};
    }
  }
  // Parse literal '>'
  if (odsParser.parseGreater()) return {};
  assert(::mlir::succeeded(_result_members));
  return odsParser.getChecked<StructType>(odsLoc, odsParser.getContext(),
      ::llvm::ArrayRef<StructLikeMember>((*_result_members)));
}

void StructType::print(::mlir::AsmPrinter &odsPrinter) const {
  ::mlir::Builder odsBuilder(getContext());
  odsPrinter << "<";
  printMembers(odsPrinter,
    getMembers());
  odsPrinter << ">";
}

::llvm::ArrayRef<StructLikeMember> StructType::getMembers() const {
  return getImpl()->members;
}


} // namespace circt::moore
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::moore::StructType)
namespace circt::moore {

namespace detail {

struct UnpackedStructTypeStorage : public ::mlir::TypeStorage {
  using KeyTy = std::tuple<::llvm::ArrayRef<StructLikeMember>>;
  UnpackedStructTypeStorage(::llvm::ArrayRef<StructLikeMember> members) : members(std::move(members)) {}

  KeyTy getAsKey() const {
    return KeyTy(members);
  }

  bool operator==(const KeyTy &tblgenKey) const {
    return (members == std::get<0>(tblgenKey));
  }

  static ::llvm::hash_code hashKey(const KeyTy &tblgenKey) {
    return ::llvm::hash_combine(std::get<0>(tblgenKey));
  }

  static UnpackedStructTypeStorage *construct(::mlir::TypeStorageAllocator &allocator, KeyTy &&tblgenKey) {
    auto members = std::move(std::get<0>(tblgenKey));
    members = allocator.copyInto(members);
    return new (allocator.allocate<UnpackedStructTypeStorage>()) UnpackedStructTypeStorage(std::move(members));
  }

  ::llvm::ArrayRef<StructLikeMember> members;
};

} // namespace detail
UnpackedStructType UnpackedStructType::get(::mlir::MLIRContext *context, ::llvm::ArrayRef<StructLikeMember> members) {
  return Base::get(context, std::move(members));
}

::mlir::Type UnpackedStructType::parse(::mlir::AsmParser &odsParser) {
  ::mlir::Builder odsBuilder(odsParser.getContext());
  ::llvm::SMLoc odsLoc = odsParser.getCurrentLocation();
  (void) odsLoc;
  ::mlir::FailureOr<::llvm::SmallVector<StructLikeMember>> _result_members;
  // Parse literal '<'
  if (odsParser.parseLess()) return {};
  {
    auto odsCustomLoc = odsParser.getCurrentLocation();
    (void)odsCustomLoc;
    auto odsCustomResult = parseMembers(odsParser,
      ::mlir::detail::unwrapForCustomParse(_result_members));
    if (::mlir::failed(odsCustomResult)) return {};
    if (::mlir::failed(_result_members)) {
      odsParser.emitError(odsCustomLoc, "custom parser failed to parse parameter 'members'");
      return {};
    }
  }
  // Parse literal '>'
  if (odsParser.parseGreater()) return {};
  assert(::mlir::succeeded(_result_members));
  return UnpackedStructType::get(odsParser.getContext(),
      ::llvm::ArrayRef<StructLikeMember>((*_result_members)));
}

void UnpackedStructType::print(::mlir::AsmPrinter &odsPrinter) const {
  ::mlir::Builder odsBuilder(getContext());
  odsPrinter << "<";
  printMembers(odsPrinter,
    getMembers());
  odsPrinter << ">";
}

::llvm::ArrayRef<StructLikeMember> UnpackedStructType::getMembers() const {
  return getImpl()->members;
}


} // namespace circt::moore
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::moore::UnpackedStructType)
namespace circt::moore {

namespace detail {

struct UnionTypeStorage : public ::mlir::TypeStorage {
  using KeyTy = std::tuple<::llvm::ArrayRef<StructLikeMember>>;
  UnionTypeStorage(::llvm::ArrayRef<StructLikeMember> members) : members(std::move(members)) {}

  KeyTy getAsKey() const {
    return KeyTy(members);
  }

  bool operator==(const KeyTy &tblgenKey) const {
    return (members == std::get<0>(tblgenKey));
  }

  static ::llvm::hash_code hashKey(const KeyTy &tblgenKey) {
    return ::llvm::hash_combine(std::get<0>(tblgenKey));
  }

  static UnionTypeStorage *construct(::mlir::TypeStorageAllocator &allocator, KeyTy &&tblgenKey) {
    auto members = std::move(std::get<0>(tblgenKey));
    members = allocator.copyInto(members);
    return new (allocator.allocate<UnionTypeStorage>()) UnionTypeStorage(std::move(members));
  }

  ::llvm::ArrayRef<StructLikeMember> members;
};

} // namespace detail
UnionType UnionType::get(::mlir::MLIRContext *context, ::llvm::ArrayRef<StructLikeMember> members) {
  return Base::get(context, std::move(members));
}

UnionType UnionType::getChecked(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::mlir::MLIRContext *context, ::llvm::ArrayRef<StructLikeMember> members) {
  return Base::getChecked(emitError, context, std::move(members));
}

::llvm::LogicalResult UnionType::verifyInvariants(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::llvm::ArrayRef<StructLikeMember> members) {
  if (::mlir::failed(verify(emitError, members)))
    return ::mlir::failure();
  return ::mlir::success();
}

::mlir::Type UnionType::parse(::mlir::AsmParser &odsParser) {
  ::mlir::Builder odsBuilder(odsParser.getContext());
  ::llvm::SMLoc odsLoc = odsParser.getCurrentLocation();
  (void) odsLoc;
  ::mlir::FailureOr<::llvm::SmallVector<StructLikeMember>> _result_members;
  // Parse literal '<'
  if (odsParser.parseLess()) return {};
  {
    auto odsCustomLoc = odsParser.getCurrentLocation();
    (void)odsCustomLoc;
    auto odsCustomResult = parseMembers(odsParser,
      ::mlir::detail::unwrapForCustomParse(_result_members));
    if (::mlir::failed(odsCustomResult)) return {};
    if (::mlir::failed(_result_members)) {
      odsParser.emitError(odsCustomLoc, "custom parser failed to parse parameter 'members'");
      return {};
    }
  }
  // Parse literal '>'
  if (odsParser.parseGreater()) return {};
  assert(::mlir::succeeded(_result_members));
  return odsParser.getChecked<UnionType>(odsLoc, odsParser.getContext(),
      ::llvm::ArrayRef<StructLikeMember>((*_result_members)));
}

void UnionType::print(::mlir::AsmPrinter &odsPrinter) const {
  ::mlir::Builder odsBuilder(getContext());
  odsPrinter << "<";
  printMembers(odsPrinter,
    getMembers());
  odsPrinter << ">";
}

::llvm::ArrayRef<StructLikeMember> UnionType::getMembers() const {
  return getImpl()->members;
}


} // namespace circt::moore
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::moore::UnionType)
namespace circt::moore {

namespace detail {

struct UnpackedUnionTypeStorage : public ::mlir::TypeStorage {
  using KeyTy = std::tuple<::llvm::ArrayRef<StructLikeMember>>;
  UnpackedUnionTypeStorage(::llvm::ArrayRef<StructLikeMember> members) : members(std::move(members)) {}

  KeyTy getAsKey() const {
    return KeyTy(members);
  }

  bool operator==(const KeyTy &tblgenKey) const {
    return (members == std::get<0>(tblgenKey));
  }

  static ::llvm::hash_code hashKey(const KeyTy &tblgenKey) {
    return ::llvm::hash_combine(std::get<0>(tblgenKey));
  }

  static UnpackedUnionTypeStorage *construct(::mlir::TypeStorageAllocator &allocator, KeyTy &&tblgenKey) {
    auto members = std::move(std::get<0>(tblgenKey));
    members = allocator.copyInto(members);
    return new (allocator.allocate<UnpackedUnionTypeStorage>()) UnpackedUnionTypeStorage(std::move(members));
  }

  ::llvm::ArrayRef<StructLikeMember> members;
};

} // namespace detail
UnpackedUnionType UnpackedUnionType::get(::mlir::MLIRContext *context, ::llvm::ArrayRef<StructLikeMember> members) {
  return Base::get(context, std::move(members));
}

::mlir::Type UnpackedUnionType::parse(::mlir::AsmParser &odsParser) {
  ::mlir::Builder odsBuilder(odsParser.getContext());
  ::llvm::SMLoc odsLoc = odsParser.getCurrentLocation();
  (void) odsLoc;
  ::mlir::FailureOr<::llvm::SmallVector<StructLikeMember>> _result_members;
  // Parse literal '<'
  if (odsParser.parseLess()) return {};
  {
    auto odsCustomLoc = odsParser.getCurrentLocation();
    (void)odsCustomLoc;
    auto odsCustomResult = parseMembers(odsParser,
      ::mlir::detail::unwrapForCustomParse(_result_members));
    if (::mlir::failed(odsCustomResult)) return {};
    if (::mlir::failed(_result_members)) {
      odsParser.emitError(odsCustomLoc, "custom parser failed to parse parameter 'members'");
      return {};
    }
  }
  // Parse literal '>'
  if (odsParser.parseGreater()) return {};
  assert(::mlir::succeeded(_result_members));
  return UnpackedUnionType::get(odsParser.getContext(),
      ::llvm::ArrayRef<StructLikeMember>((*_result_members)));
}

void UnpackedUnionType::print(::mlir::AsmPrinter &odsPrinter) const {
  ::mlir::Builder odsBuilder(getContext());
  odsPrinter << "<";
  printMembers(odsPrinter,
    getMembers());
  odsPrinter << ">";
}

::llvm::ArrayRef<StructLikeMember> UnpackedUnionType::getMembers() const {
  return getImpl()->members;
}


} // namespace circt::moore
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::moore::UnpackedUnionType)
namespace circt::moore {

namespace detail {

struct RefTypeStorage : public ::mlir::TypeStorage {
  using KeyTy = std::tuple<UnpackedType>;
  RefTypeStorage(UnpackedType nestedType) : nestedType(std::move(nestedType)) {}

  KeyTy getAsKey() const {
    return KeyTy(nestedType);
  }

  bool operator==(const KeyTy &tblgenKey) const {
    return (nestedType == std::get<0>(tblgenKey));
  }

  static ::llvm::hash_code hashKey(const KeyTy &tblgenKey) {
    return ::llvm::hash_combine(std::get<0>(tblgenKey));
  }

  static RefTypeStorage *construct(::mlir::TypeStorageAllocator &allocator, KeyTy &&tblgenKey) {
    auto nestedType = std::move(std::get<0>(tblgenKey));
    return new (allocator.allocate<RefTypeStorage>()) RefTypeStorage(std::move(nestedType));
  }

  UnpackedType nestedType;
};

} // namespace detail
RefType RefType::get(::mlir::MLIRContext *context, UnpackedType nestedType) {
  return Base::get(context, std::move(nestedType));
}

RefType RefType::get(UnpackedType nestedType) {
  return Base::get(nestedType.getContext(), nestedType);
}

::mlir::Type RefType::parse(::mlir::AsmParser &odsParser) {
  ::mlir::Builder odsBuilder(odsParser.getContext());
  ::llvm::SMLoc odsLoc = odsParser.getCurrentLocation();
  (void) odsLoc;
  ::mlir::FailureOr<UnpackedType> _result_nestedType;
  // Parse literal '<'
  if (odsParser.parseLess()) return {};

  // Parse variable 'nestedType'
  _result_nestedType = ::mlir::FieldParser<UnpackedType>::parse(odsParser);
  if (::mlir::failed(_result_nestedType)) {
    odsParser.emitError(odsParser.getCurrentLocation(), "failed to parse RefType parameter 'nestedType' which is to be a `UnpackedType`");
    return {};
  }
  // Parse literal '>'
  if (odsParser.parseGreater()) return {};
  assert(::mlir::succeeded(_result_nestedType));
  return RefType::get(odsParser.getContext(),
      UnpackedType((*_result_nestedType)));
}

void RefType::print(::mlir::AsmPrinter &odsPrinter) const {
  ::mlir::Builder odsBuilder(getContext());
  odsPrinter << "<";
  odsPrinter.printStrippedAttrOrType(getNestedType());
  odsPrinter << ">";
}

UnpackedType RefType::getNestedType() const {
  return getImpl()->nestedType;
}


} // namespace circt::moore
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::moore::RefType)
namespace circt::moore {


} // namespace circt::moore
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::moore::FormatStringType)

#endif // GET_TYPEDEF_CLASSES

