/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Op Declarations                                                            *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: Synth.td                                                             *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace circt::synth::aig {

/// AIG dialect AND operation
/// The `synth.aig.and_inv` operation represents an And-Inverter in the AIG dialect.
/// Unlike `comb.and`, operands can be inverted respectively.
/// 
/// Example:
/// ```mlir
///   %r1 = synth.aig.and_inv %a, %b: i3
///   %r2 = synth.aig.and_inv not %a, %b, not %c : i3
///   %r3 = synth.aig.and_inv not %a : i3
/// ```
/// 
/// Traditionally, an And-Node in AIG has two operands. However, `synth.aig.and_inv`
/// extends this concept by allowing variadic operands and non-i1 integer types.
/// Although the final stage of the synthesis pipeline requires lowering
/// everything to i1-binary operands, it's more efficient to progressively lower
/// the variadic multibit operations.
/// 
/// Variadic operands have demonstrated their utility in low-level optimizations
/// within the `comb` dialect. Furthermore, in synthesis, it's common practice
/// to re-balance the logic path. Variadic operands enable the compiler to
/// select more efficient solutions without the need to traverse binary trees
/// multiple times.
/// 
/// The ability to represent multibit operations during synthesis is crucial for
/// scalability. This approach enables a form of vectorization, allowing for
/// batch processing of logic synthesis when multibit operations are constructed
/// in a similar manner.
class AndInverterOp;

} // namespace circt::synth::aig
namespace circt::synth {

/// Synth choice operation
/// The `synth.choice` operation represents a set of structurally equivalent
/// choices, corresponding to the choice nodes introduced in "Reducing
/// Structural Bias in Technology Mapping" (ICCAD 2005, S. Chatterjee et al.).
/// 
/// A compiler may assume all operands are equivalent and replace the operation
/// with any one of them at any point in the pipeline.
/// 
/// Example:
/// ```mlir
///   %r1 = synth.choice %a, %b : i1
///   %r2 = synth.choice %a, %b, %c : i16
/// ```
class ChoiceOp;

} // namespace circt::synth
namespace circt::synth {

/// Ordered 3-input DOT gate with invertible inputs
/// The `synth.dot` operation represents the ordered three-input Boolean
/// function `x xor (z or (x and y))`, applied after optional per-input
/// inversion.
/// 
/// Unlike common AND, OR, XOR, and majority gates, `synth.dot` is not
/// permutation-invariant: its operands play distinct roles in the Boolean
/// expression. Dot gates are known to be a promising intermediate
/// representation for area optimization, as discussed in "Three-Input Gates
/// for Logic Synthesis" (Dewmini Sudara Marakkalage et al., TCAD 2021).
/// 
/// Example:
/// ```mlir
///   %r0 = synth.dot %x, %y, %z : i1
///   %r1 = synth.dot not %x, %y, not %z : i8
/// ```
class DotOp;

} // namespace circt::synth
namespace circt::synth {

/// 3-input Gamble gate with invertible inputs
///   The `synth.gamble` operation computes the gamble function of its three
///   inputs, where each operand can be optionally inverted. The gamble function
///   returns 1 when all inputs are 1 or all inputs are 0, and 0 otherwise.
///   For three inputs, it is equivalent to:
/// 
///   `(a & b & c) | (~a & ~b & ~c)`
/// 
///   Example:
/// ```mlir
///     %r0 = synth.gamble %a, %b, %c : i1
///     %r1 = synth.gamble not %a, %b, not %c : i1
/// ```
class GambleOp;

} // namespace circt::synth
namespace circt::synth {

/// Majority gate with invertible inputs
///   The `synth.majority` operation computes the majority function of its
///   inputs, where each operand can be optionally inverted. 
/// 
///   The majority function returns 1 when more than half of the inputs are 1,
///   and 0 otherwise. For three inputs, it's equivalent to:
///   (a & b) | (a & c) | (b & c).
/// 
/// 
///   Example:
/// ```mlir
///     %r0 = synth.majority %a, %b, %c : i1
///     %r1 = synth.majority not %a, %b, not %c : i1
/// ```
class MajorityOp;

} // namespace circt::synth
namespace circt::synth {

/// MUX gate with invertible inputs
/// The `synth.mux_inv` operation represents a 3-input multiplexer node
/// whose operands can be individually inverted before evaluation.
/// The operation chooses between two values based on a condition:
/// given operands (cond, trueValue, falseValue), it calculates `cond ? trueValue : falseValue`,
/// which is equivalent to:
/// 
/// `(cond & trueValue) | (~cond & falseValue)`
/// 
/// Example:
/// ```mlir
///   %r0 = synth.mux_inv %a, %b, %c : i8
///   %r1 = synth.mux_inv not %a, %b, not %c : i8
/// ```
class MuxInverterOp;

} // namespace circt::synth
namespace circt::synth {

/// 3-input Onehot gate with invertible inputs
///     The `synth.onehot` operation computes the one-hot function of its three
///     inputs, where each operand can be optionally inverted. The one-hot function
///     returns 1 when exactly one of the inputs is 1, and 0 otherwise. For three
///     inputs, it is equivalent to:
/// 
///     `(a & ~b & ~c) | (~a & b & ~c) | (~a & ~b & c)`
/// 
///     Example:
/// ```mlir
///       %r0 = synth.onehot %a, %b, %c : i1
///       %r1 = synth.onehot not %a, %b, not %c : i1
/// ```
class OneHotOp;

} // namespace circt::synth
namespace circt::synth {

/// XOR gate with invertible variadic inputs
/// The `synth.xor_inv` operation represents a parity node whose operands may be
/// individually inverted before the XOR is evaluated.
/// 
/// Example:
/// ```mlir
///   %r0 = synth.xor_inv %a, %b : i1
///   %r1 = synth.xor_inv not %a, %b, %c : i8
///   %r2 = synth.xor_inv not %a : i1
/// ```
class XorInverterOp;

} // namespace circt::synth
#ifdef GET_OP_CLASSES
#undef GET_OP_CLASSES

namespace circt::synth::aig {


//===----------------------------------------------------------------------===//
// ::circt::synth::aig::AndInverterOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class AndInverterOpGenericAdaptorBase {
public:
  struct Properties {
    using invertedTy = ::mlir::DenseBoolArrayAttr;
    invertedTy inverted;

    auto getInverted() const {
      auto &propStorage = this->inverted;
      return ::llvm::cast<::mlir::DenseBoolArrayAttr>(propStorage);
    }
    void setInverted(const ::mlir::DenseBoolArrayAttr &propValue) {
      this->inverted = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.inverted == this->inverted &&
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
  AndInverterOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("synth.aig.and_inv", odsAttrs.getContext());
  }

