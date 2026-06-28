/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* TypeDef Definitions                                                        *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

#ifdef GET_TYPEDEF_LIST
#undef GET_TYPEDEF_LIST

::circt::rtg::SequenceType,
::circt::rtg::RandomizedSequenceType,
::circt::rtg::SetType,
::circt::rtg::BagType,
::circt::rtg::DictType,
::circt::rtg::ArrayType,
::circt::rtg::MapType,
::circt::rtg::TupleType,
::circt::rtg::StringType,
::circt::rtg::LabelType,
::circt::rtg::ImmediateType,
::circt::rtg::MemoryType,
::circt::rtg::MemoryBlockType

#endif // GET_TYPEDEF_LIST

#ifdef GET_TYPEDEF_CLASSES
#undef GET_TYPEDEF_CLASSES

static ::mlir::OptionalParseResult generatedTypeParser(::mlir::AsmParser &parser, ::llvm::StringRef *mnemonic, ::mlir::Type &value) {
  return ::mlir::AsmParser::KeywordSwitch<::mlir::OptionalParseResult>(parser)
    .Case(::circt::rtg::SequenceType::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::rtg::SequenceType::parse(parser);
      return ::mlir::success(!!value);
    })
    .Case(::circt::rtg::RandomizedSequenceType::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::rtg::RandomizedSequenceType::get(parser.getContext());
      return ::mlir::success(!!value);
    })
    .Case(::circt::rtg::SetType::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::rtg::SetType::parse(parser);
      return ::mlir::success(!!value);
    })
    .Case(::circt::rtg::BagType::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::rtg::BagType::parse(parser);
      return ::mlir::success(!!value);
    })
    .Case(::circt::rtg::DictType::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::rtg::DictType::parse(parser);
      return ::mlir::success(!!value);
    })
    .Case(::circt::rtg::ArrayType::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::rtg::ArrayType::parse(parser);
      return ::mlir::success(!!value);
    })
    .Case(::circt::rtg::MapType::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::rtg::MapType::parse(parser);
      return ::mlir::success(!!value);
    })
    .Case(::circt::rtg::TupleType::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::rtg::TupleType::parse(parser);
      return ::mlir::success(!!value);
    })
    .Case(::circt::rtg::StringType::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::rtg::StringType::parse(parser);
      return ::mlir::success(!!value);
    })
    .Case(::circt::rtg::LabelType::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::rtg::LabelType::parse(parser);
      return ::mlir::success(!!value);
    })
    .Case(::circt::rtg::ImmediateType::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::rtg::ImmediateType::parse(parser);
      return ::mlir::success(!!value);
    })
    .Case(::circt::rtg::MemoryType::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::rtg::MemoryType::parse(parser);
      return ::mlir::success(!!value);
    })
    .Case(::circt::rtg::MemoryBlockType::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::rtg::MemoryBlockType::parse(parser);
      return ::mlir::success(!!value);
    })
    .Default([&](llvm::StringRef keyword, llvm::SMLoc) {
      *mnemonic = keyword;
      return std::nullopt;
    });
}

static ::llvm::LogicalResult generatedTypePrinter(::mlir::Type def, ::mlir::AsmPrinter &printer) {
  return ::llvm::TypeSwitch<::mlir::Type, ::llvm::LogicalResult>(def)    .Case<::circt::rtg::SequenceType>([&](auto t) {
      printer << ::circt::rtg::SequenceType::getMnemonic();
t.print(printer);
      return ::mlir::success();
    })
    .Case<::circt::rtg::RandomizedSequenceType>([&](auto t) {
      printer << ::circt::rtg::RandomizedSequenceType::getMnemonic();
      return ::mlir::success();
    })
    .Case<::circt::rtg::SetType>([&](auto t) {
      printer << ::circt::rtg::SetType::getMnemonic();
t.print(printer);
      return ::mlir::success();
    })
    .Case<::circt::rtg::BagType>([&](auto t) {
      printer << ::circt::rtg::BagType::getMnemonic();
t.print(printer);
      return ::mlir::success();
    })
    .Case<::circt::rtg::DictType>([&](auto t) {
      printer << ::circt::rtg::DictType::getMnemonic();
t.print(printer);
      return ::mlir::success();
    })
    .Case<::circt::rtg::ArrayType>([&](auto t) {
      printer << ::circt::rtg::ArrayType::getMnemonic();
t.print(printer);
      return ::mlir::success();
    })
    .Case<::circt::rtg::MapType>([&](auto t) {
      printer << ::circt::rtg::MapType::getMnemonic();
t.print(printer);
      return ::mlir::success();
    })
    .Case<::circt::rtg::TupleType>([&](auto t) {
      printer << ::circt::rtg::TupleType::getMnemonic();
t.print(printer);
      return ::mlir::success();
    })
    .Case<::circt::rtg::StringType>([&](auto t) {
      printer << ::circt::rtg::StringType::getMnemonic();
t.print(printer);
      return ::mlir::success();
    })
    .Case<::circt::rtg::LabelType>([&](auto t) {
      printer << ::circt::rtg::LabelType::getMnemonic();
t.print(printer);
      return ::mlir::success();
    })
    .Case<::circt::rtg::ImmediateType>([&](auto t) {
      printer << ::circt::rtg::ImmediateType::getMnemonic();
t.print(printer);
      return ::mlir::success();
    })
    .Case<::circt::rtg::MemoryType>([&](auto t) {
      printer << ::circt::rtg::MemoryType::getMnemonic();
t.print(printer);
      return ::mlir::success();
    })
    .Case<::circt::rtg::MemoryBlockType>([&](auto t) {
      printer << ::circt::rtg::MemoryBlockType::getMnemonic();
t.print(printer);
      return ::mlir::success();
    })
    .Default([](auto) { return ::mlir::failure(); });
}

