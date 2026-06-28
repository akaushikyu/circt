/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Op Definitions                                                             *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: Pipeline.td                                                          *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

#ifdef GET_OP_LIST
#undef GET_OP_LIST

::circt::pipeline::LatencyOp,
::circt::pipeline::LatencyReturnOp,
::circt::pipeline::ReturnOp,
::circt::pipeline::ScheduledPipelineOp,
::circt::pipeline::SourceOp,
::circt::pipeline::StageOp,
::circt::pipeline::UnscheduledPipelineOp
#endif // GET_OP_LIST

#ifdef GET_OP_CLASSES
#undef GET_OP_CLASSES


//===----------------------------------------------------------------------===//
// Local Utility Method Definitions
//===----------------------------------------------------------------------===//


static ::llvm::LogicalResult __mlir_ods_local_type_constraint_Pipeline1(
    ::mlir::Operation *op, ::mlir::Type type, ::llvm::StringRef valueKind,
    unsigned valueIndex) {
  if (!(!((::llvm::isa<::mlir::TokenType>(type))))) {
    return op->emitOpError(valueKind) << " #" << valueIndex
        << " must be variadic of any non-token type, but got " << type;
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_type_constraint_Pipeline2(
    ::mlir::Operation *op, ::mlir::Type type, ::llvm::StringRef valueKind,
    unsigned valueIndex) {
  if (!((type.isSignlessInteger(1)))) {
    return op->emitOpError(valueKind) << " #" << valueIndex
        << " must be 1-bit signless integer, but got " << type;
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_type_constraint_Pipeline3(
    ::mlir::Operation *op, ::mlir::Type type, ::llvm::StringRef valueKind,
    unsigned valueIndex) {
  if (!((::llvm::isa<::circt::seq::ClockType>(type)))) {
    return op->emitOpError(valueKind) << " #" << valueIndex
        << " must be A type for clock-carrying wires, but got " << type;
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_type_constraint_Pipeline4(
    ::mlir::Operation *op, ::mlir::Type type, ::llvm::StringRef valueKind,
    unsigned valueIndex) {
  if (!(!((::llvm::isa<::mlir::TokenType>(type))))) {
    return op->emitOpError(valueKind) << " #" << valueIndex
        << " must be any non-token type, but got " << type;
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_type_constraint_Pipeline5(
    ::mlir::Operation *op, ::mlir::Type type, ::llvm::StringRef valueKind,
    unsigned valueIndex) {
  if (!((type.isSignlessInteger(1)))) {
    return op->emitOpError(valueKind) << " #" << valueIndex
        << " must be variadic of 1-bit signless integer, but got " << type;
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_Pipeline1(
    ::mlir::Attribute attr, ::llvm::StringRef attrName, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  if (attr && !((((::llvm::isa<::mlir::IntegerAttr>(attr))) && ((::llvm::cast<::mlir::IntegerAttr>(attr).getType().isSignlessInteger(32)))) && ((::llvm::cast<::mlir::IntegerAttr>(attr).getInt() >= 1))))
    return emitError() << "attribute '" << attrName
        << "' failed to satisfy constraint: 32-bit signless integer attribute whose minimum value is 1";
  return ::mlir::success();
}
static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_Pipeline1(
    ::mlir::Operation *op, ::mlir::Attribute attr, ::llvm::StringRef attrName) {
  return __mlir_ods_local_attr_constraint_Pipeline1(attr, attrName, [op]() {
    return op->emitOpError();
  });
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_Pipeline2(
    ::mlir::Attribute attr, ::llvm::StringRef attrName, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  if (attr && !((::llvm::isa<::mlir::StringAttr>(attr))))
    return emitError() << "attribute '" << attrName
        << "' failed to satisfy constraint: string attribute";
  return ::mlir::success();
}
static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_Pipeline2(
    ::mlir::Operation *op, ::mlir::Attribute attr, ::llvm::StringRef attrName) {
  return __mlir_ods_local_attr_constraint_Pipeline2(attr, attrName, [op]() {
    return op->emitOpError();
  });
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_Pipeline3(
    ::mlir::Attribute attr, ::llvm::StringRef attrName, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  if (attr && !(((::llvm::isa<::mlir::ArrayAttr>(attr))) && (::llvm::all_of(::llvm::cast<::mlir::ArrayAttr>(attr), [&](::mlir::Attribute attr) { return attr && ((::llvm::isa<::mlir::StringAttr>(attr))); }))))
    return emitError() << "attribute '" << attrName
        << "' failed to satisfy constraint: string array attribute";
  return ::mlir::success();
}
static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_Pipeline3(
    ::mlir::Operation *op, ::mlir::Attribute attr, ::llvm::StringRef attrName) {
  return __mlir_ods_local_attr_constraint_Pipeline3(attr, attrName, [op]() {
    return op->emitOpError();
  });
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_Pipeline4(
    ::mlir::Attribute attr, ::llvm::StringRef attrName, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  if (attr && !(((::llvm::isa<::mlir::ArrayAttr>(attr))) && (::llvm::all_of(::llvm::cast<::mlir::ArrayAttr>(attr), [&](::mlir::Attribute attr) { return attr && ((::llvm::isa<::mlir::BoolAttr>(attr))); }))))
    return emitError() << "attribute '" << attrName
        << "' failed to satisfy constraint: 1-bit boolean array attribute";
  return ::mlir::success();
}
static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_Pipeline4(
    ::mlir::Operation *op, ::mlir::Attribute attr, ::llvm::StringRef attrName) {
  return __mlir_ods_local_attr_constraint_Pipeline4(attr, attrName, [op]() {
    return op->emitOpError();
  });
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_Pipeline5(
    ::mlir::Attribute attr, ::llvm::StringRef attrName, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  if (attr && !(((::llvm::isa<::mlir::ArrayAttr>(attr))) && (::llvm::all_of(::llvm::cast<::mlir::ArrayAttr>(attr), [&](::mlir::Attribute attr) { return attr && (((::llvm::isa<::mlir::IntegerAttr>(attr))) && ((::llvm::cast<::mlir::IntegerAttr>(attr).getType().isSignlessInteger(64)))); }))))
    return emitError() << "attribute '" << attrName
        << "' failed to satisfy constraint: 64-bit integer array attribute";
  return ::mlir::success();
}
static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_Pipeline5(
    ::mlir::Operation *op, ::mlir::Attribute attr, ::llvm::StringRef attrName) {
  return __mlir_ods_local_attr_constraint_Pipeline5(attr, attrName, [op]() {
    return op->emitOpError();
  });
}

static ::llvm::LogicalResult __mlir_ods_local_region_constraint_Pipeline1(
    ::mlir::Operation *op, ::mlir::Region &region, ::llvm::StringRef regionName,
    unsigned regionIndex) {
  if (!((::llvm::hasNItems(region, 1)))) {
    return op->emitOpError("region #") << regionIndex
        << (regionName.empty() ? " " : " ('" + regionName + "') ")
        << "failed to verify constraint: region with 1 blocks";
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_region_constraint_Pipeline2(
    ::mlir::Operation *op, ::mlir::Region &region, ::llvm::StringRef regionName,
    unsigned regionIndex) {
  if (!((true))) {
    return op->emitOpError("region #") << regionIndex
        << (regionName.empty() ? " " : " ('" + regionName + "') ")
        << "failed to verify constraint: any region";
  }
  return ::mlir::success();
}
namespace circt::pipeline {


//===----------------------------------------------------------------------===//
// ::circt::pipeline::LatencyOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

LatencyOpGenericAdaptorBase::LatencyOpGenericAdaptorBase(LatencyOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

uint32_t LatencyOpGenericAdaptorBase::getLatency() {
  auto attr = getLatencyAttr();
  return attr.getValue().getZExtValue();
}


} // namespace detail
LatencyOpAdaptor::LatencyOpAdaptor(LatencyOp op) : LatencyOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult LatencyOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_latency = getProperties().latency; (void)tblgen_latency;
  if (!tblgen_latency) return emitError(loc, "'pipeline.latency' op requires attribute 'latency'");

  if (tblgen_latency && !((((::llvm::isa<::mlir::IntegerAttr>(tblgen_latency))) && ((::llvm::cast<::mlir::IntegerAttr>(tblgen_latency).getType().isSignlessInteger(32)))) && ((::llvm::cast<::mlir::IntegerAttr>(tblgen_latency).getInt() >= 1))))
    return emitError(loc, "'pipeline.latency' op attribute 'latency' failed to satisfy constraint: 32-bit signless integer attribute whose minimum value is 1");
  return ::mlir::success();
}

std::pair<unsigned, unsigned> LatencyOp::getODSResultIndexAndLength(unsigned index) {
  bool isVariadic[] = {true};
  int prevVariadicCount = 0;
  for (unsigned i = 0; i < index; ++i)
    if (isVariadic[i]) ++prevVariadicCount;

  // Calculate how many dynamic values a static variadic operand corresponds to.
  // This assumes all static variadic operands have the same dynamic value count.
  int variadicSize = (getOperation()->getNumResults() - 0) / 1;
  // `index` passed in as the parameter is the static index which counts each
  // operand (variadic or not) as size 1. So here for each previous static variadic
  // operand, we need to offset by (variadicSize - 1) to get where the dynamic
  // value pack for this static operand starts.
  int start = index + (variadicSize - 1) * prevVariadicCount;
  int size = isVariadic[index] ? variadicSize : 1;
  return {start, size};
}

::llvm::LogicalResult LatencyOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.latency;
       auto attr = dict.get("latency");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `latency` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  return ::mlir::success();
}

::mlir::Attribute LatencyOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.latency;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("latency",
                                       propStorage));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code LatencyOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.latency.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> LatencyOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "latency")
      return prop.latency;
  return std::nullopt;
}

void LatencyOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "latency") {
       prop.latency = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.latency)>>(value);
       return;
    }
}

void LatencyOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.latency) attrs.append("latency", prop.latency);
}

::llvm::LogicalResult LatencyOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getLatencyAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Pipeline1(attr, "latency", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult LatencyOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.latency)))
    return ::mlir::failure();
  return ::mlir::success();
}

void LatencyOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.latency);
}

uint32_t LatencyOp::getLatency() {
  auto attr = getLatencyAttr();
  return attr.getValue().getZExtValue();
}

void LatencyOp::setLatency(uint32_t attrValue) {
  getProperties().latency = ::mlir::Builder((*this)->getContext()).getIntegerAttr(::mlir::Builder((*this)->getContext()).getIntegerType(32), attrValue);
}

void LatencyOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange results, ::mlir::IntegerAttr latency) {
  odsState.getOrAddProperties<Properties>().latency = latency;
  (void)odsState.addRegion();
  odsState.addTypes(results);
}

LatencyOp LatencyOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange results, ::mlir::IntegerAttr latency) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(results)>(results), std::forward<decltype(latency)>(latency));
  auto __res__ = ::llvm::dyn_cast<LatencyOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

LatencyOp LatencyOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange results, ::mlir::IntegerAttr latency) {
  return create(builder, builder.getLoc(), std::forward<decltype(results)>(results), std::forward<decltype(latency)>(latency));
}

void LatencyOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange results, uint32_t latency) {
  odsState.getOrAddProperties<Properties>().latency = odsBuilder.getIntegerAttr(odsBuilder.getIntegerType(32), latency);
  (void)odsState.addRegion();
  odsState.addTypes(results);
}

LatencyOp LatencyOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange results, uint32_t latency) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(results)>(results), std::forward<decltype(latency)>(latency));
  auto __res__ = ::llvm::dyn_cast<LatencyOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

LatencyOp LatencyOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange results, uint32_t latency) {
  return create(builder, builder.getLoc(), std::forward<decltype(results)>(results), std::forward<decltype(latency)>(latency));
}

void LatencyOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  for (unsigned i = 0; i != 1; ++i)
    (void)odsState.addRegion();
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<LatencyOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

LatencyOp LatencyOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<LatencyOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

LatencyOp LatencyOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void LatencyOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  for (unsigned i = 0; i != 1; ++i)
    (void)odsState.addRegion();
  odsState.addTypes(resultTypes);
}

LatencyOp LatencyOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<LatencyOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

LatencyOp LatencyOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult LatencyOp::verifyInvariantsImpl() {
  auto tblgen_latency = getProperties().latency; (void)tblgen_latency;
  if (!tblgen_latency) return emitOpError("requires attribute 'latency'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Pipeline1(*this, tblgen_latency, "latency")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Pipeline1(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;

    for (auto &region : ::llvm::MutableArrayRef((*this)->getRegion(0)))
      if (::mlir::failed(__mlir_ods_local_region_constraint_Pipeline1(*this, region, "body", index++)))
        return ::mlir::failure();
  }
  return ::mlir::success();
}

::llvm::LogicalResult LatencyOp::verifyInvariants() {
  if(::mlir::succeeded(verifyInvariantsImpl()) && ::mlir::succeeded(verify()))
    return ::mlir::success();
  return ::mlir::failure();
}

::mlir::ParseResult LatencyOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::IntegerAttr latencyAttr;
  ::llvm::SmallVector<::mlir::Type, 1> resultsTypes;
  std::unique_ptr<::mlir::Region> bodyRegion = std::make_unique<::mlir::Region>();

  if (parser.parseCustomAttributeWithFallback(latencyAttr, parser.getBuilder().getIntegerType(32))) {
    return ::mlir::failure();
  }
  if (latencyAttr) result.getOrAddProperties<LatencyOp::Properties>().latency = latencyAttr;
  if (parser.parseArrow())
    return ::mlir::failure();
  if (parser.parseLParen())
    return ::mlir::failure();

  if (parser.parseTypeList(resultsTypes))
    return ::mlir::failure();
  if (parser.parseRParen())
    return ::mlir::failure();

  if (parser.parseRegion(*bodyRegion))
    return ::mlir::failure();

  ensureTerminator(*bodyRegion, parser.getBuilder(), result.location);
  {
    auto loc = parser.getCurrentLocation();(void)loc;
    if (parser.parseOptionalAttrDict(result.attributes))
      return ::mlir::failure();
    if (failed(verifyInherentAttrs(result.name, result.attributes, [&]() {
        return parser.emitError(loc) << "'" << result.name.getStringRef() << "' op ";
      })))
      return ::mlir::failure();
  }
  result.addRegion(std::move(bodyRegion));
  result.addTypes(resultsTypes);
  return ::mlir::success();
}

void LatencyOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter.printAttributeWithoutType(getLatencyAttr());
  _odsPrinter << ' ' << "->";
  _odsPrinter << ' ' << "(";
  _odsPrinter << getResults().getTypes();
  _odsPrinter << ")";
  _odsPrinter << ' ';

  {
    bool printTerminator = true;
    if (auto *term = getBody().empty() ? nullptr : getBody().begin()->getTerminator()) {
      printTerminator = !term->getAttrDictionary().empty() ||
                        term->getNumOperands() != 0 ||
                        term->getNumResults() != 0;
    }
    _odsPrinter.printRegion(getBody(), /*printEntryBlockArgs=*/true,
      /*printBlockTerminators=*/printTerminator);
  }
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("latency");
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
}


} // namespace circt::pipeline
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::pipeline::LatencyOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::pipeline::detail::LatencyOpGenericAdaptorBase::Properties)

namespace circt::pipeline {


//===----------------------------------------------------------------------===//
// ::circt::pipeline::LatencyReturnOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

LatencyReturnOpGenericAdaptorBase::LatencyReturnOpGenericAdaptorBase(LatencyReturnOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

std::pair<unsigned, unsigned> LatencyReturnOpGenericAdaptorBase::getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
  bool isVariadic[] = {true};
  int prevVariadicCount = 0;
  for (unsigned i = 0; i < index; ++i)
    if (isVariadic[i]) ++prevVariadicCount;

  // Calculate how many dynamic values a static variadic operand corresponds to.
  // This assumes all static variadic operands have the same dynamic value count.
  int variadicSize = (odsOperandsSize - 0) / 1;
  // `index` passed in as the parameter is the static index which counts each
  // operand (variadic or not) as size 1. So here for each previous static variadic
  // operand, we need to offset by (variadicSize - 1) to get where the dynamic
  // value pack for this static operand starts.
  int start = index + (variadicSize - 1) * prevVariadicCount;
  int size = isVariadic[index] ? variadicSize : 1;
  return {start, size};
}


} // namespace detail
LatencyReturnOpAdaptor::LatencyReturnOpAdaptor(LatencyReturnOp op) : LatencyReturnOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult LatencyReturnOpAdaptor::verify(::mlir::Location loc) {
  return ::mlir::success();
}

std::pair<unsigned, unsigned> LatencyReturnOp::getODSOperandIndexAndLength(unsigned index) {
  bool isVariadic[] = {true};
  int prevVariadicCount = 0;
  for (unsigned i = 0; i < index; ++i)
    if (isVariadic[i]) ++prevVariadicCount;

  // Calculate how many dynamic values a static variadic operand corresponds to.
  // This assumes all static variadic operands have the same dynamic value count.
  int variadicSize = (getOperation()->getNumOperands() - 0) / 1;
  // `index` passed in as the parameter is the static index which counts each
  // operand (variadic or not) as size 1. So here for each previous static variadic
  // operand, we need to offset by (variadicSize - 1) to get where the dynamic
  // value pack for this static operand starts.
  int start = index + (variadicSize - 1) * prevVariadicCount;
  int size = isVariadic[index] ? variadicSize : 1;
  return {start, size};
}

::mlir::MutableOperandRange LatencyReturnOp::getInputsMutable() {
  auto range = getODSOperandIndexAndLength(0);
  auto mutableRange = ::mlir::MutableOperandRange(getOperation(), range.first, range.second);
  return mutableRange;
}

::llvm::LogicalResult LatencyReturnOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }
      return ::mlir::success();
}

::mlir::Attribute LatencyReturnOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code LatencyReturnOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine();
}

std::optional<mlir::Attribute> LatencyReturnOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
  return std::nullopt;
}

void LatencyReturnOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
}

void LatencyReturnOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
}

::llvm::LogicalResult LatencyReturnOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    return ::mlir::success();
}

void LatencyReturnOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState) {
 return; 
}

LatencyReturnOp LatencyReturnOp::create(::mlir::OpBuilder &builder, ::mlir::Location location) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__);
  auto __res__ = ::llvm::dyn_cast<LatencyReturnOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

LatencyReturnOp LatencyReturnOp::create(::mlir::ImplicitLocOpBuilder &builder) {
  return create(builder, builder.getLoc());
}

void LatencyReturnOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange inputs) {
  odsState.addOperands(inputs);
}

LatencyReturnOp LatencyReturnOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange inputs) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(inputs)>(inputs));
  auto __res__ = ::llvm::dyn_cast<LatencyReturnOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

LatencyReturnOp LatencyReturnOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange inputs) {
  return create(builder, builder.getLoc(), std::forward<decltype(inputs)>(inputs));
}

void LatencyReturnOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

LatencyReturnOp LatencyReturnOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<LatencyReturnOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

LatencyReturnOp LatencyReturnOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void LatencyReturnOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

LatencyReturnOp LatencyReturnOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<LatencyReturnOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

LatencyReturnOp LatencyReturnOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult LatencyReturnOp::verifyInvariantsImpl() {
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Pipeline1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult LatencyReturnOp::verifyInvariants() {
  if(::mlir::succeeded(verifyInvariantsImpl()) && ::mlir::succeeded(verify()))
    return ::mlir::success();
  return ::mlir::failure();
}

::mlir::ParseResult LatencyReturnOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::llvm::SmallVector<::mlir::OpAsmParser::UnresolvedOperand, 4> inputsOperands;
  ::llvm::SMLoc inputsOperandsLoc;
  (void)inputsOperandsLoc;
  ::llvm::SmallVector<::mlir::Type, 1> inputsTypes;

  inputsOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperandList(inputsOperands))
    return ::mlir::failure();
  if (!inputsOperands.empty()) {
  }
  {
    auto loc = parser.getCurrentLocation();(void)loc;
    if (parser.parseOptionalAttrDict(result.attributes))
      return ::mlir::failure();
    if (failed(verifyInherentAttrs(result.name, result.attributes, [&]() {
        return parser.emitError(loc) << "'" << result.name.getStringRef() << "' op ";
      })))
      return ::mlir::failure();
  }
  if (::mlir::succeeded(parser.parseOptionalColon())) {

  if (parser.parseTypeList(inputsTypes))
    return ::mlir::failure();
  }
  if (parser.resolveOperands(inputsOperands, inputsTypes, inputsOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void LatencyReturnOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  if (!getInputs().empty()) {
    _odsPrinter << ' ';
    _odsPrinter << getInputs();
  }
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  if (!getInputs().empty()) {
    _odsPrinter << ' ' << ":";
    _odsPrinter << ' ';
    _odsPrinter << getInputs().getTypes();
  }
}


} // namespace circt::pipeline
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::pipeline::LatencyReturnOp)

namespace circt::pipeline {


//===----------------------------------------------------------------------===//
// ::circt::pipeline::ReturnOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

ReturnOpGenericAdaptorBase::ReturnOpGenericAdaptorBase(ReturnOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

std::pair<unsigned, unsigned> ReturnOpGenericAdaptorBase::getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
  bool isVariadic[] = {true};
  int prevVariadicCount = 0;
  for (unsigned i = 0; i < index; ++i)
    if (isVariadic[i]) ++prevVariadicCount;

  // Calculate how many dynamic values a static variadic operand corresponds to.
  // This assumes all static variadic operands have the same dynamic value count.
  int variadicSize = (odsOperandsSize - 0) / 1;
  // `index` passed in as the parameter is the static index which counts each
  // operand (variadic or not) as size 1. So here for each previous static variadic
  // operand, we need to offset by (variadicSize - 1) to get where the dynamic
  // value pack for this static operand starts.
  int start = index + (variadicSize - 1) * prevVariadicCount;
  int size = isVariadic[index] ? variadicSize : 1;
  return {start, size};
}


} // namespace detail
ReturnOpAdaptor::ReturnOpAdaptor(ReturnOp op) : ReturnOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult ReturnOpAdaptor::verify(::mlir::Location loc) {
  return ::mlir::success();
}

