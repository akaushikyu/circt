/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Op Declarations                                                            *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: LoopSchedule.td                                                      *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace circt::loopschedule {

/// LoopSchedule dialect pipeline-loop.
/// The `loopschedule.pipeline` operation represents a statically scheduled
/// pipeline stucture that executes while a condition is true. For more details,
/// see: https://llvm.discourse.group/t/rfc-representing-pipelined-loops/4171.
/// 
/// A pipeline captures the result of scheduling, and is not generally safe to
/// transform, besides lowering to hardware dialects. For more discussion about
/// relaxing this, see: https://github.com/llvm/circt/issues/2204.
/// 
/// This is the top-level operation representing a high-level pipeline. It is
/// not isolated from above, but could be if this is helpful. A pipeline
/// contains two regions: `condition` and `stages`.
/// 
/// The pipeline may accept an optional `iter_args`, similar to the SCF dialect,
/// for representing loop-carried values like induction variables or reductions.
/// When the pipeline starts execution, the registers indicated as `iter_args`
/// by `pipeline.terminator` should be initialized to the initial
/// values specified in the `iter_args` section here. The `iter_args` relate to
/// the initiation interval of the loop. The maximum distance in stages between
/// where an `iter_arg` is used and where that `iter_arg` is registered must be
/// less than the loop's initiation interval. For example, with II=1, each
/// `iter_arg` must be used and registered in the same stage.
/// 
/// The single-block `condition` region dictates the condition under which the
/// pipeline should execute. It has a `register` terminator, and the
/// pipeline initiates new iterations while the registered value is `true : i1`.
/// It may access SSA values dominating the pipeline, as well as `iter_args`,
/// which are block arguments. The body of the block may only contain
/// "combinational" operations, which are currently defined to be simple
/// arithmetic, comparisons, and selects from the `Standard` dialect.
/// 
/// The single-block `stages` region wraps `loopschedule.pipeline.stage`
/// operations. It has a `loopschedule.terminator` terminator, which can
/// both return results from the pipeline and register `iter_args`. Stages may
/// access SSA values dominating the pipeline, as well as `iter_args`, which are
/// block arguments.
class LoopSchedulePipelineOp;

} // namespace circt::loopschedule
namespace circt::loopschedule {

/// LoopSchedule dialect pipeline stage.
/// This operation has a single-block region which dictates the operations that
/// may occur concurrently.
/// 
/// It has a `start` attribute, which indicates the start cycle for this stage.
/// 
/// It may have an optional `when` predicate, which supports conditional
/// execution for each stage. This is in addition to the `condition` region that
/// controls the execution of the whole pipeline. A stage with a `when`
/// predicate should only execute when the predicate is `true : i1`, and push a
/// bubble through the pipeline otherwise.
/// 
/// It has a `register` terminator, which passes the concurrently
/// computed values forward to the next stage.
/// 
/// Any stage may access `iter_args`. If a stage accesses an `iter_arg` after
/// the stage in which it is defined, it is up to lowering passes to preserve
/// this value until the last stage that needs it.
/// 
/// Other than `iter_args`, stages may only access SSA values dominating the
/// pipeline or SSA values computed by any previous stage. This ensures the
/// stages capture the coarse-grained schedule of the pipeline and how values
/// feed forward and backward.
class LoopSchedulePipelineStageOp;

} // namespace circt::loopschedule
namespace circt::loopschedule {

/// LoopSchedule dialect loop register.
/// The `loopschedule.register` terminates a pipeline stage and
/// "registers" the values specified as operands. These values become the
/// results of the stage.
class LoopScheduleRegisterOp;

} // namespace circt::loopschedule
namespace circt::loopschedule {

/// LoopSchedule dialect terminator.
/// The `loopschedule.terminator` operation represents the terminator of
/// a `loopschedule.pipeline`.
/// 
/// The `results` section accepts a variadic list of values which become the
/// pipeline’s return values. These must be results of a stage, and their types
/// must match the pipeline's return types. The results need not be defined in
/// the final stage, and it is up to lowering passes to preserve these values
/// until the final stage is complete.
/// 
/// The `iter_args` section accepts a variadic list of values which become the
/// next iteration’s `iter_args`. These may be the results of any stage, and
/// their types must match the pipeline's `iter_args` types.
class LoopScheduleTerminatorOp;

} // namespace circt::loopschedule
#ifdef GET_OP_CLASSES
#undef GET_OP_CLASSES

