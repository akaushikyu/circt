/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* AttrDef Definitions                                                        *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

#ifdef GET_ATTRDEF_LIST
#undef GET_ATTRDEF_LIST

::circt::llhd::TimeAttr

#endif // GET_ATTRDEF_LIST

#ifdef GET_ATTRDEF_CLASSES
#undef GET_ATTRDEF_CLASSES

static ::mlir::OptionalParseResult generatedAttributeParser(::mlir::AsmParser &parser, ::llvm::StringRef *mnemonic, ::mlir::Type type, ::mlir::Attribute &value) {
  return ::mlir::AsmParser::KeywordSwitch<::mlir::OptionalParseResult>(parser)
    .Case(::circt::llhd::TimeAttr::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::llhd::TimeAttr::parse(parser, type);
      return ::mlir::success(!!value);
    })
    .Default([&](llvm::StringRef keyword, llvm::SMLoc) {
      *mnemonic = keyword;
      return std::nullopt;
    });
}

static ::llvm::LogicalResult generatedAttributePrinter(::mlir::Attribute def, ::mlir::AsmPrinter &printer) {
  return ::llvm::TypeSwitch<::mlir::Attribute, ::llvm::LogicalResult>(def)    .Case<::circt::llhd::TimeAttr>([&](auto t) {
      printer << ::circt::llhd::TimeAttr::getMnemonic();
t.print(printer);
      return ::mlir::success();
    })
    .Default([](auto) { return ::mlir::failure(); });
}

namespace circt::llhd {

namespace detail {

struct TimeAttrStorage : public ::mlir::AttributeStorage {
  using KeyTy = std::tuple<llhd::TimeType, uint64_t, ::llvm::StringRef, unsigned, unsigned>;
  TimeAttrStorage(llhd::TimeType type, uint64_t time, ::llvm::StringRef timeUnit, unsigned delta, unsigned epsilon) : type(std::move(type)), time(std::move(time)), timeUnit(std::move(timeUnit)), delta(std::move(delta)), epsilon(std::move(epsilon)) {}

  KeyTy getAsKey() const {
    return KeyTy(type, time, timeUnit, delta, epsilon);
  }

  bool operator==(const KeyTy &tblgenKey) const {
    return (type == std::get<0>(tblgenKey)) && (time == std::get<1>(tblgenKey)) && (timeUnit == std::get<2>(tblgenKey)) && (delta == std::get<3>(tblgenKey)) && (epsilon == std::get<4>(tblgenKey));
  }

  static ::llvm::hash_code hashKey(const KeyTy &tblgenKey) {
    return ::llvm::hash_combine(std::get<0>(tblgenKey), std::get<1>(tblgenKey), std::get<2>(tblgenKey), std::get<3>(tblgenKey), std::get<4>(tblgenKey));
  }

  static TimeAttrStorage *construct(::mlir::AttributeStorageAllocator &allocator, KeyTy &&tblgenKey) {
    auto type = std::move(std::get<0>(tblgenKey));
    auto time = std::move(std::get<1>(tblgenKey));
    auto timeUnit = std::move(std::get<2>(tblgenKey));
    auto delta = std::move(std::get<3>(tblgenKey));
    auto epsilon = std::move(std::get<4>(tblgenKey));
    timeUnit = allocator.copyInto(timeUnit);
    return new (allocator.allocate<TimeAttrStorage>()) TimeAttrStorage(std::move(type), std::move(time), std::move(timeUnit), std::move(delta), std::move(epsilon));
  }

  llhd::TimeType type;
  uint64_t time;
  ::llvm::StringRef timeUnit;
  unsigned delta;
  unsigned epsilon;
};

} // namespace detail
TimeAttr TimeAttr::get(::mlir::MLIRContext *context, uint64_t time, llvm::StringRef timeUnit, unsigned delta, unsigned epsilon) {
  return Base::get(context, llhd::TimeType::get(context),
    time, timeUnit, delta, epsilon);
}

TimeAttr TimeAttr::getChecked(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::mlir::MLIRContext *context, uint64_t time, llvm::StringRef timeUnit, unsigned delta, unsigned epsilon) {
  return Base::getChecked(emitError, context, llhd::TimeType::get(context),
    time, timeUnit, delta, epsilon);
}

::llvm::LogicalResult TimeAttr::verifyInvariants(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, llhd::TimeType type, uint64_t time, ::llvm::StringRef timeUnit, unsigned delta, unsigned epsilon) {
  if (::mlir::failed(verify(emitError, type, time, timeUnit, delta, epsilon)))
    return ::mlir::failure();
  return ::mlir::success();
}

llhd::TimeType TimeAttr::getType() const {
  return getImpl()->type;
}

uint64_t TimeAttr::getTime() const {
  return getImpl()->time;
}

::llvm::StringRef TimeAttr::getTimeUnit() const {
  return getImpl()->timeUnit;
}

unsigned TimeAttr::getDelta() const {
  return getImpl()->delta;
}

unsigned TimeAttr::getEpsilon() const {
  return getImpl()->epsilon;
}


} // namespace circt::llhd
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::llhd::TimeAttr)
namespace circt::llhd {


/// Parse an attribute registered to this dialect.
::mlir::Attribute LLHDDialect::parseAttribute(::mlir::DialectAsmParser &parser,
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
void LLHDDialect::printAttribute(::mlir::Attribute attr,
                         ::mlir::DialectAsmPrinter &printer) const {
  if (::mlir::succeeded(generatedAttributePrinter(attr, printer)))
    return;
  
}

} // namespace circt::llhd

#endif // GET_ATTRDEF_CLASSES

