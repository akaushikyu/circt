/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* TypeDef Definitions                                                        *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

#ifdef GET_TYPEDEF_LIST
#undef GET_TYPEDEF_LIST

::circt::llhd::TimeType,
::circt::llhd::RefType

#endif // GET_TYPEDEF_LIST

#ifdef GET_TYPEDEF_CLASSES
#undef GET_TYPEDEF_CLASSES

static ::mlir::OptionalParseResult generatedTypeParser(::mlir::AsmParser &parser, ::llvm::StringRef *mnemonic, ::mlir::Type &value) {
  return ::mlir::AsmParser::KeywordSwitch<::mlir::OptionalParseResult>(parser)
    .Case(::circt::llhd::TimeType::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::llhd::TimeType::get(parser.getContext());
      return ::mlir::success(!!value);
    })
    .Case(::circt::llhd::RefType::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::llhd::RefType::parse(parser);
      return ::mlir::success(!!value);
    })
    .Default([&](llvm::StringRef keyword, llvm::SMLoc) {
      *mnemonic = keyword;
      return std::nullopt;
    });
}

static ::llvm::LogicalResult generatedTypePrinter(::mlir::Type def, ::mlir::AsmPrinter &printer) {
  return ::llvm::TypeSwitch<::mlir::Type, ::llvm::LogicalResult>(def)    .Case<::circt::llhd::TimeType>([&](auto t) {
      printer << ::circt::llhd::TimeType::getMnemonic();
      return ::mlir::success();
    })
    .Case<::circt::llhd::RefType>([&](auto t) {
      printer << ::circt::llhd::RefType::getMnemonic();
t.print(printer);
      return ::mlir::success();
    })
    .Default([](auto) { return ::mlir::failure(); });
}

namespace circt::llhd {


} // namespace circt::llhd
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::llhd::TimeType)
namespace circt::llhd {

namespace detail {

struct RefTypeStorage : public ::mlir::TypeStorage {
  using KeyTy = std::tuple<Type>;
  RefTypeStorage(Type nestedType) : nestedType(std::move(nestedType)) {}

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

  Type nestedType;
};

} // namespace detail
RefType RefType::get(::mlir::MLIRContext *context, Type nestedType) {
  return Base::get(context, std::move(nestedType));
}

RefType RefType::get(Type nestedType) {
  return Base::get(nestedType.getContext(), nestedType);
}

::mlir::Type RefType::parse(::mlir::AsmParser &odsParser) {
  ::mlir::Builder odsBuilder(odsParser.getContext());
  ::llvm::SMLoc odsLoc = odsParser.getCurrentLocation();
  (void) odsLoc;
  ::mlir::FailureOr<Type> _result_nestedType;
  // Parse literal '<'
  if (odsParser.parseLess()) return {};

  // Parse variable 'nestedType'
  _result_nestedType = ::mlir::FieldParser<Type>::parse(odsParser);
  if (::mlir::failed(_result_nestedType)) {
    odsParser.emitError(odsParser.getCurrentLocation(), "failed to parse RefType parameter 'nestedType' which is to be a `Type`");
    return {};
  }
  // Parse literal '>'
  if (odsParser.parseGreater()) return {};
  assert(::mlir::succeeded(_result_nestedType));
  return RefType::get(odsParser.getContext(),
      Type((*_result_nestedType)));
}

void RefType::print(::mlir::AsmPrinter &odsPrinter) const {
  ::mlir::Builder odsBuilder(getContext());
  odsPrinter << "<";
  odsPrinter.printStrippedAttrOrType(getNestedType());
  odsPrinter << ">";
}

Type RefType::getNestedType() const {
  return getImpl()->nestedType;
}


} // namespace circt::llhd
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::llhd::RefType)
namespace circt::llhd {


/// Parse a type registered to this dialect.
::mlir::Type LLHDDialect::parseType(::mlir::DialectAsmParser &parser) const {
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
void LLHDDialect::printType(::mlir::Type type,
                    ::mlir::DialectAsmPrinter &printer) const {
  if (::mlir::succeeded(generatedTypePrinter(type, printer)))
    return;
  
}

} // namespace circt::llhd

#endif // GET_TYPEDEF_CLASSES

