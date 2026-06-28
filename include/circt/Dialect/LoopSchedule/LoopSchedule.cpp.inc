/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Op Definitions                                                             *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: LoopSchedule.td                                                      *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

#ifdef GET_OP_LIST
#undef GET_OP_LIST

::circt::loopschedule::LoopSchedulePipelineOp,
::circt::loopschedule::LoopSchedulePipelineStageOp,
::circt::loopschedule::LoopScheduleRegisterOp,
::circt::loopschedule::LoopScheduleTerminatorOp
#endif // GET_OP_LIST

#ifdef GET_OP_CLASSES
#undef GET_OP_CLASSES


//===----------------------------------------------------------------------===//
// Local Utility Method Definitions
//===----------------------------------------------------------------------===//


static ::llvm::LogicalResult __mlir_ods_local_type_constraint_LoopSchedule1(
    ::mlir::Operation *op, ::mlir::Type type, ::llvm::StringRef valueKind,
    unsigned valueIndex) {
  if (!(!((::llvm::isa<::mlir::TokenType>(type))))) {
    return op->emitOpError(valueKind) << " #" << valueIndex
        << " must be variadic of any non-token type, but got " << type;
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_type_constraint_LoopSchedule2(
    ::mlir::Operation *op, ::mlir::Type type, ::llvm::StringRef valueKind,
    unsigned valueIndex) {
  if (!((type.isSignlessInteger(1)))) {
    return op->emitOpError(valueKind) << " #" << valueIndex
        << " must be 1-bit signless integer, but got " << type;
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_LoopSchedule1(
    ::mlir::Attribute attr, ::llvm::StringRef attrName, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  if (attr && !(((::llvm::isa<::mlir::IntegerAttr>(attr))) && ((::llvm::cast<::mlir::IntegerAttr>(attr).getType().isSignlessInteger(64)))))
    return emitError() << "attribute '" << attrName
        << "' failed to satisfy constraint: 64-bit signless integer attribute";
  return ::mlir::success();
}
static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_LoopSchedule1(
    ::mlir::Operation *op, ::mlir::Attribute attr, ::llvm::StringRef attrName) {
  return __mlir_ods_local_attr_constraint_LoopSchedule1(attr, attrName, [op]() {
    return op->emitOpError();
  });
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_LoopSchedule2(
    ::mlir::Attribute attr, ::llvm::StringRef attrName, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  if (attr && !(((::llvm::isa<::mlir::IntegerAttr>(attr))) && ((::llvm::cast<::mlir::IntegerAttr>(attr).getType().isSignedInteger(64)))))
    return emitError() << "attribute '" << attrName
        << "' failed to satisfy constraint: 64-bit signed integer attribute";
  return ::mlir::success();
}
static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_LoopSchedule2(
    ::mlir::Operation *op, ::mlir::Attribute attr, ::llvm::StringRef attrName) {
  return __mlir_ods_local_attr_constraint_LoopSchedule2(attr, attrName, [op]() {
    return op->emitOpError();
  });
}

static ::llvm::LogicalResult __mlir_ods_local_region_constraint_LoopSchedule1(
    ::mlir::Operation *op, ::mlir::Region &region, ::llvm::StringRef regionName,
    unsigned regionIndex) {
  if (!((::llvm::hasNItems(region, 1)))) {
    return op->emitOpError("region #") << regionIndex
        << (regionName.empty() ? " " : " ('" + regionName + "') ")
        << "failed to verify constraint: region with 1 blocks";
  }
  return ::mlir::success();
}
namespace circt::loopschedule {


//===----------------------------------------------------------------------===//
// ::circt::loopschedule::LoopSchedulePipelineOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

LoopSchedulePipelineOpGenericAdaptorBase::LoopSchedulePipelineOpGenericAdaptorBase(LoopSchedulePipelineOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

std::pair<unsigned, unsigned> LoopSchedulePipelineOpGenericAdaptorBase::getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
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

uint64_t LoopSchedulePipelineOpGenericAdaptorBase::getII() {
  auto attr = getIIAttr();
  return attr.getValue().getZExtValue();
}

::std::optional<uint64_t> LoopSchedulePipelineOpGenericAdaptorBase::getTripCount() {
  auto attr = getTripCountAttr();
  return attr ? ::std::optional<uint64_t>(attr.getValue().getZExtValue()) : (::std::nullopt);
}


} // namespace detail
LoopSchedulePipelineOpAdaptor::LoopSchedulePipelineOpAdaptor(LoopSchedulePipelineOp op) : LoopSchedulePipelineOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult LoopSchedulePipelineOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_II = getProperties().II; (void)tblgen_II;
  if (!tblgen_II) return emitError(loc, "'loopschedule.pipeline' op requires attribute 'II'");
  auto tblgen_tripCount = getProperties().tripCount; (void)tblgen_tripCount;

  if (tblgen_II && !(((::llvm::isa<::mlir::IntegerAttr>(tblgen_II))) && ((::llvm::cast<::mlir::IntegerAttr>(tblgen_II).getType().isSignlessInteger(64)))))
    return emitError(loc, "'loopschedule.pipeline' op attribute 'II' failed to satisfy constraint: 64-bit signless integer attribute");

  if (tblgen_tripCount && !(((::llvm::isa<::mlir::IntegerAttr>(tblgen_tripCount))) && ((::llvm::cast<::mlir::IntegerAttr>(tblgen_tripCount).getType().isSignlessInteger(64)))))
    return emitError(loc, "'loopschedule.pipeline' op attribute 'tripCount' failed to satisfy constraint: 64-bit signless integer attribute");
  return ::mlir::success();
}

std::pair<unsigned, unsigned> LoopSchedulePipelineOp::getODSOperandIndexAndLength(unsigned index) {
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

::mlir::MutableOperandRange LoopSchedulePipelineOp::getIterArgsMutable() {
  auto range = getODSOperandIndexAndLength(0);
  auto mutableRange = ::mlir::MutableOperandRange(getOperation(), range.first, range.second);
  return mutableRange;
}

std::pair<unsigned, unsigned> LoopSchedulePipelineOp::getODSResultIndexAndLength(unsigned index) {
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

::llvm::LogicalResult LoopSchedulePipelineOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.II;
       auto attr = dict.get("II");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `II` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.tripCount;
       auto attr = dict.get("tripCount");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `tripCount` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  return ::mlir::success();
}

::mlir::Attribute LoopSchedulePipelineOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.II;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("II",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.tripCount;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("tripCount",
                                       propStorage));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code LoopSchedulePipelineOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.II.getAsOpaquePointer()), 
    llvm::hash_value(prop.tripCount.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> LoopSchedulePipelineOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "II")
      return prop.II;

    if (name == "tripCount")
      return prop.tripCount;
  return std::nullopt;
}

void LoopSchedulePipelineOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "II") {
       prop.II = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.II)>>(value);
       return;
    }

    if (name == "tripCount") {
       prop.tripCount = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.tripCount)>>(value);
       return;
    }
}

void LoopSchedulePipelineOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.II) attrs.append("II", prop.II);

    if (prop.tripCount) attrs.append("tripCount", prop.tripCount);
}

::llvm::LogicalResult LoopSchedulePipelineOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getIIAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_LoopSchedule1(attr, "II", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getTripCountAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_LoopSchedule1(attr, "tripCount", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult LoopSchedulePipelineOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.II)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readOptionalAttribute(prop.tripCount)))
    return ::mlir::failure();
  return ::mlir::success();
}

void LoopSchedulePipelineOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.II);

  writer.writeOptionalAttribute(prop.tripCount);
}

uint64_t LoopSchedulePipelineOp::getII() {
  auto attr = getIIAttr();
  return attr.getValue().getZExtValue();
}

::std::optional<uint64_t> LoopSchedulePipelineOp::getTripCount() {
  auto attr = getTripCountAttr();
  return attr ? ::std::optional<uint64_t>(attr.getValue().getZExtValue()) : (::std::nullopt);
}

void LoopSchedulePipelineOp::setII(uint64_t attrValue) {
  getProperties().II = ::mlir::Builder((*this)->getContext()).getIntegerAttr(::mlir::Builder((*this)->getContext()).getIntegerType(64), attrValue);
}

void LoopSchedulePipelineOp::setTripCount(::std::optional<uint64_t> attrValue) {
    auto &odsProp = getProperties().tripCount;
    if (attrValue)
      odsProp = ::mlir::Builder((*this)->getContext()).getIntegerAttr(::mlir::Builder((*this)->getContext()).getIntegerType(64), *attrValue);
    else
      odsProp = nullptr;
}

