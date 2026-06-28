/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* TypeDef Definitions                                                        *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

#ifdef GET_TYPEDEF_LIST
#undef GET_TYPEDEF_LIST

circt::arc::StateType,
circt::arc::MemoryType,
circt::arc::StorageType,
circt::arc::SimModelInstanceType,
circt::arc::CoroutinePCType,
circt::arc::CoroutineStateType,
circt::arc::ArrayRefType

#endif // GET_TYPEDEF_LIST

#ifdef GET_TYPEDEF_CLASSES
#undef GET_TYPEDEF_CLASSES

static ::mlir::OptionalParseResult generatedTypeParser(::mlir::AsmParser &parser, ::llvm::StringRef *mnemonic, ::mlir::Type &value) {
  return ::mlir::AsmParser::KeywordSwitch<::mlir::OptionalParseResult>(parser)
    .Case(circt::arc::StateType::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = circt::arc::StateType::parse(parser);
      return ::mlir::success(!!value);
    })
    .Case(circt::arc::MemoryType::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = circt::arc::MemoryType::parse(parser);
      return ::mlir::success(!!value);
    })
    .Case(circt::arc::StorageType::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = circt::arc::StorageType::parse(parser);
      return ::mlir::success(!!value);
    })
    .Case(circt::arc::SimModelInstanceType::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = circt::arc::SimModelInstanceType::parse(parser);
      return ::mlir::success(!!value);
    })
    .Case(circt::arc::CoroutinePCType::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = circt::arc::CoroutinePCType::parse(parser);
      return ::mlir::success(!!value);
    })
    .Case(circt::arc::CoroutineStateType::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = circt::arc::CoroutineStateType::parse(parser);
      return ::mlir::success(!!value);
    })
    .Case(circt::arc::ArrayRefType::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = circt::arc::ArrayRefType::parse(parser);
      return ::mlir::success(!!value);
    })
    .Default([&](llvm::StringRef keyword, llvm::SMLoc) {
      *mnemonic = keyword;
      return std::nullopt;
    });
}

static ::llvm::LogicalResult generatedTypePrinter(::mlir::Type def, ::mlir::AsmPrinter &printer) {
  return ::llvm::TypeSwitch<::mlir::Type, ::llvm::LogicalResult>(def)    .Case<circt::arc::StateType>([&](auto t) {
      printer << circt::arc::StateType::getMnemonic();
t.print(printer);
      return ::mlir::success();
    })
    .Case<circt::arc::MemoryType>([&](auto t) {
      printer << circt::arc::MemoryType::getMnemonic();
t.print(printer);
      return ::mlir::success();
    })
    .Case<circt::arc::StorageType>([&](auto t) {
      printer << circt::arc::StorageType::getMnemonic();
t.print(printer);
      return ::mlir::success();
    })
    .Case<circt::arc::SimModelInstanceType>([&](auto t) {
      printer << circt::arc::SimModelInstanceType::getMnemonic();
t.print(printer);
      return ::mlir::success();
    })
    .Case<circt::arc::CoroutinePCType>([&](auto t) {
      printer << circt::arc::CoroutinePCType::getMnemonic();
t.print(printer);
      return ::mlir::success();
    })
    .Case<circt::arc::CoroutineStateType>([&](auto t) {
      printer << circt::arc::CoroutineStateType::getMnemonic();
t.print(printer);
      return ::mlir::success();
    })
    .Case<circt::arc::ArrayRefType>([&](auto t) {
      printer << circt::arc::ArrayRefType::getMnemonic();
t.print(printer);
      return ::mlir::success();
    })
    .Default([](auto) { return ::mlir::failure(); });
}

namespace circt::arc {

namespace detail {

struct StateTypeStorage : public ::mlir::TypeStorage {
  using KeyTy = std::tuple<::mlir::Type>;
  StateTypeStorage(::mlir::Type type) : type(std::move(type)) {}

  KeyTy getAsKey() const {
    return KeyTy(type);
  }

  bool operator==(const KeyTy &tblgenKey) const {
    return (type == std::get<0>(tblgenKey));
  }

