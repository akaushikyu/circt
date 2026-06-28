/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Op Declarations                                                            *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: HW.td                                                                *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace circt::hw {

/// Produce a constant aggregate value
/// This operation produces a constant value of an aggregate type. Clock and
/// reset values are supported. For nested aggregates, embedded arrays are
/// used.
/// 
/// Examples:
/// ```mlir
///   %result = hw.aggregate_constant [1 : i1, 2 : i2, 3 : i2] : !hw.struct<a: i8, b: i8, c: i8>
///   %result = hw.aggregate_constant [1 : i1, [2 : i2, 3 : i2]] : !hw.struct<a: i8, b: vector<i8, 2>>
/// ```
class AggregateConstantOp;

} // namespace circt::hw
namespace circt::hw {

/// Concatenate some arrays
/// Creates an array by concatenating a variable set of arrays. One or more
/// values must be listed.
/// 
/// ```
/// // %a, %b, %c are hw arrays of i4 with sizes 2, 5, and 4 respectively.
/// %array = hw.array_concat %a, %b, %c : (2, 5, 4 x i4)
/// // %array is !hw.array<11 x i4>
/// ```
/// 
/// See the HW-SV rationale document for details on operand ordering.
class ArrayConcatOp;

} // namespace circt::hw
namespace circt::hw {

/// Create an array from values
/// Creates an array from a variable set of values. One or more values must be
/// listed.
/// 
/// ```
/// // %a, %b, %c are all i4
/// %array = hw.array_create %a, %b, %c : i4
/// ```
/// 
/// Optionally, the result type can be explicitly specified to support type
/// aliases:
/// 
/// ```
/// // Create an array with a type alias result
/// %array = hw.array_create %a, %b : i4 -> !MyArrayAlias
/// ```
/// 
/// See the HW-SV rationale document for details on operand ordering.
class ArrayCreateOp;

} // namespace circt::hw
namespace circt::hw {

/// Extract an element from an array
/// Extracts the element at `index` from the given `input` array. The index must
/// be exactly `ceil(log2(length(input)))` bits wide.
class ArrayGetOp;

} // namespace circt::hw
namespace circt::hw {

/// Inject an element into an array
/// Takes an `input` array, changes the element at `index` to the given
/// `element` value, and returns the updated array value as a result. The index
/// must be exactly `ceil(log2(length(input)))` bits wide. The element type
/// must match the input array's element type.
/// 
/// If the `index` is out of bounds, the result is undefined.
class ArrayInjectOp;

} // namespace circt::hw
namespace circt::hw {

/// Get a range of values from an array
/// Extracts a sub-range from an array. The range is from `lowIndex` to
/// `lowIndex` + the number of elements in the return type, non-inclusive on
/// the high end. For instance,
/// 
/// ```
/// // Slices 16 elements starting at '%offset'.
/// %subArray = hw.slice %largerArray at %offset :
///     (!hw.array<1024xi8>) -> !hw.array<16xi8>
/// ```
/// 
/// Width of 'idx' is defined to be the precise number of bits required to
/// index the 'input' array. More precisely: for an input array of size M,
/// the width of 'idx' is ceil(log2(M)). Lower and upper bound indexes which
/// are larger than the size of the 'input' array results in undefined
/// behavior.
class ArraySliceOp;

} // namespace circt::hw
namespace circt::hw {

/// Reinterpret one value to another value of the same size and
/// potentially different type.  See the `hw` dialect rationale document for
/// more details.
class BitcastOp;

} // namespace circt::hw
namespace circt::hw {

/// Produce a constant value
/// The constant operation produces a constant value of standard integer type
/// without a sign.
/// ```
///   %result = hw.constant 42 : t1
/// ```
class ConstantOp;

} // namespace circt::hw
namespace circt::hw {

/// Compare two values of an enumeration
/// This operation compares two values with the same canonical enumeration
/// type, returning 0 if they are different, and 1 if they are the same.
/// 
/// Example:
/// ```mlir
///   %enumcmp = hw.enum.cmp %A, %B : !hw.enum<A, B, C>, !hw.enum<A, B, C>
/// ```
class EnumCmpOp;

} // namespace circt::hw
namespace circt::hw {

/// Produce a constant enumeration value.
/// The enum.constant operation produces an enumeration value of the specified
/// enum value attribute.
/// ```
///   %0 = hw.enum.constant A : !hw.enum<A, B, C>
/// ```
class EnumConstantOp;

} // namespace circt::hw
namespace circt::hw {

/// HW Generator Schema declaration
/// The "hw.generator.schema" operation declares a kind of generated module by
/// declaring the schema of meta-data required.
/// A generated module instance of a schema is independent of the external
/// method of producing it.  It is assumed that for well known schema instances,
/// multiple external tools might exist which can process it.  Generator nodes
/// list attributes required by hw.module.generated instances.
/// 
/// Example:
/// ```mlir
/// generator.schema @MEMORY, "Simple-Memory", ["ports", "write_latency", "read_latency"]
/// module.generated @mymem, @MEMORY(ports)
///   -> (ports) {write_latency=1, read_latency=1, ports=["read","write"]}
/// ```
class HWGeneratorSchemaOp;

} // namespace circt::hw
namespace circt::hw {

/// HW external Module
/// The "hw.module.extern" operation represents an external reference to a
/// Verilog module, including a given name and a list of ports.
/// 
/// The 'verilogName' attribute (when present) specifies the spelling of the
/// module name in Verilog we can use.  TODO: This is a hack because we don't
/// have proper parameterization in the hw.dialect.  We need a way to represent
/// parameterized types instead of just concrete types.
class HWModuleExternOp;

} // namespace circt::hw
namespace circt::hw {

/// HW Generated Module
/// The "hw.module.generated" operation represents a reference to an external
/// module that will be produced by some external process.
/// This represents the name and list of ports to be generated.
/// 
/// The 'verilogName' attribute (when present) specifies the spelling of the
/// module name in Verilog we can use.  See hw.module for an explanation.
class HWModuleGeneratedOp;

} // namespace circt::hw
namespace circt::hw {

/// HW Module
/// The "hw.module" operation represents a Verilog module, including a given
/// name, a list of ports, a list of parameters, and a body that represents the
/// connections within the module.
class HWModuleOp;

} // namespace circt::hw
namespace circt::hw {

/// Hierarchical path specification
/// The "hw.hierpath" operation represents a path through the hierarchy.
/// This is used to specify namable things for use in other operations, for
/// example in verbatim substitution. Non-local annotations also use these.
class HierPathOp;

} // namespace circt::hw
namespace circt::hw {

/// Create an instance of a module
/// This represents an instance of a module. The inputs and outputs are
/// the referenced module's inputs and outputs.  The `argNames` and
/// `resultNames` attributes must match the referenced module.
/// 
/// Any parameters in the "old" format (slated to be removed) are stored in the
/// `oldParameters` dictionary.
class InstanceOp;

} // namespace circt::hw
namespace circt::hw {

/// HW termination operation
/// "hw.output" marks the end of a region in the HW dialect and the values
/// to put on the output ports.
class OutputOp;

} // namespace circt::hw
namespace circt::hw {

/// Return the value of a parameter expression as an SSA value that may be used
/// by other ops.
class ParamValueOp;

} // namespace circt::hw
namespace circt::hw {

/// Create a struct from constituent parts.
class StructCreateOp;

} // namespace circt::hw
namespace circt::hw {

/// Expand a struct into its constituent parts.
/// ```
/// %result:2 = hw.struct_explode %input : !hw.struct<foo: i19, bar: i7>
/// ```
class StructExplodeOp;

} // namespace circt::hw
namespace circt::hw {

/// Extract a named field from a struct.
/// ```
/// %result = hw.struct_extract %input["field"] : !hw.struct<field: type>
/// ```
class StructExtractOp;

} // namespace circt::hw
namespace circt::hw {

/// Inject a value into a named field of a struct.
/// ```
/// %result = hw.struct_inject %input["field"], %newValue
///     : !hw.struct<field: type>
/// ```
class StructInjectOp;

} // namespace circt::hw
namespace circt::hw {

/// A procedural region with a trigger condition
/// A procedural region that can be triggered by an event. The trigger
/// condition is a 1-bit value that is activated based on some event control
/// attribute.
/// The operation is `IsolatedFromAbove`, and thus requires values passed into
/// the trigger region to be explicitly passed in through the `inputs` list.
class TriggeredOp;

} // namespace circt::hw
namespace circt::hw {

/// Type declaration wrapper.
/// An operation whose one body block contains type declarations. This op
/// provides a scope for type declarations at the top level of an MLIR module.
/// It is a symbol that may be looked up within the module, as well as a symbol
/// table itself, so type declarations may be looked up.
class TypeScopeOp;

} // namespace circt::hw
namespace circt::hw {

/// Type declaration.
/// Associate a symbolic name with a type.
class TypedeclOp;

} // namespace circt::hw
namespace circt::hw {

/// Create a union with the specified value.
/// Create a union with the value 'input' at the specified field's offset. The
/// value of the bits in the underlying representation that are not covered by
/// the specified field is undefined.
/// 
/// ```
///   %x = hw.constant 0 : i3
///   %z = hw.union_create "bar", %x : !hw.union<bar: i3, baz: i8>
/// ```
class UnionCreateOp;

} // namespace circt::hw
namespace circt::hw {

/// Get a union member.
/// Get the value of a union, interpreting it as the type of the specified
/// member field.
/// 
/// ```
///   %u = ...
///   %v = hw.union_extract %u["foo"] : !hw.union<foo: i3, bar: i16>
///   // %v is of type 'i3'
/// ```
class UnionExtractOp;

} // namespace circt::hw
namespace circt::hw {

/// Assign a name or symbol to an SSA edge
/// An `hw.wire` is used to assign a human-readable name or a symbol for remote
/// references to an SSA edge. It takes a single operand and returns its value
/// unchanged as a result. The operation guarantees the following:
/// 
/// - If the wire has a symbol, the value of its operand remains observable
///   under that symbol within the IR.
/// 
/// - If the wire has a name, the name is treated as a hint. If the wire
///   persists until code generation the resulting wire will have this name,
///   with a potential suffix to ensure uniqueness. If the wire is canonicalized
///   away, its name is propagated to its input operand as a name hint.
/// 
/// - The users of its result will always observe the operand through the
///   operation itself, meaning that optimizations cannot bypass the wire. This
///   ensures that if the wire's value is *forced*, for example through a
///   Verilog force statement, the forced value will affect all users of the
///   wire in the output.
/// 
/// Example:
/// ```
/// %1 = hw.wire %0 : i42
/// %2 = hw.wire %0 sym @mySym : i42
/// %3 = hw.wire %0 name "myWire" : i42
/// %myWire = hw.wire %0 : i42
/// ```
class WireOp;

} // namespace circt::hw
#ifdef GET_OP_CLASSES
#undef GET_OP_CLASSES

namespace circt::hw {


//===----------------------------------------------------------------------===//
// ::circt::hw::AggregateConstantOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class AggregateConstantOpGenericAdaptorBase {
public:
  struct Properties {
    using fieldsTy = ::mlir::ArrayAttr;
    fieldsTy fields;

    auto getFields() const {
      auto &propStorage = this->fields;
      return ::llvm::cast<::mlir::ArrayAttr>(propStorage);
    }
    void setFields(const ::mlir::ArrayAttr &propValue) {
      this->fields = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.fields == this->fields &&
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
  AggregateConstantOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("hw.aggregate_constant", odsAttrs.getContext());
  }

  AggregateConstantOpGenericAdaptorBase(AggregateConstantOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::ArrayAttr getFieldsAttr() {
    auto attr = ::llvm::cast<::mlir::ArrayAttr>(getProperties().fields);
    return attr;
  }

  ::mlir::ArrayAttr getFields();
};

} // namespace detail
template <typename RangeT>
class AggregateConstantOpGenericAdaptor : public detail::AggregateConstantOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::AggregateConstantOpGenericAdaptorBase;
public:
  AggregateConstantOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  AggregateConstantOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : AggregateConstantOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  AggregateConstantOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : AggregateConstantOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  AggregateConstantOpGenericAdaptor(RangeT values, const AggregateConstantOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = AggregateConstantOp, typename = std::enable_if_t<std::is_same_v<LateInst, AggregateConstantOp>>>
  AggregateConstantOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class AggregateConstantOpAdaptor : public AggregateConstantOpGenericAdaptor<::mlir::ValueRange> {
public:
  using AggregateConstantOpGenericAdaptor::AggregateConstantOpGenericAdaptor;
  AggregateConstantOpAdaptor(AggregateConstantOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class AggregateConstantOp : public ::mlir::Op<AggregateConstantOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::circt::hw::TypeVariant<
      ::circt::hw::ArrayType,
      ::circt::hw::UnpackedArrayType,
      ::circt::hw::StructType>>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::OpTrait::ConstantLike> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = AggregateConstantOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = AggregateConstantOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("fields")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getFieldsAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getFieldsAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("hw.aggregate_constant");
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

  ::mlir::TypedValue<::circt::hw::TypeVariant<
        ::circt::hw::ArrayType,
        ::circt::hw::UnpackedArrayType,
        ::circt::hw::StructType>> getResult() {
    return ::llvm::cast<::mlir::TypedValue<::circt::hw::TypeVariant<
        ::circt::hw::ArrayType,
        ::circt::hw::UnpackedArrayType,
        ::circt::hw::StructType>>>(*getODSResults(0).begin());
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
  ::mlir::ArrayAttr getFieldsAttr() {
    return ::llvm::cast<::mlir::ArrayAttr>(getProperties().fields);
  }

  ::mlir::ArrayAttr getFields();
  void setFieldsAttr(::mlir::ArrayAttr attr) {
    getProperties().fields = attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::ArrayAttr fields);
  static AggregateConstantOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::ArrayAttr fields);
  static AggregateConstantOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::ArrayAttr fields);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ArrayAttr fields);
  static AggregateConstantOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ArrayAttr fields);
  static AggregateConstantOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ArrayAttr fields);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static AggregateConstantOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static AggregateConstantOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static AggregateConstantOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static AggregateConstantOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  ::mlir::OpFoldResult fold(FoldAdaptor adaptor);
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

} // namespace circt::hw
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::hw::AggregateConstantOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::hw::detail::AggregateConstantOpGenericAdaptorBase::Properties)

namespace circt::hw {


//===----------------------------------------------------------------------===//
// ::circt::hw::ArrayConcatOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ArrayConcatOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  ArrayConcatOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("hw.array_concat", odsAttrs.getContext());
  }

  ArrayConcatOpGenericAdaptorBase(ArrayConcatOp op);

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
class ArrayConcatOpGenericAdaptor : public detail::ArrayConcatOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ArrayConcatOpGenericAdaptorBase;
  static constexpr int odsIndex_inputs = 0;
public:
  ArrayConcatOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ArrayConcatOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : ArrayConcatOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ArrayConcatOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ArrayConcatOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ArrayConcatOpGenericAdaptor(RangeT values, const ArrayConcatOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ArrayConcatOp, typename = std::enable_if_t<std::is_same_v<LateInst, ArrayConcatOp>>>
  ArrayConcatOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class ArrayConcatOpAdaptor : public ArrayConcatOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ArrayConcatOpGenericAdaptor::ArrayConcatOpGenericAdaptor;
  ArrayConcatOpAdaptor(ArrayConcatOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ArrayConcatOp : public ::mlir::Op<ArrayConcatOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::circt::hw::TypeAliasOr<circt::hw::ArrayType>>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::OpInvariants, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ArrayConcatOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ArrayConcatOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_inputs = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("hw.array_concat");
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

  ::mlir::TypedValue<::circt::hw::TypeAliasOr<circt::hw::ArrayType>> getResult() {
    return ::llvm::cast<::mlir::TypedValue<::circt::hw::TypeAliasOr<circt::hw::ArrayType>>>(*getODSResults(0).begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ValueRange inputs);
  static ArrayConcatOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ValueRange inputs);
  static ArrayConcatOp create(::mlir::ImplicitLocOpBuilder &builder, ValueRange inputs);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::ValueRange inputs);
  static ArrayConcatOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::ValueRange inputs);
  static ArrayConcatOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::ValueRange inputs);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ArrayConcatOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ArrayConcatOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ArrayConcatOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ArrayConcatOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::llvm::LogicalResult canonicalize(ArrayConcatOp op, ::mlir::PatternRewriter &rewriter);
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
  ::mlir::OpFoldResult fold(FoldAdaptor adaptor);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
};

} // namespace circt::hw
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::hw::ArrayConcatOp)

namespace circt::hw {


//===----------------------------------------------------------------------===//
// ::circt::hw::ArrayCreateOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ArrayCreateOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  ArrayCreateOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("hw.array_create", odsAttrs.getContext());
  }

  ArrayCreateOpGenericAdaptorBase(ArrayCreateOp op);

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
class ArrayCreateOpGenericAdaptor : public detail::ArrayCreateOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ArrayCreateOpGenericAdaptorBase;
  static constexpr int odsIndex_inputs = 0;
public:
  ArrayCreateOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ArrayCreateOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : ArrayCreateOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ArrayCreateOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ArrayCreateOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ArrayCreateOpGenericAdaptor(RangeT values, const ArrayCreateOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ArrayCreateOp, typename = std::enable_if_t<std::is_same_v<LateInst, ArrayCreateOp>>>
  ArrayCreateOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class ArrayCreateOpAdaptor : public ArrayCreateOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ArrayCreateOpGenericAdaptor::ArrayCreateOpGenericAdaptor;
  ArrayCreateOpAdaptor(ArrayCreateOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ArrayCreateOp : public ::mlir::Op<ArrayCreateOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::circt::hw::TypeAliasOr<circt::hw::ArrayType>>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::OpInvariants, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::OpTrait::SameTypeOperands> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ArrayCreateOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ArrayCreateOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_inputs = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("hw.array_create");
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

  ::mlir::TypedValue<::circt::hw::TypeAliasOr<circt::hw::ArrayType>> getResult() {
    return ::llvm::cast<::mlir::TypedValue<::circt::hw::TypeAliasOr<circt::hw::ArrayType>>>(*getODSResults(0).begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ValueRange input);
  static ArrayCreateOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ValueRange input);
  static ArrayCreateOp create(::mlir::ImplicitLocOpBuilder &builder, ValueRange input);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::ValueRange inputs);
  static ArrayCreateOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::ValueRange inputs);
  static ArrayCreateOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::ValueRange inputs);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ArrayCreateOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ArrayCreateOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ArrayCreateOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ArrayCreateOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &p);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static ::llvm::LogicalResult canonicalize(ArrayCreateOp op, ::mlir::PatternRewriter &rewriter);
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
  ::mlir::OpFoldResult fold(FoldAdaptor adaptor);
  static ::llvm::LogicalResult setPropertiesFromParsedAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
  /// If the all elements of the array are identical, returns that element
  /// value. Otherwise returns a null value.
  Value getUniformElement();
  /// Returns true if all array elements are identical.
  bool isUniform() { return !!getUniformElement(); }
};

} // namespace circt::hw
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::hw::ArrayCreateOp)

namespace circt::hw {


//===----------------------------------------------------------------------===//
// ::circt::hw::ArrayGetOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ArrayGetOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  ArrayGetOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("hw.array_get", odsAttrs.getContext());
  }

  ArrayGetOpGenericAdaptorBase(ArrayGetOp op);

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
class ArrayGetOpGenericAdaptor : public detail::ArrayGetOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ArrayGetOpGenericAdaptorBase;
  static constexpr int odsIndex_input = 0;
  static constexpr int odsIndex_index = 1;
