/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Op Definitions                                                             *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: CHIRRTL.td                                                           *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

#ifdef GET_OP_LIST
#undef GET_OP_LIST

::circt::chirrtl::CombMemOp,
::circt::chirrtl::MemoryDebugPortOp,
::circt::chirrtl::MemoryPortAccessOp,
::circt::chirrtl::MemoryPortOp,
::circt::chirrtl::SeqMemOp
#endif // GET_OP_LIST

#ifdef GET_OP_CLASSES
#undef GET_OP_CLASSES


//===----------------------------------------------------------------------===//
// Local Utility Method Definitions
//===----------------------------------------------------------------------===//


static ::llvm::LogicalResult __mlir_ods_local_type_constraint_CHIRRTL1(
    ::mlir::Operation *op, ::mlir::Type type, ::llvm::StringRef valueKind,
    unsigned valueIndex) {
  if (!((::llvm::isa<::circt::chirrtl::CMemoryType>(type)))) {
    return op->emitOpError(valueKind) << " #" << valueIndex
        << " must be a behavioral memory, but got " << type;
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_type_constraint_CHIRRTL2(
    ::mlir::Operation *op, ::mlir::Type type, ::llvm::StringRef valueKind,
    unsigned valueIndex) {
  if (!((isa<RefType>(type)))) {
    return op->emitOpError(valueKind) << " #" << valueIndex
        << " must be reference type, but got " << type;
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_type_constraint_CHIRRTL3(
    ::mlir::Operation *op, ::mlir::Type type, ::llvm::StringRef valueKind,
    unsigned valueIndex) {
  if (!((::llvm::isa<::circt::chirrtl::CMemoryPortType>(type)))) {
    return op->emitOpError(valueKind) << " #" << valueIndex
        << " must be a behavioral memory port, but got " << type;
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_type_constraint_CHIRRTL4(
    ::mlir::Operation *op, ::mlir::Type type, ::llvm::StringRef valueKind,
    unsigned valueIndex) {
  if (!((type_isa<IntType>(type)))) {
    return op->emitOpError(valueKind) << " #" << valueIndex
        << " must be sint or uint type, but got " << type;
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_type_constraint_CHIRRTL5(
    ::mlir::Operation *op, ::mlir::Type type, ::llvm::StringRef valueKind,
    unsigned valueIndex) {
  if (!((type_isa<ClockType>(type)))) {
    return op->emitOpError(valueKind) << " #" << valueIndex
        << " must be clock, but got " << type;
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_type_constraint_CHIRRTL6(
    ::mlir::Operation *op, ::mlir::Type type, ::llvm::StringRef valueKind,
    unsigned valueIndex) {
  if (!((llvm::isa<FIRRTLBaseType>(type)))) {
    return op->emitOpError(valueKind) << " #" << valueIndex
        << " must be a base type, but got " << type;
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_CHIRRTL1(
    ::mlir::Attribute attr, ::llvm::StringRef attrName, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  if (attr && !((::llvm::isa<::mlir::StringAttr>(attr))))
    return emitError() << "attribute '" << attrName
        << "' failed to satisfy constraint: string attribute";
  return ::mlir::success();
}
static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_CHIRRTL1(
    ::mlir::Operation *op, ::mlir::Attribute attr, ::llvm::StringRef attrName) {
  return __mlir_ods_local_attr_constraint_CHIRRTL1(attr, attrName, [op]() {
    return op->emitOpError();
  });
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_CHIRRTL2(
    ::mlir::Attribute attr, ::llvm::StringRef attrName, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  if (attr && !((::llvm::isa<::circt::firrtl::NameKindEnumAttr>(attr))))
    return emitError() << "attribute '" << attrName
        << "' failed to satisfy constraint: name kind";
  return ::mlir::success();
}
static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_CHIRRTL2(
    ::mlir::Operation *op, ::mlir::Attribute attr, ::llvm::StringRef attrName) {
  return __mlir_ods_local_attr_constraint_CHIRRTL2(attr, attrName, [op]() {
    return op->emitOpError();
  });
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_CHIRRTL3(
    ::mlir::Attribute attr, ::llvm::StringRef attrName, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  if (attr && !(((::llvm::isa<::mlir::ArrayAttr>(attr))) && (::llvm::all_of(::llvm::cast<::mlir::ArrayAttr>(attr), [&](::mlir::Attribute attr) { return attr && ((::llvm::isa<::mlir::DictionaryAttr>(attr))); }))))
    return emitError() << "attribute '" << attrName
        << "' failed to satisfy constraint: Annotation array attribute";
  return ::mlir::success();
}
static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_CHIRRTL3(
    ::mlir::Operation *op, ::mlir::Attribute attr, ::llvm::StringRef attrName) {
  return __mlir_ods_local_attr_constraint_CHIRRTL3(attr, attrName, [op]() {
    return op->emitOpError();
  });
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_CHIRRTL4(
    ::mlir::Attribute attr, ::llvm::StringRef attrName, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  if (attr && !((::llvm::isa<::circt::hw::InnerSymAttr>(attr))))
    return emitError() << "attribute '" << attrName
        << "' failed to satisfy constraint: Inner symbol definition";
  return ::mlir::success();
}
static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_CHIRRTL4(
    ::mlir::Operation *op, ::mlir::Attribute attr, ::llvm::StringRef attrName) {
  return __mlir_ods_local_attr_constraint_CHIRRTL4(attr, attrName, [op]() {
    return op->emitOpError();
  });
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_CHIRRTL5(
    ::mlir::Attribute attr, ::llvm::StringRef attrName, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  if (attr && !((::llvm::isa<::circt::firrtl::MemoryInitAttr>(attr))))
    return emitError() << "attribute '" << attrName
        << "' failed to satisfy constraint: Information about the initial state of a memory";
  return ::mlir::success();
}
static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_CHIRRTL5(
    ::mlir::Operation *op, ::mlir::Attribute attr, ::llvm::StringRef attrName) {
  return __mlir_ods_local_attr_constraint_CHIRRTL5(attr, attrName, [op]() {
    return op->emitOpError();
  });
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_CHIRRTL6(
    ::mlir::Attribute attr, ::llvm::StringRef attrName, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  if (attr && !((::llvm::isa<::circt::firrtl::MemDirAttrAttr>(attr))))
    return emitError() << "attribute '" << attrName
        << "' failed to satisfy constraint: Memory Direction Enum";
  return ::mlir::success();
}
static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_CHIRRTL6(
    ::mlir::Operation *op, ::mlir::Attribute attr, ::llvm::StringRef attrName) {
  return __mlir_ods_local_attr_constraint_CHIRRTL6(attr, attrName, [op]() {
    return op->emitOpError();
  });
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_CHIRRTL7(
    ::mlir::Attribute attr, ::llvm::StringRef attrName, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  if (attr && !((::llvm::isa<::circt::firrtl::RUWBehaviorAttr>(attr))))
    return emitError() << "attribute '" << attrName
        << "' failed to satisfy constraint: read under write behavior";
  return ::mlir::success();
}
static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_CHIRRTL7(
    ::mlir::Operation *op, ::mlir::Attribute attr, ::llvm::StringRef attrName) {
  return __mlir_ods_local_attr_constraint_CHIRRTL7(attr, attrName, [op]() {
    return op->emitOpError();
  });
}
namespace circt::chirrtl {


//===----------------------------------------------------------------------===//
// ::circt::chirrtl::CombMemOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

CombMemOpGenericAdaptorBase::CombMemOpGenericAdaptorBase(CombMemOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::llvm::StringRef CombMemOpGenericAdaptorBase::getName() {
  auto attr = getNameAttr();
  return attr.getValue();
}

::circt::firrtl::NameKindEnum CombMemOpGenericAdaptorBase::getNameKind() {
  auto attr = getNameKindAttr();
  return attr.getValue();
}

::mlir::ArrayAttr CombMemOpGenericAdaptorBase::getAnnotations() {
  auto attr = getAnnotationsAttr();
  return attr;
}

::std::optional<::circt::hw::InnerSymAttr> CombMemOpGenericAdaptorBase::getInnerSym() {
  auto attr = getInnerSymAttr();
  return attr ? ::std::optional<::circt::hw::InnerSymAttr>(::llvm::cast<::circt::hw::InnerSymAttr>(attr)) : (::std::nullopt);
}

::std::optional<::circt::firrtl::MemoryInitAttr> CombMemOpGenericAdaptorBase::getInit() {
  auto attr = getInitAttr();
  return attr ? ::std::optional<::circt::firrtl::MemoryInitAttr>(::llvm::cast<::circt::firrtl::MemoryInitAttr>(attr)) : (::std::nullopt);
}

::std::optional< ::llvm::StringRef > CombMemOpGenericAdaptorBase::getPrefix() {
  auto attr = getPrefixAttr();
  return attr ? ::std::optional< ::llvm::StringRef >(attr.getValue()) : (::std::nullopt);
}


} // namespace detail
CombMemOpAdaptor::CombMemOpAdaptor(CombMemOp op) : CombMemOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult CombMemOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_annotations = getProperties().annotations; (void)tblgen_annotations;
  if (!tblgen_annotations) return emitError(loc, "'chirrtl.combmem' op requires attribute 'annotations'");
  auto tblgen_init = getProperties().init; (void)tblgen_init;
  auto tblgen_inner_sym = getProperties().inner_sym; (void)tblgen_inner_sym;
  auto tblgen_name = getProperties().name; (void)tblgen_name;
  if (!tblgen_name) return emitError(loc, "'chirrtl.combmem' op requires attribute 'name'");
  auto tblgen_nameKind = getProperties().nameKind; (void)tblgen_nameKind;
  if (!tblgen_nameKind) return emitError(loc, "'chirrtl.combmem' op requires attribute 'nameKind'");
  auto tblgen_prefix = getProperties().prefix; (void)tblgen_prefix;

  if (tblgen_name && !((::llvm::isa<::mlir::StringAttr>(tblgen_name))))
    return emitError(loc, "'chirrtl.combmem' op attribute 'name' failed to satisfy constraint: string attribute");

  if (tblgen_nameKind && !((::llvm::isa<::circt::firrtl::NameKindEnumAttr>(tblgen_nameKind))))
    return emitError(loc, "'chirrtl.combmem' op attribute 'nameKind' failed to satisfy constraint: name kind");

  if (tblgen_annotations && !(((::llvm::isa<::mlir::ArrayAttr>(tblgen_annotations))) && (::llvm::all_of(::llvm::cast<::mlir::ArrayAttr>(tblgen_annotations), [&](::mlir::Attribute attr) { return attr && ((::llvm::isa<::mlir::DictionaryAttr>(attr))); }))))
    return emitError(loc, "'chirrtl.combmem' op attribute 'annotations' failed to satisfy constraint: Annotation array attribute");

  if (tblgen_inner_sym && !((::llvm::isa<::circt::hw::InnerSymAttr>(tblgen_inner_sym))))
    return emitError(loc, "'chirrtl.combmem' op attribute 'inner_sym' failed to satisfy constraint: Inner symbol definition");

  if (tblgen_init && !((::llvm::isa<::circt::firrtl::MemoryInitAttr>(tblgen_init))))
    return emitError(loc, "'chirrtl.combmem' op attribute 'init' failed to satisfy constraint: Information about the initial state of a memory");

  if (tblgen_prefix && !((::llvm::isa<::mlir::StringAttr>(tblgen_prefix))))
    return emitError(loc, "'chirrtl.combmem' op attribute 'prefix' failed to satisfy constraint: string attribute");
  return ::mlir::success();
}

::llvm::LogicalResult CombMemOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.annotations;
       auto attr = dict.get("annotations");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `annotations` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
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
    auto &propStorage = prop.nameKind;
       auto attr = dict.get("nameKind");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `nameKind` in property conversion: " << attr;
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
  return ::mlir::success();
}

::mlir::Attribute CombMemOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.annotations;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("annotations",
                                       propStorage));
    }

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
      const auto &propStorage = prop.nameKind;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("nameKind",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.prefix;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("prefix",
                                       propStorage));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code CombMemOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.annotations.getAsOpaquePointer()), 
    llvm::hash_value(prop.init.getAsOpaquePointer()), 
    llvm::hash_value(prop.inner_sym.getAsOpaquePointer()), 
    llvm::hash_value(prop.name.getAsOpaquePointer()), 
    llvm::hash_value(prop.nameKind.getAsOpaquePointer()), 
    llvm::hash_value(prop.prefix.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> CombMemOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "annotations")
      return prop.annotations;

    if (name == "init")
      return prop.init;

    if (name == "inner_sym")
      return prop.inner_sym;

    if (name == "name")
      return prop.name;

    if (name == "nameKind")
      return prop.nameKind;

    if (name == "prefix")
      return prop.prefix;
  return std::nullopt;
}

void CombMemOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "annotations") {
       prop.annotations = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.annotations)>>(value);
       return;
    }

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

    if (name == "nameKind") {
       prop.nameKind = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.nameKind)>>(value);
       return;
    }

    if (name == "prefix") {
       prop.prefix = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.prefix)>>(value);
       return;
    }
}

void CombMemOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.annotations) attrs.append("annotations", prop.annotations);

    if (prop.init) attrs.append("init", prop.init);

    if (prop.inner_sym) attrs.append("inner_sym", prop.inner_sym);

    if (prop.name) attrs.append("name", prop.name);

    if (prop.nameKind) attrs.append("nameKind", prop.nameKind);

    if (prop.prefix) attrs.append("prefix", prop.prefix);
}

::llvm::LogicalResult CombMemOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getAnnotationsAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_CHIRRTL3(attr, "annotations", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getInitAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_CHIRRTL5(attr, "init", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getInnerSymAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_CHIRRTL4(attr, "inner_sym", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getNameAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_CHIRRTL1(attr, "name", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getNameKindAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_CHIRRTL2(attr, "nameKind", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getPrefixAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_CHIRRTL1(attr, "prefix", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult CombMemOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.annotations)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readOptionalAttribute(prop.init)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readOptionalAttribute(prop.inner_sym)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readAttribute(prop.name)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readAttribute(prop.nameKind)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readOptionalAttribute(prop.prefix)))
    return ::mlir::failure();
  return ::mlir::success();
}

void CombMemOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.annotations);

  writer.writeOptionalAttribute(prop.init);

  writer.writeOptionalAttribute(prop.inner_sym);
  writer.writeAttribute(prop.name);
  writer.writeAttribute(prop.nameKind);

  writer.writeOptionalAttribute(prop.prefix);
}

::llvm::StringRef CombMemOp::getName() {
  auto attr = getNameAttr();
  return attr.getValue();
}

::circt::firrtl::NameKindEnum CombMemOp::getNameKind() {
  auto attr = getNameKindAttr();
  return attr.getValue();
}

::mlir::ArrayAttr CombMemOp::getAnnotations() {
  auto attr = getAnnotationsAttr();
  return attr;
}

::std::optional<::circt::hw::InnerSymAttr> CombMemOp::getInnerSym() {
  auto attr = getInnerSymAttr();
  return attr ? ::std::optional<::circt::hw::InnerSymAttr>(::llvm::cast<::circt::hw::InnerSymAttr>(attr)) : (::std::nullopt);
}

::std::optional<::circt::firrtl::MemoryInitAttr> CombMemOp::getInit() {
  auto attr = getInitAttr();
  return attr ? ::std::optional<::circt::firrtl::MemoryInitAttr>(::llvm::cast<::circt::firrtl::MemoryInitAttr>(attr)) : (::std::nullopt);
}

::std::optional< ::llvm::StringRef > CombMemOp::getPrefix() {
  auto attr = getPrefixAttr();
  return attr ? ::std::optional< ::llvm::StringRef >(attr.getValue()) : (::std::nullopt);
}

void CombMemOp::setName(::llvm::StringRef attrValue) {
  getProperties().name = ::mlir::Builder((*this)->getContext()).getStringAttr(attrValue);
}

void CombMemOp::setNameKind(::circt::firrtl::NameKindEnum attrValue) {
  getProperties().nameKind = ::circt::firrtl::NameKindEnumAttr::get(::mlir::Builder((*this)->getContext()).getContext(), attrValue);
}

void CombMemOp::setPrefix(::std::optional<::llvm::StringRef> attrValue) {
    auto &odsProp = getProperties().prefix;
    if (attrValue)
      odsProp = ::mlir::Builder((*this)->getContext()).getStringAttr(*attrValue);
    else
      odsProp = nullptr;
}

CombMemOp CombMemOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, firrtl::FIRRTLBaseType elementType, uint64_t numElements, mlir::StringRef name, firrtl::NameKindEnum nameKind, ArrayAttr annotations, StringAttr innerSym, firrtl::MemoryInitAttr init) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(elementType)>(elementType), std::forward<decltype(numElements)>(numElements), std::forward<decltype(name)>(name), std::forward<decltype(nameKind)>(nameKind), std::forward<decltype(annotations)>(annotations), std::forward<decltype(innerSym)>(innerSym), std::forward<decltype(init)>(init));
  auto __res__ = ::llvm::dyn_cast<CombMemOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

CombMemOp CombMemOp::create(::mlir::ImplicitLocOpBuilder &builder, firrtl::FIRRTLBaseType elementType, uint64_t numElements, mlir::StringRef name, firrtl::NameKindEnum nameKind, ArrayAttr annotations, StringAttr innerSym, firrtl::MemoryInitAttr init) {
  return create(builder, builder.getLoc(), std::forward<decltype(elementType)>(elementType), std::forward<decltype(numElements)>(numElements), std::forward<decltype(name)>(name), std::forward<decltype(nameKind)>(nameKind), std::forward<decltype(annotations)>(annotations), std::forward<decltype(innerSym)>(innerSym), std::forward<decltype(init)>(init));
}

void CombMemOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::StringAttr name, ::circt::firrtl::NameKindEnumAttr nameKind, ::mlir::ArrayAttr annotations, /*optional*/::circt::hw::InnerSymAttr inner_sym, /*optional*/::circt::firrtl::MemoryInitAttr init, /*optional*/::mlir::StringAttr prefix) {
  odsState.getOrAddProperties<Properties>().name = name;
  odsState.getOrAddProperties<Properties>().nameKind = nameKind;
  odsState.getOrAddProperties<Properties>().annotations = annotations;
  if (inner_sym) {
    odsState.getOrAddProperties<Properties>().inner_sym = inner_sym;
  }
  if (init) {
    odsState.getOrAddProperties<Properties>().init = init;
  }
  if (prefix) {
    odsState.getOrAddProperties<Properties>().prefix = prefix;
  }
  odsState.addTypes(result);
}

CombMemOp CombMemOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::StringAttr name, ::circt::firrtl::NameKindEnumAttr nameKind, ::mlir::ArrayAttr annotations, /*optional*/::circt::hw::InnerSymAttr inner_sym, /*optional*/::circt::firrtl::MemoryInitAttr init, /*optional*/::mlir::StringAttr prefix) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(result)>(result), std::forward<decltype(name)>(name), std::forward<decltype(nameKind)>(nameKind), std::forward<decltype(annotations)>(annotations), std::forward<decltype(inner_sym)>(inner_sym), std::forward<decltype(init)>(init), std::forward<decltype(prefix)>(prefix));
  auto __res__ = ::llvm::dyn_cast<CombMemOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

CombMemOp CombMemOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::StringAttr name, ::circt::firrtl::NameKindEnumAttr nameKind, ::mlir::ArrayAttr annotations, /*optional*/::circt::hw::InnerSymAttr inner_sym, /*optional*/::circt::firrtl::MemoryInitAttr init, /*optional*/::mlir::StringAttr prefix) {
  return create(builder, builder.getLoc(), std::forward<decltype(result)>(result), std::forward<decltype(name)>(name), std::forward<decltype(nameKind)>(nameKind), std::forward<decltype(annotations)>(annotations), std::forward<decltype(inner_sym)>(inner_sym), std::forward<decltype(init)>(init), std::forward<decltype(prefix)>(prefix));
}

void CombMemOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::StringAttr name, ::circt::firrtl::NameKindEnumAttr nameKind, ::mlir::ArrayAttr annotations, /*optional*/::circt::hw::InnerSymAttr inner_sym, /*optional*/::circt::firrtl::MemoryInitAttr init, /*optional*/::mlir::StringAttr prefix) {
  odsState.getOrAddProperties<Properties>().name = name;
  odsState.getOrAddProperties<Properties>().nameKind = nameKind;
  odsState.getOrAddProperties<Properties>().annotations = annotations;
  if (inner_sym) {
    odsState.getOrAddProperties<Properties>().inner_sym = inner_sym;
  }
  if (init) {
    odsState.getOrAddProperties<Properties>().init = init;
  }
  if (prefix) {
    odsState.getOrAddProperties<Properties>().prefix = prefix;
  }
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

CombMemOp CombMemOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::StringAttr name, ::circt::firrtl::NameKindEnumAttr nameKind, ::mlir::ArrayAttr annotations, /*optional*/::circt::hw::InnerSymAttr inner_sym, /*optional*/::circt::firrtl::MemoryInitAttr init, /*optional*/::mlir::StringAttr prefix) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(name)>(name), std::forward<decltype(nameKind)>(nameKind), std::forward<decltype(annotations)>(annotations), std::forward<decltype(inner_sym)>(inner_sym), std::forward<decltype(init)>(init), std::forward<decltype(prefix)>(prefix));
  auto __res__ = ::llvm::dyn_cast<CombMemOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

CombMemOp CombMemOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::StringAttr name, ::circt::firrtl::NameKindEnumAttr nameKind, ::mlir::ArrayAttr annotations, /*optional*/::circt::hw::InnerSymAttr inner_sym, /*optional*/::circt::firrtl::MemoryInitAttr init, /*optional*/::mlir::StringAttr prefix) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(name)>(name), std::forward<decltype(nameKind)>(nameKind), std::forward<decltype(annotations)>(annotations), std::forward<decltype(inner_sym)>(inner_sym), std::forward<decltype(init)>(init), std::forward<decltype(prefix)>(prefix));
}

void CombMemOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::llvm::StringRef name, ::circt::firrtl::NameKindEnum nameKind, ::mlir::ArrayAttr annotations, /*optional*/::circt::hw::InnerSymAttr inner_sym, /*optional*/::circt::firrtl::MemoryInitAttr init, /*optional*/::mlir::StringAttr prefix) {
  odsState.getOrAddProperties<Properties>().name = odsBuilder.getStringAttr(name);
  odsState.getOrAddProperties<Properties>().nameKind = ::circt::firrtl::NameKindEnumAttr::get(odsBuilder.getContext(), nameKind);
  odsState.getOrAddProperties<Properties>().annotations = annotations;
  if (inner_sym) {
    odsState.getOrAddProperties<Properties>().inner_sym = inner_sym;
  }
  if (init) {
    odsState.getOrAddProperties<Properties>().init = init;
  }
  if (prefix) {
    odsState.getOrAddProperties<Properties>().prefix = prefix;
  }
  odsState.addTypes(result);
}

CombMemOp CombMemOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::llvm::StringRef name, ::circt::firrtl::NameKindEnum nameKind, ::mlir::ArrayAttr annotations, /*optional*/::circt::hw::InnerSymAttr inner_sym, /*optional*/::circt::firrtl::MemoryInitAttr init, /*optional*/::mlir::StringAttr prefix) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(result)>(result), std::forward<decltype(name)>(name), std::forward<decltype(nameKind)>(nameKind), std::forward<decltype(annotations)>(annotations), std::forward<decltype(inner_sym)>(inner_sym), std::forward<decltype(init)>(init), std::forward<decltype(prefix)>(prefix));
  auto __res__ = ::llvm::dyn_cast<CombMemOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

