/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Op Declarations                                                            *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: Seq.td                                                               *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace circt::seq {

/// Produces a clock divided by a power of two
/// The output clock is phase-aligned to the input clock.
/// 
/// ```
/// %div_clock = seq.clock_div %clock by 1
/// ```
class ClockDividerOp;

} // namespace circt::seq
namespace circt::seq {

/// Safely gates a clock with an enable signal
/// The `seq.clock_gate` enables and disables a clock safely, without glitches,
/// based on a boolean enable value. If the enable operand is 1, the output
/// clock produced by the clock gate is identical to the input clock. If the
/// enable operand is 0, the output clock is a constant zero.
/// 
/// The `enable` operand is sampled at the rising edge of the input clock; any
/// changes on the enable before or after that edge are ignored and do not
/// affect the output clock.
/// 
/// The `test_enable` operand is optional and if present is OR'd together with
/// the `enable` operand to determine whether the output clock is gated or not.
/// 
/// The op can be referred to using an inner symbol. Upon translation, the
/// symbol will target the instance to the external module it lowers to.
/// 
/// ```
/// %gatedClock = seq.clock_gate %clock, %enable
/// %gatedClock = seq.clock_gate %clock, %enable, %test_enable
/// ```
class ClockGateOp;

} // namespace circt::seq
namespace circt::seq {

/// Inverts the clock signal
/// Note that the compiler can optimize inverters away, preventing their
/// use as part of explicit clock buffers.
/// 
/// ```
/// %inv_clock = seq.clock_inv %clock
/// ```
class ClockInverterOp;

} // namespace circt::seq
namespace circt::seq {

/// Safely selects a clock based on a condition
/// The `seq.clock_mux` op selects a clock from two options. If `cond` is
/// true, the first clock operand is selected to drive downstream logic.
/// Otherwise, the second clock is used.
/// 
/// ```
/// %clock = seq.clock_mux %cond, %trueClock, %falseClock
/// ```
class ClockMuxOp;

} // namespace circt::seq
namespace circt::seq {

/// When enabled, register a value
/// See the Seq dialect rationale for a longer description
class CompRegClockEnabledOp;

} // namespace circt::seq
namespace circt::seq {

/// Register a value, storing it for one cycle
/// See the Seq dialect rationale for a longer description
class CompRegOp;

} // namespace circt::seq
namespace circt::seq {

/// Produce constant clock value
/// The constant operation produces a constant clock value.
/// ```
///   %clock = seq.const_clock low
/// ```
class ConstClockOp;

} // namespace circt::seq
namespace circt::seq {

/// A high-level FIFO operation
/// This operation represents a high-level abstraction of a FIFO. Access to the
/// FIFO is structural, and thus may be composed with other core RTL dialect
/// operations.
/// The fifo operation is configurable with the following parameters:
/// 1. Depth (cycles)
/// 2. Read latency (cycles) is the number of cycles it takes for a read to
///    return data after the read enable signal is asserted.
/// 3. Almost full/empty thresholds (optional). If not provided, these will
///    be asserted when the FIFO is full/empty.
/// 
/// Like `seq.hlmem` there are no guarantees that all possible fifo configuration
/// are able to be lowered. Available lowering passes will pattern match on the
/// requested fifo configuration and attempt to provide a legal lowering.
class FIFOOp;

} // namespace circt::seq
namespace circt::seq {

/// A FIRRTL-flavored memory
/// The `seq.firmem` op represents memories lowered from the FIRRTL dialect. It
/// is used to capture some of the peculiarities of what FIRRTL expects from
/// memories, while still representing them at the HW dialect level.
/// 
/// A `seq.firmem` declares the memory and captures the memory-level parameters
/// such as width and depth or how read/write collisions are resolved. The read,
/// write, and read-write ports are expressed as separate operations that take
/// the declared memory as an operand.
class FirMemOp;

} // namespace circt::seq
namespace circt::seq {

/// A memory read port
/// The `seq.firmem.read_port` op represents a read port on a `seq.firmem`
/// memory. It takes the memory as an operand, together with the address to
/// be read, the clock on which the read is synchronized, and an optional
/// enable. Omitting the enable operand has the same effect as passing a
/// constant `true` to it.
class FirMemReadOp;

} // namespace circt::seq
namespace circt::seq {

/// A memory read-write port
/// The `seq.firmem.read_write_port` op represents a read-write port on a
/// `seq.firmem` memory. It takes the memory as an operand, together with the
/// address and data to be written, a mode operand indicating whether the port
/// should perform a read (`mode=0`) or a write (`mode=1`), the clock on which
/// the read and write is synchronized, an optional enable, and and optional
/// write mask. Omitting the enable operand has the same effect as passing a
/// constant `true` to it. Omitting the write mask operand has the same effect
/// as passing an all-ones value to it. A write mask operand can only be present
/// if the `seq.firmem` specifies a mask width; otherwise it must be omitted.
class FirMemReadWriteOp;

} // namespace circt::seq
namespace circt::seq {

/// A memory write port
/// The `seq.firmem.write_port` op represents a write port on a `seq.firmem`
/// memory. It takes the memory as an operand, together with the address and
/// data to be written, the clock on which the write is synchronized, an
/// optional enable, and and optional write mask. Omitting the enable operand
/// has the same effect as passing a constant `true` to it. Omitting the write
/// mask operand has the same effect as passing an all-ones value to it. A write
/// mask operand can only be present if the `seq.firmem` specifies a mask width;
/// otherwise it must be omitted.
class FirMemWriteOp;

} // namespace circt::seq
namespace circt::seq {

/// Register with preset and sync or async reset
/// `firreg` represents registers originating from FIRRTL after the lowering
/// of the IR to HW.  The register is used as an intermediary in the process
/// of lowering to SystemVerilog to facilitate optimisation at the HW level,
/// compactly representing a register with a single operation instead of
/// composing it from register definitions, always blocks and if statements.
/// 
/// The `data` output of the register accesses the value it stores.  On the
/// rising edge of the `clk` input, the register takes a new value provided
/// by the `next` signal.  Optionally, the register can also be provided with
/// a synchronous or an asynchronous `reset` signal and `resetValue`, as shown
/// in the example below.
/// 
/// ```
/// %name = seq.firreg %next clock %clk [ sym @sym ]
///     [ reset (sync|async) %reset, %value ]
///     [ preset value ] : type
/// ```
/// 
/// Implicitly, all registers are pre-set to a randomized value.
/// 
/// A register implementing a counter starting at 0 from reset can be defined
/// as follows:
/// 
/// ```
/// %zero = hw.constant 0 : i32
/// %reg = seq.firreg %next clock %clk reset sync %reset, %zero : i32
/// %one = hw.constant 1 : i32
/// %next = comb.add %reg, %one : i32
/// ```
class FirRegOp;

} // namespace circt::seq
namespace circt::seq {

/// Cast from a clock type to a wire type
class FromClockOp;

} // namespace circt::seq
namespace circt::seq {

/// Cast from an immutable type to a wire type
class FromImmutableOp;

} // namespace circt::seq
namespace circt::seq {

/// Instantiate a high-level memory.
/// See the Seq dialect rationale for a longer description
class HLMemOp;

} // namespace circt::seq
namespace circt::seq {

/// Operation that produces values for initialization
/// `seq.initial` op creates values wrapped types with !seq.immutable.
/// See the Seq dialect rationale for a longer description.
class InitialOp;

} // namespace circt::seq
namespace circt::seq {

/// Structural read access to a seq.hlmem, with an optional read enable signal.
class ReadPortOp;

} // namespace circt::seq
namespace circt::seq {

/// Shift register
/// The `seq.shiftreg` op represents a shift register. It takes the input
/// value and shifts it every cycle when `clockEnable` is asserted.
/// The `reset` and `resetValue` operands are optional and if present, every
/// entry in the shift register will be initialized to `resetValue` upon
/// assertion of the reset signal. Exact reset behavior (sync/async) is
/// implementation defined.
class ShiftRegOp;

} // namespace circt::seq
namespace circt::seq {

/// Cast from a wire type to a clock type
class ToClockOp;

} // namespace circt::seq
namespace circt::seq {

/// Structural write access to a seq.hlmem
class WritePortOp;

} // namespace circt::seq
namespace circt::seq {

/// Yield values
class YieldOp;

} // namespace circt::seq
#ifdef GET_OP_CLASSES
#undef GET_OP_CLASSES

namespace circt::seq {


//===----------------------------------------------------------------------===//
// ::circt::seq::ClockDividerOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ClockDividerOpGenericAdaptorBase {
public:
  struct Properties {
    using pow2Ty = ::mlir::IntegerAttr;
    pow2Ty pow2;

    auto getPow2() const {
      auto &propStorage = this->pow2;
      return ::llvm::cast<::mlir::IntegerAttr>(propStorage);
    }
    void setPow2(const ::mlir::IntegerAttr &propValue) {
      this->pow2 = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.pow2 == this->pow2 &&
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
  ClockDividerOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("seq.clock_div", odsAttrs.getContext());
  }

  ClockDividerOpGenericAdaptorBase(ClockDividerOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::IntegerAttr getPow2Attr() {
    auto attr = ::llvm::cast<::mlir::IntegerAttr>(getProperties().pow2);
    return attr;
  }

  uint64_t getPow2();
};

} // namespace detail
template <typename RangeT>
class ClockDividerOpGenericAdaptor : public detail::ClockDividerOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ClockDividerOpGenericAdaptorBase;
  static constexpr int odsIndex_input = 0;
public:
  ClockDividerOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ClockDividerOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : ClockDividerOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ClockDividerOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ClockDividerOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ClockDividerOpGenericAdaptor(RangeT values, const ClockDividerOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ClockDividerOp, typename = std::enable_if_t<std::is_same_v<LateInst, ClockDividerOp>>>
  ClockDividerOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class ClockDividerOpAdaptor : public ClockDividerOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ClockDividerOpGenericAdaptor::ClockDividerOpGenericAdaptor;
  ClockDividerOpAdaptor(ClockDividerOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ClockDividerOp : public ::mlir::Op<ClockDividerOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::circt::seq::ClockType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ClockDividerOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ClockDividerOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_input = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("pow2")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getPow2AttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getPow2AttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("seq.clock_div");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::circt::seq::ClockType> getInput() {
    return ::llvm::cast<::mlir::TypedValue<::circt::seq::ClockType>>(*getODSOperands(0).begin());
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

  ::mlir::TypedValue<::circt::seq::ClockType> getOutput() {
    return ::llvm::cast<::mlir::TypedValue<::circt::seq::ClockType>>(*getODSResults(0).begin());
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
  ::mlir::IntegerAttr getPow2Attr() {
    return ::llvm::cast<::mlir::IntegerAttr>(getProperties().pow2);
  }

  uint64_t getPow2();
  void setPow2Attr(::mlir::IntegerAttr attr) {
    getProperties().pow2 = attr;
  }

  void setPow2(uint64_t attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type output, ::mlir::Value input, ::mlir::IntegerAttr pow2);
  static ClockDividerOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type output, ::mlir::Value input, ::mlir::IntegerAttr pow2);
  static ClockDividerOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type output, ::mlir::Value input, ::mlir::IntegerAttr pow2);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value input, ::mlir::IntegerAttr pow2);
  static ClockDividerOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value input, ::mlir::IntegerAttr pow2);
  static ClockDividerOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value input, ::mlir::IntegerAttr pow2);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value input, ::mlir::IntegerAttr pow2);
  static ClockDividerOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value input, ::mlir::IntegerAttr pow2);
  static ClockDividerOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value input, ::mlir::IntegerAttr pow2);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type output, ::mlir::Value input, uint64_t pow2);
  static ClockDividerOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type output, ::mlir::Value input, uint64_t pow2);
  static ClockDividerOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type output, ::mlir::Value input, uint64_t pow2);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value input, uint64_t pow2);
  static ClockDividerOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value input, uint64_t pow2);
  static ClockDividerOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value input, uint64_t pow2);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value input, uint64_t pow2);
  static ClockDividerOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value input, uint64_t pow2);
  static ClockDividerOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value input, uint64_t pow2);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ClockDividerOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ClockDividerOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ClockDividerOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ClockDividerOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ClockDividerOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ClockDividerOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ClockDividerOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ClockDividerOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::llvm::LogicalResult canonicalize(ClockDividerOp op, ::mlir::PatternRewriter &rewriter);
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::PropertyRef properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
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
};

} // namespace circt::seq
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::seq::ClockDividerOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::seq::detail::ClockDividerOpGenericAdaptorBase::Properties)

namespace circt::seq {


//===----------------------------------------------------------------------===//
// ::circt::seq::ClockGateOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ClockGateOpGenericAdaptorBase {
public:
  struct Properties {
    using inner_symTy = ::circt::hw::InnerSymAttr;
    inner_symTy inner_sym;

    auto getInnerSym() const {
      auto &propStorage = this->inner_sym;
      return ::llvm::dyn_cast_or_null<::circt::hw::InnerSymAttr>(propStorage);
    }
    void setInnerSym(const ::circt::hw::InnerSymAttr &propValue) {
      this->inner_sym = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.inner_sym == this->inner_sym &&
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
  ClockGateOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("seq.clock_gate", odsAttrs.getContext());
  }

  ClockGateOpGenericAdaptorBase(ClockGateOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::circt::hw::InnerSymAttr getInnerSymAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::circt::hw::InnerSymAttr>(getProperties().inner_sym);
    return attr;
  }

  ::std::optional<::circt::hw::InnerSymAttr> getInnerSym();
};

} // namespace detail
template <typename RangeT>
class ClockGateOpGenericAdaptor : public detail::ClockGateOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ClockGateOpGenericAdaptorBase;
  static constexpr int odsIndex_input = 0;
  static constexpr int odsIndex_enable = 1;
  static constexpr int odsIndex_test_enable = 2;
public:
  ClockGateOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ClockGateOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : ClockGateOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ClockGateOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ClockGateOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ClockGateOpGenericAdaptor(RangeT values, const ClockGateOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ClockGateOp, typename = std::enable_if_t<std::is_same_v<LateInst, ClockGateOp>>>
  ClockGateOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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

  ValueT getEnable() {
    return (*getODSOperands(1).begin());
  }

  ValueT getTestEnable() {
    auto operands = getODSOperands(2);
    return operands.empty() ? ValueT{} : (*operands.begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class ClockGateOpAdaptor : public ClockGateOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ClockGateOpGenericAdaptor::ClockGateOpGenericAdaptor;
  ClockGateOpAdaptor(ClockGateOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ClockGateOp : public ::mlir::Op<ClockGateOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::circt::seq::ClockType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<2>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::circt::hw::InnerSymbolOpInterface::Trait, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ClockGateOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ClockGateOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_input = 0;
  static constexpr int odsIndex_enable = 1;
  static constexpr int odsIndex_test_enable = 2;
  using Properties = FoldAdaptor::Properties;
  using ::circt::hw::InnerSymbolOpInterface::Trait<ClockGateOp>::getInnerNameAttr;
  using ::circt::hw::InnerSymbolOpInterface::Trait<ClockGateOp>::getInnerName;
  using ::circt::hw::InnerSymbolOpInterface::Trait<ClockGateOp>::setInnerSymbol;
  using ::circt::hw::InnerSymbolOpInterface::Trait<ClockGateOp>::setInnerSymbolAttr;
  using ::circt::hw::InnerSymbolOpInterface::Trait<ClockGateOp>::getInnerRef;
  using ::circt::hw::InnerSymbolOpInterface::Trait<ClockGateOp>::getInnerSymAttr;
  using ::circt::hw::InnerSymbolOpInterface::Trait<ClockGateOp>::supportsPerFieldSymbols;
  using ::circt::hw::InnerSymbolOpInterface::Trait<ClockGateOp>::getTargetResult;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("inner_sym")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getInnerSymAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getInnerSymAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("seq.clock_gate");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::circt::seq::ClockType> getInput() {
    return ::llvm::cast<::mlir::TypedValue<::circt::seq::ClockType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getEnable() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSOperands(1).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getTestEnable() {
    auto operands = getODSOperands(2);
    return operands.empty() ? ::mlir::TypedValue<::mlir::IntegerType>{} : ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*operands.begin());
  }

  ::mlir::OpOperand &getInputMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getEnableMutable() {
    auto range = getODSOperandIndexAndLength(1);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::MutableOperandRange getTestEnableMutable();
  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::circt::seq::ClockType> getOutput() {
    return ::llvm::cast<::mlir::TypedValue<::circt::seq::ClockType>>(*getODSResults(0).begin());
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
  ::circt::hw::InnerSymAttr getInnerSymAttr() {
    return ::llvm::dyn_cast_or_null<::circt::hw::InnerSymAttr>(getProperties().inner_sym);
  }

  ::std::optional<::circt::hw::InnerSymAttr> getInnerSym();
  void setInnerSymAttr(::circt::hw::InnerSymAttr attr) {
    getProperties().inner_sym = attr;
  }

  ::mlir::Attribute removeInnerSymAttr() {
      auto attr = getProperties().inner_sym;
      getProperties().inner_sym = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value clock, Value enable);
  static ClockGateOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value clock, Value enable);
  static ClockGateOp create(::mlir::ImplicitLocOpBuilder &builder, Value clock, Value enable);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type output, ::mlir::Value input, ::mlir::Value enable, /*optional*/::mlir::Value test_enable, /*optional*/::circt::hw::InnerSymAttr inner_sym);
  static ClockGateOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type output, ::mlir::Value input, ::mlir::Value enable, /*optional*/::mlir::Value test_enable, /*optional*/::circt::hw::InnerSymAttr inner_sym);
  static ClockGateOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type output, ::mlir::Value input, ::mlir::Value enable, /*optional*/::mlir::Value test_enable, /*optional*/::circt::hw::InnerSymAttr inner_sym);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value input, ::mlir::Value enable, /*optional*/::mlir::Value test_enable, /*optional*/::circt::hw::InnerSymAttr inner_sym);
  static ClockGateOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value input, ::mlir::Value enable, /*optional*/::mlir::Value test_enable, /*optional*/::circt::hw::InnerSymAttr inner_sym);
  static ClockGateOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value input, ::mlir::Value enable, /*optional*/::mlir::Value test_enable, /*optional*/::circt::hw::InnerSymAttr inner_sym);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value input, ::mlir::Value enable, /*optional*/::mlir::Value test_enable, /*optional*/::circt::hw::InnerSymAttr inner_sym);
  static ClockGateOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value input, ::mlir::Value enable, /*optional*/::mlir::Value test_enable, /*optional*/::circt::hw::InnerSymAttr inner_sym);
  static ClockGateOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value input, ::mlir::Value enable, /*optional*/::mlir::Value test_enable, /*optional*/::circt::hw::InnerSymAttr inner_sym);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ClockGateOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ClockGateOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ClockGateOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ClockGateOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ClockGateOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ClockGateOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ClockGateOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ClockGateOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::llvm::LogicalResult canonicalize(ClockGateOp op, ::mlir::PatternRewriter &rewriter);
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
  ::mlir::OpFoldResult fold(FoldAdaptor adaptor);
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::PropertyRef properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
  static std::optional<size_t> getTargetResultIndex();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
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
};

} // namespace circt::seq
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::seq::ClockGateOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::seq::detail::ClockGateOpGenericAdaptorBase::Properties)

namespace circt::seq {


//===----------------------------------------------------------------------===//
// ::circt::seq::ClockInverterOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ClockInverterOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  ClockInverterOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("seq.clock_inv", odsAttrs.getContext());
  }

  ClockInverterOpGenericAdaptorBase(ClockInverterOp op);

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
class ClockInverterOpGenericAdaptor : public detail::ClockInverterOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ClockInverterOpGenericAdaptorBase;
  static constexpr int odsIndex_input = 0;
