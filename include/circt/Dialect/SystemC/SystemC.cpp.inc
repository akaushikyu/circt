/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Op Definitions                                                             *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: SystemC.td                                                           *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

#ifdef GET_OP_LIST
#undef GET_OP_LIST

::circt::systemc::AssignOp,
::circt::systemc::BindPortOp,
::circt::systemc::CallIndirectOp,
::circt::systemc::CallOp,
::circt::systemc::ConvertOp,
::circt::systemc::CtorOp,
::circt::systemc::DeleteOp,
::circt::systemc::DestructorOp,
::circt::systemc::FuncOp,
::circt::systemc::InstanceDeclOp,
::circt::systemc::InteropVerilatedOp,
::circt::systemc::MemberAccessOp,
::circt::systemc::MethodOp,
::circt::systemc::NewOp,
::circt::systemc::ReturnOp,
::circt::systemc::SCFuncOp,
::circt::systemc::SCModuleOp,
::circt::systemc::SensitiveOp,
::circt::systemc::SignalOp,
::circt::systemc::SignalReadOp,
::circt::systemc::SignalWriteOp,
::circt::systemc::ThreadOp,
::circt::systemc::VariableOp
#endif // GET_OP_LIST

#ifdef GET_OP_CLASSES
#undef GET_OP_CLASSES


//===----------------------------------------------------------------------===//
// Local Utility Method Definitions
//===----------------------------------------------------------------------===//


static ::llvm::LogicalResult __mlir_ods_local_type_constraint_SystemC1(
    ::mlir::Operation *op, ::mlir::Type type, ::llvm::StringRef valueKind,
    unsigned valueIndex) {
  if (!(!((::llvm::isa<::mlir::TokenType>(type))))) {
    return op->emitOpError(valueKind) << " #" << valueIndex
        << " must be any non-token type, but got " << type;
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_type_constraint_SystemC2(
    ::mlir::Operation *op, ::mlir::Type type, ::llvm::StringRef valueKind,
    unsigned valueIndex) {
  if (!((::llvm::isa<::circt::systemc::ModuleType>(type)))) {
    return op->emitOpError(valueKind) << " #" << valueIndex
        << " must be a SystemC module type, but got " << type;
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_type_constraint_SystemC3(
    ::mlir::Operation *op, ::mlir::Type type, ::llvm::StringRef valueKind,
    unsigned valueIndex) {
  if (!(((::llvm::isa<::circt::systemc::InputType>(type))) || ((::llvm::isa<::circt::systemc::InOutType>(type))) || ((::llvm::isa<::circt::systemc::OutputType>(type))) || ((::llvm::isa<::circt::systemc::SignalType>(type))))) {
    return op->emitOpError(valueKind) << " #" << valueIndex
        << " must be a SystemC sc_in<T> type or a SystemC sc_inout<T> type or a SystemC sc_out<T> type or a SystemC sc_signal<T> type, but got " << type;
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_type_constraint_SystemC4(
    ::mlir::Operation *op, ::mlir::Type type, ::llvm::StringRef valueKind,
    unsigned valueIndex) {
  if (!((::llvm::isa<::mlir::FunctionType>(type)))) {
    return op->emitOpError(valueKind) << " #" << valueIndex
        << " must be function type, but got " << type;
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_type_constraint_SystemC5(
    ::mlir::Operation *op, ::mlir::Type type, ::llvm::StringRef valueKind,
    unsigned valueIndex) {
  if (!(!((::llvm::isa<::mlir::TokenType>(type))))) {
    return op->emitOpError(valueKind) << " #" << valueIndex
        << " must be variadic of any non-token type, but got " << type;
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_type_constraint_SystemC6(
    ::mlir::Operation *op, ::mlir::Type type, ::llvm::StringRef valueKind,
    unsigned valueIndex) {
  if (!((((::llvm::isa<::mlir::IntegerType>(type))) || ((::circt::hw::type_isa<circt::systemc::ValueBaseType>(type)))) || (((type.isSignlessInteger())) || ((::circt::hw::type_isa<circt::systemc::BitVectorBaseType>(type))) || ((::circt::hw::type_isa<circt::systemc::BitVectorType>(type))) || ((::circt::hw::type_isa<circt::systemc::LogicVectorBaseType>(type))) || ((::circt::hw::type_isa<circt::systemc::LogicVectorType>(type)))) || ((::llvm::isa<::circt::systemc::LogicType>(type))))) {
    return op->emitOpError(valueKind) << " #" << valueIndex
        << " must be integer or a SystemC sc_value_base type or signless integer or a SystemC sc_bv_base type or a SystemC sc_bv<W> type or a SystemC sc_lv_base type or a SystemC sc_lv<W> type or a SystemC sc_logic type, but got " << type;
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_type_constraint_SystemC7(
    ::mlir::Operation *op, ::mlir::Type type, ::llvm::StringRef valueKind,
    unsigned valueIndex) {
  if (!((::llvm::isa<::mlir::emitc::PointerType>(type)))) {
    return op->emitOpError(valueKind) << " #" << valueIndex
        << " must be EmitC pointer type, but got " << type;
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_type_constraint_SystemC8(
    ::mlir::Operation *op, ::mlir::Type type, ::llvm::StringRef valueKind,
    unsigned valueIndex) {
  if (!(((::circt::hw::type_isa<mlir::FunctionType>(type) && ::circt::hw::type_cast<mlir::FunctionType>(type).getNumInputs() == 0)) && ((::circt::hw::type_isa<mlir::FunctionType>(type) && ::circt::hw::type_cast<mlir::FunctionType>(type).getNumResults() == 0)))) {
    return op->emitOpError(valueKind) << " #" << valueIndex
        << " must be FunctionType with no inputs and results, but got " << type;
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_type_constraint_SystemC9(
    ::mlir::Operation *op, ::mlir::Type type, ::llvm::StringRef valueKind,
    unsigned valueIndex) {
  if (!(((::llvm::isa<::circt::systemc::InputType>(type))) || ((::llvm::isa<::circt::systemc::InOutType>(type))) || ((::llvm::isa<::circt::systemc::OutputType>(type))) || ((::llvm::isa<::circt::systemc::SignalType>(type))))) {
    return op->emitOpError(valueKind) << " #" << valueIndex
        << " must be variadic of a SystemC sc_in<T> type or a SystemC sc_inout<T> type or a SystemC sc_out<T> type or a SystemC sc_signal<T> type, but got " << type;
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_type_constraint_SystemC10(
    ::mlir::Operation *op, ::mlir::Type type, ::llvm::StringRef valueKind,
    unsigned valueIndex) {
  if (!((::llvm::isa<::circt::systemc::SignalType>(type)))) {
    return op->emitOpError(valueKind) << " #" << valueIndex
        << " must be a SystemC sc_signal<T> type, but got " << type;
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_type_constraint_SystemC11(
    ::mlir::Operation *op, ::mlir::Type type, ::llvm::StringRef valueKind,
    unsigned valueIndex) {
  if (!(((::llvm::isa<::circt::systemc::InputType>(type))) || ((::llvm::isa<::circt::systemc::InOutType>(type))) || ((::llvm::isa<::circt::systemc::SignalType>(type))))) {
    return op->emitOpError(valueKind) << " #" << valueIndex
        << " must be a SystemC sc_in<T> type or a SystemC sc_inout<T> type or a SystemC sc_signal<T> type, but got " << type;
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_type_constraint_SystemC12(
    ::mlir::Operation *op, ::mlir::Type type, ::llvm::StringRef valueKind,
    unsigned valueIndex) {
  if (!(((::llvm::isa<::circt::systemc::OutputType>(type))) || ((::llvm::isa<::circt::systemc::InOutType>(type))) || ((::llvm::isa<::circt::systemc::SignalType>(type))))) {
    return op->emitOpError(valueKind) << " #" << valueIndex
        << " must be a SystemC sc_out<T> type or a SystemC sc_inout<T> type or a SystemC sc_signal<T> type, but got " << type;
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_SystemC1(
    ::mlir::Attribute attr, ::llvm::StringRef attrName, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  if (attr && !(((::llvm::isa<::mlir::IntegerAttr>(attr))) && ((::llvm::isa<::mlir::IndexType>(::llvm::cast<::mlir::IntegerAttr>(attr).getType())))))
    return emitError() << "attribute '" << attrName
        << "' failed to satisfy constraint: index attribute";
  return ::mlir::success();
}
static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_SystemC1(
    ::mlir::Operation *op, ::mlir::Attribute attr, ::llvm::StringRef attrName) {
  return __mlir_ods_local_attr_constraint_SystemC1(attr, attrName, [op]() {
    return op->emitOpError();
  });
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_SystemC2(
    ::mlir::Attribute attr, ::llvm::StringRef attrName, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  if (attr && !((::llvm::isa<::mlir::FlatSymbolRefAttr>(attr))))
    return emitError() << "attribute '" << attrName
        << "' failed to satisfy constraint: flat symbol reference attribute";
  return ::mlir::success();
}
static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_SystemC2(
    ::mlir::Operation *op, ::mlir::Attribute attr, ::llvm::StringRef attrName) {
  return __mlir_ods_local_attr_constraint_SystemC2(attr, attrName, [op]() {
    return op->emitOpError();
  });
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_SystemC3(
    ::mlir::Attribute attr, ::llvm::StringRef attrName, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  if (attr && !((::llvm::isa<::mlir::StringAttr>(attr))))
    return emitError() << "attribute '" << attrName
        << "' failed to satisfy constraint: string attribute";
  return ::mlir::success();
}
static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_SystemC3(
    ::mlir::Operation *op, ::mlir::Attribute attr, ::llvm::StringRef attrName) {
  return __mlir_ods_local_attr_constraint_SystemC3(attr, attrName, [op]() {
    return op->emitOpError();
  });
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_SystemC4(
    ::mlir::Attribute attr, ::llvm::StringRef attrName, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  if (attr && !(((::llvm::isa<::mlir::TypeAttr>(attr))) && ((::llvm::isa<::mlir::FunctionType>(::llvm::cast<::mlir::TypeAttr>(attr).getValue()))) && ((::llvm::isa<::mlir::FunctionType>(::llvm::cast<::mlir::TypeAttr>(attr).getValue())))))
    return emitError() << "attribute '" << attrName
        << "' failed to satisfy constraint: type attribute of function type";
  return ::mlir::success();
}
static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_SystemC4(
    ::mlir::Operation *op, ::mlir::Attribute attr, ::llvm::StringRef attrName) {
  return __mlir_ods_local_attr_constraint_SystemC4(attr, attrName, [op]() {
    return op->emitOpError();
  });
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_SystemC5(
    ::mlir::Attribute attr, ::llvm::StringRef attrName, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  if (attr && !(((::llvm::isa<::mlir::ArrayAttr>(attr))) && (::llvm::all_of(::llvm::cast<::mlir::ArrayAttr>(attr), [&](::mlir::Attribute attr) { return attr && ((::llvm::isa<::mlir::DictionaryAttr>(attr))); }))))
    return emitError() << "attribute '" << attrName
        << "' failed to satisfy constraint: Array of dictionary attributes";
  return ::mlir::success();
}
static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_SystemC5(
    ::mlir::Operation *op, ::mlir::Attribute attr, ::llvm::StringRef attrName) {
  return __mlir_ods_local_attr_constraint_SystemC5(attr, attrName, [op]() {
    return op->emitOpError();
  });
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_SystemC6(
    ::mlir::Attribute attr, ::llvm::StringRef attrName, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  if (attr && !(((::llvm::isa<::mlir::ArrayAttr>(attr))) && (::llvm::all_of(::llvm::cast<::mlir::ArrayAttr>(attr), [&](::mlir::Attribute attr) { return attr && ((::llvm::isa<::mlir::StringAttr>(attr))); }))))
    return emitError() << "attribute '" << attrName
        << "' failed to satisfy constraint: string array attribute";
  return ::mlir::success();
}
static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_SystemC6(
    ::mlir::Operation *op, ::mlir::Attribute attr, ::llvm::StringRef attrName) {
  return __mlir_ods_local_attr_constraint_SystemC6(attr, attrName, [op]() {
    return op->emitOpError();
  });
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_SystemC7(
    ::mlir::Attribute attr, ::llvm::StringRef attrName, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  if (attr && !((::llvm::isa<::mlir::UnitAttr>(attr))))
    return emitError() << "attribute '" << attrName
        << "' failed to satisfy constraint: unit attribute";
  return ::mlir::success();
}
static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_SystemC7(
    ::mlir::Operation *op, ::mlir::Attribute attr, ::llvm::StringRef attrName) {
  return __mlir_ods_local_attr_constraint_SystemC7(attr, attrName, [op]() {
    return op->emitOpError();
  });
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_SystemC8(
    ::mlir::Attribute attr, ::llvm::StringRef attrName, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  if (attr && !((::llvm::isa<::MemberAccessKindAttr>(attr))))
    return emitError() << "attribute '" << attrName
        << "' failed to satisfy constraint: C++ member access kind";
  return ::mlir::success();
}
static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_SystemC8(
    ::mlir::Operation *op, ::mlir::Attribute attr, ::llvm::StringRef attrName) {
  return __mlir_ods_local_attr_constraint_SystemC8(attr, attrName, [op]() {
    return op->emitOpError();
  });
}

static ::llvm::LogicalResult __mlir_ods_local_region_constraint_SystemC1(
    ::mlir::Operation *op, ::mlir::Region &region, ::llvm::StringRef regionName,
    unsigned regionIndex) {
  if (!((::llvm::hasNItems(region, 1)))) {
    return op->emitOpError("region #") << regionIndex
        << (regionName.empty() ? " " : " ('" + regionName + "') ")
        << "failed to verify constraint: region with 1 blocks";
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_region_constraint_SystemC2(
    ::mlir::Operation *op, ::mlir::Region &region, ::llvm::StringRef regionName,
    unsigned regionIndex) {
  if (!((true))) {
    return op->emitOpError("region #") << regionIndex
        << (regionName.empty() ? " " : " ('" + regionName + "') ")
        << "failed to verify constraint: any region";
  }
  return ::mlir::success();
}
namespace circt::systemc {


//===----------------------------------------------------------------------===//
// ::circt::systemc::AssignOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

AssignOpGenericAdaptorBase::AssignOpGenericAdaptorBase(AssignOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}


} // namespace detail
AssignOpAdaptor::AssignOpAdaptor(AssignOp op) : AssignOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult AssignOpAdaptor::verify(::mlir::Location loc) {
  return ::mlir::success();
}

::llvm::LogicalResult AssignOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }
      return ::mlir::success();
}

::mlir::Attribute AssignOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code AssignOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine();
}

std::optional<mlir::Attribute> AssignOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
  return std::nullopt;
}

void AssignOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
}

void AssignOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
}

::llvm::LogicalResult AssignOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    return ::mlir::success();
}

void AssignOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value dest, ::mlir::Value source) {
  odsState.addOperands(dest);
  odsState.addOperands(source);
}

AssignOp AssignOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value dest, ::mlir::Value source) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(dest)>(dest), std::forward<decltype(source)>(source));
  auto __res__ = ::llvm::dyn_cast<AssignOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

AssignOp AssignOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value dest, ::mlir::Value source) {
  return create(builder, builder.getLoc(), std::forward<decltype(dest)>(dest), std::forward<decltype(source)>(source));
}

void AssignOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value dest, ::mlir::Value source) {
  odsState.addOperands(dest);
  odsState.addOperands(source);
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

AssignOp AssignOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value dest, ::mlir::Value source) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(dest)>(dest), std::forward<decltype(source)>(source));
  auto __res__ = ::llvm::dyn_cast<AssignOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

AssignOp AssignOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value dest, ::mlir::Value source) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(dest)>(dest), std::forward<decltype(source)>(source));
}

void AssignOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 2u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

AssignOp AssignOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<AssignOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

AssignOp AssignOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void AssignOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 2u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

AssignOp AssignOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<AssignOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

AssignOp AssignOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult AssignOp::verifyInvariantsImpl() {
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_SystemC1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSOperands(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_SystemC1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult AssignOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult AssignOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::OpAsmParser::UnresolvedOperand destRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> destOperands(&destRawOperand, 1);  ::llvm::SMLoc destOperandsLoc;
  (void)destOperandsLoc;
  ::mlir::OpAsmParser::UnresolvedOperand sourceRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> sourceOperands(&sourceRawOperand, 1);  ::llvm::SMLoc sourceOperandsLoc;
  (void)sourceOperandsLoc;
  ::mlir::Type destRawType{};
  ::llvm::ArrayRef<::mlir::Type> destTypes(&destRawType, 1);

  destOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(destRawOperand))
    return ::mlir::failure();
  if (parser.parseEqual())
    return ::mlir::failure();

  sourceOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(sourceRawOperand))
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
    destRawType = type;
  }
  if (parser.resolveOperands(destOperands, destTypes, destOperandsLoc, result.operands))
    return ::mlir::failure();
  if (parser.resolveOperands(sourceOperands, destTypes[0], sourceOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void AssignOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter << getDest();
  _odsPrinter << ' ' << "=";
  _odsPrinter << ' ';
  _odsPrinter << getSource();
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
  {
    auto type = getDest().getType();
    if (auto validType = ::llvm::dyn_cast<::mlir::Type>(type))
      _odsPrinter.printStrippedAttrOrType(validType);
   else
     _odsPrinter << type;
  }
}


} // namespace circt::systemc
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::systemc::AssignOp)

namespace circt::systemc {


//===----------------------------------------------------------------------===//
// ::circt::systemc::BindPortOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

BindPortOpGenericAdaptorBase::BindPortOpGenericAdaptorBase(BindPortOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::llvm::APInt BindPortOpGenericAdaptorBase::getPortId() {
  auto attr = getPortIdAttr();
  return attr.getValue();
}


} // namespace detail
BindPortOpAdaptor::BindPortOpAdaptor(BindPortOp op) : BindPortOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult BindPortOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_portId = getProperties().portId; (void)tblgen_portId;
  if (!tblgen_portId) return emitError(loc, "'systemc.instance.bind_port' op requires attribute 'portId'");

  if (tblgen_portId && !(((::llvm::isa<::mlir::IntegerAttr>(tblgen_portId))) && ((::llvm::isa<::mlir::IndexType>(::llvm::cast<::mlir::IntegerAttr>(tblgen_portId).getType())))))
    return emitError(loc, "'systemc.instance.bind_port' op attribute 'portId' failed to satisfy constraint: index attribute");
  return ::mlir::success();
}

::llvm::LogicalResult BindPortOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.portId;
       auto attr = dict.get("portId");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `portId` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  return ::mlir::success();
}

::mlir::Attribute BindPortOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.portId;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("portId",
                                       propStorage));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code BindPortOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.portId.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> BindPortOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "portId")
      return prop.portId;
  return std::nullopt;
}

void BindPortOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "portId") {
       prop.portId = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.portId)>>(value);
       return;
    }
}

void BindPortOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.portId) attrs.append("portId", prop.portId);
}

::llvm::LogicalResult BindPortOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getPortIdAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_SystemC1(attr, "portId", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult BindPortOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.portId)))
    return ::mlir::failure();
  return ::mlir::success();
}

void BindPortOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.portId);
}

::llvm::APInt BindPortOp::getPortId() {
  auto attr = getPortIdAttr();
  return attr.getValue();
}

void BindPortOp::setPortId(::llvm::APInt attrValue) {
  getProperties().portId = ::mlir::Builder((*this)->getContext()).getIntegerAttr(::mlir::Builder((*this)->getContext()).getIndexType(), attrValue);
}

void BindPortOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value instance, ::mlir::IntegerAttr portId, ::mlir::Value channel) {
  odsState.addOperands(instance);
  odsState.addOperands(channel);
  odsState.getOrAddProperties<Properties>().portId = portId;
}

BindPortOp BindPortOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value instance, ::mlir::IntegerAttr portId, ::mlir::Value channel) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(instance)>(instance), std::forward<decltype(portId)>(portId), std::forward<decltype(channel)>(channel));
  auto __res__ = ::llvm::dyn_cast<BindPortOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

