/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Op Definitions                                                             *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: MSFT.td                                                              *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

#ifdef GET_OP_LIST
#undef GET_OP_LIST

::circt::msft::DeclPhysicalRegionOp,
::circt::msft::DynamicInstanceOp,
::circt::msft::DynamicInstanceVerbatimAttrOp,
::circt::msft::InstanceHierarchyOp,
::circt::msft::LinearOp,
::circt::msft::OutputOp,
::circt::msft::PDMulticycleOp,
::circt::msft::PDPhysLocationOp,
::circt::msft::PDPhysRegionOp,
::circt::msft::PDRegPhysLocationOp,
::circt::msft::PEOutputOp,
::circt::msft::SystolicArrayOp
#endif // GET_OP_LIST

#ifdef GET_OP_CLASSES
#undef GET_OP_CLASSES


//===----------------------------------------------------------------------===//
// Local Utility Method Definitions
//===----------------------------------------------------------------------===//


static ::llvm::LogicalResult __mlir_ods_local_type_constraint_MSFT1(
    ::mlir::Operation *op, ::mlir::Type type, ::llvm::StringRef valueKind,
    unsigned valueIndex) {
  if (!((::llvm::isa<::circt::seq::ClockType>(type)))) {
    return op->emitOpError(valueKind) << " #" << valueIndex
        << " must be A type for clock-carrying wires, but got " << type;
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_type_constraint_MSFT2(
    ::mlir::Operation *op, ::mlir::Type type, ::llvm::StringRef valueKind,
    unsigned valueIndex) {
  if (!(!((::llvm::isa<::mlir::TokenType>(type))))) {
    return op->emitOpError(valueKind) << " #" << valueIndex
        << " must be variadic of any non-token type, but got " << type;
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_type_constraint_MSFT3(
    ::mlir::Operation *op, ::mlir::Type type, ::llvm::StringRef valueKind,
    unsigned valueIndex) {
  if (!(!((::llvm::isa<::mlir::TokenType>(type))))) {
    return op->emitOpError(valueKind) << " #" << valueIndex
        << " must be any non-token type, but got " << type;
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_type_constraint_MSFT4(
    ::mlir::Operation *op, ::mlir::Type type, ::llvm::StringRef valueKind,
    unsigned valueIndex) {
  if (!((::circt::hw::type_isa<circt::hw::ArrayType>(type)))) {
    return op->emitOpError(valueKind) << " #" << valueIndex
        << " must be an ArrayType, but got " << type;
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_type_constraint_MSFT5(
    ::mlir::Operation *op, ::mlir::Type type, ::llvm::StringRef valueKind,
    unsigned valueIndex) {
  if (!((
      hw::type_isa<hw::ArrayType>(type) &&
      hw::type_isa<hw::ArrayType>(
        hw::type_cast<hw::ArrayType>(type).getElementType())
    ))) {
    return op->emitOpError(valueKind) << " #" << valueIndex
        << " must be an array of arrays, but got " << type;
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_MSFT1(
    ::mlir::Attribute attr, ::llvm::StringRef attrName, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  if (attr && !((::llvm::isa<::mlir::StringAttr>(attr))))
    return emitError() << "attribute '" << attrName
        << "' failed to satisfy constraint: string attribute";
  return ::mlir::success();
}
static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_MSFT1(
    ::mlir::Operation *op, ::mlir::Attribute attr, ::llvm::StringRef attrName) {
  return __mlir_ods_local_attr_constraint_MSFT1(attr, attrName, [op]() {
    return op->emitOpError();
  });
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_MSFT2(
    ::mlir::Attribute attr, ::llvm::StringRef attrName, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  if (attr && !(((::llvm::isa<::mlir::ArrayAttr>(attr))) && (::llvm::all_of(::llvm::cast<::mlir::ArrayAttr>(attr), [&](::mlir::Attribute attr) { return attr && ((::llvm::isa<::circt::msft::PhysicalBoundsAttr>(attr))); }))))
    return emitError() << "attribute '" << attrName
        << "' failed to satisfy constraint: array of PhysicalBounds";
  return ::mlir::success();
}
static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_MSFT2(
    ::mlir::Operation *op, ::mlir::Attribute attr, ::llvm::StringRef attrName) {
  return __mlir_ods_local_attr_constraint_MSFT2(attr, attrName, [op]() {
    return op->emitOpError();
  });
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_MSFT3(
    ::mlir::Attribute attr, ::llvm::StringRef attrName, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  if (attr && !((::llvm::isa<::circt::hw::InnerRefAttr>(attr))))
    return emitError() << "attribute '" << attrName
        << "' failed to satisfy constraint: Refer to a name inside a module";
  return ::mlir::success();
}
static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_MSFT3(
    ::mlir::Operation *op, ::mlir::Attribute attr, ::llvm::StringRef attrName) {
  return __mlir_ods_local_attr_constraint_MSFT3(attr, attrName, [op]() {
    return op->emitOpError();
  });
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_MSFT4(
    ::mlir::Attribute attr, ::llvm::StringRef attrName, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  if (attr && !((::llvm::isa<::mlir::FlatSymbolRefAttr>(attr))))
    return emitError() << "attribute '" << attrName
        << "' failed to satisfy constraint: flat symbol reference attribute";
  return ::mlir::success();
}
static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_MSFT4(
    ::mlir::Operation *op, ::mlir::Attribute attr, ::llvm::StringRef attrName) {
  return __mlir_ods_local_attr_constraint_MSFT4(attr, attrName, [op]() {
    return op->emitOpError();
  });
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_MSFT5(
    ::mlir::Attribute attr, ::llvm::StringRef attrName, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  if (attr && !((((::llvm::isa<::mlir::IntegerAttr>(attr))) && ((::llvm::cast<::mlir::IntegerAttr>(attr).getType().isSignlessInteger(32)))) && ((::llvm::cast<::mlir::IntegerAttr>(attr).getInt() >= 1))))
    return emitError() << "attribute '" << attrName
        << "' failed to satisfy constraint: 32-bit signless integer attribute whose minimum value is 1";
  return ::mlir::success();
}
static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_MSFT5(
    ::mlir::Operation *op, ::mlir::Attribute attr, ::llvm::StringRef attrName) {
  return __mlir_ods_local_attr_constraint_MSFT5(attr, attrName, [op]() {
    return op->emitOpError();
  });
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_MSFT6(
    ::mlir::Attribute attr, ::llvm::StringRef attrName, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  if (attr && !((::llvm::isa<::circt::msft::PhysLocationAttr>(attr))))
    return emitError() << "attribute '" << attrName
        << "' failed to satisfy constraint: Descibes a physical location on a device";
  return ::mlir::success();
}
static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_MSFT6(
    ::mlir::Operation *op, ::mlir::Attribute attr, ::llvm::StringRef attrName) {
  return __mlir_ods_local_attr_constraint_MSFT6(attr, attrName, [op]() {
    return op->emitOpError();
  });
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_MSFT7(
    ::mlir::Attribute attr, ::llvm::StringRef attrName, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  if (attr && !((::llvm::isa<::circt::msft::LocationVectorAttr>(attr))))
    return emitError() << "attribute '" << attrName
        << "' failed to satisfy constraint: Vector of optional locations corresponding to bits in a type";
  return ::mlir::success();
}
static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_MSFT7(
    ::mlir::Operation *op, ::mlir::Attribute attr, ::llvm::StringRef attrName) {
  return __mlir_ods_local_attr_constraint_MSFT7(attr, attrName, [op]() {
    return op->emitOpError();
  });
}

static ::llvm::LogicalResult __mlir_ods_local_region_constraint_MSFT1(
    ::mlir::Operation *op, ::mlir::Region &region, ::llvm::StringRef regionName,
    unsigned regionIndex) {
  if (!((::llvm::hasNItems(region, 1)))) {
    return op->emitOpError("region #") << regionIndex
        << (regionName.empty() ? " " : " ('" + regionName + "') ")
        << "failed to verify constraint: region with 1 blocks";
  }
  return ::mlir::success();
}
namespace circt::msft {


//===----------------------------------------------------------------------===//
// ::circt::msft::DeclPhysicalRegionOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

DeclPhysicalRegionOpGenericAdaptorBase::DeclPhysicalRegionOpGenericAdaptorBase(DeclPhysicalRegionOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::llvm::StringRef DeclPhysicalRegionOpGenericAdaptorBase::getSymName() {
  auto attr = getSymNameAttr();
  return attr.getValue();
}

::mlir::ArrayAttr DeclPhysicalRegionOpGenericAdaptorBase::getBounds() {
  auto attr = getBoundsAttr();
  return attr;
}


} // namespace detail
DeclPhysicalRegionOpAdaptor::DeclPhysicalRegionOpAdaptor(DeclPhysicalRegionOp op) : DeclPhysicalRegionOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult DeclPhysicalRegionOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_bounds = getProperties().bounds; (void)tblgen_bounds;
  if (!tblgen_bounds) return emitError(loc, "'msft.physical_region' op requires attribute 'bounds'");
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;
  if (!tblgen_sym_name) return emitError(loc, "'msft.physical_region' op requires attribute 'sym_name'");

  if (tblgen_sym_name && !((::llvm::isa<::mlir::StringAttr>(tblgen_sym_name))))
    return emitError(loc, "'msft.physical_region' op attribute 'sym_name' failed to satisfy constraint: string attribute");

  if (tblgen_bounds && !(((::llvm::isa<::mlir::ArrayAttr>(tblgen_bounds))) && (::llvm::all_of(::llvm::cast<::mlir::ArrayAttr>(tblgen_bounds), [&](::mlir::Attribute attr) { return attr && ((::llvm::isa<::circt::msft::PhysicalBoundsAttr>(attr))); }))))
    return emitError(loc, "'msft.physical_region' op attribute 'bounds' failed to satisfy constraint: array of PhysicalBounds");
  return ::mlir::success();
}

::llvm::LogicalResult DeclPhysicalRegionOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.bounds;
       auto attr = dict.get("bounds");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `bounds` in property conversion: " << attr;
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

::mlir::Attribute DeclPhysicalRegionOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.bounds;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("bounds",
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

llvm::hash_code DeclPhysicalRegionOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.bounds.getAsOpaquePointer()), 
    llvm::hash_value(prop.sym_name.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> DeclPhysicalRegionOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "bounds")
      return prop.bounds;

    if (name == "sym_name")
      return prop.sym_name;
  return std::nullopt;
}

void DeclPhysicalRegionOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "bounds") {
       prop.bounds = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.bounds)>>(value);
       return;
    }

    if (name == "sym_name") {
       prop.sym_name = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.sym_name)>>(value);
       return;
    }
}

void DeclPhysicalRegionOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.bounds) attrs.append("bounds", prop.bounds);

    if (prop.sym_name) attrs.append("sym_name", prop.sym_name);
}

::llvm::LogicalResult DeclPhysicalRegionOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getBoundsAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_MSFT2(attr, "bounds", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getSymNameAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_MSFT1(attr, "sym_name", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult DeclPhysicalRegionOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.bounds)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readAttribute(prop.sym_name)))
    return ::mlir::failure();
  return ::mlir::success();
}

void DeclPhysicalRegionOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.bounds);
  writer.writeAttribute(prop.sym_name);
}

::llvm::StringRef DeclPhysicalRegionOp::getSymName() {
  auto attr = getSymNameAttr();
  return attr.getValue();
}

::mlir::ArrayAttr DeclPhysicalRegionOp::getBounds() {
  auto attr = getBoundsAttr();
  return attr;
}

void DeclPhysicalRegionOp::setSymName(::llvm::StringRef attrValue) {
  getProperties().sym_name = ::mlir::Builder((*this)->getContext()).getStringAttr(attrValue);
}

void DeclPhysicalRegionOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::StringAttr sym_name, ::mlir::ArrayAttr bounds) {
  odsState.getOrAddProperties<Properties>().sym_name = sym_name;
  odsState.getOrAddProperties<Properties>().bounds = bounds;
}

DeclPhysicalRegionOp DeclPhysicalRegionOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::StringAttr sym_name, ::mlir::ArrayAttr bounds) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(bounds)>(bounds));
  auto __res__ = ::llvm::dyn_cast<DeclPhysicalRegionOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

DeclPhysicalRegionOp DeclPhysicalRegionOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::StringAttr sym_name, ::mlir::ArrayAttr bounds) {
  return create(builder, builder.getLoc(), std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(bounds)>(bounds));
}

void DeclPhysicalRegionOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name, ::mlir::ArrayAttr bounds) {
  odsState.getOrAddProperties<Properties>().sym_name = sym_name;
  odsState.getOrAddProperties<Properties>().bounds = bounds;
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

DeclPhysicalRegionOp DeclPhysicalRegionOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name, ::mlir::ArrayAttr bounds) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(bounds)>(bounds));
  auto __res__ = ::llvm::dyn_cast<DeclPhysicalRegionOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

DeclPhysicalRegionOp DeclPhysicalRegionOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name, ::mlir::ArrayAttr bounds) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(bounds)>(bounds));
}

void DeclPhysicalRegionOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::llvm::StringRef sym_name, ::mlir::ArrayAttr bounds) {
  odsState.getOrAddProperties<Properties>().sym_name = odsBuilder.getStringAttr(sym_name);
  odsState.getOrAddProperties<Properties>().bounds = bounds;
}

DeclPhysicalRegionOp DeclPhysicalRegionOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::llvm::StringRef sym_name, ::mlir::ArrayAttr bounds) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(bounds)>(bounds));
  auto __res__ = ::llvm::dyn_cast<DeclPhysicalRegionOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

DeclPhysicalRegionOp DeclPhysicalRegionOp::create(::mlir::ImplicitLocOpBuilder &builder, ::llvm::StringRef sym_name, ::mlir::ArrayAttr bounds) {
  return create(builder, builder.getLoc(), std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(bounds)>(bounds));
}

void DeclPhysicalRegionOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name, ::mlir::ArrayAttr bounds) {
  odsState.getOrAddProperties<Properties>().sym_name = odsBuilder.getStringAttr(sym_name);
  odsState.getOrAddProperties<Properties>().bounds = bounds;
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

DeclPhysicalRegionOp DeclPhysicalRegionOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name, ::mlir::ArrayAttr bounds) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(bounds)>(bounds));
  auto __res__ = ::llvm::dyn_cast<DeclPhysicalRegionOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

DeclPhysicalRegionOp DeclPhysicalRegionOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name, ::mlir::ArrayAttr bounds) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(bounds)>(bounds));
}

void DeclPhysicalRegionOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<DeclPhysicalRegionOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

DeclPhysicalRegionOp DeclPhysicalRegionOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<DeclPhysicalRegionOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

DeclPhysicalRegionOp DeclPhysicalRegionOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void DeclPhysicalRegionOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

DeclPhysicalRegionOp DeclPhysicalRegionOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<DeclPhysicalRegionOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

DeclPhysicalRegionOp DeclPhysicalRegionOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult DeclPhysicalRegionOp::verifyInvariantsImpl() {
  auto tblgen_bounds = getProperties().bounds; (void)tblgen_bounds;
  if (!tblgen_bounds) return emitOpError("requires attribute 'bounds'");
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;
  if (!tblgen_sym_name) return emitOpError("requires attribute 'sym_name'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_MSFT1(*this, tblgen_sym_name, "sym_name")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_MSFT2(*this, tblgen_bounds, "bounds")))
    return ::mlir::failure();
  return ::mlir::success();
}

::llvm::LogicalResult DeclPhysicalRegionOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult DeclPhysicalRegionOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::StringAttr sym_nameAttr;
  ::mlir::ArrayAttr boundsAttr;

  if (parser.parseSymbolName(sym_nameAttr))
    return ::mlir::failure();
  if (sym_nameAttr) result.getOrAddProperties<DeclPhysicalRegionOp::Properties>().sym_name = sym_nameAttr;
  if (parser.parseComma())
    return ::mlir::failure();

  if (parser.parseCustomAttributeWithFallback(boundsAttr, parser.getBuilder().getType<::mlir::NoneType>())) {
    return ::mlir::failure();
  }
  if (boundsAttr) result.getOrAddProperties<DeclPhysicalRegionOp::Properties>().bounds = boundsAttr;
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

void DeclPhysicalRegionOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter.printSymbolName(getSymNameAttr().getValue());
  _odsPrinter << ",";
  _odsPrinter << ' ';
  _odsPrinter.printAttributeWithoutType(getBoundsAttr());
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("sym_name");
  elidedAttrs.push_back("bounds");
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
}


} // namespace circt::msft
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::msft::DeclPhysicalRegionOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::msft::detail::DeclPhysicalRegionOpGenericAdaptorBase::Properties)

namespace circt::msft {


//===----------------------------------------------------------------------===//
// ::circt::msft::DynamicInstanceOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

DynamicInstanceOpGenericAdaptorBase::DynamicInstanceOpGenericAdaptorBase(DynamicInstanceOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::circt::hw::InnerRefAttr DynamicInstanceOpGenericAdaptorBase::getInstanceRef() {
  auto attr = getInstanceRefAttr();
  return ::llvm::cast<::circt::hw::InnerRefAttr>(attr);
}


} // namespace detail
DynamicInstanceOpAdaptor::DynamicInstanceOpAdaptor(DynamicInstanceOp op) : DynamicInstanceOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult DynamicInstanceOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_instanceRef = getProperties().instanceRef; (void)tblgen_instanceRef;
  if (!tblgen_instanceRef) return emitError(loc, "'msft.instance.dynamic' op requires attribute 'instanceRef'");

  if (tblgen_instanceRef && !((::llvm::isa<::circt::hw::InnerRefAttr>(tblgen_instanceRef))))
    return emitError(loc, "'msft.instance.dynamic' op attribute 'instanceRef' failed to satisfy constraint: Refer to a name inside a module");
  return ::mlir::success();
}

::llvm::LogicalResult DynamicInstanceOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.instanceRef;
       auto attr = dict.get("instanceRef");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `instanceRef` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  return ::mlir::success();
}

::mlir::Attribute DynamicInstanceOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.instanceRef;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("instanceRef",
                                       propStorage));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code DynamicInstanceOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.instanceRef.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> DynamicInstanceOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "instanceRef")
      return prop.instanceRef;
  return std::nullopt;
}

void DynamicInstanceOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "instanceRef") {
       prop.instanceRef = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.instanceRef)>>(value);
       return;
    }
}

void DynamicInstanceOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.instanceRef) attrs.append("instanceRef", prop.instanceRef);
}

::llvm::LogicalResult DynamicInstanceOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getInstanceRefAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_MSFT3(attr, "instanceRef", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult DynamicInstanceOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.instanceRef)))
    return ::mlir::failure();
  return ::mlir::success();
}

void DynamicInstanceOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.instanceRef);
}

::circt::hw::InnerRefAttr DynamicInstanceOp::getInstanceRef() {
  auto attr = getInstanceRefAttr();
  return ::llvm::cast<::circt::hw::InnerRefAttr>(attr);
}

void DynamicInstanceOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::circt::hw::InnerRefAttr instanceRef) {
  odsState.getOrAddProperties<Properties>().instanceRef = instanceRef;
  (void)odsState.addRegion();
}

DynamicInstanceOp DynamicInstanceOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::circt::hw::InnerRefAttr instanceRef) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(instanceRef)>(instanceRef));
  auto __res__ = ::llvm::dyn_cast<DynamicInstanceOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

DynamicInstanceOp DynamicInstanceOp::create(::mlir::ImplicitLocOpBuilder &builder, ::circt::hw::InnerRefAttr instanceRef) {
  return create(builder, builder.getLoc(), std::forward<decltype(instanceRef)>(instanceRef));
}

void DynamicInstanceOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::circt::hw::InnerRefAttr instanceRef) {
  odsState.getOrAddProperties<Properties>().instanceRef = instanceRef;
  (void)odsState.addRegion();
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

DynamicInstanceOp DynamicInstanceOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::circt::hw::InnerRefAttr instanceRef) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(instanceRef)>(instanceRef));
  auto __res__ = ::llvm::dyn_cast<DynamicInstanceOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

DynamicInstanceOp DynamicInstanceOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::circt::hw::InnerRefAttr instanceRef) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(instanceRef)>(instanceRef));
}

void DynamicInstanceOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  for (unsigned i = 0; i != 1; ++i)
    (void)odsState.addRegion();
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<DynamicInstanceOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

DynamicInstanceOp DynamicInstanceOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<DynamicInstanceOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

DynamicInstanceOp DynamicInstanceOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void DynamicInstanceOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  for (unsigned i = 0; i != 1; ++i)
    (void)odsState.addRegion();
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

DynamicInstanceOp DynamicInstanceOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<DynamicInstanceOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

DynamicInstanceOp DynamicInstanceOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult DynamicInstanceOp::verifyInvariantsImpl() {
  auto tblgen_instanceRef = getProperties().instanceRef; (void)tblgen_instanceRef;
  if (!tblgen_instanceRef) return emitOpError("requires attribute 'instanceRef'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_MSFT3(*this, tblgen_instanceRef, "instanceRef")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;

    for (auto &region : ::llvm::MutableArrayRef((*this)->getRegion(0)))
      if (::mlir::failed(__mlir_ods_local_region_constraint_MSFT1(*this, region, "body", index++)))
        return ::mlir::failure();
  }
  return ::mlir::success();
}

::llvm::LogicalResult DynamicInstanceOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult DynamicInstanceOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::circt::hw::InnerRefAttr instanceRefAttr;
  std::unique_ptr<::mlir::Region> bodyRegion = std::make_unique<::mlir::Region>();
  {
    auto odsResult = parseImplicitInnerRef(parser, instanceRefAttr);
    if (odsResult) return ::mlir::failure();
    result.getOrAddProperties<DynamicInstanceOp::Properties>().instanceRef = instanceRefAttr;
  }

  if (parser.parseRegion(*bodyRegion))
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
  result.addRegion(std::move(bodyRegion));
  return ::mlir::success();
}

void DynamicInstanceOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  printImplicitInnerRef(_odsPrinter, *this, getInstanceRefAttr());
  _odsPrinter << ' ';
  _odsPrinter.printRegion(getBody());
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("instanceRef");
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
}


} // namespace circt::msft
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::msft::DynamicInstanceOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::msft::detail::DynamicInstanceOpGenericAdaptorBase::Properties)

namespace circt::msft {


//===----------------------------------------------------------------------===//
// ::circt::msft::DynamicInstanceVerbatimAttrOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

DynamicInstanceVerbatimAttrOpGenericAdaptorBase::DynamicInstanceVerbatimAttrOpGenericAdaptorBase(DynamicInstanceVerbatimAttrOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::llvm::StringRef DynamicInstanceVerbatimAttrOpGenericAdaptorBase::getName() {
  auto attr = getNameAttr();
  return attr.getValue();
}

::llvm::StringRef DynamicInstanceVerbatimAttrOpGenericAdaptorBase::getValue() {
  auto attr = getValueAttr();
  return attr.getValue();
}

::std::optional< ::llvm::StringRef > DynamicInstanceVerbatimAttrOpGenericAdaptorBase::getSubPath() {
  auto attr = getSubPathAttr();
  return attr ? ::std::optional< ::llvm::StringRef >(attr.getValue()) : (::std::nullopt);
}

::std::optional< ::llvm::StringRef > DynamicInstanceVerbatimAttrOpGenericAdaptorBase::getRef() {
  auto attr = getRefAttr();
  return attr ? ::std::optional< ::llvm::StringRef >(attr.getValue()) : (::std::nullopt);
}


} // namespace detail
DynamicInstanceVerbatimAttrOpAdaptor::DynamicInstanceVerbatimAttrOpAdaptor(DynamicInstanceVerbatimAttrOp op) : DynamicInstanceVerbatimAttrOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult DynamicInstanceVerbatimAttrOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_name = getProperties().name; (void)tblgen_name;
  if (!tblgen_name) return emitError(loc, "'msft.instance.verb_attr' op requires attribute 'name'");
  auto tblgen_ref = getProperties().ref; (void)tblgen_ref;
  auto tblgen_subPath = getProperties().subPath; (void)tblgen_subPath;
  auto tblgen_value = getProperties().value; (void)tblgen_value;
  if (!tblgen_value) return emitError(loc, "'msft.instance.verb_attr' op requires attribute 'value'");

  if (tblgen_name && !((::llvm::isa<::mlir::StringAttr>(tblgen_name))))
    return emitError(loc, "'msft.instance.verb_attr' op attribute 'name' failed to satisfy constraint: string attribute");

  if (tblgen_value && !((::llvm::isa<::mlir::StringAttr>(tblgen_value))))
    return emitError(loc, "'msft.instance.verb_attr' op attribute 'value' failed to satisfy constraint: string attribute");

  if (tblgen_subPath && !((::llvm::isa<::mlir::StringAttr>(tblgen_subPath))))
    return emitError(loc, "'msft.instance.verb_attr' op attribute 'subPath' failed to satisfy constraint: string attribute");

  if (tblgen_ref && !((::llvm::isa<::mlir::FlatSymbolRefAttr>(tblgen_ref))))
    return emitError(loc, "'msft.instance.verb_attr' op attribute 'ref' failed to satisfy constraint: flat symbol reference attribute");
  return ::mlir::success();
}

::llvm::LogicalResult DynamicInstanceVerbatimAttrOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
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
    auto &propStorage = prop.ref;
       auto attr = dict.get("ref");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `ref` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.subPath;
       auto attr = dict.get("subPath");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `subPath` in property conversion: " << attr;
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

::mlir::Attribute DynamicInstanceVerbatimAttrOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.name;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("name",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.ref;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("ref",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.subPath;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("subPath",
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

llvm::hash_code DynamicInstanceVerbatimAttrOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.name.getAsOpaquePointer()), 
    llvm::hash_value(prop.ref.getAsOpaquePointer()), 
    llvm::hash_value(prop.subPath.getAsOpaquePointer()), 
    llvm::hash_value(prop.value.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> DynamicInstanceVerbatimAttrOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "name")
      return prop.name;

    if (name == "ref")
      return prop.ref;

    if (name == "subPath")
      return prop.subPath;

    if (name == "value")
      return prop.value;
  return std::nullopt;
}

void DynamicInstanceVerbatimAttrOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "name") {
       prop.name = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.name)>>(value);
       return;
    }

    if (name == "ref") {
       prop.ref = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.ref)>>(value);
       return;
    }

    if (name == "subPath") {
       prop.subPath = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.subPath)>>(value);
       return;
    }

    if (name == "value") {
       prop.value = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.value)>>(value);
       return;
    }
}

void DynamicInstanceVerbatimAttrOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.name) attrs.append("name", prop.name);

    if (prop.ref) attrs.append("ref", prop.ref);

    if (prop.subPath) attrs.append("subPath", prop.subPath);

    if (prop.value) attrs.append("value", prop.value);
}

::llvm::LogicalResult DynamicInstanceVerbatimAttrOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getNameAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_MSFT1(attr, "name", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getRefAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_MSFT4(attr, "ref", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getSubPathAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_MSFT1(attr, "subPath", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getValueAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_MSFT1(attr, "value", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult DynamicInstanceVerbatimAttrOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.name)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readOptionalAttribute(prop.ref)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readOptionalAttribute(prop.subPath)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readAttribute(prop.value)))
    return ::mlir::failure();
  return ::mlir::success();
}

void DynamicInstanceVerbatimAttrOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.name);

  writer.writeOptionalAttribute(prop.ref);

  writer.writeOptionalAttribute(prop.subPath);
  writer.writeAttribute(prop.value);
}

::llvm::StringRef DynamicInstanceVerbatimAttrOp::getName() {
  auto attr = getNameAttr();
  return attr.getValue();
}

::llvm::StringRef DynamicInstanceVerbatimAttrOp::getValue() {
  auto attr = getValueAttr();
  return attr.getValue();
}

::std::optional< ::llvm::StringRef > DynamicInstanceVerbatimAttrOp::getSubPath() {
  auto attr = getSubPathAttr();
  return attr ? ::std::optional< ::llvm::StringRef >(attr.getValue()) : (::std::nullopt);
}

::std::optional< ::llvm::StringRef > DynamicInstanceVerbatimAttrOp::getRef() {
  auto attr = getRefAttr();
  return attr ? ::std::optional< ::llvm::StringRef >(attr.getValue()) : (::std::nullopt);
}

void DynamicInstanceVerbatimAttrOp::setName(::llvm::StringRef attrValue) {
  getProperties().name = ::mlir::Builder((*this)->getContext()).getStringAttr(attrValue);
}

void DynamicInstanceVerbatimAttrOp::setValue(::llvm::StringRef attrValue) {
  getProperties().value = ::mlir::Builder((*this)->getContext()).getStringAttr(attrValue);
}

void DynamicInstanceVerbatimAttrOp::setSubPath(::std::optional<::llvm::StringRef> attrValue) {
    auto &odsProp = getProperties().subPath;
    if (attrValue)
      odsProp = ::mlir::Builder((*this)->getContext()).getStringAttr(*attrValue);
    else
      odsProp = nullptr;
}

void DynamicInstanceVerbatimAttrOp::setRef(::std::optional<::llvm::StringRef> attrValue) {
    auto &odsProp = getProperties().ref;
    if (attrValue)
      odsProp = ::mlir::SymbolRefAttr::get(::mlir::Builder((*this)->getContext()).getContext(), *attrValue);
    else
      odsProp = nullptr;
}

void DynamicInstanceVerbatimAttrOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::StringAttr name, ::mlir::StringAttr value, /*optional*/::mlir::StringAttr subPath, /*optional*/::mlir::FlatSymbolRefAttr ref) {
  odsState.getOrAddProperties<Properties>().name = name;
  odsState.getOrAddProperties<Properties>().value = value;
  if (subPath) {
    odsState.getOrAddProperties<Properties>().subPath = subPath;
  }
  if (ref) {
    odsState.getOrAddProperties<Properties>().ref = ref;
  }
}

DynamicInstanceVerbatimAttrOp DynamicInstanceVerbatimAttrOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::StringAttr name, ::mlir::StringAttr value, /*optional*/::mlir::StringAttr subPath, /*optional*/::mlir::FlatSymbolRefAttr ref) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(name)>(name), std::forward<decltype(value)>(value), std::forward<decltype(subPath)>(subPath), std::forward<decltype(ref)>(ref));
  auto __res__ = ::llvm::dyn_cast<DynamicInstanceVerbatimAttrOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

DynamicInstanceVerbatimAttrOp DynamicInstanceVerbatimAttrOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::StringAttr name, ::mlir::StringAttr value, /*optional*/::mlir::StringAttr subPath, /*optional*/::mlir::FlatSymbolRefAttr ref) {
  return create(builder, builder.getLoc(), std::forward<decltype(name)>(name), std::forward<decltype(value)>(value), std::forward<decltype(subPath)>(subPath), std::forward<decltype(ref)>(ref));
}

void DynamicInstanceVerbatimAttrOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::StringAttr name, ::mlir::StringAttr value, /*optional*/::mlir::StringAttr subPath, /*optional*/::mlir::FlatSymbolRefAttr ref) {
  odsState.getOrAddProperties<Properties>().name = name;
  odsState.getOrAddProperties<Properties>().value = value;
  if (subPath) {
    odsState.getOrAddProperties<Properties>().subPath = subPath;
  }
  if (ref) {
    odsState.getOrAddProperties<Properties>().ref = ref;
  }
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

DynamicInstanceVerbatimAttrOp DynamicInstanceVerbatimAttrOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::StringAttr name, ::mlir::StringAttr value, /*optional*/::mlir::StringAttr subPath, /*optional*/::mlir::FlatSymbolRefAttr ref) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(name)>(name), std::forward<decltype(value)>(value), std::forward<decltype(subPath)>(subPath), std::forward<decltype(ref)>(ref));
  auto __res__ = ::llvm::dyn_cast<DynamicInstanceVerbatimAttrOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

DynamicInstanceVerbatimAttrOp DynamicInstanceVerbatimAttrOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::StringAttr name, ::mlir::StringAttr value, /*optional*/::mlir::StringAttr subPath, /*optional*/::mlir::FlatSymbolRefAttr ref) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(name)>(name), std::forward<decltype(value)>(value), std::forward<decltype(subPath)>(subPath), std::forward<decltype(ref)>(ref));
}

void DynamicInstanceVerbatimAttrOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::llvm::StringRef name, ::llvm::StringRef value, /*optional*/::mlir::StringAttr subPath, /*optional*/::mlir::FlatSymbolRefAttr ref) {
  odsState.getOrAddProperties<Properties>().name = odsBuilder.getStringAttr(name);
  odsState.getOrAddProperties<Properties>().value = odsBuilder.getStringAttr(value);
  if (subPath) {
    odsState.getOrAddProperties<Properties>().subPath = subPath;
  }
  if (ref) {
    odsState.getOrAddProperties<Properties>().ref = ref;
  }
}

DynamicInstanceVerbatimAttrOp DynamicInstanceVerbatimAttrOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::llvm::StringRef name, ::llvm::StringRef value, /*optional*/::mlir::StringAttr subPath, /*optional*/::mlir::FlatSymbolRefAttr ref) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(name)>(name), std::forward<decltype(value)>(value), std::forward<decltype(subPath)>(subPath), std::forward<decltype(ref)>(ref));
  auto __res__ = ::llvm::dyn_cast<DynamicInstanceVerbatimAttrOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

DynamicInstanceVerbatimAttrOp DynamicInstanceVerbatimAttrOp::create(::mlir::ImplicitLocOpBuilder &builder, ::llvm::StringRef name, ::llvm::StringRef value, /*optional*/::mlir::StringAttr subPath, /*optional*/::mlir::FlatSymbolRefAttr ref) {
  return create(builder, builder.getLoc(), std::forward<decltype(name)>(name), std::forward<decltype(value)>(value), std::forward<decltype(subPath)>(subPath), std::forward<decltype(ref)>(ref));
}

void DynamicInstanceVerbatimAttrOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::llvm::StringRef name, ::llvm::StringRef value, /*optional*/::mlir::StringAttr subPath, /*optional*/::mlir::FlatSymbolRefAttr ref) {
  odsState.getOrAddProperties<Properties>().name = odsBuilder.getStringAttr(name);
  odsState.getOrAddProperties<Properties>().value = odsBuilder.getStringAttr(value);
  if (subPath) {
    odsState.getOrAddProperties<Properties>().subPath = subPath;
  }
  if (ref) {
    odsState.getOrAddProperties<Properties>().ref = ref;
  }
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

DynamicInstanceVerbatimAttrOp DynamicInstanceVerbatimAttrOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::llvm::StringRef name, ::llvm::StringRef value, /*optional*/::mlir::StringAttr subPath, /*optional*/::mlir::FlatSymbolRefAttr ref) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(name)>(name), std::forward<decltype(value)>(value), std::forward<decltype(subPath)>(subPath), std::forward<decltype(ref)>(ref));
  auto __res__ = ::llvm::dyn_cast<DynamicInstanceVerbatimAttrOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

DynamicInstanceVerbatimAttrOp DynamicInstanceVerbatimAttrOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::llvm::StringRef name, ::llvm::StringRef value, /*optional*/::mlir::StringAttr subPath, /*optional*/::mlir::FlatSymbolRefAttr ref) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(name)>(name), std::forward<decltype(value)>(value), std::forward<decltype(subPath)>(subPath), std::forward<decltype(ref)>(ref));
}

void DynamicInstanceVerbatimAttrOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<DynamicInstanceVerbatimAttrOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

DynamicInstanceVerbatimAttrOp DynamicInstanceVerbatimAttrOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<DynamicInstanceVerbatimAttrOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

DynamicInstanceVerbatimAttrOp DynamicInstanceVerbatimAttrOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void DynamicInstanceVerbatimAttrOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

DynamicInstanceVerbatimAttrOp DynamicInstanceVerbatimAttrOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<DynamicInstanceVerbatimAttrOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

DynamicInstanceVerbatimAttrOp DynamicInstanceVerbatimAttrOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult DynamicInstanceVerbatimAttrOp::verifyInvariantsImpl() {
  auto tblgen_name = getProperties().name; (void)tblgen_name;
  if (!tblgen_name) return emitOpError("requires attribute 'name'");
  auto tblgen_ref = getProperties().ref; (void)tblgen_ref;
  auto tblgen_subPath = getProperties().subPath; (void)tblgen_subPath;
  auto tblgen_value = getProperties().value; (void)tblgen_value;
  if (!tblgen_value) return emitOpError("requires attribute 'value'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_MSFT1(*this, tblgen_name, "name")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_MSFT1(*this, tblgen_value, "value")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_MSFT1(*this, tblgen_subPath, "subPath")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_MSFT4(*this, tblgen_ref, "ref")))
    return ::mlir::failure();
  return ::mlir::success();
}

::llvm::LogicalResult DynamicInstanceVerbatimAttrOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult DynamicInstanceVerbatimAttrOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::FlatSymbolRefAttr refAttr;
  ::mlir::StringAttr nameAttr;
  ::mlir::StringAttr valueAttr;
  ::mlir::StringAttr subPathAttr;

  ::mlir::OptionalParseResult parseResultrefAttr =
    parser.parseOptionalAttribute(refAttr, parser.getBuilder().getType<::mlir::NoneType>());
  if (parseResultrefAttr.has_value() && failed(*parseResultrefAttr))
    return ::mlir::failure();
  if (parseResultrefAttr.has_value() && succeeded(*parseResultrefAttr))
  if (refAttr) result.getOrAddProperties<DynamicInstanceVerbatimAttrOp::Properties>().ref = refAttr;
  if (refAttr) {
  }
  if (parser.parseKeyword("name"))
    return ::mlir::failure();
  if (parser.parseColon())
    return ::mlir::failure();

  if (parser.parseCustomAttributeWithFallback(nameAttr, parser.getBuilder().getType<::mlir::NoneType>())) {
    return ::mlir::failure();
  }
  if (nameAttr) result.getOrAddProperties<DynamicInstanceVerbatimAttrOp::Properties>().name = nameAttr;
  if (parser.parseKeyword("value"))
    return ::mlir::failure();
  if (parser.parseColon())
    return ::mlir::failure();

  if (parser.parseCustomAttributeWithFallback(valueAttr, parser.getBuilder().getType<::mlir::NoneType>())) {
    return ::mlir::failure();
  }
  if (valueAttr) result.getOrAddProperties<DynamicInstanceVerbatimAttrOp::Properties>().value = valueAttr;
  if (::mlir::succeeded(parser.parseOptionalKeyword("path"))) {
  if (parser.parseColon())
    return ::mlir::failure();

  if (parser.parseCustomAttributeWithFallback(subPathAttr, parser.getBuilder().getType<::mlir::NoneType>())) {
    return ::mlir::failure();
  }
  if (subPathAttr) result.getOrAddProperties<DynamicInstanceVerbatimAttrOp::Properties>().subPath = subPathAttr;
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
  return ::mlir::success();
}

void DynamicInstanceVerbatimAttrOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  if (getRefAttr()) {
    _odsPrinter << ' ';
    _odsPrinter.printAttributeWithoutType(getRefAttr());
  }
  _odsPrinter << ' ' << "name";
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
  _odsPrinter.printAttributeWithoutType(getNameAttr());
  _odsPrinter << ' ' << "value";
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
  _odsPrinter.printAttributeWithoutType(getValueAttr());
  if (getSubPathAttr()) {
    _odsPrinter << ' ' << "path";
    _odsPrinter << ' ' << ":";
    _odsPrinter << ' ';
    _odsPrinter.printAttributeWithoutType(getSubPathAttr());
  }
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("ref");
  elidedAttrs.push_back("name");
  elidedAttrs.push_back("value");
  elidedAttrs.push_back("subPath");
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
}


} // namespace circt::msft
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::msft::DynamicInstanceVerbatimAttrOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::msft::detail::DynamicInstanceVerbatimAttrOpGenericAdaptorBase::Properties)

namespace circt::msft {


//===----------------------------------------------------------------------===//
// ::circt::msft::InstanceHierarchyOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

InstanceHierarchyOpGenericAdaptorBase::InstanceHierarchyOpGenericAdaptorBase(InstanceHierarchyOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::llvm::StringRef InstanceHierarchyOpGenericAdaptorBase::getTopModuleRef() {
  auto attr = getTopModuleRefAttr();
  return attr.getValue();
}

::std::optional< ::llvm::StringRef > InstanceHierarchyOpGenericAdaptorBase::getInstName() {
  auto attr = getInstNameAttr();
  return attr ? ::std::optional< ::llvm::StringRef >(attr.getValue()) : (::std::nullopt);
}


} // namespace detail
InstanceHierarchyOpAdaptor::InstanceHierarchyOpAdaptor(InstanceHierarchyOp op) : InstanceHierarchyOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult InstanceHierarchyOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_instName = getProperties().instName; (void)tblgen_instName;
  auto tblgen_topModuleRef = getProperties().topModuleRef; (void)tblgen_topModuleRef;
  if (!tblgen_topModuleRef) return emitError(loc, "'msft.instance.hierarchy' op requires attribute 'topModuleRef'");