public:
  ArrayGetOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ArrayGetOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : ArrayGetOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ArrayGetOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ArrayGetOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ArrayGetOpGenericAdaptor(RangeT values, const ArrayGetOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ArrayGetOp, typename = std::enable_if_t<std::is_same_v<LateInst, ArrayGetOp>>>
  ArrayGetOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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

  ValueT getIndex() {
    return (*getODSOperands(1).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class ArrayGetOpAdaptor : public ArrayGetOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ArrayGetOpGenericAdaptor::ArrayGetOpGenericAdaptor;
  ArrayGetOpAdaptor(ArrayGetOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ArrayGetOp : public ::mlir::Op<ArrayGetOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::Type>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::NOperands<2>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ArrayGetOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ArrayGetOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_input = 0;
  static constexpr int odsIndex_index = 1;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("hw.array_get");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::circt::hw::TypeAliasOr<circt::hw::ArrayType>> getInput() {
    return ::llvm::cast<::mlir::TypedValue<::circt::hw::TypeAliasOr<circt::hw::ArrayType>>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::circt::hw::TypeVariant<::mlir::IntegerType, ::circt::hw::IntType>> getIndex() {
    return ::llvm::cast<::mlir::TypedValue<::circt::hw::TypeVariant<::mlir::IntegerType, ::circt::hw::IntType>>>(*getODSOperands(1).begin());
  }

  ::mlir::OpOperand &getInputMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getIndexMutable() {
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value input, ::mlir::Value index);
  static ArrayGetOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value input, ::mlir::Value index);
  static ArrayGetOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value input, ::mlir::Value index);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value input, ::mlir::Value index);
  static ArrayGetOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value input, ::mlir::Value index);
  static ArrayGetOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value input, ::mlir::Value index);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value input, ::mlir::Value index);
  static ArrayGetOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value input, ::mlir::Value index);
  static ArrayGetOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value input, ::mlir::Value index);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ArrayGetOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ArrayGetOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ArrayGetOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ArrayGetOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ArrayGetOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ArrayGetOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ArrayGetOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ArrayGetOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::llvm::LogicalResult canonicalize(ArrayGetOp op, ::mlir::PatternRewriter &rewriter);
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
  ::mlir::OpFoldResult fold(FoldAdaptor adaptor);
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::PropertyRef properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
};

} // namespace circt::hw
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::hw::ArrayGetOp)

namespace circt::hw {


//===----------------------------------------------------------------------===//
// ::circt::hw::ArrayInjectOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ArrayInjectOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  ArrayInjectOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("hw.array_inject", odsAttrs.getContext());
  }

  ArrayInjectOpGenericAdaptorBase(ArrayInjectOp op);

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
class ArrayInjectOpGenericAdaptor : public detail::ArrayInjectOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ArrayInjectOpGenericAdaptorBase;
  static constexpr int odsIndex_input = 0;
  static constexpr int odsIndex_index = 1;
  static constexpr int odsIndex_element = 2;
public:
  ArrayInjectOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ArrayInjectOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : ArrayInjectOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ArrayInjectOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ArrayInjectOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ArrayInjectOpGenericAdaptor(RangeT values, const ArrayInjectOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ArrayInjectOp, typename = std::enable_if_t<std::is_same_v<LateInst, ArrayInjectOp>>>
  ArrayInjectOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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

  ValueT getIndex() {
    return (*getODSOperands(1).begin());
  }

  ValueT getElement() {
    return (*getODSOperands(2).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class ArrayInjectOpAdaptor : public ArrayInjectOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ArrayInjectOpGenericAdaptor::ArrayInjectOpGenericAdaptor;
  ArrayInjectOpAdaptor(ArrayInjectOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ArrayInjectOp : public ::mlir::Op<ArrayInjectOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::circt::hw::TypeAliasOr<circt::hw::ArrayType>>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::NOperands<3>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ArrayInjectOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ArrayInjectOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_input = 0;
  static constexpr int odsIndex_index = 1;
  static constexpr int odsIndex_element = 2;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("hw.array_inject");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::circt::hw::TypeAliasOr<circt::hw::ArrayType>> getInput() {
    return ::llvm::cast<::mlir::TypedValue<::circt::hw::TypeAliasOr<circt::hw::ArrayType>>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::circt::hw::TypeVariant<::mlir::IntegerType, ::circt::hw::IntType>> getIndex() {
    return ::llvm::cast<::mlir::TypedValue<::circt::hw::TypeVariant<::mlir::IntegerType, ::circt::hw::IntType>>>(*getODSOperands(1).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getElement() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(2).begin());
  }

  ::mlir::OpOperand &getInputMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getIndexMutable() {
    auto range = getODSOperandIndexAndLength(1);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getElementMutable() {
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

  ::mlir::TypedValue<::circt::hw::TypeAliasOr<circt::hw::ArrayType>> getResult() {
    return ::llvm::cast<::mlir::TypedValue<::circt::hw::TypeAliasOr<circt::hw::ArrayType>>>(*getODSResults(0).begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value input, ::mlir::Value index, ::mlir::Value element);
  static ArrayInjectOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value input, ::mlir::Value index, ::mlir::Value element);
  static ArrayInjectOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value input, ::mlir::Value index, ::mlir::Value element);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value input, ::mlir::Value index, ::mlir::Value element);
  static ArrayInjectOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value input, ::mlir::Value index, ::mlir::Value element);
  static ArrayInjectOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value input, ::mlir::Value index, ::mlir::Value element);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value input, ::mlir::Value index, ::mlir::Value element);
  static ArrayInjectOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value input, ::mlir::Value index, ::mlir::Value element);
  static ArrayInjectOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value input, ::mlir::Value index, ::mlir::Value element);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ArrayInjectOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ArrayInjectOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ArrayInjectOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ArrayInjectOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ArrayInjectOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ArrayInjectOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ArrayInjectOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ArrayInjectOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
  ::mlir::OpFoldResult fold(FoldAdaptor adaptor);
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::PropertyRef properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
};

} // namespace circt::hw
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::hw::ArrayInjectOp)

namespace circt::hw {


//===----------------------------------------------------------------------===//
// ::circt::hw::ArraySliceOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ArraySliceOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  ArraySliceOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("hw.array_slice", odsAttrs.getContext());
  }

  ArraySliceOpGenericAdaptorBase(ArraySliceOp op);

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
class ArraySliceOpGenericAdaptor : public detail::ArraySliceOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ArraySliceOpGenericAdaptorBase;
  static constexpr int odsIndex_input = 0;
  static constexpr int odsIndex_lowIndex = 1;
public:
  ArraySliceOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ArraySliceOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : ArraySliceOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ArraySliceOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ArraySliceOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ArraySliceOpGenericAdaptor(RangeT values, const ArraySliceOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ArraySliceOp, typename = std::enable_if_t<std::is_same_v<LateInst, ArraySliceOp>>>
  ArraySliceOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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

  ValueT getLowIndex() {
    return (*getODSOperands(1).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class ArraySliceOpAdaptor : public ArraySliceOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ArraySliceOpGenericAdaptor::ArraySliceOpGenericAdaptor;
  ArraySliceOpAdaptor(ArraySliceOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ArraySliceOp : public ::mlir::Op<ArraySliceOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::circt::hw::TypeAliasOr<circt::hw::ArrayType>>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::NOperands<2>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ArraySliceOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ArraySliceOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_input = 0;
  static constexpr int odsIndex_lowIndex = 1;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("hw.array_slice");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::circt::hw::TypeAliasOr<circt::hw::ArrayType>> getInput() {
    return ::llvm::cast<::mlir::TypedValue<::circt::hw::TypeAliasOr<circt::hw::ArrayType>>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::circt::hw::TypeVariant<::mlir::IntegerType, ::circt::hw::IntType>> getLowIndex() {
    return ::llvm::cast<::mlir::TypedValue<::circt::hw::TypeVariant<::mlir::IntegerType, ::circt::hw::IntType>>>(*getODSOperands(1).begin());
  }

  ::mlir::OpOperand &getInputMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getLowIndexMutable() {
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

  ::mlir::TypedValue<::circt::hw::TypeAliasOr<circt::hw::ArrayType>> getDst() {
    return ::llvm::cast<::mlir::TypedValue<::circt::hw::TypeAliasOr<circt::hw::ArrayType>>>(*getODSResults(0).begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type dst, ::mlir::Value input, ::mlir::Value lowIndex);
  static ArraySliceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type dst, ::mlir::Value input, ::mlir::Value lowIndex);
  static ArraySliceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type dst, ::mlir::Value input, ::mlir::Value lowIndex);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value input, ::mlir::Value lowIndex);
  static ArraySliceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value input, ::mlir::Value lowIndex);
  static ArraySliceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value input, ::mlir::Value lowIndex);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ArraySliceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ArraySliceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ArraySliceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ArraySliceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static ::llvm::LogicalResult canonicalize(ArraySliceOp op, ::mlir::PatternRewriter &rewriter);
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
  ::mlir::OpFoldResult fold(FoldAdaptor adaptor);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
};

} // namespace circt::hw
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::hw::ArraySliceOp)

namespace circt::hw {


//===----------------------------------------------------------------------===//
// ::circt::hw::BitcastOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class BitcastOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  BitcastOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("hw.bitcast", odsAttrs.getContext());
  }

  BitcastOpGenericAdaptorBase(BitcastOp op);

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
class BitcastOpGenericAdaptor : public detail::BitcastOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::BitcastOpGenericAdaptorBase;
  static constexpr int odsIndex_input = 0;
public:
  BitcastOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  BitcastOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : BitcastOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  BitcastOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : BitcastOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  BitcastOpGenericAdaptor(RangeT values, const BitcastOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = BitcastOp, typename = std::enable_if_t<std::is_same_v<LateInst, BitcastOp>>>
  BitcastOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class BitcastOpAdaptor : public BitcastOpGenericAdaptor<::mlir::ValueRange> {
public:
  using BitcastOpGenericAdaptor::BitcastOpGenericAdaptor;
  BitcastOpAdaptor(BitcastOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class BitcastOp : public ::mlir::Op<BitcastOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::Type>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = BitcastOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = BitcastOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_input = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("hw.bitcast");
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value input);
  static BitcastOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value input);
  static BitcastOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value input);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value input);
  static BitcastOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value input);
  static BitcastOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value input);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static BitcastOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static BitcastOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static BitcastOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static BitcastOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static ::llvm::LogicalResult canonicalize(BitcastOp op, ::mlir::PatternRewriter &rewriter);
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
  ::mlir::OpFoldResult fold(FoldAdaptor adaptor);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
};

} // namespace circt::hw
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::hw::BitcastOp)

namespace circt::hw {


//===----------------------------------------------------------------------===//
// ::circt::hw::ConstantOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ConstantOpGenericAdaptorBase {
public:
  struct Properties {
    using valueTy = ::mlir::IntegerAttr;
    valueTy value;

    auto getValue() const {
      auto &propStorage = this->value;
      return ::llvm::cast<::mlir::IntegerAttr>(propStorage);
    }
    void setValue(const ::mlir::IntegerAttr &propValue) {
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
  ConstantOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("hw.constant", odsAttrs.getContext());
  }

  ConstantOpGenericAdaptorBase(ConstantOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::IntegerAttr getValueAttr() {
    auto attr = ::llvm::cast<::mlir::IntegerAttr>(getProperties().value);
    return attr;
  }

  ::mlir::APInt getValue();
};

} // namespace detail
template <typename RangeT>
class ConstantOpGenericAdaptor : public detail::ConstantOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ConstantOpGenericAdaptorBase;
public:
  ConstantOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ConstantOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : ConstantOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ConstantOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ConstantOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ConstantOpGenericAdaptor(RangeT values, const ConstantOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ConstantOp, typename = std::enable_if_t<std::is_same_v<LateInst, ConstantOp>>>
  ConstantOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class ConstantOpAdaptor : public ConstantOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ConstantOpGenericAdaptor::ConstantOpGenericAdaptor;
  ConstantOpAdaptor(ConstantOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ConstantOp : public ::mlir::Op<ConstantOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::circt::hw::TypeVariant<::mlir::IntegerType, ::circt::hw::IntType>>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::OpTrait::ConstantLike, ::mlir::OpAsmOpInterface::Trait, ::mlir::InferIntRangeInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ConstantOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ConstantOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::OpAsmOpInterface::Trait<ConstantOp>::getAsmBlockArgumentNames;
  using ::mlir::OpAsmOpInterface::Trait<ConstantOp>::getAsmBlockNames;
  using ::mlir::OpAsmOpInterface::Trait<ConstantOp>::getDefaultDialect;
  using ::mlir::InferIntRangeInterface::Trait<ConstantOp>::inferResultRangesFromOptional;
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
    return ::llvm::StringLiteral("hw.constant");
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

  ::mlir::TypedValue<::circt::hw::TypeVariant<::mlir::IntegerType, ::circt::hw::IntType>> getResult() {
    return ::llvm::cast<::mlir::TypedValue<::circt::hw::TypeVariant<::mlir::IntegerType, ::circt::hw::IntType>>>(*getODSResults(0).begin());
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
  ::mlir::IntegerAttr getValueAttr() {
    return ::llvm::cast<::mlir::IntegerAttr>(getProperties().value);
  }

  ::mlir::APInt getValue();
  void setValueAttr(::mlir::IntegerAttr attr) {
    getProperties().value = attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, const APInt &value);
  static ConstantOp create(::mlir::OpBuilder &builder, ::mlir::Location location, const APInt &value);
  static ConstantOp create(::mlir::ImplicitLocOpBuilder &builder, const APInt &value);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Type type, int64_t value);
  static ConstantOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Type type, int64_t value);
  static ConstantOp create(::mlir::ImplicitLocOpBuilder &builder, Type type, int64_t value);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, IntegerAttr value);
  static ConstantOp create(::mlir::OpBuilder &builder, ::mlir::Location location, IntegerAttr value);
  static ConstantOp create(::mlir::ImplicitLocOpBuilder &builder, IntegerAttr value);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::IntegerAttr value);
  static ConstantOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::IntegerAttr value);
  static ConstantOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::IntegerAttr value);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::IntegerAttr value);
  static ConstantOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::IntegerAttr value);
  static ConstantOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::IntegerAttr value);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ConstantOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ConstantOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ConstantOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ConstantOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ConstantOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ConstantOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ConstantOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ConstantOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &p);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  ::mlir::OpFoldResult fold(FoldAdaptor adaptor);
  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
  void inferResultRanges(::llvm::ArrayRef<::mlir::ConstantIntRanges> argRanges, ::mlir::SetIntRangeFn setResultRanges);
  static ::llvm::LogicalResult setPropertiesFromParsedAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
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

} // namespace circt::hw
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::hw::ConstantOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::hw::detail::ConstantOpGenericAdaptorBase::Properties)

namespace circt::hw {


//===----------------------------------------------------------------------===//
// ::circt::hw::EnumCmpOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class EnumCmpOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  EnumCmpOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("hw.enum.cmp", odsAttrs.getContext());
  }

  EnumCmpOpGenericAdaptorBase(EnumCmpOp op);

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
class EnumCmpOpGenericAdaptor : public detail::EnumCmpOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::EnumCmpOpGenericAdaptorBase;
  static constexpr int odsIndex_lhs = 0;
  static constexpr int odsIndex_rhs = 1;
public:
  EnumCmpOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  EnumCmpOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : EnumCmpOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  EnumCmpOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : EnumCmpOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  EnumCmpOpGenericAdaptor(RangeT values, const EnumCmpOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = EnumCmpOp, typename = std::enable_if_t<std::is_same_v<LateInst, EnumCmpOp>>>
  EnumCmpOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getLhs() {
    return (*getODSOperands(0).begin());
  }

  ValueT getRhs() {
    return (*getODSOperands(1).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class EnumCmpOpAdaptor : public EnumCmpOpGenericAdaptor<::mlir::ValueRange> {
public:
  using EnumCmpOpGenericAdaptor::EnumCmpOpGenericAdaptor;
  EnumCmpOpAdaptor(EnumCmpOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class EnumCmpOp : public ::mlir::Op<EnumCmpOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::IntegerType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::NOperands<2>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = EnumCmpOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = EnumCmpOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_lhs = 0;
  static constexpr int odsIndex_rhs = 1;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("hw.enum.cmp");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::circt::hw::TypeAliasOr<circt::hw::EnumType>> getLhs() {
    return ::llvm::cast<::mlir::TypedValue<::circt::hw::TypeAliasOr<circt::hw::EnumType>>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::circt::hw::TypeAliasOr<circt::hw::EnumType>> getRhs() {
    return ::llvm::cast<::mlir::TypedValue<::circt::hw::TypeAliasOr<circt::hw::EnumType>>>(*getODSOperands(1).begin());
  }

  ::mlir::OpOperand &getLhsMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getRhsMutable() {
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value lhs, ::mlir::Value rhs);
  static EnumCmpOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value lhs, ::mlir::Value rhs);
  static EnumCmpOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value lhs, ::mlir::Value rhs);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value lhs, ::mlir::Value rhs);
  static EnumCmpOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value lhs, ::mlir::Value rhs);
  static EnumCmpOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value lhs, ::mlir::Value rhs);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value lhs, ::mlir::Value rhs);
  static EnumCmpOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value lhs, ::mlir::Value rhs);
  static EnumCmpOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value lhs, ::mlir::Value rhs);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static EnumCmpOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static EnumCmpOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static EnumCmpOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static EnumCmpOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static EnumCmpOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static EnumCmpOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static EnumCmpOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static EnumCmpOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::PropertyRef properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
};

} // namespace circt::hw
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::hw::EnumCmpOp)

namespace circt::hw {


//===----------------------------------------------------------------------===//
// ::circt::hw::EnumConstantOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class EnumConstantOpGenericAdaptorBase {
public:
  struct Properties {
    using fieldTy = ::circt::hw::EnumFieldAttr;
    fieldTy field;

    auto getField() const {
      auto &propStorage = this->field;
      return ::llvm::cast<::circt::hw::EnumFieldAttr>(propStorage);
    }
    void setField(const ::circt::hw::EnumFieldAttr &propValue) {
      this->field = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.field == this->field &&
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
  EnumConstantOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("hw.enum.constant", odsAttrs.getContext());
  }

  EnumConstantOpGenericAdaptorBase(EnumConstantOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::circt::hw::EnumFieldAttr getFieldAttr() {
    auto attr = ::llvm::cast<::circt::hw::EnumFieldAttr>(getProperties().field);
    return attr;
  }

  ::circt::hw::EnumFieldAttr getField();
};

} // namespace detail
template <typename RangeT>
class EnumConstantOpGenericAdaptor : public detail::EnumConstantOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::EnumConstantOpGenericAdaptorBase;
public:
  EnumConstantOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  EnumConstantOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : EnumConstantOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  EnumConstantOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : EnumConstantOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  EnumConstantOpGenericAdaptor(RangeT values, const EnumConstantOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = EnumConstantOp, typename = std::enable_if_t<std::is_same_v<LateInst, EnumConstantOp>>>
  EnumConstantOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class EnumConstantOpAdaptor : public EnumConstantOpGenericAdaptor<::mlir::ValueRange> {
public:
  using EnumConstantOpGenericAdaptor::EnumConstantOpGenericAdaptor;
  EnumConstantOpAdaptor(EnumConstantOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class EnumConstantOp : public ::mlir::Op<EnumConstantOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::circt::hw::TypeAliasOr<circt::hw::EnumType>>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::OpTrait::ConstantLike, ::mlir::OpAsmOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = EnumConstantOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = EnumConstantOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::OpAsmOpInterface::Trait<EnumConstantOp>::getAsmBlockArgumentNames;
  using ::mlir::OpAsmOpInterface::Trait<EnumConstantOp>::getAsmBlockNames;
  using ::mlir::OpAsmOpInterface::Trait<EnumConstantOp>::getDefaultDialect;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("field")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getFieldAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getFieldAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("hw.enum.constant");
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

  ::mlir::TypedValue<::circt::hw::TypeAliasOr<circt::hw::EnumType>> getResult() {
    return ::llvm::cast<::mlir::TypedValue<::circt::hw::TypeAliasOr<circt::hw::EnumType>>>(*getODSResults(0).begin());
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
  ::circt::hw::EnumFieldAttr getFieldAttr() {
    return ::llvm::cast<::circt::hw::EnumFieldAttr>(getProperties().field);
  }

  ::circt::hw::EnumFieldAttr getField();
  void setFieldAttr(::circt::hw::EnumFieldAttr attr) {
    getProperties().field = attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, hw::EnumFieldAttr field);
  static EnumConstantOp create(::mlir::OpBuilder &builder, ::mlir::Location location, hw::EnumFieldAttr field);
  static EnumConstantOp create(::mlir::ImplicitLocOpBuilder &builder, hw::EnumFieldAttr field);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::circt::hw::EnumFieldAttr field);
  static EnumConstantOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::circt::hw::EnumFieldAttr field);
  static EnumConstantOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::circt::hw::EnumFieldAttr field);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::circt::hw::EnumFieldAttr field);
  static EnumConstantOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::circt::hw::EnumFieldAttr field);
  static EnumConstantOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::circt::hw::EnumFieldAttr field);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static EnumConstantOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static EnumConstantOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static EnumConstantOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static EnumConstantOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &p);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  ::mlir::OpFoldResult fold(FoldAdaptor adaptor);
  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
  static ::llvm::LogicalResult setPropertiesFromParsedAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
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

} // namespace circt::hw
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::hw::EnumConstantOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::hw::detail::EnumConstantOpGenericAdaptorBase::Properties)

