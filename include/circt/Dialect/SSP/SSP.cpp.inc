/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Op Definitions                                                             *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: SSP.td                                                               *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

#ifdef GET_OP_LIST
#undef GET_OP_LIST

::circt::ssp::DependenceGraphOp,
::circt::ssp::InstanceOp,
::circt::ssp::OperationOp,
::circt::ssp::OperatorLibraryOp,
::circt::ssp::OperatorTypeOp,
::circt::ssp::ResourceLibraryOp,
::circt::ssp::ResourceTypeOp
#endif // GET_OP_LIST

#ifdef GET_OP_CLASSES
#undef GET_OP_CLASSES


//===----------------------------------------------------------------------===//
// Local Utility Method Definitions
//===----------------------------------------------------------------------===//


static ::llvm::LogicalResult __mlir_ods_local_type_constraint_SSP1(
    ::mlir::Operation *op, ::mlir::Type type, ::llvm::StringRef valueKind,
    unsigned valueIndex) {
  if (!((::llvm::isa<::mlir::NoneType>(type)))) {
    return op->emitOpError(valueKind) << " #" << valueIndex
        << " must be variadic of none type, but got " << type;
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_SSP1(
    ::mlir::Attribute attr, ::llvm::StringRef attrName, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  if (attr && !((::llvm::isa<::mlir::StringAttr>(attr))))
    return emitError() << "attribute '" << attrName
        << "' failed to satisfy constraint: string attribute";
  return ::mlir::success();
}
static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_SSP1(
    ::mlir::Operation *op, ::mlir::Attribute attr, ::llvm::StringRef attrName) {
  return __mlir_ods_local_attr_constraint_SSP1(attr, attrName, [op]() {
    return op->emitOpError();
  });
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_SSP2(
    ::mlir::Attribute attr, ::llvm::StringRef attrName, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  if (attr && !((::llvm::isa<::mlir::ArrayAttr>(attr))))
    return emitError() << "attribute '" << attrName
        << "' failed to satisfy constraint: array attribute";
  return ::mlir::success();
}
static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_SSP2(
    ::mlir::Operation *op, ::mlir::Attribute attr, ::llvm::StringRef attrName) {
  return __mlir_ods_local_attr_constraint_SSP2(attr, attrName, [op]() {
    return op->emitOpError();
  });
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_SSP3(
    ::mlir::Attribute attr, ::llvm::StringRef attrName, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  if (attr && !(((::llvm::isa<::mlir::ArrayAttr>(attr))) && (::llvm::all_of(::llvm::cast<::mlir::ArrayAttr>(attr), [&](::mlir::Attribute attr) { return attr && ((::llvm::isa<::circt::ssp::DependenceAttr>(attr))); }))))
    return emitError() << "attribute '" << attrName
        << "' failed to satisfy constraint: dependence array attribute";
  return ::mlir::success();
}
static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_SSP3(
    ::mlir::Operation *op, ::mlir::Attribute attr, ::llvm::StringRef attrName) {
  return __mlir_ods_local_attr_constraint_SSP3(attr, attrName, [op]() {
    return op->emitOpError();
  });
}

static ::llvm::LogicalResult __mlir_ods_local_region_constraint_SSP1(
    ::mlir::Operation *op, ::mlir::Region &region, ::llvm::StringRef regionName,
    unsigned regionIndex) {
  if (!((::llvm::hasNItems(region, 1)))) {
    return op->emitOpError("region #") << regionIndex
        << (regionName.empty() ? " " : " ('" + regionName + "') ")
        << "failed to verify constraint: region with 1 blocks";
  }
  return ::mlir::success();
}
namespace circt::ssp {


//===----------------------------------------------------------------------===//
// ::circt::ssp::DependenceGraphOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

DependenceGraphOpGenericAdaptorBase::DependenceGraphOpGenericAdaptorBase(DependenceGraphOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}


} // namespace detail
DependenceGraphOpAdaptor::DependenceGraphOpAdaptor(DependenceGraphOp op) : DependenceGraphOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult DependenceGraphOpAdaptor::verify(::mlir::Location loc) {
  return ::mlir::success();
}

::llvm::LogicalResult DependenceGraphOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }
      return ::mlir::success();
}

::mlir::Attribute DependenceGraphOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code DependenceGraphOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine();
}

std::optional<mlir::Attribute> DependenceGraphOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
  return std::nullopt;
}

void DependenceGraphOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
}

void DependenceGraphOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
}

::llvm::LogicalResult DependenceGraphOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    return ::mlir::success();
}

void DependenceGraphOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState) {
      ::mlir::Region* region = odsState.addRegion();
      region->push_back(new ::mlir::Block());
    
}

DependenceGraphOp DependenceGraphOp::create(::mlir::OpBuilder &builder, ::mlir::Location location) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__);
  auto __res__ = ::llvm::dyn_cast<DependenceGraphOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

DependenceGraphOp DependenceGraphOp::create(::mlir::ImplicitLocOpBuilder &builder) {
  return create(builder, builder.getLoc());
}

::llvm::LogicalResult DependenceGraphOp::verifyInvariantsImpl() {
  {
    unsigned index = 0; (void)index;

    for (auto &region : ::llvm::MutableArrayRef((*this)->getRegion(0)))
      if (::mlir::failed(__mlir_ods_local_region_constraint_SSP1(*this, region, "body", index++)))
        return ::mlir::failure();
  }
  return ::mlir::success();
}

::llvm::LogicalResult DependenceGraphOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult DependenceGraphOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
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

void DependenceGraphOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter.printRegion(getBody());
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
}


} // namespace circt::ssp
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::ssp::DependenceGraphOp)

namespace circt::ssp {


//===----------------------------------------------------------------------===//
// ::circt::ssp::InstanceOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

InstanceOpGenericAdaptorBase::InstanceOpGenericAdaptorBase(InstanceOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::std::optional< ::llvm::StringRef > InstanceOpGenericAdaptorBase::getSymName() {
  auto attr = getSymNameAttr();
  return attr ? ::std::optional< ::llvm::StringRef >(attr.getValue()) : (::std::nullopt);
}

::llvm::StringRef InstanceOpGenericAdaptorBase::getProblemName() {
  auto attr = getProblemNameAttr();
  return attr.getValue();
}

::std::optional< ::mlir::ArrayAttr > InstanceOpGenericAdaptorBase::getSspProperties() {
  auto attr = getSspPropertiesAttr();
  return attr ? ::std::optional< ::mlir::ArrayAttr >(attr) : (::std::nullopt);
}


} // namespace detail
InstanceOpAdaptor::InstanceOpAdaptor(InstanceOp op) : InstanceOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult InstanceOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_problemName = getProperties().problemName; (void)tblgen_problemName;
  if (!tblgen_problemName) return emitError(loc, "'ssp.instance' op requires attribute 'problemName'");
  auto tblgen_sspProperties = getProperties().sspProperties; (void)tblgen_sspProperties;
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;