  static ::llvm::hash_code hashKey(const KeyTy &tblgenKey) {
    return ::llvm::hash_combine(std::get<0>(tblgenKey));
  }

  static StateTypeStorage *construct(::mlir::TypeStorageAllocator &allocator, KeyTy &&tblgenKey) {
    auto type = std::move(std::get<0>(tblgenKey));
    return new (allocator.allocate<StateTypeStorage>()) StateTypeStorage(std::move(type));
  }

  ::mlir::Type type;
};

} // namespace detail
StateType StateType::get(::mlir::MLIRContext *context, ::mlir::Type type) {
  return Base::get(context, std::move(type));
}

StateType StateType::getChecked(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::mlir::MLIRContext *context, ::mlir::Type type) {
  return Base::getChecked(emitError, context, std::move(type));
}

StateType StateType::get(::mlir::Type type) {
  return Base::get(type.getContext(), type);
}

StateType StateType::getChecked(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::mlir::Type type) {
  return Base::getChecked(emitError, type.getContext(), type);
}

::llvm::LogicalResult StateType::verifyInvariants(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::mlir::Type type) {
  if (::mlir::failed(verify(emitError, type)))
    return ::mlir::failure();
  return ::mlir::success();
}

::mlir::Type StateType::parse(::mlir::AsmParser &odsParser) {
  ::mlir::Builder odsBuilder(odsParser.getContext());
  ::llvm::SMLoc odsLoc = odsParser.getCurrentLocation();
  (void) odsLoc;
  ::mlir::FailureOr<::mlir::Type> _result_type;
  // Parse literal '<'
  if (odsParser.parseLess()) return {};

  // Parse variable 'type'
  _result_type = ::mlir::FieldParser<::mlir::Type>::parse(odsParser);
  if (::mlir::failed(_result_type)) {
    odsParser.emitError(odsParser.getCurrentLocation(), "failed to parse StateType parameter 'type' which is to be a `::mlir::Type`");
    return {};
  }
  // Parse literal '>'
  if (odsParser.parseGreater()) return {};
  assert(::mlir::succeeded(_result_type));
  return odsParser.getChecked<StateType>(odsLoc, odsParser.getContext(),
      ::mlir::Type((*_result_type)));
}

void StateType::print(::mlir::AsmPrinter &odsPrinter) const {
  ::mlir::Builder odsBuilder(getContext());
  odsPrinter << "<";
  odsPrinter.printStrippedAttrOrType(getType());
  odsPrinter << ">";
}

::mlir::Type StateType::getType() const {
  return getImpl()->type;
}


} // namespace circt::arc
MLIR_DEFINE_EXPLICIT_TYPE_ID(circt::arc::StateType)
namespace circt::arc {

namespace detail {

struct MemoryTypeStorage : public ::mlir::TypeStorage {
  using KeyTy = std::tuple<unsigned, ::mlir::IntegerType, ::mlir::IntegerType>;
  MemoryTypeStorage(unsigned numWords, ::mlir::IntegerType wordType, ::mlir::IntegerType addressType) : numWords(std::move(numWords)), wordType(std::move(wordType)), addressType(std::move(addressType)) {}

  KeyTy getAsKey() const {
    return KeyTy(numWords, wordType, addressType);
  }

  bool operator==(const KeyTy &tblgenKey) const {
    return (numWords == std::get<0>(tblgenKey)) && (wordType == std::get<1>(tblgenKey)) && (addressType == std::get<2>(tblgenKey));
  }

  static ::llvm::hash_code hashKey(const KeyTy &tblgenKey) {
    return ::llvm::hash_combine(std::get<0>(tblgenKey), std::get<1>(tblgenKey), std::get<2>(tblgenKey));
  }

  static MemoryTypeStorage *construct(::mlir::TypeStorageAllocator &allocator, KeyTy &&tblgenKey) {
    auto numWords = std::move(std::get<0>(tblgenKey));
    auto wordType = std::move(std::get<1>(tblgenKey));
    auto addressType = std::move(std::get<2>(tblgenKey));
    return new (allocator.allocate<MemoryTypeStorage>()) MemoryTypeStorage(std::move(numWords), std::move(wordType), std::move(addressType));
  }