namespace circt::hw {


//===----------------------------------------------------------------------===//
// ::circt::hw::HWGeneratorSchemaOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class HWGeneratorSchemaOpGenericAdaptorBase {
public:
  struct Properties {
    using descriptorTy = ::mlir::StringAttr;
    descriptorTy descriptor;

    auto getDescriptor() const {
      auto &propStorage = this->descriptor;
      return ::llvm::cast<::mlir::StringAttr>(propStorage);
    }
    void setDescriptor(const ::mlir::StringAttr &propValue) {
      this->descriptor = propValue;
    }
    using requiredAttrsTy = ::mlir::ArrayAttr;
    requiredAttrsTy requiredAttrs;

    auto getRequiredAttrs() const {
      auto &propStorage = this->requiredAttrs;
      return ::llvm::cast<::mlir::ArrayAttr>(propStorage);
    }
    void setRequiredAttrs(const ::mlir::ArrayAttr &propValue) {
      this->requiredAttrs = propValue;
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
        rhs.descriptor == this->descriptor &&
        rhs.requiredAttrs == this->requiredAttrs &&
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
  HWGeneratorSchemaOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("hw.generator.schema", odsAttrs.getContext());
  }

  HWGeneratorSchemaOpGenericAdaptorBase(HWGeneratorSchemaOp op);

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
  ::mlir::StringAttr getDescriptorAttr() {
    auto attr = ::llvm::cast<::mlir::StringAttr>(getProperties().descriptor);
    return attr;
  }

  ::llvm::StringRef getDescriptor();
  ::mlir::ArrayAttr getRequiredAttrsAttr() {
    auto attr = ::llvm::cast<::mlir::ArrayAttr>(getProperties().requiredAttrs);
    return attr;
  }

  ::mlir::ArrayAttr getRequiredAttrs();
};

} // namespace detail
template <typename RangeT>
class HWGeneratorSchemaOpGenericAdaptor : public detail::HWGeneratorSchemaOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::HWGeneratorSchemaOpGenericAdaptorBase;
public:
  HWGeneratorSchemaOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  HWGeneratorSchemaOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : HWGeneratorSchemaOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  HWGeneratorSchemaOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : HWGeneratorSchemaOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  HWGeneratorSchemaOpGenericAdaptor(RangeT values, const HWGeneratorSchemaOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = HWGeneratorSchemaOp, typename = std::enable_if_t<std::is_same_v<LateInst, HWGeneratorSchemaOp>>>
  HWGeneratorSchemaOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class HWGeneratorSchemaOpAdaptor : public HWGeneratorSchemaOpGenericAdaptor<::mlir::ValueRange> {
public:
  using HWGeneratorSchemaOpGenericAdaptor::HWGeneratorSchemaOpGenericAdaptor;
  HWGeneratorSchemaOpAdaptor(HWGeneratorSchemaOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class HWGeneratorSchemaOp : public ::mlir::Op<HWGeneratorSchemaOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::HasParent<mlir::ModuleOp>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::SymbolOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = HWGeneratorSchemaOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = HWGeneratorSchemaOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("descriptor"), ::llvm::StringRef("requiredAttrs"), ::llvm::StringRef("sym_name")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getDescriptorAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getDescriptorAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getRequiredAttrsAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getRequiredAttrsAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getSymNameAttrName() {
    return getAttributeNameForIndex(2);
  }

  static ::mlir::StringAttr getSymNameAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 2);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("hw.generator.schema");
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
  ::mlir::StringAttr getDescriptorAttr() {
    return ::llvm::cast<::mlir::StringAttr>(getProperties().descriptor);
  }

  ::llvm::StringRef getDescriptor();
  ::mlir::ArrayAttr getRequiredAttrsAttr() {
    return ::llvm::cast<::mlir::ArrayAttr>(getProperties().requiredAttrs);
  }

  ::mlir::ArrayAttr getRequiredAttrs();
  void setSymNameAttr(::mlir::StringAttr attr) {
    getProperties().sym_name = attr;
  }

  void setSymName(::llvm::StringRef attrValue);
  void setDescriptorAttr(::mlir::StringAttr attr) {
    getProperties().descriptor = attr;
  }

  void setDescriptor(::llvm::StringRef attrValue);
  void setRequiredAttrsAttr(::mlir::ArrayAttr attr) {
    getProperties().requiredAttrs = attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::StringAttr sym_name, ::mlir::StringAttr descriptor, ::mlir::ArrayAttr requiredAttrs);
  static HWGeneratorSchemaOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::StringAttr sym_name, ::mlir::StringAttr descriptor, ::mlir::ArrayAttr requiredAttrs);
  static HWGeneratorSchemaOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::StringAttr sym_name, ::mlir::StringAttr descriptor, ::mlir::ArrayAttr requiredAttrs);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name, ::mlir::StringAttr descriptor, ::mlir::ArrayAttr requiredAttrs);
  static HWGeneratorSchemaOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name, ::mlir::StringAttr descriptor, ::mlir::ArrayAttr requiredAttrs);
  static HWGeneratorSchemaOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name, ::mlir::StringAttr descriptor, ::mlir::ArrayAttr requiredAttrs);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::llvm::StringRef sym_name, ::llvm::StringRef descriptor, ::mlir::ArrayAttr requiredAttrs);
  static HWGeneratorSchemaOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::llvm::StringRef sym_name, ::llvm::StringRef descriptor, ::mlir::ArrayAttr requiredAttrs);
  static HWGeneratorSchemaOp create(::mlir::ImplicitLocOpBuilder &builder, ::llvm::StringRef sym_name, ::llvm::StringRef descriptor, ::mlir::ArrayAttr requiredAttrs);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name, ::llvm::StringRef descriptor, ::mlir::ArrayAttr requiredAttrs);
  static HWGeneratorSchemaOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name, ::llvm::StringRef descriptor, ::mlir::ArrayAttr requiredAttrs);
  static HWGeneratorSchemaOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name, ::llvm::StringRef descriptor, ::mlir::ArrayAttr requiredAttrs);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static HWGeneratorSchemaOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static HWGeneratorSchemaOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static HWGeneratorSchemaOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static HWGeneratorSchemaOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
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

} // namespace circt::hw
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::hw::HWGeneratorSchemaOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::hw::detail::HWGeneratorSchemaOpGenericAdaptorBase::Properties)

namespace circt::hw {


//===----------------------------------------------------------------------===//
// ::circt::hw::HWModuleExternOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class HWModuleExternOpGenericAdaptorBase {
public:
  struct Properties {
    using module_typeTy = ::mlir::TypeAttr;
    module_typeTy module_type;

    auto getModuleType() const {
      auto &propStorage = this->module_type;
      return ::llvm::cast<::mlir::TypeAttr>(propStorage);
    }
    void setModuleType(const ::mlir::TypeAttr &propValue) {
      this->module_type = propValue;
    }
    using parametersTy = ::mlir::ArrayAttr;
    parametersTy parameters;

    auto getParameters() const {
      auto &propStorage = this->parameters;
      return ::llvm::cast<::mlir::ArrayAttr>(propStorage);
    }
    void setParameters(const ::mlir::ArrayAttr &propValue) {
      this->parameters = propValue;
    }
    using per_port_attrsTy = ::mlir::ArrayAttr;
    per_port_attrsTy per_port_attrs;

    auto getPerPortAttrs() const {
      auto &propStorage = this->per_port_attrs;
      return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(propStorage);
    }
    void setPerPortAttrs(const ::mlir::ArrayAttr &propValue) {
      this->per_port_attrs = propValue;
    }
    using port_locsTy = ::mlir::ArrayAttr;
    port_locsTy port_locs;

    auto getPortLocs() const {
      auto &propStorage = this->port_locs;
      return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(propStorage);
    }
    void setPortLocs(const ::mlir::ArrayAttr &propValue) {
      this->port_locs = propValue;
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
    using verilogNameTy = ::mlir::StringAttr;
    verilogNameTy verilogName;

    auto getVerilogName() const {
      auto &propStorage = this->verilogName;
      return ::llvm::dyn_cast_or_null<::mlir::StringAttr>(propStorage);
    }
    void setVerilogName(const ::mlir::StringAttr &propValue) {
      this->verilogName = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.module_type == this->module_type &&
        rhs.parameters == this->parameters &&
        rhs.per_port_attrs == this->per_port_attrs &&
        rhs.port_locs == this->port_locs &&
        rhs.sym_name == this->sym_name &&
        rhs.verilogName == this->verilogName &&
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
  HWModuleExternOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("hw.module.extern", odsAttrs.getContext());
  }

  HWModuleExternOpGenericAdaptorBase(HWModuleExternOp op);

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
  ::mlir::TypeAttr getModuleTypeAttr() {
    auto attr = ::llvm::cast<::mlir::TypeAttr>(getProperties().module_type);
    return attr;
  }

  ::circt::hw::ModuleType getModuleType();
  ::mlir::ArrayAttr getPerPortAttrsAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().per_port_attrs);
    return attr;
  }

  ::std::optional< ::mlir::ArrayAttr > getPerPortAttrs();
  ::mlir::ArrayAttr getPortLocsAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().port_locs);
    return attr;
  }

  ::std::optional< ::mlir::ArrayAttr > getPortLocs();
  ::mlir::ArrayAttr getParametersAttr() {
    auto attr = ::llvm::cast<::mlir::ArrayAttr>(getProperties().parameters);
    return attr;
  }

  ::mlir::ArrayAttr getParameters();
  ::mlir::StringAttr getVerilogNameAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::StringAttr>(getProperties().verilogName);
    return attr;
  }

  ::std::optional< ::llvm::StringRef > getVerilogName();
  ::mlir::Region &getBody() {
    return *odsRegions[0];
  }

  ::mlir::RegionRange getRegions() {
    return odsRegions;
  }

};

} // namespace detail
template <typename RangeT>
class HWModuleExternOpGenericAdaptor : public detail::HWModuleExternOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::HWModuleExternOpGenericAdaptorBase;
public:
  HWModuleExternOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  HWModuleExternOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : HWModuleExternOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  HWModuleExternOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : HWModuleExternOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  HWModuleExternOpGenericAdaptor(RangeT values, const HWModuleExternOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = HWModuleExternOp, typename = std::enable_if_t<std::is_same_v<LateInst, HWModuleExternOp>>>
  HWModuleExternOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class HWModuleExternOpAdaptor : public HWModuleExternOpGenericAdaptor<::mlir::ValueRange> {
public:
  using HWModuleExternOpGenericAdaptor::HWModuleExternOpGenericAdaptor;
  HWModuleExternOpAdaptor(HWModuleExternOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class HWModuleExternOp : public ::mlir::Op<HWModuleExternOp, ::mlir::OpTrait::OneRegion, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::HasParent<mlir::ModuleOp>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, circt::hw::PortList::Trait, ::mlir::SymbolOpInterface::Trait, ::circt::igraph::ModuleOpInterface::Trait, circt::hw::HWModuleLike::Trait, circt::hw::HWMutableModuleLike::Trait, ::mlir::OpTrait::InnerSymbolTable, ::mlir::OpAsmOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = HWModuleExternOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = HWModuleExternOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  using circt::hw::HWMutableModuleLike::Trait<HWModuleExternOp>::getPortLookupInfo;
  using circt::hw::HWMutableModuleLike::Trait<HWModuleExternOp>::insertPorts;
  using circt::hw::HWMutableModuleLike::Trait<HWModuleExternOp>::erasePorts;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("module_type"), ::llvm::StringRef("parameters"), ::llvm::StringRef("per_port_attrs"), ::llvm::StringRef("port_locs"), ::llvm::StringRef("sym_name"), ::llvm::StringRef("verilogName")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getModuleTypeAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getModuleTypeAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getParametersAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getParametersAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getPerPortAttrsAttrName() {
    return getAttributeNameForIndex(2);
  }

  static ::mlir::StringAttr getPerPortAttrsAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 2);
  }

  ::mlir::StringAttr getPortLocsAttrName() {
    return getAttributeNameForIndex(3);
  }

  static ::mlir::StringAttr getPortLocsAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 3);
  }

  ::mlir::StringAttr getSymNameAttrName() {
    return getAttributeNameForIndex(4);
  }

  static ::mlir::StringAttr getSymNameAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 4);
  }

  ::mlir::StringAttr getVerilogNameAttrName() {
    return getAttributeNameForIndex(5);
  }

  static ::mlir::StringAttr getVerilogNameAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 5);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("hw.module.extern");
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
  ::mlir::TypeAttr getModuleTypeAttr() {
    return ::llvm::cast<::mlir::TypeAttr>(getProperties().module_type);
  }

  ::circt::hw::ModuleType getModuleType();
  ::mlir::ArrayAttr getPerPortAttrsAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().per_port_attrs);
  }

  ::std::optional< ::mlir::ArrayAttr > getPerPortAttrs();
  ::mlir::ArrayAttr getPortLocsAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().port_locs);
  }

  ::std::optional< ::mlir::ArrayAttr > getPortLocs();
  ::mlir::ArrayAttr getParametersAttr() {
    return ::llvm::cast<::mlir::ArrayAttr>(getProperties().parameters);
  }

  ::mlir::ArrayAttr getParameters();
  ::mlir::StringAttr getVerilogNameAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::StringAttr>(getProperties().verilogName);
  }

  ::std::optional< ::llvm::StringRef > getVerilogName();
  void setSymNameAttr(::mlir::StringAttr attr) {
    getProperties().sym_name = attr;
  }

  void setSymName(::llvm::StringRef attrValue);
  void setModuleTypeAttr(::mlir::TypeAttr attr) {
    getProperties().module_type = attr;
  }

  void setModuleType(::circt::hw::ModuleType attrValue);
  void setPerPortAttrsAttr(::mlir::ArrayAttr attr) {
    getProperties().per_port_attrs = attr;
  }

  void setPortLocsAttr(::mlir::ArrayAttr attr) {
    getProperties().port_locs = attr;
  }

  void setParametersAttr(::mlir::ArrayAttr attr) {
    getProperties().parameters = attr;
  }

  void setVerilogNameAttr(::mlir::StringAttr attr) {
    getProperties().verilogName = attr;
  }

  void setVerilogName(::std::optional<::llvm::StringRef> attrValue);
  ::mlir::Attribute removePerPortAttrsAttr() {
      auto attr = getProperties().per_port_attrs;
      getProperties().per_port_attrs = {};
      return attr;
  }

  ::mlir::Attribute removePortLocsAttr() {
      auto attr = getProperties().port_locs;
      getProperties().port_locs = {};
      return attr;
  }

  ::mlir::Attribute removeVerilogNameAttr() {
      auto attr = getProperties().verilogName;
      getProperties().verilogName = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, StringAttr name, ArrayRef<PortInfo> ports, StringRef verilogName = StringRef(), ArrayAttr parameters = {}, ArrayRef<NamedAttribute> attributes = {});
  static HWModuleExternOp create(::mlir::OpBuilder &builder, ::mlir::Location location, StringAttr name, ArrayRef<PortInfo> ports, StringRef verilogName = StringRef(), ArrayAttr parameters = {}, ArrayRef<NamedAttribute> attributes = {});
  static HWModuleExternOp create(::mlir::ImplicitLocOpBuilder &builder, StringAttr name, ArrayRef<PortInfo> ports, StringRef verilogName = StringRef(), ArrayAttr parameters = {}, ArrayRef<NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, StringAttr name, const ModulePortInfo &ports, StringRef verilogName = StringRef(), ArrayAttr parameters = {}, ArrayRef<NamedAttribute> attributes = {});
  static HWModuleExternOp create(::mlir::OpBuilder &builder, ::mlir::Location location, StringAttr name, const ModulePortInfo &ports, StringRef verilogName = StringRef(), ArrayAttr parameters = {}, ArrayRef<NamedAttribute> attributes = {});
  static HWModuleExternOp create(::mlir::ImplicitLocOpBuilder &builder, StringAttr name, const ModulePortInfo &ports, StringRef verilogName = StringRef(), ArrayAttr parameters = {}, ArrayRef<NamedAttribute> attributes = {});
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &p);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  SmallVector<::circt::hw::PortInfo> getPortList();
  ::circt::hw::PortInfo getPort(size_t idx);
  size_t getPortIdForInputId(size_t idx);
  size_t getPortIdForOutputId(size_t idx);
  size_t getNumPorts();
  size_t getNumInputPorts();
  size_t getNumOutputPorts();
  ::circt::hw::ModuleType getHWModuleType();
  ArrayRef<Attribute> getAllPortAttrs();
  void setAllPortAttrs(ArrayRef<Attribute> attrs);
  void removeAllPortAttrs();
  SmallVector<Location> getAllPortLocs();
  void setAllPortLocsAttrs(ArrayRef<Attribute> locs);
  void setHWModuleType(::circt::hw::ModuleType type);
  void setAllPortNames(ArrayRef<Attribute> names);
  void appendOutputs(ArrayRef<std::pair<StringAttr, Value>> outputs);
  static ::llvm::LogicalResult setPropertiesFromParsedAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
private:
  ::mlir::StringAttr getAttributeNameForIndex(unsigned index) {
    return getAttributeNameForIndex((*this)->getName(), index);
  }

  static ::mlir::StringAttr getAttributeNameForIndex(::mlir::OperationName name, unsigned index) {
    assert(index < 6 && "invalid attribute index");
    assert(name.getStringRef() == getOperationName() && "invalid operation name");
    assert(name.isRegistered() && "Operation isn't registered, missing a "
          "dependent dialect loading?");
    return name.getAttributeNames()[index];
  }

public:
  /// Return the name to use for the Verilog module that we're referencing
  /// here.  This is typically the symbol, but can be overridden with the
  /// verilogName attribute.
  StringRef getVerilogModuleName() {
    return getVerilogModuleNameAttr().getValue();
  }

  /// Return the name to use for the Verilog module that we're referencing
  /// here.  This is typically the symbol, but can be overridden with the
  /// verilogName attribute.
  StringAttr getVerilogModuleNameAttr();

  // Get the module's symbolic name as StringAttr.
  StringAttr getNameAttr() {
    return (*this)->getAttrOfType<StringAttr>(
      ::mlir::SymbolTable::getSymbolAttrName());
  }

  // Get the module's symbolic name.
  StringRef getName() {
    return getNameAttr().getValue();
  }

  void getAsmBlockArgumentNames(mlir::Region &region,
                                mlir::OpAsmSetValueNameFn setNameFn);


  /// Insert and remove input and output ports of this module. Does not modify
  /// the block arguments of the module body. The insertion and removal
  /// indices must be in ascending order. The indices refer to the port
  /// positions before any insertion or removal occurs. Ports inserted at the
  /// same index will appear in the module in the same order as they were
  /// listed in the insertion arrays.
  void modifyPorts(
    ArrayRef<std::pair<unsigned, PortInfo>> insertInputs,
    ArrayRef<std::pair<unsigned, PortInfo>> insertOutputs,
    ArrayRef<unsigned> eraseInputs,
    ArrayRef<unsigned> eraseOutputs
  );

  void setPortSymbolAttr(size_t portIndex, ::circt::hw::InnerSymAttr sym);

  StringAttr getArgName(size_t index) {
    return getHWModuleType().getInputNameAttr(index);
  }

};

} // namespace circt::hw
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::hw::HWModuleExternOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::hw::detail::HWModuleExternOpGenericAdaptorBase::Properties)

