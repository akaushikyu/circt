/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Op Declarations                                                            *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: SystemC.td                                                           *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace circt::systemc {

/// A C++ assignment.
/// Assigns one SSA value to another. Note that there is no notion of lvalues
/// and rvalues. This means that one can assign to a value that is the result
/// of, e.g., an addition, which is not allowed in C++. It is the responsibility
/// of the user and the implementor of a lowering pass that creates this
/// operation to make sure that the operands are valid according to C++
/// semantics. Rationale for that: implementing these constraints would add
/// quite some complexity, but still does not guarantee that the assignment
/// is valid because we also make use of non-verifyable verbatim types, etc.
class AssignOp;

} // namespace circt::systemc
namespace circt::systemc {

/// Binds a port of a module instance to a channel.
/// The ports of a submodule have to be bound to channels in a module further
/// up in the instance hierarchy (as opposed to `sc_export` where the channel
/// has to reside in the same module or a submodule). Therefore, a port can be
/// bound to either a signal declared by the `systemc.signal` operation or to
/// a port with matching direction (and thus bound to a channel further up in
/// the hierarchy).
/// More information on ports can be found in IEEE 1666-2011 §5.12.,
/// in particular IEEE 1666-2011 §5.12.7. is about port binding.
/// More information on predefined channels can be found in IEEE 1666-2011 §6.
class BindPortOp;

} // namespace circt::systemc
namespace circt::systemc {

/// indirect call operation
/// The `systemc.cpp.call_indirect` operation represents an indirect call to a
/// value of function type. The operands and result types of the call must match
/// the specified function type.
/// 
/// Example:
/// 
/// ```mlir
/// %func = systemc.cpp.member_access %object dot "func" : () -> i32
/// %result = systemc.cpp.call_indirect %func() : () -> i32
/// ```
class CallIndirectOp;

} // namespace circt::systemc
namespace circt::systemc {

/// call operation
/// The `systemc.cpp.call` operation represents a direct call to a function that
/// is within the same symbol scope as the call. The operands and result types
/// of the call must match the specified function type. The callee is encoded as
/// a symbol reference attribute named "callee".
/// 
/// Example:
/// 
/// ```mlir
/// %2 = systemc.cpp.call @my_add(%0, %1) : (i32, i32) -> i32
/// ```
class CallOp;

} // namespace circt::systemc
namespace circt::systemc {

/// Converts between various integer and bit vector types.
/// Allows conversions between the various integer and bit vector types in
/// SystemC, including MLIRs signless integers that are used to represent the
/// primitive C integer types, according to the explicit and implicit
/// constructors, implicit access operators and explicit conversion member
/// functions defined in the respective data type class in the SystemC spec
/// (refer to the description of the supported types and the spec chapters
/// listed there for more information).
class ConvertOp;

} // namespace circt::systemc
namespace circt::systemc {

/// A constructor definition.
/// Represents the SC_CTOR macro as described in IEEE 1666-2011 §5.2.7.
/// The name of the module being constructed does not have to be passed
/// to this operation, but is automatically added during emission.
class CtorOp;

} // namespace circt::systemc
namespace circt::systemc {

/// A C++ delete expression.
/// Destroys objects previously allocated by the new expression and releases
/// the allocated memory.
class DeleteOp;

} // namespace circt::systemc
namespace circt::systemc {

/// A C++ destructor definition.
/// This operation models a C++ destructor of a class or struct. It is not an
/// operation modelling some abstract SystemC construct, but still required to
/// support more complex functionality such as having a pointer to an external
/// object inside a SystemC module, e.g., for interoperability purposes.
class DestructorOp;

} // namespace circt::systemc
namespace circt::systemc {

/// An operation with a name containing a single `SSACFG` region
/// Operations within the function cannot implicitly capture values defined
/// outside of the function, i.e. Functions are `IsolatedFromAbove`. All
/// external references must use function arguments or attributes that establish
/// a symbolic connection (e.g. symbols referenced by name via a string
/// attribute like SymbolRefAttr). An external function declaration (used when
/// referring to a function declared in some other module) has no body. While
/// the MLIR textual form provides a nice inline syntax for function arguments,
/// they are internally represented as “block arguments” to the first block in
/// the region.
/// 
/// Argument names are stored in a 'argNames' attribute, but used directly as
/// the SSA value's names. They are verified to be unique and can be used to
/// print them, e.g., as C function argument names.
/// 
/// Only dialect attribute names may be specified in the attribute dictionaries
/// for function arguments, results, or the function itself.
/// 
/// Example:
/// 
/// ```mlir
/// // External function definitions.
/// systemc.cpp.func @abort()
/// systemc.cpp.func externC @scribble(i32, i64) -> i64
/// 
/// // A function that returns its argument twice:
/// systemc.cpp.func @count(%argumentName: i64) -> (i64, i64) {
///   return %argumentName, %argumentName: i64, i64
/// }
/// 
/// // A function with an attribute
/// systemc.cpp.func @exampleFnAttr() attributes {dialectName.attrName = false}
/// ```
class FuncOp;

} // namespace circt::systemc
namespace circt::systemc {

/// Declares a SystemC module instance.
/// Declares an instantiation of a SystemC module inside another SystemC module
/// by value. The instance handle returned by this operation can then be used
/// to initialize it in the constructor and to access its fields.
/// More information can be found in IEEE 1666-2011 §4.1.1.
class InstanceDeclOp;

} // namespace circt::systemc
namespace circt::systemc {

/// Instantiates a verilated module.
/// Instantiates a verilated module represented by a hw.module operation
/// (usually the extern variant).
/// 
/// This operation also encodes the interoparability layer to connect its
/// context (i.e. the surrounding operation, input values, result values, and
/// types) to the C++ code of the verilated module.
/// When residing in a context that understands C++ (e.g., inside a SystemC
/// module), this refers to the instantiation of the class, assignment of the
/// input ports, the call to the eval() function and reading the output ports.
/// 
/// Additionally, properties of the verilated module can be specified in
/// a config attribute which influences the interop layer code generation
/// (not yet implemented).
class InteropVerilatedOp;

} // namespace circt::systemc
namespace circt::systemc {

/// A C++ member access expression.
/// Represents the C++ member access operators `.` and `->`.
/// The member name is passed as a plain string and is not checked for validity.
/// Additional qualifications (`A::E1`) or template disambiguation
/// (`template E1`) can be manually added to this plain member name string for
/// emission.
/// The type of the object and result cannot be verified as it is allowed to use
/// varbatim types such as `emitc.opaque`.
class MemberAccessOp;

} // namespace circt::systemc
namespace circt::systemc {

/// Represents the SystemC SC_METHOD macro.
/// Represents the SC_METHOD macro as described in IEEE 1666-2011 §5.2.9.
class MethodOp;

} // namespace circt::systemc
namespace circt::systemc {

/// A C++ 'new' expression.
/// Creates and initializes C++ objects using dynamic storage.
/// Note that the types of the constructor arguments are not verified in any way
/// w.r.t. the result's type because it is allowed to use an opaque type for the
/// pointee.
class NewOp;

} // namespace circt::systemc
namespace circt::systemc {

/// Function return operation
/// The `systemc.cpp.return` operation represents a return operation within a
/// function. The operand number and types must match the signature of the
/// function that contains the operation.
/// 
/// Example:
/// 
/// ```mlir
/// systemc.cpp.func @foo() : i32 {
///   ...
///   systemc.cpp.return %0 : i32
/// }
/// ```
class ReturnOp;

} // namespace circt::systemc
namespace circt::systemc {

/// A (void)->void member function of a SC_MODULE.
/// This operation does not represent a specific SystemC construct, but a
/// regular C++ member function with no arguments and a void return type.
/// These are used to implement module-internal logic and are registered to the
/// module using the SC_METHOD, SC_THREAD, and SC_CTHREAD macros.
class SCFuncOp;

} // namespace circt::systemc
namespace circt::systemc {

/// Define a SystemC SC_MODULE.
/// Represents the SC_MODULE macro as described in IEEE 1666-2011 §5.2.5.
/// Models input, output and inout ports as module arguments (as opposed to
/// `sc_signal`s which are modeled by a separate `systemc.signal` operation),
/// but are nonetheless emitted as regular struct fields.
class SCModuleOp;

} // namespace circt::systemc
namespace circt::systemc {

/// Describes the static sensitivity of an unspawned process.
/// This operation allows to specify the static sensitivity of unspawned
/// processes. An unspawned process is one created by the `SC_METHOD`,
/// `SC_THREAD`, or `SC_CTHREAD` macro. The operands to this operation are
/// registered as sensitivities to the process last created (in control-flow
/// order).
/// Each `SC_MODULE` contains an instance of the `sc_sensitive` class to do the
/// registration. For a description of the `sc_sensitive` class refer to
/// IEEE 1666-2011 §5.4. For a description of the `sensitive` data member of
/// `SC_MODULE` refer to IEEE 1666-2011 §5.2.14.
class SensitiveOp;

} // namespace circt::systemc
namespace circt::systemc {

/// Declares a SystemC `sc_signal<T>`.
/// Represents the `sc_signal` template as described in IEEE 1666-2011 §6.4.
/// Adding the 'named' attribute will lead to the signal being emitted with the
/// `SC_NAMED` convenience macro. Note that this macro is not part of
/// IEEE 1666-2011, but was added in version 2.3.3.
class SignalOp;

} // namespace circt::systemc
namespace circt::systemc {

/// Returns the current value of a signal or port.
/// Represents the member function `const T& read() const;` and operator
/// `operator const T& () const;` of class `sc_signal` as described in
/// IEEE 1666-2011 §6.4.7., of class `sc_in` as described in §6.8.3., and
/// of class `sc_inout` as decribed in §6.10.3. It shall return the current
/// value of the signal/port.
class SignalReadOp;

} // namespace circt::systemc
namespace circt::systemc {

/// Writes a value to a signal or port.
/// Represents the member function `void write(const T&);` and several variants
/// of the operator `operator=` of class `sc_signal` as described in
/// IEEE 1666-2011 §6.4.8., of class `sc_inout` as described in §6.10.3., and of
/// class `sc_out` as decribed in §6.12.3. It shall modify the value of the
/// signal/port such that it appears to have the new value (as observed using
/// the `sytemc.signal.read` operation) in the next delta cycle but not before
/// then.
class SignalWriteOp;

} // namespace circt::systemc
namespace circt::systemc {

/// Represents the SystemC SC_THREAD macro.
/// Represents the SC_THREAD macro as described in IEEE 1666-2011 §5.2.9.
class ThreadOp;

} // namespace circt::systemc
namespace circt::systemc {

/// Declare a C++ variable with optional initialization value.
/// Declares a variable according to C++ semantics. If an initialization value
/// is present, the variable will be assigned that value at the declaration,
/// e.g, `int varname = 0;`.
class VariableOp;

} // namespace circt::systemc
#ifdef GET_OP_CLASSES
#undef GET_OP_CLASSES

namespace circt::systemc {


//===----------------------------------------------------------------------===//
// ::circt::systemc::AssignOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class AssignOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  AssignOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("systemc.cpp.assign", odsAttrs.getContext());
  }

  AssignOpGenericAdaptorBase(AssignOp op);

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
class AssignOpGenericAdaptor : public detail::AssignOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::AssignOpGenericAdaptorBase;
  static constexpr int odsIndex_dest = 0;
  static constexpr int odsIndex_source = 1;
public:
  AssignOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  AssignOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : AssignOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  AssignOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : AssignOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  AssignOpGenericAdaptor(RangeT values, const AssignOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = AssignOp, typename = std::enable_if_t<std::is_same_v<LateInst, AssignOp>>>
  AssignOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getDest() {
    return (*getODSOperands(0).begin());
  }

  ValueT getSource() {
    return (*getODSOperands(1).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class AssignOpAdaptor : public AssignOpGenericAdaptor<::mlir::ValueRange> {
public:
  using AssignOpGenericAdaptor::AssignOpGenericAdaptor;
  AssignOpAdaptor(AssignOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class AssignOp : public ::mlir::Op<AssignOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::NOperands<2>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::OpTrait::SameTypeOperands> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = AssignOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = AssignOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_dest = 0;
  static constexpr int odsIndex_source = 1;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("systemc.cpp.assign");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::Type> getDest() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getSource() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(1).begin());
  }

  ::mlir::OpOperand &getDestMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getSourceMutable() {
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

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value dest, ::mlir::Value source);
  static AssignOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value dest, ::mlir::Value source);
  static AssignOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value dest, ::mlir::Value source);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value dest, ::mlir::Value source);
  static AssignOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value dest, ::mlir::Value source);
  static AssignOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value dest, ::mlir::Value source);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static AssignOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static AssignOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static AssignOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static AssignOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
};

} // namespace circt::systemc
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::systemc::AssignOp)

