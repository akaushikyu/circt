/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Op Declarations                                                            *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: Pipeline.td                                                          *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace circt::pipeline {

/// Pipeline dialect latency operation.
/// The `pipeline.latency` operation represents an operation for wrapping
/// multi-cycle operations. The operation declares a single block
/// wherein any operation may be placed within. The operation is not
/// `IsolatedFromAbove` meaning that the operation can reference values
/// defined outside of the operation (subject to the materialization
/// phase of the parent pipeline).
class LatencyOp;

} // namespace circt::pipeline
namespace circt::pipeline {

/// Pipeline latency return operation.
/// The `pipeline.latency.return` operation represents a terminator of a
/// `pipeline.latency` operation.
class LatencyReturnOp;

} // namespace circt::pipeline
namespace circt::pipeline {

/// Pipeline dialect return.
/// The "return" operation represents a terminator of a `pipeline.pipeline`.
class ReturnOp;

} // namespace circt::pipeline
namespace circt::pipeline {

/// Scheduled pipeline operation
/// The `pipeline.scheduled` operation represents a scheduled pipeline.
/// The pipeline contains a single block representing a graph region.
/// 
/// A `pipeline.scheduled` operation can exist in multiple phases, mainly
/// pertaining to when registers have been materialized (made explicit).
/// For an in-depth explanation, please refer to the Pipeline dialect rationale.
/// 
/// A `pipeline.scheduled` supports a `stall` input. This signal is intended to
/// connect to all stages within the pipeline, and is used to stall the entirety
/// of the pipeline. It is lowering defined how stages choose to use this signal,
/// although in the common case, a `stall` signal would typically connect to
/// the clock-enable input of the stage-separating registers.
/// 
/// The `go` input is used to start the pipeline. This value is fed through
/// the stages as the current stage valid/next stage enable signal.
/// Note: the op is currently only designed for pipelines with II=1. For
/// pipelines with II>1, a user must themselves maintain state about when
/// the pipeline is ready to accept new inputs. We plan to add support for
/// head-of-pipeline backpressure in the future.
/// 
/// Any value defined outside the pipeline is considered an external input. An
/// external input will _not_ be registered.
/// 
/// The pipeline may optionally be provided with an array of bits `stallability`
/// which is used to determine which stages are stallable.
/// - If not provided and the pipeline has a stall signal, all stages are stallable.
/// - If provided, and the pipeline has a stall signal, the number of bits must
///   match the number of stages in the pipeline. Each bit represents a stage,
///   in the order of which the stages appear wrt. the `pipeline.stage` operations.
///   A bit set to 1 indicates that the stage is stallable, and 0 indicates that
///   the stage is not stallable.
/// 
/// The exit (non-registered) stage of a pipeline cannot be non-stallable, and
/// will always follow the stallability of the parent pipeline.
/// 
/// For more information about non-stallable stages, and how these are lowered,
/// please refer to the Pipeline dialect rationale.
class ScheduledPipelineOp;

} // namespace circt::pipeline
namespace circt::pipeline {

/// Pipeline source operation
/// The `pipeline.src` operation represents a source operation in a scheduled,
/// non-register materialized pipeline.
/// It is used as a canonicalization barrier to prevent cross-block canonicalization
/// of operations that are not allowed to be moved or mutated across pipeline
/// stages (i.e. MLIR blocks).
/// 
/// To facilitate this, the operation is _not_ marked as `Pure`.
class SourceOp;

} // namespace circt::pipeline
namespace circt::pipeline {

/// Pipeline stage terminator.
/// The `pipeline.stage` operation represents a stage terminator. It is used
/// to communicate:
/// 1. which stage (block) to transition to next
/// 2. which registers to build at this stage boundary
/// 3. which values to pass through to the next stage without registering
/// 4. An optional hierarchy of boolean values to be used for clock gates for
///    each register.
///   - The implicit '!stalled' gate will always be the first signal in the
///     hierarchy. Further signals are added to the hierarchy from left to
///     right.
/// 
/// 
/// Example:
/// ```mlir
/// pipeline.stage ^bb1 regs(%a : i32 gated by [%foo, %bar], %b : i1) pass(%c : i32)
/// ```
class StageOp;

} // namespace circt::pipeline
namespace circt::pipeline {

/// unscheduled pipeline operation
/// The "pipeline.unscheduled" operation represents a pipeline that has not yet
/// been scheduled. It contains a single block representing a graph region of
/// operations to-be-scheduled into a pipeline.
/// Mainly serves as a container and entrypoint for scheduling.
/// 
/// The interface of a `pipeline.unscheduled` is similar to that of a
/// `pipeline.scheduled`. Please refer to this op for further documentation
/// about the interface signals.
class UnscheduledPipelineOp;

} // namespace circt::pipeline
#ifdef GET_OP_CLASSES
#undef GET_OP_CLASSES

namespace circt::pipeline {


//===----------------------------------------------------------------------===//
// ::circt::pipeline::LatencyOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class LatencyOpGenericAdaptorBase {
public:
  struct Properties {
    using latencyTy = ::mlir::IntegerAttr;
    latencyTy latency;

    auto getLatency() const {
      auto &propStorage = this->latency;
      return ::llvm::cast<::mlir::IntegerAttr>(propStorage);
    }
    void setLatency(const ::mlir::IntegerAttr &propValue) {
      this->latency = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.latency == this->latency &&
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
  LatencyOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("pipeline.latency", odsAttrs.getContext());
  }