namespace circt::hw {


//===----------------------------------------------------------------------===//
// ::circt::hw::HWModuleGeneratedOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class HWModuleGeneratedOpGenericAdaptorBase {
public:
  struct Properties {
    using generatorKindTy = ::mlir::FlatSymbolRefAttr;
    generatorKindTy generatorKind;

    auto getGeneratorKind() const {
      auto &propStorage = this->generatorKind;
      return ::llvm::cast<::mlir::FlatSymbolRefAttr>(propStorage);
    }
    void setGeneratorKind(const ::mlir::FlatSymbolRefAttr &propValue) {
      this->generatorKind = propValue;
    }
    using module_typeTy = ::mlir::TypeAttr;
    module_typeTy module_type;

    auto getModuleType() const {
      auto &propStorage = this->module_type;
      return ::llvm::cast<::mlir::TypeAttr>(propStorage);
    }
    void setModuleType(const ::mlir::TypeAttr &propValue) {
      this->module_type = propValue;
    }
    using parametersTy = ::mlir::ArrayAttr;
    parametersTy parameters;

    auto getParameters() const {
      auto &propStorage = this->parameters;
      return ::llvm::cast<::mlir::ArrayAttr>(propStorage);
    }
    void setParameters(const ::mlir::ArrayAttr &propValue) {
      this->parameters = propValue;
    }
    using per_port_attrsTy = ::mlir::ArrayAttr;
    per_port_attrsTy per_port_attrs;

    auto getPerPortAttrs() const {
      auto &propStorage = this->per_port_attrs;
      return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(propStorage);
    }
    void setPerPortAttrs(const ::mlir::ArrayAttr &propValue) {
      this->per_port_attrs = propValue;
    }
    using port_locsTy = ::mlir::ArrayAttr;
    port_locsTy port_locs;

    auto getPortLocs() const {
      auto &propStorage = this->port_locs;
      return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(propStorage);
    }
    void setPortLocs(const ::mlir::ArrayAttr &propValue) {
      this->port_locs = propValue;
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
    using verilogNameTy = ::mlir::StringAttr;
    verilogNameTy verilogName;

    auto getVerilogName() const {
      auto &propStorage = this->verilogName;
      return ::llvm::dyn_cast_or_null<::mlir::StringAttr>(propStorage);
    }
    void setVerilogName(const ::mlir::StringAttr &propValue) {
      this->verilogName = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.generatorKind == this->generatorKind &&
        rhs.module_type == this->module_type &&
        rhs.parameters == this->parameters &&
        rhs.per_port_attrs == this->per_port_attrs &&
        rhs.port_locs == this->port_locs &&
        rhs.sym_name == this->sym_name &&
        rhs.verilogName == this->verilogName &&
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
  HWModuleGeneratedOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("hw.module.generated", odsAttrs.getContext());
  }

  HWModuleGeneratedOpGenericAdaptorBase(HWModuleGeneratedOp op);

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
  ::mlir::FlatSymbolRefAttr getGeneratorKindAttr() {
    auto attr = ::llvm::cast<::mlir::FlatSymbolRefAttr>(getProperties().generatorKind);
    return attr;
  }

  ::llvm::StringRef getGeneratorKind();
  ::mlir::TypeAttr getModuleTypeAttr() {
    auto attr = ::llvm::cast<::mlir::TypeAttr>(getProperties().module_type);
    return attr;
  }

  ::circt::hw::ModuleType getModuleType();
  ::mlir::ArrayAttr getPerPortAttrsAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().per_port_attrs);
    return attr;
  }

  ::std::optional< ::mlir::ArrayAttr > getPerPortAttrs();
  ::mlir::ArrayAttr getPortLocsAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().port_locs);
    return attr;
  }

  ::std::optional< ::mlir::ArrayAttr > getPortLocs();
  ::mlir::ArrayAttr getParametersAttr() {
    auto attr = ::llvm::cast<::mlir::ArrayAttr>(getProperties().parameters);
    return attr;
  }

  ::mlir::ArrayAttr getParameters();
  ::mlir::StringAttr getVerilogNameAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::StringAttr>(getProperties().verilogName);
    return attr;
  }

  ::std::optional< ::llvm::StringRef > getVerilogName();
  ::mlir::Region &getBody() {
    return *odsRegions[0];
  }

  ::mlir::RegionRange getRegions() {
    return odsRegions;
  }

};

} // namespace detail
template <typename RangeT>
class HWModuleGeneratedOpGenericAdaptor : public detail::HWModuleGeneratedOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::HWModuleGeneratedOpGenericAdaptorBase;
public:
  HWModuleGeneratedOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  HWModuleGeneratedOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : HWModuleGeneratedOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  HWModuleGeneratedOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : HWModuleGeneratedOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  HWModuleGeneratedOpGenericAdaptor(RangeT values, const HWModuleGeneratedOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = HWModuleGeneratedOp, typename = std::enable_if_t<std::is_same_v<LateInst, HWModuleGeneratedOp>>>
  HWModuleGeneratedOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class HWModuleGeneratedOpAdaptor : public HWModuleGeneratedOpGenericAdaptor<::mlir::ValueRange> {
public:
  using HWModuleGeneratedOpGenericAdaptor::HWModuleGeneratedOpGenericAdaptor;
  HWModuleGeneratedOpAdaptor(HWModuleGeneratedOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class HWModuleGeneratedOp : public ::mlir::Op<HWModuleGeneratedOp, ::mlir::OpTrait::OneRegion, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::HasParent<mlir::ModuleOp>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::SymbolUserOpInterface::Trait, ::mlir::OpTrait::IsIsolatedFromAbove, circt::hw::PortList::Trait, ::mlir::SymbolOpInterface::Trait, ::circt::igraph::ModuleOpInterface::Trait, circt::hw::HWModuleLike::Trait, circt::hw::HWMutableModuleLike::Trait, ::mlir::OpTrait::InnerSymbolTable, ::mlir::OpAsmOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = HWModuleGeneratedOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = HWModuleGeneratedOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  using circt::hw::HWMutableModuleLike::Trait<HWModuleGeneratedOp>::getPortLookupInfo;
  using circt::hw::HWMutableModuleLike::Trait<HWModuleGeneratedOp>::insertPorts;
  using circt::hw::HWMutableModuleLike::Trait<HWModuleGeneratedOp>::erasePorts;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("generatorKind"), ::llvm::StringRef("module_type"), ::llvm::StringRef("parameters"), ::llvm::StringRef("per_port_attrs"), ::llvm::StringRef("port_locs"), ::llvm::StringRef("sym_name"), ::llvm::StringRef("verilogName")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getGeneratorKindAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getGeneratorKindAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getModuleTypeAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getModuleTypeAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getParametersAttrName() {
    return getAttributeNameForIndex(2);
  }

  static ::mlir::StringAttr getParametersAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 2);
  }

  ::mlir::StringAttr getPerPortAttrsAttrName() {
    return getAttributeNameForIndex(3);
  }

  static ::mlir::StringAttr getPerPortAttrsAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 3);
  }

  ::mlir::StringAttr getPortLocsAttrName() {
    return getAttributeNameForIndex(4);
  }

  static ::mlir::StringAttr getPortLocsAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 4);
  }

  ::mlir::StringAttr getSymNameAttrName() {
    return getAttributeNameForIndex(5);
  }

  static ::mlir::StringAttr getSymNameAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 5);
  }

  ::mlir::StringAttr getVerilogNameAttrName() {
    return getAttributeNameForIndex(6);
  }

  static ::mlir::StringAttr getVerilogNameAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 6);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("hw.module.generated");
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
  ::mlir::FlatSymbolRefAttr getGeneratorKindAttr() {
    return ::llvm::cast<::mlir::FlatSymbolRefAttr>(getProperties().generatorKind);
  }

  ::llvm::StringRef getGeneratorKind();
  ::mlir::TypeAttr getModuleTypeAttr() {
    return ::llvm::cast<::mlir::TypeAttr>(getProperties().module_type);
  }

  ::circt::hw::ModuleType getModuleType();
  ::mlir::ArrayAttr getPerPortAttrsAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().per_port_attrs);
  }

  ::std::optional< ::mlir::ArrayAttr > getPerPortAttrs();
  ::mlir::ArrayAttr getPortLocsAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().port_locs);
  }

  ::std::optional< ::mlir::ArrayAttr > getPortLocs();
  ::mlir::ArrayAttr getParametersAttr() {
    return ::llvm::cast<::mlir::ArrayAttr>(getProperties().parameters);
  }

  ::mlir::ArrayAttr getParameters();
  ::mlir::StringAttr getVerilogNameAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::StringAttr>(getProperties().verilogName);
  }

  ::std::optional< ::llvm::StringRef > getVerilogName();
  void setSymNameAttr(::mlir::StringAttr attr) {
    getProperties().sym_name = attr;
  }

  void setSymName(::llvm::StringRef attrValue);
  void setGeneratorKindAttr(::mlir::FlatSymbolRefAttr attr) {
    getProperties().generatorKind = attr;
  }

  void setGeneratorKind(::llvm::StringRef attrValue);
  void setModuleTypeAttr(::mlir::TypeAttr attr) {
    getProperties().module_type = attr;
  }

  void setModuleType(::circt::hw::ModuleType attrValue);
  void setPerPortAttrsAttr(::mlir::ArrayAttr attr) {
    getProperties().per_port_attrs = attr;
  }

  void setPortLocsAttr(::mlir::ArrayAttr attr) {
    getProperties().port_locs = attr;
  }

  void setParametersAttr(::mlir::ArrayAttr attr) {
    getProperties().parameters = attr;
  }

  void setVerilogNameAttr(::mlir::StringAttr attr) {
    getProperties().verilogName = attr;
  }

  void setVerilogName(::std::optional<::llvm::StringRef> attrValue);
  ::mlir::Attribute removePerPortAttrsAttr() {
      auto attr = getProperties().per_port_attrs;
      getProperties().per_port_attrs = {};
      return attr;
  }

  ::mlir::Attribute removePortLocsAttr() {
      auto attr = getProperties().port_locs;
      getProperties().port_locs = {};
      return attr;
  }

  ::mlir::Attribute removeVerilogNameAttr() {
      auto attr = getProperties().verilogName;
      getProperties().verilogName = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, FlatSymbolRefAttr genKind, StringAttr name, ArrayRef<PortInfo> ports, StringRef verilogName = StringRef(), ArrayAttr parameters = {}, ArrayRef<NamedAttribute> attributes = {});
  static HWModuleGeneratedOp create(::mlir::OpBuilder &builder, ::mlir::Location location, FlatSymbolRefAttr genKind, StringAttr name, ArrayRef<PortInfo> ports, StringRef verilogName = StringRef(), ArrayAttr parameters = {}, ArrayRef<NamedAttribute> attributes = {});
  static HWModuleGeneratedOp create(::mlir::ImplicitLocOpBuilder &builder, FlatSymbolRefAttr genKind, StringAttr name, ArrayRef<PortInfo> ports, StringRef verilogName = StringRef(), ArrayAttr parameters = {}, ArrayRef<NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, FlatSymbolRefAttr genKind, StringAttr name, const ModulePortInfo &ports, StringRef verilogName = StringRef(), ArrayAttr parameters = {}, ArrayRef<NamedAttribute> attributes = {});
  static HWModuleGeneratedOp create(::mlir::OpBuilder &builder, ::mlir::Location location, FlatSymbolRefAttr genKind, StringAttr name, const ModulePortInfo &ports, StringRef verilogName = StringRef(), ArrayAttr parameters = {}, ArrayRef<NamedAttribute> attributes = {});
  static HWModuleGeneratedOp create(::mlir::ImplicitLocOpBuilder &builder, FlatSymbolRefAttr genKind, StringAttr name, const ModulePortInfo &ports, StringRef verilogName = StringRef(), ArrayAttr parameters = {}, ArrayRef<NamedAttribute> attributes = {});
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &p);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  ::llvm::LogicalResult verifySymbolUses(::mlir::SymbolTableCollection &symbolTable);
  SmallVector<::circt::hw::PortInfo> getPortList();
  ::circt::hw::PortInfo getPort(size_t idx);
  size_t getPortIdForInputId(size_t idx);
  size_t getPortIdForOutputId(size_t idx);
  size_t getNumPorts();
  size_t getNumInputPorts();
  size_t getNumOutputPorts();
  ::circt::hw::ModuleType getHWModuleType();
  ArrayRef<Attribute> getAllPortAttrs();
  void setAllPortAttrs(ArrayRef<Attribute> attrs);
  void removeAllPortAttrs();
  SmallVector<Location> getAllPortLocs();
  void setAllPortLocsAttrs(ArrayRef<Attribute> locs);
  void setHWModuleType(::circt::hw::ModuleType type);
  void setAllPortNames(ArrayRef<Attribute> names);
  void appendOutputs(ArrayRef<std::pair<StringAttr, Value>> outputs);
  static ::llvm::LogicalResult setPropertiesFromParsedAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
private:
  ::mlir::StringAttr getAttributeNameForIndex(unsigned index) {
    return getAttributeNameForIndex((*this)->getName(), index);
  }

  static ::mlir::StringAttr getAttributeNameForIndex(::mlir::OperationName name, unsigned index) {
    assert(index < 7 && "invalid attribute index");
    assert(name.getStringRef() == getOperationName() && "invalid operation name");
    assert(name.isRegistered() && "Operation isn't registered, missing a "
          "dependent dialect loading?");
    return name.getAttributeNames()[index];
  }

public:
  /// Return the name to use for the Verilog module that we're referencing
  /// here.  This is typically the symbol, but can be overridden with the
  /// verilogName attribute.
  StringRef getVerilogModuleName() {
    return getVerilogModuleNameAttr().getValue();
  }

  /// Return the name to use for the Verilog module that we're referencing
  /// here.  This is typically the symbol, but can be overridden with the
  /// verilogName attribute.
  StringAttr getVerilogModuleNameAttr();

  /// Lookup the generator kind for the symbol.  This returns null on
  /// invalid IR.
  Operation *getGeneratorKindOp();

  void getAsmBlockArgumentNames(mlir::Region &region,
                                mlir::OpAsmSetValueNameFn setNameFn);


  /// Insert and remove input and output ports of this module. Does not modify
  /// the block arguments of the module body. The insertion and removal
  /// indices must be in ascending order. The indices refer to the port
  /// positions before any insertion or removal occurs. Ports inserted at the
  /// same index will appear in the module in the same order as they were
  /// listed in the insertion arrays.
  void modifyPorts(
    ArrayRef<std::pair<unsigned, PortInfo>> insertInputs,
    ArrayRef<std::pair<unsigned, PortInfo>> insertOutputs,
    ArrayRef<unsigned> eraseInputs,
    ArrayRef<unsigned> eraseOutputs
  );

  void setPortSymbolAttr(size_t portIndex, ::circt::hw::InnerSymAttr sym);

  StringAttr getArgName(size_t index) {
    return getHWModuleType().getInputNameAttr(index);
  }

};

} // namespace circt::hw
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::hw::HWModuleGeneratedOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::hw::detail::HWModuleGeneratedOpGenericAdaptorBase::Properties)

namespace circt::hw {


//===----------------------------------------------------------------------===//
// ::circt::hw::HWModuleOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class HWModuleOpGenericAdaptorBase {
public:
  struct Properties {
    using commentTy = ::mlir::StringAttr;
    commentTy comment;

    auto getComment() const {
      auto &propStorage = this->comment;
      return ::llvm::dyn_cast_or_null<::mlir::StringAttr>(propStorage);
    }
    void setComment(const ::mlir::StringAttr &propValue) {
      this->comment = propValue;
    }
    using module_typeTy = ::mlir::TypeAttr;
    module_typeTy module_type;

    auto getModuleType() const {
      auto &propStorage = this->module_type;
      return ::llvm::cast<::mlir::TypeAttr>(propStorage);
    }
    void setModuleType(const ::mlir::TypeAttr &propValue) {
      this->module_type = propValue;
    }
    using parametersTy = ::mlir::ArrayAttr;
    parametersTy parameters;

    auto getParameters() const {
      auto &propStorage = this->parameters;
      return ::llvm::cast<::mlir::ArrayAttr>(propStorage);
    }
    void setParameters(const ::mlir::ArrayAttr &propValue) {
      this->parameters = propValue;
    }
    using per_port_attrsTy = ::mlir::ArrayAttr;
    per_port_attrsTy per_port_attrs;

    auto getPerPortAttrs() const {
      auto &propStorage = this->per_port_attrs;
      return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(propStorage);
    }
    void setPerPortAttrs(const ::mlir::ArrayAttr &propValue) {
      this->per_port_attrs = propValue;
    }
    using result_locsTy = ::mlir::ArrayAttr;
    result_locsTy result_locs;

    auto getResultLocs() const {
      auto &propStorage = this->result_locs;
      return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(propStorage);
    }
    void setResultLocs(const ::mlir::ArrayAttr &propValue) {
      this->result_locs = propValue;
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
        rhs.comment == this->comment &&
        rhs.module_type == this->module_type &&
        rhs.parameters == this->parameters &&
        rhs.per_port_attrs == this->per_port_attrs &&
        rhs.result_locs == this->result_locs &&
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
  HWModuleOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("hw.module", odsAttrs.getContext());
  }

  HWModuleOpGenericAdaptorBase(HWModuleOp op);

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
  ::mlir::TypeAttr getModuleTypeAttr() {
    auto attr = ::llvm::cast<::mlir::TypeAttr>(getProperties().module_type);
    return attr;
  }

