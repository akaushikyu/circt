/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* AttrDef Definitions                                                        *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

#ifdef GET_ATTRDEF_LIST
#undef GET_ATTRDEF_LIST

::circt::rtgtest::CPUAttr,
::circt::rtgtest::RegZeroAttr,
::circt::rtgtest::RegRaAttr,
::circt::rtgtest::RegSpAttr,
::circt::rtgtest::RegGpAttr,
::circt::rtgtest::RegTpAttr,
::circt::rtgtest::RegT0Attr,
::circt::rtgtest::RegT1Attr,
::circt::rtgtest::RegT2Attr,
::circt::rtgtest::RegS0Attr,
::circt::rtgtest::RegS1Attr,
::circt::rtgtest::RegA0Attr,
::circt::rtgtest::RegA1Attr,
::circt::rtgtest::RegA2Attr,
::circt::rtgtest::RegA3Attr,
::circt::rtgtest::RegA4Attr,
::circt::rtgtest::RegA5Attr,
::circt::rtgtest::RegA6Attr,
::circt::rtgtest::RegA7Attr,
::circt::rtgtest::RegS2Attr,
::circt::rtgtest::RegS3Attr,
::circt::rtgtest::RegS4Attr,
::circt::rtgtest::RegS5Attr,
::circt::rtgtest::RegS6Attr,
::circt::rtgtest::RegS7Attr,
::circt::rtgtest::RegS8Attr,
::circt::rtgtest::RegS9Attr,
::circt::rtgtest::RegS10Attr,
::circt::rtgtest::RegS11Attr,
::circt::rtgtest::RegT3Attr,
::circt::rtgtest::RegT4Attr,
::circt::rtgtest::RegT5Attr,
::circt::rtgtest::RegT6Attr,
::circt::rtgtest::RegF0Attr

#endif // GET_ATTRDEF_LIST

#ifdef GET_ATTRDEF_CLASSES
#undef GET_ATTRDEF_CLASSES

