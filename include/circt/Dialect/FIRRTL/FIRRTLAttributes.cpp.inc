/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* AttrDef Definitions                                                        *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

#ifdef GET_ATTRDEF_LIST
#undef GET_ATTRDEF_LIST

::circt::firrtl::AugmentedBundleTypeAttr,
::circt::firrtl::AugmentedVectorTypeAttr,
::circt::firrtl::AugmentedGroundTypeAttr,
::circt::firrtl::ParamDeclAttr,
::circt::firrtl::MemoryInitAttr,
::circt::firrtl::DomainFieldAttr,
::circt::firrtl::NameKindEnumAttr,
::circt::firrtl::ConventionAttr,
::circt::firrtl::LayerConventionAttr,
::circt::firrtl::LayerSpecializationAttr,
::circt::firrtl::RUWBehaviorAttr

#endif // GET_ATTRDEF_LIST

#ifdef GET_ATTRDEF_CLASSES
#undef GET_ATTRDEF_CLASSES

static ::mlir::OptionalParseResult generatedAttributeParser(::mlir::AsmParser &parser, ::llvm::StringRef *mnemonic, ::mlir::Type type, ::mlir::Attribute &value) {
  return ::mlir::AsmParser::KeywordSwitch<::mlir::OptionalParseResult>(parser)
    .Case(::circt::firrtl::AugmentedBundleTypeAttr::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::firrtl::AugmentedBundleTypeAttr::parse(parser, type);
      return ::mlir::success(!!value);
    })
    .Case(::circt::firrtl::AugmentedVectorTypeAttr::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::firrtl::AugmentedVectorTypeAttr::parse(parser, type);
      return ::mlir::success(!!value);
    })
    .Case(::circt::firrtl::AugmentedGroundTypeAttr::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::firrtl::AugmentedGroundTypeAttr::parse(parser, type);
      return ::mlir::success(!!value);
    })
    .Case(::circt::firrtl::ParamDeclAttr::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::firrtl::ParamDeclAttr::parse(parser, type);
      return ::mlir::success(!!value);
    })
    .Case(::circt::firrtl::MemoryInitAttr::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::firrtl::MemoryInitAttr::parse(parser, type);
      return ::mlir::success(!!value);
    })
    .Case(::circt::firrtl::DomainFieldAttr::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::firrtl::DomainFieldAttr::parse(parser, type);
      return ::mlir::success(!!value);
    })
    .Case(::circt::firrtl::NameKindEnumAttr::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::firrtl::NameKindEnumAttr::parse(parser, type);
      return ::mlir::success(!!value);
    })
    .Case(::circt::firrtl::ConventionAttr::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::firrtl::ConventionAttr::parse(parser, type);
      return ::mlir::success(!!value);
    })
    .Case(::circt::firrtl::LayerConventionAttr::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::firrtl::LayerConventionAttr::parse(parser, type);
      return ::mlir::success(!!value);
    })
    .Case(::circt::firrtl::LayerSpecializationAttr::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::firrtl::LayerSpecializationAttr::parse(parser, type);
      return ::mlir::success(!!value);
    })
    .Case(::circt::firrtl::RUWBehaviorAttr::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::firrtl::RUWBehaviorAttr::parse(parser, type);
      return ::mlir::success(!!value);
    })
    .Default([&](llvm::StringRef keyword, llvm::SMLoc) {
      *mnemonic = keyword;
      return std::nullopt;
    });
}

static ::llvm::LogicalResult generatedAttributePrinter(::mlir::Attribute def, ::mlir::AsmPrinter &printer) {
  return ::llvm::TypeSwitch<::mlir::Attribute, ::llvm::LogicalResult>(def)    .Case<::circt::firrtl::AugmentedBundleTypeAttr>([&](auto t) {
      printer << ::circt::firrtl::AugmentedBundleTypeAttr::getMnemonic();
t.print(printer);
      return ::mlir::success();
    })
    .Case<::circt::firrtl::AugmentedVectorTypeAttr>([&](auto t) {
      printer << ::circt::firrtl::AugmentedVectorTypeAttr::getMnemonic();
t.print(printer);
      return ::mlir::success();
    })
    .Case<::circt::firrtl::AugmentedGroundTypeAttr>([&](auto t) {
      printer << ::circt::firrtl::AugmentedGroundTypeAttr::getMnemonic();
t.print(printer);
      return ::mlir::success();
    })
    .Case<::circt::firrtl::ParamDeclAttr>([&](auto t) {
      printer << ::circt::firrtl::ParamDeclAttr::getMnemonic();
t.print(printer);
      return ::mlir::success();
    })
    .Case<::circt::firrtl::MemoryInitAttr>([&](auto t) {
      printer << ::circt::firrtl::MemoryInitAttr::getMnemonic();
t.print(printer);
      return ::mlir::success();
    })
    .Case<::circt::firrtl::DomainFieldAttr>([&](auto t) {
      printer << ::circt::firrtl::DomainFieldAttr::getMnemonic();
t.print(printer);
      return ::mlir::success();
    })
    .Case<::circt::firrtl::NameKindEnumAttr>([&](auto t) {
      printer << ::circt::firrtl::NameKindEnumAttr::getMnemonic();
printer << ' ';
t.print(printer);
      return ::mlir::success();
    })
    .Case<::circt::firrtl::ConventionAttr>([&](auto t) {
      printer << ::circt::firrtl::ConventionAttr::getMnemonic();
printer << ' ';
t.print(printer);
      return ::mlir::success();
    })
    .Case<::circt::firrtl::LayerConventionAttr>([&](auto t) {
      printer << ::circt::firrtl::LayerConventionAttr::getMnemonic();
printer << ' ';
t.print(printer);
      return ::mlir::success();
    })
    .Case<::circt::firrtl::LayerSpecializationAttr>([&](auto t) {
      printer << ::circt::firrtl::LayerSpecializationAttr::getMnemonic();
printer << ' ';
t.print(printer);
      return ::mlir::success();
    })
    .Case<::circt::firrtl::RUWBehaviorAttr>([&](auto t) {
      printer << ::circt::firrtl::RUWBehaviorAttr::getMnemonic();
printer << ' ';
t.print(printer);
      return ::mlir::success();
    })
    .Default([](auto) { return ::mlir::failure(); });
}

