/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Op Declarations                                                            *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: Debug.td                                                             *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace circt::debug {

/// Aggregate values into an array
/// Creates an array aggregate from a list of values. The first operand is
/// placed at array index 0. The last operand is placed at the highest array
/// index. The `dbg.array` operation allows for array-like source language
/// values to be captured in the debug info. This includes arrays, or in the
/// case of SystemVerilog, packed and unpacked arrays, lists, sequences, queues,
/// FIFOs, channels, and vectors.
/// 
/// See the rationale for examples and details.
class ArrayOp;

} // namespace circt::debug
namespace circt::debug {

/// Interpret an integer value as an enumeration
/// Wraps an integer value as a tag-only (C-style) enumeration, producing an
/// enum-typed debug value. Behaves like a cast: the `value` operand is the raw
/// integer tag, and `variantsMap` provides the `name -> tag` mapping consumers
/// use to reconstruct the named variant. The result is an ordinary value that
/// can be embedded in `dbg.variable`, `dbg.struct`, and `dbg.array` just like
/// any other debug value, so enum tracking needs no separate definition op,
/// scope, or subfield linkage.
/// 
/// `enumTypeName` is the source-language type name; the optional `fqn` is the
/// fully-qualified name used as the stable type-pool key. Consumers use it to
/// dedup identical enums that appear at many use sites or across modules.
/// 
/// This models tag-only enums: `variantsMap` is keyed by variant name with
/// `IntegerAttr` tags and has no slot for per-variant payload types, so
/// data-carrying variants are out of scope.
class EnumOp;

} // namespace circt::debug
namespace circt::debug {

/// Define a scope for debug values
/// Creates an additional level of hierarchy in the DI, a "scope", which can be
/// used to group variables and other scopes.
/// 
/// Operations such as `hw.module` introduce an implicit scope. All debug
/// operations within a module are added to that implicit scope, unless they
/// have an explicit `scope` operand. Providing an explicit scope can be used to
/// represent inlined modules.
/// 
/// Scopes in DI do not necessarily have to correspond to levels of a module
/// hierarchy. They can also be used to model things like control flow scopes,
/// call stacks, and other source-language concepts.
/// 
/// The `scope` operand of any debug dialect operation must be defined locally
/// by a `dbg.scope` operation. It cannot be a block argument. (This is intended
/// as a temporary restriction, to be lifted in the future.)
class ScopeOp;

} // namespace circt::debug
namespace circt::debug {

/// Aggregate values into a struct
/// Creates a struct aggregate from a list of names and values. The `dbg.struct`
/// operation allows for struct-like source language values to be captured in
/// the debug info. This includes structs, unions, bidirectional bundles,
/// interfaces, classes, and other similar structures.
/// 
/// See the rationale for examples and details.
class StructOp;

} // namespace circt::debug
namespace circt::debug {

/// Attach source-language metadata to a value
/// Annotates an SSA value with additional source-language information: the
/// source type name, its constructor parameters, and a dedicated location.
/// The result is a metadata wrapper accepted wherever other debug operations
/// accept plain values (`dbg.variable`, `dbg.struct`, `dbg.array`); consumers
/// unwrap it to reach the underlying value. Keeping the metadata on a
/// separate wrapper keeps `dbg.variable` and the aggregate ops orthogonal to
/// source-language type information.
/// 
/// An enum-typed value embeds a `dbg.enum`, so no enum linkage is carried on
/// the wrapper itself. Freshly-created ops with no users are tolerated by
/// the verifier to accommodate construction patterns; any surviving user
/// must be a debug-dialect op.
class ValueOp;

} // namespace circt::debug
namespace circt::debug {

/// A named value to be captured in debug info
/// Marks a value to be tracked in DI under the given name. The `dbg.variable`
/// operation is useful to represent named values in a source language. For
/// example, ports, constants, parameters, variables, nodes, or name aliases can
/// all be represented as a variable. In combination with `dbg.array` and
/// `dbg.struct`, complex aggregate source language values can be described and
/// reconstituted from individual IR values. The `dbg.variable` operation acts
/// as a tracker that follows the evolution of its assigned value throughout the
/// compiler's pass pipelines. The debug info analysis uses this op to populate
/// a module's scope with named source language values, and to establish how
/// these source language values can be reconstituted from the actual IR values
/// present at the end of compilation.
/// 
/// An enum-typed variable embeds a `dbg.enum` value, which carries the named
/// variants. Source-language type information is not carried on the variable
/// itself; wrap the value in a `dbg.value` to attach it.
/// 
/// See the rationale for examples and details. See the `dbg.scope` operation
/// for additional details on how to use the `scope` operand.
class VariableOp;

} // namespace circt::debug
#ifdef GET_OP_CLASSES
#undef GET_OP_CLASSES