namespace circt::systemc {


//===----------------------------------------------------------------------===//
// ::circt::systemc::BindPortOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class BindPortOpGenericAdaptorBase {
public:
  struct Properties {
    using portIdTy = ::mlir::IntegerAttr;
    portIdTy portId;

    auto getPortId() const {
      auto &propStorage = this->portId;
      return ::llvm::cast<::mlir::IntegerAttr>(propStorage);
    }
    void setPortId(const ::mlir::IntegerAttr &propValue) {
      this->portId = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.portId == this->portId &&
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
  BindPortOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("systemc.instance.bind_port", odsAttrs.getContext());
  }

  BindPortOpGenericAdaptorBase(BindPortOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::IntegerAttr getPortIdAttr() {
    auto attr = ::llvm::cast<::mlir::IntegerAttr>(getProperties().portId);
    return attr;
  }

  ::llvm::APInt getPortId();
};

} // namespace detail
template <typename RangeT>
class BindPortOpGenericAdaptor : public detail::BindPortOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::BindPortOpGenericAdaptorBase;
  static constexpr int odsIndex_instance = 0;
  static constexpr int odsIndex_channel = 1;
public:
  BindPortOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  BindPortOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : BindPortOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  BindPortOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : BindPortOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  BindPortOpGenericAdaptor(RangeT values, const BindPortOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = BindPortOp, typename = std::enable_if_t<std::is_same_v<LateInst, BindPortOp>>>
  BindPortOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getInstance() {
    return (*getODSOperands(0).begin());
  }

  ValueT getChannel() {
    return (*getODSOperands(1).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class BindPortOpAdaptor : public BindPortOpGenericAdaptor<::mlir::ValueRange> {
public:
  using BindPortOpGenericAdaptor::BindPortOpGenericAdaptor;
  BindPortOpAdaptor(BindPortOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class BindPortOp : public ::mlir::Op<BindPortOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::NOperands<2>::Impl, ::mlir::OpTrait::HasParent<CtorOp>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = BindPortOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = BindPortOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_instance = 0;
  static constexpr int odsIndex_channel = 1;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("portId")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getPortIdAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getPortIdAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("systemc.instance.bind_port");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::circt::systemc::ModuleType> getInstance() {
    return ::llvm::cast<::mlir::TypedValue<::circt::systemc::ModuleType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getChannel() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(1).begin());
  }

  ::mlir::OpOperand &getInstanceMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getChannelMutable() {
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

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::llvm::LogicalResult readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state);
  void writeProperties(::mlir::DialectBytecodeWriter &writer);
  ::mlir::IntegerAttr getPortIdAttr() {
    return ::llvm::cast<::mlir::IntegerAttr>(getProperties().portId);
  }

  ::llvm::APInt getPortId();
  void setPortIdAttr(::mlir::IntegerAttr attr) {
    getProperties().portId = attr;
  }

  void setPortId(::llvm::APInt attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value instance, ::mlir::IntegerAttr portId, ::mlir::Value channel);
  static BindPortOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value instance, ::mlir::IntegerAttr portId, ::mlir::Value channel);
  static BindPortOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value instance, ::mlir::IntegerAttr portId, ::mlir::Value channel);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value instance, ::mlir::IntegerAttr portId, ::mlir::Value channel);
  static BindPortOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value instance, ::mlir::IntegerAttr portId, ::mlir::Value channel);
  static BindPortOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value instance, ::mlir::IntegerAttr portId, ::mlir::Value channel);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value instance, ::llvm::APInt portId, ::mlir::Value channel);
  static BindPortOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value instance, ::llvm::APInt portId, ::mlir::Value channel);
  static BindPortOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value instance, ::llvm::APInt portId, ::mlir::Value channel);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value instance, ::llvm::APInt portId, ::mlir::Value channel);
  static BindPortOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value instance, ::llvm::APInt portId, ::mlir::Value channel);
  static BindPortOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value instance, ::llvm::APInt portId, ::mlir::Value channel);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static BindPortOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static BindPortOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static BindPortOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static BindPortOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
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
    assert(index < 1 && "invalid attribute index");
    assert(name.getStringRef() == getOperationName() && "invalid operation name");
    assert(name.isRegistered() && "Operation isn't registered, missing a "
          "dependent dialect loading?");
    return name.getAttributeNames()[index];
  }

public:
  /// Get the name of the port to be bound.
  StringRef getPortName();
};

} // namespace circt::systemc
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::systemc::BindPortOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::systemc::detail::BindPortOpGenericAdaptorBase::Properties)

namespace circt::systemc {


//===----------------------------------------------------------------------===//
// ::circt::systemc::CallIndirectOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class CallIndirectOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  CallIndirectOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("systemc.cpp.call_indirect", odsAttrs.getContext());
  }

  CallIndirectOpGenericAdaptorBase(CallIndirectOp op);

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
class CallIndirectOpGenericAdaptor : public detail::CallIndirectOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::CallIndirectOpGenericAdaptorBase;
  static constexpr int odsIndex_callee = 0;
  static constexpr int odsIndex_callee_operands = 1;
public:
  CallIndirectOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  CallIndirectOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : CallIndirectOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  CallIndirectOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : CallIndirectOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  CallIndirectOpGenericAdaptor(RangeT values, const CallIndirectOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = CallIndirectOp, typename = std::enable_if_t<std::is_same_v<LateInst, CallIndirectOp>>>
  CallIndirectOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getCallee() {
    return (*getODSOperands(0).begin());
  }

  RangeT getCalleeOperands() {
    return getODSOperands(1);
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class CallIndirectOpAdaptor : public CallIndirectOpGenericAdaptor<::mlir::ValueRange> {
public:
  using CallIndirectOpGenericAdaptor::CallIndirectOpGenericAdaptor;
  CallIndirectOpAdaptor(CallIndirectOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class CallIndirectOp : public ::mlir::Op<CallIndirectOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::VariadicResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::AtLeastNOperands<1>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::ArgAndResultAttrsOpInterface::Trait, ::mlir::CallOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = CallIndirectOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = CallIndirectOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_callee = 0;
  static constexpr int odsIndex_callee_operands = 1;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("systemc.cpp.call_indirect");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::FunctionType> getCallee() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::FunctionType>>(*getODSOperands(0).begin());
  }

  ::mlir::Operation::operand_range getCalleeOperands() {
    return getODSOperands(1);
  }

  ::mlir::OpOperand &getCalleeMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::MutableOperandRange getCalleeOperandsMutable();
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Value callee, ValueRange operands = {});
  static CallIndirectOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Value callee, ValueRange operands = {});
  static CallIndirectOp create(::mlir::ImplicitLocOpBuilder &builder, Value callee, ValueRange operands = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange results, ::mlir::Value callee, ::mlir::ValueRange callee_operands);
  static CallIndirectOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange results, ::mlir::Value callee, ::mlir::ValueRange callee_operands);
  static CallIndirectOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange results, ::mlir::Value callee, ::mlir::ValueRange callee_operands);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static CallIndirectOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static CallIndirectOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static CallIndirectOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static CallIndirectOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
  MutableOperandRange getArgOperandsMutable() {
    return getCalleeOperandsMutable();
  }

  /// Get the argument operands to the called function.
  operand_range getArgOperands() {
    return {arg_operand_begin(), arg_operand_end()};
  }

  operand_iterator arg_operand_begin() { return ++operand_begin(); }
  operand_iterator arg_operand_end() { return operand_end(); }

  /// Return the callee of this operation.
  CallInterfaceCallable getCallableForCallee() { return getCallee(); }

  /// Set the callee for this operation.
  void setCalleeFromCallable(mlir::CallInterfaceCallable callee) {
    assert(0 && "setCallee not possible");
    abort();
  }

  /// Stub implementations for ArgumentAttributesMethods. If desired,
  /// implement these by defining arg_attrs and res_attrs as arguments to the
  /// operation as OptionalAttr<DictArrayAttr>.
  mlir::ArrayAttr getArgAttrsAttr() { return nullptr; }
  mlir::ArrayAttr getResAttrsAttr() { return nullptr; }
  void setArgAttrsAttr(mlir::ArrayAttr args) {}
  void setResAttrsAttr(mlir::ArrayAttr args) {}
  mlir::Attribute removeArgAttrsAttr() { return nullptr; }
  mlir::Attribute removeResAttrsAttr() { return nullptr; }
};

} // namespace circt::systemc
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::systemc::CallIndirectOp)

namespace circt::systemc {


//===----------------------------------------------------------------------===//
// ::circt::systemc::CallOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class CallOpGenericAdaptorBase {
public:
  struct Properties {
    using calleeTy = ::mlir::FlatSymbolRefAttr;
    calleeTy callee;

    auto getCallee() const {
      auto &propStorage = this->callee;
      return ::llvm::cast<::mlir::FlatSymbolRefAttr>(propStorage);
    }
    void setCallee(const ::mlir::FlatSymbolRefAttr &propValue) {
      this->callee = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.callee == this->callee &&
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
  CallOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("systemc.cpp.call", odsAttrs.getContext());
  }

  CallOpGenericAdaptorBase(CallOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::FlatSymbolRefAttr getCalleeAttr() {
    auto attr = ::llvm::cast<::mlir::FlatSymbolRefAttr>(getProperties().callee);
    return attr;
  }

  ::llvm::StringRef getCallee();
};

} // namespace detail
template <typename RangeT>
class CallOpGenericAdaptor : public detail::CallOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::CallOpGenericAdaptorBase;
  static constexpr int odsIndex_callee_operands = 0;
public:
  CallOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  CallOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : CallOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  CallOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : CallOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  CallOpGenericAdaptor(RangeT values, const CallOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = CallOp, typename = std::enable_if_t<std::is_same_v<LateInst, CallOp>>>
  CallOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getCalleeOperands() {
    return getODSOperands(0);
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class CallOpAdaptor : public CallOpGenericAdaptor<::mlir::ValueRange> {
public:
  using CallOpGenericAdaptor::CallOpGenericAdaptor;
  CallOpAdaptor(CallOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class CallOp : public ::mlir::Op<CallOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::VariadicResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::ArgAndResultAttrsOpInterface::Trait, ::mlir::CallOpInterface::Trait, ::mlir::SymbolUserOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = CallOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = CallOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_callee_operands = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("callee")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getCalleeAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getCalleeAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("systemc.cpp.call");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::operand_range getCalleeOperands() {
    return getODSOperands(0);
  }

  ::mlir::MutableOperandRange getCalleeOperandsMutable();
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
  ::mlir::FlatSymbolRefAttr getCalleeAttr() {
    return ::llvm::cast<::mlir::FlatSymbolRefAttr>(getProperties().callee);
  }

  ::llvm::StringRef getCallee();
  void setCalleeAttr(::mlir::FlatSymbolRefAttr attr) {
    getProperties().callee = attr;
  }

  void setCallee(::llvm::StringRef attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, FuncOp callee, ValueRange operands = {});
  static CallOp create(::mlir::OpBuilder &builder, ::mlir::Location location, FuncOp callee, ValueRange operands = {});
  static CallOp create(::mlir::ImplicitLocOpBuilder &builder, FuncOp callee, ValueRange operands = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, SymbolRefAttr callee, Type result, ValueRange operands = {});
  static CallOp create(::mlir::OpBuilder &builder, ::mlir::Location location, SymbolRefAttr callee, Type result, ValueRange operands = {});
  static CallOp create(::mlir::ImplicitLocOpBuilder &builder, SymbolRefAttr callee, Type result, ValueRange operands = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, StringAttr callee, Type result, ValueRange operands = {});
  static CallOp create(::mlir::OpBuilder &builder, ::mlir::Location location, StringAttr callee, Type result, ValueRange operands = {});
  static CallOp create(::mlir::ImplicitLocOpBuilder &builder, StringAttr callee, Type result, ValueRange operands = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, StringRef callee, Type result, ValueRange operands = {});
  static CallOp create(::mlir::OpBuilder &builder, ::mlir::Location location, StringRef callee, Type result, ValueRange operands = {});
  static CallOp create(::mlir::ImplicitLocOpBuilder &builder, StringRef callee, Type result, ValueRange operands = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange results, ::mlir::FlatSymbolRefAttr callee, ::mlir::ValueRange callee_operands);
  static CallOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange results, ::mlir::FlatSymbolRefAttr callee, ::mlir::ValueRange callee_operands);
  static CallOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange results, ::mlir::FlatSymbolRefAttr callee, ::mlir::ValueRange callee_operands);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange results, ::llvm::StringRef callee, ::mlir::ValueRange callee_operands);
  static CallOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange results, ::llvm::StringRef callee, ::mlir::ValueRange callee_operands);
  static CallOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange results, ::llvm::StringRef callee, ::mlir::ValueRange callee_operands);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static CallOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static CallOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static CallOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static CallOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  ::llvm::LogicalResult verifySymbolUses(::mlir::SymbolTableCollection &symbolTable);
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
  FunctionType getCalleeType();

  MutableOperandRange getArgOperandsMutable() {
    return getCalleeOperandsMutable();
  }

  /// Get the argument operands to the called function.
  operand_range getArgOperands() {
    return {arg_operand_begin(), arg_operand_end()};
  }

  operand_iterator arg_operand_begin() { return operand_begin(); }
  operand_iterator arg_operand_end() { return operand_end(); }

  /// Return the callee of this operation.
  CallInterfaceCallable getCallableForCallee() {
    return (*this)->getAttrOfType<SymbolRefAttr>("callee");
  }

  /// Set the callee for this operation.
  void setCalleeFromCallable(mlir::CallInterfaceCallable callee) {
    (*this)->setAttr(getCalleeAttrName(), llvm::cast<mlir::SymbolRefAttr>(callee));
  }

  /// Stub implementations for ArgumentAttributesMethods. If desired,
  /// implement these by defining arg_attrs and res_attrs as arguments to the
  /// operation as OptionalAttr<DictArrayAttr>.
  mlir::ArrayAttr getArgAttrsAttr() { return nullptr; }
  mlir::ArrayAttr getResAttrsAttr() { return nullptr; }
  void setArgAttrsAttr(mlir::ArrayAttr args) {}
  void setResAttrsAttr(mlir::ArrayAttr args) {}
  mlir::Attribute removeArgAttrsAttr() { return nullptr; }
  mlir::Attribute removeResAttrsAttr() { return nullptr; }
};

} // namespace circt::systemc
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::systemc::CallOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::systemc::detail::CallOpGenericAdaptorBase::Properties)