namespace circt::firrtl {

namespace detail {

struct AugmentedBundleTypeAttrStorage : public ::mlir::AttributeStorage {
  using KeyTy = std::tuple<DictionaryAttr>;
  AugmentedBundleTypeAttrStorage(DictionaryAttr underlying) : underlying(std::move(underlying)) {}

  KeyTy getAsKey() const {
    return KeyTy(underlying);
  }

  bool operator==(const KeyTy &tblgenKey) const {
    return (underlying == std::get<0>(tblgenKey));
  }

  static ::llvm::hash_code hashKey(const KeyTy &tblgenKey) {
    return ::llvm::hash_combine(std::get<0>(tblgenKey));
  }

  static AugmentedBundleTypeAttrStorage *construct(::mlir::AttributeStorageAllocator &allocator, KeyTy &&tblgenKey) {
    auto underlying = std::move(std::get<0>(tblgenKey));
    return new (allocator.allocate<AugmentedBundleTypeAttrStorage>()) AugmentedBundleTypeAttrStorage(std::move(underlying));
  }

  DictionaryAttr underlying;
};

} // namespace detail
AugmentedBundleTypeAttr AugmentedBundleTypeAttr::get(::mlir::MLIRContext *context, DictionaryAttr underlying) {
  return Base::get(context, std::move(underlying));
}

::mlir::Attribute AugmentedBundleTypeAttr::parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType) {
  ::mlir::Builder odsBuilder(odsParser.getContext());
  ::llvm::SMLoc odsLoc = odsParser.getCurrentLocation();
  (void) odsLoc;
  ::mlir::FailureOr<DictionaryAttr> _result_underlying;
  // Parse literal '<'
  if (odsParser.parseLess()) return {};

  // Parse variable 'underlying'
  _result_underlying = ::mlir::FieldParser<DictionaryAttr>::parse(odsParser);
  if (::mlir::failed(_result_underlying)) {
    odsParser.emitError(odsParser.getCurrentLocation(), "failed to parse AugmentedBundleType parameter 'underlying' which is to be a `DictionaryAttr`");
    return {};
  }
  // Parse literal '>'
  if (odsParser.parseGreater()) return {};
  assert(::mlir::succeeded(_result_underlying));
  return AugmentedBundleTypeAttr::get(odsParser.getContext(),
      DictionaryAttr((*_result_underlying)));
}

void AugmentedBundleTypeAttr::print(::mlir::AsmPrinter &odsPrinter) const {
  ::mlir::Builder odsBuilder(getContext());
  odsPrinter << "<";
  odsPrinter.printStrippedAttrOrType(getUnderlying());
  odsPrinter << ">";
}

DictionaryAttr AugmentedBundleTypeAttr::getUnderlying() const {
  return getImpl()->underlying;
}


} // namespace circt::firrtl
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::firrtl::AugmentedBundleTypeAttr)
namespace circt::firrtl {

namespace detail {

struct AugmentedVectorTypeAttrStorage : public ::mlir::AttributeStorage {
  using KeyTy = std::tuple<DictionaryAttr>;
  AugmentedVectorTypeAttrStorage(DictionaryAttr underlying) : underlying(std::move(underlying)) {}

  KeyTy getAsKey() const {
    return KeyTy(underlying);
  }

  bool operator==(const KeyTy &tblgenKey) const {
    return (underlying == std::get<0>(tblgenKey));
  }

  static ::llvm::hash_code hashKey(const KeyTy &tblgenKey) {
    return ::llvm::hash_combine(std::get<0>(tblgenKey));
  }

  static AugmentedVectorTypeAttrStorage *construct(::mlir::AttributeStorageAllocator &allocator, KeyTy &&tblgenKey) {
    auto underlying = std::move(std::get<0>(tblgenKey));
    return new (allocator.allocate<AugmentedVectorTypeAttrStorage>()) AugmentedVectorTypeAttrStorage(std::move(underlying));
  }