CombMemOp CombMemOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::llvm::StringRef name, ::circt::firrtl::NameKindEnum nameKind, ::mlir::ArrayAttr annotations, /*optional*/::circt::hw::InnerSymAttr inner_sym, /*optional*/::circt::firrtl::MemoryInitAttr init, /*optional*/::mlir::StringAttr prefix) {
  return create(builder, builder.getLoc(), std::forward<decltype(result)>(result), std::forward<decltype(name)>(name), std::forward<decltype(nameKind)>(nameKind), std::forward<decltype(annotations)>(annotations), std::forward<decltype(inner_sym)>(inner_sym), std::forward<decltype(init)>(init), std::forward<decltype(prefix)>(prefix));
}

void CombMemOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::llvm::StringRef name, ::circt::firrtl::NameKindEnum nameKind, ::mlir::ArrayAttr annotations, /*optional*/::circt::hw::InnerSymAttr inner_sym, /*optional*/::circt::firrtl::MemoryInitAttr init, /*optional*/::mlir::StringAttr prefix) {
  odsState.getOrAddProperties<Properties>().name = odsBuilder.getStringAttr(name);
  odsState.getOrAddProperties<Properties>().nameKind = ::circt::firrtl::NameKindEnumAttr::get(odsBuilder.getContext(), nameKind);
  odsState.getOrAddProperties<Properties>().annotations = annotations;
  if (inner_sym) {
    odsState.getOrAddProperties<Properties>().inner_sym = inner_sym;
  }
  if (init) {
    odsState.getOrAddProperties<Properties>().init = init;
  }
  if (prefix) {
    odsState.getOrAddProperties<Properties>().prefix = prefix;
  }
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

CombMemOp CombMemOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::llvm::StringRef name, ::circt::firrtl::NameKindEnum nameKind, ::mlir::ArrayAttr annotations, /*optional*/::circt::hw::InnerSymAttr inner_sym, /*optional*/::circt::firrtl::MemoryInitAttr init, /*optional*/::mlir::StringAttr prefix) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(name)>(name), std::forward<decltype(nameKind)>(nameKind), std::forward<decltype(annotations)>(annotations), std::forward<decltype(inner_sym)>(inner_sym), std::forward<decltype(init)>(init), std::forward<decltype(prefix)>(prefix));
  auto __res__ = ::llvm::dyn_cast<CombMemOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

CombMemOp CombMemOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::llvm::StringRef name, ::circt::firrtl::NameKindEnum nameKind, ::mlir::ArrayAttr annotations, /*optional*/::circt::hw::InnerSymAttr inner_sym, /*optional*/::circt::firrtl::MemoryInitAttr init, /*optional*/::mlir::StringAttr prefix) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(name)>(name), std::forward<decltype(nameKind)>(nameKind), std::forward<decltype(annotations)>(annotations), std::forward<decltype(inner_sym)>(inner_sym), std::forward<decltype(init)>(init), std::forward<decltype(prefix)>(prefix));
}

void CombMemOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<CombMemOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

CombMemOp CombMemOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<CombMemOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

CombMemOp CombMemOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void CombMemOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

CombMemOp CombMemOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<CombMemOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

CombMemOp CombMemOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult CombMemOp::verifyInvariantsImpl() {
  auto tblgen_annotations = getProperties().annotations; (void)tblgen_annotations;
  if (!tblgen_annotations) return emitOpError("requires attribute 'annotations'");
  auto tblgen_init = getProperties().init; (void)tblgen_init;
  auto tblgen_inner_sym = getProperties().inner_sym; (void)tblgen_inner_sym;
  auto tblgen_name = getProperties().name; (void)tblgen_name;
  if (!tblgen_name) return emitOpError("requires attribute 'name'");
  auto tblgen_nameKind = getProperties().nameKind; (void)tblgen_nameKind;
  if (!tblgen_nameKind) return emitOpError("requires attribute 'nameKind'");
  auto tblgen_prefix = getProperties().prefix; (void)tblgen_prefix;

  if (::mlir::failed(__mlir_ods_local_attr_constraint_CHIRRTL1(*this, tblgen_name, "name")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_CHIRRTL2(*this, tblgen_nameKind, "nameKind")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_CHIRRTL3(*this, tblgen_annotations, "annotations")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_CHIRRTL4(*this, tblgen_inner_sym, "inner_sym")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_CHIRRTL5(*this, tblgen_init, "init")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_CHIRRTL1(*this, tblgen_prefix, "prefix")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_CHIRRTL1(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult CombMemOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult CombMemOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::circt::hw::InnerSymAttr inner_symAttr;
  ::circt::firrtl::NameKindEnumAttr nameKindAttr;
  ::mlir::Type resultRawType{};
  ::llvm::ArrayRef<::mlir::Type> resultTypes(&resultRawType, 1);
  if (::mlir::succeeded(parser.parseOptionalKeyword("sym"))) {

  if (parser.parseCustomAttributeWithFallback(inner_symAttr, ::mlir::Type{})) {
    return ::mlir::failure();
  }
  if (inner_symAttr) result.getOrAddProperties<CombMemOp::Properties>().inner_sym = inner_symAttr;
  }
  {
    auto odsResult = parseNameKind(parser, nameKindAttr);
    if (odsResult) return ::mlir::failure();
    result.getOrAddProperties<CombMemOp::Properties>().nameKind = nameKindAttr;
  }
  {
    auto odsResult = parseCombMemOp(parser, result.attributes);
    if (odsResult) return ::mlir::failure();
  }
  if (parser.parseColon())
    return ::mlir::failure();

  if (parser.parseType(resultRawType))
    return ::mlir::failure();
  result.addTypes(resultTypes);
  return ::mlir::success();
}

void CombMemOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  if (getInnerSymAttr()) {
    _odsPrinter << ' ' << "sym";
    _odsPrinter << ' ';
  _odsPrinter.printStrippedAttrOrType(getInnerSymAttr());
  }
  printNameKind(_odsPrinter, *this, getNameKindAttr());
  printCombMemOp(_odsPrinter, *this, getOperation()->getAttrDictionary());
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
   _odsPrinter << getResult().getType();
}


} // namespace circt::chirrtl
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::chirrtl::CombMemOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::chirrtl::detail::CombMemOpGenericAdaptorBase::Properties)

namespace circt::chirrtl {


//===----------------------------------------------------------------------===//
// ::circt::chirrtl::MemoryDebugPortOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

MemoryDebugPortOpGenericAdaptorBase::MemoryDebugPortOpGenericAdaptorBase(MemoryDebugPortOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::llvm::StringRef MemoryDebugPortOpGenericAdaptorBase::getName() {
  auto attr = getNameAttr();
  return attr.getValue();
}

::mlir::ArrayAttr MemoryDebugPortOpGenericAdaptorBase::getAnnotations() {
  auto attr = getAnnotationsAttr();
  return attr;
}


} // namespace detail
MemoryDebugPortOpAdaptor::MemoryDebugPortOpAdaptor(MemoryDebugPortOp op) : MemoryDebugPortOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult MemoryDebugPortOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_annotations = getProperties().annotations; (void)tblgen_annotations;
  if (!tblgen_annotations) return emitError(loc, "'chirrtl.debugport' op requires attribute 'annotations'");
  auto tblgen_name = getProperties().name; (void)tblgen_name;
  if (!tblgen_name) return emitError(loc, "'chirrtl.debugport' op requires attribute 'name'");

  if (tblgen_name && !((::llvm::isa<::mlir::StringAttr>(tblgen_name))))
    return emitError(loc, "'chirrtl.debugport' op attribute 'name' failed to satisfy constraint: string attribute");

  if (tblgen_annotations && !(((::llvm::isa<::mlir::ArrayAttr>(tblgen_annotations))) && (::llvm::all_of(::llvm::cast<::mlir::ArrayAttr>(tblgen_annotations), [&](::mlir::Attribute attr) { return attr && ((::llvm::isa<::mlir::DictionaryAttr>(attr))); }))))
    return emitError(loc, "'chirrtl.debugport' op attribute 'annotations' failed to satisfy constraint: Annotation array attribute");
  return ::mlir::success();
}

::llvm::LogicalResult MemoryDebugPortOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.annotations;
       auto attr = dict.get("annotations");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `annotations` in property conversion: " << attr;
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

::mlir::Attribute MemoryDebugPortOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.annotations;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("annotations",
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

llvm::hash_code MemoryDebugPortOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.annotations.getAsOpaquePointer()), 
    llvm::hash_value(prop.name.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> MemoryDebugPortOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "annotations")
      return prop.annotations;

    if (name == "name")
      return prop.name;
  return std::nullopt;
}

void MemoryDebugPortOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "annotations") {
       prop.annotations = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.annotations)>>(value);
       return;
    }

    if (name == "name") {
       prop.name = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.name)>>(value);
       return;
    }
}

void MemoryDebugPortOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.annotations) attrs.append("annotations", prop.annotations);

    if (prop.name) attrs.append("name", prop.name);
}

::llvm::LogicalResult MemoryDebugPortOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getAnnotationsAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_CHIRRTL3(attr, "annotations", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getNameAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_CHIRRTL1(attr, "name", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult MemoryDebugPortOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.annotations)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readAttribute(prop.name)))
    return ::mlir::failure();
  return ::mlir::success();
}

void MemoryDebugPortOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.annotations);
  writer.writeAttribute(prop.name);
}

::llvm::StringRef MemoryDebugPortOp::getName() {
  auto attr = getNameAttr();
  return attr.getValue();
}

::mlir::ArrayAttr MemoryDebugPortOp::getAnnotations() {
  auto attr = getAnnotationsAttr();
  return attr;
}

void MemoryDebugPortOp::setName(::llvm::StringRef attrValue) {
  getProperties().name = ::mlir::Builder((*this)->getContext()).getStringAttr(attrValue);
}

MemoryDebugPortOp MemoryDebugPortOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type dataType, ::mlir::Value memory, StringRef name, ArrayRef<Attribute> annotations) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(dataType)>(dataType), std::forward<decltype(memory)>(memory), std::forward<decltype(name)>(name), std::forward<decltype(annotations)>(annotations));
  auto __res__ = ::llvm::dyn_cast<MemoryDebugPortOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

MemoryDebugPortOp MemoryDebugPortOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type dataType, ::mlir::Value memory, StringRef name, ArrayRef<Attribute> annotations) {
  return create(builder, builder.getLoc(), std::forward<decltype(dataType)>(dataType), std::forward<decltype(memory)>(memory), std::forward<decltype(name)>(name), std::forward<decltype(annotations)>(annotations));
}

void MemoryDebugPortOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type data, ::mlir::Value memory, ::mlir::StringAttr name, ::mlir::ArrayAttr annotations) {
  odsState.addOperands(memory);
  odsState.getOrAddProperties<Properties>().name = name;
  odsState.getOrAddProperties<Properties>().annotations = annotations;
  odsState.addTypes(data);
}

MemoryDebugPortOp MemoryDebugPortOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type data, ::mlir::Value memory, ::mlir::StringAttr name, ::mlir::ArrayAttr annotations) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(data)>(data), std::forward<decltype(memory)>(memory), std::forward<decltype(name)>(name), std::forward<decltype(annotations)>(annotations));
  auto __res__ = ::llvm::dyn_cast<MemoryDebugPortOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

MemoryDebugPortOp MemoryDebugPortOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type data, ::mlir::Value memory, ::mlir::StringAttr name, ::mlir::ArrayAttr annotations) {
  return create(builder, builder.getLoc(), std::forward<decltype(data)>(data), std::forward<decltype(memory)>(memory), std::forward<decltype(name)>(name), std::forward<decltype(annotations)>(annotations));
}

void MemoryDebugPortOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value memory, ::mlir::StringAttr name, ::mlir::ArrayAttr annotations) {
  odsState.addOperands(memory);
  odsState.getOrAddProperties<Properties>().name = name;
  odsState.getOrAddProperties<Properties>().annotations = annotations;

        ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
        if (::mlir::succeeded(MemoryDebugPortOp::inferReturnTypes(odsBuilder.getContext(),
                      odsState.location, odsState.operands,
                      odsState.attributes.getDictionary(odsState.getContext()),
                      odsState.getRawProperties(),
                      odsState.regions, inferredReturnTypes)))
          odsState.addTypes(inferredReturnTypes);
        else
          ::mlir::detail::reportFatalInferReturnTypesError(odsState);
        
}