namespace circt::systemc {


//===----------------------------------------------------------------------===//
// ::circt::systemc::ConvertOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ConvertOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  ConvertOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("systemc.convert", odsAttrs.getContext());
  }

  ConvertOpGenericAdaptorBase(ConvertOp op);

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
class ConvertOpGenericAdaptor : public detail::ConvertOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ConvertOpGenericAdaptorBase;
  static constexpr int odsIndex_input = 0;
public:
  ConvertOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ConvertOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : ConvertOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ConvertOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ConvertOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ConvertOpGenericAdaptor(RangeT values, const ConvertOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ConvertOp, typename = std::enable_if_t<std::is_same_v<LateInst, ConvertOp>>>
  ConvertOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class ConvertOpAdaptor : public ConvertOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ConvertOpGenericAdaptor::ConvertOpGenericAdaptor;
  ConvertOpAdaptor(ConvertOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ConvertOp : public ::mlir::Op<ConvertOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::Type>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ConvertOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ConvertOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_input = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("systemc.convert");
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
  static ConvertOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value input);
  static ConvertOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value input);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value input);
  static ConvertOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value input);
  static ConvertOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value input);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ConvertOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ConvertOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ConvertOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ConvertOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::mlir::OpFoldResult fold(FoldAdaptor adaptor);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
};

} // namespace circt::systemc
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::systemc::ConvertOp)

namespace circt::systemc {


//===----------------------------------------------------------------------===//
// ::circt::systemc::CtorOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class CtorOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  CtorOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("systemc.ctor", odsAttrs.getContext());
  }

  CtorOpGenericAdaptorBase(CtorOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

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
class CtorOpGenericAdaptor : public detail::CtorOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::CtorOpGenericAdaptorBase;
public:
  CtorOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  CtorOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : CtorOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  CtorOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : CtorOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  CtorOpGenericAdaptor(RangeT values, const CtorOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = CtorOp, typename = std::enable_if_t<std::is_same_v<LateInst, CtorOp>>>
  CtorOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class CtorOpAdaptor : public CtorOpGenericAdaptor<::mlir::ValueRange> {
public:
  using CtorOpGenericAdaptor::CtorOpGenericAdaptor;
  CtorOpAdaptor(CtorOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class CtorOp : public ::mlir::Op<CtorOp, ::mlir::OpTrait::OneRegion, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::SingleBlock, ::mlir::OpTrait::NoTerminator, ::mlir::OpTrait::HasParent<SCModuleOp>::Impl, ::mlir::OpTrait::OpInvariants> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = CtorOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = CtorOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("systemc.ctor");
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState);
  static CtorOp create(::mlir::OpBuilder &builder, ::mlir::Location location);
  static CtorOp create(::mlir::ImplicitLocOpBuilder &builder);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
  /// Return the block corresponding to the region.
  Block *getBodyBlock() { return &getBody().front(); }
};

} // namespace circt::systemc
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::systemc::CtorOp)

namespace circt::systemc {


//===----------------------------------------------------------------------===//
// ::circt::systemc::DeleteOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class DeleteOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  DeleteOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("systemc.cpp.delete", odsAttrs.getContext());
  }

  DeleteOpGenericAdaptorBase(DeleteOp op);

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
class DeleteOpGenericAdaptor : public detail::DeleteOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::DeleteOpGenericAdaptorBase;
  static constexpr int odsIndex_pointer = 0;
public:
  DeleteOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  DeleteOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : DeleteOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  DeleteOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : DeleteOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  DeleteOpGenericAdaptor(RangeT values, const DeleteOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = DeleteOp, typename = std::enable_if_t<std::is_same_v<LateInst, DeleteOp>>>
  DeleteOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getPointer() {
    return (*getODSOperands(0).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class DeleteOpAdaptor : public DeleteOpGenericAdaptor<::mlir::ValueRange> {
public:
  using DeleteOpGenericAdaptor::DeleteOpGenericAdaptor;
  DeleteOpAdaptor(DeleteOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class DeleteOp : public ::mlir::Op<DeleteOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = DeleteOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = DeleteOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_pointer = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("systemc.cpp.delete");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::emitc::PointerType> getPointer() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::emitc::PointerType>>(*getODSOperands(0).begin());
  }

  ::mlir::OpOperand &getPointerMutable() {
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value pointer);
  static DeleteOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value pointer);
  static DeleteOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value pointer);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value pointer);
  static DeleteOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value pointer);
  static DeleteOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value pointer);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static DeleteOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static DeleteOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static DeleteOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static DeleteOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
};

} // namespace circt::systemc
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::systemc::DeleteOp)

namespace circt::systemc {


//===----------------------------------------------------------------------===//
// ::circt::systemc::DestructorOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class DestructorOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  DestructorOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("systemc.cpp.destructor", odsAttrs.getContext());
  }

  DestructorOpGenericAdaptorBase(DestructorOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

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
class DestructorOpGenericAdaptor : public detail::DestructorOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::DestructorOpGenericAdaptorBase;
public:
  DestructorOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  DestructorOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : DestructorOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  DestructorOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : DestructorOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  DestructorOpGenericAdaptor(RangeT values, const DestructorOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = DestructorOp, typename = std::enable_if_t<std::is_same_v<LateInst, DestructorOp>>>
  DestructorOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class DestructorOpAdaptor : public DestructorOpGenericAdaptor<::mlir::ValueRange> {
public:
  using DestructorOpGenericAdaptor::DestructorOpGenericAdaptor;
  DestructorOpAdaptor(DestructorOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class DestructorOp : public ::mlir::Op<DestructorOp, ::mlir::OpTrait::OneRegion, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::SingleBlock, ::mlir::OpTrait::NoTerminator, ::mlir::OpTrait::HasParent<SCModuleOp>::Impl, ::mlir::OpTrait::OpInvariants> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = DestructorOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = DestructorOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("systemc.cpp.destructor");
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState);
  static DestructorOp create(::mlir::OpBuilder &builder, ::mlir::Location location);
  static DestructorOp create(::mlir::ImplicitLocOpBuilder &builder);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
  /// Return the block corresponding to the region.
  Block *getBodyBlock() { return &getBody().front(); }
};

} // namespace circt::systemc
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::systemc::DestructorOp)

namespace circt::systemc {


//===----------------------------------------------------------------------===//
// ::circt::systemc::FuncOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class FuncOpGenericAdaptorBase {
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
    using arg_attrsTy = ::mlir::ArrayAttr;
    arg_attrsTy arg_attrs;

    auto getArgAttrs() const {
      auto &propStorage = this->arg_attrs;
      return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(propStorage);
    }
    void setArgAttrs(const ::mlir::ArrayAttr &propValue) {
      this->arg_attrs = propValue;
    }
    using externCTy = ::mlir::UnitAttr;
    externCTy externC;

    auto getExternC() const {
      auto &propStorage = this->externC;
      return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(propStorage);
    }
    void setExternC(const ::mlir::UnitAttr &propValue) {
      this->externC = propValue;
    }
    using function_typeTy = ::mlir::TypeAttr;
    function_typeTy function_type;

    auto getFunctionType() const {
      auto &propStorage = this->function_type;
      return ::llvm::cast<::mlir::TypeAttr>(propStorage);
    }
    void setFunctionType(const ::mlir::TypeAttr &propValue) {
      this->function_type = propValue;
    }
    using res_attrsTy = ::mlir::ArrayAttr;
    res_attrsTy res_attrs;