  unsigned numWords;
  ::mlir::IntegerType wordType;
  ::mlir::IntegerType addressType;
};

} // namespace detail
MemoryType MemoryType::get(::mlir::MLIRContext *context, unsigned numWords, ::mlir::IntegerType wordType, ::mlir::IntegerType addressType) {
  return Base::get(context, std::move(numWords), std::move(wordType), std::move(addressType));
}

::mlir::Type MemoryType::parse(::mlir::AsmParser &odsParser) {
  ::mlir::Builder odsBuilder(odsParser.getContext());
  ::llvm::SMLoc odsLoc = odsParser.getCurrentLocation();
  (void) odsLoc;
  ::mlir::FailureOr<unsigned> _result_numWords;
  ::mlir::FailureOr<::mlir::IntegerType> _result_wordType;
  ::mlir::FailureOr<::mlir::IntegerType> _result_addressType;
  // Parse literal '<'
  if (odsParser.parseLess()) return {};

  // Parse variable 'numWords'
  _result_numWords = ::mlir::FieldParser<unsigned>::parse(odsParser);
  if (::mlir::failed(_result_numWords)) {
    odsParser.emitError(odsParser.getCurrentLocation(), "failed to parse MemoryType parameter 'numWords' which is to be a `unsigned`");
    return {};
  }
  // Parse literal 'x'
  if (odsParser.parseKeyword("x")) return {};

  // Parse variable 'wordType'
  _result_wordType = ::mlir::FieldParser<::mlir::IntegerType>::parse(odsParser);
  if (::mlir::failed(_result_wordType)) {
    odsParser.emitError(odsParser.getCurrentLocation(), "failed to parse MemoryType parameter 'wordType' which is to be a `::mlir::IntegerType`");
    return {};
  }
  // Parse literal ','
  if (odsParser.parseComma()) return {};

  // Parse variable 'addressType'
  _result_addressType = ::mlir::FieldParser<::mlir::IntegerType>::parse(odsParser);
  if (::mlir::failed(_result_addressType)) {
    odsParser.emitError(odsParser.getCurrentLocation(), "failed to parse MemoryType parameter 'addressType' which is to be a `::mlir::IntegerType`");
    return {};
  }
  // Parse literal '>'
  if (odsParser.parseGreater()) return {};
  assert(::mlir::succeeded(_result_numWords));
  assert(::mlir::succeeded(_result_wordType));
  assert(::mlir::succeeded(_result_addressType));
  return MemoryType::get(odsParser.getContext(),
      unsigned((*_result_numWords)),
      ::mlir::IntegerType((*_result_wordType)),
      ::mlir::IntegerType((*_result_addressType)));
}

void MemoryType::print(::mlir::AsmPrinter &odsPrinter) const {
  ::mlir::Builder odsBuilder(getContext());
  odsPrinter << "<";
  odsPrinter.printStrippedAttrOrType(getNumWords());
  odsPrinter << ' ' << "x";
  odsPrinter << ' ';
  odsPrinter.printStrippedAttrOrType(getWordType());
  odsPrinter << ",";
  odsPrinter << ' ';
  odsPrinter.printStrippedAttrOrType(getAddressType());
  odsPrinter << ">";
}

unsigned MemoryType::getNumWords() const {
  return getImpl()->numWords;
}

::mlir::IntegerType MemoryType::getWordType() const {
  return getImpl()->wordType;
}

::mlir::IntegerType MemoryType::getAddressType() const {
  return getImpl()->addressType;
}


} // namespace circt::arc
MLIR_DEFINE_EXPLICIT_TYPE_ID(circt::arc::MemoryType)
namespace circt::arc {

namespace detail {

struct StorageTypeStorage : public ::mlir::TypeStorage {
  using KeyTy = std::tuple<unsigned>;
  StorageTypeStorage(unsigned size) : size(std::move(size)) {}

  KeyTy getAsKey() const {
    return KeyTy(size);
  }