MemoryDebugPortOp MemoryDebugPortOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value memory, ::mlir::StringAttr name, ::mlir::ArrayAttr annotations) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(memory)>(memory), std::forward<decltype(name)>(name), std::forward<decltype(annotations)>(annotations));
  auto __res__ = ::llvm::dyn_cast<MemoryDebugPortOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

MemoryDebugPortOp MemoryDebugPortOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value memory, ::mlir::StringAttr name, ::mlir::ArrayAttr annotations) {
  return create(builder, builder.getLoc(), std::forward<decltype(memory)>(memory), std::forward<decltype(name)>(name), std::forward<decltype(annotations)>(annotations));
}

void MemoryDebugPortOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value memory, ::mlir::StringAttr name, ::mlir::ArrayAttr annotations) {
  odsState.addOperands(memory);
  odsState.getOrAddProperties<Properties>().name = name;
  odsState.getOrAddProperties<Properties>().annotations = annotations;
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

MemoryDebugPortOp MemoryDebugPortOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value memory, ::mlir::StringAttr name, ::mlir::ArrayAttr annotations) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(memory)>(memory), std::forward<decltype(name)>(name), std::forward<decltype(annotations)>(annotations));
  auto __res__ = ::llvm::dyn_cast<MemoryDebugPortOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

MemoryDebugPortOp MemoryDebugPortOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value memory, ::mlir::StringAttr name, ::mlir::ArrayAttr annotations) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(memory)>(memory), std::forward<decltype(name)>(name), std::forward<decltype(annotations)>(annotations));
}

void MemoryDebugPortOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type data, ::mlir::Value memory, ::llvm::StringRef name, ::mlir::ArrayAttr annotations) {
  odsState.addOperands(memory);
  odsState.getOrAddProperties<Properties>().name = odsBuilder.getStringAttr(name);
  odsState.getOrAddProperties<Properties>().annotations = annotations;
  odsState.addTypes(data);
}

MemoryDebugPortOp MemoryDebugPortOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type data, ::mlir::Value memory, ::llvm::StringRef name, ::mlir::ArrayAttr annotations) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(data)>(data), std::forward<decltype(memory)>(memory), std::forward<decltype(name)>(name), std::forward<decltype(annotations)>(annotations));
  auto __res__ = ::llvm::dyn_cast<MemoryDebugPortOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

MemoryDebugPortOp MemoryDebugPortOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type data, ::mlir::Value memory, ::llvm::StringRef name, ::mlir::ArrayAttr annotations) {
  return create(builder, builder.getLoc(), std::forward<decltype(data)>(data), std::forward<decltype(memory)>(memory), std::forward<decltype(name)>(name), std::forward<decltype(annotations)>(annotations));
}

void MemoryDebugPortOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value memory, ::llvm::StringRef name, ::mlir::ArrayAttr annotations) {
  odsState.addOperands(memory);
  odsState.getOrAddProperties<Properties>().name = odsBuilder.getStringAttr(name);
  odsState.getOrAddProperties<Properties>().annotations = annotations;

        ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
        if (::mlir::succeeded(MemoryDebugPortOp::inferReturnTypes(odsBuilder.getContext(),
                      odsState.location, odsState.operands,
                      odsState.attributes.getDictionary(odsState.getContext()),
                      odsState.getRawProperties(),
                      odsState.regions, inferredReturnTypes)))
          odsState.addTypes(inferredReturnTypes);
        else
          ::mlir::detail::reportFatalInferReturnTypesError(odsState);
        
}

MemoryDebugPortOp MemoryDebugPortOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value memory, ::llvm::StringRef name, ::mlir::ArrayAttr annotations) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(memory)>(memory), std::forward<decltype(name)>(name), std::forward<decltype(annotations)>(annotations));
  auto __res__ = ::llvm::dyn_cast<MemoryDebugPortOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

MemoryDebugPortOp MemoryDebugPortOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value memory, ::llvm::StringRef name, ::mlir::ArrayAttr annotations) {
  return create(builder, builder.getLoc(), std::forward<decltype(memory)>(memory), std::forward<decltype(name)>(name), std::forward<decltype(annotations)>(annotations));
}

void MemoryDebugPortOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value memory, ::llvm::StringRef name, ::mlir::ArrayAttr annotations) {
  odsState.addOperands(memory);
  odsState.getOrAddProperties<Properties>().name = odsBuilder.getStringAttr(name);
  odsState.getOrAddProperties<Properties>().annotations = annotations;
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

MemoryDebugPortOp MemoryDebugPortOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value memory, ::llvm::StringRef name, ::mlir::ArrayAttr annotations) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(memory)>(memory), std::forward<decltype(name)>(name), std::forward<decltype(annotations)>(annotations));
  auto __res__ = ::llvm::dyn_cast<MemoryDebugPortOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

MemoryDebugPortOp MemoryDebugPortOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value memory, ::llvm::StringRef name, ::mlir::ArrayAttr annotations) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(memory)>(memory), std::forward<decltype(name)>(name), std::forward<decltype(annotations)>(annotations));
}

void MemoryDebugPortOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<MemoryDebugPortOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

MemoryDebugPortOp MemoryDebugPortOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<MemoryDebugPortOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

MemoryDebugPortOp MemoryDebugPortOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void MemoryDebugPortOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<MemoryDebugPortOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
  ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
  if (::mlir::succeeded(MemoryDebugPortOp::inferReturnTypes(odsBuilder.getContext(),
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

MemoryDebugPortOp MemoryDebugPortOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<MemoryDebugPortOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

MemoryDebugPortOp MemoryDebugPortOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void MemoryDebugPortOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

MemoryDebugPortOp MemoryDebugPortOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<MemoryDebugPortOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

MemoryDebugPortOp MemoryDebugPortOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

void MemoryDebugPortOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties &>(properties));
  odsState.addAttributes(discardableAttributes);

  ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
  if (::mlir::succeeded(MemoryDebugPortOp::inferReturnTypes(odsBuilder.getContext(),
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

MemoryDebugPortOp MemoryDebugPortOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<MemoryDebugPortOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

MemoryDebugPortOp MemoryDebugPortOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult MemoryDebugPortOp::verifyInvariantsImpl() {
  auto tblgen_annotations = getProperties().annotations; (void)tblgen_annotations;
  if (!tblgen_annotations) return emitOpError("requires attribute 'annotations'");
  auto tblgen_name = getProperties().name; (void)tblgen_name;
  if (!tblgen_name) return emitOpError("requires attribute 'name'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_CHIRRTL1(*this, tblgen_name, "name")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_CHIRRTL3(*this, tblgen_annotations, "annotations")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_CHIRRTL1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_CHIRRTL2(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult MemoryDebugPortOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult MemoryDebugPortOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::OpAsmParser::UnresolvedOperand memoryRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> memoryOperands(&memoryRawOperand, 1);  ::llvm::SMLoc memoryOperandsLoc;
  (void)memoryOperandsLoc;
  ::llvm::ArrayRef<::mlir::Type> allOperandTypes;
  ::llvm::ArrayRef<::mlir::Type> allResultTypes;

  memoryOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(memoryRawOperand))
    return ::mlir::failure();
  {
    auto odsResult = parseMemoryDebugPortOp(parser, result.attributes);
    if (odsResult) return ::mlir::failure();
  }
  if (parser.parseColon())
    return ::mlir::failure();

  ::mlir::FunctionType allOperand__allResult_functionType;
  if (parser.parseType(allOperand__allResult_functionType))
    return ::mlir::failure();
  allOperandTypes = allOperand__allResult_functionType.getInputs();
  allResultTypes = allOperand__allResult_functionType.getResults();
  result.addTypes(allResultTypes);
  if (parser.resolveOperands(memoryOperands, allOperandTypes, parser.getNameLoc(), result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void MemoryDebugPortOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter << getMemory();
  _odsPrinter << ' ';
  printMemoryDebugPortOp(_odsPrinter, *this, getOperation()->getAttrDictionary());
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
  _odsPrinter.printFunctionalType(getOperation()->getOperandTypes(), getOperation()->getResultTypes());
}


} // namespace circt::chirrtl
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::chirrtl::MemoryDebugPortOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::chirrtl::detail::MemoryDebugPortOpGenericAdaptorBase::Properties)

namespace circt::chirrtl {


//===----------------------------------------------------------------------===//
// ::circt::chirrtl::MemoryPortAccessOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

MemoryPortAccessOpGenericAdaptorBase::MemoryPortAccessOpGenericAdaptorBase(MemoryPortAccessOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}


} // namespace detail
MemoryPortAccessOpAdaptor::MemoryPortAccessOpAdaptor(MemoryPortAccessOp op) : MemoryPortAccessOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult MemoryPortAccessOpAdaptor::verify(::mlir::Location loc) {
  return ::mlir::success();
}

::llvm::LogicalResult MemoryPortAccessOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }
      return ::mlir::success();
}

::mlir::Attribute MemoryPortAccessOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code MemoryPortAccessOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine();
}

std::optional<mlir::Attribute> MemoryPortAccessOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
  return std::nullopt;
}

void MemoryPortAccessOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
}

void MemoryPortAccessOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
}

::llvm::LogicalResult MemoryPortAccessOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    return ::mlir::success();
}

void MemoryPortAccessOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value port, ::mlir::Value index, ::mlir::Value clock) {
  odsState.addOperands(port);
  odsState.addOperands(index);
  odsState.addOperands(clock);
}

MemoryPortAccessOp MemoryPortAccessOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value port, ::mlir::Value index, ::mlir::Value clock) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(port)>(port), std::forward<decltype(index)>(index), std::forward<decltype(clock)>(clock));
  auto __res__ = ::llvm::dyn_cast<MemoryPortAccessOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

MemoryPortAccessOp MemoryPortAccessOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value port, ::mlir::Value index, ::mlir::Value clock) {
  return create(builder, builder.getLoc(), std::forward<decltype(port)>(port), std::forward<decltype(index)>(index), std::forward<decltype(clock)>(clock));
}

void MemoryPortAccessOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value port, ::mlir::Value index, ::mlir::Value clock) {
  odsState.addOperands(port);
  odsState.addOperands(index);
  odsState.addOperands(clock);
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

MemoryPortAccessOp MemoryPortAccessOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value port, ::mlir::Value index, ::mlir::Value clock) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(port)>(port), std::forward<decltype(index)>(index), std::forward<decltype(clock)>(clock));
  auto __res__ = ::llvm::dyn_cast<MemoryPortAccessOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

MemoryPortAccessOp MemoryPortAccessOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value port, ::mlir::Value index, ::mlir::Value clock) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(port)>(port), std::forward<decltype(index)>(index), std::forward<decltype(clock)>(clock));
}

void MemoryPortAccessOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 3u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

MemoryPortAccessOp MemoryPortAccessOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<MemoryPortAccessOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

MemoryPortAccessOp MemoryPortAccessOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void MemoryPortAccessOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 3u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

MemoryPortAccessOp MemoryPortAccessOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<MemoryPortAccessOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

