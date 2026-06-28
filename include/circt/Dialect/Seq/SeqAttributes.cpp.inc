/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* AttrDef Definitions                                                        *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

#ifdef GET_ATTRDEF_LIST
#undef GET_ATTRDEF_LIST

::circt::seq::ClockConstAttr,
::circt::seq::FirMemInitAttr

#endif // GET_ATTRDEF_LIST

#ifdef GET_ATTRDEF_CLASSES
#undef GET_ATTRDEF_CLASSES

static ::mlir::OptionalParseResult generatedAttributeParser(::mlir::AsmParser &parser, ::llvm::StringRef *mnemonic, ::mlir::Type type, ::mlir::Attribute &value) {
  return ::mlir::AsmParser::KeywordSwitch<::mlir::OptionalParseResult>(parser)
    .Case(::circt::seq::ClockConstAttr::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::seq::ClockConstAttr::parse(parser, type);
      return ::mlir::success(!!value);
    })
    .Case(::circt::seq::FirMemInitAttr::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::seq::FirMemInitAttr::parse(parser, type);
      return ::mlir::success(!!value);
    })
    .Default([&](llvm::StringRef keyword, llvm::SMLoc) {
      *mnemonic = keyword;
      return std::nullopt;
    });
}

static ::llvm::LogicalResult generatedAttributePrinter(::mlir::Attribute def, ::mlir::AsmPrinter &printer) {
  return ::llvm::TypeSwitch<::mlir::Attribute, ::llvm::LogicalResult>(def)    .Case<::circt::seq::ClockConstAttr>([&](auto t) {
      printer << ::circt::seq::ClockConstAttr::getMnemonic();
printer << ' ';
t.print(printer);
      return ::mlir::success();
    })
    .Case<::circt::seq::FirMemInitAttr>([&](auto t) {
      printer << ::circt::seq::FirMemInitAttr::getMnemonic();
t.print(printer);
      return ::mlir::success();
    })
    .Default([](auto) { return ::mlir::failure(); });
}

namespace circt::seq {

namespace detail {

struct ClockConstAttrStorage : public ::mlir::AttributeStorage {
  using KeyTy = std::tuple<circt::seq::ClockConst>;
  ClockConstAttrStorage(circt::seq::ClockConst value) : value(std::move(value)) {}

  KeyTy getAsKey() const {
    return KeyTy(value);
  }

  bool operator==(const KeyTy &tblgenKey) const {
    return (value == std::get<0>(tblgenKey));
  }

  static ::llvm::hash_code hashKey(const KeyTy &tblgenKey) {
    return ::llvm::hash_combine(std::get<0>(tblgenKey));
  }

  static ClockConstAttrStorage *construct(::mlir::AttributeStorageAllocator &allocator, KeyTy &&tblgenKey) {
    auto value = std::move(std::get<0>(tblgenKey));
    return new (allocator.allocate<ClockConstAttrStorage>()) ClockConstAttrStorage(std::move(value));
  }

  circt::seq::ClockConst value;
};

} // namespace detail
ClockConstAttr ClockConstAttr::get(::mlir::MLIRContext *context, circt::seq::ClockConst value) {
  return Base::get(context, std::move(value));
}

::mlir::Attribute ClockConstAttr::parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType) {
  ::mlir::Builder odsBuilder(odsParser.getContext());
  ::llvm::SMLoc odsLoc = odsParser.getCurrentLocation();
  (void) odsLoc;
  ::mlir::FailureOr<circt::seq::ClockConst> _result_value;

  // Parse variable 'value'
  _result_value = [&]() -> ::mlir::FailureOr<circt::seq::ClockConst> {
      auto loc = odsParser.getCurrentLocation();
      std::string enumKeyword;
      if (::mlir::failed(odsParser.parseKeywordOrString(&enumKeyword)))
        return ::mlir::failure();
      auto maybeEnum = circt::seq::symbolizeClockConst(enumKeyword);
      if (maybeEnum)
        return *maybeEnum;
      return {(::llvm::LogicalResult)(odsParser.emitError(loc) << "expected " << "circt::seq::ClockConst" << " to be one of: " << "low" << ", " << "high")};
    }();
  if (::mlir::failed(_result_value)) {
    odsParser.emitError(odsParser.getCurrentLocation(), "failed to parse ClockConstAttr parameter 'value' which is to be a `circt::seq::ClockConst`");
    return {};
  }
  assert(::mlir::succeeded(_result_value));
  return ClockConstAttr::get(odsParser.getContext(),
      circt::seq::ClockConst((*_result_value)));
}

void ClockConstAttr::print(::mlir::AsmPrinter &odsPrinter) const {
  ::mlir::Builder odsBuilder(getContext());
  odsPrinter << stringifyClockConst(getValue());
}

circt::seq::ClockConst ClockConstAttr::getValue() const {
  return getImpl()->value;
}


} // namespace circt::seq
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::seq::ClockConstAttr)
namespace circt::seq {

namespace detail {

struct FirMemInitAttrStorage : public ::mlir::AttributeStorage {
  using KeyTy = std::tuple<mlir::StringAttr, bool, bool>;
  FirMemInitAttrStorage(mlir::StringAttr filename, bool isBinary, bool isInline) : filename(std::move(filename)), isBinary(std::move(isBinary)), isInline(std::move(isInline)) {}

