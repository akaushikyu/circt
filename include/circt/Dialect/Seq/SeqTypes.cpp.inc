/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* TypeDef Definitions                                                        *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

#ifdef GET_TYPEDEF_LIST
#undef GET_TYPEDEF_LIST

::circt::seq::HLMemType,
::circt::seq::FirMemType,
::circt::seq::ClockType,
::circt::seq::ImmutableType

#endif // GET_TYPEDEF_LIST

#ifdef GET_TYPEDEF_CLASSES
#undef GET_TYPEDEF_CLASSES

static ::mlir::OptionalParseResult generatedTypeParser(::mlir::AsmParser &parser, ::llvm::StringRef *mnemonic, ::mlir::Type &value) {
  return ::mlir::AsmParser::KeywordSwitch<::mlir::OptionalParseResult>(parser)
    .Case(::circt::seq::HLMemType::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::seq::HLMemType::parse(parser);
      return ::mlir::success(!!value);
    })
    .Case(::circt::seq::FirMemType::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::seq::FirMemType::parse(parser);
      return ::mlir::success(!!value);
    })
    .Case(::circt::seq::ClockType::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::seq::ClockType::get(parser.getContext());
      return ::mlir::success(!!value);
    })
    .Case(::circt::seq::ImmutableType::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::seq::ImmutableType::parse(parser);
      return ::mlir::success(!!value);
    })
    .Default([&](llvm::StringRef keyword, llvm::SMLoc) {
      *mnemonic = keyword;
      return std::nullopt;
    });
}

static ::llvm::LogicalResult generatedTypePrinter(::mlir::Type def, ::mlir::AsmPrinter &printer) {
  return ::llvm::TypeSwitch<::mlir::Type, ::llvm::LogicalResult>(def)    .Case<::circt::seq::HLMemType>([&](auto t) {
      printer << ::circt::seq::HLMemType::getMnemonic();
t.print(printer);
      return ::mlir::success();
    })
    .Case<::circt::seq::FirMemType>([&](auto t) {
      printer << ::circt::seq::FirMemType::getMnemonic();
t.print(printer);
      return ::mlir::success();
    })
    .Case<::circt::seq::ClockType>([&](auto t) {
      printer << ::circt::seq::ClockType::getMnemonic();
      return ::mlir::success();
    })
    .Case<::circt::seq::ImmutableType>([&](auto t) {
      printer << ::circt::seq::ImmutableType::getMnemonic();
t.print(printer);
      return ::mlir::success();
    })
    .Default([](auto) { return ::mlir::failure(); });
}

namespace circt::seq {

namespace detail {

struct HLMemTypeStorage : public ::mlir::TypeStorage {
  using KeyTy = std::tuple<::llvm::ArrayRef<int64_t>, Type>;
  HLMemTypeStorage(::llvm::ArrayRef<int64_t> shape, Type elementType) : shape(std::move(shape)), elementType(std::move(elementType)) {}

  KeyTy getAsKey() const {
    return KeyTy(shape, elementType);
  }

  bool operator==(const KeyTy &tblgenKey) const {
    return (shape == std::get<0>(tblgenKey)) && (elementType == std::get<1>(tblgenKey));
  }

  static ::llvm::hash_code hashKey(const KeyTy &tblgenKey) {
    return ::llvm::hash_combine(std::get<0>(tblgenKey), std::get<1>(tblgenKey));
  }

  static HLMemTypeStorage *construct(::mlir::TypeStorageAllocator &allocator, KeyTy &&tblgenKey) {
    auto shape = std::move(std::get<0>(tblgenKey));
    auto elementType = std::move(std::get<1>(tblgenKey));
    shape = allocator.copyInto(shape);
    return new (allocator.allocate<HLMemTypeStorage>()) HLMemTypeStorage(std::move(shape), std::move(elementType));
  }

