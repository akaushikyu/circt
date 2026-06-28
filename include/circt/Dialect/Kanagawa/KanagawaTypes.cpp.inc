/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* TypeDef Definitions                                                        *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

#ifdef GET_TYPEDEF_LIST
#undef GET_TYPEDEF_LIST

::circt::kanagawa::ScopeRefType,
::circt::kanagawa::PortRefType

#endif // GET_TYPEDEF_LIST

#ifdef GET_TYPEDEF_CLASSES
#undef GET_TYPEDEF_CLASSES

static ::mlir::OptionalParseResult generatedTypeParser(::mlir::AsmParser &parser, ::llvm::StringRef *mnemonic, ::mlir::Type &value) {
  return ::mlir::AsmParser::KeywordSwitch<::mlir::OptionalParseResult>(parser)
    .Case(::circt::kanagawa::ScopeRefType::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::kanagawa::ScopeRefType::parse(parser);
      return ::mlir::success(!!value);
    })
    .Case(::circt::kanagawa::PortRefType::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::kanagawa::PortRefType::parse(parser);
      return ::mlir::success(!!value);
    })
    .Default([&](llvm::StringRef keyword, llvm::SMLoc) {
      *mnemonic = keyword;
      return std::nullopt;
    });
}

static ::llvm::LogicalResult generatedTypePrinter(::mlir::Type def, ::mlir::AsmPrinter &printer) {
  return ::llvm::TypeSwitch<::mlir::Type, ::llvm::LogicalResult>(def)    .Case<::circt::kanagawa::ScopeRefType>([&](auto t) {
      printer << ::circt::kanagawa::ScopeRefType::getMnemonic();
t.print(printer);
      return ::mlir::success();
    })
    .Case<::circt::kanagawa::PortRefType>([&](auto t) {
      printer << ::circt::kanagawa::PortRefType::getMnemonic();
t.print(printer);
      return ::mlir::success();
    })
    .Default([](auto) { return ::mlir::failure(); });
}

namespace circt::kanagawa {

namespace detail {

struct ScopeRefTypeStorage : public ::mlir::TypeStorage {
  using KeyTy = std::tuple<::circt::hw::InnerRefAttr>;
  ScopeRefTypeStorage(::circt::hw::InnerRefAttr scopeRef) : scopeRef(std::move(scopeRef)) {}

  KeyTy getAsKey() const {
    return KeyTy(scopeRef);
  }

  bool operator==(const KeyTy &tblgenKey) const {
    return (scopeRef == std::get<0>(tblgenKey));
  }

  static ::llvm::hash_code hashKey(const KeyTy &tblgenKey) {
    return ::llvm::hash_combine(std::get<0>(tblgenKey));
  }

  static ScopeRefTypeStorage *construct(::mlir::TypeStorageAllocator &allocator, KeyTy &&tblgenKey) {
    auto scopeRef = std::move(std::get<0>(tblgenKey));
    return new (allocator.allocate<ScopeRefTypeStorage>()) ScopeRefTypeStorage(std::move(scopeRef));
  }

  ::circt::hw::InnerRefAttr scopeRef;
};

} // namespace detail
ScopeRefType ScopeRefType::get(::mlir::MLIRContext *context, ::circt::hw::InnerRefAttr scopeRef) {
  return Base::get(context, std::move(scopeRef));
}

ScopeRefType ScopeRefType::get(::mlir::MLIRContext *context) {
  return Base::get(context, nullptr);
}

::circt::hw::InnerRefAttr ScopeRefType::getScopeRef() const {
  return getImpl()->scopeRef;
}


} // namespace circt::kanagawa
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::kanagawa::ScopeRefType)
namespace circt::kanagawa {

namespace detail {

struct PortRefTypeStorage : public ::mlir::TypeStorage {
  using KeyTy = std::tuple<TypeAttr, kanagawa::Direction>;
  PortRefTypeStorage(TypeAttr portTypeAttr, kanagawa::Direction direction) : portTypeAttr(std::move(portTypeAttr)), direction(std::move(direction)) {}