  DictionaryAttr underlying;
};

} // namespace detail
AugmentedVectorTypeAttr AugmentedVectorTypeAttr::get(::mlir::MLIRContext *context, DictionaryAttr underlying) {
  return Base::get(context, std::move(underlying));
}

::mlir::Attribute AugmentedVectorTypeAttr::parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType) {
  ::mlir::Builder odsBuilder(odsParser.getContext());
  ::llvm::SMLoc odsLoc = odsParser.getCurrentLocation();
  (void) odsLoc;
  ::mlir::FailureOr<DictionaryAttr> _result_underlying;
  // Parse literal '<'
  if (odsParser.parseLess()) return {};

  // Parse variable 'underlying'
  _result_underlying = ::mlir::FieldParser<DictionaryAttr>::parse(odsParser);
  if (::mlir::failed(_result_underlying)) {
    odsParser.emitError(odsParser.getCurrentLocation(), "failed to parse AugmentedVectorType parameter 'underlying' which is to be a `DictionaryAttr`");
    return {};
  }
  // Parse literal '>'
  if (odsParser.parseGreater()) return {};
  assert(::mlir::succeeded(_result_underlying));
  return AugmentedVectorTypeAttr::get(odsParser.getContext(),
      DictionaryAttr((*_result_underlying)));
}

void AugmentedVectorTypeAttr::print(::mlir::AsmPrinter &odsPrinter) const {
  ::mlir::Builder odsBuilder(getContext());
  odsPrinter << "<";
  odsPrinter.printStrippedAttrOrType(getUnderlying());
  odsPrinter << ">";
}

DictionaryAttr AugmentedVectorTypeAttr::getUnderlying() const {
  return getImpl()->underlying;
}


} // namespace circt::firrtl
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::firrtl::AugmentedVectorTypeAttr)
namespace circt::firrtl {

namespace detail {

struct AugmentedGroundTypeAttrStorage : public ::mlir::AttributeStorage {
  using KeyTy = std::tuple<DictionaryAttr>;
  AugmentedGroundTypeAttrStorage(DictionaryAttr underlying) : underlying(std::move(underlying)) {}

  KeyTy getAsKey() const {
    return KeyTy(underlying);
  }

  bool operator==(const KeyTy &tblgenKey) const {
    return (underlying == std::get<0>(tblgenKey));
  }

  static ::llvm::hash_code hashKey(const KeyTy &tblgenKey) {
    return ::llvm::hash_combine(std::get<0>(tblgenKey));
  }

  static AugmentedGroundTypeAttrStorage *construct(::mlir::AttributeStorageAllocator &allocator, KeyTy &&tblgenKey) {
    auto underlying = std::move(std::get<0>(tblgenKey));
    return new (allocator.allocate<AugmentedGroundTypeAttrStorage>()) AugmentedGroundTypeAttrStorage(std::move(underlying));
  }

  DictionaryAttr underlying;
};

} // namespace detail
AugmentedGroundTypeAttr AugmentedGroundTypeAttr::get(::mlir::MLIRContext *context, DictionaryAttr underlying) {
  return Base::get(context, std::move(underlying));
}

::mlir::Attribute AugmentedGroundTypeAttr::parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType) {
  ::mlir::Builder odsBuilder(odsParser.getContext());
  ::llvm::SMLoc odsLoc = odsParser.getCurrentLocation();
  (void) odsLoc;
  ::mlir::FailureOr<DictionaryAttr> _result_underlying;
  // Parse literal '<'
  if (odsParser.parseLess()) return {};

  // Parse variable 'underlying'
  _result_underlying = ::mlir::FieldParser<DictionaryAttr>::parse(odsParser);
  if (::mlir::failed(_result_underlying)) {
    odsParser.emitError(odsParser.getCurrentLocation(), "failed to parse AugmentedGroundType parameter 'underlying' which is to be a `DictionaryAttr`");
    return {};
  }
  // Parse literal '>'
  if (odsParser.parseGreater()) return {};
  assert(::mlir::succeeded(_result_underlying));
  return AugmentedGroundTypeAttr::get(odsParser.getContext(),
      DictionaryAttr((*_result_underlying)));
}

void AugmentedGroundTypeAttr::print(::mlir::AsmPrinter &odsPrinter) const {
  ::mlir::Builder odsBuilder(getContext());
  odsPrinter << "<";
  odsPrinter.printStrippedAttrOrType(getUnderlying());
  odsPrinter << ">";
}

DictionaryAttr AugmentedGroundTypeAttr::getUnderlying() const {
  return getImpl()->underlying;
}


} // namespace circt::firrtl
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::firrtl::AugmentedGroundTypeAttr)
namespace circt::firrtl {

namespace detail {

struct ParamDeclAttrStorage : public ::mlir::AttributeStorage {
  using KeyTy = std::tuple<::mlir::StringAttr, ::mlir::Type, ::mlir::Attribute>;
  ParamDeclAttrStorage(::mlir::StringAttr name, ::mlir::Type type, ::mlir::Attribute value) : name(std::move(name)), type(std::move(type)), value(std::move(value)) {}

  KeyTy getAsKey() const {
    return KeyTy(name, type, value);
  }

  bool operator==(const KeyTy &tblgenKey) const {
    return (name == std::get<0>(tblgenKey)) && (type == std::get<1>(tblgenKey)) && (value == std::get<2>(tblgenKey));
  }

  static ::llvm::hash_code hashKey(const KeyTy &tblgenKey) {
    return ::llvm::hash_combine(std::get<0>(tblgenKey), std::get<1>(tblgenKey), std::get<2>(tblgenKey));
  }