  if (tblgen_sym_name && !((::llvm::isa<::mlir::StringAttr>(tblgen_sym_name))))
    return emitError(loc, "'ssp.instance' op attribute 'sym_name' failed to satisfy constraint: string attribute");

  if (tblgen_problemName && !((::llvm::isa<::mlir::StringAttr>(tblgen_problemName))))
    return emitError(loc, "'ssp.instance' op attribute 'problemName' failed to satisfy constraint: string attribute");

  if (tblgen_sspProperties && !((::llvm::isa<::mlir::ArrayAttr>(tblgen_sspProperties))))
    return emitError(loc, "'ssp.instance' op attribute 'sspProperties' failed to satisfy constraint: array attribute");
  return ::mlir::success();
}

::llvm::LogicalResult InstanceOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.problemName;
       auto attr = dict.get("problemName");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `problemName` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.sspProperties;
       auto attr = dict.get("sspProperties");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `sspProperties` in property conversion: " << attr;
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
      const auto &propStorage = prop.problemName;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("problemName",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.sspProperties;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("sspProperties",
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
    llvm::hash_value(prop.problemName.getAsOpaquePointer()), 
    llvm::hash_value(prop.sspProperties.getAsOpaquePointer()), 
    llvm::hash_value(prop.sym_name.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> InstanceOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "problemName")
      return prop.problemName;

    if (name == "sspProperties")
      return prop.sspProperties;

    if (name == "sym_name")
      return prop.sym_name;
  return std::nullopt;
}

void InstanceOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "problemName") {
       prop.problemName = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.problemName)>>(value);
       return;
    }

    if (name == "sspProperties") {
       prop.sspProperties = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.sspProperties)>>(value);
       return;
    }

    if (name == "sym_name") {
       prop.sym_name = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.sym_name)>>(value);
       return;
    }
}

void InstanceOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.problemName) attrs.append("problemName", prop.problemName);

    if (prop.sspProperties) attrs.append("sspProperties", prop.sspProperties);

    if (prop.sym_name) attrs.append("sym_name", prop.sym_name);
}

::llvm::LogicalResult InstanceOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getProblemNameAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_SSP1(attr, "problemName", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getSspPropertiesAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_SSP2(attr, "sspProperties", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getSymNameAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_SSP1(attr, "sym_name", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult InstanceOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.problemName)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readOptionalAttribute(prop.sspProperties)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readOptionalAttribute(prop.sym_name)))
    return ::mlir::failure();
  return ::mlir::success();
}

void InstanceOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.problemName);

  writer.writeOptionalAttribute(prop.sspProperties);

  writer.writeOptionalAttribute(prop.sym_name);
}

::std::optional< ::llvm::StringRef > InstanceOp::getSymName() {
  auto attr = getSymNameAttr();
  return attr ? ::std::optional< ::llvm::StringRef >(attr.getValue()) : (::std::nullopt);
}

::llvm::StringRef InstanceOp::getProblemName() {
  auto attr = getProblemNameAttr();
  return attr.getValue();
}

::std::optional< ::mlir::ArrayAttr > InstanceOp::getSspProperties() {
  auto attr = getSspPropertiesAttr();
  return attr ? ::std::optional< ::mlir::ArrayAttr >(attr) : (::std::nullopt);
}

void InstanceOp::setSymName(::std::optional<::llvm::StringRef> attrValue) {
    auto &odsProp = getProperties().sym_name;
    if (attrValue)
      odsProp = ::mlir::Builder((*this)->getContext()).getStringAttr(*attrValue);
    else
      odsProp = nullptr;
}

void InstanceOp::setProblemName(::llvm::StringRef attrValue) {
  getProperties().problemName = ::mlir::Builder((*this)->getContext()).getStringAttr(attrValue);
}

void InstanceOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::StringAttr problemName, ::mlir::ArrayAttr sspProperties) {
      odsState.addAttribute(odsBuilder.getStringAttr("problemName"), problemName);
      if (sspProperties)
        odsState.addAttribute(odsBuilder.getStringAttr("sspProperties"), sspProperties);
      ::mlir::Region* region = odsState.addRegion();
      region->push_back(new ::mlir::Block());
    
}

InstanceOp InstanceOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::StringAttr problemName, ::mlir::ArrayAttr sspProperties) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(problemName)>(problemName), std::forward<decltype(sspProperties)>(sspProperties));
  auto __res__ = ::llvm::dyn_cast<InstanceOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

InstanceOp InstanceOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::StringAttr problemName, ::mlir::ArrayAttr sspProperties) {
  return create(builder, builder.getLoc(), std::forward<decltype(problemName)>(problemName), std::forward<decltype(sspProperties)>(sspProperties));
}