namespace circt::rtg {

namespace detail {

struct SequenceTypeStorage : public ::mlir::TypeStorage {
  using KeyTy = std::tuple<::llvm::ArrayRef<mlir::Type>>;
  SequenceTypeStorage(::llvm::ArrayRef<mlir::Type> elementTypes) : elementTypes(std::move(elementTypes)) {}

  KeyTy getAsKey() const {
    return KeyTy(elementTypes);
  }

  bool operator==(const KeyTy &tblgenKey) const {
    return (::llvm::ArrayRef<mlir::Type>(elementTypes) == ::llvm::ArrayRef<mlir::Type>(std::get<0>(tblgenKey)));
  }

  static ::llvm::hash_code hashKey(const KeyTy &tblgenKey) {
    return ::llvm::hash_combine(std::get<0>(tblgenKey));
  }

  static SequenceTypeStorage *construct(::mlir::TypeStorageAllocator &allocator, KeyTy &&tblgenKey) {
    auto elementTypes = std::move(std::get<0>(tblgenKey));
    elementTypes = allocator.copyInto(elementTypes);
    return new (allocator.allocate<SequenceTypeStorage>()) SequenceTypeStorage(std::move(elementTypes));
  }

  ::llvm::ArrayRef<mlir::Type> elementTypes;
};

} // namespace detail
SequenceType SequenceType::get(::mlir::MLIRContext *context, ::llvm::ArrayRef<mlir::Type> elementTypes) {
  return Base::get(context, std::move(elementTypes));
}

::mlir::Type SequenceType::parse(::mlir::AsmParser &odsParser) {
  ::mlir::Builder odsBuilder(odsParser.getContext());
  ::llvm::SMLoc odsLoc = odsParser.getCurrentLocation();
  (void) odsLoc;
  ::mlir::FailureOr<::llvm::SmallVector<mlir::Type>> _result_elementTypes;
  // Parse literal '<'
  if (odsParser.parseOptionalLess()) {
  } else {

    // Parse variable 'elementTypes'
    _result_elementTypes = ::mlir::FieldParser<::llvm::SmallVector<mlir::Type>>::parse(odsParser);
    if (::mlir::failed(_result_elementTypes)) {
      odsParser.emitError(odsParser.getCurrentLocation(), "failed to parse SequenceType parameter 'elementTypes' which is to be a `::llvm::ArrayRef<mlir::Type>`");
      return {};
    }
    // Parse literal '>'
    if (odsParser.parseGreater()) return {};
  }
  return SequenceType::get(odsParser.getContext(),
      ::llvm::ArrayRef<mlir::Type>((_result_elementTypes.value_or(::llvm::SmallVector<mlir::Type>()))));
}

void SequenceType::print(::mlir::AsmPrinter &odsPrinter) const {
  ::mlir::Builder odsBuilder(getContext());
  if (!(::llvm::ArrayRef<mlir::Type>(getElementTypes()) == ::llvm::ArrayRef<mlir::Type>(::llvm::SmallVector<mlir::Type>()))) {
    odsPrinter << "<";
    if (!(::llvm::ArrayRef<mlir::Type>(getElementTypes()) == ::llvm::ArrayRef<mlir::Type>(::llvm::SmallVector<mlir::Type>()))) {
      odsPrinter.printStrippedAttrOrType(getElementTypes());
    }
    odsPrinter << ">";
  } else {
  }
}

::llvm::ArrayRef<mlir::Type> SequenceType::getElementTypes() const {
  return getImpl()->elementTypes;
}


} // namespace circt::rtg
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::rtg::SequenceType)
namespace circt::rtg {


} // namespace circt::rtg
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::rtg::RandomizedSequenceType)
namespace circt::rtg {

namespace detail {

struct SetTypeStorage : public ::mlir::TypeStorage {
  using KeyTy = std::tuple<::mlir::Type>;
  SetTypeStorage(::mlir::Type elementType) : elementType(std::move(elementType)) {}