std::pair<unsigned, unsigned> ReturnOp::getODSOperandIndexAndLength(unsigned index) {
  bool isVariadic[] = {true};
  int prevVariadicCount = 0;
  for (unsigned i = 0; i < index; ++i)
    if (isVariadic[i]) ++prevVariadicCount;

  // Calculate how many dynamic values a static variadic operand corresponds to.
  // This assumes all static variadic operands have the same dynamic value count.
  int variadicSize = (getOperation()->getNumOperands() - 0) / 1;
  // `index` passed in as the parameter is the static index which counts each
  // operand (variadic or not) as size 1. So here for each previous static variadic
  // operand, we need to offset by (variadicSize - 1) to get where the dynamic
  // value pack for this static operand starts.
  int start = index + (variadicSize - 1) * prevVariadicCount;
  int size = isVariadic[index] ? variadicSize : 1;
  return {start, size};
}

::mlir::MutableOperandRange ReturnOp::getInputsMutable() {
  auto range = getODSOperandIndexAndLength(0);
  auto mutableRange = ::mlir::MutableOperandRange(getOperation(), range.first, range.second);
  return mutableRange;
}

::llvm::LogicalResult ReturnOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }
      return ::mlir::success();
}

::mlir::Attribute ReturnOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code ReturnOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine();
}

std::optional<mlir::Attribute> ReturnOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
  return std::nullopt;
}

void ReturnOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
}

void ReturnOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
}

::llvm::LogicalResult ReturnOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    return ::mlir::success();
}

void ReturnOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState) {
 return; 
}

ReturnOp ReturnOp::create(::mlir::OpBuilder &builder, ::mlir::Location location) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__);
  auto __res__ = ::llvm::dyn_cast<ReturnOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ReturnOp ReturnOp::create(::mlir::ImplicitLocOpBuilder &builder) {
  return create(builder, builder.getLoc());
}

void ReturnOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange inputs) {
  odsState.addOperands(inputs);
}

ReturnOp ReturnOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange inputs) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(inputs)>(inputs));
  auto __res__ = ::llvm::dyn_cast<ReturnOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ReturnOp ReturnOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange inputs) {
  return create(builder, builder.getLoc(), std::forward<decltype(inputs)>(inputs));
}

void ReturnOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

ReturnOp ReturnOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<ReturnOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ReturnOp ReturnOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void ReturnOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

ReturnOp ReturnOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<ReturnOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ReturnOp ReturnOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult ReturnOp::verifyInvariantsImpl() {
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Pipeline1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult ReturnOp::verifyInvariants() {
  if(::mlir::succeeded(verifyInvariantsImpl()) && ::mlir::succeeded(verify()))
    return ::mlir::success();
  return ::mlir::failure();
}

::mlir::ParseResult ReturnOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::llvm::SmallVector<::mlir::OpAsmParser::UnresolvedOperand, 4> inputsOperands;
  ::llvm::SMLoc inputsOperandsLoc;
  (void)inputsOperandsLoc;
  ::llvm::SmallVector<::mlir::Type, 1> inputsTypes;

  inputsOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperandList(inputsOperands))
    return ::mlir::failure();
  if (!inputsOperands.empty()) {
  }
  {
    auto loc = parser.getCurrentLocation();(void)loc;
    if (parser.parseOptionalAttrDict(result.attributes))
      return ::mlir::failure();
    if (failed(verifyInherentAttrs(result.name, result.attributes, [&]() {
        return parser.emitError(loc) << "'" << result.name.getStringRef() << "' op ";
      })))
      return ::mlir::failure();
  }
  if (::mlir::succeeded(parser.parseOptionalColon())) {

  if (parser.parseTypeList(inputsTypes))
    return ::mlir::failure();
  }
  if (parser.resolveOperands(inputsOperands, inputsTypes, inputsOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void ReturnOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  if (!getInputs().empty()) {
    _odsPrinter << ' ';
    _odsPrinter << getInputs();
  }
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  if (!getInputs().empty()) {
    _odsPrinter << ' ' << ":";
    _odsPrinter << ' ';
    _odsPrinter << getInputs().getTypes();
  }
}


} // namespace circt::pipeline
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::pipeline::ReturnOp)

namespace circt::pipeline {


//===----------------------------------------------------------------------===//
// ::circt::pipeline::ScheduledPipelineOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

ScheduledPipelineOpGenericAdaptorBase::ScheduledPipelineOpGenericAdaptorBase(ScheduledPipelineOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

std::pair<unsigned, unsigned> ScheduledPipelineOpGenericAdaptorBase::getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
  ::llvm::ArrayRef<int32_t> sizeAttr = getProperties().operandSegmentSizes;

  unsigned start = 0;
  for (unsigned i = 0; i < index; ++i)
    start += sizeAttr[i];
  return {start, sizeAttr[index]};
}

::std::optional< ::llvm::StringRef > ScheduledPipelineOpGenericAdaptorBase::getName() {
  auto attr = getNameAttr();
  return attr ? ::std::optional< ::llvm::StringRef >(attr.getValue()) : (::std::nullopt);
}

::mlir::ArrayAttr ScheduledPipelineOpGenericAdaptorBase::getInputNames() {
  auto attr = getInputNamesAttr();
  return attr;
}

::mlir::ArrayAttr ScheduledPipelineOpGenericAdaptorBase::getOutputNames() {
  auto attr = getOutputNamesAttr();
  return attr;
}

::std::optional< ::mlir::ArrayAttr > ScheduledPipelineOpGenericAdaptorBase::getStallability() {
  auto attr = getStallabilityAttr();
  return attr ? ::std::optional< ::mlir::ArrayAttr >(attr) : (::std::nullopt);
}


} // namespace detail
ScheduledPipelineOpAdaptor::ScheduledPipelineOpAdaptor(ScheduledPipelineOp op) : ScheduledPipelineOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult ScheduledPipelineOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_inputNames = getProperties().inputNames; (void)tblgen_inputNames;
  if (!tblgen_inputNames) return emitError(loc, "'pipeline.scheduled' op requires attribute 'inputNames'");
  auto tblgen_name = getProperties().name; (void)tblgen_name;
  auto tblgen_outputNames = getProperties().outputNames; (void)tblgen_outputNames;
  if (!tblgen_outputNames) return emitError(loc, "'pipeline.scheduled' op requires attribute 'outputNames'");
  auto tblgen_stallability = getProperties().stallability; (void)tblgen_stallability;

  if (tblgen_name && !((::llvm::isa<::mlir::StringAttr>(tblgen_name))))
    return emitError(loc, "'pipeline.scheduled' op attribute 'name' failed to satisfy constraint: string attribute");

  if (tblgen_inputNames && !(((::llvm::isa<::mlir::ArrayAttr>(tblgen_inputNames))) && (::llvm::all_of(::llvm::cast<::mlir::ArrayAttr>(tblgen_inputNames), [&](::mlir::Attribute attr) { return attr && ((::llvm::isa<::mlir::StringAttr>(attr))); }))))
    return emitError(loc, "'pipeline.scheduled' op attribute 'inputNames' failed to satisfy constraint: string array attribute");

  if (tblgen_outputNames && !(((::llvm::isa<::mlir::ArrayAttr>(tblgen_outputNames))) && (::llvm::all_of(::llvm::cast<::mlir::ArrayAttr>(tblgen_outputNames), [&](::mlir::Attribute attr) { return attr && ((::llvm::isa<::mlir::StringAttr>(attr))); }))))
    return emitError(loc, "'pipeline.scheduled' op attribute 'outputNames' failed to satisfy constraint: string array attribute");

  if (tblgen_stallability && !(((::llvm::isa<::mlir::ArrayAttr>(tblgen_stallability))) && (::llvm::all_of(::llvm::cast<::mlir::ArrayAttr>(tblgen_stallability), [&](::mlir::Attribute attr) { return attr && ((::llvm::isa<::mlir::BoolAttr>(attr))); }))))
    return emitError(loc, "'pipeline.scheduled' op attribute 'stallability' failed to satisfy constraint: 1-bit boolean array attribute");
  return ::mlir::success();
}

std::pair<unsigned, unsigned> ScheduledPipelineOp::getODSOperandIndexAndLength(unsigned index) {
  ::llvm::ArrayRef<int32_t> sizeAttr = getProperties().operandSegmentSizes;

  unsigned start = 0;
  for (unsigned i = 0; i < index; ++i)
    start += sizeAttr[i];
  return {start, sizeAttr[index]};
}

::mlir::MutableOperandRange ScheduledPipelineOp::getInputsMutable() {
  auto range = getODSOperandIndexAndLength(0);
  auto mutableRange = ::mlir::MutableOperandRange(getOperation(), range.first, range.second, ::mlir::MutableOperandRange::OperandSegment(0u, {getOperandSegmentSizesAttrName(), ::mlir::DenseI32ArrayAttr::get(getContext(), getProperties().operandSegmentSizes)}));
  return mutableRange;
}

::mlir::MutableOperandRange ScheduledPipelineOp::getStallMutable() {
  auto range = getODSOperandIndexAndLength(1);
  auto mutableRange = ::mlir::MutableOperandRange(getOperation(), range.first, range.second, ::mlir::MutableOperandRange::OperandSegment(1u, {getOperandSegmentSizesAttrName(), ::mlir::DenseI32ArrayAttr::get(getContext(), getProperties().operandSegmentSizes)}));
  return mutableRange;
}

::mlir::MutableOperandRange ScheduledPipelineOp::getResetMutable() {
  auto range = getODSOperandIndexAndLength(3);
  auto mutableRange = ::mlir::MutableOperandRange(getOperation(), range.first, range.second, ::mlir::MutableOperandRange::OperandSegment(3u, {getOperandSegmentSizesAttrName(), ::mlir::DenseI32ArrayAttr::get(getContext(), getProperties().operandSegmentSizes)}));
  return mutableRange;
}

std::pair<unsigned, unsigned> ScheduledPipelineOp::getODSResultIndexAndLength(unsigned index) {
  bool isVariadic[] = {true, false};
  int prevVariadicCount = 0;
  for (unsigned i = 0; i < index; ++i)
    if (isVariadic[i]) ++prevVariadicCount;

  // Calculate how many dynamic values a static variadic operand corresponds to.
  // This assumes all static variadic operands have the same dynamic value count.
  int variadicSize = (getOperation()->getNumResults() - 1) / 1;
  // `index` passed in as the parameter is the static index which counts each
  // operand (variadic or not) as size 1. So here for each previous static variadic
  // operand, we need to offset by (variadicSize - 1) to get where the dynamic
  // value pack for this static operand starts.
  int start = index + (variadicSize - 1) * prevVariadicCount;
  int size = isVariadic[index] ? variadicSize : 1;
  return {start, size};
}

::llvm::LogicalResult ScheduledPipelineOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.inputNames;
       auto attr = dict.get("inputNames");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `inputNames` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.name;
       auto attr = dict.get("name");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `name` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.outputNames;
       auto attr = dict.get("outputNames");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `outputNames` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.stallability;
       auto attr = dict.get("stallability");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `stallability` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
{

      auto setFromAttr = [] (auto &propStorage, ::mlir::Attribute propAttr,
               ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) -> ::mlir::LogicalResult {
        return convertFromAttribute(propStorage, propAttr, emitError);
      };
         auto attr = dict.get("operandSegmentSizes");   if (!attr) attr = dict.get("operand_segment_sizes");;
;
      if (attr && ::mlir::failed(setFromAttr(prop.operandSegmentSizes, attr, [&]() {
            return emitError() << "for `operandSegmentSizes`: ";
          })))
        return ::mlir::failure();
  }
  return ::mlir::success();
}

