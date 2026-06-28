/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Op Definitions                                                             *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: Interop.td                                                           *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

#ifdef GET_OP_LIST
#undef GET_OP_LIST

::circt::interop::ProceduralAllocOp,
::circt::interop::ProceduralDeallocOp,
::circt::interop::ProceduralInitOp,
::circt::interop::ProceduralUpdateOp,
::circt::interop::ReturnOp
#endif // GET_OP_LIST

#ifdef GET_OP_CLASSES
#undef GET_OP_CLASSES


//===----------------------------------------------------------------------===//
// Local Utility Method Definitions
//===----------------------------------------------------------------------===//


static ::llvm::LogicalResult __mlir_ods_local_type_constraint_Interop1(
    ::mlir::Operation *op, ::mlir::Type type, ::llvm::StringRef valueKind,
    unsigned valueIndex) {
  if (!(!((::llvm::isa<::mlir::TokenType>(type))))) {
    return op->emitOpError(valueKind) << " #" << valueIndex
        << " must be variadic of any non-token type, but got " << type;
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_Interop1(
    ::mlir::Attribute attr, ::llvm::StringRef attrName, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  if (attr && !((::llvm::isa<::InteropMechanismAttr>(attr))))
    return emitError() << "attribute '" << attrName
        << "' failed to satisfy constraint: interface through which interoperability is achieved";
  return ::mlir::success();
}
static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_Interop1(
    ::mlir::Operation *op, ::mlir::Attribute attr, ::llvm::StringRef attrName) {
  return __mlir_ods_local_attr_constraint_Interop1(attr, attrName, [op]() {
    return op->emitOpError();
  });
}

static ::llvm::LogicalResult __mlir_ods_local_region_constraint_Interop1(
    ::mlir::Operation *op, ::mlir::Region &region, ::llvm::StringRef regionName,
    unsigned regionIndex) {
  if (!((::llvm::hasNItems(region, 1)))) {
    return op->emitOpError("region #") << regionIndex
        << (regionName.empty() ? " " : " ('" + regionName + "') ")
        << "failed to verify constraint: region with 1 blocks";
  }
  return ::mlir::success();
}
namespace circt::interop {


//===----------------------------------------------------------------------===//
// ::circt::interop::ProceduralAllocOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

ProceduralAllocOpGenericAdaptorBase::ProceduralAllocOpGenericAdaptorBase(ProceduralAllocOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::InteropMechanism ProceduralAllocOpGenericAdaptorBase::getInteropMechanism() {
  auto attr = getInteropMechanismAttr();
  return attr.getValue();
}


} // namespace detail
ProceduralAllocOpAdaptor::ProceduralAllocOpAdaptor(ProceduralAllocOp op) : ProceduralAllocOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult ProceduralAllocOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_interopMechanism = getProperties().interopMechanism; (void)tblgen_interopMechanism;
  if (!tblgen_interopMechanism) return emitError(loc, "'interop.procedural.alloc' op requires attribute 'interopMechanism'");

  if (tblgen_interopMechanism && !((::llvm::isa<::InteropMechanismAttr>(tblgen_interopMechanism))))
    return emitError(loc, "'interop.procedural.alloc' op attribute 'interopMechanism' failed to satisfy constraint: interface through which interoperability is achieved");
  return ::mlir::success();
}

std::pair<unsigned, unsigned> ProceduralAllocOp::getODSResultIndexAndLength(unsigned index) {
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

::llvm::LogicalResult ProceduralAllocOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.interopMechanism;
       auto attr = dict.get("interopMechanism");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `interopMechanism` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  return ::mlir::success();
}

::mlir::Attribute ProceduralAllocOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.interopMechanism;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("interopMechanism",
                                       propStorage));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code ProceduralAllocOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.interopMechanism.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> ProceduralAllocOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "interopMechanism")
      return prop.interopMechanism;
  return std::nullopt;
}

void ProceduralAllocOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "interopMechanism") {
       prop.interopMechanism = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.interopMechanism)>>(value);
       return;
    }
}

void ProceduralAllocOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.interopMechanism) attrs.append("interopMechanism", prop.interopMechanism);
}

::llvm::LogicalResult ProceduralAllocOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getInteropMechanismAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Interop1(attr, "interopMechanism", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult ProceduralAllocOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.interopMechanism)))
    return ::mlir::failure();
  return ::mlir::success();
}

void ProceduralAllocOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.interopMechanism);
}

::InteropMechanism ProceduralAllocOp::getInteropMechanism() {
  auto attr = getInteropMechanismAttr();
  return attr.getValue();
}

void ProceduralAllocOp::setInteropMechanism(::InteropMechanism attrValue) {
  getProperties().interopMechanism = ::InteropMechanismAttr::get(::mlir::Builder((*this)->getContext()).getContext(), attrValue);
}

void ProceduralAllocOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange states, ::InteropMechanismAttr interopMechanism) {
  odsState.getOrAddProperties<Properties>().interopMechanism = interopMechanism;
  odsState.addTypes(states);
}