static ::mlir::OptionalParseResult generatedAttributeParser(::mlir::AsmParser &parser, ::llvm::StringRef *mnemonic, ::mlir::Type type, ::mlir::Attribute &value) {
  return ::mlir::AsmParser::KeywordSwitch<::mlir::OptionalParseResult>(parser)
    .Case(::circt::rtgtest::CPUAttr::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::rtgtest::CPUAttr::parse(parser, type);
      return ::mlir::success(!!value);
    })
    .Case(::circt::rtgtest::RegZeroAttr::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::rtgtest::RegZeroAttr::get(parser.getContext());
      return ::mlir::success(!!value);
    })
    .Case(::circt::rtgtest::RegRaAttr::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::rtgtest::RegRaAttr::get(parser.getContext());
      return ::mlir::success(!!value);
    })
    .Case(::circt::rtgtest::RegSpAttr::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::rtgtest::RegSpAttr::get(parser.getContext());
      return ::mlir::success(!!value);
    })
    .Case(::circt::rtgtest::RegGpAttr::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::rtgtest::RegGpAttr::get(parser.getContext());
      return ::mlir::success(!!value);
    })
    .Case(::circt::rtgtest::RegTpAttr::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::rtgtest::RegTpAttr::get(parser.getContext());
      return ::mlir::success(!!value);
    })
    .Case(::circt::rtgtest::RegT0Attr::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::rtgtest::RegT0Attr::get(parser.getContext());
      return ::mlir::success(!!value);
    })
    .Case(::circt::rtgtest::RegT1Attr::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::rtgtest::RegT1Attr::get(parser.getContext());
      return ::mlir::success(!!value);
    })
    .Case(::circt::rtgtest::RegT2Attr::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::rtgtest::RegT2Attr::get(parser.getContext());
      return ::mlir::success(!!value);
    })
    .Case(::circt::rtgtest::RegS0Attr::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::rtgtest::RegS0Attr::get(parser.getContext());
      return ::mlir::success(!!value);
    })
    .Case(::circt::rtgtest::RegS1Attr::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::rtgtest::RegS1Attr::get(parser.getContext());
      return ::mlir::success(!!value);
    })
    .Case(::circt::rtgtest::RegA0Attr::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::rtgtest::RegA0Attr::get(parser.getContext());
      return ::mlir::success(!!value);
    })
    .Case(::circt::rtgtest::RegA1Attr::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::rtgtest::RegA1Attr::get(parser.getContext());
      return ::mlir::success(!!value);
    })
    .Case(::circt::rtgtest::RegA2Attr::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::rtgtest::RegA2Attr::get(parser.getContext());
      return ::mlir::success(!!value);
    })
    .Case(::circt::rtgtest::RegA3Attr::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::rtgtest::RegA3Attr::get(parser.getContext());
      return ::mlir::success(!!value);
    })
    .Case(::circt::rtgtest::RegA4Attr::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::rtgtest::RegA4Attr::get(parser.getContext());
      return ::mlir::success(!!value);
    })
    .Case(::circt::rtgtest::RegA5Attr::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::rtgtest::RegA5Attr::get(parser.getContext());
      return ::mlir::success(!!value);
    })
    .Case(::circt::rtgtest::RegA6Attr::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::rtgtest::RegA6Attr::get(parser.getContext());
      return ::mlir::success(!!value);
    })
    .Case(::circt::rtgtest::RegA7Attr::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::rtgtest::RegA7Attr::get(parser.getContext());
      return ::mlir::success(!!value);
    })
    .Case(::circt::rtgtest::RegS2Attr::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::rtgtest::RegS2Attr::get(parser.getContext());
      return ::mlir::success(!!value);
    })
    .Case(::circt::rtgtest::RegS3Attr::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::rtgtest::RegS3Attr::get(parser.getContext());
      return ::mlir::success(!!value);
    })
    .Case(::circt::rtgtest::RegS4Attr::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::rtgtest::RegS4Attr::get(parser.getContext());
      return ::mlir::success(!!value);
    })
    .Case(::circt::rtgtest::RegS5Attr::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::rtgtest::RegS5Attr::get(parser.getContext());
      return ::mlir::success(!!value);
    })
    .Case(::circt::rtgtest::RegS6Attr::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::rtgtest::RegS6Attr::get(parser.getContext());
      return ::mlir::success(!!value);
    })
    .Case(::circt::rtgtest::RegS7Attr::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::rtgtest::RegS7Attr::get(parser.getContext());
      return ::mlir::success(!!value);
    })
    .Case(::circt::rtgtest::RegS8Attr::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::rtgtest::RegS8Attr::get(parser.getContext());
      return ::mlir::success(!!value);
    })
    .Case(::circt::rtgtest::RegS9Attr::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::rtgtest::RegS9Attr::get(parser.getContext());
      return ::mlir::success(!!value);
    })
    .Case(::circt::rtgtest::RegS10Attr::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::rtgtest::RegS10Attr::get(parser.getContext());
      return ::mlir::success(!!value);
    })
    .Case(::circt::rtgtest::RegS11Attr::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::rtgtest::RegS11Attr::get(parser.getContext());
      return ::mlir::success(!!value);
    })
    .Case(::circt::rtgtest::RegT3Attr::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::rtgtest::RegT3Attr::get(parser.getContext());
      return ::mlir::success(!!value);
    })
    .Case(::circt::rtgtest::RegT4Attr::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::rtgtest::RegT4Attr::get(parser.getContext());
      return ::mlir::success(!!value);
    })
    .Case(::circt::rtgtest::RegT5Attr::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::rtgtest::RegT5Attr::get(parser.getContext());
      return ::mlir::success(!!value);
    })
    .Case(::circt::rtgtest::RegT6Attr::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::rtgtest::RegT6Attr::get(parser.getContext());
      return ::mlir::success(!!value);
    })
    .Case(::circt::rtgtest::RegF0Attr::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::rtgtest::RegF0Attr::get(parser.getContext());
      return ::mlir::success(!!value);
    })
    .Default([&](llvm::StringRef keyword, llvm::SMLoc) {
      *mnemonic = keyword;
      return std::nullopt;
    });
}