::mlir::Attribute ScheduledPipelineOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.inputNames;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("inputNames",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.name;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("name",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.outputNames;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("outputNames",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.stallability;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("stallability",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.operandSegmentSizes;
      auto attr = [&]() -> ::mlir::Attribute {
        return ::mlir::DenseI32ArrayAttr::get(ctx, propStorage);
      }();
      attrs.push_back(odsBuilder.getNamedAttr("operandSegmentSizes", attr));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code ScheduledPipelineOp::computePropertiesHash(const Properties &prop) {
  auto hash_operandSegmentSizes_ = [] (const auto &propStorage) -> llvm::hash_code {
    using ::llvm::hash_value;
    return ::llvm::hash_combine_range(std::begin(propStorage), std::end(propStorage));;
  };
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.inputNames.getAsOpaquePointer()), 
    llvm::hash_value(prop.name.getAsOpaquePointer()), 
    llvm::hash_value(prop.outputNames.getAsOpaquePointer()), 
    llvm::hash_value(prop.stallability.getAsOpaquePointer()), 
    hash_operandSegmentSizes_(prop.operandSegmentSizes));
}

std::optional<mlir::Attribute> ScheduledPipelineOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "inputNames")
      return prop.inputNames;

    if (name == "name")
      return prop.name;

    if (name == "outputNames")
      return prop.outputNames;

    if (name == "stallability")
      return prop.stallability;
    if (name == "operand_segment_sizes" || name == "operandSegmentSizes") return [&]() -> ::mlir::Attribute { return ::mlir::DenseI32ArrayAttr::get(ctx, prop.operandSegmentSizes); }();
  return std::nullopt;
}

void ScheduledPipelineOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "inputNames") {
       prop.inputNames = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.inputNames)>>(value);
       return;
    }

    if (name == "name") {
       prop.name = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.name)>>(value);
       return;
    }

    if (name == "outputNames") {
       prop.outputNames = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.outputNames)>>(value);
       return;
    }

    if (name == "stallability") {
       prop.stallability = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.stallability)>>(value);
       return;
    }
        if (name == "operand_segment_sizes" || name == "operandSegmentSizes") {
       auto arrAttr = ::llvm::dyn_cast_or_null<::mlir::DenseI32ArrayAttr>(value);
       if (!arrAttr) return;
       if (arrAttr.size() != sizeof(prop.operandSegmentSizes) / sizeof(int32_t))
         return;
       llvm::copy(arrAttr.asArrayRef(), prop.operandSegmentSizes.begin());
       return;
    }
}

void ScheduledPipelineOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.inputNames) attrs.append("inputNames", prop.inputNames);

    if (prop.name) attrs.append("name", prop.name);

    if (prop.outputNames) attrs.append("outputNames", prop.outputNames);

    if (prop.stallability) attrs.append("stallability", prop.stallability);
  attrs.append("operandSegmentSizes", [&]() -> ::mlir::Attribute { return ::mlir::DenseI32ArrayAttr::get(ctx, prop.operandSegmentSizes); }());
}

::llvm::LogicalResult ScheduledPipelineOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getInputNamesAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Pipeline3(attr, "inputNames", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getNameAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Pipeline2(attr, "name", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getOutputNamesAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Pipeline3(attr, "outputNames", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getStallabilityAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Pipeline4(attr, "stallability", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult ScheduledPipelineOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.inputNames)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readOptionalAttribute(prop.name)))
    return ::mlir::failure();

  if (reader.getBytecodeVersion() < /*kNativePropertiesODSSegmentSize=*/6) {
    auto &propStorage = prop.operandSegmentSizes;
    ::mlir::DenseI32ArrayAttr attr;
    if (::mlir::failed(reader.readAttribute(attr))) return ::mlir::failure();
    if (attr.size() > static_cast<int64_t>(sizeof(propStorage) / sizeof(int32_t))) {
      reader.emitError("size mismatch for operand/result_segment_size");
      return ::mlir::failure();
    }
    ::llvm::copy(::llvm::ArrayRef<int32_t>(attr), propStorage.begin());
  }

  if (::mlir::failed(reader.readAttribute(prop.outputNames)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readOptionalAttribute(prop.stallability)))
    return ::mlir::failure();

  {
    auto &propStorage = prop.operandSegmentSizes;
    auto readProp = [&]() {

  if (reader.getBytecodeVersion() >= /*kNativePropertiesODSSegmentSize=*/6)
    return reader.readSparseArray(::llvm::MutableArrayRef(propStorage));
;
      return ::mlir::success();
    };
    if (::mlir::failed(readProp()))
      return ::mlir::failure();
  }
  return ::mlir::success();
}

void ScheduledPipelineOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.inputNames);

  writer.writeOptionalAttribute(prop.name);

if (writer.getBytecodeVersion() < /*kNativePropertiesODSSegmentSize=*/6) {
  auto &propStorage = prop.operandSegmentSizes;
  writer.writeAttribute(::mlir::DenseI32ArrayAttr::get(this->getContext(), propStorage));
}
  writer.writeAttribute(prop.outputNames);

  writer.writeOptionalAttribute(prop.stallability);

  {
    auto &propStorage = prop.operandSegmentSizes;

  if (writer.getBytecodeVersion() >= /*kNativePropertiesODSSegmentSize=*/6)
    writer.writeSparseArray(::llvm::ArrayRef(propStorage));
;
  }
}

::std::optional< ::llvm::StringRef > ScheduledPipelineOp::getName() {
  auto attr = getNameAttr();
  return attr ? ::std::optional< ::llvm::StringRef >(attr.getValue()) : (::std::nullopt);
}

::mlir::ArrayAttr ScheduledPipelineOp::getInputNames() {
  auto attr = getInputNamesAttr();
  return attr;
}

::mlir::ArrayAttr ScheduledPipelineOp::getOutputNames() {
  auto attr = getOutputNamesAttr();
  return attr;
}

::std::optional< ::mlir::ArrayAttr > ScheduledPipelineOp::getStallability() {
  auto attr = getStallabilityAttr();
  return attr ? ::std::optional< ::mlir::ArrayAttr >(attr) : (::std::nullopt);
}

void ScheduledPipelineOp::setName(::std::optional<::llvm::StringRef> attrValue) {
    auto &odsProp = getProperties().name;
    if (attrValue)
      odsProp = ::mlir::Builder((*this)->getContext()).getStringAttr(*attrValue);
    else
      odsProp = nullptr;
}

ScheduledPipelineOp ScheduledPipelineOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, TypeRange dataOutputs, ValueRange inputs, ArrayAttr inputNames, ArrayAttr outputNames, Value clock, Value go, Value reset, Value stall, StringAttr name, ArrayAttr stallability) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(dataOutputs)>(dataOutputs), std::forward<decltype(inputs)>(inputs), std::forward<decltype(inputNames)>(inputNames), std::forward<decltype(outputNames)>(outputNames), std::forward<decltype(clock)>(clock), std::forward<decltype(go)>(go), std::forward<decltype(reset)>(reset), std::forward<decltype(stall)>(stall), std::forward<decltype(name)>(name), std::forward<decltype(stallability)>(stallability));
  auto __res__ = ::llvm::dyn_cast<ScheduledPipelineOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ScheduledPipelineOp ScheduledPipelineOp::create(::mlir::ImplicitLocOpBuilder &builder, TypeRange dataOutputs, ValueRange inputs, ArrayAttr inputNames, ArrayAttr outputNames, Value clock, Value go, Value reset, Value stall, StringAttr name, ArrayAttr stallability) {
  return create(builder, builder.getLoc(), std::forward<decltype(dataOutputs)>(dataOutputs), std::forward<decltype(inputs)>(inputs), std::forward<decltype(inputNames)>(inputNames), std::forward<decltype(outputNames)>(outputNames), std::forward<decltype(clock)>(clock), std::forward<decltype(go)>(go), std::forward<decltype(reset)>(reset), std::forward<decltype(stall)>(stall), std::forward<decltype(name)>(name), std::forward<decltype(stallability)>(stallability));
}