  KeyTy getAsKey() const {
    return KeyTy(elementType);
  }

  bool operator==(const KeyTy &tblgenKey) const {
    return (elementType == std::get<0>(tblgenKey));
  }

  static ::llvm::hash_code hashKey(const KeyTy &tblgenKey) {
    return ::llvm::hash_combine(std::get<0>(tblgenKey));
  }

  static SetTypeStorage *construct(::mlir::TypeStorageAllocator &allocator, KeyTy &&tblgenKey) {
    auto elementType = std::move(std::get<0>(tblgenKey));
    return new (allocator.allocate<SetTypeStorage>()) SetTypeStorage(std::move(elementType));
  }

  ::mlir::Type elementType;
};

} // namespace detail
SetType SetType::get(::mlir::MLIRContext *context, ::mlir::Type elementType) {
  return Base::get(context, std::move(elementType));
}

SetType SetType::get(::mlir::Type elementType) {
  return Base::get(elementType.getContext(), elementType);
}

::mlir::Type SetType::parse(::mlir::AsmParser &odsParser) {
  ::mlir::Builder odsBuilder(odsParser.getContext());
  ::llvm::SMLoc odsLoc = odsParser.getCurrentLocation();
  (void) odsLoc;
  ::mlir::FailureOr<::mlir::Type> _result_elementType;
  // Parse literal '<'
  if (odsParser.parseLess()) return {};

  // Parse variable 'elementType'
  _result_elementType = ::mlir::FieldParser<::mlir::Type>::parse(odsParser);
  if (::mlir::failed(_result_elementType)) {
    odsParser.emitError(odsParser.getCurrentLocation(), "failed to parse SetType parameter 'elementType' which is to be a `::mlir::Type`");
    return {};
  }
  // Parse literal '>'
  if (odsParser.parseGreater()) return {};
  assert(::mlir::succeeded(_result_elementType));
  return SetType::get(odsParser.getContext(),
      ::mlir::Type((*_result_elementType)));
}

void SetType::print(::mlir::AsmPrinter &odsPrinter) const {
  ::mlir::Builder odsBuilder(getContext());
  odsPrinter << "<";
  odsPrinter.printStrippedAttrOrType(getElementType());
  odsPrinter << ">";
}

::mlir::Type SetType::getElementType() const {
  return getImpl()->elementType;
}


} // namespace circt::rtg
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::rtg::SetType)
namespace circt::rtg {

namespace detail {

struct BagTypeStorage : public ::mlir::TypeStorage {
  using KeyTy = std::tuple<::mlir::Type>;
  BagTypeStorage(::mlir::Type elementType) : elementType(std::move(elementType)) {}

  KeyTy getAsKey() const {
    return KeyTy(elementType);
  }

  bool operator==(const KeyTy &tblgenKey) const {
    return (elementType == std::get<0>(tblgenKey));
  }

  static ::llvm::hash_code hashKey(const KeyTy &tblgenKey) {
    return ::llvm::hash_combine(std::get<0>(tblgenKey));
  }

  static BagTypeStorage *construct(::mlir::TypeStorageAllocator &allocator, KeyTy &&tblgenKey) {
    auto elementType = std::move(std::get<0>(tblgenKey));
    return new (allocator.allocate<BagTypeStorage>()) BagTypeStorage(std::move(elementType));
  }

