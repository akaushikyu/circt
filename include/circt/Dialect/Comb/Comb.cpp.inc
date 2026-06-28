/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Op Definitions                                                             *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: Comb.td                                                              *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

#ifdef GET_OP_LIST
#undef GET_OP_LIST

::circt::comb::AddOp,
::circt::comb::AndOp,
::circt::comb::ConcatOp,
::circt::comb::DivSOp,
::circt::comb::DivUOp,
::circt::comb::ExtractOp,
::circt::comb::ICmpOp,
::circt::comb::ModSOp,
::circt::comb::ModUOp,
::circt::comb::MulOp,
::circt::comb::MuxOp,
::circt::comb::OrOp,
::circt::comb::ParityOp,
::circt::comb::ReplicateOp,
::circt::comb::ReverseOp,
::circt::comb::ShlOp,
::circt::comb::ShrSOp,
::circt::comb::ShrUOp,
::circt::comb::SubOp,
::circt::comb::TruthTableOp,
::circt::comb::XorOp
#endif // GET_OP_LIST

#ifdef GET_OP_CLASSES
#undef GET_OP_CLASSES


//===----------------------------------------------------------------------===//
// Local Utility Method Definitions
//===----------------------------------------------------------------------===//


static ::llvm::LogicalResult __mlir_ods_local_type_constraint_Comb1(
    ::mlir::Operation *op, ::mlir::Type type, ::llvm::StringRef valueKind,
    unsigned valueIndex) {
  if (!((::circt::hw::isHWIntegerType(type)))) {
    return op->emitOpError(valueKind) << " #" << valueIndex
        << " must be variadic of a signless integer bitvector, but got " << type;
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_type_constraint_Comb2(
    ::mlir::Operation *op, ::mlir::Type type, ::llvm::StringRef valueKind,
    unsigned valueIndex) {
  if (!((::circt::hw::isHWIntegerType(type)))) {
    return op->emitOpError(valueKind) << " #" << valueIndex
        << " must be a signless integer bitvector, but got " << type;
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_type_constraint_Comb3(
    ::mlir::Operation *op, ::mlir::Type type, ::llvm::StringRef valueKind,
    unsigned valueIndex) {
  if (!((type.isSignlessInteger(1)))) {
    return op->emitOpError(valueKind) << " #" << valueIndex
        << " must be 1-bit signless integer, but got " << type;
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_type_constraint_Comb4(
    ::mlir::Operation *op, ::mlir::Type type, ::llvm::StringRef valueKind,
    unsigned valueIndex) {
  if (!(!((::llvm::isa<::mlir::TokenType>(type))))) {
    return op->emitOpError(valueKind) << " #" << valueIndex
        << " must be any non-token type, but got " << type;
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_type_constraint_Comb5(
    ::mlir::Operation *op, ::mlir::Type type, ::llvm::StringRef valueKind,
    unsigned valueIndex) {
  if (!((type.isSignlessInteger(1)))) {
    return op->emitOpError(valueKind) << " #" << valueIndex
        << " must be variadic of 1-bit signless integer, but got " << type;
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_Comb1(
    ::mlir::Attribute attr, ::llvm::StringRef attrName, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  if (attr && !((::llvm::isa<::mlir::UnitAttr>(attr))))
    return emitError() << "attribute '" << attrName
        << "' failed to satisfy constraint: unit attribute";
  return ::mlir::success();
}
static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_Comb1(
    ::mlir::Operation *op, ::mlir::Attribute attr, ::llvm::StringRef attrName) {
  return __mlir_ods_local_attr_constraint_Comb1(attr, attrName, [op]() {
    return op->emitOpError();
  });
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_Comb2(
    ::mlir::Attribute attr, ::llvm::StringRef attrName, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  if (attr && !(((::llvm::isa<::mlir::IntegerAttr>(attr))) && ((::llvm::cast<::mlir::IntegerAttr>(attr).getType().isSignlessInteger(32)))))
    return emitError() << "attribute '" << attrName
        << "' failed to satisfy constraint: 32-bit signless integer attribute";
  return ::mlir::success();
}
static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_Comb2(
    ::mlir::Operation *op, ::mlir::Attribute attr, ::llvm::StringRef attrName) {
  return __mlir_ods_local_attr_constraint_Comb2(attr, attrName, [op]() {
    return op->emitOpError();
  });
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_Comb3(
    ::mlir::Attribute attr, ::llvm::StringRef attrName, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  if (attr && !((::llvm::isa<circt::comb::ICmpPredicateAttr>(attr))))
    return emitError() << "attribute '" << attrName
        << "' failed to satisfy constraint: hw.icmp comparison predicate";
  return ::mlir::success();
}
static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_Comb3(
    ::mlir::Operation *op, ::mlir::Attribute attr, ::llvm::StringRef attrName) {
  return __mlir_ods_local_attr_constraint_Comb3(attr, attrName, [op]() {
    return op->emitOpError();
  });
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_Comb4(
    ::mlir::Attribute attr, ::llvm::StringRef attrName, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  if (attr && !((::llvm::isa<::mlir::DenseBoolArrayAttr>(attr))))
    return emitError() << "attribute '" << attrName
        << "' failed to satisfy constraint: i1 dense array attribute";
  return ::mlir::success();
}
static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_Comb4(
    ::mlir::Operation *op, ::mlir::Attribute attr, ::llvm::StringRef attrName) {
  return __mlir_ods_local_attr_constraint_Comb4(attr, attrName, [op]() {
    return op->emitOpError();
  });
}
namespace circt::comb {


//===----------------------------------------------------------------------===//
// ::circt::comb::AddOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

AddOpGenericAdaptorBase::AddOpGenericAdaptorBase(AddOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

std::pair<unsigned, unsigned> AddOpGenericAdaptorBase::getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
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

::mlir::UnitAttr AddOpGenericAdaptorBase::getTwoStateAttr() {
  auto attr = ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(getProperties().twoState);
  if (!attr)
    attr = ((false) ? ::mlir::Builder(odsAttrs.getContext()).getUnitAttr() : nullptr);
  return attr;
}

bool AddOpGenericAdaptorBase::getTwoState() {
  auto attr = getTwoStateAttr();
    if (!attr)
      return ((false) ? ::mlir::Builder(odsAttrs.getContext()).getUnitAttr() : nullptr) != nullptr;
  return attr != nullptr;
}


} // namespace detail
AddOpAdaptor::AddOpAdaptor(AddOp op) : AddOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult AddOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_twoState = getProperties().twoState; (void)tblgen_twoState;

  if (tblgen_twoState && !((::llvm::isa<::mlir::UnitAttr>(tblgen_twoState))))
    return emitError(loc, "'comb.add' op attribute 'twoState' failed to satisfy constraint: unit attribute");
  return ::mlir::success();
}

std::pair<unsigned, unsigned> AddOp::getODSOperandIndexAndLength(unsigned index) {
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

::mlir::MutableOperandRange AddOp::getInputsMutable() {
  auto range = getODSOperandIndexAndLength(0);
  auto mutableRange = ::mlir::MutableOperandRange(getOperation(), range.first, range.second);
  return mutableRange;
}

::llvm::LogicalResult AddOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.twoState;
       auto attr = dict.get("twoState");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `twoState` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  return ::mlir::success();
}

::mlir::Attribute AddOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.twoState;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("twoState",
                                       propStorage));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code AddOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.twoState.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> AddOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "twoState")
      return prop.twoState;
  return std::nullopt;
}

void AddOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "twoState") {
       prop.twoState = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.twoState)>>(value);
       return;
    }
}

void AddOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.twoState) attrs.append("twoState", prop.twoState);
}

::llvm::LogicalResult AddOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getTwoStateAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Comb1(attr, "twoState", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult AddOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readOptionalAttribute(prop.twoState)))
    return ::mlir::failure();
  return ::mlir::success();
}

void AddOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;

  writer.writeOptionalAttribute(prop.twoState);
}

bool AddOp::getTwoState() {
  auto attr = getTwoStateAttr();
    if (!attr)
      return ((false) ? ::mlir::Builder((*this)->getContext()).getUnitAttr() : nullptr) != nullptr;
  return attr != nullptr;
}

void AddOp::setTwoState(bool attrValue) {
    auto &odsProp = getProperties().twoState;
    if (attrValue)
      odsProp = ((attrValue) ? ::mlir::Builder((*this)->getContext()).getUnitAttr() : nullptr);
    else
      odsProp = nullptr;
}

void AddOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value lhs, Value rhs, bool twoState) {
      return build(odsBuilder, odsState, lhs.getType(),
                   ValueRange{lhs, rhs}, twoState);
    
}

AddOp AddOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, Value lhs, Value rhs, bool twoState) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(lhs)>(lhs), std::forward<decltype(rhs)>(rhs), std::forward<decltype(twoState)>(twoState));
  auto __res__ = ::llvm::dyn_cast<AddOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

AddOp AddOp::create(::mlir::ImplicitLocOpBuilder &builder, Value lhs, Value rhs, bool twoState) {
  return create(builder, builder.getLoc(), std::forward<decltype(lhs)>(lhs), std::forward<decltype(rhs)>(rhs), std::forward<decltype(twoState)>(twoState));
}

void AddOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::ValueRange inputs, /*optional*/::mlir::UnitAttr twoState) {
  odsState.addOperands(inputs);
  if (twoState) {
    odsState.getOrAddProperties<Properties>().twoState = twoState;
  }
  odsState.addTypes(result);
}

AddOp AddOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::ValueRange inputs, /*optional*/::mlir::UnitAttr twoState) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(result)>(result), std::forward<decltype(inputs)>(inputs), std::forward<decltype(twoState)>(twoState));
  auto __res__ = ::llvm::dyn_cast<AddOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

AddOp AddOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::ValueRange inputs, /*optional*/::mlir::UnitAttr twoState) {
  return create(builder, builder.getLoc(), std::forward<decltype(result)>(result), std::forward<decltype(inputs)>(inputs), std::forward<decltype(twoState)>(twoState));
}

void AddOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange inputs, /*optional*/::mlir::UnitAttr twoState) {
  odsState.addOperands(inputs);
  if (twoState) {
    odsState.getOrAddProperties<Properties>().twoState = twoState;
  }
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

AddOp AddOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange inputs, /*optional*/::mlir::UnitAttr twoState) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(inputs)>(inputs), std::forward<decltype(twoState)>(twoState));
  auto __res__ = ::llvm::dyn_cast<AddOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

AddOp AddOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange inputs, /*optional*/::mlir::UnitAttr twoState) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(inputs)>(inputs), std::forward<decltype(twoState)>(twoState));
}

void AddOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::ValueRange inputs, /*optional*/bool twoState) {
  odsState.addOperands(inputs);
  if (twoState) {
    odsState.getOrAddProperties<Properties>().twoState = ((twoState) ? odsBuilder.getUnitAttr() : nullptr);
  }
  odsState.addTypes(result);
}

AddOp AddOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::ValueRange inputs, /*optional*/bool twoState) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(result)>(result), std::forward<decltype(inputs)>(inputs), std::forward<decltype(twoState)>(twoState));
  auto __res__ = ::llvm::dyn_cast<AddOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

AddOp AddOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::ValueRange inputs, /*optional*/bool twoState) {
  return create(builder, builder.getLoc(), std::forward<decltype(result)>(result), std::forward<decltype(inputs)>(inputs), std::forward<decltype(twoState)>(twoState));
}

void AddOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange inputs, /*optional*/bool twoState) {
  odsState.addOperands(inputs);
  if (twoState) {
    odsState.getOrAddProperties<Properties>().twoState = ((twoState) ? odsBuilder.getUnitAttr() : nullptr);
  }
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

AddOp AddOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange inputs, /*optional*/bool twoState) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(inputs)>(inputs), std::forward<decltype(twoState)>(twoState));
  auto __res__ = ::llvm::dyn_cast<AddOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

AddOp AddOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange inputs, /*optional*/bool twoState) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(inputs)>(inputs), std::forward<decltype(twoState)>(twoState));
}

void AddOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<AddOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

AddOp AddOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<AddOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

AddOp AddOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void AddOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

AddOp AddOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<AddOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

AddOp AddOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

void AddOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange inputs, /*optional*/::mlir::UnitAttr twoState) {
  odsState.addOperands(inputs);
  if (twoState) {
    odsState.getOrAddProperties<Properties>().twoState = twoState;
  }
  odsState.addTypes({inputs.front().getType()});

}

AddOp AddOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange inputs, /*optional*/::mlir::UnitAttr twoState) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(inputs)>(inputs), std::forward<decltype(twoState)>(twoState));
  auto __res__ = ::llvm::dyn_cast<AddOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

AddOp AddOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange inputs, /*optional*/::mlir::UnitAttr twoState) {
  return create(builder, builder.getLoc(), std::forward<decltype(inputs)>(inputs), std::forward<decltype(twoState)>(twoState));
}

void AddOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange inputs, /*optional*/bool twoState) {
  odsState.addOperands(inputs);
  if (twoState) {
    odsState.getOrAddProperties<Properties>().twoState = ((twoState) ? odsBuilder.getUnitAttr() : nullptr);
  }
  odsState.addTypes({inputs.front().getType()});

}

AddOp AddOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange inputs, /*optional*/bool twoState) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(inputs)>(inputs), std::forward<decltype(twoState)>(twoState));
  auto __res__ = ::llvm::dyn_cast<AddOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

AddOp AddOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange inputs, /*optional*/bool twoState) {
  return create(builder, builder.getLoc(), std::forward<decltype(inputs)>(inputs), std::forward<decltype(twoState)>(twoState));
}

void AddOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  odsState.addTypes({operands[0].getType()});

}

AddOp AddOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<AddOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

AddOp AddOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void AddOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  odsState.addTypes({operands[0].getType()});

}

AddOp AddOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<AddOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

AddOp AddOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult AddOp::verifyInvariantsImpl() {
  auto tblgen_twoState = getProperties().twoState; (void)tblgen_twoState;

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Comb1(*this, tblgen_twoState, "twoState")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Comb1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Comb2(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult AddOp::verifyInvariants() {
  if(::mlir::succeeded(verifyInvariantsImpl()) && ::mlir::succeeded(verify()))
    return ::mlir::success();
  return ::mlir::failure();
}

void AddOp::getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context) {
  results.add(canonicalize);
}

::mlir::ParseResult AddOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::llvm::SmallVector<::mlir::OpAsmParser::UnresolvedOperand, 4> inputsOperands;
  ::llvm::SMLoc inputsOperandsLoc;
  (void)inputsOperandsLoc;
  ::mlir::Type resultRawType{};
  ::llvm::ArrayRef<::mlir::Type> resultTypes(&resultRawType, 1);
  if (::mlir::succeeded(parser.parseOptionalKeyword("bin"))) {
    result.getOrAddProperties<AddOp::Properties>().twoState = parser.getBuilder().getUnitAttr();  }

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

  if (parser.parseType(resultRawType))
    return ::mlir::failure();
  result.addTypes(resultTypes);
  if (parser.resolveOperands(inputsOperands, resultTypes[0], inputsOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void AddOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  if ((getTwoStateAttr() && getTwoStateAttr() != ((false) ? ::mlir::OpBuilder((*this)->getContext()).getUnitAttr() : nullptr))) {
    _odsPrinter << ' ' << "bin";
  }
  _odsPrinter << ' ';
  _odsPrinter << getInputs();
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("twoState");
  {
     ::mlir::Builder odsBuilder(getContext());
     ::mlir::Attribute attr = getTwoStateAttr();
     if(attr && (attr == ((false) ? odsBuilder.getUnitAttr() : nullptr)))
       elidedAttrs.push_back("twoState");
  }
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
   _odsPrinter << getResult().getType();
}

void AddOp::getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects) {
}


} // namespace circt::comb
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::comb::AddOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::comb::detail::AddOpGenericAdaptorBase::Properties)

namespace circt::comb {


//===----------------------------------------------------------------------===//
// ::circt::comb::AndOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

AndOpGenericAdaptorBase::AndOpGenericAdaptorBase(AndOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

std::pair<unsigned, unsigned> AndOpGenericAdaptorBase::getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
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

::mlir::UnitAttr AndOpGenericAdaptorBase::getTwoStateAttr() {
  auto attr = ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(getProperties().twoState);
  if (!attr)
    attr = ((false) ? ::mlir::Builder(odsAttrs.getContext()).getUnitAttr() : nullptr);
  return attr;
}

bool AndOpGenericAdaptorBase::getTwoState() {
  auto attr = getTwoStateAttr();
    if (!attr)
      return ((false) ? ::mlir::Builder(odsAttrs.getContext()).getUnitAttr() : nullptr) != nullptr;
  return attr != nullptr;
}


} // namespace detail
AndOpAdaptor::AndOpAdaptor(AndOp op) : AndOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult AndOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_twoState = getProperties().twoState; (void)tblgen_twoState;

  if (tblgen_twoState && !((::llvm::isa<::mlir::UnitAttr>(tblgen_twoState))))
    return emitError(loc, "'comb.and' op attribute 'twoState' failed to satisfy constraint: unit attribute");
  return ::mlir::success();
}

std::pair<unsigned, unsigned> AndOp::getODSOperandIndexAndLength(unsigned index) {
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

::mlir::MutableOperandRange AndOp::getInputsMutable() {
  auto range = getODSOperandIndexAndLength(0);
  auto mutableRange = ::mlir::MutableOperandRange(getOperation(), range.first, range.second);
  return mutableRange;
}

::llvm::LogicalResult AndOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.twoState;
       auto attr = dict.get("twoState");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `twoState` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  return ::mlir::success();
}

::mlir::Attribute AndOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.twoState;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("twoState",
                                       propStorage));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code AndOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.twoState.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> AndOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "twoState")
      return prop.twoState;
  return std::nullopt;
}

void AndOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "twoState") {
       prop.twoState = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.twoState)>>(value);
       return;
    }
}

void AndOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.twoState) attrs.append("twoState", prop.twoState);
}

::llvm::LogicalResult AndOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getTwoStateAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Comb1(attr, "twoState", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult AndOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readOptionalAttribute(prop.twoState)))
    return ::mlir::failure();
  return ::mlir::success();
}

void AndOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;

  writer.writeOptionalAttribute(prop.twoState);
}

bool AndOp::getTwoState() {
  auto attr = getTwoStateAttr();
    if (!attr)
      return ((false) ? ::mlir::Builder((*this)->getContext()).getUnitAttr() : nullptr) != nullptr;
  return attr != nullptr;
}

void AndOp::setTwoState(bool attrValue) {
    auto &odsProp = getProperties().twoState;
    if (attrValue)
      odsProp = ((attrValue) ? ::mlir::Builder((*this)->getContext()).getUnitAttr() : nullptr);
    else
      odsProp = nullptr;
}

void AndOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value lhs, Value rhs, bool twoState) {
      return build(odsBuilder, odsState, lhs.getType(),
                   ValueRange{lhs, rhs}, twoState);
    
}

AndOp AndOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, Value lhs, Value rhs, bool twoState) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(lhs)>(lhs), std::forward<decltype(rhs)>(rhs), std::forward<decltype(twoState)>(twoState));
  auto __res__ = ::llvm::dyn_cast<AndOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

AndOp AndOp::create(::mlir::ImplicitLocOpBuilder &builder, Value lhs, Value rhs, bool twoState) {
  return create(builder, builder.getLoc(), std::forward<decltype(lhs)>(lhs), std::forward<decltype(rhs)>(rhs), std::forward<decltype(twoState)>(twoState));
}

void AndOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::ValueRange inputs, /*optional*/::mlir::UnitAttr twoState) {
  odsState.addOperands(inputs);
  if (twoState) {
    odsState.getOrAddProperties<Properties>().twoState = twoState;
  }
  odsState.addTypes(result);
}

AndOp AndOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::ValueRange inputs, /*optional*/::mlir::UnitAttr twoState) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(result)>(result), std::forward<decltype(inputs)>(inputs), std::forward<decltype(twoState)>(twoState));
  auto __res__ = ::llvm::dyn_cast<AndOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

AndOp AndOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::ValueRange inputs, /*optional*/::mlir::UnitAttr twoState) {
  return create(builder, builder.getLoc(), std::forward<decltype(result)>(result), std::forward<decltype(inputs)>(inputs), std::forward<decltype(twoState)>(twoState));
}

void AndOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange inputs, /*optional*/::mlir::UnitAttr twoState) {
  odsState.addOperands(inputs);
  if (twoState) {
    odsState.getOrAddProperties<Properties>().twoState = twoState;
  }
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

AndOp AndOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange inputs, /*optional*/::mlir::UnitAttr twoState) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(inputs)>(inputs), std::forward<decltype(twoState)>(twoState));
  auto __res__ = ::llvm::dyn_cast<AndOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

AndOp AndOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange inputs, /*optional*/::mlir::UnitAttr twoState) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(inputs)>(inputs), std::forward<decltype(twoState)>(twoState));
}

void AndOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::ValueRange inputs, /*optional*/bool twoState) {
  odsState.addOperands(inputs);
  if (twoState) {
    odsState.getOrAddProperties<Properties>().twoState = ((twoState) ? odsBuilder.getUnitAttr() : nullptr);
  }
  odsState.addTypes(result);
}

AndOp AndOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::ValueRange inputs, /*optional*/bool twoState) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(result)>(result), std::forward<decltype(inputs)>(inputs), std::forward<decltype(twoState)>(twoState));
  auto __res__ = ::llvm::dyn_cast<AndOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

AndOp AndOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::ValueRange inputs, /*optional*/bool twoState) {
  return create(builder, builder.getLoc(), std::forward<decltype(result)>(result), std::forward<decltype(inputs)>(inputs), std::forward<decltype(twoState)>(twoState));
}

void AndOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange inputs, /*optional*/bool twoState) {
  odsState.addOperands(inputs);
  if (twoState) {
    odsState.getOrAddProperties<Properties>().twoState = ((twoState) ? odsBuilder.getUnitAttr() : nullptr);
  }
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

AndOp AndOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange inputs, /*optional*/bool twoState) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(inputs)>(inputs), std::forward<decltype(twoState)>(twoState));
  auto __res__ = ::llvm::dyn_cast<AndOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

AndOp AndOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange inputs, /*optional*/bool twoState) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(inputs)>(inputs), std::forward<decltype(twoState)>(twoState));
}

void AndOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<AndOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

AndOp AndOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<AndOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

AndOp AndOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void AndOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

AndOp AndOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<AndOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

AndOp AndOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

void AndOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange inputs, /*optional*/::mlir::UnitAttr twoState) {
  odsState.addOperands(inputs);
  if (twoState) {
    odsState.getOrAddProperties<Properties>().twoState = twoState;
  }
  odsState.addTypes({inputs.front().getType()});

}

AndOp AndOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange inputs, /*optional*/::mlir::UnitAttr twoState) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(inputs)>(inputs), std::forward<decltype(twoState)>(twoState));
  auto __res__ = ::llvm::dyn_cast<AndOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

AndOp AndOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange inputs, /*optional*/::mlir::UnitAttr twoState) {
  return create(builder, builder.getLoc(), std::forward<decltype(inputs)>(inputs), std::forward<decltype(twoState)>(twoState));
}

void AndOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange inputs, /*optional*/bool twoState) {
  odsState.addOperands(inputs);
  if (twoState) {
    odsState.getOrAddProperties<Properties>().twoState = ((twoState) ? odsBuilder.getUnitAttr() : nullptr);
  }
  odsState.addTypes({inputs.front().getType()});

}

AndOp AndOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange inputs, /*optional*/bool twoState) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(inputs)>(inputs), std::forward<decltype(twoState)>(twoState));
  auto __res__ = ::llvm::dyn_cast<AndOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

AndOp AndOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange inputs, /*optional*/bool twoState) {
  return create(builder, builder.getLoc(), std::forward<decltype(inputs)>(inputs), std::forward<decltype(twoState)>(twoState));
}

void AndOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  odsState.addTypes({operands[0].getType()});

}

AndOp AndOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<AndOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

AndOp AndOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void AndOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  odsState.addTypes({operands[0].getType()});

}

AndOp AndOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<AndOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

AndOp AndOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult AndOp::verifyInvariantsImpl() {
  auto tblgen_twoState = getProperties().twoState; (void)tblgen_twoState;

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Comb1(*this, tblgen_twoState, "twoState")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Comb1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Comb2(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult AndOp::verifyInvariants() {
  if(::mlir::succeeded(verifyInvariantsImpl()) && ::mlir::succeeded(verify()))
    return ::mlir::success();
  return ::mlir::failure();
}

void AndOp::getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context) {
  results.add(canonicalize);
}

::mlir::ParseResult AndOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::llvm::SmallVector<::mlir::OpAsmParser::UnresolvedOperand, 4> inputsOperands;
  ::llvm::SMLoc inputsOperandsLoc;
  (void)inputsOperandsLoc;
  ::mlir::Type resultRawType{};
  ::llvm::ArrayRef<::mlir::Type> resultTypes(&resultRawType, 1);
  if (::mlir::succeeded(parser.parseOptionalKeyword("bin"))) {
    result.getOrAddProperties<AndOp::Properties>().twoState = parser.getBuilder().getUnitAttr();  }

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

  if (parser.parseType(resultRawType))
    return ::mlir::failure();
  result.addTypes(resultTypes);
  if (parser.resolveOperands(inputsOperands, resultTypes[0], inputsOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void AndOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  if ((getTwoStateAttr() && getTwoStateAttr() != ((false) ? ::mlir::OpBuilder((*this)->getContext()).getUnitAttr() : nullptr))) {
    _odsPrinter << ' ' << "bin";
  }
  _odsPrinter << ' ';
  _odsPrinter << getInputs();
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("twoState");
  {
     ::mlir::Builder odsBuilder(getContext());
     ::mlir::Attribute attr = getTwoStateAttr();
     if(attr && (attr == ((false) ? odsBuilder.getUnitAttr() : nullptr)))
       elidedAttrs.push_back("twoState");
  }
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
   _odsPrinter << getResult().getType();
}

void AndOp::getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects) {
}


} // namespace circt::comb
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::comb::AndOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::comb::detail::AndOpGenericAdaptorBase::Properties)

namespace circt::comb {


//===----------------------------------------------------------------------===//
// ::circt::comb::ConcatOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

ConcatOpGenericAdaptorBase::ConcatOpGenericAdaptorBase(ConcatOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

std::pair<unsigned, unsigned> ConcatOpGenericAdaptorBase::getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
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
ConcatOpAdaptor::ConcatOpAdaptor(ConcatOp op) : ConcatOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult ConcatOpAdaptor::verify(::mlir::Location loc) {
  return ::mlir::success();
}

std::pair<unsigned, unsigned> ConcatOp::getODSOperandIndexAndLength(unsigned index) {
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

::mlir::MutableOperandRange ConcatOp::getInputsMutable() {
  auto range = getODSOperandIndexAndLength(0);
  auto mutableRange = ::mlir::MutableOperandRange(getOperation(), range.first, range.second);
  return mutableRange;
}

::llvm::LogicalResult ConcatOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }
      return ::mlir::success();
}

::mlir::Attribute ConcatOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code ConcatOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine();
}

std::optional<mlir::Attribute> ConcatOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
  return std::nullopt;
}

void ConcatOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
}

void ConcatOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
}

::llvm::LogicalResult ConcatOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    return ::mlir::success();
}

void ConcatOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value lhs, Value rhs) {
      return build(odsBuilder, odsState, ValueRange{lhs, rhs});
    
}

ConcatOp ConcatOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, Value lhs, Value rhs) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(lhs)>(lhs), std::forward<decltype(rhs)>(rhs));
  auto __res__ = ::llvm::dyn_cast<ConcatOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ConcatOp ConcatOp::create(::mlir::ImplicitLocOpBuilder &builder, Value lhs, Value rhs) {
  return create(builder, builder.getLoc(), std::forward<decltype(lhs)>(lhs), std::forward<decltype(rhs)>(rhs));
}