MemoryPortAccessOp MemoryPortAccessOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult MemoryPortAccessOp::verifyInvariantsImpl() {
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_CHIRRTL3(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSOperands(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_CHIRRTL4(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup2 = getODSOperands(2);

    for (auto v : valueGroup2) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_CHIRRTL5(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult MemoryPortAccessOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult MemoryPortAccessOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::OpAsmParser::UnresolvedOperand portRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> portOperands(&portRawOperand, 1);  ::llvm::SMLoc portOperandsLoc;
  (void)portOperandsLoc;
  ::mlir::OpAsmParser::UnresolvedOperand indexRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> indexOperands(&indexRawOperand, 1);  ::llvm::SMLoc indexOperandsLoc;
  (void)indexOperandsLoc;
  ::mlir::OpAsmParser::UnresolvedOperand clockRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> clockOperands(&clockRawOperand, 1);  ::llvm::SMLoc clockOperandsLoc;
  (void)clockOperandsLoc;
  ::llvm::SmallVector<::mlir::Type, 1> allOperandTypes;

  portOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(portRawOperand))
    return ::mlir::failure();
  if (parser.parseLSquare())
    return ::mlir::failure();

  indexOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(indexRawOperand))
    return ::mlir::failure();
  if (parser.parseRSquare())
    return ::mlir::failure();
  if (parser.parseComma())
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

  if (parser.parseTypeList(allOperandTypes))
    return ::mlir::failure();
  if (parser.resolveOperands(::llvm::concat<const ::mlir::OpAsmParser::UnresolvedOperand>(portOperands, indexOperands, clockOperands), allOperandTypes, parser.getNameLoc(), result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void MemoryPortAccessOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter << getPort();
  _odsPrinter << "[";
  _odsPrinter << getIndex();
  _odsPrinter << "]";
  _odsPrinter << ",";
  _odsPrinter << ' ';
  _odsPrinter << getClock();
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
  _odsPrinter << getOperation()->getOperandTypes();
}


} // namespace circt::chirrtl
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::chirrtl::MemoryPortAccessOp)

namespace circt::chirrtl {


//===----------------------------------------------------------------------===//
// ::circt::chirrtl::MemoryPortOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

MemoryPortOpGenericAdaptorBase::MemoryPortOpGenericAdaptorBase(MemoryPortOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::circt::firrtl::MemDirAttr MemoryPortOpGenericAdaptorBase::getDirection() {
  auto attr = getDirectionAttr();
  return attr.getValue();
}

::llvm::StringRef MemoryPortOpGenericAdaptorBase::getName() {
  auto attr = getNameAttr();
  return attr.getValue();
}

::mlir::ArrayAttr MemoryPortOpGenericAdaptorBase::getAnnotations() {
  auto attr = getAnnotationsAttr();
  return attr;
}


} // namespace detail
MemoryPortOpAdaptor::MemoryPortOpAdaptor(MemoryPortOp op) : MemoryPortOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult MemoryPortOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_annotations = getProperties().annotations; (void)tblgen_annotations;
  if (!tblgen_annotations) return emitError(loc, "'chirrtl.memoryport' op requires attribute 'annotations'");
  auto tblgen_direction = getProperties().direction; (void)tblgen_direction;
  if (!tblgen_direction) return emitError(loc, "'chirrtl.memoryport' op requires attribute 'direction'");
  auto tblgen_name = getProperties().name; (void)tblgen_name;
  if (!tblgen_name) return emitError(loc, "'chirrtl.memoryport' op requires attribute 'name'");

  if (tblgen_direction && !((::llvm::isa<::circt::firrtl::MemDirAttrAttr>(tblgen_direction))))
    return emitError(loc, "'chirrtl.memoryport' op attribute 'direction' failed to satisfy constraint: Memory Direction Enum");

  if (tblgen_name && !((::llvm::isa<::mlir::StringAttr>(tblgen_name))))
    return emitError(loc, "'chirrtl.memoryport' op attribute 'name' failed to satisfy constraint: string attribute");

  if (tblgen_annotations && !(((::llvm::isa<::mlir::ArrayAttr>(tblgen_annotations))) && (::llvm::all_of(::llvm::cast<::mlir::ArrayAttr>(tblgen_annotations), [&](::mlir::Attribute attr) { return attr && ((::llvm::isa<::mlir::DictionaryAttr>(attr))); }))))
    return emitError(loc, "'chirrtl.memoryport' op attribute 'annotations' failed to satisfy constraint: Annotation array attribute");
  return ::mlir::success();
}

::llvm::LogicalResult MemoryPortOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.annotations;
       auto attr = dict.get("annotations");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `annotations` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.direction;
       auto attr = dict.get("direction");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `direction` in property conversion: " << attr;
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

::mlir::Attribute MemoryPortOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.annotations;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("annotations",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.direction;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("direction",
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

llvm::hash_code MemoryPortOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.annotations.getAsOpaquePointer()), 
    llvm::hash_value(prop.direction.getAsOpaquePointer()), 
    llvm::hash_value(prop.name.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> MemoryPortOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "annotations")
      return prop.annotations;

    if (name == "direction")
      return prop.direction;

    if (name == "name")
      return prop.name;
  return std::nullopt;
}

void MemoryPortOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "annotations") {
       prop.annotations = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.annotations)>>(value);
       return;
    }

    if (name == "direction") {
       prop.direction = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.direction)>>(value);
       return;
    }

    if (name == "name") {
       prop.name = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.name)>>(value);
       return;
    }
}

void MemoryPortOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.annotations) attrs.append("annotations", prop.annotations);

    if (prop.direction) attrs.append("direction", prop.direction);

    if (prop.name) attrs.append("name", prop.name);
}

::llvm::LogicalResult MemoryPortOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getAnnotationsAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_CHIRRTL3(attr, "annotations", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getDirectionAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_CHIRRTL6(attr, "direction", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getNameAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_CHIRRTL1(attr, "name", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult MemoryPortOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.annotations)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readAttribute(prop.direction)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readAttribute(prop.name)))
    return ::mlir::failure();
  return ::mlir::success();
}

void MemoryPortOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.annotations);
  writer.writeAttribute(prop.direction);
  writer.writeAttribute(prop.name);
}

::circt::firrtl::MemDirAttr MemoryPortOp::getDirection() {
  auto attr = getDirectionAttr();
  return attr.getValue();
}

::llvm::StringRef MemoryPortOp::getName() {
  auto attr = getNameAttr();
  return attr.getValue();
}

::mlir::ArrayAttr MemoryPortOp::getAnnotations() {
  auto attr = getAnnotationsAttr();
  return attr;
}

void MemoryPortOp::setDirection(::circt::firrtl::MemDirAttr attrValue) {
  getProperties().direction = ::circt::firrtl::MemDirAttrAttr::get(::mlir::Builder((*this)->getContext()).getContext(), attrValue);
}

void MemoryPortOp::setName(::llvm::StringRef attrValue) {
  getProperties().name = ::mlir::Builder((*this)->getContext()).getStringAttr(attrValue);
}

MemoryPortOp MemoryPortOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type dataType, ::mlir::Value memory, firrtl::MemDirAttr direction, StringRef name, ArrayRef<Attribute> annotations) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(dataType)>(dataType), std::forward<decltype(memory)>(memory), std::forward<decltype(direction)>(direction), std::forward<decltype(name)>(name), std::forward<decltype(annotations)>(annotations));
  auto __res__ = ::llvm::dyn_cast<MemoryPortOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

MemoryPortOp MemoryPortOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type dataType, ::mlir::Value memory, firrtl::MemDirAttr direction, StringRef name, ArrayRef<Attribute> annotations) {
  return create(builder, builder.getLoc(), std::forward<decltype(dataType)>(dataType), std::forward<decltype(memory)>(memory), std::forward<decltype(direction)>(direction), std::forward<decltype(name)>(name), std::forward<decltype(annotations)>(annotations));
}

void MemoryPortOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type data, ::mlir::Type port, ::mlir::Value memory, ::circt::firrtl::MemDirAttrAttr direction, ::mlir::StringAttr name, ::mlir::ArrayAttr annotations) {
  odsState.addOperands(memory);
  odsState.getOrAddProperties<Properties>().direction = direction;
  odsState.getOrAddProperties<Properties>().name = name;
  odsState.getOrAddProperties<Properties>().annotations = annotations;
  odsState.addTypes(data);
  odsState.addTypes(port);
}

MemoryPortOp MemoryPortOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type data, ::mlir::Type port, ::mlir::Value memory, ::circt::firrtl::MemDirAttrAttr direction, ::mlir::StringAttr name, ::mlir::ArrayAttr annotations) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(data)>(data), std::forward<decltype(port)>(port), std::forward<decltype(memory)>(memory), std::forward<decltype(direction)>(direction), std::forward<decltype(name)>(name), std::forward<decltype(annotations)>(annotations));
  auto __res__ = ::llvm::dyn_cast<MemoryPortOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

MemoryPortOp MemoryPortOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type data, ::mlir::Type port, ::mlir::Value memory, ::circt::firrtl::MemDirAttrAttr direction, ::mlir::StringAttr name, ::mlir::ArrayAttr annotations) {
  return create(builder, builder.getLoc(), std::forward<decltype(data)>(data), std::forward<decltype(port)>(port), std::forward<decltype(memory)>(memory), std::forward<decltype(direction)>(direction), std::forward<decltype(name)>(name), std::forward<decltype(annotations)>(annotations));
}

void MemoryPortOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value memory, ::circt::firrtl::MemDirAttrAttr direction, ::mlir::StringAttr name, ::mlir::ArrayAttr annotations) {
  odsState.addOperands(memory);
  odsState.getOrAddProperties<Properties>().direction = direction;
  odsState.getOrAddProperties<Properties>().name = name;
  odsState.getOrAddProperties<Properties>().annotations = annotations;

        ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
        if (::mlir::succeeded(MemoryPortOp::inferReturnTypes(odsBuilder.getContext(),
                      odsState.location, odsState.operands,
                      odsState.attributes.getDictionary(odsState.getContext()),
                      odsState.getRawProperties(),
                      odsState.regions, inferredReturnTypes)))
          odsState.addTypes(inferredReturnTypes);
        else
          ::mlir::detail::reportFatalInferReturnTypesError(odsState);
        
}

MemoryPortOp MemoryPortOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value memory, ::circt::firrtl::MemDirAttrAttr direction, ::mlir::StringAttr name, ::mlir::ArrayAttr annotations) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(memory)>(memory), std::forward<decltype(direction)>(direction), std::forward<decltype(name)>(name), std::forward<decltype(annotations)>(annotations));
  auto __res__ = ::llvm::dyn_cast<MemoryPortOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

MemoryPortOp MemoryPortOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value memory, ::circt::firrtl::MemDirAttrAttr direction, ::mlir::StringAttr name, ::mlir::ArrayAttr annotations) {
  return create(builder, builder.getLoc(), std::forward<decltype(memory)>(memory), std::forward<decltype(direction)>(direction), std::forward<decltype(name)>(name), std::forward<decltype(annotations)>(annotations));
}

void MemoryPortOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value memory, ::circt::firrtl::MemDirAttrAttr direction, ::mlir::StringAttr name, ::mlir::ArrayAttr annotations) {
  odsState.addOperands(memory);
  odsState.getOrAddProperties<Properties>().direction = direction;
  odsState.getOrAddProperties<Properties>().name = name;
  odsState.getOrAddProperties<Properties>().annotations = annotations;
  assert(resultTypes.size() == 2u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

MemoryPortOp MemoryPortOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value memory, ::circt::firrtl::MemDirAttrAttr direction, ::mlir::StringAttr name, ::mlir::ArrayAttr annotations) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(memory)>(memory), std::forward<decltype(direction)>(direction), std::forward<decltype(name)>(name), std::forward<decltype(annotations)>(annotations));
  auto __res__ = ::llvm::dyn_cast<MemoryPortOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

MemoryPortOp MemoryPortOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value memory, ::circt::firrtl::MemDirAttrAttr direction, ::mlir::StringAttr name, ::mlir::ArrayAttr annotations) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(memory)>(memory), std::forward<decltype(direction)>(direction), std::forward<decltype(name)>(name), std::forward<decltype(annotations)>(annotations));
}

void MemoryPortOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type data, ::mlir::Type port, ::mlir::Value memory, ::circt::firrtl::MemDirAttr direction, ::llvm::StringRef name, ::mlir::ArrayAttr annotations) {
  odsState.addOperands(memory);
  odsState.getOrAddProperties<Properties>().direction = ::circt::firrtl::MemDirAttrAttr::get(odsBuilder.getContext(), direction);
  odsState.getOrAddProperties<Properties>().name = odsBuilder.getStringAttr(name);
  odsState.getOrAddProperties<Properties>().annotations = annotations;
  odsState.addTypes(data);
  odsState.addTypes(port);
}