  ::mlir::Type elementType;
};

} // namespace detail
BagType BagType::get(::mlir::MLIRContext *context, ::mlir::Type elementType) {
  return Base::get(context, std::move(elementType));
}

BagType BagType::get(::mlir::Type elementType) {
  return Base::get(elementType.getContext(), elementType);
}

::mlir::Type BagType::parse(::mlir::AsmParser &odsParser) {
  ::mlir::Builder odsBuilder(odsParser.getContext());
  ::llvm::SMLoc odsLoc = odsParser.getCurrentLocation();
  (void) odsLoc;
  ::mlir::FailureOr<::mlir::Type> _result_elementType;
  // Parse literal '<'
  if (odsParser.parseLess()) return {};

  // Parse variable 'elementType'
  _result_elementType = ::mlir::FieldParser<::mlir::Type>::parse(odsParser);
  if (::mlir::failed(_result_elementType)) {
    odsParser.emitError(odsParser.getCurrentLocation(), "failed to parse BagType parameter 'elementType' which is to be a `::mlir::Type`");
    return {};
  }
  // Parse literal '>'
  if (odsParser.parseGreater()) return {};
  assert(::mlir::succeeded(_result_elementType));
  return BagType::get(odsParser.getContext(),
      ::mlir::Type((*_result_elementType)));
}

void BagType::print(::mlir::AsmPrinter &odsPrinter) const {
  ::mlir::Builder odsBuilder(getContext());
  odsPrinter << "<";
  odsPrinter.printStrippedAttrOrType(getElementType());
  odsPrinter << ">";
}

::mlir::Type BagType::getElementType() const {
  return getImpl()->elementType;
}


} // namespace circt::rtg
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::rtg::BagType)
namespace circt::rtg {

namespace detail {

struct DictTypeStorage : public ::mlir::TypeStorage {
  using KeyTy = std::tuple<::llvm::ArrayRef<::circt::rtg::DictEntry>>;
  DictTypeStorage(::llvm::ArrayRef<::circt::rtg::DictEntry> entries) : entries(std::move(entries)) {}

  KeyTy getAsKey() const {
    return KeyTy(entries);
  }

  bool operator==(const KeyTy &tblgenKey) const {
    return (entries == std::get<0>(tblgenKey));
  }

  static ::llvm::hash_code hashKey(const KeyTy &tblgenKey) {
    return ::llvm::hash_combine(std::get<0>(tblgenKey));
  }

  static DictTypeStorage *construct(::mlir::TypeStorageAllocator &allocator, KeyTy &&tblgenKey) {
    auto entries = std::move(std::get<0>(tblgenKey));
    entries = allocator.copyInto(entries);
    return new (allocator.allocate<DictTypeStorage>()) DictTypeStorage(std::move(entries));
  }

  ::llvm::ArrayRef<::circt::rtg::DictEntry> entries;
};

} // namespace detail
DictType DictType::get(::mlir::MLIRContext *context, ::llvm::ArrayRef<::circt::rtg::DictEntry> entries) {
  return Base::get(context, std::move(entries));
}

DictType DictType::getChecked(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::mlir::MLIRContext *context, ::llvm::ArrayRef<::circt::rtg::DictEntry> entries) {
  return Base::getChecked(emitError, context, std::move(entries));
}

::llvm::LogicalResult DictType::verifyInvariants(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::llvm::ArrayRef<::circt::rtg::DictEntry> entries) {
  if (::mlir::failed(verify(emitError, entries)))
    return ::mlir::failure();
  return ::mlir::success();
}

::llvm::ArrayRef<::circt::rtg::DictEntry> DictType::getEntries() const {
  return getImpl()->entries;
}


} // namespace circt::rtg
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::rtg::DictType)
namespace circt::rtg {

namespace detail {

struct ArrayTypeStorage : public ::mlir::TypeStorage {
  using KeyTy = std::tuple<::mlir::Type>;
  ArrayTypeStorage(::mlir::Type elementType) : elementType(std::move(elementType)) {}

  KeyTy getAsKey() const {
    return KeyTy(elementType);
  }

  bool operator==(const KeyTy &tblgenKey) const {
    return (elementType == std::get<0>(tblgenKey));
  }

  static ::llvm::hash_code hashKey(const KeyTy &tblgenKey) {
    return ::llvm::hash_combine(std::get<0>(tblgenKey));
  }

  static ArrayTypeStorage *construct(::mlir::TypeStorageAllocator &allocator, KeyTy &&tblgenKey) {
    auto elementType = std::move(std::get<0>(tblgenKey));
    return new (allocator.allocate<ArrayTypeStorage>()) ArrayTypeStorage(std::move(elementType));
  }