  AndInverterOpGenericAdaptorBase(AndInverterOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::DenseBoolArrayAttr getInvertedAttr() {
    auto attr = ::llvm::cast<::mlir::DenseBoolArrayAttr>(getProperties().inverted);
    return attr;
  }

  ::llvm::ArrayRef<bool> getInverted();
};

} // namespace detail
template <typename RangeT>
class AndInverterOpGenericAdaptor : public detail::AndInverterOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::AndInverterOpGenericAdaptorBase;
  static constexpr int odsIndex_inputs = 0;
public:
  AndInverterOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  AndInverterOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : AndInverterOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  AndInverterOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : AndInverterOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  AndInverterOpGenericAdaptor(RangeT values, const AndInverterOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = AndInverterOp, typename = std::enable_if_t<std::is_same_v<LateInst, AndInverterOp>>>
  AndInverterOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class AndInverterOpAdaptor : public AndInverterOpGenericAdaptor<::mlir::ValueRange> {
public:
  using AndInverterOpGenericAdaptor::AndInverterOpGenericAdaptor;
  AndInverterOpAdaptor(AndInverterOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class AndInverterOp : public ::mlir::Op<AndInverterOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::Type>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::OpTrait::SameOperandsAndResultType, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::circt::synth::BooleanLogicOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = AndInverterOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = AndInverterOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_inputs = 0;
  using Properties = FoldAdaptor::Properties;
  using ::circt::synth::BooleanLogicOpInterface::Trait<AndInverterOp>::getInputs;
  using ::circt::synth::BooleanLogicOpInterface::Trait<AndInverterOp>::getInputPair;
  using ::circt::synth::BooleanLogicOpInterface::Trait<AndInverterOp>::getInput;
  using ::circt::synth::BooleanLogicOpInterface::Trait<AndInverterOp>::isInverted;
  using ::circt::synth::BooleanLogicOpInterface::Trait<AndInverterOp>::getResult;
  using ::circt::synth::BooleanLogicOpInterface::Trait<AndInverterOp>::evaluateBooleanLogic;
  using ::circt::synth::BooleanLogicOpInterface::Trait<AndInverterOp>::emitCNF;
  using ::circt::synth::BooleanLogicOpInterface::Trait<AndInverterOp>::cloneWithSameInversion;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("inverted")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getInvertedAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getInvertedAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("synth.aig.and_inv");
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
  ::mlir::DenseBoolArrayAttr getInvertedAttr() {
    return ::llvm::cast<::mlir::DenseBoolArrayAttr>(getProperties().inverted);
  }

  ::llvm::ArrayRef<bool> getInverted();
  void setInvertedAttr(::mlir::DenseBoolArrayAttr attr) {
    getProperties().inverted = attr;
  }

  void setInverted(::llvm::ArrayRef<bool> attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value input, bool invert = false);
  static AndInverterOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value input, bool invert = false);
  static AndInverterOp create(::mlir::ImplicitLocOpBuilder &builder, Value input, bool invert = false);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value lhs, Value rhs, bool invertLhs = false, bool invertRhs = false);
  static AndInverterOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value lhs, Value rhs, bool invertLhs = false, bool invertRhs = false);
  static AndInverterOp create(::mlir::ImplicitLocOpBuilder &builder, Value lhs, Value rhs, bool invertLhs = false, bool invertRhs = false);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::ValueRange inputs, ::mlir::DenseBoolArrayAttr inverted);
  static AndInverterOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::ValueRange inputs, ::mlir::DenseBoolArrayAttr inverted);
  static AndInverterOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::ValueRange inputs, ::mlir::DenseBoolArrayAttr inverted);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange inputs, ::mlir::DenseBoolArrayAttr inverted);
  static AndInverterOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange inputs, ::mlir::DenseBoolArrayAttr inverted);
  static AndInverterOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange inputs, ::mlir::DenseBoolArrayAttr inverted);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::ValueRange inputs, ::llvm::ArrayRef<bool> inverted);
  static AndInverterOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::ValueRange inputs, ::llvm::ArrayRef<bool> inverted);
  static AndInverterOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::ValueRange inputs, ::llvm::ArrayRef<bool> inverted);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange inputs, ::llvm::ArrayRef<bool> inverted);
  static AndInverterOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange inputs, ::llvm::ArrayRef<bool> inverted);
  static AndInverterOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange inputs, ::llvm::ArrayRef<bool> inverted);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static AndInverterOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static AndInverterOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static AndInverterOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static AndInverterOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange inputs, ::mlir::DenseBoolArrayAttr inverted);
  static AndInverterOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange inputs, ::mlir::DenseBoolArrayAttr inverted);
  static AndInverterOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange inputs, ::mlir::DenseBoolArrayAttr inverted);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange inputs, ::llvm::ArrayRef<bool> inverted);
  static AndInverterOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange inputs, ::llvm::ArrayRef<bool> inverted);
  static AndInverterOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange inputs, ::llvm::ArrayRef<bool> inverted);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static AndInverterOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static AndInverterOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static AndInverterOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static AndInverterOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::llvm::LogicalResult canonicalize(AndInverterOp op, ::mlir::PatternRewriter &rewriter);
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
  ::mlir::OpFoldResult fold(FoldAdaptor adaptor);
  ::llvm::KnownBits computeKnownBits(::llvm::function_ref<const ::llvm::KnownBits &(unsigned)> getInputKnownBits);
  int64_t getLogicDepthCost();
  std::optional<uint64_t> getLogicAreaCost();
  static bool supportsNumInputs(unsigned numInputs);
  static ::llvm::APInt evaluateBooleanLogicWithoutInversion(::llvm::ArrayRef<::llvm::APInt> inputs);
  static bool areInputsPermutationInvariant();
  static void emitCNFWithoutInversion(int outVar, ::llvm::ArrayRef<int> inputVars, ::llvm::function_ref<void(::llvm::ArrayRef<int>)> addClause, ::llvm::function_ref<int()> newVar);
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

} // namespace circt::synth::aig
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::synth::aig::AndInverterOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::synth::aig::detail::AndInverterOpGenericAdaptorBase::Properties)

namespace circt::synth {


//===----------------------------------------------------------------------===//
// ::circt::synth::ChoiceOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ChoiceOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  ChoiceOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("synth.choice", odsAttrs.getContext());
  }

  ChoiceOpGenericAdaptorBase(ChoiceOp op);

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
class ChoiceOpGenericAdaptor : public detail::ChoiceOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ChoiceOpGenericAdaptorBase;
  static constexpr int odsIndex_inputs = 0;