public:
  ClockInverterOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ClockInverterOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : ClockInverterOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ClockInverterOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ClockInverterOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ClockInverterOpGenericAdaptor(RangeT values, const ClockInverterOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ClockInverterOp, typename = std::enable_if_t<std::is_same_v<LateInst, ClockInverterOp>>>
  ClockInverterOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class ClockInverterOpAdaptor : public ClockInverterOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ClockInverterOpGenericAdaptor::ClockInverterOpGenericAdaptor;
  ClockInverterOpAdaptor(ClockInverterOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ClockInverterOp : public ::mlir::Op<ClockInverterOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::circt::seq::ClockType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ClockInverterOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ClockInverterOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_input = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("seq.clock_inv");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::circt::seq::ClockType> getInput() {
    return ::llvm::cast<::mlir::TypedValue<::circt::seq::ClockType>>(*getODSOperands(0).begin());
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

  ::mlir::TypedValue<::circt::seq::ClockType> getOutput() {
    return ::llvm::cast<::mlir::TypedValue<::circt::seq::ClockType>>(*getODSResults(0).begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type output, ::mlir::Value input);
  static ClockInverterOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type output, ::mlir::Value input);
  static ClockInverterOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type output, ::mlir::Value input);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value input);
  static ClockInverterOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value input);
  static ClockInverterOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value input);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value input);
  static ClockInverterOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value input);
  static ClockInverterOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value input);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ClockInverterOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ClockInverterOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ClockInverterOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ClockInverterOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ClockInverterOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ClockInverterOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ClockInverterOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ClockInverterOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::mlir::OpFoldResult fold(FoldAdaptor adaptor);
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::PropertyRef properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
};

} // namespace circt::seq
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::seq::ClockInverterOp)

namespace circt::seq {


//===----------------------------------------------------------------------===//
// ::circt::seq::ClockMuxOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ClockMuxOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  ClockMuxOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("seq.clock_mux", odsAttrs.getContext());
  }

  ClockMuxOpGenericAdaptorBase(ClockMuxOp op);

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
class ClockMuxOpGenericAdaptor : public detail::ClockMuxOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ClockMuxOpGenericAdaptorBase;
  static constexpr int odsIndex_cond = 0;
  static constexpr int odsIndex_trueClock = 1;
  static constexpr int odsIndex_falseClock = 2;
public:
  ClockMuxOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ClockMuxOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : ClockMuxOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ClockMuxOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ClockMuxOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ClockMuxOpGenericAdaptor(RangeT values, const ClockMuxOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ClockMuxOp, typename = std::enable_if_t<std::is_same_v<LateInst, ClockMuxOp>>>
  ClockMuxOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getCond() {
    return (*getODSOperands(0).begin());
  }

  ValueT getTrueClock() {
    return (*getODSOperands(1).begin());
  }

  ValueT getFalseClock() {
    return (*getODSOperands(2).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class ClockMuxOpAdaptor : public ClockMuxOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ClockMuxOpGenericAdaptor::ClockMuxOpGenericAdaptor;
  ClockMuxOpAdaptor(ClockMuxOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ClockMuxOp : public ::mlir::Op<ClockMuxOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::circt::seq::ClockType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::NOperands<3>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ClockMuxOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ClockMuxOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_cond = 0;
  static constexpr int odsIndex_trueClock = 1;
  static constexpr int odsIndex_falseClock = 2;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("seq.clock_mux");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::IntegerType> getCond() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::circt::seq::ClockType> getTrueClock() {
    return ::llvm::cast<::mlir::TypedValue<::circt::seq::ClockType>>(*getODSOperands(1).begin());
  }

  ::mlir::TypedValue<::circt::seq::ClockType> getFalseClock() {
    return ::llvm::cast<::mlir::TypedValue<::circt::seq::ClockType>>(*getODSOperands(2).begin());
  }

  ::mlir::OpOperand &getCondMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getTrueClockMutable() {
    auto range = getODSOperandIndexAndLength(1);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getFalseClockMutable() {
    auto range = getODSOperandIndexAndLength(2);
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

  ::mlir::TypedValue<::circt::seq::ClockType> getResult() {
    return ::llvm::cast<::mlir::TypedValue<::circt::seq::ClockType>>(*getODSResults(0).begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value cond, ::mlir::Value trueClock, ::mlir::Value falseClock);
  static ClockMuxOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value cond, ::mlir::Value trueClock, ::mlir::Value falseClock);
  static ClockMuxOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value cond, ::mlir::Value trueClock, ::mlir::Value falseClock);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value cond, ::mlir::Value trueClock, ::mlir::Value falseClock);
  static ClockMuxOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value cond, ::mlir::Value trueClock, ::mlir::Value falseClock);
  static ClockMuxOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value cond, ::mlir::Value trueClock, ::mlir::Value falseClock);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value cond, ::mlir::Value trueClock, ::mlir::Value falseClock);
  static ClockMuxOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value cond, ::mlir::Value trueClock, ::mlir::Value falseClock);
  static ClockMuxOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value cond, ::mlir::Value trueClock, ::mlir::Value falseClock);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ClockMuxOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ClockMuxOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ClockMuxOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ClockMuxOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ClockMuxOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ClockMuxOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ClockMuxOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ClockMuxOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::mlir::OpFoldResult fold(FoldAdaptor adaptor);
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::PropertyRef properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
};

} // namespace circt::seq
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::seq::ClockMuxOp)

namespace circt::seq {


//===----------------------------------------------------------------------===//
// ::circt::seq::CompRegClockEnabledOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class CompRegClockEnabledOpGenericAdaptorBase {
public:
  struct Properties {
    using inner_symTy = ::circt::hw::InnerSymAttr;
    inner_symTy inner_sym;

    auto getInnerSym() const {
      auto &propStorage = this->inner_sym;
      return ::llvm::dyn_cast_or_null<::circt::hw::InnerSymAttr>(propStorage);
    }
    void setInnerSym(const ::circt::hw::InnerSymAttr &propValue) {
      this->inner_sym = propValue;
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
    using operandSegmentSizesTy = std::array<int32_t, 6>;
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
        rhs.inner_sym == this->inner_sym &&
        rhs.name == this->name &&
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
  CompRegClockEnabledOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("seq.compreg.ce", odsAttrs.getContext());
  }

  CompRegClockEnabledOpGenericAdaptorBase(CompRegClockEnabledOp op);

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
  ::circt::hw::InnerSymAttr getInnerSymAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::circt::hw::InnerSymAttr>(getProperties().inner_sym);
    return attr;
  }

  ::std::optional<::circt::hw::InnerSymAttr> getInnerSym();
};

} // namespace detail
template <typename RangeT>
class CompRegClockEnabledOpGenericAdaptor : public detail::CompRegClockEnabledOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::CompRegClockEnabledOpGenericAdaptorBase;
  static constexpr int odsIndex_input = 0;
  static constexpr int odsIndex_clk = 1;
  static constexpr int odsIndex_clockEnable = 2;
  static constexpr int odsIndex_reset = 3;
  static constexpr int odsIndex_resetValue = 4;
  static constexpr int odsIndex_initialValue = 5;
public:
  CompRegClockEnabledOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  CompRegClockEnabledOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : CompRegClockEnabledOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  CompRegClockEnabledOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs) : CompRegClockEnabledOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  CompRegClockEnabledOpGenericAdaptor(RangeT values, const CompRegClockEnabledOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = CompRegClockEnabledOp, typename = std::enable_if_t<std::is_same_v<LateInst, CompRegClockEnabledOp>>>
  CompRegClockEnabledOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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

  ValueT getClk() {
    return (*getODSOperands(1).begin());
  }

  ValueT getClockEnable() {
    return (*getODSOperands(2).begin());
  }

  ValueT getReset() {
    auto operands = getODSOperands(3);
    return operands.empty() ? ValueT{} : (*operands.begin());
  }

  ValueT getResetValue() {
    auto operands = getODSOperands(4);
    return operands.empty() ? ValueT{} : (*operands.begin());
  }

  ValueT getInitialValue() {
    auto operands = getODSOperands(5);
    return operands.empty() ? ValueT{} : (*operands.begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class CompRegClockEnabledOpAdaptor : public CompRegClockEnabledOpGenericAdaptor<::mlir::ValueRange> {
public:
  using CompRegClockEnabledOpGenericAdaptor::CompRegClockEnabledOpGenericAdaptor;
  CompRegClockEnabledOpAdaptor(CompRegClockEnabledOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class CompRegClockEnabledOp : public ::mlir::Op<CompRegClockEnabledOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::Type>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<3>::Impl, ::mlir::OpTrait::AttrSizedOperandSegments, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, circt::seq::Clocked::Trait, circt::seq::Resettable::Trait, ::mlir::OpAsmOpInterface::Trait, ::circt::hw::InnerSymbolOpInterface::Trait, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = CompRegClockEnabledOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = CompRegClockEnabledOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_input = 0;
  static constexpr int odsIndex_clk = 1;
  static constexpr int odsIndex_clockEnable = 2;
  static constexpr int odsIndex_reset = 3;
  static constexpr int odsIndex_resetValue = 4;
  static constexpr int odsIndex_initialValue = 5;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::OpAsmOpInterface::Trait<CompRegClockEnabledOp>::getAsmBlockArgumentNames;
  using ::mlir::OpAsmOpInterface::Trait<CompRegClockEnabledOp>::getAsmBlockNames;
  using ::mlir::OpAsmOpInterface::Trait<CompRegClockEnabledOp>::getDefaultDialect;
  using ::circt::hw::InnerSymbolOpInterface::Trait<CompRegClockEnabledOp>::getInnerNameAttr;
  using ::circt::hw::InnerSymbolOpInterface::Trait<CompRegClockEnabledOp>::getInnerName;
  using ::circt::hw::InnerSymbolOpInterface::Trait<CompRegClockEnabledOp>::setInnerSymbol;
  using ::circt::hw::InnerSymbolOpInterface::Trait<CompRegClockEnabledOp>::setInnerSymbolAttr;
  using ::circt::hw::InnerSymbolOpInterface::Trait<CompRegClockEnabledOp>::getInnerRef;
  using ::circt::hw::InnerSymbolOpInterface::Trait<CompRegClockEnabledOp>::getInnerSymAttr;
  using ::circt::hw::InnerSymbolOpInterface::Trait<CompRegClockEnabledOp>::supportsPerFieldSymbols;
  using ::circt::hw::InnerSymbolOpInterface::Trait<CompRegClockEnabledOp>::getTargetResult;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("inner_sym"), ::llvm::StringRef("name"), ::llvm::StringRef("operandSegmentSizes")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getInnerSymAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getInnerSymAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getNameAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getNameAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getOperandSegmentSizesAttrName() {
   return (*this)->getName().getAttributeNames().back();
  }

  static ::mlir::StringAttr getOperandSegmentSizesAttrName(::mlir::OperationName name) {
   return name.getAttributeNames().back();
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("seq.compreg.ce");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::Type> getInput() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::circt::seq::ClockType> getClk() {
    return ::llvm::cast<::mlir::TypedValue<::circt::seq::ClockType>>(*getODSOperands(1).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getClockEnable() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSOperands(2).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getReset() {
    auto operands = getODSOperands(3);
    return operands.empty() ? ::mlir::TypedValue<::mlir::IntegerType>{} : ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*operands.begin());
  }

  ::mlir::TypedValue<::mlir::Type> getResetValue() {
    auto operands = getODSOperands(4);
    return operands.empty() ? ::mlir::TypedValue<::mlir::Type>{} : ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*operands.begin());
  }

  ::mlir::TypedValue<::circt::seq::ImmutableType> getInitialValue() {
    auto operands = getODSOperands(5);
    return operands.empty() ? ::mlir::TypedValue<::circt::seq::ImmutableType>{} : ::llvm::cast<::mlir::TypedValue<::circt::seq::ImmutableType>>(*operands.begin());
  }

  ::mlir::OpOperand &getInputMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getClkMutable() {
    auto range = getODSOperandIndexAndLength(1);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getClockEnableMutable() {
    auto range = getODSOperandIndexAndLength(2);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::MutableOperandRange getResetMutable();
  ::mlir::MutableOperandRange getResetValueMutable();
  ::mlir::MutableOperandRange getInitialValueMutable();
  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::Type> getData() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSResults(0).begin());
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
  ::circt::hw::InnerSymAttr getInnerSymAttr() {
    return ::llvm::dyn_cast_or_null<::circt::hw::InnerSymAttr>(getProperties().inner_sym);
  }

  ::std::optional<::circt::hw::InnerSymAttr> getInnerSym();
  void setNameAttr(::mlir::StringAttr attr) {
    getProperties().name = attr;
  }

  void setName(::std::optional<::llvm::StringRef> attrValue);
  void setInnerSymAttr(::circt::hw::InnerSymAttr attr) {
    getProperties().inner_sym = attr;
  }

  ::mlir::Attribute removeNameAttr() {
      auto attr = getProperties().name;
      getProperties().name = {};
      return attr;
  }

  ::mlir::Attribute removeInnerSymAttr() {
      auto attr = getProperties().inner_sym;
      getProperties().inner_sym = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value input, Value clk, Value ce, StringRef name);
  static CompRegClockEnabledOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value input, Value clk, Value ce, StringRef name);
  static CompRegClockEnabledOp create(::mlir::ImplicitLocOpBuilder &builder, Value input, Value clk, Value ce, StringRef name);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value input, Value clk, Value ce, Value reset, Value rstValue, StringRef name, Value initialValue = {});
  static CompRegClockEnabledOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value input, Value clk, Value ce, Value reset, Value rstValue, StringRef name, Value initialValue = {});
  static CompRegClockEnabledOp create(::mlir::ImplicitLocOpBuilder &builder, Value input, Value clk, Value ce, Value reset, Value rstValue, StringRef name, Value initialValue = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type data, ::mlir::Value input, ::mlir::Value clk, ::mlir::Value clockEnable, /*optional*/::mlir::StringAttr name, /*optional*/::mlir::Value reset, /*optional*/::mlir::Value resetValue, /*optional*/::mlir::Value initialValue, /*optional*/::circt::hw::InnerSymAttr inner_sym);
  static CompRegClockEnabledOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type data, ::mlir::Value input, ::mlir::Value clk, ::mlir::Value clockEnable, /*optional*/::mlir::StringAttr name, /*optional*/::mlir::Value reset, /*optional*/::mlir::Value resetValue, /*optional*/::mlir::Value initialValue, /*optional*/::circt::hw::InnerSymAttr inner_sym);
  static CompRegClockEnabledOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type data, ::mlir::Value input, ::mlir::Value clk, ::mlir::Value clockEnable, /*optional*/::mlir::StringAttr name, /*optional*/::mlir::Value reset, /*optional*/::mlir::Value resetValue, /*optional*/::mlir::Value initialValue, /*optional*/::circt::hw::InnerSymAttr inner_sym);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value input, ::mlir::Value clk, ::mlir::Value clockEnable, /*optional*/::mlir::StringAttr name, /*optional*/::mlir::Value reset, /*optional*/::mlir::Value resetValue, /*optional*/::mlir::Value initialValue, /*optional*/::circt::hw::InnerSymAttr inner_sym);
  static CompRegClockEnabledOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value input, ::mlir::Value clk, ::mlir::Value clockEnable, /*optional*/::mlir::StringAttr name, /*optional*/::mlir::Value reset, /*optional*/::mlir::Value resetValue, /*optional*/::mlir::Value initialValue, /*optional*/::circt::hw::InnerSymAttr inner_sym);
  static CompRegClockEnabledOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value input, ::mlir::Value clk, ::mlir::Value clockEnable, /*optional*/::mlir::StringAttr name, /*optional*/::mlir::Value reset, /*optional*/::mlir::Value resetValue, /*optional*/::mlir::Value initialValue, /*optional*/::circt::hw::InnerSymAttr inner_sym);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value input, ::mlir::Value clk, ::mlir::Value clockEnable, /*optional*/::mlir::StringAttr name, /*optional*/::mlir::Value reset, /*optional*/::mlir::Value resetValue, /*optional*/::mlir::Value initialValue, /*optional*/::circt::hw::InnerSymAttr inner_sym);
  static CompRegClockEnabledOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value input, ::mlir::Value clk, ::mlir::Value clockEnable, /*optional*/::mlir::StringAttr name, /*optional*/::mlir::Value reset, /*optional*/::mlir::Value resetValue, /*optional*/::mlir::Value initialValue, /*optional*/::circt::hw::InnerSymAttr inner_sym);
  static CompRegClockEnabledOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value input, ::mlir::Value clk, ::mlir::Value clockEnable, /*optional*/::mlir::StringAttr name, /*optional*/::mlir::Value reset, /*optional*/::mlir::Value resetValue, /*optional*/::mlir::Value initialValue, /*optional*/::circt::hw::InnerSymAttr inner_sym);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static CompRegClockEnabledOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static CompRegClockEnabledOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static CompRegClockEnabledOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static CompRegClockEnabledOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static CompRegClockEnabledOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static CompRegClockEnabledOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static CompRegClockEnabledOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static CompRegClockEnabledOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static ::llvm::LogicalResult canonicalize(CompRegClockEnabledOp op, ::mlir::PatternRewriter &rewriter);
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::PropertyRef properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
  static std::optional<size_t> getTargetResultIndex();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
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
};

} // namespace circt::seq
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::seq::CompRegClockEnabledOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::seq::detail::CompRegClockEnabledOpGenericAdaptorBase::Properties)

namespace circt::seq {


//===----------------------------------------------------------------------===//
// ::circt::seq::CompRegOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class CompRegOpGenericAdaptorBase {
public:
  struct Properties {
    using inner_symTy = ::circt::hw::InnerSymAttr;
    inner_symTy inner_sym;

    auto getInnerSym() const {
      auto &propStorage = this->inner_sym;
      return ::llvm::dyn_cast_or_null<::circt::hw::InnerSymAttr>(propStorage);
    }
    void setInnerSym(const ::circt::hw::InnerSymAttr &propValue) {
      this->inner_sym = propValue;
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
        rhs.inner_sym == this->inner_sym &&
        rhs.name == this->name &&
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
  CompRegOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("seq.compreg", odsAttrs.getContext());
  }

  CompRegOpGenericAdaptorBase(CompRegOp op);

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
  ::circt::hw::InnerSymAttr getInnerSymAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::circt::hw::InnerSymAttr>(getProperties().inner_sym);
    return attr;
  }

  ::std::optional<::circt::hw::InnerSymAttr> getInnerSym();
};

} // namespace detail
template <typename RangeT>
class CompRegOpGenericAdaptor : public detail::CompRegOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::CompRegOpGenericAdaptorBase;
  static constexpr int odsIndex_input = 0;
  static constexpr int odsIndex_clk = 1;
  static constexpr int odsIndex_reset = 2;
  static constexpr int odsIndex_resetValue = 3;
  static constexpr int odsIndex_initialValue = 4;
