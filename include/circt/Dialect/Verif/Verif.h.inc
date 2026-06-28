/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Op Declarations                                                            *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: Verif.td                                                             *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace circt::verif {

/// Assert that a property holds.
class AssertOp;

} // namespace circt::verif
namespace circt::verif {

/// Assume that a property holds.
class AssumeOp;

} // namespace circt::verif
namespace circt::verif {

/// Perform a bounded model check
/// This operation represents a bounded model checking problem explicitly in
/// the IR. The `bound` attribute indicates how many times the `circuit` region
/// should be executed, and `num_regs` indicates the number of registers in the
/// design that have been externalized and appended to the region's
/// inputs/outputs (these values are fed from each `circuit` region execution
/// to the next, as they represent register state, rather than being
/// overwritten with fresh variables like other inputs). `initial_values` is an
/// array containing the initial value of each register - where the register
/// has no initial value, a unit attribute is given. The `circuit` region
/// contains the circuit (alongside the `verif` property checking operations)
/// to be checked.
/// 
/// The `init` region contains the logic to initialize the clock signals, and
/// will be executed once before any other region - it cannot take any
/// arguments, and should return as many `!seq.clock` values as the `circuit`
/// region has `!seq.clock` arguments, followed by any initial arguments of
/// 'state' arguments to be fed to the `loop` region (see below).
/// 
/// The `loop` region contains the logic to advance the clock signals, and will
/// be executed after each execution of the `circuit` region. It should take as
/// arguments as many `!seq.clock` values as the `circuit` region has, and
/// these can be followed by additional 'state' arguments to represent e.g.
/// which clock should be toggled next. The types yielded should be the same,
/// as this region yields the updated clock and state values (this should also
/// match the types yielded by the `init` region).
class BoundedModelCheckingOp;

} // namespace circt::verif
namespace circt::verif {

/// Assert that a property holds, checked on a given clock's
/// ticks and enabled if a given condition holds. Only supports
/// a single clock and a single disable.
class ClockedAssertOp;

} // namespace circt::verif
namespace circt::verif {

/// Assume that a property holds, checked on a given clock's
/// ticks and enabled if a given condition holds. Only supports
/// a single clock and a single disable.
class ClockedAssumeOp;

} // namespace circt::verif
namespace circt::verif {

/// Cover on the holding of a property, checked on a given clock's
/// ticks and enabled if a given condition holds. Only supports
/// a single clock and a single disable.
class ClockedCoverOp;

} // namespace circt::verif
namespace circt::verif {

/// A formal contract
/// This operation creates a new formal contract which can be used to locally
/// verify a part of the IR and provide simplifying substitutions. Contracts
/// contain `verif.require` ops to establish conditions that must hold for a
/// piece of IR to work properly, and `verif.ensure` ops to describe the
/// properties that the piece of IR must guarantees when the requirements hold.
/// Outside of formal verification, operands are simply passed through to the
/// results.
/// 
/// Contracts are checked by extracting them into their own `verif.formal` test
/// and replacing `require` with `assume` and `ensure` with `assert`. The
/// results of the contract are replaced with the operands of the contract.
/// 
/// Contracts are used as simplifications for other verification tasks by
/// inlining them and replacing `require` with `assert` and `ensure` with
/// `assume`. The results of the contract are replaced with symbolic values.
/// 
/// See the documentation of the Verif dialect for more details.
class ContractOp;

} // namespace circt::verif
namespace circt::verif {

/// Ensure that a property can hold.
class CoverOp;

} // namespace circt::verif
namespace circt::verif {

/// A postcondition of a contract
/// This operation specifies a condition that is asserted when checking a
/// contract, and assumed when applying the contract as a simplification.
/// 
/// The `verif.ensure` op is commonly used to specify the conditions that output
/// values from a part of the IR are guaranteed to fulfill, under the condition
/// that all requirements are fulfilled.
class EnsureOp;

} // namespace circt::verif
namespace circt::verif {

/// A formal unit test
/// This operation defines a formal unit test that can be automatically run by
/// various tools. To describe a test, the body of this op should contain the
/// hardware to be tested, alongside any asserts, assumes, and covers to be
/// formally verified. The body can contain instances of other modules, in which
/// case all asserts, assumes, and covers in those modules are also verified.
/// 
/// The `verif.symbolic_value` op can be used to create symbolic values to feed
/// into the hardware to be tested. Testing tools will then try to find concrete
/// values for them that violate any asserts or make any covers true.
/// 
/// #### Example
/// ```
/// verif.formal @AdderTest {myParam = 42, myTag = "hello"} {
///   %0 = verif.symbolic_value : i42
///   %1 = verif.symbolic_value : i42
///   %2 = hw.instance "dut" @Adder(a: %0: i42, b: %1: i42) -> (c: i42)
///   %3 = comb.add %0, %1 : i42
///   %4 = comb.icmp eq %2, %3 : i42
///   verif.assert %4 : i1
/// }
/// ```
/// 
/// #### Parameters
/// The following parameters have a predefined meaning and are interpreted by
/// tools such as `circt-test` to guide execution of tests:
/// 
/// - `ignore`: Indicates whether the test should be ignored and skipped. This
///   can be useful for temporarily disabling tests without having to remove
///   them from the input. Must be a _boolean_ value.
///   ```mlir
///   verif.formal @Foo {ignore = true}
///   ```
/// 
/// - `require_runners`: A list of test runners that may be used to execute this
///   test. This option may be used to force a test to run using one of a few
///   known-good runners, acting like a whitelist. Must be an _array_ of
///   _strings_.
///   ```mlir
///   verif.formal @Foo {require_runners = ["sby", "circt-bmc"]}
///   ```
/// 
/// - `exclude_runners`: A list of test runners that must not be used to execute
///   this test. This option may be used to exclude a few known-bad runners from
///   executing this test, acting like a blacklist. Must be an _array_ of
///   _strings_.
///   ```mlir
///   verif.formal @Foo {exclude_runners = ["sby", "circt-bmc"]}
///   ```
class FormalOp;

} // namespace circt::verif
namespace circt::verif {

/// Creates a formatted string.
/// Creates a formatted string suitable for printing via the `verif.print` op.
/// The formatting syntax is expected to be identical to verilog string
/// formatting to keep things simple for emission.
/// If we in the future would like to be less tied to verilog formatting,
/// please ask your friendly neighbourhood compiler engineer to e.g. implement
/// a `FormatStringOp` which itself may lower to a `FormatVerilogStringOp`.
class FormatVerilogStringOp;

} // namespace circt::verif
namespace circt::verif {

/// Check that a proper reset has been seen.
/// The result of `verif.has_been_reset` reads as 0 immediately after simulation
/// startup and after each power-cycle in a power-aware simulation. The result
/// remains 0 before and during reset and only switches to 1 after the reset is
/// deasserted again.
/// 
/// This is a useful utility to disable the evaluation of assertions and other
/// verification constructs in the IR before the circuit being tested has been
/// properly reset. Verification failures due to uninitialized or randomized
/// initial state can thus be prevented.
/// 
/// Using the result of `verif.has_been_reset` to enable verification is more
/// powerful and proper than just disabling verification during reset. The
/// latter does not properly handle the period of time between simulation
/// startup or power-cycling and the start of reset. `verif.has_been_reset` is
/// guaranteed to produce a 0 value in that period, as well as during the reset.
class HasBeenResetOp;

} // namespace circt::verif
namespace circt::verif {

/// represents a logical equivalence checking problem
/// This operation represents a logic equivalence checking problem explicitly in
/// the IR. There are several possibilities to perform logical equivalence
/// checking. For example, equivalence checking of combinational circuits can be
/// done by constructing a miter circuit and testing whether the result is
/// satisfiable (can be non-zero for some input), or two canonical BDDs could be
/// constructed and compared for identity, etc.
/// 
/// The number and types of the inputs and outputs of the two circuits (and thus
/// also the block arguments and yielded values of both regions) have to match.
/// Otherwise, the two should be considered trivially non-equivalent.
/// 
/// The operation can return a boolean result that is `true` iff equivalence
/// of the two circuits has been proven. The result can be omitted for use-cases
/// which do not allow further processing (e.g., SMT-LIB exporting).
class LogicEquivalenceCheckingOp;

} // namespace circt::verif
namespace circt::verif {

/// Prints a message.
class PrintOp;

} // namespace circt::verif
namespace circt::verif {

/// check if the second module is a refinement of the first module
/// This operation represents a refinement checking problem explicitly in the
/// IR. Given two (purely combinational) circuits A and B with the same
/// signature, B refines A iff for all inputs the set of possible output
/// values of B is a subset of the possible output values of A given the
/// same input.
/// 
/// For strictly deterministic circuits the 'refines' relation is identical to
/// logical equivalence. Informally speaking, refining allows maintaining or
/// reducing the non-determinism of a circuit.
/// 
/// If the signatures of the circuits do not match, the second circuit is
/// trivially assumed to _not_ be a refinement of the first circuit. Sequential
/// elements (i.e., registers and memories) are currently unsupported.
/// 
/// The operation can return a boolean result that is `true` iff the refinement
/// relation has been proven. The result can be omitted for use-cases which do
/// not allow further processing (e.g., SMT-LIB exporting).
class RefinementCheckingOp;

} // namespace circt::verif
namespace circt::verif {

/// A precondition of a contract
/// This operation specifies a condition that is assumed when checking against
/// the contract, and asserted when applying the contract as a simplification.
/// 
/// The `verif.require` op is commonly used to specify the conditions that input
/// values into a part of the IR must fulfill in order for the IR to work as
/// expected, i.e., as outlined in the contract.
class RequireOp;

} // namespace circt::verif
namespace circt::verif {

/// A simulation unit test
/// This operation defines a simulation unit test that can be automatically run
/// by various tools. To describe a test, the body of this op should contain the
/// hardware to be tested, alongside any necessary forms of stimulus generation.
/// 
/// #### Inputs
/// 
/// The body has two block arguments as input values: a "clock" signal of type
/// `!seq.clock` and an "init" signal of type `i1`. The clock signal starts at 0
/// and continuously toggles between 0 and 1 throughout the simulation. The init
/// signal starts at 1, remains 1 during a single 0-to-1 transition of the
/// clock, and then drops to 0 for the remainder of the simulation.
/// 
/// #### Outputs
/// 
/// The body must have a `verif.yield` terminator op with exactly two operands:
/// 
/// The first operand is a "done" signal of type `i1` which indicates the end of
/// the simulation. The simulation stops when the done signal is 1 during a
/// 0-to-1 transition of the clock after the init signal has dropped to 0. No
/// additional clock toggles occur once done has been sampled as 1.
/// 
/// The second operand is a "success" signal of type `i1` which indicates the
/// success of a test as 1, or failure as 0. The signal is sampled at the same
/// time as the done signal. Simulators must signal failure to the operating
/// system through a non-zero exit code.
/// 
/// #### Schedule
/// 
/// The clock and init values adhere to the following schedule during
/// simulation:
/// 
/// | Time      | Clock | Init  | Comment
/// |-----------|-------|-------| ----
/// | t0 (>=0s) | undef | undef | Clock and init may initially be undefined.
/// | t1 (>=t0) | 0     | 1     | Initialization code (e.g., `seq.initial`, Verilog `initial` procedures) may run before or after clock and init change to their initial value.
/// | t2 (>t1)  | 1     | 1     | Single rising clock edge occurs while init is high.
/// | t3 (>t2)  | 0     | 1     | Init may stay during the falling clock edge.
/// | t4 (>=t3) | 0     | 0     | Init goes to 0 before second rising clock edge.
/// | t5 (>t4)  | 1     | 0     | Clock toggles continue indefinitely.
/// | t6 (>t5)  | 0     | 0     |
/// 
/// Simulation termination occurs when the done signal is 1 during a 0-to-1
/// transition of the clock.
/// 
/// #### Example
/// ```
/// verif.simulation @AdderTest {myParam = 42, myTag = "hello"} {
/// ^bb0(%clock: !seq.clock, %init: i1):
///   // Count the first 9001 simulation cycles.
///   %c0_i19 = hw.constant 0 : i19
///   %c1_i19 = hw.constant 1 : i19
///   %c9001_i19 = hw.constant 9001 : i19
///   %count = seq.compreg %0, %clock reset %init, %c0_i19 : i19
///   %done = comb.icmp eq %count, %c9001_i19 : i19
///   %0 = comb.add %count, %c1_i19 : i19
/// 
///   // Generate inputs to the adder.
///   %1, %2 = func.call @generateAdderInputs(%count) : (i19) -> (i42, i42)
///   %3 = hw.instance "dut" @Adder(a: %1: i42, b: %2: i42) -> (c: i42)
/// 
///   // Check results and track failures.
///   %4 = comb.add %1, %2 : i42
///   %5 = comb.icmp eq %3, %4 : i42
///   %true = hw.constant true
///   %success = seq.compreg %6, %clock reset %init, %true : i1
///   %6 = comb.and %success, %5 : i1
/// 
///   verif.yield %done, %success : i1, i1
/// }
/// ```
class SimulationOp;

} // namespace circt::verif
namespace circt::verif {

/// Create a symbolic value for formal verification
/// This operation creates a new symbolic value that can be used to formally
/// verify designs. Verification tools will try to find concrete assignments for
/// symbolic values that violate asserts or make covers true. This value is not
/// fixed - the value taken can vary arbitrarily between timesteps.
class SymbolicValueOp;

} // namespace circt::verif
namespace circt::verif {

/// yields values from a region
class YieldOp;

} // namespace circt::verif
#ifdef GET_OP_CLASSES
#undef GET_OP_CLASSES

