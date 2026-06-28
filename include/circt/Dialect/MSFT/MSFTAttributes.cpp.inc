/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* AttrDef Definitions                                                        *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

#ifdef GET_ATTRDEF_LIST
#undef GET_ATTRDEF_LIST

::circt::msft::PhysLocationAttr,
::circt::msft::PhysicalBoundsAttr,
::circt::msft::LocationVectorAttr

#endif // GET_ATTRDEF_LIST

#ifdef GET_ATTRDEF_CLASSES
#undef GET_ATTRDEF_CLASSES

static ::mlir::OptionalParseResult generatedAttributeParser(::mlir::AsmParser &parser, ::llvm::StringRef *mnemonic, ::mlir::Type type, ::mlir::Attribute &value) {
  return ::mlir::AsmParser::KeywordSwitch<::mlir::OptionalParseResult>(parser)
    .Case(::circt::msft::PhysLocationAttr::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::msft::PhysLocationAttr::parse(parser, type);
      return ::mlir::success(!!value);
    })
    .Case(::circt::msft::PhysicalBoundsAttr::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::msft::PhysicalBoundsAttr::parse(parser, type);
      return ::mlir::success(!!value);
    })
    .Case(::circt::msft::LocationVectorAttr::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::msft::LocationVectorAttr::parse(parser, type);
      return ::mlir::success(!!value);
    })
    .Default([&](llvm::StringRef keyword, llvm::SMLoc) {
      *mnemonic = keyword;
      return std::nullopt;
    });
}

static ::llvm::LogicalResult generatedAttributePrinter(::mlir::Attribute def, ::mlir::AsmPrinter &printer) {
  return ::llvm::TypeSwitch<::mlir::Attribute, ::llvm::LogicalResult>(def)    .Case<::circt::msft::PhysLocationAttr>([&](auto t) {
      printer << ::circt::msft::PhysLocationAttr::getMnemonic();
t.print(printer);
      return ::mlir::success();
    })
    .Case<::circt::msft::PhysicalBoundsAttr>([&](auto t) {
      printer << ::circt::msft::PhysicalBoundsAttr::getMnemonic();
t.print(printer);
      return ::mlir::success();
    })
    .Case<::circt::msft::LocationVectorAttr>([&](auto t) {
      printer << ::circt::msft::LocationVectorAttr::getMnemonic();
t.print(printer);
      return ::mlir::success();
    })
    .Default([](auto) { return ::mlir::failure(); });
}

namespace circt::msft {

namespace detail {

struct PhysLocationAttrStorage : public ::mlir::AttributeStorage {
  using KeyTy = std::tuple<PrimitiveTypeAttr, uint64_t, uint64_t, uint64_t>;
  PhysLocationAttrStorage(PrimitiveTypeAttr primitiveType, uint64_t x, uint64_t y, uint64_t num) : primitiveType(std::move(primitiveType)), x(std::move(x)), y(std::move(y)), num(std::move(num)) {}

  KeyTy getAsKey() const {
    return KeyTy(primitiveType, x, y, num);
  }

  bool operator==(const KeyTy &tblgenKey) const {
    return (primitiveType == std::get<0>(tblgenKey)) && (x == std::get<1>(tblgenKey)) && (y == std::get<2>(tblgenKey)) && (num == std::get<3>(tblgenKey));
  }

  static ::llvm::hash_code hashKey(const KeyTy &tblgenKey) {
    return ::llvm::hash_combine(std::get<0>(tblgenKey), std::get<1>(tblgenKey), std::get<2>(tblgenKey), std::get<3>(tblgenKey));
  }

  static PhysLocationAttrStorage *construct(::mlir::AttributeStorageAllocator &allocator, KeyTy &&tblgenKey) {
    auto primitiveType = std::move(std::get<0>(tblgenKey));
    auto x = std::move(std::get<1>(tblgenKey));
    auto y = std::move(std::get<2>(tblgenKey));
    auto num = std::move(std::get<3>(tblgenKey));
    return new (allocator.allocate<PhysLocationAttrStorage>()) PhysLocationAttrStorage(std::move(primitiveType), std::move(x), std::move(y), std::move(num));
  }

  PrimitiveTypeAttr primitiveType;
  uint64_t x;
  uint64_t y;
  uint64_t num;
};

} // namespace detail
PhysLocationAttr PhysLocationAttr::get(::mlir::MLIRContext *context, PrimitiveTypeAttr primitiveType, uint64_t x, uint64_t y, uint64_t num) {
  return Base::get(context, std::move(primitiveType), std::move(x), std::move(y), std::move(num));
}

PrimitiveTypeAttr PhysLocationAttr::getPrimitiveType() const {
  return getImpl()->primitiveType;
}

uint64_t PhysLocationAttr::getX() const {
  return getImpl()->x;
}

uint64_t PhysLocationAttr::getY() const {
  return getImpl()->y;
}

uint64_t PhysLocationAttr::getNum() const {
  return getImpl()->num;
}


} // namespace circt::msft
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::msft::PhysLocationAttr)
namespace circt::msft {

namespace detail {

struct PhysicalBoundsAttrStorage : public ::mlir::AttributeStorage {
  using KeyTy = std::tuple<uint64_t, uint64_t, uint64_t, uint64_t>;
  PhysicalBoundsAttrStorage(uint64_t xMin, uint64_t xMax, uint64_t yMin, uint64_t yMax) : xMin(std::move(xMin)), xMax(std::move(xMax)), yMin(std::move(yMin)), yMax(std::move(yMax)) {}