namespace circt::debug {


//===----------------------------------------------------------------------===//
// circt::debug::ArrayOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ArrayOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  ArrayOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("dbg.array", odsAttrs.getContext());
  }

  ArrayOpGenericAdaptorBase(ArrayOp op);

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
class ArrayOpGenericAdaptor : public detail::ArrayOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ArrayOpGenericAdaptorBase;
  static constexpr int odsIndex_elements = 0;
public:
  ArrayOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ArrayOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : ArrayOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ArrayOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ArrayOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ArrayOpGenericAdaptor(RangeT values, const ArrayOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ArrayOp, typename = std::enable_if_t<std::is_same_v<LateInst, ArrayOp>>>
  ArrayOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getElements() {
    return getODSOperands(0);
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class ArrayOpAdaptor : public ArrayOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ArrayOpGenericAdaptor::ArrayOpGenericAdaptor;
  ArrayOpAdaptor(ArrayOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ArrayOp : public ::mlir::Op<ArrayOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<circt::debug::ArrayType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::OpInvariants, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::OpTrait::SameTypeOperands, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ArrayOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ArrayOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_elements = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("dbg.array");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::operand_range getElements() {
    return getODSOperands(0);
  }

  ::mlir::MutableOperandRange getElementsMutable();
  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<circt::debug::ArrayType> getResult() {
    return ::llvm::cast<::mlir::TypedValue<circt::debug::ArrayType>>(*getODSResults(0).begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::ValueRange elements);
  static ArrayOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::ValueRange elements);
  static ArrayOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::ValueRange elements);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ArrayOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ArrayOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ArrayOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ArrayOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ArrayOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ArrayOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ArrayOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ArrayOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &p);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::PropertyRef properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
  static ::llvm::LogicalResult setPropertiesFromParsedAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
};

} // namespace circt::debug
MLIR_DECLARE_EXPLICIT_TYPE_ID(circt::debug::ArrayOp)

namespace circt::debug {


//===----------------------------------------------------------------------===//
// circt::debug::EnumOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class EnumOpGenericAdaptorBase {
public:
  struct Properties {
    using enumTypeNameTy = ::mlir::StringAttr;
    enumTypeNameTy enumTypeName;

    auto getEnumTypeName() const {
      auto &propStorage = this->enumTypeName;
      return ::llvm::cast<::mlir::StringAttr>(propStorage);
    }
    void setEnumTypeName(const ::mlir::StringAttr &propValue) {
      this->enumTypeName = propValue;
    }
    using fqnTy = ::mlir::StringAttr;
    fqnTy fqn;

    auto getFqn() const {
      auto &propStorage = this->fqn;
      return ::llvm::dyn_cast_or_null<::mlir::StringAttr>(propStorage);
    }
    void setFqn(const ::mlir::StringAttr &propValue) {
      this->fqn = propValue;
    }
    using variantsMapTy = ::mlir::DictionaryAttr;
    variantsMapTy variantsMap;

    auto getVariantsMap() const {
      auto &propStorage = this->variantsMap;
      return ::llvm::cast<::mlir::DictionaryAttr>(propStorage);
    }
    void setVariantsMap(const ::mlir::DictionaryAttr &propValue) {
      this->variantsMap = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.enumTypeName == this->enumTypeName &&
        rhs.fqn == this->fqn &&
        rhs.variantsMap == this->variantsMap &&
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
  EnumOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("dbg.enum", odsAttrs.getContext());
  }