public:
  ChoiceOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ChoiceOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : ChoiceOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ChoiceOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ChoiceOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ChoiceOpGenericAdaptor(RangeT values, const ChoiceOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ChoiceOp, typename = std::enable_if_t<std::is_same_v<LateInst, ChoiceOp>>>
  ChoiceOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class ChoiceOpAdaptor : public ChoiceOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ChoiceOpGenericAdaptor::ChoiceOpGenericAdaptor;
  ChoiceOpAdaptor(ChoiceOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ChoiceOp : public ::mlir::Op<ChoiceOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::Type>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::OpInvariants, ::mlir::OpTrait::SameOperandsAndResultType, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ChoiceOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ChoiceOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_inputs = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("synth.choice");
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::ValueRange inputs);
  static ChoiceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::ValueRange inputs);
  static ChoiceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::ValueRange inputs);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ChoiceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ChoiceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ChoiceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ChoiceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ChoiceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ChoiceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ChoiceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ChoiceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static ::llvm::LogicalResult canonicalize(ChoiceOp op, ::mlir::PatternRewriter &rewriter);
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
  ::mlir::OpFoldResult fold(FoldAdaptor adaptor);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
};

} // namespace circt::synth
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::synth::ChoiceOp)

namespace circt::synth {


//===----------------------------------------------------------------------===//
// ::circt::synth::DotOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class DotOpGenericAdaptorBase {
public:
  struct Properties {
    using invertedTy = ::mlir::DenseBoolArrayAttr;
    invertedTy inverted;

    auto getInverted() const {
      auto &propStorage = this->inverted;
      return ::llvm::cast<::mlir::DenseBoolArrayAttr>(propStorage);
    }
    void setInverted(const ::mlir::DenseBoolArrayAttr &propValue) {
      this->inverted = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.inverted == this->inverted &&
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
  DotOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("synth.dot", odsAttrs.getContext());
  }

  DotOpGenericAdaptorBase(DotOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::DenseBoolArrayAttr getInvertedAttr() {
    auto attr = ::llvm::cast<::mlir::DenseBoolArrayAttr>(getProperties().inverted);
    return attr;
  }

  ::llvm::ArrayRef<bool> getInverted();
};

} // namespace detail
template <typename RangeT>
class DotOpGenericAdaptor : public detail::DotOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::DotOpGenericAdaptorBase;
  static constexpr int odsIndex_inputs = 0;
public:
  DotOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  DotOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : DotOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  DotOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : DotOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  DotOpGenericAdaptor(RangeT values, const DotOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = DotOp, typename = std::enable_if_t<std::is_same_v<LateInst, DotOp>>>
  DotOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class DotOpAdaptor : public DotOpGenericAdaptor<::mlir::ValueRange> {
public:
  using DotOpGenericAdaptor::DotOpGenericAdaptor;
  DotOpAdaptor(DotOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class DotOp : public ::mlir::Op<DotOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::Type>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::OpTrait::SameOperandsAndResultType, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::circt::synth::BooleanLogicOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = DotOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = DotOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_inputs = 0;
  using Properties = FoldAdaptor::Properties;
  using ::circt::synth::BooleanLogicOpInterface::Trait<DotOp>::getInputs;
  using ::circt::synth::BooleanLogicOpInterface::Trait<DotOp>::getInputPair;
  using ::circt::synth::BooleanLogicOpInterface::Trait<DotOp>::getInput;
  using ::circt::synth::BooleanLogicOpInterface::Trait<DotOp>::isInverted;
  using ::circt::synth::BooleanLogicOpInterface::Trait<DotOp>::getResult;
  using ::circt::synth::BooleanLogicOpInterface::Trait<DotOp>::evaluateBooleanLogic;
  using ::circt::synth::BooleanLogicOpInterface::Trait<DotOp>::emitCNF;
  using ::circt::synth::BooleanLogicOpInterface::Trait<DotOp>::cloneWithSameInversion;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("inverted")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getInvertedAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getInvertedAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("synth.dot");
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
  ::mlir::DenseBoolArrayAttr getInvertedAttr() {
    return ::llvm::cast<::mlir::DenseBoolArrayAttr>(getProperties().inverted);
  }

  ::llvm::ArrayRef<bool> getInverted();
  void setInvertedAttr(::mlir::DenseBoolArrayAttr attr) {
    getProperties().inverted = attr;
  }

  void setInverted(::llvm::ArrayRef<bool> attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value a, Value b, Value c, bool invertA = false, bool invertB = false, bool invertC = false);
  static DotOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value a, Value b, Value c, bool invertA = false, bool invertB = false, bool invertC = false);
  static DotOp create(::mlir::ImplicitLocOpBuilder &builder, Value a, Value b, Value c, bool invertA = false, bool invertB = false, bool invertC = false);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::ValueRange inputs, ::mlir::DenseBoolArrayAttr inverted);
  static DotOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::ValueRange inputs, ::mlir::DenseBoolArrayAttr inverted);
  static DotOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::ValueRange inputs, ::mlir::DenseBoolArrayAttr inverted);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange inputs, ::mlir::DenseBoolArrayAttr inverted);
  static DotOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange inputs, ::mlir::DenseBoolArrayAttr inverted);
  static DotOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange inputs, ::mlir::DenseBoolArrayAttr inverted);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::ValueRange inputs, ::llvm::ArrayRef<bool> inverted);
  static DotOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::ValueRange inputs, ::llvm::ArrayRef<bool> inverted);
  static DotOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::ValueRange inputs, ::llvm::ArrayRef<bool> inverted);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange inputs, ::llvm::ArrayRef<bool> inverted);
  static DotOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange inputs, ::llvm::ArrayRef<bool> inverted);
  static DotOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange inputs, ::llvm::ArrayRef<bool> inverted);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static DotOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static DotOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static DotOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static DotOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange inputs, ::mlir::DenseBoolArrayAttr inverted);
  static DotOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange inputs, ::mlir::DenseBoolArrayAttr inverted);
  static DotOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange inputs, ::mlir::DenseBoolArrayAttr inverted);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange inputs, ::llvm::ArrayRef<bool> inverted);
  static DotOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange inputs, ::llvm::ArrayRef<bool> inverted);
  static DotOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange inputs, ::llvm::ArrayRef<bool> inverted);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static DotOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static DotOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static DotOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static DotOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::KnownBits computeKnownBits(::llvm::function_ref<const ::llvm::KnownBits &(unsigned)> getInputKnownBits);
  int64_t getLogicDepthCost();
  std::optional<uint64_t> getLogicAreaCost();
  static bool supportsNumInputs(unsigned numInputs);
  static ::llvm::APInt evaluateBooleanLogicWithoutInversion(::llvm::ArrayRef<::llvm::APInt> inputs);
  static bool areInputsPermutationInvariant();
  static void emitCNFWithoutInversion(int outVar, ::llvm::ArrayRef<int> inputVars, ::llvm::function_ref<void(::llvm::ArrayRef<int>)> addClause, ::llvm::function_ref<int()> newVar);
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

} // namespace circt::synth
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::synth::DotOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::synth::detail::DotOpGenericAdaptorBase::Properties)