ProceduralAllocOp ProceduralAllocOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange states, ::InteropMechanismAttr interopMechanism) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(states)>(states), std::forward<decltype(interopMechanism)>(interopMechanism));
  auto __res__ = ::llvm::dyn_cast<ProceduralAllocOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ProceduralAllocOp ProceduralAllocOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange states, ::InteropMechanismAttr interopMechanism) {
  return create(builder, builder.getLoc(), std::forward<decltype(states)>(states), std::forward<decltype(interopMechanism)>(interopMechanism));
}

void ProceduralAllocOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange states, ::InteropMechanism interopMechanism) {
  odsState.getOrAddProperties<Properties>().interopMechanism = ::InteropMechanismAttr::get(odsBuilder.getContext(), interopMechanism);
  odsState.addTypes(states);
}

ProceduralAllocOp ProceduralAllocOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange states, ::InteropMechanism interopMechanism) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(states)>(states), std::forward<decltype(interopMechanism)>(interopMechanism));
  auto __res__ = ::llvm::dyn_cast<ProceduralAllocOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ProceduralAllocOp ProceduralAllocOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange states, ::InteropMechanism interopMechanism) {
  return create(builder, builder.getLoc(), std::forward<decltype(states)>(states), std::forward<decltype(interopMechanism)>(interopMechanism));
}

void ProceduralAllocOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<ProceduralAllocOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

ProceduralAllocOp ProceduralAllocOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<ProceduralAllocOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ProceduralAllocOp ProceduralAllocOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void ProceduralAllocOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  odsState.addTypes(resultTypes);
}

ProceduralAllocOp ProceduralAllocOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<ProceduralAllocOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ProceduralAllocOp ProceduralAllocOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult ProceduralAllocOp::verifyInvariantsImpl() {
  auto tblgen_interopMechanism = getProperties().interopMechanism; (void)tblgen_interopMechanism;
  if (!tblgen_interopMechanism) return emitOpError("requires attribute 'interopMechanism'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Interop1(*this, tblgen_interopMechanism, "interopMechanism")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Interop1(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult ProceduralAllocOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult ProceduralAllocOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::InteropMechanismAttr interopMechanismAttr;
  ::llvm::SmallVector<::mlir::Type, 1> statesTypes;

  {
    ::llvm::StringRef attrStr;
    ::mlir::NamedAttrList attrStorage;
    auto loc = parser.getCurrentLocation();
    if (parser.parseOptionalKeyword(&attrStr, {"cffi","cpp"})) {
      ::mlir::StringAttr attrVal;
      ::mlir::OptionalParseResult parseResult =
        parser.parseOptionalAttribute(attrVal,
                                      parser.getBuilder().getNoneType(),
                                      "interopMechanism", attrStorage);
      if (parseResult.has_value()) {
        if (failed(*parseResult))
          return ::mlir::failure();
        attrStr = attrVal.getValue();
      } else {
        return parser.emitError(loc, "expected string or keyword containing one of the following enum values for attribute 'interopMechanism' [cffi, cpp]");
      }
    }
    if (!attrStr.empty()) {
      auto attrOptional = ::symbolizeInteropMechanism(attrStr);
      if (!attrOptional)
        return parser.emitError(loc, "invalid ")
               << "interopMechanism attribute specification: \"" << attrStr << '"';;

      interopMechanismAttr = ::InteropMechanismAttr::get(parser.getBuilder().getContext(), *attrOptional);
        result.getOrAddProperties<ProceduralAllocOp::Properties>().interopMechanism = interopMechanismAttr;
    }
  }
  if (::mlir::succeeded(parser.parseOptionalColon())) {

  if (parser.parseTypeList(statesTypes))
    return ::mlir::failure();
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
  result.addTypes(statesTypes);
  return ::mlir::success();
}

void ProceduralAllocOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';

  {
    auto caseValue = getInteropMechanism();
    auto caseValueStr = stringifyInteropMechanism(caseValue);
    _odsPrinter << caseValueStr;
  }
  if (!getStates().empty()) {
    _odsPrinter << ' ' << ":";
    _odsPrinter << ' ';
    _odsPrinter << getStates().getTypes();
  }
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("interopMechanism");
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
}


} // namespace circt::interop
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::interop::ProceduralAllocOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::interop::detail::ProceduralAllocOpGenericAdaptorBase::Properties)

namespace circt::interop {


//===----------------------------------------------------------------------===//
// ::circt::interop::ProceduralDeallocOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

ProceduralDeallocOpGenericAdaptorBase::ProceduralDeallocOpGenericAdaptorBase(ProceduralDeallocOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

std::pair<unsigned, unsigned> ProceduralDeallocOpGenericAdaptorBase::getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
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

::InteropMechanism ProceduralDeallocOpGenericAdaptorBase::getInteropMechanism() {
  auto attr = getInteropMechanismAttr();
  return attr.getValue();
}


} // namespace detail
ProceduralDeallocOpAdaptor::ProceduralDeallocOpAdaptor(ProceduralDeallocOp op) : ProceduralDeallocOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult ProceduralDeallocOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_interopMechanism = getProperties().interopMechanism; (void)tblgen_interopMechanism;
  if (!tblgen_interopMechanism) return emitError(loc, "'interop.procedural.dealloc' op requires attribute 'interopMechanism'");