namespace circt::verif {


//===----------------------------------------------------------------------===//
// circt::verif::AssertOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class AssertOpGenericAdaptorBase {
public:
  struct Properties {
    using labelTy = ::mlir::StringAttr;
    labelTy label;

    auto getLabel() const {
      auto &propStorage = this->label;
      return ::llvm::dyn_cast_or_null<::mlir::StringAttr>(propStorage);
    }
    void setLabel(const ::mlir::StringAttr &propValue) {
      this->label = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.label == this->label &&
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
  AssertOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("verif.assert", odsAttrs.getContext());
  }

  AssertOpGenericAdaptorBase(AssertOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::StringAttr getLabelAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::StringAttr>(getProperties().label);
    return attr;
  }

  ::std::optional< ::llvm::StringRef > getLabel();
};

} // namespace detail
template <typename RangeT>
class AssertOpGenericAdaptor : public detail::AssertOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::AssertOpGenericAdaptorBase;
  static constexpr int odsIndex_property = 0;
  static constexpr int odsIndex_enable = 1;
public:
  AssertOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  AssertOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : AssertOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  AssertOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : AssertOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  AssertOpGenericAdaptor(RangeT values, const AssertOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = AssertOp, typename = std::enable_if_t<std::is_same_v<LateInst, AssertOp>>>
  AssertOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getProperty() {
    return (*getODSOperands(0).begin());
  }

  ValueT getEnable() {
    auto operands = getODSOperands(1);
    return operands.empty() ? ValueT{} : (*operands.begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class AssertOpAdaptor : public AssertOpGenericAdaptor<::mlir::ValueRange> {
public:
  using AssertOpGenericAdaptor::AssertOpGenericAdaptor;
  AssertOpAdaptor(AssertOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class AssertOp : public ::mlir::Op<AssertOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<1>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = AssertOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = AssertOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_property = 0;
  static constexpr int odsIndex_enable = 1;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("label")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getLabelAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getLabelAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("verif.assert");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::Type> getProperty() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getEnable() {
    auto operands = getODSOperands(1);
    return operands.empty() ? ::mlir::TypedValue<::mlir::IntegerType>{} : ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*operands.begin());
  }

  ::mlir::OpOperand &getPropertyMutable() {
    auto range = getODSOperandIndexAndLength(0);
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

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::llvm::LogicalResult readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state);
  void writeProperties(::mlir::DialectBytecodeWriter &writer);
  ::mlir::StringAttr getLabelAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::StringAttr>(getProperties().label);
  }

  ::std::optional< ::llvm::StringRef > getLabel();
  void setLabelAttr(::mlir::StringAttr attr) {
    getProperties().label = attr;
  }

  void setLabel(::std::optional<::llvm::StringRef> attrValue);
  ::mlir::Attribute removeLabelAttr() {
      auto attr = getProperties().label;
      getProperties().label = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value property, /*optional*/::mlir::Value enable, /*optional*/::mlir::StringAttr label);
  static AssertOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value property, /*optional*/::mlir::Value enable, /*optional*/::mlir::StringAttr label);
  static AssertOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value property, /*optional*/::mlir::Value enable, /*optional*/::mlir::StringAttr label);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value property, /*optional*/::mlir::Value enable, /*optional*/::mlir::StringAttr label);
  static AssertOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value property, /*optional*/::mlir::Value enable, /*optional*/::mlir::StringAttr label);
  static AssertOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value property, /*optional*/::mlir::Value enable, /*optional*/::mlir::StringAttr label);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static AssertOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static AssertOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static AssertOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static AssertOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
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
};

} // namespace circt::verif
MLIR_DECLARE_EXPLICIT_TYPE_ID(circt::verif::AssertOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(circt::verif::detail::AssertOpGenericAdaptorBase::Properties)

namespace circt::verif {


//===----------------------------------------------------------------------===//
// circt::verif::AssumeOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class AssumeOpGenericAdaptorBase {
public:
  struct Properties {
    using labelTy = ::mlir::StringAttr;
    labelTy label;

    auto getLabel() const {
      auto &propStorage = this->label;
      return ::llvm::dyn_cast_or_null<::mlir::StringAttr>(propStorage);
    }
    void setLabel(const ::mlir::StringAttr &propValue) {
      this->label = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.label == this->label &&
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
  AssumeOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("verif.assume", odsAttrs.getContext());
  }

  AssumeOpGenericAdaptorBase(AssumeOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::StringAttr getLabelAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::StringAttr>(getProperties().label);
    return attr;
  }

  ::std::optional< ::llvm::StringRef > getLabel();
};

} // namespace detail
template <typename RangeT>
class AssumeOpGenericAdaptor : public detail::AssumeOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::AssumeOpGenericAdaptorBase;
  static constexpr int odsIndex_property = 0;
  static constexpr int odsIndex_enable = 1;
public:
  AssumeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  AssumeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : AssumeOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  AssumeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : AssumeOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  AssumeOpGenericAdaptor(RangeT values, const AssumeOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = AssumeOp, typename = std::enable_if_t<std::is_same_v<LateInst, AssumeOp>>>
  AssumeOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getProperty() {
    return (*getODSOperands(0).begin());
  }

  ValueT getEnable() {
    auto operands = getODSOperands(1);
    return operands.empty() ? ValueT{} : (*operands.begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class AssumeOpAdaptor : public AssumeOpGenericAdaptor<::mlir::ValueRange> {
public:
  using AssumeOpGenericAdaptor::AssumeOpGenericAdaptor;
  AssumeOpAdaptor(AssumeOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class AssumeOp : public ::mlir::Op<AssumeOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<1>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = AssumeOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = AssumeOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_property = 0;
  static constexpr int odsIndex_enable = 1;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("label")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getLabelAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getLabelAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("verif.assume");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::Type> getProperty() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getEnable() {
    auto operands = getODSOperands(1);
    return operands.empty() ? ::mlir::TypedValue<::mlir::IntegerType>{} : ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*operands.begin());
  }

  ::mlir::OpOperand &getPropertyMutable() {
    auto range = getODSOperandIndexAndLength(0);
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

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::llvm::LogicalResult readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state);
  void writeProperties(::mlir::DialectBytecodeWriter &writer);
  ::mlir::StringAttr getLabelAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::StringAttr>(getProperties().label);
  }

  ::std::optional< ::llvm::StringRef > getLabel();
  void setLabelAttr(::mlir::StringAttr attr) {
    getProperties().label = attr;
  }

  void setLabel(::std::optional<::llvm::StringRef> attrValue);
  ::mlir::Attribute removeLabelAttr() {
      auto attr = getProperties().label;
      getProperties().label = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value property, /*optional*/::mlir::Value enable, /*optional*/::mlir::StringAttr label);
  static AssumeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value property, /*optional*/::mlir::Value enable, /*optional*/::mlir::StringAttr label);
  static AssumeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value property, /*optional*/::mlir::Value enable, /*optional*/::mlir::StringAttr label);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value property, /*optional*/::mlir::Value enable, /*optional*/::mlir::StringAttr label);
  static AssumeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value property, /*optional*/::mlir::Value enable, /*optional*/::mlir::StringAttr label);
  static AssumeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value property, /*optional*/::mlir::Value enable, /*optional*/::mlir::StringAttr label);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static AssumeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static AssumeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static AssumeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static AssumeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
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
};

} // namespace circt::verif
MLIR_DECLARE_EXPLICIT_TYPE_ID(circt::verif::AssumeOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(circt::verif::detail::AssumeOpGenericAdaptorBase::Properties)

namespace circt::verif {


//===----------------------------------------------------------------------===//
// circt::verif::BoundedModelCheckingOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class BoundedModelCheckingOpGenericAdaptorBase {
public:
  struct Properties {
    using boundTy = ::mlir::IntegerAttr;
    boundTy bound;

    auto getBound() const {
      auto &propStorage = this->bound;
      return ::llvm::cast<::mlir::IntegerAttr>(propStorage);
    }
    void setBound(const ::mlir::IntegerAttr &propValue) {
      this->bound = propValue;
    }
    using initial_valuesTy = ::mlir::ArrayAttr;
    initial_valuesTy initial_values;

    auto getInitialValues() const {
      auto &propStorage = this->initial_values;
      return ::llvm::cast<::mlir::ArrayAttr>(propStorage);
    }
    void setInitialValues(const ::mlir::ArrayAttr &propValue) {
      this->initial_values = propValue;
    }
    using num_regsTy = ::mlir::IntegerAttr;
    num_regsTy num_regs;

    auto getNumRegs() const {
      auto &propStorage = this->num_regs;
      return ::llvm::cast<::mlir::IntegerAttr>(propStorage);
    }
    void setNumRegs(const ::mlir::IntegerAttr &propValue) {
      this->num_regs = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.bound == this->bound &&
        rhs.initial_values == this->initial_values &&
        rhs.num_regs == this->num_regs &&
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
  BoundedModelCheckingOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("verif.bmc", odsAttrs.getContext());
  }

  BoundedModelCheckingOpGenericAdaptorBase(BoundedModelCheckingOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::IntegerAttr getBoundAttr() {
    auto attr = ::llvm::cast<::mlir::IntegerAttr>(getProperties().bound);
    return attr;
  }

  uint32_t getBound();
  ::mlir::IntegerAttr getNumRegsAttr() {
    auto attr = ::llvm::cast<::mlir::IntegerAttr>(getProperties().num_regs);
    return attr;
  }

  uint32_t getNumRegs();
  ::mlir::ArrayAttr getInitialValuesAttr() {
    auto attr = ::llvm::cast<::mlir::ArrayAttr>(getProperties().initial_values);
    return attr;
  }

  ::mlir::ArrayAttr getInitialValues();
  ::mlir::Region &getInit() {
    return *odsRegions[0];
  }

  ::mlir::Region &getLoop() {
    return *odsRegions[1];
  }

  ::mlir::Region &getCircuit() {
    return *odsRegions[2];
  }

  ::mlir::RegionRange getRegions() {
    return odsRegions;
  }

};

} // namespace detail
template <typename RangeT>
class BoundedModelCheckingOpGenericAdaptor : public detail::BoundedModelCheckingOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::BoundedModelCheckingOpGenericAdaptorBase;
public:
  BoundedModelCheckingOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  BoundedModelCheckingOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : BoundedModelCheckingOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  BoundedModelCheckingOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : BoundedModelCheckingOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  BoundedModelCheckingOpGenericAdaptor(RangeT values, const BoundedModelCheckingOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = BoundedModelCheckingOp, typename = std::enable_if_t<std::is_same_v<LateInst, BoundedModelCheckingOp>>>
  BoundedModelCheckingOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class BoundedModelCheckingOpAdaptor : public BoundedModelCheckingOpGenericAdaptor<::mlir::ValueRange> {
public:
  using BoundedModelCheckingOpGenericAdaptor::BoundedModelCheckingOpGenericAdaptor;
  BoundedModelCheckingOpAdaptor(BoundedModelCheckingOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class BoundedModelCheckingOp : public ::mlir::Op<BoundedModelCheckingOp, ::mlir::OpTrait::NRegions<3>::Impl, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::IntegerType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::SingleBlock, ::mlir::OpTrait::SingleBlockImplicitTerminator<verif::YieldOp>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::OpTrait::IsIsolatedFromAbove, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = BoundedModelCheckingOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = BoundedModelCheckingOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("bound"), ::llvm::StringRef("initial_values"), ::llvm::StringRef("num_regs")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getBoundAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getBoundAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getInitialValuesAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getInitialValuesAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getNumRegsAttrName() {
    return getAttributeNameForIndex(2);
  }

  static ::mlir::StringAttr getNumRegsAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 2);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("verif.bmc");
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

  ::mlir::TypedValue<::mlir::IntegerType> getResult() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSResults(0).begin());
  }

  ::mlir::Region &getInit() {
    return (*this)->getRegion(0);
  }

  ::mlir::Region &getLoop() {
    return (*this)->getRegion(1);
  }

  ::mlir::Region &getCircuit() {
    return (*this)->getRegion(2);
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
  ::mlir::IntegerAttr getBoundAttr() {
    return ::llvm::cast<::mlir::IntegerAttr>(getProperties().bound);
  }

  uint32_t getBound();
  ::mlir::IntegerAttr getNumRegsAttr() {
    return ::llvm::cast<::mlir::IntegerAttr>(getProperties().num_regs);
  }

  uint32_t getNumRegs();
  ::mlir::ArrayAttr getInitialValuesAttr() {
    return ::llvm::cast<::mlir::ArrayAttr>(getProperties().initial_values);
  }

  ::mlir::ArrayAttr getInitialValues();
  void setBoundAttr(::mlir::IntegerAttr attr) {
    getProperties().bound = attr;
  }

  void setBound(uint32_t attrValue);
  void setNumRegsAttr(::mlir::IntegerAttr attr) {
    getProperties().num_regs = attr;
  }

  void setNumRegs(uint32_t attrValue);
  void setInitialValuesAttr(::mlir::ArrayAttr attr) {
    getProperties().initial_values = attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::IntegerAttr bound, ::mlir::IntegerAttr num_regs, ::mlir::ArrayAttr initial_values);
  static BoundedModelCheckingOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::IntegerAttr bound, ::mlir::IntegerAttr num_regs, ::mlir::ArrayAttr initial_values);
  static BoundedModelCheckingOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::IntegerAttr bound, ::mlir::IntegerAttr num_regs, ::mlir::ArrayAttr initial_values);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::IntegerAttr bound, ::mlir::IntegerAttr num_regs, ::mlir::ArrayAttr initial_values);
  static BoundedModelCheckingOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::IntegerAttr bound, ::mlir::IntegerAttr num_regs, ::mlir::ArrayAttr initial_values);
  static BoundedModelCheckingOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::IntegerAttr bound, ::mlir::IntegerAttr num_regs, ::mlir::ArrayAttr initial_values);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::IntegerAttr bound, ::mlir::IntegerAttr num_regs, ::mlir::ArrayAttr initial_values);
  static BoundedModelCheckingOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::IntegerAttr bound, ::mlir::IntegerAttr num_regs, ::mlir::ArrayAttr initial_values);
  static BoundedModelCheckingOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::IntegerAttr bound, ::mlir::IntegerAttr num_regs, ::mlir::ArrayAttr initial_values);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, uint32_t bound, uint32_t num_regs, ::mlir::ArrayAttr initial_values);
  static BoundedModelCheckingOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, uint32_t bound, uint32_t num_regs, ::mlir::ArrayAttr initial_values);
  static BoundedModelCheckingOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, uint32_t bound, uint32_t num_regs, ::mlir::ArrayAttr initial_values);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, uint32_t bound, uint32_t num_regs, ::mlir::ArrayAttr initial_values);
  static BoundedModelCheckingOp create(::mlir::OpBuilder &builder, ::mlir::Location location, uint32_t bound, uint32_t num_regs, ::mlir::ArrayAttr initial_values);
  static BoundedModelCheckingOp create(::mlir::ImplicitLocOpBuilder &builder, uint32_t bound, uint32_t num_regs, ::mlir::ArrayAttr initial_values);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, uint32_t bound, uint32_t num_regs, ::mlir::ArrayAttr initial_values);
  static BoundedModelCheckingOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, uint32_t bound, uint32_t num_regs, ::mlir::ArrayAttr initial_values);
  static BoundedModelCheckingOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, uint32_t bound, uint32_t num_regs, ::mlir::ArrayAttr initial_values);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static BoundedModelCheckingOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static BoundedModelCheckingOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static BoundedModelCheckingOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static BoundedModelCheckingOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static BoundedModelCheckingOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static BoundedModelCheckingOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static BoundedModelCheckingOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static BoundedModelCheckingOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verifyRegions();
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::PropertyRef properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
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

} // namespace circt::verif
MLIR_DECLARE_EXPLICIT_TYPE_ID(circt::verif::BoundedModelCheckingOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(circt::verif::detail::BoundedModelCheckingOpGenericAdaptorBase::Properties)

namespace circt::verif {


//===----------------------------------------------------------------------===//
// circt::verif::ClockedAssertOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ClockedAssertOpGenericAdaptorBase {
public:
  struct Properties {
    using edgeTy = circt::verif::ClockEdgeAttr;
    edgeTy edge;

    auto getEdge() const {
      auto &propStorage = this->edge;
      return ::llvm::cast<circt::verif::ClockEdgeAttr>(propStorage);
    }
    void setEdge(const circt::verif::ClockEdgeAttr &propValue) {
      this->edge = propValue;
    }
    using labelTy = ::mlir::StringAttr;
    labelTy label;

    auto getLabel() const {
      auto &propStorage = this->label;
      return ::llvm::dyn_cast_or_null<::mlir::StringAttr>(propStorage);
    }
    void setLabel(const ::mlir::StringAttr &propValue) {
      this->label = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.edge == this->edge &&
        rhs.label == this->label &&
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
  ClockedAssertOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("verif.clocked_assert", odsAttrs.getContext());
  }

  ClockedAssertOpGenericAdaptorBase(ClockedAssertOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  circt::verif::ClockEdgeAttr getEdgeAttr() {
    auto attr = ::llvm::cast<circt::verif::ClockEdgeAttr>(getProperties().edge);
    return attr;
  }

  circt::verif::ClockEdge getEdge();
  ::mlir::StringAttr getLabelAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::StringAttr>(getProperties().label);
    return attr;
  }

  ::std::optional< ::llvm::StringRef > getLabel();
};

} // namespace detail
template <typename RangeT>
class ClockedAssertOpGenericAdaptor : public detail::ClockedAssertOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ClockedAssertOpGenericAdaptorBase;
  static constexpr int odsIndex_property = 0;
  static constexpr int odsIndex_clock = 1;
  static constexpr int odsIndex_enable = 2;
public:
  ClockedAssertOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ClockedAssertOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : ClockedAssertOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ClockedAssertOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ClockedAssertOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ClockedAssertOpGenericAdaptor(RangeT values, const ClockedAssertOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ClockedAssertOp, typename = std::enable_if_t<std::is_same_v<LateInst, ClockedAssertOp>>>
  ClockedAssertOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getProperty() {
    return (*getODSOperands(0).begin());
  }

  ValueT getClock() {
    return (*getODSOperands(1).begin());
  }

  ValueT getEnable() {
    auto operands = getODSOperands(2);
    return operands.empty() ? ValueT{} : (*operands.begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class ClockedAssertOpAdaptor : public ClockedAssertOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ClockedAssertOpGenericAdaptor::ClockedAssertOpGenericAdaptor;
  ClockedAssertOpAdaptor(ClockedAssertOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ClockedAssertOp : public ::mlir::Op<ClockedAssertOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<2>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ClockedAssertOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ClockedAssertOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_property = 0;
  static constexpr int odsIndex_clock = 1;
  static constexpr int odsIndex_enable = 2;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("edge"), ::llvm::StringRef("label")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getEdgeAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getEdgeAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getLabelAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getLabelAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("verif.clocked_assert");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::Type> getProperty() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getClock() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSOperands(1).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getEnable() {
    auto operands = getODSOperands(2);
    return operands.empty() ? ::mlir::TypedValue<::mlir::IntegerType>{} : ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*operands.begin());
  }

  ::mlir::OpOperand &getPropertyMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getClockMutable() {
    auto range = getODSOperandIndexAndLength(1);
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

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::llvm::LogicalResult readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state);
  void writeProperties(::mlir::DialectBytecodeWriter &writer);
  circt::verif::ClockEdgeAttr getEdgeAttr() {
    return ::llvm::cast<circt::verif::ClockEdgeAttr>(getProperties().edge);
  }

  circt::verif::ClockEdge getEdge();
  ::mlir::StringAttr getLabelAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::StringAttr>(getProperties().label);
  }

  ::std::optional< ::llvm::StringRef > getLabel();
  void setEdgeAttr(circt::verif::ClockEdgeAttr attr) {
    getProperties().edge = attr;
  }

  void setEdge(circt::verif::ClockEdge attrValue);
  void setLabelAttr(::mlir::StringAttr attr) {
    getProperties().label = attr;
  }

  void setLabel(::std::optional<::llvm::StringRef> attrValue);
  ::mlir::Attribute removeLabelAttr() {
      auto attr = getProperties().label;
      getProperties().label = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value property, circt::verif::ClockEdgeAttr edge, ::mlir::Value clock, /*optional*/::mlir::Value enable, /*optional*/::mlir::StringAttr label);
  static ClockedAssertOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value property, circt::verif::ClockEdgeAttr edge, ::mlir::Value clock, /*optional*/::mlir::Value enable, /*optional*/::mlir::StringAttr label);
  static ClockedAssertOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value property, circt::verif::ClockEdgeAttr edge, ::mlir::Value clock, /*optional*/::mlir::Value enable, /*optional*/::mlir::StringAttr label);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value property, circt::verif::ClockEdgeAttr edge, ::mlir::Value clock, /*optional*/::mlir::Value enable, /*optional*/::mlir::StringAttr label);
  static ClockedAssertOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value property, circt::verif::ClockEdgeAttr edge, ::mlir::Value clock, /*optional*/::mlir::Value enable, /*optional*/::mlir::StringAttr label);
  static ClockedAssertOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value property, circt::verif::ClockEdgeAttr edge, ::mlir::Value clock, /*optional*/::mlir::Value enable, /*optional*/::mlir::StringAttr label);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value property, circt::verif::ClockEdge edge, ::mlir::Value clock, /*optional*/::mlir::Value enable, /*optional*/::mlir::StringAttr label);
  static ClockedAssertOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value property, circt::verif::ClockEdge edge, ::mlir::Value clock, /*optional*/::mlir::Value enable, /*optional*/::mlir::StringAttr label);
  static ClockedAssertOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value property, circt::verif::ClockEdge edge, ::mlir::Value clock, /*optional*/::mlir::Value enable, /*optional*/::mlir::StringAttr label);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value property, circt::verif::ClockEdge edge, ::mlir::Value clock, /*optional*/::mlir::Value enable, /*optional*/::mlir::StringAttr label);
  static ClockedAssertOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value property, circt::verif::ClockEdge edge, ::mlir::Value clock, /*optional*/::mlir::Value enable, /*optional*/::mlir::StringAttr label);
  static ClockedAssertOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value property, circt::verif::ClockEdge edge, ::mlir::Value clock, /*optional*/::mlir::Value enable, /*optional*/::mlir::StringAttr label);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ClockedAssertOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ClockedAssertOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ClockedAssertOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ClockedAssertOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
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

} // namespace circt::verif
MLIR_DECLARE_EXPLICIT_TYPE_ID(circt::verif::ClockedAssertOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(circt::verif::detail::ClockedAssertOpGenericAdaptorBase::Properties)

namespace circt::verif {


//===----------------------------------------------------------------------===//
// circt::verif::ClockedAssumeOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ClockedAssumeOpGenericAdaptorBase {
public:
  struct Properties {
    using edgeTy = circt::verif::ClockEdgeAttr;
    edgeTy edge;

    auto getEdge() const {
      auto &propStorage = this->edge;
      return ::llvm::cast<circt::verif::ClockEdgeAttr>(propStorage);
    }
    void setEdge(const circt::verif::ClockEdgeAttr &propValue) {
      this->edge = propValue;
    }
    using labelTy = ::mlir::StringAttr;
    labelTy label;

    auto getLabel() const {
      auto &propStorage = this->label;
      return ::llvm::dyn_cast_or_null<::mlir::StringAttr>(propStorage);
    }
    void setLabel(const ::mlir::StringAttr &propValue) {
      this->label = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.edge == this->edge &&
        rhs.label == this->label &&
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
  ClockedAssumeOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("verif.clocked_assume", odsAttrs.getContext());
  }

  ClockedAssumeOpGenericAdaptorBase(ClockedAssumeOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  circt::verif::ClockEdgeAttr getEdgeAttr() {
    auto attr = ::llvm::cast<circt::verif::ClockEdgeAttr>(getProperties().edge);
    return attr;
  }

  circt::verif::ClockEdge getEdge();
  ::mlir::StringAttr getLabelAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::StringAttr>(getProperties().label);
    return attr;
  }

  ::std::optional< ::llvm::StringRef > getLabel();
};

} // namespace detail
template <typename RangeT>
class ClockedAssumeOpGenericAdaptor : public detail::ClockedAssumeOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ClockedAssumeOpGenericAdaptorBase;
  static constexpr int odsIndex_property = 0;
  static constexpr int odsIndex_clock = 1;
  static constexpr int odsIndex_enable = 2;
public:
  ClockedAssumeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ClockedAssumeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : ClockedAssumeOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ClockedAssumeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ClockedAssumeOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ClockedAssumeOpGenericAdaptor(RangeT values, const ClockedAssumeOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ClockedAssumeOp, typename = std::enable_if_t<std::is_same_v<LateInst, ClockedAssumeOp>>>
  ClockedAssumeOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getProperty() {
    return (*getODSOperands(0).begin());
  }

  ValueT getClock() {
    return (*getODSOperands(1).begin());
  }

  ValueT getEnable() {
    auto operands = getODSOperands(2);
    return operands.empty() ? ValueT{} : (*operands.begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class ClockedAssumeOpAdaptor : public ClockedAssumeOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ClockedAssumeOpGenericAdaptor::ClockedAssumeOpGenericAdaptor;
  ClockedAssumeOpAdaptor(ClockedAssumeOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ClockedAssumeOp : public ::mlir::Op<ClockedAssumeOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<2>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ClockedAssumeOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ClockedAssumeOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_property = 0;
  static constexpr int odsIndex_clock = 1;
  static constexpr int odsIndex_enable = 2;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("edge"), ::llvm::StringRef("label")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getEdgeAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getEdgeAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getLabelAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getLabelAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("verif.clocked_assume");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::Type> getProperty() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getClock() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSOperands(1).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getEnable() {
    auto operands = getODSOperands(2);
    return operands.empty() ? ::mlir::TypedValue<::mlir::IntegerType>{} : ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*operands.begin());
  }

  ::mlir::OpOperand &getPropertyMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getClockMutable() {
    auto range = getODSOperandIndexAndLength(1);
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

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::llvm::LogicalResult readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state);
  void writeProperties(::mlir::DialectBytecodeWriter &writer);
  circt::verif::ClockEdgeAttr getEdgeAttr() {
    return ::llvm::cast<circt::verif::ClockEdgeAttr>(getProperties().edge);
  }

  circt::verif::ClockEdge getEdge();
  ::mlir::StringAttr getLabelAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::StringAttr>(getProperties().label);
  }

  ::std::optional< ::llvm::StringRef > getLabel();
  void setEdgeAttr(circt::verif::ClockEdgeAttr attr) {
    getProperties().edge = attr;
  }

  void setEdge(circt::verif::ClockEdge attrValue);
  void setLabelAttr(::mlir::StringAttr attr) {
    getProperties().label = attr;
  }

  void setLabel(::std::optional<::llvm::StringRef> attrValue);
  ::mlir::Attribute removeLabelAttr() {
      auto attr = getProperties().label;
      getProperties().label = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value property, circt::verif::ClockEdgeAttr edge, ::mlir::Value clock, /*optional*/::mlir::Value enable, /*optional*/::mlir::StringAttr label);
  static ClockedAssumeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value property, circt::verif::ClockEdgeAttr edge, ::mlir::Value clock, /*optional*/::mlir::Value enable, /*optional*/::mlir::StringAttr label);
  static ClockedAssumeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value property, circt::verif::ClockEdgeAttr edge, ::mlir::Value clock, /*optional*/::mlir::Value enable, /*optional*/::mlir::StringAttr label);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value property, circt::verif::ClockEdgeAttr edge, ::mlir::Value clock, /*optional*/::mlir::Value enable, /*optional*/::mlir::StringAttr label);
  static ClockedAssumeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value property, circt::verif::ClockEdgeAttr edge, ::mlir::Value clock, /*optional*/::mlir::Value enable, /*optional*/::mlir::StringAttr label);
  static ClockedAssumeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value property, circt::verif::ClockEdgeAttr edge, ::mlir::Value clock, /*optional*/::mlir::Value enable, /*optional*/::mlir::StringAttr label);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value property, circt::verif::ClockEdge edge, ::mlir::Value clock, /*optional*/::mlir::Value enable, /*optional*/::mlir::StringAttr label);
  static ClockedAssumeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value property, circt::verif::ClockEdge edge, ::mlir::Value clock, /*optional*/::mlir::Value enable, /*optional*/::mlir::StringAttr label);
  static ClockedAssumeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value property, circt::verif::ClockEdge edge, ::mlir::Value clock, /*optional*/::mlir::Value enable, /*optional*/::mlir::StringAttr label);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value property, circt::verif::ClockEdge edge, ::mlir::Value clock, /*optional*/::mlir::Value enable, /*optional*/::mlir::StringAttr label);
  static ClockedAssumeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value property, circt::verif::ClockEdge edge, ::mlir::Value clock, /*optional*/::mlir::Value enable, /*optional*/::mlir::StringAttr label);
  static ClockedAssumeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value property, circt::verif::ClockEdge edge, ::mlir::Value clock, /*optional*/::mlir::Value enable, /*optional*/::mlir::StringAttr label);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ClockedAssumeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ClockedAssumeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ClockedAssumeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ClockedAssumeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
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

} // namespace circt::verif
MLIR_DECLARE_EXPLICIT_TYPE_ID(circt::verif::ClockedAssumeOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(circt::verif::detail::ClockedAssumeOpGenericAdaptorBase::Properties)

namespace circt::verif {


//===----------------------------------------------------------------------===//
// circt::verif::ClockedCoverOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ClockedCoverOpGenericAdaptorBase {
public:
  struct Properties {
    using edgeTy = circt::verif::ClockEdgeAttr;
    edgeTy edge;

    auto getEdge() const {
      auto &propStorage = this->edge;
      return ::llvm::cast<circt::verif::ClockEdgeAttr>(propStorage);
    }
    void setEdge(const circt::verif::ClockEdgeAttr &propValue) {
      this->edge = propValue;
    }
    using labelTy = ::mlir::StringAttr;
    labelTy label;

    auto getLabel() const {
      auto &propStorage = this->label;
      return ::llvm::dyn_cast_or_null<::mlir::StringAttr>(propStorage);
    }
    void setLabel(const ::mlir::StringAttr &propValue) {
      this->label = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.edge == this->edge &&
        rhs.label == this->label &&
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
  ClockedCoverOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("verif.clocked_cover", odsAttrs.getContext());
  }

  ClockedCoverOpGenericAdaptorBase(ClockedCoverOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  circt::verif::ClockEdgeAttr getEdgeAttr() {
    auto attr = ::llvm::cast<circt::verif::ClockEdgeAttr>(getProperties().edge);
    return attr;
  }

  circt::verif::ClockEdge getEdge();
  ::mlir::StringAttr getLabelAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::StringAttr>(getProperties().label);
    return attr;
  }

  ::std::optional< ::llvm::StringRef > getLabel();
};

} // namespace detail
template <typename RangeT>
class ClockedCoverOpGenericAdaptor : public detail::ClockedCoverOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ClockedCoverOpGenericAdaptorBase;
  static constexpr int odsIndex_property = 0;
  static constexpr int odsIndex_clock = 1;
  static constexpr int odsIndex_enable = 2;
public:
  ClockedCoverOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ClockedCoverOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : ClockedCoverOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ClockedCoverOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ClockedCoverOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ClockedCoverOpGenericAdaptor(RangeT values, const ClockedCoverOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ClockedCoverOp, typename = std::enable_if_t<std::is_same_v<LateInst, ClockedCoverOp>>>
  ClockedCoverOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getProperty() {
    return (*getODSOperands(0).begin());
  }

  ValueT getClock() {
    return (*getODSOperands(1).begin());
  }

  ValueT getEnable() {
    auto operands = getODSOperands(2);
    return operands.empty() ? ValueT{} : (*operands.begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class ClockedCoverOpAdaptor : public ClockedCoverOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ClockedCoverOpGenericAdaptor::ClockedCoverOpGenericAdaptor;
  ClockedCoverOpAdaptor(ClockedCoverOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ClockedCoverOp : public ::mlir::Op<ClockedCoverOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<2>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ClockedCoverOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ClockedCoverOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_property = 0;
  static constexpr int odsIndex_clock = 1;
  static constexpr int odsIndex_enable = 2;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("edge"), ::llvm::StringRef("label")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getEdgeAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getEdgeAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getLabelAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getLabelAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("verif.clocked_cover");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::Type> getProperty() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getClock() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSOperands(1).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getEnable() {
    auto operands = getODSOperands(2);
    return operands.empty() ? ::mlir::TypedValue<::mlir::IntegerType>{} : ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*operands.begin());
  }

  ::mlir::OpOperand &getPropertyMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getClockMutable() {
    auto range = getODSOperandIndexAndLength(1);
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

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::llvm::LogicalResult readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state);
  void writeProperties(::mlir::DialectBytecodeWriter &writer);
  circt::verif::ClockEdgeAttr getEdgeAttr() {
    return ::llvm::cast<circt::verif::ClockEdgeAttr>(getProperties().edge);
  }

  circt::verif::ClockEdge getEdge();
  ::mlir::StringAttr getLabelAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::StringAttr>(getProperties().label);
  }

  ::std::optional< ::llvm::StringRef > getLabel();
  void setEdgeAttr(circt::verif::ClockEdgeAttr attr) {
    getProperties().edge = attr;
  }

  void setEdge(circt::verif::ClockEdge attrValue);
  void setLabelAttr(::mlir::StringAttr attr) {
    getProperties().label = attr;
  }

  void setLabel(::std::optional<::llvm::StringRef> attrValue);
  ::mlir::Attribute removeLabelAttr() {
      auto attr = getProperties().label;
      getProperties().label = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value property, circt::verif::ClockEdgeAttr edge, ::mlir::Value clock, /*optional*/::mlir::Value enable, /*optional*/::mlir::StringAttr label);
  static ClockedCoverOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value property, circt::verif::ClockEdgeAttr edge, ::mlir::Value clock, /*optional*/::mlir::Value enable, /*optional*/::mlir::StringAttr label);
  static ClockedCoverOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value property, circt::verif::ClockEdgeAttr edge, ::mlir::Value clock, /*optional*/::mlir::Value enable, /*optional*/::mlir::StringAttr label);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value property, circt::verif::ClockEdgeAttr edge, ::mlir::Value clock, /*optional*/::mlir::Value enable, /*optional*/::mlir::StringAttr label);
  static ClockedCoverOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value property, circt::verif::ClockEdgeAttr edge, ::mlir::Value clock, /*optional*/::mlir::Value enable, /*optional*/::mlir::StringAttr label);
  static ClockedCoverOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value property, circt::verif::ClockEdgeAttr edge, ::mlir::Value clock, /*optional*/::mlir::Value enable, /*optional*/::mlir::StringAttr label);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value property, circt::verif::ClockEdge edge, ::mlir::Value clock, /*optional*/::mlir::Value enable, /*optional*/::mlir::StringAttr label);
  static ClockedCoverOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value property, circt::verif::ClockEdge edge, ::mlir::Value clock, /*optional*/::mlir::Value enable, /*optional*/::mlir::StringAttr label);
  static ClockedCoverOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value property, circt::verif::ClockEdge edge, ::mlir::Value clock, /*optional*/::mlir::Value enable, /*optional*/::mlir::StringAttr label);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value property, circt::verif::ClockEdge edge, ::mlir::Value clock, /*optional*/::mlir::Value enable, /*optional*/::mlir::StringAttr label);
  static ClockedCoverOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value property, circt::verif::ClockEdge edge, ::mlir::Value clock, /*optional*/::mlir::Value enable, /*optional*/::mlir::StringAttr label);
  static ClockedCoverOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value property, circt::verif::ClockEdge edge, ::mlir::Value clock, /*optional*/::mlir::Value enable, /*optional*/::mlir::StringAttr label);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ClockedCoverOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ClockedCoverOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ClockedCoverOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ClockedCoverOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
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

} // namespace circt::verif
MLIR_DECLARE_EXPLICIT_TYPE_ID(circt::verif::ClockedCoverOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(circt::verif::detail::ClockedCoverOpGenericAdaptorBase::Properties)

namespace circt::verif {


//===----------------------------------------------------------------------===//
// circt::verif::ContractOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ContractOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  ContractOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("verif.contract", odsAttrs.getContext());
  }

  ContractOpGenericAdaptorBase(ContractOp op);

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
class ContractOpGenericAdaptor : public detail::ContractOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ContractOpGenericAdaptorBase;
  static constexpr int odsIndex_inputs = 0;
public:
  ContractOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ContractOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : ContractOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ContractOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ContractOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ContractOpGenericAdaptor(RangeT values, const ContractOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ContractOp, typename = std::enable_if_t<std::is_same_v<LateInst, ContractOp>>>
  ContractOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class ContractOpAdaptor : public ContractOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ContractOpGenericAdaptor::ContractOpGenericAdaptor;
  ContractOpAdaptor(ContractOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ContractOp : public ::mlir::Op<ContractOp, ::mlir::OpTrait::OneRegion, ::mlir::OpTrait::VariadicResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::NoRegionArguments, ::mlir::OpTrait::NoTerminator, ::mlir::OpTrait::SingleBlock, ::mlir::OpTrait::OpInvariants, ::mlir::RegionKindInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ContractOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ContractOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_inputs = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("verif.contract");
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

  ::mlir::Operation::result_range getOutputs() {
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
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ContractOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ContractOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ContractOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ContractOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
  static RegionKind getRegionKind(unsigned index) {
    return RegionKind::Graph;
  }
};

} // namespace circt::verif
MLIR_DECLARE_EXPLICIT_TYPE_ID(circt::verif::ContractOp)

namespace circt::verif {


//===----------------------------------------------------------------------===//
// circt::verif::CoverOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class CoverOpGenericAdaptorBase {
public:
  struct Properties {
    using labelTy = ::mlir::StringAttr;
    labelTy label;

    auto getLabel() const {
      auto &propStorage = this->label;
      return ::llvm::dyn_cast_or_null<::mlir::StringAttr>(propStorage);
    }
    void setLabel(const ::mlir::StringAttr &propValue) {
      this->label = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.label == this->label &&
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
  CoverOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("verif.cover", odsAttrs.getContext());
  }

  CoverOpGenericAdaptorBase(CoverOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::StringAttr getLabelAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::StringAttr>(getProperties().label);
    return attr;
  }

  ::std::optional< ::llvm::StringRef > getLabel();
};

} // namespace detail
template <typename RangeT>
class CoverOpGenericAdaptor : public detail::CoverOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::CoverOpGenericAdaptorBase;
  static constexpr int odsIndex_property = 0;
  static constexpr int odsIndex_enable = 1;
public:
  CoverOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  CoverOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : CoverOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  CoverOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : CoverOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  CoverOpGenericAdaptor(RangeT values, const CoverOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = CoverOp, typename = std::enable_if_t<std::is_same_v<LateInst, CoverOp>>>
  CoverOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getProperty() {
    return (*getODSOperands(0).begin());
  }

  ValueT getEnable() {
    auto operands = getODSOperands(1);
    return operands.empty() ? ValueT{} : (*operands.begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class CoverOpAdaptor : public CoverOpGenericAdaptor<::mlir::ValueRange> {
public:
  using CoverOpGenericAdaptor::CoverOpGenericAdaptor;
  CoverOpAdaptor(CoverOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class CoverOp : public ::mlir::Op<CoverOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<1>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = CoverOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = CoverOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_property = 0;
  static constexpr int odsIndex_enable = 1;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("label")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getLabelAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getLabelAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("verif.cover");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::Type> getProperty() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getEnable() {
    auto operands = getODSOperands(1);
    return operands.empty() ? ::mlir::TypedValue<::mlir::IntegerType>{} : ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*operands.begin());
  }

  ::mlir::OpOperand &getPropertyMutable() {
    auto range = getODSOperandIndexAndLength(0);
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

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::llvm::LogicalResult readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state);
  void writeProperties(::mlir::DialectBytecodeWriter &writer);
  ::mlir::StringAttr getLabelAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::StringAttr>(getProperties().label);
  }

  ::std::optional< ::llvm::StringRef > getLabel();
  void setLabelAttr(::mlir::StringAttr attr) {
    getProperties().label = attr;
  }

  void setLabel(::std::optional<::llvm::StringRef> attrValue);
  ::mlir::Attribute removeLabelAttr() {
      auto attr = getProperties().label;
      getProperties().label = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value property, /*optional*/::mlir::Value enable, /*optional*/::mlir::StringAttr label);
  static CoverOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value property, /*optional*/::mlir::Value enable, /*optional*/::mlir::StringAttr label);
  static CoverOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value property, /*optional*/::mlir::Value enable, /*optional*/::mlir::StringAttr label);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value property, /*optional*/::mlir::Value enable, /*optional*/::mlir::StringAttr label);
  static CoverOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value property, /*optional*/::mlir::Value enable, /*optional*/::mlir::StringAttr label);
  static CoverOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value property, /*optional*/::mlir::Value enable, /*optional*/::mlir::StringAttr label);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static CoverOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static CoverOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static CoverOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static CoverOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
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
};

} // namespace circt::verif
MLIR_DECLARE_EXPLICIT_TYPE_ID(circt::verif::CoverOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(circt::verif::detail::CoverOpGenericAdaptorBase::Properties)

namespace circt::verif {


//===----------------------------------------------------------------------===//
// circt::verif::EnsureOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class EnsureOpGenericAdaptorBase {
public:
  struct Properties {
    using labelTy = ::mlir::StringAttr;
    labelTy label;

    auto getLabel() const {
      auto &propStorage = this->label;
      return ::llvm::dyn_cast_or_null<::mlir::StringAttr>(propStorage);
    }
    void setLabel(const ::mlir::StringAttr &propValue) {
      this->label = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.label == this->label &&
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
  EnsureOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("verif.ensure", odsAttrs.getContext());
  }

  EnsureOpGenericAdaptorBase(EnsureOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::StringAttr getLabelAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::StringAttr>(getProperties().label);
    return attr;
  }

  ::std::optional< ::llvm::StringRef > getLabel();
};

} // namespace detail
template <typename RangeT>
class EnsureOpGenericAdaptor : public detail::EnsureOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::EnsureOpGenericAdaptorBase;
  static constexpr int odsIndex_property = 0;
  static constexpr int odsIndex_enable = 1;
public:
  EnsureOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  EnsureOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : EnsureOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  EnsureOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : EnsureOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  EnsureOpGenericAdaptor(RangeT values, const EnsureOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = EnsureOp, typename = std::enable_if_t<std::is_same_v<LateInst, EnsureOp>>>
  EnsureOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getProperty() {
    return (*getODSOperands(0).begin());
  }

  ValueT getEnable() {
    auto operands = getODSOperands(1);
    return operands.empty() ? ValueT{} : (*operands.begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class EnsureOpAdaptor : public EnsureOpGenericAdaptor<::mlir::ValueRange> {
public:
  using EnsureOpGenericAdaptor::EnsureOpGenericAdaptor;
  EnsureOpAdaptor(EnsureOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class EnsureOp : public ::mlir::Op<EnsureOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<1>::Impl, ::mlir::OpTrait::HasParent<verif::ContractOp>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, circt::verif::RequireLike::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = EnsureOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = EnsureOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_property = 0;
  static constexpr int odsIndex_enable = 1;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("label")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getLabelAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getLabelAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("verif.ensure");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::Type> getProperty() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getEnable() {
    auto operands = getODSOperands(1);
    return operands.empty() ? ::mlir::TypedValue<::mlir::IntegerType>{} : ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*operands.begin());
  }

  ::mlir::OpOperand &getPropertyMutable() {
    auto range = getODSOperandIndexAndLength(0);
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

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::llvm::LogicalResult readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state);
  void writeProperties(::mlir::DialectBytecodeWriter &writer);
  ::mlir::StringAttr getLabelAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::StringAttr>(getProperties().label);
  }

  ::std::optional< ::llvm::StringRef > getLabel();
  void setLabelAttr(::mlir::StringAttr attr) {
    getProperties().label = attr;
  }

  void setLabel(::std::optional<::llvm::StringRef> attrValue);
  ::mlir::Attribute removeLabelAttr() {
      auto attr = getProperties().label;
      getProperties().label = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value property, /*optional*/::mlir::Value enable, /*optional*/::mlir::StringAttr label);
  static EnsureOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value property, /*optional*/::mlir::Value enable, /*optional*/::mlir::StringAttr label);
  static EnsureOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value property, /*optional*/::mlir::Value enable, /*optional*/::mlir::StringAttr label);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value property, /*optional*/::mlir::Value enable, /*optional*/::mlir::StringAttr label);
  static EnsureOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value property, /*optional*/::mlir::Value enable, /*optional*/::mlir::StringAttr label);
  static EnsureOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value property, /*optional*/::mlir::Value enable, /*optional*/::mlir::StringAttr label);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static EnsureOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static EnsureOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static EnsureOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static EnsureOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
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
};

} // namespace circt::verif
MLIR_DECLARE_EXPLICIT_TYPE_ID(circt::verif::EnsureOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(circt::verif::detail::EnsureOpGenericAdaptorBase::Properties)

namespace circt::verif {


//===----------------------------------------------------------------------===//
// circt::verif::FormalOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class FormalOpGenericAdaptorBase {
public:
  struct Properties {
    using parametersTy = ::mlir::DictionaryAttr;
    parametersTy parameters;

    auto getParameters() const {
      auto &propStorage = this->parameters;
      return ::llvm::cast<::mlir::DictionaryAttr>(propStorage);
    }
    void setParameters(const ::mlir::DictionaryAttr &propValue) {
      this->parameters = propValue;
    }
    using sym_nameTy = ::mlir::StringAttr;
    sym_nameTy sym_name;

    auto getSymName() const {
      auto &propStorage = this->sym_name;
      return ::llvm::cast<::mlir::StringAttr>(propStorage);
    }
    void setSymName(const ::mlir::StringAttr &propValue) {
      this->sym_name = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.parameters == this->parameters &&
        rhs.sym_name == this->sym_name &&
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
  FormalOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("verif.formal", odsAttrs.getContext());
  }

  FormalOpGenericAdaptorBase(FormalOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::StringAttr getSymNameAttr() {
    auto attr = ::llvm::cast<::mlir::StringAttr>(getProperties().sym_name);
    return attr;
  }

  ::llvm::StringRef getSymName();
  ::mlir::DictionaryAttr getParametersAttr() {
    auto attr = ::llvm::cast<::mlir::DictionaryAttr>(getProperties().parameters);
    return attr;
  }

  ::mlir::DictionaryAttr getParameters();
  ::mlir::Region &getBody() {
    return *odsRegions[0];
  }

  ::mlir::RegionRange getRegions() {
    return odsRegions;
  }

};

} // namespace detail
template <typename RangeT>
class FormalOpGenericAdaptor : public detail::FormalOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::FormalOpGenericAdaptorBase;
public:
  FormalOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  FormalOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : FormalOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  FormalOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : FormalOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  FormalOpGenericAdaptor(RangeT values, const FormalOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = FormalOp, typename = std::enable_if_t<std::is_same_v<LateInst, FormalOp>>>
  FormalOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class FormalOpAdaptor : public FormalOpGenericAdaptor<::mlir::ValueRange> {
public:
  using FormalOpGenericAdaptor::FormalOpGenericAdaptor;
  FormalOpAdaptor(FormalOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class FormalOp : public ::mlir::Op<FormalOp, ::mlir::OpTrait::OneRegion, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::NoRegionArguments, ::mlir::OpTrait::NoTerminator, ::mlir::OpTrait::SingleBlock, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::OpTrait::IsIsolatedFromAbove, ::mlir::RegionKindInterface::Trait, ::mlir::SymbolOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = FormalOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = FormalOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("parameters"), ::llvm::StringRef("sym_name")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getParametersAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getParametersAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getSymNameAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getSymNameAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("verif.formal");
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
  ::mlir::StringAttr getSymNameAttr() {
    return ::llvm::cast<::mlir::StringAttr>(getProperties().sym_name);
  }

  ::llvm::StringRef getSymName();
  ::mlir::DictionaryAttr getParametersAttr() {
    return ::llvm::cast<::mlir::DictionaryAttr>(getProperties().parameters);
  }

  ::mlir::DictionaryAttr getParameters();
  void setSymNameAttr(::mlir::StringAttr attr) {
    getProperties().sym_name = attr;
  }

  void setSymName(::llvm::StringRef attrValue);
  void setParametersAttr(::mlir::DictionaryAttr attr) {
    getProperties().parameters = attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::StringAttr sym_name, ::mlir::DictionaryAttr parameters);
  static FormalOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::StringAttr sym_name, ::mlir::DictionaryAttr parameters);
  static FormalOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::StringAttr sym_name, ::mlir::DictionaryAttr parameters);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name, ::mlir::DictionaryAttr parameters);
  static FormalOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name, ::mlir::DictionaryAttr parameters);
  static FormalOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name, ::mlir::DictionaryAttr parameters);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::llvm::StringRef sym_name, ::mlir::DictionaryAttr parameters);
  static FormalOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::llvm::StringRef sym_name, ::mlir::DictionaryAttr parameters);
  static FormalOp create(::mlir::ImplicitLocOpBuilder &builder, ::llvm::StringRef sym_name, ::mlir::DictionaryAttr parameters);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name, ::mlir::DictionaryAttr parameters);
  static FormalOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name, ::mlir::DictionaryAttr parameters);
  static FormalOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name, ::mlir::DictionaryAttr parameters);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static FormalOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static FormalOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static FormalOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static FormalOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
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
  static RegionKind getRegionKind(unsigned index) {
    return RegionKind::Graph;
  }
};

} // namespace circt::verif
MLIR_DECLARE_EXPLICIT_TYPE_ID(circt::verif::FormalOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(circt::verif::detail::FormalOpGenericAdaptorBase::Properties)

namespace circt::verif {


//===----------------------------------------------------------------------===//
// circt::verif::FormatVerilogStringOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class FormatVerilogStringOpGenericAdaptorBase {
public:
  struct Properties {
    using formatStringTy = ::mlir::StringAttr;
    formatStringTy formatString;

    auto getFormatString() const {
      auto &propStorage = this->formatString;
      return ::llvm::cast<::mlir::StringAttr>(propStorage);
    }
    void setFormatString(const ::mlir::StringAttr &propValue) {
      this->formatString = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.formatString == this->formatString &&
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
  FormatVerilogStringOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("verif.format_verilog_string", odsAttrs.getContext());
  }

  FormatVerilogStringOpGenericAdaptorBase(FormatVerilogStringOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::StringAttr getFormatStringAttr() {
    auto attr = ::llvm::cast<::mlir::StringAttr>(getProperties().formatString);
    return attr;
  }

  ::llvm::StringRef getFormatString();
};

} // namespace detail
template <typename RangeT>
class FormatVerilogStringOpGenericAdaptor : public detail::FormatVerilogStringOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::FormatVerilogStringOpGenericAdaptorBase;
  static constexpr int odsIndex_substitutions = 0;
public:
  FormatVerilogStringOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  FormatVerilogStringOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : FormatVerilogStringOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  FormatVerilogStringOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : FormatVerilogStringOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  FormatVerilogStringOpGenericAdaptor(RangeT values, const FormatVerilogStringOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = FormatVerilogStringOp, typename = std::enable_if_t<std::is_same_v<LateInst, FormatVerilogStringOp>>>
  FormatVerilogStringOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getSubstitutions() {
    return getODSOperands(0);
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class FormatVerilogStringOpAdaptor : public FormatVerilogStringOpGenericAdaptor<::mlir::ValueRange> {
public:
  using FormatVerilogStringOpGenericAdaptor::FormatVerilogStringOpGenericAdaptor;
  FormatVerilogStringOpAdaptor(FormatVerilogStringOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class FormatVerilogStringOp : public ::mlir::Op<FormatVerilogStringOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::circt::hw::StringType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = FormatVerilogStringOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = FormatVerilogStringOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_substitutions = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("formatString")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getFormatStringAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getFormatStringAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("verif.format_verilog_string");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::operand_range getSubstitutions() {
    return getODSOperands(0);
  }

  ::mlir::MutableOperandRange getSubstitutionsMutable();
  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::circt::hw::StringType> getStr() {
    return ::llvm::cast<::mlir::TypedValue<::circt::hw::StringType>>(*getODSResults(0).begin());
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
  ::mlir::StringAttr getFormatStringAttr() {
    return ::llvm::cast<::mlir::StringAttr>(getProperties().formatString);
  }

  ::llvm::StringRef getFormatString();
  void setFormatStringAttr(::mlir::StringAttr attr) {
    getProperties().formatString = attr;
  }

  void setFormatString(::llvm::StringRef attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type str, ::mlir::StringAttr formatString, ::mlir::ValueRange substitutions);
  static FormatVerilogStringOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type str, ::mlir::StringAttr formatString, ::mlir::ValueRange substitutions);
  static FormatVerilogStringOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type str, ::mlir::StringAttr formatString, ::mlir::ValueRange substitutions);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::StringAttr formatString, ::mlir::ValueRange substitutions);
  static FormatVerilogStringOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::StringAttr formatString, ::mlir::ValueRange substitutions);
  static FormatVerilogStringOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::StringAttr formatString, ::mlir::ValueRange substitutions);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::StringAttr formatString, ::mlir::ValueRange substitutions);
  static FormatVerilogStringOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::StringAttr formatString, ::mlir::ValueRange substitutions);
  static FormatVerilogStringOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::StringAttr formatString, ::mlir::ValueRange substitutions);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type str, ::llvm::StringRef formatString, ::mlir::ValueRange substitutions);
  static FormatVerilogStringOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type str, ::llvm::StringRef formatString, ::mlir::ValueRange substitutions);
  static FormatVerilogStringOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type str, ::llvm::StringRef formatString, ::mlir::ValueRange substitutions);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::llvm::StringRef formatString, ::mlir::ValueRange substitutions);
  static FormatVerilogStringOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::llvm::StringRef formatString, ::mlir::ValueRange substitutions);
  static FormatVerilogStringOp create(::mlir::ImplicitLocOpBuilder &builder, ::llvm::StringRef formatString, ::mlir::ValueRange substitutions);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::llvm::StringRef formatString, ::mlir::ValueRange substitutions);
  static FormatVerilogStringOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::llvm::StringRef formatString, ::mlir::ValueRange substitutions);
  static FormatVerilogStringOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::llvm::StringRef formatString, ::mlir::ValueRange substitutions);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static FormatVerilogStringOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static FormatVerilogStringOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static FormatVerilogStringOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static FormatVerilogStringOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static FormatVerilogStringOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static FormatVerilogStringOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static FormatVerilogStringOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static FormatVerilogStringOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
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

} // namespace circt::verif
MLIR_DECLARE_EXPLICIT_TYPE_ID(circt::verif::FormatVerilogStringOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(circt::verif::detail::FormatVerilogStringOpGenericAdaptorBase::Properties)

namespace circt::verif {


//===----------------------------------------------------------------------===//
// circt::verif::HasBeenResetOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class HasBeenResetOpGenericAdaptorBase {
public:
  struct Properties {
    using asyncTy = ::mlir::BoolAttr;
    asyncTy async;

    auto getAsync() const {
      auto &propStorage = this->async;
      return ::llvm::cast<::mlir::BoolAttr>(propStorage);
    }
    void setAsync(const ::mlir::BoolAttr &propValue) {
      this->async = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.async == this->async &&
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
  HasBeenResetOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("verif.has_been_reset", odsAttrs.getContext());
  }

  HasBeenResetOpGenericAdaptorBase(HasBeenResetOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::BoolAttr getAsyncAttr() {
    auto attr = ::llvm::cast<::mlir::BoolAttr>(getProperties().async);
    return attr;
  }

  bool getAsync();
};

} // namespace detail
template <typename RangeT>
class HasBeenResetOpGenericAdaptor : public detail::HasBeenResetOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::HasBeenResetOpGenericAdaptorBase;
  static constexpr int odsIndex_clock = 0;
  static constexpr int odsIndex_reset = 1;
public:
  HasBeenResetOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  HasBeenResetOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : HasBeenResetOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  HasBeenResetOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : HasBeenResetOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  HasBeenResetOpGenericAdaptor(RangeT values, const HasBeenResetOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = HasBeenResetOp, typename = std::enable_if_t<std::is_same_v<LateInst, HasBeenResetOp>>>
  HasBeenResetOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getClock() {
    return (*getODSOperands(0).begin());
  }

  ValueT getReset() {
    return (*getODSOperands(1).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class HasBeenResetOpAdaptor : public HasBeenResetOpGenericAdaptor<::mlir::ValueRange> {
public:
  using HasBeenResetOpGenericAdaptor::HasBeenResetOpGenericAdaptor;
  HasBeenResetOpAdaptor(HasBeenResetOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class HasBeenResetOp : public ::mlir::Op<HasBeenResetOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::IntegerType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::NOperands<2>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = HasBeenResetOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = HasBeenResetOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_clock = 0;
  static constexpr int odsIndex_reset = 1;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("async")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getAsyncAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getAsyncAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("verif.has_been_reset");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::IntegerType> getClock() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getReset() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSOperands(1).begin());
  }

  ::mlir::OpOperand &getClockMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getResetMutable() {
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

  ::mlir::TypedValue<::mlir::IntegerType> getResult() {
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
  ::mlir::BoolAttr getAsyncAttr() {
    return ::llvm::cast<::mlir::BoolAttr>(getProperties().async);
  }

  bool getAsync();
  void setAsyncAttr(::mlir::BoolAttr attr) {
    getProperties().async = attr;
  }

  void setAsync(bool attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value clock, ::mlir::Value reset, ::mlir::BoolAttr async);
  static HasBeenResetOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value clock, ::mlir::Value reset, ::mlir::BoolAttr async);
  static HasBeenResetOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value clock, ::mlir::Value reset, ::mlir::BoolAttr async);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value clock, ::mlir::Value reset, ::mlir::BoolAttr async);
  static HasBeenResetOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value clock, ::mlir::Value reset, ::mlir::BoolAttr async);
  static HasBeenResetOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value clock, ::mlir::Value reset, ::mlir::BoolAttr async);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value clock, ::mlir::Value reset, ::mlir::BoolAttr async);
  static HasBeenResetOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value clock, ::mlir::Value reset, ::mlir::BoolAttr async);
  static HasBeenResetOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value clock, ::mlir::Value reset, ::mlir::BoolAttr async);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value clock, ::mlir::Value reset, bool async);
  static HasBeenResetOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value clock, ::mlir::Value reset, bool async);
  static HasBeenResetOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value clock, ::mlir::Value reset, bool async);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value clock, ::mlir::Value reset, bool async);
  static HasBeenResetOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value clock, ::mlir::Value reset, bool async);
  static HasBeenResetOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value clock, ::mlir::Value reset, bool async);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value clock, ::mlir::Value reset, bool async);
  static HasBeenResetOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value clock, ::mlir::Value reset, bool async);
  static HasBeenResetOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value clock, ::mlir::Value reset, bool async);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static HasBeenResetOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static HasBeenResetOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static HasBeenResetOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static HasBeenResetOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static HasBeenResetOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static HasBeenResetOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static HasBeenResetOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static HasBeenResetOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
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

} // namespace circt::verif
MLIR_DECLARE_EXPLICIT_TYPE_ID(circt::verif::HasBeenResetOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(circt::verif::detail::HasBeenResetOpGenericAdaptorBase::Properties)

namespace circt::verif {


//===----------------------------------------------------------------------===//
// circt::verif::LogicEquivalenceCheckingOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class LogicEquivalenceCheckingOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  LogicEquivalenceCheckingOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("verif.lec", odsAttrs.getContext());
  }

  LogicEquivalenceCheckingOpGenericAdaptorBase(LogicEquivalenceCheckingOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::Region &getFirstCircuit() {
    return *odsRegions[0];
  }

  ::mlir::Region &getSecondCircuit() {
    return *odsRegions[1];
  }

  ::mlir::RegionRange getRegions() {
    return odsRegions;
  }

};

} // namespace detail
template <typename RangeT>
class LogicEquivalenceCheckingOpGenericAdaptor : public detail::LogicEquivalenceCheckingOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::LogicEquivalenceCheckingOpGenericAdaptorBase;
public:
  LogicEquivalenceCheckingOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  LogicEquivalenceCheckingOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : LogicEquivalenceCheckingOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  LogicEquivalenceCheckingOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : LogicEquivalenceCheckingOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  LogicEquivalenceCheckingOpGenericAdaptor(RangeT values, const LogicEquivalenceCheckingOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = LogicEquivalenceCheckingOp, typename = std::enable_if_t<std::is_same_v<LateInst, LogicEquivalenceCheckingOp>>>
  LogicEquivalenceCheckingOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class LogicEquivalenceCheckingOpAdaptor : public LogicEquivalenceCheckingOpGenericAdaptor<::mlir::ValueRange> {
public:
  using LogicEquivalenceCheckingOpGenericAdaptor::LogicEquivalenceCheckingOpGenericAdaptor;
  LogicEquivalenceCheckingOpAdaptor(LogicEquivalenceCheckingOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class LogicEquivalenceCheckingOp : public ::mlir::Op<LogicEquivalenceCheckingOp, ::mlir::OpTrait::NRegions<2>::Impl, ::mlir::OpTrait::VariadicResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::SingleBlock, ::mlir::OpTrait::SingleBlockImplicitTerminator<verif::YieldOp>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::OpTrait::IsIsolatedFromAbove> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = LogicEquivalenceCheckingOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = LogicEquivalenceCheckingOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("verif.lec");
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

  ::mlir::TypedValue<::mlir::IntegerType> getIsProven() {
    auto results = getODSResults(0);
    return results.empty() ? ::mlir::TypedValue<::mlir::IntegerType>() : ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*results.begin());
  }

  ::mlir::Region &getFirstCircuit() {
    return (*this)->getRegion(0);
  }

  ::mlir::Region &getSecondCircuit() {
    return (*this)->getRegion(1);
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, bool hasResult);
  static LogicEquivalenceCheckingOp create(::mlir::OpBuilder &builder, ::mlir::Location location, bool hasResult);
  static LogicEquivalenceCheckingOp create(::mlir::ImplicitLocOpBuilder &builder, bool hasResult);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, /*optional*/::mlir::Type isProven);
  static LogicEquivalenceCheckingOp create(::mlir::OpBuilder &builder, ::mlir::Location location, /*optional*/::mlir::Type isProven);
  static LogicEquivalenceCheckingOp create(::mlir::ImplicitLocOpBuilder &builder, /*optional*/::mlir::Type isProven);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes);
  static LogicEquivalenceCheckingOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes);
  static LogicEquivalenceCheckingOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static LogicEquivalenceCheckingOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static LogicEquivalenceCheckingOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static LogicEquivalenceCheckingOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static LogicEquivalenceCheckingOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verifyRegions();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
};

} // namespace circt::verif
MLIR_DECLARE_EXPLICIT_TYPE_ID(circt::verif::LogicEquivalenceCheckingOp)