public:
  CompRegOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  CompRegOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : CompRegOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  CompRegOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs) : CompRegOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  CompRegOpGenericAdaptor(RangeT values, const CompRegOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = CompRegOp, typename = std::enable_if_t<std::is_same_v<LateInst, CompRegOp>>>
  CompRegOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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

  ValueT getClk() {
    return (*getODSOperands(1).begin());
  }

  ValueT getReset() {
    auto operands = getODSOperands(2);
    return operands.empty() ? ValueT{} : (*operands.begin());
  }

  ValueT getResetValue() {
    auto operands = getODSOperands(3);
    return operands.empty() ? ValueT{} : (*operands.begin());
  }

  ValueT getInitialValue() {
    auto operands = getODSOperands(4);
    return operands.empty() ? ValueT{} : (*operands.begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class CompRegOpAdaptor : public CompRegOpGenericAdaptor<::mlir::ValueRange> {
public:
  using CompRegOpGenericAdaptor::CompRegOpGenericAdaptor;
  CompRegOpAdaptor(CompRegOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class CompRegOp : public ::mlir::Op<CompRegOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::Type>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<2>::Impl, ::mlir::OpTrait::AttrSizedOperandSegments, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, circt::seq::Clocked::Trait, circt::seq::Resettable::Trait, ::mlir::OpAsmOpInterface::Trait, ::circt::hw::InnerSymbolOpInterface::Trait, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = CompRegOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = CompRegOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_input = 0;
  static constexpr int odsIndex_clk = 1;
  static constexpr int odsIndex_reset = 2;
  static constexpr int odsIndex_resetValue = 3;
  static constexpr int odsIndex_initialValue = 4;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::OpAsmOpInterface::Trait<CompRegOp>::getAsmBlockArgumentNames;
  using ::mlir::OpAsmOpInterface::Trait<CompRegOp>::getAsmBlockNames;
  using ::mlir::OpAsmOpInterface::Trait<CompRegOp>::getDefaultDialect;
  using ::circt::hw::InnerSymbolOpInterface::Trait<CompRegOp>::getInnerNameAttr;
  using ::circt::hw::InnerSymbolOpInterface::Trait<CompRegOp>::getInnerName;
  using ::circt::hw::InnerSymbolOpInterface::Trait<CompRegOp>::setInnerSymbol;
  using ::circt::hw::InnerSymbolOpInterface::Trait<CompRegOp>::setInnerSymbolAttr;
  using ::circt::hw::InnerSymbolOpInterface::Trait<CompRegOp>::getInnerRef;
  using ::circt::hw::InnerSymbolOpInterface::Trait<CompRegOp>::getInnerSymAttr;
  using ::circt::hw::InnerSymbolOpInterface::Trait<CompRegOp>::supportsPerFieldSymbols;
  using ::circt::hw::InnerSymbolOpInterface::Trait<CompRegOp>::getTargetResult;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("inner_sym"), ::llvm::StringRef("name"), ::llvm::StringRef("operandSegmentSizes")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getInnerSymAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getInnerSymAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getNameAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getNameAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getOperandSegmentSizesAttrName() {
   return (*this)->getName().getAttributeNames().back();
  }

  static ::mlir::StringAttr getOperandSegmentSizesAttrName(::mlir::OperationName name) {
   return name.getAttributeNames().back();
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("seq.compreg");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::Type> getInput() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::circt::seq::ClockType> getClk() {
    return ::llvm::cast<::mlir::TypedValue<::circt::seq::ClockType>>(*getODSOperands(1).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getReset() {
    auto operands = getODSOperands(2);
    return operands.empty() ? ::mlir::TypedValue<::mlir::IntegerType>{} : ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*operands.begin());
  }

  ::mlir::TypedValue<::mlir::Type> getResetValue() {
    auto operands = getODSOperands(3);
    return operands.empty() ? ::mlir::TypedValue<::mlir::Type>{} : ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*operands.begin());
  }

  ::mlir::TypedValue<::circt::seq::ImmutableType> getInitialValue() {
    auto operands = getODSOperands(4);
    return operands.empty() ? ::mlir::TypedValue<::circt::seq::ImmutableType>{} : ::llvm::cast<::mlir::TypedValue<::circt::seq::ImmutableType>>(*operands.begin());
  }

  ::mlir::OpOperand &getInputMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getClkMutable() {
    auto range = getODSOperandIndexAndLength(1);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::MutableOperandRange getResetMutable();
  ::mlir::MutableOperandRange getResetValueMutable();
  ::mlir::MutableOperandRange getInitialValueMutable();
  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::Type> getData() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSResults(0).begin());
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
  ::circt::hw::InnerSymAttr getInnerSymAttr() {
    return ::llvm::dyn_cast_or_null<::circt::hw::InnerSymAttr>(getProperties().inner_sym);
  }

  ::std::optional<::circt::hw::InnerSymAttr> getInnerSym();
  void setNameAttr(::mlir::StringAttr attr) {
    getProperties().name = attr;
  }

  void setName(::std::optional<::llvm::StringRef> attrValue);
  void setInnerSymAttr(::circt::hw::InnerSymAttr attr) {
    getProperties().inner_sym = attr;
  }

  ::mlir::Attribute removeNameAttr() {
      auto attr = getProperties().name;
      getProperties().name = {};
      return attr;
  }

  ::mlir::Attribute removeInnerSymAttr() {
      auto attr = getProperties().inner_sym;
      getProperties().inner_sym = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value input, Value clk);
  static CompRegOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value input, Value clk);
  static CompRegOp create(::mlir::ImplicitLocOpBuilder &builder, Value input, Value clk);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value input, Value clk, StringAttrOrRef name);
  static CompRegOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value input, Value clk, StringAttrOrRef name);
  static CompRegOp create(::mlir::ImplicitLocOpBuilder &builder, Value input, Value clk, StringAttrOrRef name);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value input, Value clk, Value reset, Value rstValue, Value initialValue = {});
  static CompRegOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value input, Value clk, Value reset, Value rstValue, Value initialValue = {});
  static CompRegOp create(::mlir::ImplicitLocOpBuilder &builder, Value input, Value clk, Value reset, Value rstValue, Value initialValue = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value input, Value clk, Value reset, Value rstValue, StringAttrOrRef name, Value initialValue = {});
  static CompRegOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value input, Value clk, Value reset, Value rstValue, StringAttrOrRef name, Value initialValue = {});
  static CompRegOp create(::mlir::ImplicitLocOpBuilder &builder, Value input, Value clk, Value reset, Value rstValue, StringAttrOrRef name, Value initialValue = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type data, ::mlir::Value input, ::mlir::Value clk, /*optional*/::mlir::StringAttr name, /*optional*/::mlir::Value reset, /*optional*/::mlir::Value resetValue, /*optional*/::mlir::Value initialValue, /*optional*/::circt::hw::InnerSymAttr inner_sym);
  static CompRegOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type data, ::mlir::Value input, ::mlir::Value clk, /*optional*/::mlir::StringAttr name, /*optional*/::mlir::Value reset, /*optional*/::mlir::Value resetValue, /*optional*/::mlir::Value initialValue, /*optional*/::circt::hw::InnerSymAttr inner_sym);
  static CompRegOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type data, ::mlir::Value input, ::mlir::Value clk, /*optional*/::mlir::StringAttr name, /*optional*/::mlir::Value reset, /*optional*/::mlir::Value resetValue, /*optional*/::mlir::Value initialValue, /*optional*/::circt::hw::InnerSymAttr inner_sym);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value input, ::mlir::Value clk, /*optional*/::mlir::StringAttr name, /*optional*/::mlir::Value reset, /*optional*/::mlir::Value resetValue, /*optional*/::mlir::Value initialValue, /*optional*/::circt::hw::InnerSymAttr inner_sym);
  static CompRegOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value input, ::mlir::Value clk, /*optional*/::mlir::StringAttr name, /*optional*/::mlir::Value reset, /*optional*/::mlir::Value resetValue, /*optional*/::mlir::Value initialValue, /*optional*/::circt::hw::InnerSymAttr inner_sym);
  static CompRegOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value input, ::mlir::Value clk, /*optional*/::mlir::StringAttr name, /*optional*/::mlir::Value reset, /*optional*/::mlir::Value resetValue, /*optional*/::mlir::Value initialValue, /*optional*/::circt::hw::InnerSymAttr inner_sym);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value input, ::mlir::Value clk, /*optional*/::mlir::StringAttr name, /*optional*/::mlir::Value reset, /*optional*/::mlir::Value resetValue, /*optional*/::mlir::Value initialValue, /*optional*/::circt::hw::InnerSymAttr inner_sym);
  static CompRegOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value input, ::mlir::Value clk, /*optional*/::mlir::StringAttr name, /*optional*/::mlir::Value reset, /*optional*/::mlir::Value resetValue, /*optional*/::mlir::Value initialValue, /*optional*/::circt::hw::InnerSymAttr inner_sym);
  static CompRegOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value input, ::mlir::Value clk, /*optional*/::mlir::StringAttr name, /*optional*/::mlir::Value reset, /*optional*/::mlir::Value resetValue, /*optional*/::mlir::Value initialValue, /*optional*/::circt::hw::InnerSymAttr inner_sym);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static CompRegOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static CompRegOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static CompRegOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static CompRegOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static CompRegOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static CompRegOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static CompRegOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static CompRegOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::PropertyRef properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
  static std::optional<size_t> getTargetResultIndex();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
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
};

} // namespace circt::seq
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::seq::CompRegOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::seq::detail::CompRegOpGenericAdaptorBase::Properties)

namespace circt::seq {


//===----------------------------------------------------------------------===//
// ::circt::seq::ConstClockOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ConstClockOpGenericAdaptorBase {
public:
  struct Properties {
    using valueTy = ::circt::seq::ClockConstAttr;
    valueTy value;

    auto getValue() const {
      auto &propStorage = this->value;
      return ::llvm::cast<::circt::seq::ClockConstAttr>(propStorage);
    }
    void setValue(const ::circt::seq::ClockConstAttr &propValue) {
      this->value = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.value == this->value &&
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
  ConstClockOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("seq.const_clock", odsAttrs.getContext());
  }

  ConstClockOpGenericAdaptorBase(ConstClockOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::circt::seq::ClockConstAttr getValueAttr() {
    auto attr = ::llvm::cast<::circt::seq::ClockConstAttr>(getProperties().value);
    return attr;
  }

  circt::seq::ClockConst getValue();
};

} // namespace detail
template <typename RangeT>
class ConstClockOpGenericAdaptor : public detail::ConstClockOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ConstClockOpGenericAdaptorBase;
public:
  ConstClockOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ConstClockOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : ConstClockOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ConstClockOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ConstClockOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ConstClockOpGenericAdaptor(RangeT values, const ConstClockOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ConstClockOp, typename = std::enable_if_t<std::is_same_v<LateInst, ConstClockOp>>>
  ConstClockOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class ConstClockOpAdaptor : public ConstClockOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ConstClockOpGenericAdaptor::ConstClockOpGenericAdaptor;
  ConstClockOpAdaptor(ConstClockOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ConstClockOp : public ::mlir::Op<ConstClockOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::circt::seq::ClockType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::OpTrait::ConstantLike, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ConstClockOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ConstClockOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("value")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getValueAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getValueAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("seq.const_clock");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::circt::seq::ClockType> getResult() {
    return ::llvm::cast<::mlir::TypedValue<::circt::seq::ClockType>>(*getODSResults(0).begin());
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
  ::circt::seq::ClockConstAttr getValueAttr() {
    return ::llvm::cast<::circt::seq::ClockConstAttr>(getProperties().value);
  }

  circt::seq::ClockConst getValue();
  void setValueAttr(::circt::seq::ClockConstAttr attr) {
    getProperties().value = attr;
  }

  void setValue(circt::seq::ClockConst attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::circt::seq::ClockConstAttr value);
  static ConstClockOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::circt::seq::ClockConstAttr value);
  static ConstClockOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::circt::seq::ClockConstAttr value);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::circt::seq::ClockConstAttr value);
  static ConstClockOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::circt::seq::ClockConstAttr value);
  static ConstClockOp create(::mlir::ImplicitLocOpBuilder &builder, ::circt::seq::ClockConstAttr value);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::circt::seq::ClockConstAttr value);
  static ConstClockOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::circt::seq::ClockConstAttr value);
  static ConstClockOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::circt::seq::ClockConstAttr value);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, circt::seq::ClockConst value);
  static ConstClockOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, circt::seq::ClockConst value);
  static ConstClockOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, circt::seq::ClockConst value);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, circt::seq::ClockConst value);
  static ConstClockOp create(::mlir::OpBuilder &builder, ::mlir::Location location, circt::seq::ClockConst value);
  static ConstClockOp create(::mlir::ImplicitLocOpBuilder &builder, circt::seq::ClockConst value);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, circt::seq::ClockConst value);
  static ConstClockOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, circt::seq::ClockConst value);
  static ConstClockOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, circt::seq::ClockConst value);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ConstClockOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ConstClockOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ConstClockOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ConstClockOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ConstClockOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ConstClockOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ConstClockOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ConstClockOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::mlir::OpFoldResult fold(FoldAdaptor adaptor);
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::PropertyRef properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
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
};

} // namespace circt::seq
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::seq::ConstClockOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::seq::detail::ConstClockOpGenericAdaptorBase::Properties)

namespace circt::seq {


//===----------------------------------------------------------------------===//
// ::circt::seq::FIFOOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class FIFOOpGenericAdaptorBase {
public:
  struct Properties {
    using almostEmptyThresholdTy = ::mlir::IntegerAttr;
    almostEmptyThresholdTy almostEmptyThreshold;

    auto getAlmostEmptyThreshold() const {
      auto &propStorage = this->almostEmptyThreshold;
      return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(propStorage);
    }
    void setAlmostEmptyThreshold(const ::mlir::IntegerAttr &propValue) {
      this->almostEmptyThreshold = propValue;
    }
    using almostFullThresholdTy = ::mlir::IntegerAttr;
    almostFullThresholdTy almostFullThreshold;

    auto getAlmostFullThreshold() const {
      auto &propStorage = this->almostFullThreshold;
      return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(propStorage);
    }
    void setAlmostFullThreshold(const ::mlir::IntegerAttr &propValue) {
      this->almostFullThreshold = propValue;
    }
    using depthTy = ::mlir::IntegerAttr;
    depthTy depth;

    auto getDepth() const {
      auto &propStorage = this->depth;
      return ::llvm::cast<::mlir::IntegerAttr>(propStorage);
    }
    void setDepth(const ::mlir::IntegerAttr &propValue) {
      this->depth = propValue;
    }
    using rdLatencyTy = ::mlir::IntegerAttr;
    rdLatencyTy rdLatency;

    auto getRdLatency() const {
      auto &propStorage = this->rdLatency;
      return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(propStorage);
    }
    void setRdLatency(const ::mlir::IntegerAttr &propValue) {
      this->rdLatency = propValue;
    }
    using resultSegmentSizesTy = std::array<int32_t, 5>;
    resultSegmentSizesTy resultSegmentSizes;
    ::llvm::ArrayRef<int32_t> getResultSegmentSizes() const {
      auto &propStorage = this->resultSegmentSizes;
      return propStorage;
    }
    void setResultSegmentSizes(::llvm::ArrayRef<int32_t> propValue) {
      auto &propStorage = this->resultSegmentSizes;
      ::llvm::copy(propValue, propStorage.begin());
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.almostEmptyThreshold == this->almostEmptyThreshold &&
        rhs.almostFullThreshold == this->almostFullThreshold &&
        rhs.depth == this->depth &&
        rhs.rdLatency == this->rdLatency &&
        rhs.resultSegmentSizes == this->resultSegmentSizes &&
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
  FIFOOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("seq.fifo", odsAttrs.getContext());
  }

  FIFOOpGenericAdaptorBase(FIFOOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::IntegerAttr getDepthAttr() {
    auto attr = ::llvm::cast<::mlir::IntegerAttr>(getProperties().depth);
    return attr;
  }

  uint64_t getDepth();
  ::mlir::IntegerAttr getRdLatencyAttr();
  uint64_t getRdLatency();
  ::mlir::IntegerAttr getAlmostFullThresholdAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(getProperties().almostFullThreshold);
    return attr;
  }

  ::std::optional<uint64_t> getAlmostFullThreshold();
  ::mlir::IntegerAttr getAlmostEmptyThresholdAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(getProperties().almostEmptyThreshold);
    return attr;
  }

  ::std::optional<uint64_t> getAlmostEmptyThreshold();
};

} // namespace detail
template <typename RangeT>
class FIFOOpGenericAdaptor : public detail::FIFOOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::FIFOOpGenericAdaptorBase;
  static constexpr int odsIndex_input = 0;
  static constexpr int odsIndex_rdEn = 1;
  static constexpr int odsIndex_wrEn = 2;
  static constexpr int odsIndex_clk = 3;
  static constexpr int odsIndex_rst = 4;