LoopSchedulePipelineOp LoopSchedulePipelineOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, mlir::TypeRange resultTypes, mlir::IntegerAttr II, std::optional<IntegerAttr> tripCount, mlir::ValueRange iterArgs) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(II)>(II), std::forward<decltype(tripCount)>(tripCount), std::forward<decltype(iterArgs)>(iterArgs));
  auto __res__ = ::llvm::dyn_cast<LoopSchedulePipelineOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

LoopSchedulePipelineOp LoopSchedulePipelineOp::create(::mlir::ImplicitLocOpBuilder &builder, mlir::TypeRange resultTypes, mlir::IntegerAttr II, std::optional<IntegerAttr> tripCount, mlir::ValueRange iterArgs) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(II)>(II), std::forward<decltype(tripCount)>(tripCount), std::forward<decltype(iterArgs)>(iterArgs));
}

::llvm::LogicalResult LoopSchedulePipelineOp::verifyInvariantsImpl() {
  auto tblgen_II = getProperties().II; (void)tblgen_II;
  if (!tblgen_II) return emitOpError("requires attribute 'II'");
  auto tblgen_tripCount = getProperties().tripCount; (void)tblgen_tripCount;

  if (::mlir::failed(__mlir_ods_local_attr_constraint_LoopSchedule1(*this, tblgen_II, "II")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_LoopSchedule1(*this, tblgen_tripCount, "tripCount")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_LoopSchedule1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_LoopSchedule1(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;

    for (auto &region : ::llvm::MutableArrayRef((*this)->getRegion(0)))
      if (::mlir::failed(__mlir_ods_local_region_constraint_LoopSchedule1(*this, region, "condition", index++)))
        return ::mlir::failure();

    for (auto &region : ::llvm::MutableArrayRef((*this)->getRegion(1)))
      if (::mlir::failed(__mlir_ods_local_region_constraint_LoopSchedule1(*this, region, "stages", index++)))
        return ::mlir::failure();
  }
  return ::mlir::success();
}

::llvm::LogicalResult LoopSchedulePipelineOp::verifyInvariants() {
  if(::mlir::succeeded(verifyInvariantsImpl()) && ::mlir::succeeded(verify()))
    return ::mlir::success();
  return ::mlir::failure();
}

::llvm::LogicalResult LoopSchedulePipelineOp::setPropertiesFromParsedAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
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

    auto &propStorage = prop.II;
    auto IIAttrName = ::mlir::StringAttr::get(ctx, "II");
    auto attr = dict.get(IIAttrName);
    usedKeys.insert(IIAttrName);
    if (attr || /*isRequired=*/true) {
      if (!attr) {
        emitError() << "expected key entry for II in DictionaryAttr to set "
                   "Properties.";
        return ::mlir::failure();
      }
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `II` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  {

    auto &propStorage = prop.tripCount;
    auto tripCountAttrName = ::mlir::StringAttr::get(ctx, "tripCount");
    auto attr = dict.get(tripCountAttrName);
    usedKeys.insert(tripCountAttrName);
    if (attr || /*isRequired=*/false) {
      if (!attr) {
        emitError() << "expected key entry for tripCount in DictionaryAttr to set "
                   "Properties.";
        return ::mlir::failure();
      }
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `tripCount` in property conversion: " << attr;
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


} // namespace circt::loopschedule
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::loopschedule::LoopSchedulePipelineOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::loopschedule::detail::LoopSchedulePipelineOpGenericAdaptorBase::Properties)

namespace circt::loopschedule {


//===----------------------------------------------------------------------===//
// ::circt::loopschedule::LoopSchedulePipelineStageOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

LoopSchedulePipelineStageOpGenericAdaptorBase::LoopSchedulePipelineStageOpGenericAdaptorBase(LoopSchedulePipelineStageOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

std::pair<unsigned, unsigned> LoopSchedulePipelineStageOpGenericAdaptorBase::getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
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

int64_t LoopSchedulePipelineStageOpGenericAdaptorBase::getStart() {
  auto attr = getStartAttr();
  return attr.getValue().getSExtValue();
}


} // namespace detail
LoopSchedulePipelineStageOpAdaptor::LoopSchedulePipelineStageOpAdaptor(LoopSchedulePipelineStageOp op) : LoopSchedulePipelineStageOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult LoopSchedulePipelineStageOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_start = getProperties().start; (void)tblgen_start;
  if (!tblgen_start) return emitError(loc, "'loopschedule.pipeline.stage' op requires attribute 'start'");

  if (tblgen_start && !(((::llvm::isa<::mlir::IntegerAttr>(tblgen_start))) && ((::llvm::cast<::mlir::IntegerAttr>(tblgen_start).getType().isSignedInteger(64)))))
    return emitError(loc, "'loopschedule.pipeline.stage' op attribute 'start' failed to satisfy constraint: 64-bit signed integer attribute");
  return ::mlir::success();
}

std::pair<unsigned, unsigned> LoopSchedulePipelineStageOp::getODSOperandIndexAndLength(unsigned index) {
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

::mlir::MutableOperandRange LoopSchedulePipelineStageOp::getWhenMutable() {
  auto range = getODSOperandIndexAndLength(0);
  auto mutableRange = ::mlir::MutableOperandRange(getOperation(), range.first, range.second);
  return mutableRange;
}

std::pair<unsigned, unsigned> LoopSchedulePipelineStageOp::getODSResultIndexAndLength(unsigned index) {
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

::llvm::LogicalResult LoopSchedulePipelineStageOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
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

::mlir::Attribute LoopSchedulePipelineStageOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

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

llvm::hash_code LoopSchedulePipelineStageOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.start.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> LoopSchedulePipelineStageOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "start")
      return prop.start;
  return std::nullopt;
}

void LoopSchedulePipelineStageOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "start") {
       prop.start = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.start)>>(value);
       return;
    }
}

void LoopSchedulePipelineStageOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.start) attrs.append("start", prop.start);
}

::llvm::LogicalResult LoopSchedulePipelineStageOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getStartAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_LoopSchedule2(attr, "start", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult LoopSchedulePipelineStageOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.start)))
    return ::mlir::failure();
  return ::mlir::success();
}

void LoopSchedulePipelineStageOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.start);
}

int64_t LoopSchedulePipelineStageOp::getStart() {
  auto attr = getStartAttr();
  return attr.getValue().getSExtValue();
}

void LoopSchedulePipelineStageOp::setStart(int64_t attrValue) {
  getProperties().start = ::mlir::Builder((*this)->getContext()).getIntegerAttr(::mlir::Builder((*this)->getContext()).getIntegerType(64, /*isSigned=*/true), attrValue);
}

LoopSchedulePipelineStageOp LoopSchedulePipelineStageOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, mlir::TypeRange resultTypes, mlir::IntegerAttr start) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(start)>(start));
  auto __res__ = ::llvm::dyn_cast<LoopSchedulePipelineStageOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

LoopSchedulePipelineStageOp LoopSchedulePipelineStageOp::create(::mlir::ImplicitLocOpBuilder &builder, mlir::TypeRange resultTypes, mlir::IntegerAttr start) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(start)>(start));
}