  KeyTy getAsKey() const {
    return KeyTy(portTypeAttr, direction);
  }

  bool operator==(const KeyTy &tblgenKey) const {
    return (portTypeAttr == std::get<0>(tblgenKey)) && (direction == std::get<1>(tblgenKey));
  }

  static ::llvm::hash_code hashKey(const KeyTy &tblgenKey) {
    return ::llvm::hash_combine(std::get<0>(tblgenKey), std::get<1>(tblgenKey));
  }

  static PortRefTypeStorage *construct(::mlir::TypeStorageAllocator &allocator, KeyTy &&tblgenKey) {
    auto portTypeAttr = std::move(std::get<0>(tblgenKey));
    auto direction = std::move(std::get<1>(tblgenKey));
    return new (allocator.allocate<PortRefTypeStorage>()) PortRefTypeStorage(std::move(portTypeAttr), std::move(direction));
  }

  TypeAttr portTypeAttr;
  kanagawa::Direction direction;
};

} // namespace detail
PortRefType PortRefType::get(::mlir::MLIRContext *context, TypeAttr portTypeAttr, kanagawa::Direction direction) {
  return Base::get(context, std::move(portTypeAttr), std::move(direction));
}

PortRefType PortRefType::get(::mlir::MLIRContext *context, Type t, kanagawa::Direction d) {
  return Base::get(context, TypeAttr::get(t), d);
}

::mlir::Type PortRefType::parse(::mlir::AsmParser &odsParser) {
  ::mlir::Builder odsBuilder(odsParser.getContext());
  ::llvm::SMLoc odsLoc = odsParser.getCurrentLocation();
  (void) odsLoc;
  ::mlir::FailureOr<TypeAttr> _result_portTypeAttr;
  ::mlir::FailureOr<kanagawa::Direction> _result_direction;
  // Parse literal '<'
  if (odsParser.parseLess()) return {};

  // Parse variable 'direction'
  _result_direction = ::mlir::FieldParser<kanagawa::Direction>::parse(odsParser);
  if (::mlir::failed(_result_direction)) {
    odsParser.emitError(odsParser.getCurrentLocation(), "failed to parse PortRefType parameter 'direction' which is to be a `kanagawa::Direction`");
    return {};
  }

  // Parse variable 'portTypeAttr'
  _result_portTypeAttr = ::mlir::FieldParser<TypeAttr>::parse(odsParser);
  if (::mlir::failed(_result_portTypeAttr)) {
    odsParser.emitError(odsParser.getCurrentLocation(), "failed to parse PortRefType parameter 'portTypeAttr' which is to be a `TypeAttr`");
    return {};
  }
  // Parse literal '>'
  if (odsParser.parseGreater()) return {};
  assert(::mlir::succeeded(_result_portTypeAttr));
  assert(::mlir::succeeded(_result_direction));
  return PortRefType::get(odsParser.getContext(),
      TypeAttr((*_result_portTypeAttr)),
      kanagawa::Direction((*_result_direction)));
}

void PortRefType::print(::mlir::AsmPrinter &odsPrinter) const {
  ::mlir::Builder odsBuilder(getContext());
  odsPrinter << "<";
  odsPrinter.printStrippedAttrOrType(getDirection());
  odsPrinter << ' ';
  odsPrinter.printStrippedAttrOrType(getPortTypeAttr());
  odsPrinter << ">";
}

TypeAttr PortRefType::getPortTypeAttr() const {
  return getImpl()->portTypeAttr;
}

kanagawa::Direction PortRefType::getDirection() const {
  return getImpl()->direction;
}


} // namespace circt::kanagawa
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::kanagawa::PortRefType)
namespace circt::kanagawa {


/// Parse a type registered to this dialect.
::mlir::Type KanagawaDialect::parseType(::mlir::DialectAsmParser &parser) const {
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
void KanagawaDialect::printType(::mlir::Type type,
                    ::mlir::DialectAsmPrinter &printer) const {
  if (::mlir::succeeded(generatedTypePrinter(type, printer)))
    return;
  
}

} // namespace circt::kanagawa

#endif // GET_TYPEDEF_CLASSES