ConcatOp ConcatOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, Value hd, ValueRange tl) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(hd)>(hd), std::forward<decltype(tl)>(tl));
  auto __res__ = ::llvm::dyn_cast<ConcatOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ConcatOp ConcatOp::create(::mlir::ImplicitLocOpBuilder &builder, Value hd, ValueRange tl) {
  return create(builder, builder.getLoc(), std::forward<decltype(hd)>(hd), std::forward<decltype(tl)>(tl));
}

void ConcatOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::ValueRange inputs) {
  odsState.addOperands(inputs);
  odsState.addTypes(result);
}

ConcatOp ConcatOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::ValueRange inputs) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(result)>(result), std::forward<decltype(inputs)>(inputs));
  auto __res__ = ::llvm::dyn_cast<ConcatOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ConcatOp ConcatOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::ValueRange inputs) {
  return create(builder, builder.getLoc(), std::forward<decltype(result)>(result), std::forward<decltype(inputs)>(inputs));
}

void ConcatOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

ConcatOp ConcatOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<ConcatOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ConcatOp ConcatOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void ConcatOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);

  ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
  if (::mlir::succeeded(ConcatOp::inferReturnTypes(odsBuilder.getContext(),
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

ConcatOp ConcatOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<ConcatOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ConcatOp ConcatOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void ConcatOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

ConcatOp ConcatOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<ConcatOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ConcatOp ConcatOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

void ConcatOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties &>(properties));
  odsState.addAttributes(discardableAttributes);

  ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
  if (::mlir::succeeded(ConcatOp::inferReturnTypes(odsBuilder.getContext(),
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

ConcatOp ConcatOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<ConcatOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ConcatOp ConcatOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult ConcatOp::verifyInvariantsImpl() {
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Comb1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Comb2(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult ConcatOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

void ConcatOp::getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context) {
  results.add(canonicalize);
}

::llvm::LogicalResult ConcatOp::setPropertiesFromParsedAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
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

void ConcatOp::getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects) {
}


} // namespace circt::comb
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::comb::ConcatOp)

namespace circt::comb {


//===----------------------------------------------------------------------===//
// ::circt::comb::DivSOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

DivSOpGenericAdaptorBase::DivSOpGenericAdaptorBase(DivSOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::mlir::UnitAttr DivSOpGenericAdaptorBase::getTwoStateAttr() {
  auto attr = ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(getProperties().twoState);
  if (!attr)
    attr = ((false) ? ::mlir::Builder(odsAttrs.getContext()).getUnitAttr() : nullptr);
  return attr;
}

bool DivSOpGenericAdaptorBase::getTwoState() {
  auto attr = getTwoStateAttr();
    if (!attr)
      return ((false) ? ::mlir::Builder(odsAttrs.getContext()).getUnitAttr() : nullptr) != nullptr;
  return attr != nullptr;
}


} // namespace detail
DivSOpAdaptor::DivSOpAdaptor(DivSOp op) : DivSOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult DivSOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_twoState = getProperties().twoState; (void)tblgen_twoState;

  if (tblgen_twoState && !((::llvm::isa<::mlir::UnitAttr>(tblgen_twoState))))
    return emitError(loc, "'comb.divs' op attribute 'twoState' failed to satisfy constraint: unit attribute");
  return ::mlir::success();
}

::llvm::LogicalResult DivSOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.twoState;
       auto attr = dict.get("twoState");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `twoState` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  return ::mlir::success();
}

::mlir::Attribute DivSOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.twoState;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("twoState",
                                       propStorage));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code DivSOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.twoState.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> DivSOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "twoState")
      return prop.twoState;
  return std::nullopt;
}

void DivSOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "twoState") {
       prop.twoState = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.twoState)>>(value);
       return;
    }
}

void DivSOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.twoState) attrs.append("twoState", prop.twoState);
}

::llvm::LogicalResult DivSOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getTwoStateAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Comb1(attr, "twoState", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult DivSOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readOptionalAttribute(prop.twoState)))
    return ::mlir::failure();
  return ::mlir::success();
}

void DivSOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;

  writer.writeOptionalAttribute(prop.twoState);
}

bool DivSOp::getTwoState() {
  auto attr = getTwoStateAttr();
    if (!attr)
      return ((false) ? ::mlir::Builder((*this)->getContext()).getUnitAttr() : nullptr) != nullptr;
  return attr != nullptr;
}

void DivSOp::setTwoState(bool attrValue) {
    auto &odsProp = getProperties().twoState;
    if (attrValue)
      odsProp = ((attrValue) ? ::mlir::Builder((*this)->getContext()).getUnitAttr() : nullptr);
    else
      odsProp = nullptr;
}

void DivSOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/::mlir::UnitAttr twoState) {
  odsState.addOperands(lhs);
  odsState.addOperands(rhs);
  if (twoState) {
    odsState.getOrAddProperties<Properties>().twoState = twoState;
  }
  odsState.addTypes(result);
}

DivSOp DivSOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/::mlir::UnitAttr twoState) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(result)>(result), std::forward<decltype(lhs)>(lhs), std::forward<decltype(rhs)>(rhs), std::forward<decltype(twoState)>(twoState));
  auto __res__ = ::llvm::dyn_cast<DivSOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

DivSOp DivSOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/::mlir::UnitAttr twoState) {
  return create(builder, builder.getLoc(), std::forward<decltype(result)>(result), std::forward<decltype(lhs)>(lhs), std::forward<decltype(rhs)>(rhs), std::forward<decltype(twoState)>(twoState));
}

void DivSOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/::mlir::UnitAttr twoState) {
  odsState.addOperands(lhs);
  odsState.addOperands(rhs);
  if (twoState) {
    odsState.getOrAddProperties<Properties>().twoState = twoState;
  }

        ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
        if (::mlir::succeeded(DivSOp::inferReturnTypes(odsBuilder.getContext(),
                      odsState.location, odsState.operands,
                      odsState.attributes.getDictionary(odsState.getContext()),
                      odsState.getRawProperties(),
                      odsState.regions, inferredReturnTypes)))
          odsState.addTypes(inferredReturnTypes);
        else
          ::mlir::detail::reportFatalInferReturnTypesError(odsState);
        
}

DivSOp DivSOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/::mlir::UnitAttr twoState) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(lhs)>(lhs), std::forward<decltype(rhs)>(rhs), std::forward<decltype(twoState)>(twoState));
  auto __res__ = ::llvm::dyn_cast<DivSOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

DivSOp DivSOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/::mlir::UnitAttr twoState) {
  return create(builder, builder.getLoc(), std::forward<decltype(lhs)>(lhs), std::forward<decltype(rhs)>(rhs), std::forward<decltype(twoState)>(twoState));
}

void DivSOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/::mlir::UnitAttr twoState) {
  odsState.addOperands(lhs);
  odsState.addOperands(rhs);
  if (twoState) {
    odsState.getOrAddProperties<Properties>().twoState = twoState;
  }
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

DivSOp DivSOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/::mlir::UnitAttr twoState) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(lhs)>(lhs), std::forward<decltype(rhs)>(rhs), std::forward<decltype(twoState)>(twoState));
  auto __res__ = ::llvm::dyn_cast<DivSOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

DivSOp DivSOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/::mlir::UnitAttr twoState) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(lhs)>(lhs), std::forward<decltype(rhs)>(rhs), std::forward<decltype(twoState)>(twoState));
}

void DivSOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/bool twoState) {
  odsState.addOperands(lhs);
  odsState.addOperands(rhs);
  if (twoState) {
    odsState.getOrAddProperties<Properties>().twoState = ((twoState) ? odsBuilder.getUnitAttr() : nullptr);
  }
  odsState.addTypes(result);
}

DivSOp DivSOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/bool twoState) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(result)>(result), std::forward<decltype(lhs)>(lhs), std::forward<decltype(rhs)>(rhs), std::forward<decltype(twoState)>(twoState));
  auto __res__ = ::llvm::dyn_cast<DivSOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

DivSOp DivSOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/bool twoState) {
  return create(builder, builder.getLoc(), std::forward<decltype(result)>(result), std::forward<decltype(lhs)>(lhs), std::forward<decltype(rhs)>(rhs), std::forward<decltype(twoState)>(twoState));
}

void DivSOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/bool twoState) {
  odsState.addOperands(lhs);
  odsState.addOperands(rhs);
  if (twoState) {
    odsState.getOrAddProperties<Properties>().twoState = ((twoState) ? odsBuilder.getUnitAttr() : nullptr);
  }

        ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
        if (::mlir::succeeded(DivSOp::inferReturnTypes(odsBuilder.getContext(),
                      odsState.location, odsState.operands,
                      odsState.attributes.getDictionary(odsState.getContext()),
                      odsState.getRawProperties(),
                      odsState.regions, inferredReturnTypes)))
          odsState.addTypes(inferredReturnTypes);
        else
          ::mlir::detail::reportFatalInferReturnTypesError(odsState);
        
}

DivSOp DivSOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/bool twoState) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(lhs)>(lhs), std::forward<decltype(rhs)>(rhs), std::forward<decltype(twoState)>(twoState));
  auto __res__ = ::llvm::dyn_cast<DivSOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

DivSOp DivSOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/bool twoState) {
  return create(builder, builder.getLoc(), std::forward<decltype(lhs)>(lhs), std::forward<decltype(rhs)>(rhs), std::forward<decltype(twoState)>(twoState));
}

void DivSOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/bool twoState) {
  odsState.addOperands(lhs);
  odsState.addOperands(rhs);
  if (twoState) {
    odsState.getOrAddProperties<Properties>().twoState = ((twoState) ? odsBuilder.getUnitAttr() : nullptr);
  }
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

DivSOp DivSOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/bool twoState) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(lhs)>(lhs), std::forward<decltype(rhs)>(rhs), std::forward<decltype(twoState)>(twoState));
  auto __res__ = ::llvm::dyn_cast<DivSOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

DivSOp DivSOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/bool twoState) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(lhs)>(lhs), std::forward<decltype(rhs)>(rhs), std::forward<decltype(twoState)>(twoState));
}

void DivSOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 2u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<DivSOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

DivSOp DivSOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<DivSOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

DivSOp DivSOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void DivSOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 2u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<DivSOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
  ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
  if (::mlir::succeeded(DivSOp::inferReturnTypes(odsBuilder.getContext(),
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

DivSOp DivSOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<DivSOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

DivSOp DivSOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void DivSOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 2u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

DivSOp DivSOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<DivSOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

DivSOp DivSOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

void DivSOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 2u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties &>(properties));
  odsState.addAttributes(discardableAttributes);

  ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
  if (::mlir::succeeded(DivSOp::inferReturnTypes(odsBuilder.getContext(),
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

DivSOp DivSOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<DivSOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

DivSOp DivSOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult DivSOp::verifyInvariantsImpl() {
  auto tblgen_twoState = getProperties().twoState; (void)tblgen_twoState;

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Comb1(*this, tblgen_twoState, "twoState")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Comb2(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSOperands(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Comb2(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Comb2(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult DivSOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::llvm::LogicalResult DivSOp::inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::PropertyRef properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes) {
  inferredReturnTypes.resize(1);
  ::mlir::Builder odsBuilder(context);
  if (operands.size() <= 0)
    return ::mlir::failure();
  ::mlir::Type odsInferredType0 = operands[0].getType();
  inferredReturnTypes[0] = odsInferredType0;
  return ::mlir::success();
}

::mlir::ParseResult DivSOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::OpAsmParser::UnresolvedOperand lhsRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> lhsOperands(&lhsRawOperand, 1);  ::llvm::SMLoc lhsOperandsLoc;
  (void)lhsOperandsLoc;
  ::mlir::OpAsmParser::UnresolvedOperand rhsRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> rhsOperands(&rhsRawOperand, 1);  ::llvm::SMLoc rhsOperandsLoc;
  (void)rhsOperandsLoc;
  ::mlir::Type resultRawType{};
  ::llvm::ArrayRef<::mlir::Type> resultTypes(&resultRawType, 1);
  if (::mlir::succeeded(parser.parseOptionalKeyword("bin"))) {
    result.getOrAddProperties<DivSOp::Properties>().twoState = parser.getBuilder().getUnitAttr();  }

  lhsOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(lhsRawOperand))
    return ::mlir::failure();
  if (parser.parseComma())
    return ::mlir::failure();

  rhsOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(rhsRawOperand))
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

  if (parser.parseType(resultRawType))
    return ::mlir::failure();
  result.addTypes(resultTypes);
  if (parser.resolveOperands(lhsOperands, resultTypes[0], lhsOperandsLoc, result.operands))
    return ::mlir::failure();
  if (parser.resolveOperands(rhsOperands, resultTypes[0], rhsOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void DivSOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  if ((getTwoStateAttr() && getTwoStateAttr() != ((false) ? ::mlir::OpBuilder((*this)->getContext()).getUnitAttr() : nullptr))) {
    _odsPrinter << ' ' << "bin";
  }
  _odsPrinter << ' ';
  _odsPrinter << getLhs();
  _odsPrinter << ",";
  _odsPrinter << ' ';
  _odsPrinter << getRhs();
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("twoState");
  {
     ::mlir::Builder odsBuilder(getContext());
     ::mlir::Attribute attr = getTwoStateAttr();
     if(attr && (attr == ((false) ? odsBuilder.getUnitAttr() : nullptr)))
       elidedAttrs.push_back("twoState");
  }
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
   _odsPrinter << getResult().getType();
}

void DivSOp::getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects) {
}


} // namespace circt::comb
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::comb::DivSOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::comb::detail::DivSOpGenericAdaptorBase::Properties)

namespace circt::comb {


//===----------------------------------------------------------------------===//
// ::circt::comb::DivUOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

DivUOpGenericAdaptorBase::DivUOpGenericAdaptorBase(DivUOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::mlir::UnitAttr DivUOpGenericAdaptorBase::getTwoStateAttr() {
  auto attr = ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(getProperties().twoState);
  if (!attr)
    attr = ((false) ? ::mlir::Builder(odsAttrs.getContext()).getUnitAttr() : nullptr);
  return attr;
}

bool DivUOpGenericAdaptorBase::getTwoState() {
  auto attr = getTwoStateAttr();
    if (!attr)
      return ((false) ? ::mlir::Builder(odsAttrs.getContext()).getUnitAttr() : nullptr) != nullptr;
  return attr != nullptr;
}


} // namespace detail
DivUOpAdaptor::DivUOpAdaptor(DivUOp op) : DivUOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult DivUOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_twoState = getProperties().twoState; (void)tblgen_twoState;

  if (tblgen_twoState && !((::llvm::isa<::mlir::UnitAttr>(tblgen_twoState))))
    return emitError(loc, "'comb.divu' op attribute 'twoState' failed to satisfy constraint: unit attribute");
  return ::mlir::success();
}

::llvm::LogicalResult DivUOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.twoState;
       auto attr = dict.get("twoState");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `twoState` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  return ::mlir::success();
}

::mlir::Attribute DivUOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.twoState;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("twoState",
                                       propStorage));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code DivUOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.twoState.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> DivUOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "twoState")
      return prop.twoState;
  return std::nullopt;
}

void DivUOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "twoState") {
       prop.twoState = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.twoState)>>(value);
       return;
    }
}

void DivUOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.twoState) attrs.append("twoState", prop.twoState);
}

::llvm::LogicalResult DivUOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getTwoStateAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Comb1(attr, "twoState", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult DivUOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readOptionalAttribute(prop.twoState)))
    return ::mlir::failure();
  return ::mlir::success();
}

void DivUOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;

  writer.writeOptionalAttribute(prop.twoState);
}

bool DivUOp::getTwoState() {
  auto attr = getTwoStateAttr();
    if (!attr)
      return ((false) ? ::mlir::Builder((*this)->getContext()).getUnitAttr() : nullptr) != nullptr;
  return attr != nullptr;
}

void DivUOp::setTwoState(bool attrValue) {
    auto &odsProp = getProperties().twoState;
    if (attrValue)
      odsProp = ((attrValue) ? ::mlir::Builder((*this)->getContext()).getUnitAttr() : nullptr);
    else
      odsProp = nullptr;
}

void DivUOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/::mlir::UnitAttr twoState) {
  odsState.addOperands(lhs);
  odsState.addOperands(rhs);
  if (twoState) {
    odsState.getOrAddProperties<Properties>().twoState = twoState;
  }
  odsState.addTypes(result);
}

DivUOp DivUOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/::mlir::UnitAttr twoState) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(result)>(result), std::forward<decltype(lhs)>(lhs), std::forward<decltype(rhs)>(rhs), std::forward<decltype(twoState)>(twoState));
  auto __res__ = ::llvm::dyn_cast<DivUOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

DivUOp DivUOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/::mlir::UnitAttr twoState) {
  return create(builder, builder.getLoc(), std::forward<decltype(result)>(result), std::forward<decltype(lhs)>(lhs), std::forward<decltype(rhs)>(rhs), std::forward<decltype(twoState)>(twoState));
}

void DivUOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/::mlir::UnitAttr twoState) {
  odsState.addOperands(lhs);
  odsState.addOperands(rhs);
  if (twoState) {
    odsState.getOrAddProperties<Properties>().twoState = twoState;
  }

        ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
        if (::mlir::succeeded(DivUOp::inferReturnTypes(odsBuilder.getContext(),
                      odsState.location, odsState.operands,
                      odsState.attributes.getDictionary(odsState.getContext()),
                      odsState.getRawProperties(),
                      odsState.regions, inferredReturnTypes)))
          odsState.addTypes(inferredReturnTypes);
        else
          ::mlir::detail::reportFatalInferReturnTypesError(odsState);
        
}

DivUOp DivUOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/::mlir::UnitAttr twoState) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(lhs)>(lhs), std::forward<decltype(rhs)>(rhs), std::forward<decltype(twoState)>(twoState));
  auto __res__ = ::llvm::dyn_cast<DivUOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

DivUOp DivUOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/::mlir::UnitAttr twoState) {
  return create(builder, builder.getLoc(), std::forward<decltype(lhs)>(lhs), std::forward<decltype(rhs)>(rhs), std::forward<decltype(twoState)>(twoState));
}

void DivUOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/::mlir::UnitAttr twoState) {
  odsState.addOperands(lhs);
  odsState.addOperands(rhs);
  if (twoState) {
    odsState.getOrAddProperties<Properties>().twoState = twoState;
  }
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

DivUOp DivUOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/::mlir::UnitAttr twoState) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(lhs)>(lhs), std::forward<decltype(rhs)>(rhs), std::forward<decltype(twoState)>(twoState));
  auto __res__ = ::llvm::dyn_cast<DivUOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

DivUOp DivUOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/::mlir::UnitAttr twoState) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(lhs)>(lhs), std::forward<decltype(rhs)>(rhs), std::forward<decltype(twoState)>(twoState));
}

void DivUOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/bool twoState) {
  odsState.addOperands(lhs);
  odsState.addOperands(rhs);
  if (twoState) {
    odsState.getOrAddProperties<Properties>().twoState = ((twoState) ? odsBuilder.getUnitAttr() : nullptr);
  }
  odsState.addTypes(result);
}

DivUOp DivUOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/bool twoState) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(result)>(result), std::forward<decltype(lhs)>(lhs), std::forward<decltype(rhs)>(rhs), std::forward<decltype(twoState)>(twoState));
  auto __res__ = ::llvm::dyn_cast<DivUOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

DivUOp DivUOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/bool twoState) {
  return create(builder, builder.getLoc(), std::forward<decltype(result)>(result), std::forward<decltype(lhs)>(lhs), std::forward<decltype(rhs)>(rhs), std::forward<decltype(twoState)>(twoState));
}

void DivUOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/bool twoState) {
  odsState.addOperands(lhs);
  odsState.addOperands(rhs);
  if (twoState) {
    odsState.getOrAddProperties<Properties>().twoState = ((twoState) ? odsBuilder.getUnitAttr() : nullptr);
  }

        ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
        if (::mlir::succeeded(DivUOp::inferReturnTypes(odsBuilder.getContext(),
                      odsState.location, odsState.operands,
                      odsState.attributes.getDictionary(odsState.getContext()),
                      odsState.getRawProperties(),
                      odsState.regions, inferredReturnTypes)))
          odsState.addTypes(inferredReturnTypes);
        else
          ::mlir::detail::reportFatalInferReturnTypesError(odsState);
        
}

DivUOp DivUOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/bool twoState) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(lhs)>(lhs), std::forward<decltype(rhs)>(rhs), std::forward<decltype(twoState)>(twoState));
  auto __res__ = ::llvm::dyn_cast<DivUOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

DivUOp DivUOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/bool twoState) {
  return create(builder, builder.getLoc(), std::forward<decltype(lhs)>(lhs), std::forward<decltype(rhs)>(rhs), std::forward<decltype(twoState)>(twoState));
}

void DivUOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/bool twoState) {
  odsState.addOperands(lhs);
  odsState.addOperands(rhs);
  if (twoState) {
    odsState.getOrAddProperties<Properties>().twoState = ((twoState) ? odsBuilder.getUnitAttr() : nullptr);
  }
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

DivUOp DivUOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/bool twoState) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(lhs)>(lhs), std::forward<decltype(rhs)>(rhs), std::forward<decltype(twoState)>(twoState));
  auto __res__ = ::llvm::dyn_cast<DivUOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

DivUOp DivUOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/bool twoState) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(lhs)>(lhs), std::forward<decltype(rhs)>(rhs), std::forward<decltype(twoState)>(twoState));
}

void DivUOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 2u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<DivUOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

DivUOp DivUOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<DivUOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

DivUOp DivUOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void DivUOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 2u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<DivUOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
  ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
  if (::mlir::succeeded(DivUOp::inferReturnTypes(odsBuilder.getContext(),
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

DivUOp DivUOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<DivUOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

DivUOp DivUOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void DivUOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 2u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

DivUOp DivUOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<DivUOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

DivUOp DivUOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

void DivUOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 2u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties &>(properties));
  odsState.addAttributes(discardableAttributes);

  ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
  if (::mlir::succeeded(DivUOp::inferReturnTypes(odsBuilder.getContext(),
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

DivUOp DivUOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<DivUOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

DivUOp DivUOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult DivUOp::verifyInvariantsImpl() {
  auto tblgen_twoState = getProperties().twoState; (void)tblgen_twoState;

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Comb1(*this, tblgen_twoState, "twoState")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Comb2(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSOperands(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Comb2(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Comb2(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult DivUOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

void DivUOp::getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context) {
  results.add(canonicalize);
}

::llvm::LogicalResult DivUOp::inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::PropertyRef properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes) {
  inferredReturnTypes.resize(1);
  ::mlir::Builder odsBuilder(context);
  if (operands.size() <= 0)
    return ::mlir::failure();
  ::mlir::Type odsInferredType0 = operands[0].getType();
  inferredReturnTypes[0] = odsInferredType0;
  return ::mlir::success();
}

::mlir::ParseResult DivUOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::OpAsmParser::UnresolvedOperand lhsRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> lhsOperands(&lhsRawOperand, 1);  ::llvm::SMLoc lhsOperandsLoc;
  (void)lhsOperandsLoc;
  ::mlir::OpAsmParser::UnresolvedOperand rhsRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> rhsOperands(&rhsRawOperand, 1);  ::llvm::SMLoc rhsOperandsLoc;
  (void)rhsOperandsLoc;
  ::mlir::Type resultRawType{};
  ::llvm::ArrayRef<::mlir::Type> resultTypes(&resultRawType, 1);
  if (::mlir::succeeded(parser.parseOptionalKeyword("bin"))) {
    result.getOrAddProperties<DivUOp::Properties>().twoState = parser.getBuilder().getUnitAttr();  }

  lhsOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(lhsRawOperand))
    return ::mlir::failure();
  if (parser.parseComma())
    return ::mlir::failure();

  rhsOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(rhsRawOperand))
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

  if (parser.parseType(resultRawType))
    return ::mlir::failure();
  result.addTypes(resultTypes);
  if (parser.resolveOperands(lhsOperands, resultTypes[0], lhsOperandsLoc, result.operands))
    return ::mlir::failure();
  if (parser.resolveOperands(rhsOperands, resultTypes[0], rhsOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void DivUOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  if ((getTwoStateAttr() && getTwoStateAttr() != ((false) ? ::mlir::OpBuilder((*this)->getContext()).getUnitAttr() : nullptr))) {
    _odsPrinter << ' ' << "bin";
  }
  _odsPrinter << ' ';
  _odsPrinter << getLhs();
  _odsPrinter << ",";
  _odsPrinter << ' ';
  _odsPrinter << getRhs();
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("twoState");
  {
     ::mlir::Builder odsBuilder(getContext());
     ::mlir::Attribute attr = getTwoStateAttr();
     if(attr && (attr == ((false) ? odsBuilder.getUnitAttr() : nullptr)))
       elidedAttrs.push_back("twoState");
  }
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
   _odsPrinter << getResult().getType();
}

void DivUOp::getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects) {
}


} // namespace circt::comb
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::comb::DivUOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::comb::detail::DivUOpGenericAdaptorBase::Properties)

namespace circt::comb {


//===----------------------------------------------------------------------===//
// ::circt::comb::ExtractOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

ExtractOpGenericAdaptorBase::ExtractOpGenericAdaptorBase(ExtractOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

uint32_t ExtractOpGenericAdaptorBase::getLowBit() {
  auto attr = getLowBitAttr();
  return attr.getValue().getZExtValue();
}


} // namespace detail
ExtractOpAdaptor::ExtractOpAdaptor(ExtractOp op) : ExtractOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult ExtractOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_lowBit = getProperties().lowBit; (void)tblgen_lowBit;
  if (!tblgen_lowBit) return emitError(loc, "'comb.extract' op requires attribute 'lowBit'");

  if (tblgen_lowBit && !(((::llvm::isa<::mlir::IntegerAttr>(tblgen_lowBit))) && ((::llvm::cast<::mlir::IntegerAttr>(tblgen_lowBit).getType().isSignlessInteger(32)))))
    return emitError(loc, "'comb.extract' op attribute 'lowBit' failed to satisfy constraint: 32-bit signless integer attribute");
  return ::mlir::success();
}

::llvm::LogicalResult ExtractOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.lowBit;
       auto attr = dict.get("lowBit");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `lowBit` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  return ::mlir::success();
}

::mlir::Attribute ExtractOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.lowBit;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("lowBit",
                                       propStorage));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code ExtractOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.lowBit.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> ExtractOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "lowBit")
      return prop.lowBit;
  return std::nullopt;
}

void ExtractOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "lowBit") {
       prop.lowBit = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.lowBit)>>(value);
       return;
    }
}

void ExtractOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.lowBit) attrs.append("lowBit", prop.lowBit);
}

::llvm::LogicalResult ExtractOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getLowBitAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Comb2(attr, "lowBit", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult ExtractOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.lowBit)))
    return ::mlir::failure();
  return ::mlir::success();
}

void ExtractOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.lowBit);
}

uint32_t ExtractOp::getLowBit() {
  auto attr = getLowBitAttr();
  return attr.getValue().getZExtValue();
}

void ExtractOp::setLowBit(uint32_t attrValue) {
  getProperties().lowBit = ::mlir::Builder((*this)->getContext()).getIntegerAttr(::mlir::Builder((*this)->getContext()).getIntegerType(32), attrValue);
}

void ExtractOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value lhs, int32_t lowBit, int32_t bitWidth) {
      auto resultType = odsBuilder.getIntegerType(bitWidth);
      return build(odsBuilder, odsState, resultType, lhs, lowBit);
    
}

ExtractOp ExtractOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, Value lhs, int32_t lowBit, int32_t bitWidth) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(lhs)>(lhs), std::forward<decltype(lowBit)>(lowBit), std::forward<decltype(bitWidth)>(bitWidth));
  auto __res__ = ::llvm::dyn_cast<ExtractOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ExtractOp ExtractOp::create(::mlir::ImplicitLocOpBuilder &builder, Value lhs, int32_t lowBit, int32_t bitWidth) {
  return create(builder, builder.getLoc(), std::forward<decltype(lhs)>(lhs), std::forward<decltype(lowBit)>(lowBit), std::forward<decltype(bitWidth)>(bitWidth));
}

void ExtractOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value input, ::mlir::IntegerAttr lowBit) {
  odsState.addOperands(input);
  odsState.getOrAddProperties<Properties>().lowBit = lowBit;
  odsState.addTypes(result);
}

ExtractOp ExtractOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value input, ::mlir::IntegerAttr lowBit) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(result)>(result), std::forward<decltype(input)>(input), std::forward<decltype(lowBit)>(lowBit));
  auto __res__ = ::llvm::dyn_cast<ExtractOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ExtractOp ExtractOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value input, ::mlir::IntegerAttr lowBit) {
  return create(builder, builder.getLoc(), std::forward<decltype(result)>(result), std::forward<decltype(input)>(input), std::forward<decltype(lowBit)>(lowBit));
}

void ExtractOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value input, ::mlir::IntegerAttr lowBit) {
  odsState.addOperands(input);
  odsState.getOrAddProperties<Properties>().lowBit = lowBit;
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

ExtractOp ExtractOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value input, ::mlir::IntegerAttr lowBit) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(input)>(input), std::forward<decltype(lowBit)>(lowBit));
  auto __res__ = ::llvm::dyn_cast<ExtractOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ExtractOp ExtractOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value input, ::mlir::IntegerAttr lowBit) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(input)>(input), std::forward<decltype(lowBit)>(lowBit));
}

void ExtractOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value input, uint32_t lowBit) {
  odsState.addOperands(input);
  odsState.getOrAddProperties<Properties>().lowBit = odsBuilder.getIntegerAttr(odsBuilder.getIntegerType(32), lowBit);
  odsState.addTypes(result);
}

ExtractOp ExtractOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value input, uint32_t lowBit) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(result)>(result), std::forward<decltype(input)>(input), std::forward<decltype(lowBit)>(lowBit));
  auto __res__ = ::llvm::dyn_cast<ExtractOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ExtractOp ExtractOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value input, uint32_t lowBit) {
  return create(builder, builder.getLoc(), std::forward<decltype(result)>(result), std::forward<decltype(input)>(input), std::forward<decltype(lowBit)>(lowBit));
}

void ExtractOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value input, uint32_t lowBit) {
  odsState.addOperands(input);
  odsState.getOrAddProperties<Properties>().lowBit = odsBuilder.getIntegerAttr(odsBuilder.getIntegerType(32), lowBit);
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

ExtractOp ExtractOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value input, uint32_t lowBit) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(input)>(input), std::forward<decltype(lowBit)>(lowBit));
  auto __res__ = ::llvm::dyn_cast<ExtractOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ExtractOp ExtractOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value input, uint32_t lowBit) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(input)>(input), std::forward<decltype(lowBit)>(lowBit));
}

void ExtractOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<ExtractOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

ExtractOp ExtractOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<ExtractOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ExtractOp ExtractOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void ExtractOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

ExtractOp ExtractOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<ExtractOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ExtractOp ExtractOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult ExtractOp::verifyInvariantsImpl() {
  auto tblgen_lowBit = getProperties().lowBit; (void)tblgen_lowBit;
  if (!tblgen_lowBit) return emitOpError("requires attribute 'lowBit'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Comb2(*this, tblgen_lowBit, "lowBit")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Comb2(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Comb2(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult ExtractOp::verifyInvariants() {
  if(::mlir::succeeded(verifyInvariantsImpl()) && ::mlir::succeeded(verify()))
    return ::mlir::success();
  return ::mlir::failure();
}

void ExtractOp::getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context) {
  results.add(canonicalize);
}

::mlir::ParseResult ExtractOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::OpAsmParser::UnresolvedOperand inputRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> inputOperands(&inputRawOperand, 1);  ::llvm::SMLoc inputOperandsLoc;
  (void)inputOperandsLoc;
  ::mlir::IntegerAttr lowBitAttr;
  ::llvm::ArrayRef<::mlir::Type> inputTypes;
  ::llvm::ArrayRef<::mlir::Type> resultTypes;

  inputOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(inputRawOperand))
    return ::mlir::failure();
  if (parser.parseKeyword("from"))
    return ::mlir::failure();

  if (parser.parseCustomAttributeWithFallback(lowBitAttr, parser.getBuilder().getIntegerType(32))) {
    return ::mlir::failure();
  }
  if (lowBitAttr) result.getOrAddProperties<ExtractOp::Properties>().lowBit = lowBitAttr;
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

  ::mlir::FunctionType input__result_functionType;
  if (parser.parseType(input__result_functionType))
    return ::mlir::failure();
  inputTypes = input__result_functionType.getInputs();
  resultTypes = input__result_functionType.getResults();
  result.addTypes(resultTypes);
  if (parser.resolveOperands(inputOperands, inputTypes, inputOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void ExtractOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter << getInput();
  _odsPrinter << ' ' << "from";
  _odsPrinter << ' ';
  _odsPrinter.printAttributeWithoutType(getLowBitAttr());
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("lowBit");
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
  _odsPrinter.printFunctionalType(::llvm::ArrayRef<::mlir::Type>(getInput().getType()), ::llvm::ArrayRef<::mlir::Type>(getResult().getType()));
}

void ExtractOp::getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects) {
}


} // namespace circt::comb
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::comb::ExtractOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::comb::detail::ExtractOpGenericAdaptorBase::Properties)

namespace circt::comb {


//===----------------------------------------------------------------------===//
// ::circt::comb::ICmpOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

ICmpOpGenericAdaptorBase::ICmpOpGenericAdaptorBase(ICmpOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

circt::comb::ICmpPredicate ICmpOpGenericAdaptorBase::getPredicate() {
  auto attr = getPredicateAttr();
  return attr.getValue();
}

::mlir::UnitAttr ICmpOpGenericAdaptorBase::getTwoStateAttr() {
  auto attr = ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(getProperties().twoState);
  if (!attr)
    attr = ((false) ? ::mlir::Builder(odsAttrs.getContext()).getUnitAttr() : nullptr);
  return attr;
}

bool ICmpOpGenericAdaptorBase::getTwoState() {
  auto attr = getTwoStateAttr();
    if (!attr)
      return ((false) ? ::mlir::Builder(odsAttrs.getContext()).getUnitAttr() : nullptr) != nullptr;
  return attr != nullptr;
}


} // namespace detail
ICmpOpAdaptor::ICmpOpAdaptor(ICmpOp op) : ICmpOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult ICmpOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_predicate = getProperties().predicate; (void)tblgen_predicate;
  if (!tblgen_predicate) return emitError(loc, "'comb.icmp' op requires attribute 'predicate'");
  auto tblgen_twoState = getProperties().twoState; (void)tblgen_twoState;

  if (tblgen_predicate && !((::llvm::isa<circt::comb::ICmpPredicateAttr>(tblgen_predicate))))
    return emitError(loc, "'comb.icmp' op attribute 'predicate' failed to satisfy constraint: hw.icmp comparison predicate");

  if (tblgen_twoState && !((::llvm::isa<::mlir::UnitAttr>(tblgen_twoState))))
    return emitError(loc, "'comb.icmp' op attribute 'twoState' failed to satisfy constraint: unit attribute");
  return ::mlir::success();
}

::llvm::LogicalResult ICmpOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.predicate;
       auto attr = dict.get("predicate");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `predicate` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.twoState;
       auto attr = dict.get("twoState");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `twoState` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  return ::mlir::success();
}

::mlir::Attribute ICmpOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.predicate;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("predicate",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.twoState;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("twoState",
                                       propStorage));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code ICmpOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.predicate.getAsOpaquePointer()), 
    llvm::hash_value(prop.twoState.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> ICmpOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "predicate")
      return prop.predicate;

    if (name == "twoState")
      return prop.twoState;
  return std::nullopt;
}

void ICmpOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "predicate") {
       prop.predicate = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.predicate)>>(value);
       return;
    }

    if (name == "twoState") {
       prop.twoState = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.twoState)>>(value);
       return;
    }
}

void ICmpOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.predicate) attrs.append("predicate", prop.predicate);

    if (prop.twoState) attrs.append("twoState", prop.twoState);
}

::llvm::LogicalResult ICmpOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getPredicateAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Comb3(attr, "predicate", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getTwoStateAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Comb1(attr, "twoState", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult ICmpOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.predicate)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readOptionalAttribute(prop.twoState)))
    return ::mlir::failure();
  return ::mlir::success();
}

void ICmpOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.predicate);

  writer.writeOptionalAttribute(prop.twoState);
}

circt::comb::ICmpPredicate ICmpOp::getPredicate() {
  auto attr = getPredicateAttr();
  return attr.getValue();
}

bool ICmpOp::getTwoState() {
  auto attr = getTwoStateAttr();
    if (!attr)
      return ((false) ? ::mlir::Builder((*this)->getContext()).getUnitAttr() : nullptr) != nullptr;
  return attr != nullptr;
}

void ICmpOp::setPredicate(circt::comb::ICmpPredicate attrValue) {
  getProperties().predicate = circt::comb::ICmpPredicateAttr::get(::mlir::Builder((*this)->getContext()).getContext(), attrValue);
}

void ICmpOp::setTwoState(bool attrValue) {
    auto &odsProp = getProperties().twoState;
    if (attrValue)
      odsProp = ((attrValue) ? ::mlir::Builder((*this)->getContext()).getUnitAttr() : nullptr);
    else
      odsProp = nullptr;
}

void ICmpOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, circt::comb::ICmpPredicateAttr predicate, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/::mlir::UnitAttr twoState) {
  odsState.addOperands(lhs);
  odsState.addOperands(rhs);
  odsState.getOrAddProperties<Properties>().predicate = predicate;
  if (twoState) {
    odsState.getOrAddProperties<Properties>().twoState = twoState;
  }
  odsState.addTypes(result);
}

ICmpOp ICmpOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, circt::comb::ICmpPredicateAttr predicate, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/::mlir::UnitAttr twoState) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(result)>(result), std::forward<decltype(predicate)>(predicate), std::forward<decltype(lhs)>(lhs), std::forward<decltype(rhs)>(rhs), std::forward<decltype(twoState)>(twoState));
  auto __res__ = ::llvm::dyn_cast<ICmpOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ICmpOp ICmpOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, circt::comb::ICmpPredicateAttr predicate, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/::mlir::UnitAttr twoState) {
  return create(builder, builder.getLoc(), std::forward<decltype(result)>(result), std::forward<decltype(predicate)>(predicate), std::forward<decltype(lhs)>(lhs), std::forward<decltype(rhs)>(rhs), std::forward<decltype(twoState)>(twoState));
}

void ICmpOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, circt::comb::ICmpPredicateAttr predicate, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/::mlir::UnitAttr twoState) {
  odsState.addOperands(lhs);
  odsState.addOperands(rhs);
  odsState.getOrAddProperties<Properties>().predicate = predicate;
  if (twoState) {
    odsState.getOrAddProperties<Properties>().twoState = twoState;
  }

        ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
        if (::mlir::succeeded(ICmpOp::inferReturnTypes(odsBuilder.getContext(),
                      odsState.location, odsState.operands,
                      odsState.attributes.getDictionary(odsState.getContext()),
                      odsState.getRawProperties(),
                      odsState.regions, inferredReturnTypes)))
          odsState.addTypes(inferredReturnTypes);
        else
          ::mlir::detail::reportFatalInferReturnTypesError(odsState);
        
}

ICmpOp ICmpOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, circt::comb::ICmpPredicateAttr predicate, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/::mlir::UnitAttr twoState) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(predicate)>(predicate), std::forward<decltype(lhs)>(lhs), std::forward<decltype(rhs)>(rhs), std::forward<decltype(twoState)>(twoState));
  auto __res__ = ::llvm::dyn_cast<ICmpOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ICmpOp ICmpOp::create(::mlir::ImplicitLocOpBuilder &builder, circt::comb::ICmpPredicateAttr predicate, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/::mlir::UnitAttr twoState) {
  return create(builder, builder.getLoc(), std::forward<decltype(predicate)>(predicate), std::forward<decltype(lhs)>(lhs), std::forward<decltype(rhs)>(rhs), std::forward<decltype(twoState)>(twoState));
}

void ICmpOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, circt::comb::ICmpPredicateAttr predicate, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/::mlir::UnitAttr twoState) {
  odsState.addOperands(lhs);
  odsState.addOperands(rhs);
  odsState.getOrAddProperties<Properties>().predicate = predicate;
  if (twoState) {
    odsState.getOrAddProperties<Properties>().twoState = twoState;
  }
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

ICmpOp ICmpOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, circt::comb::ICmpPredicateAttr predicate, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/::mlir::UnitAttr twoState) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(predicate)>(predicate), std::forward<decltype(lhs)>(lhs), std::forward<decltype(rhs)>(rhs), std::forward<decltype(twoState)>(twoState));
  auto __res__ = ::llvm::dyn_cast<ICmpOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ICmpOp ICmpOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, circt::comb::ICmpPredicateAttr predicate, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/::mlir::UnitAttr twoState) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(predicate)>(predicate), std::forward<decltype(lhs)>(lhs), std::forward<decltype(rhs)>(rhs), std::forward<decltype(twoState)>(twoState));
}

void ICmpOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, circt::comb::ICmpPredicate predicate, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/bool twoState) {
  odsState.addOperands(lhs);
  odsState.addOperands(rhs);
  odsState.getOrAddProperties<Properties>().predicate = circt::comb::ICmpPredicateAttr::get(odsBuilder.getContext(), predicate);
  if (twoState) {
    odsState.getOrAddProperties<Properties>().twoState = ((twoState) ? odsBuilder.getUnitAttr() : nullptr);
  }
  odsState.addTypes(result);
}

ICmpOp ICmpOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, circt::comb::ICmpPredicate predicate, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/bool twoState) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(result)>(result), std::forward<decltype(predicate)>(predicate), std::forward<decltype(lhs)>(lhs), std::forward<decltype(rhs)>(rhs), std::forward<decltype(twoState)>(twoState));
  auto __res__ = ::llvm::dyn_cast<ICmpOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ICmpOp ICmpOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, circt::comb::ICmpPredicate predicate, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/bool twoState) {
  return create(builder, builder.getLoc(), std::forward<decltype(result)>(result), std::forward<decltype(predicate)>(predicate), std::forward<decltype(lhs)>(lhs), std::forward<decltype(rhs)>(rhs), std::forward<decltype(twoState)>(twoState));
}

void ICmpOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, circt::comb::ICmpPredicate predicate, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/bool twoState) {
  odsState.addOperands(lhs);
  odsState.addOperands(rhs);
  odsState.getOrAddProperties<Properties>().predicate = circt::comb::ICmpPredicateAttr::get(odsBuilder.getContext(), predicate);
  if (twoState) {
    odsState.getOrAddProperties<Properties>().twoState = ((twoState) ? odsBuilder.getUnitAttr() : nullptr);
  }

        ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
        if (::mlir::succeeded(ICmpOp::inferReturnTypes(odsBuilder.getContext(),
                      odsState.location, odsState.operands,
                      odsState.attributes.getDictionary(odsState.getContext()),
                      odsState.getRawProperties(),
                      odsState.regions, inferredReturnTypes)))
          odsState.addTypes(inferredReturnTypes);
        else
          ::mlir::detail::reportFatalInferReturnTypesError(odsState);
        
}

ICmpOp ICmpOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, circt::comb::ICmpPredicate predicate, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/bool twoState) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(predicate)>(predicate), std::forward<decltype(lhs)>(lhs), std::forward<decltype(rhs)>(rhs), std::forward<decltype(twoState)>(twoState));
  auto __res__ = ::llvm::dyn_cast<ICmpOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ICmpOp ICmpOp::create(::mlir::ImplicitLocOpBuilder &builder, circt::comb::ICmpPredicate predicate, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/bool twoState) {
  return create(builder, builder.getLoc(), std::forward<decltype(predicate)>(predicate), std::forward<decltype(lhs)>(lhs), std::forward<decltype(rhs)>(rhs), std::forward<decltype(twoState)>(twoState));
}

void ICmpOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, circt::comb::ICmpPredicate predicate, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/bool twoState) {
  odsState.addOperands(lhs);
  odsState.addOperands(rhs);
  odsState.getOrAddProperties<Properties>().predicate = circt::comb::ICmpPredicateAttr::get(odsBuilder.getContext(), predicate);
  if (twoState) {
    odsState.getOrAddProperties<Properties>().twoState = ((twoState) ? odsBuilder.getUnitAttr() : nullptr);
  }
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

ICmpOp ICmpOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, circt::comb::ICmpPredicate predicate, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/bool twoState) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(predicate)>(predicate), std::forward<decltype(lhs)>(lhs), std::forward<decltype(rhs)>(rhs), std::forward<decltype(twoState)>(twoState));
  auto __res__ = ::llvm::dyn_cast<ICmpOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ICmpOp ICmpOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, circt::comb::ICmpPredicate predicate, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/bool twoState) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(predicate)>(predicate), std::forward<decltype(lhs)>(lhs), std::forward<decltype(rhs)>(rhs), std::forward<decltype(twoState)>(twoState));
}

void ICmpOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 2u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<ICmpOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

ICmpOp ICmpOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<ICmpOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ICmpOp ICmpOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void ICmpOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 2u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<ICmpOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
  ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
  if (::mlir::succeeded(ICmpOp::inferReturnTypes(odsBuilder.getContext(),
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

ICmpOp ICmpOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<ICmpOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ICmpOp ICmpOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void ICmpOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 2u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

ICmpOp ICmpOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<ICmpOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ICmpOp ICmpOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

void ICmpOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 2u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties &>(properties));
  odsState.addAttributes(discardableAttributes);

  ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
  if (::mlir::succeeded(ICmpOp::inferReturnTypes(odsBuilder.getContext(),
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

ICmpOp ICmpOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<ICmpOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ICmpOp ICmpOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult ICmpOp::verifyInvariantsImpl() {
  auto tblgen_predicate = getProperties().predicate; (void)tblgen_predicate;
  if (!tblgen_predicate) return emitOpError("requires attribute 'predicate'");
  auto tblgen_twoState = getProperties().twoState; (void)tblgen_twoState;

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Comb3(*this, tblgen_predicate, "predicate")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Comb1(*this, tblgen_twoState, "twoState")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Comb2(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSOperands(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Comb2(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Comb3(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult ICmpOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

void ICmpOp::getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context) {
  results.add(canonicalize);
}

::llvm::LogicalResult ICmpOp::inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::PropertyRef properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes) {
  inferredReturnTypes.resize(1);
  ::mlir::Builder odsBuilder(context);
  ::mlir::Type odsInferredType0 = odsBuilder.getIntegerType(1);
  inferredReturnTypes[0] = odsInferredType0;
  return ::mlir::success();
}

::mlir::ParseResult ICmpOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  circt::comb::ICmpPredicateAttr predicateAttr;
  ::mlir::OpAsmParser::UnresolvedOperand lhsRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> lhsOperands(&lhsRawOperand, 1);  ::llvm::SMLoc lhsOperandsLoc;
  (void)lhsOperandsLoc;
  ::mlir::OpAsmParser::UnresolvedOperand rhsRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> rhsOperands(&rhsRawOperand, 1);  ::llvm::SMLoc rhsOperandsLoc;
  (void)rhsOperandsLoc;
  ::mlir::Type lhsRawType{};
  ::llvm::ArrayRef<::mlir::Type> lhsTypes(&lhsRawType, 1);
  if (::mlir::succeeded(parser.parseOptionalKeyword("bin"))) {
    result.getOrAddProperties<ICmpOp::Properties>().twoState = parser.getBuilder().getUnitAttr();  }

  {
    ::llvm::StringRef attrStr;
    ::mlir::NamedAttrList attrStorage;
    auto loc = parser.getCurrentLocation();
    if (parser.parseOptionalKeyword(&attrStr, {"eq","ne","slt","sle","sgt","sge","ult","ule","ugt","uge","ceq","cne","weq","wne"})) {
      ::mlir::StringAttr attrVal;
      ::mlir::OptionalParseResult parseResult =
        parser.parseOptionalAttribute(attrVal,
                                      parser.getBuilder().getNoneType(),
                                      "predicate", attrStorage);
      if (parseResult.has_value()) {
        if (failed(*parseResult))
          return ::mlir::failure();
        attrStr = attrVal.getValue();
      } else {
        return parser.emitError(loc, "expected string or keyword containing one of the following enum values for attribute 'predicate' [eq, ne, slt, sle, sgt, sge, ult, ule, ugt, uge, ceq, cne, weq, wne]");
      }
    }
    if (!attrStr.empty()) {
      auto attrOptional = circt::comb::symbolizeICmpPredicate(attrStr);
      if (!attrOptional)
        return parser.emitError(loc, "invalid ")
               << "predicate attribute specification: \"" << attrStr << '"';;

      predicateAttr = circt::comb::ICmpPredicateAttr::get(parser.getBuilder().getContext(), *attrOptional);
        result.getOrAddProperties<ICmpOp::Properties>().predicate = predicateAttr;
    }
  }

  lhsOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(lhsRawOperand))
    return ::mlir::failure();
  if (parser.parseComma())
    return ::mlir::failure();

  rhsOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(rhsRawOperand))
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

  if (parser.parseType(lhsRawType))
    return ::mlir::failure();
  ::mlir::Type odsBuildableType0 = parser.getBuilder().getIntegerType(1);
  result.addTypes(odsBuildableType0);
  if (parser.resolveOperands(lhsOperands, lhsTypes, lhsOperandsLoc, result.operands))
    return ::mlir::failure();
  if (parser.resolveOperands(rhsOperands, lhsTypes[0], rhsOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void ICmpOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  if ((getTwoStateAttr() && getTwoStateAttr() != ((false) ? ::mlir::OpBuilder((*this)->getContext()).getUnitAttr() : nullptr))) {
    _odsPrinter << ' ' << "bin";
  }
  _odsPrinter << ' ';

  {
    auto caseValue = getPredicate();
    auto caseValueStr = stringifyICmpPredicate(caseValue);
    _odsPrinter << caseValueStr;
  }
  _odsPrinter << ' ';
  _odsPrinter << getLhs();
  _odsPrinter << ",";
  _odsPrinter << ' ';
  _odsPrinter << getRhs();
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("twoState");
  elidedAttrs.push_back("predicate");
  {
     ::mlir::Builder odsBuilder(getContext());
     ::mlir::Attribute attr = getTwoStateAttr();
     if(attr && (attr == ((false) ? odsBuilder.getUnitAttr() : nullptr)))
       elidedAttrs.push_back("twoState");
  }
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
   _odsPrinter << getLhs().getType();
}

void ICmpOp::getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects) {
}


} // namespace circt::comb
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::comb::ICmpOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::comb::detail::ICmpOpGenericAdaptorBase::Properties)

namespace circt::comb {


//===----------------------------------------------------------------------===//
// ::circt::comb::ModSOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

ModSOpGenericAdaptorBase::ModSOpGenericAdaptorBase(ModSOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::mlir::UnitAttr ModSOpGenericAdaptorBase::getTwoStateAttr() {
  auto attr = ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(getProperties().twoState);
  if (!attr)
    attr = ((false) ? ::mlir::Builder(odsAttrs.getContext()).getUnitAttr() : nullptr);
  return attr;
}

bool ModSOpGenericAdaptorBase::getTwoState() {
  auto attr = getTwoStateAttr();
    if (!attr)
      return ((false) ? ::mlir::Builder(odsAttrs.getContext()).getUnitAttr() : nullptr) != nullptr;
  return attr != nullptr;
}


} // namespace detail
ModSOpAdaptor::ModSOpAdaptor(ModSOp op) : ModSOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult ModSOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_twoState = getProperties().twoState; (void)tblgen_twoState;

  if (tblgen_twoState && !((::llvm::isa<::mlir::UnitAttr>(tblgen_twoState))))
    return emitError(loc, "'comb.mods' op attribute 'twoState' failed to satisfy constraint: unit attribute");
  return ::mlir::success();
}

::llvm::LogicalResult ModSOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.twoState;
       auto attr = dict.get("twoState");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `twoState` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  return ::mlir::success();
}

::mlir::Attribute ModSOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.twoState;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("twoState",
                                       propStorage));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code ModSOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.twoState.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> ModSOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "twoState")
      return prop.twoState;
  return std::nullopt;
}

void ModSOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "twoState") {
       prop.twoState = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.twoState)>>(value);
       return;
    }
}

void ModSOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.twoState) attrs.append("twoState", prop.twoState);
}

::llvm::LogicalResult ModSOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getTwoStateAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Comb1(attr, "twoState", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult ModSOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readOptionalAttribute(prop.twoState)))
    return ::mlir::failure();
  return ::mlir::success();
}

void ModSOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;

  writer.writeOptionalAttribute(prop.twoState);
}

bool ModSOp::getTwoState() {
  auto attr = getTwoStateAttr();
    if (!attr)
      return ((false) ? ::mlir::Builder((*this)->getContext()).getUnitAttr() : nullptr) != nullptr;
  return attr != nullptr;
}

void ModSOp::setTwoState(bool attrValue) {
    auto &odsProp = getProperties().twoState;
    if (attrValue)
      odsProp = ((attrValue) ? ::mlir::Builder((*this)->getContext()).getUnitAttr() : nullptr);
    else
      odsProp = nullptr;
}

void ModSOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/::mlir::UnitAttr twoState) {
  odsState.addOperands(lhs);
  odsState.addOperands(rhs);
  if (twoState) {
    odsState.getOrAddProperties<Properties>().twoState = twoState;
  }
  odsState.addTypes(result);
}

ModSOp ModSOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/::mlir::UnitAttr twoState) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(result)>(result), std::forward<decltype(lhs)>(lhs), std::forward<decltype(rhs)>(rhs), std::forward<decltype(twoState)>(twoState));
  auto __res__ = ::llvm::dyn_cast<ModSOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ModSOp ModSOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/::mlir::UnitAttr twoState) {
  return create(builder, builder.getLoc(), std::forward<decltype(result)>(result), std::forward<decltype(lhs)>(lhs), std::forward<decltype(rhs)>(rhs), std::forward<decltype(twoState)>(twoState));
}

void ModSOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/::mlir::UnitAttr twoState) {
  odsState.addOperands(lhs);
  odsState.addOperands(rhs);
  if (twoState) {
    odsState.getOrAddProperties<Properties>().twoState = twoState;
  }

        ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
        if (::mlir::succeeded(ModSOp::inferReturnTypes(odsBuilder.getContext(),
                      odsState.location, odsState.operands,
                      odsState.attributes.getDictionary(odsState.getContext()),
                      odsState.getRawProperties(),
                      odsState.regions, inferredReturnTypes)))
          odsState.addTypes(inferredReturnTypes);
        else
          ::mlir::detail::reportFatalInferReturnTypesError(odsState);
        
}

ModSOp ModSOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/::mlir::UnitAttr twoState) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(lhs)>(lhs), std::forward<decltype(rhs)>(rhs), std::forward<decltype(twoState)>(twoState));
  auto __res__ = ::llvm::dyn_cast<ModSOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ModSOp ModSOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/::mlir::UnitAttr twoState) {
  return create(builder, builder.getLoc(), std::forward<decltype(lhs)>(lhs), std::forward<decltype(rhs)>(rhs), std::forward<decltype(twoState)>(twoState));
}

void ModSOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/::mlir::UnitAttr twoState) {
  odsState.addOperands(lhs);
  odsState.addOperands(rhs);
  if (twoState) {
    odsState.getOrAddProperties<Properties>().twoState = twoState;
  }
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

ModSOp ModSOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/::mlir::UnitAttr twoState) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(lhs)>(lhs), std::forward<decltype(rhs)>(rhs), std::forward<decltype(twoState)>(twoState));
  auto __res__ = ::llvm::dyn_cast<ModSOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ModSOp ModSOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/::mlir::UnitAttr twoState) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(lhs)>(lhs), std::forward<decltype(rhs)>(rhs), std::forward<decltype(twoState)>(twoState));
}

void ModSOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/bool twoState) {
  odsState.addOperands(lhs);
  odsState.addOperands(rhs);
  if (twoState) {
    odsState.getOrAddProperties<Properties>().twoState = ((twoState) ? odsBuilder.getUnitAttr() : nullptr);
  }
  odsState.addTypes(result);
}

ModSOp ModSOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/bool twoState) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(result)>(result), std::forward<decltype(lhs)>(lhs), std::forward<decltype(rhs)>(rhs), std::forward<decltype(twoState)>(twoState));
  auto __res__ = ::llvm::dyn_cast<ModSOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ModSOp ModSOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/bool twoState) {
  return create(builder, builder.getLoc(), std::forward<decltype(result)>(result), std::forward<decltype(lhs)>(lhs), std::forward<decltype(rhs)>(rhs), std::forward<decltype(twoState)>(twoState));
}

void ModSOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/bool twoState) {
  odsState.addOperands(lhs);
  odsState.addOperands(rhs);
  if (twoState) {
    odsState.getOrAddProperties<Properties>().twoState = ((twoState) ? odsBuilder.getUnitAttr() : nullptr);
  }

        ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
        if (::mlir::succeeded(ModSOp::inferReturnTypes(odsBuilder.getContext(),
                      odsState.location, odsState.operands,
                      odsState.attributes.getDictionary(odsState.getContext()),
                      odsState.getRawProperties(),
                      odsState.regions, inferredReturnTypes)))
          odsState.addTypes(inferredReturnTypes);
        else
          ::mlir::detail::reportFatalInferReturnTypesError(odsState);
        
}

ModSOp ModSOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/bool twoState) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(lhs)>(lhs), std::forward<decltype(rhs)>(rhs), std::forward<decltype(twoState)>(twoState));
  auto __res__ = ::llvm::dyn_cast<ModSOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ModSOp ModSOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/bool twoState) {
  return create(builder, builder.getLoc(), std::forward<decltype(lhs)>(lhs), std::forward<decltype(rhs)>(rhs), std::forward<decltype(twoState)>(twoState));
}

void ModSOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/bool twoState) {
  odsState.addOperands(lhs);
  odsState.addOperands(rhs);
  if (twoState) {
    odsState.getOrAddProperties<Properties>().twoState = ((twoState) ? odsBuilder.getUnitAttr() : nullptr);
  }
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

ModSOp ModSOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/bool twoState) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(lhs)>(lhs), std::forward<decltype(rhs)>(rhs), std::forward<decltype(twoState)>(twoState));
  auto __res__ = ::llvm::dyn_cast<ModSOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ModSOp ModSOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/bool twoState) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(lhs)>(lhs), std::forward<decltype(rhs)>(rhs), std::forward<decltype(twoState)>(twoState));
}

void ModSOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 2u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<ModSOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

ModSOp ModSOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<ModSOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ModSOp ModSOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void ModSOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 2u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<ModSOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
  ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
  if (::mlir::succeeded(ModSOp::inferReturnTypes(odsBuilder.getContext(),
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

ModSOp ModSOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<ModSOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ModSOp ModSOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void ModSOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 2u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

ModSOp ModSOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<ModSOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ModSOp ModSOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

void ModSOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 2u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties &>(properties));
  odsState.addAttributes(discardableAttributes);

  ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
  if (::mlir::succeeded(ModSOp::inferReturnTypes(odsBuilder.getContext(),
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

ModSOp ModSOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<ModSOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ModSOp ModSOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult ModSOp::verifyInvariantsImpl() {
  auto tblgen_twoState = getProperties().twoState; (void)tblgen_twoState;

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Comb1(*this, tblgen_twoState, "twoState")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Comb2(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSOperands(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Comb2(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Comb2(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult ModSOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::llvm::LogicalResult ModSOp::inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::PropertyRef properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes) {
  inferredReturnTypes.resize(1);
  ::mlir::Builder odsBuilder(context);
  if (operands.size() <= 0)
    return ::mlir::failure();
  ::mlir::Type odsInferredType0 = operands[0].getType();
  inferredReturnTypes[0] = odsInferredType0;
  return ::mlir::success();
}

::mlir::ParseResult ModSOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::OpAsmParser::UnresolvedOperand lhsRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> lhsOperands(&lhsRawOperand, 1);  ::llvm::SMLoc lhsOperandsLoc;
  (void)lhsOperandsLoc;
  ::mlir::OpAsmParser::UnresolvedOperand rhsRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> rhsOperands(&rhsRawOperand, 1);  ::llvm::SMLoc rhsOperandsLoc;
  (void)rhsOperandsLoc;
  ::mlir::Type resultRawType{};
  ::llvm::ArrayRef<::mlir::Type> resultTypes(&resultRawType, 1);
  if (::mlir::succeeded(parser.parseOptionalKeyword("bin"))) {
    result.getOrAddProperties<ModSOp::Properties>().twoState = parser.getBuilder().getUnitAttr();  }

  lhsOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(lhsRawOperand))
    return ::mlir::failure();
  if (parser.parseComma())
    return ::mlir::failure();

  rhsOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(rhsRawOperand))
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

  if (parser.parseType(resultRawType))
    return ::mlir::failure();
  result.addTypes(resultTypes);
  if (parser.resolveOperands(lhsOperands, resultTypes[0], lhsOperandsLoc, result.operands))
    return ::mlir::failure();
  if (parser.resolveOperands(rhsOperands, resultTypes[0], rhsOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void ModSOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  if ((getTwoStateAttr() && getTwoStateAttr() != ((false) ? ::mlir::OpBuilder((*this)->getContext()).getUnitAttr() : nullptr))) {
    _odsPrinter << ' ' << "bin";
  }
  _odsPrinter << ' ';
  _odsPrinter << getLhs();
  _odsPrinter << ",";
  _odsPrinter << ' ';
  _odsPrinter << getRhs();
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("twoState");
  {
     ::mlir::Builder odsBuilder(getContext());
     ::mlir::Attribute attr = getTwoStateAttr();
     if(attr && (attr == ((false) ? odsBuilder.getUnitAttr() : nullptr)))
       elidedAttrs.push_back("twoState");
  }
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
   _odsPrinter << getResult().getType();
}

void ModSOp::getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects) {
}


} // namespace circt::comb
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::comb::ModSOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::comb::detail::ModSOpGenericAdaptorBase::Properties)

namespace circt::comb {


//===----------------------------------------------------------------------===//
// ::circt::comb::ModUOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

ModUOpGenericAdaptorBase::ModUOpGenericAdaptorBase(ModUOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::mlir::UnitAttr ModUOpGenericAdaptorBase::getTwoStateAttr() {
  auto attr = ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(getProperties().twoState);
  if (!attr)
    attr = ((false) ? ::mlir::Builder(odsAttrs.getContext()).getUnitAttr() : nullptr);
  return attr;
}

bool ModUOpGenericAdaptorBase::getTwoState() {
  auto attr = getTwoStateAttr();
    if (!attr)
      return ((false) ? ::mlir::Builder(odsAttrs.getContext()).getUnitAttr() : nullptr) != nullptr;
  return attr != nullptr;
}


} // namespace detail
ModUOpAdaptor::ModUOpAdaptor(ModUOp op) : ModUOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult ModUOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_twoState = getProperties().twoState; (void)tblgen_twoState;

  if (tblgen_twoState && !((::llvm::isa<::mlir::UnitAttr>(tblgen_twoState))))
    return emitError(loc, "'comb.modu' op attribute 'twoState' failed to satisfy constraint: unit attribute");
  return ::mlir::success();
}

::llvm::LogicalResult ModUOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.twoState;
       auto attr = dict.get("twoState");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `twoState` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  return ::mlir::success();
}

::mlir::Attribute ModUOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.twoState;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("twoState",
                                       propStorage));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code ModUOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.twoState.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> ModUOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "twoState")
      return prop.twoState;
  return std::nullopt;
}

void ModUOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "twoState") {
       prop.twoState = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.twoState)>>(value);
       return;
    }
}

void ModUOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.twoState) attrs.append("twoState", prop.twoState);
}

::llvm::LogicalResult ModUOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getTwoStateAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Comb1(attr, "twoState", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult ModUOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readOptionalAttribute(prop.twoState)))
    return ::mlir::failure();
  return ::mlir::success();
}

void ModUOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;

  writer.writeOptionalAttribute(prop.twoState);
}

bool ModUOp::getTwoState() {
  auto attr = getTwoStateAttr();
    if (!attr)
      return ((false) ? ::mlir::Builder((*this)->getContext()).getUnitAttr() : nullptr) != nullptr;
  return attr != nullptr;
}

void ModUOp::setTwoState(bool attrValue) {
    auto &odsProp = getProperties().twoState;
    if (attrValue)
      odsProp = ((attrValue) ? ::mlir::Builder((*this)->getContext()).getUnitAttr() : nullptr);
    else
      odsProp = nullptr;
}

void ModUOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/::mlir::UnitAttr twoState) {
  odsState.addOperands(lhs);
  odsState.addOperands(rhs);
  if (twoState) {
    odsState.getOrAddProperties<Properties>().twoState = twoState;
  }
  odsState.addTypes(result);
}

ModUOp ModUOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/::mlir::UnitAttr twoState) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(result)>(result), std::forward<decltype(lhs)>(lhs), std::forward<decltype(rhs)>(rhs), std::forward<decltype(twoState)>(twoState));
  auto __res__ = ::llvm::dyn_cast<ModUOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ModUOp ModUOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/::mlir::UnitAttr twoState) {
  return create(builder, builder.getLoc(), std::forward<decltype(result)>(result), std::forward<decltype(lhs)>(lhs), std::forward<decltype(rhs)>(rhs), std::forward<decltype(twoState)>(twoState));
}

void ModUOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/::mlir::UnitAttr twoState) {
  odsState.addOperands(lhs);
  odsState.addOperands(rhs);
  if (twoState) {
    odsState.getOrAddProperties<Properties>().twoState = twoState;
  }

        ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
        if (::mlir::succeeded(ModUOp::inferReturnTypes(odsBuilder.getContext(),
                      odsState.location, odsState.operands,
                      odsState.attributes.getDictionary(odsState.getContext()),
                      odsState.getRawProperties(),
                      odsState.regions, inferredReturnTypes)))
          odsState.addTypes(inferredReturnTypes);
        else
          ::mlir::detail::reportFatalInferReturnTypesError(odsState);
        
}

ModUOp ModUOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/::mlir::UnitAttr twoState) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(lhs)>(lhs), std::forward<decltype(rhs)>(rhs), std::forward<decltype(twoState)>(twoState));
  auto __res__ = ::llvm::dyn_cast<ModUOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ModUOp ModUOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/::mlir::UnitAttr twoState) {
  return create(builder, builder.getLoc(), std::forward<decltype(lhs)>(lhs), std::forward<decltype(rhs)>(rhs), std::forward<decltype(twoState)>(twoState));
}

void ModUOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/::mlir::UnitAttr twoState) {
  odsState.addOperands(lhs);
  odsState.addOperands(rhs);
  if (twoState) {
    odsState.getOrAddProperties<Properties>().twoState = twoState;
  }
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

ModUOp ModUOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/::mlir::UnitAttr twoState) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(lhs)>(lhs), std::forward<decltype(rhs)>(rhs), std::forward<decltype(twoState)>(twoState));
  auto __res__ = ::llvm::dyn_cast<ModUOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ModUOp ModUOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/::mlir::UnitAttr twoState) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(lhs)>(lhs), std::forward<decltype(rhs)>(rhs), std::forward<decltype(twoState)>(twoState));
}

void ModUOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/bool twoState) {
  odsState.addOperands(lhs);
  odsState.addOperands(rhs);
  if (twoState) {
    odsState.getOrAddProperties<Properties>().twoState = ((twoState) ? odsBuilder.getUnitAttr() : nullptr);
  }
  odsState.addTypes(result);
}

ModUOp ModUOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/bool twoState) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(result)>(result), std::forward<decltype(lhs)>(lhs), std::forward<decltype(rhs)>(rhs), std::forward<decltype(twoState)>(twoState));
  auto __res__ = ::llvm::dyn_cast<ModUOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ModUOp ModUOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/bool twoState) {
  return create(builder, builder.getLoc(), std::forward<decltype(result)>(result), std::forward<decltype(lhs)>(lhs), std::forward<decltype(rhs)>(rhs), std::forward<decltype(twoState)>(twoState));
}

void ModUOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/bool twoState) {
  odsState.addOperands(lhs);
  odsState.addOperands(rhs);
  if (twoState) {
    odsState.getOrAddProperties<Properties>().twoState = ((twoState) ? odsBuilder.getUnitAttr() : nullptr);
  }

        ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
        if (::mlir::succeeded(ModUOp::inferReturnTypes(odsBuilder.getContext(),
                      odsState.location, odsState.operands,
                      odsState.attributes.getDictionary(odsState.getContext()),
                      odsState.getRawProperties(),
                      odsState.regions, inferredReturnTypes)))
          odsState.addTypes(inferredReturnTypes);
        else
          ::mlir::detail::reportFatalInferReturnTypesError(odsState);
        
}

ModUOp ModUOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/bool twoState) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(lhs)>(lhs), std::forward<decltype(rhs)>(rhs), std::forward<decltype(twoState)>(twoState));
  auto __res__ = ::llvm::dyn_cast<ModUOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ModUOp ModUOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/bool twoState) {
  return create(builder, builder.getLoc(), std::forward<decltype(lhs)>(lhs), std::forward<decltype(rhs)>(rhs), std::forward<decltype(twoState)>(twoState));
}

void ModUOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/bool twoState) {
  odsState.addOperands(lhs);
  odsState.addOperands(rhs);
  if (twoState) {
    odsState.getOrAddProperties<Properties>().twoState = ((twoState) ? odsBuilder.getUnitAttr() : nullptr);
  }
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

ModUOp ModUOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/bool twoState) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(lhs)>(lhs), std::forward<decltype(rhs)>(rhs), std::forward<decltype(twoState)>(twoState));
  auto __res__ = ::llvm::dyn_cast<ModUOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ModUOp ModUOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/bool twoState) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(lhs)>(lhs), std::forward<decltype(rhs)>(rhs), std::forward<decltype(twoState)>(twoState));
}

void ModUOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 2u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<ModUOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

ModUOp ModUOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<ModUOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ModUOp ModUOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void ModUOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 2u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<ModUOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
  ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
  if (::mlir::succeeded(ModUOp::inferReturnTypes(odsBuilder.getContext(),
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

ModUOp ModUOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<ModUOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ModUOp ModUOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void ModUOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 2u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

ModUOp ModUOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<ModUOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ModUOp ModUOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

void ModUOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 2u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties &>(properties));
  odsState.addAttributes(discardableAttributes);

  ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
  if (::mlir::succeeded(ModUOp::inferReturnTypes(odsBuilder.getContext(),
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

ModUOp ModUOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<ModUOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ModUOp ModUOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult ModUOp::verifyInvariantsImpl() {
  auto tblgen_twoState = getProperties().twoState; (void)tblgen_twoState;

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Comb1(*this, tblgen_twoState, "twoState")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Comb2(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSOperands(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Comb2(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Comb2(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult ModUOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

void ModUOp::getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context) {
  results.add(canonicalize);
}

::llvm::LogicalResult ModUOp::inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::PropertyRef properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes) {
  inferredReturnTypes.resize(1);
  ::mlir::Builder odsBuilder(context);
  if (operands.size() <= 0)
    return ::mlir::failure();
  ::mlir::Type odsInferredType0 = operands[0].getType();
  inferredReturnTypes[0] = odsInferredType0;
  return ::mlir::success();
}

::mlir::ParseResult ModUOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::OpAsmParser::UnresolvedOperand lhsRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> lhsOperands(&lhsRawOperand, 1);  ::llvm::SMLoc lhsOperandsLoc;
  (void)lhsOperandsLoc;
  ::mlir::OpAsmParser::UnresolvedOperand rhsRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> rhsOperands(&rhsRawOperand, 1);  ::llvm::SMLoc rhsOperandsLoc;
  (void)rhsOperandsLoc;
  ::mlir::Type resultRawType{};
  ::llvm::ArrayRef<::mlir::Type> resultTypes(&resultRawType, 1);
  if (::mlir::succeeded(parser.parseOptionalKeyword("bin"))) {
    result.getOrAddProperties<ModUOp::Properties>().twoState = parser.getBuilder().getUnitAttr();  }

  lhsOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(lhsRawOperand))
    return ::mlir::failure();
  if (parser.parseComma())
    return ::mlir::failure();

  rhsOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(rhsRawOperand))
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

  if (parser.parseType(resultRawType))
    return ::mlir::failure();
  result.addTypes(resultTypes);
  if (parser.resolveOperands(lhsOperands, resultTypes[0], lhsOperandsLoc, result.operands))
    return ::mlir::failure();
  if (parser.resolveOperands(rhsOperands, resultTypes[0], rhsOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void ModUOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  if ((getTwoStateAttr() && getTwoStateAttr() != ((false) ? ::mlir::OpBuilder((*this)->getContext()).getUnitAttr() : nullptr))) {
    _odsPrinter << ' ' << "bin";
  }
  _odsPrinter << ' ';
  _odsPrinter << getLhs();
  _odsPrinter << ",";
  _odsPrinter << ' ';
  _odsPrinter << getRhs();
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("twoState");
  {
     ::mlir::Builder odsBuilder(getContext());
     ::mlir::Attribute attr = getTwoStateAttr();
     if(attr && (attr == ((false) ? odsBuilder.getUnitAttr() : nullptr)))
       elidedAttrs.push_back("twoState");
  }
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
   _odsPrinter << getResult().getType();
}

void ModUOp::getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects) {
}


} // namespace circt::comb
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::comb::ModUOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::comb::detail::ModUOpGenericAdaptorBase::Properties)

namespace circt::comb {


//===----------------------------------------------------------------------===//
// ::circt::comb::MulOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

MulOpGenericAdaptorBase::MulOpGenericAdaptorBase(MulOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

std::pair<unsigned, unsigned> MulOpGenericAdaptorBase::getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
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

::mlir::UnitAttr MulOpGenericAdaptorBase::getTwoStateAttr() {
  auto attr = ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(getProperties().twoState);
  if (!attr)
    attr = ((false) ? ::mlir::Builder(odsAttrs.getContext()).getUnitAttr() : nullptr);
  return attr;
}

bool MulOpGenericAdaptorBase::getTwoState() {
  auto attr = getTwoStateAttr();
    if (!attr)
      return ((false) ? ::mlir::Builder(odsAttrs.getContext()).getUnitAttr() : nullptr) != nullptr;
  return attr != nullptr;
}


} // namespace detail
MulOpAdaptor::MulOpAdaptor(MulOp op) : MulOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult MulOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_twoState = getProperties().twoState; (void)tblgen_twoState;

  if (tblgen_twoState && !((::llvm::isa<::mlir::UnitAttr>(tblgen_twoState))))
    return emitError(loc, "'comb.mul' op attribute 'twoState' failed to satisfy constraint: unit attribute");
  return ::mlir::success();
}

std::pair<unsigned, unsigned> MulOp::getODSOperandIndexAndLength(unsigned index) {
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

::mlir::MutableOperandRange MulOp::getInputsMutable() {
  auto range = getODSOperandIndexAndLength(0);
  auto mutableRange = ::mlir::MutableOperandRange(getOperation(), range.first, range.second);
  return mutableRange;
}

::llvm::LogicalResult MulOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.twoState;
       auto attr = dict.get("twoState");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `twoState` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  return ::mlir::success();
}

::mlir::Attribute MulOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.twoState;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("twoState",
                                       propStorage));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code MulOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.twoState.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> MulOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "twoState")
      return prop.twoState;
  return std::nullopt;
}

void MulOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "twoState") {
       prop.twoState = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.twoState)>>(value);
       return;
    }
}

void MulOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.twoState) attrs.append("twoState", prop.twoState);
}

::llvm::LogicalResult MulOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getTwoStateAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Comb1(attr, "twoState", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult MulOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readOptionalAttribute(prop.twoState)))
    return ::mlir::failure();
  return ::mlir::success();
}

void MulOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;

  writer.writeOptionalAttribute(prop.twoState);
}

bool MulOp::getTwoState() {
  auto attr = getTwoStateAttr();
    if (!attr)
      return ((false) ? ::mlir::Builder((*this)->getContext()).getUnitAttr() : nullptr) != nullptr;
  return attr != nullptr;
}

void MulOp::setTwoState(bool attrValue) {
    auto &odsProp = getProperties().twoState;
    if (attrValue)
      odsProp = ((attrValue) ? ::mlir::Builder((*this)->getContext()).getUnitAttr() : nullptr);
    else
      odsProp = nullptr;
}

void MulOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value lhs, Value rhs, bool twoState) {
      return build(odsBuilder, odsState, lhs.getType(),
                   ValueRange{lhs, rhs}, twoState);
    
}

MulOp MulOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, Value lhs, Value rhs, bool twoState) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(lhs)>(lhs), std::forward<decltype(rhs)>(rhs), std::forward<decltype(twoState)>(twoState));
  auto __res__ = ::llvm::dyn_cast<MulOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

MulOp MulOp::create(::mlir::ImplicitLocOpBuilder &builder, Value lhs, Value rhs, bool twoState) {
  return create(builder, builder.getLoc(), std::forward<decltype(lhs)>(lhs), std::forward<decltype(rhs)>(rhs), std::forward<decltype(twoState)>(twoState));
}

void MulOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::ValueRange inputs, /*optional*/::mlir::UnitAttr twoState) {
  odsState.addOperands(inputs);
  if (twoState) {
    odsState.getOrAddProperties<Properties>().twoState = twoState;
  }
  odsState.addTypes(result);
}

MulOp MulOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::ValueRange inputs, /*optional*/::mlir::UnitAttr twoState) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(result)>(result), std::forward<decltype(inputs)>(inputs), std::forward<decltype(twoState)>(twoState));
  auto __res__ = ::llvm::dyn_cast<MulOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

MulOp MulOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::ValueRange inputs, /*optional*/::mlir::UnitAttr twoState) {
  return create(builder, builder.getLoc(), std::forward<decltype(result)>(result), std::forward<decltype(inputs)>(inputs), std::forward<decltype(twoState)>(twoState));
}

void MulOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange inputs, /*optional*/::mlir::UnitAttr twoState) {
  odsState.addOperands(inputs);
  if (twoState) {
    odsState.getOrAddProperties<Properties>().twoState = twoState;
  }
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

MulOp MulOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange inputs, /*optional*/::mlir::UnitAttr twoState) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(inputs)>(inputs), std::forward<decltype(twoState)>(twoState));
  auto __res__ = ::llvm::dyn_cast<MulOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

MulOp MulOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange inputs, /*optional*/::mlir::UnitAttr twoState) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(inputs)>(inputs), std::forward<decltype(twoState)>(twoState));
}

void MulOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::ValueRange inputs, /*optional*/bool twoState) {
  odsState.addOperands(inputs);
  if (twoState) {
    odsState.getOrAddProperties<Properties>().twoState = ((twoState) ? odsBuilder.getUnitAttr() : nullptr);
  }
  odsState.addTypes(result);
}

MulOp MulOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::ValueRange inputs, /*optional*/bool twoState) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(result)>(result), std::forward<decltype(inputs)>(inputs), std::forward<decltype(twoState)>(twoState));
  auto __res__ = ::llvm::dyn_cast<MulOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

MulOp MulOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::ValueRange inputs, /*optional*/bool twoState) {
  return create(builder, builder.getLoc(), std::forward<decltype(result)>(result), std::forward<decltype(inputs)>(inputs), std::forward<decltype(twoState)>(twoState));
}

void MulOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange inputs, /*optional*/bool twoState) {
  odsState.addOperands(inputs);
  if (twoState) {
    odsState.getOrAddProperties<Properties>().twoState = ((twoState) ? odsBuilder.getUnitAttr() : nullptr);
  }
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

MulOp MulOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange inputs, /*optional*/bool twoState) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(inputs)>(inputs), std::forward<decltype(twoState)>(twoState));
  auto __res__ = ::llvm::dyn_cast<MulOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

MulOp MulOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange inputs, /*optional*/bool twoState) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(inputs)>(inputs), std::forward<decltype(twoState)>(twoState));
}

void MulOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<MulOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

MulOp MulOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<MulOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

MulOp MulOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void MulOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

MulOp MulOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<MulOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

MulOp MulOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

void MulOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange inputs, /*optional*/::mlir::UnitAttr twoState) {
  odsState.addOperands(inputs);
  if (twoState) {
    odsState.getOrAddProperties<Properties>().twoState = twoState;
  }
  odsState.addTypes({inputs.front().getType()});

}

MulOp MulOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange inputs, /*optional*/::mlir::UnitAttr twoState) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(inputs)>(inputs), std::forward<decltype(twoState)>(twoState));
  auto __res__ = ::llvm::dyn_cast<MulOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

MulOp MulOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange inputs, /*optional*/::mlir::UnitAttr twoState) {
  return create(builder, builder.getLoc(), std::forward<decltype(inputs)>(inputs), std::forward<decltype(twoState)>(twoState));
}

void MulOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange inputs, /*optional*/bool twoState) {
  odsState.addOperands(inputs);
  if (twoState) {
    odsState.getOrAddProperties<Properties>().twoState = ((twoState) ? odsBuilder.getUnitAttr() : nullptr);
  }
  odsState.addTypes({inputs.front().getType()});

}

MulOp MulOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange inputs, /*optional*/bool twoState) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(inputs)>(inputs), std::forward<decltype(twoState)>(twoState));
  auto __res__ = ::llvm::dyn_cast<MulOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

MulOp MulOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange inputs, /*optional*/bool twoState) {
  return create(builder, builder.getLoc(), std::forward<decltype(inputs)>(inputs), std::forward<decltype(twoState)>(twoState));
}

void MulOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  odsState.addTypes({operands[0].getType()});

}

MulOp MulOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<MulOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

MulOp MulOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void MulOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  odsState.addTypes({operands[0].getType()});

}

MulOp MulOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<MulOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

MulOp MulOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult MulOp::verifyInvariantsImpl() {
  auto tblgen_twoState = getProperties().twoState; (void)tblgen_twoState;

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Comb1(*this, tblgen_twoState, "twoState")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Comb1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Comb2(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult MulOp::verifyInvariants() {
  if(::mlir::succeeded(verifyInvariantsImpl()) && ::mlir::succeeded(verify()))
    return ::mlir::success();
  return ::mlir::failure();
}

void MulOp::getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context) {
  results.add(canonicalize);
}

::mlir::ParseResult MulOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::llvm::SmallVector<::mlir::OpAsmParser::UnresolvedOperand, 4> inputsOperands;
  ::llvm::SMLoc inputsOperandsLoc;
  (void)inputsOperandsLoc;
  ::mlir::Type resultRawType{};
  ::llvm::ArrayRef<::mlir::Type> resultTypes(&resultRawType, 1);
  if (::mlir::succeeded(parser.parseOptionalKeyword("bin"))) {
    result.getOrAddProperties<MulOp::Properties>().twoState = parser.getBuilder().getUnitAttr();  }

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

  if (parser.parseType(resultRawType))
    return ::mlir::failure();
  result.addTypes(resultTypes);
  if (parser.resolveOperands(inputsOperands, resultTypes[0], inputsOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void MulOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  if ((getTwoStateAttr() && getTwoStateAttr() != ((false) ? ::mlir::OpBuilder((*this)->getContext()).getUnitAttr() : nullptr))) {
    _odsPrinter << ' ' << "bin";
  }
  _odsPrinter << ' ';
  _odsPrinter << getInputs();
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("twoState");
  {
     ::mlir::Builder odsBuilder(getContext());
     ::mlir::Attribute attr = getTwoStateAttr();
     if(attr && (attr == ((false) ? odsBuilder.getUnitAttr() : nullptr)))
       elidedAttrs.push_back("twoState");
  }
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
   _odsPrinter << getResult().getType();
}

void MulOp::getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects) {
}


} // namespace circt::comb
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::comb::MulOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::comb::detail::MulOpGenericAdaptorBase::Properties)