  bool operator==(const KeyTy &tblgenKey) const {
    return (size == std::get<0>(tblgenKey));
  }

  static ::llvm::hash_code hashKey(const KeyTy &tblgenKey) {
    return ::llvm::hash_combine(std::get<0>(tblgenKey));
  }

  static StorageTypeStorage *construct(::mlir::TypeStorageAllocator &allocator, KeyTy &&tblgenKey) {
    auto size = std::move(std::get<0>(tblgenKey));
    return new (allocator.allocate<StorageTypeStorage>()) StorageTypeStorage(std::move(size));
  }

  unsigned size;
};

} // namespace detail
StorageType StorageType::get(::mlir::MLIRContext *context, unsigned size) {
  return Base::get(context, std::move(size));
}

::mlir::Type StorageType::parse(::mlir::AsmParser &odsParser) {
  ::mlir::Builder odsBuilder(odsParser.getContext());
  ::llvm::SMLoc odsLoc = odsParser.getCurrentLocation();
  (void) odsLoc;
  ::mlir::FailureOr<unsigned> _result_size;
  // Parse literal '<'
  if (odsParser.parseOptionalLess()) {
  } else {

    // Parse variable 'size'
    _result_size = ::mlir::FieldParser<unsigned>::parse(odsParser);
    if (::mlir::failed(_result_size)) {
      odsParser.emitError(odsParser.getCurrentLocation(), "failed to parse StorageType parameter 'size' which is to be a `unsigned`");
      return {};
    }
    // Parse literal '>'
    if (odsParser.parseGreater()) return {};
  }
  return StorageType::get(odsParser.getContext(),
      unsigned((_result_size.value_or(unsigned()))));
}

void StorageType::print(::mlir::AsmPrinter &odsPrinter) const {
  ::mlir::Builder odsBuilder(getContext());
  if (!(getSize() == unsigned())) {
    odsPrinter << "<";
    if (!(getSize() == unsigned())) {
      odsPrinter.printStrippedAttrOrType(getSize());
    }
    odsPrinter << ">";
  } else {
  }
}

unsigned StorageType::getSize() const {
  return getImpl()->size;
}


} // namespace circt::arc
MLIR_DEFINE_EXPLICIT_TYPE_ID(circt::arc::StorageType)
namespace circt::arc {

namespace detail {

struct SimModelInstanceTypeStorage : public ::mlir::TypeStorage {
  using KeyTy = std::tuple<mlir::FlatSymbolRefAttr>;
  SimModelInstanceTypeStorage(mlir::FlatSymbolRefAttr model) : model(std::move(model)) {}

  KeyTy getAsKey() const {
    return KeyTy(model);
  }

  bool operator==(const KeyTy &tblgenKey) const {
    return (model == std::get<0>(tblgenKey));
  }

  static ::llvm::hash_code hashKey(const KeyTy &tblgenKey) {
    return ::llvm::hash_combine(std::get<0>(tblgenKey));
  }

  static SimModelInstanceTypeStorage *construct(::mlir::TypeStorageAllocator &allocator, KeyTy &&tblgenKey) {
    auto model = std::move(std::get<0>(tblgenKey));
    return new (allocator.allocate<SimModelInstanceTypeStorage>()) SimModelInstanceTypeStorage(std::move(model));
  }

