/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* TypeDef Definitions                                                        *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

#ifdef GET_TYPEDEF_LIST
#undef GET_TYPEDEF_LIST

::circt::sv::UnpackedOpenArrayType,
::circt::sv::InterfaceType,
::circt::sv::ModportType

#endif // GET_TYPEDEF_LIST

#ifdef GET_TYPEDEF_CLASSES
#undef GET_TYPEDEF_CLASSES

static ::mlir::OptionalParseResult generatedTypeParser(::mlir::AsmParser &parser, ::llvm::StringRef *mnemonic, ::mlir::Type &value) {
  return ::mlir::AsmParser::KeywordSwitch<::mlir::OptionalParseResult>(parser)
    .Case(::circt::sv::UnpackedOpenArrayType::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::sv::UnpackedOpenArrayType::parse(parser);
      return ::mlir::success(!!value);
    })
    .Case(::circt::sv::InterfaceType::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::sv::InterfaceType::parse(parser);
      return ::mlir::success(!!value);
    })
    .Case(::circt::sv::ModportType::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::sv::ModportType::parse(parser);
      return ::mlir::success(!!value);
    })
    .Default([&](llvm::StringRef keyword, llvm::SMLoc) {
      *mnemonic = keyword;
      return std::nullopt;
    });
}

static ::llvm::LogicalResult generatedTypePrinter(::mlir::Type def, ::mlir::AsmPrinter &printer) {
  return ::llvm::TypeSwitch<::mlir::Type, ::llvm::LogicalResult>(def)    .Case<::circt::sv::UnpackedOpenArrayType>([&](auto t) {
      printer << ::circt::sv::UnpackedOpenArrayType::getMnemonic();
t.print(printer);
      return ::mlir::success();
    })
    .Case<::circt::sv::InterfaceType>([&](auto t) {
      printer << ::circt::sv::InterfaceType::getMnemonic();
t.print(printer);
      return ::mlir::success();
    })
    .Case<::circt::sv::ModportType>([&](auto t) {
      printer << ::circt::sv::ModportType::getMnemonic();
t.print(printer);
      return ::mlir::success();
    })
    .Default([](auto) { return ::mlir::failure(); });
}

namespace circt::sv {

namespace detail {

struct UnpackedOpenArrayTypeStorage : public ::mlir::TypeStorage {
  using KeyTy = std::tuple<::mlir::Type>;
  UnpackedOpenArrayTypeStorage(::mlir::Type elementType) : elementType(std::move(elementType)) {}

  KeyTy getAsKey() const {
    return KeyTy(elementType);
  }

  bool operator==(const KeyTy &tblgenKey) const {
    return (elementType == std::get<0>(tblgenKey));
  }

  static ::llvm::hash_code hashKey(const KeyTy &tblgenKey) {
    return ::llvm::hash_combine(std::get<0>(tblgenKey));
  }

  static UnpackedOpenArrayTypeStorage *construct(::mlir::TypeStorageAllocator &allocator, KeyTy &&tblgenKey) {
    auto elementType = std::move(std::get<0>(tblgenKey));
    return new (allocator.allocate<UnpackedOpenArrayTypeStorage>()) UnpackedOpenArrayTypeStorage(std::move(elementType));
  }

  ::mlir::Type elementType;
};

} // namespace detail
UnpackedOpenArrayType UnpackedOpenArrayType::get(::mlir::MLIRContext *context, ::mlir::Type elementType) {
  return Base::get(context, std::move(elementType));
}

UnpackedOpenArrayType UnpackedOpenArrayType::get(Type elementType) {
  auto *ctx = elementType.getContext();
  return Base::get(ctx, elementType);
}

::mlir::Type UnpackedOpenArrayType::parse(::mlir::AsmParser &odsParser) {
  ::mlir::Builder odsBuilder(odsParser.getContext());
  ::llvm::SMLoc odsLoc = odsParser.getCurrentLocation();
  (void) odsLoc;
  ::mlir::FailureOr<::mlir::Type> _result_elementType;
  // Parse literal '<'
  if (odsParser.parseLess()) return {};

  // Parse variable 'elementType'
  _result_elementType = ::mlir::FieldParser<::mlir::Type>::parse(odsParser);
  if (::mlir::failed(_result_elementType)) {
    odsParser.emitError(odsParser.getCurrentLocation(), "failed to parse UnpackedOpenArrayTypeImpl parameter 'elementType' which is to be a `::mlir::Type`");
    return {};
  }
  // Parse literal '>'
  if (odsParser.parseGreater()) return {};
  assert(::mlir::succeeded(_result_elementType));
  return UnpackedOpenArrayType::get(odsParser.getContext(),
      ::mlir::Type((*_result_elementType)));
}

void UnpackedOpenArrayType::print(::mlir::AsmPrinter &odsPrinter) const {
  ::mlir::Builder odsBuilder(getContext());
  odsPrinter << "<";
  odsPrinter.printStrippedAttrOrType(getElementType());
  odsPrinter << ">";
}

::mlir::Type UnpackedOpenArrayType::getElementType() const {
  return getImpl()->elementType;
}


} // namespace circt::sv
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::sv::UnpackedOpenArrayType)
namespace circt::sv {

namespace detail {

struct InterfaceTypeStorage : public ::mlir::TypeStorage {
  using KeyTy = std::tuple<::mlir::FlatSymbolRefAttr>;
  InterfaceTypeStorage(::mlir::FlatSymbolRefAttr interface) : interface(std::move(interface)) {}

  KeyTy getAsKey() const {
    return KeyTy(interface);
  }