  ::circt::hw::ModuleType getModuleType();
  ::mlir::ArrayAttr getPerPortAttrsAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().per_port_attrs);
    return attr;
  }

  ::std::optional< ::mlir::ArrayAttr > getPerPortAttrs();
  ::mlir::ArrayAttr getResultLocsAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().result_locs);
    return attr;
  }

  ::std::optional< ::mlir::ArrayAttr > getResultLocs();
  ::mlir::ArrayAttr getParametersAttr() {
    auto attr = ::llvm::cast<::mlir::ArrayAttr>(getProperties().parameters);
    return attr;
  }

  ::mlir::ArrayAttr getParameters();
  ::mlir::StringAttr getCommentAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::StringAttr>(getProperties().comment);
    return attr;
  }

  ::std::optional< ::llvm::StringRef > getComment();
  ::mlir::Region &getBody() {
    return *odsRegions[0];
  }

  ::mlir::RegionRange getRegions() {
    return odsRegions;
  }

};

} // namespace detail
template <typename RangeT>
class HWModuleOpGenericAdaptor : public detail::HWModuleOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::HWModuleOpGenericAdaptorBase;
public:
  HWModuleOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  HWModuleOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : HWModuleOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  HWModuleOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : HWModuleOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  HWModuleOpGenericAdaptor(RangeT values, const HWModuleOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = HWModuleOp, typename = std::enable_if_t<std::is_same_v<LateInst, HWModuleOp>>>
  HWModuleOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class HWModuleOpAdaptor : public HWModuleOpGenericAdaptor<::mlir::ValueRange> {
public:
  using HWModuleOpGenericAdaptor::HWModuleOpGenericAdaptor;
  HWModuleOpAdaptor(HWModuleOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class HWModuleOp : public ::mlir::Op<HWModuleOp, ::mlir::OpTrait::OneRegion, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::SingleBlock, ::mlir::OpTrait::SingleBlockImplicitTerminator<OutputOp>::Impl, ::mlir::OpTrait::HasParent<mlir::ModuleOp>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::OpTrait::IsIsolatedFromAbove, ::mlir::RegionKindInterface::Trait, ::mlir::SymbolOpInterface::Trait, circt::hw::PortList::Trait, ::circt::igraph::ModuleOpInterface::Trait, circt::hw::HWModuleLike::Trait, ::circt::emit::Emittable::Trait, ::circt::hw::HWEmittableModuleLike::Trait, ::circt::NonProceduralRegion, circt::hw::HWMutableModuleLike::Trait, ::mlir::OpTrait::InnerSymbolTable, ::mlir::OpAsmOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = HWModuleOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = HWModuleOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  using circt::hw::HWMutableModuleLike::Trait<HWModuleOp>::getPortLookupInfo;
  using circt::hw::HWMutableModuleLike::Trait<HWModuleOp>::insertPorts;
  using circt::hw::HWMutableModuleLike::Trait<HWModuleOp>::erasePorts;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("comment"), ::llvm::StringRef("module_type"), ::llvm::StringRef("parameters"), ::llvm::StringRef("per_port_attrs"), ::llvm::StringRef("result_locs"), ::llvm::StringRef("sym_name")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getCommentAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getCommentAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getModuleTypeAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getModuleTypeAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getParametersAttrName() {
    return getAttributeNameForIndex(2);
  }

  static ::mlir::StringAttr getParametersAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 2);
  }

  ::mlir::StringAttr getPerPortAttrsAttrName() {
    return getAttributeNameForIndex(3);
  }

  static ::mlir::StringAttr getPerPortAttrsAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 3);
  }

  ::mlir::StringAttr getResultLocsAttrName() {
    return getAttributeNameForIndex(4);
  }

  static ::mlir::StringAttr getResultLocsAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 4);
  }

  ::mlir::StringAttr getSymNameAttrName() {
    return getAttributeNameForIndex(5);
  }

  static ::mlir::StringAttr getSymNameAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 5);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("hw.module");
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
  ::mlir::TypeAttr getModuleTypeAttr() {
    return ::llvm::cast<::mlir::TypeAttr>(getProperties().module_type);
  }

  ::circt::hw::ModuleType getModuleType();
  ::mlir::ArrayAttr getPerPortAttrsAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().per_port_attrs);
  }

  ::std::optional< ::mlir::ArrayAttr > getPerPortAttrs();
  ::mlir::ArrayAttr getResultLocsAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().result_locs);
  }

  ::std::optional< ::mlir::ArrayAttr > getResultLocs();
  ::mlir::ArrayAttr getParametersAttr() {
    return ::llvm::cast<::mlir::ArrayAttr>(getProperties().parameters);
  }

  ::mlir::ArrayAttr getParameters();
  ::mlir::StringAttr getCommentAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::StringAttr>(getProperties().comment);
  }

  ::std::optional< ::llvm::StringRef > getComment();
  void setSymNameAttr(::mlir::StringAttr attr) {
    getProperties().sym_name = attr;
  }

  void setSymName(::llvm::StringRef attrValue);
  void setModuleTypeAttr(::mlir::TypeAttr attr) {
    getProperties().module_type = attr;
  }

  void setModuleType(::circt::hw::ModuleType attrValue);
  void setPerPortAttrsAttr(::mlir::ArrayAttr attr) {
    getProperties().per_port_attrs = attr;
  }

  void setResultLocsAttr(::mlir::ArrayAttr attr) {
    getProperties().result_locs = attr;
  }

  void setParametersAttr(::mlir::ArrayAttr attr) {
    getProperties().parameters = attr;
  }

  void setCommentAttr(::mlir::StringAttr attr) {
    getProperties().comment = attr;
  }

  void setComment(::std::optional<::llvm::StringRef> attrValue);
  ::mlir::Attribute removePerPortAttrsAttr() {
      auto attr = getProperties().per_port_attrs;
      getProperties().per_port_attrs = {};
      return attr;
  }

  ::mlir::Attribute removeResultLocsAttr() {
      auto attr = getProperties().result_locs;
      getProperties().result_locs = {};
      return attr;
  }

  ::mlir::Attribute removeCommentAttr() {
      auto attr = getProperties().comment;
      getProperties().comment = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, StringAttr name, ArrayRef<PortInfo> ports, ArrayAttr parameters = {}, ArrayRef<NamedAttribute> attributes = {}, StringAttr comment = {});
  static HWModuleOp create(::mlir::OpBuilder &builder, ::mlir::Location location, StringAttr name, ArrayRef<PortInfo> ports, ArrayAttr parameters = {}, ArrayRef<NamedAttribute> attributes = {}, StringAttr comment = {});
  static HWModuleOp create(::mlir::ImplicitLocOpBuilder &builder, StringAttr name, ArrayRef<PortInfo> ports, ArrayAttr parameters = {}, ArrayRef<NamedAttribute> attributes = {}, StringAttr comment = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, StringAttr name, const ModulePortInfo &ports, ArrayAttr parameters = {}, ArrayRef<NamedAttribute> attributes = {}, StringAttr comment = {}, bool shouldEnsureTerminator = true);
  static HWModuleOp create(::mlir::OpBuilder &builder, ::mlir::Location location, StringAttr name, const ModulePortInfo &ports, ArrayAttr parameters = {}, ArrayRef<NamedAttribute> attributes = {}, StringAttr comment = {}, bool shouldEnsureTerminator = true);
  static HWModuleOp create(::mlir::ImplicitLocOpBuilder &builder, StringAttr name, const ModulePortInfo &ports, ArrayAttr parameters = {}, ArrayRef<NamedAttribute> attributes = {}, StringAttr comment = {}, bool shouldEnsureTerminator = true);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, StringAttr name, const ModulePortInfo &ports, HWModuleBuilder modBuilder, ArrayAttr parameters = {}, ArrayRef<NamedAttribute> attributes = {}, StringAttr comment = {});
  static HWModuleOp create(::mlir::OpBuilder &builder, ::mlir::Location location, StringAttr name, const ModulePortInfo &ports, HWModuleBuilder modBuilder, ArrayAttr parameters = {}, ArrayRef<NamedAttribute> attributes = {}, StringAttr comment = {});
  static HWModuleOp create(::mlir::ImplicitLocOpBuilder &builder, StringAttr name, const ModulePortInfo &ports, HWModuleBuilder modBuilder, ArrayAttr parameters = {}, ArrayRef<NamedAttribute> attributes = {}, StringAttr comment = {});
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &p);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  SmallVector<::circt::hw::PortInfo> getPortList();
  ::circt::hw::PortInfo getPort(size_t idx);
  size_t getPortIdForInputId(size_t idx);
  size_t getPortIdForOutputId(size_t idx);
  size_t getNumPorts();
  size_t getNumInputPorts();
  size_t getNumOutputPorts();
  ::circt::hw::ModuleType getHWModuleType();
  ArrayRef<Attribute> getAllPortAttrs();
  void setAllPortAttrs(ArrayRef<Attribute> attrs);
  void removeAllPortAttrs();
  SmallVector<Location> getAllPortLocs();
  void setAllPortLocsAttrs(ArrayRef<Attribute> locs);
  void setHWModuleType(::circt::hw::ModuleType type);
  void setAllPortNames(ArrayRef<Attribute> names);
  void appendOutputs(ArrayRef<std::pair<StringAttr, Value>> outputs);
  static ::llvm::LogicalResult setPropertiesFromParsedAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
private:
  ::mlir::StringAttr getAttributeNameForIndex(unsigned index) {
    return getAttributeNameForIndex((*this)->getName(), index);
  }

  static ::mlir::StringAttr getAttributeNameForIndex(::mlir::OperationName name, unsigned index) {
    assert(index < 6 && "invalid attribute index");
    assert(name.getStringRef() == getOperationName() && "invalid operation name");
    assert(name.isRegistered() && "Operation isn't registered, missing a "
          "dependent dialect loading?");
    return name.getAttributeNames()[index];
  }

public:
  // Implement RegionKindInterface.
  static RegionKind getRegionKind(unsigned index) { return RegionKind::Graph;}

  /// Append an input with a given name and type to the port list.
  /// If the name is not unique, a unique name is created and returned.
  std::pair<StringAttr, BlockArgument>
  appendInput(const Twine &name, Type ty) {
    return insertInput(getNumInputPorts(), name, ty);
  }

  std::pair<StringAttr, BlockArgument>
  appendInput(StringAttr name, Type ty) {
    return insertInput(getNumInputPorts(), name.getValue(), ty);
  }

  /// Prepend an input with a given name and type to the port list.
  /// If the name is not unique, a unique name is created and returned.
  std::pair<StringAttr, BlockArgument>
  prependInput(const Twine &name, Type ty) {
    return insertInput(0, name, ty);
  }

  std::pair<StringAttr, BlockArgument>
  prependInput(StringAttr name, Type ty) {
    return insertInput(0, name.getValue(), ty);
  }

  /// Insert an input with a given name and type into the port list.
  /// The input is added at the specified index.
  std::pair<StringAttr, BlockArgument>
  insertInput(unsigned index, StringAttr name, Type ty);

  std::pair<StringAttr, BlockArgument>
  insertInput(unsigned index, const Twine &name, Type ty) {
    ::mlir::StringAttr nameAttr = ::mlir::StringAttr::get(getContext(), name);
    return insertInput(index, nameAttr, ty);
  }

  /// Append an output with a given name and type to the port list.
  /// If the name is not unique, a unique name is created.
  void appendOutput(StringAttr name, Value value) {
    return insertOutputs(getNumOutputPorts(), {{name, value}});
  }

  void appendOutput(const Twine &name, Value value) {
    ::mlir::StringAttr nameAttr = ::mlir::StringAttr::get(getContext(), name);
    return insertOutputs(getNumOutputPorts(), {{nameAttr, value}});
  }

  /// Prepend an output with a given name and type to the port list.
  /// If the name is not unique, a unique name is created.
  void prependOutput(StringAttr name, Value value) {
    return insertOutputs(0, {{name, value}});
  }

  void prependOutput(const Twine &name, Value value) {
    ::mlir::StringAttr nameAttr = ::mlir::StringAttr::get(getContext(), name);
    return insertOutputs(0, {{nameAttr, value}});
  }

  /// Inserts a list of output ports into the port list at a specific
  /// location, shifting all subsequent ports.  Rewrites the output op
  /// to return the associated values.
  void insertOutputs(unsigned index,
                     ArrayRef<std::pair<StringAttr, Value>> outputs);

  // Get the module's symbolic name as StringAttr.
  StringAttr getNameAttr() {
    return (*this)->getAttrOfType<StringAttr>(
      ::mlir::SymbolTable::getSymbolAttrName());
  }

  // Get the module's symbolic name.
  StringRef getName() {
    return getNameAttr().getValue();
  }
  void getAsmBlockArgumentNames(mlir::Region &region,
                                mlir::OpAsmSetValueNameFn setNameFn);

  /// Verifies the body of the function.
  LogicalResult verifyBody();

  /// Insert and remove input and output ports of this module. Does not modify
  /// the block arguments of the module body. The insertion and removal
  /// indices must be in ascending order. The indices refer to the port
  /// positions before any insertion or removal occurs. Ports inserted at the
  /// same index will appear in the module in the same order as they were
  /// listed in the insertion arrays.
  void modifyPorts(
    ArrayRef<std::pair<unsigned, PortInfo>> insertInputs,
    ArrayRef<std::pair<unsigned, PortInfo>> insertOutputs,
    ArrayRef<unsigned> eraseInputs,
    ArrayRef<unsigned> eraseOutputs
  );

  void setPortSymbolAttr(size_t portIndex, ::circt::hw::InnerSymAttr sym);

  StringAttr getArgName(size_t index) {
    return getHWModuleType().getInputNameAttr(index);
  }

};

} // namespace circt::hw
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::hw::HWModuleOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::hw::detail::HWModuleOpGenericAdaptorBase::Properties)

namespace circt::hw {


//===----------------------------------------------------------------------===//
// ::circt::hw::HierPathOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class HierPathOpGenericAdaptorBase {
public:
  struct Properties {
    using namepathTy = ::mlir::ArrayAttr;
    namepathTy namepath;

    auto getNamepath() const {
      auto &propStorage = this->namepath;
      return ::llvm::cast<::mlir::ArrayAttr>(propStorage);
    }
    void setNamepath(const ::mlir::ArrayAttr &propValue) {
      this->namepath = propValue;
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
        rhs.namepath == this->namepath &&
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
  HierPathOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("hw.hierpath", odsAttrs.getContext());
  }

  HierPathOpGenericAdaptorBase(HierPathOp op);

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
  ::mlir::ArrayAttr getNamepathAttr() {
    auto attr = ::llvm::cast<::mlir::ArrayAttr>(getProperties().namepath);
    return attr;
  }

  ::mlir::ArrayAttr getNamepath();
};

} // namespace detail
template <typename RangeT>
class HierPathOpGenericAdaptor : public detail::HierPathOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::HierPathOpGenericAdaptorBase;
public:
  HierPathOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  HierPathOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : HierPathOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  HierPathOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : HierPathOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  HierPathOpGenericAdaptor(RangeT values, const HierPathOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = HierPathOp, typename = std::enable_if_t<std::is_same_v<LateInst, HierPathOp>>>
  HierPathOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class HierPathOpAdaptor : public HierPathOpGenericAdaptor<::mlir::ValueRange> {
public:
  using HierPathOpGenericAdaptor::HierPathOpGenericAdaptor;
  HierPathOpAdaptor(HierPathOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class HierPathOp : public ::mlir::Op<HierPathOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::OpTrait::IsIsolatedFromAbove, ::mlir::SymbolOpInterface::Trait, ::circt::hw::InnerRefUserOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = HierPathOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = HierPathOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("namepath"), ::llvm::StringRef("sym_name")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getNamepathAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getNamepathAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getSymNameAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getSymNameAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("hw.hierpath");
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
  ::mlir::ArrayAttr getNamepathAttr() {
    return ::llvm::cast<::mlir::ArrayAttr>(getProperties().namepath);
  }

  ::mlir::ArrayAttr getNamepath();
  void setSymNameAttr(::mlir::StringAttr attr) {
    getProperties().sym_name = attr;
  }

  void setSymName(::llvm::StringRef attrValue);
  void setNamepathAttr(::mlir::ArrayAttr attr) {
    getProperties().namepath = attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::StringAttr sym_name, ::mlir::ArrayAttr namepath);
  static HierPathOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::StringAttr sym_name, ::mlir::ArrayAttr namepath);
  static HierPathOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::StringAttr sym_name, ::mlir::ArrayAttr namepath);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name, ::mlir::ArrayAttr namepath);
  static HierPathOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name, ::mlir::ArrayAttr namepath);
  static HierPathOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name, ::mlir::ArrayAttr namepath);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::llvm::StringRef sym_name, ::mlir::ArrayAttr namepath);
  static HierPathOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::llvm::StringRef sym_name, ::mlir::ArrayAttr namepath);
  static HierPathOp create(::mlir::ImplicitLocOpBuilder &builder, ::llvm::StringRef sym_name, ::mlir::ArrayAttr namepath);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name, ::mlir::ArrayAttr namepath);
  static HierPathOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name, ::mlir::ArrayAttr namepath);
  static HierPathOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name, ::mlir::ArrayAttr namepath);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static HierPathOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static HierPathOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static HierPathOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static HierPathOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &p);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::mlir::LogicalResult verifyInnerRefs(::circt::hw::InnerRefNamespace&ns);
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
  /// Drop the module from the namepath. If its a InnerNameRef, then drop
  /// the Module-Instance pair, else drop the final module from the namepath.
  /// Return true if any update is made.
  bool dropModule(StringAttr moduleToDrop);

  /// Inline the module in the namepath.
  /// Update the symbol name for the inlined module instance, by prepending
  /// the symbol name of the instance at which the inling was done.
  /// Return true if any update is made.
  bool inlineModule(StringAttr moduleToDrop);

  /// Replace the oldMod module with newMod module in the namepath of the NLA.
  /// Return true if any update is made.
  bool updateModule(StringAttr oldMod, StringAttr newMod);

  /// Replace the oldMod module with newMod module in the namepath of the NLA.
  /// Since the module is being updated, the symbols inside the module should
  /// also be renamed. Use the rename Map to update the corresponding
  /// inner_sym names in the namepath. Return true if any update is made.
  bool updateModuleAndInnerRef(StringAttr oldMod, StringAttr newMod,
       const llvm::DenseMap<StringAttr, StringAttr> &innerSymRenameMap);

  /// Truncate the namepath for this NLA, at atMod module.
  /// If includeMod is false, drop atMod and beyond, else include it and drop
  /// everything after it.
  /// Return true if any update is made.
  bool truncateAtModule(StringAttr atMod, bool includeMod = true);

  /// Return just the module part of the namepath at a specific index.
  StringAttr modPart(unsigned i);

  /// Return the root module.
  StringAttr root();

  /// Return just the reference part of the namepath at a specific index.
  /// This will return an empty attribute if this is the leaf and the leaf is
  /// a module.
  StringAttr refPart(unsigned i);

  /// Return the leaf reference.  This returns an empty attribute if the leaf
  /// reference is a module.
  StringAttr ref();

  /// Return the leaf Module.
  StringAttr leafMod();

  /// Returns true, if the NLA path contains the module.
  bool hasModule(StringAttr modName);

  /// Returns true, if the NLA path contains the InnerSym {modName, symName}.
  bool hasInnerSym(StringAttr modName, StringAttr symName) const;

  /// Returns true if this NLA targets a module or instance of a module (as
  /// opposed to an instance's port or something inside an instance).
  bool isModule();

  /// Returns true if this NLA targets something inside a module (as opposed
  /// to a module or an instance of a module);
  bool isComponent();
};

} // namespace circt::hw
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::hw::HierPathOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::hw::detail::HierPathOpGenericAdaptorBase::Properties)

namespace circt::hw {


//===----------------------------------------------------------------------===//
// ::circt::hw::InstanceOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class InstanceOpGenericAdaptorBase {
public:
  struct Properties {
    using argNamesTy = ::mlir::ArrayAttr;
    argNamesTy argNames;

    auto getArgNames() const {
      auto &propStorage = this->argNames;
      return ::llvm::cast<::mlir::ArrayAttr>(propStorage);
    }
    void setArgNames(const ::mlir::ArrayAttr &propValue) {
      this->argNames = propValue;
    }
    using doNotPrintTy = ::mlir::UnitAttr;
    doNotPrintTy doNotPrint;

