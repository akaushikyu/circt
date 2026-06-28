/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* AttrDef Definitions                                                        *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

#ifdef GET_ATTRDEF_LIST
#undef GET_ATTRDEF_LIST

::circt::kanagawa::PathStepAttr

#endif // GET_ATTRDEF_LIST

#ifdef GET_ATTRDEF_CLASSES
#undef GET_ATTRDEF_CLASSES

static ::mlir::OptionalParseResult generatedAttributeParser(::mlir::AsmParser &parser, ::llvm::StringRef *mnemonic, ::mlir::Type type, ::mlir::Attribute &value) {
  return ::mlir::AsmParser::KeywordSwitch<::mlir::OptionalParseResult>(parser)
    .Case(::circt::kanagawa::PathStepAttr::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::kanagawa::PathStepAttr::parse(parser, type);
      return ::mlir::success(!!value);
    })
    .Default([&](llvm::StringRef keyword, llvm::SMLoc) {
      *mnemonic = keyword;
      return std::nullopt;
    });
}

static ::llvm::LogicalResult generatedAttributePrinter(::mlir::Attribute def, ::mlir::AsmPrinter &printer) {
  return ::llvm::TypeSwitch<::mlir::Attribute, ::llvm::LogicalResult>(def)    .Case<::circt::kanagawa::PathStepAttr>([&](auto t) {
      printer << ::circt::kanagawa::PathStepAttr::getMnemonic();
t.print(printer);
      return ::mlir::success();
    })
    .Default([](auto) { return ::mlir::failure(); });
}

namespace circt::kanagawa {

namespace detail {

struct PathStepAttrStorage : public ::mlir::AttributeStorage {
  using KeyTy = std::tuple<PathDirection, ::mlir::Type, mlir::FlatSymbolRefAttr>;
  PathStepAttrStorage(PathDirection direction, ::mlir::Type type, mlir::FlatSymbolRefAttr child) : direction(std::move(direction)), type(std::move(type)), child(std::move(child)) {}

  KeyTy getAsKey() const {
    return KeyTy(direction, type, child);
  }

  bool operator==(const KeyTy &tblgenKey) const {
    return (direction == std::get<0>(tblgenKey)) && (type == std::get<1>(tblgenKey)) && (child == std::get<2>(tblgenKey));
  }

  static ::llvm::hash_code hashKey(const KeyTy &tblgenKey) {
    return ::llvm::hash_combine(std::get<0>(tblgenKey), std::get<1>(tblgenKey), std::get<2>(tblgenKey));
  }

  static PathStepAttrStorage *construct(::mlir::AttributeStorageAllocator &allocator, KeyTy &&tblgenKey) {
    auto direction = std::move(std::get<0>(tblgenKey));
    auto type = std::move(std::get<1>(tblgenKey));
    auto child = std::move(std::get<2>(tblgenKey));
    return new (allocator.allocate<PathStepAttrStorage>()) PathStepAttrStorage(std::move(direction), std::move(type), std::move(child));
  }