  ::mlir::Type elementType;
};

} // namespace detail
ArrayType ArrayType::get(::mlir::MLIRContext *context, ::mlir::Type elementType) {
  return Base::get(context, std::move(elementType));
}

ArrayType ArrayType::get(mlir::Type elementType) {
  return Base::get(elementType.getContext(), elementType);
}

::mlir::Type ArrayType::parse(::mlir::AsmParser &odsParser) {
  ::mlir::Builder odsBuilder(odsParser.getContext());
  ::llvm::SMLoc odsLoc = odsParser.getCurrentLocation();
  (void) odsLoc;
  ::mlir::FailureOr<::mlir::Type> _result_elementType;
  // Parse literal '<'
  if (odsParser.parseLess()) return {};

  // Parse variable 'elementType'
  _result_elementType = ::mlir::FieldParser<::mlir::Type>::parse(odsParser);
  if (::mlir::failed(_result_elementType)) {
    odsParser.emitError(odsParser.getCurrentLocation(), "failed to parse ArrayType parameter 'elementType' which is to be a `::mlir::Type`");
    return {};
  }
  // Parse literal '>'
  if (odsParser.parseGreater()) return {};
  assert(::mlir::succeeded(_result_elementType));
  return ArrayType::get(odsParser.getContext(),
      ::mlir::Type((*_result_elementType)));
}

void ArrayType::print(::mlir::AsmPrinter &odsPrinter) const {
  ::mlir::Builder odsBuilder(getContext());
  odsPrinter << "<";
  odsPrinter.printStrippedAttrOrType(getElementType());
  odsPrinter << ">";
}

::mlir::Type ArrayType::getElementType() const {
  return getImpl()->elementType;
}


} // namespace circt::rtg
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::rtg::ArrayType)
namespace circt::rtg {

namespace detail {

struct MapTypeStorage : public ::mlir::TypeStorage {
  using KeyTy = std::tuple<::mlir::Type, ::mlir::Type>;
  MapTypeStorage(::mlir::Type keyType, ::mlir::Type valueType) : keyType(std::move(keyType)), valueType(std::move(valueType)) {}

  KeyTy getAsKey() const {
    return KeyTy(keyType, valueType);
  }

  bool operator==(const KeyTy &tblgenKey) const {
    return (keyType == std::get<0>(tblgenKey)) && (valueType == std::get<1>(tblgenKey));
  }

  static ::llvm::hash_code hashKey(const KeyTy &tblgenKey) {
    return ::llvm::hash_combine(std::get<0>(tblgenKey), std::get<1>(tblgenKey));
  }

  static MapTypeStorage *construct(::mlir::TypeStorageAllocator &allocator, KeyTy &&tblgenKey) {
    auto keyType = std::move(std::get<0>(tblgenKey));
    auto valueType = std::move(std::get<1>(tblgenKey));
    return new (allocator.allocate<MapTypeStorage>()) MapTypeStorage(std::move(keyType), std::move(valueType));
  }

  ::mlir::Type keyType;
  ::mlir::Type valueType;
};

} // namespace detail
MapType MapType::get(::mlir::MLIRContext *context, ::mlir::Type keyType, ::mlir::Type valueType) {
  return Base::get(context, std::move(keyType), std::move(valueType));
}

MapType MapType::get(::mlir::Type keyType, ::mlir::Type valueType) {
  return Base::get(keyType.getContext(), keyType, valueType);
}

::mlir::Type MapType::parse(::mlir::AsmParser &odsParser) {
  ::mlir::Builder odsBuilder(odsParser.getContext());
  ::llvm::SMLoc odsLoc = odsParser.getCurrentLocation();
  (void) odsLoc;
  ::mlir::FailureOr<::mlir::Type> _result_keyType;
  ::mlir::FailureOr<::mlir::Type> _result_valueType;
  // Parse literal '<'
  if (odsParser.parseLess()) return {};

  // Parse variable 'keyType'
  _result_keyType = ::mlir::FieldParser<::mlir::Type>::parse(odsParser);
  if (::mlir::failed(_result_keyType)) {
    odsParser.emitError(odsParser.getCurrentLocation(), "failed to parse MapType parameter 'keyType' which is to be a `::mlir::Type`");
    return {};
  }
  // Parse literal '->'
  if (odsParser.parseArrow()) return {};

  // Parse variable 'valueType'
  _result_valueType = ::mlir::FieldParser<::mlir::Type>::parse(odsParser);
  if (::mlir::failed(_result_valueType)) {
    odsParser.emitError(odsParser.getCurrentLocation(), "failed to parse MapType parameter 'valueType' which is to be a `::mlir::Type`");
    return {};
  }
  // Parse literal '>'
  if (odsParser.parseGreater()) return {};
  assert(::mlir::succeeded(_result_keyType));
  assert(::mlir::succeeded(_result_valueType));
  return MapType::get(odsParser.getContext(),
      ::mlir::Type((*_result_keyType)),
      ::mlir::Type((*_result_valueType)));
}

void MapType::print(::mlir::AsmPrinter &odsPrinter) const {
  ::mlir::Builder odsBuilder(getContext());
  odsPrinter << "<";
  odsPrinter.printStrippedAttrOrType(getKeyType());
  odsPrinter << ' ' << "->";
  odsPrinter << ' ';
  odsPrinter.printStrippedAttrOrType(getValueType());
  odsPrinter << ">";
}

::mlir::Type MapType::getKeyType() const {
  return getImpl()->keyType;
}

::mlir::Type MapType::getValueType() const {
  return getImpl()->valueType;
}


} // namespace circt::rtg
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::rtg::MapType)
namespace circt::rtg {

namespace detail {

struct TupleTypeStorage : public ::mlir::TypeStorage {
  using KeyTy = std::tuple<::llvm::ArrayRef<::mlir::Type>>;
  TupleTypeStorage(::llvm::ArrayRef<::mlir::Type> fieldTypes) : fieldTypes(std::move(fieldTypes)) {}