  if (tblgen_interopMechanism && !((::llvm::isa<::InteropMechanismAttr>(tblgen_interopMechanism))))
    return emitError(loc, "'interop.procedural.dealloc' op attribute 'interopMechanism' failed to satisfy constraint: interface through which interoperability is achieved");
  return ::mlir::success();
}

std::pair<unsigned, unsigned> ProceduralDeallocOp::getODSOperandIndexAndLength(unsigned index) {
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

::mlir::MutableOperandRange ProceduralDeallocOp::getStatesMutable() {
  auto range = getODSOperandIndexAndLength(0);
  auto mutableRange = ::mlir::MutableOperandRange(getOperation(), range.first, range.second);
  return mutableRange;
}

::llvm::LogicalResult ProceduralDeallocOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.interopMechanism;
       auto attr = dict.get("interopMechanism");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `interopMechanism` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  return ::mlir::success();
}

::mlir::Attribute ProceduralDeallocOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.interopMechanism;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("interopMechanism",
                                       propStorage));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code ProceduralDeallocOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.interopMechanism.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> ProceduralDeallocOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "interopMechanism")
      return prop.interopMechanism;
  return std::nullopt;
}

void ProceduralDeallocOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "interopMechanism") {
       prop.interopMechanism = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.interopMechanism)>>(value);
       return;
    }
}

void ProceduralDeallocOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.interopMechanism) attrs.append("interopMechanism", prop.interopMechanism);
}

::llvm::LogicalResult ProceduralDeallocOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getInteropMechanismAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Interop1(attr, "interopMechanism", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult ProceduralDeallocOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.interopMechanism)))
    return ::mlir::failure();
  return ::mlir::success();
}

void ProceduralDeallocOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.interopMechanism);
}

::InteropMechanism ProceduralDeallocOp::getInteropMechanism() {
  auto attr = getInteropMechanismAttr();
  return attr.getValue();
}

void ProceduralDeallocOp::setInteropMechanism(::InteropMechanism attrValue) {
  getProperties().interopMechanism = ::InteropMechanismAttr::get(::mlir::Builder((*this)->getContext()).getContext(), attrValue);
}

ProceduralDeallocOp ProceduralDeallocOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ValueRange states, InteropMechanism interopMechanism) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(states)>(states), std::forward<decltype(interopMechanism)>(interopMechanism));
  auto __res__ = ::llvm::dyn_cast<ProceduralDeallocOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ProceduralDeallocOp ProceduralDeallocOp::create(::mlir::ImplicitLocOpBuilder &builder, ValueRange states, InteropMechanism interopMechanism) {
  return create(builder, builder.getLoc(), std::forward<decltype(states)>(states), std::forward<decltype(interopMechanism)>(interopMechanism));
}

::llvm::LogicalResult ProceduralDeallocOp::verifyInvariantsImpl() {
  auto tblgen_interopMechanism = getProperties().interopMechanism; (void)tblgen_interopMechanism;
  if (!tblgen_interopMechanism) return emitOpError("requires attribute 'interopMechanism'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Interop1(*this, tblgen_interopMechanism, "interopMechanism")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Interop1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;

    for (auto &region : ::llvm::MutableArrayRef((*this)->getRegion(0)))
      if (::mlir::failed(__mlir_ods_local_region_constraint_Interop1(*this, region, "deallocRegion", index++)))
        return ::mlir::failure();
  }
  return ::mlir::success();
}

::llvm::LogicalResult ProceduralDeallocOp::verifyInvariants() {
  if(::mlir::succeeded(verifyInvariantsImpl()) && ::mlir::succeeded(verify()))
    return ::mlir::success();
  return ::mlir::failure();
}