namespace circt::synth {


//===----------------------------------------------------------------------===//
// ::circt::synth::GambleOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class GambleOpGenericAdaptorBase {
public:
  struct Properties {
    using invertedTy = ::mlir::DenseBoolArrayAttr;
    invertedTy inverted;

    auto getInverted() const {
      auto &propStorage = this->inverted;
      return ::llvm::cast<::mlir::DenseBoolArrayAttr>(propStorage);
    }
    void setInverted(const ::mlir::DenseBoolArrayAttr &propValue) {
      this->inverted = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.inverted == this->inverted &&
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
  GambleOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("synth.gamble", odsAttrs.getContext());
  }

  GambleOpGenericAdaptorBase(GambleOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::DenseBoolArrayAttr getInvertedAttr() {
    auto attr = ::llvm::cast<::mlir::DenseBoolArrayAttr>(getProperties().inverted);
    return attr;
  }

  ::llvm::ArrayRef<bool> getInverted();
};

} // namespace detail
template <typename RangeT>
class GambleOpGenericAdaptor : public detail::GambleOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::GambleOpGenericAdaptorBase;
  static constexpr int odsIndex_inputs = 0;
public:
  GambleOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  GambleOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : GambleOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  GambleOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : GambleOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  GambleOpGenericAdaptor(RangeT values, const GambleOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = GambleOp, typename = std::enable_if_t<std::is_same_v<LateInst, GambleOp>>>
  GambleOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class GambleOpAdaptor : public GambleOpGenericAdaptor<::mlir::ValueRange> {
public:
  using GambleOpGenericAdaptor::GambleOpGenericAdaptor;
  GambleOpAdaptor(GambleOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class GambleOp : public ::mlir::Op<GambleOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::Type>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::OpTrait::SameOperandsAndResultType, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::circt::synth::BooleanLogicOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = GambleOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = GambleOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_inputs = 0;
  using Properties = FoldAdaptor::Properties;
  using ::circt::synth::BooleanLogicOpInterface::Trait<GambleOp>::getInputs;
  using ::circt::synth::BooleanLogicOpInterface::Trait<GambleOp>::getInputPair;
  using ::circt::synth::BooleanLogicOpInterface::Trait<GambleOp>::getInput;
  using ::circt::synth::BooleanLogicOpInterface::Trait<GambleOp>::isInverted;
  using ::circt::synth::BooleanLogicOpInterface::Trait<GambleOp>::getResult;
  using ::circt::synth::BooleanLogicOpInterface::Trait<GambleOp>::evaluateBooleanLogic;
  using ::circt::synth::BooleanLogicOpInterface::Trait<GambleOp>::emitCNF;
  using ::circt::synth::BooleanLogicOpInterface::Trait<GambleOp>::cloneWithSameInversion;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("inverted")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getInvertedAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getInvertedAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("synth.gamble");
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
  ::mlir::DenseBoolArrayAttr getInvertedAttr() {
    return ::llvm::cast<::mlir::DenseBoolArrayAttr>(getProperties().inverted);
  }

  ::llvm::ArrayRef<bool> getInverted();
  void setInvertedAttr(::mlir::DenseBoolArrayAttr attr) {
    getProperties().inverted = attr;
  }

  void setInverted(::llvm::ArrayRef<bool> attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value a, Value b, Value c, bool invertA = false, bool invertB = false, bool invertC = false);
  static GambleOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value a, Value b, Value c, bool invertA = false, bool invertB = false, bool invertC = false);
  static GambleOp create(::mlir::ImplicitLocOpBuilder &builder, Value a, Value b, Value c, bool invertA = false, bool invertB = false, bool invertC = false);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::ValueRange inputs, ::mlir::DenseBoolArrayAttr inverted);
  static GambleOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::ValueRange inputs, ::mlir::DenseBoolArrayAttr inverted);
  static GambleOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::ValueRange inputs, ::mlir::DenseBoolArrayAttr inverted);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange inputs, ::mlir::DenseBoolArrayAttr inverted);
  static GambleOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange inputs, ::mlir::DenseBoolArrayAttr inverted);
  static GambleOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange inputs, ::mlir::DenseBoolArrayAttr inverted);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::ValueRange inputs, ::llvm::ArrayRef<bool> inverted);
  static GambleOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::ValueRange inputs, ::llvm::ArrayRef<bool> inverted);
  static GambleOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::ValueRange inputs, ::llvm::ArrayRef<bool> inverted);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange inputs, ::llvm::ArrayRef<bool> inverted);
  static GambleOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange inputs, ::llvm::ArrayRef<bool> inverted);
  static GambleOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange inputs, ::llvm::ArrayRef<bool> inverted);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static GambleOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static GambleOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static GambleOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static GambleOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange inputs, ::mlir::DenseBoolArrayAttr inverted);
  static GambleOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange inputs, ::mlir::DenseBoolArrayAttr inverted);
  static GambleOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange inputs, ::mlir::DenseBoolArrayAttr inverted);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange inputs, ::llvm::ArrayRef<bool> inverted);
  static GambleOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange inputs, ::llvm::ArrayRef<bool> inverted);
  static GambleOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange inputs, ::llvm::ArrayRef<bool> inverted);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static GambleOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static GambleOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static GambleOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static GambleOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::KnownBits computeKnownBits(::llvm::function_ref<const ::llvm::KnownBits &(unsigned)> getInputKnownBits);
  int64_t getLogicDepthCost();
  std::optional<uint64_t> getLogicAreaCost();
  static bool supportsNumInputs(unsigned numInputs);
  static ::llvm::APInt evaluateBooleanLogicWithoutInversion(::llvm::ArrayRef<::llvm::APInt> inputs);
  static bool areInputsPermutationInvariant();
  static void emitCNFWithoutInversion(int outVar, ::llvm::ArrayRef<int> inputVars, ::llvm::function_ref<void(::llvm::ArrayRef<int>)> addClause, ::llvm::function_ref<int()> newVar);
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

} // namespace circt::synth
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::synth::GambleOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::synth::detail::GambleOpGenericAdaptorBase::Properties)

