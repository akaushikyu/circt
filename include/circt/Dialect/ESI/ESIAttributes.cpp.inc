/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* AttrDef Definitions                                                        *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

#ifdef GET_ATTRDEF_LIST
#undef GET_ATTRDEF_LIST

::circt::esi::NullChannelAttr,
::circt::esi::AppIDAttr,
::circt::esi::AppIDPathAttr,
::circt::esi::BlobAttr

#endif // GET_ATTRDEF_LIST

#ifdef GET_ATTRDEF_CLASSES
#undef GET_ATTRDEF_CLASSES

static ::mlir::OptionalParseResult generatedAttributeParser(::mlir::AsmParser &parser, ::llvm::StringRef *mnemonic, ::mlir::Type type, ::mlir::Attribute &value) {
  return ::mlir::AsmParser::KeywordSwitch<::mlir::OptionalParseResult>(parser)
    .Case(::circt::esi::NullChannelAttr::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::esi::NullChannelAttr::parse(parser, type);
      return ::mlir::success(!!value);
    })
    .Case(::circt::esi::AppIDAttr::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::esi::AppIDAttr::parse(parser, type);
      return ::mlir::success(!!value);
    })
    .Case(::circt::esi::AppIDPathAttr::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::esi::AppIDPathAttr::parse(parser, type);
      return ::mlir::success(!!value);
    })
    .Case(::circt::esi::BlobAttr::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::esi::BlobAttr::parse(parser, type);
      return ::mlir::success(!!value);
    })
    .Default([&](llvm::StringRef keyword, llvm::SMLoc) {
      *mnemonic = keyword;
      return std::nullopt;
    });
}

static ::llvm::LogicalResult generatedAttributePrinter(::mlir::Attribute def, ::mlir::AsmPrinter &printer) {
  return ::llvm::TypeSwitch<::mlir::Attribute, ::llvm::LogicalResult>(def)    .Case<::circt::esi::NullChannelAttr>([&](auto t) {
      printer << ::circt::esi::NullChannelAttr::getMnemonic();
printer << ' ';
t.print(printer);
      return ::mlir::success();
    })
    .Case<::circt::esi::AppIDAttr>([&](auto t) {
      printer << ::circt::esi::AppIDAttr::getMnemonic();
t.print(printer);
      return ::mlir::success();
    })
    .Case<::circt::esi::AppIDPathAttr>([&](auto t) {
      printer << ::circt::esi::AppIDPathAttr::getMnemonic();
t.print(printer);
      return ::mlir::success();
    })
    .Case<::circt::esi::BlobAttr>([&](auto t) {
      printer << ::circt::esi::BlobAttr::getMnemonic();
t.print(printer);
      return ::mlir::success();
    })
    .Default([](auto) { return ::mlir::failure(); });
}

namespace circt::esi {

namespace detail {

struct NullChannelAttrStorage : public ::mlir::AttributeStorage {
  using KeyTy = std::tuple<TypeAttr>;
  NullChannelAttrStorage(TypeAttr type) : type(std::move(type)) {}

  KeyTy getAsKey() const {
    return KeyTy(type);
  }

  bool operator==(const KeyTy &tblgenKey) const {
    return (type == std::get<0>(tblgenKey));
  }

  static ::llvm::hash_code hashKey(const KeyTy &tblgenKey) {
    return ::llvm::hash_combine(std::get<0>(tblgenKey));
  }

  static NullChannelAttrStorage *construct(::mlir::AttributeStorageAllocator &allocator, KeyTy &&tblgenKey) {
    auto type = std::move(std::get<0>(tblgenKey));
    return new (allocator.allocate<NullChannelAttrStorage>()) NullChannelAttrStorage(std::move(type));
  }

  TypeAttr type;
};

} // namespace detail
NullChannelAttr NullChannelAttr::get(::mlir::MLIRContext *context, TypeAttr type) {
  return Base::get(context, std::move(type));
}

::mlir::Attribute NullChannelAttr::parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType) {
  ::mlir::Builder odsBuilder(odsParser.getContext());
  ::llvm::SMLoc odsLoc = odsParser.getCurrentLocation();
  (void) odsLoc;
  ::mlir::FailureOr<TypeAttr> _result_type;

  // Parse variable 'type'
  _result_type = ::mlir::FieldParser<TypeAttr>::parse(odsParser);
  if (::mlir::failed(_result_type)) {
    odsParser.emitError(odsParser.getCurrentLocation(), "failed to parse SinkChannelAttr parameter 'type' which is to be a `TypeAttr`");
    return {};
  }
  assert(::mlir::succeeded(_result_type));
  return NullChannelAttr::get(odsParser.getContext(),
      TypeAttr((*_result_type)));
}

void NullChannelAttr::print(::mlir::AsmPrinter &odsPrinter) const {
  ::mlir::Builder odsBuilder(getContext());
  odsPrinter.printStrippedAttrOrType(getType());
}

