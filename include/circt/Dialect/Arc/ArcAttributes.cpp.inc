/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* AttrDef Definitions                                                        *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

#ifdef GET_ATTRDEF_LIST
#undef GET_ATTRDEF_LIST

circt::arc::TraceTapAttr

#endif // GET_ATTRDEF_LIST

#ifdef GET_ATTRDEF_CLASSES
#undef GET_ATTRDEF_CLASSES

static ::mlir::OptionalParseResult generatedAttributeParser(::mlir::AsmParser &parser, ::llvm::StringRef *mnemonic, ::mlir::Type type, ::mlir::Attribute &value) {
  return ::mlir::AsmParser::KeywordSwitch<::mlir::OptionalParseResult>(parser)
    .Case(circt::arc::TraceTapAttr::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = circt::arc::TraceTapAttr::parse(parser, type);
      return ::mlir::success(!!value);
    })
    .Default([&](llvm::StringRef keyword, llvm::SMLoc) {
      *mnemonic = keyword;
      return std::nullopt;
    });
}

static ::llvm::LogicalResult generatedAttributePrinter(::mlir::Attribute def, ::mlir::AsmPrinter &printer) {
  return ::llvm::TypeSwitch<::mlir::Attribute, ::llvm::LogicalResult>(def)    .Case<circt::arc::TraceTapAttr>([&](auto t) {
      printer << circt::arc::TraceTapAttr::getMnemonic();
t.print(printer);
      return ::mlir::success();
    })
    .Default([](auto) { return ::mlir::failure(); });
}

namespace circt::arc {

namespace detail {

struct TraceTapAttrStorage : public ::mlir::AttributeStorage {
  using KeyTy = std::tuple<mlir::TypeAttr, uint64_t, mlir::ArrayAttr>;
  TraceTapAttrStorage(mlir::TypeAttr sigType, uint64_t stateOffset, mlir::ArrayAttr names) : sigType(std::move(sigType)), stateOffset(std::move(stateOffset)), names(std::move(names)) {}

  KeyTy getAsKey() const {
    return KeyTy(sigType, stateOffset, names);
  }

  bool operator==(const KeyTy &tblgenKey) const {
    return (sigType == std::get<0>(tblgenKey)) && (stateOffset == std::get<1>(tblgenKey)) && (names == std::get<2>(tblgenKey));
  }

  static ::llvm::hash_code hashKey(const KeyTy &tblgenKey) {
    return ::llvm::hash_combine(std::get<0>(tblgenKey), std::get<1>(tblgenKey), std::get<2>(tblgenKey));
  }

  static TraceTapAttrStorage *construct(::mlir::AttributeStorageAllocator &allocator, KeyTy &&tblgenKey) {
    auto sigType = std::move(std::get<0>(tblgenKey));
    auto stateOffset = std::move(std::get<1>(tblgenKey));
    auto names = std::move(std::get<2>(tblgenKey));
    return new (allocator.allocate<TraceTapAttrStorage>()) TraceTapAttrStorage(std::move(sigType), std::move(stateOffset), std::move(names));
  }

