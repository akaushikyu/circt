/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Op Definitions                                                             *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: Kanagawa.td                                                          *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

#ifdef GET_OP_LIST
#undef GET_OP_LIST

::circt::kanagawa::BlockReturnOp,
::circt::kanagawa::CallOp,
::circt::kanagawa::ClassOp,
::circt::kanagawa::ContainerInstanceOp,
::circt::kanagawa::ContainerOp,
::circt::kanagawa::DCBlockOp,
::circt::kanagawa::DataflowMethodOp,
::circt::kanagawa::DesignOp,
::circt::kanagawa::GetPortOp,
::circt::kanagawa::GetVarOp,
::circt::kanagawa::InlineStaticBlockBeginOp,
::circt::kanagawa::InlineStaticBlockEndOp,
::circt::kanagawa::InputPortOp,
::circt::kanagawa::InputWireOp,
::circt::kanagawa::InstanceOp,
::circt::kanagawa::IsolatedStaticBlockOp,
::circt::kanagawa::MethodOp,
::circt::kanagawa::OutputPortOp,
::circt::kanagawa::OutputWireOp,
::circt::kanagawa::PathOp,
::circt::kanagawa::PipelineHeaderOp,
::circt::kanagawa::PortReadOp,
::circt::kanagawa::PortWriteOp,
::circt::kanagawa::ReturnOp,
::circt::kanagawa::StaticBlockOp,
::circt::kanagawa::VarOp
#endif // GET_OP_LIST

#ifdef GET_OP_CLASSES
#undef GET_OP_CLASSES


//===----------------------------------------------------------------------===//
// Local Utility Method Definitions
//===----------------------------------------------------------------------===//


static ::llvm::LogicalResult __mlir_ods_local_type_constraint_Kanagawa1(
    ::mlir::Operation *op, ::mlir::Type type, ::llvm::StringRef valueKind,
    unsigned valueIndex) {
  if (!(!((::llvm::isa<::mlir::TokenType>(type))))) {
    return op->emitOpError(valueKind) << " #" << valueIndex
        << " must be variadic of any non-token type, but got " << type;
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_type_constraint_Kanagawa2(
    ::mlir::Operation *op, ::mlir::Type type, ::llvm::StringRef valueKind,
    unsigned valueIndex) {
  if (!((::llvm::isa<::circt::kanagawa::ScopeRefType>(type)))) {
    return op->emitOpError(valueKind) << " #" << valueIndex
        << " must be , but got " << type;
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_type_constraint_Kanagawa3(
    ::mlir::Operation *op, ::mlir::Type type, ::llvm::StringRef valueKind,
    unsigned valueIndex) {
  if (!((::llvm::isa<::circt::kanagawa::PortRefType>(type)))) {
    return op->emitOpError(valueKind) << " #" << valueIndex
        << " must be , but got " << type;
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_type_constraint_Kanagawa4(
    ::mlir::Operation *op, ::mlir::Type type, ::llvm::StringRef valueKind,
    unsigned valueIndex) {
  if (!(((::llvm::isa<::mlir::MemRefType>(type))) && ([](::mlir::Type elementType) { return !((::llvm::isa<::mlir::TokenType>(elementType))); }(::llvm::cast<::mlir::ShapedType>(type).getElementType())))) {
    return op->emitOpError(valueKind) << " #" << valueIndex
        << " must be memref of any non-token type values, but got " << type;
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_type_constraint_Kanagawa5(
    ::mlir::Operation *op, ::mlir::Type type, ::llvm::StringRef valueKind,
    unsigned valueIndex) {
  if (!(!((::llvm::isa<::mlir::TokenType>(type))))) {
    return op->emitOpError(valueKind) << " #" << valueIndex
        << " must be any non-token type, but got " << type;
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_type_constraint_Kanagawa6(
    ::mlir::Operation *op, ::mlir::Type type, ::llvm::StringRef valueKind,
    unsigned valueIndex) {
  if (!((::llvm::isa<::circt::seq::ClockType>(type)))) {
    return op->emitOpError(valueKind) << " #" << valueIndex
        << " must be A type for clock-carrying wires, but got " << type;
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_type_constraint_Kanagawa7(
    ::mlir::Operation *op, ::mlir::Type type, ::llvm::StringRef valueKind,
    unsigned valueIndex) {
  if (!((type.isSignlessInteger(1)))) {
    return op->emitOpError(valueKind) << " #" << valueIndex
        << " must be 1-bit signless integer, but got " << type;
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_Kanagawa1(
    ::mlir::Attribute attr, ::llvm::StringRef attrName, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  if (attr && !((::llvm::isa<::circt::hw::InnerRefAttr>(attr))))
    return emitError() << "attribute '" << attrName
        << "' failed to satisfy constraint: Refer to a name inside a module";
  return ::mlir::success();
}
static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_Kanagawa1(
    ::mlir::Operation *op, ::mlir::Attribute attr, ::llvm::StringRef attrName) {
  return __mlir_ods_local_attr_constraint_Kanagawa1(attr, attrName, [op]() {
    return op->emitOpError();
  });
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_Kanagawa2(
    ::mlir::Attribute attr, ::llvm::StringRef attrName, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  if (attr && !((::llvm::isa<::circt::hw::InnerSymAttr>(attr))))
    return emitError() << "attribute '" << attrName
        << "' failed to satisfy constraint: Inner symbol definition";
  return ::mlir::success();
}
static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_Kanagawa2(
    ::mlir::Operation *op, ::mlir::Attribute attr, ::llvm::StringRef attrName) {
  return __mlir_ods_local_attr_constraint_Kanagawa2(attr, attrName, [op]() {
    return op->emitOpError();
  });
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_Kanagawa3(
    ::mlir::Attribute attr, ::llvm::StringRef attrName, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  if (attr && !((::llvm::isa<::mlir::StringAttr>(attr))))
    return emitError() << "attribute '" << attrName
        << "' failed to satisfy constraint: string attribute";
  return ::mlir::success();
}
static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_Kanagawa3(
    ::mlir::Operation *op, ::mlir::Attribute attr, ::llvm::StringRef attrName) {
  return __mlir_ods_local_attr_constraint_Kanagawa3(attr, attrName, [op]() {
    return op->emitOpError();
  });
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_Kanagawa4(
    ::mlir::Attribute attr, ::llvm::StringRef attrName, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  if (attr && !((::llvm::isa<::mlir::UnitAttr>(attr))))
    return emitError() << "attribute '" << attrName
        << "' failed to satisfy constraint: unit attribute";
  return ::mlir::success();
}
static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_Kanagawa4(
    ::mlir::Operation *op, ::mlir::Attribute attr, ::llvm::StringRef attrName) {
  return __mlir_ods_local_attr_constraint_Kanagawa4(attr, attrName, [op]() {
    return op->emitOpError();
  });
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_Kanagawa5(
    ::mlir::Attribute attr, ::llvm::StringRef attrName, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  if (attr && !((((::llvm::isa<::mlir::IntegerAttr>(attr))) && ((::llvm::cast<::mlir::IntegerAttr>(attr).getType().isSignlessInteger(64)))) && ((::llvm::cast<::mlir::IntegerAttr>(attr).getInt() >= 1))))
    return emitError() << "attribute '" << attrName
        << "' failed to satisfy constraint: 64-bit signless integer attribute whose minimum value is 1";
  return ::mlir::success();
}
static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_Kanagawa5(
    ::mlir::Operation *op, ::mlir::Attribute attr, ::llvm::StringRef attrName) {
  return __mlir_ods_local_attr_constraint_Kanagawa5(attr, attrName, [op]() {
    return op->emitOpError();
  });
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_Kanagawa6(
    ::mlir::Attribute attr, ::llvm::StringRef attrName, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  if (attr && !(((::llvm::isa<::mlir::TypeAttr>(attr))) && ((::llvm::isa<::mlir::FunctionType>(::llvm::cast<::mlir::TypeAttr>(attr).getValue()))) && ((::llvm::isa<::mlir::FunctionType>(::llvm::cast<::mlir::TypeAttr>(attr).getValue())))))
    return emitError() << "attribute '" << attrName
        << "' failed to satisfy constraint: type attribute of function type";
  return ::mlir::success();
}
static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_Kanagawa6(
    ::mlir::Operation *op, ::mlir::Attribute attr, ::llvm::StringRef attrName) {
  return __mlir_ods_local_attr_constraint_Kanagawa6(attr, attrName, [op]() {
    return op->emitOpError();
  });
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_Kanagawa7(
    ::mlir::Attribute attr, ::llvm::StringRef attrName, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  if (attr && !((::llvm::isa<::mlir::ArrayAttr>(attr))))
    return emitError() << "attribute '" << attrName
        << "' failed to satisfy constraint: array attribute";
  return ::mlir::success();
}
static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_Kanagawa7(
    ::mlir::Operation *op, ::mlir::Attribute attr, ::llvm::StringRef attrName) {
  return __mlir_ods_local_attr_constraint_Kanagawa7(attr, attrName, [op]() {
    return op->emitOpError();
  });
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_Kanagawa8(
    ::mlir::Attribute attr, ::llvm::StringRef attrName, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  if (attr && !(((::llvm::isa<::mlir::ArrayAttr>(attr))) && (::llvm::all_of(::llvm::cast<::mlir::ArrayAttr>(attr), [&](::mlir::Attribute attr) { return attr && ((::llvm::isa<::mlir::DictionaryAttr>(attr))); }))))
    return emitError() << "attribute '" << attrName
        << "' failed to satisfy constraint: Array of dictionary attributes";
  return ::mlir::success();
}
static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_Kanagawa8(
    ::mlir::Operation *op, ::mlir::Attribute attr, ::llvm::StringRef attrName) {
  return __mlir_ods_local_attr_constraint_Kanagawa8(attr, attrName, [op]() {
    return op->emitOpError();
  });
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_Kanagawa9(
    ::mlir::Attribute attr, ::llvm::StringRef attrName, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  if (attr && !((::llvm::isa<::mlir::FlatSymbolRefAttr>(attr))))
    return emitError() << "attribute '" << attrName
        << "' failed to satisfy constraint: flat symbol reference attribute";
  return ::mlir::success();
}
static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_Kanagawa9(
    ::mlir::Operation *op, ::mlir::Attribute attr, ::llvm::StringRef attrName) {
  return __mlir_ods_local_attr_constraint_Kanagawa9(attr, attrName, [op]() {
    return op->emitOpError();
  });
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_Kanagawa10(
    ::mlir::Attribute attr, ::llvm::StringRef attrName, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  if (attr && !(((::llvm::isa<::mlir::TypeAttr>(attr))) && ((::llvm::isa<::mlir::Type>(::llvm::cast<::mlir::TypeAttr>(attr).getValue()))) && (!((::llvm::isa<::mlir::TokenType>(::llvm::cast<::mlir::TypeAttr>(attr).getValue()))))))
    return emitError() << "attribute '" << attrName
        << "' failed to satisfy constraint: type attribute of any non-token type";
  return ::mlir::success();
}
static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_Kanagawa10(
    ::mlir::Operation *op, ::mlir::Attribute attr, ::llvm::StringRef attrName) {
  return __mlir_ods_local_attr_constraint_Kanagawa10(attr, attrName, [op]() {
    return op->emitOpError();
  });
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_Kanagawa11(
    ::mlir::Attribute attr, ::llvm::StringRef attrName, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  if (attr && !(((::llvm::isa<::mlir::ArrayAttr>(attr))) && (::llvm::all_of(::llvm::cast<::mlir::ArrayAttr>(attr), [&](::mlir::Attribute attr) { return attr && ((::llvm::isa<::circt::kanagawa::PathStepAttr>(attr))); }))))
    return emitError() << "attribute '" << attrName
        << "' failed to satisfy constraint: Path step array attribute";
  return ::mlir::success();
}
static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_Kanagawa11(
    ::mlir::Operation *op, ::mlir::Attribute attr, ::llvm::StringRef attrName) {
  return __mlir_ods_local_attr_constraint_Kanagawa11(attr, attrName, [op]() {
    return op->emitOpError();
  });
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_Kanagawa12(
    ::mlir::Attribute attr, ::llvm::StringRef attrName, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  if (attr && !(((::llvm::isa<::mlir::TypeAttr>(attr))) && ((::llvm::isa<MemRefType>(::llvm::cast<::mlir::TypeAttr>(attr).getValue()))) && ((true))))
    return emitError() << "attribute '" << attrName
        << "' failed to satisfy constraint: any memref type";
  return ::mlir::success();
}
static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_Kanagawa12(
    ::mlir::Operation *op, ::mlir::Attribute attr, ::llvm::StringRef attrName) {
  return __mlir_ods_local_attr_constraint_Kanagawa12(attr, attrName, [op]() {
    return op->emitOpError();
  });
}

static ::llvm::LogicalResult __mlir_ods_local_region_constraint_Kanagawa1(
    ::mlir::Operation *op, ::mlir::Region &region, ::llvm::StringRef regionName,
    unsigned regionIndex) {
  if (!((::llvm::hasNItems(region, 1)))) {
    return op->emitOpError("region #") << regionIndex
        << (regionName.empty() ? " " : " ('" + regionName + "') ")
        << "failed to verify constraint: region with 1 blocks";
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_region_constraint_Kanagawa2(
    ::mlir::Operation *op, ::mlir::Region &region, ::llvm::StringRef regionName,
    unsigned regionIndex) {
  if (!((true))) {
    return op->emitOpError("region #") << regionIndex
        << (regionName.empty() ? " " : " ('" + regionName + "') ")
        << "failed to verify constraint: any region";
  }
  return ::mlir::success();
}
namespace circt::kanagawa {


//===----------------------------------------------------------------------===//
// ::circt::kanagawa::BlockReturnOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

BlockReturnOpGenericAdaptorBase::BlockReturnOpGenericAdaptorBase(BlockReturnOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

std::pair<unsigned, unsigned> BlockReturnOpGenericAdaptorBase::getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
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
BlockReturnOpAdaptor::BlockReturnOpAdaptor(BlockReturnOp op) : BlockReturnOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult BlockReturnOpAdaptor::verify(::mlir::Location loc) {
  return ::mlir::success();
}

std::pair<unsigned, unsigned> BlockReturnOp::getODSOperandIndexAndLength(unsigned index) {
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

::mlir::MutableOperandRange BlockReturnOp::getRetValuesMutable() {
  auto range = getODSOperandIndexAndLength(0);
  auto mutableRange = ::mlir::MutableOperandRange(getOperation(), range.first, range.second);
  return mutableRange;
}

::llvm::LogicalResult BlockReturnOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }
      return ::mlir::success();
}

::mlir::Attribute BlockReturnOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code BlockReturnOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine();
}

std::optional<mlir::Attribute> BlockReturnOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
  return std::nullopt;
}

void BlockReturnOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
}

void BlockReturnOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
}

::llvm::LogicalResult BlockReturnOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    return ::mlir::success();
}

void BlockReturnOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState) {
/*no-op*/
}

BlockReturnOp BlockReturnOp::create(::mlir::OpBuilder &builder, ::mlir::Location location) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__);
  auto __res__ = ::llvm::dyn_cast<BlockReturnOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

BlockReturnOp BlockReturnOp::create(::mlir::ImplicitLocOpBuilder &builder) {
  return create(builder, builder.getLoc());
}

void BlockReturnOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange retValues) {
  odsState.addOperands(retValues);
}

BlockReturnOp BlockReturnOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange retValues) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(retValues)>(retValues));
  auto __res__ = ::llvm::dyn_cast<BlockReturnOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

BlockReturnOp BlockReturnOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange retValues) {
  return create(builder, builder.getLoc(), std::forward<decltype(retValues)>(retValues));
}

void BlockReturnOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

BlockReturnOp BlockReturnOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<BlockReturnOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

BlockReturnOp BlockReturnOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void BlockReturnOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

BlockReturnOp BlockReturnOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<BlockReturnOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

BlockReturnOp BlockReturnOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult BlockReturnOp::verifyInvariantsImpl() {
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Kanagawa1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult BlockReturnOp::verifyInvariants() {
  if(::mlir::succeeded(verifyInvariantsImpl()) && ::mlir::succeeded(verify()))
    return ::mlir::success();
  return ::mlir::failure();
}

::mlir::ParseResult BlockReturnOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::llvm::SmallVector<::mlir::OpAsmParser::UnresolvedOperand, 4> retValuesOperands;
  ::llvm::SMLoc retValuesOperandsLoc;
  (void)retValuesOperandsLoc;
  ::llvm::SmallVector<::mlir::Type, 1> retValuesTypes;

  retValuesOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperandList(retValuesOperands))
    return ::mlir::failure();
  if (!retValuesOperands.empty()) {
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

  if (parser.parseTypeList(retValuesTypes))
    return ::mlir::failure();
  }
  if (parser.resolveOperands(retValuesOperands, retValuesTypes, retValuesOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void BlockReturnOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  if (!getRetValues().empty()) {
    _odsPrinter << ' ';
    _odsPrinter << getRetValues();
  }
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  if (!getRetValues().empty()) {
    _odsPrinter << ' ' << ":";
    _odsPrinter << ' ';
    _odsPrinter << getRetValues().getTypes();
  }
}

void BlockReturnOp::getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects) {
}


} // namespace circt::kanagawa
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::kanagawa::BlockReturnOp)

namespace circt::kanagawa {


//===----------------------------------------------------------------------===//
// ::circt::kanagawa::CallOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

CallOpGenericAdaptorBase::CallOpGenericAdaptorBase(CallOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

std::pair<unsigned, unsigned> CallOpGenericAdaptorBase::getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
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

::circt::hw::InnerRefAttr CallOpGenericAdaptorBase::getCallee() {
  auto attr = getCalleeAttr();
  return ::llvm::cast<::circt::hw::InnerRefAttr>(attr);
}


} // namespace detail
CallOpAdaptor::CallOpAdaptor(CallOp op) : CallOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult CallOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_callee = getProperties().callee; (void)tblgen_callee;
  if (!tblgen_callee) return emitError(loc, "'kanagawa.call' op requires attribute 'callee'");

  if (tblgen_callee && !((::llvm::isa<::circt::hw::InnerRefAttr>(tblgen_callee))))
    return emitError(loc, "'kanagawa.call' op attribute 'callee' failed to satisfy constraint: Refer to a name inside a module");
  return ::mlir::success();
}

std::pair<unsigned, unsigned> CallOp::getODSOperandIndexAndLength(unsigned index) {
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

::mlir::MutableOperandRange CallOp::getOperandsMutable() {
  auto range = getODSOperandIndexAndLength(0);
  auto mutableRange = ::mlir::MutableOperandRange(getOperation(), range.first, range.second);
  return mutableRange;
}

std::pair<unsigned, unsigned> CallOp::getODSResultIndexAndLength(unsigned index) {
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

::llvm::LogicalResult CallOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.callee;
       auto attr = dict.get("callee");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `callee` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  return ::mlir::success();
}

::mlir::Attribute CallOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.callee;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("callee",
                                       propStorage));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code CallOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.callee.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> CallOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "callee")
      return prop.callee;
  return std::nullopt;
}

void CallOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "callee") {
       prop.callee = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.callee)>>(value);
       return;
    }
}

void CallOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.callee) attrs.append("callee", prop.callee);
}

::llvm::LogicalResult CallOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getCalleeAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Kanagawa1(attr, "callee", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult CallOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.callee)))
    return ::mlir::failure();
  return ::mlir::success();
}

void CallOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.callee);
}

::circt::hw::InnerRefAttr CallOp::getCallee() {
  auto attr = getCalleeAttr();
  return ::llvm::cast<::circt::hw::InnerRefAttr>(attr);
}

void CallOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultType0, ::circt::hw::InnerRefAttr callee, ::mlir::ValueRange operands) {
  odsState.addOperands(operands);
  odsState.getOrAddProperties<Properties>().callee = callee;
  odsState.addTypes(resultType0);
}

CallOp CallOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultType0, ::circt::hw::InnerRefAttr callee, ::mlir::ValueRange operands) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultType0)>(resultType0), std::forward<decltype(callee)>(callee), std::forward<decltype(operands)>(operands));
  auto __res__ = ::llvm::dyn_cast<CallOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

CallOp CallOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultType0, ::circt::hw::InnerRefAttr callee, ::mlir::ValueRange operands) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultType0)>(resultType0), std::forward<decltype(callee)>(callee), std::forward<decltype(operands)>(operands));
}

void CallOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<CallOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

CallOp CallOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<CallOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

CallOp CallOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void CallOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  odsState.addTypes(resultTypes);
}

CallOp CallOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<CallOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

CallOp CallOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult CallOp::verifyInvariantsImpl() {
  auto tblgen_callee = getProperties().callee; (void)tblgen_callee;
  if (!tblgen_callee) return emitOpError("requires attribute 'callee'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Kanagawa1(*this, tblgen_callee, "callee")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Kanagawa1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Kanagawa1(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult CallOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult CallOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::circt::hw::InnerRefAttr calleeAttr;
  ::llvm::SmallVector<::mlir::OpAsmParser::UnresolvedOperand, 4> operandsOperands;
  ::llvm::SMLoc operandsOperandsLoc;
  (void)operandsOperandsLoc;
  ::llvm::ArrayRef<::mlir::Type> operandsTypes;
  ::llvm::ArrayRef<::mlir::Type> allResultTypes;

  if (parser.parseCustomAttributeWithFallback(calleeAttr, ::mlir::Type{})) {
    return ::mlir::failure();
  }
  if (calleeAttr) result.getOrAddProperties<CallOp::Properties>().callee = calleeAttr;
  if (parser.parseLParen())
    return ::mlir::failure();

  operandsOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperandList(operandsOperands))
    return ::mlir::failure();
  if (parser.parseRParen())
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

  ::mlir::FunctionType operands__allResult_functionType;
  if (parser.parseType(operands__allResult_functionType))
    return ::mlir::failure();
  operandsTypes = operands__allResult_functionType.getInputs();
  allResultTypes = operands__allResult_functionType.getResults();
  result.addTypes(allResultTypes);
  if (parser.resolveOperands(operandsOperands, operandsTypes, operandsOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void CallOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
_odsPrinter.printStrippedAttrOrType(getCalleeAttr());
  _odsPrinter << "(";
  _odsPrinter << getOperands();
  _odsPrinter << ")";
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("callee");
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
  _odsPrinter.printFunctionalType(getOperands().getTypes(), getOperation()->getResultTypes());
}


} // namespace circt::kanagawa
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::kanagawa::CallOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::kanagawa::detail::CallOpGenericAdaptorBase::Properties)

namespace circt::kanagawa {


//===----------------------------------------------------------------------===//
// ::circt::kanagawa::ClassOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

ClassOpGenericAdaptorBase::ClassOpGenericAdaptorBase(ClassOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::circt::hw::InnerSymAttr ClassOpGenericAdaptorBase::getInnerSym() {
  auto attr = getInnerSymAttr();
  return ::llvm::cast<::circt::hw::InnerSymAttr>(attr);
}

::std::optional< ::llvm::StringRef > ClassOpGenericAdaptorBase::getName() {
  auto attr = getNameAttr();
  return attr ? ::std::optional< ::llvm::StringRef >(attr.getValue()) : (::std::nullopt);
}


} // namespace detail
ClassOpAdaptor::ClassOpAdaptor(ClassOp op) : ClassOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult ClassOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_inner_sym = getProperties().inner_sym; (void)tblgen_inner_sym;
  if (!tblgen_inner_sym) return emitError(loc, "'kanagawa.class' op requires attribute 'inner_sym'");
  auto tblgen_name = getProperties().name; (void)tblgen_name;

  if (tblgen_inner_sym && !((::llvm::isa<::circt::hw::InnerSymAttr>(tblgen_inner_sym))))
    return emitError(loc, "'kanagawa.class' op attribute 'inner_sym' failed to satisfy constraint: Inner symbol definition");

  if (tblgen_name && !((::llvm::isa<::mlir::StringAttr>(tblgen_name))))
    return emitError(loc, "'kanagawa.class' op attribute 'name' failed to satisfy constraint: string attribute");
  return ::mlir::success();
}

::llvm::LogicalResult ClassOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.inner_sym;
       auto attr = dict.get("inner_sym");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `inner_sym` in property conversion: " << attr;
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
  return ::mlir::success();
}

::mlir::Attribute ClassOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.inner_sym;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("inner_sym",
                                       propStorage));
    }

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

llvm::hash_code ClassOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.inner_sym.getAsOpaquePointer()), 
    llvm::hash_value(prop.name.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> ClassOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "inner_sym")
      return prop.inner_sym;

    if (name == "name")
      return prop.name;
  return std::nullopt;
}

void ClassOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "inner_sym") {
       prop.inner_sym = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.inner_sym)>>(value);
       return;
    }

    if (name == "name") {
       prop.name = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.name)>>(value);
       return;
    }
}

void ClassOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.inner_sym) attrs.append("inner_sym", prop.inner_sym);

    if (prop.name) attrs.append("name", prop.name);
}

::llvm::LogicalResult ClassOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getInnerSymAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Kanagawa2(attr, "inner_sym", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getNameAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Kanagawa3(attr, "name", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult ClassOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.inner_sym)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readOptionalAttribute(prop.name)))
    return ::mlir::failure();
  return ::mlir::success();
}

void ClassOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.inner_sym);

  writer.writeOptionalAttribute(prop.name);
}

::circt::hw::InnerSymAttr ClassOp::getInnerSym() {
  auto attr = getInnerSymAttr();
  return ::llvm::cast<::circt::hw::InnerSymAttr>(attr);
}

::std::optional< ::llvm::StringRef > ClassOp::getName() {
  auto attr = getNameAttr();
  return attr ? ::std::optional< ::llvm::StringRef >(attr.getValue()) : (::std::nullopt);
}

void ClassOp::setName(::std::optional<::llvm::StringRef> attrValue) {
    auto &odsProp = getProperties().name;
    if (attrValue)
      odsProp = ::mlir::Builder((*this)->getContext()).getStringAttr(*attrValue);
    else
      odsProp = nullptr;
}

void ClassOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::circt::hw::InnerSymAttr inner_sym, /*optional*/::mlir::StringAttr name) {
  odsState.getOrAddProperties<Properties>().inner_sym = inner_sym;
  if (name) {
    odsState.getOrAddProperties<Properties>().name = name;
  }
  (void)odsState.addRegion();
}

ClassOp ClassOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::circt::hw::InnerSymAttr inner_sym, /*optional*/::mlir::StringAttr name) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(inner_sym)>(inner_sym), std::forward<decltype(name)>(name));
  auto __res__ = ::llvm::dyn_cast<ClassOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ClassOp ClassOp::create(::mlir::ImplicitLocOpBuilder &builder, ::circt::hw::InnerSymAttr inner_sym, /*optional*/::mlir::StringAttr name) {
  return create(builder, builder.getLoc(), std::forward<decltype(inner_sym)>(inner_sym), std::forward<decltype(name)>(name));
}

void ClassOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::circt::hw::InnerSymAttr inner_sym, /*optional*/::mlir::StringAttr name) {
  odsState.getOrAddProperties<Properties>().inner_sym = inner_sym;
  if (name) {
    odsState.getOrAddProperties<Properties>().name = name;
  }
  (void)odsState.addRegion();
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

ClassOp ClassOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::circt::hw::InnerSymAttr inner_sym, /*optional*/::mlir::StringAttr name) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(inner_sym)>(inner_sym), std::forward<decltype(name)>(name));
  auto __res__ = ::llvm::dyn_cast<ClassOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ClassOp ClassOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::circt::hw::InnerSymAttr inner_sym, /*optional*/::mlir::StringAttr name) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(inner_sym)>(inner_sym), std::forward<decltype(name)>(name));
}

void ClassOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  for (unsigned i = 0; i != 1; ++i)
    (void)odsState.addRegion();
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<ClassOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

ClassOp ClassOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<ClassOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ClassOp ClassOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void ClassOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  for (unsigned i = 0; i != 1; ++i)
    (void)odsState.addRegion();
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

ClassOp ClassOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<ClassOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ClassOp ClassOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult ClassOp::verifyInvariantsImpl() {
  auto tblgen_inner_sym = getProperties().inner_sym; (void)tblgen_inner_sym;
  if (!tblgen_inner_sym) return emitOpError("requires attribute 'inner_sym'");
  auto tblgen_name = getProperties().name; (void)tblgen_name;

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Kanagawa2(*this, tblgen_inner_sym, "inner_sym")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Kanagawa3(*this, tblgen_name, "name")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;

    for (auto &region : ::llvm::MutableArrayRef((*this)->getRegion(0)))
      if (::mlir::failed(__mlir_ods_local_region_constraint_Kanagawa1(*this, region, "body", index++)))
        return ::mlir::failure();
  }
  return ::mlir::success();
}