TypeAttr NullChannelAttr::getType() const {
  return getImpl()->type;
}


} // namespace circt::esi
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::esi::NullChannelAttr)
namespace circt::esi {

namespace detail {

struct AppIDAttrStorage : public ::mlir::AttributeStorage {
  using KeyTy = std::tuple<StringAttr, std::optional<uint64_t>>;
  AppIDAttrStorage(StringAttr name, std::optional<uint64_t> index) : name(std::move(name)), index(std::move(index)) {}

  KeyTy getAsKey() const {
    return KeyTy(name, index);
  }

  bool operator==(const KeyTy &tblgenKey) const {
    return (name == std::get<0>(tblgenKey)) && (index == std::get<1>(tblgenKey));
  }

  static ::llvm::hash_code hashKey(const KeyTy &tblgenKey) {
    return ::llvm::hash_combine(std::get<0>(tblgenKey), std::get<1>(tblgenKey));
  }

  static AppIDAttrStorage *construct(::mlir::AttributeStorageAllocator &allocator, KeyTy &&tblgenKey) {
    auto name = std::move(std::get<0>(tblgenKey));
    auto index = std::move(std::get<1>(tblgenKey));
    return new (allocator.allocate<AppIDAttrStorage>()) AppIDAttrStorage(std::move(name), std::move(index));
  }

  StringAttr name;
  std::optional<uint64_t> index;
};

} // namespace detail
AppIDAttr AppIDAttr::get(::mlir::MLIRContext *context, StringAttr name, std::optional<uint64_t> index) {
  return Base::get(context, std::move(name), std::move(index));
}

::mlir::Attribute AppIDAttr::parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType) {
  ::mlir::Builder odsBuilder(odsParser.getContext());
  ::llvm::SMLoc odsLoc = odsParser.getCurrentLocation();
  (void) odsLoc;
  ::mlir::FailureOr<StringAttr> _result_name;
  ::mlir::FailureOr<std::optional<uint64_t>> _result_index;
  // Parse literal '<'
  if (odsParser.parseLess()) return {};

  // Parse variable 'name'
  _result_name = ::mlir::FieldParser<StringAttr>::parse(odsParser);
  if (::mlir::failed(_result_name)) {
    odsParser.emitError(odsParser.getCurrentLocation(), "failed to parse AppIDAttr parameter 'name' which is to be a `StringAttr`");
    return {};
  }
  // Parse literal '['
  if (odsParser.parseOptionalLSquare()) {
  } else {

    // Parse variable 'index'
    _result_index = ::mlir::FieldParser<std::optional<uint64_t>>::parse(odsParser);
    if (::mlir::failed(_result_index)) {
      odsParser.emitError(odsParser.getCurrentLocation(), "failed to parse AppIDAttr parameter 'index' which is to be a `std::optional<uint64_t>`");
      return {};
    }
    // Parse literal ']'
    if (odsParser.parseRSquare()) return {};
  }
  // Parse literal '>'
  if (odsParser.parseGreater()) return {};
  assert(::mlir::succeeded(_result_name));
  return AppIDAttr::get(odsParser.getContext(),
      StringAttr((*_result_name)),
      std::optional<uint64_t>((_result_index.value_or(std::optional<uint64_t>()))));
}

void AppIDAttr::print(::mlir::AsmPrinter &odsPrinter) const {
  ::mlir::Builder odsBuilder(getContext());
  odsPrinter << "<";
  odsPrinter.printStrippedAttrOrType(getName());
  if (!(getIndex() == std::optional<uint64_t>())) {
    odsPrinter << "[";
    if (!(getIndex() == std::optional<uint64_t>())) {
      odsPrinter.printStrippedAttrOrType(getIndex());
    }
    odsPrinter << "]";
  } else {
  }
  odsPrinter << ">";
}

StringAttr AppIDAttr::getName() const {
  return getImpl()->name;
}

std::optional<uint64_t> AppIDAttr::getIndex() const {
  return getImpl()->index;
}


} // namespace circt::esi
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::esi::AppIDAttr)
namespace circt::esi {

namespace detail {

struct AppIDPathAttrStorage : public ::mlir::AttributeStorage {
  using KeyTy = std::tuple<FlatSymbolRefAttr, ::llvm::ArrayRef<AppIDAttr>>;
  AppIDPathAttrStorage(FlatSymbolRefAttr root, ::llvm::ArrayRef<AppIDAttr> path) : root(std::move(root)), path(std::move(path)) {}

  KeyTy getAsKey() const {
    return KeyTy(root, path);
  }

  bool operator==(const KeyTy &tblgenKey) const {
    return (root == std::get<0>(tblgenKey)) && (path == std::get<1>(tblgenKey));
  }

  static ::llvm::hash_code hashKey(const KeyTy &tblgenKey) {
    return ::llvm::hash_combine(std::get<0>(tblgenKey), std::get<1>(tblgenKey));
  }

  static AppIDPathAttrStorage *construct(::mlir::AttributeStorageAllocator &allocator, KeyTy &&tblgenKey) {
    auto root = std::move(std::get<0>(tblgenKey));
    auto path = std::move(std::get<1>(tblgenKey));
    path = allocator.copyInto(path);
    return new (allocator.allocate<AppIDPathAttrStorage>()) AppIDPathAttrStorage(std::move(root), std::move(path));
  }