::llvm::LogicalResult LoopSchedulePipelineStageOp::verifyInvariantsImpl() {
  auto tblgen_start = getProperties().start; (void)tblgen_start;
  if (!tblgen_start) return emitOpError("requires attribute 'start'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_LoopSchedule2(*this, tblgen_start, "start")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    if (valueGroup0.size() > 1) {
      return emitOpError("operand group starting at #") << index
          << " requires 0 or 1 element, but found " << valueGroup0.size();
    }

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_LoopSchedule2(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_LoopSchedule1(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;

    for (auto &region : ::llvm::MutableArrayRef((*this)->getRegion(0)))
      if (::mlir::failed(__mlir_ods_local_region_constraint_LoopSchedule1(*this, region, "body", index++)))
        return ::mlir::failure();
  }
  return ::mlir::success();
}

::llvm::LogicalResult LoopSchedulePipelineStageOp::verifyInvariants() {
  if(::mlir::succeeded(verifyInvariantsImpl()) && ::mlir::succeeded(verify()))
    return ::mlir::success();
  return ::mlir::failure();
}

::mlir::ParseResult LoopSchedulePipelineStageOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::IntegerAttr startAttr;
  ::llvm::SmallVector<::mlir::OpAsmParser::UnresolvedOperand, 4> whenOperands;
  ::llvm::SMLoc whenOperandsLoc;
  (void)whenOperandsLoc;
  std::unique_ptr<::mlir::Region> bodyRegion = std::make_unique<::mlir::Region>();
  ::llvm::SmallVector<::mlir::Type, 1> resultsTypes;
  if (parser.parseKeyword("start"))
    return ::mlir::failure();
  if (parser.parseEqual())
    return ::mlir::failure();

  if (parser.parseCustomAttributeWithFallback(startAttr, parser.getBuilder().getIntegerType(64, /*isSigned=*/true))) {
    return ::mlir::failure();
  }
  if (startAttr) result.getOrAddProperties<LoopSchedulePipelineStageOp::Properties>().start = startAttr;
  if (::mlir::succeeded(parser.parseOptionalKeyword("when"))) {

  {
    whenOperandsLoc = parser.getCurrentLocation();
    ::mlir::OpAsmParser::UnresolvedOperand operand;
    ::mlir::OptionalParseResult parseResult =
                                    parser.parseOptionalOperand(operand);
    if (parseResult.has_value()) {
      if (failed(*parseResult))
        return ::mlir::failure();
      whenOperands.push_back(operand);
    }
  }
  }

  if (parser.parseRegion(*bodyRegion))
    return ::mlir::failure();
  if (::mlir::succeeded(parser.parseOptionalColon())) {

  if (parser.parseTypeList(resultsTypes))
    return ::mlir::failure();
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
  result.addRegion(std::move(bodyRegion));
  ::mlir::Type odsBuildableType0 = parser.getBuilder().getIntegerType(1);
  result.addTypes(resultsTypes);
  if (!whenOperands.empty()) {
  if (parser.resolveOperands(whenOperands, odsBuildableType0, whenOperandsLoc, result.operands))
    return ::mlir::failure();
  }
  return ::mlir::success();
}

void LoopSchedulePipelineStageOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ' << "start";
  _odsPrinter << ' ' << "=";
  _odsPrinter << ' ';
  _odsPrinter.printAttributeWithoutType(getStartAttr());
  if (getWhen()) {
    _odsPrinter << ' ' << "when";
    _odsPrinter << ' ';
    if (::mlir::Value value = getWhen())
      _odsPrinter << value;
  }
  _odsPrinter << ' ';
  _odsPrinter.printRegion(getBody());
  if (!getResults().empty()) {
    _odsPrinter << ' ' << ":";
    _odsPrinter << ' ';
    _odsPrinter << getResults().getTypes();
  }
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("start");
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
}


} // namespace circt::loopschedule
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::loopschedule::LoopSchedulePipelineStageOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::loopschedule::detail::LoopSchedulePipelineStageOpGenericAdaptorBase::Properties)

namespace circt::loopschedule {


//===----------------------------------------------------------------------===//
// ::circt::loopschedule::LoopScheduleRegisterOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

LoopScheduleRegisterOpGenericAdaptorBase::LoopScheduleRegisterOpGenericAdaptorBase(LoopScheduleRegisterOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

std::pair<unsigned, unsigned> LoopScheduleRegisterOpGenericAdaptorBase::getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
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
LoopScheduleRegisterOpAdaptor::LoopScheduleRegisterOpAdaptor(LoopScheduleRegisterOp op) : LoopScheduleRegisterOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult LoopScheduleRegisterOpAdaptor::verify(::mlir::Location loc) {
  return ::mlir::success();
}

std::pair<unsigned, unsigned> LoopScheduleRegisterOp::getODSOperandIndexAndLength(unsigned index) {
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

::mlir::MutableOperandRange LoopScheduleRegisterOp::getOperandsMutable() {
  auto range = getODSOperandIndexAndLength(0);
  auto mutableRange = ::mlir::MutableOperandRange(getOperation(), range.first, range.second);
  return mutableRange;
}

::llvm::LogicalResult LoopScheduleRegisterOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }
      return ::mlir::success();
}

::mlir::Attribute LoopScheduleRegisterOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code LoopScheduleRegisterOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine();
}