  EnumOpGenericAdaptorBase(EnumOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::StringAttr getEnumTypeNameAttr() {
    auto attr = ::llvm::cast<::mlir::StringAttr>(getProperties().enumTypeName);
    return attr;
  }

  ::llvm::StringRef getEnumTypeName();
  ::mlir::DictionaryAttr getVariantsMapAttr() {
    auto attr = ::llvm::cast<::mlir::DictionaryAttr>(getProperties().variantsMap);
    return attr;
  }

  ::mlir::DictionaryAttr getVariantsMap();
  ::mlir::StringAttr getFqnAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::StringAttr>(getProperties().fqn);
    return attr;
  }

  ::std::optional< ::llvm::StringRef > getFqn();
};

} // namespace detail
template <typename RangeT>
class EnumOpGenericAdaptor : public detail::EnumOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::EnumOpGenericAdaptorBase;
  static constexpr int odsIndex_value = 0;
public:
  EnumOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  EnumOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : EnumOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  EnumOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : EnumOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  EnumOpGenericAdaptor(RangeT values, const EnumOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = EnumOp, typename = std::enable_if_t<std::is_same_v<LateInst, EnumOp>>>
  EnumOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getValue() {
    return (*getODSOperands(0).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class EnumOpAdaptor : public EnumOpGenericAdaptor<::mlir::ValueRange> {
public:
  using EnumOpGenericAdaptor::EnumOpGenericAdaptor;
  EnumOpAdaptor(EnumOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class EnumOp : public ::mlir::Op<EnumOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<circt::debug::EnumType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = EnumOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = EnumOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_value = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("enumTypeName"), ::llvm::StringRef("fqn"), ::llvm::StringRef("variantsMap")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getEnumTypeNameAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getEnumTypeNameAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getFqnAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getFqnAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getVariantsMapAttrName() {
    return getAttributeNameForIndex(2);
  }

  static ::mlir::StringAttr getVariantsMapAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 2);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("dbg.enum");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::Type> getValue() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(0).begin());
  }

  ::mlir::OpOperand &getValueMutable() {
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

  ::mlir::TypedValue<circt::debug::EnumType> getResult() {
    return ::llvm::cast<::mlir::TypedValue<circt::debug::EnumType>>(*getODSResults(0).begin());
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
  ::mlir::StringAttr getEnumTypeNameAttr() {
    return ::llvm::cast<::mlir::StringAttr>(getProperties().enumTypeName);
  }

  ::llvm::StringRef getEnumTypeName();
  ::mlir::DictionaryAttr getVariantsMapAttr() {
    return ::llvm::cast<::mlir::DictionaryAttr>(getProperties().variantsMap);
  }

  ::mlir::DictionaryAttr getVariantsMap();
  ::mlir::StringAttr getFqnAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::StringAttr>(getProperties().fqn);
  }

  ::std::optional< ::llvm::StringRef > getFqn();
  void setEnumTypeNameAttr(::mlir::StringAttr attr) {
    getProperties().enumTypeName = attr;
  }

  void setEnumTypeName(::llvm::StringRef attrValue);
  void setVariantsMapAttr(::mlir::DictionaryAttr attr) {
    getProperties().variantsMap = attr;
  }

  void setFqnAttr(::mlir::StringAttr attr) {
    getProperties().fqn = attr;
  }

  void setFqn(::std::optional<::llvm::StringRef> attrValue);
  ::mlir::Attribute removeFqnAttr() {
      auto attr = getProperties().fqn;
      getProperties().fqn = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value value, ::mlir::StringAttr enumTypeName, ::mlir::DictionaryAttr variantsMap, /*optional*/::mlir::StringAttr fqn);
  static EnumOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value value, ::mlir::StringAttr enumTypeName, ::mlir::DictionaryAttr variantsMap, /*optional*/::mlir::StringAttr fqn);
  static EnumOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value value, ::mlir::StringAttr enumTypeName, ::mlir::DictionaryAttr variantsMap, /*optional*/::mlir::StringAttr fqn);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value value, ::mlir::StringAttr enumTypeName, ::mlir::DictionaryAttr variantsMap, /*optional*/::mlir::StringAttr fqn);
  static EnumOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value value, ::mlir::StringAttr enumTypeName, ::mlir::DictionaryAttr variantsMap, /*optional*/::mlir::StringAttr fqn);
  static EnumOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value value, ::mlir::StringAttr enumTypeName, ::mlir::DictionaryAttr variantsMap, /*optional*/::mlir::StringAttr fqn);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value value, ::mlir::StringAttr enumTypeName, ::mlir::DictionaryAttr variantsMap, /*optional*/::mlir::StringAttr fqn);
  static EnumOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value value, ::mlir::StringAttr enumTypeName, ::mlir::DictionaryAttr variantsMap, /*optional*/::mlir::StringAttr fqn);
  static EnumOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value value, ::mlir::StringAttr enumTypeName, ::mlir::DictionaryAttr variantsMap, /*optional*/::mlir::StringAttr fqn);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value value, ::llvm::StringRef enumTypeName, ::mlir::DictionaryAttr variantsMap, /*optional*/::mlir::StringAttr fqn);
  static EnumOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value value, ::llvm::StringRef enumTypeName, ::mlir::DictionaryAttr variantsMap, /*optional*/::mlir::StringAttr fqn);
  static EnumOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value value, ::llvm::StringRef enumTypeName, ::mlir::DictionaryAttr variantsMap, /*optional*/::mlir::StringAttr fqn);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value value, ::llvm::StringRef enumTypeName, ::mlir::DictionaryAttr variantsMap, /*optional*/::mlir::StringAttr fqn);
  static EnumOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value value, ::llvm::StringRef enumTypeName, ::mlir::DictionaryAttr variantsMap, /*optional*/::mlir::StringAttr fqn);
  static EnumOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value value, ::llvm::StringRef enumTypeName, ::mlir::DictionaryAttr variantsMap, /*optional*/::mlir::StringAttr fqn);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value value, ::llvm::StringRef enumTypeName, ::mlir::DictionaryAttr variantsMap, /*optional*/::mlir::StringAttr fqn);
  static EnumOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value value, ::llvm::StringRef enumTypeName, ::mlir::DictionaryAttr variantsMap, /*optional*/::mlir::StringAttr fqn);
  static EnumOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value value, ::llvm::StringRef enumTypeName, ::mlir::DictionaryAttr variantsMap, /*optional*/::mlir::StringAttr fqn);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static EnumOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static EnumOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static EnumOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static EnumOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static EnumOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static EnumOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static EnumOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static EnumOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::PropertyRef properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
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

} // namespace circt::debug
MLIR_DECLARE_EXPLICIT_TYPE_ID(circt::debug::EnumOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(circt::debug::detail::EnumOpGenericAdaptorBase::Properties)

namespace circt::debug {


//===----------------------------------------------------------------------===//
// circt::debug::ScopeOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ScopeOpGenericAdaptorBase {
public:
  struct Properties {
    using instanceNameTy = ::mlir::StringAttr;
    instanceNameTy instanceName;

    auto getInstanceName() const {
      auto &propStorage = this->instanceName;
      return ::llvm::cast<::mlir::StringAttr>(propStorage);
    }
    void setInstanceName(const ::mlir::StringAttr &propValue) {
      this->instanceName = propValue;
    }
    using moduleNameTy = ::mlir::StringAttr;
    moduleNameTy moduleName;

    auto getModuleName() const {
      auto &propStorage = this->moduleName;
      return ::llvm::cast<::mlir::StringAttr>(propStorage);
    }
    void setModuleName(const ::mlir::StringAttr &propValue) {
      this->moduleName = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.instanceName == this->instanceName &&
        rhs.moduleName == this->moduleName &&
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
  ScopeOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("dbg.scope", odsAttrs.getContext());
  }

  ScopeOpGenericAdaptorBase(ScopeOp op);

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
  ::mlir::StringAttr getModuleNameAttr() {
    auto attr = ::llvm::cast<::mlir::StringAttr>(getProperties().moduleName);
    return attr;
  }

  ::llvm::StringRef getModuleName();
};

} // namespace detail
template <typename RangeT>
class ScopeOpGenericAdaptor : public detail::ScopeOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ScopeOpGenericAdaptorBase;
  static constexpr int odsIndex_scope = 0;
public:
  ScopeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ScopeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : ScopeOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ScopeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ScopeOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ScopeOpGenericAdaptor(RangeT values, const ScopeOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ScopeOp, typename = std::enable_if_t<std::is_same_v<LateInst, ScopeOp>>>
  ScopeOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getScope() {
    auto operands = getODSOperands(0);
    return operands.empty() ? ValueT{} : (*operands.begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class ScopeOpAdaptor : public ScopeOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ScopeOpGenericAdaptor::ScopeOpGenericAdaptor;
  ScopeOpAdaptor(ScopeOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ScopeOp : public ::mlir::Op<ScopeOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<circt::debug::ScopeType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ScopeOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ScopeOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_scope = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("instanceName"), ::llvm::StringRef("moduleName")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getInstanceNameAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getInstanceNameAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getModuleNameAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getModuleNameAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("dbg.scope");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<circt::debug::ScopeType> getScope() {
    auto operands = getODSOperands(0);
    return operands.empty() ? ::mlir::TypedValue<circt::debug::ScopeType>{} : ::llvm::cast<::mlir::TypedValue<circt::debug::ScopeType>>(*operands.begin());
  }

  ::mlir::MutableOperandRange getScopeMutable();
  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<circt::debug::ScopeType> getResult() {
    return ::llvm::cast<::mlir::TypedValue<circt::debug::ScopeType>>(*getODSResults(0).begin());
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
  ::mlir::StringAttr getModuleNameAttr() {
    return ::llvm::cast<::mlir::StringAttr>(getProperties().moduleName);
  }

  ::llvm::StringRef getModuleName();
  void setInstanceNameAttr(::mlir::StringAttr attr) {
    getProperties().instanceName = attr;
  }

  void setInstanceName(::llvm::StringRef attrValue);
  void setModuleNameAttr(::mlir::StringAttr attr) {
    getProperties().moduleName = attr;
  }

  void setModuleName(::llvm::StringRef attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::StringAttr instanceName, ::mlir::StringAttr moduleName, /*optional*/::mlir::Value scope);
  static ScopeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::StringAttr instanceName, ::mlir::StringAttr moduleName, /*optional*/::mlir::Value scope);
  static ScopeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::StringAttr instanceName, ::mlir::StringAttr moduleName, /*optional*/::mlir::Value scope);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::StringAttr instanceName, ::mlir::StringAttr moduleName, /*optional*/::mlir::Value scope);
  static ScopeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::StringAttr instanceName, ::mlir::StringAttr moduleName, /*optional*/::mlir::Value scope);
  static ScopeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::StringAttr instanceName, ::mlir::StringAttr moduleName, /*optional*/::mlir::Value scope);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::StringAttr instanceName, ::mlir::StringAttr moduleName, /*optional*/::mlir::Value scope);
  static ScopeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::StringAttr instanceName, ::mlir::StringAttr moduleName, /*optional*/::mlir::Value scope);
  static ScopeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::StringAttr instanceName, ::mlir::StringAttr moduleName, /*optional*/::mlir::Value scope);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::llvm::StringRef instanceName, ::llvm::StringRef moduleName, /*optional*/::mlir::Value scope);
  static ScopeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::llvm::StringRef instanceName, ::llvm::StringRef moduleName, /*optional*/::mlir::Value scope);
  static ScopeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::llvm::StringRef instanceName, ::llvm::StringRef moduleName, /*optional*/::mlir::Value scope);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::llvm::StringRef instanceName, ::llvm::StringRef moduleName, /*optional*/::mlir::Value scope);
  static ScopeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::llvm::StringRef instanceName, ::llvm::StringRef moduleName, /*optional*/::mlir::Value scope);
  static ScopeOp create(::mlir::ImplicitLocOpBuilder &builder, ::llvm::StringRef instanceName, ::llvm::StringRef moduleName, /*optional*/::mlir::Value scope);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::llvm::StringRef instanceName, ::llvm::StringRef moduleName, /*optional*/::mlir::Value scope);
  static ScopeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::llvm::StringRef instanceName, ::llvm::StringRef moduleName, /*optional*/::mlir::Value scope);
  static ScopeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::llvm::StringRef instanceName, ::llvm::StringRef moduleName, /*optional*/::mlir::Value scope);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ScopeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ScopeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ScopeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ScopeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ScopeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ScopeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ScopeOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ScopeOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::PropertyRef properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
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

} // namespace circt::debug
MLIR_DECLARE_EXPLICIT_TYPE_ID(circt::debug::ScopeOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(circt::debug::detail::ScopeOpGenericAdaptorBase::Properties)

namespace circt::debug {


//===----------------------------------------------------------------------===//
// circt::debug::StructOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class StructOpGenericAdaptorBase {
public:
  struct Properties {
    using namesTy = ::mlir::ArrayAttr;
    namesTy names;

    auto getNames() const {
      auto &propStorage = this->names;
      return ::llvm::cast<::mlir::ArrayAttr>(propStorage);
    }
    void setNames(const ::mlir::ArrayAttr &propValue) {
      this->names = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.names == this->names &&
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
  StructOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("dbg.struct", odsAttrs.getContext());
  }

  StructOpGenericAdaptorBase(StructOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::ArrayAttr getNamesAttr() {
    auto attr = ::llvm::cast<::mlir::ArrayAttr>(getProperties().names);
    return attr;
  }

  ::mlir::ArrayAttr getNames();
};

} // namespace detail
template <typename RangeT>
class StructOpGenericAdaptor : public detail::StructOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::StructOpGenericAdaptorBase;
  static constexpr int odsIndex_fields = 0;
public:
  StructOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  StructOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : StructOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  StructOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : StructOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  StructOpGenericAdaptor(RangeT values, const StructOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = StructOp, typename = std::enable_if_t<std::is_same_v<LateInst, StructOp>>>
  StructOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getFields() {
    return getODSOperands(0);
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class StructOpAdaptor : public StructOpGenericAdaptor<::mlir::ValueRange> {
public:
  using StructOpGenericAdaptor::StructOpGenericAdaptor;
  StructOpAdaptor(StructOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class StructOp : public ::mlir::Op<StructOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<circt::debug::StructType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = StructOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = StructOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_fields = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("names")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getNamesAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getNamesAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("dbg.struct");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::operand_range getFields() {
    return getODSOperands(0);
  }

  ::mlir::MutableOperandRange getFieldsMutable();
  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<circt::debug::StructType> getResult() {
    return ::llvm::cast<::mlir::TypedValue<circt::debug::StructType>>(*getODSResults(0).begin());
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
  ::mlir::ArrayAttr getNamesAttr() {
    return ::llvm::cast<::mlir::ArrayAttr>(getProperties().names);
  }

  ::mlir::ArrayAttr getNames();
  void setNamesAttr(::mlir::ArrayAttr attr) {
    getProperties().names = attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::ValueRange fields, ::mlir::ArrayAttr names);
  static StructOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::ValueRange fields, ::mlir::ArrayAttr names);
  static StructOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::ValueRange fields, ::mlir::ArrayAttr names);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange fields, ::mlir::ArrayAttr names);
  static StructOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange fields, ::mlir::ArrayAttr names);
  static StructOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange fields, ::mlir::ArrayAttr names);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange fields, ::mlir::ArrayAttr names);
  static StructOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange fields, ::mlir::ArrayAttr names);
  static StructOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange fields, ::mlir::ArrayAttr names);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static StructOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static StructOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static StructOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static StructOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static StructOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static StructOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static StructOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static StructOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &p);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
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
};

} // namespace circt::debug
MLIR_DECLARE_EXPLICIT_TYPE_ID(circt::debug::StructOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(circt::debug::detail::StructOpGenericAdaptorBase::Properties)

namespace circt::debug {


//===----------------------------------------------------------------------===//
// circt::debug::ValueOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ValueOpGenericAdaptorBase {
public:
  struct Properties {
    using paramsTy = ::mlir::ArrayAttr;
    paramsTy params;

    auto getParams() const {
      auto &propStorage = this->params;
      return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(propStorage);
    }
    void setParams(const ::mlir::ArrayAttr &propValue) {
      this->params = propValue;
    }
    using typeNameTy = ::mlir::StringAttr;
    typeNameTy typeName;

    auto getTypeName() const {
      auto &propStorage = this->typeName;
      return ::llvm::dyn_cast_or_null<::mlir::StringAttr>(propStorage);
    }
    void setTypeName(const ::mlir::StringAttr &propValue) {
      this->typeName = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.params == this->params &&
        rhs.typeName == this->typeName &&
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
  ValueOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("dbg.value", odsAttrs.getContext());
  }

  ValueOpGenericAdaptorBase(ValueOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::StringAttr getTypeNameAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::StringAttr>(getProperties().typeName);
    return attr;
  }

  ::std::optional< ::llvm::StringRef > getTypeName();
  ::mlir::ArrayAttr getParamsAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().params);
    return attr;
  }

  ::std::optional< ::mlir::ArrayAttr > getParams();
};

} // namespace detail
template <typename RangeT>
class ValueOpGenericAdaptor : public detail::ValueOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ValueOpGenericAdaptorBase;
  static constexpr int odsIndex_value = 0;
