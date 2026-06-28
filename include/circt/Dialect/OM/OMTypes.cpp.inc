/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* TypeDef Definitions                                                        *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

#ifdef GET_TYPEDEF_LIST
#undef GET_TYPEDEF_LIST

::circt::om::ClassType,
::circt::om::ReferenceType,
::circt::om::ListType,
::circt::om::SymbolRefType,
::circt::om::OMIntegerType,
::circt::om::StringType,
::circt::om::BasePathType,
::circt::om::PathType,
::circt::om::FrozenBasePathType,
::circt::om::FrozenPathType,
::circt::om::AnyType

#endif // GET_TYPEDEF_LIST

#ifdef GET_TYPEDEF_CLASSES
#undef GET_TYPEDEF_CLASSES

static ::mlir::OptionalParseResult generatedTypeParser(::mlir::AsmParser &parser, ::llvm::StringRef *mnemonic, ::mlir::Type &value) {
  return ::mlir::AsmParser::KeywordSwitch<::mlir::OptionalParseResult>(parser)
    .Case(::circt::om::ClassType::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::om::ClassType::parse(parser);
      return ::mlir::success(!!value);
    })
    .Case(::circt::om::ReferenceType::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::om::ReferenceType::get(parser.getContext());
      return ::mlir::success(!!value);
    })
    .Case(::circt::om::ListType::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::om::ListType::parse(parser);
      return ::mlir::success(!!value);
    })
    .Case(::circt::om::SymbolRefType::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::om::SymbolRefType::get(parser.getContext());
      return ::mlir::success(!!value);
    })
    .Case(::circt::om::OMIntegerType::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::om::OMIntegerType::get(parser.getContext());
      return ::mlir::success(!!value);
    })
    .Case(::circt::om::StringType::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::om::StringType::get(parser.getContext());
      return ::mlir::success(!!value);
    })
    .Case(::circt::om::BasePathType::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::om::BasePathType::get(parser.getContext());
      return ::mlir::success(!!value);
    })
    .Case(::circt::om::PathType::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::om::PathType::get(parser.getContext());
      return ::mlir::success(!!value);
    })
    .Case(::circt::om::FrozenBasePathType::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::om::FrozenBasePathType::get(parser.getContext());
      return ::mlir::success(!!value);
    })
    .Case(::circt::om::FrozenPathType::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::om::FrozenPathType::get(parser.getContext());
      return ::mlir::success(!!value);
    })
    .Case(::circt::om::AnyType::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::om::AnyType::get(parser.getContext());
      return ::mlir::success(!!value);
    })
    .Default([&](llvm::StringRef keyword, llvm::SMLoc) {
      *mnemonic = keyword;
      return std::nullopt;
    });
}

static ::llvm::LogicalResult generatedTypePrinter(::mlir::Type def, ::mlir::AsmPrinter &printer) {
  return ::llvm::TypeSwitch<::mlir::Type, ::llvm::LogicalResult>(def)    .Case<::circt::om::ClassType>([&](auto t) {
      printer << ::circt::om::ClassType::getMnemonic();
t.print(printer);
      return ::mlir::success();
    })
    .Case<::circt::om::ReferenceType>([&](auto t) {
      printer << ::circt::om::ReferenceType::getMnemonic();
      return ::mlir::success();
    })
    .Case<::circt::om::ListType>([&](auto t) {
      printer << ::circt::om::ListType::getMnemonic();
t.print(printer);
      return ::mlir::success();
    })
    .Case<::circt::om::SymbolRefType>([&](auto t) {
      printer << ::circt::om::SymbolRefType::getMnemonic();
      return ::mlir::success();
    })
    .Case<::circt::om::OMIntegerType>([&](auto t) {
      printer << ::circt::om::OMIntegerType::getMnemonic();
      return ::mlir::success();
    })
    .Case<::circt::om::StringType>([&](auto t) {
      printer << ::circt::om::StringType::getMnemonic();
      return ::mlir::success();
    })
    .Case<::circt::om::BasePathType>([&](auto t) {
      printer << ::circt::om::BasePathType::getMnemonic();
      return ::mlir::success();
    })
    .Case<::circt::om::PathType>([&](auto t) {
      printer << ::circt::om::PathType::getMnemonic();
      return ::mlir::success();
    })
    .Case<::circt::om::FrozenBasePathType>([&](auto t) {
      printer << ::circt::om::FrozenBasePathType::getMnemonic();
      return ::mlir::success();
    })
    .Case<::circt::om::FrozenPathType>([&](auto t) {
      printer << ::circt::om::FrozenPathType::getMnemonic();
      return ::mlir::success();
    })
    .Case<::circt::om::AnyType>([&](auto t) {
      printer << ::circt::om::AnyType::getMnemonic();
      return ::mlir::success();
    })
    .Default([](auto) { return ::mlir::failure(); });
}

namespace circt::om {

namespace detail {

struct ClassTypeStorage : public ::mlir::TypeStorage {
  using KeyTy = std::tuple<mlir::FlatSymbolRefAttr>;
  ClassTypeStorage(mlir::FlatSymbolRefAttr className) : className(std::move(className)) {}

  KeyTy getAsKey() const {
    return KeyTy(className);
  }

  bool operator==(const KeyTy &tblgenKey) const {
    return (className == std::get<0>(tblgenKey));
  }