  KeyTy getAsKey() const {
    return KeyTy(fieldTypes);
  }

  bool operator==(const KeyTy &tblgenKey) const {
    return (::llvm::ArrayRef<::mlir::Type>(fieldTypes) == ::llvm::ArrayRef<::mlir::Type>(std::get<0>(tblgenKey)));
  }

  static ::llvm::hash_code hashKey(const KeyTy &tblgenKey) {
    return ::llvm::hash_combine(std::get<0>(tblgenKey));
  }

  static TupleTypeStorage *construct(::mlir::TypeStorageAllocator &allocator, KeyTy &&tblgenKey) {
    auto fieldTypes = std::move(std::get<0>(tblgenKey));
    fieldTypes = allocator.copyInto(fieldTypes);
    return new (allocator.allocate<TupleTypeStorage>()) TupleTypeStorage(std::move(fieldTypes));
  }

  ::llvm::ArrayRef<::mlir::Type> fieldTypes;
};

} // namespace detail
TupleType TupleType::get(::mlir::MLIRContext *context, ::llvm::ArrayRef<::mlir::Type> fieldTypes) {
  return Base::get(context, std::move(fieldTypes));
}

::mlir::Type TupleType::parse(::mlir::AsmParser &odsParser) {
  ::mlir::Builder odsBuilder(odsParser.getContext());
  ::llvm::SMLoc odsLoc = odsParser.getCurrentLocation();
  (void) odsLoc;
  ::mlir::FailureOr<::llvm::SmallVector<::mlir::Type>> _result_fieldTypes;
  // Parse literal '<'
  if (odsParser.parseOptionalLess()) {
  } else {

    // Parse variable 'fieldTypes'
    _result_fieldTypes = ::mlir::FieldParser<::llvm::SmallVector<::mlir::Type>>::parse(odsParser);
    if (::mlir::failed(_result_fieldTypes)) {
      odsParser.emitError(odsParser.getCurrentLocation(), "failed to parse TupleType parameter 'fieldTypes' which is to be a `::llvm::ArrayRef<::mlir::Type>`");
      return {};
    }
    // Parse literal '>'
    if (odsParser.parseGreater()) return {};
  }
  return TupleType::get(odsParser.getContext(),
      ::llvm::ArrayRef<::mlir::Type>((_result_fieldTypes.value_or(::llvm::SmallVector<::mlir::Type>()))));
}

void TupleType::print(::mlir::AsmPrinter &odsPrinter) const {
  ::mlir::Builder odsBuilder(getContext());
  if (!(::llvm::ArrayRef<::mlir::Type>(getFieldTypes()) == ::llvm::ArrayRef<::mlir::Type>(::llvm::SmallVector<::mlir::Type>()))) {
    odsPrinter << "<";
    if (!(::llvm::ArrayRef<::mlir::Type>(getFieldTypes()) == ::llvm::ArrayRef<::mlir::Type>(::llvm::SmallVector<::mlir::Type>()))) {
      odsPrinter.printStrippedAttrOrType(getFieldTypes());
    }
    odsPrinter << ">";
  } else {
  }
}

::llvm::ArrayRef<::mlir::Type> TupleType::getFieldTypes() const {
  return getImpl()->fieldTypes;
}


} // namespace circt::rtg
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::rtg::TupleType)
namespace circt::rtg {

::mlir::Type StringType::parse(::mlir::AsmParser &odsParser) {
  ::mlir::Builder odsBuilder(odsParser.getContext());
  ::llvm::SMLoc odsLoc = odsParser.getCurrentLocation();
  (void) odsLoc;
  return StringType::get(odsParser.getContext());
}

void StringType::print(::mlir::AsmPrinter &odsPrinter) const {
  ::mlir::Builder odsBuilder(getContext());
}


} // namespace circt::rtg
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::rtg::StringType)
namespace circt::rtg {

::mlir::Type LabelType::parse(::mlir::AsmParser &odsParser) {
  ::mlir::Builder odsBuilder(odsParser.getContext());
  ::llvm::SMLoc odsLoc = odsParser.getCurrentLocation();
  (void) odsLoc;
  return LabelType::get(odsParser.getContext());
}

void LabelType::print(::mlir::AsmPrinter &odsPrinter) const {
  ::mlir::Builder odsBuilder(getContext());
}


} // namespace circt::rtg
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::rtg::LabelType)
namespace circt::rtg {

namespace detail {

struct ImmediateTypeStorage : public ::mlir::TypeStorage {
  using KeyTy = std::tuple<uint32_t>;
  ImmediateTypeStorage(uint32_t width) : width(std::move(width)) {}

