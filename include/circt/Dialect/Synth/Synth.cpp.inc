/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Op Definitions                                                             *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: Synth.td                                                             *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

#ifdef GET_OP_LIST
#undef GET_OP_LIST

::circt::synth::aig::AndInverterOp,
::circt::synth::ChoiceOp,
::circt::synth::DotOp,
::circt::synth::GambleOp,
::circt::synth::MajorityOp,
::circt::synth::MuxInverterOp,
::circt::synth::OneHotOp,
::circt::synth::XorInverterOp
#endif // GET_OP_LIST

#ifdef GET_OP_CLASSES
#undef GET_OP_CLASSES


//===----------------------------------------------------------------------===//
// Local Utility Method Definitions
//===----------------------------------------------------------------------===//


static ::llvm::LogicalResult __mlir_ods_local_type_constraint_Synth1(
    ::mlir::Operation *op, ::mlir::Type type, ::llvm::StringRef valueKind,
    unsigned valueIndex) {
  if (!(!((::llvm::isa<::mlir::TokenType>(type))))) {
    return op->emitOpError(valueKind) << " #" << valueIndex
        << " must be variadic of any non-token type, but got " << type;
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_type_constraint_Synth2(
    ::mlir::Operation *op, ::mlir::Type type, ::llvm::StringRef valueKind,
    unsigned valueIndex) {
  if (!(!((::llvm::isa<::mlir::TokenType>(type))))) {
    return op->emitOpError(valueKind) << " #" << valueIndex
        << " must be any non-token type, but got " << type;
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_Synth1(
    ::mlir::Attribute attr, ::llvm::StringRef attrName, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  if (attr && !((::llvm::isa<::mlir::DenseBoolArrayAttr>(attr))))
    return emitError() << "attribute '" << attrName
        << "' failed to satisfy constraint: i1 dense array attribute";
  return ::mlir::success();
}
static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_Synth1(
    ::mlir::Operation *op, ::mlir::Attribute attr, ::llvm::StringRef attrName) {
  return __mlir_ods_local_attr_constraint_Synth1(attr, attrName, [op]() {
    return op->emitOpError();
  });
}
namespace circt::synth::aig {


//===----------------------------------------------------------------------===//
// ::circt::synth::aig::AndInverterOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

AndInverterOpGenericAdaptorBase::AndInverterOpGenericAdaptorBase(AndInverterOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

std::pair<unsigned, unsigned> AndInverterOpGenericAdaptorBase::getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
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

::llvm::ArrayRef<bool> AndInverterOpGenericAdaptorBase::getInverted() {
  auto attr = getInvertedAttr();
  return attr;
}


} // namespace detail
AndInverterOpAdaptor::AndInverterOpAdaptor(AndInverterOp op) : AndInverterOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult AndInverterOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_inverted = getProperties().inverted; (void)tblgen_inverted;
  if (!tblgen_inverted) return emitError(loc, "'synth.aig.and_inv' op requires attribute 'inverted'");

  if (tblgen_inverted && !((::llvm::isa<::mlir::DenseBoolArrayAttr>(tblgen_inverted))))
    return emitError(loc, "'synth.aig.and_inv' op attribute 'inverted' failed to satisfy constraint: i1 dense array attribute");
  return ::mlir::success();
}

std::pair<unsigned, unsigned> AndInverterOp::getODSOperandIndexAndLength(unsigned index) {
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

::mlir::MutableOperandRange AndInverterOp::getInputsMutable() {
  auto range = getODSOperandIndexAndLength(0);
  auto mutableRange = ::mlir::MutableOperandRange(getOperation(), range.first, range.second);
  return mutableRange;
}

::llvm::LogicalResult AndInverterOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.inverted;
       auto attr = dict.get("inverted");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `inverted` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  return ::mlir::success();
}

::mlir::Attribute AndInverterOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.inverted;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("inverted",
                                       propStorage));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code AndInverterOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.inverted.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> AndInverterOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "inverted")
      return prop.inverted;
  return std::nullopt;
}

void AndInverterOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "inverted") {
       prop.inverted = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.inverted)>>(value);
       return;
    }
}

void AndInverterOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.inverted) attrs.append("inverted", prop.inverted);
}

::llvm::LogicalResult AndInverterOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getInvertedAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Synth1(attr, "inverted", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult AndInverterOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.inverted)))
    return ::mlir::failure();
  return ::mlir::success();
}

void AndInverterOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.inverted);
}

::llvm::ArrayRef<bool> AndInverterOp::getInverted() {
  auto attr = getInvertedAttr();
  return attr;
}

void AndInverterOp::setInverted(::llvm::ArrayRef<bool> attrValue) {
  getProperties().inverted = ::mlir::Builder((*this)->getContext()).getDenseBoolArrayAttr(attrValue);
}

void AndInverterOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value input, bool invert) {
      SmallVector<bool> inverted {invert};
      return build(odsBuilder, odsState, {input}, inverted);
    
}

AndInverterOp AndInverterOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, Value input, bool invert) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(input)>(input), std::forward<decltype(invert)>(invert));
  auto __res__ = ::llvm::dyn_cast<AndInverterOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

AndInverterOp AndInverterOp::create(::mlir::ImplicitLocOpBuilder &builder, Value input, bool invert) {
  return create(builder, builder.getLoc(), std::forward<decltype(input)>(input), std::forward<decltype(invert)>(invert));
}

void AndInverterOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value lhs, Value rhs, bool invertLhs, bool invertRhs) {
      SmallVector<bool> inverted {invertLhs, invertRhs};
      return build(odsBuilder, odsState, {lhs, rhs}, inverted);
    
}

AndInverterOp AndInverterOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, Value lhs, Value rhs, bool invertLhs, bool invertRhs) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(lhs)>(lhs), std::forward<decltype(rhs)>(rhs), std::forward<decltype(invertLhs)>(invertLhs), std::forward<decltype(invertRhs)>(invertRhs));
  auto __res__ = ::llvm::dyn_cast<AndInverterOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

AndInverterOp AndInverterOp::create(::mlir::ImplicitLocOpBuilder &builder, Value lhs, Value rhs, bool invertLhs, bool invertRhs) {
  return create(builder, builder.getLoc(), std::forward<decltype(lhs)>(lhs), std::forward<decltype(rhs)>(rhs), std::forward<decltype(invertLhs)>(invertLhs), std::forward<decltype(invertRhs)>(invertRhs));
}

void AndInverterOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::ValueRange inputs, ::mlir::DenseBoolArrayAttr inverted) {
  odsState.addOperands(inputs);
  odsState.getOrAddProperties<Properties>().inverted = inverted;
  odsState.addTypes(result);
}

AndInverterOp AndInverterOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::ValueRange inputs, ::mlir::DenseBoolArrayAttr inverted) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(result)>(result), std::forward<decltype(inputs)>(inputs), std::forward<decltype(inverted)>(inverted));
  auto __res__ = ::llvm::dyn_cast<AndInverterOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

AndInverterOp AndInverterOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::ValueRange inputs, ::mlir::DenseBoolArrayAttr inverted) {
  return create(builder, builder.getLoc(), std::forward<decltype(result)>(result), std::forward<decltype(inputs)>(inputs), std::forward<decltype(inverted)>(inverted));
}

void AndInverterOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange inputs, ::mlir::DenseBoolArrayAttr inverted) {
  odsState.addOperands(inputs);
  odsState.getOrAddProperties<Properties>().inverted = inverted;
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

AndInverterOp AndInverterOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange inputs, ::mlir::DenseBoolArrayAttr inverted) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(inputs)>(inputs), std::forward<decltype(inverted)>(inverted));
  auto __res__ = ::llvm::dyn_cast<AndInverterOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

AndInverterOp AndInverterOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange inputs, ::mlir::DenseBoolArrayAttr inverted) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(inputs)>(inputs), std::forward<decltype(inverted)>(inverted));
}

void AndInverterOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::ValueRange inputs, ::llvm::ArrayRef<bool> inverted) {
  odsState.addOperands(inputs);
  odsState.getOrAddProperties<Properties>().inverted = odsBuilder.getDenseBoolArrayAttr(inverted);
  odsState.addTypes(result);
}

AndInverterOp AndInverterOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::ValueRange inputs, ::llvm::ArrayRef<bool> inverted) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(result)>(result), std::forward<decltype(inputs)>(inputs), std::forward<decltype(inverted)>(inverted));
  auto __res__ = ::llvm::dyn_cast<AndInverterOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

AndInverterOp AndInverterOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::ValueRange inputs, ::llvm::ArrayRef<bool> inverted) {
  return create(builder, builder.getLoc(), std::forward<decltype(result)>(result), std::forward<decltype(inputs)>(inputs), std::forward<decltype(inverted)>(inverted));
}

void AndInverterOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange inputs, ::llvm::ArrayRef<bool> inverted) {
  odsState.addOperands(inputs);
  odsState.getOrAddProperties<Properties>().inverted = odsBuilder.getDenseBoolArrayAttr(inverted);
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

AndInverterOp AndInverterOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange inputs, ::llvm::ArrayRef<bool> inverted) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(inputs)>(inputs), std::forward<decltype(inverted)>(inverted));
  auto __res__ = ::llvm::dyn_cast<AndInverterOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

AndInverterOp AndInverterOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange inputs, ::llvm::ArrayRef<bool> inverted) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(inputs)>(inputs), std::forward<decltype(inverted)>(inverted));
}

void AndInverterOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<AndInverterOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

AndInverterOp AndInverterOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<AndInverterOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

AndInverterOp AndInverterOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void AndInverterOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

AndInverterOp AndInverterOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<AndInverterOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

AndInverterOp AndInverterOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

void AndInverterOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange inputs, ::mlir::DenseBoolArrayAttr inverted) {
  odsState.addOperands(inputs);
  odsState.getOrAddProperties<Properties>().inverted = inverted;
  odsState.addTypes({inputs.front().getType()});

}

AndInverterOp AndInverterOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange inputs, ::mlir::DenseBoolArrayAttr inverted) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(inputs)>(inputs), std::forward<decltype(inverted)>(inverted));
  auto __res__ = ::llvm::dyn_cast<AndInverterOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

AndInverterOp AndInverterOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange inputs, ::mlir::DenseBoolArrayAttr inverted) {
  return create(builder, builder.getLoc(), std::forward<decltype(inputs)>(inputs), std::forward<decltype(inverted)>(inverted));
}

void AndInverterOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange inputs, ::llvm::ArrayRef<bool> inverted) {
  odsState.addOperands(inputs);
  odsState.getOrAddProperties<Properties>().inverted = odsBuilder.getDenseBoolArrayAttr(inverted);
  odsState.addTypes({inputs.front().getType()});

}

AndInverterOp AndInverterOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange inputs, ::llvm::ArrayRef<bool> inverted) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(inputs)>(inputs), std::forward<decltype(inverted)>(inverted));
  auto __res__ = ::llvm::dyn_cast<AndInverterOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

