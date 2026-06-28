/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* AttrDef Definitions                                                        *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

#ifdef GET_ATTRDEF_LIST
#undef GET_ATTRDEF_LIST

::circt::handshake::BufferTypeEnumAttr

#endif // GET_ATTRDEF_LIST

#ifdef GET_ATTRDEF_CLASSES
#undef GET_ATTRDEF_CLASSES

static ::mlir::OptionalParseResult generatedAttributeParser(::mlir::AsmParser &parser, ::llvm::StringRef *mnemonic, ::mlir::Type type, ::mlir::Attribute &value) {
  return ::mlir::AsmParser::KeywordSwitch<::mlir::OptionalParseResult>(parser)
    .Case(::circt::handshake::BufferTypeEnumAttr::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::handshake::BufferTypeEnumAttr::parse(parser, type);
      return ::mlir::success(!!value);
    })
    .Default([&](llvm::StringRef keyword, llvm::SMLoc) {
      *mnemonic = keyword;
      return std::nullopt;
    });
}

static ::llvm::LogicalResult generatedAttributePrinter(::mlir::Attribute def, ::mlir::AsmPrinter &printer) {
  return ::llvm::TypeSwitch<::mlir::Attribute, ::llvm::LogicalResult>(def)    .Case<::circt::handshake::BufferTypeEnumAttr>([&](auto t) {
      printer << ::circt::handshake::BufferTypeEnumAttr::getMnemonic();
printer << ' ';
t.print(printer);
      return ::mlir::success();
    })
    .Default([](auto) { return ::mlir::failure(); });
}

namespace circt::handshake {

namespace detail {

struct BufferTypeEnumAttrStorage : public ::mlir::AttributeStorage {
  using KeyTy = std::tuple<::BufferTypeEnum>;
  BufferTypeEnumAttrStorage(::BufferTypeEnum value) : value(std::move(value)) {}

  KeyTy getAsKey() const {
    return KeyTy(value);
  }

  bool operator==(const KeyTy &tblgenKey) const {
    return (value == std::get<0>(tblgenKey));
  }

  static ::llvm::hash_code hashKey(const KeyTy &tblgenKey) {
    return ::llvm::hash_combine(std::get<0>(tblgenKey));
  }

  static BufferTypeEnumAttrStorage *construct(::mlir::AttributeStorageAllocator &allocator, KeyTy &&tblgenKey) {
    auto value = std::move(std::get<0>(tblgenKey));
    return new (allocator.allocate<BufferTypeEnumAttrStorage>()) BufferTypeEnumAttrStorage(std::move(value));
  }

  ::BufferTypeEnum value;
};

} // namespace detail
BufferTypeEnumAttr BufferTypeEnumAttr::get(::mlir::MLIRContext *context, ::BufferTypeEnum value) {
  return Base::get(context, std::move(value));
}

::mlir::Attribute BufferTypeEnumAttr::parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType) {
  ::mlir::Builder odsBuilder(odsParser.getContext());
  ::llvm::SMLoc odsLoc = odsParser.getCurrentLocation();
  (void) odsLoc;
  ::mlir::FailureOr<::BufferTypeEnum> _result_value;

  // Parse variable 'value'
  _result_value = [&]() -> ::mlir::FailureOr<::BufferTypeEnum> {
      auto loc = odsParser.getCurrentLocation();
      std::string enumKeyword;
      if (::mlir::failed(odsParser.parseKeywordOrString(&enumKeyword)))
        return ::mlir::failure();
      auto maybeEnum = ::symbolizeBufferTypeEnum(enumKeyword);
      if (maybeEnum)
        return *maybeEnum;
      return {(::llvm::LogicalResult)(odsParser.emitError(loc) << "expected " << "::BufferTypeEnum" << " to be one of: " << "seq" << ", " << "fifo")};
    }();
  if (::mlir::failed(_result_value)) {
    odsParser.emitError(odsParser.getCurrentLocation(), "failed to parse BufferTypeEnumAttr parameter 'value' which is to be a `::BufferTypeEnum`");
    return {};
  }
  assert(::mlir::succeeded(_result_value));
  return BufferTypeEnumAttr::get(odsParser.getContext(),
      ::BufferTypeEnum((*_result_value)));
}

void BufferTypeEnumAttr::print(::mlir::AsmPrinter &odsPrinter) const {
  ::mlir::Builder odsBuilder(getContext());
  odsPrinter << stringifyBufferTypeEnum(getValue());
}

::BufferTypeEnum BufferTypeEnumAttr::getValue() const {
  return getImpl()->value;
}


} // namespace circt::handshake
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::handshake::BufferTypeEnumAttr)
namespace circt::handshake {


/// Parse an attribute registered to this dialect.
::mlir::Attribute HandshakeDialect::parseAttribute(::mlir::DialectAsmParser &parser,
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
void HandshakeDialect::printAttribute(::mlir::Attribute attr,
                         ::mlir::DialectAsmPrinter &printer) const {
  if (::mlir::succeeded(generatedAttributePrinter(attr, printer)))
    return;
  
}

} // namespace circt::handshake

#endif // GET_ATTRDEF_CLASSES