namespace circt::verif {


//===----------------------------------------------------------------------===//
// circt::verif::PrintOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class PrintOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  PrintOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("verif.print", odsAttrs.getContext());
  }

  PrintOpGenericAdaptorBase(PrintOp op);

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
class PrintOpGenericAdaptor : public detail::PrintOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::PrintOpGenericAdaptorBase;
  static constexpr int odsIndex_string = 0;
public:
  PrintOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  PrintOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : PrintOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  PrintOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : PrintOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  PrintOpGenericAdaptor(RangeT values, const PrintOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = PrintOp, typename = std::enable_if_t<std::is_same_v<LateInst, PrintOp>>>
  PrintOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getString() {
    return (*getODSOperands(0).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class PrintOpAdaptor : public PrintOpGenericAdaptor<::mlir::ValueRange> {
public:
  using PrintOpGenericAdaptor::PrintOpGenericAdaptor;
  PrintOpAdaptor(PrintOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class PrintOp : public ::mlir::Op<PrintOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = PrintOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = PrintOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_string = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("verif.print");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::circt::hw::StringType> getString() {
    return ::llvm::cast<::mlir::TypedValue<::circt::hw::StringType>>(*getODSOperands(0).begin());
  }

  ::mlir::OpOperand &getStringMutable() {
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

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value string);
  static PrintOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value string);
  static PrintOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value string);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value string);
  static PrintOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value string);
  static PrintOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value string);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static PrintOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static PrintOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static PrintOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static PrintOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
};

} // namespace circt::verif
MLIR_DECLARE_EXPLICIT_TYPE_ID(circt::verif::PrintOp)