AndInverterOp AndInverterOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange inputs, ::llvm::ArrayRef<bool> inverted) {
  return create(builder, builder.getLoc(), std::forward<decltype(inputs)>(inputs), std::forward<decltype(inverted)>(inverted));
}

void AndInverterOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  odsState.addTypes({operands[0].getType()});

}

AndInverterOp AndInverterOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<AndInverterOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

AndInverterOp AndInverterOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void AndInverterOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  odsState.addTypes({operands[0].getType()});

}

AndInverterOp AndInverterOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<AndInverterOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

AndInverterOp AndInverterOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult AndInverterOp::verifyInvariantsImpl() {
  auto tblgen_inverted = getProperties().inverted; (void)tblgen_inverted;
  if (!tblgen_inverted) return emitOpError("requires attribute 'inverted'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Synth1(*this, tblgen_inverted, "inverted")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Synth1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Synth2(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult AndInverterOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

void AndInverterOp::getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context) {
  results.add(canonicalize);
}

::mlir::ParseResult AndInverterOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::llvm::SmallVector<::mlir::OpAsmParser::UnresolvedOperand, 4> inputsOperands;
  ::llvm::SMLoc inputsOperandsLoc;
  (void)inputsOperandsLoc;
  ::mlir::Type resultRawType{};
  ::llvm::ArrayRef<::mlir::Type> resultTypes(&resultRawType, 1);
  ::mlir::DenseBoolArrayAttr invertedAttr;
  {
    inputsOperandsLoc = parser.getCurrentLocation();
    auto odsResult = parseVariadicInvertibleOperands(parser, inputsOperands, resultRawType, invertedAttr, result.attributes);
    if (odsResult) return ::mlir::failure();
    result.getOrAddProperties<AndInverterOp::Properties>().inverted = invertedAttr;
  }
  result.addTypes(resultTypes);
  if (parser.resolveOperands(inputsOperands, resultTypes[0], inputsOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void AndInverterOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  printVariadicInvertibleOperands(_odsPrinter, *this, getInputs(), getResult().getType(), getInvertedAttr(), getOperation()->getAttrDictionary());
}

void AndInverterOp::getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects) {
}


} // namespace circt::synth::aig
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::synth::aig::AndInverterOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::synth::aig::detail::AndInverterOpGenericAdaptorBase::Properties)

namespace circt::synth {


//===----------------------------------------------------------------------===//
// ::circt::synth::ChoiceOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

ChoiceOpGenericAdaptorBase::ChoiceOpGenericAdaptorBase(ChoiceOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

std::pair<unsigned, unsigned> ChoiceOpGenericAdaptorBase::getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
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
ChoiceOpAdaptor::ChoiceOpAdaptor(ChoiceOp op) : ChoiceOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult ChoiceOpAdaptor::verify(::mlir::Location loc) {
  return ::mlir::success();
}

std::pair<unsigned, unsigned> ChoiceOp::getODSOperandIndexAndLength(unsigned index) {
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

::mlir::MutableOperandRange ChoiceOp::getInputsMutable() {
  auto range = getODSOperandIndexAndLength(0);
  auto mutableRange = ::mlir::MutableOperandRange(getOperation(), range.first, range.second);
  return mutableRange;
}

::llvm::LogicalResult ChoiceOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }
      return ::mlir::success();
}

::mlir::Attribute ChoiceOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code ChoiceOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine();
}

std::optional<mlir::Attribute> ChoiceOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
  return std::nullopt;
}

void ChoiceOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
}

void ChoiceOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
}

::llvm::LogicalResult ChoiceOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    return ::mlir::success();
}

void ChoiceOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::ValueRange inputs) {
  odsState.addOperands(inputs);
  odsState.addTypes(result);
}

ChoiceOp ChoiceOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::ValueRange inputs) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(result)>(result), std::forward<decltype(inputs)>(inputs));
  auto __res__ = ::llvm::dyn_cast<ChoiceOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ChoiceOp ChoiceOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::ValueRange inputs) {
  return create(builder, builder.getLoc(), std::forward<decltype(result)>(result), std::forward<decltype(inputs)>(inputs));
}

void ChoiceOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

ChoiceOp ChoiceOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<ChoiceOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ChoiceOp ChoiceOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void ChoiceOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

ChoiceOp ChoiceOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<ChoiceOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ChoiceOp ChoiceOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

void ChoiceOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  odsState.addTypes({operands[0].getType()});

}

ChoiceOp ChoiceOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<ChoiceOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ChoiceOp ChoiceOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void ChoiceOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  odsState.addTypes({operands[0].getType()});

}

ChoiceOp ChoiceOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<ChoiceOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ChoiceOp ChoiceOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult ChoiceOp::verifyInvariantsImpl() {
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Synth1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Synth2(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult ChoiceOp::verifyInvariants() {
  if(::mlir::succeeded(verifyInvariantsImpl()) && ::mlir::succeeded(verify()))
    return ::mlir::success();
  return ::mlir::failure();
}

void ChoiceOp::getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context) {
  results.add(canonicalize);
}

::mlir::ParseResult ChoiceOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::llvm::SmallVector<::mlir::OpAsmParser::UnresolvedOperand, 4> inputsOperands;
  ::llvm::SMLoc inputsOperandsLoc;
  (void)inputsOperandsLoc;
  ::mlir::Type resultRawType{};
  ::llvm::ArrayRef<::mlir::Type> resultTypes(&resultRawType, 1);

  inputsOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperandList(inputsOperands))
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
  if (parser.parseColon())
    return ::mlir::failure();

  {
    ::mlir::Type type;
    if (parser.parseCustomTypeWithFallback(type))
      return ::mlir::failure();
    resultRawType = type;
  }
  result.addTypes(resultTypes);
  if (parser.resolveOperands(inputsOperands, resultTypes[0], inputsOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void ChoiceOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter << getInputs();
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
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

void ChoiceOp::getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects) {
}


} // namespace circt::synth
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::synth::ChoiceOp)

namespace circt::synth {


//===----------------------------------------------------------------------===//
// ::circt::synth::DotOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

DotOpGenericAdaptorBase::DotOpGenericAdaptorBase(DotOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

std::pair<unsigned, unsigned> DotOpGenericAdaptorBase::getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
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

::llvm::ArrayRef<bool> DotOpGenericAdaptorBase::getInverted() {
  auto attr = getInvertedAttr();
  return attr;
}


} // namespace detail
DotOpAdaptor::DotOpAdaptor(DotOp op) : DotOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult DotOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_inverted = getProperties().inverted; (void)tblgen_inverted;
  if (!tblgen_inverted) return emitError(loc, "'synth.dot' op requires attribute 'inverted'");

  if (tblgen_inverted && !((::llvm::isa<::mlir::DenseBoolArrayAttr>(tblgen_inverted))))
    return emitError(loc, "'synth.dot' op attribute 'inverted' failed to satisfy constraint: i1 dense array attribute");
  return ::mlir::success();
}

std::pair<unsigned, unsigned> DotOp::getODSOperandIndexAndLength(unsigned index) {
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

::mlir::MutableOperandRange DotOp::getInputsMutable() {
  auto range = getODSOperandIndexAndLength(0);
  auto mutableRange = ::mlir::MutableOperandRange(getOperation(), range.first, range.second);
  return mutableRange;
}

::llvm::LogicalResult DotOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.inverted;
       auto attr = dict.get("inverted");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `inverted` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  return ::mlir::success();
}

::mlir::Attribute DotOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.inverted;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("inverted",
                                       propStorage));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code DotOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.inverted.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> DotOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "inverted")
      return prop.inverted;
  return std::nullopt;
}

void DotOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "inverted") {
       prop.inverted = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.inverted)>>(value);
       return;
    }
}

void DotOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.inverted) attrs.append("inverted", prop.inverted);
}

::llvm::LogicalResult DotOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getInvertedAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Synth1(attr, "inverted", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult DotOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.inverted)))
    return ::mlir::failure();
  return ::mlir::success();
}

void DotOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.inverted);
}

::llvm::ArrayRef<bool> DotOp::getInverted() {
  auto attr = getInvertedAttr();
  return attr;
}

void DotOp::setInverted(::llvm::ArrayRef<bool> attrValue) {
  getProperties().inverted = ::mlir::Builder((*this)->getContext()).getDenseBoolArrayAttr(attrValue);
}

void DotOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value a, Value b, Value c, bool invertA, bool invertB, bool invertC) {
      SmallVector<bool> inverted{invertA, invertB, invertC};
      return build(odsBuilder, odsState, ValueRange{a, b, c},
                   odsBuilder.getDenseBoolArrayAttr(inverted));
    
}

DotOp DotOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, Value a, Value b, Value c, bool invertA, bool invertB, bool invertC) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(a)>(a), std::forward<decltype(b)>(b), std::forward<decltype(c)>(c), std::forward<decltype(invertA)>(invertA), std::forward<decltype(invertB)>(invertB), std::forward<decltype(invertC)>(invertC));
  auto __res__ = ::llvm::dyn_cast<DotOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

DotOp DotOp::create(::mlir::ImplicitLocOpBuilder &builder, Value a, Value b, Value c, bool invertA, bool invertB, bool invertC) {
  return create(builder, builder.getLoc(), std::forward<decltype(a)>(a), std::forward<decltype(b)>(b), std::forward<decltype(c)>(c), std::forward<decltype(invertA)>(invertA), std::forward<decltype(invertB)>(invertB), std::forward<decltype(invertC)>(invertC));
}

void DotOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::ValueRange inputs, ::mlir::DenseBoolArrayAttr inverted) {
  odsState.addOperands(inputs);
  odsState.getOrAddProperties<Properties>().inverted = inverted;
  odsState.addTypes(result);
}

DotOp DotOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::ValueRange inputs, ::mlir::DenseBoolArrayAttr inverted) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(result)>(result), std::forward<decltype(inputs)>(inputs), std::forward<decltype(inverted)>(inverted));
  auto __res__ = ::llvm::dyn_cast<DotOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

DotOp DotOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::ValueRange inputs, ::mlir::DenseBoolArrayAttr inverted) {
  return create(builder, builder.getLoc(), std::forward<decltype(result)>(result), std::forward<decltype(inputs)>(inputs), std::forward<decltype(inverted)>(inverted));
}

void DotOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange inputs, ::mlir::DenseBoolArrayAttr inverted) {
  odsState.addOperands(inputs);
  odsState.getOrAddProperties<Properties>().inverted = inverted;
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

DotOp DotOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange inputs, ::mlir::DenseBoolArrayAttr inverted) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(inputs)>(inputs), std::forward<decltype(inverted)>(inverted));
  auto __res__ = ::llvm::dyn_cast<DotOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

DotOp DotOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange inputs, ::mlir::DenseBoolArrayAttr inverted) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(inputs)>(inputs), std::forward<decltype(inverted)>(inverted));
}

void DotOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::ValueRange inputs, ::llvm::ArrayRef<bool> inverted) {
  odsState.addOperands(inputs);
  odsState.getOrAddProperties<Properties>().inverted = odsBuilder.getDenseBoolArrayAttr(inverted);
  odsState.addTypes(result);
}

DotOp DotOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::ValueRange inputs, ::llvm::ArrayRef<bool> inverted) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(result)>(result), std::forward<decltype(inputs)>(inputs), std::forward<decltype(inverted)>(inverted));
  auto __res__ = ::llvm::dyn_cast<DotOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

DotOp DotOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::ValueRange inputs, ::llvm::ArrayRef<bool> inverted) {
  return create(builder, builder.getLoc(), std::forward<decltype(result)>(result), std::forward<decltype(inputs)>(inputs), std::forward<decltype(inverted)>(inverted));
}

void DotOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange inputs, ::llvm::ArrayRef<bool> inverted) {
  odsState.addOperands(inputs);
  odsState.getOrAddProperties<Properties>().inverted = odsBuilder.getDenseBoolArrayAttr(inverted);
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

DotOp DotOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange inputs, ::llvm::ArrayRef<bool> inverted) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(inputs)>(inputs), std::forward<decltype(inverted)>(inverted));
  auto __res__ = ::llvm::dyn_cast<DotOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

DotOp DotOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange inputs, ::llvm::ArrayRef<bool> inverted) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(inputs)>(inputs), std::forward<decltype(inverted)>(inverted));
}

void DotOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<DotOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

DotOp DotOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<DotOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

DotOp DotOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void DotOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

DotOp DotOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<DotOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

DotOp DotOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

void DotOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange inputs, ::mlir::DenseBoolArrayAttr inverted) {
  odsState.addOperands(inputs);
  odsState.getOrAddProperties<Properties>().inverted = inverted;
  odsState.addTypes({inputs.front().getType()});

}

DotOp DotOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange inputs, ::mlir::DenseBoolArrayAttr inverted) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(inputs)>(inputs), std::forward<decltype(inverted)>(inverted));
  auto __res__ = ::llvm::dyn_cast<DotOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

DotOp DotOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange inputs, ::mlir::DenseBoolArrayAttr inverted) {
  return create(builder, builder.getLoc(), std::forward<decltype(inputs)>(inputs), std::forward<decltype(inverted)>(inverted));
}

void DotOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange inputs, ::llvm::ArrayRef<bool> inverted) {
  odsState.addOperands(inputs);
  odsState.getOrAddProperties<Properties>().inverted = odsBuilder.getDenseBoolArrayAttr(inverted);
  odsState.addTypes({inputs.front().getType()});

}

DotOp DotOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange inputs, ::llvm::ArrayRef<bool> inverted) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(inputs)>(inputs), std::forward<decltype(inverted)>(inverted));
  auto __res__ = ::llvm::dyn_cast<DotOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

DotOp DotOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange inputs, ::llvm::ArrayRef<bool> inverted) {
  return create(builder, builder.getLoc(), std::forward<decltype(inputs)>(inputs), std::forward<decltype(inverted)>(inverted));
}

void DotOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  odsState.addTypes({operands[0].getType()});

}

DotOp DotOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<DotOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

DotOp DotOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void DotOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  odsState.addTypes({operands[0].getType()});

}

DotOp DotOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<DotOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

DotOp DotOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult DotOp::verifyInvariantsImpl() {
  auto tblgen_inverted = getProperties().inverted; (void)tblgen_inverted;
  if (!tblgen_inverted) return emitOpError("requires attribute 'inverted'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Synth1(*this, tblgen_inverted, "inverted")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Synth1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Synth2(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  if (!((getOperation()->getNumOperands() == 3)))
    return emitOpError("failed to verify that requires exactly three operands");
  if (!((getInverted().size() == 3)))
    return emitOpError("failed to verify that requires exactly three inversion flags");
  return ::mlir::success();
}

::llvm::LogicalResult DotOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult DotOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::llvm::SmallVector<::mlir::OpAsmParser::UnresolvedOperand, 4> inputsOperands;
  ::llvm::SMLoc inputsOperandsLoc;
  (void)inputsOperandsLoc;
  ::mlir::Type resultRawType{};
  ::llvm::ArrayRef<::mlir::Type> resultTypes(&resultRawType, 1);
  ::mlir::DenseBoolArrayAttr invertedAttr;
  {
    inputsOperandsLoc = parser.getCurrentLocation();
    auto odsResult = parseVariadicInvertibleOperands(parser, inputsOperands, resultRawType, invertedAttr, result.attributes);
    if (odsResult) return ::mlir::failure();
    result.getOrAddProperties<DotOp::Properties>().inverted = invertedAttr;
  }
  result.addTypes(resultTypes);
  if (parser.resolveOperands(inputsOperands, resultTypes[0], inputsOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void DotOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  printVariadicInvertibleOperands(_odsPrinter, *this, getInputs(), getResult().getType(), getInvertedAttr(), getOperation()->getAttrDictionary());
}

void DotOp::getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects) {
}

bool DotOp::areInputsPermutationInvariant() {
  return false;
}
bool DotOp::supportsNumInputs(unsigned numInputs) {
  return numInputs == 3;
}
int64_t DotOp::getLogicDepthCost() { return 1; }
std::optional<uint64_t> DotOp::getLogicAreaCost() {
  int64_t bitWidth = hw::getBitWidth(getType());
  if (bitWidth < 0)
    return std::nullopt;
  return static_cast<uint64_t>(bitWidth);
}
::llvm::KnownBits DotOp::computeKnownBits(
    ::llvm::function_ref<const ::llvm::KnownBits &(unsigned)>
        getInputKnownBits) {
  auto a = applyInputInversion(getInputKnownBits(0), isInverted(0));
  auto b = applyInputInversion(getInputKnownBits(1), isInverted(1));
  auto c = applyInputInversion(getInputKnownBits(2), isInverted(2));
  return evaluateDotLogic(a, b, c);
}
::llvm::APInt DotOp::evaluateBooleanLogicWithoutInversion(
    ::llvm::ArrayRef<::llvm::APInt> inputs) {
  assert(inputs.size() == 3 && "expected exactly three inputs");
  return evaluateDotLogic(inputs[0], inputs[1], inputs[2]);
}

} // namespace circt::synth
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::synth::DotOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::synth::detail::DotOpGenericAdaptorBase::Properties)

namespace circt::synth {


//===----------------------------------------------------------------------===//
// ::circt::synth::GambleOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

GambleOpGenericAdaptorBase::GambleOpGenericAdaptorBase(GambleOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

std::pair<unsigned, unsigned> GambleOpGenericAdaptorBase::getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
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

::llvm::ArrayRef<bool> GambleOpGenericAdaptorBase::getInverted() {
  auto attr = getInvertedAttr();
  return attr;
}


} // namespace detail
GambleOpAdaptor::GambleOpAdaptor(GambleOp op) : GambleOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult GambleOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_inverted = getProperties().inverted; (void)tblgen_inverted;
  if (!tblgen_inverted) return emitError(loc, "'synth.gamble' op requires attribute 'inverted'");

  if (tblgen_inverted && !((::llvm::isa<::mlir::DenseBoolArrayAttr>(tblgen_inverted))))
    return emitError(loc, "'synth.gamble' op attribute 'inverted' failed to satisfy constraint: i1 dense array attribute");
  return ::mlir::success();
}

std::pair<unsigned, unsigned> GambleOp::getODSOperandIndexAndLength(unsigned index) {
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

::mlir::MutableOperandRange GambleOp::getInputsMutable() {
  auto range = getODSOperandIndexAndLength(0);
  auto mutableRange = ::mlir::MutableOperandRange(getOperation(), range.first, range.second);
  return mutableRange;
}

::llvm::LogicalResult GambleOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.inverted;
       auto attr = dict.get("inverted");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `inverted` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  return ::mlir::success();
}

::mlir::Attribute GambleOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.inverted;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("inverted",
                                       propStorage));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code GambleOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.inverted.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> GambleOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "inverted")
      return prop.inverted;
  return std::nullopt;
}

void GambleOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "inverted") {
       prop.inverted = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.inverted)>>(value);
       return;
    }
}

void GambleOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.inverted) attrs.append("inverted", prop.inverted);
}

::llvm::LogicalResult GambleOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getInvertedAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Synth1(attr, "inverted", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult GambleOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.inverted)))
    return ::mlir::failure();
  return ::mlir::success();
}

void GambleOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.inverted);
}

::llvm::ArrayRef<bool> GambleOp::getInverted() {
  auto attr = getInvertedAttr();
  return attr;
}

void GambleOp::setInverted(::llvm::ArrayRef<bool> attrValue) {
  getProperties().inverted = ::mlir::Builder((*this)->getContext()).getDenseBoolArrayAttr(attrValue);
}

void GambleOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value a, Value b, Value c, bool invertA, bool invertB, bool invertC) {
      SmallVector<bool> inverted{invertA, invertB, invertC};
      return build(odsBuilder, odsState, ValueRange{a, b, c},
                   odsBuilder.getDenseBoolArrayAttr(inverted));
    
}

GambleOp GambleOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, Value a, Value b, Value c, bool invertA, bool invertB, bool invertC) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(a)>(a), std::forward<decltype(b)>(b), std::forward<decltype(c)>(c), std::forward<decltype(invertA)>(invertA), std::forward<decltype(invertB)>(invertB), std::forward<decltype(invertC)>(invertC));
  auto __res__ = ::llvm::dyn_cast<GambleOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

GambleOp GambleOp::create(::mlir::ImplicitLocOpBuilder &builder, Value a, Value b, Value c, bool invertA, bool invertB, bool invertC) {
  return create(builder, builder.getLoc(), std::forward<decltype(a)>(a), std::forward<decltype(b)>(b), std::forward<decltype(c)>(c), std::forward<decltype(invertA)>(invertA), std::forward<decltype(invertB)>(invertB), std::forward<decltype(invertC)>(invertC));
}

void GambleOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::ValueRange inputs, ::mlir::DenseBoolArrayAttr inverted) {
  odsState.addOperands(inputs);
  odsState.getOrAddProperties<Properties>().inverted = inverted;
  odsState.addTypes(result);
}

GambleOp GambleOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::ValueRange inputs, ::mlir::DenseBoolArrayAttr inverted) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(result)>(result), std::forward<decltype(inputs)>(inputs), std::forward<decltype(inverted)>(inverted));
  auto __res__ = ::llvm::dyn_cast<GambleOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

GambleOp GambleOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::ValueRange inputs, ::mlir::DenseBoolArrayAttr inverted) {
  return create(builder, builder.getLoc(), std::forward<decltype(result)>(result), std::forward<decltype(inputs)>(inputs), std::forward<decltype(inverted)>(inverted));
}

void GambleOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange inputs, ::mlir::DenseBoolArrayAttr inverted) {
  odsState.addOperands(inputs);
  odsState.getOrAddProperties<Properties>().inverted = inverted;
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

GambleOp GambleOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange inputs, ::mlir::DenseBoolArrayAttr inverted) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(inputs)>(inputs), std::forward<decltype(inverted)>(inverted));
  auto __res__ = ::llvm::dyn_cast<GambleOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