  KeyTy getAsKey() const {
    return KeyTy(width);
  }

  bool operator==(const KeyTy &tblgenKey) const {
    return (width == std::get<0>(tblgenKey));
  }

  static ::llvm::hash_code hashKey(const KeyTy &tblgenKey) {
    return ::llvm::hash_combine(std::get<0>(tblgenKey));
  }

  static ImmediateTypeStorage *construct(::mlir::TypeStorageAllocator &allocator, KeyTy &&tblgenKey) {
    auto width = std::move(std::get<0>(tblgenKey));
    return new (allocator.allocate<ImmediateTypeStorage>()) ImmediateTypeStorage(std::move(width));
  }

  uint32_t width;
};

} // namespace detail
ImmediateType ImmediateType::get(::mlir::MLIRContext *context, uint32_t width) {
  return Base::get(context, std::move(width));
}

::mlir::Type ImmediateType::parse(::mlir::AsmParser &odsParser) {
  ::mlir::Builder odsBuilder(odsParser.getContext());
  ::llvm::SMLoc odsLoc = odsParser.getCurrentLocation();
  (void) odsLoc;
  ::mlir::FailureOr<uint32_t> _result_width;
  // Parse literal '<'
  if (odsParser.parseLess()) return {};

  // Parse variable 'width'
  _result_width = ::mlir::FieldParser<uint32_t>::parse(odsParser);
  if (::mlir::failed(_result_width)) {
    odsParser.emitError(odsParser.getCurrentLocation(), "failed to parse ImmediateType parameter 'width' which is to be a `uint32_t`");
    return {};
  }
  // Parse literal '>'
  if (odsParser.parseGreater()) return {};
  assert(::mlir::succeeded(_result_width));
  return ImmediateType::get(odsParser.getContext(),
      uint32_t((*_result_width)));
}

void ImmediateType::print(::mlir::AsmPrinter &odsPrinter) const {
  ::mlir::Builder odsBuilder(getContext());
  odsPrinter << "<";
  odsPrinter.printStrippedAttrOrType(getWidth());
  odsPrinter << ">";
}

uint32_t ImmediateType::getWidth() const {
  return getImpl()->width;
}


} // namespace circt::rtg
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::rtg::ImmediateType)
namespace circt::rtg {

namespace detail {

struct MemoryTypeStorage : public ::mlir::TypeStorage {
  using KeyTy = std::tuple<uint32_t>;
  MemoryTypeStorage(uint32_t addressWidth) : addressWidth(std::move(addressWidth)) {}

  KeyTy getAsKey() const {
    return KeyTy(addressWidth);
  }

  bool operator==(const KeyTy &tblgenKey) const {
    return (addressWidth == std::get<0>(tblgenKey));
  }

  static ::llvm::hash_code hashKey(const KeyTy &tblgenKey) {
    return ::llvm::hash_combine(std::get<0>(tblgenKey));
  }

  static MemoryTypeStorage *construct(::mlir::TypeStorageAllocator &allocator, KeyTy &&tblgenKey) {
    auto addressWidth = std::move(std::get<0>(tblgenKey));
    return new (allocator.allocate<MemoryTypeStorage>()) MemoryTypeStorage(std::move(addressWidth));
  }