public:
  ValueOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ValueOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : ValueOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ValueOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ValueOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ValueOpGenericAdaptor(RangeT values, const ValueOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ValueOp, typename = std::enable_if_t<std::is_same_v<LateInst, ValueOp>>>
  ValueOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getValue() {
    return (*getODSOperands(0).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class ValueOpAdaptor : public ValueOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ValueOpGenericAdaptor::ValueOpGenericAdaptor;
  ValueOpAdaptor(ValueOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ValueOp : public ::mlir::Op<ValueOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<circt::debug::ValueType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ValueOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ValueOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_value = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("params"), ::llvm::StringRef("typeName")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getParamsAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getParamsAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getTypeNameAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getTypeNameAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("dbg.value");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::Type> getValue() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(0).begin());
  }

  ::mlir::OpOperand &getValueMutable() {
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

  ::mlir::TypedValue<circt::debug::ValueType> getResult() {
    return ::llvm::cast<::mlir::TypedValue<circt::debug::ValueType>>(*getODSResults(0).begin());
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
  ::mlir::StringAttr getTypeNameAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::StringAttr>(getProperties().typeName);
  }

  ::std::optional< ::llvm::StringRef > getTypeName();
  ::mlir::ArrayAttr getParamsAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().params);
  }

  ::std::optional< ::mlir::ArrayAttr > getParams();
  void setTypeNameAttr(::mlir::StringAttr attr) {
    getProperties().typeName = attr;
  }

  void setTypeName(::std::optional<::llvm::StringRef> attrValue);
  void setParamsAttr(::mlir::ArrayAttr attr) {
    getProperties().params = attr;
  }

  ::mlir::Attribute removeTypeNameAttr() {
      auto attr = getProperties().typeName;
      getProperties().typeName = {};
      return attr;
  }

  ::mlir::Attribute removeParamsAttr() {
      auto attr = getProperties().params;
      getProperties().params = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value value, /*optional*/::mlir::StringAttr typeName, /*optional*/::mlir::ArrayAttr params);
  static ValueOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value value, /*optional*/::mlir::StringAttr typeName, /*optional*/::mlir::ArrayAttr params);
  static ValueOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value value, /*optional*/::mlir::StringAttr typeName, /*optional*/::mlir::ArrayAttr params);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value value, /*optional*/::mlir::StringAttr typeName, /*optional*/::mlir::ArrayAttr params);
  static ValueOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value value, /*optional*/::mlir::StringAttr typeName, /*optional*/::mlir::ArrayAttr params);
  static ValueOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value value, /*optional*/::mlir::StringAttr typeName, /*optional*/::mlir::ArrayAttr params);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value value, /*optional*/::mlir::StringAttr typeName, /*optional*/::mlir::ArrayAttr params);
  static ValueOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value value, /*optional*/::mlir::StringAttr typeName, /*optional*/::mlir::ArrayAttr params);
  static ValueOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value value, /*optional*/::mlir::StringAttr typeName, /*optional*/::mlir::ArrayAttr params);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ValueOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ValueOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ValueOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ValueOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ValueOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ValueOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ValueOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ValueOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::PropertyRef properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
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

} // namespace circt::debug
MLIR_DECLARE_EXPLICIT_TYPE_ID(circt::debug::ValueOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(circt::debug::detail::ValueOpGenericAdaptorBase::Properties)

namespace circt::debug {


//===----------------------------------------------------------------------===//
// circt::debug::VariableOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class VariableOpGenericAdaptorBase {
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
  VariableOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("dbg.variable", odsAttrs.getContext());
  }

  VariableOpGenericAdaptorBase(VariableOp op);

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
};

} // namespace detail
template <typename RangeT>
class VariableOpGenericAdaptor : public detail::VariableOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::VariableOpGenericAdaptorBase;
  static constexpr int odsIndex_value = 0;
  static constexpr int odsIndex_scope = 1;