    auto getDoNotPrint() const {
      auto &propStorage = this->doNotPrint;
      return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(propStorage);
    }
    void setDoNotPrint(const ::mlir::UnitAttr &propValue) {
      this->doNotPrint = propValue;
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
    using instanceNameTy = ::mlir::StringAttr;
    instanceNameTy instanceName;

    auto getInstanceName() const {
      auto &propStorage = this->instanceName;
      return ::llvm::cast<::mlir::StringAttr>(propStorage);
    }
    void setInstanceName(const ::mlir::StringAttr &propValue) {
      this->instanceName = propValue;
    }
    using moduleNameTy = ::mlir::FlatSymbolRefAttr;
    moduleNameTy moduleName;

    auto getModuleName() const {
      auto &propStorage = this->moduleName;
      return ::llvm::cast<::mlir::FlatSymbolRefAttr>(propStorage);
    }
    void setModuleName(const ::mlir::FlatSymbolRefAttr &propValue) {
      this->moduleName = propValue;
    }
    using parametersTy = ::mlir::ArrayAttr;
    parametersTy parameters;

    auto getParameters() const {
      auto &propStorage = this->parameters;
      return ::llvm::cast<::mlir::ArrayAttr>(propStorage);
    }
    void setParameters(const ::mlir::ArrayAttr &propValue) {
      this->parameters = propValue;
    }
    using resultNamesTy = ::mlir::ArrayAttr;
    resultNamesTy resultNames;

    auto getResultNames() const {
      auto &propStorage = this->resultNames;
      return ::llvm::cast<::mlir::ArrayAttr>(propStorage);
    }
    void setResultNames(const ::mlir::ArrayAttr &propValue) {
      this->resultNames = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.argNames == this->argNames &&
        rhs.doNotPrint == this->doNotPrint &&
        rhs.inner_sym == this->inner_sym &&
        rhs.instanceName == this->instanceName &&
        rhs.moduleName == this->moduleName &&
        rhs.parameters == this->parameters &&
        rhs.resultNames == this->resultNames &&
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
  InstanceOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("hw.instance", odsAttrs.getContext());
  }

  InstanceOpGenericAdaptorBase(InstanceOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::StringAttr getInstanceNameAttr() {
    auto attr = ::llvm::cast<::mlir::StringAttr>(getProperties().instanceName);
    return attr;
  }

  ::llvm::StringRef getInstanceName();
  ::mlir::FlatSymbolRefAttr getModuleNameAttr() {
    auto attr = ::llvm::cast<::mlir::FlatSymbolRefAttr>(getProperties().moduleName);
    return attr;
  }

  ::llvm::StringRef getModuleName();
  ::mlir::ArrayAttr getArgNamesAttr() {
    auto attr = ::llvm::cast<::mlir::ArrayAttr>(getProperties().argNames);
    return attr;
  }

  ::mlir::ArrayAttr getArgNames();
  ::mlir::ArrayAttr getResultNamesAttr() {
    auto attr = ::llvm::cast<::mlir::ArrayAttr>(getProperties().resultNames);
    return attr;
  }

  ::mlir::ArrayAttr getResultNames();
  ::mlir::ArrayAttr getParametersAttr() {
    auto attr = ::llvm::cast<::mlir::ArrayAttr>(getProperties().parameters);
    return attr;
  }

  ::mlir::ArrayAttr getParameters();
  ::circt::hw::InnerSymAttr getInnerSymAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::circt::hw::InnerSymAttr>(getProperties().inner_sym);
    return attr;
  }

  ::std::optional<::circt::hw::InnerSymAttr> getInnerSym();
  ::mlir::UnitAttr getDoNotPrintAttr();
  bool getDoNotPrint();
};

} // namespace detail
template <typename RangeT>
class InstanceOpGenericAdaptor : public detail::InstanceOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::InstanceOpGenericAdaptorBase;
  static constexpr int odsIndex_inputs = 0;
public:
  InstanceOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  InstanceOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : InstanceOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  InstanceOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : InstanceOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  InstanceOpGenericAdaptor(RangeT values, const InstanceOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = InstanceOp, typename = std::enable_if_t<std::is_same_v<LateInst, InstanceOp>>>
  InstanceOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class InstanceOpAdaptor : public InstanceOpGenericAdaptor<::mlir::ValueRange> {
public:
  using InstanceOpGenericAdaptor::InstanceOpGenericAdaptor;
  InstanceOpAdaptor(InstanceOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class InstanceOp : public ::mlir::Op<InstanceOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::VariadicResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::circt::igraph::InstanceOpInterface::Trait, circt::hw::HWInstanceLike::Trait, ::mlir::SymbolUserOpInterface::Trait, circt::hw::PortList::Trait, ::mlir::OpAsmOpInterface::Trait, ::circt::hw::InnerSymbolOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = InstanceOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = InstanceOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_inputs = 0;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::OpAsmOpInterface::Trait<InstanceOp>::getAsmBlockArgumentNames;
  using ::mlir::OpAsmOpInterface::Trait<InstanceOp>::getAsmBlockNames;
  using ::mlir::OpAsmOpInterface::Trait<InstanceOp>::getDefaultDialect;
  using ::circt::hw::InnerSymbolOpInterface::Trait<InstanceOp>::getInnerNameAttr;
  using ::circt::hw::InnerSymbolOpInterface::Trait<InstanceOp>::getInnerName;
  using ::circt::hw::InnerSymbolOpInterface::Trait<InstanceOp>::setInnerSymbol;
  using ::circt::hw::InnerSymbolOpInterface::Trait<InstanceOp>::setInnerSymbolAttr;
  using ::circt::hw::InnerSymbolOpInterface::Trait<InstanceOp>::getInnerRef;
  using ::circt::hw::InnerSymbolOpInterface::Trait<InstanceOp>::getInnerSymAttr;
  using ::circt::hw::InnerSymbolOpInterface::Trait<InstanceOp>::supportsPerFieldSymbols;
  using ::circt::hw::InnerSymbolOpInterface::Trait<InstanceOp>::getTargetResult;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("argNames"), ::llvm::StringRef("doNotPrint"), ::llvm::StringRef("inner_sym"), ::llvm::StringRef("instanceName"), ::llvm::StringRef("moduleName"), ::llvm::StringRef("parameters"), ::llvm::StringRef("resultNames")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getArgNamesAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getArgNamesAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getDoNotPrintAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getDoNotPrintAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getInnerSymAttrName() {
    return getAttributeNameForIndex(2);
  }

  static ::mlir::StringAttr getInnerSymAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 2);
  }

  ::mlir::StringAttr getInstanceNameAttrName() {
    return getAttributeNameForIndex(3);
  }

  static ::mlir::StringAttr getInstanceNameAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 3);
  }

  ::mlir::StringAttr getModuleNameAttrName() {
    return getAttributeNameForIndex(4);
  }

  static ::mlir::StringAttr getModuleNameAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 4);
  }

  ::mlir::StringAttr getParametersAttrName() {
    return getAttributeNameForIndex(5);
  }

  static ::mlir::StringAttr getParametersAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 5);
  }

  ::mlir::StringAttr getResultNamesAttrName() {
    return getAttributeNameForIndex(6);
  }

  static ::mlir::StringAttr getResultNamesAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 6);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("hw.instance");
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

  ::mlir::Operation::result_range getResults() {
    return getODSResults(0);
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
  ::mlir::StringAttr getInstanceNameAttr() {
    return ::llvm::cast<::mlir::StringAttr>(getProperties().instanceName);
  }

  ::llvm::StringRef getInstanceName();
  ::mlir::FlatSymbolRefAttr getModuleNameAttr() {
    return ::llvm::cast<::mlir::FlatSymbolRefAttr>(getProperties().moduleName);
  }

  ::llvm::StringRef getModuleName();
  ::mlir::ArrayAttr getArgNamesAttr() {
    return ::llvm::cast<::mlir::ArrayAttr>(getProperties().argNames);
  }

  ::mlir::ArrayAttr getArgNames();
  ::mlir::ArrayAttr getResultNamesAttr() {
    return ::llvm::cast<::mlir::ArrayAttr>(getProperties().resultNames);
  }

  ::mlir::ArrayAttr getResultNames();
  ::mlir::ArrayAttr getParametersAttr() {
    return ::llvm::cast<::mlir::ArrayAttr>(getProperties().parameters);
  }

  ::mlir::ArrayAttr getParameters();
  ::circt::hw::InnerSymAttr getInnerSymAttr() {
    return ::llvm::dyn_cast_or_null<::circt::hw::InnerSymAttr>(getProperties().inner_sym);
  }

  ::std::optional<::circt::hw::InnerSymAttr> getInnerSym();
  ::mlir::UnitAttr getDoNotPrintAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(getProperties().doNotPrint);
  }

  bool getDoNotPrint();
  void setInstanceNameAttr(::mlir::StringAttr attr) {
    getProperties().instanceName = attr;
  }

  void setInstanceName(::llvm::StringRef attrValue);
  void setModuleNameAttr(::mlir::FlatSymbolRefAttr attr) {
    getProperties().moduleName = attr;
  }

  void setModuleName(::llvm::StringRef attrValue);
  void setArgNamesAttr(::mlir::ArrayAttr attr) {
    getProperties().argNames = attr;
  }

  void setResultNamesAttr(::mlir::ArrayAttr attr) {
    getProperties().resultNames = attr;
  }

  void setParametersAttr(::mlir::ArrayAttr attr) {
    getProperties().parameters = attr;
  }

  void setInnerSymAttr(::circt::hw::InnerSymAttr attr) {
    getProperties().inner_sym = attr;
  }

  void setDoNotPrintAttr(::mlir::UnitAttr attr) {
    getProperties().doNotPrint = attr;
  }

  void setDoNotPrint(bool attrValue);
  ::mlir::Attribute removeInnerSymAttr() {
      auto attr = getProperties().inner_sym;
      getProperties().inner_sym = {};
      return attr;
  }

  ::mlir::Attribute removeDoNotPrintAttr() {
      auto attr = getProperties().doNotPrint;
      getProperties().doNotPrint = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Operation*module, StringAttr name, ArrayRef<Value> inputs, ArrayAttr parameters = {}, InnerSymAttr innerSym = {});
  static InstanceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Operation*module, StringAttr name, ArrayRef<Value> inputs, ArrayAttr parameters = {}, InnerSymAttr innerSym = {});
  static InstanceOp create(::mlir::ImplicitLocOpBuilder &builder, Operation*module, StringAttr name, ArrayRef<Value> inputs, ArrayAttr parameters = {}, InnerSymAttr innerSym = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Operation*module, StringRef name, ArrayRef<Value> inputs, ArrayAttr parameters = {}, InnerSymAttr innerSym = {});
  static InstanceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Operation*module, StringRef name, ArrayRef<Value> inputs, ArrayAttr parameters = {}, InnerSymAttr innerSym = {});
  static InstanceOp create(::mlir::ImplicitLocOpBuilder &builder, Operation*module, StringRef name, ArrayRef<Value> inputs, ArrayAttr parameters = {}, InnerSymAttr innerSym = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange results, ::mlir::StringAttr instanceName, ::mlir::FlatSymbolRefAttr moduleName, ::mlir::ValueRange inputs, ::mlir::ArrayAttr argNames, ::mlir::ArrayAttr resultNames, ::mlir::ArrayAttr parameters, /*optional*/::circt::hw::InnerSymAttr inner_sym, /*optional*/::mlir::UnitAttr doNotPrint = nullptr);
  static InstanceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange results, ::mlir::StringAttr instanceName, ::mlir::FlatSymbolRefAttr moduleName, ::mlir::ValueRange inputs, ::mlir::ArrayAttr argNames, ::mlir::ArrayAttr resultNames, ::mlir::ArrayAttr parameters, /*optional*/::circt::hw::InnerSymAttr inner_sym, /*optional*/::mlir::UnitAttr doNotPrint = nullptr);
  static InstanceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange results, ::mlir::StringAttr instanceName, ::mlir::FlatSymbolRefAttr moduleName, ::mlir::ValueRange inputs, ::mlir::ArrayAttr argNames, ::mlir::ArrayAttr resultNames, ::mlir::ArrayAttr parameters, /*optional*/::circt::hw::InnerSymAttr inner_sym, /*optional*/::mlir::UnitAttr doNotPrint = nullptr);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange results, ::llvm::StringRef instanceName, ::llvm::StringRef moduleName, ::mlir::ValueRange inputs, ::mlir::ArrayAttr argNames, ::mlir::ArrayAttr resultNames, ::mlir::ArrayAttr parameters, /*optional*/::circt::hw::InnerSymAttr inner_sym, /*optional*/bool doNotPrint = false);
  static InstanceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange results, ::llvm::StringRef instanceName, ::llvm::StringRef moduleName, ::mlir::ValueRange inputs, ::mlir::ArrayAttr argNames, ::mlir::ArrayAttr resultNames, ::mlir::ArrayAttr parameters, /*optional*/::circt::hw::InnerSymAttr inner_sym, /*optional*/bool doNotPrint = false);
  static InstanceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange results, ::llvm::StringRef instanceName, ::llvm::StringRef moduleName, ::mlir::ValueRange inputs, ::mlir::ArrayAttr argNames, ::mlir::ArrayAttr resultNames, ::mlir::ArrayAttr parameters, /*optional*/::circt::hw::InnerSymAttr inner_sym, /*optional*/bool doNotPrint = false);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static InstanceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static InstanceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static InstanceOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static InstanceOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &p);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  ::llvm::LogicalResult verifySymbolUses(::mlir::SymbolTableCollection &symbolTable);
  SmallVector<::circt::hw::PortInfo> getPortList();
  ::circt::hw::PortInfo getPort(size_t idx);
  size_t getPortIdForInputId(size_t idx);
  size_t getPortIdForOutputId(size_t idx);
  size_t getNumPorts();
  size_t getNumInputPorts();
  size_t getNumOutputPorts();
  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
  static std::optional<size_t> getTargetResultIndex();
  static ::llvm::LogicalResult setPropertiesFromParsedAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
private:
  ::mlir::StringAttr getAttributeNameForIndex(unsigned index) {
    return getAttributeNameForIndex((*this)->getName(), index);
  }

  static ::mlir::StringAttr getAttributeNameForIndex(::mlir::OperationName name, unsigned index) {
    assert(index < 7 && "invalid attribute index");
    assert(name.getStringRef() == getOperationName() && "invalid operation name");
    assert(name.isRegistered() && "Operation isn't registered, missing a "
          "dependent dialect loading?");
    return name.getAttributeNames()[index];
  }

public:
  /**
   * Return the name of the default target.
   */
  ::llvm::StringRef getReferencedModuleName() {
    return getReferencedModuleNameAttr().getValue();
  }

  /**
   * Return the name of the default target.
   */
  ::mlir::StringAttr getReferencedModuleNameAttr() {
    return getModuleNameAttr().getAttr();
  }

  /// Return the values for the port in port order.
  /// Note: The module ports may not be input, output ordered. This computes
  /// the port index to instance result/input Value mapping.
  void getValues(SmallVectorImpl<Value> &values, const ModulePortInfo &mpi);
};

} // namespace circt::hw
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::hw::InstanceOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::hw::detail::InstanceOpGenericAdaptorBase::Properties)

namespace circt::hw {


//===----------------------------------------------------------------------===//
// ::circt::hw::OutputOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class OutputOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  OutputOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("hw.output", odsAttrs.getContext());
  }

  OutputOpGenericAdaptorBase(OutputOp op);

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
class OutputOpGenericAdaptor : public detail::OutputOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::OutputOpGenericAdaptorBase;
  static constexpr int odsIndex_outputs = 0;
public:
  OutputOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  OutputOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : OutputOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  OutputOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : OutputOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  OutputOpGenericAdaptor(RangeT values, const OutputOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = OutputOp, typename = std::enable_if_t<std::is_same_v<LateInst, OutputOp>>>
  OutputOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getOutputs() {
    return getODSOperands(0);
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class OutputOpAdaptor : public OutputOpGenericAdaptor<::mlir::ValueRange> {
public:
  using OutputOpGenericAdaptor::OutputOpGenericAdaptor;
  OutputOpAdaptor(OutputOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class OutputOp : public ::mlir::Op<OutputOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::HasParent<HWModuleOp>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::OpTrait::IsTerminator, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::RegionBranchTerminatorOpInterface::Trait, ::mlir::OpTrait::ReturnLike> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = OutputOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = OutputOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_outputs = 0;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::RegionBranchTerminatorOpInterface::Trait<OutputOp>::getMutableSuccessorOperands;
  using ::mlir::RegionBranchTerminatorOpInterface::Trait<OutputOp>::getSuccessorRegions;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("hw.output");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::operand_range getOutputs() {
    return getODSOperands(0);
  }

  ::mlir::MutableOperandRange getOutputsMutable();
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
  static OutputOp create(::mlir::OpBuilder &builder, ::mlir::Location location);
  static OutputOp create(::mlir::ImplicitLocOpBuilder &builder);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange outputs);
  static OutputOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange outputs);
  static OutputOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange outputs);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static OutputOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static OutputOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static OutputOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static OutputOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
};

} // namespace circt::hw
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::hw::OutputOp)

namespace circt::hw {


//===----------------------------------------------------------------------===//
// ::circt::hw::ParamValueOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ParamValueOpGenericAdaptorBase {
public:
  struct Properties {
    using valueTy = ::mlir::Attribute;
    valueTy value;

    auto getValue() const {
      auto &propStorage = this->value;
      return ::llvm::cast<::mlir::Attribute>(propStorage);
    }
    void setValue(const ::mlir::Attribute &propValue) {
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
  ParamValueOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("hw.param.value", odsAttrs.getContext());
  }

  ParamValueOpGenericAdaptorBase(ParamValueOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::Attribute getValueAttr() {
    auto attr = ::llvm::cast<::mlir::Attribute>(getProperties().value);
    return attr;
  }

  ::mlir::Attribute getValue();
};

} // namespace detail
template <typename RangeT>
class ParamValueOpGenericAdaptor : public detail::ParamValueOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ParamValueOpGenericAdaptorBase;
public:
  ParamValueOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ParamValueOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : ParamValueOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ParamValueOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ParamValueOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ParamValueOpGenericAdaptor(RangeT values, const ParamValueOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ParamValueOp, typename = std::enable_if_t<std::is_same_v<LateInst, ParamValueOp>>>
  ParamValueOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class ParamValueOpAdaptor : public ParamValueOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ParamValueOpGenericAdaptor::ParamValueOpGenericAdaptor;
  ParamValueOpAdaptor(ParamValueOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ParamValueOp : public ::mlir::Op<ParamValueOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::Type>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::OpTrait::ConstantLike> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ParamValueOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ParamValueOpGenericAdaptor<RangeT>;
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
    return ::llvm::StringLiteral("hw.param.value");
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
  ::mlir::Attribute getValueAttr() {
    return ::llvm::cast<::mlir::Attribute>(getProperties().value);
  }

  ::mlir::Attribute getValue();
  void setValueAttr(::mlir::Attribute attr) {
    getProperties().value = attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Attribute value);
  static ParamValueOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Attribute value);
  static ParamValueOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Attribute value);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Attribute value);
  static ParamValueOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Attribute value);
  static ParamValueOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Attribute value);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ParamValueOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ParamValueOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ParamValueOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ParamValueOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ParamValueOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ParamValueOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ParamValueOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ParamValueOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  ::mlir::OpFoldResult fold(FoldAdaptor adaptor);
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

} // namespace circt::hw
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::hw::ParamValueOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::hw::detail::ParamValueOpGenericAdaptorBase::Properties)

namespace circt::hw {


//===----------------------------------------------------------------------===//
// ::circt::hw::StructCreateOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class StructCreateOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  StructCreateOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("hw.struct_create", odsAttrs.getContext());
  }

  StructCreateOpGenericAdaptorBase(StructCreateOp op);

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
class StructCreateOpGenericAdaptor : public detail::StructCreateOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::StructCreateOpGenericAdaptorBase;
  static constexpr int odsIndex_input = 0;
public:
  StructCreateOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  StructCreateOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : StructCreateOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  StructCreateOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : StructCreateOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  StructCreateOpGenericAdaptor(RangeT values, const StructCreateOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = StructCreateOp, typename = std::enable_if_t<std::is_same_v<LateInst, StructCreateOp>>>
  StructCreateOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getInput() {
    return getODSOperands(0);
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class StructCreateOpAdaptor : public StructCreateOpGenericAdaptor<::mlir::ValueRange> {
public:
  using StructCreateOpGenericAdaptor::StructCreateOpGenericAdaptor;
  StructCreateOpAdaptor(StructCreateOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class StructCreateOp : public ::mlir::Op<StructCreateOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::circt::hw::TypeAliasOr<circt::hw::StructType>>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::OpInvariants, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = StructCreateOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = StructCreateOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_input = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("hw.struct_create");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::operand_range getInput() {
    return getODSOperands(0);
  }

  ::mlir::MutableOperandRange getInputMutable();
  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::circt::hw::TypeAliasOr<circt::hw::StructType>> getResult() {
    return ::llvm::cast<::mlir::TypedValue<::circt::hw::TypeAliasOr<circt::hw::StructType>>>(*getODSResults(0).begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::ValueRange input);
  static StructCreateOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::ValueRange input);
  static StructCreateOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::ValueRange input);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static StructCreateOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static StructCreateOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static StructCreateOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static StructCreateOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &p);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static ::llvm::LogicalResult canonicalize(StructCreateOp op, ::mlir::PatternRewriter &rewriter);
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
  ::mlir::OpFoldResult fold(FoldAdaptor adaptor);
  static ::llvm::LogicalResult setPropertiesFromParsedAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
};

} // namespace circt::hw
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::hw::StructCreateOp)

namespace circt::hw {


//===----------------------------------------------------------------------===//
// ::circt::hw::StructExplodeOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class StructExplodeOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  StructExplodeOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("hw.struct_explode", odsAttrs.getContext());
  }

  StructExplodeOpGenericAdaptorBase(StructExplodeOp op);

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
class StructExplodeOpGenericAdaptor : public detail::StructExplodeOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::StructExplodeOpGenericAdaptorBase;
  static constexpr int odsIndex_input = 0;