  if (tblgen_topModuleRef && !((::llvm::isa<::mlir::FlatSymbolRefAttr>(tblgen_topModuleRef))))
    return emitError(loc, "'msft.instance.hierarchy' op attribute 'topModuleRef' failed to satisfy constraint: flat symbol reference attribute");

  if (tblgen_instName && !((::llvm::isa<::mlir::StringAttr>(tblgen_instName))))
    return emitError(loc, "'msft.instance.hierarchy' op attribute 'instName' failed to satisfy constraint: string attribute");
  return ::mlir::success();
}

::llvm::LogicalResult InstanceHierarchyOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.instName;
       auto attr = dict.get("instName");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `instName` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.topModuleRef;
       auto attr = dict.get("topModuleRef");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `topModuleRef` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  return ::mlir::success();
}

::mlir::Attribute InstanceHierarchyOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.instName;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("instName",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.topModuleRef;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("topModuleRef",
                                       propStorage));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code InstanceHierarchyOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.instName.getAsOpaquePointer()), 
    llvm::hash_value(prop.topModuleRef.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> InstanceHierarchyOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "instName")
      return prop.instName;

    if (name == "topModuleRef")
      return prop.topModuleRef;
  return std::nullopt;
}

void InstanceHierarchyOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "instName") {
       prop.instName = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.instName)>>(value);
       return;
    }

    if (name == "topModuleRef") {
       prop.topModuleRef = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.topModuleRef)>>(value);
       return;
    }
}

void InstanceHierarchyOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.instName) attrs.append("instName", prop.instName);

    if (prop.topModuleRef) attrs.append("topModuleRef", prop.topModuleRef);
}

::llvm::LogicalResult InstanceHierarchyOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getInstNameAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_MSFT1(attr, "instName", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getTopModuleRefAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_MSFT4(attr, "topModuleRef", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult InstanceHierarchyOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readOptionalAttribute(prop.instName)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readAttribute(prop.topModuleRef)))
    return ::mlir::failure();
  return ::mlir::success();
}

void InstanceHierarchyOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;

  writer.writeOptionalAttribute(prop.instName);
  writer.writeAttribute(prop.topModuleRef);
}

::llvm::StringRef InstanceHierarchyOp::getTopModuleRef() {
  auto attr = getTopModuleRefAttr();
  return attr.getValue();
}

::std::optional< ::llvm::StringRef > InstanceHierarchyOp::getInstName() {
  auto attr = getInstNameAttr();
  return attr ? ::std::optional< ::llvm::StringRef >(attr.getValue()) : (::std::nullopt);
}

void InstanceHierarchyOp::setTopModuleRef(::llvm::StringRef attrValue) {
  getProperties().topModuleRef = ::mlir::SymbolRefAttr::get(::mlir::Builder((*this)->getContext()).getContext(), attrValue);
}

void InstanceHierarchyOp::setInstName(::std::optional<::llvm::StringRef> attrValue) {
    auto &odsProp = getProperties().instName;
    if (attrValue)
      odsProp = ::mlir::Builder((*this)->getContext()).getStringAttr(*attrValue);
    else
      odsProp = nullptr;
}

void InstanceHierarchyOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::FlatSymbolRefAttr topModuleRef, /*optional*/::mlir::StringAttr instName) {
  odsState.getOrAddProperties<Properties>().topModuleRef = topModuleRef;
  if (instName) {
    odsState.getOrAddProperties<Properties>().instName = instName;
  }
  (void)odsState.addRegion();
}

InstanceHierarchyOp InstanceHierarchyOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::FlatSymbolRefAttr topModuleRef, /*optional*/::mlir::StringAttr instName) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(topModuleRef)>(topModuleRef), std::forward<decltype(instName)>(instName));
  auto __res__ = ::llvm::dyn_cast<InstanceHierarchyOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

InstanceHierarchyOp InstanceHierarchyOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::FlatSymbolRefAttr topModuleRef, /*optional*/::mlir::StringAttr instName) {
  return create(builder, builder.getLoc(), std::forward<decltype(topModuleRef)>(topModuleRef), std::forward<decltype(instName)>(instName));
}

void InstanceHierarchyOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::FlatSymbolRefAttr topModuleRef, /*optional*/::mlir::StringAttr instName) {
  odsState.getOrAddProperties<Properties>().topModuleRef = topModuleRef;
  if (instName) {
    odsState.getOrAddProperties<Properties>().instName = instName;
  }
  (void)odsState.addRegion();
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

InstanceHierarchyOp InstanceHierarchyOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::FlatSymbolRefAttr topModuleRef, /*optional*/::mlir::StringAttr instName) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(topModuleRef)>(topModuleRef), std::forward<decltype(instName)>(instName));
  auto __res__ = ::llvm::dyn_cast<InstanceHierarchyOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

InstanceHierarchyOp InstanceHierarchyOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::FlatSymbolRefAttr topModuleRef, /*optional*/::mlir::StringAttr instName) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(topModuleRef)>(topModuleRef), std::forward<decltype(instName)>(instName));
}

void InstanceHierarchyOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::llvm::StringRef topModuleRef, /*optional*/::mlir::StringAttr instName) {
  odsState.getOrAddProperties<Properties>().topModuleRef = ::mlir::SymbolRefAttr::get(odsBuilder.getContext(), topModuleRef);
  if (instName) {
    odsState.getOrAddProperties<Properties>().instName = instName;
  }
  (void)odsState.addRegion();
}

InstanceHierarchyOp InstanceHierarchyOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::llvm::StringRef topModuleRef, /*optional*/::mlir::StringAttr instName) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(topModuleRef)>(topModuleRef), std::forward<decltype(instName)>(instName));
  auto __res__ = ::llvm::dyn_cast<InstanceHierarchyOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

InstanceHierarchyOp InstanceHierarchyOp::create(::mlir::ImplicitLocOpBuilder &builder, ::llvm::StringRef topModuleRef, /*optional*/::mlir::StringAttr instName) {
  return create(builder, builder.getLoc(), std::forward<decltype(topModuleRef)>(topModuleRef), std::forward<decltype(instName)>(instName));
}

void InstanceHierarchyOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::llvm::StringRef topModuleRef, /*optional*/::mlir::StringAttr instName) {
  odsState.getOrAddProperties<Properties>().topModuleRef = ::mlir::SymbolRefAttr::get(odsBuilder.getContext(), topModuleRef);
  if (instName) {
    odsState.getOrAddProperties<Properties>().instName = instName;
  }
  (void)odsState.addRegion();
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

InstanceHierarchyOp InstanceHierarchyOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::llvm::StringRef topModuleRef, /*optional*/::mlir::StringAttr instName) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(topModuleRef)>(topModuleRef), std::forward<decltype(instName)>(instName));
  auto __res__ = ::llvm::dyn_cast<InstanceHierarchyOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

InstanceHierarchyOp InstanceHierarchyOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::llvm::StringRef topModuleRef, /*optional*/::mlir::StringAttr instName) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(topModuleRef)>(topModuleRef), std::forward<decltype(instName)>(instName));
}

void InstanceHierarchyOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  for (unsigned i = 0; i != 1; ++i)
    (void)odsState.addRegion();
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<InstanceHierarchyOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

InstanceHierarchyOp InstanceHierarchyOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<InstanceHierarchyOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

InstanceHierarchyOp InstanceHierarchyOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void InstanceHierarchyOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  for (unsigned i = 0; i != 1; ++i)
    (void)odsState.addRegion();
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

InstanceHierarchyOp InstanceHierarchyOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<InstanceHierarchyOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

InstanceHierarchyOp InstanceHierarchyOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult InstanceHierarchyOp::verifyInvariantsImpl() {
  auto tblgen_instName = getProperties().instName; (void)tblgen_instName;
  auto tblgen_topModuleRef = getProperties().topModuleRef; (void)tblgen_topModuleRef;
  if (!tblgen_topModuleRef) return emitOpError("requires attribute 'topModuleRef'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_MSFT4(*this, tblgen_topModuleRef, "topModuleRef")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_MSFT1(*this, tblgen_instName, "instName")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;

    for (auto &region : ::llvm::MutableArrayRef((*this)->getRegion(0)))
      if (::mlir::failed(__mlir_ods_local_region_constraint_MSFT1(*this, region, "body", index++)))
        return ::mlir::failure();
  }
  return ::mlir::success();
}

::llvm::LogicalResult InstanceHierarchyOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult InstanceHierarchyOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::FlatSymbolRefAttr topModuleRefAttr;
  ::mlir::StringAttr instNameAttr;
  std::unique_ptr<::mlir::Region> bodyRegion = std::make_unique<::mlir::Region>();

  if (parser.parseCustomAttributeWithFallback(topModuleRefAttr, parser.getBuilder().getType<::mlir::NoneType>())) {
    return ::mlir::failure();
  }
  if (topModuleRefAttr) result.getOrAddProperties<InstanceHierarchyOp::Properties>().topModuleRef = topModuleRefAttr;

  ::mlir::OptionalParseResult parseResultinstNameAttr =
    parser.parseOptionalAttribute(instNameAttr, parser.getBuilder().getType<::mlir::NoneType>());
  if (parseResultinstNameAttr.has_value() && failed(*parseResultinstNameAttr))
    return ::mlir::failure();
  if (parseResultinstNameAttr.has_value() && succeeded(*parseResultinstNameAttr))
  if (instNameAttr) result.getOrAddProperties<InstanceHierarchyOp::Properties>().instName = instNameAttr;
  if (instNameAttr) {
  }

  if (parser.parseRegion(*bodyRegion))
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
  result.addRegion(std::move(bodyRegion));
  return ::mlir::success();
}

void InstanceHierarchyOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter.printAttributeWithoutType(getTopModuleRefAttr());
  if (getInstNameAttr()) {
    _odsPrinter << ' ';
    _odsPrinter.printAttributeWithoutType(getInstNameAttr());
  }
  _odsPrinter << ' ';
  _odsPrinter.printRegion(getBody());
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("topModuleRef");
  elidedAttrs.push_back("instName");
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
}


} // namespace circt::msft
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::msft::InstanceHierarchyOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::msft::detail::InstanceHierarchyOpGenericAdaptorBase::Properties)

namespace circt::msft {


//===----------------------------------------------------------------------===//
// ::circt::msft::LinearOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

LinearOpGenericAdaptorBase::LinearOpGenericAdaptorBase(LinearOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}


} // namespace detail
LinearOpAdaptor::LinearOpAdaptor(LinearOp op) : LinearOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult LinearOpAdaptor::verify(::mlir::Location loc) {
  return ::mlir::success();
}

std::pair<unsigned, unsigned> LinearOp::getODSResultIndexAndLength(unsigned index) {
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

::llvm::LogicalResult LinearOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }
      return ::mlir::success();
}

::mlir::Attribute LinearOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code LinearOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine();
}

std::optional<mlir::Attribute> LinearOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
  return std::nullopt;
}

void LinearOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
}

void LinearOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
}

::llvm::LogicalResult LinearOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    return ::mlir::success();
}

void LinearOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange outs, ::mlir::Value clock) {
  odsState.addOperands(clock);
  (void)odsState.addRegion();
  odsState.addTypes(outs);
}

LinearOp LinearOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange outs, ::mlir::Value clock) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(outs)>(outs), std::forward<decltype(clock)>(clock));
  auto __res__ = ::llvm::dyn_cast<LinearOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

LinearOp LinearOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange outs, ::mlir::Value clock) {
  return create(builder, builder.getLoc(), std::forward<decltype(outs)>(outs), std::forward<decltype(clock)>(clock));
}

void LinearOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  for (unsigned i = 0; i != 1; ++i)
    (void)odsState.addRegion();
  odsState.addTypes(resultTypes);
}

LinearOp LinearOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<LinearOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

LinearOp LinearOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void LinearOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  for (unsigned i = 0; i != 1; ++i)
    (void)odsState.addRegion();
  odsState.addTypes(resultTypes);
}

LinearOp LinearOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<LinearOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

LinearOp LinearOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult LinearOp::verifyInvariantsImpl() {
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_MSFT1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_MSFT2(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;

    for (auto &region : ::llvm::MutableArrayRef((*this)->getRegion(0)))
      if (::mlir::failed(__mlir_ods_local_region_constraint_MSFT1(*this, region, "datapath", index++)))
        return ::mlir::failure();
  }
  return ::mlir::success();
}

::llvm::LogicalResult LinearOp::verifyInvariants() {
  if(::mlir::succeeded(verifyInvariantsImpl()) && ::mlir::succeeded(verify()))
    return ::mlir::success();
  return ::mlir::failure();
}

::mlir::ParseResult LinearOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::OpAsmParser::UnresolvedOperand clockRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> clockOperands(&clockRawOperand, 1);  ::llvm::SMLoc clockOperandsLoc;
  (void)clockOperandsLoc;
  ::llvm::SmallVector<::mlir::Type, 1> outsTypes;
  std::unique_ptr<::mlir::Region> datapathRegion = std::make_unique<::mlir::Region>();
  if (parser.parseKeyword("clock"))
    return ::mlir::failure();

  clockOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(clockRawOperand))
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

  if (parser.parseTypeList(outsTypes))
    return ::mlir::failure();

  if (parser.parseRegion(*datapathRegion))
    return ::mlir::failure();

  ensureTerminator(*datapathRegion, parser.getBuilder(), result.location);
  result.addRegion(std::move(datapathRegion));
  ::mlir::Type odsBuildableType0 = parser.getBuilder().getType<::circt::seq::ClockType>();
  result.addTypes(outsTypes);
  if (parser.resolveOperands(clockOperands, odsBuildableType0, clockOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void LinearOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ' << "clock";
  _odsPrinter << ' ';
  _odsPrinter << getClock();
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
  _odsPrinter << getOuts().getTypes();
  _odsPrinter << ' ';

  {
    bool printTerminator = true;
    if (auto *term = getDatapath().empty() ? nullptr : getDatapath().begin()->getTerminator()) {
      printTerminator = !term->getAttrDictionary().empty() ||
                        term->getNumOperands() != 0 ||
                        term->getNumResults() != 0;
    }
    _odsPrinter.printRegion(getDatapath(), /*printEntryBlockArgs=*/true,
      /*printBlockTerminators=*/printTerminator);
  }
}


} // namespace circt::msft
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::msft::LinearOp)