namespace circt::comb {


//===----------------------------------------------------------------------===//
// ::circt::comb::MuxOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

MuxOpGenericAdaptorBase::MuxOpGenericAdaptorBase(MuxOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::mlir::UnitAttr MuxOpGenericAdaptorBase::getTwoStateAttr() {
  auto attr = ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(getProperties().twoState);
  if (!attr)
    attr = ((false) ? ::mlir::Builder(odsAttrs.getContext()).getUnitAttr() : nullptr);
  return attr;
}

bool MuxOpGenericAdaptorBase::getTwoState() {
  auto attr = getTwoStateAttr();
    if (!attr)
      return ((false) ? ::mlir::Builder(odsAttrs.getContext()).getUnitAttr() : nullptr) != nullptr;
  return attr != nullptr;
}


} // namespace detail
MuxOpAdaptor::MuxOpAdaptor(MuxOp op) : MuxOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult MuxOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_twoState = getProperties().twoState; (void)tblgen_twoState;

  if (tblgen_twoState && !((::llvm::isa<::mlir::UnitAttr>(tblgen_twoState))))
    return emitError(loc, "'comb.mux' op attribute 'twoState' failed to satisfy constraint: unit attribute");
  return ::mlir::success();
}

::llvm::LogicalResult MuxOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.twoState;
       auto attr = dict.get("twoState");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `twoState` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  return ::mlir::success();
}

::mlir::Attribute MuxOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.twoState;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("twoState",
                                       propStorage));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code MuxOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.twoState.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> MuxOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "twoState")
      return prop.twoState;
  return std::nullopt;
}

void MuxOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "twoState") {
       prop.twoState = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.twoState)>>(value);
       return;
    }
}

void MuxOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.twoState) attrs.append("twoState", prop.twoState);
}

::llvm::LogicalResult MuxOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getTwoStateAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Comb1(attr, "twoState", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult MuxOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readOptionalAttribute(prop.twoState)))
    return ::mlir::failure();
  return ::mlir::success();
}

void MuxOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;

  writer.writeOptionalAttribute(prop.twoState);
}

bool MuxOp::getTwoState() {
  auto attr = getTwoStateAttr();
    if (!attr)
      return ((false) ? ::mlir::Builder((*this)->getContext()).getUnitAttr() : nullptr) != nullptr;
  return attr != nullptr;
}

void MuxOp::setTwoState(bool attrValue) {
    auto &odsProp = getProperties().twoState;
    if (attrValue)
      odsProp = ((attrValue) ? ::mlir::Builder((*this)->getContext()).getUnitAttr() : nullptr);
    else
      odsProp = nullptr;
}

void MuxOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value cond, ::mlir::Value trueValue, ::mlir::Value falseValue, /*optional*/::mlir::UnitAttr twoState) {
  odsState.addOperands(cond);
  odsState.addOperands(trueValue);
  odsState.addOperands(falseValue);
  if (twoState) {
    odsState.getOrAddProperties<Properties>().twoState = twoState;
  }
  odsState.addTypes(result);
}

MuxOp MuxOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value cond, ::mlir::Value trueValue, ::mlir::Value falseValue, /*optional*/::mlir::UnitAttr twoState) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(result)>(result), std::forward<decltype(cond)>(cond), std::forward<decltype(trueValue)>(trueValue), std::forward<decltype(falseValue)>(falseValue), std::forward<decltype(twoState)>(twoState));
  auto __res__ = ::llvm::dyn_cast<MuxOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

MuxOp MuxOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value cond, ::mlir::Value trueValue, ::mlir::Value falseValue, /*optional*/::mlir::UnitAttr twoState) {
  return create(builder, builder.getLoc(), std::forward<decltype(result)>(result), std::forward<decltype(cond)>(cond), std::forward<decltype(trueValue)>(trueValue), std::forward<decltype(falseValue)>(falseValue), std::forward<decltype(twoState)>(twoState));
}

void MuxOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value cond, ::mlir::Value trueValue, ::mlir::Value falseValue, /*optional*/::mlir::UnitAttr twoState) {
  odsState.addOperands(cond);
  odsState.addOperands(trueValue);
  odsState.addOperands(falseValue);
  if (twoState) {
    odsState.getOrAddProperties<Properties>().twoState = twoState;
  }

        ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
        if (::mlir::succeeded(MuxOp::inferReturnTypes(odsBuilder.getContext(),
                      odsState.location, odsState.operands,
                      odsState.attributes.getDictionary(odsState.getContext()),
                      odsState.getRawProperties(),
                      odsState.regions, inferredReturnTypes)))
          odsState.addTypes(inferredReturnTypes);
        else
          ::mlir::detail::reportFatalInferReturnTypesError(odsState);
        
}

MuxOp MuxOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value cond, ::mlir::Value trueValue, ::mlir::Value falseValue, /*optional*/::mlir::UnitAttr twoState) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(cond)>(cond), std::forward<decltype(trueValue)>(trueValue), std::forward<decltype(falseValue)>(falseValue), std::forward<decltype(twoState)>(twoState));
  auto __res__ = ::llvm::dyn_cast<MuxOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

MuxOp MuxOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value cond, ::mlir::Value trueValue, ::mlir::Value falseValue, /*optional*/::mlir::UnitAttr twoState) {
  return create(builder, builder.getLoc(), std::forward<decltype(cond)>(cond), std::forward<decltype(trueValue)>(trueValue), std::forward<decltype(falseValue)>(falseValue), std::forward<decltype(twoState)>(twoState));
}

void MuxOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value cond, ::mlir::Value trueValue, ::mlir::Value falseValue, /*optional*/::mlir::UnitAttr twoState) {
  odsState.addOperands(cond);
  odsState.addOperands(trueValue);
  odsState.addOperands(falseValue);
  if (twoState) {
    odsState.getOrAddProperties<Properties>().twoState = twoState;
  }
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

MuxOp MuxOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value cond, ::mlir::Value trueValue, ::mlir::Value falseValue, /*optional*/::mlir::UnitAttr twoState) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(cond)>(cond), std::forward<decltype(trueValue)>(trueValue), std::forward<decltype(falseValue)>(falseValue), std::forward<decltype(twoState)>(twoState));
  auto __res__ = ::llvm::dyn_cast<MuxOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

MuxOp MuxOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value cond, ::mlir::Value trueValue, ::mlir::Value falseValue, /*optional*/::mlir::UnitAttr twoState) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(cond)>(cond), std::forward<decltype(trueValue)>(trueValue), std::forward<decltype(falseValue)>(falseValue), std::forward<decltype(twoState)>(twoState));
}

void MuxOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value cond, ::mlir::Value trueValue, ::mlir::Value falseValue, /*optional*/bool twoState) {
  odsState.addOperands(cond);
  odsState.addOperands(trueValue);
  odsState.addOperands(falseValue);
  if (twoState) {
    odsState.getOrAddProperties<Properties>().twoState = ((twoState) ? odsBuilder.getUnitAttr() : nullptr);
  }
  odsState.addTypes(result);
}

MuxOp MuxOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value cond, ::mlir::Value trueValue, ::mlir::Value falseValue, /*optional*/bool twoState) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(result)>(result), std::forward<decltype(cond)>(cond), std::forward<decltype(trueValue)>(trueValue), std::forward<decltype(falseValue)>(falseValue), std::forward<decltype(twoState)>(twoState));
  auto __res__ = ::llvm::dyn_cast<MuxOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

MuxOp MuxOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value cond, ::mlir::Value trueValue, ::mlir::Value falseValue, /*optional*/bool twoState) {
  return create(builder, builder.getLoc(), std::forward<decltype(result)>(result), std::forward<decltype(cond)>(cond), std::forward<decltype(trueValue)>(trueValue), std::forward<decltype(falseValue)>(falseValue), std::forward<decltype(twoState)>(twoState));
}

void MuxOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value cond, ::mlir::Value trueValue, ::mlir::Value falseValue, /*optional*/bool twoState) {
  odsState.addOperands(cond);
  odsState.addOperands(trueValue);
  odsState.addOperands(falseValue);
  if (twoState) {
    odsState.getOrAddProperties<Properties>().twoState = ((twoState) ? odsBuilder.getUnitAttr() : nullptr);
  }

        ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
        if (::mlir::succeeded(MuxOp::inferReturnTypes(odsBuilder.getContext(),
                      odsState.location, odsState.operands,
                      odsState.attributes.getDictionary(odsState.getContext()),
                      odsState.getRawProperties(),
                      odsState.regions, inferredReturnTypes)))
          odsState.addTypes(inferredReturnTypes);
        else
          ::mlir::detail::reportFatalInferReturnTypesError(odsState);
        
}

MuxOp MuxOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value cond, ::mlir::Value trueValue, ::mlir::Value falseValue, /*optional*/bool twoState) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(cond)>(cond), std::forward<decltype(trueValue)>(trueValue), std::forward<decltype(falseValue)>(falseValue), std::forward<decltype(twoState)>(twoState));
  auto __res__ = ::llvm::dyn_cast<MuxOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

MuxOp MuxOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value cond, ::mlir::Value trueValue, ::mlir::Value falseValue, /*optional*/bool twoState) {
  return create(builder, builder.getLoc(), std::forward<decltype(cond)>(cond), std::forward<decltype(trueValue)>(trueValue), std::forward<decltype(falseValue)>(falseValue), std::forward<decltype(twoState)>(twoState));
}

void MuxOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value cond, ::mlir::Value trueValue, ::mlir::Value falseValue, /*optional*/bool twoState) {
  odsState.addOperands(cond);
  odsState.addOperands(trueValue);
  odsState.addOperands(falseValue);
  if (twoState) {
    odsState.getOrAddProperties<Properties>().twoState = ((twoState) ? odsBuilder.getUnitAttr() : nullptr);
  }
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

MuxOp MuxOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value cond, ::mlir::Value trueValue, ::mlir::Value falseValue, /*optional*/bool twoState) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(cond)>(cond), std::forward<decltype(trueValue)>(trueValue), std::forward<decltype(falseValue)>(falseValue), std::forward<decltype(twoState)>(twoState));
  auto __res__ = ::llvm::dyn_cast<MuxOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

MuxOp MuxOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value cond, ::mlir::Value trueValue, ::mlir::Value falseValue, /*optional*/bool twoState) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(cond)>(cond), std::forward<decltype(trueValue)>(trueValue), std::forward<decltype(falseValue)>(falseValue), std::forward<decltype(twoState)>(twoState));
}

void MuxOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 3u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<MuxOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

MuxOp MuxOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<MuxOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

MuxOp MuxOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void MuxOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 3u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<MuxOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
  ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
  if (::mlir::succeeded(MuxOp::inferReturnTypes(odsBuilder.getContext(),
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

MuxOp MuxOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<MuxOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

MuxOp MuxOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void MuxOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 3u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

MuxOp MuxOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<MuxOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

MuxOp MuxOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

void MuxOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 3u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties &>(properties));
  odsState.addAttributes(discardableAttributes);

  ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
  if (::mlir::succeeded(MuxOp::inferReturnTypes(odsBuilder.getContext(),
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

MuxOp MuxOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<MuxOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

MuxOp MuxOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult MuxOp::verifyInvariantsImpl() {
  auto tblgen_twoState = getProperties().twoState; (void)tblgen_twoState;

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Comb1(*this, tblgen_twoState, "twoState")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Comb3(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSOperands(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Comb4(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup2 = getODSOperands(2);

    for (auto v : valueGroup2) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Comb4(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Comb4(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  if (!((((*this->getODSOperands(1).begin()).getType()) == ((*this->getODSOperands(2).begin()).getType()) && ((*this->getODSOperands(2).begin()).getType()) == ((*this->getODSResults(0).begin()).getType()) && ((*this->getODSResults(0).begin()).getType()) == ((*this->getODSOperands(1).begin()).getType()))))
    return emitOpError("failed to verify that all of {trueValue, falseValue, result} have same type");
  return ::mlir::success();
}

::llvm::LogicalResult MuxOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::llvm::LogicalResult MuxOp::inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::PropertyRef properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes) {
  inferredReturnTypes.resize(1);
  ::mlir::Builder odsBuilder(context);
  if (operands.size() <= 2)
    return ::mlir::failure();
  ::mlir::Type odsInferredType0 = operands[2].getType();
  inferredReturnTypes[0] = odsInferredType0;
  return ::mlir::success();
}

::mlir::ParseResult MuxOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::OpAsmParser::UnresolvedOperand condRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> condOperands(&condRawOperand, 1);  ::llvm::SMLoc condOperandsLoc;
  (void)condOperandsLoc;
  ::mlir::OpAsmParser::UnresolvedOperand trueValueRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> trueValueOperands(&trueValueRawOperand, 1);  ::llvm::SMLoc trueValueOperandsLoc;
  (void)trueValueOperandsLoc;
  ::mlir::OpAsmParser::UnresolvedOperand falseValueRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> falseValueOperands(&falseValueRawOperand, 1);  ::llvm::SMLoc falseValueOperandsLoc;
  (void)falseValueOperandsLoc;
  ::mlir::Type resultRawType{};
  ::llvm::ArrayRef<::mlir::Type> resultTypes(&resultRawType, 1);
  if (::mlir::succeeded(parser.parseOptionalKeyword("bin"))) {
    result.getOrAddProperties<MuxOp::Properties>().twoState = parser.getBuilder().getUnitAttr();  }

  condOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(condRawOperand))
    return ::mlir::failure();
  if (parser.parseComma())
    return ::mlir::failure();

  trueValueOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(trueValueRawOperand))
    return ::mlir::failure();
  if (parser.parseComma())
    return ::mlir::failure();

  falseValueOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(falseValueRawOperand))
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

  if (parser.parseType(resultRawType))
    return ::mlir::failure();
  ::mlir::Type odsBuildableType0 = parser.getBuilder().getIntegerType(1);
  result.addTypes(resultTypes);
  if (parser.resolveOperands(condOperands, odsBuildableType0, condOperandsLoc, result.operands))
    return ::mlir::failure();
  if (parser.resolveOperands(trueValueOperands, resultTypes[0], trueValueOperandsLoc, result.operands))
    return ::mlir::failure();
  if (parser.resolveOperands(falseValueOperands, resultTypes[0], falseValueOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void MuxOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  if ((getTwoStateAttr() && getTwoStateAttr() != ((false) ? ::mlir::OpBuilder((*this)->getContext()).getUnitAttr() : nullptr))) {
    _odsPrinter << ' ' << "bin";
  }
  _odsPrinter << ' ';
  _odsPrinter << getCond();
  _odsPrinter << ",";
  _odsPrinter << ' ';
  _odsPrinter << getTrueValue();
  _odsPrinter << ",";
  _odsPrinter << ' ';
  _odsPrinter << getFalseValue();
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("twoState");
  {
     ::mlir::Builder odsBuilder(getContext());
     ::mlir::Attribute attr = getTwoStateAttr();
     if(attr && (attr == ((false) ? odsBuilder.getUnitAttr() : nullptr)))
       elidedAttrs.push_back("twoState");
  }
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
   _odsPrinter << getResult().getType();
}

void MuxOp::getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects) {
}


} // namespace circt::comb
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::comb::MuxOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::comb::detail::MuxOpGenericAdaptorBase::Properties)

namespace circt::comb {


//===----------------------------------------------------------------------===//
// ::circt::comb::OrOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

OrOpGenericAdaptorBase::OrOpGenericAdaptorBase(OrOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

std::pair<unsigned, unsigned> OrOpGenericAdaptorBase::getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
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

::mlir::UnitAttr OrOpGenericAdaptorBase::getTwoStateAttr() {
  auto attr = ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(getProperties().twoState);
  if (!attr)
    attr = ((false) ? ::mlir::Builder(odsAttrs.getContext()).getUnitAttr() : nullptr);
  return attr;
}

bool OrOpGenericAdaptorBase::getTwoState() {
  auto attr = getTwoStateAttr();
    if (!attr)
      return ((false) ? ::mlir::Builder(odsAttrs.getContext()).getUnitAttr() : nullptr) != nullptr;
  return attr != nullptr;
}


} // namespace detail
OrOpAdaptor::OrOpAdaptor(OrOp op) : OrOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult OrOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_twoState = getProperties().twoState; (void)tblgen_twoState;

  if (tblgen_twoState && !((::llvm::isa<::mlir::UnitAttr>(tblgen_twoState))))
    return emitError(loc, "'comb.or' op attribute 'twoState' failed to satisfy constraint: unit attribute");
  return ::mlir::success();
}

std::pair<unsigned, unsigned> OrOp::getODSOperandIndexAndLength(unsigned index) {
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

::mlir::MutableOperandRange OrOp::getInputsMutable() {
  auto range = getODSOperandIndexAndLength(0);
  auto mutableRange = ::mlir::MutableOperandRange(getOperation(), range.first, range.second);
  return mutableRange;
}

::llvm::LogicalResult OrOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.twoState;
       auto attr = dict.get("twoState");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `twoState` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  return ::mlir::success();
}

::mlir::Attribute OrOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.twoState;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("twoState",
                                       propStorage));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code OrOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.twoState.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> OrOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "twoState")
      return prop.twoState;
  return std::nullopt;
}

void OrOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "twoState") {
       prop.twoState = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.twoState)>>(value);
       return;
    }
}

void OrOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.twoState) attrs.append("twoState", prop.twoState);
}

::llvm::LogicalResult OrOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getTwoStateAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Comb1(attr, "twoState", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult OrOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readOptionalAttribute(prop.twoState)))
    return ::mlir::failure();
  return ::mlir::success();
}

void OrOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;

  writer.writeOptionalAttribute(prop.twoState);
}

bool OrOp::getTwoState() {
  auto attr = getTwoStateAttr();
    if (!attr)
      return ((false) ? ::mlir::Builder((*this)->getContext()).getUnitAttr() : nullptr) != nullptr;
  return attr != nullptr;
}

void OrOp::setTwoState(bool attrValue) {
    auto &odsProp = getProperties().twoState;
    if (attrValue)
      odsProp = ((attrValue) ? ::mlir::Builder((*this)->getContext()).getUnitAttr() : nullptr);
    else
      odsProp = nullptr;
}

void OrOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value lhs, Value rhs, bool twoState) {
      return build(odsBuilder, odsState, lhs.getType(),
                   ValueRange{lhs, rhs}, twoState);
    
}

OrOp OrOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, Value lhs, Value rhs, bool twoState) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(lhs)>(lhs), std::forward<decltype(rhs)>(rhs), std::forward<decltype(twoState)>(twoState));
  auto __res__ = ::llvm::dyn_cast<OrOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

OrOp OrOp::create(::mlir::ImplicitLocOpBuilder &builder, Value lhs, Value rhs, bool twoState) {
  return create(builder, builder.getLoc(), std::forward<decltype(lhs)>(lhs), std::forward<decltype(rhs)>(rhs), std::forward<decltype(twoState)>(twoState));
}

void OrOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::ValueRange inputs, /*optional*/::mlir::UnitAttr twoState) {
  odsState.addOperands(inputs);
  if (twoState) {
    odsState.getOrAddProperties<Properties>().twoState = twoState;
  }
  odsState.addTypes(result);
}

OrOp OrOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::ValueRange inputs, /*optional*/::mlir::UnitAttr twoState) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(result)>(result), std::forward<decltype(inputs)>(inputs), std::forward<decltype(twoState)>(twoState));
  auto __res__ = ::llvm::dyn_cast<OrOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

OrOp OrOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::ValueRange inputs, /*optional*/::mlir::UnitAttr twoState) {
  return create(builder, builder.getLoc(), std::forward<decltype(result)>(result), std::forward<decltype(inputs)>(inputs), std::forward<decltype(twoState)>(twoState));
}

void OrOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange inputs, /*optional*/::mlir::UnitAttr twoState) {
  odsState.addOperands(inputs);
  if (twoState) {
    odsState.getOrAddProperties<Properties>().twoState = twoState;
  }
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

OrOp OrOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange inputs, /*optional*/::mlir::UnitAttr twoState) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(inputs)>(inputs), std::forward<decltype(twoState)>(twoState));
  auto __res__ = ::llvm::dyn_cast<OrOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

OrOp OrOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange inputs, /*optional*/::mlir::UnitAttr twoState) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(inputs)>(inputs), std::forward<decltype(twoState)>(twoState));
}

void OrOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::ValueRange inputs, /*optional*/bool twoState) {
  odsState.addOperands(inputs);
  if (twoState) {
    odsState.getOrAddProperties<Properties>().twoState = ((twoState) ? odsBuilder.getUnitAttr() : nullptr);
  }
  odsState.addTypes(result);
}

OrOp OrOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::ValueRange inputs, /*optional*/bool twoState) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(result)>(result), std::forward<decltype(inputs)>(inputs), std::forward<decltype(twoState)>(twoState));
  auto __res__ = ::llvm::dyn_cast<OrOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

OrOp OrOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::ValueRange inputs, /*optional*/bool twoState) {
  return create(builder, builder.getLoc(), std::forward<decltype(result)>(result), std::forward<decltype(inputs)>(inputs), std::forward<decltype(twoState)>(twoState));
}

void OrOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange inputs, /*optional*/bool twoState) {
  odsState.addOperands(inputs);
  if (twoState) {
    odsState.getOrAddProperties<Properties>().twoState = ((twoState) ? odsBuilder.getUnitAttr() : nullptr);
  }
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

OrOp OrOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange inputs, /*optional*/bool twoState) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(inputs)>(inputs), std::forward<decltype(twoState)>(twoState));
  auto __res__ = ::llvm::dyn_cast<OrOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

OrOp OrOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange inputs, /*optional*/bool twoState) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(inputs)>(inputs), std::forward<decltype(twoState)>(twoState));
}

void OrOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<OrOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

OrOp OrOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<OrOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

OrOp OrOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void OrOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

OrOp OrOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<OrOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

OrOp OrOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

void OrOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange inputs, /*optional*/::mlir::UnitAttr twoState) {
  odsState.addOperands(inputs);
  if (twoState) {
    odsState.getOrAddProperties<Properties>().twoState = twoState;
  }
  odsState.addTypes({inputs.front().getType()});

}

OrOp OrOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange inputs, /*optional*/::mlir::UnitAttr twoState) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(inputs)>(inputs), std::forward<decltype(twoState)>(twoState));
  auto __res__ = ::llvm::dyn_cast<OrOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

OrOp OrOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange inputs, /*optional*/::mlir::UnitAttr twoState) {
  return create(builder, builder.getLoc(), std::forward<decltype(inputs)>(inputs), std::forward<decltype(twoState)>(twoState));
}

void OrOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange inputs, /*optional*/bool twoState) {
  odsState.addOperands(inputs);
  if (twoState) {
    odsState.getOrAddProperties<Properties>().twoState = ((twoState) ? odsBuilder.getUnitAttr() : nullptr);
  }
  odsState.addTypes({inputs.front().getType()});

}

OrOp OrOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange inputs, /*optional*/bool twoState) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(inputs)>(inputs), std::forward<decltype(twoState)>(twoState));
  auto __res__ = ::llvm::dyn_cast<OrOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

OrOp OrOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange inputs, /*optional*/bool twoState) {
  return create(builder, builder.getLoc(), std::forward<decltype(inputs)>(inputs), std::forward<decltype(twoState)>(twoState));
}

void OrOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  odsState.addTypes({operands[0].getType()});

}

OrOp OrOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<OrOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

OrOp OrOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void OrOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  odsState.addTypes({operands[0].getType()});

}

OrOp OrOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<OrOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

OrOp OrOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult OrOp::verifyInvariantsImpl() {
  auto tblgen_twoState = getProperties().twoState; (void)tblgen_twoState;

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Comb1(*this, tblgen_twoState, "twoState")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Comb1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Comb2(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult OrOp::verifyInvariants() {
  if(::mlir::succeeded(verifyInvariantsImpl()) && ::mlir::succeeded(verify()))
    return ::mlir::success();
  return ::mlir::failure();
}

void OrOp::getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context) {
  results.add(canonicalize);
}

::mlir::ParseResult OrOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::llvm::SmallVector<::mlir::OpAsmParser::UnresolvedOperand, 4> inputsOperands;
  ::llvm::SMLoc inputsOperandsLoc;
  (void)inputsOperandsLoc;
  ::mlir::Type resultRawType{};
  ::llvm::ArrayRef<::mlir::Type> resultTypes(&resultRawType, 1);
  if (::mlir::succeeded(parser.parseOptionalKeyword("bin"))) {
    result.getOrAddProperties<OrOp::Properties>().twoState = parser.getBuilder().getUnitAttr();  }

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

  if (parser.parseType(resultRawType))
    return ::mlir::failure();
  result.addTypes(resultTypes);
  if (parser.resolveOperands(inputsOperands, resultTypes[0], inputsOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void OrOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  if ((getTwoStateAttr() && getTwoStateAttr() != ((false) ? ::mlir::OpBuilder((*this)->getContext()).getUnitAttr() : nullptr))) {
    _odsPrinter << ' ' << "bin";
  }
  _odsPrinter << ' ';
  _odsPrinter << getInputs();
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("twoState");
  {
     ::mlir::Builder odsBuilder(getContext());
     ::mlir::Attribute attr = getTwoStateAttr();
     if(attr && (attr == ((false) ? odsBuilder.getUnitAttr() : nullptr)))
       elidedAttrs.push_back("twoState");
  }
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
   _odsPrinter << getResult().getType();
}

void OrOp::getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects) {
}


} // namespace circt::comb
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::comb::OrOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::comb::detail::OrOpGenericAdaptorBase::Properties)

namespace circt::comb {


//===----------------------------------------------------------------------===//
// ::circt::comb::ParityOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

ParityOpGenericAdaptorBase::ParityOpGenericAdaptorBase(ParityOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::mlir::UnitAttr ParityOpGenericAdaptorBase::getTwoStateAttr() {
  auto attr = ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(getProperties().twoState);
  if (!attr)
    attr = ((false) ? ::mlir::Builder(odsAttrs.getContext()).getUnitAttr() : nullptr);
  return attr;
}

bool ParityOpGenericAdaptorBase::getTwoState() {
  auto attr = getTwoStateAttr();
    if (!attr)
      return ((false) ? ::mlir::Builder(odsAttrs.getContext()).getUnitAttr() : nullptr) != nullptr;
  return attr != nullptr;
}


} // namespace detail
ParityOpAdaptor::ParityOpAdaptor(ParityOp op) : ParityOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult ParityOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_twoState = getProperties().twoState; (void)tblgen_twoState;

  if (tblgen_twoState && !((::llvm::isa<::mlir::UnitAttr>(tblgen_twoState))))
    return emitError(loc, "'comb.parity' op attribute 'twoState' failed to satisfy constraint: unit attribute");
  return ::mlir::success();
}

::llvm::LogicalResult ParityOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.twoState;
       auto attr = dict.get("twoState");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `twoState` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  return ::mlir::success();
}

::mlir::Attribute ParityOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.twoState;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("twoState",
                                       propStorage));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code ParityOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.twoState.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> ParityOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "twoState")
      return prop.twoState;
  return std::nullopt;
}

void ParityOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "twoState") {
       prop.twoState = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.twoState)>>(value);
       return;
    }
}

void ParityOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.twoState) attrs.append("twoState", prop.twoState);
}

::llvm::LogicalResult ParityOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getTwoStateAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Comb1(attr, "twoState", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult ParityOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readOptionalAttribute(prop.twoState)))
    return ::mlir::failure();
  return ::mlir::success();
}

void ParityOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;

  writer.writeOptionalAttribute(prop.twoState);
}

bool ParityOp::getTwoState() {
  auto attr = getTwoStateAttr();
    if (!attr)
      return ((false) ? ::mlir::Builder((*this)->getContext()).getUnitAttr() : nullptr) != nullptr;
  return attr != nullptr;
}

void ParityOp::setTwoState(bool attrValue) {
    auto &odsProp = getProperties().twoState;
    if (attrValue)
      odsProp = ((attrValue) ? ::mlir::Builder((*this)->getContext()).getUnitAttr() : nullptr);
    else
      odsProp = nullptr;
}

void ParityOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value input, /*optional*/::mlir::UnitAttr twoState) {
  odsState.addOperands(input);
  if (twoState) {
    odsState.getOrAddProperties<Properties>().twoState = twoState;
  }
  odsState.addTypes(result);
}

ParityOp ParityOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value input, /*optional*/::mlir::UnitAttr twoState) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(result)>(result), std::forward<decltype(input)>(input), std::forward<decltype(twoState)>(twoState));
  auto __res__ = ::llvm::dyn_cast<ParityOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ParityOp ParityOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value input, /*optional*/::mlir::UnitAttr twoState) {
  return create(builder, builder.getLoc(), std::forward<decltype(result)>(result), std::forward<decltype(input)>(input), std::forward<decltype(twoState)>(twoState));
}

void ParityOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value input, /*optional*/::mlir::UnitAttr twoState) {
  odsState.addOperands(input);
  if (twoState) {
    odsState.getOrAddProperties<Properties>().twoState = twoState;
  }

        ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
        if (::mlir::succeeded(ParityOp::inferReturnTypes(odsBuilder.getContext(),
                      odsState.location, odsState.operands,
                      odsState.attributes.getDictionary(odsState.getContext()),
                      odsState.getRawProperties(),
                      odsState.regions, inferredReturnTypes)))
          odsState.addTypes(inferredReturnTypes);
        else
          ::mlir::detail::reportFatalInferReturnTypesError(odsState);
        
}

ParityOp ParityOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value input, /*optional*/::mlir::UnitAttr twoState) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(input)>(input), std::forward<decltype(twoState)>(twoState));
  auto __res__ = ::llvm::dyn_cast<ParityOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ParityOp ParityOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value input, /*optional*/::mlir::UnitAttr twoState) {
  return create(builder, builder.getLoc(), std::forward<decltype(input)>(input), std::forward<decltype(twoState)>(twoState));
}

void ParityOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value input, /*optional*/::mlir::UnitAttr twoState) {
  odsState.addOperands(input);
  if (twoState) {
    odsState.getOrAddProperties<Properties>().twoState = twoState;
  }
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

ParityOp ParityOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value input, /*optional*/::mlir::UnitAttr twoState) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(input)>(input), std::forward<decltype(twoState)>(twoState));
  auto __res__ = ::llvm::dyn_cast<ParityOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ParityOp ParityOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value input, /*optional*/::mlir::UnitAttr twoState) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(input)>(input), std::forward<decltype(twoState)>(twoState));
}

void ParityOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value input, /*optional*/bool twoState) {
  odsState.addOperands(input);
  if (twoState) {
    odsState.getOrAddProperties<Properties>().twoState = ((twoState) ? odsBuilder.getUnitAttr() : nullptr);
  }
  odsState.addTypes(result);
}

ParityOp ParityOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value input, /*optional*/bool twoState) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(result)>(result), std::forward<decltype(input)>(input), std::forward<decltype(twoState)>(twoState));
  auto __res__ = ::llvm::dyn_cast<ParityOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ParityOp ParityOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value input, /*optional*/bool twoState) {
  return create(builder, builder.getLoc(), std::forward<decltype(result)>(result), std::forward<decltype(input)>(input), std::forward<decltype(twoState)>(twoState));
}

void ParityOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value input, /*optional*/bool twoState) {
  odsState.addOperands(input);
  if (twoState) {
    odsState.getOrAddProperties<Properties>().twoState = ((twoState) ? odsBuilder.getUnitAttr() : nullptr);
  }

        ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
        if (::mlir::succeeded(ParityOp::inferReturnTypes(odsBuilder.getContext(),
                      odsState.location, odsState.operands,
                      odsState.attributes.getDictionary(odsState.getContext()),
                      odsState.getRawProperties(),
                      odsState.regions, inferredReturnTypes)))
          odsState.addTypes(inferredReturnTypes);
        else
          ::mlir::detail::reportFatalInferReturnTypesError(odsState);
        
}

ParityOp ParityOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value input, /*optional*/bool twoState) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(input)>(input), std::forward<decltype(twoState)>(twoState));
  auto __res__ = ::llvm::dyn_cast<ParityOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ParityOp ParityOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value input, /*optional*/bool twoState) {
  return create(builder, builder.getLoc(), std::forward<decltype(input)>(input), std::forward<decltype(twoState)>(twoState));
}

void ParityOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value input, /*optional*/bool twoState) {
  odsState.addOperands(input);
  if (twoState) {
    odsState.getOrAddProperties<Properties>().twoState = ((twoState) ? odsBuilder.getUnitAttr() : nullptr);
  }
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

ParityOp ParityOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value input, /*optional*/bool twoState) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(input)>(input), std::forward<decltype(twoState)>(twoState));
  auto __res__ = ::llvm::dyn_cast<ParityOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ParityOp ParityOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value input, /*optional*/bool twoState) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(input)>(input), std::forward<decltype(twoState)>(twoState));
}

void ParityOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<ParityOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

ParityOp ParityOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<ParityOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ParityOp ParityOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void ParityOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<ParityOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
  ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
  if (::mlir::succeeded(ParityOp::inferReturnTypes(odsBuilder.getContext(),
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

ParityOp ParityOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<ParityOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ParityOp ParityOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void ParityOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

ParityOp ParityOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<ParityOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ParityOp ParityOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

void ParityOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties &>(properties));
  odsState.addAttributes(discardableAttributes);

  ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
  if (::mlir::succeeded(ParityOp::inferReturnTypes(odsBuilder.getContext(),
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

ParityOp ParityOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<ParityOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ParityOp ParityOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult ParityOp::verifyInvariantsImpl() {
  auto tblgen_twoState = getProperties().twoState; (void)tblgen_twoState;

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Comb1(*this, tblgen_twoState, "twoState")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Comb2(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Comb3(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult ParityOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::llvm::LogicalResult ParityOp::inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::PropertyRef properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes) {
  inferredReturnTypes.resize(1);
  ::mlir::Builder odsBuilder(context);
  ::mlir::Type odsInferredType0 = odsBuilder.getIntegerType(1);
  inferredReturnTypes[0] = odsInferredType0;
  return ::mlir::success();
}

::mlir::ParseResult ParityOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::OpAsmParser::UnresolvedOperand inputRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> inputOperands(&inputRawOperand, 1);  ::llvm::SMLoc inputOperandsLoc;
  (void)inputOperandsLoc;
  ::mlir::Type inputRawType{};
  ::llvm::ArrayRef<::mlir::Type> inputTypes(&inputRawType, 1);
  if (::mlir::succeeded(parser.parseOptionalKeyword("bin"))) {
    result.getOrAddProperties<ParityOp::Properties>().twoState = parser.getBuilder().getUnitAttr();  }

  inputOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(inputRawOperand))
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

  if (parser.parseType(inputRawType))
    return ::mlir::failure();
  ::mlir::Type odsBuildableType0 = parser.getBuilder().getIntegerType(1);
  result.addTypes(odsBuildableType0);
  if (parser.resolveOperands(inputOperands, inputTypes, inputOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void ParityOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  if ((getTwoStateAttr() && getTwoStateAttr() != ((false) ? ::mlir::OpBuilder((*this)->getContext()).getUnitAttr() : nullptr))) {
    _odsPrinter << ' ' << "bin";
  }
  _odsPrinter << ' ';
  _odsPrinter << getInput();
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("twoState");
  {
     ::mlir::Builder odsBuilder(getContext());
     ::mlir::Attribute attr = getTwoStateAttr();
     if(attr && (attr == ((false) ? odsBuilder.getUnitAttr() : nullptr)))
       elidedAttrs.push_back("twoState");
  }
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
   _odsPrinter << getInput().getType();
}

void ParityOp::getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects) {
}


} // namespace circt::comb
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::comb::ParityOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::comb::detail::ParityOpGenericAdaptorBase::Properties)

namespace circt::comb {


//===----------------------------------------------------------------------===//
// ::circt::comb::ReplicateOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

ReplicateOpGenericAdaptorBase::ReplicateOpGenericAdaptorBase(ReplicateOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}


} // namespace detail
ReplicateOpAdaptor::ReplicateOpAdaptor(ReplicateOp op) : ReplicateOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult ReplicateOpAdaptor::verify(::mlir::Location loc) {
  return ::mlir::success();
}

::llvm::LogicalResult ReplicateOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }
      return ::mlir::success();
}

::mlir::Attribute ReplicateOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code ReplicateOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine();
}

std::optional<mlir::Attribute> ReplicateOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
  return std::nullopt;
}

void ReplicateOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
}

void ReplicateOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
}

::llvm::LogicalResult ReplicateOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    return ::mlir::success();
}

void ReplicateOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value operand, int32_t multiple) {
      auto bitWidth = llvm::cast<IntegerType>(operand.getType()).getWidth();
      auto resultType = odsBuilder.getIntegerType(bitWidth*multiple);
      return build(odsBuilder, odsState, resultType, operand);
    
}

ReplicateOp ReplicateOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, Value operand, int32_t multiple) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operand)>(operand), std::forward<decltype(multiple)>(multiple));
  auto __res__ = ::llvm::dyn_cast<ReplicateOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ReplicateOp ReplicateOp::create(::mlir::ImplicitLocOpBuilder &builder, Value operand, int32_t multiple) {
  return create(builder, builder.getLoc(), std::forward<decltype(operand)>(operand), std::forward<decltype(multiple)>(multiple));
}

void ReplicateOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value input) {
  odsState.addOperands(input);
  odsState.addTypes(result);
}

ReplicateOp ReplicateOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value input) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(result)>(result), std::forward<decltype(input)>(input));
  auto __res__ = ::llvm::dyn_cast<ReplicateOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ReplicateOp ReplicateOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value input) {
  return create(builder, builder.getLoc(), std::forward<decltype(result)>(result), std::forward<decltype(input)>(input));
}

void ReplicateOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value input) {
  odsState.addOperands(input);
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

ReplicateOp ReplicateOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value input) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(input)>(input));
  auto __res__ = ::llvm::dyn_cast<ReplicateOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ReplicateOp ReplicateOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value input) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(input)>(input));
}

void ReplicateOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

ReplicateOp ReplicateOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<ReplicateOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ReplicateOp ReplicateOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void ReplicateOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

ReplicateOp ReplicateOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<ReplicateOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ReplicateOp ReplicateOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult ReplicateOp::verifyInvariantsImpl() {
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Comb2(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Comb2(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult ReplicateOp::verifyInvariants() {
  if(::mlir::succeeded(verifyInvariantsImpl()) && ::mlir::succeeded(verify()))
    return ::mlir::success();
  return ::mlir::failure();
}

::mlir::ParseResult ReplicateOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::OpAsmParser::UnresolvedOperand inputRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> inputOperands(&inputRawOperand, 1);  ::llvm::SMLoc inputOperandsLoc;
  (void)inputOperandsLoc;
  ::llvm::ArrayRef<::mlir::Type> inputTypes;
  ::llvm::ArrayRef<::mlir::Type> resultTypes;

  inputOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(inputRawOperand))
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

  ::mlir::FunctionType input__result_functionType;
  if (parser.parseType(input__result_functionType))
    return ::mlir::failure();
  inputTypes = input__result_functionType.getInputs();
  resultTypes = input__result_functionType.getResults();
  result.addTypes(resultTypes);
  if (parser.resolveOperands(inputOperands, inputTypes, inputOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void ReplicateOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter << getInput();
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
  _odsPrinter.printFunctionalType(::llvm::ArrayRef<::mlir::Type>(getInput().getType()), ::llvm::ArrayRef<::mlir::Type>(getResult().getType()));
}

void ReplicateOp::getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects) {
}


} // namespace circt::comb
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::comb::ReplicateOp)

namespace circt::comb {


//===----------------------------------------------------------------------===//
// ::circt::comb::ReverseOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

ReverseOpGenericAdaptorBase::ReverseOpGenericAdaptorBase(ReverseOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}


} // namespace detail
ReverseOpAdaptor::ReverseOpAdaptor(ReverseOp op) : ReverseOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult ReverseOpAdaptor::verify(::mlir::Location loc) {
  return ::mlir::success();
}

::llvm::LogicalResult ReverseOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }
      return ::mlir::success();
}

::mlir::Attribute ReverseOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code ReverseOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine();
}

std::optional<mlir::Attribute> ReverseOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
  return std::nullopt;
}

void ReverseOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
}

void ReverseOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
}

::llvm::LogicalResult ReverseOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    return ::mlir::success();
}

void ReverseOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value input) {
  odsState.addOperands(input);
  odsState.addTypes(result);
}

ReverseOp ReverseOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value input) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(result)>(result), std::forward<decltype(input)>(input));
  auto __res__ = ::llvm::dyn_cast<ReverseOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ReverseOp ReverseOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value input) {
  return create(builder, builder.getLoc(), std::forward<decltype(result)>(result), std::forward<decltype(input)>(input));
}

void ReverseOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value input) {
  odsState.addOperands(input);

        ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
        if (::mlir::succeeded(ReverseOp::inferReturnTypes(odsBuilder.getContext(),
                      odsState.location, odsState.operands,
                      odsState.attributes.getDictionary(odsState.getContext()),
                      odsState.getRawProperties(),
                      odsState.regions, inferredReturnTypes)))
          odsState.addTypes(inferredReturnTypes);
        else
          ::mlir::detail::reportFatalInferReturnTypesError(odsState);
        
}

ReverseOp ReverseOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value input) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(input)>(input));
  auto __res__ = ::llvm::dyn_cast<ReverseOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ReverseOp ReverseOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value input) {
  return create(builder, builder.getLoc(), std::forward<decltype(input)>(input));
}

void ReverseOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value input) {
  odsState.addOperands(input);
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

ReverseOp ReverseOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value input) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(input)>(input));
  auto __res__ = ::llvm::dyn_cast<ReverseOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ReverseOp ReverseOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value input) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(input)>(input));
}

void ReverseOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

ReverseOp ReverseOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<ReverseOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ReverseOp ReverseOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void ReverseOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);

  ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
  if (::mlir::succeeded(ReverseOp::inferReturnTypes(odsBuilder.getContext(),
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

ReverseOp ReverseOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<ReverseOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ReverseOp ReverseOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void ReverseOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

ReverseOp ReverseOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<ReverseOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ReverseOp ReverseOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

void ReverseOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties &>(properties));
  odsState.addAttributes(discardableAttributes);

  ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
  if (::mlir::succeeded(ReverseOp::inferReturnTypes(odsBuilder.getContext(),
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

ReverseOp ReverseOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<ReverseOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ReverseOp ReverseOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult ReverseOp::verifyInvariantsImpl() {
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Comb2(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Comb2(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult ReverseOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::llvm::LogicalResult ReverseOp::inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::PropertyRef properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes) {
  inferredReturnTypes.resize(1);
  ::mlir::Builder odsBuilder(context);
  if (operands.size() <= 0)
    return ::mlir::failure();
  ::mlir::Type odsInferredType0 = operands[0].getType();
  inferredReturnTypes[0] = odsInferredType0;
  return ::mlir::success();
}

::mlir::ParseResult ReverseOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::OpAsmParser::UnresolvedOperand inputRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> inputOperands(&inputRawOperand, 1);  ::llvm::SMLoc inputOperandsLoc;
  (void)inputOperandsLoc;
  ::mlir::Type inputRawType{};
  ::llvm::ArrayRef<::mlir::Type> inputTypes(&inputRawType, 1);

  inputOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(inputRawOperand))
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
    ::circt::hw::TypeVariant<::mlir::IntegerType, ::circt::hw::IntType> type;
    if (parser.parseCustomTypeWithFallback(type))
      return ::mlir::failure();
    inputRawType = type;
  }
  result.addTypes(inputTypes[0]);
  if (parser.resolveOperands(inputOperands, inputTypes, inputOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void ReverseOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter << getInput();
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
  {
    auto type = getInput().getType();
    if (auto validType = ::llvm::dyn_cast<::circt::hw::TypeVariant<::mlir::IntegerType, ::circt::hw::IntType>>(type))
      _odsPrinter.printStrippedAttrOrType(validType);
   else
     _odsPrinter << type;
  }
}

void ReverseOp::getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects) {
}


} // namespace circt::comb
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::comb::ReverseOp)

namespace circt::comb {


//===----------------------------------------------------------------------===//
// ::circt::comb::ShlOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

ShlOpGenericAdaptorBase::ShlOpGenericAdaptorBase(ShlOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::mlir::UnitAttr ShlOpGenericAdaptorBase::getTwoStateAttr() {
  auto attr = ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(getProperties().twoState);
  if (!attr)
    attr = ((false) ? ::mlir::Builder(odsAttrs.getContext()).getUnitAttr() : nullptr);
  return attr;
}

bool ShlOpGenericAdaptorBase::getTwoState() {
  auto attr = getTwoStateAttr();
    if (!attr)
      return ((false) ? ::mlir::Builder(odsAttrs.getContext()).getUnitAttr() : nullptr) != nullptr;
  return attr != nullptr;
}


} // namespace detail
ShlOpAdaptor::ShlOpAdaptor(ShlOp op) : ShlOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult ShlOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_twoState = getProperties().twoState; (void)tblgen_twoState;

  if (tblgen_twoState && !((::llvm::isa<::mlir::UnitAttr>(tblgen_twoState))))
    return emitError(loc, "'comb.shl' op attribute 'twoState' failed to satisfy constraint: unit attribute");
  return ::mlir::success();
}

::llvm::LogicalResult ShlOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.twoState;
       auto attr = dict.get("twoState");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `twoState` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  return ::mlir::success();
}

::mlir::Attribute ShlOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.twoState;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("twoState",
                                       propStorage));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code ShlOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.twoState.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> ShlOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "twoState")
      return prop.twoState;
  return std::nullopt;
}

void ShlOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "twoState") {
       prop.twoState = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.twoState)>>(value);
       return;
    }
}

void ShlOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.twoState) attrs.append("twoState", prop.twoState);
}

::llvm::LogicalResult ShlOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getTwoStateAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Comb1(attr, "twoState", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult ShlOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readOptionalAttribute(prop.twoState)))
    return ::mlir::failure();
  return ::mlir::success();
}

void ShlOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;

  writer.writeOptionalAttribute(prop.twoState);
}

bool ShlOp::getTwoState() {
  auto attr = getTwoStateAttr();
    if (!attr)
      return ((false) ? ::mlir::Builder((*this)->getContext()).getUnitAttr() : nullptr) != nullptr;
  return attr != nullptr;
}

void ShlOp::setTwoState(bool attrValue) {
    auto &odsProp = getProperties().twoState;
    if (attrValue)
      odsProp = ((attrValue) ? ::mlir::Builder((*this)->getContext()).getUnitAttr() : nullptr);
    else
      odsProp = nullptr;
}

void ShlOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/::mlir::UnitAttr twoState) {
  odsState.addOperands(lhs);
  odsState.addOperands(rhs);
  if (twoState) {
    odsState.getOrAddProperties<Properties>().twoState = twoState;
  }
  odsState.addTypes(result);
}

ShlOp ShlOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/::mlir::UnitAttr twoState) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(result)>(result), std::forward<decltype(lhs)>(lhs), std::forward<decltype(rhs)>(rhs), std::forward<decltype(twoState)>(twoState));
  auto __res__ = ::llvm::dyn_cast<ShlOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ShlOp ShlOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/::mlir::UnitAttr twoState) {
  return create(builder, builder.getLoc(), std::forward<decltype(result)>(result), std::forward<decltype(lhs)>(lhs), std::forward<decltype(rhs)>(rhs), std::forward<decltype(twoState)>(twoState));
}

void ShlOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/::mlir::UnitAttr twoState) {
  odsState.addOperands(lhs);
  odsState.addOperands(rhs);
  if (twoState) {
    odsState.getOrAddProperties<Properties>().twoState = twoState;
  }

        ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
        if (::mlir::succeeded(ShlOp::inferReturnTypes(odsBuilder.getContext(),
                      odsState.location, odsState.operands,
                      odsState.attributes.getDictionary(odsState.getContext()),
                      odsState.getRawProperties(),
                      odsState.regions, inferredReturnTypes)))
          odsState.addTypes(inferredReturnTypes);
        else
          ::mlir::detail::reportFatalInferReturnTypesError(odsState);
        
}

ShlOp ShlOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/::mlir::UnitAttr twoState) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(lhs)>(lhs), std::forward<decltype(rhs)>(rhs), std::forward<decltype(twoState)>(twoState));
  auto __res__ = ::llvm::dyn_cast<ShlOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ShlOp ShlOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/::mlir::UnitAttr twoState) {
  return create(builder, builder.getLoc(), std::forward<decltype(lhs)>(lhs), std::forward<decltype(rhs)>(rhs), std::forward<decltype(twoState)>(twoState));
}

void ShlOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/::mlir::UnitAttr twoState) {
  odsState.addOperands(lhs);
  odsState.addOperands(rhs);
  if (twoState) {
    odsState.getOrAddProperties<Properties>().twoState = twoState;
  }
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

ShlOp ShlOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/::mlir::UnitAttr twoState) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(lhs)>(lhs), std::forward<decltype(rhs)>(rhs), std::forward<decltype(twoState)>(twoState));
  auto __res__ = ::llvm::dyn_cast<ShlOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ShlOp ShlOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/::mlir::UnitAttr twoState) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(lhs)>(lhs), std::forward<decltype(rhs)>(rhs), std::forward<decltype(twoState)>(twoState));
}

void ShlOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/bool twoState) {
  odsState.addOperands(lhs);
  odsState.addOperands(rhs);
  if (twoState) {
    odsState.getOrAddProperties<Properties>().twoState = ((twoState) ? odsBuilder.getUnitAttr() : nullptr);
  }
  odsState.addTypes(result);
}

ShlOp ShlOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/bool twoState) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(result)>(result), std::forward<decltype(lhs)>(lhs), std::forward<decltype(rhs)>(rhs), std::forward<decltype(twoState)>(twoState));
  auto __res__ = ::llvm::dyn_cast<ShlOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ShlOp ShlOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/bool twoState) {
  return create(builder, builder.getLoc(), std::forward<decltype(result)>(result), std::forward<decltype(lhs)>(lhs), std::forward<decltype(rhs)>(rhs), std::forward<decltype(twoState)>(twoState));
}

void ShlOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/bool twoState) {
  odsState.addOperands(lhs);
  odsState.addOperands(rhs);
  if (twoState) {
    odsState.getOrAddProperties<Properties>().twoState = ((twoState) ? odsBuilder.getUnitAttr() : nullptr);
  }

        ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
        if (::mlir::succeeded(ShlOp::inferReturnTypes(odsBuilder.getContext(),
                      odsState.location, odsState.operands,
                      odsState.attributes.getDictionary(odsState.getContext()),
                      odsState.getRawProperties(),
                      odsState.regions, inferredReturnTypes)))
          odsState.addTypes(inferredReturnTypes);
        else
          ::mlir::detail::reportFatalInferReturnTypesError(odsState);
        
}

ShlOp ShlOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/bool twoState) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(lhs)>(lhs), std::forward<decltype(rhs)>(rhs), std::forward<decltype(twoState)>(twoState));
  auto __res__ = ::llvm::dyn_cast<ShlOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ShlOp ShlOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/bool twoState) {
  return create(builder, builder.getLoc(), std::forward<decltype(lhs)>(lhs), std::forward<decltype(rhs)>(rhs), std::forward<decltype(twoState)>(twoState));
}

void ShlOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/bool twoState) {
  odsState.addOperands(lhs);
  odsState.addOperands(rhs);
  if (twoState) {
    odsState.getOrAddProperties<Properties>().twoState = ((twoState) ? odsBuilder.getUnitAttr() : nullptr);
  }
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

ShlOp ShlOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/bool twoState) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(lhs)>(lhs), std::forward<decltype(rhs)>(rhs), std::forward<decltype(twoState)>(twoState));
  auto __res__ = ::llvm::dyn_cast<ShlOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ShlOp ShlOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/bool twoState) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(lhs)>(lhs), std::forward<decltype(rhs)>(rhs), std::forward<decltype(twoState)>(twoState));
}

void ShlOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 2u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<ShlOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

ShlOp ShlOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<ShlOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ShlOp ShlOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void ShlOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 2u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<ShlOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
  ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
  if (::mlir::succeeded(ShlOp::inferReturnTypes(odsBuilder.getContext(),
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

ShlOp ShlOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<ShlOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ShlOp ShlOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void ShlOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 2u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

ShlOp ShlOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<ShlOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ShlOp ShlOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

void ShlOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 2u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties &>(properties));
  odsState.addAttributes(discardableAttributes);

  ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
  if (::mlir::succeeded(ShlOp::inferReturnTypes(odsBuilder.getContext(),
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

ShlOp ShlOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<ShlOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ShlOp ShlOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult ShlOp::verifyInvariantsImpl() {
  auto tblgen_twoState = getProperties().twoState; (void)tblgen_twoState;

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Comb1(*this, tblgen_twoState, "twoState")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Comb2(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSOperands(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Comb2(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Comb2(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult ShlOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

void ShlOp::getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context) {
  results.add(canonicalize);
}

::llvm::LogicalResult ShlOp::inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::PropertyRef properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes) {
  inferredReturnTypes.resize(1);
  ::mlir::Builder odsBuilder(context);
  if (operands.size() <= 0)
    return ::mlir::failure();
  ::mlir::Type odsInferredType0 = operands[0].getType();
  inferredReturnTypes[0] = odsInferredType0;
  return ::mlir::success();
}

::mlir::ParseResult ShlOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::OpAsmParser::UnresolvedOperand lhsRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> lhsOperands(&lhsRawOperand, 1);  ::llvm::SMLoc lhsOperandsLoc;
  (void)lhsOperandsLoc;
  ::mlir::OpAsmParser::UnresolvedOperand rhsRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> rhsOperands(&rhsRawOperand, 1);  ::llvm::SMLoc rhsOperandsLoc;
  (void)rhsOperandsLoc;
  ::mlir::Type resultRawType{};
  ::llvm::ArrayRef<::mlir::Type> resultTypes(&resultRawType, 1);
  if (::mlir::succeeded(parser.parseOptionalKeyword("bin"))) {
    result.getOrAddProperties<ShlOp::Properties>().twoState = parser.getBuilder().getUnitAttr();  }

  lhsOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(lhsRawOperand))
    return ::mlir::failure();
  if (parser.parseComma())
    return ::mlir::failure();

  rhsOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(rhsRawOperand))
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

  if (parser.parseType(resultRawType))
    return ::mlir::failure();
  result.addTypes(resultTypes);
  if (parser.resolveOperands(lhsOperands, resultTypes[0], lhsOperandsLoc, result.operands))
    return ::mlir::failure();
  if (parser.resolveOperands(rhsOperands, resultTypes[0], rhsOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void ShlOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  if ((getTwoStateAttr() && getTwoStateAttr() != ((false) ? ::mlir::OpBuilder((*this)->getContext()).getUnitAttr() : nullptr))) {
    _odsPrinter << ' ' << "bin";
  }
  _odsPrinter << ' ';
  _odsPrinter << getLhs();
  _odsPrinter << ",";
  _odsPrinter << ' ';
  _odsPrinter << getRhs();
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("twoState");
  {
     ::mlir::Builder odsBuilder(getContext());
     ::mlir::Attribute attr = getTwoStateAttr();
     if(attr && (attr == ((false) ? odsBuilder.getUnitAttr() : nullptr)))
       elidedAttrs.push_back("twoState");
  }
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
   _odsPrinter << getResult().getType();
}

void ShlOp::getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects) {
}


} // namespace circt::comb
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::comb::ShlOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::comb::detail::ShlOpGenericAdaptorBase::Properties)

namespace circt::comb {


//===----------------------------------------------------------------------===//
// ::circt::comb::ShrSOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

ShrSOpGenericAdaptorBase::ShrSOpGenericAdaptorBase(ShrSOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::mlir::UnitAttr ShrSOpGenericAdaptorBase::getTwoStateAttr() {
  auto attr = ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(getProperties().twoState);
  if (!attr)
    attr = ((false) ? ::mlir::Builder(odsAttrs.getContext()).getUnitAttr() : nullptr);
  return attr;
}

bool ShrSOpGenericAdaptorBase::getTwoState() {
  auto attr = getTwoStateAttr();
    if (!attr)
      return ((false) ? ::mlir::Builder(odsAttrs.getContext()).getUnitAttr() : nullptr) != nullptr;
  return attr != nullptr;
}


} // namespace detail
ShrSOpAdaptor::ShrSOpAdaptor(ShrSOp op) : ShrSOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult ShrSOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_twoState = getProperties().twoState; (void)tblgen_twoState;

  if (tblgen_twoState && !((::llvm::isa<::mlir::UnitAttr>(tblgen_twoState))))
    return emitError(loc, "'comb.shrs' op attribute 'twoState' failed to satisfy constraint: unit attribute");
  return ::mlir::success();
}

::llvm::LogicalResult ShrSOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.twoState;
       auto attr = dict.get("twoState");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `twoState` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  return ::mlir::success();
}

::mlir::Attribute ShrSOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.twoState;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("twoState",
                                       propStorage));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code ShrSOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.twoState.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> ShrSOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "twoState")
      return prop.twoState;
  return std::nullopt;
}

void ShrSOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "twoState") {
       prop.twoState = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.twoState)>>(value);
       return;
    }
}

void ShrSOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.twoState) attrs.append("twoState", prop.twoState);
}

::llvm::LogicalResult ShrSOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getTwoStateAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Comb1(attr, "twoState", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult ShrSOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readOptionalAttribute(prop.twoState)))
    return ::mlir::failure();
  return ::mlir::success();
}

void ShrSOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;

  writer.writeOptionalAttribute(prop.twoState);
}

bool ShrSOp::getTwoState() {
  auto attr = getTwoStateAttr();
    if (!attr)
      return ((false) ? ::mlir::Builder((*this)->getContext()).getUnitAttr() : nullptr) != nullptr;
  return attr != nullptr;
}

void ShrSOp::setTwoState(bool attrValue) {
    auto &odsProp = getProperties().twoState;
    if (attrValue)
      odsProp = ((attrValue) ? ::mlir::Builder((*this)->getContext()).getUnitAttr() : nullptr);
    else
      odsProp = nullptr;
}

void ShrSOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/::mlir::UnitAttr twoState) {
  odsState.addOperands(lhs);
  odsState.addOperands(rhs);
  if (twoState) {
    odsState.getOrAddProperties<Properties>().twoState = twoState;
  }
  odsState.addTypes(result);
}

ShrSOp ShrSOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/::mlir::UnitAttr twoState) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(result)>(result), std::forward<decltype(lhs)>(lhs), std::forward<decltype(rhs)>(rhs), std::forward<decltype(twoState)>(twoState));
  auto __res__ = ::llvm::dyn_cast<ShrSOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ShrSOp ShrSOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/::mlir::UnitAttr twoState) {
  return create(builder, builder.getLoc(), std::forward<decltype(result)>(result), std::forward<decltype(lhs)>(lhs), std::forward<decltype(rhs)>(rhs), std::forward<decltype(twoState)>(twoState));
}

void ShrSOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/::mlir::UnitAttr twoState) {
  odsState.addOperands(lhs);
  odsState.addOperands(rhs);
  if (twoState) {
    odsState.getOrAddProperties<Properties>().twoState = twoState;
  }

        ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
        if (::mlir::succeeded(ShrSOp::inferReturnTypes(odsBuilder.getContext(),
                      odsState.location, odsState.operands,
                      odsState.attributes.getDictionary(odsState.getContext()),
                      odsState.getRawProperties(),
                      odsState.regions, inferredReturnTypes)))
          odsState.addTypes(inferredReturnTypes);
        else
          ::mlir::detail::reportFatalInferReturnTypesError(odsState);
        
}

ShrSOp ShrSOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/::mlir::UnitAttr twoState) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(lhs)>(lhs), std::forward<decltype(rhs)>(rhs), std::forward<decltype(twoState)>(twoState));
  auto __res__ = ::llvm::dyn_cast<ShrSOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ShrSOp ShrSOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/::mlir::UnitAttr twoState) {
  return create(builder, builder.getLoc(), std::forward<decltype(lhs)>(lhs), std::forward<decltype(rhs)>(rhs), std::forward<decltype(twoState)>(twoState));
}

void ShrSOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/::mlir::UnitAttr twoState) {
  odsState.addOperands(lhs);
  odsState.addOperands(rhs);
  if (twoState) {
    odsState.getOrAddProperties<Properties>().twoState = twoState;
  }
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

ShrSOp ShrSOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/::mlir::UnitAttr twoState) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(lhs)>(lhs), std::forward<decltype(rhs)>(rhs), std::forward<decltype(twoState)>(twoState));
  auto __res__ = ::llvm::dyn_cast<ShrSOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ShrSOp ShrSOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/::mlir::UnitAttr twoState) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(lhs)>(lhs), std::forward<decltype(rhs)>(rhs), std::forward<decltype(twoState)>(twoState));
}

void ShrSOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/bool twoState) {
  odsState.addOperands(lhs);
  odsState.addOperands(rhs);
  if (twoState) {
    odsState.getOrAddProperties<Properties>().twoState = ((twoState) ? odsBuilder.getUnitAttr() : nullptr);
  }
  odsState.addTypes(result);
}

ShrSOp ShrSOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/bool twoState) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(result)>(result), std::forward<decltype(lhs)>(lhs), std::forward<decltype(rhs)>(rhs), std::forward<decltype(twoState)>(twoState));
  auto __res__ = ::llvm::dyn_cast<ShrSOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ShrSOp ShrSOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/bool twoState) {
  return create(builder, builder.getLoc(), std::forward<decltype(result)>(result), std::forward<decltype(lhs)>(lhs), std::forward<decltype(rhs)>(rhs), std::forward<decltype(twoState)>(twoState));
}

void ShrSOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/bool twoState) {
  odsState.addOperands(lhs);
  odsState.addOperands(rhs);
  if (twoState) {
    odsState.getOrAddProperties<Properties>().twoState = ((twoState) ? odsBuilder.getUnitAttr() : nullptr);
  }

        ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
        if (::mlir::succeeded(ShrSOp::inferReturnTypes(odsBuilder.getContext(),
                      odsState.location, odsState.operands,
                      odsState.attributes.getDictionary(odsState.getContext()),
                      odsState.getRawProperties(),
                      odsState.regions, inferredReturnTypes)))
          odsState.addTypes(inferredReturnTypes);
        else
          ::mlir::detail::reportFatalInferReturnTypesError(odsState);
        
}

ShrSOp ShrSOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/bool twoState) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(lhs)>(lhs), std::forward<decltype(rhs)>(rhs), std::forward<decltype(twoState)>(twoState));
  auto __res__ = ::llvm::dyn_cast<ShrSOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ShrSOp ShrSOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/bool twoState) {
  return create(builder, builder.getLoc(), std::forward<decltype(lhs)>(lhs), std::forward<decltype(rhs)>(rhs), std::forward<decltype(twoState)>(twoState));
}

void ShrSOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/bool twoState) {
  odsState.addOperands(lhs);
  odsState.addOperands(rhs);
  if (twoState) {
    odsState.getOrAddProperties<Properties>().twoState = ((twoState) ? odsBuilder.getUnitAttr() : nullptr);
  }
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

ShrSOp ShrSOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/bool twoState) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(lhs)>(lhs), std::forward<decltype(rhs)>(rhs), std::forward<decltype(twoState)>(twoState));
  auto __res__ = ::llvm::dyn_cast<ShrSOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ShrSOp ShrSOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/bool twoState) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(lhs)>(lhs), std::forward<decltype(rhs)>(rhs), std::forward<decltype(twoState)>(twoState));
}

void ShrSOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 2u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<ShrSOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

ShrSOp ShrSOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<ShrSOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ShrSOp ShrSOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void ShrSOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 2u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<ShrSOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
  ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
  if (::mlir::succeeded(ShrSOp::inferReturnTypes(odsBuilder.getContext(),
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

ShrSOp ShrSOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<ShrSOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ShrSOp ShrSOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void ShrSOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 2u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

ShrSOp ShrSOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<ShrSOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ShrSOp ShrSOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

void ShrSOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 2u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties &>(properties));
  odsState.addAttributes(discardableAttributes);

  ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
  if (::mlir::succeeded(ShrSOp::inferReturnTypes(odsBuilder.getContext(),
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

ShrSOp ShrSOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<ShrSOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ShrSOp ShrSOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult ShrSOp::verifyInvariantsImpl() {
  auto tblgen_twoState = getProperties().twoState; (void)tblgen_twoState;

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Comb1(*this, tblgen_twoState, "twoState")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Comb2(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSOperands(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Comb2(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Comb2(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult ShrSOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

void ShrSOp::getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context) {
  results.add(canonicalize);
}

::llvm::LogicalResult ShrSOp::inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::PropertyRef properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes) {
  inferredReturnTypes.resize(1);
  ::mlir::Builder odsBuilder(context);
  if (operands.size() <= 0)
    return ::mlir::failure();
  ::mlir::Type odsInferredType0 = operands[0].getType();
  inferredReturnTypes[0] = odsInferredType0;
  return ::mlir::success();
}

::mlir::ParseResult ShrSOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::OpAsmParser::UnresolvedOperand lhsRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> lhsOperands(&lhsRawOperand, 1);  ::llvm::SMLoc lhsOperandsLoc;
  (void)lhsOperandsLoc;
  ::mlir::OpAsmParser::UnresolvedOperand rhsRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> rhsOperands(&rhsRawOperand, 1);  ::llvm::SMLoc rhsOperandsLoc;
  (void)rhsOperandsLoc;
  ::mlir::Type resultRawType{};
  ::llvm::ArrayRef<::mlir::Type> resultTypes(&resultRawType, 1);
  if (::mlir::succeeded(parser.parseOptionalKeyword("bin"))) {
    result.getOrAddProperties<ShrSOp::Properties>().twoState = parser.getBuilder().getUnitAttr();  }

  lhsOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(lhsRawOperand))
    return ::mlir::failure();
  if (parser.parseComma())
    return ::mlir::failure();

  rhsOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(rhsRawOperand))
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

  if (parser.parseType(resultRawType))
    return ::mlir::failure();
  result.addTypes(resultTypes);
  if (parser.resolveOperands(lhsOperands, resultTypes[0], lhsOperandsLoc, result.operands))
    return ::mlir::failure();
  if (parser.resolveOperands(rhsOperands, resultTypes[0], rhsOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void ShrSOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  if ((getTwoStateAttr() && getTwoStateAttr() != ((false) ? ::mlir::OpBuilder((*this)->getContext()).getUnitAttr() : nullptr))) {
    _odsPrinter << ' ' << "bin";
  }
  _odsPrinter << ' ';
  _odsPrinter << getLhs();
  _odsPrinter << ",";
  _odsPrinter << ' ';
  _odsPrinter << getRhs();
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("twoState");
  {
     ::mlir::Builder odsBuilder(getContext());
     ::mlir::Attribute attr = getTwoStateAttr();
     if(attr && (attr == ((false) ? odsBuilder.getUnitAttr() : nullptr)))
       elidedAttrs.push_back("twoState");
  }
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
   _odsPrinter << getResult().getType();
}

void ShrSOp::getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects) {
}


} // namespace circt::comb
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::comb::ShrSOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::comb::detail::ShrSOpGenericAdaptorBase::Properties)

namespace circt::comb {


//===----------------------------------------------------------------------===//
// ::circt::comb::ShrUOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

ShrUOpGenericAdaptorBase::ShrUOpGenericAdaptorBase(ShrUOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::mlir::UnitAttr ShrUOpGenericAdaptorBase::getTwoStateAttr() {
  auto attr = ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(getProperties().twoState);
  if (!attr)
    attr = ((false) ? ::mlir::Builder(odsAttrs.getContext()).getUnitAttr() : nullptr);
  return attr;
}

bool ShrUOpGenericAdaptorBase::getTwoState() {
  auto attr = getTwoStateAttr();
    if (!attr)
      return ((false) ? ::mlir::Builder(odsAttrs.getContext()).getUnitAttr() : nullptr) != nullptr;
  return attr != nullptr;
}


} // namespace detail
ShrUOpAdaptor::ShrUOpAdaptor(ShrUOp op) : ShrUOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult ShrUOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_twoState = getProperties().twoState; (void)tblgen_twoState;

  if (tblgen_twoState && !((::llvm::isa<::mlir::UnitAttr>(tblgen_twoState))))
    return emitError(loc, "'comb.shru' op attribute 'twoState' failed to satisfy constraint: unit attribute");
  return ::mlir::success();
}

::llvm::LogicalResult ShrUOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.twoState;
       auto attr = dict.get("twoState");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `twoState` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  return ::mlir::success();
}

::mlir::Attribute ShrUOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.twoState;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("twoState",
                                       propStorage));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code ShrUOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.twoState.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> ShrUOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "twoState")
      return prop.twoState;
  return std::nullopt;
}

void ShrUOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "twoState") {
       prop.twoState = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.twoState)>>(value);
       return;
    }
}

void ShrUOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.twoState) attrs.append("twoState", prop.twoState);
}

::llvm::LogicalResult ShrUOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getTwoStateAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Comb1(attr, "twoState", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult ShrUOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readOptionalAttribute(prop.twoState)))
    return ::mlir::failure();
  return ::mlir::success();
}

void ShrUOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;

  writer.writeOptionalAttribute(prop.twoState);
}

bool ShrUOp::getTwoState() {
  auto attr = getTwoStateAttr();
    if (!attr)
      return ((false) ? ::mlir::Builder((*this)->getContext()).getUnitAttr() : nullptr) != nullptr;
  return attr != nullptr;
}

void ShrUOp::setTwoState(bool attrValue) {
    auto &odsProp = getProperties().twoState;
    if (attrValue)
      odsProp = ((attrValue) ? ::mlir::Builder((*this)->getContext()).getUnitAttr() : nullptr);
    else
      odsProp = nullptr;
}

void ShrUOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/::mlir::UnitAttr twoState) {
  odsState.addOperands(lhs);
  odsState.addOperands(rhs);
  if (twoState) {
    odsState.getOrAddProperties<Properties>().twoState = twoState;
  }
  odsState.addTypes(result);
}

ShrUOp ShrUOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/::mlir::UnitAttr twoState) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(result)>(result), std::forward<decltype(lhs)>(lhs), std::forward<decltype(rhs)>(rhs), std::forward<decltype(twoState)>(twoState));
  auto __res__ = ::llvm::dyn_cast<ShrUOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ShrUOp ShrUOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/::mlir::UnitAttr twoState) {
  return create(builder, builder.getLoc(), std::forward<decltype(result)>(result), std::forward<decltype(lhs)>(lhs), std::forward<decltype(rhs)>(rhs), std::forward<decltype(twoState)>(twoState));
}

void ShrUOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/::mlir::UnitAttr twoState) {
  odsState.addOperands(lhs);
  odsState.addOperands(rhs);
  if (twoState) {
    odsState.getOrAddProperties<Properties>().twoState = twoState;
  }

        ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
        if (::mlir::succeeded(ShrUOp::inferReturnTypes(odsBuilder.getContext(),
                      odsState.location, odsState.operands,
                      odsState.attributes.getDictionary(odsState.getContext()),
                      odsState.getRawProperties(),
                      odsState.regions, inferredReturnTypes)))
          odsState.addTypes(inferredReturnTypes);
        else
          ::mlir::detail::reportFatalInferReturnTypesError(odsState);
        
}

ShrUOp ShrUOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/::mlir::UnitAttr twoState) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(lhs)>(lhs), std::forward<decltype(rhs)>(rhs), std::forward<decltype(twoState)>(twoState));
  auto __res__ = ::llvm::dyn_cast<ShrUOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ShrUOp ShrUOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/::mlir::UnitAttr twoState) {
  return create(builder, builder.getLoc(), std::forward<decltype(lhs)>(lhs), std::forward<decltype(rhs)>(rhs), std::forward<decltype(twoState)>(twoState));
}

void ShrUOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/::mlir::UnitAttr twoState) {
  odsState.addOperands(lhs);
  odsState.addOperands(rhs);
  if (twoState) {
    odsState.getOrAddProperties<Properties>().twoState = twoState;
  }
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

ShrUOp ShrUOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/::mlir::UnitAttr twoState) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(lhs)>(lhs), std::forward<decltype(rhs)>(rhs), std::forward<decltype(twoState)>(twoState));
  auto __res__ = ::llvm::dyn_cast<ShrUOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ShrUOp ShrUOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/::mlir::UnitAttr twoState) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(lhs)>(lhs), std::forward<decltype(rhs)>(rhs), std::forward<decltype(twoState)>(twoState));
}

void ShrUOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/bool twoState) {
  odsState.addOperands(lhs);
  odsState.addOperands(rhs);
  if (twoState) {
    odsState.getOrAddProperties<Properties>().twoState = ((twoState) ? odsBuilder.getUnitAttr() : nullptr);
  }
  odsState.addTypes(result);
}

ShrUOp ShrUOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/bool twoState) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(result)>(result), std::forward<decltype(lhs)>(lhs), std::forward<decltype(rhs)>(rhs), std::forward<decltype(twoState)>(twoState));
  auto __res__ = ::llvm::dyn_cast<ShrUOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ShrUOp ShrUOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/bool twoState) {
  return create(builder, builder.getLoc(), std::forward<decltype(result)>(result), std::forward<decltype(lhs)>(lhs), std::forward<decltype(rhs)>(rhs), std::forward<decltype(twoState)>(twoState));
}

void ShrUOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/bool twoState) {
  odsState.addOperands(lhs);
  odsState.addOperands(rhs);
  if (twoState) {
    odsState.getOrAddProperties<Properties>().twoState = ((twoState) ? odsBuilder.getUnitAttr() : nullptr);
  }

        ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
        if (::mlir::succeeded(ShrUOp::inferReturnTypes(odsBuilder.getContext(),
                      odsState.location, odsState.operands,
                      odsState.attributes.getDictionary(odsState.getContext()),
                      odsState.getRawProperties(),
                      odsState.regions, inferredReturnTypes)))
          odsState.addTypes(inferredReturnTypes);
        else
          ::mlir::detail::reportFatalInferReturnTypesError(odsState);
        
}

ShrUOp ShrUOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/bool twoState) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(lhs)>(lhs), std::forward<decltype(rhs)>(rhs), std::forward<decltype(twoState)>(twoState));
  auto __res__ = ::llvm::dyn_cast<ShrUOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ShrUOp ShrUOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/bool twoState) {
  return create(builder, builder.getLoc(), std::forward<decltype(lhs)>(lhs), std::forward<decltype(rhs)>(rhs), std::forward<decltype(twoState)>(twoState));
}

void ShrUOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/bool twoState) {
  odsState.addOperands(lhs);
  odsState.addOperands(rhs);
  if (twoState) {
    odsState.getOrAddProperties<Properties>().twoState = ((twoState) ? odsBuilder.getUnitAttr() : nullptr);
  }
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

ShrUOp ShrUOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/bool twoState) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(lhs)>(lhs), std::forward<decltype(rhs)>(rhs), std::forward<decltype(twoState)>(twoState));
  auto __res__ = ::llvm::dyn_cast<ShrUOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ShrUOp ShrUOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/bool twoState) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(lhs)>(lhs), std::forward<decltype(rhs)>(rhs), std::forward<decltype(twoState)>(twoState));
}

void ShrUOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 2u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<ShrUOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

ShrUOp ShrUOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<ShrUOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ShrUOp ShrUOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void ShrUOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 2u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<ShrUOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
  ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
  if (::mlir::succeeded(ShrUOp::inferReturnTypes(odsBuilder.getContext(),
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

ShrUOp ShrUOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<ShrUOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ShrUOp ShrUOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void ShrUOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 2u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

ShrUOp ShrUOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<ShrUOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ShrUOp ShrUOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

void ShrUOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 2u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties &>(properties));
  odsState.addAttributes(discardableAttributes);

  ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
  if (::mlir::succeeded(ShrUOp::inferReturnTypes(odsBuilder.getContext(),
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

ShrUOp ShrUOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<ShrUOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ShrUOp ShrUOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult ShrUOp::verifyInvariantsImpl() {
  auto tblgen_twoState = getProperties().twoState; (void)tblgen_twoState;

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Comb1(*this, tblgen_twoState, "twoState")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Comb2(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSOperands(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Comb2(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Comb2(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult ShrUOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

void ShrUOp::getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context) {
  results.add(canonicalize);
}

::llvm::LogicalResult ShrUOp::inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::PropertyRef properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes) {
  inferredReturnTypes.resize(1);
  ::mlir::Builder odsBuilder(context);
  if (operands.size() <= 0)
    return ::mlir::failure();
  ::mlir::Type odsInferredType0 = operands[0].getType();
  inferredReturnTypes[0] = odsInferredType0;
  return ::mlir::success();
}

::mlir::ParseResult ShrUOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::OpAsmParser::UnresolvedOperand lhsRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> lhsOperands(&lhsRawOperand, 1);  ::llvm::SMLoc lhsOperandsLoc;
  (void)lhsOperandsLoc;
  ::mlir::OpAsmParser::UnresolvedOperand rhsRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> rhsOperands(&rhsRawOperand, 1);  ::llvm::SMLoc rhsOperandsLoc;
  (void)rhsOperandsLoc;
  ::mlir::Type resultRawType{};
  ::llvm::ArrayRef<::mlir::Type> resultTypes(&resultRawType, 1);
  if (::mlir::succeeded(parser.parseOptionalKeyword("bin"))) {
    result.getOrAddProperties<ShrUOp::Properties>().twoState = parser.getBuilder().getUnitAttr();  }

  lhsOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(lhsRawOperand))
    return ::mlir::failure();
  if (parser.parseComma())
    return ::mlir::failure();

  rhsOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(rhsRawOperand))
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

  if (parser.parseType(resultRawType))
    return ::mlir::failure();
  result.addTypes(resultTypes);
  if (parser.resolveOperands(lhsOperands, resultTypes[0], lhsOperandsLoc, result.operands))
    return ::mlir::failure();
  if (parser.resolveOperands(rhsOperands, resultTypes[0], rhsOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void ShrUOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  if ((getTwoStateAttr() && getTwoStateAttr() != ((false) ? ::mlir::OpBuilder((*this)->getContext()).getUnitAttr() : nullptr))) {
    _odsPrinter << ' ' << "bin";
  }
  _odsPrinter << ' ';
  _odsPrinter << getLhs();
  _odsPrinter << ",";
  _odsPrinter << ' ';
  _odsPrinter << getRhs();
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("twoState");
  {
     ::mlir::Builder odsBuilder(getContext());
     ::mlir::Attribute attr = getTwoStateAttr();
     if(attr && (attr == ((false) ? odsBuilder.getUnitAttr() : nullptr)))
       elidedAttrs.push_back("twoState");
  }
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
   _odsPrinter << getResult().getType();
}

void ShrUOp::getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects) {
}


} // namespace circt::comb
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::comb::ShrUOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::comb::detail::ShrUOpGenericAdaptorBase::Properties)

namespace circt::comb {


//===----------------------------------------------------------------------===//
// ::circt::comb::SubOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

SubOpGenericAdaptorBase::SubOpGenericAdaptorBase(SubOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::mlir::UnitAttr SubOpGenericAdaptorBase::getTwoStateAttr() {
  auto attr = ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(getProperties().twoState);
  if (!attr)
    attr = ((false) ? ::mlir::Builder(odsAttrs.getContext()).getUnitAttr() : nullptr);
  return attr;
}

bool SubOpGenericAdaptorBase::getTwoState() {
  auto attr = getTwoStateAttr();
    if (!attr)
      return ((false) ? ::mlir::Builder(odsAttrs.getContext()).getUnitAttr() : nullptr) != nullptr;
  return attr != nullptr;
}


} // namespace detail
SubOpAdaptor::SubOpAdaptor(SubOp op) : SubOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult SubOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_twoState = getProperties().twoState; (void)tblgen_twoState;

  if (tblgen_twoState && !((::llvm::isa<::mlir::UnitAttr>(tblgen_twoState))))
    return emitError(loc, "'comb.sub' op attribute 'twoState' failed to satisfy constraint: unit attribute");
  return ::mlir::success();
}

::llvm::LogicalResult SubOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.twoState;
       auto attr = dict.get("twoState");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `twoState` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  return ::mlir::success();
}

::mlir::Attribute SubOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.twoState;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("twoState",
                                       propStorage));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code SubOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.twoState.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> SubOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "twoState")
      return prop.twoState;
  return std::nullopt;
}

void SubOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "twoState") {
       prop.twoState = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.twoState)>>(value);
       return;
    }
}

void SubOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.twoState) attrs.append("twoState", prop.twoState);
}

::llvm::LogicalResult SubOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getTwoStateAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Comb1(attr, "twoState", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult SubOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readOptionalAttribute(prop.twoState)))
    return ::mlir::failure();
  return ::mlir::success();
}

void SubOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;

  writer.writeOptionalAttribute(prop.twoState);
}

bool SubOp::getTwoState() {
  auto attr = getTwoStateAttr();
    if (!attr)
      return ((false) ? ::mlir::Builder((*this)->getContext()).getUnitAttr() : nullptr) != nullptr;
  return attr != nullptr;
}

void SubOp::setTwoState(bool attrValue) {
    auto &odsProp = getProperties().twoState;
    if (attrValue)
      odsProp = ((attrValue) ? ::mlir::Builder((*this)->getContext()).getUnitAttr() : nullptr);
    else
      odsProp = nullptr;
}

void SubOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/::mlir::UnitAttr twoState) {
  odsState.addOperands(lhs);
  odsState.addOperands(rhs);
  if (twoState) {
    odsState.getOrAddProperties<Properties>().twoState = twoState;
  }
  odsState.addTypes(result);
}

SubOp SubOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/::mlir::UnitAttr twoState) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(result)>(result), std::forward<decltype(lhs)>(lhs), std::forward<decltype(rhs)>(rhs), std::forward<decltype(twoState)>(twoState));
  auto __res__ = ::llvm::dyn_cast<SubOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SubOp SubOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/::mlir::UnitAttr twoState) {
  return create(builder, builder.getLoc(), std::forward<decltype(result)>(result), std::forward<decltype(lhs)>(lhs), std::forward<decltype(rhs)>(rhs), std::forward<decltype(twoState)>(twoState));
}

void SubOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/::mlir::UnitAttr twoState) {
  odsState.addOperands(lhs);
  odsState.addOperands(rhs);
  if (twoState) {
    odsState.getOrAddProperties<Properties>().twoState = twoState;
  }

        ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
        if (::mlir::succeeded(SubOp::inferReturnTypes(odsBuilder.getContext(),
                      odsState.location, odsState.operands,
                      odsState.attributes.getDictionary(odsState.getContext()),
                      odsState.getRawProperties(),
                      odsState.regions, inferredReturnTypes)))
          odsState.addTypes(inferredReturnTypes);
        else
          ::mlir::detail::reportFatalInferReturnTypesError(odsState);
        
}

SubOp SubOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/::mlir::UnitAttr twoState) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(lhs)>(lhs), std::forward<decltype(rhs)>(rhs), std::forward<decltype(twoState)>(twoState));
  auto __res__ = ::llvm::dyn_cast<SubOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SubOp SubOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/::mlir::UnitAttr twoState) {
  return create(builder, builder.getLoc(), std::forward<decltype(lhs)>(lhs), std::forward<decltype(rhs)>(rhs), std::forward<decltype(twoState)>(twoState));
}

void SubOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/::mlir::UnitAttr twoState) {
  odsState.addOperands(lhs);
  odsState.addOperands(rhs);
  if (twoState) {
    odsState.getOrAddProperties<Properties>().twoState = twoState;
  }
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

SubOp SubOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/::mlir::UnitAttr twoState) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(lhs)>(lhs), std::forward<decltype(rhs)>(rhs), std::forward<decltype(twoState)>(twoState));
  auto __res__ = ::llvm::dyn_cast<SubOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SubOp SubOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/::mlir::UnitAttr twoState) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(lhs)>(lhs), std::forward<decltype(rhs)>(rhs), std::forward<decltype(twoState)>(twoState));
}

void SubOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/bool twoState) {
  odsState.addOperands(lhs);
  odsState.addOperands(rhs);
  if (twoState) {
    odsState.getOrAddProperties<Properties>().twoState = ((twoState) ? odsBuilder.getUnitAttr() : nullptr);
  }
  odsState.addTypes(result);
}

SubOp SubOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/bool twoState) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(result)>(result), std::forward<decltype(lhs)>(lhs), std::forward<decltype(rhs)>(rhs), std::forward<decltype(twoState)>(twoState));
  auto __res__ = ::llvm::dyn_cast<SubOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SubOp SubOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/bool twoState) {
  return create(builder, builder.getLoc(), std::forward<decltype(result)>(result), std::forward<decltype(lhs)>(lhs), std::forward<decltype(rhs)>(rhs), std::forward<decltype(twoState)>(twoState));
}

void SubOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/bool twoState) {
  odsState.addOperands(lhs);
  odsState.addOperands(rhs);
  if (twoState) {
    odsState.getOrAddProperties<Properties>().twoState = ((twoState) ? odsBuilder.getUnitAttr() : nullptr);
  }

        ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
        if (::mlir::succeeded(SubOp::inferReturnTypes(odsBuilder.getContext(),
                      odsState.location, odsState.operands,
                      odsState.attributes.getDictionary(odsState.getContext()),
                      odsState.getRawProperties(),
                      odsState.regions, inferredReturnTypes)))
          odsState.addTypes(inferredReturnTypes);
        else
          ::mlir::detail::reportFatalInferReturnTypesError(odsState);
        
}

SubOp SubOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/bool twoState) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(lhs)>(lhs), std::forward<decltype(rhs)>(rhs), std::forward<decltype(twoState)>(twoState));
  auto __res__ = ::llvm::dyn_cast<SubOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SubOp SubOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/bool twoState) {
  return create(builder, builder.getLoc(), std::forward<decltype(lhs)>(lhs), std::forward<decltype(rhs)>(rhs), std::forward<decltype(twoState)>(twoState));
}

void SubOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/bool twoState) {
  odsState.addOperands(lhs);
  odsState.addOperands(rhs);
  if (twoState) {
    odsState.getOrAddProperties<Properties>().twoState = ((twoState) ? odsBuilder.getUnitAttr() : nullptr);
  }
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

SubOp SubOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/bool twoState) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(lhs)>(lhs), std::forward<decltype(rhs)>(rhs), std::forward<decltype(twoState)>(twoState));
  auto __res__ = ::llvm::dyn_cast<SubOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SubOp SubOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value lhs, ::mlir::Value rhs, /*optional*/bool twoState) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(lhs)>(lhs), std::forward<decltype(rhs)>(rhs), std::forward<decltype(twoState)>(twoState));
}

void SubOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 2u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<SubOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

SubOp SubOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<SubOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SubOp SubOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void SubOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 2u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<SubOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
  ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
  if (::mlir::succeeded(SubOp::inferReturnTypes(odsBuilder.getContext(),
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

SubOp SubOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<SubOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SubOp SubOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void SubOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 2u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

SubOp SubOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<SubOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SubOp SubOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

void SubOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 2u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties &>(properties));
  odsState.addAttributes(discardableAttributes);

  ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
  if (::mlir::succeeded(SubOp::inferReturnTypes(odsBuilder.getContext(),
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

SubOp SubOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<SubOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SubOp SubOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult SubOp::verifyInvariantsImpl() {
  auto tblgen_twoState = getProperties().twoState; (void)tblgen_twoState;

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Comb1(*this, tblgen_twoState, "twoState")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Comb2(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSOperands(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Comb2(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Comb2(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult SubOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

void SubOp::getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context) {
  results.add(canonicalize);
}

::llvm::LogicalResult SubOp::inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::PropertyRef properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes) {
  inferredReturnTypes.resize(1);
  ::mlir::Builder odsBuilder(context);
  if (operands.size() <= 0)
    return ::mlir::failure();
  ::mlir::Type odsInferredType0 = operands[0].getType();
  inferredReturnTypes[0] = odsInferredType0;
  return ::mlir::success();
}

::mlir::ParseResult SubOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::OpAsmParser::UnresolvedOperand lhsRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> lhsOperands(&lhsRawOperand, 1);  ::llvm::SMLoc lhsOperandsLoc;
  (void)lhsOperandsLoc;
  ::mlir::OpAsmParser::UnresolvedOperand rhsRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> rhsOperands(&rhsRawOperand, 1);  ::llvm::SMLoc rhsOperandsLoc;
  (void)rhsOperandsLoc;
  ::mlir::Type resultRawType{};
  ::llvm::ArrayRef<::mlir::Type> resultTypes(&resultRawType, 1);
  if (::mlir::succeeded(parser.parseOptionalKeyword("bin"))) {
    result.getOrAddProperties<SubOp::Properties>().twoState = parser.getBuilder().getUnitAttr();  }

  lhsOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(lhsRawOperand))
    return ::mlir::failure();
  if (parser.parseComma())
    return ::mlir::failure();

  rhsOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(rhsRawOperand))
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

  if (parser.parseType(resultRawType))
    return ::mlir::failure();
  result.addTypes(resultTypes);
  if (parser.resolveOperands(lhsOperands, resultTypes[0], lhsOperandsLoc, result.operands))
    return ::mlir::failure();
  if (parser.resolveOperands(rhsOperands, resultTypes[0], rhsOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void SubOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  if ((getTwoStateAttr() && getTwoStateAttr() != ((false) ? ::mlir::OpBuilder((*this)->getContext()).getUnitAttr() : nullptr))) {
    _odsPrinter << ' ' << "bin";
  }
  _odsPrinter << ' ';
  _odsPrinter << getLhs();
  _odsPrinter << ",";
  _odsPrinter << ' ';
  _odsPrinter << getRhs();
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("twoState");
  {
     ::mlir::Builder odsBuilder(getContext());
     ::mlir::Attribute attr = getTwoStateAttr();
     if(attr && (attr == ((false) ? odsBuilder.getUnitAttr() : nullptr)))
       elidedAttrs.push_back("twoState");
  }
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
   _odsPrinter << getResult().getType();
}

void SubOp::getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects) {
}


} // namespace circt::comb
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::comb::SubOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::comb::detail::SubOpGenericAdaptorBase::Properties)

namespace circt::comb {


//===----------------------------------------------------------------------===//
// ::circt::comb::TruthTableOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

TruthTableOpGenericAdaptorBase::TruthTableOpGenericAdaptorBase(TruthTableOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

std::pair<unsigned, unsigned> TruthTableOpGenericAdaptorBase::getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
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

::llvm::ArrayRef<bool> TruthTableOpGenericAdaptorBase::getLookupTable() {
  auto attr = getLookupTableAttr();
  return attr;
}


} // namespace detail
TruthTableOpAdaptor::TruthTableOpAdaptor(TruthTableOp op) : TruthTableOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult TruthTableOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_lookupTable = getProperties().lookupTable; (void)tblgen_lookupTable;
  if (!tblgen_lookupTable) return emitError(loc, "'comb.truth_table' op requires attribute 'lookupTable'");

  if (tblgen_lookupTable && !((::llvm::isa<::mlir::DenseBoolArrayAttr>(tblgen_lookupTable))))
    return emitError(loc, "'comb.truth_table' op attribute 'lookupTable' failed to satisfy constraint: i1 dense array attribute");
  return ::mlir::success();
}

std::pair<unsigned, unsigned> TruthTableOp::getODSOperandIndexAndLength(unsigned index) {
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

::mlir::MutableOperandRange TruthTableOp::getInputsMutable() {
  auto range = getODSOperandIndexAndLength(0);
  auto mutableRange = ::mlir::MutableOperandRange(getOperation(), range.first, range.second);
  return mutableRange;
}

::llvm::LogicalResult TruthTableOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.lookupTable;
       auto attr = dict.get("lookupTable");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `lookupTable` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  return ::mlir::success();
}

::mlir::Attribute TruthTableOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.lookupTable;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("lookupTable",
                                       propStorage));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code TruthTableOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.lookupTable.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> TruthTableOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "lookupTable")
      return prop.lookupTable;
  return std::nullopt;
}

void TruthTableOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "lookupTable") {
       prop.lookupTable = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.lookupTable)>>(value);
       return;
    }
}

void TruthTableOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.lookupTable) attrs.append("lookupTable", prop.lookupTable);
}

::llvm::LogicalResult TruthTableOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getLookupTableAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Comb4(attr, "lookupTable", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult TruthTableOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.lookupTable)))
    return ::mlir::failure();
  return ::mlir::success();
}

void TruthTableOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.lookupTable);
}

::llvm::ArrayRef<bool> TruthTableOp::getLookupTable() {
  auto attr = getLookupTableAttr();
  return attr;
}

void TruthTableOp::setLookupTable(::llvm::ArrayRef<bool> attrValue) {
  getProperties().lookupTable = ::mlir::Builder((*this)->getContext()).getDenseBoolArrayAttr(attrValue);
}

void TruthTableOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::ValueRange inputs, ::mlir::DenseBoolArrayAttr lookupTable) {
  odsState.addOperands(inputs);
  odsState.getOrAddProperties<Properties>().lookupTable = lookupTable;
  odsState.addTypes(result);
}

TruthTableOp TruthTableOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::ValueRange inputs, ::mlir::DenseBoolArrayAttr lookupTable) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(result)>(result), std::forward<decltype(inputs)>(inputs), std::forward<decltype(lookupTable)>(lookupTable));
  auto __res__ = ::llvm::dyn_cast<TruthTableOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

TruthTableOp TruthTableOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::ValueRange inputs, ::mlir::DenseBoolArrayAttr lookupTable) {
  return create(builder, builder.getLoc(), std::forward<decltype(result)>(result), std::forward<decltype(inputs)>(inputs), std::forward<decltype(lookupTable)>(lookupTable));
}

void TruthTableOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange inputs, ::mlir::DenseBoolArrayAttr lookupTable) {
  odsState.addOperands(inputs);
  odsState.getOrAddProperties<Properties>().lookupTable = lookupTable;

        ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
        if (::mlir::succeeded(TruthTableOp::inferReturnTypes(odsBuilder.getContext(),
                      odsState.location, odsState.operands,
                      odsState.attributes.getDictionary(odsState.getContext()),
                      odsState.getRawProperties(),
                      odsState.regions, inferredReturnTypes)))
          odsState.addTypes(inferredReturnTypes);
        else
          ::mlir::detail::reportFatalInferReturnTypesError(odsState);
        
}

TruthTableOp TruthTableOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange inputs, ::mlir::DenseBoolArrayAttr lookupTable) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(inputs)>(inputs), std::forward<decltype(lookupTable)>(lookupTable));
  auto __res__ = ::llvm::dyn_cast<TruthTableOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

TruthTableOp TruthTableOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange inputs, ::mlir::DenseBoolArrayAttr lookupTable) {
  return create(builder, builder.getLoc(), std::forward<decltype(inputs)>(inputs), std::forward<decltype(lookupTable)>(lookupTable));
}

void TruthTableOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange inputs, ::mlir::DenseBoolArrayAttr lookupTable) {
  odsState.addOperands(inputs);
  odsState.getOrAddProperties<Properties>().lookupTable = lookupTable;
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

TruthTableOp TruthTableOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange inputs, ::mlir::DenseBoolArrayAttr lookupTable) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(inputs)>(inputs), std::forward<decltype(lookupTable)>(lookupTable));
  auto __res__ = ::llvm::dyn_cast<TruthTableOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

TruthTableOp TruthTableOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange inputs, ::mlir::DenseBoolArrayAttr lookupTable) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(inputs)>(inputs), std::forward<decltype(lookupTable)>(lookupTable));
}

void TruthTableOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::ValueRange inputs, ::llvm::ArrayRef<bool> lookupTable) {
  odsState.addOperands(inputs);
  odsState.getOrAddProperties<Properties>().lookupTable = odsBuilder.getDenseBoolArrayAttr(lookupTable);
  odsState.addTypes(result);
}

TruthTableOp TruthTableOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::ValueRange inputs, ::llvm::ArrayRef<bool> lookupTable) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(result)>(result), std::forward<decltype(inputs)>(inputs), std::forward<decltype(lookupTable)>(lookupTable));
  auto __res__ = ::llvm::dyn_cast<TruthTableOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

TruthTableOp TruthTableOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::ValueRange inputs, ::llvm::ArrayRef<bool> lookupTable) {
  return create(builder, builder.getLoc(), std::forward<decltype(result)>(result), std::forward<decltype(inputs)>(inputs), std::forward<decltype(lookupTable)>(lookupTable));
}

void TruthTableOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange inputs, ::llvm::ArrayRef<bool> lookupTable) {
  odsState.addOperands(inputs);
  odsState.getOrAddProperties<Properties>().lookupTable = odsBuilder.getDenseBoolArrayAttr(lookupTable);

        ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
        if (::mlir::succeeded(TruthTableOp::inferReturnTypes(odsBuilder.getContext(),
                      odsState.location, odsState.operands,
                      odsState.attributes.getDictionary(odsState.getContext()),
                      odsState.getRawProperties(),
                      odsState.regions, inferredReturnTypes)))
          odsState.addTypes(inferredReturnTypes);
        else
          ::mlir::detail::reportFatalInferReturnTypesError(odsState);
        
}

TruthTableOp TruthTableOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange inputs, ::llvm::ArrayRef<bool> lookupTable) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(inputs)>(inputs), std::forward<decltype(lookupTable)>(lookupTable));
  auto __res__ = ::llvm::dyn_cast<TruthTableOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

TruthTableOp TruthTableOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange inputs, ::llvm::ArrayRef<bool> lookupTable) {
  return create(builder, builder.getLoc(), std::forward<decltype(inputs)>(inputs), std::forward<decltype(lookupTable)>(lookupTable));
}

void TruthTableOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange inputs, ::llvm::ArrayRef<bool> lookupTable) {
  odsState.addOperands(inputs);
  odsState.getOrAddProperties<Properties>().lookupTable = odsBuilder.getDenseBoolArrayAttr(lookupTable);
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

TruthTableOp TruthTableOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange inputs, ::llvm::ArrayRef<bool> lookupTable) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(inputs)>(inputs), std::forward<decltype(lookupTable)>(lookupTable));
  auto __res__ = ::llvm::dyn_cast<TruthTableOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

TruthTableOp TruthTableOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange inputs, ::llvm::ArrayRef<bool> lookupTable) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(inputs)>(inputs), std::forward<decltype(lookupTable)>(lookupTable));
}

void TruthTableOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<TruthTableOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

TruthTableOp TruthTableOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<TruthTableOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

TruthTableOp TruthTableOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void TruthTableOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<TruthTableOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
  ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
  if (::mlir::succeeded(TruthTableOp::inferReturnTypes(odsBuilder.getContext(),
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

TruthTableOp TruthTableOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<TruthTableOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

TruthTableOp TruthTableOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void TruthTableOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

TruthTableOp TruthTableOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<TruthTableOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

TruthTableOp TruthTableOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

void TruthTableOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties &>(properties));
  odsState.addAttributes(discardableAttributes);

  ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
  if (::mlir::succeeded(TruthTableOp::inferReturnTypes(odsBuilder.getContext(),
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

TruthTableOp TruthTableOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<TruthTableOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

TruthTableOp TruthTableOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult TruthTableOp::verifyInvariantsImpl() {
  auto tblgen_lookupTable = getProperties().lookupTable; (void)tblgen_lookupTable;
  if (!tblgen_lookupTable) return emitOpError("requires attribute 'lookupTable'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Comb4(*this, tblgen_lookupTable, "lookupTable")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Comb5(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Comb3(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult TruthTableOp::verifyInvariants() {
  if(::mlir::succeeded(verifyInvariantsImpl()) && ::mlir::succeeded(verify()))
    return ::mlir::success();
  return ::mlir::failure();
}

::llvm::LogicalResult TruthTableOp::inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::PropertyRef properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes) {
  inferredReturnTypes.resize(1);
  ::mlir::Builder odsBuilder(context);
  ::mlir::Type odsInferredType0 = odsBuilder.getIntegerType(1);
  inferredReturnTypes[0] = odsInferredType0;
  return ::mlir::success();
}

::mlir::ParseResult TruthTableOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::llvm::SmallVector<::mlir::OpAsmParser::UnresolvedOperand, 4> inputsOperands;
  ::llvm::SMLoc inputsOperandsLoc;
  (void)inputsOperandsLoc;
  ::mlir::DenseBoolArrayAttr lookupTableAttr;

  inputsOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperandList(inputsOperands))
    return ::mlir::failure();
  if (parser.parseArrow())
    return ::mlir::failure();

  if (parser.parseCustomAttributeWithFallback(lookupTableAttr, ::mlir::Type{})) {
    return ::mlir::failure();
  }
  if (lookupTableAttr) result.getOrAddProperties<TruthTableOp::Properties>().lookupTable = lookupTableAttr;
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
  if (parser.resolveOperands(inputsOperands, odsBuildableType0, inputsOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void TruthTableOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter << getInputs();
  _odsPrinter << ' ' << "->";
  _odsPrinter << ' ';
_odsPrinter.printStrippedAttrOrType(getLookupTableAttr());
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("lookupTable");
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
}

void TruthTableOp::getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects) {
}


} // namespace circt::comb
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::comb::TruthTableOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::comb::detail::TruthTableOpGenericAdaptorBase::Properties)

namespace circt::comb {


//===----------------------------------------------------------------------===//
// ::circt::comb::XorOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

XorOpGenericAdaptorBase::XorOpGenericAdaptorBase(XorOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

std::pair<unsigned, unsigned> XorOpGenericAdaptorBase::getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
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

::mlir::UnitAttr XorOpGenericAdaptorBase::getTwoStateAttr() {
  auto attr = ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(getProperties().twoState);
  if (!attr)
    attr = ((false) ? ::mlir::Builder(odsAttrs.getContext()).getUnitAttr() : nullptr);
  return attr;
}

bool XorOpGenericAdaptorBase::getTwoState() {
  auto attr = getTwoStateAttr();
    if (!attr)
      return ((false) ? ::mlir::Builder(odsAttrs.getContext()).getUnitAttr() : nullptr) != nullptr;
  return attr != nullptr;
}


} // namespace detail
XorOpAdaptor::XorOpAdaptor(XorOp op) : XorOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult XorOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_twoState = getProperties().twoState; (void)tblgen_twoState;

  if (tblgen_twoState && !((::llvm::isa<::mlir::UnitAttr>(tblgen_twoState))))
    return emitError(loc, "'comb.xor' op attribute 'twoState' failed to satisfy constraint: unit attribute");
  return ::mlir::success();
}

std::pair<unsigned, unsigned> XorOp::getODSOperandIndexAndLength(unsigned index) {
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

::mlir::MutableOperandRange XorOp::getInputsMutable() {
  auto range = getODSOperandIndexAndLength(0);
  auto mutableRange = ::mlir::MutableOperandRange(getOperation(), range.first, range.second);
  return mutableRange;
}

::llvm::LogicalResult XorOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.twoState;
       auto attr = dict.get("twoState");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `twoState` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  return ::mlir::success();
}

::mlir::Attribute XorOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.twoState;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("twoState",
                                       propStorage));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code XorOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.twoState.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> XorOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "twoState")
      return prop.twoState;
  return std::nullopt;
}

void XorOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "twoState") {
       prop.twoState = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.twoState)>>(value);
       return;
    }
}

void XorOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.twoState) attrs.append("twoState", prop.twoState);
}

::llvm::LogicalResult XorOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getTwoStateAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Comb1(attr, "twoState", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult XorOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readOptionalAttribute(prop.twoState)))
    return ::mlir::failure();
  return ::mlir::success();
}

void XorOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;

  writer.writeOptionalAttribute(prop.twoState);
}

bool XorOp::getTwoState() {
  auto attr = getTwoStateAttr();
    if (!attr)
      return ((false) ? ::mlir::Builder((*this)->getContext()).getUnitAttr() : nullptr) != nullptr;
  return attr != nullptr;
}

void XorOp::setTwoState(bool attrValue) {
    auto &odsProp = getProperties().twoState;
    if (attrValue)
      odsProp = ((attrValue) ? ::mlir::Builder((*this)->getContext()).getUnitAttr() : nullptr);
    else
      odsProp = nullptr;
}

void XorOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value lhs, Value rhs, bool twoState) {
      return build(odsBuilder, odsState, lhs.getType(),
                   ValueRange{lhs, rhs}, twoState);
    
}

XorOp XorOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, Value lhs, Value rhs, bool twoState) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(lhs)>(lhs), std::forward<decltype(rhs)>(rhs), std::forward<decltype(twoState)>(twoState));
  auto __res__ = ::llvm::dyn_cast<XorOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

XorOp XorOp::create(::mlir::ImplicitLocOpBuilder &builder, Value lhs, Value rhs, bool twoState) {
  return create(builder, builder.getLoc(), std::forward<decltype(lhs)>(lhs), std::forward<decltype(rhs)>(rhs), std::forward<decltype(twoState)>(twoState));
}

void XorOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::ValueRange inputs, /*optional*/::mlir::UnitAttr twoState) {
  odsState.addOperands(inputs);
  if (twoState) {
    odsState.getOrAddProperties<Properties>().twoState = twoState;
  }
  odsState.addTypes(result);
}

XorOp XorOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::ValueRange inputs, /*optional*/::mlir::UnitAttr twoState) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(result)>(result), std::forward<decltype(inputs)>(inputs), std::forward<decltype(twoState)>(twoState));
  auto __res__ = ::llvm::dyn_cast<XorOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

XorOp XorOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::ValueRange inputs, /*optional*/::mlir::UnitAttr twoState) {
  return create(builder, builder.getLoc(), std::forward<decltype(result)>(result), std::forward<decltype(inputs)>(inputs), std::forward<decltype(twoState)>(twoState));
}

void XorOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange inputs, /*optional*/::mlir::UnitAttr twoState) {
  odsState.addOperands(inputs);
  if (twoState) {
    odsState.getOrAddProperties<Properties>().twoState = twoState;
  }
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

XorOp XorOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange inputs, /*optional*/::mlir::UnitAttr twoState) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(inputs)>(inputs), std::forward<decltype(twoState)>(twoState));
  auto __res__ = ::llvm::dyn_cast<XorOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

XorOp XorOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange inputs, /*optional*/::mlir::UnitAttr twoState) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(inputs)>(inputs), std::forward<decltype(twoState)>(twoState));
}

void XorOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::ValueRange inputs, /*optional*/bool twoState) {
  odsState.addOperands(inputs);
  if (twoState) {
    odsState.getOrAddProperties<Properties>().twoState = ((twoState) ? odsBuilder.getUnitAttr() : nullptr);
  }
  odsState.addTypes(result);
}

XorOp XorOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::ValueRange inputs, /*optional*/bool twoState) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(result)>(result), std::forward<decltype(inputs)>(inputs), std::forward<decltype(twoState)>(twoState));
  auto __res__ = ::llvm::dyn_cast<XorOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

XorOp XorOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::ValueRange inputs, /*optional*/bool twoState) {
  return create(builder, builder.getLoc(), std::forward<decltype(result)>(result), std::forward<decltype(inputs)>(inputs), std::forward<decltype(twoState)>(twoState));
}

void XorOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange inputs, /*optional*/bool twoState) {
  odsState.addOperands(inputs);
  if (twoState) {
    odsState.getOrAddProperties<Properties>().twoState = ((twoState) ? odsBuilder.getUnitAttr() : nullptr);
  }
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

XorOp XorOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange inputs, /*optional*/bool twoState) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(inputs)>(inputs), std::forward<decltype(twoState)>(twoState));
  auto __res__ = ::llvm::dyn_cast<XorOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

XorOp XorOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange inputs, /*optional*/bool twoState) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(inputs)>(inputs), std::forward<decltype(twoState)>(twoState));
}

void XorOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<XorOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

XorOp XorOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<XorOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

XorOp XorOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void XorOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

XorOp XorOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<XorOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

XorOp XorOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

void XorOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange inputs, /*optional*/::mlir::UnitAttr twoState) {
  odsState.addOperands(inputs);
  if (twoState) {
    odsState.getOrAddProperties<Properties>().twoState = twoState;
  }
  odsState.addTypes({inputs.front().getType()});

}

XorOp XorOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange inputs, /*optional*/::mlir::UnitAttr twoState) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(inputs)>(inputs), std::forward<decltype(twoState)>(twoState));
  auto __res__ = ::llvm::dyn_cast<XorOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

XorOp XorOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange inputs, /*optional*/::mlir::UnitAttr twoState) {
  return create(builder, builder.getLoc(), std::forward<decltype(inputs)>(inputs), std::forward<decltype(twoState)>(twoState));
}

void XorOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange inputs, /*optional*/bool twoState) {
  odsState.addOperands(inputs);
  if (twoState) {
    odsState.getOrAddProperties<Properties>().twoState = ((twoState) ? odsBuilder.getUnitAttr() : nullptr);
  }
  odsState.addTypes({inputs.front().getType()});

}

XorOp XorOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange inputs, /*optional*/bool twoState) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(inputs)>(inputs), std::forward<decltype(twoState)>(twoState));
  auto __res__ = ::llvm::dyn_cast<XorOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

XorOp XorOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange inputs, /*optional*/bool twoState) {
  return create(builder, builder.getLoc(), std::forward<decltype(inputs)>(inputs), std::forward<decltype(twoState)>(twoState));
}

void XorOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  odsState.addTypes({operands[0].getType()});

}

XorOp XorOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<XorOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

XorOp XorOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void XorOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  odsState.addTypes({operands[0].getType()});

}

XorOp XorOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<XorOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

XorOp XorOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult XorOp::verifyInvariantsImpl() {
  auto tblgen_twoState = getProperties().twoState; (void)tblgen_twoState;

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Comb1(*this, tblgen_twoState, "twoState")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Comb1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Comb2(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult XorOp::verifyInvariants() {
  if(::mlir::succeeded(verifyInvariantsImpl()) && ::mlir::succeeded(verify()))
    return ::mlir::success();
  return ::mlir::failure();
}

void XorOp::getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context) {
  results.add(canonicalize);
}

::mlir::ParseResult XorOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::llvm::SmallVector<::mlir::OpAsmParser::UnresolvedOperand, 4> inputsOperands;
  ::llvm::SMLoc inputsOperandsLoc;
  (void)inputsOperandsLoc;
  ::mlir::Type resultRawType{};
  ::llvm::ArrayRef<::mlir::Type> resultTypes(&resultRawType, 1);
  if (::mlir::succeeded(parser.parseOptionalKeyword("bin"))) {
    result.getOrAddProperties<XorOp::Properties>().twoState = parser.getBuilder().getUnitAttr();  }

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

  if (parser.parseType(resultRawType))
    return ::mlir::failure();
  result.addTypes(resultTypes);
  if (parser.resolveOperands(inputsOperands, resultTypes[0], inputsOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void XorOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  if ((getTwoStateAttr() && getTwoStateAttr() != ((false) ? ::mlir::OpBuilder((*this)->getContext()).getUnitAttr() : nullptr))) {
    _odsPrinter << ' ' << "bin";
  }
  _odsPrinter << ' ';
  _odsPrinter << getInputs();
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("twoState");
  {
     ::mlir::Builder odsBuilder(getContext());
     ::mlir::Attribute attr = getTwoStateAttr();
     if(attr && (attr == ((false) ? odsBuilder.getUnitAttr() : nullptr)))
       elidedAttrs.push_back("twoState");
  }
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
   _odsPrinter << getResult().getType();
}

void XorOp::getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects) {
}


} // namespace circt::comb
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::comb::XorOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::comb::detail::XorOpGenericAdaptorBase::Properties)


#endif // GET_OP_CLASSES