  LatencyOpGenericAdaptorBase(LatencyOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::IntegerAttr getLatencyAttr() {
    auto attr = ::llvm::cast<::mlir::IntegerAttr>(getProperties().latency);
    return attr;
  }

  uint32_t getLatency();
  ::mlir::Region &getBody() {
    return *odsRegions[0];
  }

  ::mlir::RegionRange getRegions() {
    return odsRegions;
  }

};

} // namespace detail
template <typename RangeT>
class LatencyOpGenericAdaptor : public detail::LatencyOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::LatencyOpGenericAdaptorBase;
public:
  LatencyOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  LatencyOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : LatencyOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  LatencyOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : LatencyOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  LatencyOpGenericAdaptor(RangeT values, const LatencyOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = LatencyOp, typename = std::enable_if_t<std::is_same_v<LateInst, LatencyOp>>>
  LatencyOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class LatencyOpAdaptor : public LatencyOpGenericAdaptor<::mlir::ValueRange> {
public:
  using LatencyOpGenericAdaptor::LatencyOpGenericAdaptor;
  LatencyOpAdaptor(LatencyOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class LatencyOp : public ::mlir::Op<LatencyOp, ::mlir::OpTrait::OneRegion, ::mlir::OpTrait::VariadicResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::SingleBlock, ::mlir::OpTrait::SingleBlockImplicitTerminator<LatencyReturnOp>::Impl, ::mlir::OpTrait::HasParent<UnscheduledPipelineOp, ScheduledPipelineOp>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::RegionKindInterface::Trait, ::mlir::OpTrait::HasOnlyGraphRegion> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = LatencyOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = LatencyOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("latency")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getLatencyAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getLatencyAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("pipeline.latency");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

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
  ::mlir::IntegerAttr getLatencyAttr() {
    return ::llvm::cast<::mlir::IntegerAttr>(getProperties().latency);
  }

  uint32_t getLatency();
  void setLatencyAttr(::mlir::IntegerAttr attr) {
    getProperties().latency = attr;
  }

  void setLatency(uint32_t attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange results, ::mlir::IntegerAttr latency);
  static LatencyOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange results, ::mlir::IntegerAttr latency);
  static LatencyOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange results, ::mlir::IntegerAttr latency);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange results, uint32_t latency);
  static LatencyOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange results, uint32_t latency);
  static LatencyOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange results, uint32_t latency);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static LatencyOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static LatencyOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static LatencyOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static LatencyOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
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
  // Returns the body block of the latency operation.
  Block* getBodyBlock() {
    return &getBody().front();
  }
};

} // namespace circt::pipeline
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::pipeline::LatencyOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::pipeline::detail::LatencyOpGenericAdaptorBase::Properties)

namespace circt::pipeline {


//===----------------------------------------------------------------------===//
// ::circt::pipeline::LatencyReturnOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class LatencyReturnOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  LatencyReturnOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("pipeline.latency.return", odsAttrs.getContext());
  }

  LatencyReturnOpGenericAdaptorBase(LatencyReturnOp op);

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
class LatencyReturnOpGenericAdaptor : public detail::LatencyReturnOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::LatencyReturnOpGenericAdaptorBase;
  static constexpr int odsIndex_inputs = 0;
public:
  LatencyReturnOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  LatencyReturnOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : LatencyReturnOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  LatencyReturnOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : LatencyReturnOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  LatencyReturnOpGenericAdaptor(RangeT values, const LatencyReturnOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = LatencyReturnOp, typename = std::enable_if_t<std::is_same_v<LateInst, LatencyReturnOp>>>
  LatencyReturnOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getInputs() {
    return getODSOperands(0);
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class LatencyReturnOpAdaptor : public LatencyReturnOpGenericAdaptor<::mlir::ValueRange> {
public:
  using LatencyReturnOpGenericAdaptor::LatencyReturnOpGenericAdaptor;
  LatencyReturnOpAdaptor(LatencyReturnOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class LatencyReturnOp : public ::mlir::Op<LatencyReturnOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::HasParent<LatencyOp>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::OpTrait::IsTerminator> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = LatencyReturnOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = LatencyReturnOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_inputs = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("pipeline.latency.return");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::operand_range getInputs() {
    return getODSOperands(0);
  }

  ::mlir::MutableOperandRange getInputsMutable();
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState);
  static LatencyReturnOp create(::mlir::OpBuilder &builder, ::mlir::Location location);
  static LatencyReturnOp create(::mlir::ImplicitLocOpBuilder &builder);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange inputs);
  static LatencyReturnOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange inputs);
  static LatencyReturnOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange inputs);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static LatencyReturnOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static LatencyReturnOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static LatencyReturnOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static LatencyReturnOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
};

} // namespace circt::pipeline
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::pipeline::LatencyReturnOp)

namespace circt::pipeline {


//===----------------------------------------------------------------------===//
// ::circt::pipeline::ReturnOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ReturnOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  ReturnOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("pipeline.return", odsAttrs.getContext());
  }

  ReturnOpGenericAdaptorBase(ReturnOp op);

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
class ReturnOpGenericAdaptor : public detail::ReturnOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ReturnOpGenericAdaptorBase;
  static constexpr int odsIndex_inputs = 0;
public:
  ReturnOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ReturnOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : ReturnOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ReturnOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ReturnOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ReturnOpGenericAdaptor(RangeT values, const ReturnOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ReturnOp, typename = std::enable_if_t<std::is_same_v<LateInst, ReturnOp>>>
  ReturnOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getInputs() {
    return getODSOperands(0);
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class ReturnOpAdaptor : public ReturnOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ReturnOpGenericAdaptor::ReturnOpGenericAdaptor;
  ReturnOpAdaptor(ReturnOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ReturnOp : public ::mlir::Op<ReturnOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::HasParent<UnscheduledPipelineOp, ScheduledPipelineOp>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::OpTrait::IsTerminator> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ReturnOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ReturnOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_inputs = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("pipeline.return");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::operand_range getInputs() {
    return getODSOperands(0);
  }

  ::mlir::MutableOperandRange getInputsMutable();
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState);
  static ReturnOp create(::mlir::OpBuilder &builder, ::mlir::Location location);
  static ReturnOp create(::mlir::ImplicitLocOpBuilder &builder);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange inputs);
  static ReturnOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange inputs);
  static ReturnOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange inputs);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ReturnOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ReturnOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ReturnOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ReturnOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
};

} // namespace circt::pipeline
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::pipeline::ReturnOp)

namespace circt::pipeline {


//===----------------------------------------------------------------------===//
// ::circt::pipeline::ScheduledPipelineOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ScheduledPipelineOpGenericAdaptorBase {
public:
  struct Properties {
    using inputNamesTy = ::mlir::ArrayAttr;
    inputNamesTy inputNames;