  mlir::TypeAttr sigType;
  uint64_t stateOffset;
  mlir::ArrayAttr names;
};

} // namespace detail
TraceTapAttr TraceTapAttr::get(::mlir::MLIRContext *context, mlir::TypeAttr sigType, uint64_t stateOffset, mlir::ArrayAttr names) {
  return Base::get(context, std::move(sigType), std::move(stateOffset), std::move(names));
}

::mlir::Attribute TraceTapAttr::parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType) {
  ::mlir::Builder odsBuilder(odsParser.getContext());
  ::llvm::SMLoc odsLoc = odsParser.getCurrentLocation();
  (void) odsLoc;
  ::mlir::FailureOr<mlir::TypeAttr> _result_sigType;
  ::mlir::FailureOr<uint64_t> _result_stateOffset;
  ::mlir::FailureOr<mlir::ArrayAttr> _result_names;
  // Parse literal '<'
  if (odsParser.parseLess()) return {};

  // Parse variable 'sigType'
  _result_sigType = ::mlir::FieldParser<mlir::TypeAttr>::parse(odsParser);
  if (::mlir::failed(_result_sigType)) {
    odsParser.emitError(odsParser.getCurrentLocation(), "failed to parse TraceTapAttr parameter 'sigType' which is to be a `mlir::TypeAttr`");
    return {};
  }
  // Parse literal ','
  if (odsParser.parseComma()) return {};

  // Parse variable 'stateOffset'
  _result_stateOffset = ::mlir::FieldParser<uint64_t>::parse(odsParser);
  if (::mlir::failed(_result_stateOffset)) {
    odsParser.emitError(odsParser.getCurrentLocation(), "failed to parse TraceTapAttr parameter 'stateOffset' which is to be a `uint64_t`");
    return {};
  }
  // Parse literal ','
  if (odsParser.parseComma()) return {};

  // Parse variable 'names'
  _result_names = ::mlir::FieldParser<mlir::ArrayAttr>::parse(odsParser);
  if (::mlir::failed(_result_names)) {
    odsParser.emitError(odsParser.getCurrentLocation(), "failed to parse TraceTapAttr parameter 'names' which is to be a `mlir::ArrayAttr`");
    return {};
  }
  // Parse literal '>'
  if (odsParser.parseGreater()) return {};
  assert(::mlir::succeeded(_result_sigType));
  assert(::mlir::succeeded(_result_stateOffset));
  assert(::mlir::succeeded(_result_names));
  return TraceTapAttr::get(odsParser.getContext(),
      mlir::TypeAttr((*_result_sigType)),
      uint64_t((*_result_stateOffset)),
      mlir::ArrayAttr((*_result_names)));
}

void TraceTapAttr::print(::mlir::AsmPrinter &odsPrinter) const {
  ::mlir::Builder odsBuilder(getContext());
  odsPrinter << "<";
  odsPrinter.printStrippedAttrOrType(getSigType());
  odsPrinter << ",";
  odsPrinter << ' ';
  odsPrinter.printStrippedAttrOrType(getStateOffset());
  odsPrinter << ",";
  odsPrinter << ' ';
  odsPrinter.printStrippedAttrOrType(getNames());
  odsPrinter << ">";
}

mlir::TypeAttr TraceTapAttr::getSigType() const {
  return getImpl()->sigType;
}

uint64_t TraceTapAttr::getStateOffset() const {
  return getImpl()->stateOffset;
}

mlir::ArrayAttr TraceTapAttr::getNames() const {
  return getImpl()->names;
}


} // namespace circt::arc
MLIR_DEFINE_EXPLICIT_TYPE_ID(circt::arc::TraceTapAttr)
namespace circt::arc {


/// Parse an attribute registered to this dialect.
::mlir::Attribute ArcDialect::parseAttribute(::mlir::DialectAsmParser &parser,
                                      ::mlir::Type type) const {
  ::llvm::SMLoc typeLoc = parser.getCurrentLocation();
  ::llvm::StringRef attrTag;
  {
    ::mlir::Attribute attr;
    auto parseResult = generatedAttributeParser(parser, &attrTag, type, attr);
    if (parseResult.has_value())
      return attr;
  }
  
  parser.emitError(typeLoc) << "unknown attribute `"
      << attrTag << "` in dialect `" << getNamespace() << "`";
  return {};
}
/// Print an attribute registered to this dialect.
void ArcDialect::printAttribute(::mlir::Attribute attr,
                         ::mlir::DialectAsmPrinter &printer) const {
  if (::mlir::succeeded(generatedAttributePrinter(attr, printer)))
    return;
  
}

} // namespace circt::arc

#endif // GET_ATTRDEF_CLASSES