public:
  FIFOOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  FIFOOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : FIFOOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  FIFOOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : FIFOOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  FIFOOpGenericAdaptor(RangeT values, const FIFOOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = FIFOOp, typename = std::enable_if_t<std::is_same_v<LateInst, FIFOOp>>>
  FIFOOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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

  ValueT getRdEn() {
    return (*getODSOperands(1).begin());
  }

  ValueT getWrEn() {
    return (*getODSOperands(2).begin());
  }

  ValueT getClk() {
    return (*getODSOperands(3).begin());
  }

  ValueT getRst() {
    return (*getODSOperands(4).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class FIFOOpAdaptor : public FIFOOpGenericAdaptor<::mlir::ValueRange> {
public:
  using FIFOOpGenericAdaptor::FIFOOpGenericAdaptor;
  FIFOOpAdaptor(FIFOOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class FIFOOp : public ::mlir::Op<FIFOOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::AtLeastNResults<3>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::NOperands<5>::Impl, ::mlir::OpTrait::AttrSizedResultSegments, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::OpAsmOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = FIFOOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = FIFOOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_input = 0;
  static constexpr int odsIndex_rdEn = 1;
  static constexpr int odsIndex_wrEn = 2;
  static constexpr int odsIndex_clk = 3;
  static constexpr int odsIndex_rst = 4;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::OpAsmOpInterface::Trait<FIFOOp>::getAsmBlockArgumentNames;
  using ::mlir::OpAsmOpInterface::Trait<FIFOOp>::getAsmBlockNames;
  using ::mlir::OpAsmOpInterface::Trait<FIFOOp>::getDefaultDialect;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("almostEmptyThreshold"), ::llvm::StringRef("almostFullThreshold"), ::llvm::StringRef("depth"), ::llvm::StringRef("rdLatency")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getAlmostEmptyThresholdAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getAlmostEmptyThresholdAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getAlmostFullThresholdAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getAlmostFullThresholdAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getDepthAttrName() {
    return getAttributeNameForIndex(2);
  }

  static ::mlir::StringAttr getDepthAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 2);
  }

  ::mlir::StringAttr getRdLatencyAttrName() {
    return getAttributeNameForIndex(3);
  }

  static ::mlir::StringAttr getRdLatencyAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 3);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("seq.fifo");
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

  ::mlir::TypedValue<::mlir::IntegerType> getRdEn() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSOperands(1).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getWrEn() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSOperands(2).begin());
  }

  ::mlir::TypedValue<::circt::seq::ClockType> getClk() {
    return ::llvm::cast<::mlir::TypedValue<::circt::seq::ClockType>>(*getODSOperands(3).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getRst() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSOperands(4).begin());
  }

  ::mlir::OpOperand &getInputMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getRdEnMutable() {
    auto range = getODSOperandIndexAndLength(1);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getWrEnMutable() {
    auto range = getODSOperandIndexAndLength(2);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getClkMutable() {
    auto range = getODSOperandIndexAndLength(3);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getRstMutable() {
    auto range = getODSOperandIndexAndLength(4);
    return getOperation()->getOpOperand(range.first);
  }

  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index);
  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::Type> getOutput() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSResults(0).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getFull() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSResults(1).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getEmpty() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSResults(2).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getAlmostFull() {
    auto results = getODSResults(3);
    return results.empty() ? ::mlir::TypedValue<::mlir::IntegerType>() : ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*results.begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getAlmostEmpty() {
    auto results = getODSResults(4);
    return results.empty() ? ::mlir::TypedValue<::mlir::IntegerType>() : ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*results.begin());
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
  ::mlir::IntegerAttr getDepthAttr() {
    return ::llvm::cast<::mlir::IntegerAttr>(getProperties().depth);
  }

  uint64_t getDepth();
  ::mlir::IntegerAttr getRdLatencyAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(getProperties().rdLatency);
  }

  uint64_t getRdLatency();
  ::mlir::IntegerAttr getAlmostFullThresholdAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(getProperties().almostFullThreshold);
  }

  ::std::optional<uint64_t> getAlmostFullThreshold();
  ::mlir::IntegerAttr getAlmostEmptyThresholdAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(getProperties().almostEmptyThreshold);
  }

  ::std::optional<uint64_t> getAlmostEmptyThreshold();
  void setDepthAttr(::mlir::IntegerAttr attr) {
    getProperties().depth = attr;
  }

  void setDepth(uint64_t attrValue);
  void setRdLatencyAttr(::mlir::IntegerAttr attr) {
    getProperties().rdLatency = attr;
  }

  void setRdLatency(::std::optional<uint64_t> attrValue);
  void setAlmostFullThresholdAttr(::mlir::IntegerAttr attr) {
    getProperties().almostFullThreshold = attr;
  }

  void setAlmostFullThreshold(::std::optional<uint64_t> attrValue);
  void setAlmostEmptyThresholdAttr(::mlir::IntegerAttr attr) {
    getProperties().almostEmptyThreshold = attr;
  }

  void setAlmostEmptyThreshold(::std::optional<uint64_t> attrValue);
  ::mlir::Attribute removeRdLatencyAttr() {
      auto attr = getProperties().rdLatency;
      getProperties().rdLatency = {};
      return attr;
  }

  ::mlir::Attribute removeAlmostFullThresholdAttr() {
      auto attr = getProperties().almostFullThreshold;
      getProperties().almostFullThreshold = {};
      return attr;
  }

  ::mlir::Attribute removeAlmostEmptyThresholdAttr() {
      auto attr = getProperties().almostEmptyThreshold;
      getProperties().almostEmptyThreshold = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type output, ::mlir::Type full, ::mlir::Type empty, /*optional*/::mlir::Type almostFull, /*optional*/::mlir::Type almostEmpty, ::mlir::Value input, ::mlir::Value rdEn, ::mlir::Value wrEn, ::mlir::Value clk, ::mlir::Value rst, ::mlir::IntegerAttr depth, /*optional*/::mlir::IntegerAttr rdLatency, /*optional*/::mlir::IntegerAttr almostFullThreshold, /*optional*/::mlir::IntegerAttr almostEmptyThreshold);
  static FIFOOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type output, ::mlir::Type full, ::mlir::Type empty, /*optional*/::mlir::Type almostFull, /*optional*/::mlir::Type almostEmpty, ::mlir::Value input, ::mlir::Value rdEn, ::mlir::Value wrEn, ::mlir::Value clk, ::mlir::Value rst, ::mlir::IntegerAttr depth, /*optional*/::mlir::IntegerAttr rdLatency, /*optional*/::mlir::IntegerAttr almostFullThreshold, /*optional*/::mlir::IntegerAttr almostEmptyThreshold);
  static FIFOOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type output, ::mlir::Type full, ::mlir::Type empty, /*optional*/::mlir::Type almostFull, /*optional*/::mlir::Type almostEmpty, ::mlir::Value input, ::mlir::Value rdEn, ::mlir::Value wrEn, ::mlir::Value clk, ::mlir::Value rst, ::mlir::IntegerAttr depth, /*optional*/::mlir::IntegerAttr rdLatency, /*optional*/::mlir::IntegerAttr almostFullThreshold, /*optional*/::mlir::IntegerAttr almostEmptyThreshold);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value input, ::mlir::Value rdEn, ::mlir::Value wrEn, ::mlir::Value clk, ::mlir::Value rst, ::mlir::IntegerAttr depth, /*optional*/::mlir::IntegerAttr rdLatency, /*optional*/::mlir::IntegerAttr almostFullThreshold, /*optional*/::mlir::IntegerAttr almostEmptyThreshold);
  static FIFOOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value input, ::mlir::Value rdEn, ::mlir::Value wrEn, ::mlir::Value clk, ::mlir::Value rst, ::mlir::IntegerAttr depth, /*optional*/::mlir::IntegerAttr rdLatency, /*optional*/::mlir::IntegerAttr almostFullThreshold, /*optional*/::mlir::IntegerAttr almostEmptyThreshold);
  static FIFOOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value input, ::mlir::Value rdEn, ::mlir::Value wrEn, ::mlir::Value clk, ::mlir::Value rst, ::mlir::IntegerAttr depth, /*optional*/::mlir::IntegerAttr rdLatency, /*optional*/::mlir::IntegerAttr almostFullThreshold, /*optional*/::mlir::IntegerAttr almostEmptyThreshold);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type output, ::mlir::Type full, ::mlir::Type empty, /*optional*/::mlir::Type almostFull, /*optional*/::mlir::Type almostEmpty, ::mlir::Value input, ::mlir::Value rdEn, ::mlir::Value wrEn, ::mlir::Value clk, ::mlir::Value rst, uint64_t depth, /*optional*/uint64_t rdLatency, /*optional*/::mlir::IntegerAttr almostFullThreshold, /*optional*/::mlir::IntegerAttr almostEmptyThreshold);
  static FIFOOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type output, ::mlir::Type full, ::mlir::Type empty, /*optional*/::mlir::Type almostFull, /*optional*/::mlir::Type almostEmpty, ::mlir::Value input, ::mlir::Value rdEn, ::mlir::Value wrEn, ::mlir::Value clk, ::mlir::Value rst, uint64_t depth, /*optional*/uint64_t rdLatency, /*optional*/::mlir::IntegerAttr almostFullThreshold, /*optional*/::mlir::IntegerAttr almostEmptyThreshold);
  static FIFOOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type output, ::mlir::Type full, ::mlir::Type empty, /*optional*/::mlir::Type almostFull, /*optional*/::mlir::Type almostEmpty, ::mlir::Value input, ::mlir::Value rdEn, ::mlir::Value wrEn, ::mlir::Value clk, ::mlir::Value rst, uint64_t depth, /*optional*/uint64_t rdLatency, /*optional*/::mlir::IntegerAttr almostFullThreshold, /*optional*/::mlir::IntegerAttr almostEmptyThreshold);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value input, ::mlir::Value rdEn, ::mlir::Value wrEn, ::mlir::Value clk, ::mlir::Value rst, uint64_t depth, /*optional*/uint64_t rdLatency, /*optional*/::mlir::IntegerAttr almostFullThreshold, /*optional*/::mlir::IntegerAttr almostEmptyThreshold);
  static FIFOOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value input, ::mlir::Value rdEn, ::mlir::Value wrEn, ::mlir::Value clk, ::mlir::Value rst, uint64_t depth, /*optional*/uint64_t rdLatency, /*optional*/::mlir::IntegerAttr almostFullThreshold, /*optional*/::mlir::IntegerAttr almostEmptyThreshold);
  static FIFOOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value input, ::mlir::Value rdEn, ::mlir::Value wrEn, ::mlir::Value clk, ::mlir::Value rst, uint64_t depth, /*optional*/uint64_t rdLatency, /*optional*/::mlir::IntegerAttr almostFullThreshold, /*optional*/::mlir::IntegerAttr almostEmptyThreshold);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static FIFOOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static FIFOOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static FIFOOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static FIFOOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
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
};

} // namespace circt::seq
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::seq::FIFOOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::seq::detail::FIFOOpGenericAdaptorBase::Properties)

namespace circt::seq {


//===----------------------------------------------------------------------===//
// ::circt::seq::FirMemOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class FirMemOpGenericAdaptorBase {
public:
  struct Properties {
    using initTy = ::circt::seq::FirMemInitAttr;
    initTy init;

    auto getInit() const {
      auto &propStorage = this->init;
      return ::llvm::dyn_cast_or_null<::circt::seq::FirMemInitAttr>(propStorage);
    }
    void setInit(const ::circt::seq::FirMemInitAttr &propValue) {
      this->init = propValue;
    }
    using inner_symTy = ::circt::hw::InnerSymAttr;
    inner_symTy inner_sym;

    auto getInnerSym() const {
      auto &propStorage = this->inner_sym;
      return ::llvm::dyn_cast_or_null<::circt::hw::InnerSymAttr>(propStorage);
    }
    void setInnerSym(const ::circt::hw::InnerSymAttr &propValue) {
      this->inner_sym = propValue;
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
    using output_fileTy = ::mlir::Attribute;
    output_fileTy output_file;

    auto getOutputFile() const {
      auto &propStorage = this->output_file;
      return ::llvm::dyn_cast_or_null<::mlir::Attribute>(propStorage);
    }
    void setOutputFile(const ::mlir::Attribute &propValue) {
      this->output_file = propValue;
    }
    using prefixTy = ::mlir::StringAttr;
    prefixTy prefix;

    auto getPrefix() const {
      auto &propStorage = this->prefix;
      return ::llvm::dyn_cast_or_null<::mlir::StringAttr>(propStorage);
    }
    void setPrefix(const ::mlir::StringAttr &propValue) {
      this->prefix = propValue;
    }
    using readLatencyTy = ::mlir::IntegerAttr;
    readLatencyTy readLatency;

    auto getReadLatency() const {
      auto &propStorage = this->readLatency;
      return ::llvm::cast<::mlir::IntegerAttr>(propStorage);
    }
    void setReadLatency(const ::mlir::IntegerAttr &propValue) {
      this->readLatency = propValue;
    }
    using ruwTy = circt::seq::RUWAttr;
    ruwTy ruw;

    auto getRuw() const {
      auto &propStorage = this->ruw;
      return ::llvm::cast<circt::seq::RUWAttr>(propStorage);
    }
    void setRuw(const circt::seq::RUWAttr &propValue) {
      this->ruw = propValue;
    }
    using writeLatencyTy = ::mlir::IntegerAttr;
    writeLatencyTy writeLatency;

    auto getWriteLatency() const {
      auto &propStorage = this->writeLatency;
      return ::llvm::cast<::mlir::IntegerAttr>(propStorage);
    }
    void setWriteLatency(const ::mlir::IntegerAttr &propValue) {
      this->writeLatency = propValue;
    }
    using wuwTy = circt::seq::WUWAttr;
    wuwTy wuw;

    auto getWuw() const {
      auto &propStorage = this->wuw;
      return ::llvm::cast<circt::seq::WUWAttr>(propStorage);
    }
    void setWuw(const circt::seq::WUWAttr &propValue) {
      this->wuw = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.init == this->init &&
        rhs.inner_sym == this->inner_sym &&
        rhs.name == this->name &&
        rhs.output_file == this->output_file &&
        rhs.prefix == this->prefix &&
        rhs.readLatency == this->readLatency &&
        rhs.ruw == this->ruw &&
        rhs.writeLatency == this->writeLatency &&
        rhs.wuw == this->wuw &&
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
  FirMemOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("seq.firmem", odsAttrs.getContext());
  }

  FirMemOpGenericAdaptorBase(FirMemOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::IntegerAttr getReadLatencyAttr() {
    auto attr = ::llvm::cast<::mlir::IntegerAttr>(getProperties().readLatency);
    return attr;
  }

  uint32_t getReadLatency();
  ::mlir::IntegerAttr getWriteLatencyAttr() {
    auto attr = ::llvm::cast<::mlir::IntegerAttr>(getProperties().writeLatency);
    return attr;
  }

  uint32_t getWriteLatency();
  circt::seq::RUWAttr getRuwAttr() {
    auto attr = ::llvm::cast<circt::seq::RUWAttr>(getProperties().ruw);
    return attr;
  }

  circt::seq::RUW getRuw();
  circt::seq::WUWAttr getWuwAttr() {
    auto attr = ::llvm::cast<circt::seq::WUWAttr>(getProperties().wuw);
    return attr;
  }

  circt::seq::WUW getWuw();
  ::mlir::StringAttr getNameAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::StringAttr>(getProperties().name);
    return attr;
  }

  ::std::optional< ::llvm::StringRef > getName();
  ::circt::hw::InnerSymAttr getInnerSymAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::circt::hw::InnerSymAttr>(getProperties().inner_sym);
    return attr;
  }

  ::std::optional<::circt::hw::InnerSymAttr> getInnerSym();
  ::circt::seq::FirMemInitAttr getInitAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::circt::seq::FirMemInitAttr>(getProperties().init);
    return attr;
  }

  ::std::optional<::circt::seq::FirMemInitAttr> getInit();
  ::mlir::StringAttr getPrefixAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::StringAttr>(getProperties().prefix);
    return attr;
  }

  ::std::optional< ::llvm::StringRef > getPrefix();
  ::mlir::Attribute getOutputFileAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::Attribute>(getProperties().output_file);
    return attr;
  }

  ::std::optional<::mlir::Attribute> getOutputFile();
};

} // namespace detail
template <typename RangeT>
class FirMemOpGenericAdaptor : public detail::FirMemOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::FirMemOpGenericAdaptorBase;
public:
  FirMemOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  FirMemOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : FirMemOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  FirMemOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : FirMemOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  FirMemOpGenericAdaptor(RangeT values, const FirMemOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = FirMemOp, typename = std::enable_if_t<std::is_same_v<LateInst, FirMemOp>>>
  FirMemOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class FirMemOpAdaptor : public FirMemOpGenericAdaptor<::mlir::ValueRange> {
public:
  using FirMemOpGenericAdaptor::FirMemOpGenericAdaptor;
  FirMemOpAdaptor(FirMemOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class FirMemOp : public ::mlir::Op<FirMemOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::circt::seq::FirMemType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::OpAsmOpInterface::Trait, ::circt::hw::InnerSymbolOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = FirMemOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = FirMemOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::OpAsmOpInterface::Trait<FirMemOp>::getAsmBlockArgumentNames;
  using ::mlir::OpAsmOpInterface::Trait<FirMemOp>::getAsmBlockNames;
  using ::mlir::OpAsmOpInterface::Trait<FirMemOp>::getDefaultDialect;
  using ::circt::hw::InnerSymbolOpInterface::Trait<FirMemOp>::getInnerNameAttr;
  using ::circt::hw::InnerSymbolOpInterface::Trait<FirMemOp>::getInnerName;
  using ::circt::hw::InnerSymbolOpInterface::Trait<FirMemOp>::setInnerSymbol;
  using ::circt::hw::InnerSymbolOpInterface::Trait<FirMemOp>::setInnerSymbolAttr;
  using ::circt::hw::InnerSymbolOpInterface::Trait<FirMemOp>::getInnerRef;
  using ::circt::hw::InnerSymbolOpInterface::Trait<FirMemOp>::getInnerSymAttr;
  using ::circt::hw::InnerSymbolOpInterface::Trait<FirMemOp>::supportsPerFieldSymbols;
  using ::circt::hw::InnerSymbolOpInterface::Trait<FirMemOp>::getTargetResult;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("init"), ::llvm::StringRef("inner_sym"), ::llvm::StringRef("name"), ::llvm::StringRef("output_file"), ::llvm::StringRef("prefix"), ::llvm::StringRef("readLatency"), ::llvm::StringRef("ruw"), ::llvm::StringRef("writeLatency"), ::llvm::StringRef("wuw")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getInitAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getInitAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getInnerSymAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getInnerSymAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getNameAttrName() {
    return getAttributeNameForIndex(2);
  }

  static ::mlir::StringAttr getNameAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 2);
  }

  ::mlir::StringAttr getOutputFileAttrName() {
    return getAttributeNameForIndex(3);
  }

  static ::mlir::StringAttr getOutputFileAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 3);
  }

  ::mlir::StringAttr getPrefixAttrName() {
    return getAttributeNameForIndex(4);
  }

  static ::mlir::StringAttr getPrefixAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 4);
  }

  ::mlir::StringAttr getReadLatencyAttrName() {
    return getAttributeNameForIndex(5);
  }

  static ::mlir::StringAttr getReadLatencyAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 5);
  }

  ::mlir::StringAttr getRuwAttrName() {
    return getAttributeNameForIndex(6);
  }

  static ::mlir::StringAttr getRuwAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 6);
  }

  ::mlir::StringAttr getWriteLatencyAttrName() {
    return getAttributeNameForIndex(7);
  }

  static ::mlir::StringAttr getWriteLatencyAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 7);
  }

  ::mlir::StringAttr getWuwAttrName() {
    return getAttributeNameForIndex(8);
  }

  static ::mlir::StringAttr getWuwAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 8);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("seq.firmem");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::circt::seq::FirMemType> getMemory() {
    return ::llvm::cast<::mlir::TypedValue<::circt::seq::FirMemType>>(*getODSResults(0).begin());
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
  ::mlir::IntegerAttr getReadLatencyAttr() {
    return ::llvm::cast<::mlir::IntegerAttr>(getProperties().readLatency);
  }

  uint32_t getReadLatency();
  ::mlir::IntegerAttr getWriteLatencyAttr() {
    return ::llvm::cast<::mlir::IntegerAttr>(getProperties().writeLatency);
  }

  uint32_t getWriteLatency();
  circt::seq::RUWAttr getRuwAttr() {
    return ::llvm::cast<circt::seq::RUWAttr>(getProperties().ruw);
  }

  circt::seq::RUW getRuw();
  circt::seq::WUWAttr getWuwAttr() {
    return ::llvm::cast<circt::seq::WUWAttr>(getProperties().wuw);
  }

  circt::seq::WUW getWuw();
  ::mlir::StringAttr getNameAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::StringAttr>(getProperties().name);
  }

  ::std::optional< ::llvm::StringRef > getName();
  ::circt::hw::InnerSymAttr getInnerSymAttr() {
    return ::llvm::dyn_cast_or_null<::circt::hw::InnerSymAttr>(getProperties().inner_sym);
  }

  ::std::optional<::circt::hw::InnerSymAttr> getInnerSym();
  ::circt::seq::FirMemInitAttr getInitAttr() {
    return ::llvm::dyn_cast_or_null<::circt::seq::FirMemInitAttr>(getProperties().init);
  }

  ::std::optional<::circt::seq::FirMemInitAttr> getInit();
  ::mlir::StringAttr getPrefixAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::StringAttr>(getProperties().prefix);
  }

  ::std::optional< ::llvm::StringRef > getPrefix();
  ::mlir::Attribute getOutputFileAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::Attribute>(getProperties().output_file);
  }

  ::std::optional<::mlir::Attribute> getOutputFile();
  void setReadLatencyAttr(::mlir::IntegerAttr attr) {
    getProperties().readLatency = attr;
  }

  void setReadLatency(uint32_t attrValue);
  void setWriteLatencyAttr(::mlir::IntegerAttr attr) {
    getProperties().writeLatency = attr;
  }

  void setWriteLatency(uint32_t attrValue);
  void setRuwAttr(circt::seq::RUWAttr attr) {
    getProperties().ruw = attr;
  }

  void setRuw(circt::seq::RUW attrValue);
  void setWuwAttr(circt::seq::WUWAttr attr) {
    getProperties().wuw = attr;
  }

  void setWuw(circt::seq::WUW attrValue);
  void setNameAttr(::mlir::StringAttr attr) {
    getProperties().name = attr;
  }

  void setName(::std::optional<::llvm::StringRef> attrValue);
  void setInnerSymAttr(::circt::hw::InnerSymAttr attr) {
    getProperties().inner_sym = attr;
  }

  void setInitAttr(::circt::seq::FirMemInitAttr attr) {
    getProperties().init = attr;
  }

  void setPrefixAttr(::mlir::StringAttr attr) {
    getProperties().prefix = attr;
  }

  void setPrefix(::std::optional<::llvm::StringRef> attrValue);
  void setOutputFileAttr(::mlir::Attribute attr) {
    getProperties().output_file = attr;
  }

  ::mlir::Attribute removeNameAttr() {
      auto attr = getProperties().name;
      getProperties().name = {};
      return attr;
  }

  ::mlir::Attribute removeInnerSymAttr() {
      auto attr = getProperties().inner_sym;
      getProperties().inner_sym = {};
      return attr;
  }

  ::mlir::Attribute removeInitAttr() {
      auto attr = getProperties().init;
      getProperties().init = {};
      return attr;
  }

  ::mlir::Attribute removePrefixAttr() {
      auto attr = getProperties().prefix;
      getProperties().prefix = {};
      return attr;
  }

  ::mlir::Attribute removeOutputFileAttr() {
      auto attr = getProperties().output_file;
      getProperties().output_file = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type memory, ::mlir::IntegerAttr readLatency, ::mlir::IntegerAttr writeLatency, circt::seq::RUWAttr ruw, circt::seq::WUWAttr wuw, /*optional*/::mlir::StringAttr name, /*optional*/::circt::hw::InnerSymAttr inner_sym, /*optional*/::circt::seq::FirMemInitAttr init, /*optional*/::mlir::StringAttr prefix, /*optional*/::mlir::Attribute output_file);
  static FirMemOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type memory, ::mlir::IntegerAttr readLatency, ::mlir::IntegerAttr writeLatency, circt::seq::RUWAttr ruw, circt::seq::WUWAttr wuw, /*optional*/::mlir::StringAttr name, /*optional*/::circt::hw::InnerSymAttr inner_sym, /*optional*/::circt::seq::FirMemInitAttr init, /*optional*/::mlir::StringAttr prefix, /*optional*/::mlir::Attribute output_file);
  static FirMemOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type memory, ::mlir::IntegerAttr readLatency, ::mlir::IntegerAttr writeLatency, circt::seq::RUWAttr ruw, circt::seq::WUWAttr wuw, /*optional*/::mlir::StringAttr name, /*optional*/::circt::hw::InnerSymAttr inner_sym, /*optional*/::circt::seq::FirMemInitAttr init, /*optional*/::mlir::StringAttr prefix, /*optional*/::mlir::Attribute output_file);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::IntegerAttr readLatency, ::mlir::IntegerAttr writeLatency, circt::seq::RUWAttr ruw, circt::seq::WUWAttr wuw, /*optional*/::mlir::StringAttr name, /*optional*/::circt::hw::InnerSymAttr inner_sym, /*optional*/::circt::seq::FirMemInitAttr init, /*optional*/::mlir::StringAttr prefix, /*optional*/::mlir::Attribute output_file);
  static FirMemOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::IntegerAttr readLatency, ::mlir::IntegerAttr writeLatency, circt::seq::RUWAttr ruw, circt::seq::WUWAttr wuw, /*optional*/::mlir::StringAttr name, /*optional*/::circt::hw::InnerSymAttr inner_sym, /*optional*/::circt::seq::FirMemInitAttr init, /*optional*/::mlir::StringAttr prefix, /*optional*/::mlir::Attribute output_file);
  static FirMemOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::IntegerAttr readLatency, ::mlir::IntegerAttr writeLatency, circt::seq::RUWAttr ruw, circt::seq::WUWAttr wuw, /*optional*/::mlir::StringAttr name, /*optional*/::circt::hw::InnerSymAttr inner_sym, /*optional*/::circt::seq::FirMemInitAttr init, /*optional*/::mlir::StringAttr prefix, /*optional*/::mlir::Attribute output_file);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type memory, uint32_t readLatency, uint32_t writeLatency, circt::seq::RUW ruw, circt::seq::WUW wuw, /*optional*/::mlir::StringAttr name, /*optional*/::circt::hw::InnerSymAttr inner_sym, /*optional*/::circt::seq::FirMemInitAttr init, /*optional*/::mlir::StringAttr prefix, /*optional*/::mlir::Attribute output_file);
  static FirMemOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type memory, uint32_t readLatency, uint32_t writeLatency, circt::seq::RUW ruw, circt::seq::WUW wuw, /*optional*/::mlir::StringAttr name, /*optional*/::circt::hw::InnerSymAttr inner_sym, /*optional*/::circt::seq::FirMemInitAttr init, /*optional*/::mlir::StringAttr prefix, /*optional*/::mlir::Attribute output_file);
  static FirMemOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type memory, uint32_t readLatency, uint32_t writeLatency, circt::seq::RUW ruw, circt::seq::WUW wuw, /*optional*/::mlir::StringAttr name, /*optional*/::circt::hw::InnerSymAttr inner_sym, /*optional*/::circt::seq::FirMemInitAttr init, /*optional*/::mlir::StringAttr prefix, /*optional*/::mlir::Attribute output_file);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, uint32_t readLatency, uint32_t writeLatency, circt::seq::RUW ruw, circt::seq::WUW wuw, /*optional*/::mlir::StringAttr name, /*optional*/::circt::hw::InnerSymAttr inner_sym, /*optional*/::circt::seq::FirMemInitAttr init, /*optional*/::mlir::StringAttr prefix, /*optional*/::mlir::Attribute output_file);
  static FirMemOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, uint32_t readLatency, uint32_t writeLatency, circt::seq::RUW ruw, circt::seq::WUW wuw, /*optional*/::mlir::StringAttr name, /*optional*/::circt::hw::InnerSymAttr inner_sym, /*optional*/::circt::seq::FirMemInitAttr init, /*optional*/::mlir::StringAttr prefix, /*optional*/::mlir::Attribute output_file);
  static FirMemOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, uint32_t readLatency, uint32_t writeLatency, circt::seq::RUW ruw, circt::seq::WUW wuw, /*optional*/::mlir::StringAttr name, /*optional*/::circt::hw::InnerSymAttr inner_sym, /*optional*/::circt::seq::FirMemInitAttr init, /*optional*/::mlir::StringAttr prefix, /*optional*/::mlir::Attribute output_file);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static FirMemOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static FirMemOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static FirMemOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static FirMemOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::llvm::LogicalResult canonicalize(FirMemOp op, ::mlir::PatternRewriter &rewriter);
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
  static std::optional<size_t> getTargetResultIndex();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
