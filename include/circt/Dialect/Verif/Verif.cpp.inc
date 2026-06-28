/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Op Definitions                                                             *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: Verif.td                                                             *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

#ifdef GET_OP_LIST
#undef GET_OP_LIST

circt::verif::AssertOp,
circt::verif::AssumeOp,
circt::verif::BoundedModelCheckingOp,
circt::verif::ClockedAssertOp,
circt::verif::ClockedAssumeOp,
circt::verif::ClockedCoverOp,
circt::verif::ContractOp,
circt::verif::CoverOp,
circt::verif::EnsureOp,
circt::verif::FormalOp,
circt::verif::FormatVerilogStringOp,
circt::verif::HasBeenResetOp,
circt::verif::LogicEquivalenceCheckingOp,
circt::verif::PrintOp,
circt::verif::RefinementCheckingOp,
circt::verif::RequireOp,
circt::verif::SimulationOp,
circt::verif::SymbolicValueOp,
circt::verif::YieldOp
#endif // GET_OP_LIST

#ifdef GET_OP_CLASSES
#undef GET_OP_CLASSES


//===----------------------------------------------------------------------===//
// Local Utility Method Definitions
//===----------------------------------------------------------------------===//


static ::llvm::LogicalResult __mlir_ods_local_type_constraint_Verif1(
    ::mlir::Operation *op, ::mlir::Type type, ::llvm::StringRef valueKind,
    unsigned valueIndex) {
  if (!(((type.isSignlessInteger(1))) || ((::llvm::isa<circt::ltl::SequenceType>(type))) || ((::llvm::isa<circt::ltl::PropertyType>(type))))) {
    return op->emitOpError(valueKind) << " #" << valueIndex
        << " must be 1-bit signless integer or LTL sequence type or LTL property type, but got " << type;
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_type_constraint_Verif2(
    ::mlir::Operation *op, ::mlir::Type type, ::llvm::StringRef valueKind,
    unsigned valueIndex) {
  if (!((type.isSignlessInteger(1)))) {
    return op->emitOpError(valueKind) << " #" << valueIndex
        << " must be 1-bit signless integer, but got " << type;
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_type_constraint_Verif3(
    ::mlir::Operation *op, ::mlir::Type type, ::llvm::StringRef valueKind,
    unsigned valueIndex) {
  if (!(!((::llvm::isa<::mlir::TokenType>(type))))) {
    return op->emitOpError(valueKind) << " #" << valueIndex
        << " must be variadic of any non-token type, but got " << type;
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_type_constraint_Verif4(
    ::mlir::Operation *op, ::mlir::Type type, ::llvm::StringRef valueKind,
    unsigned valueIndex) {
  if (!((::circt::hw::type_isa<circt::hw::StringType>(type)))) {
    return op->emitOpError(valueKind) << " #" << valueIndex
        << " must be a HW string, but got " << type;
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_type_constraint_Verif5(
    ::mlir::Operation *op, ::mlir::Type type, ::llvm::StringRef valueKind,
    unsigned valueIndex) {
  if (!(!((::llvm::isa<::mlir::TokenType>(type))))) {
    return op->emitOpError(valueKind) << " #" << valueIndex
        << " must be any non-token type, but got " << type;
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_Verif1(
    ::mlir::Attribute attr, ::llvm::StringRef attrName, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  if (attr && !((::llvm::isa<::mlir::StringAttr>(attr))))
    return emitError() << "attribute '" << attrName
        << "' failed to satisfy constraint: string attribute";
  return ::mlir::success();
}
static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_Verif1(
    ::mlir::Operation *op, ::mlir::Attribute attr, ::llvm::StringRef attrName) {
  return __mlir_ods_local_attr_constraint_Verif1(attr, attrName, [op]() {
    return op->emitOpError();
  });
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_Verif2(
    ::mlir::Attribute attr, ::llvm::StringRef attrName, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  if (attr && !(((::llvm::isa<::mlir::IntegerAttr>(attr))) && ((::llvm::cast<::mlir::IntegerAttr>(attr).getType().isSignlessInteger(32)))))
    return emitError() << "attribute '" << attrName
        << "' failed to satisfy constraint: 32-bit signless integer attribute";
  return ::mlir::success();
}
static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_Verif2(
    ::mlir::Operation *op, ::mlir::Attribute attr, ::llvm::StringRef attrName) {
  return __mlir_ods_local_attr_constraint_Verif2(attr, attrName, [op]() {
    return op->emitOpError();
  });
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_Verif3(
    ::mlir::Attribute attr, ::llvm::StringRef attrName, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  if (attr && !((::llvm::isa<::mlir::ArrayAttr>(attr))))
    return emitError() << "attribute '" << attrName
        << "' failed to satisfy constraint: array attribute";
  return ::mlir::success();
}
static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_Verif3(
    ::mlir::Operation *op, ::mlir::Attribute attr, ::llvm::StringRef attrName) {
  return __mlir_ods_local_attr_constraint_Verif3(attr, attrName, [op]() {
    return op->emitOpError();
  });
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_Verif4(
    ::mlir::Attribute attr, ::llvm::StringRef attrName, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  if (attr && !((::llvm::isa<circt::verif::ClockEdgeAttr>(attr))))
    return emitError() << "attribute '" << attrName
        << "' failed to satisfy constraint: clock edge";
  return ::mlir::success();
}
static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_Verif4(
    ::mlir::Operation *op, ::mlir::Attribute attr, ::llvm::StringRef attrName) {
  return __mlir_ods_local_attr_constraint_Verif4(attr, attrName, [op]() {
    return op->emitOpError();
  });
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_Verif5(
    ::mlir::Attribute attr, ::llvm::StringRef attrName, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  if (attr && !((::llvm::isa<::mlir::DictionaryAttr>(attr))))
    return emitError() << "attribute '" << attrName
        << "' failed to satisfy constraint: dictionary of named attribute values";
  return ::mlir::success();
}
static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_Verif5(
    ::mlir::Operation *op, ::mlir::Attribute attr, ::llvm::StringRef attrName) {
  return __mlir_ods_local_attr_constraint_Verif5(attr, attrName, [op]() {
    return op->emitOpError();
  });
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_Verif6(
    ::mlir::Attribute attr, ::llvm::StringRef attrName, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  if (attr && !((::llvm::isa<::mlir::BoolAttr>(attr))))
    return emitError() << "attribute '" << attrName
        << "' failed to satisfy constraint: bool attribute";
  return ::mlir::success();
}
static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_Verif6(
    ::mlir::Operation *op, ::mlir::Attribute attr, ::llvm::StringRef attrName) {
  return __mlir_ods_local_attr_constraint_Verif6(attr, attrName, [op]() {
    return op->emitOpError();
  });
}

static ::llvm::LogicalResult __mlir_ods_local_region_constraint_Verif1(
    ::mlir::Operation *op, ::mlir::Region &region, ::llvm::StringRef regionName,
    unsigned regionIndex) {
  if (!((::llvm::hasNItems(region, 1)))) {
    return op->emitOpError("region #") << regionIndex
        << (regionName.empty() ? " " : " ('" + regionName + "') ")
        << "failed to verify constraint: region with 1 blocks";
  }
  return ::mlir::success();
}
namespace circt::verif {


//===----------------------------------------------------------------------===//
// circt::verif::AssertOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

AssertOpGenericAdaptorBase::AssertOpGenericAdaptorBase(AssertOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

std::pair<unsigned, unsigned> AssertOpGenericAdaptorBase::getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
  bool isVariadic[] = {false, true};
  int prevVariadicCount = 0;
  for (unsigned i = 0; i < index; ++i)
    if (isVariadic[i]) ++prevVariadicCount;

  // Calculate how many dynamic values a static variadic operand corresponds to.
  // This assumes all static variadic operands have the same dynamic value count.
  int variadicSize = (odsOperandsSize - 1) / 1;
  // `index` passed in as the parameter is the static index which counts each
  // operand (variadic or not) as size 1. So here for each previous static variadic
  // operand, we need to offset by (variadicSize - 1) to get where the dynamic
  // value pack for this static operand starts.
  int start = index + (variadicSize - 1) * prevVariadicCount;
  int size = isVariadic[index] ? variadicSize : 1;
  return {start, size};
}

::std::optional< ::llvm::StringRef > AssertOpGenericAdaptorBase::getLabel() {
  auto attr = getLabelAttr();
  return attr ? ::std::optional< ::llvm::StringRef >(attr.getValue()) : (::std::nullopt);
}


} // namespace detail
AssertOpAdaptor::AssertOpAdaptor(AssertOp op) : AssertOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult AssertOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_label = getProperties().label; (void)tblgen_label;

  if (tblgen_label && !((::llvm::isa<::mlir::StringAttr>(tblgen_label))))
    return emitError(loc, "'verif.assert' op attribute 'label' failed to satisfy constraint: string attribute");
  return ::mlir::success();
}

std::pair<unsigned, unsigned> AssertOp::getODSOperandIndexAndLength(unsigned index) {
  bool isVariadic[] = {false, true};
  int prevVariadicCount = 0;
  for (unsigned i = 0; i < index; ++i)
    if (isVariadic[i]) ++prevVariadicCount;

  // Calculate how many dynamic values a static variadic operand corresponds to.
  // This assumes all static variadic operands have the same dynamic value count.
  int variadicSize = (getOperation()->getNumOperands() - 1) / 1;
  // `index` passed in as the parameter is the static index which counts each
  // operand (variadic or not) as size 1. So here for each previous static variadic
  // operand, we need to offset by (variadicSize - 1) to get where the dynamic
  // value pack for this static operand starts.
  int start = index + (variadicSize - 1) * prevVariadicCount;
  int size = isVariadic[index] ? variadicSize : 1;
  return {start, size};
}

::mlir::MutableOperandRange AssertOp::getEnableMutable() {
  auto range = getODSOperandIndexAndLength(1);
  auto mutableRange = ::mlir::MutableOperandRange(getOperation(), range.first, range.second);
  return mutableRange;
}

::llvm::LogicalResult AssertOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.label;
       auto attr = dict.get("label");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `label` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  return ::mlir::success();
}

::mlir::Attribute AssertOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.label;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("label",
                                       propStorage));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code AssertOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.label.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> AssertOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "label")
      return prop.label;
  return std::nullopt;
}

void AssertOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "label") {
       prop.label = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.label)>>(value);
       return;
    }
}

void AssertOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.label) attrs.append("label", prop.label);
}

::llvm::LogicalResult AssertOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getLabelAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Verif1(attr, "label", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult AssertOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readOptionalAttribute(prop.label)))
    return ::mlir::failure();
  return ::mlir::success();
}

void AssertOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;

  writer.writeOptionalAttribute(prop.label);
}

::std::optional< ::llvm::StringRef > AssertOp::getLabel() {
  auto attr = getLabelAttr();
  return attr ? ::std::optional< ::llvm::StringRef >(attr.getValue()) : (::std::nullopt);
}

void AssertOp::setLabel(::std::optional<::llvm::StringRef> attrValue) {
    auto &odsProp = getProperties().label;
    if (attrValue)
      odsProp = ::mlir::Builder((*this)->getContext()).getStringAttr(*attrValue);
    else
      odsProp = nullptr;
}

void AssertOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value property, /*optional*/::mlir::Value enable, /*optional*/::mlir::StringAttr label) {
  odsState.addOperands(property);
  if (enable)
    odsState.addOperands(enable);
  if (label) {
    odsState.getOrAddProperties<Properties>().label = label;
  }
}

AssertOp AssertOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value property, /*optional*/::mlir::Value enable, /*optional*/::mlir::StringAttr label) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(property)>(property), std::forward<decltype(enable)>(enable), std::forward<decltype(label)>(label));
  auto __res__ = ::llvm::dyn_cast<AssertOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

AssertOp AssertOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value property, /*optional*/::mlir::Value enable, /*optional*/::mlir::StringAttr label) {
  return create(builder, builder.getLoc(), std::forward<decltype(property)>(property), std::forward<decltype(enable)>(enable), std::forward<decltype(label)>(label));
}

void AssertOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value property, /*optional*/::mlir::Value enable, /*optional*/::mlir::StringAttr label) {
  odsState.addOperands(property);
  if (enable)
    odsState.addOperands(enable);
  if (label) {
    odsState.getOrAddProperties<Properties>().label = label;
  }
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

AssertOp AssertOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value property, /*optional*/::mlir::Value enable, /*optional*/::mlir::StringAttr label) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(property)>(property), std::forward<decltype(enable)>(enable), std::forward<decltype(label)>(label));
  auto __res__ = ::llvm::dyn_cast<AssertOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

AssertOp AssertOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value property, /*optional*/::mlir::Value enable, /*optional*/::mlir::StringAttr label) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(property)>(property), std::forward<decltype(enable)>(enable), std::forward<decltype(label)>(label));
}

void AssertOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() >= 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<AssertOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

AssertOp AssertOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<AssertOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

AssertOp AssertOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void AssertOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() >= 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

AssertOp AssertOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<AssertOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

AssertOp AssertOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult AssertOp::verifyInvariantsImpl() {
  auto tblgen_label = getProperties().label; (void)tblgen_label;

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Verif1(*this, tblgen_label, "label")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Verif1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSOperands(1);

    if (valueGroup1.size() > 1) {
      return emitOpError("operand group starting at #") << index
          << " requires 0 or 1 element, but found " << valueGroup1.size();
    }

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Verif2(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult AssertOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult AssertOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::OpAsmParser::UnresolvedOperand propertyRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> propertyOperands(&propertyRawOperand, 1);  ::llvm::SMLoc propertyOperandsLoc;
  (void)propertyOperandsLoc;
  ::llvm::SmallVector<::mlir::OpAsmParser::UnresolvedOperand, 4> enableOperands;
  ::llvm::SMLoc enableOperandsLoc;
  (void)enableOperandsLoc;
  ::mlir::StringAttr labelAttr;
  ::mlir::Type propertyRawType{};
  ::llvm::ArrayRef<::mlir::Type> propertyTypes(&propertyRawType, 1);

  propertyOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(propertyRawOperand))
    return ::mlir::failure();
  if (::mlir::succeeded(parser.parseOptionalKeyword("if"))) {

  {
    enableOperandsLoc = parser.getCurrentLocation();
    ::mlir::OpAsmParser::UnresolvedOperand operand;
    ::mlir::OptionalParseResult parseResult =
                                    parser.parseOptionalOperand(operand);
    if (parseResult.has_value()) {
      if (failed(*parseResult))
        return ::mlir::failure();
      enableOperands.push_back(operand);
    }
  }
  }
  if (::mlir::succeeded(parser.parseOptionalKeyword("label"))) {

  if (parser.parseCustomAttributeWithFallback(labelAttr, parser.getBuilder().getType<::mlir::NoneType>())) {
    return ::mlir::failure();
  }
  if (labelAttr) result.getOrAddProperties<AssertOp::Properties>().label = labelAttr;
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
  if (parser.parseColon())
    return ::mlir::failure();

  {
    ::mlir::Type type;
    if (parser.parseCustomTypeWithFallback(type))
      return ::mlir::failure();
    propertyRawType = type;
  }
  ::mlir::Type odsBuildableType0 = parser.getBuilder().getIntegerType(1);
  if (parser.resolveOperands(propertyOperands, propertyTypes, propertyOperandsLoc, result.operands))
    return ::mlir::failure();
  if (!enableOperands.empty()) {
  if (parser.resolveOperands(enableOperands, odsBuildableType0, enableOperandsLoc, result.operands))
    return ::mlir::failure();
  }
  return ::mlir::success();
}

void AssertOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter << getProperty();
  if (getEnable()) {
    _odsPrinter << ' ' << "if";
    _odsPrinter << ' ';
    if (::mlir::Value value = getEnable())
      _odsPrinter << value;
  }
  if (getLabelAttr()) {
    _odsPrinter << ' ' << "label";
    _odsPrinter << ' ';
    _odsPrinter.printAttributeWithoutType(getLabelAttr());
  }
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("label");
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
  {
    auto type = getProperty().getType();
    if (auto validType = ::llvm::dyn_cast<::mlir::Type>(type))
      _odsPrinter.printStrippedAttrOrType(validType);
   else
     _odsPrinter << type;
  }
}


} // namespace circt::verif
MLIR_DEFINE_EXPLICIT_TYPE_ID(circt::verif::AssertOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(circt::verif::detail::AssertOpGenericAdaptorBase::Properties)

namespace circt::verif {


//===----------------------------------------------------------------------===//
// circt::verif::AssumeOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

AssumeOpGenericAdaptorBase::AssumeOpGenericAdaptorBase(AssumeOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

std::pair<unsigned, unsigned> AssumeOpGenericAdaptorBase::getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
  bool isVariadic[] = {false, true};
  int prevVariadicCount = 0;
  for (unsigned i = 0; i < index; ++i)
    if (isVariadic[i]) ++prevVariadicCount;

  // Calculate how many dynamic values a static variadic operand corresponds to.
  // This assumes all static variadic operands have the same dynamic value count.
  int variadicSize = (odsOperandsSize - 1) / 1;
  // `index` passed in as the parameter is the static index which counts each
  // operand (variadic or not) as size 1. So here for each previous static variadic
  // operand, we need to offset by (variadicSize - 1) to get where the dynamic
  // value pack for this static operand starts.
  int start = index + (variadicSize - 1) * prevVariadicCount;
  int size = isVariadic[index] ? variadicSize : 1;
  return {start, size};
}

::std::optional< ::llvm::StringRef > AssumeOpGenericAdaptorBase::getLabel() {
  auto attr = getLabelAttr();
  return attr ? ::std::optional< ::llvm::StringRef >(attr.getValue()) : (::std::nullopt);
}


} // namespace detail
AssumeOpAdaptor::AssumeOpAdaptor(AssumeOp op) : AssumeOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult AssumeOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_label = getProperties().label; (void)tblgen_label;

  if (tblgen_label && !((::llvm::isa<::mlir::StringAttr>(tblgen_label))))
    return emitError(loc, "'verif.assume' op attribute 'label' failed to satisfy constraint: string attribute");
  return ::mlir::success();
}

std::pair<unsigned, unsigned> AssumeOp::getODSOperandIndexAndLength(unsigned index) {
  bool isVariadic[] = {false, true};
  int prevVariadicCount = 0;
  for (unsigned i = 0; i < index; ++i)
    if (isVariadic[i]) ++prevVariadicCount;

  // Calculate how many dynamic values a static variadic operand corresponds to.
  // This assumes all static variadic operands have the same dynamic value count.
  int variadicSize = (getOperation()->getNumOperands() - 1) / 1;
  // `index` passed in as the parameter is the static index which counts each
  // operand (variadic or not) as size 1. So here for each previous static variadic
  // operand, we need to offset by (variadicSize - 1) to get where the dynamic
  // value pack for this static operand starts.
  int start = index + (variadicSize - 1) * prevVariadicCount;
  int size = isVariadic[index] ? variadicSize : 1;
  return {start, size};
}

::mlir::MutableOperandRange AssumeOp::getEnableMutable() {
  auto range = getODSOperandIndexAndLength(1);
  auto mutableRange = ::mlir::MutableOperandRange(getOperation(), range.first, range.second);
  return mutableRange;
}

::llvm::LogicalResult AssumeOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.label;
       auto attr = dict.get("label");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `label` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  return ::mlir::success();
}

::mlir::Attribute AssumeOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.label;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("label",
                                       propStorage));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code AssumeOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.label.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> AssumeOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "label")
      return prop.label;
  return std::nullopt;
}

void AssumeOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "label") {
       prop.label = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.label)>>(value);
       return;
    }
}

void AssumeOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.label) attrs.append("label", prop.label);
}

::llvm::LogicalResult AssumeOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getLabelAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Verif1(attr, "label", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult AssumeOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readOptionalAttribute(prop.label)))
    return ::mlir::failure();
  return ::mlir::success();
}

void AssumeOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;

  writer.writeOptionalAttribute(prop.label);
}

::std::optional< ::llvm::StringRef > AssumeOp::getLabel() {
  auto attr = getLabelAttr();
  return attr ? ::std::optional< ::llvm::StringRef >(attr.getValue()) : (::std::nullopt);
}

void AssumeOp::setLabel(::std::optional<::llvm::StringRef> attrValue) {
    auto &odsProp = getProperties().label;
    if (attrValue)
      odsProp = ::mlir::Builder((*this)->getContext()).getStringAttr(*attrValue);
    else
      odsProp = nullptr;
}

void AssumeOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value property, /*optional*/::mlir::Value enable, /*optional*/::mlir::StringAttr label) {
  odsState.addOperands(property);
  if (enable)
    odsState.addOperands(enable);
  if (label) {
    odsState.getOrAddProperties<Properties>().label = label;
  }
}

AssumeOp AssumeOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value property, /*optional*/::mlir::Value enable, /*optional*/::mlir::StringAttr label) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(property)>(property), std::forward<decltype(enable)>(enable), std::forward<decltype(label)>(label));
  auto __res__ = ::llvm::dyn_cast<AssumeOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

AssumeOp AssumeOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value property, /*optional*/::mlir::Value enable, /*optional*/::mlir::StringAttr label) {
  return create(builder, builder.getLoc(), std::forward<decltype(property)>(property), std::forward<decltype(enable)>(enable), std::forward<decltype(label)>(label));
}

void AssumeOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value property, /*optional*/::mlir::Value enable, /*optional*/::mlir::StringAttr label) {
  odsState.addOperands(property);
  if (enable)
    odsState.addOperands(enable);
  if (label) {
    odsState.getOrAddProperties<Properties>().label = label;
  }
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

AssumeOp AssumeOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value property, /*optional*/::mlir::Value enable, /*optional*/::mlir::StringAttr label) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(property)>(property), std::forward<decltype(enable)>(enable), std::forward<decltype(label)>(label));
  auto __res__ = ::llvm::dyn_cast<AssumeOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

AssumeOp AssumeOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value property, /*optional*/::mlir::Value enable, /*optional*/::mlir::StringAttr label) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(property)>(property), std::forward<decltype(enable)>(enable), std::forward<decltype(label)>(label));
}

void AssumeOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() >= 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<AssumeOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

AssumeOp AssumeOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<AssumeOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

AssumeOp AssumeOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void AssumeOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() >= 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

AssumeOp AssumeOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<AssumeOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