::mlir::ParseResult ProceduralDeallocOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::InteropMechanismAttr interopMechanismAttr;
  ::llvm::SmallVector<::mlir::OpAsmParser::UnresolvedOperand, 4> statesOperands;
  ::llvm::SMLoc statesOperandsLoc;
  (void)statesOperandsLoc;
  ::llvm::SmallVector<::mlir::Type, 1> statesTypes;
  std::unique_ptr<::mlir::Region> deallocRegionRegion = std::make_unique<::mlir::Region>();

  {
    ::llvm::StringRef attrStr;
    ::mlir::NamedAttrList attrStorage;
    auto loc = parser.getCurrentLocation();
    if (parser.parseOptionalKeyword(&attrStr, {"cffi","cpp"})) {
      ::mlir::StringAttr attrVal;
      ::mlir::OptionalParseResult parseResult =
        parser.parseOptionalAttribute(attrVal,
                                      parser.getBuilder().getNoneType(),
                                      "interopMechanism", attrStorage);
      if (parseResult.has_value()) {
        if (failed(*parseResult))
          return ::mlir::failure();
        attrStr = attrVal.getValue();
      } else {
        return parser.emitError(loc, "expected string or keyword containing one of the following enum values for attribute 'interopMechanism' [cffi, cpp]");
      }
    }
    if (!attrStr.empty()) {
      auto attrOptional = ::symbolizeInteropMechanism(attrStr);
      if (!attrOptional)
        return parser.emitError(loc, "invalid ")
               << "interopMechanism attribute specification: \"" << attrStr << '"';;

      interopMechanismAttr = ::InteropMechanismAttr::get(parser.getBuilder().getContext(), *attrOptional);
        result.getOrAddProperties<ProceduralDeallocOp::Properties>().interopMechanism = interopMechanismAttr;
    }
  }

  statesOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperandList(statesOperands))
    return ::mlir::failure();
  if (!statesOperands.empty()) {
  if (parser.parseColon())
    return ::mlir::failure();

  if (parser.parseTypeList(statesTypes))
    return ::mlir::failure();
  }
  {
    auto loc = parser.getCurrentLocation();(void)loc;
    if (parser.parseOptionalAttrDictWithKeyword(result.attributes))
      return ::mlir::failure();
    if (failed(verifyInherentAttrs(result.name, result.attributes, [&]() {
        return parser.emitError(loc) << "'" << result.name.getStringRef() << "' op ";
      })))
      return ::mlir::failure();
  }

  if (parser.parseRegion(*deallocRegionRegion))
    return ::mlir::failure();

  if (deallocRegionRegion->empty()) deallocRegionRegion->emplaceBlock();
  result.addRegion(std::move(deallocRegionRegion));
  if (parser.resolveOperands(statesOperands, statesTypes, statesOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void ProceduralDeallocOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';

  {
    auto caseValue = getInteropMechanism();
    auto caseValueStr = stringifyInteropMechanism(caseValue);
    _odsPrinter << caseValueStr;
  }
  if (!getStates().empty()) {
    _odsPrinter << ' ';
    _odsPrinter << getStates();
    _odsPrinter << ' ' << ":";
    _odsPrinter << ' ';
    _odsPrinter << getStates().getTypes();
  }
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("interopMechanism");
  _odsPrinter.printOptionalAttrDictWithKeyword((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ';
  _odsPrinter.printRegion(getDeallocRegion());
}


} // namespace circt::interop
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::interop::ProceduralDeallocOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::interop::detail::ProceduralDeallocOpGenericAdaptorBase::Properties)

namespace circt::interop {


//===----------------------------------------------------------------------===//
// ::circt::interop::ProceduralInitOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

ProceduralInitOpGenericAdaptorBase::ProceduralInitOpGenericAdaptorBase(ProceduralInitOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

std::pair<unsigned, unsigned> ProceduralInitOpGenericAdaptorBase::getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
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

::InteropMechanism ProceduralInitOpGenericAdaptorBase::getInteropMechanism() {
  auto attr = getInteropMechanismAttr();
  return attr.getValue();
}


} // namespace detail
ProceduralInitOpAdaptor::ProceduralInitOpAdaptor(ProceduralInitOp op) : ProceduralInitOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult ProceduralInitOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_interopMechanism = getProperties().interopMechanism; (void)tblgen_interopMechanism;
  if (!tblgen_interopMechanism) return emitError(loc, "'interop.procedural.init' op requires attribute 'interopMechanism'");

  if (tblgen_interopMechanism && !((::llvm::isa<::InteropMechanismAttr>(tblgen_interopMechanism))))
    return emitError(loc, "'interop.procedural.init' op attribute 'interopMechanism' failed to satisfy constraint: interface through which interoperability is achieved");
  return ::mlir::success();
}

std::pair<unsigned, unsigned> ProceduralInitOp::getODSOperandIndexAndLength(unsigned index) {
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

::mlir::MutableOperandRange ProceduralInitOp::getStatesMutable() {
  auto range = getODSOperandIndexAndLength(0);
  auto mutableRange = ::mlir::MutableOperandRange(getOperation(), range.first, range.second);
  return mutableRange;
}

::llvm::LogicalResult ProceduralInitOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.interopMechanism;
       auto attr = dict.get("interopMechanism");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `interopMechanism` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  return ::mlir::success();
}

::mlir::Attribute ProceduralInitOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.interopMechanism;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("interopMechanism",
                                       propStorage));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code ProceduralInitOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.interopMechanism.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> ProceduralInitOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "interopMechanism")
      return prop.interopMechanism;
  return std::nullopt;
}

void ProceduralInitOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "interopMechanism") {
       prop.interopMechanism = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.interopMechanism)>>(value);
       return;
    }
}

void ProceduralInitOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.interopMechanism) attrs.append("interopMechanism", prop.interopMechanism);
}

::llvm::LogicalResult ProceduralInitOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getInteropMechanismAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Interop1(attr, "interopMechanism", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult ProceduralInitOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.interopMechanism)))
    return ::mlir::failure();
  return ::mlir::success();
}

void ProceduralInitOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.interopMechanism);
}

::InteropMechanism ProceduralInitOp::getInteropMechanism() {
  auto attr = getInteropMechanismAttr();
  return attr.getValue();
}

void ProceduralInitOp::setInteropMechanism(::InteropMechanism attrValue) {
  getProperties().interopMechanism = ::InteropMechanismAttr::get(::mlir::Builder((*this)->getContext()).getContext(), attrValue);
}

