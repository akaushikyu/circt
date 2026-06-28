/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Op Definitions                                                             *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: Debug.td                                                             *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

#ifdef GET_OP_LIST
#undef GET_OP_LIST

circt::debug::ArrayOp,
circt::debug::EnumOp,
circt::debug::ScopeOp,
circt::debug::StructOp,
circt::debug::ValueOp,
circt::debug::VariableOp
#endif // GET_OP_LIST

#ifdef GET_OP_CLASSES
#undef GET_OP_CLASSES


//===----------------------------------------------------------------------===//
// Local Utility Method Definitions
//===----------------------------------------------------------------------===//


static ::llvm::LogicalResult __mlir_ods_local_type_constraint_Debug1(
    ::mlir::Operation *op, ::mlir::Type type, ::llvm::StringRef valueKind,
    unsigned valueIndex) {
  if (!(!((::llvm::isa<::mlir::TokenType>(type))))) {
    return op->emitOpError(valueKind) << " #" << valueIndex
        << " must be variadic of any non-token type, but got " << type;
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_type_constraint_Debug2(
    ::mlir::Operation *op, ::mlir::Type type, ::llvm::StringRef valueKind,
    unsigned valueIndex) {
  if (!((::llvm::isa<circt::debug::ArrayType>(type)))) {
    return op->emitOpError(valueKind) << " #" << valueIndex
        << " must be debug array aggregate, but got " << type;
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_type_constraint_Debug3(
    ::mlir::Operation *op, ::mlir::Type type, ::llvm::StringRef valueKind,
    unsigned valueIndex) {
  if (!(!((::llvm::isa<::mlir::TokenType>(type))))) {
    return op->emitOpError(valueKind) << " #" << valueIndex
        << " must be any non-token type, but got " << type;
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_type_constraint_Debug4(
    ::mlir::Operation *op, ::mlir::Type type, ::llvm::StringRef valueKind,
    unsigned valueIndex) {
  if (!((::llvm::isa<circt::debug::EnumType>(type)))) {
    return op->emitOpError(valueKind) << " #" << valueIndex
        << " must be debug enum value, but got " << type;
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_type_constraint_Debug5(
    ::mlir::Operation *op, ::mlir::Type type, ::llvm::StringRef valueKind,
    unsigned valueIndex) {
  if (!((::llvm::isa<circt::debug::ScopeType>(type)))) {
    return op->emitOpError(valueKind) << " #" << valueIndex
        << " must be debug scope, but got " << type;
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_type_constraint_Debug6(
    ::mlir::Operation *op, ::mlir::Type type, ::llvm::StringRef valueKind,
    unsigned valueIndex) {
  if (!((::llvm::isa<circt::debug::StructType>(type)))) {
    return op->emitOpError(valueKind) << " #" << valueIndex
        << " must be debug struct aggregate, but got " << type;
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_type_constraint_Debug7(
    ::mlir::Operation *op, ::mlir::Type type, ::llvm::StringRef valueKind,
    unsigned valueIndex) {
  if (!((::llvm::isa<circt::debug::ValueType>(type)))) {
    return op->emitOpError(valueKind) << " #" << valueIndex
        << " must be debug value annotated with source-language metadata, but got " << type;
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_Debug1(
    ::mlir::Attribute attr, ::llvm::StringRef attrName, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  if (attr && !((::llvm::isa<::mlir::StringAttr>(attr))))
    return emitError() << "attribute '" << attrName
        << "' failed to satisfy constraint: string attribute";
  return ::mlir::success();
}
static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_Debug1(
    ::mlir::Operation *op, ::mlir::Attribute attr, ::llvm::StringRef attrName) {
  return __mlir_ods_local_attr_constraint_Debug1(attr, attrName, [op]() {
    return op->emitOpError();
  });
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_Debug2(
    ::mlir::Attribute attr, ::llvm::StringRef attrName, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  if (attr && !((::llvm::isa<::mlir::DictionaryAttr>(attr))))
    return emitError() << "attribute '" << attrName
        << "' failed to satisfy constraint: dictionary of named attribute values";
  return ::mlir::success();
}
static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_Debug2(
    ::mlir::Operation *op, ::mlir::Attribute attr, ::llvm::StringRef attrName) {
  return __mlir_ods_local_attr_constraint_Debug2(attr, attrName, [op]() {
    return op->emitOpError();
  });
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_Debug3(
    ::mlir::Attribute attr, ::llvm::StringRef attrName, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  if (attr && !(((::llvm::isa<::mlir::ArrayAttr>(attr))) && (::llvm::all_of(::llvm::cast<::mlir::ArrayAttr>(attr), [&](::mlir::Attribute attr) { return attr && ((::llvm::isa<::mlir::StringAttr>(attr))); }))))
    return emitError() << "attribute '" << attrName
        << "' failed to satisfy constraint: string array attribute";
  return ::mlir::success();
}
static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_Debug3(
    ::mlir::Operation *op, ::mlir::Attribute attr, ::llvm::StringRef attrName) {
  return __mlir_ods_local_attr_constraint_Debug3(attr, attrName, [op]() {
    return op->emitOpError();
  });
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_Debug4(
    ::mlir::Attribute attr, ::llvm::StringRef attrName, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  if (attr && !((::llvm::isa<::mlir::ArrayAttr>(attr))))
    return emitError() << "attribute '" << attrName
        << "' failed to satisfy constraint: array attribute";
  return ::mlir::success();
}
static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_Debug4(
    ::mlir::Operation *op, ::mlir::Attribute attr, ::llvm::StringRef attrName) {
  return __mlir_ods_local_attr_constraint_Debug4(attr, attrName, [op]() {
    return op->emitOpError();
  });
}
namespace circt::debug {


//===----------------------------------------------------------------------===//
// circt::debug::ArrayOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

ArrayOpGenericAdaptorBase::ArrayOpGenericAdaptorBase(ArrayOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

std::pair<unsigned, unsigned> ArrayOpGenericAdaptorBase::getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
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
ArrayOpAdaptor::ArrayOpAdaptor(ArrayOp op) : ArrayOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult ArrayOpAdaptor::verify(::mlir::Location loc) {
  return ::mlir::success();
}

std::pair<unsigned, unsigned> ArrayOp::getODSOperandIndexAndLength(unsigned index) {
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

::mlir::MutableOperandRange ArrayOp::getElementsMutable() {
  auto range = getODSOperandIndexAndLength(0);
  auto mutableRange = ::mlir::MutableOperandRange(getOperation(), range.first, range.second);
  return mutableRange;
}

::llvm::LogicalResult ArrayOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }
      return ::mlir::success();
}

::mlir::Attribute ArrayOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code ArrayOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine();
}

std::optional<mlir::Attribute> ArrayOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
  return std::nullopt;
}

void ArrayOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
}

void ArrayOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
}

::llvm::LogicalResult ArrayOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    return ::mlir::success();
}

void ArrayOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::ValueRange elements) {
  odsState.addOperands(elements);
  odsState.addTypes(result);
}

ArrayOp ArrayOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::ValueRange elements) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(result)>(result), std::forward<decltype(elements)>(elements));
  auto __res__ = ::llvm::dyn_cast<ArrayOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ArrayOp ArrayOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::ValueRange elements) {
  return create(builder, builder.getLoc(), std::forward<decltype(result)>(result), std::forward<decltype(elements)>(elements));
}

void ArrayOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

ArrayOp ArrayOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<ArrayOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ArrayOp ArrayOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void ArrayOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);

  ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
  if (::mlir::succeeded(ArrayOp::inferReturnTypes(odsBuilder.getContext(),
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

ArrayOp ArrayOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<ArrayOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ArrayOp ArrayOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void ArrayOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

ArrayOp ArrayOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<ArrayOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ArrayOp ArrayOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

void ArrayOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties &>(properties));
  odsState.addAttributes(discardableAttributes);

  ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
  if (::mlir::succeeded(ArrayOp::inferReturnTypes(odsBuilder.getContext(),
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

ArrayOp ArrayOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<ArrayOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ArrayOp ArrayOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult ArrayOp::verifyInvariantsImpl() {
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Debug1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Debug2(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult ArrayOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::llvm::LogicalResult ArrayOp::inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::PropertyRef properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes) {
  inferredReturnTypes.resize(1);
  ::mlir::Builder odsBuilder(context);
  ::mlir::Type odsInferredType0 = odsBuilder.getType<circt::debug::ArrayType>();
  inferredReturnTypes[0] = odsInferredType0;
  return ::mlir::success();
}

::llvm::LogicalResult ArrayOp::setPropertiesFromParsedAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
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

  for (::mlir::NamedAttribute attr : dict) {
    if (!usedKeys.contains(attr.getName()))
      return emitError() << "unknown key '" << attr.getName() <<
          "' when parsing properties dictionary";
  }
  return ::mlir::success();
}

void ArrayOp::getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects) {
}


} // namespace circt::debug
MLIR_DEFINE_EXPLICIT_TYPE_ID(circt::debug::ArrayOp)

namespace circt::debug {


//===----------------------------------------------------------------------===//
// circt::debug::EnumOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

EnumOpGenericAdaptorBase::EnumOpGenericAdaptorBase(EnumOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::llvm::StringRef EnumOpGenericAdaptorBase::getEnumTypeName() {
  auto attr = getEnumTypeNameAttr();
  return attr.getValue();
}

::mlir::DictionaryAttr EnumOpGenericAdaptorBase::getVariantsMap() {
  auto attr = getVariantsMapAttr();
  return attr;
}

::std::optional< ::llvm::StringRef > EnumOpGenericAdaptorBase::getFqn() {
  auto attr = getFqnAttr();
  return attr ? ::std::optional< ::llvm::StringRef >(attr.getValue()) : (::std::nullopt);
}


} // namespace detail
EnumOpAdaptor::EnumOpAdaptor(EnumOp op) : EnumOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult EnumOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_enumTypeName = getProperties().enumTypeName; (void)tblgen_enumTypeName;
  if (!tblgen_enumTypeName) return emitError(loc, "'dbg.enum' op requires attribute 'enumTypeName'");
  auto tblgen_fqn = getProperties().fqn; (void)tblgen_fqn;
  auto tblgen_variantsMap = getProperties().variantsMap; (void)tblgen_variantsMap;
  if (!tblgen_variantsMap) return emitError(loc, "'dbg.enum' op requires attribute 'variantsMap'");

  if (tblgen_enumTypeName && !((::llvm::isa<::mlir::StringAttr>(tblgen_enumTypeName))))
    return emitError(loc, "'dbg.enum' op attribute 'enumTypeName' failed to satisfy constraint: string attribute");

  if (tblgen_variantsMap && !((::llvm::isa<::mlir::DictionaryAttr>(tblgen_variantsMap))))
    return emitError(loc, "'dbg.enum' op attribute 'variantsMap' failed to satisfy constraint: dictionary of named attribute values");

  if (tblgen_fqn && !((::llvm::isa<::mlir::StringAttr>(tblgen_fqn))))
    return emitError(loc, "'dbg.enum' op attribute 'fqn' failed to satisfy constraint: string attribute");
  return ::mlir::success();
}

::llvm::LogicalResult EnumOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.enumTypeName;
       auto attr = dict.get("enumTypeName");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `enumTypeName` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.fqn;
       auto attr = dict.get("fqn");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `fqn` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.variantsMap;
       auto attr = dict.get("variantsMap");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `variantsMap` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  return ::mlir::success();
}

::mlir::Attribute EnumOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.enumTypeName;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("enumTypeName",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.fqn;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("fqn",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.variantsMap;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("variantsMap",
                                       propStorage));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code EnumOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.enumTypeName.getAsOpaquePointer()), 
    llvm::hash_value(prop.fqn.getAsOpaquePointer()), 
    llvm::hash_value(prop.variantsMap.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> EnumOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "enumTypeName")
      return prop.enumTypeName;

    if (name == "fqn")
      return prop.fqn;

    if (name == "variantsMap")
      return prop.variantsMap;
  return std::nullopt;
}

void EnumOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "enumTypeName") {
       prop.enumTypeName = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.enumTypeName)>>(value);
       return;
    }

    if (name == "fqn") {
       prop.fqn = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.fqn)>>(value);
       return;
    }

    if (name == "variantsMap") {
       prop.variantsMap = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.variantsMap)>>(value);
       return;
    }
}

void EnumOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.enumTypeName) attrs.append("enumTypeName", prop.enumTypeName);

    if (prop.fqn) attrs.append("fqn", prop.fqn);

    if (prop.variantsMap) attrs.append("variantsMap", prop.variantsMap);
}

::llvm::LogicalResult EnumOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getEnumTypeNameAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Debug1(attr, "enumTypeName", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getFqnAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Debug1(attr, "fqn", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getVariantsMapAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Debug2(attr, "variantsMap", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult EnumOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.enumTypeName)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readOptionalAttribute(prop.fqn)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readAttribute(prop.variantsMap)))
    return ::mlir::failure();
  return ::mlir::success();
}

void EnumOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.enumTypeName);

  writer.writeOptionalAttribute(prop.fqn);
  writer.writeAttribute(prop.variantsMap);
}