AssumeOp AssumeOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult AssumeOp::verifyInvariantsImpl() {
  auto tblgen_label = getProperties().label; (void)tblgen_label;

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Verif1(*this, tblgen_label, "label")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Verif1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSOperands(1);

    if (valueGroup1.size() > 1) {
      return emitOpError("operand group starting at #") << index
          << " requires 0 or 1 element, but found " << valueGroup1.size();
    }

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Verif2(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult AssumeOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult AssumeOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::OpAsmParser::UnresolvedOperand propertyRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> propertyOperands(&propertyRawOperand, 1);  ::llvm::SMLoc propertyOperandsLoc;
  (void)propertyOperandsLoc;
  ::llvm::SmallVector<::mlir::OpAsmParser::UnresolvedOperand, 4> enableOperands;
  ::llvm::SMLoc enableOperandsLoc;
  (void)enableOperandsLoc;
  ::mlir::StringAttr labelAttr;
  ::mlir::Type propertyRawType{};
  ::llvm::ArrayRef<::mlir::Type> propertyTypes(&propertyRawType, 1);

  propertyOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(propertyRawOperand))
    return ::mlir::failure();
  if (::mlir::succeeded(parser.parseOptionalKeyword("if"))) {

  {
    enableOperandsLoc = parser.getCurrentLocation();
    ::mlir::OpAsmParser::UnresolvedOperand operand;
    ::mlir::OptionalParseResult parseResult =
                                    parser.parseOptionalOperand(operand);
    if (parseResult.has_value()) {
      if (failed(*parseResult))
        return ::mlir::failure();
      enableOperands.push_back(operand);
    }
  }
  }
  if (::mlir::succeeded(parser.parseOptionalKeyword("label"))) {

  if (parser.parseCustomAttributeWithFallback(labelAttr, parser.getBuilder().getType<::mlir::NoneType>())) {
    return ::mlir::failure();
  }
  if (labelAttr) result.getOrAddProperties<AssumeOp::Properties>().label = labelAttr;
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
  if (parser.parseColon())
    return ::mlir::failure();

  {
    ::mlir::Type type;
    if (parser.parseCustomTypeWithFallback(type))
      return ::mlir::failure();
    propertyRawType = type;
  }
  ::mlir::Type odsBuildableType0 = parser.getBuilder().getIntegerType(1);
  if (parser.resolveOperands(propertyOperands, propertyTypes, propertyOperandsLoc, result.operands))
    return ::mlir::failure();
  if (!enableOperands.empty()) {
  if (parser.resolveOperands(enableOperands, odsBuildableType0, enableOperandsLoc, result.operands))
    return ::mlir::failure();
  }
  return ::mlir::success();
}

void AssumeOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter << getProperty();
  if (getEnable()) {
    _odsPrinter << ' ' << "if";
    _odsPrinter << ' ';
    if (::mlir::Value value = getEnable())
      _odsPrinter << value;
  }
  if (getLabelAttr()) {
    _odsPrinter << ' ' << "label";
    _odsPrinter << ' ';
    _odsPrinter.printAttributeWithoutType(getLabelAttr());
  }
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("label");
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
  {
    auto type = getProperty().getType();
    if (auto validType = ::llvm::dyn_cast<::mlir::Type>(type))
      _odsPrinter.printStrippedAttrOrType(validType);
   else
     _odsPrinter << type;
  }
}


} // namespace circt::verif
MLIR_DEFINE_EXPLICIT_TYPE_ID(circt::verif::AssumeOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(circt::verif::detail::AssumeOpGenericAdaptorBase::Properties)

namespace circt::verif {


//===----------------------------------------------------------------------===//
// circt::verif::BoundedModelCheckingOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

BoundedModelCheckingOpGenericAdaptorBase::BoundedModelCheckingOpGenericAdaptorBase(BoundedModelCheckingOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

uint32_t BoundedModelCheckingOpGenericAdaptorBase::getBound() {
  auto attr = getBoundAttr();
  return attr.getValue().getZExtValue();
}

uint32_t BoundedModelCheckingOpGenericAdaptorBase::getNumRegs() {
  auto attr = getNumRegsAttr();
  return attr.getValue().getZExtValue();
}

::mlir::ArrayAttr BoundedModelCheckingOpGenericAdaptorBase::getInitialValues() {
  auto attr = getInitialValuesAttr();
  return attr;
}


} // namespace detail
BoundedModelCheckingOpAdaptor::BoundedModelCheckingOpAdaptor(BoundedModelCheckingOp op) : BoundedModelCheckingOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult BoundedModelCheckingOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_bound = getProperties().bound; (void)tblgen_bound;
  if (!tblgen_bound) return emitError(loc, "'verif.bmc' op requires attribute 'bound'");
  auto tblgen_initial_values = getProperties().initial_values; (void)tblgen_initial_values;
  if (!tblgen_initial_values) return emitError(loc, "'verif.bmc' op requires attribute 'initial_values'");
  auto tblgen_num_regs = getProperties().num_regs; (void)tblgen_num_regs;
  if (!tblgen_num_regs) return emitError(loc, "'verif.bmc' op requires attribute 'num_regs'");

  if (tblgen_bound && !(((::llvm::isa<::mlir::IntegerAttr>(tblgen_bound))) && ((::llvm::cast<::mlir::IntegerAttr>(tblgen_bound).getType().isSignlessInteger(32)))))
    return emitError(loc, "'verif.bmc' op attribute 'bound' failed to satisfy constraint: 32-bit signless integer attribute");

  if (tblgen_num_regs && !(((::llvm::isa<::mlir::IntegerAttr>(tblgen_num_regs))) && ((::llvm::cast<::mlir::IntegerAttr>(tblgen_num_regs).getType().isSignlessInteger(32)))))
    return emitError(loc, "'verif.bmc' op attribute 'num_regs' failed to satisfy constraint: 32-bit signless integer attribute");

  if (tblgen_initial_values && !((::llvm::isa<::mlir::ArrayAttr>(tblgen_initial_values))))
    return emitError(loc, "'verif.bmc' op attribute 'initial_values' failed to satisfy constraint: array attribute");
  return ::mlir::success();
}

::llvm::LogicalResult BoundedModelCheckingOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.bound;
       auto attr = dict.get("bound");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `bound` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.initial_values;
       auto attr = dict.get("initial_values");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `initial_values` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.num_regs;
       auto attr = dict.get("num_regs");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `num_regs` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  return ::mlir::success();
}

::mlir::Attribute BoundedModelCheckingOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.bound;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("bound",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.initial_values;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("initial_values",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.num_regs;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("num_regs",
                                       propStorage));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code BoundedModelCheckingOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.bound.getAsOpaquePointer()), 
    llvm::hash_value(prop.initial_values.getAsOpaquePointer()), 
    llvm::hash_value(prop.num_regs.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> BoundedModelCheckingOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "bound")
      return prop.bound;

    if (name == "initial_values")
      return prop.initial_values;

    if (name == "num_regs")
      return prop.num_regs;
  return std::nullopt;
}

void BoundedModelCheckingOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "bound") {
       prop.bound = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.bound)>>(value);
       return;
    }

    if (name == "initial_values") {
       prop.initial_values = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.initial_values)>>(value);
       return;
    }

    if (name == "num_regs") {
       prop.num_regs = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.num_regs)>>(value);
       return;
    }
}

void BoundedModelCheckingOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.bound) attrs.append("bound", prop.bound);

    if (prop.initial_values) attrs.append("initial_values", prop.initial_values);

    if (prop.num_regs) attrs.append("num_regs", prop.num_regs);
}

::llvm::LogicalResult BoundedModelCheckingOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getBoundAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Verif2(attr, "bound", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getInitialValuesAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Verif3(attr, "initial_values", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getNumRegsAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Verif2(attr, "num_regs", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult BoundedModelCheckingOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.bound)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readAttribute(prop.initial_values)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readAttribute(prop.num_regs)))
    return ::mlir::failure();
  return ::mlir::success();
}

void BoundedModelCheckingOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.bound);
  writer.writeAttribute(prop.initial_values);
  writer.writeAttribute(prop.num_regs);
}

uint32_t BoundedModelCheckingOp::getBound() {
  auto attr = getBoundAttr();
  return attr.getValue().getZExtValue();
}

uint32_t BoundedModelCheckingOp::getNumRegs() {
  auto attr = getNumRegsAttr();
  return attr.getValue().getZExtValue();
}

::mlir::ArrayAttr BoundedModelCheckingOp::getInitialValues() {
  auto attr = getInitialValuesAttr();
  return attr;
}

void BoundedModelCheckingOp::setBound(uint32_t attrValue) {
  getProperties().bound = ::mlir::Builder((*this)->getContext()).getIntegerAttr(::mlir::Builder((*this)->getContext()).getIntegerType(32), attrValue);
}

void BoundedModelCheckingOp::setNumRegs(uint32_t attrValue) {
  getProperties().num_regs = ::mlir::Builder((*this)->getContext()).getIntegerAttr(::mlir::Builder((*this)->getContext()).getIntegerType(32), attrValue);
}

void BoundedModelCheckingOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::IntegerAttr bound, ::mlir::IntegerAttr num_regs, ::mlir::ArrayAttr initial_values) {
  odsState.getOrAddProperties<Properties>().bound = bound;
  odsState.getOrAddProperties<Properties>().num_regs = num_regs;
  odsState.getOrAddProperties<Properties>().initial_values = initial_values;
  (void)odsState.addRegion();
  (void)odsState.addRegion();
  (void)odsState.addRegion();
  odsState.addTypes(result);
}

BoundedModelCheckingOp BoundedModelCheckingOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::IntegerAttr bound, ::mlir::IntegerAttr num_regs, ::mlir::ArrayAttr initial_values) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(result)>(result), std::forward<decltype(bound)>(bound), std::forward<decltype(num_regs)>(num_regs), std::forward<decltype(initial_values)>(initial_values));
  auto __res__ = ::llvm::dyn_cast<BoundedModelCheckingOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

BoundedModelCheckingOp BoundedModelCheckingOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::IntegerAttr bound, ::mlir::IntegerAttr num_regs, ::mlir::ArrayAttr initial_values) {
  return create(builder, builder.getLoc(), std::forward<decltype(result)>(result), std::forward<decltype(bound)>(bound), std::forward<decltype(num_regs)>(num_regs), std::forward<decltype(initial_values)>(initial_values));
}

void BoundedModelCheckingOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::IntegerAttr bound, ::mlir::IntegerAttr num_regs, ::mlir::ArrayAttr initial_values) {
  odsState.getOrAddProperties<Properties>().bound = bound;
  odsState.getOrAddProperties<Properties>().num_regs = num_regs;
  odsState.getOrAddProperties<Properties>().initial_values = initial_values;
  (void)odsState.addRegion();
  (void)odsState.addRegion();
  (void)odsState.addRegion();

        ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
        if (::mlir::succeeded(BoundedModelCheckingOp::inferReturnTypes(odsBuilder.getContext(),
                      odsState.location, odsState.operands,
                      odsState.attributes.getDictionary(odsState.getContext()),
                      odsState.getRawProperties(),
                      odsState.regions, inferredReturnTypes)))
          odsState.addTypes(inferredReturnTypes);
        else
          ::mlir::detail::reportFatalInferReturnTypesError(odsState);
        
}

BoundedModelCheckingOp BoundedModelCheckingOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::IntegerAttr bound, ::mlir::IntegerAttr num_regs, ::mlir::ArrayAttr initial_values) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(bound)>(bound), std::forward<decltype(num_regs)>(num_regs), std::forward<decltype(initial_values)>(initial_values));
  auto __res__ = ::llvm::dyn_cast<BoundedModelCheckingOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

BoundedModelCheckingOp BoundedModelCheckingOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::IntegerAttr bound, ::mlir::IntegerAttr num_regs, ::mlir::ArrayAttr initial_values) {
  return create(builder, builder.getLoc(), std::forward<decltype(bound)>(bound), std::forward<decltype(num_regs)>(num_regs), std::forward<decltype(initial_values)>(initial_values));
}

void BoundedModelCheckingOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::IntegerAttr bound, ::mlir::IntegerAttr num_regs, ::mlir::ArrayAttr initial_values) {
  odsState.getOrAddProperties<Properties>().bound = bound;
  odsState.getOrAddProperties<Properties>().num_regs = num_regs;
  odsState.getOrAddProperties<Properties>().initial_values = initial_values;
  (void)odsState.addRegion();
  (void)odsState.addRegion();
  (void)odsState.addRegion();
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

BoundedModelCheckingOp BoundedModelCheckingOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::IntegerAttr bound, ::mlir::IntegerAttr num_regs, ::mlir::ArrayAttr initial_values) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(bound)>(bound), std::forward<decltype(num_regs)>(num_regs), std::forward<decltype(initial_values)>(initial_values));
  auto __res__ = ::llvm::dyn_cast<BoundedModelCheckingOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

BoundedModelCheckingOp BoundedModelCheckingOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::IntegerAttr bound, ::mlir::IntegerAttr num_regs, ::mlir::ArrayAttr initial_values) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(bound)>(bound), std::forward<decltype(num_regs)>(num_regs), std::forward<decltype(initial_values)>(initial_values));
}

void BoundedModelCheckingOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, uint32_t bound, uint32_t num_regs, ::mlir::ArrayAttr initial_values) {
  odsState.getOrAddProperties<Properties>().bound = odsBuilder.getIntegerAttr(odsBuilder.getIntegerType(32), bound);
  odsState.getOrAddProperties<Properties>().num_regs = odsBuilder.getIntegerAttr(odsBuilder.getIntegerType(32), num_regs);
  odsState.getOrAddProperties<Properties>().initial_values = initial_values;
  (void)odsState.addRegion();
  (void)odsState.addRegion();
  (void)odsState.addRegion();
  odsState.addTypes(result);
}

BoundedModelCheckingOp BoundedModelCheckingOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, uint32_t bound, uint32_t num_regs, ::mlir::ArrayAttr initial_values) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(result)>(result), std::forward<decltype(bound)>(bound), std::forward<decltype(num_regs)>(num_regs), std::forward<decltype(initial_values)>(initial_values));
  auto __res__ = ::llvm::dyn_cast<BoundedModelCheckingOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

BoundedModelCheckingOp BoundedModelCheckingOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, uint32_t bound, uint32_t num_regs, ::mlir::ArrayAttr initial_values) {
  return create(builder, builder.getLoc(), std::forward<decltype(result)>(result), std::forward<decltype(bound)>(bound), std::forward<decltype(num_regs)>(num_regs), std::forward<decltype(initial_values)>(initial_values));
}

void BoundedModelCheckingOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, uint32_t bound, uint32_t num_regs, ::mlir::ArrayAttr initial_values) {
  odsState.getOrAddProperties<Properties>().bound = odsBuilder.getIntegerAttr(odsBuilder.getIntegerType(32), bound);
  odsState.getOrAddProperties<Properties>().num_regs = odsBuilder.getIntegerAttr(odsBuilder.getIntegerType(32), num_regs);
  odsState.getOrAddProperties<Properties>().initial_values = initial_values;
  (void)odsState.addRegion();
  (void)odsState.addRegion();
  (void)odsState.addRegion();

        ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
        if (::mlir::succeeded(BoundedModelCheckingOp::inferReturnTypes(odsBuilder.getContext(),
                      odsState.location, odsState.operands,
                      odsState.attributes.getDictionary(odsState.getContext()),
                      odsState.getRawProperties(),
                      odsState.regions, inferredReturnTypes)))
          odsState.addTypes(inferredReturnTypes);
        else
          ::mlir::detail::reportFatalInferReturnTypesError(odsState);
        
}

BoundedModelCheckingOp BoundedModelCheckingOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, uint32_t bound, uint32_t num_regs, ::mlir::ArrayAttr initial_values) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(bound)>(bound), std::forward<decltype(num_regs)>(num_regs), std::forward<decltype(initial_values)>(initial_values));
  auto __res__ = ::llvm::dyn_cast<BoundedModelCheckingOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

BoundedModelCheckingOp BoundedModelCheckingOp::create(::mlir::ImplicitLocOpBuilder &builder, uint32_t bound, uint32_t num_regs, ::mlir::ArrayAttr initial_values) {
  return create(builder, builder.getLoc(), std::forward<decltype(bound)>(bound), std::forward<decltype(num_regs)>(num_regs), std::forward<decltype(initial_values)>(initial_values));
}

void BoundedModelCheckingOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, uint32_t bound, uint32_t num_regs, ::mlir::ArrayAttr initial_values) {
  odsState.getOrAddProperties<Properties>().bound = odsBuilder.getIntegerAttr(odsBuilder.getIntegerType(32), bound);
  odsState.getOrAddProperties<Properties>().num_regs = odsBuilder.getIntegerAttr(odsBuilder.getIntegerType(32), num_regs);
  odsState.getOrAddProperties<Properties>().initial_values = initial_values;
  (void)odsState.addRegion();
  (void)odsState.addRegion();
  (void)odsState.addRegion();
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

BoundedModelCheckingOp BoundedModelCheckingOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, uint32_t bound, uint32_t num_regs, ::mlir::ArrayAttr initial_values) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(bound)>(bound), std::forward<decltype(num_regs)>(num_regs), std::forward<decltype(initial_values)>(initial_values));
  auto __res__ = ::llvm::dyn_cast<BoundedModelCheckingOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

BoundedModelCheckingOp BoundedModelCheckingOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, uint32_t bound, uint32_t num_regs, ::mlir::ArrayAttr initial_values) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(bound)>(bound), std::forward<decltype(num_regs)>(num_regs), std::forward<decltype(initial_values)>(initial_values));
}

void BoundedModelCheckingOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  for (unsigned i = 0; i != 3; ++i)
    (void)odsState.addRegion();
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<BoundedModelCheckingOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

BoundedModelCheckingOp BoundedModelCheckingOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<BoundedModelCheckingOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

BoundedModelCheckingOp BoundedModelCheckingOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void BoundedModelCheckingOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  for (unsigned i = 0; i != 3; ++i)
    (void)odsState.addRegion();

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<BoundedModelCheckingOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
  ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
  if (::mlir::succeeded(BoundedModelCheckingOp::inferReturnTypes(odsBuilder.getContext(),
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

BoundedModelCheckingOp BoundedModelCheckingOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<BoundedModelCheckingOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

BoundedModelCheckingOp BoundedModelCheckingOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void BoundedModelCheckingOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  for (unsigned i = 0; i != 3; ++i)
    (void)odsState.addRegion();
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

BoundedModelCheckingOp BoundedModelCheckingOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<BoundedModelCheckingOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

BoundedModelCheckingOp BoundedModelCheckingOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

void BoundedModelCheckingOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties &>(properties));
  odsState.addAttributes(discardableAttributes);
  for (unsigned i = 0; i != 3; ++i)
    (void)odsState.addRegion();

  ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
  if (::mlir::succeeded(BoundedModelCheckingOp::inferReturnTypes(odsBuilder.getContext(),
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

BoundedModelCheckingOp BoundedModelCheckingOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<BoundedModelCheckingOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

BoundedModelCheckingOp BoundedModelCheckingOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult BoundedModelCheckingOp::verifyInvariantsImpl() {
  auto tblgen_bound = getProperties().bound; (void)tblgen_bound;
  if (!tblgen_bound) return emitOpError("requires attribute 'bound'");
  auto tblgen_initial_values = getProperties().initial_values; (void)tblgen_initial_values;
  if (!tblgen_initial_values) return emitOpError("requires attribute 'initial_values'");
  auto tblgen_num_regs = getProperties().num_regs; (void)tblgen_num_regs;
  if (!tblgen_num_regs) return emitOpError("requires attribute 'num_regs'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Verif2(*this, tblgen_bound, "bound")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Verif2(*this, tblgen_num_regs, "num_regs")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Verif3(*this, tblgen_initial_values, "initial_values")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Verif2(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;

    for (auto &region : ::llvm::MutableArrayRef((*this)->getRegion(0)))
      if (::mlir::failed(__mlir_ods_local_region_constraint_Verif1(*this, region, "init", index++)))
        return ::mlir::failure();

    for (auto &region : ::llvm::MutableArrayRef((*this)->getRegion(1)))
      if (::mlir::failed(__mlir_ods_local_region_constraint_Verif1(*this, region, "loop", index++)))
        return ::mlir::failure();

    for (auto &region : ::llvm::MutableArrayRef((*this)->getRegion(2)))
      if (::mlir::failed(__mlir_ods_local_region_constraint_Verif1(*this, region, "circuit", index++)))
        return ::mlir::failure();
  }
  return ::mlir::success();
}

::llvm::LogicalResult BoundedModelCheckingOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::llvm::LogicalResult BoundedModelCheckingOp::inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::PropertyRef properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes) {
  inferredReturnTypes.resize(1);
  ::mlir::Builder odsBuilder(context);
  ::mlir::Type odsInferredType0 = odsBuilder.getIntegerType(1);
  inferredReturnTypes[0] = odsInferredType0;
  return ::mlir::success();
}

::mlir::ParseResult BoundedModelCheckingOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::IntegerAttr boundAttr;
  ::mlir::IntegerAttr num_regsAttr;
  ::mlir::ArrayAttr initial_valuesAttr;
  std::unique_ptr<::mlir::Region> initRegion = std::make_unique<::mlir::Region>();
  std::unique_ptr<::mlir::Region> loopRegion = std::make_unique<::mlir::Region>();
  std::unique_ptr<::mlir::Region> circuitRegion = std::make_unique<::mlir::Region>();
  if (parser.parseKeyword("bound"))
    return ::mlir::failure();

  if (parser.parseCustomAttributeWithFallback(boundAttr, parser.getBuilder().getIntegerType(32))) {
    return ::mlir::failure();
  }
  if (boundAttr) result.getOrAddProperties<BoundedModelCheckingOp::Properties>().bound = boundAttr;
  if (parser.parseKeyword("num_regs"))
    return ::mlir::failure();

  if (parser.parseCustomAttributeWithFallback(num_regsAttr, parser.getBuilder().getIntegerType(32))) {
    return ::mlir::failure();
  }
  if (num_regsAttr) result.getOrAddProperties<BoundedModelCheckingOp::Properties>().num_regs = num_regsAttr;
  if (parser.parseKeyword("initial_values"))
    return ::mlir::failure();

  if (parser.parseCustomAttributeWithFallback(initial_valuesAttr, parser.getBuilder().getType<::mlir::NoneType>())) {
    return ::mlir::failure();
  }
  if (initial_valuesAttr) result.getOrAddProperties<BoundedModelCheckingOp::Properties>().initial_values = initial_valuesAttr;
  {
    auto loc = parser.getCurrentLocation();(void)loc;
    if (parser.parseOptionalAttrDictWithKeyword(result.attributes))
      return ::mlir::failure();
    if (failed(verifyInherentAttrs(result.name, result.attributes, [&]() {
        return parser.emitError(loc) << "'" << result.name.getStringRef() << "' op ";
      })))
      return ::mlir::failure();
  }
  if (parser.parseKeyword("init"))
    return ::mlir::failure();

  if (parser.parseRegion(*initRegion))
    return ::mlir::failure();

  ensureTerminator(*initRegion, parser.getBuilder(), result.location);
  if (parser.parseKeyword("loop"))
    return ::mlir::failure();

  if (parser.parseRegion(*loopRegion))
    return ::mlir::failure();

  ensureTerminator(*loopRegion, parser.getBuilder(), result.location);
  if (parser.parseKeyword("circuit"))
    return ::mlir::failure();

  if (parser.parseRegion(*circuitRegion))
    return ::mlir::failure();

  ensureTerminator(*circuitRegion, parser.getBuilder(), result.location);
  result.addRegion(std::move(initRegion));
  result.addRegion(std::move(loopRegion));
  result.addRegion(std::move(circuitRegion));
  ::mlir::Type odsBuildableType0 = parser.getBuilder().getIntegerType(1);
  result.addTypes(odsBuildableType0);
  return ::mlir::success();
}

void BoundedModelCheckingOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ' << "bound";
  _odsPrinter << ' ';
  _odsPrinter.printAttributeWithoutType(getBoundAttr());
  _odsPrinter << ' ' << "num_regs";
  _odsPrinter << ' ';
  _odsPrinter.printAttributeWithoutType(getNumRegsAttr());
  _odsPrinter << ' ' << "initial_values";
  _odsPrinter << ' ';
  _odsPrinter.printAttributeWithoutType(getInitialValuesAttr());
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("bound");
  elidedAttrs.push_back("num_regs");
  elidedAttrs.push_back("initial_values");
  _odsPrinter.printOptionalAttrDictWithKeyword((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << "init";
  _odsPrinter << ' ';

  {
    bool printTerminator = true;
    if (auto *term = getInit().empty() ? nullptr : getInit().begin()->getTerminator()) {
      printTerminator = !term->getAttrDictionary().empty() ||
                        term->getNumOperands() != 0 ||
                        term->getNumResults() != 0;
    }
    _odsPrinter.printRegion(getInit(), /*printEntryBlockArgs=*/true,
      /*printBlockTerminators=*/printTerminator);
  }
  _odsPrinter << ' ' << "loop";
  _odsPrinter << ' ';

  {
    bool printTerminator = true;
    if (auto *term = getLoop().empty() ? nullptr : getLoop().begin()->getTerminator()) {
      printTerminator = !term->getAttrDictionary().empty() ||
                        term->getNumOperands() != 0 ||
                        term->getNumResults() != 0;
    }
    _odsPrinter.printRegion(getLoop(), /*printEntryBlockArgs=*/true,
      /*printBlockTerminators=*/printTerminator);
  }
  _odsPrinter << ' ' << "circuit";
  _odsPrinter << ' ';

  {
    bool printTerminator = true;
    if (auto *term = getCircuit().empty() ? nullptr : getCircuit().begin()->getTerminator()) {
      printTerminator = !term->getAttrDictionary().empty() ||
                        term->getNumOperands() != 0 ||
                        term->getNumResults() != 0;
    }
    _odsPrinter.printRegion(getCircuit(), /*printEntryBlockArgs=*/true,
      /*printBlockTerminators=*/printTerminator);
  }
}


} // namespace circt::verif
MLIR_DEFINE_EXPLICIT_TYPE_ID(circt::verif::BoundedModelCheckingOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(circt::verif::detail::BoundedModelCheckingOpGenericAdaptorBase::Properties)

namespace circt::verif {


//===----------------------------------------------------------------------===//
// circt::verif::ClockedAssertOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

ClockedAssertOpGenericAdaptorBase::ClockedAssertOpGenericAdaptorBase(ClockedAssertOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

std::pair<unsigned, unsigned> ClockedAssertOpGenericAdaptorBase::getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
  bool isVariadic[] = {false, false, true};
  int prevVariadicCount = 0;
  for (unsigned i = 0; i < index; ++i)
    if (isVariadic[i]) ++prevVariadicCount;

  // Calculate how many dynamic values a static variadic operand corresponds to.
  // This assumes all static variadic operands have the same dynamic value count.
  int variadicSize = (odsOperandsSize - 2) / 1;
  // `index` passed in as the parameter is the static index which counts each
  // operand (variadic or not) as size 1. So here for each previous static variadic
  // operand, we need to offset by (variadicSize - 1) to get where the dynamic
  // value pack for this static operand starts.
  int start = index + (variadicSize - 1) * prevVariadicCount;
  int size = isVariadic[index] ? variadicSize : 1;
  return {start, size};
}

circt::verif::ClockEdge ClockedAssertOpGenericAdaptorBase::getEdge() {
  auto attr = getEdgeAttr();
  return attr.getValue();
}

::std::optional< ::llvm::StringRef > ClockedAssertOpGenericAdaptorBase::getLabel() {
  auto attr = getLabelAttr();
  return attr ? ::std::optional< ::llvm::StringRef >(attr.getValue()) : (::std::nullopt);
}


} // namespace detail
ClockedAssertOpAdaptor::ClockedAssertOpAdaptor(ClockedAssertOp op) : ClockedAssertOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult ClockedAssertOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_edge = getProperties().edge; (void)tblgen_edge;
  if (!tblgen_edge) return emitError(loc, "'verif.clocked_assert' op requires attribute 'edge'");
  auto tblgen_label = getProperties().label; (void)tblgen_label;

  if (tblgen_edge && !((::llvm::isa<circt::verif::ClockEdgeAttr>(tblgen_edge))))
    return emitError(loc, "'verif.clocked_assert' op attribute 'edge' failed to satisfy constraint: clock edge");

  if (tblgen_label && !((::llvm::isa<::mlir::StringAttr>(tblgen_label))))
    return emitError(loc, "'verif.clocked_assert' op attribute 'label' failed to satisfy constraint: string attribute");
  return ::mlir::success();
}

std::pair<unsigned, unsigned> ClockedAssertOp::getODSOperandIndexAndLength(unsigned index) {
  bool isVariadic[] = {false, false, true};
  int prevVariadicCount = 0;
  for (unsigned i = 0; i < index; ++i)
    if (isVariadic[i]) ++prevVariadicCount;

  // Calculate how many dynamic values a static variadic operand corresponds to.
  // This assumes all static variadic operands have the same dynamic value count.
  int variadicSize = (getOperation()->getNumOperands() - 2) / 1;
  // `index` passed in as the parameter is the static index which counts each
  // operand (variadic or not) as size 1. So here for each previous static variadic
  // operand, we need to offset by (variadicSize - 1) to get where the dynamic
  // value pack for this static operand starts.
  int start = index + (variadicSize - 1) * prevVariadicCount;
  int size = isVariadic[index] ? variadicSize : 1;
  return {start, size};
}

::mlir::MutableOperandRange ClockedAssertOp::getEnableMutable() {
  auto range = getODSOperandIndexAndLength(2);
  auto mutableRange = ::mlir::MutableOperandRange(getOperation(), range.first, range.second);
  return mutableRange;
}

::llvm::LogicalResult ClockedAssertOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.edge;
       auto attr = dict.get("edge");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `edge` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.label;
       auto attr = dict.get("label");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `label` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  return ::mlir::success();
}

::mlir::Attribute ClockedAssertOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.edge;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("edge",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.label;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("label",
                                       propStorage));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code ClockedAssertOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.edge.getAsOpaquePointer()), 
    llvm::hash_value(prop.label.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> ClockedAssertOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "edge")
      return prop.edge;

    if (name == "label")
      return prop.label;
  return std::nullopt;
}

void ClockedAssertOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "edge") {
       prop.edge = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.edge)>>(value);
       return;
    }

    if (name == "label") {
       prop.label = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.label)>>(value);
       return;
    }
}

void ClockedAssertOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.edge) attrs.append("edge", prop.edge);

    if (prop.label) attrs.append("label", prop.label);
}

::llvm::LogicalResult ClockedAssertOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getEdgeAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Verif4(attr, "edge", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getLabelAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Verif1(attr, "label", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult ClockedAssertOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.edge)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readOptionalAttribute(prop.label)))
    return ::mlir::failure();
  return ::mlir::success();
}

void ClockedAssertOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.edge);

  writer.writeOptionalAttribute(prop.label);
}

circt::verif::ClockEdge ClockedAssertOp::getEdge() {
  auto attr = getEdgeAttr();
  return attr.getValue();
}

::std::optional< ::llvm::StringRef > ClockedAssertOp::getLabel() {
  auto attr = getLabelAttr();
  return attr ? ::std::optional< ::llvm::StringRef >(attr.getValue()) : (::std::nullopt);
}

void ClockedAssertOp::setEdge(circt::verif::ClockEdge attrValue) {
  getProperties().edge = circt::verif::ClockEdgeAttr::get(::mlir::Builder((*this)->getContext()).getContext(), attrValue);
}

void ClockedAssertOp::setLabel(::std::optional<::llvm::StringRef> attrValue) {
    auto &odsProp = getProperties().label;
    if (attrValue)
      odsProp = ::mlir::Builder((*this)->getContext()).getStringAttr(*attrValue);
    else
      odsProp = nullptr;
}

void ClockedAssertOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value property, circt::verif::ClockEdgeAttr edge, ::mlir::Value clock, /*optional*/::mlir::Value enable, /*optional*/::mlir::StringAttr label) {
  odsState.addOperands(property);
  odsState.addOperands(clock);
  if (enable)
    odsState.addOperands(enable);
  odsState.getOrAddProperties<Properties>().edge = edge;
  if (label) {
    odsState.getOrAddProperties<Properties>().label = label;
  }
}

ClockedAssertOp ClockedAssertOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value property, circt::verif::ClockEdgeAttr edge, ::mlir::Value clock, /*optional*/::mlir::Value enable, /*optional*/::mlir::StringAttr label) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(property)>(property), std::forward<decltype(edge)>(edge), std::forward<decltype(clock)>(clock), std::forward<decltype(enable)>(enable), std::forward<decltype(label)>(label));
  auto __res__ = ::llvm::dyn_cast<ClockedAssertOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ClockedAssertOp ClockedAssertOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value property, circt::verif::ClockEdgeAttr edge, ::mlir::Value clock, /*optional*/::mlir::Value enable, /*optional*/::mlir::StringAttr label) {
  return create(builder, builder.getLoc(), std::forward<decltype(property)>(property), std::forward<decltype(edge)>(edge), std::forward<decltype(clock)>(clock), std::forward<decltype(enable)>(enable), std::forward<decltype(label)>(label));
}

void ClockedAssertOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value property, circt::verif::ClockEdgeAttr edge, ::mlir::Value clock, /*optional*/::mlir::Value enable, /*optional*/::mlir::StringAttr label) {
  odsState.addOperands(property);
  odsState.addOperands(clock);
  if (enable)
    odsState.addOperands(enable);
  odsState.getOrAddProperties<Properties>().edge = edge;
  if (label) {
    odsState.getOrAddProperties<Properties>().label = label;
  }
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

ClockedAssertOp ClockedAssertOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value property, circt::verif::ClockEdgeAttr edge, ::mlir::Value clock, /*optional*/::mlir::Value enable, /*optional*/::mlir::StringAttr label) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(property)>(property), std::forward<decltype(edge)>(edge), std::forward<decltype(clock)>(clock), std::forward<decltype(enable)>(enable), std::forward<decltype(label)>(label));
  auto __res__ = ::llvm::dyn_cast<ClockedAssertOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ClockedAssertOp ClockedAssertOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value property, circt::verif::ClockEdgeAttr edge, ::mlir::Value clock, /*optional*/::mlir::Value enable, /*optional*/::mlir::StringAttr label) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(property)>(property), std::forward<decltype(edge)>(edge), std::forward<decltype(clock)>(clock), std::forward<decltype(enable)>(enable), std::forward<decltype(label)>(label));
}

void ClockedAssertOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value property, circt::verif::ClockEdge edge, ::mlir::Value clock, /*optional*/::mlir::Value enable, /*optional*/::mlir::StringAttr label) {
  odsState.addOperands(property);
  odsState.addOperands(clock);
  if (enable)
    odsState.addOperands(enable);
  odsState.getOrAddProperties<Properties>().edge = circt::verif::ClockEdgeAttr::get(odsBuilder.getContext(), edge);
  if (label) {
    odsState.getOrAddProperties<Properties>().label = label;
  }
}

ClockedAssertOp ClockedAssertOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value property, circt::verif::ClockEdge edge, ::mlir::Value clock, /*optional*/::mlir::Value enable, /*optional*/::mlir::StringAttr label) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(property)>(property), std::forward<decltype(edge)>(edge), std::forward<decltype(clock)>(clock), std::forward<decltype(enable)>(enable), std::forward<decltype(label)>(label));
  auto __res__ = ::llvm::dyn_cast<ClockedAssertOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ClockedAssertOp ClockedAssertOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value property, circt::verif::ClockEdge edge, ::mlir::Value clock, /*optional*/::mlir::Value enable, /*optional*/::mlir::StringAttr label) {
  return create(builder, builder.getLoc(), std::forward<decltype(property)>(property), std::forward<decltype(edge)>(edge), std::forward<decltype(clock)>(clock), std::forward<decltype(enable)>(enable), std::forward<decltype(label)>(label));
}

void ClockedAssertOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value property, circt::verif::ClockEdge edge, ::mlir::Value clock, /*optional*/::mlir::Value enable, /*optional*/::mlir::StringAttr label) {
  odsState.addOperands(property);
  odsState.addOperands(clock);
  if (enable)
    odsState.addOperands(enable);
  odsState.getOrAddProperties<Properties>().edge = circt::verif::ClockEdgeAttr::get(odsBuilder.getContext(), edge);
  if (label) {
    odsState.getOrAddProperties<Properties>().label = label;
  }
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

ClockedAssertOp ClockedAssertOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value property, circt::verif::ClockEdge edge, ::mlir::Value clock, /*optional*/::mlir::Value enable, /*optional*/::mlir::StringAttr label) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(property)>(property), std::forward<decltype(edge)>(edge), std::forward<decltype(clock)>(clock), std::forward<decltype(enable)>(enable), std::forward<decltype(label)>(label));
  auto __res__ = ::llvm::dyn_cast<ClockedAssertOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ClockedAssertOp ClockedAssertOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value property, circt::verif::ClockEdge edge, ::mlir::Value clock, /*optional*/::mlir::Value enable, /*optional*/::mlir::StringAttr label) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(property)>(property), std::forward<decltype(edge)>(edge), std::forward<decltype(clock)>(clock), std::forward<decltype(enable)>(enable), std::forward<decltype(label)>(label));
}

void ClockedAssertOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() >= 2u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<ClockedAssertOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

ClockedAssertOp ClockedAssertOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<ClockedAssertOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ClockedAssertOp ClockedAssertOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void ClockedAssertOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() >= 2u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

ClockedAssertOp ClockedAssertOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<ClockedAssertOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ClockedAssertOp ClockedAssertOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult ClockedAssertOp::verifyInvariantsImpl() {
  auto tblgen_edge = getProperties().edge; (void)tblgen_edge;
  if (!tblgen_edge) return emitOpError("requires attribute 'edge'");
  auto tblgen_label = getProperties().label; (void)tblgen_label;

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Verif4(*this, tblgen_edge, "edge")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Verif1(*this, tblgen_label, "label")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Verif1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSOperands(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Verif2(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup2 = getODSOperands(2);

    if (valueGroup2.size() > 1) {
      return emitOpError("operand group starting at #") << index
          << " requires 0 or 1 element, but found " << valueGroup2.size();
    }

    for (auto v : valueGroup2) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Verif2(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult ClockedAssertOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult ClockedAssertOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::OpAsmParser::UnresolvedOperand propertyRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> propertyOperands(&propertyRawOperand, 1);  ::llvm::SMLoc propertyOperandsLoc;
  (void)propertyOperandsLoc;
  ::llvm::SmallVector<::mlir::OpAsmParser::UnresolvedOperand, 4> enableOperands;
  ::llvm::SMLoc enableOperandsLoc;
  (void)enableOperandsLoc;
  circt::verif::ClockEdgeAttr edgeAttr;
  ::mlir::OpAsmParser::UnresolvedOperand clockRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> clockOperands(&clockRawOperand, 1);  ::llvm::SMLoc clockOperandsLoc;
  (void)clockOperandsLoc;
  ::mlir::StringAttr labelAttr;
  ::mlir::Type propertyRawType{};
  ::llvm::ArrayRef<::mlir::Type> propertyTypes(&propertyRawType, 1);

  propertyOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(propertyRawOperand))
    return ::mlir::failure();
  if (::mlir::succeeded(parser.parseOptionalKeyword("if"))) {

  {
    enableOperandsLoc = parser.getCurrentLocation();
    ::mlir::OpAsmParser::UnresolvedOperand operand;
    ::mlir::OptionalParseResult parseResult =
                                    parser.parseOptionalOperand(operand);
    if (parseResult.has_value()) {
      if (failed(*parseResult))
        return ::mlir::failure();
      enableOperands.push_back(operand);
    }
  }
  }
  if (parser.parseComma())
    return ::mlir::failure();

  {
    ::llvm::StringRef attrStr;
    ::mlir::NamedAttrList attrStorage;
    auto loc = parser.getCurrentLocation();
    if (parser.parseOptionalKeyword(&attrStr, {"posedge","negedge","edge"})) {
      ::mlir::StringAttr attrVal;
      ::mlir::OptionalParseResult parseResult =
        parser.parseOptionalAttribute(attrVal,
                                      parser.getBuilder().getNoneType(),
                                      "edge", attrStorage);
      if (parseResult.has_value()) {
        if (failed(*parseResult))
          return ::mlir::failure();
        attrStr = attrVal.getValue();
      } else {
        return parser.emitError(loc, "expected string or keyword containing one of the following enum values for attribute 'edge' [posedge, negedge, edge]");
      }
    }
    if (!attrStr.empty()) {
      auto attrOptional = circt::verif::symbolizeClockEdge(attrStr);
      if (!attrOptional)
        return parser.emitError(loc, "invalid ")
               << "edge attribute specification: \"" << attrStr << '"';;

      edgeAttr = circt::verif::ClockEdgeAttr::get(parser.getBuilder().getContext(), *attrOptional);
        result.getOrAddProperties<ClockedAssertOp::Properties>().edge = edgeAttr;
    }
  }

  clockOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(clockRawOperand))
    return ::mlir::failure();
  if (::mlir::succeeded(parser.parseOptionalKeyword("label"))) {

  if (parser.parseCustomAttributeWithFallback(labelAttr, parser.getBuilder().getType<::mlir::NoneType>())) {
    return ::mlir::failure();
  }
  if (labelAttr) result.getOrAddProperties<ClockedAssertOp::Properties>().label = labelAttr;
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
  if (parser.parseColon())
    return ::mlir::failure();

  {
    ::mlir::Type type;
    if (parser.parseCustomTypeWithFallback(type))
      return ::mlir::failure();
    propertyRawType = type;
  }
  ::mlir::Type odsBuildableType0 = parser.getBuilder().getIntegerType(1);
  if (parser.resolveOperands(propertyOperands, propertyTypes, propertyOperandsLoc, result.operands))
    return ::mlir::failure();
  if (parser.resolveOperands(clockOperands, odsBuildableType0, clockOperandsLoc, result.operands))
    return ::mlir::failure();
  if (!enableOperands.empty()) {
  if (parser.resolveOperands(enableOperands, odsBuildableType0, enableOperandsLoc, result.operands))
    return ::mlir::failure();
  }
  return ::mlir::success();
}

void ClockedAssertOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter << getProperty();
  if (getEnable()) {
    _odsPrinter << ' ' << "if";
    _odsPrinter << ' ';
    if (::mlir::Value value = getEnable())
      _odsPrinter << value;
  }
  _odsPrinter << ",";
  _odsPrinter << ' ';

  {
    auto caseValue = getEdge();
    auto caseValueStr = stringifyClockEdge(caseValue);
    _odsPrinter << caseValueStr;
  }
  _odsPrinter << ' ';
  _odsPrinter << getClock();
  if (getLabelAttr()) {
    _odsPrinter << ' ' << "label";
    _odsPrinter << ' ';
    _odsPrinter.printAttributeWithoutType(getLabelAttr());
  }
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("edge");
  elidedAttrs.push_back("label");
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
  {
    auto type = getProperty().getType();
    if (auto validType = ::llvm::dyn_cast<::mlir::Type>(type))
      _odsPrinter.printStrippedAttrOrType(validType);
   else
     _odsPrinter << type;
  }
}


} // namespace circt::verif
MLIR_DEFINE_EXPLICIT_TYPE_ID(circt::verif::ClockedAssertOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(circt::verif::detail::ClockedAssertOpGenericAdaptorBase::Properties)

namespace circt::verif {


//===----------------------------------------------------------------------===//
// circt::verif::ClockedAssumeOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

ClockedAssumeOpGenericAdaptorBase::ClockedAssumeOpGenericAdaptorBase(ClockedAssumeOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

std::pair<unsigned, unsigned> ClockedAssumeOpGenericAdaptorBase::getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
  bool isVariadic[] = {false, false, true};
  int prevVariadicCount = 0;
  for (unsigned i = 0; i < index; ++i)
    if (isVariadic[i]) ++prevVariadicCount;

  // Calculate how many dynamic values a static variadic operand corresponds to.
  // This assumes all static variadic operands have the same dynamic value count.
  int variadicSize = (odsOperandsSize - 2) / 1;
  // `index` passed in as the parameter is the static index which counts each
  // operand (variadic or not) as size 1. So here for each previous static variadic
  // operand, we need to offset by (variadicSize - 1) to get where the dynamic
  // value pack for this static operand starts.
  int start = index + (variadicSize - 1) * prevVariadicCount;
  int size = isVariadic[index] ? variadicSize : 1;
  return {start, size};
}

circt::verif::ClockEdge ClockedAssumeOpGenericAdaptorBase::getEdge() {
  auto attr = getEdgeAttr();
  return attr.getValue();
}

::std::optional< ::llvm::StringRef > ClockedAssumeOpGenericAdaptorBase::getLabel() {
  auto attr = getLabelAttr();
  return attr ? ::std::optional< ::llvm::StringRef >(attr.getValue()) : (::std::nullopt);
}


} // namespace detail
ClockedAssumeOpAdaptor::ClockedAssumeOpAdaptor(ClockedAssumeOp op) : ClockedAssumeOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult ClockedAssumeOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_edge = getProperties().edge; (void)tblgen_edge;
  if (!tblgen_edge) return emitError(loc, "'verif.clocked_assume' op requires attribute 'edge'");
  auto tblgen_label = getProperties().label; (void)tblgen_label;

  if (tblgen_edge && !((::llvm::isa<circt::verif::ClockEdgeAttr>(tblgen_edge))))
    return emitError(loc, "'verif.clocked_assume' op attribute 'edge' failed to satisfy constraint: clock edge");

  if (tblgen_label && !((::llvm::isa<::mlir::StringAttr>(tblgen_label))))
    return emitError(loc, "'verif.clocked_assume' op attribute 'label' failed to satisfy constraint: string attribute");
  return ::mlir::success();
}

std::pair<unsigned, unsigned> ClockedAssumeOp::getODSOperandIndexAndLength(unsigned index) {
  bool isVariadic[] = {false, false, true};
  int prevVariadicCount = 0;
  for (unsigned i = 0; i < index; ++i)
    if (isVariadic[i]) ++prevVariadicCount;

  // Calculate how many dynamic values a static variadic operand corresponds to.
  // This assumes all static variadic operands have the same dynamic value count.
  int variadicSize = (getOperation()->getNumOperands() - 2) / 1;
  // `index` passed in as the parameter is the static index which counts each
  // operand (variadic or not) as size 1. So here for each previous static variadic
  // operand, we need to offset by (variadicSize - 1) to get where the dynamic
  // value pack for this static operand starts.
  int start = index + (variadicSize - 1) * prevVariadicCount;
  int size = isVariadic[index] ? variadicSize : 1;
  return {start, size};
}

::mlir::MutableOperandRange ClockedAssumeOp::getEnableMutable() {
  auto range = getODSOperandIndexAndLength(2);
  auto mutableRange = ::mlir::MutableOperandRange(getOperation(), range.first, range.second);
  return mutableRange;
}

::llvm::LogicalResult ClockedAssumeOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.edge;
       auto attr = dict.get("edge");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `edge` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.label;
       auto attr = dict.get("label");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `label` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  return ::mlir::success();
}

::mlir::Attribute ClockedAssumeOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.edge;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("edge",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.label;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("label",
                                       propStorage));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code ClockedAssumeOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.edge.getAsOpaquePointer()), 
    llvm::hash_value(prop.label.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> ClockedAssumeOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "edge")
      return prop.edge;

    if (name == "label")
      return prop.label;
  return std::nullopt;
}

void ClockedAssumeOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "edge") {
       prop.edge = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.edge)>>(value);
       return;
    }

    if (name == "label") {
       prop.label = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.label)>>(value);
       return;
    }
}

void ClockedAssumeOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.edge) attrs.append("edge", prop.edge);

    if (prop.label) attrs.append("label", prop.label);
}

::llvm::LogicalResult ClockedAssumeOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getEdgeAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Verif4(attr, "edge", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getLabelAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Verif1(attr, "label", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult ClockedAssumeOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.edge)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readOptionalAttribute(prop.label)))
    return ::mlir::failure();
  return ::mlir::success();
}

void ClockedAssumeOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.edge);

  writer.writeOptionalAttribute(prop.label);
}

circt::verif::ClockEdge ClockedAssumeOp::getEdge() {
  auto attr = getEdgeAttr();
  return attr.getValue();
}

::std::optional< ::llvm::StringRef > ClockedAssumeOp::getLabel() {
  auto attr = getLabelAttr();
  return attr ? ::std::optional< ::llvm::StringRef >(attr.getValue()) : (::std::nullopt);
}

void ClockedAssumeOp::setEdge(circt::verif::ClockEdge attrValue) {
  getProperties().edge = circt::verif::ClockEdgeAttr::get(::mlir::Builder((*this)->getContext()).getContext(), attrValue);
}

void ClockedAssumeOp::setLabel(::std::optional<::llvm::StringRef> attrValue) {
    auto &odsProp = getProperties().label;
    if (attrValue)
      odsProp = ::mlir::Builder((*this)->getContext()).getStringAttr(*attrValue);
    else
      odsProp = nullptr;
}

void ClockedAssumeOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value property, circt::verif::ClockEdgeAttr edge, ::mlir::Value clock, /*optional*/::mlir::Value enable, /*optional*/::mlir::StringAttr label) {
  odsState.addOperands(property);
  odsState.addOperands(clock);
  if (enable)
    odsState.addOperands(enable);
  odsState.getOrAddProperties<Properties>().edge = edge;
  if (label) {
    odsState.getOrAddProperties<Properties>().label = label;
  }
}

ClockedAssumeOp ClockedAssumeOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value property, circt::verif::ClockEdgeAttr edge, ::mlir::Value clock, /*optional*/::mlir::Value enable, /*optional*/::mlir::StringAttr label) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(property)>(property), std::forward<decltype(edge)>(edge), std::forward<decltype(clock)>(clock), std::forward<decltype(enable)>(enable), std::forward<decltype(label)>(label));
  auto __res__ = ::llvm::dyn_cast<ClockedAssumeOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ClockedAssumeOp ClockedAssumeOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value property, circt::verif::ClockEdgeAttr edge, ::mlir::Value clock, /*optional*/::mlir::Value enable, /*optional*/::mlir::StringAttr label) {
  return create(builder, builder.getLoc(), std::forward<decltype(property)>(property), std::forward<decltype(edge)>(edge), std::forward<decltype(clock)>(clock), std::forward<decltype(enable)>(enable), std::forward<decltype(label)>(label));
}

void ClockedAssumeOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value property, circt::verif::ClockEdgeAttr edge, ::mlir::Value clock, /*optional*/::mlir::Value enable, /*optional*/::mlir::StringAttr label) {
  odsState.addOperands(property);
  odsState.addOperands(clock);
  if (enable)
    odsState.addOperands(enable);
  odsState.getOrAddProperties<Properties>().edge = edge;
  if (label) {
    odsState.getOrAddProperties<Properties>().label = label;
  }
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

ClockedAssumeOp ClockedAssumeOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value property, circt::verif::ClockEdgeAttr edge, ::mlir::Value clock, /*optional*/::mlir::Value enable, /*optional*/::mlir::StringAttr label) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(property)>(property), std::forward<decltype(edge)>(edge), std::forward<decltype(clock)>(clock), std::forward<decltype(enable)>(enable), std::forward<decltype(label)>(label));
  auto __res__ = ::llvm::dyn_cast<ClockedAssumeOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ClockedAssumeOp ClockedAssumeOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value property, circt::verif::ClockEdgeAttr edge, ::mlir::Value clock, /*optional*/::mlir::Value enable, /*optional*/::mlir::StringAttr label) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(property)>(property), std::forward<decltype(edge)>(edge), std::forward<decltype(clock)>(clock), std::forward<decltype(enable)>(enable), std::forward<decltype(label)>(label));
}

void ClockedAssumeOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value property, circt::verif::ClockEdge edge, ::mlir::Value clock, /*optional*/::mlir::Value enable, /*optional*/::mlir::StringAttr label) {
  odsState.addOperands(property);
  odsState.addOperands(clock);
  if (enable)
    odsState.addOperands(enable);
  odsState.getOrAddProperties<Properties>().edge = circt::verif::ClockEdgeAttr::get(odsBuilder.getContext(), edge);
  if (label) {
    odsState.getOrAddProperties<Properties>().label = label;
  }
}