static ::llvm::LogicalResult generatedAttributePrinter(::mlir::Attribute def, ::mlir::AsmPrinter &printer) {
  return ::llvm::TypeSwitch<::mlir::Attribute, ::llvm::LogicalResult>(def)    .Case<::circt::rtgtest::CPUAttr>([&](auto t) {
      printer << ::circt::rtgtest::CPUAttr::getMnemonic();
t.print(printer);
      return ::mlir::success();
    })
    .Case<::circt::rtgtest::RegZeroAttr>([&](auto t) {
      printer << ::circt::rtgtest::RegZeroAttr::getMnemonic();
      return ::mlir::success();
    })
    .Case<::circt::rtgtest::RegRaAttr>([&](auto t) {
      printer << ::circt::rtgtest::RegRaAttr::getMnemonic();
      return ::mlir::success();
    })
    .Case<::circt::rtgtest::RegSpAttr>([&](auto t) {
      printer << ::circt::rtgtest::RegSpAttr::getMnemonic();
      return ::mlir::success();
    })
    .Case<::circt::rtgtest::RegGpAttr>([&](auto t) {
      printer << ::circt::rtgtest::RegGpAttr::getMnemonic();
      return ::mlir::success();
    })
    .Case<::circt::rtgtest::RegTpAttr>([&](auto t) {
      printer << ::circt::rtgtest::RegTpAttr::getMnemonic();
      return ::mlir::success();
    })
    .Case<::circt::rtgtest::RegT0Attr>([&](auto t) {
      printer << ::circt::rtgtest::RegT0Attr::getMnemonic();
      return ::mlir::success();
    })
    .Case<::circt::rtgtest::RegT1Attr>([&](auto t) {
      printer << ::circt::rtgtest::RegT1Attr::getMnemonic();
      return ::mlir::success();
    })
    .Case<::circt::rtgtest::RegT2Attr>([&](auto t) {
      printer << ::circt::rtgtest::RegT2Attr::getMnemonic();
      return ::mlir::success();
    })
    .Case<::circt::rtgtest::RegS0Attr>([&](auto t) {
      printer << ::circt::rtgtest::RegS0Attr::getMnemonic();
      return ::mlir::success();
    })
    .Case<::circt::rtgtest::RegS1Attr>([&](auto t) {
      printer << ::circt::rtgtest::RegS1Attr::getMnemonic();
      return ::mlir::success();
    })
    .Case<::circt::rtgtest::RegA0Attr>([&](auto t) {
      printer << ::circt::rtgtest::RegA0Attr::getMnemonic();
      return ::mlir::success();
    })
    .Case<::circt::rtgtest::RegA1Attr>([&](auto t) {
      printer << ::circt::rtgtest::RegA1Attr::getMnemonic();
      return ::mlir::success();
    })
    .Case<::circt::rtgtest::RegA2Attr>([&](auto t) {
      printer << ::circt::rtgtest::RegA2Attr::getMnemonic();
      return ::mlir::success();
    })
    .Case<::circt::rtgtest::RegA3Attr>([&](auto t) {
      printer << ::circt::rtgtest::RegA3Attr::getMnemonic();
      return ::mlir::success();
    })
    .Case<::circt::rtgtest::RegA4Attr>([&](auto t) {
      printer << ::circt::rtgtest::RegA4Attr::getMnemonic();
      return ::mlir::success();
    })
    .Case<::circt::rtgtest::RegA5Attr>([&](auto t) {
      printer << ::circt::rtgtest::RegA5Attr::getMnemonic();
      return ::mlir::success();
    })
    .Case<::circt::rtgtest::RegA6Attr>([&](auto t) {
      printer << ::circt::rtgtest::RegA6Attr::getMnemonic();
      return ::mlir::success();
    })
    .Case<::circt::rtgtest::RegA7Attr>([&](auto t) {
      printer << ::circt::rtgtest::RegA7Attr::getMnemonic();
      return ::mlir::success();
    })
    .Case<::circt::rtgtest::RegS2Attr>([&](auto t) {
      printer << ::circt::rtgtest::RegS2Attr::getMnemonic();
      return ::mlir::success();
    })
    .Case<::circt::rtgtest::RegS3Attr>([&](auto t) {
      printer << ::circt::rtgtest::RegS3Attr::getMnemonic();
      return ::mlir::success();
    })
    .Case<::circt::rtgtest::RegS4Attr>([&](auto t) {
      printer << ::circt::rtgtest::RegS4Attr::getMnemonic();
      return ::mlir::success();
    })
    .Case<::circt::rtgtest::RegS5Attr>([&](auto t) {
      printer << ::circt::rtgtest::RegS5Attr::getMnemonic();
      return ::mlir::success();
    })
    .Case<::circt::rtgtest::RegS6Attr>([&](auto t) {
      printer << ::circt::rtgtest::RegS6Attr::getMnemonic();
      return ::mlir::success();
    })
    .Case<::circt::rtgtest::RegS7Attr>([&](auto t) {
      printer << ::circt::rtgtest::RegS7Attr::getMnemonic();
      return ::mlir::success();
    })
    .Case<::circt::rtgtest::RegS8Attr>([&](auto t) {
      printer << ::circt::rtgtest::RegS8Attr::getMnemonic();
      return ::mlir::success();
    })
    .Case<::circt::rtgtest::RegS9Attr>([&](auto t) {
      printer << ::circt::rtgtest::RegS9Attr::getMnemonic();
      return ::mlir::success();
    })
    .Case<::circt::rtgtest::RegS10Attr>([&](auto t) {
      printer << ::circt::rtgtest::RegS10Attr::getMnemonic();
      return ::mlir::success();
    })
    .Case<::circt::rtgtest::RegS11Attr>([&](auto t) {
      printer << ::circt::rtgtest::RegS11Attr::getMnemonic();
      return ::mlir::success();
    })
    .Case<::circt::rtgtest::RegT3Attr>([&](auto t) {
      printer << ::circt::rtgtest::RegT3Attr::getMnemonic();
      return ::mlir::success();
    })
    .Case<::circt::rtgtest::RegT4Attr>([&](auto t) {
      printer << ::circt::rtgtest::RegT4Attr::getMnemonic();
      return ::mlir::success();
    })
    .Case<::circt::rtgtest::RegT5Attr>([&](auto t) {
      printer << ::circt::rtgtest::RegT5Attr::getMnemonic();
      return ::mlir::success();
    })
    .Case<::circt::rtgtest::RegT6Attr>([&](auto t) {
      printer << ::circt::rtgtest::RegT6Attr::getMnemonic();
      return ::mlir::success();
    })
    .Case<::circt::rtgtest::RegF0Attr>([&](auto t) {
      printer << ::circt::rtgtest::RegF0Attr::getMnemonic();
      return ::mlir::success();
    })
    .Default([](auto) { return ::mlir::failure(); });
}