::llvm::LogicalResult ScheduledPipelineOp::verifyInvariantsImpl() {
  auto tblgen_inputNames = getProperties().inputNames; (void)tblgen_inputNames;
  if (!tblgen_inputNames) return emitOpError("requires attribute 'inputNames'");
  auto tblgen_name = getProperties().name; (void)tblgen_name;
  auto tblgen_outputNames = getProperties().outputNames; (void)tblgen_outputNames;
  if (!tblgen_outputNames) return emitOpError("requires attribute 'outputNames'");
  auto tblgen_stallability = getProperties().stallability; (void)tblgen_stallability;

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Pipeline2(*this, tblgen_name, "name")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Pipeline3(*this, tblgen_inputNames, "inputNames")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Pipeline3(*this, tblgen_outputNames, "outputNames")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Pipeline4(*this, tblgen_stallability, "stallability")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Pipeline1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSOperands(1);

    if (valueGroup1.size() > 1) {
      return emitOpError("operand group starting at #") << index
          << " requires 0 or 1 element, but found " << valueGroup1.size();
    }

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Pipeline2(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup2 = getODSOperands(2);

    for (auto v : valueGroup2) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Pipeline3(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup3 = getODSOperands(3);

    if (valueGroup3.size() > 1) {
      return emitOpError("operand group starting at #") << index
          << " requires 0 or 1 element, but found " << valueGroup3.size();
    }

    for (auto v : valueGroup3) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Pipeline2(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup4 = getODSOperands(4);

    for (auto v : valueGroup4) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Pipeline2(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Pipeline1(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSResults(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Pipeline2(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;

    for (auto &region : ::llvm::MutableArrayRef((*this)->getRegion(0)))
      if (::mlir::failed(__mlir_ods_local_region_constraint_Pipeline2(*this, region, "body", index++)))
        return ::mlir::failure();
  }
  return ::mlir::success();
}

::llvm::LogicalResult ScheduledPipelineOp::verifyInvariants() {
  if(::mlir::succeeded(verifyInvariantsImpl()) && ::mlir::succeeded(verify()))
    return ::mlir::success();
  return ::mlir::failure();
}

::llvm::LogicalResult ScheduledPipelineOp::setPropertiesFromParsedAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }
  // keep track of used keys in the input dictionary to be able to error out
  // if there are some unknown ones.
  ::mlir::DenseSet<::mlir::StringAttr> usedKeys;
  ::mlir::MLIRContext *ctx = dict.getContext();
  (void)ctx;
  {

    auto &propStorage = prop.name;
    auto nameAttrName = ::mlir::StringAttr::get(ctx, "name");
    auto attr = dict.get(nameAttrName);
    usedKeys.insert(nameAttrName);
    if (attr || /*isRequired=*/false) {
      if (!attr) {
        emitError() << "expected key entry for name in DictionaryAttr to set "
                   "Properties.";
        return ::mlir::failure();
      }
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `name` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  {

    auto &propStorage = prop.inputNames;
    auto inputNamesAttrName = ::mlir::StringAttr::get(ctx, "inputNames");
    auto attr = dict.get(inputNamesAttrName);
    usedKeys.insert(inputNamesAttrName);
    if (attr || /*isRequired=*/true) {
      if (!attr) {
        emitError() << "expected key entry for inputNames in DictionaryAttr to set "
                   "Properties.";
        return ::mlir::failure();
      }
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `inputNames` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  {

    auto &propStorage = prop.outputNames;
    auto outputNamesAttrName = ::mlir::StringAttr::get(ctx, "outputNames");
    auto attr = dict.get(outputNamesAttrName);
    usedKeys.insert(outputNamesAttrName);
    if (attr || /*isRequired=*/true) {
      if (!attr) {
        emitError() << "expected key entry for outputNames in DictionaryAttr to set "
                   "Properties.";
        return ::mlir::failure();
      }
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `outputNames` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  {

    auto &propStorage = prop.stallability;
    auto stallabilityAttrName = ::mlir::StringAttr::get(ctx, "stallability");
    auto attr = dict.get(stallabilityAttrName);
    usedKeys.insert(stallabilityAttrName);
    if (attr || /*isRequired=*/false) {
      if (!attr) {
        emitError() << "expected key entry for stallability in DictionaryAttr to set "
                   "Properties.";
        return ::mlir::failure();
      }
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `stallability` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  for (::mlir::NamedAttribute attr : dict) {
    if (!usedKeys.contains(attr.getName()))
      return emitError() << "unknown key '" << attr.getName() <<
          "' when parsing properties dictionary";
  }
  return ::mlir::success();
}


} // namespace circt::pipeline
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::pipeline::ScheduledPipelineOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::pipeline::detail::ScheduledPipelineOpGenericAdaptorBase::Properties)

namespace circt::pipeline {


//===----------------------------------------------------------------------===//
// ::circt::pipeline::SourceOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

SourceOpGenericAdaptorBase::SourceOpGenericAdaptorBase(SourceOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}


} // namespace detail
SourceOpAdaptor::SourceOpAdaptor(SourceOp op) : SourceOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult SourceOpAdaptor::verify(::mlir::Location loc) {
  return ::mlir::success();
}

::llvm::LogicalResult SourceOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }
      return ::mlir::success();
}

::mlir::Attribute SourceOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code SourceOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine();
}

std::optional<mlir::Attribute> SourceOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
  return std::nullopt;
}

void SourceOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
}

void SourceOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
}

::llvm::LogicalResult SourceOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    return ::mlir::success();
}

void SourceOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type output, ::mlir::Value input) {
  odsState.addOperands(input);
  odsState.addTypes(output);
}

SourceOp SourceOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type output, ::mlir::Value input) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(output)>(output), std::forward<decltype(input)>(input));
  auto __res__ = ::llvm::dyn_cast<SourceOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SourceOp SourceOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type output, ::mlir::Value input) {
  return create(builder, builder.getLoc(), std::forward<decltype(output)>(output), std::forward<decltype(input)>(input));
}

void SourceOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value input) {
  odsState.addOperands(input);

        ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
        if (::mlir::succeeded(SourceOp::inferReturnTypes(odsBuilder.getContext(),
                      odsState.location, odsState.operands,
                      odsState.attributes.getDictionary(odsState.getContext()),
                      odsState.getRawProperties(),
                      odsState.regions, inferredReturnTypes)))
          odsState.addTypes(inferredReturnTypes);
        else
          ::mlir::detail::reportFatalInferReturnTypesError(odsState);
        
}

SourceOp SourceOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value input) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(input)>(input));
  auto __res__ = ::llvm::dyn_cast<SourceOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SourceOp SourceOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value input) {
  return create(builder, builder.getLoc(), std::forward<decltype(input)>(input));
}

void SourceOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value input) {
  odsState.addOperands(input);
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

SourceOp SourceOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value input) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(input)>(input));
  auto __res__ = ::llvm::dyn_cast<SourceOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SourceOp SourceOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value input) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(input)>(input));
}

void SourceOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

SourceOp SourceOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<SourceOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SourceOp SourceOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void SourceOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);

  ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
  if (::mlir::succeeded(SourceOp::inferReturnTypes(odsBuilder.getContext(),
          odsState.location, operands,
          odsState.attributes.getDictionary(odsState.getContext()),
          odsState.getRawProperties(),
          odsState.regions, inferredReturnTypes))) {
    assert(inferredReturnTypes.size() == 1u && "mismatched number of return types");
    odsState.addTypes(inferredReturnTypes);
  } else {
    ::llvm::report_fatal_error("Failed to infer result type(s).");
  }
}

SourceOp SourceOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<SourceOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SourceOp SourceOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void SourceOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

SourceOp SourceOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<SourceOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SourceOp SourceOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

void SourceOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties &>(properties));
  odsState.addAttributes(discardableAttributes);

  ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
  if (::mlir::succeeded(SourceOp::inferReturnTypes(odsBuilder.getContext(),
          odsState.location, operands,
          odsState.attributes.getDictionary(odsState.getContext()),
          odsState.getRawProperties(),
          odsState.regions, inferredReturnTypes))) {
    assert(inferredReturnTypes.size() == 1u && "mismatched number of return types");
    odsState.addTypes(inferredReturnTypes);
  } else {
    ::llvm::report_fatal_error("Failed to infer result type(s).");
  }
}

SourceOp SourceOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<SourceOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SourceOp SourceOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult SourceOp::verifyInvariantsImpl() {
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Pipeline4(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Pipeline4(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  if (!((std::equal_to<>()((*this->getODSOperands(0).begin()).getType(), (*this->getODSResults(0).begin()).getType()))))
    return emitOpError("failed to verify that input and result types are equivalent");
  return ::mlir::success();
}

::llvm::LogicalResult SourceOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::llvm::LogicalResult SourceOp::inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::PropertyRef properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes) {
  inferredReturnTypes.resize(1);
  ::mlir::Builder odsBuilder(context);
  if (operands.size() <= 0)
    return ::mlir::failure();
  ::mlir::Type odsInferredType0 = operands[0].getType();
  inferredReturnTypes[0] = odsInferredType0;
  return ::mlir::success();
}

::mlir::ParseResult SourceOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::OpAsmParser::UnresolvedOperand inputRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> inputOperands(&inputRawOperand, 1);  ::llvm::SMLoc inputOperandsLoc;
  (void)inputOperandsLoc;
  ::mlir::Type inputRawType{};
  ::llvm::ArrayRef<::mlir::Type> inputTypes(&inputRawType, 1);

  inputOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(inputRawOperand))
    return ::mlir::failure();
  if (parser.parseColon())
    return ::mlir::failure();

  {
    ::mlir::Type type;
    if (parser.parseCustomTypeWithFallback(type))
      return ::mlir::failure();
    inputRawType = type;
  }
  {
    auto loc = parser.getCurrentLocation();(void)loc;
    if (parser.parseOptionalAttrDict(result.attributes))
      return ::mlir::failure();
    if (failed(verifyInherentAttrs(result.name, result.attributes, [&]() {
        return parser.emitError(loc) << "'" << result.name.getStringRef() << "' op ";
      })))
      return ::mlir::failure();
  }
  for (::mlir::Type type : inputTypes) {
    (void)type;
    if (!(!((::llvm::isa<::mlir::TokenType>(type))))) {
      return parser.emitError(parser.getNameLoc()) << "'input' must be any non-token type, but got " << type;
    }
  }
  result.addTypes(inputTypes[0]);
  if (parser.resolveOperands(inputOperands, inputTypes, inputOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void SourceOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter << getInput();
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
  {
    auto type = getInput().getType();
    if (auto validType = ::llvm::dyn_cast<::mlir::Type>(type))
      _odsPrinter.printStrippedAttrOrType(validType);
   else
     _odsPrinter << type;
  }
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
}


} // namespace circt::pipeline
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::pipeline::SourceOp)

namespace circt::pipeline {


//===----------------------------------------------------------------------===//
// ::circt::pipeline::StageOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

StageOpGenericAdaptorBase::StageOpGenericAdaptorBase(StageOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

std::pair<unsigned, unsigned> StageOpGenericAdaptorBase::getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
  ::llvm::ArrayRef<int32_t> sizeAttr = getProperties().operandSegmentSizes;

  unsigned start = 0;
  for (unsigned i = 0; i < index; ++i)
    start += sizeAttr[i];
  return {start, sizeAttr[index]};
}

::mlir::ArrayAttr StageOpGenericAdaptorBase::getClockGatesPerRegister() {
  auto attr = getClockGatesPerRegisterAttr();
  return attr;
}

::std::optional< ::mlir::ArrayAttr > StageOpGenericAdaptorBase::getRegisterNames() {
  auto attr = getRegisterNamesAttr();
  return attr ? ::std::optional< ::mlir::ArrayAttr >(attr) : (::std::nullopt);
}

::std::optional< ::mlir::ArrayAttr > StageOpGenericAdaptorBase::getPassthroughNames() {
  auto attr = getPassthroughNamesAttr();
  return attr ? ::std::optional< ::mlir::ArrayAttr >(attr) : (::std::nullopt);
}


} // namespace detail
StageOpAdaptor::StageOpAdaptor(StageOp op) : StageOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult StageOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_clockGatesPerRegister = getProperties().clockGatesPerRegister; (void)tblgen_clockGatesPerRegister;
  if (!tblgen_clockGatesPerRegister) return emitError(loc, "'pipeline.stage' op requires attribute 'clockGatesPerRegister'");
  auto tblgen_passthroughNames = getProperties().passthroughNames; (void)tblgen_passthroughNames;
  auto tblgen_registerNames = getProperties().registerNames; (void)tblgen_registerNames;

  if (tblgen_clockGatesPerRegister && !(((::llvm::isa<::mlir::ArrayAttr>(tblgen_clockGatesPerRegister))) && (::llvm::all_of(::llvm::cast<::mlir::ArrayAttr>(tblgen_clockGatesPerRegister), [&](::mlir::Attribute attr) { return attr && (((::llvm::isa<::mlir::IntegerAttr>(attr))) && ((::llvm::cast<::mlir::IntegerAttr>(attr).getType().isSignlessInteger(64)))); }))))
    return emitError(loc, "'pipeline.stage' op attribute 'clockGatesPerRegister' failed to satisfy constraint: 64-bit integer array attribute");

  if (tblgen_registerNames && !(((::llvm::isa<::mlir::ArrayAttr>(tblgen_registerNames))) && (::llvm::all_of(::llvm::cast<::mlir::ArrayAttr>(tblgen_registerNames), [&](::mlir::Attribute attr) { return attr && ((::llvm::isa<::mlir::StringAttr>(attr))); }))))
    return emitError(loc, "'pipeline.stage' op attribute 'registerNames' failed to satisfy constraint: string array attribute");

  if (tblgen_passthroughNames && !(((::llvm::isa<::mlir::ArrayAttr>(tblgen_passthroughNames))) && (::llvm::all_of(::llvm::cast<::mlir::ArrayAttr>(tblgen_passthroughNames), [&](::mlir::Attribute attr) { return attr && ((::llvm::isa<::mlir::StringAttr>(attr))); }))))
    return emitError(loc, "'pipeline.stage' op attribute 'passthroughNames' failed to satisfy constraint: string array attribute");
  return ::mlir::success();
}