  static ParamDeclAttrStorage *construct(::mlir::AttributeStorageAllocator &allocator, KeyTy &&tblgenKey) {
    auto name = std::move(std::get<0>(tblgenKey));
    auto type = std::move(std::get<1>(tblgenKey));
    auto value = std::move(std::get<2>(tblgenKey));
    return new (allocator.allocate<ParamDeclAttrStorage>()) ParamDeclAttrStorage(std::move(name), std::move(type), std::move(value));
  }

  ::mlir::StringAttr name;
  ::mlir::Type type;
  ::mlir::Attribute value;
};

} // namespace detail
ParamDeclAttr ParamDeclAttr::get(::mlir::MLIRContext *context, ::mlir::StringAttr name, ::mlir::Type type, ::mlir::Attribute value) {
  return Base::get(context, std::move(name), std::move(type), std::move(value));
}

ParamDeclAttr ParamDeclAttr::get(::mlir::StringAttr name, ::mlir::Type type) {
  auto *context = type.getContext();
  return Base::get(context, name, type, Attribute());
}

ParamDeclAttr ParamDeclAttr::get(::mlir::StringRef name, ::mlir::Type type) {
  return get(StringAttr::get(type.getContext(), name), type);
}

ParamDeclAttr ParamDeclAttr::get(::mlir::StringAttr name, ::mlir::TypedAttr value) {
  auto *context = value.getContext();
  return Base::get(context, name, value.getType(), value);
}

ParamDeclAttr ParamDeclAttr::get(::mlir::StringRef name, ::mlir::TypedAttr value) {
  return get(StringAttr::get(value.getContext(), name), value);
}

::mlir::StringAttr ParamDeclAttr::getName() const {
  return getImpl()->name;
}

::mlir::Type ParamDeclAttr::getType() const {
  return getImpl()->type;
}

::mlir::Attribute ParamDeclAttr::getValue() const {
  return getImpl()->value;
}


} // namespace circt::firrtl
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::firrtl::ParamDeclAttr)
namespace circt::firrtl {

namespace detail {

struct MemoryInitAttrStorage : public ::mlir::AttributeStorage {
  using KeyTy = std::tuple<::mlir::StringAttr, bool, bool>;
  MemoryInitAttrStorage(::mlir::StringAttr filename, bool isBinary, bool isInline) : filename(std::move(filename)), isBinary(std::move(isBinary)), isInline(std::move(isInline)) {}

  KeyTy getAsKey() const {
    return KeyTy(filename, isBinary, isInline);
  }

  bool operator==(const KeyTy &tblgenKey) const {
    return (filename == std::get<0>(tblgenKey)) && (isBinary == std::get<1>(tblgenKey)) && (isInline == std::get<2>(tblgenKey));
  }

  static ::llvm::hash_code hashKey(const KeyTy &tblgenKey) {
    return ::llvm::hash_combine(std::get<0>(tblgenKey), std::get<1>(tblgenKey), std::get<2>(tblgenKey));
  }

  static MemoryInitAttrStorage *construct(::mlir::AttributeStorageAllocator &allocator, KeyTy &&tblgenKey) {
    auto filename = std::move(std::get<0>(tblgenKey));
    auto isBinary = std::move(std::get<1>(tblgenKey));
    auto isInline = std::move(std::get<2>(tblgenKey));
    return new (allocator.allocate<MemoryInitAttrStorage>()) MemoryInitAttrStorage(std::move(filename), std::move(isBinary), std::move(isInline));
  }

  ::mlir::StringAttr filename;
  bool isBinary;
  bool isInline;
};

} // namespace detail
MemoryInitAttr MemoryInitAttr::get(::mlir::MLIRContext *context, ::mlir::StringAttr filename, bool isBinary, bool isInline) {
  return Base::get(context, std::move(filename), std::move(isBinary), std::move(isInline));
}

::mlir::Attribute MemoryInitAttr::parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType) {
  ::mlir::Builder odsBuilder(odsParser.getContext());
  ::llvm::SMLoc odsLoc = odsParser.getCurrentLocation();
  (void) odsLoc;
  ::mlir::FailureOr<::mlir::StringAttr> _result_filename;
  ::mlir::FailureOr<bool> _result_isBinary;
  ::mlir::FailureOr<bool> _result_isInline;
  // Parse literal '<'
  if (odsParser.parseLess()) return {};

  // Parse variable 'filename'
  _result_filename = ::mlir::FieldParser<::mlir::StringAttr>::parse(odsParser);
  if (::mlir::failed(_result_filename)) {
    odsParser.emitError(odsParser.getCurrentLocation(), "failed to parse MemoryInitAttr parameter 'filename' which is to be a `::mlir::StringAttr`");
    return {};
  }
  // Parse literal ','
  if (odsParser.parseComma()) return {};

  // Parse variable 'isBinary'
  _result_isBinary = ::mlir::FieldParser<bool>::parse(odsParser);
  if (::mlir::failed(_result_isBinary)) {
    odsParser.emitError(odsParser.getCurrentLocation(), "failed to parse MemoryInitAttr parameter 'isBinary' which is to be a `bool`");
    return {};
  }
  // Parse literal ','
  if (odsParser.parseComma()) return {};

  // Parse variable 'isInline'
  _result_isInline = ::mlir::FieldParser<bool>::parse(odsParser);
  if (::mlir::failed(_result_isInline)) {
    odsParser.emitError(odsParser.getCurrentLocation(), "failed to parse MemoryInitAttr parameter 'isInline' which is to be a `bool`");
    return {};
  }
  // Parse literal '>'
  if (odsParser.parseGreater()) return {};
  assert(::mlir::succeeded(_result_filename));
  assert(::mlir::succeeded(_result_isBinary));
  assert(::mlir::succeeded(_result_isInline));
  return MemoryInitAttr::get(odsParser.getContext(),
      ::mlir::StringAttr((*_result_filename)),
      bool((*_result_isBinary)),
      bool((*_result_isInline)));
}