GambleOp GambleOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange inputs, ::mlir::DenseBoolArrayAttr inverted) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(inputs)>(inputs), std::forward<decltype(inverted)>(inverted));
}

void GambleOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::ValueRange inputs, ::llvm::ArrayRef<bool> inverted) {
  odsState.addOperands(inputs);
  odsState.getOrAddProperties<Properties>().inverted = odsBuilder.getDenseBoolArrayAttr(inverted);
  odsState.addTypes(result);
}

GambleOp GambleOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::ValueRange inputs, ::llvm::ArrayRef<bool> inverted) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(result)>(result), std::forward<decltype(inputs)>(inputs), std::forward<decltype(inverted)>(inverted));
  auto __res__ = ::llvm::dyn_cast<GambleOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

GambleOp GambleOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::ValueRange inputs, ::llvm::ArrayRef<bool> inverted) {
  return create(builder, builder.getLoc(), std::forward<decltype(result)>(result), std::forward<decltype(inputs)>(inputs), std::forward<decltype(inverted)>(inverted));
}

void GambleOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange inputs, ::llvm::ArrayRef<bool> inverted) {
  odsState.addOperands(inputs);
  odsState.getOrAddProperties<Properties>().inverted = odsBuilder.getDenseBoolArrayAttr(inverted);
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

GambleOp GambleOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange inputs, ::llvm::ArrayRef<bool> inverted) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(inputs)>(inputs), std::forward<decltype(inverted)>(inverted));
  auto __res__ = ::llvm::dyn_cast<GambleOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

GambleOp GambleOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange inputs, ::llvm::ArrayRef<bool> inverted) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(inputs)>(inputs), std::forward<decltype(inverted)>(inverted));
}

void GambleOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<GambleOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

GambleOp GambleOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<GambleOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

GambleOp GambleOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void GambleOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

GambleOp GambleOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<GambleOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

GambleOp GambleOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

void GambleOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange inputs, ::mlir::DenseBoolArrayAttr inverted) {
  odsState.addOperands(inputs);
  odsState.getOrAddProperties<Properties>().inverted = inverted;
  odsState.addTypes({inputs.front().getType()});

}

GambleOp GambleOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange inputs, ::mlir::DenseBoolArrayAttr inverted) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(inputs)>(inputs), std::forward<decltype(inverted)>(inverted));
  auto __res__ = ::llvm::dyn_cast<GambleOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

GambleOp GambleOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange inputs, ::mlir::DenseBoolArrayAttr inverted) {
  return create(builder, builder.getLoc(), std::forward<decltype(inputs)>(inputs), std::forward<decltype(inverted)>(inverted));
}

void GambleOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange inputs, ::llvm::ArrayRef<bool> inverted) {
  odsState.addOperands(inputs);
  odsState.getOrAddProperties<Properties>().inverted = odsBuilder.getDenseBoolArrayAttr(inverted);
  odsState.addTypes({inputs.front().getType()});

}

GambleOp GambleOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange inputs, ::llvm::ArrayRef<bool> inverted) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(inputs)>(inputs), std::forward<decltype(inverted)>(inverted));
  auto __res__ = ::llvm::dyn_cast<GambleOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

GambleOp GambleOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange inputs, ::llvm::ArrayRef<bool> inverted) {
  return create(builder, builder.getLoc(), std::forward<decltype(inputs)>(inputs), std::forward<decltype(inverted)>(inverted));
}

void GambleOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  odsState.addTypes({operands[0].getType()});

}

GambleOp GambleOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<GambleOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

GambleOp GambleOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void GambleOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  odsState.addTypes({operands[0].getType()});

}

GambleOp GambleOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<GambleOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

GambleOp GambleOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult GambleOp::verifyInvariantsImpl() {
  auto tblgen_inverted = getProperties().inverted; (void)tblgen_inverted;
  if (!tblgen_inverted) return emitOpError("requires attribute 'inverted'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Synth1(*this, tblgen_inverted, "inverted")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Synth1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Synth2(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  if (!((getOperation()->getNumOperands() == 3)))
    return emitOpError("failed to verify that requires exactly three operands");
  if (!((getInverted().size() == 3)))
    return emitOpError("failed to verify that requires exactly three inversion flags");
  return ::mlir::success();
}

::llvm::LogicalResult GambleOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult GambleOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::llvm::SmallVector<::mlir::OpAsmParser::UnresolvedOperand, 4> inputsOperands;
  ::llvm::SMLoc inputsOperandsLoc;
  (void)inputsOperandsLoc;
  ::mlir::Type resultRawType{};
  ::llvm::ArrayRef<::mlir::Type> resultTypes(&resultRawType, 1);
  ::mlir::DenseBoolArrayAttr invertedAttr;
  {
    inputsOperandsLoc = parser.getCurrentLocation();
    auto odsResult = parseVariadicInvertibleOperands(parser, inputsOperands, resultRawType, invertedAttr, result.attributes);
    if (odsResult) return ::mlir::failure();
    result.getOrAddProperties<GambleOp::Properties>().inverted = invertedAttr;
  }
  result.addTypes(resultTypes);
  if (parser.resolveOperands(inputsOperands, resultTypes[0], inputsOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void GambleOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  printVariadicInvertibleOperands(_odsPrinter, *this, getInputs(), getResult().getType(), getInvertedAttr(), getOperation()->getAttrDictionary());
}

void GambleOp::getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects) {
}

bool GambleOp::areInputsPermutationInvariant() {
  return true;
}
bool GambleOp::supportsNumInputs(unsigned numInputs) {
  return numInputs == 3;
}
int64_t GambleOp::getLogicDepthCost() { return 1; }
std::optional<uint64_t> GambleOp::getLogicAreaCost() {
  int64_t bitWidth = hw::getBitWidth(getType());
  if (bitWidth < 0)
    return std::nullopt;
  return static_cast<uint64_t>(bitWidth);
}
::llvm::KnownBits GambleOp::computeKnownBits(
    ::llvm::function_ref<const ::llvm::KnownBits &(unsigned)>
        getInputKnownBits) {
  auto a = applyInputInversion(getInputKnownBits(0), isInverted(0));
  auto b = applyInputInversion(getInputKnownBits(1), isInverted(1));
  auto c = applyInputInversion(getInputKnownBits(2), isInverted(2));
  return evaluateGambleLogic(a, b, c);
}
::llvm::APInt GambleOp::evaluateBooleanLogicWithoutInversion(
    ::llvm::ArrayRef<::llvm::APInt> inputs) {
  assert(inputs.size() == 3 && "expected exactly three inputs");
  return evaluateGambleLogic(inputs[0], inputs[1], inputs[2]);
}

} // namespace circt::synth
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::synth::GambleOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::synth::detail::GambleOpGenericAdaptorBase::Properties)

namespace circt::synth {


//===----------------------------------------------------------------------===//
// ::circt::synth::MajorityOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

MajorityOpGenericAdaptorBase::MajorityOpGenericAdaptorBase(MajorityOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

std::pair<unsigned, unsigned> MajorityOpGenericAdaptorBase::getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
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

::llvm::ArrayRef<bool> MajorityOpGenericAdaptorBase::getInverted() {
  auto attr = getInvertedAttr();
  return attr;
}


} // namespace detail
MajorityOpAdaptor::MajorityOpAdaptor(MajorityOp op) : MajorityOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult MajorityOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_inverted = getProperties().inverted; (void)tblgen_inverted;
  if (!tblgen_inverted) return emitError(loc, "'synth.majority' op requires attribute 'inverted'");

  if (tblgen_inverted && !((::llvm::isa<::mlir::DenseBoolArrayAttr>(tblgen_inverted))))
    return emitError(loc, "'synth.majority' op attribute 'inverted' failed to satisfy constraint: i1 dense array attribute");
  return ::mlir::success();
}

std::pair<unsigned, unsigned> MajorityOp::getODSOperandIndexAndLength(unsigned index) {
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

::mlir::MutableOperandRange MajorityOp::getInputsMutable() {
  auto range = getODSOperandIndexAndLength(0);
  auto mutableRange = ::mlir::MutableOperandRange(getOperation(), range.first, range.second);
  return mutableRange;
}

::llvm::LogicalResult MajorityOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.inverted;
       auto attr = dict.get("inverted");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `inverted` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  return ::mlir::success();
}

::mlir::Attribute MajorityOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.inverted;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("inverted",
                                       propStorage));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code MajorityOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.inverted.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> MajorityOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "inverted")
      return prop.inverted;
  return std::nullopt;
}

void MajorityOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "inverted") {
       prop.inverted = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.inverted)>>(value);
       return;
    }
}

void MajorityOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.inverted) attrs.append("inverted", prop.inverted);
}

::llvm::LogicalResult MajorityOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getInvertedAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Synth1(attr, "inverted", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult MajorityOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.inverted)))
    return ::mlir::failure();
  return ::mlir::success();
}

void MajorityOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.inverted);
}

::llvm::ArrayRef<bool> MajorityOp::getInverted() {
  auto attr = getInvertedAttr();
  return attr;
}

void MajorityOp::setInverted(::llvm::ArrayRef<bool> attrValue) {
  getProperties().inverted = ::mlir::Builder((*this)->getContext()).getDenseBoolArrayAttr(attrValue);
}

void MajorityOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value a, Value b, Value c, bool invertA, bool invertB, bool invertC) {
      SmallVector<bool> inverted{invertA, invertB, invertC};
      return build(odsBuilder, odsState, ValueRange{a, b, c},
                   odsBuilder.getDenseBoolArrayAttr(inverted));
    
}

MajorityOp MajorityOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, Value a, Value b, Value c, bool invertA, bool invertB, bool invertC) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(a)>(a), std::forward<decltype(b)>(b), std::forward<decltype(c)>(c), std::forward<decltype(invertA)>(invertA), std::forward<decltype(invertB)>(invertB), std::forward<decltype(invertC)>(invertC));
  auto __res__ = ::llvm::dyn_cast<MajorityOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

MajorityOp MajorityOp::create(::mlir::ImplicitLocOpBuilder &builder, Value a, Value b, Value c, bool invertA, bool invertB, bool invertC) {
  return create(builder, builder.getLoc(), std::forward<decltype(a)>(a), std::forward<decltype(b)>(b), std::forward<decltype(c)>(c), std::forward<decltype(invertA)>(invertA), std::forward<decltype(invertB)>(invertB), std::forward<decltype(invertC)>(invertC));
}

void MajorityOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::ValueRange inputs, ::mlir::DenseBoolArrayAttr inverted) {
  odsState.addOperands(inputs);
  odsState.getOrAddProperties<Properties>().inverted = inverted;
  odsState.addTypes(result);
}