private:
  ::mlir::StringAttr getAttributeNameForIndex(unsigned index) {
    return getAttributeNameForIndex((*this)->getName(), index);
  }

  static ::mlir::StringAttr getAttributeNameForIndex(::mlir::OperationName name, unsigned index) {
    assert(index < 9 && "invalid attribute index");
    assert(name.getStringRef() == getOperationName() && "invalid operation name");
    assert(name.isRegistered() && "Operation isn't registered, missing a "
          "dependent dialect loading?");
    return name.getAttributeNames()[index];
  }

public:
};

} // namespace circt::seq
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::seq::FirMemOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::seq::detail::FirMemOpGenericAdaptorBase::Properties)

namespace circt::seq {


//===----------------------------------------------------------------------===//
// ::circt::seq::FirMemReadOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class FirMemReadOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  FirMemReadOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("seq.firmem.read_port", odsAttrs.getContext());
  }

  FirMemReadOpGenericAdaptorBase(FirMemReadOp op);

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
class FirMemReadOpGenericAdaptor : public detail::FirMemReadOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::FirMemReadOpGenericAdaptorBase;
  static constexpr int odsIndex_memory = 0;
  static constexpr int odsIndex_address = 1;
  static constexpr int odsIndex_clk = 2;
  static constexpr int odsIndex_enable = 3;
public:
  FirMemReadOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  FirMemReadOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : FirMemReadOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  FirMemReadOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : FirMemReadOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  FirMemReadOpGenericAdaptor(RangeT values, const FirMemReadOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = FirMemReadOp, typename = std::enable_if_t<std::is_same_v<LateInst, FirMemReadOp>>>
  FirMemReadOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getMemory() {
    return (*getODSOperands(0).begin());
  }

  ValueT getAddress() {
    return (*getODSOperands(1).begin());
  }

  ValueT getClk() {
    return (*getODSOperands(2).begin());
  }

  ValueT getEnable() {
    auto operands = getODSOperands(3);
    return operands.empty() ? ValueT{} : (*operands.begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class FirMemReadOpAdaptor : public FirMemReadOpGenericAdaptor<::mlir::ValueRange> {
public:
  using FirMemReadOpGenericAdaptor::FirMemReadOpGenericAdaptor;
  FirMemReadOpAdaptor(FirMemReadOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class FirMemReadOp : public ::mlir::Op<FirMemReadOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::IntegerType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<3>::Impl, ::mlir::OpTrait::OpInvariants, circt::seq::Clocked::Trait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = FirMemReadOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = FirMemReadOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_memory = 0;
  static constexpr int odsIndex_address = 1;
  static constexpr int odsIndex_clk = 2;
  static constexpr int odsIndex_enable = 3;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("seq.firmem.read_port");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::circt::seq::FirMemType> getMemory() {
    return ::llvm::cast<::mlir::TypedValue<::circt::seq::FirMemType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getAddress() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSOperands(1).begin());
  }

  ::mlir::TypedValue<::circt::seq::ClockType> getClk() {
    return ::llvm::cast<::mlir::TypedValue<::circt::seq::ClockType>>(*getODSOperands(2).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getEnable() {
    auto operands = getODSOperands(3);
    return operands.empty() ? ::mlir::TypedValue<::mlir::IntegerType>{} : ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*operands.begin());
  }

  ::mlir::OpOperand &getMemoryMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getAddressMutable() {
    auto range = getODSOperandIndexAndLength(1);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getClkMutable() {
    auto range = getODSOperandIndexAndLength(2);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::MutableOperandRange getEnableMutable();
  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::IntegerType> getData() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSResults(0).begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type data, ::mlir::Value memory, ::mlir::Value address, ::mlir::Value clk, /*optional*/::mlir::Value enable);
  static FirMemReadOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type data, ::mlir::Value memory, ::mlir::Value address, ::mlir::Value clk, /*optional*/::mlir::Value enable);
  static FirMemReadOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type data, ::mlir::Value memory, ::mlir::Value address, ::mlir::Value clk, /*optional*/::mlir::Value enable);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value memory, ::mlir::Value address, ::mlir::Value clk, /*optional*/::mlir::Value enable);
  static FirMemReadOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value memory, ::mlir::Value address, ::mlir::Value clk, /*optional*/::mlir::Value enable);
  static FirMemReadOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value memory, ::mlir::Value address, ::mlir::Value clk, /*optional*/::mlir::Value enable);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value memory, ::mlir::Value address, ::mlir::Value clk, /*optional*/::mlir::Value enable);
  static FirMemReadOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value memory, ::mlir::Value address, ::mlir::Value clk, /*optional*/::mlir::Value enable);
  static FirMemReadOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value memory, ::mlir::Value address, ::mlir::Value clk, /*optional*/::mlir::Value enable);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static FirMemReadOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static FirMemReadOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static FirMemReadOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static FirMemReadOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static FirMemReadOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static FirMemReadOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static FirMemReadOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static FirMemReadOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::llvm::LogicalResult canonicalize(FirMemReadOp op, ::mlir::PatternRewriter &rewriter);
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::PropertyRef properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
};

} // namespace circt::seq
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::seq::FirMemReadOp)

namespace circt::seq {


//===----------------------------------------------------------------------===//
// ::circt::seq::FirMemReadWriteOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class FirMemReadWriteOpGenericAdaptorBase {
public:
  struct Properties {
    using operandSegmentSizesTy = std::array<int32_t, 7>;
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
  FirMemReadWriteOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("seq.firmem.read_write_port", odsAttrs.getContext());
  }

  FirMemReadWriteOpGenericAdaptorBase(FirMemReadWriteOp op);

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
class FirMemReadWriteOpGenericAdaptor : public detail::FirMemReadWriteOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::FirMemReadWriteOpGenericAdaptorBase;
  static constexpr int odsIndex_memory = 0;
  static constexpr int odsIndex_address = 1;
  static constexpr int odsIndex_clk = 2;
  static constexpr int odsIndex_enable = 3;
  static constexpr int odsIndex_writeData = 4;
  static constexpr int odsIndex_mode = 5;
  static constexpr int odsIndex_mask = 6;
public:
  FirMemReadWriteOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  FirMemReadWriteOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : FirMemReadWriteOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  FirMemReadWriteOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs) : FirMemReadWriteOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  FirMemReadWriteOpGenericAdaptor(RangeT values, const FirMemReadWriteOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = FirMemReadWriteOp, typename = std::enable_if_t<std::is_same_v<LateInst, FirMemReadWriteOp>>>
  FirMemReadWriteOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getMemory() {
    return (*getODSOperands(0).begin());
  }

  ValueT getAddress() {
    return (*getODSOperands(1).begin());
  }

  ValueT getClk() {
    return (*getODSOperands(2).begin());
  }

  ValueT getEnable() {
    auto operands = getODSOperands(3);
    return operands.empty() ? ValueT{} : (*operands.begin());
  }

  ValueT getWriteData() {
    return (*getODSOperands(4).begin());
  }

  ValueT getMode() {
    return (*getODSOperands(5).begin());
  }

  ValueT getMask() {
    auto operands = getODSOperands(6);
    return operands.empty() ? ValueT{} : (*operands.begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class FirMemReadWriteOpAdaptor : public FirMemReadWriteOpGenericAdaptor<::mlir::ValueRange> {
public:
  using FirMemReadWriteOpGenericAdaptor::FirMemReadWriteOpGenericAdaptor;
  FirMemReadWriteOpAdaptor(FirMemReadWriteOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class FirMemReadWriteOp : public ::mlir::Op<FirMemReadWriteOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::IntegerType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<5>::Impl, ::mlir::OpTrait::AttrSizedOperandSegments, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, circt::seq::Clocked::Trait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = FirMemReadWriteOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = FirMemReadWriteOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_memory = 0;
  static constexpr int odsIndex_address = 1;
  static constexpr int odsIndex_clk = 2;
  static constexpr int odsIndex_enable = 3;
  static constexpr int odsIndex_writeData = 4;
  static constexpr int odsIndex_mode = 5;
  static constexpr int odsIndex_mask = 6;
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
    return ::llvm::StringLiteral("seq.firmem.read_write_port");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::circt::seq::FirMemType> getMemory() {
    return ::llvm::cast<::mlir::TypedValue<::circt::seq::FirMemType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getAddress() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSOperands(1).begin());
  }

  ::mlir::TypedValue<::circt::seq::ClockType> getClk() {
    return ::llvm::cast<::mlir::TypedValue<::circt::seq::ClockType>>(*getODSOperands(2).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getEnable() {
    auto operands = getODSOperands(3);
    return operands.empty() ? ::mlir::TypedValue<::mlir::IntegerType>{} : ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*operands.begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getWriteData() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSOperands(4).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getMode() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSOperands(5).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getMask() {
    auto operands = getODSOperands(6);
    return operands.empty() ? ::mlir::TypedValue<::mlir::IntegerType>{} : ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*operands.begin());
  }

  ::mlir::OpOperand &getMemoryMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getAddressMutable() {
    auto range = getODSOperandIndexAndLength(1);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getClkMutable() {
    auto range = getODSOperandIndexAndLength(2);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::MutableOperandRange getEnableMutable();
  ::mlir::OpOperand &getWriteDataMutable() {
    auto range = getODSOperandIndexAndLength(4);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getModeMutable() {
    auto range = getODSOperandIndexAndLength(5);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::MutableOperandRange getMaskMutable();
  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::IntegerType> getReadData() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSResults(0).begin());
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type readData, ::mlir::Value memory, ::mlir::Value address, ::mlir::Value clk, /*optional*/::mlir::Value enable, ::mlir::Value writeData, ::mlir::Value mode, /*optional*/::mlir::Value mask);
  static FirMemReadWriteOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type readData, ::mlir::Value memory, ::mlir::Value address, ::mlir::Value clk, /*optional*/::mlir::Value enable, ::mlir::Value writeData, ::mlir::Value mode, /*optional*/::mlir::Value mask);
  static FirMemReadWriteOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type readData, ::mlir::Value memory, ::mlir::Value address, ::mlir::Value clk, /*optional*/::mlir::Value enable, ::mlir::Value writeData, ::mlir::Value mode, /*optional*/::mlir::Value mask);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value memory, ::mlir::Value address, ::mlir::Value clk, /*optional*/::mlir::Value enable, ::mlir::Value writeData, ::mlir::Value mode, /*optional*/::mlir::Value mask);
  static FirMemReadWriteOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value memory, ::mlir::Value address, ::mlir::Value clk, /*optional*/::mlir::Value enable, ::mlir::Value writeData, ::mlir::Value mode, /*optional*/::mlir::Value mask);
  static FirMemReadWriteOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value memory, ::mlir::Value address, ::mlir::Value clk, /*optional*/::mlir::Value enable, ::mlir::Value writeData, ::mlir::Value mode, /*optional*/::mlir::Value mask);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value memory, ::mlir::Value address, ::mlir::Value clk, /*optional*/::mlir::Value enable, ::mlir::Value writeData, ::mlir::Value mode, /*optional*/::mlir::Value mask);
  static FirMemReadWriteOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value memory, ::mlir::Value address, ::mlir::Value clk, /*optional*/::mlir::Value enable, ::mlir::Value writeData, ::mlir::Value mode, /*optional*/::mlir::Value mask);
  static FirMemReadWriteOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value memory, ::mlir::Value address, ::mlir::Value clk, /*optional*/::mlir::Value enable, ::mlir::Value writeData, ::mlir::Value mode, /*optional*/::mlir::Value mask);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static FirMemReadWriteOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static FirMemReadWriteOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static FirMemReadWriteOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static FirMemReadWriteOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static FirMemReadWriteOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static FirMemReadWriteOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static FirMemReadWriteOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static FirMemReadWriteOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static ::llvm::LogicalResult canonicalize(FirMemReadWriteOp op, ::mlir::PatternRewriter &rewriter);
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::PropertyRef properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
private:
  ::mlir::StringAttr getAttributeNameForIndex(unsigned index) {
    return getAttributeNameForIndex((*this)->getName(), index);
  }

  static ::mlir::StringAttr getAttributeNameForIndex(::mlir::OperationName name, unsigned index) {
    return {};
  }

public:
};

} // namespace circt::seq
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::seq::FirMemReadWriteOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::seq::detail::FirMemReadWriteOpGenericAdaptorBase::Properties)

namespace circt::seq {


//===----------------------------------------------------------------------===//
// ::circt::seq::FirMemWriteOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class FirMemWriteOpGenericAdaptorBase {
public:
  struct Properties {
    using operandSegmentSizesTy = std::array<int32_t, 6>;
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
  FirMemWriteOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("seq.firmem.write_port", odsAttrs.getContext());
  }