ClockedAssumeOp ClockedAssumeOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value property, circt::verif::ClockEdge edge, ::mlir::Value clock, /*optional*/::mlir::Value enable, /*optional*/::mlir::StringAttr label) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(property)>(property), std::forward<decltype(edge)>(edge), std::forward<decltype(clock)>(clock), std::forward<decltype(enable)>(enable), std::forward<decltype(label)>(label));
  auto __res__ = ::llvm::dyn_cast<ClockedAssumeOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ClockedAssumeOp ClockedAssumeOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value property, circt::verif::ClockEdge edge, ::mlir::Value clock, /*optional*/::mlir::Value enable, /*optional*/::mlir::StringAttr label) {
  return create(builder, builder.getLoc(), std::forward<decltype(property)>(property), std::forward<decltype(edge)>(edge), std::forward<decltype(clock)>(clock), std::forward<decltype(enable)>(enable), std::forward<decltype(label)>(label));
}

void ClockedAssumeOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value property, circt::verif::ClockEdge edge, ::mlir::Value clock, /*optional*/::mlir::Value enable, /*optional*/::mlir::StringAttr label) {
  odsState.addOperands(property);
  odsState.addOperands(clock);
  if (enable)
    odsState.addOperands(enable);
  odsState.getOrAddProperties<Properties>().edge = circt::verif::ClockEdgeAttr::get(odsBuilder.getContext(), edge);
  if (label) {
    odsState.getOrAddProperties<Properties>().label = label;
  }
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

ClockedAssumeOp ClockedAssumeOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value property, circt::verif::ClockEdge edge, ::mlir::Value clock, /*optional*/::mlir::Value enable, /*optional*/::mlir::StringAttr label) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(property)>(property), std::forward<decltype(edge)>(edge), std::forward<decltype(clock)>(clock), std::forward<decltype(enable)>(enable), std::forward<decltype(label)>(label));
  auto __res__ = ::llvm::dyn_cast<ClockedAssumeOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ClockedAssumeOp ClockedAssumeOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value property, circt::verif::ClockEdge edge, ::mlir::Value clock, /*optional*/::mlir::Value enable, /*optional*/::mlir::StringAttr label) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(property)>(property), std::forward<decltype(edge)>(edge), std::forward<decltype(clock)>(clock), std::forward<decltype(enable)>(enable), std::forward<decltype(label)>(label));
}

void ClockedAssumeOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() >= 2u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<ClockedAssumeOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

ClockedAssumeOp ClockedAssumeOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<ClockedAssumeOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ClockedAssumeOp ClockedAssumeOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void ClockedAssumeOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() >= 2u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

ClockedAssumeOp ClockedAssumeOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<ClockedAssumeOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ClockedAssumeOp ClockedAssumeOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult ClockedAssumeOp::verifyInvariantsImpl() {
  auto tblgen_edge = getProperties().edge; (void)tblgen_edge;
  if (!tblgen_edge) return emitOpError("requires attribute 'edge'");
  auto tblgen_label = getProperties().label; (void)tblgen_label;

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Verif4(*this, tblgen_edge, "edge")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Verif1(*this, tblgen_label, "label")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Verif1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSOperands(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Verif2(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup2 = getODSOperands(2);

    if (valueGroup2.size() > 1) {
      return emitOpError("operand group starting at #") << index
          << " requires 0 or 1 element, but found " << valueGroup2.size();
    }

    for (auto v : valueGroup2) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Verif2(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult ClockedAssumeOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult ClockedAssumeOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::OpAsmParser::UnresolvedOperand propertyRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> propertyOperands(&propertyRawOperand, 1);  ::llvm::SMLoc propertyOperandsLoc;
  (void)propertyOperandsLoc;
  ::llvm::SmallVector<::mlir::OpAsmParser::UnresolvedOperand, 4> enableOperands;
  ::llvm::SMLoc enableOperandsLoc;
  (void)enableOperandsLoc;
  circt::verif::ClockEdgeAttr edgeAttr;
  ::mlir::OpAsmParser::UnresolvedOperand clockRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> clockOperands(&clockRawOperand, 1);  ::llvm::SMLoc clockOperandsLoc;
  (void)clockOperandsLoc;
  ::mlir::StringAttr labelAttr;
  ::mlir::Type propertyRawType{};
  ::llvm::ArrayRef<::mlir::Type> propertyTypes(&propertyRawType, 1);

  propertyOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(propertyRawOperand))
    return ::mlir::failure();
  if (::mlir::succeeded(parser.parseOptionalKeyword("if"))) {

  {
    enableOperandsLoc = parser.getCurrentLocation();
    ::mlir::OpAsmParser::UnresolvedOperand operand;
    ::mlir::OptionalParseResult parseResult =
                                    parser.parseOptionalOperand(operand);
    if (parseResult.has_value()) {
      if (failed(*parseResult))
        return ::mlir::failure();
      enableOperands.push_back(operand);
    }
  }
  }
  if (parser.parseComma())
    return ::mlir::failure();

  {
    ::llvm::StringRef attrStr;
    ::mlir::NamedAttrList attrStorage;
    auto loc = parser.getCurrentLocation();
    if (parser.parseOptionalKeyword(&attrStr, {"posedge","negedge","edge"})) {
      ::mlir::StringAttr attrVal;
      ::mlir::OptionalParseResult parseResult =
        parser.parseOptionalAttribute(attrVal,
                                      parser.getBuilder().getNoneType(),
                                      "edge", attrStorage);
      if (parseResult.has_value()) {
        if (failed(*parseResult))
          return ::mlir::failure();
        attrStr = attrVal.getValue();
      } else {
        return parser.emitError(loc, "expected string or keyword containing one of the following enum values for attribute 'edge' [posedge, negedge, edge]");
      }
    }
    if (!attrStr.empty()) {
      auto attrOptional = circt::verif::symbolizeClockEdge(attrStr);
      if (!attrOptional)
        return parser.emitError(loc, "invalid ")
               << "edge attribute specification: \"" << attrStr << '"';;

      edgeAttr = circt::verif::ClockEdgeAttr::get(parser.getBuilder().getContext(), *attrOptional);
        result.getOrAddProperties<ClockedAssumeOp::Properties>().edge = edgeAttr;
    }
  }

  clockOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(clockRawOperand))
    return ::mlir::failure();
  if (::mlir::succeeded(parser.parseOptionalKeyword("label"))) {

  if (parser.parseCustomAttributeWithFallback(labelAttr, parser.getBuilder().getType<::mlir::NoneType>())) {
    return ::mlir::failure();
  }
  if (labelAttr) result.getOrAddProperties<ClockedAssumeOp::Properties>().label = labelAttr;
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
  if (parser.parseColon())
    return ::mlir::failure();

  {
    ::mlir::Type type;
    if (parser.parseCustomTypeWithFallback(type))
      return ::mlir::failure();
    propertyRawType = type;
  }
  ::mlir::Type odsBuildableType0 = parser.getBuilder().getIntegerType(1);
  if (parser.resolveOperands(propertyOperands, propertyTypes, propertyOperandsLoc, result.operands))
    return ::mlir::failure();
  if (parser.resolveOperands(clockOperands, odsBuildableType0, clockOperandsLoc, result.operands))
    return ::mlir::failure();
  if (!enableOperands.empty()) {
  if (parser.resolveOperands(enableOperands, odsBuildableType0, enableOperandsLoc, result.operands))
    return ::mlir::failure();
  }
  return ::mlir::success();
}

void ClockedAssumeOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter << getProperty();
  if (getEnable()) {
    _odsPrinter << ' ' << "if";
    _odsPrinter << ' ';
    if (::mlir::Value value = getEnable())
      _odsPrinter << value;
  }
  _odsPrinter << ",";
  _odsPrinter << ' ';

  {
    auto caseValue = getEdge();
    auto caseValueStr = stringifyClockEdge(caseValue);
    _odsPrinter << caseValueStr;
  }
  _odsPrinter << ' ';
  _odsPrinter << getClock();
  if (getLabelAttr()) {
    _odsPrinter << ' ' << "label";
    _odsPrinter << ' ';
    _odsPrinter.printAttributeWithoutType(getLabelAttr());
  }
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("edge");
  elidedAttrs.push_back("label");
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
  {
    auto type = getProperty().getType();
    if (auto validType = ::llvm::dyn_cast<::mlir::Type>(type))
      _odsPrinter.printStrippedAttrOrType(validType);
   else
     _odsPrinter << type;
  }
}


} // namespace circt::verif
MLIR_DEFINE_EXPLICIT_TYPE_ID(circt::verif::ClockedAssumeOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(circt::verif::detail::ClockedAssumeOpGenericAdaptorBase::Properties)

namespace circt::verif {


//===----------------------------------------------------------------------===//
// circt::verif::ClockedCoverOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

ClockedCoverOpGenericAdaptorBase::ClockedCoverOpGenericAdaptorBase(ClockedCoverOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

std::pair<unsigned, unsigned> ClockedCoverOpGenericAdaptorBase::getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
  bool isVariadic[] = {false, false, true};
  int prevVariadicCount = 0;
  for (unsigned i = 0; i < index; ++i)
    if (isVariadic[i]) ++prevVariadicCount;

  // Calculate how many dynamic values a static variadic operand corresponds to.
  // This assumes all static variadic operands have the same dynamic value count.
  int variadicSize = (odsOperandsSize - 2) / 1;
  // `index` passed in as the parameter is the static index which counts each
  // operand (variadic or not) as size 1. So here for each previous static variadic
  // operand, we need to offset by (variadicSize - 1) to get where the dynamic
  // value pack for this static operand starts.
  int start = index + (variadicSize - 1) * prevVariadicCount;
  int size = isVariadic[index] ? variadicSize : 1;
  return {start, size};
}

circt::verif::ClockEdge ClockedCoverOpGenericAdaptorBase::getEdge() {
  auto attr = getEdgeAttr();
  return attr.getValue();
}

::std::optional< ::llvm::StringRef > ClockedCoverOpGenericAdaptorBase::getLabel() {
  auto attr = getLabelAttr();
  return attr ? ::std::optional< ::llvm::StringRef >(attr.getValue()) : (::std::nullopt);
}


} // namespace detail
ClockedCoverOpAdaptor::ClockedCoverOpAdaptor(ClockedCoverOp op) : ClockedCoverOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult ClockedCoverOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_edge = getProperties().edge; (void)tblgen_edge;
  if (!tblgen_edge) return emitError(loc, "'verif.clocked_cover' op requires attribute 'edge'");
  auto tblgen_label = getProperties().label; (void)tblgen_label;

  if (tblgen_edge && !((::llvm::isa<circt::verif::ClockEdgeAttr>(tblgen_edge))))
    return emitError(loc, "'verif.clocked_cover' op attribute 'edge' failed to satisfy constraint: clock edge");

  if (tblgen_label && !((::llvm::isa<::mlir::StringAttr>(tblgen_label))))
    return emitError(loc, "'verif.clocked_cover' op attribute 'label' failed to satisfy constraint: string attribute");
  return ::mlir::success();
}

std::pair<unsigned, unsigned> ClockedCoverOp::getODSOperandIndexAndLength(unsigned index) {
  bool isVariadic[] = {false, false, true};
  int prevVariadicCount = 0;
  for (unsigned i = 0; i < index; ++i)
    if (isVariadic[i]) ++prevVariadicCount;

  // Calculate how many dynamic values a static variadic operand corresponds to.
  // This assumes all static variadic operands have the same dynamic value count.
  int variadicSize = (getOperation()->getNumOperands() - 2) / 1;
  // `index` passed in as the parameter is the static index which counts each
  // operand (variadic or not) as size 1. So here for each previous static variadic
  // operand, we need to offset by (variadicSize - 1) to get where the dynamic
  // value pack for this static operand starts.
  int start = index + (variadicSize - 1) * prevVariadicCount;
  int size = isVariadic[index] ? variadicSize : 1;
  return {start, size};
}

::mlir::MutableOperandRange ClockedCoverOp::getEnableMutable() {
  auto range = getODSOperandIndexAndLength(2);
  auto mutableRange = ::mlir::MutableOperandRange(getOperation(), range.first, range.second);
  return mutableRange;
}

::llvm::LogicalResult ClockedCoverOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.edge;
       auto attr = dict.get("edge");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `edge` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.label;
       auto attr = dict.get("label");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `label` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  return ::mlir::success();
}

::mlir::Attribute ClockedCoverOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.edge;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("edge",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.label;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("label",
                                       propStorage));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code ClockedCoverOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.edge.getAsOpaquePointer()), 
    llvm::hash_value(prop.label.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> ClockedCoverOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "edge")
      return prop.edge;

    if (name == "label")
      return prop.label;
  return std::nullopt;
}

void ClockedCoverOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "edge") {
       prop.edge = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.edge)>>(value);
       return;
    }

    if (name == "label") {
       prop.label = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.label)>>(value);
       return;
    }
}

void ClockedCoverOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.edge) attrs.append("edge", prop.edge);

    if (prop.label) attrs.append("label", prop.label);
}

::llvm::LogicalResult ClockedCoverOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getEdgeAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Verif4(attr, "edge", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getLabelAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Verif1(attr, "label", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult ClockedCoverOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.edge)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readOptionalAttribute(prop.label)))
    return ::mlir::failure();
  return ::mlir::success();
}

void ClockedCoverOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.edge);

  writer.writeOptionalAttribute(prop.label);
}

circt::verif::ClockEdge ClockedCoverOp::getEdge() {
  auto attr = getEdgeAttr();
  return attr.getValue();
}

::std::optional< ::llvm::StringRef > ClockedCoverOp::getLabel() {
  auto attr = getLabelAttr();
  return attr ? ::std::optional< ::llvm::StringRef >(attr.getValue()) : (::std::nullopt);
}

void ClockedCoverOp::setEdge(circt::verif::ClockEdge attrValue) {
  getProperties().edge = circt::verif::ClockEdgeAttr::get(::mlir::Builder((*this)->getContext()).getContext(), attrValue);
}

void ClockedCoverOp::setLabel(::std::optional<::llvm::StringRef> attrValue) {
    auto &odsProp = getProperties().label;
    if (attrValue)
      odsProp = ::mlir::Builder((*this)->getContext()).getStringAttr(*attrValue);
    else
      odsProp = nullptr;
}

void ClockedCoverOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value property, circt::verif::ClockEdgeAttr edge, ::mlir::Value clock, /*optional*/::mlir::Value enable, /*optional*/::mlir::StringAttr label) {
  odsState.addOperands(property);
  odsState.addOperands(clock);
  if (enable)
    odsState.addOperands(enable);
  odsState.getOrAddProperties<Properties>().edge = edge;
  if (label) {
    odsState.getOrAddProperties<Properties>().label = label;
  }
}

ClockedCoverOp ClockedCoverOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value property, circt::verif::ClockEdgeAttr edge, ::mlir::Value clock, /*optional*/::mlir::Value enable, /*optional*/::mlir::StringAttr label) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(property)>(property), std::forward<decltype(edge)>(edge), std::forward<decltype(clock)>(clock), std::forward<decltype(enable)>(enable), std::forward<decltype(label)>(label));
  auto __res__ = ::llvm::dyn_cast<ClockedCoverOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ClockedCoverOp ClockedCoverOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value property, circt::verif::ClockEdgeAttr edge, ::mlir::Value clock, /*optional*/::mlir::Value enable, /*optional*/::mlir::StringAttr label) {
  return create(builder, builder.getLoc(), std::forward<decltype(property)>(property), std::forward<decltype(edge)>(edge), std::forward<decltype(clock)>(clock), std::forward<decltype(enable)>(enable), std::forward<decltype(label)>(label));
}

void ClockedCoverOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value property, circt::verif::ClockEdgeAttr edge, ::mlir::Value clock, /*optional*/::mlir::Value enable, /*optional*/::mlir::StringAttr label) {
  odsState.addOperands(property);
  odsState.addOperands(clock);
  if (enable)
    odsState.addOperands(enable);
  odsState.getOrAddProperties<Properties>().edge = edge;
  if (label) {
    odsState.getOrAddProperties<Properties>().label = label;
  }
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

ClockedCoverOp ClockedCoverOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value property, circt::verif::ClockEdgeAttr edge, ::mlir::Value clock, /*optional*/::mlir::Value enable, /*optional*/::mlir::StringAttr label) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(property)>(property), std::forward<decltype(edge)>(edge), std::forward<decltype(clock)>(clock), std::forward<decltype(enable)>(enable), std::forward<decltype(label)>(label));
  auto __res__ = ::llvm::dyn_cast<ClockedCoverOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ClockedCoverOp ClockedCoverOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value property, circt::verif::ClockEdgeAttr edge, ::mlir::Value clock, /*optional*/::mlir::Value enable, /*optional*/::mlir::StringAttr label) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(property)>(property), std::forward<decltype(edge)>(edge), std::forward<decltype(clock)>(clock), std::forward<decltype(enable)>(enable), std::forward<decltype(label)>(label));
}

void ClockedCoverOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value property, circt::verif::ClockEdge edge, ::mlir::Value clock, /*optional*/::mlir::Value enable, /*optional*/::mlir::StringAttr label) {
  odsState.addOperands(property);
  odsState.addOperands(clock);
  if (enable)
    odsState.addOperands(enable);
  odsState.getOrAddProperties<Properties>().edge = circt::verif::ClockEdgeAttr::get(odsBuilder.getContext(), edge);
  if (label) {
    odsState.getOrAddProperties<Properties>().label = label;
  }
}

ClockedCoverOp ClockedCoverOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value property, circt::verif::ClockEdge edge, ::mlir::Value clock, /*optional*/::mlir::Value enable, /*optional*/::mlir::StringAttr label) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(property)>(property), std::forward<decltype(edge)>(edge), std::forward<decltype(clock)>(clock), std::forward<decltype(enable)>(enable), std::forward<decltype(label)>(label));
  auto __res__ = ::llvm::dyn_cast<ClockedCoverOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ClockedCoverOp ClockedCoverOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value property, circt::verif::ClockEdge edge, ::mlir::Value clock, /*optional*/::mlir::Value enable, /*optional*/::mlir::StringAttr label) {
  return create(builder, builder.getLoc(), std::forward<decltype(property)>(property), std::forward<decltype(edge)>(edge), std::forward<decltype(clock)>(clock), std::forward<decltype(enable)>(enable), std::forward<decltype(label)>(label));
}

void ClockedCoverOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value property, circt::verif::ClockEdge edge, ::mlir::Value clock, /*optional*/::mlir::Value enable, /*optional*/::mlir::StringAttr label) {
  odsState.addOperands(property);
  odsState.addOperands(clock);
  if (enable)
    odsState.addOperands(enable);
  odsState.getOrAddProperties<Properties>().edge = circt::verif::ClockEdgeAttr::get(odsBuilder.getContext(), edge);
  if (label) {
    odsState.getOrAddProperties<Properties>().label = label;
  }
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

ClockedCoverOp ClockedCoverOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value property, circt::verif::ClockEdge edge, ::mlir::Value clock, /*optional*/::mlir::Value enable, /*optional*/::mlir::StringAttr label) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(property)>(property), std::forward<decltype(edge)>(edge), std::forward<decltype(clock)>(clock), std::forward<decltype(enable)>(enable), std::forward<decltype(label)>(label));
  auto __res__ = ::llvm::dyn_cast<ClockedCoverOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ClockedCoverOp ClockedCoverOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value property, circt::verif::ClockEdge edge, ::mlir::Value clock, /*optional*/::mlir::Value enable, /*optional*/::mlir::StringAttr label) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(property)>(property), std::forward<decltype(edge)>(edge), std::forward<decltype(clock)>(clock), std::forward<decltype(enable)>(enable), std::forward<decltype(label)>(label));
}

void ClockedCoverOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() >= 2u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<ClockedCoverOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

ClockedCoverOp ClockedCoverOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<ClockedCoverOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ClockedCoverOp ClockedCoverOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void ClockedCoverOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() >= 2u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

ClockedCoverOp ClockedCoverOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<ClockedCoverOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ClockedCoverOp ClockedCoverOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult ClockedCoverOp::verifyInvariantsImpl() {
  auto tblgen_edge = getProperties().edge; (void)tblgen_edge;
  if (!tblgen_edge) return emitOpError("requires attribute 'edge'");
  auto tblgen_label = getProperties().label; (void)tblgen_label;

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Verif4(*this, tblgen_edge, "edge")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Verif1(*this, tblgen_label, "label")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Verif1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSOperands(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Verif2(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup2 = getODSOperands(2);

    if (valueGroup2.size() > 1) {
      return emitOpError("operand group starting at #") << index
          << " requires 0 or 1 element, but found " << valueGroup2.size();
    }

    for (auto v : valueGroup2) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Verif2(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult ClockedCoverOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult ClockedCoverOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::OpAsmParser::UnresolvedOperand propertyRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> propertyOperands(&propertyRawOperand, 1);  ::llvm::SMLoc propertyOperandsLoc;
  (void)propertyOperandsLoc;
  ::llvm::SmallVector<::mlir::OpAsmParser::UnresolvedOperand, 4> enableOperands;
  ::llvm::SMLoc enableOperandsLoc;
  (void)enableOperandsLoc;
  circt::verif::ClockEdgeAttr edgeAttr;
  ::mlir::OpAsmParser::UnresolvedOperand clockRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> clockOperands(&clockRawOperand, 1);  ::llvm::SMLoc clockOperandsLoc;
  (void)clockOperandsLoc;
  ::mlir::StringAttr labelAttr;
  ::mlir::Type propertyRawType{};
  ::llvm::ArrayRef<::mlir::Type> propertyTypes(&propertyRawType, 1);

  propertyOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(propertyRawOperand))
    return ::mlir::failure();
  if (::mlir::succeeded(parser.parseOptionalKeyword("if"))) {

  {
    enableOperandsLoc = parser.getCurrentLocation();
    ::mlir::OpAsmParser::UnresolvedOperand operand;
    ::mlir::OptionalParseResult parseResult =
                                    parser.parseOptionalOperand(operand);
    if (parseResult.has_value()) {
      if (failed(*parseResult))
        return ::mlir::failure();
      enableOperands.push_back(operand);
    }
  }
  }
  if (parser.parseComma())
    return ::mlir::failure();

  {
    ::llvm::StringRef attrStr;
    ::mlir::NamedAttrList attrStorage;
    auto loc = parser.getCurrentLocation();
    if (parser.parseOptionalKeyword(&attrStr, {"posedge","negedge","edge"})) {
      ::mlir::StringAttr attrVal;
      ::mlir::OptionalParseResult parseResult =
        parser.parseOptionalAttribute(attrVal,
                                      parser.getBuilder().getNoneType(),
                                      "edge", attrStorage);
      if (parseResult.has_value()) {
        if (failed(*parseResult))
          return ::mlir::failure();
        attrStr = attrVal.getValue();
      } else {
        return parser.emitError(loc, "expected string or keyword containing one of the following enum values for attribute 'edge' [posedge, negedge, edge]");
      }
    }
    if (!attrStr.empty()) {
      auto attrOptional = circt::verif::symbolizeClockEdge(attrStr);
      if (!attrOptional)
        return parser.emitError(loc, "invalid ")
               << "edge attribute specification: \"" << attrStr << '"';;

      edgeAttr = circt::verif::ClockEdgeAttr::get(parser.getBuilder().getContext(), *attrOptional);
        result.getOrAddProperties<ClockedCoverOp::Properties>().edge = edgeAttr;
    }
  }

  clockOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(clockRawOperand))
    return ::mlir::failure();
  if (::mlir::succeeded(parser.parseOptionalKeyword("label"))) {

  if (parser.parseCustomAttributeWithFallback(labelAttr, parser.getBuilder().getType<::mlir::NoneType>())) {
    return ::mlir::failure();
  }
  if (labelAttr) result.getOrAddProperties<ClockedCoverOp::Properties>().label = labelAttr;
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
  if (parser.parseColon())
    return ::mlir::failure();

  {
    ::mlir::Type type;
    if (parser.parseCustomTypeWithFallback(type))
      return ::mlir::failure();
    propertyRawType = type;
  }
  ::mlir::Type odsBuildableType0 = parser.getBuilder().getIntegerType(1);
  if (parser.resolveOperands(propertyOperands, propertyTypes, propertyOperandsLoc, result.operands))
    return ::mlir::failure();
  if (parser.resolveOperands(clockOperands, odsBuildableType0, clockOperandsLoc, result.operands))
    return ::mlir::failure();
  if (!enableOperands.empty()) {
  if (parser.resolveOperands(enableOperands, odsBuildableType0, enableOperandsLoc, result.operands))
    return ::mlir::failure();
  }
  return ::mlir::success();
}

void ClockedCoverOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter << getProperty();
  if (getEnable()) {
    _odsPrinter << ' ' << "if";
    _odsPrinter << ' ';
    if (::mlir::Value value = getEnable())
      _odsPrinter << value;
  }
  _odsPrinter << ",";
  _odsPrinter << ' ';

  {
    auto caseValue = getEdge();
    auto caseValueStr = stringifyClockEdge(caseValue);
    _odsPrinter << caseValueStr;
  }
  _odsPrinter << ' ';
  _odsPrinter << getClock();
  if (getLabelAttr()) {
    _odsPrinter << ' ' << "label";
    _odsPrinter << ' ';
    _odsPrinter.printAttributeWithoutType(getLabelAttr());
  }
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("edge");
  elidedAttrs.push_back("label");
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
  {
    auto type = getProperty().getType();
    if (auto validType = ::llvm::dyn_cast<::mlir::Type>(type))
      _odsPrinter.printStrippedAttrOrType(validType);
   else
     _odsPrinter << type;
  }
}


} // namespace circt::verif
MLIR_DEFINE_EXPLICIT_TYPE_ID(circt::verif::ClockedCoverOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(circt::verif::detail::ClockedCoverOpGenericAdaptorBase::Properties)

namespace circt::verif {


//===----------------------------------------------------------------------===//
// circt::verif::ContractOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

ContractOpGenericAdaptorBase::ContractOpGenericAdaptorBase(ContractOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

std::pair<unsigned, unsigned> ContractOpGenericAdaptorBase::getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
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
ContractOpAdaptor::ContractOpAdaptor(ContractOp op) : ContractOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult ContractOpAdaptor::verify(::mlir::Location loc) {
  return ::mlir::success();
}

std::pair<unsigned, unsigned> ContractOp::getODSOperandIndexAndLength(unsigned index) {
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

::mlir::MutableOperandRange ContractOp::getInputsMutable() {
  auto range = getODSOperandIndexAndLength(0);
  auto mutableRange = ::mlir::MutableOperandRange(getOperation(), range.first, range.second);
  return mutableRange;
}

std::pair<unsigned, unsigned> ContractOp::getODSResultIndexAndLength(unsigned index) {
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

::llvm::LogicalResult ContractOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }
      return ::mlir::success();
}

::mlir::Attribute ContractOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code ContractOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine();
}

std::optional<mlir::Attribute> ContractOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
  return std::nullopt;
}

void ContractOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
}

void ContractOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
}

::llvm::LogicalResult ContractOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    return ::mlir::success();
}

void ContractOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  for (unsigned i = 0; i != 1; ++i)
    (void)odsState.addRegion();
  odsState.addTypes(resultTypes);
}

ContractOp ContractOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<ContractOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ContractOp ContractOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void ContractOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  for (unsigned i = 0; i != 1; ++i)
    (void)odsState.addRegion();
  odsState.addTypes(resultTypes);
}

ContractOp ContractOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<ContractOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ContractOp ContractOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult ContractOp::verifyInvariantsImpl() {
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Verif3(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Verif3(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  if (!(((this->getODSOperands(0).getType()) == (this->getODSResults(0).getType()) && (this->getODSResults(0).getType()) == (this->getODSOperands(0).getType()))))
    return emitOpError("failed to verify that all of {inputs, outputs} have same type");
  {
    unsigned index = 0; (void)index;

    for (auto &region : ::llvm::MutableArrayRef((*this)->getRegion(0)))
      if (::mlir::failed(__mlir_ods_local_region_constraint_Verif1(*this, region, "body", index++)))
        return ::mlir::failure();
  }
  return ::mlir::success();
}

::llvm::LogicalResult ContractOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult ContractOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::llvm::SmallVector<::mlir::OpAsmParser::UnresolvedOperand, 4> inputsOperands;
  ::llvm::SMLoc inputsOperandsLoc;
  (void)inputsOperandsLoc;
  ::llvm::SmallVector<::mlir::Type, 1> inputsTypes;
  std::unique_ptr<::mlir::Region> bodyRegion = std::make_unique<::mlir::Region>();

  inputsOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperandList(inputsOperands))
    return ::mlir::failure();
  if (!inputsOperands.empty()) {
  if (parser.parseColon())
    return ::mlir::failure();

  if (parser.parseTypeList(inputsTypes))
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

  if (parser.parseRegion(*bodyRegion))
    return ::mlir::failure();

  if (bodyRegion->empty()) bodyRegion->emplaceBlock();
  result.addRegion(std::move(bodyRegion));
  result.addTypes(inputsTypes);
  if (parser.resolveOperands(inputsOperands, inputsTypes, inputsOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void ContractOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  if (!getInputs().empty()) {
    _odsPrinter << ' ';
    _odsPrinter << getInputs();
    _odsPrinter << ' ' << ":";
    _odsPrinter << ' ';
    _odsPrinter << getInputs().getTypes();
  }
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  _odsPrinter.printOptionalAttrDictWithKeyword((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ';
  _odsPrinter.printRegion(getBody());
}


} // namespace circt::verif
MLIR_DEFINE_EXPLICIT_TYPE_ID(circt::verif::ContractOp)

namespace circt::verif {


//===----------------------------------------------------------------------===//
// circt::verif::CoverOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

CoverOpGenericAdaptorBase::CoverOpGenericAdaptorBase(CoverOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

std::pair<unsigned, unsigned> CoverOpGenericAdaptorBase::getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
  bool isVariadic[] = {false, true};
  int prevVariadicCount = 0;
  for (unsigned i = 0; i < index; ++i)
    if (isVariadic[i]) ++prevVariadicCount;

  // Calculate how many dynamic values a static variadic operand corresponds to.
  // This assumes all static variadic operands have the same dynamic value count.
  int variadicSize = (odsOperandsSize - 1) / 1;
  // `index` passed in as the parameter is the static index which counts each
  // operand (variadic or not) as size 1. So here for each previous static variadic
  // operand, we need to offset by (variadicSize - 1) to get where the dynamic
  // value pack for this static operand starts.
  int start = index + (variadicSize - 1) * prevVariadicCount;
  int size = isVariadic[index] ? variadicSize : 1;
  return {start, size};
}

::std::optional< ::llvm::StringRef > CoverOpGenericAdaptorBase::getLabel() {
  auto attr = getLabelAttr();
  return attr ? ::std::optional< ::llvm::StringRef >(attr.getValue()) : (::std::nullopt);
}


} // namespace detail
CoverOpAdaptor::CoverOpAdaptor(CoverOp op) : CoverOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult CoverOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_label = getProperties().label; (void)tblgen_label;

  if (tblgen_label && !((::llvm::isa<::mlir::StringAttr>(tblgen_label))))
    return emitError(loc, "'verif.cover' op attribute 'label' failed to satisfy constraint: string attribute");
  return ::mlir::success();
}

std::pair<unsigned, unsigned> CoverOp::getODSOperandIndexAndLength(unsigned index) {
  bool isVariadic[] = {false, true};
  int prevVariadicCount = 0;
  for (unsigned i = 0; i < index; ++i)
    if (isVariadic[i]) ++prevVariadicCount;

  // Calculate how many dynamic values a static variadic operand corresponds to.
  // This assumes all static variadic operands have the same dynamic value count.
  int variadicSize = (getOperation()->getNumOperands() - 1) / 1;
  // `index` passed in as the parameter is the static index which counts each
  // operand (variadic or not) as size 1. So here for each previous static variadic
  // operand, we need to offset by (variadicSize - 1) to get where the dynamic
  // value pack for this static operand starts.
  int start = index + (variadicSize - 1) * prevVariadicCount;
  int size = isVariadic[index] ? variadicSize : 1;
  return {start, size};
}

::mlir::MutableOperandRange CoverOp::getEnableMutable() {
  auto range = getODSOperandIndexAndLength(1);
  auto mutableRange = ::mlir::MutableOperandRange(getOperation(), range.first, range.second);
  return mutableRange;
}

::llvm::LogicalResult CoverOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.label;
       auto attr = dict.get("label");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `label` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  return ::mlir::success();
}

::mlir::Attribute CoverOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.label;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("label",
                                       propStorage));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code CoverOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.label.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> CoverOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "label")
      return prop.label;
  return std::nullopt;
}

void CoverOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "label") {
       prop.label = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.label)>>(value);
       return;
    }
}

void CoverOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.label) attrs.append("label", prop.label);
}

::llvm::LogicalResult CoverOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getLabelAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Verif1(attr, "label", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult CoverOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readOptionalAttribute(prop.label)))
    return ::mlir::failure();
  return ::mlir::success();
}

void CoverOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;

  writer.writeOptionalAttribute(prop.label);
}

::std::optional< ::llvm::StringRef > CoverOp::getLabel() {
  auto attr = getLabelAttr();
  return attr ? ::std::optional< ::llvm::StringRef >(attr.getValue()) : (::std::nullopt);
}

void CoverOp::setLabel(::std::optional<::llvm::StringRef> attrValue) {
    auto &odsProp = getProperties().label;
    if (attrValue)
      odsProp = ::mlir::Builder((*this)->getContext()).getStringAttr(*attrValue);
    else
      odsProp = nullptr;
}

void CoverOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value property, /*optional*/::mlir::Value enable, /*optional*/::mlir::StringAttr label) {
  odsState.addOperands(property);
  if (enable)
    odsState.addOperands(enable);
  if (label) {
    odsState.getOrAddProperties<Properties>().label = label;
  }
}

CoverOp CoverOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value property, /*optional*/::mlir::Value enable, /*optional*/::mlir::StringAttr label) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(property)>(property), std::forward<decltype(enable)>(enable), std::forward<decltype(label)>(label));
  auto __res__ = ::llvm::dyn_cast<CoverOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

CoverOp CoverOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value property, /*optional*/::mlir::Value enable, /*optional*/::mlir::StringAttr label) {
  return create(builder, builder.getLoc(), std::forward<decltype(property)>(property), std::forward<decltype(enable)>(enable), std::forward<decltype(label)>(label));
}

void CoverOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value property, /*optional*/::mlir::Value enable, /*optional*/::mlir::StringAttr label) {
  odsState.addOperands(property);
  if (enable)
    odsState.addOperands(enable);
  if (label) {
    odsState.getOrAddProperties<Properties>().label = label;
  }
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

CoverOp CoverOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value property, /*optional*/::mlir::Value enable, /*optional*/::mlir::StringAttr label) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(property)>(property), std::forward<decltype(enable)>(enable), std::forward<decltype(label)>(label));
  auto __res__ = ::llvm::dyn_cast<CoverOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

CoverOp CoverOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value property, /*optional*/::mlir::Value enable, /*optional*/::mlir::StringAttr label) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(property)>(property), std::forward<decltype(enable)>(enable), std::forward<decltype(label)>(label));
}

void CoverOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() >= 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<CoverOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

CoverOp CoverOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<CoverOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

CoverOp CoverOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void CoverOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() >= 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

CoverOp CoverOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<CoverOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

CoverOp CoverOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult CoverOp::verifyInvariantsImpl() {
  auto tblgen_label = getProperties().label; (void)tblgen_label;

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Verif1(*this, tblgen_label, "label")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Verif1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSOperands(1);

    if (valueGroup1.size() > 1) {
      return emitOpError("operand group starting at #") << index
          << " requires 0 or 1 element, but found " << valueGroup1.size();
    }

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Verif2(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult CoverOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult CoverOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::OpAsmParser::UnresolvedOperand propertyRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> propertyOperands(&propertyRawOperand, 1);  ::llvm::SMLoc propertyOperandsLoc;
  (void)propertyOperandsLoc;
  ::llvm::SmallVector<::mlir::OpAsmParser::UnresolvedOperand, 4> enableOperands;
  ::llvm::SMLoc enableOperandsLoc;
  (void)enableOperandsLoc;
  ::mlir::StringAttr labelAttr;
  ::mlir::Type propertyRawType{};
  ::llvm::ArrayRef<::mlir::Type> propertyTypes(&propertyRawType, 1);

  propertyOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(propertyRawOperand))
    return ::mlir::failure();
  if (::mlir::succeeded(parser.parseOptionalKeyword("if"))) {

  {
    enableOperandsLoc = parser.getCurrentLocation();
    ::mlir::OpAsmParser::UnresolvedOperand operand;
    ::mlir::OptionalParseResult parseResult =
                                    parser.parseOptionalOperand(operand);
    if (parseResult.has_value()) {
      if (failed(*parseResult))
        return ::mlir::failure();
      enableOperands.push_back(operand);
    }
  }
  }
  if (::mlir::succeeded(parser.parseOptionalKeyword("label"))) {

  if (parser.parseCustomAttributeWithFallback(labelAttr, parser.getBuilder().getType<::mlir::NoneType>())) {
    return ::mlir::failure();
  }
  if (labelAttr) result.getOrAddProperties<CoverOp::Properties>().label = labelAttr;
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
  if (parser.parseColon())
    return ::mlir::failure();

  {
    ::mlir::Type type;
    if (parser.parseCustomTypeWithFallback(type))
      return ::mlir::failure();
    propertyRawType = type;
  }
  ::mlir::Type odsBuildableType0 = parser.getBuilder().getIntegerType(1);
  if (parser.resolveOperands(propertyOperands, propertyTypes, propertyOperandsLoc, result.operands))
    return ::mlir::failure();
  if (!enableOperands.empty()) {
  if (parser.resolveOperands(enableOperands, odsBuildableType0, enableOperandsLoc, result.operands))
    return ::mlir::failure();
  }
  return ::mlir::success();
}

void CoverOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter << getProperty();
  if (getEnable()) {
    _odsPrinter << ' ' << "if";
    _odsPrinter << ' ';
    if (::mlir::Value value = getEnable())
      _odsPrinter << value;
  }
  if (getLabelAttr()) {
    _odsPrinter << ' ' << "label";
    _odsPrinter << ' ';
    _odsPrinter.printAttributeWithoutType(getLabelAttr());
  }
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("label");
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
  {
    auto type = getProperty().getType();
    if (auto validType = ::llvm::dyn_cast<::mlir::Type>(type))
      _odsPrinter.printStrippedAttrOrType(validType);
   else
     _odsPrinter << type;
  }
}


} // namespace circt::verif
MLIR_DEFINE_EXPLICIT_TYPE_ID(circt::verif::CoverOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(circt::verif::detail::CoverOpGenericAdaptorBase::Properties)

namespace circt::verif {


//===----------------------------------------------------------------------===//
// circt::verif::EnsureOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

EnsureOpGenericAdaptorBase::EnsureOpGenericAdaptorBase(EnsureOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

std::pair<unsigned, unsigned> EnsureOpGenericAdaptorBase::getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
  bool isVariadic[] = {false, true};
  int prevVariadicCount = 0;
  for (unsigned i = 0; i < index; ++i)
    if (isVariadic[i]) ++prevVariadicCount;

  // Calculate how many dynamic values a static variadic operand corresponds to.
  // This assumes all static variadic operands have the same dynamic value count.
  int variadicSize = (odsOperandsSize - 1) / 1;
  // `index` passed in as the parameter is the static index which counts each
  // operand (variadic or not) as size 1. So here for each previous static variadic
  // operand, we need to offset by (variadicSize - 1) to get where the dynamic
  // value pack for this static operand starts.
  int start = index + (variadicSize - 1) * prevVariadicCount;
  int size = isVariadic[index] ? variadicSize : 1;
  return {start, size};
}

::std::optional< ::llvm::StringRef > EnsureOpGenericAdaptorBase::getLabel() {
  auto attr = getLabelAttr();
  return attr ? ::std::optional< ::llvm::StringRef >(attr.getValue()) : (::std::nullopt);
}


} // namespace detail
EnsureOpAdaptor::EnsureOpAdaptor(EnsureOp op) : EnsureOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult EnsureOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_label = getProperties().label; (void)tblgen_label;

  if (tblgen_label && !((::llvm::isa<::mlir::StringAttr>(tblgen_label))))
    return emitError(loc, "'verif.ensure' op attribute 'label' failed to satisfy constraint: string attribute");
  return ::mlir::success();
}

std::pair<unsigned, unsigned> EnsureOp::getODSOperandIndexAndLength(unsigned index) {
  bool isVariadic[] = {false, true};
  int prevVariadicCount = 0;
  for (unsigned i = 0; i < index; ++i)
    if (isVariadic[i]) ++prevVariadicCount;

  // Calculate how many dynamic values a static variadic operand corresponds to.
  // This assumes all static variadic operands have the same dynamic value count.
  int variadicSize = (getOperation()->getNumOperands() - 1) / 1;
  // `index` passed in as the parameter is the static index which counts each
  // operand (variadic or not) as size 1. So here for each previous static variadic
  // operand, we need to offset by (variadicSize - 1) to get where the dynamic
  // value pack for this static operand starts.
  int start = index + (variadicSize - 1) * prevVariadicCount;
  int size = isVariadic[index] ? variadicSize : 1;
  return {start, size};
}

::mlir::MutableOperandRange EnsureOp::getEnableMutable() {
  auto range = getODSOperandIndexAndLength(1);
  auto mutableRange = ::mlir::MutableOperandRange(getOperation(), range.first, range.second);
  return mutableRange;
}

::llvm::LogicalResult EnsureOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.label;
       auto attr = dict.get("label");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `label` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  return ::mlir::success();
}

::mlir::Attribute EnsureOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.label;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("label",
                                       propStorage));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code EnsureOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.label.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> EnsureOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "label")
      return prop.label;
  return std::nullopt;
}

void EnsureOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "label") {
       prop.label = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.label)>>(value);
       return;
    }
}

void EnsureOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.label) attrs.append("label", prop.label);
}

::llvm::LogicalResult EnsureOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getLabelAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Verif1(attr, "label", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult EnsureOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readOptionalAttribute(prop.label)))
    return ::mlir::failure();
  return ::mlir::success();
}

void EnsureOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;

  writer.writeOptionalAttribute(prop.label);
}

::std::optional< ::llvm::StringRef > EnsureOp::getLabel() {
  auto attr = getLabelAttr();
  return attr ? ::std::optional< ::llvm::StringRef >(attr.getValue()) : (::std::nullopt);
}

void EnsureOp::setLabel(::std::optional<::llvm::StringRef> attrValue) {
    auto &odsProp = getProperties().label;
    if (attrValue)
      odsProp = ::mlir::Builder((*this)->getContext()).getStringAttr(*attrValue);
    else
      odsProp = nullptr;
}

void EnsureOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value property, /*optional*/::mlir::Value enable, /*optional*/::mlir::StringAttr label) {
  odsState.addOperands(property);
  if (enable)
    odsState.addOperands(enable);
  if (label) {
    odsState.getOrAddProperties<Properties>().label = label;
  }
}

EnsureOp EnsureOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value property, /*optional*/::mlir::Value enable, /*optional*/::mlir::StringAttr label) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(property)>(property), std::forward<decltype(enable)>(enable), std::forward<decltype(label)>(label));
  auto __res__ = ::llvm::dyn_cast<EnsureOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

EnsureOp EnsureOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value property, /*optional*/::mlir::Value enable, /*optional*/::mlir::StringAttr label) {
  return create(builder, builder.getLoc(), std::forward<decltype(property)>(property), std::forward<decltype(enable)>(enable), std::forward<decltype(label)>(label));
}

void EnsureOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value property, /*optional*/::mlir::Value enable, /*optional*/::mlir::StringAttr label) {
  odsState.addOperands(property);
  if (enable)
    odsState.addOperands(enable);
  if (label) {
    odsState.getOrAddProperties<Properties>().label = label;
  }
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

EnsureOp EnsureOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value property, /*optional*/::mlir::Value enable, /*optional*/::mlir::StringAttr label) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(property)>(property), std::forward<decltype(enable)>(enable), std::forward<decltype(label)>(label));
  auto __res__ = ::llvm::dyn_cast<EnsureOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

EnsureOp EnsureOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value property, /*optional*/::mlir::Value enable, /*optional*/::mlir::StringAttr label) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(property)>(property), std::forward<decltype(enable)>(enable), std::forward<decltype(label)>(label));
}

void EnsureOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() >= 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<EnsureOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

EnsureOp EnsureOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<EnsureOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

EnsureOp EnsureOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void EnsureOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() >= 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

EnsureOp EnsureOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<EnsureOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

EnsureOp EnsureOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult EnsureOp::verifyInvariantsImpl() {
  auto tblgen_label = getProperties().label; (void)tblgen_label;

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Verif1(*this, tblgen_label, "label")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Verif1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSOperands(1);

    if (valueGroup1.size() > 1) {
      return emitOpError("operand group starting at #") << index
          << " requires 0 or 1 element, but found " << valueGroup1.size();
    }

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Verif2(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult EnsureOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult EnsureOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::OpAsmParser::UnresolvedOperand propertyRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> propertyOperands(&propertyRawOperand, 1);  ::llvm::SMLoc propertyOperandsLoc;
  (void)propertyOperandsLoc;
  ::llvm::SmallVector<::mlir::OpAsmParser::UnresolvedOperand, 4> enableOperands;
  ::llvm::SMLoc enableOperandsLoc;
  (void)enableOperandsLoc;
  ::mlir::StringAttr labelAttr;
  ::mlir::Type propertyRawType{};
  ::llvm::ArrayRef<::mlir::Type> propertyTypes(&propertyRawType, 1);

  propertyOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(propertyRawOperand))
    return ::mlir::failure();
  if (::mlir::succeeded(parser.parseOptionalKeyword("if"))) {

  {
    enableOperandsLoc = parser.getCurrentLocation();
    ::mlir::OpAsmParser::UnresolvedOperand operand;
    ::mlir::OptionalParseResult parseResult =
                                    parser.parseOptionalOperand(operand);
    if (parseResult.has_value()) {
      if (failed(*parseResult))
        return ::mlir::failure();
      enableOperands.push_back(operand);
    }
  }
  }
  if (::mlir::succeeded(parser.parseOptionalKeyword("label"))) {

  if (parser.parseCustomAttributeWithFallback(labelAttr, parser.getBuilder().getType<::mlir::NoneType>())) {
    return ::mlir::failure();
  }
  if (labelAttr) result.getOrAddProperties<EnsureOp::Properties>().label = labelAttr;
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
  if (parser.parseColon())
    return ::mlir::failure();

  {
    ::mlir::Type type;
    if (parser.parseCustomTypeWithFallback(type))
      return ::mlir::failure();
    propertyRawType = type;
  }
  ::mlir::Type odsBuildableType0 = parser.getBuilder().getIntegerType(1);
  if (parser.resolveOperands(propertyOperands, propertyTypes, propertyOperandsLoc, result.operands))
    return ::mlir::failure();
  if (!enableOperands.empty()) {
  if (parser.resolveOperands(enableOperands, odsBuildableType0, enableOperandsLoc, result.operands))
    return ::mlir::failure();
  }
  return ::mlir::success();
}

void EnsureOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter << getProperty();
  if (getEnable()) {
    _odsPrinter << ' ' << "if";
    _odsPrinter << ' ';
    if (::mlir::Value value = getEnable())
      _odsPrinter << value;
  }
  if (getLabelAttr()) {
    _odsPrinter << ' ' << "label";
    _odsPrinter << ' ';
    _odsPrinter.printAttributeWithoutType(getLabelAttr());
  }
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("label");
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
  {
    auto type = getProperty().getType();
    if (auto validType = ::llvm::dyn_cast<::mlir::Type>(type))
      _odsPrinter.printStrippedAttrOrType(validType);
   else
     _odsPrinter << type;
  }
}


} // namespace circt::verif
MLIR_DEFINE_EXPLICIT_TYPE_ID(circt::verif::EnsureOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(circt::verif::detail::EnsureOpGenericAdaptorBase::Properties)

namespace circt::verif {


//===----------------------------------------------------------------------===//
// circt::verif::FormalOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

FormalOpGenericAdaptorBase::FormalOpGenericAdaptorBase(FormalOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::llvm::StringRef FormalOpGenericAdaptorBase::getSymName() {
  auto attr = getSymNameAttr();
  return attr.getValue();
}

::mlir::DictionaryAttr FormalOpGenericAdaptorBase::getParameters() {
  auto attr = getParametersAttr();
  return attr;
}


} // namespace detail
FormalOpAdaptor::FormalOpAdaptor(FormalOp op) : FormalOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult FormalOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_parameters = getProperties().parameters; (void)tblgen_parameters;
  if (!tblgen_parameters) return emitError(loc, "'verif.formal' op requires attribute 'parameters'");
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;
  if (!tblgen_sym_name) return emitError(loc, "'verif.formal' op requires attribute 'sym_name'");

  if (tblgen_sym_name && !((::llvm::isa<::mlir::StringAttr>(tblgen_sym_name))))
    return emitError(loc, "'verif.formal' op attribute 'sym_name' failed to satisfy constraint: string attribute");

  if (tblgen_parameters && !((::llvm::isa<::mlir::DictionaryAttr>(tblgen_parameters))))
    return emitError(loc, "'verif.formal' op attribute 'parameters' failed to satisfy constraint: dictionary of named attribute values");
  return ::mlir::success();
}

::llvm::LogicalResult FormalOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.parameters;
       auto attr = dict.get("parameters");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `parameters` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.sym_name;
       auto attr = dict.get("sym_name");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `sym_name` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  return ::mlir::success();
}