std::pair<unsigned, unsigned> StageOp::getODSOperandIndexAndLength(unsigned index) {
  ::llvm::ArrayRef<int32_t> sizeAttr = getProperties().operandSegmentSizes;

  unsigned start = 0;
  for (unsigned i = 0; i < index; ++i)
    start += sizeAttr[i];
  return {start, sizeAttr[index]};
}

::mlir::MutableOperandRange StageOp::getRegistersMutable() {
  auto range = getODSOperandIndexAndLength(0);
  auto mutableRange = ::mlir::MutableOperandRange(getOperation(), range.first, range.second, ::mlir::MutableOperandRange::OperandSegment(0u, {getOperandSegmentSizesAttrName(), ::mlir::DenseI32ArrayAttr::get(getContext(), getProperties().operandSegmentSizes)}));
  return mutableRange;
}

::mlir::MutableOperandRange StageOp::getPassthroughsMutable() {
  auto range = getODSOperandIndexAndLength(1);
  auto mutableRange = ::mlir::MutableOperandRange(getOperation(), range.first, range.second, ::mlir::MutableOperandRange::OperandSegment(1u, {getOperandSegmentSizesAttrName(), ::mlir::DenseI32ArrayAttr::get(getContext(), getProperties().operandSegmentSizes)}));
  return mutableRange;
}

::mlir::MutableOperandRange StageOp::getClockGatesMutable() {
  auto range = getODSOperandIndexAndLength(2);
  auto mutableRange = ::mlir::MutableOperandRange(getOperation(), range.first, range.second, ::mlir::MutableOperandRange::OperandSegment(2u, {getOperandSegmentSizesAttrName(), ::mlir::DenseI32ArrayAttr::get(getContext(), getProperties().operandSegmentSizes)}));
  return mutableRange;
}

::llvm::LogicalResult StageOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.clockGatesPerRegister;
       auto attr = dict.get("clockGatesPerRegister");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `clockGatesPerRegister` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.passthroughNames;
       auto attr = dict.get("passthroughNames");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `passthroughNames` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.registerNames;
       auto attr = dict.get("registerNames");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `registerNames` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
{

      auto setFromAttr = [] (auto &propStorage, ::mlir::Attribute propAttr,
               ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) -> ::mlir::LogicalResult {
        return convertFromAttribute(propStorage, propAttr, emitError);
      };
         auto attr = dict.get("operandSegmentSizes");   if (!attr) attr = dict.get("operand_segment_sizes");;
;
      if (attr && ::mlir::failed(setFromAttr(prop.operandSegmentSizes, attr, [&]() {
            return emitError() << "for `operandSegmentSizes`: ";
          })))
        return ::mlir::failure();
  }
  return ::mlir::success();
}

::mlir::Attribute StageOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.clockGatesPerRegister;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("clockGatesPerRegister",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.passthroughNames;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("passthroughNames",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.registerNames;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("registerNames",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.operandSegmentSizes;
      auto attr = [&]() -> ::mlir::Attribute {
        return ::mlir::DenseI32ArrayAttr::get(ctx, propStorage);
      }();
      attrs.push_back(odsBuilder.getNamedAttr("operandSegmentSizes", attr));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code StageOp::computePropertiesHash(const Properties &prop) {
  auto hash_operandSegmentSizes_ = [] (const auto &propStorage) -> llvm::hash_code {
    using ::llvm::hash_value;
    return ::llvm::hash_combine_range(std::begin(propStorage), std::end(propStorage));;
  };
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.clockGatesPerRegister.getAsOpaquePointer()), 
    llvm::hash_value(prop.passthroughNames.getAsOpaquePointer()), 
    llvm::hash_value(prop.registerNames.getAsOpaquePointer()), 
    hash_operandSegmentSizes_(prop.operandSegmentSizes));
}

std::optional<mlir::Attribute> StageOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "clockGatesPerRegister")
      return prop.clockGatesPerRegister;

    if (name == "passthroughNames")
      return prop.passthroughNames;

    if (name == "registerNames")
      return prop.registerNames;
    if (name == "operand_segment_sizes" || name == "operandSegmentSizes") return [&]() -> ::mlir::Attribute { return ::mlir::DenseI32ArrayAttr::get(ctx, prop.operandSegmentSizes); }();
  return std::nullopt;
}

void StageOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "clockGatesPerRegister") {
       prop.clockGatesPerRegister = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.clockGatesPerRegister)>>(value);
       return;
    }

    if (name == "passthroughNames") {
       prop.passthroughNames = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.passthroughNames)>>(value);
       return;
    }

    if (name == "registerNames") {
       prop.registerNames = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.registerNames)>>(value);
       return;
    }
        if (name == "operand_segment_sizes" || name == "operandSegmentSizes") {
       auto arrAttr = ::llvm::dyn_cast_or_null<::mlir::DenseI32ArrayAttr>(value);
       if (!arrAttr) return;
       if (arrAttr.size() != sizeof(prop.operandSegmentSizes) / sizeof(int32_t))
         return;
       llvm::copy(arrAttr.asArrayRef(), prop.operandSegmentSizes.begin());
       return;
    }
}

void StageOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.clockGatesPerRegister) attrs.append("clockGatesPerRegister", prop.clockGatesPerRegister);

    if (prop.passthroughNames) attrs.append("passthroughNames", prop.passthroughNames);

    if (prop.registerNames) attrs.append("registerNames", prop.registerNames);
  attrs.append("operandSegmentSizes", [&]() -> ::mlir::Attribute { return ::mlir::DenseI32ArrayAttr::get(ctx, prop.operandSegmentSizes); }());
}

::llvm::LogicalResult StageOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getClockGatesPerRegisterAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Pipeline5(attr, "clockGatesPerRegister", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getPassthroughNamesAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Pipeline3(attr, "passthroughNames", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getRegisterNamesAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Pipeline3(attr, "registerNames", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult StageOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.clockGatesPerRegister)))
    return ::mlir::failure();

  if (reader.getBytecodeVersion() < /*kNativePropertiesODSSegmentSize=*/6) {
    auto &propStorage = prop.operandSegmentSizes;
    ::mlir::DenseI32ArrayAttr attr;
    if (::mlir::failed(reader.readAttribute(attr))) return ::mlir::failure();
    if (attr.size() > static_cast<int64_t>(sizeof(propStorage) / sizeof(int32_t))) {
      reader.emitError("size mismatch for operand/result_segment_size");
      return ::mlir::failure();
    }
    ::llvm::copy(::llvm::ArrayRef<int32_t>(attr), propStorage.begin());
  }

  if (::mlir::failed(reader.readOptionalAttribute(prop.passthroughNames)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readOptionalAttribute(prop.registerNames)))
    return ::mlir::failure();

  {
    auto &propStorage = prop.operandSegmentSizes;
    auto readProp = [&]() {

  if (reader.getBytecodeVersion() >= /*kNativePropertiesODSSegmentSize=*/6)
    return reader.readSparseArray(::llvm::MutableArrayRef(propStorage));
;
      return ::mlir::success();
    };
    if (::mlir::failed(readProp()))
      return ::mlir::failure();
  }
  return ::mlir::success();
}

void StageOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.clockGatesPerRegister);

if (writer.getBytecodeVersion() < /*kNativePropertiesODSSegmentSize=*/6) {
  auto &propStorage = prop.operandSegmentSizes;
  writer.writeAttribute(::mlir::DenseI32ArrayAttr::get(this->getContext(), propStorage));
}

  writer.writeOptionalAttribute(prop.passthroughNames);

  writer.writeOptionalAttribute(prop.registerNames);

  {
    auto &propStorage = prop.operandSegmentSizes;

  if (writer.getBytecodeVersion() >= /*kNativePropertiesODSSegmentSize=*/6)
    writer.writeSparseArray(::llvm::ArrayRef(propStorage));
;
  }
}

::mlir::ArrayAttr StageOp::getClockGatesPerRegister() {
  auto attr = getClockGatesPerRegisterAttr();
  return attr;
}

::std::optional< ::mlir::ArrayAttr > StageOp::getRegisterNames() {
  auto attr = getRegisterNamesAttr();
  return attr ? ::std::optional< ::mlir::ArrayAttr >(attr) : (::std::nullopt);
}

::std::optional< ::mlir::ArrayAttr > StageOp::getPassthroughNames() {
  auto attr = getPassthroughNamesAttr();
  return attr ? ::std::optional< ::mlir::ArrayAttr >(attr) : (::std::nullopt);
}

StageOp StageOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, Block*dest, ValueRange registers, ValueRange passthroughs) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(dest)>(dest), std::forward<decltype(registers)>(registers), std::forward<decltype(passthroughs)>(passthroughs));
  auto __res__ = ::llvm::dyn_cast<StageOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

StageOp StageOp::create(::mlir::ImplicitLocOpBuilder &builder, Block*dest, ValueRange registers, ValueRange passthroughs) {
  return create(builder, builder.getLoc(), std::forward<decltype(dest)>(dest), std::forward<decltype(registers)>(registers), std::forward<decltype(passthroughs)>(passthroughs));
}

StageOp StageOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, Block*dest, ValueRange registers, ValueRange passthroughs, llvm::ArrayRef<llvm::SmallVector<Value>> clockGates, mlir::ArrayAttr registerNames, mlir::ArrayAttr passthroughNames) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(dest)>(dest), std::forward<decltype(registers)>(registers), std::forward<decltype(passthroughs)>(passthroughs), std::forward<decltype(clockGates)>(clockGates), std::forward<decltype(registerNames)>(registerNames), std::forward<decltype(passthroughNames)>(passthroughNames));
  auto __res__ = ::llvm::dyn_cast<StageOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

StageOp StageOp::create(::mlir::ImplicitLocOpBuilder &builder, Block*dest, ValueRange registers, ValueRange passthroughs, llvm::ArrayRef<llvm::SmallVector<Value>> clockGates, mlir::ArrayAttr registerNames, mlir::ArrayAttr passthroughNames) {
  return create(builder, builder.getLoc(), std::forward<decltype(dest)>(dest), std::forward<decltype(registers)>(registers), std::forward<decltype(passthroughs)>(passthroughs), std::forward<decltype(clockGates)>(clockGates), std::forward<decltype(registerNames)>(registerNames), std::forward<decltype(passthroughNames)>(passthroughNames));
}