public:
  StructExplodeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  StructExplodeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : StructExplodeOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  StructExplodeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : StructExplodeOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  StructExplodeOpGenericAdaptor(RangeT values, const StructExplodeOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = StructExplodeOp, typename = std::enable_if_t<std::is_same_v<LateInst, StructExplodeOp>>>
  StructExplodeOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class StructExplodeOpAdaptor : public StructExplodeOpGenericAdaptor<::mlir::ValueRange> {
public:
  using StructExplodeOpGenericAdaptor::StructExplodeOpGenericAdaptor;
  StructExplodeOpAdaptor(StructExplodeOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class StructExplodeOp : public ::mlir::Op<StructExplodeOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::VariadicResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::OpAsmOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = StructExplodeOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = StructExplodeOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_input = 0;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::OpAsmOpInterface::Trait<StructExplodeOp>::getAsmBlockArgumentNames;
  using ::mlir::OpAsmOpInterface::Trait<StructExplodeOp>::getAsmBlockNames;
  using ::mlir::OpAsmOpInterface::Trait<StructExplodeOp>::getDefaultDialect;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("hw.struct_explode");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::circt::hw::TypeAliasOr<circt::hw::StructType>> getInput() {
    return ::llvm::cast<::mlir::TypedValue<::circt::hw::TypeAliasOr<circt::hw::StructType>>>(*getODSOperands(0).begin());
  }

  ::mlir::OpOperand &getInputMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index);
  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::result_range getResult() {
    return getODSResults(0);
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value input);
  static StructExplodeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value input);
  static StructExplodeOp create(::mlir::ImplicitLocOpBuilder &builder, Value input);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange result, ::mlir::Value input);
  static StructExplodeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange result, ::mlir::Value input);
  static StructExplodeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange result, ::mlir::Value input);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static StructExplodeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static StructExplodeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static StructExplodeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static StructExplodeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &p);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::llvm::LogicalResult canonicalize(StructExplodeOp op, ::mlir::PatternRewriter &rewriter);
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
  ::llvm::LogicalResult fold(FoldAdaptor adaptor, ::llvm::SmallVectorImpl<::mlir::OpFoldResult> &results);
  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
  static ::llvm::LogicalResult setPropertiesFromParsedAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
};

} // namespace circt::hw
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::hw::StructExplodeOp)

namespace circt::hw {


//===----------------------------------------------------------------------===//
// ::circt::hw::StructExtractOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class StructExtractOpGenericAdaptorBase {
public:
  struct Properties {
    using fieldIndexTy = ::mlir::IntegerAttr;
    fieldIndexTy fieldIndex;

    auto getFieldIndex() const {
      auto &propStorage = this->fieldIndex;
      return ::llvm::cast<::mlir::IntegerAttr>(propStorage);
    }
    void setFieldIndex(const ::mlir::IntegerAttr &propValue) {
      this->fieldIndex = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.fieldIndex == this->fieldIndex &&
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
  StructExtractOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("hw.struct_extract", odsAttrs.getContext());
  }

  StructExtractOpGenericAdaptorBase(StructExtractOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::IntegerAttr getFieldIndexAttr() {
    auto attr = ::llvm::cast<::mlir::IntegerAttr>(getProperties().fieldIndex);
    return attr;
  }

  uint32_t getFieldIndex();
};

} // namespace detail
template <typename RangeT>
class StructExtractOpGenericAdaptor : public detail::StructExtractOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::StructExtractOpGenericAdaptorBase;
  static constexpr int odsIndex_input = 0;
public:
  StructExtractOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  StructExtractOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : StructExtractOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  StructExtractOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : StructExtractOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  StructExtractOpGenericAdaptor(RangeT values, const StructExtractOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = StructExtractOp, typename = std::enable_if_t<std::is_same_v<LateInst, StructExtractOp>>>
  StructExtractOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class StructExtractOpAdaptor : public StructExtractOpGenericAdaptor<::mlir::ValueRange> {
public:
  using StructExtractOpGenericAdaptor::StructExtractOpGenericAdaptor;
  StructExtractOpAdaptor(StructExtractOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class StructExtractOp : public ::mlir::Op<StructExtractOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::Type>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::OpAsmOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = StructExtractOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = StructExtractOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_input = 0;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::OpAsmOpInterface::Trait<StructExtractOp>::getAsmBlockArgumentNames;
  using ::mlir::OpAsmOpInterface::Trait<StructExtractOp>::getAsmBlockNames;
  using ::mlir::OpAsmOpInterface::Trait<StructExtractOp>::getDefaultDialect;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("fieldIndex")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getFieldIndexAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getFieldIndexAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("hw.struct_extract");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::circt::hw::TypeAliasOr<circt::hw::StructType>> getInput() {
    return ::llvm::cast<::mlir::TypedValue<::circt::hw::TypeAliasOr<circt::hw::StructType>>>(*getODSOperands(0).begin());
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
  ::mlir::IntegerAttr getFieldIndexAttr() {
    return ::llvm::cast<::mlir::IntegerAttr>(getProperties().fieldIndex);
  }

  uint32_t getFieldIndex();
  void setFieldIndexAttr(::mlir::IntegerAttr attr) {
    getProperties().fieldIndex = attr;
  }

  void setFieldIndex(uint32_t attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value input, StructType::FieldInfo field);
  static StructExtractOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value input, StructType::FieldInfo field);
  static StructExtractOp create(::mlir::ImplicitLocOpBuilder &builder, Value input, StructType::FieldInfo field);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value input, StringAttr fieldName);
  static StructExtractOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value input, StringAttr fieldName);
  static StructExtractOp create(::mlir::ImplicitLocOpBuilder &builder, Value input, StringAttr fieldName);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value input, StringRef fieldName);
  static StructExtractOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value input, StringRef fieldName);
  static StructExtractOp create(::mlir::ImplicitLocOpBuilder &builder, Value input, StringRef fieldName);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value input, ::mlir::IntegerAttr fieldIndex);
  static StructExtractOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value input, ::mlir::IntegerAttr fieldIndex);
  static StructExtractOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value input, ::mlir::IntegerAttr fieldIndex);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value input, ::mlir::IntegerAttr fieldIndex);
  static StructExtractOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value input, ::mlir::IntegerAttr fieldIndex);
  static StructExtractOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value input, ::mlir::IntegerAttr fieldIndex);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value input, uint32_t fieldIndex);
  static StructExtractOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value input, uint32_t fieldIndex);
  static StructExtractOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value input, uint32_t fieldIndex);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value input, uint32_t fieldIndex);
  static StructExtractOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value input, uint32_t fieldIndex);
  static StructExtractOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value input, uint32_t fieldIndex);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static StructExtractOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static StructExtractOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static StructExtractOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static StructExtractOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &p);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static ::llvm::LogicalResult canonicalize(StructExtractOp op, ::mlir::PatternRewriter &rewriter);
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
  ::mlir::OpFoldResult fold(FoldAdaptor adaptor);
  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
  static ::llvm::LogicalResult setPropertiesFromParsedAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
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
  /// Return the name attribute of the accessed field.
  StringAttr getFieldNameAttr() {
    StructType type = getInput().getType();
    return type.getElements()[getFieldIndex()].name;
  }

  /// Return the name of the accessed field.
  StringRef getFieldName() {
    return getFieldNameAttr().getValue();
  }
};

} // namespace circt::hw
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::hw::StructExtractOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::hw::detail::StructExtractOpGenericAdaptorBase::Properties)

namespace circt::hw {


//===----------------------------------------------------------------------===//
// ::circt::hw::StructInjectOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class StructInjectOpGenericAdaptorBase {
public:
  struct Properties {
    using fieldIndexTy = ::mlir::IntegerAttr;
    fieldIndexTy fieldIndex;

    auto getFieldIndex() const {
      auto &propStorage = this->fieldIndex;
      return ::llvm::cast<::mlir::IntegerAttr>(propStorage);
    }
    void setFieldIndex(const ::mlir::IntegerAttr &propValue) {
      this->fieldIndex = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.fieldIndex == this->fieldIndex &&
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
  StructInjectOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("hw.struct_inject", odsAttrs.getContext());
  }

  StructInjectOpGenericAdaptorBase(StructInjectOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::IntegerAttr getFieldIndexAttr() {
    auto attr = ::llvm::cast<::mlir::IntegerAttr>(getProperties().fieldIndex);
    return attr;
  }

  uint32_t getFieldIndex();
};

} // namespace detail
template <typename RangeT>
class StructInjectOpGenericAdaptor : public detail::StructInjectOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::StructInjectOpGenericAdaptorBase;
  static constexpr int odsIndex_input = 0;
  static constexpr int odsIndex_newValue = 1;
public:
  StructInjectOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  StructInjectOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : StructInjectOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  StructInjectOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : StructInjectOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  StructInjectOpGenericAdaptor(RangeT values, const StructInjectOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = StructInjectOp, typename = std::enable_if_t<std::is_same_v<LateInst, StructInjectOp>>>
  StructInjectOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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

  ValueT getNewValue() {
    return (*getODSOperands(1).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class StructInjectOpAdaptor : public StructInjectOpGenericAdaptor<::mlir::ValueRange> {
public:
  using StructInjectOpGenericAdaptor::StructInjectOpGenericAdaptor;
  StructInjectOpAdaptor(StructInjectOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class StructInjectOp : public ::mlir::Op<StructInjectOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::circt::hw::TypeAliasOr<circt::hw::StructType>>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::NOperands<2>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = StructInjectOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = StructInjectOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_input = 0;
  static constexpr int odsIndex_newValue = 1;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("fieldIndex")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getFieldIndexAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getFieldIndexAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("hw.struct_inject");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::circt::hw::TypeAliasOr<circt::hw::StructType>> getInput() {
    return ::llvm::cast<::mlir::TypedValue<::circt::hw::TypeAliasOr<circt::hw::StructType>>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getNewValue() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(1).begin());
  }

  ::mlir::OpOperand &getInputMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getNewValueMutable() {
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

  ::mlir::TypedValue<::circt::hw::TypeAliasOr<circt::hw::StructType>> getResult() {
    return ::llvm::cast<::mlir::TypedValue<::circt::hw::TypeAliasOr<circt::hw::StructType>>>(*getODSResults(0).begin());
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
  ::mlir::IntegerAttr getFieldIndexAttr() {
    return ::llvm::cast<::mlir::IntegerAttr>(getProperties().fieldIndex);
  }

  uint32_t getFieldIndex();
  void setFieldIndexAttr(::mlir::IntegerAttr attr) {
    getProperties().fieldIndex = attr;
  }

  void setFieldIndex(uint32_t attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value input, StringAttr fieldName, Value newValue);
  static StructInjectOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value input, StringAttr fieldName, Value newValue);
  static StructInjectOp create(::mlir::ImplicitLocOpBuilder &builder, Value input, StringAttr fieldName, Value newValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value input, StringRef fieldName, Value newValue);
  static StructInjectOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value input, StringRef fieldName, Value newValue);
  static StructInjectOp create(::mlir::ImplicitLocOpBuilder &builder, Value input, StringRef fieldName, Value newValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value input, ::mlir::IntegerAttr fieldIndex, ::mlir::Value newValue);
  static StructInjectOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value input, ::mlir::IntegerAttr fieldIndex, ::mlir::Value newValue);
  static StructInjectOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value input, ::mlir::IntegerAttr fieldIndex, ::mlir::Value newValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value input, ::mlir::IntegerAttr fieldIndex, ::mlir::Value newValue);
  static StructInjectOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value input, ::mlir::IntegerAttr fieldIndex, ::mlir::Value newValue);
  static StructInjectOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value input, ::mlir::IntegerAttr fieldIndex, ::mlir::Value newValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value input, ::mlir::IntegerAttr fieldIndex, ::mlir::Value newValue);
  static StructInjectOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value input, ::mlir::IntegerAttr fieldIndex, ::mlir::Value newValue);
  static StructInjectOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value input, ::mlir::IntegerAttr fieldIndex, ::mlir::Value newValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value input, uint32_t fieldIndex, ::mlir::Value newValue);
  static StructInjectOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value input, uint32_t fieldIndex, ::mlir::Value newValue);
  static StructInjectOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value input, uint32_t fieldIndex, ::mlir::Value newValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value input, uint32_t fieldIndex, ::mlir::Value newValue);
  static StructInjectOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value input, uint32_t fieldIndex, ::mlir::Value newValue);
  static StructInjectOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value input, uint32_t fieldIndex, ::mlir::Value newValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value input, uint32_t fieldIndex, ::mlir::Value newValue);
  static StructInjectOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value input, uint32_t fieldIndex, ::mlir::Value newValue);
  static StructInjectOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value input, uint32_t fieldIndex, ::mlir::Value newValue);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static StructInjectOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static StructInjectOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static StructInjectOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static StructInjectOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static StructInjectOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static StructInjectOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static StructInjectOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static StructInjectOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &p);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static ::llvm::LogicalResult canonicalize(StructInjectOp op, ::mlir::PatternRewriter &rewriter);
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
  ::mlir::OpFoldResult fold(FoldAdaptor adaptor);
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::PropertyRef properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
  static ::llvm::LogicalResult setPropertiesFromParsedAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
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
  /// Return the name attribute of the accessed field.
  StringAttr getFieldNameAttr() {
    StructType type = getInput().getType();
    return type.getElements()[getFieldIndex()].name;
  }

  /// Return the name of the accessed field.
  StringRef getFieldName() {
    return getFieldNameAttr().getValue();
  }
};

} // namespace circt::hw
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::hw::StructInjectOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::hw::detail::StructInjectOpGenericAdaptorBase::Properties)

namespace circt::hw {


//===----------------------------------------------------------------------===//
// ::circt::hw::TriggeredOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class TriggeredOpGenericAdaptorBase {
public:
  struct Properties {
    using eventTy = circt::hw::EventControlAttr;
    eventTy event;

    auto getEvent() const {
      auto &propStorage = this->event;
      return ::llvm::cast<circt::hw::EventControlAttr>(propStorage);
    }
    void setEvent(const circt::hw::EventControlAttr &propValue) {
      this->event = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.event == this->event &&
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
  TriggeredOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("hw.triggered", odsAttrs.getContext());
  }

  TriggeredOpGenericAdaptorBase(TriggeredOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  circt::hw::EventControlAttr getEventAttr() {
    auto attr = ::llvm::cast<circt::hw::EventControlAttr>(getProperties().event);
    return attr;
  }

  circt::hw::EventControl getEvent();
  ::mlir::Region &getBody() {
    return *odsRegions[0];
  }

  ::mlir::RegionRange getRegions() {
    return odsRegions;
  }

};

} // namespace detail
template <typename RangeT>
class TriggeredOpGenericAdaptor : public detail::TriggeredOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::TriggeredOpGenericAdaptorBase;
  static constexpr int odsIndex_trigger = 0;
  static constexpr int odsIndex_inputs = 1;
public:
  TriggeredOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  TriggeredOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : TriggeredOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  TriggeredOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : TriggeredOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  TriggeredOpGenericAdaptor(RangeT values, const TriggeredOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = TriggeredOp, typename = std::enable_if_t<std::is_same_v<LateInst, TriggeredOp>>>
  TriggeredOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getTrigger() {
    return (*getODSOperands(0).begin());
  }

  RangeT getInputs() {
    return getODSOperands(1);
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class TriggeredOpAdaptor : public TriggeredOpGenericAdaptor<::mlir::ValueRange> {
public:
  using TriggeredOpGenericAdaptor::TriggeredOpGenericAdaptor;
  TriggeredOpAdaptor(TriggeredOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class TriggeredOp : public ::mlir::Op<TriggeredOp, ::mlir::OpTrait::OneRegion, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<1>::Impl, ::mlir::OpTrait::SingleBlock, ::mlir::OpTrait::NoTerminator, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::OpTrait::IsIsolatedFromAbove, ::circt::NonProceduralOp, ::circt::ProceduralRegion> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = TriggeredOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = TriggeredOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_trigger = 0;
  static constexpr int odsIndex_inputs = 1;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("event")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getEventAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getEventAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("hw.triggered");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::IntegerType> getTrigger() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::IntegerType>>(*getODSOperands(0).begin());
  }

  ::mlir::Operation::operand_range getInputs() {
    return getODSOperands(1);
  }

  ::mlir::OpOperand &getTriggerMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
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
  circt::hw::EventControlAttr getEventAttr() {
    return ::llvm::cast<circt::hw::EventControlAttr>(getProperties().event);
  }

  circt::hw::EventControl getEvent();
  void setEventAttr(circt::hw::EventControlAttr attr) {
    getProperties().event = attr;
  }

  void setEvent(circt::hw::EventControl attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, EventControlAttr event, Value trigger, ValueRange inputs);
  static TriggeredOp create(::mlir::OpBuilder &builder, ::mlir::Location location, EventControlAttr event, Value trigger, ValueRange inputs);
  static TriggeredOp create(::mlir::ImplicitLocOpBuilder &builder, EventControlAttr event, Value trigger, ValueRange inputs);
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
  Block *getBodyBlock() { return &getBody().front(); }

  // Return the input arguments inside the trigger region.
  ArrayRef<BlockArgument> getInnerInputs() {
    return getBodyBlock()->getArguments();
  }
};

} // namespace circt::hw
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::hw::TriggeredOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::hw::detail::TriggeredOpGenericAdaptorBase::Properties)

namespace circt::hw {


//===----------------------------------------------------------------------===//
// ::circt::hw::TypeScopeOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class TypeScopeOpGenericAdaptorBase {
public:
  struct Properties {
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
  TypeScopeOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("hw.type_scope", odsAttrs.getContext());
  }

  TypeScopeOpGenericAdaptorBase(TypeScopeOp op);

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
  ::mlir::Region &getBody() {
    return *odsRegions[0];
  }

  ::mlir::RegionRange getRegions() {
    return odsRegions;
  }

};

} // namespace detail
template <typename RangeT>
class TypeScopeOpGenericAdaptor : public detail::TypeScopeOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::TypeScopeOpGenericAdaptorBase;
public:
  TypeScopeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  TypeScopeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : TypeScopeOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  TypeScopeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : TypeScopeOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  TypeScopeOpGenericAdaptor(RangeT values, const TypeScopeOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = TypeScopeOp, typename = std::enable_if_t<std::is_same_v<LateInst, TypeScopeOp>>>
  TypeScopeOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class TypeScopeOpAdaptor : public TypeScopeOpGenericAdaptor<::mlir::ValueRange> {
public:
  using TypeScopeOpGenericAdaptor::TypeScopeOpGenericAdaptor;
  TypeScopeOpAdaptor(TypeScopeOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class TypeScopeOp : public ::mlir::Op<TypeScopeOp, ::mlir::OpTrait::OneRegion, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::SingleBlock, ::mlir::OpTrait::NoTerminator, ::mlir::OpTrait::NoRegionArguments, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::circt::emit::Emittable::Trait, ::mlir::SymbolOpInterface::Trait, ::mlir::OpTrait::SymbolTable> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = TypeScopeOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = TypeScopeOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("sym_name")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getSymNameAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getSymNameAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("hw.type_scope");
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
  void setSymNameAttr(::mlir::StringAttr attr) {
    getProperties().sym_name = attr;
  }

  void setSymName(::llvm::StringRef attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::StringAttr sym_name);
  static TypeScopeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::StringAttr sym_name);
  static TypeScopeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::StringAttr sym_name);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name);
  static TypeScopeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name);
  static TypeScopeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::llvm::StringRef sym_name);
  static TypeScopeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::llvm::StringRef sym_name);
  static TypeScopeOp create(::mlir::ImplicitLocOpBuilder &builder, ::llvm::StringRef sym_name);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name);
  static TypeScopeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name);
  static TypeScopeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static TypeScopeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static TypeScopeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static TypeScopeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static TypeScopeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
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
  Block *getBodyBlock() { return &getBody().front(); }
};

} // namespace circt::hw
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::hw::TypeScopeOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::hw::detail::TypeScopeOpGenericAdaptorBase::Properties)

namespace circt::hw {


//===----------------------------------------------------------------------===//
// ::circt::hw::TypedeclOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class TypedeclOpGenericAdaptorBase {
public:
  struct Properties {
    using sym_nameTy = ::mlir::StringAttr;
    sym_nameTy sym_name;

    auto getSymName() const {
      auto &propStorage = this->sym_name;
      return ::llvm::cast<::mlir::StringAttr>(propStorage);
    }
    void setSymName(const ::mlir::StringAttr &propValue) {
      this->sym_name = propValue;
    }
    using typeTy = ::mlir::TypeAttr;
    typeTy type;

