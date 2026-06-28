/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Op Definitions                                                             *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: Seq.td                                                               *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

#ifdef GET_OP_LIST
#undef GET_OP_LIST

::circt::seq::ClockDividerOp,
::circt::seq::ClockGateOp,
::circt::seq::ClockInverterOp,
::circt::seq::ClockMuxOp,
::circt::seq::CompRegClockEnabledOp,
::circt::seq::CompRegOp,
::circt::seq::ConstClockOp,
::circt::seq::FIFOOp,
::circt::seq::FirMemOp,
::circt::seq::FirMemReadOp,
::circt::seq::FirMemReadWriteOp,
::circt::seq::FirMemWriteOp,
::circt::seq::FirRegOp,
::circt::seq::FromClockOp,
::circt::seq::FromImmutableOp,
::circt::seq::HLMemOp,
::circt::seq::InitialOp,
::circt::seq::ReadPortOp,
::circt::seq::ShiftRegOp,
::circt::seq::ToClockOp,
::circt::seq::WritePortOp,
::circt::seq::YieldOp
#endif // GET_OP_LIST

#ifdef GET_OP_CLASSES
#undef GET_OP_CLASSES


//===----------------------------------------------------------------------===//
// Local Utility Method Definitions
//===----------------------------------------------------------------------===//


static ::llvm::LogicalResult __mlir_ods_local_type_constraint_Seq1(
    ::mlir::Operation *op, ::mlir::Type type, ::llvm::StringRef valueKind,
    unsigned valueIndex) {
  if (!((::llvm::isa<::circt::seq::ClockType>(type)))) {
    return op->emitOpError(valueKind) << " #" << valueIndex
        << " must be A type for clock-carrying wires, but got " << type;
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_type_constraint_Seq2(
    ::mlir::Operation *op, ::mlir::Type type, ::llvm::StringRef valueKind,
    unsigned valueIndex) {
  if (!((type.isSignlessInteger(1)))) {
    return op->emitOpError(valueKind) << " #" << valueIndex
        << " must be 1-bit signless integer, but got " << type;
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_type_constraint_Seq3(
    ::mlir::Operation *op, ::mlir::Type type, ::llvm::StringRef valueKind,
    unsigned valueIndex) {
  if (!(!((::llvm::isa<::mlir::TokenType>(type))))) {
    return op->emitOpError(valueKind) << " #" << valueIndex
        << " must be any non-token type, but got " << type;
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_type_constraint_Seq4(
    ::mlir::Operation *op, ::mlir::Type type, ::llvm::StringRef valueKind,
    unsigned valueIndex) {
  if (!((isa<circt::seq::ImmutableType>(type)))) {
    return op->emitOpError(valueKind) << " #" << valueIndex
        << " must be an ImmutableType, but got " << type;
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_type_constraint_Seq5(
    ::mlir::Operation *op, ::mlir::Type type, ::llvm::StringRef valueKind,
    unsigned valueIndex) {
  if (!((::llvm::isa<::circt::seq::FirMemType>(type)))) {
    return op->emitOpError(valueKind) << " #" << valueIndex
        << " must be A FIRRTL-flavored memory, but got " << type;
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_type_constraint_Seq6(
    ::mlir::Operation *op, ::mlir::Type type, ::llvm::StringRef valueKind,
    unsigned valueIndex) {
  if (!((type.isSignlessInteger()))) {
    return op->emitOpError(valueKind) << " #" << valueIndex
        << " must be signless integer, but got " << type;
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_type_constraint_Seq7(
    ::mlir::Operation *op, ::mlir::Type type, ::llvm::StringRef valueKind,
    unsigned valueIndex) {
  if (!((::llvm::isa<::circt::seq::HLMemType>(type)))) {
    return op->emitOpError(valueKind) << " #" << valueIndex
        << " must be Multi-dimensional memory type, but got " << type;
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_type_constraint_Seq8(
    ::mlir::Operation *op, ::mlir::Type type, ::llvm::StringRef valueKind,
    unsigned valueIndex) {
  if (!((isa<circt::seq::ImmutableType>(type)))) {
    return op->emitOpError(valueKind) << " #" << valueIndex
        << " must be variadic of an ImmutableType, but got " << type;
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_type_constraint_Seq9(
    ::mlir::Operation *op, ::mlir::Type type, ::llvm::StringRef valueKind,
    unsigned valueIndex) {
  if (!((::circt::hw::isHWIntegerType(type)))) {
    return op->emitOpError(valueKind) << " #" << valueIndex
        << " must be variadic of a signless integer bitvector, but got " << type;
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_type_constraint_Seq10(
    ::mlir::Operation *op, ::mlir::Type type, ::llvm::StringRef valueKind,
    unsigned valueIndex) {
  if (!(!((::llvm::isa<::mlir::TokenType>(type))))) {
    return op->emitOpError(valueKind) << " #" << valueIndex
        << " must be variadic of any non-token type, but got " << type;
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_Seq1(
    ::mlir::Attribute attr, ::llvm::StringRef attrName, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  if (attr && !(((::llvm::isa<::mlir::IntegerAttr>(attr))) && ((::llvm::cast<::mlir::IntegerAttr>(attr).getType().isSignlessInteger(64)))))
    return emitError() << "attribute '" << attrName
        << "' failed to satisfy constraint: 64-bit signless integer attribute";
  return ::mlir::success();
}
static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_Seq1(
    ::mlir::Operation *op, ::mlir::Attribute attr, ::llvm::StringRef attrName) {
  return __mlir_ods_local_attr_constraint_Seq1(attr, attrName, [op]() {
    return op->emitOpError();
  });
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_Seq2(
    ::mlir::Attribute attr, ::llvm::StringRef attrName, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  if (attr && !((::llvm::isa<::circt::hw::InnerSymAttr>(attr))))
    return emitError() << "attribute '" << attrName
        << "' failed to satisfy constraint: Inner symbol definition";
  return ::mlir::success();
}
static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_Seq2(
    ::mlir::Operation *op, ::mlir::Attribute attr, ::llvm::StringRef attrName) {
  return __mlir_ods_local_attr_constraint_Seq2(attr, attrName, [op]() {
    return op->emitOpError();
  });
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_Seq3(
    ::mlir::Attribute attr, ::llvm::StringRef attrName, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  if (attr && !((::llvm::isa<::mlir::StringAttr>(attr))))
    return emitError() << "attribute '" << attrName
        << "' failed to satisfy constraint: string attribute";
  return ::mlir::success();
}
static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_Seq3(
    ::mlir::Operation *op, ::mlir::Attribute attr, ::llvm::StringRef attrName) {
  return __mlir_ods_local_attr_constraint_Seq3(attr, attrName, [op]() {
    return op->emitOpError();
  });
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_Seq4(
    ::mlir::Attribute attr, ::llvm::StringRef attrName, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  if (attr && !((::llvm::isa<::circt::seq::ClockConstAttr>(attr))))
    return emitError() << "attribute '" << attrName
        << "' failed to satisfy constraint: clock constant";
  return ::mlir::success();
}
static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_Seq4(
    ::mlir::Operation *op, ::mlir::Attribute attr, ::llvm::StringRef attrName) {
  return __mlir_ods_local_attr_constraint_Seq4(attr, attrName, [op]() {
    return op->emitOpError();
  });
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_Seq5(
    ::mlir::Attribute attr, ::llvm::StringRef attrName, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  if (attr && !((((::llvm::isa<::mlir::IntegerAttr>(attr))) && ((::llvm::cast<::mlir::IntegerAttr>(attr).getType().isSignlessInteger(64)))) && ((::llvm::cast<::mlir::IntegerAttr>(attr).getInt() >= 1))))
    return emitError() << "attribute '" << attrName
        << "' failed to satisfy constraint: 64-bit signless integer attribute whose minimum value is 1";
  return ::mlir::success();
}
static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_Seq5(
    ::mlir::Operation *op, ::mlir::Attribute attr, ::llvm::StringRef attrName) {
  return __mlir_ods_local_attr_constraint_Seq5(attr, attrName, [op]() {
    return op->emitOpError();
  });
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_Seq6(
    ::mlir::Attribute attr, ::llvm::StringRef attrName, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  if (attr && !((((::llvm::isa<::mlir::IntegerAttr>(attr))) && ((::llvm::cast<::mlir::IntegerAttr>(attr).getType().isSignlessInteger(64)))) && ((::llvm::cast<::mlir::IntegerAttr>(attr).getInt() >= 0))))
    return emitError() << "attribute '" << attrName
        << "' failed to satisfy constraint: 64-bit signless integer attribute whose minimum value is 0";
  return ::mlir::success();
}
static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_Seq6(
    ::mlir::Operation *op, ::mlir::Attribute attr, ::llvm::StringRef attrName) {
  return __mlir_ods_local_attr_constraint_Seq6(attr, attrName, [op]() {
    return op->emitOpError();
  });
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_Seq7(
    ::mlir::Attribute attr, ::llvm::StringRef attrName, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  if (attr && !(((::llvm::isa<::mlir::IntegerAttr>(attr))) && ((::llvm::cast<::mlir::IntegerAttr>(attr).getType().isSignlessInteger(32)))))
    return emitError() << "attribute '" << attrName
        << "' failed to satisfy constraint: 32-bit signless integer attribute";
  return ::mlir::success();
}
static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_Seq7(
    ::mlir::Operation *op, ::mlir::Attribute attr, ::llvm::StringRef attrName) {
  return __mlir_ods_local_attr_constraint_Seq7(attr, attrName, [op]() {
    return op->emitOpError();
  });
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_Seq8(
    ::mlir::Attribute attr, ::llvm::StringRef attrName, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  if (attr && !((::llvm::isa<circt::seq::RUWAttr>(attr))))
    return emitError() << "attribute '" << attrName
        << "' failed to satisfy constraint: Read-Under-Write Behavior";
  return ::mlir::success();
}
static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_Seq8(
    ::mlir::Operation *op, ::mlir::Attribute attr, ::llvm::StringRef attrName) {
  return __mlir_ods_local_attr_constraint_Seq8(attr, attrName, [op]() {
    return op->emitOpError();
  });
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_Seq9(
    ::mlir::Attribute attr, ::llvm::StringRef attrName, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  if (attr && !((::llvm::isa<circt::seq::WUWAttr>(attr))))
    return emitError() << "attribute '" << attrName
        << "' failed to satisfy constraint: Write-Under-Write Behavior";
  return ::mlir::success();
}
static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_Seq9(
    ::mlir::Operation *op, ::mlir::Attribute attr, ::llvm::StringRef attrName) {
  return __mlir_ods_local_attr_constraint_Seq9(attr, attrName, [op]() {
    return op->emitOpError();
  });
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_Seq10(
    ::mlir::Attribute attr, ::llvm::StringRef attrName, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  if (attr && !((::llvm::isa<::circt::seq::FirMemInitAttr>(attr))))
    return emitError() << "attribute '" << attrName
        << "' failed to satisfy constraint: Memory initialization information";
  return ::mlir::success();
}
static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_Seq10(
    ::mlir::Operation *op, ::mlir::Attribute attr, ::llvm::StringRef attrName) {
  return __mlir_ods_local_attr_constraint_Seq10(attr, attrName, [op]() {
    return op->emitOpError();
  });
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_Seq11(
    ::mlir::Attribute attr, ::llvm::StringRef attrName, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  if (attr && !((true)))
    return emitError() << "attribute '" << attrName
        << "' failed to satisfy constraint: any attribute";
  return ::mlir::success();
}
static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_Seq11(
    ::mlir::Operation *op, ::mlir::Attribute attr, ::llvm::StringRef attrName) {
  return __mlir_ods_local_attr_constraint_Seq11(attr, attrName, [op]() {
    return op->emitOpError();
  });
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_Seq12(
    ::mlir::Attribute attr, ::llvm::StringRef attrName, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  if (attr && !((::llvm::isa<::mlir::IntegerAttr>(attr))))
    return emitError() << "attribute '" << attrName
        << "' failed to satisfy constraint: arbitrary integer attribute";
  return ::mlir::success();
}
static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_Seq12(
    ::mlir::Operation *op, ::mlir::Attribute attr, ::llvm::StringRef attrName) {
  return __mlir_ods_local_attr_constraint_Seq12(attr, attrName, [op]() {
    return op->emitOpError();
  });
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_Seq13(
    ::mlir::Attribute attr, ::llvm::StringRef attrName, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  if (attr && !((::llvm::isa<::mlir::UnitAttr>(attr))))
    return emitError() << "attribute '" << attrName
        << "' failed to satisfy constraint: unit attribute";
  return ::mlir::success();
}
static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_Seq13(
    ::mlir::Operation *op, ::mlir::Attribute attr, ::llvm::StringRef attrName) {
  return __mlir_ods_local_attr_constraint_Seq13(attr, attrName, [op]() {
    return op->emitOpError();
  });
}

static ::llvm::LogicalResult __mlir_ods_local_region_constraint_Seq1(
    ::mlir::Operation *op, ::mlir::Region &region, ::llvm::StringRef regionName,
    unsigned regionIndex) {
  if (!((::llvm::hasNItems(region, 1)))) {
    return op->emitOpError("region #") << regionIndex
        << (regionName.empty() ? " " : " ('" + regionName + "') ")
        << "failed to verify constraint: region with 1 blocks";
  }
  return ::mlir::success();
}
namespace circt::seq {


//===----------------------------------------------------------------------===//
// ::circt::seq::ClockDividerOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

ClockDividerOpGenericAdaptorBase::ClockDividerOpGenericAdaptorBase(ClockDividerOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

uint64_t ClockDividerOpGenericAdaptorBase::getPow2() {
  auto attr = getPow2Attr();
  return attr.getValue().getZExtValue();
}


} // namespace detail
ClockDividerOpAdaptor::ClockDividerOpAdaptor(ClockDividerOp op) : ClockDividerOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult ClockDividerOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_pow2 = getProperties().pow2; (void)tblgen_pow2;
  if (!tblgen_pow2) return emitError(loc, "'seq.clock_div' op requires attribute 'pow2'");

  if (tblgen_pow2 && !(((::llvm::isa<::mlir::IntegerAttr>(tblgen_pow2))) && ((::llvm::cast<::mlir::IntegerAttr>(tblgen_pow2).getType().isSignlessInteger(64)))))
    return emitError(loc, "'seq.clock_div' op attribute 'pow2' failed to satisfy constraint: 64-bit signless integer attribute");
  return ::mlir::success();
}

::llvm::LogicalResult ClockDividerOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.pow2;
       auto attr = dict.get("pow2");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `pow2` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  return ::mlir::success();
}

::mlir::Attribute ClockDividerOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.pow2;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("pow2",
                                       propStorage));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code ClockDividerOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.pow2.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> ClockDividerOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "pow2")
      return prop.pow2;
  return std::nullopt;
}

void ClockDividerOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "pow2") {
       prop.pow2 = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.pow2)>>(value);
       return;
    }
}

void ClockDividerOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.pow2) attrs.append("pow2", prop.pow2);
}

::llvm::LogicalResult ClockDividerOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getPow2AttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Seq1(attr, "pow2", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult ClockDividerOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.pow2)))
    return ::mlir::failure();
  return ::mlir::success();
}

void ClockDividerOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.pow2);
}

uint64_t ClockDividerOp::getPow2() {
  auto attr = getPow2Attr();
  return attr.getValue().getZExtValue();
}

void ClockDividerOp::setPow2(uint64_t attrValue) {
  getProperties().pow2 = ::mlir::Builder((*this)->getContext()).getIntegerAttr(::mlir::Builder((*this)->getContext()).getIntegerType(64), attrValue);
}

void ClockDividerOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type output, ::mlir::Value input, ::mlir::IntegerAttr pow2) {
  odsState.addOperands(input);
  odsState.getOrAddProperties<Properties>().pow2 = pow2;
  odsState.addTypes(output);
}

ClockDividerOp ClockDividerOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type output, ::mlir::Value input, ::mlir::IntegerAttr pow2) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(output)>(output), std::forward<decltype(input)>(input), std::forward<decltype(pow2)>(pow2));
  auto __res__ = ::llvm::dyn_cast<ClockDividerOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ClockDividerOp ClockDividerOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type output, ::mlir::Value input, ::mlir::IntegerAttr pow2) {
  return create(builder, builder.getLoc(), std::forward<decltype(output)>(output), std::forward<decltype(input)>(input), std::forward<decltype(pow2)>(pow2));
}

void ClockDividerOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value input, ::mlir::IntegerAttr pow2) {
  odsState.addOperands(input);
  odsState.getOrAddProperties<Properties>().pow2 = pow2;

        ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
        if (::mlir::succeeded(ClockDividerOp::inferReturnTypes(odsBuilder.getContext(),
                      odsState.location, odsState.operands,
                      odsState.attributes.getDictionary(odsState.getContext()),
                      odsState.getRawProperties(),
                      odsState.regions, inferredReturnTypes)))
          odsState.addTypes(inferredReturnTypes);
        else
          ::mlir::detail::reportFatalInferReturnTypesError(odsState);
        
}

ClockDividerOp ClockDividerOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value input, ::mlir::IntegerAttr pow2) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(input)>(input), std::forward<decltype(pow2)>(pow2));
  auto __res__ = ::llvm::dyn_cast<ClockDividerOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ClockDividerOp ClockDividerOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value input, ::mlir::IntegerAttr pow2) {
  return create(builder, builder.getLoc(), std::forward<decltype(input)>(input), std::forward<decltype(pow2)>(pow2));
}

void ClockDividerOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value input, ::mlir::IntegerAttr pow2) {
  odsState.addOperands(input);
  odsState.getOrAddProperties<Properties>().pow2 = pow2;
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

ClockDividerOp ClockDividerOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value input, ::mlir::IntegerAttr pow2) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(input)>(input), std::forward<decltype(pow2)>(pow2));
  auto __res__ = ::llvm::dyn_cast<ClockDividerOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ClockDividerOp ClockDividerOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value input, ::mlir::IntegerAttr pow2) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(input)>(input), std::forward<decltype(pow2)>(pow2));
}

void ClockDividerOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type output, ::mlir::Value input, uint64_t pow2) {
  odsState.addOperands(input);
  odsState.getOrAddProperties<Properties>().pow2 = odsBuilder.getIntegerAttr(odsBuilder.getIntegerType(64), pow2);
  odsState.addTypes(output);
}

ClockDividerOp ClockDividerOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type output, ::mlir::Value input, uint64_t pow2) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(output)>(output), std::forward<decltype(input)>(input), std::forward<decltype(pow2)>(pow2));
  auto __res__ = ::llvm::dyn_cast<ClockDividerOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ClockDividerOp ClockDividerOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type output, ::mlir::Value input, uint64_t pow2) {
  return create(builder, builder.getLoc(), std::forward<decltype(output)>(output), std::forward<decltype(input)>(input), std::forward<decltype(pow2)>(pow2));
}

void ClockDividerOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value input, uint64_t pow2) {
  odsState.addOperands(input);
  odsState.getOrAddProperties<Properties>().pow2 = odsBuilder.getIntegerAttr(odsBuilder.getIntegerType(64), pow2);

        ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
        if (::mlir::succeeded(ClockDividerOp::inferReturnTypes(odsBuilder.getContext(),
                      odsState.location, odsState.operands,
                      odsState.attributes.getDictionary(odsState.getContext()),
                      odsState.getRawProperties(),
                      odsState.regions, inferredReturnTypes)))
          odsState.addTypes(inferredReturnTypes);
        else
          ::mlir::detail::reportFatalInferReturnTypesError(odsState);
        
}

ClockDividerOp ClockDividerOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value input, uint64_t pow2) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(input)>(input), std::forward<decltype(pow2)>(pow2));
  auto __res__ = ::llvm::dyn_cast<ClockDividerOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ClockDividerOp ClockDividerOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value input, uint64_t pow2) {
  return create(builder, builder.getLoc(), std::forward<decltype(input)>(input), std::forward<decltype(pow2)>(pow2));
}

void ClockDividerOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value input, uint64_t pow2) {
  odsState.addOperands(input);
  odsState.getOrAddProperties<Properties>().pow2 = odsBuilder.getIntegerAttr(odsBuilder.getIntegerType(64), pow2);
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

ClockDividerOp ClockDividerOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value input, uint64_t pow2) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(input)>(input), std::forward<decltype(pow2)>(pow2));
  auto __res__ = ::llvm::dyn_cast<ClockDividerOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ClockDividerOp ClockDividerOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value input, uint64_t pow2) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(input)>(input), std::forward<decltype(pow2)>(pow2));
}

void ClockDividerOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<ClockDividerOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

ClockDividerOp ClockDividerOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<ClockDividerOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ClockDividerOp ClockDividerOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void ClockDividerOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<ClockDividerOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
  ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
  if (::mlir::succeeded(ClockDividerOp::inferReturnTypes(odsBuilder.getContext(),
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

ClockDividerOp ClockDividerOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<ClockDividerOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ClockDividerOp ClockDividerOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void ClockDividerOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

ClockDividerOp ClockDividerOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<ClockDividerOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ClockDividerOp ClockDividerOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

void ClockDividerOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties &>(properties));
  odsState.addAttributes(discardableAttributes);

  ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
  if (::mlir::succeeded(ClockDividerOp::inferReturnTypes(odsBuilder.getContext(),
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

ClockDividerOp ClockDividerOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<ClockDividerOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ClockDividerOp ClockDividerOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult ClockDividerOp::verifyInvariantsImpl() {
  auto tblgen_pow2 = getProperties().pow2; (void)tblgen_pow2;
  if (!tblgen_pow2) return emitOpError("requires attribute 'pow2'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Seq1(*this, tblgen_pow2, "pow2")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Seq1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Seq1(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult ClockDividerOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

void ClockDividerOp::getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context) {
  results.add(canonicalize);
}

::llvm::LogicalResult ClockDividerOp::inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::PropertyRef properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes) {
  inferredReturnTypes.resize(1);
  ::mlir::Builder odsBuilder(context);
  ::mlir::Type odsInferredType0 = odsBuilder.getType<::circt::seq::ClockType>();
  inferredReturnTypes[0] = odsInferredType0;
  return ::mlir::success();
}

::mlir::ParseResult ClockDividerOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::OpAsmParser::UnresolvedOperand inputRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> inputOperands(&inputRawOperand, 1);  ::llvm::SMLoc inputOperandsLoc;
  (void)inputOperandsLoc;
  ::mlir::IntegerAttr pow2Attr;

  inputOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(inputRawOperand))
    return ::mlir::failure();
  if (parser.parseKeyword("by"))
    return ::mlir::failure();

  if (parser.parseCustomAttributeWithFallback(pow2Attr, parser.getBuilder().getIntegerType(64))) {
    return ::mlir::failure();
  }
  if (pow2Attr) result.getOrAddProperties<ClockDividerOp::Properties>().pow2 = pow2Attr;
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
  result.addTypes(odsBuildableType0);
  if (parser.resolveOperands(inputOperands, odsBuildableType0, inputOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void ClockDividerOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter << getInput();
  _odsPrinter << ' ' << "by";
  _odsPrinter << ' ';
  _odsPrinter.printAttributeWithoutType(getPow2Attr());
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("pow2");
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
}

void ClockDividerOp::getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects) {
}


} // namespace circt::seq
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::seq::ClockDividerOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::seq::detail::ClockDividerOpGenericAdaptorBase::Properties)

namespace circt::seq {


//===----------------------------------------------------------------------===//
// ::circt::seq::ClockGateOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

ClockGateOpGenericAdaptorBase::ClockGateOpGenericAdaptorBase(ClockGateOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

std::pair<unsigned, unsigned> ClockGateOpGenericAdaptorBase::getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
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

::std::optional<::circt::hw::InnerSymAttr> ClockGateOpGenericAdaptorBase::getInnerSym() {
  auto attr = getInnerSymAttr();
  return attr ? ::std::optional<::circt::hw::InnerSymAttr>(::llvm::cast<::circt::hw::InnerSymAttr>(attr)) : (::std::nullopt);
}


} // namespace detail
ClockGateOpAdaptor::ClockGateOpAdaptor(ClockGateOp op) : ClockGateOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult ClockGateOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_inner_sym = getProperties().inner_sym; (void)tblgen_inner_sym;

  if (tblgen_inner_sym && !((::llvm::isa<::circt::hw::InnerSymAttr>(tblgen_inner_sym))))
    return emitError(loc, "'seq.clock_gate' op attribute 'inner_sym' failed to satisfy constraint: Inner symbol definition");
  return ::mlir::success();
}

std::pair<unsigned, unsigned> ClockGateOp::getODSOperandIndexAndLength(unsigned index) {
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

::mlir::MutableOperandRange ClockGateOp::getTestEnableMutable() {
  auto range = getODSOperandIndexAndLength(2);
  auto mutableRange = ::mlir::MutableOperandRange(getOperation(), range.first, range.second);
  return mutableRange;
}

::llvm::LogicalResult ClockGateOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
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
  return ::mlir::success();
}

::mlir::Attribute ClockGateOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.inner_sym;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("inner_sym",
                                       propStorage));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code ClockGateOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.inner_sym.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> ClockGateOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "inner_sym")
      return prop.inner_sym;
  return std::nullopt;
}

void ClockGateOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "inner_sym") {
       prop.inner_sym = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.inner_sym)>>(value);
       return;
    }
}

void ClockGateOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.inner_sym) attrs.append("inner_sym", prop.inner_sym);
}

::llvm::LogicalResult ClockGateOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getInnerSymAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Seq2(attr, "inner_sym", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult ClockGateOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readOptionalAttribute(prop.inner_sym)))
    return ::mlir::failure();
  return ::mlir::success();
}

void ClockGateOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;

  writer.writeOptionalAttribute(prop.inner_sym);
}

::std::optional<::circt::hw::InnerSymAttr> ClockGateOp::getInnerSym() {
  auto attr = getInnerSymAttr();
  return attr ? ::std::optional<::circt::hw::InnerSymAttr>(::llvm::cast<::circt::hw::InnerSymAttr>(attr)) : (::std::nullopt);
}

void ClockGateOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value clock, Value enable) {
      build(odsBuilder, odsState, clock, enable, Value(), hw::InnerSymAttr());
    
}

ClockGateOp ClockGateOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, Value clock, Value enable) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(clock)>(clock), std::forward<decltype(enable)>(enable));
  auto __res__ = ::llvm::dyn_cast<ClockGateOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ClockGateOp ClockGateOp::create(::mlir::ImplicitLocOpBuilder &builder, Value clock, Value enable) {
  return create(builder, builder.getLoc(), std::forward<decltype(clock)>(clock), std::forward<decltype(enable)>(enable));
}

void ClockGateOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type output, ::mlir::Value input, ::mlir::Value enable, /*optional*/::mlir::Value test_enable, /*optional*/::circt::hw::InnerSymAttr inner_sym) {
  odsState.addOperands(input);
  odsState.addOperands(enable);
  if (test_enable)
    odsState.addOperands(test_enable);
  if (inner_sym) {
    odsState.getOrAddProperties<Properties>().inner_sym = inner_sym;
  }
  odsState.addTypes(output);
}

ClockGateOp ClockGateOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type output, ::mlir::Value input, ::mlir::Value enable, /*optional*/::mlir::Value test_enable, /*optional*/::circt::hw::InnerSymAttr inner_sym) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(output)>(output), std::forward<decltype(input)>(input), std::forward<decltype(enable)>(enable), std::forward<decltype(test_enable)>(test_enable), std::forward<decltype(inner_sym)>(inner_sym));
  auto __res__ = ::llvm::dyn_cast<ClockGateOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ClockGateOp ClockGateOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type output, ::mlir::Value input, ::mlir::Value enable, /*optional*/::mlir::Value test_enable, /*optional*/::circt::hw::InnerSymAttr inner_sym) {
  return create(builder, builder.getLoc(), std::forward<decltype(output)>(output), std::forward<decltype(input)>(input), std::forward<decltype(enable)>(enable), std::forward<decltype(test_enable)>(test_enable), std::forward<decltype(inner_sym)>(inner_sym));
}

void ClockGateOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value input, ::mlir::Value enable, /*optional*/::mlir::Value test_enable, /*optional*/::circt::hw::InnerSymAttr inner_sym) {
  odsState.addOperands(input);
  odsState.addOperands(enable);
  if (test_enable)
    odsState.addOperands(test_enable);
  if (inner_sym) {
    odsState.getOrAddProperties<Properties>().inner_sym = inner_sym;
  }

        ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
        if (::mlir::succeeded(ClockGateOp::inferReturnTypes(odsBuilder.getContext(),
                      odsState.location, odsState.operands,
                      odsState.attributes.getDictionary(odsState.getContext()),
                      odsState.getRawProperties(),
                      odsState.regions, inferredReturnTypes)))
          odsState.addTypes(inferredReturnTypes);
        else
          ::mlir::detail::reportFatalInferReturnTypesError(odsState);
        
}

ClockGateOp ClockGateOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value input, ::mlir::Value enable, /*optional*/::mlir::Value test_enable, /*optional*/::circt::hw::InnerSymAttr inner_sym) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(input)>(input), std::forward<decltype(enable)>(enable), std::forward<decltype(test_enable)>(test_enable), std::forward<decltype(inner_sym)>(inner_sym));
  auto __res__ = ::llvm::dyn_cast<ClockGateOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ClockGateOp ClockGateOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value input, ::mlir::Value enable, /*optional*/::mlir::Value test_enable, /*optional*/::circt::hw::InnerSymAttr inner_sym) {
  return create(builder, builder.getLoc(), std::forward<decltype(input)>(input), std::forward<decltype(enable)>(enable), std::forward<decltype(test_enable)>(test_enable), std::forward<decltype(inner_sym)>(inner_sym));
}

void ClockGateOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value input, ::mlir::Value enable, /*optional*/::mlir::Value test_enable, /*optional*/::circt::hw::InnerSymAttr inner_sym) {
  odsState.addOperands(input);
  odsState.addOperands(enable);
  if (test_enable)
    odsState.addOperands(test_enable);
  if (inner_sym) {
    odsState.getOrAddProperties<Properties>().inner_sym = inner_sym;
  }
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

ClockGateOp ClockGateOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value input, ::mlir::Value enable, /*optional*/::mlir::Value test_enable, /*optional*/::circt::hw::InnerSymAttr inner_sym) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(input)>(input), std::forward<decltype(enable)>(enable), std::forward<decltype(test_enable)>(test_enable), std::forward<decltype(inner_sym)>(inner_sym));
  auto __res__ = ::llvm::dyn_cast<ClockGateOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ClockGateOp ClockGateOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value input, ::mlir::Value enable, /*optional*/::mlir::Value test_enable, /*optional*/::circt::hw::InnerSymAttr inner_sym) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(input)>(input), std::forward<decltype(enable)>(enable), std::forward<decltype(test_enable)>(test_enable), std::forward<decltype(inner_sym)>(inner_sym));
}

void ClockGateOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() >= 2u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<ClockGateOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

ClockGateOp ClockGateOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<ClockGateOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ClockGateOp ClockGateOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void ClockGateOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() >= 2u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<ClockGateOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
  ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
  if (::mlir::succeeded(ClockGateOp::inferReturnTypes(odsBuilder.getContext(),
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

ClockGateOp ClockGateOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<ClockGateOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ClockGateOp ClockGateOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void ClockGateOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() >= 2u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

ClockGateOp ClockGateOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<ClockGateOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ClockGateOp ClockGateOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

void ClockGateOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() >= 2u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties &>(properties));
  odsState.addAttributes(discardableAttributes);

  ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
  if (::mlir::succeeded(ClockGateOp::inferReturnTypes(odsBuilder.getContext(),
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

ClockGateOp ClockGateOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<ClockGateOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ClockGateOp ClockGateOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult ClockGateOp::verifyInvariantsImpl() {
  auto tblgen_inner_sym = getProperties().inner_sym; (void)tblgen_inner_sym;

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Seq2(*this, tblgen_inner_sym, "inner_sym")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Seq1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSOperands(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Seq2(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup2 = getODSOperands(2);

    if (valueGroup2.size() > 1) {
      return emitOpError("operand group starting at #") << index
          << " requires 0 or 1 element, but found " << valueGroup2.size();
    }

    for (auto v : valueGroup2) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Seq2(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Seq1(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  if (!((((*this->getODSOperands(0).begin()).getType()) == ((*this->getODSResults(0).begin()).getType()) && ((*this->getODSResults(0).begin()).getType()) == ((*this->getODSOperands(0).begin()).getType()))))
    return emitOpError("failed to verify that all of {input, output} have same type");
  return ::mlir::success();
}

::llvm::LogicalResult ClockGateOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

void ClockGateOp::getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context) {
  results.add(canonicalize);
}

::llvm::LogicalResult ClockGateOp::inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::PropertyRef properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes) {
  inferredReturnTypes.resize(1);
  ::mlir::Builder odsBuilder(context);
  ::mlir::Type odsInferredType0 = odsBuilder.getType<::circt::seq::ClockType>();
  inferredReturnTypes[0] = odsInferredType0;
  return ::mlir::success();
}

::mlir::ParseResult ClockGateOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::OpAsmParser::UnresolvedOperand inputRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> inputOperands(&inputRawOperand, 1);  ::llvm::SMLoc inputOperandsLoc;
  (void)inputOperandsLoc;
  ::mlir::OpAsmParser::UnresolvedOperand enableRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> enableOperands(&enableRawOperand, 1);  ::llvm::SMLoc enableOperandsLoc;
  (void)enableOperandsLoc;
  ::llvm::SmallVector<::mlir::OpAsmParser::UnresolvedOperand, 4> test_enableOperands;
  ::llvm::SMLoc test_enableOperandsLoc;
  (void)test_enableOperandsLoc;
  ::circt::hw::InnerSymAttr inner_symAttr;

  inputOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(inputRawOperand))
    return ::mlir::failure();
  if (parser.parseComma())
    return ::mlir::failure();

  enableOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(enableRawOperand))
    return ::mlir::failure();
  if (::mlir::succeeded(parser.parseOptionalComma())) {

  {
    test_enableOperandsLoc = parser.getCurrentLocation();
    ::mlir::OpAsmParser::UnresolvedOperand operand;
    ::mlir::OptionalParseResult parseResult =
                                    parser.parseOptionalOperand(operand);
    if (parseResult.has_value()) {
      if (failed(*parseResult))
        return ::mlir::failure();
      test_enableOperands.push_back(operand);
    }
  }
  }
  if (::mlir::succeeded(parser.parseOptionalKeyword("sym"))) {

  if (parser.parseCustomAttributeWithFallback(inner_symAttr, ::mlir::Type{})) {
    return ::mlir::failure();
  }
  if (inner_symAttr) result.getOrAddProperties<ClockGateOp::Properties>().inner_sym = inner_symAttr;
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
  ::mlir::Type odsBuildableType0 = parser.getBuilder().getType<::circt::seq::ClockType>();
  ::mlir::Type odsBuildableType1 = parser.getBuilder().getIntegerType(1);
  result.addTypes(odsBuildableType0);
  if (parser.resolveOperands(inputOperands, odsBuildableType0, inputOperandsLoc, result.operands))
    return ::mlir::failure();
  if (parser.resolveOperands(enableOperands, odsBuildableType1, enableOperandsLoc, result.operands))
    return ::mlir::failure();
  if (!test_enableOperands.empty()) {
  if (parser.resolveOperands(test_enableOperands, odsBuildableType1, test_enableOperandsLoc, result.operands))
    return ::mlir::failure();
  }
  return ::mlir::success();
}

void ClockGateOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter << getInput();
  _odsPrinter << ",";
  _odsPrinter << ' ';
  _odsPrinter << getEnable();
  if (getTestEnable()) {
    _odsPrinter << ",";
    _odsPrinter << ' ';
    if (::mlir::Value value = getTestEnable())
      _odsPrinter << value;
  }
  if (getInnerSymAttr()) {
    _odsPrinter << ' ' << "sym";
    _odsPrinter << ' ';
  _odsPrinter.printStrippedAttrOrType(getInnerSymAttr());
  }
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("inner_sym");
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
}

void ClockGateOp::getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects) {
}


} // namespace circt::seq
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::seq::ClockGateOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::seq::detail::ClockGateOpGenericAdaptorBase::Properties)

namespace circt::seq {


//===----------------------------------------------------------------------===//
// ::circt::seq::ClockInverterOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

ClockInverterOpGenericAdaptorBase::ClockInverterOpGenericAdaptorBase(ClockInverterOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}


} // namespace detail
ClockInverterOpAdaptor::ClockInverterOpAdaptor(ClockInverterOp op) : ClockInverterOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult ClockInverterOpAdaptor::verify(::mlir::Location loc) {
  return ::mlir::success();
}

::llvm::LogicalResult ClockInverterOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }
      return ::mlir::success();
}

::mlir::Attribute ClockInverterOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code ClockInverterOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine();
}

std::optional<mlir::Attribute> ClockInverterOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
  return std::nullopt;
}

void ClockInverterOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
}

void ClockInverterOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
}

::llvm::LogicalResult ClockInverterOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    return ::mlir::success();
}

void ClockInverterOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type output, ::mlir::Value input) {
  odsState.addOperands(input);
  odsState.addTypes(output);
}

ClockInverterOp ClockInverterOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type output, ::mlir::Value input) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(output)>(output), std::forward<decltype(input)>(input));
  auto __res__ = ::llvm::dyn_cast<ClockInverterOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ClockInverterOp ClockInverterOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type output, ::mlir::Value input) {
  return create(builder, builder.getLoc(), std::forward<decltype(output)>(output), std::forward<decltype(input)>(input));
}

void ClockInverterOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value input) {
  odsState.addOperands(input);

        ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
        if (::mlir::succeeded(ClockInverterOp::inferReturnTypes(odsBuilder.getContext(),
                      odsState.location, odsState.operands,
                      odsState.attributes.getDictionary(odsState.getContext()),
                      odsState.getRawProperties(),
                      odsState.regions, inferredReturnTypes)))
          odsState.addTypes(inferredReturnTypes);
        else
          ::mlir::detail::reportFatalInferReturnTypesError(odsState);
        
}

ClockInverterOp ClockInverterOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value input) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(input)>(input));
  auto __res__ = ::llvm::dyn_cast<ClockInverterOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ClockInverterOp ClockInverterOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value input) {
  return create(builder, builder.getLoc(), std::forward<decltype(input)>(input));
}

void ClockInverterOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value input) {
  odsState.addOperands(input);
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

ClockInverterOp ClockInverterOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value input) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(input)>(input));
  auto __res__ = ::llvm::dyn_cast<ClockInverterOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ClockInverterOp ClockInverterOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value input) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(input)>(input));
}

void ClockInverterOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

ClockInverterOp ClockInverterOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<ClockInverterOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ClockInverterOp ClockInverterOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void ClockInverterOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);

  ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
  if (::mlir::succeeded(ClockInverterOp::inferReturnTypes(odsBuilder.getContext(),
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

ClockInverterOp ClockInverterOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<ClockInverterOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ClockInverterOp ClockInverterOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void ClockInverterOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

ClockInverterOp ClockInverterOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<ClockInverterOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ClockInverterOp ClockInverterOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

void ClockInverterOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties &>(properties));
  odsState.addAttributes(discardableAttributes);

  ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
  if (::mlir::succeeded(ClockInverterOp::inferReturnTypes(odsBuilder.getContext(),
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

ClockInverterOp ClockInverterOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<ClockInverterOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ClockInverterOp ClockInverterOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult ClockInverterOp::verifyInvariantsImpl() {
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Seq1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Seq1(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult ClockInverterOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::llvm::LogicalResult ClockInverterOp::inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::PropertyRef properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes) {
  inferredReturnTypes.resize(1);
  ::mlir::Builder odsBuilder(context);
  ::mlir::Type odsInferredType0 = odsBuilder.getType<::circt::seq::ClockType>();
  inferredReturnTypes[0] = odsInferredType0;
  return ::mlir::success();
}

::mlir::ParseResult ClockInverterOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::OpAsmParser::UnresolvedOperand inputRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> inputOperands(&inputRawOperand, 1);  ::llvm::SMLoc inputOperandsLoc;
  (void)inputOperandsLoc;

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
  ::mlir::Type odsBuildableType0 = parser.getBuilder().getType<::circt::seq::ClockType>();
  result.addTypes(odsBuildableType0);
  if (parser.resolveOperands(inputOperands, odsBuildableType0, inputOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void ClockInverterOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter << getInput();
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
}

void ClockInverterOp::getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects) {
}


} // namespace circt::seq
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::seq::ClockInverterOp)

namespace circt::seq {


//===----------------------------------------------------------------------===//
// ::circt::seq::ClockMuxOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

ClockMuxOpGenericAdaptorBase::ClockMuxOpGenericAdaptorBase(ClockMuxOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}


} // namespace detail
ClockMuxOpAdaptor::ClockMuxOpAdaptor(ClockMuxOp op) : ClockMuxOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult ClockMuxOpAdaptor::verify(::mlir::Location loc) {
  return ::mlir::success();
}

::llvm::LogicalResult ClockMuxOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }
      return ::mlir::success();
}

::mlir::Attribute ClockMuxOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code ClockMuxOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine();
}

std::optional<mlir::Attribute> ClockMuxOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
  return std::nullopt;
}

void ClockMuxOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
}

void ClockMuxOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
}

::llvm::LogicalResult ClockMuxOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    return ::mlir::success();
}

void ClockMuxOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value cond, ::mlir::Value trueClock, ::mlir::Value falseClock) {
  odsState.addOperands(cond);
  odsState.addOperands(trueClock);
  odsState.addOperands(falseClock);
  odsState.addTypes(result);
}

ClockMuxOp ClockMuxOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value cond, ::mlir::Value trueClock, ::mlir::Value falseClock) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(result)>(result), std::forward<decltype(cond)>(cond), std::forward<decltype(trueClock)>(trueClock), std::forward<decltype(falseClock)>(falseClock));
  auto __res__ = ::llvm::dyn_cast<ClockMuxOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ClockMuxOp ClockMuxOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value cond, ::mlir::Value trueClock, ::mlir::Value falseClock) {
  return create(builder, builder.getLoc(), std::forward<decltype(result)>(result), std::forward<decltype(cond)>(cond), std::forward<decltype(trueClock)>(trueClock), std::forward<decltype(falseClock)>(falseClock));
}

void ClockMuxOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value cond, ::mlir::Value trueClock, ::mlir::Value falseClock) {
  odsState.addOperands(cond);
  odsState.addOperands(trueClock);
  odsState.addOperands(falseClock);

        ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
        if (::mlir::succeeded(ClockMuxOp::inferReturnTypes(odsBuilder.getContext(),
                      odsState.location, odsState.operands,
                      odsState.attributes.getDictionary(odsState.getContext()),
                      odsState.getRawProperties(),
                      odsState.regions, inferredReturnTypes)))
          odsState.addTypes(inferredReturnTypes);
        else
          ::mlir::detail::reportFatalInferReturnTypesError(odsState);
        
}

ClockMuxOp ClockMuxOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value cond, ::mlir::Value trueClock, ::mlir::Value falseClock) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(cond)>(cond), std::forward<decltype(trueClock)>(trueClock), std::forward<decltype(falseClock)>(falseClock));
  auto __res__ = ::llvm::dyn_cast<ClockMuxOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ClockMuxOp ClockMuxOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value cond, ::mlir::Value trueClock, ::mlir::Value falseClock) {
  return create(builder, builder.getLoc(), std::forward<decltype(cond)>(cond), std::forward<decltype(trueClock)>(trueClock), std::forward<decltype(falseClock)>(falseClock));
}

void ClockMuxOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value cond, ::mlir::Value trueClock, ::mlir::Value falseClock) {
  odsState.addOperands(cond);
  odsState.addOperands(trueClock);
  odsState.addOperands(falseClock);
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

ClockMuxOp ClockMuxOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value cond, ::mlir::Value trueClock, ::mlir::Value falseClock) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(cond)>(cond), std::forward<decltype(trueClock)>(trueClock), std::forward<decltype(falseClock)>(falseClock));
  auto __res__ = ::llvm::dyn_cast<ClockMuxOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ClockMuxOp ClockMuxOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value cond, ::mlir::Value trueClock, ::mlir::Value falseClock) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(cond)>(cond), std::forward<decltype(trueClock)>(trueClock), std::forward<decltype(falseClock)>(falseClock));
}

void ClockMuxOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 3u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

ClockMuxOp ClockMuxOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<ClockMuxOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ClockMuxOp ClockMuxOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void ClockMuxOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 3u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);

  ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
  if (::mlir::succeeded(ClockMuxOp::inferReturnTypes(odsBuilder.getContext(),
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

ClockMuxOp ClockMuxOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<ClockMuxOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ClockMuxOp ClockMuxOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void ClockMuxOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 3u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

ClockMuxOp ClockMuxOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<ClockMuxOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ClockMuxOp ClockMuxOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

void ClockMuxOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 3u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties &>(properties));
  odsState.addAttributes(discardableAttributes);

  ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
  if (::mlir::succeeded(ClockMuxOp::inferReturnTypes(odsBuilder.getContext(),
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

ClockMuxOp ClockMuxOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<ClockMuxOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ClockMuxOp ClockMuxOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult ClockMuxOp::verifyInvariantsImpl() {
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Seq2(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSOperands(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Seq1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup2 = getODSOperands(2);

    for (auto v : valueGroup2) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Seq1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Seq1(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult ClockMuxOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::llvm::LogicalResult ClockMuxOp::inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::PropertyRef properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes) {
  inferredReturnTypes.resize(1);
  ::mlir::Builder odsBuilder(context);
  ::mlir::Type odsInferredType0 = odsBuilder.getType<::circt::seq::ClockType>();
  inferredReturnTypes[0] = odsInferredType0;
  return ::mlir::success();
}

::mlir::ParseResult ClockMuxOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::OpAsmParser::UnresolvedOperand condRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> condOperands(&condRawOperand, 1);  ::llvm::SMLoc condOperandsLoc;
  (void)condOperandsLoc;
  ::mlir::OpAsmParser::UnresolvedOperand trueClockRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> trueClockOperands(&trueClockRawOperand, 1);  ::llvm::SMLoc trueClockOperandsLoc;
  (void)trueClockOperandsLoc;
  ::mlir::OpAsmParser::UnresolvedOperand falseClockRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> falseClockOperands(&falseClockRawOperand, 1);  ::llvm::SMLoc falseClockOperandsLoc;
  (void)falseClockOperandsLoc;

  condOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(condRawOperand))
    return ::mlir::failure();
  if (parser.parseComma())
    return ::mlir::failure();

  trueClockOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(trueClockRawOperand))
    return ::mlir::failure();
  if (parser.parseComma())
    return ::mlir::failure();

  falseClockOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(falseClockRawOperand))
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
  ::mlir::Type odsBuildableType0 = parser.getBuilder().getType<::circt::seq::ClockType>();
  ::mlir::Type odsBuildableType1 = parser.getBuilder().getIntegerType(1);
  result.addTypes(odsBuildableType0);
  if (parser.resolveOperands(condOperands, odsBuildableType1, condOperandsLoc, result.operands))
    return ::mlir::failure();
  if (parser.resolveOperands(trueClockOperands, odsBuildableType0, trueClockOperandsLoc, result.operands))
    return ::mlir::failure();
  if (parser.resolveOperands(falseClockOperands, odsBuildableType0, falseClockOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void ClockMuxOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter << getCond();
  _odsPrinter << ",";
  _odsPrinter << ' ';
  _odsPrinter << getTrueClock();
  _odsPrinter << ",";
  _odsPrinter << ' ';
  _odsPrinter << getFalseClock();
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
}

void ClockMuxOp::getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects) {
}


} // namespace circt::seq
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::seq::ClockMuxOp)

namespace circt::seq {


//===----------------------------------------------------------------------===//
// ::circt::seq::CompRegClockEnabledOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

CompRegClockEnabledOpGenericAdaptorBase::CompRegClockEnabledOpGenericAdaptorBase(CompRegClockEnabledOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

std::pair<unsigned, unsigned> CompRegClockEnabledOpGenericAdaptorBase::getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
  ::llvm::ArrayRef<int32_t> sizeAttr = getProperties().operandSegmentSizes;

  unsigned start = 0;
  for (unsigned i = 0; i < index; ++i)
    start += sizeAttr[i];
  return {start, sizeAttr[index]};
}

::std::optional< ::llvm::StringRef > CompRegClockEnabledOpGenericAdaptorBase::getName() {
  auto attr = getNameAttr();
  return attr ? ::std::optional< ::llvm::StringRef >(attr.getValue()) : (::std::nullopt);
}

::std::optional<::circt::hw::InnerSymAttr> CompRegClockEnabledOpGenericAdaptorBase::getInnerSym() {
  auto attr = getInnerSymAttr();
  return attr ? ::std::optional<::circt::hw::InnerSymAttr>(::llvm::cast<::circt::hw::InnerSymAttr>(attr)) : (::std::nullopt);
}


} // namespace detail
CompRegClockEnabledOpAdaptor::CompRegClockEnabledOpAdaptor(CompRegClockEnabledOp op) : CompRegClockEnabledOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult CompRegClockEnabledOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_inner_sym = getProperties().inner_sym; (void)tblgen_inner_sym;
  auto tblgen_name = getProperties().name; (void)tblgen_name;

  if (tblgen_name && !((::llvm::isa<::mlir::StringAttr>(tblgen_name))))
    return emitError(loc, "'seq.compreg.ce' op attribute 'name' failed to satisfy constraint: string attribute");

  if (tblgen_inner_sym && !((::llvm::isa<::circt::hw::InnerSymAttr>(tblgen_inner_sym))))
    return emitError(loc, "'seq.compreg.ce' op attribute 'inner_sym' failed to satisfy constraint: Inner symbol definition");
  return ::mlir::success();
}

std::pair<unsigned, unsigned> CompRegClockEnabledOp::getODSOperandIndexAndLength(unsigned index) {
  ::llvm::ArrayRef<int32_t> sizeAttr = getProperties().operandSegmentSizes;

  unsigned start = 0;
  for (unsigned i = 0; i < index; ++i)
    start += sizeAttr[i];
  return {start, sizeAttr[index]};
}

::mlir::MutableOperandRange CompRegClockEnabledOp::getResetMutable() {
  auto range = getODSOperandIndexAndLength(3);
  auto mutableRange = ::mlir::MutableOperandRange(getOperation(), range.first, range.second, ::mlir::MutableOperandRange::OperandSegment(3u, {getOperandSegmentSizesAttrName(), ::mlir::DenseI32ArrayAttr::get(getContext(), getProperties().operandSegmentSizes)}));
  return mutableRange;
}

::mlir::MutableOperandRange CompRegClockEnabledOp::getResetValueMutable() {
  auto range = getODSOperandIndexAndLength(4);
  auto mutableRange = ::mlir::MutableOperandRange(getOperation(), range.first, range.second, ::mlir::MutableOperandRange::OperandSegment(4u, {getOperandSegmentSizesAttrName(), ::mlir::DenseI32ArrayAttr::get(getContext(), getProperties().operandSegmentSizes)}));
  return mutableRange;
}

::mlir::MutableOperandRange CompRegClockEnabledOp::getInitialValueMutable() {
  auto range = getODSOperandIndexAndLength(5);
  auto mutableRange = ::mlir::MutableOperandRange(getOperation(), range.first, range.second, ::mlir::MutableOperandRange::OperandSegment(5u, {getOperandSegmentSizesAttrName(), ::mlir::DenseI32ArrayAttr::get(getContext(), getProperties().operandSegmentSizes)}));
  return mutableRange;
}

::llvm::LogicalResult CompRegClockEnabledOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
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

::mlir::Attribute CompRegClockEnabledOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
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

llvm::hash_code CompRegClockEnabledOp::computePropertiesHash(const Properties &prop) {
  auto hash_operandSegmentSizes_ = [] (const auto &propStorage) -> llvm::hash_code {
    using ::llvm::hash_value;
    return ::llvm::hash_combine_range(std::begin(propStorage), std::end(propStorage));;
  };
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.inner_sym.getAsOpaquePointer()), 
    llvm::hash_value(prop.name.getAsOpaquePointer()), 
    hash_operandSegmentSizes_(prop.operandSegmentSizes));
}

std::optional<mlir::Attribute> CompRegClockEnabledOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "inner_sym")
      return prop.inner_sym;

    if (name == "name")
      return prop.name;
    if (name == "operand_segment_sizes" || name == "operandSegmentSizes") return [&]() -> ::mlir::Attribute { return ::mlir::DenseI32ArrayAttr::get(ctx, prop.operandSegmentSizes); }();
  return std::nullopt;
}

void CompRegClockEnabledOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "inner_sym") {
       prop.inner_sym = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.inner_sym)>>(value);
       return;
    }

    if (name == "name") {
       prop.name = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.name)>>(value);
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

void CompRegClockEnabledOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.inner_sym) attrs.append("inner_sym", prop.inner_sym);

    if (prop.name) attrs.append("name", prop.name);
  attrs.append("operandSegmentSizes", [&]() -> ::mlir::Attribute { return ::mlir::DenseI32ArrayAttr::get(ctx, prop.operandSegmentSizes); }());
}

::llvm::LogicalResult CompRegClockEnabledOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getInnerSymAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Seq2(attr, "inner_sym", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getNameAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Seq3(attr, "name", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult CompRegClockEnabledOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readOptionalAttribute(prop.inner_sym)))
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

void CompRegClockEnabledOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;

  writer.writeOptionalAttribute(prop.inner_sym);

  writer.writeOptionalAttribute(prop.name);

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

::std::optional< ::llvm::StringRef > CompRegClockEnabledOp::getName() {
  auto attr = getNameAttr();
  return attr ? ::std::optional< ::llvm::StringRef >(attr.getValue()) : (::std::nullopt);
}

::std::optional<::circt::hw::InnerSymAttr> CompRegClockEnabledOp::getInnerSym() {
  auto attr = getInnerSymAttr();
  return attr ? ::std::optional<::circt::hw::InnerSymAttr>(::llvm::cast<::circt::hw::InnerSymAttr>(attr)) : (::std::nullopt);
}

void CompRegClockEnabledOp::setName(::std::optional<::llvm::StringRef> attrValue) {
    auto &odsProp = getProperties().name;
    if (attrValue)
      odsProp = ::mlir::Builder((*this)->getContext()).getStringAttr(*attrValue);
    else
      odsProp = nullptr;
}

void CompRegClockEnabledOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value input, Value clk, Value ce, StringRef name) {
      auto nameAttr = StringAttr::get(odsBuilder.getContext(), name);
      return build(odsBuilder, odsState, input.getType(), input, clk, ce,
                   nameAttr, /*reset*/ Value(), /*resetValue*/ Value(),
                   /*powerOnValue*/ Value(),
                   hw::InnerSymAttr::get(nameAttr));
    
}

CompRegClockEnabledOp CompRegClockEnabledOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, Value input, Value clk, Value ce, StringRef name) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(input)>(input), std::forward<decltype(clk)>(clk), std::forward<decltype(ce)>(ce), std::forward<decltype(name)>(name));
  auto __res__ = ::llvm::dyn_cast<CompRegClockEnabledOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

CompRegClockEnabledOp CompRegClockEnabledOp::create(::mlir::ImplicitLocOpBuilder &builder, Value input, Value clk, Value ce, StringRef name) {
  return create(builder, builder.getLoc(), std::forward<decltype(input)>(input), std::forward<decltype(clk)>(clk), std::forward<decltype(ce)>(ce), std::forward<decltype(name)>(name));
}

void CompRegClockEnabledOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value input, Value clk, Value ce, Value reset, Value rstValue, StringRef name, Value initialValue) {
      auto nameAttr = StringAttr::get(odsBuilder.getContext(), name);
      return build(odsBuilder, odsState, input.getType(), input, clk, ce,
                   nameAttr, reset, rstValue, initialValue,
                   hw::InnerSymAttr::get(nameAttr));
    
}

CompRegClockEnabledOp CompRegClockEnabledOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, Value input, Value clk, Value ce, Value reset, Value rstValue, StringRef name, Value initialValue) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(input)>(input), std::forward<decltype(clk)>(clk), std::forward<decltype(ce)>(ce), std::forward<decltype(reset)>(reset), std::forward<decltype(rstValue)>(rstValue), std::forward<decltype(name)>(name), std::forward<decltype(initialValue)>(initialValue));
  auto __res__ = ::llvm::dyn_cast<CompRegClockEnabledOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

CompRegClockEnabledOp CompRegClockEnabledOp::create(::mlir::ImplicitLocOpBuilder &builder, Value input, Value clk, Value ce, Value reset, Value rstValue, StringRef name, Value initialValue) {
  return create(builder, builder.getLoc(), std::forward<decltype(input)>(input), std::forward<decltype(clk)>(clk), std::forward<decltype(ce)>(ce), std::forward<decltype(reset)>(reset), std::forward<decltype(rstValue)>(rstValue), std::forward<decltype(name)>(name), std::forward<decltype(initialValue)>(initialValue));
}

void CompRegClockEnabledOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type data, ::mlir::Value input, ::mlir::Value clk, ::mlir::Value clockEnable, /*optional*/::mlir::StringAttr name, /*optional*/::mlir::Value reset, /*optional*/::mlir::Value resetValue, /*optional*/::mlir::Value initialValue, /*optional*/::circt::hw::InnerSymAttr inner_sym) {
  odsState.addOperands(input);
  odsState.addOperands(clk);
  odsState.addOperands(clockEnable);
  if (reset)
    odsState.addOperands(reset);
  if (resetValue)
    odsState.addOperands(resetValue);
  if (initialValue)
    odsState.addOperands(initialValue);
  ::llvm::copy(::llvm::ArrayRef<int32_t>({1, 1, 1, (reset ? 1 : 0), (resetValue ? 1 : 0), (initialValue ? 1 : 0)}), odsState.getOrAddProperties<Properties>().operandSegmentSizes.begin());
  if (name) {
    odsState.getOrAddProperties<Properties>().name = name;
  }
  if (inner_sym) {
    odsState.getOrAddProperties<Properties>().inner_sym = inner_sym;
  }
  odsState.addTypes(data);
}

CompRegClockEnabledOp CompRegClockEnabledOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type data, ::mlir::Value input, ::mlir::Value clk, ::mlir::Value clockEnable, /*optional*/::mlir::StringAttr name, /*optional*/::mlir::Value reset, /*optional*/::mlir::Value resetValue, /*optional*/::mlir::Value initialValue, /*optional*/::circt::hw::InnerSymAttr inner_sym) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(data)>(data), std::forward<decltype(input)>(input), std::forward<decltype(clk)>(clk), std::forward<decltype(clockEnable)>(clockEnable), std::forward<decltype(name)>(name), std::forward<decltype(reset)>(reset), std::forward<decltype(resetValue)>(resetValue), std::forward<decltype(initialValue)>(initialValue), std::forward<decltype(inner_sym)>(inner_sym));
  auto __res__ = ::llvm::dyn_cast<CompRegClockEnabledOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

CompRegClockEnabledOp CompRegClockEnabledOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type data, ::mlir::Value input, ::mlir::Value clk, ::mlir::Value clockEnable, /*optional*/::mlir::StringAttr name, /*optional*/::mlir::Value reset, /*optional*/::mlir::Value resetValue, /*optional*/::mlir::Value initialValue, /*optional*/::circt::hw::InnerSymAttr inner_sym) {
  return create(builder, builder.getLoc(), std::forward<decltype(data)>(data), std::forward<decltype(input)>(input), std::forward<decltype(clk)>(clk), std::forward<decltype(clockEnable)>(clockEnable), std::forward<decltype(name)>(name), std::forward<decltype(reset)>(reset), std::forward<decltype(resetValue)>(resetValue), std::forward<decltype(initialValue)>(initialValue), std::forward<decltype(inner_sym)>(inner_sym));
}

void CompRegClockEnabledOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value input, ::mlir::Value clk, ::mlir::Value clockEnable, /*optional*/::mlir::StringAttr name, /*optional*/::mlir::Value reset, /*optional*/::mlir::Value resetValue, /*optional*/::mlir::Value initialValue, /*optional*/::circt::hw::InnerSymAttr inner_sym) {
  odsState.addOperands(input);
  odsState.addOperands(clk);
  odsState.addOperands(clockEnable);
  if (reset)
    odsState.addOperands(reset);
  if (resetValue)
    odsState.addOperands(resetValue);
  if (initialValue)
    odsState.addOperands(initialValue);
  ::llvm::copy(::llvm::ArrayRef<int32_t>({1, 1, 1, (reset ? 1 : 0), (resetValue ? 1 : 0), (initialValue ? 1 : 0)}), odsState.getOrAddProperties<Properties>().operandSegmentSizes.begin());
  if (name) {
    odsState.getOrAddProperties<Properties>().name = name;
  }
  if (inner_sym) {
    odsState.getOrAddProperties<Properties>().inner_sym = inner_sym;
  }

        ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
        if (::mlir::succeeded(CompRegClockEnabledOp::inferReturnTypes(odsBuilder.getContext(),
                      odsState.location, odsState.operands,
                      odsState.attributes.getDictionary(odsState.getContext()),
                      odsState.getRawProperties(),
                      odsState.regions, inferredReturnTypes)))
          odsState.addTypes(inferredReturnTypes);
        else
          ::mlir::detail::reportFatalInferReturnTypesError(odsState);
        
}

CompRegClockEnabledOp CompRegClockEnabledOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value input, ::mlir::Value clk, ::mlir::Value clockEnable, /*optional*/::mlir::StringAttr name, /*optional*/::mlir::Value reset, /*optional*/::mlir::Value resetValue, /*optional*/::mlir::Value initialValue, /*optional*/::circt::hw::InnerSymAttr inner_sym) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(input)>(input), std::forward<decltype(clk)>(clk), std::forward<decltype(clockEnable)>(clockEnable), std::forward<decltype(name)>(name), std::forward<decltype(reset)>(reset), std::forward<decltype(resetValue)>(resetValue), std::forward<decltype(initialValue)>(initialValue), std::forward<decltype(inner_sym)>(inner_sym));
  auto __res__ = ::llvm::dyn_cast<CompRegClockEnabledOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

CompRegClockEnabledOp CompRegClockEnabledOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value input, ::mlir::Value clk, ::mlir::Value clockEnable, /*optional*/::mlir::StringAttr name, /*optional*/::mlir::Value reset, /*optional*/::mlir::Value resetValue, /*optional*/::mlir::Value initialValue, /*optional*/::circt::hw::InnerSymAttr inner_sym) {
  return create(builder, builder.getLoc(), std::forward<decltype(input)>(input), std::forward<decltype(clk)>(clk), std::forward<decltype(clockEnable)>(clockEnable), std::forward<decltype(name)>(name), std::forward<decltype(reset)>(reset), std::forward<decltype(resetValue)>(resetValue), std::forward<decltype(initialValue)>(initialValue), std::forward<decltype(inner_sym)>(inner_sym));
}

void CompRegClockEnabledOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value input, ::mlir::Value clk, ::mlir::Value clockEnable, /*optional*/::mlir::StringAttr name, /*optional*/::mlir::Value reset, /*optional*/::mlir::Value resetValue, /*optional*/::mlir::Value initialValue, /*optional*/::circt::hw::InnerSymAttr inner_sym) {
  odsState.addOperands(input);
  odsState.addOperands(clk);
  odsState.addOperands(clockEnable);
  if (reset)
    odsState.addOperands(reset);
  if (resetValue)
    odsState.addOperands(resetValue);
  if (initialValue)
    odsState.addOperands(initialValue);
  ::llvm::copy(::llvm::ArrayRef<int32_t>({1, 1, 1, (reset ? 1 : 0), (resetValue ? 1 : 0), (initialValue ? 1 : 0)}), odsState.getOrAddProperties<Properties>().operandSegmentSizes.begin());
  if (name) {
    odsState.getOrAddProperties<Properties>().name = name;
  }
  if (inner_sym) {
    odsState.getOrAddProperties<Properties>().inner_sym = inner_sym;
  }
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

CompRegClockEnabledOp CompRegClockEnabledOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value input, ::mlir::Value clk, ::mlir::Value clockEnable, /*optional*/::mlir::StringAttr name, /*optional*/::mlir::Value reset, /*optional*/::mlir::Value resetValue, /*optional*/::mlir::Value initialValue, /*optional*/::circt::hw::InnerSymAttr inner_sym) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(input)>(input), std::forward<decltype(clk)>(clk), std::forward<decltype(clockEnable)>(clockEnable), std::forward<decltype(name)>(name), std::forward<decltype(reset)>(reset), std::forward<decltype(resetValue)>(resetValue), std::forward<decltype(initialValue)>(initialValue), std::forward<decltype(inner_sym)>(inner_sym));
  auto __res__ = ::llvm::dyn_cast<CompRegClockEnabledOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

CompRegClockEnabledOp CompRegClockEnabledOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value input, ::mlir::Value clk, ::mlir::Value clockEnable, /*optional*/::mlir::StringAttr name, /*optional*/::mlir::Value reset, /*optional*/::mlir::Value resetValue, /*optional*/::mlir::Value initialValue, /*optional*/::circt::hw::InnerSymAttr inner_sym) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(input)>(input), std::forward<decltype(clk)>(clk), std::forward<decltype(clockEnable)>(clockEnable), std::forward<decltype(name)>(name), std::forward<decltype(reset)>(reset), std::forward<decltype(resetValue)>(resetValue), std::forward<decltype(initialValue)>(initialValue), std::forward<decltype(inner_sym)>(inner_sym));
}

void CompRegClockEnabledOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() >= 3u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<CompRegClockEnabledOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

CompRegClockEnabledOp CompRegClockEnabledOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<CompRegClockEnabledOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

CompRegClockEnabledOp CompRegClockEnabledOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void CompRegClockEnabledOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() >= 3u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<CompRegClockEnabledOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
  ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
  if (::mlir::succeeded(CompRegClockEnabledOp::inferReturnTypes(odsBuilder.getContext(),
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

CompRegClockEnabledOp CompRegClockEnabledOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<CompRegClockEnabledOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

CompRegClockEnabledOp CompRegClockEnabledOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void CompRegClockEnabledOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() >= 3u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

CompRegClockEnabledOp CompRegClockEnabledOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<CompRegClockEnabledOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

CompRegClockEnabledOp CompRegClockEnabledOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

void CompRegClockEnabledOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() >= 3u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties &>(properties));
  odsState.addAttributes(discardableAttributes);

  ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
  if (::mlir::succeeded(CompRegClockEnabledOp::inferReturnTypes(odsBuilder.getContext(),
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

CompRegClockEnabledOp CompRegClockEnabledOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<CompRegClockEnabledOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

CompRegClockEnabledOp CompRegClockEnabledOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult CompRegClockEnabledOp::verifyInvariantsImpl() {
  auto tblgen_inner_sym = getProperties().inner_sym; (void)tblgen_inner_sym;
  auto tblgen_name = getProperties().name; (void)tblgen_name;

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Seq3(*this, tblgen_name, "name")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Seq2(*this, tblgen_inner_sym, "inner_sym")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Seq3(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSOperands(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Seq1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup2 = getODSOperands(2);

    for (auto v : valueGroup2) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Seq2(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup3 = getODSOperands(3);

    if (valueGroup3.size() > 1) {
      return emitOpError("operand group starting at #") << index
          << " requires 0 or 1 element, but found " << valueGroup3.size();
    }

    for (auto v : valueGroup3) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Seq2(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup4 = getODSOperands(4);

    if (valueGroup4.size() > 1) {
      return emitOpError("operand group starting at #") << index
          << " requires 0 or 1 element, but found " << valueGroup4.size();
    }

    for (auto v : valueGroup4) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Seq3(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup5 = getODSOperands(5);

    if (valueGroup5.size() > 1) {
      return emitOpError("operand group starting at #") << index
          << " requires 0 or 1 element, but found " << valueGroup5.size();
    }

    for (auto v : valueGroup5) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Seq4(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Seq3(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  if (!((((*this->getODSOperands(0).begin()).getType()) == ((*this->getODSResults(0).begin()).getType()) && ((*this->getODSResults(0).begin()).getType()) == ((*this->getODSOperands(0).begin()).getType()))))
    return emitOpError("failed to verify that all of {input, data} have same type");
  return ::mlir::success();
}

::llvm::LogicalResult CompRegClockEnabledOp::verifyInvariants() {
  if(::mlir::succeeded(verifyInvariantsImpl()) && ::mlir::succeeded(verify()))
    return ::mlir::success();
  return ::mlir::failure();
}

void CompRegClockEnabledOp::getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context) {
  results.add(canonicalize);
}

::llvm::LogicalResult CompRegClockEnabledOp::inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::PropertyRef properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes) {
  inferredReturnTypes.resize(1);
  ::mlir::Builder odsBuilder(context);
  if (operands.size() <= 0)
    return ::mlir::failure();
  ::mlir::Type odsInferredType0 = operands[0].getType();
  inferredReturnTypes[0] = odsInferredType0;
  return ::mlir::success();
}

::mlir::ParseResult CompRegClockEnabledOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::circt::hw::InnerSymAttr inner_symAttr;
  ::mlir::StringAttr nameAttr;
  ::mlir::OpAsmParser::UnresolvedOperand inputRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> inputOperands(&inputRawOperand, 1);  ::llvm::SMLoc inputOperandsLoc;
  (void)inputOperandsLoc;
  ::mlir::OpAsmParser::UnresolvedOperand clkRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> clkOperands(&clkRawOperand, 1);  ::llvm::SMLoc clkOperandsLoc;
  (void)clkOperandsLoc;
  ::mlir::OpAsmParser::UnresolvedOperand clockEnableRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> clockEnableOperands(&clockEnableRawOperand, 1);  ::llvm::SMLoc clockEnableOperandsLoc;
  (void)clockEnableOperandsLoc;
  ::llvm::SmallVector<::mlir::OpAsmParser::UnresolvedOperand, 4> resetOperands;
  ::llvm::SMLoc resetOperandsLoc;
  (void)resetOperandsLoc;
  ::llvm::SmallVector<::mlir::OpAsmParser::UnresolvedOperand, 4> resetValueOperands;
  ::llvm::SMLoc resetValueOperandsLoc;
  (void)resetValueOperandsLoc;
  ::llvm::SmallVector<::mlir::OpAsmParser::UnresolvedOperand, 4> initialValueOperands;
  ::llvm::SMLoc initialValueOperandsLoc;
  (void)initialValueOperandsLoc;
  ::mlir::Type dataRawType{};
  ::llvm::ArrayRef<::mlir::Type> dataTypes(&dataRawType, 1);
  ::llvm::SmallVector<::mlir::Type, 1> resetValueTypes;
  ::llvm::SmallVector<::mlir::Type, 1> initialValueTypes;
  if (::mlir::succeeded(parser.parseOptionalKeyword("sym"))) {

  if (parser.parseCustomAttributeWithFallback(inner_symAttr, ::mlir::Type{})) {
    return ::mlir::failure();
  }
  if (inner_symAttr) result.getOrAddProperties<CompRegClockEnabledOp::Properties>().inner_sym = inner_symAttr;
  }
  {
    auto odsResult = parseImplicitSSAName(parser, nameAttr);
    if (odsResult) return ::mlir::failure();
    if (nameAttr)
      result.getOrAddProperties<CompRegClockEnabledOp::Properties>().name = nameAttr;
  }

  inputOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(inputRawOperand))
    return ::mlir::failure();
  if (parser.parseComma())
    return ::mlir::failure();

  clkOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(clkRawOperand))
    return ::mlir::failure();
  if (parser.parseComma())
    return ::mlir::failure();

  clockEnableOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(clockEnableRawOperand))
    return ::mlir::failure();
  if (::mlir::succeeded(parser.parseOptionalKeyword("reset"))) {

  {
    resetOperandsLoc = parser.getCurrentLocation();
    ::mlir::OpAsmParser::UnresolvedOperand operand;
    ::mlir::OptionalParseResult parseResult =
                                    parser.parseOptionalOperand(operand);
    if (parseResult.has_value()) {
      if (failed(*parseResult))
        return ::mlir::failure();
      resetOperands.push_back(operand);
    }
  }
  if (parser.parseComma())
    return ::mlir::failure();

  {
    resetValueOperandsLoc = parser.getCurrentLocation();
    ::mlir::OpAsmParser::UnresolvedOperand operand;
    ::mlir::OptionalParseResult parseResult =
                                    parser.parseOptionalOperand(operand);
    if (parseResult.has_value()) {
      if (failed(*parseResult))
        return ::mlir::failure();
      resetValueOperands.push_back(operand);
    }
  }
  }
  if (::mlir::succeeded(parser.parseOptionalKeyword("initial"))) {

  {
    initialValueOperandsLoc = parser.getCurrentLocation();
    ::mlir::OpAsmParser::UnresolvedOperand operand;
    ::mlir::OptionalParseResult parseResult =
                                    parser.parseOptionalOperand(operand);
    if (parseResult.has_value()) {
      if (failed(*parseResult))
        return ::mlir::failure();
      initialValueOperands.push_back(operand);
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
    dataRawType = type;
  }
  {
    ::std::optional<::mlir::OpAsmParser::UnresolvedOperand> resetValueOperand = resetValueOperands.empty() ? ::std::optional<::mlir::OpAsmParser::UnresolvedOperand>() : resetValueOperands[0];
    ::mlir::Type resetValueType;
    auto odsResult = parseOptionalTypeMatch(parser, dataRawType, resetValueOperand, resetValueType);
    if (odsResult) return ::mlir::failure();
    if (resetValueType)
      resetValueTypes.push_back(resetValueType);
  }
  {
    ::std::optional<::mlir::OpAsmParser::UnresolvedOperand> initialValueOperand = initialValueOperands.empty() ? ::std::optional<::mlir::OpAsmParser::UnresolvedOperand>() : initialValueOperands[0];
    ::mlir::Type initialValueType;
    auto odsResult = parseOptionalImmutableTypeMatch(parser, dataRawType, initialValueOperand, initialValueType);
    if (odsResult) return ::mlir::failure();
    if (initialValueType)
      initialValueTypes.push_back(initialValueType);
  }
::llvm::copy(::llvm::ArrayRef<int32_t>({1, 1, 1, static_cast<int32_t>(resetOperands.size()), static_cast<int32_t>(resetValueOperands.size()), static_cast<int32_t>(initialValueOperands.size())}), result.getOrAddProperties<CompRegClockEnabledOp::Properties>().operandSegmentSizes.begin());
  ::mlir::Type odsBuildableType0 = parser.getBuilder().getType<::circt::seq::ClockType>();
  ::mlir::Type odsBuildableType1 = parser.getBuilder().getIntegerType(1);
  result.addTypes(dataTypes);
  if (parser.resolveOperands(inputOperands, dataTypes[0], inputOperandsLoc, result.operands))
    return ::mlir::failure();
  if (parser.resolveOperands(clkOperands, odsBuildableType0, clkOperandsLoc, result.operands))
    return ::mlir::failure();
  if (parser.resolveOperands(clockEnableOperands, odsBuildableType1, clockEnableOperandsLoc, result.operands))
    return ::mlir::failure();
  if (!resetOperands.empty()) {
  if (parser.resolveOperands(resetOperands, odsBuildableType1, resetOperandsLoc, result.operands))
    return ::mlir::failure();
  }
  if (!resetValueOperands.empty()) {
  if (parser.resolveOperands(resetValueOperands, resetValueTypes, resetValueOperandsLoc, result.operands))
    return ::mlir::failure();
  }
  if (!initialValueOperands.empty()) {
  if (parser.resolveOperands(initialValueOperands, initialValueTypes, initialValueOperandsLoc, result.operands))
    return ::mlir::failure();
  }
  return ::mlir::success();
}

void CompRegClockEnabledOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  if (getInnerSymAttr()) {
    _odsPrinter << ' ' << "sym";
    _odsPrinter << ' ';
  _odsPrinter.printStrippedAttrOrType(getInnerSymAttr());
  }
  printImplicitSSAName(_odsPrinter, *this, getNameAttr());
  _odsPrinter << ' ';
  _odsPrinter << getInput();
  _odsPrinter << ",";
  _odsPrinter << ' ';
  _odsPrinter << getClk();
  _odsPrinter << ",";
  _odsPrinter << ' ';
  _odsPrinter << getClockEnable();
  if (getReset()) {
    _odsPrinter << ' ' << "reset";
    _odsPrinter << ' ';
    if (::mlir::Value value = getReset())
      _odsPrinter << value;
    _odsPrinter << ",";
    _odsPrinter << ' ';
    if (::mlir::Value value = getResetValue())
      _odsPrinter << value;
  }
  if (getInitialValue()) {
    _odsPrinter << ' ' << "initial";
    _odsPrinter << ' ';
    if (::mlir::Value value = getInitialValue())
      _odsPrinter << value;
  }
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("operandSegmentSizes");
  elidedAttrs.push_back("inner_sym");
  elidedAttrs.push_back("name");
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
  {
    auto type = getData().getType();
    if (auto validType = ::llvm::dyn_cast<::mlir::Type>(type))
      _odsPrinter.printStrippedAttrOrType(validType);
   else
     _odsPrinter << type;
  }
  _odsPrinter << ' ';
  printOptionalTypeMatch(_odsPrinter, *this, getData().getType(), getResetValue(), (getResetValue() ? getResetValue().getType() : ::mlir::Type()));
  _odsPrinter << ' ';
  printOptionalImmutableTypeMatch(_odsPrinter, *this, getData().getType(), getInitialValue(), (getInitialValue() ? getInitialValue().getType() : ::mlir::Type()));
}

void CompRegClockEnabledOp::getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects) {
}


} // namespace circt::seq
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::seq::CompRegClockEnabledOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::seq::detail::CompRegClockEnabledOpGenericAdaptorBase::Properties)

namespace circt::seq {


//===----------------------------------------------------------------------===//
// ::circt::seq::CompRegOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

CompRegOpGenericAdaptorBase::CompRegOpGenericAdaptorBase(CompRegOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

std::pair<unsigned, unsigned> CompRegOpGenericAdaptorBase::getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
  ::llvm::ArrayRef<int32_t> sizeAttr = getProperties().operandSegmentSizes;

  unsigned start = 0;
  for (unsigned i = 0; i < index; ++i)
    start += sizeAttr[i];
  return {start, sizeAttr[index]};
}

::std::optional< ::llvm::StringRef > CompRegOpGenericAdaptorBase::getName() {
  auto attr = getNameAttr();
  return attr ? ::std::optional< ::llvm::StringRef >(attr.getValue()) : (::std::nullopt);
}

::std::optional<::circt::hw::InnerSymAttr> CompRegOpGenericAdaptorBase::getInnerSym() {
  auto attr = getInnerSymAttr();
  return attr ? ::std::optional<::circt::hw::InnerSymAttr>(::llvm::cast<::circt::hw::InnerSymAttr>(attr)) : (::std::nullopt);
}


} // namespace detail
CompRegOpAdaptor::CompRegOpAdaptor(CompRegOp op) : CompRegOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult CompRegOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_inner_sym = getProperties().inner_sym; (void)tblgen_inner_sym;
  auto tblgen_name = getProperties().name; (void)tblgen_name;

  if (tblgen_name && !((::llvm::isa<::mlir::StringAttr>(tblgen_name))))
    return emitError(loc, "'seq.compreg' op attribute 'name' failed to satisfy constraint: string attribute");

  if (tblgen_inner_sym && !((::llvm::isa<::circt::hw::InnerSymAttr>(tblgen_inner_sym))))
    return emitError(loc, "'seq.compreg' op attribute 'inner_sym' failed to satisfy constraint: Inner symbol definition");
  return ::mlir::success();
}

std::pair<unsigned, unsigned> CompRegOp::getODSOperandIndexAndLength(unsigned index) {
  ::llvm::ArrayRef<int32_t> sizeAttr = getProperties().operandSegmentSizes;

  unsigned start = 0;
  for (unsigned i = 0; i < index; ++i)
    start += sizeAttr[i];
  return {start, sizeAttr[index]};
}

::mlir::MutableOperandRange CompRegOp::getResetMutable() {
  auto range = getODSOperandIndexAndLength(2);
  auto mutableRange = ::mlir::MutableOperandRange(getOperation(), range.first, range.second, ::mlir::MutableOperandRange::OperandSegment(2u, {getOperandSegmentSizesAttrName(), ::mlir::DenseI32ArrayAttr::get(getContext(), getProperties().operandSegmentSizes)}));
  return mutableRange;
}

::mlir::MutableOperandRange CompRegOp::getResetValueMutable() {
  auto range = getODSOperandIndexAndLength(3);
  auto mutableRange = ::mlir::MutableOperandRange(getOperation(), range.first, range.second, ::mlir::MutableOperandRange::OperandSegment(3u, {getOperandSegmentSizesAttrName(), ::mlir::DenseI32ArrayAttr::get(getContext(), getProperties().operandSegmentSizes)}));
  return mutableRange;
}

::mlir::MutableOperandRange CompRegOp::getInitialValueMutable() {
  auto range = getODSOperandIndexAndLength(4);
  auto mutableRange = ::mlir::MutableOperandRange(getOperation(), range.first, range.second, ::mlir::MutableOperandRange::OperandSegment(4u, {getOperandSegmentSizesAttrName(), ::mlir::DenseI32ArrayAttr::get(getContext(), getProperties().operandSegmentSizes)}));
  return mutableRange;
}

::llvm::LogicalResult CompRegOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
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

::mlir::Attribute CompRegOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
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

llvm::hash_code CompRegOp::computePropertiesHash(const Properties &prop) {
  auto hash_operandSegmentSizes_ = [] (const auto &propStorage) -> llvm::hash_code {
    using ::llvm::hash_value;
    return ::llvm::hash_combine_range(std::begin(propStorage), std::end(propStorage));;
  };
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.inner_sym.getAsOpaquePointer()), 
    llvm::hash_value(prop.name.getAsOpaquePointer()), 
    hash_operandSegmentSizes_(prop.operandSegmentSizes));
}

std::optional<mlir::Attribute> CompRegOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "inner_sym")
      return prop.inner_sym;

    if (name == "name")
      return prop.name;
    if (name == "operand_segment_sizes" || name == "operandSegmentSizes") return [&]() -> ::mlir::Attribute { return ::mlir::DenseI32ArrayAttr::get(ctx, prop.operandSegmentSizes); }();
  return std::nullopt;
}

void CompRegOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "inner_sym") {
       prop.inner_sym = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.inner_sym)>>(value);
       return;
    }

    if (name == "name") {
       prop.name = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.name)>>(value);
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

void CompRegOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.inner_sym) attrs.append("inner_sym", prop.inner_sym);

    if (prop.name) attrs.append("name", prop.name);
  attrs.append("operandSegmentSizes", [&]() -> ::mlir::Attribute { return ::mlir::DenseI32ArrayAttr::get(ctx, prop.operandSegmentSizes); }());
}

::llvm::LogicalResult CompRegOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getInnerSymAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Seq2(attr, "inner_sym", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getNameAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Seq3(attr, "name", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult CompRegOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readOptionalAttribute(prop.inner_sym)))
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

void CompRegOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;

  writer.writeOptionalAttribute(prop.inner_sym);

  writer.writeOptionalAttribute(prop.name);

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

::std::optional< ::llvm::StringRef > CompRegOp::getName() {
  auto attr = getNameAttr();
  return attr ? ::std::optional< ::llvm::StringRef >(attr.getValue()) : (::std::nullopt);
}

::std::optional<::circt::hw::InnerSymAttr> CompRegOp::getInnerSym() {
  auto attr = getInnerSymAttr();
  return attr ? ::std::optional<::circt::hw::InnerSymAttr>(::llvm::cast<::circt::hw::InnerSymAttr>(attr)) : (::std::nullopt);
}

void CompRegOp::setName(::std::optional<::llvm::StringRef> attrValue) {
    auto &odsProp = getProperties().name;
    if (attrValue)
      odsProp = ::mlir::Builder((*this)->getContext()).getStringAttr(*attrValue);
    else
      odsProp = nullptr;
}

void CompRegOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value input, Value clk) {
      return build(odsBuilder, odsState, input.getType(), input, clk,
                   /*name*/ StringAttr(),
                   /*reset*/ Value(), /*resetValue*/ Value(),
                    /*initialValue*/ Value(),
                   hw::InnerSymAttr());
    
}

CompRegOp CompRegOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, Value input, Value clk) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(input)>(input), std::forward<decltype(clk)>(clk));
  auto __res__ = ::llvm::dyn_cast<CompRegOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

CompRegOp CompRegOp::create(::mlir::ImplicitLocOpBuilder &builder, Value input, Value clk) {
  return create(builder, builder.getLoc(), std::forward<decltype(input)>(input), std::forward<decltype(clk)>(clk));
}

void CompRegOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value input, Value clk, StringAttrOrRef name) {
      auto nameAttr = name.get(odsBuilder.getContext());
      return build(odsBuilder, odsState, input.getType(), input, clk, nameAttr,
                   /*reset*/ Value(), /*resetValue*/ Value(),
                   /*initialValue*/ Value(),
                   hw::InnerSymAttr::get(nameAttr));
    
}

CompRegOp CompRegOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, Value input, Value clk, StringAttrOrRef name) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(input)>(input), std::forward<decltype(clk)>(clk), std::forward<decltype(name)>(name));
  auto __res__ = ::llvm::dyn_cast<CompRegOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

CompRegOp CompRegOp::create(::mlir::ImplicitLocOpBuilder &builder, Value input, Value clk, StringAttrOrRef name) {
  return create(builder, builder.getLoc(), std::forward<decltype(input)>(input), std::forward<decltype(clk)>(clk), std::forward<decltype(name)>(name));
}

void CompRegOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value input, Value clk, Value reset, Value rstValue, Value initialValue) {
      return build(odsBuilder, odsState, input.getType(), input, clk, StringAttr(),
                   reset, rstValue, initialValue, hw::InnerSymAttr());
    
}

CompRegOp CompRegOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, Value input, Value clk, Value reset, Value rstValue, Value initialValue) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(input)>(input), std::forward<decltype(clk)>(clk), std::forward<decltype(reset)>(reset), std::forward<decltype(rstValue)>(rstValue), std::forward<decltype(initialValue)>(initialValue));
  auto __res__ = ::llvm::dyn_cast<CompRegOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

CompRegOp CompRegOp::create(::mlir::ImplicitLocOpBuilder &builder, Value input, Value clk, Value reset, Value rstValue, Value initialValue) {
  return create(builder, builder.getLoc(), std::forward<decltype(input)>(input), std::forward<decltype(clk)>(clk), std::forward<decltype(reset)>(reset), std::forward<decltype(rstValue)>(rstValue), std::forward<decltype(initialValue)>(initialValue));
}

void CompRegOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value input, Value clk, Value reset, Value rstValue, StringAttrOrRef name, Value initialValue) {
      auto nameAttr = name.get(odsBuilder.getContext());
      return build(odsBuilder, odsState, input.getType(), input, clk, nameAttr,
                   reset, rstValue, initialValue, hw::InnerSymAttr::get(nameAttr));
    
}

CompRegOp CompRegOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, Value input, Value clk, Value reset, Value rstValue, StringAttrOrRef name, Value initialValue) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(input)>(input), std::forward<decltype(clk)>(clk), std::forward<decltype(reset)>(reset), std::forward<decltype(rstValue)>(rstValue), std::forward<decltype(name)>(name), std::forward<decltype(initialValue)>(initialValue));
  auto __res__ = ::llvm::dyn_cast<CompRegOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

CompRegOp CompRegOp::create(::mlir::ImplicitLocOpBuilder &builder, Value input, Value clk, Value reset, Value rstValue, StringAttrOrRef name, Value initialValue) {
  return create(builder, builder.getLoc(), std::forward<decltype(input)>(input), std::forward<decltype(clk)>(clk), std::forward<decltype(reset)>(reset), std::forward<decltype(rstValue)>(rstValue), std::forward<decltype(name)>(name), std::forward<decltype(initialValue)>(initialValue));
}

void CompRegOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type data, ::mlir::Value input, ::mlir::Value clk, /*optional*/::mlir::StringAttr name, /*optional*/::mlir::Value reset, /*optional*/::mlir::Value resetValue, /*optional*/::mlir::Value initialValue, /*optional*/::circt::hw::InnerSymAttr inner_sym) {
  odsState.addOperands(input);
  odsState.addOperands(clk);
  if (reset)
    odsState.addOperands(reset);
  if (resetValue)
    odsState.addOperands(resetValue);
  if (initialValue)
    odsState.addOperands(initialValue);
  ::llvm::copy(::llvm::ArrayRef<int32_t>({1, 1, (reset ? 1 : 0), (resetValue ? 1 : 0), (initialValue ? 1 : 0)}), odsState.getOrAddProperties<Properties>().operandSegmentSizes.begin());
  if (name) {
    odsState.getOrAddProperties<Properties>().name = name;
  }
  if (inner_sym) {
    odsState.getOrAddProperties<Properties>().inner_sym = inner_sym;
  }
  odsState.addTypes(data);
}

CompRegOp CompRegOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type data, ::mlir::Value input, ::mlir::Value clk, /*optional*/::mlir::StringAttr name, /*optional*/::mlir::Value reset, /*optional*/::mlir::Value resetValue, /*optional*/::mlir::Value initialValue, /*optional*/::circt::hw::InnerSymAttr inner_sym) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(data)>(data), std::forward<decltype(input)>(input), std::forward<decltype(clk)>(clk), std::forward<decltype(name)>(name), std::forward<decltype(reset)>(reset), std::forward<decltype(resetValue)>(resetValue), std::forward<decltype(initialValue)>(initialValue), std::forward<decltype(inner_sym)>(inner_sym));
  auto __res__ = ::llvm::dyn_cast<CompRegOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

CompRegOp CompRegOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type data, ::mlir::Value input, ::mlir::Value clk, /*optional*/::mlir::StringAttr name, /*optional*/::mlir::Value reset, /*optional*/::mlir::Value resetValue, /*optional*/::mlir::Value initialValue, /*optional*/::circt::hw::InnerSymAttr inner_sym) {
  return create(builder, builder.getLoc(), std::forward<decltype(data)>(data), std::forward<decltype(input)>(input), std::forward<decltype(clk)>(clk), std::forward<decltype(name)>(name), std::forward<decltype(reset)>(reset), std::forward<decltype(resetValue)>(resetValue), std::forward<decltype(initialValue)>(initialValue), std::forward<decltype(inner_sym)>(inner_sym));
}

void CompRegOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value input, ::mlir::Value clk, /*optional*/::mlir::StringAttr name, /*optional*/::mlir::Value reset, /*optional*/::mlir::Value resetValue, /*optional*/::mlir::Value initialValue, /*optional*/::circt::hw::InnerSymAttr inner_sym) {
  odsState.addOperands(input);
  odsState.addOperands(clk);
  if (reset)
    odsState.addOperands(reset);
  if (resetValue)
    odsState.addOperands(resetValue);
  if (initialValue)
    odsState.addOperands(initialValue);
  ::llvm::copy(::llvm::ArrayRef<int32_t>({1, 1, (reset ? 1 : 0), (resetValue ? 1 : 0), (initialValue ? 1 : 0)}), odsState.getOrAddProperties<Properties>().operandSegmentSizes.begin());
  if (name) {
    odsState.getOrAddProperties<Properties>().name = name;
  }
  if (inner_sym) {
    odsState.getOrAddProperties<Properties>().inner_sym = inner_sym;
  }

        ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
        if (::mlir::succeeded(CompRegOp::inferReturnTypes(odsBuilder.getContext(),
                      odsState.location, odsState.operands,
                      odsState.attributes.getDictionary(odsState.getContext()),
                      odsState.getRawProperties(),
                      odsState.regions, inferredReturnTypes)))
          odsState.addTypes(inferredReturnTypes);
        else
          ::mlir::detail::reportFatalInferReturnTypesError(odsState);
        
}

CompRegOp CompRegOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value input, ::mlir::Value clk, /*optional*/::mlir::StringAttr name, /*optional*/::mlir::Value reset, /*optional*/::mlir::Value resetValue, /*optional*/::mlir::Value initialValue, /*optional*/::circt::hw::InnerSymAttr inner_sym) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(input)>(input), std::forward<decltype(clk)>(clk), std::forward<decltype(name)>(name), std::forward<decltype(reset)>(reset), std::forward<decltype(resetValue)>(resetValue), std::forward<decltype(initialValue)>(initialValue), std::forward<decltype(inner_sym)>(inner_sym));
  auto __res__ = ::llvm::dyn_cast<CompRegOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

CompRegOp CompRegOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value input, ::mlir::Value clk, /*optional*/::mlir::StringAttr name, /*optional*/::mlir::Value reset, /*optional*/::mlir::Value resetValue, /*optional*/::mlir::Value initialValue, /*optional*/::circt::hw::InnerSymAttr inner_sym) {
  return create(builder, builder.getLoc(), std::forward<decltype(input)>(input), std::forward<decltype(clk)>(clk), std::forward<decltype(name)>(name), std::forward<decltype(reset)>(reset), std::forward<decltype(resetValue)>(resetValue), std::forward<decltype(initialValue)>(initialValue), std::forward<decltype(inner_sym)>(inner_sym));
}

void CompRegOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value input, ::mlir::Value clk, /*optional*/::mlir::StringAttr name, /*optional*/::mlir::Value reset, /*optional*/::mlir::Value resetValue, /*optional*/::mlir::Value initialValue, /*optional*/::circt::hw::InnerSymAttr inner_sym) {
  odsState.addOperands(input);
  odsState.addOperands(clk);
  if (reset)
    odsState.addOperands(reset);
  if (resetValue)
    odsState.addOperands(resetValue);
  if (initialValue)
    odsState.addOperands(initialValue);
  ::llvm::copy(::llvm::ArrayRef<int32_t>({1, 1, (reset ? 1 : 0), (resetValue ? 1 : 0), (initialValue ? 1 : 0)}), odsState.getOrAddProperties<Properties>().operandSegmentSizes.begin());
  if (name) {
    odsState.getOrAddProperties<Properties>().name = name;
  }
  if (inner_sym) {
    odsState.getOrAddProperties<Properties>().inner_sym = inner_sym;
  }
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

CompRegOp CompRegOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value input, ::mlir::Value clk, /*optional*/::mlir::StringAttr name, /*optional*/::mlir::Value reset, /*optional*/::mlir::Value resetValue, /*optional*/::mlir::Value initialValue, /*optional*/::circt::hw::InnerSymAttr inner_sym) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(input)>(input), std::forward<decltype(clk)>(clk), std::forward<decltype(name)>(name), std::forward<decltype(reset)>(reset), std::forward<decltype(resetValue)>(resetValue), std::forward<decltype(initialValue)>(initialValue), std::forward<decltype(inner_sym)>(inner_sym));
  auto __res__ = ::llvm::dyn_cast<CompRegOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

CompRegOp CompRegOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value input, ::mlir::Value clk, /*optional*/::mlir::StringAttr name, /*optional*/::mlir::Value reset, /*optional*/::mlir::Value resetValue, /*optional*/::mlir::Value initialValue, /*optional*/::circt::hw::InnerSymAttr inner_sym) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(input)>(input), std::forward<decltype(clk)>(clk), std::forward<decltype(name)>(name), std::forward<decltype(reset)>(reset), std::forward<decltype(resetValue)>(resetValue), std::forward<decltype(initialValue)>(initialValue), std::forward<decltype(inner_sym)>(inner_sym));
}

void CompRegOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() >= 2u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<CompRegOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

CompRegOp CompRegOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<CompRegOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

CompRegOp CompRegOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void CompRegOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() >= 2u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<CompRegOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
  ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
  if (::mlir::succeeded(CompRegOp::inferReturnTypes(odsBuilder.getContext(),
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

CompRegOp CompRegOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<CompRegOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

CompRegOp CompRegOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void CompRegOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() >= 2u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

CompRegOp CompRegOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<CompRegOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

CompRegOp CompRegOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

void CompRegOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() >= 2u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties &>(properties));
  odsState.addAttributes(discardableAttributes);

  ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
  if (::mlir::succeeded(CompRegOp::inferReturnTypes(odsBuilder.getContext(),
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

CompRegOp CompRegOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<CompRegOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

CompRegOp CompRegOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult CompRegOp::verifyInvariantsImpl() {
  auto tblgen_inner_sym = getProperties().inner_sym; (void)tblgen_inner_sym;
  auto tblgen_name = getProperties().name; (void)tblgen_name;

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Seq3(*this, tblgen_name, "name")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Seq2(*this, tblgen_inner_sym, "inner_sym")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Seq3(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSOperands(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Seq1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup2 = getODSOperands(2);

    if (valueGroup2.size() > 1) {
      return emitOpError("operand group starting at #") << index
          << " requires 0 or 1 element, but found " << valueGroup2.size();
    }

    for (auto v : valueGroup2) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Seq2(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup3 = getODSOperands(3);

    if (valueGroup3.size() > 1) {
      return emitOpError("operand group starting at #") << index
          << " requires 0 or 1 element, but found " << valueGroup3.size();
    }

    for (auto v : valueGroup3) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Seq3(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup4 = getODSOperands(4);

    if (valueGroup4.size() > 1) {
      return emitOpError("operand group starting at #") << index
          << " requires 0 or 1 element, but found " << valueGroup4.size();
    }

    for (auto v : valueGroup4) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Seq4(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Seq3(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  if (!((((*this->getODSOperands(0).begin()).getType()) == ((*this->getODSResults(0).begin()).getType()) && ((*this->getODSResults(0).begin()).getType()) == ((*this->getODSOperands(0).begin()).getType()))))
    return emitOpError("failed to verify that all of {input, data} have same type");
  return ::mlir::success();
}

::llvm::LogicalResult CompRegOp::verifyInvariants() {
  if(::mlir::succeeded(verifyInvariantsImpl()) && ::mlir::succeeded(verify()))
    return ::mlir::success();
  return ::mlir::failure();
}

::llvm::LogicalResult CompRegOp::inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::PropertyRef properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes) {
  inferredReturnTypes.resize(1);
  ::mlir::Builder odsBuilder(context);
  if (operands.size() <= 0)
    return ::mlir::failure();
  ::mlir::Type odsInferredType0 = operands[0].getType();
  inferredReturnTypes[0] = odsInferredType0;
  return ::mlir::success();
}

::mlir::ParseResult CompRegOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::circt::hw::InnerSymAttr inner_symAttr;
  ::mlir::StringAttr nameAttr;
  ::mlir::OpAsmParser::UnresolvedOperand inputRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> inputOperands(&inputRawOperand, 1);  ::llvm::SMLoc inputOperandsLoc;
  (void)inputOperandsLoc;
  ::mlir::OpAsmParser::UnresolvedOperand clkRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> clkOperands(&clkRawOperand, 1);  ::llvm::SMLoc clkOperandsLoc;
  (void)clkOperandsLoc;
  ::llvm::SmallVector<::mlir::OpAsmParser::UnresolvedOperand, 4> resetOperands;
  ::llvm::SMLoc resetOperandsLoc;
  (void)resetOperandsLoc;
  ::llvm::SmallVector<::mlir::OpAsmParser::UnresolvedOperand, 4> resetValueOperands;
  ::llvm::SMLoc resetValueOperandsLoc;
  (void)resetValueOperandsLoc;
  ::llvm::SmallVector<::mlir::OpAsmParser::UnresolvedOperand, 4> initialValueOperands;
  ::llvm::SMLoc initialValueOperandsLoc;
  (void)initialValueOperandsLoc;
  ::mlir::Type dataRawType{};
  ::llvm::ArrayRef<::mlir::Type> dataTypes(&dataRawType, 1);
  ::llvm::SmallVector<::mlir::Type, 1> resetValueTypes;
  ::llvm::SmallVector<::mlir::Type, 1> initialValueTypes;
  if (::mlir::succeeded(parser.parseOptionalKeyword("sym"))) {

  if (parser.parseCustomAttributeWithFallback(inner_symAttr, ::mlir::Type{})) {
    return ::mlir::failure();
  }
  if (inner_symAttr) result.getOrAddProperties<CompRegOp::Properties>().inner_sym = inner_symAttr;
  }
  {
    auto odsResult = parseImplicitSSAName(parser, nameAttr);
    if (odsResult) return ::mlir::failure();
    if (nameAttr)
      result.getOrAddProperties<CompRegOp::Properties>().name = nameAttr;
  }

  inputOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(inputRawOperand))
    return ::mlir::failure();
  if (parser.parseComma())
    return ::mlir::failure();

  clkOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(clkRawOperand))
    return ::mlir::failure();
  if (::mlir::succeeded(parser.parseOptionalKeyword("reset"))) {

  {
    resetOperandsLoc = parser.getCurrentLocation();
    ::mlir::OpAsmParser::UnresolvedOperand operand;
    ::mlir::OptionalParseResult parseResult =
                                    parser.parseOptionalOperand(operand);
    if (parseResult.has_value()) {
      if (failed(*parseResult))
        return ::mlir::failure();
      resetOperands.push_back(operand);
    }
  }
  if (parser.parseComma())
    return ::mlir::failure();

  {
    resetValueOperandsLoc = parser.getCurrentLocation();
    ::mlir::OpAsmParser::UnresolvedOperand operand;
    ::mlir::OptionalParseResult parseResult =
                                    parser.parseOptionalOperand(operand);
    if (parseResult.has_value()) {
      if (failed(*parseResult))
        return ::mlir::failure();
      resetValueOperands.push_back(operand);
    }
  }
  }
  if (::mlir::succeeded(parser.parseOptionalKeyword("initial"))) {

  {
    initialValueOperandsLoc = parser.getCurrentLocation();
    ::mlir::OpAsmParser::UnresolvedOperand operand;
    ::mlir::OptionalParseResult parseResult =
                                    parser.parseOptionalOperand(operand);
    if (parseResult.has_value()) {
      if (failed(*parseResult))
        return ::mlir::failure();
      initialValueOperands.push_back(operand);
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
    dataRawType = type;
  }
  {
    ::std::optional<::mlir::OpAsmParser::UnresolvedOperand> resetValueOperand = resetValueOperands.empty() ? ::std::optional<::mlir::OpAsmParser::UnresolvedOperand>() : resetValueOperands[0];
    ::mlir::Type resetValueType;
    auto odsResult = parseOptionalTypeMatch(parser, dataRawType, resetValueOperand, resetValueType);
    if (odsResult) return ::mlir::failure();
    if (resetValueType)
      resetValueTypes.push_back(resetValueType);
  }
  {
    ::std::optional<::mlir::OpAsmParser::UnresolvedOperand> initialValueOperand = initialValueOperands.empty() ? ::std::optional<::mlir::OpAsmParser::UnresolvedOperand>() : initialValueOperands[0];
    ::mlir::Type initialValueType;
    auto odsResult = parseOptionalImmutableTypeMatch(parser, dataRawType, initialValueOperand, initialValueType);
    if (odsResult) return ::mlir::failure();
    if (initialValueType)
      initialValueTypes.push_back(initialValueType);
  }
::llvm::copy(::llvm::ArrayRef<int32_t>({1, 1, static_cast<int32_t>(resetOperands.size()), static_cast<int32_t>(resetValueOperands.size()), static_cast<int32_t>(initialValueOperands.size())}), result.getOrAddProperties<CompRegOp::Properties>().operandSegmentSizes.begin());
  ::mlir::Type odsBuildableType0 = parser.getBuilder().getType<::circt::seq::ClockType>();
  ::mlir::Type odsBuildableType1 = parser.getBuilder().getIntegerType(1);
  result.addTypes(dataTypes);
  if (parser.resolveOperands(inputOperands, dataTypes[0], inputOperandsLoc, result.operands))
    return ::mlir::failure();
  if (parser.resolveOperands(clkOperands, odsBuildableType0, clkOperandsLoc, result.operands))
    return ::mlir::failure();
  if (!resetOperands.empty()) {
  if (parser.resolveOperands(resetOperands, odsBuildableType1, resetOperandsLoc, result.operands))
    return ::mlir::failure();
  }
  if (!resetValueOperands.empty()) {
  if (parser.resolveOperands(resetValueOperands, resetValueTypes, resetValueOperandsLoc, result.operands))
    return ::mlir::failure();
  }
  if (!initialValueOperands.empty()) {
  if (parser.resolveOperands(initialValueOperands, initialValueTypes, initialValueOperandsLoc, result.operands))
    return ::mlir::failure();
  }
  return ::mlir::success();
}

void CompRegOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  if (getInnerSymAttr()) {
    _odsPrinter << ' ' << "sym";
    _odsPrinter << ' ';
  _odsPrinter.printStrippedAttrOrType(getInnerSymAttr());
  }
  printImplicitSSAName(_odsPrinter, *this, getNameAttr());
  _odsPrinter << ' ';
  _odsPrinter << getInput();
  _odsPrinter << ",";
  _odsPrinter << ' ';
  _odsPrinter << getClk();
  if (getReset()) {
    _odsPrinter << ' ' << "reset";
    _odsPrinter << ' ';
    if (::mlir::Value value = getReset())
      _odsPrinter << value;
    _odsPrinter << ",";
    _odsPrinter << ' ';
    if (::mlir::Value value = getResetValue())
      _odsPrinter << value;
  }
  if (getInitialValue()) {
    _odsPrinter << ' ' << "initial";
    _odsPrinter << ' ';
    if (::mlir::Value value = getInitialValue())
      _odsPrinter << value;
  }
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("operandSegmentSizes");
  elidedAttrs.push_back("inner_sym");
  elidedAttrs.push_back("name");
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
  {
    auto type = getData().getType();
    if (auto validType = ::llvm::dyn_cast<::mlir::Type>(type))
      _odsPrinter.printStrippedAttrOrType(validType);
   else
     _odsPrinter << type;
  }
  _odsPrinter << ' ';
  printOptionalTypeMatch(_odsPrinter, *this, getData().getType(), getResetValue(), (getResetValue() ? getResetValue().getType() : ::mlir::Type()));
  _odsPrinter << ' ';
  printOptionalImmutableTypeMatch(_odsPrinter, *this, getData().getType(), getInitialValue(), (getInitialValue() ? getInitialValue().getType() : ::mlir::Type()));
}

void CompRegOp::getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects) {
}


} // namespace circt::seq
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::seq::CompRegOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::seq::detail::CompRegOpGenericAdaptorBase::Properties)

namespace circt::seq {


//===----------------------------------------------------------------------===//
// ::circt::seq::ConstClockOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

ConstClockOpGenericAdaptorBase::ConstClockOpGenericAdaptorBase(ConstClockOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

circt::seq::ClockConst ConstClockOpGenericAdaptorBase::getValue() {
  auto attr = getValueAttr();
  return attr.getValue();
}


} // namespace detail
ConstClockOpAdaptor::ConstClockOpAdaptor(ConstClockOp op) : ConstClockOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult ConstClockOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_value = getProperties().value; (void)tblgen_value;
  if (!tblgen_value) return emitError(loc, "'seq.const_clock' op requires attribute 'value'");

  if (tblgen_value && !((::llvm::isa<::circt::seq::ClockConstAttr>(tblgen_value))))
    return emitError(loc, "'seq.const_clock' op attribute 'value' failed to satisfy constraint: clock constant");
  return ::mlir::success();
}

::llvm::LogicalResult ConstClockOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.value;
       auto attr = dict.get("value");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `value` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  return ::mlir::success();
}

::mlir::Attribute ConstClockOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.value;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("value",
                                       propStorage));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code ConstClockOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.value.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> ConstClockOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "value")
      return prop.value;
  return std::nullopt;
}

void ConstClockOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "value") {
       prop.value = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.value)>>(value);
       return;
    }
}

void ConstClockOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.value) attrs.append("value", prop.value);
}

::llvm::LogicalResult ConstClockOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getValueAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Seq4(attr, "value", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult ConstClockOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.value)))
    return ::mlir::failure();
  return ::mlir::success();
}

void ConstClockOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.value);
}

circt::seq::ClockConst ConstClockOp::getValue() {
  auto attr = getValueAttr();
  return attr.getValue();
}

void ConstClockOp::setValue(circt::seq::ClockConst attrValue) {
  getProperties().value = circt::seq::ClockConstAttr::get(::mlir::Builder((*this)->getContext()).getContext(), attrValue);
}

void ConstClockOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::circt::seq::ClockConstAttr value) {
  odsState.getOrAddProperties<Properties>().value = value;
  odsState.addTypes(result);
}

ConstClockOp ConstClockOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::circt::seq::ClockConstAttr value) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(result)>(result), std::forward<decltype(value)>(value));
  auto __res__ = ::llvm::dyn_cast<ConstClockOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ConstClockOp ConstClockOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::circt::seq::ClockConstAttr value) {
  return create(builder, builder.getLoc(), std::forward<decltype(result)>(result), std::forward<decltype(value)>(value));
}

void ConstClockOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::circt::seq::ClockConstAttr value) {
  odsState.getOrAddProperties<Properties>().value = value;

        ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
        if (::mlir::succeeded(ConstClockOp::inferReturnTypes(odsBuilder.getContext(),
                      odsState.location, odsState.operands,
                      odsState.attributes.getDictionary(odsState.getContext()),
                      odsState.getRawProperties(),
                      odsState.regions, inferredReturnTypes)))
          odsState.addTypes(inferredReturnTypes);
        else
          ::mlir::detail::reportFatalInferReturnTypesError(odsState);
        
}

ConstClockOp ConstClockOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::circt::seq::ClockConstAttr value) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(value)>(value));
  auto __res__ = ::llvm::dyn_cast<ConstClockOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ConstClockOp ConstClockOp::create(::mlir::ImplicitLocOpBuilder &builder, ::circt::seq::ClockConstAttr value) {
  return create(builder, builder.getLoc(), std::forward<decltype(value)>(value));
}

void ConstClockOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::circt::seq::ClockConstAttr value) {
  odsState.getOrAddProperties<Properties>().value = value;
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

ConstClockOp ConstClockOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::circt::seq::ClockConstAttr value) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(value)>(value));
  auto __res__ = ::llvm::dyn_cast<ConstClockOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ConstClockOp ConstClockOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::circt::seq::ClockConstAttr value) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(value)>(value));
}

void ConstClockOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, circt::seq::ClockConst value) {
  odsState.getOrAddProperties<Properties>().value = circt::seq::ClockConstAttr::get(odsBuilder.getContext(), value);
  odsState.addTypes(result);
}

ConstClockOp ConstClockOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, circt::seq::ClockConst value) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(result)>(result), std::forward<decltype(value)>(value));
  auto __res__ = ::llvm::dyn_cast<ConstClockOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ConstClockOp ConstClockOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, circt::seq::ClockConst value) {
  return create(builder, builder.getLoc(), std::forward<decltype(result)>(result), std::forward<decltype(value)>(value));
}

void ConstClockOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, circt::seq::ClockConst value) {
  odsState.getOrAddProperties<Properties>().value = circt::seq::ClockConstAttr::get(odsBuilder.getContext(), value);

        ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
        if (::mlir::succeeded(ConstClockOp::inferReturnTypes(odsBuilder.getContext(),
                      odsState.location, odsState.operands,
                      odsState.attributes.getDictionary(odsState.getContext()),
                      odsState.getRawProperties(),
                      odsState.regions, inferredReturnTypes)))
          odsState.addTypes(inferredReturnTypes);
        else
          ::mlir::detail::reportFatalInferReturnTypesError(odsState);
        
}

ConstClockOp ConstClockOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, circt::seq::ClockConst value) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(value)>(value));
  auto __res__ = ::llvm::dyn_cast<ConstClockOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ConstClockOp ConstClockOp::create(::mlir::ImplicitLocOpBuilder &builder, circt::seq::ClockConst value) {
  return create(builder, builder.getLoc(), std::forward<decltype(value)>(value));
}

void ConstClockOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, circt::seq::ClockConst value) {
  odsState.getOrAddProperties<Properties>().value = circt::seq::ClockConstAttr::get(odsBuilder.getContext(), value);
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

ConstClockOp ConstClockOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, circt::seq::ClockConst value) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(value)>(value));
  auto __res__ = ::llvm::dyn_cast<ConstClockOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ConstClockOp ConstClockOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, circt::seq::ClockConst value) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(value)>(value));
}

void ConstClockOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<ConstClockOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

ConstClockOp ConstClockOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<ConstClockOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ConstClockOp ConstClockOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void ConstClockOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<ConstClockOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
  ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
  if (::mlir::succeeded(ConstClockOp::inferReturnTypes(odsBuilder.getContext(),
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

ConstClockOp ConstClockOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<ConstClockOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ConstClockOp ConstClockOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void ConstClockOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

ConstClockOp ConstClockOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<ConstClockOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ConstClockOp ConstClockOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

void ConstClockOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties &>(properties));
  odsState.addAttributes(discardableAttributes);

  ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
  if (::mlir::succeeded(ConstClockOp::inferReturnTypes(odsBuilder.getContext(),
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

ConstClockOp ConstClockOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<ConstClockOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ConstClockOp ConstClockOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult ConstClockOp::verifyInvariantsImpl() {
  auto tblgen_value = getProperties().value; (void)tblgen_value;
  if (!tblgen_value) return emitOpError("requires attribute 'value'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Seq4(*this, tblgen_value, "value")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Seq1(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult ConstClockOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::llvm::LogicalResult ConstClockOp::inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::PropertyRef properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes) {
  inferredReturnTypes.resize(1);
  ::mlir::Builder odsBuilder(context);
  ::mlir::Type odsInferredType0 = odsBuilder.getType<::circt::seq::ClockType>();
  inferredReturnTypes[0] = odsInferredType0;
  return ::mlir::success();
}

::mlir::ParseResult ConstClockOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::circt::seq::ClockConstAttr valueAttr;

  if (parser.parseCustomAttributeWithFallback(valueAttr, ::mlir::Type{})) {
    return ::mlir::failure();
  }
  if (valueAttr) result.getOrAddProperties<ConstClockOp::Properties>().value = valueAttr;
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
  result.addTypes(odsBuildableType0);
  return ::mlir::success();
}

void ConstClockOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
_odsPrinter.printStrippedAttrOrType(getValueAttr());
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("value");
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
}

void ConstClockOp::getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects) {
}


} // namespace circt::seq
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::seq::ConstClockOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::seq::detail::ConstClockOpGenericAdaptorBase::Properties)

namespace circt::seq {


//===----------------------------------------------------------------------===//
// ::circt::seq::FIFOOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

FIFOOpGenericAdaptorBase::FIFOOpGenericAdaptorBase(FIFOOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

uint64_t FIFOOpGenericAdaptorBase::getDepth() {
  auto attr = getDepthAttr();
  return attr.getValue().getZExtValue();
}

::mlir::IntegerAttr FIFOOpGenericAdaptorBase::getRdLatencyAttr() {
  auto attr = ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(getProperties().rdLatency);
  if (!attr)
    attr = ::mlir::Builder(odsAttrs.getContext()).getIntegerAttr(::mlir::Builder(odsAttrs.getContext()).getIntegerType(64), 0);
  return attr;
}

uint64_t FIFOOpGenericAdaptorBase::getRdLatency() {
  auto attr = getRdLatencyAttr();
    if (!attr)
      return ::mlir::Builder(odsAttrs.getContext()).getIntegerAttr(::mlir::Builder(odsAttrs.getContext()).getIntegerType(64), 0).getValue().getZExtValue();
  return attr.getValue().getZExtValue();
}

::std::optional<uint64_t> FIFOOpGenericAdaptorBase::getAlmostFullThreshold() {
  auto attr = getAlmostFullThresholdAttr();
  return attr ? ::std::optional<uint64_t>(attr.getValue().getZExtValue()) : (::std::nullopt);
}

::std::optional<uint64_t> FIFOOpGenericAdaptorBase::getAlmostEmptyThreshold() {
  auto attr = getAlmostEmptyThresholdAttr();
  return attr ? ::std::optional<uint64_t>(attr.getValue().getZExtValue()) : (::std::nullopt);
}


} // namespace detail
FIFOOpAdaptor::FIFOOpAdaptor(FIFOOp op) : FIFOOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult FIFOOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_almostEmptyThreshold = getProperties().almostEmptyThreshold; (void)tblgen_almostEmptyThreshold;
  auto tblgen_almostFullThreshold = getProperties().almostFullThreshold; (void)tblgen_almostFullThreshold;
  auto tblgen_depth = getProperties().depth; (void)tblgen_depth;
  if (!tblgen_depth) return emitError(loc, "'seq.fifo' op requires attribute 'depth'");
  auto tblgen_rdLatency = getProperties().rdLatency; (void)tblgen_rdLatency;

  if (tblgen_depth && !((((::llvm::isa<::mlir::IntegerAttr>(tblgen_depth))) && ((::llvm::cast<::mlir::IntegerAttr>(tblgen_depth).getType().isSignlessInteger(64)))) && ((::llvm::cast<::mlir::IntegerAttr>(tblgen_depth).getInt() >= 1))))
    return emitError(loc, "'seq.fifo' op attribute 'depth' failed to satisfy constraint: 64-bit signless integer attribute whose minimum value is 1");

  if (tblgen_rdLatency && !((((::llvm::isa<::mlir::IntegerAttr>(tblgen_rdLatency))) && ((::llvm::cast<::mlir::IntegerAttr>(tblgen_rdLatency).getType().isSignlessInteger(64)))) && ((::llvm::cast<::mlir::IntegerAttr>(tblgen_rdLatency).getInt() >= 0))))
    return emitError(loc, "'seq.fifo' op attribute 'rdLatency' failed to satisfy constraint: 64-bit signless integer attribute whose minimum value is 0");

  if (tblgen_almostFullThreshold && !((((::llvm::isa<::mlir::IntegerAttr>(tblgen_almostFullThreshold))) && ((::llvm::cast<::mlir::IntegerAttr>(tblgen_almostFullThreshold).getType().isSignlessInteger(64)))) && ((::llvm::cast<::mlir::IntegerAttr>(tblgen_almostFullThreshold).getInt() >= 0))))
    return emitError(loc, "'seq.fifo' op attribute 'almostFullThreshold' failed to satisfy constraint: 64-bit signless integer attribute whose minimum value is 0");

  if (tblgen_almostEmptyThreshold && !((((::llvm::isa<::mlir::IntegerAttr>(tblgen_almostEmptyThreshold))) && ((::llvm::cast<::mlir::IntegerAttr>(tblgen_almostEmptyThreshold).getType().isSignlessInteger(64)))) && ((::llvm::cast<::mlir::IntegerAttr>(tblgen_almostEmptyThreshold).getInt() >= 0))))
    return emitError(loc, "'seq.fifo' op attribute 'almostEmptyThreshold' failed to satisfy constraint: 64-bit signless integer attribute whose minimum value is 0");
  return ::mlir::success();
}

std::pair<unsigned, unsigned> FIFOOp::getODSResultIndexAndLength(unsigned index) {
  ::llvm::ArrayRef<int32_t> sizeAttr = getProperties().resultSegmentSizes;

  unsigned start = 0;
  for (unsigned i = 0; i < index; ++i)
    start += sizeAttr[i];
  return {start, sizeAttr[index]};
}

::llvm::LogicalResult FIFOOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.almostEmptyThreshold;
       auto attr = dict.get("almostEmptyThreshold");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `almostEmptyThreshold` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.almostFullThreshold;
       auto attr = dict.get("almostFullThreshold");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `almostFullThreshold` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.depth;
       auto attr = dict.get("depth");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `depth` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.rdLatency;
       auto attr = dict.get("rdLatency");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `rdLatency` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
{

      auto setFromAttr = [] (auto &propStorage, ::mlir::Attribute propAttr,
               ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) -> ::mlir::LogicalResult {
        return convertFromAttribute(propStorage, propAttr, emitError);
      };
         auto attr = dict.get("resultSegmentSizes");   if (!attr) attr = dict.get("result_segment_sizes");;
;
      if (attr && ::mlir::failed(setFromAttr(prop.resultSegmentSizes, attr, [&]() {
            return emitError() << "for `resultSegmentSizes`: ";
          })))
        return ::mlir::failure();
  }
  return ::mlir::success();
}

::mlir::Attribute FIFOOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.almostEmptyThreshold;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("almostEmptyThreshold",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.almostFullThreshold;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("almostFullThreshold",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.depth;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("depth",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.rdLatency;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("rdLatency",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.resultSegmentSizes;
      auto attr = [&]() -> ::mlir::Attribute {
        return ::mlir::DenseI32ArrayAttr::get(ctx, propStorage);
      }();
      attrs.push_back(odsBuilder.getNamedAttr("resultSegmentSizes", attr));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code FIFOOp::computePropertiesHash(const Properties &prop) {
  auto hash_resultSegmentSizes_ = [] (const auto &propStorage) -> llvm::hash_code {
    using ::llvm::hash_value;
    return ::llvm::hash_combine_range(std::begin(propStorage), std::end(propStorage));;
  };
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.almostEmptyThreshold.getAsOpaquePointer()), 
    llvm::hash_value(prop.almostFullThreshold.getAsOpaquePointer()), 
    llvm::hash_value(prop.depth.getAsOpaquePointer()), 
    llvm::hash_value(prop.rdLatency.getAsOpaquePointer()), 
    hash_resultSegmentSizes_(prop.resultSegmentSizes));
}

std::optional<mlir::Attribute> FIFOOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "almostEmptyThreshold")
      return prop.almostEmptyThreshold;

    if (name == "almostFullThreshold")
      return prop.almostFullThreshold;

    if (name == "depth")
      return prop.depth;

    if (name == "rdLatency")
      return prop.rdLatency;
    if (name == "result_segment_sizes" || name == "resultSegmentSizes") return [&]() -> ::mlir::Attribute { return ::mlir::DenseI32ArrayAttr::get(ctx, prop.resultSegmentSizes); }();
  return std::nullopt;
}

void FIFOOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "almostEmptyThreshold") {
       prop.almostEmptyThreshold = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.almostEmptyThreshold)>>(value);
       return;
    }

    if (name == "almostFullThreshold") {
       prop.almostFullThreshold = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.almostFullThreshold)>>(value);
       return;
    }

    if (name == "depth") {
       prop.depth = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.depth)>>(value);
       return;
    }

    if (name == "rdLatency") {
       prop.rdLatency = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.rdLatency)>>(value);
       return;
    }
        if (name == "result_segment_sizes" || name == "resultSegmentSizes") {
       auto arrAttr = ::llvm::dyn_cast_or_null<::mlir::DenseI32ArrayAttr>(value);
       if (!arrAttr) return;
       if (arrAttr.size() != sizeof(prop.resultSegmentSizes) / sizeof(int32_t))
         return;
       llvm::copy(arrAttr.asArrayRef(), prop.resultSegmentSizes.begin());
       return;
    }
}

void FIFOOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.almostEmptyThreshold) attrs.append("almostEmptyThreshold", prop.almostEmptyThreshold);

    if (prop.almostFullThreshold) attrs.append("almostFullThreshold", prop.almostFullThreshold);

    if (prop.depth) attrs.append("depth", prop.depth);

    if (prop.rdLatency) attrs.append("rdLatency", prop.rdLatency);
  attrs.append("resultSegmentSizes", [&]() -> ::mlir::Attribute { return ::mlir::DenseI32ArrayAttr::get(ctx, prop.resultSegmentSizes); }());
}

::llvm::LogicalResult FIFOOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getAlmostEmptyThresholdAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Seq6(attr, "almostEmptyThreshold", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getAlmostFullThresholdAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Seq6(attr, "almostFullThreshold", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getDepthAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Seq5(attr, "depth", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getRdLatencyAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Seq6(attr, "rdLatency", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult FIFOOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readOptionalAttribute(prop.almostEmptyThreshold)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readOptionalAttribute(prop.almostFullThreshold)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readAttribute(prop.depth)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readOptionalAttribute(prop.rdLatency)))
    return ::mlir::failure();

  if (reader.getBytecodeVersion() < /*kNativePropertiesODSSegmentSize=*/6) {
    auto &propStorage = prop.resultSegmentSizes;
    ::mlir::DenseI32ArrayAttr attr;
    if (::mlir::failed(reader.readAttribute(attr))) return ::mlir::failure();
    if (attr.size() > static_cast<int64_t>(sizeof(propStorage) / sizeof(int32_t))) {
      reader.emitError("size mismatch for operand/result_segment_size");
      return ::mlir::failure();
    }
    ::llvm::copy(::llvm::ArrayRef<int32_t>(attr), propStorage.begin());
  }

  {
    auto &propStorage = prop.resultSegmentSizes;
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

void FIFOOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;

  writer.writeOptionalAttribute(prop.almostEmptyThreshold);

  writer.writeOptionalAttribute(prop.almostFullThreshold);
  writer.writeAttribute(prop.depth);

  writer.writeOptionalAttribute(prop.rdLatency);

if (writer.getBytecodeVersion() < /*kNativePropertiesODSSegmentSize=*/6) {
  auto &propStorage = prop.resultSegmentSizes;
  writer.writeAttribute(::mlir::DenseI32ArrayAttr::get(this->getContext(), propStorage));
}

  {
    auto &propStorage = prop.resultSegmentSizes;

  if (writer.getBytecodeVersion() >= /*kNativePropertiesODSSegmentSize=*/6)
    writer.writeSparseArray(::llvm::ArrayRef(propStorage));
;
  }
}

uint64_t FIFOOp::getDepth() {
  auto attr = getDepthAttr();
  return attr.getValue().getZExtValue();
}

uint64_t FIFOOp::getRdLatency() {
  auto attr = getRdLatencyAttr();
    if (!attr)
      return ::mlir::Builder((*this)->getContext()).getIntegerAttr(::mlir::Builder((*this)->getContext()).getIntegerType(64), 0).getValue().getZExtValue();
  return attr.getValue().getZExtValue();
}

::std::optional<uint64_t> FIFOOp::getAlmostFullThreshold() {
  auto attr = getAlmostFullThresholdAttr();
  return attr ? ::std::optional<uint64_t>(attr.getValue().getZExtValue()) : (::std::nullopt);
}

::std::optional<uint64_t> FIFOOp::getAlmostEmptyThreshold() {
  auto attr = getAlmostEmptyThresholdAttr();
  return attr ? ::std::optional<uint64_t>(attr.getValue().getZExtValue()) : (::std::nullopt);
}

void FIFOOp::setDepth(uint64_t attrValue) {
  getProperties().depth = ::mlir::Builder((*this)->getContext()).getIntegerAttr(::mlir::Builder((*this)->getContext()).getIntegerType(64), attrValue);
}

void FIFOOp::setRdLatency(::std::optional<uint64_t> attrValue) {
    auto &odsProp = getProperties().rdLatency;
    if (attrValue)
      odsProp = ::mlir::Builder((*this)->getContext()).getIntegerAttr(::mlir::Builder((*this)->getContext()).getIntegerType(64), *attrValue);
    else
      odsProp = nullptr;
}

void FIFOOp::setAlmostFullThreshold(::std::optional<uint64_t> attrValue) {
    auto &odsProp = getProperties().almostFullThreshold;
    if (attrValue)
      odsProp = ::mlir::Builder((*this)->getContext()).getIntegerAttr(::mlir::Builder((*this)->getContext()).getIntegerType(64), *attrValue);
    else
      odsProp = nullptr;
}

void FIFOOp::setAlmostEmptyThreshold(::std::optional<uint64_t> attrValue) {
    auto &odsProp = getProperties().almostEmptyThreshold;
    if (attrValue)
      odsProp = ::mlir::Builder((*this)->getContext()).getIntegerAttr(::mlir::Builder((*this)->getContext()).getIntegerType(64), *attrValue);
    else
      odsProp = nullptr;
}

void FIFOOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type output, ::mlir::Type full, ::mlir::Type empty, /*optional*/::mlir::Type almostFull, /*optional*/::mlir::Type almostEmpty, ::mlir::Value input, ::mlir::Value rdEn, ::mlir::Value wrEn, ::mlir::Value clk, ::mlir::Value rst, ::mlir::IntegerAttr depth, /*optional*/::mlir::IntegerAttr rdLatency, /*optional*/::mlir::IntegerAttr almostFullThreshold, /*optional*/::mlir::IntegerAttr almostEmptyThreshold) {
  odsState.addOperands(input);
  odsState.addOperands(rdEn);
  odsState.addOperands(wrEn);
  odsState.addOperands(clk);
  odsState.addOperands(rst);
  odsState.getOrAddProperties<Properties>().depth = depth;
  if (rdLatency) {
    odsState.getOrAddProperties<Properties>().rdLatency = rdLatency;
  }
  if (almostFullThreshold) {
    odsState.getOrAddProperties<Properties>().almostFullThreshold = almostFullThreshold;
  }
  if (almostEmptyThreshold) {
    odsState.getOrAddProperties<Properties>().almostEmptyThreshold = almostEmptyThreshold;
  }
  odsState.addTypes(output);
  odsState.addTypes(full);
  odsState.addTypes(empty);
  if (almostFull)
    odsState.addTypes(almostFull);
  if (almostEmpty)
    odsState.addTypes(almostEmpty);
  ::llvm::copy(::llvm::ArrayRef<int32_t>({1, 1, 1, (almostFull ? 1 : 0), (almostEmpty ? 1 : 0)}), odsState.getOrAddProperties<Properties>().resultSegmentSizes.begin());
}

FIFOOp FIFOOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type output, ::mlir::Type full, ::mlir::Type empty, /*optional*/::mlir::Type almostFull, /*optional*/::mlir::Type almostEmpty, ::mlir::Value input, ::mlir::Value rdEn, ::mlir::Value wrEn, ::mlir::Value clk, ::mlir::Value rst, ::mlir::IntegerAttr depth, /*optional*/::mlir::IntegerAttr rdLatency, /*optional*/::mlir::IntegerAttr almostFullThreshold, /*optional*/::mlir::IntegerAttr almostEmptyThreshold) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(output)>(output), std::forward<decltype(full)>(full), std::forward<decltype(empty)>(empty), std::forward<decltype(almostFull)>(almostFull), std::forward<decltype(almostEmpty)>(almostEmpty), std::forward<decltype(input)>(input), std::forward<decltype(rdEn)>(rdEn), std::forward<decltype(wrEn)>(wrEn), std::forward<decltype(clk)>(clk), std::forward<decltype(rst)>(rst), std::forward<decltype(depth)>(depth), std::forward<decltype(rdLatency)>(rdLatency), std::forward<decltype(almostFullThreshold)>(almostFullThreshold), std::forward<decltype(almostEmptyThreshold)>(almostEmptyThreshold));
  auto __res__ = ::llvm::dyn_cast<FIFOOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

FIFOOp FIFOOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type output, ::mlir::Type full, ::mlir::Type empty, /*optional*/::mlir::Type almostFull, /*optional*/::mlir::Type almostEmpty, ::mlir::Value input, ::mlir::Value rdEn, ::mlir::Value wrEn, ::mlir::Value clk, ::mlir::Value rst, ::mlir::IntegerAttr depth, /*optional*/::mlir::IntegerAttr rdLatency, /*optional*/::mlir::IntegerAttr almostFullThreshold, /*optional*/::mlir::IntegerAttr almostEmptyThreshold) {
  return create(builder, builder.getLoc(), std::forward<decltype(output)>(output), std::forward<decltype(full)>(full), std::forward<decltype(empty)>(empty), std::forward<decltype(almostFull)>(almostFull), std::forward<decltype(almostEmpty)>(almostEmpty), std::forward<decltype(input)>(input), std::forward<decltype(rdEn)>(rdEn), std::forward<decltype(wrEn)>(wrEn), std::forward<decltype(clk)>(clk), std::forward<decltype(rst)>(rst), std::forward<decltype(depth)>(depth), std::forward<decltype(rdLatency)>(rdLatency), std::forward<decltype(almostFullThreshold)>(almostFullThreshold), std::forward<decltype(almostEmptyThreshold)>(almostEmptyThreshold));
}

void FIFOOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value input, ::mlir::Value rdEn, ::mlir::Value wrEn, ::mlir::Value clk, ::mlir::Value rst, ::mlir::IntegerAttr depth, /*optional*/::mlir::IntegerAttr rdLatency, /*optional*/::mlir::IntegerAttr almostFullThreshold, /*optional*/::mlir::IntegerAttr almostEmptyThreshold) {
  odsState.addOperands(input);
  odsState.addOperands(rdEn);
  odsState.addOperands(wrEn);
  odsState.addOperands(clk);
  odsState.addOperands(rst);
  odsState.getOrAddProperties<Properties>().depth = depth;
  if (rdLatency) {
    odsState.getOrAddProperties<Properties>().rdLatency = rdLatency;
  }
  if (almostFullThreshold) {
    odsState.getOrAddProperties<Properties>().almostFullThreshold = almostFullThreshold;
  }
  if (almostEmptyThreshold) {
    odsState.getOrAddProperties<Properties>().almostEmptyThreshold = almostEmptyThreshold;
  }
  assert(resultTypes.size() >= 3u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

FIFOOp FIFOOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value input, ::mlir::Value rdEn, ::mlir::Value wrEn, ::mlir::Value clk, ::mlir::Value rst, ::mlir::IntegerAttr depth, /*optional*/::mlir::IntegerAttr rdLatency, /*optional*/::mlir::IntegerAttr almostFullThreshold, /*optional*/::mlir::IntegerAttr almostEmptyThreshold) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(input)>(input), std::forward<decltype(rdEn)>(rdEn), std::forward<decltype(wrEn)>(wrEn), std::forward<decltype(clk)>(clk), std::forward<decltype(rst)>(rst), std::forward<decltype(depth)>(depth), std::forward<decltype(rdLatency)>(rdLatency), std::forward<decltype(almostFullThreshold)>(almostFullThreshold), std::forward<decltype(almostEmptyThreshold)>(almostEmptyThreshold));
  auto __res__ = ::llvm::dyn_cast<FIFOOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

FIFOOp FIFOOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value input, ::mlir::Value rdEn, ::mlir::Value wrEn, ::mlir::Value clk, ::mlir::Value rst, ::mlir::IntegerAttr depth, /*optional*/::mlir::IntegerAttr rdLatency, /*optional*/::mlir::IntegerAttr almostFullThreshold, /*optional*/::mlir::IntegerAttr almostEmptyThreshold) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(input)>(input), std::forward<decltype(rdEn)>(rdEn), std::forward<decltype(wrEn)>(wrEn), std::forward<decltype(clk)>(clk), std::forward<decltype(rst)>(rst), std::forward<decltype(depth)>(depth), std::forward<decltype(rdLatency)>(rdLatency), std::forward<decltype(almostFullThreshold)>(almostFullThreshold), std::forward<decltype(almostEmptyThreshold)>(almostEmptyThreshold));
}

void FIFOOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type output, ::mlir::Type full, ::mlir::Type empty, /*optional*/::mlir::Type almostFull, /*optional*/::mlir::Type almostEmpty, ::mlir::Value input, ::mlir::Value rdEn, ::mlir::Value wrEn, ::mlir::Value clk, ::mlir::Value rst, uint64_t depth, /*optional*/uint64_t rdLatency, /*optional*/::mlir::IntegerAttr almostFullThreshold, /*optional*/::mlir::IntegerAttr almostEmptyThreshold) {
  odsState.addOperands(input);
  odsState.addOperands(rdEn);
  odsState.addOperands(wrEn);
  odsState.addOperands(clk);
  odsState.addOperands(rst);
  odsState.getOrAddProperties<Properties>().depth = odsBuilder.getIntegerAttr(odsBuilder.getIntegerType(64), depth);
  odsState.getOrAddProperties<Properties>().rdLatency = odsBuilder.getIntegerAttr(odsBuilder.getIntegerType(64), rdLatency);
  if (almostFullThreshold) {
    odsState.getOrAddProperties<Properties>().almostFullThreshold = almostFullThreshold;
  }
  if (almostEmptyThreshold) {
    odsState.getOrAddProperties<Properties>().almostEmptyThreshold = almostEmptyThreshold;
  }
  odsState.addTypes(output);
  odsState.addTypes(full);
  odsState.addTypes(empty);
  if (almostFull)
    odsState.addTypes(almostFull);
  if (almostEmpty)
    odsState.addTypes(almostEmpty);
  ::llvm::copy(::llvm::ArrayRef<int32_t>({1, 1, 1, (almostFull ? 1 : 0), (almostEmpty ? 1 : 0)}), odsState.getOrAddProperties<Properties>().resultSegmentSizes.begin());
}

FIFOOp FIFOOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type output, ::mlir::Type full, ::mlir::Type empty, /*optional*/::mlir::Type almostFull, /*optional*/::mlir::Type almostEmpty, ::mlir::Value input, ::mlir::Value rdEn, ::mlir::Value wrEn, ::mlir::Value clk, ::mlir::Value rst, uint64_t depth, /*optional*/uint64_t rdLatency, /*optional*/::mlir::IntegerAttr almostFullThreshold, /*optional*/::mlir::IntegerAttr almostEmptyThreshold) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(output)>(output), std::forward<decltype(full)>(full), std::forward<decltype(empty)>(empty), std::forward<decltype(almostFull)>(almostFull), std::forward<decltype(almostEmpty)>(almostEmpty), std::forward<decltype(input)>(input), std::forward<decltype(rdEn)>(rdEn), std::forward<decltype(wrEn)>(wrEn), std::forward<decltype(clk)>(clk), std::forward<decltype(rst)>(rst), std::forward<decltype(depth)>(depth), std::forward<decltype(rdLatency)>(rdLatency), std::forward<decltype(almostFullThreshold)>(almostFullThreshold), std::forward<decltype(almostEmptyThreshold)>(almostEmptyThreshold));
  auto __res__ = ::llvm::dyn_cast<FIFOOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

FIFOOp FIFOOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type output, ::mlir::Type full, ::mlir::Type empty, /*optional*/::mlir::Type almostFull, /*optional*/::mlir::Type almostEmpty, ::mlir::Value input, ::mlir::Value rdEn, ::mlir::Value wrEn, ::mlir::Value clk, ::mlir::Value rst, uint64_t depth, /*optional*/uint64_t rdLatency, /*optional*/::mlir::IntegerAttr almostFullThreshold, /*optional*/::mlir::IntegerAttr almostEmptyThreshold) {
  return create(builder, builder.getLoc(), std::forward<decltype(output)>(output), std::forward<decltype(full)>(full), std::forward<decltype(empty)>(empty), std::forward<decltype(almostFull)>(almostFull), std::forward<decltype(almostEmpty)>(almostEmpty), std::forward<decltype(input)>(input), std::forward<decltype(rdEn)>(rdEn), std::forward<decltype(wrEn)>(wrEn), std::forward<decltype(clk)>(clk), std::forward<decltype(rst)>(rst), std::forward<decltype(depth)>(depth), std::forward<decltype(rdLatency)>(rdLatency), std::forward<decltype(almostFullThreshold)>(almostFullThreshold), std::forward<decltype(almostEmptyThreshold)>(almostEmptyThreshold));
}

void FIFOOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value input, ::mlir::Value rdEn, ::mlir::Value wrEn, ::mlir::Value clk, ::mlir::Value rst, uint64_t depth, /*optional*/uint64_t rdLatency, /*optional*/::mlir::IntegerAttr almostFullThreshold, /*optional*/::mlir::IntegerAttr almostEmptyThreshold) {
  odsState.addOperands(input);
  odsState.addOperands(rdEn);
  odsState.addOperands(wrEn);
  odsState.addOperands(clk);
  odsState.addOperands(rst);
  odsState.getOrAddProperties<Properties>().depth = odsBuilder.getIntegerAttr(odsBuilder.getIntegerType(64), depth);
  odsState.getOrAddProperties<Properties>().rdLatency = odsBuilder.getIntegerAttr(odsBuilder.getIntegerType(64), rdLatency);
  if (almostFullThreshold) {
    odsState.getOrAddProperties<Properties>().almostFullThreshold = almostFullThreshold;
  }
  if (almostEmptyThreshold) {
    odsState.getOrAddProperties<Properties>().almostEmptyThreshold = almostEmptyThreshold;
  }
  assert(resultTypes.size() >= 3u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

FIFOOp FIFOOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value input, ::mlir::Value rdEn, ::mlir::Value wrEn, ::mlir::Value clk, ::mlir::Value rst, uint64_t depth, /*optional*/uint64_t rdLatency, /*optional*/::mlir::IntegerAttr almostFullThreshold, /*optional*/::mlir::IntegerAttr almostEmptyThreshold) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(input)>(input), std::forward<decltype(rdEn)>(rdEn), std::forward<decltype(wrEn)>(wrEn), std::forward<decltype(clk)>(clk), std::forward<decltype(rst)>(rst), std::forward<decltype(depth)>(depth), std::forward<decltype(rdLatency)>(rdLatency), std::forward<decltype(almostFullThreshold)>(almostFullThreshold), std::forward<decltype(almostEmptyThreshold)>(almostEmptyThreshold));
  auto __res__ = ::llvm::dyn_cast<FIFOOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

FIFOOp FIFOOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value input, ::mlir::Value rdEn, ::mlir::Value wrEn, ::mlir::Value clk, ::mlir::Value rst, uint64_t depth, /*optional*/uint64_t rdLatency, /*optional*/::mlir::IntegerAttr almostFullThreshold, /*optional*/::mlir::IntegerAttr almostEmptyThreshold) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(input)>(input), std::forward<decltype(rdEn)>(rdEn), std::forward<decltype(wrEn)>(wrEn), std::forward<decltype(clk)>(clk), std::forward<decltype(rst)>(rst), std::forward<decltype(depth)>(depth), std::forward<decltype(rdLatency)>(rdLatency), std::forward<decltype(almostFullThreshold)>(almostFullThreshold), std::forward<decltype(almostEmptyThreshold)>(almostEmptyThreshold));
}

void FIFOOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 5u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() >= 3u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<FIFOOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

FIFOOp FIFOOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<FIFOOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

FIFOOp FIFOOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void FIFOOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 5u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() >= 3u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

FIFOOp FIFOOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<FIFOOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

FIFOOp FIFOOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult FIFOOp::verifyInvariantsImpl() {
  auto tblgen_almostEmptyThreshold = getProperties().almostEmptyThreshold; (void)tblgen_almostEmptyThreshold;
  auto tblgen_almostFullThreshold = getProperties().almostFullThreshold; (void)tblgen_almostFullThreshold;
  auto tblgen_depth = getProperties().depth; (void)tblgen_depth;
  if (!tblgen_depth) return emitOpError("requires attribute 'depth'");
  auto tblgen_rdLatency = getProperties().rdLatency; (void)tblgen_rdLatency;

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Seq5(*this, tblgen_depth, "depth")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Seq6(*this, tblgen_rdLatency, "rdLatency")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Seq6(*this, tblgen_almostFullThreshold, "almostFullThreshold")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Seq6(*this, tblgen_almostEmptyThreshold, "almostEmptyThreshold")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Seq3(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSOperands(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Seq2(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup2 = getODSOperands(2);

    for (auto v : valueGroup2) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Seq2(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup3 = getODSOperands(3);

    for (auto v : valueGroup3) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Seq1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup4 = getODSOperands(4);

    for (auto v : valueGroup4) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Seq2(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Seq3(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSResults(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Seq2(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup2 = getODSResults(2);

    for (auto v : valueGroup2) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Seq2(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup3 = getODSResults(3);

    if (valueGroup3.size() > 1) {
      return emitOpError("result group starting at #") << index
          << " requires 0 or 1 element, but found " << valueGroup3.size();
    }

    for (auto v : valueGroup3) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Seq2(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup4 = getODSResults(4);

    if (valueGroup4.size() > 1) {
      return emitOpError("result group starting at #") << index
          << " requires 0 or 1 element, but found " << valueGroup4.size();
    }

    for (auto v : valueGroup4) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Seq2(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  if (!((std::equal_to<>()( (*this->getODSOperands(0).begin()).getType() , (*this->getODSResults(0).begin()).getType()))))
    return emitOpError("failed to verify that Input type should match output type");
  return ::mlir::success();
}

::llvm::LogicalResult FIFOOp::verifyInvariants() {
  if(::mlir::succeeded(verifyInvariantsImpl()) && ::mlir::succeeded(verify()))
    return ::mlir::success();
  return ::mlir::failure();
}

::mlir::ParseResult FIFOOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::IntegerAttr depthAttr;
  ::mlir::IntegerAttr rdLatencyAttr;
  ::mlir::IntegerAttr almostFullThresholdAttr;
  ::llvm::SmallVector<::mlir::Type, 1> almostFullTypes;
  ::mlir::IntegerAttr almostEmptyThresholdAttr;
  ::llvm::SmallVector<::mlir::Type, 1> almostEmptyTypes;
  ::mlir::OpAsmParser::UnresolvedOperand inputRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> inputOperands(&inputRawOperand, 1);  ::llvm::SMLoc inputOperandsLoc;
  (void)inputOperandsLoc;
  ::mlir::OpAsmParser::UnresolvedOperand rdEnRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> rdEnOperands(&rdEnRawOperand, 1);  ::llvm::SMLoc rdEnOperandsLoc;
  (void)rdEnOperandsLoc;
  ::mlir::OpAsmParser::UnresolvedOperand wrEnRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> wrEnOperands(&wrEnRawOperand, 1);  ::llvm::SMLoc wrEnOperandsLoc;
  (void)wrEnOperandsLoc;
  ::mlir::OpAsmParser::UnresolvedOperand clkRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> clkOperands(&clkRawOperand, 1);  ::llvm::SMLoc clkOperandsLoc;
  (void)clkOperandsLoc;
  ::mlir::OpAsmParser::UnresolvedOperand rstRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> rstOperands(&rstRawOperand, 1);  ::llvm::SMLoc rstOperandsLoc;
  (void)rstOperandsLoc;
  ::mlir::Type inputRawType{};
  ::llvm::ArrayRef<::mlir::Type> inputTypes(&inputRawType, 1);
  if (parser.parseKeyword("depth"))
    return ::mlir::failure();

  if (parser.parseCustomAttributeWithFallback(depthAttr, parser.getBuilder().getIntegerType(64))) {
    return ::mlir::failure();
  }
  if (depthAttr) result.getOrAddProperties<FIFOOp::Properties>().depth = depthAttr;
  if (::mlir::succeeded(parser.parseOptionalKeyword("rd_latency"))) {

  if (parser.parseCustomAttributeWithFallback(rdLatencyAttr, parser.getBuilder().getIntegerType(64))) {
    return ::mlir::failure();
  }
  if (rdLatencyAttr) result.getOrAddProperties<FIFOOp::Properties>().rdLatency = rdLatencyAttr;
  }
  {
    ::mlir::Type almostFullType;
    auto odsResult = parseFIFOAFThreshold(parser, almostFullThresholdAttr, almostFullType);
    if (odsResult) return ::mlir::failure();
    if (almostFullThresholdAttr)
      result.getOrAddProperties<FIFOOp::Properties>().almostFullThreshold = almostFullThresholdAttr;
    if (almostFullType)
      almostFullTypes.push_back(almostFullType);
  }
  {
    ::mlir::Type almostEmptyType;
    auto odsResult = parseFIFOAEThreshold(parser, almostEmptyThresholdAttr, almostEmptyType);
    if (odsResult) return ::mlir::failure();
    if (almostEmptyThresholdAttr)
      result.getOrAddProperties<FIFOOp::Properties>().almostEmptyThreshold = almostEmptyThresholdAttr;
    if (almostEmptyType)
      almostEmptyTypes.push_back(almostEmptyType);
  }
  if (parser.parseKeyword("in"))
    return ::mlir::failure();

  inputOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(inputRawOperand))
    return ::mlir::failure();
  if (parser.parseKeyword("rdEn"))
    return ::mlir::failure();

  rdEnOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(rdEnRawOperand))
    return ::mlir::failure();
  if (parser.parseKeyword("wrEn"))
    return ::mlir::failure();

  wrEnOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(wrEnRawOperand))
    return ::mlir::failure();
  if (parser.parseKeyword("clk"))
    return ::mlir::failure();

  clkOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(clkRawOperand))
    return ::mlir::failure();
  if (parser.parseKeyword("rst"))
    return ::mlir::failure();

  rstOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(rstRawOperand))
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
    inputRawType = type;
  }
::llvm::copy(::llvm::ArrayRef<int32_t>({1, 1, 1, static_cast<int32_t>(almostFullTypes.size()), static_cast<int32_t>(almostEmptyTypes.size())}), result.getOrAddProperties<FIFOOp::Properties>().resultSegmentSizes.begin());
  for (::mlir::Type type : inputTypes) {
    (void)type;
    if (!(!((::llvm::isa<::mlir::TokenType>(type))))) {
      return parser.emitError(parser.getNameLoc()) << "'input' must be any non-token type, but got " << type;
    }
  }
  ::mlir::Type odsBuildableType0 = parser.getBuilder().getIntegerType(1);
  ::mlir::Type odsBuildableType1 = parser.getBuilder().getType<::circt::seq::ClockType>();
  result.addTypes( inputTypes[0] );
  result.addTypes(odsBuildableType0);
  result.addTypes(odsBuildableType0);
  result.addTypes(almostFullTypes);
  result.addTypes(almostEmptyTypes);
  if (parser.resolveOperands(inputOperands, inputTypes, inputOperandsLoc, result.operands))
    return ::mlir::failure();
  if (parser.resolveOperands(rdEnOperands, odsBuildableType0, rdEnOperandsLoc, result.operands))
    return ::mlir::failure();
  if (parser.resolveOperands(wrEnOperands, odsBuildableType0, wrEnOperandsLoc, result.operands))
    return ::mlir::failure();
  if (parser.resolveOperands(clkOperands, odsBuildableType1, clkOperandsLoc, result.operands))
    return ::mlir::failure();
  if (parser.resolveOperands(rstOperands, odsBuildableType0, rstOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void FIFOOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ' << "depth";
  _odsPrinter << ' ';
  _odsPrinter.printAttributeWithoutType(getDepthAttr());
  if ((getRdLatencyAttr() && getRdLatencyAttr() != ::mlir::OpBuilder((*this)->getContext()).getIntegerAttr(::mlir::OpBuilder((*this)->getContext()).getIntegerType(64), 0))) {
    _odsPrinter << ' ' << "rd_latency";
    _odsPrinter << ' ';
    _odsPrinter.printAttributeWithoutType(getRdLatencyAttr());
  }
  _odsPrinter << ' ';
  printFIFOAFThreshold(_odsPrinter, *this, getAlmostFullThresholdAttr(), (getAlmostFull() ? getAlmostFull().getType() : ::mlir::Type()));
  _odsPrinter << ' ';
  printFIFOAEThreshold(_odsPrinter, *this, getAlmostEmptyThresholdAttr(), (getAlmostEmpty() ? getAlmostEmpty().getType() : ::mlir::Type()));
  _odsPrinter << ' ' << "in";
  _odsPrinter << ' ';
  _odsPrinter << getInput();
  _odsPrinter << ' ' << "rdEn";
  _odsPrinter << ' ';
  _odsPrinter << getRdEn();
  _odsPrinter << ' ' << "wrEn";
  _odsPrinter << ' ';
  _odsPrinter << getWrEn();
  _odsPrinter << ' ' << "clk";
  _odsPrinter << ' ';
  _odsPrinter << getClk();
  _odsPrinter << ' ' << "rst";
  _odsPrinter << ' ';
  _odsPrinter << getRst();
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("resultSegmentSizes");
  elidedAttrs.push_back("depth");
  elidedAttrs.push_back("rdLatency");
  elidedAttrs.push_back("almostFullThreshold");
  elidedAttrs.push_back("almostEmptyThreshold");
  {
     ::mlir::Builder odsBuilder(getContext());
     ::mlir::Attribute attr = getRdLatencyAttr();
     if(attr && (attr == odsBuilder.getIntegerAttr(odsBuilder.getIntegerType(64), 0)))
       elidedAttrs.push_back("rdLatency");
  }
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
  {
    auto type = getInput().getType();
    if (auto validType = ::llvm::dyn_cast<::mlir::Type>(type))
      _odsPrinter.printStrippedAttrOrType(validType);
   else
     _odsPrinter << type;
  }
}


} // namespace circt::seq
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::seq::FIFOOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::seq::detail::FIFOOpGenericAdaptorBase::Properties)

namespace circt::seq {


//===----------------------------------------------------------------------===//
// ::circt::seq::FirMemOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

FirMemOpGenericAdaptorBase::FirMemOpGenericAdaptorBase(FirMemOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

uint32_t FirMemOpGenericAdaptorBase::getReadLatency() {
  auto attr = getReadLatencyAttr();
  return attr.getValue().getZExtValue();
}

uint32_t FirMemOpGenericAdaptorBase::getWriteLatency() {
  auto attr = getWriteLatencyAttr();
  return attr.getValue().getZExtValue();
}

circt::seq::RUW FirMemOpGenericAdaptorBase::getRuw() {
  auto attr = getRuwAttr();
  return attr.getValue();
}

circt::seq::WUW FirMemOpGenericAdaptorBase::getWuw() {
  auto attr = getWuwAttr();
  return attr.getValue();
}

::std::optional< ::llvm::StringRef > FirMemOpGenericAdaptorBase::getName() {
  auto attr = getNameAttr();
  return attr ? ::std::optional< ::llvm::StringRef >(attr.getValue()) : (::std::nullopt);
}

::std::optional<::circt::hw::InnerSymAttr> FirMemOpGenericAdaptorBase::getInnerSym() {
  auto attr = getInnerSymAttr();
  return attr ? ::std::optional<::circt::hw::InnerSymAttr>(::llvm::cast<::circt::hw::InnerSymAttr>(attr)) : (::std::nullopt);
}

::std::optional<::circt::seq::FirMemInitAttr> FirMemOpGenericAdaptorBase::getInit() {
  auto attr = getInitAttr();
  return attr ? ::std::optional<::circt::seq::FirMemInitAttr>(::llvm::cast<::circt::seq::FirMemInitAttr>(attr)) : (::std::nullopt);
}

::std::optional< ::llvm::StringRef > FirMemOpGenericAdaptorBase::getPrefix() {
  auto attr = getPrefixAttr();
  return attr ? ::std::optional< ::llvm::StringRef >(attr.getValue()) : (::std::nullopt);
}

::std::optional<::mlir::Attribute> FirMemOpGenericAdaptorBase::getOutputFile() {
  auto attr = getOutputFileAttr();
  return attr ? ::std::optional<::mlir::Attribute>(attr) : (::std::nullopt);
}


} // namespace detail
FirMemOpAdaptor::FirMemOpAdaptor(FirMemOp op) : FirMemOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult FirMemOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_init = getProperties().init; (void)tblgen_init;
  auto tblgen_inner_sym = getProperties().inner_sym; (void)tblgen_inner_sym;
  auto tblgen_name = getProperties().name; (void)tblgen_name;
  auto tblgen_output_file = getProperties().output_file; (void)tblgen_output_file;
  auto tblgen_prefix = getProperties().prefix; (void)tblgen_prefix;
  auto tblgen_readLatency = getProperties().readLatency; (void)tblgen_readLatency;
  if (!tblgen_readLatency) return emitError(loc, "'seq.firmem' op requires attribute 'readLatency'");
  auto tblgen_ruw = getProperties().ruw; (void)tblgen_ruw;
  if (!tblgen_ruw) return emitError(loc, "'seq.firmem' op requires attribute 'ruw'");
  auto tblgen_writeLatency = getProperties().writeLatency; (void)tblgen_writeLatency;
  if (!tblgen_writeLatency) return emitError(loc, "'seq.firmem' op requires attribute 'writeLatency'");
  auto tblgen_wuw = getProperties().wuw; (void)tblgen_wuw;
  if (!tblgen_wuw) return emitError(loc, "'seq.firmem' op requires attribute 'wuw'");

  if (tblgen_readLatency && !(((::llvm::isa<::mlir::IntegerAttr>(tblgen_readLatency))) && ((::llvm::cast<::mlir::IntegerAttr>(tblgen_readLatency).getType().isSignlessInteger(32)))))
    return emitError(loc, "'seq.firmem' op attribute 'readLatency' failed to satisfy constraint: 32-bit signless integer attribute");

  if (tblgen_writeLatency && !(((::llvm::isa<::mlir::IntegerAttr>(tblgen_writeLatency))) && ((::llvm::cast<::mlir::IntegerAttr>(tblgen_writeLatency).getType().isSignlessInteger(32)))))
    return emitError(loc, "'seq.firmem' op attribute 'writeLatency' failed to satisfy constraint: 32-bit signless integer attribute");

  if (tblgen_ruw && !((::llvm::isa<circt::seq::RUWAttr>(tblgen_ruw))))
    return emitError(loc, "'seq.firmem' op attribute 'ruw' failed to satisfy constraint: Read-Under-Write Behavior");

  if (tblgen_wuw && !((::llvm::isa<circt::seq::WUWAttr>(tblgen_wuw))))
    return emitError(loc, "'seq.firmem' op attribute 'wuw' failed to satisfy constraint: Write-Under-Write Behavior");

  if (tblgen_name && !((::llvm::isa<::mlir::StringAttr>(tblgen_name))))
    return emitError(loc, "'seq.firmem' op attribute 'name' failed to satisfy constraint: string attribute");

  if (tblgen_inner_sym && !((::llvm::isa<::circt::hw::InnerSymAttr>(tblgen_inner_sym))))
    return emitError(loc, "'seq.firmem' op attribute 'inner_sym' failed to satisfy constraint: Inner symbol definition");

  if (tblgen_init && !((::llvm::isa<::circt::seq::FirMemInitAttr>(tblgen_init))))
    return emitError(loc, "'seq.firmem' op attribute 'init' failed to satisfy constraint: Memory initialization information");

  if (tblgen_prefix && !((::llvm::isa<::mlir::StringAttr>(tblgen_prefix))))
    return emitError(loc, "'seq.firmem' op attribute 'prefix' failed to satisfy constraint: string attribute");

  if (tblgen_output_file && !((true)))
    return emitError(loc, "'seq.firmem' op attribute 'output_file' failed to satisfy constraint: any attribute");
  return ::mlir::success();
}

::llvm::LogicalResult FirMemOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.init;
       auto attr = dict.get("init");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `init` in property conversion: " << attr;
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
    auto &propStorage = prop.output_file;
       auto attr = dict.get("output_file");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `output_file` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.prefix;
       auto attr = dict.get("prefix");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `prefix` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.readLatency;
       auto attr = dict.get("readLatency");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `readLatency` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.ruw;
       auto attr = dict.get("ruw");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `ruw` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.writeLatency;
       auto attr = dict.get("writeLatency");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `writeLatency` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.wuw;
       auto attr = dict.get("wuw");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `wuw` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  return ::mlir::success();
}

::mlir::Attribute FirMemOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.init;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("init",
                                       propStorage));
    }

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
      const auto &propStorage = prop.output_file;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("output_file",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.prefix;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("prefix",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.readLatency;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("readLatency",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.ruw;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("ruw",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.writeLatency;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("writeLatency",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.wuw;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("wuw",
                                       propStorage));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code FirMemOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.init.getAsOpaquePointer()), 
    llvm::hash_value(prop.inner_sym.getAsOpaquePointer()), 
    llvm::hash_value(prop.name.getAsOpaquePointer()), 
    llvm::hash_value(prop.output_file.getAsOpaquePointer()), 
    llvm::hash_value(prop.prefix.getAsOpaquePointer()), 
    llvm::hash_value(prop.readLatency.getAsOpaquePointer()), 
    llvm::hash_value(prop.ruw.getAsOpaquePointer()), 
    llvm::hash_value(prop.writeLatency.getAsOpaquePointer()), 
    llvm::hash_value(prop.wuw.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> FirMemOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "init")
      return prop.init;

    if (name == "inner_sym")
      return prop.inner_sym;

    if (name == "name")
      return prop.name;

    if (name == "output_file")
      return prop.output_file;

    if (name == "prefix")
      return prop.prefix;

    if (name == "readLatency")
      return prop.readLatency;

    if (name == "ruw")
      return prop.ruw;

    if (name == "writeLatency")
      return prop.writeLatency;

    if (name == "wuw")
      return prop.wuw;
  return std::nullopt;
}

void FirMemOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "init") {
       prop.init = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.init)>>(value);
       return;
    }

    if (name == "inner_sym") {
       prop.inner_sym = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.inner_sym)>>(value);
       return;
    }

    if (name == "name") {
       prop.name = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.name)>>(value);
       return;
    }

    if (name == "output_file") {
       prop.output_file = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.output_file)>>(value);
       return;
    }

    if (name == "prefix") {
       prop.prefix = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.prefix)>>(value);
       return;
    }

    if (name == "readLatency") {
       prop.readLatency = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.readLatency)>>(value);
       return;
    }

    if (name == "ruw") {
       prop.ruw = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.ruw)>>(value);
       return;
    }

    if (name == "writeLatency") {
       prop.writeLatency = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.writeLatency)>>(value);
       return;
    }

    if (name == "wuw") {
       prop.wuw = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.wuw)>>(value);
       return;
    }
}

void FirMemOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.init) attrs.append("init", prop.init);

    if (prop.inner_sym) attrs.append("inner_sym", prop.inner_sym);

    if (prop.name) attrs.append("name", prop.name);

    if (prop.output_file) attrs.append("output_file", prop.output_file);

    if (prop.prefix) attrs.append("prefix", prop.prefix);

    if (prop.readLatency) attrs.append("readLatency", prop.readLatency);

    if (prop.ruw) attrs.append("ruw", prop.ruw);

    if (prop.writeLatency) attrs.append("writeLatency", prop.writeLatency);

    if (prop.wuw) attrs.append("wuw", prop.wuw);
}

::llvm::LogicalResult FirMemOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getInitAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Seq10(attr, "init", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getInnerSymAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Seq2(attr, "inner_sym", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getNameAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Seq3(attr, "name", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getOutputFileAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Seq11(attr, "output_file", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getPrefixAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Seq3(attr, "prefix", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getReadLatencyAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Seq7(attr, "readLatency", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getRuwAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Seq8(attr, "ruw", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getWriteLatencyAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Seq7(attr, "writeLatency", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getWuwAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Seq9(attr, "wuw", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult FirMemOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readOptionalAttribute(prop.init)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readOptionalAttribute(prop.inner_sym)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readOptionalAttribute(prop.name)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readOptionalAttribute(prop.output_file)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readOptionalAttribute(prop.prefix)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readAttribute(prop.readLatency)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readAttribute(prop.ruw)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readAttribute(prop.writeLatency)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readAttribute(prop.wuw)))
    return ::mlir::failure();
  return ::mlir::success();
}

void FirMemOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;

  writer.writeOptionalAttribute(prop.init);

  writer.writeOptionalAttribute(prop.inner_sym);

  writer.writeOptionalAttribute(prop.name);

  writer.writeOptionalAttribute(prop.output_file);

  writer.writeOptionalAttribute(prop.prefix);
  writer.writeAttribute(prop.readLatency);
  writer.writeAttribute(prop.ruw);
  writer.writeAttribute(prop.writeLatency);
  writer.writeAttribute(prop.wuw);
}

uint32_t FirMemOp::getReadLatency() {
  auto attr = getReadLatencyAttr();
  return attr.getValue().getZExtValue();
}

uint32_t FirMemOp::getWriteLatency() {
  auto attr = getWriteLatencyAttr();
  return attr.getValue().getZExtValue();
}

circt::seq::RUW FirMemOp::getRuw() {
  auto attr = getRuwAttr();
  return attr.getValue();
}

circt::seq::WUW FirMemOp::getWuw() {
  auto attr = getWuwAttr();
  return attr.getValue();
}

::std::optional< ::llvm::StringRef > FirMemOp::getName() {
  auto attr = getNameAttr();
  return attr ? ::std::optional< ::llvm::StringRef >(attr.getValue()) : (::std::nullopt);
}

::std::optional<::circt::hw::InnerSymAttr> FirMemOp::getInnerSym() {
  auto attr = getInnerSymAttr();
  return attr ? ::std::optional<::circt::hw::InnerSymAttr>(::llvm::cast<::circt::hw::InnerSymAttr>(attr)) : (::std::nullopt);
}

::std::optional<::circt::seq::FirMemInitAttr> FirMemOp::getInit() {
  auto attr = getInitAttr();
  return attr ? ::std::optional<::circt::seq::FirMemInitAttr>(::llvm::cast<::circt::seq::FirMemInitAttr>(attr)) : (::std::nullopt);
}

::std::optional< ::llvm::StringRef > FirMemOp::getPrefix() {
  auto attr = getPrefixAttr();
  return attr ? ::std::optional< ::llvm::StringRef >(attr.getValue()) : (::std::nullopt);
}

::std::optional<::mlir::Attribute> FirMemOp::getOutputFile() {
  auto attr = getOutputFileAttr();
  return attr ? ::std::optional<::mlir::Attribute>(attr) : (::std::nullopt);
}

void FirMemOp::setReadLatency(uint32_t attrValue) {
  getProperties().readLatency = ::mlir::Builder((*this)->getContext()).getIntegerAttr(::mlir::Builder((*this)->getContext()).getIntegerType(32), attrValue);
}

void FirMemOp::setWriteLatency(uint32_t attrValue) {
  getProperties().writeLatency = ::mlir::Builder((*this)->getContext()).getIntegerAttr(::mlir::Builder((*this)->getContext()).getIntegerType(32), attrValue);
}

void FirMemOp::setRuw(circt::seq::RUW attrValue) {
  getProperties().ruw = circt::seq::RUWAttr::get(::mlir::Builder((*this)->getContext()).getContext(), attrValue);
}

void FirMemOp::setWuw(circt::seq::WUW attrValue) {
  getProperties().wuw = circt::seq::WUWAttr::get(::mlir::Builder((*this)->getContext()).getContext(), attrValue);
}

void FirMemOp::setName(::std::optional<::llvm::StringRef> attrValue) {
    auto &odsProp = getProperties().name;
    if (attrValue)
      odsProp = ::mlir::Builder((*this)->getContext()).getStringAttr(*attrValue);
    else
      odsProp = nullptr;
}

void FirMemOp::setPrefix(::std::optional<::llvm::StringRef> attrValue) {
    auto &odsProp = getProperties().prefix;
    if (attrValue)
      odsProp = ::mlir::Builder((*this)->getContext()).getStringAttr(*attrValue);
    else
      odsProp = nullptr;
}

void FirMemOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type memory, ::mlir::IntegerAttr readLatency, ::mlir::IntegerAttr writeLatency, circt::seq::RUWAttr ruw, circt::seq::WUWAttr wuw, /*optional*/::mlir::StringAttr name, /*optional*/::circt::hw::InnerSymAttr inner_sym, /*optional*/::circt::seq::FirMemInitAttr init, /*optional*/::mlir::StringAttr prefix, /*optional*/::mlir::Attribute output_file) {
  odsState.getOrAddProperties<Properties>().readLatency = readLatency;
  odsState.getOrAddProperties<Properties>().writeLatency = writeLatency;
  odsState.getOrAddProperties<Properties>().ruw = ruw;
  odsState.getOrAddProperties<Properties>().wuw = wuw;
  if (name) {
    odsState.getOrAddProperties<Properties>().name = name;
  }
  if (inner_sym) {
    odsState.getOrAddProperties<Properties>().inner_sym = inner_sym;
  }
  if (init) {
    odsState.getOrAddProperties<Properties>().init = init;
  }
  if (prefix) {
    odsState.getOrAddProperties<Properties>().prefix = prefix;
  }
  if (output_file) {
    odsState.getOrAddProperties<Properties>().output_file = output_file;
  }
  odsState.addTypes(memory);
}

FirMemOp FirMemOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type memory, ::mlir::IntegerAttr readLatency, ::mlir::IntegerAttr writeLatency, circt::seq::RUWAttr ruw, circt::seq::WUWAttr wuw, /*optional*/::mlir::StringAttr name, /*optional*/::circt::hw::InnerSymAttr inner_sym, /*optional*/::circt::seq::FirMemInitAttr init, /*optional*/::mlir::StringAttr prefix, /*optional*/::mlir::Attribute output_file) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(memory)>(memory), std::forward<decltype(readLatency)>(readLatency), std::forward<decltype(writeLatency)>(writeLatency), std::forward<decltype(ruw)>(ruw), std::forward<decltype(wuw)>(wuw), std::forward<decltype(name)>(name), std::forward<decltype(inner_sym)>(inner_sym), std::forward<decltype(init)>(init), std::forward<decltype(prefix)>(prefix), std::forward<decltype(output_file)>(output_file));
  auto __res__ = ::llvm::dyn_cast<FirMemOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

FirMemOp FirMemOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type memory, ::mlir::IntegerAttr readLatency, ::mlir::IntegerAttr writeLatency, circt::seq::RUWAttr ruw, circt::seq::WUWAttr wuw, /*optional*/::mlir::StringAttr name, /*optional*/::circt::hw::InnerSymAttr inner_sym, /*optional*/::circt::seq::FirMemInitAttr init, /*optional*/::mlir::StringAttr prefix, /*optional*/::mlir::Attribute output_file) {
  return create(builder, builder.getLoc(), std::forward<decltype(memory)>(memory), std::forward<decltype(readLatency)>(readLatency), std::forward<decltype(writeLatency)>(writeLatency), std::forward<decltype(ruw)>(ruw), std::forward<decltype(wuw)>(wuw), std::forward<decltype(name)>(name), std::forward<decltype(inner_sym)>(inner_sym), std::forward<decltype(init)>(init), std::forward<decltype(prefix)>(prefix), std::forward<decltype(output_file)>(output_file));
}

void FirMemOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::IntegerAttr readLatency, ::mlir::IntegerAttr writeLatency, circt::seq::RUWAttr ruw, circt::seq::WUWAttr wuw, /*optional*/::mlir::StringAttr name, /*optional*/::circt::hw::InnerSymAttr inner_sym, /*optional*/::circt::seq::FirMemInitAttr init, /*optional*/::mlir::StringAttr prefix, /*optional*/::mlir::Attribute output_file) {
  odsState.getOrAddProperties<Properties>().readLatency = readLatency;
  odsState.getOrAddProperties<Properties>().writeLatency = writeLatency;
  odsState.getOrAddProperties<Properties>().ruw = ruw;
  odsState.getOrAddProperties<Properties>().wuw = wuw;
  if (name) {
    odsState.getOrAddProperties<Properties>().name = name;
  }
  if (inner_sym) {
    odsState.getOrAddProperties<Properties>().inner_sym = inner_sym;
  }
  if (init) {
    odsState.getOrAddProperties<Properties>().init = init;
  }
  if (prefix) {
    odsState.getOrAddProperties<Properties>().prefix = prefix;
  }
  if (output_file) {
    odsState.getOrAddProperties<Properties>().output_file = output_file;
  }
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

FirMemOp FirMemOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::IntegerAttr readLatency, ::mlir::IntegerAttr writeLatency, circt::seq::RUWAttr ruw, circt::seq::WUWAttr wuw, /*optional*/::mlir::StringAttr name, /*optional*/::circt::hw::InnerSymAttr inner_sym, /*optional*/::circt::seq::FirMemInitAttr init, /*optional*/::mlir::StringAttr prefix, /*optional*/::mlir::Attribute output_file) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(readLatency)>(readLatency), std::forward<decltype(writeLatency)>(writeLatency), std::forward<decltype(ruw)>(ruw), std::forward<decltype(wuw)>(wuw), std::forward<decltype(name)>(name), std::forward<decltype(inner_sym)>(inner_sym), std::forward<decltype(init)>(init), std::forward<decltype(prefix)>(prefix), std::forward<decltype(output_file)>(output_file));
  auto __res__ = ::llvm::dyn_cast<FirMemOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

FirMemOp FirMemOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::IntegerAttr readLatency, ::mlir::IntegerAttr writeLatency, circt::seq::RUWAttr ruw, circt::seq::WUWAttr wuw, /*optional*/::mlir::StringAttr name, /*optional*/::circt::hw::InnerSymAttr inner_sym, /*optional*/::circt::seq::FirMemInitAttr init, /*optional*/::mlir::StringAttr prefix, /*optional*/::mlir::Attribute output_file) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(readLatency)>(readLatency), std::forward<decltype(writeLatency)>(writeLatency), std::forward<decltype(ruw)>(ruw), std::forward<decltype(wuw)>(wuw), std::forward<decltype(name)>(name), std::forward<decltype(inner_sym)>(inner_sym), std::forward<decltype(init)>(init), std::forward<decltype(prefix)>(prefix), std::forward<decltype(output_file)>(output_file));
}

void FirMemOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type memory, uint32_t readLatency, uint32_t writeLatency, circt::seq::RUW ruw, circt::seq::WUW wuw, /*optional*/::mlir::StringAttr name, /*optional*/::circt::hw::InnerSymAttr inner_sym, /*optional*/::circt::seq::FirMemInitAttr init, /*optional*/::mlir::StringAttr prefix, /*optional*/::mlir::Attribute output_file) {
  odsState.getOrAddProperties<Properties>().readLatency = odsBuilder.getIntegerAttr(odsBuilder.getIntegerType(32), readLatency);
  odsState.getOrAddProperties<Properties>().writeLatency = odsBuilder.getIntegerAttr(odsBuilder.getIntegerType(32), writeLatency);
  odsState.getOrAddProperties<Properties>().ruw = circt::seq::RUWAttr::get(odsBuilder.getContext(), ruw);
  odsState.getOrAddProperties<Properties>().wuw = circt::seq::WUWAttr::get(odsBuilder.getContext(), wuw);
  if (name) {
    odsState.getOrAddProperties<Properties>().name = name;
  }
  if (inner_sym) {
    odsState.getOrAddProperties<Properties>().inner_sym = inner_sym;
  }
  if (init) {
    odsState.getOrAddProperties<Properties>().init = init;
  }
  if (prefix) {
    odsState.getOrAddProperties<Properties>().prefix = prefix;
  }
  if (output_file) {
    odsState.getOrAddProperties<Properties>().output_file = output_file;
  }
  odsState.addTypes(memory);
}

FirMemOp FirMemOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type memory, uint32_t readLatency, uint32_t writeLatency, circt::seq::RUW ruw, circt::seq::WUW wuw, /*optional*/::mlir::StringAttr name, /*optional*/::circt::hw::InnerSymAttr inner_sym, /*optional*/::circt::seq::FirMemInitAttr init, /*optional*/::mlir::StringAttr prefix, /*optional*/::mlir::Attribute output_file) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(memory)>(memory), std::forward<decltype(readLatency)>(readLatency), std::forward<decltype(writeLatency)>(writeLatency), std::forward<decltype(ruw)>(ruw), std::forward<decltype(wuw)>(wuw), std::forward<decltype(name)>(name), std::forward<decltype(inner_sym)>(inner_sym), std::forward<decltype(init)>(init), std::forward<decltype(prefix)>(prefix), std::forward<decltype(output_file)>(output_file));
  auto __res__ = ::llvm::dyn_cast<FirMemOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

FirMemOp FirMemOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type memory, uint32_t readLatency, uint32_t writeLatency, circt::seq::RUW ruw, circt::seq::WUW wuw, /*optional*/::mlir::StringAttr name, /*optional*/::circt::hw::InnerSymAttr inner_sym, /*optional*/::circt::seq::FirMemInitAttr init, /*optional*/::mlir::StringAttr prefix, /*optional*/::mlir::Attribute output_file) {
  return create(builder, builder.getLoc(), std::forward<decltype(memory)>(memory), std::forward<decltype(readLatency)>(readLatency), std::forward<decltype(writeLatency)>(writeLatency), std::forward<decltype(ruw)>(ruw), std::forward<decltype(wuw)>(wuw), std::forward<decltype(name)>(name), std::forward<decltype(inner_sym)>(inner_sym), std::forward<decltype(init)>(init), std::forward<decltype(prefix)>(prefix), std::forward<decltype(output_file)>(output_file));
}

void FirMemOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, uint32_t readLatency, uint32_t writeLatency, circt::seq::RUW ruw, circt::seq::WUW wuw, /*optional*/::mlir::StringAttr name, /*optional*/::circt::hw::InnerSymAttr inner_sym, /*optional*/::circt::seq::FirMemInitAttr init, /*optional*/::mlir::StringAttr prefix, /*optional*/::mlir::Attribute output_file) {
  odsState.getOrAddProperties<Properties>().readLatency = odsBuilder.getIntegerAttr(odsBuilder.getIntegerType(32), readLatency);
  odsState.getOrAddProperties<Properties>().writeLatency = odsBuilder.getIntegerAttr(odsBuilder.getIntegerType(32), writeLatency);
  odsState.getOrAddProperties<Properties>().ruw = circt::seq::RUWAttr::get(odsBuilder.getContext(), ruw);
  odsState.getOrAddProperties<Properties>().wuw = circt::seq::WUWAttr::get(odsBuilder.getContext(), wuw);
  if (name) {
    odsState.getOrAddProperties<Properties>().name = name;
  }
  if (inner_sym) {
    odsState.getOrAddProperties<Properties>().inner_sym = inner_sym;
  }
  if (init) {
    odsState.getOrAddProperties<Properties>().init = init;
  }
  if (prefix) {
    odsState.getOrAddProperties<Properties>().prefix = prefix;
  }
  if (output_file) {
    odsState.getOrAddProperties<Properties>().output_file = output_file;
  }
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

FirMemOp FirMemOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, uint32_t readLatency, uint32_t writeLatency, circt::seq::RUW ruw, circt::seq::WUW wuw, /*optional*/::mlir::StringAttr name, /*optional*/::circt::hw::InnerSymAttr inner_sym, /*optional*/::circt::seq::FirMemInitAttr init, /*optional*/::mlir::StringAttr prefix, /*optional*/::mlir::Attribute output_file) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(readLatency)>(readLatency), std::forward<decltype(writeLatency)>(writeLatency), std::forward<decltype(ruw)>(ruw), std::forward<decltype(wuw)>(wuw), std::forward<decltype(name)>(name), std::forward<decltype(inner_sym)>(inner_sym), std::forward<decltype(init)>(init), std::forward<decltype(prefix)>(prefix), std::forward<decltype(output_file)>(output_file));
  auto __res__ = ::llvm::dyn_cast<FirMemOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

FirMemOp FirMemOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, uint32_t readLatency, uint32_t writeLatency, circt::seq::RUW ruw, circt::seq::WUW wuw, /*optional*/::mlir::StringAttr name, /*optional*/::circt::hw::InnerSymAttr inner_sym, /*optional*/::circt::seq::FirMemInitAttr init, /*optional*/::mlir::StringAttr prefix, /*optional*/::mlir::Attribute output_file) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(readLatency)>(readLatency), std::forward<decltype(writeLatency)>(writeLatency), std::forward<decltype(ruw)>(ruw), std::forward<decltype(wuw)>(wuw), std::forward<decltype(name)>(name), std::forward<decltype(inner_sym)>(inner_sym), std::forward<decltype(init)>(init), std::forward<decltype(prefix)>(prefix), std::forward<decltype(output_file)>(output_file));
}

void FirMemOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<FirMemOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

FirMemOp FirMemOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<FirMemOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

FirMemOp FirMemOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void FirMemOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

FirMemOp FirMemOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<FirMemOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

FirMemOp FirMemOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult FirMemOp::verifyInvariantsImpl() {
  auto tblgen_init = getProperties().init; (void)tblgen_init;
  auto tblgen_inner_sym = getProperties().inner_sym; (void)tblgen_inner_sym;
  auto tblgen_name = getProperties().name; (void)tblgen_name;
  auto tblgen_output_file = getProperties().output_file; (void)tblgen_output_file;
  auto tblgen_prefix = getProperties().prefix; (void)tblgen_prefix;
  auto tblgen_readLatency = getProperties().readLatency; (void)tblgen_readLatency;
  if (!tblgen_readLatency) return emitOpError("requires attribute 'readLatency'");
  auto tblgen_ruw = getProperties().ruw; (void)tblgen_ruw;
  if (!tblgen_ruw) return emitOpError("requires attribute 'ruw'");
  auto tblgen_writeLatency = getProperties().writeLatency; (void)tblgen_writeLatency;
  if (!tblgen_writeLatency) return emitOpError("requires attribute 'writeLatency'");
  auto tblgen_wuw = getProperties().wuw; (void)tblgen_wuw;
  if (!tblgen_wuw) return emitOpError("requires attribute 'wuw'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Seq7(*this, tblgen_readLatency, "readLatency")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Seq7(*this, tblgen_writeLatency, "writeLatency")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Seq8(*this, tblgen_ruw, "ruw")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Seq9(*this, tblgen_wuw, "wuw")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Seq3(*this, tblgen_name, "name")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Seq2(*this, tblgen_inner_sym, "inner_sym")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Seq10(*this, tblgen_init, "init")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Seq3(*this, tblgen_prefix, "prefix")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Seq11(*this, tblgen_output_file, "output_file")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Seq5(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult FirMemOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

void FirMemOp::getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context) {
  results.add(canonicalize);
}

::mlir::ParseResult FirMemOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::circt::hw::InnerSymAttr inner_symAttr;
  ::mlir::StringAttr nameAttr;
  ::mlir::IntegerAttr readLatencyAttr;
  ::mlir::IntegerAttr writeLatencyAttr;
  circt::seq::RUWAttr ruwAttr;
  circt::seq::WUWAttr wuwAttr;
  ::mlir::Type memoryRawType{};
  ::llvm::ArrayRef<::mlir::Type> memoryTypes(&memoryRawType, 1);
  if (::mlir::succeeded(parser.parseOptionalKeyword("sym"))) {

  if (parser.parseCustomAttributeWithFallback(inner_symAttr, ::mlir::Type{})) {
    return ::mlir::failure();
  }
  if (inner_symAttr) result.getOrAddProperties<FirMemOp::Properties>().inner_sym = inner_symAttr;
  }
  {
    auto odsResult = parseImplicitSSAName(parser, nameAttr);
    if (odsResult) return ::mlir::failure();
    if (nameAttr)
      result.getOrAddProperties<FirMemOp::Properties>().name = nameAttr;
  }

  if (parser.parseCustomAttributeWithFallback(readLatencyAttr, parser.getBuilder().getIntegerType(32))) {
    return ::mlir::failure();
  }
  if (readLatencyAttr) result.getOrAddProperties<FirMemOp::Properties>().readLatency = readLatencyAttr;
  if (parser.parseComma())
    return ::mlir::failure();

  if (parser.parseCustomAttributeWithFallback(writeLatencyAttr, parser.getBuilder().getIntegerType(32))) {
    return ::mlir::failure();
  }
  if (writeLatencyAttr) result.getOrAddProperties<FirMemOp::Properties>().writeLatency = writeLatencyAttr;
  if (parser.parseComma())
    return ::mlir::failure();

  {
    ::llvm::StringRef attrStr;
    ::mlir::NamedAttrList attrStorage;
    auto loc = parser.getCurrentLocation();
    if (parser.parseOptionalKeyword(&attrStr, {"undefined","old","new"})) {
      ::mlir::StringAttr attrVal;
      ::mlir::OptionalParseResult parseResult =
        parser.parseOptionalAttribute(attrVal,
                                      parser.getBuilder().getNoneType(),
                                      "ruw", attrStorage);
      if (parseResult.has_value()) {
        if (failed(*parseResult))
          return ::mlir::failure();
        attrStr = attrVal.getValue();
      } else {
        return parser.emitError(loc, "expected string or keyword containing one of the following enum values for attribute 'ruw' [undefined, old, new]");
      }
    }
    if (!attrStr.empty()) {
      auto attrOptional = circt::seq::symbolizeRUW(attrStr);
      if (!attrOptional)
        return parser.emitError(loc, "invalid ")
               << "ruw attribute specification: \"" << attrStr << '"';;

      ruwAttr = circt::seq::RUWAttr::get(parser.getBuilder().getContext(), *attrOptional);
        result.getOrAddProperties<FirMemOp::Properties>().ruw = ruwAttr;
    }
  }
  if (parser.parseComma())
    return ::mlir::failure();

  {
    ::llvm::StringRef attrStr;
    ::mlir::NamedAttrList attrStorage;
    auto loc = parser.getCurrentLocation();
    if (parser.parseOptionalKeyword(&attrStr, {"undefined","port_order"})) {
      ::mlir::StringAttr attrVal;
      ::mlir::OptionalParseResult parseResult =
        parser.parseOptionalAttribute(attrVal,
                                      parser.getBuilder().getNoneType(),
                                      "wuw", attrStorage);
      if (parseResult.has_value()) {
        if (failed(*parseResult))
          return ::mlir::failure();
        attrStr = attrVal.getValue();
      } else {
        return parser.emitError(loc, "expected string or keyword containing one of the following enum values for attribute 'wuw' [undefined, port_order]");
      }
    }
    if (!attrStr.empty()) {
      auto attrOptional = circt::seq::symbolizeWUW(attrStr);
      if (!attrOptional)
        return parser.emitError(loc, "invalid ")
               << "wuw attribute specification: \"" << attrStr << '"';;

      wuwAttr = circt::seq::WUWAttr::get(parser.getBuilder().getContext(), *attrOptional);
        result.getOrAddProperties<FirMemOp::Properties>().wuw = wuwAttr;
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
    ::circt::seq::FirMemType type;
    if (parser.parseCustomTypeWithFallback(type))
      return ::mlir::failure();
    memoryRawType = type;
  }
  result.addTypes(memoryTypes);
  return ::mlir::success();
}

void FirMemOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  if (getInnerSymAttr()) {
    _odsPrinter << ' ' << "sym";
    _odsPrinter << ' ';
  _odsPrinter.printStrippedAttrOrType(getInnerSymAttr());
  }
  printImplicitSSAName(_odsPrinter, *this, getNameAttr());
  _odsPrinter << ' ';
  _odsPrinter.printAttributeWithoutType(getReadLatencyAttr());
  _odsPrinter << ",";
  _odsPrinter << ' ';
  _odsPrinter.printAttributeWithoutType(getWriteLatencyAttr());
  _odsPrinter << ",";
  _odsPrinter << ' ';

  {
    auto caseValue = getRuw();
    auto caseValueStr = stringifyRUW(caseValue);
    _odsPrinter << caseValueStr;
  }
  _odsPrinter << ",";
  _odsPrinter << ' ';

  {
    auto caseValue = getWuw();
    auto caseValueStr = stringifyWUW(caseValue);
    _odsPrinter << caseValueStr;
  }
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("inner_sym");
  elidedAttrs.push_back("name");
  elidedAttrs.push_back("readLatency");
  elidedAttrs.push_back("writeLatency");
  elidedAttrs.push_back("ruw");
  elidedAttrs.push_back("wuw");
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
  {
    auto type = getMemory().getType();
    if (auto validType = ::llvm::dyn_cast<::circt::seq::FirMemType>(type))
      _odsPrinter.printStrippedAttrOrType(validType);
   else
     _odsPrinter << type;
  }
}

void FirMemOp::getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects) {
  effects.emplace_back(::mlir::MemoryEffects::Allocate::get(), 0, false, ::mlir::SideEffects::DefaultResource::get());
}


} // namespace circt::seq
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::seq::FirMemOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::seq::detail::FirMemOpGenericAdaptorBase::Properties)

namespace circt::seq {


//===----------------------------------------------------------------------===//
// ::circt::seq::FirMemReadOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

FirMemReadOpGenericAdaptorBase::FirMemReadOpGenericAdaptorBase(FirMemReadOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

std::pair<unsigned, unsigned> FirMemReadOpGenericAdaptorBase::getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
  bool isVariadic[] = {false, false, false, true};
  int prevVariadicCount = 0;
  for (unsigned i = 0; i < index; ++i)
    if (isVariadic[i]) ++prevVariadicCount;

  // Calculate how many dynamic values a static variadic operand corresponds to.
  // This assumes all static variadic operands have the same dynamic value count.
  int variadicSize = (odsOperandsSize - 3) / 1;
  // `index` passed in as the parameter is the static index which counts each
  // operand (variadic or not) as size 1. So here for each previous static variadic
  // operand, we need to offset by (variadicSize - 1) to get where the dynamic
  // value pack for this static operand starts.
  int start = index + (variadicSize - 1) * prevVariadicCount;
  int size = isVariadic[index] ? variadicSize : 1;
  return {start, size};
}


} // namespace detail
FirMemReadOpAdaptor::FirMemReadOpAdaptor(FirMemReadOp op) : FirMemReadOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult FirMemReadOpAdaptor::verify(::mlir::Location loc) {
  return ::mlir::success();
}

std::pair<unsigned, unsigned> FirMemReadOp::getODSOperandIndexAndLength(unsigned index) {
  bool isVariadic[] = {false, false, false, true};
  int prevVariadicCount = 0;
  for (unsigned i = 0; i < index; ++i)
    if (isVariadic[i]) ++prevVariadicCount;

  // Calculate how many dynamic values a static variadic operand corresponds to.
  // This assumes all static variadic operands have the same dynamic value count.
  int variadicSize = (getOperation()->getNumOperands() - 3) / 1;
  // `index` passed in as the parameter is the static index which counts each
  // operand (variadic or not) as size 1. So here for each previous static variadic
  // operand, we need to offset by (variadicSize - 1) to get where the dynamic
  // value pack for this static operand starts.
  int start = index + (variadicSize - 1) * prevVariadicCount;
  int size = isVariadic[index] ? variadicSize : 1;
  return {start, size};
}

::mlir::MutableOperandRange FirMemReadOp::getEnableMutable() {
  auto range = getODSOperandIndexAndLength(3);
  auto mutableRange = ::mlir::MutableOperandRange(getOperation(), range.first, range.second);
  return mutableRange;
}

::llvm::LogicalResult FirMemReadOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }
      return ::mlir::success();
}

::mlir::Attribute FirMemReadOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code FirMemReadOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine();
}

std::optional<mlir::Attribute> FirMemReadOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
  return std::nullopt;
}

void FirMemReadOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
}

void FirMemReadOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
}

::llvm::LogicalResult FirMemReadOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    return ::mlir::success();
}

void FirMemReadOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type data, ::mlir::Value memory, ::mlir::Value address, ::mlir::Value clk, /*optional*/::mlir::Value enable) {
  odsState.addOperands(memory);
  odsState.addOperands(address);
  odsState.addOperands(clk);
  if (enable)
    odsState.addOperands(enable);
  odsState.addTypes(data);
}

FirMemReadOp FirMemReadOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type data, ::mlir::Value memory, ::mlir::Value address, ::mlir::Value clk, /*optional*/::mlir::Value enable) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(data)>(data), std::forward<decltype(memory)>(memory), std::forward<decltype(address)>(address), std::forward<decltype(clk)>(clk), std::forward<decltype(enable)>(enable));
  auto __res__ = ::llvm::dyn_cast<FirMemReadOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

FirMemReadOp FirMemReadOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type data, ::mlir::Value memory, ::mlir::Value address, ::mlir::Value clk, /*optional*/::mlir::Value enable) {
  return create(builder, builder.getLoc(), std::forward<decltype(data)>(data), std::forward<decltype(memory)>(memory), std::forward<decltype(address)>(address), std::forward<decltype(clk)>(clk), std::forward<decltype(enable)>(enable));
}

void FirMemReadOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value memory, ::mlir::Value address, ::mlir::Value clk, /*optional*/::mlir::Value enable) {
  odsState.addOperands(memory);
  odsState.addOperands(address);
  odsState.addOperands(clk);
  if (enable)
    odsState.addOperands(enable);

        ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
        if (::mlir::succeeded(FirMemReadOp::inferReturnTypes(odsBuilder.getContext(),
                      odsState.location, odsState.operands,
                      odsState.attributes.getDictionary(odsState.getContext()),
                      odsState.getRawProperties(),
                      odsState.regions, inferredReturnTypes)))
          odsState.addTypes(inferredReturnTypes);
        else
          ::mlir::detail::reportFatalInferReturnTypesError(odsState);
        
}

FirMemReadOp FirMemReadOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value memory, ::mlir::Value address, ::mlir::Value clk, /*optional*/::mlir::Value enable) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(memory)>(memory), std::forward<decltype(address)>(address), std::forward<decltype(clk)>(clk), std::forward<decltype(enable)>(enable));
  auto __res__ = ::llvm::dyn_cast<FirMemReadOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

FirMemReadOp FirMemReadOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value memory, ::mlir::Value address, ::mlir::Value clk, /*optional*/::mlir::Value enable) {
  return create(builder, builder.getLoc(), std::forward<decltype(memory)>(memory), std::forward<decltype(address)>(address), std::forward<decltype(clk)>(clk), std::forward<decltype(enable)>(enable));
}

void FirMemReadOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value memory, ::mlir::Value address, ::mlir::Value clk, /*optional*/::mlir::Value enable) {
  odsState.addOperands(memory);
  odsState.addOperands(address);
  odsState.addOperands(clk);
  if (enable)
    odsState.addOperands(enable);
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

FirMemReadOp FirMemReadOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value memory, ::mlir::Value address, ::mlir::Value clk, /*optional*/::mlir::Value enable) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(memory)>(memory), std::forward<decltype(address)>(address), std::forward<decltype(clk)>(clk), std::forward<decltype(enable)>(enable));
  auto __res__ = ::llvm::dyn_cast<FirMemReadOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

FirMemReadOp FirMemReadOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value memory, ::mlir::Value address, ::mlir::Value clk, /*optional*/::mlir::Value enable) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(memory)>(memory), std::forward<decltype(address)>(address), std::forward<decltype(clk)>(clk), std::forward<decltype(enable)>(enable));
}

void FirMemReadOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() >= 3u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

FirMemReadOp FirMemReadOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<FirMemReadOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

FirMemReadOp FirMemReadOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void FirMemReadOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() >= 3u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);

  ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
  if (::mlir::succeeded(FirMemReadOp::inferReturnTypes(odsBuilder.getContext(),
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

FirMemReadOp FirMemReadOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<FirMemReadOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

FirMemReadOp FirMemReadOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void FirMemReadOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() >= 3u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

FirMemReadOp FirMemReadOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<FirMemReadOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

FirMemReadOp FirMemReadOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

void FirMemReadOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() >= 3u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties &>(properties));
  odsState.addAttributes(discardableAttributes);

  ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
  if (::mlir::succeeded(FirMemReadOp::inferReturnTypes(odsBuilder.getContext(),
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

FirMemReadOp FirMemReadOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<FirMemReadOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

FirMemReadOp FirMemReadOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult FirMemReadOp::verifyInvariantsImpl() {
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Seq5(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSOperands(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Seq6(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup2 = getODSOperands(2);

    for (auto v : valueGroup2) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Seq1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup3 = getODSOperands(3);

    if (valueGroup3.size() > 1) {
      return emitOpError("operand group starting at #") << index
          << " requires 0 or 1 element, but found " << valueGroup3.size();
    }

    for (auto v : valueGroup3) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Seq2(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Seq6(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  if (!((std::equal_to<>()(
      IntegerType::get(
        (*this->getODSOperands(0).begin()).getType().getContext(),
        std::max(1U, llvm::Log2_64_Ceil(cast<FirMemType>((*this->getODSOperands(0).begin()).getType()).getDepth())))
    , (*this->getODSOperands(1).begin()).getType()))))
    return emitOpError("failed to verify that address type should match clog2 of memory depth");
  if (!((std::equal_to<>()(
      IntegerType::get(
        (*this->getODSOperands(0).begin()).getType().getContext(),
        std::max(1U, cast<FirMemType>((*this->getODSOperands(0).begin()).getType()).getWidth()))
    , (*this->getODSResults(0).begin()).getType()))))
    return emitOpError("failed to verify that data type should match memory width");
  return ::mlir::success();
}

::llvm::LogicalResult FirMemReadOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

void FirMemReadOp::getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context) {
  results.add(canonicalize);
}

::llvm::LogicalResult FirMemReadOp::inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::PropertyRef properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes) {
  inferredReturnTypes.resize(1);
  ::mlir::Builder odsBuilder(context);
  if (operands.size() <= 0)
    return ::mlir::failure();
  ::mlir::Type odsInferredType0 = 
      IntegerType::get(
        operands[0].getType().getContext(),
        std::max(1U, cast<FirMemType>(operands[0].getType()).getWidth()))
    ;
  inferredReturnTypes[0] = odsInferredType0;
  return ::mlir::success();
}

::mlir::ParseResult FirMemReadOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::OpAsmParser::UnresolvedOperand memoryRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> memoryOperands(&memoryRawOperand, 1);  ::llvm::SMLoc memoryOperandsLoc;
  (void)memoryOperandsLoc;
  ::mlir::OpAsmParser::UnresolvedOperand addressRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> addressOperands(&addressRawOperand, 1);  ::llvm::SMLoc addressOperandsLoc;
  (void)addressOperandsLoc;
  ::mlir::OpAsmParser::UnresolvedOperand clkRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> clkOperands(&clkRawOperand, 1);  ::llvm::SMLoc clkOperandsLoc;
  (void)clkOperandsLoc;
  ::llvm::SmallVector<::mlir::OpAsmParser::UnresolvedOperand, 4> enableOperands;
  ::llvm::SMLoc enableOperandsLoc;
  (void)enableOperandsLoc;
  ::mlir::Type memoryRawType{};
  ::llvm::ArrayRef<::mlir::Type> memoryTypes(&memoryRawType, 1);

  memoryOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(memoryRawOperand))
    return ::mlir::failure();
  if (parser.parseLSquare())
    return ::mlir::failure();

  addressOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(addressRawOperand))
    return ::mlir::failure();
  if (parser.parseRSquare())
    return ::mlir::failure();
  if (parser.parseComma())
    return ::mlir::failure();
  if (parser.parseKeyword("clock"))
    return ::mlir::failure();

  clkOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(clkRawOperand))
    return ::mlir::failure();
  if (::mlir::succeeded(parser.parseOptionalKeyword("enable"))) {

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
    ::circt::seq::FirMemType type;
    if (parser.parseCustomTypeWithFallback(type))
      return ::mlir::failure();
    memoryRawType = type;
  }
  for (::mlir::Type type : memoryTypes) {
    (void)type;
    if (!((::llvm::isa<::circt::seq::FirMemType>(type)))) {
      return parser.emitError(parser.getNameLoc()) << "'memory' must be A FIRRTL-flavored memory, but got " << type;
    }
  }
  ::mlir::Type odsBuildableType0 = parser.getBuilder().getType<::circt::seq::ClockType>();
  ::mlir::Type odsBuildableType1 = parser.getBuilder().getIntegerType(1);
  result.addTypes(
      IntegerType::get(
        memoryTypes[0].getContext(),
        std::max(1U, cast<FirMemType>(memoryTypes[0]).getWidth()))
    );
  if (parser.resolveOperands(memoryOperands, memoryTypes, memoryOperandsLoc, result.operands))
    return ::mlir::failure();
  if (parser.resolveOperands(addressOperands, 
      IntegerType::get(
        memoryTypes[0].getContext(),
        std::max(1U, llvm::Log2_64_Ceil(cast<FirMemType>(memoryTypes[0]).getDepth())))
    , addressOperandsLoc, result.operands))
    return ::mlir::failure();
  if (parser.resolveOperands(clkOperands, odsBuildableType0, clkOperandsLoc, result.operands))
    return ::mlir::failure();
  if (!enableOperands.empty()) {
  if (parser.resolveOperands(enableOperands, odsBuildableType1, enableOperandsLoc, result.operands))
    return ::mlir::failure();
  }
  return ::mlir::success();
}

void FirMemReadOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter << getMemory();
  _odsPrinter << "[";
  _odsPrinter << getAddress();
  _odsPrinter << "]";
  _odsPrinter << ",";
  _odsPrinter << ' ' << "clock";
  _odsPrinter << ' ';
  _odsPrinter << getClk();
  if (getEnable()) {
    _odsPrinter << ' ' << "enable";
    _odsPrinter << ' ';
    if (::mlir::Value value = getEnable())
      _odsPrinter << value;
  }
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
  {
    auto type = getMemory().getType();
    if (auto validType = ::llvm::dyn_cast<::circt::seq::FirMemType>(type))
      _odsPrinter.printStrippedAttrOrType(validType);
   else
     _odsPrinter << type;
  }
}

void FirMemReadOp::getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects) {
  effects.emplace_back(::mlir::MemoryEffects::Read::get(), 0, false, ::mlir::SideEffects::DefaultResource::get());
}


} // namespace circt::seq
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::seq::FirMemReadOp)

namespace circt::seq {


//===----------------------------------------------------------------------===//
// ::circt::seq::FirMemReadWriteOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

FirMemReadWriteOpGenericAdaptorBase::FirMemReadWriteOpGenericAdaptorBase(FirMemReadWriteOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

std::pair<unsigned, unsigned> FirMemReadWriteOpGenericAdaptorBase::getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
  ::llvm::ArrayRef<int32_t> sizeAttr = getProperties().operandSegmentSizes;

  unsigned start = 0;
  for (unsigned i = 0; i < index; ++i)
    start += sizeAttr[i];
  return {start, sizeAttr[index]};
}


} // namespace detail
FirMemReadWriteOpAdaptor::FirMemReadWriteOpAdaptor(FirMemReadWriteOp op) : FirMemReadWriteOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult FirMemReadWriteOpAdaptor::verify(::mlir::Location loc) {
  return ::mlir::success();
}

std::pair<unsigned, unsigned> FirMemReadWriteOp::getODSOperandIndexAndLength(unsigned index) {
  ::llvm::ArrayRef<int32_t> sizeAttr = getProperties().operandSegmentSizes;

  unsigned start = 0;
  for (unsigned i = 0; i < index; ++i)
    start += sizeAttr[i];
  return {start, sizeAttr[index]};
}

::mlir::MutableOperandRange FirMemReadWriteOp::getEnableMutable() {
  auto range = getODSOperandIndexAndLength(3);
  auto mutableRange = ::mlir::MutableOperandRange(getOperation(), range.first, range.second, ::mlir::MutableOperandRange::OperandSegment(3u, {getOperandSegmentSizesAttrName(), ::mlir::DenseI32ArrayAttr::get(getContext(), getProperties().operandSegmentSizes)}));
  return mutableRange;
}

::mlir::MutableOperandRange FirMemReadWriteOp::getMaskMutable() {
  auto range = getODSOperandIndexAndLength(6);
  auto mutableRange = ::mlir::MutableOperandRange(getOperation(), range.first, range.second, ::mlir::MutableOperandRange::OperandSegment(6u, {getOperandSegmentSizesAttrName(), ::mlir::DenseI32ArrayAttr::get(getContext(), getProperties().operandSegmentSizes)}));
  return mutableRange;
}

::llvm::LogicalResult FirMemReadWriteOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
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

::mlir::Attribute FirMemReadWriteOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

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

llvm::hash_code FirMemReadWriteOp::computePropertiesHash(const Properties &prop) {
  auto hash_operandSegmentSizes_ = [] (const auto &propStorage) -> llvm::hash_code {
    using ::llvm::hash_value;
    return ::llvm::hash_combine_range(std::begin(propStorage), std::end(propStorage));;
  };
  using llvm::hash_value;
  return llvm::hash_combine(
    hash_operandSegmentSizes_(prop.operandSegmentSizes));
}

std::optional<mlir::Attribute> FirMemReadWriteOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "operand_segment_sizes" || name == "operandSegmentSizes") return [&]() -> ::mlir::Attribute { return ::mlir::DenseI32ArrayAttr::get(ctx, prop.operandSegmentSizes); }();
  return std::nullopt;
}

void FirMemReadWriteOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
        if (name == "operand_segment_sizes" || name == "operandSegmentSizes") {
       auto arrAttr = ::llvm::dyn_cast_or_null<::mlir::DenseI32ArrayAttr>(value);
       if (!arrAttr) return;
       if (arrAttr.size() != sizeof(prop.operandSegmentSizes) / sizeof(int32_t))
         return;
       llvm::copy(arrAttr.asArrayRef(), prop.operandSegmentSizes.begin());
       return;
    }
}

void FirMemReadWriteOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
  attrs.append("operandSegmentSizes", [&]() -> ::mlir::Attribute { return ::mlir::DenseI32ArrayAttr::get(ctx, prop.operandSegmentSizes); }());
}

::llvm::LogicalResult FirMemReadWriteOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    return ::mlir::success();
}

::llvm::LogicalResult FirMemReadWriteOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
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

void FirMemReadWriteOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;

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

void FirMemReadWriteOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type readData, ::mlir::Value memory, ::mlir::Value address, ::mlir::Value clk, /*optional*/::mlir::Value enable, ::mlir::Value writeData, ::mlir::Value mode, /*optional*/::mlir::Value mask) {
  odsState.addOperands(memory);
  odsState.addOperands(address);
  odsState.addOperands(clk);
  if (enable)
    odsState.addOperands(enable);
  odsState.addOperands(writeData);
  odsState.addOperands(mode);
  if (mask)
    odsState.addOperands(mask);
  ::llvm::copy(::llvm::ArrayRef<int32_t>({1, 1, 1, (enable ? 1 : 0), 1, 1, (mask ? 1 : 0)}), odsState.getOrAddProperties<Properties>().operandSegmentSizes.begin());
  odsState.addTypes(readData);
}

FirMemReadWriteOp FirMemReadWriteOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type readData, ::mlir::Value memory, ::mlir::Value address, ::mlir::Value clk, /*optional*/::mlir::Value enable, ::mlir::Value writeData, ::mlir::Value mode, /*optional*/::mlir::Value mask) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(readData)>(readData), std::forward<decltype(memory)>(memory), std::forward<decltype(address)>(address), std::forward<decltype(clk)>(clk), std::forward<decltype(enable)>(enable), std::forward<decltype(writeData)>(writeData), std::forward<decltype(mode)>(mode), std::forward<decltype(mask)>(mask));
  auto __res__ = ::llvm::dyn_cast<FirMemReadWriteOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

FirMemReadWriteOp FirMemReadWriteOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type readData, ::mlir::Value memory, ::mlir::Value address, ::mlir::Value clk, /*optional*/::mlir::Value enable, ::mlir::Value writeData, ::mlir::Value mode, /*optional*/::mlir::Value mask) {
  return create(builder, builder.getLoc(), std::forward<decltype(readData)>(readData), std::forward<decltype(memory)>(memory), std::forward<decltype(address)>(address), std::forward<decltype(clk)>(clk), std::forward<decltype(enable)>(enable), std::forward<decltype(writeData)>(writeData), std::forward<decltype(mode)>(mode), std::forward<decltype(mask)>(mask));
}

void FirMemReadWriteOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value memory, ::mlir::Value address, ::mlir::Value clk, /*optional*/::mlir::Value enable, ::mlir::Value writeData, ::mlir::Value mode, /*optional*/::mlir::Value mask) {
  odsState.addOperands(memory);
  odsState.addOperands(address);
  odsState.addOperands(clk);
  if (enable)
    odsState.addOperands(enable);
  odsState.addOperands(writeData);
  odsState.addOperands(mode);
  if (mask)
    odsState.addOperands(mask);
  ::llvm::copy(::llvm::ArrayRef<int32_t>({1, 1, 1, (enable ? 1 : 0), 1, 1, (mask ? 1 : 0)}), odsState.getOrAddProperties<Properties>().operandSegmentSizes.begin());

        ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
        if (::mlir::succeeded(FirMemReadWriteOp::inferReturnTypes(odsBuilder.getContext(),
                      odsState.location, odsState.operands,
                      odsState.attributes.getDictionary(odsState.getContext()),
                      odsState.getRawProperties(),
                      odsState.regions, inferredReturnTypes)))
          odsState.addTypes(inferredReturnTypes);
        else
          ::mlir::detail::reportFatalInferReturnTypesError(odsState);
        
}

FirMemReadWriteOp FirMemReadWriteOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value memory, ::mlir::Value address, ::mlir::Value clk, /*optional*/::mlir::Value enable, ::mlir::Value writeData, ::mlir::Value mode, /*optional*/::mlir::Value mask) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(memory)>(memory), std::forward<decltype(address)>(address), std::forward<decltype(clk)>(clk), std::forward<decltype(enable)>(enable), std::forward<decltype(writeData)>(writeData), std::forward<decltype(mode)>(mode), std::forward<decltype(mask)>(mask));
  auto __res__ = ::llvm::dyn_cast<FirMemReadWriteOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

FirMemReadWriteOp FirMemReadWriteOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value memory, ::mlir::Value address, ::mlir::Value clk, /*optional*/::mlir::Value enable, ::mlir::Value writeData, ::mlir::Value mode, /*optional*/::mlir::Value mask) {
  return create(builder, builder.getLoc(), std::forward<decltype(memory)>(memory), std::forward<decltype(address)>(address), std::forward<decltype(clk)>(clk), std::forward<decltype(enable)>(enable), std::forward<decltype(writeData)>(writeData), std::forward<decltype(mode)>(mode), std::forward<decltype(mask)>(mask));
}

void FirMemReadWriteOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value memory, ::mlir::Value address, ::mlir::Value clk, /*optional*/::mlir::Value enable, ::mlir::Value writeData, ::mlir::Value mode, /*optional*/::mlir::Value mask) {
  odsState.addOperands(memory);
  odsState.addOperands(address);
  odsState.addOperands(clk);
  if (enable)
    odsState.addOperands(enable);
  odsState.addOperands(writeData);
  odsState.addOperands(mode);
  if (mask)
    odsState.addOperands(mask);
  ::llvm::copy(::llvm::ArrayRef<int32_t>({1, 1, 1, (enable ? 1 : 0), 1, 1, (mask ? 1 : 0)}), odsState.getOrAddProperties<Properties>().operandSegmentSizes.begin());
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

FirMemReadWriteOp FirMemReadWriteOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value memory, ::mlir::Value address, ::mlir::Value clk, /*optional*/::mlir::Value enable, ::mlir::Value writeData, ::mlir::Value mode, /*optional*/::mlir::Value mask) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(memory)>(memory), std::forward<decltype(address)>(address), std::forward<decltype(clk)>(clk), std::forward<decltype(enable)>(enable), std::forward<decltype(writeData)>(writeData), std::forward<decltype(mode)>(mode), std::forward<decltype(mask)>(mask));
  auto __res__ = ::llvm::dyn_cast<FirMemReadWriteOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

FirMemReadWriteOp FirMemReadWriteOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value memory, ::mlir::Value address, ::mlir::Value clk, /*optional*/::mlir::Value enable, ::mlir::Value writeData, ::mlir::Value mode, /*optional*/::mlir::Value mask) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(memory)>(memory), std::forward<decltype(address)>(address), std::forward<decltype(clk)>(clk), std::forward<decltype(enable)>(enable), std::forward<decltype(writeData)>(writeData), std::forward<decltype(mode)>(mode), std::forward<decltype(mask)>(mask));
}

void FirMemReadWriteOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() >= 5u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<FirMemReadWriteOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

FirMemReadWriteOp FirMemReadWriteOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<FirMemReadWriteOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

FirMemReadWriteOp FirMemReadWriteOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void FirMemReadWriteOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() >= 5u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<FirMemReadWriteOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
  ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
  if (::mlir::succeeded(FirMemReadWriteOp::inferReturnTypes(odsBuilder.getContext(),
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

FirMemReadWriteOp FirMemReadWriteOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<FirMemReadWriteOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

FirMemReadWriteOp FirMemReadWriteOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void FirMemReadWriteOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() >= 5u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

FirMemReadWriteOp FirMemReadWriteOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<FirMemReadWriteOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

FirMemReadWriteOp FirMemReadWriteOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

void FirMemReadWriteOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() >= 5u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties &>(properties));
  odsState.addAttributes(discardableAttributes);

  ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
  if (::mlir::succeeded(FirMemReadWriteOp::inferReturnTypes(odsBuilder.getContext(),
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

FirMemReadWriteOp FirMemReadWriteOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<FirMemReadWriteOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

FirMemReadWriteOp FirMemReadWriteOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult FirMemReadWriteOp::verifyInvariantsImpl() {
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Seq5(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSOperands(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Seq6(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup2 = getODSOperands(2);

    for (auto v : valueGroup2) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Seq1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup3 = getODSOperands(3);

    if (valueGroup3.size() > 1) {
      return emitOpError("operand group starting at #") << index
          << " requires 0 or 1 element, but found " << valueGroup3.size();
    }

    for (auto v : valueGroup3) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Seq2(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup4 = getODSOperands(4);

    for (auto v : valueGroup4) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Seq6(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup5 = getODSOperands(5);

    for (auto v : valueGroup5) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Seq2(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup6 = getODSOperands(6);

    if (valueGroup6.size() > 1) {
      return emitOpError("operand group starting at #") << index
          << " requires 0 or 1 element, but found " << valueGroup6.size();
    }

    for (auto v : valueGroup6) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Seq6(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Seq6(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  if (!((std::equal_to<>()(
      IntegerType::get(
        (*this->getODSOperands(0).begin()).getType().getContext(),
        std::max(1U, llvm::Log2_64_Ceil(cast<FirMemType>((*this->getODSOperands(0).begin()).getType()).getDepth())))
    , (*this->getODSOperands(1).begin()).getType()))))
    return emitOpError("failed to verify that address type should match clog2 of memory depth");
  if (!((std::equal_to<>()(
      IntegerType::get(
        (*this->getODSOperands(0).begin()).getType().getContext(),
        std::max(1U, cast<FirMemType>((*this->getODSOperands(0).begin()).getType()).getWidth()))
    , (*this->getODSOperands(4).begin()).getType()))))
    return emitOpError("failed to verify that data type should match memory width");
  if (!((std::equal_to<>()(
      IntegerType::get(
        (*this->getODSOperands(0).begin()).getType().getContext(),
        std::max(1U, cast<FirMemType>((*this->getODSOperands(0).begin()).getType()).getWidth()))
    , (*this->getODSResults(0).begin()).getType()))))
    return emitOpError("failed to verify that data type should match memory width");
  return ::mlir::success();
}

::llvm::LogicalResult FirMemReadWriteOp::verifyInvariants() {
  if(::mlir::succeeded(verifyInvariantsImpl()) && ::mlir::succeeded(verify()))
    return ::mlir::success();
  return ::mlir::failure();
}

void FirMemReadWriteOp::getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context) {
  results.add(canonicalize);
}

::llvm::LogicalResult FirMemReadWriteOp::inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::PropertyRef properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes) {
  inferredReturnTypes.resize(1);
  ::mlir::Builder odsBuilder(context);
  if (operands.size() <= 0)
    return ::mlir::failure();
  ::mlir::Type odsInferredType0 = 
      IntegerType::get(
        operands[0].getType().getContext(),
        std::max(1U, cast<FirMemType>(operands[0].getType()).getWidth()))
    ;
  inferredReturnTypes[0] = odsInferredType0;
  return ::mlir::success();
}

::mlir::ParseResult FirMemReadWriteOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::OpAsmParser::UnresolvedOperand memoryRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> memoryOperands(&memoryRawOperand, 1);  ::llvm::SMLoc memoryOperandsLoc;
  (void)memoryOperandsLoc;
  ::mlir::OpAsmParser::UnresolvedOperand addressRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> addressOperands(&addressRawOperand, 1);  ::llvm::SMLoc addressOperandsLoc;
  (void)addressOperandsLoc;
  ::mlir::OpAsmParser::UnresolvedOperand writeDataRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> writeDataOperands(&writeDataRawOperand, 1);  ::llvm::SMLoc writeDataOperandsLoc;
  (void)writeDataOperandsLoc;
  ::mlir::OpAsmParser::UnresolvedOperand modeRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> modeOperands(&modeRawOperand, 1);  ::llvm::SMLoc modeOperandsLoc;
  (void)modeOperandsLoc;
  ::mlir::OpAsmParser::UnresolvedOperand clkRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> clkOperands(&clkRawOperand, 1);  ::llvm::SMLoc clkOperandsLoc;
  (void)clkOperandsLoc;
  ::llvm::SmallVector<::mlir::OpAsmParser::UnresolvedOperand, 4> enableOperands;
  ::llvm::SMLoc enableOperandsLoc;
  (void)enableOperandsLoc;
  ::llvm::SmallVector<::mlir::OpAsmParser::UnresolvedOperand, 4> maskOperands;
  ::llvm::SMLoc maskOperandsLoc;
  (void)maskOperandsLoc;
  ::mlir::Type memoryRawType{};
  ::llvm::ArrayRef<::mlir::Type> memoryTypes(&memoryRawType, 1);
  ::llvm::SmallVector<::mlir::Type, 1> maskTypes;

  memoryOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(memoryRawOperand))
    return ::mlir::failure();
  if (parser.parseLSquare())
    return ::mlir::failure();

  addressOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(addressRawOperand))
    return ::mlir::failure();
  if (parser.parseRSquare())
    return ::mlir::failure();
  if (parser.parseEqual())
    return ::mlir::failure();

  writeDataOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(writeDataRawOperand))
    return ::mlir::failure();
  if (parser.parseKeyword("if"))
    return ::mlir::failure();

  modeOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(modeRawOperand))
    return ::mlir::failure();
  if (parser.parseComma())
    return ::mlir::failure();
  if (parser.parseKeyword("clock"))
    return ::mlir::failure();

  clkOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(clkRawOperand))
    return ::mlir::failure();
  if (::mlir::succeeded(parser.parseOptionalKeyword("enable"))) {

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
  if (::mlir::succeeded(parser.parseOptionalKeyword("mask"))) {

  {
    maskOperandsLoc = parser.getCurrentLocation();
    ::mlir::OpAsmParser::UnresolvedOperand operand;
    ::mlir::OptionalParseResult parseResult =
                                    parser.parseOptionalOperand(operand);
    if (parseResult.has_value()) {
      if (failed(*parseResult))
        return ::mlir::failure();
      maskOperands.push_back(operand);
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
    ::circt::seq::FirMemType type;
    if (parser.parseCustomTypeWithFallback(type))
      return ::mlir::failure();
    memoryRawType = type;
  }
  if (::mlir::succeeded(parser.parseOptionalComma())) {

  {
    ::mlir::Type optionalType;
    ::mlir::OptionalParseResult parseResult =
                                    parser.parseOptionalType(optionalType);
    if (parseResult.has_value()) {
      if (failed(*parseResult))
        return ::mlir::failure();
      maskTypes.push_back(optionalType);
    }
  }
  }
::llvm::copy(::llvm::ArrayRef<int32_t>({1, 1, 1, static_cast<int32_t>(enableOperands.size()), 1, 1, static_cast<int32_t>(maskOperands.size())}), result.getOrAddProperties<FirMemReadWriteOp::Properties>().operandSegmentSizes.begin());
  for (::mlir::Type type : memoryTypes) {
    (void)type;
    if (!((::llvm::isa<::circt::seq::FirMemType>(type)))) {
      return parser.emitError(parser.getNameLoc()) << "'memory' must be A FIRRTL-flavored memory, but got " << type;
    }
  }
  ::mlir::Type odsBuildableType0 = parser.getBuilder().getType<::circt::seq::ClockType>();
  ::mlir::Type odsBuildableType1 = parser.getBuilder().getIntegerType(1);
  result.addTypes(
      IntegerType::get(
        memoryTypes[0].getContext(),
        std::max(1U, cast<FirMemType>(memoryTypes[0]).getWidth()))
    );
  if (parser.resolveOperands(memoryOperands, memoryTypes, memoryOperandsLoc, result.operands))
    return ::mlir::failure();
  if (parser.resolveOperands(addressOperands, 
      IntegerType::get(
        memoryTypes[0].getContext(),
        std::max(1U, llvm::Log2_64_Ceil(cast<FirMemType>(memoryTypes[0]).getDepth())))
    , addressOperandsLoc, result.operands))
    return ::mlir::failure();
  if (parser.resolveOperands(clkOperands, odsBuildableType0, clkOperandsLoc, result.operands))
    return ::mlir::failure();
  if (!enableOperands.empty()) {
  if (parser.resolveOperands(enableOperands, odsBuildableType1, enableOperandsLoc, result.operands))
    return ::mlir::failure();
  }
  if (parser.resolveOperands(writeDataOperands, 
      IntegerType::get(
        memoryTypes[0].getContext(),
        std::max(1U, cast<FirMemType>(memoryTypes[0]).getWidth()))
    , writeDataOperandsLoc, result.operands))
    return ::mlir::failure();
  if (parser.resolveOperands(modeOperands, odsBuildableType1, modeOperandsLoc, result.operands))
    return ::mlir::failure();
  if (!maskOperands.empty()) {
  if (parser.resolveOperands(maskOperands, maskTypes, maskOperandsLoc, result.operands))
    return ::mlir::failure();
  }
  return ::mlir::success();
}

void FirMemReadWriteOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter << getMemory();
  _odsPrinter << "[";
  _odsPrinter << getAddress();
  _odsPrinter << "]";
  _odsPrinter << ' ' << "=";
  _odsPrinter << ' ';
  _odsPrinter << getWriteData();
  _odsPrinter << ' ' << "if";
  _odsPrinter << ' ';
  _odsPrinter << getMode();
  _odsPrinter << ",";
  _odsPrinter << ' ' << "clock";
  _odsPrinter << ' ';
  _odsPrinter << getClk();
  if (getEnable()) {
    _odsPrinter << ' ' << "enable";
    _odsPrinter << ' ';
    if (::mlir::Value value = getEnable())
      _odsPrinter << value;
  }
  if (getMask()) {
    _odsPrinter << ' ' << "mask";
    _odsPrinter << ' ';
    if (::mlir::Value value = getMask())
      _odsPrinter << value;
  }
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("operandSegmentSizes");
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
  {
    auto type = getMemory().getType();
    if (auto validType = ::llvm::dyn_cast<::circt::seq::FirMemType>(type))
      _odsPrinter.printStrippedAttrOrType(validType);
   else
     _odsPrinter << type;
  }
  if (getMask()) {
    _odsPrinter << ",";
    _odsPrinter << ' ';
    _odsPrinter << (getMask() ? ::llvm::ArrayRef<::mlir::Type>(getMask().getType()) : ::llvm::ArrayRef<::mlir::Type>());
  }
}

void FirMemReadWriteOp::getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects) {
  effects.emplace_back(::mlir::MemoryEffects::Read::get(), 0, false, ::mlir::SideEffects::DefaultResource::get());
  effects.emplace_back(::mlir::MemoryEffects::Write::get(), 0, false, ::mlir::SideEffects::DefaultResource::get());
}


} // namespace circt::seq
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::seq::FirMemReadWriteOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::seq::detail::FirMemReadWriteOpGenericAdaptorBase::Properties)

namespace circt::seq {


//===----------------------------------------------------------------------===//
// ::circt::seq::FirMemWriteOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

FirMemWriteOpGenericAdaptorBase::FirMemWriteOpGenericAdaptorBase(FirMemWriteOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

std::pair<unsigned, unsigned> FirMemWriteOpGenericAdaptorBase::getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
  ::llvm::ArrayRef<int32_t> sizeAttr = getProperties().operandSegmentSizes;

  unsigned start = 0;
  for (unsigned i = 0; i < index; ++i)
    start += sizeAttr[i];
  return {start, sizeAttr[index]};
}


} // namespace detail
FirMemWriteOpAdaptor::FirMemWriteOpAdaptor(FirMemWriteOp op) : FirMemWriteOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult FirMemWriteOpAdaptor::verify(::mlir::Location loc) {
  return ::mlir::success();
}

std::pair<unsigned, unsigned> FirMemWriteOp::getODSOperandIndexAndLength(unsigned index) {
  ::llvm::ArrayRef<int32_t> sizeAttr = getProperties().operandSegmentSizes;

  unsigned start = 0;
  for (unsigned i = 0; i < index; ++i)
    start += sizeAttr[i];
  return {start, sizeAttr[index]};
}

::mlir::MutableOperandRange FirMemWriteOp::getEnableMutable() {
  auto range = getODSOperandIndexAndLength(3);
  auto mutableRange = ::mlir::MutableOperandRange(getOperation(), range.first, range.second, ::mlir::MutableOperandRange::OperandSegment(3u, {getOperandSegmentSizesAttrName(), ::mlir::DenseI32ArrayAttr::get(getContext(), getProperties().operandSegmentSizes)}));
  return mutableRange;
}

::mlir::MutableOperandRange FirMemWriteOp::getMaskMutable() {
  auto range = getODSOperandIndexAndLength(5);
  auto mutableRange = ::mlir::MutableOperandRange(getOperation(), range.first, range.second, ::mlir::MutableOperandRange::OperandSegment(5u, {getOperandSegmentSizesAttrName(), ::mlir::DenseI32ArrayAttr::get(getContext(), getProperties().operandSegmentSizes)}));
  return mutableRange;
}

::llvm::LogicalResult FirMemWriteOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
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

::mlir::Attribute FirMemWriteOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

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

llvm::hash_code FirMemWriteOp::computePropertiesHash(const Properties &prop) {
  auto hash_operandSegmentSizes_ = [] (const auto &propStorage) -> llvm::hash_code {
    using ::llvm::hash_value;
    return ::llvm::hash_combine_range(std::begin(propStorage), std::end(propStorage));;
  };
  using llvm::hash_value;
  return llvm::hash_combine(
    hash_operandSegmentSizes_(prop.operandSegmentSizes));
}

std::optional<mlir::Attribute> FirMemWriteOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "operand_segment_sizes" || name == "operandSegmentSizes") return [&]() -> ::mlir::Attribute { return ::mlir::DenseI32ArrayAttr::get(ctx, prop.operandSegmentSizes); }();
  return std::nullopt;
}

void FirMemWriteOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
        if (name == "operand_segment_sizes" || name == "operandSegmentSizes") {
       auto arrAttr = ::llvm::dyn_cast_or_null<::mlir::DenseI32ArrayAttr>(value);
       if (!arrAttr) return;
       if (arrAttr.size() != sizeof(prop.operandSegmentSizes) / sizeof(int32_t))
         return;
       llvm::copy(arrAttr.asArrayRef(), prop.operandSegmentSizes.begin());
       return;
    }
}

void FirMemWriteOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
  attrs.append("operandSegmentSizes", [&]() -> ::mlir::Attribute { return ::mlir::DenseI32ArrayAttr::get(ctx, prop.operandSegmentSizes); }());
}

::llvm::LogicalResult FirMemWriteOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    return ::mlir::success();
}

::llvm::LogicalResult FirMemWriteOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
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

void FirMemWriteOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;

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

void FirMemWriteOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value memory, ::mlir::Value address, ::mlir::Value clk, /*optional*/::mlir::Value enable, ::mlir::Value data, /*optional*/::mlir::Value mask) {
  odsState.addOperands(memory);
  odsState.addOperands(address);
  odsState.addOperands(clk);
  if (enable)
    odsState.addOperands(enable);
  odsState.addOperands(data);
  if (mask)
    odsState.addOperands(mask);
  ::llvm::copy(::llvm::ArrayRef<int32_t>({1, 1, 1, (enable ? 1 : 0), 1, (mask ? 1 : 0)}), odsState.getOrAddProperties<Properties>().operandSegmentSizes.begin());
}

FirMemWriteOp FirMemWriteOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value memory, ::mlir::Value address, ::mlir::Value clk, /*optional*/::mlir::Value enable, ::mlir::Value data, /*optional*/::mlir::Value mask) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(memory)>(memory), std::forward<decltype(address)>(address), std::forward<decltype(clk)>(clk), std::forward<decltype(enable)>(enable), std::forward<decltype(data)>(data), std::forward<decltype(mask)>(mask));
  auto __res__ = ::llvm::dyn_cast<FirMemWriteOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

FirMemWriteOp FirMemWriteOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value memory, ::mlir::Value address, ::mlir::Value clk, /*optional*/::mlir::Value enable, ::mlir::Value data, /*optional*/::mlir::Value mask) {
  return create(builder, builder.getLoc(), std::forward<decltype(memory)>(memory), std::forward<decltype(address)>(address), std::forward<decltype(clk)>(clk), std::forward<decltype(enable)>(enable), std::forward<decltype(data)>(data), std::forward<decltype(mask)>(mask));
}

void FirMemWriteOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value memory, ::mlir::Value address, ::mlir::Value clk, /*optional*/::mlir::Value enable, ::mlir::Value data, /*optional*/::mlir::Value mask) {
  odsState.addOperands(memory);
  odsState.addOperands(address);
  odsState.addOperands(clk);
  if (enable)
    odsState.addOperands(enable);
  odsState.addOperands(data);
  if (mask)
    odsState.addOperands(mask);
  ::llvm::copy(::llvm::ArrayRef<int32_t>({1, 1, 1, (enable ? 1 : 0), 1, (mask ? 1 : 0)}), odsState.getOrAddProperties<Properties>().operandSegmentSizes.begin());
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

FirMemWriteOp FirMemWriteOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value memory, ::mlir::Value address, ::mlir::Value clk, /*optional*/::mlir::Value enable, ::mlir::Value data, /*optional*/::mlir::Value mask) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(memory)>(memory), std::forward<decltype(address)>(address), std::forward<decltype(clk)>(clk), std::forward<decltype(enable)>(enable), std::forward<decltype(data)>(data), std::forward<decltype(mask)>(mask));
  auto __res__ = ::llvm::dyn_cast<FirMemWriteOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

FirMemWriteOp FirMemWriteOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value memory, ::mlir::Value address, ::mlir::Value clk, /*optional*/::mlir::Value enable, ::mlir::Value data, /*optional*/::mlir::Value mask) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(memory)>(memory), std::forward<decltype(address)>(address), std::forward<decltype(clk)>(clk), std::forward<decltype(enable)>(enable), std::forward<decltype(data)>(data), std::forward<decltype(mask)>(mask));
}

void FirMemWriteOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() >= 4u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<FirMemWriteOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

FirMemWriteOp FirMemWriteOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<FirMemWriteOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

FirMemWriteOp FirMemWriteOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void FirMemWriteOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() >= 4u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

FirMemWriteOp FirMemWriteOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<FirMemWriteOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

FirMemWriteOp FirMemWriteOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult FirMemWriteOp::verifyInvariantsImpl() {
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Seq5(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSOperands(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Seq6(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup2 = getODSOperands(2);

    for (auto v : valueGroup2) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Seq1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup3 = getODSOperands(3);

    if (valueGroup3.size() > 1) {
      return emitOpError("operand group starting at #") << index
          << " requires 0 or 1 element, but found " << valueGroup3.size();
    }

    for (auto v : valueGroup3) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Seq2(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup4 = getODSOperands(4);

    for (auto v : valueGroup4) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Seq6(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup5 = getODSOperands(5);

    if (valueGroup5.size() > 1) {
      return emitOpError("operand group starting at #") << index
          << " requires 0 or 1 element, but found " << valueGroup5.size();
    }

    for (auto v : valueGroup5) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Seq6(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  if (!((std::equal_to<>()(
      IntegerType::get(
        (*this->getODSOperands(0).begin()).getType().getContext(),
        std::max(1U, llvm::Log2_64_Ceil(cast<FirMemType>((*this->getODSOperands(0).begin()).getType()).getDepth())))
    , (*this->getODSOperands(1).begin()).getType()))))
    return emitOpError("failed to verify that address type should match clog2 of memory depth");
  if (!((std::equal_to<>()(
      IntegerType::get(
        (*this->getODSOperands(0).begin()).getType().getContext(),
        std::max(1U, cast<FirMemType>((*this->getODSOperands(0).begin()).getType()).getWidth()))
    , (*this->getODSOperands(4).begin()).getType()))))
    return emitOpError("failed to verify that data type should match memory width");
  return ::mlir::success();
}

::llvm::LogicalResult FirMemWriteOp::verifyInvariants() {
  if(::mlir::succeeded(verifyInvariantsImpl()) && ::mlir::succeeded(verify()))
    return ::mlir::success();
  return ::mlir::failure();
}

void FirMemWriteOp::getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context) {
  results.add(canonicalize);
}

::mlir::ParseResult FirMemWriteOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::OpAsmParser::UnresolvedOperand memoryRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> memoryOperands(&memoryRawOperand, 1);  ::llvm::SMLoc memoryOperandsLoc;
  (void)memoryOperandsLoc;
  ::mlir::OpAsmParser::UnresolvedOperand addressRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> addressOperands(&addressRawOperand, 1);  ::llvm::SMLoc addressOperandsLoc;
  (void)addressOperandsLoc;
  ::mlir::OpAsmParser::UnresolvedOperand dataRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> dataOperands(&dataRawOperand, 1);  ::llvm::SMLoc dataOperandsLoc;
  (void)dataOperandsLoc;
  ::mlir::OpAsmParser::UnresolvedOperand clkRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> clkOperands(&clkRawOperand, 1);  ::llvm::SMLoc clkOperandsLoc;
  (void)clkOperandsLoc;
  ::llvm::SmallVector<::mlir::OpAsmParser::UnresolvedOperand, 4> enableOperands;
  ::llvm::SMLoc enableOperandsLoc;
  (void)enableOperandsLoc;
  ::llvm::SmallVector<::mlir::OpAsmParser::UnresolvedOperand, 4> maskOperands;
  ::llvm::SMLoc maskOperandsLoc;
  (void)maskOperandsLoc;
  ::mlir::Type memoryRawType{};
  ::llvm::ArrayRef<::mlir::Type> memoryTypes(&memoryRawType, 1);
  ::llvm::SmallVector<::mlir::Type, 1> maskTypes;

  memoryOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(memoryRawOperand))
    return ::mlir::failure();
  if (parser.parseLSquare())
    return ::mlir::failure();

  addressOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(addressRawOperand))
    return ::mlir::failure();
  if (parser.parseRSquare())
    return ::mlir::failure();
  if (parser.parseEqual())
    return ::mlir::failure();

  dataOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(dataRawOperand))
    return ::mlir::failure();
  if (parser.parseComma())
    return ::mlir::failure();
  if (parser.parseKeyword("clock"))
    return ::mlir::failure();

  clkOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(clkRawOperand))
    return ::mlir::failure();
  if (::mlir::succeeded(parser.parseOptionalKeyword("enable"))) {

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
  if (::mlir::succeeded(parser.parseOptionalKeyword("mask"))) {

  {
    maskOperandsLoc = parser.getCurrentLocation();
    ::mlir::OpAsmParser::UnresolvedOperand operand;
    ::mlir::OptionalParseResult parseResult =
                                    parser.parseOptionalOperand(operand);
    if (parseResult.has_value()) {
      if (failed(*parseResult))
        return ::mlir::failure();
      maskOperands.push_back(operand);
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
    ::circt::seq::FirMemType type;
    if (parser.parseCustomTypeWithFallback(type))
      return ::mlir::failure();
    memoryRawType = type;
  }
  if (::mlir::succeeded(parser.parseOptionalComma())) {

  {
    ::mlir::Type optionalType;
    ::mlir::OptionalParseResult parseResult =
                                    parser.parseOptionalType(optionalType);
    if (parseResult.has_value()) {
      if (failed(*parseResult))
        return ::mlir::failure();
      maskTypes.push_back(optionalType);
    }
  }
  }
::llvm::copy(::llvm::ArrayRef<int32_t>({1, 1, 1, static_cast<int32_t>(enableOperands.size()), 1, static_cast<int32_t>(maskOperands.size())}), result.getOrAddProperties<FirMemWriteOp::Properties>().operandSegmentSizes.begin());
  for (::mlir::Type type : memoryTypes) {
    (void)type;
    if (!((::llvm::isa<::circt::seq::FirMemType>(type)))) {
      return parser.emitError(parser.getNameLoc()) << "'memory' must be A FIRRTL-flavored memory, but got " << type;
    }
  }
  ::mlir::Type odsBuildableType0 = parser.getBuilder().getType<::circt::seq::ClockType>();
  ::mlir::Type odsBuildableType1 = parser.getBuilder().getIntegerType(1);
  if (parser.resolveOperands(memoryOperands, memoryTypes, memoryOperandsLoc, result.operands))
    return ::mlir::failure();
  if (parser.resolveOperands(addressOperands, 
      IntegerType::get(
        memoryTypes[0].getContext(),
        std::max(1U, llvm::Log2_64_Ceil(cast<FirMemType>(memoryTypes[0]).getDepth())))
    , addressOperandsLoc, result.operands))
    return ::mlir::failure();
  if (parser.resolveOperands(clkOperands, odsBuildableType0, clkOperandsLoc, result.operands))
    return ::mlir::failure();
  if (!enableOperands.empty()) {
  if (parser.resolveOperands(enableOperands, odsBuildableType1, enableOperandsLoc, result.operands))
    return ::mlir::failure();
  }
  if (parser.resolveOperands(dataOperands, 
      IntegerType::get(
        memoryTypes[0].getContext(),
        std::max(1U, cast<FirMemType>(memoryTypes[0]).getWidth()))
    , dataOperandsLoc, result.operands))
    return ::mlir::failure();
  if (!maskOperands.empty()) {
  if (parser.resolveOperands(maskOperands, maskTypes, maskOperandsLoc, result.operands))
    return ::mlir::failure();
  }
  return ::mlir::success();
}

void FirMemWriteOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter << getMemory();
  _odsPrinter << "[";
  _odsPrinter << getAddress();
  _odsPrinter << "]";
  _odsPrinter << ' ' << "=";
  _odsPrinter << ' ';
  _odsPrinter << getData();
  _odsPrinter << ",";
  _odsPrinter << ' ' << "clock";
  _odsPrinter << ' ';
  _odsPrinter << getClk();
  if (getEnable()) {
    _odsPrinter << ' ' << "enable";
    _odsPrinter << ' ';
    if (::mlir::Value value = getEnable())
      _odsPrinter << value;
  }
  if (getMask()) {
    _odsPrinter << ' ' << "mask";
    _odsPrinter << ' ';
    if (::mlir::Value value = getMask())
      _odsPrinter << value;
  }
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("operandSegmentSizes");
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
  {
    auto type = getMemory().getType();
    if (auto validType = ::llvm::dyn_cast<::circt::seq::FirMemType>(type))
      _odsPrinter.printStrippedAttrOrType(validType);
   else
     _odsPrinter << type;
  }
  if (getMask()) {
    _odsPrinter << ",";
    _odsPrinter << ' ';
    _odsPrinter << (getMask() ? ::llvm::ArrayRef<::mlir::Type>(getMask().getType()) : ::llvm::ArrayRef<::mlir::Type>());
  }
}

void FirMemWriteOp::getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects) {
  effects.emplace_back(::mlir::MemoryEffects::Write::get(), 0, false, ::mlir::SideEffects::DefaultResource::get());
}


} // namespace circt::seq
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::seq::FirMemWriteOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::seq::detail::FirMemWriteOpGenericAdaptorBase::Properties)

namespace circt::seq {


//===----------------------------------------------------------------------===//
// ::circt::seq::FirRegOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

FirRegOpGenericAdaptorBase::FirRegOpGenericAdaptorBase(FirRegOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

std::pair<unsigned, unsigned> FirRegOpGenericAdaptorBase::getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
  bool isVariadic[] = {false, false, true, true};
  int prevVariadicCount = 0;
  for (unsigned i = 0; i < index; ++i)
    if (isVariadic[i]) ++prevVariadicCount;

  // Calculate how many dynamic values a static variadic operand corresponds to.
  // This assumes all static variadic operands have the same dynamic value count.
  int variadicSize = (odsOperandsSize - 2) / 2;
  // `index` passed in as the parameter is the static index which counts each
  // operand (variadic or not) as size 1. So here for each previous static variadic
  // operand, we need to offset by (variadicSize - 1) to get where the dynamic
  // value pack for this static operand starts.
  int start = index + (variadicSize - 1) * prevVariadicCount;
  int size = isVariadic[index] ? variadicSize : 1;
  return {start, size};
}

::llvm::StringRef FirRegOpGenericAdaptorBase::getName() {
  auto attr = getNameAttr();
  return attr.getValue();
}

::std::optional<::circt::hw::InnerSymAttr> FirRegOpGenericAdaptorBase::getInnerSym() {
  auto attr = getInnerSymAttr();
  return attr ? ::std::optional<::circt::hw::InnerSymAttr>(::llvm::cast<::circt::hw::InnerSymAttr>(attr)) : (::std::nullopt);
}

::std::optional< ::mlir::APInt > FirRegOpGenericAdaptorBase::getPreset() {
  auto attr = getPresetAttr();
  return attr ? ::std::optional< ::mlir::APInt >(attr.getValue()) : (::std::nullopt);
}

::mlir::UnitAttr FirRegOpGenericAdaptorBase::getIsAsyncAttr() {
  auto attr = ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(getProperties().isAsync);
  if (!attr)
    attr = ((false) ? ::mlir::Builder(odsAttrs.getContext()).getUnitAttr() : nullptr);
  return attr;
}

bool FirRegOpGenericAdaptorBase::getIsAsync() {
  auto attr = getIsAsyncAttr();
    if (!attr)
      return ((false) ? ::mlir::Builder(odsAttrs.getContext()).getUnitAttr() : nullptr) != nullptr;
  return attr != nullptr;
}


} // namespace detail
FirRegOpAdaptor::FirRegOpAdaptor(FirRegOp op) : FirRegOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult FirRegOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_inner_sym = getProperties().inner_sym; (void)tblgen_inner_sym;
  auto tblgen_isAsync = getProperties().isAsync; (void)tblgen_isAsync;
  auto tblgen_name = getProperties().name; (void)tblgen_name;
  if (!tblgen_name) return emitError(loc, "'seq.firreg' op requires attribute 'name'");
  auto tblgen_preset = getProperties().preset; (void)tblgen_preset;

  if (tblgen_name && !((::llvm::isa<::mlir::StringAttr>(tblgen_name))))
    return emitError(loc, "'seq.firreg' op attribute 'name' failed to satisfy constraint: string attribute");

  if (tblgen_inner_sym && !((::llvm::isa<::circt::hw::InnerSymAttr>(tblgen_inner_sym))))
    return emitError(loc, "'seq.firreg' op attribute 'inner_sym' failed to satisfy constraint: Inner symbol definition");

  if (tblgen_preset && !((::llvm::isa<::mlir::IntegerAttr>(tblgen_preset))))
    return emitError(loc, "'seq.firreg' op attribute 'preset' failed to satisfy constraint: arbitrary integer attribute");

  if (tblgen_isAsync && !((::llvm::isa<::mlir::UnitAttr>(tblgen_isAsync))))
    return emitError(loc, "'seq.firreg' op attribute 'isAsync' failed to satisfy constraint: unit attribute");
  return ::mlir::success();
}

std::pair<unsigned, unsigned> FirRegOp::getODSOperandIndexAndLength(unsigned index) {
  bool isVariadic[] = {false, false, true, true};
  int prevVariadicCount = 0;
  for (unsigned i = 0; i < index; ++i)
    if (isVariadic[i]) ++prevVariadicCount;

  // Calculate how many dynamic values a static variadic operand corresponds to.
  // This assumes all static variadic operands have the same dynamic value count.
  int variadicSize = (getOperation()->getNumOperands() - 2) / 2;
  // `index` passed in as the parameter is the static index which counts each
  // operand (variadic or not) as size 1. So here for each previous static variadic
  // operand, we need to offset by (variadicSize - 1) to get where the dynamic
  // value pack for this static operand starts.
  int start = index + (variadicSize - 1) * prevVariadicCount;
  int size = isVariadic[index] ? variadicSize : 1;
  return {start, size};
}

::mlir::MutableOperandRange FirRegOp::getResetMutable() {
  auto range = getODSOperandIndexAndLength(2);
  auto mutableRange = ::mlir::MutableOperandRange(getOperation(), range.first, range.second);
  return mutableRange;
}

::mlir::MutableOperandRange FirRegOp::getResetValueMutable() {
  auto range = getODSOperandIndexAndLength(3);
  auto mutableRange = ::mlir::MutableOperandRange(getOperation(), range.first, range.second);
  return mutableRange;
}

::llvm::LogicalResult FirRegOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
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
    auto &propStorage = prop.isAsync;
       auto attr = dict.get("isAsync");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `isAsync` in property conversion: " << attr;
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
    auto &propStorage = prop.preset;
       auto attr = dict.get("preset");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `preset` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  return ::mlir::success();
}

::mlir::Attribute FirRegOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.inner_sym;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("inner_sym",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.isAsync;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("isAsync",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.name;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("name",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.preset;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("preset",
                                       propStorage));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code FirRegOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.inner_sym.getAsOpaquePointer()), 
    llvm::hash_value(prop.isAsync.getAsOpaquePointer()), 
    llvm::hash_value(prop.name.getAsOpaquePointer()), 
    llvm::hash_value(prop.preset.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> FirRegOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "inner_sym")
      return prop.inner_sym;

    if (name == "isAsync")
      return prop.isAsync;

    if (name == "name")
      return prop.name;

    if (name == "preset")
      return prop.preset;
  return std::nullopt;
}

void FirRegOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "inner_sym") {
       prop.inner_sym = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.inner_sym)>>(value);
       return;
    }

    if (name == "isAsync") {
       prop.isAsync = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.isAsync)>>(value);
       return;
    }

    if (name == "name") {
       prop.name = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.name)>>(value);
       return;
    }

    if (name == "preset") {
       prop.preset = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.preset)>>(value);
       return;
    }
}

void FirRegOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.inner_sym) attrs.append("inner_sym", prop.inner_sym);

    if (prop.isAsync) attrs.append("isAsync", prop.isAsync);

    if (prop.name) attrs.append("name", prop.name);

    if (prop.preset) attrs.append("preset", prop.preset);
}

::llvm::LogicalResult FirRegOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getInnerSymAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Seq2(attr, "inner_sym", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getIsAsyncAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Seq13(attr, "isAsync", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getNameAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Seq3(attr, "name", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getPresetAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Seq12(attr, "preset", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult FirRegOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readOptionalAttribute(prop.inner_sym)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readOptionalAttribute(prop.isAsync)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readAttribute(prop.name)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readOptionalAttribute(prop.preset)))
    return ::mlir::failure();
  return ::mlir::success();
}

void FirRegOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;

  writer.writeOptionalAttribute(prop.inner_sym);

  writer.writeOptionalAttribute(prop.isAsync);
  writer.writeAttribute(prop.name);

  writer.writeOptionalAttribute(prop.preset);
}

::llvm::StringRef FirRegOp::getName() {
  auto attr = getNameAttr();
  return attr.getValue();
}

::std::optional<::circt::hw::InnerSymAttr> FirRegOp::getInnerSym() {
  auto attr = getInnerSymAttr();
  return attr ? ::std::optional<::circt::hw::InnerSymAttr>(::llvm::cast<::circt::hw::InnerSymAttr>(attr)) : (::std::nullopt);
}

::std::optional< ::mlir::APInt > FirRegOp::getPreset() {
  auto attr = getPresetAttr();
  return attr ? ::std::optional< ::mlir::APInt >(attr.getValue()) : (::std::nullopt);
}

bool FirRegOp::getIsAsync() {
  auto attr = getIsAsyncAttr();
    if (!attr)
      return ((false) ? ::mlir::Builder((*this)->getContext()).getUnitAttr() : nullptr) != nullptr;
  return attr != nullptr;
}

void FirRegOp::setName(::llvm::StringRef attrValue) {
  getProperties().name = ::mlir::Builder((*this)->getContext()).getStringAttr(attrValue);
}

void FirRegOp::setIsAsync(bool attrValue) {
    auto &odsProp = getProperties().isAsync;
    if (attrValue)
      odsProp = ((attrValue) ? ::mlir::Builder((*this)->getContext()).getUnitAttr() : nullptr);
    else
      odsProp = nullptr;
}

FirRegOp FirRegOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, Value next, Value clk, StringAttr name, hw::InnerSymAttr innerSym, Attribute preset) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(next)>(next), std::forward<decltype(clk)>(clk), std::forward<decltype(name)>(name), std::forward<decltype(innerSym)>(innerSym), std::forward<decltype(preset)>(preset));
  auto __res__ = ::llvm::dyn_cast<FirRegOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

FirRegOp FirRegOp::create(::mlir::ImplicitLocOpBuilder &builder, Value next, Value clk, StringAttr name, hw::InnerSymAttr innerSym, Attribute preset) {
  return create(builder, builder.getLoc(), std::forward<decltype(next)>(next), std::forward<decltype(clk)>(clk), std::forward<decltype(name)>(name), std::forward<decltype(innerSym)>(innerSym), std::forward<decltype(preset)>(preset));
}

FirRegOp FirRegOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, Value next, Value clk, StringAttr name, Value reset, Value resetValue, hw::InnerSymAttr innerSym, bool isAsync) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(next)>(next), std::forward<decltype(clk)>(clk), std::forward<decltype(name)>(name), std::forward<decltype(reset)>(reset), std::forward<decltype(resetValue)>(resetValue), std::forward<decltype(innerSym)>(innerSym), std::forward<decltype(isAsync)>(isAsync));
  auto __res__ = ::llvm::dyn_cast<FirRegOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

FirRegOp FirRegOp::create(::mlir::ImplicitLocOpBuilder &builder, Value next, Value clk, StringAttr name, Value reset, Value resetValue, hw::InnerSymAttr innerSym, bool isAsync) {
  return create(builder, builder.getLoc(), std::forward<decltype(next)>(next), std::forward<decltype(clk)>(clk), std::forward<decltype(name)>(name), std::forward<decltype(reset)>(reset), std::forward<decltype(resetValue)>(resetValue), std::forward<decltype(innerSym)>(innerSym), std::forward<decltype(isAsync)>(isAsync));
}

void FirRegOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type data, ::mlir::Value next, ::mlir::Value clk, ::mlir::StringAttr name, /*optional*/::circt::hw::InnerSymAttr inner_sym, /*optional*/::mlir::IntegerAttr preset, /*optional*/::mlir::Value reset, /*optional*/::mlir::Value resetValue, /*optional*/::mlir::UnitAttr isAsync) {
  odsState.addOperands(next);
  odsState.addOperands(clk);
  if (reset)
    odsState.addOperands(reset);
  if (resetValue)
    odsState.addOperands(resetValue);
  odsState.getOrAddProperties<Properties>().name = name;
  if (inner_sym) {
    odsState.getOrAddProperties<Properties>().inner_sym = inner_sym;
  }
  if (preset) {
    odsState.getOrAddProperties<Properties>().preset = preset;
  }
  if (isAsync) {
    odsState.getOrAddProperties<Properties>().isAsync = isAsync;
  }
  odsState.addTypes(data);
}

FirRegOp FirRegOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type data, ::mlir::Value next, ::mlir::Value clk, ::mlir::StringAttr name, /*optional*/::circt::hw::InnerSymAttr inner_sym, /*optional*/::mlir::IntegerAttr preset, /*optional*/::mlir::Value reset, /*optional*/::mlir::Value resetValue, /*optional*/::mlir::UnitAttr isAsync) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(data)>(data), std::forward<decltype(next)>(next), std::forward<decltype(clk)>(clk), std::forward<decltype(name)>(name), std::forward<decltype(inner_sym)>(inner_sym), std::forward<decltype(preset)>(preset), std::forward<decltype(reset)>(reset), std::forward<decltype(resetValue)>(resetValue), std::forward<decltype(isAsync)>(isAsync));
  auto __res__ = ::llvm::dyn_cast<FirRegOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

FirRegOp FirRegOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type data, ::mlir::Value next, ::mlir::Value clk, ::mlir::StringAttr name, /*optional*/::circt::hw::InnerSymAttr inner_sym, /*optional*/::mlir::IntegerAttr preset, /*optional*/::mlir::Value reset, /*optional*/::mlir::Value resetValue, /*optional*/::mlir::UnitAttr isAsync) {
  return create(builder, builder.getLoc(), std::forward<decltype(data)>(data), std::forward<decltype(next)>(next), std::forward<decltype(clk)>(clk), std::forward<decltype(name)>(name), std::forward<decltype(inner_sym)>(inner_sym), std::forward<decltype(preset)>(preset), std::forward<decltype(reset)>(reset), std::forward<decltype(resetValue)>(resetValue), std::forward<decltype(isAsync)>(isAsync));
}

void FirRegOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value next, ::mlir::Value clk, ::mlir::StringAttr name, /*optional*/::circt::hw::InnerSymAttr inner_sym, /*optional*/::mlir::IntegerAttr preset, /*optional*/::mlir::Value reset, /*optional*/::mlir::Value resetValue, /*optional*/::mlir::UnitAttr isAsync) {
  odsState.addOperands(next);
  odsState.addOperands(clk);
  if (reset)
    odsState.addOperands(reset);
  if (resetValue)
    odsState.addOperands(resetValue);
  odsState.getOrAddProperties<Properties>().name = name;
  if (inner_sym) {
    odsState.getOrAddProperties<Properties>().inner_sym = inner_sym;
  }
  if (preset) {
    odsState.getOrAddProperties<Properties>().preset = preset;
  }
  if (isAsync) {
    odsState.getOrAddProperties<Properties>().isAsync = isAsync;
  }

        ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
        if (::mlir::succeeded(FirRegOp::inferReturnTypes(odsBuilder.getContext(),
                      odsState.location, odsState.operands,
                      odsState.attributes.getDictionary(odsState.getContext()),
                      odsState.getRawProperties(),
                      odsState.regions, inferredReturnTypes)))
          odsState.addTypes(inferredReturnTypes);
        else
          ::mlir::detail::reportFatalInferReturnTypesError(odsState);
        
}

FirRegOp FirRegOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value next, ::mlir::Value clk, ::mlir::StringAttr name, /*optional*/::circt::hw::InnerSymAttr inner_sym, /*optional*/::mlir::IntegerAttr preset, /*optional*/::mlir::Value reset, /*optional*/::mlir::Value resetValue, /*optional*/::mlir::UnitAttr isAsync) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(next)>(next), std::forward<decltype(clk)>(clk), std::forward<decltype(name)>(name), std::forward<decltype(inner_sym)>(inner_sym), std::forward<decltype(preset)>(preset), std::forward<decltype(reset)>(reset), std::forward<decltype(resetValue)>(resetValue), std::forward<decltype(isAsync)>(isAsync));
  auto __res__ = ::llvm::dyn_cast<FirRegOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

FirRegOp FirRegOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value next, ::mlir::Value clk, ::mlir::StringAttr name, /*optional*/::circt::hw::InnerSymAttr inner_sym, /*optional*/::mlir::IntegerAttr preset, /*optional*/::mlir::Value reset, /*optional*/::mlir::Value resetValue, /*optional*/::mlir::UnitAttr isAsync) {
  return create(builder, builder.getLoc(), std::forward<decltype(next)>(next), std::forward<decltype(clk)>(clk), std::forward<decltype(name)>(name), std::forward<decltype(inner_sym)>(inner_sym), std::forward<decltype(preset)>(preset), std::forward<decltype(reset)>(reset), std::forward<decltype(resetValue)>(resetValue), std::forward<decltype(isAsync)>(isAsync));
}

void FirRegOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value next, ::mlir::Value clk, ::mlir::StringAttr name, /*optional*/::circt::hw::InnerSymAttr inner_sym, /*optional*/::mlir::IntegerAttr preset, /*optional*/::mlir::Value reset, /*optional*/::mlir::Value resetValue, /*optional*/::mlir::UnitAttr isAsync) {
  odsState.addOperands(next);
  odsState.addOperands(clk);
  if (reset)
    odsState.addOperands(reset);
  if (resetValue)
    odsState.addOperands(resetValue);
  odsState.getOrAddProperties<Properties>().name = name;
  if (inner_sym) {
    odsState.getOrAddProperties<Properties>().inner_sym = inner_sym;
  }
  if (preset) {
    odsState.getOrAddProperties<Properties>().preset = preset;
  }
  if (isAsync) {
    odsState.getOrAddProperties<Properties>().isAsync = isAsync;
  }
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

FirRegOp FirRegOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value next, ::mlir::Value clk, ::mlir::StringAttr name, /*optional*/::circt::hw::InnerSymAttr inner_sym, /*optional*/::mlir::IntegerAttr preset, /*optional*/::mlir::Value reset, /*optional*/::mlir::Value resetValue, /*optional*/::mlir::UnitAttr isAsync) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(next)>(next), std::forward<decltype(clk)>(clk), std::forward<decltype(name)>(name), std::forward<decltype(inner_sym)>(inner_sym), std::forward<decltype(preset)>(preset), std::forward<decltype(reset)>(reset), std::forward<decltype(resetValue)>(resetValue), std::forward<decltype(isAsync)>(isAsync));
  auto __res__ = ::llvm::dyn_cast<FirRegOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

FirRegOp FirRegOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value next, ::mlir::Value clk, ::mlir::StringAttr name, /*optional*/::circt::hw::InnerSymAttr inner_sym, /*optional*/::mlir::IntegerAttr preset, /*optional*/::mlir::Value reset, /*optional*/::mlir::Value resetValue, /*optional*/::mlir::UnitAttr isAsync) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(next)>(next), std::forward<decltype(clk)>(clk), std::forward<decltype(name)>(name), std::forward<decltype(inner_sym)>(inner_sym), std::forward<decltype(preset)>(preset), std::forward<decltype(reset)>(reset), std::forward<decltype(resetValue)>(resetValue), std::forward<decltype(isAsync)>(isAsync));
}

void FirRegOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type data, ::mlir::Value next, ::mlir::Value clk, ::llvm::StringRef name, /*optional*/::circt::hw::InnerSymAttr inner_sym, /*optional*/::mlir::IntegerAttr preset, /*optional*/::mlir::Value reset, /*optional*/::mlir::Value resetValue, /*optional*/bool isAsync) {
  odsState.addOperands(next);
  odsState.addOperands(clk);
  if (reset)
    odsState.addOperands(reset);
  if (resetValue)
    odsState.addOperands(resetValue);
  odsState.getOrAddProperties<Properties>().name = odsBuilder.getStringAttr(name);
  if (inner_sym) {
    odsState.getOrAddProperties<Properties>().inner_sym = inner_sym;
  }
  if (preset) {
    odsState.getOrAddProperties<Properties>().preset = preset;
  }
  if (isAsync) {
    odsState.getOrAddProperties<Properties>().isAsync = ((isAsync) ? odsBuilder.getUnitAttr() : nullptr);
  }
  odsState.addTypes(data);
}

FirRegOp FirRegOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type data, ::mlir::Value next, ::mlir::Value clk, ::llvm::StringRef name, /*optional*/::circt::hw::InnerSymAttr inner_sym, /*optional*/::mlir::IntegerAttr preset, /*optional*/::mlir::Value reset, /*optional*/::mlir::Value resetValue, /*optional*/bool isAsync) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(data)>(data), std::forward<decltype(next)>(next), std::forward<decltype(clk)>(clk), std::forward<decltype(name)>(name), std::forward<decltype(inner_sym)>(inner_sym), std::forward<decltype(preset)>(preset), std::forward<decltype(reset)>(reset), std::forward<decltype(resetValue)>(resetValue), std::forward<decltype(isAsync)>(isAsync));
  auto __res__ = ::llvm::dyn_cast<FirRegOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

FirRegOp FirRegOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type data, ::mlir::Value next, ::mlir::Value clk, ::llvm::StringRef name, /*optional*/::circt::hw::InnerSymAttr inner_sym, /*optional*/::mlir::IntegerAttr preset, /*optional*/::mlir::Value reset, /*optional*/::mlir::Value resetValue, /*optional*/bool isAsync) {
  return create(builder, builder.getLoc(), std::forward<decltype(data)>(data), std::forward<decltype(next)>(next), std::forward<decltype(clk)>(clk), std::forward<decltype(name)>(name), std::forward<decltype(inner_sym)>(inner_sym), std::forward<decltype(preset)>(preset), std::forward<decltype(reset)>(reset), std::forward<decltype(resetValue)>(resetValue), std::forward<decltype(isAsync)>(isAsync));
}

void FirRegOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value next, ::mlir::Value clk, ::llvm::StringRef name, /*optional*/::circt::hw::InnerSymAttr inner_sym, /*optional*/::mlir::IntegerAttr preset, /*optional*/::mlir::Value reset, /*optional*/::mlir::Value resetValue, /*optional*/bool isAsync) {
  odsState.addOperands(next);
  odsState.addOperands(clk);
  if (reset)
    odsState.addOperands(reset);
  if (resetValue)
    odsState.addOperands(resetValue);
  odsState.getOrAddProperties<Properties>().name = odsBuilder.getStringAttr(name);
  if (inner_sym) {
    odsState.getOrAddProperties<Properties>().inner_sym = inner_sym;
  }
  if (preset) {
    odsState.getOrAddProperties<Properties>().preset = preset;
  }
  if (isAsync) {
    odsState.getOrAddProperties<Properties>().isAsync = ((isAsync) ? odsBuilder.getUnitAttr() : nullptr);
  }

        ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
        if (::mlir::succeeded(FirRegOp::inferReturnTypes(odsBuilder.getContext(),
                      odsState.location, odsState.operands,
                      odsState.attributes.getDictionary(odsState.getContext()),
                      odsState.getRawProperties(),
                      odsState.regions, inferredReturnTypes)))
          odsState.addTypes(inferredReturnTypes);
        else
          ::mlir::detail::reportFatalInferReturnTypesError(odsState);
        
}

FirRegOp FirRegOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value next, ::mlir::Value clk, ::llvm::StringRef name, /*optional*/::circt::hw::InnerSymAttr inner_sym, /*optional*/::mlir::IntegerAttr preset, /*optional*/::mlir::Value reset, /*optional*/::mlir::Value resetValue, /*optional*/bool isAsync) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(next)>(next), std::forward<decltype(clk)>(clk), std::forward<decltype(name)>(name), std::forward<decltype(inner_sym)>(inner_sym), std::forward<decltype(preset)>(preset), std::forward<decltype(reset)>(reset), std::forward<decltype(resetValue)>(resetValue), std::forward<decltype(isAsync)>(isAsync));
  auto __res__ = ::llvm::dyn_cast<FirRegOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

FirRegOp FirRegOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value next, ::mlir::Value clk, ::llvm::StringRef name, /*optional*/::circt::hw::InnerSymAttr inner_sym, /*optional*/::mlir::IntegerAttr preset, /*optional*/::mlir::Value reset, /*optional*/::mlir::Value resetValue, /*optional*/bool isAsync) {
  return create(builder, builder.getLoc(), std::forward<decltype(next)>(next), std::forward<decltype(clk)>(clk), std::forward<decltype(name)>(name), std::forward<decltype(inner_sym)>(inner_sym), std::forward<decltype(preset)>(preset), std::forward<decltype(reset)>(reset), std::forward<decltype(resetValue)>(resetValue), std::forward<decltype(isAsync)>(isAsync));
}

void FirRegOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value next, ::mlir::Value clk, ::llvm::StringRef name, /*optional*/::circt::hw::InnerSymAttr inner_sym, /*optional*/::mlir::IntegerAttr preset, /*optional*/::mlir::Value reset, /*optional*/::mlir::Value resetValue, /*optional*/bool isAsync) {
  odsState.addOperands(next);
  odsState.addOperands(clk);
  if (reset)
    odsState.addOperands(reset);
  if (resetValue)
    odsState.addOperands(resetValue);
  odsState.getOrAddProperties<Properties>().name = odsBuilder.getStringAttr(name);
  if (inner_sym) {
    odsState.getOrAddProperties<Properties>().inner_sym = inner_sym;
  }
  if (preset) {
    odsState.getOrAddProperties<Properties>().preset = preset;
  }
  if (isAsync) {
    odsState.getOrAddProperties<Properties>().isAsync = ((isAsync) ? odsBuilder.getUnitAttr() : nullptr);
  }
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

FirRegOp FirRegOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value next, ::mlir::Value clk, ::llvm::StringRef name, /*optional*/::circt::hw::InnerSymAttr inner_sym, /*optional*/::mlir::IntegerAttr preset, /*optional*/::mlir::Value reset, /*optional*/::mlir::Value resetValue, /*optional*/bool isAsync) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(next)>(next), std::forward<decltype(clk)>(clk), std::forward<decltype(name)>(name), std::forward<decltype(inner_sym)>(inner_sym), std::forward<decltype(preset)>(preset), std::forward<decltype(reset)>(reset), std::forward<decltype(resetValue)>(resetValue), std::forward<decltype(isAsync)>(isAsync));
  auto __res__ = ::llvm::dyn_cast<FirRegOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

FirRegOp FirRegOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value next, ::mlir::Value clk, ::llvm::StringRef name, /*optional*/::circt::hw::InnerSymAttr inner_sym, /*optional*/::mlir::IntegerAttr preset, /*optional*/::mlir::Value reset, /*optional*/::mlir::Value resetValue, /*optional*/bool isAsync) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(next)>(next), std::forward<decltype(clk)>(clk), std::forward<decltype(name)>(name), std::forward<decltype(inner_sym)>(inner_sym), std::forward<decltype(preset)>(preset), std::forward<decltype(reset)>(reset), std::forward<decltype(resetValue)>(resetValue), std::forward<decltype(isAsync)>(isAsync));
}

void FirRegOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() >= 2u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<FirRegOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

FirRegOp FirRegOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<FirRegOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

FirRegOp FirRegOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void FirRegOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() >= 2u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<FirRegOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
  ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
  if (::mlir::succeeded(FirRegOp::inferReturnTypes(odsBuilder.getContext(),
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

FirRegOp FirRegOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<FirRegOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

FirRegOp FirRegOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void FirRegOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() >= 2u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

FirRegOp FirRegOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<FirRegOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

FirRegOp FirRegOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

void FirRegOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() >= 2u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties &>(properties));
  odsState.addAttributes(discardableAttributes);

  ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
  if (::mlir::succeeded(FirRegOp::inferReturnTypes(odsBuilder.getContext(),
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

FirRegOp FirRegOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<FirRegOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

FirRegOp FirRegOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult FirRegOp::verifyInvariantsImpl() {
  auto tblgen_inner_sym = getProperties().inner_sym; (void)tblgen_inner_sym;
  auto tblgen_isAsync = getProperties().isAsync; (void)tblgen_isAsync;
  auto tblgen_name = getProperties().name; (void)tblgen_name;
  if (!tblgen_name) return emitOpError("requires attribute 'name'");
  auto tblgen_preset = getProperties().preset; (void)tblgen_preset;

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Seq3(*this, tblgen_name, "name")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Seq2(*this, tblgen_inner_sym, "inner_sym")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Seq12(*this, tblgen_preset, "preset")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Seq13(*this, tblgen_isAsync, "isAsync")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Seq3(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSOperands(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Seq1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup2 = getODSOperands(2);

    if (valueGroup2.size() > 1) {
      return emitOpError("operand group starting at #") << index
          << " requires 0 or 1 element, but found " << valueGroup2.size();
    }

    for (auto v : valueGroup2) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Seq2(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup3 = getODSOperands(3);

    if (valueGroup3.size() > 1) {
      return emitOpError("operand group starting at #") << index
          << " requires 0 or 1 element, but found " << valueGroup3.size();
    }

    for (auto v : valueGroup3) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Seq3(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Seq3(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  if (!((((*this->getODSOperands(0).begin()).getType()) == ((*this->getODSResults(0).begin()).getType()) && ((*this->getODSResults(0).begin()).getType()) == ((*this->getODSOperands(0).begin()).getType()))))
    return emitOpError("failed to verify that all of {next, data} have same type");
  return ::mlir::success();
}

::llvm::LogicalResult FirRegOp::verifyInvariants() {
  if(::mlir::succeeded(verifyInvariantsImpl()) && ::mlir::succeeded(verify()))
    return ::mlir::success();
  return ::mlir::failure();
}

void FirRegOp::getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context) {
  results.add(canonicalize);
}

::llvm::LogicalResult FirRegOp::inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::PropertyRef properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes) {
  inferredReturnTypes.resize(1);
  ::mlir::Builder odsBuilder(context);
  if (operands.size() <= 0)
    return ::mlir::failure();
  ::mlir::Type odsInferredType0 = operands[0].getType();
  inferredReturnTypes[0] = odsInferredType0;
  return ::mlir::success();
}

::llvm::LogicalResult FirRegOp::setPropertiesFromParsedAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
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
  {

    auto &propStorage = prop.inner_sym;
    auto inner_symAttrName = ::mlir::StringAttr::get(ctx, "inner_sym");
    auto attr = dict.get(inner_symAttrName);
    usedKeys.insert(inner_symAttrName);
    if (attr || /*isRequired=*/false) {
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

    auto &propStorage = prop.preset;
    auto presetAttrName = ::mlir::StringAttr::get(ctx, "preset");
    auto attr = dict.get(presetAttrName);
    usedKeys.insert(presetAttrName);
    if (attr || /*isRequired=*/false) {
      if (!attr) {
        emitError() << "expected key entry for preset in DictionaryAttr to set "
                   "Properties.";
        return ::mlir::failure();
      }
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `preset` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  {

    auto &propStorage = prop.isAsync;
    auto isAsyncAttrName = ::mlir::StringAttr::get(ctx, "isAsync");
    auto attr = dict.get(isAsyncAttrName);
    usedKeys.insert(isAsyncAttrName);
    if (attr || /*isRequired=*/false) {
      if (!attr) {
        emitError() << "expected key entry for isAsync in DictionaryAttr to set "
                   "Properties.";
        return ::mlir::failure();
      }
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `isAsync` in property conversion: " << attr;
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

void FirRegOp::getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects) {
  effects.emplace_back(::mlir::MemoryEffects::Write::get(), 0, false, ::mlir::SideEffects::DefaultResource::get());
  effects.emplace_back(::mlir::MemoryEffects::Read::get(), 0, false, ::mlir::SideEffects::DefaultResource::get());
  effects.emplace_back(::mlir::MemoryEffects::Allocate::get(), 0, false, ::mlir::SideEffects::DefaultResource::get());
}


} // namespace circt::seq
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::seq::FirRegOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::seq::detail::FirRegOpGenericAdaptorBase::Properties)

namespace circt::seq {


//===----------------------------------------------------------------------===//
// ::circt::seq::FromClockOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

FromClockOpGenericAdaptorBase::FromClockOpGenericAdaptorBase(FromClockOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}


} // namespace detail
FromClockOpAdaptor::FromClockOpAdaptor(FromClockOp op) : FromClockOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult FromClockOpAdaptor::verify(::mlir::Location loc) {
  return ::mlir::success();
}

::llvm::LogicalResult FromClockOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }
      return ::mlir::success();
}

::mlir::Attribute FromClockOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code FromClockOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine();
}

std::optional<mlir::Attribute> FromClockOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
  return std::nullopt;
}

void FromClockOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
}

void FromClockOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
}

::llvm::LogicalResult FromClockOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    return ::mlir::success();
}

void FromClockOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type output, ::mlir::Value input) {
  odsState.addOperands(input);
  odsState.addTypes(output);
}

FromClockOp FromClockOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type output, ::mlir::Value input) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(output)>(output), std::forward<decltype(input)>(input));
  auto __res__ = ::llvm::dyn_cast<FromClockOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

FromClockOp FromClockOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type output, ::mlir::Value input) {
  return create(builder, builder.getLoc(), std::forward<decltype(output)>(output), std::forward<decltype(input)>(input));
}

void FromClockOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value input) {
  odsState.addOperands(input);

        ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
        if (::mlir::succeeded(FromClockOp::inferReturnTypes(odsBuilder.getContext(),
                      odsState.location, odsState.operands,
                      odsState.attributes.getDictionary(odsState.getContext()),
                      odsState.getRawProperties(),
                      odsState.regions, inferredReturnTypes)))
          odsState.addTypes(inferredReturnTypes);
        else
          ::mlir::detail::reportFatalInferReturnTypesError(odsState);
        
}

FromClockOp FromClockOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value input) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(input)>(input));
  auto __res__ = ::llvm::dyn_cast<FromClockOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

FromClockOp FromClockOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value input) {
  return create(builder, builder.getLoc(), std::forward<decltype(input)>(input));
}

void FromClockOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value input) {
  odsState.addOperands(input);
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

FromClockOp FromClockOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value input) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(input)>(input));
  auto __res__ = ::llvm::dyn_cast<FromClockOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

FromClockOp FromClockOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value input) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(input)>(input));
}

void FromClockOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

FromClockOp FromClockOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<FromClockOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

FromClockOp FromClockOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void FromClockOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);

  ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
  if (::mlir::succeeded(FromClockOp::inferReturnTypes(odsBuilder.getContext(),
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

FromClockOp FromClockOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<FromClockOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

FromClockOp FromClockOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void FromClockOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

FromClockOp FromClockOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<FromClockOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

FromClockOp FromClockOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

void FromClockOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties &>(properties));
  odsState.addAttributes(discardableAttributes);

  ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
  if (::mlir::succeeded(FromClockOp::inferReturnTypes(odsBuilder.getContext(),
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

FromClockOp FromClockOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<FromClockOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

FromClockOp FromClockOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult FromClockOp::verifyInvariantsImpl() {
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Seq1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Seq2(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult FromClockOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

void FromClockOp::getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context) {
  results.add(canonicalize);
}

::llvm::LogicalResult FromClockOp::inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::PropertyRef properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes) {
  inferredReturnTypes.resize(1);
  ::mlir::Builder odsBuilder(context);
  ::mlir::Type odsInferredType0 = odsBuilder.getIntegerType(1);
  inferredReturnTypes[0] = odsInferredType0;
  return ::mlir::success();
}

::mlir::ParseResult FromClockOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::OpAsmParser::UnresolvedOperand inputRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> inputOperands(&inputRawOperand, 1);  ::llvm::SMLoc inputOperandsLoc;
  (void)inputOperandsLoc;

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
  ::mlir::Type odsBuildableType0 = parser.getBuilder().getIntegerType(1);
  ::mlir::Type odsBuildableType1 = parser.getBuilder().getType<::circt::seq::ClockType>();
  result.addTypes(odsBuildableType0);
  if (parser.resolveOperands(inputOperands, odsBuildableType1, inputOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void FromClockOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter << getInput();
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
}

void FromClockOp::getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects) {
}


} // namespace circt::seq
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::seq::FromClockOp)

namespace circt::seq {


//===----------------------------------------------------------------------===//
// ::circt::seq::FromImmutableOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

FromImmutableOpGenericAdaptorBase::FromImmutableOpGenericAdaptorBase(FromImmutableOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}


} // namespace detail
FromImmutableOpAdaptor::FromImmutableOpAdaptor(FromImmutableOp op) : FromImmutableOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult FromImmutableOpAdaptor::verify(::mlir::Location loc) {
  return ::mlir::success();
}

::llvm::LogicalResult FromImmutableOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }
      return ::mlir::success();
}

::mlir::Attribute FromImmutableOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code FromImmutableOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine();
}

std::optional<mlir::Attribute> FromImmutableOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
  return std::nullopt;
}

void FromImmutableOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
}

void FromImmutableOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
}

::llvm::LogicalResult FromImmutableOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    return ::mlir::success();
}

void FromImmutableOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type output, ::mlir::Value input) {
  odsState.addOperands(input);
  odsState.addTypes(output);
}

FromImmutableOp FromImmutableOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type output, ::mlir::Value input) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(output)>(output), std::forward<decltype(input)>(input));
  auto __res__ = ::llvm::dyn_cast<FromImmutableOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

FromImmutableOp FromImmutableOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type output, ::mlir::Value input) {
  return create(builder, builder.getLoc(), std::forward<decltype(output)>(output), std::forward<decltype(input)>(input));
}

void FromImmutableOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value input) {
  odsState.addOperands(input);
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

FromImmutableOp FromImmutableOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value input) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(input)>(input));
  auto __res__ = ::llvm::dyn_cast<FromImmutableOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

FromImmutableOp FromImmutableOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value input) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(input)>(input));
}

void FromImmutableOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

FromImmutableOp FromImmutableOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<FromImmutableOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

FromImmutableOp FromImmutableOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void FromImmutableOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

FromImmutableOp FromImmutableOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<FromImmutableOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

FromImmutableOp FromImmutableOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult FromImmutableOp::verifyInvariantsImpl() {
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Seq4(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Seq3(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult FromImmutableOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult FromImmutableOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::OpAsmParser::UnresolvedOperand inputRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> inputOperands(&inputRawOperand, 1);  ::llvm::SMLoc inputOperandsLoc;
  (void)inputOperandsLoc;
  ::llvm::ArrayRef<::mlir::Type> allOperandTypes;
  ::llvm::ArrayRef<::mlir::Type> allResultTypes;

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

  ::mlir::FunctionType allOperand__allResult_functionType;
  if (parser.parseType(allOperand__allResult_functionType))
    return ::mlir::failure();
  allOperandTypes = allOperand__allResult_functionType.getInputs();
  allResultTypes = allOperand__allResult_functionType.getResults();
  result.addTypes(allResultTypes);
  if (parser.resolveOperands(inputOperands, allOperandTypes, parser.getNameLoc(), result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void FromImmutableOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter << getInput();
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
  _odsPrinter.printFunctionalType(getOperation()->getOperandTypes(), getOperation()->getResultTypes());
}

void FromImmutableOp::getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects) {
}


} // namespace circt::seq
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::seq::FromImmutableOp)

namespace circt::seq {


//===----------------------------------------------------------------------===//
// ::circt::seq::HLMemOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

HLMemOpGenericAdaptorBase::HLMemOpGenericAdaptorBase(HLMemOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::llvm::StringRef HLMemOpGenericAdaptorBase::getName() {
  auto attr = getNameAttr();
  return attr.getValue();
}


} // namespace detail
HLMemOpAdaptor::HLMemOpAdaptor(HLMemOp op) : HLMemOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult HLMemOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_name = getProperties().name; (void)tblgen_name;
  if (!tblgen_name) return emitError(loc, "'seq.hlmem' op requires attribute 'name'");

  if (tblgen_name && !((::llvm::isa<::mlir::StringAttr>(tblgen_name))))
    return emitError(loc, "'seq.hlmem' op attribute 'name' failed to satisfy constraint: string attribute");
  return ::mlir::success();
}

::llvm::LogicalResult HLMemOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
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

::mlir::Attribute HLMemOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
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

llvm::hash_code HLMemOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.name.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> HLMemOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "name")
      return prop.name;
  return std::nullopt;
}

void HLMemOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "name") {
       prop.name = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.name)>>(value);
       return;
    }
}

void HLMemOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.name) attrs.append("name", prop.name);
}

::llvm::LogicalResult HLMemOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getNameAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Seq3(attr, "name", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult HLMemOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.name)))
    return ::mlir::failure();
  return ::mlir::success();
}

void HLMemOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.name);
}

::llvm::StringRef HLMemOp::getName() {
  auto attr = getNameAttr();
  return attr.getValue();
}

void HLMemOp::setName(::llvm::StringRef attrValue) {
  getProperties().name = ::mlir::Builder((*this)->getContext()).getStringAttr(attrValue);
}

HLMemOp HLMemOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, Value clk, Value rst, StringRef name, llvm::ArrayRef<int64_t> shape, Type elementType) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(clk)>(clk), std::forward<decltype(rst)>(rst), std::forward<decltype(name)>(name), std::forward<decltype(shape)>(shape), std::forward<decltype(elementType)>(elementType));
  auto __res__ = ::llvm::dyn_cast<HLMemOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

HLMemOp HLMemOp::create(::mlir::ImplicitLocOpBuilder &builder, Value clk, Value rst, StringRef name, llvm::ArrayRef<int64_t> shape, Type elementType) {
  return create(builder, builder.getLoc(), std::forward<decltype(clk)>(clk), std::forward<decltype(rst)>(rst), std::forward<decltype(name)>(name), std::forward<decltype(shape)>(shape), std::forward<decltype(elementType)>(elementType));
}

void HLMemOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type handle, ::mlir::Value clk, ::mlir::Value rst, ::mlir::StringAttr name) {
  odsState.addOperands(clk);
  odsState.addOperands(rst);
  odsState.getOrAddProperties<Properties>().name = name;
  odsState.addTypes(handle);
}

HLMemOp HLMemOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type handle, ::mlir::Value clk, ::mlir::Value rst, ::mlir::StringAttr name) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(handle)>(handle), std::forward<decltype(clk)>(clk), std::forward<decltype(rst)>(rst), std::forward<decltype(name)>(name));
  auto __res__ = ::llvm::dyn_cast<HLMemOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

HLMemOp HLMemOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type handle, ::mlir::Value clk, ::mlir::Value rst, ::mlir::StringAttr name) {
  return create(builder, builder.getLoc(), std::forward<decltype(handle)>(handle), std::forward<decltype(clk)>(clk), std::forward<decltype(rst)>(rst), std::forward<decltype(name)>(name));
}

void HLMemOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value clk, ::mlir::Value rst, ::mlir::StringAttr name) {
  odsState.addOperands(clk);
  odsState.addOperands(rst);
  odsState.getOrAddProperties<Properties>().name = name;
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

HLMemOp HLMemOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value clk, ::mlir::Value rst, ::mlir::StringAttr name) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(clk)>(clk), std::forward<decltype(rst)>(rst), std::forward<decltype(name)>(name));
  auto __res__ = ::llvm::dyn_cast<HLMemOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

HLMemOp HLMemOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value clk, ::mlir::Value rst, ::mlir::StringAttr name) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(clk)>(clk), std::forward<decltype(rst)>(rst), std::forward<decltype(name)>(name));
}

void HLMemOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type handle, ::mlir::Value clk, ::mlir::Value rst, ::llvm::StringRef name) {
  odsState.addOperands(clk);
  odsState.addOperands(rst);
  odsState.getOrAddProperties<Properties>().name = odsBuilder.getStringAttr(name);
  odsState.addTypes(handle);
}

HLMemOp HLMemOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type handle, ::mlir::Value clk, ::mlir::Value rst, ::llvm::StringRef name) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(handle)>(handle), std::forward<decltype(clk)>(clk), std::forward<decltype(rst)>(rst), std::forward<decltype(name)>(name));
  auto __res__ = ::llvm::dyn_cast<HLMemOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

HLMemOp HLMemOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type handle, ::mlir::Value clk, ::mlir::Value rst, ::llvm::StringRef name) {
  return create(builder, builder.getLoc(), std::forward<decltype(handle)>(handle), std::forward<decltype(clk)>(clk), std::forward<decltype(rst)>(rst), std::forward<decltype(name)>(name));
}

void HLMemOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value clk, ::mlir::Value rst, ::llvm::StringRef name) {
  odsState.addOperands(clk);
  odsState.addOperands(rst);
  odsState.getOrAddProperties<Properties>().name = odsBuilder.getStringAttr(name);
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

HLMemOp HLMemOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value clk, ::mlir::Value rst, ::llvm::StringRef name) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(clk)>(clk), std::forward<decltype(rst)>(rst), std::forward<decltype(name)>(name));
  auto __res__ = ::llvm::dyn_cast<HLMemOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

HLMemOp HLMemOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value clk, ::mlir::Value rst, ::llvm::StringRef name) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(clk)>(clk), std::forward<decltype(rst)>(rst), std::forward<decltype(name)>(name));
}

void HLMemOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 2u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<HLMemOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

HLMemOp HLMemOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<HLMemOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

HLMemOp HLMemOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void HLMemOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 2u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

HLMemOp HLMemOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<HLMemOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

HLMemOp HLMemOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult HLMemOp::verifyInvariantsImpl() {
  auto tblgen_name = getProperties().name; (void)tblgen_name;
  if (!tblgen_name) return emitOpError("requires attribute 'name'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Seq3(*this, tblgen_name, "name")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Seq1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSOperands(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Seq2(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Seq7(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult HLMemOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult HLMemOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::StringAttr nameAttr;
  ::mlir::OpAsmParser::UnresolvedOperand clkRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> clkOperands(&clkRawOperand, 1);  ::llvm::SMLoc clkOperandsLoc;
  (void)clkOperandsLoc;
  ::mlir::OpAsmParser::UnresolvedOperand rstRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> rstOperands(&rstRawOperand, 1);  ::llvm::SMLoc rstOperandsLoc;
  (void)rstOperandsLoc;
  ::mlir::Type handleRawType{};
  ::llvm::ArrayRef<::mlir::Type> handleTypes(&handleRawType, 1);

  if (parser.parseSymbolName(nameAttr))
    return ::mlir::failure();
  if (nameAttr) result.getOrAddProperties<HLMemOp::Properties>().name = nameAttr;

  clkOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(clkRawOperand))
    return ::mlir::failure();
  if (parser.parseComma())
    return ::mlir::failure();

  rstOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(rstRawOperand))
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
    ::circt::seq::HLMemType type;
    if (parser.parseCustomTypeWithFallback(type))
      return ::mlir::failure();
    handleRawType = type;
  }
  ::mlir::Type odsBuildableType0 = parser.getBuilder().getType<::circt::seq::ClockType>();
  ::mlir::Type odsBuildableType1 = parser.getBuilder().getIntegerType(1);
  result.addTypes(handleTypes);
  if (parser.resolveOperands(clkOperands, odsBuildableType0, clkOperandsLoc, result.operands))
    return ::mlir::failure();
  if (parser.resolveOperands(rstOperands, odsBuildableType1, rstOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void HLMemOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter.printSymbolName(getNameAttr().getValue());
  _odsPrinter << ' ';
  _odsPrinter << getClk();
  _odsPrinter << ",";
  _odsPrinter << ' ';
  _odsPrinter << getRst();
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("name");
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
  {
    auto type = getHandle().getType();
    if (auto validType = ::llvm::dyn_cast<::circt::seq::HLMemType>(type))
      _odsPrinter.printStrippedAttrOrType(validType);
   else
     _odsPrinter << type;
  }
}


} // namespace circt::seq
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::seq::HLMemOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::seq::detail::HLMemOpGenericAdaptorBase::Properties)

namespace circt::seq {


//===----------------------------------------------------------------------===//
// ::circt::seq::InitialOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

InitialOpGenericAdaptorBase::InitialOpGenericAdaptorBase(InitialOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

std::pair<unsigned, unsigned> InitialOpGenericAdaptorBase::getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
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
InitialOpAdaptor::InitialOpAdaptor(InitialOp op) : InitialOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult InitialOpAdaptor::verify(::mlir::Location loc) {
  return ::mlir::success();
}

std::pair<unsigned, unsigned> InitialOp::getODSOperandIndexAndLength(unsigned index) {
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

::mlir::MutableOperandRange InitialOp::getInputsMutable() {
  auto range = getODSOperandIndexAndLength(0);
  auto mutableRange = ::mlir::MutableOperandRange(getOperation(), range.first, range.second);
  return mutableRange;
}

std::pair<unsigned, unsigned> InitialOp::getODSResultIndexAndLength(unsigned index) {
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

::llvm::LogicalResult InitialOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }
      return ::mlir::success();
}

::mlir::Attribute InitialOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code InitialOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine();
}

std::optional<mlir::Attribute> InitialOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
  return std::nullopt;
}

void InitialOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
}

void InitialOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
}

::llvm::LogicalResult InitialOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    return ::mlir::success();
}

InitialOp InitialOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, TypeRange resultTypes, std::function<void()> ctor) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(ctor)>(ctor));
  auto __res__ = ::llvm::dyn_cast<InitialOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

InitialOp InitialOp::create(::mlir::ImplicitLocOpBuilder &builder, TypeRange resultTypes, std::function<void()> ctor) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(ctor)>(ctor));
}

::llvm::LogicalResult InitialOp::verifyInvariantsImpl() {
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Seq8(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Seq8(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;

    for (auto &region : ::llvm::MutableArrayRef((*this)->getRegion(0)))
      if (::mlir::failed(__mlir_ods_local_region_constraint_Seq1(*this, region, "body", index++)))
        return ::mlir::failure();
  }
  return ::mlir::success();
}

::llvm::LogicalResult InitialOp::verifyInvariants() {
  if(::mlir::succeeded(verifyInvariantsImpl()) && ::mlir::succeeded(verify()))
    return ::mlir::success();
  return ::mlir::failure();
}

::mlir::ParseResult InitialOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::llvm::SmallVector<::mlir::OpAsmParser::UnresolvedOperand, 4> inputsOperands;
  ::llvm::SMLoc inputsOperandsLoc;
  (void)inputsOperandsLoc;
  std::unique_ptr<::mlir::Region> bodyRegion = std::make_unique<::mlir::Region>();
  ::llvm::ArrayRef<::mlir::Type> inputsTypes;
  ::llvm::ArrayRef<::mlir::Type> allResultTypes;
  if (parser.parseLParen())
    return ::mlir::failure();

  inputsOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperandList(inputsOperands))
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
  if (parser.parseColon())
    return ::mlir::failure();

  ::mlir::FunctionType inputs__allResult_functionType;
  if (parser.parseType(inputs__allResult_functionType))
    return ::mlir::failure();
  inputsTypes = inputs__allResult_functionType.getInputs();
  allResultTypes = inputs__allResult_functionType.getResults();
  result.addRegion(std::move(bodyRegion));
  result.addTypes(allResultTypes);
  if (parser.resolveOperands(inputsOperands, inputsTypes, inputsOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void InitialOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << "(";
  _odsPrinter << getInputs();
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
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
  _odsPrinter.printFunctionalType(getInputs().getTypes(), getOperation()->getResultTypes());
}


} // namespace circt::seq
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::seq::InitialOp)

namespace circt::seq {


//===----------------------------------------------------------------------===//
// ::circt::seq::ReadPortOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

ReadPortOpGenericAdaptorBase::ReadPortOpGenericAdaptorBase(ReadPortOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

std::pair<unsigned, unsigned> ReadPortOpGenericAdaptorBase::getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
  ::llvm::ArrayRef<int32_t> sizeAttr = getProperties().operandSegmentSizes;

  unsigned start = 0;
  for (unsigned i = 0; i < index; ++i)
    start += sizeAttr[i];
  return {start, sizeAttr[index]};
}

uint64_t ReadPortOpGenericAdaptorBase::getLatency() {
  auto attr = getLatencyAttr();
  return attr.getValue().getZExtValue();
}


} // namespace detail
ReadPortOpAdaptor::ReadPortOpAdaptor(ReadPortOp op) : ReadPortOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult ReadPortOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_latency = getProperties().latency; (void)tblgen_latency;
  if (!tblgen_latency) return emitError(loc, "'seq.read' op requires attribute 'latency'");

  if (tblgen_latency && !(((::llvm::isa<::mlir::IntegerAttr>(tblgen_latency))) && ((::llvm::cast<::mlir::IntegerAttr>(tblgen_latency).getType().isSignlessInteger(64)))))
    return emitError(loc, "'seq.read' op attribute 'latency' failed to satisfy constraint: 64-bit signless integer attribute");
  return ::mlir::success();
}

std::pair<unsigned, unsigned> ReadPortOp::getODSOperandIndexAndLength(unsigned index) {
  ::llvm::ArrayRef<int32_t> sizeAttr = getProperties().operandSegmentSizes;

  unsigned start = 0;
  for (unsigned i = 0; i < index; ++i)
    start += sizeAttr[i];
  return {start, sizeAttr[index]};
}

::mlir::MutableOperandRange ReadPortOp::getAddressesMutable() {
  auto range = getODSOperandIndexAndLength(1);
  auto mutableRange = ::mlir::MutableOperandRange(getOperation(), range.first, range.second, ::mlir::MutableOperandRange::OperandSegment(1u, {getOperandSegmentSizesAttrName(), ::mlir::DenseI32ArrayAttr::get(getContext(), getProperties().operandSegmentSizes)}));
  return mutableRange;
}

::mlir::MutableOperandRange ReadPortOp::getRdEnMutable() {
  auto range = getODSOperandIndexAndLength(2);
  auto mutableRange = ::mlir::MutableOperandRange(getOperation(), range.first, range.second, ::mlir::MutableOperandRange::OperandSegment(2u, {getOperandSegmentSizesAttrName(), ::mlir::DenseI32ArrayAttr::get(getContext(), getProperties().operandSegmentSizes)}));
  return mutableRange;
}

::llvm::LogicalResult ReadPortOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
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

::mlir::Attribute ReadPortOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.latency;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("latency",
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

llvm::hash_code ReadPortOp::computePropertiesHash(const Properties &prop) {
  auto hash_operandSegmentSizes_ = [] (const auto &propStorage) -> llvm::hash_code {
    using ::llvm::hash_value;
    return ::llvm::hash_combine_range(std::begin(propStorage), std::end(propStorage));;
  };
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.latency.getAsOpaquePointer()), 
    hash_operandSegmentSizes_(prop.operandSegmentSizes));
}

std::optional<mlir::Attribute> ReadPortOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "latency")
      return prop.latency;
    if (name == "operand_segment_sizes" || name == "operandSegmentSizes") return [&]() -> ::mlir::Attribute { return ::mlir::DenseI32ArrayAttr::get(ctx, prop.operandSegmentSizes); }();
  return std::nullopt;
}

void ReadPortOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "latency") {
       prop.latency = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.latency)>>(value);
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

void ReadPortOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.latency) attrs.append("latency", prop.latency);
  attrs.append("operandSegmentSizes", [&]() -> ::mlir::Attribute { return ::mlir::DenseI32ArrayAttr::get(ctx, prop.operandSegmentSizes); }());
}

::llvm::LogicalResult ReadPortOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getLatencyAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Seq1(attr, "latency", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult ReadPortOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.latency)))
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

void ReadPortOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.latency);

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

uint64_t ReadPortOp::getLatency() {
  auto attr = getLatencyAttr();
  return attr.getValue().getZExtValue();
}

void ReadPortOp::setLatency(uint64_t attrValue) {
  getProperties().latency = ::mlir::Builder((*this)->getContext()).getIntegerAttr(::mlir::Builder((*this)->getContext()).getIntegerType(64), attrValue);
}

ReadPortOp ReadPortOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, Value memory, ValueRange addresses, Value rdEn, unsigned latency) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(memory)>(memory), std::forward<decltype(addresses)>(addresses), std::forward<decltype(rdEn)>(rdEn), std::forward<decltype(latency)>(latency));
  auto __res__ = ::llvm::dyn_cast<ReadPortOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ReadPortOp ReadPortOp::create(::mlir::ImplicitLocOpBuilder &builder, Value memory, ValueRange addresses, Value rdEn, unsigned latency) {
  return create(builder, builder.getLoc(), std::forward<decltype(memory)>(memory), std::forward<decltype(addresses)>(addresses), std::forward<decltype(rdEn)>(rdEn), std::forward<decltype(latency)>(latency));
}

void ReadPortOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type readData, ::mlir::Value memory, ::mlir::ValueRange addresses, /*optional*/::mlir::Value rdEn, ::mlir::IntegerAttr latency) {
  odsState.addOperands(memory);
  odsState.addOperands(addresses);
  if (rdEn)
    odsState.addOperands(rdEn);
  ::llvm::copy(::llvm::ArrayRef<int32_t>({1, static_cast<int32_t>(addresses.size()), (rdEn ? 1 : 0)}), odsState.getOrAddProperties<Properties>().operandSegmentSizes.begin());
  odsState.getOrAddProperties<Properties>().latency = latency;
  odsState.addTypes(readData);
}

ReadPortOp ReadPortOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type readData, ::mlir::Value memory, ::mlir::ValueRange addresses, /*optional*/::mlir::Value rdEn, ::mlir::IntegerAttr latency) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(readData)>(readData), std::forward<decltype(memory)>(memory), std::forward<decltype(addresses)>(addresses), std::forward<decltype(rdEn)>(rdEn), std::forward<decltype(latency)>(latency));
  auto __res__ = ::llvm::dyn_cast<ReadPortOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ReadPortOp ReadPortOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type readData, ::mlir::Value memory, ::mlir::ValueRange addresses, /*optional*/::mlir::Value rdEn, ::mlir::IntegerAttr latency) {
  return create(builder, builder.getLoc(), std::forward<decltype(readData)>(readData), std::forward<decltype(memory)>(memory), std::forward<decltype(addresses)>(addresses), std::forward<decltype(rdEn)>(rdEn), std::forward<decltype(latency)>(latency));
}

void ReadPortOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value memory, ::mlir::ValueRange addresses, /*optional*/::mlir::Value rdEn, ::mlir::IntegerAttr latency) {
  odsState.addOperands(memory);
  odsState.addOperands(addresses);
  if (rdEn)
    odsState.addOperands(rdEn);
  ::llvm::copy(::llvm::ArrayRef<int32_t>({1, static_cast<int32_t>(addresses.size()), (rdEn ? 1 : 0)}), odsState.getOrAddProperties<Properties>().operandSegmentSizes.begin());
  odsState.getOrAddProperties<Properties>().latency = latency;
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

ReadPortOp ReadPortOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value memory, ::mlir::ValueRange addresses, /*optional*/::mlir::Value rdEn, ::mlir::IntegerAttr latency) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(memory)>(memory), std::forward<decltype(addresses)>(addresses), std::forward<decltype(rdEn)>(rdEn), std::forward<decltype(latency)>(latency));
  auto __res__ = ::llvm::dyn_cast<ReadPortOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ReadPortOp ReadPortOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value memory, ::mlir::ValueRange addresses, /*optional*/::mlir::Value rdEn, ::mlir::IntegerAttr latency) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(memory)>(memory), std::forward<decltype(addresses)>(addresses), std::forward<decltype(rdEn)>(rdEn), std::forward<decltype(latency)>(latency));
}

void ReadPortOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type readData, ::mlir::Value memory, ::mlir::ValueRange addresses, /*optional*/::mlir::Value rdEn, uint64_t latency) {
  odsState.addOperands(memory);
  odsState.addOperands(addresses);
  if (rdEn)
    odsState.addOperands(rdEn);
  ::llvm::copy(::llvm::ArrayRef<int32_t>({1, static_cast<int32_t>(addresses.size()), (rdEn ? 1 : 0)}), odsState.getOrAddProperties<Properties>().operandSegmentSizes.begin());
  odsState.getOrAddProperties<Properties>().latency = odsBuilder.getIntegerAttr(odsBuilder.getIntegerType(64), latency);
  odsState.addTypes(readData);
}

ReadPortOp ReadPortOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type readData, ::mlir::Value memory, ::mlir::ValueRange addresses, /*optional*/::mlir::Value rdEn, uint64_t latency) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(readData)>(readData), std::forward<decltype(memory)>(memory), std::forward<decltype(addresses)>(addresses), std::forward<decltype(rdEn)>(rdEn), std::forward<decltype(latency)>(latency));
  auto __res__ = ::llvm::dyn_cast<ReadPortOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ReadPortOp ReadPortOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type readData, ::mlir::Value memory, ::mlir::ValueRange addresses, /*optional*/::mlir::Value rdEn, uint64_t latency) {
  return create(builder, builder.getLoc(), std::forward<decltype(readData)>(readData), std::forward<decltype(memory)>(memory), std::forward<decltype(addresses)>(addresses), std::forward<decltype(rdEn)>(rdEn), std::forward<decltype(latency)>(latency));
}

void ReadPortOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value memory, ::mlir::ValueRange addresses, /*optional*/::mlir::Value rdEn, uint64_t latency) {
  odsState.addOperands(memory);
  odsState.addOperands(addresses);
  if (rdEn)
    odsState.addOperands(rdEn);
  ::llvm::copy(::llvm::ArrayRef<int32_t>({1, static_cast<int32_t>(addresses.size()), (rdEn ? 1 : 0)}), odsState.getOrAddProperties<Properties>().operandSegmentSizes.begin());
  odsState.getOrAddProperties<Properties>().latency = odsBuilder.getIntegerAttr(odsBuilder.getIntegerType(64), latency);
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

ReadPortOp ReadPortOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value memory, ::mlir::ValueRange addresses, /*optional*/::mlir::Value rdEn, uint64_t latency) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(memory)>(memory), std::forward<decltype(addresses)>(addresses), std::forward<decltype(rdEn)>(rdEn), std::forward<decltype(latency)>(latency));
  auto __res__ = ::llvm::dyn_cast<ReadPortOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ReadPortOp ReadPortOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value memory, ::mlir::ValueRange addresses, /*optional*/::mlir::Value rdEn, uint64_t latency) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(memory)>(memory), std::forward<decltype(addresses)>(addresses), std::forward<decltype(rdEn)>(rdEn), std::forward<decltype(latency)>(latency));
}

void ReadPortOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() >= 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<ReadPortOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

ReadPortOp ReadPortOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<ReadPortOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ReadPortOp ReadPortOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void ReadPortOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() >= 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

ReadPortOp ReadPortOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<ReadPortOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ReadPortOp ReadPortOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult ReadPortOp::verifyInvariantsImpl() {
  auto tblgen_latency = getProperties().latency; (void)tblgen_latency;
  if (!tblgen_latency) return emitOpError("requires attribute 'latency'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Seq1(*this, tblgen_latency, "latency")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Seq7(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSOperands(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Seq9(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup2 = getODSOperands(2);

    if (valueGroup2.size() > 1) {
      return emitOpError("operand group starting at #") << index
          << " requires 0 or 1 element, but found " << valueGroup2.size();
    }

    for (auto v : valueGroup2) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Seq2(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Seq3(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  if (!((isValidIndexValues((*this->getODSOperands(0).begin()), this->getODSOperands(1)))))
    return emitOpError("failed to verify that address bit widths should be identical to the clog2 of the shape of the HLMemType");
  return ::mlir::success();
}

::llvm::LogicalResult ReadPortOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::llvm::LogicalResult ReadPortOp::setPropertiesFromParsedAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
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

    auto &propStorage = prop.latency;
    auto latencyAttrName = ::mlir::StringAttr::get(ctx, "latency");
    auto attr = dict.get(latencyAttrName);
    usedKeys.insert(latencyAttrName);
    if (attr || /*isRequired=*/true) {
      if (!attr) {
        emitError() << "expected key entry for latency in DictionaryAttr to set "
                   "Properties.";
        return ::mlir::failure();
      }
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `latency` in property conversion: " << attr;
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


} // namespace circt::seq
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::seq::ReadPortOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::seq::detail::ReadPortOpGenericAdaptorBase::Properties)

namespace circt::seq {


//===----------------------------------------------------------------------===//
// ::circt::seq::ShiftRegOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

ShiftRegOpGenericAdaptorBase::ShiftRegOpGenericAdaptorBase(ShiftRegOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

std::pair<unsigned, unsigned> ShiftRegOpGenericAdaptorBase::getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
  ::llvm::ArrayRef<int32_t> sizeAttr = getProperties().operandSegmentSizes;

  unsigned start = 0;
  for (unsigned i = 0; i < index; ++i)
    start += sizeAttr[i];
  return {start, sizeAttr[index]};
}

uint64_t ShiftRegOpGenericAdaptorBase::getNumElements() {
  auto attr = getNumElementsAttr();
  return attr.getValue().getZExtValue();
}

::std::optional< ::llvm::StringRef > ShiftRegOpGenericAdaptorBase::getName() {
  auto attr = getNameAttr();
  return attr ? ::std::optional< ::llvm::StringRef >(attr.getValue()) : (::std::nullopt);
}

::std::optional<::circt::hw::InnerSymAttr> ShiftRegOpGenericAdaptorBase::getInnerSym() {
  auto attr = getInnerSymAttr();
  return attr ? ::std::optional<::circt::hw::InnerSymAttr>(::llvm::cast<::circt::hw::InnerSymAttr>(attr)) : (::std::nullopt);
}


} // namespace detail
ShiftRegOpAdaptor::ShiftRegOpAdaptor(ShiftRegOp op) : ShiftRegOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult ShiftRegOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_inner_sym = getProperties().inner_sym; (void)tblgen_inner_sym;
  auto tblgen_name = getProperties().name; (void)tblgen_name;
  auto tblgen_numElements = getProperties().numElements; (void)tblgen_numElements;
  if (!tblgen_numElements) return emitError(loc, "'seq.shiftreg' op requires attribute 'numElements'");

  if (tblgen_numElements && !((((::llvm::isa<::mlir::IntegerAttr>(tblgen_numElements))) && ((::llvm::cast<::mlir::IntegerAttr>(tblgen_numElements).getType().isSignlessInteger(64)))) && ((::llvm::cast<::mlir::IntegerAttr>(tblgen_numElements).getInt() >= 1))))
    return emitError(loc, "'seq.shiftreg' op attribute 'numElements' failed to satisfy constraint: 64-bit signless integer attribute whose minimum value is 1");

  if (tblgen_name && !((::llvm::isa<::mlir::StringAttr>(tblgen_name))))
    return emitError(loc, "'seq.shiftreg' op attribute 'name' failed to satisfy constraint: string attribute");

  if (tblgen_inner_sym && !((::llvm::isa<::circt::hw::InnerSymAttr>(tblgen_inner_sym))))
    return emitError(loc, "'seq.shiftreg' op attribute 'inner_sym' failed to satisfy constraint: Inner symbol definition");
  return ::mlir::success();
}

std::pair<unsigned, unsigned> ShiftRegOp::getODSOperandIndexAndLength(unsigned index) {
  ::llvm::ArrayRef<int32_t> sizeAttr = getProperties().operandSegmentSizes;

  unsigned start = 0;
  for (unsigned i = 0; i < index; ++i)
    start += sizeAttr[i];
  return {start, sizeAttr[index]};
}

::mlir::MutableOperandRange ShiftRegOp::getResetMutable() {
  auto range = getODSOperandIndexAndLength(3);
  auto mutableRange = ::mlir::MutableOperandRange(getOperation(), range.first, range.second, ::mlir::MutableOperandRange::OperandSegment(3u, {getOperandSegmentSizesAttrName(), ::mlir::DenseI32ArrayAttr::get(getContext(), getProperties().operandSegmentSizes)}));
  return mutableRange;
}

::mlir::MutableOperandRange ShiftRegOp::getResetValueMutable() {
  auto range = getODSOperandIndexAndLength(4);
  auto mutableRange = ::mlir::MutableOperandRange(getOperation(), range.first, range.second, ::mlir::MutableOperandRange::OperandSegment(4u, {getOperandSegmentSizesAttrName(), ::mlir::DenseI32ArrayAttr::get(getContext(), getProperties().operandSegmentSizes)}));
  return mutableRange;
}

::mlir::MutableOperandRange ShiftRegOp::getPowerOnValueMutable() {
  auto range = getODSOperandIndexAndLength(5);
  auto mutableRange = ::mlir::MutableOperandRange(getOperation(), range.first, range.second, ::mlir::MutableOperandRange::OperandSegment(5u, {getOperandSegmentSizesAttrName(), ::mlir::DenseI32ArrayAttr::get(getContext(), getProperties().operandSegmentSizes)}));
  return mutableRange;
}

::llvm::LogicalResult ShiftRegOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
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
    auto &propStorage = prop.numElements;
       auto attr = dict.get("numElements");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `numElements` in property conversion: " << attr;
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

::mlir::Attribute ShiftRegOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
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
      const auto &propStorage = prop.numElements;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("numElements",
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

llvm::hash_code ShiftRegOp::computePropertiesHash(const Properties &prop) {
  auto hash_operandSegmentSizes_ = [] (const auto &propStorage) -> llvm::hash_code {
    using ::llvm::hash_value;
    return ::llvm::hash_combine_range(std::begin(propStorage), std::end(propStorage));;
  };
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.inner_sym.getAsOpaquePointer()), 
    llvm::hash_value(prop.name.getAsOpaquePointer()), 
    llvm::hash_value(prop.numElements.getAsOpaquePointer()), 
    hash_operandSegmentSizes_(prop.operandSegmentSizes));
}

std::optional<mlir::Attribute> ShiftRegOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "inner_sym")
      return prop.inner_sym;

    if (name == "name")
      return prop.name;

    if (name == "numElements")
      return prop.numElements;
    if (name == "operand_segment_sizes" || name == "operandSegmentSizes") return [&]() -> ::mlir::Attribute { return ::mlir::DenseI32ArrayAttr::get(ctx, prop.operandSegmentSizes); }();
  return std::nullopt;
}

void ShiftRegOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "inner_sym") {
       prop.inner_sym = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.inner_sym)>>(value);
       return;
    }

    if (name == "name") {
       prop.name = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.name)>>(value);
       return;
    }

    if (name == "numElements") {
       prop.numElements = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.numElements)>>(value);
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

void ShiftRegOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.inner_sym) attrs.append("inner_sym", prop.inner_sym);

    if (prop.name) attrs.append("name", prop.name);

    if (prop.numElements) attrs.append("numElements", prop.numElements);
  attrs.append("operandSegmentSizes", [&]() -> ::mlir::Attribute { return ::mlir::DenseI32ArrayAttr::get(ctx, prop.operandSegmentSizes); }());
}

::llvm::LogicalResult ShiftRegOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getInnerSymAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Seq2(attr, "inner_sym", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getNameAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Seq3(attr, "name", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getNumElementsAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Seq5(attr, "numElements", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult ShiftRegOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readOptionalAttribute(prop.inner_sym)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readOptionalAttribute(prop.name)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readAttribute(prop.numElements)))
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

void ShiftRegOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;

  writer.writeOptionalAttribute(prop.inner_sym);

  writer.writeOptionalAttribute(prop.name);
  writer.writeAttribute(prop.numElements);

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

uint64_t ShiftRegOp::getNumElements() {
  auto attr = getNumElementsAttr();
  return attr.getValue().getZExtValue();
}

::std::optional< ::llvm::StringRef > ShiftRegOp::getName() {
  auto attr = getNameAttr();
  return attr ? ::std::optional< ::llvm::StringRef >(attr.getValue()) : (::std::nullopt);
}

::std::optional<::circt::hw::InnerSymAttr> ShiftRegOp::getInnerSym() {
  auto attr = getInnerSymAttr();
  return attr ? ::std::optional<::circt::hw::InnerSymAttr>(::llvm::cast<::circt::hw::InnerSymAttr>(attr)) : (::std::nullopt);
}

void ShiftRegOp::setNumElements(uint64_t attrValue) {
  getProperties().numElements = ::mlir::Builder((*this)->getContext()).getIntegerAttr(::mlir::Builder((*this)->getContext()).getIntegerType(64), attrValue);
}

void ShiftRegOp::setName(::std::optional<::llvm::StringRef> attrValue) {
    auto &odsProp = getProperties().name;
    if (attrValue)
      odsProp = ::mlir::Builder((*this)->getContext()).getStringAttr(*attrValue);
    else
      odsProp = nullptr;
}

void ShiftRegOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type data, ::mlir::IntegerAttr numElements, ::mlir::Value input, ::mlir::Value clk, ::mlir::Value clockEnable, /*optional*/::mlir::StringAttr name, /*optional*/::mlir::Value reset, /*optional*/::mlir::Value resetValue, /*optional*/::mlir::Value powerOnValue, /*optional*/::circt::hw::InnerSymAttr inner_sym) {
  odsState.addOperands(input);
  odsState.addOperands(clk);
  odsState.addOperands(clockEnable);
  if (reset)
    odsState.addOperands(reset);
  if (resetValue)
    odsState.addOperands(resetValue);
  if (powerOnValue)
    odsState.addOperands(powerOnValue);
  ::llvm::copy(::llvm::ArrayRef<int32_t>({1, 1, 1, (reset ? 1 : 0), (resetValue ? 1 : 0), (powerOnValue ? 1 : 0)}), odsState.getOrAddProperties<Properties>().operandSegmentSizes.begin());
  odsState.getOrAddProperties<Properties>().numElements = numElements;
  if (name) {
    odsState.getOrAddProperties<Properties>().name = name;
  }
  if (inner_sym) {
    odsState.getOrAddProperties<Properties>().inner_sym = inner_sym;
  }
  odsState.addTypes(data);
}

ShiftRegOp ShiftRegOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type data, ::mlir::IntegerAttr numElements, ::mlir::Value input, ::mlir::Value clk, ::mlir::Value clockEnable, /*optional*/::mlir::StringAttr name, /*optional*/::mlir::Value reset, /*optional*/::mlir::Value resetValue, /*optional*/::mlir::Value powerOnValue, /*optional*/::circt::hw::InnerSymAttr inner_sym) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(data)>(data), std::forward<decltype(numElements)>(numElements), std::forward<decltype(input)>(input), std::forward<decltype(clk)>(clk), std::forward<decltype(clockEnable)>(clockEnable), std::forward<decltype(name)>(name), std::forward<decltype(reset)>(reset), std::forward<decltype(resetValue)>(resetValue), std::forward<decltype(powerOnValue)>(powerOnValue), std::forward<decltype(inner_sym)>(inner_sym));
  auto __res__ = ::llvm::dyn_cast<ShiftRegOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ShiftRegOp ShiftRegOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type data, ::mlir::IntegerAttr numElements, ::mlir::Value input, ::mlir::Value clk, ::mlir::Value clockEnable, /*optional*/::mlir::StringAttr name, /*optional*/::mlir::Value reset, /*optional*/::mlir::Value resetValue, /*optional*/::mlir::Value powerOnValue, /*optional*/::circt::hw::InnerSymAttr inner_sym) {
  return create(builder, builder.getLoc(), std::forward<decltype(data)>(data), std::forward<decltype(numElements)>(numElements), std::forward<decltype(input)>(input), std::forward<decltype(clk)>(clk), std::forward<decltype(clockEnable)>(clockEnable), std::forward<decltype(name)>(name), std::forward<decltype(reset)>(reset), std::forward<decltype(resetValue)>(resetValue), std::forward<decltype(powerOnValue)>(powerOnValue), std::forward<decltype(inner_sym)>(inner_sym));
}

void ShiftRegOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::IntegerAttr numElements, ::mlir::Value input, ::mlir::Value clk, ::mlir::Value clockEnable, /*optional*/::mlir::StringAttr name, /*optional*/::mlir::Value reset, /*optional*/::mlir::Value resetValue, /*optional*/::mlir::Value powerOnValue, /*optional*/::circt::hw::InnerSymAttr inner_sym) {
  odsState.addOperands(input);
  odsState.addOperands(clk);
  odsState.addOperands(clockEnable);
  if (reset)
    odsState.addOperands(reset);
  if (resetValue)
    odsState.addOperands(resetValue);
  if (powerOnValue)
    odsState.addOperands(powerOnValue);
  ::llvm::copy(::llvm::ArrayRef<int32_t>({1, 1, 1, (reset ? 1 : 0), (resetValue ? 1 : 0), (powerOnValue ? 1 : 0)}), odsState.getOrAddProperties<Properties>().operandSegmentSizes.begin());
  odsState.getOrAddProperties<Properties>().numElements = numElements;
  if (name) {
    odsState.getOrAddProperties<Properties>().name = name;
  }
  if (inner_sym) {
    odsState.getOrAddProperties<Properties>().inner_sym = inner_sym;
  }

        ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
        if (::mlir::succeeded(ShiftRegOp::inferReturnTypes(odsBuilder.getContext(),
                      odsState.location, odsState.operands,
                      odsState.attributes.getDictionary(odsState.getContext()),
                      odsState.getRawProperties(),
                      odsState.regions, inferredReturnTypes)))
          odsState.addTypes(inferredReturnTypes);
        else
          ::mlir::detail::reportFatalInferReturnTypesError(odsState);
        
}

ShiftRegOp ShiftRegOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::IntegerAttr numElements, ::mlir::Value input, ::mlir::Value clk, ::mlir::Value clockEnable, /*optional*/::mlir::StringAttr name, /*optional*/::mlir::Value reset, /*optional*/::mlir::Value resetValue, /*optional*/::mlir::Value powerOnValue, /*optional*/::circt::hw::InnerSymAttr inner_sym) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(numElements)>(numElements), std::forward<decltype(input)>(input), std::forward<decltype(clk)>(clk), std::forward<decltype(clockEnable)>(clockEnable), std::forward<decltype(name)>(name), std::forward<decltype(reset)>(reset), std::forward<decltype(resetValue)>(resetValue), std::forward<decltype(powerOnValue)>(powerOnValue), std::forward<decltype(inner_sym)>(inner_sym));
  auto __res__ = ::llvm::dyn_cast<ShiftRegOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ShiftRegOp ShiftRegOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::IntegerAttr numElements, ::mlir::Value input, ::mlir::Value clk, ::mlir::Value clockEnable, /*optional*/::mlir::StringAttr name, /*optional*/::mlir::Value reset, /*optional*/::mlir::Value resetValue, /*optional*/::mlir::Value powerOnValue, /*optional*/::circt::hw::InnerSymAttr inner_sym) {
  return create(builder, builder.getLoc(), std::forward<decltype(numElements)>(numElements), std::forward<decltype(input)>(input), std::forward<decltype(clk)>(clk), std::forward<decltype(clockEnable)>(clockEnable), std::forward<decltype(name)>(name), std::forward<decltype(reset)>(reset), std::forward<decltype(resetValue)>(resetValue), std::forward<decltype(powerOnValue)>(powerOnValue), std::forward<decltype(inner_sym)>(inner_sym));
}

void ShiftRegOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::IntegerAttr numElements, ::mlir::Value input, ::mlir::Value clk, ::mlir::Value clockEnable, /*optional*/::mlir::StringAttr name, /*optional*/::mlir::Value reset, /*optional*/::mlir::Value resetValue, /*optional*/::mlir::Value powerOnValue, /*optional*/::circt::hw::InnerSymAttr inner_sym) {
  odsState.addOperands(input);
  odsState.addOperands(clk);
  odsState.addOperands(clockEnable);
  if (reset)
    odsState.addOperands(reset);
  if (resetValue)
    odsState.addOperands(resetValue);
  if (powerOnValue)
    odsState.addOperands(powerOnValue);
  ::llvm::copy(::llvm::ArrayRef<int32_t>({1, 1, 1, (reset ? 1 : 0), (resetValue ? 1 : 0), (powerOnValue ? 1 : 0)}), odsState.getOrAddProperties<Properties>().operandSegmentSizes.begin());
  odsState.getOrAddProperties<Properties>().numElements = numElements;
  if (name) {
    odsState.getOrAddProperties<Properties>().name = name;
  }
  if (inner_sym) {
    odsState.getOrAddProperties<Properties>().inner_sym = inner_sym;
  }
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

ShiftRegOp ShiftRegOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::IntegerAttr numElements, ::mlir::Value input, ::mlir::Value clk, ::mlir::Value clockEnable, /*optional*/::mlir::StringAttr name, /*optional*/::mlir::Value reset, /*optional*/::mlir::Value resetValue, /*optional*/::mlir::Value powerOnValue, /*optional*/::circt::hw::InnerSymAttr inner_sym) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(numElements)>(numElements), std::forward<decltype(input)>(input), std::forward<decltype(clk)>(clk), std::forward<decltype(clockEnable)>(clockEnable), std::forward<decltype(name)>(name), std::forward<decltype(reset)>(reset), std::forward<decltype(resetValue)>(resetValue), std::forward<decltype(powerOnValue)>(powerOnValue), std::forward<decltype(inner_sym)>(inner_sym));
  auto __res__ = ::llvm::dyn_cast<ShiftRegOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ShiftRegOp ShiftRegOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::IntegerAttr numElements, ::mlir::Value input, ::mlir::Value clk, ::mlir::Value clockEnable, /*optional*/::mlir::StringAttr name, /*optional*/::mlir::Value reset, /*optional*/::mlir::Value resetValue, /*optional*/::mlir::Value powerOnValue, /*optional*/::circt::hw::InnerSymAttr inner_sym) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(numElements)>(numElements), std::forward<decltype(input)>(input), std::forward<decltype(clk)>(clk), std::forward<decltype(clockEnable)>(clockEnable), std::forward<decltype(name)>(name), std::forward<decltype(reset)>(reset), std::forward<decltype(resetValue)>(resetValue), std::forward<decltype(powerOnValue)>(powerOnValue), std::forward<decltype(inner_sym)>(inner_sym));
}

void ShiftRegOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type data, uint64_t numElements, ::mlir::Value input, ::mlir::Value clk, ::mlir::Value clockEnable, /*optional*/::mlir::StringAttr name, /*optional*/::mlir::Value reset, /*optional*/::mlir::Value resetValue, /*optional*/::mlir::Value powerOnValue, /*optional*/::circt::hw::InnerSymAttr inner_sym) {
  odsState.addOperands(input);
  odsState.addOperands(clk);
  odsState.addOperands(clockEnable);
  if (reset)
    odsState.addOperands(reset);
  if (resetValue)
    odsState.addOperands(resetValue);
  if (powerOnValue)
    odsState.addOperands(powerOnValue);
  ::llvm::copy(::llvm::ArrayRef<int32_t>({1, 1, 1, (reset ? 1 : 0), (resetValue ? 1 : 0), (powerOnValue ? 1 : 0)}), odsState.getOrAddProperties<Properties>().operandSegmentSizes.begin());
  odsState.getOrAddProperties<Properties>().numElements = odsBuilder.getIntegerAttr(odsBuilder.getIntegerType(64), numElements);
  if (name) {
    odsState.getOrAddProperties<Properties>().name = name;
  }
  if (inner_sym) {
    odsState.getOrAddProperties<Properties>().inner_sym = inner_sym;
  }
  odsState.addTypes(data);
}

ShiftRegOp ShiftRegOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type data, uint64_t numElements, ::mlir::Value input, ::mlir::Value clk, ::mlir::Value clockEnable, /*optional*/::mlir::StringAttr name, /*optional*/::mlir::Value reset, /*optional*/::mlir::Value resetValue, /*optional*/::mlir::Value powerOnValue, /*optional*/::circt::hw::InnerSymAttr inner_sym) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(data)>(data), std::forward<decltype(numElements)>(numElements), std::forward<decltype(input)>(input), std::forward<decltype(clk)>(clk), std::forward<decltype(clockEnable)>(clockEnable), std::forward<decltype(name)>(name), std::forward<decltype(reset)>(reset), std::forward<decltype(resetValue)>(resetValue), std::forward<decltype(powerOnValue)>(powerOnValue), std::forward<decltype(inner_sym)>(inner_sym));
  auto __res__ = ::llvm::dyn_cast<ShiftRegOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ShiftRegOp ShiftRegOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type data, uint64_t numElements, ::mlir::Value input, ::mlir::Value clk, ::mlir::Value clockEnable, /*optional*/::mlir::StringAttr name, /*optional*/::mlir::Value reset, /*optional*/::mlir::Value resetValue, /*optional*/::mlir::Value powerOnValue, /*optional*/::circt::hw::InnerSymAttr inner_sym) {
  return create(builder, builder.getLoc(), std::forward<decltype(data)>(data), std::forward<decltype(numElements)>(numElements), std::forward<decltype(input)>(input), std::forward<decltype(clk)>(clk), std::forward<decltype(clockEnable)>(clockEnable), std::forward<decltype(name)>(name), std::forward<decltype(reset)>(reset), std::forward<decltype(resetValue)>(resetValue), std::forward<decltype(powerOnValue)>(powerOnValue), std::forward<decltype(inner_sym)>(inner_sym));
}

void ShiftRegOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, uint64_t numElements, ::mlir::Value input, ::mlir::Value clk, ::mlir::Value clockEnable, /*optional*/::mlir::StringAttr name, /*optional*/::mlir::Value reset, /*optional*/::mlir::Value resetValue, /*optional*/::mlir::Value powerOnValue, /*optional*/::circt::hw::InnerSymAttr inner_sym) {
  odsState.addOperands(input);
  odsState.addOperands(clk);
  odsState.addOperands(clockEnable);
  if (reset)
    odsState.addOperands(reset);
  if (resetValue)
    odsState.addOperands(resetValue);
  if (powerOnValue)
    odsState.addOperands(powerOnValue);
  ::llvm::copy(::llvm::ArrayRef<int32_t>({1, 1, 1, (reset ? 1 : 0), (resetValue ? 1 : 0), (powerOnValue ? 1 : 0)}), odsState.getOrAddProperties<Properties>().operandSegmentSizes.begin());
  odsState.getOrAddProperties<Properties>().numElements = odsBuilder.getIntegerAttr(odsBuilder.getIntegerType(64), numElements);
  if (name) {
    odsState.getOrAddProperties<Properties>().name = name;
  }
  if (inner_sym) {
    odsState.getOrAddProperties<Properties>().inner_sym = inner_sym;
  }

        ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
        if (::mlir::succeeded(ShiftRegOp::inferReturnTypes(odsBuilder.getContext(),
                      odsState.location, odsState.operands,
                      odsState.attributes.getDictionary(odsState.getContext()),
                      odsState.getRawProperties(),
                      odsState.regions, inferredReturnTypes)))
          odsState.addTypes(inferredReturnTypes);
        else
          ::mlir::detail::reportFatalInferReturnTypesError(odsState);
        
}

ShiftRegOp ShiftRegOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, uint64_t numElements, ::mlir::Value input, ::mlir::Value clk, ::mlir::Value clockEnable, /*optional*/::mlir::StringAttr name, /*optional*/::mlir::Value reset, /*optional*/::mlir::Value resetValue, /*optional*/::mlir::Value powerOnValue, /*optional*/::circt::hw::InnerSymAttr inner_sym) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(numElements)>(numElements), std::forward<decltype(input)>(input), std::forward<decltype(clk)>(clk), std::forward<decltype(clockEnable)>(clockEnable), std::forward<decltype(name)>(name), std::forward<decltype(reset)>(reset), std::forward<decltype(resetValue)>(resetValue), std::forward<decltype(powerOnValue)>(powerOnValue), std::forward<decltype(inner_sym)>(inner_sym));
  auto __res__ = ::llvm::dyn_cast<ShiftRegOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ShiftRegOp ShiftRegOp::create(::mlir::ImplicitLocOpBuilder &builder, uint64_t numElements, ::mlir::Value input, ::mlir::Value clk, ::mlir::Value clockEnable, /*optional*/::mlir::StringAttr name, /*optional*/::mlir::Value reset, /*optional*/::mlir::Value resetValue, /*optional*/::mlir::Value powerOnValue, /*optional*/::circt::hw::InnerSymAttr inner_sym) {
  return create(builder, builder.getLoc(), std::forward<decltype(numElements)>(numElements), std::forward<decltype(input)>(input), std::forward<decltype(clk)>(clk), std::forward<decltype(clockEnable)>(clockEnable), std::forward<decltype(name)>(name), std::forward<decltype(reset)>(reset), std::forward<decltype(resetValue)>(resetValue), std::forward<decltype(powerOnValue)>(powerOnValue), std::forward<decltype(inner_sym)>(inner_sym));
}

void ShiftRegOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, uint64_t numElements, ::mlir::Value input, ::mlir::Value clk, ::mlir::Value clockEnable, /*optional*/::mlir::StringAttr name, /*optional*/::mlir::Value reset, /*optional*/::mlir::Value resetValue, /*optional*/::mlir::Value powerOnValue, /*optional*/::circt::hw::InnerSymAttr inner_sym) {
  odsState.addOperands(input);
  odsState.addOperands(clk);
  odsState.addOperands(clockEnable);
  if (reset)
    odsState.addOperands(reset);
  if (resetValue)
    odsState.addOperands(resetValue);
  if (powerOnValue)
    odsState.addOperands(powerOnValue);
  ::llvm::copy(::llvm::ArrayRef<int32_t>({1, 1, 1, (reset ? 1 : 0), (resetValue ? 1 : 0), (powerOnValue ? 1 : 0)}), odsState.getOrAddProperties<Properties>().operandSegmentSizes.begin());
  odsState.getOrAddProperties<Properties>().numElements = odsBuilder.getIntegerAttr(odsBuilder.getIntegerType(64), numElements);
  if (name) {
    odsState.getOrAddProperties<Properties>().name = name;
  }
  if (inner_sym) {
    odsState.getOrAddProperties<Properties>().inner_sym = inner_sym;
  }
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

ShiftRegOp ShiftRegOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, uint64_t numElements, ::mlir::Value input, ::mlir::Value clk, ::mlir::Value clockEnable, /*optional*/::mlir::StringAttr name, /*optional*/::mlir::Value reset, /*optional*/::mlir::Value resetValue, /*optional*/::mlir::Value powerOnValue, /*optional*/::circt::hw::InnerSymAttr inner_sym) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(numElements)>(numElements), std::forward<decltype(input)>(input), std::forward<decltype(clk)>(clk), std::forward<decltype(clockEnable)>(clockEnable), std::forward<decltype(name)>(name), std::forward<decltype(reset)>(reset), std::forward<decltype(resetValue)>(resetValue), std::forward<decltype(powerOnValue)>(powerOnValue), std::forward<decltype(inner_sym)>(inner_sym));
  auto __res__ = ::llvm::dyn_cast<ShiftRegOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ShiftRegOp ShiftRegOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, uint64_t numElements, ::mlir::Value input, ::mlir::Value clk, ::mlir::Value clockEnable, /*optional*/::mlir::StringAttr name, /*optional*/::mlir::Value reset, /*optional*/::mlir::Value resetValue, /*optional*/::mlir::Value powerOnValue, /*optional*/::circt::hw::InnerSymAttr inner_sym) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(numElements)>(numElements), std::forward<decltype(input)>(input), std::forward<decltype(clk)>(clk), std::forward<decltype(clockEnable)>(clockEnable), std::forward<decltype(name)>(name), std::forward<decltype(reset)>(reset), std::forward<decltype(resetValue)>(resetValue), std::forward<decltype(powerOnValue)>(powerOnValue), std::forward<decltype(inner_sym)>(inner_sym));
}

void ShiftRegOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() >= 3u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<ShiftRegOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

ShiftRegOp ShiftRegOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<ShiftRegOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ShiftRegOp ShiftRegOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void ShiftRegOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() >= 3u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<ShiftRegOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
  ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
  if (::mlir::succeeded(ShiftRegOp::inferReturnTypes(odsBuilder.getContext(),
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

ShiftRegOp ShiftRegOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<ShiftRegOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ShiftRegOp ShiftRegOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void ShiftRegOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() >= 3u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

ShiftRegOp ShiftRegOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<ShiftRegOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ShiftRegOp ShiftRegOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

void ShiftRegOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() >= 3u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties &>(properties));
  odsState.addAttributes(discardableAttributes);

  ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
  if (::mlir::succeeded(ShiftRegOp::inferReturnTypes(odsBuilder.getContext(),
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

ShiftRegOp ShiftRegOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<ShiftRegOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ShiftRegOp ShiftRegOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult ShiftRegOp::verifyInvariantsImpl() {
  auto tblgen_inner_sym = getProperties().inner_sym; (void)tblgen_inner_sym;
  auto tblgen_name = getProperties().name; (void)tblgen_name;
  auto tblgen_numElements = getProperties().numElements; (void)tblgen_numElements;
  if (!tblgen_numElements) return emitOpError("requires attribute 'numElements'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Seq5(*this, tblgen_numElements, "numElements")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Seq3(*this, tblgen_name, "name")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Seq2(*this, tblgen_inner_sym, "inner_sym")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Seq3(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSOperands(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Seq1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup2 = getODSOperands(2);

    for (auto v : valueGroup2) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Seq2(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup3 = getODSOperands(3);

    if (valueGroup3.size() > 1) {
      return emitOpError("operand group starting at #") << index
          << " requires 0 or 1 element, but found " << valueGroup3.size();
    }

    for (auto v : valueGroup3) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Seq2(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup4 = getODSOperands(4);

    if (valueGroup4.size() > 1) {
      return emitOpError("operand group starting at #") << index
          << " requires 0 or 1 element, but found " << valueGroup4.size();
    }

    for (auto v : valueGroup4) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Seq3(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup5 = getODSOperands(5);

    if (valueGroup5.size() > 1) {
      return emitOpError("operand group starting at #") << index
          << " requires 0 or 1 element, but found " << valueGroup5.size();
    }

    for (auto v : valueGroup5) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Seq3(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Seq3(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  if (!((((*this->getODSOperands(0).begin()).getType()) == ((*this->getODSResults(0).begin()).getType()) && ((*this->getODSResults(0).begin()).getType()) == ((*this->getODSOperands(0).begin()).getType()))))
    return emitOpError("failed to verify that all of {input, data} have same type");
  return ::mlir::success();
}

::llvm::LogicalResult ShiftRegOp::verifyInvariants() {
  if(::mlir::succeeded(verifyInvariantsImpl()) && ::mlir::succeeded(verify()))
    return ::mlir::success();
  return ::mlir::failure();
}

::llvm::LogicalResult ShiftRegOp::inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::PropertyRef properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes) {
  inferredReturnTypes.resize(1);
  ::mlir::Builder odsBuilder(context);
  if (operands.size() <= 0)
    return ::mlir::failure();
  ::mlir::Type odsInferredType0 = operands[0].getType();
  inferredReturnTypes[0] = odsInferredType0;
  return ::mlir::success();
}

::mlir::ParseResult ShiftRegOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::IntegerAttr numElementsAttr;
  ::circt::hw::InnerSymAttr inner_symAttr;
  ::mlir::StringAttr nameAttr;
  ::mlir::OpAsmParser::UnresolvedOperand inputRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> inputOperands(&inputRawOperand, 1);  ::llvm::SMLoc inputOperandsLoc;
  (void)inputOperandsLoc;
  ::mlir::OpAsmParser::UnresolvedOperand clkRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> clkOperands(&clkRawOperand, 1);  ::llvm::SMLoc clkOperandsLoc;
  (void)clkOperandsLoc;
  ::mlir::OpAsmParser::UnresolvedOperand clockEnableRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> clockEnableOperands(&clockEnableRawOperand, 1);  ::llvm::SMLoc clockEnableOperandsLoc;
  (void)clockEnableOperandsLoc;
  ::llvm::SmallVector<::mlir::OpAsmParser::UnresolvedOperand, 4> resetOperands;
  ::llvm::SMLoc resetOperandsLoc;
  (void)resetOperandsLoc;
  ::llvm::SmallVector<::mlir::OpAsmParser::UnresolvedOperand, 4> resetValueOperands;
  ::llvm::SMLoc resetValueOperandsLoc;
  (void)resetValueOperandsLoc;
  ::llvm::SmallVector<::mlir::OpAsmParser::UnresolvedOperand, 4> powerOnValueOperands;
  ::llvm::SMLoc powerOnValueOperandsLoc;
  (void)powerOnValueOperandsLoc;
  ::mlir::Type dataRawType{};
  ::llvm::ArrayRef<::mlir::Type> dataTypes(&dataRawType, 1);
  ::llvm::SmallVector<::mlir::Type, 1> resetValueTypes;
  ::llvm::SmallVector<::mlir::Type, 1> powerOnValueTypes;
  if (parser.parseLSquare())
    return ::mlir::failure();

  if (parser.parseCustomAttributeWithFallback(numElementsAttr, parser.getBuilder().getIntegerType(64))) {
    return ::mlir::failure();
  }
  if (numElementsAttr) result.getOrAddProperties<ShiftRegOp::Properties>().numElements = numElementsAttr;
  if (parser.parseRSquare())
    return ::mlir::failure();
  if (::mlir::succeeded(parser.parseOptionalKeyword("sym"))) {

  if (parser.parseCustomAttributeWithFallback(inner_symAttr, ::mlir::Type{})) {
    return ::mlir::failure();
  }
  if (inner_symAttr) result.getOrAddProperties<ShiftRegOp::Properties>().inner_sym = inner_symAttr;
  }
  {
    auto odsResult = parseImplicitSSAName(parser, nameAttr);
    if (odsResult) return ::mlir::failure();
    if (nameAttr)
      result.getOrAddProperties<ShiftRegOp::Properties>().name = nameAttr;
  }

  inputOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(inputRawOperand))
    return ::mlir::failure();
  if (parser.parseComma())
    return ::mlir::failure();

  clkOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(clkRawOperand))
    return ::mlir::failure();
  if (parser.parseComma())
    return ::mlir::failure();

  clockEnableOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(clockEnableRawOperand))
    return ::mlir::failure();
  if (::mlir::succeeded(parser.parseOptionalKeyword("reset"))) {

  {
    resetOperandsLoc = parser.getCurrentLocation();
    ::mlir::OpAsmParser::UnresolvedOperand operand;
    ::mlir::OptionalParseResult parseResult =
                                    parser.parseOptionalOperand(operand);
    if (parseResult.has_value()) {
      if (failed(*parseResult))
        return ::mlir::failure();
      resetOperands.push_back(operand);
    }
  }
  if (parser.parseComma())
    return ::mlir::failure();

  {
    resetValueOperandsLoc = parser.getCurrentLocation();
    ::mlir::OpAsmParser::UnresolvedOperand operand;
    ::mlir::OptionalParseResult parseResult =
                                    parser.parseOptionalOperand(operand);
    if (parseResult.has_value()) {
      if (failed(*parseResult))
        return ::mlir::failure();
      resetValueOperands.push_back(operand);
    }
  }
  }
  if (::mlir::succeeded(parser.parseOptionalKeyword("powerOn"))) {

  {
    powerOnValueOperandsLoc = parser.getCurrentLocation();
    ::mlir::OpAsmParser::UnresolvedOperand operand;
    ::mlir::OptionalParseResult parseResult =
                                    parser.parseOptionalOperand(operand);
    if (parseResult.has_value()) {
      if (failed(*parseResult))
        return ::mlir::failure();
      powerOnValueOperands.push_back(operand);
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
    dataRawType = type;
  }
  {
    ::std::optional<::mlir::OpAsmParser::UnresolvedOperand> resetValueOperand = resetValueOperands.empty() ? ::std::optional<::mlir::OpAsmParser::UnresolvedOperand>() : resetValueOperands[0];
    ::mlir::Type resetValueType;
    auto odsResult = parseOptionalTypeMatch(parser, dataRawType, resetValueOperand, resetValueType);
    if (odsResult) return ::mlir::failure();
    if (resetValueType)
      resetValueTypes.push_back(resetValueType);
  }
  {
    ::std::optional<::mlir::OpAsmParser::UnresolvedOperand> powerOnValueOperand = powerOnValueOperands.empty() ? ::std::optional<::mlir::OpAsmParser::UnresolvedOperand>() : powerOnValueOperands[0];
    ::mlir::Type powerOnValueType;
    auto odsResult = parseOptionalTypeMatch(parser, dataRawType, powerOnValueOperand, powerOnValueType);
    if (odsResult) return ::mlir::failure();
    if (powerOnValueType)
      powerOnValueTypes.push_back(powerOnValueType);
  }
::llvm::copy(::llvm::ArrayRef<int32_t>({1, 1, 1, static_cast<int32_t>(resetOperands.size()), static_cast<int32_t>(resetValueOperands.size()), static_cast<int32_t>(powerOnValueOperands.size())}), result.getOrAddProperties<ShiftRegOp::Properties>().operandSegmentSizes.begin());
  ::mlir::Type odsBuildableType0 = parser.getBuilder().getType<::circt::seq::ClockType>();
  ::mlir::Type odsBuildableType1 = parser.getBuilder().getIntegerType(1);
  result.addTypes(dataTypes);
  if (parser.resolveOperands(inputOperands, dataTypes[0], inputOperandsLoc, result.operands))
    return ::mlir::failure();
  if (parser.resolveOperands(clkOperands, odsBuildableType0, clkOperandsLoc, result.operands))
    return ::mlir::failure();
  if (parser.resolveOperands(clockEnableOperands, odsBuildableType1, clockEnableOperandsLoc, result.operands))
    return ::mlir::failure();
  if (!resetOperands.empty()) {
  if (parser.resolveOperands(resetOperands, odsBuildableType1, resetOperandsLoc, result.operands))
    return ::mlir::failure();
  }
  if (!resetValueOperands.empty()) {
  if (parser.resolveOperands(resetValueOperands, resetValueTypes, resetValueOperandsLoc, result.operands))
    return ::mlir::failure();
  }
  if (!powerOnValueOperands.empty()) {
  if (parser.resolveOperands(powerOnValueOperands, powerOnValueTypes, powerOnValueOperandsLoc, result.operands))
    return ::mlir::failure();
  }
  return ::mlir::success();
}

void ShiftRegOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << "[";
  _odsPrinter.printAttributeWithoutType(getNumElementsAttr());
  _odsPrinter << "]";
  if (getInnerSymAttr()) {
    _odsPrinter << ' ' << "sym";
    _odsPrinter << ' ';
  _odsPrinter.printStrippedAttrOrType(getInnerSymAttr());
  }
  printImplicitSSAName(_odsPrinter, *this, getNameAttr());
  _odsPrinter << ' ';
  _odsPrinter << getInput();
  _odsPrinter << ",";
  _odsPrinter << ' ';
  _odsPrinter << getClk();
  _odsPrinter << ",";
  _odsPrinter << ' ';
  _odsPrinter << getClockEnable();
  if (getReset()) {
    _odsPrinter << ' ' << "reset";
    _odsPrinter << ' ';
    if (::mlir::Value value = getReset())
      _odsPrinter << value;
    _odsPrinter << ",";
    _odsPrinter << ' ';
    if (::mlir::Value value = getResetValue())
      _odsPrinter << value;
  }
  if (getPowerOnValue()) {
    _odsPrinter << ' ' << "powerOn";
    _odsPrinter << ' ';
    if (::mlir::Value value = getPowerOnValue())
      _odsPrinter << value;
  }
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("operandSegmentSizes");
  elidedAttrs.push_back("numElements");
  elidedAttrs.push_back("inner_sym");
  elidedAttrs.push_back("name");
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
  {
    auto type = getData().getType();
    if (auto validType = ::llvm::dyn_cast<::mlir::Type>(type))
      _odsPrinter.printStrippedAttrOrType(validType);
   else
     _odsPrinter << type;
  }
  _odsPrinter << ' ';
  printOptionalTypeMatch(_odsPrinter, *this, getData().getType(), getResetValue(), (getResetValue() ? getResetValue().getType() : ::mlir::Type()));
  _odsPrinter << ' ';
  printOptionalTypeMatch(_odsPrinter, *this, getData().getType(), getPowerOnValue(), (getPowerOnValue() ? getPowerOnValue().getType() : ::mlir::Type()));
}

void ShiftRegOp::getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects) {
}


} // namespace circt::seq
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::seq::ShiftRegOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::seq::detail::ShiftRegOpGenericAdaptorBase::Properties)

namespace circt::seq {


//===----------------------------------------------------------------------===//
// ::circt::seq::ToClockOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

ToClockOpGenericAdaptorBase::ToClockOpGenericAdaptorBase(ToClockOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}


} // namespace detail
ToClockOpAdaptor::ToClockOpAdaptor(ToClockOp op) : ToClockOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult ToClockOpAdaptor::verify(::mlir::Location loc) {
  return ::mlir::success();
}

::llvm::LogicalResult ToClockOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }
      return ::mlir::success();
}

::mlir::Attribute ToClockOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code ToClockOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine();
}

std::optional<mlir::Attribute> ToClockOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
  return std::nullopt;
}

void ToClockOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
}

void ToClockOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
}

::llvm::LogicalResult ToClockOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    return ::mlir::success();
}

void ToClockOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type output, ::mlir::Value input) {
  odsState.addOperands(input);
  odsState.addTypes(output);
}

ToClockOp ToClockOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type output, ::mlir::Value input) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(output)>(output), std::forward<decltype(input)>(input));
  auto __res__ = ::llvm::dyn_cast<ToClockOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ToClockOp ToClockOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type output, ::mlir::Value input) {
  return create(builder, builder.getLoc(), std::forward<decltype(output)>(output), std::forward<decltype(input)>(input));
}

void ToClockOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value input) {
  odsState.addOperands(input);

        ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
        if (::mlir::succeeded(ToClockOp::inferReturnTypes(odsBuilder.getContext(),
                      odsState.location, odsState.operands,
                      odsState.attributes.getDictionary(odsState.getContext()),
                      odsState.getRawProperties(),
                      odsState.regions, inferredReturnTypes)))
          odsState.addTypes(inferredReturnTypes);
        else
          ::mlir::detail::reportFatalInferReturnTypesError(odsState);
        
}

ToClockOp ToClockOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value input) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(input)>(input));
  auto __res__ = ::llvm::dyn_cast<ToClockOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ToClockOp ToClockOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value input) {
  return create(builder, builder.getLoc(), std::forward<decltype(input)>(input));
}

void ToClockOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value input) {
  odsState.addOperands(input);
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

ToClockOp ToClockOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value input) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(input)>(input));
  auto __res__ = ::llvm::dyn_cast<ToClockOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ToClockOp ToClockOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value input) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(input)>(input));
}

void ToClockOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

ToClockOp ToClockOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<ToClockOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ToClockOp ToClockOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void ToClockOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);

  ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
  if (::mlir::succeeded(ToClockOp::inferReturnTypes(odsBuilder.getContext(),
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

ToClockOp ToClockOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<ToClockOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ToClockOp ToClockOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void ToClockOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

ToClockOp ToClockOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<ToClockOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ToClockOp ToClockOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

void ToClockOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties &>(properties));
  odsState.addAttributes(discardableAttributes);

  ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
  if (::mlir::succeeded(ToClockOp::inferReturnTypes(odsBuilder.getContext(),
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

ToClockOp ToClockOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<ToClockOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ToClockOp ToClockOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult ToClockOp::verifyInvariantsImpl() {
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Seq2(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Seq1(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult ToClockOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

void ToClockOp::getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context) {
  results.add(canonicalize);
}

::llvm::LogicalResult ToClockOp::inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::PropertyRef properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes) {
  inferredReturnTypes.resize(1);
  ::mlir::Builder odsBuilder(context);
  ::mlir::Type odsInferredType0 = odsBuilder.getType<::circt::seq::ClockType>();
  inferredReturnTypes[0] = odsInferredType0;
  return ::mlir::success();
}

::mlir::ParseResult ToClockOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::OpAsmParser::UnresolvedOperand inputRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> inputOperands(&inputRawOperand, 1);  ::llvm::SMLoc inputOperandsLoc;
  (void)inputOperandsLoc;

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
  ::mlir::Type odsBuildableType0 = parser.getBuilder().getType<::circt::seq::ClockType>();
  ::mlir::Type odsBuildableType1 = parser.getBuilder().getIntegerType(1);
  result.addTypes(odsBuildableType0);
  if (parser.resolveOperands(inputOperands, odsBuildableType1, inputOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void ToClockOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter << getInput();
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
}

void ToClockOp::getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects) {
}


} // namespace circt::seq
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::seq::ToClockOp)

namespace circt::seq {


//===----------------------------------------------------------------------===//
// ::circt::seq::WritePortOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

WritePortOpGenericAdaptorBase::WritePortOpGenericAdaptorBase(WritePortOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

std::pair<unsigned, unsigned> WritePortOpGenericAdaptorBase::getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
  bool isVariadic[] = {false, true, false, false};
  int prevVariadicCount = 0;
  for (unsigned i = 0; i < index; ++i)
    if (isVariadic[i]) ++prevVariadicCount;

  // Calculate how many dynamic values a static variadic operand corresponds to.
  // This assumes all static variadic operands have the same dynamic value count.
  int variadicSize = (odsOperandsSize - 3) / 1;
  // `index` passed in as the parameter is the static index which counts each
  // operand (variadic or not) as size 1. So here for each previous static variadic
  // operand, we need to offset by (variadicSize - 1) to get where the dynamic
  // value pack for this static operand starts.
  int start = index + (variadicSize - 1) * prevVariadicCount;
  int size = isVariadic[index] ? variadicSize : 1;
  return {start, size};
}

uint64_t WritePortOpGenericAdaptorBase::getLatency() {
  auto attr = getLatencyAttr();
  return attr.getValue().getZExtValue();
}


} // namespace detail
WritePortOpAdaptor::WritePortOpAdaptor(WritePortOp op) : WritePortOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult WritePortOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_latency = getProperties().latency; (void)tblgen_latency;
  if (!tblgen_latency) return emitError(loc, "'seq.write' op requires attribute 'latency'");

  if (tblgen_latency && !(((::llvm::isa<::mlir::IntegerAttr>(tblgen_latency))) && ((::llvm::cast<::mlir::IntegerAttr>(tblgen_latency).getType().isSignlessInteger(64)))))
    return emitError(loc, "'seq.write' op attribute 'latency' failed to satisfy constraint: 64-bit signless integer attribute");
  return ::mlir::success();
}

std::pair<unsigned, unsigned> WritePortOp::getODSOperandIndexAndLength(unsigned index) {
  bool isVariadic[] = {false, true, false, false};
  int prevVariadicCount = 0;
  for (unsigned i = 0; i < index; ++i)
    if (isVariadic[i]) ++prevVariadicCount;

  // Calculate how many dynamic values a static variadic operand corresponds to.
  // This assumes all static variadic operands have the same dynamic value count.
  int variadicSize = (getOperation()->getNumOperands() - 3) / 1;
  // `index` passed in as the parameter is the static index which counts each
  // operand (variadic or not) as size 1. So here for each previous static variadic
  // operand, we need to offset by (variadicSize - 1) to get where the dynamic
  // value pack for this static operand starts.
  int start = index + (variadicSize - 1) * prevVariadicCount;
  int size = isVariadic[index] ? variadicSize : 1;
  return {start, size};
}

::mlir::MutableOperandRange WritePortOp::getAddressesMutable() {
  auto range = getODSOperandIndexAndLength(1);
  auto mutableRange = ::mlir::MutableOperandRange(getOperation(), range.first, range.second);
  return mutableRange;
}

::llvm::LogicalResult WritePortOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
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

::mlir::Attribute WritePortOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
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

llvm::hash_code WritePortOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.latency.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> WritePortOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "latency")
      return prop.latency;
  return std::nullopt;
}

void WritePortOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "latency") {
       prop.latency = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.latency)>>(value);
       return;
    }
}

void WritePortOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.latency) attrs.append("latency", prop.latency);
}

::llvm::LogicalResult WritePortOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getLatencyAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Seq1(attr, "latency", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult WritePortOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.latency)))
    return ::mlir::failure();
  return ::mlir::success();
}

void WritePortOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.latency);
}

uint64_t WritePortOp::getLatency() {
  auto attr = getLatencyAttr();
  return attr.getValue().getZExtValue();
}

void WritePortOp::setLatency(uint64_t attrValue) {
  getProperties().latency = ::mlir::Builder((*this)->getContext()).getIntegerAttr(::mlir::Builder((*this)->getContext()).getIntegerType(64), attrValue);
}

void WritePortOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value memory, ::mlir::ValueRange addresses, ::mlir::Value inData, ::mlir::Value wrEn, ::mlir::IntegerAttr latency) {
  odsState.addOperands(memory);
  odsState.addOperands(addresses);
  odsState.addOperands(inData);
  odsState.addOperands(wrEn);
  odsState.getOrAddProperties<Properties>().latency = latency;
}

WritePortOp WritePortOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value memory, ::mlir::ValueRange addresses, ::mlir::Value inData, ::mlir::Value wrEn, ::mlir::IntegerAttr latency) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(memory)>(memory), std::forward<decltype(addresses)>(addresses), std::forward<decltype(inData)>(inData), std::forward<decltype(wrEn)>(wrEn), std::forward<decltype(latency)>(latency));
  auto __res__ = ::llvm::dyn_cast<WritePortOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

WritePortOp WritePortOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value memory, ::mlir::ValueRange addresses, ::mlir::Value inData, ::mlir::Value wrEn, ::mlir::IntegerAttr latency) {
  return create(builder, builder.getLoc(), std::forward<decltype(memory)>(memory), std::forward<decltype(addresses)>(addresses), std::forward<decltype(inData)>(inData), std::forward<decltype(wrEn)>(wrEn), std::forward<decltype(latency)>(latency));
}

void WritePortOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value memory, ::mlir::ValueRange addresses, ::mlir::Value inData, ::mlir::Value wrEn, ::mlir::IntegerAttr latency) {
  odsState.addOperands(memory);
  odsState.addOperands(addresses);
  odsState.addOperands(inData);
  odsState.addOperands(wrEn);
  odsState.getOrAddProperties<Properties>().latency = latency;
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

WritePortOp WritePortOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value memory, ::mlir::ValueRange addresses, ::mlir::Value inData, ::mlir::Value wrEn, ::mlir::IntegerAttr latency) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(memory)>(memory), std::forward<decltype(addresses)>(addresses), std::forward<decltype(inData)>(inData), std::forward<decltype(wrEn)>(wrEn), std::forward<decltype(latency)>(latency));
  auto __res__ = ::llvm::dyn_cast<WritePortOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

WritePortOp WritePortOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value memory, ::mlir::ValueRange addresses, ::mlir::Value inData, ::mlir::Value wrEn, ::mlir::IntegerAttr latency) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(memory)>(memory), std::forward<decltype(addresses)>(addresses), std::forward<decltype(inData)>(inData), std::forward<decltype(wrEn)>(wrEn), std::forward<decltype(latency)>(latency));
}

void WritePortOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value memory, ::mlir::ValueRange addresses, ::mlir::Value inData, ::mlir::Value wrEn, uint64_t latency) {
  odsState.addOperands(memory);
  odsState.addOperands(addresses);
  odsState.addOperands(inData);
  odsState.addOperands(wrEn);
  odsState.getOrAddProperties<Properties>().latency = odsBuilder.getIntegerAttr(odsBuilder.getIntegerType(64), latency);
}

WritePortOp WritePortOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value memory, ::mlir::ValueRange addresses, ::mlir::Value inData, ::mlir::Value wrEn, uint64_t latency) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(memory)>(memory), std::forward<decltype(addresses)>(addresses), std::forward<decltype(inData)>(inData), std::forward<decltype(wrEn)>(wrEn), std::forward<decltype(latency)>(latency));
  auto __res__ = ::llvm::dyn_cast<WritePortOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

WritePortOp WritePortOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value memory, ::mlir::ValueRange addresses, ::mlir::Value inData, ::mlir::Value wrEn, uint64_t latency) {
  return create(builder, builder.getLoc(), std::forward<decltype(memory)>(memory), std::forward<decltype(addresses)>(addresses), std::forward<decltype(inData)>(inData), std::forward<decltype(wrEn)>(wrEn), std::forward<decltype(latency)>(latency));
}

void WritePortOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value memory, ::mlir::ValueRange addresses, ::mlir::Value inData, ::mlir::Value wrEn, uint64_t latency) {
  odsState.addOperands(memory);
  odsState.addOperands(addresses);
  odsState.addOperands(inData);
  odsState.addOperands(wrEn);
  odsState.getOrAddProperties<Properties>().latency = odsBuilder.getIntegerAttr(odsBuilder.getIntegerType(64), latency);
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

WritePortOp WritePortOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value memory, ::mlir::ValueRange addresses, ::mlir::Value inData, ::mlir::Value wrEn, uint64_t latency) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(memory)>(memory), std::forward<decltype(addresses)>(addresses), std::forward<decltype(inData)>(inData), std::forward<decltype(wrEn)>(wrEn), std::forward<decltype(latency)>(latency));
  auto __res__ = ::llvm::dyn_cast<WritePortOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

WritePortOp WritePortOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value memory, ::mlir::ValueRange addresses, ::mlir::Value inData, ::mlir::Value wrEn, uint64_t latency) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(memory)>(memory), std::forward<decltype(addresses)>(addresses), std::forward<decltype(inData)>(inData), std::forward<decltype(wrEn)>(wrEn), std::forward<decltype(latency)>(latency));
}

void WritePortOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() >= 3u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<WritePortOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

WritePortOp WritePortOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<WritePortOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

WritePortOp WritePortOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void WritePortOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() >= 3u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

WritePortOp WritePortOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<WritePortOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

WritePortOp WritePortOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult WritePortOp::verifyInvariantsImpl() {
  auto tblgen_latency = getProperties().latency; (void)tblgen_latency;
  if (!tblgen_latency) return emitOpError("requires attribute 'latency'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Seq1(*this, tblgen_latency, "latency")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Seq7(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSOperands(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Seq9(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup2 = getODSOperands(2);

    for (auto v : valueGroup2) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Seq3(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup3 = getODSOperands(3);

    for (auto v : valueGroup3) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Seq2(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  if (!((std::equal_to<>()(llvm::cast<HLMemType>((*this->getODSOperands(0).begin()).getType()).getElementType(), (*this->getODSOperands(2).begin()).getType()))))
    return emitOpError("failed to verify that type of 'value' matches element type of 'hlmemvalue'");
  if (!((isValidIndexValues((*this->getODSOperands(0).begin()), this->getODSOperands(1)))))
    return emitOpError("failed to verify that address bit widths should be identical to the clog2 of the shape of the HLMemType");
  return ::mlir::success();
}

::llvm::LogicalResult WritePortOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::llvm::LogicalResult WritePortOp::setPropertiesFromParsedAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
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

    auto &propStorage = prop.latency;
    auto latencyAttrName = ::mlir::StringAttr::get(ctx, "latency");
    auto attr = dict.get(latencyAttrName);
    usedKeys.insert(latencyAttrName);
    if (attr || /*isRequired=*/true) {
      if (!attr) {
        emitError() << "expected key entry for latency in DictionaryAttr to set "
                   "Properties.";
        return ::mlir::failure();
      }
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `latency` in property conversion: " << attr;
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


} // namespace circt::seq
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::seq::WritePortOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::seq::detail::WritePortOpGenericAdaptorBase::Properties)

namespace circt::seq {


//===----------------------------------------------------------------------===//
// ::circt::seq::YieldOp definitions
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

::mlir::MutableOperandRange YieldOp::getOperandsMutable() {
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

void YieldOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands) {
  odsState.addOperands(operands);
}

YieldOp YieldOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands));
  auto __res__ = ::llvm::dyn_cast<YieldOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

YieldOp YieldOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands));
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
      if (::mlir::failed(__mlir_ods_local_type_constraint_Seq10(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult YieldOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult YieldOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::llvm::SmallVector<::mlir::OpAsmParser::UnresolvedOperand, 4> operandsOperands;
  ::llvm::SMLoc operandsOperandsLoc;
  (void)operandsOperandsLoc;
  ::llvm::SmallVector<::mlir::Type, 1> operandsTypes;
  {
    auto loc = parser.getCurrentLocation();(void)loc;
    if (parser.parseOptionalAttrDict(result.attributes))
      return ::mlir::failure();
    if (failed(verifyInherentAttrs(result.name, result.attributes, [&]() {
        return parser.emitError(loc) << "'" << result.name.getStringRef() << "' op ";
      })))
      return ::mlir::failure();
  }

  operandsOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperandList(operandsOperands))
    return ::mlir::failure();
  if (!operandsOperands.empty()) {
  if (parser.parseColon())
    return ::mlir::failure();

  if (parser.parseTypeList(operandsTypes))
    return ::mlir::failure();
  }
  if (parser.resolveOperands(operandsOperands, operandsTypes, operandsOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void YieldOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  if (!getOperands().empty()) {
    _odsPrinter << ' ';
    _odsPrinter << getOperands();
    _odsPrinter << ' ' << ":";
    _odsPrinter << ' ';
    _odsPrinter << getOperands().getTypes();
  }
}

void YieldOp::getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects) {
}


} // namespace circt::seq
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::seq::YieldOp)


#endif // GET_OP_CLASSES