  mlir::FlatSymbolRefAttr model;
};

} // namespace detail
SimModelInstanceType SimModelInstanceType::get(::mlir::MLIRContext *context, mlir::FlatSymbolRefAttr model) {
  return Base::get(context, std::move(model));
}

::mlir::Type SimModelInstanceType::parse(::mlir::AsmParser &odsParser) {
  ::mlir::Builder odsBuilder(odsParser.getContext());
  ::llvm::SMLoc odsLoc = odsParser.getCurrentLocation();
  (void) odsLoc;
  ::mlir::FailureOr<mlir::FlatSymbolRefAttr> _result_model;
  // Parse literal '<'
  if (odsParser.parseLess()) return {};

  // Parse variable 'model'
  _result_model = ::mlir::FieldParser<mlir::FlatSymbolRefAttr>::parse(odsParser);
  if (::mlir::failed(_result_model)) {
    odsParser.emitError(odsParser.getCurrentLocation(), "failed to parse SimModelInstance parameter 'model' which is to be a `mlir::FlatSymbolRefAttr`");
    return {};
  }
  // Parse literal '>'
  if (odsParser.parseGreater()) return {};
  assert(::mlir::succeeded(_result_model));
  return SimModelInstanceType::get(odsParser.getContext(),
      mlir::FlatSymbolRefAttr((*_result_model)));
}

void SimModelInstanceType::print(::mlir::AsmPrinter &odsPrinter) const {
  ::mlir::Builder odsBuilder(getContext());
  odsPrinter << "<";
  odsPrinter.printStrippedAttrOrType(getModel());
  odsPrinter << ">";
}

mlir::FlatSymbolRefAttr SimModelInstanceType::getModel() const {
  return getImpl()->model;
}


} // namespace circt::arc
MLIR_DEFINE_EXPLICIT_TYPE_ID(circt::arc::SimModelInstanceType)
namespace circt::arc {

namespace detail {

struct CoroutinePCTypeStorage : public ::mlir::TypeStorage {
  using KeyTy = std::tuple<mlir::FlatSymbolRefAttr>;
  CoroutinePCTypeStorage(mlir::FlatSymbolRefAttr coroutine) : coroutine(std::move(coroutine)) {}

  KeyTy getAsKey() const {
    return KeyTy(coroutine);
  }

  bool operator==(const KeyTy &tblgenKey) const {
    return (coroutine == std::get<0>(tblgenKey));
  }

  static ::llvm::hash_code hashKey(const KeyTy &tblgenKey) {
    return ::llvm::hash_combine(std::get<0>(tblgenKey));
  }

  static CoroutinePCTypeStorage *construct(::mlir::TypeStorageAllocator &allocator, KeyTy &&tblgenKey) {
    auto coroutine = std::move(std::get<0>(tblgenKey));
    return new (allocator.allocate<CoroutinePCTypeStorage>()) CoroutinePCTypeStorage(std::move(coroutine));
  }

  mlir::FlatSymbolRefAttr coroutine;
};

} // namespace detail
CoroutinePCType CoroutinePCType::get(::mlir::MLIRContext *context, mlir::FlatSymbolRefAttr coroutine) {
  return Base::get(context, std::move(coroutine));
}

::mlir::Type CoroutinePCType::parse(::mlir::AsmParser &odsParser) {
  ::mlir::Builder odsBuilder(odsParser.getContext());
  ::llvm::SMLoc odsLoc = odsParser.getCurrentLocation();
  (void) odsLoc;
  ::mlir::FailureOr<mlir::FlatSymbolRefAttr> _result_coroutine;
  // Parse literal '<'
  if (odsParser.parseLess()) return {};

  // Parse variable 'coroutine'
  _result_coroutine = ::mlir::FieldParser<mlir::FlatSymbolRefAttr>::parse(odsParser);
  if (::mlir::failed(_result_coroutine)) {
    odsParser.emitError(odsParser.getCurrentLocation(), "failed to parse CoroutinePCType parameter 'coroutine' which is to be a `mlir::FlatSymbolRefAttr`");
    return {};
  }
  // Parse literal '>'
  if (odsParser.parseGreater()) return {};
  assert(::mlir::succeeded(_result_coroutine));
  return CoroutinePCType::get(odsParser.getContext(),
      mlir::FlatSymbolRefAttr((*_result_coroutine)));
}

void CoroutinePCType::print(::mlir::AsmPrinter &odsPrinter) const {
  ::mlir::Builder odsBuilder(getContext());
  odsPrinter << "<";
  odsPrinter.printStrippedAttrOrType(getCoroutine());
  odsPrinter << ">";
}

mlir::FlatSymbolRefAttr CoroutinePCType::getCoroutine() const {
  return getImpl()->coroutine;
}


} // namespace circt::arc
MLIR_DEFINE_EXPLICIT_TYPE_ID(circt::arc::CoroutinePCType)
namespace circt::arc {

namespace detail {

struct CoroutineStateTypeStorage : public ::mlir::TypeStorage {
  using KeyTy = std::tuple<mlir::FlatSymbolRefAttr>;
  CoroutineStateTypeStorage(mlir::FlatSymbolRefAttr coroutine) : coroutine(std::move(coroutine)) {}