    auto getResAttrs() const {
      auto &propStorage = this->res_attrs;
      return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(propStorage);
    }
    void setResAttrs(const ::mlir::ArrayAttr &propValue) {
      this->res_attrs = propValue;
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
    using sym_visibilityTy = ::mlir::StringAttr;
    sym_visibilityTy sym_visibility;

    auto getSymVisibility() const {
      auto &propStorage = this->sym_visibility;
      return ::llvm::dyn_cast_or_null<::mlir::StringAttr>(propStorage);
    }
    void setSymVisibility(const ::mlir::StringAttr &propValue) {
      this->sym_visibility = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.argNames == this->argNames &&
        rhs.arg_attrs == this->arg_attrs &&
        rhs.externC == this->externC &&
        rhs.function_type == this->function_type &&
        rhs.res_attrs == this->res_attrs &&
        rhs.sym_name == this->sym_name &&
        rhs.sym_visibility == this->sym_visibility &&
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
  FuncOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("systemc.cpp.func", odsAttrs.getContext());
  }

  FuncOpGenericAdaptorBase(FuncOp op);

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
  ::mlir::TypeAttr getFunctionTypeAttr() {
    auto attr = ::llvm::cast<::mlir::TypeAttr>(getProperties().function_type);
    return attr;
  }

  ::mlir::FunctionType getFunctionType();
  ::mlir::ArrayAttr getArgAttrsAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().arg_attrs);
    return attr;
  }

  ::std::optional< ::mlir::ArrayAttr > getArgAttrs();
  ::mlir::ArrayAttr getResAttrsAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().res_attrs);
    return attr;
  }

  ::std::optional< ::mlir::ArrayAttr > getResAttrs();
  ::mlir::ArrayAttr getArgNamesAttr() {
    auto attr = ::llvm::cast<::mlir::ArrayAttr>(getProperties().argNames);
    return attr;
  }

  ::mlir::ArrayAttr getArgNames();
  ::mlir::UnitAttr getExternCAttr();
  bool getExternC();
  ::mlir::StringAttr getSymVisibilityAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::StringAttr>(getProperties().sym_visibility);
    return attr;
  }

  ::std::optional< ::llvm::StringRef > getSymVisibility();
  ::mlir::Region &getBody() {
    return *odsRegions[0];
  }

  ::mlir::RegionRange getRegions() {
    return odsRegions;
  }

};

} // namespace detail
template <typename RangeT>
class FuncOpGenericAdaptor : public detail::FuncOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::FuncOpGenericAdaptorBase;
public:
  FuncOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  FuncOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : FuncOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  FuncOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : FuncOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  FuncOpGenericAdaptor(RangeT values, const FuncOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = FuncOp, typename = std::enable_if_t<std::is_same_v<LateInst, FuncOp>>>
  FuncOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class FuncOpAdaptor : public FuncOpGenericAdaptor<::mlir::ValueRange> {
public:
  using FuncOpGenericAdaptor::FuncOpGenericAdaptor;
  FuncOpAdaptor(FuncOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class FuncOp : public ::mlir::Op<FuncOp, ::mlir::OpTrait::OneRegion, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::OpTrait::AutomaticAllocationScope, ::mlir::SymbolOpInterface::Trait, ::mlir::ArgAndResultAttrsOpInterface::Trait, ::mlir::CallableOpInterface::Trait, ::mlir::FunctionOpInterface::Trait, ::mlir::OpTrait::IsIsolatedFromAbove, ::mlir::OpAsmOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = FuncOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = FuncOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::OpAsmOpInterface::Trait<FuncOp>::getAsmResultNames;
  using ::mlir::OpAsmOpInterface::Trait<FuncOp>::getAsmBlockNames;
  using ::mlir::OpAsmOpInterface::Trait<FuncOp>::getDefaultDialect;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("argNames"), ::llvm::StringRef("arg_attrs"), ::llvm::StringRef("externC"), ::llvm::StringRef("function_type"), ::llvm::StringRef("res_attrs"), ::llvm::StringRef("sym_name"), ::llvm::StringRef("sym_visibility")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getArgNamesAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getArgNamesAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getArgAttrsAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getArgAttrsAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getExternCAttrName() {
    return getAttributeNameForIndex(2);
  }

  static ::mlir::StringAttr getExternCAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 2);
  }

  ::mlir::StringAttr getFunctionTypeAttrName() {
    return getAttributeNameForIndex(3);
  }

  static ::mlir::StringAttr getFunctionTypeAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 3);
  }

  ::mlir::StringAttr getResAttrsAttrName() {
    return getAttributeNameForIndex(4);
  }

  static ::mlir::StringAttr getResAttrsAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 4);
  }

  ::mlir::StringAttr getSymNameAttrName() {
    return getAttributeNameForIndex(5);
  }

  static ::mlir::StringAttr getSymNameAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 5);
  }

  ::mlir::StringAttr getSymVisibilityAttrName() {
    return getAttributeNameForIndex(6);
  }

  static ::mlir::StringAttr getSymVisibilityAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 6);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("systemc.cpp.func");
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
  ::mlir::TypeAttr getFunctionTypeAttr() {
    return ::llvm::cast<::mlir::TypeAttr>(getProperties().function_type);
  }

  ::mlir::FunctionType getFunctionType();
  ::mlir::ArrayAttr getArgAttrsAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().arg_attrs);
  }

  ::std::optional< ::mlir::ArrayAttr > getArgAttrs();
  ::mlir::ArrayAttr getResAttrsAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().res_attrs);
  }

  ::std::optional< ::mlir::ArrayAttr > getResAttrs();
  ::mlir::ArrayAttr getArgNamesAttr() {
    return ::llvm::cast<::mlir::ArrayAttr>(getProperties().argNames);
  }

  ::mlir::ArrayAttr getArgNames();
  ::mlir::UnitAttr getExternCAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(getProperties().externC);
  }

  bool getExternC();
  ::mlir::StringAttr getSymVisibilityAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::StringAttr>(getProperties().sym_visibility);
  }

  ::std::optional< ::llvm::StringRef > getSymVisibility();
  void setSymNameAttr(::mlir::StringAttr attr) {
    getProperties().sym_name = attr;
  }

  void setSymName(::llvm::StringRef attrValue);
  void setFunctionTypeAttr(::mlir::TypeAttr attr) {
    getProperties().function_type = attr;
  }

  void setFunctionType(::mlir::FunctionType attrValue);
  void setArgAttrsAttr(::mlir::ArrayAttr attr) {
    getProperties().arg_attrs = attr;
  }

  void setResAttrsAttr(::mlir::ArrayAttr attr) {
    getProperties().res_attrs = attr;
  }

  void setArgNamesAttr(::mlir::ArrayAttr attr) {
    getProperties().argNames = attr;
  }

  void setExternCAttr(::mlir::UnitAttr attr) {
    getProperties().externC = attr;
  }

  void setExternC(bool attrValue);
  void setSymVisibilityAttr(::mlir::StringAttr attr) {
    getProperties().sym_visibility = attr;
  }

  void setSymVisibility(::std::optional<::llvm::StringRef> attrValue);
  ::mlir::Attribute removeArgAttrsAttr() {
      auto attr = getProperties().arg_attrs;
      getProperties().arg_attrs = {};
      return attr;
  }

  ::mlir::Attribute removeResAttrsAttr() {
      auto attr = getProperties().res_attrs;
      getProperties().res_attrs = {};
      return attr;
  }

  ::mlir::Attribute removeExternCAttr() {
      auto attr = getProperties().externC;
      getProperties().externC = {};
      return attr;
  }

  ::mlir::Attribute removeSymVisibilityAttr() {
      auto attr = getProperties().sym_visibility;
      getProperties().sym_visibility = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, StringRef name, ArrayAttr argNames, FunctionType type, ArrayRef<NamedAttribute> attrs = {}, ArrayRef<DictionaryAttr> argAttrs = {});
  static FuncOp create(::mlir::OpBuilder &builder, ::mlir::Location location, StringRef name, ArrayAttr argNames, FunctionType type, ArrayRef<NamedAttribute> attrs = {}, ArrayRef<DictionaryAttr> argAttrs = {});
  static FuncOp create(::mlir::ImplicitLocOpBuilder &builder, StringRef name, ArrayAttr argNames, FunctionType type, ArrayRef<NamedAttribute> attrs = {}, ArrayRef<DictionaryAttr> argAttrs = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::StringAttr sym_name, ::mlir::TypeAttr function_type, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs, ::mlir::ArrayAttr argNames, /*optional*/::mlir::UnitAttr externC, /*optional*/::mlir::StringAttr sym_visibility);
  static FuncOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::StringAttr sym_name, ::mlir::TypeAttr function_type, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs, ::mlir::ArrayAttr argNames, /*optional*/::mlir::UnitAttr externC, /*optional*/::mlir::StringAttr sym_visibility);
  static FuncOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::StringAttr sym_name, ::mlir::TypeAttr function_type, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs, ::mlir::ArrayAttr argNames, /*optional*/::mlir::UnitAttr externC, /*optional*/::mlir::StringAttr sym_visibility);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name, ::mlir::TypeAttr function_type, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs, ::mlir::ArrayAttr argNames, /*optional*/::mlir::UnitAttr externC, /*optional*/::mlir::StringAttr sym_visibility);
  static FuncOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name, ::mlir::TypeAttr function_type, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs, ::mlir::ArrayAttr argNames, /*optional*/::mlir::UnitAttr externC, /*optional*/::mlir::StringAttr sym_visibility);
  static FuncOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name, ::mlir::TypeAttr function_type, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs, ::mlir::ArrayAttr argNames, /*optional*/::mlir::UnitAttr externC, /*optional*/::mlir::StringAttr sym_visibility);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::llvm::StringRef sym_name, ::mlir::FunctionType function_type, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs, ::mlir::ArrayAttr argNames, /*optional*/bool externC, /*optional*/::mlir::StringAttr sym_visibility);
  static FuncOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::llvm::StringRef sym_name, ::mlir::FunctionType function_type, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs, ::mlir::ArrayAttr argNames, /*optional*/bool externC, /*optional*/::mlir::StringAttr sym_visibility);
  static FuncOp create(::mlir::ImplicitLocOpBuilder &builder, ::llvm::StringRef sym_name, ::mlir::FunctionType function_type, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs, ::mlir::ArrayAttr argNames, /*optional*/bool externC, /*optional*/::mlir::StringAttr sym_visibility);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name, ::mlir::FunctionType function_type, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs, ::mlir::ArrayAttr argNames, /*optional*/bool externC, /*optional*/::mlir::StringAttr sym_visibility);
  static FuncOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name, ::mlir::FunctionType function_type, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs, ::mlir::ArrayAttr argNames, /*optional*/bool externC, /*optional*/::mlir::StringAttr sym_visibility);
  static FuncOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name, ::mlir::FunctionType function_type, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs, ::mlir::ArrayAttr argNames, /*optional*/bool externC, /*optional*/::mlir::StringAttr sym_visibility);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static FuncOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static FuncOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static FuncOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static FuncOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &p);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  ::llvm::LogicalResult verifyRegions();
  void getAsmBlockArgumentNames(::mlir::Region&region, ::mlir::OpAsmSetValueNameFn setNameFn);
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
  static FuncOp create(Location location, StringRef name,
                       ArrayAttr argNames, FunctionType type,
                       ArrayRef<NamedAttribute> attrs = {});
  static FuncOp create(Location location, StringRef name,
                       ArrayAttr argNames, FunctionType type,
                       Operation::dialect_attr_range attrs);
  static FuncOp create(Location location, StringRef name,
                       ArrayAttr argNames, FunctionType type,
                       ArrayRef<NamedAttribute> attrs,
                       ArrayRef<DictionaryAttr> argAttrs);

  /// Create a deep copy of this function and all of its blocks, remapping any
  /// operands that use values outside of the function using the map that is
  /// provided (leaving them alone if no entry is present). If the mapper
  /// contains entries for function arguments, these arguments are not
  /// included in the new function. Replaces references to cloned sub-values
  /// with the corresponding value that is copied, and adds those mappings to
  /// the mapper.
  FuncOp clone(IRMapping &mapper);
  FuncOp clone();

  /// Clone the internal blocks and attributes from this function into dest.
  /// Any cloned blocks are appended to the back of dest. This function
  /// asserts that the attributes of the current function and dest are
  /// compatible.
  void cloneInto(FuncOp dest, IRMapping &mapper);

  //===------------------------------------------------------------------===//
  // CallableOpInterface
  //===------------------------------------------------------------------===//

  /// Returns the region on the current operation that is callable. This may
  /// return null in the case of an external callable object, e.g. an external
  /// function.
  ::mlir::Region *getCallableRegion() {
    return &getBody();
  }

  /// Returns the argument types of this function.
  ArrayRef<Type> getArgumentTypes() { return getFunctionType().getInputs(); }

  /// Returns the result types of this function.
  ArrayRef<Type> getResultTypes() { return getFunctionType().getResults(); }

  //===------------------------------------------------------------------===//
  // OpAsmOpInterface Methods
  //===------------------------------------------------------------------===//

  /// Allow the dialect prefix to be omitted.
  static StringRef getDefaultDialect() { return "systemc"; }

  //===------------------------------------------------------------------===//
  // SymbolOpInterface Methods
  //===------------------------------------------------------------------===//

  bool isDeclaration() { return isExternal(); }
};

} // namespace circt::systemc
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::systemc::FuncOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::systemc::detail::FuncOpGenericAdaptorBase::Properties)

namespace circt::systemc {


//===----------------------------------------------------------------------===//
// ::circt::systemc::InstanceDeclOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class InstanceDeclOpGenericAdaptorBase {
public:
  struct Properties {
    using moduleNameTy = ::mlir::FlatSymbolRefAttr;
    moduleNameTy moduleName;