::llvm::LogicalResult InstanceOp::verifyInvariantsImpl() {
  auto tblgen_problemName = getProperties().problemName; (void)tblgen_problemName;
  if (!tblgen_problemName) return emitOpError("requires attribute 'problemName'");
  auto tblgen_sspProperties = getProperties().sspProperties; (void)tblgen_sspProperties;
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;

  if (::mlir::failed(__mlir_ods_local_attr_constraint_SSP1(*this, tblgen_sym_name, "sym_name")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_SSP1(*this, tblgen_problemName, "problemName")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_SSP2(*this, tblgen_sspProperties, "sspProperties")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;

    for (auto &region : ::llvm::MutableArrayRef((*this)->getRegion(0)))
      if (::mlir::failed(__mlir_ods_local_region_constraint_SSP1(*this, region, "body", index++)))
        return ::mlir::failure();
  }
  return ::mlir::success();
}

::llvm::LogicalResult InstanceOp::verifyInvariants() {
  if(::mlir::succeeded(verifyInvariantsImpl()) && ::mlir::succeeded(verify()))
    return ::mlir::success();
  return ::mlir::failure();
}

::mlir::ParseResult InstanceOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::StringAttr sym_nameAttr;
  ::mlir::StringAttr problemNameAttr;
  ::mlir::ArrayAttr sspPropertiesAttr;
  std::unique_ptr<::mlir::Region> bodyRegion = std::make_unique<::mlir::Region>();

  // Parsing an optional symbol name doesn't fail, so no need to check the
  // result.
  (void)parser.parseOptionalSymbolName(sym_nameAttr);
  if (sym_nameAttr) result.getOrAddProperties<InstanceOp::Properties>().sym_name = sym_nameAttr;
  if (sym_nameAttr) {
  }
  if (parser.parseKeyword("of"))
    return ::mlir::failure();

  if (parser.parseCustomAttributeWithFallback(problemNameAttr, parser.getBuilder().getType<::mlir::NoneType>())) {
    return ::mlir::failure();
  }
  if (problemNameAttr) result.getOrAddProperties<InstanceOp::Properties>().problemName = problemNameAttr;
  {
    auto odsResult = parseSSPProperties(parser, sspPropertiesAttr);
    if (odsResult) return ::mlir::failure();
    if (sspPropertiesAttr)
      result.getOrAddProperties<InstanceOp::Properties>().sspProperties = sspPropertiesAttr;
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
  return ::mlir::success();
}

void InstanceOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  if (getSymNameAttr()) {
    _odsPrinter << ' ';
    _odsPrinter.printSymbolName(getSymNameAttr().getValue());
  }
  _odsPrinter << ' ' << "of";
  _odsPrinter << ' ';
  _odsPrinter.printAttributeWithoutType(getProblemNameAttr());
  _odsPrinter << ' ';
  printSSPProperties(_odsPrinter, *this, getSspPropertiesAttr());
  _odsPrinter << ' ';
  _odsPrinter.printRegion(getBody());
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("sym_name");
  elidedAttrs.push_back("problemName");
  elidedAttrs.push_back("sspProperties");
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
}


} // namespace circt::ssp
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::ssp::InstanceOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::ssp::detail::InstanceOpGenericAdaptorBase::Properties)

namespace circt::ssp {


//===----------------------------------------------------------------------===//
// ::circt::ssp::OperationOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

OperationOpGenericAdaptorBase::OperationOpGenericAdaptorBase(OperationOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

std::pair<unsigned, unsigned> OperationOpGenericAdaptorBase::getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
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

::std::optional< ::llvm::StringRef > OperationOpGenericAdaptorBase::getSymName() {
  auto attr = getSymNameAttr();
  return attr ? ::std::optional< ::llvm::StringRef >(attr.getValue()) : (::std::nullopt);
}

::std::optional< ::mlir::ArrayAttr > OperationOpGenericAdaptorBase::getDependences() {
  auto attr = getDependencesAttr();
  return attr ? ::std::optional< ::mlir::ArrayAttr >(attr) : (::std::nullopt);
}

::std::optional< ::mlir::ArrayAttr > OperationOpGenericAdaptorBase::getSspProperties() {
  auto attr = getSspPropertiesAttr();
  return attr ? ::std::optional< ::mlir::ArrayAttr >(attr) : (::std::nullopt);
}


} // namespace detail
OperationOpAdaptor::OperationOpAdaptor(OperationOp op) : OperationOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult OperationOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_dependences = getProperties().dependences; (void)tblgen_dependences;
  auto tblgen_sspProperties = getProperties().sspProperties; (void)tblgen_sspProperties;
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;

  if (tblgen_sym_name && !((::llvm::isa<::mlir::StringAttr>(tblgen_sym_name))))
    return emitError(loc, "'ssp.operation' op attribute 'sym_name' failed to satisfy constraint: string attribute");

  if (tblgen_dependences && !(((::llvm::isa<::mlir::ArrayAttr>(tblgen_dependences))) && (::llvm::all_of(::llvm::cast<::mlir::ArrayAttr>(tblgen_dependences), [&](::mlir::Attribute attr) { return attr && ((::llvm::isa<::circt::ssp::DependenceAttr>(attr))); }))))
    return emitError(loc, "'ssp.operation' op attribute 'dependences' failed to satisfy constraint: dependence array attribute");

  if (tblgen_sspProperties && !((::llvm::isa<::mlir::ArrayAttr>(tblgen_sspProperties))))
    return emitError(loc, "'ssp.operation' op attribute 'sspProperties' failed to satisfy constraint: array attribute");
  return ::mlir::success();
}

std::pair<unsigned, unsigned> OperationOp::getODSOperandIndexAndLength(unsigned index) {
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

::mlir::MutableOperandRange OperationOp::getOperandsMutable() {
  auto range = getODSOperandIndexAndLength(0);
  auto mutableRange = ::mlir::MutableOperandRange(getOperation(), range.first, range.second);
  return mutableRange;
}

std::pair<unsigned, unsigned> OperationOp::getODSResultIndexAndLength(unsigned index) {
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

::llvm::LogicalResult OperationOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.dependences;
       auto attr = dict.get("dependences");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `dependences` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.sspProperties;
       auto attr = dict.get("sspProperties");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `sspProperties` in property conversion: " << attr;
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

::mlir::Attribute OperationOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.dependences;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("dependences",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.sspProperties;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("sspProperties",
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

llvm::hash_code OperationOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.dependences.getAsOpaquePointer()), 
    llvm::hash_value(prop.sspProperties.getAsOpaquePointer()), 
    llvm::hash_value(prop.sym_name.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> OperationOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "dependences")
      return prop.dependences;

    if (name == "sspProperties")
      return prop.sspProperties;

    if (name == "sym_name")
      return prop.sym_name;
  return std::nullopt;
}

void OperationOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "dependences") {
       prop.dependences = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.dependences)>>(value);
       return;
    }

    if (name == "sspProperties") {
       prop.sspProperties = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.sspProperties)>>(value);
       return;
    }

    if (name == "sym_name") {
       prop.sym_name = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.sym_name)>>(value);
       return;
    }
}

void OperationOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.dependences) attrs.append("dependences", prop.dependences);

    if (prop.sspProperties) attrs.append("sspProperties", prop.sspProperties);

    if (prop.sym_name) attrs.append("sym_name", prop.sym_name);
}