::llvm::LogicalResult StageOp::verifyInvariantsImpl() {
  auto tblgen_clockGatesPerRegister = getProperties().clockGatesPerRegister; (void)tblgen_clockGatesPerRegister;
  if (!tblgen_clockGatesPerRegister) return emitOpError("requires attribute 'clockGatesPerRegister'");
  auto tblgen_passthroughNames = getProperties().passthroughNames; (void)tblgen_passthroughNames;
  auto tblgen_registerNames = getProperties().registerNames; (void)tblgen_registerNames;

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Pipeline5(*this, tblgen_clockGatesPerRegister, "clockGatesPerRegister")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Pipeline3(*this, tblgen_registerNames, "registerNames")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Pipeline3(*this, tblgen_passthroughNames, "passthroughNames")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Pipeline1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSOperands(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Pipeline1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup2 = getODSOperands(2);

    for (auto v : valueGroup2) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Pipeline5(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;
  }
  return ::mlir::success();
}

::llvm::LogicalResult StageOp::verifyInvariants() {
  if(::mlir::succeeded(verifyInvariantsImpl()) && ::mlir::succeeded(verify()))
    return ::mlir::success();
  return ::mlir::failure();
}

::mlir::ParseResult StageOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::Block *nextStageSuccessor = nullptr;
  ::llvm::SmallVector<::mlir::OpAsmParser::UnresolvedOperand, 4> registersOperands;
  ::llvm::SMLoc registersOperandsLoc;
  (void)registersOperandsLoc;
  ::llvm::SmallVector<::mlir::Type, 1> registersTypes;
  ::llvm::SmallVector<::mlir::OpAsmParser::UnresolvedOperand, 4> clockGatesOperands;
  ::llvm::SMLoc clockGatesOperandsLoc;
  (void)clockGatesOperandsLoc;
  ::mlir::ArrayAttr clockGatesPerRegisterAttr;
  ::mlir::ArrayAttr registerNamesAttr;
  ::llvm::SmallVector<::mlir::OpAsmParser::UnresolvedOperand, 4> passthroughsOperands;
  ::llvm::SMLoc passthroughsOperandsLoc;
  (void)passthroughsOperandsLoc;
  ::llvm::SmallVector<::mlir::Type, 1> passthroughsTypes;
  ::mlir::ArrayAttr passthroughNamesAttr;

  if (parser.parseSuccessor(nextStageSuccessor))
    return ::mlir::failure();
  {
    registersOperandsLoc = parser.getCurrentLocation();
    clockGatesOperandsLoc = parser.getCurrentLocation();
    auto odsResult = parseStageRegisters(parser, registersOperands, registersTypes, clockGatesOperands, clockGatesPerRegisterAttr, registerNamesAttr);
    if (odsResult) return ::mlir::failure();
    result.getOrAddProperties<StageOp::Properties>().clockGatesPerRegister = clockGatesPerRegisterAttr;
    if (registerNamesAttr)
      result.getOrAddProperties<StageOp::Properties>().registerNames = registerNamesAttr;
  }
  {
    passthroughsOperandsLoc = parser.getCurrentLocation();
    auto odsResult = parsePassthroughs(parser, passthroughsOperands, passthroughsTypes, passthroughNamesAttr);
    if (odsResult) return ::mlir::failure();
    if (passthroughNamesAttr)
      result.getOrAddProperties<StageOp::Properties>().passthroughNames = passthroughNamesAttr;
  }
  {
    auto loc = parser.getCurrentLocation();(void)loc;
    if (parser.parseOptionalAttrDict(result.attributes))
      return ::mlir::failure();
    if (failed(verifyInherentAttrs(result.name, result.attributes, [&]() {
        return parser.emitError(loc) << "'" << result.name.getStringRef() << "' op ";
      })))
      return ::mlir::failure();
  }
  result.addSuccessors(nextStageSuccessor);
::llvm::copy(::llvm::ArrayRef<int32_t>({static_cast<int32_t>(registersOperands.size()), static_cast<int32_t>(passthroughsOperands.size()), static_cast<int32_t>(clockGatesOperands.size())}), result.getOrAddProperties<StageOp::Properties>().operandSegmentSizes.begin());
  ::mlir::Type odsBuildableType0 = parser.getBuilder().getIntegerType(1);
  if (parser.resolveOperands(registersOperands, registersTypes, registersOperandsLoc, result.operands))
    return ::mlir::failure();
  if (parser.resolveOperands(passthroughsOperands, passthroughsTypes, passthroughsOperandsLoc, result.operands))
    return ::mlir::failure();
  if (parser.resolveOperands(clockGatesOperands, odsBuildableType0, clockGatesOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void StageOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter << getNextStage();
  _odsPrinter << ' ';
  printStageRegisters(_odsPrinter, *this, getRegisters(), getRegisters().getTypes(), getClockGates(), getClockGatesPerRegisterAttr(), getRegisterNamesAttr());
  _odsPrinter << ' ';
  printPassthroughs(_odsPrinter, *this, getPassthroughs(), getPassthroughs().getTypes(), getPassthroughNamesAttr());
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("operandSegmentSizes");
  elidedAttrs.push_back("clockGatesPerRegister");
  elidedAttrs.push_back("registerNames");
  elidedAttrs.push_back("passthroughNames");
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
}

void StageOp::getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects) {
}


} // namespace circt::pipeline
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::pipeline::StageOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::pipeline::detail::StageOpGenericAdaptorBase::Properties)

namespace circt::pipeline {


//===----------------------------------------------------------------------===//
// ::circt::pipeline::UnscheduledPipelineOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

UnscheduledPipelineOpGenericAdaptorBase::UnscheduledPipelineOpGenericAdaptorBase(UnscheduledPipelineOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

std::pair<unsigned, unsigned> UnscheduledPipelineOpGenericAdaptorBase::getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
  ::llvm::ArrayRef<int32_t> sizeAttr = getProperties().operandSegmentSizes;

  unsigned start = 0;
  for (unsigned i = 0; i < index; ++i)
    start += sizeAttr[i];
  return {start, sizeAttr[index]};
}

::std::optional< ::llvm::StringRef > UnscheduledPipelineOpGenericAdaptorBase::getName() {
  auto attr = getNameAttr();
  return attr ? ::std::optional< ::llvm::StringRef >(attr.getValue()) : (::std::nullopt);
}

::mlir::ArrayAttr UnscheduledPipelineOpGenericAdaptorBase::getInputNames() {
  auto attr = getInputNamesAttr();
  return attr;
}

::mlir::ArrayAttr UnscheduledPipelineOpGenericAdaptorBase::getOutputNames() {
  auto attr = getOutputNamesAttr();
  return attr;
}


} // namespace detail
UnscheduledPipelineOpAdaptor::UnscheduledPipelineOpAdaptor(UnscheduledPipelineOp op) : UnscheduledPipelineOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult UnscheduledPipelineOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_inputNames = getProperties().inputNames; (void)tblgen_inputNames;
  if (!tblgen_inputNames) return emitError(loc, "'pipeline.unscheduled' op requires attribute 'inputNames'");
  auto tblgen_name = getProperties().name; (void)tblgen_name;
  auto tblgen_outputNames = getProperties().outputNames; (void)tblgen_outputNames;
  if (!tblgen_outputNames) return emitError(loc, "'pipeline.unscheduled' op requires attribute 'outputNames'");

  if (tblgen_name && !((::llvm::isa<::mlir::StringAttr>(tblgen_name))))
    return emitError(loc, "'pipeline.unscheduled' op attribute 'name' failed to satisfy constraint: string attribute");

  if (tblgen_inputNames && !(((::llvm::isa<::mlir::ArrayAttr>(tblgen_inputNames))) && (::llvm::all_of(::llvm::cast<::mlir::ArrayAttr>(tblgen_inputNames), [&](::mlir::Attribute attr) { return attr && ((::llvm::isa<::mlir::StringAttr>(attr))); }))))
    return emitError(loc, "'pipeline.unscheduled' op attribute 'inputNames' failed to satisfy constraint: string array attribute");

  if (tblgen_outputNames && !(((::llvm::isa<::mlir::ArrayAttr>(tblgen_outputNames))) && (::llvm::all_of(::llvm::cast<::mlir::ArrayAttr>(tblgen_outputNames), [&](::mlir::Attribute attr) { return attr && ((::llvm::isa<::mlir::StringAttr>(attr))); }))))
    return emitError(loc, "'pipeline.unscheduled' op attribute 'outputNames' failed to satisfy constraint: string array attribute");
  return ::mlir::success();
}

std::pair<unsigned, unsigned> UnscheduledPipelineOp::getODSOperandIndexAndLength(unsigned index) {
  ::llvm::ArrayRef<int32_t> sizeAttr = getProperties().operandSegmentSizes;

  unsigned start = 0;
  for (unsigned i = 0; i < index; ++i)
    start += sizeAttr[i];
  return {start, sizeAttr[index]};
}

::mlir::MutableOperandRange UnscheduledPipelineOp::getInputsMutable() {
  auto range = getODSOperandIndexAndLength(0);
  auto mutableRange = ::mlir::MutableOperandRange(getOperation(), range.first, range.second, ::mlir::MutableOperandRange::OperandSegment(0u, {getOperandSegmentSizesAttrName(), ::mlir::DenseI32ArrayAttr::get(getContext(), getProperties().operandSegmentSizes)}));
  return mutableRange;
}

::mlir::MutableOperandRange UnscheduledPipelineOp::getStallMutable() {
  auto range = getODSOperandIndexAndLength(1);
  auto mutableRange = ::mlir::MutableOperandRange(getOperation(), range.first, range.second, ::mlir::MutableOperandRange::OperandSegment(1u, {getOperandSegmentSizesAttrName(), ::mlir::DenseI32ArrayAttr::get(getContext(), getProperties().operandSegmentSizes)}));
  return mutableRange;
}

::mlir::MutableOperandRange UnscheduledPipelineOp::getResetMutable() {
  auto range = getODSOperandIndexAndLength(3);
  auto mutableRange = ::mlir::MutableOperandRange(getOperation(), range.first, range.second, ::mlir::MutableOperandRange::OperandSegment(3u, {getOperandSegmentSizesAttrName(), ::mlir::DenseI32ArrayAttr::get(getContext(), getProperties().operandSegmentSizes)}));
  return mutableRange;
}

std::pair<unsigned, unsigned> UnscheduledPipelineOp::getODSResultIndexAndLength(unsigned index) {
  bool isVariadic[] = {true, false};
  int prevVariadicCount = 0;
  for (unsigned i = 0; i < index; ++i)
    if (isVariadic[i]) ++prevVariadicCount;

  // Calculate how many dynamic values a static variadic operand corresponds to.
  // This assumes all static variadic operands have the same dynamic value count.
  int variadicSize = (getOperation()->getNumResults() - 1) / 1;
  // `index` passed in as the parameter is the static index which counts each
  // operand (variadic or not) as size 1. So here for each previous static variadic
  // operand, we need to offset by (variadicSize - 1) to get where the dynamic
  // value pack for this static operand starts.
  int start = index + (variadicSize - 1) * prevVariadicCount;
  int size = isVariadic[index] ? variadicSize : 1;
  return {start, size};
}

::llvm::LogicalResult UnscheduledPipelineOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.inputNames;
       auto attr = dict.get("inputNames");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `inputNames` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.name;
       auto attr = dict.get("name");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `name` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.outputNames;
       auto attr = dict.get("outputNames");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `outputNames` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
{

      auto setFromAttr = [] (auto &propStorage, ::mlir::Attribute propAttr,
               ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) -> ::mlir::LogicalResult {
        return convertFromAttribute(propStorage, propAttr, emitError);
      };
         auto attr = dict.get("operandSegmentSizes");   if (!attr) attr = dict.get("operand_segment_sizes");;
;
      if (attr && ::mlir::failed(setFromAttr(prop.operandSegmentSizes, attr, [&]() {
            return emitError() << "for `operandSegmentSizes`: ";
          })))
        return ::mlir::failure();
  }
  return ::mlir::success();
}