::llvm::LogicalResult ClassOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult ClassOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::StringAttr nameAttr;
  ::circt::hw::InnerSymAttr inner_symAttr;
  std::unique_ptr<::mlir::Region> bodyRegion = std::make_unique<::mlir::Region>();

  ::mlir::OptionalParseResult parseResultnameAttr =
    parser.parseOptionalAttribute(nameAttr, parser.getBuilder().getType<::mlir::NoneType>());
  if (parseResultnameAttr.has_value() && failed(*parseResultnameAttr))
    return ::mlir::failure();
  if (parseResultnameAttr.has_value() && succeeded(*parseResultnameAttr))
  if (nameAttr) result.getOrAddProperties<ClassOp::Properties>().name = nameAttr;
  if (nameAttr) {
  }
  if (parser.parseKeyword("sym"))
    return ::mlir::failure();

  if (parser.parseCustomAttributeWithFallback(inner_symAttr, ::mlir::Type{})) {
    return ::mlir::failure();
  }
  if (inner_symAttr) result.getOrAddProperties<ClassOp::Properties>().inner_sym = inner_symAttr;
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

void ClassOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  if (getNameAttr()) {
    _odsPrinter << ' ';
    _odsPrinter.printAttributeWithoutType(getNameAttr());
  }
  _odsPrinter << ' ' << "sym";
  _odsPrinter << ' ';
_odsPrinter.printStrippedAttrOrType(getInnerSymAttr());
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("name");
  elidedAttrs.push_back("inner_sym");
  _odsPrinter.printOptionalAttrDictWithKeyword((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ';
  _odsPrinter.printRegion(getBody());
}


} // namespace circt::kanagawa
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::kanagawa::ClassOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::kanagawa::detail::ClassOpGenericAdaptorBase::Properties)

namespace circt::kanagawa {


//===----------------------------------------------------------------------===//
// ::circt::kanagawa::ContainerInstanceOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

ContainerInstanceOpGenericAdaptorBase::ContainerInstanceOpGenericAdaptorBase(ContainerInstanceOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::circt::hw::InnerSymAttr ContainerInstanceOpGenericAdaptorBase::getInnerSym() {
  auto attr = getInnerSymAttr();
  return ::llvm::cast<::circt::hw::InnerSymAttr>(attr);
}

::circt::hw::InnerRefAttr ContainerInstanceOpGenericAdaptorBase::getTargetName() {
  auto attr = getTargetNameAttr();
  return ::llvm::cast<::circt::hw::InnerRefAttr>(attr);
}


} // namespace detail
ContainerInstanceOpAdaptor::ContainerInstanceOpAdaptor(ContainerInstanceOp op) : ContainerInstanceOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult ContainerInstanceOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_inner_sym = getProperties().inner_sym; (void)tblgen_inner_sym;
  if (!tblgen_inner_sym) return emitError(loc, "'kanagawa.container.instance' op requires attribute 'inner_sym'");
  auto tblgen_targetName = getProperties().targetName; (void)tblgen_targetName;
  if (!tblgen_targetName) return emitError(loc, "'kanagawa.container.instance' op requires attribute 'targetName'");

  if (tblgen_inner_sym && !((::llvm::isa<::circt::hw::InnerSymAttr>(tblgen_inner_sym))))
    return emitError(loc, "'kanagawa.container.instance' op attribute 'inner_sym' failed to satisfy constraint: Inner symbol definition");

  if (tblgen_targetName && !((::llvm::isa<::circt::hw::InnerRefAttr>(tblgen_targetName))))
    return emitError(loc, "'kanagawa.container.instance' op attribute 'targetName' failed to satisfy constraint: Refer to a name inside a module");
  return ::mlir::success();
}

::llvm::LogicalResult ContainerInstanceOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.inner_sym;
       auto attr = dict.get("inner_sym");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `inner_sym` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.targetName;
       auto attr = dict.get("targetName");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `targetName` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  return ::mlir::success();
}

::mlir::Attribute ContainerInstanceOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.inner_sym;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("inner_sym",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.targetName;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("targetName",
                                       propStorage));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code ContainerInstanceOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.inner_sym.getAsOpaquePointer()), 
    llvm::hash_value(prop.targetName.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> ContainerInstanceOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "inner_sym")
      return prop.inner_sym;

    if (name == "targetName")
      return prop.targetName;
  return std::nullopt;
}

void ContainerInstanceOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "inner_sym") {
       prop.inner_sym = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.inner_sym)>>(value);
       return;
    }

    if (name == "targetName") {
       prop.targetName = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.targetName)>>(value);
       return;
    }
}

void ContainerInstanceOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.inner_sym) attrs.append("inner_sym", prop.inner_sym);

    if (prop.targetName) attrs.append("targetName", prop.targetName);
}

::llvm::LogicalResult ContainerInstanceOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getInnerSymAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Kanagawa2(attr, "inner_sym", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getTargetNameAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Kanagawa1(attr, "targetName", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult ContainerInstanceOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.inner_sym)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readAttribute(prop.targetName)))
    return ::mlir::failure();
  return ::mlir::success();
}

void ContainerInstanceOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.inner_sym);
  writer.writeAttribute(prop.targetName);
}

::circt::hw::InnerSymAttr ContainerInstanceOp::getInnerSym() {
  auto attr = getInnerSymAttr();
  return ::llvm::cast<::circt::hw::InnerSymAttr>(attr);
}

::circt::hw::InnerRefAttr ContainerInstanceOp::getTargetName() {
  auto attr = getTargetNameAttr();
  return ::llvm::cast<::circt::hw::InnerRefAttr>(attr);
}

void ContainerInstanceOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, hw::InnerSymAttr instanceName, hw::InnerRefAttr targetName) {
      build(odsBuilder, odsState, odsBuilder.getType<ScopeRefType>(targetName),
        instanceName, targetName);
    
}

ContainerInstanceOp ContainerInstanceOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, hw::InnerSymAttr instanceName, hw::InnerRefAttr targetName) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(instanceName)>(instanceName), std::forward<decltype(targetName)>(targetName));
  auto __res__ = ::llvm::dyn_cast<ContainerInstanceOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ContainerInstanceOp ContainerInstanceOp::create(::mlir::ImplicitLocOpBuilder &builder, hw::InnerSymAttr instanceName, hw::InnerRefAttr targetName) {
  return create(builder, builder.getLoc(), std::forward<decltype(instanceName)>(instanceName), std::forward<decltype(targetName)>(targetName));
}

void ContainerInstanceOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type scopeRef, ::circt::hw::InnerSymAttr inner_sym, ::circt::hw::InnerRefAttr targetName) {
  odsState.getOrAddProperties<Properties>().inner_sym = inner_sym;
  odsState.getOrAddProperties<Properties>().targetName = targetName;
  odsState.addTypes(scopeRef);
}

ContainerInstanceOp ContainerInstanceOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type scopeRef, ::circt::hw::InnerSymAttr inner_sym, ::circt::hw::InnerRefAttr targetName) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(scopeRef)>(scopeRef), std::forward<decltype(inner_sym)>(inner_sym), std::forward<decltype(targetName)>(targetName));
  auto __res__ = ::llvm::dyn_cast<ContainerInstanceOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ContainerInstanceOp ContainerInstanceOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type scopeRef, ::circt::hw::InnerSymAttr inner_sym, ::circt::hw::InnerRefAttr targetName) {
  return create(builder, builder.getLoc(), std::forward<decltype(scopeRef)>(scopeRef), std::forward<decltype(inner_sym)>(inner_sym), std::forward<decltype(targetName)>(targetName));
}

void ContainerInstanceOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::circt::hw::InnerSymAttr inner_sym, ::circt::hw::InnerRefAttr targetName) {
  odsState.getOrAddProperties<Properties>().inner_sym = inner_sym;
  odsState.getOrAddProperties<Properties>().targetName = targetName;
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

ContainerInstanceOp ContainerInstanceOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::circt::hw::InnerSymAttr inner_sym, ::circt::hw::InnerRefAttr targetName) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(inner_sym)>(inner_sym), std::forward<decltype(targetName)>(targetName));
  auto __res__ = ::llvm::dyn_cast<ContainerInstanceOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ContainerInstanceOp ContainerInstanceOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::circt::hw::InnerSymAttr inner_sym, ::circt::hw::InnerRefAttr targetName) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(inner_sym)>(inner_sym), std::forward<decltype(targetName)>(targetName));
}

void ContainerInstanceOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<ContainerInstanceOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

ContainerInstanceOp ContainerInstanceOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<ContainerInstanceOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ContainerInstanceOp ContainerInstanceOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void ContainerInstanceOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

ContainerInstanceOp ContainerInstanceOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<ContainerInstanceOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ContainerInstanceOp ContainerInstanceOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult ContainerInstanceOp::verifyInvariantsImpl() {
  auto tblgen_inner_sym = getProperties().inner_sym; (void)tblgen_inner_sym;
  if (!tblgen_inner_sym) return emitOpError("requires attribute 'inner_sym'");
  auto tblgen_targetName = getProperties().targetName; (void)tblgen_targetName;
  if (!tblgen_targetName) return emitOpError("requires attribute 'targetName'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Kanagawa2(*this, tblgen_inner_sym, "inner_sym")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Kanagawa1(*this, tblgen_targetName, "targetName")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Kanagawa2(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult ContainerInstanceOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult ContainerInstanceOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::circt::hw::InnerSymAttr inner_symAttr;
  ::circt::hw::InnerRefAttr targetNameAttr;
  ::mlir::Type scopeRefRawType{};
  ::llvm::ArrayRef<::mlir::Type> scopeRefTypes(&scopeRefRawType, 1);

  if (parser.parseCustomAttributeWithFallback(inner_symAttr, ::mlir::Type{})) {
    return ::mlir::failure();
  }
  if (inner_symAttr) result.getOrAddProperties<ContainerInstanceOp::Properties>().inner_sym = inner_symAttr;
  if (parser.parseComma())
    return ::mlir::failure();

  if (parser.parseCustomAttributeWithFallback(targetNameAttr, ::mlir::Type{})) {
    return ::mlir::failure();
  }
  if (targetNameAttr) result.getOrAddProperties<ContainerInstanceOp::Properties>().targetName = targetNameAttr;
  {
    auto loc = parser.getCurrentLocation();(void)loc;
    if (parser.parseOptionalAttrDict(result.attributes))
      return ::mlir::failure();
    if (failed(verifyInherentAttrs(result.name, result.attributes, [&]() {
        return parser.emitError(loc) << "'" << result.name.getStringRef() << "' op ";
      })))
      return ::mlir::failure();
  }
  {
    auto odsResult = parseScopeRefFromName(parser, scopeRefRawType, targetNameAttr);
    if (odsResult) return ::mlir::failure();
  }
  result.addTypes(scopeRefTypes);
  return ::mlir::success();
}

void ContainerInstanceOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
_odsPrinter.printStrippedAttrOrType(getInnerSymAttr());
  _odsPrinter << ",";
  _odsPrinter << ' ';
_odsPrinter.printStrippedAttrOrType(getTargetNameAttr());
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("inner_sym");
  elidedAttrs.push_back("targetName");
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ';
  printScopeRefFromName(_odsPrinter, *this, getScopeRef().getType(), getTargetNameAttr());
}

ContainerOp ContainerInstanceOp::getContainer(
    const hw::InnerRefNamespace &ns) {
  // return dyn_cast_or_null<ContainerOp>(getReferencedModule(&ns));
  return ns.lookupOp<ContainerOp>(getTargetNameAttr());
}
Operation* ContainerInstanceOp::getReferencedModule(
    const hw::InnerRefNamespace &ns) {
  return getContainer(ns);
}

// For hw:InnerSymbol - the symbol targets the operation and not any result.
std::optional<size_t> ContainerInstanceOp::getTargetResultIndex() {
  return std::nullopt;
}

} // namespace circt::kanagawa
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::kanagawa::ContainerInstanceOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::kanagawa::detail::ContainerInstanceOpGenericAdaptorBase::Properties)

namespace circt::kanagawa {


//===----------------------------------------------------------------------===//
// ::circt::kanagawa::ContainerOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

ContainerOpGenericAdaptorBase::ContainerOpGenericAdaptorBase(ContainerOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::circt::hw::InnerSymAttr ContainerOpGenericAdaptorBase::getInnerSym() {
  auto attr = getInnerSymAttr();
  return ::llvm::cast<::circt::hw::InnerSymAttr>(attr);
}

::mlir::UnitAttr ContainerOpGenericAdaptorBase::getIsTopLevelAttr() {
  auto attr = ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(getProperties().isTopLevel);
  if (!attr)
    attr = ((false) ? ::mlir::Builder(odsAttrs.getContext()).getUnitAttr() : nullptr);
  return attr;
}

bool ContainerOpGenericAdaptorBase::getIsTopLevel() {
  auto attr = getIsTopLevelAttr();
    if (!attr)
      return ((false) ? ::mlir::Builder(odsAttrs.getContext()).getUnitAttr() : nullptr) != nullptr;
  return attr != nullptr;
}

::std::optional< ::llvm::StringRef > ContainerOpGenericAdaptorBase::getName() {
  auto attr = getNameAttr();
  return attr ? ::std::optional< ::llvm::StringRef >(attr.getValue()) : (::std::nullopt);
}


} // namespace detail
ContainerOpAdaptor::ContainerOpAdaptor(ContainerOp op) : ContainerOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult ContainerOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_inner_sym = getProperties().inner_sym; (void)tblgen_inner_sym;
  if (!tblgen_inner_sym) return emitError(loc, "'kanagawa.container' op requires attribute 'inner_sym'");
  auto tblgen_isTopLevel = getProperties().isTopLevel; (void)tblgen_isTopLevel;
  auto tblgen_name = getProperties().name; (void)tblgen_name;

  if (tblgen_inner_sym && !((::llvm::isa<::circt::hw::InnerSymAttr>(tblgen_inner_sym))))
    return emitError(loc, "'kanagawa.container' op attribute 'inner_sym' failed to satisfy constraint: Inner symbol definition");

  if (tblgen_isTopLevel && !((::llvm::isa<::mlir::UnitAttr>(tblgen_isTopLevel))))
    return emitError(loc, "'kanagawa.container' op attribute 'isTopLevel' failed to satisfy constraint: unit attribute");

  if (tblgen_name && !((::llvm::isa<::mlir::StringAttr>(tblgen_name))))
    return emitError(loc, "'kanagawa.container' op attribute 'name' failed to satisfy constraint: string attribute");
  return ::mlir::success();
}

::llvm::LogicalResult ContainerOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.inner_sym;
       auto attr = dict.get("inner_sym");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `inner_sym` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.isTopLevel;
       auto attr = dict.get("isTopLevel");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `isTopLevel` in property conversion: " << attr;
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
  return ::mlir::success();
}

::mlir::Attribute ContainerOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.inner_sym;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("inner_sym",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.isTopLevel;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("isTopLevel",
                                       propStorage));
    }

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

llvm::hash_code ContainerOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.inner_sym.getAsOpaquePointer()), 
    llvm::hash_value(prop.isTopLevel.getAsOpaquePointer()), 
    llvm::hash_value(prop.name.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> ContainerOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "inner_sym")
      return prop.inner_sym;

    if (name == "isTopLevel")
      return prop.isTopLevel;

    if (name == "name")
      return prop.name;
  return std::nullopt;
}

void ContainerOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "inner_sym") {
       prop.inner_sym = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.inner_sym)>>(value);
       return;
    }

    if (name == "isTopLevel") {
       prop.isTopLevel = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.isTopLevel)>>(value);
       return;
    }

    if (name == "name") {
       prop.name = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.name)>>(value);
       return;
    }
}

void ContainerOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.inner_sym) attrs.append("inner_sym", prop.inner_sym);

    if (prop.isTopLevel) attrs.append("isTopLevel", prop.isTopLevel);

    if (prop.name) attrs.append("name", prop.name);
}

::llvm::LogicalResult ContainerOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getInnerSymAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Kanagawa2(attr, "inner_sym", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getIsTopLevelAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Kanagawa4(attr, "isTopLevel", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getNameAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Kanagawa3(attr, "name", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult ContainerOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.inner_sym)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readOptionalAttribute(prop.isTopLevel)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readOptionalAttribute(prop.name)))
    return ::mlir::failure();
  return ::mlir::success();
}

void ContainerOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.inner_sym);

  writer.writeOptionalAttribute(prop.isTopLevel);

  writer.writeOptionalAttribute(prop.name);
}

::circt::hw::InnerSymAttr ContainerOp::getInnerSym() {
  auto attr = getInnerSymAttr();
  return ::llvm::cast<::circt::hw::InnerSymAttr>(attr);
}

bool ContainerOp::getIsTopLevel() {
  auto attr = getIsTopLevelAttr();
    if (!attr)
      return ((false) ? ::mlir::Builder((*this)->getContext()).getUnitAttr() : nullptr) != nullptr;
  return attr != nullptr;
}

::std::optional< ::llvm::StringRef > ContainerOp::getName() {
  auto attr = getNameAttr();
  return attr ? ::std::optional< ::llvm::StringRef >(attr.getValue()) : (::std::nullopt);
}

void ContainerOp::setIsTopLevel(bool attrValue) {
    auto &odsProp = getProperties().isTopLevel;
    if (attrValue)
      odsProp = ((attrValue) ? ::mlir::Builder((*this)->getContext()).getUnitAttr() : nullptr);
    else
      odsProp = nullptr;
}

void ContainerOp::setName(::std::optional<::llvm::StringRef> attrValue) {
    auto &odsProp = getProperties().name;
    if (attrValue)
      odsProp = ::mlir::Builder((*this)->getContext()).getStringAttr(*attrValue);
    else
      odsProp = nullptr;
}

void ContainerOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, StringRef inner_sym, bool isTopLevel, mlir::StringAttr name) {
      build(odsBuilder, odsState,
        hw::InnerSymAttr::get(odsBuilder.getStringAttr(inner_sym)), isTopLevel, name);
    
}

ContainerOp ContainerOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, StringRef inner_sym, bool isTopLevel, mlir::StringAttr name) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(inner_sym)>(inner_sym), std::forward<decltype(isTopLevel)>(isTopLevel), std::forward<decltype(name)>(name));
  auto __res__ = ::llvm::dyn_cast<ContainerOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ContainerOp ContainerOp::create(::mlir::ImplicitLocOpBuilder &builder, StringRef inner_sym, bool isTopLevel, mlir::StringAttr name) {
  return create(builder, builder.getLoc(), std::forward<decltype(inner_sym)>(inner_sym), std::forward<decltype(isTopLevel)>(isTopLevel), std::forward<decltype(name)>(name));
}

void ContainerOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, hw::InnerSymAttr inner_sym, bool isTopLevel, mlir::StringAttr name) {
      auto region = odsState.addRegion();
      region->push_back(new Block());
      odsState.addAttribute(getInnerSymAttrName(odsState.name), inner_sym);
      if (isTopLevel)
        odsState.addAttribute(getIsTopLevelAttrName(odsState.name), odsBuilder.getUnitAttr());
      if(name)
        odsState.addAttribute(getNameAttrName(odsState.name), name);
    
}

ContainerOp ContainerOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, hw::InnerSymAttr inner_sym, bool isTopLevel, mlir::StringAttr name) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(inner_sym)>(inner_sym), std::forward<decltype(isTopLevel)>(isTopLevel), std::forward<decltype(name)>(name));
  auto __res__ = ::llvm::dyn_cast<ContainerOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ContainerOp ContainerOp::create(::mlir::ImplicitLocOpBuilder &builder, hw::InnerSymAttr inner_sym, bool isTopLevel, mlir::StringAttr name) {
  return create(builder, builder.getLoc(), std::forward<decltype(inner_sym)>(inner_sym), std::forward<decltype(isTopLevel)>(isTopLevel), std::forward<decltype(name)>(name));
}

::llvm::LogicalResult ContainerOp::verifyInvariantsImpl() {
  auto tblgen_inner_sym = getProperties().inner_sym; (void)tblgen_inner_sym;
  if (!tblgen_inner_sym) return emitOpError("requires attribute 'inner_sym'");
  auto tblgen_isTopLevel = getProperties().isTopLevel; (void)tblgen_isTopLevel;
  auto tblgen_name = getProperties().name; (void)tblgen_name;

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Kanagawa2(*this, tblgen_inner_sym, "inner_sym")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Kanagawa4(*this, tblgen_isTopLevel, "isTopLevel")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Kanagawa3(*this, tblgen_name, "name")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;

    for (auto &region : ::llvm::MutableArrayRef((*this)->getRegion(0)))
      if (::mlir::failed(__mlir_ods_local_region_constraint_Kanagawa1(*this, region, "body", index++)))
        return ::mlir::failure();
  }
  return ::mlir::success();
}

::llvm::LogicalResult ContainerOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult ContainerOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::StringAttr nameAttr;
  ::circt::hw::InnerSymAttr inner_symAttr;
  std::unique_ptr<::mlir::Region> bodyRegion = std::make_unique<::mlir::Region>();

  ::mlir::OptionalParseResult parseResultnameAttr =
    parser.parseOptionalAttribute(nameAttr, parser.getBuilder().getType<::mlir::NoneType>());
  if (parseResultnameAttr.has_value() && failed(*parseResultnameAttr))
    return ::mlir::failure();
  if (parseResultnameAttr.has_value() && succeeded(*parseResultnameAttr))
  if (nameAttr) result.getOrAddProperties<ContainerOp::Properties>().name = nameAttr;
  if (nameAttr) {
  }
  if (parser.parseKeyword("sym"))
    return ::mlir::failure();

  if (parser.parseCustomAttributeWithFallback(inner_symAttr, ::mlir::Type{})) {
    return ::mlir::failure();
  }
  if (inner_symAttr) result.getOrAddProperties<ContainerOp::Properties>().inner_sym = inner_symAttr;
  if (::mlir::succeeded(parser.parseOptionalKeyword("top_level"))) {
    result.getOrAddProperties<ContainerOp::Properties>().isTopLevel = parser.getBuilder().getUnitAttr();  }
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

void ContainerOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  if (getNameAttr()) {
    _odsPrinter << ' ';
    _odsPrinter.printAttributeWithoutType(getNameAttr());
  }
  _odsPrinter << ' ' << "sym";
  _odsPrinter << ' ';
_odsPrinter.printStrippedAttrOrType(getInnerSymAttr());
  if ((getIsTopLevelAttr() && getIsTopLevelAttr() != ((false) ? ::mlir::OpBuilder((*this)->getContext()).getUnitAttr() : nullptr))) {
    _odsPrinter << ' ' << "top_level";
  }
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("name");
  elidedAttrs.push_back("inner_sym");
  elidedAttrs.push_back("isTopLevel");
  {
     ::mlir::Builder odsBuilder(getContext());
     ::mlir::Attribute attr = getIsTopLevelAttr();
     if(attr && (attr == ((false) ? odsBuilder.getUnitAttr() : nullptr)))
       elidedAttrs.push_back("isTopLevel");
  }
  _odsPrinter.printOptionalAttrDictWithKeyword((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ';
  _odsPrinter.printRegion(getBody());
}


} // namespace circt::kanagawa
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::kanagawa::ContainerOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::kanagawa::detail::ContainerOpGenericAdaptorBase::Properties)

namespace circt::kanagawa {


//===----------------------------------------------------------------------===//
// ::circt::kanagawa::DCBlockOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

DCBlockOpGenericAdaptorBase::DCBlockOpGenericAdaptorBase(DCBlockOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

std::pair<unsigned, unsigned> DCBlockOpGenericAdaptorBase::getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
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

::std::optional<uint64_t> DCBlockOpGenericAdaptorBase::getMaxThreads() {
  auto attr = getMaxThreadsAttr();
  return attr ? ::std::optional<uint64_t>(attr.getValue().getZExtValue()) : (::std::nullopt);
}


} // namespace detail
DCBlockOpAdaptor::DCBlockOpAdaptor(DCBlockOp op) : DCBlockOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult DCBlockOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_maxThreads = getProperties().maxThreads; (void)tblgen_maxThreads;

  if (tblgen_maxThreads && !((((::llvm::isa<::mlir::IntegerAttr>(tblgen_maxThreads))) && ((::llvm::cast<::mlir::IntegerAttr>(tblgen_maxThreads).getType().isSignlessInteger(64)))) && ((::llvm::cast<::mlir::IntegerAttr>(tblgen_maxThreads).getInt() >= 1))))
    return emitError(loc, "'kanagawa.sblock.dc' op attribute 'maxThreads' failed to satisfy constraint: 64-bit signless integer attribute whose minimum value is 1");
  return ::mlir::success();
}

std::pair<unsigned, unsigned> DCBlockOp::getODSOperandIndexAndLength(unsigned index) {
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

::mlir::MutableOperandRange DCBlockOp::getInputsMutable() {
  auto range = getODSOperandIndexAndLength(0);
  auto mutableRange = ::mlir::MutableOperandRange(getOperation(), range.first, range.second);
  return mutableRange;
}

std::pair<unsigned, unsigned> DCBlockOp::getODSResultIndexAndLength(unsigned index) {
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

::llvm::LogicalResult DCBlockOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.maxThreads;
       auto attr = dict.get("maxThreads");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `maxThreads` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  return ::mlir::success();
}

::mlir::Attribute DCBlockOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.maxThreads;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("maxThreads",
                                       propStorage));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code DCBlockOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.maxThreads.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> DCBlockOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "maxThreads")
      return prop.maxThreads;
  return std::nullopt;
}

void DCBlockOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "maxThreads") {
       prop.maxThreads = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.maxThreads)>>(value);
       return;
    }
}

void DCBlockOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.maxThreads) attrs.append("maxThreads", prop.maxThreads);
}

::llvm::LogicalResult DCBlockOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getMaxThreadsAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Kanagawa5(attr, "maxThreads", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult DCBlockOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readOptionalAttribute(prop.maxThreads)))
    return ::mlir::failure();
  return ::mlir::success();
}

void DCBlockOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;

  writer.writeOptionalAttribute(prop.maxThreads);
}

::std::optional<uint64_t> DCBlockOp::getMaxThreads() {
  auto attr = getMaxThreadsAttr();
  return attr ? ::std::optional<uint64_t>(attr.getValue().getZExtValue()) : (::std::nullopt);
}

void DCBlockOp::setMaxThreads(::std::optional<uint64_t> attrValue) {
    auto &odsProp = getProperties().maxThreads;
    if (attrValue)
      odsProp = ::mlir::Builder((*this)->getContext()).getIntegerAttr(::mlir::Builder((*this)->getContext()).getIntegerType(64), *attrValue);
    else
      odsProp = nullptr;
}

DCBlockOp DCBlockOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, TypeRange outputs, ValueRange inputs, IntegerAttr maxThreads) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(outputs)>(outputs), std::forward<decltype(inputs)>(inputs), std::forward<decltype(maxThreads)>(maxThreads));
  auto __res__ = ::llvm::dyn_cast<DCBlockOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

DCBlockOp DCBlockOp::create(::mlir::ImplicitLocOpBuilder &builder, TypeRange outputs, ValueRange inputs, IntegerAttr maxThreads) {
  return create(builder, builder.getLoc(), std::forward<decltype(outputs)>(outputs), std::forward<decltype(inputs)>(inputs), std::forward<decltype(maxThreads)>(maxThreads));
}

::llvm::LogicalResult DCBlockOp::verifyInvariantsImpl() {
  auto tblgen_maxThreads = getProperties().maxThreads; (void)tblgen_maxThreads;

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Kanagawa5(*this, tblgen_maxThreads, "maxThreads")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Kanagawa1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Kanagawa1(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;

    for (auto &region : ::llvm::MutableArrayRef((*this)->getRegion(0)))
      if (::mlir::failed(__mlir_ods_local_region_constraint_Kanagawa1(*this, region, "body", index++)))
        return ::mlir::failure();
  }
  return ::mlir::success();
}

::llvm::LogicalResult DCBlockOp::verifyInvariants() {
  if(::mlir::succeeded(verifyInvariantsImpl()) && ::mlir::succeeded(verify()))
    return ::mlir::success();
  return ::mlir::failure();
}

::llvm::LogicalResult DCBlockOp::setPropertiesFromParsedAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
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

    auto &propStorage = prop.maxThreads;
    auto maxThreadsAttrName = ::mlir::StringAttr::get(ctx, "maxThreads");
    auto attr = dict.get(maxThreadsAttrName);
    usedKeys.insert(maxThreadsAttrName);
    if (attr || /*isRequired=*/false) {
      if (!attr) {
        emitError() << "expected key entry for maxThreads in DictionaryAttr to set "
                   "Properties.";
        return ::mlir::failure();
      }
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `maxThreads` in property conversion: " << attr;
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


} // namespace circt::kanagawa
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::kanagawa::DCBlockOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::kanagawa::detail::DCBlockOpGenericAdaptorBase::Properties)