    auto getInputNames() const {
      auto &propStorage = this->inputNames;
      return ::llvm::cast<::mlir::ArrayAttr>(propStorage);
    }
    void setInputNames(const ::mlir::ArrayAttr &propValue) {
      this->inputNames = propValue;
    }
    using nameTy = ::mlir::StringAttr;
    nameTy name;

    auto getName() const {
      auto &propStorage = this->name;
      return ::llvm::dyn_cast_or_null<::mlir::StringAttr>(propStorage);
    }
    void setName(const ::mlir::StringAttr &propValue) {
      this->name = propValue;
    }
    using outputNamesTy = ::mlir::ArrayAttr;
    outputNamesTy outputNames;

    auto getOutputNames() const {
      auto &propStorage = this->outputNames;
      return ::llvm::cast<::mlir::ArrayAttr>(propStorage);
    }
    void setOutputNames(const ::mlir::ArrayAttr &propValue) {
      this->outputNames = propValue;
    }
    using stallabilityTy = ::mlir::ArrayAttr;
    stallabilityTy stallability;

    auto getStallability() const {
      auto &propStorage = this->stallability;
      return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(propStorage);
    }
    void setStallability(const ::mlir::ArrayAttr &propValue) {
      this->stallability = propValue;
    }
    using operandSegmentSizesTy = std::array<int32_t, 5>;
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
        rhs.inputNames == this->inputNames &&
        rhs.name == this->name &&
        rhs.outputNames == this->outputNames &&
        rhs.stallability == this->stallability &&
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
  ScheduledPipelineOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("pipeline.scheduled", odsAttrs.getContext());
  }

  ScheduledPipelineOpGenericAdaptorBase(ScheduledPipelineOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::StringAttr getNameAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::StringAttr>(getProperties().name);
    return attr;
  }

  ::std::optional< ::llvm::StringRef > getName();
  ::mlir::ArrayAttr getInputNamesAttr() {
    auto attr = ::llvm::cast<::mlir::ArrayAttr>(getProperties().inputNames);
    return attr;
  }

  ::mlir::ArrayAttr getInputNames();
  ::mlir::ArrayAttr getOutputNamesAttr() {
    auto attr = ::llvm::cast<::mlir::ArrayAttr>(getProperties().outputNames);
    return attr;
  }

  ::mlir::ArrayAttr getOutputNames();
  ::mlir::ArrayAttr getStallabilityAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().stallability);
    return attr;
  }

  ::std::optional< ::mlir::ArrayAttr > getStallability();
  ::mlir::Region &getBody() {
    return *odsRegions[0];
  }

  ::mlir::RegionRange getRegions() {
    return odsRegions;
  }

};

} // namespace detail
template <typename RangeT>
class ScheduledPipelineOpGenericAdaptor : public detail::ScheduledPipelineOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ScheduledPipelineOpGenericAdaptorBase;
  static constexpr int odsIndex_inputs = 0;
  static constexpr int odsIndex_stall = 1;
  static constexpr int odsIndex_clock = 2;
  static constexpr int odsIndex_reset = 3;
  static constexpr int odsIndex_go = 4;