MajorityOp MajorityOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::ValueRange inputs, ::mlir::DenseBoolArrayAttr inverted) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(result)>(result), std::forward<decltype(inputs)>(inputs), std::forward<decltype(inverted)>(inverted));
  auto __res__ = ::llvm::dyn_cast<MajorityOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

MajorityOp MajorityOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::ValueRange inputs, ::mlir::DenseBoolArrayAttr inverted) {
  return create(builder, builder.getLoc(), std::forward<decltype(result)>(result), std::forward<decltype(inputs)>(inputs), std::forward<decltype(inverted)>(inverted));
}

void MajorityOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange inputs, ::mlir::DenseBoolArrayAttr inverted) {
  odsState.addOperands(inputs);
  odsState.getOrAddProperties<Properties>().inverted = inverted;
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

MajorityOp MajorityOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange inputs, ::mlir::DenseBoolArrayAttr inverted) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(inputs)>(inputs), std::forward<decltype(inverted)>(inverted));
  auto __res__ = ::llvm::dyn_cast<MajorityOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

MajorityOp MajorityOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange inputs, ::mlir::DenseBoolArrayAttr inverted) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(inputs)>(inputs), std::forward<decltype(inverted)>(inverted));
}

void MajorityOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::ValueRange inputs, ::llvm::ArrayRef<bool> inverted) {
  odsState.addOperands(inputs);
  odsState.getOrAddProperties<Properties>().inverted = odsBuilder.getDenseBoolArrayAttr(inverted);
  odsState.addTypes(result);
}

MajorityOp MajorityOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::ValueRange inputs, ::llvm::ArrayRef<bool> inverted) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(result)>(result), std::forward<decltype(inputs)>(inputs), std::forward<decltype(inverted)>(inverted));
  auto __res__ = ::llvm::dyn_cast<MajorityOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

MajorityOp MajorityOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::ValueRange inputs, ::llvm::ArrayRef<bool> inverted) {
  return create(builder, builder.getLoc(), std::forward<decltype(result)>(result), std::forward<decltype(inputs)>(inputs), std::forward<decltype(inverted)>(inverted));
}

void MajorityOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange inputs, ::llvm::ArrayRef<bool> inverted) {
  odsState.addOperands(inputs);
  odsState.getOrAddProperties<Properties>().inverted = odsBuilder.getDenseBoolArrayAttr(inverted);
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

MajorityOp MajorityOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange inputs, ::llvm::ArrayRef<bool> inverted) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(inputs)>(inputs), std::forward<decltype(inverted)>(inverted));
  auto __res__ = ::llvm::dyn_cast<MajorityOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

MajorityOp MajorityOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange inputs, ::llvm::ArrayRef<bool> inverted) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(inputs)>(inputs), std::forward<decltype(inverted)>(inverted));
}

void MajorityOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<MajorityOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

MajorityOp MajorityOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<MajorityOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

MajorityOp MajorityOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void MajorityOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

MajorityOp MajorityOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<MajorityOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

MajorityOp MajorityOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

void MajorityOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange inputs, ::mlir::DenseBoolArrayAttr inverted) {
  odsState.addOperands(inputs);
  odsState.getOrAddProperties<Properties>().inverted = inverted;
  odsState.addTypes({inputs.front().getType()});

}

MajorityOp MajorityOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange inputs, ::mlir::DenseBoolArrayAttr inverted) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(inputs)>(inputs), std::forward<decltype(inverted)>(inverted));
  auto __res__ = ::llvm::dyn_cast<MajorityOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

MajorityOp MajorityOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange inputs, ::mlir::DenseBoolArrayAttr inverted) {
  return create(builder, builder.getLoc(), std::forward<decltype(inputs)>(inputs), std::forward<decltype(inverted)>(inverted));
}

void MajorityOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange inputs, ::llvm::ArrayRef<bool> inverted) {
  odsState.addOperands(inputs);
  odsState.getOrAddProperties<Properties>().inverted = odsBuilder.getDenseBoolArrayAttr(inverted);
  odsState.addTypes({inputs.front().getType()});

}

MajorityOp MajorityOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange inputs, ::llvm::ArrayRef<bool> inverted) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(inputs)>(inputs), std::forward<decltype(inverted)>(inverted));
  auto __res__ = ::llvm::dyn_cast<MajorityOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

MajorityOp MajorityOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange inputs, ::llvm::ArrayRef<bool> inverted) {
  return create(builder, builder.getLoc(), std::forward<decltype(inputs)>(inputs), std::forward<decltype(inverted)>(inverted));
}

void MajorityOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  odsState.addTypes({operands[0].getType()});

}

MajorityOp MajorityOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<MajorityOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

MajorityOp MajorityOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void MajorityOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  odsState.addTypes({operands[0].getType()});

}

MajorityOp MajorityOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<MajorityOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

MajorityOp MajorityOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult MajorityOp::verifyInvariantsImpl() {
  auto tblgen_inverted = getProperties().inverted; (void)tblgen_inverted;
  if (!tblgen_inverted) return emitOpError("requires attribute 'inverted'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Synth1(*this, tblgen_inverted, "inverted")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Synth1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Synth2(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  if (!((getOperation()->getNumOperands() == 3)))
    return emitOpError("failed to verify that requires exactly three operands");
  if (!((getInverted().size() == 3)))
    return emitOpError("failed to verify that requires exactly three inversion flags");
  return ::mlir::success();
}

::llvm::LogicalResult MajorityOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult MajorityOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::llvm::SmallVector<::mlir::OpAsmParser::UnresolvedOperand, 4> inputsOperands;
  ::llvm::SMLoc inputsOperandsLoc;
  (void)inputsOperandsLoc;
  ::mlir::Type resultRawType{};
  ::llvm::ArrayRef<::mlir::Type> resultTypes(&resultRawType, 1);
  ::mlir::DenseBoolArrayAttr invertedAttr;
  {
    inputsOperandsLoc = parser.getCurrentLocation();
    auto odsResult = parseVariadicInvertibleOperands(parser, inputsOperands, resultRawType, invertedAttr, result.attributes);
    if (odsResult) return ::mlir::failure();
    result.getOrAddProperties<MajorityOp::Properties>().inverted = invertedAttr;
  }
  result.addTypes(resultTypes);
  if (parser.resolveOperands(inputsOperands, resultTypes[0], inputsOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void MajorityOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  printVariadicInvertibleOperands(_odsPrinter, *this, getInputs(), getResult().getType(), getInvertedAttr(), getOperation()->getAttrDictionary());
}

void MajorityOp::getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects) {
}

bool MajorityOp::areInputsPermutationInvariant() {
  return true;
}
bool MajorityOp::supportsNumInputs(unsigned numInputs) {
  return numInputs == 3;
}
int64_t MajorityOp::getLogicDepthCost() { return 1; }
std::optional<uint64_t> MajorityOp::getLogicAreaCost() {
  int64_t bitWidth = hw::getBitWidth(getType());
  if (bitWidth < 0)
    return std::nullopt;
  return static_cast<uint64_t>(bitWidth);
}
::llvm::KnownBits MajorityOp::computeKnownBits(
    ::llvm::function_ref<const ::llvm::KnownBits &(unsigned)>
        getInputKnownBits) {
  auto a = applyInputInversion(getInputKnownBits(0), isInverted(0));
  auto b = applyInputInversion(getInputKnownBits(1), isInverted(1));
  auto c = applyInputInversion(getInputKnownBits(2), isInverted(2));
  return evaluateMajorityLogic(a, b, c);
}
::llvm::APInt MajorityOp::evaluateBooleanLogicWithoutInversion(
    ::llvm::ArrayRef<::llvm::APInt> inputs) {
  assert(inputs.size() == 3 && "expected exactly three inputs");
  return evaluateMajorityLogic(inputs[0], inputs[1], inputs[2]);
}

} // namespace circt::synth
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::synth::MajorityOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::synth::detail::MajorityOpGenericAdaptorBase::Properties)

namespace circt::synth {


//===----------------------------------------------------------------------===//
// ::circt::synth::MuxInverterOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

MuxInverterOpGenericAdaptorBase::MuxInverterOpGenericAdaptorBase(MuxInverterOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

std::pair<unsigned, unsigned> MuxInverterOpGenericAdaptorBase::getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
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

::llvm::ArrayRef<bool> MuxInverterOpGenericAdaptorBase::getInverted() {
  auto attr = getInvertedAttr();
  return attr;
}


} // namespace detail
MuxInverterOpAdaptor::MuxInverterOpAdaptor(MuxInverterOp op) : MuxInverterOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult MuxInverterOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_inverted = getProperties().inverted; (void)tblgen_inverted;
  if (!tblgen_inverted) return emitError(loc, "'synth.mux_inv' op requires attribute 'inverted'");

  if (tblgen_inverted && !((::llvm::isa<::mlir::DenseBoolArrayAttr>(tblgen_inverted))))
    return emitError(loc, "'synth.mux_inv' op attribute 'inverted' failed to satisfy constraint: i1 dense array attribute");
  return ::mlir::success();
}

std::pair<unsigned, unsigned> MuxInverterOp::getODSOperandIndexAndLength(unsigned index) {
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

::mlir::MutableOperandRange MuxInverterOp::getInputsMutable() {
  auto range = getODSOperandIndexAndLength(0);
  auto mutableRange = ::mlir::MutableOperandRange(getOperation(), range.first, range.second);
  return mutableRange;
}

::llvm::LogicalResult MuxInverterOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.inverted;
       auto attr = dict.get("inverted");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `inverted` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  return ::mlir::success();
}

::mlir::Attribute MuxInverterOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.inverted;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("inverted",
                                       propStorage));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code MuxInverterOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.inverted.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> MuxInverterOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "inverted")
      return prop.inverted;
  return std::nullopt;
}

void MuxInverterOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "inverted") {
       prop.inverted = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.inverted)>>(value);
       return;
    }
}

void MuxInverterOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.inverted) attrs.append("inverted", prop.inverted);
}

::llvm::LogicalResult MuxInverterOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getInvertedAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Synth1(attr, "inverted", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult MuxInverterOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.inverted)))
    return ::mlir::failure();
  return ::mlir::success();
}

void MuxInverterOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.inverted);
}

::llvm::ArrayRef<bool> MuxInverterOp::getInverted() {
  auto attr = getInvertedAttr();
  return attr;
}

void MuxInverterOp::setInverted(::llvm::ArrayRef<bool> attrValue) {
  getProperties().inverted = ::mlir::Builder((*this)->getContext()).getDenseBoolArrayAttr(attrValue);
}

void MuxInverterOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value a, Value b, Value c, bool invertA, bool invertB, bool invertC) {
      SmallVector<bool> inverted{invertA, invertB, invertC};
      return build(odsBuilder, odsState, ValueRange{a, b, c},
                   odsBuilder.getDenseBoolArrayAttr(inverted));
    
}