void MemoryInitAttr::print(::mlir::AsmPrinter &odsPrinter) const {
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

::mlir::StringAttr MemoryInitAttr::getFilename() const {
  return getImpl()->filename;
}

bool MemoryInitAttr::getIsBinary() const {
  return getImpl()->isBinary;
}

bool MemoryInitAttr::getIsInline() const {
  return getImpl()->isInline;
}


} // namespace circt::firrtl
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::firrtl::MemoryInitAttr)
namespace circt::firrtl {

namespace detail {

struct DomainFieldAttrStorage : public ::mlir::AttributeStorage {
  using KeyTy = std::tuple<::mlir::StringAttr, ::circt::firrtl::PropertyType>;
  DomainFieldAttrStorage(::mlir::StringAttr name, ::circt::firrtl::PropertyType type) : name(std::move(name)), type(std::move(type)) {}

  KeyTy getAsKey() const {
    return KeyTy(name, type);
  }

  bool operator==(const KeyTy &tblgenKey) const {
    return (name == std::get<0>(tblgenKey)) && (type == std::get<1>(tblgenKey));
  }

  static ::llvm::hash_code hashKey(const KeyTy &tblgenKey) {
    return ::llvm::hash_combine(std::get<0>(tblgenKey), std::get<1>(tblgenKey));
  }

  static DomainFieldAttrStorage *construct(::mlir::AttributeStorageAllocator &allocator, KeyTy &&tblgenKey) {
    auto name = std::move(std::get<0>(tblgenKey));
    auto type = std::move(std::get<1>(tblgenKey));
    return new (allocator.allocate<DomainFieldAttrStorage>()) DomainFieldAttrStorage(std::move(name), std::move(type));
  }

  ::mlir::StringAttr name;
  ::circt::firrtl::PropertyType type;
};

} // namespace detail
DomainFieldAttr DomainFieldAttr::get(::mlir::MLIRContext *context, ::mlir::StringAttr name, ::circt::firrtl::PropertyType type) {
  return Base::get(context, std::move(name), std::move(type));
}

::mlir::Attribute DomainFieldAttr::parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType) {
  ::mlir::Builder odsBuilder(odsParser.getContext());
  ::llvm::SMLoc odsLoc = odsParser.getCurrentLocation();
  (void) odsLoc;
  ::mlir::FailureOr<::mlir::StringAttr> _result_name;
  ::mlir::FailureOr<::circt::firrtl::PropertyType> _result_type;
  // Parse literal '<'
  if (odsParser.parseLess()) return {};

  // Parse variable 'name'
  _result_name = ::mlir::FieldParser<::mlir::StringAttr>::parse(odsParser);
  if (::mlir::failed(_result_name)) {
    odsParser.emitError(odsParser.getCurrentLocation(), "failed to parse DomainFieldAttr parameter 'name' which is to be a `::mlir::StringAttr`");
    return {};
  }
  // Parse literal ','
  if (odsParser.parseComma()) return {};

  // Parse variable 'type'
  _result_type = ::mlir::FieldParser<::circt::firrtl::PropertyType>::parse(odsParser);
  if (::mlir::failed(_result_type)) {
    odsParser.emitError(odsParser.getCurrentLocation(), "failed to parse DomainFieldAttr parameter 'type' which is to be a `::circt::firrtl::PropertyType`");
    return {};
  }
  // Parse literal '>'
  if (odsParser.parseGreater()) return {};
  assert(::mlir::succeeded(_result_name));
  assert(::mlir::succeeded(_result_type));
  return DomainFieldAttr::get(odsParser.getContext(),
      ::mlir::StringAttr((*_result_name)),
      ::circt::firrtl::PropertyType((*_result_type)));
}

void DomainFieldAttr::print(::mlir::AsmPrinter &odsPrinter) const {
  ::mlir::Builder odsBuilder(getContext());
  odsPrinter << "<";
  odsPrinter.printStrippedAttrOrType(getName());
  odsPrinter << ",";
  odsPrinter << ' ';
  odsPrinter.printStrippedAttrOrType(getType());
  odsPrinter << ">";
}

::mlir::StringAttr DomainFieldAttr::getName() const {
  return getImpl()->name;
}

::circt::firrtl::PropertyType DomainFieldAttr::getType() const {
  return getImpl()->type;
}


} // namespace circt::firrtl
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::firrtl::DomainFieldAttr)
namespace circt::firrtl {

namespace detail {

struct NameKindEnumAttrStorage : public ::mlir::AttributeStorage {
  using KeyTy = std::tuple<::circt::firrtl::NameKindEnum>;
  NameKindEnumAttrStorage(::circt::firrtl::NameKindEnum value) : value(std::move(value)) {}