::llvm::StringRef EnumOp::getEnumTypeName() {
  auto attr = getEnumTypeNameAttr();
  return attr.getValue();
}

::mlir::DictionaryAttr EnumOp::getVariantsMap() {
  auto attr = getVariantsMapAttr();
  return attr;
}

::std::optional< ::llvm::StringRef > EnumOp::getFqn() {
  auto attr = getFqnAttr();
  return attr ? ::std::optional< ::llvm::StringRef >(attr.getValue()) : (::std::nullopt);
}

void EnumOp::setEnumTypeName(::llvm::StringRef attrValue) {
  getProperties().enumTypeName = ::mlir::Builder((*this)->getContext()).getStringAttr(attrValue);
}

void EnumOp::setFqn(::std::optional<::llvm::StringRef> attrValue) {
    auto &odsProp = getProperties().fqn;
    if (attrValue)
      odsProp = ::mlir::Builder((*this)->getContext()).getStringAttr(*attrValue);
    else
      odsProp = nullptr;
}

void EnumOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value value, ::mlir::StringAttr enumTypeName, ::mlir::DictionaryAttr variantsMap, /*optional*/::mlir::StringAttr fqn) {
  odsState.addOperands(value);
  odsState.getOrAddProperties<Properties>().enumTypeName = enumTypeName;
  odsState.getOrAddProperties<Properties>().variantsMap = variantsMap;
  if (fqn) {
    odsState.getOrAddProperties<Properties>().fqn = fqn;
  }
  odsState.addTypes(result);
}

EnumOp EnumOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value value, ::mlir::StringAttr enumTypeName, ::mlir::DictionaryAttr variantsMap, /*optional*/::mlir::StringAttr fqn) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(result)>(result), std::forward<decltype(value)>(value), std::forward<decltype(enumTypeName)>(enumTypeName), std::forward<decltype(variantsMap)>(variantsMap), std::forward<decltype(fqn)>(fqn));
  auto __res__ = ::llvm::dyn_cast<EnumOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

EnumOp EnumOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value value, ::mlir::StringAttr enumTypeName, ::mlir::DictionaryAttr variantsMap, /*optional*/::mlir::StringAttr fqn) {
  return create(builder, builder.getLoc(), std::forward<decltype(result)>(result), std::forward<decltype(value)>(value), std::forward<decltype(enumTypeName)>(enumTypeName), std::forward<decltype(variantsMap)>(variantsMap), std::forward<decltype(fqn)>(fqn));
}

void EnumOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value value, ::mlir::StringAttr enumTypeName, ::mlir::DictionaryAttr variantsMap, /*optional*/::mlir::StringAttr fqn) {
  odsState.addOperands(value);
  odsState.getOrAddProperties<Properties>().enumTypeName = enumTypeName;
  odsState.getOrAddProperties<Properties>().variantsMap = variantsMap;
  if (fqn) {
    odsState.getOrAddProperties<Properties>().fqn = fqn;
  }

        ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
        if (::mlir::succeeded(EnumOp::inferReturnTypes(odsBuilder.getContext(),
                      odsState.location, odsState.operands,
                      odsState.attributes.getDictionary(odsState.getContext()),
                      odsState.getRawProperties(),
                      odsState.regions, inferredReturnTypes)))
          odsState.addTypes(inferredReturnTypes);
        else
          ::mlir::detail::reportFatalInferReturnTypesError(odsState);
        
}

EnumOp EnumOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value value, ::mlir::StringAttr enumTypeName, ::mlir::DictionaryAttr variantsMap, /*optional*/::mlir::StringAttr fqn) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(value)>(value), std::forward<decltype(enumTypeName)>(enumTypeName), std::forward<decltype(variantsMap)>(variantsMap), std::forward<decltype(fqn)>(fqn));
  auto __res__ = ::llvm::dyn_cast<EnumOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

EnumOp EnumOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value value, ::mlir::StringAttr enumTypeName, ::mlir::DictionaryAttr variantsMap, /*optional*/::mlir::StringAttr fqn) {
  return create(builder, builder.getLoc(), std::forward<decltype(value)>(value), std::forward<decltype(enumTypeName)>(enumTypeName), std::forward<decltype(variantsMap)>(variantsMap), std::forward<decltype(fqn)>(fqn));
}

void EnumOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value value, ::mlir::StringAttr enumTypeName, ::mlir::DictionaryAttr variantsMap, /*optional*/::mlir::StringAttr fqn) {
  odsState.addOperands(value);
  odsState.getOrAddProperties<Properties>().enumTypeName = enumTypeName;
  odsState.getOrAddProperties<Properties>().variantsMap = variantsMap;
  if (fqn) {
    odsState.getOrAddProperties<Properties>().fqn = fqn;
  }
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

EnumOp EnumOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value value, ::mlir::StringAttr enumTypeName, ::mlir::DictionaryAttr variantsMap, /*optional*/::mlir::StringAttr fqn) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(value)>(value), std::forward<decltype(enumTypeName)>(enumTypeName), std::forward<decltype(variantsMap)>(variantsMap), std::forward<decltype(fqn)>(fqn));
  auto __res__ = ::llvm::dyn_cast<EnumOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

EnumOp EnumOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value value, ::mlir::StringAttr enumTypeName, ::mlir::DictionaryAttr variantsMap, /*optional*/::mlir::StringAttr fqn) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(value)>(value), std::forward<decltype(enumTypeName)>(enumTypeName), std::forward<decltype(variantsMap)>(variantsMap), std::forward<decltype(fqn)>(fqn));
}

void EnumOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value value, ::llvm::StringRef enumTypeName, ::mlir::DictionaryAttr variantsMap, /*optional*/::mlir::StringAttr fqn) {
  odsState.addOperands(value);
  odsState.getOrAddProperties<Properties>().enumTypeName = odsBuilder.getStringAttr(enumTypeName);
  odsState.getOrAddProperties<Properties>().variantsMap = variantsMap;
  if (fqn) {
    odsState.getOrAddProperties<Properties>().fqn = fqn;
  }
  odsState.addTypes(result);
}

EnumOp EnumOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value value, ::llvm::StringRef enumTypeName, ::mlir::DictionaryAttr variantsMap, /*optional*/::mlir::StringAttr fqn) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(result)>(result), std::forward<decltype(value)>(value), std::forward<decltype(enumTypeName)>(enumTypeName), std::forward<decltype(variantsMap)>(variantsMap), std::forward<decltype(fqn)>(fqn));
  auto __res__ = ::llvm::dyn_cast<EnumOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

EnumOp EnumOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value value, ::llvm::StringRef enumTypeName, ::mlir::DictionaryAttr variantsMap, /*optional*/::mlir::StringAttr fqn) {
  return create(builder, builder.getLoc(), std::forward<decltype(result)>(result), std::forward<decltype(value)>(value), std::forward<decltype(enumTypeName)>(enumTypeName), std::forward<decltype(variantsMap)>(variantsMap), std::forward<decltype(fqn)>(fqn));
}

void EnumOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value value, ::llvm::StringRef enumTypeName, ::mlir::DictionaryAttr variantsMap, /*optional*/::mlir::StringAttr fqn) {
  odsState.addOperands(value);
  odsState.getOrAddProperties<Properties>().enumTypeName = odsBuilder.getStringAttr(enumTypeName);
  odsState.getOrAddProperties<Properties>().variantsMap = variantsMap;
  if (fqn) {
    odsState.getOrAddProperties<Properties>().fqn = fqn;
  }

        ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
        if (::mlir::succeeded(EnumOp::inferReturnTypes(odsBuilder.getContext(),
                      odsState.location, odsState.operands,
                      odsState.attributes.getDictionary(odsState.getContext()),
                      odsState.getRawProperties(),
                      odsState.regions, inferredReturnTypes)))
          odsState.addTypes(inferredReturnTypes);
        else
          ::mlir::detail::reportFatalInferReturnTypesError(odsState);
        
}

EnumOp EnumOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value value, ::llvm::StringRef enumTypeName, ::mlir::DictionaryAttr variantsMap, /*optional*/::mlir::StringAttr fqn) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(value)>(value), std::forward<decltype(enumTypeName)>(enumTypeName), std::forward<decltype(variantsMap)>(variantsMap), std::forward<decltype(fqn)>(fqn));
  auto __res__ = ::llvm::dyn_cast<EnumOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

EnumOp EnumOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value value, ::llvm::StringRef enumTypeName, ::mlir::DictionaryAttr variantsMap, /*optional*/::mlir::StringAttr fqn) {
  return create(builder, builder.getLoc(), std::forward<decltype(value)>(value), std::forward<decltype(enumTypeName)>(enumTypeName), std::forward<decltype(variantsMap)>(variantsMap), std::forward<decltype(fqn)>(fqn));
}

void EnumOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value value, ::llvm::StringRef enumTypeName, ::mlir::DictionaryAttr variantsMap, /*optional*/::mlir::StringAttr fqn) {
  odsState.addOperands(value);
  odsState.getOrAddProperties<Properties>().enumTypeName = odsBuilder.getStringAttr(enumTypeName);
  odsState.getOrAddProperties<Properties>().variantsMap = variantsMap;
  if (fqn) {
    odsState.getOrAddProperties<Properties>().fqn = fqn;
  }
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

EnumOp EnumOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value value, ::llvm::StringRef enumTypeName, ::mlir::DictionaryAttr variantsMap, /*optional*/::mlir::StringAttr fqn) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(value)>(value), std::forward<decltype(enumTypeName)>(enumTypeName), std::forward<decltype(variantsMap)>(variantsMap), std::forward<decltype(fqn)>(fqn));
  auto __res__ = ::llvm::dyn_cast<EnumOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

EnumOp EnumOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value value, ::llvm::StringRef enumTypeName, ::mlir::DictionaryAttr variantsMap, /*optional*/::mlir::StringAttr fqn) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(value)>(value), std::forward<decltype(enumTypeName)>(enumTypeName), std::forward<decltype(variantsMap)>(variantsMap), std::forward<decltype(fqn)>(fqn));
}

void EnumOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<EnumOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

EnumOp EnumOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<EnumOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