  uint32_t addressWidth;
};

} // namespace detail
MemoryType MemoryType::get(::mlir::MLIRContext *context, uint32_t addressWidth) {
  return Base::get(context, std::move(addressWidth));
}

::mlir::Type MemoryType::parse(::mlir::AsmParser &odsParser) {
  ::mlir::Builder odsBuilder(odsParser.getContext());
  ::llvm::SMLoc odsLoc = odsParser.getCurrentLocation();
  (void) odsLoc;
  ::mlir::FailureOr<uint32_t> _result_addressWidth;
  // Parse literal '<'
  if (odsParser.parseLess()) return {};

  // Parse variable 'addressWidth'
  _result_addressWidth = ::mlir::FieldParser<uint32_t>::parse(odsParser);
  if (::mlir::failed(_result_addressWidth)) {
    odsParser.emitError(odsParser.getCurrentLocation(), "failed to parse MemoryType parameter 'addressWidth' which is to be a `uint32_t`");
    return {};
  }
  // Parse literal '>'
  if (odsParser.parseGreater()) return {};
  assert(::mlir::succeeded(_result_addressWidth));
  return MemoryType::get(odsParser.getContext(),
      uint32_t((*_result_addressWidth)));
}

void MemoryType::print(::mlir::AsmPrinter &odsPrinter) const {
  ::mlir::Builder odsBuilder(getContext());
  odsPrinter << "<";
  odsPrinter.printStrippedAttrOrType(getAddressWidth());
  odsPrinter << ">";
}

uint32_t MemoryType::getAddressWidth() const {
  return getImpl()->addressWidth;
}


} // namespace circt::rtg
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::rtg::MemoryType)
namespace circt::rtg {

namespace detail {

struct MemoryBlockTypeStorage : public ::mlir::TypeStorage {
  using KeyTy = std::tuple<uint32_t>;
  MemoryBlockTypeStorage(uint32_t addressWidth) : addressWidth(std::move(addressWidth)) {}

  KeyTy getAsKey() const {
    return KeyTy(addressWidth);
  }

  bool operator==(const KeyTy &tblgenKey) const {
    return (addressWidth == std::get<0>(tblgenKey));
  }

  static ::llvm::hash_code hashKey(const KeyTy &tblgenKey) {
    return ::llvm::hash_combine(std::get<0>(tblgenKey));
  }

  static MemoryBlockTypeStorage *construct(::mlir::TypeStorageAllocator &allocator, KeyTy &&tblgenKey) {
    auto addressWidth = std::move(std::get<0>(tblgenKey));
    return new (allocator.allocate<MemoryBlockTypeStorage>()) MemoryBlockTypeStorage(std::move(addressWidth));
  }

  uint32_t addressWidth;
};

} // namespace detail
MemoryBlockType MemoryBlockType::get(::mlir::MLIRContext *context, uint32_t addressWidth) {
  return Base::get(context, std::move(addressWidth));
}

::mlir::Type MemoryBlockType::parse(::mlir::AsmParser &odsParser) {
  ::mlir::Builder odsBuilder(odsParser.getContext());
  ::llvm::SMLoc odsLoc = odsParser.getCurrentLocation();
  (void) odsLoc;
  ::mlir::FailureOr<uint32_t> _result_addressWidth;
  // Parse literal '<'
  if (odsParser.parseLess()) return {};

  // Parse variable 'addressWidth'
  _result_addressWidth = ::mlir::FieldParser<uint32_t>::parse(odsParser);
  if (::mlir::failed(_result_addressWidth)) {
    odsParser.emitError(odsParser.getCurrentLocation(), "failed to parse MemoryBlockType parameter 'addressWidth' which is to be a `uint32_t`");
    return {};
  }
  // Parse literal '>'
  if (odsParser.parseGreater()) return {};
  assert(::mlir::succeeded(_result_addressWidth));
  return MemoryBlockType::get(odsParser.getContext(),
      uint32_t((*_result_addressWidth)));
}

void MemoryBlockType::print(::mlir::AsmPrinter &odsPrinter) const {
  ::mlir::Builder odsBuilder(getContext());
  odsPrinter << "<";
  odsPrinter.printStrippedAttrOrType(getAddressWidth());
  odsPrinter << ">";
}

uint32_t MemoryBlockType::getAddressWidth() const {
  return getImpl()->addressWidth;
}


} // namespace circt::rtg
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::rtg::MemoryBlockType)
namespace circt::rtg {


/// Parse a type registered to this dialect.
::mlir::Type RTGDialect::parseType(::mlir::DialectAsmParser &parser) const {
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
void RTGDialect::printType(::mlir::Type type,
                    ::mlir::DialectAsmPrinter &printer) const {
  if (::mlir::succeeded(generatedTypePrinter(type, printer)))
    return;
  
}

} // namespace circt::rtg

#endif // GET_TYPEDEF_CLASSES