  FirMemWriteOpGenericAdaptorBase(FirMemWriteOp op);

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
class FirMemWriteOpGenericAdaptor : public detail::FirMemWriteOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::FirMemWriteOpGenericAdaptorBase;
  static constexpr int odsIndex_memory = 0;
  static constexpr int odsIndex_address = 1;
  static constexpr int odsIndex_clk = 2;
  static constexpr int odsIndex_enable = 3;
  static constexpr int odsIndex_data = 4;
  static constexpr int odsIndex_mask = 5;
public:
  FirMemWriteOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  FirMemWriteOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : FirMemWriteOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  FirMemWriteOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs) : FirMemWriteOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  FirMemWriteOpGenericAdaptor(RangeT values, const FirMemWriteOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = FirMemWriteOp, typename = std::enable_if_t<std::is_same_v<LateInst, FirMemWriteOp>>>
  FirMemWriteOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getMemory() {
    return (*getODSOperands(0).begin());
  }

  ValueT getAddress() {
    return (*getODSOperands(1).begin());
  }

  ValueT getClk() {
    return (*getODSOperands(2).begin());
  }

  ValueT getEnable() {
    auto operands = getODSOperands(3);
    return operands.empty() ? ValueT{} : (*operands.begin());
  }

  ValueT getData() {
    return (*getODSOperands(4).begin());
  }

  ValueT getMask() {
    auto operands = getODSOperands(5);
    return operands.empty() ? ValueT{} : (*operands.begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class FirMemWriteOpAdaptor : public FirMemWriteOpGenericAdaptor<::mlir::ValueRange> {
public:
  using FirMemWriteOpGenericAdaptor::FirMemWriteOpGenericAdaptor;
  FirMemWriteOpAdaptor(FirMemWriteOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class FirMemWriteOp : public ::mlir::Op<FirMemWriteOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<4>::Impl, ::mlir::OpTrait::AttrSizedOperandSegments, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, circt::seq::Clocked::Trait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = FirMemWriteOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = FirMemWriteOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_memory = 0;
  static constexpr int odsIndex_address = 1;
  static constexpr int odsIndex_clk = 2;
  static constexpr int odsIndex_enable = 3;
  static constexpr int odsIndex_data = 4;
  static constexpr int odsIndex_mask = 5;
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
    return ::llvm::StringLiteral("seq.firmem.write_port");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::circt::seq::FirMemType> getMemory() {
    return ::llvm::cast<::mlir::TypedValue<::circt::seq::FirMemType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getAddress() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSOperands(1).begin());
  }

  ::mlir::TypedValue<::circt::seq::ClockType> getClk() {
    return ::llvm::cast<::mlir::TypedValue<::circt::seq::ClockType>>(*getODSOperands(2).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getEnable() {
    auto operands = getODSOperands(3);
    return operands.empty() ? ::mlir::TypedValue<::mlir::IntegerType>{} : ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*operands.begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getData() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSOperands(4).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getMask() {
    auto operands = getODSOperands(5);
    return operands.empty() ? ::mlir::TypedValue<::mlir::IntegerType>{} : ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*operands.begin());
  }

  ::mlir::OpOperand &getMemoryMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getAddressMutable() {
    auto range = getODSOperandIndexAndLength(1);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getClkMutable() {
    auto range = getODSOperandIndexAndLength(2);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::MutableOperandRange getEnableMutable();
  ::mlir::OpOperand &getDataMutable() {
    auto range = getODSOperandIndexAndLength(4);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::MutableOperandRange getMaskMutable();
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value memory, ::mlir::Value address, ::mlir::Value clk, /*optional*/::mlir::Value enable, ::mlir::Value data, /*optional*/::mlir::Value mask);
  static FirMemWriteOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value memory, ::mlir::Value address, ::mlir::Value clk, /*optional*/::mlir::Value enable, ::mlir::Value data, /*optional*/::mlir::Value mask);
  static FirMemWriteOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value memory, ::mlir::Value address, ::mlir::Value clk, /*optional*/::mlir::Value enable, ::mlir::Value data, /*optional*/::mlir::Value mask);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value memory, ::mlir::Value address, ::mlir::Value clk, /*optional*/::mlir::Value enable, ::mlir::Value data, /*optional*/::mlir::Value mask);
  static FirMemWriteOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value memory, ::mlir::Value address, ::mlir::Value clk, /*optional*/::mlir::Value enable, ::mlir::Value data, /*optional*/::mlir::Value mask);
  static FirMemWriteOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value memory, ::mlir::Value address, ::mlir::Value clk, /*optional*/::mlir::Value enable, ::mlir::Value data, /*optional*/::mlir::Value mask);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static FirMemWriteOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static FirMemWriteOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static FirMemWriteOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static FirMemWriteOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static ::llvm::LogicalResult canonicalize(FirMemWriteOp op, ::mlir::PatternRewriter &rewriter);
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
private:
  ::mlir::StringAttr getAttributeNameForIndex(unsigned index) {
    return getAttributeNameForIndex((*this)->getName(), index);
  }

  static ::mlir::StringAttr getAttributeNameForIndex(::mlir::OperationName name, unsigned index) {
    return {};
  }

public:
};

} // namespace circt::seq
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::seq::FirMemWriteOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::seq::detail::FirMemWriteOpGenericAdaptorBase::Properties)

namespace circt::seq {


//===----------------------------------------------------------------------===//
// ::circt::seq::FirRegOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class FirRegOpGenericAdaptorBase {
public:
  struct Properties {
    using inner_symTy = ::circt::hw::InnerSymAttr;
    inner_symTy inner_sym;

    auto getInnerSym() const {
      auto &propStorage = this->inner_sym;
      return ::llvm::dyn_cast_or_null<::circt::hw::InnerSymAttr>(propStorage);
    }
    void setInnerSym(const ::circt::hw::InnerSymAttr &propValue) {
      this->inner_sym = propValue;
    }
    using isAsyncTy = ::mlir::UnitAttr;
    isAsyncTy isAsync;

    auto getIsAsync() const {
      auto &propStorage = this->isAsync;
      return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(propStorage);
    }
    void setIsAsync(const ::mlir::UnitAttr &propValue) {
      this->isAsync = propValue;
    }
    using nameTy = ::mlir::StringAttr;
    nameTy name;

    auto getName() const {
      auto &propStorage = this->name;
      return ::llvm::cast<::mlir::StringAttr>(propStorage);
    }
    void setName(const ::mlir::StringAttr &propValue) {
      this->name = propValue;
    }
    using presetTy = ::mlir::IntegerAttr;
    presetTy preset;

    auto getPreset() const {
      auto &propStorage = this->preset;
      return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(propStorage);
    }
    void setPreset(const ::mlir::IntegerAttr &propValue) {
      this->preset = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.inner_sym == this->inner_sym &&
        rhs.isAsync == this->isAsync &&
        rhs.name == this->name &&
        rhs.preset == this->preset &&
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
  FirRegOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("seq.firreg", odsAttrs.getContext());
  }

  FirRegOpGenericAdaptorBase(FirRegOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::StringAttr getNameAttr() {
    auto attr = ::llvm::cast<::mlir::StringAttr>(getProperties().name);
    return attr;
  }

  ::llvm::StringRef getName();
  ::circt::hw::InnerSymAttr getInnerSymAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::circt::hw::InnerSymAttr>(getProperties().inner_sym);
    return attr;
  }

  ::std::optional<::circt::hw::InnerSymAttr> getInnerSym();
  ::mlir::IntegerAttr getPresetAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(getProperties().preset);
    return attr;
  }

  ::std::optional< ::mlir::APInt > getPreset();
  ::mlir::UnitAttr getIsAsyncAttr();
  bool getIsAsync();
};

} // namespace detail
template <typename RangeT>
class FirRegOpGenericAdaptor : public detail::FirRegOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::FirRegOpGenericAdaptorBase;
  static constexpr int odsIndex_next = 0;
  static constexpr int odsIndex_clk = 1;
  static constexpr int odsIndex_reset = 2;
  static constexpr int odsIndex_resetValue = 3;
public:
  FirRegOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  FirRegOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : FirRegOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  FirRegOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : FirRegOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  FirRegOpGenericAdaptor(RangeT values, const FirRegOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = FirRegOp, typename = std::enable_if_t<std::is_same_v<LateInst, FirRegOp>>>
  FirRegOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getNext() {
    return (*getODSOperands(0).begin());
  }

  ValueT getClk() {
    return (*getODSOperands(1).begin());
  }

  ValueT getReset() {
    auto operands = getODSOperands(2);
    return operands.empty() ? ValueT{} : (*operands.begin());
  }

  ValueT getResetValue() {
    auto operands = getODSOperands(3);
    return operands.empty() ? ValueT{} : (*operands.begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class FirRegOpAdaptor : public FirRegOpGenericAdaptor<::mlir::ValueRange> {
public:
  using FirRegOpGenericAdaptor::FirRegOpGenericAdaptor;
  FirRegOpAdaptor(FirRegOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class FirRegOp : public ::mlir::Op<FirRegOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::Type>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<2>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, circt::seq::Clocked::Trait, circt::seq::Resettable::Trait, ::mlir::OpAsmOpInterface::Trait, ::circt::hw::InnerSymbolOpInterface::Trait, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = FirRegOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = FirRegOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_next = 0;
  static constexpr int odsIndex_clk = 1;
  static constexpr int odsIndex_reset = 2;
  static constexpr int odsIndex_resetValue = 3;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::OpAsmOpInterface::Trait<FirRegOp>::getAsmBlockArgumentNames;
  using ::mlir::OpAsmOpInterface::Trait<FirRegOp>::getAsmBlockNames;
  using ::mlir::OpAsmOpInterface::Trait<FirRegOp>::getDefaultDialect;
  using ::circt::hw::InnerSymbolOpInterface::Trait<FirRegOp>::getInnerNameAttr;
  using ::circt::hw::InnerSymbolOpInterface::Trait<FirRegOp>::getInnerName;
  using ::circt::hw::InnerSymbolOpInterface::Trait<FirRegOp>::setInnerSymbol;
  using ::circt::hw::InnerSymbolOpInterface::Trait<FirRegOp>::setInnerSymbolAttr;
  using ::circt::hw::InnerSymbolOpInterface::Trait<FirRegOp>::getInnerRef;
  using ::circt::hw::InnerSymbolOpInterface::Trait<FirRegOp>::getInnerSymAttr;
  using ::circt::hw::InnerSymbolOpInterface::Trait<FirRegOp>::supportsPerFieldSymbols;
  using ::circt::hw::InnerSymbolOpInterface::Trait<FirRegOp>::getTargetResult;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("inner_sym"), ::llvm::StringRef("isAsync"), ::llvm::StringRef("name"), ::llvm::StringRef("preset")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getInnerSymAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getInnerSymAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getIsAsyncAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getIsAsyncAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getNameAttrName() {
    return getAttributeNameForIndex(2);
  }

  static ::mlir::StringAttr getNameAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 2);
  }

  ::mlir::StringAttr getPresetAttrName() {
    return getAttributeNameForIndex(3);
  }

  static ::mlir::StringAttr getPresetAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 3);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("seq.firreg");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::Type> getNext() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::circt::seq::ClockType> getClk() {
    return ::llvm::cast<::mlir::TypedValue<::circt::seq::ClockType>>(*getODSOperands(1).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getReset() {
    auto operands = getODSOperands(2);
    return operands.empty() ? ::mlir::TypedValue<::mlir::IntegerType>{} : ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*operands.begin());
  }

  ::mlir::TypedValue<::mlir::Type> getResetValue() {
    auto operands = getODSOperands(3);
    return operands.empty() ? ::mlir::TypedValue<::mlir::Type>{} : ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*operands.begin());
  }

  ::mlir::OpOperand &getNextMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getClkMutable() {
    auto range = getODSOperandIndexAndLength(1);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::MutableOperandRange getResetMutable();
  ::mlir::MutableOperandRange getResetValueMutable();
  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::Type> getData() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSResults(0).begin());
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
    return ::llvm::cast<::mlir::StringAttr>(getProperties().name);
  }

  ::llvm::StringRef getName();
  ::circt::hw::InnerSymAttr getInnerSymAttr() {
    return ::llvm::dyn_cast_or_null<::circt::hw::InnerSymAttr>(getProperties().inner_sym);
  }

  ::std::optional<::circt::hw::InnerSymAttr> getInnerSym();
  ::mlir::IntegerAttr getPresetAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(getProperties().preset);
  }

  ::std::optional< ::mlir::APInt > getPreset();
  ::mlir::UnitAttr getIsAsyncAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(getProperties().isAsync);
  }

  bool getIsAsync();
  void setNameAttr(::mlir::StringAttr attr) {
    getProperties().name = attr;
  }

  void setName(::llvm::StringRef attrValue);
  void setInnerSymAttr(::circt::hw::InnerSymAttr attr) {
    getProperties().inner_sym = attr;
  }

  void setPresetAttr(::mlir::IntegerAttr attr) {
    getProperties().preset = attr;
  }

  void setIsAsyncAttr(::mlir::UnitAttr attr) {
    getProperties().isAsync = attr;
  }

  void setIsAsync(bool attrValue);
  ::mlir::Attribute removeInnerSymAttr() {
      auto attr = getProperties().inner_sym;
      getProperties().inner_sym = {};
      return attr;
  }

  ::mlir::Attribute removePresetAttr() {
      auto attr = getProperties().preset;
      getProperties().preset = {};
      return attr;
  }

  ::mlir::Attribute removeIsAsyncAttr() {
      auto attr = getProperties().isAsync;
      getProperties().isAsync = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value next, Value clk, StringAttr name, hw::InnerSymAttr innerSym = {}, Attribute preset = {});
  static FirRegOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value next, Value clk, StringAttr name, hw::InnerSymAttr innerSym = {}, Attribute preset = {});
  static FirRegOp create(::mlir::ImplicitLocOpBuilder &builder, Value next, Value clk, StringAttr name, hw::InnerSymAttr innerSym = {}, Attribute preset = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value next, Value clk, StringAttr name, Value reset, Value resetValue, hw::InnerSymAttr innerSym = {}, bool isAsync = false);
  static FirRegOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value next, Value clk, StringAttr name, Value reset, Value resetValue, hw::InnerSymAttr innerSym = {}, bool isAsync = false);
  static FirRegOp create(::mlir::ImplicitLocOpBuilder &builder, Value next, Value clk, StringAttr name, Value reset, Value resetValue, hw::InnerSymAttr innerSym = {}, bool isAsync = false);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type data, ::mlir::Value next, ::mlir::Value clk, ::mlir::StringAttr name, /*optional*/::circt::hw::InnerSymAttr inner_sym, /*optional*/::mlir::IntegerAttr preset, /*optional*/::mlir::Value reset, /*optional*/::mlir::Value resetValue, /*optional*/::mlir::UnitAttr isAsync = nullptr);
  static FirRegOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type data, ::mlir::Value next, ::mlir::Value clk, ::mlir::StringAttr name, /*optional*/::circt::hw::InnerSymAttr inner_sym, /*optional*/::mlir::IntegerAttr preset, /*optional*/::mlir::Value reset, /*optional*/::mlir::Value resetValue, /*optional*/::mlir::UnitAttr isAsync = nullptr);
  static FirRegOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type data, ::mlir::Value next, ::mlir::Value clk, ::mlir::StringAttr name, /*optional*/::circt::hw::InnerSymAttr inner_sym, /*optional*/::mlir::IntegerAttr preset, /*optional*/::mlir::Value reset, /*optional*/::mlir::Value resetValue, /*optional*/::mlir::UnitAttr isAsync = nullptr);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value next, ::mlir::Value clk, ::mlir::StringAttr name, /*optional*/::circt::hw::InnerSymAttr inner_sym, /*optional*/::mlir::IntegerAttr preset, /*optional*/::mlir::Value reset, /*optional*/::mlir::Value resetValue, /*optional*/::mlir::UnitAttr isAsync = nullptr);
  static FirRegOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value next, ::mlir::Value clk, ::mlir::StringAttr name, /*optional*/::circt::hw::InnerSymAttr inner_sym, /*optional*/::mlir::IntegerAttr preset, /*optional*/::mlir::Value reset, /*optional*/::mlir::Value resetValue, /*optional*/::mlir::UnitAttr isAsync = nullptr);
  static FirRegOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value next, ::mlir::Value clk, ::mlir::StringAttr name, /*optional*/::circt::hw::InnerSymAttr inner_sym, /*optional*/::mlir::IntegerAttr preset, /*optional*/::mlir::Value reset, /*optional*/::mlir::Value resetValue, /*optional*/::mlir::UnitAttr isAsync = nullptr);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value next, ::mlir::Value clk, ::mlir::StringAttr name, /*optional*/::circt::hw::InnerSymAttr inner_sym, /*optional*/::mlir::IntegerAttr preset, /*optional*/::mlir::Value reset, /*optional*/::mlir::Value resetValue, /*optional*/::mlir::UnitAttr isAsync = nullptr);
  static FirRegOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value next, ::mlir::Value clk, ::mlir::StringAttr name, /*optional*/::circt::hw::InnerSymAttr inner_sym, /*optional*/::mlir::IntegerAttr preset, /*optional*/::mlir::Value reset, /*optional*/::mlir::Value resetValue, /*optional*/::mlir::UnitAttr isAsync = nullptr);
  static FirRegOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value next, ::mlir::Value clk, ::mlir::StringAttr name, /*optional*/::circt::hw::InnerSymAttr inner_sym, /*optional*/::mlir::IntegerAttr preset, /*optional*/::mlir::Value reset, /*optional*/::mlir::Value resetValue, /*optional*/::mlir::UnitAttr isAsync = nullptr);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type data, ::mlir::Value next, ::mlir::Value clk, ::llvm::StringRef name, /*optional*/::circt::hw::InnerSymAttr inner_sym, /*optional*/::mlir::IntegerAttr preset, /*optional*/::mlir::Value reset, /*optional*/::mlir::Value resetValue, /*optional*/bool isAsync = false);
  static FirRegOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type data, ::mlir::Value next, ::mlir::Value clk, ::llvm::StringRef name, /*optional*/::circt::hw::InnerSymAttr inner_sym, /*optional*/::mlir::IntegerAttr preset, /*optional*/::mlir::Value reset, /*optional*/::mlir::Value resetValue, /*optional*/bool isAsync = false);
  static FirRegOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type data, ::mlir::Value next, ::mlir::Value clk, ::llvm::StringRef name, /*optional*/::circt::hw::InnerSymAttr inner_sym, /*optional*/::mlir::IntegerAttr preset, /*optional*/::mlir::Value reset, /*optional*/::mlir::Value resetValue, /*optional*/bool isAsync = false);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value next, ::mlir::Value clk, ::llvm::StringRef name, /*optional*/::circt::hw::InnerSymAttr inner_sym, /*optional*/::mlir::IntegerAttr preset, /*optional*/::mlir::Value reset, /*optional*/::mlir::Value resetValue, /*optional*/bool isAsync = false);
  static FirRegOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value next, ::mlir::Value clk, ::llvm::StringRef name, /*optional*/::circt::hw::InnerSymAttr inner_sym, /*optional*/::mlir::IntegerAttr preset, /*optional*/::mlir::Value reset, /*optional*/::mlir::Value resetValue, /*optional*/bool isAsync = false);
  static FirRegOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value next, ::mlir::Value clk, ::llvm::StringRef name, /*optional*/::circt::hw::InnerSymAttr inner_sym, /*optional*/::mlir::IntegerAttr preset, /*optional*/::mlir::Value reset, /*optional*/::mlir::Value resetValue, /*optional*/bool isAsync = false);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value next, ::mlir::Value clk, ::llvm::StringRef name, /*optional*/::circt::hw::InnerSymAttr inner_sym, /*optional*/::mlir::IntegerAttr preset, /*optional*/::mlir::Value reset, /*optional*/::mlir::Value resetValue, /*optional*/bool isAsync = false);
  static FirRegOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value next, ::mlir::Value clk, ::llvm::StringRef name, /*optional*/::circt::hw::InnerSymAttr inner_sym, /*optional*/::mlir::IntegerAttr preset, /*optional*/::mlir::Value reset, /*optional*/::mlir::Value resetValue, /*optional*/bool isAsync = false);
  static FirRegOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value next, ::mlir::Value clk, ::llvm::StringRef name, /*optional*/::circt::hw::InnerSymAttr inner_sym, /*optional*/::mlir::IntegerAttr preset, /*optional*/::mlir::Value reset, /*optional*/::mlir::Value resetValue, /*optional*/bool isAsync = false);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static FirRegOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static FirRegOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static FirRegOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static FirRegOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static FirRegOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static FirRegOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static FirRegOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static FirRegOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &p);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static ::llvm::LogicalResult canonicalize(FirRegOp op, ::mlir::PatternRewriter &rewriter);
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
  ::mlir::OpFoldResult fold(FoldAdaptor adaptor);
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::PropertyRef properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
  static std::optional<size_t> getTargetResultIndex();
  static ::llvm::LogicalResult setPropertiesFromParsedAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
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
  /// Check whether the register has a reset value.
  bool hasReset() { return !!getReset(); }
  /// Check whether the register has a preset value.
  bool hasPresetValue() { return !!getPresetAttr(); }
};

} // namespace circt::seq
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::seq::FirRegOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::seq::detail::FirRegOpGenericAdaptorBase::Properties)

namespace circt::seq {


//===----------------------------------------------------------------------===//
// ::circt::seq::FromClockOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class FromClockOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  FromClockOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("seq.from_clock", odsAttrs.getContext());
  }

  FromClockOpGenericAdaptorBase(FromClockOp op);

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
class FromClockOpGenericAdaptor : public detail::FromClockOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::FromClockOpGenericAdaptorBase;
  static constexpr int odsIndex_input = 0;