  KeyTy getAsKey() const {
    return KeyTy(xMin, xMax, yMin, yMax);
  }

  bool operator==(const KeyTy &tblgenKey) const {
    return (xMin == std::get<0>(tblgenKey)) && (xMax == std::get<1>(tblgenKey)) && (yMin == std::get<2>(tblgenKey)) && (yMax == std::get<3>(tblgenKey));
  }

  static ::llvm::hash_code hashKey(const KeyTy &tblgenKey) {
    return ::llvm::hash_combine(std::get<0>(tblgenKey), std::get<1>(tblgenKey), std::get<2>(tblgenKey), std::get<3>(tblgenKey));
  }

  static PhysicalBoundsAttrStorage *construct(::mlir::AttributeStorageAllocator &allocator, KeyTy &&tblgenKey) {
    auto xMin = std::move(std::get<0>(tblgenKey));
    auto xMax = std::move(std::get<1>(tblgenKey));
    auto yMin = std::move(std::get<2>(tblgenKey));
    auto yMax = std::move(std::get<3>(tblgenKey));
    return new (allocator.allocate<PhysicalBoundsAttrStorage>()) PhysicalBoundsAttrStorage(std::move(xMin), std::move(xMax), std::move(yMin), std::move(yMax));
  }

  uint64_t xMin;
  uint64_t xMax;
  uint64_t yMin;
  uint64_t yMax;
};

} // namespace detail
PhysicalBoundsAttr PhysicalBoundsAttr::get(::mlir::MLIRContext *context, uint64_t xMin, uint64_t xMax, uint64_t yMin, uint64_t yMax) {
  return Base::get(context, std::move(xMin), std::move(xMax), std::move(yMin), std::move(yMax));
}

uint64_t PhysicalBoundsAttr::getXMin() const {
  return getImpl()->xMin;
}

uint64_t PhysicalBoundsAttr::getXMax() const {
  return getImpl()->xMax;
}

uint64_t PhysicalBoundsAttr::getYMin() const {
  return getImpl()->yMin;
}

uint64_t PhysicalBoundsAttr::getYMax() const {
  return getImpl()->yMax;
}


} // namespace circt::msft
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::msft::PhysicalBoundsAttr)
namespace circt::msft {

namespace detail {

struct LocationVectorAttrStorage : public ::mlir::AttributeStorage {
  using KeyTy = std::tuple<::mlir::TypeAttr, ::llvm::ArrayRef<::circt::msft::PhysLocationAttr>>;
  LocationVectorAttrStorage(::mlir::TypeAttr type, ::llvm::ArrayRef<::circt::msft::PhysLocationAttr> locs) : type(std::move(type)), locs(std::move(locs)) {}

  KeyTy getAsKey() const {
    return KeyTy(type, locs);
  }

  bool operator==(const KeyTy &tblgenKey) const {
    return (type == std::get<0>(tblgenKey)) && (locs == std::get<1>(tblgenKey));
  }

  static ::llvm::hash_code hashKey(const KeyTy &tblgenKey) {
    return ::llvm::hash_combine(std::get<0>(tblgenKey), std::get<1>(tblgenKey));
  }

  static LocationVectorAttrStorage *construct(::mlir::AttributeStorageAllocator &allocator, KeyTy &&tblgenKey) {
    auto type = std::move(std::get<0>(tblgenKey));
    auto locs = std::move(std::get<1>(tblgenKey));
    locs = allocator.copyInto(locs);
    return new (allocator.allocate<LocationVectorAttrStorage>()) LocationVectorAttrStorage(std::move(type), std::move(locs));
  }

  ::mlir::TypeAttr type;
  ::llvm::ArrayRef<::circt::msft::PhysLocationAttr> locs;
};

} // namespace detail
LocationVectorAttr LocationVectorAttr::get(::mlir::MLIRContext *context, ::mlir::TypeAttr type, ::llvm::ArrayRef<::circt::msft::PhysLocationAttr> locs) {
  return Base::get(context, std::move(type), std::move(locs));
}

LocationVectorAttr LocationVectorAttr::getChecked(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::mlir::MLIRContext *context, ::mlir::TypeAttr type, ::llvm::ArrayRef<::circt::msft::PhysLocationAttr> locs) {
  return Base::getChecked(emitError, context, std::move(type), std::move(locs));
}

::llvm::LogicalResult LocationVectorAttr::verifyInvariants(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::mlir::TypeAttr type, ::llvm::ArrayRef<::circt::msft::PhysLocationAttr> locs) {
  if (::mlir::failed(verify(emitError, type, locs)))
    return ::mlir::failure();
  return ::mlir::success();
}

::mlir::TypeAttr LocationVectorAttr::getType() const {
  return getImpl()->type;
}

::llvm::ArrayRef<::circt::msft::PhysLocationAttr> LocationVectorAttr::getLocs() const {
  return getImpl()->locs;
}


} // namespace circt::msft
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::msft::LocationVectorAttr)
namespace circt::msft {


/// Parse an attribute registered to this dialect.
::mlir::Attribute MSFTDialect::parseAttribute(::mlir::DialectAsmParser &parser,
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
void MSFTDialect::printAttribute(::mlir::Attribute attr,
                         ::mlir::DialectAsmPrinter &printer) const {
  if (::mlir::succeeded(generatedAttributePrinter(attr, printer)))
    return;
  
}

} // namespace circt::msft

#endif // GET_ATTRDEF_CLASSES