  ::llvm::ArrayRef<int64_t> shape;
  Type elementType;
};

} // namespace detail
HLMemType HLMemType::get(::mlir::MLIRContext *context, ::llvm::ArrayRef<int64_t> shape, Type elementType) {
  return Base::get(context, std::move(shape), std::move(elementType));
}

HLMemType HLMemType::getChecked(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::mlir::MLIRContext *context, ::llvm::ArrayRef<int64_t> shape, Type elementType) {
  return Base::getChecked(emitError, context, std::move(shape), std::move(elementType));
}

::llvm::LogicalResult HLMemType::verifyInvariants(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::llvm::ArrayRef<int64_t> shape, Type elementType) {
  if (::mlir::failed(verify(emitError, shape, elementType)))
    return ::mlir::failure();
  return ::mlir::success();
}

::llvm::ArrayRef<int64_t> HLMemType::getShape() const {
  return getImpl()->shape;
}

Type HLMemType::getElementType() const {
  return getImpl()->elementType;
}


} // namespace circt::seq
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::seq::HLMemType)
namespace circt::seq {

namespace detail {

struct FirMemTypeStorage : public ::mlir::TypeStorage {
  using KeyTy = std::tuple<uint64_t, uint32_t, std::optional<uint32_t>>;
  FirMemTypeStorage(uint64_t depth, uint32_t width, std::optional<uint32_t> maskWidth) : depth(std::move(depth)), width(std::move(width)), maskWidth(std::move(maskWidth)) {}

  KeyTy getAsKey() const {
    return KeyTy(depth, width, maskWidth);
  }

  bool operator==(const KeyTy &tblgenKey) const {
    return (depth == std::get<0>(tblgenKey)) && (width == std::get<1>(tblgenKey)) && (maskWidth == std::get<2>(tblgenKey));
  }

  static ::llvm::hash_code hashKey(const KeyTy &tblgenKey) {
    return ::llvm::hash_combine(std::get<0>(tblgenKey), std::get<1>(tblgenKey), std::get<2>(tblgenKey));
  }

  static FirMemTypeStorage *construct(::mlir::TypeStorageAllocator &allocator, KeyTy &&tblgenKey) {
    auto depth = std::move(std::get<0>(tblgenKey));
    auto width = std::move(std::get<1>(tblgenKey));
    auto maskWidth = std::move(std::get<2>(tblgenKey));
    return new (allocator.allocate<FirMemTypeStorage>()) FirMemTypeStorage(std::move(depth), std::move(width), std::move(maskWidth));
  }

  uint64_t depth;
  uint32_t width;
  std::optional<uint32_t> maskWidth;
};

} // namespace detail
FirMemType FirMemType::get(::mlir::MLIRContext *context, uint64_t depth, uint32_t width, std::optional<uint32_t> maskWidth) {
  return Base::get(context, std::move(depth), std::move(width), std::move(maskWidth));
}

::mlir::Type FirMemType::parse(::mlir::AsmParser &odsParser) {
  ::mlir::Builder odsBuilder(odsParser.getContext());
  ::llvm::SMLoc odsLoc = odsParser.getCurrentLocation();
  (void) odsLoc;
  ::mlir::FailureOr<uint64_t> _result_depth;
  ::mlir::FailureOr<uint32_t> _result_width;
  ::mlir::FailureOr<std::optional<uint32_t>> _result_maskWidth;
  // Parse literal '<'
  if (odsParser.parseLess()) return {};

  // Parse variable 'depth'
  _result_depth = ::mlir::FieldParser<uint64_t>::parse(odsParser);
  if (::mlir::failed(_result_depth)) {
    odsParser.emitError(odsParser.getCurrentLocation(), "failed to parse FirMemType parameter 'depth' which is to be a `uint64_t`");
    return {};
  }
  // Parse literal 'x'
  if (odsParser.parseKeyword("x")) return {};

  // Parse variable 'width'
  _result_width = ::mlir::FieldParser<uint32_t>::parse(odsParser);
  if (::mlir::failed(_result_width)) {
    odsParser.emitError(odsParser.getCurrentLocation(), "failed to parse FirMemType parameter 'width' which is to be a `uint32_t`");
    return {};
  }
  // Parse literal ','
  if (odsParser.parseOptionalComma()) {
  } else {
    // Parse literal 'mask'
    if (odsParser.parseKeyword("mask")) return {};

    // Parse variable 'maskWidth'
    _result_maskWidth = ::mlir::FieldParser<std::optional<uint32_t>>::parse(odsParser);
    if (::mlir::failed(_result_maskWidth)) {
      odsParser.emitError(odsParser.getCurrentLocation(), "failed to parse FirMemType parameter 'maskWidth' which is to be a `std::optional<uint32_t>`");
      return {};
    }
  }
  // Parse literal '>'
  if (odsParser.parseGreater()) return {};
  assert(::mlir::succeeded(_result_depth));
  assert(::mlir::succeeded(_result_width));
  return FirMemType::get(odsParser.getContext(),
      uint64_t((*_result_depth)),
      uint32_t((*_result_width)),
      std::optional<uint32_t>((_result_maskWidth.value_or(std::optional<uint32_t>()))));
}

void FirMemType::print(::mlir::AsmPrinter &odsPrinter) const {
  ::mlir::Builder odsBuilder(getContext());
  odsPrinter << "<";
  odsPrinter.printStrippedAttrOrType(getDepth());
  odsPrinter << ' ' << "x";
  odsPrinter << ' ';
  odsPrinter.printStrippedAttrOrType(getWidth());
  if (!(getMaskWidth() == std::optional<uint32_t>())) {
    odsPrinter << ",";
    odsPrinter << ' ' << "mask";
    if (!(getMaskWidth() == std::optional<uint32_t>())) {
      odsPrinter << ' ';
      odsPrinter.printStrippedAttrOrType(getMaskWidth());
    }
  } else {
  }
  odsPrinter << ">";
}

uint64_t FirMemType::getDepth() const {
  return getImpl()->depth;
}

uint32_t FirMemType::getWidth() const {
  return getImpl()->width;
}

std::optional<uint32_t> FirMemType::getMaskWidth() const {
  return getImpl()->maskWidth;
}


} // namespace circt::seq
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::seq::FirMemType)
namespace circt::seq {


} // namespace circt::seq
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::seq::ClockType)
namespace circt::seq {

namespace detail {

struct ImmutableTypeStorage : public ::mlir::TypeStorage {
  using KeyTy = std::tuple<::mlir::Type>;
  ImmutableTypeStorage(::mlir::Type innerType) : innerType(std::move(innerType)) {}