namespace circt::synth {


//===----------------------------------------------------------------------===//
// ::circt::synth::MajorityOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class MajorityOpGenericAdaptorBase {
public:
  struct Properties {
    using invertedTy = ::mlir::DenseBoolArrayAttr;
    invertedTy inverted;

    auto getInverted() const {
      auto &propStorage = this->inverted;
      return ::llvm::cast<::mlir::DenseBoolArrayAttr>(propStorage);
    }
    void setInverted(const ::mlir::DenseBoolArrayAttr &propValue) {
      this->inverted = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.inverted == this->inverted &&
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
  MajorityOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("synth.majority", odsAttrs.getContext());
  }

  MajorityOpGenericAdaptorBase(MajorityOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::DenseBoolArrayAttr getInvertedAttr() {
    auto attr = ::llvm::cast<::mlir::DenseBoolArrayAttr>(getProperties().inverted);
    return attr;
  }

  ::llvm::ArrayRef<bool> getInverted();
};

} // namespace detail
template <typename RangeT>
class MajorityOpGenericAdaptor : public detail::MajorityOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::MajorityOpGenericAdaptorBase;
  static constexpr int odsIndex_inputs = 0;
public:
  MajorityOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  MajorityOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : MajorityOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  MajorityOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : MajorityOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  MajorityOpGenericAdaptor(RangeT values, const MajorityOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = MajorityOp, typename = std::enable_if_t<std::is_same_v<LateInst, MajorityOp>>>
  MajorityOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class MajorityOpAdaptor : public MajorityOpGenericAdaptor<::mlir::ValueRange> {
public:
  using MajorityOpGenericAdaptor::MajorityOpGenericAdaptor;
  MajorityOpAdaptor(MajorityOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class MajorityOp : public ::mlir::Op<MajorityOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::Type>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::OpTrait::SameOperandsAndResultType, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::circt::synth::BooleanLogicOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = MajorityOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = MajorityOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_inputs = 0;
  using Properties = FoldAdaptor::Properties;
  using ::circt::synth::BooleanLogicOpInterface::Trait<MajorityOp>::getInputs;
  using ::circt::synth::BooleanLogicOpInterface::Trait<MajorityOp>::getInputPair;
  using ::circt::synth::BooleanLogicOpInterface::Trait<MajorityOp>::getInput;
  using ::circt::synth::BooleanLogicOpInterface::Trait<MajorityOp>::isInverted;
  using ::circt::synth::BooleanLogicOpInterface::Trait<MajorityOp>::getResult;
  using ::circt::synth::BooleanLogicOpInterface::Trait<MajorityOp>::evaluateBooleanLogic;
  using ::circt::synth::BooleanLogicOpInterface::Trait<MajorityOp>::emitCNF;
  using ::circt::synth::BooleanLogicOpInterface::Trait<MajorityOp>::cloneWithSameInversion;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("inverted")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getInvertedAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getInvertedAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("synth.majority");
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
  ::mlir::DenseBoolArrayAttr getInvertedAttr() {
    return ::llvm::cast<::mlir::DenseBoolArrayAttr>(getProperties().inverted);
  }

  ::llvm::ArrayRef<bool> getInverted();
  void setInvertedAttr(::mlir::DenseBoolArrayAttr attr) {
    getProperties().inverted = attr;
  }

  void setInverted(::llvm::ArrayRef<bool> attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value a, Value b, Value c, bool invertA = false, bool invertB = false, bool invertC = false);
  static MajorityOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value a, Value b, Value c, bool invertA = false, bool invertB = false, bool invertC = false);
  static MajorityOp create(::mlir::ImplicitLocOpBuilder &builder, Value a, Value b, Value c, bool invertA = false, bool invertB = false, bool invertC = false);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::ValueRange inputs, ::mlir::DenseBoolArrayAttr inverted);
  static MajorityOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::ValueRange inputs, ::mlir::DenseBoolArrayAttr inverted);
  static MajorityOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::ValueRange inputs, ::mlir::DenseBoolArrayAttr inverted);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange inputs, ::mlir::DenseBoolArrayAttr inverted);
  static MajorityOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange inputs, ::mlir::DenseBoolArrayAttr inverted);
  static MajorityOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange inputs, ::mlir::DenseBoolArrayAttr inverted);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::ValueRange inputs, ::llvm::ArrayRef<bool> inverted);
  static MajorityOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::ValueRange inputs, ::llvm::ArrayRef<bool> inverted);
  static MajorityOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::ValueRange inputs, ::llvm::ArrayRef<bool> inverted);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange inputs, ::llvm::ArrayRef<bool> inverted);
  static MajorityOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange inputs, ::llvm::ArrayRef<bool> inverted);
  static MajorityOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange inputs, ::llvm::ArrayRef<bool> inverted);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static MajorityOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static MajorityOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static MajorityOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static MajorityOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange inputs, ::mlir::DenseBoolArrayAttr inverted);
  static MajorityOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange inputs, ::mlir::DenseBoolArrayAttr inverted);
  static MajorityOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange inputs, ::mlir::DenseBoolArrayAttr inverted);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange inputs, ::llvm::ArrayRef<bool> inverted);
  static MajorityOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange inputs, ::llvm::ArrayRef<bool> inverted);
  static MajorityOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange inputs, ::llvm::ArrayRef<bool> inverted);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static MajorityOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static MajorityOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static MajorityOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static MajorityOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::KnownBits computeKnownBits(::llvm::function_ref<const ::llvm::KnownBits &(unsigned)> getInputKnownBits);
  int64_t getLogicDepthCost();
  std::optional<uint64_t> getLogicAreaCost();
  static bool supportsNumInputs(unsigned numInputs);
  static ::llvm::APInt evaluateBooleanLogicWithoutInversion(::llvm::ArrayRef<::llvm::APInt> inputs);
  static bool areInputsPermutationInvariant();
  static void emitCNFWithoutInversion(int outVar, ::llvm::ArrayRef<int> inputVars, ::llvm::function_ref<void(::llvm::ArrayRef<int>)> addClause, ::llvm::function_ref<int()> newVar);
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

} // namespace circt::synth
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::synth::MajorityOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::synth::detail::MajorityOpGenericAdaptorBase::Properties)

namespace circt::synth {


//===----------------------------------------------------------------------===//
// ::circt::synth::MuxInverterOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class MuxInverterOpGenericAdaptorBase {
public:
  struct Properties {
    using invertedTy = ::mlir::DenseBoolArrayAttr;
    invertedTy inverted;