public:
  ScheduledPipelineOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ScheduledPipelineOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : ScheduledPipelineOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ScheduledPipelineOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs) : ScheduledPipelineOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ScheduledPipelineOpGenericAdaptor(RangeT values, const ScheduledPipelineOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ScheduledPipelineOp, typename = std::enable_if_t<std::is_same_v<LateInst, ScheduledPipelineOp>>>
  ScheduledPipelineOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getInputs() {
    return getODSOperands(0);
  }

  ValueT getStall() {
    auto operands = getODSOperands(1);
    return operands.empty() ? ValueT{} : (*operands.begin());
  }

  ValueT getClock() {
    return (*getODSOperands(2).begin());
  }

  ValueT getReset() {
    auto operands = getODSOperands(3);
    return operands.empty() ? ValueT{} : (*operands.begin());
  }

  ValueT getGo() {
    return (*getODSOperands(4).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class ScheduledPipelineOpAdaptor : public ScheduledPipelineOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ScheduledPipelineOpGenericAdaptor::ScheduledPipelineOpGenericAdaptor;
  ScheduledPipelineOpAdaptor(ScheduledPipelineOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ScheduledPipelineOp : public ::mlir::Op<ScheduledPipelineOp, ::mlir::OpTrait::OneRegion, ::mlir::OpTrait::AtLeastNResults<1>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<2>::Impl, ::mlir::OpTrait::AttrSizedOperandSegments, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::RegionKindInterface::Trait, ::mlir::OpAsmOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ScheduledPipelineOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ScheduledPipelineOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_inputs = 0;
  static constexpr int odsIndex_stall = 1;
  static constexpr int odsIndex_clock = 2;
  static constexpr int odsIndex_reset = 3;
  static constexpr int odsIndex_go = 4;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::OpAsmOpInterface::Trait<ScheduledPipelineOp>::getAsmBlockNames;
  using ::mlir::OpAsmOpInterface::Trait<ScheduledPipelineOp>::getDefaultDialect;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("inputNames"), ::llvm::StringRef("name"), ::llvm::StringRef("outputNames"), ::llvm::StringRef("stallability"), ::llvm::StringRef("operandSegmentSizes")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getInputNamesAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getInputNamesAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getNameAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getNameAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getOutputNamesAttrName() {
    return getAttributeNameForIndex(2);
  }

  static ::mlir::StringAttr getOutputNamesAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 2);
  }

  ::mlir::StringAttr getStallabilityAttrName() {
    return getAttributeNameForIndex(3);
  }

  static ::mlir::StringAttr getStallabilityAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 3);
  }

  ::mlir::StringAttr getOperandSegmentSizesAttrName() {
   return (*this)->getName().getAttributeNames().back();
  }

  static ::mlir::StringAttr getOperandSegmentSizesAttrName(::mlir::OperationName name) {
   return name.getAttributeNames().back();
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("pipeline.scheduled");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::operand_range getInputs() {
    return getODSOperands(0);
  }

  ::mlir::TypedValue<::mlir::IntegerType> getStall() {
    auto operands = getODSOperands(1);
    return operands.empty() ? ::mlir::TypedValue<::mlir::IntegerType>{} : ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*operands.begin());
  }

  ::mlir::TypedValue<::circt::seq::ClockType> getClock() {
    return ::llvm::cast<::mlir::TypedValue<::circt::seq::ClockType>>(*getODSOperands(2).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getReset() {
    auto operands = getODSOperands(3);
    return operands.empty() ? ::mlir::TypedValue<::mlir::IntegerType>{} : ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*operands.begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getGo() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSOperands(4).begin());
  }

  ::mlir::MutableOperandRange getInputsMutable();
  ::mlir::MutableOperandRange getStallMutable();
  ::mlir::OpOperand &getClockMutable() {
    auto range = getODSOperandIndexAndLength(2);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::MutableOperandRange getResetMutable();
  ::mlir::OpOperand &getGoMutable() {
    auto range = getODSOperandIndexAndLength(4);
    return getOperation()->getOpOperand(range.first);
  }

  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index);
  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::result_range getDataOutputs() {
    return getODSResults(0);
  }

  ::mlir::TypedValue<::mlir::IntegerType> getDone() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSResults(1).begin());
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
  ::mlir::StringAttr getNameAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::StringAttr>(getProperties().name);
  }

  ::std::optional< ::llvm::StringRef > getName();
  ::mlir::ArrayAttr getInputNamesAttr() {
    return ::llvm::cast<::mlir::ArrayAttr>(getProperties().inputNames);
  }

  ::mlir::ArrayAttr getInputNames();
  ::mlir::ArrayAttr getOutputNamesAttr() {
    return ::llvm::cast<::mlir::ArrayAttr>(getProperties().outputNames);
  }

  ::mlir::ArrayAttr getOutputNames();
  ::mlir::ArrayAttr getStallabilityAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().stallability);
  }

  ::std::optional< ::mlir::ArrayAttr > getStallability();
  void setNameAttr(::mlir::StringAttr attr) {
    getProperties().name = attr;
  }

  void setName(::std::optional<::llvm::StringRef> attrValue);
  void setInputNamesAttr(::mlir::ArrayAttr attr) {
    getProperties().inputNames = attr;
  }

  void setOutputNamesAttr(::mlir::ArrayAttr attr) {
    getProperties().outputNames = attr;
  }

  void setStallabilityAttr(::mlir::ArrayAttr attr) {
    getProperties().stallability = attr;
  }

  ::mlir::Attribute removeNameAttr() {
      auto attr = getProperties().name;
      getProperties().name = {};
      return attr;
  }

  ::mlir::Attribute removeStallabilityAttr() {
      auto attr = getProperties().stallability;
      getProperties().stallability = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, TypeRange dataOutputs, ValueRange inputs, ArrayAttr inputNames, ArrayAttr outputNames, Value clock, Value go, Value reset = {}, Value stall = {}, StringAttr name = {}, ArrayAttr stallability = {});
  static ScheduledPipelineOp create(::mlir::OpBuilder &builder, ::mlir::Location location, TypeRange dataOutputs, ValueRange inputs, ArrayAttr inputNames, ArrayAttr outputNames, Value clock, Value go, Value reset = {}, Value stall = {}, StringAttr name = {}, ArrayAttr stallability = {});
  static ScheduledPipelineOp create(::mlir::ImplicitLocOpBuilder &builder, TypeRange dataOutputs, ValueRange inputs, ArrayAttr inputNames, ArrayAttr outputNames, Value clock, Value go, Value reset = {}, Value stall = {}, StringAttr name = {}, ArrayAttr stallability = {});
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &p);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
  void getAsmBlockArgumentNames(::mlir::Region&region, ::mlir::OpAsmSetValueNameFn setNameFn);
  static ::llvm::LogicalResult setPropertiesFromParsedAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
private:
  ::mlir::StringAttr getAttributeNameForIndex(unsigned index) {
    return getAttributeNameForIndex((*this)->getName(), index);
  }

  static ::mlir::StringAttr getAttributeNameForIndex(::mlir::OperationName name, unsigned index) {
    assert(index < 4 && "invalid attribute index");
    assert(name.getStringRef() == getOperationName() && "invalid operation name");
    assert(name.isRegistered() && "Operation isn't registered, missing a "
          "dependent dialect loading?");
    return name.getAttributeNames()[index];
  }