public:
  FromClockOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  FromClockOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : FromClockOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  FromClockOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : FromClockOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  FromClockOpGenericAdaptor(RangeT values, const FromClockOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = FromClockOp, typename = std::enable_if_t<std::is_same_v<LateInst, FromClockOp>>>
  FromClockOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class FromClockOpAdaptor : public FromClockOpGenericAdaptor<::mlir::ValueRange> {
public:
  using FromClockOpGenericAdaptor::FromClockOpGenericAdaptor;
  FromClockOpAdaptor(FromClockOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class FromClockOp : public ::mlir::Op<FromClockOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::IntegerType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = FromClockOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = FromClockOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_input = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("seq.from_clock");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::circt::seq::ClockType> getInput() {
    return ::llvm::cast<::mlir::TypedValue<::circt::seq::ClockType>>(*getODSOperands(0).begin());
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

  ::mlir::TypedValue<::mlir::IntegerType> getOutput() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSResults(0).begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type output, ::mlir::Value input);
  static FromClockOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type output, ::mlir::Value input);
  static FromClockOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type output, ::mlir::Value input);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value input);
  static FromClockOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value input);
  static FromClockOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value input);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value input);
  static FromClockOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value input);
  static FromClockOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value input);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static FromClockOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static FromClockOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static FromClockOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static FromClockOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static FromClockOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static FromClockOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static FromClockOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static FromClockOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::llvm::LogicalResult canonicalize(FromClockOp op, ::mlir::PatternRewriter &rewriter);
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
  ::mlir::OpFoldResult fold(FoldAdaptor adaptor);
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::PropertyRef properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
};

} // namespace circt::seq
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::seq::FromClockOp)

namespace circt::seq {


//===----------------------------------------------------------------------===//
// ::circt::seq::FromImmutableOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class FromImmutableOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  FromImmutableOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("seq.from_immutable", odsAttrs.getContext());
  }

  FromImmutableOpGenericAdaptorBase(FromImmutableOp op);

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
class FromImmutableOpGenericAdaptor : public detail::FromImmutableOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::FromImmutableOpGenericAdaptorBase;
  static constexpr int odsIndex_input = 0;
public:
  FromImmutableOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  FromImmutableOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : FromImmutableOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  FromImmutableOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : FromImmutableOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  FromImmutableOpGenericAdaptor(RangeT values, const FromImmutableOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = FromImmutableOp, typename = std::enable_if_t<std::is_same_v<LateInst, FromImmutableOp>>>
  FromImmutableOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class FromImmutableOpAdaptor : public FromImmutableOpGenericAdaptor<::mlir::ValueRange> {
public:
  using FromImmutableOpGenericAdaptor::FromImmutableOpGenericAdaptor;
  FromImmutableOpAdaptor(FromImmutableOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class FromImmutableOp : public ::mlir::Op<FromImmutableOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::Type>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = FromImmutableOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = FromImmutableOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_input = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("seq.from_immutable");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::circt::seq::ImmutableType> getInput() {
    return ::llvm::cast<::mlir::TypedValue<::circt::seq::ImmutableType>>(*getODSOperands(0).begin());
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
  static FromImmutableOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type output, ::mlir::Value input);
  static FromImmutableOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type output, ::mlir::Value input);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value input);
  static FromImmutableOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value input);
  static FromImmutableOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value input);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static FromImmutableOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static FromImmutableOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static FromImmutableOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static FromImmutableOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
};

} // namespace circt::seq
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::seq::FromImmutableOp)

namespace circt::seq {


//===----------------------------------------------------------------------===//
// ::circt::seq::HLMemOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class HLMemOpGenericAdaptorBase {
public:
  struct Properties {
    using nameTy = ::mlir::StringAttr;
    nameTy name;

    auto getName() const {
      auto &propStorage = this->name;
      return ::llvm::cast<::mlir::StringAttr>(propStorage);
    }
    void setName(const ::mlir::StringAttr &propValue) {
      this->name = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.name == this->name &&
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
  HLMemOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("seq.hlmem", odsAttrs.getContext());
  }

  HLMemOpGenericAdaptorBase(HLMemOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::StringAttr getNameAttr() {
    auto attr = ::llvm::cast<::mlir::StringAttr>(getProperties().name);
    return attr;
  }

  ::llvm::StringRef getName();
};

} // namespace detail
template <typename RangeT>
class HLMemOpGenericAdaptor : public detail::HLMemOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::HLMemOpGenericAdaptorBase;
  static constexpr int odsIndex_clk = 0;
  static constexpr int odsIndex_rst = 1;
public:
  HLMemOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  HLMemOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : HLMemOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  HLMemOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : HLMemOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  HLMemOpGenericAdaptor(RangeT values, const HLMemOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = HLMemOp, typename = std::enable_if_t<std::is_same_v<LateInst, HLMemOp>>>
  HLMemOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getClk() {
    return (*getODSOperands(0).begin());
  }

  ValueT getRst() {
    return (*getODSOperands(1).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class HLMemOpAdaptor : public HLMemOpGenericAdaptor<::mlir::ValueRange> {
public:
  using HLMemOpGenericAdaptor::HLMemOpGenericAdaptor;
  HLMemOpAdaptor(HLMemOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class HLMemOp : public ::mlir::Op<HLMemOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::circt::seq::HLMemType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::NOperands<2>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, circt::seq::Clocked::Trait, ::mlir::OpAsmOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = HLMemOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = HLMemOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_clk = 0;
  static constexpr int odsIndex_rst = 1;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::OpAsmOpInterface::Trait<HLMemOp>::getAsmBlockArgumentNames;
  using ::mlir::OpAsmOpInterface::Trait<HLMemOp>::getAsmBlockNames;
  using ::mlir::OpAsmOpInterface::Trait<HLMemOp>::getDefaultDialect;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("name")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getNameAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getNameAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("seq.hlmem");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::circt::seq::ClockType> getClk() {
    return ::llvm::cast<::mlir::TypedValue<::circt::seq::ClockType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getRst() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSOperands(1).begin());
  }

  ::mlir::OpOperand &getClkMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getRstMutable() {
    auto range = getODSOperandIndexAndLength(1);
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

  ::mlir::TypedValue<::circt::seq::HLMemType> getHandle() {
    return ::llvm::cast<::mlir::TypedValue<::circt::seq::HLMemType>>(*getODSResults(0).begin());
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
    return ::llvm::cast<::mlir::StringAttr>(getProperties().name);
  }

  ::llvm::StringRef getName();
  void setNameAttr(::mlir::StringAttr attr) {
    getProperties().name = attr;
  }

  void setName(::llvm::StringRef attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value clk, Value rst, StringRef name, llvm::ArrayRef<int64_t> shape, Type elementType);
  static HLMemOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value clk, Value rst, StringRef name, llvm::ArrayRef<int64_t> shape, Type elementType);
  static HLMemOp create(::mlir::ImplicitLocOpBuilder &builder, Value clk, Value rst, StringRef name, llvm::ArrayRef<int64_t> shape, Type elementType);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type handle, ::mlir::Value clk, ::mlir::Value rst, ::mlir::StringAttr name);
  static HLMemOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type handle, ::mlir::Value clk, ::mlir::Value rst, ::mlir::StringAttr name);
  static HLMemOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type handle, ::mlir::Value clk, ::mlir::Value rst, ::mlir::StringAttr name);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value clk, ::mlir::Value rst, ::mlir::StringAttr name);
  static HLMemOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value clk, ::mlir::Value rst, ::mlir::StringAttr name);
  static HLMemOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value clk, ::mlir::Value rst, ::mlir::StringAttr name);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type handle, ::mlir::Value clk, ::mlir::Value rst, ::llvm::StringRef name);
  static HLMemOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type handle, ::mlir::Value clk, ::mlir::Value rst, ::llvm::StringRef name);
  static HLMemOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type handle, ::mlir::Value clk, ::mlir::Value rst, ::llvm::StringRef name);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value clk, ::mlir::Value rst, ::llvm::StringRef name);
  static HLMemOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value clk, ::mlir::Value rst, ::llvm::StringRef name);
  static HLMemOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value clk, ::mlir::Value rst, ::llvm::StringRef name);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static HLMemOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static HLMemOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static HLMemOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static HLMemOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
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
  HLMemType getMemType() {
    return llvm::cast<HLMemType>(getHandle().getType());
  }
};

} // namespace circt::seq
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::seq::HLMemOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::seq::detail::HLMemOpGenericAdaptorBase::Properties)

namespace circt::seq {


//===----------------------------------------------------------------------===//
// ::circt::seq::InitialOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class InitialOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  InitialOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("seq.initial", odsAttrs.getContext());
  }

  InitialOpGenericAdaptorBase(InitialOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::Region &getBody() {
    return *odsRegions[0];
  }

  ::mlir::RegionRange getRegions() {
    return odsRegions;
  }

};

} // namespace detail
template <typename RangeT>
class InitialOpGenericAdaptor : public detail::InitialOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::InitialOpGenericAdaptorBase;
  static constexpr int odsIndex_inputs = 0;
public:
  InitialOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  InitialOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : InitialOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  InitialOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : InitialOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  InitialOpGenericAdaptor(RangeT values, const InitialOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = InitialOp, typename = std::enable_if_t<std::is_same_v<LateInst, InitialOp>>>
  InitialOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class InitialOpAdaptor : public InitialOpGenericAdaptor<::mlir::ValueRange> {
public:
  using InitialOpGenericAdaptor::InitialOpGenericAdaptor;
  InitialOpAdaptor(InitialOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class InitialOp : public ::mlir::Op<InitialOp, ::mlir::OpTrait::OneRegion, ::mlir::OpTrait::VariadicResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::SingleBlock, ::mlir::OpTrait::SingleBlockImplicitTerminator<YieldOp>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::RecursivelySpeculatableImplTrait, ::mlir::OpTrait::HasRecursiveMemoryEffects, ::mlir::OpTrait::IsIsolatedFromAbove> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = InitialOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = InitialOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_inputs = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("seq.initial");
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
  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index);
  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, TypeRange resultTypes = {}, std::function<void()> ctor = {});
  static InitialOp create(::mlir::OpBuilder &builder, ::mlir::Location location, TypeRange resultTypes = {}, std::function<void()> ctor = {});
  static InitialOp create(::mlir::ImplicitLocOpBuilder &builder, TypeRange resultTypes = {}, std::function<void()> ctor = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
  Block *getBodyBlock() { return &getBody().front(); }
};

} // namespace circt::seq
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::seq::InitialOp)

namespace circt::seq {


//===----------------------------------------------------------------------===//
// ::circt::seq::ReadPortOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ReadPortOpGenericAdaptorBase {
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
        rhs.latency == this->latency &&
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
  ReadPortOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("seq.read", odsAttrs.getContext());
  }

  ReadPortOpGenericAdaptorBase(ReadPortOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
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

  uint64_t getLatency();
};

} // namespace detail
template <typename RangeT>
class ReadPortOpGenericAdaptor : public detail::ReadPortOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ReadPortOpGenericAdaptorBase;
  static constexpr int odsIndex_memory = 0;
  static constexpr int odsIndex_addresses = 1;
  static constexpr int odsIndex_rdEn = 2;
public:
  ReadPortOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ReadPortOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : ReadPortOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ReadPortOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs) : ReadPortOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ReadPortOpGenericAdaptor(RangeT values, const ReadPortOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ReadPortOp, typename = std::enable_if_t<std::is_same_v<LateInst, ReadPortOp>>>
  ReadPortOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getMemory() {
    return (*getODSOperands(0).begin());
  }

  RangeT getAddresses() {
    return getODSOperands(1);
  }

  ValueT getRdEn() {
    auto operands = getODSOperands(2);
    return operands.empty() ? ValueT{} : (*operands.begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class ReadPortOpAdaptor : public ReadPortOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ReadPortOpGenericAdaptor::ReadPortOpGenericAdaptor;
  ReadPortOpAdaptor(ReadPortOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ReadPortOp : public ::mlir::Op<ReadPortOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::Type>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<1>::Impl, ::mlir::OpTrait::AttrSizedOperandSegments, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::OpAsmOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ReadPortOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ReadPortOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_memory = 0;
  static constexpr int odsIndex_addresses = 1;
  static constexpr int odsIndex_rdEn = 2;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::OpAsmOpInterface::Trait<ReadPortOp>::getAsmBlockArgumentNames;
  using ::mlir::OpAsmOpInterface::Trait<ReadPortOp>::getAsmBlockNames;
  using ::mlir::OpAsmOpInterface::Trait<ReadPortOp>::getDefaultDialect;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("latency"), ::llvm::StringRef("operandSegmentSizes")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getLatencyAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getLatencyAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getOperandSegmentSizesAttrName() {
   return (*this)->getName().getAttributeNames().back();
  }

  static ::mlir::StringAttr getOperandSegmentSizesAttrName(::mlir::OperationName name) {
   return name.getAttributeNames().back();
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("seq.read");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::circt::seq::HLMemType> getMemory() {
    return ::llvm::cast<::mlir::TypedValue<::circt::seq::HLMemType>>(*getODSOperands(0).begin());
  }

  ::mlir::Operation::operand_range getAddresses() {
    return getODSOperands(1);
  }

  ::mlir::TypedValue<::mlir::IntegerType> getRdEn() {
    auto operands = getODSOperands(2);
    return operands.empty() ? ::mlir::TypedValue<::mlir::IntegerType>{} : ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*operands.begin());
  }

  ::mlir::OpOperand &getMemoryMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::MutableOperandRange getAddressesMutable();
  ::mlir::MutableOperandRange getRdEnMutable();
  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::Type> getReadData() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSResults(0).begin());
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

  uint64_t getLatency();
  void setLatencyAttr(::mlir::IntegerAttr attr) {
    getProperties().latency = attr;
  }

  void setLatency(uint64_t attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value memory, ValueRange addresses, Value rdEn, unsigned latency);
  static ReadPortOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value memory, ValueRange addresses, Value rdEn, unsigned latency);
  static ReadPortOp create(::mlir::ImplicitLocOpBuilder &builder, Value memory, ValueRange addresses, Value rdEn, unsigned latency);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type readData, ::mlir::Value memory, ::mlir::ValueRange addresses, /*optional*/::mlir::Value rdEn, ::mlir::IntegerAttr latency);
  static ReadPortOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type readData, ::mlir::Value memory, ::mlir::ValueRange addresses, /*optional*/::mlir::Value rdEn, ::mlir::IntegerAttr latency);
  static ReadPortOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type readData, ::mlir::Value memory, ::mlir::ValueRange addresses, /*optional*/::mlir::Value rdEn, ::mlir::IntegerAttr latency);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value memory, ::mlir::ValueRange addresses, /*optional*/::mlir::Value rdEn, ::mlir::IntegerAttr latency);
  static ReadPortOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value memory, ::mlir::ValueRange addresses, /*optional*/::mlir::Value rdEn, ::mlir::IntegerAttr latency);
  static ReadPortOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value memory, ::mlir::ValueRange addresses, /*optional*/::mlir::Value rdEn, ::mlir::IntegerAttr latency);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type readData, ::mlir::Value memory, ::mlir::ValueRange addresses, /*optional*/::mlir::Value rdEn, uint64_t latency);
  static ReadPortOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type readData, ::mlir::Value memory, ::mlir::ValueRange addresses, /*optional*/::mlir::Value rdEn, uint64_t latency);
  static ReadPortOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type readData, ::mlir::Value memory, ::mlir::ValueRange addresses, /*optional*/::mlir::Value rdEn, uint64_t latency);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value memory, ::mlir::ValueRange addresses, /*optional*/::mlir::Value rdEn, uint64_t latency);
  static ReadPortOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value memory, ::mlir::ValueRange addresses, /*optional*/::mlir::Value rdEn, uint64_t latency);
  static ReadPortOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value memory, ::mlir::ValueRange addresses, /*optional*/::mlir::Value rdEn, uint64_t latency);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ReadPortOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ReadPortOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ReadPortOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ReadPortOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &p);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
  static ::llvm::LogicalResult setPropertiesFromParsedAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
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
};

} // namespace circt::seq
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::seq::ReadPortOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::seq::detail::ReadPortOpGenericAdaptorBase::Properties)

namespace circt::seq {


//===----------------------------------------------------------------------===//
// ::circt::seq::ShiftRegOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ShiftRegOpGenericAdaptorBase {
public:
  struct Properties {
    using inner_symTy = ::circt::hw::InnerSymAttr;
    inner_symTy inner_sym;

    auto getInnerSym() const {
      auto &propStorage = this->inner_sym;
      return ::llvm::dyn_cast_or_null<::circt::hw::InnerSymAttr>(propStorage);
    }
    void setInnerSym(const ::circt::hw::InnerSymAttr &propValue) {
      this->inner_sym = propValue;
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
    using numElementsTy = ::mlir::IntegerAttr;
    numElementsTy numElements;

    auto getNumElements() const {
      auto &propStorage = this->numElements;
      return ::llvm::cast<::mlir::IntegerAttr>(propStorage);
    }
    void setNumElements(const ::mlir::IntegerAttr &propValue) {
      this->numElements = propValue;
    }
    using operandSegmentSizesTy = std::array<int32_t, 6>;
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
        rhs.inner_sym == this->inner_sym &&
        rhs.name == this->name &&
        rhs.numElements == this->numElements &&
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
  ShiftRegOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("seq.shiftreg", odsAttrs.getContext());
  }

  ShiftRegOpGenericAdaptorBase(ShiftRegOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::IntegerAttr getNumElementsAttr() {
    auto attr = ::llvm::cast<::mlir::IntegerAttr>(getProperties().numElements);
    return attr;
  }

  uint64_t getNumElements();
  ::mlir::StringAttr getNameAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::StringAttr>(getProperties().name);
    return attr;
  }

  ::std::optional< ::llvm::StringRef > getName();
  ::circt::hw::InnerSymAttr getInnerSymAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::circt::hw::InnerSymAttr>(getProperties().inner_sym);
    return attr;
  }

  ::std::optional<::circt::hw::InnerSymAttr> getInnerSym();
};

} // namespace detail
template <typename RangeT>
class ShiftRegOpGenericAdaptor : public detail::ShiftRegOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ShiftRegOpGenericAdaptorBase;
  static constexpr int odsIndex_input = 0;
  static constexpr int odsIndex_clk = 1;
  static constexpr int odsIndex_clockEnable = 2;
  static constexpr int odsIndex_reset = 3;
  static constexpr int odsIndex_resetValue = 4;
  static constexpr int odsIndex_powerOnValue = 5;