namespace circt::rtgtest {

namespace detail {

struct CPUAttrStorage : public ::mlir::AttributeStorage {
  using KeyTy = std::tuple<size_t>;
  CPUAttrStorage(size_t id) : id(std::move(id)) {}

  KeyTy getAsKey() const {
    return KeyTy(id);
  }

  bool operator==(const KeyTy &tblgenKey) const {
    return (id == std::get<0>(tblgenKey));
  }

  static ::llvm::hash_code hashKey(const KeyTy &tblgenKey) {
    return ::llvm::hash_combine(std::get<0>(tblgenKey));
  }

  static CPUAttrStorage *construct(::mlir::AttributeStorageAllocator &allocator, KeyTy &&tblgenKey) {
    auto id = std::move(std::get<0>(tblgenKey));
    return new (allocator.allocate<CPUAttrStorage>()) CPUAttrStorage(std::move(id));
  }

  size_t id;
};

} // namespace detail
CPUAttr CPUAttr::get(::mlir::MLIRContext *context, size_t id) {
  return Base::get(context, std::move(id));
}

::mlir::Attribute CPUAttr::parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType) {
  ::mlir::Builder odsBuilder(odsParser.getContext());
  ::llvm::SMLoc odsLoc = odsParser.getCurrentLocation();
  (void) odsLoc;
  ::mlir::FailureOr<size_t> _result_id;
  // Parse literal '<'
  if (odsParser.parseLess()) return {};

  // Parse variable 'id'
  _result_id = ::mlir::FieldParser<size_t>::parse(odsParser);
  if (::mlir::failed(_result_id)) {
    odsParser.emitError(odsParser.getCurrentLocation(), "failed to parse CPUAttr parameter 'id' which is to be a `size_t`");
    return {};
  }
  // Parse literal '>'
  if (odsParser.parseGreater()) return {};
  assert(::mlir::succeeded(_result_id));
  return CPUAttr::get(odsParser.getContext(),
      size_t((*_result_id)));
}

void CPUAttr::print(::mlir::AsmPrinter &odsPrinter) const {
  ::mlir::Builder odsBuilder(getContext());
  odsPrinter << "<";
  odsPrinter.printStrippedAttrOrType(getId());
  odsPrinter << ">";
}