  PathDirection direction;
  ::mlir::Type type;
  mlir::FlatSymbolRefAttr child;
};

} // namespace detail
PathStepAttr PathStepAttr::get(::mlir::MLIRContext *context, PathDirection direction, ::mlir::Type type, mlir::FlatSymbolRefAttr child) {
  return Base::get(context, std::move(direction), std::move(type), std::move(child));
}

PathStepAttr PathStepAttr::getChecked(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::mlir::MLIRContext *context, PathDirection direction, ::mlir::Type type, mlir::FlatSymbolRefAttr child) {
  return Base::getChecked(emitError, context, std::move(direction), std::move(type), std::move(child));
}

::llvm::LogicalResult PathStepAttr::verifyInvariants(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, PathDirection direction, ::mlir::Type type, mlir::FlatSymbolRefAttr child) {
  if (::mlir::failed(verify(emitError, direction, type, child)))
    return ::mlir::failure();
  return ::mlir::success();
}

::mlir::Attribute PathStepAttr::parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType) {
  ::mlir::Builder odsBuilder(odsParser.getContext());
  ::llvm::SMLoc odsLoc = odsParser.getCurrentLocation();
  (void) odsLoc;
  ::mlir::FailureOr<PathDirection> _result_direction;
  ::mlir::FailureOr<::mlir::Type> _result_type;

  if (odsType) {
    if (auto reqType = ::llvm::dyn_cast<::mlir::Type>(odsType)) {
      _result_type = reqType;
    } else {
      odsParser.emitError(odsLoc, "invalid kind of type specified");
      return {};
    }
  }
  ::mlir::FailureOr<mlir::FlatSymbolRefAttr> _result_child;
  // Parse literal '<'
  if (odsParser.parseLess()) return {};

  // Parse variable 'direction'
  _result_direction = ::mlir::FieldParser<PathDirection>::parse(odsParser);
  if (::mlir::failed(_result_direction)) {
    odsParser.emitError(odsParser.getCurrentLocation(), "failed to parse PathStepAttr parameter 'direction' which is to be a `PathDirection`");
    return {};
  }
  // Parse literal ','
  if (odsParser.parseOptionalComma()) {
  } else {

    // Parse variable 'child'
    _result_child = ::mlir::FieldParser<mlir::FlatSymbolRefAttr>::parse(odsParser);
    if (::mlir::failed(_result_child)) {
      odsParser.emitError(odsParser.getCurrentLocation(), "failed to parse PathStepAttr parameter 'child' which is to be a `mlir::FlatSymbolRefAttr`");
      return {};
    }
  }
  // Parse literal ':'
  if (odsParser.parseColon()) return {};

  // Parse variable 'type'
  _result_type = ::mlir::FieldParser<::mlir::Type>::parse(odsParser);
  if (::mlir::failed(_result_type)) {
    odsParser.emitError(odsParser.getCurrentLocation(), "failed to parse PathStepAttr parameter 'type' which is to be a `::mlir::Type`");
    return {};
  }
  // Parse literal '>'
  if (odsParser.parseGreater()) return {};
  assert(::mlir::succeeded(_result_direction));
  return odsParser.getChecked<PathStepAttr>(odsLoc, odsParser.getContext(),
      PathDirection((*_result_direction)),
      ::mlir::Type((_result_type.value_or(::mlir::NoneType::get(odsParser.getContext())))),
      mlir::FlatSymbolRefAttr((_result_child.value_or(mlir::FlatSymbolRefAttr()))));
}

void PathStepAttr::print(::mlir::AsmPrinter &odsPrinter) const {
  ::mlir::Builder odsBuilder(getContext());
  odsPrinter << "<";
  odsPrinter.printStrippedAttrOrType(getDirection());
  if (!(getChild() == mlir::FlatSymbolRefAttr())) {
    odsPrinter << ",";
    if (!(getChild() == mlir::FlatSymbolRefAttr())) {
      odsPrinter << ' ';
      odsPrinter.printStrippedAttrOrType(getChild());
    }
  } else {
  }
  odsPrinter << ' ' << ":";
  if (!(getType() == ::mlir::NoneType::get(getContext()))) {
    odsPrinter << ' ';
    odsPrinter.printStrippedAttrOrType(getType());
  }
  odsPrinter << ">";
}

PathDirection PathStepAttr::getDirection() const {
  return getImpl()->direction;
}

::mlir::Type PathStepAttr::getType() const {
  return getImpl()->type;
}

mlir::FlatSymbolRefAttr PathStepAttr::getChild() const {
  return getImpl()->child;
}


} // namespace circt::kanagawa
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::kanagawa::PathStepAttr)
namespace circt::kanagawa {


/// Parse an attribute registered to this dialect.
::mlir::Attribute KanagawaDialect::parseAttribute(::mlir::DialectAsmParser &parser,
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
void KanagawaDialect::printAttribute(::mlir::Attribute attr,
                         ::mlir::DialectAsmPrinter &printer) const {
  if (::mlir::succeeded(generatedAttributePrinter(attr, printer)))
    return;
  
}

} // namespace circt::kanagawa

#endif // GET_ATTRDEF_CLASSES