public:
  static mlir::RegionKind getRegionKind(unsigned index) {
    return mlir::RegionKind::SSACFG;
  }

  // Returns all of the stages in this pipeline.
  llvm::iplist<mlir::Block>& getStages() {
    return getRegion().getBlocks();
  }

  size_t getNumStages() {
    return getStages().size();
  }

  // Returns all of the stages in this pipeline. The stages are ordered
  // with respect to their position in the pipeline as determined by the
  // control flow of `pipeline.stage` operations.
  // Stages are ordered from first (entry) to last (exit).
  llvm::SmallVector<Block*> getOrderedStages();

  // Returns a map of stages to their index in the pipeline - this is
  // with respect to 'getOrderedStages'.
  llvm::DenseMap<Block*, unsigned> getStageMap();

  // Returns the last stage in the pipeline.
  Block* getLastStage();

  // Adds a new stage to this pipeline. It is the users responsibility to
  // modify other stages to point to this new stage.
  Block* addStage();

  // Returns true if the pipeline has entered the register materialized phase.
  // This enables certain invariants such as "all values used within a stage
  // must be defined within a stage".
  bool isMaterialized();

  // Returns the data arguments for a stage. The stage enable signal is _not_ part
  // of the returned values.
  mlir::Block::BlockArgListType getStageDataArgs(Block* stage) {
    if(stage == getEntryStage())
      return getInnerInputs();

    // Data arguments for all non-entry stages are all block arguments
    // except for the last block arguments (which is the stage enable signal).
    return stage->getArguments().drop_back();
  }

  // Returns the stage kind of the given stage index.
  StageKind getStageKind(size_t stageIdx);

  // Returns the entry stage of this pipeline.
  Block* getEntryStage() {
    Region* region = &getOperation()->getRegion(0);
    return &region->front();
  }

  // Returns true if this pipeline has a stall signal.
  bool hasStall() {
    return static_cast<bool>(getStall());
  }

  // Returns true if this pipeline has a reset signal.
  bool hasReset() {
    return static_cast<bool>(getReset());
  }

  mlir::Block::BlockArgListType getInnerInputs() {
    return getEntryStage()->getArguments().take_front(getInputs().size());
  }

  // Returns a list of external inputs to the pipeline. These are defined
  // as any value which is defined outside the inner pipeline region.
  // This will walk the entire pipeline, so it is recommended to cache the
  // result if it is used multiple times.
  llvm::SmallVector<Value> getExtInputs() {
    return detail::getValuesDefinedOutsideRegion(getRegion());
  }

  // Gets the n'th stage of this pipeline
  Block* getStage(unsigned n) {
    auto& blocks = getRegion().getBlocks();
    assert(n < blocks.size() && "Stage index out of bounds");
    return &*std::next(blocks.begin(), n);
  }

  // Returns the enable signal of the given pipeline stage. This is always
  // the last block argument of a stage for anything but the entry stage.
  Value getStageEnableSignal(size_t stageIdx) {
    return getStageEnableSignal(getStage(stageIdx));
  }

  // Returns the enable signal for the given stage. The enable signal is always
  // the last signal in the stage argument list.
  Value getStageEnableSignal(Block* stage) {
    return stage->getArguments().back();
  }
};

} // namespace circt::pipeline
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::pipeline::ScheduledPipelineOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::pipeline::detail::ScheduledPipelineOpGenericAdaptorBase::Properties)

namespace circt::pipeline {


//===----------------------------------------------------------------------===//
// ::circt::pipeline::SourceOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class SourceOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  SourceOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("pipeline.src", odsAttrs.getContext());
  }

  SourceOpGenericAdaptorBase(SourceOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

};

} // namespace detail
template <typename RangeT>
class SourceOpGenericAdaptor : public detail::SourceOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::SourceOpGenericAdaptorBase;
  static constexpr int odsIndex_input = 0;
public:
  SourceOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  SourceOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : SourceOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  SourceOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : SourceOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  SourceOpGenericAdaptor(RangeT values, const SourceOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = SourceOp, typename = std::enable_if_t<std::is_same_v<LateInst, SourceOp>>>
  SourceOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getInput() {
    return (*getODSOperands(0).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class SourceOpAdaptor : public SourceOpGenericAdaptor<::mlir::ValueRange> {
public:
  using SourceOpGenericAdaptor::SourceOpGenericAdaptor;
  SourceOpAdaptor(SourceOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class SourceOp : public ::mlir::Op<SourceOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::Type>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::HasParent<ScheduledPipelineOp>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = SourceOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = SourceOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_input = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("pipeline.src");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::Type> getInput() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(0).begin());
  }

  ::mlir::OpOperand &getInputMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::Type> getOutput() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSResults(0).begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type output, ::mlir::Value input);
  static SourceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type output, ::mlir::Value input);
  static SourceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type output, ::mlir::Value input);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value input);
  static SourceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value input);
  static SourceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value input);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value input);
  static SourceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value input);
  static SourceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value input);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SourceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SourceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SourceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SourceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SourceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SourceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SourceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SourceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::PropertyRef properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
};

} // namespace circt::pipeline
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::pipeline::SourceOp)

namespace circt::pipeline {


//===----------------------------------------------------------------------===//
// ::circt::pipeline::StageOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class StageOpGenericAdaptorBase {
public:
  struct Properties {
    using clockGatesPerRegisterTy = ::mlir::ArrayAttr;
    clockGatesPerRegisterTy clockGatesPerRegister;

    auto getClockGatesPerRegister() const {
      auto &propStorage = this->clockGatesPerRegister;
      return ::llvm::cast<::mlir::ArrayAttr>(propStorage);
    }
    void setClockGatesPerRegister(const ::mlir::ArrayAttr &propValue) {
      this->clockGatesPerRegister = propValue;
    }
    using passthroughNamesTy = ::mlir::ArrayAttr;
    passthroughNamesTy passthroughNames;

    auto getPassthroughNames() const {
      auto &propStorage = this->passthroughNames;
      return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(propStorage);
    }
    void setPassthroughNames(const ::mlir::ArrayAttr &propValue) {
      this->passthroughNames = propValue;
    }
    using registerNamesTy = ::mlir::ArrayAttr;
    registerNamesTy registerNames;

    auto getRegisterNames() const {
      auto &propStorage = this->registerNames;
      return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(propStorage);
    }
    void setRegisterNames(const ::mlir::ArrayAttr &propValue) {
      this->registerNames = propValue;
    }
    using operandSegmentSizesTy = std::array<int32_t, 3>;
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
        rhs.clockGatesPerRegister == this->clockGatesPerRegister &&
        rhs.passthroughNames == this->passthroughNames &&
        rhs.registerNames == this->registerNames &&
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
  StageOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("pipeline.stage", odsAttrs.getContext());
  }

  StageOpGenericAdaptorBase(StageOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::ArrayAttr getClockGatesPerRegisterAttr() {
    auto attr = ::llvm::cast<::mlir::ArrayAttr>(getProperties().clockGatesPerRegister);
    return attr;
  }

  ::mlir::ArrayAttr getClockGatesPerRegister();
  ::mlir::ArrayAttr getRegisterNamesAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().registerNames);
    return attr;
  }

  ::std::optional< ::mlir::ArrayAttr > getRegisterNames();
  ::mlir::ArrayAttr getPassthroughNamesAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().passthroughNames);
    return attr;
  }

  ::std::optional< ::mlir::ArrayAttr > getPassthroughNames();
};

} // namespace detail
template <typename RangeT>
class StageOpGenericAdaptor : public detail::StageOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::StageOpGenericAdaptorBase;
  static constexpr int odsIndex_registers = 0;
  static constexpr int odsIndex_passthroughs = 1;
  static constexpr int odsIndex_clockGates = 2;