    auto getModuleName() const {
      auto &propStorage = this->moduleName;
      return ::llvm::cast<::mlir::FlatSymbolRefAttr>(propStorage);
    }
    void setModuleName(const ::mlir::FlatSymbolRefAttr &propValue) {
      this->moduleName = propValue;
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
    bool operator==(const Properties &rhs) const {
      return 
        rhs.moduleName == this->moduleName &&
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
  InstanceDeclOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("systemc.instance.decl", odsAttrs.getContext());
  }

  InstanceDeclOpGenericAdaptorBase(InstanceDeclOp op);

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
  ::mlir::FlatSymbolRefAttr getModuleNameAttr() {
    auto attr = ::llvm::cast<::mlir::FlatSymbolRefAttr>(getProperties().moduleName);
    return attr;
  }

  ::llvm::StringRef getModuleName();
};

} // namespace detail
template <typename RangeT>
class InstanceDeclOpGenericAdaptor : public detail::InstanceDeclOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::InstanceDeclOpGenericAdaptorBase;
public:
  InstanceDeclOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  InstanceDeclOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : InstanceDeclOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  InstanceDeclOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : InstanceDeclOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  InstanceDeclOpGenericAdaptor(RangeT values, const InstanceDeclOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = InstanceDeclOp, typename = std::enable_if_t<std::is_same_v<LateInst, InstanceDeclOp>>>
  InstanceDeclOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class InstanceDeclOpAdaptor : public InstanceDeclOpGenericAdaptor<::mlir::ValueRange> {
public:
  using InstanceDeclOpGenericAdaptor::InstanceDeclOpGenericAdaptor;
  InstanceDeclOpAdaptor(InstanceDeclOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class InstanceDeclOp : public ::mlir::Op<InstanceDeclOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::circt::systemc::ModuleType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::HasParent<SCModuleOp>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::SymbolUserOpInterface::Trait, ::circt::igraph::InstanceOpInterface::Trait, ::mlir::OpAsmOpInterface::Trait, circt::systemc::SystemCNameDeclOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = InstanceDeclOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = InstanceDeclOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  using ::circt::igraph::InstanceOpInterface::Trait<InstanceDeclOp>::getReferencedModuleNames;
  using ::circt::igraph::InstanceOpInterface::Trait<InstanceDeclOp>::getReferencedModuleNamesAttr;
  using ::mlir::OpAsmOpInterface::Trait<InstanceDeclOp>::getAsmBlockArgumentNames;
  using ::mlir::OpAsmOpInterface::Trait<InstanceDeclOp>::getAsmBlockNames;
  using ::mlir::OpAsmOpInterface::Trait<InstanceDeclOp>::getDefaultDialect;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("moduleName"), ::llvm::StringRef("name")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getModuleNameAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getModuleNameAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getNameAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getNameAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("systemc.instance.decl");
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

  ::mlir::TypedValue<::circt::systemc::ModuleType> getInstanceHandle() {
    return ::llvm::cast<::mlir::TypedValue<::circt::systemc::ModuleType>>(*getODSResults(0).begin());
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
  ::mlir::FlatSymbolRefAttr getModuleNameAttr() {
    return ::llvm::cast<::mlir::FlatSymbolRefAttr>(getProperties().moduleName);
  }

  ::llvm::StringRef getModuleName();
  void setNameAttr(::mlir::StringAttr attr) {
    getProperties().name = attr;
  }

  void setName(::llvm::StringRef attrValue);
  void setModuleNameAttr(::mlir::FlatSymbolRefAttr attr) {
    getProperties().moduleName = attr;
  }

  void setModuleName(::llvm::StringRef attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, StringAttr instanceName, FlatSymbolRefAttr moduleRef, ArrayRef<ModuleType::PortInfo> ports);
  static InstanceDeclOp create(::mlir::OpBuilder &builder, ::mlir::Location location, StringAttr instanceName, FlatSymbolRefAttr moduleRef, ArrayRef<ModuleType::PortInfo> ports);
  static InstanceDeclOp create(::mlir::ImplicitLocOpBuilder &builder, StringAttr instanceName, FlatSymbolRefAttr moduleRef, ArrayRef<ModuleType::PortInfo> ports);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type instanceHandle, ::mlir::StringAttr name, ::mlir::FlatSymbolRefAttr moduleName);
  static InstanceDeclOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type instanceHandle, ::mlir::StringAttr name, ::mlir::FlatSymbolRefAttr moduleName);
  static InstanceDeclOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type instanceHandle, ::mlir::StringAttr name, ::mlir::FlatSymbolRefAttr moduleName);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::StringAttr name, ::mlir::FlatSymbolRefAttr moduleName);
  static InstanceDeclOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::StringAttr name, ::mlir::FlatSymbolRefAttr moduleName);
  static InstanceDeclOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::StringAttr name, ::mlir::FlatSymbolRefAttr moduleName);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type instanceHandle, ::llvm::StringRef name, ::llvm::StringRef moduleName);
  static InstanceDeclOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type instanceHandle, ::llvm::StringRef name, ::llvm::StringRef moduleName);
  static InstanceDeclOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type instanceHandle, ::llvm::StringRef name, ::llvm::StringRef moduleName);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::llvm::StringRef name, ::llvm::StringRef moduleName);
  static InstanceDeclOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::llvm::StringRef name, ::llvm::StringRef moduleName);
  static InstanceDeclOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::llvm::StringRef name, ::llvm::StringRef moduleName);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static InstanceDeclOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static InstanceDeclOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static InstanceDeclOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static InstanceDeclOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verifySymbolUses(::mlir::SymbolTableCollection &symbolTable);
  ::llvm::StringRef getInstanceName();
  ::mlir::StringAttr getInstanceNameAttr();
  void getAsmResultNames(::mlir::OpAsmSetValueNameFn setNameFn);
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
  /// Get the systemc::ModuleType that represents the instantiated module.
  systemc::ModuleType getInstanceType() {
    return llvm::cast<systemc::ModuleType>(getInstanceHandle().getType());
  }

  /// Lookup the module for the symbol. This returns null on invalid IR.
  Operation *getReferencedModuleCached(const hw::HWSymbolCache *cache);

  //===------------------------------------------------------------------===//
  // SymbolOpInterface Methods
  //===------------------------------------------------------------------===//

  /// An InstanceDeclOp may not optionally define a symbol.
  bool isOptionalSymbol() { return false; }

  //===------------------------------------------------------------------===//
  // InstanceGraphInstanceOpInterface Methods
  //===------------------------------------------------------------------===//

  StringAttr getReferencedModuleNameAttr() {
    return getModuleNameAttr().getAttr();
  }

  //===------------------------------------------------------------------===//
  // PortList Methods
  //===------------------------------------------------------------------===//
  SmallVector<::circt::hw::PortInfo> getPortList();
};

} // namespace circt::systemc
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::systemc::InstanceDeclOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::systemc::detail::InstanceDeclOpGenericAdaptorBase::Properties)

namespace circt::systemc {


//===----------------------------------------------------------------------===//
// ::circt::systemc::InteropVerilatedOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class InteropVerilatedOpGenericAdaptorBase {
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
        rhs.inputNames == this->inputNames &&
        rhs.instanceName == this->instanceName &&
        rhs.moduleName == this->moduleName &&
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
  InteropVerilatedOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("systemc.interop.verilated", odsAttrs.getContext());
  }

  InteropVerilatedOpGenericAdaptorBase(InteropVerilatedOp op);

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
  ::mlir::ArrayAttr getInputNamesAttr() {
    auto attr = ::llvm::cast<::mlir::ArrayAttr>(getProperties().inputNames);
    return attr;
  }

  ::mlir::ArrayAttr getInputNames();
  ::mlir::ArrayAttr getResultNamesAttr() {
    auto attr = ::llvm::cast<::mlir::ArrayAttr>(getProperties().resultNames);
    return attr;
  }

  ::mlir::ArrayAttr getResultNames();
};

} // namespace detail
template <typename RangeT>
class InteropVerilatedOpGenericAdaptor : public detail::InteropVerilatedOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::InteropVerilatedOpGenericAdaptorBase;
  static constexpr int odsIndex_inputs = 0;
public:
  InteropVerilatedOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  InteropVerilatedOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : InteropVerilatedOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  InteropVerilatedOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : InteropVerilatedOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  InteropVerilatedOpGenericAdaptor(RangeT values, const InteropVerilatedOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = InteropVerilatedOp, typename = std::enable_if_t<std::is_same_v<LateInst, InteropVerilatedOp>>>
  InteropVerilatedOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class InteropVerilatedOpAdaptor : public InteropVerilatedOpGenericAdaptor<::mlir::ValueRange> {
public:
  using InteropVerilatedOpGenericAdaptor::InteropVerilatedOpGenericAdaptor;
  InteropVerilatedOpAdaptor(InteropVerilatedOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class InteropVerilatedOp : public ::mlir::Op<InteropVerilatedOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::VariadicResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::SymbolUserOpInterface::Trait, ::mlir::OpAsmOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = InteropVerilatedOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = InteropVerilatedOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_inputs = 0;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::OpAsmOpInterface::Trait<InteropVerilatedOp>::getAsmBlockArgumentNames;
  using ::mlir::OpAsmOpInterface::Trait<InteropVerilatedOp>::getAsmBlockNames;
  using ::mlir::OpAsmOpInterface::Trait<InteropVerilatedOp>::getDefaultDialect;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("inputNames"), ::llvm::StringRef("instanceName"), ::llvm::StringRef("moduleName"), ::llvm::StringRef("resultNames")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getInputNamesAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getInputNamesAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getInstanceNameAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getInstanceNameAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getModuleNameAttrName() {
    return getAttributeNameForIndex(2);
  }

  static ::mlir::StringAttr getModuleNameAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 2);
  }

  ::mlir::StringAttr getResultNamesAttrName() {
    return getAttributeNameForIndex(3);
  }

  static ::mlir::StringAttr getResultNamesAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 3);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("systemc.interop.verilated");
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
  ::mlir::ArrayAttr getInputNamesAttr() {
    return ::llvm::cast<::mlir::ArrayAttr>(getProperties().inputNames);
  }

  ::mlir::ArrayAttr getInputNames();
  ::mlir::ArrayAttr getResultNamesAttr() {
    return ::llvm::cast<::mlir::ArrayAttr>(getProperties().resultNames);
  }

  ::mlir::ArrayAttr getResultNames();
  void setInstanceNameAttr(::mlir::StringAttr attr) {
    getProperties().instanceName = attr;
  }

  void setInstanceName(::llvm::StringRef attrValue);
  void setModuleNameAttr(::mlir::FlatSymbolRefAttr attr) {
    getProperties().moduleName = attr;
  }

  void setModuleName(::llvm::StringRef attrValue);
  void setInputNamesAttr(::mlir::ArrayAttr attr) {
    getProperties().inputNames = attr;
  }

  void setResultNamesAttr(::mlir::ArrayAttr attr) {
    getProperties().resultNames = attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Operation*module, StringAttr name, ArrayRef<Value> inputs);
  static InteropVerilatedOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Operation*module, StringAttr name, ArrayRef<Value> inputs);
  static InteropVerilatedOp create(::mlir::ImplicitLocOpBuilder &builder, Operation*module, StringAttr name, ArrayRef<Value> inputs);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, Operation*module, StringRef name, ArrayRef<Value> inputs);
  static InteropVerilatedOp create(::mlir::OpBuilder &builder, ::mlir::Location location, Operation*module, StringRef name, ArrayRef<Value> inputs);
  static InteropVerilatedOp create(::mlir::ImplicitLocOpBuilder &builder, Operation*module, StringRef name, ArrayRef<Value> inputs);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange results, ::mlir::StringAttr instanceName, ::mlir::FlatSymbolRefAttr moduleName, ::mlir::ArrayAttr inputNames, ::mlir::ArrayAttr resultNames, ::mlir::ValueRange inputs);
  static InteropVerilatedOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange results, ::mlir::StringAttr instanceName, ::mlir::FlatSymbolRefAttr moduleName, ::mlir::ArrayAttr inputNames, ::mlir::ArrayAttr resultNames, ::mlir::ValueRange inputs);
  static InteropVerilatedOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange results, ::mlir::StringAttr instanceName, ::mlir::FlatSymbolRefAttr moduleName, ::mlir::ArrayAttr inputNames, ::mlir::ArrayAttr resultNames, ::mlir::ValueRange inputs);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange results, ::llvm::StringRef instanceName, ::llvm::StringRef moduleName, ::mlir::ArrayAttr inputNames, ::mlir::ArrayAttr resultNames, ::mlir::ValueRange inputs);
  static InteropVerilatedOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange results, ::llvm::StringRef instanceName, ::llvm::StringRef moduleName, ::mlir::ArrayAttr inputNames, ::mlir::ArrayAttr resultNames, ::mlir::ValueRange inputs);
  static InteropVerilatedOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange results, ::llvm::StringRef instanceName, ::llvm::StringRef moduleName, ::mlir::ArrayAttr inputNames, ::mlir::ArrayAttr resultNames, ::mlir::ValueRange inputs);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static InteropVerilatedOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static InteropVerilatedOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static InteropVerilatedOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static InteropVerilatedOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verifySymbolUses(::mlir::SymbolTableCollection &symbolTable);
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
  /// Return the name of the specified input port or null if it cannot be
  /// determined.
  StringAttr getInputName(size_t i) {
    return hw::instance_like_impl::getName(getInputNames(), i);
  }

  /// Return the name of the specified result or null if it cannot be
  /// determined.
  StringAttr getResultName(size_t i) {
    return hw::instance_like_impl::getName(getResultNames(), i);
  }

  /// Change the name of the specified input port.
  void setInputName(size_t i, StringAttr name) {
    setInputNamesAttr(
      hw::instance_like_impl::updateName(getInputNames(), i, name));
  }

  /// Change the name of the specified output port.
  void setResultName(size_t i, StringAttr name) {
    setResultNamesAttr(
      hw::instance_like_impl::updateName(getResultNames(), i, name));
  }

  /// Lookup the module or extmodule for the symbol.  This returns null on
  /// invalid IR.
  Operation *getReferencedModule() {
    return SymbolTable::lookupNearestSymbolFrom(getOperation(),
                                                getModuleNameAttr());
  }

  /// Get the instances's name.
  StringAttr getName() { return getInstanceNameAttr(); }

  /// Set the instance's name.
  void setName(StringAttr name) { setInstanceNameAttr(name); }

  //===------------------------------------------------------------------===//
  // SymbolOpInterface Methods
  //===------------------------------------------------------------------===//

  /// An InstanceOp may optionally define a symbol.
  bool isOptionalSymbol() { return true; }
};

} // namespace circt::systemc
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::systemc::InteropVerilatedOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::systemc::detail::InteropVerilatedOpGenericAdaptorBase::Properties)

