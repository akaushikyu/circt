/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* AttrDef Definitions                                                        *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

#ifdef GET_ATTRDEF_LIST
#undef GET_ATTRDEF_LIST

::circt::om::ReferenceAttr,
::circt::om::SymbolRefAttr,
::circt::om::ListAttr,
::circt::om::PathAttr,
::circt::om::IntegerAttr

#endif // GET_ATTRDEF_LIST

#ifdef GET_ATTRDEF_CLASSES
#undef GET_ATTRDEF_CLASSES

static ::mlir::OptionalParseResult generatedAttributeParser(::mlir::AsmParser &parser, ::llvm::StringRef *mnemonic, ::mlir::Type type, ::mlir::Attribute &value) {
  return ::mlir::AsmParser::KeywordSwitch<::mlir::OptionalParseResult>(parser)
    .Case(::circt::om::ReferenceAttr::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::om::ReferenceAttr::parse(parser, type);
      return ::mlir::success(!!value);
    })
    .Case(::circt::om::SymbolRefAttr::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::om::SymbolRefAttr::parse(parser, type);
      return ::mlir::success(!!value);
    })
    .Case(::circt::om::ListAttr::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::om::ListAttr::parse(parser, type);
      return ::mlir::success(!!value);
    })
    .Case(::circt::om::PathAttr::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::om::PathAttr::parse(parser, type);
      return ::mlir::success(!!value);
    })
    .Case(::circt::om::IntegerAttr::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::om::IntegerAttr::parse(parser, type);
      return ::mlir::success(!!value);
    })
    .Default([&](llvm::StringRef keyword, llvm::SMLoc) {
      *mnemonic = keyword;
      return std::nullopt;
    });
}

static ::llvm::LogicalResult generatedAttributePrinter(::mlir::Attribute def, ::mlir::AsmPrinter &printer) {
  return ::llvm::TypeSwitch<::mlir::Attribute, ::llvm::LogicalResult>(def)    .Case<::circt::om::ReferenceAttr>([&](auto t) {
      printer << ::circt::om::ReferenceAttr::getMnemonic();
t.print(printer);
      return ::mlir::success();
    })
    .Case<::circt::om::SymbolRefAttr>([&](auto t) {
      printer << ::circt::om::SymbolRefAttr::getMnemonic();
t.print(printer);
      return ::mlir::success();
    })
    .Case<::circt::om::ListAttr>([&](auto t) {
      printer << ::circt::om::ListAttr::getMnemonic();
t.print(printer);
      return ::mlir::success();
    })
    .Case<::circt::om::PathAttr>([&](auto t) {
      printer << ::circt::om::PathAttr::getMnemonic();
t.print(printer);
      return ::mlir::success();
    })
    .Case<::circt::om::IntegerAttr>([&](auto t) {
      printer << ::circt::om::IntegerAttr::getMnemonic();
t.print(printer);
      return ::mlir::success();
    })
    .Default([](auto) { return ::mlir::failure(); });
}

namespace circt::om {

namespace detail {

struct ReferenceAttrStorage : public ::mlir::AttributeStorage {
  using KeyTy = std::tuple<circt::hw::InnerRefAttr>;
  ReferenceAttrStorage(circt::hw::InnerRefAttr innerRef) : innerRef(std::move(innerRef)) {}

  KeyTy getAsKey() const {
    return KeyTy(innerRef);
  }

  bool operator==(const KeyTy &tblgenKey) const {
    return (innerRef == std::get<0>(tblgenKey));
  }

  static ::llvm::hash_code hashKey(const KeyTy &tblgenKey) {
    return ::llvm::hash_combine(std::get<0>(tblgenKey));
  }

  static ReferenceAttrStorage *construct(::mlir::AttributeStorageAllocator &allocator, KeyTy &&tblgenKey) {
    auto innerRef = std::move(std::get<0>(tblgenKey));
    return new (allocator.allocate<ReferenceAttrStorage>()) ReferenceAttrStorage(std::move(innerRef));
  }

