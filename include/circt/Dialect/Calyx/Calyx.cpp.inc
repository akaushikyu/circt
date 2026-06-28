/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Op Definitions                                                             *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: Calyx.td                                                             *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

#ifdef GET_OP_LIST
#undef GET_OP_LIST

::circt::calyx::AddFOpIEEE754,
::circt::calyx::AddLibOp,
::circt::calyx::AndLibOp,
::circt::calyx::AssignOp,
::circt::calyx::CombComponentOp,
::circt::calyx::CombGroupOp,
::circt::calyx::CompareFOpIEEE754,
::circt::calyx::ComponentOp,
::circt::calyx::ConstantOp,
::circt::calyx::ControlOp,
::circt::calyx::CycleOp,
::circt::calyx::DivSPipeLibOp,
::circt::calyx::DivSqrtOpIEEE754,
::circt::calyx::DivUPipeLibOp,
::circt::calyx::EnableOp,
::circt::calyx::EqLibOp,
::circt::calyx::ExtSILibOp,
::circt::calyx::FpToIntOpIEEE754,
::circt::calyx::GeLibOp,
::circt::calyx::GroupDoneOp,
::circt::calyx::GroupGoOp,
::circt::calyx::GroupOp,
::circt::calyx::GtLibOp,
::circt::calyx::IfOp,
::circt::calyx::InstanceOp,
::circt::calyx::IntToFpOpIEEE754,
::circt::calyx::InvokeOp,
::circt::calyx::LeLibOp,
::circt::calyx::LshLibOp,
::circt::calyx::LtLibOp,
::circt::calyx::MemoryOp,
::circt::calyx::MulFOpIEEE754,
::circt::calyx::MultPipeLibOp,
::circt::calyx::MuxLibOp,
::circt::calyx::NeqLibOp,
::circt::calyx::NotLibOp,
::circt::calyx::OrLibOp,
::circt::calyx::PadLibOp,
::circt::calyx::ParOp,
::circt::calyx::PrimitiveOp,
::circt::calyx::RegisterOp,
::circt::calyx::RemSPipeLibOp,
::circt::calyx::RemUPipeLibOp,
::circt::calyx::RepeatOp,
::circt::calyx::RshLibOp,
::circt::calyx::SeqLibOp,
::circt::calyx::SeqMemoryOp,
::circt::calyx::SeqOp,
::circt::calyx::SgeLibOp,
::circt::calyx::SgtLibOp,
::circt::calyx::ShruLibOp,
::circt::calyx::SleLibOp,
::circt::calyx::SliceLibOp,
::circt::calyx::SltLibOp,
::circt::calyx::SneqLibOp,
::circt::calyx::SrshLibOp,
::circt::calyx::StaticGroupOp,
::circt::calyx::StaticIfOp,
::circt::calyx::StaticParOp,
::circt::calyx::StaticRepeatOp,
::circt::calyx::StaticSeqOp,
::circt::calyx::SubLibOp,
::circt::calyx::UndefLibOp,
::circt::calyx::UndefinedOp,
::circt::calyx::WhileOp,
::circt::calyx::WireLibOp,
::circt::calyx::WiresOp,
::circt::calyx::XorLibOp
#endif // GET_OP_LIST

#ifdef GET_OP_CLASSES
#undef GET_OP_CLASSES


//===----------------------------------------------------------------------===//
// Local Utility Method Definitions
//===----------------------------------------------------------------------===//


static ::llvm::LogicalResult __mlir_ods_local_type_constraint_Calyx1(
    ::mlir::Operation *op, ::mlir::Type type, ::llvm::StringRef valueKind,
    unsigned valueIndex) {
  if (!((type.isSignlessInteger(1)))) {
    return op->emitOpError(valueKind) << " #" << valueIndex
        << " must be 1-bit signless integer, but got " << type;
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_type_constraint_Calyx2(
    ::mlir::Operation *op, ::mlir::Type type, ::llvm::StringRef valueKind,
    unsigned valueIndex) {
  if (!((type.isSignlessInteger()))) {
    return op->emitOpError(valueKind) << " #" << valueIndex
        << " must be signless integer, but got " << type;
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_type_constraint_Calyx3(
    ::mlir::Operation *op, ::mlir::Type type, ::llvm::StringRef valueKind,
    unsigned valueIndex) {
  if (!((type.isSignlessInteger(3)))) {
    return op->emitOpError(valueKind) << " #" << valueIndex
        << " must be 3-bit signless integer, but got " << type;
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_type_constraint_Calyx4(
    ::mlir::Operation *op, ::mlir::Type type, ::llvm::StringRef valueKind,
    unsigned valueIndex) {
  if (!((type.isSignlessInteger(5)))) {
    return op->emitOpError(valueKind) << " #" << valueIndex
        << " must be 5-bit signless integer, but got " << type;
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_type_constraint_Calyx5(
    ::mlir::Operation *op, ::mlir::Type type, ::llvm::StringRef valueKind,
    unsigned valueIndex) {
  if (!(!((::llvm::isa<::mlir::TokenType>(type))))) {
    return op->emitOpError(valueKind) << " #" << valueIndex
        << " must be any non-token type, but got " << type;
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_type_constraint_Calyx6(
    ::mlir::Operation *op, ::mlir::Type type, ::llvm::StringRef valueKind,
    unsigned valueIndex) {
  if (!((::llvm::isa<::mlir::IntegerType>(type)))) {
    return op->emitOpError(valueKind) << " #" << valueIndex
        << " must be integer, but got " << type;
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_type_constraint_Calyx7(
    ::mlir::Operation *op, ::mlir::Type type, ::llvm::StringRef valueKind,
    unsigned valueIndex) {
  if (!(!((::llvm::isa<::mlir::TokenType>(type))))) {
    return op->emitOpError(valueKind) << " #" << valueIndex
        << " must be variadic of any non-token type, but got " << type;
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_type_constraint_Calyx8(
    ::mlir::Operation *op, ::mlir::Type type, ::llvm::StringRef valueKind,
    unsigned valueIndex) {
  if (!((type.isSignlessInteger()))) {
    return op->emitOpError(valueKind) << " #" << valueIndex
        << " must be variadic of signless integer, but got " << type;
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_Calyx1(
    ::mlir::Attribute attr, ::llvm::StringRef attrName, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  if (attr && !((::llvm::isa<::mlir::StringAttr>(attr))))
    return emitError() << "attribute '" << attrName
        << "' failed to satisfy constraint: string attribute";
  return ::mlir::success();
}
static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_Calyx1(
    ::mlir::Operation *op, ::mlir::Attribute attr, ::llvm::StringRef attrName) {
  return __mlir_ods_local_attr_constraint_Calyx1(attr, attrName, [op]() {
    return op->emitOpError();
  });
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_Calyx2(
    ::mlir::Attribute attr, ::llvm::StringRef attrName, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  if (attr && !(((::llvm::isa<::mlir::TypeAttr>(attr))) && ((::llvm::isa<::mlir::FunctionType>(::llvm::cast<::mlir::TypeAttr>(attr).getValue()))) && ((::llvm::isa<::mlir::FunctionType>(::llvm::cast<::mlir::TypeAttr>(attr).getValue())))))
    return emitError() << "attribute '" << attrName
        << "' failed to satisfy constraint: type attribute of function type";
  return ::mlir::success();
}
static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_Calyx2(
    ::mlir::Operation *op, ::mlir::Attribute attr, ::llvm::StringRef attrName) {
  return __mlir_ods_local_attr_constraint_Calyx2(attr, attrName, [op]() {
    return op->emitOpError();
  });
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_Calyx3(
    ::mlir::Attribute attr, ::llvm::StringRef attrName, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  if (attr && !(((::llvm::isa<::mlir::ArrayAttr>(attr))) && (::llvm::all_of(::llvm::cast<::mlir::ArrayAttr>(attr), [&](::mlir::Attribute attr) { return attr && ((::llvm::isa<::mlir::DictionaryAttr>(attr))); }))))
    return emitError() << "attribute '" << attrName
        << "' failed to satisfy constraint: Array of dictionary attributes";
  return ::mlir::success();
}
static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_Calyx3(
    ::mlir::Operation *op, ::mlir::Attribute attr, ::llvm::StringRef attrName) {
  return __mlir_ods_local_attr_constraint_Calyx3(attr, attrName, [op]() {
    return op->emitOpError();
  });
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_Calyx4(
    ::mlir::Attribute attr, ::llvm::StringRef attrName, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  if (attr && !((::llvm::isa<::mlir::ArrayAttr>(attr))))
    return emitError() << "attribute '" << attrName
        << "' failed to satisfy constraint: array attribute";
  return ::mlir::success();
}
static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_Calyx4(
    ::mlir::Operation *op, ::mlir::Attribute attr, ::llvm::StringRef attrName) {
  return __mlir_ods_local_attr_constraint_Calyx4(attr, attrName, [op]() {
    return op->emitOpError();
  });
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_Calyx5(
    ::mlir::Attribute attr, ::llvm::StringRef attrName, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  if (attr && !((::llvm::isa<::mlir::IntegerAttr>(attr))))
    return emitError() << "attribute '" << attrName
        << "' failed to satisfy constraint: arbitrary integer attribute";
  return ::mlir::success();
}
static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_Calyx5(
    ::mlir::Operation *op, ::mlir::Attribute attr, ::llvm::StringRef attrName) {
  return __mlir_ods_local_attr_constraint_Calyx5(attr, attrName, [op]() {
    return op->emitOpError();
  });
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_Calyx6(
    ::mlir::Attribute attr, ::llvm::StringRef attrName, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  if (attr && !((::llvm::isa<::mlir::TypedAttr>(attr))))
    return emitError() << "attribute '" << attrName
        << "' failed to satisfy constraint: TypedAttr instance";
  return ::mlir::success();
}
static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_Calyx6(
    ::mlir::Operation *op, ::mlir::Attribute attr, ::llvm::StringRef attrName) {
  return __mlir_ods_local_attr_constraint_Calyx6(attr, attrName, [op]() {
    return op->emitOpError();
  });
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_Calyx7(
    ::mlir::Attribute attr, ::llvm::StringRef attrName, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  if (attr && !(((::llvm::isa<::mlir::IntegerAttr>(attr))) && ((::llvm::cast<::mlir::IntegerAttr>(attr).getType().isSignlessInteger(32)))))
    return emitError() << "attribute '" << attrName
        << "' failed to satisfy constraint: 32-bit signless integer attribute";
  return ::mlir::success();
}
static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_Calyx7(
    ::mlir::Operation *op, ::mlir::Attribute attr, ::llvm::StringRef attrName) {
  return __mlir_ods_local_attr_constraint_Calyx7(attr, attrName, [op]() {
    return op->emitOpError();
  });
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_Calyx8(
    ::mlir::Attribute attr, ::llvm::StringRef attrName, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  if (attr && !((::llvm::isa<::mlir::FlatSymbolRefAttr>(attr))))
    return emitError() << "attribute '" << attrName
        << "' failed to satisfy constraint: flat symbol reference attribute";
  return ::mlir::success();
}
static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_Calyx8(
    ::mlir::Operation *op, ::mlir::Attribute attr, ::llvm::StringRef attrName) {
  return __mlir_ods_local_attr_constraint_Calyx8(attr, attrName, [op]() {
    return op->emitOpError();
  });
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_Calyx9(
    ::mlir::Attribute attr, ::llvm::StringRef attrName, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  if (attr && !(((::llvm::isa<::mlir::IntegerAttr>(attr))) && ((::llvm::cast<::mlir::IntegerAttr>(attr).getType().isSignlessInteger(64)))))
    return emitError() << "attribute '" << attrName
        << "' failed to satisfy constraint: 64-bit signless integer attribute";
  return ::mlir::success();
}
static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_Calyx9(
    ::mlir::Operation *op, ::mlir::Attribute attr, ::llvm::StringRef attrName) {
  return __mlir_ods_local_attr_constraint_Calyx9(attr, attrName, [op]() {
    return op->emitOpError();
  });
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_Calyx10(
    ::mlir::Attribute attr, ::llvm::StringRef attrName, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  if (attr && !(((::llvm::isa<::mlir::ArrayAttr>(attr))) && (::llvm::all_of(::llvm::cast<::mlir::ArrayAttr>(attr), [&](::mlir::Attribute attr) { return attr && ((llvm::isa<hw::ParamDeclAttr>(attr))); }))))
    return emitError() << "attribute '" << attrName
        << "' failed to satisfy constraint: parameter array";
  return ::mlir::success();
}
static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_Calyx10(
    ::mlir::Operation *op, ::mlir::Attribute attr, ::llvm::StringRef attrName) {
  return __mlir_ods_local_attr_constraint_Calyx10(attr, attrName, [op]() {
    return op->emitOpError();
  });
}

static ::llvm::LogicalResult __mlir_ods_local_region_constraint_Calyx1(
    ::mlir::Operation *op, ::mlir::Region &region, ::llvm::StringRef regionName,
    unsigned regionIndex) {
  if (!((::llvm::hasNItems(region, 1)))) {
    return op->emitOpError("region #") << regionIndex
        << (regionName.empty() ? " " : " ('" + regionName + "') ")
        << "failed to verify constraint: region with 1 blocks";
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_region_constraint_Calyx2(
    ::mlir::Operation *op, ::mlir::Region &region, ::llvm::StringRef regionName,
    unsigned regionIndex) {
  if (!((true))) {
    return op->emitOpError("region #") << regionIndex
        << (regionName.empty() ? " " : " ('" + regionName + "') ")
        << "failed to verify constraint: any region";
  }
  return ::mlir::success();
}
namespace circt::calyx {


//===----------------------------------------------------------------------===//
// ::circt::calyx::AddFOpIEEE754 definitions
//===----------------------------------------------------------------------===//

namespace detail {

AddFOpIEEE754GenericAdaptorBase::AddFOpIEEE754GenericAdaptorBase(AddFOpIEEE754 op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::llvm::StringRef AddFOpIEEE754GenericAdaptorBase::getSymName() {
  auto attr = getSymNameAttr();
  return attr.getValue();
}


} // namespace detail
AddFOpIEEE754Adaptor::AddFOpIEEE754Adaptor(AddFOpIEEE754 op) : AddFOpIEEE754GenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult AddFOpIEEE754Adaptor::verify(::mlir::Location loc) {
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;
  if (!tblgen_sym_name) return emitError(loc, "'calyx.ieee754.add' op requires attribute 'sym_name'");

  if (tblgen_sym_name && !((::llvm::isa<::mlir::StringAttr>(tblgen_sym_name))))
    return emitError(loc, "'calyx.ieee754.add' op attribute 'sym_name' failed to satisfy constraint: string attribute");
  return ::mlir::success();
}

::llvm::LogicalResult AddFOpIEEE754::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
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

::mlir::Attribute AddFOpIEEE754::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
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

llvm::hash_code AddFOpIEEE754::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.sym_name.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> AddFOpIEEE754::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "sym_name")
      return prop.sym_name;
  return std::nullopt;
}

void AddFOpIEEE754::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "sym_name") {
       prop.sym_name = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.sym_name)>>(value);
       return;
    }
}

void AddFOpIEEE754::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.sym_name) attrs.append("sym_name", prop.sym_name);
}

::llvm::LogicalResult AddFOpIEEE754::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getSymNameAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Calyx1(attr, "sym_name", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult AddFOpIEEE754::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.sym_name)))
    return ::mlir::failure();
  return ::mlir::success();
}

void AddFOpIEEE754::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.sym_name);
}

::llvm::StringRef AddFOpIEEE754::getSymName() {
  auto attr = getSymNameAttr();
  return attr.getValue();
}

void AddFOpIEEE754::setSymName(::llvm::StringRef attrValue) {
  getProperties().sym_name = ::mlir::Builder((*this)->getContext()).getStringAttr(attrValue);
}

void AddFOpIEEE754::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, StringRef sym_name, ::mlir::TypeRange resultTypes) {
      odsState.addAttribute(mlir::SymbolTable::getSymbolAttrName(), odsBuilder.getStringAttr(sym_name));
      odsState.addTypes(resultTypes);
    
}

AddFOpIEEE754 AddFOpIEEE754::create(::mlir::OpBuilder &builder, ::mlir::Location location, StringRef sym_name, ::mlir::TypeRange resultTypes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(resultTypes)>(resultTypes));
  auto __res__ = ::llvm::dyn_cast<AddFOpIEEE754>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

AddFOpIEEE754 AddFOpIEEE754::create(::mlir::ImplicitLocOpBuilder &builder, StringRef sym_name, ::mlir::TypeRange resultTypes) {
  return create(builder, builder.getLoc(), std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(resultTypes)>(resultTypes));
}

::llvm::LogicalResult AddFOpIEEE754::verifyInvariantsImpl() {
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;
  if (!tblgen_sym_name) return emitOpError("requires attribute 'sym_name'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Calyx1(*this, tblgen_sym_name, "sym_name")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx1(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSResults(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx1(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup2 = getODSResults(2);

    for (auto v : valueGroup2) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx1(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup3 = getODSResults(3);

    for (auto v : valueGroup3) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx1(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup4 = getODSResults(4);

    for (auto v : valueGroup4) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx1(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup5 = getODSResults(5);

    for (auto v : valueGroup5) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx2(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup6 = getODSResults(6);

    for (auto v : valueGroup6) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx2(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup7 = getODSResults(7);

    for (auto v : valueGroup7) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx3(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup8 = getODSResults(8);

    for (auto v : valueGroup8) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx2(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup9 = getODSResults(9);

    for (auto v : valueGroup9) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx4(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup10 = getODSResults(10);

    for (auto v : valueGroup10) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx1(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  if (!((std::equal_to<>()( (*this->getODSResults(5).begin()).getType() , (*this->getODSResults(8).begin()).getType()))))
    return emitOpError("failed to verify that lhs and rhs types should be equivalent");
  if (!((std::equal_to<>()( (*this->getODSResults(5).begin()).getType() , (*this->getODSResults(6).begin()).getType()))))
    return emitOpError("failed to verify that lhs and rhs types should be equivalent");
  return ::mlir::success();
}

::llvm::LogicalResult AddFOpIEEE754::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult AddFOpIEEE754::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::StringAttr sym_nameAttr;
  ::llvm::SmallVector<::mlir::Type, 1> allResultTypes;

  if (parser.parseSymbolName(sym_nameAttr))
    return ::mlir::failure();
  if (sym_nameAttr) result.getOrAddProperties<AddFOpIEEE754::Properties>().sym_name = sym_nameAttr;
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

  if (parser.parseTypeList(allResultTypes))
    return ::mlir::failure();
  result.addTypes(allResultTypes);
  return ::mlir::success();
}

void AddFOpIEEE754::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter.printSymbolName(getSymNameAttr().getValue());
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("sym_name");
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
  _odsPrinter << getOperation()->getResultTypes();
}

SmallVector<StringRef> AddFOpIEEE754::portNames() {
  return {clkPort, resetPort, goPort, "control", "subOp",
          "left", "right", "roundingMode", "out", "exceptionalFlags", donePort
  };
}

SmallVector<Direction> AddFOpIEEE754::portDirections() {
  return {Input, Input, Input, Input, Input, Input, Input, Input, Output, Output, Output};
}

void AddFOpIEEE754::getAsmResultNames(OpAsmSetValueNameFn setNameFn) {
  getCellAsmResultNames(setNameFn, *this, this->portNames());
}

bool AddFOpIEEE754::isCombinational() { return false; }

SmallVector<DictionaryAttr> AddFOpIEEE754::portAttributes() {
  IntegerAttr isSet = IntegerAttr::get(IntegerType::get(getContext(), 1), 1);
  NamedAttrList go, clk, reset, done;
  go.append(goPort, isSet);
  clk.append(clkPort, isSet);
  reset.append(resetPort, isSet);
  done.append(donePort, isSet);
  return {clk.getDictionary(getContext()), reset.getDictionary(getContext()),
          go.getDictionary(getContext()), DictionaryAttr::get(getContext()),
          DictionaryAttr::get(getContext()), DictionaryAttr::get(getContext()),
          DictionaryAttr::get(getContext()), DictionaryAttr::get(getContext()),
          DictionaryAttr::get(getContext()), done.getDictionary(getContext()),
          DictionaryAttr::get(getContext())
  };
}

} // namespace circt::calyx
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::calyx::AddFOpIEEE754)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::calyx::detail::AddFOpIEEE754GenericAdaptorBase::Properties)

namespace circt::calyx {


//===----------------------------------------------------------------------===//
// ::circt::calyx::AddLibOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

AddLibOpGenericAdaptorBase::AddLibOpGenericAdaptorBase(AddLibOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::llvm::StringRef AddLibOpGenericAdaptorBase::getSymName() {
  auto attr = getSymNameAttr();
  return attr.getValue();
}


} // namespace detail
AddLibOpAdaptor::AddLibOpAdaptor(AddLibOp op) : AddLibOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult AddLibOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;
  if (!tblgen_sym_name) return emitError(loc, "'calyx.std_add' op requires attribute 'sym_name'");

  if (tblgen_sym_name && !((::llvm::isa<::mlir::StringAttr>(tblgen_sym_name))))
    return emitError(loc, "'calyx.std_add' op attribute 'sym_name' failed to satisfy constraint: string attribute");
  return ::mlir::success();
}

::llvm::LogicalResult AddLibOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
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

::mlir::Attribute AddLibOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
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

llvm::hash_code AddLibOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.sym_name.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> AddLibOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "sym_name")
      return prop.sym_name;
  return std::nullopt;
}

void AddLibOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "sym_name") {
       prop.sym_name = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.sym_name)>>(value);
       return;
    }
}

void AddLibOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.sym_name) attrs.append("sym_name", prop.sym_name);
}

::llvm::LogicalResult AddLibOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getSymNameAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Calyx1(attr, "sym_name", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult AddLibOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.sym_name)))
    return ::mlir::failure();
  return ::mlir::success();
}

void AddLibOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.sym_name);
}

::llvm::StringRef AddLibOp::getSymName() {
  auto attr = getSymNameAttr();
  return attr.getValue();
}

void AddLibOp::setSymName(::llvm::StringRef attrValue) {
  getProperties().sym_name = ::mlir::Builder((*this)->getContext()).getStringAttr(attrValue);
}

void AddLibOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, StringRef sym_name, ::mlir::TypeRange resultTypes) {
      odsState.addAttribute(mlir::SymbolTable::getSymbolAttrName(), odsBuilder.getStringAttr(sym_name));
      odsState.addTypes(resultTypes);
    
}

AddLibOp AddLibOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, StringRef sym_name, ::mlir::TypeRange resultTypes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(resultTypes)>(resultTypes));
  auto __res__ = ::llvm::dyn_cast<AddLibOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

AddLibOp AddLibOp::create(::mlir::ImplicitLocOpBuilder &builder, StringRef sym_name, ::mlir::TypeRange resultTypes) {
  return create(builder, builder.getLoc(), std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(resultTypes)>(resultTypes));
}

::llvm::LogicalResult AddLibOp::verifyInvariantsImpl() {
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;
  if (!tblgen_sym_name) return emitOpError("requires attribute 'sym_name'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Calyx1(*this, tblgen_sym_name, "sym_name")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx5(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSResults(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx5(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup2 = getODSResults(2);

    for (auto v : valueGroup2) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx5(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  if (!((std::equal_to<>()( (*this->getODSResults(0).begin()).getType() , (*this->getODSResults(2).begin()).getType()))))
    return emitOpError("failed to verify that lhs and rhs types should be equivalent");
  if (!((std::equal_to<>()( (*this->getODSResults(0).begin()).getType() , (*this->getODSResults(1).begin()).getType()))))
    return emitOpError("failed to verify that lhs and rhs types should be equivalent");
  return ::mlir::success();
}

::llvm::LogicalResult AddLibOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult AddLibOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::StringAttr sym_nameAttr;
  ::llvm::SmallVector<::mlir::Type, 1> allResultTypes;

  if (parser.parseSymbolName(sym_nameAttr))
    return ::mlir::failure();
  if (sym_nameAttr) result.getOrAddProperties<AddLibOp::Properties>().sym_name = sym_nameAttr;
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

  if (parser.parseTypeList(allResultTypes))
    return ::mlir::failure();
  result.addTypes(allResultTypes);
  return ::mlir::success();
}

void AddLibOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter.printSymbolName(getSymNameAttr().getValue());
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("sym_name");
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
  _odsPrinter << getOperation()->getResultTypes();
}


} // namespace circt::calyx
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::calyx::AddLibOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::calyx::detail::AddLibOpGenericAdaptorBase::Properties)

namespace circt::calyx {


//===----------------------------------------------------------------------===//
// ::circt::calyx::AndLibOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

AndLibOpGenericAdaptorBase::AndLibOpGenericAdaptorBase(AndLibOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::llvm::StringRef AndLibOpGenericAdaptorBase::getSymName() {
  auto attr = getSymNameAttr();
  return attr.getValue();
}


} // namespace detail
AndLibOpAdaptor::AndLibOpAdaptor(AndLibOp op) : AndLibOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult AndLibOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;
  if (!tblgen_sym_name) return emitError(loc, "'calyx.std_and' op requires attribute 'sym_name'");

  if (tblgen_sym_name && !((::llvm::isa<::mlir::StringAttr>(tblgen_sym_name))))
    return emitError(loc, "'calyx.std_and' op attribute 'sym_name' failed to satisfy constraint: string attribute");
  return ::mlir::success();
}

::llvm::LogicalResult AndLibOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
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

::mlir::Attribute AndLibOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
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

llvm::hash_code AndLibOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.sym_name.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> AndLibOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "sym_name")
      return prop.sym_name;
  return std::nullopt;
}

void AndLibOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "sym_name") {
       prop.sym_name = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.sym_name)>>(value);
       return;
    }
}

void AndLibOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.sym_name) attrs.append("sym_name", prop.sym_name);
}

::llvm::LogicalResult AndLibOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getSymNameAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Calyx1(attr, "sym_name", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult AndLibOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.sym_name)))
    return ::mlir::failure();
  return ::mlir::success();
}

void AndLibOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.sym_name);
}

::llvm::StringRef AndLibOp::getSymName() {
  auto attr = getSymNameAttr();
  return attr.getValue();
}

void AndLibOp::setSymName(::llvm::StringRef attrValue) {
  getProperties().sym_name = ::mlir::Builder((*this)->getContext()).getStringAttr(attrValue);
}

void AndLibOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, StringRef sym_name, ::mlir::TypeRange resultTypes) {
      odsState.addAttribute(mlir::SymbolTable::getSymbolAttrName(), odsBuilder.getStringAttr(sym_name));
      odsState.addTypes(resultTypes);
    
}

AndLibOp AndLibOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, StringRef sym_name, ::mlir::TypeRange resultTypes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(resultTypes)>(resultTypes));
  auto __res__ = ::llvm::dyn_cast<AndLibOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

AndLibOp AndLibOp::create(::mlir::ImplicitLocOpBuilder &builder, StringRef sym_name, ::mlir::TypeRange resultTypes) {
  return create(builder, builder.getLoc(), std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(resultTypes)>(resultTypes));
}

::llvm::LogicalResult AndLibOp::verifyInvariantsImpl() {
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;
  if (!tblgen_sym_name) return emitOpError("requires attribute 'sym_name'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Calyx1(*this, tblgen_sym_name, "sym_name")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx5(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSResults(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx5(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup2 = getODSResults(2);

    for (auto v : valueGroup2) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx5(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  if (!((std::equal_to<>()( (*this->getODSResults(0).begin()).getType() , (*this->getODSResults(2).begin()).getType()))))
    return emitOpError("failed to verify that lhs and rhs types should be equivalent");
  if (!((std::equal_to<>()( (*this->getODSResults(0).begin()).getType() , (*this->getODSResults(1).begin()).getType()))))
    return emitOpError("failed to verify that lhs and rhs types should be equivalent");
  return ::mlir::success();
}

::llvm::LogicalResult AndLibOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult AndLibOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::StringAttr sym_nameAttr;
  ::llvm::SmallVector<::mlir::Type, 1> allResultTypes;

  if (parser.parseSymbolName(sym_nameAttr))
    return ::mlir::failure();
  if (sym_nameAttr) result.getOrAddProperties<AndLibOp::Properties>().sym_name = sym_nameAttr;
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

  if (parser.parseTypeList(allResultTypes))
    return ::mlir::failure();
  result.addTypes(allResultTypes);
  return ::mlir::success();
}

void AndLibOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter.printSymbolName(getSymNameAttr().getValue());
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("sym_name");
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
  _odsPrinter << getOperation()->getResultTypes();
}


} // namespace circt::calyx
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::calyx::AndLibOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::calyx::detail::AndLibOpGenericAdaptorBase::Properties)

namespace circt::calyx {


//===----------------------------------------------------------------------===//
// ::circt::calyx::AssignOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

AssignOpGenericAdaptorBase::AssignOpGenericAdaptorBase(AssignOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

std::pair<unsigned, unsigned> AssignOpGenericAdaptorBase::getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
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


} // namespace detail
AssignOpAdaptor::AssignOpAdaptor(AssignOp op) : AssignOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult AssignOpAdaptor::verify(::mlir::Location loc) {
  return ::mlir::success();
}

std::pair<unsigned, unsigned> AssignOp::getODSOperandIndexAndLength(unsigned index) {
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

::mlir::MutableOperandRange AssignOp::getGuardMutable() {
  auto range = getODSOperandIndexAndLength(2);
  auto mutableRange = ::mlir::MutableOperandRange(getOperation(), range.first, range.second);
  return mutableRange;
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

void AssignOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value dest, Value src) {
      odsState.addOperands({dest, src});
    
}

AssignOp AssignOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, Value dest, Value src) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(dest)>(dest), std::forward<decltype(src)>(src));
  auto __res__ = ::llvm::dyn_cast<AssignOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

AssignOp AssignOp::create(::mlir::ImplicitLocOpBuilder &builder, Value dest, Value src) {
  return create(builder, builder.getLoc(), std::forward<decltype(dest)>(dest), std::forward<decltype(src)>(src));
}

void AssignOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value dest, ::mlir::Value src, /*optional*/::mlir::Value guard) {
  odsState.addOperands(dest);
  odsState.addOperands(src);
  if (guard)
    odsState.addOperands(guard);
}

AssignOp AssignOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value dest, ::mlir::Value src, /*optional*/::mlir::Value guard) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(dest)>(dest), std::forward<decltype(src)>(src), std::forward<decltype(guard)>(guard));
  auto __res__ = ::llvm::dyn_cast<AssignOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

AssignOp AssignOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value dest, ::mlir::Value src, /*optional*/::mlir::Value guard) {
  return create(builder, builder.getLoc(), std::forward<decltype(dest)>(dest), std::forward<decltype(src)>(src), std::forward<decltype(guard)>(guard));
}

void AssignOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value dest, ::mlir::Value src, /*optional*/::mlir::Value guard) {
  odsState.addOperands(dest);
  odsState.addOperands(src);
  if (guard)
    odsState.addOperands(guard);
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

AssignOp AssignOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value dest, ::mlir::Value src, /*optional*/::mlir::Value guard) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(dest)>(dest), std::forward<decltype(src)>(src), std::forward<decltype(guard)>(guard));
  auto __res__ = ::llvm::dyn_cast<AssignOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

AssignOp AssignOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value dest, ::mlir::Value src, /*optional*/::mlir::Value guard) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(dest)>(dest), std::forward<decltype(src)>(src), std::forward<decltype(guard)>(guard));
}

void AssignOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() >= 2u && "mismatched number of parameters");
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
  assert(operands.size() >= 2u && "mismatched number of parameters");
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
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx5(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSOperands(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx5(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup2 = getODSOperands(2);

    if (valueGroup2.size() > 1) {
      return emitOpError("operand group starting at #") << index
          << " requires 0 or 1 element, but found " << valueGroup2.size();
    }

    for (auto v : valueGroup2) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  if (!((std::equal_to<>()( (*this->getODSOperands(0).begin()).getType() , (*this->getODSOperands(1).begin()).getType()))))
    return emitOpError("failed to verify that lhs and rhs types should be equivalent");
  return ::mlir::success();
}

::llvm::LogicalResult AssignOp::verifyInvariants() {
  if(::mlir::succeeded(verifyInvariantsImpl()) && ::mlir::succeeded(verify()))
    return ::mlir::success();
  return ::mlir::failure();
}

::llvm::LogicalResult AssignOp::setPropertiesFromParsedAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
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


} // namespace circt::calyx
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::calyx::AssignOp)

namespace circt::calyx {


//===----------------------------------------------------------------------===//
// ::circt::calyx::CombComponentOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

CombComponentOpGenericAdaptorBase::CombComponentOpGenericAdaptorBase(CombComponentOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::mlir::FunctionType CombComponentOpGenericAdaptorBase::getFunctionType() {
  auto attr = getFunctionTypeAttr();
  return ::llvm::cast<::mlir::FunctionType>(attr.getValue());
}

::std::optional< ::mlir::ArrayAttr > CombComponentOpGenericAdaptorBase::getArgAttrs() {
  auto attr = getArgAttrsAttr();
  return attr ? ::std::optional< ::mlir::ArrayAttr >(attr) : (::std::nullopt);
}

::std::optional< ::mlir::ArrayAttr > CombComponentOpGenericAdaptorBase::getResAttrs() {
  auto attr = getResAttrsAttr();
  return attr ? ::std::optional< ::mlir::ArrayAttr >(attr) : (::std::nullopt);
}

::mlir::ArrayAttr CombComponentOpGenericAdaptorBase::getPortNames() {
  auto attr = getPortNamesAttr();
  return attr;
}

::mlir::ArrayAttr CombComponentOpGenericAdaptorBase::getPortAttributes() {
  auto attr = getPortAttributesAttr();
  return attr;
}

::mlir::APInt CombComponentOpGenericAdaptorBase::getPortDirections() {
  auto attr = getPortDirectionsAttr();
  return attr.getValue();
}


} // namespace detail
CombComponentOpAdaptor::CombComponentOpAdaptor(CombComponentOp op) : CombComponentOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult CombComponentOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_arg_attrs = getProperties().arg_attrs; (void)tblgen_arg_attrs;
  auto tblgen_function_type = getProperties().function_type; (void)tblgen_function_type;
  if (!tblgen_function_type) return emitError(loc, "'calyx.comb_component' op requires attribute 'function_type'");
  auto tblgen_portAttributes = getProperties().portAttributes; (void)tblgen_portAttributes;
  if (!tblgen_portAttributes) return emitError(loc, "'calyx.comb_component' op requires attribute 'portAttributes'");
  auto tblgen_portDirections = getProperties().portDirections; (void)tblgen_portDirections;
  if (!tblgen_portDirections) return emitError(loc, "'calyx.comb_component' op requires attribute 'portDirections'");
  auto tblgen_portNames = getProperties().portNames; (void)tblgen_portNames;
  if (!tblgen_portNames) return emitError(loc, "'calyx.comb_component' op requires attribute 'portNames'");
  auto tblgen_res_attrs = getProperties().res_attrs; (void)tblgen_res_attrs;

  if (tblgen_function_type && !(((::llvm::isa<::mlir::TypeAttr>(tblgen_function_type))) && ((::llvm::isa<::mlir::FunctionType>(::llvm::cast<::mlir::TypeAttr>(tblgen_function_type).getValue()))) && ((::llvm::isa<::mlir::FunctionType>(::llvm::cast<::mlir::TypeAttr>(tblgen_function_type).getValue())))))
    return emitError(loc, "'calyx.comb_component' op attribute 'function_type' failed to satisfy constraint: type attribute of function type");

  if (tblgen_arg_attrs && !(((::llvm::isa<::mlir::ArrayAttr>(tblgen_arg_attrs))) && (::llvm::all_of(::llvm::cast<::mlir::ArrayAttr>(tblgen_arg_attrs), [&](::mlir::Attribute attr) { return attr && ((::llvm::isa<::mlir::DictionaryAttr>(attr))); }))))
    return emitError(loc, "'calyx.comb_component' op attribute 'arg_attrs' failed to satisfy constraint: Array of dictionary attributes");

  if (tblgen_res_attrs && !(((::llvm::isa<::mlir::ArrayAttr>(tblgen_res_attrs))) && (::llvm::all_of(::llvm::cast<::mlir::ArrayAttr>(tblgen_res_attrs), [&](::mlir::Attribute attr) { return attr && ((::llvm::isa<::mlir::DictionaryAttr>(attr))); }))))
    return emitError(loc, "'calyx.comb_component' op attribute 'res_attrs' failed to satisfy constraint: Array of dictionary attributes");

  if (tblgen_portNames && !((::llvm::isa<::mlir::ArrayAttr>(tblgen_portNames))))
    return emitError(loc, "'calyx.comb_component' op attribute 'portNames' failed to satisfy constraint: array attribute");

  if (tblgen_portAttributes && !((::llvm::isa<::mlir::ArrayAttr>(tblgen_portAttributes))))
    return emitError(loc, "'calyx.comb_component' op attribute 'portAttributes' failed to satisfy constraint: array attribute");

  if (tblgen_portDirections && !((::llvm::isa<::mlir::IntegerAttr>(tblgen_portDirections))))
    return emitError(loc, "'calyx.comb_component' op attribute 'portDirections' failed to satisfy constraint: arbitrary integer attribute");
  return ::mlir::success();
}

::llvm::LogicalResult CombComponentOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
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
    auto &propStorage = prop.portAttributes;
       auto attr = dict.get("portAttributes");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `portAttributes` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.portDirections;
       auto attr = dict.get("portDirections");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `portDirections` in property conversion: " << attr;
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

::mlir::Attribute CombComponentOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
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
      const auto &propStorage = prop.portAttributes;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("portAttributes",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.portDirections;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("portDirections",
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

llvm::hash_code CombComponentOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.arg_attrs.getAsOpaquePointer()), 
    llvm::hash_value(prop.function_type.getAsOpaquePointer()), 
    llvm::hash_value(prop.portAttributes.getAsOpaquePointer()), 
    llvm::hash_value(prop.portDirections.getAsOpaquePointer()), 
    llvm::hash_value(prop.portNames.getAsOpaquePointer()), 
    llvm::hash_value(prop.res_attrs.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> CombComponentOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "arg_attrs")
      return prop.arg_attrs;

    if (name == "function_type")
      return prop.function_type;

    if (name == "portAttributes")
      return prop.portAttributes;

    if (name == "portDirections")
      return prop.portDirections;

    if (name == "portNames")
      return prop.portNames;

    if (name == "res_attrs")
      return prop.res_attrs;
  return std::nullopt;
}

void CombComponentOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "arg_attrs") {
       prop.arg_attrs = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.arg_attrs)>>(value);
       return;
    }

    if (name == "function_type") {
       prop.function_type = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.function_type)>>(value);
       return;
    }

    if (name == "portAttributes") {
       prop.portAttributes = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.portAttributes)>>(value);
       return;
    }

    if (name == "portDirections") {
       prop.portDirections = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.portDirections)>>(value);
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

void CombComponentOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.arg_attrs) attrs.append("arg_attrs", prop.arg_attrs);

    if (prop.function_type) attrs.append("function_type", prop.function_type);

    if (prop.portAttributes) attrs.append("portAttributes", prop.portAttributes);

    if (prop.portDirections) attrs.append("portDirections", prop.portDirections);

    if (prop.portNames) attrs.append("portNames", prop.portNames);

    if (prop.res_attrs) attrs.append("res_attrs", prop.res_attrs);
}

::llvm::LogicalResult CombComponentOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getArgAttrsAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Calyx3(attr, "arg_attrs", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getFunctionTypeAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Calyx2(attr, "function_type", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getPortAttributesAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Calyx4(attr, "portAttributes", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getPortDirectionsAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Calyx5(attr, "portDirections", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getPortNamesAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Calyx4(attr, "portNames", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getResAttrsAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Calyx3(attr, "res_attrs", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult CombComponentOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readOptionalAttribute(prop.arg_attrs)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readAttribute(prop.function_type)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readAttribute(prop.portAttributes)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readAttribute(prop.portDirections)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readAttribute(prop.portNames)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readOptionalAttribute(prop.res_attrs)))
    return ::mlir::failure();
  return ::mlir::success();
}

void CombComponentOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;

  writer.writeOptionalAttribute(prop.arg_attrs);
  writer.writeAttribute(prop.function_type);
  writer.writeAttribute(prop.portAttributes);
  writer.writeAttribute(prop.portDirections);
  writer.writeAttribute(prop.portNames);

  writer.writeOptionalAttribute(prop.res_attrs);
}

::mlir::FunctionType CombComponentOp::getFunctionType() {
  auto attr = getFunctionTypeAttr();
  return ::llvm::cast<::mlir::FunctionType>(attr.getValue());
}

::std::optional< ::mlir::ArrayAttr > CombComponentOp::getArgAttrs() {
  auto attr = getArgAttrsAttr();
  return attr ? ::std::optional< ::mlir::ArrayAttr >(attr) : (::std::nullopt);
}

::std::optional< ::mlir::ArrayAttr > CombComponentOp::getResAttrs() {
  auto attr = getResAttrsAttr();
  return attr ? ::std::optional< ::mlir::ArrayAttr >(attr) : (::std::nullopt);
}

::mlir::ArrayAttr CombComponentOp::getPortNames() {
  auto attr = getPortNamesAttr();
  return attr;
}

::mlir::ArrayAttr CombComponentOp::getPortAttributes() {
  auto attr = getPortAttributesAttr();
  return attr;
}

::mlir::APInt CombComponentOp::getPortDirections() {
  auto attr = getPortDirectionsAttr();
  return attr.getValue();
}

void CombComponentOp::setFunctionType(::mlir::FunctionType attrValue) {
  getProperties().function_type = ::mlir::TypeAttr::get(attrValue);
}

CombComponentOp CombComponentOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, StringAttr name, ArrayRef<PortInfo> ports) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(name)>(name), std::forward<decltype(ports)>(ports));
  auto __res__ = ::llvm::dyn_cast<CombComponentOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

CombComponentOp CombComponentOp::create(::mlir::ImplicitLocOpBuilder &builder, StringAttr name, ArrayRef<PortInfo> ports) {
  return create(builder, builder.getLoc(), std::forward<decltype(name)>(name), std::forward<decltype(ports)>(ports));
}

void CombComponentOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeAttr function_type, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs, ::mlir::ArrayAttr portNames, ::mlir::ArrayAttr portAttributes, ::mlir::IntegerAttr portDirections) {
  odsState.getOrAddProperties<Properties>().function_type = function_type;
  if (arg_attrs) {
    odsState.getOrAddProperties<Properties>().arg_attrs = arg_attrs;
  }
  if (res_attrs) {
    odsState.getOrAddProperties<Properties>().res_attrs = res_attrs;
  }
  odsState.getOrAddProperties<Properties>().portNames = portNames;
  odsState.getOrAddProperties<Properties>().portAttributes = portAttributes;
  odsState.getOrAddProperties<Properties>().portDirections = portDirections;
  (void)odsState.addRegion();
}

CombComponentOp CombComponentOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeAttr function_type, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs, ::mlir::ArrayAttr portNames, ::mlir::ArrayAttr portAttributes, ::mlir::IntegerAttr portDirections) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(function_type)>(function_type), std::forward<decltype(arg_attrs)>(arg_attrs), std::forward<decltype(res_attrs)>(res_attrs), std::forward<decltype(portNames)>(portNames), std::forward<decltype(portAttributes)>(portAttributes), std::forward<decltype(portDirections)>(portDirections));
  auto __res__ = ::llvm::dyn_cast<CombComponentOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

CombComponentOp CombComponentOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeAttr function_type, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs, ::mlir::ArrayAttr portNames, ::mlir::ArrayAttr portAttributes, ::mlir::IntegerAttr portDirections) {
  return create(builder, builder.getLoc(), std::forward<decltype(function_type)>(function_type), std::forward<decltype(arg_attrs)>(arg_attrs), std::forward<decltype(res_attrs)>(res_attrs), std::forward<decltype(portNames)>(portNames), std::forward<decltype(portAttributes)>(portAttributes), std::forward<decltype(portDirections)>(portDirections));
}

void CombComponentOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::TypeAttr function_type, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs, ::mlir::ArrayAttr portNames, ::mlir::ArrayAttr portAttributes, ::mlir::IntegerAttr portDirections) {
  odsState.getOrAddProperties<Properties>().function_type = function_type;
  if (arg_attrs) {
    odsState.getOrAddProperties<Properties>().arg_attrs = arg_attrs;
  }
  if (res_attrs) {
    odsState.getOrAddProperties<Properties>().res_attrs = res_attrs;
  }
  odsState.getOrAddProperties<Properties>().portNames = portNames;
  odsState.getOrAddProperties<Properties>().portAttributes = portAttributes;
  odsState.getOrAddProperties<Properties>().portDirections = portDirections;
  (void)odsState.addRegion();
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

CombComponentOp CombComponentOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::TypeAttr function_type, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs, ::mlir::ArrayAttr portNames, ::mlir::ArrayAttr portAttributes, ::mlir::IntegerAttr portDirections) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(function_type)>(function_type), std::forward<decltype(arg_attrs)>(arg_attrs), std::forward<decltype(res_attrs)>(res_attrs), std::forward<decltype(portNames)>(portNames), std::forward<decltype(portAttributes)>(portAttributes), std::forward<decltype(portDirections)>(portDirections));
  auto __res__ = ::llvm::dyn_cast<CombComponentOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

CombComponentOp CombComponentOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::TypeAttr function_type, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs, ::mlir::ArrayAttr portNames, ::mlir::ArrayAttr portAttributes, ::mlir::IntegerAttr portDirections) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(function_type)>(function_type), std::forward<decltype(arg_attrs)>(arg_attrs), std::forward<decltype(res_attrs)>(res_attrs), std::forward<decltype(portNames)>(portNames), std::forward<decltype(portAttributes)>(portAttributes), std::forward<decltype(portDirections)>(portDirections));
}

void CombComponentOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::FunctionType function_type, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs, ::mlir::ArrayAttr portNames, ::mlir::ArrayAttr portAttributes, ::mlir::IntegerAttr portDirections) {
  odsState.getOrAddProperties<Properties>().function_type = ::mlir::TypeAttr::get(function_type);
  if (arg_attrs) {
    odsState.getOrAddProperties<Properties>().arg_attrs = arg_attrs;
  }
  if (res_attrs) {
    odsState.getOrAddProperties<Properties>().res_attrs = res_attrs;
  }
  odsState.getOrAddProperties<Properties>().portNames = portNames;
  odsState.getOrAddProperties<Properties>().portAttributes = portAttributes;
  odsState.getOrAddProperties<Properties>().portDirections = portDirections;
  (void)odsState.addRegion();
}

CombComponentOp CombComponentOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::FunctionType function_type, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs, ::mlir::ArrayAttr portNames, ::mlir::ArrayAttr portAttributes, ::mlir::IntegerAttr portDirections) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(function_type)>(function_type), std::forward<decltype(arg_attrs)>(arg_attrs), std::forward<decltype(res_attrs)>(res_attrs), std::forward<decltype(portNames)>(portNames), std::forward<decltype(portAttributes)>(portAttributes), std::forward<decltype(portDirections)>(portDirections));
  auto __res__ = ::llvm::dyn_cast<CombComponentOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

CombComponentOp CombComponentOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::FunctionType function_type, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs, ::mlir::ArrayAttr portNames, ::mlir::ArrayAttr portAttributes, ::mlir::IntegerAttr portDirections) {
  return create(builder, builder.getLoc(), std::forward<decltype(function_type)>(function_type), std::forward<decltype(arg_attrs)>(arg_attrs), std::forward<decltype(res_attrs)>(res_attrs), std::forward<decltype(portNames)>(portNames), std::forward<decltype(portAttributes)>(portAttributes), std::forward<decltype(portDirections)>(portDirections));
}

void CombComponentOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::FunctionType function_type, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs, ::mlir::ArrayAttr portNames, ::mlir::ArrayAttr portAttributes, ::mlir::IntegerAttr portDirections) {
  odsState.getOrAddProperties<Properties>().function_type = ::mlir::TypeAttr::get(function_type);
  if (arg_attrs) {
    odsState.getOrAddProperties<Properties>().arg_attrs = arg_attrs;
  }
  if (res_attrs) {
    odsState.getOrAddProperties<Properties>().res_attrs = res_attrs;
  }
  odsState.getOrAddProperties<Properties>().portNames = portNames;
  odsState.getOrAddProperties<Properties>().portAttributes = portAttributes;
  odsState.getOrAddProperties<Properties>().portDirections = portDirections;
  (void)odsState.addRegion();
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

CombComponentOp CombComponentOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::FunctionType function_type, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs, ::mlir::ArrayAttr portNames, ::mlir::ArrayAttr portAttributes, ::mlir::IntegerAttr portDirections) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(function_type)>(function_type), std::forward<decltype(arg_attrs)>(arg_attrs), std::forward<decltype(res_attrs)>(res_attrs), std::forward<decltype(portNames)>(portNames), std::forward<decltype(portAttributes)>(portAttributes), std::forward<decltype(portDirections)>(portDirections));
  auto __res__ = ::llvm::dyn_cast<CombComponentOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

CombComponentOp CombComponentOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::FunctionType function_type, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs, ::mlir::ArrayAttr portNames, ::mlir::ArrayAttr portAttributes, ::mlir::IntegerAttr portDirections) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(function_type)>(function_type), std::forward<decltype(arg_attrs)>(arg_attrs), std::forward<decltype(res_attrs)>(res_attrs), std::forward<decltype(portNames)>(portNames), std::forward<decltype(portAttributes)>(portAttributes), std::forward<decltype(portDirections)>(portDirections));
}

void CombComponentOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  for (unsigned i = 0; i != 1; ++i)
    (void)odsState.addRegion();
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<CombComponentOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

CombComponentOp CombComponentOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<CombComponentOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

CombComponentOp CombComponentOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void CombComponentOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  for (unsigned i = 0; i != 1; ++i)
    (void)odsState.addRegion();
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

CombComponentOp CombComponentOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<CombComponentOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

CombComponentOp CombComponentOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult CombComponentOp::verifyInvariantsImpl() {
  auto tblgen_arg_attrs = getProperties().arg_attrs; (void)tblgen_arg_attrs;
  auto tblgen_function_type = getProperties().function_type; (void)tblgen_function_type;
  if (!tblgen_function_type) return emitOpError("requires attribute 'function_type'");
  auto tblgen_portAttributes = getProperties().portAttributes; (void)tblgen_portAttributes;
  if (!tblgen_portAttributes) return emitOpError("requires attribute 'portAttributes'");
  auto tblgen_portDirections = getProperties().portDirections; (void)tblgen_portDirections;
  if (!tblgen_portDirections) return emitOpError("requires attribute 'portDirections'");
  auto tblgen_portNames = getProperties().portNames; (void)tblgen_portNames;
  if (!tblgen_portNames) return emitOpError("requires attribute 'portNames'");
  auto tblgen_res_attrs = getProperties().res_attrs; (void)tblgen_res_attrs;

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Calyx2(*this, tblgen_function_type, "function_type")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Calyx3(*this, tblgen_arg_attrs, "arg_attrs")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Calyx3(*this, tblgen_res_attrs, "res_attrs")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Calyx4(*this, tblgen_portNames, "portNames")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Calyx4(*this, tblgen_portAttributes, "portAttributes")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Calyx5(*this, tblgen_portDirections, "portDirections")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;

    for (auto &region : ::llvm::MutableArrayRef((*this)->getRegion(0)))
      if (::mlir::failed(__mlir_ods_local_region_constraint_Calyx1(*this, region, "body", index++)))
        return ::mlir::failure();
  }
  return ::mlir::success();
}

::llvm::LogicalResult CombComponentOp::verifyInvariants() {
  if(::mlir::succeeded(verifyInvariantsImpl()) && ::mlir::succeeded(verify()))
    return ::mlir::success();
  return ::mlir::failure();
}

::llvm::LogicalResult CombComponentOp::setPropertiesFromParsedAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
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
  {

    auto &propStorage = prop.portAttributes;
    auto portAttributesAttrName = ::mlir::StringAttr::get(ctx, "portAttributes");
    auto attr = dict.get(portAttributesAttrName);
    usedKeys.insert(portAttributesAttrName);
    if (attr || /*isRequired=*/true) {
      if (!attr) {
        emitError() << "expected key entry for portAttributes in DictionaryAttr to set "
                   "Properties.";
        return ::mlir::failure();
      }
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `portAttributes` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  {

    auto &propStorage = prop.portDirections;
    auto portDirectionsAttrName = ::mlir::StringAttr::get(ctx, "portDirections");
    auto attr = dict.get(portDirectionsAttrName);
    usedKeys.insert(portDirectionsAttrName);
    if (attr || /*isRequired=*/true) {
      if (!attr) {
        emitError() << "expected key entry for portDirections in DictionaryAttr to set "
                   "Properties.";
        return ::mlir::failure();
      }
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `portDirections` in property conversion: " << attr;
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

Block* CombComponentOp::getBodyBlock() {
  Region* region = getRegion();
  assert(region->hasOneBlock() && "The body should have one Block.");
  return &region->front();
}

StringRef CombComponentOp::getName() {
  return cast<FunctionOpInterface>(**this).getName();
}

bool CombComponentOp::isComb() {
  return true;
}

/// Returns the region of a Calyx component.
Region* CombComponentOp::getRegion() { return &getFunctionBody(); }

} // namespace circt::calyx
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::calyx::CombComponentOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::calyx::detail::CombComponentOpGenericAdaptorBase::Properties)

namespace circt::calyx {


//===----------------------------------------------------------------------===//
// ::circt::calyx::CombGroupOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

CombGroupOpGenericAdaptorBase::CombGroupOpGenericAdaptorBase(CombGroupOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::llvm::StringRef CombGroupOpGenericAdaptorBase::getSymName() {
  auto attr = getSymNameAttr();
  return attr.getValue();
}


} // namespace detail
CombGroupOpAdaptor::CombGroupOpAdaptor(CombGroupOp op) : CombGroupOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult CombGroupOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;
  if (!tblgen_sym_name) return emitError(loc, "'calyx.comb_group' op requires attribute 'sym_name'");

  if (tblgen_sym_name && !((::llvm::isa<::mlir::StringAttr>(tblgen_sym_name))))
    return emitError(loc, "'calyx.comb_group' op attribute 'sym_name' failed to satisfy constraint: string attribute");
  return ::mlir::success();
}

::llvm::LogicalResult CombGroupOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
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

::mlir::Attribute CombGroupOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
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

llvm::hash_code CombGroupOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.sym_name.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> CombGroupOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "sym_name")
      return prop.sym_name;
  return std::nullopt;
}

void CombGroupOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "sym_name") {
       prop.sym_name = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.sym_name)>>(value);
       return;
    }
}

void CombGroupOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.sym_name) attrs.append("sym_name", prop.sym_name);
}

::llvm::LogicalResult CombGroupOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getSymNameAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Calyx1(attr, "sym_name", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult CombGroupOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.sym_name)))
    return ::mlir::failure();
  return ::mlir::success();
}

void CombGroupOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.sym_name);
}

::llvm::StringRef CombGroupOp::getSymName() {
  auto attr = getSymNameAttr();
  return attr.getValue();
}

void CombGroupOp::setSymName(::llvm::StringRef attrValue) {
  getProperties().sym_name = ::mlir::Builder((*this)->getContext()).getStringAttr(attrValue);
}

void CombGroupOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, StringRef sym_name) {
      odsState.addAttribute(
        mlir::SymbolTable::getSymbolAttrName(),
        StringAttr::get(odsState.getContext(), sym_name)
      );
      Region* region = odsState.addRegion();
      region->push_back(new Block());
    
}

CombGroupOp CombGroupOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, StringRef sym_name) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(sym_name)>(sym_name));
  auto __res__ = ::llvm::dyn_cast<CombGroupOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

CombGroupOp CombGroupOp::create(::mlir::ImplicitLocOpBuilder &builder, StringRef sym_name) {
  return create(builder, builder.getLoc(), std::forward<decltype(sym_name)>(sym_name));
}

void CombGroupOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, StringAttr sym_name) {
      odsState.addAttribute(mlir::SymbolTable::getSymbolAttrName(), sym_name);
      Region* region = odsState.addRegion();
      region->push_back(new Block());
    
}

CombGroupOp CombGroupOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, StringAttr sym_name) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(sym_name)>(sym_name));
  auto __res__ = ::llvm::dyn_cast<CombGroupOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

CombGroupOp CombGroupOp::create(::mlir::ImplicitLocOpBuilder &builder, StringAttr sym_name) {
  return create(builder, builder.getLoc(), std::forward<decltype(sym_name)>(sym_name));
}

::llvm::LogicalResult CombGroupOp::verifyInvariantsImpl() {
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;
  if (!tblgen_sym_name) return emitOpError("requires attribute 'sym_name'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Calyx1(*this, tblgen_sym_name, "sym_name")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;

    for (auto &region : ::llvm::MutableArrayRef((*this)->getRegion(0)))
      if (::mlir::failed(__mlir_ods_local_region_constraint_Calyx1(*this, region, "body", index++)))
        return ::mlir::failure();
  }
  return ::mlir::success();
}

::llvm::LogicalResult CombGroupOp::verifyInvariants() {
  if(::mlir::succeeded(verifyInvariantsImpl()) && ::mlir::succeeded(verify()))
    return ::mlir::success();
  return ::mlir::failure();
}

::mlir::ParseResult CombGroupOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::StringAttr sym_nameAttr;
  std::unique_ptr<::mlir::Region> bodyRegion = std::make_unique<::mlir::Region>();

  if (parser.parseSymbolName(sym_nameAttr))
    return ::mlir::failure();
  if (sym_nameAttr) result.getOrAddProperties<CombGroupOp::Properties>().sym_name = sym_nameAttr;

  if (parser.parseRegion(*bodyRegion))
    return ::mlir::failure();

  if (bodyRegion->empty()) bodyRegion->emplaceBlock();
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
  return ::mlir::success();
}

void CombGroupOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter.printSymbolName(getSymNameAttr().getValue());
  _odsPrinter << ' ';
  _odsPrinter.printRegion(getBody());
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("sym_name");
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
}


} // namespace circt::calyx
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::calyx::CombGroupOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::calyx::detail::CombGroupOpGenericAdaptorBase::Properties)

namespace circt::calyx {


//===----------------------------------------------------------------------===//
// ::circt::calyx::CompareFOpIEEE754 definitions
//===----------------------------------------------------------------------===//

namespace detail {

CompareFOpIEEE754GenericAdaptorBase::CompareFOpIEEE754GenericAdaptorBase(CompareFOpIEEE754 op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::llvm::StringRef CompareFOpIEEE754GenericAdaptorBase::getSymName() {
  auto attr = getSymNameAttr();
  return attr.getValue();
}


} // namespace detail
CompareFOpIEEE754Adaptor::CompareFOpIEEE754Adaptor(CompareFOpIEEE754 op) : CompareFOpIEEE754GenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult CompareFOpIEEE754Adaptor::verify(::mlir::Location loc) {
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;
  if (!tblgen_sym_name) return emitError(loc, "'calyx.ieee754.compare' op requires attribute 'sym_name'");

  if (tblgen_sym_name && !((::llvm::isa<::mlir::StringAttr>(tblgen_sym_name))))
    return emitError(loc, "'calyx.ieee754.compare' op attribute 'sym_name' failed to satisfy constraint: string attribute");
  return ::mlir::success();
}

::llvm::LogicalResult CompareFOpIEEE754::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
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

::mlir::Attribute CompareFOpIEEE754::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
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

llvm::hash_code CompareFOpIEEE754::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.sym_name.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> CompareFOpIEEE754::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "sym_name")
      return prop.sym_name;
  return std::nullopt;
}

void CompareFOpIEEE754::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "sym_name") {
       prop.sym_name = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.sym_name)>>(value);
       return;
    }
}

void CompareFOpIEEE754::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.sym_name) attrs.append("sym_name", prop.sym_name);
}

::llvm::LogicalResult CompareFOpIEEE754::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getSymNameAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Calyx1(attr, "sym_name", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult CompareFOpIEEE754::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.sym_name)))
    return ::mlir::failure();
  return ::mlir::success();
}

void CompareFOpIEEE754::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.sym_name);
}

::llvm::StringRef CompareFOpIEEE754::getSymName() {
  auto attr = getSymNameAttr();
  return attr.getValue();
}

void CompareFOpIEEE754::setSymName(::llvm::StringRef attrValue) {
  getProperties().sym_name = ::mlir::Builder((*this)->getContext()).getStringAttr(attrValue);
}

void CompareFOpIEEE754::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, StringRef sym_name, ::mlir::TypeRange resultTypes) {
      odsState.addAttribute(mlir::SymbolTable::getSymbolAttrName(), odsBuilder.getStringAttr(sym_name));
      odsState.addTypes(resultTypes);
    
}

CompareFOpIEEE754 CompareFOpIEEE754::create(::mlir::OpBuilder &builder, ::mlir::Location location, StringRef sym_name, ::mlir::TypeRange resultTypes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(resultTypes)>(resultTypes));
  auto __res__ = ::llvm::dyn_cast<CompareFOpIEEE754>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

CompareFOpIEEE754 CompareFOpIEEE754::create(::mlir::ImplicitLocOpBuilder &builder, StringRef sym_name, ::mlir::TypeRange resultTypes) {
  return create(builder, builder.getLoc(), std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(resultTypes)>(resultTypes));
}

::llvm::LogicalResult CompareFOpIEEE754::verifyInvariantsImpl() {
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;
  if (!tblgen_sym_name) return emitOpError("requires attribute 'sym_name'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Calyx1(*this, tblgen_sym_name, "sym_name")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx1(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSResults(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx1(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup2 = getODSResults(2);

    for (auto v : valueGroup2) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx1(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup3 = getODSResults(3);

    for (auto v : valueGroup3) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx2(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup4 = getODSResults(4);

    for (auto v : valueGroup4) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx2(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup5 = getODSResults(5);

    for (auto v : valueGroup5) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx1(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup6 = getODSResults(6);

    for (auto v : valueGroup6) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx1(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup7 = getODSResults(7);

    for (auto v : valueGroup7) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx1(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup8 = getODSResults(8);

    for (auto v : valueGroup8) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx1(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup9 = getODSResults(9);

    for (auto v : valueGroup9) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx1(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup10 = getODSResults(10);

    for (auto v : valueGroup10) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx4(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup11 = getODSResults(11);

    for (auto v : valueGroup11) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx1(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  if (!((std::equal_to<>()( (*this->getODSResults(3).begin()).getType() , (*this->getODSResults(4).begin()).getType()))))
    return emitOpError("failed to verify that lhs and rhs types should be equivalent");
  return ::mlir::success();
}

::llvm::LogicalResult CompareFOpIEEE754::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult CompareFOpIEEE754::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::StringAttr sym_nameAttr;
  ::llvm::SmallVector<::mlir::Type, 1> allResultTypes;

  if (parser.parseSymbolName(sym_nameAttr))
    return ::mlir::failure();
  if (sym_nameAttr) result.getOrAddProperties<CompareFOpIEEE754::Properties>().sym_name = sym_nameAttr;
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

  if (parser.parseTypeList(allResultTypes))
    return ::mlir::failure();
  result.addTypes(allResultTypes);
  return ::mlir::success();
}

void CompareFOpIEEE754::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter.printSymbolName(getSymNameAttr().getValue());
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("sym_name");
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
  _odsPrinter << getOperation()->getResultTypes();
}

SmallVector<StringRef> CompareFOpIEEE754::portNames() {
  return {clkPort, resetPort, goPort, "left", "right", "signaling",
          "lt", "eq", "gt", "unordered", "exceptionalFlags", donePort
  };
}
SmallVector<Direction> CompareFOpIEEE754::portDirections() {
  return {Input, Input, Input, Input, Input, Input, Output, Output, Output, Output, Output, Output};
}
void CompareFOpIEEE754::getAsmResultNames(OpAsmSetValueNameFn setNameFn) {
  getCellAsmResultNames(setNameFn, *this, this->portNames());
}
bool CompareFOpIEEE754::isCombinational() { return false; }
SmallVector<DictionaryAttr> CompareFOpIEEE754::portAttributes() {
  IntegerAttr isSet = IntegerAttr::get(IntegerType::get(getContext(), 1), 1);
  NamedAttrList go, clk, reset, done;
  go.append(goPort, isSet);
  clk.append(clkPort, isSet);
  reset.append(resetPort, isSet);
  done.append(donePort, isSet);
  return {clk.getDictionary(getContext()), reset.getDictionary(getContext()),
          go.getDictionary(getContext()), DictionaryAttr::get(getContext()),
          DictionaryAttr::get(getContext()), DictionaryAttr::get(getContext()),
          DictionaryAttr::get(getContext()), DictionaryAttr::get(getContext()),
          DictionaryAttr::get(getContext()), DictionaryAttr::get(getContext()),
          DictionaryAttr::get(getContext()), done.getDictionary(getContext())
  };
}

} // namespace circt::calyx
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::calyx::CompareFOpIEEE754)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::calyx::detail::CompareFOpIEEE754GenericAdaptorBase::Properties)

namespace circt::calyx {


//===----------------------------------------------------------------------===//
// ::circt::calyx::ComponentOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

ComponentOpGenericAdaptorBase::ComponentOpGenericAdaptorBase(ComponentOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::mlir::FunctionType ComponentOpGenericAdaptorBase::getFunctionType() {
  auto attr = getFunctionTypeAttr();
  return ::llvm::cast<::mlir::FunctionType>(attr.getValue());
}

::std::optional< ::mlir::ArrayAttr > ComponentOpGenericAdaptorBase::getArgAttrs() {
  auto attr = getArgAttrsAttr();
  return attr ? ::std::optional< ::mlir::ArrayAttr >(attr) : (::std::nullopt);
}

::std::optional< ::mlir::ArrayAttr > ComponentOpGenericAdaptorBase::getResAttrs() {
  auto attr = getResAttrsAttr();
  return attr ? ::std::optional< ::mlir::ArrayAttr >(attr) : (::std::nullopt);
}

::mlir::ArrayAttr ComponentOpGenericAdaptorBase::getPortNames() {
  auto attr = getPortNamesAttr();
  return attr;
}

::mlir::ArrayAttr ComponentOpGenericAdaptorBase::getPortAttributes() {
  auto attr = getPortAttributesAttr();
  return attr;
}

::mlir::APInt ComponentOpGenericAdaptorBase::getPortDirections() {
  auto attr = getPortDirectionsAttr();
  return attr.getValue();
}


} // namespace detail
ComponentOpAdaptor::ComponentOpAdaptor(ComponentOp op) : ComponentOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult ComponentOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_arg_attrs = getProperties().arg_attrs; (void)tblgen_arg_attrs;
  auto tblgen_function_type = getProperties().function_type; (void)tblgen_function_type;
  if (!tblgen_function_type) return emitError(loc, "'calyx.component' op requires attribute 'function_type'");
  auto tblgen_portAttributes = getProperties().portAttributes; (void)tblgen_portAttributes;
  if (!tblgen_portAttributes) return emitError(loc, "'calyx.component' op requires attribute 'portAttributes'");
  auto tblgen_portDirections = getProperties().portDirections; (void)tblgen_portDirections;
  if (!tblgen_portDirections) return emitError(loc, "'calyx.component' op requires attribute 'portDirections'");
  auto tblgen_portNames = getProperties().portNames; (void)tblgen_portNames;
  if (!tblgen_portNames) return emitError(loc, "'calyx.component' op requires attribute 'portNames'");
  auto tblgen_res_attrs = getProperties().res_attrs; (void)tblgen_res_attrs;

  if (tblgen_function_type && !(((::llvm::isa<::mlir::TypeAttr>(tblgen_function_type))) && ((::llvm::isa<::mlir::FunctionType>(::llvm::cast<::mlir::TypeAttr>(tblgen_function_type).getValue()))) && ((::llvm::isa<::mlir::FunctionType>(::llvm::cast<::mlir::TypeAttr>(tblgen_function_type).getValue())))))
    return emitError(loc, "'calyx.component' op attribute 'function_type' failed to satisfy constraint: type attribute of function type");

  if (tblgen_arg_attrs && !(((::llvm::isa<::mlir::ArrayAttr>(tblgen_arg_attrs))) && (::llvm::all_of(::llvm::cast<::mlir::ArrayAttr>(tblgen_arg_attrs), [&](::mlir::Attribute attr) { return attr && ((::llvm::isa<::mlir::DictionaryAttr>(attr))); }))))
    return emitError(loc, "'calyx.component' op attribute 'arg_attrs' failed to satisfy constraint: Array of dictionary attributes");

  if (tblgen_res_attrs && !(((::llvm::isa<::mlir::ArrayAttr>(tblgen_res_attrs))) && (::llvm::all_of(::llvm::cast<::mlir::ArrayAttr>(tblgen_res_attrs), [&](::mlir::Attribute attr) { return attr && ((::llvm::isa<::mlir::DictionaryAttr>(attr))); }))))
    return emitError(loc, "'calyx.component' op attribute 'res_attrs' failed to satisfy constraint: Array of dictionary attributes");

  if (tblgen_portNames && !((::llvm::isa<::mlir::ArrayAttr>(tblgen_portNames))))
    return emitError(loc, "'calyx.component' op attribute 'portNames' failed to satisfy constraint: array attribute");

  if (tblgen_portAttributes && !((::llvm::isa<::mlir::ArrayAttr>(tblgen_portAttributes))))
    return emitError(loc, "'calyx.component' op attribute 'portAttributes' failed to satisfy constraint: array attribute");

  if (tblgen_portDirections && !((::llvm::isa<::mlir::IntegerAttr>(tblgen_portDirections))))
    return emitError(loc, "'calyx.component' op attribute 'portDirections' failed to satisfy constraint: arbitrary integer attribute");
  return ::mlir::success();
}

::llvm::LogicalResult ComponentOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
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
    auto &propStorage = prop.portAttributes;
       auto attr = dict.get("portAttributes");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `portAttributes` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.portDirections;
       auto attr = dict.get("portDirections");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `portDirections` in property conversion: " << attr;
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

::mlir::Attribute ComponentOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
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
      const auto &propStorage = prop.portAttributes;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("portAttributes",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.portDirections;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("portDirections",
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

llvm::hash_code ComponentOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.arg_attrs.getAsOpaquePointer()), 
    llvm::hash_value(prop.function_type.getAsOpaquePointer()), 
    llvm::hash_value(prop.portAttributes.getAsOpaquePointer()), 
    llvm::hash_value(prop.portDirections.getAsOpaquePointer()), 
    llvm::hash_value(prop.portNames.getAsOpaquePointer()), 
    llvm::hash_value(prop.res_attrs.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> ComponentOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "arg_attrs")
      return prop.arg_attrs;

    if (name == "function_type")
      return prop.function_type;

    if (name == "portAttributes")
      return prop.portAttributes;

    if (name == "portDirections")
      return prop.portDirections;

    if (name == "portNames")
      return prop.portNames;

    if (name == "res_attrs")
      return prop.res_attrs;
  return std::nullopt;
}

void ComponentOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "arg_attrs") {
       prop.arg_attrs = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.arg_attrs)>>(value);
       return;
    }

    if (name == "function_type") {
       prop.function_type = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.function_type)>>(value);
       return;
    }

    if (name == "portAttributes") {
       prop.portAttributes = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.portAttributes)>>(value);
       return;
    }

    if (name == "portDirections") {
       prop.portDirections = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.portDirections)>>(value);
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

void ComponentOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.arg_attrs) attrs.append("arg_attrs", prop.arg_attrs);

    if (prop.function_type) attrs.append("function_type", prop.function_type);

    if (prop.portAttributes) attrs.append("portAttributes", prop.portAttributes);

    if (prop.portDirections) attrs.append("portDirections", prop.portDirections);

    if (prop.portNames) attrs.append("portNames", prop.portNames);

    if (prop.res_attrs) attrs.append("res_attrs", prop.res_attrs);
}

::llvm::LogicalResult ComponentOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getArgAttrsAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Calyx3(attr, "arg_attrs", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getFunctionTypeAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Calyx2(attr, "function_type", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getPortAttributesAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Calyx4(attr, "portAttributes", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getPortDirectionsAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Calyx5(attr, "portDirections", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getPortNamesAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Calyx4(attr, "portNames", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getResAttrsAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Calyx3(attr, "res_attrs", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult ComponentOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readOptionalAttribute(prop.arg_attrs)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readAttribute(prop.function_type)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readAttribute(prop.portAttributes)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readAttribute(prop.portDirections)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readAttribute(prop.portNames)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readOptionalAttribute(prop.res_attrs)))
    return ::mlir::failure();
  return ::mlir::success();
}

void ComponentOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;

  writer.writeOptionalAttribute(prop.arg_attrs);
  writer.writeAttribute(prop.function_type);
  writer.writeAttribute(prop.portAttributes);
  writer.writeAttribute(prop.portDirections);
  writer.writeAttribute(prop.portNames);

  writer.writeOptionalAttribute(prop.res_attrs);
}

::mlir::FunctionType ComponentOp::getFunctionType() {
  auto attr = getFunctionTypeAttr();
  return ::llvm::cast<::mlir::FunctionType>(attr.getValue());
}

::std::optional< ::mlir::ArrayAttr > ComponentOp::getArgAttrs() {
  auto attr = getArgAttrsAttr();
  return attr ? ::std::optional< ::mlir::ArrayAttr >(attr) : (::std::nullopt);
}

::std::optional< ::mlir::ArrayAttr > ComponentOp::getResAttrs() {
  auto attr = getResAttrsAttr();
  return attr ? ::std::optional< ::mlir::ArrayAttr >(attr) : (::std::nullopt);
}

::mlir::ArrayAttr ComponentOp::getPortNames() {
  auto attr = getPortNamesAttr();
  return attr;
}

::mlir::ArrayAttr ComponentOp::getPortAttributes() {
  auto attr = getPortAttributesAttr();
  return attr;
}

::mlir::APInt ComponentOp::getPortDirections() {
  auto attr = getPortDirectionsAttr();
  return attr.getValue();
}

void ComponentOp::setFunctionType(::mlir::FunctionType attrValue) {
  getProperties().function_type = ::mlir::TypeAttr::get(attrValue);
}

ComponentOp ComponentOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, StringAttr name, ArrayRef<PortInfo> ports) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(name)>(name), std::forward<decltype(ports)>(ports));
  auto __res__ = ::llvm::dyn_cast<ComponentOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ComponentOp ComponentOp::create(::mlir::ImplicitLocOpBuilder &builder, StringAttr name, ArrayRef<PortInfo> ports) {
  return create(builder, builder.getLoc(), std::forward<decltype(name)>(name), std::forward<decltype(ports)>(ports));
}

void ComponentOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeAttr function_type, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs, ::mlir::ArrayAttr portNames, ::mlir::ArrayAttr portAttributes, ::mlir::IntegerAttr portDirections) {
  odsState.getOrAddProperties<Properties>().function_type = function_type;
  if (arg_attrs) {
    odsState.getOrAddProperties<Properties>().arg_attrs = arg_attrs;
  }
  if (res_attrs) {
    odsState.getOrAddProperties<Properties>().res_attrs = res_attrs;
  }
  odsState.getOrAddProperties<Properties>().portNames = portNames;
  odsState.getOrAddProperties<Properties>().portAttributes = portAttributes;
  odsState.getOrAddProperties<Properties>().portDirections = portDirections;
  (void)odsState.addRegion();
}

ComponentOp ComponentOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeAttr function_type, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs, ::mlir::ArrayAttr portNames, ::mlir::ArrayAttr portAttributes, ::mlir::IntegerAttr portDirections) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(function_type)>(function_type), std::forward<decltype(arg_attrs)>(arg_attrs), std::forward<decltype(res_attrs)>(res_attrs), std::forward<decltype(portNames)>(portNames), std::forward<decltype(portAttributes)>(portAttributes), std::forward<decltype(portDirections)>(portDirections));
  auto __res__ = ::llvm::dyn_cast<ComponentOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ComponentOp ComponentOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeAttr function_type, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs, ::mlir::ArrayAttr portNames, ::mlir::ArrayAttr portAttributes, ::mlir::IntegerAttr portDirections) {
  return create(builder, builder.getLoc(), std::forward<decltype(function_type)>(function_type), std::forward<decltype(arg_attrs)>(arg_attrs), std::forward<decltype(res_attrs)>(res_attrs), std::forward<decltype(portNames)>(portNames), std::forward<decltype(portAttributes)>(portAttributes), std::forward<decltype(portDirections)>(portDirections));
}

void ComponentOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::TypeAttr function_type, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs, ::mlir::ArrayAttr portNames, ::mlir::ArrayAttr portAttributes, ::mlir::IntegerAttr portDirections) {
  odsState.getOrAddProperties<Properties>().function_type = function_type;
  if (arg_attrs) {
    odsState.getOrAddProperties<Properties>().arg_attrs = arg_attrs;
  }
  if (res_attrs) {
    odsState.getOrAddProperties<Properties>().res_attrs = res_attrs;
  }
  odsState.getOrAddProperties<Properties>().portNames = portNames;
  odsState.getOrAddProperties<Properties>().portAttributes = portAttributes;
  odsState.getOrAddProperties<Properties>().portDirections = portDirections;
  (void)odsState.addRegion();
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

ComponentOp ComponentOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::TypeAttr function_type, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs, ::mlir::ArrayAttr portNames, ::mlir::ArrayAttr portAttributes, ::mlir::IntegerAttr portDirections) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(function_type)>(function_type), std::forward<decltype(arg_attrs)>(arg_attrs), std::forward<decltype(res_attrs)>(res_attrs), std::forward<decltype(portNames)>(portNames), std::forward<decltype(portAttributes)>(portAttributes), std::forward<decltype(portDirections)>(portDirections));
  auto __res__ = ::llvm::dyn_cast<ComponentOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ComponentOp ComponentOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::TypeAttr function_type, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs, ::mlir::ArrayAttr portNames, ::mlir::ArrayAttr portAttributes, ::mlir::IntegerAttr portDirections) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(function_type)>(function_type), std::forward<decltype(arg_attrs)>(arg_attrs), std::forward<decltype(res_attrs)>(res_attrs), std::forward<decltype(portNames)>(portNames), std::forward<decltype(portAttributes)>(portAttributes), std::forward<decltype(portDirections)>(portDirections));
}

void ComponentOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::FunctionType function_type, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs, ::mlir::ArrayAttr portNames, ::mlir::ArrayAttr portAttributes, ::mlir::IntegerAttr portDirections) {
  odsState.getOrAddProperties<Properties>().function_type = ::mlir::TypeAttr::get(function_type);
  if (arg_attrs) {
    odsState.getOrAddProperties<Properties>().arg_attrs = arg_attrs;
  }
  if (res_attrs) {
    odsState.getOrAddProperties<Properties>().res_attrs = res_attrs;
  }
  odsState.getOrAddProperties<Properties>().portNames = portNames;
  odsState.getOrAddProperties<Properties>().portAttributes = portAttributes;
  odsState.getOrAddProperties<Properties>().portDirections = portDirections;
  (void)odsState.addRegion();
}

ComponentOp ComponentOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::FunctionType function_type, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs, ::mlir::ArrayAttr portNames, ::mlir::ArrayAttr portAttributes, ::mlir::IntegerAttr portDirections) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(function_type)>(function_type), std::forward<decltype(arg_attrs)>(arg_attrs), std::forward<decltype(res_attrs)>(res_attrs), std::forward<decltype(portNames)>(portNames), std::forward<decltype(portAttributes)>(portAttributes), std::forward<decltype(portDirections)>(portDirections));
  auto __res__ = ::llvm::dyn_cast<ComponentOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ComponentOp ComponentOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::FunctionType function_type, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs, ::mlir::ArrayAttr portNames, ::mlir::ArrayAttr portAttributes, ::mlir::IntegerAttr portDirections) {
  return create(builder, builder.getLoc(), std::forward<decltype(function_type)>(function_type), std::forward<decltype(arg_attrs)>(arg_attrs), std::forward<decltype(res_attrs)>(res_attrs), std::forward<decltype(portNames)>(portNames), std::forward<decltype(portAttributes)>(portAttributes), std::forward<decltype(portDirections)>(portDirections));
}

void ComponentOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::FunctionType function_type, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs, ::mlir::ArrayAttr portNames, ::mlir::ArrayAttr portAttributes, ::mlir::IntegerAttr portDirections) {
  odsState.getOrAddProperties<Properties>().function_type = ::mlir::TypeAttr::get(function_type);
  if (arg_attrs) {
    odsState.getOrAddProperties<Properties>().arg_attrs = arg_attrs;
  }
  if (res_attrs) {
    odsState.getOrAddProperties<Properties>().res_attrs = res_attrs;
  }
  odsState.getOrAddProperties<Properties>().portNames = portNames;
  odsState.getOrAddProperties<Properties>().portAttributes = portAttributes;
  odsState.getOrAddProperties<Properties>().portDirections = portDirections;
  (void)odsState.addRegion();
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

ComponentOp ComponentOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::FunctionType function_type, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs, ::mlir::ArrayAttr portNames, ::mlir::ArrayAttr portAttributes, ::mlir::IntegerAttr portDirections) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(function_type)>(function_type), std::forward<decltype(arg_attrs)>(arg_attrs), std::forward<decltype(res_attrs)>(res_attrs), std::forward<decltype(portNames)>(portNames), std::forward<decltype(portAttributes)>(portAttributes), std::forward<decltype(portDirections)>(portDirections));
  auto __res__ = ::llvm::dyn_cast<ComponentOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ComponentOp ComponentOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::FunctionType function_type, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs, ::mlir::ArrayAttr portNames, ::mlir::ArrayAttr portAttributes, ::mlir::IntegerAttr portDirections) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(function_type)>(function_type), std::forward<decltype(arg_attrs)>(arg_attrs), std::forward<decltype(res_attrs)>(res_attrs), std::forward<decltype(portNames)>(portNames), std::forward<decltype(portAttributes)>(portAttributes), std::forward<decltype(portDirections)>(portDirections));
}

void ComponentOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  for (unsigned i = 0; i != 1; ++i)
    (void)odsState.addRegion();
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<ComponentOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

ComponentOp ComponentOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<ComponentOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ComponentOp ComponentOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void ComponentOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  for (unsigned i = 0; i != 1; ++i)
    (void)odsState.addRegion();
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

ComponentOp ComponentOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<ComponentOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ComponentOp ComponentOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult ComponentOp::verifyInvariantsImpl() {
  auto tblgen_arg_attrs = getProperties().arg_attrs; (void)tblgen_arg_attrs;
  auto tblgen_function_type = getProperties().function_type; (void)tblgen_function_type;
  if (!tblgen_function_type) return emitOpError("requires attribute 'function_type'");
  auto tblgen_portAttributes = getProperties().portAttributes; (void)tblgen_portAttributes;
  if (!tblgen_portAttributes) return emitOpError("requires attribute 'portAttributes'");
  auto tblgen_portDirections = getProperties().portDirections; (void)tblgen_portDirections;
  if (!tblgen_portDirections) return emitOpError("requires attribute 'portDirections'");
  auto tblgen_portNames = getProperties().portNames; (void)tblgen_portNames;
  if (!tblgen_portNames) return emitOpError("requires attribute 'portNames'");
  auto tblgen_res_attrs = getProperties().res_attrs; (void)tblgen_res_attrs;

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Calyx2(*this, tblgen_function_type, "function_type")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Calyx3(*this, tblgen_arg_attrs, "arg_attrs")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Calyx3(*this, tblgen_res_attrs, "res_attrs")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Calyx4(*this, tblgen_portNames, "portNames")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Calyx4(*this, tblgen_portAttributes, "portAttributes")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Calyx5(*this, tblgen_portDirections, "portDirections")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;

    for (auto &region : ::llvm::MutableArrayRef((*this)->getRegion(0)))
      if (::mlir::failed(__mlir_ods_local_region_constraint_Calyx1(*this, region, "body", index++)))
        return ::mlir::failure();
  }
  return ::mlir::success();
}

::llvm::LogicalResult ComponentOp::verifyInvariants() {
  if(::mlir::succeeded(verifyInvariantsImpl()) && ::mlir::succeeded(verify()))
    return ::mlir::success();
  return ::mlir::failure();
}

::llvm::LogicalResult ComponentOp::setPropertiesFromParsedAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
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
  {

    auto &propStorage = prop.portAttributes;
    auto portAttributesAttrName = ::mlir::StringAttr::get(ctx, "portAttributes");
    auto attr = dict.get(portAttributesAttrName);
    usedKeys.insert(portAttributesAttrName);
    if (attr || /*isRequired=*/true) {
      if (!attr) {
        emitError() << "expected key entry for portAttributes in DictionaryAttr to set "
                   "Properties.";
        return ::mlir::failure();
      }
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `portAttributes` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  {

    auto &propStorage = prop.portDirections;
    auto portDirectionsAttrName = ::mlir::StringAttr::get(ctx, "portDirections");
    auto attr = dict.get(portDirectionsAttrName);
    usedKeys.insert(portDirectionsAttrName);
    if (attr || /*isRequired=*/true) {
      if (!attr) {
        emitError() << "expected key entry for portDirections in DictionaryAttr to set "
                   "Properties.";
        return ::mlir::failure();
      }
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `portDirections` in property conversion: " << attr;
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

Block* ComponentOp::getBodyBlock() {
  Region* region = getRegion();
  assert(region->hasOneBlock() && "The body should have one Block.");
  return &region->front();
}

StringRef ComponentOp::getName() {
  return cast<FunctionOpInterface>(**this).getName();
}

bool ComponentOp::isComb() {
  return false;
}

/// Returns the region of a Calyx component.
Region* ComponentOp::getRegion() { return &getFunctionBody(); }

} // namespace circt::calyx
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::calyx::ComponentOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::calyx::detail::ComponentOpGenericAdaptorBase::Properties)

namespace circt::calyx {


//===----------------------------------------------------------------------===//
// ::circt::calyx::ConstantOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

ConstantOpGenericAdaptorBase::ConstantOpGenericAdaptorBase(ConstantOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::llvm::StringRef ConstantOpGenericAdaptorBase::getSymName() {
  auto attr = getSymNameAttr();
  return attr.getValue();
}

::mlir::TypedAttr ConstantOpGenericAdaptorBase::getValue() {
  auto attr = getValueAttr();
  return attr;
}


} // namespace detail
ConstantOpAdaptor::ConstantOpAdaptor(ConstantOp op) : ConstantOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult ConstantOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;
  if (!tblgen_sym_name) return emitError(loc, "'calyx.constant' op requires attribute 'sym_name'");
  auto tblgen_value = getProperties().value; (void)tblgen_value;
  if (!tblgen_value) return emitError(loc, "'calyx.constant' op requires attribute 'value'");

  if (tblgen_sym_name && !((::llvm::isa<::mlir::StringAttr>(tblgen_sym_name))))
    return emitError(loc, "'calyx.constant' op attribute 'sym_name' failed to satisfy constraint: string attribute");

  if (tblgen_value && !((::llvm::isa<::mlir::TypedAttr>(tblgen_value))))
    return emitError(loc, "'calyx.constant' op attribute 'value' failed to satisfy constraint: TypedAttr instance");
  return ::mlir::success();
}

::llvm::LogicalResult ConstantOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
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

::mlir::Attribute ConstantOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.sym_name;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("sym_name",
                                       propStorage));
    }

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

llvm::hash_code ConstantOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.sym_name.getAsOpaquePointer()), 
    llvm::hash_value(prop.value.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> ConstantOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "sym_name")
      return prop.sym_name;

    if (name == "value")
      return prop.value;
  return std::nullopt;
}

void ConstantOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "sym_name") {
       prop.sym_name = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.sym_name)>>(value);
       return;
    }

    if (name == "value") {
       prop.value = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.value)>>(value);
       return;
    }
}

void ConstantOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.sym_name) attrs.append("sym_name", prop.sym_name);

    if (prop.value) attrs.append("value", prop.value);
}

::llvm::LogicalResult ConstantOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getSymNameAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Calyx1(attr, "sym_name", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getValueAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Calyx6(attr, "value", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult ConstantOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.sym_name)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readAttribute(prop.value)))
    return ::mlir::failure();
  return ::mlir::success();
}

void ConstantOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.sym_name);
  writer.writeAttribute(prop.value);
}

::llvm::StringRef ConstantOp::getSymName() {
  auto attr = getSymNameAttr();
  return attr.getValue();
}

::mlir::TypedAttr ConstantOp::getValue() {
  auto attr = getValueAttr();
  return attr;
}

void ConstantOp::setSymName(::llvm::StringRef attrValue) {
  getProperties().sym_name = ::mlir::Builder((*this)->getContext()).getStringAttr(attrValue);
}

ConstantOp ConstantOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, StringRef sym_name, Attribute attr, Type type) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(attr)>(attr), std::forward<decltype(type)>(type));
  auto __res__ = ::llvm::dyn_cast<ConstantOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ConstantOp ConstantOp::create(::mlir::ImplicitLocOpBuilder &builder, StringRef sym_name, Attribute attr, Type type) {
  return create(builder, builder.getLoc(), std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(attr)>(attr), std::forward<decltype(type)>(type));
}

::llvm::LogicalResult ConstantOp::verifyInvariantsImpl() {
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;
  if (!tblgen_sym_name) return emitOpError("requires attribute 'sym_name'");
  auto tblgen_value = getProperties().value; (void)tblgen_value;
  if (!tblgen_value) return emitOpError("requires attribute 'value'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Calyx1(*this, tblgen_sym_name, "sym_name")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Calyx6(*this, tblgen_value, "value")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx2(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult ConstantOp::verifyInvariants() {
  if(::mlir::succeeded(verifyInvariantsImpl()) && ::mlir::succeeded(verify()))
    return ::mlir::success();
  return ::mlir::failure();
}

::mlir::ParseResult ConstantOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::StringAttr sym_nameAttr;
  ::mlir::TypedAttr valueAttr;
  ::mlir::Type outRawType{};
  ::llvm::ArrayRef<::mlir::Type> outTypes(&outRawType, 1);

  if (parser.parseSymbolName(sym_nameAttr))
    return ::mlir::failure();
  if (sym_nameAttr) result.getOrAddProperties<ConstantOp::Properties>().sym_name = sym_nameAttr;
  if (parser.parseLess())
    return ::mlir::failure();

  if (parser.parseCustomAttributeWithFallback(valueAttr, ::mlir::Type{})) {
    return ::mlir::failure();
  }
  if (valueAttr) result.getOrAddProperties<ConstantOp::Properties>().value = valueAttr;
  if (parser.parseGreater())
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

  if (parser.parseType(outRawType))
    return ::mlir::failure();
  result.addTypes(outTypes);
  return ::mlir::success();
}

void ConstantOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter.printSymbolName(getSymNameAttr().getValue());
  _odsPrinter << ' ';
  _odsPrinter << "<";
_odsPrinter.printStrippedAttrOrType(getValueAttr());
  _odsPrinter << ">";
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("sym_name");
  elidedAttrs.push_back("value");
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
   _odsPrinter << getOut().getType();
}


} // namespace circt::calyx
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::calyx::ConstantOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::calyx::detail::ConstantOpGenericAdaptorBase::Properties)

namespace circt::calyx {


//===----------------------------------------------------------------------===//
// ::circt::calyx::ControlOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

ControlOpGenericAdaptorBase::ControlOpGenericAdaptorBase(ControlOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}


} // namespace detail
ControlOpAdaptor::ControlOpAdaptor(ControlOp op) : ControlOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult ControlOpAdaptor::verify(::mlir::Location loc) {
  return ::mlir::success();
}

::llvm::LogicalResult ControlOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }
      return ::mlir::success();
}

::mlir::Attribute ControlOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code ControlOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine();
}

std::optional<mlir::Attribute> ControlOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
  return std::nullopt;
}

void ControlOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
}

void ControlOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
}

::llvm::LogicalResult ControlOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    return ::mlir::success();
}

void ControlOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState) {
      Region* region = odsState.addRegion();
      region->push_back(new Block());
    
}

ControlOp ControlOp::create(::mlir::OpBuilder &builder, ::mlir::Location location) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__);
  auto __res__ = ::llvm::dyn_cast<ControlOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ControlOp ControlOp::create(::mlir::ImplicitLocOpBuilder &builder) {
  return create(builder, builder.getLoc());
}

::llvm::LogicalResult ControlOp::verifyInvariantsImpl() {
  {
    unsigned index = 0; (void)index;

    for (auto &region : ::llvm::MutableArrayRef((*this)->getRegion(0)))
      if (::mlir::failed(__mlir_ods_local_region_constraint_Calyx1(*this, region, "body", index++)))
        return ::mlir::failure();
  }
  return ::mlir::success();
}

::llvm::LogicalResult ControlOp::verifyInvariants() {
  if(::mlir::succeeded(verifyInvariantsImpl()) && ::mlir::succeeded(verify()))
    return ::mlir::success();
  return ::mlir::failure();
}

::mlir::ParseResult ControlOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  std::unique_ptr<::mlir::Region> bodyRegion = std::make_unique<::mlir::Region>();

  if (parser.parseRegion(*bodyRegion))
    return ::mlir::failure();

  if (bodyRegion->empty()) bodyRegion->emplaceBlock();
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
  return ::mlir::success();
}

void ControlOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter.printRegion(getBody());
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
}


} // namespace circt::calyx
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::calyx::ControlOp)

namespace circt::calyx {


//===----------------------------------------------------------------------===//
// ::circt::calyx::CycleOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

CycleOpGenericAdaptorBase::CycleOpGenericAdaptorBase(CycleOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

uint32_t CycleOpGenericAdaptorBase::getStart() {
  auto attr = getStartAttr();
  return attr.getValue().getZExtValue();
}

::std::optional<uint32_t> CycleOpGenericAdaptorBase::getEnd() {
  auto attr = getEndAttr();
  return attr ? ::std::optional<uint32_t>(attr.getValue().getZExtValue()) : (::std::nullopt);
}


} // namespace detail
CycleOpAdaptor::CycleOpAdaptor(CycleOp op) : CycleOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult CycleOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_end = getProperties().end; (void)tblgen_end;
  auto tblgen_start = getProperties().start; (void)tblgen_start;
  if (!tblgen_start) return emitError(loc, "'calyx.cycle' op requires attribute 'start'");

  if (tblgen_start && !(((::llvm::isa<::mlir::IntegerAttr>(tblgen_start))) && ((::llvm::cast<::mlir::IntegerAttr>(tblgen_start).getType().isSignlessInteger(32)))))
    return emitError(loc, "'calyx.cycle' op attribute 'start' failed to satisfy constraint: 32-bit signless integer attribute");

  if (tblgen_end && !(((::llvm::isa<::mlir::IntegerAttr>(tblgen_end))) && ((::llvm::cast<::mlir::IntegerAttr>(tblgen_end).getType().isSignlessInteger(32)))))
    return emitError(loc, "'calyx.cycle' op attribute 'end' failed to satisfy constraint: 32-bit signless integer attribute");
  return ::mlir::success();
}

::llvm::LogicalResult CycleOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.end;
       auto attr = dict.get("end");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `end` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.start;
       auto attr = dict.get("start");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `start` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  return ::mlir::success();
}

::mlir::Attribute CycleOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.end;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("end",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.start;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("start",
                                       propStorage));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code CycleOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.end.getAsOpaquePointer()), 
    llvm::hash_value(prop.start.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> CycleOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "end")
      return prop.end;

    if (name == "start")
      return prop.start;
  return std::nullopt;
}

void CycleOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "end") {
       prop.end = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.end)>>(value);
       return;
    }

    if (name == "start") {
       prop.start = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.start)>>(value);
       return;
    }
}

void CycleOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.end) attrs.append("end", prop.end);

    if (prop.start) attrs.append("start", prop.start);
}

::llvm::LogicalResult CycleOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getEndAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Calyx7(attr, "end", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getStartAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Calyx7(attr, "start", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult CycleOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readOptionalAttribute(prop.end)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readAttribute(prop.start)))
    return ::mlir::failure();
  return ::mlir::success();
}

void CycleOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;

  writer.writeOptionalAttribute(prop.end);
  writer.writeAttribute(prop.start);
}

uint32_t CycleOp::getStart() {
  auto attr = getStartAttr();
  return attr.getValue().getZExtValue();
}

::std::optional<uint32_t> CycleOp::getEnd() {
  auto attr = getEndAttr();
  return attr ? ::std::optional<uint32_t>(attr.getValue().getZExtValue()) : (::std::nullopt);
}

void CycleOp::setStart(uint32_t attrValue) {
  getProperties().start = ::mlir::Builder((*this)->getContext()).getIntegerAttr(::mlir::Builder((*this)->getContext()).getIntegerType(32), attrValue);
}

void CycleOp::setEnd(::std::optional<uint32_t> attrValue) {
    auto &odsProp = getProperties().end;
    if (attrValue)
      odsProp = ::mlir::Builder((*this)->getContext()).getIntegerAttr(::mlir::Builder((*this)->getContext()).getIntegerType(32), *attrValue);
    else
      odsProp = nullptr;
}

void CycleOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, uint32_t start) {
      odsState.addAttribute(
        getStartAttrName(odsState.name),
        mlir::IntegerAttr::get(IntegerType::get(odsState.getContext(), 32), start)
      );
    
}

CycleOp CycleOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, uint32_t start) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(start)>(start));
  auto __res__ = ::llvm::dyn_cast<CycleOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

CycleOp CycleOp::create(::mlir::ImplicitLocOpBuilder &builder, uint32_t start) {
  return create(builder, builder.getLoc(), std::forward<decltype(start)>(start));
}

void CycleOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, uint32_t start, uint32_t end) {
      odsState.addAttribute(
        getStartAttrName(odsState.name),
        mlir::IntegerAttr::get(IntegerType::get(odsState.getContext(), 32), start)
      );
      odsState.addAttribute(
        getEndAttrName(odsState.name),
        mlir::IntegerAttr::get(IntegerType::get(odsState.getContext(), 32), end)
      );
    
}

CycleOp CycleOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, uint32_t start, uint32_t end) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(start)>(start), std::forward<decltype(end)>(end));
  auto __res__ = ::llvm::dyn_cast<CycleOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

CycleOp CycleOp::create(::mlir::ImplicitLocOpBuilder &builder, uint32_t start, uint32_t end) {
  return create(builder, builder.getLoc(), std::forward<decltype(start)>(start), std::forward<decltype(end)>(end));
}

void CycleOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type active, ::mlir::IntegerAttr start, /*optional*/::mlir::IntegerAttr end) {
  odsState.getOrAddProperties<Properties>().start = start;
  if (end) {
    odsState.getOrAddProperties<Properties>().end = end;
  }
  odsState.addTypes(active);
}

CycleOp CycleOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type active, ::mlir::IntegerAttr start, /*optional*/::mlir::IntegerAttr end) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(active)>(active), std::forward<decltype(start)>(start), std::forward<decltype(end)>(end));
  auto __res__ = ::llvm::dyn_cast<CycleOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

CycleOp CycleOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type active, ::mlir::IntegerAttr start, /*optional*/::mlir::IntegerAttr end) {
  return create(builder, builder.getLoc(), std::forward<decltype(active)>(active), std::forward<decltype(start)>(start), std::forward<decltype(end)>(end));
}

void CycleOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::IntegerAttr start, /*optional*/::mlir::IntegerAttr end) {
  odsState.getOrAddProperties<Properties>().start = start;
  if (end) {
    odsState.getOrAddProperties<Properties>().end = end;
  }
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

CycleOp CycleOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::IntegerAttr start, /*optional*/::mlir::IntegerAttr end) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(start)>(start), std::forward<decltype(end)>(end));
  auto __res__ = ::llvm::dyn_cast<CycleOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

CycleOp CycleOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::IntegerAttr start, /*optional*/::mlir::IntegerAttr end) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(start)>(start), std::forward<decltype(end)>(end));
}

void CycleOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type active, uint32_t start, /*optional*/::mlir::IntegerAttr end) {
  odsState.getOrAddProperties<Properties>().start = odsBuilder.getIntegerAttr(odsBuilder.getIntegerType(32), start);
  if (end) {
    odsState.getOrAddProperties<Properties>().end = end;
  }
  odsState.addTypes(active);
}

CycleOp CycleOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type active, uint32_t start, /*optional*/::mlir::IntegerAttr end) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(active)>(active), std::forward<decltype(start)>(start), std::forward<decltype(end)>(end));
  auto __res__ = ::llvm::dyn_cast<CycleOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

CycleOp CycleOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type active, uint32_t start, /*optional*/::mlir::IntegerAttr end) {
  return create(builder, builder.getLoc(), std::forward<decltype(active)>(active), std::forward<decltype(start)>(start), std::forward<decltype(end)>(end));
}

void CycleOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, uint32_t start, /*optional*/::mlir::IntegerAttr end) {
  odsState.getOrAddProperties<Properties>().start = odsBuilder.getIntegerAttr(odsBuilder.getIntegerType(32), start);
  if (end) {
    odsState.getOrAddProperties<Properties>().end = end;
  }
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

CycleOp CycleOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, uint32_t start, /*optional*/::mlir::IntegerAttr end) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(start)>(start), std::forward<decltype(end)>(end));
  auto __res__ = ::llvm::dyn_cast<CycleOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

CycleOp CycleOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, uint32_t start, /*optional*/::mlir::IntegerAttr end) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(start)>(start), std::forward<decltype(end)>(end));
}

void CycleOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<CycleOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

CycleOp CycleOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<CycleOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

CycleOp CycleOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void CycleOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

CycleOp CycleOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<CycleOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

CycleOp CycleOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult CycleOp::verifyInvariantsImpl() {
  auto tblgen_end = getProperties().end; (void)tblgen_end;
  auto tblgen_start = getProperties().start; (void)tblgen_start;
  if (!tblgen_start) return emitOpError("requires attribute 'start'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Calyx7(*this, tblgen_start, "start")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Calyx7(*this, tblgen_end, "end")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx1(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult CycleOp::verifyInvariants() {
  if(::mlir::succeeded(verifyInvariantsImpl()) && ::mlir::succeeded(verify()))
    return ::mlir::success();
  return ::mlir::failure();
}

::llvm::LogicalResult CycleOp::setPropertiesFromParsedAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
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

    auto &propStorage = prop.start;
    auto startAttrName = ::mlir::StringAttr::get(ctx, "start");
    auto attr = dict.get(startAttrName);
    usedKeys.insert(startAttrName);
    if (attr || /*isRequired=*/true) {
      if (!attr) {
        emitError() << "expected key entry for start in DictionaryAttr to set "
                   "Properties.";
        return ::mlir::failure();
      }
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `start` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  {

    auto &propStorage = prop.end;
    auto endAttrName = ::mlir::StringAttr::get(ctx, "end");
    auto attr = dict.get(endAttrName);
    usedKeys.insert(endAttrName);
    if (attr || /*isRequired=*/false) {
      if (!attr) {
        emitError() << "expected key entry for end in DictionaryAttr to set "
                   "Properties.";
        return ::mlir::failure();
      }
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `end` in property conversion: " << attr;
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


} // namespace circt::calyx
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::calyx::CycleOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::calyx::detail::CycleOpGenericAdaptorBase::Properties)

namespace circt::calyx {


//===----------------------------------------------------------------------===//
// ::circt::calyx::DivSPipeLibOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

DivSPipeLibOpGenericAdaptorBase::DivSPipeLibOpGenericAdaptorBase(DivSPipeLibOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::llvm::StringRef DivSPipeLibOpGenericAdaptorBase::getSymName() {
  auto attr = getSymNameAttr();
  return attr.getValue();
}


} // namespace detail
DivSPipeLibOpAdaptor::DivSPipeLibOpAdaptor(DivSPipeLibOp op) : DivSPipeLibOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult DivSPipeLibOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;
  if (!tblgen_sym_name) return emitError(loc, "'calyx.std_divs_pipe' op requires attribute 'sym_name'");

  if (tblgen_sym_name && !((::llvm::isa<::mlir::StringAttr>(tblgen_sym_name))))
    return emitError(loc, "'calyx.std_divs_pipe' op attribute 'sym_name' failed to satisfy constraint: string attribute");
  return ::mlir::success();
}

::llvm::LogicalResult DivSPipeLibOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
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

::mlir::Attribute DivSPipeLibOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
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

llvm::hash_code DivSPipeLibOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.sym_name.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> DivSPipeLibOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "sym_name")
      return prop.sym_name;
  return std::nullopt;
}

void DivSPipeLibOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "sym_name") {
       prop.sym_name = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.sym_name)>>(value);
       return;
    }
}

void DivSPipeLibOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.sym_name) attrs.append("sym_name", prop.sym_name);
}

::llvm::LogicalResult DivSPipeLibOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getSymNameAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Calyx1(attr, "sym_name", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult DivSPipeLibOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.sym_name)))
    return ::mlir::failure();
  return ::mlir::success();
}

void DivSPipeLibOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.sym_name);
}

::llvm::StringRef DivSPipeLibOp::getSymName() {
  auto attr = getSymNameAttr();
  return attr.getValue();
}

void DivSPipeLibOp::setSymName(::llvm::StringRef attrValue) {
  getProperties().sym_name = ::mlir::Builder((*this)->getContext()).getStringAttr(attrValue);
}

void DivSPipeLibOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, StringRef sym_name, ::mlir::TypeRange resultTypes) {
      odsState.addAttribute(mlir::SymbolTable::getSymbolAttrName(), odsBuilder.getStringAttr(sym_name));
      odsState.addTypes(resultTypes);
    
}

DivSPipeLibOp DivSPipeLibOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, StringRef sym_name, ::mlir::TypeRange resultTypes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(resultTypes)>(resultTypes));
  auto __res__ = ::llvm::dyn_cast<DivSPipeLibOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

DivSPipeLibOp DivSPipeLibOp::create(::mlir::ImplicitLocOpBuilder &builder, StringRef sym_name, ::mlir::TypeRange resultTypes) {
  return create(builder, builder.getLoc(), std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(resultTypes)>(resultTypes));
}

::llvm::LogicalResult DivSPipeLibOp::verifyInvariantsImpl() {
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;
  if (!tblgen_sym_name) return emitOpError("requires attribute 'sym_name'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Calyx1(*this, tblgen_sym_name, "sym_name")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx1(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSResults(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx1(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup2 = getODSResults(2);

    for (auto v : valueGroup2) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx1(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup3 = getODSResults(3);

    for (auto v : valueGroup3) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx5(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup4 = getODSResults(4);

    for (auto v : valueGroup4) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx5(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup5 = getODSResults(5);

    for (auto v : valueGroup5) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx5(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup6 = getODSResults(6);

    for (auto v : valueGroup6) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx1(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  if (!((std::equal_to<>()( (*this->getODSResults(3).begin()).getType() , (*this->getODSResults(5).begin()).getType()))))
    return emitOpError("failed to verify that lhs and rhs types should be equivalent");
  if (!((std::equal_to<>()( (*this->getODSResults(3).begin()).getType() , (*this->getODSResults(4).begin()).getType()))))
    return emitOpError("failed to verify that lhs and rhs types should be equivalent");
  return ::mlir::success();
}

::llvm::LogicalResult DivSPipeLibOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult DivSPipeLibOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::StringAttr sym_nameAttr;
  ::llvm::SmallVector<::mlir::Type, 1> allResultTypes;

  if (parser.parseSymbolName(sym_nameAttr))
    return ::mlir::failure();
  if (sym_nameAttr) result.getOrAddProperties<DivSPipeLibOp::Properties>().sym_name = sym_nameAttr;
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

  if (parser.parseTypeList(allResultTypes))
    return ::mlir::failure();
  result.addTypes(allResultTypes);
  return ::mlir::success();
}

void DivSPipeLibOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter.printSymbolName(getSymNameAttr().getValue());
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("sym_name");
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
  _odsPrinter << getOperation()->getResultTypes();
}


} // namespace circt::calyx
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::calyx::DivSPipeLibOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::calyx::detail::DivSPipeLibOpGenericAdaptorBase::Properties)

namespace circt::calyx {


//===----------------------------------------------------------------------===//
// ::circt::calyx::DivSqrtOpIEEE754 definitions
//===----------------------------------------------------------------------===//

namespace detail {

DivSqrtOpIEEE754GenericAdaptorBase::DivSqrtOpIEEE754GenericAdaptorBase(DivSqrtOpIEEE754 op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::llvm::StringRef DivSqrtOpIEEE754GenericAdaptorBase::getSymName() {
  auto attr = getSymNameAttr();
  return attr.getValue();
}


} // namespace detail
DivSqrtOpIEEE754Adaptor::DivSqrtOpIEEE754Adaptor(DivSqrtOpIEEE754 op) : DivSqrtOpIEEE754GenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult DivSqrtOpIEEE754Adaptor::verify(::mlir::Location loc) {
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;
  if (!tblgen_sym_name) return emitError(loc, "'calyx.ieee754.divSqrt' op requires attribute 'sym_name'");

  if (tblgen_sym_name && !((::llvm::isa<::mlir::StringAttr>(tblgen_sym_name))))
    return emitError(loc, "'calyx.ieee754.divSqrt' op attribute 'sym_name' failed to satisfy constraint: string attribute");
  return ::mlir::success();
}

::llvm::LogicalResult DivSqrtOpIEEE754::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
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

::mlir::Attribute DivSqrtOpIEEE754::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
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

llvm::hash_code DivSqrtOpIEEE754::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.sym_name.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> DivSqrtOpIEEE754::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "sym_name")
      return prop.sym_name;
  return std::nullopt;
}

void DivSqrtOpIEEE754::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "sym_name") {
       prop.sym_name = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.sym_name)>>(value);
       return;
    }
}

void DivSqrtOpIEEE754::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.sym_name) attrs.append("sym_name", prop.sym_name);
}

::llvm::LogicalResult DivSqrtOpIEEE754::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getSymNameAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Calyx1(attr, "sym_name", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult DivSqrtOpIEEE754::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.sym_name)))
    return ::mlir::failure();
  return ::mlir::success();
}

void DivSqrtOpIEEE754::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.sym_name);
}

::llvm::StringRef DivSqrtOpIEEE754::getSymName() {
  auto attr = getSymNameAttr();
  return attr.getValue();
}

void DivSqrtOpIEEE754::setSymName(::llvm::StringRef attrValue) {
  getProperties().sym_name = ::mlir::Builder((*this)->getContext()).getStringAttr(attrValue);
}

void DivSqrtOpIEEE754::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, StringRef sym_name, ::mlir::TypeRange resultTypes) {
      odsState.addAttribute(mlir::SymbolTable::getSymbolAttrName(), odsBuilder.getStringAttr(sym_name));
      odsState.addTypes(resultTypes);
    
}

DivSqrtOpIEEE754 DivSqrtOpIEEE754::create(::mlir::OpBuilder &builder, ::mlir::Location location, StringRef sym_name, ::mlir::TypeRange resultTypes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(resultTypes)>(resultTypes));
  auto __res__ = ::llvm::dyn_cast<DivSqrtOpIEEE754>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

DivSqrtOpIEEE754 DivSqrtOpIEEE754::create(::mlir::ImplicitLocOpBuilder &builder, StringRef sym_name, ::mlir::TypeRange resultTypes) {
  return create(builder, builder.getLoc(), std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(resultTypes)>(resultTypes));
}

::llvm::LogicalResult DivSqrtOpIEEE754::verifyInvariantsImpl() {
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;
  if (!tblgen_sym_name) return emitOpError("requires attribute 'sym_name'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Calyx1(*this, tblgen_sym_name, "sym_name")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx1(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSResults(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx1(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup2 = getODSResults(2);

    for (auto v : valueGroup2) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx1(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup3 = getODSResults(3);

    for (auto v : valueGroup3) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx1(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup4 = getODSResults(4);

    for (auto v : valueGroup4) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx1(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup5 = getODSResults(5);

    for (auto v : valueGroup5) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx2(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup6 = getODSResults(6);

    for (auto v : valueGroup6) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx2(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup7 = getODSResults(7);

    for (auto v : valueGroup7) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx3(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup8 = getODSResults(8);

    for (auto v : valueGroup8) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx2(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup9 = getODSResults(9);

    for (auto v : valueGroup9) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx4(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup10 = getODSResults(10);

    for (auto v : valueGroup10) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx1(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  if (!((std::equal_to<>()( (*this->getODSResults(5).begin()).getType() , (*this->getODSResults(8).begin()).getType()))))
    return emitOpError("failed to verify that lhs and rhs types should be equivalent");
  if (!((std::equal_to<>()( (*this->getODSResults(5).begin()).getType() , (*this->getODSResults(6).begin()).getType()))))
    return emitOpError("failed to verify that lhs and rhs types should be equivalent");
  return ::mlir::success();
}

::llvm::LogicalResult DivSqrtOpIEEE754::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult DivSqrtOpIEEE754::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::StringAttr sym_nameAttr;
  ::llvm::SmallVector<::mlir::Type, 1> allResultTypes;

  if (parser.parseSymbolName(sym_nameAttr))
    return ::mlir::failure();
  if (sym_nameAttr) result.getOrAddProperties<DivSqrtOpIEEE754::Properties>().sym_name = sym_nameAttr;
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

  if (parser.parseTypeList(allResultTypes))
    return ::mlir::failure();
  result.addTypes(allResultTypes);
  return ::mlir::success();
}

void DivSqrtOpIEEE754::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter.printSymbolName(getSymNameAttr().getValue());
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("sym_name");
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
  _odsPrinter << getOperation()->getResultTypes();
}

SmallVector<StringRef> DivSqrtOpIEEE754::portNames() {
  return {clkPort, resetPort, goPort, "control", "sqrtOp", "left", "right",
          "roundingMode", "out", "exceptionalFlags", donePort
  };
}
SmallVector<Direction> DivSqrtOpIEEE754::portDirections() {
  return {Input, Input, Input, Input, Input, Input, Input, Input, Output, Output, Output};
}
void DivSqrtOpIEEE754::getAsmResultNames(OpAsmSetValueNameFn setNameFn) {
  getCellAsmResultNames(setNameFn, *this, this->portNames());
}
bool DivSqrtOpIEEE754::isCombinational() { return false; }
SmallVector<DictionaryAttr> DivSqrtOpIEEE754::portAttributes() {
  IntegerAttr isSet = IntegerAttr::get(IntegerType::get(getContext(), 1), 1);
  NamedAttrList go, clk, reset, done;
  go.append(goPort, isSet);
  clk.append(clkPort, isSet);
  reset.append(resetPort, isSet);
  done.append(donePort, isSet);
  return {
    clk.getDictionary(getContext()),
    reset.getDictionary(getContext()),
    go.getDictionary(getContext()),
    DictionaryAttr::get(getContext()), // control
    DictionaryAttr::get(getContext()), // sqrtOp
    DictionaryAttr::get(getContext()), // left
    DictionaryAttr::get(getContext()), // right
    DictionaryAttr::get(getContext()), // roundingMode
    DictionaryAttr::get(getContext()), // out
    DictionaryAttr::get(getContext()), // exceptionalFlags
    done.getDictionary(getContext())
  };
}

} // namespace circt::calyx
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::calyx::DivSqrtOpIEEE754)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::calyx::detail::DivSqrtOpIEEE754GenericAdaptorBase::Properties)

namespace circt::calyx {


//===----------------------------------------------------------------------===//
// ::circt::calyx::DivUPipeLibOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

DivUPipeLibOpGenericAdaptorBase::DivUPipeLibOpGenericAdaptorBase(DivUPipeLibOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::llvm::StringRef DivUPipeLibOpGenericAdaptorBase::getSymName() {
  auto attr = getSymNameAttr();
  return attr.getValue();
}


} // namespace detail
DivUPipeLibOpAdaptor::DivUPipeLibOpAdaptor(DivUPipeLibOp op) : DivUPipeLibOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult DivUPipeLibOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;
  if (!tblgen_sym_name) return emitError(loc, "'calyx.std_divu_pipe' op requires attribute 'sym_name'");

  if (tblgen_sym_name && !((::llvm::isa<::mlir::StringAttr>(tblgen_sym_name))))
    return emitError(loc, "'calyx.std_divu_pipe' op attribute 'sym_name' failed to satisfy constraint: string attribute");
  return ::mlir::success();
}

::llvm::LogicalResult DivUPipeLibOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
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

::mlir::Attribute DivUPipeLibOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
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

llvm::hash_code DivUPipeLibOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.sym_name.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> DivUPipeLibOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "sym_name")
      return prop.sym_name;
  return std::nullopt;
}

void DivUPipeLibOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "sym_name") {
       prop.sym_name = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.sym_name)>>(value);
       return;
    }
}

void DivUPipeLibOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.sym_name) attrs.append("sym_name", prop.sym_name);
}

::llvm::LogicalResult DivUPipeLibOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getSymNameAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Calyx1(attr, "sym_name", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult DivUPipeLibOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.sym_name)))
    return ::mlir::failure();
  return ::mlir::success();
}

void DivUPipeLibOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.sym_name);
}

::llvm::StringRef DivUPipeLibOp::getSymName() {
  auto attr = getSymNameAttr();
  return attr.getValue();
}

void DivUPipeLibOp::setSymName(::llvm::StringRef attrValue) {
  getProperties().sym_name = ::mlir::Builder((*this)->getContext()).getStringAttr(attrValue);
}

void DivUPipeLibOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, StringRef sym_name, ::mlir::TypeRange resultTypes) {
      odsState.addAttribute(mlir::SymbolTable::getSymbolAttrName(), odsBuilder.getStringAttr(sym_name));
      odsState.addTypes(resultTypes);
    
}

DivUPipeLibOp DivUPipeLibOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, StringRef sym_name, ::mlir::TypeRange resultTypes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(resultTypes)>(resultTypes));
  auto __res__ = ::llvm::dyn_cast<DivUPipeLibOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

DivUPipeLibOp DivUPipeLibOp::create(::mlir::ImplicitLocOpBuilder &builder, StringRef sym_name, ::mlir::TypeRange resultTypes) {
  return create(builder, builder.getLoc(), std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(resultTypes)>(resultTypes));
}

::llvm::LogicalResult DivUPipeLibOp::verifyInvariantsImpl() {
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;
  if (!tblgen_sym_name) return emitOpError("requires attribute 'sym_name'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Calyx1(*this, tblgen_sym_name, "sym_name")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx1(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSResults(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx1(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup2 = getODSResults(2);

    for (auto v : valueGroup2) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx1(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup3 = getODSResults(3);

    for (auto v : valueGroup3) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx5(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup4 = getODSResults(4);

    for (auto v : valueGroup4) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx5(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup5 = getODSResults(5);

    for (auto v : valueGroup5) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx5(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup6 = getODSResults(6);

    for (auto v : valueGroup6) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx1(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  if (!((std::equal_to<>()( (*this->getODSResults(3).begin()).getType() , (*this->getODSResults(5).begin()).getType()))))
    return emitOpError("failed to verify that lhs and rhs types should be equivalent");
  if (!((std::equal_to<>()( (*this->getODSResults(3).begin()).getType() , (*this->getODSResults(4).begin()).getType()))))
    return emitOpError("failed to verify that lhs and rhs types should be equivalent");
  return ::mlir::success();
}

::llvm::LogicalResult DivUPipeLibOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult DivUPipeLibOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::StringAttr sym_nameAttr;
  ::llvm::SmallVector<::mlir::Type, 1> allResultTypes;

  if (parser.parseSymbolName(sym_nameAttr))
    return ::mlir::failure();
  if (sym_nameAttr) result.getOrAddProperties<DivUPipeLibOp::Properties>().sym_name = sym_nameAttr;
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

  if (parser.parseTypeList(allResultTypes))
    return ::mlir::failure();
  result.addTypes(allResultTypes);
  return ::mlir::success();
}

void DivUPipeLibOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter.printSymbolName(getSymNameAttr().getValue());
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("sym_name");
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
  _odsPrinter << getOperation()->getResultTypes();
}


} // namespace circt::calyx
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::calyx::DivUPipeLibOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::calyx::detail::DivUPipeLibOpGenericAdaptorBase::Properties)

namespace circt::calyx {


//===----------------------------------------------------------------------===//
// ::circt::calyx::EnableOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

EnableOpGenericAdaptorBase::EnableOpGenericAdaptorBase(EnableOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::llvm::StringRef EnableOpGenericAdaptorBase::getGroupName() {
  auto attr = getGroupNameAttr();
  return attr.getValue();
}

::std::optional< ::mlir::ArrayAttr > EnableOpGenericAdaptorBase::getCompiledGroups() {
  auto attr = getCompiledGroupsAttr();
  return attr ? ::std::optional< ::mlir::ArrayAttr >(attr) : (::std::nullopt);
}


} // namespace detail
EnableOpAdaptor::EnableOpAdaptor(EnableOp op) : EnableOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult EnableOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_compiledGroups = getProperties().compiledGroups; (void)tblgen_compiledGroups;
  auto tblgen_groupName = getProperties().groupName; (void)tblgen_groupName;
  if (!tblgen_groupName) return emitError(loc, "'calyx.enable' op requires attribute 'groupName'");

  if (tblgen_groupName && !((::llvm::isa<::mlir::FlatSymbolRefAttr>(tblgen_groupName))))
    return emitError(loc, "'calyx.enable' op attribute 'groupName' failed to satisfy constraint: flat symbol reference attribute");

  if (tblgen_compiledGroups && !((::llvm::isa<::mlir::ArrayAttr>(tblgen_compiledGroups))))
    return emitError(loc, "'calyx.enable' op attribute 'compiledGroups' failed to satisfy constraint: array attribute");
  return ::mlir::success();
}

::llvm::LogicalResult EnableOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.compiledGroups;
       auto attr = dict.get("compiledGroups");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `compiledGroups` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.groupName;
       auto attr = dict.get("groupName");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `groupName` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  return ::mlir::success();
}

::mlir::Attribute EnableOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.compiledGroups;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("compiledGroups",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.groupName;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("groupName",
                                       propStorage));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code EnableOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.compiledGroups.getAsOpaquePointer()), 
    llvm::hash_value(prop.groupName.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> EnableOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "compiledGroups")
      return prop.compiledGroups;

    if (name == "groupName")
      return prop.groupName;
  return std::nullopt;
}

void EnableOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "compiledGroups") {
       prop.compiledGroups = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.compiledGroups)>>(value);
       return;
    }

    if (name == "groupName") {
       prop.groupName = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.groupName)>>(value);
       return;
    }
}

void EnableOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.compiledGroups) attrs.append("compiledGroups", prop.compiledGroups);

    if (prop.groupName) attrs.append("groupName", prop.groupName);
}

::llvm::LogicalResult EnableOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getCompiledGroupsAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Calyx4(attr, "compiledGroups", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getGroupNameAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Calyx8(attr, "groupName", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult EnableOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readOptionalAttribute(prop.compiledGroups)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readAttribute(prop.groupName)))
    return ::mlir::failure();
  return ::mlir::success();
}

void EnableOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;

  writer.writeOptionalAttribute(prop.compiledGroups);
  writer.writeAttribute(prop.groupName);
}

::llvm::StringRef EnableOp::getGroupName() {
  auto attr = getGroupNameAttr();
  return attr.getValue();
}

::std::optional< ::mlir::ArrayAttr > EnableOp::getCompiledGroups() {
  auto attr = getCompiledGroupsAttr();
  return attr ? ::std::optional< ::mlir::ArrayAttr >(attr) : (::std::nullopt);
}

void EnableOp::setGroupName(::llvm::StringRef attrValue) {
  getProperties().groupName = ::mlir::SymbolRefAttr::get(::mlir::Builder((*this)->getContext()).getContext(), attrValue);
}

void EnableOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, StringRef groupName) {
      odsState.addAttribute(
        "groupName",
        FlatSymbolRefAttr::get(odsBuilder.getContext(), groupName)
      );
    
}

EnableOp EnableOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, StringRef groupName) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(groupName)>(groupName));
  auto __res__ = ::llvm::dyn_cast<EnableOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

EnableOp EnableOp::create(::mlir::ImplicitLocOpBuilder &builder, StringRef groupName) {
  return create(builder, builder.getLoc(), std::forward<decltype(groupName)>(groupName));
}

void EnableOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::FlatSymbolRefAttr groupName, /*optional*/::mlir::ArrayAttr compiledGroups) {
  odsState.getOrAddProperties<Properties>().groupName = groupName;
  if (compiledGroups) {
    odsState.getOrAddProperties<Properties>().compiledGroups = compiledGroups;
  }
}

EnableOp EnableOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::FlatSymbolRefAttr groupName, /*optional*/::mlir::ArrayAttr compiledGroups) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(groupName)>(groupName), std::forward<decltype(compiledGroups)>(compiledGroups));
  auto __res__ = ::llvm::dyn_cast<EnableOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

EnableOp EnableOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::FlatSymbolRefAttr groupName, /*optional*/::mlir::ArrayAttr compiledGroups) {
  return create(builder, builder.getLoc(), std::forward<decltype(groupName)>(groupName), std::forward<decltype(compiledGroups)>(compiledGroups));
}

void EnableOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::FlatSymbolRefAttr groupName, /*optional*/::mlir::ArrayAttr compiledGroups) {
  odsState.getOrAddProperties<Properties>().groupName = groupName;
  if (compiledGroups) {
    odsState.getOrAddProperties<Properties>().compiledGroups = compiledGroups;
  }
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

EnableOp EnableOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::FlatSymbolRefAttr groupName, /*optional*/::mlir::ArrayAttr compiledGroups) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(groupName)>(groupName), std::forward<decltype(compiledGroups)>(compiledGroups));
  auto __res__ = ::llvm::dyn_cast<EnableOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

EnableOp EnableOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::FlatSymbolRefAttr groupName, /*optional*/::mlir::ArrayAttr compiledGroups) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(groupName)>(groupName), std::forward<decltype(compiledGroups)>(compiledGroups));
}

void EnableOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::llvm::StringRef groupName, /*optional*/::mlir::ArrayAttr compiledGroups) {
  odsState.getOrAddProperties<Properties>().groupName = ::mlir::SymbolRefAttr::get(odsBuilder.getContext(), groupName);
  if (compiledGroups) {
    odsState.getOrAddProperties<Properties>().compiledGroups = compiledGroups;
  }
}

EnableOp EnableOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::llvm::StringRef groupName, /*optional*/::mlir::ArrayAttr compiledGroups) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(groupName)>(groupName), std::forward<decltype(compiledGroups)>(compiledGroups));
  auto __res__ = ::llvm::dyn_cast<EnableOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

EnableOp EnableOp::create(::mlir::ImplicitLocOpBuilder &builder, ::llvm::StringRef groupName, /*optional*/::mlir::ArrayAttr compiledGroups) {
  return create(builder, builder.getLoc(), std::forward<decltype(groupName)>(groupName), std::forward<decltype(compiledGroups)>(compiledGroups));
}

void EnableOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::llvm::StringRef groupName, /*optional*/::mlir::ArrayAttr compiledGroups) {
  odsState.getOrAddProperties<Properties>().groupName = ::mlir::SymbolRefAttr::get(odsBuilder.getContext(), groupName);
  if (compiledGroups) {
    odsState.getOrAddProperties<Properties>().compiledGroups = compiledGroups;
  }
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

EnableOp EnableOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::llvm::StringRef groupName, /*optional*/::mlir::ArrayAttr compiledGroups) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(groupName)>(groupName), std::forward<decltype(compiledGroups)>(compiledGroups));
  auto __res__ = ::llvm::dyn_cast<EnableOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

EnableOp EnableOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::llvm::StringRef groupName, /*optional*/::mlir::ArrayAttr compiledGroups) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(groupName)>(groupName), std::forward<decltype(compiledGroups)>(compiledGroups));
}

void EnableOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<EnableOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

EnableOp EnableOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<EnableOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

EnableOp EnableOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void EnableOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

EnableOp EnableOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<EnableOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

EnableOp EnableOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult EnableOp::verifyInvariantsImpl() {
  auto tblgen_compiledGroups = getProperties().compiledGroups; (void)tblgen_compiledGroups;
  auto tblgen_groupName = getProperties().groupName; (void)tblgen_groupName;
  if (!tblgen_groupName) return emitOpError("requires attribute 'groupName'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Calyx8(*this, tblgen_groupName, "groupName")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Calyx4(*this, tblgen_compiledGroups, "compiledGroups")))
    return ::mlir::failure();
  return ::mlir::success();
}

::llvm::LogicalResult EnableOp::verifyInvariants() {
  if(::mlir::succeeded(verifyInvariantsImpl()) && ::mlir::succeeded(verify()))
    return ::mlir::success();
  return ::mlir::failure();
}

::mlir::ParseResult EnableOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::FlatSymbolRefAttr groupNameAttr;

  if (parser.parseCustomAttributeWithFallback(groupNameAttr, parser.getBuilder().getType<::mlir::NoneType>())) {
    return ::mlir::failure();
  }
  if (groupNameAttr) result.getOrAddProperties<EnableOp::Properties>().groupName = groupNameAttr;
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

void EnableOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter.printAttributeWithoutType(getGroupNameAttr());
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("groupName");
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
}


} // namespace circt::calyx
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::calyx::EnableOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::calyx::detail::EnableOpGenericAdaptorBase::Properties)

namespace circt::calyx {


//===----------------------------------------------------------------------===//
// ::circt::calyx::EqLibOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

EqLibOpGenericAdaptorBase::EqLibOpGenericAdaptorBase(EqLibOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::llvm::StringRef EqLibOpGenericAdaptorBase::getSymName() {
  auto attr = getSymNameAttr();
  return attr.getValue();
}


} // namespace detail
EqLibOpAdaptor::EqLibOpAdaptor(EqLibOp op) : EqLibOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult EqLibOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;
  if (!tblgen_sym_name) return emitError(loc, "'calyx.std_eq' op requires attribute 'sym_name'");

  if (tblgen_sym_name && !((::llvm::isa<::mlir::StringAttr>(tblgen_sym_name))))
    return emitError(loc, "'calyx.std_eq' op attribute 'sym_name' failed to satisfy constraint: string attribute");
  return ::mlir::success();
}

::llvm::LogicalResult EqLibOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
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

::mlir::Attribute EqLibOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
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

llvm::hash_code EqLibOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.sym_name.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> EqLibOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "sym_name")
      return prop.sym_name;
  return std::nullopt;
}

void EqLibOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "sym_name") {
       prop.sym_name = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.sym_name)>>(value);
       return;
    }
}

void EqLibOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.sym_name) attrs.append("sym_name", prop.sym_name);
}

::llvm::LogicalResult EqLibOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getSymNameAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Calyx1(attr, "sym_name", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult EqLibOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.sym_name)))
    return ::mlir::failure();
  return ::mlir::success();
}

void EqLibOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.sym_name);
}

::llvm::StringRef EqLibOp::getSymName() {
  auto attr = getSymNameAttr();
  return attr.getValue();
}

void EqLibOp::setSymName(::llvm::StringRef attrValue) {
  getProperties().sym_name = ::mlir::Builder((*this)->getContext()).getStringAttr(attrValue);
}

void EqLibOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, StringRef sym_name, ::mlir::TypeRange resultTypes) {
      odsState.addAttribute(mlir::SymbolTable::getSymbolAttrName(), odsBuilder.getStringAttr(sym_name));
      odsState.addTypes(resultTypes);
    
}

EqLibOp EqLibOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, StringRef sym_name, ::mlir::TypeRange resultTypes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(resultTypes)>(resultTypes));
  auto __res__ = ::llvm::dyn_cast<EqLibOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

EqLibOp EqLibOp::create(::mlir::ImplicitLocOpBuilder &builder, StringRef sym_name, ::mlir::TypeRange resultTypes) {
  return create(builder, builder.getLoc(), std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(resultTypes)>(resultTypes));
}

::llvm::LogicalResult EqLibOp::verifyInvariantsImpl() {
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;
  if (!tblgen_sym_name) return emitOpError("requires attribute 'sym_name'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Calyx1(*this, tblgen_sym_name, "sym_name")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx5(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSResults(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx5(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup2 = getODSResults(2);

    for (auto v : valueGroup2) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx1(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  if (!((std::equal_to<>()( (*this->getODSResults(0).begin()).getType() , (*this->getODSResults(1).begin()).getType()))))
    return emitOpError("failed to verify that lhs and rhs types should be equivalent");
  return ::mlir::success();
}

::llvm::LogicalResult EqLibOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult EqLibOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::StringAttr sym_nameAttr;
  ::llvm::SmallVector<::mlir::Type, 1> allResultTypes;

  if (parser.parseSymbolName(sym_nameAttr))
    return ::mlir::failure();
  if (sym_nameAttr) result.getOrAddProperties<EqLibOp::Properties>().sym_name = sym_nameAttr;
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

  if (parser.parseTypeList(allResultTypes))
    return ::mlir::failure();
  result.addTypes(allResultTypes);
  return ::mlir::success();
}

void EqLibOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter.printSymbolName(getSymNameAttr().getValue());
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("sym_name");
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
  _odsPrinter << getOperation()->getResultTypes();
}


} // namespace circt::calyx
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::calyx::EqLibOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::calyx::detail::EqLibOpGenericAdaptorBase::Properties)

namespace circt::calyx {


//===----------------------------------------------------------------------===//
// ::circt::calyx::ExtSILibOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

ExtSILibOpGenericAdaptorBase::ExtSILibOpGenericAdaptorBase(ExtSILibOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::llvm::StringRef ExtSILibOpGenericAdaptorBase::getSymName() {
  auto attr = getSymNameAttr();
  return attr.getValue();
}


} // namespace detail
ExtSILibOpAdaptor::ExtSILibOpAdaptor(ExtSILibOp op) : ExtSILibOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult ExtSILibOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;
  if (!tblgen_sym_name) return emitError(loc, "'calyx.std_signext' op requires attribute 'sym_name'");

  if (tblgen_sym_name && !((::llvm::isa<::mlir::StringAttr>(tblgen_sym_name))))
    return emitError(loc, "'calyx.std_signext' op attribute 'sym_name' failed to satisfy constraint: string attribute");
  return ::mlir::success();
}

::llvm::LogicalResult ExtSILibOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
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

::mlir::Attribute ExtSILibOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
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

llvm::hash_code ExtSILibOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.sym_name.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> ExtSILibOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "sym_name")
      return prop.sym_name;
  return std::nullopt;
}

void ExtSILibOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "sym_name") {
       prop.sym_name = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.sym_name)>>(value);
       return;
    }
}

void ExtSILibOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.sym_name) attrs.append("sym_name", prop.sym_name);
}

::llvm::LogicalResult ExtSILibOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getSymNameAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Calyx1(attr, "sym_name", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult ExtSILibOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.sym_name)))
    return ::mlir::failure();
  return ::mlir::success();
}

void ExtSILibOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.sym_name);
}

::llvm::StringRef ExtSILibOp::getSymName() {
  auto attr = getSymNameAttr();
  return attr.getValue();
}

void ExtSILibOp::setSymName(::llvm::StringRef attrValue) {
  getProperties().sym_name = ::mlir::Builder((*this)->getContext()).getStringAttr(attrValue);
}

void ExtSILibOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, StringRef sym_name, ::mlir::TypeRange resultTypes) {
      odsState.addAttribute(mlir::SymbolTable::getSymbolAttrName(), odsBuilder.getStringAttr(sym_name));
      odsState.addTypes(resultTypes);
    
}

ExtSILibOp ExtSILibOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, StringRef sym_name, ::mlir::TypeRange resultTypes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(resultTypes)>(resultTypes));
  auto __res__ = ::llvm::dyn_cast<ExtSILibOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ExtSILibOp ExtSILibOp::create(::mlir::ImplicitLocOpBuilder &builder, StringRef sym_name, ::mlir::TypeRange resultTypes) {
  return create(builder, builder.getLoc(), std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(resultTypes)>(resultTypes));
}

::llvm::LogicalResult ExtSILibOp::verifyInvariantsImpl() {
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;
  if (!tblgen_sym_name) return emitOpError("requires attribute 'sym_name'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Calyx1(*this, tblgen_sym_name, "sym_name")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx6(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSResults(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx6(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult ExtSILibOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult ExtSILibOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::StringAttr sym_nameAttr;
  ::llvm::SmallVector<::mlir::Type, 1> allResultTypes;

  if (parser.parseSymbolName(sym_nameAttr))
    return ::mlir::failure();
  if (sym_nameAttr) result.getOrAddProperties<ExtSILibOp::Properties>().sym_name = sym_nameAttr;
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

  if (parser.parseTypeList(allResultTypes))
    return ::mlir::failure();
  result.addTypes(allResultTypes);
  return ::mlir::success();
}

void ExtSILibOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter.printSymbolName(getSymNameAttr().getValue());
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("sym_name");
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
  _odsPrinter << getOperation()->getResultTypes();
}


} // namespace circt::calyx
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::calyx::ExtSILibOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::calyx::detail::ExtSILibOpGenericAdaptorBase::Properties)

namespace circt::calyx {


//===----------------------------------------------------------------------===//
// ::circt::calyx::FpToIntOpIEEE754 definitions
//===----------------------------------------------------------------------===//

namespace detail {

FpToIntOpIEEE754GenericAdaptorBase::FpToIntOpIEEE754GenericAdaptorBase(FpToIntOpIEEE754 op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::llvm::StringRef FpToIntOpIEEE754GenericAdaptorBase::getSymName() {
  auto attr = getSymNameAttr();
  return attr.getValue();
}


} // namespace detail
FpToIntOpIEEE754Adaptor::FpToIntOpIEEE754Adaptor(FpToIntOpIEEE754 op) : FpToIntOpIEEE754GenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult FpToIntOpIEEE754Adaptor::verify(::mlir::Location loc) {
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;
  if (!tblgen_sym_name) return emitError(loc, "'calyx.ieee754.fpToInt' op requires attribute 'sym_name'");

  if (tblgen_sym_name && !((::llvm::isa<::mlir::StringAttr>(tblgen_sym_name))))
    return emitError(loc, "'calyx.ieee754.fpToInt' op attribute 'sym_name' failed to satisfy constraint: string attribute");
  return ::mlir::success();
}

::llvm::LogicalResult FpToIntOpIEEE754::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
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

::mlir::Attribute FpToIntOpIEEE754::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
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

llvm::hash_code FpToIntOpIEEE754::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.sym_name.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> FpToIntOpIEEE754::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "sym_name")
      return prop.sym_name;
  return std::nullopt;
}

void FpToIntOpIEEE754::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "sym_name") {
       prop.sym_name = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.sym_name)>>(value);
       return;
    }
}

void FpToIntOpIEEE754::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.sym_name) attrs.append("sym_name", prop.sym_name);
}

::llvm::LogicalResult FpToIntOpIEEE754::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getSymNameAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Calyx1(attr, "sym_name", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult FpToIntOpIEEE754::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.sym_name)))
    return ::mlir::failure();
  return ::mlir::success();
}

void FpToIntOpIEEE754::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.sym_name);
}

::llvm::StringRef FpToIntOpIEEE754::getSymName() {
  auto attr = getSymNameAttr();
  return attr.getValue();
}

void FpToIntOpIEEE754::setSymName(::llvm::StringRef attrValue) {
  getProperties().sym_name = ::mlir::Builder((*this)->getContext()).getStringAttr(attrValue);
}

void FpToIntOpIEEE754::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, StringRef sym_name, ::mlir::TypeRange resultTypes) {
      odsState.addAttribute(mlir::SymbolTable::getSymbolAttrName(), odsBuilder.getStringAttr(sym_name));
      odsState.addTypes(resultTypes);
    
}

FpToIntOpIEEE754 FpToIntOpIEEE754::create(::mlir::OpBuilder &builder, ::mlir::Location location, StringRef sym_name, ::mlir::TypeRange resultTypes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(resultTypes)>(resultTypes));
  auto __res__ = ::llvm::dyn_cast<FpToIntOpIEEE754>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

FpToIntOpIEEE754 FpToIntOpIEEE754::create(::mlir::ImplicitLocOpBuilder &builder, StringRef sym_name, ::mlir::TypeRange resultTypes) {
  return create(builder, builder.getLoc(), std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(resultTypes)>(resultTypes));
}

::llvm::LogicalResult FpToIntOpIEEE754::verifyInvariantsImpl() {
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;
  if (!tblgen_sym_name) return emitOpError("requires attribute 'sym_name'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Calyx1(*this, tblgen_sym_name, "sym_name")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx1(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSResults(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx1(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup2 = getODSResults(2);

    for (auto v : valueGroup2) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx1(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup3 = getODSResults(3);

    for (auto v : valueGroup3) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx2(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup4 = getODSResults(4);

    for (auto v : valueGroup4) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx1(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup5 = getODSResults(5);

    for (auto v : valueGroup5) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx2(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup6 = getODSResults(6);

    for (auto v : valueGroup6) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx1(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult FpToIntOpIEEE754::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult FpToIntOpIEEE754::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::StringAttr sym_nameAttr;
  ::llvm::SmallVector<::mlir::Type, 1> allResultTypes;

  if (parser.parseSymbolName(sym_nameAttr))
    return ::mlir::failure();
  if (sym_nameAttr) result.getOrAddProperties<FpToIntOpIEEE754::Properties>().sym_name = sym_nameAttr;
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

  if (parser.parseTypeList(allResultTypes))
    return ::mlir::failure();
  result.addTypes(allResultTypes);
  return ::mlir::success();
}

void FpToIntOpIEEE754::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter.printSymbolName(getSymNameAttr().getValue());
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("sym_name");
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
  _odsPrinter << getOperation()->getResultTypes();
}

SmallVector<StringRef> FpToIntOpIEEE754::portNames() {
  return {clkPort, resetPort, goPort, "in", "signedOut", "out", donePort};
}

SmallVector<Direction> FpToIntOpIEEE754::portDirections() {
  return {Input, Input, Input, Input, Input, Output, Output};
}

void FpToIntOpIEEE754::getAsmResultNames(OpAsmSetValueNameFn setNameFn) {
  getCellAsmResultNames(setNameFn, *this, this->portNames());
}

bool FpToIntOpIEEE754::isCombinational() { return false; }

SmallVector<DictionaryAttr> FpToIntOpIEEE754::portAttributes() {
  IntegerAttr isSet = IntegerAttr::get(IntegerType::get(getContext(), 1), 1);
  NamedAttrList go, clk, reset, done;
  go.append(goPort, isSet);
  clk.append(clkPort, isSet);
  reset.append(resetPort, isSet);
  done.append(donePort, isSet);
  return {
    clk.getDictionary(getContext()),
    reset.getDictionary(getContext()),
    go.getDictionary(getContext()),
    DictionaryAttr::get(getContext()), // in
    DictionaryAttr::get(getContext()), // signedOut
    DictionaryAttr::get(getContext()), // out
    done.getDictionary(getContext())
  };
}

} // namespace circt::calyx
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::calyx::FpToIntOpIEEE754)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::calyx::detail::FpToIntOpIEEE754GenericAdaptorBase::Properties)

namespace circt::calyx {


//===----------------------------------------------------------------------===//
// ::circt::calyx::GeLibOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

GeLibOpGenericAdaptorBase::GeLibOpGenericAdaptorBase(GeLibOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::llvm::StringRef GeLibOpGenericAdaptorBase::getSymName() {
  auto attr = getSymNameAttr();
  return attr.getValue();
}


} // namespace detail
GeLibOpAdaptor::GeLibOpAdaptor(GeLibOp op) : GeLibOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult GeLibOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;
  if (!tblgen_sym_name) return emitError(loc, "'calyx.std_ge' op requires attribute 'sym_name'");

  if (tblgen_sym_name && !((::llvm::isa<::mlir::StringAttr>(tblgen_sym_name))))
    return emitError(loc, "'calyx.std_ge' op attribute 'sym_name' failed to satisfy constraint: string attribute");
  return ::mlir::success();
}

::llvm::LogicalResult GeLibOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
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

::mlir::Attribute GeLibOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
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

llvm::hash_code GeLibOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.sym_name.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> GeLibOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "sym_name")
      return prop.sym_name;
  return std::nullopt;
}

void GeLibOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "sym_name") {
       prop.sym_name = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.sym_name)>>(value);
       return;
    }
}

void GeLibOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.sym_name) attrs.append("sym_name", prop.sym_name);
}

::llvm::LogicalResult GeLibOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getSymNameAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Calyx1(attr, "sym_name", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult GeLibOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.sym_name)))
    return ::mlir::failure();
  return ::mlir::success();
}

void GeLibOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.sym_name);
}

::llvm::StringRef GeLibOp::getSymName() {
  auto attr = getSymNameAttr();
  return attr.getValue();
}

void GeLibOp::setSymName(::llvm::StringRef attrValue) {
  getProperties().sym_name = ::mlir::Builder((*this)->getContext()).getStringAttr(attrValue);
}

void GeLibOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, StringRef sym_name, ::mlir::TypeRange resultTypes) {
      odsState.addAttribute(mlir::SymbolTable::getSymbolAttrName(), odsBuilder.getStringAttr(sym_name));
      odsState.addTypes(resultTypes);
    
}

GeLibOp GeLibOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, StringRef sym_name, ::mlir::TypeRange resultTypes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(resultTypes)>(resultTypes));
  auto __res__ = ::llvm::dyn_cast<GeLibOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

GeLibOp GeLibOp::create(::mlir::ImplicitLocOpBuilder &builder, StringRef sym_name, ::mlir::TypeRange resultTypes) {
  return create(builder, builder.getLoc(), std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(resultTypes)>(resultTypes));
}

::llvm::LogicalResult GeLibOp::verifyInvariantsImpl() {
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;
  if (!tblgen_sym_name) return emitOpError("requires attribute 'sym_name'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Calyx1(*this, tblgen_sym_name, "sym_name")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx5(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSResults(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx5(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup2 = getODSResults(2);

    for (auto v : valueGroup2) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx1(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  if (!((std::equal_to<>()( (*this->getODSResults(0).begin()).getType() , (*this->getODSResults(1).begin()).getType()))))
    return emitOpError("failed to verify that lhs and rhs types should be equivalent");
  return ::mlir::success();
}

::llvm::LogicalResult GeLibOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult GeLibOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::StringAttr sym_nameAttr;
  ::llvm::SmallVector<::mlir::Type, 1> allResultTypes;

  if (parser.parseSymbolName(sym_nameAttr))
    return ::mlir::failure();
  if (sym_nameAttr) result.getOrAddProperties<GeLibOp::Properties>().sym_name = sym_nameAttr;
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

  if (parser.parseTypeList(allResultTypes))
    return ::mlir::failure();
  result.addTypes(allResultTypes);
  return ::mlir::success();
}

void GeLibOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter.printSymbolName(getSymNameAttr().getValue());
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("sym_name");
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
  _odsPrinter << getOperation()->getResultTypes();
}


} // namespace circt::calyx
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::calyx::GeLibOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::calyx::detail::GeLibOpGenericAdaptorBase::Properties)

namespace circt::calyx {


//===----------------------------------------------------------------------===//
// ::circt::calyx::GroupDoneOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

GroupDoneOpGenericAdaptorBase::GroupDoneOpGenericAdaptorBase(GroupDoneOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

std::pair<unsigned, unsigned> GroupDoneOpGenericAdaptorBase::getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
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
GroupDoneOpAdaptor::GroupDoneOpAdaptor(GroupDoneOp op) : GroupDoneOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult GroupDoneOpAdaptor::verify(::mlir::Location loc) {
  return ::mlir::success();
}

std::pair<unsigned, unsigned> GroupDoneOp::getODSOperandIndexAndLength(unsigned index) {
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

::mlir::MutableOperandRange GroupDoneOp::getGuardMutable() {
  auto range = getODSOperandIndexAndLength(1);
  auto mutableRange = ::mlir::MutableOperandRange(getOperation(), range.first, range.second);
  return mutableRange;
}

::llvm::LogicalResult GroupDoneOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }
      return ::mlir::success();
}

::mlir::Attribute GroupDoneOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code GroupDoneOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine();
}

std::optional<mlir::Attribute> GroupDoneOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
  return std::nullopt;
}

void GroupDoneOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
}

void GroupDoneOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
}

::llvm::LogicalResult GroupDoneOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    return ::mlir::success();
}

void GroupDoneOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value src) {
      odsState.addOperands(src);
    
}

GroupDoneOp GroupDoneOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, Value src) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(src)>(src));
  auto __res__ = ::llvm::dyn_cast<GroupDoneOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

GroupDoneOp GroupDoneOp::create(::mlir::ImplicitLocOpBuilder &builder, Value src) {
  return create(builder, builder.getLoc(), std::forward<decltype(src)>(src));
}

void GroupDoneOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value src, /*optional*/::mlir::Value guard) {
  odsState.addOperands(src);
  if (guard)
    odsState.addOperands(guard);
}

GroupDoneOp GroupDoneOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value src, /*optional*/::mlir::Value guard) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(src)>(src), std::forward<decltype(guard)>(guard));
  auto __res__ = ::llvm::dyn_cast<GroupDoneOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

GroupDoneOp GroupDoneOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value src, /*optional*/::mlir::Value guard) {
  return create(builder, builder.getLoc(), std::forward<decltype(src)>(src), std::forward<decltype(guard)>(guard));
}

void GroupDoneOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value src, /*optional*/::mlir::Value guard) {
  odsState.addOperands(src);
  if (guard)
    odsState.addOperands(guard);
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

GroupDoneOp GroupDoneOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value src, /*optional*/::mlir::Value guard) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(src)>(src), std::forward<decltype(guard)>(guard));
  auto __res__ = ::llvm::dyn_cast<GroupDoneOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

GroupDoneOp GroupDoneOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value src, /*optional*/::mlir::Value guard) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(src)>(src), std::forward<decltype(guard)>(guard));
}

void GroupDoneOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() >= 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

GroupDoneOp GroupDoneOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<GroupDoneOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

GroupDoneOp GroupDoneOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void GroupDoneOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() >= 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

GroupDoneOp GroupDoneOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<GroupDoneOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

GroupDoneOp GroupDoneOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult GroupDoneOp::verifyInvariantsImpl() {
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSOperands(1);

    if (valueGroup1.size() > 1) {
      return emitOpError("operand group starting at #") << index
          << " requires 0 or 1 element, but found " << valueGroup1.size();
    }

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult GroupDoneOp::verifyInvariants() {
  if(::mlir::succeeded(verifyInvariantsImpl()) && ::mlir::succeeded(verify()))
    return ::mlir::success();
  return ::mlir::failure();
}

::llvm::LogicalResult GroupDoneOp::setPropertiesFromParsedAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
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


} // namespace circt::calyx
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::calyx::GroupDoneOp)

namespace circt::calyx {


//===----------------------------------------------------------------------===//
// ::circt::calyx::GroupGoOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

GroupGoOpGenericAdaptorBase::GroupGoOpGenericAdaptorBase(GroupGoOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

std::pair<unsigned, unsigned> GroupGoOpGenericAdaptorBase::getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
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
GroupGoOpAdaptor::GroupGoOpAdaptor(GroupGoOp op) : GroupGoOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult GroupGoOpAdaptor::verify(::mlir::Location loc) {
  return ::mlir::success();
}

std::pair<unsigned, unsigned> GroupGoOp::getODSOperandIndexAndLength(unsigned index) {
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

::mlir::MutableOperandRange GroupGoOp::getGuardMutable() {
  auto range = getODSOperandIndexAndLength(1);
  auto mutableRange = ::mlir::MutableOperandRange(getOperation(), range.first, range.second);
  return mutableRange;
}

::llvm::LogicalResult GroupGoOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }
      return ::mlir::success();
}

::mlir::Attribute GroupGoOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code GroupGoOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine();
}

std::optional<mlir::Attribute> GroupGoOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
  return std::nullopt;
}

void GroupGoOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
}

void GroupGoOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
}

::llvm::LogicalResult GroupGoOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    return ::mlir::success();
}

void GroupGoOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value src) {
      odsState.addTypes(odsBuilder.getI1Type());
      odsState.addOperands(src);
    
}

GroupGoOp GroupGoOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, Value src) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(src)>(src));
  auto __res__ = ::llvm::dyn_cast<GroupGoOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

GroupGoOp GroupGoOp::create(::mlir::ImplicitLocOpBuilder &builder, Value src) {
  return create(builder, builder.getLoc(), std::forward<decltype(src)>(src));
}

void GroupGoOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type resultType0, ::mlir::Value src, /*optional*/::mlir::Value guard) {
  odsState.addOperands(src);
  if (guard)
    odsState.addOperands(guard);
  odsState.addTypes(resultType0);
}

GroupGoOp GroupGoOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type resultType0, ::mlir::Value src, /*optional*/::mlir::Value guard) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultType0)>(resultType0), std::forward<decltype(src)>(src), std::forward<decltype(guard)>(guard));
  auto __res__ = ::llvm::dyn_cast<GroupGoOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

GroupGoOp GroupGoOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type resultType0, ::mlir::Value src, /*optional*/::mlir::Value guard) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultType0)>(resultType0), std::forward<decltype(src)>(src), std::forward<decltype(guard)>(guard));
}

void GroupGoOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value src, /*optional*/::mlir::Value guard) {
  odsState.addOperands(src);
  if (guard)
    odsState.addOperands(guard);
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

GroupGoOp GroupGoOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value src, /*optional*/::mlir::Value guard) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(src)>(src), std::forward<decltype(guard)>(guard));
  auto __res__ = ::llvm::dyn_cast<GroupGoOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

GroupGoOp GroupGoOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value src, /*optional*/::mlir::Value guard) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(src)>(src), std::forward<decltype(guard)>(guard));
}

void GroupGoOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() >= 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

GroupGoOp GroupGoOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<GroupGoOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

GroupGoOp GroupGoOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void GroupGoOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() >= 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

GroupGoOp GroupGoOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<GroupGoOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

GroupGoOp GroupGoOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult GroupGoOp::verifyInvariantsImpl() {
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSOperands(1);

    if (valueGroup1.size() > 1) {
      return emitOpError("operand group starting at #") << index
          << " requires 0 or 1 element, but found " << valueGroup1.size();
    }

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx1(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult GroupGoOp::verifyInvariants() {
  if(::mlir::succeeded(verifyInvariantsImpl()) && ::mlir::succeeded(verify()))
    return ::mlir::success();
  return ::mlir::failure();
}

::llvm::LogicalResult GroupGoOp::setPropertiesFromParsedAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
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


} // namespace circt::calyx
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::calyx::GroupGoOp)

namespace circt::calyx {


//===----------------------------------------------------------------------===//
// ::circt::calyx::GroupOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

GroupOpGenericAdaptorBase::GroupOpGenericAdaptorBase(GroupOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::llvm::StringRef GroupOpGenericAdaptorBase::getSymName() {
  auto attr = getSymNameAttr();
  return attr.getValue();
}


} // namespace detail
GroupOpAdaptor::GroupOpAdaptor(GroupOp op) : GroupOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult GroupOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;
  if (!tblgen_sym_name) return emitError(loc, "'calyx.group' op requires attribute 'sym_name'");

  if (tblgen_sym_name && !((::llvm::isa<::mlir::StringAttr>(tblgen_sym_name))))
    return emitError(loc, "'calyx.group' op attribute 'sym_name' failed to satisfy constraint: string attribute");
  return ::mlir::success();
}

::llvm::LogicalResult GroupOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
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

::mlir::Attribute GroupOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
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

llvm::hash_code GroupOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.sym_name.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> GroupOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "sym_name")
      return prop.sym_name;
  return std::nullopt;
}

void GroupOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "sym_name") {
       prop.sym_name = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.sym_name)>>(value);
       return;
    }
}

void GroupOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.sym_name) attrs.append("sym_name", prop.sym_name);
}

::llvm::LogicalResult GroupOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getSymNameAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Calyx1(attr, "sym_name", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult GroupOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.sym_name)))
    return ::mlir::failure();
  return ::mlir::success();
}

void GroupOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.sym_name);
}

::llvm::StringRef GroupOp::getSymName() {
  auto attr = getSymNameAttr();
  return attr.getValue();
}

void GroupOp::setSymName(::llvm::StringRef attrValue) {
  getProperties().sym_name = ::mlir::Builder((*this)->getContext()).getStringAttr(attrValue);
}

void GroupOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, StringRef sym_name) {
      odsState.addAttribute(
        mlir::SymbolTable::getSymbolAttrName(),
        StringAttr::get(odsState.getContext(), sym_name)
      );
      Region* region = odsState.addRegion();
      region->push_back(new Block());
    
}

GroupOp GroupOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, StringRef sym_name) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(sym_name)>(sym_name));
  auto __res__ = ::llvm::dyn_cast<GroupOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

GroupOp GroupOp::create(::mlir::ImplicitLocOpBuilder &builder, StringRef sym_name) {
  return create(builder, builder.getLoc(), std::forward<decltype(sym_name)>(sym_name));
}

void GroupOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, StringAttr sym_name) {
      odsState.addAttribute(mlir::SymbolTable::getSymbolAttrName(), sym_name);
      Region* region = odsState.addRegion();
      region->push_back(new Block());
    
}

GroupOp GroupOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, StringAttr sym_name) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(sym_name)>(sym_name));
  auto __res__ = ::llvm::dyn_cast<GroupOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

GroupOp GroupOp::create(::mlir::ImplicitLocOpBuilder &builder, StringAttr sym_name) {
  return create(builder, builder.getLoc(), std::forward<decltype(sym_name)>(sym_name));
}

::llvm::LogicalResult GroupOp::verifyInvariantsImpl() {
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;
  if (!tblgen_sym_name) return emitOpError("requires attribute 'sym_name'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Calyx1(*this, tblgen_sym_name, "sym_name")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;

    for (auto &region : ::llvm::MutableArrayRef((*this)->getRegion(0)))
      if (::mlir::failed(__mlir_ods_local_region_constraint_Calyx1(*this, region, "body", index++)))
        return ::mlir::failure();
  }
  return ::mlir::success();
}

::llvm::LogicalResult GroupOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult GroupOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::StringAttr sym_nameAttr;
  std::unique_ptr<::mlir::Region> bodyRegion = std::make_unique<::mlir::Region>();

  if (parser.parseSymbolName(sym_nameAttr))
    return ::mlir::failure();
  if (sym_nameAttr) result.getOrAddProperties<GroupOp::Properties>().sym_name = sym_nameAttr;

  if (parser.parseRegion(*bodyRegion))
    return ::mlir::failure();

  if (bodyRegion->empty()) bodyRegion->emplaceBlock();
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
  return ::mlir::success();
}

void GroupOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter.printSymbolName(getSymNameAttr().getValue());
  _odsPrinter << ' ';
  _odsPrinter.printRegion(getBody());
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("sym_name");
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
}


} // namespace circt::calyx
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::calyx::GroupOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::calyx::detail::GroupOpGenericAdaptorBase::Properties)

namespace circt::calyx {


//===----------------------------------------------------------------------===//
// ::circt::calyx::GtLibOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

GtLibOpGenericAdaptorBase::GtLibOpGenericAdaptorBase(GtLibOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::llvm::StringRef GtLibOpGenericAdaptorBase::getSymName() {
  auto attr = getSymNameAttr();
  return attr.getValue();
}


} // namespace detail
GtLibOpAdaptor::GtLibOpAdaptor(GtLibOp op) : GtLibOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult GtLibOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;
  if (!tblgen_sym_name) return emitError(loc, "'calyx.std_gt' op requires attribute 'sym_name'");

  if (tblgen_sym_name && !((::llvm::isa<::mlir::StringAttr>(tblgen_sym_name))))
    return emitError(loc, "'calyx.std_gt' op attribute 'sym_name' failed to satisfy constraint: string attribute");
  return ::mlir::success();
}

::llvm::LogicalResult GtLibOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
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

::mlir::Attribute GtLibOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
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

llvm::hash_code GtLibOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.sym_name.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> GtLibOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "sym_name")
      return prop.sym_name;
  return std::nullopt;
}

void GtLibOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "sym_name") {
       prop.sym_name = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.sym_name)>>(value);
       return;
    }
}

void GtLibOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.sym_name) attrs.append("sym_name", prop.sym_name);
}

::llvm::LogicalResult GtLibOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getSymNameAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Calyx1(attr, "sym_name", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult GtLibOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.sym_name)))
    return ::mlir::failure();
  return ::mlir::success();
}

void GtLibOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.sym_name);
}

::llvm::StringRef GtLibOp::getSymName() {
  auto attr = getSymNameAttr();
  return attr.getValue();
}

void GtLibOp::setSymName(::llvm::StringRef attrValue) {
  getProperties().sym_name = ::mlir::Builder((*this)->getContext()).getStringAttr(attrValue);
}

void GtLibOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, StringRef sym_name, ::mlir::TypeRange resultTypes) {
      odsState.addAttribute(mlir::SymbolTable::getSymbolAttrName(), odsBuilder.getStringAttr(sym_name));
      odsState.addTypes(resultTypes);
    
}

GtLibOp GtLibOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, StringRef sym_name, ::mlir::TypeRange resultTypes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(resultTypes)>(resultTypes));
  auto __res__ = ::llvm::dyn_cast<GtLibOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

GtLibOp GtLibOp::create(::mlir::ImplicitLocOpBuilder &builder, StringRef sym_name, ::mlir::TypeRange resultTypes) {
  return create(builder, builder.getLoc(), std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(resultTypes)>(resultTypes));
}

::llvm::LogicalResult GtLibOp::verifyInvariantsImpl() {
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;
  if (!tblgen_sym_name) return emitOpError("requires attribute 'sym_name'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Calyx1(*this, tblgen_sym_name, "sym_name")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx5(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSResults(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx5(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup2 = getODSResults(2);

    for (auto v : valueGroup2) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx1(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  if (!((std::equal_to<>()( (*this->getODSResults(0).begin()).getType() , (*this->getODSResults(1).begin()).getType()))))
    return emitOpError("failed to verify that lhs and rhs types should be equivalent");
  return ::mlir::success();
}

::llvm::LogicalResult GtLibOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult GtLibOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::StringAttr sym_nameAttr;
  ::llvm::SmallVector<::mlir::Type, 1> allResultTypes;

  if (parser.parseSymbolName(sym_nameAttr))
    return ::mlir::failure();
  if (sym_nameAttr) result.getOrAddProperties<GtLibOp::Properties>().sym_name = sym_nameAttr;
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

  if (parser.parseTypeList(allResultTypes))
    return ::mlir::failure();
  result.addTypes(allResultTypes);
  return ::mlir::success();
}

void GtLibOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter.printSymbolName(getSymNameAttr().getValue());
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("sym_name");
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
  _odsPrinter << getOperation()->getResultTypes();
}


} // namespace circt::calyx
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::calyx::GtLibOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::calyx::detail::GtLibOpGenericAdaptorBase::Properties)

namespace circt::calyx {


//===----------------------------------------------------------------------===//
// ::circt::calyx::IfOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

IfOpGenericAdaptorBase::IfOpGenericAdaptorBase(IfOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::std::optional< ::llvm::StringRef > IfOpGenericAdaptorBase::getGroupName() {
  auto attr = getGroupNameAttr();
  return attr ? ::std::optional< ::llvm::StringRef >(attr.getValue()) : (::std::nullopt);
}


} // namespace detail
IfOpAdaptor::IfOpAdaptor(IfOp op) : IfOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult IfOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_groupName = getProperties().groupName; (void)tblgen_groupName;

  if (tblgen_groupName && !((::llvm::isa<::mlir::FlatSymbolRefAttr>(tblgen_groupName))))
    return emitError(loc, "'calyx.if' op attribute 'groupName' failed to satisfy constraint: flat symbol reference attribute");
  return ::mlir::success();
}

::llvm::LogicalResult IfOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.groupName;
       auto attr = dict.get("groupName");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `groupName` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  return ::mlir::success();
}

::mlir::Attribute IfOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.groupName;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("groupName",
                                       propStorage));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code IfOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.groupName.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> IfOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "groupName")
      return prop.groupName;
  return std::nullopt;
}

void IfOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "groupName") {
       prop.groupName = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.groupName)>>(value);
       return;
    }
}

void IfOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.groupName) attrs.append("groupName", prop.groupName);
}

::llvm::LogicalResult IfOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getGroupNameAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Calyx8(attr, "groupName", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult IfOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readOptionalAttribute(prop.groupName)))
    return ::mlir::failure();
  return ::mlir::success();
}

void IfOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;

  writer.writeOptionalAttribute(prop.groupName);
}

::std::optional< ::llvm::StringRef > IfOp::getGroupName() {
  auto attr = getGroupNameAttr();
  return attr ? ::std::optional< ::llvm::StringRef >(attr.getValue()) : (::std::nullopt);
}

void IfOp::setGroupName(::std::optional<::llvm::StringRef> attrValue) {
    auto &odsProp = getProperties().groupName;
    if (attrValue)
      odsProp = ::mlir::SymbolRefAttr::get(::mlir::Builder((*this)->getContext()).getContext(), *attrValue);
    else
      odsProp = nullptr;
}

void IfOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value cond, FlatSymbolRefAttr groupName, bool initializeElseBody) {
        odsState.addOperands(cond);
        if (groupName)
          odsState.addAttribute("groupName", groupName);

        Region *thenRegion = odsState.addRegion();
        Region *elseRegion = odsState.addRegion();
        thenRegion->push_back(new Block());
        if (initializeElseBody)
          elseRegion->push_back(new Block());
    
}

IfOp IfOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, Value cond, FlatSymbolRefAttr groupName, bool initializeElseBody) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(cond)>(cond), std::forward<decltype(groupName)>(groupName), std::forward<decltype(initializeElseBody)>(initializeElseBody));
  auto __res__ = ::llvm::dyn_cast<IfOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

IfOp IfOp::create(::mlir::ImplicitLocOpBuilder &builder, Value cond, FlatSymbolRefAttr groupName, bool initializeElseBody) {
  return create(builder, builder.getLoc(), std::forward<decltype(cond)>(cond), std::forward<decltype(groupName)>(groupName), std::forward<decltype(initializeElseBody)>(initializeElseBody));
}

::llvm::LogicalResult IfOp::verifyInvariantsImpl() {
  auto tblgen_groupName = getProperties().groupName; (void)tblgen_groupName;

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Calyx8(*this, tblgen_groupName, "groupName")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;

    for (auto &region : ::llvm::MutableArrayRef((*this)->getRegion(0)))
      if (::mlir::failed(__mlir_ods_local_region_constraint_Calyx1(*this, region, "thenRegion", index++)))
        return ::mlir::failure();

    for (auto &region : ::llvm::MutableArrayRef((*this)->getRegion(1)))
      if (::mlir::failed(__mlir_ods_local_region_constraint_Calyx2(*this, region, "elseRegion", index++)))
        return ::mlir::failure();
  }
  return ::mlir::success();
}

::llvm::LogicalResult IfOp::verifyInvariants() {
  if(::mlir::succeeded(verifyInvariantsImpl()) && ::mlir::succeeded(verify()))
    return ::mlir::success();
  return ::mlir::failure();
}

::mlir::ParseResult IfOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::OpAsmParser::UnresolvedOperand condRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> condOperands(&condRawOperand, 1);  ::llvm::SMLoc condOperandsLoc;
  (void)condOperandsLoc;
  ::mlir::FlatSymbolRefAttr groupNameAttr;
  std::unique_ptr<::mlir::Region> thenRegionRegion = std::make_unique<::mlir::Region>();
  std::unique_ptr<::mlir::Region> elseRegionRegion = std::make_unique<::mlir::Region>();

  condOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(condRawOperand))
    return ::mlir::failure();
  if (::mlir::succeeded(parser.parseOptionalKeyword("with"))) {

  if (parser.parseCustomAttributeWithFallback(groupNameAttr, parser.getBuilder().getType<::mlir::NoneType>())) {
    return ::mlir::failure();
  }
  if (groupNameAttr) result.getOrAddProperties<IfOp::Properties>().groupName = groupNameAttr;
  }

  if (parser.parseRegion(*thenRegionRegion))
    return ::mlir::failure();

  if (thenRegionRegion->empty()) thenRegionRegion->emplaceBlock();
  if (::mlir::succeeded(parser.parseOptionalKeyword("else"))) {

  if (parser.parseRegion(*elseRegionRegion))
    return ::mlir::failure();

  if (elseRegionRegion->empty()) elseRegionRegion->emplaceBlock();
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
  result.addRegion(std::move(thenRegionRegion));
  result.addRegion(std::move(elseRegionRegion));
  ::mlir::Type odsBuildableType0 = parser.getBuilder().getIntegerType(1);
  if (parser.resolveOperands(condOperands, odsBuildableType0, condOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void IfOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter << getCond();
  if (getGroupNameAttr()) {
    _odsPrinter << ' ' << "with";
    _odsPrinter << ' ';
    _odsPrinter.printAttributeWithoutType(getGroupNameAttr());
  }
  _odsPrinter << ' ';
  _odsPrinter.printRegion(getThenRegion());
  if (!getElseRegion().empty()) {
    _odsPrinter << ' ' << "else";
    _odsPrinter << ' ';
    _odsPrinter.printRegion(getElseRegion());
  }
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("groupName");
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
}


} // namespace circt::calyx
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::calyx::IfOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::calyx::detail::IfOpGenericAdaptorBase::Properties)

namespace circt::calyx {


//===----------------------------------------------------------------------===//
// ::circt::calyx::InstanceOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

InstanceOpGenericAdaptorBase::InstanceOpGenericAdaptorBase(InstanceOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::llvm::StringRef InstanceOpGenericAdaptorBase::getSymName() {
  auto attr = getSymNameAttr();
  return attr.getValue();
}

::llvm::StringRef InstanceOpGenericAdaptorBase::getComponentName() {
  auto attr = getComponentNameAttr();
  return attr.getValue();
}


} // namespace detail
InstanceOpAdaptor::InstanceOpAdaptor(InstanceOp op) : InstanceOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult InstanceOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_componentName = getProperties().componentName; (void)tblgen_componentName;
  if (!tblgen_componentName) return emitError(loc, "'calyx.instance' op requires attribute 'componentName'");
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;
  if (!tblgen_sym_name) return emitError(loc, "'calyx.instance' op requires attribute 'sym_name'");

  if (tblgen_sym_name && !((::llvm::isa<::mlir::StringAttr>(tblgen_sym_name))))
    return emitError(loc, "'calyx.instance' op attribute 'sym_name' failed to satisfy constraint: string attribute");

  if (tblgen_componentName && !((::llvm::isa<::mlir::FlatSymbolRefAttr>(tblgen_componentName))))
    return emitError(loc, "'calyx.instance' op attribute 'componentName' failed to satisfy constraint: flat symbol reference attribute");
  return ::mlir::success();
}

std::pair<unsigned, unsigned> InstanceOp::getODSResultIndexAndLength(unsigned index) {
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

::llvm::LogicalResult InstanceOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.componentName;
       auto attr = dict.get("componentName");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `componentName` in property conversion: " << attr;
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

::mlir::Attribute InstanceOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.componentName;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("componentName",
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

llvm::hash_code InstanceOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.componentName.getAsOpaquePointer()), 
    llvm::hash_value(prop.sym_name.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> InstanceOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "componentName")
      return prop.componentName;

    if (name == "sym_name")
      return prop.sym_name;
  return std::nullopt;
}

void InstanceOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "componentName") {
       prop.componentName = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.componentName)>>(value);
       return;
    }

    if (name == "sym_name") {
       prop.sym_name = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.sym_name)>>(value);
       return;
    }
}

void InstanceOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.componentName) attrs.append("componentName", prop.componentName);

    if (prop.sym_name) attrs.append("sym_name", prop.sym_name);
}

::llvm::LogicalResult InstanceOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getComponentNameAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Calyx8(attr, "componentName", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getSymNameAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Calyx1(attr, "sym_name", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult InstanceOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.componentName)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readAttribute(prop.sym_name)))
    return ::mlir::failure();
  return ::mlir::success();
}

void InstanceOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.componentName);
  writer.writeAttribute(prop.sym_name);
}

::llvm::StringRef InstanceOp::getSymName() {
  auto attr = getSymNameAttr();
  return attr.getValue();
}

::llvm::StringRef InstanceOp::getComponentName() {
  auto attr = getComponentNameAttr();
  return attr.getValue();
}

void InstanceOp::setSymName(::llvm::StringRef attrValue) {
  getProperties().sym_name = ::mlir::Builder((*this)->getContext()).getStringAttr(attrValue);
}

void InstanceOp::setComponentName(::llvm::StringRef attrValue) {
  getProperties().componentName = ::mlir::SymbolRefAttr::get(::mlir::Builder((*this)->getContext()).getContext(), attrValue);
}

void InstanceOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange results, ::mlir::StringAttr sym_name, ::mlir::FlatSymbolRefAttr componentName) {
  odsState.getOrAddProperties<Properties>().sym_name = sym_name;
  odsState.getOrAddProperties<Properties>().componentName = componentName;
  odsState.addTypes(results);
}

InstanceOp InstanceOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange results, ::mlir::StringAttr sym_name, ::mlir::FlatSymbolRefAttr componentName) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(results)>(results), std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(componentName)>(componentName));
  auto __res__ = ::llvm::dyn_cast<InstanceOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

InstanceOp InstanceOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange results, ::mlir::StringAttr sym_name, ::mlir::FlatSymbolRefAttr componentName) {
  return create(builder, builder.getLoc(), std::forward<decltype(results)>(results), std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(componentName)>(componentName));
}

void InstanceOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange results, ::llvm::StringRef sym_name, ::llvm::StringRef componentName) {
  odsState.getOrAddProperties<Properties>().sym_name = odsBuilder.getStringAttr(sym_name);
  odsState.getOrAddProperties<Properties>().componentName = ::mlir::SymbolRefAttr::get(odsBuilder.getContext(), componentName);
  odsState.addTypes(results);
}

InstanceOp InstanceOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange results, ::llvm::StringRef sym_name, ::llvm::StringRef componentName) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(results)>(results), std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(componentName)>(componentName));
  auto __res__ = ::llvm::dyn_cast<InstanceOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

InstanceOp InstanceOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange results, ::llvm::StringRef sym_name, ::llvm::StringRef componentName) {
  return create(builder, builder.getLoc(), std::forward<decltype(results)>(results), std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(componentName)>(componentName));
}

void InstanceOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
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
  auto tblgen_componentName = getProperties().componentName; (void)tblgen_componentName;
  if (!tblgen_componentName) return emitOpError("requires attribute 'componentName'");
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;
  if (!tblgen_sym_name) return emitOpError("requires attribute 'sym_name'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Calyx1(*this, tblgen_sym_name, "sym_name")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Calyx8(*this, tblgen_componentName, "componentName")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx7(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult InstanceOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult InstanceOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::StringAttr sym_nameAttr;
  ::mlir::FlatSymbolRefAttr componentNameAttr;
  ::llvm::SmallVector<::mlir::Type, 1> resultsTypes;

  if (parser.parseSymbolName(sym_nameAttr))
    return ::mlir::failure();
  if (sym_nameAttr) result.getOrAddProperties<InstanceOp::Properties>().sym_name = sym_nameAttr;
  if (parser.parseKeyword("of"))
    return ::mlir::failure();

  if (parser.parseCustomAttributeWithFallback(componentNameAttr, parser.getBuilder().getType<::mlir::NoneType>())) {
    return ::mlir::failure();
  }
  if (componentNameAttr) result.getOrAddProperties<InstanceOp::Properties>().componentName = componentNameAttr;
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

  if (parser.parseTypeList(resultsTypes))
    return ::mlir::failure();
  }
  result.addTypes(resultsTypes);
  return ::mlir::success();
}

void InstanceOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter.printSymbolName(getSymNameAttr().getValue());
  _odsPrinter << ' ' << "of";
  _odsPrinter << ' ';
  _odsPrinter.printAttributeWithoutType(getComponentNameAttr());
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("sym_name");
  elidedAttrs.push_back("componentName");
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  if (!getResults().empty()) {
    _odsPrinter << ' ' << ":";
    _odsPrinter << ' ';
    _odsPrinter << getResults().getTypes();
  }
}


} // namespace circt::calyx
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::calyx::InstanceOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::calyx::detail::InstanceOpGenericAdaptorBase::Properties)

namespace circt::calyx {


//===----------------------------------------------------------------------===//
// ::circt::calyx::IntToFpOpIEEE754 definitions
//===----------------------------------------------------------------------===//

namespace detail {

IntToFpOpIEEE754GenericAdaptorBase::IntToFpOpIEEE754GenericAdaptorBase(IntToFpOpIEEE754 op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::llvm::StringRef IntToFpOpIEEE754GenericAdaptorBase::getSymName() {
  auto attr = getSymNameAttr();
  return attr.getValue();
}


} // namespace detail
IntToFpOpIEEE754Adaptor::IntToFpOpIEEE754Adaptor(IntToFpOpIEEE754 op) : IntToFpOpIEEE754GenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult IntToFpOpIEEE754Adaptor::verify(::mlir::Location loc) {
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;
  if (!tblgen_sym_name) return emitError(loc, "'calyx.ieee754.intToFp' op requires attribute 'sym_name'");

  if (tblgen_sym_name && !((::llvm::isa<::mlir::StringAttr>(tblgen_sym_name))))
    return emitError(loc, "'calyx.ieee754.intToFp' op attribute 'sym_name' failed to satisfy constraint: string attribute");
  return ::mlir::success();
}

::llvm::LogicalResult IntToFpOpIEEE754::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
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

::mlir::Attribute IntToFpOpIEEE754::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
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

llvm::hash_code IntToFpOpIEEE754::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.sym_name.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> IntToFpOpIEEE754::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "sym_name")
      return prop.sym_name;
  return std::nullopt;
}

void IntToFpOpIEEE754::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "sym_name") {
       prop.sym_name = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.sym_name)>>(value);
       return;
    }
}

void IntToFpOpIEEE754::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.sym_name) attrs.append("sym_name", prop.sym_name);
}

::llvm::LogicalResult IntToFpOpIEEE754::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getSymNameAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Calyx1(attr, "sym_name", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult IntToFpOpIEEE754::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.sym_name)))
    return ::mlir::failure();
  return ::mlir::success();
}

void IntToFpOpIEEE754::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.sym_name);
}

::llvm::StringRef IntToFpOpIEEE754::getSymName() {
  auto attr = getSymNameAttr();
  return attr.getValue();
}

void IntToFpOpIEEE754::setSymName(::llvm::StringRef attrValue) {
  getProperties().sym_name = ::mlir::Builder((*this)->getContext()).getStringAttr(attrValue);
}

void IntToFpOpIEEE754::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, StringRef sym_name, ::mlir::TypeRange resultTypes) {
      odsState.addAttribute(mlir::SymbolTable::getSymbolAttrName(), odsBuilder.getStringAttr(sym_name));
      odsState.addTypes(resultTypes);
    
}

IntToFpOpIEEE754 IntToFpOpIEEE754::create(::mlir::OpBuilder &builder, ::mlir::Location location, StringRef sym_name, ::mlir::TypeRange resultTypes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(resultTypes)>(resultTypes));
  auto __res__ = ::llvm::dyn_cast<IntToFpOpIEEE754>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

IntToFpOpIEEE754 IntToFpOpIEEE754::create(::mlir::ImplicitLocOpBuilder &builder, StringRef sym_name, ::mlir::TypeRange resultTypes) {
  return create(builder, builder.getLoc(), std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(resultTypes)>(resultTypes));
}

::llvm::LogicalResult IntToFpOpIEEE754::verifyInvariantsImpl() {
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;
  if (!tblgen_sym_name) return emitOpError("requires attribute 'sym_name'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Calyx1(*this, tblgen_sym_name, "sym_name")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx1(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSResults(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx1(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup2 = getODSResults(2);

    for (auto v : valueGroup2) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx1(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup3 = getODSResults(3);

    for (auto v : valueGroup3) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx2(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup4 = getODSResults(4);

    for (auto v : valueGroup4) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx1(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup5 = getODSResults(5);

    for (auto v : valueGroup5) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx2(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup6 = getODSResults(6);

    for (auto v : valueGroup6) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx1(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult IntToFpOpIEEE754::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult IntToFpOpIEEE754::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::StringAttr sym_nameAttr;
  ::llvm::SmallVector<::mlir::Type, 1> allResultTypes;

  if (parser.parseSymbolName(sym_nameAttr))
    return ::mlir::failure();
  if (sym_nameAttr) result.getOrAddProperties<IntToFpOpIEEE754::Properties>().sym_name = sym_nameAttr;
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

  if (parser.parseTypeList(allResultTypes))
    return ::mlir::failure();
  result.addTypes(allResultTypes);
  return ::mlir::success();
}

void IntToFpOpIEEE754::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter.printSymbolName(getSymNameAttr().getValue());
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("sym_name");
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
  _odsPrinter << getOperation()->getResultTypes();
}

SmallVector<StringRef> IntToFpOpIEEE754::portNames() {
  return {clkPort, resetPort, goPort, "in", "signedIn", "out", donePort};
}

SmallVector<Direction> IntToFpOpIEEE754::portDirections() {
  return {Input, Input, Input, Input, Input, Output, Output};
}

void IntToFpOpIEEE754::getAsmResultNames(OpAsmSetValueNameFn setNameFn) {
  getCellAsmResultNames(setNameFn, *this, this->portNames());
}

bool IntToFpOpIEEE754::isCombinational() { return false; }

SmallVector<DictionaryAttr> IntToFpOpIEEE754::portAttributes() {
  IntegerAttr isSet = IntegerAttr::get(IntegerType::get(getContext(), 1), 1);
  NamedAttrList go, clk, reset, done;
  go.append(goPort, isSet);
  clk.append(clkPort, isSet);
  reset.append(resetPort, isSet);
  done.append(donePort, isSet);
  return {
    clk.getDictionary(getContext()),
    reset.getDictionary(getContext()),
    go.getDictionary(getContext()),
    DictionaryAttr::get(getContext()), // in
    DictionaryAttr::get(getContext()), // signedIn
    DictionaryAttr::get(getContext()), // out
    done.getDictionary(getContext())
  };
}

} // namespace circt::calyx
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::calyx::IntToFpOpIEEE754)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::calyx::detail::IntToFpOpIEEE754GenericAdaptorBase::Properties)

namespace circt::calyx {


//===----------------------------------------------------------------------===//
// ::circt::calyx::InvokeOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

InvokeOpGenericAdaptorBase::InvokeOpGenericAdaptorBase(InvokeOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

std::pair<unsigned, unsigned> InvokeOpGenericAdaptorBase::getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
  bool isVariadic[] = {true, true};
  int prevVariadicCount = 0;
  for (unsigned i = 0; i < index; ++i)
    if (isVariadic[i]) ++prevVariadicCount;

  // Calculate how many dynamic values a static variadic operand corresponds to.
  // This assumes all static variadic operands have the same dynamic value count.
  int variadicSize = (odsOperandsSize - 0) / 2;
  // `index` passed in as the parameter is the static index which counts each
  // operand (variadic or not) as size 1. So here for each previous static variadic
  // operand, we need to offset by (variadicSize - 1) to get where the dynamic
  // value pack for this static operand starts.
  int start = index + (variadicSize - 1) * prevVariadicCount;
  int size = isVariadic[index] ? variadicSize : 1;
  return {start, size};
}

::llvm::StringRef InvokeOpGenericAdaptorBase::getCallee() {
  auto attr = getCalleeAttr();
  return attr.getValue();
}

::mlir::ArrayAttr InvokeOpGenericAdaptorBase::getRefCellsMap() {
  auto attr = getRefCellsMapAttr();
  return attr;
}

::mlir::ArrayAttr InvokeOpGenericAdaptorBase::getPortNames() {
  auto attr = getPortNamesAttr();
  return attr;
}

::mlir::ArrayAttr InvokeOpGenericAdaptorBase::getInputNames() {
  auto attr = getInputNamesAttr();
  return attr;
}


} // namespace detail
InvokeOpAdaptor::InvokeOpAdaptor(InvokeOp op) : InvokeOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult InvokeOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_callee = getProperties().callee; (void)tblgen_callee;
  if (!tblgen_callee) return emitError(loc, "'calyx.invoke' op requires attribute 'callee'");
  auto tblgen_inputNames = getProperties().inputNames; (void)tblgen_inputNames;
  if (!tblgen_inputNames) return emitError(loc, "'calyx.invoke' op requires attribute 'inputNames'");
  auto tblgen_portNames = getProperties().portNames; (void)tblgen_portNames;
  if (!tblgen_portNames) return emitError(loc, "'calyx.invoke' op requires attribute 'portNames'");
  auto tblgen_refCellsMap = getProperties().refCellsMap; (void)tblgen_refCellsMap;
  if (!tblgen_refCellsMap) return emitError(loc, "'calyx.invoke' op requires attribute 'refCellsMap'");

  if (tblgen_callee && !((::llvm::isa<::mlir::FlatSymbolRefAttr>(tblgen_callee))))
    return emitError(loc, "'calyx.invoke' op attribute 'callee' failed to satisfy constraint: flat symbol reference attribute");

  if (tblgen_refCellsMap && !((::llvm::isa<::mlir::ArrayAttr>(tblgen_refCellsMap))))
    return emitError(loc, "'calyx.invoke' op attribute 'refCellsMap' failed to satisfy constraint: array attribute");

  if (tblgen_portNames && !((::llvm::isa<::mlir::ArrayAttr>(tblgen_portNames))))
    return emitError(loc, "'calyx.invoke' op attribute 'portNames' failed to satisfy constraint: array attribute");

  if (tblgen_inputNames && !((::llvm::isa<::mlir::ArrayAttr>(tblgen_inputNames))))
    return emitError(loc, "'calyx.invoke' op attribute 'inputNames' failed to satisfy constraint: array attribute");
  return ::mlir::success();
}

std::pair<unsigned, unsigned> InvokeOp::getODSOperandIndexAndLength(unsigned index) {
  bool isVariadic[] = {true, true};
  int prevVariadicCount = 0;
  for (unsigned i = 0; i < index; ++i)
    if (isVariadic[i]) ++prevVariadicCount;

  // Calculate how many dynamic values a static variadic operand corresponds to.
  // This assumes all static variadic operands have the same dynamic value count.
  int variadicSize = (getOperation()->getNumOperands() - 0) / 2;
  // `index` passed in as the parameter is the static index which counts each
  // operand (variadic or not) as size 1. So here for each previous static variadic
  // operand, we need to offset by (variadicSize - 1) to get where the dynamic
  // value pack for this static operand starts.
  int start = index + (variadicSize - 1) * prevVariadicCount;
  int size = isVariadic[index] ? variadicSize : 1;
  return {start, size};
}

::mlir::MutableOperandRange InvokeOp::getPortsMutable() {
  auto range = getODSOperandIndexAndLength(0);
  auto mutableRange = ::mlir::MutableOperandRange(getOperation(), range.first, range.second);
  return mutableRange;
}

::mlir::MutableOperandRange InvokeOp::getInputsMutable() {
  auto range = getODSOperandIndexAndLength(1);
  auto mutableRange = ::mlir::MutableOperandRange(getOperation(), range.first, range.second);
  return mutableRange;
}

::llvm::LogicalResult InvokeOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
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
    auto &propStorage = prop.refCellsMap;
       auto attr = dict.get("refCellsMap");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `refCellsMap` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  return ::mlir::success();
}

::mlir::Attribute InvokeOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.callee;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("callee",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.inputNames;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("inputNames",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.portNames;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("portNames",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.refCellsMap;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("refCellsMap",
                                       propStorage));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code InvokeOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.callee.getAsOpaquePointer()), 
    llvm::hash_value(prop.inputNames.getAsOpaquePointer()), 
    llvm::hash_value(prop.portNames.getAsOpaquePointer()), 
    llvm::hash_value(prop.refCellsMap.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> InvokeOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "callee")
      return prop.callee;

    if (name == "inputNames")
      return prop.inputNames;

    if (name == "portNames")
      return prop.portNames;

    if (name == "refCellsMap")
      return prop.refCellsMap;
  return std::nullopt;
}

void InvokeOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "callee") {
       prop.callee = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.callee)>>(value);
       return;
    }

    if (name == "inputNames") {
       prop.inputNames = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.inputNames)>>(value);
       return;
    }

    if (name == "portNames") {
       prop.portNames = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.portNames)>>(value);
       return;
    }

    if (name == "refCellsMap") {
       prop.refCellsMap = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.refCellsMap)>>(value);
       return;
    }
}

void InvokeOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.callee) attrs.append("callee", prop.callee);

    if (prop.inputNames) attrs.append("inputNames", prop.inputNames);

    if (prop.portNames) attrs.append("portNames", prop.portNames);

    if (prop.refCellsMap) attrs.append("refCellsMap", prop.refCellsMap);
}

::llvm::LogicalResult InvokeOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getCalleeAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Calyx8(attr, "callee", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getInputNamesAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Calyx4(attr, "inputNames", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getPortNamesAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Calyx4(attr, "portNames", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getRefCellsMapAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Calyx4(attr, "refCellsMap", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult InvokeOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.callee)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readAttribute(prop.inputNames)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readAttribute(prop.portNames)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readAttribute(prop.refCellsMap)))
    return ::mlir::failure();
  return ::mlir::success();
}

void InvokeOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.callee);
  writer.writeAttribute(prop.inputNames);
  writer.writeAttribute(prop.portNames);
  writer.writeAttribute(prop.refCellsMap);
}

::llvm::StringRef InvokeOp::getCallee() {
  auto attr = getCalleeAttr();
  return attr.getValue();
}

::mlir::ArrayAttr InvokeOp::getRefCellsMap() {
  auto attr = getRefCellsMapAttr();
  return attr;
}

::mlir::ArrayAttr InvokeOp::getPortNames() {
  auto attr = getPortNamesAttr();
  return attr;
}

::mlir::ArrayAttr InvokeOp::getInputNames() {
  auto attr = getInputNamesAttr();
  return attr;
}

void InvokeOp::setCallee(::llvm::StringRef attrValue) {
  getProperties().callee = ::mlir::SymbolRefAttr::get(::mlir::Builder((*this)->getContext()).getContext(), attrValue);
}

void InvokeOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::FlatSymbolRefAttr callee, ::mlir::ValueRange ports, ::mlir::ValueRange inputs, ::mlir::ArrayAttr refCellsMap, ::mlir::ArrayAttr portNames, ::mlir::ArrayAttr inputNames) {
  odsState.addOperands(ports);
  odsState.addOperands(inputs);
  odsState.getOrAddProperties<Properties>().callee = callee;
  odsState.getOrAddProperties<Properties>().refCellsMap = refCellsMap;
  odsState.getOrAddProperties<Properties>().portNames = portNames;
  odsState.getOrAddProperties<Properties>().inputNames = inputNames;
}

InvokeOp InvokeOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::FlatSymbolRefAttr callee, ::mlir::ValueRange ports, ::mlir::ValueRange inputs, ::mlir::ArrayAttr refCellsMap, ::mlir::ArrayAttr portNames, ::mlir::ArrayAttr inputNames) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(callee)>(callee), std::forward<decltype(ports)>(ports), std::forward<decltype(inputs)>(inputs), std::forward<decltype(refCellsMap)>(refCellsMap), std::forward<decltype(portNames)>(portNames), std::forward<decltype(inputNames)>(inputNames));
  auto __res__ = ::llvm::dyn_cast<InvokeOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

InvokeOp InvokeOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::FlatSymbolRefAttr callee, ::mlir::ValueRange ports, ::mlir::ValueRange inputs, ::mlir::ArrayAttr refCellsMap, ::mlir::ArrayAttr portNames, ::mlir::ArrayAttr inputNames) {
  return create(builder, builder.getLoc(), std::forward<decltype(callee)>(callee), std::forward<decltype(ports)>(ports), std::forward<decltype(inputs)>(inputs), std::forward<decltype(refCellsMap)>(refCellsMap), std::forward<decltype(portNames)>(portNames), std::forward<decltype(inputNames)>(inputNames));
}

void InvokeOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::FlatSymbolRefAttr callee, ::mlir::ValueRange ports, ::mlir::ValueRange inputs, ::mlir::ArrayAttr refCellsMap, ::mlir::ArrayAttr portNames, ::mlir::ArrayAttr inputNames) {
  odsState.addOperands(ports);
  odsState.addOperands(inputs);
  odsState.getOrAddProperties<Properties>().callee = callee;
  odsState.getOrAddProperties<Properties>().refCellsMap = refCellsMap;
  odsState.getOrAddProperties<Properties>().portNames = portNames;
  odsState.getOrAddProperties<Properties>().inputNames = inputNames;
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

InvokeOp InvokeOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::FlatSymbolRefAttr callee, ::mlir::ValueRange ports, ::mlir::ValueRange inputs, ::mlir::ArrayAttr refCellsMap, ::mlir::ArrayAttr portNames, ::mlir::ArrayAttr inputNames) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(callee)>(callee), std::forward<decltype(ports)>(ports), std::forward<decltype(inputs)>(inputs), std::forward<decltype(refCellsMap)>(refCellsMap), std::forward<decltype(portNames)>(portNames), std::forward<decltype(inputNames)>(inputNames));
  auto __res__ = ::llvm::dyn_cast<InvokeOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

InvokeOp InvokeOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::FlatSymbolRefAttr callee, ::mlir::ValueRange ports, ::mlir::ValueRange inputs, ::mlir::ArrayAttr refCellsMap, ::mlir::ArrayAttr portNames, ::mlir::ArrayAttr inputNames) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(callee)>(callee), std::forward<decltype(ports)>(ports), std::forward<decltype(inputs)>(inputs), std::forward<decltype(refCellsMap)>(refCellsMap), std::forward<decltype(portNames)>(portNames), std::forward<decltype(inputNames)>(inputNames));
}

void InvokeOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::llvm::StringRef callee, ::mlir::ValueRange ports, ::mlir::ValueRange inputs, ::mlir::ArrayAttr refCellsMap, ::mlir::ArrayAttr portNames, ::mlir::ArrayAttr inputNames) {
  odsState.addOperands(ports);
  odsState.addOperands(inputs);
  odsState.getOrAddProperties<Properties>().callee = ::mlir::SymbolRefAttr::get(odsBuilder.getContext(), callee);
  odsState.getOrAddProperties<Properties>().refCellsMap = refCellsMap;
  odsState.getOrAddProperties<Properties>().portNames = portNames;
  odsState.getOrAddProperties<Properties>().inputNames = inputNames;
}

InvokeOp InvokeOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::llvm::StringRef callee, ::mlir::ValueRange ports, ::mlir::ValueRange inputs, ::mlir::ArrayAttr refCellsMap, ::mlir::ArrayAttr portNames, ::mlir::ArrayAttr inputNames) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(callee)>(callee), std::forward<decltype(ports)>(ports), std::forward<decltype(inputs)>(inputs), std::forward<decltype(refCellsMap)>(refCellsMap), std::forward<decltype(portNames)>(portNames), std::forward<decltype(inputNames)>(inputNames));
  auto __res__ = ::llvm::dyn_cast<InvokeOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

InvokeOp InvokeOp::create(::mlir::ImplicitLocOpBuilder &builder, ::llvm::StringRef callee, ::mlir::ValueRange ports, ::mlir::ValueRange inputs, ::mlir::ArrayAttr refCellsMap, ::mlir::ArrayAttr portNames, ::mlir::ArrayAttr inputNames) {
  return create(builder, builder.getLoc(), std::forward<decltype(callee)>(callee), std::forward<decltype(ports)>(ports), std::forward<decltype(inputs)>(inputs), std::forward<decltype(refCellsMap)>(refCellsMap), std::forward<decltype(portNames)>(portNames), std::forward<decltype(inputNames)>(inputNames));
}

void InvokeOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::llvm::StringRef callee, ::mlir::ValueRange ports, ::mlir::ValueRange inputs, ::mlir::ArrayAttr refCellsMap, ::mlir::ArrayAttr portNames, ::mlir::ArrayAttr inputNames) {
  odsState.addOperands(ports);
  odsState.addOperands(inputs);
  odsState.getOrAddProperties<Properties>().callee = ::mlir::SymbolRefAttr::get(odsBuilder.getContext(), callee);
  odsState.getOrAddProperties<Properties>().refCellsMap = refCellsMap;
  odsState.getOrAddProperties<Properties>().portNames = portNames;
  odsState.getOrAddProperties<Properties>().inputNames = inputNames;
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

InvokeOp InvokeOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::llvm::StringRef callee, ::mlir::ValueRange ports, ::mlir::ValueRange inputs, ::mlir::ArrayAttr refCellsMap, ::mlir::ArrayAttr portNames, ::mlir::ArrayAttr inputNames) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(callee)>(callee), std::forward<decltype(ports)>(ports), std::forward<decltype(inputs)>(inputs), std::forward<decltype(refCellsMap)>(refCellsMap), std::forward<decltype(portNames)>(portNames), std::forward<decltype(inputNames)>(inputNames));
  auto __res__ = ::llvm::dyn_cast<InvokeOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

InvokeOp InvokeOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::llvm::StringRef callee, ::mlir::ValueRange ports, ::mlir::ValueRange inputs, ::mlir::ArrayAttr refCellsMap, ::mlir::ArrayAttr portNames, ::mlir::ArrayAttr inputNames) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(callee)>(callee), std::forward<decltype(ports)>(ports), std::forward<decltype(inputs)>(inputs), std::forward<decltype(refCellsMap)>(refCellsMap), std::forward<decltype(portNames)>(portNames), std::forward<decltype(inputNames)>(inputNames));
}

void InvokeOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<InvokeOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

InvokeOp InvokeOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<InvokeOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

InvokeOp InvokeOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void InvokeOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

InvokeOp InvokeOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<InvokeOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

InvokeOp InvokeOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult InvokeOp::verifyInvariantsImpl() {
  auto tblgen_callee = getProperties().callee; (void)tblgen_callee;
  if (!tblgen_callee) return emitOpError("requires attribute 'callee'");
  auto tblgen_inputNames = getProperties().inputNames; (void)tblgen_inputNames;
  if (!tblgen_inputNames) return emitOpError("requires attribute 'inputNames'");
  auto tblgen_portNames = getProperties().portNames; (void)tblgen_portNames;
  if (!tblgen_portNames) return emitOpError("requires attribute 'portNames'");
  auto tblgen_refCellsMap = getProperties().refCellsMap; (void)tblgen_refCellsMap;
  if (!tblgen_refCellsMap) return emitOpError("requires attribute 'refCellsMap'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Calyx8(*this, tblgen_callee, "callee")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Calyx4(*this, tblgen_refCellsMap, "refCellsMap")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Calyx4(*this, tblgen_portNames, "portNames")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Calyx4(*this, tblgen_inputNames, "inputNames")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx7(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSOperands(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx7(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult InvokeOp::verifyInvariants() {
  if(::mlir::succeeded(verifyInvariantsImpl()) && ::mlir::succeeded(verify()))
    return ::mlir::success();
  return ::mlir::failure();
}

::llvm::LogicalResult InvokeOp::setPropertiesFromParsedAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
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

    auto &propStorage = prop.callee;
    auto calleeAttrName = ::mlir::StringAttr::get(ctx, "callee");
    auto attr = dict.get(calleeAttrName);
    usedKeys.insert(calleeAttrName);
    if (attr || /*isRequired=*/true) {
      if (!attr) {
        emitError() << "expected key entry for callee in DictionaryAttr to set "
                   "Properties.";
        return ::mlir::failure();
      }
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `callee` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  {

    auto &propStorage = prop.refCellsMap;
    auto refCellsMapAttrName = ::mlir::StringAttr::get(ctx, "refCellsMap");
    auto attr = dict.get(refCellsMapAttrName);
    usedKeys.insert(refCellsMapAttrName);
    if (attr || /*isRequired=*/true) {
      if (!attr) {
        emitError() << "expected key entry for refCellsMap in DictionaryAttr to set "
                   "Properties.";
        return ::mlir::failure();
      }
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `refCellsMap` in property conversion: " << attr;
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

  for (::mlir::NamedAttribute attr : dict) {
    if (!usedKeys.contains(attr.getName()))
      return emitError() << "unknown key '" << attr.getName() <<
          "' when parsing properties dictionary";
  }
  return ::mlir::success();
}


} // namespace circt::calyx
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::calyx::InvokeOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::calyx::detail::InvokeOpGenericAdaptorBase::Properties)

namespace circt::calyx {


//===----------------------------------------------------------------------===//
// ::circt::calyx::LeLibOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

LeLibOpGenericAdaptorBase::LeLibOpGenericAdaptorBase(LeLibOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::llvm::StringRef LeLibOpGenericAdaptorBase::getSymName() {
  auto attr = getSymNameAttr();
  return attr.getValue();
}


} // namespace detail
LeLibOpAdaptor::LeLibOpAdaptor(LeLibOp op) : LeLibOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult LeLibOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;
  if (!tblgen_sym_name) return emitError(loc, "'calyx.std_le' op requires attribute 'sym_name'");

  if (tblgen_sym_name && !((::llvm::isa<::mlir::StringAttr>(tblgen_sym_name))))
    return emitError(loc, "'calyx.std_le' op attribute 'sym_name' failed to satisfy constraint: string attribute");
  return ::mlir::success();
}

::llvm::LogicalResult LeLibOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
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

::mlir::Attribute LeLibOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
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

llvm::hash_code LeLibOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.sym_name.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> LeLibOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "sym_name")
      return prop.sym_name;
  return std::nullopt;
}

void LeLibOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "sym_name") {
       prop.sym_name = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.sym_name)>>(value);
       return;
    }
}

void LeLibOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.sym_name) attrs.append("sym_name", prop.sym_name);
}

::llvm::LogicalResult LeLibOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getSymNameAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Calyx1(attr, "sym_name", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult LeLibOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.sym_name)))
    return ::mlir::failure();
  return ::mlir::success();
}

void LeLibOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.sym_name);
}

::llvm::StringRef LeLibOp::getSymName() {
  auto attr = getSymNameAttr();
  return attr.getValue();
}

void LeLibOp::setSymName(::llvm::StringRef attrValue) {
  getProperties().sym_name = ::mlir::Builder((*this)->getContext()).getStringAttr(attrValue);
}

void LeLibOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, StringRef sym_name, ::mlir::TypeRange resultTypes) {
      odsState.addAttribute(mlir::SymbolTable::getSymbolAttrName(), odsBuilder.getStringAttr(sym_name));
      odsState.addTypes(resultTypes);
    
}

LeLibOp LeLibOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, StringRef sym_name, ::mlir::TypeRange resultTypes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(resultTypes)>(resultTypes));
  auto __res__ = ::llvm::dyn_cast<LeLibOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

LeLibOp LeLibOp::create(::mlir::ImplicitLocOpBuilder &builder, StringRef sym_name, ::mlir::TypeRange resultTypes) {
  return create(builder, builder.getLoc(), std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(resultTypes)>(resultTypes));
}

::llvm::LogicalResult LeLibOp::verifyInvariantsImpl() {
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;
  if (!tblgen_sym_name) return emitOpError("requires attribute 'sym_name'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Calyx1(*this, tblgen_sym_name, "sym_name")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx5(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSResults(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx5(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup2 = getODSResults(2);

    for (auto v : valueGroup2) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx1(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  if (!((std::equal_to<>()( (*this->getODSResults(0).begin()).getType() , (*this->getODSResults(1).begin()).getType()))))
    return emitOpError("failed to verify that lhs and rhs types should be equivalent");
  return ::mlir::success();
}

::llvm::LogicalResult LeLibOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult LeLibOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::StringAttr sym_nameAttr;
  ::llvm::SmallVector<::mlir::Type, 1> allResultTypes;

  if (parser.parseSymbolName(sym_nameAttr))
    return ::mlir::failure();
  if (sym_nameAttr) result.getOrAddProperties<LeLibOp::Properties>().sym_name = sym_nameAttr;
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

  if (parser.parseTypeList(allResultTypes))
    return ::mlir::failure();
  result.addTypes(allResultTypes);
  return ::mlir::success();
}

void LeLibOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter.printSymbolName(getSymNameAttr().getValue());
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("sym_name");
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
  _odsPrinter << getOperation()->getResultTypes();
}


} // namespace circt::calyx
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::calyx::LeLibOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::calyx::detail::LeLibOpGenericAdaptorBase::Properties)

namespace circt::calyx {


//===----------------------------------------------------------------------===//
// ::circt::calyx::LshLibOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

LshLibOpGenericAdaptorBase::LshLibOpGenericAdaptorBase(LshLibOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::llvm::StringRef LshLibOpGenericAdaptorBase::getSymName() {
  auto attr = getSymNameAttr();
  return attr.getValue();
}


} // namespace detail
LshLibOpAdaptor::LshLibOpAdaptor(LshLibOp op) : LshLibOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult LshLibOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;
  if (!tblgen_sym_name) return emitError(loc, "'calyx.std_lsh' op requires attribute 'sym_name'");

  if (tblgen_sym_name && !((::llvm::isa<::mlir::StringAttr>(tblgen_sym_name))))
    return emitError(loc, "'calyx.std_lsh' op attribute 'sym_name' failed to satisfy constraint: string attribute");
  return ::mlir::success();
}

::llvm::LogicalResult LshLibOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
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

::mlir::Attribute LshLibOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
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

llvm::hash_code LshLibOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.sym_name.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> LshLibOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "sym_name")
      return prop.sym_name;
  return std::nullopt;
}

void LshLibOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "sym_name") {
       prop.sym_name = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.sym_name)>>(value);
       return;
    }
}

void LshLibOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.sym_name) attrs.append("sym_name", prop.sym_name);
}

::llvm::LogicalResult LshLibOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getSymNameAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Calyx1(attr, "sym_name", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult LshLibOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.sym_name)))
    return ::mlir::failure();
  return ::mlir::success();
}

void LshLibOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.sym_name);
}

::llvm::StringRef LshLibOp::getSymName() {
  auto attr = getSymNameAttr();
  return attr.getValue();
}

void LshLibOp::setSymName(::llvm::StringRef attrValue) {
  getProperties().sym_name = ::mlir::Builder((*this)->getContext()).getStringAttr(attrValue);
}

void LshLibOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, StringRef sym_name, ::mlir::TypeRange resultTypes) {
      odsState.addAttribute(mlir::SymbolTable::getSymbolAttrName(), odsBuilder.getStringAttr(sym_name));
      odsState.addTypes(resultTypes);
    
}

LshLibOp LshLibOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, StringRef sym_name, ::mlir::TypeRange resultTypes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(resultTypes)>(resultTypes));
  auto __res__ = ::llvm::dyn_cast<LshLibOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

LshLibOp LshLibOp::create(::mlir::ImplicitLocOpBuilder &builder, StringRef sym_name, ::mlir::TypeRange resultTypes) {
  return create(builder, builder.getLoc(), std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(resultTypes)>(resultTypes));
}

::llvm::LogicalResult LshLibOp::verifyInvariantsImpl() {
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;
  if (!tblgen_sym_name) return emitOpError("requires attribute 'sym_name'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Calyx1(*this, tblgen_sym_name, "sym_name")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx5(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSResults(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx5(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup2 = getODSResults(2);

    for (auto v : valueGroup2) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx5(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  if (!((std::equal_to<>()( (*this->getODSResults(0).begin()).getType() , (*this->getODSResults(2).begin()).getType()))))
    return emitOpError("failed to verify that lhs and rhs types should be equivalent");
  if (!((std::equal_to<>()( (*this->getODSResults(0).begin()).getType() , (*this->getODSResults(1).begin()).getType()))))
    return emitOpError("failed to verify that lhs and rhs types should be equivalent");
  return ::mlir::success();
}

::llvm::LogicalResult LshLibOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult LshLibOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::StringAttr sym_nameAttr;
  ::llvm::SmallVector<::mlir::Type, 1> allResultTypes;

  if (parser.parseSymbolName(sym_nameAttr))
    return ::mlir::failure();
  if (sym_nameAttr) result.getOrAddProperties<LshLibOp::Properties>().sym_name = sym_nameAttr;
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

  if (parser.parseTypeList(allResultTypes))
    return ::mlir::failure();
  result.addTypes(allResultTypes);
  return ::mlir::success();
}

void LshLibOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter.printSymbolName(getSymNameAttr().getValue());
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("sym_name");
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
  _odsPrinter << getOperation()->getResultTypes();
}


} // namespace circt::calyx
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::calyx::LshLibOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::calyx::detail::LshLibOpGenericAdaptorBase::Properties)

namespace circt::calyx {


//===----------------------------------------------------------------------===//
// ::circt::calyx::LtLibOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

LtLibOpGenericAdaptorBase::LtLibOpGenericAdaptorBase(LtLibOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::llvm::StringRef LtLibOpGenericAdaptorBase::getSymName() {
  auto attr = getSymNameAttr();
  return attr.getValue();
}


} // namespace detail
LtLibOpAdaptor::LtLibOpAdaptor(LtLibOp op) : LtLibOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult LtLibOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;
  if (!tblgen_sym_name) return emitError(loc, "'calyx.std_lt' op requires attribute 'sym_name'");

  if (tblgen_sym_name && !((::llvm::isa<::mlir::StringAttr>(tblgen_sym_name))))
    return emitError(loc, "'calyx.std_lt' op attribute 'sym_name' failed to satisfy constraint: string attribute");
  return ::mlir::success();
}

::llvm::LogicalResult LtLibOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
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

::mlir::Attribute LtLibOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
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

llvm::hash_code LtLibOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.sym_name.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> LtLibOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "sym_name")
      return prop.sym_name;
  return std::nullopt;
}

void LtLibOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "sym_name") {
       prop.sym_name = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.sym_name)>>(value);
       return;
    }
}

void LtLibOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.sym_name) attrs.append("sym_name", prop.sym_name);
}

::llvm::LogicalResult LtLibOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getSymNameAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Calyx1(attr, "sym_name", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult LtLibOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.sym_name)))
    return ::mlir::failure();
  return ::mlir::success();
}

void LtLibOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.sym_name);
}

::llvm::StringRef LtLibOp::getSymName() {
  auto attr = getSymNameAttr();
  return attr.getValue();
}

void LtLibOp::setSymName(::llvm::StringRef attrValue) {
  getProperties().sym_name = ::mlir::Builder((*this)->getContext()).getStringAttr(attrValue);
}

void LtLibOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, StringRef sym_name, ::mlir::TypeRange resultTypes) {
      odsState.addAttribute(mlir::SymbolTable::getSymbolAttrName(), odsBuilder.getStringAttr(sym_name));
      odsState.addTypes(resultTypes);
    
}

LtLibOp LtLibOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, StringRef sym_name, ::mlir::TypeRange resultTypes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(resultTypes)>(resultTypes));
  auto __res__ = ::llvm::dyn_cast<LtLibOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

LtLibOp LtLibOp::create(::mlir::ImplicitLocOpBuilder &builder, StringRef sym_name, ::mlir::TypeRange resultTypes) {
  return create(builder, builder.getLoc(), std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(resultTypes)>(resultTypes));
}

::llvm::LogicalResult LtLibOp::verifyInvariantsImpl() {
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;
  if (!tblgen_sym_name) return emitOpError("requires attribute 'sym_name'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Calyx1(*this, tblgen_sym_name, "sym_name")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx5(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSResults(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx5(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup2 = getODSResults(2);

    for (auto v : valueGroup2) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx1(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  if (!((std::equal_to<>()( (*this->getODSResults(0).begin()).getType() , (*this->getODSResults(1).begin()).getType()))))
    return emitOpError("failed to verify that lhs and rhs types should be equivalent");
  return ::mlir::success();
}

::llvm::LogicalResult LtLibOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult LtLibOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::StringAttr sym_nameAttr;
  ::llvm::SmallVector<::mlir::Type, 1> allResultTypes;

  if (parser.parseSymbolName(sym_nameAttr))
    return ::mlir::failure();
  if (sym_nameAttr) result.getOrAddProperties<LtLibOp::Properties>().sym_name = sym_nameAttr;
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

  if (parser.parseTypeList(allResultTypes))
    return ::mlir::failure();
  result.addTypes(allResultTypes);
  return ::mlir::success();
}

void LtLibOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter.printSymbolName(getSymNameAttr().getValue());
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("sym_name");
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
  _odsPrinter << getOperation()->getResultTypes();
}


} // namespace circt::calyx
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::calyx::LtLibOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::calyx::detail::LtLibOpGenericAdaptorBase::Properties)

namespace circt::calyx {


//===----------------------------------------------------------------------===//
// ::circt::calyx::MemoryOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

MemoryOpGenericAdaptorBase::MemoryOpGenericAdaptorBase(MemoryOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::llvm::StringRef MemoryOpGenericAdaptorBase::getSymName() {
  auto attr = getSymNameAttr();
  return attr.getValue();
}

uint64_t MemoryOpGenericAdaptorBase::getWidth() {
  auto attr = getWidthAttr();
  return attr.getValue().getZExtValue();
}

::mlir::ArrayAttr MemoryOpGenericAdaptorBase::getSizes() {
  auto attr = getSizesAttr();
  return attr;
}

::mlir::ArrayAttr MemoryOpGenericAdaptorBase::getAddrSizes() {
  auto attr = getAddrSizesAttr();
  return attr;
}


} // namespace detail
MemoryOpAdaptor::MemoryOpAdaptor(MemoryOp op) : MemoryOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult MemoryOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_addrSizes = getProperties().addrSizes; (void)tblgen_addrSizes;
  if (!tblgen_addrSizes) return emitError(loc, "'calyx.memory' op requires attribute 'addrSizes'");
  auto tblgen_sizes = getProperties().sizes; (void)tblgen_sizes;
  if (!tblgen_sizes) return emitError(loc, "'calyx.memory' op requires attribute 'sizes'");
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;
  if (!tblgen_sym_name) return emitError(loc, "'calyx.memory' op requires attribute 'sym_name'");
  auto tblgen_width = getProperties().width; (void)tblgen_width;
  if (!tblgen_width) return emitError(loc, "'calyx.memory' op requires attribute 'width'");

  if (tblgen_sym_name && !((::llvm::isa<::mlir::StringAttr>(tblgen_sym_name))))
    return emitError(loc, "'calyx.memory' op attribute 'sym_name' failed to satisfy constraint: string attribute");

  if (tblgen_width && !(((::llvm::isa<::mlir::IntegerAttr>(tblgen_width))) && ((::llvm::cast<::mlir::IntegerAttr>(tblgen_width).getType().isSignlessInteger(64)))))
    return emitError(loc, "'calyx.memory' op attribute 'width' failed to satisfy constraint: 64-bit signless integer attribute");

  if (tblgen_sizes && !((::llvm::isa<::mlir::ArrayAttr>(tblgen_sizes))))
    return emitError(loc, "'calyx.memory' op attribute 'sizes' failed to satisfy constraint: array attribute");

  if (tblgen_addrSizes && !((::llvm::isa<::mlir::ArrayAttr>(tblgen_addrSizes))))
    return emitError(loc, "'calyx.memory' op attribute 'addrSizes' failed to satisfy constraint: array attribute");
  return ::mlir::success();
}

std::pair<unsigned, unsigned> MemoryOp::getODSResultIndexAndLength(unsigned index) {
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

::llvm::LogicalResult MemoryOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.addrSizes;
       auto attr = dict.get("addrSizes");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `addrSizes` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.sizes;
       auto attr = dict.get("sizes");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `sizes` in property conversion: " << attr;
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
    auto &propStorage = prop.width;
       auto attr = dict.get("width");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `width` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  return ::mlir::success();
}

::mlir::Attribute MemoryOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.addrSizes;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("addrSizes",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.sizes;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("sizes",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.sym_name;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("sym_name",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.width;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("width",
                                       propStorage));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code MemoryOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.addrSizes.getAsOpaquePointer()), 
    llvm::hash_value(prop.sizes.getAsOpaquePointer()), 
    llvm::hash_value(prop.sym_name.getAsOpaquePointer()), 
    llvm::hash_value(prop.width.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> MemoryOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "addrSizes")
      return prop.addrSizes;

    if (name == "sizes")
      return prop.sizes;

    if (name == "sym_name")
      return prop.sym_name;

    if (name == "width")
      return prop.width;
  return std::nullopt;
}

void MemoryOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "addrSizes") {
       prop.addrSizes = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.addrSizes)>>(value);
       return;
    }

    if (name == "sizes") {
       prop.sizes = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.sizes)>>(value);
       return;
    }

    if (name == "sym_name") {
       prop.sym_name = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.sym_name)>>(value);
       return;
    }

    if (name == "width") {
       prop.width = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.width)>>(value);
       return;
    }
}

void MemoryOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.addrSizes) attrs.append("addrSizes", prop.addrSizes);

    if (prop.sizes) attrs.append("sizes", prop.sizes);

    if (prop.sym_name) attrs.append("sym_name", prop.sym_name);

    if (prop.width) attrs.append("width", prop.width);
}

::llvm::LogicalResult MemoryOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getAddrSizesAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Calyx4(attr, "addrSizes", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getSizesAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Calyx4(attr, "sizes", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getSymNameAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Calyx1(attr, "sym_name", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getWidthAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Calyx9(attr, "width", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult MemoryOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.addrSizes)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readAttribute(prop.sizes)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readAttribute(prop.sym_name)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readAttribute(prop.width)))
    return ::mlir::failure();
  return ::mlir::success();
}

void MemoryOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.addrSizes);
  writer.writeAttribute(prop.sizes);
  writer.writeAttribute(prop.sym_name);
  writer.writeAttribute(prop.width);
}

::llvm::StringRef MemoryOp::getSymName() {
  auto attr = getSymNameAttr();
  return attr.getValue();
}

uint64_t MemoryOp::getWidth() {
  auto attr = getWidthAttr();
  return attr.getValue().getZExtValue();
}

::mlir::ArrayAttr MemoryOp::getSizes() {
  auto attr = getSizesAttr();
  return attr;
}

::mlir::ArrayAttr MemoryOp::getAddrSizes() {
  auto attr = getAddrSizesAttr();
  return attr;
}

void MemoryOp::setSymName(::llvm::StringRef attrValue) {
  getProperties().sym_name = ::mlir::Builder((*this)->getContext()).getStringAttr(attrValue);
}

void MemoryOp::setWidth(uint64_t attrValue) {
  getProperties().width = ::mlir::Builder((*this)->getContext()).getIntegerAttr(::mlir::Builder((*this)->getContext()).getIntegerType(64), attrValue);
}

MemoryOp MemoryOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, StringRef sym_name, int64_t width, ArrayRef<int64_t> sizes, ArrayRef<int64_t> addrSizes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(width)>(width), std::forward<decltype(sizes)>(sizes), std::forward<decltype(addrSizes)>(addrSizes));
  auto __res__ = ::llvm::dyn_cast<MemoryOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

MemoryOp MemoryOp::create(::mlir::ImplicitLocOpBuilder &builder, StringRef sym_name, int64_t width, ArrayRef<int64_t> sizes, ArrayRef<int64_t> addrSizes) {
  return create(builder, builder.getLoc(), std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(width)>(width), std::forward<decltype(sizes)>(sizes), std::forward<decltype(addrSizes)>(addrSizes));
}

::llvm::LogicalResult MemoryOp::verifyInvariantsImpl() {
  auto tblgen_addrSizes = getProperties().addrSizes; (void)tblgen_addrSizes;
  if (!tblgen_addrSizes) return emitOpError("requires attribute 'addrSizes'");
  auto tblgen_sizes = getProperties().sizes; (void)tblgen_sizes;
  if (!tblgen_sizes) return emitOpError("requires attribute 'sizes'");
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;
  if (!tblgen_sym_name) return emitOpError("requires attribute 'sym_name'");
  auto tblgen_width = getProperties().width; (void)tblgen_width;
  if (!tblgen_width) return emitOpError("requires attribute 'width'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Calyx1(*this, tblgen_sym_name, "sym_name")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Calyx9(*this, tblgen_width, "width")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Calyx4(*this, tblgen_sizes, "sizes")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Calyx4(*this, tblgen_addrSizes, "addrSizes")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx8(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult MemoryOp::verifyInvariants() {
  if(::mlir::succeeded(verifyInvariantsImpl()) && ::mlir::succeeded(verify()))
    return ::mlir::success();
  return ::mlir::failure();
}

::mlir::ParseResult MemoryOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::StringAttr sym_nameAttr;
  ::mlir::ArrayAttr sizesAttr;
  ::mlir::IntegerAttr widthAttr;
  ::mlir::ArrayAttr addrSizesAttr;
  ::llvm::SmallVector<::mlir::Type, 1> resultsTypes;

  if (parser.parseSymbolName(sym_nameAttr))
    return ::mlir::failure();
  if (sym_nameAttr) result.getOrAddProperties<MemoryOp::Properties>().sym_name = sym_nameAttr;
  if (parser.parseLess())
    return ::mlir::failure();

  if (parser.parseCustomAttributeWithFallback(sizesAttr, parser.getBuilder().getType<::mlir::NoneType>())) {
    return ::mlir::failure();
  }
  if (sizesAttr) result.getOrAddProperties<MemoryOp::Properties>().sizes = sizesAttr;
  if (parser.parseKeyword("x"))
    return ::mlir::failure();

  if (parser.parseCustomAttributeWithFallback(widthAttr, parser.getBuilder().getIntegerType(64))) {
    return ::mlir::failure();
  }
  if (widthAttr) result.getOrAddProperties<MemoryOp::Properties>().width = widthAttr;
  if (parser.parseGreater())
    return ::mlir::failure();

  if (parser.parseCustomAttributeWithFallback(addrSizesAttr, parser.getBuilder().getType<::mlir::NoneType>())) {
    return ::mlir::failure();
  }
  if (addrSizesAttr) result.getOrAddProperties<MemoryOp::Properties>().addrSizes = addrSizesAttr;
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

  if (parser.parseTypeList(resultsTypes))
    return ::mlir::failure();
  result.addTypes(resultsTypes);
  return ::mlir::success();
}

void MemoryOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter.printSymbolName(getSymNameAttr().getValue());
  _odsPrinter << ' ';
  _odsPrinter << "<";
  _odsPrinter.printAttributeWithoutType(getSizesAttr());
  _odsPrinter << ' ' << "x";
  _odsPrinter << ' ';
  _odsPrinter.printAttributeWithoutType(getWidthAttr());
  _odsPrinter << ">";
  _odsPrinter << ' ';
  _odsPrinter.printAttributeWithoutType(getAddrSizesAttr());
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("sym_name");
  elidedAttrs.push_back("sizes");
  elidedAttrs.push_back("width");
  elidedAttrs.push_back("addrSizes");
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
  _odsPrinter << getResults().getTypes();
}

bool MemoryOp::isCombinational() { return false; }

} // namespace circt::calyx
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::calyx::MemoryOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::calyx::detail::MemoryOpGenericAdaptorBase::Properties)

namespace circt::calyx {


//===----------------------------------------------------------------------===//
// ::circt::calyx::MulFOpIEEE754 definitions
//===----------------------------------------------------------------------===//

namespace detail {

MulFOpIEEE754GenericAdaptorBase::MulFOpIEEE754GenericAdaptorBase(MulFOpIEEE754 op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::llvm::StringRef MulFOpIEEE754GenericAdaptorBase::getSymName() {
  auto attr = getSymNameAttr();
  return attr.getValue();
}


} // namespace detail
MulFOpIEEE754Adaptor::MulFOpIEEE754Adaptor(MulFOpIEEE754 op) : MulFOpIEEE754GenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult MulFOpIEEE754Adaptor::verify(::mlir::Location loc) {
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;
  if (!tblgen_sym_name) return emitError(loc, "'calyx.ieee754.mul' op requires attribute 'sym_name'");

  if (tblgen_sym_name && !((::llvm::isa<::mlir::StringAttr>(tblgen_sym_name))))
    return emitError(loc, "'calyx.ieee754.mul' op attribute 'sym_name' failed to satisfy constraint: string attribute");
  return ::mlir::success();
}

::llvm::LogicalResult MulFOpIEEE754::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
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

::mlir::Attribute MulFOpIEEE754::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
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

llvm::hash_code MulFOpIEEE754::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.sym_name.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> MulFOpIEEE754::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "sym_name")
      return prop.sym_name;
  return std::nullopt;
}

void MulFOpIEEE754::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "sym_name") {
       prop.sym_name = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.sym_name)>>(value);
       return;
    }
}

void MulFOpIEEE754::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.sym_name) attrs.append("sym_name", prop.sym_name);
}

::llvm::LogicalResult MulFOpIEEE754::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getSymNameAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Calyx1(attr, "sym_name", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult MulFOpIEEE754::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.sym_name)))
    return ::mlir::failure();
  return ::mlir::success();
}

void MulFOpIEEE754::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.sym_name);
}

::llvm::StringRef MulFOpIEEE754::getSymName() {
  auto attr = getSymNameAttr();
  return attr.getValue();
}

void MulFOpIEEE754::setSymName(::llvm::StringRef attrValue) {
  getProperties().sym_name = ::mlir::Builder((*this)->getContext()).getStringAttr(attrValue);
}

void MulFOpIEEE754::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, StringRef sym_name, ::mlir::TypeRange resultTypes) {
      odsState.addAttribute(mlir::SymbolTable::getSymbolAttrName(), odsBuilder.getStringAttr(sym_name));
      odsState.addTypes(resultTypes);
    
}

MulFOpIEEE754 MulFOpIEEE754::create(::mlir::OpBuilder &builder, ::mlir::Location location, StringRef sym_name, ::mlir::TypeRange resultTypes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(resultTypes)>(resultTypes));
  auto __res__ = ::llvm::dyn_cast<MulFOpIEEE754>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

MulFOpIEEE754 MulFOpIEEE754::create(::mlir::ImplicitLocOpBuilder &builder, StringRef sym_name, ::mlir::TypeRange resultTypes) {
  return create(builder, builder.getLoc(), std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(resultTypes)>(resultTypes));
}

::llvm::LogicalResult MulFOpIEEE754::verifyInvariantsImpl() {
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;
  if (!tblgen_sym_name) return emitOpError("requires attribute 'sym_name'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Calyx1(*this, tblgen_sym_name, "sym_name")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx1(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSResults(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx1(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup2 = getODSResults(2);

    for (auto v : valueGroup2) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx1(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup3 = getODSResults(3);

    for (auto v : valueGroup3) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx1(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup4 = getODSResults(4);

    for (auto v : valueGroup4) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx2(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup5 = getODSResults(5);

    for (auto v : valueGroup5) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx2(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup6 = getODSResults(6);

    for (auto v : valueGroup6) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx3(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup7 = getODSResults(7);

    for (auto v : valueGroup7) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx2(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup8 = getODSResults(8);

    for (auto v : valueGroup8) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx4(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup9 = getODSResults(9);

    for (auto v : valueGroup9) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx1(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  if (!((std::equal_to<>()( (*this->getODSResults(4).begin()).getType() , (*this->getODSResults(7).begin()).getType()))))
    return emitOpError("failed to verify that lhs and rhs types should be equivalent");
  if (!((std::equal_to<>()( (*this->getODSResults(4).begin()).getType() , (*this->getODSResults(5).begin()).getType()))))
    return emitOpError("failed to verify that lhs and rhs types should be equivalent");
  return ::mlir::success();
}

::llvm::LogicalResult MulFOpIEEE754::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult MulFOpIEEE754::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::StringAttr sym_nameAttr;
  ::llvm::SmallVector<::mlir::Type, 1> allResultTypes;

  if (parser.parseSymbolName(sym_nameAttr))
    return ::mlir::failure();
  if (sym_nameAttr) result.getOrAddProperties<MulFOpIEEE754::Properties>().sym_name = sym_nameAttr;
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

  if (parser.parseTypeList(allResultTypes))
    return ::mlir::failure();
  result.addTypes(allResultTypes);
  return ::mlir::success();
}

void MulFOpIEEE754::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter.printSymbolName(getSymNameAttr().getValue());
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("sym_name");
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
  _odsPrinter << getOperation()->getResultTypes();
}

SmallVector<StringRef> MulFOpIEEE754::portNames() {
  return {clkPort, resetPort, goPort, "control", "left", "right",
          "roundingMode", "out", "exceptionalFlags", donePort
  };
}
SmallVector<Direction> MulFOpIEEE754::portDirections() {
  return {Input, Input, Input, Input, Input, Input, Input, Output, Output, Output};
}
void MulFOpIEEE754::getAsmResultNames(OpAsmSetValueNameFn setNameFn) {
  getCellAsmResultNames(setNameFn, *this, this->portNames());
}
bool MulFOpIEEE754::isCombinational() { return false; }
SmallVector<DictionaryAttr> MulFOpIEEE754::portAttributes() {
  IntegerAttr isSet = IntegerAttr::get(IntegerType::get(getContext(), 1), 1);
  NamedAttrList go, clk, reset, done;
  go.append(goPort, isSet);
  clk.append(clkPort, isSet);
  reset.append(resetPort, isSet);
  done.append(donePort, isSet);
  return {clk.getDictionary(getContext()), reset.getDictionary(getContext()),
          go.getDictionary(getContext()), DictionaryAttr::get(getContext()),
          DictionaryAttr::get(getContext()), DictionaryAttr::get(getContext()),
          DictionaryAttr::get(getContext()), DictionaryAttr::get(getContext()),
          done.getDictionary(getContext()), DictionaryAttr::get(getContext())
  };
}

} // namespace circt::calyx
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::calyx::MulFOpIEEE754)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::calyx::detail::MulFOpIEEE754GenericAdaptorBase::Properties)

namespace circt::calyx {


//===----------------------------------------------------------------------===//
// ::circt::calyx::MultPipeLibOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

MultPipeLibOpGenericAdaptorBase::MultPipeLibOpGenericAdaptorBase(MultPipeLibOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::llvm::StringRef MultPipeLibOpGenericAdaptorBase::getSymName() {
  auto attr = getSymNameAttr();
  return attr.getValue();
}


} // namespace detail
MultPipeLibOpAdaptor::MultPipeLibOpAdaptor(MultPipeLibOp op) : MultPipeLibOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult MultPipeLibOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;
  if (!tblgen_sym_name) return emitError(loc, "'calyx.std_mult_pipe' op requires attribute 'sym_name'");

  if (tblgen_sym_name && !((::llvm::isa<::mlir::StringAttr>(tblgen_sym_name))))
    return emitError(loc, "'calyx.std_mult_pipe' op attribute 'sym_name' failed to satisfy constraint: string attribute");
  return ::mlir::success();
}

::llvm::LogicalResult MultPipeLibOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
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

::mlir::Attribute MultPipeLibOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
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

llvm::hash_code MultPipeLibOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.sym_name.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> MultPipeLibOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "sym_name")
      return prop.sym_name;
  return std::nullopt;
}

void MultPipeLibOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "sym_name") {
       prop.sym_name = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.sym_name)>>(value);
       return;
    }
}

void MultPipeLibOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.sym_name) attrs.append("sym_name", prop.sym_name);
}

::llvm::LogicalResult MultPipeLibOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getSymNameAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Calyx1(attr, "sym_name", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult MultPipeLibOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.sym_name)))
    return ::mlir::failure();
  return ::mlir::success();
}

void MultPipeLibOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.sym_name);
}

::llvm::StringRef MultPipeLibOp::getSymName() {
  auto attr = getSymNameAttr();
  return attr.getValue();
}

void MultPipeLibOp::setSymName(::llvm::StringRef attrValue) {
  getProperties().sym_name = ::mlir::Builder((*this)->getContext()).getStringAttr(attrValue);
}

void MultPipeLibOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, StringRef sym_name, ::mlir::TypeRange resultTypes) {
      odsState.addAttribute(mlir::SymbolTable::getSymbolAttrName(), odsBuilder.getStringAttr(sym_name));
      odsState.addTypes(resultTypes);
    
}

MultPipeLibOp MultPipeLibOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, StringRef sym_name, ::mlir::TypeRange resultTypes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(resultTypes)>(resultTypes));
  auto __res__ = ::llvm::dyn_cast<MultPipeLibOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

MultPipeLibOp MultPipeLibOp::create(::mlir::ImplicitLocOpBuilder &builder, StringRef sym_name, ::mlir::TypeRange resultTypes) {
  return create(builder, builder.getLoc(), std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(resultTypes)>(resultTypes));
}

::llvm::LogicalResult MultPipeLibOp::verifyInvariantsImpl() {
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;
  if (!tblgen_sym_name) return emitOpError("requires attribute 'sym_name'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Calyx1(*this, tblgen_sym_name, "sym_name")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx1(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSResults(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx1(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup2 = getODSResults(2);

    for (auto v : valueGroup2) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx1(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup3 = getODSResults(3);

    for (auto v : valueGroup3) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx5(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup4 = getODSResults(4);

    for (auto v : valueGroup4) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx5(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup5 = getODSResults(5);

    for (auto v : valueGroup5) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx5(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup6 = getODSResults(6);

    for (auto v : valueGroup6) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx1(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  if (!((std::equal_to<>()( (*this->getODSResults(3).begin()).getType() , (*this->getODSResults(5).begin()).getType()))))
    return emitOpError("failed to verify that lhs and rhs types should be equivalent");
  if (!((std::equal_to<>()( (*this->getODSResults(3).begin()).getType() , (*this->getODSResults(4).begin()).getType()))))
    return emitOpError("failed to verify that lhs and rhs types should be equivalent");
  return ::mlir::success();
}

::llvm::LogicalResult MultPipeLibOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult MultPipeLibOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::StringAttr sym_nameAttr;
  ::llvm::SmallVector<::mlir::Type, 1> allResultTypes;

  if (parser.parseSymbolName(sym_nameAttr))
    return ::mlir::failure();
  if (sym_nameAttr) result.getOrAddProperties<MultPipeLibOp::Properties>().sym_name = sym_nameAttr;
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

  if (parser.parseTypeList(allResultTypes))
    return ::mlir::failure();
  result.addTypes(allResultTypes);
  return ::mlir::success();
}

void MultPipeLibOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter.printSymbolName(getSymNameAttr().getValue());
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("sym_name");
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
  _odsPrinter << getOperation()->getResultTypes();
}


} // namespace circt::calyx
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::calyx::MultPipeLibOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::calyx::detail::MultPipeLibOpGenericAdaptorBase::Properties)

namespace circt::calyx {


//===----------------------------------------------------------------------===//
// ::circt::calyx::MuxLibOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

MuxLibOpGenericAdaptorBase::MuxLibOpGenericAdaptorBase(MuxLibOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::llvm::StringRef MuxLibOpGenericAdaptorBase::getSymName() {
  auto attr = getSymNameAttr();
  return attr.getValue();
}


} // namespace detail
MuxLibOpAdaptor::MuxLibOpAdaptor(MuxLibOp op) : MuxLibOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult MuxLibOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;
  if (!tblgen_sym_name) return emitError(loc, "'calyx.std_mux' op requires attribute 'sym_name'");

  if (tblgen_sym_name && !((::llvm::isa<::mlir::StringAttr>(tblgen_sym_name))))
    return emitError(loc, "'calyx.std_mux' op attribute 'sym_name' failed to satisfy constraint: string attribute");
  return ::mlir::success();
}

::llvm::LogicalResult MuxLibOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
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

::mlir::Attribute MuxLibOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
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

llvm::hash_code MuxLibOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.sym_name.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> MuxLibOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "sym_name")
      return prop.sym_name;
  return std::nullopt;
}

void MuxLibOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "sym_name") {
       prop.sym_name = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.sym_name)>>(value);
       return;
    }
}

void MuxLibOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.sym_name) attrs.append("sym_name", prop.sym_name);
}

::llvm::LogicalResult MuxLibOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getSymNameAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Calyx1(attr, "sym_name", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult MuxLibOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.sym_name)))
    return ::mlir::failure();
  return ::mlir::success();
}

void MuxLibOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.sym_name);
}

::llvm::StringRef MuxLibOp::getSymName() {
  auto attr = getSymNameAttr();
  return attr.getValue();
}

void MuxLibOp::setSymName(::llvm::StringRef attrValue) {
  getProperties().sym_name = ::mlir::Builder((*this)->getContext()).getStringAttr(attrValue);
}

void MuxLibOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, StringRef sym_name, ::mlir::TypeRange resultTypes) {
      odsState.addAttribute(mlir::SymbolTable::getSymbolAttrName(), odsBuilder.getStringAttr(sym_name));
      odsState.addTypes(resultTypes);
    
}

MuxLibOp MuxLibOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, StringRef sym_name, ::mlir::TypeRange resultTypes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(resultTypes)>(resultTypes));
  auto __res__ = ::llvm::dyn_cast<MuxLibOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

MuxLibOp MuxLibOp::create(::mlir::ImplicitLocOpBuilder &builder, StringRef sym_name, ::mlir::TypeRange resultTypes) {
  return create(builder, builder.getLoc(), std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(resultTypes)>(resultTypes));
}

::llvm::LogicalResult MuxLibOp::verifyInvariantsImpl() {
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;
  if (!tblgen_sym_name) return emitOpError("requires attribute 'sym_name'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Calyx1(*this, tblgen_sym_name, "sym_name")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx1(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSResults(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx5(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup2 = getODSResults(2);

    for (auto v : valueGroup2) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx5(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup3 = getODSResults(3);

    for (auto v : valueGroup3) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx5(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  if (!((std::equal_to<>()( (*this->getODSResults(1).begin()).getType() , (*this->getODSResults(2).begin()).getType()))))
    return emitOpError("failed to verify that lhs and rhs types should be equivalent");
  if (!((std::equal_to<>()( (*this->getODSResults(1).begin()).getType() , (*this->getODSResults(3).begin()).getType()))))
    return emitOpError("failed to verify that lhs and rhs types should be equivalent");
  return ::mlir::success();
}

::llvm::LogicalResult MuxLibOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult MuxLibOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::StringAttr sym_nameAttr;
  ::llvm::SmallVector<::mlir::Type, 1> allResultTypes;

  if (parser.parseSymbolName(sym_nameAttr))
    return ::mlir::failure();
  if (sym_nameAttr) result.getOrAddProperties<MuxLibOp::Properties>().sym_name = sym_nameAttr;
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

  if (parser.parseTypeList(allResultTypes))
    return ::mlir::failure();
  result.addTypes(allResultTypes);
  return ::mlir::success();
}

void MuxLibOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter.printSymbolName(getSymNameAttr().getValue());
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("sym_name");
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
  _odsPrinter << getOperation()->getResultTypes();
}

SmallVector<StringRef> MuxLibOp::portNames() {
  return {"cond", "tru", "fal", "out"};
}
SmallVector<Direction> MuxLibOp::portDirections() {
  return {Input, Input, Input, Output};
}
void MuxLibOp::getAsmResultNames(OpAsmSetValueNameFn setNameFn) {
  getCellAsmResultNames(setNameFn, *this, this->portNames());
}
bool MuxLibOp::isCombinational() { return true; }
SmallVector<DictionaryAttr> MuxLibOp::portAttributes() {
  return {DictionaryAttr::get(getContext()), DictionaryAttr::get(getContext()),
          DictionaryAttr::get(getContext()), DictionaryAttr::get(getContext())};
}

} // namespace circt::calyx
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::calyx::MuxLibOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::calyx::detail::MuxLibOpGenericAdaptorBase::Properties)

namespace circt::calyx {


//===----------------------------------------------------------------------===//
// ::circt::calyx::NeqLibOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

NeqLibOpGenericAdaptorBase::NeqLibOpGenericAdaptorBase(NeqLibOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::llvm::StringRef NeqLibOpGenericAdaptorBase::getSymName() {
  auto attr = getSymNameAttr();
  return attr.getValue();
}


} // namespace detail
NeqLibOpAdaptor::NeqLibOpAdaptor(NeqLibOp op) : NeqLibOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult NeqLibOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;
  if (!tblgen_sym_name) return emitError(loc, "'calyx.std_neq' op requires attribute 'sym_name'");

  if (tblgen_sym_name && !((::llvm::isa<::mlir::StringAttr>(tblgen_sym_name))))
    return emitError(loc, "'calyx.std_neq' op attribute 'sym_name' failed to satisfy constraint: string attribute");
  return ::mlir::success();
}

::llvm::LogicalResult NeqLibOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
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

::mlir::Attribute NeqLibOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
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

llvm::hash_code NeqLibOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.sym_name.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> NeqLibOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "sym_name")
      return prop.sym_name;
  return std::nullopt;
}

void NeqLibOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "sym_name") {
       prop.sym_name = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.sym_name)>>(value);
       return;
    }
}

void NeqLibOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.sym_name) attrs.append("sym_name", prop.sym_name);
}

::llvm::LogicalResult NeqLibOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getSymNameAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Calyx1(attr, "sym_name", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult NeqLibOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.sym_name)))
    return ::mlir::failure();
  return ::mlir::success();
}

void NeqLibOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.sym_name);
}

::llvm::StringRef NeqLibOp::getSymName() {
  auto attr = getSymNameAttr();
  return attr.getValue();
}

void NeqLibOp::setSymName(::llvm::StringRef attrValue) {
  getProperties().sym_name = ::mlir::Builder((*this)->getContext()).getStringAttr(attrValue);
}

void NeqLibOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, StringRef sym_name, ::mlir::TypeRange resultTypes) {
      odsState.addAttribute(mlir::SymbolTable::getSymbolAttrName(), odsBuilder.getStringAttr(sym_name));
      odsState.addTypes(resultTypes);
    
}

NeqLibOp NeqLibOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, StringRef sym_name, ::mlir::TypeRange resultTypes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(resultTypes)>(resultTypes));
  auto __res__ = ::llvm::dyn_cast<NeqLibOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

NeqLibOp NeqLibOp::create(::mlir::ImplicitLocOpBuilder &builder, StringRef sym_name, ::mlir::TypeRange resultTypes) {
  return create(builder, builder.getLoc(), std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(resultTypes)>(resultTypes));
}

::llvm::LogicalResult NeqLibOp::verifyInvariantsImpl() {
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;
  if (!tblgen_sym_name) return emitOpError("requires attribute 'sym_name'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Calyx1(*this, tblgen_sym_name, "sym_name")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx5(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSResults(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx5(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup2 = getODSResults(2);

    for (auto v : valueGroup2) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx1(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  if (!((std::equal_to<>()( (*this->getODSResults(0).begin()).getType() , (*this->getODSResults(1).begin()).getType()))))
    return emitOpError("failed to verify that lhs and rhs types should be equivalent");
  return ::mlir::success();
}

::llvm::LogicalResult NeqLibOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult NeqLibOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::StringAttr sym_nameAttr;
  ::llvm::SmallVector<::mlir::Type, 1> allResultTypes;

  if (parser.parseSymbolName(sym_nameAttr))
    return ::mlir::failure();
  if (sym_nameAttr) result.getOrAddProperties<NeqLibOp::Properties>().sym_name = sym_nameAttr;
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

  if (parser.parseTypeList(allResultTypes))
    return ::mlir::failure();
  result.addTypes(allResultTypes);
  return ::mlir::success();
}

void NeqLibOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter.printSymbolName(getSymNameAttr().getValue());
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("sym_name");
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
  _odsPrinter << getOperation()->getResultTypes();
}


} // namespace circt::calyx
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::calyx::NeqLibOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::calyx::detail::NeqLibOpGenericAdaptorBase::Properties)

namespace circt::calyx {


//===----------------------------------------------------------------------===//
// ::circt::calyx::NotLibOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

NotLibOpGenericAdaptorBase::NotLibOpGenericAdaptorBase(NotLibOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::llvm::StringRef NotLibOpGenericAdaptorBase::getSymName() {
  auto attr = getSymNameAttr();
  return attr.getValue();
}


} // namespace detail
NotLibOpAdaptor::NotLibOpAdaptor(NotLibOp op) : NotLibOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult NotLibOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;
  if (!tblgen_sym_name) return emitError(loc, "'calyx.std_not' op requires attribute 'sym_name'");

  if (tblgen_sym_name && !((::llvm::isa<::mlir::StringAttr>(tblgen_sym_name))))
    return emitError(loc, "'calyx.std_not' op attribute 'sym_name' failed to satisfy constraint: string attribute");
  return ::mlir::success();
}

::llvm::LogicalResult NotLibOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
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

::mlir::Attribute NotLibOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
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

llvm::hash_code NotLibOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.sym_name.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> NotLibOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "sym_name")
      return prop.sym_name;
  return std::nullopt;
}

void NotLibOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "sym_name") {
       prop.sym_name = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.sym_name)>>(value);
       return;
    }
}

void NotLibOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.sym_name) attrs.append("sym_name", prop.sym_name);
}

::llvm::LogicalResult NotLibOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getSymNameAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Calyx1(attr, "sym_name", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult NotLibOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.sym_name)))
    return ::mlir::failure();
  return ::mlir::success();
}

void NotLibOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.sym_name);
}

::llvm::StringRef NotLibOp::getSymName() {
  auto attr = getSymNameAttr();
  return attr.getValue();
}

void NotLibOp::setSymName(::llvm::StringRef attrValue) {
  getProperties().sym_name = ::mlir::Builder((*this)->getContext()).getStringAttr(attrValue);
}

void NotLibOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, StringRef sym_name, ::mlir::TypeRange resultTypes) {
      odsState.addAttribute(mlir::SymbolTable::getSymbolAttrName(), odsBuilder.getStringAttr(sym_name));
      odsState.addTypes(resultTypes);
    
}

NotLibOp NotLibOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, StringRef sym_name, ::mlir::TypeRange resultTypes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(resultTypes)>(resultTypes));
  auto __res__ = ::llvm::dyn_cast<NotLibOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

NotLibOp NotLibOp::create(::mlir::ImplicitLocOpBuilder &builder, StringRef sym_name, ::mlir::TypeRange resultTypes) {
  return create(builder, builder.getLoc(), std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(resultTypes)>(resultTypes));
}

::llvm::LogicalResult NotLibOp::verifyInvariantsImpl() {
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;
  if (!tblgen_sym_name) return emitOpError("requires attribute 'sym_name'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Calyx1(*this, tblgen_sym_name, "sym_name")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx6(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSResults(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx6(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult NotLibOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult NotLibOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::StringAttr sym_nameAttr;
  ::llvm::SmallVector<::mlir::Type, 1> allResultTypes;

  if (parser.parseSymbolName(sym_nameAttr))
    return ::mlir::failure();
  if (sym_nameAttr) result.getOrAddProperties<NotLibOp::Properties>().sym_name = sym_nameAttr;
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

  if (parser.parseTypeList(allResultTypes))
    return ::mlir::failure();
  result.addTypes(allResultTypes);
  return ::mlir::success();
}

void NotLibOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter.printSymbolName(getSymNameAttr().getValue());
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("sym_name");
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
  _odsPrinter << getOperation()->getResultTypes();
}


} // namespace circt::calyx
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::calyx::NotLibOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::calyx::detail::NotLibOpGenericAdaptorBase::Properties)

namespace circt::calyx {


//===----------------------------------------------------------------------===//
// ::circt::calyx::OrLibOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

OrLibOpGenericAdaptorBase::OrLibOpGenericAdaptorBase(OrLibOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::llvm::StringRef OrLibOpGenericAdaptorBase::getSymName() {
  auto attr = getSymNameAttr();
  return attr.getValue();
}


} // namespace detail
OrLibOpAdaptor::OrLibOpAdaptor(OrLibOp op) : OrLibOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult OrLibOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;
  if (!tblgen_sym_name) return emitError(loc, "'calyx.std_or' op requires attribute 'sym_name'");

  if (tblgen_sym_name && !((::llvm::isa<::mlir::StringAttr>(tblgen_sym_name))))
    return emitError(loc, "'calyx.std_or' op attribute 'sym_name' failed to satisfy constraint: string attribute");
  return ::mlir::success();
}

::llvm::LogicalResult OrLibOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
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

::mlir::Attribute OrLibOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
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

llvm::hash_code OrLibOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.sym_name.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> OrLibOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "sym_name")
      return prop.sym_name;
  return std::nullopt;
}

void OrLibOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "sym_name") {
       prop.sym_name = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.sym_name)>>(value);
       return;
    }
}

void OrLibOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.sym_name) attrs.append("sym_name", prop.sym_name);
}

::llvm::LogicalResult OrLibOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getSymNameAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Calyx1(attr, "sym_name", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult OrLibOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.sym_name)))
    return ::mlir::failure();
  return ::mlir::success();
}

void OrLibOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.sym_name);
}

::llvm::StringRef OrLibOp::getSymName() {
  auto attr = getSymNameAttr();
  return attr.getValue();
}

void OrLibOp::setSymName(::llvm::StringRef attrValue) {
  getProperties().sym_name = ::mlir::Builder((*this)->getContext()).getStringAttr(attrValue);
}

void OrLibOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, StringRef sym_name, ::mlir::TypeRange resultTypes) {
      odsState.addAttribute(mlir::SymbolTable::getSymbolAttrName(), odsBuilder.getStringAttr(sym_name));
      odsState.addTypes(resultTypes);
    
}

OrLibOp OrLibOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, StringRef sym_name, ::mlir::TypeRange resultTypes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(resultTypes)>(resultTypes));
  auto __res__ = ::llvm::dyn_cast<OrLibOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

OrLibOp OrLibOp::create(::mlir::ImplicitLocOpBuilder &builder, StringRef sym_name, ::mlir::TypeRange resultTypes) {
  return create(builder, builder.getLoc(), std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(resultTypes)>(resultTypes));
}

::llvm::LogicalResult OrLibOp::verifyInvariantsImpl() {
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;
  if (!tblgen_sym_name) return emitOpError("requires attribute 'sym_name'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Calyx1(*this, tblgen_sym_name, "sym_name")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx5(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSResults(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx5(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup2 = getODSResults(2);

    for (auto v : valueGroup2) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx5(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  if (!((std::equal_to<>()( (*this->getODSResults(0).begin()).getType() , (*this->getODSResults(2).begin()).getType()))))
    return emitOpError("failed to verify that lhs and rhs types should be equivalent");
  if (!((std::equal_to<>()( (*this->getODSResults(0).begin()).getType() , (*this->getODSResults(1).begin()).getType()))))
    return emitOpError("failed to verify that lhs and rhs types should be equivalent");
  return ::mlir::success();
}

::llvm::LogicalResult OrLibOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult OrLibOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::StringAttr sym_nameAttr;
  ::llvm::SmallVector<::mlir::Type, 1> allResultTypes;

  if (parser.parseSymbolName(sym_nameAttr))
    return ::mlir::failure();
  if (sym_nameAttr) result.getOrAddProperties<OrLibOp::Properties>().sym_name = sym_nameAttr;
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

  if (parser.parseTypeList(allResultTypes))
    return ::mlir::failure();
  result.addTypes(allResultTypes);
  return ::mlir::success();
}

void OrLibOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter.printSymbolName(getSymNameAttr().getValue());
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("sym_name");
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
  _odsPrinter << getOperation()->getResultTypes();
}


} // namespace circt::calyx
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::calyx::OrLibOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::calyx::detail::OrLibOpGenericAdaptorBase::Properties)

namespace circt::calyx {


//===----------------------------------------------------------------------===//
// ::circt::calyx::PadLibOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

PadLibOpGenericAdaptorBase::PadLibOpGenericAdaptorBase(PadLibOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::llvm::StringRef PadLibOpGenericAdaptorBase::getSymName() {
  auto attr = getSymNameAttr();
  return attr.getValue();
}


} // namespace detail
PadLibOpAdaptor::PadLibOpAdaptor(PadLibOp op) : PadLibOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult PadLibOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;
  if (!tblgen_sym_name) return emitError(loc, "'calyx.std_pad' op requires attribute 'sym_name'");

  if (tblgen_sym_name && !((::llvm::isa<::mlir::StringAttr>(tblgen_sym_name))))
    return emitError(loc, "'calyx.std_pad' op attribute 'sym_name' failed to satisfy constraint: string attribute");
  return ::mlir::success();
}

::llvm::LogicalResult PadLibOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
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

::mlir::Attribute PadLibOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
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

llvm::hash_code PadLibOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.sym_name.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> PadLibOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "sym_name")
      return prop.sym_name;
  return std::nullopt;
}

void PadLibOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "sym_name") {
       prop.sym_name = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.sym_name)>>(value);
       return;
    }
}

void PadLibOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.sym_name) attrs.append("sym_name", prop.sym_name);
}

::llvm::LogicalResult PadLibOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getSymNameAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Calyx1(attr, "sym_name", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult PadLibOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.sym_name)))
    return ::mlir::failure();
  return ::mlir::success();
}

void PadLibOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.sym_name);
}

::llvm::StringRef PadLibOp::getSymName() {
  auto attr = getSymNameAttr();
  return attr.getValue();
}

void PadLibOp::setSymName(::llvm::StringRef attrValue) {
  getProperties().sym_name = ::mlir::Builder((*this)->getContext()).getStringAttr(attrValue);
}

void PadLibOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, StringRef sym_name, ::mlir::TypeRange resultTypes) {
      odsState.addAttribute(mlir::SymbolTable::getSymbolAttrName(), odsBuilder.getStringAttr(sym_name));
      odsState.addTypes(resultTypes);
    
}

PadLibOp PadLibOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, StringRef sym_name, ::mlir::TypeRange resultTypes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(resultTypes)>(resultTypes));
  auto __res__ = ::llvm::dyn_cast<PadLibOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

PadLibOp PadLibOp::create(::mlir::ImplicitLocOpBuilder &builder, StringRef sym_name, ::mlir::TypeRange resultTypes) {
  return create(builder, builder.getLoc(), std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(resultTypes)>(resultTypes));
}

::llvm::LogicalResult PadLibOp::verifyInvariantsImpl() {
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;
  if (!tblgen_sym_name) return emitOpError("requires attribute 'sym_name'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Calyx1(*this, tblgen_sym_name, "sym_name")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx6(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSResults(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx6(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult PadLibOp::verifyInvariants() {
  if(::mlir::succeeded(verifyInvariantsImpl()) && ::mlir::succeeded(verify()))
    return ::mlir::success();
  return ::mlir::failure();
}

::mlir::ParseResult PadLibOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::StringAttr sym_nameAttr;
  ::llvm::SmallVector<::mlir::Type, 1> allResultTypes;

  if (parser.parseSymbolName(sym_nameAttr))
    return ::mlir::failure();
  if (sym_nameAttr) result.getOrAddProperties<PadLibOp::Properties>().sym_name = sym_nameAttr;
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

  if (parser.parseTypeList(allResultTypes))
    return ::mlir::failure();
  result.addTypes(allResultTypes);
  return ::mlir::success();
}

void PadLibOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter.printSymbolName(getSymNameAttr().getValue());
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("sym_name");
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
  _odsPrinter << getOperation()->getResultTypes();
}


} // namespace circt::calyx
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::calyx::PadLibOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::calyx::detail::PadLibOpGenericAdaptorBase::Properties)

namespace circt::calyx {


//===----------------------------------------------------------------------===//
// ::circt::calyx::ParOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

ParOpGenericAdaptorBase::ParOpGenericAdaptorBase(ParOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}


} // namespace detail
ParOpAdaptor::ParOpAdaptor(ParOp op) : ParOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult ParOpAdaptor::verify(::mlir::Location loc) {
  return ::mlir::success();
}

::llvm::LogicalResult ParOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }
      return ::mlir::success();
}

::mlir::Attribute ParOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code ParOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine();
}

std::optional<mlir::Attribute> ParOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
  return std::nullopt;
}

void ParOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
}

void ParOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
}

::llvm::LogicalResult ParOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    return ::mlir::success();
}

void ParOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState) {
      Region* region = odsState.addRegion();
      region->push_back(new Block());
    
}

ParOp ParOp::create(::mlir::OpBuilder &builder, ::mlir::Location location) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__);
  auto __res__ = ::llvm::dyn_cast<ParOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ParOp ParOp::create(::mlir::ImplicitLocOpBuilder &builder) {
  return create(builder, builder.getLoc());
}

::llvm::LogicalResult ParOp::verifyInvariantsImpl() {
  {
    unsigned index = 0; (void)index;

    for (auto &region : ::llvm::MutableArrayRef((*this)->getRegion(0)))
      if (::mlir::failed(__mlir_ods_local_region_constraint_Calyx1(*this, region, "body", index++)))
        return ::mlir::failure();
  }
  return ::mlir::success();
}

::llvm::LogicalResult ParOp::verifyInvariants() {
  if(::mlir::succeeded(verifyInvariantsImpl()) && ::mlir::succeeded(verify()))
    return ::mlir::success();
  return ::mlir::failure();
}

::mlir::ParseResult ParOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  std::unique_ptr<::mlir::Region> bodyRegion = std::make_unique<::mlir::Region>();

  if (parser.parseRegion(*bodyRegion))
    return ::mlir::failure();

  if (bodyRegion->empty()) bodyRegion->emplaceBlock();
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
  return ::mlir::success();
}

void ParOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter.printRegion(getBody());
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
}


} // namespace circt::calyx
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::calyx::ParOp)

namespace circt::calyx {


//===----------------------------------------------------------------------===//
// ::circt::calyx::PrimitiveOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

PrimitiveOpGenericAdaptorBase::PrimitiveOpGenericAdaptorBase(PrimitiveOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::llvm::StringRef PrimitiveOpGenericAdaptorBase::getSymName() {
  auto attr = getSymNameAttr();
  return attr.getValue();
}

::std::optional< ::mlir::ArrayAttr > PrimitiveOpGenericAdaptorBase::getParameters() {
  auto attr = getParametersAttr();
  return attr ? ::std::optional< ::mlir::ArrayAttr >(attr) : (::std::nullopt);
}

::llvm::StringRef PrimitiveOpGenericAdaptorBase::getPrimitiveName() {
  auto attr = getPrimitiveNameAttr();
  return attr.getValue();
}


} // namespace detail
PrimitiveOpAdaptor::PrimitiveOpAdaptor(PrimitiveOp op) : PrimitiveOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult PrimitiveOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_parameters = getProperties().parameters; (void)tblgen_parameters;
  auto tblgen_primitiveName = getProperties().primitiveName; (void)tblgen_primitiveName;
  if (!tblgen_primitiveName) return emitError(loc, "'calyx.primitive' op requires attribute 'primitiveName'");
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;
  if (!tblgen_sym_name) return emitError(loc, "'calyx.primitive' op requires attribute 'sym_name'");

  if (tblgen_sym_name && !((::llvm::isa<::mlir::StringAttr>(tblgen_sym_name))))
    return emitError(loc, "'calyx.primitive' op attribute 'sym_name' failed to satisfy constraint: string attribute");

  if (tblgen_parameters && !(((::llvm::isa<::mlir::ArrayAttr>(tblgen_parameters))) && (::llvm::all_of(::llvm::cast<::mlir::ArrayAttr>(tblgen_parameters), [&](::mlir::Attribute attr) { return attr && ((llvm::isa<hw::ParamDeclAttr>(attr))); }))))
    return emitError(loc, "'calyx.primitive' op attribute 'parameters' failed to satisfy constraint: parameter array");

  if (tblgen_primitiveName && !((::llvm::isa<::mlir::FlatSymbolRefAttr>(tblgen_primitiveName))))
    return emitError(loc, "'calyx.primitive' op attribute 'primitiveName' failed to satisfy constraint: flat symbol reference attribute");
  return ::mlir::success();
}

std::pair<unsigned, unsigned> PrimitiveOp::getODSResultIndexAndLength(unsigned index) {
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

::llvm::LogicalResult PrimitiveOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
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
    auto &propStorage = prop.primitiveName;
       auto attr = dict.get("primitiveName");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `primitiveName` in property conversion: " << attr;
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

::mlir::Attribute PrimitiveOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.parameters;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("parameters",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.primitiveName;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("primitiveName",
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

llvm::hash_code PrimitiveOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.parameters.getAsOpaquePointer()), 
    llvm::hash_value(prop.primitiveName.getAsOpaquePointer()), 
    llvm::hash_value(prop.sym_name.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> PrimitiveOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "parameters")
      return prop.parameters;

    if (name == "primitiveName")
      return prop.primitiveName;

    if (name == "sym_name")
      return prop.sym_name;
  return std::nullopt;
}

void PrimitiveOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "parameters") {
       prop.parameters = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.parameters)>>(value);
       return;
    }

    if (name == "primitiveName") {
       prop.primitiveName = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.primitiveName)>>(value);
       return;
    }

    if (name == "sym_name") {
       prop.sym_name = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.sym_name)>>(value);
       return;
    }
}

void PrimitiveOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.parameters) attrs.append("parameters", prop.parameters);

    if (prop.primitiveName) attrs.append("primitiveName", prop.primitiveName);

    if (prop.sym_name) attrs.append("sym_name", prop.sym_name);
}

::llvm::LogicalResult PrimitiveOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getParametersAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Calyx10(attr, "parameters", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getPrimitiveNameAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Calyx8(attr, "primitiveName", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getSymNameAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Calyx1(attr, "sym_name", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult PrimitiveOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readOptionalAttribute(prop.parameters)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readAttribute(prop.primitiveName)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readAttribute(prop.sym_name)))
    return ::mlir::failure();
  return ::mlir::success();
}

void PrimitiveOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;

  writer.writeOptionalAttribute(prop.parameters);
  writer.writeAttribute(prop.primitiveName);
  writer.writeAttribute(prop.sym_name);
}

::llvm::StringRef PrimitiveOp::getSymName() {
  auto attr = getSymNameAttr();
  return attr.getValue();
}

::std::optional< ::mlir::ArrayAttr > PrimitiveOp::getParameters() {
  auto attr = getParametersAttr();
  return attr ? ::std::optional< ::mlir::ArrayAttr >(attr) : (::std::nullopt);
}

::llvm::StringRef PrimitiveOp::getPrimitiveName() {
  auto attr = getPrimitiveNameAttr();
  return attr.getValue();
}

void PrimitiveOp::setSymName(::llvm::StringRef attrValue) {
  getProperties().sym_name = ::mlir::Builder((*this)->getContext()).getStringAttr(attrValue);
}

void PrimitiveOp::setPrimitiveName(::llvm::StringRef attrValue) {
  getProperties().primitiveName = ::mlir::SymbolRefAttr::get(::mlir::Builder((*this)->getContext()).getContext(), attrValue);
}

void PrimitiveOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange results, ::mlir::StringAttr sym_name, /*optional*/::mlir::ArrayAttr parameters, ::mlir::FlatSymbolRefAttr primitiveName) {
  odsState.getOrAddProperties<Properties>().sym_name = sym_name;
  if (parameters) {
    odsState.getOrAddProperties<Properties>().parameters = parameters;
  }
  odsState.getOrAddProperties<Properties>().primitiveName = primitiveName;
  odsState.addTypes(results);
}

PrimitiveOp PrimitiveOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange results, ::mlir::StringAttr sym_name, /*optional*/::mlir::ArrayAttr parameters, ::mlir::FlatSymbolRefAttr primitiveName) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(results)>(results), std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(parameters)>(parameters), std::forward<decltype(primitiveName)>(primitiveName));
  auto __res__ = ::llvm::dyn_cast<PrimitiveOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

PrimitiveOp PrimitiveOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange results, ::mlir::StringAttr sym_name, /*optional*/::mlir::ArrayAttr parameters, ::mlir::FlatSymbolRefAttr primitiveName) {
  return create(builder, builder.getLoc(), std::forward<decltype(results)>(results), std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(parameters)>(parameters), std::forward<decltype(primitiveName)>(primitiveName));
}

void PrimitiveOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange results, ::llvm::StringRef sym_name, /*optional*/::mlir::ArrayAttr parameters, ::llvm::StringRef primitiveName) {
  odsState.getOrAddProperties<Properties>().sym_name = odsBuilder.getStringAttr(sym_name);
  if (parameters) {
    odsState.getOrAddProperties<Properties>().parameters = parameters;
  }
  odsState.getOrAddProperties<Properties>().primitiveName = ::mlir::SymbolRefAttr::get(odsBuilder.getContext(), primitiveName);
  odsState.addTypes(results);
}

PrimitiveOp PrimitiveOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange results, ::llvm::StringRef sym_name, /*optional*/::mlir::ArrayAttr parameters, ::llvm::StringRef primitiveName) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(results)>(results), std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(parameters)>(parameters), std::forward<decltype(primitiveName)>(primitiveName));
  auto __res__ = ::llvm::dyn_cast<PrimitiveOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

PrimitiveOp PrimitiveOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange results, ::llvm::StringRef sym_name, /*optional*/::mlir::ArrayAttr parameters, ::llvm::StringRef primitiveName) {
  return create(builder, builder.getLoc(), std::forward<decltype(results)>(results), std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(parameters)>(parameters), std::forward<decltype(primitiveName)>(primitiveName));
}

void PrimitiveOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<PrimitiveOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

PrimitiveOp PrimitiveOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<PrimitiveOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

PrimitiveOp PrimitiveOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void PrimitiveOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  odsState.addTypes(resultTypes);
}

PrimitiveOp PrimitiveOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<PrimitiveOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

PrimitiveOp PrimitiveOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult PrimitiveOp::verifyInvariantsImpl() {
  auto tblgen_parameters = getProperties().parameters; (void)tblgen_parameters;
  auto tblgen_primitiveName = getProperties().primitiveName; (void)tblgen_primitiveName;
  if (!tblgen_primitiveName) return emitOpError("requires attribute 'primitiveName'");
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;
  if (!tblgen_sym_name) return emitOpError("requires attribute 'sym_name'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Calyx1(*this, tblgen_sym_name, "sym_name")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Calyx10(*this, tblgen_parameters, "parameters")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Calyx8(*this, tblgen_primitiveName, "primitiveName")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx7(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult PrimitiveOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult PrimitiveOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::StringAttr sym_nameAttr;
  ::mlir::FlatSymbolRefAttr primitiveNameAttr;
  ::mlir::ArrayAttr parametersAttr;
  ::llvm::SmallVector<::mlir::Type, 1> resultsTypes;

  if (parser.parseSymbolName(sym_nameAttr))
    return ::mlir::failure();
  if (sym_nameAttr) result.getOrAddProperties<PrimitiveOp::Properties>().sym_name = sym_nameAttr;
  if (parser.parseKeyword("of"))
    return ::mlir::failure();

  if (parser.parseCustomAttributeWithFallback(primitiveNameAttr, parser.getBuilder().getType<::mlir::NoneType>())) {
    return ::mlir::failure();
  }
  if (primitiveNameAttr) result.getOrAddProperties<PrimitiveOp::Properties>().primitiveName = primitiveNameAttr;
  {
    auto odsResult = parseParameterList(parser, parametersAttr);
    if (odsResult) return ::mlir::failure();
    if (parametersAttr)
      result.getOrAddProperties<PrimitiveOp::Properties>().parameters = parametersAttr;
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

  if (parser.parseTypeList(resultsTypes))
    return ::mlir::failure();
  }
  result.addTypes(resultsTypes);
  return ::mlir::success();
}

void PrimitiveOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter.printSymbolName(getSymNameAttr().getValue());
  _odsPrinter << ' ' << "of";
  _odsPrinter << ' ';
  _odsPrinter.printAttributeWithoutType(getPrimitiveNameAttr());
  printParameterList(_odsPrinter, *this, getParametersAttr());
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("sym_name");
  elidedAttrs.push_back("primitiveName");
  elidedAttrs.push_back("parameters");
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  if (!getResults().empty()) {
    _odsPrinter << ' ' << ":";
    _odsPrinter << ' ';
    _odsPrinter << getResults().getTypes();
  }
}


} // namespace circt::calyx
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::calyx::PrimitiveOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::calyx::detail::PrimitiveOpGenericAdaptorBase::Properties)

namespace circt::calyx {


//===----------------------------------------------------------------------===//
// ::circt::calyx::RegisterOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

RegisterOpGenericAdaptorBase::RegisterOpGenericAdaptorBase(RegisterOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::llvm::StringRef RegisterOpGenericAdaptorBase::getSymName() {
  auto attr = getSymNameAttr();
  return attr.getValue();
}


} // namespace detail
RegisterOpAdaptor::RegisterOpAdaptor(RegisterOp op) : RegisterOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult RegisterOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;
  if (!tblgen_sym_name) return emitError(loc, "'calyx.register' op requires attribute 'sym_name'");

  if (tblgen_sym_name && !((::llvm::isa<::mlir::StringAttr>(tblgen_sym_name))))
    return emitError(loc, "'calyx.register' op attribute 'sym_name' failed to satisfy constraint: string attribute");
  return ::mlir::success();
}

::llvm::LogicalResult RegisterOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
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

::mlir::Attribute RegisterOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
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

llvm::hash_code RegisterOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.sym_name.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> RegisterOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "sym_name")
      return prop.sym_name;
  return std::nullopt;
}

void RegisterOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "sym_name") {
       prop.sym_name = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.sym_name)>>(value);
       return;
    }
}

void RegisterOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.sym_name) attrs.append("sym_name", prop.sym_name);
}

::llvm::LogicalResult RegisterOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getSymNameAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Calyx1(attr, "sym_name", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult RegisterOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.sym_name)))
    return ::mlir::failure();
  return ::mlir::success();
}

void RegisterOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.sym_name);
}

::llvm::StringRef RegisterOp::getSymName() {
  auto attr = getSymNameAttr();
  return attr.getValue();
}

void RegisterOp::setSymName(::llvm::StringRef attrValue) {
  getProperties().sym_name = ::mlir::Builder((*this)->getContext()).getStringAttr(attrValue);
}

void RegisterOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, StringRef sym_name, size_t width) {
      odsState.addAttribute(mlir::SymbolTable::getSymbolAttrName(), odsBuilder.getStringAttr(sym_name));
      Type i1Type = odsBuilder.getI1Type();
      Type widthType = odsBuilder.getIntegerType(width);
      odsState.addTypes({widthType, i1Type, i1Type, i1Type, widthType, i1Type});
    
}

RegisterOp RegisterOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, StringRef sym_name, size_t width) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(width)>(width));
  auto __res__ = ::llvm::dyn_cast<RegisterOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

RegisterOp RegisterOp::create(::mlir::ImplicitLocOpBuilder &builder, StringRef sym_name, size_t width) {
  return create(builder, builder.getLoc(), std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(width)>(width));
}

void RegisterOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, StringRef sym_name, Type type) {
      odsState.addAttribute(mlir::SymbolTable::getSymbolAttrName(), odsBuilder.getStringAttr(sym_name));
      Type i1Type = odsBuilder.getI1Type();
      odsState.addTypes({type, i1Type, i1Type, i1Type, type, i1Type});
    
}

RegisterOp RegisterOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, StringRef sym_name, Type type) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(type)>(type));
  auto __res__ = ::llvm::dyn_cast<RegisterOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

RegisterOp RegisterOp::create(::mlir::ImplicitLocOpBuilder &builder, StringRef sym_name, Type type) {
  return create(builder, builder.getLoc(), std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(type)>(type));
}

::llvm::LogicalResult RegisterOp::verifyInvariantsImpl() {
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;
  if (!tblgen_sym_name) return emitOpError("requires attribute 'sym_name'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Calyx1(*this, tblgen_sym_name, "sym_name")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx5(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSResults(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx1(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup2 = getODSResults(2);

    for (auto v : valueGroup2) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx1(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup3 = getODSResults(3);

    for (auto v : valueGroup3) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx1(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup4 = getODSResults(4);

    for (auto v : valueGroup4) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx5(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup5 = getODSResults(5);

    for (auto v : valueGroup5) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx1(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  if (!((std::equal_to<>()( (*this->getODSResults(0).begin()).getType() , (*this->getODSResults(4).begin()).getType()))))
    return emitOpError("failed to verify that lhs and rhs types should be equivalent");
  return ::mlir::success();
}

::llvm::LogicalResult RegisterOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult RegisterOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::StringAttr sym_nameAttr;
  ::llvm::SmallVector<::mlir::Type, 1> allResultTypes;

  if (parser.parseSymbolName(sym_nameAttr))
    return ::mlir::failure();
  if (sym_nameAttr) result.getOrAddProperties<RegisterOp::Properties>().sym_name = sym_nameAttr;
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

  if (parser.parseTypeList(allResultTypes))
    return ::mlir::failure();
  result.addTypes(allResultTypes);
  return ::mlir::success();
}

void RegisterOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter.printSymbolName(getSymNameAttr().getValue());
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("sym_name");
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
  _odsPrinter << getOperation()->getResultTypes();
}


} // namespace circt::calyx
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::calyx::RegisterOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::calyx::detail::RegisterOpGenericAdaptorBase::Properties)

namespace circt::calyx {


//===----------------------------------------------------------------------===//
// ::circt::calyx::RemSPipeLibOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

RemSPipeLibOpGenericAdaptorBase::RemSPipeLibOpGenericAdaptorBase(RemSPipeLibOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::llvm::StringRef RemSPipeLibOpGenericAdaptorBase::getSymName() {
  auto attr = getSymNameAttr();
  return attr.getValue();
}


} // namespace detail
RemSPipeLibOpAdaptor::RemSPipeLibOpAdaptor(RemSPipeLibOp op) : RemSPipeLibOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult RemSPipeLibOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;
  if (!tblgen_sym_name) return emitError(loc, "'calyx.std_rems_pipe' op requires attribute 'sym_name'");

  if (tblgen_sym_name && !((::llvm::isa<::mlir::StringAttr>(tblgen_sym_name))))
    return emitError(loc, "'calyx.std_rems_pipe' op attribute 'sym_name' failed to satisfy constraint: string attribute");
  return ::mlir::success();
}

::llvm::LogicalResult RemSPipeLibOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
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

::mlir::Attribute RemSPipeLibOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
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

llvm::hash_code RemSPipeLibOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.sym_name.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> RemSPipeLibOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "sym_name")
      return prop.sym_name;
  return std::nullopt;
}

void RemSPipeLibOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "sym_name") {
       prop.sym_name = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.sym_name)>>(value);
       return;
    }
}

void RemSPipeLibOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.sym_name) attrs.append("sym_name", prop.sym_name);
}

::llvm::LogicalResult RemSPipeLibOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getSymNameAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Calyx1(attr, "sym_name", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult RemSPipeLibOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.sym_name)))
    return ::mlir::failure();
  return ::mlir::success();
}

void RemSPipeLibOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.sym_name);
}

::llvm::StringRef RemSPipeLibOp::getSymName() {
  auto attr = getSymNameAttr();
  return attr.getValue();
}

void RemSPipeLibOp::setSymName(::llvm::StringRef attrValue) {
  getProperties().sym_name = ::mlir::Builder((*this)->getContext()).getStringAttr(attrValue);
}

void RemSPipeLibOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, StringRef sym_name, ::mlir::TypeRange resultTypes) {
      odsState.addAttribute(mlir::SymbolTable::getSymbolAttrName(), odsBuilder.getStringAttr(sym_name));
      odsState.addTypes(resultTypes);
    
}

RemSPipeLibOp RemSPipeLibOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, StringRef sym_name, ::mlir::TypeRange resultTypes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(resultTypes)>(resultTypes));
  auto __res__ = ::llvm::dyn_cast<RemSPipeLibOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

RemSPipeLibOp RemSPipeLibOp::create(::mlir::ImplicitLocOpBuilder &builder, StringRef sym_name, ::mlir::TypeRange resultTypes) {
  return create(builder, builder.getLoc(), std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(resultTypes)>(resultTypes));
}

::llvm::LogicalResult RemSPipeLibOp::verifyInvariantsImpl() {
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;
  if (!tblgen_sym_name) return emitOpError("requires attribute 'sym_name'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Calyx1(*this, tblgen_sym_name, "sym_name")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx1(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSResults(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx1(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup2 = getODSResults(2);

    for (auto v : valueGroup2) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx1(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup3 = getODSResults(3);

    for (auto v : valueGroup3) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx5(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup4 = getODSResults(4);

    for (auto v : valueGroup4) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx5(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup5 = getODSResults(5);

    for (auto v : valueGroup5) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx5(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup6 = getODSResults(6);

    for (auto v : valueGroup6) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx1(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  if (!((std::equal_to<>()( (*this->getODSResults(3).begin()).getType() , (*this->getODSResults(5).begin()).getType()))))
    return emitOpError("failed to verify that lhs and rhs types should be equivalent");
  if (!((std::equal_to<>()( (*this->getODSResults(3).begin()).getType() , (*this->getODSResults(4).begin()).getType()))))
    return emitOpError("failed to verify that lhs and rhs types should be equivalent");
  return ::mlir::success();
}

::llvm::LogicalResult RemSPipeLibOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult RemSPipeLibOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::StringAttr sym_nameAttr;
  ::llvm::SmallVector<::mlir::Type, 1> allResultTypes;

  if (parser.parseSymbolName(sym_nameAttr))
    return ::mlir::failure();
  if (sym_nameAttr) result.getOrAddProperties<RemSPipeLibOp::Properties>().sym_name = sym_nameAttr;
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

  if (parser.parseTypeList(allResultTypes))
    return ::mlir::failure();
  result.addTypes(allResultTypes);
  return ::mlir::success();
}

void RemSPipeLibOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter.printSymbolName(getSymNameAttr().getValue());
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("sym_name");
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
  _odsPrinter << getOperation()->getResultTypes();
}


} // namespace circt::calyx
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::calyx::RemSPipeLibOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::calyx::detail::RemSPipeLibOpGenericAdaptorBase::Properties)

namespace circt::calyx {


//===----------------------------------------------------------------------===//
// ::circt::calyx::RemUPipeLibOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

RemUPipeLibOpGenericAdaptorBase::RemUPipeLibOpGenericAdaptorBase(RemUPipeLibOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::llvm::StringRef RemUPipeLibOpGenericAdaptorBase::getSymName() {
  auto attr = getSymNameAttr();
  return attr.getValue();
}


} // namespace detail
RemUPipeLibOpAdaptor::RemUPipeLibOpAdaptor(RemUPipeLibOp op) : RemUPipeLibOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult RemUPipeLibOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;
  if (!tblgen_sym_name) return emitError(loc, "'calyx.std_remu_pipe' op requires attribute 'sym_name'");

  if (tblgen_sym_name && !((::llvm::isa<::mlir::StringAttr>(tblgen_sym_name))))
    return emitError(loc, "'calyx.std_remu_pipe' op attribute 'sym_name' failed to satisfy constraint: string attribute");
  return ::mlir::success();
}

::llvm::LogicalResult RemUPipeLibOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
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

::mlir::Attribute RemUPipeLibOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
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

llvm::hash_code RemUPipeLibOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.sym_name.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> RemUPipeLibOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "sym_name")
      return prop.sym_name;
  return std::nullopt;
}

void RemUPipeLibOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "sym_name") {
       prop.sym_name = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.sym_name)>>(value);
       return;
    }
}

void RemUPipeLibOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.sym_name) attrs.append("sym_name", prop.sym_name);
}

::llvm::LogicalResult RemUPipeLibOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getSymNameAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Calyx1(attr, "sym_name", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult RemUPipeLibOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.sym_name)))
    return ::mlir::failure();
  return ::mlir::success();
}

void RemUPipeLibOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.sym_name);
}

::llvm::StringRef RemUPipeLibOp::getSymName() {
  auto attr = getSymNameAttr();
  return attr.getValue();
}

void RemUPipeLibOp::setSymName(::llvm::StringRef attrValue) {
  getProperties().sym_name = ::mlir::Builder((*this)->getContext()).getStringAttr(attrValue);
}

void RemUPipeLibOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, StringRef sym_name, ::mlir::TypeRange resultTypes) {
      odsState.addAttribute(mlir::SymbolTable::getSymbolAttrName(), odsBuilder.getStringAttr(sym_name));
      odsState.addTypes(resultTypes);
    
}

RemUPipeLibOp RemUPipeLibOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, StringRef sym_name, ::mlir::TypeRange resultTypes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(resultTypes)>(resultTypes));
  auto __res__ = ::llvm::dyn_cast<RemUPipeLibOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

RemUPipeLibOp RemUPipeLibOp::create(::mlir::ImplicitLocOpBuilder &builder, StringRef sym_name, ::mlir::TypeRange resultTypes) {
  return create(builder, builder.getLoc(), std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(resultTypes)>(resultTypes));
}

::llvm::LogicalResult RemUPipeLibOp::verifyInvariantsImpl() {
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;
  if (!tblgen_sym_name) return emitOpError("requires attribute 'sym_name'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Calyx1(*this, tblgen_sym_name, "sym_name")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx1(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSResults(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx1(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup2 = getODSResults(2);

    for (auto v : valueGroup2) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx1(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup3 = getODSResults(3);

    for (auto v : valueGroup3) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx5(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup4 = getODSResults(4);

    for (auto v : valueGroup4) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx5(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup5 = getODSResults(5);

    for (auto v : valueGroup5) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx5(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup6 = getODSResults(6);

    for (auto v : valueGroup6) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx1(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  if (!((std::equal_to<>()( (*this->getODSResults(3).begin()).getType() , (*this->getODSResults(5).begin()).getType()))))
    return emitOpError("failed to verify that lhs and rhs types should be equivalent");
  if (!((std::equal_to<>()( (*this->getODSResults(3).begin()).getType() , (*this->getODSResults(4).begin()).getType()))))
    return emitOpError("failed to verify that lhs and rhs types should be equivalent");
  return ::mlir::success();
}

::llvm::LogicalResult RemUPipeLibOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult RemUPipeLibOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::StringAttr sym_nameAttr;
  ::llvm::SmallVector<::mlir::Type, 1> allResultTypes;

  if (parser.parseSymbolName(sym_nameAttr))
    return ::mlir::failure();
  if (sym_nameAttr) result.getOrAddProperties<RemUPipeLibOp::Properties>().sym_name = sym_nameAttr;
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

  if (parser.parseTypeList(allResultTypes))
    return ::mlir::failure();
  result.addTypes(allResultTypes);
  return ::mlir::success();
}

void RemUPipeLibOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter.printSymbolName(getSymNameAttr().getValue());
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("sym_name");
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
  _odsPrinter << getOperation()->getResultTypes();
}


} // namespace circt::calyx
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::calyx::RemUPipeLibOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::calyx::detail::RemUPipeLibOpGenericAdaptorBase::Properties)

namespace circt::calyx {


//===----------------------------------------------------------------------===//
// ::circt::calyx::RepeatOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

RepeatOpGenericAdaptorBase::RepeatOpGenericAdaptorBase(RepeatOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

uint32_t RepeatOpGenericAdaptorBase::getCount() {
  auto attr = getCountAttr();
  return attr.getValue().getZExtValue();
}


} // namespace detail
RepeatOpAdaptor::RepeatOpAdaptor(RepeatOp op) : RepeatOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult RepeatOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_count = getProperties().count; (void)tblgen_count;
  if (!tblgen_count) return emitError(loc, "'calyx.repeat' op requires attribute 'count'");

  if (tblgen_count && !(((::llvm::isa<::mlir::IntegerAttr>(tblgen_count))) && ((::llvm::cast<::mlir::IntegerAttr>(tblgen_count).getType().isSignlessInteger(32)))))
    return emitError(loc, "'calyx.repeat' op attribute 'count' failed to satisfy constraint: 32-bit signless integer attribute");
  return ::mlir::success();
}

::llvm::LogicalResult RepeatOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.count;
       auto attr = dict.get("count");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `count` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  return ::mlir::success();
}

::mlir::Attribute RepeatOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.count;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("count",
                                       propStorage));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code RepeatOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.count.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> RepeatOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "count")
      return prop.count;
  return std::nullopt;
}

void RepeatOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "count") {
       prop.count = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.count)>>(value);
       return;
    }
}

void RepeatOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.count) attrs.append("count", prop.count);
}

::llvm::LogicalResult RepeatOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getCountAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Calyx7(attr, "count", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult RepeatOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.count)))
    return ::mlir::failure();
  return ::mlir::success();
}

void RepeatOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.count);
}

uint32_t RepeatOp::getCount() {
  auto attr = getCountAttr();
  return attr.getValue().getZExtValue();
}

void RepeatOp::setCount(uint32_t attrValue) {
  getProperties().count = ::mlir::Builder((*this)->getContext()).getIntegerAttr(::mlir::Builder((*this)->getContext()).getIntegerType(32), attrValue);
}

void RepeatOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, uint32_t count) {
        odsState.addAttribute("count", 
          mlir::IntegerAttr::get(IntegerType::get(odsState.getContext(), 32), count)
        );

        Region *body = odsState.addRegion();
        body->push_back(new Block());
    
}

RepeatOp RepeatOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, uint32_t count) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(count)>(count));
  auto __res__ = ::llvm::dyn_cast<RepeatOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

RepeatOp RepeatOp::create(::mlir::ImplicitLocOpBuilder &builder, uint32_t count) {
  return create(builder, builder.getLoc(), std::forward<decltype(count)>(count));
}

::llvm::LogicalResult RepeatOp::verifyInvariantsImpl() {
  auto tblgen_count = getProperties().count; (void)tblgen_count;
  if (!tblgen_count) return emitOpError("requires attribute 'count'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Calyx7(*this, tblgen_count, "count")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;

    for (auto &region : ::llvm::MutableArrayRef((*this)->getRegion(0)))
      if (::mlir::failed(__mlir_ods_local_region_constraint_Calyx1(*this, region, "body", index++)))
        return ::mlir::failure();
  }
  return ::mlir::success();
}

::llvm::LogicalResult RepeatOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult RepeatOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::IntegerAttr countAttr;
  std::unique_ptr<::mlir::Region> bodyRegion = std::make_unique<::mlir::Region>();

  if (parser.parseCustomAttributeWithFallback(countAttr, parser.getBuilder().getIntegerType(32))) {
    return ::mlir::failure();
  }
  if (countAttr) result.getOrAddProperties<RepeatOp::Properties>().count = countAttr;

  if (parser.parseRegion(*bodyRegion))
    return ::mlir::failure();

  if (bodyRegion->empty()) bodyRegion->emplaceBlock();
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
  return ::mlir::success();
}

void RepeatOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter.printAttributeWithoutType(getCountAttr());
  _odsPrinter << ' ';
  _odsPrinter.printRegion(getBody());
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("count");
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
}


} // namespace circt::calyx
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::calyx::RepeatOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::calyx::detail::RepeatOpGenericAdaptorBase::Properties)

namespace circt::calyx {


//===----------------------------------------------------------------------===//
// ::circt::calyx::RshLibOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

RshLibOpGenericAdaptorBase::RshLibOpGenericAdaptorBase(RshLibOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::llvm::StringRef RshLibOpGenericAdaptorBase::getSymName() {
  auto attr = getSymNameAttr();
  return attr.getValue();
}


} // namespace detail
RshLibOpAdaptor::RshLibOpAdaptor(RshLibOp op) : RshLibOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult RshLibOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;
  if (!tblgen_sym_name) return emitError(loc, "'calyx.std_rsh' op requires attribute 'sym_name'");

  if (tblgen_sym_name && !((::llvm::isa<::mlir::StringAttr>(tblgen_sym_name))))
    return emitError(loc, "'calyx.std_rsh' op attribute 'sym_name' failed to satisfy constraint: string attribute");
  return ::mlir::success();
}

::llvm::LogicalResult RshLibOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
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

::mlir::Attribute RshLibOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
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

llvm::hash_code RshLibOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.sym_name.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> RshLibOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "sym_name")
      return prop.sym_name;
  return std::nullopt;
}

void RshLibOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "sym_name") {
       prop.sym_name = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.sym_name)>>(value);
       return;
    }
}

void RshLibOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.sym_name) attrs.append("sym_name", prop.sym_name);
}

::llvm::LogicalResult RshLibOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getSymNameAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Calyx1(attr, "sym_name", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult RshLibOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.sym_name)))
    return ::mlir::failure();
  return ::mlir::success();
}

void RshLibOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.sym_name);
}

::llvm::StringRef RshLibOp::getSymName() {
  auto attr = getSymNameAttr();
  return attr.getValue();
}

void RshLibOp::setSymName(::llvm::StringRef attrValue) {
  getProperties().sym_name = ::mlir::Builder((*this)->getContext()).getStringAttr(attrValue);
}

void RshLibOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, StringRef sym_name, ::mlir::TypeRange resultTypes) {
      odsState.addAttribute(mlir::SymbolTable::getSymbolAttrName(), odsBuilder.getStringAttr(sym_name));
      odsState.addTypes(resultTypes);
    
}

RshLibOp RshLibOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, StringRef sym_name, ::mlir::TypeRange resultTypes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(resultTypes)>(resultTypes));
  auto __res__ = ::llvm::dyn_cast<RshLibOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

RshLibOp RshLibOp::create(::mlir::ImplicitLocOpBuilder &builder, StringRef sym_name, ::mlir::TypeRange resultTypes) {
  return create(builder, builder.getLoc(), std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(resultTypes)>(resultTypes));
}

::llvm::LogicalResult RshLibOp::verifyInvariantsImpl() {
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;
  if (!tblgen_sym_name) return emitOpError("requires attribute 'sym_name'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Calyx1(*this, tblgen_sym_name, "sym_name")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx5(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSResults(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx5(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup2 = getODSResults(2);

    for (auto v : valueGroup2) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx5(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  if (!((std::equal_to<>()( (*this->getODSResults(0).begin()).getType() , (*this->getODSResults(2).begin()).getType()))))
    return emitOpError("failed to verify that lhs and rhs types should be equivalent");
  if (!((std::equal_to<>()( (*this->getODSResults(0).begin()).getType() , (*this->getODSResults(1).begin()).getType()))))
    return emitOpError("failed to verify that lhs and rhs types should be equivalent");
  return ::mlir::success();
}

::llvm::LogicalResult RshLibOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult RshLibOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::StringAttr sym_nameAttr;
  ::llvm::SmallVector<::mlir::Type, 1> allResultTypes;

  if (parser.parseSymbolName(sym_nameAttr))
    return ::mlir::failure();
  if (sym_nameAttr) result.getOrAddProperties<RshLibOp::Properties>().sym_name = sym_nameAttr;
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

  if (parser.parseTypeList(allResultTypes))
    return ::mlir::failure();
  result.addTypes(allResultTypes);
  return ::mlir::success();
}

void RshLibOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter.printSymbolName(getSymNameAttr().getValue());
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("sym_name");
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
  _odsPrinter << getOperation()->getResultTypes();
}


} // namespace circt::calyx
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::calyx::RshLibOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::calyx::detail::RshLibOpGenericAdaptorBase::Properties)

namespace circt::calyx {


//===----------------------------------------------------------------------===//
// ::circt::calyx::SeqLibOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

SeqLibOpGenericAdaptorBase::SeqLibOpGenericAdaptorBase(SeqLibOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::llvm::StringRef SeqLibOpGenericAdaptorBase::getSymName() {
  auto attr = getSymNameAttr();
  return attr.getValue();
}


} // namespace detail
SeqLibOpAdaptor::SeqLibOpAdaptor(SeqLibOp op) : SeqLibOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult SeqLibOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;
  if (!tblgen_sym_name) return emitError(loc, "'calyx.std_seq' op requires attribute 'sym_name'");

  if (tblgen_sym_name && !((::llvm::isa<::mlir::StringAttr>(tblgen_sym_name))))
    return emitError(loc, "'calyx.std_seq' op attribute 'sym_name' failed to satisfy constraint: string attribute");
  return ::mlir::success();
}

::llvm::LogicalResult SeqLibOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
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

::mlir::Attribute SeqLibOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
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

llvm::hash_code SeqLibOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.sym_name.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> SeqLibOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "sym_name")
      return prop.sym_name;
  return std::nullopt;
}

void SeqLibOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "sym_name") {
       prop.sym_name = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.sym_name)>>(value);
       return;
    }
}

void SeqLibOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.sym_name) attrs.append("sym_name", prop.sym_name);
}

::llvm::LogicalResult SeqLibOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getSymNameAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Calyx1(attr, "sym_name", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult SeqLibOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.sym_name)))
    return ::mlir::failure();
  return ::mlir::success();
}

void SeqLibOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.sym_name);
}

::llvm::StringRef SeqLibOp::getSymName() {
  auto attr = getSymNameAttr();
  return attr.getValue();
}

void SeqLibOp::setSymName(::llvm::StringRef attrValue) {
  getProperties().sym_name = ::mlir::Builder((*this)->getContext()).getStringAttr(attrValue);
}

void SeqLibOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, StringRef sym_name, ::mlir::TypeRange resultTypes) {
      odsState.addAttribute(mlir::SymbolTable::getSymbolAttrName(), odsBuilder.getStringAttr(sym_name));
      odsState.addTypes(resultTypes);
    
}

SeqLibOp SeqLibOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, StringRef sym_name, ::mlir::TypeRange resultTypes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(resultTypes)>(resultTypes));
  auto __res__ = ::llvm::dyn_cast<SeqLibOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SeqLibOp SeqLibOp::create(::mlir::ImplicitLocOpBuilder &builder, StringRef sym_name, ::mlir::TypeRange resultTypes) {
  return create(builder, builder.getLoc(), std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(resultTypes)>(resultTypes));
}

::llvm::LogicalResult SeqLibOp::verifyInvariantsImpl() {
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;
  if (!tblgen_sym_name) return emitOpError("requires attribute 'sym_name'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Calyx1(*this, tblgen_sym_name, "sym_name")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx5(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSResults(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx5(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup2 = getODSResults(2);

    for (auto v : valueGroup2) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx1(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  if (!((std::equal_to<>()( (*this->getODSResults(0).begin()).getType() , (*this->getODSResults(1).begin()).getType()))))
    return emitOpError("failed to verify that lhs and rhs types should be equivalent");
  return ::mlir::success();
}

::llvm::LogicalResult SeqLibOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult SeqLibOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::StringAttr sym_nameAttr;
  ::llvm::SmallVector<::mlir::Type, 1> allResultTypes;

  if (parser.parseSymbolName(sym_nameAttr))
    return ::mlir::failure();
  if (sym_nameAttr) result.getOrAddProperties<SeqLibOp::Properties>().sym_name = sym_nameAttr;
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

  if (parser.parseTypeList(allResultTypes))
    return ::mlir::failure();
  result.addTypes(allResultTypes);
  return ::mlir::success();
}

void SeqLibOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter.printSymbolName(getSymNameAttr().getValue());
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("sym_name");
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
  _odsPrinter << getOperation()->getResultTypes();
}


} // namespace circt::calyx
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::calyx::SeqLibOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::calyx::detail::SeqLibOpGenericAdaptorBase::Properties)

namespace circt::calyx {


//===----------------------------------------------------------------------===//
// ::circt::calyx::SeqMemoryOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

SeqMemoryOpGenericAdaptorBase::SeqMemoryOpGenericAdaptorBase(SeqMemoryOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::llvm::StringRef SeqMemoryOpGenericAdaptorBase::getSymName() {
  auto attr = getSymNameAttr();
  return attr.getValue();
}

uint64_t SeqMemoryOpGenericAdaptorBase::getWidth() {
  auto attr = getWidthAttr();
  return attr.getValue().getZExtValue();
}

::mlir::ArrayAttr SeqMemoryOpGenericAdaptorBase::getSizes() {
  auto attr = getSizesAttr();
  return attr;
}

::mlir::ArrayAttr SeqMemoryOpGenericAdaptorBase::getAddrSizes() {
  auto attr = getAddrSizesAttr();
  return attr;
}


} // namespace detail
SeqMemoryOpAdaptor::SeqMemoryOpAdaptor(SeqMemoryOp op) : SeqMemoryOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult SeqMemoryOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_addrSizes = getProperties().addrSizes; (void)tblgen_addrSizes;
  if (!tblgen_addrSizes) return emitError(loc, "'calyx.seq_mem' op requires attribute 'addrSizes'");
  auto tblgen_sizes = getProperties().sizes; (void)tblgen_sizes;
  if (!tblgen_sizes) return emitError(loc, "'calyx.seq_mem' op requires attribute 'sizes'");
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;
  if (!tblgen_sym_name) return emitError(loc, "'calyx.seq_mem' op requires attribute 'sym_name'");
  auto tblgen_width = getProperties().width; (void)tblgen_width;
  if (!tblgen_width) return emitError(loc, "'calyx.seq_mem' op requires attribute 'width'");

  if (tblgen_sym_name && !((::llvm::isa<::mlir::StringAttr>(tblgen_sym_name))))
    return emitError(loc, "'calyx.seq_mem' op attribute 'sym_name' failed to satisfy constraint: string attribute");

  if (tblgen_width && !(((::llvm::isa<::mlir::IntegerAttr>(tblgen_width))) && ((::llvm::cast<::mlir::IntegerAttr>(tblgen_width).getType().isSignlessInteger(64)))))
    return emitError(loc, "'calyx.seq_mem' op attribute 'width' failed to satisfy constraint: 64-bit signless integer attribute");

  if (tblgen_sizes && !((::llvm::isa<::mlir::ArrayAttr>(tblgen_sizes))))
    return emitError(loc, "'calyx.seq_mem' op attribute 'sizes' failed to satisfy constraint: array attribute");

  if (tblgen_addrSizes && !((::llvm::isa<::mlir::ArrayAttr>(tblgen_addrSizes))))
    return emitError(loc, "'calyx.seq_mem' op attribute 'addrSizes' failed to satisfy constraint: array attribute");
  return ::mlir::success();
}

std::pair<unsigned, unsigned> SeqMemoryOp::getODSResultIndexAndLength(unsigned index) {
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

::llvm::LogicalResult SeqMemoryOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.addrSizes;
       auto attr = dict.get("addrSizes");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `addrSizes` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.sizes;
       auto attr = dict.get("sizes");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `sizes` in property conversion: " << attr;
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
    auto &propStorage = prop.width;
       auto attr = dict.get("width");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `width` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  return ::mlir::success();
}

::mlir::Attribute SeqMemoryOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.addrSizes;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("addrSizes",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.sizes;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("sizes",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.sym_name;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("sym_name",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.width;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("width",
                                       propStorage));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code SeqMemoryOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.addrSizes.getAsOpaquePointer()), 
    llvm::hash_value(prop.sizes.getAsOpaquePointer()), 
    llvm::hash_value(prop.sym_name.getAsOpaquePointer()), 
    llvm::hash_value(prop.width.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> SeqMemoryOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "addrSizes")
      return prop.addrSizes;

    if (name == "sizes")
      return prop.sizes;

    if (name == "sym_name")
      return prop.sym_name;

    if (name == "width")
      return prop.width;
  return std::nullopt;
}

void SeqMemoryOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "addrSizes") {
       prop.addrSizes = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.addrSizes)>>(value);
       return;
    }

    if (name == "sizes") {
       prop.sizes = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.sizes)>>(value);
       return;
    }

    if (name == "sym_name") {
       prop.sym_name = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.sym_name)>>(value);
       return;
    }

    if (name == "width") {
       prop.width = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.width)>>(value);
       return;
    }
}

void SeqMemoryOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.addrSizes) attrs.append("addrSizes", prop.addrSizes);

    if (prop.sizes) attrs.append("sizes", prop.sizes);

    if (prop.sym_name) attrs.append("sym_name", prop.sym_name);

    if (prop.width) attrs.append("width", prop.width);
}

::llvm::LogicalResult SeqMemoryOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getAddrSizesAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Calyx4(attr, "addrSizes", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getSizesAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Calyx4(attr, "sizes", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getSymNameAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Calyx1(attr, "sym_name", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getWidthAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Calyx9(attr, "width", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult SeqMemoryOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.addrSizes)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readAttribute(prop.sizes)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readAttribute(prop.sym_name)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readAttribute(prop.width)))
    return ::mlir::failure();
  return ::mlir::success();
}

void SeqMemoryOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.addrSizes);
  writer.writeAttribute(prop.sizes);
  writer.writeAttribute(prop.sym_name);
  writer.writeAttribute(prop.width);
}

::llvm::StringRef SeqMemoryOp::getSymName() {
  auto attr = getSymNameAttr();
  return attr.getValue();
}

uint64_t SeqMemoryOp::getWidth() {
  auto attr = getWidthAttr();
  return attr.getValue().getZExtValue();
}

::mlir::ArrayAttr SeqMemoryOp::getSizes() {
  auto attr = getSizesAttr();
  return attr;
}

::mlir::ArrayAttr SeqMemoryOp::getAddrSizes() {
  auto attr = getAddrSizesAttr();
  return attr;
}

void SeqMemoryOp::setSymName(::llvm::StringRef attrValue) {
  getProperties().sym_name = ::mlir::Builder((*this)->getContext()).getStringAttr(attrValue);
}

void SeqMemoryOp::setWidth(uint64_t attrValue) {
  getProperties().width = ::mlir::Builder((*this)->getContext()).getIntegerAttr(::mlir::Builder((*this)->getContext()).getIntegerType(64), attrValue);
}

SeqMemoryOp SeqMemoryOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, StringRef sym_name, int64_t width, ArrayRef<int64_t> sizes, ArrayRef<int64_t> addrSizes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(width)>(width), std::forward<decltype(sizes)>(sizes), std::forward<decltype(addrSizes)>(addrSizes));
  auto __res__ = ::llvm::dyn_cast<SeqMemoryOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SeqMemoryOp SeqMemoryOp::create(::mlir::ImplicitLocOpBuilder &builder, StringRef sym_name, int64_t width, ArrayRef<int64_t> sizes, ArrayRef<int64_t> addrSizes) {
  return create(builder, builder.getLoc(), std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(width)>(width), std::forward<decltype(sizes)>(sizes), std::forward<decltype(addrSizes)>(addrSizes));
}

::llvm::LogicalResult SeqMemoryOp::verifyInvariantsImpl() {
  auto tblgen_addrSizes = getProperties().addrSizes; (void)tblgen_addrSizes;
  if (!tblgen_addrSizes) return emitOpError("requires attribute 'addrSizes'");
  auto tblgen_sizes = getProperties().sizes; (void)tblgen_sizes;
  if (!tblgen_sizes) return emitOpError("requires attribute 'sizes'");
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;
  if (!tblgen_sym_name) return emitOpError("requires attribute 'sym_name'");
  auto tblgen_width = getProperties().width; (void)tblgen_width;
  if (!tblgen_width) return emitOpError("requires attribute 'width'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Calyx1(*this, tblgen_sym_name, "sym_name")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Calyx9(*this, tblgen_width, "width")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Calyx4(*this, tblgen_sizes, "sizes")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Calyx4(*this, tblgen_addrSizes, "addrSizes")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx8(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult SeqMemoryOp::verifyInvariants() {
  if(::mlir::succeeded(verifyInvariantsImpl()) && ::mlir::succeeded(verify()))
    return ::mlir::success();
  return ::mlir::failure();
}

::mlir::ParseResult SeqMemoryOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::StringAttr sym_nameAttr;
  ::mlir::ArrayAttr sizesAttr;
  ::mlir::IntegerAttr widthAttr;
  ::mlir::ArrayAttr addrSizesAttr;
  ::llvm::SmallVector<::mlir::Type, 1> resultsTypes;

  if (parser.parseSymbolName(sym_nameAttr))
    return ::mlir::failure();
  if (sym_nameAttr) result.getOrAddProperties<SeqMemoryOp::Properties>().sym_name = sym_nameAttr;
  if (parser.parseLess())
    return ::mlir::failure();

  if (parser.parseCustomAttributeWithFallback(sizesAttr, parser.getBuilder().getType<::mlir::NoneType>())) {
    return ::mlir::failure();
  }
  if (sizesAttr) result.getOrAddProperties<SeqMemoryOp::Properties>().sizes = sizesAttr;
  if (parser.parseKeyword("x"))
    return ::mlir::failure();

  if (parser.parseCustomAttributeWithFallback(widthAttr, parser.getBuilder().getIntegerType(64))) {
    return ::mlir::failure();
  }
  if (widthAttr) result.getOrAddProperties<SeqMemoryOp::Properties>().width = widthAttr;
  if (parser.parseGreater())
    return ::mlir::failure();

  if (parser.parseCustomAttributeWithFallback(addrSizesAttr, parser.getBuilder().getType<::mlir::NoneType>())) {
    return ::mlir::failure();
  }
  if (addrSizesAttr) result.getOrAddProperties<SeqMemoryOp::Properties>().addrSizes = addrSizesAttr;
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

  if (parser.parseTypeList(resultsTypes))
    return ::mlir::failure();
  result.addTypes(resultsTypes);
  return ::mlir::success();
}

void SeqMemoryOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter.printSymbolName(getSymNameAttr().getValue());
  _odsPrinter << ' ';
  _odsPrinter << "<";
  _odsPrinter.printAttributeWithoutType(getSizesAttr());
  _odsPrinter << ' ' << "x";
  _odsPrinter << ' ';
  _odsPrinter.printAttributeWithoutType(getWidthAttr());
  _odsPrinter << ">";
  _odsPrinter << ' ';
  _odsPrinter.printAttributeWithoutType(getAddrSizesAttr());
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("sym_name");
  elidedAttrs.push_back("sizes");
  elidedAttrs.push_back("width");
  elidedAttrs.push_back("addrSizes");
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
  _odsPrinter << getResults().getTypes();
}

bool SeqMemoryOp::isCombinational() { return false; }

} // namespace circt::calyx
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::calyx::SeqMemoryOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::calyx::detail::SeqMemoryOpGenericAdaptorBase::Properties)

namespace circt::calyx {


//===----------------------------------------------------------------------===//
// ::circt::calyx::SeqOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

SeqOpGenericAdaptorBase::SeqOpGenericAdaptorBase(SeqOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}


} // namespace detail
SeqOpAdaptor::SeqOpAdaptor(SeqOp op) : SeqOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult SeqOpAdaptor::verify(::mlir::Location loc) {
  return ::mlir::success();
}

::llvm::LogicalResult SeqOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }
      return ::mlir::success();
}

::mlir::Attribute SeqOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code SeqOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine();
}

std::optional<mlir::Attribute> SeqOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
  return std::nullopt;
}

void SeqOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
}

void SeqOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
}

::llvm::LogicalResult SeqOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    return ::mlir::success();
}

void SeqOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState) {
      Region* region = odsState.addRegion();
      region->push_back(new Block());
    
}

SeqOp SeqOp::create(::mlir::OpBuilder &builder, ::mlir::Location location) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__);
  auto __res__ = ::llvm::dyn_cast<SeqOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SeqOp SeqOp::create(::mlir::ImplicitLocOpBuilder &builder) {
  return create(builder, builder.getLoc());
}

::llvm::LogicalResult SeqOp::verifyInvariantsImpl() {
  {
    unsigned index = 0; (void)index;

    for (auto &region : ::llvm::MutableArrayRef((*this)->getRegion(0)))
      if (::mlir::failed(__mlir_ods_local_region_constraint_Calyx1(*this, region, "body", index++)))
        return ::mlir::failure();
  }
  return ::mlir::success();
}

::llvm::LogicalResult SeqOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult SeqOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  std::unique_ptr<::mlir::Region> bodyRegion = std::make_unique<::mlir::Region>();

  if (parser.parseRegion(*bodyRegion))
    return ::mlir::failure();

  if (bodyRegion->empty()) bodyRegion->emplaceBlock();
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
  return ::mlir::success();
}

void SeqOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter.printRegion(getBody());
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
}


} // namespace circt::calyx
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::calyx::SeqOp)

namespace circt::calyx {


//===----------------------------------------------------------------------===//
// ::circt::calyx::SgeLibOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

SgeLibOpGenericAdaptorBase::SgeLibOpGenericAdaptorBase(SgeLibOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::llvm::StringRef SgeLibOpGenericAdaptorBase::getSymName() {
  auto attr = getSymNameAttr();
  return attr.getValue();
}


} // namespace detail
SgeLibOpAdaptor::SgeLibOpAdaptor(SgeLibOp op) : SgeLibOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult SgeLibOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;
  if (!tblgen_sym_name) return emitError(loc, "'calyx.std_sge' op requires attribute 'sym_name'");

  if (tblgen_sym_name && !((::llvm::isa<::mlir::StringAttr>(tblgen_sym_name))))
    return emitError(loc, "'calyx.std_sge' op attribute 'sym_name' failed to satisfy constraint: string attribute");
  return ::mlir::success();
}

::llvm::LogicalResult SgeLibOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
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

::mlir::Attribute SgeLibOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
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

llvm::hash_code SgeLibOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.sym_name.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> SgeLibOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "sym_name")
      return prop.sym_name;
  return std::nullopt;
}

void SgeLibOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "sym_name") {
       prop.sym_name = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.sym_name)>>(value);
       return;
    }
}

void SgeLibOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.sym_name) attrs.append("sym_name", prop.sym_name);
}

::llvm::LogicalResult SgeLibOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getSymNameAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Calyx1(attr, "sym_name", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult SgeLibOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.sym_name)))
    return ::mlir::failure();
  return ::mlir::success();
}

void SgeLibOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.sym_name);
}

::llvm::StringRef SgeLibOp::getSymName() {
  auto attr = getSymNameAttr();
  return attr.getValue();
}

void SgeLibOp::setSymName(::llvm::StringRef attrValue) {
  getProperties().sym_name = ::mlir::Builder((*this)->getContext()).getStringAttr(attrValue);
}

void SgeLibOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, StringRef sym_name, ::mlir::TypeRange resultTypes) {
      odsState.addAttribute(mlir::SymbolTable::getSymbolAttrName(), odsBuilder.getStringAttr(sym_name));
      odsState.addTypes(resultTypes);
    
}

SgeLibOp SgeLibOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, StringRef sym_name, ::mlir::TypeRange resultTypes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(resultTypes)>(resultTypes));
  auto __res__ = ::llvm::dyn_cast<SgeLibOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SgeLibOp SgeLibOp::create(::mlir::ImplicitLocOpBuilder &builder, StringRef sym_name, ::mlir::TypeRange resultTypes) {
  return create(builder, builder.getLoc(), std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(resultTypes)>(resultTypes));
}

::llvm::LogicalResult SgeLibOp::verifyInvariantsImpl() {
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;
  if (!tblgen_sym_name) return emitOpError("requires attribute 'sym_name'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Calyx1(*this, tblgen_sym_name, "sym_name")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx5(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSResults(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx5(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup2 = getODSResults(2);

    for (auto v : valueGroup2) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx1(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  if (!((std::equal_to<>()( (*this->getODSResults(0).begin()).getType() , (*this->getODSResults(1).begin()).getType()))))
    return emitOpError("failed to verify that lhs and rhs types should be equivalent");
  return ::mlir::success();
}

::llvm::LogicalResult SgeLibOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult SgeLibOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::StringAttr sym_nameAttr;
  ::llvm::SmallVector<::mlir::Type, 1> allResultTypes;

  if (parser.parseSymbolName(sym_nameAttr))
    return ::mlir::failure();
  if (sym_nameAttr) result.getOrAddProperties<SgeLibOp::Properties>().sym_name = sym_nameAttr;
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

  if (parser.parseTypeList(allResultTypes))
    return ::mlir::failure();
  result.addTypes(allResultTypes);
  return ::mlir::success();
}

void SgeLibOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter.printSymbolName(getSymNameAttr().getValue());
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("sym_name");
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
  _odsPrinter << getOperation()->getResultTypes();
}


} // namespace circt::calyx
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::calyx::SgeLibOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::calyx::detail::SgeLibOpGenericAdaptorBase::Properties)

namespace circt::calyx {


//===----------------------------------------------------------------------===//
// ::circt::calyx::SgtLibOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

SgtLibOpGenericAdaptorBase::SgtLibOpGenericAdaptorBase(SgtLibOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::llvm::StringRef SgtLibOpGenericAdaptorBase::getSymName() {
  auto attr = getSymNameAttr();
  return attr.getValue();
}


} // namespace detail
SgtLibOpAdaptor::SgtLibOpAdaptor(SgtLibOp op) : SgtLibOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult SgtLibOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;
  if (!tblgen_sym_name) return emitError(loc, "'calyx.std_sgt' op requires attribute 'sym_name'");

  if (tblgen_sym_name && !((::llvm::isa<::mlir::StringAttr>(tblgen_sym_name))))
    return emitError(loc, "'calyx.std_sgt' op attribute 'sym_name' failed to satisfy constraint: string attribute");
  return ::mlir::success();
}

::llvm::LogicalResult SgtLibOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
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

::mlir::Attribute SgtLibOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
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

llvm::hash_code SgtLibOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.sym_name.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> SgtLibOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "sym_name")
      return prop.sym_name;
  return std::nullopt;
}

void SgtLibOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "sym_name") {
       prop.sym_name = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.sym_name)>>(value);
       return;
    }
}

void SgtLibOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.sym_name) attrs.append("sym_name", prop.sym_name);
}

::llvm::LogicalResult SgtLibOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getSymNameAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Calyx1(attr, "sym_name", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult SgtLibOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.sym_name)))
    return ::mlir::failure();
  return ::mlir::success();
}

void SgtLibOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.sym_name);
}

::llvm::StringRef SgtLibOp::getSymName() {
  auto attr = getSymNameAttr();
  return attr.getValue();
}

void SgtLibOp::setSymName(::llvm::StringRef attrValue) {
  getProperties().sym_name = ::mlir::Builder((*this)->getContext()).getStringAttr(attrValue);
}

void SgtLibOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, StringRef sym_name, ::mlir::TypeRange resultTypes) {
      odsState.addAttribute(mlir::SymbolTable::getSymbolAttrName(), odsBuilder.getStringAttr(sym_name));
      odsState.addTypes(resultTypes);
    
}

SgtLibOp SgtLibOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, StringRef sym_name, ::mlir::TypeRange resultTypes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(resultTypes)>(resultTypes));
  auto __res__ = ::llvm::dyn_cast<SgtLibOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SgtLibOp SgtLibOp::create(::mlir::ImplicitLocOpBuilder &builder, StringRef sym_name, ::mlir::TypeRange resultTypes) {
  return create(builder, builder.getLoc(), std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(resultTypes)>(resultTypes));
}

::llvm::LogicalResult SgtLibOp::verifyInvariantsImpl() {
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;
  if (!tblgen_sym_name) return emitOpError("requires attribute 'sym_name'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Calyx1(*this, tblgen_sym_name, "sym_name")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx5(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSResults(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx5(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup2 = getODSResults(2);

    for (auto v : valueGroup2) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx1(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  if (!((std::equal_to<>()( (*this->getODSResults(0).begin()).getType() , (*this->getODSResults(1).begin()).getType()))))
    return emitOpError("failed to verify that lhs and rhs types should be equivalent");
  return ::mlir::success();
}

::llvm::LogicalResult SgtLibOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult SgtLibOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::StringAttr sym_nameAttr;
  ::llvm::SmallVector<::mlir::Type, 1> allResultTypes;

  if (parser.parseSymbolName(sym_nameAttr))
    return ::mlir::failure();
  if (sym_nameAttr) result.getOrAddProperties<SgtLibOp::Properties>().sym_name = sym_nameAttr;
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

  if (parser.parseTypeList(allResultTypes))
    return ::mlir::failure();
  result.addTypes(allResultTypes);
  return ::mlir::success();
}

void SgtLibOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter.printSymbolName(getSymNameAttr().getValue());
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("sym_name");
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
  _odsPrinter << getOperation()->getResultTypes();
}


} // namespace circt::calyx
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::calyx::SgtLibOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::calyx::detail::SgtLibOpGenericAdaptorBase::Properties)

namespace circt::calyx {


//===----------------------------------------------------------------------===//
// ::circt::calyx::ShruLibOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

ShruLibOpGenericAdaptorBase::ShruLibOpGenericAdaptorBase(ShruLibOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::llvm::StringRef ShruLibOpGenericAdaptorBase::getSymName() {
  auto attr = getSymNameAttr();
  return attr.getValue();
}


} // namespace detail
ShruLibOpAdaptor::ShruLibOpAdaptor(ShruLibOp op) : ShruLibOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult ShruLibOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;
  if (!tblgen_sym_name) return emitError(loc, "'calyx.std_shru' op requires attribute 'sym_name'");

  if (tblgen_sym_name && !((::llvm::isa<::mlir::StringAttr>(tblgen_sym_name))))
    return emitError(loc, "'calyx.std_shru' op attribute 'sym_name' failed to satisfy constraint: string attribute");
  return ::mlir::success();
}

::llvm::LogicalResult ShruLibOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
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

::mlir::Attribute ShruLibOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
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

llvm::hash_code ShruLibOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.sym_name.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> ShruLibOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "sym_name")
      return prop.sym_name;
  return std::nullopt;
}

void ShruLibOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "sym_name") {
       prop.sym_name = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.sym_name)>>(value);
       return;
    }
}

void ShruLibOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.sym_name) attrs.append("sym_name", prop.sym_name);
}

::llvm::LogicalResult ShruLibOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getSymNameAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Calyx1(attr, "sym_name", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult ShruLibOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.sym_name)))
    return ::mlir::failure();
  return ::mlir::success();
}

void ShruLibOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.sym_name);
}

::llvm::StringRef ShruLibOp::getSymName() {
  auto attr = getSymNameAttr();
  return attr.getValue();
}

void ShruLibOp::setSymName(::llvm::StringRef attrValue) {
  getProperties().sym_name = ::mlir::Builder((*this)->getContext()).getStringAttr(attrValue);
}

void ShruLibOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, StringRef sym_name, ::mlir::TypeRange resultTypes) {
      odsState.addAttribute(mlir::SymbolTable::getSymbolAttrName(), odsBuilder.getStringAttr(sym_name));
      odsState.addTypes(resultTypes);
    
}

ShruLibOp ShruLibOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, StringRef sym_name, ::mlir::TypeRange resultTypes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(resultTypes)>(resultTypes));
  auto __res__ = ::llvm::dyn_cast<ShruLibOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ShruLibOp ShruLibOp::create(::mlir::ImplicitLocOpBuilder &builder, StringRef sym_name, ::mlir::TypeRange resultTypes) {
  return create(builder, builder.getLoc(), std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(resultTypes)>(resultTypes));
}

::llvm::LogicalResult ShruLibOp::verifyInvariantsImpl() {
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;
  if (!tblgen_sym_name) return emitOpError("requires attribute 'sym_name'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Calyx1(*this, tblgen_sym_name, "sym_name")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx5(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSResults(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx5(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup2 = getODSResults(2);

    for (auto v : valueGroup2) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx5(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  if (!((std::equal_to<>()( (*this->getODSResults(0).begin()).getType() , (*this->getODSResults(2).begin()).getType()))))
    return emitOpError("failed to verify that lhs and rhs types should be equivalent");
  if (!((std::equal_to<>()( (*this->getODSResults(0).begin()).getType() , (*this->getODSResults(1).begin()).getType()))))
    return emitOpError("failed to verify that lhs and rhs types should be equivalent");
  return ::mlir::success();
}

::llvm::LogicalResult ShruLibOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult ShruLibOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::StringAttr sym_nameAttr;
  ::llvm::SmallVector<::mlir::Type, 1> allResultTypes;

  if (parser.parseSymbolName(sym_nameAttr))
    return ::mlir::failure();
  if (sym_nameAttr) result.getOrAddProperties<ShruLibOp::Properties>().sym_name = sym_nameAttr;
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

  if (parser.parseTypeList(allResultTypes))
    return ::mlir::failure();
  result.addTypes(allResultTypes);
  return ::mlir::success();
}

void ShruLibOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter.printSymbolName(getSymNameAttr().getValue());
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("sym_name");
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
  _odsPrinter << getOperation()->getResultTypes();
}


} // namespace circt::calyx
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::calyx::ShruLibOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::calyx::detail::ShruLibOpGenericAdaptorBase::Properties)

namespace circt::calyx {


//===----------------------------------------------------------------------===//
// ::circt::calyx::SleLibOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

SleLibOpGenericAdaptorBase::SleLibOpGenericAdaptorBase(SleLibOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::llvm::StringRef SleLibOpGenericAdaptorBase::getSymName() {
  auto attr = getSymNameAttr();
  return attr.getValue();
}


} // namespace detail
SleLibOpAdaptor::SleLibOpAdaptor(SleLibOp op) : SleLibOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult SleLibOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;
  if (!tblgen_sym_name) return emitError(loc, "'calyx.std_sle' op requires attribute 'sym_name'");

  if (tblgen_sym_name && !((::llvm::isa<::mlir::StringAttr>(tblgen_sym_name))))
    return emitError(loc, "'calyx.std_sle' op attribute 'sym_name' failed to satisfy constraint: string attribute");
  return ::mlir::success();
}

::llvm::LogicalResult SleLibOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
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

::mlir::Attribute SleLibOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
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

llvm::hash_code SleLibOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.sym_name.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> SleLibOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "sym_name")
      return prop.sym_name;
  return std::nullopt;
}

void SleLibOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "sym_name") {
       prop.sym_name = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.sym_name)>>(value);
       return;
    }
}

void SleLibOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.sym_name) attrs.append("sym_name", prop.sym_name);
}

::llvm::LogicalResult SleLibOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getSymNameAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Calyx1(attr, "sym_name", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult SleLibOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.sym_name)))
    return ::mlir::failure();
  return ::mlir::success();
}

void SleLibOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.sym_name);
}

::llvm::StringRef SleLibOp::getSymName() {
  auto attr = getSymNameAttr();
  return attr.getValue();
}

void SleLibOp::setSymName(::llvm::StringRef attrValue) {
  getProperties().sym_name = ::mlir::Builder((*this)->getContext()).getStringAttr(attrValue);
}

void SleLibOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, StringRef sym_name, ::mlir::TypeRange resultTypes) {
      odsState.addAttribute(mlir::SymbolTable::getSymbolAttrName(), odsBuilder.getStringAttr(sym_name));
      odsState.addTypes(resultTypes);
    
}

SleLibOp SleLibOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, StringRef sym_name, ::mlir::TypeRange resultTypes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(resultTypes)>(resultTypes));
  auto __res__ = ::llvm::dyn_cast<SleLibOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SleLibOp SleLibOp::create(::mlir::ImplicitLocOpBuilder &builder, StringRef sym_name, ::mlir::TypeRange resultTypes) {
  return create(builder, builder.getLoc(), std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(resultTypes)>(resultTypes));
}

::llvm::LogicalResult SleLibOp::verifyInvariantsImpl() {
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;
  if (!tblgen_sym_name) return emitOpError("requires attribute 'sym_name'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Calyx1(*this, tblgen_sym_name, "sym_name")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx5(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSResults(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx5(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup2 = getODSResults(2);

    for (auto v : valueGroup2) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx1(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  if (!((std::equal_to<>()( (*this->getODSResults(0).begin()).getType() , (*this->getODSResults(1).begin()).getType()))))
    return emitOpError("failed to verify that lhs and rhs types should be equivalent");
  return ::mlir::success();
}

::llvm::LogicalResult SleLibOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult SleLibOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::StringAttr sym_nameAttr;
  ::llvm::SmallVector<::mlir::Type, 1> allResultTypes;

  if (parser.parseSymbolName(sym_nameAttr))
    return ::mlir::failure();
  if (sym_nameAttr) result.getOrAddProperties<SleLibOp::Properties>().sym_name = sym_nameAttr;
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

  if (parser.parseTypeList(allResultTypes))
    return ::mlir::failure();
  result.addTypes(allResultTypes);
  return ::mlir::success();
}

void SleLibOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter.printSymbolName(getSymNameAttr().getValue());
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("sym_name");
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
  _odsPrinter << getOperation()->getResultTypes();
}


} // namespace circt::calyx
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::calyx::SleLibOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::calyx::detail::SleLibOpGenericAdaptorBase::Properties)

namespace circt::calyx {


//===----------------------------------------------------------------------===//
// ::circt::calyx::SliceLibOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

SliceLibOpGenericAdaptorBase::SliceLibOpGenericAdaptorBase(SliceLibOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::llvm::StringRef SliceLibOpGenericAdaptorBase::getSymName() {
  auto attr = getSymNameAttr();
  return attr.getValue();
}


} // namespace detail
SliceLibOpAdaptor::SliceLibOpAdaptor(SliceLibOp op) : SliceLibOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult SliceLibOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;
  if (!tblgen_sym_name) return emitError(loc, "'calyx.std_slice' op requires attribute 'sym_name'");

  if (tblgen_sym_name && !((::llvm::isa<::mlir::StringAttr>(tblgen_sym_name))))
    return emitError(loc, "'calyx.std_slice' op attribute 'sym_name' failed to satisfy constraint: string attribute");
  return ::mlir::success();
}

::llvm::LogicalResult SliceLibOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
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

::mlir::Attribute SliceLibOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
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

llvm::hash_code SliceLibOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.sym_name.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> SliceLibOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "sym_name")
      return prop.sym_name;
  return std::nullopt;
}

void SliceLibOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "sym_name") {
       prop.sym_name = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.sym_name)>>(value);
       return;
    }
}

void SliceLibOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.sym_name) attrs.append("sym_name", prop.sym_name);
}

::llvm::LogicalResult SliceLibOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getSymNameAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Calyx1(attr, "sym_name", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult SliceLibOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.sym_name)))
    return ::mlir::failure();
  return ::mlir::success();
}

void SliceLibOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.sym_name);
}

::llvm::StringRef SliceLibOp::getSymName() {
  auto attr = getSymNameAttr();
  return attr.getValue();
}

void SliceLibOp::setSymName(::llvm::StringRef attrValue) {
  getProperties().sym_name = ::mlir::Builder((*this)->getContext()).getStringAttr(attrValue);
}

void SliceLibOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, StringRef sym_name, ::mlir::TypeRange resultTypes) {
      odsState.addAttribute(mlir::SymbolTable::getSymbolAttrName(), odsBuilder.getStringAttr(sym_name));
      odsState.addTypes(resultTypes);
    
}

SliceLibOp SliceLibOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, StringRef sym_name, ::mlir::TypeRange resultTypes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(resultTypes)>(resultTypes));
  auto __res__ = ::llvm::dyn_cast<SliceLibOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SliceLibOp SliceLibOp::create(::mlir::ImplicitLocOpBuilder &builder, StringRef sym_name, ::mlir::TypeRange resultTypes) {
  return create(builder, builder.getLoc(), std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(resultTypes)>(resultTypes));
}

::llvm::LogicalResult SliceLibOp::verifyInvariantsImpl() {
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;
  if (!tblgen_sym_name) return emitOpError("requires attribute 'sym_name'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Calyx1(*this, tblgen_sym_name, "sym_name")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx6(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSResults(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx6(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult SliceLibOp::verifyInvariants() {
  if(::mlir::succeeded(verifyInvariantsImpl()) && ::mlir::succeeded(verify()))
    return ::mlir::success();
  return ::mlir::failure();
}

::mlir::ParseResult SliceLibOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::StringAttr sym_nameAttr;
  ::llvm::SmallVector<::mlir::Type, 1> allResultTypes;

  if (parser.parseSymbolName(sym_nameAttr))
    return ::mlir::failure();
  if (sym_nameAttr) result.getOrAddProperties<SliceLibOp::Properties>().sym_name = sym_nameAttr;
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

  if (parser.parseTypeList(allResultTypes))
    return ::mlir::failure();
  result.addTypes(allResultTypes);
  return ::mlir::success();
}

void SliceLibOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter.printSymbolName(getSymNameAttr().getValue());
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("sym_name");
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
  _odsPrinter << getOperation()->getResultTypes();
}


} // namespace circt::calyx
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::calyx::SliceLibOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::calyx::detail::SliceLibOpGenericAdaptorBase::Properties)

namespace circt::calyx {


//===----------------------------------------------------------------------===//
// ::circt::calyx::SltLibOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

SltLibOpGenericAdaptorBase::SltLibOpGenericAdaptorBase(SltLibOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::llvm::StringRef SltLibOpGenericAdaptorBase::getSymName() {
  auto attr = getSymNameAttr();
  return attr.getValue();
}


} // namespace detail
SltLibOpAdaptor::SltLibOpAdaptor(SltLibOp op) : SltLibOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult SltLibOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;
  if (!tblgen_sym_name) return emitError(loc, "'calyx.std_slt' op requires attribute 'sym_name'");

  if (tblgen_sym_name && !((::llvm::isa<::mlir::StringAttr>(tblgen_sym_name))))
    return emitError(loc, "'calyx.std_slt' op attribute 'sym_name' failed to satisfy constraint: string attribute");
  return ::mlir::success();
}

::llvm::LogicalResult SltLibOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
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

::mlir::Attribute SltLibOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
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

llvm::hash_code SltLibOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.sym_name.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> SltLibOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "sym_name")
      return prop.sym_name;
  return std::nullopt;
}

void SltLibOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "sym_name") {
       prop.sym_name = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.sym_name)>>(value);
       return;
    }
}

void SltLibOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.sym_name) attrs.append("sym_name", prop.sym_name);
}

::llvm::LogicalResult SltLibOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getSymNameAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Calyx1(attr, "sym_name", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult SltLibOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.sym_name)))
    return ::mlir::failure();
  return ::mlir::success();
}

void SltLibOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.sym_name);
}

::llvm::StringRef SltLibOp::getSymName() {
  auto attr = getSymNameAttr();
  return attr.getValue();
}

void SltLibOp::setSymName(::llvm::StringRef attrValue) {
  getProperties().sym_name = ::mlir::Builder((*this)->getContext()).getStringAttr(attrValue);
}

void SltLibOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, StringRef sym_name, ::mlir::TypeRange resultTypes) {
      odsState.addAttribute(mlir::SymbolTable::getSymbolAttrName(), odsBuilder.getStringAttr(sym_name));
      odsState.addTypes(resultTypes);
    
}

SltLibOp SltLibOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, StringRef sym_name, ::mlir::TypeRange resultTypes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(resultTypes)>(resultTypes));
  auto __res__ = ::llvm::dyn_cast<SltLibOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SltLibOp SltLibOp::create(::mlir::ImplicitLocOpBuilder &builder, StringRef sym_name, ::mlir::TypeRange resultTypes) {
  return create(builder, builder.getLoc(), std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(resultTypes)>(resultTypes));
}

::llvm::LogicalResult SltLibOp::verifyInvariantsImpl() {
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;
  if (!tblgen_sym_name) return emitOpError("requires attribute 'sym_name'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Calyx1(*this, tblgen_sym_name, "sym_name")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx5(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSResults(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx5(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup2 = getODSResults(2);

    for (auto v : valueGroup2) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx1(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  if (!((std::equal_to<>()( (*this->getODSResults(0).begin()).getType() , (*this->getODSResults(1).begin()).getType()))))
    return emitOpError("failed to verify that lhs and rhs types should be equivalent");
  return ::mlir::success();
}

::llvm::LogicalResult SltLibOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult SltLibOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::StringAttr sym_nameAttr;
  ::llvm::SmallVector<::mlir::Type, 1> allResultTypes;

  if (parser.parseSymbolName(sym_nameAttr))
    return ::mlir::failure();
  if (sym_nameAttr) result.getOrAddProperties<SltLibOp::Properties>().sym_name = sym_nameAttr;
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

  if (parser.parseTypeList(allResultTypes))
    return ::mlir::failure();
  result.addTypes(allResultTypes);
  return ::mlir::success();
}

void SltLibOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter.printSymbolName(getSymNameAttr().getValue());
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("sym_name");
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
  _odsPrinter << getOperation()->getResultTypes();
}


} // namespace circt::calyx
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::calyx::SltLibOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::calyx::detail::SltLibOpGenericAdaptorBase::Properties)

namespace circt::calyx {


//===----------------------------------------------------------------------===//
// ::circt::calyx::SneqLibOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

SneqLibOpGenericAdaptorBase::SneqLibOpGenericAdaptorBase(SneqLibOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::llvm::StringRef SneqLibOpGenericAdaptorBase::getSymName() {
  auto attr = getSymNameAttr();
  return attr.getValue();
}


} // namespace detail
SneqLibOpAdaptor::SneqLibOpAdaptor(SneqLibOp op) : SneqLibOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult SneqLibOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;
  if (!tblgen_sym_name) return emitError(loc, "'calyx.std_sneq' op requires attribute 'sym_name'");

  if (tblgen_sym_name && !((::llvm::isa<::mlir::StringAttr>(tblgen_sym_name))))
    return emitError(loc, "'calyx.std_sneq' op attribute 'sym_name' failed to satisfy constraint: string attribute");
  return ::mlir::success();
}

::llvm::LogicalResult SneqLibOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
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

::mlir::Attribute SneqLibOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
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

llvm::hash_code SneqLibOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.sym_name.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> SneqLibOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "sym_name")
      return prop.sym_name;
  return std::nullopt;
}

void SneqLibOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "sym_name") {
       prop.sym_name = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.sym_name)>>(value);
       return;
    }
}

void SneqLibOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.sym_name) attrs.append("sym_name", prop.sym_name);
}

::llvm::LogicalResult SneqLibOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getSymNameAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Calyx1(attr, "sym_name", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult SneqLibOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.sym_name)))
    return ::mlir::failure();
  return ::mlir::success();
}

void SneqLibOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.sym_name);
}

::llvm::StringRef SneqLibOp::getSymName() {
  auto attr = getSymNameAttr();
  return attr.getValue();
}

void SneqLibOp::setSymName(::llvm::StringRef attrValue) {
  getProperties().sym_name = ::mlir::Builder((*this)->getContext()).getStringAttr(attrValue);
}

void SneqLibOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, StringRef sym_name, ::mlir::TypeRange resultTypes) {
      odsState.addAttribute(mlir::SymbolTable::getSymbolAttrName(), odsBuilder.getStringAttr(sym_name));
      odsState.addTypes(resultTypes);
    
}

SneqLibOp SneqLibOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, StringRef sym_name, ::mlir::TypeRange resultTypes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(resultTypes)>(resultTypes));
  auto __res__ = ::llvm::dyn_cast<SneqLibOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SneqLibOp SneqLibOp::create(::mlir::ImplicitLocOpBuilder &builder, StringRef sym_name, ::mlir::TypeRange resultTypes) {
  return create(builder, builder.getLoc(), std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(resultTypes)>(resultTypes));
}

::llvm::LogicalResult SneqLibOp::verifyInvariantsImpl() {
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;
  if (!tblgen_sym_name) return emitOpError("requires attribute 'sym_name'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Calyx1(*this, tblgen_sym_name, "sym_name")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx5(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSResults(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx5(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup2 = getODSResults(2);

    for (auto v : valueGroup2) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx1(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  if (!((std::equal_to<>()( (*this->getODSResults(0).begin()).getType() , (*this->getODSResults(1).begin()).getType()))))
    return emitOpError("failed to verify that lhs and rhs types should be equivalent");
  return ::mlir::success();
}

::llvm::LogicalResult SneqLibOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult SneqLibOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::StringAttr sym_nameAttr;
  ::llvm::SmallVector<::mlir::Type, 1> allResultTypes;

  if (parser.parseSymbolName(sym_nameAttr))
    return ::mlir::failure();
  if (sym_nameAttr) result.getOrAddProperties<SneqLibOp::Properties>().sym_name = sym_nameAttr;
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

  if (parser.parseTypeList(allResultTypes))
    return ::mlir::failure();
  result.addTypes(allResultTypes);
  return ::mlir::success();
}

void SneqLibOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter.printSymbolName(getSymNameAttr().getValue());
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("sym_name");
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
  _odsPrinter << getOperation()->getResultTypes();
}


} // namespace circt::calyx
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::calyx::SneqLibOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::calyx::detail::SneqLibOpGenericAdaptorBase::Properties)

namespace circt::calyx {


//===----------------------------------------------------------------------===//
// ::circt::calyx::SrshLibOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

SrshLibOpGenericAdaptorBase::SrshLibOpGenericAdaptorBase(SrshLibOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::llvm::StringRef SrshLibOpGenericAdaptorBase::getSymName() {
  auto attr = getSymNameAttr();
  return attr.getValue();
}


} // namespace detail
SrshLibOpAdaptor::SrshLibOpAdaptor(SrshLibOp op) : SrshLibOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult SrshLibOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;
  if (!tblgen_sym_name) return emitError(loc, "'calyx.std_srsh' op requires attribute 'sym_name'");

  if (tblgen_sym_name && !((::llvm::isa<::mlir::StringAttr>(tblgen_sym_name))))
    return emitError(loc, "'calyx.std_srsh' op attribute 'sym_name' failed to satisfy constraint: string attribute");
  return ::mlir::success();
}

::llvm::LogicalResult SrshLibOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
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

::mlir::Attribute SrshLibOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
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

llvm::hash_code SrshLibOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.sym_name.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> SrshLibOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "sym_name")
      return prop.sym_name;
  return std::nullopt;
}

void SrshLibOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "sym_name") {
       prop.sym_name = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.sym_name)>>(value);
       return;
    }
}

void SrshLibOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.sym_name) attrs.append("sym_name", prop.sym_name);
}

::llvm::LogicalResult SrshLibOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getSymNameAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Calyx1(attr, "sym_name", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult SrshLibOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.sym_name)))
    return ::mlir::failure();
  return ::mlir::success();
}

void SrshLibOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.sym_name);
}

::llvm::StringRef SrshLibOp::getSymName() {
  auto attr = getSymNameAttr();
  return attr.getValue();
}

void SrshLibOp::setSymName(::llvm::StringRef attrValue) {
  getProperties().sym_name = ::mlir::Builder((*this)->getContext()).getStringAttr(attrValue);
}

void SrshLibOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, StringRef sym_name, ::mlir::TypeRange resultTypes) {
      odsState.addAttribute(mlir::SymbolTable::getSymbolAttrName(), odsBuilder.getStringAttr(sym_name));
      odsState.addTypes(resultTypes);
    
}

SrshLibOp SrshLibOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, StringRef sym_name, ::mlir::TypeRange resultTypes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(resultTypes)>(resultTypes));
  auto __res__ = ::llvm::dyn_cast<SrshLibOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SrshLibOp SrshLibOp::create(::mlir::ImplicitLocOpBuilder &builder, StringRef sym_name, ::mlir::TypeRange resultTypes) {
  return create(builder, builder.getLoc(), std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(resultTypes)>(resultTypes));
}

::llvm::LogicalResult SrshLibOp::verifyInvariantsImpl() {
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;
  if (!tblgen_sym_name) return emitOpError("requires attribute 'sym_name'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Calyx1(*this, tblgen_sym_name, "sym_name")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx5(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSResults(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx5(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup2 = getODSResults(2);

    for (auto v : valueGroup2) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx5(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  if (!((std::equal_to<>()( (*this->getODSResults(0).begin()).getType() , (*this->getODSResults(2).begin()).getType()))))
    return emitOpError("failed to verify that lhs and rhs types should be equivalent");
  if (!((std::equal_to<>()( (*this->getODSResults(0).begin()).getType() , (*this->getODSResults(1).begin()).getType()))))
    return emitOpError("failed to verify that lhs and rhs types should be equivalent");
  return ::mlir::success();
}

::llvm::LogicalResult SrshLibOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult SrshLibOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::StringAttr sym_nameAttr;
  ::llvm::SmallVector<::mlir::Type, 1> allResultTypes;

  if (parser.parseSymbolName(sym_nameAttr))
    return ::mlir::failure();
  if (sym_nameAttr) result.getOrAddProperties<SrshLibOp::Properties>().sym_name = sym_nameAttr;
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

  if (parser.parseTypeList(allResultTypes))
    return ::mlir::failure();
  result.addTypes(allResultTypes);
  return ::mlir::success();
}

void SrshLibOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter.printSymbolName(getSymNameAttr().getValue());
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("sym_name");
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
  _odsPrinter << getOperation()->getResultTypes();
}


} // namespace circt::calyx
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::calyx::SrshLibOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::calyx::detail::SrshLibOpGenericAdaptorBase::Properties)

namespace circt::calyx {


//===----------------------------------------------------------------------===//
// ::circt::calyx::StaticGroupOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

StaticGroupOpGenericAdaptorBase::StaticGroupOpGenericAdaptorBase(StaticGroupOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::llvm::StringRef StaticGroupOpGenericAdaptorBase::getSymName() {
  auto attr = getSymNameAttr();
  return attr.getValue();
}

uint64_t StaticGroupOpGenericAdaptorBase::getLatency() {
  auto attr = getLatencyAttr();
  return attr.getValue().getZExtValue();
}


} // namespace detail
StaticGroupOpAdaptor::StaticGroupOpAdaptor(StaticGroupOp op) : StaticGroupOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult StaticGroupOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_latency = getProperties().latency; (void)tblgen_latency;
  if (!tblgen_latency) return emitError(loc, "'calyx.static_group' op requires attribute 'latency'");
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;
  if (!tblgen_sym_name) return emitError(loc, "'calyx.static_group' op requires attribute 'sym_name'");

  if (tblgen_sym_name && !((::llvm::isa<::mlir::StringAttr>(tblgen_sym_name))))
    return emitError(loc, "'calyx.static_group' op attribute 'sym_name' failed to satisfy constraint: string attribute");

  if (tblgen_latency && !(((::llvm::isa<::mlir::IntegerAttr>(tblgen_latency))) && ((::llvm::cast<::mlir::IntegerAttr>(tblgen_latency).getType().isSignlessInteger(64)))))
    return emitError(loc, "'calyx.static_group' op attribute 'latency' failed to satisfy constraint: 64-bit signless integer attribute");
  return ::mlir::success();
}

::llvm::LogicalResult StaticGroupOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
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

::mlir::Attribute StaticGroupOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.latency;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("latency",
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

llvm::hash_code StaticGroupOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.latency.getAsOpaquePointer()), 
    llvm::hash_value(prop.sym_name.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> StaticGroupOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "latency")
      return prop.latency;

    if (name == "sym_name")
      return prop.sym_name;
  return std::nullopt;
}

void StaticGroupOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "latency") {
       prop.latency = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.latency)>>(value);
       return;
    }

    if (name == "sym_name") {
       prop.sym_name = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.sym_name)>>(value);
       return;
    }
}

void StaticGroupOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.latency) attrs.append("latency", prop.latency);

    if (prop.sym_name) attrs.append("sym_name", prop.sym_name);
}

::llvm::LogicalResult StaticGroupOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getLatencyAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Calyx9(attr, "latency", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getSymNameAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Calyx1(attr, "sym_name", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult StaticGroupOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.latency)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readAttribute(prop.sym_name)))
    return ::mlir::failure();
  return ::mlir::success();
}

void StaticGroupOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.latency);
  writer.writeAttribute(prop.sym_name);
}

::llvm::StringRef StaticGroupOp::getSymName() {
  auto attr = getSymNameAttr();
  return attr.getValue();
}

uint64_t StaticGroupOp::getLatency() {
  auto attr = getLatencyAttr();
  return attr.getValue().getZExtValue();
}

void StaticGroupOp::setSymName(::llvm::StringRef attrValue) {
  getProperties().sym_name = ::mlir::Builder((*this)->getContext()).getStringAttr(attrValue);
}

void StaticGroupOp::setLatency(uint64_t attrValue) {
  getProperties().latency = ::mlir::Builder((*this)->getContext()).getIntegerAttr(::mlir::Builder((*this)->getContext()).getIntegerType(64), attrValue);
}

void StaticGroupOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, StringRef sym_name, uint64_t latency) {
      odsState.addAttribute(
        mlir::SymbolTable::getSymbolAttrName(),
        StringAttr::get(odsState.getContext(), sym_name)
      );
      odsState.addAttribute(
        getLatencyAttrName(odsState.name),
        mlir::IntegerAttr::get(IntegerType::get(odsState.getContext(), 64), latency)
      );
      Region* region = odsState.addRegion();
      region->push_back(new Block());
    
}

StaticGroupOp StaticGroupOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, StringRef sym_name, uint64_t latency) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(latency)>(latency));
  auto __res__ = ::llvm::dyn_cast<StaticGroupOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

StaticGroupOp StaticGroupOp::create(::mlir::ImplicitLocOpBuilder &builder, StringRef sym_name, uint64_t latency) {
  return create(builder, builder.getLoc(), std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(latency)>(latency));
}

void StaticGroupOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, StringAttr sym_name, uint64_t latency) {
      odsState.addAttribute(mlir::SymbolTable::getSymbolAttrName(), sym_name);
      odsState.addAttribute(
        getLatencyAttrName(odsState.name),
        mlir::IntegerAttr::get(IntegerType::get(odsState.getContext(), 64), latency)
      );
      Region* region = odsState.addRegion();
      region->push_back(new Block());
    
}

StaticGroupOp StaticGroupOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, StringAttr sym_name, uint64_t latency) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(latency)>(latency));
  auto __res__ = ::llvm::dyn_cast<StaticGroupOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

StaticGroupOp StaticGroupOp::create(::mlir::ImplicitLocOpBuilder &builder, StringAttr sym_name, uint64_t latency) {
  return create(builder, builder.getLoc(), std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(latency)>(latency));
}

::llvm::LogicalResult StaticGroupOp::verifyInvariantsImpl() {
  auto tblgen_latency = getProperties().latency; (void)tblgen_latency;
  if (!tblgen_latency) return emitOpError("requires attribute 'latency'");
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;
  if (!tblgen_sym_name) return emitOpError("requires attribute 'sym_name'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Calyx1(*this, tblgen_sym_name, "sym_name")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Calyx9(*this, tblgen_latency, "latency")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;

    for (auto &region : ::llvm::MutableArrayRef((*this)->getRegion(0)))
      if (::mlir::failed(__mlir_ods_local_region_constraint_Calyx1(*this, region, "body", index++)))
        return ::mlir::failure();
  }
  return ::mlir::success();
}

::llvm::LogicalResult StaticGroupOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult StaticGroupOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::IntegerAttr latencyAttr;
  ::mlir::StringAttr sym_nameAttr;
  std::unique_ptr<::mlir::Region> bodyRegion = std::make_unique<::mlir::Region>();
  if (parser.parseKeyword("latency"))
    return ::mlir::failure();
  if (parser.parseLess())
    return ::mlir::failure();

  if (parser.parseCustomAttributeWithFallback(latencyAttr, parser.getBuilder().getIntegerType(64))) {
    return ::mlir::failure();
  }
  if (latencyAttr) result.getOrAddProperties<StaticGroupOp::Properties>().latency = latencyAttr;
  if (parser.parseGreater())
    return ::mlir::failure();

  if (parser.parseSymbolName(sym_nameAttr))
    return ::mlir::failure();
  if (sym_nameAttr) result.getOrAddProperties<StaticGroupOp::Properties>().sym_name = sym_nameAttr;

  if (parser.parseRegion(*bodyRegion))
    return ::mlir::failure();

  if (bodyRegion->empty()) bodyRegion->emplaceBlock();
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
  return ::mlir::success();
}

void StaticGroupOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ' << "latency";
  _odsPrinter << "<";
  _odsPrinter.printAttributeWithoutType(getLatencyAttr());
  _odsPrinter << ">";
  _odsPrinter << ' ';
  _odsPrinter.printSymbolName(getSymNameAttr().getValue());
  _odsPrinter << ' ';
  _odsPrinter.printRegion(getBody());
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("latency");
  elidedAttrs.push_back("sym_name");
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
}


} // namespace circt::calyx
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::calyx::StaticGroupOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::calyx::detail::StaticGroupOpGenericAdaptorBase::Properties)

namespace circt::calyx {


//===----------------------------------------------------------------------===//
// ::circt::calyx::StaticIfOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

StaticIfOpGenericAdaptorBase::StaticIfOpGenericAdaptorBase(StaticIfOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}


} // namespace detail
StaticIfOpAdaptor::StaticIfOpAdaptor(StaticIfOp op) : StaticIfOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult StaticIfOpAdaptor::verify(::mlir::Location loc) {
  return ::mlir::success();
}

::llvm::LogicalResult StaticIfOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }
      return ::mlir::success();
}

::mlir::Attribute StaticIfOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code StaticIfOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine();
}

std::optional<mlir::Attribute> StaticIfOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
  return std::nullopt;
}

void StaticIfOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
}

void StaticIfOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
}

::llvm::LogicalResult StaticIfOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    return ::mlir::success();
}

void StaticIfOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value cond, bool initializeElseBody) {
        odsState.addOperands(cond);

        Region *thenRegion = odsState.addRegion();
        Region *elseRegion = odsState.addRegion();
        thenRegion->push_back(new Block());
        if (initializeElseBody)
          elseRegion->push_back(new Block());
    
}

StaticIfOp StaticIfOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, Value cond, bool initializeElseBody) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(cond)>(cond), std::forward<decltype(initializeElseBody)>(initializeElseBody));
  auto __res__ = ::llvm::dyn_cast<StaticIfOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

StaticIfOp StaticIfOp::create(::mlir::ImplicitLocOpBuilder &builder, Value cond, bool initializeElseBody) {
  return create(builder, builder.getLoc(), std::forward<decltype(cond)>(cond), std::forward<decltype(initializeElseBody)>(initializeElseBody));
}

::llvm::LogicalResult StaticIfOp::verifyInvariantsImpl() {
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;

    for (auto &region : ::llvm::MutableArrayRef((*this)->getRegion(0)))
      if (::mlir::failed(__mlir_ods_local_region_constraint_Calyx1(*this, region, "thenRegion", index++)))
        return ::mlir::failure();

    for (auto &region : ::llvm::MutableArrayRef((*this)->getRegion(1)))
      if (::mlir::failed(__mlir_ods_local_region_constraint_Calyx2(*this, region, "elseRegion", index++)))
        return ::mlir::failure();
  }
  return ::mlir::success();
}

::llvm::LogicalResult StaticIfOp::verifyInvariants() {
  if(::mlir::succeeded(verifyInvariantsImpl()) && ::mlir::succeeded(verify()))
    return ::mlir::success();
  return ::mlir::failure();
}

::mlir::ParseResult StaticIfOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::OpAsmParser::UnresolvedOperand condRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> condOperands(&condRawOperand, 1);  ::llvm::SMLoc condOperandsLoc;
  (void)condOperandsLoc;
  std::unique_ptr<::mlir::Region> thenRegionRegion = std::make_unique<::mlir::Region>();
  std::unique_ptr<::mlir::Region> elseRegionRegion = std::make_unique<::mlir::Region>();

  condOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(condRawOperand))
    return ::mlir::failure();

  if (parser.parseRegion(*thenRegionRegion))
    return ::mlir::failure();

  if (thenRegionRegion->empty()) thenRegionRegion->emplaceBlock();
  if (::mlir::succeeded(parser.parseOptionalKeyword("else"))) {

  if (parser.parseRegion(*elseRegionRegion))
    return ::mlir::failure();

  if (elseRegionRegion->empty()) elseRegionRegion->emplaceBlock();
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
  result.addRegion(std::move(thenRegionRegion));
  result.addRegion(std::move(elseRegionRegion));
  ::mlir::Type odsBuildableType0 = parser.getBuilder().getIntegerType(1);
  if (parser.resolveOperands(condOperands, odsBuildableType0, condOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void StaticIfOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter << getCond();
  _odsPrinter << ' ';
  _odsPrinter.printRegion(getThenRegion());
  if (!getElseRegion().empty()) {
    _odsPrinter << ' ' << "else";
    _odsPrinter << ' ';
    _odsPrinter.printRegion(getElseRegion());
  }
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
}


} // namespace circt::calyx
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::calyx::StaticIfOp)

namespace circt::calyx {


//===----------------------------------------------------------------------===//
// ::circt::calyx::StaticParOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

StaticParOpGenericAdaptorBase::StaticParOpGenericAdaptorBase(StaticParOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}


} // namespace detail
StaticParOpAdaptor::StaticParOpAdaptor(StaticParOp op) : StaticParOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult StaticParOpAdaptor::verify(::mlir::Location loc) {
  return ::mlir::success();
}

::llvm::LogicalResult StaticParOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }
      return ::mlir::success();
}

::mlir::Attribute StaticParOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code StaticParOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine();
}

std::optional<mlir::Attribute> StaticParOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
  return std::nullopt;
}

void StaticParOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
}

void StaticParOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
}

::llvm::LogicalResult StaticParOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    return ::mlir::success();
}

void StaticParOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState) {
      Region* region = odsState.addRegion();
      region->push_back(new Block());
    
}

StaticParOp StaticParOp::create(::mlir::OpBuilder &builder, ::mlir::Location location) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__);
  auto __res__ = ::llvm::dyn_cast<StaticParOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

StaticParOp StaticParOp::create(::mlir::ImplicitLocOpBuilder &builder) {
  return create(builder, builder.getLoc());
}

::llvm::LogicalResult StaticParOp::verifyInvariantsImpl() {
  {
    unsigned index = 0; (void)index;

    for (auto &region : ::llvm::MutableArrayRef((*this)->getRegion(0)))
      if (::mlir::failed(__mlir_ods_local_region_constraint_Calyx1(*this, region, "body", index++)))
        return ::mlir::failure();
  }
  return ::mlir::success();
}

::llvm::LogicalResult StaticParOp::verifyInvariants() {
  if(::mlir::succeeded(verifyInvariantsImpl()) && ::mlir::succeeded(verify()))
    return ::mlir::success();
  return ::mlir::failure();
}

::mlir::ParseResult StaticParOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  std::unique_ptr<::mlir::Region> bodyRegion = std::make_unique<::mlir::Region>();

  if (parser.parseRegion(*bodyRegion))
    return ::mlir::failure();

  if (bodyRegion->empty()) bodyRegion->emplaceBlock();
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
  return ::mlir::success();
}

void StaticParOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter.printRegion(getBody());
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
}


} // namespace circt::calyx
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::calyx::StaticParOp)

namespace circt::calyx {


//===----------------------------------------------------------------------===//
// ::circt::calyx::StaticRepeatOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

StaticRepeatOpGenericAdaptorBase::StaticRepeatOpGenericAdaptorBase(StaticRepeatOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

uint32_t StaticRepeatOpGenericAdaptorBase::getCount() {
  auto attr = getCountAttr();
  return attr.getValue().getZExtValue();
}


} // namespace detail
StaticRepeatOpAdaptor::StaticRepeatOpAdaptor(StaticRepeatOp op) : StaticRepeatOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult StaticRepeatOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_count = getProperties().count; (void)tblgen_count;
  if (!tblgen_count) return emitError(loc, "'calyx.static_repeat' op requires attribute 'count'");

  if (tblgen_count && !(((::llvm::isa<::mlir::IntegerAttr>(tblgen_count))) && ((::llvm::cast<::mlir::IntegerAttr>(tblgen_count).getType().isSignlessInteger(32)))))
    return emitError(loc, "'calyx.static_repeat' op attribute 'count' failed to satisfy constraint: 32-bit signless integer attribute");
  return ::mlir::success();
}

::llvm::LogicalResult StaticRepeatOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.count;
       auto attr = dict.get("count");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `count` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  return ::mlir::success();
}

::mlir::Attribute StaticRepeatOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.count;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("count",
                                       propStorage));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code StaticRepeatOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.count.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> StaticRepeatOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "count")
      return prop.count;
  return std::nullopt;
}

void StaticRepeatOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "count") {
       prop.count = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.count)>>(value);
       return;
    }
}

void StaticRepeatOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.count) attrs.append("count", prop.count);
}

::llvm::LogicalResult StaticRepeatOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getCountAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Calyx7(attr, "count", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult StaticRepeatOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.count)))
    return ::mlir::failure();
  return ::mlir::success();
}

void StaticRepeatOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.count);
}

uint32_t StaticRepeatOp::getCount() {
  auto attr = getCountAttr();
  return attr.getValue().getZExtValue();
}

void StaticRepeatOp::setCount(uint32_t attrValue) {
  getProperties().count = ::mlir::Builder((*this)->getContext()).getIntegerAttr(::mlir::Builder((*this)->getContext()).getIntegerType(32), attrValue);
}

void StaticRepeatOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, uint32_t count) {
        odsState.addAttribute("count", 
          mlir::IntegerAttr::get(IntegerType::get(odsState.getContext(), 32), count)
        );

        Region *body = odsState.addRegion();
        body->push_back(new Block());
    
}

StaticRepeatOp StaticRepeatOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, uint32_t count) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(count)>(count));
  auto __res__ = ::llvm::dyn_cast<StaticRepeatOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

StaticRepeatOp StaticRepeatOp::create(::mlir::ImplicitLocOpBuilder &builder, uint32_t count) {
  return create(builder, builder.getLoc(), std::forward<decltype(count)>(count));
}

::llvm::LogicalResult StaticRepeatOp::verifyInvariantsImpl() {
  auto tblgen_count = getProperties().count; (void)tblgen_count;
  if (!tblgen_count) return emitOpError("requires attribute 'count'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Calyx7(*this, tblgen_count, "count")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;

    for (auto &region : ::llvm::MutableArrayRef((*this)->getRegion(0)))
      if (::mlir::failed(__mlir_ods_local_region_constraint_Calyx1(*this, region, "body", index++)))
        return ::mlir::failure();
  }
  return ::mlir::success();
}

::llvm::LogicalResult StaticRepeatOp::verifyInvariants() {
  if(::mlir::succeeded(verifyInvariantsImpl()) && ::mlir::succeeded(verify()))
    return ::mlir::success();
  return ::mlir::failure();
}

::mlir::ParseResult StaticRepeatOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::IntegerAttr countAttr;
  std::unique_ptr<::mlir::Region> bodyRegion = std::make_unique<::mlir::Region>();

  if (parser.parseCustomAttributeWithFallback(countAttr, parser.getBuilder().getIntegerType(32))) {
    return ::mlir::failure();
  }
  if (countAttr) result.getOrAddProperties<StaticRepeatOp::Properties>().count = countAttr;

  if (parser.parseRegion(*bodyRegion))
    return ::mlir::failure();

  if (bodyRegion->empty()) bodyRegion->emplaceBlock();
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
  return ::mlir::success();
}

void StaticRepeatOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter.printAttributeWithoutType(getCountAttr());
  _odsPrinter << ' ';
  _odsPrinter.printRegion(getBody());
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("count");
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
}


} // namespace circt::calyx
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::calyx::StaticRepeatOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::calyx::detail::StaticRepeatOpGenericAdaptorBase::Properties)

namespace circt::calyx {


//===----------------------------------------------------------------------===//
// ::circt::calyx::StaticSeqOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

StaticSeqOpGenericAdaptorBase::StaticSeqOpGenericAdaptorBase(StaticSeqOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}


} // namespace detail
StaticSeqOpAdaptor::StaticSeqOpAdaptor(StaticSeqOp op) : StaticSeqOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult StaticSeqOpAdaptor::verify(::mlir::Location loc) {
  return ::mlir::success();
}

::llvm::LogicalResult StaticSeqOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }
      return ::mlir::success();
}

::mlir::Attribute StaticSeqOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code StaticSeqOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine();
}

std::optional<mlir::Attribute> StaticSeqOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
  return std::nullopt;
}

void StaticSeqOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
}

void StaticSeqOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
}

::llvm::LogicalResult StaticSeqOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    return ::mlir::success();
}

void StaticSeqOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState) {
      Region* region = odsState.addRegion();
      region->push_back(new Block());
    
}

StaticSeqOp StaticSeqOp::create(::mlir::OpBuilder &builder, ::mlir::Location location) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__);
  auto __res__ = ::llvm::dyn_cast<StaticSeqOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

StaticSeqOp StaticSeqOp::create(::mlir::ImplicitLocOpBuilder &builder) {
  return create(builder, builder.getLoc());
}

::llvm::LogicalResult StaticSeqOp::verifyInvariantsImpl() {
  {
    unsigned index = 0; (void)index;

    for (auto &region : ::llvm::MutableArrayRef((*this)->getRegion(0)))
      if (::mlir::failed(__mlir_ods_local_region_constraint_Calyx1(*this, region, "body", index++)))
        return ::mlir::failure();
  }
  return ::mlir::success();
}

::llvm::LogicalResult StaticSeqOp::verifyInvariants() {
  if(::mlir::succeeded(verifyInvariantsImpl()) && ::mlir::succeeded(verify()))
    return ::mlir::success();
  return ::mlir::failure();
}

::mlir::ParseResult StaticSeqOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  std::unique_ptr<::mlir::Region> bodyRegion = std::make_unique<::mlir::Region>();

  if (parser.parseRegion(*bodyRegion))
    return ::mlir::failure();

  if (bodyRegion->empty()) bodyRegion->emplaceBlock();
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
  return ::mlir::success();
}

void StaticSeqOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter.printRegion(getBody());
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
}


} // namespace circt::calyx
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::calyx::StaticSeqOp)

namespace circt::calyx {


//===----------------------------------------------------------------------===//
// ::circt::calyx::SubLibOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

SubLibOpGenericAdaptorBase::SubLibOpGenericAdaptorBase(SubLibOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::llvm::StringRef SubLibOpGenericAdaptorBase::getSymName() {
  auto attr = getSymNameAttr();
  return attr.getValue();
}


} // namespace detail
SubLibOpAdaptor::SubLibOpAdaptor(SubLibOp op) : SubLibOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult SubLibOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;
  if (!tblgen_sym_name) return emitError(loc, "'calyx.std_sub' op requires attribute 'sym_name'");

  if (tblgen_sym_name && !((::llvm::isa<::mlir::StringAttr>(tblgen_sym_name))))
    return emitError(loc, "'calyx.std_sub' op attribute 'sym_name' failed to satisfy constraint: string attribute");
  return ::mlir::success();
}

::llvm::LogicalResult SubLibOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
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

::mlir::Attribute SubLibOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
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

llvm::hash_code SubLibOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.sym_name.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> SubLibOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "sym_name")
      return prop.sym_name;
  return std::nullopt;
}

void SubLibOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "sym_name") {
       prop.sym_name = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.sym_name)>>(value);
       return;
    }
}

void SubLibOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.sym_name) attrs.append("sym_name", prop.sym_name);
}

::llvm::LogicalResult SubLibOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getSymNameAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Calyx1(attr, "sym_name", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult SubLibOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.sym_name)))
    return ::mlir::failure();
  return ::mlir::success();
}

void SubLibOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.sym_name);
}

::llvm::StringRef SubLibOp::getSymName() {
  auto attr = getSymNameAttr();
  return attr.getValue();
}

void SubLibOp::setSymName(::llvm::StringRef attrValue) {
  getProperties().sym_name = ::mlir::Builder((*this)->getContext()).getStringAttr(attrValue);
}

void SubLibOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, StringRef sym_name, ::mlir::TypeRange resultTypes) {
      odsState.addAttribute(mlir::SymbolTable::getSymbolAttrName(), odsBuilder.getStringAttr(sym_name));
      odsState.addTypes(resultTypes);
    
}

SubLibOp SubLibOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, StringRef sym_name, ::mlir::TypeRange resultTypes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(resultTypes)>(resultTypes));
  auto __res__ = ::llvm::dyn_cast<SubLibOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SubLibOp SubLibOp::create(::mlir::ImplicitLocOpBuilder &builder, StringRef sym_name, ::mlir::TypeRange resultTypes) {
  return create(builder, builder.getLoc(), std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(resultTypes)>(resultTypes));
}

::llvm::LogicalResult SubLibOp::verifyInvariantsImpl() {
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;
  if (!tblgen_sym_name) return emitOpError("requires attribute 'sym_name'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Calyx1(*this, tblgen_sym_name, "sym_name")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx5(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSResults(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx5(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup2 = getODSResults(2);

    for (auto v : valueGroup2) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx5(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  if (!((std::equal_to<>()( (*this->getODSResults(0).begin()).getType() , (*this->getODSResults(2).begin()).getType()))))
    return emitOpError("failed to verify that lhs and rhs types should be equivalent");
  if (!((std::equal_to<>()( (*this->getODSResults(0).begin()).getType() , (*this->getODSResults(1).begin()).getType()))))
    return emitOpError("failed to verify that lhs and rhs types should be equivalent");
  return ::mlir::success();
}

::llvm::LogicalResult SubLibOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult SubLibOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::StringAttr sym_nameAttr;
  ::llvm::SmallVector<::mlir::Type, 1> allResultTypes;

  if (parser.parseSymbolName(sym_nameAttr))
    return ::mlir::failure();
  if (sym_nameAttr) result.getOrAddProperties<SubLibOp::Properties>().sym_name = sym_nameAttr;
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

  if (parser.parseTypeList(allResultTypes))
    return ::mlir::failure();
  result.addTypes(allResultTypes);
  return ::mlir::success();
}

void SubLibOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter.printSymbolName(getSymNameAttr().getValue());
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("sym_name");
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
  _odsPrinter << getOperation()->getResultTypes();
}


} // namespace circt::calyx
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::calyx::SubLibOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::calyx::detail::SubLibOpGenericAdaptorBase::Properties)

namespace circt::calyx {


//===----------------------------------------------------------------------===//
// ::circt::calyx::UndefLibOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

UndefLibOpGenericAdaptorBase::UndefLibOpGenericAdaptorBase(UndefLibOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::llvm::StringRef UndefLibOpGenericAdaptorBase::getSymName() {
  auto attr = getSymNameAttr();
  return attr.getValue();
}


} // namespace detail
UndefLibOpAdaptor::UndefLibOpAdaptor(UndefLibOp op) : UndefLibOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult UndefLibOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;
  if (!tblgen_sym_name) return emitError(loc, "'calyx.undefined' op requires attribute 'sym_name'");

  if (tblgen_sym_name && !((::llvm::isa<::mlir::StringAttr>(tblgen_sym_name))))
    return emitError(loc, "'calyx.undefined' op attribute 'sym_name' failed to satisfy constraint: string attribute");
  return ::mlir::success();
}

::llvm::LogicalResult UndefLibOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
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

::mlir::Attribute UndefLibOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
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

llvm::hash_code UndefLibOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.sym_name.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> UndefLibOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "sym_name")
      return prop.sym_name;
  return std::nullopt;
}

void UndefLibOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "sym_name") {
       prop.sym_name = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.sym_name)>>(value);
       return;
    }
}

void UndefLibOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.sym_name) attrs.append("sym_name", prop.sym_name);
}

::llvm::LogicalResult UndefLibOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getSymNameAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Calyx1(attr, "sym_name", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult UndefLibOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.sym_name)))
    return ::mlir::failure();
  return ::mlir::success();
}

void UndefLibOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.sym_name);
}

::llvm::StringRef UndefLibOp::getSymName() {
  auto attr = getSymNameAttr();
  return attr.getValue();
}

void UndefLibOp::setSymName(::llvm::StringRef attrValue) {
  getProperties().sym_name = ::mlir::Builder((*this)->getContext()).getStringAttr(attrValue);
}

void UndefLibOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, StringRef sym_name, ::mlir::TypeRange resultTypes) {
      odsState.addAttribute(mlir::SymbolTable::getSymbolAttrName(), odsBuilder.getStringAttr(sym_name));
      odsState.addTypes(resultTypes);
    
}

UndefLibOp UndefLibOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, StringRef sym_name, ::mlir::TypeRange resultTypes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(resultTypes)>(resultTypes));
  auto __res__ = ::llvm::dyn_cast<UndefLibOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

UndefLibOp UndefLibOp::create(::mlir::ImplicitLocOpBuilder &builder, StringRef sym_name, ::mlir::TypeRange resultTypes) {
  return create(builder, builder.getLoc(), std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(resultTypes)>(resultTypes));
}

::llvm::LogicalResult UndefLibOp::verifyInvariantsImpl() {
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;
  if (!tblgen_sym_name) return emitOpError("requires attribute 'sym_name'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Calyx1(*this, tblgen_sym_name, "sym_name")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx5(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult UndefLibOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult UndefLibOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::StringAttr sym_nameAttr;
  ::llvm::SmallVector<::mlir::Type, 1> allResultTypes;

  if (parser.parseSymbolName(sym_nameAttr))
    return ::mlir::failure();
  if (sym_nameAttr) result.getOrAddProperties<UndefLibOp::Properties>().sym_name = sym_nameAttr;
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

  if (parser.parseTypeList(allResultTypes))
    return ::mlir::failure();
  result.addTypes(allResultTypes);
  return ::mlir::success();
}

void UndefLibOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter.printSymbolName(getSymNameAttr().getValue());
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("sym_name");
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
  _odsPrinter << getOperation()->getResultTypes();
}

bool UndefLibOp::isCombinational() { return false; }
SmallVector<StringRef> UndefLibOp::portNames() { return {"out"}; }
SmallVector<Direction> UndefLibOp::portDirections() { return {Output}; }
void UndefLibOp::getAsmResultNames(OpAsmSetValueNameFn setNameFn) {
  getCellAsmResultNames(setNameFn, *this, this->portNames());
}
SmallVector<DictionaryAttr> UndefLibOp::portAttributes() {
  return {DictionaryAttr::get(getContext())};
}

} // namespace circt::calyx
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::calyx::UndefLibOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::calyx::detail::UndefLibOpGenericAdaptorBase::Properties)

namespace circt::calyx {


//===----------------------------------------------------------------------===//
// ::circt::calyx::UndefinedOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

UndefinedOpGenericAdaptorBase::UndefinedOpGenericAdaptorBase(UndefinedOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}


} // namespace detail
UndefinedOpAdaptor::UndefinedOpAdaptor(UndefinedOp op) : UndefinedOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult UndefinedOpAdaptor::verify(::mlir::Location loc) {
  return ::mlir::success();
}

::llvm::LogicalResult UndefinedOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }
      return ::mlir::success();
}

::mlir::Attribute UndefinedOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code UndefinedOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine();
}

std::optional<mlir::Attribute> UndefinedOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
  return std::nullopt;
}

void UndefinedOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
}

void UndefinedOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
}

::llvm::LogicalResult UndefinedOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    return ::mlir::success();
}

void UndefinedOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type res) {
  odsState.addTypes(res);
}

UndefinedOp UndefinedOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type res) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(res)>(res));
  auto __res__ = ::llvm::dyn_cast<UndefinedOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

UndefinedOp UndefinedOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type res) {
  return create(builder, builder.getLoc(), std::forward<decltype(res)>(res));
}

void UndefinedOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes) {
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

UndefinedOp UndefinedOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes));
  auto __res__ = ::llvm::dyn_cast<UndefinedOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

UndefinedOp UndefinedOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes));
}

void UndefinedOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

UndefinedOp UndefinedOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<UndefinedOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

UndefinedOp UndefinedOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void UndefinedOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

UndefinedOp UndefinedOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<UndefinedOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

UndefinedOp UndefinedOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult UndefinedOp::verifyInvariantsImpl() {
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx5(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult UndefinedOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult UndefinedOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::Type resRawType{};
  ::llvm::ArrayRef<::mlir::Type> resTypes(&resRawType, 1);
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

  if (parser.parseType(resRawType))
    return ::mlir::failure();
  result.addTypes(resTypes);
  return ::mlir::success();
}

void UndefinedOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
   _odsPrinter << getRes().getType();
}

void UndefinedOp::getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects) {
}


} // namespace circt::calyx
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::calyx::UndefinedOp)

namespace circt::calyx {


//===----------------------------------------------------------------------===//
// ::circt::calyx::WhileOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

WhileOpGenericAdaptorBase::WhileOpGenericAdaptorBase(WhileOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::std::optional< ::llvm::StringRef > WhileOpGenericAdaptorBase::getGroupName() {
  auto attr = getGroupNameAttr();
  return attr ? ::std::optional< ::llvm::StringRef >(attr.getValue()) : (::std::nullopt);
}


} // namespace detail
WhileOpAdaptor::WhileOpAdaptor(WhileOp op) : WhileOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult WhileOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_groupName = getProperties().groupName; (void)tblgen_groupName;

  if (tblgen_groupName && !((::llvm::isa<::mlir::FlatSymbolRefAttr>(tblgen_groupName))))
    return emitError(loc, "'calyx.while' op attribute 'groupName' failed to satisfy constraint: flat symbol reference attribute");
  return ::mlir::success();
}

::llvm::LogicalResult WhileOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.groupName;
       auto attr = dict.get("groupName");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `groupName` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  return ::mlir::success();
}

::mlir::Attribute WhileOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.groupName;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("groupName",
                                       propStorage));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code WhileOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.groupName.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> WhileOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "groupName")
      return prop.groupName;
  return std::nullopt;
}

void WhileOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "groupName") {
       prop.groupName = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.groupName)>>(value);
       return;
    }
}

void WhileOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.groupName) attrs.append("groupName", prop.groupName);
}

::llvm::LogicalResult WhileOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getGroupNameAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Calyx8(attr, "groupName", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult WhileOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readOptionalAttribute(prop.groupName)))
    return ::mlir::failure();
  return ::mlir::success();
}

void WhileOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;

  writer.writeOptionalAttribute(prop.groupName);
}

::std::optional< ::llvm::StringRef > WhileOp::getGroupName() {
  auto attr = getGroupNameAttr();
  return attr ? ::std::optional< ::llvm::StringRef >(attr.getValue()) : (::std::nullopt);
}

void WhileOp::setGroupName(::std::optional<::llvm::StringRef> attrValue) {
    auto &odsProp = getProperties().groupName;
    if (attrValue)
      odsProp = ::mlir::SymbolRefAttr::get(::mlir::Builder((*this)->getContext()).getContext(), *attrValue);
    else
      odsProp = nullptr;
}

void WhileOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value cond, FlatSymbolRefAttr groupName) {
        odsState.addOperands(cond);
        if (groupName)
          odsState.addAttribute("groupName", groupName);

        Region *body = odsState.addRegion();
        body->push_back(new Block());
    
}

WhileOp WhileOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, Value cond, FlatSymbolRefAttr groupName) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(cond)>(cond), std::forward<decltype(groupName)>(groupName));
  auto __res__ = ::llvm::dyn_cast<WhileOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

WhileOp WhileOp::create(::mlir::ImplicitLocOpBuilder &builder, Value cond, FlatSymbolRefAttr groupName) {
  return create(builder, builder.getLoc(), std::forward<decltype(cond)>(cond), std::forward<decltype(groupName)>(groupName));
}

::llvm::LogicalResult WhileOp::verifyInvariantsImpl() {
  auto tblgen_groupName = getProperties().groupName; (void)tblgen_groupName;

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Calyx8(*this, tblgen_groupName, "groupName")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;

    for (auto &region : ::llvm::MutableArrayRef((*this)->getRegion(0)))
      if (::mlir::failed(__mlir_ods_local_region_constraint_Calyx1(*this, region, "body", index++)))
        return ::mlir::failure();
  }
  return ::mlir::success();
}

::llvm::LogicalResult WhileOp::verifyInvariants() {
  if(::mlir::succeeded(verifyInvariantsImpl()) && ::mlir::succeeded(verify()))
    return ::mlir::success();
  return ::mlir::failure();
}

void WhileOp::getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context) {
  results.add(canonicalize);
}

::mlir::ParseResult WhileOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::OpAsmParser::UnresolvedOperand condRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> condOperands(&condRawOperand, 1);  ::llvm::SMLoc condOperandsLoc;
  (void)condOperandsLoc;
  ::mlir::FlatSymbolRefAttr groupNameAttr;
  std::unique_ptr<::mlir::Region> bodyRegion = std::make_unique<::mlir::Region>();

  condOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(condRawOperand))
    return ::mlir::failure();
  if (::mlir::succeeded(parser.parseOptionalKeyword("with"))) {

  if (parser.parseCustomAttributeWithFallback(groupNameAttr, parser.getBuilder().getType<::mlir::NoneType>())) {
    return ::mlir::failure();
  }
  if (groupNameAttr) result.getOrAddProperties<WhileOp::Properties>().groupName = groupNameAttr;
  }

  if (parser.parseRegion(*bodyRegion))
    return ::mlir::failure();

  if (bodyRegion->empty()) bodyRegion->emplaceBlock();
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
  ::mlir::Type odsBuildableType0 = parser.getBuilder().getIntegerType(1);
  if (parser.resolveOperands(condOperands, odsBuildableType0, condOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void WhileOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter << getCond();
  if (getGroupNameAttr()) {
    _odsPrinter << ' ' << "with";
    _odsPrinter << ' ';
    _odsPrinter.printAttributeWithoutType(getGroupNameAttr());
  }
  _odsPrinter << ' ';
  _odsPrinter.printRegion(getBody());
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("groupName");
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
}


} // namespace circt::calyx
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::calyx::WhileOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::calyx::detail::WhileOpGenericAdaptorBase::Properties)

namespace circt::calyx {


//===----------------------------------------------------------------------===//
// ::circt::calyx::WireLibOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

WireLibOpGenericAdaptorBase::WireLibOpGenericAdaptorBase(WireLibOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::llvm::StringRef WireLibOpGenericAdaptorBase::getSymName() {
  auto attr = getSymNameAttr();
  return attr.getValue();
}


} // namespace detail
WireLibOpAdaptor::WireLibOpAdaptor(WireLibOp op) : WireLibOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult WireLibOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;
  if (!tblgen_sym_name) return emitError(loc, "'calyx.std_wire' op requires attribute 'sym_name'");

  if (tblgen_sym_name && !((::llvm::isa<::mlir::StringAttr>(tblgen_sym_name))))
    return emitError(loc, "'calyx.std_wire' op attribute 'sym_name' failed to satisfy constraint: string attribute");
  return ::mlir::success();
}

::llvm::LogicalResult WireLibOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
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

::mlir::Attribute WireLibOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
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

llvm::hash_code WireLibOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.sym_name.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> WireLibOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "sym_name")
      return prop.sym_name;
  return std::nullopt;
}

void WireLibOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "sym_name") {
       prop.sym_name = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.sym_name)>>(value);
       return;
    }
}

void WireLibOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.sym_name) attrs.append("sym_name", prop.sym_name);
}

::llvm::LogicalResult WireLibOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getSymNameAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Calyx1(attr, "sym_name", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult WireLibOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.sym_name)))
    return ::mlir::failure();
  return ::mlir::success();
}

void WireLibOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.sym_name);
}

::llvm::StringRef WireLibOp::getSymName() {
  auto attr = getSymNameAttr();
  return attr.getValue();
}

void WireLibOp::setSymName(::llvm::StringRef attrValue) {
  getProperties().sym_name = ::mlir::Builder((*this)->getContext()).getStringAttr(attrValue);
}

void WireLibOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, StringRef sym_name, ::mlir::Type wireType) {
      llvm::SmallVector<mlir::Type> resultTypes = {wireType, wireType};
      odsState.addAttribute(mlir::SymbolTable::getSymbolAttrName(), odsBuilder.getStringAttr(sym_name));
      odsState.addTypes(resultTypes);
    
}

WireLibOp WireLibOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, StringRef sym_name, ::mlir::Type wireType) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(wireType)>(wireType));
  auto __res__ = ::llvm::dyn_cast<WireLibOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

WireLibOp WireLibOp::create(::mlir::ImplicitLocOpBuilder &builder, StringRef sym_name, ::mlir::Type wireType) {
  return create(builder, builder.getLoc(), std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(wireType)>(wireType));
}

::llvm::LogicalResult WireLibOp::verifyInvariantsImpl() {
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;
  if (!tblgen_sym_name) return emitOpError("requires attribute 'sym_name'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Calyx1(*this, tblgen_sym_name, "sym_name")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx6(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSResults(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx6(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  if (!((std::equal_to<>()( (*this->getODSResults(0).begin()).getType() , (*this->getODSResults(1).begin()).getType()))))
    return emitOpError("failed to verify that lhs and rhs types should be equivalent");
  return ::mlir::success();
}

::llvm::LogicalResult WireLibOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult WireLibOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::StringAttr sym_nameAttr;
  ::llvm::SmallVector<::mlir::Type, 1> allResultTypes;

  if (parser.parseSymbolName(sym_nameAttr))
    return ::mlir::failure();
  if (sym_nameAttr) result.getOrAddProperties<WireLibOp::Properties>().sym_name = sym_nameAttr;
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

  if (parser.parseTypeList(allResultTypes))
    return ::mlir::failure();
  result.addTypes(allResultTypes);
  return ::mlir::success();
}

void WireLibOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter.printSymbolName(getSymNameAttr().getValue());
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("sym_name");
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
  _odsPrinter << getOperation()->getResultTypes();
}


} // namespace circt::calyx
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::calyx::WireLibOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::calyx::detail::WireLibOpGenericAdaptorBase::Properties)

namespace circt::calyx {


//===----------------------------------------------------------------------===//
// ::circt::calyx::WiresOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

WiresOpGenericAdaptorBase::WiresOpGenericAdaptorBase(WiresOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}


} // namespace detail
WiresOpAdaptor::WiresOpAdaptor(WiresOp op) : WiresOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult WiresOpAdaptor::verify(::mlir::Location loc) {
  return ::mlir::success();
}

::llvm::LogicalResult WiresOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }
      return ::mlir::success();
}

::mlir::Attribute WiresOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code WiresOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine();
}

std::optional<mlir::Attribute> WiresOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
  return std::nullopt;
}

void WiresOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
}

void WiresOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
}

::llvm::LogicalResult WiresOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    return ::mlir::success();
}

void WiresOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState) {
      Region* region = odsState.addRegion();
      region->push_back(new Block());
    
}

WiresOp WiresOp::create(::mlir::OpBuilder &builder, ::mlir::Location location) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__);
  auto __res__ = ::llvm::dyn_cast<WiresOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

WiresOp WiresOp::create(::mlir::ImplicitLocOpBuilder &builder) {
  return create(builder, builder.getLoc());
}

::llvm::LogicalResult WiresOp::verifyInvariantsImpl() {
  {
    unsigned index = 0; (void)index;

    for (auto &region : ::llvm::MutableArrayRef((*this)->getRegion(0)))
      if (::mlir::failed(__mlir_ods_local_region_constraint_Calyx1(*this, region, "body", index++)))
        return ::mlir::failure();
  }
  return ::mlir::success();
}

::llvm::LogicalResult WiresOp::verifyInvariants() {
  if(::mlir::succeeded(verifyInvariantsImpl()) && ::mlir::succeeded(verify()))
    return ::mlir::success();
  return ::mlir::failure();
}

::mlir::ParseResult WiresOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  std::unique_ptr<::mlir::Region> bodyRegion = std::make_unique<::mlir::Region>();

  if (parser.parseRegion(*bodyRegion))
    return ::mlir::failure();

  if (bodyRegion->empty()) bodyRegion->emplaceBlock();
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
  return ::mlir::success();
}

void WiresOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter.printRegion(getBody());
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
}


} // namespace circt::calyx
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::calyx::WiresOp)

namespace circt::calyx {


//===----------------------------------------------------------------------===//
// ::circt::calyx::XorLibOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

XorLibOpGenericAdaptorBase::XorLibOpGenericAdaptorBase(XorLibOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::llvm::StringRef XorLibOpGenericAdaptorBase::getSymName() {
  auto attr = getSymNameAttr();
  return attr.getValue();
}


} // namespace detail
XorLibOpAdaptor::XorLibOpAdaptor(XorLibOp op) : XorLibOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult XorLibOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;
  if (!tblgen_sym_name) return emitError(loc, "'calyx.std_xor' op requires attribute 'sym_name'");

  if (tblgen_sym_name && !((::llvm::isa<::mlir::StringAttr>(tblgen_sym_name))))
    return emitError(loc, "'calyx.std_xor' op attribute 'sym_name' failed to satisfy constraint: string attribute");
  return ::mlir::success();
}

::llvm::LogicalResult XorLibOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
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

::mlir::Attribute XorLibOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
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

llvm::hash_code XorLibOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.sym_name.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> XorLibOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "sym_name")
      return prop.sym_name;
  return std::nullopt;
}

void XorLibOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "sym_name") {
       prop.sym_name = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.sym_name)>>(value);
       return;
    }
}

void XorLibOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.sym_name) attrs.append("sym_name", prop.sym_name);
}

::llvm::LogicalResult XorLibOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getSymNameAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_Calyx1(attr, "sym_name", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult XorLibOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.sym_name)))
    return ::mlir::failure();
  return ::mlir::success();
}

void XorLibOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.sym_name);
}

::llvm::StringRef XorLibOp::getSymName() {
  auto attr = getSymNameAttr();
  return attr.getValue();
}

void XorLibOp::setSymName(::llvm::StringRef attrValue) {
  getProperties().sym_name = ::mlir::Builder((*this)->getContext()).getStringAttr(attrValue);
}

void XorLibOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, StringRef sym_name, ::mlir::TypeRange resultTypes) {
      odsState.addAttribute(mlir::SymbolTable::getSymbolAttrName(), odsBuilder.getStringAttr(sym_name));
      odsState.addTypes(resultTypes);
    
}

XorLibOp XorLibOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, StringRef sym_name, ::mlir::TypeRange resultTypes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(resultTypes)>(resultTypes));
  auto __res__ = ::llvm::dyn_cast<XorLibOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

XorLibOp XorLibOp::create(::mlir::ImplicitLocOpBuilder &builder, StringRef sym_name, ::mlir::TypeRange resultTypes) {
  return create(builder, builder.getLoc(), std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(resultTypes)>(resultTypes));
}

::llvm::LogicalResult XorLibOp::verifyInvariantsImpl() {
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;
  if (!tblgen_sym_name) return emitOpError("requires attribute 'sym_name'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_Calyx1(*this, tblgen_sym_name, "sym_name")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx5(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSResults(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx5(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup2 = getODSResults(2);

    for (auto v : valueGroup2) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Calyx5(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  if (!((std::equal_to<>()( (*this->getODSResults(0).begin()).getType() , (*this->getODSResults(2).begin()).getType()))))
    return emitOpError("failed to verify that lhs and rhs types should be equivalent");
  if (!((std::equal_to<>()( (*this->getODSResults(0).begin()).getType() , (*this->getODSResults(1).begin()).getType()))))
    return emitOpError("failed to verify that lhs and rhs types should be equivalent");
  return ::mlir::success();
}

::llvm::LogicalResult XorLibOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult XorLibOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::StringAttr sym_nameAttr;
  ::llvm::SmallVector<::mlir::Type, 1> allResultTypes;

  if (parser.parseSymbolName(sym_nameAttr))
    return ::mlir::failure();
  if (sym_nameAttr) result.getOrAddProperties<XorLibOp::Properties>().sym_name = sym_nameAttr;
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

  if (parser.parseTypeList(allResultTypes))
    return ::mlir::failure();
  result.addTypes(allResultTypes);
  return ::mlir::success();
}

void XorLibOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter.printSymbolName(getSymNameAttr().getValue());
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("sym_name");
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
  _odsPrinter << getOperation()->getResultTypes();
}


} // namespace circt::calyx
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::calyx::XorLibOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::calyx::detail::XorLibOpGenericAdaptorBase::Properties)


#endif // GET_OP_CLASSES