    auto getInverted() const {
      auto &propStorage = this->inverted;
      return ::llvm::cast<::mlir::DenseBoolArrayAttr>(propStorage);
    }
    void setInverted(const ::mlir::DenseBoolArrayAttr &propValue) {
      this->inverted = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.inverted == this->inverted &&
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
  MuxInverterOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("synth.mux_inv", odsAttrs.getContext());
  }

  MuxInverterOpGenericAdaptorBase(MuxInverterOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::DenseBoolArrayAttr getInvertedAttr() {
    auto attr = ::llvm::cast<::mlir::DenseBoolArrayAttr>(getProperties().inverted);
    return attr;
  }

  ::llvm::ArrayRef<bool> getInverted();
};

} // namespace detail
template <typename RangeT>
class MuxInverterOpGenericAdaptor : public detail::MuxInverterOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::MuxInverterOpGenericAdaptorBase;
  static constexpr int odsIndex_inputs = 0;
public:
  MuxInverterOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  MuxInverterOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : MuxInverterOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  MuxInverterOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : MuxInverterOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  MuxInverterOpGenericAdaptor(RangeT values, const MuxInverterOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = MuxInverterOp, typename = std::enable_if_t<std::is_same_v<LateInst, MuxInverterOp>>>
  MuxInverterOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class MuxInverterOpAdaptor : public MuxInverterOpGenericAdaptor<::mlir::ValueRange> {
public:
  using MuxInverterOpGenericAdaptor::MuxInverterOpGenericAdaptor;
  MuxInverterOpAdaptor(MuxInverterOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class MuxInverterOp : public ::mlir::Op<MuxInverterOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::Type>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::OpTrait::SameOperandsAndResultType, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::circt::synth::BooleanLogicOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = MuxInverterOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = MuxInverterOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_inputs = 0;
  using Properties = FoldAdaptor::Properties;
  using ::circt::synth::BooleanLogicOpInterface::Trait<MuxInverterOp>::getInputs;
  using ::circt::synth::BooleanLogicOpInterface::Trait<MuxInverterOp>::getInputPair;
  using ::circt::synth::BooleanLogicOpInterface::Trait<MuxInverterOp>::getInput;
  using ::circt::synth::BooleanLogicOpInterface::Trait<MuxInverterOp>::isInverted;
  using ::circt::synth::BooleanLogicOpInterface::Trait<MuxInverterOp>::getResult;
  using ::circt::synth::BooleanLogicOpInterface::Trait<MuxInverterOp>::evaluateBooleanLogic;
  using ::circt::synth::BooleanLogicOpInterface::Trait<MuxInverterOp>::emitCNF;
  using ::circt::synth::BooleanLogicOpInterface::Trait<MuxInverterOp>::cloneWithSameInversion;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("inverted")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getInvertedAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getInvertedAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("synth.mux_inv");
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
  ::mlir::DenseBoolArrayAttr getInvertedAttr() {
    return ::llvm::cast<::mlir::DenseBoolArrayAttr>(getProperties().inverted);
  }

  ::llvm::ArrayRef<bool> getInverted();
  void setInvertedAttr(::mlir::DenseBoolArrayAttr attr) {
    getProperties().inverted = attr;
  }

  void setInverted(::llvm::ArrayRef<bool> attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value a, Value b, Value c, bool invertA = false, bool invertB = false, bool invertC = false);
  static MuxInverterOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value a, Value b, Value c, bool invertA = false, bool invertB = false, bool invertC = false);
  static MuxInverterOp create(::mlir::ImplicitLocOpBuilder &builder, Value a, Value b, Value c, bool invertA = false, bool invertB = false, bool invertC = false);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::ValueRange inputs, ::mlir::DenseBoolArrayAttr inverted);
  static MuxInverterOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::ValueRange inputs, ::mlir::DenseBoolArrayAttr inverted);
  static MuxInverterOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::ValueRange inputs, ::mlir::DenseBoolArrayAttr inverted);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange inputs, ::mlir::DenseBoolArrayAttr inverted);
  static MuxInverterOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange inputs, ::mlir::DenseBoolArrayAttr inverted);
  static MuxInverterOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange inputs, ::mlir::DenseBoolArrayAttr inverted);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::ValueRange inputs, ::llvm::ArrayRef<bool> inverted);
  static MuxInverterOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::ValueRange inputs, ::llvm::ArrayRef<bool> inverted);
  static MuxInverterOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::ValueRange inputs, ::llvm::ArrayRef<bool> inverted);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange inputs, ::llvm::ArrayRef<bool> inverted);
  static MuxInverterOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange inputs, ::llvm::ArrayRef<bool> inverted);
  static MuxInverterOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange inputs, ::llvm::ArrayRef<bool> inverted);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static MuxInverterOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static MuxInverterOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static MuxInverterOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static MuxInverterOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange inputs, ::mlir::DenseBoolArrayAttr inverted);
  static MuxInverterOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange inputs, ::mlir::DenseBoolArrayAttr inverted);
  static MuxInverterOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange inputs, ::mlir::DenseBoolArrayAttr inverted);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange inputs, ::llvm::ArrayRef<bool> inverted);
  static MuxInverterOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange inputs, ::llvm::ArrayRef<bool> inverted);
  static MuxInverterOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange inputs, ::llvm::ArrayRef<bool> inverted);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static MuxInverterOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static MuxInverterOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static MuxInverterOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static MuxInverterOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::KnownBits computeKnownBits(::llvm::function_ref<const ::llvm::KnownBits &(unsigned)> getInputKnownBits);
  int64_t getLogicDepthCost();
  std::optional<uint64_t> getLogicAreaCost();
  static bool supportsNumInputs(unsigned numInputs);
  static ::llvm::APInt evaluateBooleanLogicWithoutInversion(::llvm::ArrayRef<::llvm::APInt> inputs);
  static bool areInputsPermutationInvariant();
  static void emitCNFWithoutInversion(int outVar, ::llvm::ArrayRef<int> inputVars, ::llvm::function_ref<void(::llvm::ArrayRef<int>)> addClause, ::llvm::function_ref<int()> newVar);
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

} // namespace circt::synth
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::synth::MuxInverterOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::synth::detail::MuxInverterOpGenericAdaptorBase::Properties)

namespace circt::synth {


//===----------------------------------------------------------------------===//
// ::circt::synth::OneHotOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class OneHotOpGenericAdaptorBase {
public:
  struct Properties {
    using invertedTy = ::mlir::DenseBoolArrayAttr;
    invertedTy inverted;