::mlir::Attribute FormalOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.parameters;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("parameters",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.sym_name;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("sym_name",
                                       propStorage));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code FormalOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.parameters.getAsOpaquePointer()), 
    llvm::hash_value(prop.sym_name.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> FormalOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "parameters")
      return prop.parameters;

    if (name == "sym_name")
      return prop.sym_name;
  return std::nullopt;
}

void FormalOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "parameters") {
       prop.parameters = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.parameters)>>(value);
       return;
    }

    if (name == "sym_name") {
       prop.sym_name = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.sym_name)>>(value);
       return;
    }
}

void FormalOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.parameters) attrs.append("parameters", prop.parameters);

    if (prop.sym_name) attrs.append("sym_name", prop.sym_name);
}

::llvm::LogicalResult FormalOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getParametersAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Verif5(attr, "parameters", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getSymNameAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Verif1(attr, "sym_name", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult FormalOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.parameters)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readAttribute(prop.sym_name)))
    return ::mlir::failure();
  return ::mlir::success();
}

void FormalOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.parameters);
  writer.writeAttribute(prop.sym_name);
}

::llvm::StringRef FormalOp::getSymName() {
  auto attr = getSymNameAttr();
  return attr.getValue();
}

::mlir::DictionaryAttr FormalOp::getParameters() {
  auto attr = getParametersAttr();
  return attr;
}

void FormalOp::setSymName(::llvm::StringRef attrValue) {
  getProperties().sym_name = ::mlir::Builder((*this)->getContext()).getStringAttr(attrValue);
}

void FormalOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::StringAttr sym_name, ::mlir::DictionaryAttr parameters) {
  odsState.getOrAddProperties<Properties>().sym_name = sym_name;
  odsState.getOrAddProperties<Properties>().parameters = parameters;
  (void)odsState.addRegion();
}

FormalOp FormalOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::StringAttr sym_name, ::mlir::DictionaryAttr parameters) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(parameters)>(parameters));
  auto __res__ = ::llvm::dyn_cast<FormalOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

FormalOp FormalOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::StringAttr sym_name, ::mlir::DictionaryAttr parameters) {
  return create(builder, builder.getLoc(), std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(parameters)>(parameters));
}

void FormalOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name, ::mlir::DictionaryAttr parameters) {
  odsState.getOrAddProperties<Properties>().sym_name = sym_name;
  odsState.getOrAddProperties<Properties>().parameters = parameters;
  (void)odsState.addRegion();
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

FormalOp FormalOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name, ::mlir::DictionaryAttr parameters) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(parameters)>(parameters));
  auto __res__ = ::llvm::dyn_cast<FormalOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

FormalOp FormalOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name, ::mlir::DictionaryAttr parameters) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(parameters)>(parameters));
}

void FormalOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::llvm::StringRef sym_name, ::mlir::DictionaryAttr parameters) {
  odsState.getOrAddProperties<Properties>().sym_name = odsBuilder.getStringAttr(sym_name);
  odsState.getOrAddProperties<Properties>().parameters = parameters;
  (void)odsState.addRegion();
}

FormalOp FormalOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::llvm::StringRef sym_name, ::mlir::DictionaryAttr parameters) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(parameters)>(parameters));
  auto __res__ = ::llvm::dyn_cast<FormalOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

FormalOp FormalOp::create(::mlir::ImplicitLocOpBuilder &builder, ::llvm::StringRef sym_name, ::mlir::DictionaryAttr parameters) {
  return create(builder, builder.getLoc(), std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(parameters)>(parameters));
}

void FormalOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name, ::mlir::DictionaryAttr parameters) {
  odsState.getOrAddProperties<Properties>().sym_name = odsBuilder.getStringAttr(sym_name);
  odsState.getOrAddProperties<Properties>().parameters = parameters;
  (void)odsState.addRegion();
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

FormalOp FormalOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name, ::mlir::DictionaryAttr parameters) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(parameters)>(parameters));
  auto __res__ = ::llvm::dyn_cast<FormalOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

FormalOp FormalOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name, ::mlir::DictionaryAttr parameters) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(parameters)>(parameters));
}

void FormalOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  for (unsigned i = 0; i != 1; ++i)
    (void)odsState.addRegion();
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<FormalOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

FormalOp FormalOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<FormalOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

FormalOp FormalOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void FormalOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  for (unsigned i = 0; i != 1; ++i)
    (void)odsState.addRegion();
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

FormalOp FormalOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<FormalOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

FormalOp FormalOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult FormalOp::verifyInvariantsImpl() {
  auto tblgen_parameters = getProperties().parameters; (void)tblgen_parameters;
  if (!tblgen_parameters) return emitOpError("requires attribute 'parameters'");
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;
  if (!tblgen_sym_name) return emitOpError("requires attribute 'sym_name'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Verif1(*this, tblgen_sym_name, "sym_name")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Verif5(*this, tblgen_parameters, "parameters")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;

    for (auto &region : ::llvm::MutableArrayRef((*this)->getRegion(0)))
      if (::mlir::failed(__mlir_ods_local_region_constraint_Verif1(*this, region, "body", index++)))
        return ::mlir::failure();
  }
  return ::mlir::success();
}

::llvm::LogicalResult FormalOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult FormalOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::StringAttr sym_nameAttr;
  ::mlir::DictionaryAttr parametersAttr;
  std::unique_ptr<::mlir::Region> bodyRegion = std::make_unique<::mlir::Region>();

  if (parser.parseSymbolName(sym_nameAttr))
    return ::mlir::failure();
  if (sym_nameAttr) result.getOrAddProperties<FormalOp::Properties>().sym_name = sym_nameAttr;

  if (parser.parseCustomAttributeWithFallback(parametersAttr, parser.getBuilder().getType<::mlir::NoneType>())) {
    return ::mlir::failure();
  }
  if (parametersAttr) result.getOrAddProperties<FormalOp::Properties>().parameters = parametersAttr;
  {
    auto loc = parser.getCurrentLocation();(void)loc;
    if (parser.parseOptionalAttrDictWithKeyword(result.attributes))
      return ::mlir::failure();
    if (failed(verifyInherentAttrs(result.name, result.attributes, [&]() {
        return parser.emitError(loc) << "'" << result.name.getStringRef() << "' op ";
      })))
      return ::mlir::failure();
  }

  if (parser.parseRegion(*bodyRegion))
    return ::mlir::failure();

  if (bodyRegion->empty()) bodyRegion->emplaceBlock();
  result.addRegion(std::move(bodyRegion));
  return ::mlir::success();
}

void FormalOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter.printSymbolName(getSymNameAttr().getValue());
  _odsPrinter << ' ';
  _odsPrinter.printAttributeWithoutType(getParametersAttr());
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("sym_name");
  elidedAttrs.push_back("parameters");
  _odsPrinter.printOptionalAttrDictWithKeyword((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ';
  _odsPrinter.printRegion(getBody());
}


} // namespace circt::verif
MLIR_DEFINE_EXPLICIT_TYPE_ID(circt::verif::FormalOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(circt::verif::detail::FormalOpGenericAdaptorBase::Properties)

namespace circt::verif {


//===----------------------------------------------------------------------===//
// circt::verif::FormatVerilogStringOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

FormatVerilogStringOpGenericAdaptorBase::FormatVerilogStringOpGenericAdaptorBase(FormatVerilogStringOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

std::pair<unsigned, unsigned> FormatVerilogStringOpGenericAdaptorBase::getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
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

::llvm::StringRef FormatVerilogStringOpGenericAdaptorBase::getFormatString() {
  auto attr = getFormatStringAttr();
  return attr.getValue();
}


} // namespace detail
FormatVerilogStringOpAdaptor::FormatVerilogStringOpAdaptor(FormatVerilogStringOp op) : FormatVerilogStringOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult FormatVerilogStringOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_formatString = getProperties().formatString; (void)tblgen_formatString;
  if (!tblgen_formatString) return emitError(loc, "'verif.format_verilog_string' op requires attribute 'formatString'");

  if (tblgen_formatString && !((::llvm::isa<::mlir::StringAttr>(tblgen_formatString))))
    return emitError(loc, "'verif.format_verilog_string' op attribute 'formatString' failed to satisfy constraint: string attribute");
  return ::mlir::success();
}

std::pair<unsigned, unsigned> FormatVerilogStringOp::getODSOperandIndexAndLength(unsigned index) {
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

::mlir::MutableOperandRange FormatVerilogStringOp::getSubstitutionsMutable() {
  auto range = getODSOperandIndexAndLength(0);
  auto mutableRange = ::mlir::MutableOperandRange(getOperation(), range.first, range.second);
  return mutableRange;
}

::llvm::LogicalResult FormatVerilogStringOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.formatString;
       auto attr = dict.get("formatString");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `formatString` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  return ::mlir::success();
}

::mlir::Attribute FormatVerilogStringOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.formatString;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("formatString",
                                       propStorage));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code FormatVerilogStringOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.formatString.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> FormatVerilogStringOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "formatString")
      return prop.formatString;
  return std::nullopt;
}

void FormatVerilogStringOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "formatString") {
       prop.formatString = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.formatString)>>(value);
       return;
    }
}

void FormatVerilogStringOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.formatString) attrs.append("formatString", prop.formatString);
}

::llvm::LogicalResult FormatVerilogStringOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getFormatStringAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Verif1(attr, "formatString", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult FormatVerilogStringOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.formatString)))
    return ::mlir::failure();
  return ::mlir::success();
}

void FormatVerilogStringOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.formatString);
}

::llvm::StringRef FormatVerilogStringOp::getFormatString() {
  auto attr = getFormatStringAttr();
  return attr.getValue();
}

void FormatVerilogStringOp::setFormatString(::llvm::StringRef attrValue) {
  getProperties().formatString = ::mlir::Builder((*this)->getContext()).getStringAttr(attrValue);
}

void FormatVerilogStringOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type str, ::mlir::StringAttr formatString, ::mlir::ValueRange substitutions) {
  odsState.addOperands(substitutions);
  odsState.getOrAddProperties<Properties>().formatString = formatString;
  odsState.addTypes(str);
}

FormatVerilogStringOp FormatVerilogStringOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type str, ::mlir::StringAttr formatString, ::mlir::ValueRange substitutions) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(str)>(str), std::forward<decltype(formatString)>(formatString), std::forward<decltype(substitutions)>(substitutions));
  auto __res__ = ::llvm::dyn_cast<FormatVerilogStringOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

FormatVerilogStringOp FormatVerilogStringOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type str, ::mlir::StringAttr formatString, ::mlir::ValueRange substitutions) {
  return create(builder, builder.getLoc(), std::forward<decltype(str)>(str), std::forward<decltype(formatString)>(formatString), std::forward<decltype(substitutions)>(substitutions));
}

void FormatVerilogStringOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::StringAttr formatString, ::mlir::ValueRange substitutions) {
  odsState.addOperands(substitutions);
  odsState.getOrAddProperties<Properties>().formatString = formatString;

        ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
        if (::mlir::succeeded(FormatVerilogStringOp::inferReturnTypes(odsBuilder.getContext(),
                      odsState.location, odsState.operands,
                      odsState.attributes.getDictionary(odsState.getContext()),
                      odsState.getRawProperties(),
                      odsState.regions, inferredReturnTypes)))
          odsState.addTypes(inferredReturnTypes);
        else
          ::mlir::detail::reportFatalInferReturnTypesError(odsState);
        
}

FormatVerilogStringOp FormatVerilogStringOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::StringAttr formatString, ::mlir::ValueRange substitutions) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(formatString)>(formatString), std::forward<decltype(substitutions)>(substitutions));
  auto __res__ = ::llvm::dyn_cast<FormatVerilogStringOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

FormatVerilogStringOp FormatVerilogStringOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::StringAttr formatString, ::mlir::ValueRange substitutions) {
  return create(builder, builder.getLoc(), std::forward<decltype(formatString)>(formatString), std::forward<decltype(substitutions)>(substitutions));
}

void FormatVerilogStringOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::StringAttr formatString, ::mlir::ValueRange substitutions) {
  odsState.addOperands(substitutions);
  odsState.getOrAddProperties<Properties>().formatString = formatString;
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

FormatVerilogStringOp FormatVerilogStringOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::StringAttr formatString, ::mlir::ValueRange substitutions) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(formatString)>(formatString), std::forward<decltype(substitutions)>(substitutions));
  auto __res__ = ::llvm::dyn_cast<FormatVerilogStringOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

FormatVerilogStringOp FormatVerilogStringOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::StringAttr formatString, ::mlir::ValueRange substitutions) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(formatString)>(formatString), std::forward<decltype(substitutions)>(substitutions));
}

void FormatVerilogStringOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type str, ::llvm::StringRef formatString, ::mlir::ValueRange substitutions) {
  odsState.addOperands(substitutions);
  odsState.getOrAddProperties<Properties>().formatString = odsBuilder.getStringAttr(formatString);
  odsState.addTypes(str);
}

FormatVerilogStringOp FormatVerilogStringOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type str, ::llvm::StringRef formatString, ::mlir::ValueRange substitutions) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(str)>(str), std::forward<decltype(formatString)>(formatString), std::forward<decltype(substitutions)>(substitutions));
  auto __res__ = ::llvm::dyn_cast<FormatVerilogStringOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

FormatVerilogStringOp FormatVerilogStringOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type str, ::llvm::StringRef formatString, ::mlir::ValueRange substitutions) {
  return create(builder, builder.getLoc(), std::forward<decltype(str)>(str), std::forward<decltype(formatString)>(formatString), std::forward<decltype(substitutions)>(substitutions));
}

void FormatVerilogStringOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::llvm::StringRef formatString, ::mlir::ValueRange substitutions) {
  odsState.addOperands(substitutions);
  odsState.getOrAddProperties<Properties>().formatString = odsBuilder.getStringAttr(formatString);

        ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
        if (::mlir::succeeded(FormatVerilogStringOp::inferReturnTypes(odsBuilder.getContext(),
                      odsState.location, odsState.operands,
                      odsState.attributes.getDictionary(odsState.getContext()),
                      odsState.getRawProperties(),
                      odsState.regions, inferredReturnTypes)))
          odsState.addTypes(inferredReturnTypes);
        else
          ::mlir::detail::reportFatalInferReturnTypesError(odsState);
        
}

FormatVerilogStringOp FormatVerilogStringOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::llvm::StringRef formatString, ::mlir::ValueRange substitutions) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(formatString)>(formatString), std::forward<decltype(substitutions)>(substitutions));
  auto __res__ = ::llvm::dyn_cast<FormatVerilogStringOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

FormatVerilogStringOp FormatVerilogStringOp::create(::mlir::ImplicitLocOpBuilder &builder, ::llvm::StringRef formatString, ::mlir::ValueRange substitutions) {
  return create(builder, builder.getLoc(), std::forward<decltype(formatString)>(formatString), std::forward<decltype(substitutions)>(substitutions));
}

void FormatVerilogStringOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::llvm::StringRef formatString, ::mlir::ValueRange substitutions) {
  odsState.addOperands(substitutions);
  odsState.getOrAddProperties<Properties>().formatString = odsBuilder.getStringAttr(formatString);
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

FormatVerilogStringOp FormatVerilogStringOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::llvm::StringRef formatString, ::mlir::ValueRange substitutions) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(formatString)>(formatString), std::forward<decltype(substitutions)>(substitutions));
  auto __res__ = ::llvm::dyn_cast<FormatVerilogStringOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

FormatVerilogStringOp FormatVerilogStringOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::llvm::StringRef formatString, ::mlir::ValueRange substitutions) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(formatString)>(formatString), std::forward<decltype(substitutions)>(substitutions));
}

void FormatVerilogStringOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<FormatVerilogStringOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

FormatVerilogStringOp FormatVerilogStringOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<FormatVerilogStringOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

FormatVerilogStringOp FormatVerilogStringOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void FormatVerilogStringOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<FormatVerilogStringOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
  ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
  if (::mlir::succeeded(FormatVerilogStringOp::inferReturnTypes(odsBuilder.getContext(),
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

FormatVerilogStringOp FormatVerilogStringOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<FormatVerilogStringOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

FormatVerilogStringOp FormatVerilogStringOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void FormatVerilogStringOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

FormatVerilogStringOp FormatVerilogStringOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<FormatVerilogStringOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

FormatVerilogStringOp FormatVerilogStringOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

void FormatVerilogStringOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties &>(properties));
  odsState.addAttributes(discardableAttributes);

  ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
  if (::mlir::succeeded(FormatVerilogStringOp::inferReturnTypes(odsBuilder.getContext(),
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

FormatVerilogStringOp FormatVerilogStringOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<FormatVerilogStringOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

FormatVerilogStringOp FormatVerilogStringOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult FormatVerilogStringOp::verifyInvariantsImpl() {
  auto tblgen_formatString = getProperties().formatString; (void)tblgen_formatString;
  if (!tblgen_formatString) return emitOpError("requires attribute 'formatString'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Verif1(*this, tblgen_formatString, "formatString")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Verif3(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Verif4(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult FormatVerilogStringOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::llvm::LogicalResult FormatVerilogStringOp::inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::PropertyRef properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes) {
  inferredReturnTypes.resize(1);
  ::mlir::Builder odsBuilder(context);
  ::mlir::Type odsInferredType0 = ::circt::hw::StringType::get(odsBuilder.getContext());
  inferredReturnTypes[0] = odsInferredType0;
  return ::mlir::success();
}

::mlir::ParseResult FormatVerilogStringOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::StringAttr formatStringAttr;
  ::llvm::SmallVector<::mlir::OpAsmParser::UnresolvedOperand, 4> substitutionsOperands;
  ::llvm::SMLoc substitutionsOperandsLoc;
  (void)substitutionsOperandsLoc;
  ::llvm::SmallVector<::mlir::Type, 1> substitutionsTypes;

  if (parser.parseCustomAttributeWithFallback(formatStringAttr, parser.getBuilder().getType<::mlir::NoneType>())) {
    return ::mlir::failure();
  }
  if (formatStringAttr) result.getOrAddProperties<FormatVerilogStringOp::Properties>().formatString = formatStringAttr;
  if (parser.parseLParen())
    return ::mlir::failure();

  substitutionsOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperandList(substitutionsOperands))
    return ::mlir::failure();
  if (parser.parseRParen())
    return ::mlir::failure();
  if (parser.parseColon())
    return ::mlir::failure();

  if (parser.parseTypeList(substitutionsTypes))
    return ::mlir::failure();
  {
    auto loc = parser.getCurrentLocation();(void)loc;
    if (parser.parseOptionalAttrDict(result.attributes))
      return ::mlir::failure();
    if (failed(verifyInherentAttrs(result.name, result.attributes, [&]() {
        return parser.emitError(loc) << "'" << result.name.getStringRef() << "' op ";
      })))
      return ::mlir::failure();
  }
  ::mlir::Type odsBuildableType0 = ::circt::hw::StringType::get(parser.getBuilder().getContext());
  result.addTypes(odsBuildableType0);
  if (parser.resolveOperands(substitutionsOperands, substitutionsTypes, substitutionsOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void FormatVerilogStringOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter.printAttributeWithoutType(getFormatStringAttr());
  _odsPrinter << "(";
  _odsPrinter << getSubstitutions();
  _odsPrinter << ")";
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
  _odsPrinter << getSubstitutions().getTypes();
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("formatString");
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
}

void FormatVerilogStringOp::getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects) {
}


} // namespace circt::verif
MLIR_DEFINE_EXPLICIT_TYPE_ID(circt::verif::FormatVerilogStringOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(circt::verif::detail::FormatVerilogStringOpGenericAdaptorBase::Properties)

namespace circt::verif {


//===----------------------------------------------------------------------===//
// circt::verif::HasBeenResetOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

HasBeenResetOpGenericAdaptorBase::HasBeenResetOpGenericAdaptorBase(HasBeenResetOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

bool HasBeenResetOpGenericAdaptorBase::getAsync() {
  auto attr = getAsyncAttr();
  return attr.getValue();
}


} // namespace detail
HasBeenResetOpAdaptor::HasBeenResetOpAdaptor(HasBeenResetOp op) : HasBeenResetOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult HasBeenResetOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_async = getProperties().async; (void)tblgen_async;
  if (!tblgen_async) return emitError(loc, "'verif.has_been_reset' op requires attribute 'async'");

  if (tblgen_async && !((::llvm::isa<::mlir::BoolAttr>(tblgen_async))))
    return emitError(loc, "'verif.has_been_reset' op attribute 'async' failed to satisfy constraint: bool attribute");
  return ::mlir::success();
}

::llvm::LogicalResult HasBeenResetOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.async;
       auto attr = dict.get("async");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `async` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  return ::mlir::success();
}

::mlir::Attribute HasBeenResetOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.async;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("async",
                                       propStorage));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code HasBeenResetOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.async.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> HasBeenResetOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "async")
      return prop.async;
  return std::nullopt;
}

void HasBeenResetOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "async") {
       prop.async = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.async)>>(value);
       return;
    }
}

void HasBeenResetOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.async) attrs.append("async", prop.async);
}

::llvm::LogicalResult HasBeenResetOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getAsyncAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Verif6(attr, "async", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult HasBeenResetOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.async)))
    return ::mlir::failure();
  return ::mlir::success();
}

void HasBeenResetOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.async);
}

bool HasBeenResetOp::getAsync() {
  auto attr = getAsyncAttr();
  return attr.getValue();
}

void HasBeenResetOp::setAsync(bool attrValue) {
  getProperties().async = ::mlir::Builder((*this)->getContext()).getBoolAttr(attrValue);
}

void HasBeenResetOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value clock, ::mlir::Value reset, ::mlir::BoolAttr async) {
  odsState.addOperands(clock);
  odsState.addOperands(reset);
  odsState.getOrAddProperties<Properties>().async = async;
  odsState.addTypes(result);
}

HasBeenResetOp HasBeenResetOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value clock, ::mlir::Value reset, ::mlir::BoolAttr async) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(result)>(result), std::forward<decltype(clock)>(clock), std::forward<decltype(reset)>(reset), std::forward<decltype(async)>(async));
  auto __res__ = ::llvm::dyn_cast<HasBeenResetOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

HasBeenResetOp HasBeenResetOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value clock, ::mlir::Value reset, ::mlir::BoolAttr async) {
  return create(builder, builder.getLoc(), std::forward<decltype(result)>(result), std::forward<decltype(clock)>(clock), std::forward<decltype(reset)>(reset), std::forward<decltype(async)>(async));
}

void HasBeenResetOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value clock, ::mlir::Value reset, ::mlir::BoolAttr async) {
  odsState.addOperands(clock);
  odsState.addOperands(reset);
  odsState.getOrAddProperties<Properties>().async = async;

        ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
        if (::mlir::succeeded(HasBeenResetOp::inferReturnTypes(odsBuilder.getContext(),
                      odsState.location, odsState.operands,
                      odsState.attributes.getDictionary(odsState.getContext()),
                      odsState.getRawProperties(),
                      odsState.regions, inferredReturnTypes)))
          odsState.addTypes(inferredReturnTypes);
        else
          ::mlir::detail::reportFatalInferReturnTypesError(odsState);
        
}

HasBeenResetOp HasBeenResetOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value clock, ::mlir::Value reset, ::mlir::BoolAttr async) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(clock)>(clock), std::forward<decltype(reset)>(reset), std::forward<decltype(async)>(async));
  auto __res__ = ::llvm::dyn_cast<HasBeenResetOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

HasBeenResetOp HasBeenResetOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value clock, ::mlir::Value reset, ::mlir::BoolAttr async) {
  return create(builder, builder.getLoc(), std::forward<decltype(clock)>(clock), std::forward<decltype(reset)>(reset), std::forward<decltype(async)>(async));
}

void HasBeenResetOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value clock, ::mlir::Value reset, ::mlir::BoolAttr async) {
  odsState.addOperands(clock);
  odsState.addOperands(reset);
  odsState.getOrAddProperties<Properties>().async = async;
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

HasBeenResetOp HasBeenResetOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value clock, ::mlir::Value reset, ::mlir::BoolAttr async) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(clock)>(clock), std::forward<decltype(reset)>(reset), std::forward<decltype(async)>(async));
  auto __res__ = ::llvm::dyn_cast<HasBeenResetOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

HasBeenResetOp HasBeenResetOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value clock, ::mlir::Value reset, ::mlir::BoolAttr async) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(clock)>(clock), std::forward<decltype(reset)>(reset), std::forward<decltype(async)>(async));
}

void HasBeenResetOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value clock, ::mlir::Value reset, bool async) {
  odsState.addOperands(clock);
  odsState.addOperands(reset);
  odsState.getOrAddProperties<Properties>().async = odsBuilder.getBoolAttr(async);
  odsState.addTypes(result);
}

HasBeenResetOp HasBeenResetOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value clock, ::mlir::Value reset, bool async) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(result)>(result), std::forward<decltype(clock)>(clock), std::forward<decltype(reset)>(reset), std::forward<decltype(async)>(async));
  auto __res__ = ::llvm::dyn_cast<HasBeenResetOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