  KeyTy getAsKey() const {
    return KeyTy(filename, isBinary, isInline);
  }

  bool operator==(const KeyTy &tblgenKey) const {
    return (filename == std::get<0>(tblgenKey)) && (isBinary == std::get<1>(tblgenKey)) && (isInline == std::get<2>(tblgenKey));
  }

  static ::llvm::hash_code hashKey(const KeyTy &tblgenKey) {
    return ::llvm::hash_combine(std::get<0>(tblgenKey), std::get<1>(tblgenKey), std::get<2>(tblgenKey));
  }

  static FirMemInitAttrStorage *construct(::mlir::AttributeStorageAllocator &allocator, KeyTy &&tblgenKey) {
    auto filename = std::move(std::get<0>(tblgenKey));
    auto isBinary = std::move(std::get<1>(tblgenKey));
    auto isInline = std::move(std::get<2>(tblgenKey));
    return new (allocator.allocate<FirMemInitAttrStorage>()) FirMemInitAttrStorage(std::move(filename), std::move(isBinary), std::move(isInline));
  }

  mlir::StringAttr filename;
  bool isBinary;
  bool isInline;
};

} // namespace detail
FirMemInitAttr FirMemInitAttr::get(::mlir::MLIRContext *context, mlir::StringAttr filename, bool isBinary, bool isInline) {
  return Base::get(context, std::move(filename), std::move(isBinary), std::move(isInline));
}

::mlir::Attribute FirMemInitAttr::parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType) {
  ::mlir::Builder odsBuilder(odsParser.getContext());
  ::llvm::SMLoc odsLoc = odsParser.getCurrentLocation();
  (void) odsLoc;
  ::mlir::FailureOr<mlir::StringAttr> _result_filename;
  ::mlir::FailureOr<bool> _result_isBinary;
  ::mlir::FailureOr<bool> _result_isInline;
  // Parse literal '<'
  if (odsParser.parseLess()) return {};

  // Parse variable 'filename'
  _result_filename = ::mlir::FieldParser<mlir::StringAttr>::parse(odsParser);
  if (::mlir::failed(_result_filename)) {
    odsParser.emitError(odsParser.getCurrentLocation(), "failed to parse FirMemInitAttr parameter 'filename' which is to be a `mlir::StringAttr`");
    return {};
  }
  // Parse literal ','
  if (odsParser.parseComma()) return {};

  // Parse variable 'isBinary'
  _result_isBinary = ::mlir::FieldParser<bool>::parse(odsParser);
  if (::mlir::failed(_result_isBinary)) {
    odsParser.emitError(odsParser.getCurrentLocation(), "failed to parse FirMemInitAttr parameter 'isBinary' which is to be a `bool`");
    return {};
  }
  // Parse literal ','
  if (odsParser.parseComma()) return {};

  // Parse variable 'isInline'
  _result_isInline = ::mlir::FieldParser<bool>::parse(odsParser);
  if (::mlir::failed(_result_isInline)) {
    odsParser.emitError(odsParser.getCurrentLocation(), "failed to parse FirMemInitAttr parameter 'isInline' which is to be a `bool`");
    return {};
  }
  // Parse literal '>'
  if (odsParser.parseGreater()) return {};
  assert(::mlir::succeeded(_result_filename));
  assert(::mlir::succeeded(_result_isBinary));
  assert(::mlir::succeeded(_result_isInline));
  return FirMemInitAttr::get(odsParser.getContext(),
      mlir::StringAttr((*_result_filename)),
      bool((*_result_isBinary)),
      bool((*_result_isInline)));
}

void FirMemInitAttr::print(::mlir::AsmPrinter &odsPrinter) const {
  ::mlir::Builder odsBuilder(getContext());
  odsPrinter << "<";
  odsPrinter.printStrippedAttrOrType(getFilename());
  odsPrinter << ",";
  odsPrinter << ' ';
  odsPrinter.printStrippedAttrOrType(getIsBinary());
  odsPrinter << ",";
  odsPrinter << ' ';
  odsPrinter.printStrippedAttrOrType(getIsInline());
  odsPrinter << ">";
}

mlir::StringAttr FirMemInitAttr::getFilename() const {
  return getImpl()->filename;
}

bool FirMemInitAttr::getIsBinary() const {
  return getImpl()->isBinary;
}

bool FirMemInitAttr::getIsInline() const {
  return getImpl()->isInline;
}


} // namespace circt::seq
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::seq::FirMemInitAttr)
namespace circt::seq {


/// Parse an attribute registered to this dialect.
::mlir::Attribute SeqDialect::parseAttribute(::mlir::DialectAsmParser &parser,
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
void SeqDialect::printAttribute(::mlir::Attribute attr,
                         ::mlir::DialectAsmPrinter &printer) const {
  if (::mlir::succeeded(generatedAttributePrinter(attr, printer)))
    return;
  
}

} // namespace circt::seq

#endif // GET_ATTRDEF_CLASSES