  KeyTy getAsKey() const {
    return KeyTy(coroutine);
  }

  bool operator==(const KeyTy &tblgenKey) const {
    return (coroutine == std::get<0>(tblgenKey));
  }

  static ::llvm::hash_code hashKey(const KeyTy &tblgenKey) {
    return ::llvm::hash_combine(std::get<0>(tblgenKey));
  }

  static CoroutineStateTypeStorage *construct(::mlir::TypeStorageAllocator &allocator, KeyTy &&tblgenKey) {
    auto coroutine = std::move(std::get<0>(tblgenKey));
    return new (allocator.allocate<CoroutineStateTypeStorage>()) CoroutineStateTypeStorage(std::move(coroutine));
  }

  mlir::FlatSymbolRefAttr coroutine;
};

} // namespace detail
CoroutineStateType CoroutineStateType::get(::mlir::MLIRContext *context, mlir::FlatSymbolRefAttr coroutine) {
  return Base::get(context, std::move(coroutine));
}

::mlir::Type CoroutineStateType::parse(::mlir::AsmParser &odsParser) {
  ::mlir::Builder odsBuilder(odsParser.getContext());
  ::llvm::SMLoc odsLoc = odsParser.getCurrentLocation();
  (void) odsLoc;
  ::mlir::FailureOr<mlir::FlatSymbolRefAttr> _result_coroutine;
  // Parse literal '<'
  if (odsParser.parseLess()) return {};

  // Parse variable 'coroutine'
  _result_coroutine = ::mlir::FieldParser<mlir::FlatSymbolRefAttr>::parse(odsParser);
  if (::mlir::failed(_result_coroutine)) {
    odsParser.emitError(odsParser.getCurrentLocation(), "failed to parse CoroutineStateType parameter 'coroutine' which is to be a `mlir::FlatSymbolRefAttr`");
    return {};
  }
  // Parse literal '>'
  if (odsParser.parseGreater()) return {};
  assert(::mlir::succeeded(_result_coroutine));
  return CoroutineStateType::get(odsParser.getContext(),
      mlir::FlatSymbolRefAttr((*_result_coroutine)));
}

void CoroutineStateType::print(::mlir::AsmPrinter &odsPrinter) const {
  ::mlir::Builder odsBuilder(getContext());
  odsPrinter << "<";
  odsPrinter.printStrippedAttrOrType(getCoroutine());
  odsPrinter << ">";
}

mlir::FlatSymbolRefAttr CoroutineStateType::getCoroutine() const {
  return getImpl()->coroutine;
}


} // namespace circt::arc
MLIR_DEFINE_EXPLICIT_TYPE_ID(circt::arc::CoroutineStateType)
namespace circt::arc {

namespace detail {

struct ArrayRefTypeStorage : public ::mlir::TypeStorage {
  using KeyTy = std::tuple<::mlir::Type, uint64_t>;
  ArrayRefTypeStorage(::mlir::Type elementType, uint64_t size) : elementType(std::move(elementType)), size(std::move(size)) {}

  KeyTy getAsKey() const {
    return KeyTy(elementType, size);
  }

  bool operator==(const KeyTy &tblgenKey) const {
    return (elementType == std::get<0>(tblgenKey)) && (size == std::get<1>(tblgenKey));
  }

  static ::llvm::hash_code hashKey(const KeyTy &tblgenKey) {
    return ::llvm::hash_combine(std::get<0>(tblgenKey), std::get<1>(tblgenKey));
  }

  static ArrayRefTypeStorage *construct(::mlir::TypeStorageAllocator &allocator, KeyTy &&tblgenKey) {
    auto elementType = std::move(std::get<0>(tblgenKey));
    auto size = std::move(std::get<1>(tblgenKey));
    return new (allocator.allocate<ArrayRefTypeStorage>()) ArrayRefTypeStorage(std::move(elementType), std::move(size));
  }