HasBeenResetOp HasBeenResetOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value clock, ::mlir::Value reset, bool async) {
  return create(builder, builder.getLoc(), std::forward<decltype(result)>(result), std::forward<decltype(clock)>(clock), std::forward<decltype(reset)>(reset), std::forward<decltype(async)>(async));
}

void HasBeenResetOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value clock, ::mlir::Value reset, bool async) {
  odsState.addOperands(clock);
  odsState.addOperands(reset);
  odsState.getOrAddProperties<Properties>().async = odsBuilder.getBoolAttr(async);

        ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
        if (::mlir::succeeded(HasBeenResetOp::inferReturnTypes(odsBuilder.getContext(),
                      odsState.location, odsState.operands,
                      odsState.attributes.getDictionary(odsState.getContext()),
                      odsState.getRawProperties(),
                      odsState.regions, inferredReturnTypes)))
          odsState.addTypes(inferredReturnTypes);
        else
          ::mlir::detail::reportFatalInferReturnTypesError(odsState);
        
}

HasBeenResetOp HasBeenResetOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value clock, ::mlir::Value reset, bool async) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(clock)>(clock), std::forward<decltype(reset)>(reset), std::forward<decltype(async)>(async));
  auto __res__ = ::llvm::dyn_cast<HasBeenResetOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

HasBeenResetOp HasBeenResetOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value clock, ::mlir::Value reset, bool async) {
  return create(builder, builder.getLoc(), std::forward<decltype(clock)>(clock), std::forward<decltype(reset)>(reset), std::forward<decltype(async)>(async));
}

void HasBeenResetOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value clock, ::mlir::Value reset, bool async) {
  odsState.addOperands(clock);
  odsState.addOperands(reset);
  odsState.getOrAddProperties<Properties>().async = odsBuilder.getBoolAttr(async);
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

HasBeenResetOp HasBeenResetOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value clock, ::mlir::Value reset, bool async) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(clock)>(clock), std::forward<decltype(reset)>(reset), std::forward<decltype(async)>(async));
  auto __res__ = ::llvm::dyn_cast<HasBeenResetOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

HasBeenResetOp HasBeenResetOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value clock, ::mlir::Value reset, bool async) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(clock)>(clock), std::forward<decltype(reset)>(reset), std::forward<decltype(async)>(async));
}

void HasBeenResetOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 2u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<HasBeenResetOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

HasBeenResetOp HasBeenResetOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<HasBeenResetOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

HasBeenResetOp HasBeenResetOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void HasBeenResetOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 2u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<HasBeenResetOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
  ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
  if (::mlir::succeeded(HasBeenResetOp::inferReturnTypes(odsBuilder.getContext(),
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

HasBeenResetOp HasBeenResetOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<HasBeenResetOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

HasBeenResetOp HasBeenResetOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void HasBeenResetOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 2u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

HasBeenResetOp HasBeenResetOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<HasBeenResetOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

HasBeenResetOp HasBeenResetOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

void HasBeenResetOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 2u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties &>(properties));
  odsState.addAttributes(discardableAttributes);

  ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
  if (::mlir::succeeded(HasBeenResetOp::inferReturnTypes(odsBuilder.getContext(),
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

HasBeenResetOp HasBeenResetOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<HasBeenResetOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

HasBeenResetOp HasBeenResetOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult HasBeenResetOp::verifyInvariantsImpl() {
  auto tblgen_async = getProperties().async; (void)tblgen_async;
  if (!tblgen_async) return emitOpError("requires attribute 'async'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Verif6(*this, tblgen_async, "async")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Verif2(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSOperands(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Verif2(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Verif2(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult HasBeenResetOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::llvm::LogicalResult HasBeenResetOp::inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::PropertyRef properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes) {
  inferredReturnTypes.resize(1);
  ::mlir::Builder odsBuilder(context);
  ::mlir::Type odsInferredType0 = odsBuilder.getIntegerType(1);
  inferredReturnTypes[0] = odsInferredType0;
  return ::mlir::success();
}

::mlir::ParseResult HasBeenResetOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::OpAsmParser::UnresolvedOperand clockRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> clockOperands(&clockRawOperand, 1);  ::llvm::SMLoc clockOperandsLoc;
  (void)clockOperandsLoc;
  ::mlir::BoolAttr asyncAttr;
  ::mlir::OpAsmParser::UnresolvedOperand resetRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> resetOperands(&resetRawOperand, 1);  ::llvm::SMLoc resetOperandsLoc;
  (void)resetOperandsLoc;

  clockOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(clockRawOperand))
    return ::mlir::failure();
  if (parser.parseComma())
    return ::mlir::failure();
  {
    auto odsResult = parseKeywordBool(parser, asyncAttr, "async", "sync");
    if (odsResult) return ::mlir::failure();
    result.getOrAddProperties<HasBeenResetOp::Properties>().async = asyncAttr;
  }

  resetOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(resetRawOperand))
    return ::mlir::failure();
  {
    auto loc = parser.getCurrentLocation();(void)loc;
    if (parser.parseOptionalAttrDict(result.attributes))
      return ::mlir::failure();
    if (failed(verifyInherentAttrs(result.name, result.attributes, [&]() {
        return parser.emitError(loc) << "'" << result.name.getStringRef() << "' op ";
      })))
      return ::mlir::failure();
  }
  ::mlir::Type odsBuildableType0 = parser.getBuilder().getIntegerType(1);
  result.addTypes(odsBuildableType0);
  if (parser.resolveOperands(clockOperands, odsBuildableType0, clockOperandsLoc, result.operands))
    return ::mlir::failure();
  if (parser.resolveOperands(resetOperands, odsBuildableType0, resetOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void HasBeenResetOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter << getClock();
  _odsPrinter << ",";
  _odsPrinter << ' ';
  printKeywordBool(_odsPrinter, *this, getAsyncAttr(), "async", "sync");
  _odsPrinter << ' ';
  _odsPrinter << getReset();
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("async");
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
}

void HasBeenResetOp::getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects) {
}


} // namespace circt::verif
MLIR_DEFINE_EXPLICIT_TYPE_ID(circt::verif::HasBeenResetOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(circt::verif::detail::HasBeenResetOpGenericAdaptorBase::Properties)

namespace circt::verif {


//===----------------------------------------------------------------------===//
// circt::verif::LogicEquivalenceCheckingOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

LogicEquivalenceCheckingOpGenericAdaptorBase::LogicEquivalenceCheckingOpGenericAdaptorBase(LogicEquivalenceCheckingOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}


} // namespace detail
LogicEquivalenceCheckingOpAdaptor::LogicEquivalenceCheckingOpAdaptor(LogicEquivalenceCheckingOp op) : LogicEquivalenceCheckingOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult LogicEquivalenceCheckingOpAdaptor::verify(::mlir::Location loc) {
  return ::mlir::success();
}

std::pair<unsigned, unsigned> LogicEquivalenceCheckingOp::getODSResultIndexAndLength(unsigned index) {
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

::llvm::LogicalResult LogicEquivalenceCheckingOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }
      return ::mlir::success();
}

::mlir::Attribute LogicEquivalenceCheckingOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code LogicEquivalenceCheckingOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine();
}

std::optional<mlir::Attribute> LogicEquivalenceCheckingOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
  return std::nullopt;
}

void LogicEquivalenceCheckingOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
}

void LogicEquivalenceCheckingOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
}

::llvm::LogicalResult LogicEquivalenceCheckingOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    return ::mlir::success();
}

void LogicEquivalenceCheckingOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, bool hasResult) {
      build(odsBuilder, odsState, hasResult ? odsBuilder.getI1Type() : Type{} );
    
}

LogicEquivalenceCheckingOp LogicEquivalenceCheckingOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, bool hasResult) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(hasResult)>(hasResult));
  auto __res__ = ::llvm::dyn_cast<LogicEquivalenceCheckingOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

LogicEquivalenceCheckingOp LogicEquivalenceCheckingOp::create(::mlir::ImplicitLocOpBuilder &builder, bool hasResult) {
  return create(builder, builder.getLoc(), std::forward<decltype(hasResult)>(hasResult));
}

void LogicEquivalenceCheckingOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, /*optional*/::mlir::Type isProven) {
  (void)odsState.addRegion();
  (void)odsState.addRegion();
  if (isProven)
    odsState.addTypes(isProven);
}

LogicEquivalenceCheckingOp LogicEquivalenceCheckingOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, /*optional*/::mlir::Type isProven) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(isProven)>(isProven));
  auto __res__ = ::llvm::dyn_cast<LogicEquivalenceCheckingOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

LogicEquivalenceCheckingOp LogicEquivalenceCheckingOp::create(::mlir::ImplicitLocOpBuilder &builder, /*optional*/::mlir::Type isProven) {
  return create(builder, builder.getLoc(), std::forward<decltype(isProven)>(isProven));
}

void LogicEquivalenceCheckingOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes) {
  (void)odsState.addRegion();
  (void)odsState.addRegion();
  odsState.addTypes(resultTypes);
}

LogicEquivalenceCheckingOp LogicEquivalenceCheckingOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes));
  auto __res__ = ::llvm::dyn_cast<LogicEquivalenceCheckingOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

LogicEquivalenceCheckingOp LogicEquivalenceCheckingOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes));
}

void LogicEquivalenceCheckingOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  for (unsigned i = 0; i != 2; ++i)
    (void)odsState.addRegion();
  odsState.addTypes(resultTypes);
}

LogicEquivalenceCheckingOp LogicEquivalenceCheckingOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<LogicEquivalenceCheckingOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

LogicEquivalenceCheckingOp LogicEquivalenceCheckingOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void LogicEquivalenceCheckingOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  for (unsigned i = 0; i != 2; ++i)
    (void)odsState.addRegion();
  odsState.addTypes(resultTypes);
}

LogicEquivalenceCheckingOp LogicEquivalenceCheckingOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<LogicEquivalenceCheckingOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

LogicEquivalenceCheckingOp LogicEquivalenceCheckingOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult LogicEquivalenceCheckingOp::verifyInvariantsImpl() {
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    if (valueGroup0.size() > 1) {
      return emitOpError("result group starting at #") << index
          << " requires 0 or 1 element, but found " << valueGroup0.size();
    }

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Verif2(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;

    for (auto &region : ::llvm::MutableArrayRef((*this)->getRegion(0)))
      if (::mlir::failed(__mlir_ods_local_region_constraint_Verif1(*this, region, "firstCircuit", index++)))
        return ::mlir::failure();

    for (auto &region : ::llvm::MutableArrayRef((*this)->getRegion(1)))
      if (::mlir::failed(__mlir_ods_local_region_constraint_Verif1(*this, region, "secondCircuit", index++)))
        return ::mlir::failure();
  }
  return ::mlir::success();
}

::llvm::LogicalResult LogicEquivalenceCheckingOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult LogicEquivalenceCheckingOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::llvm::SmallVector<::mlir::Type, 1> isProvenTypes;
  std::unique_ptr<::mlir::Region> firstCircuitRegion = std::make_unique<::mlir::Region>();
  std::unique_ptr<::mlir::Region> secondCircuitRegion = std::make_unique<::mlir::Region>();
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

  {
    ::mlir::Type optionalType;
    ::mlir::OptionalParseResult parseResult =
                                    parser.parseOptionalType(optionalType);
    if (parseResult.has_value()) {
      if (failed(*parseResult))
        return ::mlir::failure();
      isProvenTypes.push_back(optionalType);
    }
  }
  }
  if (parser.parseKeyword("first"))
    return ::mlir::failure();

  if (parser.parseRegion(*firstCircuitRegion))
    return ::mlir::failure();

  ensureTerminator(*firstCircuitRegion, parser.getBuilder(), result.location);
  if (parser.parseKeyword("second"))
    return ::mlir::failure();

  if (parser.parseRegion(*secondCircuitRegion))
    return ::mlir::failure();

  ensureTerminator(*secondCircuitRegion, parser.getBuilder(), result.location);
  result.addRegion(std::move(firstCircuitRegion));
  result.addRegion(std::move(secondCircuitRegion));
  result.addTypes(isProvenTypes);
  return ::mlir::success();
}

void LogicEquivalenceCheckingOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  if (getIsProven()) {
    _odsPrinter << ' ' << ":";
    _odsPrinter << ' ';
    _odsPrinter << (getIsProven() ? ::llvm::ArrayRef<::mlir::Type>(getIsProven().getType()) : ::llvm::ArrayRef<::mlir::Type>());
  }
  _odsPrinter << ' ' << "first";
  _odsPrinter << ' ';

  {
    bool printTerminator = true;
    if (auto *term = getFirstCircuit().empty() ? nullptr : getFirstCircuit().begin()->getTerminator()) {
      printTerminator = !term->getAttrDictionary().empty() ||
                        term->getNumOperands() != 0 ||
                        term->getNumResults() != 0;
    }
    _odsPrinter.printRegion(getFirstCircuit(), /*printEntryBlockArgs=*/true,
      /*printBlockTerminators=*/printTerminator);
  }
  _odsPrinter << ' ' << "second";
  _odsPrinter << ' ';

  {
    bool printTerminator = true;
    if (auto *term = getSecondCircuit().empty() ? nullptr : getSecondCircuit().begin()->getTerminator()) {
      printTerminator = !term->getAttrDictionary().empty() ||
                        term->getNumOperands() != 0 ||
                        term->getNumResults() != 0;
    }
    _odsPrinter.printRegion(getSecondCircuit(), /*printEntryBlockArgs=*/true,
      /*printBlockTerminators=*/printTerminator);
  }
}


} // namespace circt::verif
MLIR_DEFINE_EXPLICIT_TYPE_ID(circt::verif::LogicEquivalenceCheckingOp)

namespace circt::verif {


//===----------------------------------------------------------------------===//
// circt::verif::PrintOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

PrintOpGenericAdaptorBase::PrintOpGenericAdaptorBase(PrintOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}


} // namespace detail
PrintOpAdaptor::PrintOpAdaptor(PrintOp op) : PrintOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult PrintOpAdaptor::verify(::mlir::Location loc) {
  return ::mlir::success();
}

::llvm::LogicalResult PrintOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }
      return ::mlir::success();
}

::mlir::Attribute PrintOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code PrintOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine();
}

std::optional<mlir::Attribute> PrintOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
  return std::nullopt;
}

void PrintOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
}

void PrintOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
}

::llvm::LogicalResult PrintOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    return ::mlir::success();
}

void PrintOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value string) {
  odsState.addOperands(string);
}

PrintOp PrintOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value string) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(string)>(string));
  auto __res__ = ::llvm::dyn_cast<PrintOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

PrintOp PrintOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value string) {
  return create(builder, builder.getLoc(), std::forward<decltype(string)>(string));
}

void PrintOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value string) {
  odsState.addOperands(string);
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

PrintOp PrintOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value string) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(string)>(string));
  auto __res__ = ::llvm::dyn_cast<PrintOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

PrintOp PrintOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value string) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(string)>(string));
}

void PrintOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

PrintOp PrintOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<PrintOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

PrintOp PrintOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void PrintOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

PrintOp PrintOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<PrintOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

PrintOp PrintOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult PrintOp::verifyInvariantsImpl() {
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Verif4(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult PrintOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult PrintOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::OpAsmParser::UnresolvedOperand stringRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> stringOperands(&stringRawOperand, 1);  ::llvm::SMLoc stringOperandsLoc;
  (void)stringOperandsLoc;

  stringOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(stringRawOperand))
    return ::mlir::failure();
  {
    auto loc = parser.getCurrentLocation();(void)loc;
    if (parser.parseOptionalAttrDict(result.attributes))
      return ::mlir::failure();
    if (failed(verifyInherentAttrs(result.name, result.attributes, [&]() {
        return parser.emitError(loc) << "'" << result.name.getStringRef() << "' op ";
      })))
      return ::mlir::failure();
  }
  ::mlir::Type odsBuildableType0 = ::circt::hw::StringType::get(parser.getBuilder().getContext());
  if (parser.resolveOperands(stringOperands, odsBuildableType0, stringOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void PrintOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter << getString();
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
}


} // namespace circt::verif
MLIR_DEFINE_EXPLICIT_TYPE_ID(circt::verif::PrintOp)

namespace circt::verif {


//===----------------------------------------------------------------------===//
// circt::verif::RefinementCheckingOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

RefinementCheckingOpGenericAdaptorBase::RefinementCheckingOpGenericAdaptorBase(RefinementCheckingOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}


} // namespace detail
RefinementCheckingOpAdaptor::RefinementCheckingOpAdaptor(RefinementCheckingOp op) : RefinementCheckingOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult RefinementCheckingOpAdaptor::verify(::mlir::Location loc) {
  return ::mlir::success();
}

std::pair<unsigned, unsigned> RefinementCheckingOp::getODSResultIndexAndLength(unsigned index) {
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

::llvm::LogicalResult RefinementCheckingOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }
      return ::mlir::success();
}

::mlir::Attribute RefinementCheckingOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code RefinementCheckingOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine();
}

std::optional<mlir::Attribute> RefinementCheckingOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
  return std::nullopt;
}

void RefinementCheckingOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
}

void RefinementCheckingOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
}

::llvm::LogicalResult RefinementCheckingOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    return ::mlir::success();
}

void RefinementCheckingOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, bool hasResult) {
      build(odsBuilder, odsState, hasResult ? odsBuilder.getI1Type() : Type{} );
    
}

RefinementCheckingOp RefinementCheckingOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, bool hasResult) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(hasResult)>(hasResult));
  auto __res__ = ::llvm::dyn_cast<RefinementCheckingOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

RefinementCheckingOp RefinementCheckingOp::create(::mlir::ImplicitLocOpBuilder &builder, bool hasResult) {
  return create(builder, builder.getLoc(), std::forward<decltype(hasResult)>(hasResult));
}

void RefinementCheckingOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, /*optional*/::mlir::Type isProven) {
  (void)odsState.addRegion();
  (void)odsState.addRegion();
  if (isProven)
    odsState.addTypes(isProven);
}

RefinementCheckingOp RefinementCheckingOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, /*optional*/::mlir::Type isProven) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(isProven)>(isProven));
  auto __res__ = ::llvm::dyn_cast<RefinementCheckingOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

RefinementCheckingOp RefinementCheckingOp::create(::mlir::ImplicitLocOpBuilder &builder, /*optional*/::mlir::Type isProven) {
  return create(builder, builder.getLoc(), std::forward<decltype(isProven)>(isProven));
}

void RefinementCheckingOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes) {
  (void)odsState.addRegion();
  (void)odsState.addRegion();
  odsState.addTypes(resultTypes);
}

RefinementCheckingOp RefinementCheckingOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes));
  auto __res__ = ::llvm::dyn_cast<RefinementCheckingOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

RefinementCheckingOp RefinementCheckingOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes));
}

void RefinementCheckingOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  for (unsigned i = 0; i != 2; ++i)
    (void)odsState.addRegion();
  odsState.addTypes(resultTypes);
}

RefinementCheckingOp RefinementCheckingOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<RefinementCheckingOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

RefinementCheckingOp RefinementCheckingOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void RefinementCheckingOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  for (unsigned i = 0; i != 2; ++i)
    (void)odsState.addRegion();
  odsState.addTypes(resultTypes);
}

RefinementCheckingOp RefinementCheckingOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<RefinementCheckingOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

RefinementCheckingOp RefinementCheckingOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult RefinementCheckingOp::verifyInvariantsImpl() {
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    if (valueGroup0.size() > 1) {
      return emitOpError("result group starting at #") << index
          << " requires 0 or 1 element, but found " << valueGroup0.size();
    }

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Verif2(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;

    for (auto &region : ::llvm::MutableArrayRef((*this)->getRegion(0)))
      if (::mlir::failed(__mlir_ods_local_region_constraint_Verif1(*this, region, "firstCircuit", index++)))
        return ::mlir::failure();

    for (auto &region : ::llvm::MutableArrayRef((*this)->getRegion(1)))
      if (::mlir::failed(__mlir_ods_local_region_constraint_Verif1(*this, region, "secondCircuit", index++)))
        return ::mlir::failure();
  }
  return ::mlir::success();
}

::llvm::LogicalResult RefinementCheckingOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult RefinementCheckingOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::llvm::SmallVector<::mlir::Type, 1> isProvenTypes;
  std::unique_ptr<::mlir::Region> firstCircuitRegion = std::make_unique<::mlir::Region>();
  std::unique_ptr<::mlir::Region> secondCircuitRegion = std::make_unique<::mlir::Region>();
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

  {
    ::mlir::Type optionalType;
    ::mlir::OptionalParseResult parseResult =
                                    parser.parseOptionalType(optionalType);
    if (parseResult.has_value()) {
      if (failed(*parseResult))
        return ::mlir::failure();
      isProvenTypes.push_back(optionalType);
    }
  }
  }
  if (parser.parseKeyword("first"))
    return ::mlir::failure();

  if (parser.parseRegion(*firstCircuitRegion))
    return ::mlir::failure();

  ensureTerminator(*firstCircuitRegion, parser.getBuilder(), result.location);
  if (parser.parseKeyword("second"))
    return ::mlir::failure();

  if (parser.parseRegion(*secondCircuitRegion))
    return ::mlir::failure();

  ensureTerminator(*secondCircuitRegion, parser.getBuilder(), result.location);
  result.addRegion(std::move(firstCircuitRegion));
  result.addRegion(std::move(secondCircuitRegion));
  result.addTypes(isProvenTypes);
  return ::mlir::success();
}

void RefinementCheckingOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  if (getIsProven()) {
    _odsPrinter << ' ' << ":";
    _odsPrinter << ' ';
    _odsPrinter << (getIsProven() ? ::llvm::ArrayRef<::mlir::Type>(getIsProven().getType()) : ::llvm::ArrayRef<::mlir::Type>());
  }
  _odsPrinter << ' ' << "first";
  _odsPrinter << ' ';

  {
    bool printTerminator = true;
    if (auto *term = getFirstCircuit().empty() ? nullptr : getFirstCircuit().begin()->getTerminator()) {
      printTerminator = !term->getAttrDictionary().empty() ||
                        term->getNumOperands() != 0 ||
                        term->getNumResults() != 0;
    }
    _odsPrinter.printRegion(getFirstCircuit(), /*printEntryBlockArgs=*/true,
      /*printBlockTerminators=*/printTerminator);
  }
  _odsPrinter << ' ' << "second";
  _odsPrinter << ' ';

  {
    bool printTerminator = true;
    if (auto *term = getSecondCircuit().empty() ? nullptr : getSecondCircuit().begin()->getTerminator()) {
      printTerminator = !term->getAttrDictionary().empty() ||
                        term->getNumOperands() != 0 ||
                        term->getNumResults() != 0;
    }
    _odsPrinter.printRegion(getSecondCircuit(), /*printEntryBlockArgs=*/true,
      /*printBlockTerminators=*/printTerminator);
  }
}


} // namespace circt::verif
MLIR_DEFINE_EXPLICIT_TYPE_ID(circt::verif::RefinementCheckingOp)

namespace circt::verif {


//===----------------------------------------------------------------------===//
// circt::verif::RequireOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

RequireOpGenericAdaptorBase::RequireOpGenericAdaptorBase(RequireOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

std::pair<unsigned, unsigned> RequireOpGenericAdaptorBase::getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
  bool isVariadic[] = {false, true};
  int prevVariadicCount = 0;
  for (unsigned i = 0; i < index; ++i)
    if (isVariadic[i]) ++prevVariadicCount;

  // Calculate how many dynamic values a static variadic operand corresponds to.
  // This assumes all static variadic operands have the same dynamic value count.
  int variadicSize = (odsOperandsSize - 1) / 1;
  // `index` passed in as the parameter is the static index which counts each
  // operand (variadic or not) as size 1. So here for each previous static variadic
  // operand, we need to offset by (variadicSize - 1) to get where the dynamic
  // value pack for this static operand starts.
  int start = index + (variadicSize - 1) * prevVariadicCount;
  int size = isVariadic[index] ? variadicSize : 1;
  return {start, size};
}

::std::optional< ::llvm::StringRef > RequireOpGenericAdaptorBase::getLabel() {
  auto attr = getLabelAttr();
  return attr ? ::std::optional< ::llvm::StringRef >(attr.getValue()) : (::std::nullopt);
}


} // namespace detail
RequireOpAdaptor::RequireOpAdaptor(RequireOp op) : RequireOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult RequireOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_label = getProperties().label; (void)tblgen_label;

  if (tblgen_label && !((::llvm::isa<::mlir::StringAttr>(tblgen_label))))
    return emitError(loc, "'verif.require' op attribute 'label' failed to satisfy constraint: string attribute");
  return ::mlir::success();
}