namespace circt::msft {


//===----------------------------------------------------------------------===//
// ::circt::msft::OutputOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

OutputOpGenericAdaptorBase::OutputOpGenericAdaptorBase(OutputOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

std::pair<unsigned, unsigned> OutputOpGenericAdaptorBase::getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
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
OutputOpAdaptor::OutputOpAdaptor(OutputOp op) : OutputOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult OutputOpAdaptor::verify(::mlir::Location loc) {
  return ::mlir::success();
}

std::pair<unsigned, unsigned> OutputOp::getODSOperandIndexAndLength(unsigned index) {
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

::mlir::MutableOperandRange OutputOp::getOperandsMutable() {
  auto range = getODSOperandIndexAndLength(0);
  auto mutableRange = ::mlir::MutableOperandRange(getOperation(), range.first, range.second);
  return mutableRange;
}

::llvm::LogicalResult OutputOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }
      return ::mlir::success();
}

::mlir::Attribute OutputOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code OutputOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine();
}

std::optional<mlir::Attribute> OutputOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
  return std::nullopt;
}

void OutputOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
}

void OutputOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
}

::llvm::LogicalResult OutputOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    return ::mlir::success();
}

OutputOp OutputOp::create(::mlir::OpBuilder &builder, ::mlir::Location location) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__);
  auto __res__ = ::llvm::dyn_cast<OutputOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

OutputOp OutputOp::create(::mlir::ImplicitLocOpBuilder &builder) {
  return create(builder, builder.getLoc());
}

void OutputOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands) {
  odsState.addOperands(operands);
}

OutputOp OutputOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands));
  auto __res__ = ::llvm::dyn_cast<OutputOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

OutputOp OutputOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands));
}

void OutputOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

OutputOp OutputOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<OutputOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

OutputOp OutputOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void OutputOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

OutputOp OutputOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<OutputOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

OutputOp OutputOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult OutputOp::verifyInvariantsImpl() {
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_MSFT2(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult OutputOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult OutputOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
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

void OutputOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
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

void OutputOp::getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects) {
}


} // namespace circt::msft
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::msft::OutputOp)

namespace circt::msft {


//===----------------------------------------------------------------------===//
// ::circt::msft::PDMulticycleOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

PDMulticycleOpGenericAdaptorBase::PDMulticycleOpGenericAdaptorBase(PDMulticycleOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::llvm::StringRef PDMulticycleOpGenericAdaptorBase::getSource() {
  auto attr = getSourceAttr();
  return attr.getValue();
}

::llvm::StringRef PDMulticycleOpGenericAdaptorBase::getDest() {
  auto attr = getDestAttr();
  return attr.getValue();
}

uint32_t PDMulticycleOpGenericAdaptorBase::getCycles() {
  auto attr = getCyclesAttr();
  return attr.getValue().getZExtValue();
}


} // namespace detail
PDMulticycleOpAdaptor::PDMulticycleOpAdaptor(PDMulticycleOp op) : PDMulticycleOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult PDMulticycleOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_cycles = getProperties().cycles; (void)tblgen_cycles;
  if (!tblgen_cycles) return emitError(loc, "'msft.pd.multicycle' op requires attribute 'cycles'");
  auto tblgen_dest = getProperties().dest; (void)tblgen_dest;
  if (!tblgen_dest) return emitError(loc, "'msft.pd.multicycle' op requires attribute 'dest'");
  auto tblgen_source = getProperties().source; (void)tblgen_source;
  if (!tblgen_source) return emitError(loc, "'msft.pd.multicycle' op requires attribute 'source'");

  if (tblgen_source && !((::llvm::isa<::mlir::FlatSymbolRefAttr>(tblgen_source))))
    return emitError(loc, "'msft.pd.multicycle' op attribute 'source' failed to satisfy constraint: flat symbol reference attribute");

  if (tblgen_dest && !((::llvm::isa<::mlir::FlatSymbolRefAttr>(tblgen_dest))))
    return emitError(loc, "'msft.pd.multicycle' op attribute 'dest' failed to satisfy constraint: flat symbol reference attribute");

  if (tblgen_cycles && !((((::llvm::isa<::mlir::IntegerAttr>(tblgen_cycles))) && ((::llvm::cast<::mlir::IntegerAttr>(tblgen_cycles).getType().isSignlessInteger(32)))) && ((::llvm::cast<::mlir::IntegerAttr>(tblgen_cycles).getInt() >= 1))))
    return emitError(loc, "'msft.pd.multicycle' op attribute 'cycles' failed to satisfy constraint: 32-bit signless integer attribute whose minimum value is 1");
  return ::mlir::success();
}

::llvm::LogicalResult PDMulticycleOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.cycles;
       auto attr = dict.get("cycles");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `cycles` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.dest;
       auto attr = dict.get("dest");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `dest` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.source;
       auto attr = dict.get("source");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `source` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  return ::mlir::success();
}

::mlir::Attribute PDMulticycleOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.cycles;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("cycles",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.dest;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("dest",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.source;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("source",
                                       propStorage));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code PDMulticycleOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.cycles.getAsOpaquePointer()), 
    llvm::hash_value(prop.dest.getAsOpaquePointer()), 
    llvm::hash_value(prop.source.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> PDMulticycleOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "cycles")
      return prop.cycles;

    if (name == "dest")
      return prop.dest;

    if (name == "source")
      return prop.source;
  return std::nullopt;
}

void PDMulticycleOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "cycles") {
       prop.cycles = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.cycles)>>(value);
       return;
    }

    if (name == "dest") {
       prop.dest = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.dest)>>(value);
       return;
    }

    if (name == "source") {
       prop.source = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.source)>>(value);
       return;
    }
}

void PDMulticycleOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.cycles) attrs.append("cycles", prop.cycles);

    if (prop.dest) attrs.append("dest", prop.dest);

    if (prop.source) attrs.append("source", prop.source);
}

::llvm::LogicalResult PDMulticycleOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getCyclesAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_MSFT5(attr, "cycles", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getDestAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_MSFT4(attr, "dest", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getSourceAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_MSFT4(attr, "source", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult PDMulticycleOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.cycles)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readAttribute(prop.dest)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readAttribute(prop.source)))
    return ::mlir::failure();
  return ::mlir::success();
}

void PDMulticycleOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.cycles);
  writer.writeAttribute(prop.dest);
  writer.writeAttribute(prop.source);
}

::llvm::StringRef PDMulticycleOp::getSource() {
  auto attr = getSourceAttr();
  return attr.getValue();
}

::llvm::StringRef PDMulticycleOp::getDest() {
  auto attr = getDestAttr();
  return attr.getValue();
}

uint32_t PDMulticycleOp::getCycles() {
  auto attr = getCyclesAttr();
  return attr.getValue().getZExtValue();
}

void PDMulticycleOp::setSource(::llvm::StringRef attrValue) {
  getProperties().source = ::mlir::SymbolRefAttr::get(::mlir::Builder((*this)->getContext()).getContext(), attrValue);
}

void PDMulticycleOp::setDest(::llvm::StringRef attrValue) {
  getProperties().dest = ::mlir::SymbolRefAttr::get(::mlir::Builder((*this)->getContext()).getContext(), attrValue);
}

void PDMulticycleOp::setCycles(uint32_t attrValue) {
  getProperties().cycles = ::mlir::Builder((*this)->getContext()).getIntegerAttr(::mlir::Builder((*this)->getContext()).getIntegerType(32), attrValue);
}

void PDMulticycleOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::FlatSymbolRefAttr source, ::mlir::FlatSymbolRefAttr dest, ::mlir::IntegerAttr cycles) {
  odsState.getOrAddProperties<Properties>().source = source;
  odsState.getOrAddProperties<Properties>().dest = dest;
  odsState.getOrAddProperties<Properties>().cycles = cycles;
}

PDMulticycleOp PDMulticycleOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::FlatSymbolRefAttr source, ::mlir::FlatSymbolRefAttr dest, ::mlir::IntegerAttr cycles) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(source)>(source), std::forward<decltype(dest)>(dest), std::forward<decltype(cycles)>(cycles));
  auto __res__ = ::llvm::dyn_cast<PDMulticycleOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

PDMulticycleOp PDMulticycleOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::FlatSymbolRefAttr source, ::mlir::FlatSymbolRefAttr dest, ::mlir::IntegerAttr cycles) {
  return create(builder, builder.getLoc(), std::forward<decltype(source)>(source), std::forward<decltype(dest)>(dest), std::forward<decltype(cycles)>(cycles));
}

void PDMulticycleOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::FlatSymbolRefAttr source, ::mlir::FlatSymbolRefAttr dest, ::mlir::IntegerAttr cycles) {
  odsState.getOrAddProperties<Properties>().source = source;
  odsState.getOrAddProperties<Properties>().dest = dest;
  odsState.getOrAddProperties<Properties>().cycles = cycles;
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

PDMulticycleOp PDMulticycleOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::FlatSymbolRefAttr source, ::mlir::FlatSymbolRefAttr dest, ::mlir::IntegerAttr cycles) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(source)>(source), std::forward<decltype(dest)>(dest), std::forward<decltype(cycles)>(cycles));
  auto __res__ = ::llvm::dyn_cast<PDMulticycleOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

PDMulticycleOp PDMulticycleOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::FlatSymbolRefAttr source, ::mlir::FlatSymbolRefAttr dest, ::mlir::IntegerAttr cycles) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(source)>(source), std::forward<decltype(dest)>(dest), std::forward<decltype(cycles)>(cycles));
}

void PDMulticycleOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::llvm::StringRef source, ::llvm::StringRef dest, uint32_t cycles) {
  odsState.getOrAddProperties<Properties>().source = ::mlir::SymbolRefAttr::get(odsBuilder.getContext(), source);
  odsState.getOrAddProperties<Properties>().dest = ::mlir::SymbolRefAttr::get(odsBuilder.getContext(), dest);
  odsState.getOrAddProperties<Properties>().cycles = odsBuilder.getIntegerAttr(odsBuilder.getIntegerType(32), cycles);
}

PDMulticycleOp PDMulticycleOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::llvm::StringRef source, ::llvm::StringRef dest, uint32_t cycles) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(source)>(source), std::forward<decltype(dest)>(dest), std::forward<decltype(cycles)>(cycles));
  auto __res__ = ::llvm::dyn_cast<PDMulticycleOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

PDMulticycleOp PDMulticycleOp::create(::mlir::ImplicitLocOpBuilder &builder, ::llvm::StringRef source, ::llvm::StringRef dest, uint32_t cycles) {
  return create(builder, builder.getLoc(), std::forward<decltype(source)>(source), std::forward<decltype(dest)>(dest), std::forward<decltype(cycles)>(cycles));
}

void PDMulticycleOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::llvm::StringRef source, ::llvm::StringRef dest, uint32_t cycles) {
  odsState.getOrAddProperties<Properties>().source = ::mlir::SymbolRefAttr::get(odsBuilder.getContext(), source);
  odsState.getOrAddProperties<Properties>().dest = ::mlir::SymbolRefAttr::get(odsBuilder.getContext(), dest);
  odsState.getOrAddProperties<Properties>().cycles = odsBuilder.getIntegerAttr(odsBuilder.getIntegerType(32), cycles);
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

PDMulticycleOp PDMulticycleOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::llvm::StringRef source, ::llvm::StringRef dest, uint32_t cycles) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(source)>(source), std::forward<decltype(dest)>(dest), std::forward<decltype(cycles)>(cycles));
  auto __res__ = ::llvm::dyn_cast<PDMulticycleOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

PDMulticycleOp PDMulticycleOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::llvm::StringRef source, ::llvm::StringRef dest, uint32_t cycles) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(source)>(source), std::forward<decltype(dest)>(dest), std::forward<decltype(cycles)>(cycles));
}

void PDMulticycleOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<PDMulticycleOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

PDMulticycleOp PDMulticycleOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<PDMulticycleOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

PDMulticycleOp PDMulticycleOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void PDMulticycleOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

PDMulticycleOp PDMulticycleOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<PDMulticycleOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