namespace circt::systemc {


//===----------------------------------------------------------------------===//
// ::circt::systemc::MemberAccessOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class MemberAccessOpGenericAdaptorBase {
public:
  struct Properties {
    using accessKindTy = ::MemberAccessKindAttr;
    accessKindTy accessKind;

    auto getAccessKind() const {
      auto &propStorage = this->accessKind;
      return ::llvm::cast<::MemberAccessKindAttr>(propStorage);
    }
    void setAccessKind(const ::MemberAccessKindAttr &propValue) {
      this->accessKind = propValue;
    }
    using memberNameTy = ::mlir::StringAttr;
    memberNameTy memberName;

    auto getMemberName() const {
      auto &propStorage = this->memberName;
      return ::llvm::cast<::mlir::StringAttr>(propStorage);
    }
    void setMemberName(const ::mlir::StringAttr &propValue) {
      this->memberName = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.accessKind == this->accessKind &&
        rhs.memberName == this->memberName &&
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
  MemberAccessOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("systemc.cpp.member_access", odsAttrs.getContext());
  }

  MemberAccessOpGenericAdaptorBase(MemberAccessOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::StringAttr getMemberNameAttr() {
    auto attr = ::llvm::cast<::mlir::StringAttr>(getProperties().memberName);
    return attr;
  }

  ::llvm::StringRef getMemberName();
  ::MemberAccessKindAttr getAccessKindAttr() {
    auto attr = ::llvm::cast<::MemberAccessKindAttr>(getProperties().accessKind);
    return attr;
  }

  ::MemberAccessKind getAccessKind();
};

} // namespace detail
template <typename RangeT>
class MemberAccessOpGenericAdaptor : public detail::MemberAccessOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::MemberAccessOpGenericAdaptorBase;
  static constexpr int odsIndex_object = 0;
public:
  MemberAccessOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  MemberAccessOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : MemberAccessOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  MemberAccessOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : MemberAccessOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  MemberAccessOpGenericAdaptor(RangeT values, const MemberAccessOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = MemberAccessOp, typename = std::enable_if_t<std::is_same_v<LateInst, MemberAccessOp>>>
  MemberAccessOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getObject() {
    return (*getODSOperands(0).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class MemberAccessOpAdaptor : public MemberAccessOpGenericAdaptor<::mlir::ValueRange> {
public:
  using MemberAccessOpGenericAdaptor::MemberAccessOpGenericAdaptor;
  MemberAccessOpAdaptor(MemberAccessOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class MemberAccessOp : public ::mlir::Op<MemberAccessOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::Type>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = MemberAccessOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = MemberAccessOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_object = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("accessKind"), ::llvm::StringRef("memberName")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getAccessKindAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getAccessKindAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getMemberNameAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getMemberNameAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("systemc.cpp.member_access");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::Type> getObject() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(0).begin());
  }

  ::mlir::OpOperand &getObjectMutable() {
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
  ::mlir::StringAttr getMemberNameAttr() {
    return ::llvm::cast<::mlir::StringAttr>(getProperties().memberName);
  }

  ::llvm::StringRef getMemberName();
  ::MemberAccessKindAttr getAccessKindAttr() {
    return ::llvm::cast<::MemberAccessKindAttr>(getProperties().accessKind);
  }

  ::MemberAccessKind getAccessKind();
  void setMemberNameAttr(::mlir::StringAttr attr) {
    getProperties().memberName = attr;
  }

  void setMemberName(::llvm::StringRef attrValue);
  void setAccessKindAttr(::MemberAccessKindAttr attr) {
    getProperties().accessKind = attr;
  }

  void setAccessKind(::MemberAccessKind attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value object, ::mlir::StringAttr memberName, ::MemberAccessKindAttr accessKind);
  static MemberAccessOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value object, ::mlir::StringAttr memberName, ::MemberAccessKindAttr accessKind);
  static MemberAccessOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value object, ::mlir::StringAttr memberName, ::MemberAccessKindAttr accessKind);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value object, ::mlir::StringAttr memberName, ::MemberAccessKindAttr accessKind);
  static MemberAccessOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value object, ::mlir::StringAttr memberName, ::MemberAccessKindAttr accessKind);
  static MemberAccessOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value object, ::mlir::StringAttr memberName, ::MemberAccessKindAttr accessKind);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::Value object, ::llvm::StringRef memberName, ::MemberAccessKind accessKind);
  static MemberAccessOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value object, ::llvm::StringRef memberName, ::MemberAccessKind accessKind);
  static MemberAccessOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value object, ::llvm::StringRef memberName, ::MemberAccessKind accessKind);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value object, ::llvm::StringRef memberName, ::MemberAccessKind accessKind);
  static MemberAccessOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value object, ::llvm::StringRef memberName, ::MemberAccessKind accessKind);
  static MemberAccessOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value object, ::llvm::StringRef memberName, ::MemberAccessKind accessKind);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static MemberAccessOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static MemberAccessOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static MemberAccessOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static MemberAccessOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
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

} // namespace circt::systemc
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::systemc::MemberAccessOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::systemc::detail::MemberAccessOpGenericAdaptorBase::Properties)

namespace circt::systemc {


//===----------------------------------------------------------------------===//
// ::circt::systemc::MethodOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class MethodOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  MethodOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("systemc.method", odsAttrs.getContext());
  }

  MethodOpGenericAdaptorBase(MethodOp op);

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
class MethodOpGenericAdaptor : public detail::MethodOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::MethodOpGenericAdaptorBase;
  static constexpr int odsIndex_funcHandle = 0;
public:
  MethodOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  MethodOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : MethodOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  MethodOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : MethodOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  MethodOpGenericAdaptor(RangeT values, const MethodOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = MethodOp, typename = std::enable_if_t<std::is_same_v<LateInst, MethodOp>>>
  MethodOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getFuncHandle() {
    return (*getODSOperands(0).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class MethodOpAdaptor : public MethodOpGenericAdaptor<::mlir::ValueRange> {
public:
  using MethodOpGenericAdaptor::MethodOpGenericAdaptor;
  MethodOpAdaptor(MethodOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class MethodOp : public ::mlir::Op<MethodOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = MethodOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = MethodOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_funcHandle = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("systemc.method");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::circt::hw::TypeAliasOr<mlir::FunctionType>> getFuncHandle() {
    return ::llvm::cast<::mlir::TypedValue<::circt::hw::TypeAliasOr<mlir::FunctionType>>>(*getODSOperands(0).begin());
  }

  ::mlir::OpOperand &getFuncHandleMutable() {
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value funcHandle);
  static MethodOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value funcHandle);
  static MethodOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value funcHandle);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value funcHandle);
  static MethodOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value funcHandle);
  static MethodOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value funcHandle);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static MethodOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static MethodOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static MethodOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static MethodOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
};

} // namespace circt::systemc
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::systemc::MethodOp)

namespace circt::systemc {


//===----------------------------------------------------------------------===//
// ::circt::systemc::NewOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class NewOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  NewOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("systemc.cpp.new", odsAttrs.getContext());
  }

  NewOpGenericAdaptorBase(NewOp op);

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
class NewOpGenericAdaptor : public detail::NewOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::NewOpGenericAdaptorBase;
  static constexpr int odsIndex_args = 0;
public:
  NewOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  NewOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : NewOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  NewOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : NewOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  NewOpGenericAdaptor(RangeT values, const NewOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = NewOp, typename = std::enable_if_t<std::is_same_v<LateInst, NewOp>>>
  NewOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getArgs() {
    return getODSOperands(0);
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class NewOpAdaptor : public NewOpGenericAdaptor<::mlir::ValueRange> {
public:
  using NewOpGenericAdaptor::NewOpGenericAdaptor;
  NewOpAdaptor(NewOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class NewOp : public ::mlir::Op<NewOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::emitc::PointerType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::OpInvariants, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = NewOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = NewOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_args = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("systemc.cpp.new");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::operand_range getArgs() {
    return getODSOperands(0);
  }

  ::mlir::MutableOperandRange getArgsMutable();
  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::emitc::PointerType> getResult() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::emitc::PointerType>>(*getODSResults(0).begin());
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type result, ::mlir::ValueRange args);
  static NewOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::ValueRange args);
  static NewOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::ValueRange args);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static NewOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static NewOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static NewOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static NewOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
};

} // namespace circt::systemc
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::systemc::NewOp)

namespace circt::systemc {


//===----------------------------------------------------------------------===//
// ::circt::systemc::ReturnOp declarations
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
      odsOpName.emplace("systemc.cpp.return", odsAttrs.getContext());
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
  static constexpr int odsIndex_returnValues = 0;
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

  RangeT getReturnValues() {
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
class ReturnOp : public ::mlir::Op<ReturnOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::HasParent<systemc::FuncOp>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::RegionBranchTerminatorOpInterface::Trait, ::mlir::OpTrait::ReturnLike, ::mlir::OpTrait::IsTerminator> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ReturnOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ReturnOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_returnValues = 0;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::RegionBranchTerminatorOpInterface::Trait<ReturnOp>::getMutableSuccessorOperands;
  using ::mlir::RegionBranchTerminatorOpInterface::Trait<ReturnOp>::getSuccessorRegions;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("systemc.cpp.return");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::operand_range getReturnValues() {
    return getODSOperands(0);
  }

  ::mlir::MutableOperandRange getReturnValuesMutable();
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange returnValues);
  static ReturnOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange returnValues);
  static ReturnOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange returnValues);
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
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
};

} // namespace circt::systemc
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::systemc::ReturnOp)

namespace circt::systemc {


//===----------------------------------------------------------------------===//
// ::circt::systemc::SCFuncOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class SCFuncOpGenericAdaptorBase {
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
  SCFuncOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("systemc.func", odsAttrs.getContext());
  }

  SCFuncOpGenericAdaptorBase(SCFuncOp op);

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
  ::mlir::Region &getBody() {
    return *odsRegions[0];
  }

  ::mlir::RegionRange getRegions() {
    return odsRegions;
  }

};

} // namespace detail
template <typename RangeT>
class SCFuncOpGenericAdaptor : public detail::SCFuncOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::SCFuncOpGenericAdaptorBase;
public:
  SCFuncOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  SCFuncOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : SCFuncOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  SCFuncOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : SCFuncOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  SCFuncOpGenericAdaptor(RangeT values, const SCFuncOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = SCFuncOp, typename = std::enable_if_t<std::is_same_v<LateInst, SCFuncOp>>>
  SCFuncOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class SCFuncOpAdaptor : public SCFuncOpGenericAdaptor<::mlir::ValueRange> {
public:
  using SCFuncOpGenericAdaptor::SCFuncOpGenericAdaptor;
  SCFuncOpAdaptor(SCFuncOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class SCFuncOp : public ::mlir::Op<SCFuncOp, ::mlir::OpTrait::OneRegion, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::circt::hw::TypeAliasOr<mlir::FunctionType>>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::SingleBlock, ::mlir::OpTrait::NoTerminator, ::mlir::OpTrait::HasParent<SCModuleOp>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::OpAsmOpInterface::Trait, circt::systemc::SystemCNameDeclOpInterface::Trait, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = SCFuncOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = SCFuncOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::OpAsmOpInterface::Trait<SCFuncOp>::getAsmBlockArgumentNames;
  using ::mlir::OpAsmOpInterface::Trait<SCFuncOp>::getAsmBlockNames;
  using ::mlir::OpAsmOpInterface::Trait<SCFuncOp>::getDefaultDialect;
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
    return ::llvm::StringLiteral("systemc.func");
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

  ::mlir::TypedValue<::circt::hw::TypeAliasOr<mlir::FunctionType>> getHandle() {
    return ::llvm::cast<::mlir::TypedValue<::circt::hw::TypeAliasOr<mlir::FunctionType>>>(*getODSResults(0).begin());
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
    return ::llvm::cast<::mlir::StringAttr>(getProperties().name);
  }

  ::llvm::StringRef getName();
  void setNameAttr(::mlir::StringAttr attr) {
    getProperties().name = attr;
  }

  void setName(::llvm::StringRef attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, StringAttr name);
  static SCFuncOp create(::mlir::OpBuilder &builder, ::mlir::Location location, StringAttr name);
  static SCFuncOp create(::mlir::ImplicitLocOpBuilder &builder, StringAttr name);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static ::llvm::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::PropertyRef properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
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
  /// Return the block corresponding to the region.
  Block *getBodyBlock() { return &getBody().front(); }
};

} // namespace circt::systemc
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::systemc::SCFuncOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::systemc::detail::SCFuncOpGenericAdaptorBase::Properties)