::llvm::LogicalResult OperationOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getDependencesAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_SSP3(attr, "dependences", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getSspPropertiesAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_SSP2(attr, "sspProperties", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getSymNameAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_SSP1(attr, "sym_name", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult OperationOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readOptionalAttribute(prop.dependences)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readOptionalAttribute(prop.sspProperties)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readOptionalAttribute(prop.sym_name)))
    return ::mlir::failure();
  return ::mlir::success();
}

void OperationOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;

  writer.writeOptionalAttribute(prop.dependences);

  writer.writeOptionalAttribute(prop.sspProperties);

  writer.writeOptionalAttribute(prop.sym_name);
}

::std::optional< ::llvm::StringRef > OperationOp::getSymName() {
  auto attr = getSymNameAttr();
  return attr ? ::std::optional< ::llvm::StringRef >(attr.getValue()) : (::std::nullopt);
}

::std::optional< ::mlir::ArrayAttr > OperationOp::getDependences() {
  auto attr = getDependencesAttr();
  return attr ? ::std::optional< ::mlir::ArrayAttr >(attr) : (::std::nullopt);
}

::std::optional< ::mlir::ArrayAttr > OperationOp::getSspProperties() {
  auto attr = getSspPropertiesAttr();
  return attr ? ::std::optional< ::mlir::ArrayAttr >(attr) : (::std::nullopt);
}

void OperationOp::setSymName(::std::optional<::llvm::StringRef> attrValue) {
    auto &odsProp = getProperties().sym_name;
    if (attrValue)
      odsProp = ::mlir::Builder((*this)->getContext()).getStringAttr(*attrValue);
    else
      odsProp = nullptr;
}

void OperationOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, unsigned numResults, ::mlir::ValueRange operands, ::mlir::StringAttr sym_name, ::mlir::ArrayAttr dependences, ::mlir::ArrayAttr sspProperties) {
      odsState.addTypes(::llvm::SmallVector<::mlir::Type>(numResults, odsBuilder.getNoneType()));
      odsState.addOperands(operands);
      if (sym_name)
        odsState.addAttribute(::mlir::SymbolTable::getSymbolAttrName(), sym_name);
      if (dependences)
        odsState.addAttribute(odsBuilder.getStringAttr("dependences"), dependences);
      if (sspProperties)
        odsState.addAttribute(odsBuilder.getStringAttr("sspProperties"), sspProperties);
    
}

OperationOp OperationOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, unsigned numResults, ::mlir::ValueRange operands, ::mlir::StringAttr sym_name, ::mlir::ArrayAttr dependences, ::mlir::ArrayAttr sspProperties) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(numResults)>(numResults), std::forward<decltype(operands)>(operands), std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(dependences)>(dependences), std::forward<decltype(sspProperties)>(sspProperties));
  auto __res__ = ::llvm::dyn_cast<OperationOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

OperationOp OperationOp::create(::mlir::ImplicitLocOpBuilder &builder, unsigned numResults, ::mlir::ValueRange operands, ::mlir::StringAttr sym_name, ::mlir::ArrayAttr dependences, ::mlir::ArrayAttr sspProperties) {
  return create(builder, builder.getLoc(), std::forward<decltype(numResults)>(numResults), std::forward<decltype(operands)>(operands), std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(dependences)>(dependences), std::forward<decltype(sspProperties)>(sspProperties));
}

::llvm::LogicalResult OperationOp::verifyInvariantsImpl() {
  auto tblgen_dependences = getProperties().dependences; (void)tblgen_dependences;
  auto tblgen_sspProperties = getProperties().sspProperties; (void)tblgen_sspProperties;
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;

  if (::mlir::failed(__mlir_ods_local_attr_constraint_SSP1(*this, tblgen_sym_name, "sym_name")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_SSP3(*this, tblgen_dependences, "dependences")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_SSP2(*this, tblgen_sspProperties, "sspProperties")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_SSP1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_SSP1(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult OperationOp::verifyInvariants() {
  if(::mlir::succeeded(verifyInvariantsImpl()) && ::mlir::succeeded(verify()))
    return ::mlir::success();
  return ::mlir::failure();
}

::llvm::LogicalResult OperationOp::setPropertiesFromParsedAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
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
    if (attr || /*isRequired=*/false) {
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

    auto &propStorage = prop.dependences;
    auto dependencesAttrName = ::mlir::StringAttr::get(ctx, "dependences");
    auto attr = dict.get(dependencesAttrName);
    usedKeys.insert(dependencesAttrName);
    if (attr || /*isRequired=*/false) {
      if (!attr) {
        emitError() << "expected key entry for dependences in DictionaryAttr to set "
                   "Properties.";
        return ::mlir::failure();
      }
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `dependences` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  {

    auto &propStorage = prop.sspProperties;
    auto sspPropertiesAttrName = ::mlir::StringAttr::get(ctx, "sspProperties");
    auto attr = dict.get(sspPropertiesAttrName);
    usedKeys.insert(sspPropertiesAttrName);
    if (attr || /*isRequired=*/false) {
      if (!attr) {
        emitError() << "expected key entry for sspProperties in DictionaryAttr to set "
                   "Properties.";
        return ::mlir::failure();
      }
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `sspProperties` in property conversion: " << attr;
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


} // namespace circt::ssp
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::ssp::OperationOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::ssp::detail::OperationOpGenericAdaptorBase::Properties)

namespace circt::ssp {


//===----------------------------------------------------------------------===//
// ::circt::ssp::OperatorLibraryOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

OperatorLibraryOpGenericAdaptorBase::OperatorLibraryOpGenericAdaptorBase(OperatorLibraryOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::std::optional< ::llvm::StringRef > OperatorLibraryOpGenericAdaptorBase::getSymName() {
  auto attr = getSymNameAttr();
  return attr ? ::std::optional< ::llvm::StringRef >(attr.getValue()) : (::std::nullopt);
}


} // namespace detail
OperatorLibraryOpAdaptor::OperatorLibraryOpAdaptor(OperatorLibraryOp op) : OperatorLibraryOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult OperatorLibraryOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;

  if (tblgen_sym_name && !((::llvm::isa<::mlir::StringAttr>(tblgen_sym_name))))
    return emitError(loc, "'ssp.library' op attribute 'sym_name' failed to satisfy constraint: string attribute");
  return ::mlir::success();
}

::llvm::LogicalResult OperatorLibraryOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
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

::mlir::Attribute OperatorLibraryOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
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

llvm::hash_code OperatorLibraryOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.sym_name.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> OperatorLibraryOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "sym_name")
      return prop.sym_name;
  return std::nullopt;
}

void OperatorLibraryOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "sym_name") {
       prop.sym_name = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.sym_name)>>(value);
       return;
    }
}

void OperatorLibraryOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.sym_name) attrs.append("sym_name", prop.sym_name);
}