public:
  StageOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  StageOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : StageOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  StageOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs) : StageOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  StageOpGenericAdaptor(RangeT values, const StageOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = StageOp, typename = std::enable_if_t<std::is_same_v<LateInst, StageOp>>>
  StageOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getRegisters() {
    return getODSOperands(0);
  }

  RangeT getPassthroughs() {
    return getODSOperands(1);
  }

  RangeT getClockGates() {
    return getODSOperands(2);
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class StageOpAdaptor : public StageOpGenericAdaptor<::mlir::ValueRange> {
public:
  using StageOpGenericAdaptor::StageOpGenericAdaptor;
  StageOpAdaptor(StageOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class StageOp : public ::mlir::Op<StageOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::OneSuccessor, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::AttrSizedOperandSegments, ::mlir::OpTrait::HasParent<ScheduledPipelineOp>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::OpTrait::IsTerminator> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = StageOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = StageOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_registers = 0;
  static constexpr int odsIndex_passthroughs = 1;
  static constexpr int odsIndex_clockGates = 2;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("clockGatesPerRegister"), ::llvm::StringRef("passthroughNames"), ::llvm::StringRef("registerNames"), ::llvm::StringRef("operandSegmentSizes")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getClockGatesPerRegisterAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getClockGatesPerRegisterAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getPassthroughNamesAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getPassthroughNamesAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getRegisterNamesAttrName() {
    return getAttributeNameForIndex(2);
  }

  static ::mlir::StringAttr getRegisterNamesAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 2);
  }

  ::mlir::StringAttr getOperandSegmentSizesAttrName() {
   return (*this)->getName().getAttributeNames().back();
  }

  static ::mlir::StringAttr getOperandSegmentSizesAttrName(::mlir::OperationName name) {
   return name.getAttributeNames().back();
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("pipeline.stage");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::operand_range getRegisters() {
    return getODSOperands(0);
  }

  ::mlir::Operation::operand_range getPassthroughs() {
    return getODSOperands(1);
  }

  ::mlir::Operation::operand_range getClockGates() {
    return getODSOperands(2);
  }

  ::mlir::MutableOperandRange getRegistersMutable();
  ::mlir::MutableOperandRange getPassthroughsMutable();
  ::mlir::MutableOperandRange getClockGatesMutable();
  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Block *getNextStage() {
    return (*this)->getSuccessor(0);
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
  ::mlir::ArrayAttr getClockGatesPerRegisterAttr() {
    return ::llvm::cast<::mlir::ArrayAttr>(getProperties().clockGatesPerRegister);
  }

  ::mlir::ArrayAttr getClockGatesPerRegister();
  ::mlir::ArrayAttr getRegisterNamesAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().registerNames);
  }

  ::std::optional< ::mlir::ArrayAttr > getRegisterNames();
  ::mlir::ArrayAttr getPassthroughNamesAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().passthroughNames);
  }

  ::std::optional< ::mlir::ArrayAttr > getPassthroughNames();
  void setClockGatesPerRegisterAttr(::mlir::ArrayAttr attr) {
    getProperties().clockGatesPerRegister = attr;
  }

  void setRegisterNamesAttr(::mlir::ArrayAttr attr) {
    getProperties().registerNames = attr;
  }

  void setPassthroughNamesAttr(::mlir::ArrayAttr attr) {
    getProperties().passthroughNames = attr;
  }

  ::mlir::Attribute removeRegisterNamesAttr() {
      auto attr = getProperties().registerNames;
      getProperties().registerNames = {};
      return attr;
  }

  ::mlir::Attribute removePassthroughNamesAttr() {
      auto attr = getProperties().passthroughNames;
      getProperties().passthroughNames = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Block*dest, ValueRange registers, ValueRange passthroughs);
  static StageOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Block*dest, ValueRange registers, ValueRange passthroughs);
  static StageOp create(::mlir::ImplicitLocOpBuilder &builder, Block*dest, ValueRange registers, ValueRange passthroughs);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Block*dest, ValueRange registers, ValueRange passthroughs, llvm::ArrayRef<llvm::SmallVector<Value>> clockGates, mlir::ArrayAttr registerNames = {}, mlir::ArrayAttr passthroughNames = {});
  static StageOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Block*dest, ValueRange registers, ValueRange passthroughs, llvm::ArrayRef<llvm::SmallVector<Value>> clockGates, mlir::ArrayAttr registerNames = {}, mlir::ArrayAttr passthroughNames = {});
  static StageOp create(::mlir::ImplicitLocOpBuilder &builder, Block*dest, ValueRange registers, ValueRange passthroughs, llvm::ArrayRef<llvm::SmallVector<Value>> clockGates, mlir::ArrayAttr registerNames = {}, mlir::ArrayAttr passthroughNames = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
private:
  ::mlir::StringAttr getAttributeNameForIndex(unsigned index) {
    return getAttributeNameForIndex((*this)->getName(), index);
  }

  static ::mlir::StringAttr getAttributeNameForIndex(::mlir::OperationName name, unsigned index) {
    assert(index < 3 && "invalid attribute index");
    assert(name.getStringRef() == getOperationName() && "invalid operation name");
    assert(name.isRegistered() && "Operation isn't registered, missing a "
          "dependent dialect loading?");
    return name.getAttributeNames()[index];
  }

public:
  // Set the destination stage.
  void setNextStage(Block *block) {
    setSuccessor(block);
  }

  // Returns the list of clock gates for the given register.
  ValueRange getClockGatesForReg(unsigned regIdx);

  // Returns the register name for a given register index.
  StringAttr getRegisterName(unsigned regIdx) {
    if(auto names = getOperation()->getAttrOfType<ArrayAttr>("registerNames")) {
      auto name = llvm::cast<StringAttr>(names[regIdx]);
      if(!name.strref().empty())
        return name;
    }

    return {};
  }

  // Returns the passthrough name for a given passthrough index.
  StringAttr getPassthroughName(unsigned passthroughIdx) {
    if(auto names = getOperation()->getAttrOfType<ArrayAttr>("passthroughNames")) {
      auto name = llvm::cast<StringAttr>(names[passthroughIdx]);
      if(!name.strref().empty())
        return name;
    }

    return {};
  }


};

} // namespace circt::pipeline
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::pipeline::StageOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::pipeline::detail::StageOpGenericAdaptorBase::Properties)