MemoryPortOp MemoryPortOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type data, ::mlir::Type port, ::mlir::Value memory, ::circt::firrtl::MemDirAttr direction, ::llvm::StringRef name, ::mlir::ArrayAttr annotations) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(data)>(data), std::forward<decltype(port)>(port), std::forward<decltype(memory)>(memory), std::forward<decltype(direction)>(direction), std::forward<decltype(name)>(name), std::forward<decltype(annotations)>(annotations));
  auto __res__ = ::llvm::dyn_cast<MemoryPortOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

MemoryPortOp MemoryPortOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type data, ::mlir::Type port, ::mlir::Value memory, ::circt::firrtl::MemDirAttr direction, ::llvm::StringRef name, ::mlir::ArrayAttr annotations) {
  return create(builder, builder.getLoc(), std::forward<decltype(data)>(data), std::forward<decltype(port)>(port), std::forward<decltype(memory)>(memory), std::forward<decltype(direction)>(direction), std::forward<decltype(name)>(name), std::forward<decltype(annotations)>(annotations));
}

void MemoryPortOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value memory, ::circt::firrtl::MemDirAttr direction, ::llvm::StringRef name, ::mlir::ArrayAttr annotations) {
  odsState.addOperands(memory);
  odsState.getOrAddProperties<Properties>().direction = ::circt::firrtl::MemDirAttrAttr::get(odsBuilder.getContext(), direction);
  odsState.getOrAddProperties<Properties>().name = odsBuilder.getStringAttr(name);
  odsState.getOrAddProperties<Properties>().annotations = annotations;

        ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
        if (::mlir::succeeded(MemoryPortOp::inferReturnTypes(odsBuilder.getContext(),
                      odsState.location, odsState.operands,
                      odsState.attributes.getDictionary(odsState.getContext()),
                      odsState.getRawProperties(),
                      odsState.regions, inferredReturnTypes)))
          odsState.addTypes(inferredReturnTypes);
        else
          ::mlir::detail::reportFatalInferReturnTypesError(odsState);
        
}

MemoryPortOp MemoryPortOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value memory, ::circt::firrtl::MemDirAttr direction, ::llvm::StringRef name, ::mlir::ArrayAttr annotations) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(memory)>(memory), std::forward<decltype(direction)>(direction), std::forward<decltype(name)>(name), std::forward<decltype(annotations)>(annotations));
  auto __res__ = ::llvm::dyn_cast<MemoryPortOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

MemoryPortOp MemoryPortOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value memory, ::circt::firrtl::MemDirAttr direction, ::llvm::StringRef name, ::mlir::ArrayAttr annotations) {
  return create(builder, builder.getLoc(), std::forward<decltype(memory)>(memory), std::forward<decltype(direction)>(direction), std::forward<decltype(name)>(name), std::forward<decltype(annotations)>(annotations));
}

void MemoryPortOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value memory, ::circt::firrtl::MemDirAttr direction, ::llvm::StringRef name, ::mlir::ArrayAttr annotations) {
  odsState.addOperands(memory);
  odsState.getOrAddProperties<Properties>().direction = ::circt::firrtl::MemDirAttrAttr::get(odsBuilder.getContext(), direction);
  odsState.getOrAddProperties<Properties>().name = odsBuilder.getStringAttr(name);
  odsState.getOrAddProperties<Properties>().annotations = annotations;
  assert(resultTypes.size() == 2u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

MemoryPortOp MemoryPortOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value memory, ::circt::firrtl::MemDirAttr direction, ::llvm::StringRef name, ::mlir::ArrayAttr annotations) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(memory)>(memory), std::forward<decltype(direction)>(direction), std::forward<decltype(name)>(name), std::forward<decltype(annotations)>(annotations));
  auto __res__ = ::llvm::dyn_cast<MemoryPortOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

MemoryPortOp MemoryPortOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value memory, ::circt::firrtl::MemDirAttr direction, ::llvm::StringRef name, ::mlir::ArrayAttr annotations) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(memory)>(memory), std::forward<decltype(direction)>(direction), std::forward<decltype(name)>(name), std::forward<decltype(annotations)>(annotations));
}

void MemoryPortOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 2u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<MemoryPortOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

MemoryPortOp MemoryPortOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<MemoryPortOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

MemoryPortOp MemoryPortOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void MemoryPortOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<MemoryPortOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
  ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
  if (::mlir::succeeded(MemoryPortOp::inferReturnTypes(odsBuilder.getContext(),
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

MemoryPortOp MemoryPortOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<MemoryPortOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

MemoryPortOp MemoryPortOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void MemoryPortOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 2u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

MemoryPortOp MemoryPortOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<MemoryPortOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

MemoryPortOp MemoryPortOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

void MemoryPortOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 1u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties &>(properties));
  odsState.addAttributes(discardableAttributes);

  ::llvm::SmallVector<::mlir::Type, 2> inferredReturnTypes;
  if (::mlir::succeeded(MemoryPortOp::inferReturnTypes(odsBuilder.getContext(),
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

MemoryPortOp MemoryPortOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<MemoryPortOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

MemoryPortOp MemoryPortOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult MemoryPortOp::verifyInvariantsImpl() {
  auto tblgen_annotations = getProperties().annotations; (void)tblgen_annotations;
  if (!tblgen_annotations) return emitOpError("requires attribute 'annotations'");
  auto tblgen_direction = getProperties().direction; (void)tblgen_direction;
  if (!tblgen_direction) return emitOpError("requires attribute 'direction'");
  auto tblgen_name = getProperties().name; (void)tblgen_name;
  if (!tblgen_name) return emitOpError("requires attribute 'name'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_CHIRRTL6(*this, tblgen_direction, "direction")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_CHIRRTL1(*this, tblgen_name, "name")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_CHIRRTL3(*this, tblgen_annotations, "annotations")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_CHIRRTL1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_CHIRRTL6(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSResults(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_CHIRRTL3(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult MemoryPortOp::verifyInvariants() {
  if(::mlir::succeeded(verifyInvariantsImpl()) && ::mlir::succeeded(verify()))
    return ::mlir::success();
  return ::mlir::failure();
}

::mlir::ParseResult MemoryPortOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::circt::firrtl::MemDirAttrAttr directionAttr;
  ::mlir::OpAsmParser::UnresolvedOperand memoryRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> memoryOperands(&memoryRawOperand, 1);  ::llvm::SMLoc memoryOperandsLoc;
  (void)memoryOperandsLoc;
  ::llvm::ArrayRef<::mlir::Type> allOperandTypes;
  ::llvm::ArrayRef<::mlir::Type> allResultTypes;

  {
    ::llvm::StringRef attrStr;
    ::mlir::NamedAttrList attrStorage;
    auto loc = parser.getCurrentLocation();
    if (parser.parseOptionalKeyword(&attrStr, {"Infer","Read","Write","ReadWrite"})) {
      ::mlir::StringAttr attrVal;
      ::mlir::OptionalParseResult parseResult =
        parser.parseOptionalAttribute(attrVal,
                                      parser.getBuilder().getNoneType(),
                                      "direction", attrStorage);
      if (parseResult.has_value()) {
        if (failed(*parseResult))
          return ::mlir::failure();
        attrStr = attrVal.getValue();
      } else {
        return parser.emitError(loc, "expected string or keyword containing one of the following enum values for attribute 'direction' [Infer, Read, Write, ReadWrite]");
      }
    }
    if (!attrStr.empty()) {
      auto attrOptional = ::circt::firrtl::symbolizeMemDirAttr(attrStr);
      if (!attrOptional)
        return parser.emitError(loc, "invalid ")
               << "direction attribute specification: \"" << attrStr << '"';;

      directionAttr = ::circt::firrtl::MemDirAttrAttr::get(parser.getBuilder().getContext(), *attrOptional);
        result.getOrAddProperties<MemoryPortOp::Properties>().direction = directionAttr;
    }
  }

  memoryOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(memoryRawOperand))
    return ::mlir::failure();
  {
    auto odsResult = parseMemoryPortOp(parser, result.attributes);
    if (odsResult) return ::mlir::failure();
  }
  if (parser.parseColon())
    return ::mlir::failure();

  ::mlir::FunctionType allOperand__allResult_functionType;
  if (parser.parseType(allOperand__allResult_functionType))
    return ::mlir::failure();
  allOperandTypes = allOperand__allResult_functionType.getInputs();
  allResultTypes = allOperand__allResult_functionType.getResults();
  result.addTypes(allResultTypes);
  if (parser.resolveOperands(memoryOperands, allOperandTypes, parser.getNameLoc(), result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void MemoryPortOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';

  {
    auto caseValue = getDirection();
    auto caseValueStr = stringifyMemDirAttr(caseValue);
    _odsPrinter << caseValueStr;
  }
  _odsPrinter << ' ';
  _odsPrinter << getMemory();
  printMemoryPortOp(_odsPrinter, *this, getOperation()->getAttrDictionary());
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
  _odsPrinter.printFunctionalType(getOperation()->getOperandTypes(), getOperation()->getResultTypes());
}


} // namespace circt::chirrtl
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::chirrtl::MemoryPortOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::chirrtl::detail::MemoryPortOpGenericAdaptorBase::Properties)

namespace circt::chirrtl {


//===----------------------------------------------------------------------===//
// ::circt::chirrtl::SeqMemOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

SeqMemOpGenericAdaptorBase::SeqMemOpGenericAdaptorBase(SeqMemOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::circt::firrtl::RUWBehavior SeqMemOpGenericAdaptorBase::getRuw() {
  auto attr = getRuwAttr();
  return attr.getValue();
}

::llvm::StringRef SeqMemOpGenericAdaptorBase::getName() {
  auto attr = getNameAttr();
  return attr.getValue();
}

::circt::firrtl::NameKindEnum SeqMemOpGenericAdaptorBase::getNameKind() {
  auto attr = getNameKindAttr();
  return attr.getValue();
}

::mlir::ArrayAttr SeqMemOpGenericAdaptorBase::getAnnotations() {
  auto attr = getAnnotationsAttr();
  return attr;
}

::std::optional<::circt::hw::InnerSymAttr> SeqMemOpGenericAdaptorBase::getInnerSym() {
  auto attr = getInnerSymAttr();
  return attr ? ::std::optional<::circt::hw::InnerSymAttr>(::llvm::cast<::circt::hw::InnerSymAttr>(attr)) : (::std::nullopt);
}

::std::optional<::circt::firrtl::MemoryInitAttr> SeqMemOpGenericAdaptorBase::getInit() {
  auto attr = getInitAttr();
  return attr ? ::std::optional<::circt::firrtl::MemoryInitAttr>(::llvm::cast<::circt::firrtl::MemoryInitAttr>(attr)) : (::std::nullopt);
}

::std::optional< ::llvm::StringRef > SeqMemOpGenericAdaptorBase::getPrefix() {
  auto attr = getPrefixAttr();
  return attr ? ::std::optional< ::llvm::StringRef >(attr.getValue()) : (::std::nullopt);
}


} // namespace detail
SeqMemOpAdaptor::SeqMemOpAdaptor(SeqMemOp op) : SeqMemOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult SeqMemOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_annotations = getProperties().annotations; (void)tblgen_annotations;
  if (!tblgen_annotations) return emitError(loc, "'chirrtl.seqmem' op requires attribute 'annotations'");
  auto tblgen_init = getProperties().init; (void)tblgen_init;
  auto tblgen_inner_sym = getProperties().inner_sym; (void)tblgen_inner_sym;
  auto tblgen_name = getProperties().name; (void)tblgen_name;
  if (!tblgen_name) return emitError(loc, "'chirrtl.seqmem' op requires attribute 'name'");
  auto tblgen_nameKind = getProperties().nameKind; (void)tblgen_nameKind;
  if (!tblgen_nameKind) return emitError(loc, "'chirrtl.seqmem' op requires attribute 'nameKind'");
  auto tblgen_prefix = getProperties().prefix; (void)tblgen_prefix;
  auto tblgen_ruw = getProperties().ruw; (void)tblgen_ruw;
  if (!tblgen_ruw) return emitError(loc, "'chirrtl.seqmem' op requires attribute 'ruw'");

  if (tblgen_ruw && !((::llvm::isa<::circt::firrtl::RUWBehaviorAttr>(tblgen_ruw))))
    return emitError(loc, "'chirrtl.seqmem' op attribute 'ruw' failed to satisfy constraint: read under write behavior");

  if (tblgen_name && !((::llvm::isa<::mlir::StringAttr>(tblgen_name))))
    return emitError(loc, "'chirrtl.seqmem' op attribute 'name' failed to satisfy constraint: string attribute");

  if (tblgen_nameKind && !((::llvm::isa<::circt::firrtl::NameKindEnumAttr>(tblgen_nameKind))))
    return emitError(loc, "'chirrtl.seqmem' op attribute 'nameKind' failed to satisfy constraint: name kind");

  if (tblgen_annotations && !(((::llvm::isa<::mlir::ArrayAttr>(tblgen_annotations))) && (::llvm::all_of(::llvm::cast<::mlir::ArrayAttr>(tblgen_annotations), [&](::mlir::Attribute attr) { return attr && ((::llvm::isa<::mlir::DictionaryAttr>(attr))); }))))
    return emitError(loc, "'chirrtl.seqmem' op attribute 'annotations' failed to satisfy constraint: Annotation array attribute");

  if (tblgen_inner_sym && !((::llvm::isa<::circt::hw::InnerSymAttr>(tblgen_inner_sym))))
    return emitError(loc, "'chirrtl.seqmem' op attribute 'inner_sym' failed to satisfy constraint: Inner symbol definition");

  if (tblgen_init && !((::llvm::isa<::circt::firrtl::MemoryInitAttr>(tblgen_init))))
    return emitError(loc, "'chirrtl.seqmem' op attribute 'init' failed to satisfy constraint: Information about the initial state of a memory");

  if (tblgen_prefix && !((::llvm::isa<::mlir::StringAttr>(tblgen_prefix))))
    return emitError(loc, "'chirrtl.seqmem' op attribute 'prefix' failed to satisfy constraint: string attribute");
  return ::mlir::success();
}

::llvm::LogicalResult SeqMemOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.annotations;
       auto attr = dict.get("annotations");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `annotations` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
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
    auto &propStorage = prop.nameKind;
       auto attr = dict.get("nameKind");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `nameKind` in property conversion: " << attr;
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
  return ::mlir::success();
}

::mlir::Attribute SeqMemOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.annotations;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("annotations",
                                       propStorage));
    }

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
      const auto &propStorage = prop.nameKind;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("nameKind",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.prefix;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("prefix",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.ruw;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("ruw",
                                       propStorage));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code SeqMemOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.annotations.getAsOpaquePointer()), 
    llvm::hash_value(prop.init.getAsOpaquePointer()), 
    llvm::hash_value(prop.inner_sym.getAsOpaquePointer()), 
    llvm::hash_value(prop.name.getAsOpaquePointer()), 
    llvm::hash_value(prop.nameKind.getAsOpaquePointer()), 
    llvm::hash_value(prop.prefix.getAsOpaquePointer()), 
    llvm::hash_value(prop.ruw.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> SeqMemOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "annotations")
      return prop.annotations;

    if (name == "init")
      return prop.init;

    if (name == "inner_sym")
      return prop.inner_sym;

    if (name == "name")
      return prop.name;

    if (name == "nameKind")
      return prop.nameKind;

    if (name == "prefix")
      return prop.prefix;

    if (name == "ruw")
      return prop.ruw;
  return std::nullopt;
}

void SeqMemOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "annotations") {
       prop.annotations = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.annotations)>>(value);
       return;
    }

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

    if (name == "nameKind") {
       prop.nameKind = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.nameKind)>>(value);
       return;
    }

    if (name == "prefix") {
       prop.prefix = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.prefix)>>(value);
       return;
    }

    if (name == "ruw") {
       prop.ruw = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.ruw)>>(value);
       return;
    }
}

void SeqMemOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.annotations) attrs.append("annotations", prop.annotations);

    if (prop.init) attrs.append("init", prop.init);

    if (prop.inner_sym) attrs.append("inner_sym", prop.inner_sym);

    if (prop.name) attrs.append("name", prop.name);

    if (prop.nameKind) attrs.append("nameKind", prop.nameKind);

    if (prop.prefix) attrs.append("prefix", prop.prefix);

    if (prop.ruw) attrs.append("ruw", prop.ruw);
}

::llvm::LogicalResult SeqMemOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getAnnotationsAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_CHIRRTL3(attr, "annotations", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getInitAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_CHIRRTL5(attr, "init", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getInnerSymAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_CHIRRTL4(attr, "inner_sym", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getNameAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_CHIRRTL1(attr, "name", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getNameKindAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_CHIRRTL2(attr, "nameKind", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getPrefixAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_CHIRRTL1(attr, "prefix", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getRuwAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_CHIRRTL7(attr, "ruw", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult SeqMemOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.annotations)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readOptionalAttribute(prop.init)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readOptionalAttribute(prop.inner_sym)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readAttribute(prop.name)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readAttribute(prop.nameKind)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readOptionalAttribute(prop.prefix)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readAttribute(prop.ruw)))
    return ::mlir::failure();
  return ::mlir::success();
}

void SeqMemOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.annotations);

  writer.writeOptionalAttribute(prop.init);

  writer.writeOptionalAttribute(prop.inner_sym);
  writer.writeAttribute(prop.name);
  writer.writeAttribute(prop.nameKind);

  writer.writeOptionalAttribute(prop.prefix);
  writer.writeAttribute(prop.ruw);
}

::circt::firrtl::RUWBehavior SeqMemOp::getRuw() {
  auto attr = getRuwAttr();
  return attr.getValue();
}

::llvm::StringRef SeqMemOp::getName() {
  auto attr = getNameAttr();
  return attr.getValue();
}

::circt::firrtl::NameKindEnum SeqMemOp::getNameKind() {
  auto attr = getNameKindAttr();
  return attr.getValue();
}

::mlir::ArrayAttr SeqMemOp::getAnnotations() {
  auto attr = getAnnotationsAttr();
  return attr;
}

::std::optional<::circt::hw::InnerSymAttr> SeqMemOp::getInnerSym() {
  auto attr = getInnerSymAttr();
  return attr ? ::std::optional<::circt::hw::InnerSymAttr>(::llvm::cast<::circt::hw::InnerSymAttr>(attr)) : (::std::nullopt);
}

::std::optional<::circt::firrtl::MemoryInitAttr> SeqMemOp::getInit() {
  auto attr = getInitAttr();
  return attr ? ::std::optional<::circt::firrtl::MemoryInitAttr>(::llvm::cast<::circt::firrtl::MemoryInitAttr>(attr)) : (::std::nullopt);
}

::std::optional< ::llvm::StringRef > SeqMemOp::getPrefix() {
  auto attr = getPrefixAttr();
  return attr ? ::std::optional< ::llvm::StringRef >(attr.getValue()) : (::std::nullopt);
}

void SeqMemOp::setRuw(::circt::firrtl::RUWBehavior attrValue) {
  getProperties().ruw = ::circt::firrtl::RUWBehaviorAttr::get(::mlir::Builder((*this)->getContext()).getContext(), attrValue);
}

void SeqMemOp::setName(::llvm::StringRef attrValue) {
  getProperties().name = ::mlir::Builder((*this)->getContext()).getStringAttr(attrValue);
}

void SeqMemOp::setNameKind(::circt::firrtl::NameKindEnum attrValue) {
  getProperties().nameKind = ::circt::firrtl::NameKindEnumAttr::get(::mlir::Builder((*this)->getContext()).getContext(), attrValue);
}

void SeqMemOp::setPrefix(::std::optional<::llvm::StringRef> attrValue) {
    auto &odsProp = getProperties().prefix;
    if (attrValue)
      odsProp = ::mlir::Builder((*this)->getContext()).getStringAttr(*attrValue);
    else
      odsProp = nullptr;
}

SeqMemOp SeqMemOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, firrtl::FIRRTLBaseType elementType, uint64_t numElements, firrtl::RUWBehavior ruw, mlir::StringRef name, firrtl::NameKindEnum nameKind, ArrayAttr annotations, StringAttr innerSym, firrtl::MemoryInitAttr init) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(elementType)>(elementType), std::forward<decltype(numElements)>(numElements), std::forward<decltype(ruw)>(ruw), std::forward<decltype(name)>(name), std::forward<decltype(nameKind)>(nameKind), std::forward<decltype(annotations)>(annotations), std::forward<decltype(innerSym)>(innerSym), std::forward<decltype(init)>(init));
  auto __res__ = ::llvm::dyn_cast<SeqMemOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SeqMemOp SeqMemOp::create(::mlir::ImplicitLocOpBuilder &builder, firrtl::FIRRTLBaseType elementType, uint64_t numElements, firrtl::RUWBehavior ruw, mlir::StringRef name, firrtl::NameKindEnum nameKind, ArrayAttr annotations, StringAttr innerSym, firrtl::MemoryInitAttr init) {
  return create(builder, builder.getLoc(), std::forward<decltype(elementType)>(elementType), std::forward<decltype(numElements)>(numElements), std::forward<decltype(ruw)>(ruw), std::forward<decltype(name)>(name), std::forward<decltype(nameKind)>(nameKind), std::forward<decltype(annotations)>(annotations), std::forward<decltype(innerSym)>(innerSym), std::forward<decltype(init)>(init));
}

void SeqMemOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::circt::firrtl::RUWBehaviorAttr ruw, ::mlir::StringAttr name, ::circt::firrtl::NameKindEnumAttr nameKind, ::mlir::ArrayAttr annotations, /*optional*/::circt::hw::InnerSymAttr inner_sym, /*optional*/::circt::firrtl::MemoryInitAttr init, /*optional*/::mlir::StringAttr prefix) {
  odsState.getOrAddProperties<Properties>().ruw = ruw;
  odsState.getOrAddProperties<Properties>().name = name;
  odsState.getOrAddProperties<Properties>().nameKind = nameKind;
  odsState.getOrAddProperties<Properties>().annotations = annotations;
  if (inner_sym) {
    odsState.getOrAddProperties<Properties>().inner_sym = inner_sym;
  }
  if (init) {
    odsState.getOrAddProperties<Properties>().init = init;
  }
  if (prefix) {
    odsState.getOrAddProperties<Properties>().prefix = prefix;
  }
  odsState.addTypes(result);
}

SeqMemOp SeqMemOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::circt::firrtl::RUWBehaviorAttr ruw, ::mlir::StringAttr name, ::circt::firrtl::NameKindEnumAttr nameKind, ::mlir::ArrayAttr annotations, /*optional*/::circt::hw::InnerSymAttr inner_sym, /*optional*/::circt::firrtl::MemoryInitAttr init, /*optional*/::mlir::StringAttr prefix) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(result)>(result), std::forward<decltype(ruw)>(ruw), std::forward<decltype(name)>(name), std::forward<decltype(nameKind)>(nameKind), std::forward<decltype(annotations)>(annotations), std::forward<decltype(inner_sym)>(inner_sym), std::forward<decltype(init)>(init), std::forward<decltype(prefix)>(prefix));
  auto __res__ = ::llvm::dyn_cast<SeqMemOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SeqMemOp SeqMemOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::circt::firrtl::RUWBehaviorAttr ruw, ::mlir::StringAttr name, ::circt::firrtl::NameKindEnumAttr nameKind, ::mlir::ArrayAttr annotations, /*optional*/::circt::hw::InnerSymAttr inner_sym, /*optional*/::circt::firrtl::MemoryInitAttr init, /*optional*/::mlir::StringAttr prefix) {
  return create(builder, builder.getLoc(), std::forward<decltype(result)>(result), std::forward<decltype(ruw)>(ruw), std::forward<decltype(name)>(name), std::forward<decltype(nameKind)>(nameKind), std::forward<decltype(annotations)>(annotations), std::forward<decltype(inner_sym)>(inner_sym), std::forward<decltype(init)>(init), std::forward<decltype(prefix)>(prefix));
}

void SeqMemOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::circt::firrtl::RUWBehaviorAttr ruw, ::mlir::StringAttr name, ::circt::firrtl::NameKindEnumAttr nameKind, ::mlir::ArrayAttr annotations, /*optional*/::circt::hw::InnerSymAttr inner_sym, /*optional*/::circt::firrtl::MemoryInitAttr init, /*optional*/::mlir::StringAttr prefix) {
  odsState.getOrAddProperties<Properties>().ruw = ruw;
  odsState.getOrAddProperties<Properties>().name = name;
  odsState.getOrAddProperties<Properties>().nameKind = nameKind;
  odsState.getOrAddProperties<Properties>().annotations = annotations;
  if (inner_sym) {
    odsState.getOrAddProperties<Properties>().inner_sym = inner_sym;
  }
  if (init) {
    odsState.getOrAddProperties<Properties>().init = init;
  }
  if (prefix) {
    odsState.getOrAddProperties<Properties>().prefix = prefix;
  }
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

SeqMemOp SeqMemOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::circt::firrtl::RUWBehaviorAttr ruw, ::mlir::StringAttr name, ::circt::firrtl::NameKindEnumAttr nameKind, ::mlir::ArrayAttr annotations, /*optional*/::circt::hw::InnerSymAttr inner_sym, /*optional*/::circt::firrtl::MemoryInitAttr init, /*optional*/::mlir::StringAttr prefix) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(ruw)>(ruw), std::forward<decltype(name)>(name), std::forward<decltype(nameKind)>(nameKind), std::forward<decltype(annotations)>(annotations), std::forward<decltype(inner_sym)>(inner_sym), std::forward<decltype(init)>(init), std::forward<decltype(prefix)>(prefix));
  auto __res__ = ::llvm::dyn_cast<SeqMemOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SeqMemOp SeqMemOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::circt::firrtl::RUWBehaviorAttr ruw, ::mlir::StringAttr name, ::circt::firrtl::NameKindEnumAttr nameKind, ::mlir::ArrayAttr annotations, /*optional*/::circt::hw::InnerSymAttr inner_sym, /*optional*/::circt::firrtl::MemoryInitAttr init, /*optional*/::mlir::StringAttr prefix) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(ruw)>(ruw), std::forward<decltype(name)>(name), std::forward<decltype(nameKind)>(nameKind), std::forward<decltype(annotations)>(annotations), std::forward<decltype(inner_sym)>(inner_sym), std::forward<decltype(init)>(init), std::forward<decltype(prefix)>(prefix));
}

void SeqMemOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::circt::firrtl::RUWBehavior ruw, ::llvm::StringRef name, ::circt::firrtl::NameKindEnum nameKind, ::mlir::ArrayAttr annotations, /*optional*/::circt::hw::InnerSymAttr inner_sym, /*optional*/::circt::firrtl::MemoryInitAttr init, /*optional*/::mlir::StringAttr prefix) {
  odsState.getOrAddProperties<Properties>().ruw = ::circt::firrtl::RUWBehaviorAttr::get(odsBuilder.getContext(), ruw);
  odsState.getOrAddProperties<Properties>().name = odsBuilder.getStringAttr(name);
  odsState.getOrAddProperties<Properties>().nameKind = ::circt::firrtl::NameKindEnumAttr::get(odsBuilder.getContext(), nameKind);
  odsState.getOrAddProperties<Properties>().annotations = annotations;
  if (inner_sym) {
    odsState.getOrAddProperties<Properties>().inner_sym = inner_sym;
  }
  if (init) {
    odsState.getOrAddProperties<Properties>().init = init;
  }
  if (prefix) {
    odsState.getOrAddProperties<Properties>().prefix = prefix;
  }
  odsState.addTypes(result);
}

SeqMemOp SeqMemOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::circt::firrtl::RUWBehavior ruw, ::llvm::StringRef name, ::circt::firrtl::NameKindEnum nameKind, ::mlir::ArrayAttr annotations, /*optional*/::circt::hw::InnerSymAttr inner_sym, /*optional*/::circt::firrtl::MemoryInitAttr init, /*optional*/::mlir::StringAttr prefix) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(result)>(result), std::forward<decltype(ruw)>(ruw), std::forward<decltype(name)>(name), std::forward<decltype(nameKind)>(nameKind), std::forward<decltype(annotations)>(annotations), std::forward<decltype(inner_sym)>(inner_sym), std::forward<decltype(init)>(init), std::forward<decltype(prefix)>(prefix));
  auto __res__ = ::llvm::dyn_cast<SeqMemOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SeqMemOp SeqMemOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::circt::firrtl::RUWBehavior ruw, ::llvm::StringRef name, ::circt::firrtl::NameKindEnum nameKind, ::mlir::ArrayAttr annotations, /*optional*/::circt::hw::InnerSymAttr inner_sym, /*optional*/::circt::firrtl::MemoryInitAttr init, /*optional*/::mlir::StringAttr prefix) {
  return create(builder, builder.getLoc(), std::forward<decltype(result)>(result), std::forward<decltype(ruw)>(ruw), std::forward<decltype(name)>(name), std::forward<decltype(nameKind)>(nameKind), std::forward<decltype(annotations)>(annotations), std::forward<decltype(inner_sym)>(inner_sym), std::forward<decltype(init)>(init), std::forward<decltype(prefix)>(prefix));
}

void SeqMemOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::circt::firrtl::RUWBehavior ruw, ::llvm::StringRef name, ::circt::firrtl::NameKindEnum nameKind, ::mlir::ArrayAttr annotations, /*optional*/::circt::hw::InnerSymAttr inner_sym, /*optional*/::circt::firrtl::MemoryInitAttr init, /*optional*/::mlir::StringAttr prefix) {
  odsState.getOrAddProperties<Properties>().ruw = ::circt::firrtl::RUWBehaviorAttr::get(odsBuilder.getContext(), ruw);
  odsState.getOrAddProperties<Properties>().name = odsBuilder.getStringAttr(name);
  odsState.getOrAddProperties<Properties>().nameKind = ::circt::firrtl::NameKindEnumAttr::get(odsBuilder.getContext(), nameKind);
  odsState.getOrAddProperties<Properties>().annotations = annotations;
  if (inner_sym) {
    odsState.getOrAddProperties<Properties>().inner_sym = inner_sym;
  }
  if (init) {
    odsState.getOrAddProperties<Properties>().init = init;
  }
  if (prefix) {
    odsState.getOrAddProperties<Properties>().prefix = prefix;
  }
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

SeqMemOp SeqMemOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::circt::firrtl::RUWBehavior ruw, ::llvm::StringRef name, ::circt::firrtl::NameKindEnum nameKind, ::mlir::ArrayAttr annotations, /*optional*/::circt::hw::InnerSymAttr inner_sym, /*optional*/::circt::firrtl::MemoryInitAttr init, /*optional*/::mlir::StringAttr prefix) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(ruw)>(ruw), std::forward<decltype(name)>(name), std::forward<decltype(nameKind)>(nameKind), std::forward<decltype(annotations)>(annotations), std::forward<decltype(inner_sym)>(inner_sym), std::forward<decltype(init)>(init), std::forward<decltype(prefix)>(prefix));
  auto __res__ = ::llvm::dyn_cast<SeqMemOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SeqMemOp SeqMemOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::circt::firrtl::RUWBehavior ruw, ::llvm::StringRef name, ::circt::firrtl::NameKindEnum nameKind, ::mlir::ArrayAttr annotations, /*optional*/::circt::hw::InnerSymAttr inner_sym, /*optional*/::circt::firrtl::MemoryInitAttr init, /*optional*/::mlir::StringAttr prefix) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(ruw)>(ruw), std::forward<decltype(name)>(name), std::forward<decltype(nameKind)>(nameKind), std::forward<decltype(annotations)>(annotations), std::forward<decltype(inner_sym)>(inner_sym), std::forward<decltype(init)>(init), std::forward<decltype(prefix)>(prefix));
}

void SeqMemOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<SeqMemOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

SeqMemOp SeqMemOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<SeqMemOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SeqMemOp SeqMemOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void SeqMemOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

SeqMemOp SeqMemOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<SeqMemOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

SeqMemOp SeqMemOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult SeqMemOp::verifyInvariantsImpl() {
  auto tblgen_annotations = getProperties().annotations; (void)tblgen_annotations;
  if (!tblgen_annotations) return emitOpError("requires attribute 'annotations'");
  auto tblgen_init = getProperties().init; (void)tblgen_init;
  auto tblgen_inner_sym = getProperties().inner_sym; (void)tblgen_inner_sym;
  auto tblgen_name = getProperties().name; (void)tblgen_name;
  if (!tblgen_name) return emitOpError("requires attribute 'name'");
  auto tblgen_nameKind = getProperties().nameKind; (void)tblgen_nameKind;
  if (!tblgen_nameKind) return emitOpError("requires attribute 'nameKind'");
  auto tblgen_prefix = getProperties().prefix; (void)tblgen_prefix;
  auto tblgen_ruw = getProperties().ruw; (void)tblgen_ruw;
  if (!tblgen_ruw) return emitOpError("requires attribute 'ruw'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_CHIRRTL7(*this, tblgen_ruw, "ruw")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_CHIRRTL1(*this, tblgen_name, "name")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_CHIRRTL2(*this, tblgen_nameKind, "nameKind")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_CHIRRTL3(*this, tblgen_annotations, "annotations")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_CHIRRTL4(*this, tblgen_inner_sym, "inner_sym")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_CHIRRTL5(*this, tblgen_init, "init")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_CHIRRTL1(*this, tblgen_prefix, "prefix")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_CHIRRTL1(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult SeqMemOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult SeqMemOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::circt::hw::InnerSymAttr inner_symAttr;
  ::circt::firrtl::NameKindEnumAttr nameKindAttr;
  ::circt::firrtl::RUWBehaviorAttr ruwAttr;
  ::mlir::Type resultRawType{};
  ::llvm::ArrayRef<::mlir::Type> resultTypes(&resultRawType, 1);
  if (::mlir::succeeded(parser.parseOptionalKeyword("sym"))) {

  if (parser.parseCustomAttributeWithFallback(inner_symAttr, ::mlir::Type{})) {
    return ::mlir::failure();
  }
  if (inner_symAttr) result.getOrAddProperties<SeqMemOp::Properties>().inner_sym = inner_symAttr;
  }
  {
    auto odsResult = parseNameKind(parser, nameKindAttr);
    if (odsResult) return ::mlir::failure();
    result.getOrAddProperties<SeqMemOp::Properties>().nameKind = nameKindAttr;
  }

  if (parser.parseCustomAttributeWithFallback(ruwAttr, ::mlir::Type{})) {
    return ::mlir::failure();
  }
  if (ruwAttr) result.getOrAddProperties<SeqMemOp::Properties>().ruw = ruwAttr;
  {
    auto odsResult = parseSeqMemOp(parser, result.attributes);
    if (odsResult) return ::mlir::failure();
  }
  if (parser.parseColon())
    return ::mlir::failure();

  if (parser.parseType(resultRawType))
    return ::mlir::failure();
  result.addTypes(resultTypes);
  return ::mlir::success();
}

void SeqMemOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  if (getInnerSymAttr()) {
    _odsPrinter << ' ' << "sym";
    _odsPrinter << ' ';
  _odsPrinter.printStrippedAttrOrType(getInnerSymAttr());
  }
  printNameKind(_odsPrinter, *this, getNameKindAttr());
  _odsPrinter << ' ';
_odsPrinter.printStrippedAttrOrType(getRuwAttr());
  _odsPrinter << ' ';
  printSeqMemOp(_odsPrinter, *this, getOperation()->getAttrDictionary());
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
   _odsPrinter << getResult().getType();
}


} // namespace circt::chirrtl
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::chirrtl::SeqMemOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::chirrtl::detail::SeqMemOpGenericAdaptorBase::Properties)


#endif // GET_OP_CLASSES