namespace circt::loopschedule {


//===----------------------------------------------------------------------===//
// ::circt::loopschedule::LoopSchedulePipelineOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class LoopSchedulePipelineOpGenericAdaptorBase {
public:
  struct Properties {
    using IITy = ::mlir::IntegerAttr;
    IITy II;

    auto getII() const {
      auto &propStorage = this->II;
      return ::llvm::cast<::mlir::IntegerAttr>(propStorage);
    }
    void setII(const ::mlir::IntegerAttr &propValue) {
      this->II = propValue;
    }
    using tripCountTy = ::mlir::IntegerAttr;
    tripCountTy tripCount;

    auto getTripCount() const {
      auto &propStorage = this->tripCount;
      return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(propStorage);
    }
    void setTripCount(const ::mlir::IntegerAttr &propValue) {
      this->tripCount = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.II == this->II &&
        rhs.tripCount == this->tripCount &&
        true;
    }
    bool operator!=(const Properties &rhs) const {
      return !(*this == rhs);
    }
  };
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  LoopSchedulePipelineOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("loopschedule.pipeline", odsAttrs.getContext());
  }

  LoopSchedulePipelineOpGenericAdaptorBase(LoopSchedulePipelineOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::IntegerAttr getIIAttr() {
    auto attr = ::llvm::cast<::mlir::IntegerAttr>(getProperties().II);
    return attr;
  }

  uint64_t getII();
  ::mlir::IntegerAttr getTripCountAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(getProperties().tripCount);
    return attr;
  }

  ::std::optional<uint64_t> getTripCount();
  ::mlir::Region &getCondition() {
    return *odsRegions[0];
  }

  ::mlir::Region &getStages() {
    return *odsRegions[1];
  }

  ::mlir::RegionRange getRegions() {
    return odsRegions;
  }

};

} // namespace detail
template <typename RangeT>
class LoopSchedulePipelineOpGenericAdaptor : public detail::LoopSchedulePipelineOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::LoopSchedulePipelineOpGenericAdaptorBase;
  static constexpr int odsIndex_iterArgs = 0;
public:
  LoopSchedulePipelineOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  LoopSchedulePipelineOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : LoopSchedulePipelineOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  LoopSchedulePipelineOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : LoopSchedulePipelineOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  LoopSchedulePipelineOpGenericAdaptor(RangeT values, const LoopSchedulePipelineOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = LoopSchedulePipelineOp, typename = std::enable_if_t<std::is_same_v<LateInst, LoopSchedulePipelineOp>>>
  LoopSchedulePipelineOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getIterArgs() {
    return getODSOperands(0);
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class LoopSchedulePipelineOpAdaptor : public LoopSchedulePipelineOpGenericAdaptor<::mlir::ValueRange> {
public:
  using LoopSchedulePipelineOpGenericAdaptor::LoopSchedulePipelineOpGenericAdaptor;
  LoopSchedulePipelineOpAdaptor(LoopSchedulePipelineOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class LoopSchedulePipelineOp : public ::mlir::Op<LoopSchedulePipelineOp, ::mlir::OpTrait::NRegions<2>::Impl, ::mlir::OpTrait::VariadicResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = LoopSchedulePipelineOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = LoopSchedulePipelineOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_iterArgs = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("II"), ::llvm::StringRef("tripCount")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getIIAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getIIAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getTripCountAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getTripCountAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("loopschedule.pipeline");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::operand_range getIterArgs() {
    return getODSOperands(0);
  }

  ::mlir::MutableOperandRange getIterArgsMutable();
  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index);
  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::result_range getResults() {
    return getODSResults(0);
  }

  ::mlir::Region &getCondition() {
    return (*this)->getRegion(0);
  }

  ::mlir::Region &getStages() {
    return (*this)->getRegion(1);
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::llvm::LogicalResult readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state);
  void writeProperties(::mlir::DialectBytecodeWriter &writer);
  ::mlir::IntegerAttr getIIAttr() {
    return ::llvm::cast<::mlir::IntegerAttr>(getProperties().II);
  }

  uint64_t getII();
  ::mlir::IntegerAttr getTripCountAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(getProperties().tripCount);
  }

  ::std::optional<uint64_t> getTripCount();
  void setIIAttr(::mlir::IntegerAttr attr) {
    getProperties().II = attr;
  }

  void setII(uint64_t attrValue);
  void setTripCountAttr(::mlir::IntegerAttr attr) {
    getProperties().tripCount = attr;
  }

  void setTripCount(::std::optional<uint64_t> attrValue);
  ::mlir::Attribute removeTripCountAttr() {
      auto attr = getProperties().tripCount;
      getProperties().tripCount = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, mlir::TypeRange resultTypes, mlir::IntegerAttr II, std::optional<IntegerAttr> tripCount, mlir::ValueRange iterArgs);
  static LoopSchedulePipelineOp create(::mlir::OpBuilder &builder, ::mlir::Location location, mlir::TypeRange resultTypes, mlir::IntegerAttr II, std::optional<IntegerAttr> tripCount, mlir::ValueRange iterArgs);
  static LoopSchedulePipelineOp create(::mlir::ImplicitLocOpBuilder &builder, mlir::TypeRange resultTypes, mlir::IntegerAttr II, std::optional<IntegerAttr> tripCount, mlir::ValueRange iterArgs);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &p);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static ::llvm::LogicalResult setPropertiesFromParsedAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
private:
  ::mlir::StringAttr getAttributeNameForIndex(unsigned index) {
    return getAttributeNameForIndex((*this)->getName(), index);
  }

  static ::mlir::StringAttr getAttributeNameForIndex(::mlir::OperationName name, unsigned index) {
    assert(index < 2 && "invalid attribute index");
    assert(name.getStringRef() == getOperationName() && "invalid operation name");
    assert(name.isRegistered() && "Operation isn't registered, missing a "
          "dependent dialect loading?");
    return name.getAttributeNames()[index];
  }

public:
  Block &getCondBlock() { return getCondition().front(); }
  Block &getStagesBlock() { return getStages().front(); }
};

} // namespace circt::loopschedule
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::loopschedule::LoopSchedulePipelineOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::loopschedule::detail::LoopSchedulePipelineOpGenericAdaptorBase::Properties)