    auto getType() const {
      auto &propStorage = this->type;
      return ::llvm::cast<::mlir::TypeAttr>(propStorage);
    }
    void setType(const ::mlir::TypeAttr &propValue) {
      this->type = propValue;
    }
    using verilogNameTy = ::mlir::StringAttr;
    verilogNameTy verilogName;

    auto getVerilogName() const {
      auto &propStorage = this->verilogName;
      return ::llvm::dyn_cast_or_null<::mlir::StringAttr>(propStorage);
    }
    void setVerilogName(const ::mlir::StringAttr &propValue) {
      this->verilogName = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.sym_name == this->sym_name &&
        rhs.type == this->type &&
        rhs.verilogName == this->verilogName &&
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
  TypedeclOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("hw.typedecl", odsAttrs.getContext());
  }

  TypedeclOpGenericAdaptorBase(TypedeclOp op);

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
  ::mlir::TypeAttr getTypeAttr() {
    auto attr = ::llvm::cast<::mlir::TypeAttr>(getProperties().type);
    return attr;
  }

  ::mlir::Type getType();
  ::mlir::StringAttr getVerilogNameAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::StringAttr>(getProperties().verilogName);
    return attr;
  }

  ::std::optional< ::llvm::StringRef > getVerilogName();
};

} // namespace detail
template <typename RangeT>
class TypedeclOpGenericAdaptor : public detail::TypedeclOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::TypedeclOpGenericAdaptorBase;
public:
  TypedeclOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  TypedeclOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : TypedeclOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  TypedeclOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : TypedeclOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  TypedeclOpGenericAdaptor(RangeT values, const TypedeclOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = TypedeclOp, typename = std::enable_if_t<std::is_same_v<LateInst, TypedeclOp>>>
  TypedeclOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class TypedeclOpAdaptor : public TypedeclOpGenericAdaptor<::mlir::ValueRange> {
public:
  using TypedeclOpGenericAdaptor::TypedeclOpGenericAdaptor;
  TypedeclOpAdaptor(TypedeclOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class TypedeclOp : public ::mlir::Op<TypedeclOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::HasParent<TypeScopeOp>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::SymbolOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = TypedeclOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = TypedeclOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("sym_name"), ::llvm::StringRef("type"), ::llvm::StringRef("verilogName")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getSymNameAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getSymNameAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getTypeAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getTypeAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getVerilogNameAttrName() {
    return getAttributeNameForIndex(2);
  }

  static ::mlir::StringAttr getVerilogNameAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 2);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("hw.typedecl");
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
  ::mlir::TypeAttr getTypeAttr() {
    return ::llvm::cast<::mlir::TypeAttr>(getProperties().type);
  }

  ::mlir::Type getType();
  ::mlir::StringAttr getVerilogNameAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::StringAttr>(getProperties().verilogName);
  }

  ::std::optional< ::llvm::StringRef > getVerilogName();
  void setSymNameAttr(::mlir::StringAttr attr) {
    getProperties().sym_name = attr;
  }

  void setSymName(::llvm::StringRef attrValue);
  void setTypeAttr(::mlir::TypeAttr attr) {
    getProperties().type = attr;
  }

  void setType(::mlir::Type attrValue);
  void setVerilogNameAttr(::mlir::StringAttr attr) {
    getProperties().verilogName = attr;
  }

  void setVerilogName(::std::optional<::llvm::StringRef> attrValue);
  ::mlir::Attribute removeVerilogNameAttr() {
      auto attr = getProperties().verilogName;
      getProperties().verilogName = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::StringAttr sym_name, ::mlir::TypeAttr type, /*optional*/::mlir::StringAttr verilogName);
  static TypedeclOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::StringAttr sym_name, ::mlir::TypeAttr type, /*optional*/::mlir::StringAttr verilogName);
  static TypedeclOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::StringAttr sym_name, ::mlir::TypeAttr type, /*optional*/::mlir::StringAttr verilogName);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name, ::mlir::TypeAttr type, /*optional*/::mlir::StringAttr verilogName);
  static TypedeclOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name, ::mlir::TypeAttr type, /*optional*/::mlir::StringAttr verilogName);
  static TypedeclOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name, ::mlir::TypeAttr type, /*optional*/::mlir::StringAttr verilogName);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::llvm::StringRef sym_name, ::mlir::Type type, /*optional*/::mlir::StringAttr verilogName);
  static TypedeclOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::llvm::StringRef sym_name, ::mlir::Type type, /*optional*/::mlir::StringAttr verilogName);
  static TypedeclOp create(::mlir::ImplicitLocOpBuilder &builder, ::llvm::StringRef sym_name, ::mlir::Type type, /*optional*/::mlir::StringAttr verilogName);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name, ::mlir::Type type, /*optional*/::mlir::StringAttr verilogName);
  static TypedeclOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name, ::mlir::Type type, /*optional*/::mlir::StringAttr verilogName);
  static TypedeclOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name, ::mlir::Type type, /*optional*/::mlir::StringAttr verilogName);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static TypedeclOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static TypedeclOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static TypedeclOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static TypedeclOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
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
  StringRef getPreferredName();

  // Returns the type alias type which this typedecl op defines.
  Type getAliasType();
};

} // namespace circt::hw
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::hw::TypedeclOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::hw::detail::TypedeclOpGenericAdaptorBase::Properties)

namespace circt::hw {


//===----------------------------------------------------------------------===//
// ::circt::hw::UnionCreateOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class UnionCreateOpGenericAdaptorBase {
public:
  struct Properties {
    using fieldIndexTy = ::mlir::IntegerAttr;
    fieldIndexTy fieldIndex;

    auto getFieldIndex() const {
      auto &propStorage = this->fieldIndex;
      return ::llvm::cast<::mlir::IntegerAttr>(propStorage);
    }
    void setFieldIndex(const ::mlir::IntegerAttr &propValue) {
      this->fieldIndex = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.fieldIndex == this->fieldIndex &&
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
  UnionCreateOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("hw.union_create", odsAttrs.getContext());
  }

  UnionCreateOpGenericAdaptorBase(UnionCreateOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::IntegerAttr getFieldIndexAttr() {
    auto attr = ::llvm::cast<::mlir::IntegerAttr>(getProperties().fieldIndex);
    return attr;
  }

  uint32_t getFieldIndex();
};

} // namespace detail
template <typename RangeT>
class UnionCreateOpGenericAdaptor : public detail::UnionCreateOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::UnionCreateOpGenericAdaptorBase;
  static constexpr int odsIndex_input = 0;
public:
  UnionCreateOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  UnionCreateOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : UnionCreateOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  UnionCreateOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : UnionCreateOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  UnionCreateOpGenericAdaptor(RangeT values, const UnionCreateOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = UnionCreateOp, typename = std::enable_if_t<std::is_same_v<LateInst, UnionCreateOp>>>
  UnionCreateOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class UnionCreateOpAdaptor : public UnionCreateOpGenericAdaptor<::mlir::ValueRange> {
public:
  using UnionCreateOpGenericAdaptor::UnionCreateOpGenericAdaptor;
  UnionCreateOpAdaptor(UnionCreateOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class UnionCreateOp : public ::mlir::Op<UnionCreateOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::circt::hw::TypeAliasOr<::circt::hw::UnionType>>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = UnionCreateOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = UnionCreateOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_input = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("fieldIndex")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getFieldIndexAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getFieldIndexAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("hw.union_create");
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

  ::mlir::TypedValue<::circt::hw::TypeAliasOr<::circt::hw::UnionType>> getResult() {
    return ::llvm::cast<::mlir::TypedValue<::circt::hw::TypeAliasOr<::circt::hw::UnionType>>>(*getODSResults(0).begin());
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
  ::mlir::IntegerAttr getFieldIndexAttr() {
    return ::llvm::cast<::mlir::IntegerAttr>(getProperties().fieldIndex);
  }

  uint32_t getFieldIndex();
  void setFieldIndexAttr(::mlir::IntegerAttr attr) {
    getProperties().fieldIndex = attr;
  }

  void setFieldIndex(uint32_t attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Type unionType, StringAttr fieldName, Value input);
  static UnionCreateOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Type unionType, StringAttr fieldName, Value input);
  static UnionCreateOp create(::mlir::ImplicitLocOpBuilder &builder, Type unionType, StringAttr fieldName, Value input);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Type unionType, StringRef fieldName, Value input);
  static UnionCreateOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Type unionType, StringRef fieldName, Value input);
  static UnionCreateOp create(::mlir::ImplicitLocOpBuilder &builder, Type unionType, StringRef fieldName, Value input);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::IntegerAttr fieldIndex, ::mlir::Value input);
  static UnionCreateOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::IntegerAttr fieldIndex, ::mlir::Value input);
  static UnionCreateOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::IntegerAttr fieldIndex, ::mlir::Value input);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::IntegerAttr fieldIndex, ::mlir::Value input);
  static UnionCreateOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::IntegerAttr fieldIndex, ::mlir::Value input);
  static UnionCreateOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::IntegerAttr fieldIndex, ::mlir::Value input);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, uint32_t fieldIndex, ::mlir::Value input);
  static UnionCreateOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, uint32_t fieldIndex, ::mlir::Value input);
  static UnionCreateOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, uint32_t fieldIndex, ::mlir::Value input);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, uint32_t fieldIndex, ::mlir::Value input);
  static UnionCreateOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, uint32_t fieldIndex, ::mlir::Value input);
  static UnionCreateOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, uint32_t fieldIndex, ::mlir::Value input);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static UnionCreateOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static UnionCreateOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static UnionCreateOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static UnionCreateOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &p);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static ::llvm::LogicalResult setPropertiesFromParsedAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
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
  /// Return the name attribute of the accessed field.
  StringAttr getFieldNameAttr() {
    UnionType type = getType();
    return type.getElements()[getFieldIndex()].name;
  }

  /// Return the name of the accessed field.
  StringRef getFieldName() {
    return getFieldNameAttr().getValue();
  }
};

} // namespace circt::hw
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::hw::UnionCreateOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::hw::detail::UnionCreateOpGenericAdaptorBase::Properties)

namespace circt::hw {


//===----------------------------------------------------------------------===//
// ::circt::hw::UnionExtractOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class UnionExtractOpGenericAdaptorBase {
public:
  struct Properties {
    using fieldIndexTy = ::mlir::IntegerAttr;
    fieldIndexTy fieldIndex;

    auto getFieldIndex() const {
      auto &propStorage = this->fieldIndex;
      return ::llvm::cast<::mlir::IntegerAttr>(propStorage);
    }
    void setFieldIndex(const ::mlir::IntegerAttr &propValue) {
      this->fieldIndex = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.fieldIndex == this->fieldIndex &&
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
  UnionExtractOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("hw.union_extract", odsAttrs.getContext());
  }

  UnionExtractOpGenericAdaptorBase(UnionExtractOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::IntegerAttr getFieldIndexAttr() {
    auto attr = ::llvm::cast<::mlir::IntegerAttr>(getProperties().fieldIndex);
    return attr;
  }

  uint32_t getFieldIndex();
};

} // namespace detail
template <typename RangeT>
class UnionExtractOpGenericAdaptor : public detail::UnionExtractOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::UnionExtractOpGenericAdaptorBase;
  static constexpr int odsIndex_input = 0;
public:
  UnionExtractOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  UnionExtractOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : UnionExtractOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  UnionExtractOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : UnionExtractOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  UnionExtractOpGenericAdaptor(RangeT values, const UnionExtractOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = UnionExtractOp, typename = std::enable_if_t<std::is_same_v<LateInst, UnionExtractOp>>>
  UnionExtractOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class UnionExtractOpAdaptor : public UnionExtractOpGenericAdaptor<::mlir::ValueRange> {
public:
  using UnionExtractOpGenericAdaptor::UnionExtractOpGenericAdaptor;
  UnionExtractOpAdaptor(UnionExtractOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class UnionExtractOp : public ::mlir::Op<UnionExtractOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::Type>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = UnionExtractOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = UnionExtractOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_input = 0;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::InferTypeOpInterface::Trait<UnionExtractOp>::refineReturnTypes;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("fieldIndex")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getFieldIndexAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getFieldIndexAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("hw.union_extract");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::circt::hw::TypeAliasOr<::circt::hw::UnionType>> getInput() {
    return ::llvm::cast<::mlir::TypedValue<::circt::hw::TypeAliasOr<::circt::hw::UnionType>>>(*getODSOperands(0).begin());
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
  ::mlir::IntegerAttr getFieldIndexAttr() {
    return ::llvm::cast<::mlir::IntegerAttr>(getProperties().fieldIndex);
  }

  uint32_t getFieldIndex();
  void setFieldIndexAttr(::mlir::IntegerAttr attr) {
    getProperties().fieldIndex = attr;
  }

  void setFieldIndex(uint32_t attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value input, StringAttr fieldName);
  static UnionExtractOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value input, StringAttr fieldName);
  static UnionExtractOp create(::mlir::ImplicitLocOpBuilder &builder, Value input, StringAttr fieldName);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value input, StringRef fieldName);
  static UnionExtractOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value input, StringRef fieldName);
  static UnionExtractOp create(::mlir::ImplicitLocOpBuilder &builder, Value input, StringRef fieldName);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value input, ::mlir::IntegerAttr fieldIndex);
  static UnionExtractOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value input, ::mlir::IntegerAttr fieldIndex);
  static UnionExtractOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value input, ::mlir::IntegerAttr fieldIndex);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value input, ::mlir::IntegerAttr fieldIndex);
  static UnionExtractOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value input, ::mlir::IntegerAttr fieldIndex);
  static UnionExtractOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value input, ::mlir::IntegerAttr fieldIndex);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value input, ::mlir::IntegerAttr fieldIndex);
  static UnionExtractOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value input, ::mlir::IntegerAttr fieldIndex);
  static UnionExtractOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value input, ::mlir::IntegerAttr fieldIndex);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value input, uint32_t fieldIndex);
  static UnionExtractOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value input, uint32_t fieldIndex);
  static UnionExtractOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value input, uint32_t fieldIndex);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value input, uint32_t fieldIndex);
  static UnionExtractOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value input, uint32_t fieldIndex);
  static UnionExtractOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value input, uint32_t fieldIndex);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value input, uint32_t fieldIndex);
  static UnionExtractOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value input, uint32_t fieldIndex);
  static UnionExtractOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value input, uint32_t fieldIndex);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static UnionExtractOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static UnionExtractOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static UnionExtractOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static UnionExtractOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static UnionExtractOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static UnionExtractOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static UnionExtractOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static UnionExtractOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &p);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::llvm::LogicalResult canonicalize(UnionExtractOp op, ::mlir::PatternRewriter &rewriter);
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::PropertyRef properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
  static ::llvm::LogicalResult setPropertiesFromParsedAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
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
  /// Return the name attribute of the accessed field.
  StringAttr getFieldNameAttr() {
    UnionType type = getInput().getType();
    return type.getElements()[getFieldIndex()].name;
  }

  /// Return the name of the accessed field.
  StringRef getFieldName() {
    return getFieldNameAttr().getValue();
  }
};

} // namespace circt::hw
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::hw::UnionExtractOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::hw::detail::UnionExtractOpGenericAdaptorBase::Properties)

namespace circt::hw {


//===----------------------------------------------------------------------===//
// ::circt::hw::WireOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class WireOpGenericAdaptorBase {
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
    bool operator==(const Properties &rhs) const {
      return 
        rhs.inner_sym == this->inner_sym &&
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
  WireOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("hw.wire", odsAttrs.getContext());
  }

  WireOpGenericAdaptorBase(WireOp op);

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
  ::circt::hw::InnerSymAttr getInnerSymAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::circt::hw::InnerSymAttr>(getProperties().inner_sym);
    return attr;
  }

  ::std::optional<::circt::hw::InnerSymAttr> getInnerSym();
};

} // namespace detail
template <typename RangeT>
class WireOpGenericAdaptor : public detail::WireOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::WireOpGenericAdaptorBase;
  static constexpr int odsIndex_input = 0;
public:
  WireOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  WireOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : WireOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  WireOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : WireOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  WireOpGenericAdaptor(RangeT values, const WireOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = WireOp, typename = std::enable_if_t<std::is_same_v<LateInst, WireOp>>>
  WireOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class WireOpAdaptor : public WireOpGenericAdaptor<::mlir::ValueRange> {
public:
  using WireOpGenericAdaptor::WireOpGenericAdaptor;
  WireOpAdaptor(WireOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class WireOp : public ::mlir::Op<WireOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::Type>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::OpTrait::SameOperandsAndResultType, ::mlir::OpAsmOpInterface::Trait, ::circt::hw::InnerSymbolOpInterface::Trait, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = WireOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = WireOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_input = 0;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::OpAsmOpInterface::Trait<WireOp>::getAsmBlockArgumentNames;
  using ::mlir::OpAsmOpInterface::Trait<WireOp>::getAsmBlockNames;
  using ::mlir::OpAsmOpInterface::Trait<WireOp>::getDefaultDialect;
  using ::circt::hw::InnerSymbolOpInterface::Trait<WireOp>::getInnerNameAttr;
  using ::circt::hw::InnerSymbolOpInterface::Trait<WireOp>::getInnerName;
  using ::circt::hw::InnerSymbolOpInterface::Trait<WireOp>::setInnerSymbol;
  using ::circt::hw::InnerSymbolOpInterface::Trait<WireOp>::setInnerSymbolAttr;
  using ::circt::hw::InnerSymbolOpInterface::Trait<WireOp>::getInnerRef;
  using ::circt::hw::InnerSymbolOpInterface::Trait<WireOp>::getInnerSymAttr;
  using ::circt::hw::InnerSymbolOpInterface::Trait<WireOp>::supportsPerFieldSymbols;
  using ::circt::hw::InnerSymbolOpInterface::Trait<WireOp>::getTargetResult;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("inner_sym"), ::llvm::StringRef("name")};
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

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("hw.wire");
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

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, mlir::Value input, const StringAttrOrRef &name = {}, hw::InnerSymAttr innerSym = {});
  static WireOp create(::mlir::OpBuilder &builder, ::mlir::Location location, mlir::Value input, const StringAttrOrRef &name = {}, hw::InnerSymAttr innerSym = {});
  static WireOp create(::mlir::ImplicitLocOpBuilder &builder, mlir::Value input, const StringAttrOrRef &name = {}, hw::InnerSymAttr innerSym = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value input, /*optional*/::mlir::StringAttr name, /*optional*/::circt::hw::InnerSymAttr inner_sym);
  static WireOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value input, /*optional*/::mlir::StringAttr name, /*optional*/::circt::hw::InnerSymAttr inner_sym);
  static WireOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value input, /*optional*/::mlir::StringAttr name, /*optional*/::circt::hw::InnerSymAttr inner_sym);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value input, /*optional*/::mlir::StringAttr name, /*optional*/::circt::hw::InnerSymAttr inner_sym);
  static WireOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value input, /*optional*/::mlir::StringAttr name, /*optional*/::circt::hw::InnerSymAttr inner_sym);
  static WireOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value input, /*optional*/::mlir::StringAttr name, /*optional*/::circt::hw::InnerSymAttr inner_sym);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value input, /*optional*/::mlir::StringAttr name, /*optional*/::circt::hw::InnerSymAttr inner_sym);
  static WireOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value input, /*optional*/::mlir::StringAttr name, /*optional*/::circt::hw::InnerSymAttr inner_sym);
  static WireOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value input, /*optional*/::mlir::StringAttr name, /*optional*/::circt::hw::InnerSymAttr inner_sym);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static WireOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static WireOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static WireOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static WireOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static WireOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static WireOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static WireOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static WireOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::llvm::LogicalResult canonicalize(WireOp op, ::mlir::PatternRewriter &rewriter);
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
  ::mlir::OpFoldResult fold(FoldAdaptor adaptor);
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::PropertyRef properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
  static std::optional<size_t> getTargetResultIndex();
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

} // namespace circt::hw
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::hw::WireOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::hw::detail::WireOpGenericAdaptorBase::Properties)


#endif // GET_OP_CLASSES