MuxInverterOp MuxInverterOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, Value a, Value b, Value c, bool invertA, bool invertB, bool invertC) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(a)>(a), std::forward<decltype(b)>(b), std::forward<decltype(c)>(c), std::forward<decltype(invertA)>(invertA), std::forward<decltype(invertB)>(invertB), std::forward<decltype(invertC)>(invertC));
  auto __res__ = ::llvm::dyn_cast<MuxInverterOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

MuxInverterOp MuxInverterOp::create(::mlir::ImplicitLocOpBuilder &builder, Value a, Value b, Value c, bool invertA, bool invertB, bool invertC) {
  return create(builder, builder.getLoc(), std::forward<decltype(a)>(a), std::forward<decltype(b)>(b), std::forward<decltype(c)>(c), std::forward<decltype(invertA)>(invertA), std::forward<decltype(invertB)>(invertB), std::forward<decltype(invertC)>(invertC));
}

void MuxInverterOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::ValueRange inputs, ::mlir::DenseBoolArrayAttr inverted) {
  odsState.addOperands(inputs);
  odsState.getOrAddProperties<Properties>().inverted = inverted;
  odsState.addTypes(result);
}

MuxInverterOp MuxInverterOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::ValueRange inputs, ::mlir::DenseBoolArrayAttr inverted) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(result)>(result), std::forward<decltype(inputs)>(inputs), std::forward<decltype(inverted)>(inverted));
  auto __res__ = ::llvm::dyn_cast<MuxInverterOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

MuxInverterOp MuxInverterOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::ValueRange inputs, ::mlir::DenseBoolArrayAttr inverted) {
  return create(builder, builder.getLoc(), std::forward<decltype(result)>(result), std::forward<decltype(inputs)>(inputs), std::forward<decltype(inverted)>(inverted));
}

void MuxInverterOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange inputs, ::mlir::DenseBoolArrayAttr inverted) {
  odsState.addOperands(inputs);
  odsState.getOrAddProperties<Properties>().inverted = inverted;
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

MuxInverterOp MuxInverterOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange inputs, ::mlir::DenseBoolArrayAttr inverted) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(inputs)>(inputs), std::forward<decltype(inverted)>(inverted));
  auto __res__ = ::llvm::dyn_cast<MuxInverterOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

MuxInverterOp MuxInverterOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange inputs, ::mlir::DenseBoolArrayAttr inverted) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(inputs)>(inputs), std::forward<decltype(inverted)>(inverted));
}

void MuxInverterOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::ValueRange inputs, ::llvm::ArrayRef<bool> inverted) {
  odsState.addOperands(inputs);
  odsState.getOrAddProperties<Properties>().inverted = odsBuilder.getDenseBoolArrayAttr(inverted);
  odsState.addTypes(result);
}

MuxInverterOp MuxInverterOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::ValueRange inputs, ::llvm::ArrayRef<bool> inverted) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(result)>(result), std::forward<decltype(inputs)>(inputs), std::forward<decltype(inverted)>(inverted));
  auto __res__ = ::llvm::dyn_cast<MuxInverterOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

MuxInverterOp MuxInverterOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::ValueRange inputs, ::llvm::ArrayRef<bool> inverted) {
  return create(builder, builder.getLoc(), std::forward<decltype(result)>(result), std::forward<decltype(inputs)>(inputs), std::forward<decltype(inverted)>(inverted));
}

void MuxInverterOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange inputs, ::llvm::ArrayRef<bool> inverted) {
  odsState.addOperands(inputs);
  odsState.getOrAddProperties<Properties>().inverted = odsBuilder.getDenseBoolArrayAttr(inverted);
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

MuxInverterOp MuxInverterOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange inputs, ::llvm::ArrayRef<bool> inverted) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(inputs)>(inputs), std::forward<decltype(inverted)>(inverted));
  auto __res__ = ::llvm::dyn_cast<MuxInverterOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

MuxInverterOp MuxInverterOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange inputs, ::llvm::ArrayRef<bool> inverted) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(inputs)>(inputs), std::forward<decltype(inverted)>(inverted));
}

void MuxInverterOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<MuxInverterOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

MuxInverterOp MuxInverterOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<MuxInverterOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

MuxInverterOp MuxInverterOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void MuxInverterOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

MuxInverterOp MuxInverterOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<MuxInverterOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

MuxInverterOp MuxInverterOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

void MuxInverterOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange inputs, ::mlir::DenseBoolArrayAttr inverted) {
  odsState.addOperands(inputs);
  odsState.getOrAddProperties<Properties>().inverted = inverted;
  odsState.addTypes({inputs.front().getType()});

}

MuxInverterOp MuxInverterOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange inputs, ::mlir::DenseBoolArrayAttr inverted) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(inputs)>(inputs), std::forward<decltype(inverted)>(inverted));
  auto __res__ = ::llvm::dyn_cast<MuxInverterOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

MuxInverterOp MuxInverterOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange inputs, ::mlir::DenseBoolArrayAttr inverted) {
  return create(builder, builder.getLoc(), std::forward<decltype(inputs)>(inputs), std::forward<decltype(inverted)>(inverted));
}

void MuxInverterOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange inputs, ::llvm::ArrayRef<bool> inverted) {
  odsState.addOperands(inputs);
  odsState.getOrAddProperties<Properties>().inverted = odsBuilder.getDenseBoolArrayAttr(inverted);
  odsState.addTypes({inputs.front().getType()});

}

MuxInverterOp MuxInverterOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange inputs, ::llvm::ArrayRef<bool> inverted) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(inputs)>(inputs), std::forward<decltype(inverted)>(inverted));
  auto __res__ = ::llvm::dyn_cast<MuxInverterOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

MuxInverterOp MuxInverterOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange inputs, ::llvm::ArrayRef<bool> inverted) {
  return create(builder, builder.getLoc(), std::forward<decltype(inputs)>(inputs), std::forward<decltype(inverted)>(inverted));
}

void MuxInverterOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  odsState.addTypes({operands[0].getType()});

}

MuxInverterOp MuxInverterOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<MuxInverterOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

MuxInverterOp MuxInverterOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void MuxInverterOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  odsState.addTypes({operands[0].getType()});

}

MuxInverterOp MuxInverterOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<MuxInverterOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

MuxInverterOp MuxInverterOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult MuxInverterOp::verifyInvariantsImpl() {
  auto tblgen_inverted = getProperties().inverted; (void)tblgen_inverted;
  if (!tblgen_inverted) return emitOpError("requires attribute 'inverted'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Synth1(*this, tblgen_inverted, "inverted")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Synth1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Synth2(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  if (!((getOperation()->getNumOperands() == 3)))
    return emitOpError("failed to verify that requires exactly three operands");
  if (!((getInverted().size() == 3)))
    return emitOpError("failed to verify that requires exactly three inversion flags");
  return ::mlir::success();
}

::llvm::LogicalResult MuxInverterOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult MuxInverterOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::llvm::SmallVector<::mlir::OpAsmParser::UnresolvedOperand, 4> inputsOperands;
  ::llvm::SMLoc inputsOperandsLoc;
  (void)inputsOperandsLoc;
  ::mlir::Type resultRawType{};
  ::llvm::ArrayRef<::mlir::Type> resultTypes(&resultRawType, 1);
  ::mlir::DenseBoolArrayAttr invertedAttr;
  {
    inputsOperandsLoc = parser.getCurrentLocation();
    auto odsResult = parseVariadicInvertibleOperands(parser, inputsOperands, resultRawType, invertedAttr, result.attributes);
    if (odsResult) return ::mlir::failure();
    result.getOrAddProperties<MuxInverterOp::Properties>().inverted = invertedAttr;
  }
  result.addTypes(resultTypes);
  if (parser.resolveOperands(inputsOperands, resultTypes[0], inputsOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void MuxInverterOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  printVariadicInvertibleOperands(_odsPrinter, *this, getInputs(), getResult().getType(), getInvertedAttr(), getOperation()->getAttrDictionary());
}

void MuxInverterOp::getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects) {
}

bool MuxInverterOp::areInputsPermutationInvariant() {
  return false;
}
bool MuxInverterOp::supportsNumInputs(unsigned numInputs) {
  return numInputs == 3;
}
int64_t MuxInverterOp::getLogicDepthCost() { return 1; }
std::optional<uint64_t> MuxInverterOp::getLogicAreaCost() {
  int64_t bitWidth = hw::getBitWidth(getType());
  if (bitWidth < 0)
    return std::nullopt;
  return static_cast<uint64_t>(bitWidth);
}
::llvm::KnownBits MuxInverterOp::computeKnownBits(
    ::llvm::function_ref<const ::llvm::KnownBits &(unsigned)>
        getInputKnownBits) {
  auto a = applyInputInversion(getInputKnownBits(0), isInverted(0));
  auto b = applyInputInversion(getInputKnownBits(1), isInverted(1));
  auto c = applyInputInversion(getInputKnownBits(2), isInverted(2));
  return evaluateMuxLogic(a, b, c);
}
::llvm::APInt MuxInverterOp::evaluateBooleanLogicWithoutInversion(
    ::llvm::ArrayRef<::llvm::APInt> inputs) {
  assert(inputs.size() == 3 && "expected exactly three inputs");
  return evaluateMuxLogic(inputs[0], inputs[1], inputs[2]);
}

} // namespace circt::synth
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::synth::MuxInverterOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::synth::detail::MuxInverterOpGenericAdaptorBase::Properties)

namespace circt::synth {


//===----------------------------------------------------------------------===//
// ::circt::synth::OneHotOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

OneHotOpGenericAdaptorBase::OneHotOpGenericAdaptorBase(OneHotOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

std::pair<unsigned, unsigned> OneHotOpGenericAdaptorBase::getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
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

::llvm::ArrayRef<bool> OneHotOpGenericAdaptorBase::getInverted() {
  auto attr = getInvertedAttr();
  return attr;
}


} // namespace detail
OneHotOpAdaptor::OneHotOpAdaptor(OneHotOp op) : OneHotOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult OneHotOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_inverted = getProperties().inverted; (void)tblgen_inverted;
  if (!tblgen_inverted) return emitError(loc, "'synth.onehot' op requires attribute 'inverted'");

  if (tblgen_inverted && !((::llvm::isa<::mlir::DenseBoolArrayAttr>(tblgen_inverted))))
    return emitError(loc, "'synth.onehot' op attribute 'inverted' failed to satisfy constraint: i1 dense array attribute");
  return ::mlir::success();
}

std::pair<unsigned, unsigned> OneHotOp::getODSOperandIndexAndLength(unsigned index) {
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

::mlir::MutableOperandRange OneHotOp::getInputsMutable() {
  auto range = getODSOperandIndexAndLength(0);
  auto mutableRange = ::mlir::MutableOperandRange(getOperation(), range.first, range.second);
  return mutableRange;
}

::llvm::LogicalResult OneHotOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.inverted;
       auto attr = dict.get("inverted");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `inverted` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  return ::mlir::success();
}

::mlir::Attribute OneHotOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.inverted;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("inverted",
                                       propStorage));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code OneHotOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.inverted.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> OneHotOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "inverted")
      return prop.inverted;
  return std::nullopt;
}

void OneHotOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "inverted") {
       prop.inverted = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.inverted)>>(value);
       return;
    }
}

void OneHotOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.inverted) attrs.append("inverted", prop.inverted);
}

::llvm::LogicalResult OneHotOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getInvertedAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Synth1(attr, "inverted", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult OneHotOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.inverted)))
    return ::mlir::failure();
  return ::mlir::success();
}

void OneHotOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.inverted);
}

::llvm::ArrayRef<bool> OneHotOp::getInverted() {
  auto attr = getInvertedAttr();
  return attr;
}

void OneHotOp::setInverted(::llvm::ArrayRef<bool> attrValue) {
  getProperties().inverted = ::mlir::Builder((*this)->getContext()).getDenseBoolArrayAttr(attrValue);
}

void OneHotOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value a, Value b, Value c, bool invertA, bool invertB, bool invertC) {
      SmallVector<bool> inverted{invertA, invertB, invertC};
      return build(odsBuilder, odsState, ValueRange{a, b, c},
                   odsBuilder.getDenseBoolArrayAttr(inverted));
    
}

OneHotOp OneHotOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, Value a, Value b, Value c, bool invertA, bool invertB, bool invertC) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(a)>(a), std::forward<decltype(b)>(b), std::forward<decltype(c)>(c), std::forward<decltype(invertA)>(invertA), std::forward<decltype(invertB)>(invertB), std::forward<decltype(invertC)>(invertC));
  auto __res__ = ::llvm::dyn_cast<OneHotOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

OneHotOp OneHotOp::create(::mlir::ImplicitLocOpBuilder &builder, Value a, Value b, Value c, bool invertA, bool invertB, bool invertC) {
  return create(builder, builder.getLoc(), std::forward<decltype(a)>(a), std::forward<decltype(b)>(b), std::forward<decltype(c)>(c), std::forward<decltype(invertA)>(invertA), std::forward<decltype(invertB)>(invertB), std::forward<decltype(invertC)>(invertC));
}

void OneHotOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::ValueRange inputs, ::mlir::DenseBoolArrayAttr inverted) {
  odsState.addOperands(inputs);
  odsState.getOrAddProperties<Properties>().inverted = inverted;
  odsState.addTypes(result);
}

OneHotOp OneHotOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::ValueRange inputs, ::mlir::DenseBoolArrayAttr inverted) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(result)>(result), std::forward<decltype(inputs)>(inputs), std::forward<decltype(inverted)>(inverted));
  auto __res__ = ::llvm::dyn_cast<OneHotOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

OneHotOp OneHotOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::ValueRange inputs, ::mlir::DenseBoolArrayAttr inverted) {
  return create(builder, builder.getLoc(), std::forward<decltype(result)>(result), std::forward<decltype(inputs)>(inputs), std::forward<decltype(inverted)>(inverted));
}

void OneHotOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange inputs, ::mlir::DenseBoolArrayAttr inverted) {
  odsState.addOperands(inputs);
  odsState.getOrAddProperties<Properties>().inverted = inverted;
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

OneHotOp OneHotOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange inputs, ::mlir::DenseBoolArrayAttr inverted) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(inputs)>(inputs), std::forward<decltype(inverted)>(inverted));
  auto __res__ = ::llvm::dyn_cast<OneHotOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

OneHotOp OneHotOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange inputs, ::mlir::DenseBoolArrayAttr inverted) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(inputs)>(inputs), std::forward<decltype(inverted)>(inverted));
}

void OneHotOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::ValueRange inputs, ::llvm::ArrayRef<bool> inverted) {
  odsState.addOperands(inputs);
  odsState.getOrAddProperties<Properties>().inverted = odsBuilder.getDenseBoolArrayAttr(inverted);
  odsState.addTypes(result);
}

OneHotOp OneHotOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::ValueRange inputs, ::llvm::ArrayRef<bool> inverted) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(result)>(result), std::forward<decltype(inputs)>(inputs), std::forward<decltype(inverted)>(inverted));
  auto __res__ = ::llvm::dyn_cast<OneHotOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

OneHotOp OneHotOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::ValueRange inputs, ::llvm::ArrayRef<bool> inverted) {
  return create(builder, builder.getLoc(), std::forward<decltype(result)>(result), std::forward<decltype(inputs)>(inputs), std::forward<decltype(inverted)>(inverted));
}

void OneHotOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange inputs, ::llvm::ArrayRef<bool> inverted) {
  odsState.addOperands(inputs);
  odsState.getOrAddProperties<Properties>().inverted = odsBuilder.getDenseBoolArrayAttr(inverted);
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

OneHotOp OneHotOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange inputs, ::llvm::ArrayRef<bool> inverted) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(inputs)>(inputs), std::forward<decltype(inverted)>(inverted));
  auto __res__ = ::llvm::dyn_cast<OneHotOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

OneHotOp OneHotOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange inputs, ::llvm::ArrayRef<bool> inverted) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(inputs)>(inputs), std::forward<decltype(inverted)>(inverted));
}

void OneHotOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<OneHotOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

OneHotOp OneHotOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<OneHotOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

OneHotOp OneHotOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void OneHotOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

OneHotOp OneHotOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<OneHotOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

OneHotOp OneHotOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

void OneHotOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange inputs, ::mlir::DenseBoolArrayAttr inverted) {
  odsState.addOperands(inputs);
  odsState.getOrAddProperties<Properties>().inverted = inverted;
  odsState.addTypes({inputs.front().getType()});

}

OneHotOp OneHotOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange inputs, ::mlir::DenseBoolArrayAttr inverted) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(inputs)>(inputs), std::forward<decltype(inverted)>(inverted));
  auto __res__ = ::llvm::dyn_cast<OneHotOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

OneHotOp OneHotOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange inputs, ::mlir::DenseBoolArrayAttr inverted) {
  return create(builder, builder.getLoc(), std::forward<decltype(inputs)>(inputs), std::forward<decltype(inverted)>(inverted));
}

void OneHotOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange inputs, ::llvm::ArrayRef<bool> inverted) {
  odsState.addOperands(inputs);
  odsState.getOrAddProperties<Properties>().inverted = odsBuilder.getDenseBoolArrayAttr(inverted);
  odsState.addTypes({inputs.front().getType()});

}

OneHotOp OneHotOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange inputs, ::llvm::ArrayRef<bool> inverted) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(inputs)>(inputs), std::forward<decltype(inverted)>(inverted));
  auto __res__ = ::llvm::dyn_cast<OneHotOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

OneHotOp OneHotOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange inputs, ::llvm::ArrayRef<bool> inverted) {
  return create(builder, builder.getLoc(), std::forward<decltype(inputs)>(inputs), std::forward<decltype(inverted)>(inverted));
}

void OneHotOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  odsState.addTypes({operands[0].getType()});

}

OneHotOp OneHotOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<OneHotOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

OneHotOp OneHotOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void OneHotOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  odsState.addTypes({operands[0].getType()});

}

OneHotOp OneHotOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<OneHotOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

OneHotOp OneHotOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult OneHotOp::verifyInvariantsImpl() {
  auto tblgen_inverted = getProperties().inverted; (void)tblgen_inverted;
  if (!tblgen_inverted) return emitOpError("requires attribute 'inverted'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Synth1(*this, tblgen_inverted, "inverted")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Synth1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Synth2(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  if (!((getOperation()->getNumOperands() == 3)))
    return emitOpError("failed to verify that requires exactly three operands");
  if (!((getInverted().size() == 3)))
    return emitOpError("failed to verify that requires exactly three inversion flags");
  return ::mlir::success();
}

::llvm::LogicalResult OneHotOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult OneHotOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::llvm::SmallVector<::mlir::OpAsmParser::UnresolvedOperand, 4> inputsOperands;
  ::llvm::SMLoc inputsOperandsLoc;
  (void)inputsOperandsLoc;
  ::mlir::Type resultRawType{};
  ::llvm::ArrayRef<::mlir::Type> resultTypes(&resultRawType, 1);
  ::mlir::DenseBoolArrayAttr invertedAttr;
  {
    inputsOperandsLoc = parser.getCurrentLocation();
    auto odsResult = parseVariadicInvertibleOperands(parser, inputsOperands, resultRawType, invertedAttr, result.attributes);
    if (odsResult) return ::mlir::failure();
    result.getOrAddProperties<OneHotOp::Properties>().inverted = invertedAttr;
  }
  result.addTypes(resultTypes);
  if (parser.resolveOperands(inputsOperands, resultTypes[0], inputsOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void OneHotOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  printVariadicInvertibleOperands(_odsPrinter, *this, getInputs(), getResult().getType(), getInvertedAttr(), getOperation()->getAttrDictionary());
}

void OneHotOp::getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects) {
}

bool OneHotOp::areInputsPermutationInvariant() {
  return true;
}
bool OneHotOp::supportsNumInputs(unsigned numInputs) {
  return numInputs == 3;
}
int64_t OneHotOp::getLogicDepthCost() { return 1; }
std::optional<uint64_t> OneHotOp::getLogicAreaCost() {
  int64_t bitWidth = hw::getBitWidth(getType());
  if (bitWidth < 0)
    return std::nullopt;
  return static_cast<uint64_t>(bitWidth);
}
::llvm::KnownBits OneHotOp::computeKnownBits(
    ::llvm::function_ref<const ::llvm::KnownBits &(unsigned)>
        getInputKnownBits) {
  auto a = applyInputInversion(getInputKnownBits(0), isInverted(0));
  auto b = applyInputInversion(getInputKnownBits(1), isInverted(1));
  auto c = applyInputInversion(getInputKnownBits(2), isInverted(2));
  return evaluateOneHotLogic(a, b, c);
}
::llvm::APInt OneHotOp::evaluateBooleanLogicWithoutInversion(
    ::llvm::ArrayRef<::llvm::APInt> inputs) {
  assert(inputs.size() == 3 && "expected exactly three inputs");
  return evaluateOneHotLogic(inputs[0], inputs[1], inputs[2]);
}

} // namespace circt::synth
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::synth::OneHotOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::synth::detail::OneHotOpGenericAdaptorBase::Properties)

namespace circt::synth {


//===----------------------------------------------------------------------===//
// ::circt::synth::XorInverterOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

XorInverterOpGenericAdaptorBase::XorInverterOpGenericAdaptorBase(XorInverterOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

std::pair<unsigned, unsigned> XorInverterOpGenericAdaptorBase::getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
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

::llvm::ArrayRef<bool> XorInverterOpGenericAdaptorBase::getInverted() {
  auto attr = getInvertedAttr();
  return attr;
}


} // namespace detail
XorInverterOpAdaptor::XorInverterOpAdaptor(XorInverterOp op) : XorInverterOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult XorInverterOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_inverted = getProperties().inverted; (void)tblgen_inverted;
  if (!tblgen_inverted) return emitError(loc, "'synth.xor_inv' op requires attribute 'inverted'");