namespace circt::systemc {


//===----------------------------------------------------------------------===//
// ::circt::systemc::SCModuleOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class SCModuleOpGenericAdaptorBase {
public:
  struct Properties {
    using arg_attrsTy = ::mlir::ArrayAttr;
    arg_attrsTy arg_attrs;

    auto getArgAttrs() const {
      auto &propStorage = this->arg_attrs;
      return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(propStorage);
    }
    void setArgAttrs(const ::mlir::ArrayAttr &propValue) {
      this->arg_attrs = propValue;
    }
    using function_typeTy = ::mlir::TypeAttr;
    function_typeTy function_type;

    auto getFunctionType() const {
      auto &propStorage = this->function_type;
      return ::llvm::cast<::mlir::TypeAttr>(propStorage);
    }
    void setFunctionType(const ::mlir::TypeAttr &propValue) {
      this->function_type = propValue;
    }
    using portNamesTy = ::mlir::ArrayAttr;
    portNamesTy portNames;

    auto getPortNames() const {
      auto &propStorage = this->portNames;
      return ::llvm::cast<::mlir::ArrayAttr>(propStorage);
    }
    void setPortNames(const ::mlir::ArrayAttr &propValue) {
      this->portNames = propValue;
    }
    using res_attrsTy = ::mlir::ArrayAttr;
    res_attrsTy res_attrs;

    auto getResAttrs() const {
      auto &propStorage = this->res_attrs;
      return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(propStorage);
    }
    void setResAttrs(const ::mlir::ArrayAttr &propValue) {
      this->res_attrs = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.arg_attrs == this->arg_attrs &&
        rhs.function_type == this->function_type &&
        rhs.portNames == this->portNames &&
        rhs.res_attrs == this->res_attrs &&
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
  SCModuleOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("systemc.module", odsAttrs.getContext());
  }

  SCModuleOpGenericAdaptorBase(SCModuleOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::TypeAttr getFunctionTypeAttr() {
    auto attr = ::llvm::cast<::mlir::TypeAttr>(getProperties().function_type);
    return attr;
  }

  ::mlir::FunctionType getFunctionType();
  ::mlir::ArrayAttr getArgAttrsAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().arg_attrs);
    return attr;
  }

  ::std::optional< ::mlir::ArrayAttr > getArgAttrs();
  ::mlir::ArrayAttr getResAttrsAttr() {
    auto attr = ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().res_attrs);
    return attr;
  }

  ::std::optional< ::mlir::ArrayAttr > getResAttrs();
  ::mlir::ArrayAttr getPortNamesAttr() {
    auto attr = ::llvm::cast<::mlir::ArrayAttr>(getProperties().portNames);
    return attr;
  }

  ::mlir::ArrayAttr getPortNames();
  ::mlir::Region &getBody() {
    return *odsRegions[0];
  }

  ::mlir::RegionRange getRegions() {
    return odsRegions;
  }

};

} // namespace detail
template <typename RangeT>
class SCModuleOpGenericAdaptor : public detail::SCModuleOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::SCModuleOpGenericAdaptorBase;
public:
  SCModuleOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  SCModuleOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : SCModuleOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  SCModuleOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : SCModuleOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  SCModuleOpGenericAdaptor(RangeT values, const SCModuleOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = SCModuleOp, typename = std::enable_if_t<std::is_same_v<LateInst, SCModuleOp>>>
  SCModuleOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class SCModuleOpAdaptor : public SCModuleOpGenericAdaptor<::mlir::ValueRange> {
public:
  using SCModuleOpGenericAdaptor::SCModuleOpGenericAdaptor;
  SCModuleOpAdaptor(SCModuleOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class SCModuleOp : public ::mlir::Op<SCModuleOp, ::mlir::OpTrait::OneRegion, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::SingleBlock, ::mlir::OpTrait::NoTerminator, ::mlir::OpTrait::HasParent<mlir::ModuleOp>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::SymbolOpInterface::Trait, ::circt::igraph::ModuleOpInterface::Trait, ::mlir::ArgAndResultAttrsOpInterface::Trait, ::mlir::CallableOpInterface::Trait, ::mlir::FunctionOpInterface::Trait, ::mlir::OpTrait::IsIsolatedFromAbove, ::mlir::RegionKindInterface::Trait, ::mlir::OpAsmOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = SCModuleOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = SCModuleOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  using ::circt::igraph::ModuleOpInterface::Trait<SCModuleOp>::getModuleName;
  using ::circt::igraph::ModuleOpInterface::Trait<SCModuleOp>::getModuleNameAttr;
  using ::mlir::OpAsmOpInterface::Trait<SCModuleOp>::getAsmResultNames;
  using ::mlir::OpAsmOpInterface::Trait<SCModuleOp>::getAsmBlockNames;
  using ::mlir::OpAsmOpInterface::Trait<SCModuleOp>::getDefaultDialect;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("arg_attrs"), ::llvm::StringRef("function_type"), ::llvm::StringRef("portNames"), ::llvm::StringRef("res_attrs")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getArgAttrsAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getArgAttrsAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getFunctionTypeAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getFunctionTypeAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getPortNamesAttrName() {
    return getAttributeNameForIndex(2);
  }

  static ::mlir::StringAttr getPortNamesAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 2);
  }

  ::mlir::StringAttr getResAttrsAttrName() {
    return getAttributeNameForIndex(3);
  }

  static ::mlir::StringAttr getResAttrsAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 3);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("systemc.module");
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
  ::mlir::TypeAttr getFunctionTypeAttr() {
    return ::llvm::cast<::mlir::TypeAttr>(getProperties().function_type);
  }

  ::mlir::FunctionType getFunctionType();
  ::mlir::ArrayAttr getArgAttrsAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().arg_attrs);
  }

  ::std::optional< ::mlir::ArrayAttr > getArgAttrs();
  ::mlir::ArrayAttr getResAttrsAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().res_attrs);
  }

  ::std::optional< ::mlir::ArrayAttr > getResAttrs();
  ::mlir::ArrayAttr getPortNamesAttr() {
    return ::llvm::cast<::mlir::ArrayAttr>(getProperties().portNames);
  }

  ::mlir::ArrayAttr getPortNames();
  void setFunctionTypeAttr(::mlir::TypeAttr attr) {
    getProperties().function_type = attr;
  }

  void setFunctionType(::mlir::FunctionType attrValue);
  void setArgAttrsAttr(::mlir::ArrayAttr attr) {
    getProperties().arg_attrs = attr;
  }

  void setResAttrsAttr(::mlir::ArrayAttr attr) {
    getProperties().res_attrs = attr;
  }

  void setPortNamesAttr(::mlir::ArrayAttr attr) {
    getProperties().portNames = attr;
  }

  ::mlir::Attribute removeArgAttrsAttr() {
      auto attr = getProperties().arg_attrs;
      getProperties().arg_attrs = {};
      return attr;
  }

  ::mlir::Attribute removeResAttrsAttr() {
      auto attr = getProperties().res_attrs;
      getProperties().res_attrs = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, StringAttr name, ArrayRef<hw::PortInfo> ports, ArrayRef<NamedAttribute> attributes = {});
  static SCModuleOp create(::mlir::OpBuilder &builder, ::mlir::Location location, StringAttr name, ArrayRef<hw::PortInfo> ports, ArrayRef<NamedAttribute> attributes = {});
  static SCModuleOp create(::mlir::ImplicitLocOpBuilder &builder, StringAttr name, ArrayRef<hw::PortInfo> ports, ArrayRef<NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, StringAttr name, const hw::ModulePortInfo &ports, ArrayRef<NamedAttribute> attributes = {});
  static SCModuleOp create(::mlir::OpBuilder &builder, ::mlir::Location location, StringAttr name, const hw::ModulePortInfo &ports, ArrayRef<NamedAttribute> attributes = {});
  static SCModuleOp create(::mlir::ImplicitLocOpBuilder &builder, StringAttr name, const hw::ModulePortInfo &ports, ArrayRef<NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, StringAttr name, ArrayAttr portNames, ArrayRef<Type> portTypes, ArrayRef<NamedAttribute> attributes = {});
  static SCModuleOp create(::mlir::OpBuilder &builder, ::mlir::Location location, StringAttr name, ArrayAttr portNames, ArrayRef<Type> portTypes, ArrayRef<NamedAttribute> attributes = {});
  static SCModuleOp create(::mlir::ImplicitLocOpBuilder &builder, StringAttr name, ArrayAttr portNames, ArrayRef<Type> portTypes, ArrayRef<NamedAttribute> attributes = {});
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &p);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  ::llvm::LogicalResult verifyRegions();
  ::mlir::Region *getCallableRegion();
  ::llvm::ArrayRef<::mlir::Type> getArgumentTypes();
  ::llvm::ArrayRef<::mlir::Type> getResultTypes();
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
  // Implement RegionKindInterface.
  static RegionKind getRegionKind(unsigned index) {
    return RegionKind::Graph;
  }

  // Use FunctionOpInterface traits's getFunctionBody method.
  using mlir::detail::FunctionOpInterfaceTrait<SCModuleOp>::getFunctionBody;

  /// Return the block corresponding to the region.
  Block *getBodyBlock() { return &getFunctionBody().front(); }

  /// Return the symbol name of this module as string.
  StringRef getModuleName();

  using PortDirectionRange = llvm::iterator_range<
    llvm::filter_iterator<Region::BlockArgListType::iterator,
                          std::function<bool(const BlockArgument &)>>>;

  PortDirectionRange getPortsOfDirection(hw::ModulePort::Direction direction);
  PortDirectionRange getInputPorts() {
    return getPortsOfDirection(hw::ModulePort::Direction::Input);
  }
  PortDirectionRange getOutputPorts() {
    return getPortsOfDirection(hw::ModulePort::Direction::Output);
  }
  PortDirectionRange getInOutPorts() {
    return getPortsOfDirection(hw::ModulePort::Direction::InOut);
  }

  // Return the Ctor operation in this module's body or create one if none
  // exists yet.
  systemc::CtorOp getOrCreateCtor(OpBuilder &builder);

  // Return the Destructor operation in this module's body or create one if
  // none exists yet.
  systemc::DestructorOp getOrCreateDestructor();

  //===------------------------------------------------------------------===//
  // PortList Methods
  //===------------------------------------------------------------------===//
  SmallVector<::circt::hw::PortInfo> getPortList();
};

} // namespace circt::systemc
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::systemc::SCModuleOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::systemc::detail::SCModuleOpGenericAdaptorBase::Properties)

namespace circt::systemc {


//===----------------------------------------------------------------------===//
// ::circt::systemc::SensitiveOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class SensitiveOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  SensitiveOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("systemc.sensitive", odsAttrs.getContext());
  }

  SensitiveOpGenericAdaptorBase(SensitiveOp op);

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
class SensitiveOpGenericAdaptor : public detail::SensitiveOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::SensitiveOpGenericAdaptorBase;
  static constexpr int odsIndex_sensitivities = 0;
public:
  SensitiveOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  SensitiveOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : SensitiveOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  SensitiveOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : SensitiveOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  SensitiveOpGenericAdaptor(RangeT values, const SensitiveOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = SensitiveOp, typename = std::enable_if_t<std::is_same_v<LateInst, SensitiveOp>>>
  SensitiveOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getSensitivities() {
    return getODSOperands(0);
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class SensitiveOpAdaptor : public SensitiveOpGenericAdaptor<::mlir::ValueRange> {
public:
  using SensitiveOpGenericAdaptor::SensitiveOpGenericAdaptor;
  SensitiveOpAdaptor(SensitiveOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class SensitiveOp : public ::mlir::Op<SensitiveOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::HasParent<CtorOp>::Impl, ::mlir::OpTrait::OpInvariants> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = SensitiveOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = SensitiveOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_sensitivities = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("systemc.sensitive");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::Operation::operand_range getSensitivities() {
    return getODSOperands(0);
  }

  ::mlir::MutableOperandRange getSensitivitiesMutable();
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange sensitivities);
  static SensitiveOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange sensitivities);
  static SensitiveOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange sensitivities);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SensitiveOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SensitiveOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SensitiveOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SensitiveOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::llvm::LogicalResult canonicalize(SensitiveOp op, ::mlir::PatternRewriter &rewriter);
  static void getCanonicalizationPatterns(::mlir::RewritePatternSet &results, ::mlir::MLIRContext *context);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
};

} // namespace circt::systemc
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::systemc::SensitiveOp)

namespace circt::systemc {


//===----------------------------------------------------------------------===//
// ::circt::systemc::SignalOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class SignalOpGenericAdaptorBase {
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
    using namedTy = ::mlir::UnitAttr;
    namedTy named;