  ::mlir::Type elementType;
  uint64_t size;
};

} // namespace detail
ArrayRefType ArrayRefType::get(::mlir::MLIRContext *context, ::mlir::Type elementType, uint64_t size) {
  return Base::get(context, std::move(elementType), std::move(size));
}

ArrayRefType ArrayRefType::getChecked(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::mlir::MLIRContext *context, ::mlir::Type elementType, uint64_t size) {
  return Base::getChecked(emitError, context, std::move(elementType), std::move(size));
}

ArrayRefType ArrayRefType::get(Type elementType, uint64_t size) {
  auto *ctx = elementType.getContext();
  return Base::get(ctx, elementType, size);
}

ArrayRefType ArrayRefType::getChecked(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, Type elementType, uint64_t size) {
  auto *ctx = elementType.getContext();
  return Base::getChecked(emitError, ctx, elementType, size);
}

::llvm::LogicalResult ArrayRefType::verifyInvariants(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::mlir::Type elementType, uint64_t size) {
  if (::mlir::failed(verify(emitError, elementType, size)))
    return ::mlir::failure();
  return ::mlir::success();
}

::mlir::Type ArrayRefType::parse(::mlir::AsmParser &odsParser) {
  ::mlir::Builder odsBuilder(odsParser.getContext());
  ::llvm::SMLoc odsLoc = odsParser.getCurrentLocation();
  (void) odsLoc;
  ::mlir::FailureOr<::mlir::Type> _result_elementType;
  ::mlir::FailureOr<uint64_t> _result_size;
  // Parse literal '<'
  if (odsParser.parseLess()) return {};

  // Parse variable 'size'
  _result_size = ::mlir::FieldParser<uint64_t>::parse(odsParser);
  if (::mlir::failed(_result_size)) {
    odsParser.emitError(odsParser.getCurrentLocation(), "failed to parse ArrayRefType parameter 'size' which is to be a `uint64_t`");
    return {};
  }
  {
    auto odsCustomLoc = odsParser.getCurrentLocation();
    (void)odsCustomLoc;
    auto odsCustomResult = parseXInDimList(odsParser,
      ::mlir::detail::unwrapForCustomParse(_result_elementType));
    if (::mlir::failed(odsCustomResult)) return {};
    if (::mlir::failed(_result_elementType)) {
      odsParser.emitError(odsCustomLoc, "custom parser failed to parse parameter 'elementType'");
      return {};
    }
  }
  // Parse literal '>'
  if (odsParser.parseGreater()) return {};
  assert(::mlir::succeeded(_result_elementType));
  assert(::mlir::succeeded(_result_size));
  return odsParser.getChecked<ArrayRefType>(odsLoc, odsParser.getContext(),
      ::mlir::Type((*_result_elementType)),
      uint64_t((*_result_size)));
}

void ArrayRefType::print(::mlir::AsmPrinter &odsPrinter) const {
  ::mlir::Builder odsBuilder(getContext());
  odsPrinter << "<";
  odsPrinter.printStrippedAttrOrType(getSize());
  printXInDimList(odsPrinter,
    getElementType());
  odsPrinter << ">";
}

::mlir::Type ArrayRefType::getElementType() const {
  return getImpl()->elementType;
}

uint64_t ArrayRefType::getSize() const {
  return getImpl()->size;
}


} // namespace circt::arc
MLIR_DEFINE_EXPLICIT_TYPE_ID(circt::arc::ArrayRefType)
namespace circt::arc {


/// Parse a type registered to this dialect.
::mlir::Type ArcDialect::parseType(::mlir::DialectAsmParser &parser) const {
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
void ArcDialect::printType(::mlir::Type type,
                    ::mlir::DialectAsmPrinter &printer) const {
  if (::mlir::succeeded(generatedTypePrinter(type, printer)))
    return;
  
}

} // namespace circt::arc

#endif // GET_TYPEDEF_CLASSES