public:
  VariableOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  VariableOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : VariableOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  VariableOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : VariableOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  VariableOpGenericAdaptor(RangeT values, const VariableOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = VariableOp, typename = std::enable_if_t<std::is_same_v<LateInst, VariableOp>>>
  VariableOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getValue() {
    return (*getODSOperands(0).begin());
  }

  ValueT getScope() {
    auto operands = getODSOperands(1);
    return operands.empty() ? ValueT{} : (*operands.begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class VariableOpAdaptor : public VariableOpGenericAdaptor<::mlir::ValueRange> {
public:
  using VariableOpGenericAdaptor::VariableOpGenericAdaptor;
  VariableOpAdaptor(VariableOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class VariableOp : public ::mlir::Op<VariableOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<1>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = VariableOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = VariableOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_value = 0;
  static constexpr int odsIndex_scope = 1;
  using Properties = FoldAdaptor::Properties;
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
    return ::llvm::StringLiteral("dbg.variable");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::Type> getValue() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<circt::debug::ScopeType> getScope() {
    auto operands = getODSOperands(1);
    return operands.empty() ? ::mlir::TypedValue<circt::debug::ScopeType>{} : ::llvm::cast<::mlir::TypedValue<circt::debug::ScopeType>>(*operands.begin());
  }

  ::mlir::OpOperand &getValueMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::MutableOperandRange getScopeMutable();
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
  ::mlir::StringAttr getNameAttr() {
    return ::llvm::cast<::mlir::StringAttr>(getProperties().name);
  }

  ::llvm::StringRef getName();
  void setNameAttr(::mlir::StringAttr attr) {
    getProperties().name = attr;
  }

  void setName(::llvm::StringRef attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::StringAttr name, ::mlir::Value value, /*optional*/::mlir::Value scope);
  static VariableOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::StringAttr name, ::mlir::Value value, /*optional*/::mlir::Value scope);
  static VariableOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::StringAttr name, ::mlir::Value value, /*optional*/::mlir::Value scope);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::StringAttr name, ::mlir::Value value, /*optional*/::mlir::Value scope);
  static VariableOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::StringAttr name, ::mlir::Value value, /*optional*/::mlir::Value scope);
  static VariableOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::StringAttr name, ::mlir::Value value, /*optional*/::mlir::Value scope);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::llvm::StringRef name, ::mlir::Value value, /*optional*/::mlir::Value scope);
  static VariableOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::llvm::StringRef name, ::mlir::Value value, /*optional*/::mlir::Value scope);
  static VariableOp create(::mlir::ImplicitLocOpBuilder &builder, ::llvm::StringRef name, ::mlir::Value value, /*optional*/::mlir::Value scope);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::llvm::StringRef name, ::mlir::Value value, /*optional*/::mlir::Value scope);
  static VariableOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::llvm::StringRef name, ::mlir::Value value, /*optional*/::mlir::Value scope);
  static VariableOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::llvm::StringRef name, ::mlir::Value value, /*optional*/::mlir::Value scope);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static VariableOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static VariableOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static VariableOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static VariableOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
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

} // namespace circt::debug
MLIR_DECLARE_EXPLICIT_TYPE_ID(circt::debug::VariableOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(circt::debug::detail::VariableOpGenericAdaptorBase::Properties)


#endif // GET_OP_CLASSES