namespace circt::loopschedule {


//===----------------------------------------------------------------------===//
// ::circt::loopschedule::LoopSchedulePipelineStageOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class LoopSchedulePipelineStageOpGenericAdaptorBase {
public:
  struct Properties {
    using startTy = ::mlir::IntegerAttr;
    startTy start;

    auto getStart() const {
      auto &propStorage = this->start;
      return ::llvm::cast<::mlir::IntegerAttr>(propStorage);
    }
    void setStart(const ::mlir::IntegerAttr &propValue) {
      this->start = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.start == this->start &&
        true;
    }
    bool operator!=(const Properties &rhs) const {
      return !(*this == rhs);
    }
  };
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  LoopSchedulePipelineStageOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("loopschedule.pipeline.stage", odsAttrs.getContext());
  }

  LoopSchedulePipelineStageOpGenericAdaptorBase(LoopSchedulePipelineStageOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::IntegerAttr getStartAttr() {
    auto attr = ::llvm::cast<::mlir::IntegerAttr>(getProperties().start);
    return attr;
  }

  int64_t getStart();
  ::mlir::Region &getBody() {
    return *odsRegions[0];
  }

  ::mlir::RegionRange getRegions() {
    return odsRegions;
  }

};

} // namespace detail
template <typename RangeT>
class LoopSchedulePipelineStageOpGenericAdaptor : public detail::LoopSchedulePipelineStageOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::LoopSchedulePipelineStageOpGenericAdaptorBase;
  static constexpr int odsIndex_when = 0;