namespace circt::verif {


//===----------------------------------------------------------------------===//
// circt::verif::RefinementCheckingOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class RefinementCheckingOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  RefinementCheckingOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("verif.refines", odsAttrs.getContext());
  }

  RefinementCheckingOpGenericAdaptorBase(RefinementCheckingOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::Region &getFirstCircuit() {
    return *odsRegions[0];
  }

  ::mlir::Region &getSecondCircuit() {
    return *odsRegions[1];
  }

  ::mlir::RegionRange getRegions() {
    return odsRegions;
  }

};

} // namespace detail
template <typename RangeT>
class RefinementCheckingOpGenericAdaptor : public detail::RefinementCheckingOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::RefinementCheckingOpGenericAdaptorBase;
public:
  RefinementCheckingOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  RefinementCheckingOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : RefinementCheckingOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  RefinementCheckingOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : RefinementCheckingOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  RefinementCheckingOpGenericAdaptor(RangeT values, const RefinementCheckingOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = RefinementCheckingOp, typename = std::enable_if_t<std::is_same_v<LateInst, RefinementCheckingOp>>>
  RefinementCheckingOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class RefinementCheckingOpAdaptor : public RefinementCheckingOpGenericAdaptor<::mlir::ValueRange> {
public:
  using RefinementCheckingOpGenericAdaptor::RefinementCheckingOpGenericAdaptor;
  RefinementCheckingOpAdaptor(RefinementCheckingOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class RefinementCheckingOp : public ::mlir::Op<RefinementCheckingOp, ::mlir::OpTrait::NRegions<2>::Impl, ::mlir::OpTrait::VariadicResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::SingleBlock, ::mlir::OpTrait::SingleBlockImplicitTerminator<verif::YieldOp>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::OpTrait::IsIsolatedFromAbove> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = RefinementCheckingOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = RefinementCheckingOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("verif.refines");
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

  ::mlir::TypedValue<::mlir::IntegerType> getIsProven() {
    auto results = getODSResults(0);
    return results.empty() ? ::mlir::TypedValue<::mlir::IntegerType>() : ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*results.begin());
  }

  ::mlir::Region &getFirstCircuit() {
    return (*this)->getRegion(0);
  }

  ::mlir::Region &getSecondCircuit() {
    return (*this)->getRegion(1);
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, bool hasResult);
  static RefinementCheckingOp create(::mlir::OpBuilder &builder, ::mlir::Location location, bool hasResult);
  static RefinementCheckingOp create(::mlir::ImplicitLocOpBuilder &builder, bool hasResult);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, /*optional*/::mlir::Type isProven);
  static RefinementCheckingOp create(::mlir::OpBuilder &builder, ::mlir::Location location, /*optional*/::mlir::Type isProven);
  static RefinementCheckingOp create(::mlir::ImplicitLocOpBuilder &builder, /*optional*/::mlir::Type isProven);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes);
  static RefinementCheckingOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes);
  static RefinementCheckingOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static RefinementCheckingOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static RefinementCheckingOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static RefinementCheckingOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static RefinementCheckingOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verifyRegions();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
};

} // namespace circt::verif
MLIR_DECLARE_EXPLICIT_TYPE_ID(circt::verif::RefinementCheckingOp)