    auto getInverted() const {
      auto &propStorage = this->inverted;
      return ::llvm::cast<::mlir::DenseBoolArrayAttr>(propStorage);
    }
    void setInverted(const ::mlir::DenseBoolArrayAttr &propValue) {
      this->inverted = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.inverted == this->inverted &&
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
  OneHotOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("synth.onehot", odsAttrs.getContext());
  }

  OneHotOpGenericAdaptorBase(OneHotOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::DenseBoolArrayAttr getInvertedAttr() {
    auto attr = ::llvm::cast<::mlir::DenseBoolArrayAttr>(getProperties().inverted);
    return attr;
  }

  ::llvm::ArrayRef<bool> getInverted();
};

} // namespace detail
template <typename RangeT>
class OneHotOpGenericAdaptor : public detail::OneHotOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::OneHotOpGenericAdaptorBase;
  static constexpr int odsIndex_inputs = 0;
public:
  OneHotOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  OneHotOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : OneHotOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  OneHotOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : OneHotOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  OneHotOpGenericAdaptor(RangeT values, const OneHotOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = OneHotOp, typename = std::enable_if_t<std::is_same_v<LateInst, OneHotOp>>>
  OneHotOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class OneHotOpAdaptor : public OneHotOpGenericAdaptor<::mlir::ValueRange> {
public:
  using OneHotOpGenericAdaptor::OneHotOpGenericAdaptor;
  OneHotOpAdaptor(OneHotOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class OneHotOp : public ::mlir::Op<OneHotOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::Type>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::OpTrait::SameOperandsAndResultType, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::circt::synth::BooleanLogicOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = OneHotOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = OneHotOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_inputs = 0;
  using Properties = FoldAdaptor::Properties;
  using ::circt::synth::BooleanLogicOpInterface::Trait<OneHotOp>::getInputs;
  using ::circt::synth::BooleanLogicOpInterface::Trait<OneHotOp>::getInputPair;
  using ::circt::synth::BooleanLogicOpInterface::Trait<OneHotOp>::getInput;
  using ::circt::synth::BooleanLogicOpInterface::Trait<OneHotOp>::isInverted;
  using ::circt::synth::BooleanLogicOpInterface::Trait<OneHotOp>::getResult;
  using ::circt::synth::BooleanLogicOpInterface::Trait<OneHotOp>::evaluateBooleanLogic;
  using ::circt::synth::BooleanLogicOpInterface::Trait<OneHotOp>::emitCNF;
  using ::circt::synth::BooleanLogicOpInterface::Trait<OneHotOp>::cloneWithSameInversion;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("inverted")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getInvertedAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getInvertedAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("synth.onehot");
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
  ::mlir::DenseBoolArrayAttr getInvertedAttr() {
    return ::llvm::cast<::mlir::DenseBoolArrayAttr>(getProperties().inverted);
  }

  ::llvm::ArrayRef<bool> getInverted();
  void setInvertedAttr(::mlir::DenseBoolArrayAttr attr) {
    getProperties().inverted = attr;
  }

  void setInverted(::llvm::ArrayRef<bool> attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value a, Value b, Value c, bool invertA = false, bool invertB = false, bool invertC = false);
  static OneHotOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value a, Value b, Value c, bool invertA = false, bool invertB = false, bool invertC = false);
  static OneHotOp create(::mlir::ImplicitLocOpBuilder &builder, Value a, Value b, Value c, bool invertA = false, bool invertB = false, bool invertC = false);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::ValueRange inputs, ::mlir::DenseBoolArrayAttr inverted);
  static OneHotOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::ValueRange inputs, ::mlir::DenseBoolArrayAttr inverted);
  static OneHotOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::ValueRange inputs, ::mlir::DenseBoolArrayAttr inverted);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange inputs, ::mlir::DenseBoolArrayAttr inverted);
  static OneHotOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange inputs, ::mlir::DenseBoolArrayAttr inverted);
  static OneHotOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange inputs, ::mlir::DenseBoolArrayAttr inverted);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::ValueRange inputs, ::llvm::ArrayRef<bool> inverted);
  static OneHotOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::ValueRange inputs, ::llvm::ArrayRef<bool> inverted);
  static OneHotOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::ValueRange inputs, ::llvm::ArrayRef<bool> inverted);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange inputs, ::llvm::ArrayRef<bool> inverted);
  static OneHotOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange inputs, ::llvm::ArrayRef<bool> inverted);
  static OneHotOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange inputs, ::llvm::ArrayRef<bool> inverted);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static OneHotOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static OneHotOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static OneHotOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static OneHotOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange inputs, ::mlir::DenseBoolArrayAttr inverted);
  static OneHotOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange inputs, ::mlir::DenseBoolArrayAttr inverted);
  static OneHotOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange inputs, ::mlir::DenseBoolArrayAttr inverted);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange inputs, ::llvm::ArrayRef<bool> inverted);
  static OneHotOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange inputs, ::llvm::ArrayRef<bool> inverted);
  static OneHotOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange inputs, ::llvm::ArrayRef<bool> inverted);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static OneHotOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static OneHotOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static OneHotOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static OneHotOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::KnownBits computeKnownBits(::llvm::function_ref<const ::llvm::KnownBits &(unsigned)> getInputKnownBits);
  int64_t getLogicDepthCost();
  std::optional<uint64_t> getLogicAreaCost();
  static bool supportsNumInputs(unsigned numInputs);
  static ::llvm::APInt evaluateBooleanLogicWithoutInversion(::llvm::ArrayRef<::llvm::APInt> inputs);
  static bool areInputsPermutationInvariant();
  static void emitCNFWithoutInversion(int outVar, ::llvm::ArrayRef<int> inputVars, ::llvm::function_ref<void(::llvm::ArrayRef<int>)> addClause, ::llvm::function_ref<int()> newVar);
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

} // namespace circt::synth
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::synth::OneHotOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::synth::detail::OneHotOpGenericAdaptorBase::Properties)

namespace circt::synth {


//===----------------------------------------------------------------------===//
// ::circt::synth::XorInverterOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class XorInverterOpGenericAdaptorBase {
public:
  struct Properties {
    using invertedTy = ::mlir::DenseBoolArrayAttr;
    invertedTy inverted;

    auto getInverted() const {
      auto &propStorage = this->inverted;
      return ::llvm::cast<::mlir::DenseBoolArrayAttr>(propStorage);
    }
    void setInverted(const ::mlir::DenseBoolArrayAttr &propValue) {
      this->inverted = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.inverted == this->inverted &&
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
  XorInverterOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("synth.xor_inv", odsAttrs.getContext());
  }