  KeyTy getAsKey() const {
    return KeyTy(value);
  }

  bool operator==(const KeyTy &tblgenKey) const {
    return (value == std::get<0>(tblgenKey));
  }

  static ::llvm::hash_code hashKey(const KeyTy &tblgenKey) {
    return ::llvm::hash_combine(std::get<0>(tblgenKey));
  }

  static NameKindEnumAttrStorage *construct(::mlir::AttributeStorageAllocator &allocator, KeyTy &&tblgenKey) {
    auto value = std::move(std::get<0>(tblgenKey));
    return new (allocator.allocate<NameKindEnumAttrStorage>()) NameKindEnumAttrStorage(std::move(value));
  }

  ::circt::firrtl::NameKindEnum value;
};

} // namespace detail
NameKindEnumAttr NameKindEnumAttr::get(::mlir::MLIRContext *context, ::circt::firrtl::NameKindEnum value) {
  return Base::get(context, std::move(value));
}

::mlir::Attribute NameKindEnumAttr::parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType) {
  ::mlir::Builder odsBuilder(odsParser.getContext());
  ::llvm::SMLoc odsLoc = odsParser.getCurrentLocation();
  (void) odsLoc;
  ::mlir::FailureOr<::circt::firrtl::NameKindEnum> _result_value;

  // Parse variable 'value'
  _result_value = [&]() -> ::mlir::FailureOr<::circt::firrtl::NameKindEnum> {
      auto loc = odsParser.getCurrentLocation();
      std::string enumKeyword;
      if (::mlir::failed(odsParser.parseKeywordOrString(&enumKeyword)))
        return ::mlir::failure();
      auto maybeEnum = ::circt::firrtl::symbolizeNameKindEnum(enumKeyword);
      if (maybeEnum)
        return *maybeEnum;
      return {(::llvm::LogicalResult)(odsParser.emitError(loc) << "expected " << "::circt::firrtl::NameKindEnum" << " to be one of: " << "droppable_name" << ", " << "interesting_name")};
    }();
  if (::mlir::failed(_result_value)) {
    odsParser.emitError(odsParser.getCurrentLocation(), "failed to parse NameKindAttr parameter 'value' which is to be a `::circt::firrtl::NameKindEnum`");
    return {};
  }
  assert(::mlir::succeeded(_result_value));
  return NameKindEnumAttr::get(odsParser.getContext(),
      ::circt::firrtl::NameKindEnum((*_result_value)));
}

void NameKindEnumAttr::print(::mlir::AsmPrinter &odsPrinter) const {
  ::mlir::Builder odsBuilder(getContext());
  odsPrinter << stringifyNameKindEnum(getValue());
}

::circt::firrtl::NameKindEnum NameKindEnumAttr::getValue() const {
  return getImpl()->value;
}


} // namespace circt::firrtl
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::firrtl::NameKindEnumAttr)
namespace circt::firrtl {

namespace detail {

struct ConventionAttrStorage : public ::mlir::AttributeStorage {
  using KeyTy = std::tuple<::circt::firrtl::Convention>;
  ConventionAttrStorage(::circt::firrtl::Convention value) : value(std::move(value)) {}

  KeyTy getAsKey() const {
    return KeyTy(value);
  }

  bool operator==(const KeyTy &tblgenKey) const {
    return (value == std::get<0>(tblgenKey));
  }

  static ::llvm::hash_code hashKey(const KeyTy &tblgenKey) {
    return ::llvm::hash_combine(std::get<0>(tblgenKey));
  }

  static ConventionAttrStorage *construct(::mlir::AttributeStorageAllocator &allocator, KeyTy &&tblgenKey) {
    auto value = std::move(std::get<0>(tblgenKey));
    return new (allocator.allocate<ConventionAttrStorage>()) ConventionAttrStorage(std::move(value));
  }

  ::circt::firrtl::Convention value;
};

} // namespace detail
ConventionAttr ConventionAttr::get(::mlir::MLIRContext *context, ::circt::firrtl::Convention value) {
  return Base::get(context, std::move(value));
}

::mlir::Attribute ConventionAttr::parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType) {
  ::mlir::Builder odsBuilder(odsParser.getContext());
  ::llvm::SMLoc odsLoc = odsParser.getCurrentLocation();
  (void) odsLoc;
  ::mlir::FailureOr<::circt::firrtl::Convention> _result_value;

  // Parse variable 'value'
  _result_value = [&]() -> ::mlir::FailureOr<::circt::firrtl::Convention> {
      auto loc = odsParser.getCurrentLocation();
      std::string enumKeyword;
      if (::mlir::failed(odsParser.parseKeywordOrString(&enumKeyword)))
        return ::mlir::failure();
      auto maybeEnum = ::circt::firrtl::symbolizeConvention(enumKeyword);
      if (maybeEnum)
        return *maybeEnum;
      return {(::llvm::LogicalResult)(odsParser.emitError(loc) << "expected " << "::circt::firrtl::Convention" << " to be one of: " << "internal" << ", " << "scalarized")};
    }();
  if (::mlir::failed(_result_value)) {
    odsParser.emitError(odsParser.getCurrentLocation(), "failed to parse ConventionAttr parameter 'value' which is to be a `::circt::firrtl::Convention`");
    return {};
  }
  assert(::mlir::succeeded(_result_value));
  return ConventionAttr::get(odsParser.getContext(),
      ::circt::firrtl::Convention((*_result_value)));
}