PDMulticycleOp PDMulticycleOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult PDMulticycleOp::verifyInvariantsImpl() {
  auto tblgen_cycles = getProperties().cycles; (void)tblgen_cycles;
  if (!tblgen_cycles) return emitOpError("requires attribute 'cycles'");
  auto tblgen_dest = getProperties().dest; (void)tblgen_dest;
  if (!tblgen_dest) return emitOpError("requires attribute 'dest'");
  auto tblgen_source = getProperties().source; (void)tblgen_source;
  if (!tblgen_source) return emitOpError("requires attribute 'source'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_MSFT4(*this, tblgen_source, "source")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_MSFT4(*this, tblgen_dest, "dest")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_MSFT5(*this, tblgen_cycles, "cycles")))
    return ::mlir::failure();
  return ::mlir::success();
}

::llvm::LogicalResult PDMulticycleOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult PDMulticycleOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::IntegerAttr cyclesAttr;
  ::mlir::FlatSymbolRefAttr sourceAttr;
  ::mlir::FlatSymbolRefAttr destAttr;

  if (parser.parseCustomAttributeWithFallback(cyclesAttr, parser.getBuilder().getIntegerType(32))) {
    return ::mlir::failure();
  }
  if (cyclesAttr) result.getOrAddProperties<PDMulticycleOp::Properties>().cycles = cyclesAttr;

  if (parser.parseCustomAttributeWithFallback(sourceAttr, parser.getBuilder().getType<::mlir::NoneType>())) {
    return ::mlir::failure();
  }
  if (sourceAttr) result.getOrAddProperties<PDMulticycleOp::Properties>().source = sourceAttr;
  if (parser.parseArrow())
    return ::mlir::failure();

  if (parser.parseCustomAttributeWithFallback(destAttr, parser.getBuilder().getType<::mlir::NoneType>())) {
    return ::mlir::failure();
  }
  if (destAttr) result.getOrAddProperties<PDMulticycleOp::Properties>().dest = destAttr;
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

void PDMulticycleOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter.printAttributeWithoutType(getCyclesAttr());
  _odsPrinter << ' ';
  _odsPrinter.printAttributeWithoutType(getSourceAttr());
  _odsPrinter << ' ' << "->";
  _odsPrinter << ' ';
  _odsPrinter.printAttributeWithoutType(getDestAttr());
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("cycles");
  elidedAttrs.push_back("source");
  elidedAttrs.push_back("dest");
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
}


} // namespace circt::msft
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::msft::PDMulticycleOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::msft::detail::PDMulticycleOpGenericAdaptorBase::Properties)

namespace circt::msft {


//===----------------------------------------------------------------------===//
// ::circt::msft::PDPhysLocationOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

PDPhysLocationOpGenericAdaptorBase::PDPhysLocationOpGenericAdaptorBase(PDPhysLocationOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::circt::msft::PhysLocationAttr PDPhysLocationOpGenericAdaptorBase::getLoc() {
  auto attr = getLocAttr();
  return ::llvm::cast<::circt::msft::PhysLocationAttr>(attr);
}

::std::optional< ::llvm::StringRef > PDPhysLocationOpGenericAdaptorBase::getSubPath() {
  auto attr = getSubPathAttr();
  return attr ? ::std::optional< ::llvm::StringRef >(attr.getValue()) : (::std::nullopt);
}

::std::optional< ::llvm::StringRef > PDPhysLocationOpGenericAdaptorBase::getRef() {
  auto attr = getRefAttr();
  return attr ? ::std::optional< ::llvm::StringRef >(attr.getValue()) : (::std::nullopt);
}


} // namespace detail
PDPhysLocationOpAdaptor::PDPhysLocationOpAdaptor(PDPhysLocationOp op) : PDPhysLocationOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult PDPhysLocationOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_loc = getProperties().loc; (void)tblgen_loc;
  if (!tblgen_loc) return emitError(loc, "'msft.pd.location' op requires attribute 'loc'");
  auto tblgen_ref = getProperties().ref; (void)tblgen_ref;
  auto tblgen_subPath = getProperties().subPath; (void)tblgen_subPath;

  if (tblgen_loc && !((::llvm::isa<::circt::msft::PhysLocationAttr>(tblgen_loc))))
    return emitError(loc, "'msft.pd.location' op attribute 'loc' failed to satisfy constraint: Descibes a physical location on a device");

  if (tblgen_subPath && !((::llvm::isa<::mlir::StringAttr>(tblgen_subPath))))
    return emitError(loc, "'msft.pd.location' op attribute 'subPath' failed to satisfy constraint: string attribute");

  if (tblgen_ref && !((::llvm::isa<::mlir::FlatSymbolRefAttr>(tblgen_ref))))
    return emitError(loc, "'msft.pd.location' op attribute 'ref' failed to satisfy constraint: flat symbol reference attribute");
  return ::mlir::success();
}

::llvm::LogicalResult PDPhysLocationOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.loc;
       auto attr = dict.get("loc");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `loc` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.ref;
       auto attr = dict.get("ref");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `ref` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.subPath;
       auto attr = dict.get("subPath");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `subPath` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  return ::mlir::success();
}

::mlir::Attribute PDPhysLocationOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.loc;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("loc",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.ref;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("ref",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.subPath;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("subPath",
                                       propStorage));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code PDPhysLocationOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.loc.getAsOpaquePointer()), 
    llvm::hash_value(prop.ref.getAsOpaquePointer()), 
    llvm::hash_value(prop.subPath.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> PDPhysLocationOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "loc")
      return prop.loc;

    if (name == "ref")
      return prop.ref;

    if (name == "subPath")
      return prop.subPath;
  return std::nullopt;
}

void PDPhysLocationOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "loc") {
       prop.loc = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.loc)>>(value);
       return;
    }

    if (name == "ref") {
       prop.ref = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.ref)>>(value);
       return;
    }

    if (name == "subPath") {
       prop.subPath = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.subPath)>>(value);
       return;
    }
}

void PDPhysLocationOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.loc) attrs.append("loc", prop.loc);

    if (prop.ref) attrs.append("ref", prop.ref);

    if (prop.subPath) attrs.append("subPath", prop.subPath);
}

::llvm::LogicalResult PDPhysLocationOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getLocAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_MSFT6(attr, "loc", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getRefAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_MSFT4(attr, "ref", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getSubPathAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_MSFT1(attr, "subPath", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult PDPhysLocationOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.loc)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readOptionalAttribute(prop.ref)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readOptionalAttribute(prop.subPath)))
    return ::mlir::failure();
  return ::mlir::success();
}

void PDPhysLocationOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.loc);

  writer.writeOptionalAttribute(prop.ref);

  writer.writeOptionalAttribute(prop.subPath);
}

::circt::msft::PhysLocationAttr PDPhysLocationOp::getLoc() {
  auto attr = getLocAttr();
  return ::llvm::cast<::circt::msft::PhysLocationAttr>(attr);
}

::std::optional< ::llvm::StringRef > PDPhysLocationOp::getSubPath() {
  auto attr = getSubPathAttr();
  return attr ? ::std::optional< ::llvm::StringRef >(attr.getValue()) : (::std::nullopt);
}

::std::optional< ::llvm::StringRef > PDPhysLocationOp::getRef() {
  auto attr = getRefAttr();
  return attr ? ::std::optional< ::llvm::StringRef >(attr.getValue()) : (::std::nullopt);
}

void PDPhysLocationOp::setSubPath(::std::optional<::llvm::StringRef> attrValue) {
    auto &odsProp = getProperties().subPath;
    if (attrValue)
      odsProp = ::mlir::Builder((*this)->getContext()).getStringAttr(*attrValue);
    else
      odsProp = nullptr;
}

void PDPhysLocationOp::setRef(::std::optional<::llvm::StringRef> attrValue) {
    auto &odsProp = getProperties().ref;
    if (attrValue)
      odsProp = ::mlir::SymbolRefAttr::get(::mlir::Builder((*this)->getContext()).getContext(), *attrValue);
    else
      odsProp = nullptr;
}

void PDPhysLocationOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::circt::msft::PhysLocationAttr loc, /*optional*/::mlir::StringAttr subPath, /*optional*/::mlir::FlatSymbolRefAttr ref) {
  odsState.getOrAddProperties<Properties>().loc = loc;
  if (subPath) {
    odsState.getOrAddProperties<Properties>().subPath = subPath;
  }
  if (ref) {
    odsState.getOrAddProperties<Properties>().ref = ref;
  }
}

PDPhysLocationOp PDPhysLocationOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::circt::msft::PhysLocationAttr loc, /*optional*/::mlir::StringAttr subPath, /*optional*/::mlir::FlatSymbolRefAttr ref) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(loc)>(loc), std::forward<decltype(subPath)>(subPath), std::forward<decltype(ref)>(ref));
  auto __res__ = ::llvm::dyn_cast<PDPhysLocationOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

PDPhysLocationOp PDPhysLocationOp::create(::mlir::ImplicitLocOpBuilder &builder, ::circt::msft::PhysLocationAttr loc, /*optional*/::mlir::StringAttr subPath, /*optional*/::mlir::FlatSymbolRefAttr ref) {
  return create(builder, builder.getLoc(), std::forward<decltype(loc)>(loc), std::forward<decltype(subPath)>(subPath), std::forward<decltype(ref)>(ref));
}

void PDPhysLocationOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::circt::msft::PhysLocationAttr loc, /*optional*/::mlir::StringAttr subPath, /*optional*/::mlir::FlatSymbolRefAttr ref) {
  odsState.getOrAddProperties<Properties>().loc = loc;
  if (subPath) {
    odsState.getOrAddProperties<Properties>().subPath = subPath;
  }
  if (ref) {
    odsState.getOrAddProperties<Properties>().ref = ref;
  }
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

PDPhysLocationOp PDPhysLocationOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::circt::msft::PhysLocationAttr loc, /*optional*/::mlir::StringAttr subPath, /*optional*/::mlir::FlatSymbolRefAttr ref) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(loc)>(loc), std::forward<decltype(subPath)>(subPath), std::forward<decltype(ref)>(ref));
  auto __res__ = ::llvm::dyn_cast<PDPhysLocationOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

PDPhysLocationOp PDPhysLocationOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::circt::msft::PhysLocationAttr loc, /*optional*/::mlir::StringAttr subPath, /*optional*/::mlir::FlatSymbolRefAttr ref) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(loc)>(loc), std::forward<decltype(subPath)>(subPath), std::forward<decltype(ref)>(ref));
}

void PDPhysLocationOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<PDPhysLocationOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

PDPhysLocationOp PDPhysLocationOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<PDPhysLocationOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

PDPhysLocationOp PDPhysLocationOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void PDPhysLocationOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

PDPhysLocationOp PDPhysLocationOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<PDPhysLocationOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

PDPhysLocationOp PDPhysLocationOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult PDPhysLocationOp::verifyInvariantsImpl() {
  auto tblgen_loc = getProperties().loc; (void)tblgen_loc;
  if (!tblgen_loc) return emitOpError("requires attribute 'loc'");
  auto tblgen_ref = getProperties().ref; (void)tblgen_ref;
  auto tblgen_subPath = getProperties().subPath; (void)tblgen_subPath;

  if (::mlir::failed(__mlir_ods_local_attr_constraint_MSFT6(*this, tblgen_loc, "loc")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_MSFT1(*this, tblgen_subPath, "subPath")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_MSFT4(*this, tblgen_ref, "ref")))
    return ::mlir::failure();
  return ::mlir::success();
}

::llvm::LogicalResult PDPhysLocationOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult PDPhysLocationOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::FlatSymbolRefAttr refAttr;
  ::circt::msft::PhysLocationAttr locAttr;
  ::mlir::StringAttr subPathAttr;

  ::mlir::OptionalParseResult parseResultrefAttr =
    parser.parseOptionalAttribute(refAttr, parser.getBuilder().getType<::mlir::NoneType>());
  if (parseResultrefAttr.has_value() && failed(*parseResultrefAttr))
    return ::mlir::failure();
  if (parseResultrefAttr.has_value() && succeeded(*parseResultrefAttr))
  if (refAttr) result.getOrAddProperties<PDPhysLocationOp::Properties>().ref = refAttr;
  if (refAttr) {
  }
  {
    auto odsResult = parsePhysLoc(parser, locAttr);
    if (odsResult) return ::mlir::failure();
    result.getOrAddProperties<PDPhysLocationOp::Properties>().loc = locAttr;
  }
  if (::mlir::succeeded(parser.parseOptionalKeyword("path"))) {
  if (parser.parseColon())
    return ::mlir::failure();

  if (parser.parseCustomAttributeWithFallback(subPathAttr, parser.getBuilder().getType<::mlir::NoneType>())) {
    return ::mlir::failure();
  }
  if (subPathAttr) result.getOrAddProperties<PDPhysLocationOp::Properties>().subPath = subPathAttr;
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
  return ::mlir::success();
}

void PDPhysLocationOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  if (getRefAttr()) {
    _odsPrinter << ' ';
    _odsPrinter.printAttributeWithoutType(getRefAttr());
  }
  _odsPrinter << ' ';
  printPhysLoc(_odsPrinter, *this, getLocAttr());
  if (getSubPathAttr()) {
    _odsPrinter << ' ' << "path";
    _odsPrinter << ' ' << ":";
    _odsPrinter << ' ';
    _odsPrinter.printAttributeWithoutType(getSubPathAttr());
  }
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("ref");
  elidedAttrs.push_back("loc");
  elidedAttrs.push_back("subPath");
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
}


} // namespace circt::msft
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::msft::PDPhysLocationOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::msft::detail::PDPhysLocationOpGenericAdaptorBase::Properties)

namespace circt::msft {


//===----------------------------------------------------------------------===//
// ::circt::msft::PDPhysRegionOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

PDPhysRegionOpGenericAdaptorBase::PDPhysRegionOpGenericAdaptorBase(PDPhysRegionOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::llvm::StringRef PDPhysRegionOpGenericAdaptorBase::getPhysRegionRef() {
  auto attr = getPhysRegionRefAttr();
  return attr.getValue();
}

::std::optional< ::llvm::StringRef > PDPhysRegionOpGenericAdaptorBase::getSubPath() {
  auto attr = getSubPathAttr();
  return attr ? ::std::optional< ::llvm::StringRef >(attr.getValue()) : (::std::nullopt);
}

::std::optional< ::llvm::StringRef > PDPhysRegionOpGenericAdaptorBase::getRef() {
  auto attr = getRefAttr();
  return attr ? ::std::optional< ::llvm::StringRef >(attr.getValue()) : (::std::nullopt);
}


} // namespace detail
PDPhysRegionOpAdaptor::PDPhysRegionOpAdaptor(PDPhysRegionOp op) : PDPhysRegionOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult PDPhysRegionOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_physRegionRef = getProperties().physRegionRef; (void)tblgen_physRegionRef;
  if (!tblgen_physRegionRef) return emitError(loc, "'msft.pd.physregion' op requires attribute 'physRegionRef'");
  auto tblgen_ref = getProperties().ref; (void)tblgen_ref;
  auto tblgen_subPath = getProperties().subPath; (void)tblgen_subPath;

