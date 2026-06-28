/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* TypeDef Definitions                                                        *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

#ifdef GET_TYPEDEF_LIST
#undef GET_TYPEDEF_LIST

::circt::sim::FormatStringType,
::circt::sim::DynamicStringType,
::circt::sim::QueueType,
::circt::sim::DPIFunctionType,
::circt::sim::OutputStreamType

#endif // GET_TYPEDEF_LIST

#ifdef GET_TYPEDEF_CLASSES
#undef GET_TYPEDEF_CLASSES

static ::mlir::OptionalParseResult generatedTypeParser(::mlir::AsmParser &parser, ::llvm::StringRef *mnemonic, ::mlir::Type &value) {
  return ::mlir::AsmParser::KeywordSwitch<::mlir::OptionalParseResult>(parser)
    .Case(::circt::sim::FormatStringType::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::sim::FormatStringType::get(parser.getContext());
      return ::mlir::success(!!value);
    })
    .Case(::circt::sim::DynamicStringType::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::sim::DynamicStringType::get(parser.getContext());
      return ::mlir::success(!!value);
    })
    .Case(::circt::sim::QueueType::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::sim::QueueType::parse(parser);
      return ::mlir::success(!!value);
    })
    .Case(::circt::sim::DPIFunctionType::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::sim::DPIFunctionType::parse(parser);
      return ::mlir::success(!!value);
    })
    .Case(::circt::sim::OutputStreamType::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::sim::OutputStreamType::get(parser.getContext());
      return ::mlir::success(!!value);
    })
    .Default([&](llvm::StringRef keyword, llvm::SMLoc) {
      *mnemonic = keyword;
      return std::nullopt;
    });
}

static ::llvm::LogicalResult generatedTypePrinter(::mlir::Type def, ::mlir::AsmPrinter &printer) {
  return ::llvm::TypeSwitch<::mlir::Type, ::llvm::LogicalResult>(def)    .Case<::circt::sim::FormatStringType>([&](auto t) {
      printer << ::circt::sim::FormatStringType::getMnemonic();
      return ::mlir::success();
    })
    .Case<::circt::sim::DynamicStringType>([&](auto t) {
      printer << ::circt::sim::DynamicStringType::getMnemonic();
      return ::mlir::success();
    })
    .Case<::circt::sim::QueueType>([&](auto t) {
      printer << ::circt::sim::QueueType::getMnemonic();
t.print(printer);
      return ::mlir::success();
    })
    .Case<::circt::sim::DPIFunctionType>([&](auto t) {
      printer << ::circt::sim::DPIFunctionType::getMnemonic();
t.print(printer);
      return ::mlir::success();
    })
    .Case<::circt::sim::OutputStreamType>([&](auto t) {
      printer << ::circt::sim::OutputStreamType::getMnemonic();
      return ::mlir::success();
    })
    .Default([](auto) { return ::mlir::failure(); });
}

namespace circt::sim {


} // namespace circt::sim
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::sim::FormatStringType)
namespace circt::sim {


} // namespace circt::sim
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::sim::DynamicStringType)
namespace circt::sim {

namespace detail {

struct QueueTypeStorage : public ::mlir::TypeStorage {
  using KeyTy = std::tuple<::mlir::Type, unsigned>;
  QueueTypeStorage(::mlir::Type elementType, unsigned bound) : elementType(std::move(elementType)), bound(std::move(bound)) {}

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

  ::mlir::Type elementType;
  unsigned bound;
};

} // namespace detail
QueueType QueueType::get(::mlir::MLIRContext *context, ::mlir::Type elementType, unsigned bound) {
  return Base::get(context, std::move(elementType), std::move(bound));
}

QueueType QueueType::get(Type elementType, unsigned bound) {
  return Base::get(elementType.getContext(), elementType, bound);
}

::mlir::Type QueueType::parse(::mlir::AsmParser &odsParser) {
  ::mlir::Builder odsBuilder(odsParser.getContext());
  ::llvm::SMLoc odsLoc = odsParser.getCurrentLocation();
  (void) odsLoc;
  ::mlir::FailureOr<::mlir::Type> _result_elementType;
  ::mlir::FailureOr<unsigned> _result_bound;
  // Parse literal '<'
  if (odsParser.parseLess()) return {};

  // Parse variable 'elementType'
  _result_elementType = ::mlir::FieldParser<::mlir::Type>::parse(odsParser);
  if (::mlir::failed(_result_elementType)) {
    odsParser.emitError(odsParser.getCurrentLocation(), "failed to parse QueueType parameter 'elementType' which is to be a `::mlir::Type`");
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
      ::mlir::Type((*_result_elementType)),
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

::mlir::Type QueueType::getElementType() const {
  return getImpl()->elementType;
}

unsigned QueueType::getBound() const {
  return getImpl()->bound;
}


} // namespace circt::sim
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::sim::QueueType)
namespace circt::sim {

DPIFunctionType DPIFunctionType::get(::mlir::MLIRContext *context, ::llvm::ArrayRef<::circt::sim::DPIArgument> arguments) {
  return Base::get(context, std::move(arguments));
}


} // namespace circt::sim
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::sim::DPIFunctionType)
namespace circt::sim {


} // namespace circt::sim
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::sim::OutputStreamType)
namespace circt::sim {


/// Parse a type registered to this dialect.
::mlir::Type SimDialect::parseType(::mlir::DialectAsmParser &parser) const {
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
void SimDialect::printType(::mlir::Type type,
                    ::mlir::DialectAsmPrinter &printer) const {
  if (::mlir::succeeded(generatedTypePrinter(type, printer)))
    return;
  
}

} // namespace circt::sim

#endif // GET_TYPEDEF_CLASSES