ProceduralInitOp ProceduralInitOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ValueRange states, InteropMechanism interopMechanism) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(states)>(states), std::forward<decltype(interopMechanism)>(interopMechanism));
  auto __res__ = ::llvm::dyn_cast<ProceduralInitOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ProceduralInitOp ProceduralInitOp::create(::mlir::ImplicitLocOpBuilder &builder, ValueRange states, InteropMechanism interopMechanism) {
  return create(builder, builder.getLoc(), std::forward<decltype(states)>(states), std::forward<decltype(interopMechanism)>(interopMechanism));
}

::llvm::LogicalResult ProceduralInitOp::verifyInvariantsImpl() {
  auto tblgen_interopMechanism = getProperties().interopMechanism; (void)tblgen_interopMechanism;
  if (!tblgen_interopMechanism) return emitOpError("requires attribute 'interopMechanism'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Interop1(*this, tblgen_interopMechanism, "interopMechanism")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Interop1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;

    for (auto &region : ::llvm::MutableArrayRef((*this)->getRegion(0)))
      if (::mlir::failed(__mlir_ods_local_region_constraint_Interop1(*this, region, "initRegion", index++)))
        return ::mlir::failure();
  }
  return ::mlir::success();
}

::llvm::LogicalResult ProceduralInitOp::verifyInvariants() {
  if(::mlir::succeeded(verifyInvariantsImpl()) && ::mlir::succeeded(verify()))
    return ::mlir::success();
  return ::mlir::failure();
}

::mlir::ParseResult ProceduralInitOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::InteropMechanismAttr interopMechanismAttr;
  ::llvm::SmallVector<::mlir::OpAsmParser::UnresolvedOperand, 4> statesOperands;
  ::llvm::SMLoc statesOperandsLoc;
  (void)statesOperandsLoc;
  ::llvm::SmallVector<::mlir::Type, 1> statesTypes;
  std::unique_ptr<::mlir::Region> initRegionRegion = std::make_unique<::mlir::Region>();

  {
    ::llvm::StringRef attrStr;
    ::mlir::NamedAttrList attrStorage;
    auto loc = parser.getCurrentLocation();
    if (parser.parseOptionalKeyword(&attrStr, {"cffi","cpp"})) {
      ::mlir::StringAttr attrVal;
      ::mlir::OptionalParseResult parseResult =
        parser.parseOptionalAttribute(attrVal,
                                      parser.getBuilder().getNoneType(),
                                      "interopMechanism", attrStorage);
      if (parseResult.has_value()) {
        if (failed(*parseResult))
          return ::mlir::failure();
        attrStr = attrVal.getValue();
      } else {
        return parser.emitError(loc, "expected string or keyword containing one of the following enum values for attribute 'interopMechanism' [cffi, cpp]");
      }
    }
    if (!attrStr.empty()) {
      auto attrOptional = ::symbolizeInteropMechanism(attrStr);
      if (!attrOptional)
        return parser.emitError(loc, "invalid ")
               << "interopMechanism attribute specification: \"" << attrStr << '"';;

      interopMechanismAttr = ::InteropMechanismAttr::get(parser.getBuilder().getContext(), *attrOptional);
        result.getOrAddProperties<ProceduralInitOp::Properties>().interopMechanism = interopMechanismAttr;
    }
  }

  statesOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperandList(statesOperands))
    return ::mlir::failure();
  if (!statesOperands.empty()) {
  if (parser.parseColon())
    return ::mlir::failure();

  if (parser.parseTypeList(statesTypes))
    return ::mlir::failure();
  }
  {
    auto loc = parser.getCurrentLocation();(void)loc;
    if (parser.parseOptionalAttrDictWithKeyword(result.attributes))
      return ::mlir::failure();
    if (failed(verifyInherentAttrs(result.name, result.attributes, [&]() {
        return parser.emitError(loc) << "'" << result.name.getStringRef() << "' op ";
      })))
      return ::mlir::failure();
  }

  if (parser.parseRegion(*initRegionRegion))
    return ::mlir::failure();

  if (initRegionRegion->empty()) initRegionRegion->emplaceBlock();
  result.addRegion(std::move(initRegionRegion));
  if (parser.resolveOperands(statesOperands, statesTypes, statesOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void ProceduralInitOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';

  {
    auto caseValue = getInteropMechanism();
    auto caseValueStr = stringifyInteropMechanism(caseValue);
    _odsPrinter << caseValueStr;
  }
  if (!getStates().empty()) {
    _odsPrinter << ' ';
    _odsPrinter << getStates();
    _odsPrinter << ' ' << ":";
    _odsPrinter << ' ';
    _odsPrinter << getStates().getTypes();
  }
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("interopMechanism");
  _odsPrinter.printOptionalAttrDictWithKeyword((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ';
  _odsPrinter.printRegion(getInitRegion());
}


} // namespace circt::interop
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::interop::ProceduralInitOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::interop::detail::ProceduralInitOpGenericAdaptorBase::Properties)

namespace circt::interop {


//===----------------------------------------------------------------------===//
// ::circt::interop::ProceduralUpdateOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

ProceduralUpdateOpGenericAdaptorBase::ProceduralUpdateOpGenericAdaptorBase(ProceduralUpdateOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

std::pair<unsigned, unsigned> ProceduralUpdateOpGenericAdaptorBase::getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
  ::llvm::ArrayRef<int32_t> sizeAttr = getProperties().operandSegmentSizes;

  unsigned start = 0;
  for (unsigned i = 0; i < index; ++i)
    start += sizeAttr[i];
  return {start, sizeAttr[index]};
}

::InteropMechanism ProceduralUpdateOpGenericAdaptorBase::getInteropMechanism() {
  auto attr = getInteropMechanismAttr();
  return attr.getValue();
}


} // namespace detail
ProceduralUpdateOpAdaptor::ProceduralUpdateOpAdaptor(ProceduralUpdateOp op) : ProceduralUpdateOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult ProceduralUpdateOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_interopMechanism = getProperties().interopMechanism; (void)tblgen_interopMechanism;
  if (!tblgen_interopMechanism) return emitError(loc, "'interop.procedural.update' op requires attribute 'interopMechanism'");

  if (tblgen_interopMechanism && !((::llvm::isa<::InteropMechanismAttr>(tblgen_interopMechanism))))
    return emitError(loc, "'interop.procedural.update' op attribute 'interopMechanism' failed to satisfy constraint: interface through which interoperability is achieved");
  return ::mlir::success();
}