  KeyTy getAsKey() const {
    return KeyTy(innerType);
  }

  bool operator==(const KeyTy &tblgenKey) const {
    return (innerType == std::get<0>(tblgenKey));
  }

  static ::llvm::hash_code hashKey(const KeyTy &tblgenKey) {
    return ::llvm::hash_combine(std::get<0>(tblgenKey));
  }

  static ImmutableTypeStorage *construct(::mlir::TypeStorageAllocator &allocator, KeyTy &&tblgenKey) {
    auto innerType = std::move(std::get<0>(tblgenKey));
    return new (allocator.allocate<ImmutableTypeStorage>()) ImmutableTypeStorage(std::move(innerType));
  }

  ::mlir::Type innerType;
};

} // namespace detail
ImmutableType ImmutableType::get(::mlir::MLIRContext *context, ::mlir::Type innerType) {
  return Base::get(context, std::move(innerType));
}

ImmutableType ImmutableType::get(Type innerType) {
  auto *ctx = innerType.getContext();
  return Base::get(ctx, innerType);
}

::mlir::Type ImmutableType::parse(::mlir::AsmParser &odsParser) {
  ::mlir::Builder odsBuilder(odsParser.getContext());
  ::llvm::SMLoc odsLoc = odsParser.getCurrentLocation();
  (void) odsLoc;
  ::mlir::FailureOr<::mlir::Type> _result_innerType;
  // Parse literal '<'
  if (odsParser.parseLess()) return {};

  // Parse variable 'innerType'
  _result_innerType = ::mlir::FieldParser<::mlir::Type>::parse(odsParser);
  if (::mlir::failed(_result_innerType)) {
    odsParser.emitError(odsParser.getCurrentLocation(), "failed to parse ImmutableTypeImpl parameter 'innerType' which is to be a `::mlir::Type`");
    return {};
  }
  // Parse literal '>'
  if (odsParser.parseGreater()) return {};
  assert(::mlir::succeeded(_result_innerType));
  return ImmutableType::get(odsParser.getContext(),
      ::mlir::Type((*_result_innerType)));
}

void ImmutableType::print(::mlir::AsmPrinter &odsPrinter) const {
  ::mlir::Builder odsBuilder(getContext());
  odsPrinter << "<";
  odsPrinter.printStrippedAttrOrType(getInnerType());
  odsPrinter << ">";
}

::mlir::Type ImmutableType::getInnerType() const {
  return getImpl()->innerType;
}


} // namespace circt::seq
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::seq::ImmutableType)
namespace circt::seq {


/// Parse a type registered to this dialect.
::mlir::Type SeqDialect::parseType(::mlir::DialectAsmParser &parser) const {
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
void SeqDialect::printType(::mlir::Type type,
                    ::mlir::DialectAsmPrinter &printer) const {
  if (::mlir::succeeded(generatedTypePrinter(type, printer)))
    return;
  
}

} // namespace circt::seq

#endif // GET_TYPEDEF_CLASSES