EnumOp EnumOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void EnumOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<EnumOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
  ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
  if (::mlir::succeeded(EnumOp::inferReturnTypes(odsBuilder.getContext(),
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

EnumOp EnumOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<EnumOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

EnumOp EnumOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void EnumOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

EnumOp EnumOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<EnumOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

EnumOp EnumOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

void EnumOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties &>(properties));
  odsState.addAttributes(discardableAttributes);

  ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
  if (::mlir::succeeded(EnumOp::inferReturnTypes(odsBuilder.getContext(),
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

EnumOp EnumOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<EnumOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

EnumOp EnumOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult EnumOp::verifyInvariantsImpl() {
  auto tblgen_enumTypeName = getProperties().enumTypeName; (void)tblgen_enumTypeName;
  if (!tblgen_enumTypeName) return emitOpError("requires attribute 'enumTypeName'");
  auto tblgen_fqn = getProperties().fqn; (void)tblgen_fqn;
  auto tblgen_variantsMap = getProperties().variantsMap; (void)tblgen_variantsMap;
  if (!tblgen_variantsMap) return emitOpError("requires attribute 'variantsMap'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Debug1(*this, tblgen_enumTypeName, "enumTypeName")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Debug2(*this, tblgen_variantsMap, "variantsMap")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Debug1(*this, tblgen_fqn, "fqn")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Debug3(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Debug4(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult EnumOp::verifyInvariants() {
  if(::mlir::succeeded(verifyInvariantsImpl()) && ::mlir::succeeded(verify()))
    return ::mlir::success();
  return ::mlir::failure();
}

::llvm::LogicalResult EnumOp::inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::PropertyRef properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes) {
  inferredReturnTypes.resize(1);
  ::mlir::Builder odsBuilder(context);
  ::mlir::Type odsInferredType0 = odsBuilder.getType<circt::debug::EnumType>();
  inferredReturnTypes[0] = odsInferredType0;
  return ::mlir::success();
}

::mlir::ParseResult EnumOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::OpAsmParser::UnresolvedOperand valueRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> valueOperands(&valueRawOperand, 1);  ::llvm::SMLoc valueOperandsLoc;
  (void)valueOperandsLoc;
  ::mlir::StringAttr enumTypeNameAttr;
  ::mlir::DictionaryAttr variantsMapAttr;
  ::mlir::StringAttr fqnAttr;
  ::mlir::Type valueRawType{};
  ::llvm::ArrayRef<::mlir::Type> valueTypes(&valueRawType, 1);

  valueOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(valueRawOperand))
    return ::mlir::failure();
  if (parser.parseComma())
    return ::mlir::failure();

  if (parser.parseCustomAttributeWithFallback(enumTypeNameAttr, parser.getBuilder().getType<::mlir::NoneType>())) {
    return ::mlir::failure();
  }
  if (enumTypeNameAttr) result.getOrAddProperties<EnumOp::Properties>().enumTypeName = enumTypeNameAttr;
  if (parser.parseComma())
    return ::mlir::failure();

  if (parser.parseCustomAttributeWithFallback(variantsMapAttr, parser.getBuilder().getType<::mlir::NoneType>())) {
    return ::mlir::failure();
  }
  if (variantsMapAttr) result.getOrAddProperties<EnumOp::Properties>().variantsMap = variantsMapAttr;
  if (::mlir::succeeded(parser.parseOptionalKeyword("fqn"))) {

  if (parser.parseCustomAttributeWithFallback(fqnAttr, parser.getBuilder().getType<::mlir::NoneType>())) {
    return ::mlir::failure();
  }
  if (fqnAttr) result.getOrAddProperties<EnumOp::Properties>().fqn = fqnAttr;
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
    valueRawType = type;
  }
  ::mlir::Type odsBuildableType0 = parser.getBuilder().getType<circt::debug::EnumType>();
  result.addTypes(odsBuildableType0);
  if (parser.resolveOperands(valueOperands, valueTypes, valueOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void EnumOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter << getValue();
  _odsPrinter << ",";
  _odsPrinter << ' ';
  _odsPrinter.printAttributeWithoutType(getEnumTypeNameAttr());
  _odsPrinter << ",";
  _odsPrinter << ' ';
  _odsPrinter.printAttributeWithoutType(getVariantsMapAttr());
  if (getFqnAttr()) {
    _odsPrinter << ' ' << "fqn";
    _odsPrinter << ' ';
    _odsPrinter.printAttributeWithoutType(getFqnAttr());
  }
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("enumTypeName");
  elidedAttrs.push_back("variantsMap");
  elidedAttrs.push_back("fqn");
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
  {
    auto type = getValue().getType();
    if (auto validType = ::llvm::dyn_cast<::mlir::Type>(type))
      _odsPrinter.printStrippedAttrOrType(validType);
   else
     _odsPrinter << type;
  }
}

void EnumOp::getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects) {
}


} // namespace circt::debug
MLIR_DEFINE_EXPLICIT_TYPE_ID(circt::debug::EnumOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(circt::debug::detail::EnumOpGenericAdaptorBase::Properties)

namespace circt::debug {


//===----------------------------------------------------------------------===//
// circt::debug::ScopeOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

ScopeOpGenericAdaptorBase::ScopeOpGenericAdaptorBase(ScopeOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

std::pair<unsigned, unsigned> ScopeOpGenericAdaptorBase::getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
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

::llvm::StringRef ScopeOpGenericAdaptorBase::getInstanceName() {
  auto attr = getInstanceNameAttr();
  return attr.getValue();
}

::llvm::StringRef ScopeOpGenericAdaptorBase::getModuleName() {
  auto attr = getModuleNameAttr();
  return attr.getValue();
}


} // namespace detail
ScopeOpAdaptor::ScopeOpAdaptor(ScopeOp op) : ScopeOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult ScopeOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_instanceName = getProperties().instanceName; (void)tblgen_instanceName;
  if (!tblgen_instanceName) return emitError(loc, "'dbg.scope' op requires attribute 'instanceName'");
  auto tblgen_moduleName = getProperties().moduleName; (void)tblgen_moduleName;
  if (!tblgen_moduleName) return emitError(loc, "'dbg.scope' op requires attribute 'moduleName'");

  if (tblgen_instanceName && !((::llvm::isa<::mlir::StringAttr>(tblgen_instanceName))))
    return emitError(loc, "'dbg.scope' op attribute 'instanceName' failed to satisfy constraint: string attribute");

  if (tblgen_moduleName && !((::llvm::isa<::mlir::StringAttr>(tblgen_moduleName))))
    return emitError(loc, "'dbg.scope' op attribute 'moduleName' failed to satisfy constraint: string attribute");
  return ::mlir::success();
}

std::pair<unsigned, unsigned> ScopeOp::getODSOperandIndexAndLength(unsigned index) {
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

::mlir::MutableOperandRange ScopeOp::getScopeMutable() {
  auto range = getODSOperandIndexAndLength(0);
  auto mutableRange = ::mlir::MutableOperandRange(getOperation(), range.first, range.second);
  return mutableRange;
}

::llvm::LogicalResult ScopeOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.instanceName;
       auto attr = dict.get("instanceName");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `instanceName` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.moduleName;
       auto attr = dict.get("moduleName");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `moduleName` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  return ::mlir::success();
}

::mlir::Attribute ScopeOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.instanceName;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("instanceName",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.moduleName;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("moduleName",
                                       propStorage));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code ScopeOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.instanceName.getAsOpaquePointer()), 
    llvm::hash_value(prop.moduleName.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> ScopeOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "instanceName")
      return prop.instanceName;

    if (name == "moduleName")
      return prop.moduleName;
  return std::nullopt;
}

void ScopeOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "instanceName") {
       prop.instanceName = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.instanceName)>>(value);
       return;
    }

    if (name == "moduleName") {
       prop.moduleName = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.moduleName)>>(value);
       return;
    }
}

void ScopeOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.instanceName) attrs.append("instanceName", prop.instanceName);

    if (prop.moduleName) attrs.append("moduleName", prop.moduleName);
}

::llvm::LogicalResult ScopeOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getInstanceNameAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Debug1(attr, "instanceName", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getModuleNameAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Debug1(attr, "moduleName", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult ScopeOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.instanceName)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readAttribute(prop.moduleName)))
    return ::mlir::failure();
  return ::mlir::success();
}

void ScopeOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.instanceName);
  writer.writeAttribute(prop.moduleName);
}

::llvm::StringRef ScopeOp::getInstanceName() {
  auto attr = getInstanceNameAttr();
  return attr.getValue();
}

::llvm::StringRef ScopeOp::getModuleName() {
  auto attr = getModuleNameAttr();
  return attr.getValue();
}

void ScopeOp::setInstanceName(::llvm::StringRef attrValue) {
  getProperties().instanceName = ::mlir::Builder((*this)->getContext()).getStringAttr(attrValue);
}

void ScopeOp::setModuleName(::llvm::StringRef attrValue) {
  getProperties().moduleName = ::mlir::Builder((*this)->getContext()).getStringAttr(attrValue);
}

void ScopeOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::StringAttr instanceName, ::mlir::StringAttr moduleName, /*optional*/::mlir::Value scope) {
  if (scope)
    odsState.addOperands(scope);
  odsState.getOrAddProperties<Properties>().instanceName = instanceName;
  odsState.getOrAddProperties<Properties>().moduleName = moduleName;
  odsState.addTypes(result);
}

ScopeOp ScopeOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::StringAttr instanceName, ::mlir::StringAttr moduleName, /*optional*/::mlir::Value scope) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(result)>(result), std::forward<decltype(instanceName)>(instanceName), std::forward<decltype(moduleName)>(moduleName), std::forward<decltype(scope)>(scope));
  auto __res__ = ::llvm::dyn_cast<ScopeOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ScopeOp ScopeOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::StringAttr instanceName, ::mlir::StringAttr moduleName, /*optional*/::mlir::Value scope) {
  return create(builder, builder.getLoc(), std::forward<decltype(result)>(result), std::forward<decltype(instanceName)>(instanceName), std::forward<decltype(moduleName)>(moduleName), std::forward<decltype(scope)>(scope));
}

void ScopeOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::StringAttr instanceName, ::mlir::StringAttr moduleName, /*optional*/::mlir::Value scope) {
  if (scope)
    odsState.addOperands(scope);
  odsState.getOrAddProperties<Properties>().instanceName = instanceName;
  odsState.getOrAddProperties<Properties>().moduleName = moduleName;

        ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
        if (::mlir::succeeded(ScopeOp::inferReturnTypes(odsBuilder.getContext(),
                      odsState.location, odsState.operands,
                      odsState.attributes.getDictionary(odsState.getContext()),
                      odsState.getRawProperties(),
                      odsState.regions, inferredReturnTypes)))
          odsState.addTypes(inferredReturnTypes);
        else
          ::mlir::detail::reportFatalInferReturnTypesError(odsState);
        
}

ScopeOp ScopeOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::StringAttr instanceName, ::mlir::StringAttr moduleName, /*optional*/::mlir::Value scope) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(instanceName)>(instanceName), std::forward<decltype(moduleName)>(moduleName), std::forward<decltype(scope)>(scope));
  auto __res__ = ::llvm::dyn_cast<ScopeOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ScopeOp ScopeOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::StringAttr instanceName, ::mlir::StringAttr moduleName, /*optional*/::mlir::Value scope) {
  return create(builder, builder.getLoc(), std::forward<decltype(instanceName)>(instanceName), std::forward<decltype(moduleName)>(moduleName), std::forward<decltype(scope)>(scope));
}

void ScopeOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::StringAttr instanceName, ::mlir::StringAttr moduleName, /*optional*/::mlir::Value scope) {
  if (scope)
    odsState.addOperands(scope);
  odsState.getOrAddProperties<Properties>().instanceName = instanceName;
  odsState.getOrAddProperties<Properties>().moduleName = moduleName;
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

ScopeOp ScopeOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::StringAttr instanceName, ::mlir::StringAttr moduleName, /*optional*/::mlir::Value scope) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(instanceName)>(instanceName), std::forward<decltype(moduleName)>(moduleName), std::forward<decltype(scope)>(scope));
  auto __res__ = ::llvm::dyn_cast<ScopeOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ScopeOp ScopeOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::StringAttr instanceName, ::mlir::StringAttr moduleName, /*optional*/::mlir::Value scope) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(instanceName)>(instanceName), std::forward<decltype(moduleName)>(moduleName), std::forward<decltype(scope)>(scope));
}

void ScopeOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::llvm::StringRef instanceName, ::llvm::StringRef moduleName, /*optional*/::mlir::Value scope) {
  if (scope)
    odsState.addOperands(scope);
  odsState.getOrAddProperties<Properties>().instanceName = odsBuilder.getStringAttr(instanceName);
  odsState.getOrAddProperties<Properties>().moduleName = odsBuilder.getStringAttr(moduleName);
  odsState.addTypes(result);
}

ScopeOp ScopeOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::llvm::StringRef instanceName, ::llvm::StringRef moduleName, /*optional*/::mlir::Value scope) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(result)>(result), std::forward<decltype(instanceName)>(instanceName), std::forward<decltype(moduleName)>(moduleName), std::forward<decltype(scope)>(scope));
  auto __res__ = ::llvm::dyn_cast<ScopeOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ScopeOp ScopeOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::llvm::StringRef instanceName, ::llvm::StringRef moduleName, /*optional*/::mlir::Value scope) {
  return create(builder, builder.getLoc(), std::forward<decltype(result)>(result), std::forward<decltype(instanceName)>(instanceName), std::forward<decltype(moduleName)>(moduleName), std::forward<decltype(scope)>(scope));
}

void ScopeOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::llvm::StringRef instanceName, ::llvm::StringRef moduleName, /*optional*/::mlir::Value scope) {
  if (scope)
    odsState.addOperands(scope);
  odsState.getOrAddProperties<Properties>().instanceName = odsBuilder.getStringAttr(instanceName);
  odsState.getOrAddProperties<Properties>().moduleName = odsBuilder.getStringAttr(moduleName);

        ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
        if (::mlir::succeeded(ScopeOp::inferReturnTypes(odsBuilder.getContext(),
                      odsState.location, odsState.operands,
                      odsState.attributes.getDictionary(odsState.getContext()),
                      odsState.getRawProperties(),
                      odsState.regions, inferredReturnTypes)))
          odsState.addTypes(inferredReturnTypes);
        else
          ::mlir::detail::reportFatalInferReturnTypesError(odsState);
        
}

ScopeOp ScopeOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::llvm::StringRef instanceName, ::llvm::StringRef moduleName, /*optional*/::mlir::Value scope) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(instanceName)>(instanceName), std::forward<decltype(moduleName)>(moduleName), std::forward<decltype(scope)>(scope));
  auto __res__ = ::llvm::dyn_cast<ScopeOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ScopeOp ScopeOp::create(::mlir::ImplicitLocOpBuilder &builder, ::llvm::StringRef instanceName, ::llvm::StringRef moduleName, /*optional*/::mlir::Value scope) {
  return create(builder, builder.getLoc(), std::forward<decltype(instanceName)>(instanceName), std::forward<decltype(moduleName)>(moduleName), std::forward<decltype(scope)>(scope));
}

void ScopeOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::llvm::StringRef instanceName, ::llvm::StringRef moduleName, /*optional*/::mlir::Value scope) {
  if (scope)
    odsState.addOperands(scope);
  odsState.getOrAddProperties<Properties>().instanceName = odsBuilder.getStringAttr(instanceName);
  odsState.getOrAddProperties<Properties>().moduleName = odsBuilder.getStringAttr(moduleName);
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

ScopeOp ScopeOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::llvm::StringRef instanceName, ::llvm::StringRef moduleName, /*optional*/::mlir::Value scope) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(instanceName)>(instanceName), std::forward<decltype(moduleName)>(moduleName), std::forward<decltype(scope)>(scope));
  auto __res__ = ::llvm::dyn_cast<ScopeOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ScopeOp ScopeOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::llvm::StringRef instanceName, ::llvm::StringRef moduleName, /*optional*/::mlir::Value scope) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(instanceName)>(instanceName), std::forward<decltype(moduleName)>(moduleName), std::forward<decltype(scope)>(scope));
}

void ScopeOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<ScopeOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

ScopeOp ScopeOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<ScopeOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ScopeOp ScopeOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void ScopeOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<ScopeOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
  ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
  if (::mlir::succeeded(ScopeOp::inferReturnTypes(odsBuilder.getContext(),
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

ScopeOp ScopeOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<ScopeOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ScopeOp ScopeOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void ScopeOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

ScopeOp ScopeOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<ScopeOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ScopeOp ScopeOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

void ScopeOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties &>(properties));
  odsState.addAttributes(discardableAttributes);

  ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
  if (::mlir::succeeded(ScopeOp::inferReturnTypes(odsBuilder.getContext(),
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

ScopeOp ScopeOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<ScopeOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ScopeOp ScopeOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult ScopeOp::verifyInvariantsImpl() {
  auto tblgen_instanceName = getProperties().instanceName; (void)tblgen_instanceName;
  if (!tblgen_instanceName) return emitOpError("requires attribute 'instanceName'");
  auto tblgen_moduleName = getProperties().moduleName; (void)tblgen_moduleName;
  if (!tblgen_moduleName) return emitOpError("requires attribute 'moduleName'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Debug1(*this, tblgen_instanceName, "instanceName")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Debug1(*this, tblgen_moduleName, "moduleName")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    if (valueGroup0.size() > 1) {
      return emitOpError("operand group starting at #") << index
          << " requires 0 or 1 element, but found " << valueGroup0.size();
    }

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Debug5(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Debug5(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult ScopeOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::llvm::LogicalResult ScopeOp::inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::PropertyRef properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes) {
  inferredReturnTypes.resize(1);
  ::mlir::Builder odsBuilder(context);
  ::mlir::Type odsInferredType0 = odsBuilder.getType<circt::debug::ScopeType>();
  inferredReturnTypes[0] = odsInferredType0;
  return ::mlir::success();
}

::mlir::ParseResult ScopeOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::StringAttr instanceNameAttr;
  ::mlir::StringAttr moduleNameAttr;
  ::llvm::SmallVector<::mlir::OpAsmParser::UnresolvedOperand, 4> scopeOperands;
  ::llvm::SMLoc scopeOperandsLoc;
  (void)scopeOperandsLoc;

  if (parser.parseCustomAttributeWithFallback(instanceNameAttr, parser.getBuilder().getType<::mlir::NoneType>())) {
    return ::mlir::failure();
  }
  if (instanceNameAttr) result.getOrAddProperties<ScopeOp::Properties>().instanceName = instanceNameAttr;
  if (parser.parseComma())
    return ::mlir::failure();

  if (parser.parseCustomAttributeWithFallback(moduleNameAttr, parser.getBuilder().getType<::mlir::NoneType>())) {
    return ::mlir::failure();
  }
  if (moduleNameAttr) result.getOrAddProperties<ScopeOp::Properties>().moduleName = moduleNameAttr;
  if (::mlir::succeeded(parser.parseOptionalKeyword("scope"))) {

  {
    scopeOperandsLoc = parser.getCurrentLocation();
    ::mlir::OpAsmParser::UnresolvedOperand operand;
    ::mlir::OptionalParseResult parseResult =
                                    parser.parseOptionalOperand(operand);
    if (parseResult.has_value()) {
      if (failed(*parseResult))
        return ::mlir::failure();
      scopeOperands.push_back(operand);
    }
  }
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
  ::mlir::Type odsBuildableType0 = parser.getBuilder().getType<circt::debug::ScopeType>();
  result.addTypes(odsBuildableType0);
  if (!scopeOperands.empty()) {
  if (parser.resolveOperands(scopeOperands, odsBuildableType0, scopeOperandsLoc, result.operands))
    return ::mlir::failure();
  }
  return ::mlir::success();
}

void ScopeOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter.printAttributeWithoutType(getInstanceNameAttr());
  _odsPrinter << ",";
  _odsPrinter << ' ';
  _odsPrinter.printAttributeWithoutType(getModuleNameAttr());
  if (getScope()) {
    _odsPrinter << ' ' << "scope";
    _odsPrinter << ' ';
    if (::mlir::Value value = getScope())
      _odsPrinter << value;
  }
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("instanceName");
  elidedAttrs.push_back("moduleName");
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
}


} // namespace circt::debug
MLIR_DEFINE_EXPLICIT_TYPE_ID(circt::debug::ScopeOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(circt::debug::detail::ScopeOpGenericAdaptorBase::Properties)

namespace circt::debug {


//===----------------------------------------------------------------------===//
// circt::debug::StructOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

StructOpGenericAdaptorBase::StructOpGenericAdaptorBase(StructOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

std::pair<unsigned, unsigned> StructOpGenericAdaptorBase::getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
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

::mlir::ArrayAttr StructOpGenericAdaptorBase::getNames() {
  auto attr = getNamesAttr();
  return attr;
}


} // namespace detail
StructOpAdaptor::StructOpAdaptor(StructOp op) : StructOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult StructOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_names = getProperties().names; (void)tblgen_names;
  if (!tblgen_names) return emitError(loc, "'dbg.struct' op requires attribute 'names'");

  if (tblgen_names && !(((::llvm::isa<::mlir::ArrayAttr>(tblgen_names))) && (::llvm::all_of(::llvm::cast<::mlir::ArrayAttr>(tblgen_names), [&](::mlir::Attribute attr) { return attr && ((::llvm::isa<::mlir::StringAttr>(attr))); }))))
    return emitError(loc, "'dbg.struct' op attribute 'names' failed to satisfy constraint: string array attribute");
  return ::mlir::success();
}

std::pair<unsigned, unsigned> StructOp::getODSOperandIndexAndLength(unsigned index) {
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

::mlir::MutableOperandRange StructOp::getFieldsMutable() {
  auto range = getODSOperandIndexAndLength(0);
  auto mutableRange = ::mlir::MutableOperandRange(getOperation(), range.first, range.second);
  return mutableRange;
}

::llvm::LogicalResult StructOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.names;
       auto attr = dict.get("names");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `names` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  return ::mlir::success();
}

::mlir::Attribute StructOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.names;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("names",
                                       propStorage));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code StructOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.names.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> StructOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "names")
      return prop.names;
  return std::nullopt;
}

void StructOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "names") {
       prop.names = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.names)>>(value);
       return;
    }
}

void StructOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.names) attrs.append("names", prop.names);
}

::llvm::LogicalResult StructOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getNamesAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Debug3(attr, "names", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult StructOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.names)))
    return ::mlir::failure();
  return ::mlir::success();
}

void StructOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.names);
}

::mlir::ArrayAttr StructOp::getNames() {
  auto attr = getNamesAttr();
  return attr;
}

void StructOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::ValueRange fields, ::mlir::ArrayAttr names) {
  odsState.addOperands(fields);
  odsState.getOrAddProperties<Properties>().names = names;
  odsState.addTypes(result);
}

StructOp StructOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::ValueRange fields, ::mlir::ArrayAttr names) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(result)>(result), std::forward<decltype(fields)>(fields), std::forward<decltype(names)>(names));
  auto __res__ = ::llvm::dyn_cast<StructOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

StructOp StructOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::ValueRange fields, ::mlir::ArrayAttr names) {
  return create(builder, builder.getLoc(), std::forward<decltype(result)>(result), std::forward<decltype(fields)>(fields), std::forward<decltype(names)>(names));
}

void StructOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange fields, ::mlir::ArrayAttr names) {
  odsState.addOperands(fields);
  odsState.getOrAddProperties<Properties>().names = names;

        ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
        if (::mlir::succeeded(StructOp::inferReturnTypes(odsBuilder.getContext(),
                      odsState.location, odsState.operands,
                      odsState.attributes.getDictionary(odsState.getContext()),
                      odsState.getRawProperties(),
                      odsState.regions, inferredReturnTypes)))
          odsState.addTypes(inferredReturnTypes);
        else
          ::mlir::detail::reportFatalInferReturnTypesError(odsState);
        
}

StructOp StructOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange fields, ::mlir::ArrayAttr names) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(fields)>(fields), std::forward<decltype(names)>(names));
  auto __res__ = ::llvm::dyn_cast<StructOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

StructOp StructOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange fields, ::mlir::ArrayAttr names) {
  return create(builder, builder.getLoc(), std::forward<decltype(fields)>(fields), std::forward<decltype(names)>(names));
}

void StructOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange fields, ::mlir::ArrayAttr names) {
  odsState.addOperands(fields);
  odsState.getOrAddProperties<Properties>().names = names;
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

StructOp StructOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange fields, ::mlir::ArrayAttr names) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(fields)>(fields), std::forward<decltype(names)>(names));
  auto __res__ = ::llvm::dyn_cast<StructOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

StructOp StructOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange fields, ::mlir::ArrayAttr names) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(fields)>(fields), std::forward<decltype(names)>(names));
}

void StructOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<StructOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

StructOp StructOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<StructOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

StructOp StructOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void StructOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<StructOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
  ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
  if (::mlir::succeeded(StructOp::inferReturnTypes(odsBuilder.getContext(),
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

StructOp StructOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<StructOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

StructOp StructOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void StructOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

StructOp StructOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<StructOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

StructOp StructOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

void StructOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties &>(properties));
  odsState.addAttributes(discardableAttributes);

  ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
  if (::mlir::succeeded(StructOp::inferReturnTypes(odsBuilder.getContext(),
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

StructOp StructOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<StructOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

StructOp StructOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult StructOp::verifyInvariantsImpl() {
  auto tblgen_names = getProperties().names; (void)tblgen_names;
  if (!tblgen_names) return emitOpError("requires attribute 'names'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Debug3(*this, tblgen_names, "names")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Debug1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Debug6(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  if (!((this->getODSOperands(0).size() == getNames().size())))
    return emitOpError("failed to verify that number of fields and names match");
  return ::mlir::success();
}

::llvm::LogicalResult StructOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::llvm::LogicalResult StructOp::inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::PropertyRef properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes) {
  inferredReturnTypes.resize(1);
  ::mlir::Builder odsBuilder(context);
  ::mlir::Type odsInferredType0 = odsBuilder.getType<circt::debug::StructType>();
  inferredReturnTypes[0] = odsInferredType0;
  return ::mlir::success();
}

::llvm::LogicalResult StructOp::setPropertiesFromParsedAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
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

    auto &propStorage = prop.names;
    auto namesAttrName = ::mlir::StringAttr::get(ctx, "names");
    auto attr = dict.get(namesAttrName);
    usedKeys.insert(namesAttrName);
    if (attr || /*isRequired=*/true) {
      if (!attr) {
        emitError() << "expected key entry for names in DictionaryAttr to set "
                   "Properties.";
        return ::mlir::failure();
      }
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `names` in property conversion: " << attr;
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

void StructOp::getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects) {
}


} // namespace circt::debug
MLIR_DEFINE_EXPLICIT_TYPE_ID(circt::debug::StructOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(circt::debug::detail::StructOpGenericAdaptorBase::Properties)

namespace circt::debug {


//===----------------------------------------------------------------------===//
// circt::debug::ValueOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

ValueOpGenericAdaptorBase::ValueOpGenericAdaptorBase(ValueOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::std::optional< ::llvm::StringRef > ValueOpGenericAdaptorBase::getTypeName() {
  auto attr = getTypeNameAttr();
  return attr ? ::std::optional< ::llvm::StringRef >(attr.getValue()) : (::std::nullopt);
}

::std::optional< ::mlir::ArrayAttr > ValueOpGenericAdaptorBase::getParams() {
  auto attr = getParamsAttr();
  return attr ? ::std::optional< ::mlir::ArrayAttr >(attr) : (::std::nullopt);
}


} // namespace detail
ValueOpAdaptor::ValueOpAdaptor(ValueOp op) : ValueOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult ValueOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_params = getProperties().params; (void)tblgen_params;
  auto tblgen_typeName = getProperties().typeName; (void)tblgen_typeName;

  if (tblgen_typeName && !((::llvm::isa<::mlir::StringAttr>(tblgen_typeName))))
    return emitError(loc, "'dbg.value' op attribute 'typeName' failed to satisfy constraint: string attribute");

  if (tblgen_params && !((::llvm::isa<::mlir::ArrayAttr>(tblgen_params))))
    return emitError(loc, "'dbg.value' op attribute 'params' failed to satisfy constraint: array attribute");
  return ::mlir::success();
}

::llvm::LogicalResult ValueOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.params;
       auto attr = dict.get("params");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `params` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.typeName;
       auto attr = dict.get("typeName");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `typeName` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  return ::mlir::success();
}

::mlir::Attribute ValueOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.params;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("params",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.typeName;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("typeName",
                                       propStorage));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code ValueOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.params.getAsOpaquePointer()), 
    llvm::hash_value(prop.typeName.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> ValueOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "params")
      return prop.params;

    if (name == "typeName")
      return prop.typeName;
  return std::nullopt;
}

void ValueOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "params") {
       prop.params = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.params)>>(value);
       return;
    }

    if (name == "typeName") {
       prop.typeName = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.typeName)>>(value);
       return;
    }
}

void ValueOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.params) attrs.append("params", prop.params);

    if (prop.typeName) attrs.append("typeName", prop.typeName);
}

::llvm::LogicalResult ValueOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getParamsAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Debug4(attr, "params", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getTypeNameAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Debug1(attr, "typeName", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult ValueOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readOptionalAttribute(prop.params)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readOptionalAttribute(prop.typeName)))
    return ::mlir::failure();
  return ::mlir::success();
}

void ValueOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;

  writer.writeOptionalAttribute(prop.params);

  writer.writeOptionalAttribute(prop.typeName);
}

::std::optional< ::llvm::StringRef > ValueOp::getTypeName() {
  auto attr = getTypeNameAttr();
  return attr ? ::std::optional< ::llvm::StringRef >(attr.getValue()) : (::std::nullopt);
}

::std::optional< ::mlir::ArrayAttr > ValueOp::getParams() {
  auto attr = getParamsAttr();
  return attr ? ::std::optional< ::mlir::ArrayAttr >(attr) : (::std::nullopt);
}

void ValueOp::setTypeName(::std::optional<::llvm::StringRef> attrValue) {
    auto &odsProp = getProperties().typeName;
    if (attrValue)
      odsProp = ::mlir::Builder((*this)->getContext()).getStringAttr(*attrValue);
    else
      odsProp = nullptr;
}

void ValueOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value value, /*optional*/::mlir::StringAttr typeName, /*optional*/::mlir::ArrayAttr params) {
  odsState.addOperands(value);
  if (typeName) {
    odsState.getOrAddProperties<Properties>().typeName = typeName;
  }
  if (params) {
    odsState.getOrAddProperties<Properties>().params = params;
  }
  odsState.addTypes(result);
}

ValueOp ValueOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value value, /*optional*/::mlir::StringAttr typeName, /*optional*/::mlir::ArrayAttr params) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(result)>(result), std::forward<decltype(value)>(value), std::forward<decltype(typeName)>(typeName), std::forward<decltype(params)>(params));
  auto __res__ = ::llvm::dyn_cast<ValueOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ValueOp ValueOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value value, /*optional*/::mlir::StringAttr typeName, /*optional*/::mlir::ArrayAttr params) {
  return create(builder, builder.getLoc(), std::forward<decltype(result)>(result), std::forward<decltype(value)>(value), std::forward<decltype(typeName)>(typeName), std::forward<decltype(params)>(params));
}

void ValueOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value value, /*optional*/::mlir::StringAttr typeName, /*optional*/::mlir::ArrayAttr params) {
  odsState.addOperands(value);
  if (typeName) {
    odsState.getOrAddProperties<Properties>().typeName = typeName;
  }
  if (params) {
    odsState.getOrAddProperties<Properties>().params = params;
  }

        ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
        if (::mlir::succeeded(ValueOp::inferReturnTypes(odsBuilder.getContext(),
                      odsState.location, odsState.operands,
                      odsState.attributes.getDictionary(odsState.getContext()),
                      odsState.getRawProperties(),
                      odsState.regions, inferredReturnTypes)))
          odsState.addTypes(inferredReturnTypes);
        else
          ::mlir::detail::reportFatalInferReturnTypesError(odsState);
        
}

ValueOp ValueOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value value, /*optional*/::mlir::StringAttr typeName, /*optional*/::mlir::ArrayAttr params) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(value)>(value), std::forward<decltype(typeName)>(typeName), std::forward<decltype(params)>(params));
  auto __res__ = ::llvm::dyn_cast<ValueOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ValueOp ValueOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value value, /*optional*/::mlir::StringAttr typeName, /*optional*/::mlir::ArrayAttr params) {
  return create(builder, builder.getLoc(), std::forward<decltype(value)>(value), std::forward<decltype(typeName)>(typeName), std::forward<decltype(params)>(params));
}

void ValueOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value value, /*optional*/::mlir::StringAttr typeName, /*optional*/::mlir::ArrayAttr params) {
  odsState.addOperands(value);
  if (typeName) {
    odsState.getOrAddProperties<Properties>().typeName = typeName;
  }
  if (params) {
    odsState.getOrAddProperties<Properties>().params = params;
  }
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

ValueOp ValueOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value value, /*optional*/::mlir::StringAttr typeName, /*optional*/::mlir::ArrayAttr params) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(value)>(value), std::forward<decltype(typeName)>(typeName), std::forward<decltype(params)>(params));
  auto __res__ = ::llvm::dyn_cast<ValueOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ValueOp ValueOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value value, /*optional*/::mlir::StringAttr typeName, /*optional*/::mlir::ArrayAttr params) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(value)>(value), std::forward<decltype(typeName)>(typeName), std::forward<decltype(params)>(params));
}

void ValueOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<ValueOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

ValueOp ValueOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<ValueOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ValueOp ValueOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void ValueOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<ValueOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
  ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
  if (::mlir::succeeded(ValueOp::inferReturnTypes(odsBuilder.getContext(),
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

ValueOp ValueOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<ValueOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ValueOp ValueOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void ValueOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

ValueOp ValueOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<ValueOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ValueOp ValueOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

void ValueOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties &>(properties));
  odsState.addAttributes(discardableAttributes);

  ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
  if (::mlir::succeeded(ValueOp::inferReturnTypes(odsBuilder.getContext(),
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

ValueOp ValueOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<ValueOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ValueOp ValueOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult ValueOp::verifyInvariantsImpl() {
  auto tblgen_params = getProperties().params; (void)tblgen_params;
  auto tblgen_typeName = getProperties().typeName; (void)tblgen_typeName;

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Debug1(*this, tblgen_typeName, "typeName")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Debug4(*this, tblgen_params, "params")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Debug3(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Debug7(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult ValueOp::verifyInvariants() {
  if(::mlir::succeeded(verifyInvariantsImpl()) && ::mlir::succeeded(verify()))
    return ::mlir::success();
  return ::mlir::failure();
}

::llvm::LogicalResult ValueOp::inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::PropertyRef properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes) {
  inferredReturnTypes.resize(1);
  ::mlir::Builder odsBuilder(context);
  ::mlir::Type odsInferredType0 = odsBuilder.getType<circt::debug::ValueType>();
  inferredReturnTypes[0] = odsInferredType0;
  return ::mlir::success();
}

::mlir::ParseResult ValueOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::OpAsmParser::UnresolvedOperand valueRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> valueOperands(&valueRawOperand, 1);  ::llvm::SMLoc valueOperandsLoc;
  (void)valueOperandsLoc;
  ::mlir::StringAttr typeNameAttr;
  ::mlir::ArrayAttr paramsAttr;
  ::mlir::Type valueRawType{};
  ::llvm::ArrayRef<::mlir::Type> valueTypes(&valueRawType, 1);

  valueOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(valueRawOperand))
    return ::mlir::failure();
  if (::mlir::succeeded(parser.parseOptionalKeyword("typeName"))) {

  if (parser.parseCustomAttributeWithFallback(typeNameAttr, parser.getBuilder().getType<::mlir::NoneType>())) {
    return ::mlir::failure();
  }
  if (typeNameAttr) result.getOrAddProperties<ValueOp::Properties>().typeName = typeNameAttr;
  }
  if (::mlir::succeeded(parser.parseOptionalKeyword("params"))) {

  if (parser.parseCustomAttributeWithFallback(paramsAttr, parser.getBuilder().getType<::mlir::NoneType>())) {
    return ::mlir::failure();
  }
  if (paramsAttr) result.getOrAddProperties<ValueOp::Properties>().params = paramsAttr;
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
    valueRawType = type;
  }
  ::mlir::Type odsBuildableType0 = parser.getBuilder().getType<circt::debug::ValueType>();
  result.addTypes(odsBuildableType0);
  if (parser.resolveOperands(valueOperands, valueTypes, valueOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void ValueOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter << getValue();
  if (getTypeNameAttr()) {
    _odsPrinter << ' ' << "typeName";
    _odsPrinter << ' ';
    _odsPrinter.printAttributeWithoutType(getTypeNameAttr());
  }
  if (getParamsAttr()) {
    _odsPrinter << ' ' << "params";
    _odsPrinter << ' ';
    _odsPrinter.printAttributeWithoutType(getParamsAttr());
  }
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("typeName");
  elidedAttrs.push_back("params");
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
  {
    auto type = getValue().getType();
    if (auto validType = ::llvm::dyn_cast<::mlir::Type>(type))
      _odsPrinter.printStrippedAttrOrType(validType);
   else
     _odsPrinter << type;
  }
}


} // namespace circt::debug
MLIR_DEFINE_EXPLICIT_TYPE_ID(circt::debug::ValueOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(circt::debug::detail::ValueOpGenericAdaptorBase::Properties)

namespace circt::debug {


//===----------------------------------------------------------------------===//
// circt::debug::VariableOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

VariableOpGenericAdaptorBase::VariableOpGenericAdaptorBase(VariableOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

std::pair<unsigned, unsigned> VariableOpGenericAdaptorBase::getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
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

::llvm::StringRef VariableOpGenericAdaptorBase::getName() {
  auto attr = getNameAttr();
  return attr.getValue();
}


} // namespace detail
VariableOpAdaptor::VariableOpAdaptor(VariableOp op) : VariableOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult VariableOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_name = getProperties().name; (void)tblgen_name;
  if (!tblgen_name) return emitError(loc, "'dbg.variable' op requires attribute 'name'");

  if (tblgen_name && !((::llvm::isa<::mlir::StringAttr>(tblgen_name))))
    return emitError(loc, "'dbg.variable' op attribute 'name' failed to satisfy constraint: string attribute");
  return ::mlir::success();
}

std::pair<unsigned, unsigned> VariableOp::getODSOperandIndexAndLength(unsigned index) {
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

::mlir::MutableOperandRange VariableOp::getScopeMutable() {
  auto range = getODSOperandIndexAndLength(1);
  auto mutableRange = ::mlir::MutableOperandRange(getOperation(), range.first, range.second);
  return mutableRange;
}

::llvm::LogicalResult VariableOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
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

::mlir::Attribute VariableOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
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

llvm::hash_code VariableOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.name.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> VariableOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "name")
      return prop.name;
  return std::nullopt;
}

void VariableOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "name") {
       prop.name = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.name)>>(value);
       return;
    }
}

void VariableOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.name) attrs.append("name", prop.name);
}

::llvm::LogicalResult VariableOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getNameAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Debug1(attr, "name", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult VariableOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.name)))
    return ::mlir::failure();
  return ::mlir::success();
}

void VariableOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.name);
}

::llvm::StringRef VariableOp::getName() {
  auto attr = getNameAttr();
  return attr.getValue();
}

void VariableOp::setName(::llvm::StringRef attrValue) {
  getProperties().name = ::mlir::Builder((*this)->getContext()).getStringAttr(attrValue);
}

void VariableOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::StringAttr name, ::mlir::Value value, /*optional*/::mlir::Value scope) {
  odsState.addOperands(value);
  if (scope)
    odsState.addOperands(scope);
  odsState.getOrAddProperties<Properties>().name = name;
}

VariableOp VariableOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::StringAttr name, ::mlir::Value value, /*optional*/::mlir::Value scope) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(name)>(name), std::forward<decltype(value)>(value), std::forward<decltype(scope)>(scope));
  auto __res__ = ::llvm::dyn_cast<VariableOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

VariableOp VariableOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::StringAttr name, ::mlir::Value value, /*optional*/::mlir::Value scope) {
  return create(builder, builder.getLoc(), std::forward<decltype(name)>(name), std::forward<decltype(value)>(value), std::forward<decltype(scope)>(scope));
}

void VariableOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::StringAttr name, ::mlir::Value value, /*optional*/::mlir::Value scope) {
  odsState.addOperands(value);
  if (scope)
    odsState.addOperands(scope);
  odsState.getOrAddProperties<Properties>().name = name;
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

VariableOp VariableOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::StringAttr name, ::mlir::Value value, /*optional*/::mlir::Value scope) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(name)>(name), std::forward<decltype(value)>(value), std::forward<decltype(scope)>(scope));
  auto __res__ = ::llvm::dyn_cast<VariableOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

VariableOp VariableOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::StringAttr name, ::mlir::Value value, /*optional*/::mlir::Value scope) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(name)>(name), std::forward<decltype(value)>(value), std::forward<decltype(scope)>(scope));
}

void VariableOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::llvm::StringRef name, ::mlir::Value value, /*optional*/::mlir::Value scope) {
  odsState.addOperands(value);
  if (scope)
    odsState.addOperands(scope);
  odsState.getOrAddProperties<Properties>().name = odsBuilder.getStringAttr(name);
}

VariableOp VariableOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::llvm::StringRef name, ::mlir::Value value, /*optional*/::mlir::Value scope) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(name)>(name), std::forward<decltype(value)>(value), std::forward<decltype(scope)>(scope));
  auto __res__ = ::llvm::dyn_cast<VariableOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

VariableOp VariableOp::create(::mlir::ImplicitLocOpBuilder &builder, ::llvm::StringRef name, ::mlir::Value value, /*optional*/::mlir::Value scope) {
  return create(builder, builder.getLoc(), std::forward<decltype(name)>(name), std::forward<decltype(value)>(value), std::forward<decltype(scope)>(scope));
}

void VariableOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::llvm::StringRef name, ::mlir::Value value, /*optional*/::mlir::Value scope) {
  odsState.addOperands(value);
  if (scope)
    odsState.addOperands(scope);
  odsState.getOrAddProperties<Properties>().name = odsBuilder.getStringAttr(name);
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

VariableOp VariableOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::llvm::StringRef name, ::mlir::Value value, /*optional*/::mlir::Value scope) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(name)>(name), std::forward<decltype(value)>(value), std::forward<decltype(scope)>(scope));
  auto __res__ = ::llvm::dyn_cast<VariableOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

VariableOp VariableOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::llvm::StringRef name, ::mlir::Value value, /*optional*/::mlir::Value scope) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(name)>(name), std::forward<decltype(value)>(value), std::forward<decltype(scope)>(scope));
}

void VariableOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() >= 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<VariableOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

VariableOp VariableOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<VariableOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

VariableOp VariableOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void VariableOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() >= 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

VariableOp VariableOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<VariableOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

VariableOp VariableOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult VariableOp::verifyInvariantsImpl() {
  auto tblgen_name = getProperties().name; (void)tblgen_name;
  if (!tblgen_name) return emitOpError("requires attribute 'name'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Debug1(*this, tblgen_name, "name")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Debug3(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSOperands(1);

    if (valueGroup1.size() > 1) {
      return emitOpError("operand group starting at #") << index
          << " requires 0 or 1 element, but found " << valueGroup1.size();
    }

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Debug5(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult VariableOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult VariableOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::StringAttr nameAttr;
  ::mlir::OpAsmParser::UnresolvedOperand valueRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> valueOperands(&valueRawOperand, 1);  ::llvm::SMLoc valueOperandsLoc;
  (void)valueOperandsLoc;
  ::llvm::SmallVector<::mlir::OpAsmParser::UnresolvedOperand, 4> scopeOperands;
  ::llvm::SMLoc scopeOperandsLoc;
  (void)scopeOperandsLoc;
  ::mlir::Type valueRawType{};
  ::llvm::ArrayRef<::mlir::Type> valueTypes(&valueRawType, 1);

  if (parser.parseCustomAttributeWithFallback(nameAttr, parser.getBuilder().getType<::mlir::NoneType>())) {
    return ::mlir::failure();
  }
  if (nameAttr) result.getOrAddProperties<VariableOp::Properties>().name = nameAttr;
  if (parser.parseComma())
    return ::mlir::failure();

  valueOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(valueRawOperand))
    return ::mlir::failure();
  if (::mlir::succeeded(parser.parseOptionalKeyword("scope"))) {

  {
    scopeOperandsLoc = parser.getCurrentLocation();
    ::mlir::OpAsmParser::UnresolvedOperand operand;
    ::mlir::OptionalParseResult parseResult =
                                    parser.parseOptionalOperand(operand);
    if (parseResult.has_value()) {
      if (failed(*parseResult))
        return ::mlir::failure();
      scopeOperands.push_back(operand);
    }
  }
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
    valueRawType = type;
  }
  ::mlir::Type odsBuildableType0 = parser.getBuilder().getType<circt::debug::ScopeType>();
  if (parser.resolveOperands(valueOperands, valueTypes, valueOperandsLoc, result.operands))
    return ::mlir::failure();
  if (!scopeOperands.empty()) {
  if (parser.resolveOperands(scopeOperands, odsBuildableType0, scopeOperandsLoc, result.operands))
    return ::mlir::failure();
  }
  return ::mlir::success();
}

void VariableOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter.printAttributeWithoutType(getNameAttr());
  _odsPrinter << ",";
  _odsPrinter << ' ';
  _odsPrinter << getValue();
  if (getScope()) {
    _odsPrinter << ' ' << "scope";
    _odsPrinter << ' ';
    if (::mlir::Value value = getScope())
      _odsPrinter << value;
  }
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("name");
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
  {
    auto type = getValue().getType();
    if (auto validType = ::llvm::dyn_cast<::mlir::Type>(type))
      _odsPrinter.printStrippedAttrOrType(validType);
   else
     _odsPrinter << type;
  }
}


} // namespace circt::debug
MLIR_DEFINE_EXPLICIT_TYPE_ID(circt::debug::VariableOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(circt::debug::detail::VariableOpGenericAdaptorBase::Properties)


#endif // GET_OP_CLASSES