size_t CPUAttr::getId() const {
  return getImpl()->id;
}


} // namespace circt::rtgtest
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::rtgtest::CPUAttr)
namespace circt::rtgtest {


} // namespace circt::rtgtest
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::rtgtest::RegZeroAttr)
namespace circt::rtgtest {


} // namespace circt::rtgtest
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::rtgtest::RegRaAttr)
namespace circt::rtgtest {


} // namespace circt::rtgtest
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::rtgtest::RegSpAttr)
namespace circt::rtgtest {


} // namespace circt::rtgtest
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::rtgtest::RegGpAttr)
namespace circt::rtgtest {


} // namespace circt::rtgtest
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::rtgtest::RegTpAttr)
namespace circt::rtgtest {


} // namespace circt::rtgtest
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::rtgtest::RegT0Attr)
namespace circt::rtgtest {


} // namespace circt::rtgtest
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::rtgtest::RegT1Attr)
namespace circt::rtgtest {


} // namespace circt::rtgtest
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::rtgtest::RegT2Attr)
namespace circt::rtgtest {


} // namespace circt::rtgtest
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::rtgtest::RegS0Attr)
namespace circt::rtgtest {


} // namespace circt::rtgtest
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::rtgtest::RegS1Attr)
namespace circt::rtgtest {


} // namespace circt::rtgtest
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::rtgtest::RegA0Attr)
namespace circt::rtgtest {


} // namespace circt::rtgtest
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::rtgtest::RegA1Attr)
namespace circt::rtgtest {


} // namespace circt::rtgtest
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::rtgtest::RegA2Attr)
namespace circt::rtgtest {


} // namespace circt::rtgtest
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::rtgtest::RegA3Attr)
namespace circt::rtgtest {


} // namespace circt::rtgtest
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::rtgtest::RegA4Attr)
namespace circt::rtgtest {


} // namespace circt::rtgtest
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::rtgtest::RegA5Attr)
namespace circt::rtgtest {


} // namespace circt::rtgtest
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::rtgtest::RegA6Attr)
namespace circt::rtgtest {


} // namespace circt::rtgtest
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::rtgtest::RegA7Attr)
namespace circt::rtgtest {


} // namespace circt::rtgtest
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::rtgtest::RegS2Attr)
namespace circt::rtgtest {


} // namespace circt::rtgtest
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::rtgtest::RegS3Attr)
namespace circt::rtgtest {


} // namespace circt::rtgtest
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::rtgtest::RegS4Attr)
namespace circt::rtgtest {


} // namespace circt::rtgtest
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::rtgtest::RegS5Attr)
namespace circt::rtgtest {


} // namespace circt::rtgtest
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::rtgtest::RegS6Attr)
namespace circt::rtgtest {


} // namespace circt::rtgtest
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::rtgtest::RegS7Attr)
namespace circt::rtgtest {


} // namespace circt::rtgtest
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::rtgtest::RegS8Attr)
namespace circt::rtgtest {


} // namespace circt::rtgtest
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::rtgtest::RegS9Attr)
namespace circt::rtgtest {


} // namespace circt::rtgtest
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::rtgtest::RegS10Attr)
namespace circt::rtgtest {


} // namespace circt::rtgtest
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::rtgtest::RegS11Attr)
namespace circt::rtgtest {


} // namespace circt::rtgtest
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::rtgtest::RegT3Attr)
namespace circt::rtgtest {


} // namespace circt::rtgtest
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::rtgtest::RegT4Attr)
namespace circt::rtgtest {


} // namespace circt::rtgtest
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::rtgtest::RegT5Attr)
namespace circt::rtgtest {


} // namespace circt::rtgtest
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::rtgtest::RegT6Attr)
namespace circt::rtgtest {


} // namespace circt::rtgtest
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::rtgtest::RegF0Attr)
namespace circt::rtgtest {


/// Parse an attribute registered to this dialect.
::mlir::Attribute RTGTestDialect::parseAttribute(::mlir::DialectAsmParser &parser,
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
void RTGTestDialect::printAttribute(::mlir::Attribute attr,
                         ::mlir::DialectAsmPrinter &printer) const {
  if (::mlir::succeeded(generatedAttributePrinter(attr, printer)))
    return;
  
}

} // namespace circt::rtgtest

#endif // GET_ATTRDEF_CLASSES