  if (tblgen_physRegionRef && !((::llvm::isa<::mlir::FlatSymbolRefAttr>(tblgen_physRegionRef))))
    return emitError(loc, "'msft.pd.physregion' op attribute 'physRegionRef' failed to satisfy constraint: flat symbol reference attribute");

  if (tblgen_subPath && !((::llvm::isa<::mlir::StringAttr>(tblgen_subPath))))
    return emitError(loc, "'msft.pd.physregion' op attribute 'subPath' failed to satisfy constraint: string attribute");

  if (tblgen_ref && !((::llvm::isa<::mlir::FlatSymbolRefAttr>(tblgen_ref))))
    return emitError(loc, "'msft.pd.physregion' op attribute 'ref' failed to satisfy constraint: flat symbol reference attribute");
  return ::mlir::success();
}

::llvm::LogicalResult PDPhysRegionOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.physRegionRef;
       auto attr = dict.get("physRegionRef");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `physRegionRef` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.ref;
       auto attr = dict.get("ref");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `ref` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.subPath;
       auto attr = dict.get("subPath");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `subPath` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  return ::mlir::success();
}

::mlir::Attribute PDPhysRegionOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.physRegionRef;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("physRegionRef",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.ref;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("ref",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.subPath;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("subPath",
                                       propStorage));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code PDPhysRegionOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.physRegionRef.getAsOpaquePointer()), 
    llvm::hash_value(prop.ref.getAsOpaquePointer()), 
    llvm::hash_value(prop.subPath.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> PDPhysRegionOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "physRegionRef")
      return prop.physRegionRef;

    if (name == "ref")
      return prop.ref;

    if (name == "subPath")
      return prop.subPath;
  return std::nullopt;
}

void PDPhysRegionOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "physRegionRef") {
       prop.physRegionRef = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.physRegionRef)>>(value);
       return;
    }

    if (name == "ref") {
       prop.ref = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.ref)>>(value);
       return;
    }

    if (name == "subPath") {
       prop.subPath = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.subPath)>>(value);
       return;
    }
}

void PDPhysRegionOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.physRegionRef) attrs.append("physRegionRef", prop.physRegionRef);

    if (prop.ref) attrs.append("ref", prop.ref);

    if (prop.subPath) attrs.append("subPath", prop.subPath);
}

::llvm::LogicalResult PDPhysRegionOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getPhysRegionRefAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_MSFT4(attr, "physRegionRef", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getRefAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_MSFT4(attr, "ref", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getSubPathAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_MSFT1(attr, "subPath", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult PDPhysRegionOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.physRegionRef)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readOptionalAttribute(prop.ref)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readOptionalAttribute(prop.subPath)))
    return ::mlir::failure();
  return ::mlir::success();
}

void PDPhysRegionOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.physRegionRef);

  writer.writeOptionalAttribute(prop.ref);

  writer.writeOptionalAttribute(prop.subPath);
}

::llvm::StringRef PDPhysRegionOp::getPhysRegionRef() {
  auto attr = getPhysRegionRefAttr();
  return attr.getValue();
}

::std::optional< ::llvm::StringRef > PDPhysRegionOp::getSubPath() {
  auto attr = getSubPathAttr();
  return attr ? ::std::optional< ::llvm::StringRef >(attr.getValue()) : (::std::nullopt);
}

::std::optional< ::llvm::StringRef > PDPhysRegionOp::getRef() {
  auto attr = getRefAttr();
  return attr ? ::std::optional< ::llvm::StringRef >(attr.getValue()) : (::std::nullopt);
}

void PDPhysRegionOp::setPhysRegionRef(::llvm::StringRef attrValue) {
  getProperties().physRegionRef = ::mlir::SymbolRefAttr::get(::mlir::Builder((*this)->getContext()).getContext(), attrValue);
}

void PDPhysRegionOp::setSubPath(::std::optional<::llvm::StringRef> attrValue) {
    auto &odsProp = getProperties().subPath;
    if (attrValue)
      odsProp = ::mlir::Builder((*this)->getContext()).getStringAttr(*attrValue);
    else
      odsProp = nullptr;
}

void PDPhysRegionOp::setRef(::std::optional<::llvm::StringRef> attrValue) {
    auto &odsProp = getProperties().ref;
    if (attrValue)
      odsProp = ::mlir::SymbolRefAttr::get(::mlir::Builder((*this)->getContext()).getContext(), *attrValue);
    else
      odsProp = nullptr;
}

void PDPhysRegionOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::FlatSymbolRefAttr physRegionRef, /*optional*/::mlir::StringAttr subPath, /*optional*/::mlir::FlatSymbolRefAttr ref) {
  odsState.getOrAddProperties<Properties>().physRegionRef = physRegionRef;
  if (subPath) {
    odsState.getOrAddProperties<Properties>().subPath = subPath;
  }
  if (ref) {
    odsState.getOrAddProperties<Properties>().ref = ref;
  }
}

PDPhysRegionOp PDPhysRegionOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::FlatSymbolRefAttr physRegionRef, /*optional*/::mlir::StringAttr subPath, /*optional*/::mlir::FlatSymbolRefAttr ref) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(physRegionRef)>(physRegionRef), std::forward<decltype(subPath)>(subPath), std::forward<decltype(ref)>(ref));
  auto __res__ = ::llvm::dyn_cast<PDPhysRegionOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

PDPhysRegionOp PDPhysRegionOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::FlatSymbolRefAttr physRegionRef, /*optional*/::mlir::StringAttr subPath, /*optional*/::mlir::FlatSymbolRefAttr ref) {
  return create(builder, builder.getLoc(), std::forward<decltype(physRegionRef)>(physRegionRef), std::forward<decltype(subPath)>(subPath), std::forward<decltype(ref)>(ref));
}

void PDPhysRegionOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::FlatSymbolRefAttr physRegionRef, /*optional*/::mlir::StringAttr subPath, /*optional*/::mlir::FlatSymbolRefAttr ref) {
  odsState.getOrAddProperties<Properties>().physRegionRef = physRegionRef;
  if (subPath) {
    odsState.getOrAddProperties<Properties>().subPath = subPath;
  }
  if (ref) {
    odsState.getOrAddProperties<Properties>().ref = ref;
  }
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

PDPhysRegionOp PDPhysRegionOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::FlatSymbolRefAttr physRegionRef, /*optional*/::mlir::StringAttr subPath, /*optional*/::mlir::FlatSymbolRefAttr ref) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(physRegionRef)>(physRegionRef), std::forward<decltype(subPath)>(subPath), std::forward<decltype(ref)>(ref));
  auto __res__ = ::llvm::dyn_cast<PDPhysRegionOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

PDPhysRegionOp PDPhysRegionOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::FlatSymbolRefAttr physRegionRef, /*optional*/::mlir::StringAttr subPath, /*optional*/::mlir::FlatSymbolRefAttr ref) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(physRegionRef)>(physRegionRef), std::forward<decltype(subPath)>(subPath), std::forward<decltype(ref)>(ref));
}

void PDPhysRegionOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::llvm::StringRef physRegionRef, /*optional*/::mlir::StringAttr subPath, /*optional*/::mlir::FlatSymbolRefAttr ref) {
  odsState.getOrAddProperties<Properties>().physRegionRef = ::mlir::SymbolRefAttr::get(odsBuilder.getContext(), physRegionRef);
  if (subPath) {
    odsState.getOrAddProperties<Properties>().subPath = subPath;
  }
  if (ref) {
    odsState.getOrAddProperties<Properties>().ref = ref;
  }
}

PDPhysRegionOp PDPhysRegionOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::llvm::StringRef physRegionRef, /*optional*/::mlir::StringAttr subPath, /*optional*/::mlir::FlatSymbolRefAttr ref) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(physRegionRef)>(physRegionRef), std::forward<decltype(subPath)>(subPath), std::forward<decltype(ref)>(ref));
  auto __res__ = ::llvm::dyn_cast<PDPhysRegionOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

PDPhysRegionOp PDPhysRegionOp::create(::mlir::ImplicitLocOpBuilder &builder, ::llvm::StringRef physRegionRef, /*optional*/::mlir::StringAttr subPath, /*optional*/::mlir::FlatSymbolRefAttr ref) {
  return create(builder, builder.getLoc(), std::forward<decltype(physRegionRef)>(physRegionRef), std::forward<decltype(subPath)>(subPath), std::forward<decltype(ref)>(ref));
}

void PDPhysRegionOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::llvm::StringRef physRegionRef, /*optional*/::mlir::StringAttr subPath, /*optional*/::mlir::FlatSymbolRefAttr ref) {
  odsState.getOrAddProperties<Properties>().physRegionRef = ::mlir::SymbolRefAttr::get(odsBuilder.getContext(), physRegionRef);
  if (subPath) {
    odsState.getOrAddProperties<Properties>().subPath = subPath;
  }
  if (ref) {
    odsState.getOrAddProperties<Properties>().ref = ref;
  }
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

PDPhysRegionOp PDPhysRegionOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::llvm::StringRef physRegionRef, /*optional*/::mlir::StringAttr subPath, /*optional*/::mlir::FlatSymbolRefAttr ref) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(physRegionRef)>(physRegionRef), std::forward<decltype(subPath)>(subPath), std::forward<decltype(ref)>(ref));
  auto __res__ = ::llvm::dyn_cast<PDPhysRegionOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

PDPhysRegionOp PDPhysRegionOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::llvm::StringRef physRegionRef, /*optional*/::mlir::StringAttr subPath, /*optional*/::mlir::FlatSymbolRefAttr ref) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(physRegionRef)>(physRegionRef), std::forward<decltype(subPath)>(subPath), std::forward<decltype(ref)>(ref));
}

void PDPhysRegionOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<PDPhysRegionOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

PDPhysRegionOp PDPhysRegionOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<PDPhysRegionOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

PDPhysRegionOp PDPhysRegionOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void PDPhysRegionOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

PDPhysRegionOp PDPhysRegionOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<PDPhysRegionOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

PDPhysRegionOp PDPhysRegionOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult PDPhysRegionOp::verifyInvariantsImpl() {
  auto tblgen_physRegionRef = getProperties().physRegionRef; (void)tblgen_physRegionRef;
  if (!tblgen_physRegionRef) return emitOpError("requires attribute 'physRegionRef'");
  auto tblgen_ref = getProperties().ref; (void)tblgen_ref;
  auto tblgen_subPath = getProperties().subPath; (void)tblgen_subPath;

  if (::mlir::failed(__mlir_ods_local_attr_constraint_MSFT4(*this, tblgen_physRegionRef, "physRegionRef")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_MSFT1(*this, tblgen_subPath, "subPath")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_MSFT4(*this, tblgen_ref, "ref")))
    return ::mlir::failure();
  return ::mlir::success();
}

::llvm::LogicalResult PDPhysRegionOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult PDPhysRegionOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::FlatSymbolRefAttr refAttr;
  ::mlir::FlatSymbolRefAttr physRegionRefAttr;
  ::mlir::StringAttr subPathAttr;

  ::mlir::OptionalParseResult parseResultrefAttr =
    parser.parseOptionalAttribute(refAttr, parser.getBuilder().getType<::mlir::NoneType>());
  if (parseResultrefAttr.has_value() && failed(*parseResultrefAttr))
    return ::mlir::failure();
  if (parseResultrefAttr.has_value() && succeeded(*parseResultrefAttr))
  if (refAttr) result.getOrAddProperties<PDPhysRegionOp::Properties>().ref = refAttr;
  if (refAttr) {
  }

  if (parser.parseCustomAttributeWithFallback(physRegionRefAttr, parser.getBuilder().getType<::mlir::NoneType>())) {
    return ::mlir::failure();
  }
  if (physRegionRefAttr) result.getOrAddProperties<PDPhysRegionOp::Properties>().physRegionRef = physRegionRefAttr;
  if (::mlir::succeeded(parser.parseOptionalKeyword("path"))) {
  if (parser.parseColon())
    return ::mlir::failure();

  if (parser.parseCustomAttributeWithFallback(subPathAttr, parser.getBuilder().getType<::mlir::NoneType>())) {
    return ::mlir::failure();
  }
  if (subPathAttr) result.getOrAddProperties<PDPhysRegionOp::Properties>().subPath = subPathAttr;
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
  return ::mlir::success();
}

void PDPhysRegionOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  if (getRefAttr()) {
    _odsPrinter << ' ';
    _odsPrinter.printAttributeWithoutType(getRefAttr());
  }
  _odsPrinter << ' ';
  _odsPrinter.printAttributeWithoutType(getPhysRegionRefAttr());
  if (getSubPathAttr()) {
    _odsPrinter << ' ' << "path";
    _odsPrinter << ' ' << ":";
    _odsPrinter << ' ';
    _odsPrinter.printAttributeWithoutType(getSubPathAttr());
  }
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("ref");
  elidedAttrs.push_back("physRegionRef");
  elidedAttrs.push_back("subPath");
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
}


} // namespace circt::msft
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::msft::PDPhysRegionOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::msft::detail::PDPhysRegionOpGenericAdaptorBase::Properties)