namespace circt::verif {


//===----------------------------------------------------------------------===//
// circt::verif::RequireOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class RequireOpGenericAdaptorBase {
public:
  struct Properties {
    using labelTy = ::mlir::StringAttr;
    labelTy label;

    auto getLabel() const {
      auto &propStorage = this->label;
      return ::llvm::dyn_cast_or_null<::mlir::StringAttr>(propStorage);
    }
    void setLabel(const ::mlir::StringAttr &propValue) {
      this->label = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.label == this->label &&
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
  RequireOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("verif.require", odsAttrs.getContext());
  }

  RequireOpGenericAdaptorBase(RequireOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::StringAttr getLabelAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::StringAttr>(getProperties().label);
    return attr;
  }

  ::std::optional< ::llvm::StringRef > getLabel();
};

} // namespace detail
template <typename RangeT>
class RequireOpGenericAdaptor : public detail::RequireOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::RequireOpGenericAdaptorBase;
  static constexpr int odsIndex_property = 0;
  static constexpr int odsIndex_enable = 1;
public:
  RequireOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  RequireOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : RequireOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  RequireOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : RequireOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  RequireOpGenericAdaptor(RangeT values, const RequireOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = RequireOp, typename = std::enable_if_t<std::is_same_v<LateInst, RequireOp>>>
  RequireOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getProperty() {
    return (*getODSOperands(0).begin());
  }

  ValueT getEnable() {
    auto operands = getODSOperands(1);
    return operands.empty() ? ValueT{} : (*operands.begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class RequireOpAdaptor : public RequireOpGenericAdaptor<::mlir::ValueRange> {
public:
  using RequireOpGenericAdaptor::RequireOpGenericAdaptor;
  RequireOpAdaptor(RequireOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class RequireOp : public ::mlir::Op<RequireOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<1>::Impl, ::mlir::OpTrait::HasParent<verif::ContractOp>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, circt::verif::RequireLike::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = RequireOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = RequireOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_property = 0;
  static constexpr int odsIndex_enable = 1;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("label")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getLabelAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getLabelAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("verif.require");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::Type> getProperty() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::mlir::IntegerType> getEnable() {
    auto operands = getODSOperands(1);
    return operands.empty() ? ::mlir::TypedValue<::mlir::IntegerType>{} : ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*operands.begin());
  }

  ::mlir::OpOperand &getPropertyMutable() {
    auto range = getODSOperandIndexAndLength(0);
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

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::llvm::LogicalResult readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state);
  void writeProperties(::mlir::DialectBytecodeWriter &writer);
  ::mlir::StringAttr getLabelAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::StringAttr>(getProperties().label);
  }

  ::std::optional< ::llvm::StringRef > getLabel();
  void setLabelAttr(::mlir::StringAttr attr) {
    getProperties().label = attr;
  }

  void setLabel(::std::optional<::llvm::StringRef> attrValue);
  ::mlir::Attribute removeLabelAttr() {
      auto attr = getProperties().label;
      getProperties().label = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value property, /*optional*/::mlir::Value enable, /*optional*/::mlir::StringAttr label);
  static RequireOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value property, /*optional*/::mlir::Value enable, /*optional*/::mlir::StringAttr label);
  static RequireOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value property, /*optional*/::mlir::Value enable, /*optional*/::mlir::StringAttr label);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value property, /*optional*/::mlir::Value enable, /*optional*/::mlir::StringAttr label);
  static RequireOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value property, /*optional*/::mlir::Value enable, /*optional*/::mlir::StringAttr label);
  static RequireOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value property, /*optional*/::mlir::Value enable, /*optional*/::mlir::StringAttr label);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static RequireOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static RequireOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static RequireOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static RequireOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
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
};

} // namespace circt::verif
MLIR_DECLARE_EXPLICIT_TYPE_ID(circt::verif::RequireOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(circt::verif::detail::RequireOpGenericAdaptorBase::Properties)

namespace circt::verif {


//===----------------------------------------------------------------------===//
// circt::verif::SimulationOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class SimulationOpGenericAdaptorBase {
public:
  struct Properties {
    using parametersTy = ::mlir::DictionaryAttr;
    parametersTy parameters;

    auto getParameters() const {
      auto &propStorage = this->parameters;
      return ::llvm::cast<::mlir::DictionaryAttr>(propStorage);
    }
    void setParameters(const ::mlir::DictionaryAttr &propValue) {
      this->parameters = propValue;
    }
    using sym_nameTy = ::mlir::StringAttr;
    sym_nameTy sym_name;

    auto getSymName() const {
      auto &propStorage = this->sym_name;
      return ::llvm::cast<::mlir::StringAttr>(propStorage);
    }
    void setSymName(const ::mlir::StringAttr &propValue) {
      this->sym_name = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.parameters == this->parameters &&
        rhs.sym_name == this->sym_name &&
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
  SimulationOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("verif.simulation", odsAttrs.getContext());
  }

  SimulationOpGenericAdaptorBase(SimulationOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::StringAttr getSymNameAttr() {
    auto attr = ::llvm::cast<::mlir::StringAttr>(getProperties().sym_name);
    return attr;
  }

  ::llvm::StringRef getSymName();
  ::mlir::DictionaryAttr getParametersAttr() {
    auto attr = ::llvm::cast<::mlir::DictionaryAttr>(getProperties().parameters);
    return attr;
  }

  ::mlir::DictionaryAttr getParameters();
  ::mlir::Region &getRegion() {
    return *odsRegions[0];
  }

  ::mlir::RegionRange getRegions() {
    return odsRegions;
  }

};

} // namespace detail
template <typename RangeT>
class SimulationOpGenericAdaptor : public detail::SimulationOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::SimulationOpGenericAdaptorBase;
public:
  SimulationOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  SimulationOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : SimulationOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  SimulationOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : SimulationOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  SimulationOpGenericAdaptor(RangeT values, const SimulationOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = SimulationOp, typename = std::enable_if_t<std::is_same_v<LateInst, SimulationOp>>>
  SimulationOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class SimulationOpAdaptor : public SimulationOpGenericAdaptor<::mlir::ValueRange> {
public:
  using SimulationOpGenericAdaptor::SimulationOpGenericAdaptor;
  SimulationOpAdaptor(SimulationOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class SimulationOp : public ::mlir::Op<SimulationOp, ::mlir::OpTrait::OneRegion, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::SingleBlock, ::mlir::OpTrait::SingleBlockImplicitTerminator<verif::YieldOp>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::OpAsmOpInterface::Trait, ::mlir::OpTrait::IsIsolatedFromAbove, ::mlir::RegionKindInterface::Trait, ::mlir::SymbolOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = SimulationOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = SimulationOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::OpAsmOpInterface::Trait<SimulationOp>::getAsmResultNames;
  using ::mlir::OpAsmOpInterface::Trait<SimulationOp>::getAsmBlockNames;
  using ::mlir::OpAsmOpInterface::Trait<SimulationOp>::getDefaultDialect;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("parameters"), ::llvm::StringRef("sym_name")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getParametersAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getParametersAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getSymNameAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getSymNameAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("verif.simulation");
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

  ::mlir::Region &getRegion() {
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
  ::mlir::StringAttr getSymNameAttr() {
    return ::llvm::cast<::mlir::StringAttr>(getProperties().sym_name);
  }

  ::llvm::StringRef getSymName();
  ::mlir::DictionaryAttr getParametersAttr() {
    return ::llvm::cast<::mlir::DictionaryAttr>(getProperties().parameters);
  }

  ::mlir::DictionaryAttr getParameters();
  void setSymNameAttr(::mlir::StringAttr attr) {
    getProperties().sym_name = attr;
  }

  void setSymName(::llvm::StringRef attrValue);
  void setParametersAttr(::mlir::DictionaryAttr attr) {
    getProperties().parameters = attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::StringAttr sym_name, ::mlir::DictionaryAttr parameters);
  static SimulationOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::StringAttr sym_name, ::mlir::DictionaryAttr parameters);
  static SimulationOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::StringAttr sym_name, ::mlir::DictionaryAttr parameters);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name, ::mlir::DictionaryAttr parameters);
  static SimulationOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name, ::mlir::DictionaryAttr parameters);
  static SimulationOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name, ::mlir::DictionaryAttr parameters);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::llvm::StringRef sym_name, ::mlir::DictionaryAttr parameters);
  static SimulationOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::llvm::StringRef sym_name, ::mlir::DictionaryAttr parameters);
  static SimulationOp create(::mlir::ImplicitLocOpBuilder &builder, ::llvm::StringRef sym_name, ::mlir::DictionaryAttr parameters);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name, ::mlir::DictionaryAttr parameters);
  static SimulationOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name, ::mlir::DictionaryAttr parameters);
  static SimulationOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name, ::mlir::DictionaryAttr parameters);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SimulationOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SimulationOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SimulationOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SimulationOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verifyRegions();
  void getAsmBlockArgumentNames(::mlir::Region&region, ::mlir::OpAsmSetValueNameFn setNameFn);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
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
  static RegionKind getRegionKind(unsigned index) {
    return RegionKind::Graph;
  }
};

} // namespace circt::verif
MLIR_DECLARE_EXPLICIT_TYPE_ID(circt::verif::SimulationOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(circt::verif::detail::SimulationOpGenericAdaptorBase::Properties)

namespace circt::verif {


//===----------------------------------------------------------------------===//
// circt::verif::SymbolicValueOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class SymbolicValueOpGenericAdaptorBase {
public:
  struct Properties {
    using nameTy = ::mlir::StringAttr;
    nameTy name;

    auto getName() const {
      auto &propStorage = this->name;
      return ::llvm::dyn_cast_or_null<::mlir::StringAttr>(propStorage);
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
  SymbolicValueOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("verif.symbolic_value", odsAttrs.getContext());
  }

  SymbolicValueOpGenericAdaptorBase(SymbolicValueOp op);

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
    auto attr = ::llvm::dyn_cast_or_null<::mlir::StringAttr>(getProperties().name);
    return attr;
  }

  ::std::optional< ::llvm::StringRef > getName();
};

} // namespace detail
template <typename RangeT>
class SymbolicValueOpGenericAdaptor : public detail::SymbolicValueOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::SymbolicValueOpGenericAdaptorBase;
public:
  SymbolicValueOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  SymbolicValueOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : SymbolicValueOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  SymbolicValueOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : SymbolicValueOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  SymbolicValueOpGenericAdaptor(RangeT values, const SymbolicValueOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = SymbolicValueOp, typename = std::enable_if_t<std::is_same_v<LateInst, SymbolicValueOp>>>
  SymbolicValueOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class SymbolicValueOpAdaptor : public SymbolicValueOpGenericAdaptor<::mlir::ValueRange> {
public:
  using SymbolicValueOpGenericAdaptor::SymbolicValueOpGenericAdaptor;
  SymbolicValueOpAdaptor(SymbolicValueOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class SymbolicValueOp : public ::mlir::Op<SymbolicValueOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::Type>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::HasParent<verif::FormalOp, hw::HWModuleOp>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::OpAsmOpInterface::Trait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = SymbolicValueOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = SymbolicValueOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::OpAsmOpInterface::Trait<SymbolicValueOp>::getAsmBlockArgumentNames;
  using ::mlir::OpAsmOpInterface::Trait<SymbolicValueOp>::getAsmBlockNames;
  using ::mlir::OpAsmOpInterface::Trait<SymbolicValueOp>::getDefaultDialect;
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
    return ::llvm::StringLiteral("verif.symbolic_value");
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

  ::mlir::TypedValue<::mlir::Type> getResult() {
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
  void setNameAttr(::mlir::StringAttr attr) {
    getProperties().name = attr;
  }

  void setName(::std::optional<::llvm::StringRef> attrValue);
  ::mlir::Attribute removeNameAttr() {
      auto attr = getProperties().name;
      getProperties().name = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, /*optional*/::mlir::StringAttr name);
  static SymbolicValueOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, /*optional*/::mlir::StringAttr name);
  static SymbolicValueOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, /*optional*/::mlir::StringAttr name);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, /*optional*/::mlir::StringAttr name);
  static SymbolicValueOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, /*optional*/::mlir::StringAttr name);
  static SymbolicValueOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, /*optional*/::mlir::StringAttr name);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SymbolicValueOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SymbolicValueOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SymbolicValueOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SymbolicValueOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
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

} // namespace circt::verif
MLIR_DECLARE_EXPLICIT_TYPE_ID(circt::verif::SymbolicValueOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(circt::verif::detail::SymbolicValueOpGenericAdaptorBase::Properties)

namespace circt::verif {


//===----------------------------------------------------------------------===//
// circt::verif::YieldOp declarations
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
      odsOpName.emplace("verif.yield", odsAttrs.getContext());
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
  static constexpr int odsIndex_inputs = 0;
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

  RangeT getInputs() {
    return getODSOperands(0);
  }

  RangeT getOperands() {
    return odsOperands;
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
class YieldOp : public ::mlir::Op<YieldOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::HasParent<verif::BoundedModelCheckingOp, verif::LogicEquivalenceCheckingOp, verif::RefinementCheckingOp, verif::SimulationOp>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::OpTrait::IsTerminator> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = YieldOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = YieldOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_inputs = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("verif.yield");
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
  static YieldOp create(::mlir::OpBuilder &builder, ::mlir::Location location);
  static YieldOp create(::mlir::ImplicitLocOpBuilder &builder);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange inputs);
  static YieldOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange inputs);
  static YieldOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange inputs);
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
public:
};

} // namespace circt::verif
MLIR_DECLARE_EXPLICIT_TYPE_ID(circt::verif::YieldOp)


#endif // GET_OP_CLASSES