  if (tblgen_inverted && !((::llvm::isa<::mlir::DenseBoolArrayAttr>(tblgen_inverted))))
    return emitError(loc, "'synth.xor_inv' op attribute 'inverted' failed to satisfy constraint: i1 dense array attribute");
  return ::mlir::success();
}

std::pair<unsigned, unsigned> XorInverterOp::getODSOperandIndexAndLength(unsigned index) {
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

::mlir::MutableOperandRange XorInverterOp::getInputsMutable() {
  auto range = getODSOperandIndexAndLength(0);
  auto mutableRange = ::mlir::MutableOperandRange(getOperation(), range.first, range.second);
  return mutableRange;
}

::llvm::LogicalResult XorInverterOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.inverted;
       auto attr = dict.get("inverted");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `inverted` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  return ::mlir::success();
}

::mlir::Attribute XorInverterOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.inverted;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("inverted",
                                       propStorage));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code XorInverterOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.inverted.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> XorInverterOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "inverted")
      return prop.inverted;
  return std::nullopt;
}

void XorInverterOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "inverted") {
       prop.inverted = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.inverted)>>(value);
       return;
    }
}

void XorInverterOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.inverted) attrs.append("inverted", prop.inverted);
}

::llvm::LogicalResult XorInverterOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getInvertedAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Synth1(attr, "inverted", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult XorInverterOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.inverted)))
    return ::mlir::failure();
  return ::mlir::success();
}

void XorInverterOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.inverted);
}

::llvm::ArrayRef<bool> XorInverterOp::getInverted() {
  auto attr = getInvertedAttr();
  return attr;
}

void XorInverterOp::setInverted(::llvm::ArrayRef<bool> attrValue) {
  getProperties().inverted = ::mlir::Builder((*this)->getContext()).getDenseBoolArrayAttr(attrValue);
}

void XorInverterOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value input, bool invert) {
      SmallVector<bool> inverted {invert};
      return build(odsBuilder, odsState, {input}, inverted);
    
}

XorInverterOp XorInverterOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, Value input, bool invert) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(input)>(input), std::forward<decltype(invert)>(invert));
  auto __res__ = ::llvm::dyn_cast<XorInverterOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

XorInverterOp XorInverterOp::create(::mlir::ImplicitLocOpBuilder &builder, Value input, bool invert) {
  return create(builder, builder.getLoc(), std::forward<decltype(input)>(input), std::forward<decltype(invert)>(invert));
}

void XorInverterOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value lhs, Value rhs, bool invertLhs, bool invertRhs) {
      SmallVector<bool> inverted {invertLhs, invertRhs};
      return build(odsBuilder, odsState, {lhs, rhs}, inverted);
    
}

XorInverterOp XorInverterOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, Value lhs, Value rhs, bool invertLhs, bool invertRhs) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(lhs)>(lhs), std::forward<decltype(rhs)>(rhs), std::forward<decltype(invertLhs)>(invertLhs), std::forward<decltype(invertRhs)>(invertRhs));
  auto __res__ = ::llvm::dyn_cast<XorInverterOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

XorInverterOp XorInverterOp::create(::mlir::ImplicitLocOpBuilder &builder, Value lhs, Value rhs, bool invertLhs, bool invertRhs) {
  return create(builder, builder.getLoc(), std::forward<decltype(lhs)>(lhs), std::forward<decltype(rhs)>(rhs), std::forward<decltype(invertLhs)>(invertLhs), std::forward<decltype(invertRhs)>(invertRhs));
}

void XorInverterOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ArrayRef<std::pair<Value, bool>> operands) {
      SmallVector<Value> values;
      SmallVector<bool> inverts;
      for (auto &[val, inv] : operands) {
        values.push_back(val);
        inverts.push_back(inv);
      }
      return build(odsBuilder, odsState, values, inverts);
    
}

XorInverterOp XorInverterOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ArrayRef<std::pair<Value, bool>> operands) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands));
  auto __res__ = ::llvm::dyn_cast<XorInverterOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

XorInverterOp XorInverterOp::create(::mlir::ImplicitLocOpBuilder &builder, ArrayRef<std::pair<Value, bool>> operands) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands));
}

void XorInverterOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::ValueRange inputs, ::mlir::DenseBoolArrayAttr inverted) {
  odsState.addOperands(inputs);
  odsState.getOrAddProperties<Properties>().inverted = inverted;
  odsState.addTypes(result);
}

XorInverterOp XorInverterOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::ValueRange inputs, ::mlir::DenseBoolArrayAttr inverted) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(result)>(result), std::forward<decltype(inputs)>(inputs), std::forward<decltype(inverted)>(inverted));
  auto __res__ = ::llvm::dyn_cast<XorInverterOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

XorInverterOp XorInverterOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::ValueRange inputs, ::mlir::DenseBoolArrayAttr inverted) {
  return create(builder, builder.getLoc(), std::forward<decltype(result)>(result), std::forward<decltype(inputs)>(inputs), std::forward<decltype(inverted)>(inverted));
}

void XorInverterOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange inputs, ::mlir::DenseBoolArrayAttr inverted) {
  odsState.addOperands(inputs);
  odsState.getOrAddProperties<Properties>().inverted = inverted;
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

XorInverterOp XorInverterOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange inputs, ::mlir::DenseBoolArrayAttr inverted) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(inputs)>(inputs), std::forward<decltype(inverted)>(inverted));
  auto __res__ = ::llvm::dyn_cast<XorInverterOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

XorInverterOp XorInverterOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange inputs, ::mlir::DenseBoolArrayAttr inverted) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(inputs)>(inputs), std::forward<decltype(inverted)>(inverted));
}

void XorInverterOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::ValueRange inputs, ::llvm::ArrayRef<bool> inverted) {
  odsState.addOperands(inputs);
  odsState.getOrAddProperties<Properties>().inverted = odsBuilder.getDenseBoolArrayAttr(inverted);
  odsState.addTypes(result);
}

XorInverterOp XorInverterOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::ValueRange inputs, ::llvm::ArrayRef<bool> inverted) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(result)>(result), std::forward<decltype(inputs)>(inputs), std::forward<decltype(inverted)>(inverted));
  auto __res__ = ::llvm::dyn_cast<XorInverterOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

XorInverterOp XorInverterOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::ValueRange inputs, ::llvm::ArrayRef<bool> inverted) {
  return create(builder, builder.getLoc(), std::forward<decltype(result)>(result), std::forward<decltype(inputs)>(inputs), std::forward<decltype(inverted)>(inverted));
}

void XorInverterOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange inputs, ::llvm::ArrayRef<bool> inverted) {
  odsState.addOperands(inputs);
  odsState.getOrAddProperties<Properties>().inverted = odsBuilder.getDenseBoolArrayAttr(inverted);
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

XorInverterOp XorInverterOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange inputs, ::llvm::ArrayRef<bool> inverted) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(inputs)>(inputs), std::forward<decltype(inverted)>(inverted));
  auto __res__ = ::llvm::dyn_cast<XorInverterOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

XorInverterOp XorInverterOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange inputs, ::llvm::ArrayRef<bool> inverted) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(inputs)>(inputs), std::forward<decltype(inverted)>(inverted));
}

void XorInverterOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<XorInverterOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

XorInverterOp XorInverterOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<XorInverterOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

XorInverterOp XorInverterOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void XorInverterOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

XorInverterOp XorInverterOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<XorInverterOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

XorInverterOp XorInverterOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

void XorInverterOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange inputs, ::mlir::DenseBoolArrayAttr inverted) {
  odsState.addOperands(inputs);
  odsState.getOrAddProperties<Properties>().inverted = inverted;
  odsState.addTypes({inputs.front().getType()});

}

XorInverterOp XorInverterOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange inputs, ::mlir::DenseBoolArrayAttr inverted) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(inputs)>(inputs), std::forward<decltype(inverted)>(inverted));
  auto __res__ = ::llvm::dyn_cast<XorInverterOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

XorInverterOp XorInverterOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange inputs, ::mlir::DenseBoolArrayAttr inverted) {
  return create(builder, builder.getLoc(), std::forward<decltype(inputs)>(inputs), std::forward<decltype(inverted)>(inverted));
}

void XorInverterOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange inputs, ::llvm::ArrayRef<bool> inverted) {
  odsState.addOperands(inputs);
  odsState.getOrAddProperties<Properties>().inverted = odsBuilder.getDenseBoolArrayAttr(inverted);
  odsState.addTypes({inputs.front().getType()});

}

XorInverterOp XorInverterOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange inputs, ::llvm::ArrayRef<bool> inverted) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(inputs)>(inputs), std::forward<decltype(inverted)>(inverted));
  auto __res__ = ::llvm::dyn_cast<XorInverterOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

XorInverterOp XorInverterOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange inputs, ::llvm::ArrayRef<bool> inverted) {
  return create(builder, builder.getLoc(), std::forward<decltype(inputs)>(inputs), std::forward<decltype(inverted)>(inverted));
}

void XorInverterOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  odsState.addTypes({operands[0].getType()});

}

XorInverterOp XorInverterOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<XorInverterOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

XorInverterOp XorInverterOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void XorInverterOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  odsState.addTypes({operands[0].getType()});

}

XorInverterOp XorInverterOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<XorInverterOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

XorInverterOp XorInverterOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult XorInverterOp::verifyInvariantsImpl() {
  auto tblgen_inverted = getProperties().inverted; (void)tblgen_inverted;
  if (!tblgen_inverted) return emitOpError("requires attribute 'inverted'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Synth1(*this, tblgen_inverted, "inverted")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Synth1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Synth2(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult XorInverterOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

void XorInverterOp::getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context) {
  results.add(canonicalize);
}

::mlir::ParseResult XorInverterOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::llvm::SmallVector<::mlir::OpAsmParser::UnresolvedOperand, 4> inputsOperands;
  ::llvm::SMLoc inputsOperandsLoc;
  (void)inputsOperandsLoc;
  ::mlir::Type resultRawType{};
  ::llvm::ArrayRef<::mlir::Type> resultTypes(&resultRawType, 1);
  ::mlir::DenseBoolArrayAttr invertedAttr;
  {
    inputsOperandsLoc = parser.getCurrentLocation();
    auto odsResult = parseVariadicInvertibleOperands(parser, inputsOperands, resultRawType, invertedAttr, result.attributes);
    if (odsResult) return ::mlir::failure();
    result.getOrAddProperties<XorInverterOp::Properties>().inverted = invertedAttr;
  }
  result.addTypes(resultTypes);
  if (parser.resolveOperands(inputsOperands, resultTypes[0], inputsOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void XorInverterOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  printVariadicInvertibleOperands(_odsPrinter, *this, getInputs(), getResult().getType(), getInvertedAttr(), getOperation()->getAttrDictionary());
}

void XorInverterOp::getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects) {
}


} // namespace circt::synth
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::synth::XorInverterOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::synth::detail::XorInverterOpGenericAdaptorBase::Properties)


#endif // GET_OP_CLASSES