  static ::llvm::hash_code hashKey(const KeyTy &tblgenKey) {
    return ::llvm::hash_combine(std::get<0>(tblgenKey));
  }

  static ClassTypeStorage *construct(::mlir::TypeStorageAllocator &allocator, KeyTy &&tblgenKey) {
    auto className = std::move(std::get<0>(tblgenKey));
    return new (allocator.allocate<ClassTypeStorage>()) ClassTypeStorage(std::move(className));
  }

  mlir::FlatSymbolRefAttr className;
};

} // namespace detail
ClassType ClassType::get(::mlir::MLIRContext *context, mlir::FlatSymbolRefAttr className) {
  return Base::get(context, std::move(className));
}

::mlir::Type ClassType::parse(::mlir::AsmParser &odsParser) {
  ::mlir::Builder odsBuilder(odsParser.getContext());
  ::llvm::SMLoc odsLoc = odsParser.getCurrentLocation();
  (void) odsLoc;
  ::mlir::FailureOr<mlir::FlatSymbolRefAttr> _result_className;
  // Parse literal '<'
  if (odsParser.parseLess()) return {};

  // Parse variable 'className'
  _result_className = ::mlir::FieldParser<mlir::FlatSymbolRefAttr>::parse(odsParser);
  if (::mlir::failed(_result_className)) {
    odsParser.emitError(odsParser.getCurrentLocation(), "failed to parse ClassType parameter 'className' which is to be a `mlir::FlatSymbolRefAttr`");
    return {};
  }
  // Parse literal '>'
  if (odsParser.parseGreater()) return {};
  assert(::mlir::succeeded(_result_className));
  return ClassType::get(odsParser.getContext(),
      mlir::FlatSymbolRefAttr((*_result_className)));
}

void ClassType::print(::mlir::AsmPrinter &odsPrinter) const {
  ::mlir::Builder odsBuilder(getContext());
  odsPrinter << "<";
  odsPrinter.printStrippedAttrOrType(getClassName());
  odsPrinter << ">";
}

mlir::FlatSymbolRefAttr ClassType::getClassName() const {
  return getImpl()->className;
}


} // namespace circt::om
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::om::ClassType)
namespace circt::om {


} // namespace circt::om
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::om::ReferenceType)
namespace circt::om {

namespace detail {

struct ListTypeStorage : public ::mlir::TypeStorage {
  using KeyTy = std::tuple<mlir::Type>;
  ListTypeStorage(mlir::Type elementType) : elementType(std::move(elementType)) {}

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

  mlir::Type elementType;
};

} // namespace detail
ListType ListType::get(::mlir::MLIRContext *context, mlir::Type elementType) {
  return Base::get(context, std::move(elementType));
}

ListType ListType::get(::mlir::Type elementType) {
  return Base::get(elementType.getContext(), elementType);
}

::mlir::Type ListType::parse(::mlir::AsmParser &odsParser) {
  ::mlir::Builder odsBuilder(odsParser.getContext());
  ::llvm::SMLoc odsLoc = odsParser.getCurrentLocation();
  (void) odsLoc;
  ::mlir::FailureOr<mlir::Type> _result_elementType;
  // Parse literal '<'
  if (odsParser.parseLess()) return {};

  // Parse variable 'elementType'
  _result_elementType = ::mlir::FieldParser<mlir::Type>::parse(odsParser);
  if (::mlir::failed(_result_elementType)) {
    odsParser.emitError(odsParser.getCurrentLocation(), "failed to parse ListType parameter 'elementType' which is to be a `mlir::Type`");
    return {};
  }
  // Parse literal '>'
  if (odsParser.parseGreater()) return {};
  assert(::mlir::succeeded(_result_elementType));
  return ListType::get(odsParser.getContext(),
      mlir::Type((*_result_elementType)));
}

void ListType::print(::mlir::AsmPrinter &odsPrinter) const {
  ::mlir::Builder odsBuilder(getContext());
  odsPrinter << "<";
  odsPrinter.printStrippedAttrOrType(getElementType());
  odsPrinter << ">";
}

mlir::Type ListType::getElementType() const {
  return getImpl()->elementType;
}


} // namespace circt::om
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::om::ListType)
namespace circt::om {


} // namespace circt::om
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::om::SymbolRefType)
namespace circt::om {


} // namespace circt::om
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::om::OMIntegerType)
namespace circt::om {


} // namespace circt::om
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::om::StringType)
namespace circt::om {


} // namespace circt::om
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::om::BasePathType)
namespace circt::om {


} // namespace circt::om
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::om::PathType)
namespace circt::om {


} // namespace circt::om
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::om::FrozenBasePathType)
namespace circt::om {


} // namespace circt::om
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::om::FrozenPathType)
namespace circt::om {


} // namespace circt::om
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::om::AnyType)
namespace circt::om {


/// Parse a type registered to this dialect.
::mlir::Type OMDialect::parseType(::mlir::DialectAsmParser &parser) const {
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
void OMDialect::printType(::mlir::Type type,
                    ::mlir::DialectAsmPrinter &printer) const {
  if (::mlir::succeeded(generatedTypePrinter(type, printer)))
    return;
  
}

} // namespace circt::om

#endif // GET_TYPEDEF_CLASSES