  XorInverterOpGenericAdaptorBase(XorInverterOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::DenseBoolArrayAttr getInvertedAttr() {
    auto attr = ::llvm::cast<::mlir::DenseBoolArrayAttr>(getProperties().inverted);
    return attr;
  }

  ::llvm::ArrayRef<bool> getInverted();
};

} // namespace detail
template <typename RangeT>
class XorInverterOpGenericAdaptor : public detail::XorInverterOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::XorInverterOpGenericAdaptorBase;
  static constexpr int odsIndex_inputs = 0;
public:
  XorInverterOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  XorInverterOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : XorInverterOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  XorInverterOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : XorInverterOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  XorInverterOpGenericAdaptor(RangeT values, const XorInverterOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = XorInverterOp, typename = std::enable_if_t<std::is_same_v<LateInst, XorInverterOp>>>
  XorInverterOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class XorInverterOpAdaptor : public XorInverterOpGenericAdaptor<::mlir::ValueRange> {
public:
  using XorInverterOpGenericAdaptor::XorInverterOpGenericAdaptor;
  XorInverterOpAdaptor(XorInverterOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class XorInverterOp : public ::mlir::Op<XorInverterOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::Type>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::OpTrait::SameOperandsAndResultType, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::circt::synth::BooleanLogicOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = XorInverterOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = XorInverterOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_inputs = 0;
  using Properties = FoldAdaptor::Properties;
  using ::circt::synth::BooleanLogicOpInterface::Trait<XorInverterOp>::getInputs;
  using ::circt::synth::BooleanLogicOpInterface::Trait<XorInverterOp>::getInputPair;
  using ::circt::synth::BooleanLogicOpInterface::Trait<XorInverterOp>::getInput;
  using ::circt::synth::BooleanLogicOpInterface::Trait<XorInverterOp>::isInverted;
  using ::circt::synth::BooleanLogicOpInterface::Trait<XorInverterOp>::getResult;
  using ::circt::synth::BooleanLogicOpInterface::Trait<XorInverterOp>::evaluateBooleanLogic;
  using ::circt::synth::BooleanLogicOpInterface::Trait<XorInverterOp>::emitCNF;
  using ::circt::synth::BooleanLogicOpInterface::Trait<XorInverterOp>::cloneWithSameInversion;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("inverted")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getInvertedAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getInvertedAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("synth.xor_inv");
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
  ::mlir::DenseBoolArrayAttr getInvertedAttr() {
    return ::llvm::cast<::mlir::DenseBoolArrayAttr>(getProperties().inverted);
  }

  ::llvm::ArrayRef<bool> getInverted();
  void setInvertedAttr(::mlir::DenseBoolArrayAttr attr) {
    getProperties().inverted = attr;
  }

  void setInverted(::llvm::ArrayRef<bool> attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value input, bool invert = false);
  static XorInverterOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value input, bool invert = false);
  static XorInverterOp create(::mlir::ImplicitLocOpBuilder &builder, Value input, bool invert = false);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value lhs, Value rhs, bool invertLhs = false, bool invertRhs = false);
  static XorInverterOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value lhs, Value rhs, bool invertLhs = false, bool invertRhs = false);
  static XorInverterOp create(::mlir::ImplicitLocOpBuilder &builder, Value lhs, Value rhs, bool invertLhs = false, bool invertRhs = false);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ArrayRef<std::pair<Value, bool>> operands);
  static XorInverterOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ArrayRef<std::pair<Value, bool>> operands);
  static XorInverterOp create(::mlir::ImplicitLocOpBuilder &builder, ArrayRef<std::pair<Value, bool>> operands);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::ValueRange inputs, ::mlir::DenseBoolArrayAttr inverted);
  static XorInverterOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::ValueRange inputs, ::mlir::DenseBoolArrayAttr inverted);
  static XorInverterOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::ValueRange inputs, ::mlir::DenseBoolArrayAttr inverted);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange inputs, ::mlir::DenseBoolArrayAttr inverted);
  static XorInverterOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange inputs, ::mlir::DenseBoolArrayAttr inverted);
  static XorInverterOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange inputs, ::mlir::DenseBoolArrayAttr inverted);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::ValueRange inputs, ::llvm::ArrayRef<bool> inverted);
  static XorInverterOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::ValueRange inputs, ::llvm::ArrayRef<bool> inverted);
  static XorInverterOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::ValueRange inputs, ::llvm::ArrayRef<bool> inverted);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange inputs, ::llvm::ArrayRef<bool> inverted);
  static XorInverterOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange inputs, ::llvm::ArrayRef<bool> inverted);
  static XorInverterOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange inputs, ::llvm::ArrayRef<bool> inverted);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static XorInverterOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static XorInverterOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static XorInverterOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static XorInverterOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange inputs, ::mlir::DenseBoolArrayAttr inverted);
  static XorInverterOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange inputs, ::mlir::DenseBoolArrayAttr inverted);
  static XorInverterOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange inputs, ::mlir::DenseBoolArrayAttr inverted);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange inputs, ::llvm::ArrayRef<bool> inverted);
  static XorInverterOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange inputs, ::llvm::ArrayRef<bool> inverted);
  static XorInverterOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange inputs, ::llvm::ArrayRef<bool> inverted);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static XorInverterOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static XorInverterOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static XorInverterOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static XorInverterOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::llvm::LogicalResult canonicalize(XorInverterOp op, ::mlir::PatternRewriter &rewriter);
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
  ::mlir::OpFoldResult fold(FoldAdaptor adaptor);
  ::llvm::KnownBits computeKnownBits(::llvm::function_ref<const ::llvm::KnownBits &(unsigned)> getInputKnownBits);
  int64_t getLogicDepthCost();
  std::optional<uint64_t> getLogicAreaCost();
  static bool supportsNumInputs(unsigned numInputs);
  static ::llvm::APInt evaluateBooleanLogicWithoutInversion(::llvm::ArrayRef<::llvm::APInt> inputs);
  static bool areInputsPermutationInvariant();
  static void emitCNFWithoutInversion(int outVar, ::llvm::ArrayRef<int> inputVars, ::llvm::function_ref<void(::llvm::ArrayRef<int>)> addClause, ::llvm::function_ref<int()> newVar);
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

} // namespace circt::synth
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::synth::XorInverterOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::synth::detail::XorInverterOpGenericAdaptorBase::Properties)


#endif // GET_OP_CLASSES