  circt::hw::InnerRefAttr innerRef;
};

} // namespace detail
ReferenceAttr ReferenceAttr::get(::mlir::MLIRContext *context, circt::hw::InnerRefAttr innerRef) {
  return Base::get(context, std::move(innerRef));
}

::mlir::Attribute ReferenceAttr::parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType) {
  ::mlir::Builder odsBuilder(odsParser.getContext());
  ::llvm::SMLoc odsLoc = odsParser.getCurrentLocation();
  (void) odsLoc;
  ::mlir::FailureOr<circt::hw::InnerRefAttr> _result_innerRef;
  // Parse literal '<'
  if (odsParser.parseLess()) return {};

  // Parse variable 'innerRef'
  _result_innerRef = ::mlir::FieldParser<circt::hw::InnerRefAttr>::parse(odsParser);
  if (::mlir::failed(_result_innerRef)) {
    odsParser.emitError(odsParser.getCurrentLocation(), "failed to parse ReferenceAttr parameter 'innerRef' which is to be a `circt::hw::InnerRefAttr`");
    return {};
  }
  // Parse literal '>'
  if (odsParser.parseGreater()) return {};
  assert(::mlir::succeeded(_result_innerRef));
  return ReferenceAttr::get(odsParser.getContext(),
      circt::hw::InnerRefAttr((*_result_innerRef)));
}

void ReferenceAttr::print(::mlir::AsmPrinter &odsPrinter) const {
  ::mlir::Builder odsBuilder(getContext());
  odsPrinter << "<";
  odsPrinter.printStrippedAttrOrType(getInnerRef());
  odsPrinter << ">";
}

circt::hw::InnerRefAttr ReferenceAttr::getInnerRef() const {
  return getImpl()->innerRef;
}


} // namespace circt::om
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::om::ReferenceAttr)
namespace circt::om {

namespace detail {

struct SymbolRefAttrStorage : public ::mlir::AttributeStorage {
  using KeyTy = std::tuple<mlir::FlatSymbolRefAttr>;
  SymbolRefAttrStorage(mlir::FlatSymbolRefAttr ref) : ref(std::move(ref)) {}

  KeyTy getAsKey() const {
    return KeyTy(ref);
  }

  bool operator==(const KeyTy &tblgenKey) const {
    return (ref == std::get<0>(tblgenKey));
  }

  static ::llvm::hash_code hashKey(const KeyTy &tblgenKey) {
    return ::llvm::hash_combine(std::get<0>(tblgenKey));
  }

  static SymbolRefAttrStorage *construct(::mlir::AttributeStorageAllocator &allocator, KeyTy &&tblgenKey) {
    auto ref = std::move(std::get<0>(tblgenKey));
    return new (allocator.allocate<SymbolRefAttrStorage>()) SymbolRefAttrStorage(std::move(ref));
  }

  mlir::FlatSymbolRefAttr ref;
};

} // namespace detail
SymbolRefAttr SymbolRefAttr::get(::mlir::MLIRContext *context, mlir::FlatSymbolRefAttr ref) {
  return Base::get(context, std::move(ref));
}

::mlir::Attribute SymbolRefAttr::parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType) {
  ::mlir::Builder odsBuilder(odsParser.getContext());
  ::llvm::SMLoc odsLoc = odsParser.getCurrentLocation();
  (void) odsLoc;
  ::mlir::FailureOr<mlir::FlatSymbolRefAttr> _result_ref;
  // Parse literal '<'
  if (odsParser.parseLess()) return {};

  // Parse variable 'ref'
  _result_ref = ::mlir::FieldParser<mlir::FlatSymbolRefAttr>::parse(odsParser);
  if (::mlir::failed(_result_ref)) {
    odsParser.emitError(odsParser.getCurrentLocation(), "failed to parse OMSymbolRefAttr parameter 'ref' which is to be a `mlir::FlatSymbolRefAttr`");
    return {};
  }
  // Parse literal '>'
  if (odsParser.parseGreater()) return {};
  assert(::mlir::succeeded(_result_ref));
  return SymbolRefAttr::get(odsParser.getContext(),
      mlir::FlatSymbolRefAttr((*_result_ref)));
}

void SymbolRefAttr::print(::mlir::AsmPrinter &odsPrinter) const {
  ::mlir::Builder odsBuilder(getContext());
  odsPrinter << "<";
  odsPrinter.printStrippedAttrOrType(getRef());
  odsPrinter << ">";
}

mlir::FlatSymbolRefAttr SymbolRefAttr::getRef() const {
  return getImpl()->ref;
}


} // namespace circt::om
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::om::SymbolRefAttr)
namespace circt::om {

namespace detail {

struct ListAttrStorage : public ::mlir::AttributeStorage {
  using KeyTy = std::tuple<mlir::Type, mlir::ArrayAttr>;
  ListAttrStorage(mlir::Type elementType, mlir::ArrayAttr elements) : elementType(std::move(elementType)), elements(std::move(elements)) {}

  KeyTy getAsKey() const {
    return KeyTy(elementType, elements);
  }

  bool operator==(const KeyTy &tblgenKey) const {
    return (elementType == std::get<0>(tblgenKey)) && (elements == std::get<1>(tblgenKey));
  }