::llvm::LogicalResult OperatorLibraryOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getSymNameAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_SSP1(attr, "sym_name", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult OperatorLibraryOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readOptionalAttribute(prop.sym_name)))
    return ::mlir::failure();
  return ::mlir::success();
}

void OperatorLibraryOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;

  writer.writeOptionalAttribute(prop.sym_name);
}

::std::optional< ::llvm::StringRef > OperatorLibraryOp::getSymName() {
  auto attr = getSymNameAttr();
  return attr ? ::std::optional< ::llvm::StringRef >(attr.getValue()) : (::std::nullopt);
}

void OperatorLibraryOp::setSymName(::std::optional<::llvm::StringRef> attrValue) {
    auto &odsProp = getProperties().sym_name;
    if (attrValue)
      odsProp = ::mlir::Builder((*this)->getContext()).getStringAttr(*attrValue);
    else
      odsProp = nullptr;
}

void OperatorLibraryOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState) {
      ::mlir::Region* region = odsState.addRegion();
      region->push_back(new ::mlir::Block());
    
}

OperatorLibraryOp OperatorLibraryOp::create(::mlir::OpBuilder &builder, ::mlir::Location location) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__);
  auto __res__ = ::llvm::dyn_cast<OperatorLibraryOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

OperatorLibraryOp OperatorLibraryOp::create(::mlir::ImplicitLocOpBuilder &builder) {
  return create(builder, builder.getLoc());
}

::llvm::LogicalResult OperatorLibraryOp::verifyInvariantsImpl() {
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;

  if (::mlir::failed(__mlir_ods_local_attr_constraint_SSP1(*this, tblgen_sym_name, "sym_name")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;

    for (auto &region : ::llvm::MutableArrayRef((*this)->getRegion(0)))
      if (::mlir::failed(__mlir_ods_local_region_constraint_SSP1(*this, region, "body", index++)))
        return ::mlir::failure();
  }
  return ::mlir::success();
}

::llvm::LogicalResult OperatorLibraryOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult OperatorLibraryOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::StringAttr sym_nameAttr;
  std::unique_ptr<::mlir::Region> bodyRegion = std::make_unique<::mlir::Region>();

  // Parsing an optional symbol name doesn't fail, so no need to check the
  // result.
  (void)parser.parseOptionalSymbolName(sym_nameAttr);
  if (sym_nameAttr) result.getOrAddProperties<OperatorLibraryOp::Properties>().sym_name = sym_nameAttr;
  if (sym_nameAttr) {
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
  return ::mlir::success();
}

void OperatorLibraryOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  if (getSymNameAttr()) {
    _odsPrinter << ' ';
    _odsPrinter.printSymbolName(getSymNameAttr().getValue());
  }
  _odsPrinter << ' ';
  _odsPrinter.printRegion(getBody());
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("sym_name");
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
}


} // namespace circt::ssp
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::ssp::OperatorLibraryOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::ssp::detail::OperatorLibraryOpGenericAdaptorBase::Properties)

namespace circt::ssp {


//===----------------------------------------------------------------------===//
// ::circt::ssp::OperatorTypeOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

OperatorTypeOpGenericAdaptorBase::OperatorTypeOpGenericAdaptorBase(OperatorTypeOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::llvm::StringRef OperatorTypeOpGenericAdaptorBase::getSymName() {
  auto attr = getSymNameAttr();
  return attr.getValue();
}

::std::optional< ::mlir::ArrayAttr > OperatorTypeOpGenericAdaptorBase::getSspProperties() {
  auto attr = getSspPropertiesAttr();
  return attr ? ::std::optional< ::mlir::ArrayAttr >(attr) : (::std::nullopt);
}


} // namespace detail
OperatorTypeOpAdaptor::OperatorTypeOpAdaptor(OperatorTypeOp op) : OperatorTypeOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult OperatorTypeOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_sspProperties = getProperties().sspProperties; (void)tblgen_sspProperties;
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;
  if (!tblgen_sym_name) return emitError(loc, "'ssp.operator_type' op requires attribute 'sym_name'");

  if (tblgen_sym_name && !((::llvm::isa<::mlir::StringAttr>(tblgen_sym_name))))
    return emitError(loc, "'ssp.operator_type' op attribute 'sym_name' failed to satisfy constraint: string attribute");

  if (tblgen_sspProperties && !((::llvm::isa<::mlir::ArrayAttr>(tblgen_sspProperties))))
    return emitError(loc, "'ssp.operator_type' op attribute 'sspProperties' failed to satisfy constraint: array attribute");
  return ::mlir::success();
}

::llvm::LogicalResult OperatorTypeOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.sspProperties;
       auto attr = dict.get("sspProperties");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `sspProperties` in property conversion: " << attr;
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

::mlir::Attribute OperatorTypeOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.sspProperties;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("sspProperties",
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

llvm::hash_code OperatorTypeOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.sspProperties.getAsOpaquePointer()), 
    llvm::hash_value(prop.sym_name.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> OperatorTypeOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "sspProperties")
      return prop.sspProperties;

    if (name == "sym_name")
      return prop.sym_name;
  return std::nullopt;
}

void OperatorTypeOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "sspProperties") {
       prop.sspProperties = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.sspProperties)>>(value);
       return;
    }

    if (name == "sym_name") {
       prop.sym_name = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.sym_name)>>(value);
       return;
    }
}

void OperatorTypeOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.sspProperties) attrs.append("sspProperties", prop.sspProperties);

    if (prop.sym_name) attrs.append("sym_name", prop.sym_name);
}

::llvm::LogicalResult OperatorTypeOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getSspPropertiesAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_SSP2(attr, "sspProperties", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getSymNameAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_SSP1(attr, "sym_name", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult OperatorTypeOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readOptionalAttribute(prop.sspProperties)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readAttribute(prop.sym_name)))
    return ::mlir::failure();
  return ::mlir::success();
}

void OperatorTypeOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;

  writer.writeOptionalAttribute(prop.sspProperties);
  writer.writeAttribute(prop.sym_name);
}

::llvm::StringRef OperatorTypeOp::getSymName() {
  auto attr = getSymNameAttr();
  return attr.getValue();
}

::std::optional< ::mlir::ArrayAttr > OperatorTypeOp::getSspProperties() {
  auto attr = getSspPropertiesAttr();
  return attr ? ::std::optional< ::mlir::ArrayAttr >(attr) : (::std::nullopt);
}

void OperatorTypeOp::setSymName(::llvm::StringRef attrValue) {
  getProperties().sym_name = ::mlir::Builder((*this)->getContext()).getStringAttr(attrValue);
}

void OperatorTypeOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::StringAttr sym_name, /*optional*/::mlir::ArrayAttr sspProperties) {
  odsState.getOrAddProperties<Properties>().sym_name = sym_name;
  if (sspProperties) {
    odsState.getOrAddProperties<Properties>().sspProperties = sspProperties;
  }
}

OperatorTypeOp OperatorTypeOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::StringAttr sym_name, /*optional*/::mlir::ArrayAttr sspProperties) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(sspProperties)>(sspProperties));
  auto __res__ = ::llvm::dyn_cast<OperatorTypeOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

OperatorTypeOp OperatorTypeOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::StringAttr sym_name, /*optional*/::mlir::ArrayAttr sspProperties) {
  return create(builder, builder.getLoc(), std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(sspProperties)>(sspProperties));
}

void OperatorTypeOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name, /*optional*/::mlir::ArrayAttr sspProperties) {
  odsState.getOrAddProperties<Properties>().sym_name = sym_name;
  if (sspProperties) {
    odsState.getOrAddProperties<Properties>().sspProperties = sspProperties;
  }
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

OperatorTypeOp OperatorTypeOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name, /*optional*/::mlir::ArrayAttr sspProperties) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(sspProperties)>(sspProperties));
  auto __res__ = ::llvm::dyn_cast<OperatorTypeOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

OperatorTypeOp OperatorTypeOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name, /*optional*/::mlir::ArrayAttr sspProperties) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(sspProperties)>(sspProperties));
}

void OperatorTypeOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::llvm::StringRef sym_name, /*optional*/::mlir::ArrayAttr sspProperties) {
  odsState.getOrAddProperties<Properties>().sym_name = odsBuilder.getStringAttr(sym_name);
  if (sspProperties) {
    odsState.getOrAddProperties<Properties>().sspProperties = sspProperties;
  }
}

OperatorTypeOp OperatorTypeOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::llvm::StringRef sym_name, /*optional*/::mlir::ArrayAttr sspProperties) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(sspProperties)>(sspProperties));
  auto __res__ = ::llvm::dyn_cast<OperatorTypeOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

OperatorTypeOp OperatorTypeOp::create(::mlir::ImplicitLocOpBuilder &builder, ::llvm::StringRef sym_name, /*optional*/::mlir::ArrayAttr sspProperties) {
  return create(builder, builder.getLoc(), std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(sspProperties)>(sspProperties));
}

void OperatorTypeOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name, /*optional*/::mlir::ArrayAttr sspProperties) {
  odsState.getOrAddProperties<Properties>().sym_name = odsBuilder.getStringAttr(sym_name);
  if (sspProperties) {
    odsState.getOrAddProperties<Properties>().sspProperties = sspProperties;
  }
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

OperatorTypeOp OperatorTypeOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name, /*optional*/::mlir::ArrayAttr sspProperties) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(sspProperties)>(sspProperties));
  auto __res__ = ::llvm::dyn_cast<OperatorTypeOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

OperatorTypeOp OperatorTypeOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name, /*optional*/::mlir::ArrayAttr sspProperties) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(sspProperties)>(sspProperties));
}

void OperatorTypeOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<OperatorTypeOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

OperatorTypeOp OperatorTypeOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<OperatorTypeOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

OperatorTypeOp OperatorTypeOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void OperatorTypeOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

OperatorTypeOp OperatorTypeOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<OperatorTypeOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

OperatorTypeOp OperatorTypeOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult OperatorTypeOp::verifyInvariantsImpl() {
  auto tblgen_sspProperties = getProperties().sspProperties; (void)tblgen_sspProperties;
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;
  if (!tblgen_sym_name) return emitOpError("requires attribute 'sym_name'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_SSP1(*this, tblgen_sym_name, "sym_name")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_SSP2(*this, tblgen_sspProperties, "sspProperties")))
    return ::mlir::failure();
  return ::mlir::success();
}

::llvm::LogicalResult OperatorTypeOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult OperatorTypeOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::StringAttr sym_nameAttr;
  ::mlir::ArrayAttr sspPropertiesAttr;

  if (parser.parseSymbolName(sym_nameAttr))
    return ::mlir::failure();
  if (sym_nameAttr) result.getOrAddProperties<OperatorTypeOp::Properties>().sym_name = sym_nameAttr;
  {
    auto odsResult = parseSSPProperties(parser, sspPropertiesAttr);
    if (odsResult) return ::mlir::failure();
    if (sspPropertiesAttr)
      result.getOrAddProperties<OperatorTypeOp::Properties>().sspProperties = sspPropertiesAttr;
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

void OperatorTypeOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter.printSymbolName(getSymNameAttr().getValue());
  _odsPrinter << ' ';
  printSSPProperties(_odsPrinter, *this, getSspPropertiesAttr());
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("sym_name");
  elidedAttrs.push_back("sspProperties");
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
}


} // namespace circt::ssp
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::ssp::OperatorTypeOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::ssp::detail::OperatorTypeOpGenericAdaptorBase::Properties)

namespace circt::ssp {


//===----------------------------------------------------------------------===//
// ::circt::ssp::ResourceLibraryOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

ResourceLibraryOpGenericAdaptorBase::ResourceLibraryOpGenericAdaptorBase(ResourceLibraryOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::std::optional< ::llvm::StringRef > ResourceLibraryOpGenericAdaptorBase::getSymName() {
  auto attr = getSymNameAttr();
  return attr ? ::std::optional< ::llvm::StringRef >(attr.getValue()) : (::std::nullopt);
}


} // namespace detail
ResourceLibraryOpAdaptor::ResourceLibraryOpAdaptor(ResourceLibraryOp op) : ResourceLibraryOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult ResourceLibraryOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;