void ConventionAttr::print(::mlir::AsmPrinter &odsPrinter) const {
  ::mlir::Builder odsBuilder(getContext());
  odsPrinter << stringifyConvention(getValue());
}

::circt::firrtl::Convention ConventionAttr::getValue() const {
  return getImpl()->value;
}


} // namespace circt::firrtl
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::firrtl::ConventionAttr)
namespace circt::firrtl {

namespace detail {

struct LayerConventionAttrStorage : public ::mlir::AttributeStorage {
  using KeyTy = std::tuple<::circt::firrtl::LayerConvention>;
  LayerConventionAttrStorage(::circt::firrtl::LayerConvention value) : value(std::move(value)) {}

  KeyTy getAsKey() const {
    return KeyTy(value);
  }

  bool operator==(const KeyTy &tblgenKey) const {
    return (value == std::get<0>(tblgenKey));
  }

  static ::llvm::hash_code hashKey(const KeyTy &tblgenKey) {
    return ::llvm::hash_combine(std::get<0>(tblgenKey));
  }

  static LayerConventionAttrStorage *construct(::mlir::AttributeStorageAllocator &allocator, KeyTy &&tblgenKey) {
    auto value = std::move(std::get<0>(tblgenKey));
    return new (allocator.allocate<LayerConventionAttrStorage>()) LayerConventionAttrStorage(std::move(value));
  }

  ::circt::firrtl::LayerConvention value;
};

} // namespace detail
LayerConventionAttr LayerConventionAttr::get(::mlir::MLIRContext *context, ::circt::firrtl::LayerConvention value) {
  return Base::get(context, std::move(value));
}

::mlir::Attribute LayerConventionAttr::parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType) {
  ::mlir::Builder odsBuilder(odsParser.getContext());
  ::llvm::SMLoc odsLoc = odsParser.getCurrentLocation();
  (void) odsLoc;
  ::mlir::FailureOr<::circt::firrtl::LayerConvention> _result_value;

  // Parse variable 'value'
  _result_value = [&]() -> ::mlir::FailureOr<::circt::firrtl::LayerConvention> {
      auto loc = odsParser.getCurrentLocation();
      std::string enumKeyword;
      if (::mlir::failed(odsParser.parseKeywordOrString(&enumKeyword)))
        return ::mlir::failure();
      auto maybeEnum = ::circt::firrtl::symbolizeLayerConvention(enumKeyword);
      if (maybeEnum)
        return *maybeEnum;
      return {(::llvm::LogicalResult)(odsParser.emitError(loc) << "expected " << "::circt::firrtl::LayerConvention" << " to be one of: " << "bind" << ", " << "inline")};
    }();
  if (::mlir::failed(_result_value)) {
    odsParser.emitError(odsParser.getCurrentLocation(), "failed to parse LayerConventionAttr parameter 'value' which is to be a `::circt::firrtl::LayerConvention`");
    return {};
  }
  assert(::mlir::succeeded(_result_value));
  return LayerConventionAttr::get(odsParser.getContext(),
      ::circt::firrtl::LayerConvention((*_result_value)));
}

void LayerConventionAttr::print(::mlir::AsmPrinter &odsPrinter) const {
  ::mlir::Builder odsBuilder(getContext());
  odsPrinter << stringifyLayerConvention(getValue());
}

::circt::firrtl::LayerConvention LayerConventionAttr::getValue() const {
  return getImpl()->value;
}


} // namespace circt::firrtl
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::firrtl::LayerConventionAttr)
namespace circt::firrtl {

namespace detail {

struct LayerSpecializationAttrStorage : public ::mlir::AttributeStorage {
  using KeyTy = std::tuple<::circt::firrtl::LayerSpecialization>;
  LayerSpecializationAttrStorage(::circt::firrtl::LayerSpecialization value) : value(std::move(value)) {}

  KeyTy getAsKey() const {
    return KeyTy(value);
  }

  bool operator==(const KeyTy &tblgenKey) const {
    return (value == std::get<0>(tblgenKey));
  }

  static ::llvm::hash_code hashKey(const KeyTy &tblgenKey) {
    return ::llvm::hash_combine(std::get<0>(tblgenKey));
  }

  static LayerSpecializationAttrStorage *construct(::mlir::AttributeStorageAllocator &allocator, KeyTy &&tblgenKey) {
    auto value = std::move(std::get<0>(tblgenKey));
    return new (allocator.allocate<LayerSpecializationAttrStorage>()) LayerSpecializationAttrStorage(std::move(value));
  }