std::pair<unsigned, unsigned> ProceduralUpdateOp::getODSOperandIndexAndLength(unsigned index) {
  ::llvm::ArrayRef<int32_t> sizeAttr = getProperties().operandSegmentSizes;

  unsigned start = 0;
  for (unsigned i = 0; i < index; ++i)
    start += sizeAttr[i];
  return {start, sizeAttr[index]};
}

::mlir::MutableOperandRange ProceduralUpdateOp::getStatesMutable() {
  auto range = getODSOperandIndexAndLength(0);
  auto mutableRange = ::mlir::MutableOperandRange(getOperation(), range.first, range.second, ::mlir::MutableOperandRange::OperandSegment(0u, {getOperandSegmentSizesAttrName(), ::mlir::DenseI32ArrayAttr::get(getContext(), getProperties().operandSegmentSizes)}));
  return mutableRange;
}

::mlir::MutableOperandRange ProceduralUpdateOp::getInputsMutable() {
  auto range = getODSOperandIndexAndLength(1);
  auto mutableRange = ::mlir::MutableOperandRange(getOperation(), range.first, range.second, ::mlir::MutableOperandRange::OperandSegment(1u, {getOperandSegmentSizesAttrName(), ::mlir::DenseI32ArrayAttr::get(getContext(), getProperties().operandSegmentSizes)}));
  return mutableRange;
}

std::pair<unsigned, unsigned> ProceduralUpdateOp::getODSResultIndexAndLength(unsigned index) {
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

::llvm::LogicalResult ProceduralUpdateOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.interopMechanism;
       auto attr = dict.get("interopMechanism");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `interopMechanism` in property conversion: " << attr;
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

::mlir::Attribute ProceduralUpdateOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.interopMechanism;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("interopMechanism",
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

llvm::hash_code ProceduralUpdateOp::computePropertiesHash(const Properties &prop) {
  auto hash_operandSegmentSizes_ = [] (const auto &propStorage) -> llvm::hash_code {
    using ::llvm::hash_value;
    return ::llvm::hash_combine_range(std::begin(propStorage), std::end(propStorage));;
  };
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.interopMechanism.getAsOpaquePointer()), 
    hash_operandSegmentSizes_(prop.operandSegmentSizes));
}

std::optional<mlir::Attribute> ProceduralUpdateOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "interopMechanism")
      return prop.interopMechanism;
    if (name == "operand_segment_sizes" || name == "operandSegmentSizes") return [&]() -> ::mlir::Attribute { return ::mlir::DenseI32ArrayAttr::get(ctx, prop.operandSegmentSizes); }();
  return std::nullopt;
}

void ProceduralUpdateOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "interopMechanism") {
       prop.interopMechanism = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.interopMechanism)>>(value);
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

void ProceduralUpdateOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.interopMechanism) attrs.append("interopMechanism", prop.interopMechanism);
  attrs.append("operandSegmentSizes", [&]() -> ::mlir::Attribute { return ::mlir::DenseI32ArrayAttr::get(ctx, prop.operandSegmentSizes); }());
}

::llvm::LogicalResult ProceduralUpdateOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getInteropMechanismAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Interop1(attr, "interopMechanism", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult ProceduralUpdateOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.interopMechanism)))
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

void ProceduralUpdateOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.interopMechanism);

if (writer.getBytecodeVersion() < /*kNativePropertiesODSSegmentSize=*/6) {
  auto &propStorage = prop.operandSegmentSizes;
  writer.writeAttribute(::mlir::DenseI32ArrayAttr::get(this->getContext(), propStorage));
}

  {
    auto &propStorage = prop.operandSegmentSizes;

  if (writer.getBytecodeVersion() >= /*kNativePropertiesODSSegmentSize=*/6)
    writer.writeSparseArray(::llvm::ArrayRef(propStorage));
;
  }
}