BindPortOp BindPortOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value instance, ::mlir::IntegerAttr portId, ::mlir::Value channel) {
  return create(builder, builder.getLoc(), std::forward<decltype(instance)>(instance), std::forward<decltype(portId)>(portId), std::forward<decltype(channel)>(channel));
}

void BindPortOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value instance, ::mlir::IntegerAttr portId, ::mlir::Value channel) {
  odsState.addOperands(instance);
  odsState.addOperands(channel);
  odsState.getOrAddProperties<Properties>().portId = portId;
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

BindPortOp BindPortOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value instance, ::mlir::IntegerAttr portId, ::mlir::Value channel) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(instance)>(instance), std::forward<decltype(portId)>(portId), std::forward<decltype(channel)>(channel));
  auto __res__ = ::llvm::dyn_cast<BindPortOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

BindPortOp BindPortOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value instance, ::mlir::IntegerAttr portId, ::mlir::Value channel) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(instance)>(instance), std::forward<decltype(portId)>(portId), std::forward<decltype(channel)>(channel));
}

void BindPortOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value instance, ::llvm::APInt portId, ::mlir::Value channel) {
  odsState.addOperands(instance);
  odsState.addOperands(channel);
  odsState.getOrAddProperties<Properties>().portId = odsBuilder.getIntegerAttr(odsBuilder.getIndexType(), portId);
}

BindPortOp BindPortOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value instance, ::llvm::APInt portId, ::mlir::Value channel) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(instance)>(instance), std::forward<decltype(portId)>(portId), std::forward<decltype(channel)>(channel));
  auto __res__ = ::llvm::dyn_cast<BindPortOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

BindPortOp BindPortOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value instance, ::llvm::APInt portId, ::mlir::Value channel) {
  return create(builder, builder.getLoc(), std::forward<decltype(instance)>(instance), std::forward<decltype(portId)>(portId), std::forward<decltype(channel)>(channel));
}

void BindPortOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value instance, ::llvm::APInt portId, ::mlir::Value channel) {
  odsState.addOperands(instance);
  odsState.addOperands(channel);
  odsState.getOrAddProperties<Properties>().portId = odsBuilder.getIntegerAttr(odsBuilder.getIndexType(), portId);
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

BindPortOp BindPortOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value instance, ::llvm::APInt portId, ::mlir::Value channel) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(instance)>(instance), std::forward<decltype(portId)>(portId), std::forward<decltype(channel)>(channel));
  auto __res__ = ::llvm::dyn_cast<BindPortOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

BindPortOp BindPortOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value instance, ::llvm::APInt portId, ::mlir::Value channel) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(instance)>(instance), std::forward<decltype(portId)>(portId), std::forward<decltype(channel)>(channel));
}

void BindPortOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 2u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<BindPortOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

BindPortOp BindPortOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<BindPortOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

BindPortOp BindPortOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void BindPortOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 2u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

BindPortOp BindPortOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<BindPortOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

BindPortOp BindPortOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult BindPortOp::verifyInvariantsImpl() {
  auto tblgen_portId = getProperties().portId; (void)tblgen_portId;
  if (!tblgen_portId) return emitOpError("requires attribute 'portId'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_SystemC1(*this, tblgen_portId, "portId")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_SystemC2(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSOperands(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_SystemC3(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult BindPortOp::verifyInvariants() {
  if(::mlir::succeeded(verifyInvariantsImpl()) && ::mlir::succeeded(verify()))
    return ::mlir::success();
  return ::mlir::failure();
}

::llvm::LogicalResult BindPortOp::setPropertiesFromParsedAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
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

    auto &propStorage = prop.portId;
    auto portIdAttrName = ::mlir::StringAttr::get(ctx, "portId");
    auto attr = dict.get(portIdAttrName);
    usedKeys.insert(portIdAttrName);
    if (attr || /*isRequired=*/true) {
      if (!attr) {
        emitError() << "expected key entry for portId in DictionaryAttr to set "
                   "Properties.";
        return ::mlir::failure();
      }
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `portId` in property conversion: " << attr;
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


} // namespace circt::systemc
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::systemc::BindPortOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::systemc::detail::BindPortOpGenericAdaptorBase::Properties)

namespace circt::systemc {


//===----------------------------------------------------------------------===//
// ::circt::systemc::CallIndirectOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

CallIndirectOpGenericAdaptorBase::CallIndirectOpGenericAdaptorBase(CallIndirectOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

std::pair<unsigned, unsigned> CallIndirectOpGenericAdaptorBase::getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
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


} // namespace detail
CallIndirectOpAdaptor::CallIndirectOpAdaptor(CallIndirectOp op) : CallIndirectOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult CallIndirectOpAdaptor::verify(::mlir::Location loc) {
  return ::mlir::success();
}

std::pair<unsigned, unsigned> CallIndirectOp::getODSOperandIndexAndLength(unsigned index) {
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

::mlir::MutableOperandRange CallIndirectOp::getCalleeOperandsMutable() {
  auto range = getODSOperandIndexAndLength(1);
  auto mutableRange = ::mlir::MutableOperandRange(getOperation(), range.first, range.second);
  return mutableRange;
}

std::pair<unsigned, unsigned> CallIndirectOp::getODSResultIndexAndLength(unsigned index) {
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

::llvm::LogicalResult CallIndirectOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }
      return ::mlir::success();
}

::mlir::Attribute CallIndirectOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code CallIndirectOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine();
}

std::optional<mlir::Attribute> CallIndirectOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
  return std::nullopt;
}

void CallIndirectOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
}

void CallIndirectOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
}

::llvm::LogicalResult CallIndirectOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    return ::mlir::success();
}

void CallIndirectOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value callee, ValueRange operands) {
      odsState.operands.push_back(callee);
      odsState.addOperands(operands);
      odsState.addTypes(llvm::cast<FunctionType>(callee.getType()).getResults());
    
}

CallIndirectOp CallIndirectOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, Value callee, ValueRange operands) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(callee)>(callee), std::forward<decltype(operands)>(operands));
  auto __res__ = ::llvm::dyn_cast<CallIndirectOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

CallIndirectOp CallIndirectOp::create(::mlir::ImplicitLocOpBuilder &builder, Value callee, ValueRange operands) {
  return create(builder, builder.getLoc(), std::forward<decltype(callee)>(callee), std::forward<decltype(operands)>(operands));
}

void CallIndirectOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange results, ::mlir::Value callee, ::mlir::ValueRange callee_operands) {
  odsState.addOperands(callee);
  odsState.addOperands(callee_operands);
  odsState.addTypes(results);
}

CallIndirectOp CallIndirectOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange results, ::mlir::Value callee, ::mlir::ValueRange callee_operands) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(results)>(results), std::forward<decltype(callee)>(callee), std::forward<decltype(callee_operands)>(callee_operands));
  auto __res__ = ::llvm::dyn_cast<CallIndirectOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

CallIndirectOp CallIndirectOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange results, ::mlir::Value callee, ::mlir::ValueRange callee_operands) {
  return create(builder, builder.getLoc(), std::forward<decltype(results)>(results), std::forward<decltype(callee)>(callee), std::forward<decltype(callee_operands)>(callee_operands));
}

void CallIndirectOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() >= 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  odsState.addTypes(resultTypes);
}

CallIndirectOp CallIndirectOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<CallIndirectOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

CallIndirectOp CallIndirectOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void CallIndirectOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() >= 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  odsState.addTypes(resultTypes);
}

CallIndirectOp CallIndirectOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<CallIndirectOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

CallIndirectOp CallIndirectOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult CallIndirectOp::verifyInvariantsImpl() {
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_SystemC4(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSOperands(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_SystemC5(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_SystemC5(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  if (!((std::equal_to<>()(llvm::cast<FunctionType>((*this->getODSOperands(0).begin()).getType()).getInputs(), this->getODSOperands(1).getType()))))
    return emitOpError("failed to verify that callee input types match argument types");
  if (!((std::equal_to<>()(llvm::cast<FunctionType>((*this->getODSOperands(0).begin()).getType()).getResults(), this->getODSResults(0).getType()))))
    return emitOpError("failed to verify that callee result types match result types");
  return ::mlir::success();
}

::llvm::LogicalResult CallIndirectOp::verifyInvariants() {
  if(::mlir::succeeded(verifyInvariantsImpl()) && ::mlir::succeeded(verify()))
    return ::mlir::success();
  return ::mlir::failure();
}

::mlir::ParseResult CallIndirectOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::OpAsmParser::UnresolvedOperand calleeRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> calleeOperands(&calleeRawOperand, 1);  ::llvm::SMLoc calleeOperandsLoc;
  (void)calleeOperandsLoc;
  ::llvm::SmallVector<::mlir::OpAsmParser::UnresolvedOperand, 4> callee_operandsOperands;
  ::llvm::SMLoc callee_operandsOperandsLoc;
  (void)callee_operandsOperandsLoc;
  ::mlir::Type calleeRawType{};
  ::llvm::ArrayRef<::mlir::Type> calleeTypes(&calleeRawType, 1);

  calleeOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(calleeRawOperand))
    return ::mlir::failure();
  if (parser.parseLParen())
    return ::mlir::failure();

  callee_operandsOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperandList(callee_operandsOperands))
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

  {
    ::mlir::FunctionType type;
    if (parser.parseCustomTypeWithFallback(type))
      return ::mlir::failure();
    calleeRawType = type;
  }
  for (::mlir::Type type : calleeTypes) {
    (void)type;
    if (!((::llvm::isa<::mlir::FunctionType>(type)))) {
      return parser.emitError(parser.getNameLoc()) << "'callee' must be function type, but got " << type;
    }
  }
  result.addTypes(llvm::cast<FunctionType>(calleeTypes[0]).getResults());
  if (parser.resolveOperands(calleeOperands, calleeTypes, calleeOperandsLoc, result.operands))
    return ::mlir::failure();
  if (parser.resolveOperands(callee_operandsOperands, llvm::cast<FunctionType>(calleeTypes[0]).getInputs(), callee_operandsOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void CallIndirectOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter << getCallee();
  _odsPrinter << "(";
  _odsPrinter << getCalleeOperands();
  _odsPrinter << ")";
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
  {
    auto type = getCallee().getType();
    if (auto validType = ::llvm::dyn_cast<::mlir::FunctionType>(type))
      _odsPrinter.printStrippedAttrOrType(validType);
   else
     _odsPrinter << type;
  }
}


} // namespace circt::systemc
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::systemc::CallIndirectOp)

namespace circt::systemc {


//===----------------------------------------------------------------------===//
// ::circt::systemc::CallOp definitions
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

::llvm::StringRef CallOpGenericAdaptorBase::getCallee() {
  auto attr = getCalleeAttr();
  return attr.getValue();
}


} // namespace detail
CallOpAdaptor::CallOpAdaptor(CallOp op) : CallOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult CallOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_callee = getProperties().callee; (void)tblgen_callee;
  if (!tblgen_callee) return emitError(loc, "'systemc.cpp.call' op requires attribute 'callee'");

  if (tblgen_callee && !((::llvm::isa<::mlir::FlatSymbolRefAttr>(tblgen_callee))))
    return emitError(loc, "'systemc.cpp.call' op attribute 'callee' failed to satisfy constraint: flat symbol reference attribute");
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

::mlir::MutableOperandRange CallOp::getCalleeOperandsMutable() {
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
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_SystemC2(attr, "callee", emitError)))
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

::llvm::StringRef CallOp::getCallee() {
  auto attr = getCalleeAttr();
  return attr.getValue();
}

void CallOp::setCallee(::llvm::StringRef attrValue) {
  getProperties().callee = ::mlir::SymbolRefAttr::get(::mlir::Builder((*this)->getContext()).getContext(), attrValue);
}

void CallOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, FuncOp callee, ValueRange operands) {
      odsState.addOperands(operands);
      odsState.addAttribute("callee", SymbolRefAttr::get(callee));
      odsState.addTypes(callee.getFunctionType().getResults());
    
}

CallOp CallOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, FuncOp callee, ValueRange operands) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(callee)>(callee), std::forward<decltype(operands)>(operands));
  auto __res__ = ::llvm::dyn_cast<CallOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

CallOp CallOp::create(::mlir::ImplicitLocOpBuilder &builder, FuncOp callee, ValueRange operands) {
  return create(builder, builder.getLoc(), std::forward<decltype(callee)>(callee), std::forward<decltype(operands)>(operands));
}

void CallOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, SymbolRefAttr callee, Type result, ValueRange operands) {
      odsState.addOperands(operands);
      odsState.addAttribute("callee", callee);
      odsState.addTypes(result);
    
}

CallOp CallOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, SymbolRefAttr callee, Type result, ValueRange operands) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(callee)>(callee), std::forward<decltype(result)>(result), std::forward<decltype(operands)>(operands));
  auto __res__ = ::llvm::dyn_cast<CallOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

CallOp CallOp::create(::mlir::ImplicitLocOpBuilder &builder, SymbolRefAttr callee, Type result, ValueRange operands) {
  return create(builder, builder.getLoc(), std::forward<decltype(callee)>(callee), std::forward<decltype(result)>(result), std::forward<decltype(operands)>(operands));
}

void CallOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, StringAttr callee, Type result, ValueRange operands) {
      build(odsBuilder, odsState, SymbolRefAttr::get(callee), result, operands);
    
}

CallOp CallOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, StringAttr callee, Type result, ValueRange operands) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(callee)>(callee), std::forward<decltype(result)>(result), std::forward<decltype(operands)>(operands));
  auto __res__ = ::llvm::dyn_cast<CallOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

CallOp CallOp::create(::mlir::ImplicitLocOpBuilder &builder, StringAttr callee, Type result, ValueRange operands) {
  return create(builder, builder.getLoc(), std::forward<decltype(callee)>(callee), std::forward<decltype(result)>(result), std::forward<decltype(operands)>(operands));
}

void CallOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, StringRef callee, Type result, ValueRange operands) {
      build(odsBuilder, odsState, StringAttr::get(odsBuilder.getContext(), callee),
            result, operands);
    
}

CallOp CallOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, StringRef callee, Type result, ValueRange operands) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(callee)>(callee), std::forward<decltype(result)>(result), std::forward<decltype(operands)>(operands));
  auto __res__ = ::llvm::dyn_cast<CallOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

CallOp CallOp::create(::mlir::ImplicitLocOpBuilder &builder, StringRef callee, Type result, ValueRange operands) {
  return create(builder, builder.getLoc(), std::forward<decltype(callee)>(callee), std::forward<decltype(result)>(result), std::forward<decltype(operands)>(operands));
}

void CallOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange results, ::mlir::FlatSymbolRefAttr callee, ::mlir::ValueRange callee_operands) {
  odsState.addOperands(callee_operands);
  odsState.getOrAddProperties<Properties>().callee = callee;
  odsState.addTypes(results);
}

CallOp CallOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange results, ::mlir::FlatSymbolRefAttr callee, ::mlir::ValueRange callee_operands) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(results)>(results), std::forward<decltype(callee)>(callee), std::forward<decltype(callee_operands)>(callee_operands));
  auto __res__ = ::llvm::dyn_cast<CallOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

CallOp CallOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange results, ::mlir::FlatSymbolRefAttr callee, ::mlir::ValueRange callee_operands) {
  return create(builder, builder.getLoc(), std::forward<decltype(results)>(results), std::forward<decltype(callee)>(callee), std::forward<decltype(callee_operands)>(callee_operands));
}

void CallOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange results, ::llvm::StringRef callee, ::mlir::ValueRange callee_operands) {
  odsState.addOperands(callee_operands);
  odsState.getOrAddProperties<Properties>().callee = ::mlir::SymbolRefAttr::get(odsBuilder.getContext(), callee);
  odsState.addTypes(results);
}

CallOp CallOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange results, ::llvm::StringRef callee, ::mlir::ValueRange callee_operands) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(results)>(results), std::forward<decltype(callee)>(callee), std::forward<decltype(callee_operands)>(callee_operands));
  auto __res__ = ::llvm::dyn_cast<CallOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

CallOp CallOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange results, ::llvm::StringRef callee, ::mlir::ValueRange callee_operands) {
  return create(builder, builder.getLoc(), std::forward<decltype(results)>(results), std::forward<decltype(callee)>(callee), std::forward<decltype(callee_operands)>(callee_operands));
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

  if (::mlir::failed(__mlir_ods_local_attr_constraint_SystemC2(*this, tblgen_callee, "callee")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_SystemC5(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_SystemC5(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult CallOp::verifyInvariants() {
  if(::mlir::succeeded(verifyInvariantsImpl()) && ::mlir::succeeded(verify()))
    return ::mlir::success();
  return ::mlir::failure();
}

::mlir::ParseResult CallOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::FlatSymbolRefAttr calleeAttr;
  ::llvm::SmallVector<::mlir::OpAsmParser::UnresolvedOperand, 4> callee_operandsOperands;
  ::llvm::SMLoc callee_operandsOperandsLoc;
  (void)callee_operandsOperandsLoc;
  ::llvm::ArrayRef<::mlir::Type> callee_operandsTypes;
  ::llvm::ArrayRef<::mlir::Type> resultsTypes;

  if (parser.parseCustomAttributeWithFallback(calleeAttr, parser.getBuilder().getType<::mlir::NoneType>())) {
    return ::mlir::failure();
  }
  if (calleeAttr) result.getOrAddProperties<CallOp::Properties>().callee = calleeAttr;
  if (parser.parseLParen())
    return ::mlir::failure();

  callee_operandsOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperandList(callee_operandsOperands))
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

  ::mlir::FunctionType callee_operands__results_functionType;
  if (parser.parseType(callee_operands__results_functionType))
    return ::mlir::failure();
  callee_operandsTypes = callee_operands__results_functionType.getInputs();
  resultsTypes = callee_operands__results_functionType.getResults();
  result.addTypes(resultsTypes);
  if (parser.resolveOperands(callee_operandsOperands, callee_operandsTypes, callee_operandsOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void CallOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter.printAttributeWithoutType(getCalleeAttr());
  _odsPrinter << "(";
  _odsPrinter << getCalleeOperands();
  _odsPrinter << ")";
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("callee");
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
  _odsPrinter.printFunctionalType(getCalleeOperands().getTypes(), getResults().getTypes());
}


} // namespace circt::systemc
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::systemc::CallOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::systemc::detail::CallOpGenericAdaptorBase::Properties)

namespace circt::systemc {


//===----------------------------------------------------------------------===//
// ::circt::systemc::ConvertOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

ConvertOpGenericAdaptorBase::ConvertOpGenericAdaptorBase(ConvertOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}


} // namespace detail
ConvertOpAdaptor::ConvertOpAdaptor(ConvertOp op) : ConvertOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult ConvertOpAdaptor::verify(::mlir::Location loc) {
  return ::mlir::success();
}

::llvm::LogicalResult ConvertOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }
      return ::mlir::success();
}

::mlir::Attribute ConvertOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code ConvertOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine();
}

std::optional<mlir::Attribute> ConvertOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
  return std::nullopt;
}

void ConvertOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
}

void ConvertOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
}

::llvm::LogicalResult ConvertOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    return ::mlir::success();
}

void ConvertOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value input) {
  odsState.addOperands(input);
  odsState.addTypes(result);
}

ConvertOp ConvertOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value input) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(result)>(result), std::forward<decltype(input)>(input));
  auto __res__ = ::llvm::dyn_cast<ConvertOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ConvertOp ConvertOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value input) {
  return create(builder, builder.getLoc(), std::forward<decltype(result)>(result), std::forward<decltype(input)>(input));
}

void ConvertOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value input) {
  odsState.addOperands(input);
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

ConvertOp ConvertOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value input) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(input)>(input));
  auto __res__ = ::llvm::dyn_cast<ConvertOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ConvertOp ConvertOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value input) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(input)>(input));
}

void ConvertOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

ConvertOp ConvertOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<ConvertOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ConvertOp ConvertOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void ConvertOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