namespace circt::kanagawa {


//===----------------------------------------------------------------------===//
// ::circt::kanagawa::DataflowMethodOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

DataflowMethodOpGenericAdaptorBase::DataflowMethodOpGenericAdaptorBase(DataflowMethodOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::circt::hw::InnerSymAttr DataflowMethodOpGenericAdaptorBase::getInnerSym() {
  auto attr = getInnerSymAttr();
  return ::llvm::cast<::circt::hw::InnerSymAttr>(attr);
}

::mlir::FunctionType DataflowMethodOpGenericAdaptorBase::getFunctionType() {
  auto attr = getFunctionTypeAttr();
  return ::llvm::cast<::mlir::FunctionType>(attr.getValue());
}

::mlir::ArrayAttr DataflowMethodOpGenericAdaptorBase::getArgNames() {
  auto attr = getArgNamesAttr();
  return attr;
}

::std::optional< ::mlir::ArrayAttr > DataflowMethodOpGenericAdaptorBase::getArgAttrs() {
  auto attr = getArgAttrsAttr();
  return attr ? ::std::optional< ::mlir::ArrayAttr >(attr) : (::std::nullopt);
}

::std::optional< ::mlir::ArrayAttr > DataflowMethodOpGenericAdaptorBase::getResAttrs() {
  auto attr = getResAttrsAttr();
  return attr ? ::std::optional< ::mlir::ArrayAttr >(attr) : (::std::nullopt);
}


} // namespace detail
DataflowMethodOpAdaptor::DataflowMethodOpAdaptor(DataflowMethodOp op) : DataflowMethodOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult DataflowMethodOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_argNames = getProperties().argNames; (void)tblgen_argNames;
  if (!tblgen_argNames) return emitError(loc, "'kanagawa.method.df' op requires attribute 'argNames'");
  auto tblgen_arg_attrs = getProperties().arg_attrs; (void)tblgen_arg_attrs;
  auto tblgen_function_type = getProperties().function_type; (void)tblgen_function_type;
  if (!tblgen_function_type) return emitError(loc, "'kanagawa.method.df' op requires attribute 'function_type'");
  auto tblgen_inner_sym = getProperties().inner_sym; (void)tblgen_inner_sym;
  if (!tblgen_inner_sym) return emitError(loc, "'kanagawa.method.df' op requires attribute 'inner_sym'");
  auto tblgen_res_attrs = getProperties().res_attrs; (void)tblgen_res_attrs;

  if (tblgen_inner_sym && !((::llvm::isa<::circt::hw::InnerSymAttr>(tblgen_inner_sym))))
    return emitError(loc, "'kanagawa.method.df' op attribute 'inner_sym' failed to satisfy constraint: Inner symbol definition");

  if (tblgen_function_type && !(((::llvm::isa<::mlir::TypeAttr>(tblgen_function_type))) && ((::llvm::isa<::mlir::FunctionType>(::llvm::cast<::mlir::TypeAttr>(tblgen_function_type).getValue()))) && ((::llvm::isa<::mlir::FunctionType>(::llvm::cast<::mlir::TypeAttr>(tblgen_function_type).getValue())))))
    return emitError(loc, "'kanagawa.method.df' op attribute 'function_type' failed to satisfy constraint: type attribute of function type");

  if (tblgen_argNames && !((::llvm::isa<::mlir::ArrayAttr>(tblgen_argNames))))
    return emitError(loc, "'kanagawa.method.df' op attribute 'argNames' failed to satisfy constraint: array attribute");

  if (tblgen_arg_attrs && !(((::llvm::isa<::mlir::ArrayAttr>(tblgen_arg_attrs))) && (::llvm::all_of(::llvm::cast<::mlir::ArrayAttr>(tblgen_arg_attrs), [&](::mlir::Attribute attr) { return attr && ((::llvm::isa<::mlir::DictionaryAttr>(attr))); }))))
    return emitError(loc, "'kanagawa.method.df' op attribute 'arg_attrs' failed to satisfy constraint: Array of dictionary attributes");

  if (tblgen_res_attrs && !(((::llvm::isa<::mlir::ArrayAttr>(tblgen_res_attrs))) && (::llvm::all_of(::llvm::cast<::mlir::ArrayAttr>(tblgen_res_attrs), [&](::mlir::Attribute attr) { return attr && ((::llvm::isa<::mlir::DictionaryAttr>(attr))); }))))
    return emitError(loc, "'kanagawa.method.df' op attribute 'res_attrs' failed to satisfy constraint: Array of dictionary attributes");
  return ::mlir::success();
}

::llvm::LogicalResult DataflowMethodOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.argNames;
       auto attr = dict.get("argNames");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `argNames` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.arg_attrs;
       auto attr = dict.get("arg_attrs");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `arg_attrs` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.function_type;
       auto attr = dict.get("function_type");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `function_type` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.inner_sym;
       auto attr = dict.get("inner_sym");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `inner_sym` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.res_attrs;
       auto attr = dict.get("res_attrs");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `res_attrs` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  return ::mlir::success();
}

::mlir::Attribute DataflowMethodOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.argNames;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("argNames",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.arg_attrs;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("arg_attrs",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.function_type;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("function_type",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.inner_sym;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("inner_sym",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.res_attrs;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("res_attrs",
                                       propStorage));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code DataflowMethodOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.argNames.getAsOpaquePointer()), 
    llvm::hash_value(prop.arg_attrs.getAsOpaquePointer()), 
    llvm::hash_value(prop.function_type.getAsOpaquePointer()), 
    llvm::hash_value(prop.inner_sym.getAsOpaquePointer()), 
    llvm::hash_value(prop.res_attrs.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> DataflowMethodOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "argNames")
      return prop.argNames;

    if (name == "arg_attrs")
      return prop.arg_attrs;

    if (name == "function_type")
      return prop.function_type;

    if (name == "inner_sym")
      return prop.inner_sym;

    if (name == "res_attrs")
      return prop.res_attrs;
  return std::nullopt;
}

void DataflowMethodOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "argNames") {
       prop.argNames = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.argNames)>>(value);
       return;
    }

    if (name == "arg_attrs") {
       prop.arg_attrs = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.arg_attrs)>>(value);
       return;
    }

    if (name == "function_type") {
       prop.function_type = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.function_type)>>(value);
       return;
    }

    if (name == "inner_sym") {
       prop.inner_sym = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.inner_sym)>>(value);
       return;
    }

    if (name == "res_attrs") {
       prop.res_attrs = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.res_attrs)>>(value);
       return;
    }
}

void DataflowMethodOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.argNames) attrs.append("argNames", prop.argNames);

    if (prop.arg_attrs) attrs.append("arg_attrs", prop.arg_attrs);

    if (prop.function_type) attrs.append("function_type", prop.function_type);

    if (prop.inner_sym) attrs.append("inner_sym", prop.inner_sym);

    if (prop.res_attrs) attrs.append("res_attrs", prop.res_attrs);
}

::llvm::LogicalResult DataflowMethodOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getArgNamesAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Kanagawa7(attr, "argNames", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getArgAttrsAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Kanagawa8(attr, "arg_attrs", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getFunctionTypeAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Kanagawa6(attr, "function_type", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getInnerSymAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Kanagawa2(attr, "inner_sym", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getResAttrsAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Kanagawa8(attr, "res_attrs", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult DataflowMethodOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.argNames)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readOptionalAttribute(prop.arg_attrs)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readAttribute(prop.function_type)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readAttribute(prop.inner_sym)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readOptionalAttribute(prop.res_attrs)))
    return ::mlir::failure();
  return ::mlir::success();
}

void DataflowMethodOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.argNames);

  writer.writeOptionalAttribute(prop.arg_attrs);
  writer.writeAttribute(prop.function_type);
  writer.writeAttribute(prop.inner_sym);

  writer.writeOptionalAttribute(prop.res_attrs);
}

::circt::hw::InnerSymAttr DataflowMethodOp::getInnerSym() {
  auto attr = getInnerSymAttr();
  return ::llvm::cast<::circt::hw::InnerSymAttr>(attr);
}

::mlir::FunctionType DataflowMethodOp::getFunctionType() {
  auto attr = getFunctionTypeAttr();
  return ::llvm::cast<::mlir::FunctionType>(attr.getValue());
}

::mlir::ArrayAttr DataflowMethodOp::getArgNames() {
  auto attr = getArgNamesAttr();
  return attr;
}

::std::optional< ::mlir::ArrayAttr > DataflowMethodOp::getArgAttrs() {
  auto attr = getArgAttrsAttr();
  return attr ? ::std::optional< ::mlir::ArrayAttr >(attr) : (::std::nullopt);
}

::std::optional< ::mlir::ArrayAttr > DataflowMethodOp::getResAttrs() {
  auto attr = getResAttrsAttr();
  return attr ? ::std::optional< ::mlir::ArrayAttr >(attr) : (::std::nullopt);
}

void DataflowMethodOp::setFunctionType(::mlir::FunctionType attrValue) {
  getProperties().function_type = ::mlir::TypeAttr::get(attrValue);
}

void DataflowMethodOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::circt::hw::InnerSymAttr inner_sym, ::mlir::TypeAttr function_type, ::mlir::ArrayAttr argNames, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs) {
  odsState.getOrAddProperties<Properties>().inner_sym = inner_sym;
  odsState.getOrAddProperties<Properties>().function_type = function_type;
  odsState.getOrAddProperties<Properties>().argNames = argNames;
  if (arg_attrs) {
    odsState.getOrAddProperties<Properties>().arg_attrs = arg_attrs;
  }
  if (res_attrs) {
    odsState.getOrAddProperties<Properties>().res_attrs = res_attrs;
  }
  (void)odsState.addRegion();
}

DataflowMethodOp DataflowMethodOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::circt::hw::InnerSymAttr inner_sym, ::mlir::TypeAttr function_type, ::mlir::ArrayAttr argNames, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(inner_sym)>(inner_sym), std::forward<decltype(function_type)>(function_type), std::forward<decltype(argNames)>(argNames), std::forward<decltype(arg_attrs)>(arg_attrs), std::forward<decltype(res_attrs)>(res_attrs));
  auto __res__ = ::llvm::dyn_cast<DataflowMethodOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

DataflowMethodOp DataflowMethodOp::create(::mlir::ImplicitLocOpBuilder &builder, ::circt::hw::InnerSymAttr inner_sym, ::mlir::TypeAttr function_type, ::mlir::ArrayAttr argNames, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs) {
  return create(builder, builder.getLoc(), std::forward<decltype(inner_sym)>(inner_sym), std::forward<decltype(function_type)>(function_type), std::forward<decltype(argNames)>(argNames), std::forward<decltype(arg_attrs)>(arg_attrs), std::forward<decltype(res_attrs)>(res_attrs));
}

void DataflowMethodOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::circt::hw::InnerSymAttr inner_sym, ::mlir::TypeAttr function_type, ::mlir::ArrayAttr argNames, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs) {
  odsState.getOrAddProperties<Properties>().inner_sym = inner_sym;
  odsState.getOrAddProperties<Properties>().function_type = function_type;
  odsState.getOrAddProperties<Properties>().argNames = argNames;
  if (arg_attrs) {
    odsState.getOrAddProperties<Properties>().arg_attrs = arg_attrs;
  }
  if (res_attrs) {
    odsState.getOrAddProperties<Properties>().res_attrs = res_attrs;
  }
  (void)odsState.addRegion();
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

DataflowMethodOp DataflowMethodOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::circt::hw::InnerSymAttr inner_sym, ::mlir::TypeAttr function_type, ::mlir::ArrayAttr argNames, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(inner_sym)>(inner_sym), std::forward<decltype(function_type)>(function_type), std::forward<decltype(argNames)>(argNames), std::forward<decltype(arg_attrs)>(arg_attrs), std::forward<decltype(res_attrs)>(res_attrs));
  auto __res__ = ::llvm::dyn_cast<DataflowMethodOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

DataflowMethodOp DataflowMethodOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::circt::hw::InnerSymAttr inner_sym, ::mlir::TypeAttr function_type, ::mlir::ArrayAttr argNames, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(inner_sym)>(inner_sym), std::forward<decltype(function_type)>(function_type), std::forward<decltype(argNames)>(argNames), std::forward<decltype(arg_attrs)>(arg_attrs), std::forward<decltype(res_attrs)>(res_attrs));
}

void DataflowMethodOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::circt::hw::InnerSymAttr inner_sym, ::mlir::FunctionType function_type, ::mlir::ArrayAttr argNames, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs) {
  odsState.getOrAddProperties<Properties>().inner_sym = inner_sym;
  odsState.getOrAddProperties<Properties>().function_type = ::mlir::TypeAttr::get(function_type);
  odsState.getOrAddProperties<Properties>().argNames = argNames;
  if (arg_attrs) {
    odsState.getOrAddProperties<Properties>().arg_attrs = arg_attrs;
  }
  if (res_attrs) {
    odsState.getOrAddProperties<Properties>().res_attrs = res_attrs;
  }
  (void)odsState.addRegion();
}

DataflowMethodOp DataflowMethodOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::circt::hw::InnerSymAttr inner_sym, ::mlir::FunctionType function_type, ::mlir::ArrayAttr argNames, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(inner_sym)>(inner_sym), std::forward<decltype(function_type)>(function_type), std::forward<decltype(argNames)>(argNames), std::forward<decltype(arg_attrs)>(arg_attrs), std::forward<decltype(res_attrs)>(res_attrs));
  auto __res__ = ::llvm::dyn_cast<DataflowMethodOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

DataflowMethodOp DataflowMethodOp::create(::mlir::ImplicitLocOpBuilder &builder, ::circt::hw::InnerSymAttr inner_sym, ::mlir::FunctionType function_type, ::mlir::ArrayAttr argNames, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs) {
  return create(builder, builder.getLoc(), std::forward<decltype(inner_sym)>(inner_sym), std::forward<decltype(function_type)>(function_type), std::forward<decltype(argNames)>(argNames), std::forward<decltype(arg_attrs)>(arg_attrs), std::forward<decltype(res_attrs)>(res_attrs));
}

void DataflowMethodOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::circt::hw::InnerSymAttr inner_sym, ::mlir::FunctionType function_type, ::mlir::ArrayAttr argNames, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs) {
  odsState.getOrAddProperties<Properties>().inner_sym = inner_sym;
  odsState.getOrAddProperties<Properties>().function_type = ::mlir::TypeAttr::get(function_type);
  odsState.getOrAddProperties<Properties>().argNames = argNames;
  if (arg_attrs) {
    odsState.getOrAddProperties<Properties>().arg_attrs = arg_attrs;
  }
  if (res_attrs) {
    odsState.getOrAddProperties<Properties>().res_attrs = res_attrs;
  }
  (void)odsState.addRegion();
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

DataflowMethodOp DataflowMethodOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::circt::hw::InnerSymAttr inner_sym, ::mlir::FunctionType function_type, ::mlir::ArrayAttr argNames, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(inner_sym)>(inner_sym), std::forward<decltype(function_type)>(function_type), std::forward<decltype(argNames)>(argNames), std::forward<decltype(arg_attrs)>(arg_attrs), std::forward<decltype(res_attrs)>(res_attrs));
  auto __res__ = ::llvm::dyn_cast<DataflowMethodOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

DataflowMethodOp DataflowMethodOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::circt::hw::InnerSymAttr inner_sym, ::mlir::FunctionType function_type, ::mlir::ArrayAttr argNames, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(inner_sym)>(inner_sym), std::forward<decltype(function_type)>(function_type), std::forward<decltype(argNames)>(argNames), std::forward<decltype(arg_attrs)>(arg_attrs), std::forward<decltype(res_attrs)>(res_attrs));
}

void DataflowMethodOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  for (unsigned i = 0; i != 1; ++i)
    (void)odsState.addRegion();
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<DataflowMethodOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

DataflowMethodOp DataflowMethodOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<DataflowMethodOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

DataflowMethodOp DataflowMethodOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void DataflowMethodOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  for (unsigned i = 0; i != 1; ++i)
    (void)odsState.addRegion();
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

DataflowMethodOp DataflowMethodOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<DataflowMethodOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

DataflowMethodOp DataflowMethodOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult DataflowMethodOp::verifyInvariantsImpl() {
  auto tblgen_argNames = getProperties().argNames; (void)tblgen_argNames;
  if (!tblgen_argNames) return emitOpError("requires attribute 'argNames'");
  auto tblgen_arg_attrs = getProperties().arg_attrs; (void)tblgen_arg_attrs;
  auto tblgen_function_type = getProperties().function_type; (void)tblgen_function_type;
  if (!tblgen_function_type) return emitOpError("requires attribute 'function_type'");
  auto tblgen_inner_sym = getProperties().inner_sym; (void)tblgen_inner_sym;
  if (!tblgen_inner_sym) return emitOpError("requires attribute 'inner_sym'");
  auto tblgen_res_attrs = getProperties().res_attrs; (void)tblgen_res_attrs;

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Kanagawa2(*this, tblgen_inner_sym, "inner_sym")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Kanagawa6(*this, tblgen_function_type, "function_type")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Kanagawa7(*this, tblgen_argNames, "argNames")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Kanagawa8(*this, tblgen_arg_attrs, "arg_attrs")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Kanagawa8(*this, tblgen_res_attrs, "res_attrs")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;

    for (auto &region : ::llvm::MutableArrayRef((*this)->getRegion(0)))
      if (::mlir::failed(__mlir_ods_local_region_constraint_Kanagawa1(*this, region, "body", index++)))
        return ::mlir::failure();
  }
  return ::mlir::success();
}

::llvm::LogicalResult DataflowMethodOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::llvm::LogicalResult DataflowMethodOp::setPropertiesFromParsedAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
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

    auto &propStorage = prop.inner_sym;
    auto inner_symAttrName = ::mlir::StringAttr::get(ctx, "inner_sym");
    auto attr = dict.get(inner_symAttrName);
    usedKeys.insert(inner_symAttrName);
    if (attr || /*isRequired=*/true) {
      if (!attr) {
        emitError() << "expected key entry for inner_sym in DictionaryAttr to set "
                   "Properties.";
        return ::mlir::failure();
      }
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `inner_sym` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  {

    auto &propStorage = prop.function_type;
    auto function_typeAttrName = ::mlir::StringAttr::get(ctx, "function_type");
    auto attr = dict.get(function_typeAttrName);
    usedKeys.insert(function_typeAttrName);
    if (attr || /*isRequired=*/true) {
      if (!attr) {
        emitError() << "expected key entry for function_type in DictionaryAttr to set "
                   "Properties.";
        return ::mlir::failure();
      }
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `function_type` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  {

    auto &propStorage = prop.argNames;
    auto argNamesAttrName = ::mlir::StringAttr::get(ctx, "argNames");
    auto attr = dict.get(argNamesAttrName);
    usedKeys.insert(argNamesAttrName);
    if (attr || /*isRequired=*/true) {
      if (!attr) {
        emitError() << "expected key entry for argNames in DictionaryAttr to set "
                   "Properties.";
        return ::mlir::failure();
      }
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `argNames` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  {

    auto &propStorage = prop.arg_attrs;
    auto arg_attrsAttrName = ::mlir::StringAttr::get(ctx, "arg_attrs");
    auto attr = dict.get(arg_attrsAttrName);
    usedKeys.insert(arg_attrsAttrName);
    if (attr || /*isRequired=*/false) {
      if (!attr) {
        emitError() << "expected key entry for arg_attrs in DictionaryAttr to set "
                   "Properties.";
        return ::mlir::failure();
      }
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `arg_attrs` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  {

    auto &propStorage = prop.res_attrs;
    auto res_attrsAttrName = ::mlir::StringAttr::get(ctx, "res_attrs");
    auto attr = dict.get(res_attrsAttrName);
    usedKeys.insert(res_attrsAttrName);
    if (attr || /*isRequired=*/false) {
      if (!attr) {
        emitError() << "expected key entry for res_attrs in DictionaryAttr to set "
                   "Properties.";
        return ::mlir::failure();
      }
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `res_attrs` in property conversion: " << attr;
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

// For hw:InnerSymbol - the symbol targets the operation and not any result.
std::optional<size_t> DataflowMethodOp::getTargetResultIndex() {
  return std::nullopt;
}

} // namespace circt::kanagawa
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::kanagawa::DataflowMethodOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::kanagawa::detail::DataflowMethodOpGenericAdaptorBase::Properties)

namespace circt::kanagawa {


//===----------------------------------------------------------------------===//
// ::circt::kanagawa::DesignOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

DesignOpGenericAdaptorBase::DesignOpGenericAdaptorBase(DesignOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::llvm::StringRef DesignOpGenericAdaptorBase::getSymName() {
  auto attr = getSymNameAttr();
  return attr.getValue();
}


} // namespace detail
DesignOpAdaptor::DesignOpAdaptor(DesignOp op) : DesignOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult DesignOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;
  if (!tblgen_sym_name) return emitError(loc, "'kanagawa.design' op requires attribute 'sym_name'");

  if (tblgen_sym_name && !((::llvm::isa<::mlir::StringAttr>(tblgen_sym_name))))
    return emitError(loc, "'kanagawa.design' op attribute 'sym_name' failed to satisfy constraint: string attribute");
  return ::mlir::success();
}

::llvm::LogicalResult DesignOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
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

::mlir::Attribute DesignOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

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

llvm::hash_code DesignOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.sym_name.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> DesignOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "sym_name")
      return prop.sym_name;
  return std::nullopt;
}

void DesignOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "sym_name") {
       prop.sym_name = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.sym_name)>>(value);
       return;
    }
}

void DesignOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.sym_name) attrs.append("sym_name", prop.sym_name);
}

::llvm::LogicalResult DesignOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getSymNameAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Kanagawa3(attr, "sym_name", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult DesignOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.sym_name)))
    return ::mlir::failure();
  return ::mlir::success();
}

void DesignOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.sym_name);
}

::llvm::StringRef DesignOp::getSymName() {
  auto attr = getSymNameAttr();
  return attr.getValue();
}

void DesignOp::setSymName(::llvm::StringRef attrValue) {
  getProperties().sym_name = ::mlir::Builder((*this)->getContext()).getStringAttr(attrValue);
}

void DesignOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::StringAttr sym_name) {
  odsState.getOrAddProperties<Properties>().sym_name = sym_name;
  (void)odsState.addRegion();
}

DesignOp DesignOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::StringAttr sym_name) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(sym_name)>(sym_name));
  auto __res__ = ::llvm::dyn_cast<DesignOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

DesignOp DesignOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::StringAttr sym_name) {
  return create(builder, builder.getLoc(), std::forward<decltype(sym_name)>(sym_name));
}

void DesignOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name) {
  odsState.getOrAddProperties<Properties>().sym_name = sym_name;
  (void)odsState.addRegion();
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

DesignOp DesignOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(sym_name)>(sym_name));
  auto __res__ = ::llvm::dyn_cast<DesignOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

DesignOp DesignOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(sym_name)>(sym_name));
}

void DesignOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::llvm::StringRef sym_name) {
  odsState.getOrAddProperties<Properties>().sym_name = odsBuilder.getStringAttr(sym_name);
  (void)odsState.addRegion();
}

DesignOp DesignOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::llvm::StringRef sym_name) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(sym_name)>(sym_name));
  auto __res__ = ::llvm::dyn_cast<DesignOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

DesignOp DesignOp::create(::mlir::ImplicitLocOpBuilder &builder, ::llvm::StringRef sym_name) {
  return create(builder, builder.getLoc(), std::forward<decltype(sym_name)>(sym_name));
}

void DesignOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name) {
  odsState.getOrAddProperties<Properties>().sym_name = odsBuilder.getStringAttr(sym_name);
  (void)odsState.addRegion();
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

DesignOp DesignOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(sym_name)>(sym_name));
  auto __res__ = ::llvm::dyn_cast<DesignOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

DesignOp DesignOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(sym_name)>(sym_name));
}

void DesignOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  for (unsigned i = 0; i != 1; ++i)
    (void)odsState.addRegion();
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<DesignOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

DesignOp DesignOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<DesignOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

DesignOp DesignOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void DesignOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  for (unsigned i = 0; i != 1; ++i)
    (void)odsState.addRegion();
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

DesignOp DesignOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<DesignOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

DesignOp DesignOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult DesignOp::verifyInvariantsImpl() {
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;
  if (!tblgen_sym_name) return emitOpError("requires attribute 'sym_name'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Kanagawa3(*this, tblgen_sym_name, "sym_name")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;

    for (auto &region : ::llvm::MutableArrayRef((*this)->getRegion(0)))
      if (::mlir::failed(__mlir_ods_local_region_constraint_Kanagawa1(*this, region, "body", index++)))
        return ::mlir::failure();
  }
  return ::mlir::success();
}

::llvm::LogicalResult DesignOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult DesignOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::StringAttr sym_nameAttr;
  std::unique_ptr<::mlir::Region> bodyRegion = std::make_unique<::mlir::Region>();

  if (parser.parseSymbolName(sym_nameAttr))
    return ::mlir::failure();
  if (sym_nameAttr) result.getOrAddProperties<DesignOp::Properties>().sym_name = sym_nameAttr;
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

void DesignOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter.printSymbolName(getSymNameAttr().getValue());
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("sym_name");
  _odsPrinter.printOptionalAttrDictWithKeyword((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ';
  _odsPrinter.printRegion(getBody());
}


} // namespace circt::kanagawa
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::kanagawa::DesignOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::kanagawa::detail::DesignOpGenericAdaptorBase::Properties)

namespace circt::kanagawa {


//===----------------------------------------------------------------------===//
// ::circt::kanagawa::GetPortOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

GetPortOpGenericAdaptorBase::GetPortOpGenericAdaptorBase(GetPortOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::llvm::StringRef GetPortOpGenericAdaptorBase::getPortSymbol() {
  auto attr = getPortSymbolAttr();
  return attr.getValue();
}


} // namespace detail
GetPortOpAdaptor::GetPortOpAdaptor(GetPortOp op) : GetPortOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult GetPortOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_portSymbol = getProperties().portSymbol; (void)tblgen_portSymbol;
  if (!tblgen_portSymbol) return emitError(loc, "'kanagawa.get_port' op requires attribute 'portSymbol'");

  if (tblgen_portSymbol && !((::llvm::isa<::mlir::FlatSymbolRefAttr>(tblgen_portSymbol))))
    return emitError(loc, "'kanagawa.get_port' op attribute 'portSymbol' failed to satisfy constraint: flat symbol reference attribute");
  return ::mlir::success();
}

::llvm::LogicalResult GetPortOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.portSymbol;
       auto attr = dict.get("portSymbol");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `portSymbol` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  return ::mlir::success();
}

::mlir::Attribute GetPortOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.portSymbol;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("portSymbol",
                                       propStorage));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code GetPortOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.portSymbol.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> GetPortOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "portSymbol")
      return prop.portSymbol;
  return std::nullopt;
}

void GetPortOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "portSymbol") {
       prop.portSymbol = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.portSymbol)>>(value);
       return;
    }
}

void GetPortOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.portSymbol) attrs.append("portSymbol", prop.portSymbol);
}

::llvm::LogicalResult GetPortOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getPortSymbolAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Kanagawa9(attr, "portSymbol", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult GetPortOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.portSymbol)))
    return ::mlir::failure();
  return ::mlir::success();
}

void GetPortOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.portSymbol);
}

::llvm::StringRef GetPortOp::getPortSymbol() {
  auto attr = getPortSymbolAttr();
  return attr.getValue();
}

void GetPortOp::setPortSymbol(::llvm::StringRef attrValue) {
  getProperties().portSymbol = ::mlir::SymbolRefAttr::get(::mlir::Builder((*this)->getContext()).getContext(), attrValue);
}

void GetPortOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value instance, StringAttr portName, Type innerPortType, kanagawa::Direction direction) {
      build(odsBuilder, odsState, odsBuilder.getType<PortRefType>(
        innerPortType, direction), instance, portName
      );
    
}

GetPortOp GetPortOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, Value instance, StringAttr portName, Type innerPortType, kanagawa::Direction direction) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(instance)>(instance), std::forward<decltype(portName)>(portName), std::forward<decltype(innerPortType)>(innerPortType), std::forward<decltype(direction)>(direction));
  auto __res__ = ::llvm::dyn_cast<GetPortOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

GetPortOp GetPortOp::create(::mlir::ImplicitLocOpBuilder &builder, Value instance, StringAttr portName, Type innerPortType, kanagawa::Direction direction) {
  return create(builder, builder.getLoc(), std::forward<decltype(instance)>(instance), std::forward<decltype(portName)>(portName), std::forward<decltype(innerPortType)>(innerPortType), std::forward<decltype(direction)>(direction));
}

void GetPortOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type port, ::mlir::Value instance, ::mlir::FlatSymbolRefAttr portSymbol) {
  odsState.addOperands(instance);
  odsState.getOrAddProperties<Properties>().portSymbol = portSymbol;
  odsState.addTypes(port);
}

GetPortOp GetPortOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type port, ::mlir::Value instance, ::mlir::FlatSymbolRefAttr portSymbol) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(port)>(port), std::forward<decltype(instance)>(instance), std::forward<decltype(portSymbol)>(portSymbol));
  auto __res__ = ::llvm::dyn_cast<GetPortOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

GetPortOp GetPortOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type port, ::mlir::Value instance, ::mlir::FlatSymbolRefAttr portSymbol) {
  return create(builder, builder.getLoc(), std::forward<decltype(port)>(port), std::forward<decltype(instance)>(instance), std::forward<decltype(portSymbol)>(portSymbol));
}

void GetPortOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value instance, ::mlir::FlatSymbolRefAttr portSymbol) {
  odsState.addOperands(instance);
  odsState.getOrAddProperties<Properties>().portSymbol = portSymbol;
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

GetPortOp GetPortOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value instance, ::mlir::FlatSymbolRefAttr portSymbol) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(instance)>(instance), std::forward<decltype(portSymbol)>(portSymbol));
  auto __res__ = ::llvm::dyn_cast<GetPortOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

GetPortOp GetPortOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value instance, ::mlir::FlatSymbolRefAttr portSymbol) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(instance)>(instance), std::forward<decltype(portSymbol)>(portSymbol));
}

void GetPortOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type port, ::mlir::Value instance, ::llvm::StringRef portSymbol) {
  odsState.addOperands(instance);
  odsState.getOrAddProperties<Properties>().portSymbol = ::mlir::SymbolRefAttr::get(odsBuilder.getContext(), portSymbol);
  odsState.addTypes(port);
}

GetPortOp GetPortOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type port, ::mlir::Value instance, ::llvm::StringRef portSymbol) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(port)>(port), std::forward<decltype(instance)>(instance), std::forward<decltype(portSymbol)>(portSymbol));
  auto __res__ = ::llvm::dyn_cast<GetPortOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

GetPortOp GetPortOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type port, ::mlir::Value instance, ::llvm::StringRef portSymbol) {
  return create(builder, builder.getLoc(), std::forward<decltype(port)>(port), std::forward<decltype(instance)>(instance), std::forward<decltype(portSymbol)>(portSymbol));
}

void GetPortOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value instance, ::llvm::StringRef portSymbol) {
  odsState.addOperands(instance);
  odsState.getOrAddProperties<Properties>().portSymbol = ::mlir::SymbolRefAttr::get(odsBuilder.getContext(), portSymbol);
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

GetPortOp GetPortOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value instance, ::llvm::StringRef portSymbol) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(instance)>(instance), std::forward<decltype(portSymbol)>(portSymbol));
  auto __res__ = ::llvm::dyn_cast<GetPortOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

GetPortOp GetPortOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value instance, ::llvm::StringRef portSymbol) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(instance)>(instance), std::forward<decltype(portSymbol)>(portSymbol));
}

void GetPortOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<GetPortOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

GetPortOp GetPortOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<GetPortOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

GetPortOp GetPortOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void GetPortOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

GetPortOp GetPortOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<GetPortOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

GetPortOp GetPortOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult GetPortOp::verifyInvariantsImpl() {
  auto tblgen_portSymbol = getProperties().portSymbol; (void)tblgen_portSymbol;
  if (!tblgen_portSymbol) return emitOpError("requires attribute 'portSymbol'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Kanagawa9(*this, tblgen_portSymbol, "portSymbol")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Kanagawa2(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Kanagawa3(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult GetPortOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult GetPortOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::OpAsmParser::UnresolvedOperand instanceRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> instanceOperands(&instanceRawOperand, 1);  ::llvm::SMLoc instanceOperandsLoc;
  (void)instanceOperandsLoc;
  ::mlir::FlatSymbolRefAttr portSymbolAttr;
  ::mlir::Type instanceRawType{};
  ::llvm::ArrayRef<::mlir::Type> instanceTypes(&instanceRawType, 1);
  ::mlir::Type portRawType{};
  ::llvm::ArrayRef<::mlir::Type> portTypes(&portRawType, 1);

  instanceOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(instanceRawOperand))
    return ::mlir::failure();
  if (parser.parseComma())
    return ::mlir::failure();

  if (parser.parseCustomAttributeWithFallback(portSymbolAttr, parser.getBuilder().getType<::mlir::NoneType>())) {
    return ::mlir::failure();
  }
  if (portSymbolAttr) result.getOrAddProperties<GetPortOp::Properties>().portSymbol = portSymbolAttr;
  if (parser.parseColon())
    return ::mlir::failure();

  if (parser.parseType(instanceRawType))
    return ::mlir::failure();
  if (parser.parseArrow())
    return ::mlir::failure();

  if (parser.parseType(portRawType))
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
  result.addTypes(portTypes);
  if (parser.resolveOperands(instanceOperands, instanceTypes, instanceOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void GetPortOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter << getInstance();
  _odsPrinter << ",";
  _odsPrinter << ' ';
  _odsPrinter.printAttributeWithoutType(getPortSymbolAttr());
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
   _odsPrinter << getInstance().getType();
  _odsPrinter << ' ' << "->";
  _odsPrinter << ' ';
   _odsPrinter << getPort().getType();
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("portSymbol");
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
}

void GetPortOp::getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects) {
}


} // namespace circt::kanagawa
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::kanagawa::GetPortOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::kanagawa::detail::GetPortOpGenericAdaptorBase::Properties)

namespace circt::kanagawa {


//===----------------------------------------------------------------------===//
// ::circt::kanagawa::GetVarOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

GetVarOpGenericAdaptorBase::GetVarOpGenericAdaptorBase(GetVarOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::llvm::StringRef GetVarOpGenericAdaptorBase::getVarName() {
  auto attr = getVarNameAttr();
  return attr.getValue();
}


} // namespace detail
GetVarOpAdaptor::GetVarOpAdaptor(GetVarOp op) : GetVarOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult GetVarOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_varName = getProperties().varName; (void)tblgen_varName;
  if (!tblgen_varName) return emitError(loc, "'kanagawa.get_var' op requires attribute 'varName'");

  if (tblgen_varName && !((::llvm::isa<::mlir::FlatSymbolRefAttr>(tblgen_varName))))
    return emitError(loc, "'kanagawa.get_var' op attribute 'varName' failed to satisfy constraint: flat symbol reference attribute");
  return ::mlir::success();
}

::llvm::LogicalResult GetVarOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.varName;
       auto attr = dict.get("varName");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `varName` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  return ::mlir::success();
}

::mlir::Attribute GetVarOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.varName;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("varName",
                                       propStorage));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code GetVarOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.varName.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> GetVarOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "varName")
      return prop.varName;
  return std::nullopt;
}

void GetVarOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "varName") {
       prop.varName = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.varName)>>(value);
       return;
    }
}

void GetVarOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.varName) attrs.append("varName", prop.varName);
}

::llvm::LogicalResult GetVarOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getVarNameAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Kanagawa9(attr, "varName", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult GetVarOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.varName)))
    return ::mlir::failure();
  return ::mlir::success();
}

void GetVarOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.varName);
}

::llvm::StringRef GetVarOp::getVarName() {
  auto attr = getVarNameAttr();
  return attr.getValue();
}

void GetVarOp::setVarName(::llvm::StringRef attrValue) {
  getProperties().varName = ::mlir::SymbolRefAttr::get(::mlir::Builder((*this)->getContext()).getContext(), attrValue);
}

void GetVarOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type var, ::mlir::Value instance, ::mlir::FlatSymbolRefAttr varName) {
  odsState.addOperands(instance);
  odsState.getOrAddProperties<Properties>().varName = varName;
  odsState.addTypes(var);
}

GetVarOp GetVarOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type var, ::mlir::Value instance, ::mlir::FlatSymbolRefAttr varName) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(var)>(var), std::forward<decltype(instance)>(instance), std::forward<decltype(varName)>(varName));
  auto __res__ = ::llvm::dyn_cast<GetVarOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

GetVarOp GetVarOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type var, ::mlir::Value instance, ::mlir::FlatSymbolRefAttr varName) {
  return create(builder, builder.getLoc(), std::forward<decltype(var)>(var), std::forward<decltype(instance)>(instance), std::forward<decltype(varName)>(varName));
}

void GetVarOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value instance, ::mlir::FlatSymbolRefAttr varName) {
  odsState.addOperands(instance);
  odsState.getOrAddProperties<Properties>().varName = varName;
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

GetVarOp GetVarOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value instance, ::mlir::FlatSymbolRefAttr varName) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(instance)>(instance), std::forward<decltype(varName)>(varName));
  auto __res__ = ::llvm::dyn_cast<GetVarOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

GetVarOp GetVarOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value instance, ::mlir::FlatSymbolRefAttr varName) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(instance)>(instance), std::forward<decltype(varName)>(varName));
}

void GetVarOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type var, ::mlir::Value instance, ::llvm::StringRef varName) {
  odsState.addOperands(instance);
  odsState.getOrAddProperties<Properties>().varName = ::mlir::SymbolRefAttr::get(odsBuilder.getContext(), varName);
  odsState.addTypes(var);
}

GetVarOp GetVarOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type var, ::mlir::Value instance, ::llvm::StringRef varName) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(var)>(var), std::forward<decltype(instance)>(instance), std::forward<decltype(varName)>(varName));
  auto __res__ = ::llvm::dyn_cast<GetVarOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

GetVarOp GetVarOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type var, ::mlir::Value instance, ::llvm::StringRef varName) {
  return create(builder, builder.getLoc(), std::forward<decltype(var)>(var), std::forward<decltype(instance)>(instance), std::forward<decltype(varName)>(varName));
}

void GetVarOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value instance, ::llvm::StringRef varName) {
  odsState.addOperands(instance);
  odsState.getOrAddProperties<Properties>().varName = ::mlir::SymbolRefAttr::get(odsBuilder.getContext(), varName);
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

GetVarOp GetVarOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value instance, ::llvm::StringRef varName) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(instance)>(instance), std::forward<decltype(varName)>(varName));
  auto __res__ = ::llvm::dyn_cast<GetVarOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

GetVarOp GetVarOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value instance, ::llvm::StringRef varName) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(instance)>(instance), std::forward<decltype(varName)>(varName));
}

void GetVarOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<GetVarOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

GetVarOp GetVarOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<GetVarOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

GetVarOp GetVarOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void GetVarOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

GetVarOp GetVarOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<GetVarOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

GetVarOp GetVarOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult GetVarOp::verifyInvariantsImpl() {
  auto tblgen_varName = getProperties().varName; (void)tblgen_varName;
  if (!tblgen_varName) return emitOpError("requires attribute 'varName'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Kanagawa9(*this, tblgen_varName, "varName")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Kanagawa2(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Kanagawa4(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult GetVarOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult GetVarOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::OpAsmParser::UnresolvedOperand instanceRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> instanceOperands(&instanceRawOperand, 1);  ::llvm::SMLoc instanceOperandsLoc;
  (void)instanceOperandsLoc;
  ::mlir::FlatSymbolRefAttr varNameAttr;
  ::mlir::Type instanceRawType{};
  ::llvm::ArrayRef<::mlir::Type> instanceTypes(&instanceRawType, 1);
  ::mlir::Type varRawType{};
  ::llvm::ArrayRef<::mlir::Type> varTypes(&varRawType, 1);

  instanceOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(instanceRawOperand))
    return ::mlir::failure();
  if (parser.parseComma())
    return ::mlir::failure();

  if (parser.parseCustomAttributeWithFallback(varNameAttr, parser.getBuilder().getType<::mlir::NoneType>())) {
    return ::mlir::failure();
  }
  if (varNameAttr) result.getOrAddProperties<GetVarOp::Properties>().varName = varNameAttr;
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

  if (parser.parseType(instanceRawType))
    return ::mlir::failure();
  if (parser.parseArrow())
    return ::mlir::failure();

  if (parser.parseType(varRawType))
    return ::mlir::failure();
  result.addTypes(varTypes);
  if (parser.resolveOperands(instanceOperands, instanceTypes, instanceOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void GetVarOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter << getInstance();
  _odsPrinter << ",";
  _odsPrinter << ' ';
  _odsPrinter.printAttributeWithoutType(getVarNameAttr());
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("varName");
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
   _odsPrinter << getInstance().getType();
  _odsPrinter << ' ' << "->";
  _odsPrinter << ' ';
   _odsPrinter << getVar().getType();
}

void GetVarOp::getAsmResultNames(OpAsmSetValueNameFn setNameFn) {
  setNameFn(getResult(), getVarName());
}

} // namespace circt::kanagawa
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::kanagawa::GetVarOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::kanagawa::detail::GetVarOpGenericAdaptorBase::Properties)

namespace circt::kanagawa {


//===----------------------------------------------------------------------===//
// ::circt::kanagawa::InlineStaticBlockBeginOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

InlineStaticBlockBeginOpGenericAdaptorBase::InlineStaticBlockBeginOpGenericAdaptorBase(InlineStaticBlockBeginOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}


} // namespace detail
InlineStaticBlockBeginOpAdaptor::InlineStaticBlockBeginOpAdaptor(InlineStaticBlockBeginOp op) : InlineStaticBlockBeginOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult InlineStaticBlockBeginOpAdaptor::verify(::mlir::Location loc) {
  return ::mlir::success();
}

::llvm::LogicalResult InlineStaticBlockBeginOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }
      return ::mlir::success();
}

::mlir::Attribute InlineStaticBlockBeginOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code InlineStaticBlockBeginOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine();
}

std::optional<mlir::Attribute> InlineStaticBlockBeginOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
  return std::nullopt;
}

void InlineStaticBlockBeginOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
}

void InlineStaticBlockBeginOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
}

::llvm::LogicalResult InlineStaticBlockBeginOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    return ::mlir::success();
}

void InlineStaticBlockBeginOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState) {
}

InlineStaticBlockBeginOp InlineStaticBlockBeginOp::create(::mlir::OpBuilder &builder, ::mlir::Location location) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__);
  auto __res__ = ::llvm::dyn_cast<InlineStaticBlockBeginOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

InlineStaticBlockBeginOp InlineStaticBlockBeginOp::create(::mlir::ImplicitLocOpBuilder &builder) {
  return create(builder, builder.getLoc());
}

void InlineStaticBlockBeginOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes) {
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

InlineStaticBlockBeginOp InlineStaticBlockBeginOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes));
  auto __res__ = ::llvm::dyn_cast<InlineStaticBlockBeginOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

InlineStaticBlockBeginOp InlineStaticBlockBeginOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes));
}

void InlineStaticBlockBeginOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

InlineStaticBlockBeginOp InlineStaticBlockBeginOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<InlineStaticBlockBeginOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

InlineStaticBlockBeginOp InlineStaticBlockBeginOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void InlineStaticBlockBeginOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

InlineStaticBlockBeginOp InlineStaticBlockBeginOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<InlineStaticBlockBeginOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

InlineStaticBlockBeginOp InlineStaticBlockBeginOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult InlineStaticBlockBeginOp::verifyInvariantsImpl() {
  return ::mlir::success();
}

::llvm::LogicalResult InlineStaticBlockBeginOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult InlineStaticBlockBeginOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  {
    auto loc = parser.getCurrentLocation();(void)loc;
    if (parser.parseOptionalAttrDict(result.attributes))
      return ::mlir::failure();
    if (failed(verifyInherentAttrs(result.name, result.attributes, [&]() {
        return parser.emitError(loc) << "'" << result.name.getStringRef() << "' op ";
      })))
      return ::mlir::failure();
  }
  return ::mlir::success();
}

void InlineStaticBlockBeginOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
}


} // namespace circt::kanagawa
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::kanagawa::InlineStaticBlockBeginOp)

namespace circt::kanagawa {


//===----------------------------------------------------------------------===//
// ::circt::kanagawa::InlineStaticBlockEndOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

InlineStaticBlockEndOpGenericAdaptorBase::InlineStaticBlockEndOpGenericAdaptorBase(InlineStaticBlockEndOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}


} // namespace detail
InlineStaticBlockEndOpAdaptor::InlineStaticBlockEndOpAdaptor(InlineStaticBlockEndOp op) : InlineStaticBlockEndOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult InlineStaticBlockEndOpAdaptor::verify(::mlir::Location loc) {
  return ::mlir::success();
}

::llvm::LogicalResult InlineStaticBlockEndOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }
      return ::mlir::success();
}

::mlir::Attribute InlineStaticBlockEndOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code InlineStaticBlockEndOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine();
}

std::optional<mlir::Attribute> InlineStaticBlockEndOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
  return std::nullopt;
}

void InlineStaticBlockEndOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
}

void InlineStaticBlockEndOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
}

::llvm::LogicalResult InlineStaticBlockEndOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    return ::mlir::success();
}

void InlineStaticBlockEndOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState) {
}

InlineStaticBlockEndOp InlineStaticBlockEndOp::create(::mlir::OpBuilder &builder, ::mlir::Location location) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__);
  auto __res__ = ::llvm::dyn_cast<InlineStaticBlockEndOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

InlineStaticBlockEndOp InlineStaticBlockEndOp::create(::mlir::ImplicitLocOpBuilder &builder) {
  return create(builder, builder.getLoc());
}

void InlineStaticBlockEndOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes) {
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

InlineStaticBlockEndOp InlineStaticBlockEndOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes));
  auto __res__ = ::llvm::dyn_cast<InlineStaticBlockEndOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

InlineStaticBlockEndOp InlineStaticBlockEndOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes));
}

void InlineStaticBlockEndOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

InlineStaticBlockEndOp InlineStaticBlockEndOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<InlineStaticBlockEndOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

InlineStaticBlockEndOp InlineStaticBlockEndOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void InlineStaticBlockEndOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

InlineStaticBlockEndOp InlineStaticBlockEndOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<InlineStaticBlockEndOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

InlineStaticBlockEndOp InlineStaticBlockEndOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult InlineStaticBlockEndOp::verifyInvariantsImpl() {
  return ::mlir::success();
}

::llvm::LogicalResult InlineStaticBlockEndOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult InlineStaticBlockEndOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  {
    auto loc = parser.getCurrentLocation();(void)loc;
    if (parser.parseOptionalAttrDict(result.attributes))
      return ::mlir::failure();
    if (failed(verifyInherentAttrs(result.name, result.attributes, [&]() {
        return parser.emitError(loc) << "'" << result.name.getStringRef() << "' op ";
      })))
      return ::mlir::failure();
  }
  return ::mlir::success();
}

void InlineStaticBlockEndOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
}


} // namespace circt::kanagawa
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::kanagawa::InlineStaticBlockEndOp)

namespace circt::kanagawa {


//===----------------------------------------------------------------------===//
// ::circt::kanagawa::InputPortOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

InputPortOpGenericAdaptorBase::InputPortOpGenericAdaptorBase(InputPortOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::circt::hw::InnerSymAttr InputPortOpGenericAdaptorBase::getInnerSym() {
  auto attr = getInnerSymAttr();
  return ::llvm::cast<::circt::hw::InnerSymAttr>(attr);
}

::mlir::Type InputPortOpGenericAdaptorBase::getType() {
  auto attr = getTypeAttr();
  return ::llvm::cast<::mlir::Type>(attr.getValue());
}

::std::optional< ::llvm::StringRef > InputPortOpGenericAdaptorBase::getName() {
  auto attr = getNameAttr();
  return attr ? ::std::optional< ::llvm::StringRef >(attr.getValue()) : (::std::nullopt);
}


} // namespace detail
InputPortOpAdaptor::InputPortOpAdaptor(InputPortOp op) : InputPortOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult InputPortOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_inner_sym = getProperties().inner_sym; (void)tblgen_inner_sym;
  if (!tblgen_inner_sym) return emitError(loc, "'kanagawa.port.input' op requires attribute 'inner_sym'");
  auto tblgen_name = getProperties().name; (void)tblgen_name;
  auto tblgen_type = getProperties().type; (void)tblgen_type;
  if (!tblgen_type) return emitError(loc, "'kanagawa.port.input' op requires attribute 'type'");

  if (tblgen_inner_sym && !((::llvm::isa<::circt::hw::InnerSymAttr>(tblgen_inner_sym))))
    return emitError(loc, "'kanagawa.port.input' op attribute 'inner_sym' failed to satisfy constraint: Inner symbol definition");

  if (tblgen_type && !(((::llvm::isa<::mlir::TypeAttr>(tblgen_type))) && ((::llvm::isa<::mlir::Type>(::llvm::cast<::mlir::TypeAttr>(tblgen_type).getValue()))) && (!((::llvm::isa<::mlir::TokenType>(::llvm::cast<::mlir::TypeAttr>(tblgen_type).getValue()))))))
    return emitError(loc, "'kanagawa.port.input' op attribute 'type' failed to satisfy constraint: type attribute of any non-token type");

  if (tblgen_name && !((::llvm::isa<::mlir::StringAttr>(tblgen_name))))
    return emitError(loc, "'kanagawa.port.input' op attribute 'name' failed to satisfy constraint: string attribute");
  return ::mlir::success();
}

::llvm::LogicalResult InputPortOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.inner_sym;
       auto attr = dict.get("inner_sym");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `inner_sym` in property conversion: " << attr;
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
    auto &propStorage = prop.type;
       auto attr = dict.get("type");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `type` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  return ::mlir::success();
}

::mlir::Attribute InputPortOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.inner_sym;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("inner_sym",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.name;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("name",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.type;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("type",
                                       propStorage));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code InputPortOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.inner_sym.getAsOpaquePointer()), 
    llvm::hash_value(prop.name.getAsOpaquePointer()), 
    llvm::hash_value(prop.type.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> InputPortOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "inner_sym")
      return prop.inner_sym;

    if (name == "name")
      return prop.name;

    if (name == "type")
      return prop.type;
  return std::nullopt;
}

void InputPortOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "inner_sym") {
       prop.inner_sym = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.inner_sym)>>(value);
       return;
    }

    if (name == "name") {
       prop.name = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.name)>>(value);
       return;
    }

    if (name == "type") {
       prop.type = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.type)>>(value);
       return;
    }
}

void InputPortOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.inner_sym) attrs.append("inner_sym", prop.inner_sym);

    if (prop.name) attrs.append("name", prop.name);

    if (prop.type) attrs.append("type", prop.type);
}

::llvm::LogicalResult InputPortOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getInnerSymAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Kanagawa2(attr, "inner_sym", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getNameAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Kanagawa3(attr, "name", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getTypeAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Kanagawa10(attr, "type", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult InputPortOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.inner_sym)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readOptionalAttribute(prop.name)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readAttribute(prop.type)))
    return ::mlir::failure();
  return ::mlir::success();
}

void InputPortOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.inner_sym);

  writer.writeOptionalAttribute(prop.name);
  writer.writeAttribute(prop.type);
}

::circt::hw::InnerSymAttr InputPortOp::getInnerSym() {
  auto attr = getInnerSymAttr();
  return ::llvm::cast<::circt::hw::InnerSymAttr>(attr);
}

::mlir::Type InputPortOp::getType() {
  auto attr = getTypeAttr();
  return ::llvm::cast<::mlir::Type>(attr.getValue());
}

::std::optional< ::llvm::StringRef > InputPortOp::getName() {
  auto attr = getNameAttr();
  return attr ? ::std::optional< ::llvm::StringRef >(attr.getValue()) : (::std::nullopt);
}

void InputPortOp::setType(::mlir::Type attrValue) {
  getProperties().type = ::mlir::TypeAttr::get(attrValue);
}

void InputPortOp::setName(::std::optional<::llvm::StringRef> attrValue) {
    auto &odsProp = getProperties().name;
    if (attrValue)
      odsProp = ::mlir::Builder((*this)->getContext()).getStringAttr(*attrValue);
    else
      odsProp = nullptr;
}

void InputPortOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type port, ::circt::hw::InnerSymAttr inner_sym, ::mlir::TypeAttr type, /*optional*/::mlir::StringAttr name) {
  odsState.getOrAddProperties<Properties>().inner_sym = inner_sym;
  odsState.getOrAddProperties<Properties>().type = type;
  if (name) {
    odsState.getOrAddProperties<Properties>().name = name;
  }
  odsState.addTypes(port);
}

InputPortOp InputPortOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type port, ::circt::hw::InnerSymAttr inner_sym, ::mlir::TypeAttr type, /*optional*/::mlir::StringAttr name) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(port)>(port), std::forward<decltype(inner_sym)>(inner_sym), std::forward<decltype(type)>(type), std::forward<decltype(name)>(name));
  auto __res__ = ::llvm::dyn_cast<InputPortOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

InputPortOp InputPortOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type port, ::circt::hw::InnerSymAttr inner_sym, ::mlir::TypeAttr type, /*optional*/::mlir::StringAttr name) {
  return create(builder, builder.getLoc(), std::forward<decltype(port)>(port), std::forward<decltype(inner_sym)>(inner_sym), std::forward<decltype(type)>(type), std::forward<decltype(name)>(name));
}

void InputPortOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::circt::hw::InnerSymAttr inner_sym, ::mlir::TypeAttr type, /*optional*/::mlir::StringAttr name) {
  odsState.getOrAddProperties<Properties>().inner_sym = inner_sym;
  odsState.getOrAddProperties<Properties>().type = type;
  if (name) {
    odsState.getOrAddProperties<Properties>().name = name;
  }

        ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
        if (::mlir::succeeded(InputPortOp::inferReturnTypes(odsBuilder.getContext(),
                      odsState.location, odsState.operands,
                      odsState.attributes.getDictionary(odsState.getContext()),
                      odsState.getRawProperties(),
                      odsState.regions, inferredReturnTypes)))
          odsState.addTypes(inferredReturnTypes);
        else
          ::mlir::detail::reportFatalInferReturnTypesError(odsState);
        
}

InputPortOp InputPortOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::circt::hw::InnerSymAttr inner_sym, ::mlir::TypeAttr type, /*optional*/::mlir::StringAttr name) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(inner_sym)>(inner_sym), std::forward<decltype(type)>(type), std::forward<decltype(name)>(name));
  auto __res__ = ::llvm::dyn_cast<InputPortOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

InputPortOp InputPortOp::create(::mlir::ImplicitLocOpBuilder &builder, ::circt::hw::InnerSymAttr inner_sym, ::mlir::TypeAttr type, /*optional*/::mlir::StringAttr name) {
  return create(builder, builder.getLoc(), std::forward<decltype(inner_sym)>(inner_sym), std::forward<decltype(type)>(type), std::forward<decltype(name)>(name));
}

void InputPortOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::circt::hw::InnerSymAttr inner_sym, ::mlir::TypeAttr type, /*optional*/::mlir::StringAttr name) {
  odsState.getOrAddProperties<Properties>().inner_sym = inner_sym;
  odsState.getOrAddProperties<Properties>().type = type;
  if (name) {
    odsState.getOrAddProperties<Properties>().name = name;
  }
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

InputPortOp InputPortOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::circt::hw::InnerSymAttr inner_sym, ::mlir::TypeAttr type, /*optional*/::mlir::StringAttr name) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(inner_sym)>(inner_sym), std::forward<decltype(type)>(type), std::forward<decltype(name)>(name));
  auto __res__ = ::llvm::dyn_cast<InputPortOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

InputPortOp InputPortOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::circt::hw::InnerSymAttr inner_sym, ::mlir::TypeAttr type, /*optional*/::mlir::StringAttr name) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(inner_sym)>(inner_sym), std::forward<decltype(type)>(type), std::forward<decltype(name)>(name));
}

void InputPortOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type port, ::circt::hw::InnerSymAttr inner_sym, ::mlir::Type type, /*optional*/::mlir::StringAttr name) {
  odsState.getOrAddProperties<Properties>().inner_sym = inner_sym;
  odsState.getOrAddProperties<Properties>().type = ::mlir::TypeAttr::get(type);
  if (name) {
    odsState.getOrAddProperties<Properties>().name = name;
  }
  odsState.addTypes(port);
}

InputPortOp InputPortOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type port, ::circt::hw::InnerSymAttr inner_sym, ::mlir::Type type, /*optional*/::mlir::StringAttr name) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(port)>(port), std::forward<decltype(inner_sym)>(inner_sym), std::forward<decltype(type)>(type), std::forward<decltype(name)>(name));
  auto __res__ = ::llvm::dyn_cast<InputPortOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

InputPortOp InputPortOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type port, ::circt::hw::InnerSymAttr inner_sym, ::mlir::Type type, /*optional*/::mlir::StringAttr name) {
  return create(builder, builder.getLoc(), std::forward<decltype(port)>(port), std::forward<decltype(inner_sym)>(inner_sym), std::forward<decltype(type)>(type), std::forward<decltype(name)>(name));
}

void InputPortOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::circt::hw::InnerSymAttr inner_sym, ::mlir::Type type, /*optional*/::mlir::StringAttr name) {
  odsState.getOrAddProperties<Properties>().inner_sym = inner_sym;
  odsState.getOrAddProperties<Properties>().type = ::mlir::TypeAttr::get(type);
  if (name) {
    odsState.getOrAddProperties<Properties>().name = name;
  }

        ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
        if (::mlir::succeeded(InputPortOp::inferReturnTypes(odsBuilder.getContext(),
                      odsState.location, odsState.operands,
                      odsState.attributes.getDictionary(odsState.getContext()),
                      odsState.getRawProperties(),
                      odsState.regions, inferredReturnTypes)))
          odsState.addTypes(inferredReturnTypes);
        else
          ::mlir::detail::reportFatalInferReturnTypesError(odsState);
        
}

InputPortOp InputPortOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::circt::hw::InnerSymAttr inner_sym, ::mlir::Type type, /*optional*/::mlir::StringAttr name) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(inner_sym)>(inner_sym), std::forward<decltype(type)>(type), std::forward<decltype(name)>(name));
  auto __res__ = ::llvm::dyn_cast<InputPortOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

InputPortOp InputPortOp::create(::mlir::ImplicitLocOpBuilder &builder, ::circt::hw::InnerSymAttr inner_sym, ::mlir::Type type, /*optional*/::mlir::StringAttr name) {
  return create(builder, builder.getLoc(), std::forward<decltype(inner_sym)>(inner_sym), std::forward<decltype(type)>(type), std::forward<decltype(name)>(name));
}

void InputPortOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::circt::hw::InnerSymAttr inner_sym, ::mlir::Type type, /*optional*/::mlir::StringAttr name) {
  odsState.getOrAddProperties<Properties>().inner_sym = inner_sym;
  odsState.getOrAddProperties<Properties>().type = ::mlir::TypeAttr::get(type);
  if (name) {
    odsState.getOrAddProperties<Properties>().name = name;
  }
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

InputPortOp InputPortOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::circt::hw::InnerSymAttr inner_sym, ::mlir::Type type, /*optional*/::mlir::StringAttr name) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(inner_sym)>(inner_sym), std::forward<decltype(type)>(type), std::forward<decltype(name)>(name));
  auto __res__ = ::llvm::dyn_cast<InputPortOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

InputPortOp InputPortOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::circt::hw::InnerSymAttr inner_sym, ::mlir::Type type, /*optional*/::mlir::StringAttr name) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(inner_sym)>(inner_sym), std::forward<decltype(type)>(type), std::forward<decltype(name)>(name));
}

void InputPortOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<InputPortOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

InputPortOp InputPortOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<InputPortOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

InputPortOp InputPortOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void InputPortOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<InputPortOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
  ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
  if (::mlir::succeeded(InputPortOp::inferReturnTypes(odsBuilder.getContext(),
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

InputPortOp InputPortOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<InputPortOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

InputPortOp InputPortOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void InputPortOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

InputPortOp InputPortOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<InputPortOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

InputPortOp InputPortOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

void InputPortOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties &>(properties));
  odsState.addAttributes(discardableAttributes);

  ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
  if (::mlir::succeeded(InputPortOp::inferReturnTypes(odsBuilder.getContext(),
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

InputPortOp InputPortOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<InputPortOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

InputPortOp InputPortOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult InputPortOp::verifyInvariantsImpl() {
  auto tblgen_inner_sym = getProperties().inner_sym; (void)tblgen_inner_sym;
  if (!tblgen_inner_sym) return emitOpError("requires attribute 'inner_sym'");
  auto tblgen_name = getProperties().name; (void)tblgen_name;
  auto tblgen_type = getProperties().type; (void)tblgen_type;
  if (!tblgen_type) return emitOpError("requires attribute 'type'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Kanagawa2(*this, tblgen_inner_sym, "inner_sym")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Kanagawa10(*this, tblgen_type, "type")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Kanagawa3(*this, tblgen_name, "name")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Kanagawa3(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult InputPortOp::verifyInvariants() {
  if(::mlir::succeeded(verifyInvariantsImpl()) && ::mlir::succeeded(verify()))
    return ::mlir::success();
  return ::mlir::failure();
}

::mlir::ParseResult InputPortOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::StringAttr nameAttr;
  ::circt::hw::InnerSymAttr inner_symAttr;
  ::mlir::TypeAttr typeAttr;

  ::mlir::OptionalParseResult parseResultnameAttr =
    parser.parseOptionalAttribute(nameAttr, parser.getBuilder().getType<::mlir::NoneType>());
  if (parseResultnameAttr.has_value() && failed(*parseResultnameAttr))
    return ::mlir::failure();
  if (parseResultnameAttr.has_value() && succeeded(*parseResultnameAttr))
  if (nameAttr) result.getOrAddProperties<InputPortOp::Properties>().name = nameAttr;
  if (nameAttr) {
  }
  if (parser.parseKeyword("sym"))
    return ::mlir::failure();

  if (parser.parseCustomAttributeWithFallback(inner_symAttr, ::mlir::Type{})) {
    return ::mlir::failure();
  }
  if (inner_symAttr) result.getOrAddProperties<InputPortOp::Properties>().inner_sym = inner_symAttr;
  if (parser.parseColon())
    return ::mlir::failure();

  if (parser.parseCustomAttributeWithFallback(typeAttr, parser.getBuilder().getType<::mlir::NoneType>())) {
    return ::mlir::failure();
  }
  if (typeAttr) result.getOrAddProperties<InputPortOp::Properties>().type = typeAttr;
  {
    auto loc = parser.getCurrentLocation();(void)loc;
    if (parser.parseOptionalAttrDict(result.attributes))
      return ::mlir::failure();
    if (failed(verifyInherentAttrs(result.name, result.attributes, [&]() {
        return parser.emitError(loc) << "'" << result.name.getStringRef() << "' op ";
      })))
      return ::mlir::failure();
  }

  ::llvm::SmallVector<::mlir::Type> inferredReturnTypes;
  if (::mlir::failed(InputPortOp::inferReturnTypes(parser.getContext(),
      result.location, result.operands,
      result.attributes.getDictionary(parser.getContext()),
      result.getRawProperties(),
      result.regions, inferredReturnTypes)))
    return ::mlir::failure();
  result.addTypes(inferredReturnTypes);
  return ::mlir::success();
}

void InputPortOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  if (getNameAttr()) {
    _odsPrinter << ' ';
    _odsPrinter.printAttributeWithoutType(getNameAttr());
  }
  _odsPrinter << ' ' << "sym";
  _odsPrinter << ' ';
_odsPrinter.printStrippedAttrOrType(getInnerSymAttr());
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
  _odsPrinter.printAttributeWithoutType(getTypeAttr());
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("name");
  elidedAttrs.push_back("inner_sym");
  elidedAttrs.push_back("type");
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
}

kanagawa::Direction InputPortOp::getPortDirection() {
  return kanagawa::Direction::Input;
}

LogicalResult InputPortOp::verify() {
  if(llvm::isa<ScopeRefType>(getType()))
    return emitOpError("port type cannot be a scope reference");

  return success();
}

} // namespace circt::kanagawa
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::kanagawa::InputPortOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::kanagawa::detail::InputPortOpGenericAdaptorBase::Properties)

namespace circt::kanagawa {


//===----------------------------------------------------------------------===//
// ::circt::kanagawa::InputWireOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

InputWireOpGenericAdaptorBase::InputWireOpGenericAdaptorBase(InputWireOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::circt::hw::InnerSymAttr InputWireOpGenericAdaptorBase::getInnerSym() {
  auto attr = getInnerSymAttr();
  return ::llvm::cast<::circt::hw::InnerSymAttr>(attr);
}

::std::optional< ::llvm::StringRef > InputWireOpGenericAdaptorBase::getName() {
  auto attr = getNameAttr();
  return attr ? ::std::optional< ::llvm::StringRef >(attr.getValue()) : (::std::nullopt);
}


} // namespace detail
InputWireOpAdaptor::InputWireOpAdaptor(InputWireOp op) : InputWireOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult InputWireOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_inner_sym = getProperties().inner_sym; (void)tblgen_inner_sym;
  if (!tblgen_inner_sym) return emitError(loc, "'kanagawa.wire.input' op requires attribute 'inner_sym'");
  auto tblgen_name = getProperties().name; (void)tblgen_name;

  if (tblgen_inner_sym && !((::llvm::isa<::circt::hw::InnerSymAttr>(tblgen_inner_sym))))
    return emitError(loc, "'kanagawa.wire.input' op attribute 'inner_sym' failed to satisfy constraint: Inner symbol definition");

  if (tblgen_name && !((::llvm::isa<::mlir::StringAttr>(tblgen_name))))
    return emitError(loc, "'kanagawa.wire.input' op attribute 'name' failed to satisfy constraint: string attribute");
  return ::mlir::success();
}

::llvm::LogicalResult InputWireOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.inner_sym;
       auto attr = dict.get("inner_sym");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `inner_sym` in property conversion: " << attr;
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
  return ::mlir::success();
}

::mlir::Attribute InputWireOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.inner_sym;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("inner_sym",
                                       propStorage));
    }

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

llvm::hash_code InputWireOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.inner_sym.getAsOpaquePointer()), 
    llvm::hash_value(prop.name.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> InputWireOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "inner_sym")
      return prop.inner_sym;

    if (name == "name")
      return prop.name;
  return std::nullopt;
}

void InputWireOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "inner_sym") {
       prop.inner_sym = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.inner_sym)>>(value);
       return;
    }

    if (name == "name") {
       prop.name = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.name)>>(value);
       return;
    }
}

void InputWireOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.inner_sym) attrs.append("inner_sym", prop.inner_sym);

    if (prop.name) attrs.append("name", prop.name);
}

::llvm::LogicalResult InputWireOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getInnerSymAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Kanagawa2(attr, "inner_sym", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getNameAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Kanagawa3(attr, "name", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult InputWireOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.inner_sym)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readOptionalAttribute(prop.name)))
    return ::mlir::failure();
  return ::mlir::success();
}

void InputWireOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.inner_sym);

  writer.writeOptionalAttribute(prop.name);
}

::circt::hw::InnerSymAttr InputWireOp::getInnerSym() {
  auto attr = getInnerSymAttr();
  return ::llvm::cast<::circt::hw::InnerSymAttr>(attr);
}

::std::optional< ::llvm::StringRef > InputWireOp::getName() {
  auto attr = getNameAttr();
  return attr ? ::std::optional< ::llvm::StringRef >(attr.getValue()) : (::std::nullopt);
}

void InputWireOp::setName(::std::optional<::llvm::StringRef> attrValue) {
    auto &odsProp = getProperties().name;
    if (attrValue)
      odsProp = ::mlir::Builder((*this)->getContext()).getStringAttr(*attrValue);
    else
      odsProp = nullptr;
}

void InputWireOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, StringAttr inner_sym, Type innerPortType, mlir::StringAttr name) {
      build(odsBuilder, odsState,
        {odsBuilder.getType<PortRefType>(
          innerPortType, kanagawa::Direction::Input), innerPortType}, hw::InnerSymAttr::get(inner_sym), name);
    
}

InputWireOp InputWireOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, StringAttr inner_sym, Type innerPortType, mlir::StringAttr name) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(inner_sym)>(inner_sym), std::forward<decltype(innerPortType)>(innerPortType), std::forward<decltype(name)>(name));
  auto __res__ = ::llvm::dyn_cast<InputWireOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

InputWireOp InputWireOp::create(::mlir::ImplicitLocOpBuilder &builder, StringAttr inner_sym, Type innerPortType, mlir::StringAttr name) {
  return create(builder, builder.getLoc(), std::forward<decltype(inner_sym)>(inner_sym), std::forward<decltype(innerPortType)>(innerPortType), std::forward<decltype(name)>(name));
}

void InputWireOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type port, ::mlir::Type output, ::circt::hw::InnerSymAttr inner_sym, /*optional*/::mlir::StringAttr name) {
  odsState.getOrAddProperties<Properties>().inner_sym = inner_sym;
  if (name) {
    odsState.getOrAddProperties<Properties>().name = name;
  }
  odsState.addTypes(port);
  odsState.addTypes(output);
}

InputWireOp InputWireOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type port, ::mlir::Type output, ::circt::hw::InnerSymAttr inner_sym, /*optional*/::mlir::StringAttr name) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(port)>(port), std::forward<decltype(output)>(output), std::forward<decltype(inner_sym)>(inner_sym), std::forward<decltype(name)>(name));
  auto __res__ = ::llvm::dyn_cast<InputWireOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

InputWireOp InputWireOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type port, ::mlir::Type output, ::circt::hw::InnerSymAttr inner_sym, /*optional*/::mlir::StringAttr name) {
  return create(builder, builder.getLoc(), std::forward<decltype(port)>(port), std::forward<decltype(output)>(output), std::forward<decltype(inner_sym)>(inner_sym), std::forward<decltype(name)>(name));
}

void InputWireOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::circt::hw::InnerSymAttr inner_sym, /*optional*/::mlir::StringAttr name) {
  odsState.getOrAddProperties<Properties>().inner_sym = inner_sym;
  if (name) {
    odsState.getOrAddProperties<Properties>().name = name;
  }
  assert(resultTypes.size() == 2u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

InputWireOp InputWireOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::circt::hw::InnerSymAttr inner_sym, /*optional*/::mlir::StringAttr name) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(inner_sym)>(inner_sym), std::forward<decltype(name)>(name));
  auto __res__ = ::llvm::dyn_cast<InputWireOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

InputWireOp InputWireOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::circt::hw::InnerSymAttr inner_sym, /*optional*/::mlir::StringAttr name) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(inner_sym)>(inner_sym), std::forward<decltype(name)>(name));
}

void InputWireOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 2u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<InputWireOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

InputWireOp InputWireOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<InputWireOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

InputWireOp InputWireOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void InputWireOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 2u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

InputWireOp InputWireOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<InputWireOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

InputWireOp InputWireOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult InputWireOp::verifyInvariantsImpl() {
  auto tblgen_inner_sym = getProperties().inner_sym; (void)tblgen_inner_sym;
  if (!tblgen_inner_sym) return emitOpError("requires attribute 'inner_sym'");
  auto tblgen_name = getProperties().name; (void)tblgen_name;

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Kanagawa2(*this, tblgen_inner_sym, "inner_sym")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Kanagawa3(*this, tblgen_name, "name")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Kanagawa3(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSResults(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Kanagawa5(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  if (!((std::equal_to<>()(PortRefType::get(this->getOperation()->getContext(), (*this->getODSResults(1).begin()).getType(), kanagawa::Direction::Input), (*this->getODSResults(0).begin()).getType()))))
    return emitOpError("failed to verify that the rhs type dictates the inner type of the rhs portref type");
  return ::mlir::success();
}

::llvm::LogicalResult InputWireOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

void InputWireOp::getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context) {
  results.add(canonicalize);
}

::mlir::ParseResult InputWireOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::circt::hw::InnerSymAttr inner_symAttr;
  ::mlir::Type outputRawType{};
  ::llvm::ArrayRef<::mlir::Type> outputTypes(&outputRawType, 1);

  if (parser.parseCustomAttributeWithFallback(inner_symAttr, ::mlir::Type{})) {
    return ::mlir::failure();
  }
  if (inner_symAttr) result.getOrAddProperties<InputWireOp::Properties>().inner_sym = inner_symAttr;
  if (parser.parseColon())
    return ::mlir::failure();

  if (parser.parseType(outputRawType))
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
  for (::mlir::Type type : outputTypes) {
    (void)type;
    if (!(!((::llvm::isa<::mlir::TokenType>(type))))) {
      return parser.emitError(parser.getNameLoc()) << "'output' must be any non-token type, but got " << type;
    }
  }
  result.addTypes(PortRefType::get(parser.getContext(), outputTypes[0], kanagawa::Direction::Input));
  result.addTypes(outputTypes);
  return ::mlir::success();
}

void InputWireOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
_odsPrinter.printStrippedAttrOrType(getInnerSymAttr());
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
   _odsPrinter << getOutput().getType();
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("inner_sym");
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
}

kanagawa::Direction InputWireOp::getPortDirection() {
  return kanagawa::Direction::Input;
}

// For hw:InnerSymbol - the symbol targets the operation and not any result.
std::optional<size_t> InputWireOp::getTargetResultIndex() {
  return std::nullopt;
}

} // namespace circt::kanagawa
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::kanagawa::InputWireOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::kanagawa::detail::InputWireOpGenericAdaptorBase::Properties)

namespace circt::kanagawa {


//===----------------------------------------------------------------------===//
// ::circt::kanagawa::InstanceOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

InstanceOpGenericAdaptorBase::InstanceOpGenericAdaptorBase(InstanceOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::circt::hw::InnerSymAttr InstanceOpGenericAdaptorBase::getInnerSym() {
  auto attr = getInnerSymAttr();
  return ::llvm::cast<::circt::hw::InnerSymAttr>(attr);
}

::circt::hw::InnerRefAttr InstanceOpGenericAdaptorBase::getTargetName() {
  auto attr = getTargetNameAttr();
  return ::llvm::cast<::circt::hw::InnerRefAttr>(attr);
}


} // namespace detail
InstanceOpAdaptor::InstanceOpAdaptor(InstanceOp op) : InstanceOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult InstanceOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_inner_sym = getProperties().inner_sym; (void)tblgen_inner_sym;
  if (!tblgen_inner_sym) return emitError(loc, "'kanagawa.instance' op requires attribute 'inner_sym'");
  auto tblgen_targetName = getProperties().targetName; (void)tblgen_targetName;
  if (!tblgen_targetName) return emitError(loc, "'kanagawa.instance' op requires attribute 'targetName'");

  if (tblgen_inner_sym && !((::llvm::isa<::circt::hw::InnerSymAttr>(tblgen_inner_sym))))
    return emitError(loc, "'kanagawa.instance' op attribute 'inner_sym' failed to satisfy constraint: Inner symbol definition");

  if (tblgen_targetName && !((::llvm::isa<::circt::hw::InnerRefAttr>(tblgen_targetName))))
    return emitError(loc, "'kanagawa.instance' op attribute 'targetName' failed to satisfy constraint: Refer to a name inside a module");
  return ::mlir::success();
}

::llvm::LogicalResult InstanceOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.inner_sym;
       auto attr = dict.get("inner_sym");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `inner_sym` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.targetName;
       auto attr = dict.get("targetName");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `targetName` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  return ::mlir::success();
}

::mlir::Attribute InstanceOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.inner_sym;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("inner_sym",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.targetName;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("targetName",
                                       propStorage));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code InstanceOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.inner_sym.getAsOpaquePointer()), 
    llvm::hash_value(prop.targetName.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> InstanceOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "inner_sym")
      return prop.inner_sym;

    if (name == "targetName")
      return prop.targetName;
  return std::nullopt;
}

void InstanceOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "inner_sym") {
       prop.inner_sym = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.inner_sym)>>(value);
       return;
    }

    if (name == "targetName") {
       prop.targetName = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.targetName)>>(value);
       return;
    }
}

void InstanceOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.inner_sym) attrs.append("inner_sym", prop.inner_sym);

    if (prop.targetName) attrs.append("targetName", prop.targetName);
}

::llvm::LogicalResult InstanceOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getInnerSymAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Kanagawa2(attr, "inner_sym", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getTargetNameAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Kanagawa1(attr, "targetName", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult InstanceOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.inner_sym)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readAttribute(prop.targetName)))
    return ::mlir::failure();
  return ::mlir::success();
}

void InstanceOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.inner_sym);
  writer.writeAttribute(prop.targetName);
}

::circt::hw::InnerSymAttr InstanceOp::getInnerSym() {
  auto attr = getInnerSymAttr();
  return ::llvm::cast<::circt::hw::InnerSymAttr>(attr);
}

::circt::hw::InnerRefAttr InstanceOp::getTargetName() {
  auto attr = getTargetNameAttr();
  return ::llvm::cast<::circt::hw::InnerRefAttr>(attr);
}

void InstanceOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, hw::InnerSymAttr instanceName, hw::InnerRefAttr targetName) {
      build(odsBuilder, odsState, odsBuilder.getType<ScopeRefType>(targetName),
        instanceName, targetName);
    
}

InstanceOp InstanceOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, hw::InnerSymAttr instanceName, hw::InnerRefAttr targetName) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(instanceName)>(instanceName), std::forward<decltype(targetName)>(targetName));
  auto __res__ = ::llvm::dyn_cast<InstanceOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

InstanceOp InstanceOp::create(::mlir::ImplicitLocOpBuilder &builder, hw::InnerSymAttr instanceName, hw::InnerRefAttr targetName) {
  return create(builder, builder.getLoc(), std::forward<decltype(instanceName)>(instanceName), std::forward<decltype(targetName)>(targetName));
}

void InstanceOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type scopeRef, ::circt::hw::InnerSymAttr inner_sym, ::circt::hw::InnerRefAttr targetName) {
  odsState.getOrAddProperties<Properties>().inner_sym = inner_sym;
  odsState.getOrAddProperties<Properties>().targetName = targetName;
  odsState.addTypes(scopeRef);
}

InstanceOp InstanceOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type scopeRef, ::circt::hw::InnerSymAttr inner_sym, ::circt::hw::InnerRefAttr targetName) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(scopeRef)>(scopeRef), std::forward<decltype(inner_sym)>(inner_sym), std::forward<decltype(targetName)>(targetName));
  auto __res__ = ::llvm::dyn_cast<InstanceOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

InstanceOp InstanceOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type scopeRef, ::circt::hw::InnerSymAttr inner_sym, ::circt::hw::InnerRefAttr targetName) {
  return create(builder, builder.getLoc(), std::forward<decltype(scopeRef)>(scopeRef), std::forward<decltype(inner_sym)>(inner_sym), std::forward<decltype(targetName)>(targetName));
}

void InstanceOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::circt::hw::InnerSymAttr inner_sym, ::circt::hw::InnerRefAttr targetName) {
  odsState.getOrAddProperties<Properties>().inner_sym = inner_sym;
  odsState.getOrAddProperties<Properties>().targetName = targetName;
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

InstanceOp InstanceOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::circt::hw::InnerSymAttr inner_sym, ::circt::hw::InnerRefAttr targetName) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(inner_sym)>(inner_sym), std::forward<decltype(targetName)>(targetName));
  auto __res__ = ::llvm::dyn_cast<InstanceOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

InstanceOp InstanceOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::circt::hw::InnerSymAttr inner_sym, ::circt::hw::InnerRefAttr targetName) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(inner_sym)>(inner_sym), std::forward<decltype(targetName)>(targetName));
}

void InstanceOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<InstanceOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

InstanceOp InstanceOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<InstanceOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

InstanceOp InstanceOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void InstanceOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

InstanceOp InstanceOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<InstanceOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

InstanceOp InstanceOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult InstanceOp::verifyInvariantsImpl() {
  auto tblgen_inner_sym = getProperties().inner_sym; (void)tblgen_inner_sym;
  if (!tblgen_inner_sym) return emitOpError("requires attribute 'inner_sym'");
  auto tblgen_targetName = getProperties().targetName; (void)tblgen_targetName;
  if (!tblgen_targetName) return emitOpError("requires attribute 'targetName'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Kanagawa2(*this, tblgen_inner_sym, "inner_sym")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Kanagawa1(*this, tblgen_targetName, "targetName")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Kanagawa2(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult InstanceOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult InstanceOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::circt::hw::InnerSymAttr inner_symAttr;
  ::circt::hw::InnerRefAttr targetNameAttr;
  ::mlir::Type scopeRefRawType{};
  ::llvm::ArrayRef<::mlir::Type> scopeRefTypes(&scopeRefRawType, 1);

  if (parser.parseCustomAttributeWithFallback(inner_symAttr, ::mlir::Type{})) {
    return ::mlir::failure();
  }
  if (inner_symAttr) result.getOrAddProperties<InstanceOp::Properties>().inner_sym = inner_symAttr;
  if (parser.parseComma())
    return ::mlir::failure();

  if (parser.parseCustomAttributeWithFallback(targetNameAttr, ::mlir::Type{})) {
    return ::mlir::failure();
  }
  if (targetNameAttr) result.getOrAddProperties<InstanceOp::Properties>().targetName = targetNameAttr;
  {
    auto loc = parser.getCurrentLocation();(void)loc;
    if (parser.parseOptionalAttrDict(result.attributes))
      return ::mlir::failure();
    if (failed(verifyInherentAttrs(result.name, result.attributes, [&]() {
        return parser.emitError(loc) << "'" << result.name.getStringRef() << "' op ";
      })))
      return ::mlir::failure();
  }
  {
    auto odsResult = parseScopeRefFromName(parser, scopeRefRawType, targetNameAttr);
    if (odsResult) return ::mlir::failure();
  }
  result.addTypes(scopeRefTypes);
  return ::mlir::success();
}

void InstanceOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
_odsPrinter.printStrippedAttrOrType(getInnerSymAttr());
  _odsPrinter << ",";
  _odsPrinter << ' ';
_odsPrinter.printStrippedAttrOrType(getTargetNameAttr());
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("inner_sym");
  elidedAttrs.push_back("targetName");
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ';
  printScopeRefFromName(_odsPrinter, *this, getScopeRef().getType(), getTargetNameAttr());
}

ClassOp InstanceOp::getClass(const hw::InnerRefNamespace &ns) {
  return ns.lookupOp<ClassOp>(getTargetNameAttr());
  // return dyn_cast_or_null<ClassOp>(getReferencedModule(&ns));
}
Operation* InstanceOp::getReferencedModule(
    const hw::InnerRefNamespace &ns) {
  return getClass(ns);
}

// For hw:InnerSymbol - the symbol targets the operation and not any result.
std::optional<size_t> InstanceOp::getTargetResultIndex() {
  return std::nullopt;
}

} // namespace circt::kanagawa
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::kanagawa::InstanceOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::kanagawa::detail::InstanceOpGenericAdaptorBase::Properties)

namespace circt::kanagawa {


//===----------------------------------------------------------------------===//
// ::circt::kanagawa::IsolatedStaticBlockOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

IsolatedStaticBlockOpGenericAdaptorBase::IsolatedStaticBlockOpGenericAdaptorBase(IsolatedStaticBlockOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

std::pair<unsigned, unsigned> IsolatedStaticBlockOpGenericAdaptorBase::getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
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

::std::optional<uint64_t> IsolatedStaticBlockOpGenericAdaptorBase::getMaxThreads() {
  auto attr = getMaxThreadsAttr();
  return attr ? ::std::optional<uint64_t>(attr.getValue().getZExtValue()) : (::std::nullopt);
}


} // namespace detail
IsolatedStaticBlockOpAdaptor::IsolatedStaticBlockOpAdaptor(IsolatedStaticBlockOp op) : IsolatedStaticBlockOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult IsolatedStaticBlockOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_maxThreads = getProperties().maxThreads; (void)tblgen_maxThreads;

  if (tblgen_maxThreads && !((((::llvm::isa<::mlir::IntegerAttr>(tblgen_maxThreads))) && ((::llvm::cast<::mlir::IntegerAttr>(tblgen_maxThreads).getType().isSignlessInteger(64)))) && ((::llvm::cast<::mlir::IntegerAttr>(tblgen_maxThreads).getInt() >= 1))))
    return emitError(loc, "'kanagawa.sblock.isolated' op attribute 'maxThreads' failed to satisfy constraint: 64-bit signless integer attribute whose minimum value is 1");
  return ::mlir::success();
}

std::pair<unsigned, unsigned> IsolatedStaticBlockOp::getODSOperandIndexAndLength(unsigned index) {
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

::mlir::MutableOperandRange IsolatedStaticBlockOp::getInputsMutable() {
  auto range = getODSOperandIndexAndLength(0);
  auto mutableRange = ::mlir::MutableOperandRange(getOperation(), range.first, range.second);
  return mutableRange;
}

std::pair<unsigned, unsigned> IsolatedStaticBlockOp::getODSResultIndexAndLength(unsigned index) {
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

::llvm::LogicalResult IsolatedStaticBlockOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.maxThreads;
       auto attr = dict.get("maxThreads");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `maxThreads` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  return ::mlir::success();
}

::mlir::Attribute IsolatedStaticBlockOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.maxThreads;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("maxThreads",
                                       propStorage));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code IsolatedStaticBlockOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.maxThreads.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> IsolatedStaticBlockOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "maxThreads")
      return prop.maxThreads;
  return std::nullopt;
}

void IsolatedStaticBlockOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "maxThreads") {
       prop.maxThreads = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.maxThreads)>>(value);
       return;
    }
}

void IsolatedStaticBlockOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.maxThreads) attrs.append("maxThreads", prop.maxThreads);
}

::llvm::LogicalResult IsolatedStaticBlockOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getMaxThreadsAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Kanagawa5(attr, "maxThreads", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult IsolatedStaticBlockOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readOptionalAttribute(prop.maxThreads)))
    return ::mlir::failure();
  return ::mlir::success();
}

void IsolatedStaticBlockOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;

  writer.writeOptionalAttribute(prop.maxThreads);
}

::std::optional<uint64_t> IsolatedStaticBlockOp::getMaxThreads() {
  auto attr = getMaxThreadsAttr();
  return attr ? ::std::optional<uint64_t>(attr.getValue().getZExtValue()) : (::std::nullopt);
}

void IsolatedStaticBlockOp::setMaxThreads(::std::optional<uint64_t> attrValue) {
    auto &odsProp = getProperties().maxThreads;
    if (attrValue)
      odsProp = ::mlir::Builder((*this)->getContext()).getIntegerAttr(::mlir::Builder((*this)->getContext()).getIntegerType(64), *attrValue);
    else
      odsProp = nullptr;
}

void IsolatedStaticBlockOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, TypeRange outputs, ValueRange inputs, IntegerAttr maxThreads) {
      odsState.addOperands(inputs);
      if (maxThreads)
        odsState.addAttribute(getMaxThreadsAttrName(odsState.name), maxThreads);
      auto* region = odsState.addRegion();
      odsState.addTypes(outputs);
      ensureTerminator(*region, odsBuilder, odsState.location);
      llvm::SmallVector<Location> argLocs;
      for(auto input : inputs)
        argLocs.push_back(input.getLoc());
      region->front().addArguments(inputs.getTypes(), argLocs);
    
}

IsolatedStaticBlockOp IsolatedStaticBlockOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, TypeRange outputs, ValueRange inputs, IntegerAttr maxThreads) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(outputs)>(outputs), std::forward<decltype(inputs)>(inputs), std::forward<decltype(maxThreads)>(maxThreads));
  auto __res__ = ::llvm::dyn_cast<IsolatedStaticBlockOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

IsolatedStaticBlockOp IsolatedStaticBlockOp::create(::mlir::ImplicitLocOpBuilder &builder, TypeRange outputs, ValueRange inputs, IntegerAttr maxThreads) {
  return create(builder, builder.getLoc(), std::forward<decltype(outputs)>(outputs), std::forward<decltype(inputs)>(inputs), std::forward<decltype(maxThreads)>(maxThreads));
}