std::optional<mlir::Attribute> LoopScheduleRegisterOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
  return std::nullopt;
}

void LoopScheduleRegisterOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
}

void LoopScheduleRegisterOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
}

::llvm::LogicalResult LoopScheduleRegisterOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    return ::mlir::success();
}

void LoopScheduleRegisterOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands) {
  odsState.addOperands(operands);
}

LoopScheduleRegisterOp LoopScheduleRegisterOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(operands)>(operands));
  auto __res__ = ::llvm::dyn_cast<LoopScheduleRegisterOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

LoopScheduleRegisterOp LoopScheduleRegisterOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands) {
  return create(builder, builder.getLoc(), std::forward<decltype(operands)>(operands));
}

void LoopScheduleRegisterOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

LoopScheduleRegisterOp LoopScheduleRegisterOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<LoopScheduleRegisterOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

LoopScheduleRegisterOp LoopScheduleRegisterOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void LoopScheduleRegisterOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

LoopScheduleRegisterOp LoopScheduleRegisterOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<LoopScheduleRegisterOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

LoopScheduleRegisterOp LoopScheduleRegisterOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult LoopScheduleRegisterOp::verifyInvariantsImpl() {
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_LoopSchedule1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult LoopScheduleRegisterOp::verifyInvariants() {
  if(::mlir::succeeded(verifyInvariantsImpl()) && ::mlir::succeeded(verify()))
    return ::mlir::success();
  return ::mlir::failure();
}

::mlir::ParseResult LoopScheduleRegisterOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::llvm::SmallVector<::mlir::OpAsmParser::UnresolvedOperand, 4> operandsOperands;
  ::llvm::SMLoc operandsOperandsLoc;
  (void)operandsOperandsLoc;
  ::llvm::SmallVector<::mlir::Type, 1> operandsTypes;

  operandsOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperandList(operandsOperands))
    return ::mlir::failure();
  if (::mlir::succeeded(parser.parseOptionalColon())) {

  if (parser.parseTypeList(operandsTypes))
    return ::mlir::failure();
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
  if (parser.resolveOperands(operandsOperands, operandsTypes, operandsOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void LoopScheduleRegisterOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter << getOperands();
  if (!getOperands().empty()) {
    _odsPrinter << ' ' << ":";
    _odsPrinter << ' ';
    _odsPrinter << getOperands().getTypes();
  }
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
}


} // namespace circt::loopschedule
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::loopschedule::LoopScheduleRegisterOp)

namespace circt::loopschedule {


//===----------------------------------------------------------------------===//
// ::circt::loopschedule::LoopScheduleTerminatorOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

LoopScheduleTerminatorOpGenericAdaptorBase::LoopScheduleTerminatorOpGenericAdaptorBase(LoopScheduleTerminatorOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

std::pair<unsigned, unsigned> LoopScheduleTerminatorOpGenericAdaptorBase::getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
  ::llvm::ArrayRef<int32_t> sizeAttr = getProperties().operandSegmentSizes;

  unsigned start = 0;
  for (unsigned i = 0; i < index; ++i)
    start += sizeAttr[i];
  return {start, sizeAttr[index]};
}


} // namespace detail
LoopScheduleTerminatorOpAdaptor::LoopScheduleTerminatorOpAdaptor(LoopScheduleTerminatorOp op) : LoopScheduleTerminatorOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult LoopScheduleTerminatorOpAdaptor::verify(::mlir::Location loc) {
  return ::mlir::success();
}

std::pair<unsigned, unsigned> LoopScheduleTerminatorOp::getODSOperandIndexAndLength(unsigned index) {
  ::llvm::ArrayRef<int32_t> sizeAttr = getProperties().operandSegmentSizes;

  unsigned start = 0;
  for (unsigned i = 0; i < index; ++i)
    start += sizeAttr[i];
  return {start, sizeAttr[index]};
}

::mlir::MutableOperandRange LoopScheduleTerminatorOp::getIterArgsMutable() {
  auto range = getODSOperandIndexAndLength(0);
  auto mutableRange = ::mlir::MutableOperandRange(getOperation(), range.first, range.second, ::mlir::MutableOperandRange::OperandSegment(0u, {getOperandSegmentSizesAttrName(), ::mlir::DenseI32ArrayAttr::get(getContext(), getProperties().operandSegmentSizes)}));
  return mutableRange;
}