namespace circt::pipeline {


//===----------------------------------------------------------------------===//
// ::circt::pipeline::UnscheduledPipelineOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class UnscheduledPipelineOpGenericAdaptorBase {
public:
  struct Properties {
    using inputNamesTy = ::mlir::ArrayAttr;
    inputNamesTy inputNames;

    auto getInputNames() const {
      auto &propStorage = this->inputNames;
      return ::llvm::cast<::mlir::ArrayAttr>(propStorage);
    }
    void setInputNames(const ::mlir::ArrayAttr &propValue) {
      this->inputNames = propValue;
    }
    using nameTy = ::mlir::StringAttr;
    nameTy name;

    auto getName() const {
      auto &propStorage = this->name;
      return ::llvm::dyn_cast_or_null<::mlir::StringAttr>(propStorage);
    }
    void setName(const ::mlir::StringAttr &propValue) {
      this->name = propValue;
    }
    using outputNamesTy = ::mlir::ArrayAttr;
    outputNamesTy outputNames;

    auto getOutputNames() const {
      auto &propStorage = this->outputNames;
      return ::llvm::cast<::mlir::ArrayAttr>(propStorage);
    }
    void setOutputNames(const ::mlir::ArrayAttr &propValue) {
      this->outputNames = propValue;
    }
    using operandSegmentSizesTy = std::array<int32_t, 5>;
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
        rhs.inputNames == this->inputNames &&
        rhs.name == this->name &&
        rhs.outputNames == this->outputNames &&
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
  UnscheduledPipelineOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("pipeline.unscheduled", odsAttrs.getContext());
  }

  UnscheduledPipelineOpGenericAdaptorBase(UnscheduledPipelineOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::StringAttr getNameAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::StringAttr>(getProperties().name);
    return attr;
  }

  ::std::optional< ::llvm::StringRef > getName();
  ::mlir::ArrayAttr getInputNamesAttr() {
    auto attr = ::llvm::cast<::mlir::ArrayAttr>(getProperties().inputNames);
    return attr;
  }

  ::mlir::ArrayAttr getInputNames();
  ::mlir::ArrayAttr getOutputNamesAttr() {
    auto attr = ::llvm::cast<::mlir::ArrayAttr>(getProperties().outputNames);
    return attr;
  }

  ::mlir::ArrayAttr getOutputNames();
  ::mlir::Region &getBody() {
    return *odsRegions[0];
  }

  ::mlir::RegionRange getRegions() {
    return odsRegions;
  }

};

} // namespace detail
template <typename RangeT>
class UnscheduledPipelineOpGenericAdaptor : public detail::UnscheduledPipelineOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::UnscheduledPipelineOpGenericAdaptorBase;
  static constexpr int odsIndex_inputs = 0;
  static constexpr int odsIndex_stall = 1;
  static constexpr int odsIndex_clock = 2;
  static constexpr int odsIndex_reset = 3;
  static constexpr int odsIndex_go = 4;