  static ::llvm::hash_code hashKey(const KeyTy &tblgenKey) {
    return ::llvm::hash_combine(std::get<0>(tblgenKey), std::get<1>(tblgenKey));
  }

  static ListAttrStorage *construct(::mlir::AttributeStorageAllocator &allocator, KeyTy &&tblgenKey) {
    auto elementType = std::move(std::get<0>(tblgenKey));
    auto elements = std::move(std::get<1>(tblgenKey));
    return new (allocator.allocate<ListAttrStorage>()) ListAttrStorage(std::move(elementType), std::move(elements));
  }

  mlir::Type elementType;
  mlir::ArrayAttr elements;
};

} // namespace detail
ListAttr ListAttr::get(::mlir::MLIRContext *context, mlir::Type elementType, mlir::ArrayAttr elements) {
  return Base::get(context, std::move(elementType), std::move(elements));
}

ListAttr ListAttr::getChecked(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::mlir::MLIRContext *context, mlir::Type elementType, mlir::ArrayAttr elements) {
  return Base::getChecked(emitError, context, std::move(elementType), std::move(elements));
}

::llvm::LogicalResult ListAttr::verifyInvariants(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, mlir::Type elementType, mlir::ArrayAttr elements) {
  if (::mlir::failed(verify(emitError, elementType, elements)))
    return ::mlir::failure();
  return ::mlir::success();
}

::mlir::Attribute ListAttr::parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType) {
  ::mlir::Builder odsBuilder(odsParser.getContext());
  ::llvm::SMLoc odsLoc = odsParser.getCurrentLocation();
  (void) odsLoc;
  ::mlir::FailureOr<mlir::Type> _result_elementType;
  ::mlir::FailureOr<mlir::ArrayAttr> _result_elements;
  // Parse literal '<'
  if (odsParser.parseLess()) return {};

  // Parse variable 'elementType'
  _result_elementType = ::mlir::FieldParser<mlir::Type>::parse(odsParser);
  if (::mlir::failed(_result_elementType)) {
    odsParser.emitError(odsParser.getCurrentLocation(), "failed to parse OMListAttr parameter 'elementType' which is to be a `mlir::Type`");
    return {};
  }
  // Parse literal ','
  if (odsParser.parseComma()) return {};

  // Parse variable 'elements'
  _result_elements = ::mlir::FieldParser<mlir::ArrayAttr>::parse(odsParser);
  if (::mlir::failed(_result_elements)) {
    odsParser.emitError(odsParser.getCurrentLocation(), "failed to parse OMListAttr parameter 'elements' which is to be a `mlir::ArrayAttr`");
    return {};
  }
  // Parse literal '>'
  if (odsParser.parseGreater()) return {};
  assert(::mlir::succeeded(_result_elementType));
  assert(::mlir::succeeded(_result_elements));
  return odsParser.getChecked<ListAttr>(odsLoc, odsParser.getContext(),
      mlir::Type((*_result_elementType)),
      mlir::ArrayAttr((*_result_elements)));
}

void ListAttr::print(::mlir::AsmPrinter &odsPrinter) const {
  ::mlir::Builder odsBuilder(getContext());
  odsPrinter << "<";
  odsPrinter.printStrippedAttrOrType(getElementType());
  odsPrinter << ",";
  odsPrinter << ' ';
  odsPrinter.printStrippedAttrOrType(getElements());
  odsPrinter << ">";
}

mlir::Type ListAttr::getElementType() const {
  return getImpl()->elementType;
}

mlir::ArrayAttr ListAttr::getElements() const {
  return getImpl()->elements;
}


} // namespace circt::om
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::om::ListAttr)
namespace circt::om {

namespace detail {

struct PathAttrStorage : public ::mlir::AttributeStorage {
  using KeyTy = std::tuple<::llvm::ArrayRef<::circt::om::PathElement>>;
  PathAttrStorage(::llvm::ArrayRef<::circt::om::PathElement> path) : path(std::move(path)) {}

  KeyTy getAsKey() const {
    return KeyTy(path);
  }

  bool operator==(const KeyTy &tblgenKey) const {
    return (path == std::get<0>(tblgenKey));
  }

  static ::llvm::hash_code hashKey(const KeyTy &tblgenKey) {
    return ::llvm::hash_combine(std::get<0>(tblgenKey));
  }

  static PathAttrStorage *construct(::mlir::AttributeStorageAllocator &allocator, KeyTy &&tblgenKey) {
    auto path = std::move(std::get<0>(tblgenKey));
    path = allocator.copyInto(path);
    return new (allocator.allocate<PathAttrStorage>()) PathAttrStorage(std::move(path));
  }