  if (tblgen_sym_name && !((::llvm::isa<::mlir::StringAttr>(tblgen_sym_name))))
    return emitError(loc, "'ssp.resource' op attribute 'sym_name' failed to satisfy constraint: string attribute");
  return ::mlir::success();
}

::llvm::LogicalResult ResourceLibraryOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
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

::mlir::Attribute ResourceLibraryOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
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

llvm::hash_code ResourceLibraryOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.sym_name.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> ResourceLibraryOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "sym_name")
      return prop.sym_name;
  return std::nullopt;
}

void ResourceLibraryOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "sym_name") {
       prop.sym_name = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.sym_name)>>(value);
       return;
    }
}

void ResourceLibraryOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.sym_name) attrs.append("sym_name", prop.sym_name);
}

::llvm::LogicalResult ResourceLibraryOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getSymNameAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_SSP1(attr, "sym_name", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult ResourceLibraryOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readOptionalAttribute(prop.sym_name)))
    return ::mlir::failure();
  return ::mlir::success();
}

void ResourceLibraryOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;

  writer.writeOptionalAttribute(prop.sym_name);
}

::std::optional< ::llvm::StringRef > ResourceLibraryOp::getSymName() {
  auto attr = getSymNameAttr();
  return attr ? ::std::optional< ::llvm::StringRef >(attr.getValue()) : (::std::nullopt);
}

void ResourceLibraryOp::setSymName(::std::optional<::llvm::StringRef> attrValue) {
    auto &odsProp = getProperties().sym_name;
    if (attrValue)
      odsProp = ::mlir::Builder((*this)->getContext()).getStringAttr(*attrValue);
    else
      odsProp = nullptr;
}

void ResourceLibraryOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState) {
      ::mlir::Region* region = odsState.addRegion();
      region->push_back(new ::mlir::Block());
    
}

ResourceLibraryOp ResourceLibraryOp::create(::mlir::OpBuilder &builder, ::mlir::Location location) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__);
  auto __res__ = ::llvm::dyn_cast<ResourceLibraryOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ResourceLibraryOp ResourceLibraryOp::create(::mlir::ImplicitLocOpBuilder &builder) {
  return create(builder, builder.getLoc());
}

::llvm::LogicalResult ResourceLibraryOp::verifyInvariantsImpl() {
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;

  if (::mlir::failed(__mlir_ods_local_attr_constraint_SSP1(*this, tblgen_sym_name, "sym_name")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;

    for (auto &region : ::llvm::MutableArrayRef((*this)->getRegion(0)))
      if (::mlir::failed(__mlir_ods_local_region_constraint_SSP1(*this, region, "body", index++)))
        return ::mlir::failure();
  }
  return ::mlir::success();
}

::llvm::LogicalResult ResourceLibraryOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult ResourceLibraryOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::StringAttr sym_nameAttr;
  std::unique_ptr<::mlir::Region> bodyRegion = std::make_unique<::mlir::Region>();

  // Parsing an optional symbol name doesn't fail, so no need to check the
  // result.
  (void)parser.parseOptionalSymbolName(sym_nameAttr);
  if (sym_nameAttr) result.getOrAddProperties<ResourceLibraryOp::Properties>().sym_name = sym_nameAttr;
  if (sym_nameAttr) {
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
  return ::mlir::success();
}

void ResourceLibraryOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  if (getSymNameAttr()) {
    _odsPrinter << ' ';
    _odsPrinter.printSymbolName(getSymNameAttr().getValue());
  }
  _odsPrinter << ' ';
  _odsPrinter.printRegion(getBody());
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("sym_name");
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
}


} // namespace circt::ssp
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::ssp::ResourceLibraryOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::ssp::detail::ResourceLibraryOpGenericAdaptorBase::Properties)

namespace circt::ssp {


//===----------------------------------------------------------------------===//
// ::circt::ssp::ResourceTypeOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

ResourceTypeOpGenericAdaptorBase::ResourceTypeOpGenericAdaptorBase(ResourceTypeOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::llvm::StringRef ResourceTypeOpGenericAdaptorBase::getSymName() {
  auto attr = getSymNameAttr();
  return attr.getValue();
}

::std::optional< ::mlir::ArrayAttr > ResourceTypeOpGenericAdaptorBase::getSspProperties() {
  auto attr = getSspPropertiesAttr();
  return attr ? ::std::optional< ::mlir::ArrayAttr >(attr) : (::std::nullopt);
}


} // namespace detail
ResourceTypeOpAdaptor::ResourceTypeOpAdaptor(ResourceTypeOp op) : ResourceTypeOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult ResourceTypeOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_sspProperties = getProperties().sspProperties; (void)tblgen_sspProperties;
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;
  if (!tblgen_sym_name) return emitError(loc, "'ssp.resource_type' op requires attribute 'sym_name'");

  if (tblgen_sym_name && !((::llvm::isa<::mlir::StringAttr>(tblgen_sym_name))))
    return emitError(loc, "'ssp.resource_type' op attribute 'sym_name' failed to satisfy constraint: string attribute");

  if (tblgen_sspProperties && !((::llvm::isa<::mlir::ArrayAttr>(tblgen_sspProperties))))
    return emitError(loc, "'ssp.resource_type' op attribute 'sspProperties' failed to satisfy constraint: array attribute");
  return ::mlir::success();
}

::llvm::LogicalResult ResourceTypeOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.sspProperties;
       auto attr = dict.get("sspProperties");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `sspProperties` in property conversion: " << attr;
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

::mlir::Attribute ResourceTypeOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.sspProperties;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("sspProperties",
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

llvm::hash_code ResourceTypeOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.sspProperties.getAsOpaquePointer()), 
    llvm::hash_value(prop.sym_name.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> ResourceTypeOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "sspProperties")
      return prop.sspProperties;

    if (name == "sym_name")
      return prop.sym_name;
  return std::nullopt;
}

void ResourceTypeOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "sspProperties") {
       prop.sspProperties = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.sspProperties)>>(value);
       return;
    }

    if (name == "sym_name") {
       prop.sym_name = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.sym_name)>>(value);
       return;
    }
}

void ResourceTypeOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.sspProperties) attrs.append("sspProperties", prop.sspProperties);

    if (prop.sym_name) attrs.append("sym_name", prop.sym_name);
}

::llvm::LogicalResult ResourceTypeOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getSspPropertiesAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_SSP2(attr, "sspProperties", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getSymNameAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_SSP1(attr, "sym_name", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult ResourceTypeOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readOptionalAttribute(prop.sspProperties)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readAttribute(prop.sym_name)))
    return ::mlir::failure();
  return ::mlir::success();
}

void ResourceTypeOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;

  writer.writeOptionalAttribute(prop.sspProperties);
  writer.writeAttribute(prop.sym_name);
}

::llvm::StringRef ResourceTypeOp::getSymName() {
  auto attr = getSymNameAttr();
  return attr.getValue();
}

::std::optional< ::mlir::ArrayAttr > ResourceTypeOp::getSspProperties() {
  auto attr = getSspPropertiesAttr();
  return attr ? ::std::optional< ::mlir::ArrayAttr >(attr) : (::std::nullopt);
}

void ResourceTypeOp::setSymName(::llvm::StringRef attrValue) {
  getProperties().sym_name = ::mlir::Builder((*this)->getContext()).getStringAttr(attrValue);
}

void ResourceTypeOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::StringAttr sym_name, /*optional*/::mlir::ArrayAttr sspProperties) {
  odsState.getOrAddProperties<Properties>().sym_name = sym_name;
  if (sspProperties) {
    odsState.getOrAddProperties<Properties>().sspProperties = sspProperties;
  }
}

ResourceTypeOp ResourceTypeOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::StringAttr sym_name, /*optional*/::mlir::ArrayAttr sspProperties) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(sspProperties)>(sspProperties));
  auto __res__ = ::llvm::dyn_cast<ResourceTypeOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ResourceTypeOp ResourceTypeOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::StringAttr sym_name, /*optional*/::mlir::ArrayAttr sspProperties) {
  return create(builder, builder.getLoc(), std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(sspProperties)>(sspProperties));
}

void ResourceTypeOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name, /*optional*/::mlir::ArrayAttr sspProperties) {
  odsState.getOrAddProperties<Properties>().sym_name = sym_name;
  if (sspProperties) {
    odsState.getOrAddProperties<Properties>().sspProperties = sspProperties;
  }
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

ResourceTypeOp ResourceTypeOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name, /*optional*/::mlir::ArrayAttr sspProperties) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(sspProperties)>(sspProperties));
  auto __res__ = ::llvm::dyn_cast<ResourceTypeOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ResourceTypeOp ResourceTypeOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name, /*optional*/::mlir::ArrayAttr sspProperties) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(sspProperties)>(sspProperties));
}

void ResourceTypeOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::llvm::StringRef sym_name, /*optional*/::mlir::ArrayAttr sspProperties) {
  odsState.getOrAddProperties<Properties>().sym_name = odsBuilder.getStringAttr(sym_name);
  if (sspProperties) {
    odsState.getOrAddProperties<Properties>().sspProperties = sspProperties;
  }
}

ResourceTypeOp ResourceTypeOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::llvm::StringRef sym_name, /*optional*/::mlir::ArrayAttr sspProperties) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(sspProperties)>(sspProperties));
  auto __res__ = ::llvm::dyn_cast<ResourceTypeOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ResourceTypeOp ResourceTypeOp::create(::mlir::ImplicitLocOpBuilder &builder, ::llvm::StringRef sym_name, /*optional*/::mlir::ArrayAttr sspProperties) {
  return create(builder, builder.getLoc(), std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(sspProperties)>(sspProperties));
}

void ResourceTypeOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name, /*optional*/::mlir::ArrayAttr sspProperties) {
  odsState.getOrAddProperties<Properties>().sym_name = odsBuilder.getStringAttr(sym_name);
  if (sspProperties) {
    odsState.getOrAddProperties<Properties>().sspProperties = sspProperties;
  }
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

ResourceTypeOp ResourceTypeOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name, /*optional*/::mlir::ArrayAttr sspProperties) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(sspProperties)>(sspProperties));
  auto __res__ = ::llvm::dyn_cast<ResourceTypeOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ResourceTypeOp ResourceTypeOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name, /*optional*/::mlir::ArrayAttr sspProperties) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(sym_name)>(sym_name), std::forward<decltype(sspProperties)>(sspProperties));
}

void ResourceTypeOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<ResourceTypeOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

ResourceTypeOp ResourceTypeOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<ResourceTypeOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ResourceTypeOp ResourceTypeOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void ResourceTypeOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

ResourceTypeOp ResourceTypeOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<ResourceTypeOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

ResourceTypeOp ResourceTypeOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult ResourceTypeOp::verifyInvariantsImpl() {
  auto tblgen_sspProperties = getProperties().sspProperties; (void)tblgen_sspProperties;
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;
  if (!tblgen_sym_name) return emitOpError("requires attribute 'sym_name'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_SSP1(*this, tblgen_sym_name, "sym_name")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_SSP2(*this, tblgen_sspProperties, "sspProperties")))
    return ::mlir::failure();
  return ::mlir::success();
}

::llvm::LogicalResult ResourceTypeOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult ResourceTypeOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::StringAttr sym_nameAttr;
  ::mlir::ArrayAttr sspPropertiesAttr;

  if (parser.parseSymbolName(sym_nameAttr))
    return ::mlir::failure();
  if (sym_nameAttr) result.getOrAddProperties<ResourceTypeOp::Properties>().sym_name = sym_nameAttr;
  {
    auto odsResult = parseSSPProperties(parser, sspPropertiesAttr);
    if (odsResult) return ::mlir::failure();
    if (sspPropertiesAttr)
      result.getOrAddProperties<ResourceTypeOp::Properties>().sspProperties = sspPropertiesAttr;
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

void ResourceTypeOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter.printSymbolName(getSymNameAttr().getValue());
  _odsPrinter << ' ';
  printSSPProperties(_odsPrinter, *this, getSspPropertiesAttr());
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("sym_name");
  elidedAttrs.push_back("sspProperties");
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
}


} // namespace circt::ssp
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::ssp::ResourceTypeOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::ssp::detail::ResourceTypeOpGenericAdaptorBase::Properties)


#endif // GET_OP_CLASSES