std::pair<unsigned, unsigned> RequireOp::getODSOperandIndexAndLength(unsigned index) {
  bool isVariadic[] = {false, true};
  int prevVariadicCount = 0;
  for (unsigned i = 0; i < index; ++i)
    if (isVariadic[i]) ++prevVariadicCount;

  // Calculate how many dynamic values a static variadic operand corresponds to.
  // This assumes all static variadic operands have the same dynamic value count.
  int variadicSize = (getOperation()->getNumOperands() - 1) / 1;
  // `index` passed in as the parameter is the static index which counts each
  // operand (variadic or not) as size 1. So here for each previous static variadic
  // operand, we need to offset by (variadicSize - 1) to get where the dynamic
  // value pack for this static operand starts.
  int start = index + (variadicSize - 1) * prevVariadicCount;
  int size = isVariadic[index] ? variadicSize : 1;
  return {start, size};
}

::mlir::MutableOperandRange RequireOp::getEnableMutable() {
  auto range = getODSOperandIndexAndLength(1);
  auto mutableRange = ::mlir::MutableOperandRange(getOperation(), range.first, range.second);
  return mutableRange;
}

::llvm::LogicalResult RequireOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.label;
       auto attr = dict.get("label");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `label` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  return ::mlir::success();
}

::mlir::Attribute RequireOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.label;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("label",
                                       propStorage));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code RequireOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.label.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> RequireOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "label")
      return prop.label;
  return std::nullopt;
}

void RequireOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "label") {
       prop.label = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.label)>>(value);
       return;
    }
}

void RequireOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.label) attrs.append("label", prop.label);
}

::llvm::LogicalResult RequireOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getLabelAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Verif1(attr, "label", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult RequireOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readOptionalAttribute(prop.label)))
    return ::mlir::failure();
  return ::mlir::success();
}

void RequireOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;

  writer.writeOptionalAttribute(prop.label);
}

::std::optional< ::llvm::StringRef > RequireOp::getLabel() {
  auto attr = getLabelAttr();
  return attr ? ::std::optional< ::llvm::StringRef >(attr.getValue()) : (::std::nullopt);
}

void RequireOp::setLabel(::std::optional<::llvm::StringRef> attrValue) {
    auto &odsProp = getProperties().label;
    if (attrValue)
      odsProp = ::mlir::Builder((*this)->getContext()).getStringAttr(*attrValue);
    else
      odsProp = nullptr;
}

void RequireOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value property, /*optional*/::mlir::Value enable, /*optional*/::mlir::StringAttr label) {
  odsState.addOperands(property);
  if (enable)
    odsState.addOperands(enable);
  if (label) {
    odsState.getOrAddProperties<Properties>().label = label;
  }
}

RequireOp RequireOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value property, /*optional*/::mlir::Value enable, /*optional*/::mlir::StringAttr label) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(property)>(property), std::forward<decltype(enable)>(enable), std::forward<decltype(label)>(label));
  auto __res__ = ::llvm::dyn_cast<RequireOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

RequireOp RequireOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value property, /*optional*/::mlir::Value enable, /*optional*/::mlir::StringAttr label) {
  return create(builder, builder.getLoc(), std::forward<decltype(property)>(property), std::forward<decltype(enable)>(enable), std::forward<decltype(label)>(label));
}

void RequireOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value property, /*optional*/::mlir::Value enable, /*optional*/::mlir::StringAttr label) {
  odsState.addOperands(property);
  if (enable)
    odsState.addOperands(enable);
  if (label) {
    odsState.getOrAddProperties<Properties>().label = label;
  }
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

RequireOp RequireOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value property, /*optional*/::mlir::Value enable, /*optional*/::mlir::StringAttr label) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(property)>(property), std::forward<decltype(enable)>(enable), std::forward<decltype(label)>(label));
  auto __res__ = ::llvm::dyn_cast<RequireOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

RequireOp RequireOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value property, /*optional*/::mlir::Value enable, /*optional*/::mlir::StringAttr label) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(property)>(property), std::forward<decltype(enable)>(enable), std::forward<decltype(label)>(label));
}

void RequireOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() >= 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<RequireOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

RequireOp RequireOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<RequireOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

RequireOp RequireOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void RequireOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() >= 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

RequireOp RequireOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<RequireOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

RequireOp RequireOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult RequireOp::verifyInvariantsImpl() {
  auto tblgen_label = getProperties().label; (void)tblgen_label;

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Verif1(*this, tblgen_label, "label")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Verif1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSOperands(1);

    if (valueGroup1.size() > 1) {
      return emitOpError("operand group starting at #") << index
          << " requires 0 or 1 element, but found " << valueGroup1.size();
    }

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Verif2(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult RequireOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult RequireOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::OpAsmParser::UnresolvedOperand propertyRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> propertyOperands(&propertyRawOperand, 1);  ::llvm::SMLoc propertyOperandsLoc;
  (void)propertyOperandsLoc;
  ::llvm::SmallVector<::mlir::OpAsmParser::UnresolvedOperand, 4> enableOperands;
  ::llvm::SMLoc enableOperandsLoc;
  (void)enableOperandsLoc;
  ::mlir::StringAttr labelAttr;
  ::mlir::Type propertyRawType{};
  ::llvm::ArrayRef<::mlir::Type> propertyTypes(&propertyRawType, 1);

  propertyOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(propertyRawOperand))
    return ::mlir::failure();
  if (::mlir::succeeded(parser.parseOptionalKeyword("if"))) {

  {
    enableOperandsLoc = parser.getCurrentLocation();
    ::mlir::OpAsmParser::UnresolvedOperand operand;
    ::mlir::OptionalParseResult parseResult =
                                    parser.parseOptionalOperand(operand);
    if (parseResult.has_value()) {
      if (failed(*parseResult))
        return ::mlir::failure();
      enableOperands.push_back(operand);
    }
  }
  }
  if (::mlir::succeeded(parser.parseOptionalKeyword("label"))) {

  if (parser.parseCustomAttributeWithFallback(labelAttr, parser.getBuilder().getType<::mlir::NoneType>())) {
    return ::mlir::failure();
  }
  if (labelAttr) result.getOrAddProperties<RequireOp::Properties>().label = labelAttr;
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
  if (parser.parseColon())
    return ::mlir::failure();

  {
    ::mlir::Type type;
    if (parser.parseCustomTypeWithFallback(type))
      return ::mlir::failure();
    propertyRawType = type;
  }
  ::mlir::Type odsBuildableType0 = parser.getBuilder().getIntegerType(1);
  if (parser.resolveOperands(propertyOperands, propertyTypes, propertyOperandsLoc, result.operands))
    return ::mlir::failure();
  if (!enableOperands.empty()) {
  if (parser.resolveOperands(enableOperands, odsBuildableType0, enableOperandsLoc, result.operands))
    return ::mlir::failure();
  }
  return ::mlir::success();
}

void RequireOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter << getProperty();
  if (getEnable()) {
    _odsPrinter << ' ' << "if";
    _odsPrinter << ' ';
    if (::mlir::Value value = getEnable())
      _odsPrinter << value;
  }
  if (getLabelAttr()) {
    _odsPrinter << ' ' << "label";
    _odsPrinter << ' ';
    _odsPrinter.printAttributeWithoutType(getLabelAttr());
  }
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("label");
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
  {
    auto type = getProperty().getType();
    if (auto validType = ::llvm::dyn_cast<::mlir::Type>(type))
      _odsPrinter.printStrippedAttrOrType(validType);
   else
     _odsPrinter << type;
  }
}


} // namespace circt::verif
MLIR_DEFINE_EXPLICIT_TYPE_ID(circt::verif::RequireOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(circt::verif::detail::RequireOpGenericAdaptorBase::Properties)

namespace circt::verif {


//===----------------------------------------------------------------------===//
// circt::verif::SimulationOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

SimulationOpGenericAdaptorBase::SimulationOpGenericAdaptorBase(SimulationOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::llvm::StringRef SimulationOpGenericAdaptorBase::getSymName() {
  auto attr = getSymNameAttr();
  return attr.getValue();
}

::mlir::DictionaryAttr SimulationOpGenericAdaptorBase::getParameters() {
  auto attr = getParametersAttr();
  return attr;
}


} // namespace detail
SimulationOpAdaptor::SimulationOpAdaptor(SimulationOp op) : SimulationOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult SimulationOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_parameters = getProperties().parameters; (void)tblgen_parameters;
  if (!tblgen_parameters) return emitError(loc, "'verif.simulation' op requires attribute 'parameters'");
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;
  if (!tblgen_sym_name) return emitError(loc, "'verif.simulation' op requires attribute 'sym_name'");

  if (tblgen_sym_name && !((::llvm::isa<::mlir::StringAttr>(tblgen_sym_name))))
    return emitError(loc, "'verif.simulation' op attribute 'sym_name' failed to satisfy constraint: string attribute");

  if (tblgen_parameters && !((::llvm::isa<::mlir::DictionaryAttr>(tblgen_parameters))))
    return emitError(loc, "'verif.simulation' op attribute 'parameters' failed to satisfy constraint: dictionary of named attribute values");
  return ::mlir::success();
}

::llvm::LogicalResult SimulationOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.parameters;
       auto attr = dict.get("parameters");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `parameters` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.sym_name;
       auto attr = dict.get("sym_name");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `sym_name` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  return ::mlir::success();
}

::mlir::Attribute SimulationOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.parameters;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("parameters",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.sym_name;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("sym_name",
                                       propStorage));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code SimulationOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.parameters.getAsOpaquePointer()), 
    llvm::hash_value(prop.sym_name.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> SimulationOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "parameters")
      return prop.parameters;

    if (name == "sym_name")
      return prop.sym_name;
  return std::nullopt;
}

void SimulationOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "parameters") {
       prop.parameters = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.parameters)>>(value);
       return;
    }

    if (name == "sym_name") {
       prop.sym_name = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.sym_name)>>(value);
       return;
    }
}

void SimulationOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.parameters) attrs.append("parameters", prop.parameters);

    if (prop.sym_name) attrs.append("sym_name", prop.sym_name);
}

::llvm::LogicalResult SimulationOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getParametersAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Verif5(attr, "parameters", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getSymNameAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Verif1(attr, "sym_name", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult SimulationOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.parameters)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readAttribute(prop.sym_name)))
    return ::mlir::failure();
  return ::mlir::success();
}

void SimulationOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.parameters);
  writer.writeAttribute(prop.sym_name);
}

::llvm::StringRef SimulationOp::getSymName() {
  auto attr = getSymNameAttr();
  return attr.getValue();
}

::mlir::DictionaryAttr SimulationOp::getParameters() {
  auto attr = getParametersAttr();
  return attr;
}

void SimulationOp::setSymName(::llvm::StringRef attrValue) {
  getProperties().sym_name = ::mlir::Builder((*this)->getContext()).getStringAttr(attrValue);
}

void SimulationOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::StringAttr sym_name, ::mlir::DictionaryAttr parameters) {
  odsState.getOrAddProperties<Properties>().sym_name = sym_name;
  odsState.getOrAddProperties<Properties>().parameters = parameters;
  (void)odsState.addRegion();
}

SimulationOp SimulationOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::StringAttr sym_name, ::mlir::DictionaryAttr parameters) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(parameters)>(parameters));
  auto __res__ = ::llvm::dyn_cast<SimulationOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SimulationOp SimulationOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::StringAttr sym_name, ::mlir::DictionaryAttr parameters) {
  return create(builder, builder.getLoc(), std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(parameters)>(parameters));
}

void SimulationOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name, ::mlir::DictionaryAttr parameters) {
  odsState.getOrAddProperties<Properties>().sym_name = sym_name;
  odsState.getOrAddProperties<Properties>().parameters = parameters;
  (void)odsState.addRegion();
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

SimulationOp SimulationOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name, ::mlir::DictionaryAttr parameters) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(parameters)>(parameters));
  auto __res__ = ::llvm::dyn_cast<SimulationOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SimulationOp SimulationOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name, ::mlir::DictionaryAttr parameters) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(parameters)>(parameters));
}

void SimulationOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::llvm::StringRef sym_name, ::mlir::DictionaryAttr parameters) {
  odsState.getOrAddProperties<Properties>().sym_name = odsBuilder.getStringAttr(sym_name);
  odsState.getOrAddProperties<Properties>().parameters = parameters;
  (void)odsState.addRegion();
}

SimulationOp SimulationOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::llvm::StringRef sym_name, ::mlir::DictionaryAttr parameters) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(parameters)>(parameters));
  auto __res__ = ::llvm::dyn_cast<SimulationOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SimulationOp SimulationOp::create(::mlir::ImplicitLocOpBuilder &builder, ::llvm::StringRef sym_name, ::mlir::DictionaryAttr parameters) {
  return create(builder, builder.getLoc(), std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(parameters)>(parameters));
}

void SimulationOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name, ::mlir::DictionaryAttr parameters) {
  odsState.getOrAddProperties<Properties>().sym_name = odsBuilder.getStringAttr(sym_name);
  odsState.getOrAddProperties<Properties>().parameters = parameters;
  (void)odsState.addRegion();
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

SimulationOp SimulationOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name, ::mlir::DictionaryAttr parameters) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(parameters)>(parameters));
  auto __res__ = ::llvm::dyn_cast<SimulationOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SimulationOp SimulationOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name, ::mlir::DictionaryAttr parameters) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(parameters)>(parameters));
}

void SimulationOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  for (unsigned i = 0; i != 1; ++i)
    (void)odsState.addRegion();
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<SimulationOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

SimulationOp SimulationOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<SimulationOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SimulationOp SimulationOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void SimulationOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  for (unsigned i = 0; i != 1; ++i)
    (void)odsState.addRegion();
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

SimulationOp SimulationOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<SimulationOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SimulationOp SimulationOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult SimulationOp::verifyInvariantsImpl() {
  auto tblgen_parameters = getProperties().parameters; (void)tblgen_parameters;
  if (!tblgen_parameters) return emitOpError("requires attribute 'parameters'");
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;
  if (!tblgen_sym_name) return emitOpError("requires attribute 'sym_name'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Verif1(*this, tblgen_sym_name, "sym_name")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Verif5(*this, tblgen_parameters, "parameters")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;

    for (auto &region : ::llvm::MutableArrayRef((*this)->getRegion(0)))
      if (::mlir::failed(__mlir_ods_local_region_constraint_Verif1(*this, region, "region", index++)))
        return ::mlir::failure();
  }
  return ::mlir::success();
}

::llvm::LogicalResult SimulationOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult SimulationOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::StringAttr sym_nameAttr;
  ::mlir::DictionaryAttr parametersAttr;
  std::unique_ptr<::mlir::Region> regionRegion = std::make_unique<::mlir::Region>();

  if (parser.parseSymbolName(sym_nameAttr))
    return ::mlir::failure();
  if (sym_nameAttr) result.getOrAddProperties<SimulationOp::Properties>().sym_name = sym_nameAttr;

  if (parser.parseCustomAttributeWithFallback(parametersAttr, parser.getBuilder().getType<::mlir::NoneType>())) {
    return ::mlir::failure();
  }
  if (parametersAttr) result.getOrAddProperties<SimulationOp::Properties>().parameters = parametersAttr;
  {
    auto loc = parser.getCurrentLocation();(void)loc;
    if (parser.parseOptionalAttrDictWithKeyword(result.attributes))
      return ::mlir::failure();
    if (failed(verifyInherentAttrs(result.name, result.attributes, [&]() {
        return parser.emitError(loc) << "'" << result.name.getStringRef() << "' op ";
      })))
      return ::mlir::failure();
  }

  if (parser.parseRegion(*regionRegion))
    return ::mlir::failure();

  ensureTerminator(*regionRegion, parser.getBuilder(), result.location);
  result.addRegion(std::move(regionRegion));
  return ::mlir::success();
}

void SimulationOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter.printSymbolName(getSymNameAttr().getValue());
  _odsPrinter << ' ';
  _odsPrinter.printAttributeWithoutType(getParametersAttr());
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("sym_name");
  elidedAttrs.push_back("parameters");
  _odsPrinter.printOptionalAttrDictWithKeyword((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ';

  {
    bool printTerminator = true;
    if (auto *term = getRegion().empty() ? nullptr : getRegion().begin()->getTerminator()) {
      printTerminator = !term->getAttrDictionary().empty() ||
                        term->getNumOperands() != 0 ||
                        term->getNumResults() != 0;
    }
    _odsPrinter.printRegion(getRegion(), /*printEntryBlockArgs=*/true,
      /*printBlockTerminators=*/printTerminator);
  }
}


} // namespace circt::verif
MLIR_DEFINE_EXPLICIT_TYPE_ID(circt::verif::SimulationOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(circt::verif::detail::SimulationOpGenericAdaptorBase::Properties)

namespace circt::verif {


//===----------------------------------------------------------------------===//
// circt::verif::SymbolicValueOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

SymbolicValueOpGenericAdaptorBase::SymbolicValueOpGenericAdaptorBase(SymbolicValueOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::std::optional< ::llvm::StringRef > SymbolicValueOpGenericAdaptorBase::getName() {
  auto attr = getNameAttr();
  return attr ? ::std::optional< ::llvm::StringRef >(attr.getValue()) : (::std::nullopt);
}


} // namespace detail
SymbolicValueOpAdaptor::SymbolicValueOpAdaptor(SymbolicValueOp op) : SymbolicValueOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult SymbolicValueOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_name = getProperties().name; (void)tblgen_name;

  if (tblgen_name && !((::llvm::isa<::mlir::StringAttr>(tblgen_name))))
    return emitError(loc, "'verif.symbolic_value' op attribute 'name' failed to satisfy constraint: string attribute");
  return ::mlir::success();
}

::llvm::LogicalResult SymbolicValueOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
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
  return ::mlir::success();
}

::mlir::Attribute SymbolicValueOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.name;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("name",
                                       propStorage));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code SymbolicValueOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.name.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> SymbolicValueOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "name")
      return prop.name;
  return std::nullopt;
}

void SymbolicValueOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "name") {
       prop.name = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.name)>>(value);
       return;
    }
}

void SymbolicValueOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.name) attrs.append("name", prop.name);
}

::llvm::LogicalResult SymbolicValueOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getNameAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Verif1(attr, "name", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult SymbolicValueOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readOptionalAttribute(prop.name)))
    return ::mlir::failure();
  return ::mlir::success();
}

void SymbolicValueOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;

  writer.writeOptionalAttribute(prop.name);
}

::std::optional< ::llvm::StringRef > SymbolicValueOp::getName() {
  auto attr = getNameAttr();
  return attr ? ::std::optional< ::llvm::StringRef >(attr.getValue()) : (::std::nullopt);
}

void SymbolicValueOp::setName(::std::optional<::llvm::StringRef> attrValue) {
    auto &odsProp = getProperties().name;
    if (attrValue)
      odsProp = ::mlir::Builder((*this)->getContext()).getStringAttr(*attrValue);
    else
      odsProp = nullptr;
}

void SymbolicValueOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, /*optional*/::mlir::StringAttr name) {
  if (name) {
    odsState.getOrAddProperties<Properties>().name = name;
  }
  odsState.addTypes(result);
}

SymbolicValueOp SymbolicValueOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, /*optional*/::mlir::StringAttr name) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(result)>(result), std::forward<decltype(name)>(name));
  auto __res__ = ::llvm::dyn_cast<SymbolicValueOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SymbolicValueOp SymbolicValueOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, /*optional*/::mlir::StringAttr name) {
  return create(builder, builder.getLoc(), std::forward<decltype(result)>(result), std::forward<decltype(name)>(name));
}

void SymbolicValueOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, /*optional*/::mlir::StringAttr name) {
  if (name) {
    odsState.getOrAddProperties<Properties>().name = name;
  }
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

SymbolicValueOp SymbolicValueOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, /*optional*/::mlir::StringAttr name) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(name)>(name));
  auto __res__ = ::llvm::dyn_cast<SymbolicValueOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SymbolicValueOp SymbolicValueOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, /*optional*/::mlir::StringAttr name) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(name)>(name));
}

void SymbolicValueOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<SymbolicValueOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

SymbolicValueOp SymbolicValueOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<SymbolicValueOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SymbolicValueOp SymbolicValueOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void SymbolicValueOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

SymbolicValueOp SymbolicValueOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<SymbolicValueOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SymbolicValueOp SymbolicValueOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult SymbolicValueOp::verifyInvariantsImpl() {
  auto tblgen_name = getProperties().name; (void)tblgen_name;

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Verif1(*this, tblgen_name, "name")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Verif5(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult SymbolicValueOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult SymbolicValueOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::StringAttr nameAttr;
  ::mlir::Type resultRawType{};
  ::llvm::ArrayRef<::mlir::Type> resultTypes(&resultRawType, 1);
  {
    auto odsResult = parseImplicitSSAName(parser, nameAttr);
    if (odsResult) return ::mlir::failure();
    if (nameAttr)
      result.getOrAddProperties<SymbolicValueOp::Properties>().name = nameAttr;
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
  if (parser.parseColon())
    return ::mlir::failure();

  {
    ::mlir::Type type;
    if (parser.parseCustomTypeWithFallback(type))
      return ::mlir::failure();
    resultRawType = type;
  }
  result.addTypes(resultTypes);
  return ::mlir::success();
}

void SymbolicValueOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  printImplicitSSAName(_odsPrinter, *this, getNameAttr());
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("name");
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
  {
    auto type = getResult().getType();
    if (auto validType = ::llvm::dyn_cast<::mlir::Type>(type))
      _odsPrinter.printStrippedAttrOrType(validType);
   else
     _odsPrinter << type;
  }
}

void SymbolicValueOp::getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects) {
  {
    auto valueRange = getODSResultIndexAndLength(0);
    for (unsigned idx = valueRange.first; idx < valueRange.first + valueRange.second; idx++) {
      effects.emplace_back(::mlir::MemoryEffects::Allocate::get(), getOperation()->getOpResult(idx), 0, false, ::mlir::SideEffects::DefaultResource::get());
    }
  }
}


} // namespace circt::verif
MLIR_DEFINE_EXPLICIT_TYPE_ID(circt::verif::SymbolicValueOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(circt::verif::detail::SymbolicValueOpGenericAdaptorBase::Properties)

namespace circt::verif {


//===----------------------------------------------------------------------===//
// circt::verif::YieldOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

YieldOpGenericAdaptorBase::YieldOpGenericAdaptorBase(YieldOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

std::pair<unsigned, unsigned> YieldOpGenericAdaptorBase::getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
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
YieldOpAdaptor::YieldOpAdaptor(YieldOp op) : YieldOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult YieldOpAdaptor::verify(::mlir::Location loc) {
  return ::mlir::success();
}

std::pair<unsigned, unsigned> YieldOp::getODSOperandIndexAndLength(unsigned index) {
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

::mlir::MutableOperandRange YieldOp::getInputsMutable() {
  auto range = getODSOperandIndexAndLength(0);
  auto mutableRange = ::mlir::MutableOperandRange(getOperation(), range.first, range.second);
  return mutableRange;
}

::llvm::LogicalResult YieldOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }
      return ::mlir::success();
}

::mlir::Attribute YieldOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code YieldOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine();
}

std::optional<mlir::Attribute> YieldOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
  return std::nullopt;
}

void YieldOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
}

void YieldOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
}

::llvm::LogicalResult YieldOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    return ::mlir::success();
}

void YieldOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState) {
      build(odsBuilder, odsState, mlir::ValueRange());
    
}

YieldOp YieldOp::create(::mlir::OpBuilder &builder, ::mlir::Location location) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__);
  auto __res__ = ::llvm::dyn_cast<YieldOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

YieldOp YieldOp::create(::mlir::ImplicitLocOpBuilder &builder) {
  return create(builder, builder.getLoc());
}

void YieldOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange inputs) {
  odsState.addOperands(inputs);
}

YieldOp YieldOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange inputs) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(inputs)>(inputs));
  auto __res__ = ::llvm::dyn_cast<YieldOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

YieldOp YieldOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange inputs) {
  return create(builder, builder.getLoc(), std::forward<decltype(inputs)>(inputs));
}

void YieldOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

YieldOp YieldOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<YieldOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

YieldOp YieldOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void YieldOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

YieldOp YieldOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<YieldOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

YieldOp YieldOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult YieldOp::verifyInvariantsImpl() {
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Verif3(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult YieldOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult YieldOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::llvm::SmallVector<::mlir::OpAsmParser::UnresolvedOperand, 4> inputsOperands;
  ::llvm::SMLoc inputsOperandsLoc;
  (void)inputsOperandsLoc;
  ::llvm::SmallVector<::mlir::Type, 1> inputsTypes;

  inputsOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperandList(inputsOperands))
    return ::mlir::failure();
  if (!inputsOperands.empty()) {
  if (parser.parseColon())
    return ::mlir::failure();

  if (parser.parseTypeList(inputsTypes))
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
  if (parser.resolveOperands(inputsOperands, inputsTypes, inputsOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void YieldOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  if (!getInputs().empty()) {
    _odsPrinter << ' ';
    _odsPrinter << getInputs();
    _odsPrinter << ' ' << ":";
    _odsPrinter << ' ';
    _odsPrinter << getInputs().getTypes();
  }
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
}


} // namespace circt::verif
MLIR_DEFINE_EXPLICIT_TYPE_ID(circt::verif::YieldOp)


#endif // GET_OP_CLASSES

