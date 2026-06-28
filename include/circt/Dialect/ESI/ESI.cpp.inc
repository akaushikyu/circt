/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Op Definitions                                                             *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: ESI.td                                                               *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

#ifdef GET_OP_LIST
#undef GET_OP_LIST

::circt::esi::AppIDHierNodeOp,
::circt::esi::AppIDHierRootOp,
::circt::esi::CallServiceDeclOp,
::circt::esi::ChannelBufferOp,
::circt::esi::ChannelServiceDeclOp,
::circt::esi::CompressedManifestOp,
::circt::esi::CosimFromHostEndpointOp,
::circt::esi::CosimToHostEndpointOp,
::circt::esi::CustomServiceDeclOp,
::circt::esi::ESIPureModuleInputOp,
::circt::esi::ESIPureModuleOp,
::circt::esi::ESIPureModuleOutputOp,
::circt::esi::ESIPureModuleParamOp,
::circt::esi::FIFOOp,
::circt::esi::FuncServiceDeclOp,
::circt::esi::HostMemServiceDeclOp,
::circt::esi::MMIOServiceDeclOp,
::circt::esi::NullSourceOp,
::circt::esi::PackBundleOp,
::circt::esi::PipelineStageOp,
::circt::esi::RandomAccessMemoryDeclOp,
::circt::esi::RequestConnectionOp,
::circt::esi::ServiceDeclPortOp,
::circt::esi::ServiceImplClientRecordOp,
::circt::esi::ServiceImplRecordOp,
::circt::esi::ServiceImplementConnReqOp,
::circt::esi::ServiceImplementReqOp,
::circt::esi::ServiceInstanceOp,
::circt::esi::ServiceRequestRecordOp,
::circt::esi::SnoopTransactionOp,
::circt::esi::SnoopValidReadyOp,
::circt::esi::SymbolConstantsOp,
::circt::esi::SymbolMetadataOp,
::circt::esi::TelemetryServiceDeclOp,
::circt::esi::UnpackBundleOp,
::circt::esi::UnwrapFIFOOp,
::circt::esi::UnwrapSVInterfaceOp,
::circt::esi::UnwrapValidOnlyOp,
::circt::esi::UnwrapValidReadyOp,
::circt::esi::UnwrapWindow,
::circt::esi::WrapFIFOOp,
::circt::esi::WrapSVInterfaceOp,
::circt::esi::WrapValidOnlyOp,
::circt::esi::WrapValidReadyOp,
::circt::esi::WrapWindow
#endif // GET_OP_LIST

#ifdef GET_OP_CLASSES
#undef GET_OP_CLASSES


//===----------------------------------------------------------------------===//
// Local Utility Method Definitions
//===----------------------------------------------------------------------===//


static ::llvm::LogicalResult __mlir_ods_local_type_constraint_ESI1(
    ::mlir::Operation *op, ::mlir::Type type, ::llvm::StringRef valueKind,
    unsigned valueIndex) {
  if (!((::llvm::isa<::circt::seq::ClockType>(type)))) {
    return op->emitOpError(valueKind) << " #" << valueIndex
        << " must be A type for clock-carrying wires, but got " << type;
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_type_constraint_ESI2(
    ::mlir::Operation *op, ::mlir::Type type, ::llvm::StringRef valueKind,
    unsigned valueIndex) {
  if (!((type.isSignlessInteger(1)))) {
    return op->emitOpError(valueKind) << " #" << valueIndex
        << " must be 1-bit signless integer, but got " << type;
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_type_constraint_ESI3(
    ::mlir::Operation *op, ::mlir::Type type, ::llvm::StringRef valueKind,
    unsigned valueIndex) {
  if (!((isa<::circt::esi::ChannelType>(type)))) {
    return op->emitOpError(valueKind) << " #" << valueIndex
        << " must be an ESI channel, but got " << type;
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_type_constraint_ESI4(
    ::mlir::Operation *op, ::mlir::Type type, ::llvm::StringRef valueKind,
    unsigned valueIndex) {
  if (!(!((::llvm::isa<::mlir::TokenType>(type))))) {
    return op->emitOpError(valueKind) << " #" << valueIndex
        << " must be any non-token type, but got " << type;
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_type_constraint_ESI5(
    ::mlir::Operation *op, ::mlir::Type type, ::llvm::StringRef valueKind,
    unsigned valueIndex) {
  if (!((isa<::circt::esi::ChannelType>(type)))) {
    return op->emitOpError(valueKind) << " #" << valueIndex
        << " must be variadic of an ESI channel, but got " << type;
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_type_constraint_ESI6(
    ::mlir::Operation *op, ::mlir::Type type, ::llvm::StringRef valueKind,
    unsigned valueIndex) {
  if (!((::llvm::isa<::circt::esi::ChannelBundleType>(type)))) {
    return op->emitOpError(valueKind) << " #" << valueIndex
        << " must be a bundle of channels, but got " << type;
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_type_constraint_ESI7(
    ::mlir::Operation *op, ::mlir::Type type, ::llvm::StringRef valueKind,
    unsigned valueIndex) {
  if (!(!((::llvm::isa<::mlir::TokenType>(type))))) {
    return op->emitOpError(valueKind) << " #" << valueIndex
        << " must be variadic of any non-token type, but got " << type;
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_type_constraint_ESI8(
    ::mlir::Operation *op, ::mlir::Type type, ::llvm::StringRef valueKind,
    unsigned valueIndex) {
  if (!((llvm::isa<::circt::sv::ModportType>(type)))) {
    return op->emitOpError(valueKind) << " #" << valueIndex
        << " must be sv.interface, but got " << type;
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_type_constraint_ESI9(
    ::mlir::Operation *op, ::mlir::Type type, ::llvm::StringRef valueKind,
    unsigned valueIndex) {
  if (!((::llvm::isa<::circt::esi::WindowType>(type)))) {
    return op->emitOpError(valueKind) << " #" << valueIndex
        << " must be a data window, but got " << type;
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_ESI1(
    ::mlir::Attribute attr, ::llvm::StringRef attrName, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  if (attr && !((::llvm::isa<::circt::esi::AppIDAttr>(attr))))
    return emitError() << "attribute '" << attrName
        << "' failed to satisfy constraint: An application relevant instance identifier";
  return ::mlir::success();
}
static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_ESI1(
    ::mlir::Operation *op, ::mlir::Attribute attr, ::llvm::StringRef attrName) {
  return __mlir_ods_local_attr_constraint_ESI1(attr, attrName, [op]() {
    return op->emitOpError();
  });
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_ESI2(
    ::mlir::Attribute attr, ::llvm::StringRef attrName, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  if (attr && !((::llvm::isa<::mlir::FlatSymbolRefAttr>(attr))))
    return emitError() << "attribute '" << attrName
        << "' failed to satisfy constraint: flat symbol reference attribute";
  return ::mlir::success();
}
static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_ESI2(
    ::mlir::Operation *op, ::mlir::Attribute attr, ::llvm::StringRef attrName) {
  return __mlir_ods_local_attr_constraint_ESI2(attr, attrName, [op]() {
    return op->emitOpError();
  });
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_ESI3(
    ::mlir::Attribute attr, ::llvm::StringRef attrName, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  if (attr && !((::llvm::isa<::mlir::StringAttr>(attr))))
    return emitError() << "attribute '" << attrName
        << "' failed to satisfy constraint: string attribute";
  return ::mlir::success();
}
static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_ESI3(
    ::mlir::Operation *op, ::mlir::Attribute attr, ::llvm::StringRef attrName) {
  return __mlir_ods_local_attr_constraint_ESI3(attr, attrName, [op]() {
    return op->emitOpError();
  });
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_ESI4(
    ::mlir::Attribute attr, ::llvm::StringRef attrName, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  if (attr && !((((::llvm::isa<::mlir::IntegerAttr>(attr))) && ((::llvm::cast<::mlir::IntegerAttr>(attr).getType().isSignlessInteger(64)))) && ((::llvm::cast<::mlir::IntegerAttr>(attr).getInt() >= 1))))
    return emitError() << "attribute '" << attrName
        << "' failed to satisfy constraint: 64-bit signless integer attribute whose minimum value is 1";
  return ::mlir::success();
}
static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_ESI4(
    ::mlir::Operation *op, ::mlir::Attribute attr, ::llvm::StringRef attrName) {
  return __mlir_ods_local_attr_constraint_ESI4(attr, attrName, [op]() {
    return op->emitOpError();
  });
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_ESI5(
    ::mlir::Attribute attr, ::llvm::StringRef attrName, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  if (attr && !((::llvm::isa<::circt::esi::BlobAttr>(attr))))
    return emitError() << "attribute '" << attrName
        << "' failed to satisfy constraint: A binary blob";
  return ::mlir::success();
}
static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_ESI5(
    ::mlir::Operation *op, ::mlir::Attribute attr, ::llvm::StringRef attrName) {
  return __mlir_ods_local_attr_constraint_ESI5(attr, attrName, [op]() {
    return op->emitOpError();
  });
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_ESI6(
    ::mlir::Attribute attr, ::llvm::StringRef attrName, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  if (attr && !(((::llvm::isa<::mlir::TypeAttr>(attr))) && ((::llvm::isa<::mlir::Type>(::llvm::cast<::mlir::TypeAttr>(attr).getValue()))) && ((true))))
    return emitError() << "attribute '" << attrName
        << "' failed to satisfy constraint: any type attribute";
  return ::mlir::success();
}
static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_ESI6(
    ::mlir::Operation *op, ::mlir::Attribute attr, ::llvm::StringRef attrName) {
  return __mlir_ods_local_attr_constraint_ESI6(attr, attrName, [op]() {
    return op->emitOpError();
  });
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_ESI7(
    ::mlir::Attribute attr, ::llvm::StringRef attrName, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  if (attr && !(((::llvm::isa<::mlir::IntegerAttr>(attr))) && ((::llvm::cast<::mlir::IntegerAttr>(attr).getType().isSignlessInteger(64)))))
    return emitError() << "attribute '" << attrName
        << "' failed to satisfy constraint: 64-bit signless integer attribute";
  return ::mlir::success();
}
static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_ESI7(
    ::mlir::Operation *op, ::mlir::Attribute attr, ::llvm::StringRef attrName) {
  return __mlir_ods_local_attr_constraint_ESI7(attr, attrName, [op]() {
    return op->emitOpError();
  });
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_ESI8(
    ::mlir::Attribute attr, ::llvm::StringRef attrName, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  if (attr && !((::llvm::isa<::circt::hw::InnerRefAttr>(attr))))
    return emitError() << "attribute '" << attrName
        << "' failed to satisfy constraint: Refer to a name inside a module";
  return ::mlir::success();
}
static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_ESI8(
    ::mlir::Operation *op, ::mlir::Attribute attr, ::llvm::StringRef attrName) {
  return __mlir_ods_local_attr_constraint_ESI8(attr, attrName, [op]() {
    return op->emitOpError();
  });
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_ESI9(
    ::mlir::Attribute attr, ::llvm::StringRef attrName, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  if (attr && !(((::llvm::isa<::mlir::TypeAttr>(attr))) && ((::llvm::isa<::circt::esi::ChannelBundleType>(::llvm::cast<::mlir::TypeAttr>(attr).getValue()))) && ((::llvm::isa<::circt::esi::ChannelBundleType>(::llvm::cast<::mlir::TypeAttr>(attr).getValue())))))
    return emitError() << "attribute '" << attrName
        << "' failed to satisfy constraint: type attribute of a bundle of channels";
  return ::mlir::success();
}
static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_ESI9(
    ::mlir::Operation *op, ::mlir::Attribute attr, ::llvm::StringRef attrName) {
  return __mlir_ods_local_attr_constraint_ESI9(attr, attrName, [op]() {
    return op->emitOpError();
  });
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_ESI10(
    ::mlir::Attribute attr, ::llvm::StringRef attrName, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  if (attr && !(((::llvm::isa<::mlir::ArrayAttr>(attr))) && (::llvm::all_of(::llvm::cast<::mlir::ArrayAttr>(attr), [&](::mlir::Attribute attr) { return attr && ((::llvm::isa<::circt::esi::AppIDAttr>(attr))); }))))
    return emitError() << "attribute '" << attrName
        << "' failed to satisfy constraint: Array of AppIDs";
  return ::mlir::success();
}
static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_ESI10(
    ::mlir::Operation *op, ::mlir::Attribute attr, ::llvm::StringRef attrName) {
  return __mlir_ods_local_attr_constraint_ESI10(attr, attrName, [op]() {
    return op->emitOpError();
  });
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_ESI11(
    ::mlir::Attribute attr, ::llvm::StringRef attrName, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  if (attr && !((::llvm::isa<::mlir::DictionaryAttr>(attr))))
    return emitError() << "attribute '" << attrName
        << "' failed to satisfy constraint: dictionary of named attribute values";
  return ::mlir::success();
}
static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_ESI11(
    ::mlir::Operation *op, ::mlir::Attribute attr, ::llvm::StringRef attrName) {
  return __mlir_ods_local_attr_constraint_ESI11(attr, attrName, [op]() {
    return op->emitOpError();
  });
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_ESI12(
    ::mlir::Attribute attr, ::llvm::StringRef attrName, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  if (attr && !((::llvm::isa<::mlir::UnitAttr>(attr))))
    return emitError() << "attribute '" << attrName
        << "' failed to satisfy constraint: unit attribute";
  return ::mlir::success();
}
static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_ESI12(
    ::mlir::Operation *op, ::mlir::Attribute attr, ::llvm::StringRef attrName) {
  return __mlir_ods_local_attr_constraint_ESI12(attr, attrName, [op]() {
    return op->emitOpError();
  });
}

static ::llvm::LogicalResult __mlir_ods_local_region_constraint_ESI1(
    ::mlir::Operation *op, ::mlir::Region &region, ::llvm::StringRef regionName,
    unsigned regionIndex) {
  if (!((::llvm::hasNItems(region, 1)))) {
    return op->emitOpError("region #") << regionIndex
        << (regionName.empty() ? " " : " ('" + regionName + "') ")
        << "failed to verify constraint: region with 1 blocks";
  }
  return ::mlir::success();
}
namespace circt::esi {


//===----------------------------------------------------------------------===//
// ::circt::esi::AppIDHierNodeOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

AppIDHierNodeOpGenericAdaptorBase::AppIDHierNodeOpGenericAdaptorBase(AppIDHierNodeOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::circt::esi::AppIDAttr AppIDHierNodeOpGenericAdaptorBase::getAppID() {
  auto attr = getAppIDAttr();
  return ::llvm::cast<::circt::esi::AppIDAttr>(attr);
}

::llvm::StringRef AppIDHierNodeOpGenericAdaptorBase::getModuleRef() {
  auto attr = getModuleRefAttr();
  return attr.getValue();
}


} // namespace detail
AppIDHierNodeOpAdaptor::AppIDHierNodeOpAdaptor(AppIDHierNodeOp op) : AppIDHierNodeOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult AppIDHierNodeOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_appID = getProperties().appID; (void)tblgen_appID;
  if (!tblgen_appID) return emitError(loc, "'esi.manifest.hier_node' op requires attribute 'appID'");
  auto tblgen_moduleRef = getProperties().moduleRef; (void)tblgen_moduleRef;
  if (!tblgen_moduleRef) return emitError(loc, "'esi.manifest.hier_node' op requires attribute 'moduleRef'");

  if (tblgen_appID && !((::llvm::isa<::circt::esi::AppIDAttr>(tblgen_appID))))
    return emitError(loc, "'esi.manifest.hier_node' op attribute 'appID' failed to satisfy constraint: An application relevant instance identifier");

  if (tblgen_moduleRef && !((::llvm::isa<::mlir::FlatSymbolRefAttr>(tblgen_moduleRef))))
    return emitError(loc, "'esi.manifest.hier_node' op attribute 'moduleRef' failed to satisfy constraint: flat symbol reference attribute");
  return ::mlir::success();
}

::llvm::LogicalResult AppIDHierNodeOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.appID;
       auto attr = dict.get("appID");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `appID` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.moduleRef;
       auto attr = dict.get("moduleRef");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `moduleRef` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  return ::mlir::success();
}

::mlir::Attribute AppIDHierNodeOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.appID;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("appID",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.moduleRef;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("moduleRef",
                                       propStorage));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code AppIDHierNodeOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.appID.getAsOpaquePointer()), 
    llvm::hash_value(prop.moduleRef.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> AppIDHierNodeOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "appID")
      return prop.appID;

    if (name == "moduleRef")
      return prop.moduleRef;
  return std::nullopt;
}

void AppIDHierNodeOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "appID") {
       prop.appID = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.appID)>>(value);
       return;
    }

    if (name == "moduleRef") {
       prop.moduleRef = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.moduleRef)>>(value);
       return;
    }
}

void AppIDHierNodeOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.appID) attrs.append("appID", prop.appID);

    if (prop.moduleRef) attrs.append("moduleRef", prop.moduleRef);
}

::llvm::LogicalResult AppIDHierNodeOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getAppIDAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_ESI1(attr, "appID", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getModuleRefAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_ESI2(attr, "moduleRef", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult AppIDHierNodeOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.appID)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readAttribute(prop.moduleRef)))
    return ::mlir::failure();
  return ::mlir::success();
}

void AppIDHierNodeOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.appID);
  writer.writeAttribute(prop.moduleRef);
}

::circt::esi::AppIDAttr AppIDHierNodeOp::getAppID() {
  auto attr = getAppIDAttr();
  return ::llvm::cast<::circt::esi::AppIDAttr>(attr);
}

::llvm::StringRef AppIDHierNodeOp::getModuleRef() {
  auto attr = getModuleRefAttr();
  return attr.getValue();
}

void AppIDHierNodeOp::setModuleRef(::llvm::StringRef attrValue) {
  getProperties().moduleRef = ::mlir::SymbolRefAttr::get(::mlir::Builder((*this)->getContext()).getContext(), attrValue);
}

void AppIDHierNodeOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::circt::esi::AppIDAttr appID, ::mlir::FlatSymbolRefAttr moduleRef) {
  odsState.getOrAddProperties<Properties>().appID = appID;
  odsState.getOrAddProperties<Properties>().moduleRef = moduleRef;
  (void)odsState.addRegion();
}

AppIDHierNodeOp AppIDHierNodeOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::circt::esi::AppIDAttr appID, ::mlir::FlatSymbolRefAttr moduleRef) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(appID)>(appID), std::forward<decltype(moduleRef)>(moduleRef));
  auto __res__ = ::llvm::dyn_cast<AppIDHierNodeOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

AppIDHierNodeOp AppIDHierNodeOp::create(::mlir::ImplicitLocOpBuilder &builder, ::circt::esi::AppIDAttr appID, ::mlir::FlatSymbolRefAttr moduleRef) {
  return create(builder, builder.getLoc(), std::forward<decltype(appID)>(appID), std::forward<decltype(moduleRef)>(moduleRef));
}

void AppIDHierNodeOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::circt::esi::AppIDAttr appID, ::mlir::FlatSymbolRefAttr moduleRef) {
  odsState.getOrAddProperties<Properties>().appID = appID;
  odsState.getOrAddProperties<Properties>().moduleRef = moduleRef;
  (void)odsState.addRegion();
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

AppIDHierNodeOp AppIDHierNodeOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::circt::esi::AppIDAttr appID, ::mlir::FlatSymbolRefAttr moduleRef) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(appID)>(appID), std::forward<decltype(moduleRef)>(moduleRef));
  auto __res__ = ::llvm::dyn_cast<AppIDHierNodeOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

AppIDHierNodeOp AppIDHierNodeOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::circt::esi::AppIDAttr appID, ::mlir::FlatSymbolRefAttr moduleRef) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(appID)>(appID), std::forward<decltype(moduleRef)>(moduleRef));
}

void AppIDHierNodeOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::circt::esi::AppIDAttr appID, ::llvm::StringRef moduleRef) {
  odsState.getOrAddProperties<Properties>().appID = appID;
  odsState.getOrAddProperties<Properties>().moduleRef = ::mlir::SymbolRefAttr::get(odsBuilder.getContext(), moduleRef);
  (void)odsState.addRegion();
}

AppIDHierNodeOp AppIDHierNodeOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::circt::esi::AppIDAttr appID, ::llvm::StringRef moduleRef) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(appID)>(appID), std::forward<decltype(moduleRef)>(moduleRef));
  auto __res__ = ::llvm::dyn_cast<AppIDHierNodeOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

AppIDHierNodeOp AppIDHierNodeOp::create(::mlir::ImplicitLocOpBuilder &builder, ::circt::esi::AppIDAttr appID, ::llvm::StringRef moduleRef) {
  return create(builder, builder.getLoc(), std::forward<decltype(appID)>(appID), std::forward<decltype(moduleRef)>(moduleRef));
}

void AppIDHierNodeOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::circt::esi::AppIDAttr appID, ::llvm::StringRef moduleRef) {
  odsState.getOrAddProperties<Properties>().appID = appID;
  odsState.getOrAddProperties<Properties>().moduleRef = ::mlir::SymbolRefAttr::get(odsBuilder.getContext(), moduleRef);
  (void)odsState.addRegion();
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

AppIDHierNodeOp AppIDHierNodeOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::circt::esi::AppIDAttr appID, ::llvm::StringRef moduleRef) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(appID)>(appID), std::forward<decltype(moduleRef)>(moduleRef));
  auto __res__ = ::llvm::dyn_cast<AppIDHierNodeOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

AppIDHierNodeOp AppIDHierNodeOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::circt::esi::AppIDAttr appID, ::llvm::StringRef moduleRef) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(appID)>(appID), std::forward<decltype(moduleRef)>(moduleRef));
}

void AppIDHierNodeOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  for (unsigned i = 0; i != 1; ++i)
    (void)odsState.addRegion();
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<AppIDHierNodeOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

AppIDHierNodeOp AppIDHierNodeOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<AppIDHierNodeOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

AppIDHierNodeOp AppIDHierNodeOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void AppIDHierNodeOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  for (unsigned i = 0; i != 1; ++i)
    (void)odsState.addRegion();
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

AppIDHierNodeOp AppIDHierNodeOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<AppIDHierNodeOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

AppIDHierNodeOp AppIDHierNodeOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult AppIDHierNodeOp::verifyInvariantsImpl() {
  auto tblgen_appID = getProperties().appID; (void)tblgen_appID;
  if (!tblgen_appID) return emitOpError("requires attribute 'appID'");
  auto tblgen_moduleRef = getProperties().moduleRef; (void)tblgen_moduleRef;
  if (!tblgen_moduleRef) return emitOpError("requires attribute 'moduleRef'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_ESI1(*this, tblgen_appID, "appID")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_ESI2(*this, tblgen_moduleRef, "moduleRef")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;

    for (auto &region : ::llvm::MutableArrayRef((*this)->getRegion(0)))
      if (::mlir::failed(__mlir_ods_local_region_constraint_ESI1(*this, region, "children", index++)))
        return ::mlir::failure();
  }
  return ::mlir::success();
}

::llvm::LogicalResult AppIDHierNodeOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult AppIDHierNodeOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::circt::esi::AppIDAttr appIDAttr;
  ::mlir::FlatSymbolRefAttr moduleRefAttr;
  std::unique_ptr<::mlir::Region> childrenRegion = std::make_unique<::mlir::Region>();

  if (parser.parseAttribute(appIDAttr, ::mlir::Type{}))
    return ::mlir::failure();
  if (appIDAttr) result.getOrAddProperties<AppIDHierNodeOp::Properties>().appID = appIDAttr;
  if (parser.parseKeyword("mod"))
    return ::mlir::failure();

  if (parser.parseCustomAttributeWithFallback(moduleRefAttr, parser.getBuilder().getType<::mlir::NoneType>())) {
    return ::mlir::failure();
  }
  if (moduleRefAttr) result.getOrAddProperties<AppIDHierNodeOp::Properties>().moduleRef = moduleRefAttr;
  {
    auto loc = parser.getCurrentLocation();(void)loc;
    if (parser.parseOptionalAttrDictWithKeyword(result.attributes))
      return ::mlir::failure();
    if (failed(verifyInherentAttrs(result.name, result.attributes, [&]() {
        return parser.emitError(loc) << "'" << result.name.getStringRef() << "' op ";
      })))
      return ::mlir::failure();
  }

  if (parser.parseRegion(*childrenRegion))
    return ::mlir::failure();

  if (childrenRegion->empty()) childrenRegion->emplaceBlock();
  result.addRegion(std::move(childrenRegion));
  return ::mlir::success();
}

void AppIDHierNodeOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter.printAttribute(getAppIDAttr());
  _odsPrinter << ' ' << "mod";
  _odsPrinter << ' ';
  _odsPrinter.printAttributeWithoutType(getModuleRefAttr());
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("appID");
  elidedAttrs.push_back("moduleRef");
  _odsPrinter.printOptionalAttrDictWithKeyword((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ';
  _odsPrinter.printRegion(getChildren());
}


} // namespace circt::esi
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::esi::AppIDHierNodeOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::esi::detail::AppIDHierNodeOpGenericAdaptorBase::Properties)

namespace circt::esi {


//===----------------------------------------------------------------------===//
// ::circt::esi::AppIDHierRootOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

AppIDHierRootOpGenericAdaptorBase::AppIDHierRootOpGenericAdaptorBase(AppIDHierRootOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::llvm::StringRef AppIDHierRootOpGenericAdaptorBase::getTopModuleRef() {
  auto attr = getTopModuleRefAttr();
  return attr.getValue();
}


} // namespace detail
AppIDHierRootOpAdaptor::AppIDHierRootOpAdaptor(AppIDHierRootOp op) : AppIDHierRootOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult AppIDHierRootOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_topModuleRef = getProperties().topModuleRef; (void)tblgen_topModuleRef;
  if (!tblgen_topModuleRef) return emitError(loc, "'esi.manifest.hier_root' op requires attribute 'topModuleRef'");

  if (tblgen_topModuleRef && !((::llvm::isa<::mlir::FlatSymbolRefAttr>(tblgen_topModuleRef))))
    return emitError(loc, "'esi.manifest.hier_root' op attribute 'topModuleRef' failed to satisfy constraint: flat symbol reference attribute");
  return ::mlir::success();
}

::llvm::LogicalResult AppIDHierRootOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
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

::mlir::Attribute AppIDHierRootOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

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

llvm::hash_code AppIDHierRootOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.topModuleRef.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> AppIDHierRootOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "topModuleRef")
      return prop.topModuleRef;
  return std::nullopt;
}

void AppIDHierRootOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "topModuleRef") {
       prop.topModuleRef = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.topModuleRef)>>(value);
       return;
    }
}

void AppIDHierRootOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.topModuleRef) attrs.append("topModuleRef", prop.topModuleRef);
}

::llvm::LogicalResult AppIDHierRootOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getTopModuleRefAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_ESI2(attr, "topModuleRef", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult AppIDHierRootOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.topModuleRef)))
    return ::mlir::failure();
  return ::mlir::success();
}

void AppIDHierRootOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.topModuleRef);
}

::llvm::StringRef AppIDHierRootOp::getTopModuleRef() {
  auto attr = getTopModuleRefAttr();
  return attr.getValue();
}

void AppIDHierRootOp::setTopModuleRef(::llvm::StringRef attrValue) {
  getProperties().topModuleRef = ::mlir::SymbolRefAttr::get(::mlir::Builder((*this)->getContext()).getContext(), attrValue);
}

void AppIDHierRootOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::FlatSymbolRefAttr topModuleRef) {
  odsState.getOrAddProperties<Properties>().topModuleRef = topModuleRef;
  (void)odsState.addRegion();
}

AppIDHierRootOp AppIDHierRootOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::FlatSymbolRefAttr topModuleRef) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(topModuleRef)>(topModuleRef));
  auto __res__ = ::llvm::dyn_cast<AppIDHierRootOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

AppIDHierRootOp AppIDHierRootOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::FlatSymbolRefAttr topModuleRef) {
  return create(builder, builder.getLoc(), std::forward<decltype(topModuleRef)>(topModuleRef));
}

void AppIDHierRootOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::FlatSymbolRefAttr topModuleRef) {
  odsState.getOrAddProperties<Properties>().topModuleRef = topModuleRef;
  (void)odsState.addRegion();
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

AppIDHierRootOp AppIDHierRootOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::FlatSymbolRefAttr topModuleRef) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(topModuleRef)>(topModuleRef));
  auto __res__ = ::llvm::dyn_cast<AppIDHierRootOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

AppIDHierRootOp AppIDHierRootOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::FlatSymbolRefAttr topModuleRef) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(topModuleRef)>(topModuleRef));
}

void AppIDHierRootOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::llvm::StringRef topModuleRef) {
  odsState.getOrAddProperties<Properties>().topModuleRef = ::mlir::SymbolRefAttr::get(odsBuilder.getContext(), topModuleRef);
  (void)odsState.addRegion();
}

AppIDHierRootOp AppIDHierRootOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::llvm::StringRef topModuleRef) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(topModuleRef)>(topModuleRef));
  auto __res__ = ::llvm::dyn_cast<AppIDHierRootOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

AppIDHierRootOp AppIDHierRootOp::create(::mlir::ImplicitLocOpBuilder &builder, ::llvm::StringRef topModuleRef) {
  return create(builder, builder.getLoc(), std::forward<decltype(topModuleRef)>(topModuleRef));
}

void AppIDHierRootOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::llvm::StringRef topModuleRef) {
  odsState.getOrAddProperties<Properties>().topModuleRef = ::mlir::SymbolRefAttr::get(odsBuilder.getContext(), topModuleRef);
  (void)odsState.addRegion();
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

AppIDHierRootOp AppIDHierRootOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::llvm::StringRef topModuleRef) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(topModuleRef)>(topModuleRef));
  auto __res__ = ::llvm::dyn_cast<AppIDHierRootOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

AppIDHierRootOp AppIDHierRootOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::llvm::StringRef topModuleRef) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(topModuleRef)>(topModuleRef));
}

void AppIDHierRootOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  for (unsigned i = 0; i != 1; ++i)
    (void)odsState.addRegion();
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<AppIDHierRootOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

AppIDHierRootOp AppIDHierRootOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<AppIDHierRootOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

AppIDHierRootOp AppIDHierRootOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void AppIDHierRootOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  for (unsigned i = 0; i != 1; ++i)
    (void)odsState.addRegion();
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

AppIDHierRootOp AppIDHierRootOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<AppIDHierRootOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

AppIDHierRootOp AppIDHierRootOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult AppIDHierRootOp::verifyInvariantsImpl() {
  auto tblgen_topModuleRef = getProperties().topModuleRef; (void)tblgen_topModuleRef;
  if (!tblgen_topModuleRef) return emitOpError("requires attribute 'topModuleRef'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_ESI2(*this, tblgen_topModuleRef, "topModuleRef")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;

    for (auto &region : ::llvm::MutableArrayRef((*this)->getRegion(0)))
      if (::mlir::failed(__mlir_ods_local_region_constraint_ESI1(*this, region, "children", index++)))
        return ::mlir::failure();
  }
  return ::mlir::success();
}

::llvm::LogicalResult AppIDHierRootOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult AppIDHierRootOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::FlatSymbolRefAttr topModuleRefAttr;
  std::unique_ptr<::mlir::Region> childrenRegion = std::make_unique<::mlir::Region>();

  if (parser.parseCustomAttributeWithFallback(topModuleRefAttr, parser.getBuilder().getType<::mlir::NoneType>())) {
    return ::mlir::failure();
  }
  if (topModuleRefAttr) result.getOrAddProperties<AppIDHierRootOp::Properties>().topModuleRef = topModuleRefAttr;
  {
    auto loc = parser.getCurrentLocation();(void)loc;
    if (parser.parseOptionalAttrDictWithKeyword(result.attributes))
      return ::mlir::failure();
    if (failed(verifyInherentAttrs(result.name, result.attributes, [&]() {
        return parser.emitError(loc) << "'" << result.name.getStringRef() << "' op ";
      })))
      return ::mlir::failure();
  }

  if (parser.parseRegion(*childrenRegion))
    return ::mlir::failure();

  if (childrenRegion->empty()) childrenRegion->emplaceBlock();
  result.addRegion(std::move(childrenRegion));
  return ::mlir::success();
}

void AppIDHierRootOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter.printAttributeWithoutType(getTopModuleRefAttr());
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("topModuleRef");
  _odsPrinter.printOptionalAttrDictWithKeyword((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ';
  _odsPrinter.printRegion(getChildren());
}


} // namespace circt::esi
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::esi::AppIDHierRootOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::esi::detail::AppIDHierRootOpGenericAdaptorBase::Properties)

namespace circt::esi {


//===----------------------------------------------------------------------===//
// ::circt::esi::CallServiceDeclOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

CallServiceDeclOpGenericAdaptorBase::CallServiceDeclOpGenericAdaptorBase(CallServiceDeclOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::llvm::StringRef CallServiceDeclOpGenericAdaptorBase::getSymName() {
  auto attr = getSymNameAttr();
  return attr.getValue();
}


} // namespace detail
CallServiceDeclOpAdaptor::CallServiceDeclOpAdaptor(CallServiceDeclOp op) : CallServiceDeclOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult CallServiceDeclOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;
  if (!tblgen_sym_name) return emitError(loc, "'esi.service.std.call' op requires attribute 'sym_name'");

  if (tblgen_sym_name && !((::llvm::isa<::mlir::StringAttr>(tblgen_sym_name))))
    return emitError(loc, "'esi.service.std.call' op attribute 'sym_name' failed to satisfy constraint: string attribute");
  return ::mlir::success();
}

::llvm::LogicalResult CallServiceDeclOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
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

::mlir::Attribute CallServiceDeclOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
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

llvm::hash_code CallServiceDeclOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.sym_name.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> CallServiceDeclOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "sym_name")
      return prop.sym_name;
  return std::nullopt;
}

void CallServiceDeclOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "sym_name") {
       prop.sym_name = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.sym_name)>>(value);
       return;
    }
}

void CallServiceDeclOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.sym_name) attrs.append("sym_name", prop.sym_name);
}

::llvm::LogicalResult CallServiceDeclOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getSymNameAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_ESI3(attr, "sym_name", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult CallServiceDeclOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.sym_name)))
    return ::mlir::failure();
  return ::mlir::success();
}

void CallServiceDeclOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.sym_name);
}

::llvm::StringRef CallServiceDeclOp::getSymName() {
  auto attr = getSymNameAttr();
  return attr.getValue();
}

void CallServiceDeclOp::setSymName(::llvm::StringRef attrValue) {
  getProperties().sym_name = ::mlir::Builder((*this)->getContext()).getStringAttr(attrValue);
}

void CallServiceDeclOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::StringAttr sym_name) {
  odsState.getOrAddProperties<Properties>().sym_name = sym_name;
}

CallServiceDeclOp CallServiceDeclOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::StringAttr sym_name) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(sym_name)>(sym_name));
  auto __res__ = ::llvm::dyn_cast<CallServiceDeclOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

CallServiceDeclOp CallServiceDeclOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::StringAttr sym_name) {
  return create(builder, builder.getLoc(), std::forward<decltype(sym_name)>(sym_name));
}

void CallServiceDeclOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name) {
  odsState.getOrAddProperties<Properties>().sym_name = sym_name;
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

CallServiceDeclOp CallServiceDeclOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(sym_name)>(sym_name));
  auto __res__ = ::llvm::dyn_cast<CallServiceDeclOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

CallServiceDeclOp CallServiceDeclOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(sym_name)>(sym_name));
}

void CallServiceDeclOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::llvm::StringRef sym_name) {
  odsState.getOrAddProperties<Properties>().sym_name = odsBuilder.getStringAttr(sym_name);
}

CallServiceDeclOp CallServiceDeclOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::llvm::StringRef sym_name) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(sym_name)>(sym_name));
  auto __res__ = ::llvm::dyn_cast<CallServiceDeclOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

CallServiceDeclOp CallServiceDeclOp::create(::mlir::ImplicitLocOpBuilder &builder, ::llvm::StringRef sym_name) {
  return create(builder, builder.getLoc(), std::forward<decltype(sym_name)>(sym_name));
}

void CallServiceDeclOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name) {
  odsState.getOrAddProperties<Properties>().sym_name = odsBuilder.getStringAttr(sym_name);
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

CallServiceDeclOp CallServiceDeclOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(sym_name)>(sym_name));
  auto __res__ = ::llvm::dyn_cast<CallServiceDeclOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

CallServiceDeclOp CallServiceDeclOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(sym_name)>(sym_name));
}

void CallServiceDeclOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<CallServiceDeclOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

CallServiceDeclOp CallServiceDeclOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<CallServiceDeclOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

CallServiceDeclOp CallServiceDeclOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void CallServiceDeclOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

CallServiceDeclOp CallServiceDeclOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<CallServiceDeclOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

CallServiceDeclOp CallServiceDeclOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult CallServiceDeclOp::verifyInvariantsImpl() {
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;
  if (!tblgen_sym_name) return emitOpError("requires attribute 'sym_name'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_ESI3(*this, tblgen_sym_name, "sym_name")))
    return ::mlir::failure();
  return ::mlir::success();
}

::llvm::LogicalResult CallServiceDeclOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult CallServiceDeclOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::StringAttr sym_nameAttr;

  if (parser.parseSymbolName(sym_nameAttr))
    return ::mlir::failure();
  if (sym_nameAttr) result.getOrAddProperties<CallServiceDeclOp::Properties>().sym_name = sym_nameAttr;
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

void CallServiceDeclOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter.printSymbolName(getSymNameAttr().getValue());
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("sym_name");
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
}


} // namespace circt::esi
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::esi::CallServiceDeclOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::esi::detail::CallServiceDeclOpGenericAdaptorBase::Properties)

namespace circt::esi {


//===----------------------------------------------------------------------===//
// ::circt::esi::ChannelBufferOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

ChannelBufferOpGenericAdaptorBase::ChannelBufferOpGenericAdaptorBase(ChannelBufferOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::std::optional<uint64_t> ChannelBufferOpGenericAdaptorBase::getStages() {
  auto attr = getStagesAttr();
  return attr ? ::std::optional<uint64_t>(attr.getValue().getZExtValue()) : (::std::nullopt);
}

::std::optional< ::llvm::StringRef > ChannelBufferOpGenericAdaptorBase::getName() {
  auto attr = getNameAttr();
  return attr ? ::std::optional< ::llvm::StringRef >(attr.getValue()) : (::std::nullopt);
}


} // namespace detail
ChannelBufferOpAdaptor::ChannelBufferOpAdaptor(ChannelBufferOp op) : ChannelBufferOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult ChannelBufferOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_name = getProperties().name; (void)tblgen_name;
  auto tblgen_stages = getProperties().stages; (void)tblgen_stages;

  if (tblgen_stages && !((((::llvm::isa<::mlir::IntegerAttr>(tblgen_stages))) && ((::llvm::cast<::mlir::IntegerAttr>(tblgen_stages).getType().isSignlessInteger(64)))) && ((::llvm::cast<::mlir::IntegerAttr>(tblgen_stages).getInt() >= 1))))
    return emitError(loc, "'esi.buffer' op attribute 'stages' failed to satisfy constraint: 64-bit signless integer attribute whose minimum value is 1");

  if (tblgen_name && !((::llvm::isa<::mlir::StringAttr>(tblgen_name))))
    return emitError(loc, "'esi.buffer' op attribute 'name' failed to satisfy constraint: string attribute");
  return ::mlir::success();
}

::llvm::LogicalResult ChannelBufferOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
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
    auto &propStorage = prop.stages;
       auto attr = dict.get("stages");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `stages` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  return ::mlir::success();
}

::mlir::Attribute ChannelBufferOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.name;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("name",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.stages;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("stages",
                                       propStorage));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code ChannelBufferOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.name.getAsOpaquePointer()), 
    llvm::hash_value(prop.stages.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> ChannelBufferOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "name")
      return prop.name;

    if (name == "stages")
      return prop.stages;
  return std::nullopt;
}

void ChannelBufferOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "name") {
       prop.name = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.name)>>(value);
       return;
    }

    if (name == "stages") {
       prop.stages = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.stages)>>(value);
       return;
    }
}

void ChannelBufferOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.name) attrs.append("name", prop.name);

    if (prop.stages) attrs.append("stages", prop.stages);
}

::llvm::LogicalResult ChannelBufferOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getNameAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_ESI3(attr, "name", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getStagesAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_ESI4(attr, "stages", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult ChannelBufferOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readOptionalAttribute(prop.name)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readOptionalAttribute(prop.stages)))
    return ::mlir::failure();
  return ::mlir::success();
}

void ChannelBufferOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;

  writer.writeOptionalAttribute(prop.name);

  writer.writeOptionalAttribute(prop.stages);
}

::std::optional<uint64_t> ChannelBufferOp::getStages() {
  auto attr = getStagesAttr();
  return attr ? ::std::optional<uint64_t>(attr.getValue().getZExtValue()) : (::std::nullopt);
}

::std::optional< ::llvm::StringRef > ChannelBufferOp::getName() {
  auto attr = getNameAttr();
  return attr ? ::std::optional< ::llvm::StringRef >(attr.getValue()) : (::std::nullopt);
}

void ChannelBufferOp::setStages(::std::optional<uint64_t> attrValue) {
    auto &odsProp = getProperties().stages;
    if (attrValue)
      odsProp = ::mlir::Builder((*this)->getContext()).getIntegerAttr(::mlir::Builder((*this)->getContext()).getIntegerType(64), *attrValue);
    else
      odsProp = nullptr;
}

void ChannelBufferOp::setName(::std::optional<::llvm::StringRef> attrValue) {
    auto &odsProp = getProperties().name;
    if (attrValue)
      odsProp = ::mlir::Builder((*this)->getContext()).getStringAttr(*attrValue);
    else
      odsProp = nullptr;
}

void ChannelBufferOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type output, ::mlir::Value clk, ::mlir::Value rst, ::mlir::Value input, /*optional*/::mlir::IntegerAttr stages, /*optional*/::mlir::StringAttr name) {
  odsState.addOperands(clk);
  odsState.addOperands(rst);
  odsState.addOperands(input);
  if (stages) {
    odsState.getOrAddProperties<Properties>().stages = stages;
  }
  if (name) {
    odsState.getOrAddProperties<Properties>().name = name;
  }
  odsState.addTypes(output);
}

ChannelBufferOp ChannelBufferOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type output, ::mlir::Value clk, ::mlir::Value rst, ::mlir::Value input, /*optional*/::mlir::IntegerAttr stages, /*optional*/::mlir::StringAttr name) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(output)>(output), std::forward<decltype(clk)>(clk), std::forward<decltype(rst)>(rst), std::forward<decltype(input)>(input), std::forward<decltype(stages)>(stages), std::forward<decltype(name)>(name));
  auto __res__ = ::llvm::dyn_cast<ChannelBufferOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ChannelBufferOp ChannelBufferOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type output, ::mlir::Value clk, ::mlir::Value rst, ::mlir::Value input, /*optional*/::mlir::IntegerAttr stages, /*optional*/::mlir::StringAttr name) {
  return create(builder, builder.getLoc(), std::forward<decltype(output)>(output), std::forward<decltype(clk)>(clk), std::forward<decltype(rst)>(rst), std::forward<decltype(input)>(input), std::forward<decltype(stages)>(stages), std::forward<decltype(name)>(name));
}

void ChannelBufferOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value clk, ::mlir::Value rst, ::mlir::Value input, /*optional*/::mlir::IntegerAttr stages, /*optional*/::mlir::StringAttr name) {
  odsState.addOperands(clk);
  odsState.addOperands(rst);
  odsState.addOperands(input);
  if (stages) {
    odsState.getOrAddProperties<Properties>().stages = stages;
  }
  if (name) {
    odsState.getOrAddProperties<Properties>().name = name;
  }
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

ChannelBufferOp ChannelBufferOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value clk, ::mlir::Value rst, ::mlir::Value input, /*optional*/::mlir::IntegerAttr stages, /*optional*/::mlir::StringAttr name) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(clk)>(clk), std::forward<decltype(rst)>(rst), std::forward<decltype(input)>(input), std::forward<decltype(stages)>(stages), std::forward<decltype(name)>(name));
  auto __res__ = ::llvm::dyn_cast<ChannelBufferOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ChannelBufferOp ChannelBufferOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value clk, ::mlir::Value rst, ::mlir::Value input, /*optional*/::mlir::IntegerAttr stages, /*optional*/::mlir::StringAttr name) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(clk)>(clk), std::forward<decltype(rst)>(rst), std::forward<decltype(input)>(input), std::forward<decltype(stages)>(stages), std::forward<decltype(name)>(name));
}

void ChannelBufferOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 3u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<ChannelBufferOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

ChannelBufferOp ChannelBufferOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<ChannelBufferOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ChannelBufferOp ChannelBufferOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void ChannelBufferOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 3u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

ChannelBufferOp ChannelBufferOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<ChannelBufferOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ChannelBufferOp ChannelBufferOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult ChannelBufferOp::verifyInvariantsImpl() {
  auto tblgen_name = getProperties().name; (void)tblgen_name;
  auto tblgen_stages = getProperties().stages; (void)tblgen_stages;

  if (::mlir::failed(__mlir_ods_local_attr_constraint_ESI4(*this, tblgen_stages, "stages")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_ESI3(*this, tblgen_name, "name")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_ESI1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSOperands(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_ESI2(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup2 = getODSOperands(2);

    for (auto v : valueGroup2) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_ESI3(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_ESI3(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult ChannelBufferOp::verifyInvariants() {
  if(::mlir::succeeded(verifyInvariantsImpl()) && ::mlir::succeeded(verify()))
    return ::mlir::success();
  return ::mlir::failure();
}

::mlir::ParseResult ChannelBufferOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::OpAsmParser::UnresolvedOperand clkRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> clkOperands(&clkRawOperand, 1);  ::llvm::SMLoc clkOperandsLoc;
  (void)clkOperandsLoc;
  ::mlir::OpAsmParser::UnresolvedOperand rstRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> rstOperands(&rstRawOperand, 1);  ::llvm::SMLoc rstOperandsLoc;
  (void)rstOperandsLoc;
  ::mlir::OpAsmParser::UnresolvedOperand inputRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> inputOperands(&inputRawOperand, 1);  ::llvm::SMLoc inputOperandsLoc;
  (void)inputOperandsLoc;
  ::mlir::Type inputRawType{};
  ::llvm::ArrayRef<::mlir::Type> inputTypes(&inputRawType, 1);
  ::mlir::Type outputRawType{};
  ::llvm::ArrayRef<::mlir::Type> outputTypes(&outputRawType, 1);

  clkOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(clkRawOperand))
    return ::mlir::failure();
  if (parser.parseComma())
    return ::mlir::failure();

  rstOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(rstRawOperand))
    return ::mlir::failure();
  if (parser.parseComma())
    return ::mlir::failure();

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
  if (parser.parseArrow())
    return ::mlir::failure();

  if (parser.parseType(outputRawType))
    return ::mlir::failure();
  ::mlir::Type odsBuildableType0 = parser.getBuilder().getType<::circt::seq::ClockType>();
  ::mlir::Type odsBuildableType1 = parser.getBuilder().getIntegerType(1);
  result.addTypes(outputTypes);
  if (parser.resolveOperands(clkOperands, odsBuildableType0, clkOperandsLoc, result.operands))
    return ::mlir::failure();
  if (parser.resolveOperands(rstOperands, odsBuildableType1, rstOperandsLoc, result.operands))
    return ::mlir::failure();
  if (parser.resolveOperands(inputOperands, inputTypes, inputOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void ChannelBufferOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter << getClk();
  _odsPrinter << ",";
  _odsPrinter << ' ';
  _odsPrinter << getRst();
  _odsPrinter << ",";
  _odsPrinter << ' ';
  _odsPrinter << getInput();
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
   _odsPrinter << getInput().getType();
  _odsPrinter << ' ' << "->";
  _odsPrinter << ' ';
   _odsPrinter << getOutput().getType();
}

void ChannelBufferOp::getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects) {
}


} // namespace circt::esi
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::esi::ChannelBufferOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::esi::detail::ChannelBufferOpGenericAdaptorBase::Properties)

namespace circt::esi {


//===----------------------------------------------------------------------===//
// ::circt::esi::ChannelServiceDeclOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

ChannelServiceDeclOpGenericAdaptorBase::ChannelServiceDeclOpGenericAdaptorBase(ChannelServiceDeclOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::llvm::StringRef ChannelServiceDeclOpGenericAdaptorBase::getSymName() {
  auto attr = getSymNameAttr();
  return attr.getValue();
}


} // namespace detail
ChannelServiceDeclOpAdaptor::ChannelServiceDeclOpAdaptor(ChannelServiceDeclOp op) : ChannelServiceDeclOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult ChannelServiceDeclOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;
  if (!tblgen_sym_name) return emitError(loc, "'esi.service.std.channel' op requires attribute 'sym_name'");

  if (tblgen_sym_name && !((::llvm::isa<::mlir::StringAttr>(tblgen_sym_name))))
    return emitError(loc, "'esi.service.std.channel' op attribute 'sym_name' failed to satisfy constraint: string attribute");
  return ::mlir::success();
}

::llvm::LogicalResult ChannelServiceDeclOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
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

::mlir::Attribute ChannelServiceDeclOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
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

llvm::hash_code ChannelServiceDeclOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.sym_name.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> ChannelServiceDeclOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "sym_name")
      return prop.sym_name;
  return std::nullopt;
}

void ChannelServiceDeclOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "sym_name") {
       prop.sym_name = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.sym_name)>>(value);
       return;
    }
}

void ChannelServiceDeclOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.sym_name) attrs.append("sym_name", prop.sym_name);
}

::llvm::LogicalResult ChannelServiceDeclOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getSymNameAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_ESI3(attr, "sym_name", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult ChannelServiceDeclOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.sym_name)))
    return ::mlir::failure();
  return ::mlir::success();
}

void ChannelServiceDeclOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.sym_name);
}

::llvm::StringRef ChannelServiceDeclOp::getSymName() {
  auto attr = getSymNameAttr();
  return attr.getValue();
}

void ChannelServiceDeclOp::setSymName(::llvm::StringRef attrValue) {
  getProperties().sym_name = ::mlir::Builder((*this)->getContext()).getStringAttr(attrValue);
}

void ChannelServiceDeclOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::StringAttr sym_name) {
  odsState.getOrAddProperties<Properties>().sym_name = sym_name;
}

ChannelServiceDeclOp ChannelServiceDeclOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::StringAttr sym_name) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(sym_name)>(sym_name));
  auto __res__ = ::llvm::dyn_cast<ChannelServiceDeclOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ChannelServiceDeclOp ChannelServiceDeclOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::StringAttr sym_name) {
  return create(builder, builder.getLoc(), std::forward<decltype(sym_name)>(sym_name));
}

void ChannelServiceDeclOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name) {
  odsState.getOrAddProperties<Properties>().sym_name = sym_name;
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

ChannelServiceDeclOp ChannelServiceDeclOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(sym_name)>(sym_name));
  auto __res__ = ::llvm::dyn_cast<ChannelServiceDeclOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ChannelServiceDeclOp ChannelServiceDeclOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(sym_name)>(sym_name));
}

void ChannelServiceDeclOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::llvm::StringRef sym_name) {
  odsState.getOrAddProperties<Properties>().sym_name = odsBuilder.getStringAttr(sym_name);
}

ChannelServiceDeclOp ChannelServiceDeclOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::llvm::StringRef sym_name) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(sym_name)>(sym_name));
  auto __res__ = ::llvm::dyn_cast<ChannelServiceDeclOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ChannelServiceDeclOp ChannelServiceDeclOp::create(::mlir::ImplicitLocOpBuilder &builder, ::llvm::StringRef sym_name) {
  return create(builder, builder.getLoc(), std::forward<decltype(sym_name)>(sym_name));
}

void ChannelServiceDeclOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name) {
  odsState.getOrAddProperties<Properties>().sym_name = odsBuilder.getStringAttr(sym_name);
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

ChannelServiceDeclOp ChannelServiceDeclOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(sym_name)>(sym_name));
  auto __res__ = ::llvm::dyn_cast<ChannelServiceDeclOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ChannelServiceDeclOp ChannelServiceDeclOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(sym_name)>(sym_name));
}

void ChannelServiceDeclOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<ChannelServiceDeclOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

ChannelServiceDeclOp ChannelServiceDeclOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<ChannelServiceDeclOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ChannelServiceDeclOp ChannelServiceDeclOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void ChannelServiceDeclOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

ChannelServiceDeclOp ChannelServiceDeclOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<ChannelServiceDeclOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ChannelServiceDeclOp ChannelServiceDeclOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult ChannelServiceDeclOp::verifyInvariantsImpl() {
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;
  if (!tblgen_sym_name) return emitOpError("requires attribute 'sym_name'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_ESI3(*this, tblgen_sym_name, "sym_name")))
    return ::mlir::failure();
  return ::mlir::success();
}

::llvm::LogicalResult ChannelServiceDeclOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult ChannelServiceDeclOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::StringAttr sym_nameAttr;

  if (parser.parseSymbolName(sym_nameAttr))
    return ::mlir::failure();
  if (sym_nameAttr) result.getOrAddProperties<ChannelServiceDeclOp::Properties>().sym_name = sym_nameAttr;
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

void ChannelServiceDeclOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter.printSymbolName(getSymNameAttr().getValue());
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("sym_name");
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
}


} // namespace circt::esi
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::esi::ChannelServiceDeclOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::esi::detail::ChannelServiceDeclOpGenericAdaptorBase::Properties)

namespace circt::esi {


//===----------------------------------------------------------------------===//
// ::circt::esi::CompressedManifestOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

CompressedManifestOpGenericAdaptorBase::CompressedManifestOpGenericAdaptorBase(CompressedManifestOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::circt::esi::BlobAttr CompressedManifestOpGenericAdaptorBase::getCompressedManifest() {
  auto attr = getCompressedManifestAttr();
  return ::llvm::cast<::circt::esi::BlobAttr>(attr);
}


} // namespace detail
CompressedManifestOpAdaptor::CompressedManifestOpAdaptor(CompressedManifestOp op) : CompressedManifestOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult CompressedManifestOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_compressedManifest = getProperties().compressedManifest; (void)tblgen_compressedManifest;
  if (!tblgen_compressedManifest) return emitError(loc, "'esi.manifest.compressed' op requires attribute 'compressedManifest'");

  if (tblgen_compressedManifest && !((::llvm::isa<::circt::esi::BlobAttr>(tblgen_compressedManifest))))
    return emitError(loc, "'esi.manifest.compressed' op attribute 'compressedManifest' failed to satisfy constraint: A binary blob");
  return ::mlir::success();
}

::llvm::LogicalResult CompressedManifestOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.compressedManifest;
       auto attr = dict.get("compressedManifest");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `compressedManifest` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  return ::mlir::success();
}

::mlir::Attribute CompressedManifestOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.compressedManifest;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("compressedManifest",
                                       propStorage));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code CompressedManifestOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.compressedManifest.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> CompressedManifestOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "compressedManifest")
      return prop.compressedManifest;
  return std::nullopt;
}

void CompressedManifestOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "compressedManifest") {
       prop.compressedManifest = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.compressedManifest)>>(value);
       return;
    }
}

void CompressedManifestOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.compressedManifest) attrs.append("compressedManifest", prop.compressedManifest);
}

::llvm::LogicalResult CompressedManifestOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getCompressedManifestAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_ESI5(attr, "compressedManifest", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult CompressedManifestOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.compressedManifest)))
    return ::mlir::failure();
  return ::mlir::success();
}

void CompressedManifestOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.compressedManifest);
}

::circt::esi::BlobAttr CompressedManifestOp::getCompressedManifest() {
  auto attr = getCompressedManifestAttr();
  return ::llvm::cast<::circt::esi::BlobAttr>(attr);
}

void CompressedManifestOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::circt::esi::BlobAttr compressedManifest) {
  odsState.getOrAddProperties<Properties>().compressedManifest = compressedManifest;
}

CompressedManifestOp CompressedManifestOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::circt::esi::BlobAttr compressedManifest) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(compressedManifest)>(compressedManifest));
  auto __res__ = ::llvm::dyn_cast<CompressedManifestOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

CompressedManifestOp CompressedManifestOp::create(::mlir::ImplicitLocOpBuilder &builder, ::circt::esi::BlobAttr compressedManifest) {
  return create(builder, builder.getLoc(), std::forward<decltype(compressedManifest)>(compressedManifest));
}

void CompressedManifestOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::circt::esi::BlobAttr compressedManifest) {
  odsState.getOrAddProperties<Properties>().compressedManifest = compressedManifest;
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

CompressedManifestOp CompressedManifestOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::circt::esi::BlobAttr compressedManifest) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(compressedManifest)>(compressedManifest));
  auto __res__ = ::llvm::dyn_cast<CompressedManifestOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

CompressedManifestOp CompressedManifestOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::circt::esi::BlobAttr compressedManifest) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(compressedManifest)>(compressedManifest));
}

void CompressedManifestOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<CompressedManifestOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

CompressedManifestOp CompressedManifestOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<CompressedManifestOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

CompressedManifestOp CompressedManifestOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void CompressedManifestOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

CompressedManifestOp CompressedManifestOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<CompressedManifestOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

CompressedManifestOp CompressedManifestOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult CompressedManifestOp::verifyInvariantsImpl() {
  auto tblgen_compressedManifest = getProperties().compressedManifest; (void)tblgen_compressedManifest;
  if (!tblgen_compressedManifest) return emitOpError("requires attribute 'compressedManifest'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_ESI5(*this, tblgen_compressedManifest, "compressedManifest")))
    return ::mlir::failure();
  return ::mlir::success();
}

::llvm::LogicalResult CompressedManifestOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult CompressedManifestOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::circt::esi::BlobAttr compressedManifestAttr;

  if (parser.parseCustomAttributeWithFallback(compressedManifestAttr, ::mlir::Type{})) {
    return ::mlir::failure();
  }
  if (compressedManifestAttr) result.getOrAddProperties<CompressedManifestOp::Properties>().compressedManifest = compressedManifestAttr;
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

void CompressedManifestOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
_odsPrinter.printStrippedAttrOrType(getCompressedManifestAttr());
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("compressedManifest");
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
}


} // namespace circt::esi
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::esi::CompressedManifestOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::esi::detail::CompressedManifestOpGenericAdaptorBase::Properties)

namespace circt::esi {


//===----------------------------------------------------------------------===//
// ::circt::esi::CosimFromHostEndpointOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

CosimFromHostEndpointOpGenericAdaptorBase::CosimFromHostEndpointOpGenericAdaptorBase(CosimFromHostEndpointOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::llvm::StringRef CosimFromHostEndpointOpGenericAdaptorBase::getId() {
  auto attr = getIdAttr();
  return attr.getValue();
}


} // namespace detail
CosimFromHostEndpointOpAdaptor::CosimFromHostEndpointOpAdaptor(CosimFromHostEndpointOp op) : CosimFromHostEndpointOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult CosimFromHostEndpointOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_id = getProperties().id; (void)tblgen_id;
  if (!tblgen_id) return emitError(loc, "'esi.cosim.from_host' op requires attribute 'id'");

  if (tblgen_id && !((::llvm::isa<::mlir::StringAttr>(tblgen_id))))
    return emitError(loc, "'esi.cosim.from_host' op attribute 'id' failed to satisfy constraint: string attribute");
  return ::mlir::success();
}

::llvm::LogicalResult CosimFromHostEndpointOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.id;
       auto attr = dict.get("id");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `id` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  return ::mlir::success();
}

::mlir::Attribute CosimFromHostEndpointOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.id;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("id",
                                       propStorage));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code CosimFromHostEndpointOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.id.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> CosimFromHostEndpointOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "id")
      return prop.id;
  return std::nullopt;
}

void CosimFromHostEndpointOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "id") {
       prop.id = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.id)>>(value);
       return;
    }
}

void CosimFromHostEndpointOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.id) attrs.append("id", prop.id);
}

::llvm::LogicalResult CosimFromHostEndpointOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getIdAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_ESI3(attr, "id", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult CosimFromHostEndpointOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.id)))
    return ::mlir::failure();
  return ::mlir::success();
}

void CosimFromHostEndpointOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.id);
}

::llvm::StringRef CosimFromHostEndpointOp::getId() {
  auto attr = getIdAttr();
  return attr.getValue();
}

void CosimFromHostEndpointOp::setId(::llvm::StringRef attrValue) {
  getProperties().id = ::mlir::Builder((*this)->getContext()).getStringAttr(attrValue);
}

void CosimFromHostEndpointOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type fromHost, ::mlir::Value clk, ::mlir::Value rst, ::mlir::StringAttr id) {
  odsState.addOperands(clk);
  odsState.addOperands(rst);
  odsState.getOrAddProperties<Properties>().id = id;
  odsState.addTypes(fromHost);
}

CosimFromHostEndpointOp CosimFromHostEndpointOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type fromHost, ::mlir::Value clk, ::mlir::Value rst, ::mlir::StringAttr id) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(fromHost)>(fromHost), std::forward<decltype(clk)>(clk), std::forward<decltype(rst)>(rst), std::forward<decltype(id)>(id));
  auto __res__ = ::llvm::dyn_cast<CosimFromHostEndpointOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

CosimFromHostEndpointOp CosimFromHostEndpointOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type fromHost, ::mlir::Value clk, ::mlir::Value rst, ::mlir::StringAttr id) {
  return create(builder, builder.getLoc(), std::forward<decltype(fromHost)>(fromHost), std::forward<decltype(clk)>(clk), std::forward<decltype(rst)>(rst), std::forward<decltype(id)>(id));
}

void CosimFromHostEndpointOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value clk, ::mlir::Value rst, ::mlir::StringAttr id) {
  odsState.addOperands(clk);
  odsState.addOperands(rst);
  odsState.getOrAddProperties<Properties>().id = id;
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

CosimFromHostEndpointOp CosimFromHostEndpointOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value clk, ::mlir::Value rst, ::mlir::StringAttr id) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(clk)>(clk), std::forward<decltype(rst)>(rst), std::forward<decltype(id)>(id));
  auto __res__ = ::llvm::dyn_cast<CosimFromHostEndpointOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

CosimFromHostEndpointOp CosimFromHostEndpointOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value clk, ::mlir::Value rst, ::mlir::StringAttr id) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(clk)>(clk), std::forward<decltype(rst)>(rst), std::forward<decltype(id)>(id));
}

void CosimFromHostEndpointOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type fromHost, ::mlir::Value clk, ::mlir::Value rst, ::llvm::StringRef id) {
  odsState.addOperands(clk);
  odsState.addOperands(rst);
  odsState.getOrAddProperties<Properties>().id = odsBuilder.getStringAttr(id);
  odsState.addTypes(fromHost);
}

CosimFromHostEndpointOp CosimFromHostEndpointOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type fromHost, ::mlir::Value clk, ::mlir::Value rst, ::llvm::StringRef id) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(fromHost)>(fromHost), std::forward<decltype(clk)>(clk), std::forward<decltype(rst)>(rst), std::forward<decltype(id)>(id));
  auto __res__ = ::llvm::dyn_cast<CosimFromHostEndpointOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

CosimFromHostEndpointOp CosimFromHostEndpointOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type fromHost, ::mlir::Value clk, ::mlir::Value rst, ::llvm::StringRef id) {
  return create(builder, builder.getLoc(), std::forward<decltype(fromHost)>(fromHost), std::forward<decltype(clk)>(clk), std::forward<decltype(rst)>(rst), std::forward<decltype(id)>(id));
}

void CosimFromHostEndpointOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value clk, ::mlir::Value rst, ::llvm::StringRef id) {
  odsState.addOperands(clk);
  odsState.addOperands(rst);
  odsState.getOrAddProperties<Properties>().id = odsBuilder.getStringAttr(id);
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

CosimFromHostEndpointOp CosimFromHostEndpointOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value clk, ::mlir::Value rst, ::llvm::StringRef id) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(clk)>(clk), std::forward<decltype(rst)>(rst), std::forward<decltype(id)>(id));
  auto __res__ = ::llvm::dyn_cast<CosimFromHostEndpointOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

CosimFromHostEndpointOp CosimFromHostEndpointOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value clk, ::mlir::Value rst, ::llvm::StringRef id) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(clk)>(clk), std::forward<decltype(rst)>(rst), std::forward<decltype(id)>(id));
}

void CosimFromHostEndpointOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 2u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<CosimFromHostEndpointOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

CosimFromHostEndpointOp CosimFromHostEndpointOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<CosimFromHostEndpointOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

CosimFromHostEndpointOp CosimFromHostEndpointOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void CosimFromHostEndpointOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 2u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

CosimFromHostEndpointOp CosimFromHostEndpointOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<CosimFromHostEndpointOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

CosimFromHostEndpointOp CosimFromHostEndpointOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult CosimFromHostEndpointOp::verifyInvariantsImpl() {
  auto tblgen_id = getProperties().id; (void)tblgen_id;
  if (!tblgen_id) return emitOpError("requires attribute 'id'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_ESI3(*this, tblgen_id, "id")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_ESI1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSOperands(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_ESI2(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_ESI3(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult CosimFromHostEndpointOp::verifyInvariants() {
  if(::mlir::succeeded(verifyInvariantsImpl()) && ::mlir::succeeded(verify()))
    return ::mlir::success();
  return ::mlir::failure();
}

::mlir::ParseResult CosimFromHostEndpointOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::OpAsmParser::UnresolvedOperand clkRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> clkOperands(&clkRawOperand, 1);  ::llvm::SMLoc clkOperandsLoc;
  (void)clkOperandsLoc;
  ::mlir::OpAsmParser::UnresolvedOperand rstRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> rstOperands(&rstRawOperand, 1);  ::llvm::SMLoc rstOperandsLoc;
  (void)rstOperandsLoc;
  ::mlir::StringAttr idAttr;
  ::mlir::Type fromHostRawType{};
  ::llvm::ArrayRef<::mlir::Type> fromHostTypes(&fromHostRawType, 1);

  clkOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(clkRawOperand))
    return ::mlir::failure();
  if (parser.parseComma())
    return ::mlir::failure();

  rstOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(rstRawOperand))
    return ::mlir::failure();
  if (parser.parseComma())
    return ::mlir::failure();

  if (parser.parseCustomAttributeWithFallback(idAttr, parser.getBuilder().getType<::mlir::NoneType>())) {
    return ::mlir::failure();
  }
  if (idAttr) result.getOrAddProperties<CosimFromHostEndpointOp::Properties>().id = idAttr;
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

  if (parser.parseType(fromHostRawType))
    return ::mlir::failure();
  ::mlir::Type odsBuildableType0 = parser.getBuilder().getType<::circt::seq::ClockType>();
  ::mlir::Type odsBuildableType1 = parser.getBuilder().getIntegerType(1);
  result.addTypes(fromHostTypes);
  if (parser.resolveOperands(clkOperands, odsBuildableType0, clkOperandsLoc, result.operands))
    return ::mlir::failure();
  if (parser.resolveOperands(rstOperands, odsBuildableType1, rstOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void CosimFromHostEndpointOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter << getClk();
  _odsPrinter << ",";
  _odsPrinter << ' ';
  _odsPrinter << getRst();
  _odsPrinter << ",";
  _odsPrinter << ' ';
  _odsPrinter.printAttributeWithoutType(getIdAttr());
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("id");
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
   _odsPrinter << getFromHost().getType();
}


} // namespace circt::esi
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::esi::CosimFromHostEndpointOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::esi::detail::CosimFromHostEndpointOpGenericAdaptorBase::Properties)

namespace circt::esi {


//===----------------------------------------------------------------------===//
// ::circt::esi::CosimToHostEndpointOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

CosimToHostEndpointOpGenericAdaptorBase::CosimToHostEndpointOpGenericAdaptorBase(CosimToHostEndpointOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::llvm::StringRef CosimToHostEndpointOpGenericAdaptorBase::getId() {
  auto attr = getIdAttr();
  return attr.getValue();
}


} // namespace detail
CosimToHostEndpointOpAdaptor::CosimToHostEndpointOpAdaptor(CosimToHostEndpointOp op) : CosimToHostEndpointOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult CosimToHostEndpointOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_id = getProperties().id; (void)tblgen_id;
  if (!tblgen_id) return emitError(loc, "'esi.cosim.to_host' op requires attribute 'id'");

  if (tblgen_id && !((::llvm::isa<::mlir::StringAttr>(tblgen_id))))
    return emitError(loc, "'esi.cosim.to_host' op attribute 'id' failed to satisfy constraint: string attribute");
  return ::mlir::success();
}

::llvm::LogicalResult CosimToHostEndpointOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.id;
       auto attr = dict.get("id");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `id` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  return ::mlir::success();
}

::mlir::Attribute CosimToHostEndpointOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.id;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("id",
                                       propStorage));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code CosimToHostEndpointOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.id.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> CosimToHostEndpointOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "id")
      return prop.id;
  return std::nullopt;
}

void CosimToHostEndpointOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "id") {
       prop.id = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.id)>>(value);
       return;
    }
}

void CosimToHostEndpointOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.id) attrs.append("id", prop.id);
}

::llvm::LogicalResult CosimToHostEndpointOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getIdAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_ESI3(attr, "id", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult CosimToHostEndpointOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.id)))
    return ::mlir::failure();
  return ::mlir::success();
}

void CosimToHostEndpointOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.id);
}

::llvm::StringRef CosimToHostEndpointOp::getId() {
  auto attr = getIdAttr();
  return attr.getValue();
}

void CosimToHostEndpointOp::setId(::llvm::StringRef attrValue) {
  getProperties().id = ::mlir::Builder((*this)->getContext()).getStringAttr(attrValue);
}

void CosimToHostEndpointOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value clk, ::mlir::Value rst, ::mlir::Value toHost, ::mlir::StringAttr id) {
  odsState.addOperands(clk);
  odsState.addOperands(rst);
  odsState.addOperands(toHost);
  odsState.getOrAddProperties<Properties>().id = id;
}

CosimToHostEndpointOp CosimToHostEndpointOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value clk, ::mlir::Value rst, ::mlir::Value toHost, ::mlir::StringAttr id) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(clk)>(clk), std::forward<decltype(rst)>(rst), std::forward<decltype(toHost)>(toHost), std::forward<decltype(id)>(id));
  auto __res__ = ::llvm::dyn_cast<CosimToHostEndpointOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

CosimToHostEndpointOp CosimToHostEndpointOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value clk, ::mlir::Value rst, ::mlir::Value toHost, ::mlir::StringAttr id) {
  return create(builder, builder.getLoc(), std::forward<decltype(clk)>(clk), std::forward<decltype(rst)>(rst), std::forward<decltype(toHost)>(toHost), std::forward<decltype(id)>(id));
}

void CosimToHostEndpointOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value clk, ::mlir::Value rst, ::mlir::Value toHost, ::mlir::StringAttr id) {
  odsState.addOperands(clk);
  odsState.addOperands(rst);
  odsState.addOperands(toHost);
  odsState.getOrAddProperties<Properties>().id = id;
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

CosimToHostEndpointOp CosimToHostEndpointOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value clk, ::mlir::Value rst, ::mlir::Value toHost, ::mlir::StringAttr id) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(clk)>(clk), std::forward<decltype(rst)>(rst), std::forward<decltype(toHost)>(toHost), std::forward<decltype(id)>(id));
  auto __res__ = ::llvm::dyn_cast<CosimToHostEndpointOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

CosimToHostEndpointOp CosimToHostEndpointOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value clk, ::mlir::Value rst, ::mlir::Value toHost, ::mlir::StringAttr id) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(clk)>(clk), std::forward<decltype(rst)>(rst), std::forward<decltype(toHost)>(toHost), std::forward<decltype(id)>(id));
}

void CosimToHostEndpointOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value clk, ::mlir::Value rst, ::mlir::Value toHost, ::llvm::StringRef id) {
  odsState.addOperands(clk);
  odsState.addOperands(rst);
  odsState.addOperands(toHost);
  odsState.getOrAddProperties<Properties>().id = odsBuilder.getStringAttr(id);
}

CosimToHostEndpointOp CosimToHostEndpointOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value clk, ::mlir::Value rst, ::mlir::Value toHost, ::llvm::StringRef id) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(clk)>(clk), std::forward<decltype(rst)>(rst), std::forward<decltype(toHost)>(toHost), std::forward<decltype(id)>(id));
  auto __res__ = ::llvm::dyn_cast<CosimToHostEndpointOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

CosimToHostEndpointOp CosimToHostEndpointOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value clk, ::mlir::Value rst, ::mlir::Value toHost, ::llvm::StringRef id) {
  return create(builder, builder.getLoc(), std::forward<decltype(clk)>(clk), std::forward<decltype(rst)>(rst), std::forward<decltype(toHost)>(toHost), std::forward<decltype(id)>(id));
}

void CosimToHostEndpointOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value clk, ::mlir::Value rst, ::mlir::Value toHost, ::llvm::StringRef id) {
  odsState.addOperands(clk);
  odsState.addOperands(rst);
  odsState.addOperands(toHost);
  odsState.getOrAddProperties<Properties>().id = odsBuilder.getStringAttr(id);
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

CosimToHostEndpointOp CosimToHostEndpointOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value clk, ::mlir::Value rst, ::mlir::Value toHost, ::llvm::StringRef id) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(clk)>(clk), std::forward<decltype(rst)>(rst), std::forward<decltype(toHost)>(toHost), std::forward<decltype(id)>(id));
  auto __res__ = ::llvm::dyn_cast<CosimToHostEndpointOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

CosimToHostEndpointOp CosimToHostEndpointOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value clk, ::mlir::Value rst, ::mlir::Value toHost, ::llvm::StringRef id) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(clk)>(clk), std::forward<decltype(rst)>(rst), std::forward<decltype(toHost)>(toHost), std::forward<decltype(id)>(id));
}

void CosimToHostEndpointOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 3u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<CosimToHostEndpointOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

CosimToHostEndpointOp CosimToHostEndpointOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<CosimToHostEndpointOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

CosimToHostEndpointOp CosimToHostEndpointOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void CosimToHostEndpointOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 3u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

CosimToHostEndpointOp CosimToHostEndpointOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<CosimToHostEndpointOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

CosimToHostEndpointOp CosimToHostEndpointOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult CosimToHostEndpointOp::verifyInvariantsImpl() {
  auto tblgen_id = getProperties().id; (void)tblgen_id;
  if (!tblgen_id) return emitOpError("requires attribute 'id'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_ESI3(*this, tblgen_id, "id")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_ESI1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSOperands(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_ESI2(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup2 = getODSOperands(2);

    for (auto v : valueGroup2) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_ESI3(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult CosimToHostEndpointOp::verifyInvariants() {
  if(::mlir::succeeded(verifyInvariantsImpl()) && ::mlir::succeeded(verify()))
    return ::mlir::success();
  return ::mlir::failure();
}

::mlir::ParseResult CosimToHostEndpointOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::OpAsmParser::UnresolvedOperand clkRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> clkOperands(&clkRawOperand, 1);  ::llvm::SMLoc clkOperandsLoc;
  (void)clkOperandsLoc;
  ::mlir::OpAsmParser::UnresolvedOperand rstRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> rstOperands(&rstRawOperand, 1);  ::llvm::SMLoc rstOperandsLoc;
  (void)rstOperandsLoc;
  ::mlir::OpAsmParser::UnresolvedOperand toHostRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> toHostOperands(&toHostRawOperand, 1);  ::llvm::SMLoc toHostOperandsLoc;
  (void)toHostOperandsLoc;
  ::mlir::StringAttr idAttr;
  ::mlir::Type toHostRawType{};
  ::llvm::ArrayRef<::mlir::Type> toHostTypes(&toHostRawType, 1);

  clkOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(clkRawOperand))
    return ::mlir::failure();
  if (parser.parseComma())
    return ::mlir::failure();

  rstOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(rstRawOperand))
    return ::mlir::failure();
  if (parser.parseComma())
    return ::mlir::failure();

  toHostOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(toHostRawOperand))
    return ::mlir::failure();
  if (parser.parseComma())
    return ::mlir::failure();

  if (parser.parseCustomAttributeWithFallback(idAttr, parser.getBuilder().getType<::mlir::NoneType>())) {
    return ::mlir::failure();
  }
  if (idAttr) result.getOrAddProperties<CosimToHostEndpointOp::Properties>().id = idAttr;
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

  if (parser.parseType(toHostRawType))
    return ::mlir::failure();
  ::mlir::Type odsBuildableType0 = parser.getBuilder().getType<::circt::seq::ClockType>();
  ::mlir::Type odsBuildableType1 = parser.getBuilder().getIntegerType(1);
  if (parser.resolveOperands(clkOperands, odsBuildableType0, clkOperandsLoc, result.operands))
    return ::mlir::failure();
  if (parser.resolveOperands(rstOperands, odsBuildableType1, rstOperandsLoc, result.operands))
    return ::mlir::failure();
  if (parser.resolveOperands(toHostOperands, toHostTypes, toHostOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void CosimToHostEndpointOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter << getClk();
  _odsPrinter << ",";
  _odsPrinter << ' ';
  _odsPrinter << getRst();
  _odsPrinter << ",";
  _odsPrinter << ' ';
  _odsPrinter << getToHost();
  _odsPrinter << ",";
  _odsPrinter << ' ';
  _odsPrinter.printAttributeWithoutType(getIdAttr());
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("id");
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
   _odsPrinter << getToHost().getType();
}


} // namespace circt::esi
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::esi::CosimToHostEndpointOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::esi::detail::CosimToHostEndpointOpGenericAdaptorBase::Properties)

namespace circt::esi {


//===----------------------------------------------------------------------===//
// ::circt::esi::CustomServiceDeclOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

CustomServiceDeclOpGenericAdaptorBase::CustomServiceDeclOpGenericAdaptorBase(CustomServiceDeclOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::llvm::StringRef CustomServiceDeclOpGenericAdaptorBase::getSymName() {
  auto attr = getSymNameAttr();
  return attr.getValue();
}


} // namespace detail
CustomServiceDeclOpAdaptor::CustomServiceDeclOpAdaptor(CustomServiceDeclOp op) : CustomServiceDeclOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult CustomServiceDeclOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;
  if (!tblgen_sym_name) return emitError(loc, "'esi.service.decl' op requires attribute 'sym_name'");

  if (tblgen_sym_name && !((::llvm::isa<::mlir::StringAttr>(tblgen_sym_name))))
    return emitError(loc, "'esi.service.decl' op attribute 'sym_name' failed to satisfy constraint: string attribute");
  return ::mlir::success();
}

::llvm::LogicalResult CustomServiceDeclOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
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

::mlir::Attribute CustomServiceDeclOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
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

llvm::hash_code CustomServiceDeclOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.sym_name.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> CustomServiceDeclOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "sym_name")
      return prop.sym_name;
  return std::nullopt;
}

void CustomServiceDeclOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "sym_name") {
       prop.sym_name = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.sym_name)>>(value);
       return;
    }
}

void CustomServiceDeclOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.sym_name) attrs.append("sym_name", prop.sym_name);
}

::llvm::LogicalResult CustomServiceDeclOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getSymNameAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_ESI3(attr, "sym_name", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult CustomServiceDeclOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.sym_name)))
    return ::mlir::failure();
  return ::mlir::success();
}

void CustomServiceDeclOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.sym_name);
}

::llvm::StringRef CustomServiceDeclOp::getSymName() {
  auto attr = getSymNameAttr();
  return attr.getValue();
}

void CustomServiceDeclOp::setSymName(::llvm::StringRef attrValue) {
  getProperties().sym_name = ::mlir::Builder((*this)->getContext()).getStringAttr(attrValue);
}

void CustomServiceDeclOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::StringAttr sym_name) {
  odsState.getOrAddProperties<Properties>().sym_name = sym_name;
  (void)odsState.addRegion();
}

CustomServiceDeclOp CustomServiceDeclOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::StringAttr sym_name) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(sym_name)>(sym_name));
  auto __res__ = ::llvm::dyn_cast<CustomServiceDeclOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

CustomServiceDeclOp CustomServiceDeclOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::StringAttr sym_name) {
  return create(builder, builder.getLoc(), std::forward<decltype(sym_name)>(sym_name));
}

void CustomServiceDeclOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name) {
  odsState.getOrAddProperties<Properties>().sym_name = sym_name;
  (void)odsState.addRegion();
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

CustomServiceDeclOp CustomServiceDeclOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(sym_name)>(sym_name));
  auto __res__ = ::llvm::dyn_cast<CustomServiceDeclOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

CustomServiceDeclOp CustomServiceDeclOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(sym_name)>(sym_name));
}

void CustomServiceDeclOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::llvm::StringRef sym_name) {
  odsState.getOrAddProperties<Properties>().sym_name = odsBuilder.getStringAttr(sym_name);
  (void)odsState.addRegion();
}

CustomServiceDeclOp CustomServiceDeclOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::llvm::StringRef sym_name) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(sym_name)>(sym_name));
  auto __res__ = ::llvm::dyn_cast<CustomServiceDeclOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

CustomServiceDeclOp CustomServiceDeclOp::create(::mlir::ImplicitLocOpBuilder &builder, ::llvm::StringRef sym_name) {
  return create(builder, builder.getLoc(), std::forward<decltype(sym_name)>(sym_name));
}

void CustomServiceDeclOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name) {
  odsState.getOrAddProperties<Properties>().sym_name = odsBuilder.getStringAttr(sym_name);
  (void)odsState.addRegion();
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

CustomServiceDeclOp CustomServiceDeclOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(sym_name)>(sym_name));
  auto __res__ = ::llvm::dyn_cast<CustomServiceDeclOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

CustomServiceDeclOp CustomServiceDeclOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(sym_name)>(sym_name));
}

void CustomServiceDeclOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  for (unsigned i = 0; i != 1; ++i)
    (void)odsState.addRegion();
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<CustomServiceDeclOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

CustomServiceDeclOp CustomServiceDeclOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<CustomServiceDeclOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

CustomServiceDeclOp CustomServiceDeclOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void CustomServiceDeclOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  for (unsigned i = 0; i != 1; ++i)
    (void)odsState.addRegion();
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

CustomServiceDeclOp CustomServiceDeclOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<CustomServiceDeclOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

CustomServiceDeclOp CustomServiceDeclOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult CustomServiceDeclOp::verifyInvariantsImpl() {
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;
  if (!tblgen_sym_name) return emitOpError("requires attribute 'sym_name'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_ESI3(*this, tblgen_sym_name, "sym_name")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;

    for (auto &region : ::llvm::MutableArrayRef((*this)->getRegion(0)))
      if (::mlir::failed(__mlir_ods_local_region_constraint_ESI1(*this, region, "ports", index++)))
        return ::mlir::failure();
  }
  return ::mlir::success();
}

::llvm::LogicalResult CustomServiceDeclOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult CustomServiceDeclOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::StringAttr sym_nameAttr;
  std::unique_ptr<::mlir::Region> portsRegion = std::make_unique<::mlir::Region>();

  if (parser.parseSymbolName(sym_nameAttr))
    return ::mlir::failure();
  if (sym_nameAttr) result.getOrAddProperties<CustomServiceDeclOp::Properties>().sym_name = sym_nameAttr;

  if (parser.parseRegion(*portsRegion))
    return ::mlir::failure();

  if (portsRegion->empty()) portsRegion->emplaceBlock();
  {
    auto loc = parser.getCurrentLocation();(void)loc;
    if (parser.parseOptionalAttrDict(result.attributes))
      return ::mlir::failure();
    if (failed(verifyInherentAttrs(result.name, result.attributes, [&]() {
        return parser.emitError(loc) << "'" << result.name.getStringRef() << "' op ";
      })))
      return ::mlir::failure();
  }
  result.addRegion(std::move(portsRegion));
  return ::mlir::success();
}

void CustomServiceDeclOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter.printSymbolName(getSymNameAttr().getValue());
  _odsPrinter << ' ';
  _odsPrinter.printRegion(getPorts());
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("sym_name");
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
}


} // namespace circt::esi
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::esi::CustomServiceDeclOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::esi::detail::CustomServiceDeclOpGenericAdaptorBase::Properties)

namespace circt::esi {


//===----------------------------------------------------------------------===//
// ::circt::esi::ESIPureModuleInputOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

ESIPureModuleInputOpGenericAdaptorBase::ESIPureModuleInputOpGenericAdaptorBase(ESIPureModuleInputOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::llvm::StringRef ESIPureModuleInputOpGenericAdaptorBase::getName() {
  auto attr = getNameAttr();
  return attr.getValue();
}


} // namespace detail
ESIPureModuleInputOpAdaptor::ESIPureModuleInputOpAdaptor(ESIPureModuleInputOp op) : ESIPureModuleInputOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult ESIPureModuleInputOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_name = getProperties().name; (void)tblgen_name;
  if (!tblgen_name) return emitError(loc, "'esi.pure_module.input' op requires attribute 'name'");

  if (tblgen_name && !((::llvm::isa<::mlir::StringAttr>(tblgen_name))))
    return emitError(loc, "'esi.pure_module.input' op attribute 'name' failed to satisfy constraint: string attribute");
  return ::mlir::success();
}

::llvm::LogicalResult ESIPureModuleInputOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
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

::mlir::Attribute ESIPureModuleInputOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
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

llvm::hash_code ESIPureModuleInputOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.name.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> ESIPureModuleInputOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "name")
      return prop.name;
  return std::nullopt;
}

void ESIPureModuleInputOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "name") {
       prop.name = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.name)>>(value);
       return;
    }
}

void ESIPureModuleInputOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.name) attrs.append("name", prop.name);
}

::llvm::LogicalResult ESIPureModuleInputOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getNameAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_ESI3(attr, "name", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult ESIPureModuleInputOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.name)))
    return ::mlir::failure();
  return ::mlir::success();
}

void ESIPureModuleInputOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.name);
}

::llvm::StringRef ESIPureModuleInputOp::getName() {
  auto attr = getNameAttr();
  return attr.getValue();
}

void ESIPureModuleInputOp::setName(::llvm::StringRef attrValue) {
  getProperties().name = ::mlir::Builder((*this)->getContext()).getStringAttr(attrValue);
}

void ESIPureModuleInputOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type value, ::mlir::StringAttr name) {
  odsState.getOrAddProperties<Properties>().name = name;
  odsState.addTypes(value);
}

ESIPureModuleInputOp ESIPureModuleInputOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type value, ::mlir::StringAttr name) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(value)>(value), std::forward<decltype(name)>(name));
  auto __res__ = ::llvm::dyn_cast<ESIPureModuleInputOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ESIPureModuleInputOp ESIPureModuleInputOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type value, ::mlir::StringAttr name) {
  return create(builder, builder.getLoc(), std::forward<decltype(value)>(value), std::forward<decltype(name)>(name));
}

void ESIPureModuleInputOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::StringAttr name) {
  odsState.getOrAddProperties<Properties>().name = name;
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

ESIPureModuleInputOp ESIPureModuleInputOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::StringAttr name) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(name)>(name));
  auto __res__ = ::llvm::dyn_cast<ESIPureModuleInputOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ESIPureModuleInputOp ESIPureModuleInputOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::StringAttr name) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(name)>(name));
}

void ESIPureModuleInputOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type value, ::llvm::StringRef name) {
  odsState.getOrAddProperties<Properties>().name = odsBuilder.getStringAttr(name);
  odsState.addTypes(value);
}

ESIPureModuleInputOp ESIPureModuleInputOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type value, ::llvm::StringRef name) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(value)>(value), std::forward<decltype(name)>(name));
  auto __res__ = ::llvm::dyn_cast<ESIPureModuleInputOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ESIPureModuleInputOp ESIPureModuleInputOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type value, ::llvm::StringRef name) {
  return create(builder, builder.getLoc(), std::forward<decltype(value)>(value), std::forward<decltype(name)>(name));
}

void ESIPureModuleInputOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::llvm::StringRef name) {
  odsState.getOrAddProperties<Properties>().name = odsBuilder.getStringAttr(name);
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

ESIPureModuleInputOp ESIPureModuleInputOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::llvm::StringRef name) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(name)>(name));
  auto __res__ = ::llvm::dyn_cast<ESIPureModuleInputOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ESIPureModuleInputOp ESIPureModuleInputOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::llvm::StringRef name) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(name)>(name));
}

void ESIPureModuleInputOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<ESIPureModuleInputOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

ESIPureModuleInputOp ESIPureModuleInputOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<ESIPureModuleInputOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ESIPureModuleInputOp ESIPureModuleInputOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void ESIPureModuleInputOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

ESIPureModuleInputOp ESIPureModuleInputOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<ESIPureModuleInputOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ESIPureModuleInputOp ESIPureModuleInputOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult ESIPureModuleInputOp::verifyInvariantsImpl() {
  auto tblgen_name = getProperties().name; (void)tblgen_name;
  if (!tblgen_name) return emitOpError("requires attribute 'name'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_ESI3(*this, tblgen_name, "name")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_ESI4(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult ESIPureModuleInputOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult ESIPureModuleInputOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::StringAttr nameAttr;
  ::mlir::Type valueRawType{};
  ::llvm::ArrayRef<::mlir::Type> valueTypes(&valueRawType, 1);

  if (parser.parseCustomAttributeWithFallback(nameAttr, parser.getBuilder().getType<::mlir::NoneType>())) {
    return ::mlir::failure();
  }
  if (nameAttr) result.getOrAddProperties<ESIPureModuleInputOp::Properties>().name = nameAttr;
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
  result.addTypes(valueTypes);
  return ::mlir::success();
}

void ESIPureModuleInputOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter.printAttributeWithoutType(getNameAttr());
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


} // namespace circt::esi
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::esi::ESIPureModuleInputOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::esi::detail::ESIPureModuleInputOpGenericAdaptorBase::Properties)

namespace circt::esi {


//===----------------------------------------------------------------------===//
// ::circt::esi::ESIPureModuleOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

ESIPureModuleOpGenericAdaptorBase::ESIPureModuleOpGenericAdaptorBase(ESIPureModuleOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::llvm::StringRef ESIPureModuleOpGenericAdaptorBase::getSymName() {
  auto attr = getSymNameAttr();
  return attr.getValue();
}


} // namespace detail
ESIPureModuleOpAdaptor::ESIPureModuleOpAdaptor(ESIPureModuleOp op) : ESIPureModuleOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult ESIPureModuleOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;
  if (!tblgen_sym_name) return emitError(loc, "'esi.pure_module' op requires attribute 'sym_name'");

  if (tblgen_sym_name && !((::llvm::isa<::mlir::StringAttr>(tblgen_sym_name))))
    return emitError(loc, "'esi.pure_module' op attribute 'sym_name' failed to satisfy constraint: string attribute");
  return ::mlir::success();
}

::llvm::LogicalResult ESIPureModuleOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
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

::mlir::Attribute ESIPureModuleOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
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

llvm::hash_code ESIPureModuleOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.sym_name.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> ESIPureModuleOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "sym_name")
      return prop.sym_name;
  return std::nullopt;
}

void ESIPureModuleOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "sym_name") {
       prop.sym_name = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.sym_name)>>(value);
       return;
    }
}

void ESIPureModuleOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.sym_name) attrs.append("sym_name", prop.sym_name);
}

::llvm::LogicalResult ESIPureModuleOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getSymNameAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_ESI3(attr, "sym_name", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult ESIPureModuleOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.sym_name)))
    return ::mlir::failure();
  return ::mlir::success();
}

void ESIPureModuleOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.sym_name);
}

::llvm::StringRef ESIPureModuleOp::getSymName() {
  auto attr = getSymNameAttr();
  return attr.getValue();
}

void ESIPureModuleOp::setSymName(::llvm::StringRef attrValue) {
  getProperties().sym_name = ::mlir::Builder((*this)->getContext()).getStringAttr(attrValue);
}

void ESIPureModuleOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::StringAttr sym_name) {
  odsState.getOrAddProperties<Properties>().sym_name = sym_name;
  (void)odsState.addRegion();
}

ESIPureModuleOp ESIPureModuleOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::StringAttr sym_name) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(sym_name)>(sym_name));
  auto __res__ = ::llvm::dyn_cast<ESIPureModuleOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ESIPureModuleOp ESIPureModuleOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::StringAttr sym_name) {
  return create(builder, builder.getLoc(), std::forward<decltype(sym_name)>(sym_name));
}

void ESIPureModuleOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name) {
  odsState.getOrAddProperties<Properties>().sym_name = sym_name;
  (void)odsState.addRegion();
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

ESIPureModuleOp ESIPureModuleOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(sym_name)>(sym_name));
  auto __res__ = ::llvm::dyn_cast<ESIPureModuleOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ESIPureModuleOp ESIPureModuleOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(sym_name)>(sym_name));
}

void ESIPureModuleOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::llvm::StringRef sym_name) {
  odsState.getOrAddProperties<Properties>().sym_name = odsBuilder.getStringAttr(sym_name);
  (void)odsState.addRegion();
}

ESIPureModuleOp ESIPureModuleOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::llvm::StringRef sym_name) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(sym_name)>(sym_name));
  auto __res__ = ::llvm::dyn_cast<ESIPureModuleOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ESIPureModuleOp ESIPureModuleOp::create(::mlir::ImplicitLocOpBuilder &builder, ::llvm::StringRef sym_name) {
  return create(builder, builder.getLoc(), std::forward<decltype(sym_name)>(sym_name));
}

void ESIPureModuleOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name) {
  odsState.getOrAddProperties<Properties>().sym_name = odsBuilder.getStringAttr(sym_name);
  (void)odsState.addRegion();
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

ESIPureModuleOp ESIPureModuleOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(sym_name)>(sym_name));
  auto __res__ = ::llvm::dyn_cast<ESIPureModuleOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ESIPureModuleOp ESIPureModuleOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(sym_name)>(sym_name));
}

void ESIPureModuleOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  for (unsigned i = 0; i != 1; ++i)
    (void)odsState.addRegion();
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<ESIPureModuleOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

ESIPureModuleOp ESIPureModuleOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<ESIPureModuleOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ESIPureModuleOp ESIPureModuleOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void ESIPureModuleOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  for (unsigned i = 0; i != 1; ++i)
    (void)odsState.addRegion();
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

ESIPureModuleOp ESIPureModuleOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<ESIPureModuleOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ESIPureModuleOp ESIPureModuleOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult ESIPureModuleOp::verifyInvariantsImpl() {
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;
  if (!tblgen_sym_name) return emitOpError("requires attribute 'sym_name'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_ESI3(*this, tblgen_sym_name, "sym_name")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;

    for (auto &region : ::llvm::MutableArrayRef((*this)->getRegion(0)))
      if (::mlir::failed(__mlir_ods_local_region_constraint_ESI1(*this, region, "body", index++)))
        return ::mlir::failure();
  }
  return ::mlir::success();
}

::llvm::LogicalResult ESIPureModuleOp::verifyInvariants() {
  if(::mlir::succeeded(verifyInvariantsImpl()) && ::mlir::succeeded(verify()))
    return ::mlir::success();
  return ::mlir::failure();
}

::mlir::ParseResult ESIPureModuleOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::StringAttr sym_nameAttr;
  std::unique_ptr<::mlir::Region> bodyRegion = std::make_unique<::mlir::Region>();

  if (parser.parseSymbolName(sym_nameAttr))
    return ::mlir::failure();
  if (sym_nameAttr) result.getOrAddProperties<ESIPureModuleOp::Properties>().sym_name = sym_nameAttr;
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

void ESIPureModuleOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter.printSymbolName(getSymNameAttr().getValue());
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("sym_name");
  _odsPrinter.printOptionalAttrDictWithKeyword((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ';
  _odsPrinter.printRegion(getBody());
}


} // namespace circt::esi
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::esi::ESIPureModuleOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::esi::detail::ESIPureModuleOpGenericAdaptorBase::Properties)

namespace circt::esi {


//===----------------------------------------------------------------------===//
// ::circt::esi::ESIPureModuleOutputOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

ESIPureModuleOutputOpGenericAdaptorBase::ESIPureModuleOutputOpGenericAdaptorBase(ESIPureModuleOutputOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::llvm::StringRef ESIPureModuleOutputOpGenericAdaptorBase::getName() {
  auto attr = getNameAttr();
  return attr.getValue();
}


} // namespace detail
ESIPureModuleOutputOpAdaptor::ESIPureModuleOutputOpAdaptor(ESIPureModuleOutputOp op) : ESIPureModuleOutputOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult ESIPureModuleOutputOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_name = getProperties().name; (void)tblgen_name;
  if (!tblgen_name) return emitError(loc, "'esi.pure_module.output' op requires attribute 'name'");

  if (tblgen_name && !((::llvm::isa<::mlir::StringAttr>(tblgen_name))))
    return emitError(loc, "'esi.pure_module.output' op attribute 'name' failed to satisfy constraint: string attribute");
  return ::mlir::success();
}

::llvm::LogicalResult ESIPureModuleOutputOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
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

::mlir::Attribute ESIPureModuleOutputOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
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

llvm::hash_code ESIPureModuleOutputOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.name.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> ESIPureModuleOutputOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "name")
      return prop.name;
  return std::nullopt;
}

void ESIPureModuleOutputOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "name") {
       prop.name = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.name)>>(value);
       return;
    }
}

void ESIPureModuleOutputOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.name) attrs.append("name", prop.name);
}

::llvm::LogicalResult ESIPureModuleOutputOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getNameAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_ESI3(attr, "name", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult ESIPureModuleOutputOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.name)))
    return ::mlir::failure();
  return ::mlir::success();
}

void ESIPureModuleOutputOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.name);
}

::llvm::StringRef ESIPureModuleOutputOp::getName() {
  auto attr = getNameAttr();
  return attr.getValue();
}

void ESIPureModuleOutputOp::setName(::llvm::StringRef attrValue) {
  getProperties().name = ::mlir::Builder((*this)->getContext()).getStringAttr(attrValue);
}

void ESIPureModuleOutputOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::StringAttr name, ::mlir::Value value) {
  odsState.addOperands(value);
  odsState.getOrAddProperties<Properties>().name = name;
}

ESIPureModuleOutputOp ESIPureModuleOutputOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::StringAttr name, ::mlir::Value value) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(name)>(name), std::forward<decltype(value)>(value));
  auto __res__ = ::llvm::dyn_cast<ESIPureModuleOutputOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ESIPureModuleOutputOp ESIPureModuleOutputOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::StringAttr name, ::mlir::Value value) {
  return create(builder, builder.getLoc(), std::forward<decltype(name)>(name), std::forward<decltype(value)>(value));
}

void ESIPureModuleOutputOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::StringAttr name, ::mlir::Value value) {
  odsState.addOperands(value);
  odsState.getOrAddProperties<Properties>().name = name;
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

ESIPureModuleOutputOp ESIPureModuleOutputOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::StringAttr name, ::mlir::Value value) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(name)>(name), std::forward<decltype(value)>(value));
  auto __res__ = ::llvm::dyn_cast<ESIPureModuleOutputOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ESIPureModuleOutputOp ESIPureModuleOutputOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::StringAttr name, ::mlir::Value value) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(name)>(name), std::forward<decltype(value)>(value));
}

void ESIPureModuleOutputOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::llvm::StringRef name, ::mlir::Value value) {
  odsState.addOperands(value);
  odsState.getOrAddProperties<Properties>().name = odsBuilder.getStringAttr(name);
}

ESIPureModuleOutputOp ESIPureModuleOutputOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::llvm::StringRef name, ::mlir::Value value) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(name)>(name), std::forward<decltype(value)>(value));
  auto __res__ = ::llvm::dyn_cast<ESIPureModuleOutputOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ESIPureModuleOutputOp ESIPureModuleOutputOp::create(::mlir::ImplicitLocOpBuilder &builder, ::llvm::StringRef name, ::mlir::Value value) {
  return create(builder, builder.getLoc(), std::forward<decltype(name)>(name), std::forward<decltype(value)>(value));
}

void ESIPureModuleOutputOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::llvm::StringRef name, ::mlir::Value value) {
  odsState.addOperands(value);
  odsState.getOrAddProperties<Properties>().name = odsBuilder.getStringAttr(name);
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

ESIPureModuleOutputOp ESIPureModuleOutputOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::llvm::StringRef name, ::mlir::Value value) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(name)>(name), std::forward<decltype(value)>(value));
  auto __res__ = ::llvm::dyn_cast<ESIPureModuleOutputOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ESIPureModuleOutputOp ESIPureModuleOutputOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::llvm::StringRef name, ::mlir::Value value) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(name)>(name), std::forward<decltype(value)>(value));
}

void ESIPureModuleOutputOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<ESIPureModuleOutputOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

ESIPureModuleOutputOp ESIPureModuleOutputOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<ESIPureModuleOutputOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ESIPureModuleOutputOp ESIPureModuleOutputOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void ESIPureModuleOutputOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

ESIPureModuleOutputOp ESIPureModuleOutputOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<ESIPureModuleOutputOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ESIPureModuleOutputOp ESIPureModuleOutputOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult ESIPureModuleOutputOp::verifyInvariantsImpl() {
  auto tblgen_name = getProperties().name; (void)tblgen_name;
  if (!tblgen_name) return emitOpError("requires attribute 'name'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_ESI3(*this, tblgen_name, "name")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_ESI4(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult ESIPureModuleOutputOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult ESIPureModuleOutputOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::StringAttr nameAttr;
  ::mlir::OpAsmParser::UnresolvedOperand valueRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> valueOperands(&valueRawOperand, 1);  ::llvm::SMLoc valueOperandsLoc;
  (void)valueOperandsLoc;
  ::mlir::Type valueRawType{};
  ::llvm::ArrayRef<::mlir::Type> valueTypes(&valueRawType, 1);

  if (parser.parseCustomAttributeWithFallback(nameAttr, parser.getBuilder().getType<::mlir::NoneType>())) {
    return ::mlir::failure();
  }
  if (nameAttr) result.getOrAddProperties<ESIPureModuleOutputOp::Properties>().name = nameAttr;
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

  {
    ::mlir::Type type;
    if (parser.parseCustomTypeWithFallback(type))
      return ::mlir::failure();
    valueRawType = type;
  }
  if (parser.resolveOperands(valueOperands, valueTypes, valueOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void ESIPureModuleOutputOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter.printAttributeWithoutType(getNameAttr());
  _odsPrinter << ",";
  _odsPrinter << ' ';
  _odsPrinter << getValue();
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


} // namespace circt::esi
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::esi::ESIPureModuleOutputOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::esi::detail::ESIPureModuleOutputOpGenericAdaptorBase::Properties)

namespace circt::esi {


//===----------------------------------------------------------------------===//
// ::circt::esi::ESIPureModuleParamOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

ESIPureModuleParamOpGenericAdaptorBase::ESIPureModuleParamOpGenericAdaptorBase(ESIPureModuleParamOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::llvm::StringRef ESIPureModuleParamOpGenericAdaptorBase::getName() {
  auto attr = getNameAttr();
  return attr.getValue();
}

::mlir::Type ESIPureModuleParamOpGenericAdaptorBase::getType() {
  auto attr = getTypeAttr();
  return ::llvm::cast<::mlir::Type>(attr.getValue());
}


} // namespace detail
ESIPureModuleParamOpAdaptor::ESIPureModuleParamOpAdaptor(ESIPureModuleParamOp op) : ESIPureModuleParamOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult ESIPureModuleParamOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_name = getProperties().name; (void)tblgen_name;
  if (!tblgen_name) return emitError(loc, "'esi.pure_module.param' op requires attribute 'name'");
  auto tblgen_type = getProperties().type; (void)tblgen_type;
  if (!tblgen_type) return emitError(loc, "'esi.pure_module.param' op requires attribute 'type'");

  if (tblgen_name && !((::llvm::isa<::mlir::StringAttr>(tblgen_name))))
    return emitError(loc, "'esi.pure_module.param' op attribute 'name' failed to satisfy constraint: string attribute");

  if (tblgen_type && !(((::llvm::isa<::mlir::TypeAttr>(tblgen_type))) && ((::llvm::isa<::mlir::Type>(::llvm::cast<::mlir::TypeAttr>(tblgen_type).getValue()))) && ((true))))
    return emitError(loc, "'esi.pure_module.param' op attribute 'type' failed to satisfy constraint: any type attribute");
  return ::mlir::success();
}

::llvm::LogicalResult ESIPureModuleParamOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
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

::mlir::Attribute ESIPureModuleParamOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

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

llvm::hash_code ESIPureModuleParamOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.name.getAsOpaquePointer()), 
    llvm::hash_value(prop.type.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> ESIPureModuleParamOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "name")
      return prop.name;

    if (name == "type")
      return prop.type;
  return std::nullopt;
}

void ESIPureModuleParamOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "name") {
       prop.name = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.name)>>(value);
       return;
    }

    if (name == "type") {
       prop.type = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.type)>>(value);
       return;
    }
}

void ESIPureModuleParamOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.name) attrs.append("name", prop.name);

    if (prop.type) attrs.append("type", prop.type);
}

::llvm::LogicalResult ESIPureModuleParamOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getNameAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_ESI3(attr, "name", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getTypeAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_ESI6(attr, "type", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult ESIPureModuleParamOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.name)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readAttribute(prop.type)))
    return ::mlir::failure();
  return ::mlir::success();
}

void ESIPureModuleParamOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.name);
  writer.writeAttribute(prop.type);
}

::llvm::StringRef ESIPureModuleParamOp::getName() {
  auto attr = getNameAttr();
  return attr.getValue();
}

::mlir::Type ESIPureModuleParamOp::getType() {
  auto attr = getTypeAttr();
  return ::llvm::cast<::mlir::Type>(attr.getValue());
}

void ESIPureModuleParamOp::setName(::llvm::StringRef attrValue) {
  getProperties().name = ::mlir::Builder((*this)->getContext()).getStringAttr(attrValue);
}

void ESIPureModuleParamOp::setType(::mlir::Type attrValue) {
  getProperties().type = ::mlir::TypeAttr::get(attrValue);
}

void ESIPureModuleParamOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::StringAttr name, ::mlir::TypeAttr type) {
  odsState.getOrAddProperties<Properties>().name = name;
  odsState.getOrAddProperties<Properties>().type = type;
}

ESIPureModuleParamOp ESIPureModuleParamOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::StringAttr name, ::mlir::TypeAttr type) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(name)>(name), std::forward<decltype(type)>(type));
  auto __res__ = ::llvm::dyn_cast<ESIPureModuleParamOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ESIPureModuleParamOp ESIPureModuleParamOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::StringAttr name, ::mlir::TypeAttr type) {
  return create(builder, builder.getLoc(), std::forward<decltype(name)>(name), std::forward<decltype(type)>(type));
}

void ESIPureModuleParamOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::StringAttr name, ::mlir::TypeAttr type) {
  odsState.getOrAddProperties<Properties>().name = name;
  odsState.getOrAddProperties<Properties>().type = type;
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

ESIPureModuleParamOp ESIPureModuleParamOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::StringAttr name, ::mlir::TypeAttr type) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(name)>(name), std::forward<decltype(type)>(type));
  auto __res__ = ::llvm::dyn_cast<ESIPureModuleParamOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ESIPureModuleParamOp ESIPureModuleParamOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::StringAttr name, ::mlir::TypeAttr type) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(name)>(name), std::forward<decltype(type)>(type));
}

void ESIPureModuleParamOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::llvm::StringRef name, ::mlir::Type type) {
  odsState.getOrAddProperties<Properties>().name = odsBuilder.getStringAttr(name);
  odsState.getOrAddProperties<Properties>().type = ::mlir::TypeAttr::get(type);
}

ESIPureModuleParamOp ESIPureModuleParamOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::llvm::StringRef name, ::mlir::Type type) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(name)>(name), std::forward<decltype(type)>(type));
  auto __res__ = ::llvm::dyn_cast<ESIPureModuleParamOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ESIPureModuleParamOp ESIPureModuleParamOp::create(::mlir::ImplicitLocOpBuilder &builder, ::llvm::StringRef name, ::mlir::Type type) {
  return create(builder, builder.getLoc(), std::forward<decltype(name)>(name), std::forward<decltype(type)>(type));
}

void ESIPureModuleParamOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::llvm::StringRef name, ::mlir::Type type) {
  odsState.getOrAddProperties<Properties>().name = odsBuilder.getStringAttr(name);
  odsState.getOrAddProperties<Properties>().type = ::mlir::TypeAttr::get(type);
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

ESIPureModuleParamOp ESIPureModuleParamOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::llvm::StringRef name, ::mlir::Type type) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(name)>(name), std::forward<decltype(type)>(type));
  auto __res__ = ::llvm::dyn_cast<ESIPureModuleParamOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ESIPureModuleParamOp ESIPureModuleParamOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::llvm::StringRef name, ::mlir::Type type) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(name)>(name), std::forward<decltype(type)>(type));
}

void ESIPureModuleParamOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<ESIPureModuleParamOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

ESIPureModuleParamOp ESIPureModuleParamOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<ESIPureModuleParamOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ESIPureModuleParamOp ESIPureModuleParamOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void ESIPureModuleParamOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

ESIPureModuleParamOp ESIPureModuleParamOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<ESIPureModuleParamOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ESIPureModuleParamOp ESIPureModuleParamOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult ESIPureModuleParamOp::verifyInvariantsImpl() {
  auto tblgen_name = getProperties().name; (void)tblgen_name;
  if (!tblgen_name) return emitOpError("requires attribute 'name'");
  auto tblgen_type = getProperties().type; (void)tblgen_type;
  if (!tblgen_type) return emitOpError("requires attribute 'type'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_ESI3(*this, tblgen_name, "name")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_ESI6(*this, tblgen_type, "type")))
    return ::mlir::failure();
  return ::mlir::success();
}

::llvm::LogicalResult ESIPureModuleParamOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult ESIPureModuleParamOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::StringAttr nameAttr;
  ::mlir::TypeAttr typeAttr;

  if (parser.parseCustomAttributeWithFallback(nameAttr, parser.getBuilder().getType<::mlir::NoneType>())) {
    return ::mlir::failure();
  }
  if (nameAttr) result.getOrAddProperties<ESIPureModuleParamOp::Properties>().name = nameAttr;
  if (parser.parseColon())
    return ::mlir::failure();

  if (parser.parseCustomAttributeWithFallback(typeAttr, parser.getBuilder().getType<::mlir::NoneType>())) {
    return ::mlir::failure();
  }
  if (typeAttr) result.getOrAddProperties<ESIPureModuleParamOp::Properties>().type = typeAttr;
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

void ESIPureModuleParamOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter.printAttributeWithoutType(getNameAttr());
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
  _odsPrinter.printAttributeWithoutType(getTypeAttr());
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("name");
  elidedAttrs.push_back("type");
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
}


} // namespace circt::esi
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::esi::ESIPureModuleParamOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::esi::detail::ESIPureModuleParamOpGenericAdaptorBase::Properties)

namespace circt::esi {


//===----------------------------------------------------------------------===//
// ::circt::esi::FIFOOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

FIFOOpGenericAdaptorBase::FIFOOpGenericAdaptorBase(FIFOOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

uint64_t FIFOOpGenericAdaptorBase::getDepth() {
  auto attr = getDepthAttr();
  return attr.getValue().getZExtValue();
}


} // namespace detail
FIFOOpAdaptor::FIFOOpAdaptor(FIFOOp op) : FIFOOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult FIFOOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_depth = getProperties().depth; (void)tblgen_depth;
  if (!tblgen_depth) return emitError(loc, "'esi.fifo' op requires attribute 'depth'");

  if (tblgen_depth && !((((::llvm::isa<::mlir::IntegerAttr>(tblgen_depth))) && ((::llvm::cast<::mlir::IntegerAttr>(tblgen_depth).getType().isSignlessInteger(64)))) && ((::llvm::cast<::mlir::IntegerAttr>(tblgen_depth).getInt() >= 1))))
    return emitError(loc, "'esi.fifo' op attribute 'depth' failed to satisfy constraint: 64-bit signless integer attribute whose minimum value is 1");
  return ::mlir::success();
}

::llvm::LogicalResult FIFOOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
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
  return ::mlir::success();
}

::mlir::Attribute FIFOOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.depth;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("depth",
                                       propStorage));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code FIFOOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.depth.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> FIFOOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "depth")
      return prop.depth;
  return std::nullopt;
}

void FIFOOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "depth") {
       prop.depth = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.depth)>>(value);
       return;
    }
}

void FIFOOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.depth) attrs.append("depth", prop.depth);
}

::llvm::LogicalResult FIFOOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getDepthAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_ESI4(attr, "depth", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult FIFOOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.depth)))
    return ::mlir::failure();
  return ::mlir::success();
}

void FIFOOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.depth);
}

uint64_t FIFOOp::getDepth() {
  auto attr = getDepthAttr();
  return attr.getValue().getZExtValue();
}

void FIFOOp::setDepth(uint64_t attrValue) {
  getProperties().depth = ::mlir::Builder((*this)->getContext()).getIntegerAttr(::mlir::Builder((*this)->getContext()).getIntegerType(64), attrValue);
}

void FIFOOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type output, ::mlir::Value clk, ::mlir::Value rst, ::mlir::Value input, ::mlir::IntegerAttr depth) {
  odsState.addOperands(clk);
  odsState.addOperands(rst);
  odsState.addOperands(input);
  odsState.getOrAddProperties<Properties>().depth = depth;
  odsState.addTypes(output);
}

FIFOOp FIFOOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type output, ::mlir::Value clk, ::mlir::Value rst, ::mlir::Value input, ::mlir::IntegerAttr depth) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(output)>(output), std::forward<decltype(clk)>(clk), std::forward<decltype(rst)>(rst), std::forward<decltype(input)>(input), std::forward<decltype(depth)>(depth));
  auto __res__ = ::llvm::dyn_cast<FIFOOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

FIFOOp FIFOOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type output, ::mlir::Value clk, ::mlir::Value rst, ::mlir::Value input, ::mlir::IntegerAttr depth) {
  return create(builder, builder.getLoc(), std::forward<decltype(output)>(output), std::forward<decltype(clk)>(clk), std::forward<decltype(rst)>(rst), std::forward<decltype(input)>(input), std::forward<decltype(depth)>(depth));
}

void FIFOOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value clk, ::mlir::Value rst, ::mlir::Value input, ::mlir::IntegerAttr depth) {
  odsState.addOperands(clk);
  odsState.addOperands(rst);
  odsState.addOperands(input);
  odsState.getOrAddProperties<Properties>().depth = depth;
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

FIFOOp FIFOOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value clk, ::mlir::Value rst, ::mlir::Value input, ::mlir::IntegerAttr depth) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(clk)>(clk), std::forward<decltype(rst)>(rst), std::forward<decltype(input)>(input), std::forward<decltype(depth)>(depth));
  auto __res__ = ::llvm::dyn_cast<FIFOOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

FIFOOp FIFOOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value clk, ::mlir::Value rst, ::mlir::Value input, ::mlir::IntegerAttr depth) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(clk)>(clk), std::forward<decltype(rst)>(rst), std::forward<decltype(input)>(input), std::forward<decltype(depth)>(depth));
}

void FIFOOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type output, ::mlir::Value clk, ::mlir::Value rst, ::mlir::Value input, uint64_t depth) {
  odsState.addOperands(clk);
  odsState.addOperands(rst);
  odsState.addOperands(input);
  odsState.getOrAddProperties<Properties>().depth = odsBuilder.getIntegerAttr(odsBuilder.getIntegerType(64), depth);
  odsState.addTypes(output);
}

FIFOOp FIFOOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type output, ::mlir::Value clk, ::mlir::Value rst, ::mlir::Value input, uint64_t depth) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(output)>(output), std::forward<decltype(clk)>(clk), std::forward<decltype(rst)>(rst), std::forward<decltype(input)>(input), std::forward<decltype(depth)>(depth));
  auto __res__ = ::llvm::dyn_cast<FIFOOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

FIFOOp FIFOOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type output, ::mlir::Value clk, ::mlir::Value rst, ::mlir::Value input, uint64_t depth) {
  return create(builder, builder.getLoc(), std::forward<decltype(output)>(output), std::forward<decltype(clk)>(clk), std::forward<decltype(rst)>(rst), std::forward<decltype(input)>(input), std::forward<decltype(depth)>(depth));
}

void FIFOOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value clk, ::mlir::Value rst, ::mlir::Value input, uint64_t depth) {
  odsState.addOperands(clk);
  odsState.addOperands(rst);
  odsState.addOperands(input);
  odsState.getOrAddProperties<Properties>().depth = odsBuilder.getIntegerAttr(odsBuilder.getIntegerType(64), depth);
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

FIFOOp FIFOOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value clk, ::mlir::Value rst, ::mlir::Value input, uint64_t depth) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(clk)>(clk), std::forward<decltype(rst)>(rst), std::forward<decltype(input)>(input), std::forward<decltype(depth)>(depth));
  auto __res__ = ::llvm::dyn_cast<FIFOOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

FIFOOp FIFOOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value clk, ::mlir::Value rst, ::mlir::Value input, uint64_t depth) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(clk)>(clk), std::forward<decltype(rst)>(rst), std::forward<decltype(input)>(input), std::forward<decltype(depth)>(depth));
}

void FIFOOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 3u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
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
  assert(operands.size() == 3u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
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
  auto tblgen_depth = getProperties().depth; (void)tblgen_depth;
  if (!tblgen_depth) return emitOpError("requires attribute 'depth'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_ESI4(*this, tblgen_depth, "depth")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_ESI1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSOperands(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_ESI2(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup2 = getODSOperands(2);

    for (auto v : valueGroup2) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_ESI3(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_ESI3(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult FIFOOp::verifyInvariants() {
  if(::mlir::succeeded(verifyInvariantsImpl()) && ::mlir::succeeded(verify()))
    return ::mlir::success();
  return ::mlir::failure();
}

::mlir::ParseResult FIFOOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::OpAsmParser::UnresolvedOperand inputRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> inputOperands(&inputRawOperand, 1);  ::llvm::SMLoc inputOperandsLoc;
  (void)inputOperandsLoc;
  ::mlir::OpAsmParser::UnresolvedOperand clkRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> clkOperands(&clkRawOperand, 1);  ::llvm::SMLoc clkOperandsLoc;
  (void)clkOperandsLoc;
  ::mlir::OpAsmParser::UnresolvedOperand rstRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> rstOperands(&rstRawOperand, 1);  ::llvm::SMLoc rstOperandsLoc;
  (void)rstOperandsLoc;
  ::mlir::IntegerAttr depthAttr;
  ::mlir::Type inputRawType{};
  ::llvm::ArrayRef<::mlir::Type> inputTypes(&inputRawType, 1);
  ::mlir::Type outputRawType{};
  ::llvm::ArrayRef<::mlir::Type> outputTypes(&outputRawType, 1);
  if (parser.parseKeyword("in"))
    return ::mlir::failure();

  inputOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(inputRawOperand))
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
  if (parser.parseKeyword("depth"))
    return ::mlir::failure();

  if (parser.parseCustomAttributeWithFallback(depthAttr, parser.getBuilder().getIntegerType(64))) {
    return ::mlir::failure();
  }
  if (depthAttr) result.getOrAddProperties<FIFOOp::Properties>().depth = depthAttr;
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
    ::circt::esi::ChannelType type;
    if (parser.parseCustomTypeWithFallback(type))
      return ::mlir::failure();
    inputRawType = type;
  }
  if (parser.parseArrow())
    return ::mlir::failure();

  {
    ::circt::esi::ChannelType type;
    if (parser.parseCustomTypeWithFallback(type))
      return ::mlir::failure();
    outputRawType = type;
  }
  ::mlir::Type odsBuildableType0 = parser.getBuilder().getType<::circt::seq::ClockType>();
  ::mlir::Type odsBuildableType1 = parser.getBuilder().getIntegerType(1);
  result.addTypes(outputTypes);
  if (parser.resolveOperands(clkOperands, odsBuildableType0, clkOperandsLoc, result.operands))
    return ::mlir::failure();
  if (parser.resolveOperands(rstOperands, odsBuildableType1, rstOperandsLoc, result.operands))
    return ::mlir::failure();
  if (parser.resolveOperands(inputOperands, inputTypes, inputOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void FIFOOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ' << "in";
  _odsPrinter << ' ';
  _odsPrinter << getInput();
  _odsPrinter << ' ' << "clk";
  _odsPrinter << ' ';
  _odsPrinter << getClk();
  _odsPrinter << ' ' << "rst";
  _odsPrinter << ' ';
  _odsPrinter << getRst();
  _odsPrinter << ' ' << "depth";
  _odsPrinter << ' ';
  _odsPrinter.printAttributeWithoutType(getDepthAttr());
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("depth");
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
  {
    auto type = getInput().getType();
    if (auto validType = ::llvm::dyn_cast<::circt::esi::ChannelType>(type))
      _odsPrinter.printStrippedAttrOrType(validType);
   else
     _odsPrinter << type;
  }
  _odsPrinter << ' ' << "->";
  _odsPrinter << ' ';
  {
    auto type = getOutput().getType();
    if (auto validType = ::llvm::dyn_cast<::circt::esi::ChannelType>(type))
      _odsPrinter.printStrippedAttrOrType(validType);
   else
     _odsPrinter << type;
  }
}


} // namespace circt::esi
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::esi::FIFOOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::esi::detail::FIFOOpGenericAdaptorBase::Properties)

namespace circt::esi {


//===----------------------------------------------------------------------===//
// ::circt::esi::FuncServiceDeclOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

FuncServiceDeclOpGenericAdaptorBase::FuncServiceDeclOpGenericAdaptorBase(FuncServiceDeclOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::llvm::StringRef FuncServiceDeclOpGenericAdaptorBase::getSymName() {
  auto attr = getSymNameAttr();
  return attr.getValue();
}


} // namespace detail
FuncServiceDeclOpAdaptor::FuncServiceDeclOpAdaptor(FuncServiceDeclOp op) : FuncServiceDeclOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult FuncServiceDeclOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;
  if (!tblgen_sym_name) return emitError(loc, "'esi.service.std.func' op requires attribute 'sym_name'");

  if (tblgen_sym_name && !((::llvm::isa<::mlir::StringAttr>(tblgen_sym_name))))
    return emitError(loc, "'esi.service.std.func' op attribute 'sym_name' failed to satisfy constraint: string attribute");
  return ::mlir::success();
}

::llvm::LogicalResult FuncServiceDeclOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
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

::mlir::Attribute FuncServiceDeclOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
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

llvm::hash_code FuncServiceDeclOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.sym_name.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> FuncServiceDeclOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "sym_name")
      return prop.sym_name;
  return std::nullopt;
}

void FuncServiceDeclOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "sym_name") {
       prop.sym_name = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.sym_name)>>(value);
       return;
    }
}

void FuncServiceDeclOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.sym_name) attrs.append("sym_name", prop.sym_name);
}

::llvm::LogicalResult FuncServiceDeclOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getSymNameAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_ESI3(attr, "sym_name", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult FuncServiceDeclOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.sym_name)))
    return ::mlir::failure();
  return ::mlir::success();
}

void FuncServiceDeclOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.sym_name);
}

::llvm::StringRef FuncServiceDeclOp::getSymName() {
  auto attr = getSymNameAttr();
  return attr.getValue();
}

void FuncServiceDeclOp::setSymName(::llvm::StringRef attrValue) {
  getProperties().sym_name = ::mlir::Builder((*this)->getContext()).getStringAttr(attrValue);
}

void FuncServiceDeclOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::StringAttr sym_name) {
  odsState.getOrAddProperties<Properties>().sym_name = sym_name;
}

FuncServiceDeclOp FuncServiceDeclOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::StringAttr sym_name) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(sym_name)>(sym_name));
  auto __res__ = ::llvm::dyn_cast<FuncServiceDeclOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

FuncServiceDeclOp FuncServiceDeclOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::StringAttr sym_name) {
  return create(builder, builder.getLoc(), std::forward<decltype(sym_name)>(sym_name));
}

void FuncServiceDeclOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name) {
  odsState.getOrAddProperties<Properties>().sym_name = sym_name;
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

FuncServiceDeclOp FuncServiceDeclOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(sym_name)>(sym_name));
  auto __res__ = ::llvm::dyn_cast<FuncServiceDeclOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

FuncServiceDeclOp FuncServiceDeclOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(sym_name)>(sym_name));
}

void FuncServiceDeclOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::llvm::StringRef sym_name) {
  odsState.getOrAddProperties<Properties>().sym_name = odsBuilder.getStringAttr(sym_name);
}

FuncServiceDeclOp FuncServiceDeclOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::llvm::StringRef sym_name) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(sym_name)>(sym_name));
  auto __res__ = ::llvm::dyn_cast<FuncServiceDeclOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

FuncServiceDeclOp FuncServiceDeclOp::create(::mlir::ImplicitLocOpBuilder &builder, ::llvm::StringRef sym_name) {
  return create(builder, builder.getLoc(), std::forward<decltype(sym_name)>(sym_name));
}

void FuncServiceDeclOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name) {
  odsState.getOrAddProperties<Properties>().sym_name = odsBuilder.getStringAttr(sym_name);
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

FuncServiceDeclOp FuncServiceDeclOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(sym_name)>(sym_name));
  auto __res__ = ::llvm::dyn_cast<FuncServiceDeclOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

FuncServiceDeclOp FuncServiceDeclOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(sym_name)>(sym_name));
}

void FuncServiceDeclOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<FuncServiceDeclOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

FuncServiceDeclOp FuncServiceDeclOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<FuncServiceDeclOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

FuncServiceDeclOp FuncServiceDeclOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void FuncServiceDeclOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

FuncServiceDeclOp FuncServiceDeclOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<FuncServiceDeclOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

FuncServiceDeclOp FuncServiceDeclOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult FuncServiceDeclOp::verifyInvariantsImpl() {
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;
  if (!tblgen_sym_name) return emitOpError("requires attribute 'sym_name'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_ESI3(*this, tblgen_sym_name, "sym_name")))
    return ::mlir::failure();
  return ::mlir::success();
}

::llvm::LogicalResult FuncServiceDeclOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult FuncServiceDeclOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::StringAttr sym_nameAttr;

  if (parser.parseSymbolName(sym_nameAttr))
    return ::mlir::failure();
  if (sym_nameAttr) result.getOrAddProperties<FuncServiceDeclOp::Properties>().sym_name = sym_nameAttr;
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

void FuncServiceDeclOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter.printSymbolName(getSymNameAttr().getValue());
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("sym_name");
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
}


} // namespace circt::esi
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::esi::FuncServiceDeclOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::esi::detail::FuncServiceDeclOpGenericAdaptorBase::Properties)

namespace circt::esi {


//===----------------------------------------------------------------------===//
// ::circt::esi::HostMemServiceDeclOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

HostMemServiceDeclOpGenericAdaptorBase::HostMemServiceDeclOpGenericAdaptorBase(HostMemServiceDeclOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::llvm::StringRef HostMemServiceDeclOpGenericAdaptorBase::getSymName() {
  auto attr = getSymNameAttr();
  return attr.getValue();
}


} // namespace detail
HostMemServiceDeclOpAdaptor::HostMemServiceDeclOpAdaptor(HostMemServiceDeclOp op) : HostMemServiceDeclOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult HostMemServiceDeclOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;
  if (!tblgen_sym_name) return emitError(loc, "'esi.service.std.hostmem' op requires attribute 'sym_name'");

  if (tblgen_sym_name && !((::llvm::isa<::mlir::StringAttr>(tblgen_sym_name))))
    return emitError(loc, "'esi.service.std.hostmem' op attribute 'sym_name' failed to satisfy constraint: string attribute");
  return ::mlir::success();
}

::llvm::LogicalResult HostMemServiceDeclOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
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

::mlir::Attribute HostMemServiceDeclOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
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

llvm::hash_code HostMemServiceDeclOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.sym_name.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> HostMemServiceDeclOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "sym_name")
      return prop.sym_name;
  return std::nullopt;
}

void HostMemServiceDeclOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "sym_name") {
       prop.sym_name = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.sym_name)>>(value);
       return;
    }
}

void HostMemServiceDeclOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.sym_name) attrs.append("sym_name", prop.sym_name);
}

::llvm::LogicalResult HostMemServiceDeclOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getSymNameAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_ESI3(attr, "sym_name", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult HostMemServiceDeclOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.sym_name)))
    return ::mlir::failure();
  return ::mlir::success();
}

void HostMemServiceDeclOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.sym_name);
}

::llvm::StringRef HostMemServiceDeclOp::getSymName() {
  auto attr = getSymNameAttr();
  return attr.getValue();
}

void HostMemServiceDeclOp::setSymName(::llvm::StringRef attrValue) {
  getProperties().sym_name = ::mlir::Builder((*this)->getContext()).getStringAttr(attrValue);
}

void HostMemServiceDeclOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::StringAttr sym_name) {
  odsState.getOrAddProperties<Properties>().sym_name = sym_name;
}

HostMemServiceDeclOp HostMemServiceDeclOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::StringAttr sym_name) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(sym_name)>(sym_name));
  auto __res__ = ::llvm::dyn_cast<HostMemServiceDeclOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

HostMemServiceDeclOp HostMemServiceDeclOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::StringAttr sym_name) {
  return create(builder, builder.getLoc(), std::forward<decltype(sym_name)>(sym_name));
}

void HostMemServiceDeclOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name) {
  odsState.getOrAddProperties<Properties>().sym_name = sym_name;
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

HostMemServiceDeclOp HostMemServiceDeclOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(sym_name)>(sym_name));
  auto __res__ = ::llvm::dyn_cast<HostMemServiceDeclOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

HostMemServiceDeclOp HostMemServiceDeclOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(sym_name)>(sym_name));
}

void HostMemServiceDeclOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::llvm::StringRef sym_name) {
  odsState.getOrAddProperties<Properties>().sym_name = odsBuilder.getStringAttr(sym_name);
}

HostMemServiceDeclOp HostMemServiceDeclOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::llvm::StringRef sym_name) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(sym_name)>(sym_name));
  auto __res__ = ::llvm::dyn_cast<HostMemServiceDeclOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

HostMemServiceDeclOp HostMemServiceDeclOp::create(::mlir::ImplicitLocOpBuilder &builder, ::llvm::StringRef sym_name) {
  return create(builder, builder.getLoc(), std::forward<decltype(sym_name)>(sym_name));
}

void HostMemServiceDeclOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name) {
  odsState.getOrAddProperties<Properties>().sym_name = odsBuilder.getStringAttr(sym_name);
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

HostMemServiceDeclOp HostMemServiceDeclOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(sym_name)>(sym_name));
  auto __res__ = ::llvm::dyn_cast<HostMemServiceDeclOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

HostMemServiceDeclOp HostMemServiceDeclOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(sym_name)>(sym_name));
}

void HostMemServiceDeclOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<HostMemServiceDeclOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

HostMemServiceDeclOp HostMemServiceDeclOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<HostMemServiceDeclOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

HostMemServiceDeclOp HostMemServiceDeclOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void HostMemServiceDeclOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

HostMemServiceDeclOp HostMemServiceDeclOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<HostMemServiceDeclOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

HostMemServiceDeclOp HostMemServiceDeclOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult HostMemServiceDeclOp::verifyInvariantsImpl() {
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;
  if (!tblgen_sym_name) return emitOpError("requires attribute 'sym_name'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_ESI3(*this, tblgen_sym_name, "sym_name")))
    return ::mlir::failure();
  return ::mlir::success();
}

::llvm::LogicalResult HostMemServiceDeclOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult HostMemServiceDeclOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::StringAttr sym_nameAttr;

  if (parser.parseSymbolName(sym_nameAttr))
    return ::mlir::failure();
  if (sym_nameAttr) result.getOrAddProperties<HostMemServiceDeclOp::Properties>().sym_name = sym_nameAttr;
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

void HostMemServiceDeclOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter.printSymbolName(getSymNameAttr().getValue());
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("sym_name");
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
}


} // namespace circt::esi
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::esi::HostMemServiceDeclOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::esi::detail::HostMemServiceDeclOpGenericAdaptorBase::Properties)

namespace circt::esi {


//===----------------------------------------------------------------------===//
// ::circt::esi::MMIOServiceDeclOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

MMIOServiceDeclOpGenericAdaptorBase::MMIOServiceDeclOpGenericAdaptorBase(MMIOServiceDeclOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::llvm::StringRef MMIOServiceDeclOpGenericAdaptorBase::getSymName() {
  auto attr = getSymNameAttr();
  return attr.getValue();
}


} // namespace detail
MMIOServiceDeclOpAdaptor::MMIOServiceDeclOpAdaptor(MMIOServiceDeclOp op) : MMIOServiceDeclOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult MMIOServiceDeclOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;
  if (!tblgen_sym_name) return emitError(loc, "'esi.service.std.mmio' op requires attribute 'sym_name'");

  if (tblgen_sym_name && !((::llvm::isa<::mlir::StringAttr>(tblgen_sym_name))))
    return emitError(loc, "'esi.service.std.mmio' op attribute 'sym_name' failed to satisfy constraint: string attribute");
  return ::mlir::success();
}

::llvm::LogicalResult MMIOServiceDeclOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
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

::mlir::Attribute MMIOServiceDeclOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
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

llvm::hash_code MMIOServiceDeclOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.sym_name.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> MMIOServiceDeclOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "sym_name")
      return prop.sym_name;
  return std::nullopt;
}

void MMIOServiceDeclOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "sym_name") {
       prop.sym_name = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.sym_name)>>(value);
       return;
    }
}

void MMIOServiceDeclOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.sym_name) attrs.append("sym_name", prop.sym_name);
}

::llvm::LogicalResult MMIOServiceDeclOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getSymNameAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_ESI3(attr, "sym_name", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult MMIOServiceDeclOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.sym_name)))
    return ::mlir::failure();
  return ::mlir::success();
}

void MMIOServiceDeclOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.sym_name);
}

::llvm::StringRef MMIOServiceDeclOp::getSymName() {
  auto attr = getSymNameAttr();
  return attr.getValue();
}

void MMIOServiceDeclOp::setSymName(::llvm::StringRef attrValue) {
  getProperties().sym_name = ::mlir::Builder((*this)->getContext()).getStringAttr(attrValue);
}

void MMIOServiceDeclOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::StringAttr sym_name) {
  odsState.getOrAddProperties<Properties>().sym_name = sym_name;
}

MMIOServiceDeclOp MMIOServiceDeclOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::StringAttr sym_name) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(sym_name)>(sym_name));
  auto __res__ = ::llvm::dyn_cast<MMIOServiceDeclOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

MMIOServiceDeclOp MMIOServiceDeclOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::StringAttr sym_name) {
  return create(builder, builder.getLoc(), std::forward<decltype(sym_name)>(sym_name));
}

void MMIOServiceDeclOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name) {
  odsState.getOrAddProperties<Properties>().sym_name = sym_name;
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

MMIOServiceDeclOp MMIOServiceDeclOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(sym_name)>(sym_name));
  auto __res__ = ::llvm::dyn_cast<MMIOServiceDeclOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

MMIOServiceDeclOp MMIOServiceDeclOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(sym_name)>(sym_name));
}

void MMIOServiceDeclOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::llvm::StringRef sym_name) {
  odsState.getOrAddProperties<Properties>().sym_name = odsBuilder.getStringAttr(sym_name);
}

MMIOServiceDeclOp MMIOServiceDeclOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::llvm::StringRef sym_name) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(sym_name)>(sym_name));
  auto __res__ = ::llvm::dyn_cast<MMIOServiceDeclOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

MMIOServiceDeclOp MMIOServiceDeclOp::create(::mlir::ImplicitLocOpBuilder &builder, ::llvm::StringRef sym_name) {
  return create(builder, builder.getLoc(), std::forward<decltype(sym_name)>(sym_name));
}

void MMIOServiceDeclOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name) {
  odsState.getOrAddProperties<Properties>().sym_name = odsBuilder.getStringAttr(sym_name);
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

MMIOServiceDeclOp MMIOServiceDeclOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(sym_name)>(sym_name));
  auto __res__ = ::llvm::dyn_cast<MMIOServiceDeclOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

MMIOServiceDeclOp MMIOServiceDeclOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(sym_name)>(sym_name));
}

void MMIOServiceDeclOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<MMIOServiceDeclOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

MMIOServiceDeclOp MMIOServiceDeclOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<MMIOServiceDeclOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

MMIOServiceDeclOp MMIOServiceDeclOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void MMIOServiceDeclOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

MMIOServiceDeclOp MMIOServiceDeclOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<MMIOServiceDeclOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

MMIOServiceDeclOp MMIOServiceDeclOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult MMIOServiceDeclOp::verifyInvariantsImpl() {
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;
  if (!tblgen_sym_name) return emitOpError("requires attribute 'sym_name'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_ESI3(*this, tblgen_sym_name, "sym_name")))
    return ::mlir::failure();
  return ::mlir::success();
}

::llvm::LogicalResult MMIOServiceDeclOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult MMIOServiceDeclOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::StringAttr sym_nameAttr;

  if (parser.parseSymbolName(sym_nameAttr))
    return ::mlir::failure();
  if (sym_nameAttr) result.getOrAddProperties<MMIOServiceDeclOp::Properties>().sym_name = sym_nameAttr;
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

void MMIOServiceDeclOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter.printSymbolName(getSymNameAttr().getValue());
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("sym_name");
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
}


} // namespace circt::esi
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::esi::MMIOServiceDeclOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::esi::detail::MMIOServiceDeclOpGenericAdaptorBase::Properties)

namespace circt::esi {


//===----------------------------------------------------------------------===//
// ::circt::esi::NullSourceOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

NullSourceOpGenericAdaptorBase::NullSourceOpGenericAdaptorBase(NullSourceOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}


} // namespace detail
NullSourceOpAdaptor::NullSourceOpAdaptor(NullSourceOp op) : NullSourceOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult NullSourceOpAdaptor::verify(::mlir::Location loc) {
  return ::mlir::success();
}

::llvm::LogicalResult NullSourceOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }
      return ::mlir::success();
}

::mlir::Attribute NullSourceOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code NullSourceOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine();
}

std::optional<mlir::Attribute> NullSourceOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
  return std::nullopt;
}

void NullSourceOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
}

void NullSourceOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
}

::llvm::LogicalResult NullSourceOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    return ::mlir::success();
}

void NullSourceOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type out) {
  odsState.addTypes(out);
}

NullSourceOp NullSourceOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type out) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(out)>(out));
  auto __res__ = ::llvm::dyn_cast<NullSourceOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

NullSourceOp NullSourceOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type out) {
  return create(builder, builder.getLoc(), std::forward<decltype(out)>(out));
}

void NullSourceOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes) {
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

NullSourceOp NullSourceOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes));
  auto __res__ = ::llvm::dyn_cast<NullSourceOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

NullSourceOp NullSourceOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes));
}

void NullSourceOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

NullSourceOp NullSourceOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<NullSourceOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

NullSourceOp NullSourceOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void NullSourceOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

NullSourceOp NullSourceOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<NullSourceOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

NullSourceOp NullSourceOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult NullSourceOp::verifyInvariantsImpl() {
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_ESI3(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult NullSourceOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult NullSourceOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::Type outRawType{};
  ::llvm::ArrayRef<::mlir::Type> outTypes(&outRawType, 1);
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

void NullSourceOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
   _odsPrinter << getOut().getType();
}

void NullSourceOp::getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects) {
}


} // namespace circt::esi
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::esi::NullSourceOp)

namespace circt::esi {


//===----------------------------------------------------------------------===//
// ::circt::esi::PackBundleOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

PackBundleOpGenericAdaptorBase::PackBundleOpGenericAdaptorBase(PackBundleOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

std::pair<unsigned, unsigned> PackBundleOpGenericAdaptorBase::getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
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
PackBundleOpAdaptor::PackBundleOpAdaptor(PackBundleOp op) : PackBundleOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult PackBundleOpAdaptor::verify(::mlir::Location loc) {
  return ::mlir::success();
}

std::pair<unsigned, unsigned> PackBundleOp::getODSOperandIndexAndLength(unsigned index) {
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

::mlir::MutableOperandRange PackBundleOp::getToChannelsMutable() {
  auto range = getODSOperandIndexAndLength(0);
  auto mutableRange = ::mlir::MutableOperandRange(getOperation(), range.first, range.second);
  return mutableRange;
}

std::pair<unsigned, unsigned> PackBundleOp::getODSResultIndexAndLength(unsigned index) {
  bool isVariadic[] = {false, true};
  int prevVariadicCount = 0;
  for (unsigned i = 0; i < index; ++i)
    if (isVariadic[i]) ++prevVariadicCount;

  // Calculate how many dynamic values a static variadic operand corresponds to.
  // This assumes all static variadic operands have the same dynamic value count.
  int variadicSize = (getOperation()->getNumResults() - 1) / 1;
  // `index` passed in as the parameter is the static index which counts each
  // operand (variadic or not) as size 1. So here for each previous static variadic
  // operand, we need to offset by (variadicSize - 1) to get where the dynamic
  // value pack for this static operand starts.
  int start = index + (variadicSize - 1) * prevVariadicCount;
  int size = isVariadic[index] ? variadicSize : 1;
  return {start, size};
}

::llvm::LogicalResult PackBundleOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }
      return ::mlir::success();
}

::mlir::Attribute PackBundleOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code PackBundleOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine();
}

std::optional<mlir::Attribute> PackBundleOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
  return std::nullopt;
}

void PackBundleOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
}

void PackBundleOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
}

::llvm::LogicalResult PackBundleOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    return ::mlir::success();
}

PackBundleOp PackBundleOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ChannelBundleType bundleType, mlir::ValueRange toChannels) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(bundleType)>(bundleType), std::forward<decltype(toChannels)>(toChannels));
  auto __res__ = ::llvm::dyn_cast<PackBundleOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

PackBundleOp PackBundleOp::create(::mlir::ImplicitLocOpBuilder &builder, ChannelBundleType bundleType, mlir::ValueRange toChannels) {
  return create(builder, builder.getLoc(), std::forward<decltype(bundleType)>(bundleType), std::forward<decltype(toChannels)>(toChannels));
}

::llvm::LogicalResult PackBundleOp::verifyInvariantsImpl() {
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_ESI5(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_ESI6(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSResults(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_ESI5(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult PackBundleOp::verifyInvariants() {
  if(::mlir::succeeded(verifyInvariantsImpl()) && ::mlir::succeeded(verify()))
    return ::mlir::success();
  return ::mlir::failure();
}

void PackBundleOp::getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context) {
  results.add(canonicalize);
}

::mlir::ParseResult PackBundleOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::llvm::SmallVector<::mlir::OpAsmParser::UnresolvedOperand, 4> toChannelsOperands;
  ::llvm::SMLoc toChannelsOperandsLoc;
  (void)toChannelsOperandsLoc;
  ::llvm::SmallVector<::mlir::Type, 1> toChannelsTypes;
  ::llvm::SmallVector<::mlir::Type, 1> fromChannelsTypes;
  ::mlir::Type bundleRawType{};
  ::llvm::ArrayRef<::mlir::Type> bundleTypes(&bundleRawType, 1);

  toChannelsOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperandList(toChannelsOperands))
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
    auto odsResult = parseUnPackBundleType(parser, toChannelsTypes, fromChannelsTypes, bundleRawType);
    if (odsResult) return ::mlir::failure();
  }
  result.addTypes(bundleTypes);
  result.addTypes(fromChannelsTypes);
  if (parser.resolveOperands(toChannelsOperands, toChannelsTypes, toChannelsOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void PackBundleOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter << getToChannels();
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
  printUnPackBundleType(_odsPrinter, *this, getToChannels().getTypes(), getFromChannels().getTypes(), getBundle().getType());
}


} // namespace circt::esi
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::esi::PackBundleOp)

namespace circt::esi {


//===----------------------------------------------------------------------===//
// ::circt::esi::PipelineStageOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

PipelineStageOpGenericAdaptorBase::PipelineStageOpGenericAdaptorBase(PipelineStageOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}


} // namespace detail
PipelineStageOpAdaptor::PipelineStageOpAdaptor(PipelineStageOp op) : PipelineStageOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult PipelineStageOpAdaptor::verify(::mlir::Location loc) {
  return ::mlir::success();
}

::llvm::LogicalResult PipelineStageOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }
      return ::mlir::success();
}

::mlir::Attribute PipelineStageOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code PipelineStageOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine();
}

std::optional<mlir::Attribute> PipelineStageOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
  return std::nullopt;
}

void PipelineStageOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
}

void PipelineStageOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
}

::llvm::LogicalResult PipelineStageOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    return ::mlir::success();
}

void PipelineStageOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type output, ::mlir::Value clk, ::mlir::Value rst, ::mlir::Value input) {
  odsState.addOperands(clk);
  odsState.addOperands(rst);
  odsState.addOperands(input);
  odsState.addTypes(output);
}

PipelineStageOp PipelineStageOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type output, ::mlir::Value clk, ::mlir::Value rst, ::mlir::Value input) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(output)>(output), std::forward<decltype(clk)>(clk), std::forward<decltype(rst)>(rst), std::forward<decltype(input)>(input));
  auto __res__ = ::llvm::dyn_cast<PipelineStageOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

PipelineStageOp PipelineStageOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type output, ::mlir::Value clk, ::mlir::Value rst, ::mlir::Value input) {
  return create(builder, builder.getLoc(), std::forward<decltype(output)>(output), std::forward<decltype(clk)>(clk), std::forward<decltype(rst)>(rst), std::forward<decltype(input)>(input));
}

void PipelineStageOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value clk, ::mlir::Value rst, ::mlir::Value input) {
  odsState.addOperands(clk);
  odsState.addOperands(rst);
  odsState.addOperands(input);

        ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
        if (::mlir::succeeded(PipelineStageOp::inferReturnTypes(odsBuilder.getContext(),
                      odsState.location, odsState.operands,
                      odsState.attributes.getDictionary(odsState.getContext()),
                      odsState.getRawProperties(),
                      odsState.regions, inferredReturnTypes)))
          odsState.addTypes(inferredReturnTypes);
        else
          ::mlir::detail::reportFatalInferReturnTypesError(odsState);
        
}

PipelineStageOp PipelineStageOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value clk, ::mlir::Value rst, ::mlir::Value input) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(clk)>(clk), std::forward<decltype(rst)>(rst), std::forward<decltype(input)>(input));
  auto __res__ = ::llvm::dyn_cast<PipelineStageOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

PipelineStageOp PipelineStageOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value clk, ::mlir::Value rst, ::mlir::Value input) {
  return create(builder, builder.getLoc(), std::forward<decltype(clk)>(clk), std::forward<decltype(rst)>(rst), std::forward<decltype(input)>(input));
}

void PipelineStageOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value clk, ::mlir::Value rst, ::mlir::Value input) {
  odsState.addOperands(clk);
  odsState.addOperands(rst);
  odsState.addOperands(input);
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

PipelineStageOp PipelineStageOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value clk, ::mlir::Value rst, ::mlir::Value input) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(clk)>(clk), std::forward<decltype(rst)>(rst), std::forward<decltype(input)>(input));
  auto __res__ = ::llvm::dyn_cast<PipelineStageOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

PipelineStageOp PipelineStageOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value clk, ::mlir::Value rst, ::mlir::Value input) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(clk)>(clk), std::forward<decltype(rst)>(rst), std::forward<decltype(input)>(input));
}

void PipelineStageOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 3u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

PipelineStageOp PipelineStageOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<PipelineStageOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

PipelineStageOp PipelineStageOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void PipelineStageOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 3u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);

  ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
  if (::mlir::succeeded(PipelineStageOp::inferReturnTypes(odsBuilder.getContext(),
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

PipelineStageOp PipelineStageOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<PipelineStageOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

PipelineStageOp PipelineStageOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void PipelineStageOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 3u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

PipelineStageOp PipelineStageOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<PipelineStageOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

PipelineStageOp PipelineStageOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

void PipelineStageOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 3u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties &>(properties));
  odsState.addAttributes(discardableAttributes);

  ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
  if (::mlir::succeeded(PipelineStageOp::inferReturnTypes(odsBuilder.getContext(),
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

PipelineStageOp PipelineStageOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<PipelineStageOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

PipelineStageOp PipelineStageOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult PipelineStageOp::verifyInvariantsImpl() {
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_ESI1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSOperands(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_ESI2(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup2 = getODSOperands(2);

    for (auto v : valueGroup2) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_ESI3(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_ESI3(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  if (!((((*this->getODSOperands(2).begin()).getType()) == ((*this->getODSResults(0).begin()).getType()) && ((*this->getODSResults(0).begin()).getType()) == ((*this->getODSOperands(2).begin()).getType()))))
    return emitOpError("failed to verify that all of {input, output} have same type");
  return ::mlir::success();
}

::llvm::LogicalResult PipelineStageOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::llvm::LogicalResult PipelineStageOp::inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::PropertyRef properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes) {
  inferredReturnTypes.resize(1);
  ::mlir::Builder odsBuilder(context);
  if (operands.size() <= 2)
    return ::mlir::failure();
  ::mlir::Type odsInferredType0 = operands[2].getType();
  inferredReturnTypes[0] = odsInferredType0;
  return ::mlir::success();
}

::mlir::ParseResult PipelineStageOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::OpAsmParser::UnresolvedOperand clkRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> clkOperands(&clkRawOperand, 1);  ::llvm::SMLoc clkOperandsLoc;
  (void)clkOperandsLoc;
  ::mlir::OpAsmParser::UnresolvedOperand rstRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> rstOperands(&rstRawOperand, 1);  ::llvm::SMLoc rstOperandsLoc;
  (void)rstOperandsLoc;
  ::mlir::OpAsmParser::UnresolvedOperand inputRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> inputOperands(&inputRawOperand, 1);  ::llvm::SMLoc inputOperandsLoc;
  (void)inputOperandsLoc;
  ::mlir::Type inputRawType{};
  ::llvm::ArrayRef<::mlir::Type> inputTypes(&inputRawType, 1);

  clkOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(clkRawOperand))
    return ::mlir::failure();
  if (parser.parseComma())
    return ::mlir::failure();

  rstOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(rstRawOperand))
    return ::mlir::failure();
  if (parser.parseComma())
    return ::mlir::failure();

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
  ::mlir::Type odsBuildableType0 = parser.getBuilder().getType<::circt::seq::ClockType>();
  ::mlir::Type odsBuildableType1 = parser.getBuilder().getIntegerType(1);
  result.addTypes(inputTypes[0]);
  if (parser.resolveOperands(clkOperands, odsBuildableType0, clkOperandsLoc, result.operands))
    return ::mlir::failure();
  if (parser.resolveOperands(rstOperands, odsBuildableType1, rstOperandsLoc, result.operands))
    return ::mlir::failure();
  if (parser.resolveOperands(inputOperands, inputTypes, inputOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void PipelineStageOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter << getClk();
  _odsPrinter << ",";
  _odsPrinter << ' ';
  _odsPrinter << getRst();
  _odsPrinter << ",";
  _odsPrinter << ' ';
  _odsPrinter << getInput();
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
   _odsPrinter << getInput().getType();
}

void PipelineStageOp::getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects) {
}


} // namespace circt::esi
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::esi::PipelineStageOp)

namespace circt::esi {


//===----------------------------------------------------------------------===//
// ::circt::esi::RandomAccessMemoryDeclOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

RandomAccessMemoryDeclOpGenericAdaptorBase::RandomAccessMemoryDeclOpGenericAdaptorBase(RandomAccessMemoryDeclOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::llvm::StringRef RandomAccessMemoryDeclOpGenericAdaptorBase::getSymName() {
  auto attr = getSymNameAttr();
  return attr.getValue();
}

::mlir::Type RandomAccessMemoryDeclOpGenericAdaptorBase::getInnerType() {
  auto attr = getInnerTypeAttr();
  return ::llvm::cast<::mlir::Type>(attr.getValue());
}

uint64_t RandomAccessMemoryDeclOpGenericAdaptorBase::getDepth() {
  auto attr = getDepthAttr();
  return attr.getValue().getZExtValue();
}


} // namespace detail
RandomAccessMemoryDeclOpAdaptor::RandomAccessMemoryDeclOpAdaptor(RandomAccessMemoryDeclOp op) : RandomAccessMemoryDeclOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult RandomAccessMemoryDeclOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_depth = getProperties().depth; (void)tblgen_depth;
  if (!tblgen_depth) return emitError(loc, "'esi.mem.ram' op requires attribute 'depth'");
  auto tblgen_innerType = getProperties().innerType; (void)tblgen_innerType;
  if (!tblgen_innerType) return emitError(loc, "'esi.mem.ram' op requires attribute 'innerType'");
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;
  if (!tblgen_sym_name) return emitError(loc, "'esi.mem.ram' op requires attribute 'sym_name'");

  if (tblgen_sym_name && !((::llvm::isa<::mlir::StringAttr>(tblgen_sym_name))))
    return emitError(loc, "'esi.mem.ram' op attribute 'sym_name' failed to satisfy constraint: string attribute");

  if (tblgen_innerType && !(((::llvm::isa<::mlir::TypeAttr>(tblgen_innerType))) && ((::llvm::isa<::mlir::Type>(::llvm::cast<::mlir::TypeAttr>(tblgen_innerType).getValue()))) && ((true))))
    return emitError(loc, "'esi.mem.ram' op attribute 'innerType' failed to satisfy constraint: any type attribute");

  if (tblgen_depth && !(((::llvm::isa<::mlir::IntegerAttr>(tblgen_depth))) && ((::llvm::cast<::mlir::IntegerAttr>(tblgen_depth).getType().isSignlessInteger(64)))))
    return emitError(loc, "'esi.mem.ram' op attribute 'depth' failed to satisfy constraint: 64-bit signless integer attribute");
  return ::mlir::success();
}

::llvm::LogicalResult RandomAccessMemoryDeclOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
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
    auto &propStorage = prop.innerType;
       auto attr = dict.get("innerType");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `innerType` in property conversion: " << attr;
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

::mlir::Attribute RandomAccessMemoryDeclOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.depth;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("depth",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.innerType;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("innerType",
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

llvm::hash_code RandomAccessMemoryDeclOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.depth.getAsOpaquePointer()), 
    llvm::hash_value(prop.innerType.getAsOpaquePointer()), 
    llvm::hash_value(prop.sym_name.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> RandomAccessMemoryDeclOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "depth")
      return prop.depth;

    if (name == "innerType")
      return prop.innerType;

    if (name == "sym_name")
      return prop.sym_name;
  return std::nullopt;
}

void RandomAccessMemoryDeclOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "depth") {
       prop.depth = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.depth)>>(value);
       return;
    }

    if (name == "innerType") {
       prop.innerType = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.innerType)>>(value);
       return;
    }

    if (name == "sym_name") {
       prop.sym_name = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.sym_name)>>(value);
       return;
    }
}

void RandomAccessMemoryDeclOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.depth) attrs.append("depth", prop.depth);

    if (prop.innerType) attrs.append("innerType", prop.innerType);

    if (prop.sym_name) attrs.append("sym_name", prop.sym_name);
}

::llvm::LogicalResult RandomAccessMemoryDeclOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getDepthAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_ESI7(attr, "depth", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getInnerTypeAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_ESI6(attr, "innerType", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getSymNameAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_ESI3(attr, "sym_name", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult RandomAccessMemoryDeclOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.depth)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readAttribute(prop.innerType)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readAttribute(prop.sym_name)))
    return ::mlir::failure();
  return ::mlir::success();
}

void RandomAccessMemoryDeclOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.depth);
  writer.writeAttribute(prop.innerType);
  writer.writeAttribute(prop.sym_name);
}

::llvm::StringRef RandomAccessMemoryDeclOp::getSymName() {
  auto attr = getSymNameAttr();
  return attr.getValue();
}

::mlir::Type RandomAccessMemoryDeclOp::getInnerType() {
  auto attr = getInnerTypeAttr();
  return ::llvm::cast<::mlir::Type>(attr.getValue());
}

uint64_t RandomAccessMemoryDeclOp::getDepth() {
  auto attr = getDepthAttr();
  return attr.getValue().getZExtValue();
}

void RandomAccessMemoryDeclOp::setSymName(::llvm::StringRef attrValue) {
  getProperties().sym_name = ::mlir::Builder((*this)->getContext()).getStringAttr(attrValue);
}

void RandomAccessMemoryDeclOp::setInnerType(::mlir::Type attrValue) {
  getProperties().innerType = ::mlir::TypeAttr::get(attrValue);
}

void RandomAccessMemoryDeclOp::setDepth(uint64_t attrValue) {
  getProperties().depth = ::mlir::Builder((*this)->getContext()).getIntegerAttr(::mlir::Builder((*this)->getContext()).getIntegerType(64), attrValue);
}

void RandomAccessMemoryDeclOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::StringAttr sym_name, ::mlir::TypeAttr innerType, ::mlir::IntegerAttr depth) {
  odsState.getOrAddProperties<Properties>().sym_name = sym_name;
  odsState.getOrAddProperties<Properties>().innerType = innerType;
  odsState.getOrAddProperties<Properties>().depth = depth;
}

RandomAccessMemoryDeclOp RandomAccessMemoryDeclOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::StringAttr sym_name, ::mlir::TypeAttr innerType, ::mlir::IntegerAttr depth) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(innerType)>(innerType), std::forward<decltype(depth)>(depth));
  auto __res__ = ::llvm::dyn_cast<RandomAccessMemoryDeclOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

RandomAccessMemoryDeclOp RandomAccessMemoryDeclOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::StringAttr sym_name, ::mlir::TypeAttr innerType, ::mlir::IntegerAttr depth) {
  return create(builder, builder.getLoc(), std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(innerType)>(innerType), std::forward<decltype(depth)>(depth));
}

void RandomAccessMemoryDeclOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name, ::mlir::TypeAttr innerType, ::mlir::IntegerAttr depth) {
  odsState.getOrAddProperties<Properties>().sym_name = sym_name;
  odsState.getOrAddProperties<Properties>().innerType = innerType;
  odsState.getOrAddProperties<Properties>().depth = depth;
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

RandomAccessMemoryDeclOp RandomAccessMemoryDeclOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name, ::mlir::TypeAttr innerType, ::mlir::IntegerAttr depth) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(innerType)>(innerType), std::forward<decltype(depth)>(depth));
  auto __res__ = ::llvm::dyn_cast<RandomAccessMemoryDeclOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

RandomAccessMemoryDeclOp RandomAccessMemoryDeclOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name, ::mlir::TypeAttr innerType, ::mlir::IntegerAttr depth) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(innerType)>(innerType), std::forward<decltype(depth)>(depth));
}

void RandomAccessMemoryDeclOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::llvm::StringRef sym_name, ::mlir::Type innerType, uint64_t depth) {
  odsState.getOrAddProperties<Properties>().sym_name = odsBuilder.getStringAttr(sym_name);
  odsState.getOrAddProperties<Properties>().innerType = ::mlir::TypeAttr::get(innerType);
  odsState.getOrAddProperties<Properties>().depth = odsBuilder.getIntegerAttr(odsBuilder.getIntegerType(64), depth);
}

RandomAccessMemoryDeclOp RandomAccessMemoryDeclOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::llvm::StringRef sym_name, ::mlir::Type innerType, uint64_t depth) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(innerType)>(innerType), std::forward<decltype(depth)>(depth));
  auto __res__ = ::llvm::dyn_cast<RandomAccessMemoryDeclOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

RandomAccessMemoryDeclOp RandomAccessMemoryDeclOp::create(::mlir::ImplicitLocOpBuilder &builder, ::llvm::StringRef sym_name, ::mlir::Type innerType, uint64_t depth) {
  return create(builder, builder.getLoc(), std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(innerType)>(innerType), std::forward<decltype(depth)>(depth));
}

void RandomAccessMemoryDeclOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name, ::mlir::Type innerType, uint64_t depth) {
  odsState.getOrAddProperties<Properties>().sym_name = odsBuilder.getStringAttr(sym_name);
  odsState.getOrAddProperties<Properties>().innerType = ::mlir::TypeAttr::get(innerType);
  odsState.getOrAddProperties<Properties>().depth = odsBuilder.getIntegerAttr(odsBuilder.getIntegerType(64), depth);
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

RandomAccessMemoryDeclOp RandomAccessMemoryDeclOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name, ::mlir::Type innerType, uint64_t depth) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(innerType)>(innerType), std::forward<decltype(depth)>(depth));
  auto __res__ = ::llvm::dyn_cast<RandomAccessMemoryDeclOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

RandomAccessMemoryDeclOp RandomAccessMemoryDeclOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name, ::mlir::Type innerType, uint64_t depth) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(innerType)>(innerType), std::forward<decltype(depth)>(depth));
}

void RandomAccessMemoryDeclOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<RandomAccessMemoryDeclOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

RandomAccessMemoryDeclOp RandomAccessMemoryDeclOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<RandomAccessMemoryDeclOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

RandomAccessMemoryDeclOp RandomAccessMemoryDeclOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void RandomAccessMemoryDeclOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

RandomAccessMemoryDeclOp RandomAccessMemoryDeclOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<RandomAccessMemoryDeclOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

RandomAccessMemoryDeclOp RandomAccessMemoryDeclOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult RandomAccessMemoryDeclOp::verifyInvariantsImpl() {
  auto tblgen_depth = getProperties().depth; (void)tblgen_depth;
  if (!tblgen_depth) return emitOpError("requires attribute 'depth'");
  auto tblgen_innerType = getProperties().innerType; (void)tblgen_innerType;
  if (!tblgen_innerType) return emitOpError("requires attribute 'innerType'");
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;
  if (!tblgen_sym_name) return emitOpError("requires attribute 'sym_name'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_ESI3(*this, tblgen_sym_name, "sym_name")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_ESI6(*this, tblgen_innerType, "innerType")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_ESI7(*this, tblgen_depth, "depth")))
    return ::mlir::failure();
  return ::mlir::success();
}

::llvm::LogicalResult RandomAccessMemoryDeclOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult RandomAccessMemoryDeclOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::StringAttr sym_nameAttr;
  ::mlir::TypeAttr innerTypeAttr;
  ::mlir::IntegerAttr depthAttr;

  if (parser.parseSymbolName(sym_nameAttr))
    return ::mlir::failure();
  if (sym_nameAttr) result.getOrAddProperties<RandomAccessMemoryDeclOp::Properties>().sym_name = sym_nameAttr;

  if (parser.parseCustomAttributeWithFallback(innerTypeAttr, parser.getBuilder().getType<::mlir::NoneType>())) {
    return ::mlir::failure();
  }
  if (innerTypeAttr) result.getOrAddProperties<RandomAccessMemoryDeclOp::Properties>().innerType = innerTypeAttr;
  if (parser.parseKeyword("x"))
    return ::mlir::failure();

  if (parser.parseCustomAttributeWithFallback(depthAttr, parser.getBuilder().getIntegerType(64))) {
    return ::mlir::failure();
  }
  if (depthAttr) result.getOrAddProperties<RandomAccessMemoryDeclOp::Properties>().depth = depthAttr;
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

void RandomAccessMemoryDeclOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter.printSymbolName(getSymNameAttr().getValue());
  _odsPrinter << ' ';
  _odsPrinter.printAttributeWithoutType(getInnerTypeAttr());
  _odsPrinter << ' ' << "x";
  _odsPrinter << ' ';
  _odsPrinter.printAttributeWithoutType(getDepthAttr());
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("sym_name");
  elidedAttrs.push_back("innerType");
  elidedAttrs.push_back("depth");
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
}


} // namespace circt::esi
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::esi::RandomAccessMemoryDeclOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::esi::detail::RandomAccessMemoryDeclOpGenericAdaptorBase::Properties)

namespace circt::esi {


//===----------------------------------------------------------------------===//
// ::circt::esi::RequestConnectionOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

RequestConnectionOpGenericAdaptorBase::RequestConnectionOpGenericAdaptorBase(RequestConnectionOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::circt::hw::InnerRefAttr RequestConnectionOpGenericAdaptorBase::getServicePort() {
  auto attr = getServicePortAttr();
  return ::llvm::cast<::circt::hw::InnerRefAttr>(attr);
}

::circt::esi::AppIDAttr RequestConnectionOpGenericAdaptorBase::getAppID() {
  auto attr = getAppIDAttr();
  return ::llvm::cast<::circt::esi::AppIDAttr>(attr);
}


} // namespace detail
RequestConnectionOpAdaptor::RequestConnectionOpAdaptor(RequestConnectionOp op) : RequestConnectionOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult RequestConnectionOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_appID = getProperties().appID; (void)tblgen_appID;
  if (!tblgen_appID) return emitError(loc, "'esi.service.req' op requires attribute 'appID'");
  auto tblgen_servicePort = getProperties().servicePort; (void)tblgen_servicePort;
  if (!tblgen_servicePort) return emitError(loc, "'esi.service.req' op requires attribute 'servicePort'");

  if (tblgen_servicePort && !((::llvm::isa<::circt::hw::InnerRefAttr>(tblgen_servicePort))))
    return emitError(loc, "'esi.service.req' op attribute 'servicePort' failed to satisfy constraint: Refer to a name inside a module");

  if (tblgen_appID && !((::llvm::isa<::circt::esi::AppIDAttr>(tblgen_appID))))
    return emitError(loc, "'esi.service.req' op attribute 'appID' failed to satisfy constraint: An application relevant instance identifier");
  return ::mlir::success();
}

::llvm::LogicalResult RequestConnectionOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.appID;
       auto attr = dict.get("appID");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `appID` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.servicePort;
       auto attr = dict.get("servicePort");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `servicePort` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  return ::mlir::success();
}

::mlir::Attribute RequestConnectionOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.appID;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("appID",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.servicePort;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("servicePort",
                                       propStorage));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code RequestConnectionOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.appID.getAsOpaquePointer()), 
    llvm::hash_value(prop.servicePort.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> RequestConnectionOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "appID")
      return prop.appID;

    if (name == "servicePort")
      return prop.servicePort;
  return std::nullopt;
}

void RequestConnectionOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "appID") {
       prop.appID = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.appID)>>(value);
       return;
    }

    if (name == "servicePort") {
       prop.servicePort = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.servicePort)>>(value);
       return;
    }
}

void RequestConnectionOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.appID) attrs.append("appID", prop.appID);

    if (prop.servicePort) attrs.append("servicePort", prop.servicePort);
}

::llvm::LogicalResult RequestConnectionOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getAppIDAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_ESI1(attr, "appID", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getServicePortAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_ESI8(attr, "servicePort", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult RequestConnectionOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.appID)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readAttribute(prop.servicePort)))
    return ::mlir::failure();
  return ::mlir::success();
}

void RequestConnectionOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.appID);
  writer.writeAttribute(prop.servicePort);
}

::circt::hw::InnerRefAttr RequestConnectionOp::getServicePort() {
  auto attr = getServicePortAttr();
  return ::llvm::cast<::circt::hw::InnerRefAttr>(attr);
}

::circt::esi::AppIDAttr RequestConnectionOp::getAppID() {
  auto attr = getAppIDAttr();
  return ::llvm::cast<::circt::esi::AppIDAttr>(attr);
}

void RequestConnectionOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type toClient, ::circt::hw::InnerRefAttr servicePort, ::circt::esi::AppIDAttr appID) {
  odsState.getOrAddProperties<Properties>().servicePort = servicePort;
  odsState.getOrAddProperties<Properties>().appID = appID;
  odsState.addTypes(toClient);
}

RequestConnectionOp RequestConnectionOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type toClient, ::circt::hw::InnerRefAttr servicePort, ::circt::esi::AppIDAttr appID) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(toClient)>(toClient), std::forward<decltype(servicePort)>(servicePort), std::forward<decltype(appID)>(appID));
  auto __res__ = ::llvm::dyn_cast<RequestConnectionOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

RequestConnectionOp RequestConnectionOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type toClient, ::circt::hw::InnerRefAttr servicePort, ::circt::esi::AppIDAttr appID) {
  return create(builder, builder.getLoc(), std::forward<decltype(toClient)>(toClient), std::forward<decltype(servicePort)>(servicePort), std::forward<decltype(appID)>(appID));
}

void RequestConnectionOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::circt::hw::InnerRefAttr servicePort, ::circt::esi::AppIDAttr appID) {
  odsState.getOrAddProperties<Properties>().servicePort = servicePort;
  odsState.getOrAddProperties<Properties>().appID = appID;
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

RequestConnectionOp RequestConnectionOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::circt::hw::InnerRefAttr servicePort, ::circt::esi::AppIDAttr appID) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(servicePort)>(servicePort), std::forward<decltype(appID)>(appID));
  auto __res__ = ::llvm::dyn_cast<RequestConnectionOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

RequestConnectionOp RequestConnectionOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::circt::hw::InnerRefAttr servicePort, ::circt::esi::AppIDAttr appID) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(servicePort)>(servicePort), std::forward<decltype(appID)>(appID));
}

void RequestConnectionOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<RequestConnectionOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

RequestConnectionOp RequestConnectionOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<RequestConnectionOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

RequestConnectionOp RequestConnectionOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void RequestConnectionOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

RequestConnectionOp RequestConnectionOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<RequestConnectionOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

RequestConnectionOp RequestConnectionOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult RequestConnectionOp::verifyInvariantsImpl() {
  auto tblgen_appID = getProperties().appID; (void)tblgen_appID;
  if (!tblgen_appID) return emitOpError("requires attribute 'appID'");
  auto tblgen_servicePort = getProperties().servicePort; (void)tblgen_servicePort;
  if (!tblgen_servicePort) return emitOpError("requires attribute 'servicePort'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_ESI8(*this, tblgen_servicePort, "servicePort")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_ESI1(*this, tblgen_appID, "appID")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_ESI6(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult RequestConnectionOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult RequestConnectionOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::circt::hw::InnerRefAttr servicePortAttr;
  ::circt::esi::AppIDAttr appIDAttr;
  ::mlir::Type toClientRawType{};
  ::llvm::ArrayRef<::mlir::Type> toClientTypes(&toClientRawType, 1);

  if (parser.parseCustomAttributeWithFallback(servicePortAttr, ::mlir::Type{})) {
    return ::mlir::failure();
  }
  if (servicePortAttr) result.getOrAddProperties<RequestConnectionOp::Properties>().servicePort = servicePortAttr;
  if (parser.parseLParen())
    return ::mlir::failure();

  if (parser.parseAttribute(appIDAttr, ::mlir::Type{}))
    return ::mlir::failure();
  if (appIDAttr) result.getOrAddProperties<RequestConnectionOp::Properties>().appID = appIDAttr;
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

  if (parser.parseType(toClientRawType))
    return ::mlir::failure();
  result.addTypes(toClientTypes);
  return ::mlir::success();
}

void RequestConnectionOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
_odsPrinter.printStrippedAttrOrType(getServicePortAttr());
  _odsPrinter << "(";
  _odsPrinter.printAttribute(getAppIDAttr());
  _odsPrinter << ")";
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("servicePort");
  elidedAttrs.push_back("appID");
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
   _odsPrinter << getToClient().getType();
}


} // namespace circt::esi
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::esi::RequestConnectionOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::esi::detail::RequestConnectionOpGenericAdaptorBase::Properties)

namespace circt::esi {


//===----------------------------------------------------------------------===//
// ::circt::esi::ServiceDeclPortOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

ServiceDeclPortOpGenericAdaptorBase::ServiceDeclPortOpGenericAdaptorBase(ServiceDeclPortOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::llvm::StringRef ServiceDeclPortOpGenericAdaptorBase::getInnerSym() {
  auto attr = getInnerSymAttr();
  return attr.getValue();
}

::circt::esi::ChannelBundleType ServiceDeclPortOpGenericAdaptorBase::getToClientType() {
  auto attr = getToClientTypeAttr();
  return ::llvm::cast<::circt::esi::ChannelBundleType>(attr.getValue());
}


} // namespace detail
ServiceDeclPortOpAdaptor::ServiceDeclPortOpAdaptor(ServiceDeclPortOp op) : ServiceDeclPortOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult ServiceDeclPortOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_inner_sym = getProperties().inner_sym; (void)tblgen_inner_sym;
  if (!tblgen_inner_sym) return emitError(loc, "'esi.service.port' op requires attribute 'inner_sym'");
  auto tblgen_toClientType = getProperties().toClientType; (void)tblgen_toClientType;
  if (!tblgen_toClientType) return emitError(loc, "'esi.service.port' op requires attribute 'toClientType'");

  if (tblgen_inner_sym && !((::llvm::isa<::mlir::StringAttr>(tblgen_inner_sym))))
    return emitError(loc, "'esi.service.port' op attribute 'inner_sym' failed to satisfy constraint: string attribute");

  if (tblgen_toClientType && !(((::llvm::isa<::mlir::TypeAttr>(tblgen_toClientType))) && ((::llvm::isa<::circt::esi::ChannelBundleType>(::llvm::cast<::mlir::TypeAttr>(tblgen_toClientType).getValue()))) && ((::llvm::isa<::circt::esi::ChannelBundleType>(::llvm::cast<::mlir::TypeAttr>(tblgen_toClientType).getValue())))))
    return emitError(loc, "'esi.service.port' op attribute 'toClientType' failed to satisfy constraint: type attribute of a bundle of channels");
  return ::mlir::success();
}

::llvm::LogicalResult ServiceDeclPortOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
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
    auto &propStorage = prop.toClientType;
       auto attr = dict.get("toClientType");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `toClientType` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  return ::mlir::success();
}

::mlir::Attribute ServiceDeclPortOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.inner_sym;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("inner_sym",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.toClientType;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("toClientType",
                                       propStorage));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code ServiceDeclPortOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.inner_sym.getAsOpaquePointer()), 
    llvm::hash_value(prop.toClientType.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> ServiceDeclPortOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "inner_sym")
      return prop.inner_sym;

    if (name == "toClientType")
      return prop.toClientType;
  return std::nullopt;
}

void ServiceDeclPortOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "inner_sym") {
       prop.inner_sym = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.inner_sym)>>(value);
       return;
    }

    if (name == "toClientType") {
       prop.toClientType = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.toClientType)>>(value);
       return;
    }
}

void ServiceDeclPortOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.inner_sym) attrs.append("inner_sym", prop.inner_sym);

    if (prop.toClientType) attrs.append("toClientType", prop.toClientType);
}

::llvm::LogicalResult ServiceDeclPortOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getInnerSymAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_ESI3(attr, "inner_sym", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getToClientTypeAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_ESI9(attr, "toClientType", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult ServiceDeclPortOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.inner_sym)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readAttribute(prop.toClientType)))
    return ::mlir::failure();
  return ::mlir::success();
}

void ServiceDeclPortOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.inner_sym);
  writer.writeAttribute(prop.toClientType);
}

::llvm::StringRef ServiceDeclPortOp::getInnerSym() {
  auto attr = getInnerSymAttr();
  return attr.getValue();
}

::circt::esi::ChannelBundleType ServiceDeclPortOp::getToClientType() {
  auto attr = getToClientTypeAttr();
  return ::llvm::cast<::circt::esi::ChannelBundleType>(attr.getValue());
}

void ServiceDeclPortOp::setInnerSym(::llvm::StringRef attrValue) {
  getProperties().inner_sym = ::mlir::Builder((*this)->getContext()).getStringAttr(attrValue);
}

void ServiceDeclPortOp::setToClientType(::circt::esi::ChannelBundleType attrValue) {
  getProperties().toClientType = ::mlir::TypeAttr::get(attrValue);
}

void ServiceDeclPortOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::StringAttr inner_sym, ::mlir::TypeAttr toClientType) {
  odsState.getOrAddProperties<Properties>().inner_sym = inner_sym;
  odsState.getOrAddProperties<Properties>().toClientType = toClientType;
}

ServiceDeclPortOp ServiceDeclPortOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::StringAttr inner_sym, ::mlir::TypeAttr toClientType) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(inner_sym)>(inner_sym), std::forward<decltype(toClientType)>(toClientType));
  auto __res__ = ::llvm::dyn_cast<ServiceDeclPortOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ServiceDeclPortOp ServiceDeclPortOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::StringAttr inner_sym, ::mlir::TypeAttr toClientType) {
  return create(builder, builder.getLoc(), std::forward<decltype(inner_sym)>(inner_sym), std::forward<decltype(toClientType)>(toClientType));
}

void ServiceDeclPortOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::StringAttr inner_sym, ::mlir::TypeAttr toClientType) {
  odsState.getOrAddProperties<Properties>().inner_sym = inner_sym;
  odsState.getOrAddProperties<Properties>().toClientType = toClientType;
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

ServiceDeclPortOp ServiceDeclPortOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::StringAttr inner_sym, ::mlir::TypeAttr toClientType) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(inner_sym)>(inner_sym), std::forward<decltype(toClientType)>(toClientType));
  auto __res__ = ::llvm::dyn_cast<ServiceDeclPortOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ServiceDeclPortOp ServiceDeclPortOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::StringAttr inner_sym, ::mlir::TypeAttr toClientType) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(inner_sym)>(inner_sym), std::forward<decltype(toClientType)>(toClientType));
}

void ServiceDeclPortOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::llvm::StringRef inner_sym, ::circt::esi::ChannelBundleType toClientType) {
  odsState.getOrAddProperties<Properties>().inner_sym = odsBuilder.getStringAttr(inner_sym);
  odsState.getOrAddProperties<Properties>().toClientType = ::mlir::TypeAttr::get(toClientType);
}

ServiceDeclPortOp ServiceDeclPortOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::llvm::StringRef inner_sym, ::circt::esi::ChannelBundleType toClientType) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(inner_sym)>(inner_sym), std::forward<decltype(toClientType)>(toClientType));
  auto __res__ = ::llvm::dyn_cast<ServiceDeclPortOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ServiceDeclPortOp ServiceDeclPortOp::create(::mlir::ImplicitLocOpBuilder &builder, ::llvm::StringRef inner_sym, ::circt::esi::ChannelBundleType toClientType) {
  return create(builder, builder.getLoc(), std::forward<decltype(inner_sym)>(inner_sym), std::forward<decltype(toClientType)>(toClientType));
}

void ServiceDeclPortOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::llvm::StringRef inner_sym, ::circt::esi::ChannelBundleType toClientType) {
  odsState.getOrAddProperties<Properties>().inner_sym = odsBuilder.getStringAttr(inner_sym);
  odsState.getOrAddProperties<Properties>().toClientType = ::mlir::TypeAttr::get(toClientType);
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

ServiceDeclPortOp ServiceDeclPortOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::llvm::StringRef inner_sym, ::circt::esi::ChannelBundleType toClientType) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(inner_sym)>(inner_sym), std::forward<decltype(toClientType)>(toClientType));
  auto __res__ = ::llvm::dyn_cast<ServiceDeclPortOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ServiceDeclPortOp ServiceDeclPortOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::llvm::StringRef inner_sym, ::circt::esi::ChannelBundleType toClientType) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(inner_sym)>(inner_sym), std::forward<decltype(toClientType)>(toClientType));
}

void ServiceDeclPortOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<ServiceDeclPortOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

ServiceDeclPortOp ServiceDeclPortOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<ServiceDeclPortOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ServiceDeclPortOp ServiceDeclPortOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void ServiceDeclPortOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

ServiceDeclPortOp ServiceDeclPortOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<ServiceDeclPortOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ServiceDeclPortOp ServiceDeclPortOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult ServiceDeclPortOp::verifyInvariantsImpl() {
  auto tblgen_inner_sym = getProperties().inner_sym; (void)tblgen_inner_sym;
  if (!tblgen_inner_sym) return emitOpError("requires attribute 'inner_sym'");
  auto tblgen_toClientType = getProperties().toClientType; (void)tblgen_toClientType;
  if (!tblgen_toClientType) return emitOpError("requires attribute 'toClientType'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_ESI3(*this, tblgen_inner_sym, "inner_sym")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_ESI9(*this, tblgen_toClientType, "toClientType")))
    return ::mlir::failure();
  return ::mlir::success();
}

::llvm::LogicalResult ServiceDeclPortOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult ServiceDeclPortOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::StringAttr inner_symAttr;
  ::mlir::TypeAttr toClientTypeAttr;

  if (parser.parseSymbolName(inner_symAttr))
    return ::mlir::failure();
  if (inner_symAttr) result.getOrAddProperties<ServiceDeclPortOp::Properties>().inner_sym = inner_symAttr;
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

  if (parser.parseCustomAttributeWithFallback(toClientTypeAttr, parser.getBuilder().getType<::mlir::NoneType>())) {
    return ::mlir::failure();
  }
  if (toClientTypeAttr) result.getOrAddProperties<ServiceDeclPortOp::Properties>().toClientType = toClientTypeAttr;
  return ::mlir::success();
}

void ServiceDeclPortOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter.printSymbolName(getInnerSymAttr().getValue());
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("inner_sym");
  elidedAttrs.push_back("toClientType");
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
  _odsPrinter.printAttributeWithoutType(getToClientTypeAttr());
}


} // namespace circt::esi
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::esi::ServiceDeclPortOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::esi::detail::ServiceDeclPortOpGenericAdaptorBase::Properties)

namespace circt::esi {


//===----------------------------------------------------------------------===//
// ::circt::esi::ServiceImplClientRecordOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

ServiceImplClientRecordOpGenericAdaptorBase::ServiceImplClientRecordOpGenericAdaptorBase(ServiceImplClientRecordOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::mlir::ArrayAttr ServiceImplClientRecordOpGenericAdaptorBase::getRelAppIDPath() {
  auto attr = getRelAppIDPathAttr();
  return attr;
}

::circt::hw::InnerRefAttr ServiceImplClientRecordOpGenericAdaptorBase::getServicePort() {
  auto attr = getServicePortAttr();
  return ::llvm::cast<::circt::hw::InnerRefAttr>(attr);
}

::circt::esi::ChannelBundleType ServiceImplClientRecordOpGenericAdaptorBase::getTypeID() {
  auto attr = getTypeIDAttr();
  return ::llvm::cast<::circt::esi::ChannelBundleType>(attr.getValue());
}

::std::optional< ::mlir::DictionaryAttr > ServiceImplClientRecordOpGenericAdaptorBase::getChannelAssignments() {
  auto attr = getChannelAssignmentsAttr();
  return attr ? ::std::optional< ::mlir::DictionaryAttr >(attr) : (::std::nullopt);
}

::std::optional< ::mlir::DictionaryAttr > ServiceImplClientRecordOpGenericAdaptorBase::getImplDetails() {
  auto attr = getImplDetailsAttr();
  return attr ? ::std::optional< ::mlir::DictionaryAttr >(attr) : (::std::nullopt);
}


} // namespace detail
ServiceImplClientRecordOpAdaptor::ServiceImplClientRecordOpAdaptor(ServiceImplClientRecordOp op) : ServiceImplClientRecordOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult ServiceImplClientRecordOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_channelAssignments = getProperties().channelAssignments; (void)tblgen_channelAssignments;
  auto tblgen_implDetails = getProperties().implDetails; (void)tblgen_implDetails;
  auto tblgen_relAppIDPath = getProperties().relAppIDPath; (void)tblgen_relAppIDPath;
  if (!tblgen_relAppIDPath) return emitError(loc, "'esi.manifest.impl_conn' op requires attribute 'relAppIDPath'");
  auto tblgen_servicePort = getProperties().servicePort; (void)tblgen_servicePort;
  if (!tblgen_servicePort) return emitError(loc, "'esi.manifest.impl_conn' op requires attribute 'servicePort'");
  auto tblgen_typeID = getProperties().typeID; (void)tblgen_typeID;
  if (!tblgen_typeID) return emitError(loc, "'esi.manifest.impl_conn' op requires attribute 'typeID'");

  if (tblgen_relAppIDPath && !(((::llvm::isa<::mlir::ArrayAttr>(tblgen_relAppIDPath))) && (::llvm::all_of(::llvm::cast<::mlir::ArrayAttr>(tblgen_relAppIDPath), [&](::mlir::Attribute attr) { return attr && ((::llvm::isa<::circt::esi::AppIDAttr>(attr))); }))))
    return emitError(loc, "'esi.manifest.impl_conn' op attribute 'relAppIDPath' failed to satisfy constraint: Array of AppIDs");

  if (tblgen_servicePort && !((::llvm::isa<::circt::hw::InnerRefAttr>(tblgen_servicePort))))
    return emitError(loc, "'esi.manifest.impl_conn' op attribute 'servicePort' failed to satisfy constraint: Refer to a name inside a module");

  if (tblgen_typeID && !(((::llvm::isa<::mlir::TypeAttr>(tblgen_typeID))) && ((::llvm::isa<::circt::esi::ChannelBundleType>(::llvm::cast<::mlir::TypeAttr>(tblgen_typeID).getValue()))) && ((::llvm::isa<::circt::esi::ChannelBundleType>(::llvm::cast<::mlir::TypeAttr>(tblgen_typeID).getValue())))))
    return emitError(loc, "'esi.manifest.impl_conn' op attribute 'typeID' failed to satisfy constraint: type attribute of a bundle of channels");

  if (tblgen_channelAssignments && !((::llvm::isa<::mlir::DictionaryAttr>(tblgen_channelAssignments))))
    return emitError(loc, "'esi.manifest.impl_conn' op attribute 'channelAssignments' failed to satisfy constraint: dictionary of named attribute values");

  if (tblgen_implDetails && !((::llvm::isa<::mlir::DictionaryAttr>(tblgen_implDetails))))
    return emitError(loc, "'esi.manifest.impl_conn' op attribute 'implDetails' failed to satisfy constraint: dictionary of named attribute values");
  return ::mlir::success();
}

::llvm::LogicalResult ServiceImplClientRecordOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.channelAssignments;
       auto attr = dict.get("channelAssignments");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `channelAssignments` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.implDetails;
       auto attr = dict.get("implDetails");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `implDetails` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.relAppIDPath;
       auto attr = dict.get("relAppIDPath");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `relAppIDPath` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.servicePort;
       auto attr = dict.get("servicePort");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `servicePort` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.typeID;
       auto attr = dict.get("typeID");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `typeID` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  return ::mlir::success();
}

::mlir::Attribute ServiceImplClientRecordOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.channelAssignments;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("channelAssignments",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.implDetails;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("implDetails",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.relAppIDPath;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("relAppIDPath",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.servicePort;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("servicePort",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.typeID;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("typeID",
                                       propStorage));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code ServiceImplClientRecordOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.channelAssignments.getAsOpaquePointer()), 
    llvm::hash_value(prop.implDetails.getAsOpaquePointer()), 
    llvm::hash_value(prop.relAppIDPath.getAsOpaquePointer()), 
    llvm::hash_value(prop.servicePort.getAsOpaquePointer()), 
    llvm::hash_value(prop.typeID.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> ServiceImplClientRecordOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "channelAssignments")
      return prop.channelAssignments;

    if (name == "implDetails")
      return prop.implDetails;

    if (name == "relAppIDPath")
      return prop.relAppIDPath;

    if (name == "servicePort")
      return prop.servicePort;

    if (name == "typeID")
      return prop.typeID;
  return std::nullopt;
}

void ServiceImplClientRecordOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "channelAssignments") {
       prop.channelAssignments = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.channelAssignments)>>(value);
       return;
    }

    if (name == "implDetails") {
       prop.implDetails = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.implDetails)>>(value);
       return;
    }

    if (name == "relAppIDPath") {
       prop.relAppIDPath = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.relAppIDPath)>>(value);
       return;
    }

    if (name == "servicePort") {
       prop.servicePort = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.servicePort)>>(value);
       return;
    }

    if (name == "typeID") {
       prop.typeID = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.typeID)>>(value);
       return;
    }
}

void ServiceImplClientRecordOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.channelAssignments) attrs.append("channelAssignments", prop.channelAssignments);

    if (prop.implDetails) attrs.append("implDetails", prop.implDetails);

    if (prop.relAppIDPath) attrs.append("relAppIDPath", prop.relAppIDPath);

    if (prop.servicePort) attrs.append("servicePort", prop.servicePort);

    if (prop.typeID) attrs.append("typeID", prop.typeID);
}

::llvm::LogicalResult ServiceImplClientRecordOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getChannelAssignmentsAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_ESI11(attr, "channelAssignments", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getImplDetailsAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_ESI11(attr, "implDetails", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getRelAppIDPathAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_ESI10(attr, "relAppIDPath", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getServicePortAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_ESI8(attr, "servicePort", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getTypeIDAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_ESI9(attr, "typeID", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult ServiceImplClientRecordOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readOptionalAttribute(prop.channelAssignments)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readOptionalAttribute(prop.implDetails)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readAttribute(prop.relAppIDPath)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readAttribute(prop.servicePort)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readAttribute(prop.typeID)))
    return ::mlir::failure();
  return ::mlir::success();
}

void ServiceImplClientRecordOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;

  writer.writeOptionalAttribute(prop.channelAssignments);

  writer.writeOptionalAttribute(prop.implDetails);
  writer.writeAttribute(prop.relAppIDPath);
  writer.writeAttribute(prop.servicePort);
  writer.writeAttribute(prop.typeID);
}

::mlir::ArrayAttr ServiceImplClientRecordOp::getRelAppIDPath() {
  auto attr = getRelAppIDPathAttr();
  return attr;
}

::circt::hw::InnerRefAttr ServiceImplClientRecordOp::getServicePort() {
  auto attr = getServicePortAttr();
  return ::llvm::cast<::circt::hw::InnerRefAttr>(attr);
}

::circt::esi::ChannelBundleType ServiceImplClientRecordOp::getTypeID() {
  auto attr = getTypeIDAttr();
  return ::llvm::cast<::circt::esi::ChannelBundleType>(attr.getValue());
}

::std::optional< ::mlir::DictionaryAttr > ServiceImplClientRecordOp::getChannelAssignments() {
  auto attr = getChannelAssignmentsAttr();
  return attr ? ::std::optional< ::mlir::DictionaryAttr >(attr) : (::std::nullopt);
}

::std::optional< ::mlir::DictionaryAttr > ServiceImplClientRecordOp::getImplDetails() {
  auto attr = getImplDetailsAttr();
  return attr ? ::std::optional< ::mlir::DictionaryAttr >(attr) : (::std::nullopt);
}

void ServiceImplClientRecordOp::setTypeID(::circt::esi::ChannelBundleType attrValue) {
  getProperties().typeID = ::mlir::TypeAttr::get(attrValue);
}

void ServiceImplClientRecordOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ArrayAttr relAppIDPath, ::circt::hw::InnerRefAttr servicePort, ::mlir::TypeAttr typeID, /*optional*/::mlir::DictionaryAttr channelAssignments, /*optional*/::mlir::DictionaryAttr implDetails) {
  odsState.getOrAddProperties<Properties>().relAppIDPath = relAppIDPath;
  odsState.getOrAddProperties<Properties>().servicePort = servicePort;
  odsState.getOrAddProperties<Properties>().typeID = typeID;
  if (channelAssignments) {
    odsState.getOrAddProperties<Properties>().channelAssignments = channelAssignments;
  }
  if (implDetails) {
    odsState.getOrAddProperties<Properties>().implDetails = implDetails;
  }
}

ServiceImplClientRecordOp ServiceImplClientRecordOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ArrayAttr relAppIDPath, ::circt::hw::InnerRefAttr servicePort, ::mlir::TypeAttr typeID, /*optional*/::mlir::DictionaryAttr channelAssignments, /*optional*/::mlir::DictionaryAttr implDetails) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(relAppIDPath)>(relAppIDPath), std::forward<decltype(servicePort)>(servicePort), std::forward<decltype(typeID)>(typeID), std::forward<decltype(channelAssignments)>(channelAssignments), std::forward<decltype(implDetails)>(implDetails));
  auto __res__ = ::llvm::dyn_cast<ServiceImplClientRecordOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ServiceImplClientRecordOp ServiceImplClientRecordOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ArrayAttr relAppIDPath, ::circt::hw::InnerRefAttr servicePort, ::mlir::TypeAttr typeID, /*optional*/::mlir::DictionaryAttr channelAssignments, /*optional*/::mlir::DictionaryAttr implDetails) {
  return create(builder, builder.getLoc(), std::forward<decltype(relAppIDPath)>(relAppIDPath), std::forward<decltype(servicePort)>(servicePort), std::forward<decltype(typeID)>(typeID), std::forward<decltype(channelAssignments)>(channelAssignments), std::forward<decltype(implDetails)>(implDetails));
}

void ServiceImplClientRecordOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ArrayAttr relAppIDPath, ::circt::hw::InnerRefAttr servicePort, ::mlir::TypeAttr typeID, /*optional*/::mlir::DictionaryAttr channelAssignments, /*optional*/::mlir::DictionaryAttr implDetails) {
  odsState.getOrAddProperties<Properties>().relAppIDPath = relAppIDPath;
  odsState.getOrAddProperties<Properties>().servicePort = servicePort;
  odsState.getOrAddProperties<Properties>().typeID = typeID;
  if (channelAssignments) {
    odsState.getOrAddProperties<Properties>().channelAssignments = channelAssignments;
  }
  if (implDetails) {
    odsState.getOrAddProperties<Properties>().implDetails = implDetails;
  }
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

ServiceImplClientRecordOp ServiceImplClientRecordOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ArrayAttr relAppIDPath, ::circt::hw::InnerRefAttr servicePort, ::mlir::TypeAttr typeID, /*optional*/::mlir::DictionaryAttr channelAssignments, /*optional*/::mlir::DictionaryAttr implDetails) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(relAppIDPath)>(relAppIDPath), std::forward<decltype(servicePort)>(servicePort), std::forward<decltype(typeID)>(typeID), std::forward<decltype(channelAssignments)>(channelAssignments), std::forward<decltype(implDetails)>(implDetails));
  auto __res__ = ::llvm::dyn_cast<ServiceImplClientRecordOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ServiceImplClientRecordOp ServiceImplClientRecordOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ArrayAttr relAppIDPath, ::circt::hw::InnerRefAttr servicePort, ::mlir::TypeAttr typeID, /*optional*/::mlir::DictionaryAttr channelAssignments, /*optional*/::mlir::DictionaryAttr implDetails) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(relAppIDPath)>(relAppIDPath), std::forward<decltype(servicePort)>(servicePort), std::forward<decltype(typeID)>(typeID), std::forward<decltype(channelAssignments)>(channelAssignments), std::forward<decltype(implDetails)>(implDetails));
}

void ServiceImplClientRecordOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ArrayAttr relAppIDPath, ::circt::hw::InnerRefAttr servicePort, ::circt::esi::ChannelBundleType typeID, /*optional*/::mlir::DictionaryAttr channelAssignments, /*optional*/::mlir::DictionaryAttr implDetails) {
  odsState.getOrAddProperties<Properties>().relAppIDPath = relAppIDPath;
  odsState.getOrAddProperties<Properties>().servicePort = servicePort;
  odsState.getOrAddProperties<Properties>().typeID = ::mlir::TypeAttr::get(typeID);
  if (channelAssignments) {
    odsState.getOrAddProperties<Properties>().channelAssignments = channelAssignments;
  }
  if (implDetails) {
    odsState.getOrAddProperties<Properties>().implDetails = implDetails;
  }
}

ServiceImplClientRecordOp ServiceImplClientRecordOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ArrayAttr relAppIDPath, ::circt::hw::InnerRefAttr servicePort, ::circt::esi::ChannelBundleType typeID, /*optional*/::mlir::DictionaryAttr channelAssignments, /*optional*/::mlir::DictionaryAttr implDetails) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(relAppIDPath)>(relAppIDPath), std::forward<decltype(servicePort)>(servicePort), std::forward<decltype(typeID)>(typeID), std::forward<decltype(channelAssignments)>(channelAssignments), std::forward<decltype(implDetails)>(implDetails));
  auto __res__ = ::llvm::dyn_cast<ServiceImplClientRecordOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ServiceImplClientRecordOp ServiceImplClientRecordOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ArrayAttr relAppIDPath, ::circt::hw::InnerRefAttr servicePort, ::circt::esi::ChannelBundleType typeID, /*optional*/::mlir::DictionaryAttr channelAssignments, /*optional*/::mlir::DictionaryAttr implDetails) {
  return create(builder, builder.getLoc(), std::forward<decltype(relAppIDPath)>(relAppIDPath), std::forward<decltype(servicePort)>(servicePort), std::forward<decltype(typeID)>(typeID), std::forward<decltype(channelAssignments)>(channelAssignments), std::forward<decltype(implDetails)>(implDetails));
}

void ServiceImplClientRecordOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ArrayAttr relAppIDPath, ::circt::hw::InnerRefAttr servicePort, ::circt::esi::ChannelBundleType typeID, /*optional*/::mlir::DictionaryAttr channelAssignments, /*optional*/::mlir::DictionaryAttr implDetails) {
  odsState.getOrAddProperties<Properties>().relAppIDPath = relAppIDPath;
  odsState.getOrAddProperties<Properties>().servicePort = servicePort;
  odsState.getOrAddProperties<Properties>().typeID = ::mlir::TypeAttr::get(typeID);
  if (channelAssignments) {
    odsState.getOrAddProperties<Properties>().channelAssignments = channelAssignments;
  }
  if (implDetails) {
    odsState.getOrAddProperties<Properties>().implDetails = implDetails;
  }
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

ServiceImplClientRecordOp ServiceImplClientRecordOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ArrayAttr relAppIDPath, ::circt::hw::InnerRefAttr servicePort, ::circt::esi::ChannelBundleType typeID, /*optional*/::mlir::DictionaryAttr channelAssignments, /*optional*/::mlir::DictionaryAttr implDetails) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(relAppIDPath)>(relAppIDPath), std::forward<decltype(servicePort)>(servicePort), std::forward<decltype(typeID)>(typeID), std::forward<decltype(channelAssignments)>(channelAssignments), std::forward<decltype(implDetails)>(implDetails));
  auto __res__ = ::llvm::dyn_cast<ServiceImplClientRecordOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ServiceImplClientRecordOp ServiceImplClientRecordOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ArrayAttr relAppIDPath, ::circt::hw::InnerRefAttr servicePort, ::circt::esi::ChannelBundleType typeID, /*optional*/::mlir::DictionaryAttr channelAssignments, /*optional*/::mlir::DictionaryAttr implDetails) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(relAppIDPath)>(relAppIDPath), std::forward<decltype(servicePort)>(servicePort), std::forward<decltype(typeID)>(typeID), std::forward<decltype(channelAssignments)>(channelAssignments), std::forward<decltype(implDetails)>(implDetails));
}

void ServiceImplClientRecordOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<ServiceImplClientRecordOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

ServiceImplClientRecordOp ServiceImplClientRecordOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<ServiceImplClientRecordOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ServiceImplClientRecordOp ServiceImplClientRecordOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void ServiceImplClientRecordOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

ServiceImplClientRecordOp ServiceImplClientRecordOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<ServiceImplClientRecordOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ServiceImplClientRecordOp ServiceImplClientRecordOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult ServiceImplClientRecordOp::verifyInvariantsImpl() {
  auto tblgen_channelAssignments = getProperties().channelAssignments; (void)tblgen_channelAssignments;
  auto tblgen_implDetails = getProperties().implDetails; (void)tblgen_implDetails;
  auto tblgen_relAppIDPath = getProperties().relAppIDPath; (void)tblgen_relAppIDPath;
  if (!tblgen_relAppIDPath) return emitOpError("requires attribute 'relAppIDPath'");
  auto tblgen_servicePort = getProperties().servicePort; (void)tblgen_servicePort;
  if (!tblgen_servicePort) return emitOpError("requires attribute 'servicePort'");
  auto tblgen_typeID = getProperties().typeID; (void)tblgen_typeID;
  if (!tblgen_typeID) return emitOpError("requires attribute 'typeID'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_ESI10(*this, tblgen_relAppIDPath, "relAppIDPath")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_ESI8(*this, tblgen_servicePort, "servicePort")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_ESI9(*this, tblgen_typeID, "typeID")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_ESI11(*this, tblgen_channelAssignments, "channelAssignments")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_ESI11(*this, tblgen_implDetails, "implDetails")))
    return ::mlir::failure();
  return ::mlir::success();
}

::llvm::LogicalResult ServiceImplClientRecordOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult ServiceImplClientRecordOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::ArrayAttr relAppIDPathAttr;
  ::circt::hw::InnerRefAttr servicePortAttr;
  ::mlir::TypeAttr typeIDAttr;
  ::mlir::DictionaryAttr channelAssignmentsAttr;
  ::mlir::DictionaryAttr implDetailsAttr;

  if (parser.parseCustomAttributeWithFallback(relAppIDPathAttr, parser.getBuilder().getType<::mlir::NoneType>())) {
    return ::mlir::failure();
  }
  if (relAppIDPathAttr) result.getOrAddProperties<ServiceImplClientRecordOp::Properties>().relAppIDPath = relAppIDPathAttr;
  if (parser.parseKeyword("req"))
    return ::mlir::failure();

  if (parser.parseCustomAttributeWithFallback(servicePortAttr, ::mlir::Type{})) {
    return ::mlir::failure();
  }
  if (servicePortAttr) result.getOrAddProperties<ServiceImplClientRecordOp::Properties>().servicePort = servicePortAttr;
  if (parser.parseLParen())
    return ::mlir::failure();

  if (parser.parseCustomAttributeWithFallback(typeIDAttr, parser.getBuilder().getType<::mlir::NoneType>())) {
    return ::mlir::failure();
  }
  if (typeIDAttr) result.getOrAddProperties<ServiceImplClientRecordOp::Properties>().typeID = typeIDAttr;
  if (parser.parseRParen())
    return ::mlir::failure();
  if (::mlir::succeeded(parser.parseOptionalKeyword("channels"))) {

  if (parser.parseCustomAttributeWithFallback(channelAssignmentsAttr, parser.getBuilder().getType<::mlir::NoneType>())) {
    return ::mlir::failure();
  }
  if (channelAssignmentsAttr) result.getOrAddProperties<ServiceImplClientRecordOp::Properties>().channelAssignments = channelAssignmentsAttr;
  }
  if (::mlir::succeeded(parser.parseOptionalKeyword("with"))) {

  if (parser.parseCustomAttributeWithFallback(implDetailsAttr, parser.getBuilder().getType<::mlir::NoneType>())) {
    return ::mlir::failure();
  }
  if (implDetailsAttr) result.getOrAddProperties<ServiceImplClientRecordOp::Properties>().implDetails = implDetailsAttr;
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

void ServiceImplClientRecordOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter.printAttributeWithoutType(getRelAppIDPathAttr());
  _odsPrinter << ' ' << "req";
  _odsPrinter << ' ';
_odsPrinter.printStrippedAttrOrType(getServicePortAttr());
  _odsPrinter << "(";
  _odsPrinter.printAttributeWithoutType(getTypeIDAttr());
  _odsPrinter << ")";
  if (getChannelAssignmentsAttr()) {
    _odsPrinter << ' ' << "channels";
    _odsPrinter << ' ';
    _odsPrinter.printAttributeWithoutType(getChannelAssignmentsAttr());
  }
  if (getImplDetailsAttr()) {
    _odsPrinter << ' ' << "with";
    _odsPrinter << ' ';
    _odsPrinter.printAttributeWithoutType(getImplDetailsAttr());
  }
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("relAppIDPath");
  elidedAttrs.push_back("servicePort");
  elidedAttrs.push_back("typeID");
  elidedAttrs.push_back("channelAssignments");
  elidedAttrs.push_back("implDetails");
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
}


} // namespace circt::esi
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::esi::ServiceImplClientRecordOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::esi::detail::ServiceImplClientRecordOpGenericAdaptorBase::Properties)

namespace circt::esi {


//===----------------------------------------------------------------------===//
// ::circt::esi::ServiceImplRecordOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

ServiceImplRecordOpGenericAdaptorBase::ServiceImplRecordOpGenericAdaptorBase(ServiceImplRecordOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::circt::esi::AppIDAttr ServiceImplRecordOpGenericAdaptorBase::getAppID() {
  auto attr = getAppIDAttr();
  return ::llvm::cast<::circt::esi::AppIDAttr>(attr);
}

::mlir::UnitAttr ServiceImplRecordOpGenericAdaptorBase::getIsEngineAttr() {
  auto attr = ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(getProperties().isEngine);
  return attr;
}

bool ServiceImplRecordOpGenericAdaptorBase::getIsEngine() {
  auto attr = getIsEngineAttr();
  return attr != nullptr;
}

::std::optional< ::llvm::StringRef > ServiceImplRecordOpGenericAdaptorBase::getService() {
  auto attr = getServiceAttr();
  return attr ? ::std::optional< ::llvm::StringRef >(attr.getValue()) : (::std::nullopt);
}

::std::optional< ::llvm::StringRef > ServiceImplRecordOpGenericAdaptorBase::getStdService() {
  auto attr = getStdServiceAttr();
  return attr ? ::std::optional< ::llvm::StringRef >(attr.getValue()) : (::std::nullopt);
}

::llvm::StringRef ServiceImplRecordOpGenericAdaptorBase::getServiceImplName() {
  auto attr = getServiceImplNameAttr();
  return attr.getValue();
}

::mlir::DictionaryAttr ServiceImplRecordOpGenericAdaptorBase::getImplDetails() {
  auto attr = getImplDetailsAttr();
  return attr;
}


} // namespace detail
ServiceImplRecordOpAdaptor::ServiceImplRecordOpAdaptor(ServiceImplRecordOp op) : ServiceImplRecordOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult ServiceImplRecordOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_appID = getProperties().appID; (void)tblgen_appID;
  if (!tblgen_appID) return emitError(loc, "'esi.manifest.service_impl' op requires attribute 'appID'");
  auto tblgen_implDetails = getProperties().implDetails; (void)tblgen_implDetails;
  if (!tblgen_implDetails) return emitError(loc, "'esi.manifest.service_impl' op requires attribute 'implDetails'");
  auto tblgen_isEngine = getProperties().isEngine; (void)tblgen_isEngine;
  auto tblgen_service = getProperties().service; (void)tblgen_service;
  auto tblgen_serviceImplName = getProperties().serviceImplName; (void)tblgen_serviceImplName;
  if (!tblgen_serviceImplName) return emitError(loc, "'esi.manifest.service_impl' op requires attribute 'serviceImplName'");
  auto tblgen_stdService = getProperties().stdService; (void)tblgen_stdService;

  if (tblgen_appID && !((::llvm::isa<::circt::esi::AppIDAttr>(tblgen_appID))))
    return emitError(loc, "'esi.manifest.service_impl' op attribute 'appID' failed to satisfy constraint: An application relevant instance identifier");

  if (tblgen_isEngine && !((::llvm::isa<::mlir::UnitAttr>(tblgen_isEngine))))
    return emitError(loc, "'esi.manifest.service_impl' op attribute 'isEngine' failed to satisfy constraint: unit attribute");

  if (tblgen_service && !((::llvm::isa<::mlir::FlatSymbolRefAttr>(tblgen_service))))
    return emitError(loc, "'esi.manifest.service_impl' op attribute 'service' failed to satisfy constraint: flat symbol reference attribute");

  if (tblgen_stdService && !((::llvm::isa<::mlir::StringAttr>(tblgen_stdService))))
    return emitError(loc, "'esi.manifest.service_impl' op attribute 'stdService' failed to satisfy constraint: string attribute");

  if (tblgen_serviceImplName && !((::llvm::isa<::mlir::StringAttr>(tblgen_serviceImplName))))
    return emitError(loc, "'esi.manifest.service_impl' op attribute 'serviceImplName' failed to satisfy constraint: string attribute");

  if (tblgen_implDetails && !((::llvm::isa<::mlir::DictionaryAttr>(tblgen_implDetails))))
    return emitError(loc, "'esi.manifest.service_impl' op attribute 'implDetails' failed to satisfy constraint: dictionary of named attribute values");
  return ::mlir::success();
}

::llvm::LogicalResult ServiceImplRecordOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.appID;
       auto attr = dict.get("appID");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `appID` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.implDetails;
       auto attr = dict.get("implDetails");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `implDetails` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.isEngine;
       auto attr = dict.get("isEngine");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `isEngine` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.service;
       auto attr = dict.get("service");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `service` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.serviceImplName;
       auto attr = dict.get("serviceImplName");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `serviceImplName` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.stdService;
       auto attr = dict.get("stdService");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `stdService` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  return ::mlir::success();
}

::mlir::Attribute ServiceImplRecordOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.appID;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("appID",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.implDetails;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("implDetails",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.isEngine;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("isEngine",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.service;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("service",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.serviceImplName;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("serviceImplName",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.stdService;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("stdService",
                                       propStorage));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code ServiceImplRecordOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.appID.getAsOpaquePointer()), 
    llvm::hash_value(prop.implDetails.getAsOpaquePointer()), 
    llvm::hash_value(prop.isEngine.getAsOpaquePointer()), 
    llvm::hash_value(prop.service.getAsOpaquePointer()), 
    llvm::hash_value(prop.serviceImplName.getAsOpaquePointer()), 
    llvm::hash_value(prop.stdService.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> ServiceImplRecordOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "appID")
      return prop.appID;

    if (name == "implDetails")
      return prop.implDetails;

    if (name == "isEngine")
      return prop.isEngine;

    if (name == "service")
      return prop.service;

    if (name == "serviceImplName")
      return prop.serviceImplName;

    if (name == "stdService")
      return prop.stdService;
  return std::nullopt;
}

void ServiceImplRecordOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "appID") {
       prop.appID = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.appID)>>(value);
       return;
    }

    if (name == "implDetails") {
       prop.implDetails = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.implDetails)>>(value);
       return;
    }

    if (name == "isEngine") {
       prop.isEngine = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.isEngine)>>(value);
       return;
    }

    if (name == "service") {
       prop.service = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.service)>>(value);
       return;
    }

    if (name == "serviceImplName") {
       prop.serviceImplName = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.serviceImplName)>>(value);
       return;
    }

    if (name == "stdService") {
       prop.stdService = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.stdService)>>(value);
       return;
    }
}

void ServiceImplRecordOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.appID) attrs.append("appID", prop.appID);

    if (prop.implDetails) attrs.append("implDetails", prop.implDetails);

    if (prop.isEngine) attrs.append("isEngine", prop.isEngine);

    if (prop.service) attrs.append("service", prop.service);

    if (prop.serviceImplName) attrs.append("serviceImplName", prop.serviceImplName);

    if (prop.stdService) attrs.append("stdService", prop.stdService);
}

::llvm::LogicalResult ServiceImplRecordOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getAppIDAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_ESI1(attr, "appID", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getImplDetailsAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_ESI11(attr, "implDetails", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getIsEngineAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_ESI12(attr, "isEngine", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getServiceAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_ESI2(attr, "service", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getServiceImplNameAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_ESI3(attr, "serviceImplName", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getStdServiceAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_ESI3(attr, "stdService", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult ServiceImplRecordOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.appID)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readAttribute(prop.implDetails)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readOptionalAttribute(prop.isEngine)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readOptionalAttribute(prop.service)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readAttribute(prop.serviceImplName)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readOptionalAttribute(prop.stdService)))
    return ::mlir::failure();
  return ::mlir::success();
}

void ServiceImplRecordOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.appID);
  writer.writeAttribute(prop.implDetails);

  writer.writeOptionalAttribute(prop.isEngine);

  writer.writeOptionalAttribute(prop.service);
  writer.writeAttribute(prop.serviceImplName);

  writer.writeOptionalAttribute(prop.stdService);
}

::circt::esi::AppIDAttr ServiceImplRecordOp::getAppID() {
  auto attr = getAppIDAttr();
  return ::llvm::cast<::circt::esi::AppIDAttr>(attr);
}

bool ServiceImplRecordOp::getIsEngine() {
  auto attr = getIsEngineAttr();
  return attr != nullptr;
}

::std::optional< ::llvm::StringRef > ServiceImplRecordOp::getService() {
  auto attr = getServiceAttr();
  return attr ? ::std::optional< ::llvm::StringRef >(attr.getValue()) : (::std::nullopt);
}

::std::optional< ::llvm::StringRef > ServiceImplRecordOp::getStdService() {
  auto attr = getStdServiceAttr();
  return attr ? ::std::optional< ::llvm::StringRef >(attr.getValue()) : (::std::nullopt);
}

::llvm::StringRef ServiceImplRecordOp::getServiceImplName() {
  auto attr = getServiceImplNameAttr();
  return attr.getValue();
}

::mlir::DictionaryAttr ServiceImplRecordOp::getImplDetails() {
  auto attr = getImplDetailsAttr();
  return attr;
}

void ServiceImplRecordOp::setIsEngine(bool attrValue) {
  getProperties().isEngine = ((attrValue) ? ::mlir::Builder((*this)->getContext()).getUnitAttr() : nullptr);
}

void ServiceImplRecordOp::setService(::std::optional<::llvm::StringRef> attrValue) {
    auto &odsProp = getProperties().service;
    if (attrValue)
      odsProp = ::mlir::SymbolRefAttr::get(::mlir::Builder((*this)->getContext()).getContext(), *attrValue);
    else
      odsProp = nullptr;
}

void ServiceImplRecordOp::setStdService(::std::optional<::llvm::StringRef> attrValue) {
    auto &odsProp = getProperties().stdService;
    if (attrValue)
      odsProp = ::mlir::Builder((*this)->getContext()).getStringAttr(*attrValue);
    else
      odsProp = nullptr;
}

void ServiceImplRecordOp::setServiceImplName(::llvm::StringRef attrValue) {
  getProperties().serviceImplName = ::mlir::Builder((*this)->getContext()).getStringAttr(attrValue);
}

void ServiceImplRecordOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::circt::esi::AppIDAttr appID, ::mlir::UnitAttr isEngine, /*optional*/::mlir::FlatSymbolRefAttr service, /*optional*/::mlir::StringAttr stdService, ::mlir::StringAttr serviceImplName, ::mlir::DictionaryAttr implDetails) {
  odsState.getOrAddProperties<Properties>().appID = appID;
  if (isEngine) {
    odsState.getOrAddProperties<Properties>().isEngine = isEngine;
  }
  if (service) {
    odsState.getOrAddProperties<Properties>().service = service;
  }
  if (stdService) {
    odsState.getOrAddProperties<Properties>().stdService = stdService;
  }
  odsState.getOrAddProperties<Properties>().serviceImplName = serviceImplName;
  odsState.getOrAddProperties<Properties>().implDetails = implDetails;
  (void)odsState.addRegion();
}

ServiceImplRecordOp ServiceImplRecordOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::circt::esi::AppIDAttr appID, ::mlir::UnitAttr isEngine, /*optional*/::mlir::FlatSymbolRefAttr service, /*optional*/::mlir::StringAttr stdService, ::mlir::StringAttr serviceImplName, ::mlir::DictionaryAttr implDetails) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(appID)>(appID), std::forward<decltype(isEngine)>(isEngine), std::forward<decltype(service)>(service), std::forward<decltype(stdService)>(stdService), std::forward<decltype(serviceImplName)>(serviceImplName), std::forward<decltype(implDetails)>(implDetails));
  auto __res__ = ::llvm::dyn_cast<ServiceImplRecordOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ServiceImplRecordOp ServiceImplRecordOp::create(::mlir::ImplicitLocOpBuilder &builder, ::circt::esi::AppIDAttr appID, ::mlir::UnitAttr isEngine, /*optional*/::mlir::FlatSymbolRefAttr service, /*optional*/::mlir::StringAttr stdService, ::mlir::StringAttr serviceImplName, ::mlir::DictionaryAttr implDetails) {
  return create(builder, builder.getLoc(), std::forward<decltype(appID)>(appID), std::forward<decltype(isEngine)>(isEngine), std::forward<decltype(service)>(service), std::forward<decltype(stdService)>(stdService), std::forward<decltype(serviceImplName)>(serviceImplName), std::forward<decltype(implDetails)>(implDetails));
}

void ServiceImplRecordOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::circt::esi::AppIDAttr appID, ::mlir::UnitAttr isEngine, /*optional*/::mlir::FlatSymbolRefAttr service, /*optional*/::mlir::StringAttr stdService, ::mlir::StringAttr serviceImplName, ::mlir::DictionaryAttr implDetails) {
  odsState.getOrAddProperties<Properties>().appID = appID;
  if (isEngine) {
    odsState.getOrAddProperties<Properties>().isEngine = isEngine;
  }
  if (service) {
    odsState.getOrAddProperties<Properties>().service = service;
  }
  if (stdService) {
    odsState.getOrAddProperties<Properties>().stdService = stdService;
  }
  odsState.getOrAddProperties<Properties>().serviceImplName = serviceImplName;
  odsState.getOrAddProperties<Properties>().implDetails = implDetails;
  (void)odsState.addRegion();
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

ServiceImplRecordOp ServiceImplRecordOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::circt::esi::AppIDAttr appID, ::mlir::UnitAttr isEngine, /*optional*/::mlir::FlatSymbolRefAttr service, /*optional*/::mlir::StringAttr stdService, ::mlir::StringAttr serviceImplName, ::mlir::DictionaryAttr implDetails) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(appID)>(appID), std::forward<decltype(isEngine)>(isEngine), std::forward<decltype(service)>(service), std::forward<decltype(stdService)>(stdService), std::forward<decltype(serviceImplName)>(serviceImplName), std::forward<decltype(implDetails)>(implDetails));
  auto __res__ = ::llvm::dyn_cast<ServiceImplRecordOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ServiceImplRecordOp ServiceImplRecordOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::circt::esi::AppIDAttr appID, ::mlir::UnitAttr isEngine, /*optional*/::mlir::FlatSymbolRefAttr service, /*optional*/::mlir::StringAttr stdService, ::mlir::StringAttr serviceImplName, ::mlir::DictionaryAttr implDetails) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(appID)>(appID), std::forward<decltype(isEngine)>(isEngine), std::forward<decltype(service)>(service), std::forward<decltype(stdService)>(stdService), std::forward<decltype(serviceImplName)>(serviceImplName), std::forward<decltype(implDetails)>(implDetails));
}

void ServiceImplRecordOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::circt::esi::AppIDAttr appID, bool isEngine, /*optional*/::mlir::FlatSymbolRefAttr service, /*optional*/::mlir::StringAttr stdService, ::llvm::StringRef serviceImplName, ::mlir::DictionaryAttr implDetails) {
  odsState.getOrAddProperties<Properties>().appID = appID;
  if (isEngine) {
    odsState.getOrAddProperties<Properties>().isEngine = ((isEngine) ? odsBuilder.getUnitAttr() : nullptr);
  }
  if (service) {
    odsState.getOrAddProperties<Properties>().service = service;
  }
  if (stdService) {
    odsState.getOrAddProperties<Properties>().stdService = stdService;
  }
  odsState.getOrAddProperties<Properties>().serviceImplName = odsBuilder.getStringAttr(serviceImplName);
  odsState.getOrAddProperties<Properties>().implDetails = implDetails;
  (void)odsState.addRegion();
}

ServiceImplRecordOp ServiceImplRecordOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::circt::esi::AppIDAttr appID, bool isEngine, /*optional*/::mlir::FlatSymbolRefAttr service, /*optional*/::mlir::StringAttr stdService, ::llvm::StringRef serviceImplName, ::mlir::DictionaryAttr implDetails) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(appID)>(appID), std::forward<decltype(isEngine)>(isEngine), std::forward<decltype(service)>(service), std::forward<decltype(stdService)>(stdService), std::forward<decltype(serviceImplName)>(serviceImplName), std::forward<decltype(implDetails)>(implDetails));
  auto __res__ = ::llvm::dyn_cast<ServiceImplRecordOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ServiceImplRecordOp ServiceImplRecordOp::create(::mlir::ImplicitLocOpBuilder &builder, ::circt::esi::AppIDAttr appID, bool isEngine, /*optional*/::mlir::FlatSymbolRefAttr service, /*optional*/::mlir::StringAttr stdService, ::llvm::StringRef serviceImplName, ::mlir::DictionaryAttr implDetails) {
  return create(builder, builder.getLoc(), std::forward<decltype(appID)>(appID), std::forward<decltype(isEngine)>(isEngine), std::forward<decltype(service)>(service), std::forward<decltype(stdService)>(stdService), std::forward<decltype(serviceImplName)>(serviceImplName), std::forward<decltype(implDetails)>(implDetails));
}

void ServiceImplRecordOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::circt::esi::AppIDAttr appID, bool isEngine, /*optional*/::mlir::FlatSymbolRefAttr service, /*optional*/::mlir::StringAttr stdService, ::llvm::StringRef serviceImplName, ::mlir::DictionaryAttr implDetails) {
  odsState.getOrAddProperties<Properties>().appID = appID;
  if (isEngine) {
    odsState.getOrAddProperties<Properties>().isEngine = ((isEngine) ? odsBuilder.getUnitAttr() : nullptr);
  }
  if (service) {
    odsState.getOrAddProperties<Properties>().service = service;
  }
  if (stdService) {
    odsState.getOrAddProperties<Properties>().stdService = stdService;
  }
  odsState.getOrAddProperties<Properties>().serviceImplName = odsBuilder.getStringAttr(serviceImplName);
  odsState.getOrAddProperties<Properties>().implDetails = implDetails;
  (void)odsState.addRegion();
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

ServiceImplRecordOp ServiceImplRecordOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::circt::esi::AppIDAttr appID, bool isEngine, /*optional*/::mlir::FlatSymbolRefAttr service, /*optional*/::mlir::StringAttr stdService, ::llvm::StringRef serviceImplName, ::mlir::DictionaryAttr implDetails) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(appID)>(appID), std::forward<decltype(isEngine)>(isEngine), std::forward<decltype(service)>(service), std::forward<decltype(stdService)>(stdService), std::forward<decltype(serviceImplName)>(serviceImplName), std::forward<decltype(implDetails)>(implDetails));
  auto __res__ = ::llvm::dyn_cast<ServiceImplRecordOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ServiceImplRecordOp ServiceImplRecordOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::circt::esi::AppIDAttr appID, bool isEngine, /*optional*/::mlir::FlatSymbolRefAttr service, /*optional*/::mlir::StringAttr stdService, ::llvm::StringRef serviceImplName, ::mlir::DictionaryAttr implDetails) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(appID)>(appID), std::forward<decltype(isEngine)>(isEngine), std::forward<decltype(service)>(service), std::forward<decltype(stdService)>(stdService), std::forward<decltype(serviceImplName)>(serviceImplName), std::forward<decltype(implDetails)>(implDetails));
}

void ServiceImplRecordOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  for (unsigned i = 0; i != 1; ++i)
    (void)odsState.addRegion();
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<ServiceImplRecordOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

ServiceImplRecordOp ServiceImplRecordOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<ServiceImplRecordOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ServiceImplRecordOp ServiceImplRecordOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void ServiceImplRecordOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  for (unsigned i = 0; i != 1; ++i)
    (void)odsState.addRegion();
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

ServiceImplRecordOp ServiceImplRecordOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<ServiceImplRecordOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ServiceImplRecordOp ServiceImplRecordOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

void ServiceImplRecordOp::populateDefaultProperties(::mlir::OperationName opName, Properties &properties) {
  ::mlir::Builder odsBuilder(opName.getContext());
  if (!properties.isEngine)
    properties.isEngine = ((false) ? odsBuilder.getUnitAttr() : nullptr);
}

::llvm::LogicalResult ServiceImplRecordOp::verifyInvariantsImpl() {
  auto tblgen_appID = getProperties().appID; (void)tblgen_appID;
  if (!tblgen_appID) return emitOpError("requires attribute 'appID'");
  auto tblgen_implDetails = getProperties().implDetails; (void)tblgen_implDetails;
  if (!tblgen_implDetails) return emitOpError("requires attribute 'implDetails'");
  auto tblgen_isEngine = getProperties().isEngine; (void)tblgen_isEngine;
  auto tblgen_service = getProperties().service; (void)tblgen_service;
  auto tblgen_serviceImplName = getProperties().serviceImplName; (void)tblgen_serviceImplName;
  if (!tblgen_serviceImplName) return emitOpError("requires attribute 'serviceImplName'");
  auto tblgen_stdService = getProperties().stdService; (void)tblgen_stdService;

  if (::mlir::failed(__mlir_ods_local_attr_constraint_ESI1(*this, tblgen_appID, "appID")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_ESI12(*this, tblgen_isEngine, "isEngine")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_ESI2(*this, tblgen_service, "service")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_ESI3(*this, tblgen_stdService, "stdService")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_ESI3(*this, tblgen_serviceImplName, "serviceImplName")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_ESI11(*this, tblgen_implDetails, "implDetails")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;

    for (auto &region : ::llvm::MutableArrayRef((*this)->getRegion(0)))
      if (::mlir::failed(__mlir_ods_local_region_constraint_ESI1(*this, region, "reqDetails", index++)))
        return ::mlir::failure();
  }
  return ::mlir::success();
}

::llvm::LogicalResult ServiceImplRecordOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult ServiceImplRecordOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::circt::esi::AppIDAttr appIDAttr;
  ::mlir::FlatSymbolRefAttr serviceAttr;
  ::mlir::StringAttr stdServiceAttr;
  ::mlir::StringAttr serviceImplNameAttr;
  ::mlir::DictionaryAttr implDetailsAttr;
  std::unique_ptr<::mlir::Region> reqDetailsRegion = std::make_unique<::mlir::Region>();

  if (parser.parseAttribute(appIDAttr, ::mlir::Type{}))
    return ::mlir::failure();
  if (appIDAttr) result.getOrAddProperties<ServiceImplRecordOp::Properties>().appID = appIDAttr;
  if (::mlir::succeeded(parser.parseOptionalKeyword("svc"))) {

  if (parser.parseCustomAttributeWithFallback(serviceAttr, parser.getBuilder().getType<::mlir::NoneType>())) {
    return ::mlir::failure();
  }
  if (serviceAttr) result.getOrAddProperties<ServiceImplRecordOp::Properties>().service = serviceAttr;
  }
  if (::mlir::succeeded(parser.parseOptionalKeyword("std"))) {

  if (parser.parseCustomAttributeWithFallback(stdServiceAttr, parser.getBuilder().getType<::mlir::NoneType>())) {
    return ::mlir::failure();
  }
  if (stdServiceAttr) result.getOrAddProperties<ServiceImplRecordOp::Properties>().stdService = stdServiceAttr;
  }
  if (parser.parseKeyword("by"))
    return ::mlir::failure();

  if (parser.parseCustomAttributeWithFallback(serviceImplNameAttr, parser.getBuilder().getType<::mlir::NoneType>())) {
    return ::mlir::failure();
  }
  if (serviceImplNameAttr) result.getOrAddProperties<ServiceImplRecordOp::Properties>().serviceImplName = serviceImplNameAttr;
  if (::mlir::succeeded(parser.parseOptionalKeyword("engine"))) {
    result.getOrAddProperties<ServiceImplRecordOp::Properties>().isEngine = parser.getBuilder().getUnitAttr();  }
  if (parser.parseKeyword("with"))
    return ::mlir::failure();

  if (parser.parseCustomAttributeWithFallback(implDetailsAttr, parser.getBuilder().getType<::mlir::NoneType>())) {
    return ::mlir::failure();
  }
  if (implDetailsAttr) result.getOrAddProperties<ServiceImplRecordOp::Properties>().implDetails = implDetailsAttr;
  {
    auto loc = parser.getCurrentLocation();(void)loc;
    if (parser.parseOptionalAttrDictWithKeyword(result.attributes))
      return ::mlir::failure();
    if (failed(verifyInherentAttrs(result.name, result.attributes, [&]() {
        return parser.emitError(loc) << "'" << result.name.getStringRef() << "' op ";
      })))
      return ::mlir::failure();
  }
  {
    auto odsResult = parseServiceImplRecordReqDetails(parser, *reqDetailsRegion);
    if (odsResult) return ::mlir::failure();
  }
  result.addRegion(std::move(reqDetailsRegion));
  return ::mlir::success();
}

void ServiceImplRecordOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter.printAttribute(getAppIDAttr());
  if (getServiceAttr()) {
    _odsPrinter << ' ' << "svc";
    _odsPrinter << ' ';
    _odsPrinter.printAttributeWithoutType(getServiceAttr());
  }
  if (getStdServiceAttr()) {
    _odsPrinter << ' ' << "std";
    _odsPrinter << ' ';
    _odsPrinter.printAttributeWithoutType(getStdServiceAttr());
  }
  _odsPrinter << ' ' << "by";
  _odsPrinter << ' ';
  _odsPrinter.printAttributeWithoutType(getServiceImplNameAttr());
  if (getIsEngineAttr() != ((false) ? ::mlir::OpBuilder((*this)->getContext()).getUnitAttr() : nullptr)) {
    _odsPrinter << ' ' << "engine";
  }
  _odsPrinter << ' ' << "with";
  _odsPrinter << ' ';
  _odsPrinter.printAttributeWithoutType(getImplDetailsAttr());
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("appID");
  elidedAttrs.push_back("service");
  elidedAttrs.push_back("stdService");
  elidedAttrs.push_back("serviceImplName");
  elidedAttrs.push_back("isEngine");
  elidedAttrs.push_back("implDetails");
  {
     ::mlir::Builder odsBuilder(getContext());
     ::mlir::Attribute attr = getIsEngineAttr();
     if(attr && (attr == ((false) ? odsBuilder.getUnitAttr() : nullptr)))
       elidedAttrs.push_back("isEngine");
  }
  _odsPrinter.printOptionalAttrDictWithKeyword((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ';
  printServiceImplRecordReqDetails(_odsPrinter, *this, getReqDetails());
}


} // namespace circt::esi
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::esi::ServiceImplRecordOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::esi::detail::ServiceImplRecordOpGenericAdaptorBase::Properties)

namespace circt::esi {


//===----------------------------------------------------------------------===//
// ::circt::esi::ServiceImplementConnReqOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

ServiceImplementConnReqOpGenericAdaptorBase::ServiceImplementConnReqOpGenericAdaptorBase(ServiceImplementConnReqOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::circt::hw::InnerRefAttr ServiceImplementConnReqOpGenericAdaptorBase::getServicePort() {
  auto attr = getServicePortAttr();
  return ::llvm::cast<::circt::hw::InnerRefAttr>(attr);
}

::mlir::ArrayAttr ServiceImplementConnReqOpGenericAdaptorBase::getRelativeAppIDPath() {
  auto attr = getRelativeAppIDPathAttr();
  return attr;
}


} // namespace detail
ServiceImplementConnReqOpAdaptor::ServiceImplementConnReqOpAdaptor(ServiceImplementConnReqOp op) : ServiceImplementConnReqOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult ServiceImplementConnReqOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_relativeAppIDPath = getProperties().relativeAppIDPath; (void)tblgen_relativeAppIDPath;
  if (!tblgen_relativeAppIDPath) return emitError(loc, "'esi.service.impl_req.req' op requires attribute 'relativeAppIDPath'");
  auto tblgen_servicePort = getProperties().servicePort; (void)tblgen_servicePort;
  if (!tblgen_servicePort) return emitError(loc, "'esi.service.impl_req.req' op requires attribute 'servicePort'");

  if (tblgen_servicePort && !((::llvm::isa<::circt::hw::InnerRefAttr>(tblgen_servicePort))))
    return emitError(loc, "'esi.service.impl_req.req' op attribute 'servicePort' failed to satisfy constraint: Refer to a name inside a module");

  if (tblgen_relativeAppIDPath && !(((::llvm::isa<::mlir::ArrayAttr>(tblgen_relativeAppIDPath))) && (::llvm::all_of(::llvm::cast<::mlir::ArrayAttr>(tblgen_relativeAppIDPath), [&](::mlir::Attribute attr) { return attr && ((::llvm::isa<::circt::esi::AppIDAttr>(attr))); }))))
    return emitError(loc, "'esi.service.impl_req.req' op attribute 'relativeAppIDPath' failed to satisfy constraint: Array of AppIDs");
  return ::mlir::success();
}

::llvm::LogicalResult ServiceImplementConnReqOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.relativeAppIDPath;
       auto attr = dict.get("relativeAppIDPath");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `relativeAppIDPath` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.servicePort;
       auto attr = dict.get("servicePort");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `servicePort` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  return ::mlir::success();
}

::mlir::Attribute ServiceImplementConnReqOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.relativeAppIDPath;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("relativeAppIDPath",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.servicePort;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("servicePort",
                                       propStorage));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code ServiceImplementConnReqOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.relativeAppIDPath.getAsOpaquePointer()), 
    llvm::hash_value(prop.servicePort.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> ServiceImplementConnReqOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "relativeAppIDPath")
      return prop.relativeAppIDPath;

    if (name == "servicePort")
      return prop.servicePort;
  return std::nullopt;
}

void ServiceImplementConnReqOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "relativeAppIDPath") {
       prop.relativeAppIDPath = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.relativeAppIDPath)>>(value);
       return;
    }

    if (name == "servicePort") {
       prop.servicePort = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.servicePort)>>(value);
       return;
    }
}

void ServiceImplementConnReqOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.relativeAppIDPath) attrs.append("relativeAppIDPath", prop.relativeAppIDPath);

    if (prop.servicePort) attrs.append("servicePort", prop.servicePort);
}

::llvm::LogicalResult ServiceImplementConnReqOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getRelativeAppIDPathAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_ESI10(attr, "relativeAppIDPath", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getServicePortAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_ESI8(attr, "servicePort", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult ServiceImplementConnReqOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.relativeAppIDPath)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readAttribute(prop.servicePort)))
    return ::mlir::failure();
  return ::mlir::success();
}

void ServiceImplementConnReqOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.relativeAppIDPath);
  writer.writeAttribute(prop.servicePort);
}

::circt::hw::InnerRefAttr ServiceImplementConnReqOp::getServicePort() {
  auto attr = getServicePortAttr();
  return ::llvm::cast<::circt::hw::InnerRefAttr>(attr);
}

::mlir::ArrayAttr ServiceImplementConnReqOp::getRelativeAppIDPath() {
  auto attr = getRelativeAppIDPathAttr();
  return attr;
}

void ServiceImplementConnReqOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type toClient, ::circt::hw::InnerRefAttr servicePort, ::mlir::ArrayAttr relativeAppIDPath) {
  odsState.getOrAddProperties<Properties>().servicePort = servicePort;
  odsState.getOrAddProperties<Properties>().relativeAppIDPath = relativeAppIDPath;
  odsState.addTypes(toClient);
}

ServiceImplementConnReqOp ServiceImplementConnReqOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type toClient, ::circt::hw::InnerRefAttr servicePort, ::mlir::ArrayAttr relativeAppIDPath) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(toClient)>(toClient), std::forward<decltype(servicePort)>(servicePort), std::forward<decltype(relativeAppIDPath)>(relativeAppIDPath));
  auto __res__ = ::llvm::dyn_cast<ServiceImplementConnReqOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ServiceImplementConnReqOp ServiceImplementConnReqOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type toClient, ::circt::hw::InnerRefAttr servicePort, ::mlir::ArrayAttr relativeAppIDPath) {
  return create(builder, builder.getLoc(), std::forward<decltype(toClient)>(toClient), std::forward<decltype(servicePort)>(servicePort), std::forward<decltype(relativeAppIDPath)>(relativeAppIDPath));
}

void ServiceImplementConnReqOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::circt::hw::InnerRefAttr servicePort, ::mlir::ArrayAttr relativeAppIDPath) {
  odsState.getOrAddProperties<Properties>().servicePort = servicePort;
  odsState.getOrAddProperties<Properties>().relativeAppIDPath = relativeAppIDPath;
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

ServiceImplementConnReqOp ServiceImplementConnReqOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::circt::hw::InnerRefAttr servicePort, ::mlir::ArrayAttr relativeAppIDPath) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(servicePort)>(servicePort), std::forward<decltype(relativeAppIDPath)>(relativeAppIDPath));
  auto __res__ = ::llvm::dyn_cast<ServiceImplementConnReqOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ServiceImplementConnReqOp ServiceImplementConnReqOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::circt::hw::InnerRefAttr servicePort, ::mlir::ArrayAttr relativeAppIDPath) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(servicePort)>(servicePort), std::forward<decltype(relativeAppIDPath)>(relativeAppIDPath));
}

void ServiceImplementConnReqOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<ServiceImplementConnReqOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

ServiceImplementConnReqOp ServiceImplementConnReqOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<ServiceImplementConnReqOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ServiceImplementConnReqOp ServiceImplementConnReqOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void ServiceImplementConnReqOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

ServiceImplementConnReqOp ServiceImplementConnReqOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<ServiceImplementConnReqOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ServiceImplementConnReqOp ServiceImplementConnReqOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult ServiceImplementConnReqOp::verifyInvariantsImpl() {
  auto tblgen_relativeAppIDPath = getProperties().relativeAppIDPath; (void)tblgen_relativeAppIDPath;
  if (!tblgen_relativeAppIDPath) return emitOpError("requires attribute 'relativeAppIDPath'");
  auto tblgen_servicePort = getProperties().servicePort; (void)tblgen_servicePort;
  if (!tblgen_servicePort) return emitOpError("requires attribute 'servicePort'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_ESI8(*this, tblgen_servicePort, "servicePort")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_ESI10(*this, tblgen_relativeAppIDPath, "relativeAppIDPath")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_ESI6(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult ServiceImplementConnReqOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult ServiceImplementConnReqOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::circt::hw::InnerRefAttr servicePortAttr;
  ::mlir::ArrayAttr relativeAppIDPathAttr;
  ::mlir::Type toClientRawType{};
  ::llvm::ArrayRef<::mlir::Type> toClientTypes(&toClientRawType, 1);

  if (parser.parseCustomAttributeWithFallback(servicePortAttr, ::mlir::Type{})) {
    return ::mlir::failure();
  }
  if (servicePortAttr) result.getOrAddProperties<ServiceImplementConnReqOp::Properties>().servicePort = servicePortAttr;
  if (parser.parseLParen())
    return ::mlir::failure();

  if (parser.parseCustomAttributeWithFallback(relativeAppIDPathAttr, parser.getBuilder().getType<::mlir::NoneType>())) {
    return ::mlir::failure();
  }
  if (relativeAppIDPathAttr) result.getOrAddProperties<ServiceImplementConnReqOp::Properties>().relativeAppIDPath = relativeAppIDPathAttr;
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

  if (parser.parseType(toClientRawType))
    return ::mlir::failure();
  result.addTypes(toClientTypes);
  return ::mlir::success();
}

void ServiceImplementConnReqOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
_odsPrinter.printStrippedAttrOrType(getServicePortAttr());
  _odsPrinter << "(";
  _odsPrinter.printAttributeWithoutType(getRelativeAppIDPathAttr());
  _odsPrinter << ")";
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("servicePort");
  elidedAttrs.push_back("relativeAppIDPath");
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
   _odsPrinter << getToClient().getType();
}


} // namespace circt::esi
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::esi::ServiceImplementConnReqOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::esi::detail::ServiceImplementConnReqOpGenericAdaptorBase::Properties)

namespace circt::esi {


//===----------------------------------------------------------------------===//
// ::circt::esi::ServiceImplementReqOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

ServiceImplementReqOpGenericAdaptorBase::ServiceImplementReqOpGenericAdaptorBase(ServiceImplementReqOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

std::pair<unsigned, unsigned> ServiceImplementReqOpGenericAdaptorBase::getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
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

::circt::esi::AppIDAttr ServiceImplementReqOpGenericAdaptorBase::getAppID() {
  auto attr = getAppIDAttr();
  return ::llvm::cast<::circt::esi::AppIDAttr>(attr);
}

::std::optional< ::llvm::StringRef > ServiceImplementReqOpGenericAdaptorBase::getServiceSymbol() {
  auto attr = getServiceSymbolAttr();
  return attr ? ::std::optional< ::llvm::StringRef >(attr.getValue()) : (::std::nullopt);
}

::llvm::StringRef ServiceImplementReqOpGenericAdaptorBase::getImplType() {
  auto attr = getImplTypeAttr();
  return attr.getValue();
}

::std::optional< ::llvm::StringRef > ServiceImplementReqOpGenericAdaptorBase::getStdService() {
  auto attr = getStdServiceAttr();
  return attr ? ::std::optional< ::llvm::StringRef >(attr.getValue()) : (::std::nullopt);
}

::std::optional< ::mlir::DictionaryAttr > ServiceImplementReqOpGenericAdaptorBase::getImplOpts() {
  auto attr = getImplOptsAttr();
  return attr ? ::std::optional< ::mlir::DictionaryAttr >(attr) : (::std::nullopt);
}


} // namespace detail
ServiceImplementReqOpAdaptor::ServiceImplementReqOpAdaptor(ServiceImplementReqOp op) : ServiceImplementReqOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult ServiceImplementReqOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_appID = getProperties().appID; (void)tblgen_appID;
  if (!tblgen_appID) return emitError(loc, "'esi.service.impl_req' op requires attribute 'appID'");
  auto tblgen_impl_opts = getProperties().impl_opts; (void)tblgen_impl_opts;
  auto tblgen_impl_type = getProperties().impl_type; (void)tblgen_impl_type;
  if (!tblgen_impl_type) return emitError(loc, "'esi.service.impl_req' op requires attribute 'impl_type'");
  auto tblgen_service_symbol = getProperties().service_symbol; (void)tblgen_service_symbol;
  auto tblgen_stdService = getProperties().stdService; (void)tblgen_stdService;

  if (tblgen_appID && !((::llvm::isa<::circt::esi::AppIDAttr>(tblgen_appID))))
    return emitError(loc, "'esi.service.impl_req' op attribute 'appID' failed to satisfy constraint: An application relevant instance identifier");

  if (tblgen_service_symbol && !((::llvm::isa<::mlir::FlatSymbolRefAttr>(tblgen_service_symbol))))
    return emitError(loc, "'esi.service.impl_req' op attribute 'service_symbol' failed to satisfy constraint: flat symbol reference attribute");

  if (tblgen_impl_type && !((::llvm::isa<::mlir::StringAttr>(tblgen_impl_type))))
    return emitError(loc, "'esi.service.impl_req' op attribute 'impl_type' failed to satisfy constraint: string attribute");

  if (tblgen_stdService && !((::llvm::isa<::mlir::StringAttr>(tblgen_stdService))))
    return emitError(loc, "'esi.service.impl_req' op attribute 'stdService' failed to satisfy constraint: string attribute");

  if (tblgen_impl_opts && !((::llvm::isa<::mlir::DictionaryAttr>(tblgen_impl_opts))))
    return emitError(loc, "'esi.service.impl_req' op attribute 'impl_opts' failed to satisfy constraint: dictionary of named attribute values");
  return ::mlir::success();
}

std::pair<unsigned, unsigned> ServiceImplementReqOp::getODSOperandIndexAndLength(unsigned index) {
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

::mlir::MutableOperandRange ServiceImplementReqOp::getInputsMutable() {
  auto range = getODSOperandIndexAndLength(0);
  auto mutableRange = ::mlir::MutableOperandRange(getOperation(), range.first, range.second);
  return mutableRange;
}

std::pair<unsigned, unsigned> ServiceImplementReqOp::getODSResultIndexAndLength(unsigned index) {
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

::llvm::LogicalResult ServiceImplementReqOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.appID;
       auto attr = dict.get("appID");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `appID` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.impl_opts;
       auto attr = dict.get("impl_opts");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `impl_opts` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.impl_type;
       auto attr = dict.get("impl_type");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `impl_type` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.service_symbol;
       auto attr = dict.get("service_symbol");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `service_symbol` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.stdService;
       auto attr = dict.get("stdService");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `stdService` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  return ::mlir::success();
}

::mlir::Attribute ServiceImplementReqOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.appID;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("appID",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.impl_opts;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("impl_opts",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.impl_type;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("impl_type",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.service_symbol;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("service_symbol",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.stdService;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("stdService",
                                       propStorage));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code ServiceImplementReqOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.appID.getAsOpaquePointer()), 
    llvm::hash_value(prop.impl_opts.getAsOpaquePointer()), 
    llvm::hash_value(prop.impl_type.getAsOpaquePointer()), 
    llvm::hash_value(prop.service_symbol.getAsOpaquePointer()), 
    llvm::hash_value(prop.stdService.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> ServiceImplementReqOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "appID")
      return prop.appID;

    if (name == "impl_opts")
      return prop.impl_opts;

    if (name == "impl_type")
      return prop.impl_type;

    if (name == "service_symbol")
      return prop.service_symbol;

    if (name == "stdService")
      return prop.stdService;
  return std::nullopt;
}

void ServiceImplementReqOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "appID") {
       prop.appID = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.appID)>>(value);
       return;
    }

    if (name == "impl_opts") {
       prop.impl_opts = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.impl_opts)>>(value);
       return;
    }

    if (name == "impl_type") {
       prop.impl_type = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.impl_type)>>(value);
       return;
    }

    if (name == "service_symbol") {
       prop.service_symbol = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.service_symbol)>>(value);
       return;
    }

    if (name == "stdService") {
       prop.stdService = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.stdService)>>(value);
       return;
    }
}

void ServiceImplementReqOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.appID) attrs.append("appID", prop.appID);

    if (prop.impl_opts) attrs.append("impl_opts", prop.impl_opts);

    if (prop.impl_type) attrs.append("impl_type", prop.impl_type);

    if (prop.service_symbol) attrs.append("service_symbol", prop.service_symbol);

    if (prop.stdService) attrs.append("stdService", prop.stdService);
}

::llvm::LogicalResult ServiceImplementReqOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getAppIDAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_ESI1(attr, "appID", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getImplOptsAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_ESI11(attr, "impl_opts", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getImplTypeAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_ESI3(attr, "impl_type", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getServiceSymbolAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_ESI2(attr, "service_symbol", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getStdServiceAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_ESI3(attr, "stdService", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult ServiceImplementReqOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.appID)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readOptionalAttribute(prop.impl_opts)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readAttribute(prop.impl_type)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readOptionalAttribute(prop.service_symbol)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readOptionalAttribute(prop.stdService)))
    return ::mlir::failure();
  return ::mlir::success();
}

void ServiceImplementReqOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.appID);

  writer.writeOptionalAttribute(prop.impl_opts);
  writer.writeAttribute(prop.impl_type);

  writer.writeOptionalAttribute(prop.service_symbol);

  writer.writeOptionalAttribute(prop.stdService);
}

::circt::esi::AppIDAttr ServiceImplementReqOp::getAppID() {
  auto attr = getAppIDAttr();
  return ::llvm::cast<::circt::esi::AppIDAttr>(attr);
}

::std::optional< ::llvm::StringRef > ServiceImplementReqOp::getServiceSymbol() {
  auto attr = getServiceSymbolAttr();
  return attr ? ::std::optional< ::llvm::StringRef >(attr.getValue()) : (::std::nullopt);
}

::llvm::StringRef ServiceImplementReqOp::getImplType() {
  auto attr = getImplTypeAttr();
  return attr.getValue();
}

::std::optional< ::llvm::StringRef > ServiceImplementReqOp::getStdService() {
  auto attr = getStdServiceAttr();
  return attr ? ::std::optional< ::llvm::StringRef >(attr.getValue()) : (::std::nullopt);
}

::std::optional< ::mlir::DictionaryAttr > ServiceImplementReqOp::getImplOpts() {
  auto attr = getImplOptsAttr();
  return attr ? ::std::optional< ::mlir::DictionaryAttr >(attr) : (::std::nullopt);
}

void ServiceImplementReqOp::setServiceSymbol(::std::optional<::llvm::StringRef> attrValue) {
    auto &odsProp = getProperties().service_symbol;
    if (attrValue)
      odsProp = ::mlir::SymbolRefAttr::get(::mlir::Builder((*this)->getContext()).getContext(), *attrValue);
    else
      odsProp = nullptr;
}

void ServiceImplementReqOp::setImplType(::llvm::StringRef attrValue) {
  getProperties().impl_type = ::mlir::Builder((*this)->getContext()).getStringAttr(attrValue);
}

void ServiceImplementReqOp::setStdService(::std::optional<::llvm::StringRef> attrValue) {
    auto &odsProp = getProperties().stdService;
    if (attrValue)
      odsProp = ::mlir::Builder((*this)->getContext()).getStringAttr(*attrValue);
    else
      odsProp = nullptr;
}

void ServiceImplementReqOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange outputs, ::circt::esi::AppIDAttr appID, /*optional*/::mlir::FlatSymbolRefAttr service_symbol, ::mlir::StringAttr impl_type, /*optional*/::mlir::StringAttr stdService, /*optional*/::mlir::DictionaryAttr impl_opts, ::mlir::ValueRange inputs) {
  odsState.addOperands(inputs);
  odsState.getOrAddProperties<Properties>().appID = appID;
  if (service_symbol) {
    odsState.getOrAddProperties<Properties>().service_symbol = service_symbol;
  }
  odsState.getOrAddProperties<Properties>().impl_type = impl_type;
  if (stdService) {
    odsState.getOrAddProperties<Properties>().stdService = stdService;
  }
  if (impl_opts) {
    odsState.getOrAddProperties<Properties>().impl_opts = impl_opts;
  }
  (void)odsState.addRegion();
  odsState.addTypes(outputs);
}

ServiceImplementReqOp ServiceImplementReqOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange outputs, ::circt::esi::AppIDAttr appID, /*optional*/::mlir::FlatSymbolRefAttr service_symbol, ::mlir::StringAttr impl_type, /*optional*/::mlir::StringAttr stdService, /*optional*/::mlir::DictionaryAttr impl_opts, ::mlir::ValueRange inputs) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(outputs)>(outputs), std::forward<decltype(appID)>(appID), std::forward<decltype(service_symbol)>(service_symbol), std::forward<decltype(impl_type)>(impl_type), std::forward<decltype(stdService)>(stdService), std::forward<decltype(impl_opts)>(impl_opts), std::forward<decltype(inputs)>(inputs));
  auto __res__ = ::llvm::dyn_cast<ServiceImplementReqOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ServiceImplementReqOp ServiceImplementReqOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange outputs, ::circt::esi::AppIDAttr appID, /*optional*/::mlir::FlatSymbolRefAttr service_symbol, ::mlir::StringAttr impl_type, /*optional*/::mlir::StringAttr stdService, /*optional*/::mlir::DictionaryAttr impl_opts, ::mlir::ValueRange inputs) {
  return create(builder, builder.getLoc(), std::forward<decltype(outputs)>(outputs), std::forward<decltype(appID)>(appID), std::forward<decltype(service_symbol)>(service_symbol), std::forward<decltype(impl_type)>(impl_type), std::forward<decltype(stdService)>(stdService), std::forward<decltype(impl_opts)>(impl_opts), std::forward<decltype(inputs)>(inputs));
}

void ServiceImplementReqOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange outputs, ::circt::esi::AppIDAttr appID, /*optional*/::mlir::FlatSymbolRefAttr service_symbol, ::llvm::StringRef impl_type, /*optional*/::mlir::StringAttr stdService, /*optional*/::mlir::DictionaryAttr impl_opts, ::mlir::ValueRange inputs) {
  odsState.addOperands(inputs);
  odsState.getOrAddProperties<Properties>().appID = appID;
  if (service_symbol) {
    odsState.getOrAddProperties<Properties>().service_symbol = service_symbol;
  }
  odsState.getOrAddProperties<Properties>().impl_type = odsBuilder.getStringAttr(impl_type);
  if (stdService) {
    odsState.getOrAddProperties<Properties>().stdService = stdService;
  }
  if (impl_opts) {
    odsState.getOrAddProperties<Properties>().impl_opts = impl_opts;
  }
  (void)odsState.addRegion();
  odsState.addTypes(outputs);
}

ServiceImplementReqOp ServiceImplementReqOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange outputs, ::circt::esi::AppIDAttr appID, /*optional*/::mlir::FlatSymbolRefAttr service_symbol, ::llvm::StringRef impl_type, /*optional*/::mlir::StringAttr stdService, /*optional*/::mlir::DictionaryAttr impl_opts, ::mlir::ValueRange inputs) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(outputs)>(outputs), std::forward<decltype(appID)>(appID), std::forward<decltype(service_symbol)>(service_symbol), std::forward<decltype(impl_type)>(impl_type), std::forward<decltype(stdService)>(stdService), std::forward<decltype(impl_opts)>(impl_opts), std::forward<decltype(inputs)>(inputs));
  auto __res__ = ::llvm::dyn_cast<ServiceImplementReqOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ServiceImplementReqOp ServiceImplementReqOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange outputs, ::circt::esi::AppIDAttr appID, /*optional*/::mlir::FlatSymbolRefAttr service_symbol, ::llvm::StringRef impl_type, /*optional*/::mlir::StringAttr stdService, /*optional*/::mlir::DictionaryAttr impl_opts, ::mlir::ValueRange inputs) {
  return create(builder, builder.getLoc(), std::forward<decltype(outputs)>(outputs), std::forward<decltype(appID)>(appID), std::forward<decltype(service_symbol)>(service_symbol), std::forward<decltype(impl_type)>(impl_type), std::forward<decltype(stdService)>(stdService), std::forward<decltype(impl_opts)>(impl_opts), std::forward<decltype(inputs)>(inputs));
}

void ServiceImplementReqOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  for (unsigned i = 0; i != 1; ++i)
    (void)odsState.addRegion();
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<ServiceImplementReqOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

ServiceImplementReqOp ServiceImplementReqOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<ServiceImplementReqOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ServiceImplementReqOp ServiceImplementReqOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void ServiceImplementReqOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  for (unsigned i = 0; i != 1; ++i)
    (void)odsState.addRegion();
  odsState.addTypes(resultTypes);
}

ServiceImplementReqOp ServiceImplementReqOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<ServiceImplementReqOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ServiceImplementReqOp ServiceImplementReqOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult ServiceImplementReqOp::verifyInvariantsImpl() {
  auto tblgen_appID = getProperties().appID; (void)tblgen_appID;
  if (!tblgen_appID) return emitOpError("requires attribute 'appID'");
  auto tblgen_impl_opts = getProperties().impl_opts; (void)tblgen_impl_opts;
  auto tblgen_impl_type = getProperties().impl_type; (void)tblgen_impl_type;
  if (!tblgen_impl_type) return emitOpError("requires attribute 'impl_type'");
  auto tblgen_service_symbol = getProperties().service_symbol; (void)tblgen_service_symbol;
  auto tblgen_stdService = getProperties().stdService; (void)tblgen_stdService;

  if (::mlir::failed(__mlir_ods_local_attr_constraint_ESI1(*this, tblgen_appID, "appID")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_ESI2(*this, tblgen_service_symbol, "service_symbol")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_ESI3(*this, tblgen_impl_type, "impl_type")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_ESI3(*this, tblgen_stdService, "stdService")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_ESI11(*this, tblgen_impl_opts, "impl_opts")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_ESI7(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_ESI7(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;

    for (auto &region : ::llvm::MutableArrayRef((*this)->getRegion(0)))
      if (::mlir::failed(__mlir_ods_local_region_constraint_ESI1(*this, region, "portReqs", index++)))
        return ::mlir::failure();
  }
  return ::mlir::success();
}

::llvm::LogicalResult ServiceImplementReqOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult ServiceImplementReqOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::circt::esi::AppIDAttr appIDAttr;
  ::mlir::FlatSymbolRefAttr service_symbolAttr;
  ::mlir::StringAttr impl_typeAttr;
  ::mlir::StringAttr stdServiceAttr;
  ::mlir::DictionaryAttr impl_optsAttr;
  ::llvm::SmallVector<::mlir::OpAsmParser::UnresolvedOperand, 4> inputsOperands;
  ::llvm::SMLoc inputsOperandsLoc;
  (void)inputsOperandsLoc;
  ::llvm::ArrayRef<::mlir::Type> inputsTypes;
  ::llvm::ArrayRef<::mlir::Type> allResultTypes;
  std::unique_ptr<::mlir::Region> portReqsRegion = std::make_unique<::mlir::Region>();

  if (parser.parseAttribute(appIDAttr, ::mlir::Type{}))
    return ::mlir::failure();
  if (appIDAttr) result.getOrAddProperties<ServiceImplementReqOp::Properties>().appID = appIDAttr;
  if (::mlir::succeeded(parser.parseOptionalKeyword("svc"))) {

  if (parser.parseCustomAttributeWithFallback(service_symbolAttr, parser.getBuilder().getType<::mlir::NoneType>())) {
    return ::mlir::failure();
  }
  if (service_symbolAttr) result.getOrAddProperties<ServiceImplementReqOp::Properties>().service_symbol = service_symbolAttr;
  }
  if (parser.parseKeyword("impl"))
    return ::mlir::failure();
  if (parser.parseKeyword("as"))
    return ::mlir::failure();

  if (parser.parseCustomAttributeWithFallback(impl_typeAttr, parser.getBuilder().getType<::mlir::NoneType>())) {
    return ::mlir::failure();
  }
  if (impl_typeAttr) result.getOrAddProperties<ServiceImplementReqOp::Properties>().impl_type = impl_typeAttr;
  if (::mlir::succeeded(parser.parseOptionalKeyword("std"))) {

  if (parser.parseCustomAttributeWithFallback(stdServiceAttr, parser.getBuilder().getType<::mlir::NoneType>())) {
    return ::mlir::failure();
  }
  if (stdServiceAttr) result.getOrAddProperties<ServiceImplementReqOp::Properties>().stdService = stdServiceAttr;
  }
  if (::mlir::succeeded(parser.parseOptionalKeyword("opts"))) {

  if (parser.parseCustomAttributeWithFallback(impl_optsAttr, parser.getBuilder().getType<::mlir::NoneType>())) {
    return ::mlir::failure();
  }
  if (impl_optsAttr) result.getOrAddProperties<ServiceImplementReqOp::Properties>().impl_opts = impl_optsAttr;
  }
  if (parser.parseLParen())
    return ::mlir::failure();

  inputsOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperandList(inputsOperands))
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

  ::mlir::FunctionType inputs__allResult_functionType;
  if (parser.parseType(inputs__allResult_functionType))
    return ::mlir::failure();
  inputsTypes = inputs__allResult_functionType.getInputs();
  allResultTypes = inputs__allResult_functionType.getResults();

  if (parser.parseRegion(*portReqsRegion))
    return ::mlir::failure();
  result.addRegion(std::move(portReqsRegion));
  result.addTypes(allResultTypes);
  if (parser.resolveOperands(inputsOperands, inputsTypes, inputsOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void ServiceImplementReqOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter.printAttribute(getAppIDAttr());
  if (getServiceSymbolAttr()) {
    _odsPrinter << ' ' << "svc";
    _odsPrinter << ' ';
    _odsPrinter.printAttributeWithoutType(getServiceSymbolAttr());
  }
  _odsPrinter << ' ' << "impl";
  _odsPrinter << ' ' << "as";
  _odsPrinter << ' ';
  _odsPrinter.printAttributeWithoutType(getImplTypeAttr());
  if (getStdServiceAttr()) {
    _odsPrinter << ' ' << "std";
    _odsPrinter << ' ';
    _odsPrinter.printAttributeWithoutType(getStdServiceAttr());
  }
  if (getImplOptsAttr()) {
    _odsPrinter << ' ' << "opts";
    _odsPrinter << ' ';
    _odsPrinter.printAttributeWithoutType(getImplOptsAttr());
  }
  _odsPrinter << "(";
  _odsPrinter << getInputs();
  _odsPrinter << ")";
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("appID");
  elidedAttrs.push_back("service_symbol");
  elidedAttrs.push_back("impl_type");
  elidedAttrs.push_back("stdService");
  elidedAttrs.push_back("impl_opts");
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
  _odsPrinter.printFunctionalType(getInputs().getTypes(), getOperation()->getResultTypes());
  _odsPrinter << ' ';
  _odsPrinter.printRegion(getPortReqs());
}


} // namespace circt::esi
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::esi::ServiceImplementReqOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::esi::detail::ServiceImplementReqOpGenericAdaptorBase::Properties)

namespace circt::esi {


//===----------------------------------------------------------------------===//
// ::circt::esi::ServiceInstanceOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

ServiceInstanceOpGenericAdaptorBase::ServiceInstanceOpGenericAdaptorBase(ServiceInstanceOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

std::pair<unsigned, unsigned> ServiceInstanceOpGenericAdaptorBase::getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
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

::circt::esi::AppIDAttr ServiceInstanceOpGenericAdaptorBase::getAppID() {
  auto attr = getAppIDAttr();
  return ::llvm::cast<::circt::esi::AppIDAttr>(attr);
}

::std::optional< ::llvm::StringRef > ServiceInstanceOpGenericAdaptorBase::getServiceSymbol() {
  auto attr = getServiceSymbolAttr();
  return attr ? ::std::optional< ::llvm::StringRef >(attr.getValue()) : (::std::nullopt);
}

::llvm::StringRef ServiceInstanceOpGenericAdaptorBase::getImplType() {
  auto attr = getImplTypeAttr();
  return attr.getValue();
}

::std::optional< ::mlir::DictionaryAttr > ServiceInstanceOpGenericAdaptorBase::getImplOpts() {
  auto attr = getImplOptsAttr();
  return attr ? ::std::optional< ::mlir::DictionaryAttr >(attr) : (::std::nullopt);
}


} // namespace detail
ServiceInstanceOpAdaptor::ServiceInstanceOpAdaptor(ServiceInstanceOp op) : ServiceInstanceOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult ServiceInstanceOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_appID = getProperties().appID; (void)tblgen_appID;
  if (!tblgen_appID) return emitError(loc, "'esi.service.instance' op requires attribute 'appID'");
  auto tblgen_impl_opts = getProperties().impl_opts; (void)tblgen_impl_opts;
  auto tblgen_impl_type = getProperties().impl_type; (void)tblgen_impl_type;
  if (!tblgen_impl_type) return emitError(loc, "'esi.service.instance' op requires attribute 'impl_type'");
  auto tblgen_service_symbol = getProperties().service_symbol; (void)tblgen_service_symbol;

  if (tblgen_appID && !((::llvm::isa<::circt::esi::AppIDAttr>(tblgen_appID))))
    return emitError(loc, "'esi.service.instance' op attribute 'appID' failed to satisfy constraint: An application relevant instance identifier");

  if (tblgen_service_symbol && !((::llvm::isa<::mlir::FlatSymbolRefAttr>(tblgen_service_symbol))))
    return emitError(loc, "'esi.service.instance' op attribute 'service_symbol' failed to satisfy constraint: flat symbol reference attribute");

  if (tblgen_impl_type && !((::llvm::isa<::mlir::StringAttr>(tblgen_impl_type))))
    return emitError(loc, "'esi.service.instance' op attribute 'impl_type' failed to satisfy constraint: string attribute");

  if (tblgen_impl_opts && !((::llvm::isa<::mlir::DictionaryAttr>(tblgen_impl_opts))))
    return emitError(loc, "'esi.service.instance' op attribute 'impl_opts' failed to satisfy constraint: dictionary of named attribute values");
  return ::mlir::success();
}

std::pair<unsigned, unsigned> ServiceInstanceOp::getODSOperandIndexAndLength(unsigned index) {
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

::mlir::MutableOperandRange ServiceInstanceOp::getInputsMutable() {
  auto range = getODSOperandIndexAndLength(0);
  auto mutableRange = ::mlir::MutableOperandRange(getOperation(), range.first, range.second);
  return mutableRange;
}

std::pair<unsigned, unsigned> ServiceInstanceOp::getODSResultIndexAndLength(unsigned index) {
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

::llvm::LogicalResult ServiceInstanceOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.appID;
       auto attr = dict.get("appID");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `appID` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.impl_opts;
       auto attr = dict.get("impl_opts");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `impl_opts` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.impl_type;
       auto attr = dict.get("impl_type");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `impl_type` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.service_symbol;
       auto attr = dict.get("service_symbol");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `service_symbol` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  return ::mlir::success();
}

::mlir::Attribute ServiceInstanceOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.appID;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("appID",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.impl_opts;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("impl_opts",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.impl_type;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("impl_type",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.service_symbol;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("service_symbol",
                                       propStorage));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code ServiceInstanceOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.appID.getAsOpaquePointer()), 
    llvm::hash_value(prop.impl_opts.getAsOpaquePointer()), 
    llvm::hash_value(prop.impl_type.getAsOpaquePointer()), 
    llvm::hash_value(prop.service_symbol.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> ServiceInstanceOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "appID")
      return prop.appID;

    if (name == "impl_opts")
      return prop.impl_opts;

    if (name == "impl_type")
      return prop.impl_type;

    if (name == "service_symbol")
      return prop.service_symbol;
  return std::nullopt;
}

void ServiceInstanceOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "appID") {
       prop.appID = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.appID)>>(value);
       return;
    }

    if (name == "impl_opts") {
       prop.impl_opts = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.impl_opts)>>(value);
       return;
    }

    if (name == "impl_type") {
       prop.impl_type = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.impl_type)>>(value);
       return;
    }

    if (name == "service_symbol") {
       prop.service_symbol = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.service_symbol)>>(value);
       return;
    }
}

void ServiceInstanceOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.appID) attrs.append("appID", prop.appID);

    if (prop.impl_opts) attrs.append("impl_opts", prop.impl_opts);

    if (prop.impl_type) attrs.append("impl_type", prop.impl_type);

    if (prop.service_symbol) attrs.append("service_symbol", prop.service_symbol);
}

::llvm::LogicalResult ServiceInstanceOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getAppIDAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_ESI1(attr, "appID", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getImplOptsAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_ESI11(attr, "impl_opts", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getImplTypeAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_ESI3(attr, "impl_type", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getServiceSymbolAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_ESI2(attr, "service_symbol", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult ServiceInstanceOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.appID)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readOptionalAttribute(prop.impl_opts)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readAttribute(prop.impl_type)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readOptionalAttribute(prop.service_symbol)))
    return ::mlir::failure();
  return ::mlir::success();
}

void ServiceInstanceOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.appID);

  writer.writeOptionalAttribute(prop.impl_opts);
  writer.writeAttribute(prop.impl_type);

  writer.writeOptionalAttribute(prop.service_symbol);
}

::circt::esi::AppIDAttr ServiceInstanceOp::getAppID() {
  auto attr = getAppIDAttr();
  return ::llvm::cast<::circt::esi::AppIDAttr>(attr);
}

::std::optional< ::llvm::StringRef > ServiceInstanceOp::getServiceSymbol() {
  auto attr = getServiceSymbolAttr();
  return attr ? ::std::optional< ::llvm::StringRef >(attr.getValue()) : (::std::nullopt);
}

::llvm::StringRef ServiceInstanceOp::getImplType() {
  auto attr = getImplTypeAttr();
  return attr.getValue();
}

::std::optional< ::mlir::DictionaryAttr > ServiceInstanceOp::getImplOpts() {
  auto attr = getImplOptsAttr();
  return attr ? ::std::optional< ::mlir::DictionaryAttr >(attr) : (::std::nullopt);
}

void ServiceInstanceOp::setServiceSymbol(::std::optional<::llvm::StringRef> attrValue) {
    auto &odsProp = getProperties().service_symbol;
    if (attrValue)
      odsProp = ::mlir::SymbolRefAttr::get(::mlir::Builder((*this)->getContext()).getContext(), *attrValue);
    else
      odsProp = nullptr;
}

void ServiceInstanceOp::setImplType(::llvm::StringRef attrValue) {
  getProperties().impl_type = ::mlir::Builder((*this)->getContext()).getStringAttr(attrValue);
}

void ServiceInstanceOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultType0, ::circt::esi::AppIDAttr appID, /*optional*/::mlir::FlatSymbolRefAttr service_symbol, ::mlir::StringAttr impl_type, /*optional*/::mlir::DictionaryAttr impl_opts, ::mlir::ValueRange inputs) {
  odsState.addOperands(inputs);
  odsState.getOrAddProperties<Properties>().appID = appID;
  if (service_symbol) {
    odsState.getOrAddProperties<Properties>().service_symbol = service_symbol;
  }
  odsState.getOrAddProperties<Properties>().impl_type = impl_type;
  if (impl_opts) {
    odsState.getOrAddProperties<Properties>().impl_opts = impl_opts;
  }
  odsState.addTypes(resultType0);
}

ServiceInstanceOp ServiceInstanceOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultType0, ::circt::esi::AppIDAttr appID, /*optional*/::mlir::FlatSymbolRefAttr service_symbol, ::mlir::StringAttr impl_type, /*optional*/::mlir::DictionaryAttr impl_opts, ::mlir::ValueRange inputs) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultType0)>(resultType0), std::forward<decltype(appID)>(appID), std::forward<decltype(service_symbol)>(service_symbol), std::forward<decltype(impl_type)>(impl_type), std::forward<decltype(impl_opts)>(impl_opts), std::forward<decltype(inputs)>(inputs));
  auto __res__ = ::llvm::dyn_cast<ServiceInstanceOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ServiceInstanceOp ServiceInstanceOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultType0, ::circt::esi::AppIDAttr appID, /*optional*/::mlir::FlatSymbolRefAttr service_symbol, ::mlir::StringAttr impl_type, /*optional*/::mlir::DictionaryAttr impl_opts, ::mlir::ValueRange inputs) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultType0)>(resultType0), std::forward<decltype(appID)>(appID), std::forward<decltype(service_symbol)>(service_symbol), std::forward<decltype(impl_type)>(impl_type), std::forward<decltype(impl_opts)>(impl_opts), std::forward<decltype(inputs)>(inputs));
}

void ServiceInstanceOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultType0, ::circt::esi::AppIDAttr appID, /*optional*/::mlir::FlatSymbolRefAttr service_symbol, ::llvm::StringRef impl_type, /*optional*/::mlir::DictionaryAttr impl_opts, ::mlir::ValueRange inputs) {
  odsState.addOperands(inputs);
  odsState.getOrAddProperties<Properties>().appID = appID;
  if (service_symbol) {
    odsState.getOrAddProperties<Properties>().service_symbol = service_symbol;
  }
  odsState.getOrAddProperties<Properties>().impl_type = odsBuilder.getStringAttr(impl_type);
  if (impl_opts) {
    odsState.getOrAddProperties<Properties>().impl_opts = impl_opts;
  }
  odsState.addTypes(resultType0);
}

ServiceInstanceOp ServiceInstanceOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultType0, ::circt::esi::AppIDAttr appID, /*optional*/::mlir::FlatSymbolRefAttr service_symbol, ::llvm::StringRef impl_type, /*optional*/::mlir::DictionaryAttr impl_opts, ::mlir::ValueRange inputs) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultType0)>(resultType0), std::forward<decltype(appID)>(appID), std::forward<decltype(service_symbol)>(service_symbol), std::forward<decltype(impl_type)>(impl_type), std::forward<decltype(impl_opts)>(impl_opts), std::forward<decltype(inputs)>(inputs));
  auto __res__ = ::llvm::dyn_cast<ServiceInstanceOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ServiceInstanceOp ServiceInstanceOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultType0, ::circt::esi::AppIDAttr appID, /*optional*/::mlir::FlatSymbolRefAttr service_symbol, ::llvm::StringRef impl_type, /*optional*/::mlir::DictionaryAttr impl_opts, ::mlir::ValueRange inputs) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultType0)>(resultType0), std::forward<decltype(appID)>(appID), std::forward<decltype(service_symbol)>(service_symbol), std::forward<decltype(impl_type)>(impl_type), std::forward<decltype(impl_opts)>(impl_opts), std::forward<decltype(inputs)>(inputs));
}

void ServiceInstanceOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<ServiceInstanceOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

ServiceInstanceOp ServiceInstanceOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<ServiceInstanceOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ServiceInstanceOp ServiceInstanceOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void ServiceInstanceOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  odsState.addTypes(resultTypes);
}

ServiceInstanceOp ServiceInstanceOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<ServiceInstanceOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ServiceInstanceOp ServiceInstanceOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult ServiceInstanceOp::verifyInvariantsImpl() {
  auto tblgen_appID = getProperties().appID; (void)tblgen_appID;
  if (!tblgen_appID) return emitOpError("requires attribute 'appID'");
  auto tblgen_impl_opts = getProperties().impl_opts; (void)tblgen_impl_opts;
  auto tblgen_impl_type = getProperties().impl_type; (void)tblgen_impl_type;
  if (!tblgen_impl_type) return emitOpError("requires attribute 'impl_type'");
  auto tblgen_service_symbol = getProperties().service_symbol; (void)tblgen_service_symbol;

  if (::mlir::failed(__mlir_ods_local_attr_constraint_ESI1(*this, tblgen_appID, "appID")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_ESI2(*this, tblgen_service_symbol, "service_symbol")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_ESI3(*this, tblgen_impl_type, "impl_type")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_ESI11(*this, tblgen_impl_opts, "impl_opts")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_ESI7(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_ESI7(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult ServiceInstanceOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult ServiceInstanceOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::circt::esi::AppIDAttr appIDAttr;
  ::mlir::FlatSymbolRefAttr service_symbolAttr;
  ::mlir::StringAttr impl_typeAttr;
  ::mlir::DictionaryAttr impl_optsAttr;
  ::llvm::SmallVector<::mlir::OpAsmParser::UnresolvedOperand, 4> inputsOperands;
  ::llvm::SMLoc inputsOperandsLoc;
  (void)inputsOperandsLoc;
  ::llvm::ArrayRef<::mlir::Type> inputsTypes;
  ::llvm::ArrayRef<::mlir::Type> allResultTypes;

  if (parser.parseAttribute(appIDAttr, ::mlir::Type{}))
    return ::mlir::failure();
  if (appIDAttr) result.getOrAddProperties<ServiceInstanceOp::Properties>().appID = appIDAttr;
  if (::mlir::succeeded(parser.parseOptionalKeyword("svc"))) {

  if (parser.parseCustomAttributeWithFallback(service_symbolAttr, parser.getBuilder().getType<::mlir::NoneType>())) {
    return ::mlir::failure();
  }
  if (service_symbolAttr) result.getOrAddProperties<ServiceInstanceOp::Properties>().service_symbol = service_symbolAttr;
  }
  if (parser.parseKeyword("impl"))
    return ::mlir::failure();
  if (parser.parseKeyword("as"))
    return ::mlir::failure();

  if (parser.parseCustomAttributeWithFallback(impl_typeAttr, parser.getBuilder().getType<::mlir::NoneType>())) {
    return ::mlir::failure();
  }
  if (impl_typeAttr) result.getOrAddProperties<ServiceInstanceOp::Properties>().impl_type = impl_typeAttr;
  if (::mlir::succeeded(parser.parseOptionalKeyword("opts"))) {

  if (parser.parseCustomAttributeWithFallback(impl_optsAttr, parser.getBuilder().getType<::mlir::NoneType>())) {
    return ::mlir::failure();
  }
  if (impl_optsAttr) result.getOrAddProperties<ServiceInstanceOp::Properties>().impl_opts = impl_optsAttr;
  }
  if (parser.parseLParen())
    return ::mlir::failure();

  inputsOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperandList(inputsOperands))
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

  ::mlir::FunctionType inputs__allResult_functionType;
  if (parser.parseType(inputs__allResult_functionType))
    return ::mlir::failure();
  inputsTypes = inputs__allResult_functionType.getInputs();
  allResultTypes = inputs__allResult_functionType.getResults();
  result.addTypes(allResultTypes);
  if (parser.resolveOperands(inputsOperands, inputsTypes, inputsOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void ServiceInstanceOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter.printAttribute(getAppIDAttr());
  if (getServiceSymbolAttr()) {
    _odsPrinter << ' ' << "svc";
    _odsPrinter << ' ';
    _odsPrinter.printAttributeWithoutType(getServiceSymbolAttr());
  }
  _odsPrinter << ' ' << "impl";
  _odsPrinter << ' ' << "as";
  _odsPrinter << ' ';
  _odsPrinter.printAttributeWithoutType(getImplTypeAttr());
  if (getImplOptsAttr()) {
    _odsPrinter << ' ' << "opts";
    _odsPrinter << ' ';
    _odsPrinter.printAttributeWithoutType(getImplOptsAttr());
  }
  _odsPrinter << "(";
  _odsPrinter << getInputs();
  _odsPrinter << ")";
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("appID");
  elidedAttrs.push_back("service_symbol");
  elidedAttrs.push_back("impl_type");
  elidedAttrs.push_back("impl_opts");
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
  _odsPrinter.printFunctionalType(getInputs().getTypes(), getOperation()->getResultTypes());
}


} // namespace circt::esi
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::esi::ServiceInstanceOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::esi::detail::ServiceInstanceOpGenericAdaptorBase::Properties)

namespace circt::esi {


//===----------------------------------------------------------------------===//
// ::circt::esi::ServiceRequestRecordOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

ServiceRequestRecordOpGenericAdaptorBase::ServiceRequestRecordOpGenericAdaptorBase(ServiceRequestRecordOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::circt::esi::AppIDAttr ServiceRequestRecordOpGenericAdaptorBase::getRequestor() {
  auto attr = getRequestorAttr();
  return ::llvm::cast<::circt::esi::AppIDAttr>(attr);
}

::circt::hw::InnerRefAttr ServiceRequestRecordOpGenericAdaptorBase::getServicePort() {
  auto attr = getServicePortAttr();
  return ::llvm::cast<::circt::hw::InnerRefAttr>(attr);
}

::std::optional< ::llvm::StringRef > ServiceRequestRecordOpGenericAdaptorBase::getStdService() {
  auto attr = getStdServiceAttr();
  return attr ? ::std::optional< ::llvm::StringRef >(attr.getValue()) : (::std::nullopt);
}

::circt::esi::ChannelBundleType ServiceRequestRecordOpGenericAdaptorBase::getTypeID() {
  auto attr = getTypeIDAttr();
  return ::llvm::cast<::circt::esi::ChannelBundleType>(attr.getValue());
}


} // namespace detail
ServiceRequestRecordOpAdaptor::ServiceRequestRecordOpAdaptor(ServiceRequestRecordOp op) : ServiceRequestRecordOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult ServiceRequestRecordOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_requestor = getProperties().requestor; (void)tblgen_requestor;
  if (!tblgen_requestor) return emitError(loc, "'esi.manifest.req' op requires attribute 'requestor'");
  auto tblgen_servicePort = getProperties().servicePort; (void)tblgen_servicePort;
  if (!tblgen_servicePort) return emitError(loc, "'esi.manifest.req' op requires attribute 'servicePort'");
  auto tblgen_stdService = getProperties().stdService; (void)tblgen_stdService;
  auto tblgen_typeID = getProperties().typeID; (void)tblgen_typeID;
  if (!tblgen_typeID) return emitError(loc, "'esi.manifest.req' op requires attribute 'typeID'");

  if (tblgen_requestor && !((::llvm::isa<::circt::esi::AppIDAttr>(tblgen_requestor))))
    return emitError(loc, "'esi.manifest.req' op attribute 'requestor' failed to satisfy constraint: An application relevant instance identifier");

  if (tblgen_servicePort && !((::llvm::isa<::circt::hw::InnerRefAttr>(tblgen_servicePort))))
    return emitError(loc, "'esi.manifest.req' op attribute 'servicePort' failed to satisfy constraint: Refer to a name inside a module");

  if (tblgen_stdService && !((::llvm::isa<::mlir::StringAttr>(tblgen_stdService))))
    return emitError(loc, "'esi.manifest.req' op attribute 'stdService' failed to satisfy constraint: string attribute");

  if (tblgen_typeID && !(((::llvm::isa<::mlir::TypeAttr>(tblgen_typeID))) && ((::llvm::isa<::circt::esi::ChannelBundleType>(::llvm::cast<::mlir::TypeAttr>(tblgen_typeID).getValue()))) && ((::llvm::isa<::circt::esi::ChannelBundleType>(::llvm::cast<::mlir::TypeAttr>(tblgen_typeID).getValue())))))
    return emitError(loc, "'esi.manifest.req' op attribute 'typeID' failed to satisfy constraint: type attribute of a bundle of channels");
  return ::mlir::success();
}

::llvm::LogicalResult ServiceRequestRecordOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.requestor;
       auto attr = dict.get("requestor");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `requestor` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.servicePort;
       auto attr = dict.get("servicePort");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `servicePort` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.stdService;
       auto attr = dict.get("stdService");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `stdService` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.typeID;
       auto attr = dict.get("typeID");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `typeID` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  return ::mlir::success();
}

::mlir::Attribute ServiceRequestRecordOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.requestor;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("requestor",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.servicePort;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("servicePort",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.stdService;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("stdService",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.typeID;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("typeID",
                                       propStorage));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code ServiceRequestRecordOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.requestor.getAsOpaquePointer()), 
    llvm::hash_value(prop.servicePort.getAsOpaquePointer()), 
    llvm::hash_value(prop.stdService.getAsOpaquePointer()), 
    llvm::hash_value(prop.typeID.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> ServiceRequestRecordOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "requestor")
      return prop.requestor;

    if (name == "servicePort")
      return prop.servicePort;

    if (name == "stdService")
      return prop.stdService;

    if (name == "typeID")
      return prop.typeID;
  return std::nullopt;
}

void ServiceRequestRecordOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "requestor") {
       prop.requestor = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.requestor)>>(value);
       return;
    }

    if (name == "servicePort") {
       prop.servicePort = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.servicePort)>>(value);
       return;
    }

    if (name == "stdService") {
       prop.stdService = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.stdService)>>(value);
       return;
    }

    if (name == "typeID") {
       prop.typeID = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.typeID)>>(value);
       return;
    }
}

void ServiceRequestRecordOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.requestor) attrs.append("requestor", prop.requestor);

    if (prop.servicePort) attrs.append("servicePort", prop.servicePort);

    if (prop.stdService) attrs.append("stdService", prop.stdService);

    if (prop.typeID) attrs.append("typeID", prop.typeID);
}

::llvm::LogicalResult ServiceRequestRecordOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getRequestorAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_ESI1(attr, "requestor", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getServicePortAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_ESI8(attr, "servicePort", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getStdServiceAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_ESI3(attr, "stdService", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getTypeIDAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_ESI9(attr, "typeID", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult ServiceRequestRecordOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.requestor)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readAttribute(prop.servicePort)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readOptionalAttribute(prop.stdService)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readAttribute(prop.typeID)))
    return ::mlir::failure();
  return ::mlir::success();
}

void ServiceRequestRecordOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.requestor);
  writer.writeAttribute(prop.servicePort);

  writer.writeOptionalAttribute(prop.stdService);
  writer.writeAttribute(prop.typeID);
}

::circt::esi::AppIDAttr ServiceRequestRecordOp::getRequestor() {
  auto attr = getRequestorAttr();
  return ::llvm::cast<::circt::esi::AppIDAttr>(attr);
}

::circt::hw::InnerRefAttr ServiceRequestRecordOp::getServicePort() {
  auto attr = getServicePortAttr();
  return ::llvm::cast<::circt::hw::InnerRefAttr>(attr);
}

::std::optional< ::llvm::StringRef > ServiceRequestRecordOp::getStdService() {
  auto attr = getStdServiceAttr();
  return attr ? ::std::optional< ::llvm::StringRef >(attr.getValue()) : (::std::nullopt);
}

::circt::esi::ChannelBundleType ServiceRequestRecordOp::getTypeID() {
  auto attr = getTypeIDAttr();
  return ::llvm::cast<::circt::esi::ChannelBundleType>(attr.getValue());
}

void ServiceRequestRecordOp::setStdService(::std::optional<::llvm::StringRef> attrValue) {
    auto &odsProp = getProperties().stdService;
    if (attrValue)
      odsProp = ::mlir::Builder((*this)->getContext()).getStringAttr(*attrValue);
    else
      odsProp = nullptr;
}

void ServiceRequestRecordOp::setTypeID(::circt::esi::ChannelBundleType attrValue) {
  getProperties().typeID = ::mlir::TypeAttr::get(attrValue);
}

void ServiceRequestRecordOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::circt::esi::AppIDAttr requestor, ::circt::hw::InnerRefAttr servicePort, /*optional*/::mlir::StringAttr stdService, ::mlir::TypeAttr typeID) {
  odsState.getOrAddProperties<Properties>().requestor = requestor;
  odsState.getOrAddProperties<Properties>().servicePort = servicePort;
  if (stdService) {
    odsState.getOrAddProperties<Properties>().stdService = stdService;
  }
  odsState.getOrAddProperties<Properties>().typeID = typeID;
}

ServiceRequestRecordOp ServiceRequestRecordOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::circt::esi::AppIDAttr requestor, ::circt::hw::InnerRefAttr servicePort, /*optional*/::mlir::StringAttr stdService, ::mlir::TypeAttr typeID) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(requestor)>(requestor), std::forward<decltype(servicePort)>(servicePort), std::forward<decltype(stdService)>(stdService), std::forward<decltype(typeID)>(typeID));
  auto __res__ = ::llvm::dyn_cast<ServiceRequestRecordOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ServiceRequestRecordOp ServiceRequestRecordOp::create(::mlir::ImplicitLocOpBuilder &builder, ::circt::esi::AppIDAttr requestor, ::circt::hw::InnerRefAttr servicePort, /*optional*/::mlir::StringAttr stdService, ::mlir::TypeAttr typeID) {
  return create(builder, builder.getLoc(), std::forward<decltype(requestor)>(requestor), std::forward<decltype(servicePort)>(servicePort), std::forward<decltype(stdService)>(stdService), std::forward<decltype(typeID)>(typeID));
}

void ServiceRequestRecordOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::circt::esi::AppIDAttr requestor, ::circt::hw::InnerRefAttr servicePort, /*optional*/::mlir::StringAttr stdService, ::mlir::TypeAttr typeID) {
  odsState.getOrAddProperties<Properties>().requestor = requestor;
  odsState.getOrAddProperties<Properties>().servicePort = servicePort;
  if (stdService) {
    odsState.getOrAddProperties<Properties>().stdService = stdService;
  }
  odsState.getOrAddProperties<Properties>().typeID = typeID;
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

ServiceRequestRecordOp ServiceRequestRecordOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::circt::esi::AppIDAttr requestor, ::circt::hw::InnerRefAttr servicePort, /*optional*/::mlir::StringAttr stdService, ::mlir::TypeAttr typeID) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(requestor)>(requestor), std::forward<decltype(servicePort)>(servicePort), std::forward<decltype(stdService)>(stdService), std::forward<decltype(typeID)>(typeID));
  auto __res__ = ::llvm::dyn_cast<ServiceRequestRecordOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ServiceRequestRecordOp ServiceRequestRecordOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::circt::esi::AppIDAttr requestor, ::circt::hw::InnerRefAttr servicePort, /*optional*/::mlir::StringAttr stdService, ::mlir::TypeAttr typeID) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(requestor)>(requestor), std::forward<decltype(servicePort)>(servicePort), std::forward<decltype(stdService)>(stdService), std::forward<decltype(typeID)>(typeID));
}

void ServiceRequestRecordOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::circt::esi::AppIDAttr requestor, ::circt::hw::InnerRefAttr servicePort, /*optional*/::mlir::StringAttr stdService, ::circt::esi::ChannelBundleType typeID) {
  odsState.getOrAddProperties<Properties>().requestor = requestor;
  odsState.getOrAddProperties<Properties>().servicePort = servicePort;
  if (stdService) {
    odsState.getOrAddProperties<Properties>().stdService = stdService;
  }
  odsState.getOrAddProperties<Properties>().typeID = ::mlir::TypeAttr::get(typeID);
}

ServiceRequestRecordOp ServiceRequestRecordOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::circt::esi::AppIDAttr requestor, ::circt::hw::InnerRefAttr servicePort, /*optional*/::mlir::StringAttr stdService, ::circt::esi::ChannelBundleType typeID) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(requestor)>(requestor), std::forward<decltype(servicePort)>(servicePort), std::forward<decltype(stdService)>(stdService), std::forward<decltype(typeID)>(typeID));
  auto __res__ = ::llvm::dyn_cast<ServiceRequestRecordOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ServiceRequestRecordOp ServiceRequestRecordOp::create(::mlir::ImplicitLocOpBuilder &builder, ::circt::esi::AppIDAttr requestor, ::circt::hw::InnerRefAttr servicePort, /*optional*/::mlir::StringAttr stdService, ::circt::esi::ChannelBundleType typeID) {
  return create(builder, builder.getLoc(), std::forward<decltype(requestor)>(requestor), std::forward<decltype(servicePort)>(servicePort), std::forward<decltype(stdService)>(stdService), std::forward<decltype(typeID)>(typeID));
}

void ServiceRequestRecordOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::circt::esi::AppIDAttr requestor, ::circt::hw::InnerRefAttr servicePort, /*optional*/::mlir::StringAttr stdService, ::circt::esi::ChannelBundleType typeID) {
  odsState.getOrAddProperties<Properties>().requestor = requestor;
  odsState.getOrAddProperties<Properties>().servicePort = servicePort;
  if (stdService) {
    odsState.getOrAddProperties<Properties>().stdService = stdService;
  }
  odsState.getOrAddProperties<Properties>().typeID = ::mlir::TypeAttr::get(typeID);
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

ServiceRequestRecordOp ServiceRequestRecordOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::circt::esi::AppIDAttr requestor, ::circt::hw::InnerRefAttr servicePort, /*optional*/::mlir::StringAttr stdService, ::circt::esi::ChannelBundleType typeID) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(requestor)>(requestor), std::forward<decltype(servicePort)>(servicePort), std::forward<decltype(stdService)>(stdService), std::forward<decltype(typeID)>(typeID));
  auto __res__ = ::llvm::dyn_cast<ServiceRequestRecordOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ServiceRequestRecordOp ServiceRequestRecordOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::circt::esi::AppIDAttr requestor, ::circt::hw::InnerRefAttr servicePort, /*optional*/::mlir::StringAttr stdService, ::circt::esi::ChannelBundleType typeID) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(requestor)>(requestor), std::forward<decltype(servicePort)>(servicePort), std::forward<decltype(stdService)>(stdService), std::forward<decltype(typeID)>(typeID));
}

void ServiceRequestRecordOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<ServiceRequestRecordOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

ServiceRequestRecordOp ServiceRequestRecordOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<ServiceRequestRecordOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ServiceRequestRecordOp ServiceRequestRecordOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void ServiceRequestRecordOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

ServiceRequestRecordOp ServiceRequestRecordOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<ServiceRequestRecordOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ServiceRequestRecordOp ServiceRequestRecordOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult ServiceRequestRecordOp::verifyInvariantsImpl() {
  auto tblgen_requestor = getProperties().requestor; (void)tblgen_requestor;
  if (!tblgen_requestor) return emitOpError("requires attribute 'requestor'");
  auto tblgen_servicePort = getProperties().servicePort; (void)tblgen_servicePort;
  if (!tblgen_servicePort) return emitOpError("requires attribute 'servicePort'");
  auto tblgen_stdService = getProperties().stdService; (void)tblgen_stdService;
  auto tblgen_typeID = getProperties().typeID; (void)tblgen_typeID;
  if (!tblgen_typeID) return emitOpError("requires attribute 'typeID'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_ESI1(*this, tblgen_requestor, "requestor")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_ESI8(*this, tblgen_servicePort, "servicePort")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_ESI3(*this, tblgen_stdService, "stdService")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_ESI9(*this, tblgen_typeID, "typeID")))
    return ::mlir::failure();
  return ::mlir::success();
}

::llvm::LogicalResult ServiceRequestRecordOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult ServiceRequestRecordOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::circt::esi::AppIDAttr requestorAttr;
  ::circt::hw::InnerRefAttr servicePortAttr;
  ::mlir::StringAttr stdServiceAttr;
  ::mlir::TypeAttr typeIDAttr;

  if (parser.parseAttribute(requestorAttr, ::mlir::Type{}))
    return ::mlir::failure();
  if (requestorAttr) result.getOrAddProperties<ServiceRequestRecordOp::Properties>().requestor = requestorAttr;
  if (parser.parseComma())
    return ::mlir::failure();

  if (parser.parseCustomAttributeWithFallback(servicePortAttr, ::mlir::Type{})) {
    return ::mlir::failure();
  }
  if (servicePortAttr) result.getOrAddProperties<ServiceRequestRecordOp::Properties>().servicePort = servicePortAttr;
  if (::mlir::succeeded(parser.parseOptionalKeyword("std"))) {

  if (parser.parseCustomAttributeWithFallback(stdServiceAttr, parser.getBuilder().getType<::mlir::NoneType>())) {
    return ::mlir::failure();
  }
  if (stdServiceAttr) result.getOrAddProperties<ServiceRequestRecordOp::Properties>().stdService = stdServiceAttr;
  }
  if (parser.parseComma())
    return ::mlir::failure();

  if (parser.parseCustomAttributeWithFallback(typeIDAttr, parser.getBuilder().getType<::mlir::NoneType>())) {
    return ::mlir::failure();
  }
  if (typeIDAttr) result.getOrAddProperties<ServiceRequestRecordOp::Properties>().typeID = typeIDAttr;
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

void ServiceRequestRecordOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter.printAttribute(getRequestorAttr());
  _odsPrinter << ",";
  _odsPrinter << ' ';
_odsPrinter.printStrippedAttrOrType(getServicePortAttr());
  if (getStdServiceAttr()) {
    _odsPrinter << ' ' << "std";
    _odsPrinter << ' ';
    _odsPrinter.printAttributeWithoutType(getStdServiceAttr());
  }
  _odsPrinter << ",";
  _odsPrinter << ' ';
  _odsPrinter.printAttributeWithoutType(getTypeIDAttr());
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("requestor");
  elidedAttrs.push_back("servicePort");
  elidedAttrs.push_back("stdService");
  elidedAttrs.push_back("typeID");
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
}


} // namespace circt::esi
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::esi::ServiceRequestRecordOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::esi::detail::ServiceRequestRecordOpGenericAdaptorBase::Properties)

namespace circt::esi {


//===----------------------------------------------------------------------===//
// ::circt::esi::SnoopTransactionOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

SnoopTransactionOpGenericAdaptorBase::SnoopTransactionOpGenericAdaptorBase(SnoopTransactionOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}


} // namespace detail
SnoopTransactionOpAdaptor::SnoopTransactionOpAdaptor(SnoopTransactionOp op) : SnoopTransactionOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult SnoopTransactionOpAdaptor::verify(::mlir::Location loc) {
  return ::mlir::success();
}

void SnoopTransactionOp::getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn) {
  auto resultGroup0 = getODSResults(0);
  if (!resultGroup0.empty())
    setNameFn(*resultGroup0.begin(), "transaction");
  auto resultGroup1 = getODSResults(1);
  if (!resultGroup1.empty())
    setNameFn(*resultGroup1.begin(), "data");
}

::llvm::LogicalResult SnoopTransactionOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }
      return ::mlir::success();
}

::mlir::Attribute SnoopTransactionOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code SnoopTransactionOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine();
}

std::optional<mlir::Attribute> SnoopTransactionOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
  return std::nullopt;
}

void SnoopTransactionOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
}

void SnoopTransactionOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
}

::llvm::LogicalResult SnoopTransactionOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    return ::mlir::success();
}

void SnoopTransactionOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type transaction, ::mlir::Type data, ::mlir::Value input) {
  odsState.addOperands(input);
  odsState.addTypes(transaction);
  odsState.addTypes(data);
}

SnoopTransactionOp SnoopTransactionOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type transaction, ::mlir::Type data, ::mlir::Value input) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(transaction)>(transaction), std::forward<decltype(data)>(data), std::forward<decltype(input)>(input));
  auto __res__ = ::llvm::dyn_cast<SnoopTransactionOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SnoopTransactionOp SnoopTransactionOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type transaction, ::mlir::Type data, ::mlir::Value input) {
  return create(builder, builder.getLoc(), std::forward<decltype(transaction)>(transaction), std::forward<decltype(data)>(data), std::forward<decltype(input)>(input));
}

void SnoopTransactionOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value input) {
  odsState.addOperands(input);

        ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
        if (::mlir::succeeded(SnoopTransactionOp::inferReturnTypes(odsBuilder.getContext(),
                      odsState.location, odsState.operands,
                      odsState.attributes.getDictionary(odsState.getContext()),
                      odsState.getRawProperties(),
                      odsState.regions, inferredReturnTypes)))
          odsState.addTypes(inferredReturnTypes);
        else
          ::mlir::detail::reportFatalInferReturnTypesError(odsState);
        
}

SnoopTransactionOp SnoopTransactionOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value input) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(input)>(input));
  auto __res__ = ::llvm::dyn_cast<SnoopTransactionOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SnoopTransactionOp SnoopTransactionOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value input) {
  return create(builder, builder.getLoc(), std::forward<decltype(input)>(input));
}

void SnoopTransactionOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value input) {
  odsState.addOperands(input);
  assert(resultTypes.size() == 2u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

SnoopTransactionOp SnoopTransactionOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value input) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(input)>(input));
  auto __res__ = ::llvm::dyn_cast<SnoopTransactionOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SnoopTransactionOp SnoopTransactionOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value input) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(input)>(input));
}

void SnoopTransactionOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 2u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

SnoopTransactionOp SnoopTransactionOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<SnoopTransactionOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SnoopTransactionOp SnoopTransactionOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void SnoopTransactionOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);

  ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
  if (::mlir::succeeded(SnoopTransactionOp::inferReturnTypes(odsBuilder.getContext(),
          odsState.location, operands,
          odsState.attributes.getDictionary(odsState.getContext()),
          odsState.getRawProperties(),
          odsState.regions, inferredReturnTypes))) {
    assert(inferredReturnTypes.size() == 2u && "mismatched number of return types");
    odsState.addTypes(inferredReturnTypes);
  } else {
    ::llvm::report_fatal_error("Failed to infer result type(s).");
  }
}

SnoopTransactionOp SnoopTransactionOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<SnoopTransactionOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SnoopTransactionOp SnoopTransactionOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void SnoopTransactionOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 2u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

SnoopTransactionOp SnoopTransactionOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<SnoopTransactionOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SnoopTransactionOp SnoopTransactionOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

void SnoopTransactionOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties &>(properties));
  odsState.addAttributes(discardableAttributes);

  ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
  if (::mlir::succeeded(SnoopTransactionOp::inferReturnTypes(odsBuilder.getContext(),
          odsState.location, operands,
          odsState.attributes.getDictionary(odsState.getContext()),
          odsState.getRawProperties(),
          odsState.regions, inferredReturnTypes))) {
    assert(inferredReturnTypes.size() == 2u && "mismatched number of return types");
    odsState.addTypes(inferredReturnTypes);
  } else {
    ::llvm::report_fatal_error("Failed to infer result type(s).");
  }
}

SnoopTransactionOp SnoopTransactionOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<SnoopTransactionOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SnoopTransactionOp SnoopTransactionOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult SnoopTransactionOp::verifyInvariantsImpl() {
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_ESI3(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_ESI2(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSResults(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_ESI4(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult SnoopTransactionOp::verifyInvariants() {
  if(::mlir::succeeded(verifyInvariantsImpl()) && ::mlir::succeeded(verify()))
    return ::mlir::success();
  return ::mlir::failure();
}

::mlir::ParseResult SnoopTransactionOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
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
  if (::mlir::failed(SnoopTransactionOp::inferReturnTypes(parser.getContext(),
      result.location, result.operands,
      result.attributes.getDictionary(parser.getContext()),
      result.getRawProperties(),
      result.regions, inferredReturnTypes)))
    return ::mlir::failure();
  result.addTypes(inferredReturnTypes);
  return ::mlir::success();
}

void SnoopTransactionOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter << getInput();
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
   _odsPrinter << getInput().getType();
}


} // namespace circt::esi
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::esi::SnoopTransactionOp)

namespace circt::esi {


//===----------------------------------------------------------------------===//
// ::circt::esi::SnoopValidReadyOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

SnoopValidReadyOpGenericAdaptorBase::SnoopValidReadyOpGenericAdaptorBase(SnoopValidReadyOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}


} // namespace detail
SnoopValidReadyOpAdaptor::SnoopValidReadyOpAdaptor(SnoopValidReadyOp op) : SnoopValidReadyOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult SnoopValidReadyOpAdaptor::verify(::mlir::Location loc) {
  return ::mlir::success();
}

void SnoopValidReadyOp::getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn) {
  auto resultGroup0 = getODSResults(0);
  if (!resultGroup0.empty())
    setNameFn(*resultGroup0.begin(), "valid");
  auto resultGroup1 = getODSResults(1);
  if (!resultGroup1.empty())
    setNameFn(*resultGroup1.begin(), "ready");
  auto resultGroup2 = getODSResults(2);
  if (!resultGroup2.empty())
    setNameFn(*resultGroup2.begin(), "data");
}

::llvm::LogicalResult SnoopValidReadyOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }
      return ::mlir::success();
}

::mlir::Attribute SnoopValidReadyOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code SnoopValidReadyOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine();
}

std::optional<mlir::Attribute> SnoopValidReadyOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
  return std::nullopt;
}

void SnoopValidReadyOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
}

void SnoopValidReadyOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
}

::llvm::LogicalResult SnoopValidReadyOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    return ::mlir::success();
}

void SnoopValidReadyOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type valid, ::mlir::Type ready, ::mlir::Type data, ::mlir::Value input) {
  odsState.addOperands(input);
  odsState.addTypes(valid);
  odsState.addTypes(ready);
  odsState.addTypes(data);
}

SnoopValidReadyOp SnoopValidReadyOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type valid, ::mlir::Type ready, ::mlir::Type data, ::mlir::Value input) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(valid)>(valid), std::forward<decltype(ready)>(ready), std::forward<decltype(data)>(data), std::forward<decltype(input)>(input));
  auto __res__ = ::llvm::dyn_cast<SnoopValidReadyOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SnoopValidReadyOp SnoopValidReadyOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type valid, ::mlir::Type ready, ::mlir::Type data, ::mlir::Value input) {
  return create(builder, builder.getLoc(), std::forward<decltype(valid)>(valid), std::forward<decltype(ready)>(ready), std::forward<decltype(data)>(data), std::forward<decltype(input)>(input));
}

void SnoopValidReadyOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value input) {
  odsState.addOperands(input);

        ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
        if (::mlir::succeeded(SnoopValidReadyOp::inferReturnTypes(odsBuilder.getContext(),
                      odsState.location, odsState.operands,
                      odsState.attributes.getDictionary(odsState.getContext()),
                      odsState.getRawProperties(),
                      odsState.regions, inferredReturnTypes)))
          odsState.addTypes(inferredReturnTypes);
        else
          ::mlir::detail::reportFatalInferReturnTypesError(odsState);
        
}

SnoopValidReadyOp SnoopValidReadyOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value input) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(input)>(input));
  auto __res__ = ::llvm::dyn_cast<SnoopValidReadyOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SnoopValidReadyOp SnoopValidReadyOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value input) {
  return create(builder, builder.getLoc(), std::forward<decltype(input)>(input));
}

void SnoopValidReadyOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value input) {
  odsState.addOperands(input);
  assert(resultTypes.size() == 3u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

SnoopValidReadyOp SnoopValidReadyOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value input) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(input)>(input));
  auto __res__ = ::llvm::dyn_cast<SnoopValidReadyOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SnoopValidReadyOp SnoopValidReadyOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value input) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(input)>(input));
}

void SnoopValidReadyOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 3u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

SnoopValidReadyOp SnoopValidReadyOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<SnoopValidReadyOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SnoopValidReadyOp SnoopValidReadyOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void SnoopValidReadyOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);

  ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
  if (::mlir::succeeded(SnoopValidReadyOp::inferReturnTypes(odsBuilder.getContext(),
          odsState.location, operands,
          odsState.attributes.getDictionary(odsState.getContext()),
          odsState.getRawProperties(),
          odsState.regions, inferredReturnTypes))) {
    assert(inferredReturnTypes.size() == 3u && "mismatched number of return types");
    odsState.addTypes(inferredReturnTypes);
  } else {
    ::llvm::report_fatal_error("Failed to infer result type(s).");
  }
}

SnoopValidReadyOp SnoopValidReadyOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<SnoopValidReadyOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SnoopValidReadyOp SnoopValidReadyOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void SnoopValidReadyOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 3u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

SnoopValidReadyOp SnoopValidReadyOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<SnoopValidReadyOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SnoopValidReadyOp SnoopValidReadyOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

void SnoopValidReadyOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties &>(properties));
  odsState.addAttributes(discardableAttributes);

  ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
  if (::mlir::succeeded(SnoopValidReadyOp::inferReturnTypes(odsBuilder.getContext(),
          odsState.location, operands,
          odsState.attributes.getDictionary(odsState.getContext()),
          odsState.getRawProperties(),
          odsState.regions, inferredReturnTypes))) {
    assert(inferredReturnTypes.size() == 3u && "mismatched number of return types");
    odsState.addTypes(inferredReturnTypes);
  } else {
    ::llvm::report_fatal_error("Failed to infer result type(s).");
  }
}

SnoopValidReadyOp SnoopValidReadyOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<SnoopValidReadyOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SnoopValidReadyOp SnoopValidReadyOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult SnoopValidReadyOp::verifyInvariantsImpl() {
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_ESI3(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_ESI2(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSResults(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_ESI2(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup2 = getODSResults(2);

    for (auto v : valueGroup2) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_ESI4(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult SnoopValidReadyOp::verifyInvariants() {
  if(::mlir::succeeded(verifyInvariantsImpl()) && ::mlir::succeeded(verify()))
    return ::mlir::success();
  return ::mlir::failure();
}

::mlir::ParseResult SnoopValidReadyOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
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
  if (::mlir::failed(SnoopValidReadyOp::inferReturnTypes(parser.getContext(),
      result.location, result.operands,
      result.attributes.getDictionary(parser.getContext()),
      result.getRawProperties(),
      result.regions, inferredReturnTypes)))
    return ::mlir::failure();
  result.addTypes(inferredReturnTypes);
  return ::mlir::success();
}

void SnoopValidReadyOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter << getInput();
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
   _odsPrinter << getInput().getType();
}


} // namespace circt::esi
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::esi::SnoopValidReadyOp)

namespace circt::esi {


//===----------------------------------------------------------------------===//
// ::circt::esi::SymbolConstantsOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

SymbolConstantsOpGenericAdaptorBase::SymbolConstantsOpGenericAdaptorBase(SymbolConstantsOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::llvm::StringRef SymbolConstantsOpGenericAdaptorBase::getSymbolRef() {
  auto attr = getSymbolRefAttr();
  return attr.getValue();
}

::mlir::DictionaryAttr SymbolConstantsOpGenericAdaptorBase::getConstants() {
  auto attr = getConstantsAttr();
  return attr;
}


} // namespace detail
SymbolConstantsOpAdaptor::SymbolConstantsOpAdaptor(SymbolConstantsOp op) : SymbolConstantsOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult SymbolConstantsOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_constants = getProperties().constants; (void)tblgen_constants;
  if (!tblgen_constants) return emitError(loc, "'esi.manifest.constants' op requires attribute 'constants'");
  auto tblgen_symbolRef = getProperties().symbolRef; (void)tblgen_symbolRef;
  if (!tblgen_symbolRef) return emitError(loc, "'esi.manifest.constants' op requires attribute 'symbolRef'");

  if (tblgen_symbolRef && !((::llvm::isa<::mlir::FlatSymbolRefAttr>(tblgen_symbolRef))))
    return emitError(loc, "'esi.manifest.constants' op attribute 'symbolRef' failed to satisfy constraint: flat symbol reference attribute");

  if (tblgen_constants && !((::llvm::isa<::mlir::DictionaryAttr>(tblgen_constants))))
    return emitError(loc, "'esi.manifest.constants' op attribute 'constants' failed to satisfy constraint: dictionary of named attribute values");
  return ::mlir::success();
}

::llvm::LogicalResult SymbolConstantsOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.constants;
       auto attr = dict.get("constants");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `constants` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.symbolRef;
       auto attr = dict.get("symbolRef");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `symbolRef` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  return ::mlir::success();
}

::mlir::Attribute SymbolConstantsOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.constants;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("constants",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.symbolRef;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("symbolRef",
                                       propStorage));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code SymbolConstantsOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.constants.getAsOpaquePointer()), 
    llvm::hash_value(prop.symbolRef.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> SymbolConstantsOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "constants")
      return prop.constants;

    if (name == "symbolRef")
      return prop.symbolRef;
  return std::nullopt;
}

void SymbolConstantsOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "constants") {
       prop.constants = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.constants)>>(value);
       return;
    }

    if (name == "symbolRef") {
       prop.symbolRef = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.symbolRef)>>(value);
       return;
    }
}

void SymbolConstantsOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.constants) attrs.append("constants", prop.constants);

    if (prop.symbolRef) attrs.append("symbolRef", prop.symbolRef);
}

::llvm::LogicalResult SymbolConstantsOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getConstantsAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_ESI11(attr, "constants", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getSymbolRefAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_ESI2(attr, "symbolRef", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult SymbolConstantsOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.constants)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readAttribute(prop.symbolRef)))
    return ::mlir::failure();
  return ::mlir::success();
}

void SymbolConstantsOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.constants);
  writer.writeAttribute(prop.symbolRef);
}

::llvm::StringRef SymbolConstantsOp::getSymbolRef() {
  auto attr = getSymbolRefAttr();
  return attr.getValue();
}

::mlir::DictionaryAttr SymbolConstantsOp::getConstants() {
  auto attr = getConstantsAttr();
  return attr;
}

void SymbolConstantsOp::setSymbolRef(::llvm::StringRef attrValue) {
  getProperties().symbolRef = ::mlir::SymbolRefAttr::get(::mlir::Builder((*this)->getContext()).getContext(), attrValue);
}

void SymbolConstantsOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::FlatSymbolRefAttr symbolRef, ::mlir::DictionaryAttr constants) {
  odsState.getOrAddProperties<Properties>().symbolRef = symbolRef;
  odsState.getOrAddProperties<Properties>().constants = constants;
}

SymbolConstantsOp SymbolConstantsOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::FlatSymbolRefAttr symbolRef, ::mlir::DictionaryAttr constants) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(symbolRef)>(symbolRef), std::forward<decltype(constants)>(constants));
  auto __res__ = ::llvm::dyn_cast<SymbolConstantsOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SymbolConstantsOp SymbolConstantsOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::FlatSymbolRefAttr symbolRef, ::mlir::DictionaryAttr constants) {
  return create(builder, builder.getLoc(), std::forward<decltype(symbolRef)>(symbolRef), std::forward<decltype(constants)>(constants));
}

void SymbolConstantsOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::FlatSymbolRefAttr symbolRef, ::mlir::DictionaryAttr constants) {
  odsState.getOrAddProperties<Properties>().symbolRef = symbolRef;
  odsState.getOrAddProperties<Properties>().constants = constants;
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

SymbolConstantsOp SymbolConstantsOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::FlatSymbolRefAttr symbolRef, ::mlir::DictionaryAttr constants) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(symbolRef)>(symbolRef), std::forward<decltype(constants)>(constants));
  auto __res__ = ::llvm::dyn_cast<SymbolConstantsOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SymbolConstantsOp SymbolConstantsOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::FlatSymbolRefAttr symbolRef, ::mlir::DictionaryAttr constants) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(symbolRef)>(symbolRef), std::forward<decltype(constants)>(constants));
}

void SymbolConstantsOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::llvm::StringRef symbolRef, ::mlir::DictionaryAttr constants) {
  odsState.getOrAddProperties<Properties>().symbolRef = ::mlir::SymbolRefAttr::get(odsBuilder.getContext(), symbolRef);
  odsState.getOrAddProperties<Properties>().constants = constants;
}

SymbolConstantsOp SymbolConstantsOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::llvm::StringRef symbolRef, ::mlir::DictionaryAttr constants) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(symbolRef)>(symbolRef), std::forward<decltype(constants)>(constants));
  auto __res__ = ::llvm::dyn_cast<SymbolConstantsOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SymbolConstantsOp SymbolConstantsOp::create(::mlir::ImplicitLocOpBuilder &builder, ::llvm::StringRef symbolRef, ::mlir::DictionaryAttr constants) {
  return create(builder, builder.getLoc(), std::forward<decltype(symbolRef)>(symbolRef), std::forward<decltype(constants)>(constants));
}

void SymbolConstantsOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::llvm::StringRef symbolRef, ::mlir::DictionaryAttr constants) {
  odsState.getOrAddProperties<Properties>().symbolRef = ::mlir::SymbolRefAttr::get(odsBuilder.getContext(), symbolRef);
  odsState.getOrAddProperties<Properties>().constants = constants;
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

SymbolConstantsOp SymbolConstantsOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::llvm::StringRef symbolRef, ::mlir::DictionaryAttr constants) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(symbolRef)>(symbolRef), std::forward<decltype(constants)>(constants));
  auto __res__ = ::llvm::dyn_cast<SymbolConstantsOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SymbolConstantsOp SymbolConstantsOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::llvm::StringRef symbolRef, ::mlir::DictionaryAttr constants) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(symbolRef)>(symbolRef), std::forward<decltype(constants)>(constants));
}

void SymbolConstantsOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<SymbolConstantsOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

SymbolConstantsOp SymbolConstantsOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<SymbolConstantsOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SymbolConstantsOp SymbolConstantsOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void SymbolConstantsOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

SymbolConstantsOp SymbolConstantsOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<SymbolConstantsOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SymbolConstantsOp SymbolConstantsOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult SymbolConstantsOp::verifyInvariantsImpl() {
  auto tblgen_constants = getProperties().constants; (void)tblgen_constants;
  if (!tblgen_constants) return emitOpError("requires attribute 'constants'");
  auto tblgen_symbolRef = getProperties().symbolRef; (void)tblgen_symbolRef;
  if (!tblgen_symbolRef) return emitOpError("requires attribute 'symbolRef'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_ESI2(*this, tblgen_symbolRef, "symbolRef")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_ESI11(*this, tblgen_constants, "constants")))
    return ::mlir::failure();
  return ::mlir::success();
}

::llvm::LogicalResult SymbolConstantsOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult SymbolConstantsOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::FlatSymbolRefAttr symbolRefAttr;
  ::mlir::DictionaryAttr constantsAttr;

  if (parser.parseCustomAttributeWithFallback(symbolRefAttr, parser.getBuilder().getType<::mlir::NoneType>())) {
    return ::mlir::failure();
  }
  if (symbolRefAttr) result.getOrAddProperties<SymbolConstantsOp::Properties>().symbolRef = symbolRefAttr;

  if (parser.parseCustomAttributeWithFallback(constantsAttr, parser.getBuilder().getType<::mlir::NoneType>())) {
    return ::mlir::failure();
  }
  if (constantsAttr) result.getOrAddProperties<SymbolConstantsOp::Properties>().constants = constantsAttr;
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

void SymbolConstantsOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter.printAttributeWithoutType(getSymbolRefAttr());
  _odsPrinter << ' ';
  _odsPrinter.printAttributeWithoutType(getConstantsAttr());
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("symbolRef");
  elidedAttrs.push_back("constants");
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
}


} // namespace circt::esi
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::esi::SymbolConstantsOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::esi::detail::SymbolConstantsOpGenericAdaptorBase::Properties)

namespace circt::esi {


//===----------------------------------------------------------------------===//
// ::circt::esi::SymbolMetadataOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

SymbolMetadataOpGenericAdaptorBase::SymbolMetadataOpGenericAdaptorBase(SymbolMetadataOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::llvm::StringRef SymbolMetadataOpGenericAdaptorBase::getSymbolRef() {
  auto attr = getSymbolRefAttr();
  return attr.getValue();
}

::std::optional< ::llvm::StringRef > SymbolMetadataOpGenericAdaptorBase::getName() {
  auto attr = getNameAttr();
  return attr ? ::std::optional< ::llvm::StringRef >(attr.getValue()) : (::std::nullopt);
}

::std::optional< ::llvm::StringRef > SymbolMetadataOpGenericAdaptorBase::getRepo() {
  auto attr = getRepoAttr();
  return attr ? ::std::optional< ::llvm::StringRef >(attr.getValue()) : (::std::nullopt);
}

::std::optional< ::llvm::StringRef > SymbolMetadataOpGenericAdaptorBase::getCommitHash() {
  auto attr = getCommitHashAttr();
  return attr ? ::std::optional< ::llvm::StringRef >(attr.getValue()) : (::std::nullopt);
}

::std::optional< ::llvm::StringRef > SymbolMetadataOpGenericAdaptorBase::getVersion() {
  auto attr = getVersionAttr();
  return attr ? ::std::optional< ::llvm::StringRef >(attr.getValue()) : (::std::nullopt);
}

::std::optional< ::llvm::StringRef > SymbolMetadataOpGenericAdaptorBase::getSummary() {
  auto attr = getSummaryAttr();
  return attr ? ::std::optional< ::llvm::StringRef >(attr.getValue()) : (::std::nullopt);
}


} // namespace detail
SymbolMetadataOpAdaptor::SymbolMetadataOpAdaptor(SymbolMetadataOp op) : SymbolMetadataOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult SymbolMetadataOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_commitHash = getProperties().commitHash; (void)tblgen_commitHash;
  auto tblgen_name = getProperties().name; (void)tblgen_name;
  auto tblgen_repo = getProperties().repo; (void)tblgen_repo;
  auto tblgen_summary = getProperties().summary; (void)tblgen_summary;
  auto tblgen_symbolRef = getProperties().symbolRef; (void)tblgen_symbolRef;
  if (!tblgen_symbolRef) return emitError(loc, "'esi.manifest.sym' op requires attribute 'symbolRef'");
  auto tblgen_version = getProperties().version; (void)tblgen_version;

  if (tblgen_symbolRef && !((::llvm::isa<::mlir::FlatSymbolRefAttr>(tblgen_symbolRef))))
    return emitError(loc, "'esi.manifest.sym' op attribute 'symbolRef' failed to satisfy constraint: flat symbol reference attribute");

  if (tblgen_name && !((::llvm::isa<::mlir::StringAttr>(tblgen_name))))
    return emitError(loc, "'esi.manifest.sym' op attribute 'name' failed to satisfy constraint: string attribute");

  if (tblgen_repo && !((::llvm::isa<::mlir::StringAttr>(tblgen_repo))))
    return emitError(loc, "'esi.manifest.sym' op attribute 'repo' failed to satisfy constraint: string attribute");

  if (tblgen_commitHash && !((::llvm::isa<::mlir::StringAttr>(tblgen_commitHash))))
    return emitError(loc, "'esi.manifest.sym' op attribute 'commitHash' failed to satisfy constraint: string attribute");

  if (tblgen_version && !((::llvm::isa<::mlir::StringAttr>(tblgen_version))))
    return emitError(loc, "'esi.manifest.sym' op attribute 'version' failed to satisfy constraint: string attribute");

  if (tblgen_summary && !((::llvm::isa<::mlir::StringAttr>(tblgen_summary))))
    return emitError(loc, "'esi.manifest.sym' op attribute 'summary' failed to satisfy constraint: string attribute");
  return ::mlir::success();
}

::llvm::LogicalResult SymbolMetadataOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.commitHash;
       auto attr = dict.get("commitHash");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `commitHash` in property conversion: " << attr;
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
    auto &propStorage = prop.repo;
       auto attr = dict.get("repo");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `repo` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.summary;
       auto attr = dict.get("summary");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `summary` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.symbolRef;
       auto attr = dict.get("symbolRef");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `symbolRef` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.version;
       auto attr = dict.get("version");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `version` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  return ::mlir::success();
}

::mlir::Attribute SymbolMetadataOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.commitHash;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("commitHash",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.name;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("name",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.repo;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("repo",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.summary;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("summary",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.symbolRef;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("symbolRef",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.version;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("version",
                                       propStorage));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code SymbolMetadataOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.commitHash.getAsOpaquePointer()), 
    llvm::hash_value(prop.name.getAsOpaquePointer()), 
    llvm::hash_value(prop.repo.getAsOpaquePointer()), 
    llvm::hash_value(prop.summary.getAsOpaquePointer()), 
    llvm::hash_value(prop.symbolRef.getAsOpaquePointer()), 
    llvm::hash_value(prop.version.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> SymbolMetadataOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "commitHash")
      return prop.commitHash;

    if (name == "name")
      return prop.name;

    if (name == "repo")
      return prop.repo;

    if (name == "summary")
      return prop.summary;

    if (name == "symbolRef")
      return prop.symbolRef;

    if (name == "version")
      return prop.version;
  return std::nullopt;
}

void SymbolMetadataOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "commitHash") {
       prop.commitHash = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.commitHash)>>(value);
       return;
    }

    if (name == "name") {
       prop.name = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.name)>>(value);
       return;
    }

    if (name == "repo") {
       prop.repo = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.repo)>>(value);
       return;
    }

    if (name == "summary") {
       prop.summary = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.summary)>>(value);
       return;
    }

    if (name == "symbolRef") {
       prop.symbolRef = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.symbolRef)>>(value);
       return;
    }

    if (name == "version") {
       prop.version = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.version)>>(value);
       return;
    }
}

void SymbolMetadataOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.commitHash) attrs.append("commitHash", prop.commitHash);

    if (prop.name) attrs.append("name", prop.name);

    if (prop.repo) attrs.append("repo", prop.repo);

    if (prop.summary) attrs.append("summary", prop.summary);

    if (prop.symbolRef) attrs.append("symbolRef", prop.symbolRef);

    if (prop.version) attrs.append("version", prop.version);
}

::llvm::LogicalResult SymbolMetadataOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getCommitHashAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_ESI3(attr, "commitHash", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getNameAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_ESI3(attr, "name", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getRepoAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_ESI3(attr, "repo", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getSummaryAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_ESI3(attr, "summary", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getSymbolRefAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_ESI2(attr, "symbolRef", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getVersionAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_ESI3(attr, "version", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult SymbolMetadataOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readOptionalAttribute(prop.commitHash)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readOptionalAttribute(prop.name)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readOptionalAttribute(prop.repo)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readOptionalAttribute(prop.summary)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readAttribute(prop.symbolRef)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readOptionalAttribute(prop.version)))
    return ::mlir::failure();
  return ::mlir::success();
}

void SymbolMetadataOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;

  writer.writeOptionalAttribute(prop.commitHash);

  writer.writeOptionalAttribute(prop.name);

  writer.writeOptionalAttribute(prop.repo);

  writer.writeOptionalAttribute(prop.summary);
  writer.writeAttribute(prop.symbolRef);

  writer.writeOptionalAttribute(prop.version);
}

::llvm::StringRef SymbolMetadataOp::getSymbolRef() {
  auto attr = getSymbolRefAttr();
  return attr.getValue();
}

::std::optional< ::llvm::StringRef > SymbolMetadataOp::getName() {
  auto attr = getNameAttr();
  return attr ? ::std::optional< ::llvm::StringRef >(attr.getValue()) : (::std::nullopt);
}

::std::optional< ::llvm::StringRef > SymbolMetadataOp::getRepo() {
  auto attr = getRepoAttr();
  return attr ? ::std::optional< ::llvm::StringRef >(attr.getValue()) : (::std::nullopt);
}

::std::optional< ::llvm::StringRef > SymbolMetadataOp::getCommitHash() {
  auto attr = getCommitHashAttr();
  return attr ? ::std::optional< ::llvm::StringRef >(attr.getValue()) : (::std::nullopt);
}

::std::optional< ::llvm::StringRef > SymbolMetadataOp::getVersion() {
  auto attr = getVersionAttr();
  return attr ? ::std::optional< ::llvm::StringRef >(attr.getValue()) : (::std::nullopt);
}

::std::optional< ::llvm::StringRef > SymbolMetadataOp::getSummary() {
  auto attr = getSummaryAttr();
  return attr ? ::std::optional< ::llvm::StringRef >(attr.getValue()) : (::std::nullopt);
}

void SymbolMetadataOp::setSymbolRef(::llvm::StringRef attrValue) {
  getProperties().symbolRef = ::mlir::SymbolRefAttr::get(::mlir::Builder((*this)->getContext()).getContext(), attrValue);
}

void SymbolMetadataOp::setName(::std::optional<::llvm::StringRef> attrValue) {
    auto &odsProp = getProperties().name;
    if (attrValue)
      odsProp = ::mlir::Builder((*this)->getContext()).getStringAttr(*attrValue);
    else
      odsProp = nullptr;
}

void SymbolMetadataOp::setRepo(::std::optional<::llvm::StringRef> attrValue) {
    auto &odsProp = getProperties().repo;
    if (attrValue)
      odsProp = ::mlir::Builder((*this)->getContext()).getStringAttr(*attrValue);
    else
      odsProp = nullptr;
}

void SymbolMetadataOp::setCommitHash(::std::optional<::llvm::StringRef> attrValue) {
    auto &odsProp = getProperties().commitHash;
    if (attrValue)
      odsProp = ::mlir::Builder((*this)->getContext()).getStringAttr(*attrValue);
    else
      odsProp = nullptr;
}

void SymbolMetadataOp::setVersion(::std::optional<::llvm::StringRef> attrValue) {
    auto &odsProp = getProperties().version;
    if (attrValue)
      odsProp = ::mlir::Builder((*this)->getContext()).getStringAttr(*attrValue);
    else
      odsProp = nullptr;
}

void SymbolMetadataOp::setSummary(::std::optional<::llvm::StringRef> attrValue) {
    auto &odsProp = getProperties().summary;
    if (attrValue)
      odsProp = ::mlir::Builder((*this)->getContext()).getStringAttr(*attrValue);
    else
      odsProp = nullptr;
}

void SymbolMetadataOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::FlatSymbolRefAttr symbolRef, /*optional*/::mlir::StringAttr name, /*optional*/::mlir::StringAttr repo, /*optional*/::mlir::StringAttr commitHash, /*optional*/::mlir::StringAttr version, /*optional*/::mlir::StringAttr summary) {
  odsState.getOrAddProperties<Properties>().symbolRef = symbolRef;
  if (name) {
    odsState.getOrAddProperties<Properties>().name = name;
  }
  if (repo) {
    odsState.getOrAddProperties<Properties>().repo = repo;
  }
  if (commitHash) {
    odsState.getOrAddProperties<Properties>().commitHash = commitHash;
  }
  if (version) {
    odsState.getOrAddProperties<Properties>().version = version;
  }
  if (summary) {
    odsState.getOrAddProperties<Properties>().summary = summary;
  }
}

SymbolMetadataOp SymbolMetadataOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::FlatSymbolRefAttr symbolRef, /*optional*/::mlir::StringAttr name, /*optional*/::mlir::StringAttr repo, /*optional*/::mlir::StringAttr commitHash, /*optional*/::mlir::StringAttr version, /*optional*/::mlir::StringAttr summary) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(symbolRef)>(symbolRef), std::forward<decltype(name)>(name), std::forward<decltype(repo)>(repo), std::forward<decltype(commitHash)>(commitHash), std::forward<decltype(version)>(version), std::forward<decltype(summary)>(summary));
  auto __res__ = ::llvm::dyn_cast<SymbolMetadataOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SymbolMetadataOp SymbolMetadataOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::FlatSymbolRefAttr symbolRef, /*optional*/::mlir::StringAttr name, /*optional*/::mlir::StringAttr repo, /*optional*/::mlir::StringAttr commitHash, /*optional*/::mlir::StringAttr version, /*optional*/::mlir::StringAttr summary) {
  return create(builder, builder.getLoc(), std::forward<decltype(symbolRef)>(symbolRef), std::forward<decltype(name)>(name), std::forward<decltype(repo)>(repo), std::forward<decltype(commitHash)>(commitHash), std::forward<decltype(version)>(version), std::forward<decltype(summary)>(summary));
}

void SymbolMetadataOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::FlatSymbolRefAttr symbolRef, /*optional*/::mlir::StringAttr name, /*optional*/::mlir::StringAttr repo, /*optional*/::mlir::StringAttr commitHash, /*optional*/::mlir::StringAttr version, /*optional*/::mlir::StringAttr summary) {
  odsState.getOrAddProperties<Properties>().symbolRef = symbolRef;
  if (name) {
    odsState.getOrAddProperties<Properties>().name = name;
  }
  if (repo) {
    odsState.getOrAddProperties<Properties>().repo = repo;
  }
  if (commitHash) {
    odsState.getOrAddProperties<Properties>().commitHash = commitHash;
  }
  if (version) {
    odsState.getOrAddProperties<Properties>().version = version;
  }
  if (summary) {
    odsState.getOrAddProperties<Properties>().summary = summary;
  }
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

SymbolMetadataOp SymbolMetadataOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::FlatSymbolRefAttr symbolRef, /*optional*/::mlir::StringAttr name, /*optional*/::mlir::StringAttr repo, /*optional*/::mlir::StringAttr commitHash, /*optional*/::mlir::StringAttr version, /*optional*/::mlir::StringAttr summary) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(symbolRef)>(symbolRef), std::forward<decltype(name)>(name), std::forward<decltype(repo)>(repo), std::forward<decltype(commitHash)>(commitHash), std::forward<decltype(version)>(version), std::forward<decltype(summary)>(summary));
  auto __res__ = ::llvm::dyn_cast<SymbolMetadataOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SymbolMetadataOp SymbolMetadataOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::FlatSymbolRefAttr symbolRef, /*optional*/::mlir::StringAttr name, /*optional*/::mlir::StringAttr repo, /*optional*/::mlir::StringAttr commitHash, /*optional*/::mlir::StringAttr version, /*optional*/::mlir::StringAttr summary) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(symbolRef)>(symbolRef), std::forward<decltype(name)>(name), std::forward<decltype(repo)>(repo), std::forward<decltype(commitHash)>(commitHash), std::forward<decltype(version)>(version), std::forward<decltype(summary)>(summary));
}

void SymbolMetadataOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::llvm::StringRef symbolRef, /*optional*/::mlir::StringAttr name, /*optional*/::mlir::StringAttr repo, /*optional*/::mlir::StringAttr commitHash, /*optional*/::mlir::StringAttr version, /*optional*/::mlir::StringAttr summary) {
  odsState.getOrAddProperties<Properties>().symbolRef = ::mlir::SymbolRefAttr::get(odsBuilder.getContext(), symbolRef);
  if (name) {
    odsState.getOrAddProperties<Properties>().name = name;
  }
  if (repo) {
    odsState.getOrAddProperties<Properties>().repo = repo;
  }
  if (commitHash) {
    odsState.getOrAddProperties<Properties>().commitHash = commitHash;
  }
  if (version) {
    odsState.getOrAddProperties<Properties>().version = version;
  }
  if (summary) {
    odsState.getOrAddProperties<Properties>().summary = summary;
  }
}

SymbolMetadataOp SymbolMetadataOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::llvm::StringRef symbolRef, /*optional*/::mlir::StringAttr name, /*optional*/::mlir::StringAttr repo, /*optional*/::mlir::StringAttr commitHash, /*optional*/::mlir::StringAttr version, /*optional*/::mlir::StringAttr summary) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(symbolRef)>(symbolRef), std::forward<decltype(name)>(name), std::forward<decltype(repo)>(repo), std::forward<decltype(commitHash)>(commitHash), std::forward<decltype(version)>(version), std::forward<decltype(summary)>(summary));
  auto __res__ = ::llvm::dyn_cast<SymbolMetadataOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SymbolMetadataOp SymbolMetadataOp::create(::mlir::ImplicitLocOpBuilder &builder, ::llvm::StringRef symbolRef, /*optional*/::mlir::StringAttr name, /*optional*/::mlir::StringAttr repo, /*optional*/::mlir::StringAttr commitHash, /*optional*/::mlir::StringAttr version, /*optional*/::mlir::StringAttr summary) {
  return create(builder, builder.getLoc(), std::forward<decltype(symbolRef)>(symbolRef), std::forward<decltype(name)>(name), std::forward<decltype(repo)>(repo), std::forward<decltype(commitHash)>(commitHash), std::forward<decltype(version)>(version), std::forward<decltype(summary)>(summary));
}

void SymbolMetadataOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::llvm::StringRef symbolRef, /*optional*/::mlir::StringAttr name, /*optional*/::mlir::StringAttr repo, /*optional*/::mlir::StringAttr commitHash, /*optional*/::mlir::StringAttr version, /*optional*/::mlir::StringAttr summary) {
  odsState.getOrAddProperties<Properties>().symbolRef = ::mlir::SymbolRefAttr::get(odsBuilder.getContext(), symbolRef);
  if (name) {
    odsState.getOrAddProperties<Properties>().name = name;
  }
  if (repo) {
    odsState.getOrAddProperties<Properties>().repo = repo;
  }
  if (commitHash) {
    odsState.getOrAddProperties<Properties>().commitHash = commitHash;
  }
  if (version) {
    odsState.getOrAddProperties<Properties>().version = version;
  }
  if (summary) {
    odsState.getOrAddProperties<Properties>().summary = summary;
  }
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

SymbolMetadataOp SymbolMetadataOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::llvm::StringRef symbolRef, /*optional*/::mlir::StringAttr name, /*optional*/::mlir::StringAttr repo, /*optional*/::mlir::StringAttr commitHash, /*optional*/::mlir::StringAttr version, /*optional*/::mlir::StringAttr summary) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(symbolRef)>(symbolRef), std::forward<decltype(name)>(name), std::forward<decltype(repo)>(repo), std::forward<decltype(commitHash)>(commitHash), std::forward<decltype(version)>(version), std::forward<decltype(summary)>(summary));
  auto __res__ = ::llvm::dyn_cast<SymbolMetadataOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SymbolMetadataOp SymbolMetadataOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::llvm::StringRef symbolRef, /*optional*/::mlir::StringAttr name, /*optional*/::mlir::StringAttr repo, /*optional*/::mlir::StringAttr commitHash, /*optional*/::mlir::StringAttr version, /*optional*/::mlir::StringAttr summary) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(symbolRef)>(symbolRef), std::forward<decltype(name)>(name), std::forward<decltype(repo)>(repo), std::forward<decltype(commitHash)>(commitHash), std::forward<decltype(version)>(version), std::forward<decltype(summary)>(summary));
}

void SymbolMetadataOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<SymbolMetadataOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

SymbolMetadataOp SymbolMetadataOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<SymbolMetadataOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SymbolMetadataOp SymbolMetadataOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void SymbolMetadataOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

SymbolMetadataOp SymbolMetadataOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<SymbolMetadataOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SymbolMetadataOp SymbolMetadataOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult SymbolMetadataOp::verifyInvariantsImpl() {
  auto tblgen_commitHash = getProperties().commitHash; (void)tblgen_commitHash;
  auto tblgen_name = getProperties().name; (void)tblgen_name;
  auto tblgen_repo = getProperties().repo; (void)tblgen_repo;
  auto tblgen_summary = getProperties().summary; (void)tblgen_summary;
  auto tblgen_symbolRef = getProperties().symbolRef; (void)tblgen_symbolRef;
  if (!tblgen_symbolRef) return emitOpError("requires attribute 'symbolRef'");
  auto tblgen_version = getProperties().version; (void)tblgen_version;

  if (::mlir::failed(__mlir_ods_local_attr_constraint_ESI2(*this, tblgen_symbolRef, "symbolRef")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_ESI3(*this, tblgen_name, "name")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_ESI3(*this, tblgen_repo, "repo")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_ESI3(*this, tblgen_commitHash, "commitHash")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_ESI3(*this, tblgen_version, "version")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_ESI3(*this, tblgen_summary, "summary")))
    return ::mlir::failure();
  return ::mlir::success();
}

::llvm::LogicalResult SymbolMetadataOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult SymbolMetadataOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::FlatSymbolRefAttr symbolRefAttr;
  ::mlir::StringAttr nameAttr;
  ::mlir::StringAttr repoAttr;
  ::mlir::StringAttr commitHashAttr;
  ::mlir::StringAttr versionAttr;
  ::mlir::StringAttr summaryAttr;

  if (parser.parseCustomAttributeWithFallback(symbolRefAttr, parser.getBuilder().getType<::mlir::NoneType>())) {
    return ::mlir::failure();
  }
  if (symbolRefAttr) result.getOrAddProperties<SymbolMetadataOp::Properties>().symbolRef = symbolRefAttr;
  if (::mlir::succeeded(parser.parseOptionalKeyword("name"))) {

  if (parser.parseCustomAttributeWithFallback(nameAttr, parser.getBuilder().getType<::mlir::NoneType>())) {
    return ::mlir::failure();
  }
  if (nameAttr) result.getOrAddProperties<SymbolMetadataOp::Properties>().name = nameAttr;
  }
  if (::mlir::succeeded(parser.parseOptionalKeyword("repo"))) {

  if (parser.parseCustomAttributeWithFallback(repoAttr, parser.getBuilder().getType<::mlir::NoneType>())) {
    return ::mlir::failure();
  }
  if (repoAttr) result.getOrAddProperties<SymbolMetadataOp::Properties>().repo = repoAttr;
  }
  if (::mlir::succeeded(parser.parseOptionalKeyword("commit"))) {

  if (parser.parseCustomAttributeWithFallback(commitHashAttr, parser.getBuilder().getType<::mlir::NoneType>())) {
    return ::mlir::failure();
  }
  if (commitHashAttr) result.getOrAddProperties<SymbolMetadataOp::Properties>().commitHash = commitHashAttr;
  }
  if (::mlir::succeeded(parser.parseOptionalKeyword("version"))) {

  if (parser.parseCustomAttributeWithFallback(versionAttr, parser.getBuilder().getType<::mlir::NoneType>())) {
    return ::mlir::failure();
  }
  if (versionAttr) result.getOrAddProperties<SymbolMetadataOp::Properties>().version = versionAttr;
  }
  if (::mlir::succeeded(parser.parseOptionalKeyword("summary"))) {

  if (parser.parseCustomAttributeWithFallback(summaryAttr, parser.getBuilder().getType<::mlir::NoneType>())) {
    return ::mlir::failure();
  }
  if (summaryAttr) result.getOrAddProperties<SymbolMetadataOp::Properties>().summary = summaryAttr;
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

void SymbolMetadataOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter.printAttributeWithoutType(getSymbolRefAttr());
  if (getNameAttr()) {
    _odsPrinter << ' ' << "name";
    _odsPrinter << ' ';
    _odsPrinter.printAttributeWithoutType(getNameAttr());
  }
  if (getRepoAttr()) {
    _odsPrinter << ' ' << "repo";
    _odsPrinter << ' ';
    _odsPrinter.printAttributeWithoutType(getRepoAttr());
  }
  if (getCommitHashAttr()) {
    _odsPrinter << ' ' << "commit";
    _odsPrinter << ' ';
    _odsPrinter.printAttributeWithoutType(getCommitHashAttr());
  }
  if (getVersionAttr()) {
    _odsPrinter << ' ' << "version";
    _odsPrinter << ' ';
    _odsPrinter.printAttributeWithoutType(getVersionAttr());
  }
  if (getSummaryAttr()) {
    _odsPrinter << ' ' << "summary";
    _odsPrinter << ' ';
    _odsPrinter.printAttributeWithoutType(getSummaryAttr());
  }
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("symbolRef");
  elidedAttrs.push_back("name");
  elidedAttrs.push_back("repo");
  elidedAttrs.push_back("commitHash");
  elidedAttrs.push_back("version");
  elidedAttrs.push_back("summary");
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
}


} // namespace circt::esi
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::esi::SymbolMetadataOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::esi::detail::SymbolMetadataOpGenericAdaptorBase::Properties)

namespace circt::esi {


//===----------------------------------------------------------------------===//
// ::circt::esi::TelemetryServiceDeclOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

TelemetryServiceDeclOpGenericAdaptorBase::TelemetryServiceDeclOpGenericAdaptorBase(TelemetryServiceDeclOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::llvm::StringRef TelemetryServiceDeclOpGenericAdaptorBase::getSymName() {
  auto attr = getSymNameAttr();
  return attr.getValue();
}


} // namespace detail
TelemetryServiceDeclOpAdaptor::TelemetryServiceDeclOpAdaptor(TelemetryServiceDeclOp op) : TelemetryServiceDeclOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult TelemetryServiceDeclOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;
  if (!tblgen_sym_name) return emitError(loc, "'esi.service.std.telemetry' op requires attribute 'sym_name'");

  if (tblgen_sym_name && !((::llvm::isa<::mlir::StringAttr>(tblgen_sym_name))))
    return emitError(loc, "'esi.service.std.telemetry' op attribute 'sym_name' failed to satisfy constraint: string attribute");
  return ::mlir::success();
}

::llvm::LogicalResult TelemetryServiceDeclOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
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

::mlir::Attribute TelemetryServiceDeclOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
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

llvm::hash_code TelemetryServiceDeclOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.sym_name.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> TelemetryServiceDeclOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "sym_name")
      return prop.sym_name;
  return std::nullopt;
}

void TelemetryServiceDeclOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "sym_name") {
       prop.sym_name = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.sym_name)>>(value);
       return;
    }
}

void TelemetryServiceDeclOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.sym_name) attrs.append("sym_name", prop.sym_name);
}

::llvm::LogicalResult TelemetryServiceDeclOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getSymNameAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_ESI3(attr, "sym_name", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult TelemetryServiceDeclOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.sym_name)))
    return ::mlir::failure();
  return ::mlir::success();
}

void TelemetryServiceDeclOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.sym_name);
}

::llvm::StringRef TelemetryServiceDeclOp::getSymName() {
  auto attr = getSymNameAttr();
  return attr.getValue();
}

void TelemetryServiceDeclOp::setSymName(::llvm::StringRef attrValue) {
  getProperties().sym_name = ::mlir::Builder((*this)->getContext()).getStringAttr(attrValue);
}

void TelemetryServiceDeclOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::StringAttr sym_name) {
  odsState.getOrAddProperties<Properties>().sym_name = sym_name;
}

TelemetryServiceDeclOp TelemetryServiceDeclOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::StringAttr sym_name) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(sym_name)>(sym_name));
  auto __res__ = ::llvm::dyn_cast<TelemetryServiceDeclOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

TelemetryServiceDeclOp TelemetryServiceDeclOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::StringAttr sym_name) {
  return create(builder, builder.getLoc(), std::forward<decltype(sym_name)>(sym_name));
}

void TelemetryServiceDeclOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name) {
  odsState.getOrAddProperties<Properties>().sym_name = sym_name;
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

TelemetryServiceDeclOp TelemetryServiceDeclOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(sym_name)>(sym_name));
  auto __res__ = ::llvm::dyn_cast<TelemetryServiceDeclOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

TelemetryServiceDeclOp TelemetryServiceDeclOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(sym_name)>(sym_name));
}

void TelemetryServiceDeclOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::llvm::StringRef sym_name) {
  odsState.getOrAddProperties<Properties>().sym_name = odsBuilder.getStringAttr(sym_name);
}

TelemetryServiceDeclOp TelemetryServiceDeclOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::llvm::StringRef sym_name) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(sym_name)>(sym_name));
  auto __res__ = ::llvm::dyn_cast<TelemetryServiceDeclOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

TelemetryServiceDeclOp TelemetryServiceDeclOp::create(::mlir::ImplicitLocOpBuilder &builder, ::llvm::StringRef sym_name) {
  return create(builder, builder.getLoc(), std::forward<decltype(sym_name)>(sym_name));
}

void TelemetryServiceDeclOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name) {
  odsState.getOrAddProperties<Properties>().sym_name = odsBuilder.getStringAttr(sym_name);
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

TelemetryServiceDeclOp TelemetryServiceDeclOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(sym_name)>(sym_name));
  auto __res__ = ::llvm::dyn_cast<TelemetryServiceDeclOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

TelemetryServiceDeclOp TelemetryServiceDeclOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(sym_name)>(sym_name));
}

void TelemetryServiceDeclOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<TelemetryServiceDeclOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

TelemetryServiceDeclOp TelemetryServiceDeclOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<TelemetryServiceDeclOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

TelemetryServiceDeclOp TelemetryServiceDeclOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void TelemetryServiceDeclOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

TelemetryServiceDeclOp TelemetryServiceDeclOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<TelemetryServiceDeclOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

TelemetryServiceDeclOp TelemetryServiceDeclOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult TelemetryServiceDeclOp::verifyInvariantsImpl() {
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;
  if (!tblgen_sym_name) return emitOpError("requires attribute 'sym_name'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_ESI3(*this, tblgen_sym_name, "sym_name")))
    return ::mlir::failure();
  return ::mlir::success();
}

::llvm::LogicalResult TelemetryServiceDeclOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult TelemetryServiceDeclOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::StringAttr sym_nameAttr;

  if (parser.parseSymbolName(sym_nameAttr))
    return ::mlir::failure();
  if (sym_nameAttr) result.getOrAddProperties<TelemetryServiceDeclOp::Properties>().sym_name = sym_nameAttr;
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

void TelemetryServiceDeclOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter.printSymbolName(getSymNameAttr().getValue());
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("sym_name");
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
}


} // namespace circt::esi
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::esi::TelemetryServiceDeclOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::esi::detail::TelemetryServiceDeclOpGenericAdaptorBase::Properties)

namespace circt::esi {


//===----------------------------------------------------------------------===//
// ::circt::esi::UnpackBundleOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

UnpackBundleOpGenericAdaptorBase::UnpackBundleOpGenericAdaptorBase(UnpackBundleOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

std::pair<unsigned, unsigned> UnpackBundleOpGenericAdaptorBase::getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
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
UnpackBundleOpAdaptor::UnpackBundleOpAdaptor(UnpackBundleOp op) : UnpackBundleOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult UnpackBundleOpAdaptor::verify(::mlir::Location loc) {
  return ::mlir::success();
}

std::pair<unsigned, unsigned> UnpackBundleOp::getODSOperandIndexAndLength(unsigned index) {
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

::mlir::MutableOperandRange UnpackBundleOp::getFromChannelsMutable() {
  auto range = getODSOperandIndexAndLength(1);
  auto mutableRange = ::mlir::MutableOperandRange(getOperation(), range.first, range.second);
  return mutableRange;
}

std::pair<unsigned, unsigned> UnpackBundleOp::getODSResultIndexAndLength(unsigned index) {
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

::llvm::LogicalResult UnpackBundleOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }
      return ::mlir::success();
}

::mlir::Attribute UnpackBundleOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code UnpackBundleOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine();
}

std::optional<mlir::Attribute> UnpackBundleOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
  return std::nullopt;
}

void UnpackBundleOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
}

void UnpackBundleOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
}

::llvm::LogicalResult UnpackBundleOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    return ::mlir::success();
}

UnpackBundleOp UnpackBundleOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, Value bundle, mlir::ValueRange fromChannels) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(bundle)>(bundle), std::forward<decltype(fromChannels)>(fromChannels));
  auto __res__ = ::llvm::dyn_cast<UnpackBundleOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

UnpackBundleOp UnpackBundleOp::create(::mlir::ImplicitLocOpBuilder &builder, Value bundle, mlir::ValueRange fromChannels) {
  return create(builder, builder.getLoc(), std::forward<decltype(bundle)>(bundle), std::forward<decltype(fromChannels)>(fromChannels));
}

::llvm::LogicalResult UnpackBundleOp::verifyInvariantsImpl() {
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_ESI6(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSOperands(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_ESI5(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_ESI5(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult UnpackBundleOp::verifyInvariants() {
  if(::mlir::succeeded(verifyInvariantsImpl()) && ::mlir::succeeded(verify()))
    return ::mlir::success();
  return ::mlir::failure();
}

void UnpackBundleOp::getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context) {
  results.add(canonicalize);
}

::mlir::ParseResult UnpackBundleOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::llvm::SmallVector<::mlir::OpAsmParser::UnresolvedOperand, 4> fromChannelsOperands;
  ::llvm::SMLoc fromChannelsOperandsLoc;
  (void)fromChannelsOperandsLoc;
  ::mlir::OpAsmParser::UnresolvedOperand bundleRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> bundleOperands(&bundleRawOperand, 1);  ::llvm::SMLoc bundleOperandsLoc;
  (void)bundleOperandsLoc;
  ::llvm::SmallVector<::mlir::Type, 1> toChannelsTypes;
  ::llvm::SmallVector<::mlir::Type, 1> fromChannelsTypes;
  ::mlir::Type bundleRawType{};
  ::llvm::ArrayRef<::mlir::Type> bundleTypes(&bundleRawType, 1);

  fromChannelsOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperandList(fromChannelsOperands))
    return ::mlir::failure();
  if (parser.parseKeyword("from"))
    return ::mlir::failure();

  bundleOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(bundleRawOperand))
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
    auto odsResult = parseUnPackBundleType(parser, toChannelsTypes, fromChannelsTypes, bundleRawType);
    if (odsResult) return ::mlir::failure();
  }
  result.addTypes(toChannelsTypes);
  if (parser.resolveOperands(bundleOperands, bundleTypes, bundleOperandsLoc, result.operands))
    return ::mlir::failure();
  if (parser.resolveOperands(fromChannelsOperands, fromChannelsTypes, fromChannelsOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void UnpackBundleOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter << getFromChannels();
  _odsPrinter << ' ' << "from";
  _odsPrinter << ' ';
  _odsPrinter << getBundle();
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
  printUnPackBundleType(_odsPrinter, *this, getToChannels().getTypes(), getFromChannels().getTypes(), getBundle().getType());
}


} // namespace circt::esi
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::esi::UnpackBundleOp)

namespace circt::esi {


//===----------------------------------------------------------------------===//
// ::circt::esi::UnwrapFIFOOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

UnwrapFIFOOpGenericAdaptorBase::UnwrapFIFOOpGenericAdaptorBase(UnwrapFIFOOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}


} // namespace detail
UnwrapFIFOOpAdaptor::UnwrapFIFOOpAdaptor(UnwrapFIFOOp op) : UnwrapFIFOOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult UnwrapFIFOOpAdaptor::verify(::mlir::Location loc) {
  return ::mlir::success();
}

void UnwrapFIFOOp::getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn) {
  auto resultGroup0 = getODSResults(0);
  if (!resultGroup0.empty())
    setNameFn(*resultGroup0.begin(), "data");
  auto resultGroup1 = getODSResults(1);
  if (!resultGroup1.empty())
    setNameFn(*resultGroup1.begin(), "empty");
}

::llvm::LogicalResult UnwrapFIFOOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }
      return ::mlir::success();
}

::mlir::Attribute UnwrapFIFOOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code UnwrapFIFOOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine();
}

std::optional<mlir::Attribute> UnwrapFIFOOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
  return std::nullopt;
}

void UnwrapFIFOOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
}

void UnwrapFIFOOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
}

::llvm::LogicalResult UnwrapFIFOOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    return ::mlir::success();
}

void UnwrapFIFOOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type data, ::mlir::Type empty, ::mlir::Value chanInput, ::mlir::Value rden) {
  odsState.addOperands(chanInput);
  odsState.addOperands(rden);
  odsState.addTypes(data);
  odsState.addTypes(empty);
}

UnwrapFIFOOp UnwrapFIFOOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type data, ::mlir::Type empty, ::mlir::Value chanInput, ::mlir::Value rden) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(data)>(data), std::forward<decltype(empty)>(empty), std::forward<decltype(chanInput)>(chanInput), std::forward<decltype(rden)>(rden));
  auto __res__ = ::llvm::dyn_cast<UnwrapFIFOOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

UnwrapFIFOOp UnwrapFIFOOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type data, ::mlir::Type empty, ::mlir::Value chanInput, ::mlir::Value rden) {
  return create(builder, builder.getLoc(), std::forward<decltype(data)>(data), std::forward<decltype(empty)>(empty), std::forward<decltype(chanInput)>(chanInput), std::forward<decltype(rden)>(rden));
}

void UnwrapFIFOOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value chanInput, ::mlir::Value rden) {
  odsState.addOperands(chanInput);
  odsState.addOperands(rden);

        ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
        if (::mlir::succeeded(UnwrapFIFOOp::inferReturnTypes(odsBuilder.getContext(),
                      odsState.location, odsState.operands,
                      odsState.attributes.getDictionary(odsState.getContext()),
                      odsState.getRawProperties(),
                      odsState.regions, inferredReturnTypes)))
          odsState.addTypes(inferredReturnTypes);
        else
          ::mlir::detail::reportFatalInferReturnTypesError(odsState);
        
}

UnwrapFIFOOp UnwrapFIFOOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value chanInput, ::mlir::Value rden) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(chanInput)>(chanInput), std::forward<decltype(rden)>(rden));
  auto __res__ = ::llvm::dyn_cast<UnwrapFIFOOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

UnwrapFIFOOp UnwrapFIFOOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value chanInput, ::mlir::Value rden) {
  return create(builder, builder.getLoc(), std::forward<decltype(chanInput)>(chanInput), std::forward<decltype(rden)>(rden));
}

void UnwrapFIFOOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value chanInput, ::mlir::Value rden) {
  odsState.addOperands(chanInput);
  odsState.addOperands(rden);
  assert(resultTypes.size() == 2u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

UnwrapFIFOOp UnwrapFIFOOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value chanInput, ::mlir::Value rden) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(chanInput)>(chanInput), std::forward<decltype(rden)>(rden));
  auto __res__ = ::llvm::dyn_cast<UnwrapFIFOOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

UnwrapFIFOOp UnwrapFIFOOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value chanInput, ::mlir::Value rden) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(chanInput)>(chanInput), std::forward<decltype(rden)>(rden));
}

void UnwrapFIFOOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 2u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 2u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

UnwrapFIFOOp UnwrapFIFOOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<UnwrapFIFOOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

UnwrapFIFOOp UnwrapFIFOOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void UnwrapFIFOOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 2u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);

  ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
  if (::mlir::succeeded(UnwrapFIFOOp::inferReturnTypes(odsBuilder.getContext(),
          odsState.location, operands,
          odsState.attributes.getDictionary(odsState.getContext()),
          odsState.getRawProperties(),
          odsState.regions, inferredReturnTypes))) {
    assert(inferredReturnTypes.size() == 2u && "mismatched number of return types");
    odsState.addTypes(inferredReturnTypes);
  } else {
    ::llvm::report_fatal_error("Failed to infer result type(s).");
  }
}

UnwrapFIFOOp UnwrapFIFOOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<UnwrapFIFOOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

UnwrapFIFOOp UnwrapFIFOOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void UnwrapFIFOOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 2u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 2u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

UnwrapFIFOOp UnwrapFIFOOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<UnwrapFIFOOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

UnwrapFIFOOp UnwrapFIFOOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

void UnwrapFIFOOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 2u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties &>(properties));
  odsState.addAttributes(discardableAttributes);

  ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
  if (::mlir::succeeded(UnwrapFIFOOp::inferReturnTypes(odsBuilder.getContext(),
          odsState.location, operands,
          odsState.attributes.getDictionary(odsState.getContext()),
          odsState.getRawProperties(),
          odsState.regions, inferredReturnTypes))) {
    assert(inferredReturnTypes.size() == 2u && "mismatched number of return types");
    odsState.addTypes(inferredReturnTypes);
  } else {
    ::llvm::report_fatal_error("Failed to infer result type(s).");
  }
}

UnwrapFIFOOp UnwrapFIFOOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<UnwrapFIFOOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

UnwrapFIFOOp UnwrapFIFOOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult UnwrapFIFOOp::verifyInvariantsImpl() {
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_ESI3(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSOperands(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_ESI2(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_ESI4(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSResults(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_ESI2(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult UnwrapFIFOOp::verifyInvariants() {
  if(::mlir::succeeded(verifyInvariantsImpl()) && ::mlir::succeeded(verify()))
    return ::mlir::success();
  return ::mlir::failure();
}

void UnwrapFIFOOp::getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context) {
  results.add(canonicalize);
}

::mlir::ParseResult UnwrapFIFOOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::OpAsmParser::UnresolvedOperand chanInputRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> chanInputOperands(&chanInputRawOperand, 1);  ::llvm::SMLoc chanInputOperandsLoc;
  (void)chanInputOperandsLoc;
  ::mlir::OpAsmParser::UnresolvedOperand rdenRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> rdenOperands(&rdenRawOperand, 1);  ::llvm::SMLoc rdenOperandsLoc;
  (void)rdenOperandsLoc;
  ::mlir::Type chanInputRawType{};
  ::llvm::ArrayRef<::mlir::Type> chanInputTypes(&chanInputRawType, 1);

  chanInputOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(chanInputRawOperand))
    return ::mlir::failure();
  if (parser.parseComma())
    return ::mlir::failure();

  rdenOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(rdenRawOperand))
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

  if (parser.parseType(chanInputRawType))
    return ::mlir::failure();
  ::mlir::Type odsBuildableType0 = parser.getBuilder().getIntegerType(1);
  if (parser.resolveOperands(chanInputOperands, chanInputTypes, chanInputOperandsLoc, result.operands))
    return ::mlir::failure();
  if (parser.resolveOperands(rdenOperands, odsBuildableType0, rdenOperandsLoc, result.operands))
    return ::mlir::failure();

  ::llvm::SmallVector<::mlir::Type> inferredReturnTypes;
  if (::mlir::failed(UnwrapFIFOOp::inferReturnTypes(parser.getContext(),
      result.location, result.operands,
      result.attributes.getDictionary(parser.getContext()),
      result.getRawProperties(),
      result.regions, inferredReturnTypes)))
    return ::mlir::failure();
  result.addTypes(inferredReturnTypes);
  return ::mlir::success();
}

void UnwrapFIFOOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter << getChanInput();
  _odsPrinter << ",";
  _odsPrinter << ' ';
  _odsPrinter << getRden();
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
   _odsPrinter << getChanInput().getType();
}


} // namespace circt::esi
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::esi::UnwrapFIFOOp)

namespace circt::esi {


//===----------------------------------------------------------------------===//
// ::circt::esi::UnwrapSVInterfaceOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

UnwrapSVInterfaceOpGenericAdaptorBase::UnwrapSVInterfaceOpGenericAdaptorBase(UnwrapSVInterfaceOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}


} // namespace detail
UnwrapSVInterfaceOpAdaptor::UnwrapSVInterfaceOpAdaptor(UnwrapSVInterfaceOp op) : UnwrapSVInterfaceOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult UnwrapSVInterfaceOpAdaptor::verify(::mlir::Location loc) {
  return ::mlir::success();
}

::llvm::LogicalResult UnwrapSVInterfaceOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }
      return ::mlir::success();
}

::mlir::Attribute UnwrapSVInterfaceOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code UnwrapSVInterfaceOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine();
}

std::optional<mlir::Attribute> UnwrapSVInterfaceOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
  return std::nullopt;
}

void UnwrapSVInterfaceOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
}

void UnwrapSVInterfaceOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
}

::llvm::LogicalResult UnwrapSVInterfaceOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    return ::mlir::success();
}

void UnwrapSVInterfaceOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value chanInput, ::mlir::Value interfaceSource) {
  odsState.addOperands(chanInput);
  odsState.addOperands(interfaceSource);
}

UnwrapSVInterfaceOp UnwrapSVInterfaceOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value chanInput, ::mlir::Value interfaceSource) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(chanInput)>(chanInput), std::forward<decltype(interfaceSource)>(interfaceSource));
  auto __res__ = ::llvm::dyn_cast<UnwrapSVInterfaceOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

UnwrapSVInterfaceOp UnwrapSVInterfaceOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value chanInput, ::mlir::Value interfaceSource) {
  return create(builder, builder.getLoc(), std::forward<decltype(chanInput)>(chanInput), std::forward<decltype(interfaceSource)>(interfaceSource));
}

void UnwrapSVInterfaceOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value chanInput, ::mlir::Value interfaceSource) {
  odsState.addOperands(chanInput);
  odsState.addOperands(interfaceSource);
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

UnwrapSVInterfaceOp UnwrapSVInterfaceOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value chanInput, ::mlir::Value interfaceSource) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(chanInput)>(chanInput), std::forward<decltype(interfaceSource)>(interfaceSource));
  auto __res__ = ::llvm::dyn_cast<UnwrapSVInterfaceOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

UnwrapSVInterfaceOp UnwrapSVInterfaceOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value chanInput, ::mlir::Value interfaceSource) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(chanInput)>(chanInput), std::forward<decltype(interfaceSource)>(interfaceSource));
}

void UnwrapSVInterfaceOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 2u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

UnwrapSVInterfaceOp UnwrapSVInterfaceOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<UnwrapSVInterfaceOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

UnwrapSVInterfaceOp UnwrapSVInterfaceOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void UnwrapSVInterfaceOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 2u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

UnwrapSVInterfaceOp UnwrapSVInterfaceOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<UnwrapSVInterfaceOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

UnwrapSVInterfaceOp UnwrapSVInterfaceOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult UnwrapSVInterfaceOp::verifyInvariantsImpl() {
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_ESI3(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSOperands(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_ESI8(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult UnwrapSVInterfaceOp::verifyInvariants() {
  if(::mlir::succeeded(verifyInvariantsImpl()) && ::mlir::succeeded(verify()))
    return ::mlir::success();
  return ::mlir::failure();
}

::mlir::ParseResult UnwrapSVInterfaceOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::OpAsmParser::UnresolvedOperand chanInputRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> chanInputOperands(&chanInputRawOperand, 1);  ::llvm::SMLoc chanInputOperandsLoc;
  (void)chanInputOperandsLoc;
  ::mlir::OpAsmParser::UnresolvedOperand interfaceSourceRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> interfaceSourceOperands(&interfaceSourceRawOperand, 1);  ::llvm::SMLoc interfaceSourceOperandsLoc;
  (void)interfaceSourceOperandsLoc;
  ::mlir::Type chanInputRawType{};
  ::llvm::ArrayRef<::mlir::Type> chanInputTypes(&chanInputRawType, 1);
  ::mlir::Type interfaceSourceRawType{};
  ::llvm::ArrayRef<::mlir::Type> interfaceSourceTypes(&interfaceSourceRawType, 1);

  chanInputOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(chanInputRawOperand))
    return ::mlir::failure();
  if (parser.parseKeyword("into"))
    return ::mlir::failure();

  interfaceSourceOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(interfaceSourceRawOperand))
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
  if (parser.parseLParen())
    return ::mlir::failure();

  if (parser.parseType(chanInputRawType))
    return ::mlir::failure();
  if (parser.parseComma())
    return ::mlir::failure();

  if (parser.parseType(interfaceSourceRawType))
    return ::mlir::failure();
  if (parser.parseRParen())
    return ::mlir::failure();
  if (parser.resolveOperands(chanInputOperands, chanInputTypes, chanInputOperandsLoc, result.operands))
    return ::mlir::failure();
  if (parser.resolveOperands(interfaceSourceOperands, interfaceSourceTypes, interfaceSourceOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void UnwrapSVInterfaceOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter << getChanInput();
  _odsPrinter << ' ' << "into";
  _odsPrinter << ' ';
  _odsPrinter << getInterfaceSource();
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ' << "(";
   _odsPrinter << getChanInput().getType();
  _odsPrinter << ",";
  _odsPrinter << ' ';
   _odsPrinter << getInterfaceSource().getType();
  _odsPrinter << ")";
}


} // namespace circt::esi
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::esi::UnwrapSVInterfaceOp)

namespace circt::esi {


//===----------------------------------------------------------------------===//
// ::circt::esi::UnwrapValidOnlyOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

UnwrapValidOnlyOpGenericAdaptorBase::UnwrapValidOnlyOpGenericAdaptorBase(UnwrapValidOnlyOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}


} // namespace detail
UnwrapValidOnlyOpAdaptor::UnwrapValidOnlyOpAdaptor(UnwrapValidOnlyOp op) : UnwrapValidOnlyOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult UnwrapValidOnlyOpAdaptor::verify(::mlir::Location loc) {
  return ::mlir::success();
}

void UnwrapValidOnlyOp::getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn) {
  auto resultGroup0 = getODSResults(0);
  if (!resultGroup0.empty())
    setNameFn(*resultGroup0.begin(), "rawOutput");
  auto resultGroup1 = getODSResults(1);
  if (!resultGroup1.empty())
    setNameFn(*resultGroup1.begin(), "valid");
}

::llvm::LogicalResult UnwrapValidOnlyOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }
      return ::mlir::success();
}

::mlir::Attribute UnwrapValidOnlyOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code UnwrapValidOnlyOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine();
}

std::optional<mlir::Attribute> UnwrapValidOnlyOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
  return std::nullopt;
}

void UnwrapValidOnlyOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
}

void UnwrapValidOnlyOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
}

::llvm::LogicalResult UnwrapValidOnlyOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    return ::mlir::success();
}

void UnwrapValidOnlyOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type rawOutput, ::mlir::Type valid, ::mlir::Value chanInput) {
  odsState.addOperands(chanInput);
  odsState.addTypes(rawOutput);
  odsState.addTypes(valid);
}

UnwrapValidOnlyOp UnwrapValidOnlyOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type rawOutput, ::mlir::Type valid, ::mlir::Value chanInput) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(rawOutput)>(rawOutput), std::forward<decltype(valid)>(valid), std::forward<decltype(chanInput)>(chanInput));
  auto __res__ = ::llvm::dyn_cast<UnwrapValidOnlyOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

UnwrapValidOnlyOp UnwrapValidOnlyOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type rawOutput, ::mlir::Type valid, ::mlir::Value chanInput) {
  return create(builder, builder.getLoc(), std::forward<decltype(rawOutput)>(rawOutput), std::forward<decltype(valid)>(valid), std::forward<decltype(chanInput)>(chanInput));
}

void UnwrapValidOnlyOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value chanInput) {
  odsState.addOperands(chanInput);

        ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
        if (::mlir::succeeded(UnwrapValidOnlyOp::inferReturnTypes(odsBuilder.getContext(),
                      odsState.location, odsState.operands,
                      odsState.attributes.getDictionary(odsState.getContext()),
                      odsState.getRawProperties(),
                      odsState.regions, inferredReturnTypes)))
          odsState.addTypes(inferredReturnTypes);
        else
          ::mlir::detail::reportFatalInferReturnTypesError(odsState);
        
}

UnwrapValidOnlyOp UnwrapValidOnlyOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value chanInput) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(chanInput)>(chanInput));
  auto __res__ = ::llvm::dyn_cast<UnwrapValidOnlyOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

UnwrapValidOnlyOp UnwrapValidOnlyOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value chanInput) {
  return create(builder, builder.getLoc(), std::forward<decltype(chanInput)>(chanInput));
}

void UnwrapValidOnlyOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value chanInput) {
  odsState.addOperands(chanInput);
  assert(resultTypes.size() == 2u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

UnwrapValidOnlyOp UnwrapValidOnlyOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value chanInput) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(chanInput)>(chanInput));
  auto __res__ = ::llvm::dyn_cast<UnwrapValidOnlyOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

UnwrapValidOnlyOp UnwrapValidOnlyOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value chanInput) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(chanInput)>(chanInput));
}

void UnwrapValidOnlyOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 2u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

UnwrapValidOnlyOp UnwrapValidOnlyOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<UnwrapValidOnlyOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

UnwrapValidOnlyOp UnwrapValidOnlyOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void UnwrapValidOnlyOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);

  ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
  if (::mlir::succeeded(UnwrapValidOnlyOp::inferReturnTypes(odsBuilder.getContext(),
          odsState.location, operands,
          odsState.attributes.getDictionary(odsState.getContext()),
          odsState.getRawProperties(),
          odsState.regions, inferredReturnTypes))) {
    assert(inferredReturnTypes.size() == 2u && "mismatched number of return types");
    odsState.addTypes(inferredReturnTypes);
  } else {
    ::llvm::report_fatal_error("Failed to infer result type(s).");
  }
}

UnwrapValidOnlyOp UnwrapValidOnlyOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<UnwrapValidOnlyOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

UnwrapValidOnlyOp UnwrapValidOnlyOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void UnwrapValidOnlyOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 2u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

UnwrapValidOnlyOp UnwrapValidOnlyOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<UnwrapValidOnlyOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

UnwrapValidOnlyOp UnwrapValidOnlyOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

void UnwrapValidOnlyOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties &>(properties));
  odsState.addAttributes(discardableAttributes);

  ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
  if (::mlir::succeeded(UnwrapValidOnlyOp::inferReturnTypes(odsBuilder.getContext(),
          odsState.location, operands,
          odsState.attributes.getDictionary(odsState.getContext()),
          odsState.getRawProperties(),
          odsState.regions, inferredReturnTypes))) {
    assert(inferredReturnTypes.size() == 2u && "mismatched number of return types");
    odsState.addTypes(inferredReturnTypes);
  } else {
    ::llvm::report_fatal_error("Failed to infer result type(s).");
  }
}

UnwrapValidOnlyOp UnwrapValidOnlyOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<UnwrapValidOnlyOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

UnwrapValidOnlyOp UnwrapValidOnlyOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult UnwrapValidOnlyOp::verifyInvariantsImpl() {
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_ESI3(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_ESI4(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSResults(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_ESI2(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult UnwrapValidOnlyOp::verifyInvariants() {
  if(::mlir::succeeded(verifyInvariantsImpl()) && ::mlir::succeeded(verify()))
    return ::mlir::success();
  return ::mlir::failure();
}

void UnwrapValidOnlyOp::getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context) {
  results.add(canonicalize);
}

::mlir::ParseResult UnwrapValidOnlyOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::OpAsmParser::UnresolvedOperand chanInputRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> chanInputOperands(&chanInputRawOperand, 1);  ::llvm::SMLoc chanInputOperandsLoc;
  (void)chanInputOperandsLoc;
  ::mlir::Type chanInputRawType{};
  ::llvm::ArrayRef<::mlir::Type> chanInputTypes(&chanInputRawType, 1);

  chanInputOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(chanInputRawOperand))
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

  if (parser.parseType(chanInputRawType))
    return ::mlir::failure();
  if (parser.resolveOperands(chanInputOperands, chanInputTypes, chanInputOperandsLoc, result.operands))
    return ::mlir::failure();

  ::llvm::SmallVector<::mlir::Type> inferredReturnTypes;
  if (::mlir::failed(UnwrapValidOnlyOp::inferReturnTypes(parser.getContext(),
      result.location, result.operands,
      result.attributes.getDictionary(parser.getContext()),
      result.getRawProperties(),
      result.regions, inferredReturnTypes)))
    return ::mlir::failure();
  result.addTypes(inferredReturnTypes);
  return ::mlir::success();
}

void UnwrapValidOnlyOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter << getChanInput();
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
   _odsPrinter << getChanInput().getType();
}


} // namespace circt::esi
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::esi::UnwrapValidOnlyOp)

namespace circt::esi {


//===----------------------------------------------------------------------===//
// ::circt::esi::UnwrapValidReadyOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

UnwrapValidReadyOpGenericAdaptorBase::UnwrapValidReadyOpGenericAdaptorBase(UnwrapValidReadyOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}


} // namespace detail
UnwrapValidReadyOpAdaptor::UnwrapValidReadyOpAdaptor(UnwrapValidReadyOp op) : UnwrapValidReadyOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult UnwrapValidReadyOpAdaptor::verify(::mlir::Location loc) {
  return ::mlir::success();
}

void UnwrapValidReadyOp::getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn) {
  auto resultGroup0 = getODSResults(0);
  if (!resultGroup0.empty())
    setNameFn(*resultGroup0.begin(), "rawOutput");
  auto resultGroup1 = getODSResults(1);
  if (!resultGroup1.empty())
    setNameFn(*resultGroup1.begin(), "valid");
}

::llvm::LogicalResult UnwrapValidReadyOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }
      return ::mlir::success();
}

::mlir::Attribute UnwrapValidReadyOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code UnwrapValidReadyOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine();
}

std::optional<mlir::Attribute> UnwrapValidReadyOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
  return std::nullopt;
}

void UnwrapValidReadyOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
}

void UnwrapValidReadyOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
}

::llvm::LogicalResult UnwrapValidReadyOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    return ::mlir::success();
}

UnwrapValidReadyOp UnwrapValidReadyOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, mlir::Value inChan, mlir::Value ready) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(inChan)>(inChan), std::forward<decltype(ready)>(ready));
  auto __res__ = ::llvm::dyn_cast<UnwrapValidReadyOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

UnwrapValidReadyOp UnwrapValidReadyOp::create(::mlir::ImplicitLocOpBuilder &builder, mlir::Value inChan, mlir::Value ready) {
  return create(builder, builder.getLoc(), std::forward<decltype(inChan)>(inChan), std::forward<decltype(ready)>(ready));
}

void UnwrapValidReadyOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type rawOutput, ::mlir::Type valid, ::mlir::Value chanInput, ::mlir::Value ready) {
  odsState.addOperands(chanInput);
  odsState.addOperands(ready);
  odsState.addTypes(rawOutput);
  odsState.addTypes(valid);
}

UnwrapValidReadyOp UnwrapValidReadyOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type rawOutput, ::mlir::Type valid, ::mlir::Value chanInput, ::mlir::Value ready) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(rawOutput)>(rawOutput), std::forward<decltype(valid)>(valid), std::forward<decltype(chanInput)>(chanInput), std::forward<decltype(ready)>(ready));
  auto __res__ = ::llvm::dyn_cast<UnwrapValidReadyOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

UnwrapValidReadyOp UnwrapValidReadyOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type rawOutput, ::mlir::Type valid, ::mlir::Value chanInput, ::mlir::Value ready) {
  return create(builder, builder.getLoc(), std::forward<decltype(rawOutput)>(rawOutput), std::forward<decltype(valid)>(valid), std::forward<decltype(chanInput)>(chanInput), std::forward<decltype(ready)>(ready));
}

void UnwrapValidReadyOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value chanInput, ::mlir::Value ready) {
  odsState.addOperands(chanInput);
  odsState.addOperands(ready);
  assert(resultTypes.size() == 2u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

UnwrapValidReadyOp UnwrapValidReadyOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value chanInput, ::mlir::Value ready) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(chanInput)>(chanInput), std::forward<decltype(ready)>(ready));
  auto __res__ = ::llvm::dyn_cast<UnwrapValidReadyOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

UnwrapValidReadyOp UnwrapValidReadyOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value chanInput, ::mlir::Value ready) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(chanInput)>(chanInput), std::forward<decltype(ready)>(ready));
}

void UnwrapValidReadyOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 2u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 2u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

UnwrapValidReadyOp UnwrapValidReadyOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<UnwrapValidReadyOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

UnwrapValidReadyOp UnwrapValidReadyOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void UnwrapValidReadyOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 2u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 2u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

UnwrapValidReadyOp UnwrapValidReadyOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<UnwrapValidReadyOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

UnwrapValidReadyOp UnwrapValidReadyOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult UnwrapValidReadyOp::verifyInvariantsImpl() {
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_ESI3(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSOperands(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_ESI2(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_ESI4(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSResults(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_ESI2(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult UnwrapValidReadyOp::verifyInvariants() {
  if(::mlir::succeeded(verifyInvariantsImpl()) && ::mlir::succeeded(verify()))
    return ::mlir::success();
  return ::mlir::failure();
}

::llvm::LogicalResult UnwrapValidReadyOp::setPropertiesFromParsedAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
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


} // namespace circt::esi
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::esi::UnwrapValidReadyOp)

namespace circt::esi {


//===----------------------------------------------------------------------===//
// ::circt::esi::UnwrapWindow definitions
//===----------------------------------------------------------------------===//

namespace detail {

UnwrapWindowGenericAdaptorBase::UnwrapWindowGenericAdaptorBase(UnwrapWindow op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}


} // namespace detail
UnwrapWindowAdaptor::UnwrapWindowAdaptor(UnwrapWindow op) : UnwrapWindowGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult UnwrapWindowAdaptor::verify(::mlir::Location loc) {
  return ::mlir::success();
}

::llvm::LogicalResult UnwrapWindow::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }
      return ::mlir::success();
}

::mlir::Attribute UnwrapWindow::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code UnwrapWindow::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine();
}

std::optional<mlir::Attribute> UnwrapWindow::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
  return std::nullopt;
}

void UnwrapWindow::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
}

void UnwrapWindow::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
}

::llvm::LogicalResult UnwrapWindow::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    return ::mlir::success();
}

void UnwrapWindow::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type frame, ::mlir::Value window) {
  odsState.addOperands(window);
  odsState.addTypes(frame);
}

UnwrapWindow UnwrapWindow::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type frame, ::mlir::Value window) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(frame)>(frame), std::forward<decltype(window)>(window));
  auto __res__ = ::llvm::dyn_cast<UnwrapWindow>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

UnwrapWindow UnwrapWindow::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type frame, ::mlir::Value window) {
  return create(builder, builder.getLoc(), std::forward<decltype(frame)>(frame), std::forward<decltype(window)>(window));
}

void UnwrapWindow::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value window) {
  odsState.addOperands(window);

        ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
        if (::mlir::succeeded(UnwrapWindow::inferReturnTypes(odsBuilder.getContext(),
                      odsState.location, odsState.operands,
                      odsState.attributes.getDictionary(odsState.getContext()),
                      odsState.getRawProperties(),
                      odsState.regions, inferredReturnTypes)))
          odsState.addTypes(inferredReturnTypes);
        else
          ::mlir::detail::reportFatalInferReturnTypesError(odsState);
        
}

UnwrapWindow UnwrapWindow::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value window) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(window)>(window));
  auto __res__ = ::llvm::dyn_cast<UnwrapWindow>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

UnwrapWindow UnwrapWindow::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value window) {
  return create(builder, builder.getLoc(), std::forward<decltype(window)>(window));
}

void UnwrapWindow::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value window) {
  odsState.addOperands(window);
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

UnwrapWindow UnwrapWindow::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value window) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(window)>(window));
  auto __res__ = ::llvm::dyn_cast<UnwrapWindow>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

UnwrapWindow UnwrapWindow::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value window) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(window)>(window));
}

void UnwrapWindow::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

UnwrapWindow UnwrapWindow::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<UnwrapWindow>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

UnwrapWindow UnwrapWindow::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void UnwrapWindow::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);

  ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
  if (::mlir::succeeded(UnwrapWindow::inferReturnTypes(odsBuilder.getContext(),
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

UnwrapWindow UnwrapWindow::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<UnwrapWindow>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

UnwrapWindow UnwrapWindow::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void UnwrapWindow::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

UnwrapWindow UnwrapWindow::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<UnwrapWindow>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

UnwrapWindow UnwrapWindow::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

void UnwrapWindow::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties &>(properties));
  odsState.addAttributes(discardableAttributes);

  ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
  if (::mlir::succeeded(UnwrapWindow::inferReturnTypes(odsBuilder.getContext(),
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

UnwrapWindow UnwrapWindow::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<UnwrapWindow>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

UnwrapWindow UnwrapWindow::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult UnwrapWindow::verifyInvariantsImpl() {
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_ESI9(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_ESI4(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult UnwrapWindow::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult UnwrapWindow::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::OpAsmParser::UnresolvedOperand windowRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> windowOperands(&windowRawOperand, 1);  ::llvm::SMLoc windowOperandsLoc;
  (void)windowOperandsLoc;
  ::mlir::Type windowRawType{};
  ::llvm::ArrayRef<::mlir::Type> windowTypes(&windowRawType, 1);

  windowOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(windowRawOperand))
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

  if (parser.parseType(windowRawType))
    return ::mlir::failure();
  if (parser.resolveOperands(windowOperands, windowTypes, windowOperandsLoc, result.operands))
    return ::mlir::failure();

  ::llvm::SmallVector<::mlir::Type> inferredReturnTypes;
  if (::mlir::failed(UnwrapWindow::inferReturnTypes(parser.getContext(),
      result.location, result.operands,
      result.attributes.getDictionary(parser.getContext()),
      result.getRawProperties(),
      result.regions, inferredReturnTypes)))
    return ::mlir::failure();
  result.addTypes(inferredReturnTypes);
  return ::mlir::success();
}

void UnwrapWindow::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter << getWindow();
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
   _odsPrinter << getWindow().getType();
}

void UnwrapWindow::getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects) {
}


} // namespace circt::esi
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::esi::UnwrapWindow)

namespace circt::esi {


//===----------------------------------------------------------------------===//
// ::circt::esi::WrapFIFOOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

WrapFIFOOpGenericAdaptorBase::WrapFIFOOpGenericAdaptorBase(WrapFIFOOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}


} // namespace detail
WrapFIFOOpAdaptor::WrapFIFOOpAdaptor(WrapFIFOOp op) : WrapFIFOOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult WrapFIFOOpAdaptor::verify(::mlir::Location loc) {
  return ::mlir::success();
}

void WrapFIFOOp::getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn) {
  auto resultGroup0 = getODSResults(0);
  if (!resultGroup0.empty())
    setNameFn(*resultGroup0.begin(), "chanOutput");
  auto resultGroup1 = getODSResults(1);
  if (!resultGroup1.empty())
    setNameFn(*resultGroup1.begin(), "rden");
}

::llvm::LogicalResult WrapFIFOOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }
      return ::mlir::success();
}

::mlir::Attribute WrapFIFOOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code WrapFIFOOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine();
}

std::optional<mlir::Attribute> WrapFIFOOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
  return std::nullopt;
}

void WrapFIFOOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
}

void WrapFIFOOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
}

::llvm::LogicalResult WrapFIFOOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    return ::mlir::success();
}

void WrapFIFOOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type chanOutput, ::mlir::Type rden, ::mlir::Value data, ::mlir::Value empty) {
  odsState.addOperands(data);
  odsState.addOperands(empty);
  odsState.addTypes(chanOutput);
  odsState.addTypes(rden);
}

WrapFIFOOp WrapFIFOOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type chanOutput, ::mlir::Type rden, ::mlir::Value data, ::mlir::Value empty) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(chanOutput)>(chanOutput), std::forward<decltype(rden)>(rden), std::forward<decltype(data)>(data), std::forward<decltype(empty)>(empty));
  auto __res__ = ::llvm::dyn_cast<WrapFIFOOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

WrapFIFOOp WrapFIFOOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type chanOutput, ::mlir::Type rden, ::mlir::Value data, ::mlir::Value empty) {
  return create(builder, builder.getLoc(), std::forward<decltype(chanOutput)>(chanOutput), std::forward<decltype(rden)>(rden), std::forward<decltype(data)>(data), std::forward<decltype(empty)>(empty));
}

void WrapFIFOOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value data, ::mlir::Value empty) {
  odsState.addOperands(data);
  odsState.addOperands(empty);
  assert(resultTypes.size() == 2u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

WrapFIFOOp WrapFIFOOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value data, ::mlir::Value empty) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(data)>(data), std::forward<decltype(empty)>(empty));
  auto __res__ = ::llvm::dyn_cast<WrapFIFOOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

WrapFIFOOp WrapFIFOOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value data, ::mlir::Value empty) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(data)>(data), std::forward<decltype(empty)>(empty));
}

void WrapFIFOOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 2u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 2u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

WrapFIFOOp WrapFIFOOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<WrapFIFOOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

WrapFIFOOp WrapFIFOOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void WrapFIFOOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 2u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 2u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

WrapFIFOOp WrapFIFOOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<WrapFIFOOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

WrapFIFOOp WrapFIFOOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult WrapFIFOOp::verifyInvariantsImpl() {
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_ESI4(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSOperands(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_ESI2(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_ESI3(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSResults(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_ESI2(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult WrapFIFOOp::verifyInvariants() {
  if(::mlir::succeeded(verifyInvariantsImpl()) && ::mlir::succeeded(verify()))
    return ::mlir::success();
  return ::mlir::failure();
}

void WrapFIFOOp::getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context) {
  results.add(canonicalize);
}

::mlir::ParseResult WrapFIFOOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::OpAsmParser::UnresolvedOperand dataRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> dataOperands(&dataRawOperand, 1);  ::llvm::SMLoc dataOperandsLoc;
  (void)dataOperandsLoc;
  ::mlir::OpAsmParser::UnresolvedOperand emptyRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> emptyOperands(&emptyRawOperand, 1);  ::llvm::SMLoc emptyOperandsLoc;
  (void)emptyOperandsLoc;
  ::mlir::Type dataRawType{};
  ::llvm::ArrayRef<::mlir::Type> dataTypes(&dataRawType, 1);
  ::mlir::Type chanOutputRawType{};
  ::llvm::ArrayRef<::mlir::Type> chanOutputTypes(&chanOutputRawType, 1);

  dataOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(dataRawOperand))
    return ::mlir::failure();
  if (parser.parseComma())
    return ::mlir::failure();

  emptyOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(emptyRawOperand))
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
    auto odsResult = parseWrapFIFOType(parser, dataRawType, chanOutputRawType);
    if (odsResult) return ::mlir::failure();
  }
  ::mlir::Type odsBuildableType0 = parser.getBuilder().getIntegerType(1);
  result.addTypes(chanOutputTypes);
  result.addTypes(odsBuildableType0);
  if (parser.resolveOperands(dataOperands, dataTypes, dataOperandsLoc, result.operands))
    return ::mlir::failure();
  if (parser.resolveOperands(emptyOperands, odsBuildableType0, emptyOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void WrapFIFOOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter << getData();
  _odsPrinter << ",";
  _odsPrinter << ' ';
  _odsPrinter << getEmpty();
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
  printWrapFIFOType(_odsPrinter, *this, getData().getType(), getChanOutput().getType());
}


} // namespace circt::esi
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::esi::WrapFIFOOp)

namespace circt::esi {


//===----------------------------------------------------------------------===//
// ::circt::esi::WrapSVInterfaceOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

WrapSVInterfaceOpGenericAdaptorBase::WrapSVInterfaceOpGenericAdaptorBase(WrapSVInterfaceOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}


} // namespace detail
WrapSVInterfaceOpAdaptor::WrapSVInterfaceOpAdaptor(WrapSVInterfaceOp op) : WrapSVInterfaceOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult WrapSVInterfaceOpAdaptor::verify(::mlir::Location loc) {
  return ::mlir::success();
}

::llvm::LogicalResult WrapSVInterfaceOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }
      return ::mlir::success();
}

::mlir::Attribute WrapSVInterfaceOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code WrapSVInterfaceOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine();
}

std::optional<mlir::Attribute> WrapSVInterfaceOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
  return std::nullopt;
}

void WrapSVInterfaceOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
}

void WrapSVInterfaceOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
}

::llvm::LogicalResult WrapSVInterfaceOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    return ::mlir::success();
}

void WrapSVInterfaceOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type output, ::mlir::Value interfaceSink) {
  odsState.addOperands(interfaceSink);
  odsState.addTypes(output);
}

WrapSVInterfaceOp WrapSVInterfaceOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type output, ::mlir::Value interfaceSink) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(output)>(output), std::forward<decltype(interfaceSink)>(interfaceSink));
  auto __res__ = ::llvm::dyn_cast<WrapSVInterfaceOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

WrapSVInterfaceOp WrapSVInterfaceOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type output, ::mlir::Value interfaceSink) {
  return create(builder, builder.getLoc(), std::forward<decltype(output)>(output), std::forward<decltype(interfaceSink)>(interfaceSink));
}

void WrapSVInterfaceOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value interfaceSink) {
  odsState.addOperands(interfaceSink);
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

WrapSVInterfaceOp WrapSVInterfaceOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value interfaceSink) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(interfaceSink)>(interfaceSink));
  auto __res__ = ::llvm::dyn_cast<WrapSVInterfaceOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

WrapSVInterfaceOp WrapSVInterfaceOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value interfaceSink) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(interfaceSink)>(interfaceSink));
}

void WrapSVInterfaceOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

WrapSVInterfaceOp WrapSVInterfaceOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<WrapSVInterfaceOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

WrapSVInterfaceOp WrapSVInterfaceOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void WrapSVInterfaceOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

WrapSVInterfaceOp WrapSVInterfaceOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<WrapSVInterfaceOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

WrapSVInterfaceOp WrapSVInterfaceOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult WrapSVInterfaceOp::verifyInvariantsImpl() {
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_ESI8(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_ESI3(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult WrapSVInterfaceOp::verifyInvariants() {
  if(::mlir::succeeded(verifyInvariantsImpl()) && ::mlir::succeeded(verify()))
    return ::mlir::success();
  return ::mlir::failure();
}

::mlir::ParseResult WrapSVInterfaceOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::OpAsmParser::UnresolvedOperand interfaceSinkRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> interfaceSinkOperands(&interfaceSinkRawOperand, 1);  ::llvm::SMLoc interfaceSinkOperandsLoc;
  (void)interfaceSinkOperandsLoc;
  ::mlir::Type interfaceSinkRawType{};
  ::llvm::ArrayRef<::mlir::Type> interfaceSinkTypes(&interfaceSinkRawType, 1);
  ::mlir::Type outputRawType{};
  ::llvm::ArrayRef<::mlir::Type> outputTypes(&outputRawType, 1);

  interfaceSinkOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(interfaceSinkRawOperand))
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

  if (parser.parseType(interfaceSinkRawType))
    return ::mlir::failure();
  if (parser.parseArrow())
    return ::mlir::failure();

  if (parser.parseType(outputRawType))
    return ::mlir::failure();
  result.addTypes(outputTypes);
  if (parser.resolveOperands(interfaceSinkOperands, interfaceSinkTypes, interfaceSinkOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void WrapSVInterfaceOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter << getInterfaceSink();
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
   _odsPrinter << getInterfaceSink().getType();
  _odsPrinter << ' ' << "->";
  _odsPrinter << ' ';
   _odsPrinter << getOutput().getType();
}


} // namespace circt::esi
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::esi::WrapSVInterfaceOp)

namespace circt::esi {


//===----------------------------------------------------------------------===//
// ::circt::esi::WrapValidOnlyOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

WrapValidOnlyOpGenericAdaptorBase::WrapValidOnlyOpGenericAdaptorBase(WrapValidOnlyOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}


} // namespace detail
WrapValidOnlyOpAdaptor::WrapValidOnlyOpAdaptor(WrapValidOnlyOp op) : WrapValidOnlyOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult WrapValidOnlyOpAdaptor::verify(::mlir::Location loc) {
  return ::mlir::success();
}

::llvm::LogicalResult WrapValidOnlyOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }
      return ::mlir::success();
}

::mlir::Attribute WrapValidOnlyOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code WrapValidOnlyOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine();
}

std::optional<mlir::Attribute> WrapValidOnlyOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
  return std::nullopt;
}

void WrapValidOnlyOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
}

void WrapValidOnlyOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
}

::llvm::LogicalResult WrapValidOnlyOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    return ::mlir::success();
}

void WrapValidOnlyOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type chanOutput, ::mlir::Value rawInput, ::mlir::Value valid) {
  odsState.addOperands(rawInput);
  odsState.addOperands(valid);
  odsState.addTypes(chanOutput);
}

WrapValidOnlyOp WrapValidOnlyOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type chanOutput, ::mlir::Value rawInput, ::mlir::Value valid) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(chanOutput)>(chanOutput), std::forward<decltype(rawInput)>(rawInput), std::forward<decltype(valid)>(valid));
  auto __res__ = ::llvm::dyn_cast<WrapValidOnlyOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

WrapValidOnlyOp WrapValidOnlyOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type chanOutput, ::mlir::Value rawInput, ::mlir::Value valid) {
  return create(builder, builder.getLoc(), std::forward<decltype(chanOutput)>(chanOutput), std::forward<decltype(rawInput)>(rawInput), std::forward<decltype(valid)>(valid));
}

void WrapValidOnlyOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value rawInput, ::mlir::Value valid) {
  odsState.addOperands(rawInput);
  odsState.addOperands(valid);

        ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
        if (::mlir::succeeded(WrapValidOnlyOp::inferReturnTypes(odsBuilder.getContext(),
                      odsState.location, odsState.operands,
                      odsState.attributes.getDictionary(odsState.getContext()),
                      odsState.getRawProperties(),
                      odsState.regions, inferredReturnTypes)))
          odsState.addTypes(inferredReturnTypes);
        else
          ::mlir::detail::reportFatalInferReturnTypesError(odsState);
        
}

WrapValidOnlyOp WrapValidOnlyOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value rawInput, ::mlir::Value valid) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(rawInput)>(rawInput), std::forward<decltype(valid)>(valid));
  auto __res__ = ::llvm::dyn_cast<WrapValidOnlyOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

WrapValidOnlyOp WrapValidOnlyOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value rawInput, ::mlir::Value valid) {
  return create(builder, builder.getLoc(), std::forward<decltype(rawInput)>(rawInput), std::forward<decltype(valid)>(valid));
}

void WrapValidOnlyOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value rawInput, ::mlir::Value valid) {
  odsState.addOperands(rawInput);
  odsState.addOperands(valid);
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

WrapValidOnlyOp WrapValidOnlyOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value rawInput, ::mlir::Value valid) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(rawInput)>(rawInput), std::forward<decltype(valid)>(valid));
  auto __res__ = ::llvm::dyn_cast<WrapValidOnlyOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

WrapValidOnlyOp WrapValidOnlyOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value rawInput, ::mlir::Value valid) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(rawInput)>(rawInput), std::forward<decltype(valid)>(valid));
}

void WrapValidOnlyOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 2u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

WrapValidOnlyOp WrapValidOnlyOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<WrapValidOnlyOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

WrapValidOnlyOp WrapValidOnlyOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void WrapValidOnlyOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 2u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);

  ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
  if (::mlir::succeeded(WrapValidOnlyOp::inferReturnTypes(odsBuilder.getContext(),
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

WrapValidOnlyOp WrapValidOnlyOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<WrapValidOnlyOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

WrapValidOnlyOp WrapValidOnlyOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void WrapValidOnlyOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 2u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

WrapValidOnlyOp WrapValidOnlyOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<WrapValidOnlyOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

WrapValidOnlyOp WrapValidOnlyOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

void WrapValidOnlyOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 2u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties &>(properties));
  odsState.addAttributes(discardableAttributes);

  ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
  if (::mlir::succeeded(WrapValidOnlyOp::inferReturnTypes(odsBuilder.getContext(),
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

WrapValidOnlyOp WrapValidOnlyOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<WrapValidOnlyOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

WrapValidOnlyOp WrapValidOnlyOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult WrapValidOnlyOp::verifyInvariantsImpl() {
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_ESI4(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSOperands(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_ESI2(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_ESI3(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult WrapValidOnlyOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

void WrapValidOnlyOp::getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context) {
  results.add(canonicalize);
}

::mlir::ParseResult WrapValidOnlyOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::OpAsmParser::UnresolvedOperand rawInputRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> rawInputOperands(&rawInputRawOperand, 1);  ::llvm::SMLoc rawInputOperandsLoc;
  (void)rawInputOperandsLoc;
  ::mlir::OpAsmParser::UnresolvedOperand validRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> validOperands(&validRawOperand, 1);  ::llvm::SMLoc validOperandsLoc;
  (void)validOperandsLoc;
  ::mlir::Type rawInputRawType{};
  ::llvm::ArrayRef<::mlir::Type> rawInputTypes(&rawInputRawType, 1);

  rawInputOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(rawInputRawOperand))
    return ::mlir::failure();
  if (parser.parseComma())
    return ::mlir::failure();

  validOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(validRawOperand))
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
    rawInputRawType = type;
  }
  ::mlir::Type odsBuildableType0 = parser.getBuilder().getIntegerType(1);
  if (parser.resolveOperands(rawInputOperands, rawInputTypes, rawInputOperandsLoc, result.operands))
    return ::mlir::failure();
  if (parser.resolveOperands(validOperands, odsBuildableType0, validOperandsLoc, result.operands))
    return ::mlir::failure();

  ::llvm::SmallVector<::mlir::Type> inferredReturnTypes;
  if (::mlir::failed(WrapValidOnlyOp::inferReturnTypes(parser.getContext(),
      result.location, result.operands,
      result.attributes.getDictionary(parser.getContext()),
      result.getRawProperties(),
      result.regions, inferredReturnTypes)))
    return ::mlir::failure();
  result.addTypes(inferredReturnTypes);
  return ::mlir::success();
}

void WrapValidOnlyOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter << getRawInput();
  _odsPrinter << ",";
  _odsPrinter << ' ';
  _odsPrinter << getValid();
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
  {
    auto type = getRawInput().getType();
    if (auto validType = ::llvm::dyn_cast<::mlir::Type>(type))
      _odsPrinter.printStrippedAttrOrType(validType);
   else
     _odsPrinter << type;
  }
}


} // namespace circt::esi
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::esi::WrapValidOnlyOp)

namespace circt::esi {


//===----------------------------------------------------------------------===//
// ::circt::esi::WrapValidReadyOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

WrapValidReadyOpGenericAdaptorBase::WrapValidReadyOpGenericAdaptorBase(WrapValidReadyOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}


} // namespace detail
WrapValidReadyOpAdaptor::WrapValidReadyOpAdaptor(WrapValidReadyOp op) : WrapValidReadyOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult WrapValidReadyOpAdaptor::verify(::mlir::Location loc) {
  return ::mlir::success();
}

void WrapValidReadyOp::getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn) {
  auto resultGroup0 = getODSResults(0);
  if (!resultGroup0.empty())
    setNameFn(*resultGroup0.begin(), "chanOutput");
  auto resultGroup1 = getODSResults(1);
  if (!resultGroup1.empty())
    setNameFn(*resultGroup1.begin(), "ready");
}

::llvm::LogicalResult WrapValidReadyOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }
      return ::mlir::success();
}

::mlir::Attribute WrapValidReadyOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code WrapValidReadyOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine();
}

std::optional<mlir::Attribute> WrapValidReadyOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
  return std::nullopt;
}

void WrapValidReadyOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
}

void WrapValidReadyOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
}

::llvm::LogicalResult WrapValidReadyOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    return ::mlir::success();
}

WrapValidReadyOp WrapValidReadyOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, mlir::Value data, mlir::Value valid) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(data)>(data), std::forward<decltype(valid)>(valid));
  auto __res__ = ::llvm::dyn_cast<WrapValidReadyOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

WrapValidReadyOp WrapValidReadyOp::create(::mlir::ImplicitLocOpBuilder &builder, mlir::Value data, mlir::Value valid) {
  return create(builder, builder.getLoc(), std::forward<decltype(data)>(data), std::forward<decltype(valid)>(valid));
}

void WrapValidReadyOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type chanOutput, ::mlir::Type ready, ::mlir::Value rawInput, ::mlir::Value valid) {
  odsState.addOperands(rawInput);
  odsState.addOperands(valid);
  odsState.addTypes(chanOutput);
  odsState.addTypes(ready);
}

WrapValidReadyOp WrapValidReadyOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type chanOutput, ::mlir::Type ready, ::mlir::Value rawInput, ::mlir::Value valid) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(chanOutput)>(chanOutput), std::forward<decltype(ready)>(ready), std::forward<decltype(rawInput)>(rawInput), std::forward<decltype(valid)>(valid));
  auto __res__ = ::llvm::dyn_cast<WrapValidReadyOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

WrapValidReadyOp WrapValidReadyOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type chanOutput, ::mlir::Type ready, ::mlir::Value rawInput, ::mlir::Value valid) {
  return create(builder, builder.getLoc(), std::forward<decltype(chanOutput)>(chanOutput), std::forward<decltype(ready)>(ready), std::forward<decltype(rawInput)>(rawInput), std::forward<decltype(valid)>(valid));
}

void WrapValidReadyOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value rawInput, ::mlir::Value valid) {
  odsState.addOperands(rawInput);
  odsState.addOperands(valid);
  assert(resultTypes.size() == 2u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

WrapValidReadyOp WrapValidReadyOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value rawInput, ::mlir::Value valid) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(rawInput)>(rawInput), std::forward<decltype(valid)>(valid));
  auto __res__ = ::llvm::dyn_cast<WrapValidReadyOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

WrapValidReadyOp WrapValidReadyOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value rawInput, ::mlir::Value valid) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(rawInput)>(rawInput), std::forward<decltype(valid)>(valid));
}

void WrapValidReadyOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 2u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 2u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

WrapValidReadyOp WrapValidReadyOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<WrapValidReadyOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

WrapValidReadyOp WrapValidReadyOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void WrapValidReadyOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 2u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 2u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

WrapValidReadyOp WrapValidReadyOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<WrapValidReadyOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

WrapValidReadyOp WrapValidReadyOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult WrapValidReadyOp::verifyInvariantsImpl() {
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_ESI4(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSOperands(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_ESI2(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_ESI3(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSResults(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_ESI2(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult WrapValidReadyOp::verifyInvariants() {
  if(::mlir::succeeded(verifyInvariantsImpl()) && ::mlir::succeeded(verify()))
    return ::mlir::success();
  return ::mlir::failure();
}

void WrapValidReadyOp::getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context) {
  results.add(canonicalize);
}

::llvm::LogicalResult WrapValidReadyOp::setPropertiesFromParsedAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
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


} // namespace circt::esi
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::esi::WrapValidReadyOp)

namespace circt::esi {


//===----------------------------------------------------------------------===//
// ::circt::esi::WrapWindow definitions
//===----------------------------------------------------------------------===//

namespace detail {

WrapWindowGenericAdaptorBase::WrapWindowGenericAdaptorBase(WrapWindow op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}


} // namespace detail
WrapWindowAdaptor::WrapWindowAdaptor(WrapWindow op) : WrapWindowGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult WrapWindowAdaptor::verify(::mlir::Location loc) {
  return ::mlir::success();
}

::llvm::LogicalResult WrapWindow::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }
      return ::mlir::success();
}

::mlir::Attribute WrapWindow::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code WrapWindow::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine();
}

std::optional<mlir::Attribute> WrapWindow::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
  return std::nullopt;
}

void WrapWindow::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
}

void WrapWindow::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
}

::llvm::LogicalResult WrapWindow::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    return ::mlir::success();
}

void WrapWindow::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type window, ::mlir::Value frame) {
  odsState.addOperands(frame);
  odsState.addTypes(window);
}

WrapWindow WrapWindow::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type window, ::mlir::Value frame) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(window)>(window), std::forward<decltype(frame)>(frame));
  auto __res__ = ::llvm::dyn_cast<WrapWindow>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

WrapWindow WrapWindow::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type window, ::mlir::Value frame) {
  return create(builder, builder.getLoc(), std::forward<decltype(window)>(window), std::forward<decltype(frame)>(frame));
}

void WrapWindow::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value frame) {
  odsState.addOperands(frame);
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

WrapWindow WrapWindow::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value frame) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(frame)>(frame));
  auto __res__ = ::llvm::dyn_cast<WrapWindow>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

WrapWindow WrapWindow::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value frame) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(frame)>(frame));
}

void WrapWindow::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

WrapWindow WrapWindow::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<WrapWindow>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

WrapWindow WrapWindow::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void WrapWindow::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

WrapWindow WrapWindow::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<WrapWindow>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

WrapWindow WrapWindow::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult WrapWindow::verifyInvariantsImpl() {
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_ESI4(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_ESI9(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult WrapWindow::verifyInvariants() {
  if(::mlir::succeeded(verifyInvariantsImpl()) && ::mlir::succeeded(verify()))
    return ::mlir::success();
  return ::mlir::failure();
}

void WrapWindow::getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context) {
  results.add(canonicalize);
}

::mlir::ParseResult WrapWindow::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::OpAsmParser::UnresolvedOperand frameRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> frameOperands(&frameRawOperand, 1);  ::llvm::SMLoc frameOperandsLoc;
  (void)frameOperandsLoc;
  ::mlir::Type frameRawType{};
  ::llvm::ArrayRef<::mlir::Type> frameTypes(&frameRawType, 1);
  ::mlir::Type windowRawType{};
  ::llvm::ArrayRef<::mlir::Type> windowTypes(&windowRawType, 1);

  frameOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(frameRawOperand))
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
    auto odsResult = parseInferWindowRet(parser, frameRawType, windowRawType);
    if (odsResult) return ::mlir::failure();
  }
  result.addTypes(windowTypes);
  if (parser.resolveOperands(frameOperands, frameTypes, frameOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void WrapWindow::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter << getFrame();
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
  printInferWindowRet(_odsPrinter, *this, getFrame().getType(), getWindow().getType());
}

void WrapWindow::getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects) {
}


} // namespace circt::esi
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::esi::WrapWindow)


#endif // GET_OP_CLASSES