ConvertOp ConvertOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<ConvertOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ConvertOp ConvertOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult ConvertOp::verifyInvariantsImpl() {
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_SystemC6(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_SystemC6(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult ConvertOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult ConvertOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
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

void ConvertOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter << getInput();
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
  _odsPrinter.printFunctionalType(::llvm::ArrayRef<::mlir::Type>(getInput().getType()), ::llvm::ArrayRef<::mlir::Type>(getResult().getType()));
}

void ConvertOp::getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects) {
}


} // namespace circt::systemc
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::systemc::ConvertOp)

namespace circt::systemc {


//===----------------------------------------------------------------------===//
// ::circt::systemc::CtorOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

CtorOpGenericAdaptorBase::CtorOpGenericAdaptorBase(CtorOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}


} // namespace detail
CtorOpAdaptor::CtorOpAdaptor(CtorOp op) : CtorOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult CtorOpAdaptor::verify(::mlir::Location loc) {
  return ::mlir::success();
}

::llvm::LogicalResult CtorOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }
      return ::mlir::success();
}

::mlir::Attribute CtorOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code CtorOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine();
}

std::optional<mlir::Attribute> CtorOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
  return std::nullopt;
}

void CtorOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
}

void CtorOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
}

::llvm::LogicalResult CtorOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    return ::mlir::success();
}

void CtorOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState) {
      Region *region = odsState.addRegion();
      region->push_back(new Block);
    
}

CtorOp CtorOp::create(::mlir::OpBuilder &builder, ::mlir::Location location) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__);
  auto __res__ = ::llvm::dyn_cast<CtorOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

CtorOp CtorOp::create(::mlir::ImplicitLocOpBuilder &builder) {
  return create(builder, builder.getLoc());
}

::llvm::LogicalResult CtorOp::verifyInvariantsImpl() {
  {
    unsigned index = 0; (void)index;

    for (auto &region : ::llvm::MutableArrayRef((*this)->getRegion(0)))
      if (::mlir::failed(__mlir_ods_local_region_constraint_SystemC1(*this, region, "body", index++)))
        return ::mlir::failure();
  }
  return ::mlir::success();
}

::llvm::LogicalResult CtorOp::verifyInvariants() {
  if(::mlir::succeeded(verifyInvariantsImpl()) && ::mlir::succeeded(verify()))
    return ::mlir::success();
  return ::mlir::failure();
}

::mlir::ParseResult CtorOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  std::unique_ptr<::mlir::Region> bodyRegion = std::make_unique<::mlir::Region>();
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

void CtorOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  _odsPrinter.printOptionalAttrDictWithKeyword((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ';
  _odsPrinter.printRegion(getBody());
}


} // namespace circt::systemc
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::systemc::CtorOp)

namespace circt::systemc {


//===----------------------------------------------------------------------===//
// ::circt::systemc::DeleteOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

DeleteOpGenericAdaptorBase::DeleteOpGenericAdaptorBase(DeleteOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}


} // namespace detail
DeleteOpAdaptor::DeleteOpAdaptor(DeleteOp op) : DeleteOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult DeleteOpAdaptor::verify(::mlir::Location loc) {
  return ::mlir::success();
}

::llvm::LogicalResult DeleteOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }
      return ::mlir::success();
}

::mlir::Attribute DeleteOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code DeleteOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine();
}

std::optional<mlir::Attribute> DeleteOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
  return std::nullopt;
}

void DeleteOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
}

void DeleteOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
}

::llvm::LogicalResult DeleteOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    return ::mlir::success();
}

void DeleteOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value pointer) {
  odsState.addOperands(pointer);
}

DeleteOp DeleteOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value pointer) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(pointer)>(pointer));
  auto __res__ = ::llvm::dyn_cast<DeleteOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

DeleteOp DeleteOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value pointer) {
  return create(builder, builder.getLoc(), std::forward<decltype(pointer)>(pointer));
}

void DeleteOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value pointer) {
  odsState.addOperands(pointer);
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

DeleteOp DeleteOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value pointer) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(pointer)>(pointer));
  auto __res__ = ::llvm::dyn_cast<DeleteOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

DeleteOp DeleteOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value pointer) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(pointer)>(pointer));
}

void DeleteOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

DeleteOp DeleteOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<DeleteOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

DeleteOp DeleteOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void DeleteOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

DeleteOp DeleteOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<DeleteOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

DeleteOp DeleteOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult DeleteOp::verifyInvariantsImpl() {
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_SystemC7(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult DeleteOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult DeleteOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::OpAsmParser::UnresolvedOperand pointerRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> pointerOperands(&pointerRawOperand, 1);  ::llvm::SMLoc pointerOperandsLoc;
  (void)pointerOperandsLoc;
  ::mlir::Type pointerRawType{};
  ::llvm::ArrayRef<::mlir::Type> pointerTypes(&pointerRawType, 1);

  pointerOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(pointerRawOperand))
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

  if (parser.parseType(pointerRawType))
    return ::mlir::failure();
  if (parser.resolveOperands(pointerOperands, pointerTypes, pointerOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void DeleteOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter << getPointer();
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
   _odsPrinter << getPointer().getType();
}


} // namespace circt::systemc
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::systemc::DeleteOp)

namespace circt::systemc {


//===----------------------------------------------------------------------===//
// ::circt::systemc::DestructorOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

DestructorOpGenericAdaptorBase::DestructorOpGenericAdaptorBase(DestructorOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}


} // namespace detail
DestructorOpAdaptor::DestructorOpAdaptor(DestructorOp op) : DestructorOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult DestructorOpAdaptor::verify(::mlir::Location loc) {
  return ::mlir::success();
}

::llvm::LogicalResult DestructorOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }
      return ::mlir::success();
}

::mlir::Attribute DestructorOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code DestructorOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine();
}

std::optional<mlir::Attribute> DestructorOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
  return std::nullopt;
}

void DestructorOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
}

void DestructorOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
}

::llvm::LogicalResult DestructorOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    return ::mlir::success();
}

void DestructorOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState) {
      Region *region = odsState.addRegion();
      region->push_back(new Block);
    
}

DestructorOp DestructorOp::create(::mlir::OpBuilder &builder, ::mlir::Location location) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__);
  auto __res__ = ::llvm::dyn_cast<DestructorOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

DestructorOp DestructorOp::create(::mlir::ImplicitLocOpBuilder &builder) {
  return create(builder, builder.getLoc());
}

::llvm::LogicalResult DestructorOp::verifyInvariantsImpl() {
  {
    unsigned index = 0; (void)index;

    for (auto &region : ::llvm::MutableArrayRef((*this)->getRegion(0)))
      if (::mlir::failed(__mlir_ods_local_region_constraint_SystemC1(*this, region, "body", index++)))
        return ::mlir::failure();
  }
  return ::mlir::success();
}

::llvm::LogicalResult DestructorOp::verifyInvariants() {
  if(::mlir::succeeded(verifyInvariantsImpl()) && ::mlir::succeeded(verify()))
    return ::mlir::success();
  return ::mlir::failure();
}

::mlir::ParseResult DestructorOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  std::unique_ptr<::mlir::Region> bodyRegion = std::make_unique<::mlir::Region>();
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

void DestructorOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  _odsPrinter.printOptionalAttrDictWithKeyword((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ';
  _odsPrinter.printRegion(getBody());
}


} // namespace circt::systemc
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::systemc::DestructorOp)

namespace circt::systemc {


//===----------------------------------------------------------------------===//
// ::circt::systemc::FuncOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

FuncOpGenericAdaptorBase::FuncOpGenericAdaptorBase(FuncOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::llvm::StringRef FuncOpGenericAdaptorBase::getSymName() {
  auto attr = getSymNameAttr();
  return attr.getValue();
}

::mlir::FunctionType FuncOpGenericAdaptorBase::getFunctionType() {
  auto attr = getFunctionTypeAttr();
  return ::llvm::cast<::mlir::FunctionType>(attr.getValue());
}

::std::optional< ::mlir::ArrayAttr > FuncOpGenericAdaptorBase::getArgAttrs() {
  auto attr = getArgAttrsAttr();
  return attr ? ::std::optional< ::mlir::ArrayAttr >(attr) : (::std::nullopt);
}

::std::optional< ::mlir::ArrayAttr > FuncOpGenericAdaptorBase::getResAttrs() {
  auto attr = getResAttrsAttr();
  return attr ? ::std::optional< ::mlir::ArrayAttr >(attr) : (::std::nullopt);
}

::mlir::ArrayAttr FuncOpGenericAdaptorBase::getArgNames() {
  auto attr = getArgNamesAttr();
  return attr;
}

::mlir::UnitAttr FuncOpGenericAdaptorBase::getExternCAttr() {
  auto attr = ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(getProperties().externC);
  if (!attr)
    attr = ((false) ? ::mlir::Builder(odsAttrs.getContext()).getUnitAttr() : nullptr);
  return attr;
}

bool FuncOpGenericAdaptorBase::getExternC() {
  auto attr = getExternCAttr();
    if (!attr)
      return ((false) ? ::mlir::Builder(odsAttrs.getContext()).getUnitAttr() : nullptr) != nullptr;
  return attr != nullptr;
}

::std::optional< ::llvm::StringRef > FuncOpGenericAdaptorBase::getSymVisibility() {
  auto attr = getSymVisibilityAttr();
  return attr ? ::std::optional< ::llvm::StringRef >(attr.getValue()) : (::std::nullopt);
}


} // namespace detail
FuncOpAdaptor::FuncOpAdaptor(FuncOp op) : FuncOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult FuncOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_argNames = getProperties().argNames; (void)tblgen_argNames;
  if (!tblgen_argNames) return emitError(loc, "'systemc.cpp.func' op requires attribute 'argNames'");
  auto tblgen_arg_attrs = getProperties().arg_attrs; (void)tblgen_arg_attrs;
  auto tblgen_externC = getProperties().externC; (void)tblgen_externC;
  auto tblgen_function_type = getProperties().function_type; (void)tblgen_function_type;
  if (!tblgen_function_type) return emitError(loc, "'systemc.cpp.func' op requires attribute 'function_type'");
  auto tblgen_res_attrs = getProperties().res_attrs; (void)tblgen_res_attrs;
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;
  if (!tblgen_sym_name) return emitError(loc, "'systemc.cpp.func' op requires attribute 'sym_name'");
  auto tblgen_sym_visibility = getProperties().sym_visibility; (void)tblgen_sym_visibility;

  if (tblgen_sym_name && !((::llvm::isa<::mlir::StringAttr>(tblgen_sym_name))))
    return emitError(loc, "'systemc.cpp.func' op attribute 'sym_name' failed to satisfy constraint: string attribute");

  if (tblgen_function_type && !(((::llvm::isa<::mlir::TypeAttr>(tblgen_function_type))) && ((::llvm::isa<::mlir::FunctionType>(::llvm::cast<::mlir::TypeAttr>(tblgen_function_type).getValue()))) && ((::llvm::isa<::mlir::FunctionType>(::llvm::cast<::mlir::TypeAttr>(tblgen_function_type).getValue())))))
    return emitError(loc, "'systemc.cpp.func' op attribute 'function_type' failed to satisfy constraint: type attribute of function type");

  if (tblgen_arg_attrs && !(((::llvm::isa<::mlir::ArrayAttr>(tblgen_arg_attrs))) && (::llvm::all_of(::llvm::cast<::mlir::ArrayAttr>(tblgen_arg_attrs), [&](::mlir::Attribute attr) { return attr && ((::llvm::isa<::mlir::DictionaryAttr>(attr))); }))))
    return emitError(loc, "'systemc.cpp.func' op attribute 'arg_attrs' failed to satisfy constraint: Array of dictionary attributes");

  if (tblgen_res_attrs && !(((::llvm::isa<::mlir::ArrayAttr>(tblgen_res_attrs))) && (::llvm::all_of(::llvm::cast<::mlir::ArrayAttr>(tblgen_res_attrs), [&](::mlir::Attribute attr) { return attr && ((::llvm::isa<::mlir::DictionaryAttr>(attr))); }))))
    return emitError(loc, "'systemc.cpp.func' op attribute 'res_attrs' failed to satisfy constraint: Array of dictionary attributes");

  if (tblgen_argNames && !(((::llvm::isa<::mlir::ArrayAttr>(tblgen_argNames))) && (::llvm::all_of(::llvm::cast<::mlir::ArrayAttr>(tblgen_argNames), [&](::mlir::Attribute attr) { return attr && ((::llvm::isa<::mlir::StringAttr>(attr))); }))))
    return emitError(loc, "'systemc.cpp.func' op attribute 'argNames' failed to satisfy constraint: string array attribute");

  if (tblgen_externC && !((::llvm::isa<::mlir::UnitAttr>(tblgen_externC))))
    return emitError(loc, "'systemc.cpp.func' op attribute 'externC' failed to satisfy constraint: unit attribute");

  if (tblgen_sym_visibility && !((::llvm::isa<::mlir::StringAttr>(tblgen_sym_visibility))))
    return emitError(loc, "'systemc.cpp.func' op attribute 'sym_visibility' failed to satisfy constraint: string attribute");
  return ::mlir::success();
}

::llvm::LogicalResult FuncOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
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
    auto &propStorage = prop.externC;
       auto attr = dict.get("externC");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `externC` in property conversion: " << attr;
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

  {
    auto &propStorage = prop.sym_visibility;
       auto attr = dict.get("sym_visibility");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `sym_visibility` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  return ::mlir::success();
}

::mlir::Attribute FuncOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
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
      const auto &propStorage = prop.externC;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("externC",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.function_type;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("function_type",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.res_attrs;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("res_attrs",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.sym_name;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("sym_name",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.sym_visibility;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("sym_visibility",
                                       propStorage));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code FuncOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.argNames.getAsOpaquePointer()), 
    llvm::hash_value(prop.arg_attrs.getAsOpaquePointer()), 
    llvm::hash_value(prop.externC.getAsOpaquePointer()), 
    llvm::hash_value(prop.function_type.getAsOpaquePointer()), 
    llvm::hash_value(prop.res_attrs.getAsOpaquePointer()), 
    llvm::hash_value(prop.sym_name.getAsOpaquePointer()), 
    llvm::hash_value(prop.sym_visibility.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> FuncOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "argNames")
      return prop.argNames;

    if (name == "arg_attrs")
      return prop.arg_attrs;

    if (name == "externC")
      return prop.externC;

    if (name == "function_type")
      return prop.function_type;

    if (name == "res_attrs")
      return prop.res_attrs;

    if (name == "sym_name")
      return prop.sym_name;

    if (name == "sym_visibility")
      return prop.sym_visibility;
  return std::nullopt;
}

void FuncOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "argNames") {
       prop.argNames = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.argNames)>>(value);
       return;
    }

    if (name == "arg_attrs") {
       prop.arg_attrs = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.arg_attrs)>>(value);
       return;
    }

    if (name == "externC") {
       prop.externC = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.externC)>>(value);
       return;
    }

    if (name == "function_type") {
       prop.function_type = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.function_type)>>(value);
       return;
    }

    if (name == "res_attrs") {
       prop.res_attrs = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.res_attrs)>>(value);
       return;
    }

    if (name == "sym_name") {
       prop.sym_name = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.sym_name)>>(value);
       return;
    }

    if (name == "sym_visibility") {
       prop.sym_visibility = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.sym_visibility)>>(value);
       return;
    }
}

void FuncOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.argNames) attrs.append("argNames", prop.argNames);

    if (prop.arg_attrs) attrs.append("arg_attrs", prop.arg_attrs);

    if (prop.externC) attrs.append("externC", prop.externC);

    if (prop.function_type) attrs.append("function_type", prop.function_type);

    if (prop.res_attrs) attrs.append("res_attrs", prop.res_attrs);

    if (prop.sym_name) attrs.append("sym_name", prop.sym_name);

    if (prop.sym_visibility) attrs.append("sym_visibility", prop.sym_visibility);
}

::llvm::LogicalResult FuncOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getArgNamesAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_SystemC6(attr, "argNames", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getArgAttrsAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_SystemC5(attr, "arg_attrs", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getExternCAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_SystemC7(attr, "externC", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getFunctionTypeAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_SystemC4(attr, "function_type", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getResAttrsAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_SystemC5(attr, "res_attrs", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getSymNameAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_SystemC3(attr, "sym_name", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getSymVisibilityAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_SystemC3(attr, "sym_visibility", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult FuncOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.argNames)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readOptionalAttribute(prop.arg_attrs)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readOptionalAttribute(prop.externC)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readAttribute(prop.function_type)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readOptionalAttribute(prop.res_attrs)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readAttribute(prop.sym_name)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readOptionalAttribute(prop.sym_visibility)))
    return ::mlir::failure();
  return ::mlir::success();
}

void FuncOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.argNames);

  writer.writeOptionalAttribute(prop.arg_attrs);

  writer.writeOptionalAttribute(prop.externC);
  writer.writeAttribute(prop.function_type);

  writer.writeOptionalAttribute(prop.res_attrs);
  writer.writeAttribute(prop.sym_name);

  writer.writeOptionalAttribute(prop.sym_visibility);
}

::llvm::StringRef FuncOp::getSymName() {
  auto attr = getSymNameAttr();
  return attr.getValue();
}

::mlir::FunctionType FuncOp::getFunctionType() {
  auto attr = getFunctionTypeAttr();
  return ::llvm::cast<::mlir::FunctionType>(attr.getValue());
}

::std::optional< ::mlir::ArrayAttr > FuncOp::getArgAttrs() {
  auto attr = getArgAttrsAttr();
  return attr ? ::std::optional< ::mlir::ArrayAttr >(attr) : (::std::nullopt);
}

::std::optional< ::mlir::ArrayAttr > FuncOp::getResAttrs() {
  auto attr = getResAttrsAttr();
  return attr ? ::std::optional< ::mlir::ArrayAttr >(attr) : (::std::nullopt);
}

::mlir::ArrayAttr FuncOp::getArgNames() {
  auto attr = getArgNamesAttr();
  return attr;
}

bool FuncOp::getExternC() {
  auto attr = getExternCAttr();
    if (!attr)
      return ((false) ? ::mlir::Builder((*this)->getContext()).getUnitAttr() : nullptr) != nullptr;
  return attr != nullptr;
}

::std::optional< ::llvm::StringRef > FuncOp::getSymVisibility() {
  auto attr = getSymVisibilityAttr();
  return attr ? ::std::optional< ::llvm::StringRef >(attr.getValue()) : (::std::nullopt);
}

void FuncOp::setSymName(::llvm::StringRef attrValue) {
  getProperties().sym_name = ::mlir::Builder((*this)->getContext()).getStringAttr(attrValue);
}

void FuncOp::setFunctionType(::mlir::FunctionType attrValue) {
  getProperties().function_type = ::mlir::TypeAttr::get(attrValue);
}

void FuncOp::setExternC(bool attrValue) {
    auto &odsProp = getProperties().externC;
    if (attrValue)
      odsProp = ((attrValue) ? ::mlir::Builder((*this)->getContext()).getUnitAttr() : nullptr);
    else
      odsProp = nullptr;
}

void FuncOp::setSymVisibility(::std::optional<::llvm::StringRef> attrValue) {
    auto &odsProp = getProperties().sym_visibility;
    if (attrValue)
      odsProp = ::mlir::Builder((*this)->getContext()).getStringAttr(*attrValue);
    else
      odsProp = nullptr;
}

FuncOp FuncOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, StringRef name, ArrayAttr argNames, FunctionType type, ArrayRef<NamedAttribute> attrs, ArrayRef<DictionaryAttr> argAttrs) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(name)>(name), std::forward<decltype(argNames)>(argNames), std::forward<decltype(type)>(type), std::forward<decltype(attrs)>(attrs), std::forward<decltype(argAttrs)>(argAttrs));
  auto __res__ = ::llvm::dyn_cast<FuncOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

FuncOp FuncOp::create(::mlir::ImplicitLocOpBuilder &builder, StringRef name, ArrayAttr argNames, FunctionType type, ArrayRef<NamedAttribute> attrs, ArrayRef<DictionaryAttr> argAttrs) {
  return create(builder, builder.getLoc(), std::forward<decltype(name)>(name), std::forward<decltype(argNames)>(argNames), std::forward<decltype(type)>(type), std::forward<decltype(attrs)>(attrs), std::forward<decltype(argAttrs)>(argAttrs));
}

void FuncOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::StringAttr sym_name, ::mlir::TypeAttr function_type, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs, ::mlir::ArrayAttr argNames, /*optional*/::mlir::UnitAttr externC, /*optional*/::mlir::StringAttr sym_visibility) {
  odsState.getOrAddProperties<Properties>().sym_name = sym_name;
  odsState.getOrAddProperties<Properties>().function_type = function_type;
  if (arg_attrs) {
    odsState.getOrAddProperties<Properties>().arg_attrs = arg_attrs;
  }
  if (res_attrs) {
    odsState.getOrAddProperties<Properties>().res_attrs = res_attrs;
  }
  odsState.getOrAddProperties<Properties>().argNames = argNames;
  if (externC) {
    odsState.getOrAddProperties<Properties>().externC = externC;
  }
  if (sym_visibility) {
    odsState.getOrAddProperties<Properties>().sym_visibility = sym_visibility;
  }
  (void)odsState.addRegion();
}

FuncOp FuncOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::StringAttr sym_name, ::mlir::TypeAttr function_type, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs, ::mlir::ArrayAttr argNames, /*optional*/::mlir::UnitAttr externC, /*optional*/::mlir::StringAttr sym_visibility) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(function_type)>(function_type), std::forward<decltype(arg_attrs)>(arg_attrs), std::forward<decltype(res_attrs)>(res_attrs), std::forward<decltype(argNames)>(argNames), std::forward<decltype(externC)>(externC), std::forward<decltype(sym_visibility)>(sym_visibility));
  auto __res__ = ::llvm::dyn_cast<FuncOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

FuncOp FuncOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::StringAttr sym_name, ::mlir::TypeAttr function_type, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs, ::mlir::ArrayAttr argNames, /*optional*/::mlir::UnitAttr externC, /*optional*/::mlir::StringAttr sym_visibility) {
  return create(builder, builder.getLoc(), std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(function_type)>(function_type), std::forward<decltype(arg_attrs)>(arg_attrs), std::forward<decltype(res_attrs)>(res_attrs), std::forward<decltype(argNames)>(argNames), std::forward<decltype(externC)>(externC), std::forward<decltype(sym_visibility)>(sym_visibility));
}

void FuncOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name, ::mlir::TypeAttr function_type, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs, ::mlir::ArrayAttr argNames, /*optional*/::mlir::UnitAttr externC, /*optional*/::mlir::StringAttr sym_visibility) {
  odsState.getOrAddProperties<Properties>().sym_name = sym_name;
  odsState.getOrAddProperties<Properties>().function_type = function_type;
  if (arg_attrs) {
    odsState.getOrAddProperties<Properties>().arg_attrs = arg_attrs;
  }
  if (res_attrs) {
    odsState.getOrAddProperties<Properties>().res_attrs = res_attrs;
  }
  odsState.getOrAddProperties<Properties>().argNames = argNames;
  if (externC) {
    odsState.getOrAddProperties<Properties>().externC = externC;
  }
  if (sym_visibility) {
    odsState.getOrAddProperties<Properties>().sym_visibility = sym_visibility;
  }
  (void)odsState.addRegion();
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

FuncOp FuncOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name, ::mlir::TypeAttr function_type, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs, ::mlir::ArrayAttr argNames, /*optional*/::mlir::UnitAttr externC, /*optional*/::mlir::StringAttr sym_visibility) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(function_type)>(function_type), std::forward<decltype(arg_attrs)>(arg_attrs), std::forward<decltype(res_attrs)>(res_attrs), std::forward<decltype(argNames)>(argNames), std::forward<decltype(externC)>(externC), std::forward<decltype(sym_visibility)>(sym_visibility));
  auto __res__ = ::llvm::dyn_cast<FuncOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

FuncOp FuncOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name, ::mlir::TypeAttr function_type, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs, ::mlir::ArrayAttr argNames, /*optional*/::mlir::UnitAttr externC, /*optional*/::mlir::StringAttr sym_visibility) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(function_type)>(function_type), std::forward<decltype(arg_attrs)>(arg_attrs), std::forward<decltype(res_attrs)>(res_attrs), std::forward<decltype(argNames)>(argNames), std::forward<decltype(externC)>(externC), std::forward<decltype(sym_visibility)>(sym_visibility));
}

void FuncOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::llvm::StringRef sym_name, ::mlir::FunctionType function_type, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs, ::mlir::ArrayAttr argNames, /*optional*/bool externC, /*optional*/::mlir::StringAttr sym_visibility) {
  odsState.getOrAddProperties<Properties>().sym_name = odsBuilder.getStringAttr(sym_name);
  odsState.getOrAddProperties<Properties>().function_type = ::mlir::TypeAttr::get(function_type);
  if (arg_attrs) {
    odsState.getOrAddProperties<Properties>().arg_attrs = arg_attrs;
  }
  if (res_attrs) {
    odsState.getOrAddProperties<Properties>().res_attrs = res_attrs;
  }
  odsState.getOrAddProperties<Properties>().argNames = argNames;
  if (externC) {
    odsState.getOrAddProperties<Properties>().externC = ((externC) ? odsBuilder.getUnitAttr() : nullptr);
  }
  if (sym_visibility) {
    odsState.getOrAddProperties<Properties>().sym_visibility = sym_visibility;
  }
  (void)odsState.addRegion();
}

FuncOp FuncOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::llvm::StringRef sym_name, ::mlir::FunctionType function_type, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs, ::mlir::ArrayAttr argNames, /*optional*/bool externC, /*optional*/::mlir::StringAttr sym_visibility) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(function_type)>(function_type), std::forward<decltype(arg_attrs)>(arg_attrs), std::forward<decltype(res_attrs)>(res_attrs), std::forward<decltype(argNames)>(argNames), std::forward<decltype(externC)>(externC), std::forward<decltype(sym_visibility)>(sym_visibility));
  auto __res__ = ::llvm::dyn_cast<FuncOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

FuncOp FuncOp::create(::mlir::ImplicitLocOpBuilder &builder, ::llvm::StringRef sym_name, ::mlir::FunctionType function_type, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs, ::mlir::ArrayAttr argNames, /*optional*/bool externC, /*optional*/::mlir::StringAttr sym_visibility) {
  return create(builder, builder.getLoc(), std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(function_type)>(function_type), std::forward<decltype(arg_attrs)>(arg_attrs), std::forward<decltype(res_attrs)>(res_attrs), std::forward<decltype(argNames)>(argNames), std::forward<decltype(externC)>(externC), std::forward<decltype(sym_visibility)>(sym_visibility));
}

void FuncOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name, ::mlir::FunctionType function_type, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs, ::mlir::ArrayAttr argNames, /*optional*/bool externC, /*optional*/::mlir::StringAttr sym_visibility) {
  odsState.getOrAddProperties<Properties>().sym_name = odsBuilder.getStringAttr(sym_name);
  odsState.getOrAddProperties<Properties>().function_type = ::mlir::TypeAttr::get(function_type);
  if (arg_attrs) {
    odsState.getOrAddProperties<Properties>().arg_attrs = arg_attrs;
  }
  if (res_attrs) {
    odsState.getOrAddProperties<Properties>().res_attrs = res_attrs;
  }
  odsState.getOrAddProperties<Properties>().argNames = argNames;
  if (externC) {
    odsState.getOrAddProperties<Properties>().externC = ((externC) ? odsBuilder.getUnitAttr() : nullptr);
  }
  if (sym_visibility) {
    odsState.getOrAddProperties<Properties>().sym_visibility = sym_visibility;
  }
  (void)odsState.addRegion();
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

FuncOp FuncOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name, ::mlir::FunctionType function_type, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs, ::mlir::ArrayAttr argNames, /*optional*/bool externC, /*optional*/::mlir::StringAttr sym_visibility) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(function_type)>(function_type), std::forward<decltype(arg_attrs)>(arg_attrs), std::forward<decltype(res_attrs)>(res_attrs), std::forward<decltype(argNames)>(argNames), std::forward<decltype(externC)>(externC), std::forward<decltype(sym_visibility)>(sym_visibility));
  auto __res__ = ::llvm::dyn_cast<FuncOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

FuncOp FuncOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name, ::mlir::FunctionType function_type, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs, ::mlir::ArrayAttr argNames, /*optional*/bool externC, /*optional*/::mlir::StringAttr sym_visibility) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(function_type)>(function_type), std::forward<decltype(arg_attrs)>(arg_attrs), std::forward<decltype(res_attrs)>(res_attrs), std::forward<decltype(argNames)>(argNames), std::forward<decltype(externC)>(externC), std::forward<decltype(sym_visibility)>(sym_visibility));
}

void FuncOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  for (unsigned i = 0; i != 1; ++i)
    (void)odsState.addRegion();
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<FuncOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

FuncOp FuncOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<FuncOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

FuncOp FuncOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void FuncOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  for (unsigned i = 0; i != 1; ++i)
    (void)odsState.addRegion();
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

FuncOp FuncOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<FuncOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

FuncOp FuncOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult FuncOp::verifyInvariantsImpl() {
  auto tblgen_argNames = getProperties().argNames; (void)tblgen_argNames;
  if (!tblgen_argNames) return emitOpError("requires attribute 'argNames'");
  auto tblgen_arg_attrs = getProperties().arg_attrs; (void)tblgen_arg_attrs;
  auto tblgen_externC = getProperties().externC; (void)tblgen_externC;
  auto tblgen_function_type = getProperties().function_type; (void)tblgen_function_type;
  if (!tblgen_function_type) return emitOpError("requires attribute 'function_type'");
  auto tblgen_res_attrs = getProperties().res_attrs; (void)tblgen_res_attrs;
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;
  if (!tblgen_sym_name) return emitOpError("requires attribute 'sym_name'");
  auto tblgen_sym_visibility = getProperties().sym_visibility; (void)tblgen_sym_visibility;

  if (::mlir::failed(__mlir_ods_local_attr_constraint_SystemC3(*this, tblgen_sym_name, "sym_name")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_SystemC4(*this, tblgen_function_type, "function_type")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_SystemC5(*this, tblgen_arg_attrs, "arg_attrs")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_SystemC5(*this, tblgen_res_attrs, "res_attrs")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_SystemC6(*this, tblgen_argNames, "argNames")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_SystemC7(*this, tblgen_externC, "externC")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_SystemC3(*this, tblgen_sym_visibility, "sym_visibility")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;

    for (auto &region : ::llvm::MutableArrayRef((*this)->getRegion(0)))
      if (::mlir::failed(__mlir_ods_local_region_constraint_SystemC2(*this, region, "body", index++)))
        return ::mlir::failure();
  }
  return ::mlir::success();
}

::llvm::LogicalResult FuncOp::verifyInvariants() {
  if(::mlir::succeeded(verifyInvariantsImpl()) && ::mlir::succeeded(verify()))
    return ::mlir::success();
  return ::mlir::failure();
}

::llvm::LogicalResult FuncOp::setPropertiesFromParsedAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
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

    auto &propStorage = prop.sym_name;
    auto sym_nameAttrName = ::mlir::StringAttr::get(ctx, "sym_name");
    auto attr = dict.get(sym_nameAttrName);
    usedKeys.insert(sym_nameAttrName);
    if (attr || /*isRequired=*/true) {
      if (!attr) {
        emitError() << "expected key entry for sym_name in DictionaryAttr to set "
                   "Properties.";
        return ::mlir::failure();
      }
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `sym_name` in property conversion: " << attr;
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

    auto &propStorage = prop.externC;
    auto externCAttrName = ::mlir::StringAttr::get(ctx, "externC");
    auto attr = dict.get(externCAttrName);
    usedKeys.insert(externCAttrName);
    if (attr || /*isRequired=*/false) {
      if (!attr) {
        emitError() << "expected key entry for externC in DictionaryAttr to set "
                   "Properties.";
        return ::mlir::failure();
      }
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `externC` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  {

    auto &propStorage = prop.sym_visibility;
    auto sym_visibilityAttrName = ::mlir::StringAttr::get(ctx, "sym_visibility");
    auto attr = dict.get(sym_visibilityAttrName);
    usedKeys.insert(sym_visibilityAttrName);
    if (attr || /*isRequired=*/false) {
      if (!attr) {
        emitError() << "expected key entry for sym_visibility in DictionaryAttr to set "
                   "Properties.";
        return ::mlir::failure();
      }
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `sym_visibility` in property conversion: " << attr;
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


} // namespace circt::systemc
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::systemc::FuncOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::systemc::detail::FuncOpGenericAdaptorBase::Properties)

namespace circt::systemc {


//===----------------------------------------------------------------------===//
// ::circt::systemc::InstanceDeclOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

InstanceDeclOpGenericAdaptorBase::InstanceDeclOpGenericAdaptorBase(InstanceDeclOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::llvm::StringRef InstanceDeclOpGenericAdaptorBase::getName() {
  auto attr = getNameAttr();
  return attr.getValue();
}

::llvm::StringRef InstanceDeclOpGenericAdaptorBase::getModuleName() {
  auto attr = getModuleNameAttr();
  return attr.getValue();
}


} // namespace detail
InstanceDeclOpAdaptor::InstanceDeclOpAdaptor(InstanceDeclOp op) : InstanceDeclOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult InstanceDeclOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_moduleName = getProperties().moduleName; (void)tblgen_moduleName;
  if (!tblgen_moduleName) return emitError(loc, "'systemc.instance.decl' op requires attribute 'moduleName'");
  auto tblgen_name = getProperties().name; (void)tblgen_name;
  if (!tblgen_name) return emitError(loc, "'systemc.instance.decl' op requires attribute 'name'");

  if (tblgen_name && !((::llvm::isa<::mlir::StringAttr>(tblgen_name))))
    return emitError(loc, "'systemc.instance.decl' op attribute 'name' failed to satisfy constraint: string attribute");

  if (tblgen_moduleName && !((::llvm::isa<::mlir::FlatSymbolRefAttr>(tblgen_moduleName))))
    return emitError(loc, "'systemc.instance.decl' op attribute 'moduleName' failed to satisfy constraint: flat symbol reference attribute");
  return ::mlir::success();
}

::llvm::LogicalResult InstanceDeclOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
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

::mlir::Attribute InstanceDeclOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.moduleName;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("moduleName",
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

llvm::hash_code InstanceDeclOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.moduleName.getAsOpaquePointer()), 
    llvm::hash_value(prop.name.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> InstanceDeclOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "moduleName")
      return prop.moduleName;

    if (name == "name")
      return prop.name;
  return std::nullopt;
}

void InstanceDeclOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "moduleName") {
       prop.moduleName = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.moduleName)>>(value);
       return;
    }

    if (name == "name") {
       prop.name = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.name)>>(value);
       return;
    }
}

void InstanceDeclOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.moduleName) attrs.append("moduleName", prop.moduleName);

    if (prop.name) attrs.append("name", prop.name);
}

::llvm::LogicalResult InstanceDeclOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getModuleNameAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_SystemC2(attr, "moduleName", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getNameAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_SystemC3(attr, "name", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult InstanceDeclOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.moduleName)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readAttribute(prop.name)))
    return ::mlir::failure();
  return ::mlir::success();
}

void InstanceDeclOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.moduleName);
  writer.writeAttribute(prop.name);
}

::llvm::StringRef InstanceDeclOp::getName() {
  auto attr = getNameAttr();
  return attr.getValue();
}

::llvm::StringRef InstanceDeclOp::getModuleName() {
  auto attr = getModuleNameAttr();
  return attr.getValue();
}

void InstanceDeclOp::setName(::llvm::StringRef attrValue) {
  getProperties().name = ::mlir::Builder((*this)->getContext()).getStringAttr(attrValue);
}

void InstanceDeclOp::setModuleName(::llvm::StringRef attrValue) {
  getProperties().moduleName = ::mlir::SymbolRefAttr::get(::mlir::Builder((*this)->getContext()).getContext(), attrValue);
}

void InstanceDeclOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, StringAttr instanceName, FlatSymbolRefAttr moduleRef, ArrayRef<ModuleType::PortInfo> ports) {
      build(odsBuilder, odsState,
            ModuleType::get(odsBuilder.getContext(), moduleRef.getAttr(), ports),
            instanceName, moduleRef);
    
}

InstanceDeclOp InstanceDeclOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, StringAttr instanceName, FlatSymbolRefAttr moduleRef, ArrayRef<ModuleType::PortInfo> ports) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(instanceName)>(instanceName), std::forward<decltype(moduleRef)>(moduleRef), std::forward<decltype(ports)>(ports));
  auto __res__ = ::llvm::dyn_cast<InstanceDeclOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

InstanceDeclOp InstanceDeclOp::create(::mlir::ImplicitLocOpBuilder &builder, StringAttr instanceName, FlatSymbolRefAttr moduleRef, ArrayRef<ModuleType::PortInfo> ports) {
  return create(builder, builder.getLoc(), std::forward<decltype(instanceName)>(instanceName), std::forward<decltype(moduleRef)>(moduleRef), std::forward<decltype(ports)>(ports));
}

void InstanceDeclOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type instanceHandle, ::mlir::StringAttr name, ::mlir::FlatSymbolRefAttr moduleName) {
  odsState.getOrAddProperties<Properties>().name = name;
  odsState.getOrAddProperties<Properties>().moduleName = moduleName;
  odsState.addTypes(instanceHandle);
}

InstanceDeclOp InstanceDeclOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type instanceHandle, ::mlir::StringAttr name, ::mlir::FlatSymbolRefAttr moduleName) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(instanceHandle)>(instanceHandle), std::forward<decltype(name)>(name), std::forward<decltype(moduleName)>(moduleName));
  auto __res__ = ::llvm::dyn_cast<InstanceDeclOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

InstanceDeclOp InstanceDeclOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type instanceHandle, ::mlir::StringAttr name, ::mlir::FlatSymbolRefAttr moduleName) {
  return create(builder, builder.getLoc(), std::forward<decltype(instanceHandle)>(instanceHandle), std::forward<decltype(name)>(name), std::forward<decltype(moduleName)>(moduleName));
}

void InstanceDeclOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::StringAttr name, ::mlir::FlatSymbolRefAttr moduleName) {
  odsState.getOrAddProperties<Properties>().name = name;
  odsState.getOrAddProperties<Properties>().moduleName = moduleName;
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

InstanceDeclOp InstanceDeclOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::StringAttr name, ::mlir::FlatSymbolRefAttr moduleName) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(name)>(name), std::forward<decltype(moduleName)>(moduleName));
  auto __res__ = ::llvm::dyn_cast<InstanceDeclOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

InstanceDeclOp InstanceDeclOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::StringAttr name, ::mlir::FlatSymbolRefAttr moduleName) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(name)>(name), std::forward<decltype(moduleName)>(moduleName));
}

void InstanceDeclOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type instanceHandle, ::llvm::StringRef name, ::llvm::StringRef moduleName) {
  odsState.getOrAddProperties<Properties>().name = odsBuilder.getStringAttr(name);
  odsState.getOrAddProperties<Properties>().moduleName = ::mlir::SymbolRefAttr::get(odsBuilder.getContext(), moduleName);
  odsState.addTypes(instanceHandle);
}

InstanceDeclOp InstanceDeclOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type instanceHandle, ::llvm::StringRef name, ::llvm::StringRef moduleName) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(instanceHandle)>(instanceHandle), std::forward<decltype(name)>(name), std::forward<decltype(moduleName)>(moduleName));
  auto __res__ = ::llvm::dyn_cast<InstanceDeclOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

InstanceDeclOp InstanceDeclOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type instanceHandle, ::llvm::StringRef name, ::llvm::StringRef moduleName) {
  return create(builder, builder.getLoc(), std::forward<decltype(instanceHandle)>(instanceHandle), std::forward<decltype(name)>(name), std::forward<decltype(moduleName)>(moduleName));
}

void InstanceDeclOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::llvm::StringRef name, ::llvm::StringRef moduleName) {
  odsState.getOrAddProperties<Properties>().name = odsBuilder.getStringAttr(name);
  odsState.getOrAddProperties<Properties>().moduleName = ::mlir::SymbolRefAttr::get(odsBuilder.getContext(), moduleName);
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

InstanceDeclOp InstanceDeclOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::llvm::StringRef name, ::llvm::StringRef moduleName) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(name)>(name), std::forward<decltype(moduleName)>(moduleName));
  auto __res__ = ::llvm::dyn_cast<InstanceDeclOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

InstanceDeclOp InstanceDeclOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::llvm::StringRef name, ::llvm::StringRef moduleName) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(name)>(name), std::forward<decltype(moduleName)>(moduleName));
}

void InstanceDeclOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<InstanceDeclOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

InstanceDeclOp InstanceDeclOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<InstanceDeclOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

InstanceDeclOp InstanceDeclOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void InstanceDeclOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

InstanceDeclOp InstanceDeclOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<InstanceDeclOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

InstanceDeclOp InstanceDeclOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult InstanceDeclOp::verifyInvariantsImpl() {
  auto tblgen_moduleName = getProperties().moduleName; (void)tblgen_moduleName;
  if (!tblgen_moduleName) return emitOpError("requires attribute 'moduleName'");
  auto tblgen_name = getProperties().name; (void)tblgen_name;
  if (!tblgen_name) return emitOpError("requires attribute 'name'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_SystemC3(*this, tblgen_name, "name")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_SystemC2(*this, tblgen_moduleName, "moduleName")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_SystemC2(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult InstanceDeclOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult InstanceDeclOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::StringAttr nameAttr;
  ::mlir::FlatSymbolRefAttr moduleNameAttr;
  ::mlir::Type instanceHandleRawType{};
  ::llvm::ArrayRef<::mlir::Type> instanceHandleTypes(&instanceHandleRawType, 1);
  {
    auto odsResult = parseImplicitSSAName(parser, nameAttr);
    if (odsResult) return ::mlir::failure();
    result.getOrAddProperties<InstanceDeclOp::Properties>().name = nameAttr;
  }

  if (parser.parseCustomAttributeWithFallback(moduleNameAttr, parser.getBuilder().getType<::mlir::NoneType>())) {
    return ::mlir::failure();
  }
  if (moduleNameAttr) result.getOrAddProperties<InstanceDeclOp::Properties>().moduleName = moduleNameAttr;
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

  if (parser.parseType(instanceHandleRawType))
    return ::mlir::failure();
  result.addTypes(instanceHandleTypes);
  return ::mlir::success();
}

void InstanceDeclOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  printImplicitSSAName(_odsPrinter, *this, getNameAttr());
  _odsPrinter << ' ';
  _odsPrinter.printAttributeWithoutType(getModuleNameAttr());
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("name");
  elidedAttrs.push_back("moduleName");
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
   _odsPrinter << getInstanceHandle().getType();
}


} // namespace circt::systemc
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::systemc::InstanceDeclOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::systemc::detail::InstanceDeclOpGenericAdaptorBase::Properties)

namespace circt::systemc {


//===----------------------------------------------------------------------===//
// ::circt::systemc::InteropVerilatedOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

InteropVerilatedOpGenericAdaptorBase::InteropVerilatedOpGenericAdaptorBase(InteropVerilatedOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

std::pair<unsigned, unsigned> InteropVerilatedOpGenericAdaptorBase::getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
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

::llvm::StringRef InteropVerilatedOpGenericAdaptorBase::getInstanceName() {
  auto attr = getInstanceNameAttr();
  return attr.getValue();
}

::llvm::StringRef InteropVerilatedOpGenericAdaptorBase::getModuleName() {
  auto attr = getModuleNameAttr();
  return attr.getValue();
}

::mlir::ArrayAttr InteropVerilatedOpGenericAdaptorBase::getInputNames() {
  auto attr = getInputNamesAttr();
  return attr;
}

::mlir::ArrayAttr InteropVerilatedOpGenericAdaptorBase::getResultNames() {
  auto attr = getResultNamesAttr();
  return attr;
}


} // namespace detail
InteropVerilatedOpAdaptor::InteropVerilatedOpAdaptor(InteropVerilatedOp op) : InteropVerilatedOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult InteropVerilatedOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_inputNames = getProperties().inputNames; (void)tblgen_inputNames;
  if (!tblgen_inputNames) return emitError(loc, "'systemc.interop.verilated' op requires attribute 'inputNames'");
  auto tblgen_instanceName = getProperties().instanceName; (void)tblgen_instanceName;
  if (!tblgen_instanceName) return emitError(loc, "'systemc.interop.verilated' op requires attribute 'instanceName'");
  auto tblgen_moduleName = getProperties().moduleName; (void)tblgen_moduleName;
  if (!tblgen_moduleName) return emitError(loc, "'systemc.interop.verilated' op requires attribute 'moduleName'");
  auto tblgen_resultNames = getProperties().resultNames; (void)tblgen_resultNames;
  if (!tblgen_resultNames) return emitError(loc, "'systemc.interop.verilated' op requires attribute 'resultNames'");

  if (tblgen_instanceName && !((::llvm::isa<::mlir::StringAttr>(tblgen_instanceName))))
    return emitError(loc, "'systemc.interop.verilated' op attribute 'instanceName' failed to satisfy constraint: string attribute");

  if (tblgen_moduleName && !((::llvm::isa<::mlir::FlatSymbolRefAttr>(tblgen_moduleName))))
    return emitError(loc, "'systemc.interop.verilated' op attribute 'moduleName' failed to satisfy constraint: flat symbol reference attribute");

  if (tblgen_inputNames && !(((::llvm::isa<::mlir::ArrayAttr>(tblgen_inputNames))) && (::llvm::all_of(::llvm::cast<::mlir::ArrayAttr>(tblgen_inputNames), [&](::mlir::Attribute attr) { return attr && ((::llvm::isa<::mlir::StringAttr>(attr))); }))))
    return emitError(loc, "'systemc.interop.verilated' op attribute 'inputNames' failed to satisfy constraint: string array attribute");

  if (tblgen_resultNames && !(((::llvm::isa<::mlir::ArrayAttr>(tblgen_resultNames))) && (::llvm::all_of(::llvm::cast<::mlir::ArrayAttr>(tblgen_resultNames), [&](::mlir::Attribute attr) { return attr && ((::llvm::isa<::mlir::StringAttr>(attr))); }))))
    return emitError(loc, "'systemc.interop.verilated' op attribute 'resultNames' failed to satisfy constraint: string array attribute");
  return ::mlir::success();
}

std::pair<unsigned, unsigned> InteropVerilatedOp::getODSOperandIndexAndLength(unsigned index) {
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

::mlir::MutableOperandRange InteropVerilatedOp::getInputsMutable() {
  auto range = getODSOperandIndexAndLength(0);
  auto mutableRange = ::mlir::MutableOperandRange(getOperation(), range.first, range.second);
  return mutableRange;
}

std::pair<unsigned, unsigned> InteropVerilatedOp::getODSResultIndexAndLength(unsigned index) {
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

::llvm::LogicalResult InteropVerilatedOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
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

  {
    auto &propStorage = prop.resultNames;
       auto attr = dict.get("resultNames");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `resultNames` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  return ::mlir::success();
}

::mlir::Attribute InteropVerilatedOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.inputNames;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("inputNames",
                                       propStorage));
    }

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

    {
      const auto &propStorage = prop.resultNames;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("resultNames",
                                       propStorage));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code InteropVerilatedOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.inputNames.getAsOpaquePointer()), 
    llvm::hash_value(prop.instanceName.getAsOpaquePointer()), 
    llvm::hash_value(prop.moduleName.getAsOpaquePointer()), 
    llvm::hash_value(prop.resultNames.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> InteropVerilatedOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "inputNames")
      return prop.inputNames;

    if (name == "instanceName")
      return prop.instanceName;

    if (name == "moduleName")
      return prop.moduleName;

    if (name == "resultNames")
      return prop.resultNames;
  return std::nullopt;
}

void InteropVerilatedOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "inputNames") {
       prop.inputNames = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.inputNames)>>(value);
       return;
    }

    if (name == "instanceName") {
       prop.instanceName = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.instanceName)>>(value);
       return;
    }

    if (name == "moduleName") {
       prop.moduleName = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.moduleName)>>(value);
       return;
    }

    if (name == "resultNames") {
       prop.resultNames = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.resultNames)>>(value);
       return;
    }
}

void InteropVerilatedOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.inputNames) attrs.append("inputNames", prop.inputNames);

    if (prop.instanceName) attrs.append("instanceName", prop.instanceName);

    if (prop.moduleName) attrs.append("moduleName", prop.moduleName);

    if (prop.resultNames) attrs.append("resultNames", prop.resultNames);
}

::llvm::LogicalResult InteropVerilatedOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getInputNamesAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_SystemC6(attr, "inputNames", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getInstanceNameAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_SystemC3(attr, "instanceName", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getModuleNameAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_SystemC2(attr, "moduleName", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getResultNamesAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_SystemC6(attr, "resultNames", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult InteropVerilatedOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.inputNames)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readAttribute(prop.instanceName)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readAttribute(prop.moduleName)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readAttribute(prop.resultNames)))
    return ::mlir::failure();
  return ::mlir::success();
}

void InteropVerilatedOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.inputNames);
  writer.writeAttribute(prop.instanceName);
  writer.writeAttribute(prop.moduleName);
  writer.writeAttribute(prop.resultNames);
}

::llvm::StringRef InteropVerilatedOp::getInstanceName() {
  auto attr = getInstanceNameAttr();
  return attr.getValue();
}

::llvm::StringRef InteropVerilatedOp::getModuleName() {
  auto attr = getModuleNameAttr();
  return attr.getValue();
}

::mlir::ArrayAttr InteropVerilatedOp::getInputNames() {
  auto attr = getInputNamesAttr();
  return attr;
}

::mlir::ArrayAttr InteropVerilatedOp::getResultNames() {
  auto attr = getResultNamesAttr();
  return attr;
}

void InteropVerilatedOp::setInstanceName(::llvm::StringRef attrValue) {
  getProperties().instanceName = ::mlir::Builder((*this)->getContext()).getStringAttr(attrValue);
}

void InteropVerilatedOp::setModuleName(::llvm::StringRef attrValue) {
  getProperties().moduleName = ::mlir::SymbolRefAttr::get(::mlir::Builder((*this)->getContext()).getContext(), attrValue);
}

InteropVerilatedOp InteropVerilatedOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, Operation*module, StringAttr name, ArrayRef<Value> inputs) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(module)>(module), std::forward<decltype(name)>(name), std::forward<decltype(inputs)>(inputs));
  auto __res__ = ::llvm::dyn_cast<InteropVerilatedOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

InteropVerilatedOp InteropVerilatedOp::create(::mlir::ImplicitLocOpBuilder &builder, Operation*module, StringAttr name, ArrayRef<Value> inputs) {
  return create(builder, builder.getLoc(), std::forward<decltype(module)>(module), std::forward<decltype(name)>(name), std::forward<decltype(inputs)>(inputs));
}

void InteropVerilatedOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Operation*module, StringRef name, ArrayRef<Value> inputs) {
      build(odsBuilder, odsState, module, odsBuilder.getStringAttr(name), inputs);
    
}

InteropVerilatedOp InteropVerilatedOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, Operation*module, StringRef name, ArrayRef<Value> inputs) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(module)>(module), std::forward<decltype(name)>(name), std::forward<decltype(inputs)>(inputs));
  auto __res__ = ::llvm::dyn_cast<InteropVerilatedOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

InteropVerilatedOp InteropVerilatedOp::create(::mlir::ImplicitLocOpBuilder &builder, Operation*module, StringRef name, ArrayRef<Value> inputs) {
  return create(builder, builder.getLoc(), std::forward<decltype(module)>(module), std::forward<decltype(name)>(name), std::forward<decltype(inputs)>(inputs));
}

void InteropVerilatedOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange results, ::mlir::StringAttr instanceName, ::mlir::FlatSymbolRefAttr moduleName, ::mlir::ArrayAttr inputNames, ::mlir::ArrayAttr resultNames, ::mlir::ValueRange inputs) {
  odsState.addOperands(inputs);
  odsState.getOrAddProperties<Properties>().instanceName = instanceName;
  odsState.getOrAddProperties<Properties>().moduleName = moduleName;
  odsState.getOrAddProperties<Properties>().inputNames = inputNames;
  odsState.getOrAddProperties<Properties>().resultNames = resultNames;
  odsState.addTypes(results);
}

InteropVerilatedOp InteropVerilatedOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange results, ::mlir::StringAttr instanceName, ::mlir::FlatSymbolRefAttr moduleName, ::mlir::ArrayAttr inputNames, ::mlir::ArrayAttr resultNames, ::mlir::ValueRange inputs) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(results)>(results), std::forward<decltype(instanceName)>(instanceName), std::forward<decltype(moduleName)>(moduleName), std::forward<decltype(inputNames)>(inputNames), std::forward<decltype(resultNames)>(resultNames), std::forward<decltype(inputs)>(inputs));
  auto __res__ = ::llvm::dyn_cast<InteropVerilatedOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

InteropVerilatedOp InteropVerilatedOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange results, ::mlir::StringAttr instanceName, ::mlir::FlatSymbolRefAttr moduleName, ::mlir::ArrayAttr inputNames, ::mlir::ArrayAttr resultNames, ::mlir::ValueRange inputs) {
  return create(builder, builder.getLoc(), std::forward<decltype(results)>(results), std::forward<decltype(instanceName)>(instanceName), std::forward<decltype(moduleName)>(moduleName), std::forward<decltype(inputNames)>(inputNames), std::forward<decltype(resultNames)>(resultNames), std::forward<decltype(inputs)>(inputs));
}

void InteropVerilatedOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange results, ::llvm::StringRef instanceName, ::llvm::StringRef moduleName, ::mlir::ArrayAttr inputNames, ::mlir::ArrayAttr resultNames, ::mlir::ValueRange inputs) {
  odsState.addOperands(inputs);
  odsState.getOrAddProperties<Properties>().instanceName = odsBuilder.getStringAttr(instanceName);
  odsState.getOrAddProperties<Properties>().moduleName = ::mlir::SymbolRefAttr::get(odsBuilder.getContext(), moduleName);
  odsState.getOrAddProperties<Properties>().inputNames = inputNames;
  odsState.getOrAddProperties<Properties>().resultNames = resultNames;
  odsState.addTypes(results);
}

InteropVerilatedOp InteropVerilatedOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange results, ::llvm::StringRef instanceName, ::llvm::StringRef moduleName, ::mlir::ArrayAttr inputNames, ::mlir::ArrayAttr resultNames, ::mlir::ValueRange inputs) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(results)>(results), std::forward<decltype(instanceName)>(instanceName), std::forward<decltype(moduleName)>(moduleName), std::forward<decltype(inputNames)>(inputNames), std::forward<decltype(resultNames)>(resultNames), std::forward<decltype(inputs)>(inputs));
  auto __res__ = ::llvm::dyn_cast<InteropVerilatedOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

InteropVerilatedOp InteropVerilatedOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange results, ::llvm::StringRef instanceName, ::llvm::StringRef moduleName, ::mlir::ArrayAttr inputNames, ::mlir::ArrayAttr resultNames, ::mlir::ValueRange inputs) {
  return create(builder, builder.getLoc(), std::forward<decltype(results)>(results), std::forward<decltype(instanceName)>(instanceName), std::forward<decltype(moduleName)>(moduleName), std::forward<decltype(inputNames)>(inputNames), std::forward<decltype(resultNames)>(resultNames), std::forward<decltype(inputs)>(inputs));
}

void InteropVerilatedOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<InteropVerilatedOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

InteropVerilatedOp InteropVerilatedOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<InteropVerilatedOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

InteropVerilatedOp InteropVerilatedOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void InteropVerilatedOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  odsState.addTypes(resultTypes);
}

InteropVerilatedOp InteropVerilatedOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<InteropVerilatedOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

InteropVerilatedOp InteropVerilatedOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult InteropVerilatedOp::verifyInvariantsImpl() {
  auto tblgen_inputNames = getProperties().inputNames; (void)tblgen_inputNames;
  if (!tblgen_inputNames) return emitOpError("requires attribute 'inputNames'");
  auto tblgen_instanceName = getProperties().instanceName; (void)tblgen_instanceName;
  if (!tblgen_instanceName) return emitOpError("requires attribute 'instanceName'");
  auto tblgen_moduleName = getProperties().moduleName; (void)tblgen_moduleName;
  if (!tblgen_moduleName) return emitOpError("requires attribute 'moduleName'");
  auto tblgen_resultNames = getProperties().resultNames; (void)tblgen_resultNames;
  if (!tblgen_resultNames) return emitOpError("requires attribute 'resultNames'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_SystemC3(*this, tblgen_instanceName, "instanceName")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_SystemC2(*this, tblgen_moduleName, "moduleName")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_SystemC6(*this, tblgen_inputNames, "inputNames")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_SystemC6(*this, tblgen_resultNames, "resultNames")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_SystemC5(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_SystemC5(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult InteropVerilatedOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult InteropVerilatedOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::StringAttr instanceNameAttr;
  ::mlir::FlatSymbolRefAttr moduleNameAttr;
  ::llvm::SmallVector<::mlir::OpAsmParser::UnresolvedOperand, 4> inputsOperands;
  ::llvm::SMLoc inputsOperandsLoc;
  (void)inputsOperandsLoc;
  ::llvm::SmallVector<::mlir::Type, 1> inputsTypes;
  ::mlir::ArrayAttr inputNamesAttr;
  ::llvm::SmallVector<::mlir::Type, 1> resultsTypes;
  ::mlir::ArrayAttr resultNamesAttr;

  if (parser.parseCustomAttributeWithFallback(instanceNameAttr, parser.getBuilder().getType<::mlir::NoneType>())) {
    return ::mlir::failure();
  }
  if (instanceNameAttr) result.getOrAddProperties<InteropVerilatedOp::Properties>().instanceName = instanceNameAttr;

  if (parser.parseCustomAttributeWithFallback(moduleNameAttr, parser.getBuilder().getType<::mlir::NoneType>())) {
    return ::mlir::failure();
  }
  if (moduleNameAttr) result.getOrAddProperties<InteropVerilatedOp::Properties>().moduleName = moduleNameAttr;
  {
    inputsOperandsLoc = parser.getCurrentLocation();
    auto odsResult = parseInputPortList(parser, inputsOperands, inputsTypes, inputNamesAttr);
    if (odsResult) return ::mlir::failure();
    result.getOrAddProperties<InteropVerilatedOp::Properties>().inputNames = inputNamesAttr;
  }
  if (parser.parseArrow())
    return ::mlir::failure();
  {
    auto odsResult = parseOutputPortList(parser, resultsTypes, resultNamesAttr);
    if (odsResult) return ::mlir::failure();
    result.getOrAddProperties<InteropVerilatedOp::Properties>().resultNames = resultNamesAttr;
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
  result.addTypes(resultsTypes);
  if (parser.resolveOperands(inputsOperands, inputsTypes, inputsOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void InteropVerilatedOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter.printAttributeWithoutType(getInstanceNameAttr());
  _odsPrinter << ' ';
  _odsPrinter.printAttributeWithoutType(getModuleNameAttr());
  _odsPrinter << ' ';
  printInputPortList(_odsPrinter, *this, getInputs(), getInputs().getTypes(), getInputNamesAttr());
  _odsPrinter << ' ' << "->";
  _odsPrinter << ' ';
  printOutputPortList(_odsPrinter, *this, getResults().getTypes(), getResultNamesAttr());
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("instanceName");
  elidedAttrs.push_back("moduleName");
  elidedAttrs.push_back("inputNames");
  elidedAttrs.push_back("resultNames");
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
}


} // namespace circt::systemc
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::systemc::InteropVerilatedOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::systemc::detail::InteropVerilatedOpGenericAdaptorBase::Properties)

namespace circt::systemc {


//===----------------------------------------------------------------------===//
// ::circt::systemc::MemberAccessOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

MemberAccessOpGenericAdaptorBase::MemberAccessOpGenericAdaptorBase(MemberAccessOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::llvm::StringRef MemberAccessOpGenericAdaptorBase::getMemberName() {
  auto attr = getMemberNameAttr();
  return attr.getValue();
}

::MemberAccessKind MemberAccessOpGenericAdaptorBase::getAccessKind() {
  auto attr = getAccessKindAttr();
  return attr.getValue();
}


} // namespace detail
MemberAccessOpAdaptor::MemberAccessOpAdaptor(MemberAccessOp op) : MemberAccessOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult MemberAccessOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_accessKind = getProperties().accessKind; (void)tblgen_accessKind;
  if (!tblgen_accessKind) return emitError(loc, "'systemc.cpp.member_access' op requires attribute 'accessKind'");
  auto tblgen_memberName = getProperties().memberName; (void)tblgen_memberName;
  if (!tblgen_memberName) return emitError(loc, "'systemc.cpp.member_access' op requires attribute 'memberName'");

  if (tblgen_memberName && !((::llvm::isa<::mlir::StringAttr>(tblgen_memberName))))
    return emitError(loc, "'systemc.cpp.member_access' op attribute 'memberName' failed to satisfy constraint: string attribute");

  if (tblgen_accessKind && !((::llvm::isa<::MemberAccessKindAttr>(tblgen_accessKind))))
    return emitError(loc, "'systemc.cpp.member_access' op attribute 'accessKind' failed to satisfy constraint: C++ member access kind");
  return ::mlir::success();
}

::llvm::LogicalResult MemberAccessOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.accessKind;
       auto attr = dict.get("accessKind");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `accessKind` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.memberName;
       auto attr = dict.get("memberName");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `memberName` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  return ::mlir::success();
}

::mlir::Attribute MemberAccessOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.accessKind;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("accessKind",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.memberName;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("memberName",
                                       propStorage));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code MemberAccessOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.accessKind.getAsOpaquePointer()), 
    llvm::hash_value(prop.memberName.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> MemberAccessOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "accessKind")
      return prop.accessKind;

    if (name == "memberName")
      return prop.memberName;
  return std::nullopt;
}

void MemberAccessOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "accessKind") {
       prop.accessKind = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.accessKind)>>(value);
       return;
    }

    if (name == "memberName") {
       prop.memberName = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.memberName)>>(value);
       return;
    }
}

void MemberAccessOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.accessKind) attrs.append("accessKind", prop.accessKind);

    if (prop.memberName) attrs.append("memberName", prop.memberName);
}

::llvm::LogicalResult MemberAccessOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getAccessKindAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_SystemC8(attr, "accessKind", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getMemberNameAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_SystemC3(attr, "memberName", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult MemberAccessOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.accessKind)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readAttribute(prop.memberName)))
    return ::mlir::failure();
  return ::mlir::success();
}

void MemberAccessOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.accessKind);
  writer.writeAttribute(prop.memberName);
}

::llvm::StringRef MemberAccessOp::getMemberName() {
  auto attr = getMemberNameAttr();
  return attr.getValue();
}

::MemberAccessKind MemberAccessOp::getAccessKind() {
  auto attr = getAccessKindAttr();
  return attr.getValue();
}

void MemberAccessOp::setMemberName(::llvm::StringRef attrValue) {
  getProperties().memberName = ::mlir::Builder((*this)->getContext()).getStringAttr(attrValue);
}

void MemberAccessOp::setAccessKind(::MemberAccessKind attrValue) {
  getProperties().accessKind = ::MemberAccessKindAttr::get(::mlir::Builder((*this)->getContext()).getContext(), attrValue);
}

void MemberAccessOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value object, ::mlir::StringAttr memberName, ::MemberAccessKindAttr accessKind) {
  odsState.addOperands(object);
  odsState.getOrAddProperties<Properties>().memberName = memberName;
  odsState.getOrAddProperties<Properties>().accessKind = accessKind;
  odsState.addTypes(result);
}

MemberAccessOp MemberAccessOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value object, ::mlir::StringAttr memberName, ::MemberAccessKindAttr accessKind) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(result)>(result), std::forward<decltype(object)>(object), std::forward<decltype(memberName)>(memberName), std::forward<decltype(accessKind)>(accessKind));
  auto __res__ = ::llvm::dyn_cast<MemberAccessOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

MemberAccessOp MemberAccessOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value object, ::mlir::StringAttr memberName, ::MemberAccessKindAttr accessKind) {
  return create(builder, builder.getLoc(), std::forward<decltype(result)>(result), std::forward<decltype(object)>(object), std::forward<decltype(memberName)>(memberName), std::forward<decltype(accessKind)>(accessKind));
}

void MemberAccessOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value object, ::mlir::StringAttr memberName, ::MemberAccessKindAttr accessKind) {
  odsState.addOperands(object);
  odsState.getOrAddProperties<Properties>().memberName = memberName;
  odsState.getOrAddProperties<Properties>().accessKind = accessKind;
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

MemberAccessOp MemberAccessOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value object, ::mlir::StringAttr memberName, ::MemberAccessKindAttr accessKind) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(object)>(object), std::forward<decltype(memberName)>(memberName), std::forward<decltype(accessKind)>(accessKind));
  auto __res__ = ::llvm::dyn_cast<MemberAccessOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

MemberAccessOp MemberAccessOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value object, ::mlir::StringAttr memberName, ::MemberAccessKindAttr accessKind) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(object)>(object), std::forward<decltype(memberName)>(memberName), std::forward<decltype(accessKind)>(accessKind));
}

void MemberAccessOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value object, ::llvm::StringRef memberName, ::MemberAccessKind accessKind) {
  odsState.addOperands(object);
  odsState.getOrAddProperties<Properties>().memberName = odsBuilder.getStringAttr(memberName);
  odsState.getOrAddProperties<Properties>().accessKind = ::MemberAccessKindAttr::get(odsBuilder.getContext(), accessKind);
  odsState.addTypes(result);
}

MemberAccessOp MemberAccessOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value object, ::llvm::StringRef memberName, ::MemberAccessKind accessKind) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(result)>(result), std::forward<decltype(object)>(object), std::forward<decltype(memberName)>(memberName), std::forward<decltype(accessKind)>(accessKind));
  auto __res__ = ::llvm::dyn_cast<MemberAccessOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

MemberAccessOp MemberAccessOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value object, ::llvm::StringRef memberName, ::MemberAccessKind accessKind) {
  return create(builder, builder.getLoc(), std::forward<decltype(result)>(result), std::forward<decltype(object)>(object), std::forward<decltype(memberName)>(memberName), std::forward<decltype(accessKind)>(accessKind));
}

void MemberAccessOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value object, ::llvm::StringRef memberName, ::MemberAccessKind accessKind) {
  odsState.addOperands(object);
  odsState.getOrAddProperties<Properties>().memberName = odsBuilder.getStringAttr(memberName);
  odsState.getOrAddProperties<Properties>().accessKind = ::MemberAccessKindAttr::get(odsBuilder.getContext(), accessKind);
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

MemberAccessOp MemberAccessOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value object, ::llvm::StringRef memberName, ::MemberAccessKind accessKind) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(object)>(object), std::forward<decltype(memberName)>(memberName), std::forward<decltype(accessKind)>(accessKind));
  auto __res__ = ::llvm::dyn_cast<MemberAccessOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

MemberAccessOp MemberAccessOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value object, ::llvm::StringRef memberName, ::MemberAccessKind accessKind) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(object)>(object), std::forward<decltype(memberName)>(memberName), std::forward<decltype(accessKind)>(accessKind));
}

void MemberAccessOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<MemberAccessOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

MemberAccessOp MemberAccessOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<MemberAccessOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

MemberAccessOp MemberAccessOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void MemberAccessOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

MemberAccessOp MemberAccessOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<MemberAccessOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

MemberAccessOp MemberAccessOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult MemberAccessOp::verifyInvariantsImpl() {
  auto tblgen_accessKind = getProperties().accessKind; (void)tblgen_accessKind;
  if (!tblgen_accessKind) return emitOpError("requires attribute 'accessKind'");
  auto tblgen_memberName = getProperties().memberName; (void)tblgen_memberName;
  if (!tblgen_memberName) return emitOpError("requires attribute 'memberName'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_SystemC3(*this, tblgen_memberName, "memberName")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_SystemC8(*this, tblgen_accessKind, "accessKind")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_SystemC1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_SystemC1(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult MemberAccessOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult MemberAccessOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::OpAsmParser::UnresolvedOperand objectRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> objectOperands(&objectRawOperand, 1);  ::llvm::SMLoc objectOperandsLoc;
  (void)objectOperandsLoc;
  ::MemberAccessKindAttr accessKindAttr;
  ::mlir::StringAttr memberNameAttr;
  ::llvm::ArrayRef<::mlir::Type> objectTypes;
  ::llvm::ArrayRef<::mlir::Type> resultTypes;

  objectOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(objectRawOperand))
    return ::mlir::failure();

  {
    ::llvm::StringRef attrStr;
    ::mlir::NamedAttrList attrStorage;
    auto loc = parser.getCurrentLocation();
    if (parser.parseOptionalKeyword(&attrStr, {"dot","arrow"})) {
      ::mlir::StringAttr attrVal;
      ::mlir::OptionalParseResult parseResult =
        parser.parseOptionalAttribute(attrVal,
                                      parser.getBuilder().getNoneType(),
                                      "accessKind", attrStorage);
      if (parseResult.has_value()) {
        if (failed(*parseResult))
          return ::mlir::failure();
        attrStr = attrVal.getValue();
      } else {
        return parser.emitError(loc, "expected string or keyword containing one of the following enum values for attribute 'accessKind' [dot, arrow]");
      }
    }
    if (!attrStr.empty()) {
      auto attrOptional = ::symbolizeMemberAccessKind(attrStr);
      if (!attrOptional)
        return parser.emitError(loc, "invalid ")
               << "accessKind attribute specification: \"" << attrStr << '"';;

      accessKindAttr = ::MemberAccessKindAttr::get(parser.getBuilder().getContext(), *attrOptional);
        result.getOrAddProperties<MemberAccessOp::Properties>().accessKind = accessKindAttr;
    }
  }

  if (parser.parseCustomAttributeWithFallback(memberNameAttr, parser.getBuilder().getType<::mlir::NoneType>())) {
    return ::mlir::failure();
  }
  if (memberNameAttr) result.getOrAddProperties<MemberAccessOp::Properties>().memberName = memberNameAttr;
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

  ::mlir::FunctionType object__result_functionType;
  if (parser.parseType(object__result_functionType))
    return ::mlir::failure();
  objectTypes = object__result_functionType.getInputs();
  resultTypes = object__result_functionType.getResults();
  result.addTypes(resultTypes);
  if (parser.resolveOperands(objectOperands, objectTypes, objectOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void MemberAccessOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter << getObject();
  _odsPrinter << ' ';

  {
    auto caseValue = getAccessKind();
    auto caseValueStr = stringifyMemberAccessKind(caseValue);
    _odsPrinter << caseValueStr;
  }
  _odsPrinter << ' ';
  _odsPrinter.printAttributeWithoutType(getMemberNameAttr());
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("accessKind");
  elidedAttrs.push_back("memberName");
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
  _odsPrinter.printFunctionalType(::llvm::ArrayRef<::mlir::Type>(getObject().getType()), ::llvm::ArrayRef<::mlir::Type>(getResult().getType()));
}

void MemberAccessOp::getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects) {
}


} // namespace circt::systemc
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::systemc::MemberAccessOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::systemc::detail::MemberAccessOpGenericAdaptorBase::Properties)

namespace circt::systemc {


//===----------------------------------------------------------------------===//
// ::circt::systemc::MethodOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

MethodOpGenericAdaptorBase::MethodOpGenericAdaptorBase(MethodOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}


} // namespace detail
MethodOpAdaptor::MethodOpAdaptor(MethodOp op) : MethodOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult MethodOpAdaptor::verify(::mlir::Location loc) {
  return ::mlir::success();
}

::llvm::LogicalResult MethodOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }
      return ::mlir::success();
}

::mlir::Attribute MethodOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code MethodOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine();
}

std::optional<mlir::Attribute> MethodOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
  return std::nullopt;
}

void MethodOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
}

void MethodOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
}

::llvm::LogicalResult MethodOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    return ::mlir::success();
}

void MethodOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value funcHandle) {
  odsState.addOperands(funcHandle);
}

MethodOp MethodOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value funcHandle) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(funcHandle)>(funcHandle));
  auto __res__ = ::llvm::dyn_cast<MethodOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

MethodOp MethodOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value funcHandle) {
  return create(builder, builder.getLoc(), std::forward<decltype(funcHandle)>(funcHandle));
}

void MethodOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value funcHandle) {
  odsState.addOperands(funcHandle);
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

MethodOp MethodOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value funcHandle) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(funcHandle)>(funcHandle));
  auto __res__ = ::llvm::dyn_cast<MethodOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

MethodOp MethodOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value funcHandle) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(funcHandle)>(funcHandle));
}

void MethodOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
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
  assert(operands.size() == 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
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
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_SystemC8(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult MethodOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult MethodOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::OpAsmParser::UnresolvedOperand funcHandleRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> funcHandleOperands(&funcHandleRawOperand, 1);  ::llvm::SMLoc funcHandleOperandsLoc;
  (void)funcHandleOperandsLoc;

  funcHandleOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(funcHandleRawOperand))
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
  ::mlir::Type odsBuildableType0 = mlir::FunctionType::get(parser.getBuilder().getContext(), {}, {});
  if (parser.resolveOperands(funcHandleOperands, odsBuildableType0, funcHandleOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void MethodOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter << getFuncHandle();
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
}


} // namespace circt::systemc
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::systemc::MethodOp)

namespace circt::systemc {


//===----------------------------------------------------------------------===//
// ::circt::systemc::NewOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

NewOpGenericAdaptorBase::NewOpGenericAdaptorBase(NewOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

std::pair<unsigned, unsigned> NewOpGenericAdaptorBase::getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
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
NewOpAdaptor::NewOpAdaptor(NewOp op) : NewOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult NewOpAdaptor::verify(::mlir::Location loc) {
  return ::mlir::success();
}

std::pair<unsigned, unsigned> NewOp::getODSOperandIndexAndLength(unsigned index) {
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

::mlir::MutableOperandRange NewOp::getArgsMutable() {
  auto range = getODSOperandIndexAndLength(0);
  auto mutableRange = ::mlir::MutableOperandRange(getOperation(), range.first, range.second);
  return mutableRange;
}

::llvm::LogicalResult NewOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }
      return ::mlir::success();
}

::mlir::Attribute NewOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code NewOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine();
}

std::optional<mlir::Attribute> NewOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
  return std::nullopt;
}

void NewOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
}

void NewOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
}

::llvm::LogicalResult NewOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    return ::mlir::success();
}

void NewOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::ValueRange args) {
  odsState.addOperands(args);
  odsState.addTypes(result);
}

NewOp NewOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::ValueRange args) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(result)>(result), std::forward<decltype(args)>(args));
  auto __res__ = ::llvm::dyn_cast<NewOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

NewOp NewOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::ValueRange args) {
  return create(builder, builder.getLoc(), std::forward<decltype(result)>(result), std::forward<decltype(args)>(args));
}

void NewOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

NewOp NewOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<NewOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

NewOp NewOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void NewOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

NewOp NewOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<NewOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

NewOp NewOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult NewOp::verifyInvariantsImpl() {
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_SystemC5(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_SystemC7(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult NewOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult NewOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::llvm::SmallVector<::mlir::OpAsmParser::UnresolvedOperand, 4> argsOperands;
  ::llvm::SMLoc argsOperandsLoc;
  (void)argsOperandsLoc;
  ::llvm::ArrayRef<::mlir::Type> argsTypes;
  ::llvm::ArrayRef<::mlir::Type> resultTypes;
  if (parser.parseLParen())
    return ::mlir::failure();

  argsOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperandList(argsOperands))
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

  ::mlir::FunctionType args__result_functionType;
  if (parser.parseType(args__result_functionType))
    return ::mlir::failure();
  argsTypes = args__result_functionType.getInputs();
  resultTypes = args__result_functionType.getResults();
  result.addTypes(resultTypes);
  if (parser.resolveOperands(argsOperands, argsTypes, argsOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void NewOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << "(";
  _odsPrinter << getArgs();
  _odsPrinter << ")";
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
  _odsPrinter.printFunctionalType(getArgs().getTypes(), ::llvm::ArrayRef<::mlir::Type>(getResult().getType()));
}

void NewOp::getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects) {
}


} // namespace circt::systemc
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::systemc::NewOp)

namespace circt::systemc {


//===----------------------------------------------------------------------===//
// ::circt::systemc::ReturnOp definitions
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
      if (::mlir::failed(__mlir_ods_local_type_constraint_SystemC5(*this, v.getType(), "operand", index++)))
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

void ReturnOp::getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects) {
}


} // namespace circt::systemc
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::systemc::ReturnOp)

namespace circt::systemc {


//===----------------------------------------------------------------------===//
// ::circt::systemc::SCFuncOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

SCFuncOpGenericAdaptorBase::SCFuncOpGenericAdaptorBase(SCFuncOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::llvm::StringRef SCFuncOpGenericAdaptorBase::getName() {
  auto attr = getNameAttr();
  return attr.getValue();
}


} // namespace detail
SCFuncOpAdaptor::SCFuncOpAdaptor(SCFuncOp op) : SCFuncOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult SCFuncOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_name = getProperties().name; (void)tblgen_name;
  if (!tblgen_name) return emitError(loc, "'systemc.func' op requires attribute 'name'");

  if (tblgen_name && !((::llvm::isa<::mlir::StringAttr>(tblgen_name))))
    return emitError(loc, "'systemc.func' op attribute 'name' failed to satisfy constraint: string attribute");
  return ::mlir::success();
}

::llvm::LogicalResult SCFuncOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
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

::mlir::Attribute SCFuncOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
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

llvm::hash_code SCFuncOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.name.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> SCFuncOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "name")
      return prop.name;
  return std::nullopt;
}

void SCFuncOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "name") {
       prop.name = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.name)>>(value);
       return;
    }
}

void SCFuncOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.name) attrs.append("name", prop.name);
}

::llvm::LogicalResult SCFuncOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getNameAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_SystemC3(attr, "name", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult SCFuncOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.name)))
    return ::mlir::failure();
  return ::mlir::success();
}

void SCFuncOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.name);
}

::llvm::StringRef SCFuncOp::getName() {
  auto attr = getNameAttr();
  return attr.getValue();
}

void SCFuncOp::setName(::llvm::StringRef attrValue) {
  getProperties().name = ::mlir::Builder((*this)->getContext()).getStringAttr(attrValue);
}

void SCFuncOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, StringAttr name) {
      odsState.addAttribute(getNameAttrName(odsState.name), name);
      Region *region = odsState.addRegion();
      odsState.addTypes(FunctionType::get(odsBuilder.getContext(), {}, {}));
      region->push_back(new Block);
    
}

SCFuncOp SCFuncOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, StringAttr name) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(name)>(name));
  auto __res__ = ::llvm::dyn_cast<SCFuncOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SCFuncOp SCFuncOp::create(::mlir::ImplicitLocOpBuilder &builder, StringAttr name) {
  return create(builder, builder.getLoc(), std::forward<decltype(name)>(name));
}

::llvm::LogicalResult SCFuncOp::verifyInvariantsImpl() {
  auto tblgen_name = getProperties().name; (void)tblgen_name;
  if (!tblgen_name) return emitOpError("requires attribute 'name'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_SystemC3(*this, tblgen_name, "name")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_SystemC8(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;

    for (auto &region : ::llvm::MutableArrayRef((*this)->getRegion(0)))
      if (::mlir::failed(__mlir_ods_local_region_constraint_SystemC1(*this, region, "body", index++)))
        return ::mlir::failure();
  }
  return ::mlir::success();
}