::mlir::Attribute UnscheduledPipelineOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.inputNames;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("inputNames",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.name;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("name",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.outputNames;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("outputNames",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.operandSegmentSizes;
      auto attr = [&]() -> ::mlir::Attribute {
        return ::mlir::DenseI32ArrayAttr::get(ctx, propStorage);
      }();
      attrs.push_back(odsBuilder.getNamedAttr("operandSegmentSizes", attr));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code UnscheduledPipelineOp::computePropertiesHash(const Properties &prop) {
  auto hash_operandSegmentSizes_ = [] (const auto &propStorage) -> llvm::hash_code {
    using ::llvm::hash_value;
    return ::llvm::hash_combine_range(std::begin(propStorage), std::end(propStorage));;
  };
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.inputNames.getAsOpaquePointer()), 
    llvm::hash_value(prop.name.getAsOpaquePointer()), 
    llvm::hash_value(prop.outputNames.getAsOpaquePointer()), 
    hash_operandSegmentSizes_(prop.operandSegmentSizes));
}

std::optional<mlir::Attribute> UnscheduledPipelineOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "inputNames")
      return prop.inputNames;

    if (name == "name")
      return prop.name;

    if (name == "outputNames")
      return prop.outputNames;
    if (name == "operand_segment_sizes" || name == "operandSegmentSizes") return [&]() -> ::mlir::Attribute { return ::mlir::DenseI32ArrayAttr::get(ctx, prop.operandSegmentSizes); }();
  return std::nullopt;
}

void UnscheduledPipelineOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "inputNames") {
       prop.inputNames = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.inputNames)>>(value);
       return;
    }

    if (name == "name") {
       prop.name = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.name)>>(value);
       return;
    }

    if (name == "outputNames") {
       prop.outputNames = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.outputNames)>>(value);
       return;
    }
        if (name == "operand_segment_sizes" || name == "operandSegmentSizes") {
       auto arrAttr = ::llvm::dyn_cast_or_null<::mlir::DenseI32ArrayAttr>(value);
       if (!arrAttr) return;
       if (arrAttr.size() != sizeof(prop.operandSegmentSizes) / sizeof(int32_t))
         return;
       llvm::copy(arrAttr.asArrayRef(), prop.operandSegmentSizes.begin());
       return;
    }
}

void UnscheduledPipelineOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.inputNames) attrs.append("inputNames", prop.inputNames);

    if (prop.name) attrs.append("name", prop.name);

    if (prop.outputNames) attrs.append("outputNames", prop.outputNames);
  attrs.append("operandSegmentSizes", [&]() -> ::mlir::Attribute { return ::mlir::DenseI32ArrayAttr::get(ctx, prop.operandSegmentSizes); }());
}

::llvm::LogicalResult UnscheduledPipelineOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getInputNamesAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Pipeline3(attr, "inputNames", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getNameAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Pipeline2(attr, "name", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getOutputNamesAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Pipeline3(attr, "outputNames", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult UnscheduledPipelineOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.inputNames)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readOptionalAttribute(prop.name)))
    return ::mlir::failure();

  if (reader.getBytecodeVersion() < /*kNativePropertiesODSSegmentSize=*/6) {
    auto &propStorage = prop.operandSegmentSizes;
    ::mlir::DenseI32ArrayAttr attr;
    if (::mlir::failed(reader.readAttribute(attr))) return ::mlir::failure();
    if (attr.size() > static_cast<int64_t>(sizeof(propStorage) / sizeof(int32_t))) {
      reader.emitError("size mismatch for operand/result_segment_size");
      return ::mlir::failure();
    }
    ::llvm::copy(::llvm::ArrayRef<int32_t>(attr), propStorage.begin());
  }

  if (::mlir::failed(reader.readAttribute(prop.outputNames)))
    return ::mlir::failure();

  {
    auto &propStorage = prop.operandSegmentSizes;
    auto readProp = [&]() {

  if (reader.getBytecodeVersion() >= /*kNativePropertiesODSSegmentSize=*/6)
    return reader.readSparseArray(::llvm::MutableArrayRef(propStorage));
;
      return ::mlir::success();
    };
    if (::mlir::failed(readProp()))
      return ::mlir::failure();
  }
  return ::mlir::success();
}

void UnscheduledPipelineOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.inputNames);

  writer.writeOptionalAttribute(prop.name);

if (writer.getBytecodeVersion() < /*kNativePropertiesODSSegmentSize=*/6) {
  auto &propStorage = prop.operandSegmentSizes;
  writer.writeAttribute(::mlir::DenseI32ArrayAttr::get(this->getContext(), propStorage));
}
  writer.writeAttribute(prop.outputNames);

  {
    auto &propStorage = prop.operandSegmentSizes;

  if (writer.getBytecodeVersion() >= /*kNativePropertiesODSSegmentSize=*/6)
    writer.writeSparseArray(::llvm::ArrayRef(propStorage));
;
  }
}

::std::optional< ::llvm::StringRef > UnscheduledPipelineOp::getName() {
  auto attr = getNameAttr();
  return attr ? ::std::optional< ::llvm::StringRef >(attr.getValue()) : (::std::nullopt);
}

::mlir::ArrayAttr UnscheduledPipelineOp::getInputNames() {
  auto attr = getInputNamesAttr();
  return attr;
}

::mlir::ArrayAttr UnscheduledPipelineOp::getOutputNames() {
  auto attr = getOutputNamesAttr();
  return attr;
}

void UnscheduledPipelineOp::setName(::std::optional<::llvm::StringRef> attrValue) {
    auto &odsProp = getProperties().name;
    if (attrValue)
      odsProp = ::mlir::Builder((*this)->getContext()).getStringAttr(*attrValue);
    else
      odsProp = nullptr;
}

UnscheduledPipelineOp UnscheduledPipelineOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, TypeRange dataOutputs, ValueRange inputs, ArrayAttr inputNames, ArrayAttr outputNames, Value clock, Value go, Value reset, Value stall, StringAttr name, ArrayAttr stallability) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(dataOutputs)>(dataOutputs), std::forward<decltype(inputs)>(inputs), std::forward<decltype(inputNames)>(inputNames), std::forward<decltype(outputNames)>(outputNames), std::forward<decltype(clock)>(clock), std::forward<decltype(go)>(go), std::forward<decltype(reset)>(reset), std::forward<decltype(stall)>(stall), std::forward<decltype(name)>(name), std::forward<decltype(stallability)>(stallability));
  auto __res__ = ::llvm::dyn_cast<UnscheduledPipelineOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

UnscheduledPipelineOp UnscheduledPipelineOp::create(::mlir::ImplicitLocOpBuilder &builder, TypeRange dataOutputs, ValueRange inputs, ArrayAttr inputNames, ArrayAttr outputNames, Value clock, Value go, Value reset, Value stall, StringAttr name, ArrayAttr stallability) {
  return create(builder, builder.getLoc(), std::forward<decltype(dataOutputs)>(dataOutputs), std::forward<decltype(inputs)>(inputs), std::forward<decltype(inputNames)>(inputNames), std::forward<decltype(outputNames)>(outputNames), std::forward<decltype(clock)>(clock), std::forward<decltype(go)>(go), std::forward<decltype(reset)>(reset), std::forward<decltype(stall)>(stall), std::forward<decltype(name)>(name), std::forward<decltype(stallability)>(stallability));
}

::llvm::LogicalResult UnscheduledPipelineOp::verifyInvariantsImpl() {
  auto tblgen_inputNames = getProperties().inputNames; (void)tblgen_inputNames;
  if (!tblgen_inputNames) return emitOpError("requires attribute 'inputNames'");
  auto tblgen_name = getProperties().name; (void)tblgen_name;
  auto tblgen_outputNames = getProperties().outputNames; (void)tblgen_outputNames;
  if (!tblgen_outputNames) return emitOpError("requires attribute 'outputNames'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Pipeline2(*this, tblgen_name, "name")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Pipeline3(*this, tblgen_inputNames, "inputNames")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Pipeline3(*this, tblgen_outputNames, "outputNames")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Pipeline1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSOperands(1);

    if (valueGroup1.size() > 1) {
      return emitOpError("operand group starting at #") << index
          << " requires 0 or 1 element, but found " << valueGroup1.size();
    }

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Pipeline2(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup2 = getODSOperands(2);

    for (auto v : valueGroup2) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Pipeline3(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup3 = getODSOperands(3);

    if (valueGroup3.size() > 1) {
      return emitOpError("operand group starting at #") << index
          << " requires 0 or 1 element, but found " << valueGroup3.size();
    }

    for (auto v : valueGroup3) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Pipeline2(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup4 = getODSOperands(4);

    for (auto v : valueGroup4) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Pipeline2(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Pipeline1(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSResults(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Pipeline2(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;

    for (auto &region : ::llvm::MutableArrayRef((*this)->getRegion(0)))
      if (::mlir::failed(__mlir_ods_local_region_constraint_Pipeline1(*this, region, "body", index++)))
        return ::mlir::failure();
  }
  return ::mlir::success();
}

::llvm::LogicalResult UnscheduledPipelineOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::llvm::LogicalResult UnscheduledPipelineOp::setPropertiesFromParsedAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }
  // keep track of used keys in the input dictionary to be able to error out
  // if there are some unknown ones.
  ::mlir::DenseSet<::mlir::StringAttr> usedKeys;
  ::mlir::MLIRContext *ctx = dict.getContext();
  (void)ctx;
  {

    auto &propStorage = prop.name;
    auto nameAttrName = ::mlir::StringAttr::get(ctx, "name");
    auto attr = dict.get(nameAttrName);
    usedKeys.insert(nameAttrName);
    if (attr || /*isRequired=*/false) {
      if (!attr) {
        emitError() << "expected key entry for name in DictionaryAttr to set "
                   "Properties.";
        return ::mlir::failure();
      }
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `name` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  {

    auto &propStorage = prop.inputNames;
    auto inputNamesAttrName = ::mlir::StringAttr::get(ctx, "inputNames");
    auto attr = dict.get(inputNamesAttrName);
    usedKeys.insert(inputNamesAttrName);
    if (attr || /*isRequired=*/true) {
      if (!attr) {
        emitError() << "expected key entry for inputNames in DictionaryAttr to set "
                   "Properties.";
        return ::mlir::failure();
      }
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `inputNames` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  {

    auto &propStorage = prop.outputNames;
    auto outputNamesAttrName = ::mlir::StringAttr::get(ctx, "outputNames");
    auto attr = dict.get(outputNamesAttrName);
    usedKeys.insert(outputNamesAttrName);
    if (attr || /*isRequired=*/true) {
      if (!attr) {
        emitError() << "expected key entry for outputNames in DictionaryAttr to set "
                   "Properties.";
        return ::mlir::failure();
      }
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `outputNames` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  for (::mlir::NamedAttribute attr : dict) {
    if (!usedKeys.contains(attr.getName()))
      return emitError() << "unknown key '" << attr.getName() <<
          "' when parsing properties dictionary";
  }
  return ::mlir::success();
}


} // namespace circt::pipeline
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::pipeline::UnscheduledPipelineOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::pipeline::detail::UnscheduledPipelineOpGenericAdaptorBase::Properties)


#endif // GET_OP_CLASSES