  ::llvm::ArrayRef<::circt::om::PathElement> path;
};

} // namespace detail
PathAttr PathAttr::get(::mlir::MLIRContext *context, ::llvm::ArrayRef<::circt::om::PathElement> path) {
  return Base::get(context, std::move(path));
}

PathAttr PathAttr::getChecked(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::mlir::MLIRContext *context, ::llvm::ArrayRef<::circt::om::PathElement> path) {
  return Base::getChecked(emitError, context, std::move(path));
}

::llvm::LogicalResult PathAttr::verifyInvariants(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::llvm::ArrayRef<::circt::om::PathElement> path) {
  if (::mlir::failed(verify(emitError, path)))
    return ::mlir::failure();
  return ::mlir::success();
}

::llvm::ArrayRef<::circt::om::PathElement> PathAttr::getPath() const {
  return getImpl()->path;
}


} // namespace circt::om
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::om::PathAttr)
namespace circt::om {

namespace detail {

struct IntegerAttrStorage : public ::mlir::AttributeStorage {
  using KeyTy = std::tuple<mlir::IntegerAttr>;
  IntegerAttrStorage(mlir::IntegerAttr value) : value(std::move(value)) {}

  KeyTy getAsKey() const {
    return KeyTy(value);
  }

  bool operator==(const KeyTy &tblgenKey) const {
    return (value == std::get<0>(tblgenKey));
  }

  static ::llvm::hash_code hashKey(const KeyTy &tblgenKey) {
    return ::llvm::hash_combine(std::get<0>(tblgenKey));
  }

  static IntegerAttrStorage *construct(::mlir::AttributeStorageAllocator &allocator, KeyTy &&tblgenKey) {
    auto value = std::move(std::get<0>(tblgenKey));
    return new (allocator.allocate<IntegerAttrStorage>()) IntegerAttrStorage(std::move(value));
  }

  mlir::IntegerAttr value;
};

} // namespace detail
IntegerAttr IntegerAttr::get(::mlir::MLIRContext *context, mlir::IntegerAttr value) {
  return Base::get(context, std::move(value));
}

IntegerAttr IntegerAttr::getChecked(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::mlir::MLIRContext *context, mlir::IntegerAttr value) {
  return Base::getChecked(emitError, context, std::move(value));
}

::llvm::LogicalResult IntegerAttr::verifyInvariants(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, mlir::IntegerAttr value) {
  if (::mlir::failed(verify(emitError, value)))
    return ::mlir::failure();
  return ::mlir::success();
}

::mlir::Attribute IntegerAttr::parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType) {
  ::mlir::Builder odsBuilder(odsParser.getContext());
  ::llvm::SMLoc odsLoc = odsParser.getCurrentLocation();
  (void) odsLoc;
  ::mlir::FailureOr<mlir::IntegerAttr> _result_value;
  // Parse literal '<'
  if (odsParser.parseLess()) return {};

  // Parse variable 'value'
  _result_value = ::mlir::FieldParser<mlir::IntegerAttr>::parse(odsParser);
  if (::mlir::failed(_result_value)) {
    odsParser.emitError(odsParser.getCurrentLocation(), "failed to parse OMIntegerAttr parameter 'value' which is to be a `mlir::IntegerAttr`");
    return {};
  }
  // Parse literal '>'
  if (odsParser.parseGreater()) return {};
  assert(::mlir::succeeded(_result_value));
  return odsParser.getChecked<IntegerAttr>(odsLoc, odsParser.getContext(),
      mlir::IntegerAttr((*_result_value)));
}

void IntegerAttr::print(::mlir::AsmPrinter &odsPrinter) const {
  ::mlir::Builder odsBuilder(getContext());
  odsPrinter << "<";
  odsPrinter.printStrippedAttrOrType(getValue());
  odsPrinter << ">";
}

mlir::IntegerAttr IntegerAttr::getValue() const {
  return getImpl()->value;
}


} // namespace circt::om
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::om::IntegerAttr)
namespace circt::om {


/// Parse an attribute registered to this dialect.
::mlir::Attribute OMDialect::parseAttribute(::mlir::DialectAsmParser &parser,
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
void OMDialect::printAttribute(::mlir::Attribute attr,
                         ::mlir::DialectAsmPrinter &printer) const {
  if (::mlir::succeeded(generatedAttributePrinter(attr, printer)))
    return;
  
}

} // namespace circt::om

#endif // GET_ATTRDEF_CLASSES