::InteropMechanism ProceduralUpdateOp::getInteropMechanism() {
  auto attr = getInteropMechanismAttr();
  return attr.getValue();
}

void ProceduralUpdateOp::setInteropMechanism(::InteropMechanism attrValue) {
  getProperties().interopMechanism = ::InteropMechanismAttr::get(::mlir::Builder((*this)->getContext()).getContext(), attrValue);
}

ProceduralUpdateOp ProceduralUpdateOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, TypeRange outputs, ValueRange inputs, ValueRange states, InteropMechanism interopMechanism) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(outputs)>(outputs), std::forward<decltype(inputs)>(inputs), std::forward<decltype(states)>(states), std::forward<decltype(interopMechanism)>(interopMechanism));
  auto __res__ = ::llvm::dyn_cast<ProceduralUpdateOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ProceduralUpdateOp ProceduralUpdateOp::create(::mlir::ImplicitLocOpBuilder &builder, TypeRange outputs, ValueRange inputs, ValueRange states, InteropMechanism interopMechanism) {
  return create(builder, builder.getLoc(), std::forward<decltype(outputs)>(outputs), std::forward<decltype(inputs)>(inputs), std::forward<decltype(states)>(states), std::forward<decltype(interopMechanism)>(interopMechanism));
}

::llvm::LogicalResult ProceduralUpdateOp::verifyInvariantsImpl() {
  auto tblgen_interopMechanism = getProperties().interopMechanism; (void)tblgen_interopMechanism;
  if (!tblgen_interopMechanism) return emitOpError("requires attribute 'interopMechanism'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Interop1(*this, tblgen_interopMechanism, "interopMechanism")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Interop1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSOperands(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Interop1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Interop1(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;

    for (auto &region : ::llvm::MutableArrayRef((*this)->getRegion(0)))
      if (::mlir::failed(__mlir_ods_local_region_constraint_Interop1(*this, region, "updateRegion", index++)))
        return ::mlir::failure();
  }
  return ::mlir::success();
}

::llvm::LogicalResult ProceduralUpdateOp::verifyInvariants() {
  if(::mlir::succeeded(verifyInvariantsImpl()) && ::mlir::succeeded(verify()))
    return ::mlir::success();
  return ::mlir::failure();
}

::mlir::ParseResult ProceduralUpdateOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::InteropMechanismAttr interopMechanismAttr;
  ::llvm::SmallVector<::mlir::OpAsmParser::UnresolvedOperand, 4> statesOperands;
  ::llvm::SMLoc statesOperandsLoc;
  (void)statesOperandsLoc;
  ::llvm::SmallVector<::mlir::OpAsmParser::UnresolvedOperand, 4> inputsOperands;
  ::llvm::SMLoc inputsOperandsLoc;
  (void)inputsOperandsLoc;
  ::llvm::SmallVector<::mlir::Type, 1> statesTypes;
  ::llvm::ArrayRef<::mlir::Type> inputsTypes;
  ::llvm::ArrayRef<::mlir::Type> outputsTypes;
  std::unique_ptr<::mlir::Region> updateRegionRegion = std::make_unique<::mlir::Region>();

  {
    ::llvm::StringRef attrStr;
    ::mlir::NamedAttrList attrStorage;
    auto loc = parser.getCurrentLocation();
    if (parser.parseOptionalKeyword(&attrStr, {"cffi","cpp"})) {
      ::mlir::StringAttr attrVal;
      ::mlir::OptionalParseResult parseResult =
        parser.parseOptionalAttribute(attrVal,
                                      parser.getBuilder().getNoneType(),
                                      "interopMechanism", attrStorage);
      if (parseResult.has_value()) {
        if (failed(*parseResult))
          return ::mlir::failure();
        attrStr = attrVal.getValue();
      } else {
        return parser.emitError(loc, "expected string or keyword containing one of the following enum values for attribute 'interopMechanism' [cffi, cpp]");
      }
    }
    if (!attrStr.empty()) {
      auto attrOptional = ::symbolizeInteropMechanism(attrStr);
      if (!attrOptional)
        return parser.emitError(loc, "invalid ")
               << "interopMechanism attribute specification: \"" << attrStr << '"';;

      interopMechanismAttr = ::InteropMechanismAttr::get(parser.getBuilder().getContext(), *attrOptional);
        result.getOrAddProperties<ProceduralUpdateOp::Properties>().interopMechanism = interopMechanismAttr;
    }
  }
  if (::mlir::succeeded(parser.parseOptionalLSquare())) {

  statesOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperandList(statesOperands))
    return ::mlir::failure();
  if (parser.parseRSquare())
    return ::mlir::failure();
  }
  if (::mlir::succeeded(parser.parseOptionalLParen())) {

  inputsOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperandList(inputsOperands))
    return ::mlir::failure();
  if (parser.parseRParen())
    return ::mlir::failure();
  }
  if (parser.parseColon())
    return ::mlir::failure();
  if (::mlir::succeeded(parser.parseOptionalLSquare())) {

  if (parser.parseTypeList(statesTypes))
    return ::mlir::failure();
  if (parser.parseRSquare())
    return ::mlir::failure();
  }

  ::mlir::FunctionType inputs__outputs_functionType;
  if (parser.parseType(inputs__outputs_functionType))
    return ::mlir::failure();
  inputsTypes = inputs__outputs_functionType.getInputs();
  outputsTypes = inputs__outputs_functionType.getResults();
  {
    auto loc = parser.getCurrentLocation();(void)loc;
    if (parser.parseOptionalAttrDictWithKeyword(result.attributes))
      return ::mlir::failure();
    if (failed(verifyInherentAttrs(result.name, result.attributes, [&]() {
        return parser.emitError(loc) << "'" << result.name.getStringRef() << "' op ";
      })))
      return ::mlir::failure();
  }

  if (parser.parseRegion(*updateRegionRegion))
    return ::mlir::failure();

  if (updateRegionRegion->empty()) updateRegionRegion->emplaceBlock();
  result.addRegion(std::move(updateRegionRegion));