    auto getNamed() const {
      auto &propStorage = this->named;
      return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(propStorage);
    }
    void setNamed(const ::mlir::UnitAttr &propValue) {
      this->named = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.name == this->name &&
        rhs.named == this->named &&
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
  SignalOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("systemc.signal", odsAttrs.getContext());
  }

  SignalOpGenericAdaptorBase(SignalOp op);

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
  ::mlir::UnitAttr getNamedAttr();
  bool getNamed();
};

} // namespace detail
template <typename RangeT>
class SignalOpGenericAdaptor : public detail::SignalOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::SignalOpGenericAdaptorBase;
public:
  SignalOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  SignalOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : SignalOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  SignalOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : SignalOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  SignalOpGenericAdaptor(RangeT values, const SignalOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = SignalOp, typename = std::enable_if_t<std::is_same_v<LateInst, SignalOp>>>
  SignalOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class SignalOpAdaptor : public SignalOpGenericAdaptor<::mlir::ValueRange> {
public:
  using SignalOpGenericAdaptor::SignalOpGenericAdaptor;
  SignalOpAdaptor(SignalOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class SignalOp : public ::mlir::Op<SignalOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::circt::systemc::SignalType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::HasParent<SCModuleOp>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::OpAsmOpInterface::Trait, circt::systemc::SystemCNameDeclOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = SignalOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = SignalOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::OpAsmOpInterface::Trait<SignalOp>::getAsmBlockArgumentNames;
  using ::mlir::OpAsmOpInterface::Trait<SignalOp>::getAsmBlockNames;
  using ::mlir::OpAsmOpInterface::Trait<SignalOp>::getDefaultDialect;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("name"), ::llvm::StringRef("named")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getNameAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getNameAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getNamedAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getNamedAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("systemc.signal");
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

  ::mlir::TypedValue<::circt::systemc::SignalType> getSignal() {
    return ::llvm::cast<::mlir::TypedValue<::circt::systemc::SignalType>>(*getODSResults(0).begin());
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
  ::mlir::UnitAttr getNamedAttr() {
    return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(getProperties().named);
  }

  bool getNamed();
  void setNameAttr(::mlir::StringAttr attr) {
    getProperties().name = attr;
  }

  void setName(::llvm::StringRef attrValue);
  void setNamedAttr(::mlir::UnitAttr attr) {
    getProperties().named = attr;
  }

  void setNamed(bool attrValue);
  ::mlir::Attribute removeNamedAttr() {
      auto attr = getProperties().named;
      getProperties().named = {};
      return attr;
  }

  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type signal, ::mlir::StringAttr name, /*optional*/::mlir::UnitAttr named = nullptr);
  static SignalOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type signal, ::mlir::StringAttr name, /*optional*/::mlir::UnitAttr named = nullptr);
  static SignalOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type signal, ::mlir::StringAttr name, /*optional*/::mlir::UnitAttr named = nullptr);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::StringAttr name, /*optional*/::mlir::UnitAttr named = nullptr);
  static SignalOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::StringAttr name, /*optional*/::mlir::UnitAttr named = nullptr);
  static SignalOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::StringAttr name, /*optional*/::mlir::UnitAttr named = nullptr);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type signal, ::llvm::StringRef name, /*optional*/bool named = false);
  static SignalOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type signal, ::llvm::StringRef name, /*optional*/bool named = false);
  static SignalOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type signal, ::llvm::StringRef name, /*optional*/bool named = false);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::llvm::StringRef name, /*optional*/bool named = false);
  static SignalOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::llvm::StringRef name, /*optional*/bool named = false);
  static SignalOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::llvm::StringRef name, /*optional*/bool named = false);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SignalOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SignalOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SignalOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SignalOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
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
    assert(index < 2 && "invalid attribute index");
    assert(name.getStringRef() == getOperationName() && "invalid operation name");
    assert(name.isRegistered() && "Operation isn't registered, missing a "
          "dependent dialect loading?");
    return name.getAttributeNames()[index];
  }

public:
};

} // namespace circt::systemc
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::systemc::SignalOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::systemc::detail::SignalOpGenericAdaptorBase::Properties)

namespace circt::systemc {


//===----------------------------------------------------------------------===//
// ::circt::systemc::SignalReadOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class SignalReadOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  SignalReadOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("systemc.signal.read", odsAttrs.getContext());
  }

  SignalReadOpGenericAdaptorBase(SignalReadOp op);

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
class SignalReadOpGenericAdaptor : public detail::SignalReadOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::SignalReadOpGenericAdaptorBase;
  static constexpr int odsIndex_input = 0;
public:
  SignalReadOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  SignalReadOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : SignalReadOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  SignalReadOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : SignalReadOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  SignalReadOpGenericAdaptor(RangeT values, const SignalReadOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = SignalReadOp, typename = std::enable_if_t<std::is_same_v<LateInst, SignalReadOp>>>
  SignalReadOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class SignalReadOpAdaptor : public SignalReadOpGenericAdaptor<::mlir::ValueRange> {
public:
  using SignalReadOpGenericAdaptor::SignalReadOpGenericAdaptor;
  SignalReadOpAdaptor(SignalReadOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class SignalReadOp : public ::mlir::Op<SignalReadOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::Type>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = SignalReadOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = SignalReadOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_input = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("systemc.signal.read");
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
  static SignalReadOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type result, ::mlir::Value input);
  static SignalReadOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type result, ::mlir::Value input);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value input);
  static SignalReadOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value input);
  static SignalReadOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value input);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value input);
  static SignalReadOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value input);
  static SignalReadOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value input);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SignalReadOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SignalReadOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SignalReadOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SignalReadOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SignalReadOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SignalReadOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SignalReadOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SignalReadOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
  /// Infer the return types of this operation.
  static LogicalResult inferReturnTypes(MLIRContext *context,
                                        std::optional<Location> loc,
                                        ValueRange operands,
                                        DictionaryAttr attrs,
                                        mlir::PropertyRef properties,
                                        mlir::RegionRange regions,
                                        SmallVectorImpl<Type> &results) {
    results.push_back(systemc::getSignalBaseType(operands[0].getType()));
    return success();
  }
};

} // namespace circt::systemc
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::systemc::SignalReadOp)

namespace circt::systemc {


//===----------------------------------------------------------------------===//
// ::circt::systemc::SignalWriteOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class SignalWriteOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  SignalWriteOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("systemc.signal.write", odsAttrs.getContext());
  }

  SignalWriteOpGenericAdaptorBase(SignalWriteOp op);

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
class SignalWriteOpGenericAdaptor : public detail::SignalWriteOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::SignalWriteOpGenericAdaptorBase;
  static constexpr int odsIndex_dest = 0;
  static constexpr int odsIndex_src = 1;
public:
  SignalWriteOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  SignalWriteOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : SignalWriteOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  SignalWriteOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : SignalWriteOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  SignalWriteOpGenericAdaptor(RangeT values, const SignalWriteOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = SignalWriteOp, typename = std::enable_if_t<std::is_same_v<LateInst, SignalWriteOp>>>
  SignalWriteOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getDest() {
    return (*getODSOperands(0).begin());
  }

  ValueT getSrc() {
    return (*getODSOperands(1).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class SignalWriteOpAdaptor : public SignalWriteOpGenericAdaptor<::mlir::ValueRange> {
public:
  using SignalWriteOpGenericAdaptor::SignalWriteOpGenericAdaptor;
  SignalWriteOpAdaptor(SignalWriteOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class SignalWriteOp : public ::mlir::Op<SignalWriteOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::NOperands<2>::Impl, ::mlir::OpTrait::OpInvariants> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = SignalWriteOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = SignalWriteOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_dest = 0;
  static constexpr int odsIndex_src = 1;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("systemc.signal.write");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::Type> getDest() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getSrc() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(1).begin());
  }

  ::mlir::OpOperand &getDestMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getSrcMutable() {
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

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value dest, ::mlir::Value src);
  static SignalWriteOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value dest, ::mlir::Value src);
  static SignalWriteOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value dest, ::mlir::Value src);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value dest, ::mlir::Value src);
  static SignalWriteOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value dest, ::mlir::Value src);
  static SignalWriteOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value dest, ::mlir::Value src);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SignalWriteOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static SignalWriteOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SignalWriteOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static SignalWriteOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
};

} // namespace circt::systemc
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::systemc::SignalWriteOp)

namespace circt::systemc {


//===----------------------------------------------------------------------===//
// ::circt::systemc::ThreadOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class ThreadOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  ThreadOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("systemc.thread", odsAttrs.getContext());
  }

  ThreadOpGenericAdaptorBase(ThreadOp op);

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
class ThreadOpGenericAdaptor : public detail::ThreadOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ThreadOpGenericAdaptorBase;
  static constexpr int odsIndex_funcHandle = 0;
public:
  ThreadOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ThreadOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : ThreadOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  ThreadOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : ThreadOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  ThreadOpGenericAdaptor(RangeT values, const ThreadOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = ThreadOp, typename = std::enable_if_t<std::is_same_v<LateInst, ThreadOp>>>
  ThreadOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getFuncHandle() {
    return (*getODSOperands(0).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class ThreadOpAdaptor : public ThreadOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ThreadOpGenericAdaptor::ThreadOpGenericAdaptor;
  ThreadOpAdaptor(ThreadOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class ThreadOp : public ::mlir::Op<ThreadOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::OneOperand, ::mlir::OpTrait::OpInvariants> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ThreadOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ThreadOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_funcHandle = 0;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("systemc.thread");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::circt::hw::TypeAliasOr<mlir::FunctionType>> getFuncHandle() {
    return ::llvm::cast<::mlir::TypedValue<::circt::hw::TypeAliasOr<mlir::FunctionType>>>(*getODSOperands(0).begin());
  }

  ::mlir::OpOperand &getFuncHandleMutable() {
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
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value funcHandle);
  static ThreadOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value funcHandle);
  static ThreadOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value funcHandle);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value funcHandle);
  static ThreadOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value funcHandle);
  static ThreadOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value funcHandle);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ThreadOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ThreadOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ThreadOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ThreadOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
};

} // namespace circt::systemc
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::systemc::ThreadOp)

namespace circt::systemc {


//===----------------------------------------------------------------------===//
// ::circt::systemc::VariableOp declarations
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
      odsOpName.emplace("systemc.cpp.variable", odsAttrs.getContext());
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
  static constexpr int odsIndex_init = 0;
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

  ValueT getInit() {
    auto operands = getODSOperands(0);
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
class VariableOp : public ::mlir::Op<VariableOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::Type>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::OpAsmOpInterface::Trait, circt::systemc::SystemCNameDeclOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = VariableOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = VariableOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_init = 0;
  using Properties = FoldAdaptor::Properties;
  using ::mlir::OpAsmOpInterface::Trait<VariableOp>::getAsmBlockArgumentNames;
  using ::mlir::OpAsmOpInterface::Trait<VariableOp>::getAsmBlockNames;
  using ::mlir::OpAsmOpInterface::Trait<VariableOp>::getDefaultDialect;
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
    return ::llvm::StringLiteral("systemc.cpp.variable");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::Type> getInit() {
    auto operands = getODSOperands(0);
    return operands.empty() ? ::mlir::TypedValue<::mlir::Type>{} : ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*operands.begin());
  }

  ::mlir::MutableOperandRange getInitMutable();
  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::Type> getVariable() {
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
  void setNameAttr(::mlir::StringAttr attr) {
    getProperties().name = attr;
  }

  void setName(::llvm::StringRef attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type variable, ::mlir::StringAttr name, /*optional*/::mlir::Value init);
  static VariableOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type variable, ::mlir::StringAttr name, /*optional*/::mlir::Value init);
  static VariableOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type variable, ::mlir::StringAttr name, /*optional*/::mlir::Value init);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::StringAttr name, /*optional*/::mlir::Value init);
  static VariableOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::StringAttr name, /*optional*/::mlir::Value init);
  static VariableOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::StringAttr name, /*optional*/::mlir::Value init);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type variable, ::llvm::StringRef name, /*optional*/::mlir::Value init);
  static VariableOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type variable, ::llvm::StringRef name, /*optional*/::mlir::Value init);
  static VariableOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type variable, ::llvm::StringRef name, /*optional*/::mlir::Value init);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::llvm::StringRef name, /*optional*/::mlir::Value init);
  static VariableOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::llvm::StringRef name, /*optional*/::mlir::Value init);
  static VariableOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::llvm::StringRef name, /*optional*/::mlir::Value init);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static VariableOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static VariableOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static VariableOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static VariableOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &p);
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
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

} // namespace circt::systemc
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::systemc::VariableOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::systemc::detail::VariableOpGenericAdaptorBase::Properties)


#endif // GET_OP_CLASSES