  FlatSymbolRefAttr root;
  ::llvm::ArrayRef<AppIDAttr> path;
};

} // namespace detail
AppIDPathAttr AppIDPathAttr::get(::mlir::MLIRContext *context, FlatSymbolRefAttr root, ::llvm::ArrayRef<AppIDAttr> path) {
  return Base::get(context, std::move(root), std::move(path));
}

::mlir::Attribute AppIDPathAttr::parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType) {
  ::mlir::Builder odsBuilder(odsParser.getContext());
  ::llvm::SMLoc odsLoc = odsParser.getCurrentLocation();
  (void) odsLoc;
  ::mlir::FailureOr<FlatSymbolRefAttr> _result_root;
  ::mlir::FailureOr<::llvm::SmallVector<AppIDAttr>> _result_path;
  // Parse literal '<'
  if (odsParser.parseLess()) return {};

  // Parse variable 'root'
  _result_root = ::mlir::FieldParser<FlatSymbolRefAttr>::parse(odsParser);
  if (::mlir::failed(_result_root)) {
    odsParser.emitError(odsParser.getCurrentLocation(), "failed to parse AppIDPathAttr parameter 'root' which is to be a `FlatSymbolRefAttr`");
    return {};
  }
  // Parse literal '['
  if (odsParser.parseLSquare()) return {};

  // Parse variable 'path'
  _result_path = ::mlir::FieldParser<::llvm::SmallVector<AppIDAttr>>::parse(odsParser);
  if (::mlir::failed(_result_path)) {
    odsParser.emitError(odsParser.getCurrentLocation(), "failed to parse AppIDPathAttr parameter 'path' which is to be a `::llvm::ArrayRef<AppIDAttr>`");
    return {};
  }
  // Parse literal ']'
  if (odsParser.parseRSquare()) return {};
  // Parse literal '>'
  if (odsParser.parseGreater()) return {};
  assert(::mlir::succeeded(_result_root));
  assert(::mlir::succeeded(_result_path));
  return AppIDPathAttr::get(odsParser.getContext(),
      FlatSymbolRefAttr((*_result_root)),
      ::llvm::ArrayRef<AppIDAttr>((*_result_path)));
}

void AppIDPathAttr::print(::mlir::AsmPrinter &odsPrinter) const {
  ::mlir::Builder odsBuilder(getContext());
  odsPrinter << "<";
  odsPrinter.printStrippedAttrOrType(getRoot());
  odsPrinter << "[";
  odsPrinter.printStrippedAttrOrType(getPath());
  odsPrinter << "]";
  odsPrinter << ">";
}

FlatSymbolRefAttr AppIDPathAttr::getRoot() const {
  return getImpl()->root;
}

::llvm::ArrayRef<AppIDAttr> AppIDPathAttr::getPath() const {
  return getImpl()->path;
}


} // namespace circt::esi
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::esi::AppIDPathAttr)
namespace circt::esi {

namespace detail {

struct BlobAttrStorage : public ::mlir::AttributeStorage {
  using KeyTy = std::tuple<::llvm::ArrayRef<uint8_t>>;
  BlobAttrStorage(::llvm::ArrayRef<uint8_t> data) : data(std::move(data)) {}

  KeyTy getAsKey() const {
    return KeyTy(data);
  }

  bool operator==(const KeyTy &tblgenKey) const {
    return (data == std::get<0>(tblgenKey));
  }

  static ::llvm::hash_code hashKey(const KeyTy &tblgenKey) {
    return ::llvm::hash_combine(std::get<0>(tblgenKey));
  }

  static BlobAttrStorage *construct(::mlir::AttributeStorageAllocator &allocator, KeyTy &&tblgenKey) {
    auto data = std::move(std::get<0>(tblgenKey));
    data = allocator.copyInto(data);
    return new (allocator.allocate<BlobAttrStorage>()) BlobAttrStorage(std::move(data));
  }

  ::llvm::ArrayRef<uint8_t> data;
};

} // namespace detail
BlobAttr BlobAttr::get(::mlir::MLIRContext *context, ::llvm::ArrayRef<uint8_t> data) {
  return Base::get(context, std::move(data));
}

::llvm::ArrayRef<uint8_t> BlobAttr::getData() const {
  return getImpl()->data;
}


} // namespace circt::esi
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::esi::BlobAttr)
namespace circt::esi {


/// Parse an attribute registered to this dialect.
::mlir::Attribute ESIDialect::parseAttribute(::mlir::DialectAsmParser &parser,
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
void ESIDialect::printAttribute(::mlir::Attribute attr,
                         ::mlir::DialectAsmPrinter &printer) const {
  if (::mlir::succeeded(generatedAttributePrinter(attr, printer)))
    return;
  
}

} // namespace circt::esi

#endif // GET_ATTRDEF_CLASSES