::llvm::copy(::llvm::ArrayRef<int32_t>({static_cast<int32_t>(statesOperands.size()), static_cast<int32_t>(inputsOperands.size())}), result.getOrAddProperties<ProceduralUpdateOp::Properties>().operandSegmentSizes.begin());
  result.addTypes(outputsTypes);
  if (parser.resolveOperands(statesOperands, statesTypes, statesOperandsLoc, result.operands))
    return ::mlir::failure();
  if (parser.resolveOperands(inputsOperands, inputsTypes, inputsOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void ProceduralUpdateOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';

  {
    auto caseValue = getInteropMechanism();
    auto caseValueStr = stringifyInteropMechanism(caseValue);
    _odsPrinter << caseValueStr;
  }
  if (!getStates().empty()) {
    _odsPrinter << ' ';
    _odsPrinter << "[";
    _odsPrinter << getStates();
    _odsPrinter << "]";
  }
  if (!getInputs().empty()) {
    _odsPrinter << ' ' << "(";
    _odsPrinter << getInputs();
    _odsPrinter << ")";
  }
  _odsPrinter << ' ' << ":";
  if (!getStates().empty()) {
    _odsPrinter << ' ' << "[";
    _odsPrinter << getStates().getTypes();
    _odsPrinter << "]";
  }
  _odsPrinter << ' ';
  _odsPrinter.printFunctionalType(getInputs().getTypes(), getOutputs().getTypes());
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("operandSegmentSizes");
  elidedAttrs.push_back("interopMechanism");
  _odsPrinter.printOptionalAttrDictWithKeyword((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ';
  _odsPrinter.printRegion(getUpdateRegion());
}


} // namespace circt::interop
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::interop::ProceduralUpdateOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::interop::detail::ProceduralUpdateOpGenericAdaptorBase::Properties)

namespace circt::interop {


//===----------------------------------------------------------------------===//
// ::circt::interop::ReturnOp definitions
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

::mlir::MutableOperandRange ReturnOp::getReturnValuesMutable() {
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
    build(odsBuilder, odsState, mlir::ValueRange());
  
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

void ReturnOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange returnValues) {
  odsState.addOperands(returnValues);
}

ReturnOp ReturnOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange returnValues) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(returnValues)>(returnValues));
  auto __res__ = ::llvm::dyn_cast<ReturnOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ReturnOp ReturnOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange returnValues) {
  return create(builder, builder.getLoc(), std::forward<decltype(returnValues)>(returnValues));
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
      if (::mlir::failed(__mlir_ods_local_type_constraint_Interop1(*this, v.getType(), "operand", index++)))
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
  ::llvm::SmallVector<::mlir::OpAsmParser::UnresolvedOperand, 4> returnValuesOperands;
  ::llvm::SMLoc returnValuesOperandsLoc;
  (void)returnValuesOperandsLoc;
  ::llvm::SmallVector<::mlir::Type, 1> returnValuesTypes;
  {
    auto loc = parser.getCurrentLocation();(void)loc;
    if (parser.parseOptionalAttrDict(result.attributes))
      return ::mlir::failure();
    if (failed(verifyInherentAttrs(result.name, result.attributes, [&]() {
        return parser.emitError(loc) << "'" << result.name.getStringRef() << "' op ";
      })))
      return ::mlir::failure();
  }

  returnValuesOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperandList(returnValuesOperands))
    return ::mlir::failure();
  if (!returnValuesOperands.empty()) {
  if (parser.parseColon())
    return ::mlir::failure();

  if (parser.parseTypeList(returnValuesTypes))
    return ::mlir::failure();
  }
  if (parser.resolveOperands(returnValuesOperands, returnValuesTypes, returnValuesOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void ReturnOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  if (!getReturnValues().empty()) {
    _odsPrinter << ' ';
    _odsPrinter << getReturnValues();
    _odsPrinter << ' ' << ":";
    _odsPrinter << ' ';
    _odsPrinter << getReturnValues().getTypes();
  }
}


} // namespace circt::interop
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::interop::ReturnOp)


#endif // GET_OP_CLASSES