  bool operator==(const KeyTy &tblgenKey) const {
    return (interface == std::get<0>(tblgenKey));
  }

  static ::llvm::hash_code hashKey(const KeyTy &tblgenKey) {
    return ::llvm::hash_combine(std::get<0>(tblgenKey));
  }

  static InterfaceTypeStorage *construct(::mlir::TypeStorageAllocator &allocator, KeyTy &&tblgenKey) {
    auto interface = std::move(std::get<0>(tblgenKey));
    return new (allocator.allocate<InterfaceTypeStorage>()) InterfaceTypeStorage(std::move(interface));
  }

  ::mlir::FlatSymbolRefAttr interface;
};

} // namespace detail
InterfaceType InterfaceType::get(::mlir::MLIRContext *context, ::mlir::FlatSymbolRefAttr interface) {
  return Base::get(context, std::move(interface));
}

::mlir::Type InterfaceType::parse(::mlir::AsmParser &odsParser) {
  ::mlir::Builder odsBuilder(odsParser.getContext());
  ::llvm::SMLoc odsLoc = odsParser.getCurrentLocation();
  (void) odsLoc;
  ::mlir::FailureOr<::mlir::FlatSymbolRefAttr> _result_interface;
  // Parse literal '<'
  if (odsParser.parseLess()) return {};

  // Parse variable 'interface'
  _result_interface = ::mlir::FieldParser<::mlir::FlatSymbolRefAttr>::parse(odsParser);
  if (::mlir::failed(_result_interface)) {
    odsParser.emitError(odsParser.getCurrentLocation(), "failed to parse InterfaceType parameter 'interface' which is to be a `::mlir::FlatSymbolRefAttr`");
    return {};
  }
  // Parse literal '>'
  if (odsParser.parseGreater()) return {};
  assert(::mlir::succeeded(_result_interface));
  return InterfaceType::get(odsParser.getContext(),
      ::mlir::FlatSymbolRefAttr((*_result_interface)));
}

void InterfaceType::print(::mlir::AsmPrinter &odsPrinter) const {
  ::mlir::Builder odsBuilder(getContext());
  odsPrinter << "<";
  odsPrinter.printStrippedAttrOrType(getInterface());
  odsPrinter << ">";
}

::mlir::FlatSymbolRefAttr InterfaceType::getInterface() const {
  return getImpl()->interface;
}


} // namespace circt::sv
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::sv::InterfaceType)
namespace circt::sv {

namespace detail {

struct ModportTypeStorage : public ::mlir::TypeStorage {
  using KeyTy = std::tuple<::mlir::SymbolRefAttr>;
  ModportTypeStorage(::mlir::SymbolRefAttr modport) : modport(std::move(modport)) {}

  KeyTy getAsKey() const {
    return KeyTy(modport);
  }

  bool operator==(const KeyTy &tblgenKey) const {
    return (modport == std::get<0>(tblgenKey));
  }

  static ::llvm::hash_code hashKey(const KeyTy &tblgenKey) {
    return ::llvm::hash_combine(std::get<0>(tblgenKey));
  }

  static ModportTypeStorage *construct(::mlir::TypeStorageAllocator &allocator, KeyTy &&tblgenKey) {
    auto modport = std::move(std::get<0>(tblgenKey));
    return new (allocator.allocate<ModportTypeStorage>()) ModportTypeStorage(std::move(modport));
  }

  ::mlir::SymbolRefAttr modport;
};

} // namespace detail
ModportType ModportType::get(::mlir::MLIRContext *context, ::mlir::SymbolRefAttr modport) {
  return Base::get(context, std::move(modport));
}

::mlir::Type ModportType::parse(::mlir::AsmParser &odsParser) {
  ::mlir::Builder odsBuilder(odsParser.getContext());
  ::llvm::SMLoc odsLoc = odsParser.getCurrentLocation();
  (void) odsLoc;
  ::mlir::FailureOr<::mlir::SymbolRefAttr> _result_modport;
  // Parse literal '<'
  if (odsParser.parseLess()) return {};

  // Parse variable 'modport'
  _result_modport = ::mlir::FieldParser<::mlir::SymbolRefAttr>::parse(odsParser);
  if (::mlir::failed(_result_modport)) {
    odsParser.emitError(odsParser.getCurrentLocation(), "failed to parse ModportType parameter 'modport' which is to be a `::mlir::SymbolRefAttr`");
    return {};
  }
  // Parse literal '>'
  if (odsParser.parseGreater()) return {};
  assert(::mlir::succeeded(_result_modport));
  return ModportType::get(odsParser.getContext(),
      ::mlir::SymbolRefAttr((*_result_modport)));
}

void ModportType::print(::mlir::AsmPrinter &odsPrinter) const {
  ::mlir::Builder odsBuilder(getContext());
  odsPrinter << "<";
  odsPrinter.printStrippedAttrOrType(getModport());
  odsPrinter << ">";
}

::mlir::SymbolRefAttr ModportType::getModport() const {
  return getImpl()->modport;
}


} // namespace circt::sv
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::sv::ModportType)
namespace circt::sv {


/// Parse a type registered to this dialect.
::mlir::Type SVDialect::parseType(::mlir::DialectAsmParser &parser) const {
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
void SVDialect::printType(::mlir::Type type,
                    ::mlir::DialectAsmPrinter &printer) const {
  if (::mlir::succeeded(generatedTypePrinter(type, printer)))
    return;
  
}

} // namespace circt::sv

#endif // GET_TYPEDEF_CLASSES