::llvm::LogicalResult SCFuncOp::verifyInvariants() {
  if(::mlir::succeeded(verifyInvariantsImpl()) && ::mlir::succeeded(verify()))
    return ::mlir::success();
  return ::mlir::failure();
}

::llvm::LogicalResult SCFuncOp::inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::PropertyRef properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes) {
  inferredReturnTypes.resize(1);
  ::mlir::Builder odsBuilder(context);
  ::mlir::Type odsInferredType0 = mlir::FunctionType::get(odsBuilder.getContext(), {}, {});
  inferredReturnTypes[0] = odsInferredType0;
  return ::mlir::success();
}

::mlir::ParseResult SCFuncOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::StringAttr nameAttr;
  std::unique_ptr<::mlir::Region> bodyRegion = std::make_unique<::mlir::Region>();
  {
    auto odsResult = parseImplicitSSAName(parser, nameAttr);
    if (odsResult) return ::mlir::failure();
    result.getOrAddProperties<SCFuncOp::Properties>().name = nameAttr;
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
  ::mlir::Type odsBuildableType0 = mlir::FunctionType::get(parser.getBuilder().getContext(), {}, {});
  result.addTypes(odsBuildableType0);
  return ::mlir::success();
}

void SCFuncOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  printImplicitSSAName(_odsPrinter, *this, getNameAttr());
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("name");
  _odsPrinter.printOptionalAttrDictWithKeyword((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ';
  _odsPrinter.printRegion(getBody());
}


} // namespace circt::systemc
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::systemc::SCFuncOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::systemc::detail::SCFuncOpGenericAdaptorBase::Properties)

namespace circt::systemc {


//===----------------------------------------------------------------------===//
// ::circt::systemc::SCModuleOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

SCModuleOpGenericAdaptorBase::SCModuleOpGenericAdaptorBase(SCModuleOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::mlir::FunctionType SCModuleOpGenericAdaptorBase::getFunctionType() {
  auto attr = getFunctionTypeAttr();
  return ::llvm::cast<::mlir::FunctionType>(attr.getValue());
}

::std::optional< ::mlir::ArrayAttr > SCModuleOpGenericAdaptorBase::getArgAttrs() {
  auto attr = getArgAttrsAttr();
  return attr ? ::std::optional< ::mlir::ArrayAttr >(attr) : (::std::nullopt);
}

::std::optional< ::mlir::ArrayAttr > SCModuleOpGenericAdaptorBase::getResAttrs() {
  auto attr = getResAttrsAttr();
  return attr ? ::std::optional< ::mlir::ArrayAttr >(attr) : (::std::nullopt);
}

::mlir::ArrayAttr SCModuleOpGenericAdaptorBase::getPortNames() {
  auto attr = getPortNamesAttr();
  return attr;
}


} // namespace detail
SCModuleOpAdaptor::SCModuleOpAdaptor(SCModuleOp op) : SCModuleOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult SCModuleOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_arg_attrs = getProperties().arg_attrs; (void)tblgen_arg_attrs;
  auto tblgen_function_type = getProperties().function_type; (void)tblgen_function_type;
  if (!tblgen_function_type) return emitError(loc, "'systemc.module' op requires attribute 'function_type'");
  auto tblgen_portNames = getProperties().portNames; (void)tblgen_portNames;
  if (!tblgen_portNames) return emitError(loc, "'systemc.module' op requires attribute 'portNames'");
  auto tblgen_res_attrs = getProperties().res_attrs; (void)tblgen_res_attrs;

  if (tblgen_function_type && !(((::llvm::isa<::mlir::TypeAttr>(tblgen_function_type))) && ((::llvm::isa<::mlir::FunctionType>(::llvm::cast<::mlir::TypeAttr>(tblgen_function_type).getValue()))) && ((::llvm::isa<::mlir::FunctionType>(::llvm::cast<::mlir::TypeAttr>(tblgen_function_type).getValue())))))
    return emitError(loc, "'systemc.module' op attribute 'function_type' failed to satisfy constraint: type attribute of function type");

  if (tblgen_arg_attrs && !(((::llvm::isa<::mlir::ArrayAttr>(tblgen_arg_attrs))) && (::llvm::all_of(::llvm::cast<::mlir::ArrayAttr>(tblgen_arg_attrs), [&](::mlir::Attribute attr) { return attr && ((::llvm::isa<::mlir::DictionaryAttr>(attr))); }))))
    return emitError(loc, "'systemc.module' op attribute 'arg_attrs' failed to satisfy constraint: Array of dictionary attributes");

  if (tblgen_res_attrs && !(((::llvm::isa<::mlir::ArrayAttr>(tblgen_res_attrs))) && (::llvm::all_of(::llvm::cast<::mlir::ArrayAttr>(tblgen_res_attrs), [&](::mlir::Attribute attr) { return attr && ((::llvm::isa<::mlir::DictionaryAttr>(attr))); }))))
    return emitError(loc, "'systemc.module' op attribute 'res_attrs' failed to satisfy constraint: Array of dictionary attributes");

  if (tblgen_portNames && !(((::llvm::isa<::mlir::ArrayAttr>(tblgen_portNames))) && (::llvm::all_of(::llvm::cast<::mlir::ArrayAttr>(tblgen_portNames), [&](::mlir::Attribute attr) { return attr && ((::llvm::isa<::mlir::StringAttr>(attr))); }))))
    return emitError(loc, "'systemc.module' op attribute 'portNames' failed to satisfy constraint: string array attribute");
  return ::mlir::success();
}

::llvm::LogicalResult SCModuleOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
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
    auto &propStorage = prop.portNames;
       auto attr = dict.get("portNames");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `portNames` in property conversion: " << attr;
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

::mlir::Attribute SCModuleOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

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
      const auto &propStorage = prop.portNames;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("portNames",
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

llvm::hash_code SCModuleOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.arg_attrs.getAsOpaquePointer()), 
    llvm::hash_value(prop.function_type.getAsOpaquePointer()), 
    llvm::hash_value(prop.portNames.getAsOpaquePointer()), 
    llvm::hash_value(prop.res_attrs.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> SCModuleOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "arg_attrs")
      return prop.arg_attrs;

    if (name == "function_type")
      return prop.function_type;

    if (name == "portNames")
      return prop.portNames;

    if (name == "res_attrs")
      return prop.res_attrs;
  return std::nullopt;
}

void SCModuleOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "arg_attrs") {
       prop.arg_attrs = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.arg_attrs)>>(value);
       return;
    }

    if (name == "function_type") {
       prop.function_type = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.function_type)>>(value);
       return;
    }

    if (name == "portNames") {
       prop.portNames = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.portNames)>>(value);
       return;
    }

    if (name == "res_attrs") {
       prop.res_attrs = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.res_attrs)>>(value);
       return;
    }
}

void SCModuleOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.arg_attrs) attrs.append("arg_attrs", prop.arg_attrs);

    if (prop.function_type) attrs.append("function_type", prop.function_type);

    if (prop.portNames) attrs.append("portNames", prop.portNames);

    if (prop.res_attrs) attrs.append("res_attrs", prop.res_attrs);
}

::llvm::LogicalResult SCModuleOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getArgAttrsAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_SystemC5(attr, "arg_attrs", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getFunctionTypeAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_SystemC4(attr, "function_type", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getPortNamesAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_SystemC6(attr, "portNames", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getResAttrsAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_SystemC5(attr, "res_attrs", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult SCModuleOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readOptionalAttribute(prop.arg_attrs)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readAttribute(prop.function_type)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readAttribute(prop.portNames)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readOptionalAttribute(prop.res_attrs)))
    return ::mlir::failure();
  return ::mlir::success();
}

void SCModuleOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;

  writer.writeOptionalAttribute(prop.arg_attrs);
  writer.writeAttribute(prop.function_type);
  writer.writeAttribute(prop.portNames);

  writer.writeOptionalAttribute(prop.res_attrs);
}

::mlir::FunctionType SCModuleOp::getFunctionType() {
  auto attr = getFunctionTypeAttr();
  return ::llvm::cast<::mlir::FunctionType>(attr.getValue());
}

::std::optional< ::mlir::ArrayAttr > SCModuleOp::getArgAttrs() {
  auto attr = getArgAttrsAttr();
  return attr ? ::std::optional< ::mlir::ArrayAttr >(attr) : (::std::nullopt);
}

::std::optional< ::mlir::ArrayAttr > SCModuleOp::getResAttrs() {
  auto attr = getResAttrsAttr();
  return attr ? ::std::optional< ::mlir::ArrayAttr >(attr) : (::std::nullopt);
}

::mlir::ArrayAttr SCModuleOp::getPortNames() {
  auto attr = getPortNamesAttr();
  return attr;
}

void SCModuleOp::setFunctionType(::mlir::FunctionType attrValue) {
  getProperties().function_type = ::mlir::TypeAttr::get(attrValue);
}

SCModuleOp SCModuleOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, StringAttr name, ArrayRef<hw::PortInfo> ports, ArrayRef<NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(name)>(name), std::forward<decltype(ports)>(ports), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<SCModuleOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SCModuleOp SCModuleOp::create(::mlir::ImplicitLocOpBuilder &builder, StringAttr name, ArrayRef<hw::PortInfo> ports, ArrayRef<NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(name)>(name), std::forward<decltype(ports)>(ports), std::forward<decltype(attributes)>(attributes));
}

SCModuleOp SCModuleOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, StringAttr name, const hw::ModulePortInfo &ports, ArrayRef<NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(name)>(name), std::forward<decltype(ports)>(ports), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<SCModuleOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SCModuleOp SCModuleOp::create(::mlir::ImplicitLocOpBuilder &builder, StringAttr name, const hw::ModulePortInfo &ports, ArrayRef<NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(name)>(name), std::forward<decltype(ports)>(ports), std::forward<decltype(attributes)>(attributes));
}

SCModuleOp SCModuleOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, StringAttr name, ArrayAttr portNames, ArrayRef<Type> portTypes, ArrayRef<NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(name)>(name), std::forward<decltype(portNames)>(portNames), std::forward<decltype(portTypes)>(portTypes), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<SCModuleOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SCModuleOp SCModuleOp::create(::mlir::ImplicitLocOpBuilder &builder, StringAttr name, ArrayAttr portNames, ArrayRef<Type> portTypes, ArrayRef<NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(name)>(name), std::forward<decltype(portNames)>(portNames), std::forward<decltype(portTypes)>(portTypes), std::forward<decltype(attributes)>(attributes));
}

::llvm::LogicalResult SCModuleOp::verifyInvariantsImpl() {
  auto tblgen_arg_attrs = getProperties().arg_attrs; (void)tblgen_arg_attrs;
  auto tblgen_function_type = getProperties().function_type; (void)tblgen_function_type;
  if (!tblgen_function_type) return emitOpError("requires attribute 'function_type'");
  auto tblgen_portNames = getProperties().portNames; (void)tblgen_portNames;
  if (!tblgen_portNames) return emitOpError("requires attribute 'portNames'");
  auto tblgen_res_attrs = getProperties().res_attrs; (void)tblgen_res_attrs;

  if (::mlir::failed(__mlir_ods_local_attr_constraint_SystemC4(*this, tblgen_function_type, "function_type")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_SystemC5(*this, tblgen_arg_attrs, "arg_attrs")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_SystemC5(*this, tblgen_res_attrs, "res_attrs")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_SystemC6(*this, tblgen_portNames, "portNames")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;

    for (auto &region : ::llvm::MutableArrayRef((*this)->getRegion(0)))
      if (::mlir::failed(__mlir_ods_local_region_constraint_SystemC1(*this, region, "body", index++)))
        return ::mlir::failure();
  }
  return ::mlir::success();
}

::llvm::LogicalResult SCModuleOp::verifyInvariants() {
  if(::mlir::succeeded(verifyInvariantsImpl()) && ::mlir::succeeded(verify()))
    return ::mlir::success();
  return ::mlir::failure();
}

::llvm::LogicalResult SCModuleOp::setPropertiesFromParsedAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
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
  {

    auto &propStorage = prop.portNames;
    auto portNamesAttrName = ::mlir::StringAttr::get(ctx, "portNames");
    auto attr = dict.get(portNamesAttrName);
    usedKeys.insert(portNamesAttrName);
    if (attr || /*isRequired=*/true) {
      if (!attr) {
        emitError() << "expected key entry for portNames in DictionaryAttr to set "
                   "Properties.";
        return ::mlir::failure();
      }
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `portNames` in property conversion: " << attr;
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


} // namespace circt::systemc
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::systemc::SCModuleOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::systemc::detail::SCModuleOpGenericAdaptorBase::Properties)

namespace circt::systemc {


//===----------------------------------------------------------------------===//
// ::circt::systemc::SensitiveOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

SensitiveOpGenericAdaptorBase::SensitiveOpGenericAdaptorBase(SensitiveOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

std::pair<unsigned, unsigned> SensitiveOpGenericAdaptorBase::getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
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
SensitiveOpAdaptor::SensitiveOpAdaptor(SensitiveOp op) : SensitiveOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult SensitiveOpAdaptor::verify(::mlir::Location loc) {
  return ::mlir::success();
}

std::pair<unsigned, unsigned> SensitiveOp::getODSOperandIndexAndLength(unsigned index) {
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

::mlir::MutableOperandRange SensitiveOp::getSensitivitiesMutable() {
  auto range = getODSOperandIndexAndLength(0);
  auto mutableRange = ::mlir::MutableOperandRange(getOperation(), range.first, range.second);
  return mutableRange;
}

::llvm::LogicalResult SensitiveOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }
      return ::mlir::success();
}

::mlir::Attribute SensitiveOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code SensitiveOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine();
}

std::optional<mlir::Attribute> SensitiveOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
  return std::nullopt;
}

void SensitiveOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
}

void SensitiveOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
}

::llvm::LogicalResult SensitiveOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    return ::mlir::success();
}

void SensitiveOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange sensitivities) {
  odsState.addOperands(sensitivities);
}

SensitiveOp SensitiveOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange sensitivities) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(sensitivities)>(sensitivities));
  auto __res__ = ::llvm::dyn_cast<SensitiveOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SensitiveOp SensitiveOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange sensitivities) {
  return create(builder, builder.getLoc(), std::forward<decltype(sensitivities)>(sensitivities));
}

void SensitiveOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

SensitiveOp SensitiveOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<SensitiveOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SensitiveOp SensitiveOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void SensitiveOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

SensitiveOp SensitiveOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<SensitiveOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SensitiveOp SensitiveOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult SensitiveOp::verifyInvariantsImpl() {
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_SystemC9(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult SensitiveOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

void SensitiveOp::getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context) {
  results.add(canonicalize);
}

::mlir::ParseResult SensitiveOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::llvm::SmallVector<::mlir::OpAsmParser::UnresolvedOperand, 4> sensitivitiesOperands;
  ::llvm::SMLoc sensitivitiesOperandsLoc;
  (void)sensitivitiesOperandsLoc;
  ::llvm::SmallVector<::mlir::Type, 1> sensitivitiesTypes;

  sensitivitiesOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperandList(sensitivitiesOperands))
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
  if (::mlir::succeeded(parser.parseOptionalColon())) {

  if (parser.parseTypeList(sensitivitiesTypes))
    return ::mlir::failure();
  }
  if (parser.resolveOperands(sensitivitiesOperands, sensitivitiesTypes, sensitivitiesOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void SensitiveOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter << getSensitivities();
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  if (!getSensitivities().empty()) {
    _odsPrinter << ' ' << ":";
    _odsPrinter << ' ';
    _odsPrinter << getSensitivities().getTypes();
  }
}


} // namespace circt::systemc
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::systemc::SensitiveOp)

namespace circt::systemc {


//===----------------------------------------------------------------------===//
// ::circt::systemc::SignalOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

SignalOpGenericAdaptorBase::SignalOpGenericAdaptorBase(SignalOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::llvm::StringRef SignalOpGenericAdaptorBase::getName() {
  auto attr = getNameAttr();
  return attr.getValue();
}

::mlir::UnitAttr SignalOpGenericAdaptorBase::getNamedAttr() {
  auto attr = ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(getProperties().named);
  if (!attr)
    attr = ((false) ? ::mlir::Builder(odsAttrs.getContext()).getUnitAttr() : nullptr);
  return attr;
}

bool SignalOpGenericAdaptorBase::getNamed() {
  auto attr = getNamedAttr();
    if (!attr)
      return ((false) ? ::mlir::Builder(odsAttrs.getContext()).getUnitAttr() : nullptr) != nullptr;
  return attr != nullptr;
}


} // namespace detail
SignalOpAdaptor::SignalOpAdaptor(SignalOp op) : SignalOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult SignalOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_name = getProperties().name; (void)tblgen_name;
  if (!tblgen_name) return emitError(loc, "'systemc.signal' op requires attribute 'name'");
  auto tblgen_named = getProperties().named; (void)tblgen_named;

  if (tblgen_name && !((::llvm::isa<::mlir::StringAttr>(tblgen_name))))
    return emitError(loc, "'systemc.signal' op attribute 'name' failed to satisfy constraint: string attribute");

  if (tblgen_named && !((::llvm::isa<::mlir::UnitAttr>(tblgen_named))))
    return emitError(loc, "'systemc.signal' op attribute 'named' failed to satisfy constraint: unit attribute");
  return ::mlir::success();
}

::llvm::LogicalResult SignalOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
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

  {
    auto &propStorage = prop.named;
       auto attr = dict.get("named");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `named` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  return ::mlir::success();
}

::mlir::Attribute SignalOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.name;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("name",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.named;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("named",
                                       propStorage));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code SignalOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.name.getAsOpaquePointer()), 
    llvm::hash_value(prop.named.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> SignalOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "name")
      return prop.name;

    if (name == "named")
      return prop.named;
  return std::nullopt;
}

void SignalOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "name") {
       prop.name = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.name)>>(value);
       return;
    }

    if (name == "named") {
       prop.named = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.named)>>(value);
       return;
    }
}

void SignalOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.name) attrs.append("name", prop.name);

    if (prop.named) attrs.append("named", prop.named);
}

::llvm::LogicalResult SignalOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getNameAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_SystemC3(attr, "name", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getNamedAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_SystemC7(attr, "named", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult SignalOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.name)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readOptionalAttribute(prop.named)))
    return ::mlir::failure();
  return ::mlir::success();
}

void SignalOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.name);

  writer.writeOptionalAttribute(prop.named);
}

::llvm::StringRef SignalOp::getName() {
  auto attr = getNameAttr();
  return attr.getValue();
}

bool SignalOp::getNamed() {
  auto attr = getNamedAttr();
    if (!attr)
      return ((false) ? ::mlir::Builder((*this)->getContext()).getUnitAttr() : nullptr) != nullptr;
  return attr != nullptr;
}

void SignalOp::setName(::llvm::StringRef attrValue) {
  getProperties().name = ::mlir::Builder((*this)->getContext()).getStringAttr(attrValue);
}

void SignalOp::setNamed(bool attrValue) {
    auto &odsProp = getProperties().named;
    if (attrValue)
      odsProp = ((attrValue) ? ::mlir::Builder((*this)->getContext()).getUnitAttr() : nullptr);
    else
      odsProp = nullptr;
}

void SignalOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type signal, ::mlir::StringAttr name, /*optional*/::mlir::UnitAttr named) {
  odsState.getOrAddProperties<Properties>().name = name;
  if (named) {
    odsState.getOrAddProperties<Properties>().named = named;
  }
  odsState.addTypes(signal);
}

SignalOp SignalOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type signal, ::mlir::StringAttr name, /*optional*/::mlir::UnitAttr named) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(signal)>(signal), std::forward<decltype(name)>(name), std::forward<decltype(named)>(named));
  auto __res__ = ::llvm::dyn_cast<SignalOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SignalOp SignalOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type signal, ::mlir::StringAttr name, /*optional*/::mlir::UnitAttr named) {
  return create(builder, builder.getLoc(), std::forward<decltype(signal)>(signal), std::forward<decltype(name)>(name), std::forward<decltype(named)>(named));
}

void SignalOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::StringAttr name, /*optional*/::mlir::UnitAttr named) {
  odsState.getOrAddProperties<Properties>().name = name;
  if (named) {
    odsState.getOrAddProperties<Properties>().named = named;
  }
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

SignalOp SignalOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::StringAttr name, /*optional*/::mlir::UnitAttr named) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(name)>(name), std::forward<decltype(named)>(named));
  auto __res__ = ::llvm::dyn_cast<SignalOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SignalOp SignalOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::StringAttr name, /*optional*/::mlir::UnitAttr named) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(name)>(name), std::forward<decltype(named)>(named));
}

void SignalOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type signal, ::llvm::StringRef name, /*optional*/bool named) {
  odsState.getOrAddProperties<Properties>().name = odsBuilder.getStringAttr(name);
  if (named) {
    odsState.getOrAddProperties<Properties>().named = ((named) ? odsBuilder.getUnitAttr() : nullptr);
  }
  odsState.addTypes(signal);
}

SignalOp SignalOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type signal, ::llvm::StringRef name, /*optional*/bool named) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(signal)>(signal), std::forward<decltype(name)>(name), std::forward<decltype(named)>(named));
  auto __res__ = ::llvm::dyn_cast<SignalOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SignalOp SignalOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type signal, ::llvm::StringRef name, /*optional*/bool named) {
  return create(builder, builder.getLoc(), std::forward<decltype(signal)>(signal), std::forward<decltype(name)>(name), std::forward<decltype(named)>(named));
}

void SignalOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::llvm::StringRef name, /*optional*/bool named) {
  odsState.getOrAddProperties<Properties>().name = odsBuilder.getStringAttr(name);
  if (named) {
    odsState.getOrAddProperties<Properties>().named = ((named) ? odsBuilder.getUnitAttr() : nullptr);
  }
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

SignalOp SignalOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::llvm::StringRef name, /*optional*/bool named) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(name)>(name), std::forward<decltype(named)>(named));
  auto __res__ = ::llvm::dyn_cast<SignalOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SignalOp SignalOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::llvm::StringRef name, /*optional*/bool named) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(name)>(name), std::forward<decltype(named)>(named));
}

void SignalOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<SignalOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

SignalOp SignalOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<SignalOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SignalOp SignalOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void SignalOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

SignalOp SignalOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<SignalOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SignalOp SignalOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult SignalOp::verifyInvariantsImpl() {
  auto tblgen_name = getProperties().name; (void)tblgen_name;
  if (!tblgen_name) return emitOpError("requires attribute 'name'");
  auto tblgen_named = getProperties().named; (void)tblgen_named;

  if (::mlir::failed(__mlir_ods_local_attr_constraint_SystemC3(*this, tblgen_name, "name")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_SystemC7(*this, tblgen_named, "named")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_SystemC10(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult SignalOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult SignalOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::StringAttr nameAttr;
  ::mlir::Type signalRawType{};
  ::llvm::ArrayRef<::mlir::Type> signalTypes(&signalRawType, 1);
  {
    auto odsResult = parseImplicitSSAName(parser, nameAttr);
    if (odsResult) return ::mlir::failure();
    result.getOrAddProperties<SignalOp::Properties>().name = nameAttr;
  }
  if (::mlir::succeeded(parser.parseOptionalKeyword("named"))) {
    result.getOrAddProperties<SignalOp::Properties>().named = parser.getBuilder().getUnitAttr();  }
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

  if (parser.parseType(signalRawType))
    return ::mlir::failure();
  result.addTypes(signalTypes);
  return ::mlir::success();
}

void SignalOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  printImplicitSSAName(_odsPrinter, *this, getNameAttr());
  if ((getNamedAttr() && getNamedAttr() != ((false) ? ::mlir::OpBuilder((*this)->getContext()).getUnitAttr() : nullptr))) {
    _odsPrinter << ' ' << "named";
  }
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("name");
  elidedAttrs.push_back("named");
  {
     ::mlir::Builder odsBuilder(getContext());
     ::mlir::Attribute attr = getNamedAttr();
     if(attr && (attr == ((false) ? odsBuilder.getUnitAttr() : nullptr)))
       elidedAttrs.push_back("named");
  }
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
   _odsPrinter << getSignal().getType();
}


} // namespace circt::systemc
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::systemc::SignalOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::systemc::detail::SignalOpGenericAdaptorBase::Properties)

namespace circt::systemc {


//===----------------------------------------------------------------------===//
// ::circt::systemc::SignalReadOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

SignalReadOpGenericAdaptorBase::SignalReadOpGenericAdaptorBase(SignalReadOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}


} // namespace detail
SignalReadOpAdaptor::SignalReadOpAdaptor(SignalReadOp op) : SignalReadOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult SignalReadOpAdaptor::verify(::mlir::Location loc) {
  return ::mlir::success();
}

::llvm::LogicalResult SignalReadOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }
      return ::mlir::success();
}

::mlir::Attribute SignalReadOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code SignalReadOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine();
}

std::optional<mlir::Attribute> SignalReadOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
  return std::nullopt;
}

void SignalReadOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
}

void SignalReadOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
}

::llvm::LogicalResult SignalReadOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    return ::mlir::success();
}

void SignalReadOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value input) {
  odsState.addOperands(input);
  odsState.addTypes(result);
}

SignalReadOp SignalReadOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value input) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(result)>(result), std::forward<decltype(input)>(input));
  auto __res__ = ::llvm::dyn_cast<SignalReadOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SignalReadOp SignalReadOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value input) {
  return create(builder, builder.getLoc(), std::forward<decltype(result)>(result), std::forward<decltype(input)>(input));
}

void SignalReadOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value input) {
  odsState.addOperands(input);

        ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
        if (::mlir::succeeded(SignalReadOp::inferReturnTypes(odsBuilder.getContext(),
                      odsState.location, odsState.operands,
                      odsState.attributes.getDictionary(odsState.getContext()),
                      odsState.getRawProperties(),
                      odsState.regions, inferredReturnTypes)))
          odsState.addTypes(inferredReturnTypes);
        else
          ::mlir::detail::reportFatalInferReturnTypesError(odsState);
        
}

SignalReadOp SignalReadOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value input) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(input)>(input));
  auto __res__ = ::llvm::dyn_cast<SignalReadOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SignalReadOp SignalReadOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value input) {
  return create(builder, builder.getLoc(), std::forward<decltype(input)>(input));
}

void SignalReadOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value input) {
  odsState.addOperands(input);
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

SignalReadOp SignalReadOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value input) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(input)>(input));
  auto __res__ = ::llvm::dyn_cast<SignalReadOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SignalReadOp SignalReadOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value input) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(input)>(input));
}

void SignalReadOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

SignalReadOp SignalReadOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<SignalReadOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SignalReadOp SignalReadOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void SignalReadOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);

  ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
  if (::mlir::succeeded(SignalReadOp::inferReturnTypes(odsBuilder.getContext(),
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

SignalReadOp SignalReadOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<SignalReadOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SignalReadOp SignalReadOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void SignalReadOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

SignalReadOp SignalReadOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<SignalReadOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SignalReadOp SignalReadOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

void SignalReadOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties &>(properties));
  odsState.addAttributes(discardableAttributes);

  ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
  if (::mlir::succeeded(SignalReadOp::inferReturnTypes(odsBuilder.getContext(),
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

SignalReadOp SignalReadOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<SignalReadOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SignalReadOp SignalReadOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult SignalReadOp::verifyInvariantsImpl() {
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_SystemC11(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_SystemC1(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult SignalReadOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult SignalReadOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
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

  if (parser.parseType(inputRawType))
    return ::mlir::failure();
  if (parser.resolveOperands(inputOperands, inputTypes, inputOperandsLoc, result.operands))
    return ::mlir::failure();

  ::llvm::SmallVector<::mlir::Type> inferredReturnTypes;
  if (::mlir::failed(SignalReadOp::inferReturnTypes(parser.getContext(),
      result.location, result.operands,
      result.attributes.getDictionary(parser.getContext()),
      result.getRawProperties(),
      result.regions, inferredReturnTypes)))
    return ::mlir::failure();
  result.addTypes(inferredReturnTypes);
  return ::mlir::success();
}

void SignalReadOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter << getInput();
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
   _odsPrinter << getInput().getType();
}

void SignalReadOp::getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects) {
}


} // namespace circt::systemc
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::systemc::SignalReadOp)

namespace circt::systemc {


//===----------------------------------------------------------------------===//
// ::circt::systemc::SignalWriteOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

SignalWriteOpGenericAdaptorBase::SignalWriteOpGenericAdaptorBase(SignalWriteOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}


} // namespace detail
SignalWriteOpAdaptor::SignalWriteOpAdaptor(SignalWriteOp op) : SignalWriteOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult SignalWriteOpAdaptor::verify(::mlir::Location loc) {
  return ::mlir::success();
}

::llvm::LogicalResult SignalWriteOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }
      return ::mlir::success();
}

::mlir::Attribute SignalWriteOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code SignalWriteOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine();
}

std::optional<mlir::Attribute> SignalWriteOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
  return std::nullopt;
}

void SignalWriteOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
}

void SignalWriteOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
}

::llvm::LogicalResult SignalWriteOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    return ::mlir::success();
}

void SignalWriteOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value dest, ::mlir::Value src) {
  odsState.addOperands(dest);
  odsState.addOperands(src);
}

SignalWriteOp SignalWriteOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value dest, ::mlir::Value src) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(dest)>(dest), std::forward<decltype(src)>(src));
  auto __res__ = ::llvm::dyn_cast<SignalWriteOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SignalWriteOp SignalWriteOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value dest, ::mlir::Value src) {
  return create(builder, builder.getLoc(), std::forward<decltype(dest)>(dest), std::forward<decltype(src)>(src));
}

void SignalWriteOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value dest, ::mlir::Value src) {
  odsState.addOperands(dest);
  odsState.addOperands(src);
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

SignalWriteOp SignalWriteOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value dest, ::mlir::Value src) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(dest)>(dest), std::forward<decltype(src)>(src));
  auto __res__ = ::llvm::dyn_cast<SignalWriteOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SignalWriteOp SignalWriteOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value dest, ::mlir::Value src) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(dest)>(dest), std::forward<decltype(src)>(src));
}

void SignalWriteOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 2u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

SignalWriteOp SignalWriteOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<SignalWriteOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SignalWriteOp SignalWriteOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void SignalWriteOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 2u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

SignalWriteOp SignalWriteOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<SignalWriteOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SignalWriteOp SignalWriteOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult SignalWriteOp::verifyInvariantsImpl() {
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_SystemC12(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSOperands(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_SystemC1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  if (!((std::equal_to<>()(systemc::getSignalBaseType((*this->getODSOperands(0).begin()).getType()), (*this->getODSOperands(1).begin()).getType()))))
    return emitOpError("failed to verify that dest has to be the base type of the src");
  return ::mlir::success();
}

::llvm::LogicalResult SignalWriteOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult SignalWriteOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::OpAsmParser::UnresolvedOperand destRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> destOperands(&destRawOperand, 1);  ::llvm::SMLoc destOperandsLoc;
  (void)destOperandsLoc;
  ::mlir::OpAsmParser::UnresolvedOperand srcRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> srcOperands(&srcRawOperand, 1);  ::llvm::SMLoc srcOperandsLoc;
  (void)srcOperandsLoc;
  ::mlir::Type destRawType{};
  ::llvm::ArrayRef<::mlir::Type> destTypes(&destRawType, 1);

  destOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(destRawOperand))
    return ::mlir::failure();
  if (parser.parseComma())
    return ::mlir::failure();

  srcOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(srcRawOperand))
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

  if (parser.parseType(destRawType))
    return ::mlir::failure();
  for (::mlir::Type type : destTypes) {
    (void)type;
    if (!(((::llvm::isa<::circt::systemc::OutputType>(type))) || ((::llvm::isa<::circt::systemc::InOutType>(type))) || ((::llvm::isa<::circt::systemc::SignalType>(type))))) {
      return parser.emitError(parser.getNameLoc()) << "'dest' must be a SystemC sc_out<T> type or a SystemC sc_inout<T> type or a SystemC sc_signal<T> type, but got " << type;
    }
  }
  if (parser.resolveOperands(destOperands, destTypes, destOperandsLoc, result.operands))
    return ::mlir::failure();
  if (parser.resolveOperands(srcOperands, systemc::getSignalBaseType(destTypes[0]), srcOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void SignalWriteOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter << getDest();
  _odsPrinter << ",";
  _odsPrinter << ' ';
  _odsPrinter << getSrc();
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
   _odsPrinter << getDest().getType();
}


} // namespace circt::systemc
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::systemc::SignalWriteOp)

namespace circt::systemc {


//===----------------------------------------------------------------------===//
// ::circt::systemc::ThreadOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

ThreadOpGenericAdaptorBase::ThreadOpGenericAdaptorBase(ThreadOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}


} // namespace detail
ThreadOpAdaptor::ThreadOpAdaptor(ThreadOp op) : ThreadOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult ThreadOpAdaptor::verify(::mlir::Location loc) {
  return ::mlir::success();
}

::llvm::LogicalResult ThreadOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }
      return ::mlir::success();
}

::mlir::Attribute ThreadOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code ThreadOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine();
}

std::optional<mlir::Attribute> ThreadOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
  return std::nullopt;
}

void ThreadOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
}

void ThreadOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
}

::llvm::LogicalResult ThreadOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    return ::mlir::success();
}

void ThreadOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value funcHandle) {
  odsState.addOperands(funcHandle);
}

ThreadOp ThreadOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value funcHandle) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(funcHandle)>(funcHandle));
  auto __res__ = ::llvm::dyn_cast<ThreadOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ThreadOp ThreadOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value funcHandle) {
  return create(builder, builder.getLoc(), std::forward<decltype(funcHandle)>(funcHandle));
}

void ThreadOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value funcHandle) {
  odsState.addOperands(funcHandle);
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

ThreadOp ThreadOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value funcHandle) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(funcHandle)>(funcHandle));
  auto __res__ = ::llvm::dyn_cast<ThreadOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ThreadOp ThreadOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value funcHandle) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(funcHandle)>(funcHandle));
}

void ThreadOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

ThreadOp ThreadOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<ThreadOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ThreadOp ThreadOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void ThreadOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

ThreadOp ThreadOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<ThreadOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ThreadOp ThreadOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult ThreadOp::verifyInvariantsImpl() {
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_SystemC8(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult ThreadOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult ThreadOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::OpAsmParser::UnresolvedOperand funcHandleRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> funcHandleOperands(&funcHandleRawOperand, 1);  ::llvm::SMLoc funcHandleOperandsLoc;
  (void)funcHandleOperandsLoc;

  funcHandleOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(funcHandleRawOperand))
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
  ::mlir::Type odsBuildableType0 = mlir::FunctionType::get(parser.getBuilder().getContext(), {}, {});
  if (parser.resolveOperands(funcHandleOperands, odsBuildableType0, funcHandleOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void ThreadOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter << getFuncHandle();
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
}


} // namespace circt::systemc
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::systemc::ThreadOp)

namespace circt::systemc {


//===----------------------------------------------------------------------===//
// ::circt::systemc::VariableOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

VariableOpGenericAdaptorBase::VariableOpGenericAdaptorBase(VariableOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

std::pair<unsigned, unsigned> VariableOpGenericAdaptorBase::getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
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

::llvm::StringRef VariableOpGenericAdaptorBase::getName() {
  auto attr = getNameAttr();
  return attr.getValue();
}


} // namespace detail
VariableOpAdaptor::VariableOpAdaptor(VariableOp op) : VariableOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult VariableOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_name = getProperties().name; (void)tblgen_name;
  if (!tblgen_name) return emitError(loc, "'systemc.cpp.variable' op requires attribute 'name'");

  if (tblgen_name && !((::llvm::isa<::mlir::StringAttr>(tblgen_name))))
    return emitError(loc, "'systemc.cpp.variable' op attribute 'name' failed to satisfy constraint: string attribute");
  return ::mlir::success();
}

std::pair<unsigned, unsigned> VariableOp::getODSOperandIndexAndLength(unsigned index) {
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

::mlir::MutableOperandRange VariableOp::getInitMutable() {
  auto range = getODSOperandIndexAndLength(0);
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
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_SystemC3(attr, "name", emitError)))
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

void VariableOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type variable, ::mlir::StringAttr name, /*optional*/::mlir::Value init) {
  if (init)
    odsState.addOperands(init);
  odsState.getOrAddProperties<Properties>().name = name;
  odsState.addTypes(variable);
}

VariableOp VariableOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type variable, ::mlir::StringAttr name, /*optional*/::mlir::Value init) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(variable)>(variable), std::forward<decltype(name)>(name), std::forward<decltype(init)>(init));
  auto __res__ = ::llvm::dyn_cast<VariableOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

VariableOp VariableOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type variable, ::mlir::StringAttr name, /*optional*/::mlir::Value init) {
  return create(builder, builder.getLoc(), std::forward<decltype(variable)>(variable), std::forward<decltype(name)>(name), std::forward<decltype(init)>(init));
}

void VariableOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::StringAttr name, /*optional*/::mlir::Value init) {
  if (init)
    odsState.addOperands(init);
  odsState.getOrAddProperties<Properties>().name = name;
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

VariableOp VariableOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::StringAttr name, /*optional*/::mlir::Value init) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(name)>(name), std::forward<decltype(init)>(init));
  auto __res__ = ::llvm::dyn_cast<VariableOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

VariableOp VariableOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::StringAttr name, /*optional*/::mlir::Value init) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(name)>(name), std::forward<decltype(init)>(init));
}

void VariableOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type variable, ::llvm::StringRef name, /*optional*/::mlir::Value init) {
  if (init)
    odsState.addOperands(init);
  odsState.getOrAddProperties<Properties>().name = odsBuilder.getStringAttr(name);
  odsState.addTypes(variable);
}

VariableOp VariableOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type variable, ::llvm::StringRef name, /*optional*/::mlir::Value init) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(variable)>(variable), std::forward<decltype(name)>(name), std::forward<decltype(init)>(init));
  auto __res__ = ::llvm::dyn_cast<VariableOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

VariableOp VariableOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type variable, ::llvm::StringRef name, /*optional*/::mlir::Value init) {
  return create(builder, builder.getLoc(), std::forward<decltype(variable)>(variable), std::forward<decltype(name)>(name), std::forward<decltype(init)>(init));
}

void VariableOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::llvm::StringRef name, /*optional*/::mlir::Value init) {
  if (init)
    odsState.addOperands(init);
  odsState.getOrAddProperties<Properties>().name = odsBuilder.getStringAttr(name);
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

VariableOp VariableOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::llvm::StringRef name, /*optional*/::mlir::Value init) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(name)>(name), std::forward<decltype(init)>(init));
  auto __res__ = ::llvm::dyn_cast<VariableOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

VariableOp VariableOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::llvm::StringRef name, /*optional*/::mlir::Value init) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(name)>(name), std::forward<decltype(init)>(init));
}

void VariableOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
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
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
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

  if (::mlir::failed(__mlir_ods_local_attr_constraint_SystemC3(*this, tblgen_name, "name")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    if (valueGroup0.size() > 1) {
      return emitOpError("operand group starting at #") << index
          << " requires 0 or 1 element, but found " << valueGroup0.size();
    }

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_SystemC1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_SystemC1(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult VariableOp::verifyInvariants() {
  if(::mlir::succeeded(verifyInvariantsImpl()) && ::mlir::succeeded(verify()))
    return ::mlir::success();
  return ::mlir::failure();
}

::llvm::LogicalResult VariableOp::setPropertiesFromParsedAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
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
    if (attr || /*isRequired=*/true) {
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

  for (::mlir::NamedAttribute attr : dict) {
    if (!usedKeys.contains(attr.getName()))
      return emitError() << "unknown key '" << attr.getName() <<
          "' when parsing properties dictionary";
  }
  return ::mlir::success();
}


} // namespace circt::systemc
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::systemc::VariableOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::systemc::detail::VariableOpGenericAdaptorBase::Properties)


#endif // GET_OP_CLASSES