public:
  ShiftRegOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ShiftRegOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : ShiftRegOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ShiftRegOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs) : ShiftRegOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ShiftRegOpGenericAdaptor(RangeT values, const ShiftRegOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ShiftRegOp, typename = std::enable_if_t<std::is_same_v<LateInst, ShiftRegOp>>>
  ShiftRegOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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

  ValueT getClk() {
    return (*getODSOperands(1).begin());
  }

  ValueT getClockEnable() {
    return (*getODSOperands(2).begin());
  }

  ValueT getReset() {
    auto operands = getODSOperands(3);
    return operands.empty() ? ValueT{} : (*operands.begin());
  }

  ValueT getResetValue() {
    auto operands = getODSOperands(4);
    return operands.empty() ? ValueT{} : (*operands.begin());
  }

  ValueT getPowerOnValue() {
    auto operands = getODSOperands(5);
    return operands.empty() ? ValueT{} : (*operands.begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class ShiftRegOpAdaptor : public ShiftRegOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ShiftRegOpGenericAdaptor::ShiftRegOpGenericAdaptor;
  ShiftRegOpAdaptor(ShiftRegOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ShiftRegOp : public ::mlir::Op<ShiftRegOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::Type>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<3>::Impl, ::mlir::OpTrait::AttrSizedOperandSegments, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, circt::seq::Clocked::Trait, circt::seq::Resettable::Trait, ::mlir::OpAsmOpInterface::Trait, ::circt::hw::InnerSymbolOpInterface::Trait, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ShiftRegOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ShiftRegOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_input = 0;
  static constexpr int odsIndex_clk = 1;
  static constexpr int odsIndex_clockEnable = 2;
  static constexpr int odsIndex_reset = 3;
  static constexpr int odsIndex_resetValue = 4;
  static constexpr int odsIndex_powerOnValue = 5;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::OpAsmOpInterface::Trait<ShiftRegOp>::getAsmBlockArgumentNames;
  using ::mlir::OpAsmOpInterface::Trait<ShiftRegOp>::getAsmBlockNames;
  using ::mlir::OpAsmOpInterface::Trait<ShiftRegOp>::getDefaultDialect;
  using ::circt::hw::InnerSymbolOpInterface::Trait<ShiftRegOp>::getInnerNameAttr;
  using ::circt::hw::InnerSymbolOpInterface::Trait<ShiftRegOp>::getInnerName;
  using ::circt::hw::InnerSymbolOpInterface::Trait<ShiftRegOp>::setInnerSymbol;
  using ::circt::hw::InnerSymbolOpInterface::Trait<ShiftRegOp>::setInnerSymbolAttr;
  using ::circt::hw::InnerSymbolOpInterface::Trait<ShiftRegOp>::getInnerRef;
  using ::circt::hw::InnerSymbolOpInterface::Trait<ShiftRegOp>::getInnerSymAttr;
  using ::circt::hw::InnerSymbolOpInterface::Trait<ShiftRegOp>::supportsPerFieldSymbols;
  using ::circt::hw::InnerSymbolOpInterface::Trait<ShiftRegOp>::getTargetResult;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("inner_sym"), ::llvm::StringRef("name"), ::llvm::StringRef("numElements"), ::llvm::StringRef("operandSegmentSizes")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getInnerSymAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getInnerSymAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getNameAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getNameAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getNumElementsAttrName() {
    return getAttributeNameForIndex(2);
  }

  static ::mlir::StringAttr getNumElementsAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 2);
  }

  ::mlir::StringAttr getOperandSegmentSizesAttrName() {
   return (*this)->getName().getAttributeNames().back();
  }

  static ::mlir::StringAttr getOperandSegmentSizesAttrName(::mlir::OperationName name) {
   return name.getAttributeNames().back();
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("seq.shiftreg");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::Type> getInput() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::circt::seq::ClockType> getClk() {
    return ::llvm::cast<::mlir::TypedValue<::circt::seq::ClockType>>(*getODSOperands(1).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getClockEnable() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSOperands(2).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getReset() {
    auto operands = getODSOperands(3);
    return operands.empty() ? ::mlir::TypedValue<::mlir::IntegerType>{} : ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*operands.begin());
  }

  ::mlir::TypedValue<::mlir::Type> getResetValue() {
    auto operands = getODSOperands(4);
    return operands.empty() ? ::mlir::TypedValue<::mlir::Type>{} : ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*operands.begin());
  }

  ::mlir::TypedValue<::mlir::Type> getPowerOnValue() {
    auto operands = getODSOperands(5);
    return operands.empty() ? ::mlir::TypedValue<::mlir::Type>{} : ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*operands.begin());
  }

  ::mlir::OpOperand &getInputMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getClkMutable() {
    auto range = getODSOperandIndexAndLength(1);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getClockEnableMutable() {
    auto range = getODSOperandIndexAndLength(2);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::MutableOperandRange getResetMutable();
  ::mlir::MutableOperandRange getResetValueMutable();
  ::mlir::MutableOperandRange getPowerOnValueMutable();
  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::Type> getData() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSResults(0).begin());
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
  ::mlir::IntegerAttr getNumElementsAttr() {
    return ::llvm::cast<::mlir::IntegerAttr>(getProperties().numElements);
  }

  uint64_t getNumElements();
  ::mlir::StringAttr getNameAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::StringAttr>(getProperties().name);
  }

  ::std::optional< ::llvm::StringRef > getName();
  ::circt::hw::InnerSymAttr getInnerSymAttr() {
    return ::llvm::dyn_cast_or_null<::circt::hw::InnerSymAttr>(getProperties().inner_sym);
  }

  ::std::optional<::circt::hw::InnerSymAttr> getInnerSym();
  void setNumElementsAttr(::mlir::IntegerAttr attr) {
    getProperties().numElements = attr;
  }

  void setNumElements(uint64_t attrValue);
  void setNameAttr(::mlir::StringAttr attr) {
    getProperties().name = attr;
  }

  void setName(::std::optional<::llvm::StringRef> attrValue);
  void setInnerSymAttr(::circt::hw::InnerSymAttr attr) {
    getProperties().inner_sym = attr;
  }

  ::mlir::Attribute removeNameAttr() {
      auto attr = getProperties().name;
      getProperties().name = {};
      return attr;
  }

  ::mlir::Attribute removeInnerSymAttr() {
      auto attr = getProperties().inner_sym;
      getProperties().inner_sym = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type data, ::mlir::IntegerAttr numElements, ::mlir::Value input, ::mlir::Value clk, ::mlir::Value clockEnable, /*optional*/::mlir::StringAttr name, /*optional*/::mlir::Value reset, /*optional*/::mlir::Value resetValue, /*optional*/::mlir::Value powerOnValue, /*optional*/::circt::hw::InnerSymAttr inner_sym);
  static ShiftRegOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type data, ::mlir::IntegerAttr numElements, ::mlir::Value input, ::mlir::Value clk, ::mlir::Value clockEnable, /*optional*/::mlir::StringAttr name, /*optional*/::mlir::Value reset, /*optional*/::mlir::Value resetValue, /*optional*/::mlir::Value powerOnValue, /*optional*/::circt::hw::InnerSymAttr inner_sym);
  static ShiftRegOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type data, ::mlir::IntegerAttr numElements, ::mlir::Value input, ::mlir::Value clk, ::mlir::Value clockEnable, /*optional*/::mlir::StringAttr name, /*optional*/::mlir::Value reset, /*optional*/::mlir::Value resetValue, /*optional*/::mlir::Value powerOnValue, /*optional*/::circt::hw::InnerSymAttr inner_sym);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::IntegerAttr numElements, ::mlir::Value input, ::mlir::Value clk, ::mlir::Value clockEnable, /*optional*/::mlir::StringAttr name, /*optional*/::mlir::Value reset, /*optional*/::mlir::Value resetValue, /*optional*/::mlir::Value powerOnValue, /*optional*/::circt::hw::InnerSymAttr inner_sym);
  static ShiftRegOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::IntegerAttr numElements, ::mlir::Value input, ::mlir::Value clk, ::mlir::Value clockEnable, /*optional*/::mlir::StringAttr name, /*optional*/::mlir::Value reset, /*optional*/::mlir::Value resetValue, /*optional*/::mlir::Value powerOnValue, /*optional*/::circt::hw::InnerSymAttr inner_sym);
  static ShiftRegOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::IntegerAttr numElements, ::mlir::Value input, ::mlir::Value clk, ::mlir::Value clockEnable, /*optional*/::mlir::StringAttr name, /*optional*/::mlir::Value reset, /*optional*/::mlir::Value resetValue, /*optional*/::mlir::Value powerOnValue, /*optional*/::circt::hw::InnerSymAttr inner_sym);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::IntegerAttr numElements, ::mlir::Value input, ::mlir::Value clk, ::mlir::Value clockEnable, /*optional*/::mlir::StringAttr name, /*optional*/::mlir::Value reset, /*optional*/::mlir::Value resetValue, /*optional*/::mlir::Value powerOnValue, /*optional*/::circt::hw::InnerSymAttr inner_sym);
  static ShiftRegOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::IntegerAttr numElements, ::mlir::Value input, ::mlir::Value clk, ::mlir::Value clockEnable, /*optional*/::mlir::StringAttr name, /*optional*/::mlir::Value reset, /*optional*/::mlir::Value resetValue, /*optional*/::mlir::Value powerOnValue, /*optional*/::circt::hw::InnerSymAttr inner_sym);
  static ShiftRegOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::IntegerAttr numElements, ::mlir::Value input, ::mlir::Value clk, ::mlir::Value clockEnable, /*optional*/::mlir::StringAttr name, /*optional*/::mlir::Value reset, /*optional*/::mlir::Value resetValue, /*optional*/::mlir::Value powerOnValue, /*optional*/::circt::hw::InnerSymAttr inner_sym);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type data, uint64_t numElements, ::mlir::Value input, ::mlir::Value clk, ::mlir::Value clockEnable, /*optional*/::mlir::StringAttr name, /*optional*/::mlir::Value reset, /*optional*/::mlir::Value resetValue, /*optional*/::mlir::Value powerOnValue, /*optional*/::circt::hw::InnerSymAttr inner_sym);
  static ShiftRegOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type data, uint64_t numElements, ::mlir::Value input, ::mlir::Value clk, ::mlir::Value clockEnable, /*optional*/::mlir::StringAttr name, /*optional*/::mlir::Value reset, /*optional*/::mlir::Value resetValue, /*optional*/::mlir::Value powerOnValue, /*optional*/::circt::hw::InnerSymAttr inner_sym);
  static ShiftRegOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type data, uint64_t numElements, ::mlir::Value input, ::mlir::Value clk, ::mlir::Value clockEnable, /*optional*/::mlir::StringAttr name, /*optional*/::mlir::Value reset, /*optional*/::mlir::Value resetValue, /*optional*/::mlir::Value powerOnValue, /*optional*/::circt::hw::InnerSymAttr inner_sym);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, uint64_t numElements, ::mlir::Value input, ::mlir::Value clk, ::mlir::Value clockEnable, /*optional*/::mlir::StringAttr name, /*optional*/::mlir::Value reset, /*optional*/::mlir::Value resetValue, /*optional*/::mlir::Value powerOnValue, /*optional*/::circt::hw::InnerSymAttr inner_sym);
  static ShiftRegOp create(::mlir::OpBuilder &builder, ::mlir::Location location, uint64_t numElements, ::mlir::Value input, ::mlir::Value clk, ::mlir::Value clockEnable, /*optional*/::mlir::StringAttr name, /*optional*/::mlir::Value reset, /*optional*/::mlir::Value resetValue, /*optional*/::mlir::Value powerOnValue, /*optional*/::circt::hw::InnerSymAttr inner_sym);
  static ShiftRegOp create(::mlir::ImplicitLocOpBuilder &builder, uint64_t numElements, ::mlir::Value input, ::mlir::Value clk, ::mlir::Value clockEnable, /*optional*/::mlir::StringAttr name, /*optional*/::mlir::Value reset, /*optional*/::mlir::Value resetValue, /*optional*/::mlir::Value powerOnValue, /*optional*/::circt::hw::InnerSymAttr inner_sym);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, uint64_t numElements, ::mlir::Value input, ::mlir::Value clk, ::mlir::Value clockEnable, /*optional*/::mlir::StringAttr name, /*optional*/::mlir::Value reset, /*optional*/::mlir::Value resetValue, /*optional*/::mlir::Value powerOnValue, /*optional*/::circt::hw::InnerSymAttr inner_sym);
  static ShiftRegOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, uint64_t numElements, ::mlir::Value input, ::mlir::Value clk, ::mlir::Value clockEnable, /*optional*/::mlir::StringAttr name, /*optional*/::mlir::Value reset, /*optional*/::mlir::Value resetValue, /*optional*/::mlir::Value powerOnValue, /*optional*/::circt::hw::InnerSymAttr inner_sym);
  static ShiftRegOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, uint64_t numElements, ::mlir::Value input, ::mlir::Value clk, ::mlir::Value clockEnable, /*optional*/::mlir::StringAttr name, /*optional*/::mlir::Value reset, /*optional*/::mlir::Value resetValue, /*optional*/::mlir::Value powerOnValue, /*optional*/::circt::hw::InnerSymAttr inner_sym);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ShiftRegOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ShiftRegOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ShiftRegOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ShiftRegOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ShiftRegOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ShiftRegOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ShiftRegOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ShiftRegOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::PropertyRef properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
  static std::optional<size_t> getTargetResultIndex();
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
};

} // namespace circt::seq
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::seq::ShiftRegOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::seq::detail::ShiftRegOpGenericAdaptorBase::Properties)

namespace circt::seq {


//===----------------------------------------------------------------------===//
// ::circt::seq::ToClockOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ToClockOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  ToClockOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("seq.to_clock", odsAttrs.getContext());
  }

  ToClockOpGenericAdaptorBase(ToClockOp op);

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
class ToClockOpGenericAdaptor : public detail::ToClockOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ToClockOpGenericAdaptorBase;
  static constexpr int odsIndex_input = 0;
public:
  ToClockOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ToClockOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : ToClockOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ToClockOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ToClockOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ToClockOpGenericAdaptor(RangeT values, const ToClockOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ToClockOp, typename = std::enable_if_t<std::is_same_v<LateInst, ToClockOp>>>
  ToClockOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class ToClockOpAdaptor : public ToClockOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ToClockOpGenericAdaptor::ToClockOpGenericAdaptor;
  ToClockOpAdaptor(ToClockOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ToClockOp : public ::mlir::Op<ToClockOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::circt::seq::ClockType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ToClockOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ToClockOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_input = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("seq.to_clock");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::IntegerType> getInput() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSOperands(0).begin());
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

  ::mlir::TypedValue<::circt::seq::ClockType> getOutput() {
    return ::llvm::cast<::mlir::TypedValue<::circt::seq::ClockType>>(*getODSResults(0).begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type output, ::mlir::Value input);
  static ToClockOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type output, ::mlir::Value input);
  static ToClockOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type output, ::mlir::Value input);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value input);
  static ToClockOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value input);
  static ToClockOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value input);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value input);
  static ToClockOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value input);
  static ToClockOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value input);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ToClockOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ToClockOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ToClockOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ToClockOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ToClockOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ToClockOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ToClockOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ToClockOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::llvm::LogicalResult canonicalize(ToClockOp op, ::mlir::PatternRewriter &rewriter);
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
  ::mlir::OpFoldResult fold(FoldAdaptor adaptor);
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::PropertyRef properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
};

} // namespace circt::seq
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::seq::ToClockOp)

namespace circt::seq {


//===----------------------------------------------------------------------===//
// ::circt::seq::WritePortOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class WritePortOpGenericAdaptorBase {
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
  WritePortOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("seq.write", odsAttrs.getContext());
  }

  WritePortOpGenericAdaptorBase(WritePortOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
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

  uint64_t getLatency();
};

} // namespace detail
template <typename RangeT>
class WritePortOpGenericAdaptor : public detail::WritePortOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::WritePortOpGenericAdaptorBase;
  static constexpr int odsIndex_memory = 0;
  static constexpr int odsIndex_addresses = 1;
  static constexpr int odsIndex_inData = 2;
  static constexpr int odsIndex_wrEn = 3;
public:
  WritePortOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  WritePortOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : WritePortOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  WritePortOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : WritePortOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  WritePortOpGenericAdaptor(RangeT values, const WritePortOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = WritePortOp, typename = std::enable_if_t<std::is_same_v<LateInst, WritePortOp>>>
  WritePortOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getMemory() {
    return (*getODSOperands(0).begin());
  }

  RangeT getAddresses() {
    return getODSOperands(1);
  }

  ValueT getInData() {
    return (*getODSOperands(2).begin());
  }

  ValueT getWrEn() {
    return (*getODSOperands(3).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class WritePortOpAdaptor : public WritePortOpGenericAdaptor<::mlir::ValueRange> {
public:
  using WritePortOpGenericAdaptor::WritePortOpGenericAdaptor;
  WritePortOpAdaptor(WritePortOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class WritePortOp : public ::mlir::Op<WritePortOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<3>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = WritePortOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = WritePortOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_memory = 0;
  static constexpr int odsIndex_addresses = 1;
  static constexpr int odsIndex_inData = 2;
  static constexpr int odsIndex_wrEn = 3;
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
    return ::llvm::StringLiteral("seq.write");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::circt::seq::HLMemType> getMemory() {
    return ::llvm::cast<::mlir::TypedValue<::circt::seq::HLMemType>>(*getODSOperands(0).begin());
  }

  ::mlir::Operation::operand_range getAddresses() {
    return getODSOperands(1);
  }

  ::mlir::TypedValue<::mlir::Type> getInData() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(2).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getWrEn() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSOperands(3).begin());
  }

  ::mlir::OpOperand &getMemoryMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::MutableOperandRange getAddressesMutable();
  ::mlir::OpOperand &getInDataMutable() {
    auto range = getODSOperandIndexAndLength(2);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getWrEnMutable() {
    auto range = getODSOperandIndexAndLength(3);
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

  uint64_t getLatency();
  void setLatencyAttr(::mlir::IntegerAttr attr) {
    getProperties().latency = attr;
  }

  void setLatency(uint64_t attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value memory, ::mlir::ValueRange addresses, ::mlir::Value inData, ::mlir::Value wrEn, ::mlir::IntegerAttr latency);
  static WritePortOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value memory, ::mlir::ValueRange addresses, ::mlir::Value inData, ::mlir::Value wrEn, ::mlir::IntegerAttr latency);
  static WritePortOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value memory, ::mlir::ValueRange addresses, ::mlir::Value inData, ::mlir::Value wrEn, ::mlir::IntegerAttr latency);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value memory, ::mlir::ValueRange addresses, ::mlir::Value inData, ::mlir::Value wrEn, ::mlir::IntegerAttr latency);
  static WritePortOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value memory, ::mlir::ValueRange addresses, ::mlir::Value inData, ::mlir::Value wrEn, ::mlir::IntegerAttr latency);
  static WritePortOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value memory, ::mlir::ValueRange addresses, ::mlir::Value inData, ::mlir::Value wrEn, ::mlir::IntegerAttr latency);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value memory, ::mlir::ValueRange addresses, ::mlir::Value inData, ::mlir::Value wrEn, uint64_t latency);
  static WritePortOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value memory, ::mlir::ValueRange addresses, ::mlir::Value inData, ::mlir::Value wrEn, uint64_t latency);
  static WritePortOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value memory, ::mlir::ValueRange addresses, ::mlir::Value inData, ::mlir::Value wrEn, uint64_t latency);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value memory, ::mlir::ValueRange addresses, ::mlir::Value inData, ::mlir::Value wrEn, uint64_t latency);
  static WritePortOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value memory, ::mlir::ValueRange addresses, ::mlir::Value inData, ::mlir::Value wrEn, uint64_t latency);
  static WritePortOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value memory, ::mlir::ValueRange addresses, ::mlir::Value inData, ::mlir::Value wrEn, uint64_t latency);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static WritePortOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static WritePortOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static WritePortOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static WritePortOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &p);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::llvm::LogicalResult setPropertiesFromParsedAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
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
};

} // namespace circt::seq
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::seq::WritePortOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::seq::detail::WritePortOpGenericAdaptorBase::Properties)

namespace circt::seq {


//===----------------------------------------------------------------------===//
// ::circt::seq::YieldOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class YieldOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  YieldOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("seq.yield", odsAttrs.getContext());
  }

  YieldOpGenericAdaptorBase(YieldOp op);

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
class YieldOpGenericAdaptor : public detail::YieldOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::YieldOpGenericAdaptorBase;
  static constexpr int odsIndex_operands = 0;
public:
  YieldOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  YieldOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : YieldOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  YieldOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : YieldOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  YieldOpGenericAdaptor(RangeT values, const YieldOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = YieldOp, typename = std::enable_if_t<std::is_same_v<LateInst, YieldOp>>>
  YieldOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class YieldOpAdaptor : public YieldOpGenericAdaptor<::mlir::ValueRange> {
public:
  using YieldOpGenericAdaptor::YieldOpGenericAdaptor;
  YieldOpAdaptor(YieldOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class YieldOp : public ::mlir::Op<YieldOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::HasParent<InitialOp>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::OpTrait::IsTerminator> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = YieldOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = YieldOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_operands = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("seq.yield");
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState);
  static YieldOp create(::mlir::OpBuilder &builder, ::mlir::Location location);
  static YieldOp create(::mlir::ImplicitLocOpBuilder &builder);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands);
  static YieldOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands);
  static YieldOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static YieldOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static YieldOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static YieldOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static YieldOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
};

} // namespace circt::seq
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::seq::YieldOp)


#endif // GET_OP_CLASSES