public:
  LoopSchedulePipelineStageOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  LoopSchedulePipelineStageOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : LoopSchedulePipelineStageOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  LoopSchedulePipelineStageOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : LoopSchedulePipelineStageOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  LoopSchedulePipelineStageOpGenericAdaptor(RangeT values, const LoopSchedulePipelineStageOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = LoopSchedulePipelineStageOp, typename = std::enable_if_t<std::is_same_v<LateInst, LoopSchedulePipelineStageOp>>>
  LoopSchedulePipelineStageOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getWhen() {
    auto operands = getODSOperands(0);
    return operands.empty() ? ValueT{} : (*operands.begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class LoopSchedulePipelineStageOpAdaptor : public LoopSchedulePipelineStageOpGenericAdaptor<::mlir::ValueRange> {
public:
  using LoopSchedulePipelineStageOpGenericAdaptor::LoopSchedulePipelineStageOpGenericAdaptor;
  LoopSchedulePipelineStageOpAdaptor(LoopSchedulePipelineStageOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class LoopSchedulePipelineStageOp : public ::mlir::Op<LoopSchedulePipelineStageOp, ::mlir::OpTrait::OneRegion, ::mlir::OpTrait::VariadicResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::HasParent<LoopSchedulePipelineOp>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = LoopSchedulePipelineStageOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = LoopSchedulePipelineStageOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_when = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("start")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getStartAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getStartAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("loopschedule.pipeline.stage");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::IntegerType> getWhen() {
    auto operands = getODSOperands(0);
    return operands.empty() ? ::mlir::TypedValue<::mlir::IntegerType>{} : ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*operands.begin());
  }

  ::mlir::MutableOperandRange getWhenMutable();
  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index);
  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::result_range getResults() {
    return getODSResults(0);
  }

  ::mlir::Region &getBody() {
    return (*this)->getRegion(0);
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::llvm::LogicalResult readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state);
  void writeProperties(::mlir::DialectBytecodeWriter &writer);
  ::mlir::IntegerAttr getStartAttr() {
    return ::llvm::cast<::mlir::IntegerAttr>(getProperties().start);
  }

  int64_t getStart();
  void setStartAttr(::mlir::IntegerAttr attr) {
    getProperties().start = attr;
  }

  void setStart(int64_t attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, mlir::TypeRange resultTypes, mlir::IntegerAttr start);
  static LoopSchedulePipelineStageOp create(::mlir::OpBuilder &builder, ::mlir::Location location, mlir::TypeRange resultTypes, mlir::IntegerAttr start);
  static LoopSchedulePipelineStageOp create(::mlir::ImplicitLocOpBuilder &builder, mlir::TypeRange resultTypes, mlir::IntegerAttr start);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
private:
  ::mlir::StringAttr getAttributeNameForIndex(unsigned index) {
    return getAttributeNameForIndex((*this)->getName(), index);
  }

  static ::mlir::StringAttr getAttributeNameForIndex(::mlir::OperationName name, unsigned index) {
    assert(index < 1 && "invalid attribute index");
    assert(name.getStringRef() == getOperationName() && "invalid operation name");
    assert(name.isRegistered() && "Operation isn't registered, missing a "
          "dependent dialect loading?");
    return name.getAttributeNames()[index];
  }

public:
  Block &getBodyBlock() { return getBody().front(); }
  unsigned getStageNumber();
};

} // namespace circt::loopschedule
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::loopschedule::LoopSchedulePipelineStageOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::loopschedule::detail::LoopSchedulePipelineStageOpGenericAdaptorBase::Properties)

namespace circt::loopschedule {


//===----------------------------------------------------------------------===//
// ::circt::loopschedule::LoopScheduleRegisterOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class LoopScheduleRegisterOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  LoopScheduleRegisterOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("loopschedule.register", odsAttrs.getContext());
  }

  LoopScheduleRegisterOpGenericAdaptorBase(LoopScheduleRegisterOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

};

} // namespace detail
template <typename RangeT>
class LoopScheduleRegisterOpGenericAdaptor : public detail::LoopScheduleRegisterOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::LoopScheduleRegisterOpGenericAdaptorBase;
  static constexpr int odsIndex_operands = 0;
public:
  LoopScheduleRegisterOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  LoopScheduleRegisterOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : LoopScheduleRegisterOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  LoopScheduleRegisterOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : LoopScheduleRegisterOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  LoopScheduleRegisterOpGenericAdaptor(RangeT values, const LoopScheduleRegisterOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = LoopScheduleRegisterOp, typename = std::enable_if_t<std::is_same_v<LateInst, LoopScheduleRegisterOp>>>
  LoopScheduleRegisterOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getOperands() {
    return getODSOperands(0);
  }

private:
  RangeT odsOperands;
};
class LoopScheduleRegisterOpAdaptor : public LoopScheduleRegisterOpGenericAdaptor<::mlir::ValueRange> {
public:
  using LoopScheduleRegisterOpGenericAdaptor::LoopScheduleRegisterOpGenericAdaptor;
  LoopScheduleRegisterOpAdaptor(LoopScheduleRegisterOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class LoopScheduleRegisterOp : public ::mlir::Op<LoopScheduleRegisterOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::HasParent<LoopSchedulePipelineOp, LoopSchedulePipelineStageOp>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::OpTrait::IsTerminator> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = LoopScheduleRegisterOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = LoopScheduleRegisterOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_operands = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("loopschedule.register");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::operand_range getOperands() {
    return getODSOperands(0);
  }

  ::mlir::MutableOperandRange getOperandsMutable();
  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands);
  static LoopScheduleRegisterOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands);
  static LoopScheduleRegisterOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static LoopScheduleRegisterOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static LoopScheduleRegisterOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static LoopScheduleRegisterOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static LoopScheduleRegisterOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
};

} // namespace circt::loopschedule
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::loopschedule::LoopScheduleRegisterOp)