  ::circt::firrtl::LayerSpecialization value;
};

} // namespace detail
LayerSpecializationAttr LayerSpecializationAttr::get(::mlir::MLIRContext *context, ::circt::firrtl::LayerSpecialization value) {
  return Base::get(context, std::move(value));
}

::mlir::Attribute LayerSpecializationAttr::parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType) {
  ::mlir::Builder odsBuilder(odsParser.getContext());
  ::llvm::SMLoc odsLoc = odsParser.getCurrentLocation();
  (void) odsLoc;
  ::mlir::FailureOr<::circt::firrtl::LayerSpecialization> _result_value;

  // Parse variable 'value'
  _result_value = [&]() -> ::mlir::FailureOr<::circt::firrtl::LayerSpecialization> {
      auto loc = odsParser.getCurrentLocation();
      std::string enumKeyword;
      if (::mlir::failed(odsParser.parseKeywordOrString(&enumKeyword)))
        return ::mlir::failure();
      auto maybeEnum = ::circt::firrtl::symbolizeLayerSpecialization(enumKeyword);
      if (maybeEnum)
        return *maybeEnum;
      return {(::llvm::LogicalResult)(odsParser.emitError(loc) << "expected " << "::circt::firrtl::LayerSpecialization" << " to be one of: " << "enable" << ", " << "disable")};
    }();
  if (::mlir::failed(_result_value)) {
    odsParser.emitError(odsParser.getCurrentLocation(), "failed to parse LayerSpecializationAttr parameter 'value' which is to be a `::circt::firrtl::LayerSpecialization`");
    return {};
  }
  assert(::mlir::succeeded(_result_value));
  return LayerSpecializationAttr::get(odsParser.getContext(),
      ::circt::firrtl::LayerSpecialization((*_result_value)));
}

void LayerSpecializationAttr::print(::mlir::AsmPrinter &odsPrinter) const {
  ::mlir::Builder odsBuilder(getContext());
  odsPrinter << stringifyLayerSpecialization(getValue());
}

::circt::firrtl::LayerSpecialization LayerSpecializationAttr::getValue() const {
  return getImpl()->value;
}


} // namespace circt::firrtl
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::firrtl::LayerSpecializationAttr)
namespace circt::firrtl {

namespace detail {

struct RUWBehaviorAttrStorage : public ::mlir::AttributeStorage {
  using KeyTy = std::tuple<::circt::firrtl::RUWBehavior>;
  RUWBehaviorAttrStorage(::circt::firrtl::RUWBehavior value) : value(std::move(value)) {}

  KeyTy getAsKey() const {
    return KeyTy(value);
  }

  bool operator==(const KeyTy &tblgenKey) const {
    return (value == std::get<0>(tblgenKey));
  }

  static ::llvm::hash_code hashKey(const KeyTy &tblgenKey) {
    return ::llvm::hash_combine(std::get<0>(tblgenKey));
  }

  static RUWBehaviorAttrStorage *construct(::mlir::AttributeStorageAllocator &allocator, KeyTy &&tblgenKey) {
    auto value = std::move(std::get<0>(tblgenKey));
    return new (allocator.allocate<RUWBehaviorAttrStorage>()) RUWBehaviorAttrStorage(std::move(value));
  }

  ::circt::firrtl::RUWBehavior value;
};

} // namespace detail
RUWBehaviorAttr RUWBehaviorAttr::get(::mlir::MLIRContext *context, ::circt::firrtl::RUWBehavior value) {
  return Base::get(context, std::move(value));
}

::mlir::Attribute RUWBehaviorAttr::parse(::mlir::AsmParser &odsParser, ::mlir::Type odsType) {
  ::mlir::Builder odsBuilder(odsParser.getContext());
  ::llvm::SMLoc odsLoc = odsParser.getCurrentLocation();
  (void) odsLoc;
  ::mlir::FailureOr<::circt::firrtl::RUWBehavior> _result_value;

  // Parse variable 'value'
  _result_value = [&]() -> ::mlir::FailureOr<::circt::firrtl::RUWBehavior> {
      auto loc = odsParser.getCurrentLocation();
      std::string enumKeyword;
      if (::mlir::failed(odsParser.parseKeywordOrString(&enumKeyword)))
        return ::mlir::failure();
      auto maybeEnum = ::circt::firrtl::symbolizeRUWBehavior(enumKeyword);
      if (maybeEnum)
        return *maybeEnum;
      return {(::llvm::LogicalResult)(odsParser.emitError(loc) << "expected " << "::circt::firrtl::RUWBehavior" << " to be one of: " << "Undefined" << ", " << "Old" << ", " << "New")};
    }();
  if (::mlir::failed(_result_value)) {
    odsParser.emitError(odsParser.getCurrentLocation(), "failed to parse RUWBehaviorAttr parameter 'value' which is to be a `::circt::firrtl::RUWBehavior`");
    return {};
  }
  assert(::mlir::succeeded(_result_value));
  return RUWBehaviorAttr::get(odsParser.getContext(),
      ::circt::firrtl::RUWBehavior((*_result_value)));
}

void RUWBehaviorAttr::print(::mlir::AsmPrinter &odsPrinter) const {
  ::mlir::Builder odsBuilder(getContext());
  odsPrinter << stringifyRUWBehavior(getValue());
}

::circt::firrtl::RUWBehavior RUWBehaviorAttr::getValue() const {
  return getImpl()->value;
}


} // namespace circt::firrtl
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::firrtl::RUWBehaviorAttr)
namespace circt::firrtl {


/// Parse an attribute registered to this dialect.
::mlir::Attribute FIRRTLDialect::parseAttribute(::mlir::DialectAsmParser &parser,
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
void FIRRTLDialect::printAttribute(::mlir::Attribute attr,
                         ::mlir::DialectAsmPrinter &printer) const {
  if (::mlir::succeeded(generatedAttributePrinter(attr, printer)))
    return;
  
}

} // namespace circt::firrtl

#endif // GET_ATTRDEF_CLASSES