::llvm::LogicalResult IsolatedStaticBlockOp::verifyInvariantsImpl() {
  auto tblgen_maxThreads = getProperties().maxThreads; (void)tblgen_maxThreads;

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Kanagawa5(*this, tblgen_maxThreads, "maxThreads")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Kanagawa1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Kanagawa1(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;

    for (auto &region : ::llvm::MutableArrayRef((*this)->getRegion(0)))
      if (::mlir::failed(__mlir_ods_local_region_constraint_Kanagawa1(*this, region, "body", index++)))
        return ::mlir::failure();
  }
  return ::mlir::success();
}

::llvm::LogicalResult IsolatedStaticBlockOp::verifyInvariants() {
  if(::mlir::succeeded(verifyInvariantsImpl()) && ::mlir::succeeded(verify()))
    return ::mlir::success();
  return ::mlir::failure();
}

::llvm::LogicalResult IsolatedStaticBlockOp::setPropertiesFromParsedAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
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

    auto &propStorage = prop.maxThreads;
    auto maxThreadsAttrName = ::mlir::StringAttr::get(ctx, "maxThreads");
    auto attr = dict.get(maxThreadsAttrName);
    usedKeys.insert(maxThreadsAttrName);
    if (attr || /*isRequired=*/false) {
      if (!attr) {
        emitError() << "expected key entry for maxThreads in DictionaryAttr to set "
                   "Properties.";
        return ::mlir::failure();
      }
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `maxThreads` in property conversion: " << attr;
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


} // namespace circt::kanagawa
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::kanagawa::IsolatedStaticBlockOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::kanagawa::detail::IsolatedStaticBlockOpGenericAdaptorBase::Properties)

namespace circt::kanagawa {


//===----------------------------------------------------------------------===//
// ::circt::kanagawa::MethodOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

MethodOpGenericAdaptorBase::MethodOpGenericAdaptorBase(MethodOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::circt::hw::InnerSymAttr MethodOpGenericAdaptorBase::getInnerSym() {
  auto attr = getInnerSymAttr();
  return ::llvm::cast<::circt::hw::InnerSymAttr>(attr);
}

::mlir::FunctionType MethodOpGenericAdaptorBase::getFunctionType() {
  auto attr = getFunctionTypeAttr();
  return ::llvm::cast<::mlir::FunctionType>(attr.getValue());
}

::mlir::ArrayAttr MethodOpGenericAdaptorBase::getArgNames() {
  auto attr = getArgNamesAttr();
  return attr;
}

::std::optional< ::mlir::ArrayAttr > MethodOpGenericAdaptorBase::getArgAttrs() {
  auto attr = getArgAttrsAttr();
  return attr ? ::std::optional< ::mlir::ArrayAttr >(attr) : (::std::nullopt);
}

::std::optional< ::mlir::ArrayAttr > MethodOpGenericAdaptorBase::getResAttrs() {
  auto attr = getResAttrsAttr();
  return attr ? ::std::optional< ::mlir::ArrayAttr >(attr) : (::std::nullopt);
}


} // namespace detail
MethodOpAdaptor::MethodOpAdaptor(MethodOp op) : MethodOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult MethodOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_argNames = getProperties().argNames; (void)tblgen_argNames;
  if (!tblgen_argNames) return emitError(loc, "'kanagawa.method' op requires attribute 'argNames'");
  auto tblgen_arg_attrs = getProperties().arg_attrs; (void)tblgen_arg_attrs;
  auto tblgen_function_type = getProperties().function_type; (void)tblgen_function_type;
  if (!tblgen_function_type) return emitError(loc, "'kanagawa.method' op requires attribute 'function_type'");
  auto tblgen_inner_sym = getProperties().inner_sym; (void)tblgen_inner_sym;
  if (!tblgen_inner_sym) return emitError(loc, "'kanagawa.method' op requires attribute 'inner_sym'");
  auto tblgen_res_attrs = getProperties().res_attrs; (void)tblgen_res_attrs;

  if (tblgen_inner_sym && !((::llvm::isa<::circt::hw::InnerSymAttr>(tblgen_inner_sym))))
    return emitError(loc, "'kanagawa.method' op attribute 'inner_sym' failed to satisfy constraint: Inner symbol definition");

  if (tblgen_function_type && !(((::llvm::isa<::mlir::TypeAttr>(tblgen_function_type))) && ((::llvm::isa<::mlir::FunctionType>(::llvm::cast<::mlir::TypeAttr>(tblgen_function_type).getValue()))) && ((::llvm::isa<::mlir::FunctionType>(::llvm::cast<::mlir::TypeAttr>(tblgen_function_type).getValue())))))
    return emitError(loc, "'kanagawa.method' op attribute 'function_type' failed to satisfy constraint: type attribute of function type");

  if (tblgen_argNames && !((::llvm::isa<::mlir::ArrayAttr>(tblgen_argNames))))
    return emitError(loc, "'kanagawa.method' op attribute 'argNames' failed to satisfy constraint: array attribute");

  if (tblgen_arg_attrs && !(((::llvm::isa<::mlir::ArrayAttr>(tblgen_arg_attrs))) && (::llvm::all_of(::llvm::cast<::mlir::ArrayAttr>(tblgen_arg_attrs), [&](::mlir::Attribute attr) { return attr && ((::llvm::isa<::mlir::DictionaryAttr>(attr))); }))))
    return emitError(loc, "'kanagawa.method' op attribute 'arg_attrs' failed to satisfy constraint: Array of dictionary attributes");

  if (tblgen_res_attrs && !(((::llvm::isa<::mlir::ArrayAttr>(tblgen_res_attrs))) && (::llvm::all_of(::llvm::cast<::mlir::ArrayAttr>(tblgen_res_attrs), [&](::mlir::Attribute attr) { return attr && ((::llvm::isa<::mlir::DictionaryAttr>(attr))); }))))
    return emitError(loc, "'kanagawa.method' op attribute 'res_attrs' failed to satisfy constraint: Array of dictionary attributes");
  return ::mlir::success();
}

::llvm::LogicalResult MethodOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.argNames;
       auto attr = dict.get("argNames");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `argNames` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.arg_attrs;
       auto attr = dict.get("arg_attrs");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `arg_attrs` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.function_type;
       auto attr = dict.get("function_type");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `function_type` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.inner_sym;
       auto attr = dict.get("inner_sym");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `inner_sym` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.res_attrs;
       auto attr = dict.get("res_attrs");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `res_attrs` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  return ::mlir::success();
}

::mlir::Attribute MethodOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.argNames;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("argNames",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.arg_attrs;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("arg_attrs",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.function_type;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("function_type",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.inner_sym;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("inner_sym",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.res_attrs;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("res_attrs",
                                       propStorage));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code MethodOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.argNames.getAsOpaquePointer()), 
    llvm::hash_value(prop.arg_attrs.getAsOpaquePointer()), 
    llvm::hash_value(prop.function_type.getAsOpaquePointer()), 
    llvm::hash_value(prop.inner_sym.getAsOpaquePointer()), 
    llvm::hash_value(prop.res_attrs.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> MethodOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "argNames")
      return prop.argNames;

    if (name == "arg_attrs")
      return prop.arg_attrs;

    if (name == "function_type")
      return prop.function_type;

    if (name == "inner_sym")
      return prop.inner_sym;

    if (name == "res_attrs")
      return prop.res_attrs;
  return std::nullopt;
}

void MethodOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "argNames") {
       prop.argNames = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.argNames)>>(value);
       return;
    }

    if (name == "arg_attrs") {
       prop.arg_attrs = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.arg_attrs)>>(value);
       return;
    }

    if (name == "function_type") {
       prop.function_type = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.function_type)>>(value);
       return;
    }

    if (name == "inner_sym") {
       prop.inner_sym = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.inner_sym)>>(value);
       return;
    }

    if (name == "res_attrs") {
       prop.res_attrs = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.res_attrs)>>(value);
       return;
    }
}

void MethodOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.argNames) attrs.append("argNames", prop.argNames);

    if (prop.arg_attrs) attrs.append("arg_attrs", prop.arg_attrs);

    if (prop.function_type) attrs.append("function_type", prop.function_type);

    if (prop.inner_sym) attrs.append("inner_sym", prop.inner_sym);

    if (prop.res_attrs) attrs.append("res_attrs", prop.res_attrs);
}

::llvm::LogicalResult MethodOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getArgNamesAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Kanagawa7(attr, "argNames", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getArgAttrsAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Kanagawa8(attr, "arg_attrs", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getFunctionTypeAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Kanagawa6(attr, "function_type", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getInnerSymAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Kanagawa2(attr, "inner_sym", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getResAttrsAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Kanagawa8(attr, "res_attrs", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult MethodOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.argNames)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readOptionalAttribute(prop.arg_attrs)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readAttribute(prop.function_type)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readAttribute(prop.inner_sym)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readOptionalAttribute(prop.res_attrs)))
    return ::mlir::failure();
  return ::mlir::success();
}

void MethodOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.argNames);

  writer.writeOptionalAttribute(prop.arg_attrs);
  writer.writeAttribute(prop.function_type);
  writer.writeAttribute(prop.inner_sym);

  writer.writeOptionalAttribute(prop.res_attrs);
}

::circt::hw::InnerSymAttr MethodOp::getInnerSym() {
  auto attr = getInnerSymAttr();
  return ::llvm::cast<::circt::hw::InnerSymAttr>(attr);
}

::mlir::FunctionType MethodOp::getFunctionType() {
  auto attr = getFunctionTypeAttr();
  return ::llvm::cast<::mlir::FunctionType>(attr.getValue());
}

::mlir::ArrayAttr MethodOp::getArgNames() {
  auto attr = getArgNamesAttr();
  return attr;
}

::std::optional< ::mlir::ArrayAttr > MethodOp::getArgAttrs() {
  auto attr = getArgAttrsAttr();
  return attr ? ::std::optional< ::mlir::ArrayAttr >(attr) : (::std::nullopt);
}

::std::optional< ::mlir::ArrayAttr > MethodOp::getResAttrs() {
  auto attr = getResAttrsAttr();
  return attr ? ::std::optional< ::mlir::ArrayAttr >(attr) : (::std::nullopt);
}

void MethodOp::setFunctionType(::mlir::FunctionType attrValue) {
  getProperties().function_type = ::mlir::TypeAttr::get(attrValue);
}

void MethodOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::circt::hw::InnerSymAttr inner_sym, ::mlir::TypeAttr function_type, ::mlir::ArrayAttr argNames, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs) {
  odsState.getOrAddProperties<Properties>().inner_sym = inner_sym;
  odsState.getOrAddProperties<Properties>().function_type = function_type;
  odsState.getOrAddProperties<Properties>().argNames = argNames;
  if (arg_attrs) {
    odsState.getOrAddProperties<Properties>().arg_attrs = arg_attrs;
  }
  if (res_attrs) {
    odsState.getOrAddProperties<Properties>().res_attrs = res_attrs;
  }
  (void)odsState.addRegion();
}

MethodOp MethodOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::circt::hw::InnerSymAttr inner_sym, ::mlir::TypeAttr function_type, ::mlir::ArrayAttr argNames, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(inner_sym)>(inner_sym), std::forward<decltype(function_type)>(function_type), std::forward<decltype(argNames)>(argNames), std::forward<decltype(arg_attrs)>(arg_attrs), std::forward<decltype(res_attrs)>(res_attrs));
  auto __res__ = ::llvm::dyn_cast<MethodOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

MethodOp MethodOp::create(::mlir::ImplicitLocOpBuilder &builder, ::circt::hw::InnerSymAttr inner_sym, ::mlir::TypeAttr function_type, ::mlir::ArrayAttr argNames, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs) {
  return create(builder, builder.getLoc(), std::forward<decltype(inner_sym)>(inner_sym), std::forward<decltype(function_type)>(function_type), std::forward<decltype(argNames)>(argNames), std::forward<decltype(arg_attrs)>(arg_attrs), std::forward<decltype(res_attrs)>(res_attrs));
}

void MethodOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::circt::hw::InnerSymAttr inner_sym, ::mlir::TypeAttr function_type, ::mlir::ArrayAttr argNames, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs) {
  odsState.getOrAddProperties<Properties>().inner_sym = inner_sym;
  odsState.getOrAddProperties<Properties>().function_type = function_type;
  odsState.getOrAddProperties<Properties>().argNames = argNames;
  if (arg_attrs) {
    odsState.getOrAddProperties<Properties>().arg_attrs = arg_attrs;
  }
  if (res_attrs) {
    odsState.getOrAddProperties<Properties>().res_attrs = res_attrs;
  }
  (void)odsState.addRegion();
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

MethodOp MethodOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::circt::hw::InnerSymAttr inner_sym, ::mlir::TypeAttr function_type, ::mlir::ArrayAttr argNames, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(inner_sym)>(inner_sym), std::forward<decltype(function_type)>(function_type), std::forward<decltype(argNames)>(argNames), std::forward<decltype(arg_attrs)>(arg_attrs), std::forward<decltype(res_attrs)>(res_attrs));
  auto __res__ = ::llvm::dyn_cast<MethodOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

MethodOp MethodOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::circt::hw::InnerSymAttr inner_sym, ::mlir::TypeAttr function_type, ::mlir::ArrayAttr argNames, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(inner_sym)>(inner_sym), std::forward<decltype(function_type)>(function_type), std::forward<decltype(argNames)>(argNames), std::forward<decltype(arg_attrs)>(arg_attrs), std::forward<decltype(res_attrs)>(res_attrs));
}

void MethodOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::circt::hw::InnerSymAttr inner_sym, ::mlir::FunctionType function_type, ::mlir::ArrayAttr argNames, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs) {
  odsState.getOrAddProperties<Properties>().inner_sym = inner_sym;
  odsState.getOrAddProperties<Properties>().function_type = ::mlir::TypeAttr::get(function_type);
  odsState.getOrAddProperties<Properties>().argNames = argNames;
  if (arg_attrs) {
    odsState.getOrAddProperties<Properties>().arg_attrs = arg_attrs;
  }
  if (res_attrs) {
    odsState.getOrAddProperties<Properties>().res_attrs = res_attrs;
  }
  (void)odsState.addRegion();
}

MethodOp MethodOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::circt::hw::InnerSymAttr inner_sym, ::mlir::FunctionType function_type, ::mlir::ArrayAttr argNames, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(inner_sym)>(inner_sym), std::forward<decltype(function_type)>(function_type), std::forward<decltype(argNames)>(argNames), std::forward<decltype(arg_attrs)>(arg_attrs), std::forward<decltype(res_attrs)>(res_attrs));
  auto __res__ = ::llvm::dyn_cast<MethodOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

MethodOp MethodOp::create(::mlir::ImplicitLocOpBuilder &builder, ::circt::hw::InnerSymAttr inner_sym, ::mlir::FunctionType function_type, ::mlir::ArrayAttr argNames, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs) {
  return create(builder, builder.getLoc(), std::forward<decltype(inner_sym)>(inner_sym), std::forward<decltype(function_type)>(function_type), std::forward<decltype(argNames)>(argNames), std::forward<decltype(arg_attrs)>(arg_attrs), std::forward<decltype(res_attrs)>(res_attrs));
}

void MethodOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::circt::hw::InnerSymAttr inner_sym, ::mlir::FunctionType function_type, ::mlir::ArrayAttr argNames, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs) {
  odsState.getOrAddProperties<Properties>().inner_sym = inner_sym;
  odsState.getOrAddProperties<Properties>().function_type = ::mlir::TypeAttr::get(function_type);
  odsState.getOrAddProperties<Properties>().argNames = argNames;
  if (arg_attrs) {
    odsState.getOrAddProperties<Properties>().arg_attrs = arg_attrs;
  }
  if (res_attrs) {
    odsState.getOrAddProperties<Properties>().res_attrs = res_attrs;
  }
  (void)odsState.addRegion();
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

MethodOp MethodOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::circt::hw::InnerSymAttr inner_sym, ::mlir::FunctionType function_type, ::mlir::ArrayAttr argNames, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(inner_sym)>(inner_sym), std::forward<decltype(function_type)>(function_type), std::forward<decltype(argNames)>(argNames), std::forward<decltype(arg_attrs)>(arg_attrs), std::forward<decltype(res_attrs)>(res_attrs));
  auto __res__ = ::llvm::dyn_cast<MethodOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

MethodOp MethodOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::circt::hw::InnerSymAttr inner_sym, ::mlir::FunctionType function_type, ::mlir::ArrayAttr argNames, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(inner_sym)>(inner_sym), std::forward<decltype(function_type)>(function_type), std::forward<decltype(argNames)>(argNames), std::forward<decltype(arg_attrs)>(arg_attrs), std::forward<decltype(res_attrs)>(res_attrs));
}

void MethodOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  for (unsigned i = 0; i != 1; ++i)
    (void)odsState.addRegion();
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<MethodOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

MethodOp MethodOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<MethodOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

MethodOp MethodOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void MethodOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  for (unsigned i = 0; i != 1; ++i)
    (void)odsState.addRegion();
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

MethodOp MethodOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<MethodOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

MethodOp MethodOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult MethodOp::verifyInvariantsImpl() {
  auto tblgen_argNames = getProperties().argNames; (void)tblgen_argNames;
  if (!tblgen_argNames) return emitOpError("requires attribute 'argNames'");
  auto tblgen_arg_attrs = getProperties().arg_attrs; (void)tblgen_arg_attrs;
  auto tblgen_function_type = getProperties().function_type; (void)tblgen_function_type;
  if (!tblgen_function_type) return emitOpError("requires attribute 'function_type'");
  auto tblgen_inner_sym = getProperties().inner_sym; (void)tblgen_inner_sym;
  if (!tblgen_inner_sym) return emitOpError("requires attribute 'inner_sym'");
  auto tblgen_res_attrs = getProperties().res_attrs; (void)tblgen_res_attrs;

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Kanagawa2(*this, tblgen_inner_sym, "inner_sym")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Kanagawa6(*this, tblgen_function_type, "function_type")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Kanagawa7(*this, tblgen_argNames, "argNames")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Kanagawa8(*this, tblgen_arg_attrs, "arg_attrs")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Kanagawa8(*this, tblgen_res_attrs, "res_attrs")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;

    for (auto &region : ::llvm::MutableArrayRef((*this)->getRegion(0)))
      if (::mlir::failed(__mlir_ods_local_region_constraint_Kanagawa2(*this, region, "body", index++)))
        return ::mlir::failure();
  }
  return ::mlir::success();
}

::llvm::LogicalResult MethodOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::llvm::LogicalResult MethodOp::setPropertiesFromParsedAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
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

    auto &propStorage = prop.inner_sym;
    auto inner_symAttrName = ::mlir::StringAttr::get(ctx, "inner_sym");
    auto attr = dict.get(inner_symAttrName);
    usedKeys.insert(inner_symAttrName);
    if (attr || /*isRequired=*/true) {
      if (!attr) {
        emitError() << "expected key entry for inner_sym in DictionaryAttr to set "
                   "Properties.";
        return ::mlir::failure();
      }
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `inner_sym` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  {

    auto &propStorage = prop.function_type;
    auto function_typeAttrName = ::mlir::StringAttr::get(ctx, "function_type");
    auto attr = dict.get(function_typeAttrName);
    usedKeys.insert(function_typeAttrName);
    if (attr || /*isRequired=*/true) {
      if (!attr) {
        emitError() << "expected key entry for function_type in DictionaryAttr to set "
                   "Properties.";
        return ::mlir::failure();
      }
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `function_type` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  {

    auto &propStorage = prop.argNames;
    auto argNamesAttrName = ::mlir::StringAttr::get(ctx, "argNames");
    auto attr = dict.get(argNamesAttrName);
    usedKeys.insert(argNamesAttrName);
    if (attr || /*isRequired=*/true) {
      if (!attr) {
        emitError() << "expected key entry for argNames in DictionaryAttr to set "
                   "Properties.";
        return ::mlir::failure();
      }
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `argNames` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  {

    auto &propStorage = prop.arg_attrs;
    auto arg_attrsAttrName = ::mlir::StringAttr::get(ctx, "arg_attrs");
    auto attr = dict.get(arg_attrsAttrName);
    usedKeys.insert(arg_attrsAttrName);
    if (attr || /*isRequired=*/false) {
      if (!attr) {
        emitError() << "expected key entry for arg_attrs in DictionaryAttr to set "
                   "Properties.";
        return ::mlir::failure();
      }
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `arg_attrs` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  {

    auto &propStorage = prop.res_attrs;
    auto res_attrsAttrName = ::mlir::StringAttr::get(ctx, "res_attrs");
    auto attr = dict.get(res_attrsAttrName);
    usedKeys.insert(res_attrsAttrName);
    if (attr || /*isRequired=*/false) {
      if (!attr) {
        emitError() << "expected key entry for res_attrs in DictionaryAttr to set "
                   "Properties.";
        return ::mlir::failure();
      }
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `res_attrs` in property conversion: " << attr;
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

// For hw:InnerSymbol - the symbol targets the operation and not any result.
std::optional<size_t> MethodOp::getTargetResultIndex() {
  return std::nullopt;
}

} // namespace circt::kanagawa
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::kanagawa::MethodOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::kanagawa::detail::MethodOpGenericAdaptorBase::Properties)

namespace circt::kanagawa {


//===----------------------------------------------------------------------===//
// ::circt::kanagawa::OutputPortOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

OutputPortOpGenericAdaptorBase::OutputPortOpGenericAdaptorBase(OutputPortOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::circt::hw::InnerSymAttr OutputPortOpGenericAdaptorBase::getInnerSym() {
  auto attr = getInnerSymAttr();
  return ::llvm::cast<::circt::hw::InnerSymAttr>(attr);
}

::mlir::Type OutputPortOpGenericAdaptorBase::getType() {
  auto attr = getTypeAttr();
  return ::llvm::cast<::mlir::Type>(attr.getValue());
}

::std::optional< ::llvm::StringRef > OutputPortOpGenericAdaptorBase::getName() {
  auto attr = getNameAttr();
  return attr ? ::std::optional< ::llvm::StringRef >(attr.getValue()) : (::std::nullopt);
}


} // namespace detail
OutputPortOpAdaptor::OutputPortOpAdaptor(OutputPortOp op) : OutputPortOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult OutputPortOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_inner_sym = getProperties().inner_sym; (void)tblgen_inner_sym;
  if (!tblgen_inner_sym) return emitError(loc, "'kanagawa.port.output' op requires attribute 'inner_sym'");
  auto tblgen_name = getProperties().name; (void)tblgen_name;
  auto tblgen_type = getProperties().type; (void)tblgen_type;
  if (!tblgen_type) return emitError(loc, "'kanagawa.port.output' op requires attribute 'type'");

  if (tblgen_inner_sym && !((::llvm::isa<::circt::hw::InnerSymAttr>(tblgen_inner_sym))))
    return emitError(loc, "'kanagawa.port.output' op attribute 'inner_sym' failed to satisfy constraint: Inner symbol definition");

  if (tblgen_type && !(((::llvm::isa<::mlir::TypeAttr>(tblgen_type))) && ((::llvm::isa<::mlir::Type>(::llvm::cast<::mlir::TypeAttr>(tblgen_type).getValue()))) && (!((::llvm::isa<::mlir::TokenType>(::llvm::cast<::mlir::TypeAttr>(tblgen_type).getValue()))))))
    return emitError(loc, "'kanagawa.port.output' op attribute 'type' failed to satisfy constraint: type attribute of any non-token type");

  if (tblgen_name && !((::llvm::isa<::mlir::StringAttr>(tblgen_name))))
    return emitError(loc, "'kanagawa.port.output' op attribute 'name' failed to satisfy constraint: string attribute");
  return ::mlir::success();
}

::llvm::LogicalResult OutputPortOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.inner_sym;
       auto attr = dict.get("inner_sym");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `inner_sym` in property conversion: " << attr;
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
    auto &propStorage = prop.type;
       auto attr = dict.get("type");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `type` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  return ::mlir::success();
}

::mlir::Attribute OutputPortOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.inner_sym;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("inner_sym",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.name;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("name",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.type;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("type",
                                       propStorage));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code OutputPortOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.inner_sym.getAsOpaquePointer()), 
    llvm::hash_value(prop.name.getAsOpaquePointer()), 
    llvm::hash_value(prop.type.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> OutputPortOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "inner_sym")
      return prop.inner_sym;

    if (name == "name")
      return prop.name;

    if (name == "type")
      return prop.type;
  return std::nullopt;
}

void OutputPortOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "inner_sym") {
       prop.inner_sym = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.inner_sym)>>(value);
       return;
    }

    if (name == "name") {
       prop.name = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.name)>>(value);
       return;
    }

    if (name == "type") {
       prop.type = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.type)>>(value);
       return;
    }
}

void OutputPortOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.inner_sym) attrs.append("inner_sym", prop.inner_sym);

    if (prop.name) attrs.append("name", prop.name);

    if (prop.type) attrs.append("type", prop.type);
}

::llvm::LogicalResult OutputPortOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getInnerSymAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Kanagawa2(attr, "inner_sym", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getNameAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Kanagawa3(attr, "name", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getTypeAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Kanagawa10(attr, "type", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult OutputPortOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.inner_sym)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readOptionalAttribute(prop.name)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readAttribute(prop.type)))
    return ::mlir::failure();
  return ::mlir::success();
}

void OutputPortOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.inner_sym);

  writer.writeOptionalAttribute(prop.name);
  writer.writeAttribute(prop.type);
}

::circt::hw::InnerSymAttr OutputPortOp::getInnerSym() {
  auto attr = getInnerSymAttr();
  return ::llvm::cast<::circt::hw::InnerSymAttr>(attr);
}

::mlir::Type OutputPortOp::getType() {
  auto attr = getTypeAttr();
  return ::llvm::cast<::mlir::Type>(attr.getValue());
}

::std::optional< ::llvm::StringRef > OutputPortOp::getName() {
  auto attr = getNameAttr();
  return attr ? ::std::optional< ::llvm::StringRef >(attr.getValue()) : (::std::nullopt);
}

void OutputPortOp::setType(::mlir::Type attrValue) {
  getProperties().type = ::mlir::TypeAttr::get(attrValue);
}

void OutputPortOp::setName(::std::optional<::llvm::StringRef> attrValue) {
    auto &odsProp = getProperties().name;
    if (attrValue)
      odsProp = ::mlir::Builder((*this)->getContext()).getStringAttr(*attrValue);
    else
      odsProp = nullptr;
}

void OutputPortOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type port, ::circt::hw::InnerSymAttr inner_sym, ::mlir::TypeAttr type, /*optional*/::mlir::StringAttr name) {
  odsState.getOrAddProperties<Properties>().inner_sym = inner_sym;
  odsState.getOrAddProperties<Properties>().type = type;
  if (name) {
    odsState.getOrAddProperties<Properties>().name = name;
  }
  odsState.addTypes(port);
}

OutputPortOp OutputPortOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type port, ::circt::hw::InnerSymAttr inner_sym, ::mlir::TypeAttr type, /*optional*/::mlir::StringAttr name) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(port)>(port), std::forward<decltype(inner_sym)>(inner_sym), std::forward<decltype(type)>(type), std::forward<decltype(name)>(name));
  auto __res__ = ::llvm::dyn_cast<OutputPortOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

OutputPortOp OutputPortOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type port, ::circt::hw::InnerSymAttr inner_sym, ::mlir::TypeAttr type, /*optional*/::mlir::StringAttr name) {
  return create(builder, builder.getLoc(), std::forward<decltype(port)>(port), std::forward<decltype(inner_sym)>(inner_sym), std::forward<decltype(type)>(type), std::forward<decltype(name)>(name));
}

void OutputPortOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::circt::hw::InnerSymAttr inner_sym, ::mlir::TypeAttr type, /*optional*/::mlir::StringAttr name) {
  odsState.getOrAddProperties<Properties>().inner_sym = inner_sym;
  odsState.getOrAddProperties<Properties>().type = type;
  if (name) {
    odsState.getOrAddProperties<Properties>().name = name;
  }

        ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
        if (::mlir::succeeded(OutputPortOp::inferReturnTypes(odsBuilder.getContext(),
                      odsState.location, odsState.operands,
                      odsState.attributes.getDictionary(odsState.getContext()),
                      odsState.getRawProperties(),
                      odsState.regions, inferredReturnTypes)))
          odsState.addTypes(inferredReturnTypes);
        else
          ::mlir::detail::reportFatalInferReturnTypesError(odsState);
        
}

OutputPortOp OutputPortOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::circt::hw::InnerSymAttr inner_sym, ::mlir::TypeAttr type, /*optional*/::mlir::StringAttr name) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(inner_sym)>(inner_sym), std::forward<decltype(type)>(type), std::forward<decltype(name)>(name));
  auto __res__ = ::llvm::dyn_cast<OutputPortOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

OutputPortOp OutputPortOp::create(::mlir::ImplicitLocOpBuilder &builder, ::circt::hw::InnerSymAttr inner_sym, ::mlir::TypeAttr type, /*optional*/::mlir::StringAttr name) {
  return create(builder, builder.getLoc(), std::forward<decltype(inner_sym)>(inner_sym), std::forward<decltype(type)>(type), std::forward<decltype(name)>(name));
}

void OutputPortOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::circt::hw::InnerSymAttr inner_sym, ::mlir::TypeAttr type, /*optional*/::mlir::StringAttr name) {
  odsState.getOrAddProperties<Properties>().inner_sym = inner_sym;
  odsState.getOrAddProperties<Properties>().type = type;
  if (name) {
    odsState.getOrAddProperties<Properties>().name = name;
  }
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

OutputPortOp OutputPortOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::circt::hw::InnerSymAttr inner_sym, ::mlir::TypeAttr type, /*optional*/::mlir::StringAttr name) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(inner_sym)>(inner_sym), std::forward<decltype(type)>(type), std::forward<decltype(name)>(name));
  auto __res__ = ::llvm::dyn_cast<OutputPortOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

OutputPortOp OutputPortOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::circt::hw::InnerSymAttr inner_sym, ::mlir::TypeAttr type, /*optional*/::mlir::StringAttr name) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(inner_sym)>(inner_sym), std::forward<decltype(type)>(type), std::forward<decltype(name)>(name));
}

void OutputPortOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type port, ::circt::hw::InnerSymAttr inner_sym, ::mlir::Type type, /*optional*/::mlir::StringAttr name) {
  odsState.getOrAddProperties<Properties>().inner_sym = inner_sym;
  odsState.getOrAddProperties<Properties>().type = ::mlir::TypeAttr::get(type);
  if (name) {
    odsState.getOrAddProperties<Properties>().name = name;
  }
  odsState.addTypes(port);
}

OutputPortOp OutputPortOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type port, ::circt::hw::InnerSymAttr inner_sym, ::mlir::Type type, /*optional*/::mlir::StringAttr name) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(port)>(port), std::forward<decltype(inner_sym)>(inner_sym), std::forward<decltype(type)>(type), std::forward<decltype(name)>(name));
  auto __res__ = ::llvm::dyn_cast<OutputPortOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

OutputPortOp OutputPortOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type port, ::circt::hw::InnerSymAttr inner_sym, ::mlir::Type type, /*optional*/::mlir::StringAttr name) {
  return create(builder, builder.getLoc(), std::forward<decltype(port)>(port), std::forward<decltype(inner_sym)>(inner_sym), std::forward<decltype(type)>(type), std::forward<decltype(name)>(name));
}

void OutputPortOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::circt::hw::InnerSymAttr inner_sym, ::mlir::Type type, /*optional*/::mlir::StringAttr name) {
  odsState.getOrAddProperties<Properties>().inner_sym = inner_sym;
  odsState.getOrAddProperties<Properties>().type = ::mlir::TypeAttr::get(type);
  if (name) {
    odsState.getOrAddProperties<Properties>().name = name;
  }

        ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
        if (::mlir::succeeded(OutputPortOp::inferReturnTypes(odsBuilder.getContext(),
                      odsState.location, odsState.operands,
                      odsState.attributes.getDictionary(odsState.getContext()),
                      odsState.getRawProperties(),
                      odsState.regions, inferredReturnTypes)))
          odsState.addTypes(inferredReturnTypes);
        else
          ::mlir::detail::reportFatalInferReturnTypesError(odsState);
        
}

OutputPortOp OutputPortOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::circt::hw::InnerSymAttr inner_sym, ::mlir::Type type, /*optional*/::mlir::StringAttr name) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(inner_sym)>(inner_sym), std::forward<decltype(type)>(type), std::forward<decltype(name)>(name));
  auto __res__ = ::llvm::dyn_cast<OutputPortOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

OutputPortOp OutputPortOp::create(::mlir::ImplicitLocOpBuilder &builder, ::circt::hw::InnerSymAttr inner_sym, ::mlir::Type type, /*optional*/::mlir::StringAttr name) {
  return create(builder, builder.getLoc(), std::forward<decltype(inner_sym)>(inner_sym), std::forward<decltype(type)>(type), std::forward<decltype(name)>(name));
}

void OutputPortOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::circt::hw::InnerSymAttr inner_sym, ::mlir::Type type, /*optional*/::mlir::StringAttr name) {
  odsState.getOrAddProperties<Properties>().inner_sym = inner_sym;
  odsState.getOrAddProperties<Properties>().type = ::mlir::TypeAttr::get(type);
  if (name) {
    odsState.getOrAddProperties<Properties>().name = name;
  }
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

OutputPortOp OutputPortOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::circt::hw::InnerSymAttr inner_sym, ::mlir::Type type, /*optional*/::mlir::StringAttr name) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(inner_sym)>(inner_sym), std::forward<decltype(type)>(type), std::forward<decltype(name)>(name));
  auto __res__ = ::llvm::dyn_cast<OutputPortOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

OutputPortOp OutputPortOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::circt::hw::InnerSymAttr inner_sym, ::mlir::Type type, /*optional*/::mlir::StringAttr name) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(inner_sym)>(inner_sym), std::forward<decltype(type)>(type), std::forward<decltype(name)>(name));
}

void OutputPortOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<OutputPortOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

OutputPortOp OutputPortOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<OutputPortOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

OutputPortOp OutputPortOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void OutputPortOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<OutputPortOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
  ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
  if (::mlir::succeeded(OutputPortOp::inferReturnTypes(odsBuilder.getContext(),
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

OutputPortOp OutputPortOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<OutputPortOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

OutputPortOp OutputPortOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void OutputPortOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

OutputPortOp OutputPortOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<OutputPortOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

OutputPortOp OutputPortOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

void OutputPortOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties &>(properties));
  odsState.addAttributes(discardableAttributes);

  ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
  if (::mlir::succeeded(OutputPortOp::inferReturnTypes(odsBuilder.getContext(),
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

OutputPortOp OutputPortOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<OutputPortOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

OutputPortOp OutputPortOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult OutputPortOp::verifyInvariantsImpl() {
  auto tblgen_inner_sym = getProperties().inner_sym; (void)tblgen_inner_sym;
  if (!tblgen_inner_sym) return emitOpError("requires attribute 'inner_sym'");
  auto tblgen_name = getProperties().name; (void)tblgen_name;
  auto tblgen_type = getProperties().type; (void)tblgen_type;
  if (!tblgen_type) return emitOpError("requires attribute 'type'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Kanagawa2(*this, tblgen_inner_sym, "inner_sym")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Kanagawa10(*this, tblgen_type, "type")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Kanagawa3(*this, tblgen_name, "name")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Kanagawa3(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult OutputPortOp::verifyInvariants() {
  if(::mlir::succeeded(verifyInvariantsImpl()) && ::mlir::succeeded(verify()))
    return ::mlir::success();
  return ::mlir::failure();
}

void OutputPortOp::getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context) {
  results.add(canonicalize);
}

::mlir::ParseResult OutputPortOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::StringAttr nameAttr;
  ::circt::hw::InnerSymAttr inner_symAttr;
  ::mlir::TypeAttr typeAttr;

  ::mlir::OptionalParseResult parseResultnameAttr =
    parser.parseOptionalAttribute(nameAttr, parser.getBuilder().getType<::mlir::NoneType>());
  if (parseResultnameAttr.has_value() && failed(*parseResultnameAttr))
    return ::mlir::failure();
  if (parseResultnameAttr.has_value() && succeeded(*parseResultnameAttr))
  if (nameAttr) result.getOrAddProperties<OutputPortOp::Properties>().name = nameAttr;
  if (nameAttr) {
  }
  if (parser.parseKeyword("sym"))
    return ::mlir::failure();

  if (parser.parseCustomAttributeWithFallback(inner_symAttr, ::mlir::Type{})) {
    return ::mlir::failure();
  }
  if (inner_symAttr) result.getOrAddProperties<OutputPortOp::Properties>().inner_sym = inner_symAttr;
  if (parser.parseColon())
    return ::mlir::failure();

  if (parser.parseCustomAttributeWithFallback(typeAttr, parser.getBuilder().getType<::mlir::NoneType>())) {
    return ::mlir::failure();
  }
  if (typeAttr) result.getOrAddProperties<OutputPortOp::Properties>().type = typeAttr;
  {
    auto loc = parser.getCurrentLocation();(void)loc;
    if (parser.parseOptionalAttrDict(result.attributes))
      return ::mlir::failure();
    if (failed(verifyInherentAttrs(result.name, result.attributes, [&]() {
        return parser.emitError(loc) << "'" << result.name.getStringRef() << "' op ";
      })))
      return ::mlir::failure();
  }

  ::llvm::SmallVector<::mlir::Type> inferredReturnTypes;
  if (::mlir::failed(OutputPortOp::inferReturnTypes(parser.getContext(),
      result.location, result.operands,
      result.attributes.getDictionary(parser.getContext()),
      result.getRawProperties(),
      result.regions, inferredReturnTypes)))
    return ::mlir::failure();
  result.addTypes(inferredReturnTypes);
  return ::mlir::success();
}

void OutputPortOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  if (getNameAttr()) {
    _odsPrinter << ' ';
    _odsPrinter.printAttributeWithoutType(getNameAttr());
  }
  _odsPrinter << ' ' << "sym";
  _odsPrinter << ' ';
_odsPrinter.printStrippedAttrOrType(getInnerSymAttr());
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
  _odsPrinter.printAttributeWithoutType(getTypeAttr());
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("name");
  elidedAttrs.push_back("inner_sym");
  elidedAttrs.push_back("type");
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
}

kanagawa::Direction OutputPortOp::getPortDirection() {
  return kanagawa::Direction::Output;
}

LogicalResult OutputPortOp::verify() {
  if(llvm::isa<ScopeRefType>(getType()))
    return emitOpError("port type cannot be a scope reference");

  return success();
}

} // namespace circt::kanagawa
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::kanagawa::OutputPortOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::kanagawa::detail::OutputPortOpGenericAdaptorBase::Properties)

namespace circt::kanagawa {


//===----------------------------------------------------------------------===//
// ::circt::kanagawa::OutputWireOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

OutputWireOpGenericAdaptorBase::OutputWireOpGenericAdaptorBase(OutputWireOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::circt::hw::InnerSymAttr OutputWireOpGenericAdaptorBase::getInnerSym() {
  auto attr = getInnerSymAttr();
  return ::llvm::cast<::circt::hw::InnerSymAttr>(attr);
}

::std::optional< ::llvm::StringRef > OutputWireOpGenericAdaptorBase::getName() {
  auto attr = getNameAttr();
  return attr ? ::std::optional< ::llvm::StringRef >(attr.getValue()) : (::std::nullopt);
}


} // namespace detail
OutputWireOpAdaptor::OutputWireOpAdaptor(OutputWireOp op) : OutputWireOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult OutputWireOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_inner_sym = getProperties().inner_sym; (void)tblgen_inner_sym;
  if (!tblgen_inner_sym) return emitError(loc, "'kanagawa.wire.output' op requires attribute 'inner_sym'");
  auto tblgen_name = getProperties().name; (void)tblgen_name;

  if (tblgen_inner_sym && !((::llvm::isa<::circt::hw::InnerSymAttr>(tblgen_inner_sym))))
    return emitError(loc, "'kanagawa.wire.output' op attribute 'inner_sym' failed to satisfy constraint: Inner symbol definition");

  if (tblgen_name && !((::llvm::isa<::mlir::StringAttr>(tblgen_name))))
    return emitError(loc, "'kanagawa.wire.output' op attribute 'name' failed to satisfy constraint: string attribute");
  return ::mlir::success();
}

::llvm::LogicalResult OutputWireOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.inner_sym;
       auto attr = dict.get("inner_sym");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `inner_sym` in property conversion: " << attr;
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
  return ::mlir::success();
}

::mlir::Attribute OutputWireOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.inner_sym;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("inner_sym",
                                       propStorage));
    }

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

llvm::hash_code OutputWireOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.inner_sym.getAsOpaquePointer()), 
    llvm::hash_value(prop.name.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> OutputWireOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "inner_sym")
      return prop.inner_sym;

    if (name == "name")
      return prop.name;
  return std::nullopt;
}

void OutputWireOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "inner_sym") {
       prop.inner_sym = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.inner_sym)>>(value);
       return;
    }

    if (name == "name") {
       prop.name = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.name)>>(value);
       return;
    }
}

void OutputWireOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.inner_sym) attrs.append("inner_sym", prop.inner_sym);

    if (prop.name) attrs.append("name", prop.name);
}

::llvm::LogicalResult OutputWireOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getInnerSymAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Kanagawa2(attr, "inner_sym", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getNameAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Kanagawa3(attr, "name", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult OutputWireOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.inner_sym)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readOptionalAttribute(prop.name)))
    return ::mlir::failure();
  return ::mlir::success();
}

void OutputWireOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.inner_sym);

  writer.writeOptionalAttribute(prop.name);
}

::circt::hw::InnerSymAttr OutputWireOp::getInnerSym() {
  auto attr = getInnerSymAttr();
  return ::llvm::cast<::circt::hw::InnerSymAttr>(attr);
}

::std::optional< ::llvm::StringRef > OutputWireOp::getName() {
  auto attr = getNameAttr();
  return attr ? ::std::optional< ::llvm::StringRef >(attr.getValue()) : (::std::nullopt);
}

void OutputWireOp::setName(::std::optional<::llvm::StringRef> attrValue) {
    auto &odsProp = getProperties().name;
    if (attrValue)
      odsProp = ::mlir::Builder((*this)->getContext()).getStringAttr(*attrValue);
    else
      odsProp = nullptr;
}

void OutputWireOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type port, ::circt::hw::InnerSymAttr inner_sym, ::mlir::Value input, /*optional*/::mlir::StringAttr name) {
  odsState.addOperands(input);
  odsState.getOrAddProperties<Properties>().inner_sym = inner_sym;
  if (name) {
    odsState.getOrAddProperties<Properties>().name = name;
  }
  odsState.addTypes(port);
}

OutputWireOp OutputWireOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type port, ::circt::hw::InnerSymAttr inner_sym, ::mlir::Value input, /*optional*/::mlir::StringAttr name) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(port)>(port), std::forward<decltype(inner_sym)>(inner_sym), std::forward<decltype(input)>(input), std::forward<decltype(name)>(name));
  auto __res__ = ::llvm::dyn_cast<OutputWireOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

OutputWireOp OutputWireOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type port, ::circt::hw::InnerSymAttr inner_sym, ::mlir::Value input, /*optional*/::mlir::StringAttr name) {
  return create(builder, builder.getLoc(), std::forward<decltype(port)>(port), std::forward<decltype(inner_sym)>(inner_sym), std::forward<decltype(input)>(input), std::forward<decltype(name)>(name));
}

void OutputWireOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::circt::hw::InnerSymAttr inner_sym, ::mlir::Value input, /*optional*/::mlir::StringAttr name) {
  odsState.addOperands(input);
  odsState.getOrAddProperties<Properties>().inner_sym = inner_sym;
  if (name) {
    odsState.getOrAddProperties<Properties>().name = name;
  }

        ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
        if (::mlir::succeeded(OutputWireOp::inferReturnTypes(odsBuilder.getContext(),
                      odsState.location, odsState.operands,
                      odsState.attributes.getDictionary(odsState.getContext()),
                      odsState.getRawProperties(),
                      odsState.regions, inferredReturnTypes)))
          odsState.addTypes(inferredReturnTypes);
        else
          ::mlir::detail::reportFatalInferReturnTypesError(odsState);
        
}

OutputWireOp OutputWireOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::circt::hw::InnerSymAttr inner_sym, ::mlir::Value input, /*optional*/::mlir::StringAttr name) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(inner_sym)>(inner_sym), std::forward<decltype(input)>(input), std::forward<decltype(name)>(name));
  auto __res__ = ::llvm::dyn_cast<OutputWireOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

OutputWireOp OutputWireOp::create(::mlir::ImplicitLocOpBuilder &builder, ::circt::hw::InnerSymAttr inner_sym, ::mlir::Value input, /*optional*/::mlir::StringAttr name) {
  return create(builder, builder.getLoc(), std::forward<decltype(inner_sym)>(inner_sym), std::forward<decltype(input)>(input), std::forward<decltype(name)>(name));
}

void OutputWireOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::circt::hw::InnerSymAttr inner_sym, ::mlir::Value input, /*optional*/::mlir::StringAttr name) {
  odsState.addOperands(input);
  odsState.getOrAddProperties<Properties>().inner_sym = inner_sym;
  if (name) {
    odsState.getOrAddProperties<Properties>().name = name;
  }
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

OutputWireOp OutputWireOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::circt::hw::InnerSymAttr inner_sym, ::mlir::Value input, /*optional*/::mlir::StringAttr name) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(inner_sym)>(inner_sym), std::forward<decltype(input)>(input), std::forward<decltype(name)>(name));
  auto __res__ = ::llvm::dyn_cast<OutputWireOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

OutputWireOp OutputWireOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::circt::hw::InnerSymAttr inner_sym, ::mlir::Value input, /*optional*/::mlir::StringAttr name) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(inner_sym)>(inner_sym), std::forward<decltype(input)>(input), std::forward<decltype(name)>(name));
}

void OutputWireOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<OutputWireOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

OutputWireOp OutputWireOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<OutputWireOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

OutputWireOp OutputWireOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void OutputWireOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<OutputWireOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
  ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
  if (::mlir::succeeded(OutputWireOp::inferReturnTypes(odsBuilder.getContext(),
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

OutputWireOp OutputWireOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<OutputWireOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

OutputWireOp OutputWireOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void OutputWireOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

OutputWireOp OutputWireOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<OutputWireOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

OutputWireOp OutputWireOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

void OutputWireOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties &>(properties));
  odsState.addAttributes(discardableAttributes);

  ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
  if (::mlir::succeeded(OutputWireOp::inferReturnTypes(odsBuilder.getContext(),
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

OutputWireOp OutputWireOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<OutputWireOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

OutputWireOp OutputWireOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult OutputWireOp::verifyInvariantsImpl() {
  auto tblgen_inner_sym = getProperties().inner_sym; (void)tblgen_inner_sym;
  if (!tblgen_inner_sym) return emitOpError("requires attribute 'inner_sym'");
  auto tblgen_name = getProperties().name; (void)tblgen_name;

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Kanagawa2(*this, tblgen_inner_sym, "inner_sym")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Kanagawa3(*this, tblgen_name, "name")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Kanagawa5(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Kanagawa3(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  if (!((std::equal_to<>()(PortRefType::get(this->getOperation()->getContext(), (*this->getODSOperands(0).begin()).getType(), kanagawa::Direction::Output), (*this->getODSResults(0).begin()).getType()))))
    return emitOpError("failed to verify that the rhs type dictates the inner type of the rhs portref type");
  return ::mlir::success();
}

::llvm::LogicalResult OutputWireOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

void OutputWireOp::getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context) {
  results.add(canonicalize);
}

::llvm::LogicalResult OutputWireOp::inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::PropertyRef properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes) {
  inferredReturnTypes.resize(1);
  ::mlir::Builder odsBuilder(context);
  if (operands.size() <= 0)
    return ::mlir::failure();
  ::mlir::Type odsInferredType0 = PortRefType::get(context, operands[0].getType(), kanagawa::Direction::Output);
  inferredReturnTypes[0] = odsInferredType0;
  return ::mlir::success();
}

::mlir::ParseResult OutputWireOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::circt::hw::InnerSymAttr inner_symAttr;
  ::mlir::OpAsmParser::UnresolvedOperand inputRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> inputOperands(&inputRawOperand, 1);  ::llvm::SMLoc inputOperandsLoc;
  (void)inputOperandsLoc;
  ::mlir::Type inputRawType{};
  ::llvm::ArrayRef<::mlir::Type> inputTypes(&inputRawType, 1);

  if (parser.parseCustomAttributeWithFallback(inner_symAttr, ::mlir::Type{})) {
    return ::mlir::failure();
  }
  if (inner_symAttr) result.getOrAddProperties<OutputWireOp::Properties>().inner_sym = inner_symAttr;
  if (parser.parseComma())
    return ::mlir::failure();

  inputOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(inputRawOperand))
    return ::mlir::failure();
  if (parser.parseColon())
    return ::mlir::failure();

  if (parser.parseType(inputRawType))
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
  for (::mlir::Type type : inputTypes) {
    (void)type;
    if (!(!((::llvm::isa<::mlir::TokenType>(type))))) {
      return parser.emitError(parser.getNameLoc()) << "'input' must be any non-token type, but got " << type;
    }
  }
  result.addTypes(PortRefType::get(parser.getContext(), inputTypes[0], kanagawa::Direction::Output));
  if (parser.resolveOperands(inputOperands, inputTypes, inputOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void OutputWireOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
_odsPrinter.printStrippedAttrOrType(getInnerSymAttr());
  _odsPrinter << ",";
  _odsPrinter << ' ';
  _odsPrinter << getInput();
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
   _odsPrinter << getInput().getType();
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("inner_sym");
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
}

kanagawa::Direction OutputWireOp::getPortDirection() {
  return kanagawa::Direction::Output;
}

// For hw:InnerSymbol - the symbol targets the operation and not any result.
std::optional<size_t> OutputWireOp::getTargetResultIndex() {
  return std::nullopt;
}

} // namespace circt::kanagawa
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::kanagawa::OutputWireOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::kanagawa::detail::OutputWireOpGenericAdaptorBase::Properties)

namespace circt::kanagawa {


//===----------------------------------------------------------------------===//
// ::circt::kanagawa::PathOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

PathOpGenericAdaptorBase::PathOpGenericAdaptorBase(PathOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::mlir::ArrayAttr PathOpGenericAdaptorBase::getPath() {
  auto attr = getPathAttr();
  return attr;
}


} // namespace detail
PathOpAdaptor::PathOpAdaptor(PathOp op) : PathOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult PathOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_path = getProperties().path; (void)tblgen_path;
  if (!tblgen_path) return emitError(loc, "'kanagawa.path' op requires attribute 'path'");

  if (tblgen_path && !(((::llvm::isa<::mlir::ArrayAttr>(tblgen_path))) && (::llvm::all_of(::llvm::cast<::mlir::ArrayAttr>(tblgen_path), [&](::mlir::Attribute attr) { return attr && ((::llvm::isa<::circt::kanagawa::PathStepAttr>(attr))); }))))
    return emitError(loc, "'kanagawa.path' op attribute 'path' failed to satisfy constraint: Path step array attribute");
  return ::mlir::success();
}

::llvm::LogicalResult PathOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.path;
       auto attr = dict.get("path");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `path` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  return ::mlir::success();
}

::mlir::Attribute PathOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.path;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("path",
                                       propStorage));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code PathOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.path.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> PathOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "path")
      return prop.path;
  return std::nullopt;
}

void PathOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "path") {
       prop.path = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.path)>>(value);
       return;
    }
}

void PathOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.path) attrs.append("path", prop.path);
}

::llvm::LogicalResult PathOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getPathAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Kanagawa11(attr, "path", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult PathOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.path)))
    return ::mlir::failure();
  return ::mlir::success();
}

void PathOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.path);
}

::mlir::ArrayAttr PathOp::getPath() {
  auto attr = getPathAttr();
  return attr;
}

void PathOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type instance, ::mlir::ArrayAttr path) {
  odsState.getOrAddProperties<Properties>().path = path;
  odsState.addTypes(instance);
}

PathOp PathOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type instance, ::mlir::ArrayAttr path) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(instance)>(instance), std::forward<decltype(path)>(path));
  auto __res__ = ::llvm::dyn_cast<PathOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

PathOp PathOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type instance, ::mlir::ArrayAttr path) {
  return create(builder, builder.getLoc(), std::forward<decltype(instance)>(instance), std::forward<decltype(path)>(path));
}

void PathOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ArrayAttr path) {
  odsState.getOrAddProperties<Properties>().path = path;

        ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
        if (::mlir::succeeded(PathOp::inferReturnTypes(odsBuilder.getContext(),
                      odsState.location, odsState.operands,
                      odsState.attributes.getDictionary(odsState.getContext()),
                      odsState.getRawProperties(),
                      odsState.regions, inferredReturnTypes)))
          odsState.addTypes(inferredReturnTypes);
        else
          ::mlir::detail::reportFatalInferReturnTypesError(odsState);
        
}

PathOp PathOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ArrayAttr path) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(path)>(path));
  auto __res__ = ::llvm::dyn_cast<PathOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

PathOp PathOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ArrayAttr path) {
  return create(builder, builder.getLoc(), std::forward<decltype(path)>(path));
}

void PathOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ArrayAttr path) {
  odsState.getOrAddProperties<Properties>().path = path;
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

PathOp PathOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ArrayAttr path) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(path)>(path));
  auto __res__ = ::llvm::dyn_cast<PathOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

PathOp PathOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ArrayAttr path) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(path)>(path));
}

void PathOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<PathOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

PathOp PathOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<PathOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

PathOp PathOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void PathOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<PathOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
  ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
  if (::mlir::succeeded(PathOp::inferReturnTypes(odsBuilder.getContext(),
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

PathOp PathOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<PathOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

PathOp PathOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void PathOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

PathOp PathOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<PathOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

PathOp PathOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

void PathOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties &>(properties));
  odsState.addAttributes(discardableAttributes);

  ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
  if (::mlir::succeeded(PathOp::inferReturnTypes(odsBuilder.getContext(),
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

PathOp PathOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<PathOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

PathOp PathOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult PathOp::verifyInvariantsImpl() {
  auto tblgen_path = getProperties().path; (void)tblgen_path;
  if (!tblgen_path) return emitOpError("requires attribute 'path'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Kanagawa11(*this, tblgen_path, "path")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Kanagawa2(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult PathOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

void PathOp::getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context) {
  results.add(canonicalize);
}

::mlir::ParseResult PathOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::ArrayAttr pathAttr;

  if (parser.parseCustomAttributeWithFallback(pathAttr, parser.getBuilder().getType<::mlir::NoneType>())) {
    return ::mlir::failure();
  }
  if (pathAttr) result.getOrAddProperties<PathOp::Properties>().path = pathAttr;
  {
    auto loc = parser.getCurrentLocation();(void)loc;
    if (parser.parseOptionalAttrDict(result.attributes))
      return ::mlir::failure();
    if (failed(verifyInherentAttrs(result.name, result.attributes, [&]() {
        return parser.emitError(loc) << "'" << result.name.getStringRef() << "' op ";
      })))
      return ::mlir::failure();
  }

  ::llvm::SmallVector<::mlir::Type> inferredReturnTypes;
  if (::mlir::failed(PathOp::inferReturnTypes(parser.getContext(),
      result.location, result.operands,
      result.attributes.getDictionary(parser.getContext()),
      result.getRawProperties(),
      result.regions, inferredReturnTypes)))
    return ::mlir::failure();
  result.addTypes(inferredReturnTypes);
  return ::mlir::success();
}

void PathOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter.printAttributeWithoutType(getPathAttr());
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("path");
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
}

void PathOp::getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects) {
}


} // namespace circt::kanagawa
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::kanagawa::PathOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::kanagawa::detail::PathOpGenericAdaptorBase::Properties)

namespace circt::kanagawa {


//===----------------------------------------------------------------------===//
// ::circt::kanagawa::PipelineHeaderOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

PipelineHeaderOpGenericAdaptorBase::PipelineHeaderOpGenericAdaptorBase(PipelineHeaderOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}


} // namespace detail
PipelineHeaderOpAdaptor::PipelineHeaderOpAdaptor(PipelineHeaderOp op) : PipelineHeaderOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult PipelineHeaderOpAdaptor::verify(::mlir::Location loc) {
  return ::mlir::success();
}

void PipelineHeaderOp::getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn) {
  auto resultGroup0 = getODSResults(0);
  if (!resultGroup0.empty())
    setNameFn(*resultGroup0.begin(), "clock");
  auto resultGroup1 = getODSResults(1);
  if (!resultGroup1.empty())
    setNameFn(*resultGroup1.begin(), "reset");
  auto resultGroup2 = getODSResults(2);
  if (!resultGroup2.empty())
    setNameFn(*resultGroup2.begin(), "go");
  auto resultGroup3 = getODSResults(3);
  if (!resultGroup3.empty())
    setNameFn(*resultGroup3.begin(), "stall");
}

::llvm::LogicalResult PipelineHeaderOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }
      return ::mlir::success();
}

::mlir::Attribute PipelineHeaderOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code PipelineHeaderOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine();
}

std::optional<mlir::Attribute> PipelineHeaderOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
  return std::nullopt;
}

void PipelineHeaderOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
}

void PipelineHeaderOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
}

::llvm::LogicalResult PipelineHeaderOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    return ::mlir::success();
}

void PipelineHeaderOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type clock, ::mlir::Type reset, ::mlir::Type go, ::mlir::Type stall) {
  odsState.addTypes(clock);
  odsState.addTypes(reset);
  odsState.addTypes(go);
  odsState.addTypes(stall);
}

PipelineHeaderOp PipelineHeaderOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type clock, ::mlir::Type reset, ::mlir::Type go, ::mlir::Type stall) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(clock)>(clock), std::forward<decltype(reset)>(reset), std::forward<decltype(go)>(go), std::forward<decltype(stall)>(stall));
  auto __res__ = ::llvm::dyn_cast<PipelineHeaderOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

PipelineHeaderOp PipelineHeaderOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type clock, ::mlir::Type reset, ::mlir::Type go, ::mlir::Type stall) {
  return create(builder, builder.getLoc(), std::forward<decltype(clock)>(clock), std::forward<decltype(reset)>(reset), std::forward<decltype(go)>(go), std::forward<decltype(stall)>(stall));
}

void PipelineHeaderOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState) {
        ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
        if (::mlir::succeeded(PipelineHeaderOp::inferReturnTypes(odsBuilder.getContext(),
                      odsState.location, odsState.operands,
                      odsState.attributes.getDictionary(odsState.getContext()),
                      odsState.getRawProperties(),
                      odsState.regions, inferredReturnTypes)))
          odsState.addTypes(inferredReturnTypes);
        else
          ::mlir::detail::reportFatalInferReturnTypesError(odsState);
        
}

PipelineHeaderOp PipelineHeaderOp::create(::mlir::OpBuilder &builder, ::mlir::Location location) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__);
  auto __res__ = ::llvm::dyn_cast<PipelineHeaderOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

PipelineHeaderOp PipelineHeaderOp::create(::mlir::ImplicitLocOpBuilder &builder) {
  return create(builder, builder.getLoc());
}

void PipelineHeaderOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes) {
  assert(resultTypes.size() == 4u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

PipelineHeaderOp PipelineHeaderOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes));
  auto __res__ = ::llvm::dyn_cast<PipelineHeaderOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

PipelineHeaderOp PipelineHeaderOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes));
}

void PipelineHeaderOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 4u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

PipelineHeaderOp PipelineHeaderOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<PipelineHeaderOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

PipelineHeaderOp PipelineHeaderOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void PipelineHeaderOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);

  ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
  if (::mlir::succeeded(PipelineHeaderOp::inferReturnTypes(odsBuilder.getContext(),
          odsState.location, operands,
          odsState.attributes.getDictionary(odsState.getContext()),
          odsState.getRawProperties(),
          odsState.regions, inferredReturnTypes))) {
    assert(inferredReturnTypes.size() == 4u && "mismatched number of return types");
    odsState.addTypes(inferredReturnTypes);
  } else {
    ::llvm::report_fatal_error("Failed to infer result type(s).");
  }
}

PipelineHeaderOp PipelineHeaderOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<PipelineHeaderOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

PipelineHeaderOp PipelineHeaderOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void PipelineHeaderOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 4u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

PipelineHeaderOp PipelineHeaderOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<PipelineHeaderOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

PipelineHeaderOp PipelineHeaderOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

void PipelineHeaderOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties &>(properties));
  odsState.addAttributes(discardableAttributes);

  ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
  if (::mlir::succeeded(PipelineHeaderOp::inferReturnTypes(odsBuilder.getContext(),
          odsState.location, operands,
          odsState.attributes.getDictionary(odsState.getContext()),
          odsState.getRawProperties(),
          odsState.regions, inferredReturnTypes))) {
    assert(inferredReturnTypes.size() == 4u && "mismatched number of return types");
    odsState.addTypes(inferredReturnTypes);
  } else {
    ::llvm::report_fatal_error("Failed to infer result type(s).");
  }
}

PipelineHeaderOp PipelineHeaderOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<PipelineHeaderOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

PipelineHeaderOp PipelineHeaderOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult PipelineHeaderOp::verifyInvariantsImpl() {
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Kanagawa6(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSResults(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Kanagawa7(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup2 = getODSResults(2);

    for (auto v : valueGroup2) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Kanagawa7(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup3 = getODSResults(3);

    for (auto v : valueGroup3) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Kanagawa7(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult PipelineHeaderOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::llvm::LogicalResult PipelineHeaderOp::inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::PropertyRef properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes) {
  inferredReturnTypes.resize(4);
  ::mlir::Builder odsBuilder(context);
  ::mlir::Type odsInferredType0 = odsBuilder.getType<::circt::seq::ClockType>();
  ::mlir::Type odsInferredType1 = odsBuilder.getIntegerType(1);
  ::mlir::Type odsInferredType2 = odsBuilder.getIntegerType(1);
  ::mlir::Type odsInferredType3 = odsBuilder.getIntegerType(1);
  inferredReturnTypes[0] = odsInferredType0;
  inferredReturnTypes[1] = odsInferredType1;
  inferredReturnTypes[2] = odsInferredType2;
  inferredReturnTypes[3] = odsInferredType3;
  return ::mlir::success();
}

::mlir::ParseResult PipelineHeaderOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  {
    auto loc = parser.getCurrentLocation();(void)loc;
    if (parser.parseOptionalAttrDict(result.attributes))
      return ::mlir::failure();
    if (failed(verifyInherentAttrs(result.name, result.attributes, [&]() {
        return parser.emitError(loc) << "'" << result.name.getStringRef() << "' op ";
      })))
      return ::mlir::failure();
  }
  ::mlir::Type odsBuildableType0 = parser.getBuilder().getType<::circt::seq::ClockType>();
  ::mlir::Type odsBuildableType1 = parser.getBuilder().getIntegerType(1);
  result.addTypes(odsBuildableType0);
  result.addTypes(odsBuildableType1);
  result.addTypes(odsBuildableType1);
  result.addTypes(odsBuildableType1);
  return ::mlir::success();
}

void PipelineHeaderOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
}

void PipelineHeaderOp::getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects) {
}


} // namespace circt::kanagawa
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::kanagawa::PipelineHeaderOp)

namespace circt::kanagawa {


//===----------------------------------------------------------------------===//
// ::circt::kanagawa::PortReadOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

PortReadOpGenericAdaptorBase::PortReadOpGenericAdaptorBase(PortReadOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}


} // namespace detail
PortReadOpAdaptor::PortReadOpAdaptor(PortReadOp op) : PortReadOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult PortReadOpAdaptor::verify(::mlir::Location loc) {
  return ::mlir::success();
}

::llvm::LogicalResult PortReadOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }
      return ::mlir::success();
}

::mlir::Attribute PortReadOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code PortReadOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine();
}

std::optional<mlir::Attribute> PortReadOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
  return std::nullopt;
}

void PortReadOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
}

void PortReadOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
}

::llvm::LogicalResult PortReadOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    return ::mlir::success();
}

void PortReadOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type output, ::mlir::Value port) {
  odsState.addOperands(port);
  odsState.addTypes(output);
}

PortReadOp PortReadOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type output, ::mlir::Value port) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(output)>(output), std::forward<decltype(port)>(port));
  auto __res__ = ::llvm::dyn_cast<PortReadOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

PortReadOp PortReadOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type output, ::mlir::Value port) {
  return create(builder, builder.getLoc(), std::forward<decltype(output)>(output), std::forward<decltype(port)>(port));
}

void PortReadOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value port) {
  odsState.addOperands(port);

        ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
        if (::mlir::succeeded(PortReadOp::inferReturnTypes(odsBuilder.getContext(),
                      odsState.location, odsState.operands,
                      odsState.attributes.getDictionary(odsState.getContext()),
                      odsState.getRawProperties(),
                      odsState.regions, inferredReturnTypes)))
          odsState.addTypes(inferredReturnTypes);
        else
          ::mlir::detail::reportFatalInferReturnTypesError(odsState);
        
}

PortReadOp PortReadOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value port) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(port)>(port));
  auto __res__ = ::llvm::dyn_cast<PortReadOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

PortReadOp PortReadOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value port) {
  return create(builder, builder.getLoc(), std::forward<decltype(port)>(port));
}

void PortReadOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value port) {
  odsState.addOperands(port);
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

PortReadOp PortReadOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value port) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(port)>(port));
  auto __res__ = ::llvm::dyn_cast<PortReadOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

PortReadOp PortReadOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value port) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(port)>(port));
}

void PortReadOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

PortReadOp PortReadOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<PortReadOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

PortReadOp PortReadOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void PortReadOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);

  ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
  if (::mlir::succeeded(PortReadOp::inferReturnTypes(odsBuilder.getContext(),
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

PortReadOp PortReadOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<PortReadOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

PortReadOp PortReadOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void PortReadOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

PortReadOp PortReadOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<PortReadOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

PortReadOp PortReadOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

void PortReadOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties &>(properties));
  odsState.addAttributes(discardableAttributes);

  ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
  if (::mlir::succeeded(PortReadOp::inferReturnTypes(odsBuilder.getContext(),
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

PortReadOp PortReadOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<PortReadOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

PortReadOp PortReadOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult PortReadOp::verifyInvariantsImpl() {
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Kanagawa3(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Kanagawa5(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  if (!((std::equal_to<>()(llvm::cast<PortRefType>((*this->getODSOperands(0).begin()).getType()).getPortType(), (*this->getODSResults(0).begin()).getType()))))
    return emitOpError("failed to verify that the inner type of the lhs portref type dictates the rhs type");
  return ::mlir::success();
}

::llvm::LogicalResult PortReadOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::llvm::LogicalResult PortReadOp::inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::PropertyRef properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes) {
  inferredReturnTypes.resize(1);
  ::mlir::Builder odsBuilder(context);
  if (operands.size() <= 0)
    return ::mlir::failure();
  ::mlir::Type odsInferredType0 = llvm::cast<PortRefType>(operands[0].getType()).getPortType();
  inferredReturnTypes[0] = odsInferredType0;
  return ::mlir::success();
}

::mlir::ParseResult PortReadOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::OpAsmParser::UnresolvedOperand portRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> portOperands(&portRawOperand, 1);  ::llvm::SMLoc portOperandsLoc;
  (void)portOperandsLoc;
  ::mlir::Type portRawType{};
  ::llvm::ArrayRef<::mlir::Type> portTypes(&portRawType, 1);

  portOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(portRawOperand))
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

  if (parser.parseType(portRawType))
    return ::mlir::failure();
  for (::mlir::Type type : portTypes) {
    (void)type;
    if (!((::llvm::isa<::circt::kanagawa::PortRefType>(type)))) {
      return parser.emitError(parser.getNameLoc()) << "'port' must be , but got " << type;
    }
  }
  result.addTypes(llvm::cast<PortRefType>(portTypes[0]).getPortType());
  if (parser.resolveOperands(portOperands, portTypes, portOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void PortReadOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter << getPort();
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
   _odsPrinter << getPort().getType();
}

void PortReadOp::getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects) {
}


} // namespace circt::kanagawa
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::kanagawa::PortReadOp)

namespace circt::kanagawa {


//===----------------------------------------------------------------------===//
// ::circt::kanagawa::PortWriteOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

PortWriteOpGenericAdaptorBase::PortWriteOpGenericAdaptorBase(PortWriteOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}


} // namespace detail
PortWriteOpAdaptor::PortWriteOpAdaptor(PortWriteOp op) : PortWriteOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult PortWriteOpAdaptor::verify(::mlir::Location loc) {
  return ::mlir::success();
}

::llvm::LogicalResult PortWriteOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }
      return ::mlir::success();
}

::mlir::Attribute PortWriteOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code PortWriteOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine();
}

std::optional<mlir::Attribute> PortWriteOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
  return std::nullopt;
}

void PortWriteOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
}

void PortWriteOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
}

::llvm::LogicalResult PortWriteOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    return ::mlir::success();
}

void PortWriteOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value port, ::mlir::Value value) {
  odsState.addOperands(port);
  odsState.addOperands(value);
}

PortWriteOp PortWriteOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value port, ::mlir::Value value) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(port)>(port), std::forward<decltype(value)>(value));
  auto __res__ = ::llvm::dyn_cast<PortWriteOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

PortWriteOp PortWriteOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value port, ::mlir::Value value) {
  return create(builder, builder.getLoc(), std::forward<decltype(port)>(port), std::forward<decltype(value)>(value));
}

void PortWriteOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value port, ::mlir::Value value) {
  odsState.addOperands(port);
  odsState.addOperands(value);
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

PortWriteOp PortWriteOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value port, ::mlir::Value value) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(port)>(port), std::forward<decltype(value)>(value));
  auto __res__ = ::llvm::dyn_cast<PortWriteOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

PortWriteOp PortWriteOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value port, ::mlir::Value value) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(port)>(port), std::forward<decltype(value)>(value));
}

void PortWriteOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 2u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

PortWriteOp PortWriteOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<PortWriteOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

PortWriteOp PortWriteOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void PortWriteOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 2u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

PortWriteOp PortWriteOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<PortWriteOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

PortWriteOp PortWriteOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult PortWriteOp::verifyInvariantsImpl() {
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Kanagawa3(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSOperands(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Kanagawa5(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  if (!((std::equal_to<>()(llvm::cast<PortRefType>((*this->getODSOperands(0).begin()).getType()).getPortType(), (*this->getODSOperands(1).begin()).getType()))))
    return emitOpError("failed to verify that the inner type of the lhs portref type dictates the rhs type");
  return ::mlir::success();
}

::llvm::LogicalResult PortWriteOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult PortWriteOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::OpAsmParser::UnresolvedOperand portRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> portOperands(&portRawOperand, 1);  ::llvm::SMLoc portOperandsLoc;
  (void)portOperandsLoc;
  ::mlir::OpAsmParser::UnresolvedOperand valueRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> valueOperands(&valueRawOperand, 1);  ::llvm::SMLoc valueOperandsLoc;
  (void)valueOperandsLoc;
  ::mlir::Type portRawType{};
  ::llvm::ArrayRef<::mlir::Type> portTypes(&portRawType, 1);

  portOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(portRawOperand))
    return ::mlir::failure();
  if (parser.parseComma())
    return ::mlir::failure();

  valueOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(valueRawOperand))
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

  if (parser.parseType(portRawType))
    return ::mlir::failure();
  for (::mlir::Type type : portTypes) {
    (void)type;
    if (!((::llvm::isa<::circt::kanagawa::PortRefType>(type)))) {
      return parser.emitError(parser.getNameLoc()) << "'port' must be , but got " << type;
    }
  }
  if (parser.resolveOperands(portOperands, portTypes, portOperandsLoc, result.operands))
    return ::mlir::failure();
  if (parser.resolveOperands(valueOperands, llvm::cast<PortRefType>(portTypes[0]).getPortType(), valueOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void PortWriteOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter << getPort();
  _odsPrinter << ",";
  _odsPrinter << ' ';
  _odsPrinter << getValue();
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
   _odsPrinter << getPort().getType();
}


} // namespace circt::kanagawa
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::kanagawa::PortWriteOp)

namespace circt::kanagawa {


//===----------------------------------------------------------------------===//
// ::circt::kanagawa::ReturnOp definitions
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

::mlir::MutableOperandRange ReturnOp::getRetValuesMutable() {
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

void ReturnOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange retValues) {
  odsState.addOperands(retValues);
}

ReturnOp ReturnOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange retValues) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(retValues)>(retValues));
  auto __res__ = ::llvm::dyn_cast<ReturnOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ReturnOp ReturnOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange retValues) {
  return create(builder, builder.getLoc(), std::forward<decltype(retValues)>(retValues));
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
      if (::mlir::failed(__mlir_ods_local_type_constraint_Kanagawa1(*this, v.getType(), "operand", index++)))
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
  ::llvm::SmallVector<::mlir::OpAsmParser::UnresolvedOperand, 4> retValuesOperands;
  ::llvm::SMLoc retValuesOperandsLoc;
  (void)retValuesOperandsLoc;
  ::llvm::SmallVector<::mlir::Type, 1> retValuesTypes;

  retValuesOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperandList(retValuesOperands))
    return ::mlir::failure();
  if (!retValuesOperands.empty()) {
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

  if (parser.parseTypeList(retValuesTypes))
    return ::mlir::failure();
  }
  if (parser.resolveOperands(retValuesOperands, retValuesTypes, retValuesOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void ReturnOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  if (!getRetValues().empty()) {
    _odsPrinter << ' ';
    _odsPrinter << getRetValues();
  }
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  if (!getRetValues().empty()) {
    _odsPrinter << ' ' << ":";
    _odsPrinter << ' ';
    _odsPrinter << getRetValues().getTypes();
  }
}

void ReturnOp::getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects) {
}


} // namespace circt::kanagawa
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::kanagawa::ReturnOp)

namespace circt::kanagawa {


//===----------------------------------------------------------------------===//
// ::circt::kanagawa::StaticBlockOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

StaticBlockOpGenericAdaptorBase::StaticBlockOpGenericAdaptorBase(StaticBlockOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

std::pair<unsigned, unsigned> StaticBlockOpGenericAdaptorBase::getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
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

::std::optional<uint64_t> StaticBlockOpGenericAdaptorBase::getMaxThreads() {
  auto attr = getMaxThreadsAttr();
  return attr ? ::std::optional<uint64_t>(attr.getValue().getZExtValue()) : (::std::nullopt);
}


} // namespace detail
StaticBlockOpAdaptor::StaticBlockOpAdaptor(StaticBlockOp op) : StaticBlockOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult StaticBlockOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_maxThreads = getProperties().maxThreads; (void)tblgen_maxThreads;

  if (tblgen_maxThreads && !((((::llvm::isa<::mlir::IntegerAttr>(tblgen_maxThreads))) && ((::llvm::cast<::mlir::IntegerAttr>(tblgen_maxThreads).getType().isSignlessInteger(64)))) && ((::llvm::cast<::mlir::IntegerAttr>(tblgen_maxThreads).getInt() >= 1))))
    return emitError(loc, "'kanagawa.sblock' op attribute 'maxThreads' failed to satisfy constraint: 64-bit signless integer attribute whose minimum value is 1");
  return ::mlir::success();
}

std::pair<unsigned, unsigned> StaticBlockOp::getODSOperandIndexAndLength(unsigned index) {
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

::mlir::MutableOperandRange StaticBlockOp::getInputsMutable() {
  auto range = getODSOperandIndexAndLength(0);
  auto mutableRange = ::mlir::MutableOperandRange(getOperation(), range.first, range.second);
  return mutableRange;
}

std::pair<unsigned, unsigned> StaticBlockOp::getODSResultIndexAndLength(unsigned index) {
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

::llvm::LogicalResult StaticBlockOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.maxThreads;
       auto attr = dict.get("maxThreads");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `maxThreads` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  return ::mlir::success();
}

::mlir::Attribute StaticBlockOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.maxThreads;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("maxThreads",
                                       propStorage));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code StaticBlockOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.maxThreads.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> StaticBlockOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "maxThreads")
      return prop.maxThreads;
  return std::nullopt;
}

void StaticBlockOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "maxThreads") {
       prop.maxThreads = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.maxThreads)>>(value);
       return;
    }
}

void StaticBlockOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.maxThreads) attrs.append("maxThreads", prop.maxThreads);
}

::llvm::LogicalResult StaticBlockOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getMaxThreadsAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Kanagawa5(attr, "maxThreads", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult StaticBlockOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readOptionalAttribute(prop.maxThreads)))
    return ::mlir::failure();
  return ::mlir::success();
}

void StaticBlockOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;

  writer.writeOptionalAttribute(prop.maxThreads);
}

::std::optional<uint64_t> StaticBlockOp::getMaxThreads() {
  auto attr = getMaxThreadsAttr();
  return attr ? ::std::optional<uint64_t>(attr.getValue().getZExtValue()) : (::std::nullopt);
}

void StaticBlockOp::setMaxThreads(::std::optional<uint64_t> attrValue) {
    auto &odsProp = getProperties().maxThreads;
    if (attrValue)
      odsProp = ::mlir::Builder((*this)->getContext()).getIntegerAttr(::mlir::Builder((*this)->getContext()).getIntegerType(64), *attrValue);
    else
      odsProp = nullptr;
}

void StaticBlockOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, TypeRange outputs, ValueRange inputs, IntegerAttr maxThreads) {
      odsState.addOperands(inputs);
      if (maxThreads)
        odsState.addAttribute(getMaxThreadsAttrName(odsState.name), maxThreads);
      auto* region = odsState.addRegion();
      odsState.addTypes(outputs);
      ensureTerminator(*region, odsBuilder, odsState.location);
      llvm::SmallVector<Location> argLocs;
      for(auto input : inputs)
        argLocs.push_back(input.getLoc());
      region->front().addArguments(inputs.getTypes(), argLocs);
    
}

StaticBlockOp StaticBlockOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, TypeRange outputs, ValueRange inputs, IntegerAttr maxThreads) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(outputs)>(outputs), std::forward<decltype(inputs)>(inputs), std::forward<decltype(maxThreads)>(maxThreads));
  auto __res__ = ::llvm::dyn_cast<StaticBlockOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

StaticBlockOp StaticBlockOp::create(::mlir::ImplicitLocOpBuilder &builder, TypeRange outputs, ValueRange inputs, IntegerAttr maxThreads) {
  return create(builder, builder.getLoc(), std::forward<decltype(outputs)>(outputs), std::forward<decltype(inputs)>(inputs), std::forward<decltype(maxThreads)>(maxThreads));
}

::llvm::LogicalResult StaticBlockOp::verifyInvariantsImpl() {
  auto tblgen_maxThreads = getProperties().maxThreads; (void)tblgen_maxThreads;

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Kanagawa5(*this, tblgen_maxThreads, "maxThreads")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Kanagawa1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Kanagawa1(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;

    for (auto &region : ::llvm::MutableArrayRef((*this)->getRegion(0)))
      if (::mlir::failed(__mlir_ods_local_region_constraint_Kanagawa1(*this, region, "body", index++)))
        return ::mlir::failure();
  }
  return ::mlir::success();
}

::llvm::LogicalResult StaticBlockOp::verifyInvariants() {
  if(::mlir::succeeded(verifyInvariantsImpl()) && ::mlir::succeeded(verify()))
    return ::mlir::success();
  return ::mlir::failure();
}

::llvm::LogicalResult StaticBlockOp::setPropertiesFromParsedAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
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

    auto &propStorage = prop.maxThreads;
    auto maxThreadsAttrName = ::mlir::StringAttr::get(ctx, "maxThreads");
    auto attr = dict.get(maxThreadsAttrName);
    usedKeys.insert(maxThreadsAttrName);
    if (attr || /*isRequired=*/false) {
      if (!attr) {
        emitError() << "expected key entry for maxThreads in DictionaryAttr to set "
                   "Properties.";
        return ::mlir::failure();
      }
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `maxThreads` in property conversion: " << attr;
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


} // namespace circt::kanagawa
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::kanagawa::StaticBlockOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::kanagawa::detail::StaticBlockOpGenericAdaptorBase::Properties)

namespace circt::kanagawa {


//===----------------------------------------------------------------------===//
// ::circt::kanagawa::VarOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

VarOpGenericAdaptorBase::VarOpGenericAdaptorBase(VarOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::circt::hw::InnerSymAttr VarOpGenericAdaptorBase::getInnerSym() {
  auto attr = getInnerSymAttr();
  return ::llvm::cast<::circt::hw::InnerSymAttr>(attr);
}

MemRefType VarOpGenericAdaptorBase::getType() {
  auto attr = getTypeAttr();
  return ::llvm::cast<MemRefType>(attr.getValue());
}


} // namespace detail
VarOpAdaptor::VarOpAdaptor(VarOp op) : VarOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult VarOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_inner_sym = getProperties().inner_sym; (void)tblgen_inner_sym;
  if (!tblgen_inner_sym) return emitError(loc, "'kanagawa.var' op requires attribute 'inner_sym'");
  auto tblgen_type = getProperties().type; (void)tblgen_type;
  if (!tblgen_type) return emitError(loc, "'kanagawa.var' op requires attribute 'type'");

  if (tblgen_inner_sym && !((::llvm::isa<::circt::hw::InnerSymAttr>(tblgen_inner_sym))))
    return emitError(loc, "'kanagawa.var' op attribute 'inner_sym' failed to satisfy constraint: Inner symbol definition");

  if (tblgen_type && !(((::llvm::isa<::mlir::TypeAttr>(tblgen_type))) && ((::llvm::isa<MemRefType>(::llvm::cast<::mlir::TypeAttr>(tblgen_type).getValue()))) && ((true))))
    return emitError(loc, "'kanagawa.var' op attribute 'type' failed to satisfy constraint: any memref type");
  return ::mlir::success();
}

::llvm::LogicalResult VarOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.inner_sym;
       auto attr = dict.get("inner_sym");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `inner_sym` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.type;
       auto attr = dict.get("type");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `type` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  return ::mlir::success();
}

::mlir::Attribute VarOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.inner_sym;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("inner_sym",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.type;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("type",
                                       propStorage));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code VarOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.inner_sym.getAsOpaquePointer()), 
    llvm::hash_value(prop.type.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> VarOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "inner_sym")
      return prop.inner_sym;

    if (name == "type")
      return prop.type;
  return std::nullopt;
}

void VarOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "inner_sym") {
       prop.inner_sym = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.inner_sym)>>(value);
       return;
    }

    if (name == "type") {
       prop.type = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.type)>>(value);
       return;
    }
}

void VarOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.inner_sym) attrs.append("inner_sym", prop.inner_sym);

    if (prop.type) attrs.append("type", prop.type);
}

::llvm::LogicalResult VarOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getInnerSymAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Kanagawa2(attr, "inner_sym", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getTypeAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Kanagawa12(attr, "type", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult VarOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.inner_sym)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readAttribute(prop.type)))
    return ::mlir::failure();
  return ::mlir::success();
}

void VarOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.inner_sym);
  writer.writeAttribute(prop.type);
}

::circt::hw::InnerSymAttr VarOp::getInnerSym() {
  auto attr = getInnerSymAttr();
  return ::llvm::cast<::circt::hw::InnerSymAttr>(attr);
}

MemRefType VarOp::getType() {
  auto attr = getTypeAttr();
  return ::llvm::cast<MemRefType>(attr.getValue());
}

void VarOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::circt::hw::InnerSymAttr inner_sym, ::mlir::TypeAttr type) {
  odsState.getOrAddProperties<Properties>().inner_sym = inner_sym;
  odsState.getOrAddProperties<Properties>().type = type;
}

VarOp VarOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::circt::hw::InnerSymAttr inner_sym, ::mlir::TypeAttr type) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(inner_sym)>(inner_sym), std::forward<decltype(type)>(type));
  auto __res__ = ::llvm::dyn_cast<VarOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

VarOp VarOp::create(::mlir::ImplicitLocOpBuilder &builder, ::circt::hw::InnerSymAttr inner_sym, ::mlir::TypeAttr type) {
  return create(builder, builder.getLoc(), std::forward<decltype(inner_sym)>(inner_sym), std::forward<decltype(type)>(type));
}

void VarOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::circt::hw::InnerSymAttr inner_sym, ::mlir::TypeAttr type) {
  odsState.getOrAddProperties<Properties>().inner_sym = inner_sym;
  odsState.getOrAddProperties<Properties>().type = type;
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

VarOp VarOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::circt::hw::InnerSymAttr inner_sym, ::mlir::TypeAttr type) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(inner_sym)>(inner_sym), std::forward<decltype(type)>(type));
  auto __res__ = ::llvm::dyn_cast<VarOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

VarOp VarOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::circt::hw::InnerSymAttr inner_sym, ::mlir::TypeAttr type) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(inner_sym)>(inner_sym), std::forward<decltype(type)>(type));
}

void VarOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<VarOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

VarOp VarOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<VarOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

VarOp VarOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void VarOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

VarOp VarOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<VarOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

VarOp VarOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult VarOp::verifyInvariantsImpl() {
  auto tblgen_inner_sym = getProperties().inner_sym; (void)tblgen_inner_sym;
  if (!tblgen_inner_sym) return emitOpError("requires attribute 'inner_sym'");
  auto tblgen_type = getProperties().type; (void)tblgen_type;
  if (!tblgen_type) return emitOpError("requires attribute 'type'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Kanagawa2(*this, tblgen_inner_sym, "inner_sym")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Kanagawa12(*this, tblgen_type, "type")))
    return ::mlir::failure();
  return ::mlir::success();
}

::llvm::LogicalResult VarOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult VarOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::circt::hw::InnerSymAttr inner_symAttr;
  ::mlir::TypeAttr typeAttr;

  if (parser.parseCustomAttributeWithFallback(inner_symAttr, ::mlir::Type{})) {
    return ::mlir::failure();
  }
  if (inner_symAttr) result.getOrAddProperties<VarOp::Properties>().inner_sym = inner_symAttr;
  if (parser.parseColon())
    return ::mlir::failure();

  if (parser.parseCustomAttributeWithFallback(typeAttr, parser.getBuilder().getType<::mlir::NoneType>())) {
    return ::mlir::failure();
  }
  if (typeAttr) result.getOrAddProperties<VarOp::Properties>().type = typeAttr;
  {
    auto loc = parser.getCurrentLocation();(void)loc;
    if (parser.parseOptionalAttrDict(result.attributes))
      return ::mlir::failure();
    if (failed(verifyInherentAttrs(result.name, result.attributes, [&]() {
        return parser.emitError(loc) << "'" << result.name.getStringRef() << "' op ";
      })))
      return ::mlir::failure();
  }
  return ::mlir::success();
}

void VarOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
_odsPrinter.printStrippedAttrOrType(getInnerSymAttr());
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
  _odsPrinter.printAttributeWithoutType(getTypeAttr());
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("inner_sym");
  elidedAttrs.push_back("type");
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
}

// For hw:InnerSymbol - the symbol targets the operation and not any result.
std::optional<size_t> VarOp::getTargetResultIndex() {
  return std::nullopt;
}

} // namespace circt::kanagawa
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::kanagawa::VarOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::kanagawa::detail::VarOpGenericAdaptorBase::Properties)


#endif // GET_OP_CLASSES