public:
  UnscheduledPipelineOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  UnscheduledPipelineOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : UnscheduledPipelineOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  UnscheduledPipelineOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs) : UnscheduledPipelineOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  UnscheduledPipelineOpGenericAdaptor(RangeT values, const UnscheduledPipelineOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = UnscheduledPipelineOp, typename = std::enable_if_t<std::is_same_v<LateInst, UnscheduledPipelineOp>>>
  UnscheduledPipelineOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getInputs() {
    return getODSOperands(0);
  }

  ValueT getStall() {
    auto operands = getODSOperands(1);
    return operands.empty() ? ValueT{} : (*operands.begin());
  }

  ValueT getClock() {
    return (*getODSOperands(2).begin());
  }

  ValueT getReset() {
    auto operands = getODSOperands(3);
    return operands.empty() ? ValueT{} : (*operands.begin());
  }

  ValueT getGo() {
    return (*getODSOperands(4).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class UnscheduledPipelineOpAdaptor : public UnscheduledPipelineOpGenericAdaptor<::mlir::ValueRange> {
public:
  using UnscheduledPipelineOpGenericAdaptor::UnscheduledPipelineOpGenericAdaptor;
  UnscheduledPipelineOpAdaptor(UnscheduledPipelineOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class UnscheduledPipelineOp : public ::mlir::Op<UnscheduledPipelineOp, ::mlir::OpTrait::OneRegion, ::mlir::OpTrait::AtLeastNResults<1>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<2>::Impl, ::mlir::OpTrait::SingleBlock, ::mlir::OpTrait::SingleBlockImplicitTerminator<ReturnOp>::Impl, ::mlir::OpTrait::AttrSizedOperandSegments, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::RegionKindInterface::Trait, ::mlir::OpTrait::HasOnlyGraphRegion, ::mlir::OpAsmOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = UnscheduledPipelineOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = UnscheduledPipelineOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_inputs = 0;
  static constexpr int odsIndex_stall = 1;
  static constexpr int odsIndex_clock = 2;
  static constexpr int odsIndex_reset = 3;
  static constexpr int odsIndex_go = 4;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::OpAsmOpInterface::Trait<UnscheduledPipelineOp>::getAsmBlockNames;
  using ::mlir::OpAsmOpInterface::Trait<UnscheduledPipelineOp>::getDefaultDialect;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("inputNames"), ::llvm::StringRef("name"), ::llvm::StringRef("outputNames"), ::llvm::StringRef("operandSegmentSizes")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getInputNamesAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getInputNamesAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getNameAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getNameAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getOutputNamesAttrName() {
    return getAttributeNameForIndex(2);
  }

  static ::mlir::StringAttr getOutputNamesAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 2);
  }

  ::mlir::StringAttr getOperandSegmentSizesAttrName() {
   return (*this)->getName().getAttributeNames().back();
  }

  static ::mlir::StringAttr getOperandSegmentSizesAttrName(::mlir::OperationName name) {
   return name.getAttributeNames().back();
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("pipeline.unscheduled");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::operand_range getInputs() {
    return getODSOperands(0);
  }

  ::mlir::TypedValue<::mlir::IntegerType> getStall() {
    auto operands = getODSOperands(1);
    return operands.empty() ? ::mlir::TypedValue<::mlir::IntegerType>{} : ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*operands.begin());
  }

  ::mlir::TypedValue<::circt::seq::ClockType> getClock() {
    return ::llvm::cast<::mlir::TypedValue<::circt::seq::ClockType>>(*getODSOperands(2).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getReset() {
    auto operands = getODSOperands(3);
    return operands.empty() ? ::mlir::TypedValue<::mlir::IntegerType>{} : ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*operands.begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getGo() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSOperands(4).begin());
  }

  ::mlir::MutableOperandRange getInputsMutable();
  ::mlir::MutableOperandRange getStallMutable();
  ::mlir::OpOperand &getClockMutable() {
    auto range = getODSOperandIndexAndLength(2);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::MutableOperandRange getResetMutable();
  ::mlir::OpOperand &getGoMutable() {
    auto range = getODSOperandIndexAndLength(4);
    return getOperation()->getOpOperand(range.first);
  }

  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index);
  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::result_range getDataOutputs() {
    return getODSResults(0);
  }

  ::mlir::TypedValue<::mlir::IntegerType> getDone() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSResults(1).begin());
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
  ::mlir::StringAttr getNameAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::StringAttr>(getProperties().name);
  }

  ::std::optional< ::llvm::StringRef > getName();
  ::mlir::ArrayAttr getInputNamesAttr() {
    return ::llvm::cast<::mlir::ArrayAttr>(getProperties().inputNames);
  }

  ::mlir::ArrayAttr getInputNames();
  ::mlir::ArrayAttr getOutputNamesAttr() {
    return ::llvm::cast<::mlir::ArrayAttr>(getProperties().outputNames);
  }

  ::mlir::ArrayAttr getOutputNames();
  void setNameAttr(::mlir::StringAttr attr) {
    getProperties().name = attr;
  }

  void setName(::std::optional<::llvm::StringRef> attrValue);
  void setInputNamesAttr(::mlir::ArrayAttr attr) {
    getProperties().inputNames = attr;
  }

  void setOutputNamesAttr(::mlir::ArrayAttr attr) {
    getProperties().outputNames = attr;
  }

  ::mlir::Attribute removeNameAttr() {
      auto attr = getProperties().name;
      getProperties().name = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, TypeRange dataOutputs, ValueRange inputs, ArrayAttr inputNames, ArrayAttr outputNames, Value clock, Value go, Value reset = {}, Value stall = {}, StringAttr name = {}, ArrayAttr stallability = {});
  static UnscheduledPipelineOp create(::mlir::OpBuilder &builder, ::mlir::Location location, TypeRange dataOutputs, ValueRange inputs, ArrayAttr inputNames, ArrayAttr outputNames, Value clock, Value go, Value reset = {}, Value stall = {}, StringAttr name = {}, ArrayAttr stallability = {});
  static UnscheduledPipelineOp create(::mlir::ImplicitLocOpBuilder &builder, TypeRange dataOutputs, ValueRange inputs, ArrayAttr inputNames, ArrayAttr outputNames, Value clock, Value go, Value reset = {}, Value stall = {}, StringAttr name = {}, ArrayAttr stallability = {});
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &p);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
  void getAsmBlockArgumentNames(::mlir::Region&region, ::mlir::OpAsmSetValueNameFn setNameFn);
  static ::llvm::LogicalResult setPropertiesFromParsedAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
private:
  ::mlir::StringAttr getAttributeNameForIndex(unsigned index) {
    return getAttributeNameForIndex((*this)->getName(), index);
  }

  static ::mlir::StringAttr getAttributeNameForIndex(::mlir::OperationName name, unsigned index) {
    assert(index < 3 && "invalid attribute index");
    assert(name.getStringRef() == getOperationName() && "invalid operation name");
    assert(name.isRegistered() && "Operation isn't registered, missing a "
          "dependent dialect loading?");
    return name.getAttributeNames()[index];
  }

public:
  // Returns the entry stage of this pipeline.
  Block* getEntryStage() {
    Region* region = &getOperation()->getRegion(0);
    return &region->front();
  }

  // Returns true if this pipeline has a stall signal.
  bool hasStall() {
    return static_cast<bool>(getStall());
  }

  // Returns true if this pipeline has a reset signal.
  bool hasReset() {
    return static_cast<bool>(getReset());
  }

  mlir::Block::BlockArgListType getInnerInputs() {
    return getEntryStage()->getArguments().take_front(getInputs().size());
  }

  // Returns a list of external inputs to the pipeline. These are defined
  // as any value which is defined outside the inner pipeline region.
  // This will walk the entire pipeline, so it is recommended to cache the
  // result if it is used multiple times.
  llvm::SmallVector<Value> getExtInputs() {
    return detail::getValuesDefinedOutsideRegion(getRegion());
  }

  // Gets the n'th stage of this pipeline
  Block* getStage(unsigned n) {
    auto& blocks = getRegion().getBlocks();
    assert(n < blocks.size() && "Stage index out of bounds");
    return &*std::next(blocks.begin(), n);
  }

  // Returns the enable signal of the given pipeline stage. This is always
  // the last block argument of a stage for anything but the entry stage.
  Value getStageEnableSignal(size_t stageIdx) {
    return getStageEnableSignal(getStage(stageIdx));
  }

  // Returns the enable signal for the given stage. The enable signal is always
  // the last signal in the stage argument list.
  Value getStageEnableSignal(Block* stage) {
    return stage->getArguments().back();
  }
};

} // namespace circt::pipeline
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::pipeline::UnscheduledPipelineOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::pipeline::detail::UnscheduledPipelineOpGenericAdaptorBase::Properties)


#endif // GET_OP_CLASSES