namespace circt::msft {


//===----------------------------------------------------------------------===//
// ::circt::msft::PDRegPhysLocationOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

PDRegPhysLocationOpGenericAdaptorBase::PDRegPhysLocationOpGenericAdaptorBase(PDRegPhysLocationOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::circt::msft::LocationVectorAttr PDRegPhysLocationOpGenericAdaptorBase::getLocs() {
  auto attr = getLocsAttr();
  return ::llvm::cast<::circt::msft::LocationVectorAttr>(attr);
}

::std::optional< ::llvm::StringRef > PDRegPhysLocationOpGenericAdaptorBase::getRef() {
  auto attr = getRefAttr();
  return attr ? ::std::optional< ::llvm::StringRef >(attr.getValue()) : (::std::nullopt);
}


} // namespace detail
PDRegPhysLocationOpAdaptor::PDRegPhysLocationOpAdaptor(PDRegPhysLocationOp op) : PDRegPhysLocationOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult PDRegPhysLocationOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_locs = getProperties().locs; (void)tblgen_locs;
  if (!tblgen_locs) return emitError(loc, "'msft.pd.reg_location' op requires attribute 'locs'");
  auto tblgen_ref = getProperties().ref; (void)tblgen_ref;

  if (tblgen_locs && !((::llvm::isa<::circt::msft::LocationVectorAttr>(tblgen_locs))))
    return emitError(loc, "'msft.pd.reg_location' op attribute 'locs' failed to satisfy constraint: Vector of optional locations corresponding to bits in a type");

  if (tblgen_ref && !((::llvm::isa<::mlir::FlatSymbolRefAttr>(tblgen_ref))))
    return emitError(loc, "'msft.pd.reg_location' op attribute 'ref' failed to satisfy constraint: flat symbol reference attribute");
  return ::mlir::success();
}

::llvm::LogicalResult PDRegPhysLocationOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.locs;
       auto attr = dict.get("locs");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `locs` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.ref;
       auto attr = dict.get("ref");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `ref` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  return ::mlir::success();
}

::mlir::Attribute PDRegPhysLocationOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.locs;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("locs",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.ref;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("ref",
                                       propStorage));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code PDRegPhysLocationOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.locs.getAsOpaquePointer()), 
    llvm::hash_value(prop.ref.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> PDRegPhysLocationOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "locs")
      return prop.locs;

    if (name == "ref")
      return prop.ref;
  return std::nullopt;
}

void PDRegPhysLocationOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "locs") {
       prop.locs = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.locs)>>(value);
       return;
    }

    if (name == "ref") {
       prop.ref = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.ref)>>(value);
       return;
    }
}

void PDRegPhysLocationOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.locs) attrs.append("locs", prop.locs);

    if (prop.ref) attrs.append("ref", prop.ref);
}

::llvm::LogicalResult PDRegPhysLocationOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getLocsAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_MSFT7(attr, "locs", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getRefAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_MSFT4(attr, "ref", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult PDRegPhysLocationOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.locs)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readOptionalAttribute(prop.ref)))
    return ::mlir::failure();
  return ::mlir::success();
}

void PDRegPhysLocationOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.locs);

  writer.writeOptionalAttribute(prop.ref);
}

::circt::msft::LocationVectorAttr PDRegPhysLocationOp::getLocs() {
  auto attr = getLocsAttr();
  return ::llvm::cast<::circt::msft::LocationVectorAttr>(attr);
}

::std::optional< ::llvm::StringRef > PDRegPhysLocationOp::getRef() {
  auto attr = getRefAttr();
  return attr ? ::std::optional< ::llvm::StringRef >(attr.getValue()) : (::std::nullopt);
}

void PDRegPhysLocationOp::setRef(::std::optional<::llvm::StringRef> attrValue) {
    auto &odsProp = getProperties().ref;
    if (attrValue)
      odsProp = ::mlir::SymbolRefAttr::get(::mlir::Builder((*this)->getContext()).getContext(), *attrValue);
    else
      odsProp = nullptr;
}

void PDRegPhysLocationOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::circt::msft::LocationVectorAttr locs, /*optional*/::mlir::FlatSymbolRefAttr ref) {
  odsState.getOrAddProperties<Properties>().locs = locs;
  if (ref) {
    odsState.getOrAddProperties<Properties>().ref = ref;
  }
}

PDRegPhysLocationOp PDRegPhysLocationOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::circt::msft::LocationVectorAttr locs, /*optional*/::mlir::FlatSymbolRefAttr ref) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(locs)>(locs), std::forward<decltype(ref)>(ref));
  auto __res__ = ::llvm::dyn_cast<PDRegPhysLocationOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

PDRegPhysLocationOp PDRegPhysLocationOp::create(::mlir::ImplicitLocOpBuilder &builder, ::circt::msft::LocationVectorAttr locs, /*optional*/::mlir::FlatSymbolRefAttr ref) {
  return create(builder, builder.getLoc(), std::forward<decltype(locs)>(locs), std::forward<decltype(ref)>(ref));
}

void PDRegPhysLocationOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::circt::msft::LocationVectorAttr locs, /*optional*/::mlir::FlatSymbolRefAttr ref) {
  odsState.getOrAddProperties<Properties>().locs = locs;
  if (ref) {
    odsState.getOrAddProperties<Properties>().ref = ref;
  }
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

PDRegPhysLocationOp PDRegPhysLocationOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::circt::msft::LocationVectorAttr locs, /*optional*/::mlir::FlatSymbolRefAttr ref) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(locs)>(locs), std::forward<decltype(ref)>(ref));
  auto __res__ = ::llvm::dyn_cast<PDRegPhysLocationOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

PDRegPhysLocationOp PDRegPhysLocationOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::circt::msft::LocationVectorAttr locs, /*optional*/::mlir::FlatSymbolRefAttr ref) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(locs)>(locs), std::forward<decltype(ref)>(ref));
}

void PDRegPhysLocationOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<PDRegPhysLocationOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

PDRegPhysLocationOp PDRegPhysLocationOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<PDRegPhysLocationOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

PDRegPhysLocationOp PDRegPhysLocationOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void PDRegPhysLocationOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

PDRegPhysLocationOp PDRegPhysLocationOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<PDRegPhysLocationOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

PDRegPhysLocationOp PDRegPhysLocationOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult PDRegPhysLocationOp::verifyInvariantsImpl() {
  auto tblgen_locs = getProperties().locs; (void)tblgen_locs;
  if (!tblgen_locs) return emitOpError("requires attribute 'locs'");
  auto tblgen_ref = getProperties().ref; (void)tblgen_ref;

  if (::mlir::failed(__mlir_ods_local_attr_constraint_MSFT7(*this, tblgen_locs, "locs")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_MSFT4(*this, tblgen_ref, "ref")))
    return ::mlir::failure();
  return ::mlir::success();
}

::llvm::LogicalResult PDRegPhysLocationOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult PDRegPhysLocationOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::FlatSymbolRefAttr refAttr;
  ::circt::msft::LocationVectorAttr locsAttr;
  if (::mlir::succeeded(parser.parseOptionalKeyword("ref"))) {

  if (parser.parseCustomAttributeWithFallback(refAttr, parser.getBuilder().getType<::mlir::NoneType>())) {
    return ::mlir::failure();
  }
  if (refAttr) result.getOrAddProperties<PDRegPhysLocationOp::Properties>().ref = refAttr;
  }
  {
    auto odsResult = parseListOptionalRegLocList(parser, locsAttr);
    if (odsResult) return ::mlir::failure();
    result.getOrAddProperties<PDRegPhysLocationOp::Properties>().locs = locsAttr;
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
  return ::mlir::success();
}

void PDRegPhysLocationOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  if (getRefAttr()) {
    _odsPrinter << ' ' << "ref";
    _odsPrinter << ' ';
    _odsPrinter.printAttributeWithoutType(getRefAttr());
  }
  _odsPrinter << ' ';
  printListOptionalRegLocList(_odsPrinter, *this, getLocsAttr());
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("ref");
  elidedAttrs.push_back("locs");
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
}


} // namespace circt::msft
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::msft::PDRegPhysLocationOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::msft::detail::PDRegPhysLocationOpGenericAdaptorBase::Properties)

namespace circt::msft {


//===----------------------------------------------------------------------===//
// ::circt::msft::PEOutputOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

PEOutputOpGenericAdaptorBase::PEOutputOpGenericAdaptorBase(PEOutputOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}


} // namespace detail
PEOutputOpAdaptor::PEOutputOpAdaptor(PEOutputOp op) : PEOutputOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult PEOutputOpAdaptor::verify(::mlir::Location loc) {
  return ::mlir::success();
}

::llvm::LogicalResult PEOutputOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }
      return ::mlir::success();
}

::mlir::Attribute PEOutputOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code PEOutputOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine();
}

std::optional<mlir::Attribute> PEOutputOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
  return std::nullopt;
}

void PEOutputOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
}

void PEOutputOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
}

::llvm::LogicalResult PEOutputOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    return ::mlir::success();
}

void PEOutputOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value output) {
  odsState.addOperands(output);
}

PEOutputOp PEOutputOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value output) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(output)>(output));
  auto __res__ = ::llvm::dyn_cast<PEOutputOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

PEOutputOp PEOutputOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value output) {
  return create(builder, builder.getLoc(), std::forward<decltype(output)>(output));
}

void PEOutputOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value output) {
  odsState.addOperands(output);
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

PEOutputOp PEOutputOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value output) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(output)>(output));
  auto __res__ = ::llvm::dyn_cast<PEOutputOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

PEOutputOp PEOutputOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value output) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(output)>(output));
}

void PEOutputOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

PEOutputOp PEOutputOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<PEOutputOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

PEOutputOp PEOutputOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void PEOutputOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

PEOutputOp PEOutputOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<PEOutputOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

PEOutputOp PEOutputOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult PEOutputOp::verifyInvariantsImpl() {
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_MSFT3(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult PEOutputOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult PEOutputOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::OpAsmParser::UnresolvedOperand outputRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> outputOperands(&outputRawOperand, 1);  ::llvm::SMLoc outputOperandsLoc;
  (void)outputOperandsLoc;
  ::mlir::Type outputRawType{};
  ::llvm::ArrayRef<::mlir::Type> outputTypes(&outputRawType, 1);

  outputOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(outputRawOperand))
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
    outputRawType = type;
  }
  if (parser.resolveOperands(outputOperands, outputTypes, outputOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void PEOutputOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter << getOutput();
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
  {
    auto type = getOutput().getType();
    if (auto validType = ::llvm::dyn_cast<::mlir::Type>(type))
      _odsPrinter.printStrippedAttrOrType(validType);
   else
     _odsPrinter << type;
  }
}


} // namespace circt::msft
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::msft::PEOutputOp)

namespace circt::msft {


//===----------------------------------------------------------------------===//
// ::circt::msft::SystolicArrayOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

SystolicArrayOpGenericAdaptorBase::SystolicArrayOpGenericAdaptorBase(SystolicArrayOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}


} // namespace detail
SystolicArrayOpAdaptor::SystolicArrayOpAdaptor(SystolicArrayOp op) : SystolicArrayOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult SystolicArrayOpAdaptor::verify(::mlir::Location loc) {
  return ::mlir::success();
}

::llvm::LogicalResult SystolicArrayOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }
      return ::mlir::success();
}

::mlir::Attribute SystolicArrayOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code SystolicArrayOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine();
}

std::optional<mlir::Attribute> SystolicArrayOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
  return std::nullopt;
}

void SystolicArrayOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
}

void SystolicArrayOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
}

::llvm::LogicalResult SystolicArrayOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    return ::mlir::success();
}

void SystolicArrayOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type peOutputs, ::mlir::Value rowInputs, ::mlir::Value colInputs) {
  odsState.addOperands(rowInputs);
  odsState.addOperands(colInputs);
  (void)odsState.addRegion();
  odsState.addTypes(peOutputs);
}

SystolicArrayOp SystolicArrayOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type peOutputs, ::mlir::Value rowInputs, ::mlir::Value colInputs) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(peOutputs)>(peOutputs), std::forward<decltype(rowInputs)>(rowInputs), std::forward<decltype(colInputs)>(colInputs));
  auto __res__ = ::llvm::dyn_cast<SystolicArrayOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SystolicArrayOp SystolicArrayOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type peOutputs, ::mlir::Value rowInputs, ::mlir::Value colInputs) {
  return create(builder, builder.getLoc(), std::forward<decltype(peOutputs)>(peOutputs), std::forward<decltype(rowInputs)>(rowInputs), std::forward<decltype(colInputs)>(colInputs));
}

void SystolicArrayOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value rowInputs, ::mlir::Value colInputs) {
  odsState.addOperands(rowInputs);
  odsState.addOperands(colInputs);
  (void)odsState.addRegion();
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

SystolicArrayOp SystolicArrayOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value rowInputs, ::mlir::Value colInputs) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(rowInputs)>(rowInputs), std::forward<decltype(colInputs)>(colInputs));
  auto __res__ = ::llvm::dyn_cast<SystolicArrayOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SystolicArrayOp SystolicArrayOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value rowInputs, ::mlir::Value colInputs) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(rowInputs)>(rowInputs), std::forward<decltype(colInputs)>(colInputs));
}

void SystolicArrayOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 2u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  for (unsigned i = 0; i != 1; ++i)
    (void)odsState.addRegion();
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

SystolicArrayOp SystolicArrayOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<SystolicArrayOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SystolicArrayOp SystolicArrayOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void SystolicArrayOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 2u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  for (unsigned i = 0; i != 1; ++i)
    (void)odsState.addRegion();
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

SystolicArrayOp SystolicArrayOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<SystolicArrayOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SystolicArrayOp SystolicArrayOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult SystolicArrayOp::verifyInvariantsImpl() {
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_MSFT4(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSOperands(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_MSFT4(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_MSFT5(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;

    for (auto &region : ::llvm::MutableArrayRef((*this)->getRegion(0)))
      if (::mlir::failed(__mlir_ods_local_region_constraint_MSFT1(*this, region, "pe", index++)))
        return ::mlir::failure();
  }
  return ::mlir::success();
}

::llvm::LogicalResult SystolicArrayOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::llvm::LogicalResult SystolicArrayOp::setPropertiesFromParsedAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
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


} // namespace circt::msft
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::msft::SystolicArrayOp)


#endif // GET_OP_CLASSES