::mlir::MutableOperandRange LoopScheduleTerminatorOp::getResultsMutable() {
  auto range = getODSOperandIndexAndLength(1);
  auto mutableRange = ::mlir::MutableOperandRange(getOperation(), range.first, range.second, ::mlir::MutableOperandRange::OperandSegment(1u, {getOperandSegmentSizesAttrName(), ::mlir::DenseI32ArrayAttr::get(getContext(), getProperties().operandSegmentSizes)}));
  return mutableRange;
}

::llvm::LogicalResult LoopScheduleTerminatorOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
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

::mlir::Attribute LoopScheduleTerminatorOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
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

llvm::hash_code LoopScheduleTerminatorOp::computePropertiesHash(const Properties &prop) {
  auto hash_operandSegmentSizes_ = [] (const auto &propStorage) -> llvm::hash_code {
    using ::llvm::hash_value;
    return ::llvm::hash_combine_range(std::begin(propStorage), std::end(propStorage));;
  };
  using llvm::hash_value;
  return llvm::hash_combine(
    hash_operandSegmentSizes_(prop.operandSegmentSizes));
}

std::optional<mlir::Attribute> LoopScheduleTerminatorOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "operand_segment_sizes" || name == "operandSegmentSizes") return [&]() -> ::mlir::Attribute { return ::mlir::DenseI32ArrayAttr::get(ctx, prop.operandSegmentSizes); }();
  return std::nullopt;
}

void LoopScheduleTerminatorOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
        if (name == "operand_segment_sizes" || name == "operandSegmentSizes") {
       auto arrAttr = ::llvm::dyn_cast_or_null<::mlir::DenseI32ArrayAttr>(value);
       if (!arrAttr) return;
       if (arrAttr.size() != sizeof(prop.operandSegmentSizes) / sizeof(int32_t))
         return;
       llvm::copy(arrAttr.asArrayRef(), prop.operandSegmentSizes.begin());
       return;
    }
}

void LoopScheduleTerminatorOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
  attrs.append("operandSegmentSizes", [&]() -> ::mlir::Attribute { return ::mlir::DenseI32ArrayAttr::get(ctx, prop.operandSegmentSizes); }());
}

::llvm::LogicalResult LoopScheduleTerminatorOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    return ::mlir::success();
}

::llvm::LogicalResult LoopScheduleTerminatorOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
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

void LoopScheduleTerminatorOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
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

void LoopScheduleTerminatorOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange iter_args, ::mlir::ValueRange results) {
  odsState.addOperands(iter_args);
  odsState.addOperands(results);
  ::llvm::copy(::llvm::ArrayRef<int32_t>({static_cast<int32_t>(iter_args.size()), static_cast<int32_t>(results.size())}), odsState.getOrAddProperties<Properties>().operandSegmentSizes.begin());
}

LoopScheduleTerminatorOp LoopScheduleTerminatorOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange iter_args, ::mlir::ValueRange results) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(iter_args)>(iter_args), std::forward<decltype(results)>(results));
  auto __res__ = ::llvm::dyn_cast<LoopScheduleTerminatorOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

LoopScheduleTerminatorOp LoopScheduleTerminatorOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange iter_args, ::mlir::ValueRange results) {
  return create(builder, builder.getLoc(), std::forward<decltype(iter_args)>(iter_args), std::forward<decltype(results)>(results));
}

void LoopScheduleTerminatorOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange iter_args, ::mlir::ValueRange results) {
  odsState.addOperands(iter_args);
  odsState.addOperands(results);
  ::llvm::copy(::llvm::ArrayRef<int32_t>({static_cast<int32_t>(iter_args.size()), static_cast<int32_t>(results.size())}), odsState.getOrAddProperties<Properties>().operandSegmentSizes.begin());
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

LoopScheduleTerminatorOp LoopScheduleTerminatorOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange iter_args, ::mlir::ValueRange results) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(iter_args)>(iter_args), std::forward<decltype(results)>(results));
  auto __res__ = ::llvm::dyn_cast<LoopScheduleTerminatorOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

LoopScheduleTerminatorOp LoopScheduleTerminatorOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange iter_args, ::mlir::ValueRange results) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(iter_args)>(iter_args), std::forward<decltype(results)>(results));
}

void LoopScheduleTerminatorOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<LoopScheduleTerminatorOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

LoopScheduleTerminatorOp LoopScheduleTerminatorOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = ::llvm::dyn_cast<LoopScheduleTerminatorOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

LoopScheduleTerminatorOp LoopScheduleTerminatorOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void LoopScheduleTerminatorOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

LoopScheduleTerminatorOp LoopScheduleTerminatorOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = ::llvm::dyn_cast<LoopScheduleTerminatorOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

LoopScheduleTerminatorOp LoopScheduleTerminatorOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult LoopScheduleTerminatorOp::verifyInvariantsImpl() {
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_LoopSchedule1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSOperands(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_LoopSchedule1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult LoopScheduleTerminatorOp::verifyInvariants() {
  if(::mlir::succeeded(verifyInvariantsImpl()) && ::mlir::succeeded(verify()))
    return ::mlir::success();
  return ::mlir::failure();
}

::mlir::ParseResult LoopScheduleTerminatorOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::llvm::SmallVector<::mlir::OpAsmParser::UnresolvedOperand, 4> iter_argsOperands;
  ::llvm::SMLoc iter_argsOperandsLoc;
  (void)iter_argsOperandsLoc;
  ::llvm::SmallVector<::mlir::OpAsmParser::UnresolvedOperand, 4> resultsOperands;
  ::llvm::SMLoc resultsOperandsLoc;
  (void)resultsOperandsLoc;
  ::llvm::ArrayRef<::mlir::Type> iter_argsTypes;
  ::llvm::ArrayRef<::mlir::Type> resultsTypes;
  if (parser.parseKeyword("iter_args"))
    return ::mlir::failure();
  if (parser.parseLParen())
    return ::mlir::failure();

  iter_argsOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperandList(iter_argsOperands))
    return ::mlir::failure();
  if (parser.parseRParen())
    return ::mlir::failure();
  if (parser.parseComma())
    return ::mlir::failure();
  if (parser.parseKeyword("results"))
    return ::mlir::failure();
  if (parser.parseLParen())
    return ::mlir::failure();

  resultsOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperandList(resultsOperands))
    return ::mlir::failure();
  if (parser.parseRParen())
    return ::mlir::failure();
  if (parser.parseColon())
    return ::mlir::failure();

  ::mlir::FunctionType iter_args__results_functionType;
  if (parser.parseType(iter_args__results_functionType))
    return ::mlir::failure();
  iter_argsTypes = iter_args__results_functionType.getInputs();
  resultsTypes = iter_args__results_functionType.getResults();
  {
    auto loc = parser.getCurrentLocation();(void)loc;
    if (parser.parseOptionalAttrDict(result.attributes))
      return ::mlir::failure();
    if (failed(verifyInherentAttrs(result.name, result.attributes, [&]() {
        return parser.emitError(loc) << "'" << result.name.getStringRef() << "' op ";
      })))
      return ::mlir::failure();
  }
::llvm::copy(::llvm::ArrayRef<int32_t>({static_cast<int32_t>(iter_argsOperands.size()), static_cast<int32_t>(resultsOperands.size())}), result.getOrAddProperties<LoopScheduleTerminatorOp::Properties>().operandSegmentSizes.begin());
  if (parser.resolveOperands(iter_argsOperands, iter_argsTypes, iter_argsOperandsLoc, result.operands))
    return ::mlir::failure();
  if (parser.resolveOperands(resultsOperands, resultsTypes, resultsOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void LoopScheduleTerminatorOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ' << "iter_args";
  _odsPrinter << "(";
  _odsPrinter << getIterArgs();
  _odsPrinter << ")";
  _odsPrinter << ",";
  _odsPrinter << ' ' << "results";
  _odsPrinter << "(";
  _odsPrinter << getResults();
  _odsPrinter << ")";
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
  _odsPrinter.printFunctionalType(getIterArgs().getTypes(), getResults().getTypes());
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("operandSegmentSizes");
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
}


} // namespace circt::loopschedule
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::loopschedule::LoopScheduleTerminatorOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::loopschedule::detail::LoopScheduleTerminatorOpGenericAdaptorBase::Properties)


#endif // GET_OP_CLASSES