namespace circt::loopschedule {


//===----------------------------------------------------------------------===//
// ::circt::loopschedule::LoopScheduleTerminatorOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class LoopScheduleTerminatorOpGenericAdaptorBase {
public:
  struct Properties {
    using operandSegmentSizesTy = std::array<int32_t, 2>;
    operandSegmentSizesTy operandSegmentSizes;
    ::llvm::ArrayRef<int32_t> getOperandSegmentSizes() const {
      auto &propStorage = this->operandSegmentSizes;
      return propStorage;
    }
    void setOperandSegmentSizes(::llvm::ArrayRef<int32_t> propValue) {
      auto &propStorage = this->operandSegmentSizes;
      ::llvm::copy(propValue, propStorage.begin());
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.operandSegmentSizes == this->operandSegmentSizes &&
        true;
    }
    bool operator!=(const Properties &rhs) const {
      return !(*this == rhs);
    }
  };
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  LoopScheduleTerminatorOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("loopschedule.terminator", odsAttrs.getContext());
  }

  LoopScheduleTerminatorOpGenericAdaptorBase(LoopScheduleTerminatorOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

};

} // namespace detail
template <typename RangeT>
class LoopScheduleTerminatorOpGenericAdaptor : public detail::LoopScheduleTerminatorOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::LoopScheduleTerminatorOpGenericAdaptorBase;
  static constexpr int odsIndex_iter_args = 0;
  static constexpr int odsIndex_results = 1;
public:
  LoopScheduleTerminatorOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  LoopScheduleTerminatorOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : LoopScheduleTerminatorOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  LoopScheduleTerminatorOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs) : LoopScheduleTerminatorOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  LoopScheduleTerminatorOpGenericAdaptor(RangeT values, const LoopScheduleTerminatorOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = LoopScheduleTerminatorOp, typename = std::enable_if_t<std::is_same_v<LateInst, LoopScheduleTerminatorOp>>>
  LoopScheduleTerminatorOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getIterArgs() {
    return getODSOperands(0);
  }

  RangeT getResults() {
    return getODSOperands(1);
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class LoopScheduleTerminatorOpAdaptor : public LoopScheduleTerminatorOpGenericAdaptor<::mlir::ValueRange> {
public:
  using LoopScheduleTerminatorOpGenericAdaptor::LoopScheduleTerminatorOpGenericAdaptor;
  LoopScheduleTerminatorOpAdaptor(LoopScheduleTerminatorOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class LoopScheduleTerminatorOp : public ::mlir::Op<LoopScheduleTerminatorOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::HasParent<LoopSchedulePipelineOp>::Impl, ::mlir::OpTrait::AttrSizedOperandSegments, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::OpTrait::IsTerminator> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = LoopScheduleTerminatorOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = LoopScheduleTerminatorOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_iter_args = 0;
  static constexpr int odsIndex_results = 1;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("operandSegmentSizes")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getOperandSegmentSizesAttrName() {
   return (*this)->getName().getAttributeNames().back();
  }

  static ::mlir::StringAttr getOperandSegmentSizesAttrName(::mlir::OperationName name) {
   return name.getAttributeNames().back();
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("loopschedule.terminator");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::operand_range getIterArgs() {
    return getODSOperands(0);
  }

  ::mlir::Operation::operand_range getResults() {
    return getODSOperands(1);
  }

  ::mlir::MutableOperandRange getIterArgsMutable();
  ::mlir::MutableOperandRange getResultsMutable();
  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::llvm::LogicalResult readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state);
  void writeProperties(::mlir::DialectBytecodeWriter &writer);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange iter_args, ::mlir::ValueRange results);
  static LoopScheduleTerminatorOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange iter_args, ::mlir::ValueRange results);
  static LoopScheduleTerminatorOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange iter_args, ::mlir::ValueRange results);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange iter_args, ::mlir::ValueRange results);
  static LoopScheduleTerminatorOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange iter_args, ::mlir::ValueRange results);
  static LoopScheduleTerminatorOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange iter_args, ::mlir::ValueRange results);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static LoopScheduleTerminatorOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static LoopScheduleTerminatorOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static LoopScheduleTerminatorOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static LoopScheduleTerminatorOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
private:
  ::mlir::StringAttr getAttributeNameForIndex(unsigned index) {
    return getAttributeNameForIndex((*this)->getName(), index);
  }

  static ::mlir::StringAttr getAttributeNameForIndex(::mlir::OperationName name, unsigned index) {
    return {};
  }

public:
};

} // namespace circt::loopschedule
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::loopschedule::LoopScheduleTerminatorOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::loopschedule::detail::LoopScheduleTerminatorOpGenericAdaptorBase::Properties)


#endif // GET_OP_CLASSES

